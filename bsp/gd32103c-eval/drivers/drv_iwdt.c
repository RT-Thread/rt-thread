/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2021-03-03     iysheng           first version
 */

#include <board.h>

#define DBG_TAG             "drv.wdt"
#define DBG_LVL             DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_WDT

typedef struct {
    struct rt_watchdog_device wdt;
    rt_uint32_t min_threshold_s;
    rt_uint32_t max_threshold_s;
    rt_uint32_t current_threshold_s;
} gd32_wdt_device_t;

static gd32_wdt_device_t g_wdt_dev;

static rt_err_t gd32_iwdt_init(rt_watchdog_t *wdt)
{
    rcu_osci_on(RCU_IRC40K);
    if (ERROR == rcu_osci_stab_wait(RCU_IRC40K))
    {
        LOG_E("failed init IRC40K clock for free watchdog.");
        return -EINVAL;
    }

    g_wdt_dev.min_threshold_s = 1;
    g_wdt_dev.max_threshold_s = (0xfff << 8) / 40000;
    LOG_I("threshold section [%u, %d]", \
        g_wdt_dev.min_threshold_s, g_wdt_dev.max_threshold_s);

    IWDG_Write_Enable(IWDG_WRITEACCESS_ENABLE);
    IWDG_SetPrescaler(IWDG_PRESCALER_256);
    IWDG_SetReloadValue(0xfff);
    IWDG_Write_Enable(IWDG_WRITEACCESS_DISABLE);

    return 0;
}

static rt_err_t gd32_iwdt_control(rt_watchdog_t *wdt, int cmd, void *arg)
{
    rt_uint32_t param;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        IWDG_ReloadCounter();
        break;
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        param = *(rt_uint32_t *) arg;
        if ((param > g_wdt_dev.max_threshold_s) || \
            (param < g_wdt_dev.min_threshold_s))
        {
            LOG_E("invalid param@%u.", param);
            return -E2BIG;
        }
        else
        {
            g_wdt_dev.current_threshold_s = param;
        }
        IWDG_Write_Enable(IWDG_WRITEACCESS_ENABLE);
        IWDG_SetReloadValue(param * 40000 >> 8);
        IWDG_Write_Enable(IWDG_WRITEACCESS_DISABLE);
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        *(rt_uint32_t *)arg = g_wdt_dev.current_threshold_s;
        break;
    case RT_DEVICE_CTRL_WDT_START:
        IWDG_Enable();
        break;
    default:
        LOG_W("This command is not supported.");
        return -RT_ERROR;
    }

    return RT_EOK;
}

static struct rt_watchdog_ops g_wdt_ops = {
    gd32_iwdt_init,
    gd32_iwdt_control,
};

static int rt_hw_iwdt_init(void)
{
    rt_err_t ret;

    g_wdt_dev.wdt.ops = &g_wdt_ops;
    /* register watchdog device */
    if (rt_hw_watchdog_register(&g_wdt_dev.wdt, "iwdt", \
        RT_DEVICE_FLAG_DEACTIVATE, RT_NULL) != RT_EOK)
    {
        LOG_E("wdt device register failed.");
        return -RT_ERROR;
    }
    LOG_D("wdt device register success.");

    return ret;
}
INIT_BOARD_EXPORT(rt_hw_iwdt_init);
#endif
