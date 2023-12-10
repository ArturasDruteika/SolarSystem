#ifndef SOLARSYSTEMCORE_CONTROLWINDOW_HPP
#define SOLARSYSTEMCORE_CONTROLWINDOW_HPP


#include "GraphicalWindow.hpp"
#include "ObjectsInfoWindow.hpp"
#include "ObjectsComponents.hpp"
#include "Planet.hpp"
#include "boost/signals2.hpp"
#include "imgui.h"
#include <map>


typedef boost::signals2::signal<void(int id, const ObjectAttributes& objectAttributes)> CreationSignal;
typedef boost::signals2::signal<void(const int id)> DeleteSignal;


class ObjectCreationWindow : public GraphicalWindow
{
public:
    ObjectCreationWindow(ObjectsInfoWindow* pObjectsInfoWindow);
    ~ObjectCreationWindow();

    void Init() override;
    void DeInit() override;

    CreationSignal OnCreateSignal;
    DeleteSignal OnDeleteSignal;

private:
    void InitInternal() override;
    void DeInitInternal() override;
    void RenderMainWindowInternal() override;

    void RenderObjectRadiusSection();
    void RenderObjectDistanceSection();
    void RenderObjectSpeedSection();
    void RenderObjectTiltSection();
    void RenderObjectCreationSection();
    void RenderPlanetsTableSection();
    void RenderCreatedPlanetsInfoSection();

    void SetInitialValues();
    void RenderObjectAttributeSelectionSection(const std::string& separatorText, const std::string& idText, double& parameterValue);
    void OnDeletePlanet(int id);

    ObjectAttributes m_objectAttributes;
    std::map<int, ObjectAttributes> m_planetsAttributesMap;
    int m_planetsCount;
    ImFont* m_customFont;

    ObjectsInfoWindow* m_pObjectsInfoWindow;
};


#endif //SOLARSYSTEMCORE_CONTROLWINDOW_HPP
