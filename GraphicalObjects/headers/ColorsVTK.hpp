#ifndef GRAPHICALOBJECTS_COLORSVTK_HPP
#define GRAPHICALOBJECTS_COLORSVTK_HPP


#include "vtkNew.h"
#include <vtkColor.h>


struct ColorsVTK 
{
    inline static const vtkColor4d GREEN = vtkColor4d(0.0, 1.0, 0.0, 1.0);
    inline static const vtkColor4d BLUE = vtkColor4d(0.0, 0.0, 1.0, 1.0);
    inline static const vtkColor4d RED = vtkColor4d(1.0, 0.0, 0.0, 1.0);
    inline static const vtkColor4d YELLOW = vtkColor4d(1.0, 1.0, 0.0, 1.0);
};


#endif //GRAPHICALOBJECTS_COLORSVTK_HPP
