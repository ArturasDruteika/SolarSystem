#include "Star.hpp"
#include "ColorsVTK.hpp"
#include <boost/dll/runtime_symbol_info.hpp>


constexpr int SUN_SCALE_FACTOR = 4;


Star::Star(double radius, double mass)
	: CosmicBody(radius, mass)
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
	std::string currentPath = boost::dll::program_location().parent_path().string();
	ReadSTLFIle(currentPath + "/res/" + "spatial_body_prototype.stl");
	SetScale(SUN_SCALE_FACTOR, SUN_SCALE_FACTOR, SUN_SCALE_FACTOR);
	SetColor(ColorsVTK::YELLOW);
	SetActorInitialPos();
}
