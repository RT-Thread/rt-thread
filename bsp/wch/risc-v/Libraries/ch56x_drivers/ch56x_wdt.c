/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-07-20     Emuzit            first version
 */
#include <rthw.h>
#include "drivers/dev_watchdog.h"
#include "ch56x_sys.h"

#define WDOG_HICOUNT_MAX    0xfff  // enough to hold (4095 * 120M/524288) >> 8

struct watchdog_device
{
    rt_watchdog_t parent;
    volatile uint32_t hicount;
    uint32_t timeout;
    uint32_t reload;
    uint8_t is_start;
};

static struct watchdog_device watchdog_device;

static void wdt_reload_counter(rt_watchdog_t *wdt, int cmd)
{
    struct watchdog_device *wdt_dev = (void *)wdt;

    volatile struct sys_registers *sys = (void *)SYS_REG_BASE;

    rt_base_t level;

    level = rt_hw_interrupt_disable();
    /* reload WDOG_COUNT also clears RB_WDOG_INT_FLAG*/
    sys->WDOG_COUNT = (uint8_t)wdt_dev->reload;
    wdt_dev->hicount = wdt_dev->reload >> 8;
    if (cmd != RT_DEVICE_CTRL_WDT_KEEPALIVE && wdt_dev->is_start)
    {
        sys_safe_access_enter(sys);
        if ((wdt_dev->reload >> 8) == WDOG_HICOUNT_MAX)
        {
            /* WDOG_COUNT can work on its own, no wdog_irq needed */
            sys->RST_WDOG_CTRL.reg = wdog_ctrl_wdat(RB_WDOG_RST_EN);
            rt_hw_interrupt_mask(WDOG_IRQn);
        }
        else
        {
            /* Extend wdt with wdt_dev->hicount through wdog_irq.
             * CAVEAT: wdt not effective if global interrupt disabled !!
            */
            sys->RST_WDOG_CTRL.reg = wdog_ctrl_wdat(RB_WDOG_INT_EN);
            rt_hw_interrupt_umask(WDOG_IRQn);
        }
        sys_safe_access_leave(sys);
    }
    rt_hw_interrupt_enable(level);
}

static uint32_t wdt_get_timeleft(rt_watchdog_t *wdt)
{
    struct watchdog_device *wdt_dev = (void *)wdt;

    volatile struct sys_registers *sys = (void *)SYS_REG_BASE;

    uint32_t countleft;
    uint64_t count64;

    if ((wdt_dev->reload >> 8) == WDOG_HICOUNT_MAX)
    {
        /* WDOG_COUNT can work on its own, without hicount */
        countleft = 0xff - sys->WDOG_COUNT;
    }
    else
    {
        uint32_t c1 = sys->WDOG_COUNT;
        uint32_t hc = wdt_dev->hicount;
        uint32_t c2 = sys->WDOG_COUNT;
        /* check if WDOG_COUNT overflows between c1/c2 reads */
        if (c2 < c1)
        {
            rt_base_t level = rt_hw_interrupt_disable();
            hc = wdt_dev->hicount;
            if (sys->RST_WDOG_CTRL.wdog_int_flag && sys->RST_WDOG_CTRL.wdog_int_en)
            {
                hc++;
            }
            rt_hw_interrupt_enable(level);
        }
        countleft = ((WDOG_HICOUNT_MAX << 8) + 0xff) - ((hc << 8) + c2);
    }

    /* convert wdt count to seconds : count / (Fsys/524288) */
    count64 = countleft;
    return (uint32_t)((count64 << 19) / sys_hclk_get());
}

static uint32_t _convert_timeout_to_reload(uint32_t seconds)
{
    uint32_t N, R, Fsys, reload = -1;

    /* timeout is limited to 4095, not to overflow 32-bit (T * 2^19) */
    if (seconds < 4096)
    {
        /* watchdog timer is clocked at Fsys/524288, arround 3~228Hz */
        Fsys = sys_hclk_get();
        /* T * (Fsys/2^19) => (T * N) + T * (R/2^19) */
        N = Fsys >> 19;
        R = Fsys & 0x7ffff;
        reload = (WDOG_HICOUNT_MAX << 8) + 0xff;
        reload -= seconds * N + ((seconds * R) >> 19) + 1;
    }

    return reload;
}

static void _stop_wdog_operation()
{
    volatile struct sys_registers *sys = (void *)SYS_REG_BASE;

    rt_base_t level = rt_hw_interrupt_disable();
    sys_safe_access_enter(sys);
    sys->RST_WDOG_CTRL.reg = wdog_ctrl_wdat(RB_WDOG_INT_FLAG);
    sys_safe_access_leave(sys);
    rt_hw_interrupt_enable(level);

    rt_hw_interrupt_mask(WDOG_IRQn);
}

static rt_err_t wdt_init(rt_watchdog_t *wdt)
{
    struct watchdog_device *wdt_dev = (void *)wdt;

    _stop_wdog_operation();
    wdt_dev->is_start = 0;
    wdt_dev->timeout = -1;
    wdt_dev->reload = -1;

    return RT_EOK;
}

static rt_err_t wdt_control(rt_watchdog_t *wdt, int cmd, void *arg)
{
    struct watchdog_device *wdt_dev = (void *)wdt;

    uint32_t reload, timeout;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        wdt_reload_counter(wdt, cmd);
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMELEFT:
        *((uint32_t *)arg) = wdt_get_timeleft(wdt);
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        *((uint32_t *)arg) = wdt_dev->timeout;
        break;
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        /* CAVEAT: Setting timeout larger than an 8-bit WDOG_COUNT can
         * hold turns the wdog into interrupt mode, which makes wdog
         * usless if cause of death is lost global interrupt enable.
        */
        timeout = *((uint32_t *)arg);
        reload = _convert_timeout_to_reload(timeout);
        if ((reload >> 8) > WDOG_HICOUNT_MAX)
        {
            return -RT_EINVAL;
        }
        wdt_dev->timeout = timeout;
        wdt_dev->reload = reload;
        /* FIXME: code example implies wdt started by SET_TIMEOUT ? */
    case RT_DEVICE_CTRL_WDT_START:
        if ((wdt_dev->reload >> 8) > WDOG_HICOUNT_MAX)
        {
            return -RT_EINVAL;
        }
        wdt_dev->is_start = 1;
        wdt_reload_counter(wdt, cmd);
        break;
    case RT_DEVICE_CTRL_WDT_STOP:
        _stop_wdog_operation();
        wdt_dev->is_start = 0;
        break;
    default:
        return -RT_ERROR;
    }

    return RT_EOK;
}

static struct rt_watchdog_ops watchdog_ops =
{
    .init = wdt_init,
    .control = wdt_control,
};

int rt_hw_wdt_init(void)
{
    rt_uint32_t flag;

    watchdog_device.parent.ops = &watchdog_ops;

    flag = RT_DEVICE_FLAG_DEACTIVATE;
    return rt_hw_watchdog_register(&watchdog_device.parent, "wdt", flag, RT_NULL);
}
INIT_BOARD_EXPORT(rt_hw_wdt_init);

void wdog_irq_handler(void) __attribute__((interrupt()));
void wdog_irq_handler(void)
{
    volatile struct pfic_registers *pfic;
    volatile struct sys_registers *sys;

    rt_interrupt_enter();

    sys = (struct sys_registers *)SYS_REG_BASE;
    /* FIXME: RB_WDOG_INT_FLAG seems completely not functioning at all !!
     * It's not set at WDOG_COUNT overflow, writing 1 to it does not clear
     * wdt interrupt. Bit 16 of pfic->IPR[0] is not effective thereof.
    */
    if (watchdog_device.hicount < WDOG_HICOUNT_MAX)
    {
        watchdog_device.hicount++;
        /* clear interrupt flag */
        //sys->RST_WDOG_CTRL.reg |= RB_WDOG_INT_FLAG;
        sys->WDOG_COUNT = sys->WDOG_COUNT;
    }
    else
    {
        /* reset system if watchdog timeout */
        uint8_t u8v = RB_SOFTWARE_RESET | RB_WDOG_INT_FLAG;
        sys_safe_access_enter(sys);
        sys->RST_WDOG_CTRL.reg = wdog_ctrl_wdat(u8v);
        sys_safe_access_leave(sys);
    }

    rt_interrupt_leave();
}
