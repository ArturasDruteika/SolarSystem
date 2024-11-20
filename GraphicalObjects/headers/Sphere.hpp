#ifndef GRAPHICALOBJECTS_SPHERE_HPP
#define GRAPHICALOBJECTS_SPHERE_HPP


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


#include "ObjectBase.hpp"
#include "ColorsVTK.hpp"

#include <vtkActor.h>
#include <vtkNew.h>
#include <vtkTransform.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>
#include <vtkSphereSource.h>

#include <vector>


class GRAPHICALOBJECTS_API Sphere : public ObjectBase
{
public:
	Sphere(double radius, const std::vector<double>& initialPosCoord, const vtkColor4d& color);
	~Sphere();

	double GetRadius() const;
	vtkColor4d GetColor() const;

	// TODO: make GenerateCube() have arguments of shape paratmeters like xyz
	void GenerateObject(double radius) override;

private:
	void GenerateDefaultSphere(std::vector<double>& initialPosCoord);

	double m_radius;
	std::vector<double> m_initialPosCoord;
	vtkColor4d m_color;
	vtkNew<vtkSphereSource> GenerateSphereData(double radius);
};

#endif //GRAPHICALOBJECTS_SPHERE_HPP
