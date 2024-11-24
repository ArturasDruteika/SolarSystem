#ifndef SOLARSYSTEMCORE_GRAPHICALWINDOW_HPP
#define SOLARSYSTEMCORE_GRAPHICALWINDOW_HPP


#include "imgui.h"
#include <string>


class GraphicalWindow
{
public:
    GraphicalWindow(const std::string& windowName);
    ~GraphicalWindow();

    virtual void Init() = 0;
    virtual void DeInit() = 0;
    virtual void RenderWindow();
    
    virtual void PushMainWindowStyleVars();
    virtual void PopMainWindowStyleVars();
    virtual ImFont* CreateFont(const std::string& fontPath, float fontSize);

    std::string GetWindowName() const;
    void SetWindowName(const std::string& windowName);

protected:
    std::string m_windowName;

private:
    virtual void InitInternal() = 0;
    virtual void DeInitInternal() = 0;
    virtual void RenderWindowInternal() = 0;
    
    int m_nStyleVars;
};


#endif //SOLARSYSTEMCORE_GRAPHICALWINDOW_HPP
