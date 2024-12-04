#include "VTKWindow.hpp"
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include "spdlog/spdlog.h"



VTKWindow::VTKWindow(const std::string& windowName)
    : GraphicalWindow(windowName)
    , m_isVtkOpen{ true }
    , m_solarSystemVTKInteractor{}
    , m_planetsRotationCoords{}
{
}

VTKWindow::~VTKWindow()
{
}

void VTKWindow::Init()
{
    InitInternal();
}

void VTKWindow::DeInit()
{
    DeInitInternal();
}

void VTKWindow::InitializeVtkActors()
{
    m_solarSystemVTKInteractor.AddStar(0, 2.0);
    m_vtkViewer.GetRenderer()->SetBackground(0, 0, 0);
    m_vtkViewer.AddActor(m_solarSystemVTKInteractor.GetStarsSpheresMap().at(0).GetObjectActor());
}

void VTKWindow::OnNewPlanet(int id, PlanetAttributes objectAttributes)
{
    m_solarSystemVTKInteractor.AddPlanet(id, objectAttributes);
    AddVTKActor(m_solarSystemVTKInteractor.GetPlanetsSpheresMap().at(id).GetObjectActor());
}

void VTKWindow::OnDeletePlanet(int planetId)
{
    RemoveVTKActor(m_solarSystemVTKInteractor.GetPlanetsSpheresMap().at(planetId).GetObjectActor());
    m_solarSystemVTKInteractor.OnDeletePlanet(planetId);
}

void VTKWindow::InitInternal()
{
    SetUpCamera();
}

void VTKWindow::DeInitInternal()
{
}

void VTKWindow::RenderWindowInternal()
{
    m_solarSystemVTKInteractor.Step();

    if (ImGui::Button("Reset To Original View", ImVec2(200, 25)))
    {
        m_vtkViewer.ResetRendererOrientation();
    }

    m_vtkViewer.Render();
}

void VTKWindow::AddVTKActor(const vtkSmartPointer<vtkActor>& actor)
{
    m_vtkViewer.AddActor(actor);
}

void VTKWindow::RemoveVTKActor(const vtkSmartPointer<vtkActor>& actor)
{
    m_vtkViewer.RemoveActor(actor);
}

void VTKWindow::SetUpCamera()
{
    m_camera = vtkSmartPointer<vtkCamera>::New();
    m_camera->Elevation(270);
    m_vtkViewer.GetRenderer()->SetActiveCamera(m_camera);
}


