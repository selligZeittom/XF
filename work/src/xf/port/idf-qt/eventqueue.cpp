#include <config/xf-config.h>

#if (USE_XF_PORT_IDF_QT_EVENT_QUEUE_IMPLEMENTATION != 0)

#include <assert.h>
#include <QtGlobal>
#include <QMutexLocker>
#include "eventqueue.h"
#include "trace/trace.h"
#include "xf/event.h"

XFEventQueuePort::XFEventQueuePort()
{
}

XFEventQueuePort::~XFEventQueuePort()
{
    for(auto e : _queue)
    {
        if(e)
        {
            delete e;
            e = NULL;
        }
    }
}

bool XFEventQueuePort::empty() const
{
    return _queue.isEmpty(); //return wether the queue is empty or not
}

bool XFEventQueuePort::push(const XFEvent *pEvent)
{
    _mutex.lock();
    bool emptyBeforeEnqueue = _queue.empty(); //save state before enqueuing
    _queue.enqueue(pEvent);
    _mutex.unlock();

    if(emptyBeforeEnqueue)
    {
        _newEvents.wakeAll(); //wake up the pend()
    }
    return true;
}

const XFEvent *XFEventQueuePort::front()
{
    if(!_queue.isEmpty()) //check wether it is empty or not
    {
        return _queue.dequeue();
    }
    return NULL; //return NULL if the queue is empty
}

void XFEventQueuePort::pop()
{
    if(!_queue.isEmpty()) //check wether it is empty or not
    {
        _queue.pop_front(); //remove the next event of the list
    }
}

bool XFEventQueuePort::pend()
{
    _mutex.lock();
    _newEvents.wait(&_mutex); //wait for a signal
    _mutex.unlock();

    return true; //return true once an event came
}

#endif // USE_XF_PORT_IDF_QT_EVENT_QUEUE_IMPLEMENTATION
