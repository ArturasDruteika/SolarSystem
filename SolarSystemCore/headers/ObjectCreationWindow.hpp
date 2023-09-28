#ifndef SOLARSYSTEMCORE_CONTROLWINDOW_HPP
#define SOLARSYSTEMCORE_CONTROLWINDOW_HPP


#include "ObjectsComponents.hpp"
#include "boost/signals2.hpp"


typedef boost::signals2::signal<void(const ObjectAttributes& objectAttributes)> CreationSignal;


class ObjectCreationWindow
{
public:
    ObjectCreationWindow();
    ~ObjectCreationWindow();

    void RenderMainWindow();

    CreationSignal OnCreateSignal;

private:
    void RenderObjectRadiusSection();
    void RenderObjectDistanceSection();
    void RenderObjectSpeedSection();
    void RenderObjectTiltSection();
    void RenderObjectCreationSection();

    ObjectAttributes m_objectAttributes;

};


#endif //SOLARSYSTEMCORE_CONTROLWINDOW_HPP
