#include <assert.h>
#include <config/xf-config.h>

#if (USE_XF_DEFAULT_IMPLEMENTATION != 0)

#include "xf/interface/timeoutmanager.h"
#include "xf/interface/resourcefactory.h"
#include "xf/interface/dispatcher.h"
#include "xf/xf.h"
#include "mdw/trace/trace.h"

using interface::XFResourceFactory;
using interface::XFTimeoutManager;

bool XF::_bInitialized = false;

// TODO: Implement code for XF class
void XF::initialize(int timeInterval, int argc, char* argv[])
{
	Trace::out("initializing");
	if(!_bInitialized)
	{
		interface::XFTimeoutManager::getInstance()->initialize(timeInterval);
		getDefaultDispatcher()->initialize();
		Trace::out("initialized");
	}
}

void XF::kill()
{

}

int XF::exec()
{
	if(!_bInitialized)
	{
		initialize(20);
	}

	interface::XFTimeoutManager::getInstance()->start();
	getDefaultDispatcher()->start();

	return 0;
}

int XF::execOnce()
{
	return getDefaultDispatcher()->executeOnce();
}

interface::XFDispatcher* XF::getDefaultDispatcher()
{
	return XFResourceFactory::getInstance()->getDefaultDispatcher();
}

void XF_initialize(int timeInterval)
{
	Trace::out("call c++ method initialize");
	XF::initialize(timeInterval);
}

void XF_exec()
{
	XF::exec();
}

void XF_execOnce()
{
	XF::execOnce();
}
#endif // USE_XF_DEFAULT_IMPLEMENTATION
