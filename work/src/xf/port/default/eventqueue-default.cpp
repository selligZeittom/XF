#include <config/xf-config.h>

#if (USE_XF_EVENT_QUEUE_DEFAULT_IMPLEMENTATION != 0)

#include <assert.h>
#include "eventqueue-default.h"
#include "xf/event.h" //Added

// TODO: Implement code for XFEventQueueDefault class

#endif // USE_XF_EVENT_QUEUE_DEFAULT_IMPLEMENTATION

XFEventQueueDefault::XFEventQueueDefault()
{
}

XFEventQueueDefault::~XFEventQueueDefault()
{
	/*
	for(auto e : _queue)
	{
		if(e)
		{
			delete e;
			e = nullptr;
		}
	}*/
}

bool XFEventQueueDefault::empty() const
{
	return _queue.empty();
}

bool XFEventQueueDefault::push(const XFEvent* pEvent)
{
	_queue.emplace(pEvent);
	return true;
}

const XFEvent* XFEventQueueDefault::front()
{
	if(!_queue.empty()) //check wether it is empty or not
	{
		const XFEvent* e = _queue.front(); //get the ptr on the first element
		_queue.pop(); //remove it from the list
		return e;
	}
	return nullptr;
}

void XFEventQueueDefault::pop()
{
    if(!_queue.empty()) //check wether it is empty or not
    {
        _queue.pop(); //remove the next event of the list
    }
}

bool XFEventQueueDefault::pend()
{
	while(_queue.empty()) {}
	return true;
}
