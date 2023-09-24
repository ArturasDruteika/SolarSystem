#include "VTKWindow.hpp"
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkTransform.h>
#include "spdlog/spdlog.h"


VTKWindow::VTKWindow()
    : m_cube{}
    , m_isVtkOpen{true}
    , m_cubeActor{}
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
    static double i = 0.;
    ImGui::SetNextWindowSize(ImVec2(720, 480), ImGuiCond_FirstUseEver);
    if (m_isVtkOpen)
    {
        ImGui::Begin("Vtk Viewer", &m_isVtkOpen, VtkViewer::NoScrollFlags());

        auto renderer = m_vtkViewerFinal.getRenderer();
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

        m_vtkViewerFinal.render();

        m_cube.MoveActor(m_cubeActor, 0.00001 * double(i), 0.000001 * double(i), 0.000001 * double(i));
        i++;

        ImGui::End();
    }

    ImGui::Render();
}

void VTKWindow::InitializeVtkActors()
{
    m_cubeActor = m_cube.GenerateCube();
    m_vtkViewer1.addActor(m_cubeActor);
    m_vtkViewerFinal.getRenderer()->SetBackground(0, 0, 0); // Black background
    m_vtkViewerFinal.addActor(m_cubeActor);
}
