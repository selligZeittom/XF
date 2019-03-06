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
	this->_pCurrentEvent = NULL;
    this->_isActive = false; //default dispatcher is used
    this->_pDispatcher = pDispatcher; //if the constructor provides a dispatcher : use it !
    if(_pDispatcher == nullptr) //but if it is null then create one...
    {
        _pDispatcher = XFResourceFactory::getInstance()->getDefaultDispatcher();
    }
}

XFBehavior::XFBehavior(bool ownDispatcher)
{
	this->_pCurrentEvent = NULL;
    this->_isActive = ownDispatcher;
    if(_isActive) //create a dispatcher for this instance of behavior
    {
        if(_pDispatcher == nullptr)
        {
            _pDispatcher = XFResourceFactory::getInstance()->createDispatcher();
        }
    }
    else
    {
        _pDispatcher = XFResourceFactory::getInstance()->getDefaultDispatcher();
    }
}

XFBehavior::~XFBehavior()
{
    if(_isActive) //means it got a personnal dispatcher that needs to be deleted
    {
        if(_pDispatcher)
        {
            delete _pDispatcher;
            _pDispatcher = NULL;
        }
    }
}

void XFBehavior::startBehavior()
{
    //create an lauch an init event into the dispatcher
    XFInitialEvent* initEvent = new XFInitialEvent();
    pushEvent(initEvent);
}

void XFBehavior::pushEvent(XFEvent *pEvent)
{
    pEvent->setBehavior(this); //set the target before sending it to the dispatcher
    _pDispatcher->pushEvent(pEvent); //vamos to the dispatcher

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
    if(_pCurrentEvent->getEventType() == XFEvent::XFEventType::Timeout) //only if it is a timeout
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
    XFEventStatus status = processEvent(); //then call the processEvent which will use the _pCurrentEvent
    if(pEvent->deleteAfterConsume() && status == XFEventStatus::Consumed) //if it should be destroyed then delete it
    {
        if(pEvent)
        {
            delete pEvent;
        }
    }
    else if(status == XFEventStatus::Terminate) //shut down the state machine
    {
        if(pEvent->deleteAfterConsume())
        {
            if(pEvent)
            {
                delete pEvent;
            }
        }
    }
    return status;
}
