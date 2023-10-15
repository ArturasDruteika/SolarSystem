#include "SolarSystemModel.hpp"


constexpr double M_PI = 3.14159265358979323846;


SolarSystemModel::SolarSystemModel()
	: m_planetsMap{}
	, m_planetsRotationCoords{}
{
}

SolarSystemModel::~SolarSystemModel()
{
}

void SolarSystemModel::AddPlanet(int id, ObjectAttributes objectAttributes)
{
	m_planetsMap.insert({ id, Planet(objectAttributes) });
	std::vector<std::vector<double>> rotationCoordsVec = m_orbitalMechanics.GenerateOrbitPoints(10.0, 0.50, objectAttributes.tiltDegrees);
	m_planetsRotationCoords.insert({ id, rotationCoordsVec });
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

std::map<int, std::vector<std::vector<double>>> SolarSystemModel::GetPlanetsRotationCoords(int a)
{
	return m_planetsRotationCoords;
}

void SolarSystemModel::MovePlanet(int planetID, int orbitCoordPoint)
{
	double x = m_planetsRotationCoords.at(planetID)[orbitCoordPoint][0] / 1000;
	double y = m_planetsRotationCoords.at(planetID)[orbitCoordPoint][1] / 1000;
	double z = m_planetsRotationCoords.at(planetID)[orbitCoordPoint][2] / 1000;
	m_planetsMap.at(planetID).MovePlanet(x, y, z);
}
