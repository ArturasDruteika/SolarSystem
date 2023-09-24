#ifndef GRAPHICALOBJECTS_CUBE_HPP
#define GRAPHICALOBJECTS_CUBE_HPP

#include "ObjectBase.hpp"

#include <vtkActor.h>
#include <vtkNew.h>
#include <vtkTransform.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>


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

class GRAPHICALOBJECTS_API Cube : public ObjectBase
{
public:
	Cube();
	~Cube();

	// TODO: make GenerateCube() have arguments of shape paratmeters like xyz
	void GenerateObject() override;

private:
	vtkNew<vtkPolyData> GenerateCubeData();
};

#endif //GRAPHICALOBJECTS_CUBE_HPP
