#include <assert.h>
#include <config/xf-config.h>

#if (USE_XF_DEFAULT_IMPLEMENTATION != 0)

#include "xf/interface/timeoutmanager.h"
#include "xf/interface/resourcefactory.h"
#include "xf/interface/dispatcher.h"
#include "xf/xf.h"

using interface::XFResourceFactory;
using interface::XFTimeoutManager;

// TODO: Implement code for XF class
void XF::initialize(int timeInterval, int argc, char* argv[]) {
}

void XF::kill() {
}

int XF::exec() {
}

int XF::execOnce() {
}

interface::XFDispatcher* XF::getDefaultDispatcher() {
}

void XF_initialize(int timeInterval) {
}

void XF_exec() {
}

void XF_execOnce() {
}
#endif // USE_XF_DEFAULT_IMPLEMENTATION
