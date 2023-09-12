#include "GraphicalRunnerImpl.hpp"


GraphicalRunner::GraphicalRunnerImpl::GraphicalRunnerImpl(GraphicalRunner& parentRef)
{
}

GraphicalRunner::GraphicalRunnerImpl::~GraphicalRunnerImpl()
= default;

void GraphicalRunner::GraphicalRunnerImpl::Enter()
{
    m_gui.Init();
    //m_gui.Run();
    m_gui.RenderVtkWindow();
    m_gui.DeInit();
}


