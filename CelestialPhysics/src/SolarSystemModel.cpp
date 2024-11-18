#include "SolarSystemModel.hpp"
#include "spdlog/spdlog.h"


constexpr double M_PI = 3.141'592'653'589'793'238'46;
constexpr double N_ORBIT_PTS = 10'000;


SolarSystemModel::SolarSystemModel()
	: m_starsMap{}
	, m_planetsMap{}
	, m_orbitalPointsIteratorMap{}
	, m_starPoint{ 0, 0, 0 }
{
}

SolarSystemModel::~SolarSystemModel()
{
}

void SolarSystemModel::AddStar(int id, double starRadius)
{
	m_starsMap.insert({ id, Star(starRadius, 0.0) });
}

void SolarSystemModel::AddPlanet(int id, PlanetAttributes objectAttributes)
{
	m_planetsMap.insert({ id, Planet(objectAttributes, m_starPoint, 10000, N_ORBIT_PTS) });
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

int SolarSystemModel::GetPlanetsCount()
{
	return m_planetsMap.size();
}

std::map<int, Star> SolarSystemModel::GetStarsMap()
{
	return m_starsMap;
}

std::map<int, Planet> SolarSystemModel::GetPlanetsMap()
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

void SolarSystemModel::Step()
{
	RotatePlanetsAroundAxis();
	MovePlanets();
}

void SolarSystemModel::RotatePlanetAroundAxis(int planetId)
{
	m_planetsMap.at(planetId).RotatePlanet();
}

void SolarSystemModel::RotatePlanetsAroundAxis()
{
	for (auto& [id, planet] : m_planetsMap)
	{
		RotatePlanetAroundAxis(id);
	}
}

void SolarSystemModel::MovePlanet(int planetId)
{
	std::vector<double> nextOrbitalPosition = GetNextOrbitalPosition(planetId);
	MovePlanet(planetId, nextOrbitalPosition);
	UpdateOrbitalPointsIterator(planetId);
}

void SolarSystemModel::MovePlanet(int planetId, const std::vector<double> nextOrbitalPt)
{
	m_planetsMap.at(planetId).MoveActor(nextOrbitalPt[0], nextOrbitalPt[1], nextOrbitalPt[2]);
}

void SolarSystemModel::MovePlanets()
{
	for (auto& [id, planet] : m_planetsMap)
	{
		MovePlanet(id);
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
