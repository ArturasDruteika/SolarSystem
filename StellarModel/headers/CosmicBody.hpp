#ifndef STELLARMODEL_COSMICBODY_HPP
#define STELLARMODEL_COSMICBODY_HPP


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



namespace StellarSystem
{
	class STELLARMODEL_API CosmicBody
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
}


#endif //STELLARMODEL_COSMICBODY_HPP