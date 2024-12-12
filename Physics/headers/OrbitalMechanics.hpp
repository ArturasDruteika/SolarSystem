#ifndef PHYSICS_ORBITALMECHANICS_HPP
#define PHYSICS_ORBITALMECHANICS_HPP


#if defined (_WIN32) 
#if defined(PHYSICS_EXPORT)
#define PHYSICS_API __declspec(dllexport)
#else
#define PHYSICS_API __declspec(dllimport)
#endif /* PHYSICS_API */
#define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
//  GCC
#define PHYSICS_API __attribute__((visibility("default")))
#endif


#include "OrbitalPoint.hpp"
#include <vector>


class PHYSICS_API OrbitalMechanics
{
public:
	OrbitalMechanics();
	~OrbitalMechanics();

	static std::vector<Point3D> CalculateOrbitPoints(double semiMajorAxis, double eccentricity, double inclination, int numPoints);
	static std::vector<Point3D> GenerateEllipticalOrbit(double semiMajorAxis,double eccentricity,double inclination, int numPoints);
	static double CalculateEccentricity(double semiMajorAxis, double semiMinorAxis);
	static double CalculateGravitationalParameter(double focusMass);
	static double CalculateOrbitalRadius(const Point3D& focusPt, const Point3D& bodyPoint);
	static double CalculateOrbitalSpeed(double orbitalRadius, double semiMajorAxis, double mu);
	static std::vector<double> CalculateOrbitalSpeeds(
		double semiMajorAxis, 
		double gravitationalParameter, 
		const std::vector<Point3D>& orbitalPoints, 
		const Point3D& focusPt
	);

private:

};

#endif //PHYSICS_ORBITALMECHANICS_HPP
