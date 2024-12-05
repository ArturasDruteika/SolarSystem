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
    , m_addPlanetThreadRunning{ false }
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

void VTKWindow::OnNewPlanet(int id, const PlanetAttributes& objectAttributes)
{
    if (m_addPlanetThreadRunning.exchange(true)) // Ensure only one thread is running
    {
        spdlog::warn("Annotation thread is already running.");
        return;
    }
    m_addPlanetThread = std::jthread(&VTKWindow::SetUpPlanet, this, id, objectAttributes);
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

void VTKWindow::SetUpPlanet(int id, const PlanetAttributes& objectAttributes)
{
    // Post back to the main thread to update GUI
    std::lock_guard<std::mutex> lock(m_guiUpdateMutex); // Use a mutex if necessary
    // Perform the long-running task in this thread
    m_solarSystemVTKInteractor.AddPlanet(id, objectAttributes);
    vtkSmartPointer<vtkActor> actor = m_solarSystemVTKInteractor.GetPlanetsSpheresMap().at(id).GetObjectActor();
    AddVTKActor(actor);

    m_addPlanetThreadRunning = false;
}


