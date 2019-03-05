#include <config/xf-config.h>

#if (USE_XF_PORT_IDF_QT_THREAD_IMPLEMENTATION != 0)

#include <assert.h>
#include <string.h>
#include "thread.h"
#include "trace/trace.h"

#if !defined(XFTHREAD_DEFAULT_STACK_SIZE)
    #define XFTHREAD_DEFAULT_STACK_SIZE	256
#endif

/**
 * Always keep threads after creation in suspended state.
 * Threads must be explicitly started with start()!
 */

void XFThreadPort::start()
{
    QThread::start();
    //run();
}

void XFThreadPort::suspend()
{
    wait();
}

void XFThreadPort::stop()
{
    exit();
}

void XFThreadPort::setPriority(XFThreadPriority priority)
{
    //setPriority((QThread::Priority)priority);
}

XFThreadPriority XFThreadPort::getPriority() const
{
    return (XFThreadPriority) priority();
}

void XFThreadPort::delay(uint32_t milliseconds)
{
    msleep(milliseconds);
}

XFThreadPort::XFThreadPort(interface::XFThreadEntryPointProvider *pProvider, interface::XFThread::EntryMethodBody entryMethod, const char *threadName, const uint32_t stackSize)
{
    _pEntryMethodProvider = pProvider;
    _entryMethod = entryMethod;
    setStackSize(stackSize);
}

void XFThreadPort::run()
{
    Trace::out("[thread.cpp] run()");
    (_pEntryMethodProvider->*_entryMethod)(nullptr);
    Trace::out("[thread.cpp] end of run()");
}

#endif // USE_XF_PORT_IDF_QT_THREAD_IMPLEMENTATION
