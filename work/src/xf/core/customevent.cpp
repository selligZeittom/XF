#include "xf/customevent.h"

XFCustomEvent::XFCustomEvent(int id, interface::XFReactive *pBehavior) : XFEvent(XFEventType::Event, id, pBehavior)
{
}

XFCustomEvent::~XFCustomEvent()
{
}

void XFCustomEvent::setDeleteAfterConsume(bool bDeleteAfterConsume)
{
    _bDeleteAfterConsume = bDeleteAfterConsume;
}


