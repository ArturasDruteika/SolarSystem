#ifndef SOLARSYSTEMRENDERING_SOLARSYSTEMVTKRENDERER_HPP
#define SOLARSYSTEMRENDERING_SOLARSYSTEMVTKRENDERER_HPP


#include "Sphere.hpp"
#include "SolarSystemModel.hpp"
#include <map>


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
	std::map<int, Sphere> GetStarsSpheresMap() const;
	std::map<int, Sphere> GetPlanetsSpheresMap() const;

	void Step();

private:
	std::map<int, Sphere> m_starSpheresMap;
	std::map<int, Sphere> m_planetSpheresMap;

	SolarSystemModel& m_solarSystemModel;
};


#endif //SOLARSYSTEMRENDERING_SOLARSYSTEMVTKRENDERER_HPP
