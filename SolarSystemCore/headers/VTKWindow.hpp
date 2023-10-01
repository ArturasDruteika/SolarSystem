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
    void AddPlanet(ObjectAttributes objectAttributes);

    bool m_isVtkOpen;
    Cube m_cube;
    Sphere m_sphere;
    VtkViewer m_vtkViewer1;
    VtkViewer m_vtkViewerFinal;
    std::vector<Planet> m_planetsVec;
    ObjectCreationWindow* m_pObjectCreationWindow;
    SolarSystemModel m_solarSystemModel;
};


#endif //VTKWINDOW_HPP
