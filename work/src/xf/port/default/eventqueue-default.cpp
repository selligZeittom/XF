#include <config/xf-config.h>

#if (USE_XF_EVENT_QUEUE_DEFAULT_IMPLEMENTATION != 0)

#include <assert.h>
#include "eventqueue-default.h"
#include "xf/event.h" //Added


XFEventQueueDefault::XFEventQueueDefault()
{
}

XFEventQueueDefault::~XFEventQueueDefault()
{

}

bool XFEventQueueDefault::empty() const
{
	return _queue.empty();
}

bool XFEventQueueDefault::push(const XFEvent* pEvent)
{
	_queue.emplace(pEvent); //put the event into the queue
	return true;
}

const XFEvent* XFEventQueueDefault::front()
{
	if(!_queue.empty()) //check whether it is empty or not
	{
		const XFEvent* e = _queue.front(); //get the ptr on the first element
		_queue.pop(); //remove it from the list
		return e;
	}
	return nullptr;
}

void XFEventQueueDefault::pop()
{
    if(!_queue.empty()) //check whether it is empty or not
    {
        _queue.pop(); //remove the next event of the list
    }
}

bool XFEventQueueDefault::pend()
{
	while(_queue.empty()) {} //this is blocking here as long as the queue is empty
	return true; //after an event came, it returns true
}

#endif // USE_XF_EVENT_QUEUE_DEFAULT_IMPLEMENTATION
