#include "PhysicalConstants.hpp"
#include "OrbitalMechanics.hpp"
#include "Geometry.hpp"
#include "spdlog/spdlog.h"
#include <cmath>
#include <string>


namespace Physics
{
    double OrbitalMechanics::CalculateEccentricity(double semiMajorAxis, double semiMinorAxis)
    {
        if (semiMajorAxis <= 0 || semiMinorAxis <= 0 || semiMinorAxis > semiMajorAxis)
        {
            throw std::invalid_argument("Semi-major axis (a) must be greater than semi-minor axis (b), and both must be positive.");
            return -1;
        }
        return std::sqrt(1 - (semiMinorAxis * semiMinorAxis) / (semiMajorAxis * semiMajorAxis));
    }

    double OrbitalMechanics::CalculateEccentricityUsingAphelion(double semiMajorAxis, double aphelion)
    {
        return (aphelion - semiMajorAxis) / semiMajorAxis;
    }

    double OrbitalMechanics::CalculateGravitationalParameter(double centralBodyMass)
    {
        return GRAVITATIONAL_CONSTANT * centralBodyMass;
    }

    double OrbitalMechanics::CalculateOrbitalSpeed(double orbitalRadius, double semiMajorAxis, double massCentralBody, double gravitationalParameter)
    {
        return std::sqrt(gravitationalParameter * massCentralBody * (2.0 / orbitalRadius - 1.0 / semiMajorAxis));
    }

    double OrbitalMechanics::CalculateOrbitalSpeed(double orbitalRadius, double semiMajorAxis, double mu)
    {
        return std::sqrt(mu * (2.0 / orbitalRadius - 1.0 / semiMajorAxis));
    }

    std::vector<double> OrbitalMechanics::CalculateOrbitalSpeeds(
        double semiMajorAxis,
        double gravitationalParameter,
        const std::vector<Point3D>& orbitalPoints,
        const Point3D& focusPt
    )
    {
        std::vector<double> orbitalSpeeds;
        for (const Point3D& orbitalPt : orbitalPoints)
        {
            double orbitalRadius = Geometry::CalculateEuclidianDistance(focusPt, orbitalPt);
            double orbitalSpeed = CalculateOrbitalSpeed(orbitalRadius, semiMajorAxis, gravitationalParameter);
            orbitalSpeeds.push_back(orbitalSpeed);
        }
        return orbitalSpeeds;
    }

    double OrbitalMechanics::CalculateOrbitalPeriod(double semiMajorAxis, double massOfCentralBody)
    {
        return 2 * M_PI * std::sqrt(std::pow(semiMajorAxis, 3) / (GRAVITATIONAL_CONSTANT * massOfCentralBody));
    }

    Point3D OrbitalMechanics::CalculatePosition(double semiMajorAxis, double eccentricity, double inclination, double trueAnomaly)
    {
        // Radius at current true anomaly
        double radius = semiMajorAxis * (1 - eccentricity * eccentricity) / (1 + eccentricity * std::cos(trueAnomaly));

        // Position in orbital plane
        double xPlane = radius * std::cos(trueAnomaly);
        double yPlane = radius * std::sin(trueAnomaly);

        // Convert to 3D space considering inclination
        Point3D pos;
        pos.x = xPlane;
        pos.y = yPlane * std::cos(inclination);
        pos.z = yPlane * std::sin(inclination);

        return pos;
    }

    std::vector<Point3D> OrbitalMechanics::CalculateElipticalOrbitPoints(double semiMajorAxis, double eccentricity, double inclination, int nSteps)
    {
        std::vector<Point3D> elipticalOrbitPts;
        elipticalOrbitPts.reserve(nSteps);

        for (int i = 0; i < nSteps; i++)
        {
            double trueAnomaly = 2 * M_PI * i / nSteps; // Divide orbit into equal angles
            Point3D pos = CalculatePosition(semiMajorAxis, eccentricity, inclination, trueAnomaly);
            elipticalOrbitPts.push_back(pos);
        }
        return elipticalOrbitPts;
    }

    std::vector<double> OrbitalMechanics::CalculateTravelTimesBetweenPoints(const std::vector<Point3D>& points, const std::vector<double>& speeds)
    {
        // Validate input sizes
        if (points.size() != speeds.size()) {
            throw std::invalid_argument("Points and speeds vectors must have the same size.");
        }

        std::vector<double> travelTimes;
        travelTimes.reserve(points.size() - 1);

        // Loop through the points to calculate travel times
        for (size_t i = 0; i < points.size() - 1; ++i) 
        {
            double distance = Geometry::CalculateEuclidianDistance(points[i], points[i + 1]);
            double time = distance / speeds[i]; // Assuming speed is constant for the segment
            travelTimes.push_back(time);
        }

        return travelTimes;
    }
}