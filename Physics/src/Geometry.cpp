#include "Geometry.hpp"
#include <cmath>
#include <stdexcept>


namespace Physics
{
    double Geometry::CalculateEuclidianDistance(const Point2D& pt1, const Point2D& pt2)
    {
        return std::sqrt(
            std::pow(pt2.x - pt1.x, 2) +
            std::pow(pt2.y - pt1.y, 2)
        );
    }

    double Geometry::CalculateEuclidianDistance(const Point3D& pt1, const Point3D& pt2)
    {
        return std::sqrt(
            std::pow(pt2.x - pt1.x, 2) +
            std::pow(pt2.y - pt1.y, 2) +
            std::pow(pt2.z - pt1.z, 2)
        );
    }

    double Geometry::CalculateEuclidianDistance(const std::vector<double>& pt1, const std::vector<double> pt2)
    {
        // Check if the points have the same number of dimensions
        if (pt1.size() != pt2.size())
        {
            throw std::invalid_argument("Points must have the same number of dimensions.");
        }

        double sum = 0.0;

        // Calculate the sum of squared differences
        for (size_t i = 0; i < pt1.size(); ++i)
        {
            sum += std::pow(pt1[i] - pt2[i], 2);
        }

        // Return the square root of the sum
        return std::sqrt(sum);
    }
    double Geometry::CalculateSemiMinorAxis(double semiMajorAxis, double eccentricity)
    {
        return semiMajorAxis * std::sqrt(1 - std::pow(eccentricity, 2));
    }
}
