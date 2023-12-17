#ifndef VTKWINDOW_HPP
#define VTKWINDOW_HPP


#include "GraphicalWindow.hpp"
#include "VtkViewer.h"
#include "Planet.hpp"
#include "ObjectCreationWindow.hpp"
#include "ObjectsInfoWindow.hpp"
#include "ObjectsComponents.hpp"
#include "SolarSystemModel.hpp"
#include "vtkSmartPointer.h"
#include <vector>


class VTKWindow : public GraphicalWindow
{
public:
    VTKWindow();
    ~VTKWindow();

    void Init() override;
    void DeInit() override;

    void SetUpWindowPointers(ObjectCreationWindow* pObjectCreationWindow, ObjectsInfoWindow* pObjectInfoWindow);
    void InitializeVtkActors();

private:
    void InitInternal() override;
    void DeInitInternal() override;
    void RenderMainWindowInternal() override;

    void AddVTKActor(const vtkSmartPointer<vtkActor>& actor);
    void RemoveVTKActor(const vtkSmartPointer<vtkActor>& actor);
    void OnNewPlanet(int id, PlanetAttributes objectAttributes);
    void OnDeletePlanet(int planetId);

    bool m_isVtkOpen;
    VtkViewer m_vtkViewer;
    ObjectCreationWindow* m_pObjectCreationWindow;
    ObjectsInfoWindow* m_pObjectInfoWindow;
    SolarSystemModel m_solarSystemModel;
    std::map<int, Planet> m_planetsMap;
    std::map<int, std::vector<std::vector<double>>> m_planetsRotationCoords;
};


#endif //VTKWINDOW_HPP
