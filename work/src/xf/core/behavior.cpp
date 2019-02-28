#include <assert.h>
#include "xf/xf.h"
#include "xf/interface/resourcefactory.h"
#include "xf/interface/dispatcher.h"
#include "xf/timeout.h"
#include "xf/initialevent.h"
#include "xf/behavior.h"
#include "trace/trace.h"


using interface::XFResourceFactory;

XFBehavior::XFBehavior(interface::XFDispatcher *pDispatcher)
{
    Trace::out("[behavior.cpp] XFBehavior()");
    this->_pDispatcher = pDispatcher;

}

XFBehavior::XFBehavior(bool ownDispatcher)
{
    Trace::out("[behavior.cpp] XFBehavior()");
    this->_isActive = ownDispatcher;
}

XFBehavior::~XFBehavior()
{
    Trace::out("[behavior.cpp] ~XFBehavior() TBI");

}

void XFBehavior::startBehavior()
{
    Trace::out("[behavior.cpp] startBehavior()");
    _pDispatcher->pushEvent(new XFInitialEvent());

}

void XFBehavior::pushEvent(XFEvent *pEvent)
{
    Trace::out("[behavior.cpp] pushEvent()");
    //_pDispatcher->pushEvent(pEvent);
    process(pEvent);

}

const XFEvent *XFBehavior::getCurrentEvent() const
{
    Trace::out("[behavior.cpp] getCurrentEvent()");
    return this->_pCurrentEvent;
}

interface::XFDispatcher *XFBehavior::getDispatcher()
{
    Trace::out("[behavior.cpp] getDispatcher()");
    return this->_pDispatcher;
}

const XFTimeout *XFBehavior::getCurrentTimeout()
{
    Trace::out("[behavior.cpp] XFBehavior() TBI");
    if(_pCurrentEvent->getEventType() == XFEvent::XFEventType::Timeout)
    {
        return (XFTimeout*) _pCurrentEvent;
    }
    return NULL;
}

void XFBehavior::setCurrentEvent(const XFEvent *pEvent)
{
    Trace::out("[behavior.cpp] setCurrentEvent()");
    this->_pCurrentEvent = pEvent;

}

XFEventStatus XFBehavior::process(const XFEvent *pEvent)
{
    Trace::out("[behavior.cpp] process()");
    setCurrentEvent(pEvent); //set the current event first
    processEvent(); //then call the processEvent

}
