#ifndef CELESTIALPHYSICS_STAR_HPP
#define CELESTIALPHYSICS_STAR_HPP


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

class CELESTIALPHYSICS_API Star : public Sphere
{
public:
	Star();
	~Star();

	vtkSmartPointer<vtkActor> GetStarActor();

private:

};

#endif //CELESTIALPHYSICS_STAR_HPP