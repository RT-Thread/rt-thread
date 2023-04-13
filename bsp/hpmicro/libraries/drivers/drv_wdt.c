/*
 * Copyright (c) 2021 - 2022 hpmicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <rthw.h>
#include <rtdevice.h>
#include <rtdbg.h>
#include "board.h"
#include "drv_wdt.h"
#include "hpm_wdg_drv.h"
#include "hpm_sysctl_drv.h"


#ifdef BSP_USING_WDG


typedef struct hpm_wdog
{
    WDG_Type *wdog_base;
    char *device_name;
    clock_name_t clock_name;
    uint32_t irq_num;
    rt_watchdog_t *wdog;
}hpm_wdog_t;

static rt_err_t hpm_wdog_init(rt_watchdog_t *wdt);
static rt_err_t hpm_wdog_open(rt_watchdog_t *wdt, rt_uint16_t oflag);
static rt_err_t hpm_wdog_close(rt_watchdog_t *wdt);
static rt_err_t hpm_wdog_refresh(rt_watchdog_t *wdt);
static rt_err_t hpm_wdog_control(rt_watchdog_t *wdt, int cmd, void *args);

static void hpm_wdog_isr(rt_watchdog_t *wdt);

static wdg_control_t wdog_ctrl = {
    .reset_interval = reset_interval_clock_period_mult_16k,
    .interrupt_interval = interrupt_interval_clock_period_multi_8k,
    .reset_enable = true,
    .interrupt_enable = false,
    .clksrc = wdg_clksrc_extclk,
    .wdg_enable = false,
};

#if defined(BSP_USING_WDG0)
rt_watchdog_t wdog0;
void wdog0_isr(void)
{
    hpm_wdog_isr(&wdog0);
}
SDK_DECLARE_EXT_ISR_M(IRQn_WDOG0, wdog0_isr)
#endif

#if defined(BSP_USING_WDG1)
rt_watchdog_t wdog1;
void wdog1_isr(void)
{
    hpm_wdog_isr(&wdog1);
}
SDK_DECLARE_EXT_ISR_M(IRQn_WDOG1, wdog1_isr)
#endif

#if defined(BSP_USING_WDG2)
rt_watchdog_t wdog2;
void wdog2_isr(void)
{
    hpm_wdog_isr(&wdog2);
}
SDK_DECLARE_EXT_ISR_M(IRQn_WDOG2, wdog2_isr)
#endif

#if defined(BSP_USING_WDG3)
rt_watchdog_t wdog3;
void wdog3_isr(void)
{
    hpm_wdog_isr(&wdog3);
}
SDK_DECLARE_EXT_ISR_M(IRQn_WDOG3, wdog3_isr)
#endif

static hpm_wdog_t wdogs[] = {
#ifdef BSP_USING_WDG0
    {
        .wdog_base = HPM_WDG0,
        .device_name = "wdt0",
        .clock_name = clock_watchdog0,
        .irq_num = IRQn_WDG0,
        .wdog = &wdog0,
    },
#endif

#ifdef BSP_USING_WDG1
    {
        .wdog_base = HPM_WDG1,
        .device_name = "wdt1",
        .clock_name = clock_watchdog1,
        .irq_num = IRQn_WDG1,
        .wdog = &wdog1,
    },
#endif

#ifdef BSP_USING_WDG2
    {
        .wdog_base = HPM_WDG2,
        .device_name = "wdt2",
        .clock_name = clock_watchdog2,
        .irq_num = IRQn_WDG2,
        .wdog = &wdog2,
    },
#endif

#ifdef BSP_USING_WDG3
    {
        .wdog_name = HPM_WDG3,
        .device_name = "wdt3",
        .clock_name = clock_watchdog3,
        .irq_num = IRQn_WDG3,
        .wdog = &wdog3,
    },
#endif
};

static struct rt_watchdog_ops hpm_wdog_ops = {
    .init = hpm_wdog_init,
    .control = hpm_wdog_control,
};

static rt_err_t hpm_wdog_init(rt_watchdog_t *wdt)
{
    hpm_wdog_t *hpm_wdog = (hpm_wdog_t*)wdt->parent.user_data;
    WDG_Type *base = hpm_wdog->wdog_base;

    wdg_init(base, &wdog_ctrl);

    return RT_EOK;
}

static rt_err_t hpm_wdog_open(rt_watchdog_t *wdt, rt_uint16_t oflag)
{
    hpm_wdog_t *hpm_wdog = (hpm_wdog_t*)wdt->parent.user_data;
    WDG_Type *base = hpm_wdog->wdog_base;

    rt_enter_critical();
    wdg_enable(base);
    rt_exit_critical();
}

static rt_err_t hpm_wdog_close(rt_watchdog_t *wdt)
{
    hpm_wdog_t *hpm_wdog = (hpm_wdog_t*)wdt->parent.user_data;
    WDG_Type *base = hpm_wdog->wdog_base;

    rt_enter_critical();
    wdg_disable(base);
    rt_exit_critical();

    return RT_EOK;
}

static rt_err_t hpm_wdog_refresh(rt_watchdog_t *wdt)
{
    hpm_wdog_t *hpm_wdog = (hpm_wdog_t*)wdt->parent.user_data;
    WDG_Type *base = hpm_wdog->wdog_base;

    rt_enter_critical();
    wdg_restart(base);
    rt_exit_critical();

    return RT_EOK;
}

static rt_err_t hpm_wdog_control(rt_watchdog_t *wdt, int cmd, void *args)
{
    rt_err_t ret = RT_EOK;

    hpm_wdog_t *hpm_wdog = (hpm_wdog_t*)wdt->parent.user_data;
    WDG_Type *base = hpm_wdog->wdog_base;

    uint32_t temp;
    switch (cmd)
    {
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        temp = wdg_get_total_reset_interval_in_us(base, WDG_EXT_CLK_FREQ);
        temp /= 1000000UL; /* Convert to seconds */
        *(uint32_t *)args = temp;
        break;
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        RT_ASSERT(*(uint32_t *)args != 0);
        temp = *(uint32_t *)args;
        temp *= 1000000U; /* Convert to microseconds */
        wdog_ctrl.interrupt_interval = wdg_convert_interrupt_interval_from_us(WDG_EXT_CLK_FREQ, temp);
        wdog_ctrl.reset_interval = reset_interval_clock_period_mult_128;
        wdog_ctrl.reset_enable = true;
        wdog_ctrl.interrupt_enable = true;
        wdog_ctrl.clksrc = wdg_clksrc_extclk;
        wdog_ctrl.wdg_enable = false;
        hpm_wdog_init(wdt);
        break;
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        hpm_wdog_refresh(wdt);
        break;
    case RT_DEVICE_CTRL_WDT_START:
        hpm_wdog_open(wdt, *(uint16_t*)args);
        break;
    case RT_DEVICE_CTRL_WDT_STOP:
        hpm_wdog_close(wdt);
        break;
    default:
        ret = -RT_EINVAL;
        break;
    }

    return RT_EOK;
}

void hpm_wdog_isr(rt_watchdog_t *wdt)
{
    hpm_wdog_t *hpm_wdog = (hpm_wdog_t*)wdt->parent.user_data;
    WDG_Type *base = hpm_wdog->wdog_base;

    uint32_t status = wdg_get_status(base);

    if (IS_HPM_BITMASK_SET(status, WDG_ST_INTEXPIRED_MASK)) {
        wdg_clear_status(base, WDG_ST_INTEXPIRED_MASK);
    }
}

int rt_hw_wdt_init(void)
{
    rt_err_t err = RT_EOK;

#if defined(BSP_USING_WDG)
    for (uint32_t i = 0; i < sizeof(wdogs) / sizeof(wdogs[0]); i++)
    {
        wdogs[i].wdog->ops = &hpm_wdog_ops;
        clock_add_to_group(wdogs[i].clock_name, 0);
        err = rt_hw_watchdog_register(wdogs[i].wdog, wdogs[i].device_name, RT_DEVICE_FLAG_RDWR, (void *)&wdogs[i]);
        if (err != RT_EOK)
        {
            LOG_E("rt device %s failed, status=%d\n", wdogs[i].device_name, err);
        }
    }
#endif
    return err;
}

INIT_BOARD_EXPORT(rt_hw_wdt_init);
#endif /* RT_USING_WDT */