#include "OrbitingBody.hpp"
#include "OrbitalMechanics.hpp"
#include "PhysicalConstants.hpp"
#include <stdexcept>
#include <complex>


constexpr double N_ORBIT_PTS = 10'000;


OrbitingBody::OrbitingBody(
	double radius, 
	double mass, 
	const Point3D& focusObjectPt,
	double focusObjectMass, 
	double semiMajorAxis, 
	double semiMinorAxis, 
	double inclination
)
	: CosmicBody(radius, mass)
	, m_semiMajorAxis{ semiMajorAxis }
	, m_semiMinorAxis{ semiMinorAxis }
	, m_inclination{ inclination }
{
	m_eccentricity = OrbitalMechanics::CalculateEccentricity(m_semiMajorAxis, m_semiMinorAxis);
	m_mu = OrbitalMechanics::CalculateGravitationalParameter(focusObjectMass);
	CalculateOrbitalPoints();
	CalculateOrbitalSpeedVec(focusObjectPt);
}

OrbitingBody::~OrbitingBody()
{
}

double OrbitingBody::GetSemiMajorAxis()
{
	return m_semiMajorAxis;
}

double OrbitingBody::GetSemiMinorAxis()
{
	return m_semiMinorAxis;
}

double OrbitingBody::GetEccentricity()
{
	return m_eccentricity;
}

double OrbitingBody::GetInclination()
{
	return m_inclination;
}

double OrbitingBody::GetGravitationalParameter()
{
	return m_mu;
}

std::vector<Point3D> OrbitingBody::GetOrbitalPoints()
{
	return m_orbitalPoints;
}

std::vector<double> OrbitingBody::GetOrbitalSpeeds()
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
