#include <config/xf-config.h>

#if (USE_XF_EVENT_QUEUE_DEFAULT_IMPLEMENTATION != 0)

#include <assert.h>
#include "eventqueue-default.h"

// TODO: Implement code for XFEventQueueDefault class

#endif // USE_XF_EVENT_QUEUE_DEFAULT_IMPLEMENTATION

XFEventQueueDefault::XFEventQueueDefault() {
}

XFEventQueueDefault::~XFEventQueueDefault() {
}

bool XFEventQueueDefault::empty() const {
}

bool XFEventQueueDefault::push(const XFEvent* pEvent) {
}

const XFEvent* XFEventQueueDefault::front() {
}

void XFEventQueueDefault::pop() {
}

bool XFEventQueueDefault::pend() {
}
