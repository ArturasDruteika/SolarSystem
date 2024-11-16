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

double OrbitalMechanics::CalculateEccentricity(double semiMajorAxis, double semiMinorAxis)
{
    if (semiMajorAxis <= 0 || semiMinorAxis <= 0 || semiMinorAxis > semiMajorAxis)
    {
        throw std::invalid_argument("Semi-major axis (a) must be greater than semi-minor axis (b), and both must be positive.");
        return -1;
    }
    return std::sqrt(1 - (semiMinorAxis * semiMinorAxis) / (semiMajorAxis * semiMajorAxis));
}

double OrbitalMechanics::CalculateGravitationalParameter(double focusMass)
{
    return GRAVITATIONAL_CONSTANT * focusMass;
}

double OrbitalMechanics::CalculateOrbitalRadius(const Point3D& focusPt, const Point3D& bodyPoint)
{
    return std::sqrt(
        std::pow(focusPt.x - bodyPoint.x, 2) +
        std::pow(focusPt.y - bodyPoint.y, 2) +
        std::pow(focusPt.z - bodyPoint.z, 2)
    );
}

double OrbitalMechanics::CalculateOrbitalSpeed(double orbitalRadius, double semiMajorAxis, double mu)
{
    return std::sqrt(mu * (2.0 / orbitalRadius - 1.0 / semiMajorAxis));
}
