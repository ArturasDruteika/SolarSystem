#include "ObjectsInfoWindow.hpp"
#include <boost/dll.hpp>


ObjectsInfoWindow::ObjectsInfoWindow()
    : m_customFont{ nullptr }
{
}

ObjectsInfoWindow::~ObjectsInfoWindow()
{
}

void ObjectsInfoWindow::Init()
{
    InitInternal();
}

void ObjectsInfoWindow::DeInit()
{
}

void ObjectsInfoWindow::RenderMainWindow()
{
    ImGui::Begin("Objects Info", nullptr, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 5.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 4.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, 4.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_PopupRounding, 2.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarRounding, 4.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_TabRounding, 4.0f);

    ImGui::PopStyleVar(7);

    ImGui::End();
}

void ObjectsInfoWindow::InitInternal()
{
    // Font part
    std::string executableDir = boost::dll::program_location().parent_path().string();
    std::string fontPath = executableDir + "//res//fonts//Roboto-Bold.ttf";
    CreateFont(fontPath, 24.f);
}

void ObjectsInfoWindow::CreateFont(const std::string& fontPath, float fontSize)
{
    std::string executableDir = boost::dll::program_location().parent_path().string();
    ImGuiIO& io = ImGui::GetIO();
    m_customFont = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), fontSize);
}
