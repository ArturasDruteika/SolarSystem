#ifndef CELESTIALPHYSICS_ORBITINGBODY_HPP
#define CELESTIALPHYSICS_ORBITINGBODY_HPP


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
#define OBJECTBASE_API __attribute__((visibility("default")))
#endif


#include "CosmicBody.hpp"
#include "OrbitalPoint.hpp"
#include <vector>


class CELESTIALPHYSICS_API OrbitingBody : public CosmicBody
{
public:
	OrbitingBody(
		double radius, 
		double mass, 
		const Point3D& focusObjectPt,
		double focusObjectMass,
		double semiMajorAxis, 
		double semiMinorAxis, 
		double rotationPeriod,
		double inclination
	);
	~OrbitingBody();

	double GetSemiMajorAxis() const;
	double GetSemiMinorAxis() const;
	double GetEccentricity() const;
	double GetInclination() const;
	double GetGravitationalParameter() const;
	double GetRotationalPeriod() const;
	const std::vector<Point3D>& GetOrbitalPoints() const;
	Point3D GetOrbitalPoints(int id) const;
	const std::vector<double>& GetOrbitalSpeeds() const;


private:
	void CalculateOrbitalPoints();
	void CalculateOrbitalSpeedVec(const Point3D& focusPt);

protected:
	double m_semiMajorAxis;
	double m_semiMinorAxis;
	double m_eccentricity;
	double m_inclination;
	double m_mu; // gravitational parameter
	double m_rotationalPeriod;
	std::vector<Point3D> m_orbitalPoints;
	std::vector<double> m_orbitalSpeeds;
	Point3D m_focusObjPoint;
};


#endif //CELESTIALPHYSICS_ORBITINGBODY_HPP