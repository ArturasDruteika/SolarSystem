#include "Sphere.hpp"

#include <vtkCellArray.h>
#include <vtkFloatArray.h>
#include <vtkNamedColors.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkSTLReader.h>
#include <vtkActor.h>


constexpr int PHI_RESOLUTION = 15;
constexpr int THETA_RESOLUTION = 15;


Sphere::Sphere()
{
}

Sphere::~Sphere()
{
}

void Sphere::GenerateObject(double radius)
{
    vtkNew<vtkPolyDataMapper> sphereMapper;
    vtkNew<vtkSphereSource> sphere = GenerateSphereData(radius);
    sphereMapper->SetInputConnection(sphere->GetOutputPort());
    SetMapper(sphereMapper);
    SetActorInitialPos();
}

vtkNew<vtkSphereSource> Sphere::GenerateSphereData(double radius)
{
    // Create a sphere
    vtkNew<vtkSphereSource> sphereSource;
    sphereSource->SetCenter(0.0, 0.0, 0.0);
    sphereSource->SetRadius(radius);
    // Make the surface smooth.
    sphereSource->SetPhiResolution(PHI_RESOLUTION);
    sphereSource->SetThetaResolution(THETA_RESOLUTION);
    return sphereSource;
}
