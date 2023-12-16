#ifndef SOLARSYSTEMSETUP_GRAPHICALRUNNER_HPP
#define SOLARSYSTEMSETUP_GRAPHICALRUNNER_HPP


#if defined (_WIN32)
#if defined(SOLARSYSTEMRENDERING_EXPORT)
#define SOLARSYSTEMRENDERING_API __declspec(dllexport)
#else
#define  SOLARSYSTEMRENDERING_API __declspec(dllimport)
#endif /* SOLARSYSTEMRENDERING_API */
#define _sprintf sprintf_s
#endif

#if defined(__GNUC__)
//  GCC
#define GRAPHICALRUNNER_API __attribute__((visibility("default")))
#endif


class SOLARSYSTEMRENDERING_API GraphicalRunner
{
public:
    GraphicalRunner();
    ~GraphicalRunner();

    // Start app
    void Enter();
public:
    class GraphicalRunnerImpl;

    GraphicalRunnerImpl* pGraphicalRunnerImpl;
};


#endif //SOLARSYSTEMSETUP_GRAPHICALRUNNER_HPP
