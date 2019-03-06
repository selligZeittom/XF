
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

interface::XFTimeoutManager *XFTimeoutManagerDefault::getInstance()
{
    static XFTimeoutManagerDefault* theTimeoutManager = NULL;
    if(!theTimeoutManager) //create the singleton
    {
        theTimeoutManager = new XFTimeoutManagerDefault();
    }
    return theTimeoutManager;
}

XFTimeoutManagerDefault::~XFTimeoutManagerDefault()
{
    //delete the singleton
    if(getInstance())
    {
        delete getInstance();
    }

    //delete the mutex
    if(_pMutex)
    {
        delete _pMutex;
        _pMutex = NULL;
    }

    for(auto t : _timeouts)
    {
        if(t)
        {
            delete t;
            t = NULL;
        }
    }
}

void XFTimeoutManagerDefault::start()
{
    //this will launch the qtimer
    XF_startTimeoutManagerTimer(_tickInterval);
}

void XFTimeoutManagerDefault::scheduleTimeout(int32_t timeoutId, int32_t interval, interface::XFReactive *pReactive)
{
    //create the timeout to add to the list
    XFTimeout* tm = new XFTimeout(timeoutId, interval, pReactive);

    addTimeout(tm); //call the protected method
}

void XFTimeoutManagerDefault::unscheduleTimeout(int32_t timeoutId, interface::XFReactive *pReactive)
{
    removeTimeouts(timeoutId, pReactive); //call the protected method
}

void XFTimeoutManagerDefault::tick()
{
    _pMutex->lock();

    if(_timeouts.size() > 0)
    {
        //get the reference of the first element of the list
        XFTimeout* tm = _timeouts.front();

        //decrement it
        tm->substractFromRelTicks(_tickInterval);

        while(_timeouts.size() > 0)
        {
            //timeout has a relative tick of 0
            if(tm->getRelTicks() <= 0)
            {
                _timeouts.pop_front(); //remove it from the list

                //push into the event queue
                returnTimeout(tm);

                tm = _timeouts.front();
            }
            else
            {
                break;
            }
        }
    }
    _pMutex->unlock();
}

XFTimeoutManagerDefault::XFTimeoutManagerDefault()
{
    _pMutex = XFResourceFactory::getInstance()->createMutex();
}

void XFTimeoutManagerDefault::addTimeout(XFTimeout *pNewTimeout)
{
    //create an iterator at the beginning of the list
    _pMutex->lock();
    TimeoutList::iterator it = _timeouts.begin();

    //store the total of remaining ticks of some timeouts
    int remainingTicksSum = 0;

    //iterate over the already existing timeouts until the right position is found
    for (; it != _timeouts.end(); ++it)
    {
        int deltaTime = remainingTicksSum + (*it)->getRelTicks();
        //break if the sum is already bigger than the interval
        if(deltaTime >= pNewTimeout->getInterval())
        {
            break;
        }

        //increment the remainingTicksSum
        remainingTicksSum += (*it)->getRelTicks();
    }

    int newRelTicks = pNewTimeout->getInterval() - remainingTicksSum;

    //set the relative ticks for the inserted timeout
    pNewTimeout->setRelTicks(newRelTicks);

    //insert before that iterator
    _timeouts.insert(it, pNewTimeout);

    //iterate over the remainings timeouts and decrement their relative ticks
    for (; it != _timeouts.end(); ++it)
    {
        //substract the added
        (*it)->substractFromRelTicks(newRelTicks);
    }
    _pMutex->unlock();
}

void XFTimeoutManagerDefault::removeTimeouts(int32_t timeoutId, interface::XFReactive *pReactive)
{
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
            tm->addToRelTicks(relTicksTmErased);
        }
    }
    _pMutex->unlock();
}

void XFTimeoutManagerDefault::returnTimeout(XFTimeout *pTimeout)
{
    //Trace::out("[timeoutmanager-default.cpp] returnTimeout()");
    pTimeout->getBehavior()->pushEvent(pTimeout);
}

#endif // USE_XF_TIMEOUTMANAGER_DEFAULT_IMPLEMENTATION
