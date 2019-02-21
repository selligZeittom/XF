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

// TODO: Implement XF_tick() and XF_tickIntervalInMilliseconds() function

#endif // USE_XF_PORT_IDF_STM32CUBE_PORT_FUNCTIONS_IMPLEMENTATION
