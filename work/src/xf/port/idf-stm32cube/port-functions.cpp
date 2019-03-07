#include <config/xf-config.h>

#if (USE_XF_PORT_IDF_STM32CUBE_PORT_FUNCTIONS_IMPLEMENTATION != 0)

#include <assert.h>
#include "mcu/mcu.h"
#include "critical/critical.h"
#include "xf/interface/timeoutmanager.h"
#include "xf/port/port-functions.h"

using interface::XFTimeoutManager;

void XF_startTimeoutManagerTimer(uint32_t tickInterval)
{
    (void)tickInterval;

    // SysTick gets already started by the STM32CubeMX HAL.
    // So nothing to do here.
}

//called from the isr
void XF_tick()
{
	interface::XFTimeoutManager::getInstance()->tick();
}

int32_t XF_tickIntervalInMilliseconds()
{
	return interface::XFTimeoutManager::getInstance()->getTickInterval();
}

#endif // USE_XF_PORT_IDF_STM32CUBE_PORT_FUNCTIONS_IMPLEMENTATION
