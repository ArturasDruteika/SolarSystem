#include "OrbitingBody.hpp"
#include "OrbitalMechanics.hpp"
#include "PhysicalConstants.hpp"
#include <stdexcept>
#include <complex>


namespace StellarSystem
{
	OrbitingBody::OrbitingBody(
		double radius, 
		double mass, 
		const Physics::Point3D& focusObjectPt,
		double focusObjectMass, 
		double aphelion, 
		double perihelion,
		double rotationPeriod,
		double inclination
	)
		: CosmicBody(radius, mass)
		, m_aphelion{ aphelion }
		, m_perihelion{ perihelion }
		, m_inclination{ inclination }
		, m_rotationalPeriod{ rotationPeriod }
		, m_semiMajorAxis{}
		, m_stepIterator{ 0 }
	{
		Init(focusObjectPt, focusObjectMass);
	}

	OrbitingBody::~OrbitingBody()
	{
	}

	double OrbitingBody::GetAphelion() const
	{
		return m_aphelion;
	}

	double OrbitingBody::GetPerihelion() const
	{
		return m_perihelion;
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

	double OrbitingBody::GetStepIterator() const
	{
		return m_stepIterator;
	}

	void OrbitingBody::UpdateStepIterator()
	{
		m_stepIterator += 1;
		if (m_stepIterator == Physics::N_ORBIT_PTS)
		{
			m_stepIterator = 0;
		}
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

	const double OrbitingBody::GetCurrentSpeed() const
	{
		return m_orbitalSpeeds[m_stepIterator];
	}

	void OrbitingBody::Init(const Physics::Point3D& focusObjectPt, double focusObjectMass)
	{
		m_semiMajorAxis = CalculateSemiMajorAxis(m_aphelion, m_perihelion);
		m_eccentricity = Physics::OrbitalMechanics::CalculateEccentricityUsingAphelion(m_semiMajorAxis, m_aphelion);
		m_semiMinorAxis = CalculateSemiMinorAxis(m_semiMajorAxis, m_eccentricity);
		m_mu = Physics::OrbitalMechanics::CalculateGravitationalParameter(focusObjectMass);
		m_orbitalPoints = Physics::OrbitalMechanics::CalculateElipticalOrbitPoints(
			m_semiMajorAxis,
			m_eccentricity,
			m_inclination,
			Physics::N_ORBIT_PTS
		);
		m_orbitalSpeeds = Physics::OrbitalMechanics::CalculateOrbitalSpeeds(m_semiMajorAxis, m_mu, m_orbitalPoints, focusObjectPt);
	}

	void OrbitingBody::CalculateOrbitalPoints()
	{
		m_orbitalPoints = Physics::OrbitalMechanics::CalculateElipticalOrbitPoints(
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

	double OrbitingBody::CalculateSemiMajorAxis(double aphelion, double perihelion)
	{
		return (aphelion + perihelion) / 2.0;
	}

	double OrbitingBody::CalculateSemiMinorAxis(double semiMajorAxis, double eccentricity)
	{
		return semiMajorAxis * std::sqrt(1 - std::pow(eccentricity, 2));
	}
}

