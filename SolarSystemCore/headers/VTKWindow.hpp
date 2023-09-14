#ifndef VTKWINDOW_HPP
#define VTKWINDOW_HPP


#include "VtkViewer.h"
#include "cube.hpp"


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

    Cube m_cube;
    VtkViewer m_vtkViewer1;
    VtkViewer m_vtkViewerFinal;
};


#endif //VTKWINDOW_HPP
