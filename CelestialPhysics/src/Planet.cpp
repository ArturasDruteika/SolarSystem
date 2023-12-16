#include "Planet.hpp"
#include "ObjectsComponents.hpp"
#include "ColorsVTK.hpp"
#include <cmath>


Planet::Planet(PlanetAttributes objectAttributes)
	: m_planetAttributes{ objectAttributes }
	, xyCircularCoords{}
{
	Init(objectAttributes);
}

Planet::~Planet()
{
}

PlanetAttributes Planet::GetPlanetAttributes()
{
	return m_planetAttributes;
}

vtkSmartPointer<vtkActor> Planet::GetPlanetActor()
{
	return GetObjectActor();
}

void Planet::MovePlanet(double xPos, double yPos, double zPos)
{
	MoveActor(xPos, yPos, zPos);
}

void Planet::Init(const PlanetAttributes& objectAttributes)
{
	GenerateObject(m_planetAttributes.radius);
	SetColor(ColorsVTK::BLUE);

	std::pair <double, double> xzCoords = CalculateInitialPosition(objectAttributes.semiMajorAxis, objectAttributes.tilt);
	SetActorInitialPos(xzCoords.first, 0.0, xzCoords.second);
}

std::pair<double, double> Planet::CalculateInitialPosition(double radius, double theta)
{
	double xCoord = radius * cos(theta);
	double zCoord = radius * sin(theta);
	return std::make_pair(xCoord, zCoord);
}
