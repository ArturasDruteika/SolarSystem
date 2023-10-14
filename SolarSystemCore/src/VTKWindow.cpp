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
    , m_pObjectCreationWindow{nullptr}
    , m_pObjectInfoWindow{nullptr}
    , m_solarSystemModel{}
    , m_planetsRotationCoords{}
    , m_planetsMap{}
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
    m_cube.GenerateObject(1.5);
    m_vtkViewer.getRenderer()->SetBackground(0, 0, 0);
    m_vtkViewer.addActor(m_cube.GetObjectActor());
}

void VTKWindow::InitInternal()
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

void VTKWindow::DeInitInternal()
{
    delete m_pObjectCreationWindow;
    delete m_pObjectInfoWindow;
}

void VTKWindow::RenderMainWindowInternal()
{
    static int i = 0;
    if (i == 9000) { i = 0; }

    for (auto& [planetID, planet] : m_planetsMap)
    {
        double x = m_planetsRotationCoords.at(planetID)[i][0];
        double y = m_planetsRotationCoords.at(planetID)[i][1];
        double z = m_planetsRotationCoords.at(planetID)[i][2];
        planet.MovePlanet(x, y, z);
    }
    i++;

    m_vtkViewer.render();
}

void VTKWindow::AddVTKActor(const vtkSmartPointer<vtkActor>& actor)
{
    m_vtkViewer.addActor(actor);
}

void VTKWindow::RemoveVTKActor(const vtkSmartPointer<vtkActor>& actor)
{
    m_vtkViewer.removeActor(actor);
}

void VTKWindow::OnNewPlanet(int id, ObjectAttributes objectAttributes)
{
    m_solarSystemModel.AddPlanet(id, objectAttributes);
    m_planetsRotationCoords = m_solarSystemModel.GetPlanetsRotationCoords(0);
    m_planetsMap = m_solarSystemModel.GetPlanetsMap();

    AddVTKActor(m_solarSystemModel.GetPlanetsMap().at(id).GetPlanetActor());
}

void VTKWindow::OnDeletePlanet(int planetID)
{
    RemoveVTKActor(m_solarSystemModel.GetPlanetsMap().at(planetID).GetPlanetActor());

    m_solarSystemModel.OnDeletePlanet(planetID);
    m_planetsRotationCoords = m_solarSystemModel.GetPlanetsRotationCoords(0);
    m_planetsMap = m_solarSystemModel.GetPlanetsMap();
}
