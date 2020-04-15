/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2020-01-22     shelton           first version
 */

#include <board.h>
#include <drivers/watchdog.h>

#ifdef RT_USING_WDT

#define LSI_VALUE 40000

//#define DRV_DEBUG
#define LOG_TAG             "drv.wdt"
#include <drv_log.h>

struct at32_wdt_obj
{
    IWDG_Type *instance;
    rt_uint32_t Prescaler;
    rt_uint32_t Reload;
    rt_uint16_t is_start;
};
static struct at32_wdt_obj at32_wdt;
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
        IWDG_ReloadCounter();
        break;
        /* set watchdog timeout */
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
#if defined(LSI_VALUE)
        if(LSI_VALUE)
        {
            at32_wdt.Reload = (*((rt_uint32_t*)arg)) * LSI_VALUE / 256 ;
        }
        else
        {
            LOG_E("Please define the value of LSI_VALUE!");
        }
        if(at32_wdt.Reload > 0xFFF)
        {
            LOG_E("wdg set timeout parameter too large, please less than %ds",0xFFF * 256 / LSI_VALUE);
            return -RT_EINVAL;
        }
#else
  #error "Please define the value of LSI_VALUE!"
#endif
        if(at32_wdt.is_start)
        {
            IWDG_KeyRegWrite(IWDG_KeyRegWrite_Enable);
            IWDG_SetPrescaler(at32_wdt.Prescaler);
            IWDG_SetReload(at32_wdt.Reload);
            IWDG_KeyRegWrite(IWDG_KeyRegWrite_Disable);
            IWDG_Enable();
        }
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
#if defined(LSI_VALUE)
        if(LSI_VALUE)
        {
            (*((rt_uint32_t*)arg)) = at32_wdt.Reload * 256 / LSI_VALUE;
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
        IWDG_KeyRegWrite(IWDG_KeyRegWrite_Enable);
        IWDG_SetPrescaler(at32_wdt.Prescaler);
        IWDG_SetReload(at32_wdt.Reload);
        IWDG_KeyRegWrite(IWDG_KeyRegWrite_Disable);
        IWDG_Enable();
        at32_wdt.is_start = 1;
        break;
    default:
        LOG_W("This command is not supported.");
        return -RT_ERROR;
    }
    return RT_EOK;
}

int rt_hw_wdt_init(void)
{
    at32_wdt.instance = IWDG;
    at32_wdt.Prescaler = IWDG_Psc_256;
    at32_wdt.Reload = 0x00000FFF;
    at32_wdt.is_start = 0;

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
INIT_BOARD_EXPORT(rt_hw_wdt_init);

#endif /* RT_USING_WDT */
