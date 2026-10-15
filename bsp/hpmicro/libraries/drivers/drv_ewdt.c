/*
 * Copyright (c) 2023-2025 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#include <rthw.h>
#include <rtdevice.h>
#include <rtdbg.h>
#include "board.h"
#include "drv_ewdt.h"
#include "hpm_ewdg_drv.h"
#include "hpm_sysctl_drv.h"


#ifdef BSP_USING_EWDG

#define EWDG_CNT_CLK_FREQ 32768UL


typedef struct hpm_wdog
{
    EWDG_Type *wdog_base;
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

#ifndef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
static void hpm_wdog_isr(rt_watchdog_t *wdt);

/* Macro to declare watchdog device and ISR handler */
#define HPM_EWDG_DECLARE_DEVICE_ISR(idx) \
    rt_watchdog_t wdog##idx; \
    SDK_DECLARE_EXT_ISR_M(IRQn_EWDG##idx, wdog##idx##_isr) \
    void wdog##idx##_isr(void) \
    { \
        hpm_wdog_isr(&wdog##idx); \
    }

#if defined(BSP_USING_EWDG0)
HPM_EWDG_DECLARE_DEVICE_ISR(0)
#endif

#if defined(BSP_USING_EWDG1)
HPM_EWDG_DECLARE_DEVICE_ISR(1)
#endif

#if defined(BSP_USING_EWDG2)
HPM_EWDG_DECLARE_DEVICE_ISR(2)
#endif

#if defined(BSP_USING_EWDG3)
HPM_EWDG_DECLARE_DEVICE_ISR(3)
#endif
#else
#ifdef BSP_USING_EWDG0
rt_watchdog_t wdog0;
#endif
#ifdef BSP_USING_EWDG1
rt_watchdog_t wdog1;
#endif
#ifdef BSP_USING_EWDG2
rt_watchdog_t wdog2;
#endif
#ifdef BSP_USING_EWDG3
rt_watchdog_t wdog3;
#endif
static void hpm_wdog_isr(int vector, rt_watchdog_t *wdt);
#endif /* HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK */

/* Macro to configure watchdog instance */
#define HPM_EWDG_CONFIG(idx) \
    { \
        .wdog_base = HPM_EWDG##idx, \
        .device_name = "wdt"#idx, \
        .clock_name = clock_watchdog##idx, \
        .irq_num = IRQn_EWDG##idx, \
        .wdog = &wdog##idx, \
    }

#ifdef BSP_USING_EWDG0
rt_watchdog_t wdog0;
#endif
#ifdef BSP_USING_EWDG1
rt_watchdog_t wdog1;
#endif
#ifdef BSP_USING_EWDG2
rt_watchdog_t wdog2;
#endif
#ifdef BSP_USING_EWDG3
rt_watchdog_t wdog3;
#endif

static hpm_wdog_t wdogs[] = {
#ifdef BSP_USING_EWDG0
    HPM_EWDG_CONFIG(0),
#endif

#ifdef BSP_USING_EWDG1
    HPM_EWDG_CONFIG(1),
#endif

#ifdef BSP_USING_EWDG2
    HPM_EWDG_CONFIG(2),
#endif

#ifdef BSP_USING_EWDG3
    HPM_EWDG_CONFIG(3),
#endif
};

static struct rt_watchdog_ops hpm_wdog_ops = {
    .init = hpm_wdog_init,
    .control = hpm_wdog_control,
};

static rt_err_t hpm_wdog_init(rt_watchdog_t *wdt)
{
    hpm_wdog_t *hpm_wdog = (hpm_wdog_t*)wdt->parent.user_data;
    EWDG_Type *base = hpm_wdog->wdog_base;

    ewdg_config_t config;

    LOG_I("Init Watchdog\n");
    ewdg_get_default_config(base, &config);
    /* Enable EWDG */
    config.enable_watchdog = true;
    config.ctrl_config.use_lowlevel_timeout = false;
    /* Enable EWDG Timeout Reset */
    config.int_rst_config.enable_timeout_reset = true;
    /* Set EWDG Count clock source to OSC32 */
    config.ctrl_config.cnt_clk_sel = ewdg_cnt_clk_src_ext_osc_clk;

    /* Set the EWDG reset timeout to 101ms */
    config.cnt_src_freq = EWDG_CNT_CLK_FREQ;
    config.ctrl_config.timeout_reset_us = 101UL * 1000UL;

    ewdg_init(base, &config);

    return RT_EOK;
}

static rt_err_t hpm_wdog_open(rt_watchdog_t *wdt, rt_uint16_t oflag)
{
    hpm_wdog_t *hpm_wdog = (hpm_wdog_t*)wdt->parent.user_data;
    EWDG_Type *base = hpm_wdog->wdog_base;

    rt_enter_critical();
    ewdg_enable(base);
    rt_exit_critical();
    return RT_EOK;
}

static rt_err_t hpm_wdog_close(rt_watchdog_t *wdt)
{
    hpm_wdog_t *hpm_wdog = (hpm_wdog_t*)wdt->parent.user_data;
    EWDG_Type *base = hpm_wdog->wdog_base;

    rt_enter_critical();
    ewdg_disable(base);
    rt_exit_critical();

    return RT_EOK;
}

static rt_err_t hpm_wdog_refresh(rt_watchdog_t *wdt)
{
    hpm_wdog_t *hpm_wdog = (hpm_wdog_t*)wdt->parent.user_data;
    EWDG_Type *base = hpm_wdog->wdog_base;

    rt_enter_critical();
    ewdg_refresh(base);
    rt_exit_critical();

    return RT_EOK;
}

static rt_err_t hpm_wdog_control(rt_watchdog_t *wdt, int cmd, void *args)
{
    rt_err_t ret = RT_EOK;

    hpm_wdog_t *hpm_wdog = (hpm_wdog_t*)wdt->parent.user_data;
    EWDG_Type *base = hpm_wdog->wdog_base;

    ewdg_config_t config;

    uint32_t temp;
    switch (cmd)
    {
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        RT_ASSERT(*(uint32_t *)args != 0);
        temp = *(uint32_t *)args;
        temp *= 1000000U; /* Convert to microseconds */

        ewdg_get_default_config(base, &config);
        config.enable_watchdog = true;
        config.int_rst_config.enable_timeout_reset = true;
        config.ctrl_config.use_lowlevel_timeout = false;
        uint32_t ewdg_src_clk_freq = EWDG_CNT_CLK_FREQ;
        config.ctrl_config.cnt_clk_sel = ewdg_cnt_clk_src_ext_osc_clk;

        /* Set the EWDG reset timeout to 1 second */
        config.cnt_src_freq = ewdg_src_clk_freq;
        config.ctrl_config.timeout_reset_us = temp;

        /* Initialize the EWDG */
        hpm_stat_t status = ewdg_init(base, &config);
        if (status != status_success) {
            LOG_E(" EWDG initialization failed, error_code=%d\n", status);
        }
        /* delay 1ms to ensure above configure take effective*/
        rt_thread_mdelay(1);
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
        ret = RT_EINVAL;
        break;
    }

    return ret;
}

#ifndef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
void hpm_wdog_isr(rt_watchdog_t *wdt)
#else
void hpm_wdog_isr(int vector, rt_watchdog_t *wdt)
#endif /* HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK */
{
    hpm_wdog_t *hpm_wdog = (hpm_wdog_t*)wdt->parent.user_data;
    EWDG_Type *base = hpm_wdog->wdog_base;

    uint32_t ewdg_stat = ewdg_get_status_flags(base);

    if ((ewdg_stat & EWDG_INT_TIMEOUT) != 0) {
        ewdg_refresh(base);
    }
    ewdg_clear_status_flags(base, ewdg_stat);
}

int rt_hw_wdt_init(void)
{
    rt_err_t err = RT_EOK;

#if defined(BSP_USING_EWDG)
    for (uint32_t i = 0; i < sizeof(wdogs) / sizeof(wdogs[0]); i++)
    {
        wdogs[i].wdog->ops = &hpm_wdog_ops;
        clock_add_to_group(wdogs[i].clock_name, 0);
        err = rt_hw_watchdog_register(wdogs[i].wdog, wdogs[i].device_name, RT_DEVICE_FLAG_RDWR, (void *)&wdogs[i]);
        if (err != RT_EOK)
        {
            LOG_E("rt device %s failed, status=%d\n", wdogs[i].device_name, err);
        }
#ifdef HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK
        /* Register EWDT device to irq table */
        rt_hw_interrupt_install(wdogs[i].irq_num, (rt_isr_handler_t)hpm_wdog_isr, &wdogs[i], wdogs[i].device_name);
#endif /* HPM_USING_RTTHREAD_INTERRUPT_FRAMEWORK */
    }
#endif
    return err;
}

INIT_BOARD_EXPORT(rt_hw_wdt_init);
#endif /* RT_USING_WDT */