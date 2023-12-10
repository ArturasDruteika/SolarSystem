#include "Cube.hpp"

#include <vtkCellArray.h>
#include <vtkFloatArray.h>
#include <vtkNamedColors.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkSTLReader.h>
#include <vtkActor.h>


Cube::Cube()
{
}

Cube::~Cube()
{
}

void Cube::GenerateObject(double edgeLength)
{
    vtkNew<vtkPolyDataMapper> cubeMapper;
    vtkNew<vtkPolyData> cube = GenerateCubeData();
    cubeMapper->SetInputData(cube);
    cubeMapper->SetScalarRange(cube->GetScalarRange());
    SetMapper(cubeMapper);
    SetActorInitialPos();
}

vtkNew<vtkPolyData> Cube::GenerateCubeData()
{
    //vtkNew<vtkNamedColors> colors;

    // Define the half-length of the cube.
    double halfLength = 0.5;

    std::array<std::array<double, 3>, 8> pts = {
        {{{-halfLength, -halfLength, -halfLength}},
         {{ halfLength, -halfLength, -halfLength}},
         {{ halfLength,  halfLength, -halfLength}},
         {{-halfLength,  halfLength, -halfLength}},
         {{-halfLength, -halfLength,  halfLength}},
         {{ halfLength, -halfLength,  halfLength}},
         {{ halfLength,  halfLength,  halfLength}},
         {{-halfLength,  halfLength,  halfLength}}}
    };
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

