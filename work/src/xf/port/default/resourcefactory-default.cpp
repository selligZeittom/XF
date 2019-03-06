#include <config/xf-config.h>

#if (USE_XF_RESOURCE_FACTORY_DEFAULT_IMPLEMENTATION != 0)

#include "resourcefactory-default.h"
#include "mutex-default.h"

//static
interface::XFResourceFactory * interface::XFResourceFactory::getInstance()
{
	return XFResourceFactoryDefault::getInstance();
}

interface::XFResourceFactory* XFResourceFactoryDefault::getInstance() {
}

interface::XFDispatcher* XFResourceFactoryDefault::getDefaultDispatcher() {
}

interface::XFDispatcher* XFResourceFactoryDefault::createDispatcher() {
}

interface::XFThread* XFResourceFactoryDefault::createThread(
		interface::XFThreadEntryPointProvider* pProvider,
		interface::XFThread::EntryMethodBody entryMethod,
		const char* threadName, const uint32_t stackSize) {
}

interface::XFMutex* XFResourceFactoryDefault::createMutex() {
}

// TODO: Implement code for XFResourceFactoryDefault class

#endif // USE_XF_RESOURCE_FACTORY_DEFAULT_IMPLEMENTATION
