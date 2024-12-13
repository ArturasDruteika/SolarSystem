#include "SolarSystemVTKInteractor.hpp"
#include "OrbitalPoint.hpp"
#include "ColorsVTK.hpp"
#include "spdlog/spdlog.h"


SolarSystemVTKInteractor::SolarSystemVTKInteractor()
	: m_solarSystemModel{ StellarSystem::SolarSystemModel::GetInstance() }
{
}

SolarSystemVTKInteractor::~SolarSystemVTKInteractor()
{
}

void SolarSystemVTKInteractor::AddStar(int id, double starRadius)
{
	// TODO: add another param for star coordinates
	std::vector<double> starCoords = { 0.0, 0.0, 0.0 };
	m_solarSystemModel.AddStar(id, starRadius);
	m_starSpheresMap.insert({ id, Sphere(starRadius, starCoords, ColorsVTK::YELLOW) });
}

void SolarSystemVTKInteractor::AddPlanet(int id, const StellarSystem::PlanetAttributes& planetAttributes)
{
	m_solarSystemModel.AddPlanet(id, planetAttributes);
	Physics::Point3D initialCoords = m_solarSystemModel.GetPlanetsMap().at(id).GetOrbitalPoints()[0];
	std::vector<double> initialCoordsVec;
	initialCoordsVec.push_back(initialCoords.x);
	initialCoordsVec.push_back(initialCoords.y);
	initialCoordsVec.push_back(initialCoords.z);
	Sphere planetSphere = Sphere(planetAttributes.radius, initialCoordsVec, ColorsVTK::BLUE);
	planetSphere.RotateY(m_solarSystemModel.GetPlanetsMap().at(id).GetTilt());
	m_planetSpheresMap.insert({ id, planetSphere });
}

void SolarSystemVTKInteractor::OnDeleteStar(int id)
{
	m_solarSystemModel.OnDeleteStar(id);
}

void SolarSystemVTKInteractor::OnDeletePlanet(int id)
{
	m_solarSystemModel.OnDeletePlanet(id);
	m_planetSpheresMap.erase(id);
}

std::unordered_map<int, Sphere> SolarSystemVTKInteractor::GetStarsSpheresMap() const
{
	return m_starSpheresMap;
}

std::unordered_map<int, Sphere> SolarSystemVTKInteractor::GetPlanetsSpheresMap() const
{
	return m_planetSpheresMap;
}

void SolarSystemVTKInteractor::Step()
{
	const std::unordered_map<int, StellarSystem::Planet>& planetMap = m_solarSystemModel.GetPlanetsMap();
	// Check needed to ensure that during planet addition or deletion there was enough time to create planet object and planet sphere
	if (m_planetSpheresMap.size() != planetMap.size())
	{
		return;
	}
	static const std::unordered_map<int, double>& planetsRotationDegrees = m_solarSystemModel.GetPlanetsRotationDegrees();
	for (auto& [id, planet] : planetMap)
	{
		int stepIterator = planetMap.at(id).GetStepIterator();
		Physics::Point3D nextOrbitalPoint = planet.GetOrbitalPoints().at(stepIterator);
		m_planetSpheresMap.at(id).MoveActor(
			nextOrbitalPoint.x,
			nextOrbitalPoint.y,
			nextOrbitalPoint.z
		);
		m_planetSpheresMap.at(id).RotateActor(planetsRotationDegrees.at(id));
		m_solarSystemModel.Step();
	}
}
