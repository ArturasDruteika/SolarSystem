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

		double GetAphelion() const;
		double GetPerihelion() const;
		double GetSemiMajorAxis() const;
		double GetSemiMinorAxis() const;
		double GetEccentricity() const;
		double GetInclination() const;
		double GetGravitationalParameter() const;
		double GetRotationalPeriod() const;
		double GetStepIterator() const;
		void UpdateStepIterator();
		const std::vector<Physics::Point3D>& GetOrbitalPoints() const;
		Physics::Point3D GetOrbitalPoints(int id) const;
		const std::vector<double>& GetOrbitalSpeeds() const;
		double GetCurrentSpeed() const;
		const std::vector<double>& GetOrbitalTravelTimesBetweenPoints() const;
		double GetCurrentTime() const;


	private:
		void Init(const Physics::Point3D& focusObjectPt, double focusObjectMass);
		void CalculateOrbitalPoints();
		void CalculateOrbitalSpeedVec(const Physics::Point3D& focusPt);
		double CalculateSemiMajorAxis(double aphelion, double perihelion);

	protected:
		double m_aphelion;
		double m_perihelion;
		double m_semiMajorAxis;
		double m_semiMinorAxis;
		double m_eccentricity;
		double m_inclination;
		double m_mu; // gravitational parameter
		double m_rotationalPeriod;
		int m_stepIterator;
		std::vector<Physics::Point3D> m_orbitalPoints;
		std::vector<double> m_orbitalSpeeds;
		std::vector<double> m_orbitalTravelTimesBetweenPoints;
		Physics::Point3D m_focusObjPoint;
	};
}



#endif //STELLARMODEL_ORBITINGBODY_HPP