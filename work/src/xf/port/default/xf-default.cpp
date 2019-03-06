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
inline void XF::initialize(int timeInterval, int argc, char* argv[]) {
}

inline void XF::kill() {
}

inline int XF::exec() {
}

inline int XF::execOnce() {
}

inline interface::XFDispatcher* XF::getDefaultDispatcher() {
}

inline void XF_initialize(int timeInterval) {
}

inline void XF_exec() {
}

inline void XF_execOnce() {
}
#endif // USE_XF_DEFAULT_IMPLEMENTATION
