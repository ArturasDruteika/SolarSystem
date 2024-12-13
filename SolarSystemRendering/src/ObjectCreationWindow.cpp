#include "ObjectCreationWindow.hpp"
#include "AnglesOperations.hpp"
#include "imgui.h"
#include <boost/dll.hpp>
#include <string>
#include <set>


constexpr float CREATE_BUTTON_DISABLE_TIME = 4.0f;


ObjectCreationWindow::ObjectCreationWindow(const std::string& windowName)
    : GraphicalWindow(windowName)
    , m_planetsAttributesMap{}
    , m_customFont{nullptr}
    , m_isButtonDisabled{ false }
    , m_disableTimer{ CREATE_BUTTON_DISABLE_TIME }
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

void ObjectCreationWindow::OnDeletePlanet(int id)
{
    m_planetsIds = RemoveIntegerFromVector(m_planetsIds, id);
}

void ObjectCreationWindow::InitInternal()
{
    // Font part
    std::string executableDir = boost::dll::program_location().parent_path().string();
    std::string fontPath = executableDir + "//res//fonts//Roboto-Bold.ttf";
    m_customFont = CreateFont(fontPath, 24.f);
}

void ObjectCreationWindow::DeInitInternal()
{
    delete m_customFont;
}

void ObjectCreationWindow::RenderWindowInternal()
{
    RenderObjectRadiusSection();
    RenderSemiMajorAxisSection();
    RenderSemiMinorAxisSection();
    RenderObjectRotationalPeriodSection();
    RenderObjectInclinationSection();
    RenderObjectTiltSection();
    ImGui::Separator();
    RenderObjectCreationSection();
    ImGui::Separator();
    RenderPlanetsTableSection();
    ImGui::Separator();
}

void ObjectCreationWindow::RenderObjectRadiusSection()
{
    RenderObjectAttributeSelectionSection("Radius", "Radius", m_objectAttributes.radius);
}

void ObjectCreationWindow::RenderSemiMajorAxisSection()
{
    RenderObjectAttributeSelectionSection("Semi-major axis (km)", "Semi-major", m_objectAttributes.semiMajorAxis);
}

void ObjectCreationWindow::RenderSemiMinorAxisSection()
{
    RenderObjectAttributeSelectionSection("Semi-minor axis (km)", "Semi-minor", m_objectAttributes.semiMinorAxis);
}

void ObjectCreationWindow::RenderObjectRotationalPeriodSection()
{
    RenderObjectAttributeSelectionSection("Rotational Period (Days)", "RotationalPeriod", m_objectAttributes.rotationalPeriod);
}

void ObjectCreationWindow::RenderObjectInclinationSection()
{
    RenderObjectAttributeSelectionSection("Inclination (Degrees)", "Inclination", m_objectAttributes.inclination);
}

void ObjectCreationWindow::RenderObjectTiltSection()
{
    RenderObjectAttributeSelectionSection("Tilt (Degrees)", "Tilt", m_objectAttributes.tilt);
}

void ObjectCreationWindow::RenderObjectCreationSection()
{
    UpdateDisableTimer(); // Update the timer logic
    static bool isDisabled;
    isDisabled = m_isButtonDisabled;

    if (isDisabled)
    {
        ImGui::BeginDisabled();
    }

    RenderCreateButton();

    if (isDisabled)
    {
        ImGui::EndDisabled();
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
        ImGui::Text("%d", m_planetsIds.size());

        ImGui::EndTable();
    }
    ImGui::PopFont();
}

void ObjectCreationWindow::RenderCreatedPlanetsInfoSection()
{
    static int planetIdToDelete;
    static bool unusedSelectionSection = false;
    static std::string sectionName = "PlanetToDelete";
}

void ObjectCreationWindow::RenderCreateButton()
{
    if (ImGui::Button("Create", ImVec2(250, 20)) && !m_isButtonDisabled)
    {
        CreatePlanet();
    }
}

void ObjectCreationWindow::SetInitialValues()
{
    m_objectAttributes.radius = 0.5;
    m_objectAttributes.mass = 0.0;
    m_objectAttributes.semiMajorAxis = 10.0;
    m_objectAttributes.semiMinorAxis = 8.0;
    m_objectAttributes.rotationalPeriod = 1.0;
    m_objectAttributes.inclination = 0.0;
    m_objectAttributes.tilt = 0.0;
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

void ObjectCreationWindow::ReplaceDegreesToRadians(StellarSystem::PlanetAttributes& planetAttributes)
{
    planetAttributes.inclination = AnglesOperations::Deg2Rad(planetAttributes.inclination);
}

StellarSystem::PlanetAttributes ObjectCreationWindow::ProcessPlanetAttributes(const StellarSystem::PlanetAttributes& objectAttributes)
{
    StellarSystem::PlanetAttributes planetAttributesProcessed = objectAttributes;
    ReplaceDegreesToRadians(planetAttributesProcessed);
    return planetAttributesProcessed;
}

int ObjectCreationWindow::GetNextAvailableNumber(const std::vector<int>& values)
{
    // Create a copy of the input vector and sort it
    std::vector<int> sortedValues = values;
    std::sort(sortedValues.begin(), sortedValues.end());

    // Find the smallest non-negative integer not in the sorted vector
    int nextAvailable = 0;
    for (int value : sortedValues) 
    {
        if (value < nextAvailable) 
        {
            // Ignore negative values or duplicates
            continue;
        }
        if (value != nextAvailable) 
        {
            break;
        }
        ++nextAvailable;
    }

    return nextAvailable;
}

std::vector<int> ObjectCreationWindow::RemoveIntegerFromVector(const std::vector<int>& inputVector, int numberToRemove)
{
    std::vector<int> result;
    for (int value : inputVector) 
    {
        if (value != numberToRemove) 
        {
            result.push_back(value);
        }
    }
    return result;
}

void ObjectCreationWindow::UpdateDisableTimer()
{
    if (m_isButtonDisabled)
    {
        m_disableTimer -= ImGui::GetIO().DeltaTime; // Decrease timer based on frame time
        if (m_disableTimer <= 0.0f)
        {
            m_isButtonDisabled = false; // Re-enable the button after the timer ends
        }
    }
}

void ObjectCreationWindow::StartDisableTimer()
{
    m_disableTimer = CREATE_BUTTON_DISABLE_TIME; // Set timer to 4 seconds
    m_isButtonDisabled = true;
}

void ObjectCreationWindow::CreatePlanet()
{
    int nextAvailableNumber = GetNextAvailableNumber(m_planetsIds);
    m_planetsIds.push_back(nextAvailableNumber);
    StellarSystem::PlanetAttributes planetAttributesProcessed = ProcessPlanetAttributes(m_objectAttributes);
    OnCreateSignal(nextAvailableNumber, planetAttributesProcessed);
    m_planetsAttributesMap.insert({ nextAvailableNumber, m_objectAttributes });

    StartDisableTimer(); // Start the disable timer
}
