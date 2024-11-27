#ifndef SOLARSYSTEMRENDERING_SOLARSYSTEMVTKRENDERER_HPP
#define SOLARSYSTEMRENDERING_SOLARSYSTEMVTKRENDERER_HPP


#include "Sphere.hpp"
#include "SolarSystemModel.hpp"
#include <unordered_map>


class SolarSystemVTKInteractor
{
public:
	SolarSystemVTKInteractor();
	~SolarSystemVTKInteractor();

	void AddStar(int id, double starRadius);
	void AddPlanet(int id, PlanetAttributes planetAttributes);
	void OnDeleteStar(int id);
	void OnDeletePlanet(int id);
	std::unordered_map<int, Sphere> GetStarsSpheresMap() const;
	std::unordered_map<int, Sphere> GetPlanetsSpheresMap() const;

	void Step();

private:
	std::unordered_map<int, Sphere> m_starSpheresMap;
	std::unordered_map<int, Sphere> m_planetSpheresMap;

	SolarSystemModel& m_solarSystemModel;
};


#endif //SOLARSYSTEMRENDERING_SOLARSYSTEMVTKRENDERER_HPP
