#ifndef PHYSICS_MATHFUNCS_HPP
#define PHYSICS_MATHFUNCS_HPP


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


namespace Physics
{
	class PHYSICS_API Geometry
	{
	public:
		double CalculateEuclidianDistance(const Point2D& pt1, const Point2D& pt2);
		double CalculateEuclidianDistance(const Point3D& pt1, const Point3D& pt2);
		double CalculateEuclidianDistance(const std::vector<double>& pt1, const std::vector<double> pt2);
	};
}


#endif //PHYSICS_MATHFUNCS_HPP