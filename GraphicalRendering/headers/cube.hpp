#ifndef SOLARSYSTEMSETUP_CUBE_HPP
#define SOLARSYSTEMSETUP_CUBE_HPP

#include <vtkActor.h>
#include <vtkNew.h>
#include <vtkTransform.h>
#include <vtkSmartPointer.h>
#include <vtkPolyData.h>


#if defined (_WIN32)
#if defined(GRAPHICALRENDERING_EXPORT)
#define GRAPHICALRENDERING_API __declspec(dllexport)
#else
#define  GRAPHICALRENDERING_API __declspec(dllimport)
#endif /* GRAPHICALRENDERING_API */
#define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
//  GCC
#define CUBE_API __attribute__((visibility("default")))
#endif

class GRAPHICALRENDERING_API Cube
{
public:
	Cube();
	~Cube();

	vtkNew<vtkActor> GenerateCube();
	vtkNew<vtkActor> ReadSTLFIle(std::string pathToStlFile);
	std::vector<double> GetActorPosition(vtkNew<vtkActor>& actor);
	void MoveActor(vtkNew<vtkActor>& actor, double xPos, double yPos, double zPos);

	void TestFunc();

private:
	vtkNew<vtkPolyData> GenerateCubeData();
	void SetCubeInitialPos(vtkNew<vtkActor>& actor);

	vtkSmartPointer<vtkTransform> m_transform;
};

#endif //SOLARSYSTEMSETUP_CUBE_HPP
