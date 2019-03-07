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
	enterCritical();
}

void XFMutexDefault::unlock()
{
	exitCritical();
}

bool XFMutexDefault::tryLock(int32_t timeout)
{
	return false;
}

#endif // USE_XF_MUTEX_DEFAULT_IMPLEMENTATION
