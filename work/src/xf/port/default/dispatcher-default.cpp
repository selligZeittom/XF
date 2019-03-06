#include <assert.h>
#include <config/xf-config.h>

#if (USE_XF_DISPATCHER_DEFAULT_IMPLEMENTATION != 0)
#if (XF_TRACE_EVENT_PUSH_POP != 0)
    #include "trace/trace.h"
#endif // XF_TRACE_EVENT_PUSH_POP
#include "xf/eventstatus.h"
#include "xf/interface/timeoutmanager.h"
#include "xf/interface/reactive.h"
#include "xf/interface/resourcefactory.h"
#include "dispatcher-default.h"

using interface::XFTimeoutManager;
using interface::XFResourceFactory;

XFDispatcherDefault::XFDispatcherDefault() {
}

XFDispatcherDefault::~XFDispatcherDefault() {
}

void XFDispatcherDefault::initialize() {
}

void XFDispatcherDefault::start() {
}

void XFDispatcherDefault::stop() {
}

void XFDispatcherDefault::pushEvent(XFEvent* pEvent) {
}

void XFDispatcherDefault::scheduleTimeout(int timeoutId, int interval,
		interface::XFReactive* pReactive) {
}

void XFDispatcherDefault::unscheduleTimeout(int timeoutId,
		interface::XFReactive* pReactive) {
}

int XFDispatcherDefault::executeOnce() {
}

int XFDispatcherDefault::execute(const void* param) {
}

void XFDispatcherDefault::dispatchEvent(const XFEvent* pEvent) const {
}

// TODO: Implement code for XFDispatcherDefault class

#endif // USE_XF_DISPATCHER_DEFAULT_IMPLEMENTATION
