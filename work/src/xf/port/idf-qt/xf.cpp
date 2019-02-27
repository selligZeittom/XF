#include <config/xf-config.h>

#if (USE_XF_PORT_IDF_QT_XF_IMPLEMENTATION != 0)

#include <QCoreApplication>
#include "xf/interface/timeoutmanager.h"
#include "xf/interface/resourcefactory.h"
#include "xf/interface/dispatcher.h"
#include "xf/xf.h"
#include "trace/trace.h"


using interface::XFResourceFactory;

// TODO: Implement code for XF class


void XF::initialize(int timeInterval, int argc, char *argv[])
{
    Trace::out("[xf.cpp] initialize()");

}

int XF::exec()
{
    //main loop for event dispatching, this is blocking
    while(true)
    {
        execOnce();
    }

}

int XF::execOnce()
{
    //execute only one time the dispatcher
    getDefaultDispatcher()->executeOnce();
}

interface::XFDispatcher *XF::getDefaultDispatcher()
{
    //the one and only one dispatcher
    return getDefaultDispatcher();
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
