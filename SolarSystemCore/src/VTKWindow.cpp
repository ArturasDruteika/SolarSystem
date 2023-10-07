#include "VTKWindow.hpp"
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkTransform.h>
#include "spdlog/spdlog.h"


VTKWindow::VTKWindow(ObjectCreationWindow* pObjectCreationWindow)
    : m_cube{}
    , m_sphere{}
    , m_isVtkOpen{true}
    , m_pObjectCreationWindow{ pObjectCreationWindow }
    , m_solarSystemModel{}
    , m_planetsRotationCoords{}
    , m_planetsMap{}
{
}

VTKWindow::~VTKWindow()
{
}

int VTKWindow::Init()
{
    m_pObjectCreationWindow->OnCreateSignal.connect(
        boost::bind(
            &VTKWindow::OnNewPlanet,
            this,
            boost::placeholders::_1,
            boost::placeholders::_2
        )
    );

	return 0;
}

void VTKWindow::DeInit()
{
}

void VTKWindow::RenderMainWindow()
{
    static int i = 0;
    if (i == 9000) { i = 0; }

    ImGui::Begin("Vtk Viewer");

    for (auto& [planetID, planet] : m_planetsMap)
    {
        double x = m_planetsRotationCoords.at(planetID)[i].first;
        double y = m_planetsRotationCoords.at(planetID)[i].second;
        planet.MovePlanet(x, y, 0);
    }
    i++;

    m_vtkViewer.render();

    ImGui::End();
}

void VTKWindow::InitializeVtkActors()
{
    m_cube.GenerateObject(1.5);
    m_vtkViewer.getRenderer()->SetBackground(0, 0, 0);
    m_vtkViewer.addActor(m_cube.GetObjectActor());
}

void VTKWindow::AddVTKActor(const vtkSmartPointer<vtkActor>& actor)
{
    m_vtkViewer.addActor(actor);
}

void VTKWindow::OnNewPlanet(int id, ObjectAttributes objectAttributes)
{
    m_solarSystemModel.OnNewPlanet(id, objectAttributes);
    m_planetsRotationCoords = m_solarSystemModel.GetPlanetsRotationCoords();
    AddVTKActor(m_solarSystemModel.GetPlanetsMap().at(id).GetPlanetActor());
    m_planetsMap = m_solarSystemModel.GetPlanetsMap();
}
