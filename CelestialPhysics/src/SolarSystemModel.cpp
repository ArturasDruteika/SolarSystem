#include "SolarSystemModel.hpp"

SolarSystemModel::SolarSystemModel()
	: m_planetsMap{}
{
}

SolarSystemModel::~SolarSystemModel()
{
}

void SolarSystemModel::OnNewPlanet(int id, ObjectAttributes objectAttributes)
{
	m_planetsMap.insert({ id, Planet(objectAttributes) });
}

int SolarSystemModel::GetPlanetsCount()
{
	return m_planetsMap.size();
}

std::map<int, Planet> SolarSystemModel::GetPlanetsMap()
{
	return m_planetsMap;
}
