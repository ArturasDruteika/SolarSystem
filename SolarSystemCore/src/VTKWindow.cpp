#include "VTKWindow.hpp"
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkTransform.h>
#include "spdlog/spdlog.h"
#include <vtkAxesActor.h>
#include <vtkOrientationMarkerWidget.h>


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
    m_camOrientManipulator = vtkSmartPointer<vtkCameraOrientationWidget>::New();
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

    if (!m_vtkViewer.getRenderer()) 
    {
        std::cerr << "Error: Renderer is not initialized." << std::endl;
        // Handle the error or return from the function
    }

    m_vtkViewer.addActor(m_cube.GetObjectActor());
    m_xyzArrows.AddOrientationArrowsOnRenderer(m_vtkViewer.getRenderer(), m_camOrientManipulator);
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
    m_pObjectCreationWindow = nullptr;
    m_pObjectInfoWindow = nullptr;
}

void VTKWindow::RenderMainWindowInternal()
{
    /*if (m_planetsRotationCoords.size() > 0)
    {
        static int i = 0;
        if (i == 9000) { i = 0; }

        for (auto& [planetID, planet] : m_planetsMap)
        {
            m_solarSystemModel.MovePlanet(planetID, i);
        }

        spdlog::info("a {};", i);

        i++;
    }*/
    

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


