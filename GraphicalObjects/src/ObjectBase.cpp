#include "ObjectBase.hpp"

#include <vtkPolyDataMapper.h>
#include <vtkSTLReader.h>



ObjectBase::ObjectBase()
{
    m_transform = vtkSmartPointer<vtkTransform>::New();
}

ObjectBase::~ObjectBase()
{
}

void ObjectBase::MoveActor(vtkNew<vtkActor>& actor, double xPos, double yPos, double zPos)
{
    m_transform->Translate(xPos, yPos, zPos);
    actor->SetUserTransform(m_transform);
}

vtkNew<vtkActor> ObjectBase::ReadSTLFIle(std::string pathToStlFile)
{
    vtkNew<vtkSTLReader> reader;
    reader->SetFileName(pathToStlFile.c_str());

    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(reader->GetOutputPort());

    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);
    return actor;
}
