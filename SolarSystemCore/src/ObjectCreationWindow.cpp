#include "ObjectCreationWindow.hpp"
#include "imgui.h"
#include <boost/dll.hpp>


ObjectCreationWindow::ObjectCreationWindow()
    : m_planetsCount{0}
    , m_customFont{nullptr}
{
    m_objectAttributes.radius = 1;
    m_objectAttributes.distanceFromCenter = 1;
    m_objectAttributes.speed = 1;
    m_objectAttributes.tiltDegrees = 1;
}

ObjectCreationWindow::~ObjectCreationWindow() = default;

void ObjectCreationWindow::Init()
{
    InitInternal();
}

void ObjectCreationWindow::RenderMainWindow()
{
    ImGui::Begin(
        "Object Creation",
        nullptr,
        ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse
    );

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 4.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 4.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_GrabRounding, 4.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_PopupRounding, 2.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarRounding, 4.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_TabRounding, 4.0f);

    RenderObjectRadiusSection();
    RenderObjectDistanceSection();
    RenderObjectSpeedSection();
    RenderObjectTiltSection();
    ImGui::Separator();
    RenderObjectCreationSection();
    ImGui::Separator();
    RenderPlanetsTable();

    ImGui::PopStyleVar(7);

    ImGui::End();
}

void ObjectCreationWindow::InitInternal()
{
    // Font part
    std::string executableDir = boost::dll::program_location().parent_path().string();
    std::string fontPath = executableDir + "//res//fonts//Roboto-Bold.ttf";
    CreateFont(fontPath, 24.f);
}

void ObjectCreationWindow::RenderObjectRadiusSection()
{
    ImGui::SeparatorText("Object Radius");
    ImGui::PushID("Radius");
    ImGui::InputDouble("", &m_objectAttributes.radius, 1.f, 1.0f, "%.4f");
    ImGui::PopID();
}

void ObjectCreationWindow::RenderObjectDistanceSection()
{
    ImGui::SeparatorText("Object Distance From The Center");
    ImGui::PushID("Distance");
    ImGui::InputDouble("", &m_objectAttributes.distanceFromCenter, 1.f, 1.0f, "%.4f");
    ImGui::PopID();
}

void ObjectCreationWindow::RenderObjectSpeedSection()
{
    ImGui::SeparatorText("Object Speed Around The Center");
    ImGui::PushID("Speed");
    ImGui::InputDouble("", &m_objectAttributes.speed, 1.f, 1.0f, "%.4f");
    ImGui::PopID();
}

void ObjectCreationWindow::RenderObjectTiltSection()
{
    ImGui::SeparatorText("Object Tilt");
    ImGui::PushID("Tilt");
    ImGui::InputDouble("", &m_objectAttributes.tiltDegrees, 1.f, 1.0f, "%.4f");
    ImGui::PopID();
}

void ObjectCreationWindow::RenderObjectCreationSection()
{
    if (ImGui::Button("Create"))
    {
        OnCreateSignal(m_objectAttributes);
        m_planetsCount++;
    }
}

void ObjectCreationWindow::RenderPlanetsTable()
{
    static ImGuiTableFlags flagsPlanetsTable = ImGuiTableFlags_Borders | ImGuiTableFlags_NoHostExtendX;

    ImGui::PushFont(m_customFont);
    if (ImGui::BeginTable("Planet Counter", 2, flagsPlanetsTable))
    {
        ImGui::TableSetupColumn("Parameter", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableSetupColumn("Value", ImGuiTableColumnFlags_WidthFixed);
        ImGui::TableHeadersRow();

        ImGui::TableNextColumn();
        ImGui::Text("Planets");
        ImGui::TableNextColumn();
        ImGui::Text("%d", m_planetsCount);

        ImGui::EndTable();
    }
    ImGui::PopFont();
}

void ObjectCreationWindow::CreateFont(const std::string& fontPath, float fontSize)
{
    std::string executableDir = boost::dll::program_location().parent_path().string();
    ImGuiIO& io = ImGui::GetIO();
    m_customFont = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), fontSize);
}
