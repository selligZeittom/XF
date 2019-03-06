#include <assert.h>
#include <config/xf-config.h>

#if (USE_XF_PORT_IDF_QT_MUTEX_IMPLEMENTATION != 0)

#include "mutex.h"

// TODO: Implement code for XFXFMutexPort class

XFMutexPort::XFMutexPort()
{

}

XFMutexPort::~XFMutexPort()
{

}

void XFMutexPort::lock()
{
    _mutex.lock();
}

void XFMutexPort::unlock()
{
    _mutex.unlock();
}

bool XFMutexPort::tryLock(int32_t timeout)
{
    return _mutex.tryLock(timeout);
}

#endif // USE_XF_PORT_IDF_QT_MUTEX_IMPLEMENTATION
