#ifndef CELESTIALPHYSICS_OBJECTSCOMPONENTS_HPP
#define CELESTIALPHYSICS_OBJECTSCOMPONENTS_HPP


#if defined (_WIN32)
#if defined(CELESTIALPHYSICS_EXPORT)
#define CELESTIALPHYSICS_API __declspec(dllexport)
#else
#define  CELESTIALPHYSICS_API __declspec(dllimport)
#endif /* CELESTIALPHYSICS_API */
#define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
//  GCC
#define Planet_API __attribute__((visibility("default")))
#endif


typedef CELESTIALPHYSICS_API struct
{
    double radius; // km
    double mass; // kg
    double semiMajorAxis; // km
    double semiMinorAxis; // km
    double rotationalPeriod; // days
    double inclination; // radians (for orbit calculation) / degrees (for rendering)
    double tilt; // degrees
} PlanetAttributes;


#endif // CELESTIALPHYSICS_OBJECTSCOMPONENTS_HPP
