#include "cube.hpp"
#include <vtkActor.h>
#include <vtkCellArray.h>
#include <vtkFloatArray.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPointData.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <array>


Cube::Cube()
{
}

Cube::~Cube()
{
}

vtkNew<vtkActor> Cube::GenerateCube()
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

    // Now we'll look at it.
    vtkNew<vtkPolyDataMapper> cubeMapper;
    cubeMapper->SetInputData(cube);
    cubeMapper->SetScalarRange(cube->GetScalarRange());
    vtkNew<vtkActor> cubeActor;
    cubeActor->SetMapper(cubeMapper);

    return cubeActor;
}