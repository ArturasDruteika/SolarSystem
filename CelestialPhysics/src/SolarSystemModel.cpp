#include "SolarSystemModel.hpp"

SolarSystemModel::SolarSystemModel()
	: m_planetsMap{}
	, m_planetsRotationCoords2{}
{
}

SolarSystemModel::~SolarSystemModel()
{
}

void SolarSystemModel::AddPlanet(int id, ObjectAttributes objectAttributes)
{
	// TODO: shouldn't it be new Planet(objectAttributes)???
	m_planetsMap.insert({ id, Planet(objectAttributes) });
	m_planetsRotationCoords.insert(
		{ 
			id, 
			m_planetsMap.at(id).GenerateCircleXYPointsVec(objectAttributes.distanceFromCenter, 9000) 
		}
	);

	std::vector<std::vector<double>> rotationCoordsVec = m_orbitalMechanics.GenerateRotationCoords(objectAttributes.radius, objectAttributes.tiltDegrees, 9000);
	m_planetsRotationCoords2.insert({ id, rotationCoordsVec });

}

void SolarSystemModel::OnDeletePlanet(int id)
{
	m_planetsMap.erase(id);
	m_planetsRotationCoords.erase(id);
}

int SolarSystemModel::GetPlanetsCount()
{
	return m_planetsMap.size();
}

std::map<int, Planet> SolarSystemModel::GetPlanetsMap()
{
	return m_planetsMap;
}

std::map<int, std::vector<std::pair<double, double>>> SolarSystemModel::GetPlanetsRotationCoords()
{
	return m_planetsRotationCoords;
}

std::map<int, std::vector<std::vector<double>>> SolarSystemModel::GetPlanetsRotationCoords(int a)
{
	return m_planetsRotationCoords2;
}
