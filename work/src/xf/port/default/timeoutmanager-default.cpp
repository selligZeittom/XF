
#include <config/xf-config.h>

#if (USE_XF_TIMEOUTMANAGER_DEFAULT_IMPLEMENTATION != 0)

#include <assert.h>
#include "xf/interface/reactive.h"
#include "xf/interface/resourcefactory.h"
#include "port-functions.h"
#include "timeoutmanager-default.h"

using interface::XFResourceFactory;

interface::XFTimeoutManager * interface::XFTimeoutManager::getInstance()
{
	return XFTimeoutManagerDefault::getInstance();
}

// TODO: Implement code for XFTimeoutManagerDefault class

#endif // USE_XF_TIMEOUTMANAGER_DEFAULT_IMPLEMENTATION
