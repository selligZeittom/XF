#include <config/xf-config.h>

#if (USE_XF_RESOURCE_FACTORY_DEFAULT_IMPLEMENTATION != 0)

#include "resourcefactory-default.h"
#include "mutex-default.h"

//static
interface::XFResourceFactory * interface::XFResourceFactory::getInstance()
{
	return XFResourceFactoryDefault::getInstance();
}

interface::XFResourceFactory* XFResourceFactoryDefault::getInstance()
{
	static XFResourceFactoryDefault* theRF  = nullptr;
	if(theRF == nullptr)
	{
		theRF = new XFResourceFactoryDefault(); //singleton pattern
	}
	return theRF;
}

interface::XFDispatcher* XFResourceFactoryDefault::getDefaultDispatcher()
{
	static XFDispatcherDefault _mainDispatcher; //the one and only one dispatcher
	return &_mainDispatcher;
}

interface::XFDispatcher* XFResourceFactoryDefault::createDispatcher()
{
	return nullptr;
}

interface::XFThread* XFResourceFactoryDefault::createThread(
		interface::XFThreadEntryPointProvider* pProvider,
		interface::XFThread::EntryMethodBody entryMethod,
		const char* threadName, const uint32_t stackSize)
{
	return nullptr; //no thread on the stm32 platform
}

interface::XFMutex* XFResourceFactoryDefault::createMutex()
{
	return new XFMutexDefault();
}

#endif // USE_XF_RESOURCE_FACTORY_DEFAULT_IMPLEMENTATION
