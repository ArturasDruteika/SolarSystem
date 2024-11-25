#ifndef CELESTIALPHYSICS_SOLARSYSTEMMODEL_HPP
#define CELESTIALPHYSICS_SOLARSYSTEMMODEL_HPP


#if defined (_WIN32)
#if defined(CELESTIALPHYSICS_EXPORT)
#define CELESTIALPHYSICS_API __declspec(dllexport)
#else
#define  CELESTIALPHYSICS_API __declspec(dllimport)
#endif /* CELESTIALPHYSICS_API */
#define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
//  GCC
#define SolarSystemModel_API __attribute__((visibility("default")))
#endif


#include "Planet.hpp"
#include "Star.hpp"
#include "ObjectsComponents.hpp"
#include "OrbitalMechanics.hpp"
#include <map>
#include <vector>
#include <utility>


class CELESTIALPHYSICS_API SolarSystemModel
{
public:
    // Delete copy constructor and assignment operator to enforce singleton pattern
    SolarSystemModel(const SolarSystemModel&) = delete;
    SolarSystemModel& operator=(const SolarSystemModel&) = delete;

    // Provide a static method to access the singleton instance
    static SolarSystemModel& GetInstance();

    void AddStar(int id, double starRadius);
    void AddPlanet(int id, const PlanetAttributes& objectAttributes);
    void OnDeleteStar(int id);
    void OnDeletePlanet(int id);
    int GetPlanetsCount() const;
    const std::map<int, Star>& GetStarsMap() const;
    const std::map<int, Planet>& GetPlanetsMap() const;
    const std::map<int, Point3D>& GetPlanetsNextOrbitalPositions(int orbitalPointId) const;
    const std::map<int, double>& GetPlanetsRotationDegrees() const;
    const std::map<int, int>& GetPlanetsStepIterators() const;
    void Step();

private:
    // Private constructor and destructor
    SolarSystemModel();
    ~SolarSystemModel();

    Point3D m_starPoint;
    std::map<int, Star> m_starsMap;
    std::map<int, Planet> m_planetsMap;
    std::map<int, Point3D> m_planetsNextOrbitalPositions;
    std::map<int, double> m_planetsRotationDegrees;
    std::map<int, int> m_planetsStepIterators;

    OrbitalMechanics m_orbitalMechanics;
};

#endif //CELESTIALPHYSICS_SOLARSYSTEMMODEL_HPP
