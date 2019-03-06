#include "xf/customevent.h"

XFCustomEvent::XFCustomEvent(int id, interface::XFReactive *pBehavior) : XFEvent(XFEventType::Event, id, pBehavior)
{
	_bDeleteAfterConsume = false;
}

XFCustomEvent::~XFCustomEvent()
{
}

void XFCustomEvent::setDeleteAfterConsume(bool bDeleteAfterConsume)
{
    _bDeleteAfterConsume = bDeleteAfterConsume;
}


