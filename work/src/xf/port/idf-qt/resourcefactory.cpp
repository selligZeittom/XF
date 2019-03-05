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

interface::XFResourceFactory *XFResourceFactoryPort::getInstance()
{
    static XFResourceFactoryPort* theResourceFactoryPort = NULL;
    if(!theResourceFactoryPort) //create the singleton if needed
    {
        theResourceFactoryPort = new XFResourceFactoryPort();
    }
    return theResourceFactoryPort;
}

interface::XFDispatcher *XFResourceFactoryPort::getDefaultDispatcher()
{
    static interface::XFDispatcher* defaultDispatcher = NULL;
    if(!defaultDispatcher) //create the default dispatcher
    {
        defaultDispatcher = createDispatcher();
    }

    return defaultDispatcher;
}

interface::XFDispatcher *XFResourceFactoryPort::createDispatcher()
{
    XFDispatcherActiveDefault* newDispatcher = new XFDispatcherActiveDefault();
    return newDispatcher;

}

interface::XFThread *XFResourceFactoryPort::createThread(interface::XFThreadEntryPointProvider *pProvider, interface::XFThread::EntryMethodBody entryMethod, const char *threadName, const uint32_t stackSize)
{
    XFThreadPort* newThread = new XFThreadPort(pProvider, entryMethod, threadName, stackSize);
    return newThread;
}

interface::XFMutex *XFResourceFactoryPort::createMutex()
{
    return new XFMutexPort();
}

#endif // USE_XF_PORT_IDF_QT_RESOURCE_FACTORY_IMPLEMENTATION
