/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2023-3-27     wcx1024979076  first version.
 */
/*
 * 程序清单：这是一个独立看门狗设备使用例程
 * 例程导出了 wdt_sample 命令到控制终端
 * 命令调用格式：wdt_sample wdt
 * 命令解释：命令第二个参数是要使用的看门狗设备名称，为空则使用例程默认的看门狗设备。
 * 程序功能：程序通过设备名称查找看门狗设备，然后初始化设备并设置看门狗设备溢出时间。
 *           然后设置空闲线程回调函数，在回调函数里会喂狗。
*/

#include <rtthread.h>
#include <rtdevice.h>

#ifdef RT_USING_WDT

#define WDT_DEVICE_NAME    "wdt"    /* 看门狗设备名称 */

static rt_device_t wdg_dev;         /* 看门狗设备句柄 */

static void idle_hook(void)
{
    /* 在空闲线程的回调函数里喂狗 */
    rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_KEEPALIVE, NULL);
    rt_kprintf("feed the dog!\n ");
}

static int wdt_sample(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    rt_uint32_t timeout = 1;        /* 溢出时间，单位：秒 */
    char device_name[RT_NAME_MAX];

    /* 判断命令行参数是否给定了设备名称 */
    if (argc == 2)
    {
        rt_strncpy(device_name, argv[1], RT_NAME_MAX);
    }
    else
    {
        rt_strncpy(device_name, WDT_DEVICE_NAME, RT_NAME_MAX);
    }
    /* 根据设备名称查找看门狗设备，获取设备句柄 */
    wdg_dev = rt_device_find(device_name);
    if (!wdg_dev)
    {
        rt_kprintf("find %s failed!\n", device_name);
        return -RT_ERROR;
    }
    /* 初始化设备 */
    rt_device_init(wdg_dev);

    /* 设置看门狗溢出时间 */
    ret = rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_SET_TIMEOUT, &timeout);
    if (ret != RT_EOK)
    {
        rt_kprintf("set %s timeout failed!\n", device_name);
        return -RT_ERROR;
    }

    /* 启动看门狗 */
    ret = rt_device_control(wdg_dev, RT_DEVICE_CTRL_WDT_START, RT_NULL);
    if (ret != RT_EOK)
    {
        rt_kprintf("start %s failed!\n", device_name);
        return -RT_ERROR;
    }
    /* 设置空闲线程回调函数 */
    rt_thread_idle_sethook(idle_hook);
    return ret;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(wdt_sample, wdt sample);

#endif  /* RT_USING_WDT */
