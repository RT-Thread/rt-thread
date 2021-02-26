/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020-06-08     hqfang       the first version.
 *
 */
#include "drv_wdt.h"

#ifdef BSP_USING_WDT


static rt_err_t gd32_wdog_close(rt_watchdog_t *wdt)
{
    rt_uint32_t level;

    level = rt_hw_interrupt_disable();
    rcu_osci_off(RCU_IRC40K);
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t gd32_wdog_open(rt_watchdog_t *wdt, rt_uint16_t oflag)
{
    rt_uint32_t level;

    level = rt_hw_interrupt_disable();
    /* enable IRC40K */
    rcu_osci_on(RCU_IRC40K);
    /* wait till IRC40K is ready */
    while (SUCCESS != rcu_osci_stab_wait(RCU_IRC40K));
    fwdgt_counter_reload();
    fwdgt_enable();
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

static rt_err_t gd32_wdog_init(rt_watchdog_t *wdt)
{
    /* confiure FWDGT counter clock: 40KHz(IRC40K) / 256 = 0.15625 KHz */
    fwdgt_config(FWDGT_RLD_RLD, FWDGT_PSC_DIV256);
    fwdgt_enable();
    return RT_EOK;
}

static rt_err_t gd32_wdog_refresh(rt_watchdog_t *wdt)
{
    rt_uint32_t level;

    level = rt_hw_interrupt_disable();
    fwdgt_counter_reload();
    rt_hw_interrupt_enable(level);

    return RT_EOK;
}

/**
 * @function control wdog
 *
 * @param
 *    wdt  whick wdog used
 *    cmd  control wdog options
 *    args argument of conrtol
 * @retval rt_err_t the status of control result
 *
 *
 */
#define WDT_RELOAD_SECOND       ((FWDGT_RLD & FWDGT_RLD_RLD) / 156)
static rt_err_t gd32_wdog_control(rt_watchdog_t *wdt, int cmd, void *args)
{
    RT_ASSERT(wdt != NULL);

    uint16_t reload_value;
    static uint16_t wdt_started = 0;
    static rt_tick_t last_tick = 0;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
    {
        *(uint16_t *)args = WDT_RELOAD_SECOND;
    }
    break;
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
    {
        RT_ASSERT(*(uint16_t *)args != 0);
        reload_value = *(uint16_t *)args;
        // 6.4ms 1 tick, 1s -> 1000 / 6.4 = 625 / 4 ticks
        reload_value = ((uint32_t)reload_value * 625) / 4;
        fwdgt_write_enable();
        while (FWDGT_STAT & FWDGT_STAT_RUD);
        FWDGT_RLD = FWDGT_RLD_RLD & reload_value;
        fwdgt_write_disable();
    }
    break;
    case RT_DEVICE_CTRL_WDT_GET_TIMELEFT:
        *(uint16_t *)args = WDT_RELOAD_SECOND - \
                            (rt_tick_get() - last_tick) / RT_TICK_PER_SECOND;

        break;
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
    {
        last_tick = rt_tick_get();
        gd32_wdog_refresh(wdt);
    }
    break;
    case RT_DEVICE_CTRL_WDT_START:
    {
        gd32_wdog_open(wdt, *(rt_uint32_t *)args);
        last_tick = rt_tick_get();
        wdt_started = 1;
        while (FWDGT_STAT & FWDGT_STAT_RUD);
    }
    break;
    case RT_DEVICE_CTRL_WDT_STOP:
    {
        gd32_wdog_close(wdt);
        wdt_started = 0;
    }
    break;
    default:
        return RT_EINVAL;
    }

    return RT_EOK;
}

static struct rt_watchdog_ops gd32_wdog_ops =
{
    .init = gd32_wdog_init,
    .control = gd32_wdog_control,
};

static struct rt_watchdog_device gd32_wdt_device;

int rt_hw_wdt_init(void)
{
    int result = RT_EOK;

    rcu_osci_off(RCU_IRC40K);
    gd32_wdt_device.ops = &gd32_wdog_ops;
    result = rt_hw_watchdog_register(&gd32_wdt_device, "wdt", \
                                     RT_DEVICE_FLAG_RDWR, (void *)FWDGT);

    return result;
}

INIT_DEVICE_EXPORT(rt_hw_wdt_init);

#endif /* BSP_USING_WDT */

