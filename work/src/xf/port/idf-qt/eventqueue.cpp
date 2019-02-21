#include <config/xf-config.h>

#if (USE_XF_PORT_IDF_QT_EVENT_QUEUE_IMPLEMENTATION != 0)

#include <assert.h>
#include <QtGlobal>
#include <QMutexLocker>
#include "eventqueue.h"

// TODO: Implement code for XFEventQueuePort class

#endif // USE_XF_PORT_IDF_QT_EVENT_QUEUE_IMPLEMENTATION

bool XFEventQueuePort::empty() const
{

}

bool XFEventQueuePort::push(const XFEvent *pEvent)
{

}

const XFEvent *XFEventQueuePort::front()
{

}

void XFEventQueuePort::pop()
{

}

bool XFEventQueuePort::pend()
{

}
