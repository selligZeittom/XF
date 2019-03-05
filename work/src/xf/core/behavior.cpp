#include <assert.h>
#include "xf/xf.h"
#include "xf/interface/resourcefactory.h"
#include "xf/interface/dispatcher.h"
#include "xf/timeout.h"
#include "xf/initialevent.h"
#include "xf/behavior.h"


using interface::XFResourceFactory;

XFBehavior::XFBehavior(interface::XFDispatcher *pDispatcher)
{
    this->_pDispatcher = pDispatcher;
    if(_pDispatcher == nullptr)
    {
        _pDispatcher = XFResourceFactory::getInstance()->getDefaultDispatcher();
    }

}

XFBehavior::XFBehavior(bool ownDispatcher)
{
    this->_isActive = ownDispatcher;
}

XFBehavior::~XFBehavior()
{

}

void XFBehavior::startBehavior()
{
    XFInitialEvent* initEvent = new XFInitialEvent();
    initEvent->setBehavior(this);
    _pDispatcher->pushEvent(initEvent);

}

void XFBehavior::pushEvent(XFEvent *pEvent)
{
    pEvent->setBehavior(this);
    _pDispatcher->pushEvent(pEvent);
    //process(pEvent);

}

const XFEvent *XFBehavior::getCurrentEvent() const
{
    return this->_pCurrentEvent;
}

interface::XFDispatcher *XFBehavior::getDispatcher()
{
    return this->_pDispatcher;
}

const XFTimeout *XFBehavior::getCurrentTimeout()
{
    if(_pCurrentEvent->getEventType() == XFEvent::XFEventType::Timeout)
    {
        return (XFTimeout*) _pCurrentEvent;
    }
    return NULL;
}

void XFBehavior::setCurrentEvent(const XFEvent *pEvent)
{
    this->_pCurrentEvent = pEvent;

}

XFEventStatus XFBehavior::process(const XFEvent *pEvent)
{
    setCurrentEvent(pEvent); //set the current event first
    processEvent(); //then call the processEvent
}
