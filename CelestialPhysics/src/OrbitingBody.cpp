#include "OrbitingBody.hpp"
#include "OrbitalMechanics.hpp"
#include "PhysicalConstants.hpp"
#include <stdexcept>
#include <complex>


OrbitingBody::OrbitingBody(
	double radius, 
	double mass, 
	const Physics::Point3D& focusObjectPt,
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
	m_eccentricity = Physics::OrbitalMechanics::CalculateEccentricity(m_semiMajorAxis, m_semiMinorAxis);
	m_mu = Physics::OrbitalMechanics::CalculateGravitationalParameter(focusObjectMass);
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

const std::vector<Physics::Point3D>& OrbitingBody::GetOrbitalPoints() const
{
	return m_orbitalPoints;
}

Physics::Point3D OrbitingBody::GetOrbitalPoints(int id) const
{
	return m_orbitalPoints[id];
}

const std::vector<double>& OrbitingBody::GetOrbitalSpeeds() const
{
	return m_orbitalSpeeds;
}

void OrbitingBody::CalculateOrbitalPoints()
{
	m_orbitalPoints = Physics::OrbitalMechanics::GenerateEllipticalOrbit(
		m_semiMajorAxis,
		m_eccentricity,
		m_inclination,
		Physics::N_ORBIT_PTS
	);
}

void OrbitingBody::CalculateOrbitalSpeedVec(const Physics::Point3D& focusPt)
{
	m_orbitalSpeeds = Physics::OrbitalMechanics::CalculateOrbitalSpeeds(m_semiMajorAxis, m_mu, m_orbitalPoints, focusPt);
}
