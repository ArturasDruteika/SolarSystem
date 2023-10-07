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

void ObjectCreationWindow::DeInit()
{
    DeInitInternal();
}

void ObjectCreationWindow::InitInternal()
{
    m_pObjectsInfoWindow->OnDeleteRecord.connect(
        boost::bind(
            &ObjectCreationWindow::OnDeletePlanet,
            this,
            boost::placeholders::_1
        )
    );

    // Font part
    std::string executableDir = boost::dll::program_location().parent_path().string();
    std::string fontPath = executableDir + "//res//fonts//Roboto-Bold.ttf";
    m_customFont = CreateFont(fontPath, 24.f);
}

void ObjectCreationWindow::DeInitInternal()
{
    delete m_pObjectsInfoWindow;
    delete m_customFont;
}

void ObjectCreationWindow::RenderMainWindowInternal()
{
    RenderObjectRadiusSection();
    RenderObjectDistanceSection();
    RenderObjectSpeedSection();
    RenderObjectTiltSection();
    ImGui::Separator();
    RenderObjectCreationSection();
    ImGui::Separator();
    RenderPlanetsTableSection();
    ImGui::Separator();
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

void ObjectCreationWindow::OnDeletePlanet(int id)
{
    m_planetsCount--;
}
