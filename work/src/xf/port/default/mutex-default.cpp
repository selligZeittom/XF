#include <config/xf-config.h>

#if (USE_XF_MUTEX_DEFAULT_IMPLEMENTATION != 0)

#include "critical/critical.h"	// Provided by the platform used
#include "mutex-default.h"

// TODO: Implement code for XFMutexDefault class


XFMutexDefault::XFMutexDefault()
{
}

XFMutexDefault::~XFMutexDefault()
{
}

void XFMutexDefault::lock()
{
	enterCritical(); //kind of a low level mutex : disable the isr
}

void XFMutexDefault::unlock()
{
	exitCritical(); //enable the isr again
}

bool XFMutexDefault::tryLock(int32_t timeout)
{
	return false;
}

#endif // USE_XF_MUTEX_DEFAULT_IMPLEMENTATION
