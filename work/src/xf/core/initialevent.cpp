#include "xf/initialevent.h"

XFInitialEvent::XFInitialEvent() : XFEvent(XFEventType::Initial,  0, nullptr)
{

}

XFInitialEvent::~XFInitialEvent()
{

}

bool XFInitialEvent::deleteAfterConsume() const
{
    return true;
}
