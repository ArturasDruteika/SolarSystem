#include "DisplayWindow.hpp"


DisplayWindow::DisplayWindow() = default;

DisplayWindow::~DisplayWindow() = default;

void DisplayWindow::RunMainWindow()
{
    ImGui::Begin(
        "Simulation Window",
        nullptr,
        ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoCollapse
    );

    ImGui::Button("Click Me!");

    ImGui::End();
}
