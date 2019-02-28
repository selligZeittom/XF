#include "xf/timeout.h"

XFTimeout::XFTimeout(int id, int interval, interface::XFReactive *pBehavior) : XFEvent(XFEventType::Timeout, id, pBehavior)
{
    this->_interval = interval;
}

XFTimeout::~XFTimeout()
{

}

bool XFTimeout::operator ==(const XFTimeout &timeout) const
{
    return (timeout.getId() == this->getId() && timeout.getBehavior() == this->getBehavior());
}

bool XFTimeout::deleteAfterConsume() const
{
    return true;
}
