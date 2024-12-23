#include "SolarSystemModel.hpp"
#include "PhysicalConstants.hpp"
#include "spdlog/spdlog.h"


namespace StellarSystem
{

    // Private constructor for singleton
    SolarSystemModel::SolarSystemModel()
        : m_starsMap{}
        , m_planetsMap{}
        , m_starPoint{ 0.0, 0.0, 0.0 }
        , m_planetsNextOrbitalPositions{}
        , m_planetsRotationDegrees{}
        , m_planetsStepIterators{}
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
        PlanetAttributes planetAttributes = objectAttributes;
        planetAttributes.aphelion *= DISTANCE_MULTIPLIER;
        planetAttributes.perihelion *= DISTANCE_MULTIPLIER;
        m_planetsMap.insert({ id, Planet(planetAttributes, m_starPoint, Physics::SOLAR_MASS, Physics::N_ORBIT_PTS) });
        m_planetsNextOrbitalPositions.insert({ id, m_planetsMap.at(id).GetOrbitalPoints(0)});
        m_planetsRotationDegrees.insert({ id, m_planetsMap.at(id).GetRotationPerStep() });
        m_planetsStepIterators.insert({ id, 0 });
        m_accumulitiveTimes.insert({ id, std::chrono::nanoseconds::zero() });
        m_lastIterationTimes.insert({ id, std::chrono::high_resolution_clock::now() });
    }

    void SolarSystemModel::OnDeleteStar(int id)
    {
        m_starsMap.erase(id);
    }

    void SolarSystemModel::OnDeletePlanet(int id)
    {
        m_planetsMap.erase(id);
    }

    const std::unordered_map<int, Star>& SolarSystemModel::GetStarsMap() const
    {
        return m_starsMap;
    }

    const std::unordered_map<int, Planet>& SolarSystemModel::GetPlanetsMap() const
    {
        return m_planetsMap;
    }

    const std::unordered_map<int, Physics::Point3D>& SolarSystemModel::GetPlanetsNextOrbitalPositions(int orbitalPointId) const
    {
        return m_planetsNextOrbitalPositions;
    }

    const std::unordered_map<int, double>& SolarSystemModel::GetPlanetsRotationDegrees() const
    {
        return m_planetsRotationDegrees;
    }

    const std::unordered_map<int, int>& SolarSystemModel::GetPlanetsStepIterators() const
    {
        return m_planetsStepIterators;
    }

    void SolarSystemModel::Step(double speedUpValue)
    {
        static int stepIterator = 0;
        for (auto& [id, planet] : m_planetsMap)
        {
            std::chrono::steady_clock::time_point currentTime = std::chrono::high_resolution_clock::now();
            std::chrono::nanoseconds iterationTime = std::chrono::duration_cast<std::chrono::nanoseconds>(currentTime - m_lastIterationTimes[id]);
            m_lastIterationTimes[id] = currentTime;
            m_accumulitiveTimes[id] += iterationTime;
            double timeBetweenCurrentElypticalPoints = planet.GetCurrentTime();
            timeBetweenCurrentElypticalPoints /= speedUpValue;
            std::chrono::nanoseconds nanosecondsBetweenCurrentElypticalPoints = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::duration<double>(timeBetweenCurrentElypticalPoints));
            
            if (m_accumulitiveTimes[id] > nanosecondsBetweenCurrentElypticalPoints)
            {
                planet.UpdateStepIterator();
                stepIterator = planet.GetStepIterator();
                m_planetsNextOrbitalPositions.at(id) = planet.GetOrbitalPoints(stepIterator);
                m_planetsStepIterators.at(id) = stepIterator;
                m_accumulitiveTimes[id] = std::chrono::nanoseconds::zero();
            }
        }
    }
}
