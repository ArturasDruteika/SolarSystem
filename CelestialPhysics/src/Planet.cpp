#include "PhysicalConstants.hpp"
#include "Planet.hpp"
#include "ObjectsComponents.hpp"
#include "ColorsVTK.hpp"
#include <boost/dll/runtime_symbol_info.hpp>
#include <cmath>



Planet::Planet(
	PlanetAttributes planetAttributes,
	const Point3D& focusObjectPt,
	double focusObjectMass, 
	int ptsInSingleOrbit
)
	: OrbitingBody(
		planetAttributes.radius,
		planetAttributes.mass, 
		focusObjectPt,
		focusObjectMass,
		planetAttributes.semiMajorAxis, 
		planetAttributes.semiMinorAxis,
		planetAttributes.inclination
	)
	, m_planetAttributes{ planetAttributes }
	, m_rotationPerStep{ 0 }
	, m_speedAroundCenter{}
{
	Init(planetAttributes, ptsInSingleOrbit);
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

void Planet::Init(const PlanetAttributes& planetAttributes, int ptsInSingleOrbit)
{
	std::string currentPath = boost::dll::program_location().parent_path().string();
	ReadSTLFIle(currentPath + "/res/" + "spatial_body_prototype.stl");

	SetScale(planetAttributes.radius, planetAttributes.radius, planetAttributes.radius);
	SetColor(ColorsVTK::BLUE);
	SetActorInitialPos(planetAttributes.semiMajorAxis);
	RotateY(planetAttributes.tilt);

	m_rotationPerStep = CalculateRotationPerStep(planetAttributes.rotationalPeriod, ptsInSingleOrbit);
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
