#include "VTKWindow.hpp"
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include "spdlog/spdlog.h"



VTKWindow::VTKWindow()
    : m_isVtkOpen{ true }
    , m_pObjectCreationWindow{ nullptr }
    , m_pObjectInfoWindow{ nullptr }
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

void VTKWindow::SetUpWindowPointers(ObjectCreationWindow* pObjectCreationWindow, ObjectsInfoWindow* pObjectInfoWindow)
{
    m_pObjectCreationWindow = pObjectCreationWindow;
    m_pObjectInfoWindow = pObjectInfoWindow;
}

void VTKWindow::InitializeVtkActors()
{
    m_solarSystemVTKInteractor.AddStar(0, 2.0);
    m_vtkViewer.GetRenderer()->SetBackground(0, 0, 0);
    m_vtkViewer.AddActor(m_solarSystemVTKInteractor.GetStarsSpheresMap().at(0).GetObjectActor());
}

void VTKWindow::InitInternal()
{
    SetUpObserverSubscribers();
    SetUpCamera();
}

void VTKWindow::DeInitInternal()
{
    delete m_pObjectCreationWindow;
    delete m_pObjectInfoWindow;
    m_pObjectCreationWindow = nullptr;
    m_pObjectInfoWindow = nullptr;
}

void VTKWindow::RenderMainWindowInternal()
{
    m_solarSystemVTKInteractor.Step();
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

void VTKWindow::SetUpObserverSubscribers()
{
    m_pObjectCreationWindow->OnCreateSignal.connect(
        boost::bind(
            &VTKWindow::OnNewPlanet,
            this,
            boost::placeholders::_1,
            boost::placeholders::_2
        )
    );

    m_pObjectInfoWindow->OnDeleteRecord.connect(
        boost::bind(
            &VTKWindow::OnDeletePlanet,
            this,
            boost::placeholders::_1
        )
    );
}

void VTKWindow::SetUpCamera()
{
    m_camera = vtkSmartPointer<vtkCamera>::New();
    m_camera->Elevation(270);
    m_vtkViewer.GetRenderer()->SetActiveCamera(m_camera);
}


