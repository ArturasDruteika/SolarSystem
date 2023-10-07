#include "ObjectCreationWindow.hpp"
#include "imgui.h"
#include <boost/dll.hpp>
#include <string>


ObjectCreationWindow::ObjectCreationWindow(ObjectsInfoWindow* pObjectsInfoWindow)
    : m_planetsAttributesMap{}
    , m_planetsCount{0}
    , m_customFont{nullptr}
    , m_pObjectsInfoWindow{ pObjectsInfoWindow }
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
    RenderPlanetsTableSection();
    ImGui::Separator();

    ImGui::PopStyleVar(7);

    ImGui::End();
}

void ObjectCreationWindow::InitInternal()
{
    m_pObjectsInfoWindow->OnDeleteRecord.connect(
        boost::bind(
            &ObjectCreationWindow::DecrementPlanetsCount,
            this
        )
    );

    // Font part
    std::string executableDir = boost::dll::program_location().parent_path().string();
    std::string fontPath = executableDir + "//res//fonts//Roboto-Bold.ttf";
    CreateFont(fontPath, 24.f);
}

void ObjectCreationWindow::RenderObjectRadiusSection()
{
    RenderObjectAttributeSelectionSection("Object's Radius", "Radius", m_objectAttributes.radius);
}

void ObjectCreationWindow::RenderObjectDistanceSection()
{
    RenderObjectAttributeSelectionSection("Object's Distance From The Center", "Distance", m_objectAttributes.distanceFromCenter);
}

void ObjectCreationWindow::RenderObjectSpeedSection()
{
    RenderObjectAttributeSelectionSection("Object's Speed Around The Center", "Speed", m_objectAttributes.speed);
}

void ObjectCreationWindow::RenderObjectTiltSection()
{
    RenderObjectAttributeSelectionSection("Object's Tilt", "Tilt", m_objectAttributes.tiltDegrees);
}

void ObjectCreationWindow::RenderObjectCreationSection()
{
    if (ImGui::Button("Create", ImVec2(250, 20)))
    {
        OnCreateSignal(m_planetsCount, m_objectAttributes);
        m_planetsAttributesMap.insert({ m_planetsCount, m_objectAttributes });
        m_pObjectsInfoWindow->AddPlanetRecord(m_planetsCount, m_objectAttributes);
        m_planetsCount++;
    }
}

void ObjectCreationWindow::RenderPlanetsTableSection()
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

void ObjectCreationWindow::RenderCreatedPlanetsInfoSection()
{
    static int planetIDToDelete;
    static bool unusedSelectionSection = false;
    static std::string sectionName = "PlanetToDelete";
}

void ObjectCreationWindow::RenderObjectAttributeSelectionSection(const std::string& separatorText, const std::string& idText, double& parameterValue)
{
    ImGui::PushItemWidth(250);
    ImGui::SeparatorText(separatorText.c_str());
    ImGui::PushID(idText.c_str());
    ImGui::InputDouble("", &parameterValue, 1.f, 1.0f, "%.4f");
    ImGui::PopID();
    ImGui::PopItemWidth();
}

void ObjectCreationWindow::CreateFont(const std::string& fontPath, float fontSize)
{
    std::string executableDir = boost::dll::program_location().parent_path().string();
    ImGuiIO& io = ImGui::GetIO();
    m_customFont = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), fontSize);
}

void ObjectCreationWindow::DecrementPlanetsCount()
{
    m_planetsCount--;
}
