#ifndef CELESTIALPHYSICS_ORBITALMECHANICS_HPP
#define CELESTIALPHYSICS_ORBITALMECHANICS_HPP


#include "OrbitalPoint.hpp"
#include <vector>


class OrbitalMechanics
{
public:
	OrbitalMechanics();
	~OrbitalMechanics();

	static std::vector<Point3D> CalculateOrbitPoints(double semiMajorAxis, double eccentricity, double inclination, int numPoints);
	static std::vector<Point3D> GenerateEllipticalOrbit(double semiMajorAxis,double eccentricity,double inclination, int numPoints);
	static double CalculateEccentricity(double semiMajorAxis, double semiMinorAxis);
	static double CalculateGravitationalParameter(double focusMass);
	static double CalculateOrbitalRadius(const Point3D& focusPt, const Point3D& bodyPoint);
	static double CalculateOrbitalSpeed(double orbitalRadius, double semiMajorAxis, double mu);

private:

};

#endif //CELESTIALPHYSICS_ORBITALMECHANICS_HPP
