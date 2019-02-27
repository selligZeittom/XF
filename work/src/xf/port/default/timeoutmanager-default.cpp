
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
    XFTimeoutManagerDefault* theTimeoutManager = NULL;
    if(!theTimeoutManager)
    {
        theTimeoutManager = new XFTimeoutManagerDefault();
    }

    return theTimeoutManager;
}

XFTimeoutManagerDefault::~XFTimeoutManagerDefault()
{
    Trace::out("[timeoutmanager-default.cpp] ~XFTimeoutManagerDefault() TBI");
}

void XFTimeoutManagerDefault::start()
{
    Trace::out("[timeoutmanager-default.cpp] ~start() TBI");
}

void XFTimeoutManagerDefault::scheduleTimeout(int32_t timeoutId, int32_t interval, interface::XFReactive *pReactive)
{
    //create the timeout to add to the list
    XFTimeout* tm = new XFTimeout(timeoutId, interval, pReactive);

    //create an iterator at the beginning of the list
    TimeoutList::iterator it = _timeouts.begin();

    //store the total of remaining ticks of some timeouts
    int remainingTicksSum = 0;

    //iterate over the already existing timeouts until the right position is found
    for (; it != _timeouts.end(); ++it)
    {
        //break if the sum is already bigger than the interval
        if(interval < remainingTicksSum + (*it)->getRelTicks())
        {
            break;
        }

        //increment the remainingTicksSum
        remainingTicksSum += (*it)->getRelTicks();
    }

    //insert before that iterator
    _timeouts.insert(it, tm);

    //set the relative ticks for the inserted timeout
    tm->setRelTicks(remainingTicksSum);

    //iterate over the remainings timeouts and decrement their relative ticks
    for (; it != _timeouts.end(); ++it)
    {
        //cut the number of ticks counted by the inserted timeout
        (*it)->setRelTicks((*it)->getRelTicks()- remainingTicksSum);
    }
}

void XFTimeoutManagerDefault::unscheduleTimeout(int32_t timeoutId, interface::XFReactive *pReactive)
{
    int relTicksTmErased = 0;       //number of ticks deleted, must be added to the following timeouts in the list
    bool hasBeenFound = false;      //true once the wanted timeout has been found and deleted from the list

    //create a timeout with the parameters just to use the operator ==
    XFTimeout toDeleteTm(timeoutId, 0, pReactive); //interval is not compared with ==

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
}

void XFTimeoutManagerDefault::tick()
{
    Trace::out("[timeoutmanager-default.cpp] tick()");

    //get the first element of the list
    XFTimeout* tm = _timeouts.front();

    //decrement it
    tm->substractFromRelTicks(1);

    if(tm->getRelTicks() == 0)
    {

    }
}

XFTimeoutManagerDefault::XFTimeoutManagerDefault()
{
    Trace::out("[timeoutmanager-default.cpp] ~XFTimeoutManagerDefault()) TBI");
}

void XFTimeoutManagerDefault::addTimeout(XFTimeout *pNewTimeout)
{
    Trace::out("[timeoutmanager-default.cpp] addTimeout()) TBI");
}

void XFTimeoutManagerDefault::removeTimeouts(int32_t timeoutId, interface::XFReactive *pReactive)
{
    Trace::out("[timeoutmanager-default.cpp] removeTimeouts() TBI");
}

void XFTimeoutManagerDefault::returnTimeout(XFTimeout *pTimeout)
{
    Trace::out("[timeoutmanager-default.cpp] returnTimeout() TBI");
}

#endif // USE_XF_TIMEOUTMANAGER_DEFAULT_IMPLEMENTATION
