/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-08-20     Mr.Tiger     first version
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <rthw.h>
#include <drv_common.h>
#include <drv_config.h>
#include <hal_data.h>

#ifdef RT_USING_WDT

//#define DRV_DEBUG
#define LOG_TAG             "drv.wdt"
#include <rtdbg.h>

static struct rt_watchdog_device ra_wdt_dev;
static struct rt_watchdog_ops ops;

static rt_err_t wdt_init(rt_watchdog_t *wdt)
{
    return RT_EOK;
}

static rt_err_t wdt_control(rt_watchdog_t *wdt, int cmd, void *arg)
{
    rt_err_t ret = -RT_ERROR;
    struct st_wdt_timeout_values *wdt_value = {0};
    switch (cmd)
    {
    /* feed the watchdog */
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        if (R_WDT_Refresh(&g_wdt_ctrl) != FSP_SUCCESS)
        {
            LOG_E("watch dog keepalive fail.");
            ret =  -RT_ERROR;
        }
        else
        {
            ret = RT_EOK;
        }
        break;
    /* set watchdog timeout */
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        /**< set*/
        LOG_W("Use the FSP tool to modify the configuration parameters!");
        ret = -RT_EINVAL;
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        wdt_value = (struct st_wdt_timeout_values *)arg;
        if (R_WDT_TimeoutGet(&g_wdt_ctrl, wdt_value) != FSP_SUCCESS)
        {
            LOG_E("wdt get timeout failed.");
            ret =  -RT_ERROR;
        }
        else
        {
            ret = RT_EOK;
        }
        break;
    case RT_DEVICE_CTRL_WDT_START:
        if (R_WDT_Open(&g_wdt_ctrl, &g_wdt_cfg) == FSP_SUCCESS)
        {
            if (R_WDT_Refresh(&g_wdt_ctrl) != FSP_SUCCESS)
            {
                LOG_E("wdt start failed.");
                ret =  -RT_ERROR;
            }
            else
            {
                ret = RT_EOK;
            }
        }
        else
        {
            LOG_E("wdt start failed.");
            ret =  -RT_ERROR;
        }
        break;
    default:
        LOG_W("This command is not supported.");
        ret =  -RT_ERROR;
    }
    return ret;
}

int rt_wdt_init(void)
{
    ops.init = &wdt_init;
    ops.control = &wdt_control;
    ra_wdt_dev.ops = &ops;
    /* register watchdog device */
    if (rt_hw_watchdog_register(&ra_wdt_dev, "wdt", RT_DEVICE_FLAG_DEACTIVATE, RT_NULL) != RT_EOK)
    {
        LOG_E("wdt device register failed.");
        return -RT_ERROR;
    }
    LOG_D("wdt device register success.");
    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_wdt_init);

#endif /* RT_USING_WDT */
