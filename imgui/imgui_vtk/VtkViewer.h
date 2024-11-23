#pragma once

#include <vtkProp.h>
#include <vtkPropCollection.h>
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkCallbackCommand.h>
#include <vtkCommand.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkOpenGLFramebufferObject.h>
#include <vtkGenericRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkRenderer.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkCamera.h>

#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui.h"

#include <iostream>
#include <string>
#include <exception>


// RGB Color in range [0.0, 1.0]
#define DEFAULT_BACKGROUND 0.39, 0.39, 0.39
// Alpha value in range [0.0, 1.0] where 1 = opaque
#define DEFAULT_ALPHA 1

class VtkViewerError : public std::runtime_error 
{
public:
	explicit VtkViewerError(const std::string& message) throw() : std::runtime_error(message) {}
	~VtkViewerError() = default;
public:
	virtual char const* what() const throw() 
	{
		return exception::what();
	}
};

class VtkViewer 
{
private:
	static void isCurrentCallbackFn(vtkObject* caller, long unsigned int eventId, void* clientData, void* callData);
	void processEvents();
private:
	vtkSmartPointer<vtkGenericOpenGLRenderWindow> m_renderWindow;
	vtkSmartPointer<vtkGenericRenderWindowInteractor> m_interactor;
	vtkSmartPointer<vtkInteractorStyleTrackballCamera> m_interactorStyle;
	vtkSmartPointer<vtkRenderer> m_renderer;
	vtkSmartPointer<vtkOrientationMarkerWidget> m_orientationMarker;
	vtkSmartPointer<vtkCamera> m_initialCameraState;
private:
	unsigned int m_viewportWidth, m_viewportHeight;
	unsigned int m_tex;
	bool m_firstRender;
public:
	VtkViewer();
	VtkViewer(const VtkViewer& vtkViewer);
	VtkViewer(VtkViewer&& vtkViewer) noexcept;
	~VtkViewer();

	VtkViewer& operator=(const VtkViewer& vtkViewer);

	void ResetRendererOrientation();

private:
	IMGUI_IMPL_API void Init();
public:
	IMGUI_IMPL_API void Render();
	IMGUI_IMPL_API void Render(const ImVec2 size);
	IMGUI_IMPL_API void AddActor(const vtkSmartPointer<vtkProp>& actor);
	IMGUI_IMPL_API void AddActors(const vtkSmartPointer<vtkPropCollection>& actors);
	IMGUI_IMPL_API void RemoveActor(const vtkSmartPointer<vtkProp>& actor);
	void SetViewportSize(const ImVec2 newSize);
public:
	static inline unsigned int NoScrollFlags()
	{
		return ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
	}
public:
	inline void SetRenderWindow(const vtkSmartPointer<vtkGenericOpenGLRenderWindow>& m_renderWindow) 
	{
		this->m_renderWindow = m_renderWindow;
	}

	inline void SetInteractor(const vtkSmartPointer<vtkGenericRenderWindowInteractor>& m_interactor) 
	{
		this->m_interactor = m_interactor;
	}

	inline void SetInteractorStyle(const vtkSmartPointer<vtkInteractorStyleTrackballCamera>& m_interactorStyle) 
	{
		this->m_interactorStyle = m_interactorStyle;
	}

	inline void SetRenderer(const vtkSmartPointer<vtkRenderer>& m_renderer) 
	{
		this->m_renderer = m_renderer;
	}
public:
	inline vtkSmartPointer<vtkGenericOpenGLRenderWindow>& GetRenderWindow() 
	{
		return m_renderWindow;
	}

	inline vtkSmartPointer<vtkGenericRenderWindowInteractor>& GetInteractor() 
	{
		return m_interactor;
	}

	inline vtkSmartPointer<vtkInteractorStyleTrackballCamera>& GetInteractorStyle() 
	{
		return m_interactorStyle;
	}

	inline vtkSmartPointer<vtkRenderer>& GetRenderer() 
	{
		return m_renderer;
	}
public:

	inline unsigned int GetViewportWidth() const 
	{
		return m_viewportWidth;
	}

	inline unsigned int GetViewportHeight() const 
	{
		return m_viewportHeight;
	}

	inline unsigned int GetTexture() const 
	{
		return m_tex;
	}
};
