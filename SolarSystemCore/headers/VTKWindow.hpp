#ifndef VTKWINDOW_HPP
#define VTKWINDOW_HPP


#include "VtkViewer.h"
#include "Cube.hpp"
#include "Sphere.hpp"
#include "Planet.hpp"
#include "ObjectCreationWindow.hpp"
#include "ObjectsComponents.hpp"
#include "SolarSystemModel.hpp"

#include <vector>


class VTKWindow
{
public:
    VTKWindow(ObjectCreationWindow* pObjectCreationWindow);
    ~VTKWindow();

    int Init();
    void DeInit();

    void RenderMainWindow();
    void InitializeVtkActors();

private:
    void AddVTKActor(const vtkSmartPointer<vtkActor>& actor);
    void OnNewPlanet(int id, ObjectAttributes objectAttributes);

    bool m_isVtkOpen;
    Cube m_cube;
    Sphere m_sphere;
    VtkViewer m_vtkViewer1;
    VtkViewer m_vtkViewer;
    ObjectCreationWindow* m_pObjectCreationWindow;
    SolarSystemModel m_solarSystemModel;
    std::map<int, Planet> m_planetsMap;
    std::map<int, std::vector<std::pair<double, double>>> m_planetsRotationCoords;
};


#endif //VTKWINDOW_HPP
