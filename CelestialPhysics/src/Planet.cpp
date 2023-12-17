#include "Planet.hpp"
#include "ObjectsComponents.hpp"
#include "ColorsVTK.hpp"
#include <boost/dll/runtime_symbol_info.hpp>
#include <cmath>


constexpr double EARTH_ROTATIONS_PER_YEAR = 365.2421897;


Planet::Planet(PlanetAttributes objectAttributes)
	: m_planetAttributes{ objectAttributes }
	, xyCircularCoords{}
	, m_rotationPer1Step{ 0 }
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
	RotateActor(m_rotationPer1Step);
}

void Planet::Init(const PlanetAttributes& objectAttributes)
{
	std::string currentPath = boost::dll::program_location().parent_path().string();
	ReadSTLFIle(currentPath + "/res/" + "spatial_body_prototype.stl");

	SetScale(objectAttributes.radius, objectAttributes.radius, objectAttributes.radius);
	SetColor(ColorsVTK::BLUE);
	SetActorInitialPos(objectAttributes.semiMajorAxis);

	m_rotationPer1Step = CalculateRotationPer1Step(objectAttributes.rotationalPeriod);
}

double Planet::CalculateRotationPer1Step(double rotationalPeriod)
{
	double rotationCoeffComperedToEarth = 1 / rotationalPeriod;
	double rotationsPerYear = EARTH_ROTATIONS_PER_YEAR * rotationCoeffComperedToEarth;
	double totalRotationDegreesPerYear = rotationsPerYear * 360;
	double rotationPerStep = totalRotationDegreesPerYear / 10'000;
	return rotationPerStep;
}
