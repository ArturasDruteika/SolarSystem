#include "ObjectsInfoWindow.hpp"
#include <boost/dll.hpp>


ObjectsInfoWindow::ObjectsInfoWindow()
    : m_customFont{ nullptr }
    , m_planetsAttributesMap{}
    , m_nStyleVars{0}
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

void ObjectsInfoWindow::AddPlanetRecord(int id, const ObjectAttributes& objectAttributes)
{
    m_planetsAttributesMap.insert({ id, objectAttributes });
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

void ObjectsInfoWindow::RenderMainWindowInternal()
{
    RenderPlanetsInfoTable();
}

void ObjectsInfoWindow::RenderPlanetsInfoTable()
{
    ImGui::SeparatorText("Planets Table");

    static ImGuiTableFlags flagsPlanetsTable = ImGuiTableFlags_Borders | ImGuiTableFlags_NoHostExtendX;
    static std::vector<std::string> tableColumnNames = {
        "Planet Number", 
        "Radius (Km)",
        "Distance From Earth (Km)",
        "Speed (Km / h)",
        "Tilt Degrees (Deg)",
        ""
    };

    ImGui::PushFont(m_customFont);

    if (ImGui::BeginTable("Planets Info", tableColumnNames.size(), flagsPlanetsTable))
    {
        for (std::string& columnName : tableColumnNames)
        {
            ImGui::TableSetupColumn(columnName.c_str(), ImGuiTableColumnFlags_WidthFixed);
        }
        ImGui::TableHeadersRow();

        for (auto& [planetId, objectAttributes] : m_planetsAttributesMap)
        {
            ImGui::TableNextColumn();
            ImGui::Text("%d", planetId);
            ImGui::TableNextColumn();
            ImGui::Text("%.5f", objectAttributes.radius);
            ImGui::TableNextColumn();
            ImGui::Text("%.5f", objectAttributes.distanceFromCenter);
            ImGui::TableNextColumn();
            ImGui::Text("%.5f", objectAttributes.speed);
            ImGui::TableNextColumn();
            ImGui::Text("%.5f", objectAttributes.tiltRadians);
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
        m_planetsAttributesMap.erase(buttonId);
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