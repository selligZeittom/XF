#include <config/xf-config.h>

#if (USE_XF_PORT_IDF_QT_THREAD_IMPLEMENTATION != 0)

#include <assert.h>
#include <string.h>
#include "thread.h"

#if !defined(XFTHREAD_DEFAULT_STACK_SIZE)
    #define XFTHREAD_DEFAULT_STACK_SIZE	256
#endif

/**
 * Always keep threads after creation in suspended state.
 * Threads must be explicitly started with start()!
 */

// TODO: Implement code for XFThreadPort class

void XFThreadPort::start()
{

}

void XFThreadPort::suspend()
{

}

void XFThreadPort::stop()
{

}

void XFThreadPort::setPriority(XFThreadPriority priority)
{

}

XFThreadPriority XFThreadPort::getPriority() const
{

}

void XFThreadPort::delay(uint32_t milliseconds)
{

}

void XFThreadPort::run()
{

}

#endif // USE_XF_PORT_IDF_QT_THREAD_IMPLEMENTATION
