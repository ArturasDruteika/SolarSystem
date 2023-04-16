#include "ContextWindow.hpp"

int main()
{
    ContextWindow contextWindow;

    contextWindow.Init();
    contextWindow.Run();
    contextWindow.DeInit();

    return 0;
}
