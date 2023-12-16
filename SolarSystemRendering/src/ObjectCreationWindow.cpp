#include "ObjectCreationWindow.hpp"
#include "AnglesOperations.hpp"
#include "imgui.h"
#include <boost/dll.hpp>
#include <string>


ObjectCreationWindow::ObjectCreationWindow(ObjectsInfoWindow* pObjectsInfoWindow)
    : m_planetsAttributesMap{}
    , m_planetsCount{0}
    , m_customFont{nullptr}
    , m_pObjectsInfoWindow{ pObjectsInfoWindow }
{
    SetInitialValues();
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
    RenderSemiMajorAxisSection();
    RenderSemiMinorAxisSection();
    RenderObjectSpeedSection();
    RenderObjectTiltSection();
    RenderObjectInclinationSection();
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

void ObjectCreationWindow::RenderSemiMajorAxisSection()
{
    RenderObjectAttributeSelectionSection("Semi-major axis (km)", "Semi-major", m_objectAttributes.semiMajorAxis);
}

void ObjectCreationWindow::RenderSemiMinorAxisSection()
{
    RenderObjectAttributeSelectionSection("Semi-minor axis (km)", "Semi-minor", m_objectAttributes.semiMinorAxis);
}

void ObjectCreationWindow::RenderObjectSpeedSection()
{
    RenderObjectAttributeSelectionSection("Object's Speed Around The Center", "Speed", m_objectAttributes.speed);
}

void ObjectCreationWindow::RenderObjectTiltSection()
{
    RenderObjectAttributeSelectionSection("Object's Tilt (Degrees)", "Tilt", m_objectAttributes.tilt);
}

void ObjectCreationWindow::RenderObjectInclinationSection()
{
    RenderObjectAttributeSelectionSection("Object's Inclination (Degrees)", "Inclination", m_objectAttributes.inclination);
}

void ObjectCreationWindow::RenderObjectCreationSection()
{
    if (ImGui::Button("Create", ImVec2(250, 20)))
    {
        PlanetAttributes planetAttributesProcessed = ProcessPlanetAttributes(m_objectAttributes);
        OnCreateSignal(m_planetsCount, planetAttributesProcessed);
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

void ObjectCreationWindow::SetInitialValues()
{
    m_objectAttributes.radius = 0.5;
    m_objectAttributes.semiMajorAxis = 10.0;
    m_objectAttributes.semiMinorAxis = 8.0;
    m_objectAttributes.speed = 1;
    m_objectAttributes.tilt = 0;
    m_objectAttributes.inclination = 0;
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

void ObjectCreationWindow::ReplaceDegreesToRadians(PlanetAttributes& planetAttributes)
{
    planetAttributes.tilt = AnglesOperations::Deg2Rad(planetAttributes.tilt);
    planetAttributes.inclination = AnglesOperations::Deg2Rad(planetAttributes.inclination);
}

PlanetAttributes ObjectCreationWindow::ProcessPlanetAttributes(const PlanetAttributes& objectAttributes)
{
    PlanetAttributes planetAttributesProcessed = objectAttributes;
    ReplaceDegreesToRadians(planetAttributesProcessed);
    return planetAttributesProcessed;
}
