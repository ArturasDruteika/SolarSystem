#ifndef SOLARSYSTEMSETUP_CONTEXTWINDOW_HPP
#define SOLARSYSTEMSETUP_CONTEXTWINDOW_HPP


#include "ObjectCreationWindow.hpp"
#include "VTKWindow.hpp"

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
#define WINDOW_TITLE "Solar System"


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
    void LoadFont();

    GLFWwindow* m_window;
    ImVec4 m_backgroundColor;

    ObjectCreationWindow* m_pObjectCreationWindow;
    VTKWindow* m_vtkWindow;
};


#endif //SOLARSYSTEMSETUP_CONTEXTWINDOW_HPP
