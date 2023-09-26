#ifndef SOLARSYSTEMCORE_CONTROLWINDOW_HPP
#define SOLARSYSTEMCORE_CONTROLWINDOW_HPP


#include "GraphicalObjectsComponents.hpp"


class ControlWindow
{
public:
    ControlWindow();
    ~ControlWindow();

    void RenderMainWindow();

private:
    void RenderObjectRadiusSection();
    void RenderObjectDistanceSection();
    void RenderObjectSpeedSection();
    void RenderObjectTiltSection();
    void RenderObjectCreationSection();

    ObjectAttributes m_objectAttributes;

};


#endif //SOLARSYSTEMCORE_CONTROLWINDOW_HPP
