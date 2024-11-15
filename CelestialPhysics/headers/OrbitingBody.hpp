#ifndef CELESTIALPHYSICS_ORBITINGBODY_HPP
#define CELESTIALPHYSICS_ORBITINGBODY_HPP


#include "CosmicBody.hpp"
#include "OrbitalPoint.hpp"
#include <vector>


class OrbitingBody : public CosmicBody
{
public:
	OrbitingBody(
		double radius, 
		double mass, 
		const Point3D& focusObjectPt,
		double focusObjectMass,
		double semiMajorAxis, 
		double semiMinorAxis, 
		double inclination
	);
	~OrbitingBody();

	double GetSemiMajorAxis();
	double GetSemiMinorAxis();
	double GetEccentricity();
	double GetInclination();
	double GetGravitationalParameter();
	std::vector<Point3D> GetOrbitalPoints();
	std::vector<double> GetOrbitalSpeeds()


private:
	void CalculateEccentricity();
	void CalculateOrbitalPoints();
	void CalculateGravitationalParameter(double focusObjectMass);
	double CalculateOrbitalRadius(const Point3D& focusPt, const Point3D& bodyPoint);
	double CalculateOrbitalSpeed(double orbitalRadius, double semiMajorAxis, double mu);
	void CalculateOrbitalSpeedVec(const Point3D& focusPt);

	double m_semiMajorAxis;
	double m_semiMinorAxis;
	double m_eccentricity;
	double m_inclination;
	double m_mu; // gravitational parameter
	std::vector<Point3D> m_orbitalPoints;
	std::vector<double> m_orbitalSpeeds;
	Point3D m_focusObjPoint;
};


#endif //CELESTIALPHYSICS_ORBITINGBODY_HPP