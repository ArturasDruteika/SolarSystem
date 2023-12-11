#include "SolarSystemModel.hpp"
#include "spdlog/spdlog.h"


constexpr double M_PI = 3.14159265358979323846;


SolarSystemModel::SolarSystemModel()
	: m_starsMap{}
	, m_planetsMap{}
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

}

void SolarSystemModel::RotatePlanetAroundAxis(int planetId, double rotationAngle)
{
	m_planetsMap.at(planetId).RotateActor(rotationAngle);
}
