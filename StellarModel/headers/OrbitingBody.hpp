#ifndef STELLARMODEL_ORBITINGBODY_HPP
#define STELLARMODEL_ORBITINGBODY_HPP


#if defined(_WIN32)
    #if defined(STELLARMODEL_EXPORT)
        #define STELLARMODEL_API __declspec(dllexport)
    #else
        #define STELLARMODEL_API __declspec(dllimport)
    #endif /* STELLARMODEL_API */
    #define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
    // GCC
    #define STELLARMODEL_API __attribute__((visibility("default")))
#endif


#include "CosmicBody.hpp"
#include "OrbitalPoint.hpp"
#include <vector>


namespace StellarSystem
{
	class STELLARMODEL_API OrbitingBody : public CosmicBody
	{
	public:
		OrbitingBody(
			double radius, 
			double mass, 
			const Physics::Point3D& focusObjectPt,
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
		const std::vector<Physics::Point3D>& GetOrbitalPoints() const;
		Physics::Point3D GetOrbitalPoints(int id) const;
		const std::vector<double>& GetOrbitalSpeeds() const;


	private:
		void CalculateOrbitalPoints();
		void CalculateOrbitalSpeedVec(const Physics::Point3D& focusPt);

	protected:
		double m_semiMajorAxis;
		double m_semiMinorAxis;
		double m_eccentricity;
		double m_inclination;
		double m_mu; // gravitational parameter
		double m_rotationalPeriod;
		std::vector<Physics::Point3D> m_orbitalPoints;
		std::vector<double> m_orbitalSpeeds;
		Physics::Point3D m_focusObjPoint;
	};
}



#endif //STELLARMODEL_ORBITINGBODY_HPP