#include "OrbitalMechanics.hpp"
#include "spdlog/spdlog.h"
#include <cmath>
#include <string>


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

std::vector<Point3D> OrbitalMechanics::CalculateOrbitPoints(double semiMajorAxis, double semiMinorAxis, double inclination, int numPoints)
{
    std::vector<Point3D> points;
    double step = 2 * M_PI / numPoints; // Divide the orbit into equal intervals
    double i_rad = inclination * M_PI / 180.0; // Convert inclination angle to radians

    for (int n = 0; n < numPoints; ++n) 
    {
        double t = n * step;
        Point3D point;
        point.x = semiMajorAxis * cos(t);
        point.y = semiMinorAxis * sin(t) * cos(i_rad);
        point.z = semiMinorAxis * sin(t) * sin(i_rad);
        points.push_back(point);
    }
    return points;
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
