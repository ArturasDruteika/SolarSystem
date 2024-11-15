#ifndef CELESTIALPHYSICS_ORBITALMECHANICS_HPP
#define CELESTIALPHYSICS_ORBITALMECHANICS_HPP


#include "OrbitalPoint.hpp"
#include <vector>


class OrbitalMechanics
{
public:
	OrbitalMechanics();
	~OrbitalMechanics();

	double CalculateDistanceToOrigin(double x, double y, double z);
	static std::vector<Point3D> CalculateOrbitPoints(double semiMajorAxis, double eccentricity, double inclination, int numPoints);

private:
	double CalculateNewTheta(int i, double incrementValue);
	double CalculateNewRadius(double semiMajorAxis, double eccentricity, double theta);
	std::vector<double> GetOrbitPointCoord(double radius, double fie, double theta);

};

#endif //CELESTIALPHYSICS_ORBITALMECHANICS_HPP
