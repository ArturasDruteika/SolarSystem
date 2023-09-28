#ifndef CELESTIALPHYSICS_PLANETS_HPP
#define CELESTIALPHYSICS_PLANETS_HPP


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
#define Planet_API __attribute__((visibility("default")))
#endif


#include "Sphere.hpp"
#include <map>

class CELESTIALPHYSICS_API Planet
{
public:
	Planet();
	~Planet();

	void OnNewPlanet(const ObjectAttributes& objectAttributes);

private:
	int m_planetCount;
	std::map<int, ObjectAttributes> m_planetsMap;
};

#endif //CELESTIALPHYSICS_PLANETS_HPP
