#include "SolarSystemModel.hpp"

SolarSystemModel::SolarSystemModel()
	: m_planetsVec{}
{
}

SolarSystemModel::~SolarSystemModel()
{
}

void SolarSystemModel::OnNewPlanet(ObjectAttributes objectAttributes)
{
	m_planetsVec.push_back(Planet(objectAttributes));
}

int SolarSystemModel::GetPlanetsCount()
{
	return m_planetsVec.size();
}
