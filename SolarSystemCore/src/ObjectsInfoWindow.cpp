#include "ObjectsInfoWindow.hpp"
#include <boost/dll.hpp>


ObjectsInfoWindow::ObjectsInfoWindow()
    : m_customFont{ nullptr }
    , m_planetsAttributesMap{}
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

    RenderPlanetsInfoTable();

    ImGui::PopStyleVar(7);

    ImGui::End();
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
    CreateFont(fontPath, 18.f);
}

void ObjectsInfoWindow::RenderPlanetsInfoTable()
{
    ImGui::SeparatorText("Planets table");

    static ImGuiTableFlags flagsPlanetsTable = ImGuiTableFlags_Borders | ImGuiTableFlags_NoHostExtendX;
    static std::vector<std::string> tableColumnNames = {
        "Planet Number", 
        "Radius",
        "Distance From Earth",
        "Speed",
        "Tilt Degrees"
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
            ImGui::Text("%.5f", objectAttributes.tiltDegrees);
        }

        ImGui::EndTable();
    }

    ImGui::PopFont();
}

void ObjectsInfoWindow::CreateFont(const std::string& fontPath, float fontSize)
{
    std::string executableDir = boost::dll::program_location().parent_path().string();
    ImGuiIO& io = ImGui::GetIO();
    m_customFont = io.Fonts->AddFontFromFileTTF(fontPath.c_str(), fontSize);
}
