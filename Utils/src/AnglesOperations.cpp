#include "AnglesOperations.hpp"


constexpr double M_PI = 3.141'592'653'589'793'238'46;


double AnglesOperations::Deg2Rad(double degrees)
{
    return degrees * (M_PI / 180.0);
}

double AnglesOperations::Rad2Deg(double radians)
{
    return radians * (180.0 / M_PI);
}
