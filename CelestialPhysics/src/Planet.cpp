#include "Planet.hpp"
#include "ObjectsComponents.hpp"
#include "ColorsVTK.hpp"
#include <boost/dll/runtime_symbol_info.hpp>
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

void Planet::RotatePlanet()
{
	RotateActor(m_planetAttributes.tilt);
}

void Planet::Init(const PlanetAttributes& objectAttributes)
{
	std::string currentPath = boost::dll::program_location().parent_path().string();
	ReadSTLFIle(currentPath + "/res/" + "spatial_body_prototype.stl");

	SetScale(objectAttributes.radius, objectAttributes.radius, objectAttributes.radius);
	SetColor(ColorsVTK::BLUE);
	SetActorInitialPos(objectAttributes.semiMajorAxis);
}
