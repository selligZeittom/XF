#include <config/xf-config.h>

#if (USE_XF_PORT_IDF_QT_EVENT_QUEUE_IMPLEMENTATION != 0)

#include <assert.h>
#include <QtGlobal>
#include <QMutexLocker>
#include "eventqueue.h"

// TODO: Implement code for XFEventQueuePort class

XFEventQueuePort::XFEventQueuePort()
{

}

XFEventQueuePort::~XFEventQueuePort()
{

}

bool XFEventQueuePort::empty() const
{
    return _queue.isEmpty();
}

bool XFEventQueuePort::push(const XFEvent *pEvent)
{
    _queue.enqueue(pEvent);
    _newEvents.wakeAll();
    return true;
}

const XFEvent *XFEventQueuePort::front()
{
    //_mutex.lock(); //make sure that only one thread can access to that CS
    if(!_queue.isEmpty()) //check wether it is empty or not
    {
        return _queue.head(); //return the pointer on the first event
    }
    else
    {
        return NULL; //return NULL if the queue is empty
    }
    //_mutex.unlock();
}

void XFEventQueuePort::pop()
{
    //_mutex.lock(); //make sure that only one thread can access to that CS
    if(!_queue.isEmpty()) //check wether it is empty or not
    {
        _queue.pop_front(); //remove the next event of the list
    }
    //_mutex.unlock();
}

bool XFEventQueuePort::pend()
{
    _mutex.lock();
    _newEvents.wait(&_mutex);
    _mutex.unlock();
    return true; //return true once an event came
}

#endif // USE_XF_PORT_IDF_QT_EVENT_QUEUE_IMPLEMENTATION
