/*
 * Copyright (c) 2022-2024, Xiaohua Semiconductor Co., Ltd.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-12-30     CDT          first version
 */

/*
 * 程序清单：这是 WDT 设备使用例程
 * 例程导出了 wdt_sample 命令到控制终端。
 * 命令调用格式：wdt_sample set_timeout x
 * 命令解释：x 对应的是超时时间，以实际计算的接近值为准
 * 终端先打印N次设置的超时，然后依次递减等待N秒后复位系统(N等于设置的超时秒数)
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <stdlib.h>

#ifdef BSP_USING_WDT_TMR

#if defined(BSP_USING_WDT)
    #define WDT_DEVICE_NAME     "wdt"
#elif defined(BSP_USING_SWDT)
    #define WDT_DEVICE_NAME     "swdt"
#endif

static rt_device_t wdg_dev;
static rt_uint32_t valid_timeout = 0;
static rt_uint32_t wdt_cnt = 0;

static void idle_hook(void)
{
    if (wdt_cnt < valid_timeout)
    {
        /* Feed watch dog */
        rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_KEEPALIVE, NULL);
    }
}

static void _wdt_cmd_print_usage(void)
{
    rt_kprintf("wdt_sample [option]\n");
    rt_kprintf("  set_timeout: set wdt timeout(S)\n");
    rt_kprintf("    e.g. MSH >wdt_sample set_timeout 10\n");
}

static int wdt_sample(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    rt_uint32_t timeleft;
    rt_uint32_t timeout = atoi(argv[2]);

    if (argc != 3)
    {
        _wdt_cmd_print_usage();
        return -RT_ERROR;
    }

    if (!rt_strcmp("set_timeout", argv[1]))
    {
        wdg_dev = rt_device_find(WDT_DEVICE_NAME);
        if (!wdg_dev)
        {
            rt_kprintf("find %s failed!\n", WDT_DEVICE_NAME);
            return -RT_ERROR;
        }

        ret = rt_device_init(wdg_dev);
        if (ret != RT_EOK)
        {
            rt_kprintf("init %s failed!\n", WDT_DEVICE_NAME);
            return -RT_ERROR;
        }

        /* Set timeout (Unit:S) */
        ret = rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_SET_TIMEOUT, &timeout);
        if (ret != RT_EOK)
        {
            rt_kprintf("set %s timeout failed!\n", WDT_DEVICE_NAME);
            return -RT_ERROR;
        }

        /* Get the time when it real effective */
        ret = rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_GET_TIMEOUT, &valid_timeout);
        if (ret != RT_EOK)
        {
            rt_kprintf("start %s failed!\n", WDT_DEVICE_NAME);
            return -RT_ERROR;
        }
        rt_kprintf("valid_timeout = %d S\n", valid_timeout);

        /* Start WDT */
        ret = rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_START, RT_NULL);
        if (ret != RT_EOK)
        {
            rt_kprintf("start %s failed!\n", WDT_DEVICE_NAME);
            return -RT_ERROR;
        }

        rt_thread_idle_sethook(idle_hook);

        for (;;)
        {
            rt_thread_mdelay(1000);
            rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_GET_TIMELEFT, &timeleft);
            rt_kprintf("timeleft = %d S\n", timeleft);
            wdt_cnt++;
        }
    }
    else
    {
        _wdt_cmd_print_usage();
        return -RT_ERROR;
    }

    return ret;
}

MSH_CMD_EXPORT(wdt_sample, wdt_sample [option]);

#endif
