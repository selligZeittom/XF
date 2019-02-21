#include "xf/xf.h"
#include "trace/trace.h"
#include "testfactory02.h"

void Factory_initialize()
{
    TestFactory02::initialize();
}

void Factory_build()
{
    TestFactory02::build();
}

StateMachine02 TestFactory02::_task01;

TestFactory02::TestFactory02()
{
}

// static
void TestFactory02::initialize()
{
}

// static
void TestFactory02::build()
{
    Trace::out("Starting test2...\n---------------------");

    // Start state machine
    _task01.startBehavior();
}
