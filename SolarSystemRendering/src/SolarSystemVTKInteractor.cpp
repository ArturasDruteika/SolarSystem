#include "SolarSystemVTKInteractor.hpp"
#include "OrbitalPoint.hpp"


SolarSystemVTKInteractor::SolarSystemVTKInteractor()
{
}

SolarSystemVTKInteractor::~SolarSystemVTKInteractor()
{
}

void SolarSystemVTKInteractor::Step()
{
	int i = 0;
	if (i % 10'000 == 0)
	{
		i = 0;
	}

	std::map<int, Point3D> planetsNextOrbitalPoints = m_solarSystemModel.GetPlanetsNextOrbitalPositions(i);

	i++;
}
