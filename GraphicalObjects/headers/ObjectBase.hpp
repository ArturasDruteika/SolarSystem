#ifndef GRAPHICALOBJECTS_OBJECTBASE_HPP
#define GRAPHICALOBJECTS_OBJECTBASE_HPP


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
#define OBJECTBASE_API __attribute__((visibility("default")))
#endif


#include <vtkActor.h>
#include <vtkNew.h>
#include <vtkTransform.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkAxesActor.h>
#include <vtkColor.h>


class GRAPHICALOBJECTS_API ObjectBase
{
public:
	ObjectBase();
	~ObjectBase();

	bool operator==(const ObjectBase& other) const = default;

	virtual void GenerateObject(double) = 0;

	vtkSmartPointer<vtkActor> GetObjectActor();
	vtkSmartPointer<vtkAxesActor> GetArrowActor();
	std::vector<double> GetActorPosition(vtkSmartPointer<vtkActor>& actor);
	void MoveActor(double xPos, double yPos, double zPos);
	void SetMapper(vtkNew<vtkPolyDataMapper>& mapper);
	void SetArrowActor(vtkNew<vtkAxesActor>& axes);
	void SetActorInitialPos(double xPos=0.0, double yPos=0.0, double zPos=0.0);
	void ReadSTLFIle(std::string pathToStlFile);
	void SetColor(const vtkColor4d& color);

private:
	vtkSmartPointer<vtkActor> m_actor;
	vtkSmartPointer<vtkAxesActor> m_axes;
	vtkSmartPointer<vtkTransform> m_transform;
};


#endif //GRAPHICALOBJECTS_OBJECTBASE_HPP
