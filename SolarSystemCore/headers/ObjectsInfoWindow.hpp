#ifndef OBJECTSINFOWINDOW_H
#define OBJECTSINFOWINDOW_H


#include "ObjectsComponents.hpp"
#include "imgui.h"
#include <string>
#include <map>


class ObjectsInfoWindow
{
public:
    ObjectsInfoWindow();
    ~ObjectsInfoWindow();

    void Init();
    void DeInit();

    void RenderMainWindow();
    void AddPlanetRecord(int id, const ObjectAttributes& objectAttributes);

private:
    void InitInternal();
    void RenderPlanetsInfoTable();
    void CreateFont(const std::string& fontPath, float fontSize);

    std::map<int, ObjectAttributes> m_planetsAttributesMap;
    ImFont* m_customFont;
};


#endif //OBJECTSINFOWINDOW_H
