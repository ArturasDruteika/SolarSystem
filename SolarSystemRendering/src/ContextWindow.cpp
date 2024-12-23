#include "ContextWindow.hpp"
#include "Cube.hpp"
#include "spdlog/spdlog.h"
#include "implot.h"
#include "boost/dll.hpp"

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
    , m_pObjectCreationWindow{nullptr}
    , m_pVTKWindow{nullptr}
    , m_pObjectsInfoWindow{ nullptr }
    , m_pGraphicalWindows{}
{

}

ContextWindow::~ContextWindow()
{
    for (GraphicalWindow* pGraphicalWindow : m_pGraphicalWindows)
    {
        delete pGraphicalWindow;
    }
    m_pGraphicalWindows.clear(); // Optional, ensures the vector is emptied.
}

int ContextWindow::Init()
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
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

    LoadFont();

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
    SetUpAllGraphicalWindows();

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

    // TODO: delete pointers to windows!!!
}

int ContextWindow::Run()
{
    //setup 'enable docking' flag
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

    int display_w;
    int display_h;

    // static ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoCollapse;

    m_pVTKWindow->InitializeVtkActors();

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

        // Dockspace
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());

        for (GraphicalWindow* pGraphicalWindow : m_pGraphicalWindows)
        {
            pGraphicalWindow->RenderWindow();
        }

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

void ContextWindow::LoadFont()
{
    ImGuiIO& io = ImGui::GetIO();
    std::string executableDir = boost::dll::program_location().parent_path().string();
    std::string fontPath = executableDir + "//res//fonts//Roboto-Bold.ttf";
    io.Fonts->AddFontFromFileTTF(fontPath.c_str(), 14);
}

void ContextWindow::CreateAllGraphicalWindows()
{
    m_pObjectsInfoWindow = new ObjectsInfoWindow("Objects Info");
    m_pObjectCreationWindow = new ObjectCreationWindow("Object Creation");
    m_pVTKWindow = new VTKWindow("Vtk Viewer");
}

void ContextWindow::InitAllGraphicalWindows()
{
    m_pObjectCreationWindow->Init();
    m_pVTKWindow->Init();
    m_pObjectsInfoWindow->Init();

}

void ContextWindow::ConnectObservers()
{
    m_pObjectCreationWindow->OnCreateSignal.connect(
        boost::bind(
            &VTKWindow::OnNewPlanet,
            m_pVTKWindow,
            boost::placeholders::_1,
            boost::placeholders::_2
        )
    );

    m_pObjectsInfoWindow->OnDeleteRecord.connect(
        boost::bind(
            &VTKWindow::OnDeletePlanet,
            m_pVTKWindow,
            boost::placeholders::_1
        )
    );
    m_pObjectsInfoWindow->OnDeleteRecord.connect(
        boost::bind(
            &ObjectCreationWindow::OnDeletePlanet,
            m_pObjectCreationWindow,
            boost::placeholders::_1
        )
    );
}

void ContextWindow::AddAllGraphicalWindows()
{
    m_pGraphicalWindows.push_back(m_pObjectsInfoWindow);
    m_pGraphicalWindows.push_back(m_pObjectCreationWindow);
    m_pGraphicalWindows.push_back(m_pVTKWindow);
}

void ContextWindow::SetUpAllGraphicalWindows()
{
    CreateAllGraphicalWindows();
    InitAllGraphicalWindows();
    ConnectObservers();
    AddAllGraphicalWindows();
}
