#ifndef SOLARSYSTEMCORE_CONTROLWINDOW_HPP
#define SOLARSYSTEMCORE_CONTROLWINDOW_HPP


#include "GraphicalWindow.hpp"
#include "ObjectsComponents.hpp"
#include "Planet.hpp"
#include "boost/signals2.hpp"
#include "imgui.h"
#include <map>


typedef boost::signals2::signal<void(int id, const PlanetAttributes& objectAttributes)> CreationSignal;
typedef boost::signals2::signal<void(const int id)> DeleteSignal;


class ObjectCreationWindow : public GraphicalWindow
{
public:
    ObjectCreationWindow(const std::string& windowName);
    ~ObjectCreationWindow();

    void Init() override;
    void DeInit() override;
    void OnDeletePlanet(int id);

    CreationSignal OnCreateSignal;
    DeleteSignal OnDeleteSignal;

private:
    void InitInternal() override;
    void DeInitInternal() override;
    void RenderWindowInternal() override;

    void RenderObjectRadiusSection();
    void RenderSemiMajorAxisSection();
    void RenderSemiMinorAxisSection();
    void RenderObjectRotationalPeriodSection();
    void RenderObjectInclinationSection();
    void RenderObjectTiltSection();
    void RenderObjectCreationSection();
    void RenderPlanetsTableSection();
    void RenderCreatedPlanetsInfoSection();

    void SetInitialValues();
    void RenderObjectAttributeSelectionSection(const std::string& separatorText, const std::string& idText, double& parameterValue);
    void ReplaceDegreesToRadians(PlanetAttributes& planetAttributes);
    PlanetAttributes ProcessPlanetAttributes(const PlanetAttributes& objectAttributes);
    int GetNextAvailableNumber(const std::vector<int>& values);
    std::vector<int> RemoveIntegerFromVector(const std::vector<int>& inputVector, int numberToRemove);

    std::vector<int> m_planetsIds;
    std::unordered_map<int, PlanetAttributes> m_planetsAttributesMap;
    PlanetAttributes m_objectAttributes;
    ImFont* m_customFont;
};


#endif //SOLARSYSTEMCORE_CONTROLWINDOW_HPP
