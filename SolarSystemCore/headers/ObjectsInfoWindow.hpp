#ifndef OBJECTSINFOWINDOW_H
#define OBJECTSINFOWINDOW_H


#include "imgui.h"
#include <string>


class ObjectsInfoWindow
{
public:
    ObjectsInfoWindow();
    ~ObjectsInfoWindow();

    void Init();
    void DeInit();

    void RenderMainWindow();

private:
    void InitInternal();
    void CreateFont(const std::string& fontPath, float fontSize);

    ImFont* m_customFont;
};


#endif //OBJECTSINFOWINDOW_H
