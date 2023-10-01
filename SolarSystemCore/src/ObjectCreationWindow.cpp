#include "ObjectCreationWindow.hpp"
#include "imgui.h"


ObjectCreationWindow::ObjectCreationWindow()
{
    m_objectAttributes.radius = 1;
    m_objectAttributes.distanceFromCenter = 1;
    m_objectAttributes.speed = 1;
    m_objectAttributes.tiltDegrees = 1;
}

ObjectCreationWindow::~ObjectCreationWindow() = default;

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

    ImGui::PopStyleVar(7);

    ImGui::End();
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
    }
}
