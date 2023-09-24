#ifndef SOLARSYSTEMSETUP_CUBE_HPP
#define SOLARSYSTEMSETUP_CUBE_HPP

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

	bool operator==(const Cube& other) const = default;

	vtkNew<vtkActor> GenerateCube();
	std::vector<double> GetActorPosition(vtkNew<vtkActor>& actor);

	void TestFunc();

private:
	vtkNew<vtkPolyData> GenerateCubeData();
	void SetCubeInitialPos(vtkNew<vtkActor>& actor);

};

#endif //SOLARSYSTEMSETUP_CUBE_HPP
