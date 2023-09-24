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


Sphere::Sphere()
{
}

Sphere::~Sphere()
{
}

void Sphere::GenerateObject()
{
    vtkNew<vtkPolyDataMapper> sphereMapper;
    vtkNew<vtkSphereSource> sphere = GenerateSphereData();
    sphereMapper->SetInputConnection(sphere->GetOutputPort());
    SetMapper(sphereMapper);
    SetActorInitialPos();
}

vtkNew<vtkSphereSource> Sphere::GenerateSphereData()
{
    vtkNew<vtkNamedColors> colors;

    // Create a sphere
    vtkNew<vtkSphereSource> sphereSource;
    sphereSource->SetCenter(0.0, 0.0, 0.0);
    sphereSource->SetRadius(1.0);
    // Make the surface smooth.
    sphereSource->SetPhiResolution(100);
    sphereSource->SetThetaResolution(100);

    return sphereSource;
}
