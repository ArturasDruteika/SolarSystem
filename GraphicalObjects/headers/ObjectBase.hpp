#ifndef GRAPHICALRENDERING_OBJECTBASE_HPP
#define GRAPHICALRENDERING_OBJECTBASE_HPP


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


#include <vtkActor.h>
#include <vtkNew.h>
#include <vtkTransform.h>
#include <vtkSmartPointer.h>


class GRAPHICALOBJECTS_API ObjectBase
{
public:
	ObjectBase();
	~ObjectBase();

	bool operator==(const ObjectBase& other) const = default;

	void MoveActor(vtkNew<vtkActor>& actor, double xPos, double yPos, double zPos);
	vtkNew<vtkActor> ReadSTLFIle(std::string pathToStlFile);

private:
	vtkSmartPointer<vtkTransform> m_transform;
};


#endif //GRAPHICALRENDERING_OBJECTBASE_HPP
