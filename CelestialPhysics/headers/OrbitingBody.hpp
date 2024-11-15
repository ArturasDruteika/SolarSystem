#ifndef CELESTIALPHYSICS_ORBITINGBODY_HPP
#define CELESTIALPHYSICS_ORBITINGBODY_HPP


#include "CosmicBody.hpp"


class OrbitingBody : public CosmicBody
{
public:
	OrbitingBody(double radius, double mass, double semiMajorAxis, double semiMinorAxis);
	~OrbitingBody();

	double GetSemiMajorAxis();
	double GetSemiMinorAxis();
	double GetEccentricity();

private:
	void CalculateEccentricity();

	double m_semiMajorAxis;
	double m_semiMinorAxis;
	double m_eccentricity;
};


#endif //CELESTIALPHYSICS_ORBITINGBODY_HPP