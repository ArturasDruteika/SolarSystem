#ifndef CELESTIALPHYSICS_SOLARSYSTEMMODEL_HPP
#define CELESTIALPHYSICS_SOLARSYSTEMMODEL_HPP


#if defined (_WIN32)
#if defined(CELESTIALPHYSICS_EXPORT)
#define CELESTIALPHYSICS_API __declspec(dllexport)
#else
#define  CELESTIALPHYSICS_API __declspec(dllimport)
#endif /* CELESTIALPHYSICS_API */
#define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
//  GCC
#define SolarSystemModel_API __attribute__((visibility("default")))
#endif


#include "Sphere.hpp"
#include "Planet.hpp"
#include "Star.hpp"
#include "ObjectsComponents.hpp"
#include "OrbitalMechanics.hpp"
#include <map>
#include <vector>
#include <utility>


class CELESTIALPHYSICS_API SolarSystemModel
{
public:
	SolarSystemModel();
	~SolarSystemModel();

	void AddStar(int id, double starRadius);
	void AddPlanet(int id, ObjectAttributes objectAttributes);
	void OnDeleteStar(int id);
	void OnDeletePlanet(int id);
	int GetPlanetsCount();
	std::map<int, Star> GetStarsMap();
	std::map<int, Planet> GetPlanetsMap();
	void MovePlanets();

private:
	void MovePlanet(int planetID);

	std::map<int, Star> m_starsMap;
	std::map<int, Planet> m_planetsMap;

	OrbitalMechanics m_orbitalMechanics;
};

#endif //CELESTIALPHYSICS_SOLARSYSTEMMODEL_HPP
