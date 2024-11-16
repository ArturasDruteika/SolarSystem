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

private:

};

#endif //CELESTIALPHYSICS_ORBITALMECHANICS_HPP
