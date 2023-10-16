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
    double radius;
    double distanceFromCenter;
    double speed;
    double tiltRadians;
} ObjectAttributes;


#endif // CELESTIALPHYSICS_OBJECTSCOMPONENTS_HPP
