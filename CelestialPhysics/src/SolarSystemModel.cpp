#include "SolarSystemModel.hpp"
#include "spdlog/spdlog.h"


constexpr double M_PI = 3.14159265358979323846;


SolarSystemModel::SolarSystemModel()
	: m_starsMap{}
	, m_planetsMap{}
	, m_orbitalPointsIteratorMap{}
{
}

SolarSystemModel::~SolarSystemModel()
{
}

void SolarSystemModel::AddStar(int id, double starRadius)
{
	m_starsMap.insert({ id, Star(starRadius) });
}

void SolarSystemModel::AddPlanet(int id, ObjectAttributes objectAttributes)
{
	m_planetsMap.insert({ id, Planet(objectAttributes) });
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

void SolarSystemModel::MovePlanets()
{
	for (auto& [id, planet] : m_planetsMap)
	{
		MovePlanet(id);
	}
}

void SolarSystemModel::RotatePlanetAroundAxis()
{
	for (auto& [id, planet] : m_planetsMap)
	{
		RotatePlanetAroundAxis(id);
	}
}

void SolarSystemModel::MovePlanet(int planetID)
{
	if (m_orbitalPointsIteratorMap.at(planetID) == 0)
	{
		m_orbitalPointsIteratorMap.at(planetID)++;
		return;
	}
	std::vector<Point3D> orbitalPts = m_planetsMap.at(planetID).GetOrbitalPts();
	double x = orbitalPts.at(m_orbitalPointsIteratorMap.at(planetID)).x;
	double y = orbitalPts.at(m_orbitalPointsIteratorMap.at(planetID)).y;
	double z = orbitalPts.at(m_orbitalPointsIteratorMap.at(planetID)).z;
	spdlog::info("Point: (" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")");
	m_planetsMap.at(planetID).MoveActor(x, y, z);
	m_orbitalPointsIteratorMap.at(planetID)++;
	if (m_orbitalPointsIteratorMap.at(planetID) == 10'000)
	{
		m_orbitalPointsIteratorMap.at(planetID) = 0;
	}
}

void SolarSystemModel::RotatePlanetAroundAxis(int planetId, double rotationAngle)
{
	m_planetsMap.at(planetId).RotateActor(rotationAngle);
}
