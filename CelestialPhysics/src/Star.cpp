#include "Star.hpp"
#include "ColorsVTK.hpp"

Star::Star()
{
	Init();
}

Star::~Star()
{
}

vtkSmartPointer<vtkActor> Star::GetStarActor()
{
	return GetObjectActor();
}

void Star::Init()
{
	GenerateObject(1.0);
	SetColor(ColorsVTK::YELLOW);
	SetActorInitialPos();
}
