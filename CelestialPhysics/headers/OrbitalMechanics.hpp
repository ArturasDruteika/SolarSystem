#ifndef CELESTIALPHYSICS_ORBITALMECHANICS_HPP
#define CELESTIALPHYSICS_ORBITALMECHANICS_HPP


#include <vector>


class OrbitalMechanics
{
public:
	OrbitalMechanics();
	~OrbitalMechanics();

	std::vector<std::vector<double>> GenerateRotationCoords(double circleRadius, double theta, int resolution);

private:
	std::vector<double> GetSphereSurfarePointCoord(double radius, double fie, double theta);
};

#endif //CELESTIALPHYSICS_ORBITALMECHANICS_HPP
