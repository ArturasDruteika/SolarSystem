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


#include "OrbitingBody.hpp"
#include "ObjectsComponents.hpp"
#include <utility>


class CELESTIALPHYSICS_API Planet : public OrbitingBody
{
public:
	Planet(
		PlanetAttributes planetAttributes, 
		const Point3D& focusObjectPt,
		double focusObjectMass, 
		int ptsInSingleOrbit
	);
	~Planet();

	double GetRotationPerStep() const;
	PlanetAttributes GetPlanetAttributes() const;

private:
	void Init(const PlanetAttributes& planetAttributes, int ptsInSingleOrbit);
	double CalculateRotationPerStep(double rotationalPeriod, int ptsInSingleOrbit);
	void TiltPlanet(double tilt);

	double m_rotationPerStep;
	PlanetAttributes m_planetAttributes;
};

#endif //CELESTIALPHYSICS_PLANETS_HPP
