#include "Star.hpp"
#include "ColorsVTK.hpp"

Star::Star(double starRadius)
{
	Init(starRadius);
}

Star::~Star()
{
}

vtkSmartPointer<vtkActor> Star::GetStarActor()
{
	return GetObjectActor();
}

void Star::Init(double starRadius)
{
	GenerateObject(starRadius);
	SetColor(ColorsVTK::YELLOW);
	SetActorInitialPos();
}
