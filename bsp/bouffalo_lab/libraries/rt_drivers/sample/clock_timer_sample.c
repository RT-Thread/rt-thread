/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2023-04-01     wcx1024979076  first version.
 */
/*
 * 程序清单：这是一个 clock_timer 设备使用例程
 * 例程导出了 clock_timer_sample 命令到控制终端
 * 命令调用格式：clock_timer_sample
 * 程序功能：硬件定时器超时回调函数周期性的打印当前tick值，2次tick值之差换算为时间等同于定时时间值。
*/

#include <rtthread.h>
#include <rtdevice.h>

#ifdef BSP_USING_CLOCK_TIMER

#define CLOCK_TIMER_DEV_NAME   "timer0"     /* 定时器名称 */

/* 定时器超时回调函数 */
static rt_err_t timeout_cb(rt_device_t dev, rt_size_t size)
{
    rt_kprintf("this is clock_timer timeout callback fucntion!\n");
    rt_kprintf("tick is :%d !\n", rt_tick_get());

    return 0;
}

static int clock_timer_sample(int argc, char *argv[])
{
    rt_err_t ret = RT_EOK;
    rt_clock_timerval_t timeout_s;      /* 定时器超时值 */
    rt_device_t hw_dev = RT_NULL;   /* 定时器设备句柄 */
    rt_clock_timer_mode_t mode;         /* 定时器模式 */
    rt_uint32_t freq = 10000;               /* 计数频率 */

    /* 查找定时器设备 */
    hw_dev = rt_device_find(CLOCK_TIMER_DEV_NAME);
    if (hw_dev == RT_NULL)
    {
        rt_kprintf("clock_timer sample run failed! can't find %s device!\n", CLOCK_TIMER_DEV_NAME);
        return -RT_ERROR;
    }

    /* 以读写方式打开设备 */
    ret = rt_device_open(hw_dev, RT_DEVICE_OFLAG_RDWR);
    if (ret != RT_EOK)
    {
        rt_kprintf("open %s device failed!\n", CLOCK_TIMER_DEV_NAME);
        return ret;
    }

    /* 设置超时回调函数 */
    rt_device_set_rx_indicate(hw_dev, timeout_cb);

    /* 设置计数频率(若未设置该项，默认为1Mhz 或 支持的最小计数频率) */
    rt_device_control(hw_dev, CLOCK_TIMER_CTRL_FREQ_SET, &freq);
    /* 设置模式为周期性定时器（若未设置，默认是CLOCK_TIMER_MODE_ONESHOT）*/
    mode = CLOCK_TIMER_MODE_PERIOD;
    ret = rt_device_control(hw_dev, CLOCK_TIMER_CTRL_MODE_SET, &mode);
    if (ret != RT_EOK)
    {
        rt_kprintf("set mode failed! ret is :%d\n", ret);
        return ret;
    }

    /* 设置定时器超时值为2s并启动定时器 */
    timeout_s.sec = 2;      /* 秒 */
    timeout_s.usec = 0;     /* 微秒 */
    if (rt_device_write(hw_dev, 0, &timeout_s, sizeof(timeout_s)) != sizeof(timeout_s))
    {
        rt_kprintf("set timeout value failed\n");
        return -RT_ERROR;
    }

    /* 延时1500ms */
    rt_thread_mdelay(1500);

    /* 读取定时器当前值 */
    rt_device_read(hw_dev, 0, &timeout_s, sizeof(timeout_s));
    rt_kprintf("Read: Sec = %d, Usec = %d\n", timeout_s.sec, timeout_s.usec);

    return ret;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(clock_timer_sample, clock_timer sample);

#endif /* RT_USING_CLOCK_TIME */
