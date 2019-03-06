#include <config/xf-config.h>

#if (USE_XF_PORT_IDF_QT_XF_IMPLEMENTATION != 0)

#include "xf/interface/timeoutmanager.h"
#include "xf/interface/resourcefactory.h"
#include "xf/interface/dispatcher.h"
#include "xf/xf.h"
#include "trace/trace.h"
#include <QCoreApplication>



using interface::XFResourceFactory;
bool XF::_bInitialized;

static QCoreApplication* _app = nullptr;

void XF::initialize(int timeInterval, int argc, char *argv[])
{
    _app = new QCoreApplication(argc, argv);
    if(!_bInitialized) //initialize what should be initialized
    {
        interface::XFTimeoutManager::getInstance()->initialize(timeInterval);
        XFResourceFactory::getInstance()->getDefaultDispatcher()->initialize();
    }
    _bInitialized = true;
}

void XF::kill()
{
    XFResourceFactory::getInstance()->getDefaultDispatcher()->stop();

    if(XFResourceFactory::getInstance()->getDefaultDispatcher() != NULL)
    {
        delete XFResourceFactory::getInstance()->getDefaultDispatcher();
    }

    if(XFResourceFactory::getInstance() != NULL)
    {
        delete XFResourceFactory::getInstance();
    }
    _app->exit(); //let the app return
}

int XF::exec()
{
    //start the dispatcher and the timeout manager
    XFResourceFactory::getInstance()->getDefaultDispatcher()->start();
    interface::XFTimeoutManager::getInstance()->start();
    return _app->exec(); //keep the main thread aliiiive
}

int XF::execOnce()
{
    //execute only one time the dispatcher
    getDefaultDispatcher()->executeOnce();
    return 1;
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
