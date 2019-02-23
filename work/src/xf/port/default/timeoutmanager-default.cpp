
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
    XFTimeout t(timeoutId, pReactive);

    for (TimeoutList::iterator it = _timeouts.begin(); it != _timeouts.end(); ++it)
    {

    }
}

void XFTimeoutManagerDefault::unscheduleTimeout(int32_t timeoutId, interface::XFReactive *pReactive)
{

}

void XFTimeoutManagerDefault::tick()
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
