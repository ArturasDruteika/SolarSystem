#ifndef SOLARSYSTEMCORE_CONTROLWINDOW_HPP
#define SOLARSYSTEMCORE_CONTROLWINDOW_HPP


#include "ObjectsComponents.hpp"
#include "Planet.hpp"
#include "boost/signals2.hpp"
#include "imgui.h"


typedef boost::signals2::signal<void(const ObjectAttributes& objectAttributes)> CreationSignal;


class ObjectCreationWindow
{
public:
    ObjectCreationWindow();
    ~ObjectCreationWindow();

    void Init();
    void RenderMainWindow();

    CreationSignal OnCreateSignal;

private:
    void InitInternal();

    void RenderObjectRadiusSection();
    void RenderObjectDistanceSection();
    void RenderObjectSpeedSection();
    void RenderObjectTiltSection();
    void RenderObjectCreationSection();
    void RenderPlanetsTable();

    void CreateFont(const std::string& fontPath, float fontSize);

    ObjectAttributes m_objectAttributes;
    int m_planetsCount;
    ImFont* m_customFont;

};


#endif //SOLARSYSTEMCORE_CONTROLWINDOW_HPP
