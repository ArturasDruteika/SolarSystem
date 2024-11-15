#include "PhysicalConstants.hpp"
#include "OrbitalMechanics.hpp"
#include "spdlog/spdlog.h"
#include <cmath>
#include <string>



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

std::vector<Point3D> OrbitalMechanics::CalculateOrbitPoints(double semiMajorAxis, double eccentricity, double inclination, int numPoints)
{
    std::vector<Point3D> points;

    // Calculate semi-minor axis and focal distance
    double semiMinorAxis = semiMajorAxis * std::sqrt(1 - eccentricity * eccentricity);
    double focalDistance = semiMajorAxis * eccentricity; // Distance from center to focus

    // Step size for dividing the orbit into equal intervals
    double step = 2 * M_PI / numPoints;

    for (int n = 0; n < numPoints; ++n)
    {
        // True anomaly (angle around the orbit in radians)
        double t = n * step;

        // Parametric equations for an ellipse with a focal offset
        double x = semiMajorAxis * std::cos(t) + focalDistance;  // Shift x by focal distance
        double y = semiMinorAxis * std::sin(t);                  // Y-coordinate in orbital plane

        // Account for orbital inclination to project into 3D space
        Point3D point;
        point.x = x;                            // X-coordinate remains unchanged
        point.y = y * std::cos(inclination);    // Y-coordinate adjusted for inclination
        point.z = y * std::sin(inclination);    // Z-coordinate comes from inclination

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
