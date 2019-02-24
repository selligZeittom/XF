
#include <config/xf-config.h>

#if (USE_XF_TIMEOUTMANAGER_DEFAULT_IMPLEMENTATION != 0)

#include <assert.h>
#include "xf/interface/reactive.h"
#include "xf/interface/resourcefactory.h"
#include "port-functions.h"
#include "timeoutmanager-default.h"

using interface::XFResourceFactory;

interface::XFTimeoutManager * interface::XFTimeoutManager::getInstance()
{
    return XFTimeoutManagerDefault::getInstance();
}

// TODO: Implement code for XFTimeoutManagerDefault class

interface::XFTimeoutManager *XFTimeoutManagerDefault::getInstance()
{

}

XFTimeoutManagerDefault::~XFTimeoutManagerDefault()
{

}

void XFTimeoutManagerDefault::start()
{

}

void XFTimeoutManagerDefault::scheduleTimeout(int32_t timeoutId, int32_t interval, interface::XFReactive *pReactive)
{
    //create the timeout to add to the list
    XFTimeout* tm = new XFTimeout(timeoutId, interval, pReactive);

    //create an iterator at the beginning of the list
    TimeoutList::iterator it = _timeouts.begin();

    //store the total of remaining ticks of some timeouts
    int remainingTicksSum = 0;

    //iterate over the already existing timeouts until the good place is found
    for (; it != _timeouts.end(); ++it)
    {
        //break if it's the interval is already smaller than the sum
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
    //create an iterator at the beginning of the list
    TimeoutList::iterator it = _timeouts.begin();

    //create a timeout with the parameters just to use the operator ==
    XFTimeout tm(timeoutId, 0, pReactive); //interval is not compared later

    //iterate over the already existing timeouts until the good place is found
    for (; it != _timeouts.end(); ++it)
    {
        //break if it's the interval is already smaller than the sum
        if((*it) == tm)
        {
            if((*it) =! NULL)
            {
                delete (*it); //delete this timeout ptr
            }
            _timeouts.erase(it); //then erase it from the list
            break;
        }
    }
}

void XFTimeoutManagerDefault::tick()
{

}

XFTimeoutManagerDefault::XFTimeoutManagerDefault()
{

}

void XFTimeoutManagerDefault::addTimeout(XFTimeout *pNewTimeout)
{

}

void XFTimeoutManagerDefault::removeTimeouts(int32_t timeoutId, interface::XFReactive *pReactive)
{

}

void XFTimeoutManagerDefault::returnTimeout(XFTimeout *pTimeout)
{

}

#endif // USE_XF_TIMEOUTMANAGER_DEFAULT_IMPLEMENTATION
