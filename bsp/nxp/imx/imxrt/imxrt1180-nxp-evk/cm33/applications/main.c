/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2019-05-06     tyustli      first version
 *
 */

#include <rtthread.h>
#include <rtdevice.h>
#include <drv_gpio.h>
#include <fsl_rgpio.h>

#ifdef BSP_USING_CLOCK_TIMER1
static rt_err_t gpt1_timeout_cb(rt_device_t dev, rt_size_t size)
{
    rt_kprintf("gpt1 timeout, tick: %d\r\n", rt_tick_get());
    return RT_EOK;
}

static void gpt1_sample_init(void)
{
    rt_device_t dev;
    rt_clock_timer_mode_t mode;
    rt_clock_timerval_t tv;

    dev = rt_device_find("gpt1");
    if (dev == RT_NULL)
    {
        rt_kprintf("gpt1 device not found\r\n");
        return;
    }

    if (rt_device_open(dev, RT_DEVICE_OFLAG_RDWR) != RT_EOK)
    {
        rt_kprintf("gpt1 open failed\r\n");
        return;
    }

    if (rt_device_set_rx_indicate(dev, gpt1_timeout_cb) != RT_EOK)
    {
        rt_kprintf("gpt1 set rx indicate failed\r\n");
        rt_device_close(dev);
        return;
    }

    mode = CLOCK_TIMER_MODE_PERIOD;
    if (rt_device_control(dev, CLOCK_TIMER_CTRL_MODE_SET, &mode) != RT_EOK)
    {
        rt_kprintf("gpt1 mode set failed\r\n");
        rt_device_close(dev);
        return;
    }

    tv.sec = 1;
    tv.usec = 0;
    if (rt_device_write(dev, 0, &tv, sizeof(tv)) != sizeof(tv))
    {
        rt_kprintf("gpt1 write failed\r\n");
        rt_device_close(dev);
        return;
    }

    rt_kprintf("gpt1 periodic timer started (1s)\r\n");
}
#endif

int main(void)
{
    rt_kprintf("MIMXRT1180_CM33 Hello_World\r\n");

#ifdef BSP_USING_CLOCK_TIMER1
    gpt1_sample_init();
#endif

    while (1)
    {
        rt_thread_mdelay(500);
    }
}
