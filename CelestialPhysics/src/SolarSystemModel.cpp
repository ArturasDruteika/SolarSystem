#include "SolarSystemModel.hpp"
#include "PhysicalConstants.hpp"
#include "spdlog/spdlog.h"


// Private constructor for singleton
SolarSystemModel::SolarSystemModel()
    : m_starsMap{}
    , m_planetsMap{}
    , m_orbitalPointsIteratorMap{}
    , m_starPoint{ 0, 0, 0 }
{
}

// Destructor
SolarSystemModel::~SolarSystemModel()
{
}

// Singleton instance access
SolarSystemModel& SolarSystemModel::GetInstance()
{
    static SolarSystemModel instance; // Ensures single creation
    return instance;
}

void SolarSystemModel::AddStar(int id, double starRadius)
{
    m_starsMap.insert({ id, Star(starRadius, 0.0) });
}

void SolarSystemModel::AddPlanet(int id, const PlanetAttributes& objectAttributes)
{
    m_planetsMap.insert({ id, Planet(objectAttributes, m_starPoint, 10000.0, N_ORBIT_PTS) });
    m_orbitalPointsIteratorMap.insert({ id, 0 });
}

void SolarSystemModel::OnDeleteStar(int id)
{
    m_starsMap.erase(id);
}

void SolarSystemModel::OnDeletePlanet(int id)
{
    m_planetsMap.erase(id);
}

int SolarSystemModel::GetPlanetsCount() const
{
    return m_planetsMap.size();
}

const std::map<int, Star>& SolarSystemModel::GetStarsMap() const
{
    return m_starsMap;
}

const std::map<int, Planet>& SolarSystemModel::GetPlanetsMap() const
{
    return m_planetsMap;
}

std::map<int, Point3D> SolarSystemModel::GetPlanetsNextOrbitalPositions(int orbitalPointId) const
{
    std::map<int, Point3D> planetsNextOrbitalPoints;
    for (const auto& [id, planet] : m_planetsMap)
    {
        planetsNextOrbitalPoints.insert({ id, planet.GetOrbitalPoints(orbitalPointId) });
    }
    return planetsNextOrbitalPoints;
}

std::map<int, double> SolarSystemModel::GetPlanetsRotationDegrees() const
{
    std::map<int, double> planetsRotationDegrees;
    for (const auto& [id, planet] : m_planetsMap)
    {
        planetsRotationDegrees.insert({ id, planet.GetRotationPerStep() });
    }
    return planetsRotationDegrees;
}

std::map<int, int> SolarSystemModel::GetPlanetsStepIterators() const
{
    std::map<int, int> planetsStepIterators;
    for (const auto& [id, planet] : m_planetsMap)
    {
        planetsStepIterators.insert({ id, planet.GetStepIterator() });
    }
    return planetsStepIterators;
}

void SolarSystemModel::Step()
{
    for (auto& [id, planet] : m_planetsMap)
    {
        planet.UpdateStepIterator();
    }
}

std::vector<double> SolarSystemModel::GetNextOrbitalPosition(int planetId)
{
    std::vector<double> nextOrbitalPosition;
    std::vector<Point3D> orbitalPts = m_planetsMap.at(planetId).GetOrbitalPoints();
    double x = orbitalPts.at(m_orbitalPointsIteratorMap.at(planetId)).x;
    double y = orbitalPts.at(m_orbitalPointsIteratorMap.at(planetId)).y;
    double z = orbitalPts.at(m_orbitalPointsIteratorMap.at(planetId)).z;
    nextOrbitalPosition.push_back(x);
    nextOrbitalPosition.push_back(y);
    nextOrbitalPosition.push_back(z);
    return nextOrbitalPosition;
}

void SolarSystemModel::UpdateOrbitalPointsIterator(int planetId)
{
    m_orbitalPointsIteratorMap.at(planetId)++;
    if (m_orbitalPointsIteratorMap.at(planetId) == N_ORBIT_PTS)
    {
        m_orbitalPointsIteratorMap.at(planetId) = 0;
    }
}
