#include "XYZArrows.hpp"
#include <vtkAxesActor.h>
#include <vtkCameraOrientationWidget.h>

XYZArrows::XYZArrows()
{
	m_camOrientManipulator = vtkSmartPointer<vtkCameraOrientationWidget>::New();
}

XYZArrows::~XYZArrows()
{
}

// TODO: find a solution for this problem.
void XYZArrows::AddOrientationArrowsOnRenderer(vtkSmartPointer<vtkRenderer> renderer, vtkSmartPointer<vtkCameraOrientationWidget>& camOrientManipulator)
{
	if (renderer == nullptr)
	{
		std::cerr << "Renderer or interactor is not initialized." << std::endl;
		return;
	}

	//vtkSmartPointer<vtkCameraOrientationWidget> camOrientManipulator = vtkSmartPointer<vtkCameraOrientationWidget>::New();
	camOrientManipulator->SetParentRenderer(renderer);
	// Enable the widget.
	camOrientManipulator->On();
}
