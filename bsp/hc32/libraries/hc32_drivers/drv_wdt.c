/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 * Copyright (c) 2022, xiaoxiaolisunny
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author               Notes
 * 2022-07-11     xiaoxiaolisunny      first version
 */

#include <drv_config.h>
#include <board_config.h>
#include "drv_irq.h"

#ifdef RT_USING_WDT

#define LOG_TAG             "drv.dwt"
#include <drv_log.h>

struct hc32_wdt_obj
{
    rt_watchdog_t watchdog;
    stc_wdt_init_t hiwdg;
    rt_uint16_t is_start;
};

static struct hc32_wdt_obj hc32_wdt;
static struct rt_watchdog_ops ops;

static rt_err_t wdt_init(rt_watchdog_t *wdt)
{
    return RT_EOK;
}

/* timeout(s) = PERI * CKS / PCLK3
   16384 * 8192 / 50M = 2.68s
*/
static rt_err_t wdt_control(rt_watchdog_t *wdt, int cmd, void *arg)
{
    switch (cmd)
    {
    /* feed the watchdog */
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        WDT_FeedDog();
        break;
    /* set watchdog timeout */
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        hc32_wdt.hiwdg.u32CountPeriod = WDT_CNT_PERIOD16384;
        if(hc32_wdt.hiwdg.u32RefreshRange > 0xFFFF)
        {
            LOG_E("wdg set timeout parameter too large, please less than %ds", 0xFFFF);
            return -RT_EINVAL;
        }
        if(hc32_wdt.is_start)
        {
            if (WDT_Init(&hc32_wdt.hiwdg) != LL_OK)
            {
                LOG_E("wdg set timeout failed.");
                return -RT_ERROR;
            }
        }
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        (*((rt_uint32_t*)arg)) = 16384 * 8192 / 50000000;
        break;
    case RT_DEVICE_CTRL_WDT_START:
        if (WDT_Init(&hc32_wdt.hiwdg) != LL_OK)
        {
            LOG_E("wdt start failed.");
            return -RT_ERROR;
        }
        hc32_wdt.is_start = 1;
        break;
    default:
        LOG_W("This command is not supported.");
        return -RT_ERROR;
    }
    return RT_EOK;
}

int rt_wdt_init(void)
{
    hc32_wdt.hiwdg.u32ClockDiv =  WDT_CLK_DIV8192;
    hc32_wdt.hiwdg.u32CountPeriod = WDT_CNT_PERIOD16384;
    hc32_wdt.hiwdg.u32RefreshRange  = WDT_RANGE_0TO100PCT;
    hc32_wdt.hiwdg.u32LPMCount      = WDT_LPM_CNT_STOP;
    hc32_wdt.hiwdg.u32ExceptionType = WDT_EXP_TYPE_RST;
    hc32_wdt.is_start = 0;

    ops.init = &wdt_init;
    ops.control = &wdt_control;
    hc32_wdt.watchdog.ops = &ops;

    /* register watchdog device */
    if (rt_hw_watchdog_register(&hc32_wdt.watchdog, "wdt", RT_DEVICE_FLAG_DEACTIVATE, RT_NULL) != RT_EOK)
    {
        LOG_E("wdt device register failed.");
        return -RT_ERROR;
    }
    LOG_D("wdt device register success.");
    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_wdt_init);

#endif

