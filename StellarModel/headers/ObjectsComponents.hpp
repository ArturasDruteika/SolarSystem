#ifndef STELLARMODEL_OBJECTSCOMPONENTS_HPP
#define STELLARMODEL_OBJECTSCOMPONENTS_HPP


#if defined (_WIN32)
#if defined(STELLARMODEL_EXPORT)
#define STELLARMODEL_API __declspec(dllexport)
#else
#define  STELLARMODEL_API __declspec(dllimport)
#endif /* STELLARMODEL_API */
#define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
//  GCC
#define Planet_API __attribute__((visibility("default")))
#endif


typedef STELLARMODEL_API struct
{
    double radius; // km
    double mass; // kg
    double semiMajorAxis; // km
    double semiMinorAxis; // km
    double rotationalPeriod; // days
    double inclination; // radians (for orbit calculation) / degrees (for rendering)
    double tilt; // degrees
} PlanetAttributes;


#endif // STELLARMODEL_OBJECTSCOMPONENTS_HPP
