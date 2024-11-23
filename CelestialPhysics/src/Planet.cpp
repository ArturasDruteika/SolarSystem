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
	, m_tilt{ planetAttributes.tilt }
	, m_stepIterator{ 0 }
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

double Planet::GetTilt() const
{
	return m_tilt;
}

double Planet::GetStepIterator() const
{
	return m_stepIterator;
}

void Planet::UpdateStepIterator()
{
	m_stepIterator += 1;
	if (m_stepIterator == N_ORBIT_PTS)
	{
		m_stepIterator = 0;
	}
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
	double totalRotationDegreesPerYear = rotationalPeriod * 360;
	double rotationPerStep = totalRotationDegreesPerYear / ptsInSingleOrbit;
	return rotationPerStep;
}
