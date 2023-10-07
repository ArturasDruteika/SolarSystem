#include "GraphicalWindow.hpp"
#include <boost/dll.hpp>
#include "imgui.h"


GraphicalWindow::GraphicalWindow()
    : m_nStyleVars{0}
{
}

GraphicalWindow::~GraphicalWindow()
{
}

void GraphicalWindow::RenderMainWindow(const std::string& windowName)
{
    ImGui::Begin(windowName.c_str(), nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);
    PushMainWindowStyleVars();
    RenderMainWindowInternal();
    PopMainWindowStyleVars();
    ImGui::End();
}

void GraphicalWindow::PushMainWindowStyleVars()
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 4.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, 4.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_PopupRounding, 2.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarRounding, 4.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_TabRounding, 4.0f);

    m_nStyleVars = 7;
}

void GraphicalWindow::PopMainWindowStyleVars()
{
    ImGui::PopStyleVar(m_nStyleVars);
}

ImFont* GraphicalWindow::CreateFont(const std::string& fontPath, float fontSize)
{
    std::string executableDir = boost::dll::program_location().parent_path().string();
    ImGuiIO& io = ImGui::GetIO();
    return io.Fonts->AddFontFromFileTTF(fontPath.c_str(), fontSize);
}
