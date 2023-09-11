#ifndef SOLARSYSTEMSETUP_CUBE_HPP
#define SOLARSYSTEMSETUP_CUBE_HPP

#if defined (_WIN32)
#if defined(GRAPHICALRENDERING_EXPORT)
#define GRAPHICALRENDERING_API __declspec(dllexport)
#else
#define  GRAPHICALRENDERING_API __declspec(dllimport)
#endif /* GRAPHICALRENDERING_API */
#define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
//  GCC
#define CUBE_API __attribute__((visibility("default")))
#endif

class GRAPHICALRENDERING_API Cube
{
public:
	Cube();
	~Cube();

	static void RenderCube();
};

#endif //SOLARSYSTEMSETUP_CUBE_HPP
