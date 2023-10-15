#include "OrbitalMechanics.hpp"
#include <cmath>


constexpr double M_PI = 3.14159265358979323846;


OrbitalMechanics::OrbitalMechanics()
{
}

OrbitalMechanics::~OrbitalMechanics()
{
}


std::vector<std::vector<double>> OrbitalMechanics::GenerateOrbitPoints(double semiMajorAxis, double eccentricity, double inclination, int numPoints) {
	std::vector<std::vector<double>> orbitPoints;

	double incrementValue = 2.0 * M_PI / numPoints;

	for (int j = 0; j < numPoints; ++j) {
		double theta = CalculateNewTheta(j, incrementValue);
		double r = CalculateNewRadius(semiMajorAxis, eccentricity, theta);
		orbitPoints.push_back(GetOrbitPointCoord(r, theta, inclination));
	}

	return orbitPoints;
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
