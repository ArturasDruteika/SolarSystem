#include "VtkViewer.h"

//#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GL/gl3w.h>
#include <GLFW/glfw3.h> // Will drag system OpenGL headers
#include <vtkAxesActor.h>
#include <vtkOrientationMarkerWidget.h>

// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif



void VtkViewer::isCurrentCallbackFn(vtkObject* caller, long unsigned int eventId, void* clientData, void* callData)
{
	bool* isCurrent = static_cast<bool*>(callData);
	*isCurrent = true;
}

void VtkViewer::processEvents()
{
	if (!ImGui::IsWindowFocused() && !ImGui::IsWindowHovered())
	{
		return;
	}

	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigWindowsMoveFromTitleBarOnly = true; // don't drag window when clicking on image.
	ImVec2 viewportPos = ImGui::GetCursorStartPos();

	double xpos = static_cast<double>(io.MousePos[0]) - static_cast<double>(viewportPos.x);
	double ypos = static_cast<double>(io.MousePos[1]) - static_cast<double>(viewportPos.y);
	int ctrl = static_cast<int>(io.KeyCtrl);
	int shift = static_cast<int>(io.KeyShift);
	bool dclick = io.MouseDoubleClicked[0] || io.MouseDoubleClicked[1] || io.MouseDoubleClicked[2];

	m_interactor->SetEventInformationFlipY(xpos, ypos, ctrl, shift, dclick);

	if (ImGui::IsWindowHovered())
	{
		if (io.MouseClicked[ImGuiMouseButton_Left])
		{
			m_interactor->InvokeEvent(vtkCommand::LeftButtonPressEvent, nullptr);
		}
		else if (io.MouseClicked[ImGuiMouseButton_Right])
		{
			m_interactor->InvokeEvent(vtkCommand::RightButtonPressEvent, nullptr);
			ImGui::SetWindowFocus(); // make right-clicks bring window into focus
		}
		else if (io.MouseWheel > 0)
		{
			m_interactor->InvokeEvent(vtkCommand::MouseWheelForwardEvent, nullptr);
		}
		else if (io.MouseWheel < 0)
		{
			m_interactor->InvokeEvent(vtkCommand::MouseWheelBackwardEvent, nullptr);
		}
	}

	if (io.MouseReleased[ImGuiMouseButton_Left])
	{
		m_interactor->InvokeEvent(vtkCommand::LeftButtonReleaseEvent, nullptr);
	}
	else if (io.MouseReleased[ImGuiMouseButton_Right])
	{
		m_interactor->InvokeEvent(vtkCommand::RightButtonReleaseEvent, nullptr);
	}

	m_interactor->InvokeEvent(vtkCommand::MouseMoveEvent, nullptr);
}

VtkViewer::VtkViewer() 
	: m_viewportWidth(0) 
	, m_viewportHeight(0)
	, m_renderWindow(nullptr)
	, m_interactor(nullptr)
	, m_interactorStyle(nullptr)
	, m_renderer(nullptr)
	, m_tex(0)
	, m_firstRender(true)
{
	Init();
}

VtkViewer::VtkViewer(const VtkViewer& vtkViewer) 
	: m_viewportWidth(0)
	, m_viewportHeight(0)
	, m_renderWindow(vtkViewer.m_renderWindow)
	, m_interactor(vtkViewer.m_interactor)
	, m_interactorStyle(vtkViewer.m_interactorStyle)
	, m_renderer(vtkViewer.m_renderer)
	, m_tex(vtkViewer.m_tex)
	, m_firstRender(vtkViewer.m_firstRender)
{
}

VtkViewer::VtkViewer(VtkViewer&& vtkViewer) noexcept 
	: m_viewportWidth(0)
	, m_viewportHeight(0)
	, m_renderWindow(std::move(vtkViewer.m_renderWindow))
	, m_interactor(std::move(vtkViewer.m_interactor))
	, m_interactorStyle(std::move(vtkViewer.m_interactorStyle))
	, m_renderer(std::move(vtkViewer.m_renderer))
	, m_tex(vtkViewer.m_tex)
	, m_firstRender(vtkViewer.m_firstRender)
{
}

VtkViewer::~VtkViewer()
{
	m_renderer = nullptr;
	m_interactorStyle = nullptr;
	m_interactor = nullptr;
	m_renderWindow = nullptr;

	glDeleteTextures(1, &m_tex);
}

VtkViewer& VtkViewer::operator=(const VtkViewer& vtkViewer)
{
	m_viewportWidth = vtkViewer.m_viewportWidth;
	m_viewportHeight = vtkViewer.m_viewportHeight;
	m_renderWindow = vtkViewer.m_renderWindow;
	m_interactor = vtkViewer.m_interactor;
	m_interactorStyle = vtkViewer.m_interactorStyle;
	m_renderer = vtkViewer.m_renderer;
	m_tex = vtkViewer.m_tex;
	m_firstRender = vtkViewer.m_firstRender;
	return *this;
}

void VtkViewer::Init() 
{
	m_renderer = vtkSmartPointer<vtkRenderer>::New();
	m_renderer->ResetCamera();
	m_renderer->SetBackground(DEFAULT_BACKGROUND);
	m_renderer->SetBackgroundAlpha(DEFAULT_ALPHA);

	m_interactorStyle = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	m_interactorStyle->SetDefaultRenderer(m_renderer);

	m_interactor = vtkSmartPointer<vtkGenericRenderWindowInteractor>::New();
	m_interactor->SetInteractorStyle(m_interactorStyle);
	m_interactor->EnableRenderOff();

	int viewportSize[2] = { static_cast<int>(m_viewportWidth), static_cast<int>(m_viewportHeight) };

	m_renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
	m_renderWindow->SetSize(viewportSize);

	vtkSmartPointer<vtkCallbackCommand> isCurrentCallback = vtkSmartPointer<vtkCallbackCommand>::New();
	isCurrentCallback->SetCallback(&isCurrentCallbackFn);
	m_renderWindow->AddObserver(vtkCommand::WindowIsCurrentEvent, isCurrentCallback);

	m_renderWindow->SwapBuffersOn();
	m_renderWindow->SetOffScreenRendering(true);
	m_renderWindow->SetFrameBlitModeToNoBlit();
	m_renderWindow->AddRenderer(m_renderer);
	m_renderWindow->SetInteractor(m_interactor);

	// Add orientation marker
	vtkSmartPointer<vtkAxesActor> axesActor = vtkSmartPointer<vtkAxesActor>::New();
	m_orientationMarker = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
	m_orientationMarker->SetOrientationMarker(axesActor);
	m_orientationMarker->SetInteractor(m_interactor);
	m_orientationMarker->SetViewport(0.8, 0.8, 1.0, 1.0); // Top-left corner, 20% of the window size
	m_orientationMarker->SetEnabled(1); // Enable the widget
	m_orientationMarker->InteractiveOn(); // Allow interaction with the marker

	m_initialCameraState = vtkSmartPointer<vtkCamera>::New();
	m_initialCameraState->DeepCopy(m_renderer->GetActiveCamera());

	if (!m_renderer || !m_interactorStyle || !m_renderWindow || !m_interactor || !m_orientationMarker) 
	{
		throw VtkViewerError("Couldn't initialize VtkViewer");
	}
}

void VtkViewer::Render()
{
	ImVec2 windowSize = ImGui::GetContentRegionAvail();
	windowSize.y -= 30;
	Render(windowSize);
}
void VtkViewer::Render(const ImVec2 size)
{
	SetViewportSize(size);

	if (ImGui::Button("Reset To Original View", ImVec2(200, 25)))
	{
		m_renderer->GetActiveCamera()->DeepCopy(m_initialCameraState);
		m_renderer->ResetCamera();
	}

	m_renderWindow->Render();
	m_renderWindow->WaitForCompletion();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0,0));
	ImGui::BeginChild("##Viewport", size, true, VtkViewer::NoScrollFlags());
	ImGui::Image(reinterpret_cast<void*>(m_tex), ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
	processEvents();
	ImGui::EndChild();
	ImGui::PopStyleVar();
}

void VtkViewer::AddActor(const vtkSmartPointer<vtkProp>& actor)
{
	m_renderer->AddActor(actor);
	m_renderer->ResetCamera();
}

void VtkViewer::AddActors(const vtkSmartPointer<vtkPropCollection>& actors)
{
	actors->InitTraversal();
	vtkProp* actor;
	vtkCollectionSimpleIterator sit;
	for (actors->InitTraversal(sit); (actor = actors->GetNextProp(sit));)
	{
		m_renderer->AddActor(actor);
		m_renderer->ResetCamera();
	}
}

void VtkViewer::RemoveActor(const vtkSmartPointer<vtkProp>& actor)
{
	m_renderer->RemoveActor(actor);
}

void VtkViewer::SetViewportSize(const ImVec2 newSize)
{
	if (gl3wInit()) 
	{
		// Handle initialization error
		return;
	}

	if (((m_viewportWidth == newSize.x && m_viewportHeight == newSize.y) || m_viewportWidth <= 0 || m_viewportHeight <= 0) && !m_firstRender)
	{
		return;
	}

	m_viewportWidth = static_cast<unsigned int>(newSize.x);
	m_viewportHeight = static_cast<unsigned int>(newSize.y) - 25;

	int viewportSize[] = {static_cast<int>(newSize.x), static_cast<int>(newSize.y)};

	// Free old buffers
	glDeleteTextures(1, &m_tex);

	glGenTextures(1, &m_tex);
	glBindTexture(GL_TEXTURE_2D, m_tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_viewportWidth, m_viewportHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	glBindTexture(GL_TEXTURE_2D, 0);

	m_renderWindow->InitializeFromCurrentContext();
	m_renderWindow->SetSize(viewportSize);
	m_interactor->SetSize(viewportSize);

	auto vtkfbo = m_renderWindow->GetDisplayFramebuffer();
	vtkfbo->Bind();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_tex, 0);
	vtkfbo->UnBind();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	if (m_firstRender)
	{
		m_initialCameraState->DeepCopy(m_renderer->GetActiveCamera());
	}
	m_firstRender = false;
}
