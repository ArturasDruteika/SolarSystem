#ifndef VTKWINDOW_HPP
#define VTKWINDOW_HPP


#include "GraphicalWindow.hpp"
#include "VtkViewer.h"
#include "Planet.hpp"
#include "ObjectsComponents.hpp"
#include "SolarSystemVTKInteractor.hpp"
#include "vtkSmartPointer.h"
#include "vtkCamera.h"
#include <vector>
#include <unordered_map>
#include <mutex>
#include <thread>
#include <atomic>


class VTKWindow : public GraphicalWindow
{
public:
    VTKWindow(const std::string& windowName);
    ~VTKWindow();

    void Init() override;
    void DeInit() override;

    void InitializeVtkActors();
    void OnNewPlanet(int id, const StellarSystem::PlanetAttributes& objectAttributes);
    void OnDeletePlanet(int planetId);

private:
    void InitInternal() override;
    void DeInitInternal() override;
    void RenderWindowInternal() override;

    void AddVTKActor(const vtkSmartPointer<vtkActor>& actor);
    void RemoveVTKActor(const vtkSmartPointer<vtkActor>& actor);
    void SetUpCamera();
    void SetUpPlanet(int id, const StellarSystem::PlanetAttributes& objectAttributes);

    bool m_isVtkOpen;
    std::mutex m_guiUpdateMutex;
    std::jthread m_addPlanetThread;
    std::atomic<bool> m_addPlanetThreadRunning;
    vtkSmartPointer<vtkCamera> m_camera;
    VtkViewer m_vtkViewer;
    std::unordered_map<int, std::vector<std::vector<double>>> m_planetsRotationCoords;
    SolarSystemVTKInteractor m_solarSystemVTKInteractor;
};


#endif //VTKWINDOW_HPP
