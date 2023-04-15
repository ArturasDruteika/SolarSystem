#ifndef SOLARSYSTEMSETUP_DISPLAYWINDOW_HPP
#define SOLARSYSTEMSETUP_DISPLAYWINDOW_HPP


#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#ifdef __APPLE__
#define GL_SILENCE_DEPRECATION
#endif
#include <GLFW/glfw3.h>

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#endif


constexpr int MINVIEWPORTWIDTH{1266};
constexpr int MINVIEWPORTHEIGHT{668};


class DisplayWIndow
{
public:
    DisplayWIndow();
    ~DisplayWIndow();

    void Init();
    void DeInit();


private:

};


#endif //SOLARSYSTEMSETUP_DISPLAYWINDOW_HPP
