#ifndef UTILS_ANGLESOPERATIONS_HPP
#define UTILS_ANGLESOPERATIONS_HPP


#if defined (_WIN32)
#if defined(UTILS_EXPORT)
#define UTILS_API __declspec(dllexport)
#else
#define  UTILS_API __declspec(dllimport)
#endif /* UTILS_API */
#define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
//  GCC
#define UTILS_API __attribute__((visibility("default")))
#endif


class UTILS_API AnglesOperations
{
public:
	static double Deg2Rad(double degrees);
	static double Rad2Deg(double radians);
};


#endif //UTILS_ANGLESOPERATIONS_HPP
