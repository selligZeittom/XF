#include "xf/timeout.h"

XFTimeout::XFTimeout(int id, int interval, interface::XFReactive *pBehavior) : XFEvent(XFEventType::Timeout, id, pBehavior)
{
    this->_interval = interval; //number of ticks before timeout
}

XFTimeout::~XFTimeout()
{

}

bool XFTimeout::operator ==(const XFTimeout &timeout) const
{
    //check wether the id and the target equal for both timeout
    return (timeout.getId() == this->getId() && timeout.getBehavior() == this->getBehavior());
}

bool XFTimeout::deleteAfterConsume() const
{
    return true; //as it's dynamically created by the timeoutmanager-default, must be destructed
}
