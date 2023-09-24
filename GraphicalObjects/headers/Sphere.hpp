#ifndef GRAPHICALOBJECTS_SPHERE_HPP
#define GRAPHICALOBJECTS_SPHERE_HPP

#include "ObjectBase.hpp"

#include <vtkActor.h>
#include <vtkNew.h>
#include <vtkTransform.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>


#if defined (_WIN32)
#if defined(GRAPHICALOBJECTS_EXPORT)
#define GRAPHICALOBJECTS_API __declspec(dllexport)
#else
#define  GRAPHICALOBJECTS_API __declspec(dllimport)
#endif /* GRAPHICALOBJECTS_API */
#define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
//  GCC
#define CUBE_API __attribute__((visibility("default")))
#endif

class GRAPHICALOBJECTS_API Sphere : public ObjectBase
{
public:
	Sphere();
	~Sphere();

	// TODO: make GenerateCube() have arguments of shape paratmeters like xyz
	void GenerateSphere();

private:
	vtkNew<vtkSphereSource> GenerateSphereData();
};

#endif //GRAPHICALOBJECTS_SPHERE_HPP
