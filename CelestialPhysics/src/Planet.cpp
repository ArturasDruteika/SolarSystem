#include "Planet.hpp"
#include "ObjectsComponents.hpp"
#include "ColorsVTK.hpp"
#include <boost/dll/runtime_symbol_info.hpp>
#include <cmath>


constexpr double EARTH_ROTATIONS_PER_YEAR = 365.2421897;


Planet::Planet(PlanetAttributes objectAttributes, int ptsInSingleOrbit)
	: m_planetAttributes{ objectAttributes }
	, m_rotationPerStep{ 0 }
	, m_speedAroundCenter{}
{
	Init(objectAttributes, ptsInSingleOrbit);
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
	RotateActor(m_rotationPerStep);
}

void Planet::Init(const PlanetAttributes& objectAttributes, int ptsInSingleOrbit)
{
	std::string currentPath = boost::dll::program_location().parent_path().string();
	ReadSTLFIle(currentPath + "/res/" + "spatial_body_prototype.stl");

	SetScale(objectAttributes.radius, objectAttributes.radius, objectAttributes.radius);
	SetColor(ColorsVTK::BLUE);
	SetActorInitialPos(objectAttributes.semiMajorAxis);
	RotateY(objectAttributes.tilt);

	m_rotationPerStep = CalculateRotationPerStep(objectAttributes.rotationalPeriod, ptsInSingleOrbit);
}

double Planet::CalculateRotationPerStep(double rotationalPeriod, int ptsInSingleOrbit)
{
	double rotationCoeffComperedToEarth = 1 / rotationalPeriod;
	double rotationsPerYear = EARTH_ROTATIONS_PER_YEAR * rotationCoeffComperedToEarth;
	double totalRotationDegreesPerYear = rotationsPerYear * 360;
	double rotationPerStep = totalRotationDegreesPerYear / ptsInSingleOrbit;
	return rotationPerStep;
}

void Planet::TiltPlanet(double tilt)
{
}
