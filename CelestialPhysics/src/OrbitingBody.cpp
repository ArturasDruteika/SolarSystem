#include "OrbitingBody.hpp"
#include "OrbitalMechanics.hpp"
#include "PhysicalConstants.hpp"
#include <stdexcept>
#include <complex>


OrbitingBody::OrbitingBody(
	double radius, 
	double mass, 
	const Point3D& focusObjectPt,
	double focusObjectMass, 
	double semiMajorAxis, 
	double semiMinorAxis,
	double rotationPeriod,
	double inclination
)
	: CosmicBody(radius, mass)
	, m_semiMajorAxis{ semiMajorAxis }
	, m_semiMinorAxis{ semiMinorAxis }
	, m_inclination{ inclination }
	, m_rotationalPeriod{ rotationPeriod }
{
	m_eccentricity = OrbitalMechanics::CalculateEccentricity(m_semiMajorAxis, m_semiMinorAxis);
	m_mu = OrbitalMechanics::CalculateGravitationalParameter(focusObjectMass);
	CalculateOrbitalPoints();
	CalculateOrbitalSpeedVec(focusObjectPt);
}

OrbitingBody::~OrbitingBody()
{
}

double OrbitingBody::GetSemiMajorAxis() const
{
	return m_semiMajorAxis;
}

double OrbitingBody::GetSemiMinorAxis() const
{
	return m_semiMinorAxis;
}

double OrbitingBody::GetEccentricity() const
{
	return m_eccentricity;
}

double OrbitingBody::GetInclination() const
{
	return m_inclination;
}

double OrbitingBody::GetGravitationalParameter() const
{
	return m_mu;
}

double OrbitingBody::GetRotationalPeriod() const
{
	return m_rotationalPeriod;
}

const std::vector<Point3D>& OrbitingBody::GetOrbitalPoints() const
{
	return m_orbitalPoints;
}

Point3D OrbitingBody::GetOrbitalPoints(int id) const
{
	return m_orbitalPoints[id];
}

const std::vector<double>& OrbitingBody::GetOrbitalSpeeds() const
{
	return m_orbitalSpeeds;
}

void OrbitingBody::CalculateOrbitalPoints()
{
	m_orbitalPoints = OrbitalMechanics::GenerateEllipticalOrbit(
		m_semiMajorAxis,
		m_eccentricity,
		m_inclination,
		N_ORBIT_PTS
	);
}

void OrbitingBody::CalculateOrbitalSpeedVec(const Point3D& focusPt)
{
	for (const Point3D& orbitalPt : m_orbitalPoints)
	{
		double orbitalRadius = OrbitalMechanics::CalculateOrbitalRadius(focusPt, orbitalPt);
		double orbitalSpeed = OrbitalMechanics::CalculateOrbitalSpeed(orbitalRadius, m_semiMajorAxis, m_mu);
		m_orbitalSpeeds.push_back(orbitalSpeed);
	}
}
