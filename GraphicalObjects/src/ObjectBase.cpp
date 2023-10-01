#include "ObjectBase.hpp"

#include <vtkPolyDataMapper.h>
#include <vtkSTLReader.h>



ObjectBase::ObjectBase()
{
    m_actor = vtkSmartPointer<vtkActor>::New();
    m_transform = vtkSmartPointer<vtkTransform>::New();
}

ObjectBase::~ObjectBase()
{
}

vtkSmartPointer<vtkActor> ObjectBase::GetObjectActor()
{
    return m_actor;
}

std::vector<double> ObjectBase::GetActorPosition(vtkSmartPointer<vtkActor>& actor)
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

void ObjectBase::MoveActor(double xPos, double yPos, double zPos)
{
    m_transform->Translate(xPos, yPos, zPos);
    m_actor->SetUserTransform(m_transform);
}

void ObjectBase::SetMapper(vtkNew<vtkPolyDataMapper>& mapper)
{
    m_actor->SetMapper(mapper);
}

void ObjectBase::SetActorInitialPos(double xPos, double yPos, double zPos)
{
    m_actor->SetPosition(xPos, yPos, zPos);
}

void ObjectBase::ReadSTLFIle(std::string pathToStlFile)
{
    vtkNew<vtkSTLReader> reader;
    reader->SetFileName(pathToStlFile.c_str());
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(reader->GetOutputPort());
    m_actor->SetMapper(mapper);
}
