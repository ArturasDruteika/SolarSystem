#ifndef VTKWINDOW_HPP
#define VTKWINDOW_HPP


#include "GraphicalWindow.hpp"
#include "VtkViewer.h"
#include "Planet.hpp"
#include "ObjectCreationWindow.hpp"
#include "ObjectsInfoWindow.hpp"
#include "ObjectsComponents.hpp"
#include "SolarSystemVTKInteractor.hpp"
#include "vtkSmartPointer.h"
#include "vtkCamera.h"
#include <vector>
#include <unordered_map>


class VTKWindow : public GraphicalWindow
{
public:
    VTKWindow(const std::string& windowName);
    ~VTKWindow();

    void Init() override;
    void DeInit() override;

    void SetUpWindowPointers(ObjectCreationWindow* pObjectCreationWindow, ObjectsInfoWindow* pObjectInfoWindow);
    void InitializeVtkActors();

private:
    void InitInternal() override;
    void DeInitInternal() override;
    void RenderWindowInternal() override;

    void AddVTKActor(const vtkSmartPointer<vtkActor>& actor);
    void RemoveVTKActor(const vtkSmartPointer<vtkActor>& actor);
    void OnNewPlanet(int id, PlanetAttributes objectAttributes);
    void OnDeletePlanet(int planetId);
    void SetUpObserverSubscribers();
    void SetUpCamera();

    bool m_isVtkOpen;
    vtkSmartPointer<vtkCamera> m_camera;
    VtkViewer m_vtkViewer;
    ObjectCreationWindow* m_pObjectCreationWindow;
    ObjectsInfoWindow* m_pObjectInfoWindow;
    std::unordered_map<int, std::vector<std::vector<double>>> m_planetsRotationCoords;
    SolarSystemVTKInteractor m_solarSystemVTKInteractor;
};


#endif //VTKWINDOW_HPP
