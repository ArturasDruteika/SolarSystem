#ifndef CELESTIALPHYSICS_PLANETS_HPP
#define CELESTIALPHYSICS_PLANETS_HPP


#if defined (_WIN32)
#if defined(CELESTIALPHYSICS_EXPORT)
#define CELESTIALPHYSICS_API __declspec(dllexport)
#else
#define  CELESTIALPHYSICS_API __declspec(dllimport)
#endif /* CELESTIALPHYSICS_API */
#define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
//  GCC
#define Planet_API __attribute__((visibility("default")))
#endif


#include "Sphere.hpp"
#include "ObjectsComponents.hpp"
#include <utility>


class CELESTIALPHYSICS_API Planet : public Sphere
{
public:
	Planet(PlanetAttributes objectAttributes);
	~Planet();

	PlanetAttributes GetPlanetAttributes();
	vtkSmartPointer<vtkActor> GetPlanetActor();
	void MovePlanet(double xPos, double yPos, double zPos);
	void RotatePlanet();

private:
	void Init(const PlanetAttributes& objectAttributes);
	// Function returns ONLY x and z coords, since at the time of creation the y coord is always 0 (ZERO)
	// theta is the same as the tilt (the angle between the x and z axis
	// Theta is in Radians
	std::pair<double, double> CalculateInitialPosition(double radius, double theta);

	PlanetAttributes m_planetAttributes;
	std::vector<std::pair<double, double>> xyCircularCoords;
};

#endif //CELESTIALPHYSICS_PLANETS_HPP
