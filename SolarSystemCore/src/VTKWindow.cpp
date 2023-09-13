#include "cube.hpp"
#include "VTKWindow.hpp"
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>


VTKWindow::VTKWindow()
    : m_cube{}
    , m_isVtkOpen{true}
{
}

VTKWindow::~VTKWindow()
{
}

int VTKWindow::Init()
{
	return 0;
}

void VTKWindow::DeInit()
{
}

void VTKWindow::RunMainWindow()
{
    ImGui::SetNextWindowSize(ImVec2(720, 480), ImGuiCond_FirstUseEver);
    if (m_isVtkOpen)
    {
        ImGui::Begin("Vtk Viewer 2", &m_isVtkOpen, VtkViewer::NoScrollFlags());

        auto renderer = m_vtkViewer2.getRenderer();
        if (ImGui::Button("VTK Background: Black"))
        {
            renderer->SetBackground(0, 0, 0);
        }
        ImGui::SameLine();
        if (ImGui::Button("VTK Background: Red"))
        {
            renderer->SetBackground(1, 0, 0);
        }
        ImGui::SameLine();
        if (ImGui::Button("VTK Background: Green"))
        {
            renderer->SetBackground(0, 1, 0);
        }
        ImGui::SameLine();
        if (ImGui::Button("VTK Background: Blue"))
        {
            renderer->SetBackground(0, 0, 1);
        }
        static float vtk2BkgAlpha = 0.2f;
        ImGui::SliderFloat("Background Alpha", &vtk2BkgAlpha, 0.0f, 1.0f);
        renderer->SetBackgroundAlpha(vtk2BkgAlpha);

        m_vtkViewer2.render();

        ImGui::End();
    }

    ImGui::Render();
}

void VTKWindow::InitializeVtkActors()
{
    vtkNew<vtkActor> actor = m_cube.ReadSTLFIle("C:/Users/artur/C++Projects/solar_system/SolarSystem_build/Debug/trappist1_h_1_25_10_7.stl");
    m_vtkViewer1.addActor(actor);
    m_vtkViewer2.getRenderer()->SetBackground(0, 0, 0); // Black background
    m_vtkViewer2.addActor(actor);
}
