#include "cube.hpp"

#include <vtkCellArray.h>
#include <vtkFloatArray.h>
#include <vtkNamedColors.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkSTLReader.h>
#include <vtkActor.h>


#include <array>
#include <iostream>


Cube::Cube()
    : m_transform{nullptr}
{
}

Cube::~Cube()
{
}

vtkNew<vtkActor> Cube::GenerateCube()
{
    // Now we'll look at it.
    vtkNew<vtkPolyDataMapper> cubeMapper;
    vtkNew<vtkPolyData> cube = GenerateCubeData();
    cubeMapper->SetInputData(cube);
    cubeMapper->SetScalarRange(cube->GetScalarRange());
    vtkNew<vtkActor> cubeActor;
    cubeActor->SetMapper(cubeMapper);
    SetCubeInitialPos(cubeActor);
    return cubeActor;
}

vtkNew<vtkActor> Cube::ReadSTLFIle(std::string pathToStlFile)
{
    vtkNew<vtkSTLReader> reader;
    reader->SetFileName(pathToStlFile.c_str()); // Replace with your STL file path

    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(reader->GetOutputPort());

    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);
    return actor;
}

std::vector<double> Cube::GetActorPosition(vtkNew<vtkActor>& actor)
{
    // Get the actor's transformation matrix
    vtkSmartPointer<vtkMatrix4x4> actorMatrix = vtkSmartPointer<vtkMatrix4x4>::New();
    actor->GetMatrix(actorMatrix);
    double actorPosition[3];
    std::vector<double> actorPositionVec;
    actor->GetPosition(actorPosition);
    for (int i = 0; i < 3; i++)
    {
        actorPositionVec.push_back(actorPosition[i]);
    }
    return actorPositionVec;
}

void Cube::MoveActor(vtkNew<vtkActor>& actor, double xPos, double yPos, double zPos)
{
    m_transform->Translate(xPos, yPos, zPos);
    actor->SetUserTransform(m_transform);
}


void Cube::TestFunc()
{

}

vtkNew<vtkPolyData> Cube::GenerateCubeData()
{
    vtkNew<vtkNamedColors> colors;

    std::array<std::array<double, 3>, 8> pts = { {{{0, 0, 0}},
                                                 {{1, 0, 0}},
                                                 {{1, 1, 0}},
                                                 {{0, 1, 0}},
                                                 {{0, 0, 1}},
                                                 {{1, 0, 1}},
                                                 {{1, 1, 1}},
                                                 {{0, 1, 1}}} };
    // The ordering of the corner points on each face.
    std::array<std::array<vtkIdType, 4>, 6> ordering = { {{{0, 3, 2, 1}},
                                                         {{4, 5, 6, 7}},
                                                         {{0, 1, 5, 4}},
                                                         {{1, 2, 6, 5}},
                                                         {{2, 3, 7, 6}},
                                                         {{3, 0, 4, 7}}} };

    // We'll create the building blocks of polydata including data attributes.
    vtkNew<vtkPolyData> cube;
    vtkNew<vtkPoints> points;
    vtkNew<vtkCellArray> polys;
    vtkNew<vtkFloatArray> scalars;

    // Load the point, cell, and data attributes.
    for (auto i = 0ul; i < pts.size(); ++i)
    {
        points->InsertPoint(i, pts[i].data());
        scalars->InsertTuple1(i, i);
    }
    for (auto&& i : ordering)
    {
        polys->InsertNextCell(vtkIdType(i.size()), i.data());
    }

    // We now assign the pieces to the vtkPolyData.
    cube->SetPoints(points);
    cube->SetPolys(polys);
    cube->GetPointData()->SetScalars(scalars);
    return cube;
}

void Cube::SetCubeInitialPos(vtkNew<vtkActor>& actor)
{
    double x = 0;
    double y = 0;
    double z = 0;

    m_transform = vtkSmartPointer<vtkTransform>::New();
    m_transform->Translate(x, y, z);
    actor->SetUserTransform(m_transform);
}

