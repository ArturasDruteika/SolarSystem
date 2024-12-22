#ifndef STELLARMODEL_SOLARSYSTEMMODEL_HPP
#define STELLARMODEL_SOLARSYSTEMMODEL_HPP


#if defined(_WIN32)
    #if defined(STELLARMODEL_EXPORT)
        #define STELLARMODEL_API __declspec(dllexport)
    #else
        #define STELLARMODEL_API __declspec(dllimport)
    #endif /* STELLARMODEL_API */
    #define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
    // GCC
    #define STELLARMODEL_API __attribute__((visibility("default")))
#endif


#include "Planet.hpp"
#include "Star.hpp"
#include "ObjectsComponents.hpp"
#include <unordered_map>
#include <vector>
#include <utility>
#include <chrono>


namespace StellarSystem
{
    constexpr double DISTANCE_MULTIPLIER = 1e9;

    class STELLARMODEL_API SolarSystemModel
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
        const std::unordered_map<int, Star>& GetStarsMap() const;
        const std::unordered_map<int, Planet>& GetPlanetsMap() const;
        const std::unordered_map<int, Physics::Point3D>& GetPlanetsNextOrbitalPositions(int orbitalPointId) const;
        const std::unordered_map<int, double>& GetPlanetsRotationDegrees() const;
        const std::unordered_map<int, int>& GetPlanetsStepIterators() const;
        void Step(double speedUpValue = 1.0);

    private:
        // Private constructor and destructor
        SolarSystemModel();
        ~SolarSystemModel();

        Physics::Point3D m_starPoint;
        std::unordered_map<int, Star> m_starsMap;
        std::unordered_map<int, Planet> m_planetsMap;
        std::unordered_map<int, Physics::Point3D> m_planetsNextOrbitalPositions;
        std::unordered_map<int, double> m_planetsRotationDegrees;
        std::unordered_map<int, int> m_planetsStepIterators;
        std::unordered_map<int, std::chrono::nanoseconds> m_accumulitiveTimes;
        std::unordered_map<int, std::chrono::steady_clock::time_point> m_lastIterationTimes;
    };
}


#endif //STELLARMODEL_SOLARSYSTEMMODEL_HPP
