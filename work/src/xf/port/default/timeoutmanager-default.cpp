
#include <config/xf-config.h>

#if (USE_XF_TIMEOUTMANAGER_DEFAULT_IMPLEMENTATION != 0)

#include <assert.h>
#include "xf/interface/reactive.h"
#include "xf/interface/resourcefactory.h"
#include "port-functions.h"
#include "timeoutmanager-default.h"
#include "trace/trace.h"

using interface::XFResourceFactory;

interface::XFTimeoutManager * interface::XFTimeoutManager::getInstance()
{
    return XFTimeoutManagerDefault::getInstance();
}

// TODO: Implement code for XFTimeoutManagerDefault class

interface::XFTimeoutManager *XFTimeoutManagerDefault::getInstance()
{
    static XFTimeoutManagerDefault* theTimeoutManager = NULL;
    if(!theTimeoutManager)
    {
        theTimeoutManager = new XFTimeoutManagerDefault();
        Trace::out("[timeoutmanager-default.cpp] new timeoutmanager created");
    }
    return theTimeoutManager;
}

XFTimeoutManagerDefault::~XFTimeoutManagerDefault()
{
    Trace::out("[timeoutmanager-default.cpp] ~XFTimeoutManagerDefault() destructor TBI");
}

void XFTimeoutManagerDefault::start()
{
    Trace::out("[timeoutmanager-default.cpp] start()");
    XF_startTimeoutManagerTimer(_tickInterval);
}

void XFTimeoutManagerDefault::scheduleTimeout(int32_t timeoutId, int32_t interval, interface::XFReactive *pReactive)
{
    Trace::out("[timeoutmanager-default.cpp] scheduleTimeout()");

    //create the timeout to add to the list
    XFTimeout* tm = new XFTimeout(timeoutId, interval, pReactive);

    addTimeout(tm); //call the protected method
}

void XFTimeoutManagerDefault::unscheduleTimeout(int32_t timeoutId, interface::XFReactive *pReactive)
{
    Trace::out("[timeoutmanager-default.cpp] unscheduleTimeout()");

    removeTimeouts(timeoutId, pReactive); //call the protected method
}

void XFTimeoutManagerDefault::tick()
{
    //Trace::out("[timeoutmanager-default.cpp] tick()");

    //get the reference of the first element of the list
    _pMutex->lock();
    if(_timeouts.size() > 0)
    {
        XFTimeout* tm = _timeouts.front();

        //decrement it
        tm->substractFromRelTicks(_tickInterval);

        if(tm->getRelTicks() == 0)
        {
            _timeouts.pop_front(); //remove it from the list

            //push into the event queue
            returnTimeout(tm);
        }
    }
    _pMutex->unlock();
}

XFTimeoutManagerDefault::XFTimeoutManagerDefault()
{
    Trace::out("[timeoutmanager-default.cpp] XFTimeoutManagerDefault()) TBI");
    _pMutex = XFResourceFactory::getInstance()->createMutex();
}

void XFTimeoutManagerDefault::addTimeout(XFTimeout *pNewTimeout)
{
    Trace::out("[timeoutmanager-default.cpp] addTimeout()");
    //create an iterator at the beginning of the list
    _pMutex->lock();
    TimeoutList::iterator it = _timeouts.begin();

    //store the total of remaining ticks of some timeouts
    int remainingTicksSum = 0;

    //iterate over the already existing timeouts until the right position is found
    for (; it != _timeouts.end(); ++it)
    {
        //break if the sum is already bigger than the interval
        if(pNewTimeout->getInterval() < remainingTicksSum + (*it)->getRelTicks())
        {
            break;
        }

        //increment the remainingTicksSum
        remainingTicksSum += (*it)->getRelTicks();
    }

    //insert before that iterator
    _timeouts.insert(it, pNewTimeout);

    //set the relative ticks for the inserted timeout
    pNewTimeout->setRelTicks(remainingTicksSum);

    //iterate over the remainings timeouts and decrement their relative ticks
    for (; it != _timeouts.end(); ++it)
    {
        //substract the added
        (*it)->addToRelTicks(remainingTicksSum);
    }
    _pMutex->unlock();
}

void XFTimeoutManagerDefault::removeTimeouts(int32_t timeoutId, interface::XFReactive *pReactive)
{
    Trace::out("[timeoutmanager-default.cpp] removeTimeouts()");

    int relTicksTmErased = 0;       //number of ticks deleted, must be added to the following timeouts in the list
    bool hasBeenFound = false;      //true once the wanted timeout has been found and deleted from the list

    //create a timeout with the parameters just to use the operator ==
    XFTimeout toDeleteTm(timeoutId, 0, pReactive); //interval is not compared with ==

    _pMutex->lock();
    //iterate over the already existing timeouts until the right timeout is found
    for (XFTimeout* tm : _timeouts)
    {
        if(*tm == toDeleteTm && !hasBeenFound)
        {
            //first save the relatives ticks that are remaining
            relTicksTmErased = tm->getRelTicks();

            _timeouts.remove(tm); //then remove it from the list

            if(tm != NULL)
            {
                delete tm; //delete this timeout ptr
            }
            continue; //goto next iteration
        }

        //after it has been found, adjust the relTicks
        if(hasBeenFound)
        {
            tm->setRelTicks(tm->getRelTicks() + relTicksTmErased);
        }
    }
    _pMutex->unlock();
}

void XFTimeoutManagerDefault::returnTimeout(XFTimeout *pTimeout)
{
    Trace::out("[timeoutmanager-default.cpp] returnTimeout() TBI");
    pTimeout->getBehavior()->pushEvent(pTimeout);
}

#endif // USE_XF_TIMEOUTMANAGER_DEFAULT_IMPLEMENTATION
