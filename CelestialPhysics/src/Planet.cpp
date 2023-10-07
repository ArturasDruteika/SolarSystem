#include "Planet.hpp"
#include "ObjectsComponents.hpp"


Planet::Planet(ObjectAttributes objectAttributes)
	: m_planetAttributes{ objectAttributes }
	, xyCircularCoords{}
{
	m_sphere.GenerateObject(m_planetAttributes.radius);
	m_sphere.SetActorInitialPos(objectAttributes.distanceFromCenter, 0.0);
}

Planet::~Planet()
{
}

ObjectAttributes Planet::GetPlanetAttributes()
{
	return m_planetAttributes;
}

vtkSmartPointer<vtkActor> Planet::GetPlanetActor()
{
	return m_sphere.GetObjectActor();
}

void Planet::MovePlanet(double xPos, double yPos, double zPos)
{
	m_sphere.MoveActor(xPos, yPos, zPos);
}

std::vector<std::pair<double, double>> Planet::GenerateCircleXYPointsVec(double distanceFromCenter, double resolution)
{
	std::vector<std::pair<double, double>> circlePoints;
	double angle = 0;
	double rotationSpeed = 90.0 / resolution;

	for (int i = 0; i < resolution; i++)
	{
		// Calculate the position of the sphere
		double sphereX = distanceFromCenter * cos(angle) / 100;
		double sphereY = distanceFromCenter * sin(angle) / 100;
		std::pair<double, double> xyCoords(sphereX, sphereY);
		circlePoints.push_back(xyCoords);
		angle += rotationSpeed;
	}
	return circlePoints;
}
