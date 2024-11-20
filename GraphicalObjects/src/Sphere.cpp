#include "Sphere.hpp"

#include <boost/dll/runtime_symbol_info.hpp>

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


Sphere::Sphere(double radius, const std::vector<double>& initialPosCoord, const vtkColor4d& color)
    : m_radius{ radius }
    , m_color{ color }
{
    GenerateDefaultSphere(initialPosCoord);
}

Sphere::~Sphere()
{
}

double Sphere::GetRadius() const
{
    return m_radius;
}

vtkColor4d Sphere::GetColor() const
{
    return m_color;
}

void Sphere::GenerateObject(double radius)
{
    vtkNew<vtkPolyDataMapper> sphereMapper;
    vtkNew<vtkSphereSource> sphere = GenerateSphereData(radius);
    sphereMapper->SetInputConnection(sphere->GetOutputPort());
    SetMapper(sphereMapper);
    SetActorInitialPos();
}

void Sphere::GenerateDefaultSphere(const std::vector<double>& initialPosCoord)
{
    std::string currentPath = boost::dll::program_location().parent_path().string();
    ReadSTLFIle(currentPath + "/res/" + "spatial_body_prototype.stl");
    SetScale(m_radius, m_radius, m_radius);
    SetColor(m_color);
    SetActorInitialPos(initialPosCoord[0], initialPosCoord[1], initialPosCoord[2]);
    //RotateY(planetAttributes.tilt);
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
