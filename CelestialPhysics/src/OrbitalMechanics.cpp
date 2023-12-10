#include "OrbitalMechanics.hpp"
#include <cmath>


constexpr double M_PI = 3.14159265358979323846;


OrbitalMechanics::OrbitalMechanics()
{
}

OrbitalMechanics::~OrbitalMechanics()
{
}

double OrbitalMechanics::CalculateDistanceToOrigin(double x, double y, double z)
{
	double distance = std::sqrt(x * x + y * y + z * z);
	return distance;
}

double OrbitalMechanics::CalculateNewTheta(int i, double incrementValue)
{
	return i * incrementValue;
}

double OrbitalMechanics::CalculateNewRadius(double semiMajorAxis, double eccentricity, double theta)
{
	return semiMajorAxis * (1 - eccentricity * eccentricity) / (1 + eccentricity * std::cos(theta));
}

std::vector<double> OrbitalMechanics::GetOrbitPointCoord(double radius, double theta, double fie)
{
	double x = radius * std::cos(theta);
	double y = radius * std::sin(theta);
	double z = radius * std::sin(fie) * std::sin(theta);
	return { x, y, z };
}
