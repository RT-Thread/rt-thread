/*
 * Copyright (c) 2023 HPMicro
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

static void hpm_wdog_isr(rt_watchdog_t *wdt);

#if defined(BSP_USING_EWDG0)
rt_watchdog_t wdog0;
void wdog0_isr(void)
{
    hpm_wdog_isr(&wdog0);
}
SDK_DECLARE_EXT_ISR_M(IRQn_EWDG0, wdog0_isr)
#endif

#if defined(BSP_USING_EWDG1)
rt_watchdog_t wdog1;
void wdog1_isr(void)
{
    hpm_wdog_isr(&wdog1);
}
SDK_DECLARE_EXT_ISR_M(IRQn_EWDG1, wdog1_isr)
#endif

#if defined(BSP_USING_EWDG2)
rt_watchdog_t wdog2;
void wdog2_isr(void)
{
    hpm_wdog_isr(&wdog2);
}
SDK_DECLARE_EXT_ISR_M(IRQn_EWDG2, wdog2_isr)
#endif

#if defined(BSP_USING_EWDG3)
rt_watchdog_t wdog3;
void wdog3_isr(void)
{
    hpm_wdog_isr(&wdog3);
}
SDK_DECLARE_EXT_ISR_M(IRQn_EWDG3, wdog3_isr)
#endif

static hpm_wdog_t wdogs[] = {
#ifdef BSP_USING_EWDG0
    {
        .wdog_base = HPM_EWDG0,
        .device_name = "wdt0",
        .clock_name = clock_watchdog0,
        .irq_num = IRQn_EWDG0,
        .wdog = &wdog0,
    },
#endif

#ifdef BSP_USING_EWDG1
    {
        .wdog_base = HPM_EWDG1,
        .device_name = "wdt1",
        .clock_name = clock_watchdog1,
        .irq_num = IRQn_EWDG1,
        .wdog = &wdog1,
    },
#endif

#ifdef BSP_USING_EWDG2
    {
        .wdog_base = HPM_EWDG2,
        .device_name = "wdt2",
        .clock_name = clock_watchdog2,
        .irq_num = IRQn_EWDG2,
        .wdog = &wdog2,
    },
#endif

#ifdef BSP_USING_EWDG3
    {
        .wdog_name = HPM_EWDG3,
        .device_name = "wdt3",
        .clock_name = clock_watchdog3,
        .irq_num = IRQn_EWDG3,
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
    EWDG_Type *base = hpm_wdog->wdog_base;

    ewdg_config_t config;

    printf("Init Watchdog\n");
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
            printf(" EWDG initialization failed, error_code=%d\n", status);
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

    return RT_EOK;
}

void hpm_wdog_isr(rt_watchdog_t *wdt)
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
    }
#endif
    return err;
}

INIT_BOARD_EXPORT(rt_hw_wdt_init);
#endif /* RT_USING_WDT */