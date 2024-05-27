/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2024/03/02     ShichengChu    first version
 */
#include <rtthread.h>
#include <rtdevice.h>
#include "drv_wdt.h"

#define DBG_LEVEL   DBG_LOG
#include <rtdbg.h>
#define LOG_TAG "DRV.WDT"

#define WDT_FREQ_DEFAULT 25000000UL
#define CVI_WDT_MAX_TOP     15

struct _cvi_wdt_dev
{
    struct rt_watchdog_device device;
    const char *name;
    rt_uint32_t base;
};

static struct _cvi_wdt_dev _wdt_dev[] =
{
#ifdef BSP_USING_WDT0
    {
        .name = "wdt0",
        .base = CVI_WDT0_BASE
    },
#endif /* BSP_USING_WDT0 */
#ifdef BSP_USING_WDT1
    {
        .name = "wdt1",
        .base = CVI_WDT1_BASE
    },
#endif /* BSP_USING_WDT1 */
#ifdef BSP_USING_WDT2
    {
        .name = "wdt2",
        .base = CVI_WDT2_BASE
    },
#endif /* BSP_USING_WDT2 */
};
struct rt_watchdog_device wdt_device;

static rt_err_t _wdt_init(rt_watchdog_t *wdt_device)
{
    cvi_wdt_top_setting();

    return RT_EOK;
}

rt_inline int wdt_top_in_ms(unsigned int top)
{
    /*
     * There are 16 possible timeout values in 0..15 where the number of
     * cycles is 2 ^ (16 + i) and the watchdog counts down.
     */
    // pr_debug("wdt top in seconds: %d/%d=%d\n", (1U << (16 + top)), chip->clk_hz, (1U << (16 + top)) / chip->clk_hz);
    return (1U << (16 + top)) / (WDT_FREQ_DEFAULT / 1000);
}

static rt_err_t csi_wdt_set_timeout(unsigned long reg_base, uint32_t ms)
{
    rt_err_t ret = RT_EOK;
    int i, top_val = CVI_WDT_MAX_TOP;

    /*
     * Iterate over the timeout values until we find the closest match. We
     * always look for >=.
     */
    for (i = 0; i <= CVI_WDT_MAX_TOP; ++i)
        if (wdt_top_in_ms(i) >= ms) {
            top_val = i;
            break;
        }

    if (i < CVI_WDT_MAX_TOP)
    {
        /*
        * Set the new value in the watchdog.  Some versions of wdt_chip
        * have TOPINIT in the TIMEOUT_RANGE register (as per
        * CP_WDT_DUAL_TOP in WDT_COMP_PARAMS_1).  On those we
        * effectively get a pat of the watchdog right here.
        */
        cvi_wdt_set_timeout(reg_base, top_val);
        cvi_wdt_start_en(reg_base);
    }
    else
    {
        ret = -RT_ERROR;
    }

    return ret;
}


static rt_err_t _wdt_control(rt_watchdog_t *wdt_device, int cmd, void *arg)
{
    RT_ASSERT(wdt_device != RT_NULL);

    struct _cvi_wdt_dev *wdt = rt_container_of(wdt_device, struct _cvi_wdt_dev, device);
    rt_uint32_t reg_base = wdt->base;

    switch (cmd)
    {
    case RT_DEVICE_CTRL_WDT_KEEPALIVE:
        cvi_wdt_feed_en(reg_base);
        break;
    case RT_DEVICE_CTRL_WDT_SET_TIMEOUT:
        csi_wdt_set_timeout(reg_base, *(rt_uint32_t *)arg);
        wdt_device->parent.user_data = (rt_uint32_t)(*(rt_uint32_t *)arg);
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMEOUT:
        *(rt_uint32_t *)arg = (rt_uint32_t)wdt_device->parent.user_data;
        break;
    case RT_DEVICE_CTRL_WDT_GET_TIMELEFT:
        *(rt_uint32_t *)arg = (cvi_wdt_get_counter_value(reg_base) / (WDT_FREQ_DEFAULT / 1000U));
        break;
    case RT_DEVICE_CTRL_WDT_START:
        cvi_wdt_set_respond_system_reset(reg_base);
        cvi_wdt_start_en(reg_base);
        break;
    case RT_DEVICE_CTRL_WDT_STOP:
        cvi_wdt_start_dis(reg_base);
        break;
    default:
        LOG_W("This command is not supported.");
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static const struct rt_watchdog_ops _wdt_ops =
{
    .init = _wdt_init,
    .control = _wdt_control
};

int rt_hw_wdt_init(void)
{
    rt_uint8_t i;
    for (i = 0; i < sizeof(_wdt_dev) / sizeof(_wdt_dev[0]); i ++)
    {
        _wdt_dev[i].device.ops = &_wdt_ops;
        if (rt_hw_watchdog_register(&_wdt_dev[i].device, _wdt_dev[i].name, RT_DEVICE_FLAG_RDWR, RT_NULL) != RT_EOK)
        {
            LOG_E("%s register failed!", _wdt_dev[i].name);
            return -RT_ERROR;
        }
    }

    return RT_EOK;
}
INIT_BOARD_EXPORT(rt_hw_wdt_init);
