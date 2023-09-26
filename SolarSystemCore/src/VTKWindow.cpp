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
    , m_sphere{}
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

void VTKWindow::RenderMainWindow()
{
    static double i = 0.;
    ImGui::SetNextWindowSize(ImVec2(720, 480), ImGuiCond_FirstUseEver);

    ImGui::Begin("Vtk Viewer");

    m_vtkViewerFinal.render();

    ImGui::End();

    ImGui::Render();
}

void VTKWindow::InitializeVtkActors()
{
    m_cube.GenerateObject();
    m_sphere.GenerateObject();
    m_vtkViewer1.addActor(m_cube.GetObjectActor());
    m_vtkViewerFinal.getRenderer()->SetBackground(0, 0, 0);
    m_vtkViewerFinal.addActor(m_cube.GetObjectActor());
}
