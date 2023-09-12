#ifndef VTKWINDOW_HPP
#define VTKWINDOW_HPP


#include "VtkViewer.h"


class VTKWindow
{
public:
    VTKWindow();
    ~VTKWindow();

    int Init();
    void DeInit();

    void RunMainWindow();
    void InitializeVtkActors();

private:
    bool m_isVtkOpen;

    VtkViewer m_vtkViewer1;
    VtkViewer m_vtkViewer2;
};


#endif //VTKWINDOW_HPP
