#include "Star.hpp"

Star::Star()
{
}

Star::~Star()
{
}

vtkSmartPointer<vtkActor> Star::GetStarActor()
{
	return GetObjectActor();
}
