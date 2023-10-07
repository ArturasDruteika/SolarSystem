#ifndef VTKWINDOW_HPP
#define VTKWINDOW_HPP


#include "VtkViewer.h"
#include "Cube.hpp"
#include "Sphere.hpp"
#include "Planet.hpp"
#include "ObjectCreationWindow.hpp"
#include "ObjectsInfoWindow.hpp"
#include "ObjectsComponents.hpp"
#include "SolarSystemModel.hpp"

#include <vector>


class VTKWindow
{
public:
    VTKWindow();
    ~VTKWindow();

    int Init();
    void DeInit();
    void SetUpWindowPointer(ObjectCreationWindow* pObjectCreationWindow, ObjectsInfoWindow* pObjectInfoWindow);

    void RenderMainWindow();
    void InitializeVtkActors();

private:
    void InitInternal();
    void AddVTKActor(const vtkSmartPointer<vtkActor>& actor);
    void RemoveVTKActor(const vtkSmartPointer<vtkActor>& actor);
    void OnNewPlanet(int id, ObjectAttributes objectAttributes);
    void OnDeletePlanet(int planetID);

    bool m_isVtkOpen;
    Cube m_cube;
    Sphere m_sphere;
    VtkViewer m_vtkViewer;
    ObjectCreationWindow* m_pObjectCreationWindow;
    ObjectsInfoWindow* m_pObjectInfoWindow;
    SolarSystemModel m_solarSystemModel;
    std::map<int, Planet> m_planetsMap;
    std::map<int, std::vector<std::pair<double, double>>> m_planetsRotationCoords;
};


#endif //VTKWINDOW_HPP
