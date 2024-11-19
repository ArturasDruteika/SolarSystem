#include "SolarSystemVTKInteractor.hpp"
#include "OrbitalPoint.hpp"


SolarSystemVTKInteractor::SolarSystemVTKInteractor()
{
}

SolarSystemVTKInteractor::~SolarSystemVTKInteractor()
{
}

void SolarSystemVTKInteractor::AddStar(int id, double starRadius)
{
	// TODO: add another param for star coordinates
	m_solarSystemModel.AddStar(id, starRadius);
}

void SolarSystemVTKInteractor::AddPlanet(int id, PlanetAttributes planetAttributes)
{
	m_solarSystemModel.AddPlanet(id, planetAttributes);
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

std::map<int, Star> SolarSystemVTKInteractor::GetStarsMap() const
{
	return m_solarSystemModel.GetStarsMap();
}

std::map<int, Planet> SolarSystemVTKInteractor::GetPlanetsMap() const
{
	return m_solarSystemModel.GetPlanetsMap();
}

void SolarSystemVTKInteractor::Step()
{
	m_solarSystemModel.Step();
	int i = 0;
	if (i % 10'000 == 0)
	{
		i = 0;
	}

	std::map<int, Point3D> planetsNextOrbitalPoints = m_solarSystemModel.GetPlanetsNextOrbitalPositions(i);

	i++;
}
