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
	double CalculateRotationPer1Step(double rotationalPeriod);

	double m_rotationPer1Step;

	PlanetAttributes m_planetAttributes;
	std::vector<std::pair<double, double>> xyCircularCoords;
};

#endif //CELESTIALPHYSICS_PLANETS_HPP
