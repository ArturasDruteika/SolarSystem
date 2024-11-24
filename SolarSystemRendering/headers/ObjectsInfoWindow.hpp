#ifndef OBJECTSINFOWINDOW_H
#define OBJECTSINFOWINDOW_H


#include "GraphicalWindow.hpp"
#include "ObjectsComponents.hpp"
#include "SolarSystemModel.hpp"
#include "imgui.h"
#include "boost/signals2.hpp"
#include <string>
#include <map>


typedef boost::signals2::signal<void(int id)> DeletePlanetSignal;


class ObjectsInfoWindow : public GraphicalWindow
{
public:
    ObjectsInfoWindow(const std::string& windowName);
    ~ObjectsInfoWindow();

    void Init() override;
    void DeInit() override;

    DeletePlanetSignal OnDeleteRecord;

private:
    void InitInternal() override;
    void DeInitInternal() override;
    void RenderWindowInternal() override;

    void RenderPlanetsInfoTable();
    bool RenderDeleteButtonOnTable(int buttonId);

    ImFont* m_customFont;
    int m_nStyleVars;
    SolarSystemModel& m_solarSystemModel;
};


#endif //OBJECTSINFOWINDOW_H
