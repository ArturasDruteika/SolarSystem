#ifndef SOLARSYSTEMSETUP_GRAPHICALRUNNERIMPL_HPP
#define SOLARSYSTEMSETUP_GRAPHICALRUNNERIMPL_HPP


#include "GraphicalRunner.hpp"
#include "ContextWindow.hpp"

class GraphicalRunner::GraphicalRunnerImpl
{
public:
    GraphicalRunnerImpl(GraphicalRunner& parentRef);
    ~GraphicalRunnerImpl();

    void Enter();
private:
    ContextWindow m_gui;
};


#endif //SOLARSYSTEMSETUP_GRAPHICALRUNNERIMPL_HPP
