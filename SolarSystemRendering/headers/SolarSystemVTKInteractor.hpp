#ifndef SOLARSYSTEMRENDERING_SOLARSYSTEMVTKRENDERER_HPP
#define SOLARSYSTEMRENDERING_SOLARSYSTEMVTKRENDERER_HPP


#include "Sphere.hpp"
#include "SolarSystemModel.hpp"


class SolarSystemVTKInteractor
{
public:
	SolarSystemVTKInteractor();
	~SolarSystemVTKInteractor();

	void AddStar(int id, double starRadius);
	void AddPlanet(int id, PlanetAttributes planetAttributes);
	void OnDeleteStar(int id);
	void OnDeletePlanet(int id);
	int GetPlanetsCount() const;
	std::map<int, Star> GetStarsMap() const;
	std::map<int, Planet> GetPlanetsMap() const;

	void Step();

private:
	SolarSystemModel m_solarSystemModel;
};


#endif //SOLARSYSTEMRENDERING_SOLARSYSTEMVTKRENDERER_HPP
