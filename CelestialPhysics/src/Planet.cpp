#include "PhysicalConstants.hpp"
#include "Planet.hpp"
#include "ObjectsComponents.hpp"
#include <boost/dll/runtime_symbol_info.hpp>
#include <cmath>



Planet::Planet(
	PlanetAttributes planetAttributes,
	const Point3D& focusObjectPt,
	double focusObjectMass, 
	int ptsInSingleOrbit
)
	: OrbitingBody(
		planetAttributes.radius,
		planetAttributes.mass, 
		focusObjectPt,
		focusObjectMass,
		planetAttributes.semiMajorAxis, 
		planetAttributes.semiMinorAxis,
		planetAttributes.inclination
	)
	, m_planetAttributes{ planetAttributes }
	, m_rotationPerStep{ 0 }
{
	Init(planetAttributes, ptsInSingleOrbit);
}

Planet::~Planet()
{
}

double Planet::GetRotationPerStep() const
{
	return m_rotationPerStep;
}

PlanetAttributes Planet::GetPlanetAttributes() const
{
	return m_planetAttributes;
}

void Planet::Init(const PlanetAttributes& planetAttributes, int ptsInSingleOrbit)
{
	m_rotationPerStep = CalculateRotationPerStep(planetAttributes.rotationalPeriod, ptsInSingleOrbit);
}

double Planet::CalculateRotationPerStep(double rotationalPeriod, int ptsInSingleOrbit)
{
	double rotationCoeffComperedToEarth = 1 / rotationalPeriod;
	double rotationsPerYear = EARTH_ROTATIONS_PER_YEAR * rotationCoeffComperedToEarth;
	double totalRotationDegreesPerYear = rotationsPerYear * 360;
	double rotationPerStep = totalRotationDegreesPerYear / ptsInSingleOrbit;
	return rotationPerStep;
}

void Planet::TiltPlanet(double tilt)
{
}
