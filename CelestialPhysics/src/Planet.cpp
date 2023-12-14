#include "Planet.hpp"
#include "ObjectsComponents.hpp"
#include "ColorsVTK.hpp"
#include "OrbitalMechanics.hpp"
#include <cmath>


Planet::Planet(ObjectAttributes objectAttributes)
	: m_planetAttributes{ objectAttributes }
	, xyCircularCoords{}
	, m_orbitalPoints{}
{
	Init(objectAttributes);
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
	return GetObjectActor();
}

void Planet::MovePlanet(double xPos, double yPos, double zPos)
{
	MoveActor(xPos, yPos, zPos);
}

std::vector<Point3D> Planet::GetOrbitalPts()
{
	return m_orbitalPoints;
}

void Planet::Init(const ObjectAttributes& objectAttributes)
{
	GenerateObject(m_planetAttributes.radius);
	SetColor(ColorsVTK::BLUE);

	std::pair <double, double> xzCoords = CalculateInitialPosition(objectAttributes.semiMajorAxis, objectAttributes.tiltRadians);
	SetActorInitialPos(xzCoords.first, 0.0, xzCoords.second);
	m_orbitalPoints = OrbitalMechanics::CalculateOrbitPoints(objectAttributes.semiMajorAxis, objectAttributes.semiMinorAxis, 0, 10'000);
}

std::pair<double, double> Planet::CalculateInitialPosition(double radius, double theta)
{
	double xCoord = radius * cos(theta);
	double zCoord = radius * sin(theta);
	return std::make_pair(xCoord, zCoord);
}
