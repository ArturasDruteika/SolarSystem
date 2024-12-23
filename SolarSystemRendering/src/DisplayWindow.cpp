#include "ControlWindow.hpp"
#include "imgui.h"


ControlWindow::ControlWindow() = default;

ControlWindow::~ControlWindow() = default;

void ControlWindow::RunMainWindow()
{
    ImGui::Begin(
        "Simulation Window",
        nullptr,
        ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse
    );

    ImGui::Button("Click Me!");

    ImGui::End();
}
