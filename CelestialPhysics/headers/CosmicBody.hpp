#ifndef CELESTIALPHYSICS_COSMICBODY_HPP
#define CELESTIALPHYSICS_COSMICBODY_HPP


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


class CELESTIALPHYSICS_API CosmicBody
{
public:
	CosmicBody(double radius, double mass);
	~CosmicBody();

	double GetRadius() const;
	double GetMass() const;

private:
	double m_radius;
	double m_mass;
};


#endif //CELESTIALPHYSICS_COSMICBODY_HPP