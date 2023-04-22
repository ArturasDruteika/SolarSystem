#include "GraphicalRunner.hpp"
#include "GraphicalRunnerImpl.hpp"
#include <iostream>
#include "spdlog/spdlog.h"

GraphicalRunner::GraphicalRunner()
    : pGraphicalRunnerImpl(new GraphicalRunner::GraphicalRunnerImpl(*this))
{
}

GraphicalRunner::~GraphicalRunner()
{
    delete pGraphicalRunnerImpl;
}

void GraphicalRunner::Enter()
{
    spdlog::info("Starting!");
    pGraphicalRunnerImpl->Enter();
}
