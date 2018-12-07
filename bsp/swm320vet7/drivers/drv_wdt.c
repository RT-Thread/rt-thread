/******************************************************************************
* @file drv_wdt.c
* @author Zohar_Lee
* @version V1.00
* @date 2018.11.09
* @brief
******************************************************************************/
#include "SWM320.h"
#include "rtthread.h"
#include "rtdevice.h"

#ifdef BSP_USING_WDT

rt_err_t watchdog_init(rt_watchdog_t *wdt)
{
    WDT_Init(WDT, SystemCoreClock / 2, WDT_MODE_INTERRUPT);

    return RT_EOK;
}

rt_err_t watchdog_control(rt_watchdog_t *wdt, int cmd, void *arg)
{
    switch (cmd)
    {
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        *(uint32_t *)arg = WDT->LOAD;
        break;
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        WDT_Stop(WDT);
        WDT->LOAD = SystemCoreClock / 1000 * (*(uint32_t *)arg);
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMELEFT:
        *(uint32_t *)arg = WDT_GetValue(WDT);
        break;
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        WDT_Feed(WDT);
        break;
    case RT_DEVICE_CTRL_WDT_START:
        WDT_Start(WDT);
        break;
    case RT_DEVICE_CTRL_WDT_STOP:
        WDT_Stop(WDT);
        break;
    default:
        break;
    }

    return RT_EOK;
}

rt_watchdog_t _watchdog;
struct rt_watchdog_ops _watchdog_ops =
    {
        watchdog_init,
        watchdog_control};

int drv_watchdog_init(void)
{
    rt_err_t result = RT_EOK;

    WDT_Init(WDT, SystemCoreClock / 2, WDT_MODE_INTERRUPT);

    _watchdog.ops = &_watchdog_ops;

    result = rt_hw_watchdog_register(&_watchdog, "watchdog", RT_DEVICE_FLAG_RDWR, WDT);

    return result;
}
INIT_DEVICE_EXPORT(drv_watchdog_init);

void WDT_Handler(void)
{
    WDT_INTClr(WDT);

    rt_kprintf("%s  %s()  %d\r\n", __FILE__, __func__, __LINE__); //打印位置
}

#endif //BSP_USING_WDT

/******************************* end of file *********************************/
