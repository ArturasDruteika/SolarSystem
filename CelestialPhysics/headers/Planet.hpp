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
#include "ObjectsComponents.hpp"

class CELESTIALPHYSICS_API Planet
{
public:
	Planet(ObjectAttributes objectAttributes);
	~Planet();

	vtkSmartPointer<vtkActor> GetPlanetActor();
	void MovePlanet(double xPos, double yPos, double zPos);

private:
	ObjectAttributes m_planetAttributes;
	Sphere m_sphere;
};

#endif //CELESTIALPHYSICS_PLANETS_HPP
