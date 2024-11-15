#include "OrbitingBody.hpp"
#include <stdexcept>
#include <complex>


OrbitingBody::OrbitingBody(double radius, double mass, double semiMajorAxis, double semiMinorAxis)
	: CosmicBody(radius, mass)
	, m_semiMajorAxis{ semiMajorAxis }
	, m_semiMinorAxis{ semiMinorAxis }
{
	CalculateEccentricity();
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

void OrbitingBody::CalculateEccentricity()
{
	if (m_semiMajorAxis <= 0 || m_semiMinorAxis <= 0 || m_semiMinorAxis > m_semiMajorAxis)
	{
		throw std::invalid_argument("Semi-major axis (a) must be greater than semi-minor axis (b), and both must be positive.");
	}
	m_eccentricity = std::sqrt(1 - (m_semiMinorAxis * m_semiMinorAxis) / (m_semiMajorAxis * m_semiMajorAxis));
}
