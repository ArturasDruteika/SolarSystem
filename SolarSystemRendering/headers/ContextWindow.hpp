#ifndef SOLARSYSTEMSETUP_CONTEXTWINDOW_HPP
#define SOLARSYSTEMSETUP_CONTEXTWINDOW_HPP


#include "ObjectCreationWindow.hpp"
#include "VTKWindow.hpp"
#include "ObjectsInfoWindow.hpp"
#include "GraphicalWindow.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)

#include <GL/gl3w.h>    // Initialize with gl3wInit()

#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
#include <GL/glew.h>    // Initialize with glewInit()
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
#include <glad/glad.h>  // Initialize with gladLoadGL()
#else
//#include IMGUI_IMPL_OPENGL_LOADER_CUSTOM
#endif

// Include glfw3.h after our OpenGL definitions
#include "GLFW/glfw3.h"

#include <string>


constexpr int MIN_VIEWPORT_WIDTH{1266};
constexpr int MIN_VIEWPORT_HEIGHT{668};
constexpr auto WINDOW_TITLE = "Solar System";


class ContextWindow
{
public:
    ContextWindow();
    ~ContextWindow();

    int Init();
    void DeInit();

    int Run();

private:
    // OpenGL error callback
    static void glfw_error_callback(int error, const char* description);
    // Load icon
    void CreateWindowIcon();
    // Load Font
    void LoadFont();
    // Create all the separate windows
    void CreateAllGraphicalWindows();
    // Initialize all the separate windows
    void InitAllGraphicalWindows();
    // Add all the separate windows to the graphical windows vector
    void AddAllGraphicalWindows();
    // Set up all the separate windows
    void SetUpAllGraphicalWindows();


    std::vector<GraphicalWindow*> m_pGraphicalWindows;
    GLFWwindow* m_window;
    ImVec4 m_backgroundColor;
    ObjectCreationWindow* m_pObjectCreationWindow;
    VTKWindow* m_pVTKWindow;
    ObjectsInfoWindow* m_pObjectsInfoWindow;
};


#endif //SOLARSYSTEMSETUP_CONTEXTWINDOW_HPP
