#include <config/xf-config.h>

#if (USE_XF_PORT_IDF_QT_RESOURCE_FACTORY_IMPLEMENTATION != 0)

#include <QtGlobal>
#include "thread.h"
#include "default/dispatcher-active.h"
#include "mutex.h"
#include "resourcefactory.h"
#include "trace/trace.h"


//static
interface::XFResourceFactory * interface::XFResourceFactory::getInstance()
{
    return XFResourceFactoryPort::getInstance();
}

// TODO: Implement code for XFResourceFactoryPort class

interface::XFResourceFactory *XFResourceFactoryPort::getInstance()
{
    static XFResourceFactoryPort* theResourceFactoryPort = NULL;
    if(!theResourceFactoryPort)
    {
        theResourceFactoryPort = new XFResourceFactoryPort();
        Trace::out("[resourcecfactory.cpp] new resourcefactoryport created");
    }
    return theResourceFactoryPort;
}

interface::XFDispatcher *XFResourceFactoryPort::getDefaultDispatcher()
{
    static interface::XFDispatcher* defaultDispatcher = NULL;
    if(!defaultDispatcher)
    {
        defaultDispatcher = createDispatcher();
    }

    return defaultDispatcher;
}

interface::XFDispatcher *XFResourceFactoryPort::createDispatcher()
{
    XFDispatcherActiveDefault* newDispatcher = new XFDispatcherActiveDefault();
    Trace::out("[resourcecfactory.cpp] new Dispatcher created()");
    return newDispatcher;

}

interface::XFThread *XFResourceFactoryPort::createThread(interface::XFThreadEntryPointProvider *pProvider, interface::XFThread::EntryMethodBody entryMethod, const char *threadName, const uint32_t stackSize)
{
    Trace::out("[resourcecfactory.cpp] createThread()");
    XFThreadPort* newThread = new XFThreadPort(pProvider, entryMethod, threadName, stackSize);
    return newThread;
}

interface::XFMutex *XFResourceFactoryPort::createMutex()
{
    Trace::out("[resourcecfactory.cpp] createMutex()");
    return new XFMutexPort();
}

#endif // USE_XF_PORT_IDF_QT_RESOURCE_FACTORY_IMPLEMENTATION
