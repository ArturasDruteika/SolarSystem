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



void VtkViewer::isCurrentCallbackFn(vtkObject* caller, long unsigned int eventId, void* clientData, void* callData){
	bool* isCurrent = static_cast<bool*>(callData);
	*isCurrent = true;
}

void VtkViewer::processEvents(){
	if (!ImGui::IsWindowFocused() && !ImGui::IsWindowHovered()){
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

	interactor->SetEventInformationFlipY(xpos, ypos, ctrl, shift, dclick);

	if (ImGui::IsWindowHovered()){
		if (io.MouseClicked[ImGuiMouseButton_Left]){
			interactor->InvokeEvent(vtkCommand::LeftButtonPressEvent, nullptr);
		}
		else if (io.MouseClicked[ImGuiMouseButton_Right]){
			interactor->InvokeEvent(vtkCommand::RightButtonPressEvent, nullptr);
			ImGui::SetWindowFocus(); // make right-clicks bring window into focus
		}
		else if (io.MouseWheel > 0){
			interactor->InvokeEvent(vtkCommand::MouseWheelForwardEvent, nullptr);
		}
		else if (io.MouseWheel < 0){
			interactor->InvokeEvent(vtkCommand::MouseWheelBackwardEvent, nullptr);
		}
	}

	if (io.MouseReleased[ImGuiMouseButton_Left]){
		interactor->InvokeEvent(vtkCommand::LeftButtonReleaseEvent, nullptr);
	}
	else if (io.MouseReleased[ImGuiMouseButton_Right]){
		interactor->InvokeEvent(vtkCommand::RightButtonReleaseEvent, nullptr);
	}

	interactor->InvokeEvent(vtkCommand::MouseMoveEvent, nullptr);
}

VtkViewer::VtkViewer() 
	: viewportWidth(0), viewportHeight(0), renderWindow(nullptr), interactor(nullptr), interactorStyle(nullptr),
	renderer(nullptr), tex(0), firstRender(true){
	init();
}

VtkViewer::VtkViewer(const VtkViewer& vtkViewer) 
	: viewportWidth(0), viewportHeight(0), renderWindow(vtkViewer.renderWindow), interactor(vtkViewer.interactor),
	interactorStyle(vtkViewer.interactorStyle), renderer(vtkViewer.renderer), tex(vtkViewer.tex),
	firstRender(vtkViewer.firstRender){
}

VtkViewer::VtkViewer(VtkViewer&& vtkViewer) noexcept 
	: viewportWidth(0), viewportHeight(0), renderWindow(std::move(vtkViewer.renderWindow)),
	interactor(std::move(vtkViewer.interactor)), interactorStyle(std::move(vtkViewer.interactorStyle)),
	renderer(std::move(vtkViewer.renderer)), tex(vtkViewer.tex), firstRender(vtkViewer.firstRender){
}

VtkViewer::~VtkViewer(){
	renderer = nullptr;
	interactorStyle = nullptr;
	interactor = nullptr;
	renderWindow = nullptr;

	glDeleteTextures(1, &tex);
}

VtkViewer& VtkViewer::operator=(const VtkViewer& vtkViewer){
	viewportWidth = vtkViewer.viewportWidth;
	viewportHeight = vtkViewer.viewportHeight;
	renderWindow = vtkViewer.renderWindow;
	interactor = vtkViewer.interactor;
	interactorStyle = vtkViewer.interactorStyle;
	renderer = vtkViewer.renderer;
	tex = vtkViewer.tex;
	firstRender = vtkViewer.firstRender;
	return *this;
}

void VtkViewer::init() {
	renderer = vtkSmartPointer<vtkRenderer>::New();
	renderer->ResetCamera();
	renderer->SetBackground(DEFAULT_BACKGROUND);
	renderer->SetBackgroundAlpha(DEFAULT_ALPHA);

	interactorStyle = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
	interactorStyle->SetDefaultRenderer(renderer);

	interactor = vtkSmartPointer<vtkGenericRenderWindowInteractor>::New();
	interactor->SetInteractorStyle(interactorStyle);
	interactor->EnableRenderOff();

	int viewportSize[2] = { static_cast<int>(viewportWidth), static_cast<int>(viewportHeight) };

	renderWindow = vtkSmartPointer<vtkGenericOpenGLRenderWindow>::New();
	renderWindow->SetSize(viewportSize);

	vtkSmartPointer<vtkCallbackCommand> isCurrentCallback = vtkSmartPointer<vtkCallbackCommand>::New();
	isCurrentCallback->SetCallback(&isCurrentCallbackFn);
	renderWindow->AddObserver(vtkCommand::WindowIsCurrentEvent, isCurrentCallback);

	renderWindow->SwapBuffersOn();
	renderWindow->SetOffScreenRendering(true);
	renderWindow->SetFrameBlitModeToNoBlit();
	renderWindow->AddRenderer(renderer);
	renderWindow->SetInteractor(interactor);

	// Add orientation marker
	vtkSmartPointer<vtkAxesActor> axesActor = vtkSmartPointer<vtkAxesActor>::New();
	m_orientationMarker = vtkSmartPointer<vtkOrientationMarkerWidget>::New();
	m_orientationMarker->SetOrientationMarker(axesActor);
	m_orientationMarker->SetInteractor(interactor);
	m_orientationMarker->SetViewport(0.0, 0.8, 0.2, 1.0); // Top-left corner, 20% of the window size
	m_orientationMarker->SetEnabled(1); // Enable the widget
	m_orientationMarker->InteractiveOn(); // Allow interaction with the marker

	if (!renderer || !interactorStyle || !renderWindow || !interactor || !m_orientationMarker) {
		throw VtkViewerError("Couldn't initialize VtkViewer");
	}
}

void VtkViewer::render(){
	render(ImGui::GetContentRegionAvail());
}
void VtkViewer::render(const ImVec2 size){
	setViewportSize(size);

	renderWindow->Render();
	renderWindow->WaitForCompletion();

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0,0));
	ImGui::BeginChild("##Viewport", size, true, VtkViewer::NoScrollFlags());
	ImGui::Image(reinterpret_cast<void*>(tex), ImGui::GetContentRegionAvail(), ImVec2(0, 1), ImVec2(1, 0));
	processEvents();
	ImGui::EndChild();
	ImGui::PopStyleVar();
}

void VtkViewer::addActor(const vtkSmartPointer<vtkProp>& actor){
	renderer->AddActor(actor);
	renderer->ResetCamera();
}

void VtkViewer::addActors(const vtkSmartPointer<vtkPropCollection>& actors){
	actors->InitTraversal();
	vtkProp* actor;
	vtkCollectionSimpleIterator sit;
	for (actors->InitTraversal(sit); (actor = actors->GetNextProp(sit));){
		renderer->AddActor(actor);
		renderer->ResetCamera();
	}
}

void VtkViewer::removeActor(const vtkSmartPointer<vtkProp>& actor){
	renderer->RemoveActor(actor);
}

void VtkViewer::setViewportSize(const ImVec2 newSize){
	if (gl3wInit()) {
		// Handle initialization error
		return;
	}

	if (((viewportWidth == newSize.x && viewportHeight == newSize.y) || viewportWidth <= 0 || viewportHeight <= 0) && !firstRender){
		return;
	}

	viewportWidth = static_cast<unsigned int>(newSize.x);
	viewportHeight = static_cast<unsigned int>(newSize.y);

	int viewportSize[] = {static_cast<int>(newSize.x), static_cast<int>(newSize.y)};

	// Free old buffers
	glDeleteTextures(1, &tex);

	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, viewportWidth, viewportHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, 0);

	glBindTexture(GL_TEXTURE_2D, 0);

	renderWindow->InitializeFromCurrentContext();
	renderWindow->SetSize(viewportSize);
	interactor->SetSize(viewportSize);

	auto vtkfbo = renderWindow->GetDisplayFramebuffer();
	vtkfbo->Bind();
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);
	vtkfbo->UnBind();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	firstRender = false;
}
