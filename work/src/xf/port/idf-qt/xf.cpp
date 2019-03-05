#include <config/xf-config.h>

#if (USE_XF_PORT_IDF_QT_XF_IMPLEMENTATION != 0)

#include "xf/interface/timeoutmanager.h"
#include "xf/interface/resourcefactory.h"
#include "xf/interface/dispatcher.h"
#include "xf/xf.h"
#include "trace/trace.h"


using interface::XFResourceFactory;
bool XF::_bInitialized;

QCoreApplication* XF::_app;


void XF::initialize(int timeInterval, int argc, char *argv[])
{
    XF::_app = new QCoreApplication(argc, argv);
    Trace::out("[xf.cpp] initialize()");
    if(!_bInitialized)
    {
        interface::XFTimeoutManager::getInstance()->initialize(timeInterval);
        XFResourceFactory::getInstance()->getDefaultDispatcher()->initialize();
        Trace::out("[xf.cpp] timeout manager, dispatcher and xf initialized ");

    }
    _bInitialized = true;
}

int XF::exec()
{
    XFResourceFactory::getInstance()->getDefaultDispatcher()->start();
    interface::XFTimeoutManager::getInstance()->start();
    _app->exec();
}

int XF::execOnce()
{
    //execute only one time the dispatcher
    getDefaultDispatcher()->executeOnce();
}

interface::XFDispatcher *XF::getDefaultDispatcher()
{
    //the one and only one dispatcher
    return XFResourceFactory::getInstance()->getDefaultDispatcher();
}


/*
 * call of the c++ methods for the 3 following functions
 */

void XF_initialize(int timeInterval)
{
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

#endif // USE_XF_PORT_IDF_QT_XF_IMPLEMENTATION
