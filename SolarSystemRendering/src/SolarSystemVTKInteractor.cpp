#include "SolarSystemVTKInteractor.hpp"
#include "OrbitalPoint.hpp"
#include "ColorsVTK.hpp"

#include "spdlog/spdlog.h"


SolarSystemVTKInteractor::SolarSystemVTKInteractor()
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

void SolarSystemVTKInteractor::AddPlanet(int id, PlanetAttributes planetAttributes)
{
	m_solarSystemModel.AddPlanet(id, planetAttributes);
	Point3D initialCoords = m_solarSystemModel.GetPlanetsMap().at(id).GetOrbitalPoints()[0];
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
}

int SolarSystemVTKInteractor::GetPlanetsCount() const
{
	return m_solarSystemModel.GetPlanetsCount();
}

std::map<int, Sphere> SolarSystemVTKInteractor::GetStarsSpheresMap() const
{
	return m_starSpheresMap;
}

std::map<int, Sphere> SolarSystemVTKInteractor::GetPlanetsSpheresMap() const
{
	return m_planetSpheresMap;
}

void SolarSystemVTKInteractor::Step()
{
	std::map<int, Planet> planetMap = m_solarSystemModel.GetPlanetsMap();
	std::map<int, double> planetsRotationDegrees = m_solarSystemModel.GetPlanetsRotationDegrees();
	for (auto& [id, planet] : planetMap)
	{
		int stepIterator = planetMap.at(id).GetStepIterator();
		Point3D nextOrbitalPoint = planet.GetOrbitalPoints().at(stepIterator);
		m_planetSpheresMap.at(id).MoveActor(
			nextOrbitalPoint.x,
			nextOrbitalPoint.y,
			nextOrbitalPoint.z
		);
		m_planetSpheresMap.at(id).RotateActor(planetsRotationDegrees.at(id));
		m_solarSystemModel.Step();
	}
}
