#include "Planet.hpp"
#include "ObjectsComponents.hpp"


Planet::Planet(ObjectAttributes objectAttributes)
	: m_planetAttributes{ objectAttributes }
{
	m_sphere.GenerateObject(m_planetAttributes.radius);
	m_sphere.SetActorInitialPos(objectAttributes.distanceFromCenter, 0.0);
}

Planet::~Planet()
{
}

vtkSmartPointer<vtkActor> Planet::GetPlanetActor()
{
	return m_sphere.GetObjectActor();
}

void Planet::MovePlanet(double xPos, double yPos, double zPos)
{
	m_sphere.MoveActor(xPos, yPos, zPos);
}
