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

bool XF::_bInitialized = false; //must be set to false somewhere, so let's do it there

void XF::initialize(int timeInterval, int argc, char* argv[])
{
	if(!_bInitialized) //should only be done once
	{
		interface::XFTimeoutManager::getInstance()->initialize(timeInterval);
		getDefaultDispatcher()->initialize();
		_bInitialized = true;
	}

	//start the timeoutmanager and the dispatcher
	interface::XFTimeoutManager::getInstance()->start();
	getDefaultDispatcher()->start();
}

int XF::exec()
{
	if(!_bInitialized) //be sure that everything is initialized and started properly
	{
		initialize(20); //20 is kind of a default value
	}
	getDefaultDispatcher()->execute();

	return 0;
}

int XF::execOnce()
{
	if(!_bInitialized) //be sure that everything is initialized and started properly
	{
		initialize(20); //20 is kind of a default value
	}
	return getDefaultDispatcher()->executeOnce();
}

interface::XFDispatcher* XF::getDefaultDispatcher()
{
	return XFResourceFactory::getInstance()->getDefaultDispatcher();
}

void XF_initialize(int timeInterval)
{
	XF::initialize(timeInterval); //call the c++ method
}

void XF_exec()
{
	XF::exec(); //call the c++ method
}

void XF_execOnce()
{
	XF::execOnce(); //call the c++ method
}
#endif // USE_XF_DEFAULT_IMPLEMENTATION
