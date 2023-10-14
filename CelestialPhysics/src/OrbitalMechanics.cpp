#include "OrbitalMechanics.hpp"

OrbitalMechanics::OrbitalMechanics()
{
}

OrbitalMechanics::~OrbitalMechanics()
{
}

std::vector<std::vector<double>> OrbitalMechanics::GenerateRotationCoords(double circleRadius, double theta, int resolution)
{
	std::vector<std::vector<double>> circleCoords;

	double angleFie = 90 - theta;
	double angleTheta = 0;
	double angularSpeed = 90.0 / resolution;

	double x, y, z = 0;
	std::vector<double> pointCoords{};

	for (int i = 0; i < resolution; i++)
	{
		pointCoords = GetSphereSurfarePointCoord(circleRadius, angleFie, angleTheta);
		circleCoords.push_back(pointCoords);
		angleTheta -= angularSpeed;
	}
	return circleCoords;
}

std::vector<double> OrbitalMechanics::GetSphereSurfarePointCoord(double radius, double fie, double theta)
{
	double x = radius * cos(theta);
	double y = radius * sin(theta);
	double z = radius * tan(fie) * sin(theta);
	std::vector<double> pointCoords{x, y, z};
	return pointCoords;
}
