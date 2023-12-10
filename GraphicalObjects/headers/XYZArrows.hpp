#ifndef GRAPHICALOBJECTS_XYZARROWS_HPP
#define GRAPHICALOBJECTS_XYZARROWS_HPP


#if defined (_WIN32)
#if defined(GRAPHICALOBJECTS_EXPORT)
#define GRAPHICALOBJECTS_API __declspec(dllexport)
#else
#define  GRAPHICALOBJECTS_API __declspec(dllimport)
#endif /* GRAPHICALOBJECTS_API */
#define _sprintf sprintf_s
#endif


#include "ObjectBase.hpp"
#include <vtkGenericRenderWindowInteractor.h>
#include <vtkCameraOrientationWidget.h>
#include "vtkRenderer.h"


#if defined(__GNUC__)
//  GCC
#define CUBE_API __attribute__((visibility("default")))
#endif

class GRAPHICALOBJECTS_API XYZArrows
{
public:
	XYZArrows();
	~XYZArrows();

	void AddOrientationArrowsOnRenderer(vtkSmartPointer<vtkRenderer> renderer, vtkSmartPointer<vtkCameraOrientationWidget>& camOrientManipulator);
	
private:
	vtkSmartPointer<vtkCameraOrientationWidget> m_camOrientManipulator;
};

#endif //GRAPHICALOBJECTS_XYZARROWS_HPP
