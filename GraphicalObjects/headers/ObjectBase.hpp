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


class GRAPHICALOBJECTS_API ObjectBase
{
public:
	ObjectBase();
	~ObjectBase();

	bool operator==(const ObjectBase& other) const = default;

	vtkSmartPointer<vtkActor> GetObjectActor();
	std::vector<double> GetActorPosition(vtkSmartPointer<vtkActor>& actor);
	void MoveActor(double xPos, double yPos, double zPos);
	void SetMapper(vtkNew<vtkPolyDataMapper>& mapper);
	void SetActorInitialPos();

	void ReadSTLFIle(std::string pathToStlFile);

private:
	vtkSmartPointer<vtkActor> m_actor;
	vtkSmartPointer<vtkTransform> m_transform;
};


#endif //GRAPHICALOBJECTS_OBJECTBASE_HPP
