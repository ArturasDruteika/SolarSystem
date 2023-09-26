#ifndef GRAPHICALOBJECTS_COMPONENTS_HPP
#define GRAPHICALOBJECTS_COMPONENTS_HPP


#if defined (_WIN32)
#if defined(GRAPHICALOBJECTS_EXPORT)
#define GRAPHICALOBJECTS_API __declspec(dllexport)
#else
#define  GRAPHICALOBJECTS_API __declspec(dllimport)
#endif /* GRAPHICALOBJECTS_API */
#define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
//  GCC
#define GRAPHICALOBJECTS_COMPONENTS_API __attribute__((visibility("default")))
#endif


typedef GRAPHICALOBJECTS_API struct
{
    int radius;
    int distanceFromCenter;
    int speed;
    int tiltDegrees;
} ObjectAttributes;


#endif // GRAPHICALOBJECTS_COMPONENTS_HPP
