#ifndef OBJECTSINFOWINDOW_H
#define OBJECTSINFOWINDOW_H


#include "GraphicalWindow.hpp"
#include "ObjectsComponents.hpp"
#include "imgui.h"
#include "boost/signals2.hpp"
#include <string>
#include <map>


typedef boost::signals2::signal<void(int id)> DeletePlanetSignal;


class ObjectsInfoWindow : public GraphicalWindow
{
public:
    ObjectsInfoWindow();
    ~ObjectsInfoWindow();

    void Init() override;
    void DeInit() override;

    void AddPlanetRecord(int id, const PlanetAttributes& objectAttributes);
    DeletePlanetSignal OnDeleteRecord;

private:
    void InitInternal() override;
    void DeInitInternal() override;
    void RenderMainWindowInternal() override;

    void RenderPlanetsInfoTable();
    bool RenderDeleteButtonOnTable(int buttonId);

    std::map<int, PlanetAttributes> m_planetsAttributesMap;
    ImFont* m_customFont;
    int m_nStyleVars;
};


#endif //OBJECTSINFOWINDOW_H
