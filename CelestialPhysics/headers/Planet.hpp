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
#include "CosmicBody.hpp"
#include "ObjectsComponents.hpp"
#include <utility>


class CELESTIALPHYSICS_API Planet : public CosmicBody, public Sphere
{
public:
	Planet(PlanetAttributes planetAttributes, int ptsInSingleOrbit);
	~Planet();

	PlanetAttributes GetPlanetAttributes();
	vtkSmartPointer<vtkActor> GetPlanetActor();
	void MovePlanet(double xPos, double yPos, double zPos);
	void RotatePlanet();

private:
	void Init(const PlanetAttributes& planetAttributes, int ptsInSingleOrbit);
	double CalculateRotationPerStep(double rotationalPeriod, int ptsInSingleOrbit);
	void TiltPlanet(double tilt);

	double m_speedAroundCenter;
	double m_rotationPerStep;

	PlanetAttributes m_planetAttributes;
};

#endif //CELESTIALPHYSICS_PLANETS_HPP
