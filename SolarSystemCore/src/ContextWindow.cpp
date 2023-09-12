#include "ContextWindow.hpp"
#include "cube.hpp"
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

#include "spdlog/spdlog.h"
#include "implot.h"

#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif

//just for loading image as icon
#define STB_IMAGE_IMPLEMENTATION

#include "stb_image.h"

#include <string>
#include <stdio.h>

// Include glfw3.h after our OpenGL definitions
#include "GLFW/glfw3.h"


// [Win32] Our example includes a copy of glfw3.lib pre-compiled with VS2010 to maximize ease of testing and compatibility with old VS compilers.
// To link with VS2010-era libraries, VS2015+ requires linking with legacy_stdio_definitions.lib, which we do using this pragma.
// Your own project should not be affected, as you are likely to link with a newer binary of GLFW that is adequate for your version of Visual Studio.
#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}


ContextWindow::ContextWindow()
    : m_window{glfwCreateWindow(MIN_VIEWPORT_WIDTH, MIN_VIEWPORT_HEIGHT, "Solar System", nullptr, nullptr)}
    , m_backgroundColor(ImVec4(0.45f, 0.55f, 0.60f, 1.00f))
    , m_pDisplayWindow{nullptr}
{

}

ContextWindow::~ContextWindow()
{

}

int ContextWindow::Init()
{
    glfwSetErrorCallback(ContextWindow::glfw_error_callback);
    if (!glfwInit())
        return 1;

    spdlog::info("Window initialized!");

    // Decide GL+GLSL versions
#if __APPLE__
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    m_window = glfwCreateWindow(MIN_VIEWPORT_WIDTH, MIN_VIEWPORT_HEIGHT, WINDOW_TITLE, nullptr, nullptr);
    if (m_window == nullptr)
        return 1;

    //set minimum window size
    glfwSetWindowSizeLimits(m_window, MIN_VIEWPORT_WIDTH, MIN_VIEWPORT_HEIGHT, GLFW_DONT_CARE, GLFW_DONT_CARE);
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1); // Enable vsync

    // Initialize OpenGL loader
#if defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)
    bool err = gl3wInit() != 0;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)
    bool err = glewInit() != GLEW_OK;
#elif defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)
    bool err = gladLoadGL() == 0;
#else
    bool err = false; // If you use IMGUI_IMPL_OPENGL_LOADER_CUSTOM, your loader is likely to requires some form of initialization.
#endif
    if (err)
    {
        fprintf(stderr, "Failed to initialize OpenGL loader!\n");
        return 1;
    }

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    // Initialize DisplayWindow
    m_pDisplayWindow = new DisplayWindow();

    ImGuiIO& io = ImGui::GetIO();
    (void) io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    //io.ConfigViewportsNoAutoMerge = true;
    //io.ConfigViewportsNoTaskBarIcon = true;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
    ImGuiStyle& style = ImGui::GetStyle();
    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        style.WindowRounding = 0.0f;
        style.Colors[ImGuiCol_WindowBg].w = 1.0f;
    }

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init();

    ImPlot::CreateContext();

    CreateWindowIcon();

    return 0;
}

void ContextWindow::DeInit()
{
    // Cleanup
    ImPlot::DestroyContext();
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

int ContextWindow::Run()
{
    //setup 'enable docking' flag
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    int display_w;
    int display_h;

//    static ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse;

    while (!glfwWindowShouldClose(m_window))
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

//        Dockspace
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

        m_pDisplayWindow->RunMainWindow();

        // Rendering
        ImGui::Render();

        glfwMakeContextCurrent(m_window);
        glfwGetFramebufferSize(m_window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(
            m_backgroundColor.x * m_backgroundColor.w,
            m_backgroundColor.y * m_backgroundColor.w,
            m_backgroundColor.z * m_backgroundColor.w,
            m_backgroundColor.w
        );
        glClear(GL_COLOR_BUFFER_BIT);

        // If you are using this code with non-legacy OpenGL header/contexts (which you should not, prefer using imgui_impl_opengl3.cpp!!),
        // you may need to backup/reset/restore other state, e.g. for current shader using the commented lines below.
        //GLint last_program;
        //glGetIntegerv(GL_CURRENT_PROGRAM, &last_program);
        //glUseProgram(0);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        //glUseProgram(last_program);

        // Update and Render additional Platform Windows
        // (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
        //  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(m_window);
    }

    return 0;
}

int ContextWindow::RenderVtkWindow()
{
    InitializeVtkActors();
    //setup 'enable docking' flag
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    int display_w;
    int display_h;

    bool vtk_2_open = true;
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    // Main loop
    while (!glfwWindowShouldClose(m_window))
    {
        // Poll and handle events (inputs, window resize, etc.)
        // You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
        // - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application.
        // - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application.
        // Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
        glfwPollEvents();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // 5. Show a more complex VtkViewer Instance (Closable, Widgets in Window)
        ImGui::SetNextWindowSize(ImVec2(720, 480), ImGuiCond_FirstUseEver);
        if (vtk_2_open)
        {
            ImGui::Begin("Vtk Viewer 2", &vtk_2_open, VtkViewer::NoScrollFlags());

            // Other widgets can be placed in the same window as the VTKViewer
            // However, since the VTKViewer is rendered to size ImGui::GetContentRegionAvail(),
            // it is best to put all widgets first (i.e., render the VTKViewer last).
            // If you want the VTKViewer to be at the top of a window, you can manually calculate
            // and define its size, accounting for the space taken up by other widgets

            auto renderer = m_vtkViewer2.getRenderer();
            if (ImGui::Button("VTK Background: Black"))
            {
                renderer->SetBackground(0, 0, 0);
            }
            ImGui::SameLine();
            if (ImGui::Button("VTK Background: Red"))
            {
                renderer->SetBackground(1, 0, 0);
            }
            ImGui::SameLine();
            if (ImGui::Button("VTK Background: Green"))
            {
                renderer->SetBackground(0, 1, 0);
            }
            ImGui::SameLine();
            if (ImGui::Button("VTK Background: Blue"))
            {
                renderer->SetBackground(0, 0, 1);
            }
            static float vtk2BkgAlpha = 0.2f;
            ImGui::SliderFloat("Background Alpha", &vtk2BkgAlpha, 0.0f, 1.0f);
            renderer->SetBackgroundAlpha(vtk2BkgAlpha);

            m_vtkViewer2.render();

            ImGui::End();
        }

        ImGui::Render();

        int display_w, display_h;
        glfwGetFramebufferSize(m_window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
        {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context);
        }

        glfwSwapBuffers(m_window);
    }

    return 0;
}

void ContextWindow::glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void ContextWindow::CreateWindowIcon()
{
    std::string iconFile = "res//solar_system_32x32.png";
    try
    {
        GLFWimage images[1];
        images[0].pixels = stbi_load(iconFile.c_str(), &images[0].width, &images[0].height, 0, 4); //rgba channels
        glfwSetWindowIcon(m_window, 1, images);
        stbi_image_free(images[0].pixels);
    }
    catch (...)
    {
        spdlog::warn("Failed to load icon from " + iconFile);
    }
}

void ContextWindow::InitializeVtkActors()
{
    vtkNew<vtkActor> cubeActor = Cube::GenerateCube();
    m_vtkViewer1.addActor(cubeActor);
    m_vtkViewer2.getRenderer()->SetBackground(0, 0, 0); // Black background
    m_vtkViewer2.addActor(cubeActor);
}
