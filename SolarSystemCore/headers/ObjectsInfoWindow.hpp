#ifndef OBJECTSINFOWINDOW_H
#define OBJECTSINFOWINDOW_H


#include "ObjectsComponents.hpp"
#include "imgui.h"
#include "boost/signals2.hpp"
#include <string>
#include <map>


typedef boost::signals2::signal<void()> DeletePlanetSignal;


class ObjectsInfoWindow
{
public:
    ObjectsInfoWindow();
    ~ObjectsInfoWindow();

    void Init();
    void DeInit();

    void RenderMainWindow();
    void AddPlanetRecord(int id, const ObjectAttributes& objectAttributes);
    DeletePlanetSignal OnDeleteRecord;

private:
    void InitInternal();
    void RenderPlanetsInfoTable();
    bool RenderDeleteButtonOnTable(int buttonId);
    void CreateFont(const std::string& fontPath, float fontSize);

    std::map<int, ObjectAttributes> m_planetsAttributesMap;
    ImFont* m_customFont;
};


#endif //OBJECTSINFOWINDOW_H
