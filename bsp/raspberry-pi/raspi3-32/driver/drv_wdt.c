/*
 * Copyright (c) 2006-2019, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2019-07-29     zdzn           first version
 */
#include "drv_wdt.h"

#ifdef BSP_USING_WDT

#define SECS_TO_WDOG_TICKS(x) ((x) << 16)
#define WDOG_TICKS_TO_SECS(x) ((x) >> 16)

static struct raspi_wdt_driver bcm_wdt;

void raspi_watchdog_init(rt_uint32_t time_init)
{
    bcm_wdt.timeout = time_init;
}

void raspi_watchdog_start()
{
    volatile rt_uint32_t cur;
    PM_WDOG = PM_PASSWORD | (SECS_TO_WDOG_TICKS(bcm_wdt.timeout) & PM_WDOG_TIME_SET);
    cur = PM_RSTC;
    PM_RSTC = PM_PASSWORD | (cur & PM_RSTC_WRCFG_CLR) | PM_RSTC_WRCFG_FULL_RESET;
}

void raspi_watchdog_stop()
{
    PM_RSTC = PM_PASSWORD | PM_RSTC_RESET;
}

void raspi_watchdog_clr()
{
    bcm_wdt.timeout = 0;
}

void raspi_watchdog_set_timeout(rt_uint32_t timeout_us)
{
    bcm_wdt.timeout = timeout_us;
}

rt_uint64_t raspi_watchdog_get_timeout()
{
    return bcm_wdt.timeout;
}

rt_uint64_t raspi_watchdog_get_timeleft()
{
    rt_uint32_t ret = PM_WDOG;
    return WDOG_TICKS_TO_SECS(ret & PM_WDOG_TIME_SET);
}

static rt_err_t raspi_wdg_init(rt_watchdog_t *wdt)
{
    /*init for 10S*/
    raspi_watchdog_init(1000000);
    raspi_watchdog_start();
    raspi_watchdog_stop();
    return RT_EOK;
}

static rt_err_t raspi_wdg_control(rt_watchdog_t *wdt, int cmd, void *arg)
{
    rt_uint64_t  timeout_us = 0;
    switch (cmd)
    {
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        timeout_us = *((rt_uint32_t *)arg) * 1000000;
        if (timeout_us >= 0xFFFFFFFF)
            timeout_us = 0xFFFFFFFF;
        raspi_watchdog_set_timeout((rt_uint32_t)timeout_us);
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        timeout_us = raspi_watchdog_get_timeout();
        *((rt_uint32_t *)arg) = timeout_us / 1000000;
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMELEFT:
        timeout_us = raspi_watchdog_get_timeleft();
        *((rt_uint32_t *)arg) = timeout_us / 1000000;
        break;
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        raspi_watchdog_clr();
        break;
    case RT_DEVICE_CTRL_WDT_START:
        raspi_watchdog_start();
        break;
    case RT_DEVICE_CTRL_WDT_STOP:
        raspi_watchdog_stop();
        break;
    default:
        return RT_EIO;
    }
    return RT_EOK;
}

static const struct rt_watchdog_ops raspi_wdg_pos =
{
    raspi_wdg_init,
    raspi_wdg_control,
};

static rt_watchdog_t raspi_wdg;

int rt_hw_wdt_init(void)
{
    raspi_wdg.ops = &raspi_wdg_pos;
    rt_hw_watchdog_register(&raspi_wdg, "wdg", 0, RT_NULL);
    return RT_EOK;
}

INIT_DEVICE_EXPORT(rt_hw_wdt_init);

/**
 * Reboot
 */
int reboot(void)
{
    unsigned int r;

    rt_kprintf("reboot system...\n");
    rt_thread_mdelay(100);
    // trigger a restart by instructing the GPU to boot from partition 0
    r = PM_RSTS; r &= ~0xfffffaaa;
    PM_RSTS = PM_PASSWORD | r;   // boot from partition 0
    PM_WDOG = PM_PASSWORD | 10;
    PM_RSTC = PM_PASSWORD | PM_RSTC_WRCFG_FULL_RESET;
    
    while (1);
    
    return 0;
}
MSH_CMD_EXPORT(reboot,reboot system...);

#endif /*BSP_USING_WDT */
