#include <config/xf-config.h>

#if (USE_XF_DISPATCHER_ACTIVE_DEFAULT_IMPLEMENTATION != 0)

#include <assert.h>
#if (XF_TRACE_EVENT_PUSH_POP != 0)
    #include "trace/trace.h"
#endif // XF_TRACE_EVENT_PUSH_POP
#include "xf/eventstatus.h"
#include "xf/interface/timeoutmanager.h"
#include "xf/interface/reactive.h"
#include "xf/interface/thread.h"
#include "xf/interface/resourcefactory.h"
#include "dispatcher-active.h"
#include "trace/trace.h"


using interface::XFTimeoutManager;
using interface::XFResourceFactory;

// TODO: Implement code for XFDispatcherActive class


XFDispatcherActiveDefault::XFDispatcherActiveDefault()
{
    Trace::out("[dispatcher-active.cpp] XFDispatcherActiveDefault() TBI");
}

XFDispatcherActiveDefault::~XFDispatcherActiveDefault()
{
    Trace::out("[dispatcher-active.cpp] ~XFDispatcherActiveDefault() TBI");
}

void XFDispatcherActiveDefault::initialize()
{
    Trace::out("[dispatcher-active.cpp] initialize() TBI");

}

void XFDispatcherActiveDefault::start()
{
    Trace::out("[dispatcher-active.cpp] start() TBI");

}

void XFDispatcherActiveDefault::stop()
{
    Trace::out("[dispatcher-active.cpp] stop() TBI");

}

void XFDispatcherActiveDefault::pushEvent(XFEvent *pEvent)
{
    Trace::out("[dispatcher-active.cpp] pushEvent() TBI");

}

void XFDispatcherActiveDefault::scheduleTimeout(int timeoutId, int interval, interface::XFReactive *pReactive)
{
    Trace::out("[dispatcher-active.cpp] scheduleTimeout() TBI");

}

void XFDispatcherActiveDefault::unscheduleTimeout(int timeoutId, interface::XFReactive *pReactive)
{
    Trace::out("[dispatcher-active.cpp] initialize() TBI");

}

int XFDispatcherActiveDefault::executeOnce()
{
    Trace::out("[dispatcher-active.cpp] executeOnce() TBI");

}

int XFDispatcherActiveDefault::execute(const void *param)
{
    Trace::out("[dispatcher-active.cpp] execute() TBI");

}

void XFDispatcherActiveDefault::dispatchEvent(const XFEvent *pEvent) const
{
    Trace::out("[dispatcher-active.cpp] dispatchEvent() TBI");

}


#endif // USE_XF_DISPATCHER_ACTIVE_DEFAULT_IMPLEMENTATION
