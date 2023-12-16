#include "SolarSystemModel.hpp"
#include "spdlog/spdlog.h"


constexpr double M_PI = 3.141'592'653'589'793'238'46;
constexpr double N_ORBIT_PTS = 10'000;


SolarSystemModel::SolarSystemModel()
	: m_starsMap{}
	, m_planetsMap{}
	, m_orbitalPointsMap{}
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

void SolarSystemModel::AddPlanet(int id, PlanetAttributes objectAttributes)
{
	m_planetsMap.insert({ id, Planet(objectAttributes) });
	std::vector<Point3D> orbitalPoints = OrbitalMechanics::CalculateOrbitPoints(
		objectAttributes.semiMajorAxis, 
		objectAttributes.semiMinorAxis, 
		objectAttributes.inclination, 
		N_ORBIT_PTS
	);
	m_orbitalPointsMap.insert({ id, orbitalPoints });
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

void SolarSystemModel::Step()
{
	MovePlanets();
	//RotatePlanetsAroundAxis();
}

void SolarSystemModel::MovePlanet(int planetID)
{
	if (m_orbitalPointsIteratorMap.at(planetID) == 0)
	{
		m_orbitalPointsIteratorMap.at(planetID)++;
		return;
	}
	std::vector<Point3D> orbitalPts = m_orbitalPointsMap.at(planetID);
	double x = orbitalPts.at(m_orbitalPointsIteratorMap.at(planetID)).x;
	double y = orbitalPts.at(m_orbitalPointsIteratorMap.at(planetID)).y;
	double z = orbitalPts.at(m_orbitalPointsIteratorMap.at(planetID)).z;
	m_planetsMap.at(planetID).MoveActor(x, y, z);
	m_orbitalPointsIteratorMap.at(planetID)++;
	if (m_orbitalPointsIteratorMap.at(planetID) == N_ORBIT_PTS)
	{
		m_orbitalPointsIteratorMap.at(planetID) = 0;
	}
}

void SolarSystemModel::MovePlanets()
{
	for (auto& [id, planet] : m_planetsMap)
	{
		MovePlanet(id);
	}
}

void SolarSystemModel::RotatePlanetAroundAxis(int planetId, double rotationAngle)
{
	double tilt = m_planetsMap.at(planetId).GetPlanetAttributes().tilt;
	m_planetsMap.at(planetId).RotateActor(tilt);
}

void SolarSystemModel::RotatePlanetsAroundAxis()
{
	for (auto& [id, planet] : m_planetsMap)
	{
		RotatePlanetAroundAxis(id);
	}
}