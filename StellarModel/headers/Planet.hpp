#ifndef STELLARMODEL_PLANETS_HPP
#define STELLARMODEL_PLANETS_HPP


#if defined (_WIN32)
#if defined(STELLARMODEL_EXPORT)
#define STELLARMODEL_API __declspec(dllexport)
#else
#define  STELLARMODEL_API __declspec(dllimport)
#endif /* STELLARMODEL_API */
#define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
//  GCC
#define Planet_API __attribute__((visibility("default")))
#endif


#include "OrbitingBody.hpp"
#include "ObjectsComponents.hpp"
#include <utility>


class STELLARMODEL_API Planet : public OrbitingBody
{
public:
	Planet(
		PlanetAttributes planetAttributes, 
		const Physics::Point3D& focusObjectPt,
		double focusObjectMass, 
		int ptsInSingleOrbit
	);
	~Planet();

	double GetRotationPerStep() const;
	double GetTilt() const;
	double GetStepIterator() const;
	void UpdateStepIterator();
	double GetCurrentSpeed() const;
	PlanetAttributes GetPlanetAttributes() const;

private:
	void Init(const PlanetAttributes& planetAttributes, int ptsInSingleOrbit);
	double CalculateRotationPerStep(double rotationalPeriod, int ptsInSingleOrbit);

	double m_rotationPerStep;
	double m_tilt;
	int m_stepIterator;
	PlanetAttributes m_planetAttributes;
};

#endif //STELLARMODEL_PLANETS_HPP
