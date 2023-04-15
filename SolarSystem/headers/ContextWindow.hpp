#ifndef SOLARSYSTEMSETUP_CONTEXTWINDOW_HPP
#define SOLARSYSTEMSETUP_CONTEXTWINDOW_HPP


constexpr int MIN_VIEWPORT_WIDTH{1266};
constexpr int MIN_VIEWPORT_HEIGHT{668};


class ContextWindow
{
public:
    ContextWindow();
    ~ContextWindow();

    int Init();
    void DeInit();
    int Run();

private:
    static void glfw_error_callback(int error, const char* description);

};


#endif //SOLARSYSTEMSETUP_CONTEXTWINDOW_HPP
