#include <assert.h>
#include <config/xf-config.h>

#if (USE_XF_DISPATCHER_DEFAULT_IMPLEMENTATION != 0)
#if (XF_TRACE_EVENT_PUSH_POP != 0)
    #include "trace/trace.h"
#endif // XF_TRACE_EVENT_PUSH_POP
#include "xf/eventstatus.h"
#include "xf/interface/timeoutmanager.h"
#include "xf/interface/reactive.h"
#include "xf/interface/resourcefactory.h"
#include "dispatcher-default.h"

using interface::XFTimeoutManager;
using interface::XFResourceFactory;

XFDispatcherDefault::XFDispatcherDefault()
{
	_bExecuting = false;
	_bInitialized = false;
	_pMutex = nullptr;
	if(!_bInitialized)
	{
		_pMutex = XFResourceFactory::getInstance()->createMutex();
		_bInitialized = true;
		assert(_pMutex);
	}
}

XFDispatcherDefault::~XFDispatcherDefault()
{
	if(_pMutex)
	{
		delete _pMutex;
		_pMutex = nullptr;
	}
}

void XFDispatcherDefault::initialize()
{
	//all done into the constructor
}

void XFDispatcherDefault::start()
{
	_bExecuting = true;
	// todo implements start method of dispatcher
}

void XFDispatcherDefault::stop()
{
	_bExecuting = false;
	// todo implements stop method of dispatcher
}

void XFDispatcherDefault::pushEvent(XFEvent* pEvent)
{
	_pMutex->lock();
	_events.push(pEvent);
	_pMutex->unlock();
}

void XFDispatcherDefault::scheduleTimeout(int timeoutId, int interval,
		interface::XFReactive* pReactive)
{
	XFTimeoutManager::getInstance()->scheduleTimeout(timeoutId, interval, pReactive);
}

void XFDispatcherDefault::unscheduleTimeout(int timeoutId,
		interface::XFReactive* pReactive)
{
	XFTimeoutManager::getInstance()->unscheduleTimeout(timeoutId, pReactive);
}

int XFDispatcherDefault::executeOnce()
{
	if(_events.empty() && _bExecuting)
	{
		dispatchEvent(_events.front()); //get the first event and send it
		return 0;
	}
	return -1;
}

int XFDispatcherDefault::execute(const void* param)
{
	while(_bExecuting)
	{
		while(_events.empty())
		{
			_events.pend(); //wait until an event comes
		}

		//now we got an event
		executeOnce();
	}
}

void XFDispatcherDefault::dispatchEvent(const XFEvent* pEvent) const
{
	interface::XFReactive* target = pEvent->getBehavior();
	if(target) //only if the behavior is not null
	{
		target->process(pEvent); //to the state machine
	}
}


#endif // USE_XF_DISPATCHER_DEFAULT_IMPLEMENTATION
