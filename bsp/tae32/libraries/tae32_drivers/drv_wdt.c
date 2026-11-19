/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2025-02-22     yeml           the first version
 */

#include "drv_wdt.h"

#ifdef RT_USING_WDT

#define DBG_TAG             "WDT"
#define DBG_LVL             DBG_ERROR
#include "dbg/tae_dbg.h"

static struct tae32_wdt tae32_wdt_obj;

static rt_err_t tae32_wdt_init(rt_watchdog_t *wdt)
{
    tae32_wdt_obj.Instance = IWDG;
    tae32_wdt_obj.is_start = RT_FALSE;

    tae32_wdt_obj.config.reload_val = 0x1FFF;
    tae32_wdt_obj.config.mode = IWDG_MODE_RESET;
    tae32_wdt_obj.config.pre_div = IWDG_PRE_DIV_256;

    if (LL_IWDG_Init(tae32_wdt_obj.Instance, &tae32_wdt_obj.config) == LL_OK)
    {
        return RT_EOK;
    }
    else
    {
        return RT_ERROR;
    }
}

static rt_err_t tae32_wdt_control(rt_watchdog_t *wdt, int cmd, void *arg)
{
    struct tae32_wdt *ptr_tae32_wdt;
    float f_temp = 0;
    ptr_tae32_wdt = rt_container_of(wdt, struct tae32_wdt, watchdog);
    switch (cmd)
    {
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
#if defined(LSI_VALUE)
        f_temp = (float)tae32_wdt_obj.config.reload_val * 256 / LSI_VALUE;
        /*Rounding*/
        if(f_temp + 0.5 > (rt_uint32_t)f_temp + 1)
        {
            (*((rt_uint32_t*)arg)) = (rt_uint32_t)f_temp + 1;
        }
        else
        {
             (*((rt_uint32_t*)arg)) = (rt_uint32_t)f_temp;
        }
        
#else
#error "Please define the value of LSI_VALUE!"
#endif
        break;

    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
#if defined(LSI_VALUE)
        tae32_wdt_obj.config.reload_val = (*((rt_uint32_t*)arg)) * LSI_VALUE / 256;
        if (tae32_wdt_obj.config.reload_val > 0x1FFF)
        {
            LOG_E("wdg set timeout parameter too large, please less than %ds", 0x1FFF * 256 / LSI_VALUE);
            return -RT_EINVAL;
        }
#else
#error "Please define the value of LSI_VALUE!"
#endif
        if (tae32_wdt_obj.is_start)
        {
            if (LL_IWDG_Init(tae32_wdt_obj.Instance, &tae32_wdt_obj.config) != LL_OK)
            {
                LOG_E("wdg set timeout failed.");
                return -RT_ERROR;
            }
        }
        break;

    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        LL_IWDG_Refresh(ptr_tae32_wdt->Instance);
        break;

    case RT_DEVICE_CTRL_WDT_START:
        if ((LL_IWDG_Init(tae32_wdt_obj.Instance, &tae32_wdt_obj.config) == LL_OK) && \
                (LL_IWDG_Start(ptr_tae32_wdt->Instance) == LL_OK))
        {
            tae32_wdt_obj.is_start = RT_TRUE;
        }
        else
        {
            LOG_E("wdg start failed.");
            return -RT_ERROR;
        }
        break;

    case RT_DEVICE_CTRL_WDT_STOP:
        LL_IWDG_Stop(ptr_tae32_wdt->Instance);
        tae32_wdt_obj.is_start = RT_FALSE;
        break;

    default:
        LOG_W("This command is not supported.");
        return -RT_ERROR;
    }

    return RT_EOK;
}

static const struct rt_watchdog_ops tae32_wdt_ops =
{
    .init = tae32_wdt_init,
    .control = tae32_wdt_control
};

int rt_hw_wdt_init(void)
{
    rt_err_t result = 0;

    tae32_wdt_obj.watchdog.ops = &tae32_wdt_ops;
    result = rt_hw_watchdog_register(&tae32_wdt_obj.watchdog,
                                     "wdt", RT_DEVICE_FLAG_DEACTIVATE,
                                     RT_NULL);

    RT_ASSERT(result == RT_EOK);
    return result;
}
INIT_BOARD_EXPORT(rt_hw_wdt_init);

#endif /* RT_USING_WDT */
