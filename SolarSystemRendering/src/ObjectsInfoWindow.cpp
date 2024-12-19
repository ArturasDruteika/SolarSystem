#include "ObjectsInfoWindow.hpp"
#include "PhysicalConstants.hpp"
#include <boost/dll.hpp>


ObjectsInfoWindow::ObjectsInfoWindow(const std::string& windowName)
    : GraphicalWindow(windowName)
    , m_customFont{ nullptr }
    , m_nStyleVars{ 0 }
    , m_solarSystemModel{ StellarSystem::SolarSystemModel::GetInstance() }
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
    DeInitInternal();
}

void ObjectsInfoWindow::InitInternal()
{
    // Font part
    std::string executableDir = boost::dll::program_location().parent_path().string();
    std::string fontPath = executableDir + "//res//fonts//Roboto-Bold.ttf";
    m_customFont = CreateFont(fontPath, 18.f);
}

void ObjectsInfoWindow::DeInitInternal()
{
    delete m_customFont;
}

void ObjectsInfoWindow::RenderWindowInternal()
{
    RenderPlanetsInfoTable();
}

void ObjectsInfoWindow::RenderPlanetsInfoTable()
{
    ImGui::SeparatorText("Planets Table");

    static ImGuiTableFlags flagsPlanetsTable = ImGuiTableFlags_Borders | ImGuiTableFlags_NoHostExtendX;
    static std::vector<std::string> tableColumnNames =
    {
        "Planet Number",
        "Radius (km)",
        "Aphelion (mln km)",
        "Perihelion (mln km)",
        "Eccentricity",
        "Speed (km / h)",
        "Rotational Period (Days)",
        "Inclination (Deg)",
        "Tilt (Deg)",
        "Delete Planet (?)"
    };

    ImGui::PushFont(m_customFont);

    static std::unordered_map<int, StellarSystem::Planet> planetsMap;
    planetsMap = m_solarSystemModel.GetPlanetsMap();

    if (ImGui::BeginTable("Planets Info", tableColumnNames.size(), flagsPlanetsTable))
    {
        for (std::string& columnName : tableColumnNames)
        {
            ImGui::TableSetupColumn(columnName.c_str(), ImGuiTableColumnFlags_WidthFixed);
        }
        ImGui::TableHeadersRow();

        for (const auto& [planetId, planet] : planetsMap)
        {
            ImGui::TableNextColumn();
            ImGui::Text("%d", planetId);
            ImGui::TableNextColumn();
            ImGui::Text("%.2f", planet.GetRadius());
            ImGui::TableNextColumn();
            ImGui::Text("%.2f", planet.GetAphelion() / StellarSystem::DISTANCE_MULTIPLIER);
            ImGui::TableNextColumn();
            ImGui::Text("%.2f", planet.GetPerihelion() / StellarSystem::DISTANCE_MULTIPLIER);
            ImGui::TableNextColumn();
            ImGui::Text("%.4f", planet.GetEccentricity());
            ImGui::TableNextColumn();
            ImGui::Text("%.2f", planet.GetCurrentSpeed() / Physics::KM);
            ImGui::TableNextColumn();
            ImGui::Text("%.2f", planet.GetRotationalPeriod());
            ImGui::TableNextColumn();
            ImGui::Text("%.2f", planet.GetInclination());
            ImGui::TableNextColumn();
            ImGui::Text("%.2f", planet.GetTilt());
            ImGui::TableNextColumn();
            if (RenderDeleteButtonOnTable(planetId))
            {
                break;
            }
        }
        ImGui::EndTable();
    }
    ImGui::PopFont();
}

bool ObjectsInfoWindow::RenderDeleteButtonOnTable(int buttonId)
{
    static bool isPressed = false;
    ImGui::PushID(std::to_string(buttonId).c_str());
    if (ImGui::Button("Delete", ImVec2(55, 25)))
    {
        OnDeleteRecord(buttonId);
        isPressed = true;
    }
    else
    {
        isPressed = false;
    }
    ImGui::PopID();
    return isPressed;
}
