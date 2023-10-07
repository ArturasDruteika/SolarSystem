#ifndef SOLARSYSTEMCORE_GRAPHICALWINDOW_HPP
#define SOLARSYSTEMCORE_GRAPHICALWINDOW_HPP


#include "imgui.h"
#include <string>


class GraphicalWindow
{
public:
    GraphicalWindow();
    ~GraphicalWindow();

    virtual void Init() = 0;
    virtual void DeInit() = 0;
    virtual void RenderMainWindow(const std::string& windowName);
    
    virtual void PushMainWindowStyleVars();
    virtual void PopMainWindowStyleVars();
    virtual ImFont* CreateFont(const std::string& fontPath, float fontSize);

private:
    virtual void InitInternal() = 0;
    virtual void DeInitInternal() = 0;
    virtual void RenderMainWindowInternal() = 0;
    
    int m_nStyleVars;
};


#endif //SOLARSYSTEMCORE_GRAPHICALWINDOW_HPP
