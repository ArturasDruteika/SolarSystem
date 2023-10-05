#ifndef SOLARSYSTEMCORE_CONTROLWINDOW_HPP
#define SOLARSYSTEMCORE_CONTROLWINDOW_HPP


#include "ObjectsComponents.hpp"
#include "Planet.hpp"
#include "boost/signals2.hpp"
#include "imgui.h"
#include <map>


typedef boost::signals2::signal<void(int id, const ObjectAttributes& objectAttributes)> CreationSignal;
typedef boost::signals2::signal<void(const int id)> DeleteSignal;


class ObjectCreationWindow
{
public:
    ObjectCreationWindow();
    ~ObjectCreationWindow();

    void Init();
    void RenderMainWindow();

    CreationSignal OnCreateSignal;
    DeleteSignal OnDeleteSignal;

private:
    void InitInternal();

    void RenderObjectRadiusSection();
    void RenderObjectDistanceSection();
    void RenderObjectSpeedSection();
    void RenderObjectTiltSection();
    void RenderObjectCreationSection();
    void RenderPlanetsTableSection();
    void RenderCreatedPlanetsInfoSection();

    void RenderObjectAttributeSelectionSection(const std::string& separatorText, const std::string& idText, double& parameterValue);
    void CreateFont(const std::string& fontPath, float fontSize);

    ObjectAttributes m_objectAttributes;
    std::map<int, ObjectAttributes> m_planetsAttributesMap;
    int m_planetsCount;
    ImFont* m_customFont;
};


#endif //SOLARSYSTEMCORE_CONTROLWINDOW_HPP
