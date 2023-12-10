#include "SolarSystemModel.hpp"
#include "spdlog/spdlog.h"


constexpr double M_PI = 3.14159265358979323846;


SolarSystemModel::SolarSystemModel()
	: m_planetsMap{}
{
}

SolarSystemModel::~SolarSystemModel()
{
}

void SolarSystemModel::AddPlanet(int id, ObjectAttributes objectAttributes)
{
	m_planetsMap.insert({ id, Planet(objectAttributes) });
}

void SolarSystemModel::OnDeletePlanet(int id)
{
	m_planetsMap.erase(id);
}

int SolarSystemModel::GetPlanetsCount()
{
	return m_planetsMap.size();
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

void SolarSystemModel::MovePlanet(int planetID)
{

}
