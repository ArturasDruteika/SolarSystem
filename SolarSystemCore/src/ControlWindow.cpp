#include "ControlWindow.hpp"
#include "imgui.h"


ControlWindow::ControlWindow()
{
    m_objectAttributes.radius = 1;
    m_objectAttributes.distanceFromCenter = 1;
    m_objectAttributes.speed = 1;
    m_objectAttributes.tiltDegrees = 1;
}

ControlWindow::~ControlWindow() = default;

void ControlWindow::RenderMainWindow()
{
    ImGui::Begin(
        "Simulation Window",
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

    ImGui::PopStyleVar(7);

    ImGui::End();
}

void ControlWindow::RenderObjectRadiusSection()
{
    ImGui::SeparatorText("Object Radius");
    ImGui::PushID("Radius");
    ImGui::InputInt("", &m_objectAttributes.radius);
    ImGui::PopID();
}

void ControlWindow::RenderObjectDistanceSection()
{
    ImGui::SeparatorText("Object Distance From The Center");
    ImGui::PushID("Distance");
    ImGui::InputInt("", &m_objectAttributes.distanceFromCenter);
    ImGui::PopID();
}

void ControlWindow::RenderObjectSpeedSection()
{
    ImGui::SeparatorText("Object Speed Around The Center");
    ImGui::PushID("Speed");
    ImGui::InputInt("", &m_objectAttributes.speed);
    ImGui::PopID();
}

void ControlWindow::RenderObjectTiltSection()
{
    ImGui::SeparatorText("Object Tilt");
    ImGui::PushID("Tilt");
    ImGui::InputInt("", &m_objectAttributes.tiltDegrees);
    ImGui::PopID();
}

void ControlWindow::RenderObjectCreationSection()
{
    ImGui::Button("Create");
}
