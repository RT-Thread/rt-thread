/*
 * Copyright (c) 2006-2023
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2022-07-02     zengjianwei       first version
 */

#include <board.h>
#include <rtdbg.h>
#include <rtdevice.h>
#include <rtthread.h>

#ifdef RT_USING_WDT

#define LSI_VALUE 40000U

struct gd32_wdt_obj
{
    uint16_t reload_value;
    uint8_t prescaler_div;
    rt_uint16_t is_start;
};

static struct gd32_wdt_obj gd32_wdt;
static struct rt_watchdog_ops ops;
static rt_watchdog_t watchdog;

static rt_err_t wdt_init(rt_watchdog_t *wdt)
{
    return RT_EOK;
}

static rt_err_t wdt_control(rt_watchdog_t *wdt, int cmd, void *arg)
{
    switch (cmd)
    {
        /* feed the watchdog */
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        fwdgt_counter_reload();
        break;
        /* set watchdog timeout */
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
#if defined(LSI_VALUE)
        if (LSI_VALUE)
        {
            gd32_wdt.reload_value = (*((rt_uint32_t *)arg)) * LSI_VALUE / 256;
        }
        else
        {
            LOG_E("Please define the value of LSI_VALUE!");
        }

        if (gd32_wdt.reload_value > 0xFFF)
        {
            LOG_E("wdg set timeout parameter too large, please less than %ds", 0xFFF * 256 / LSI_VALUE);
            return -RT_EINVAL;
        }
#else
#error "Please define the value of LSI_VALUE!"
#endif
        if (gd32_wdt.is_start)
        {
            if (fwdgt_config(gd32_wdt.reload_value, gd32_wdt.prescaler_div) != SUCCESS)
            {
                LOG_E("wdg set timeout failed.");
                return -RT_ERROR;
            }
        }
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
#if defined(LSI_VALUE)
        if (LSI_VALUE)
        {
            (*((rt_uint32_t *)arg)) = gd32_wdt.reload_value * 256 / LSI_VALUE;
        }
        else
        {
            LOG_E("Please define the value of LSI_VALUE!");
        }
#else
#error "Please define the value of LSI_VALUE!"
#endif
        break;
    case RT_DEVICE_CTRL_WDT_START:
        if (fwdgt_config(gd32_wdt.reload_value, gd32_wdt.prescaler_div) != SUCCESS)
        {
            LOG_E("wdt start failed.");
            return -RT_ERROR;
        }
        fwdgt_enable();
        gd32_wdt.is_start = 1;
        break;
    default:
        LOG_W("This command is not supported.");
        return -RT_ERROR;
    }
    return RT_EOK;
}

int rt_wdt_init(void)
{
    gd32_wdt.prescaler_div = FWDGT_PSC_DIV256;
    gd32_wdt.reload_value = 0x00000FFF;
    gd32_wdt.is_start = 0;

    ops.init = &wdt_init;
    ops.control = &wdt_control;
    watchdog.ops = &ops;
    /* register watchdog device */
    if (rt_hw_watchdog_register(&watchdog, "wdt", RT_DEVICE_FLAG_DEACTIVATE, RT_NULL) != RT_EOK)
    {
        LOG_E("wdt device register failed.");
        return -RT_ERROR;
    }
    LOG_D("wdt device register success.");
    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_wdt_init);

#endif /* RT_USING_WDT */
