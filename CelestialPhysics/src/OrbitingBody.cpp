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
	CalculateEccentricity();
	CalculateGravitationalParameter(focusObjectMass);
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

void OrbitingBody::CalculateEccentricity()
{
	if (m_semiMajorAxis <= 0 || m_semiMinorAxis <= 0 || m_semiMinorAxis > m_semiMajorAxis)
	{
		throw std::invalid_argument("Semi-major axis (a) must be greater than semi-minor axis (b), and both must be positive.");
	}
	m_eccentricity = std::sqrt(1 - (m_semiMinorAxis * m_semiMinorAxis) / (m_semiMajorAxis * m_semiMajorAxis));
}

void OrbitingBody::CalculateOrbitalPoints()
{
	m_orbitalPoints = OrbitalMechanics::CalculateOrbitPoints(
		m_semiMajorAxis,
		m_semiMinorAxis,
		m_inclination,
		N_ORBIT_PTS
	);
}

void OrbitingBody::CalculateGravitationalParameter(double focusObjectMass)
{
	m_mu = GRAVITATIONAL_CONSTANT * focusObjectMass;
}

double OrbitingBody::CalculateOrbitalRadius(const Point3D& focusPt, const Point3D& bodyPoint)
{
	return std::sqrt(
		std::pow(focusPt.x - bodyPoint.x, 2) +
		std::pow(focusPt.y - bodyPoint.y, 2) +
		std::pow(focusPt.z - bodyPoint.z, 2)
	);
}

double OrbitingBody::CalculateOrbitalSpeed(double orbitalRadius, double semiMajorAxis, double mu)
{
	return std::sqrt(mu * (2.0 / orbitalRadius - 1.0 / semiMajorAxis));
}

void OrbitingBody::CalculateOrbitalSpeedVec(const Point3D& focusPt)
{
	for (const Point3D& orbitalPt : m_orbitalPoints)
	{
		double orbitalRadius = CalculateOrbitalRadius(focusPt, orbitalPt);
		double orbitalSpeed = CalculateOrbitalSpeed(orbitalRadius, m_semiMajorAxis, m_mu);
		m_orbitalSpeeds.push_back(orbitalSpeed);
	}
}
