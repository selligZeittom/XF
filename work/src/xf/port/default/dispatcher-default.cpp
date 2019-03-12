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
	_pMutex = XFResourceFactory::getInstance()->createMutex();
	_bInitialized = true;
	assert(_pMutex);
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
	_bExecuting = true; //only set _bExecuting to true so that the main can call execOnce()
}

void XFDispatcherDefault::stop()
{
	_bExecuting = false; //stop the execution as execOnce() checks whether _bExecuting is true or false;
}

void XFDispatcherDefault::pushEvent(XFEvent* pEvent)
{
	_pMutex->lock();
	_events.push(pEvent); //forward event to the queue
	_pMutex->unlock();
}

void XFDispatcherDefault::scheduleTimeout(int timeoutId, int interval,
		interface::XFReactive* pReactive)
{
	XFTimeoutManager::getInstance()->scheduleTimeout(timeoutId, interval, pReactive); //forward timeout to the timeoutmanager
}

void XFDispatcherDefault::unscheduleTimeout(int timeoutId,
		interface::XFReactive* pReactive)
{
	XFTimeoutManager::getInstance()->unscheduleTimeout(timeoutId, pReactive); //forward to the timeoutmanager
}

int XFDispatcherDefault::executeOnce()
{
	if(!_events.empty() && _bExecuting) //be sure that the queue isn't empty and that everything is set up properly
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

	return 0;
}

void XFDispatcherDefault::dispatchEvent(const XFEvent* pEvent) const
{
	interface::XFReactive* target = pEvent->getBehavior();
	if(target) //only if the behavior is not null
	{
		XFEventStatus status = target->process(pEvent); //to the state machine
		if(status == XFEventStatus::Terminate) //means that the state machine is finished
		{
			/* to be added into the interface XFReactive so we know when to delete a statemachine
			if(target->dynamicallyCreated())
			{
				delete target;
				target = nullptr;
			}
			*/
		}
	}
}


#endif // USE_XF_DISPATCHER_DEFAULT_IMPLEMENTATION
