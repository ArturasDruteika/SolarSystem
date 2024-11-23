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

class VtkViewerError : public std::runtime_error {
public:
	explicit VtkViewerError(const std::string& message) throw() : std::runtime_error(message) {}
	~VtkViewerError() = default;
public:
	virtual char const* what() const throw() {
		return exception::what();
	}
};

class VtkViewer {
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
private:
	IMGUI_IMPL_API void init();
public:
	IMGUI_IMPL_API void render();
	IMGUI_IMPL_API void render(const ImVec2 size);
	IMGUI_IMPL_API void addActor(const vtkSmartPointer<vtkProp>& actor);
	IMGUI_IMPL_API void addActors(const vtkSmartPointer<vtkPropCollection>& actors);
	IMGUI_IMPL_API void removeActor(const vtkSmartPointer<vtkProp>& actor);
	void setViewportSize(const ImVec2 newSize);
public:
	static inline unsigned int NoScrollFlags(){
		return ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
	}
public:
	inline void setRenderWindow(const vtkSmartPointer<vtkGenericOpenGLRenderWindow>& m_renderWindow) {
		this->m_renderWindow = m_renderWindow;
	}

	inline void setInteractor(const vtkSmartPointer<vtkGenericRenderWindowInteractor>& m_interactor) {
		this->m_interactor = m_interactor;
	}

	inline void setInteractorStyle(const vtkSmartPointer<vtkInteractorStyleTrackballCamera>& m_interactorStyle) {
		this->m_interactorStyle = m_interactorStyle;
	}

	inline void setRenderer(const vtkSmartPointer<vtkRenderer>& m_renderer) {
		this->m_renderer = m_renderer;
	}
public:
	inline vtkSmartPointer<vtkGenericOpenGLRenderWindow>& getRenderWindow() {
		return m_renderWindow;
	}

	inline vtkSmartPointer<vtkGenericRenderWindowInteractor>& getInteractor() {
		return m_interactor;
	}

	inline vtkSmartPointer<vtkInteractorStyleTrackballCamera>& getInteractorStyle() {
		return m_interactorStyle;
	}

	inline vtkSmartPointer<vtkRenderer>& getRenderer() {
		return m_renderer;
	}
public:

	inline unsigned int getViewportWidth() const {
		return m_viewportWidth;
	}

	inline unsigned int getViewportHeight() const {
		return m_viewportHeight;
	}

	inline unsigned int getTexture() const {
		return m_tex;
	}
};
