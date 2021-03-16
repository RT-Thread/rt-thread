/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2014-07-13     xiaonong     port for lpc43xx
 */

#include <rtthread.h>
#include <board.h>
#include <rtdevice.h>
#include "drv_led.h"

#ifdef RT_USING_FINSH
#include <finsh.h>
#include <shell.h>
#endif

#ifdef RT_USING_VBUS
#include <vbus.h>
#endif

/* thread phase init */
void rt_init_thread_entry(void *parameter)
{
#ifdef RT_USING_FINSH
    /* initialize finsh */
    finsh_system_init();
    finsh_set_device(RT_CONSOLE_DEVICE_NAME);
#endif

#ifdef RT_USING_VBUS
    rt_vbus_do_init();
#endif
}

/*the led thread*/
ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t led_stack[1024];
static struct rt_thread led_thread;
static void led_thread_entry(void *parameter)
{
    rt_device_t led_dev;
    rt_device_t vbus_dev;
    rt_err_t err;

    rt_led_hw_init();

    led_dev = rt_device_find("led");
    if (led_dev == RT_NULL)
    {
        rt_kprintf("can not find the led device\n");
        return;
    }

    vbus_dev = rt_device_find("vecho");
    if (vbus_dev == RT_NULL)
    {
        rt_kprintf("can not find the vbus device\n");
        return;
    }

    err = rt_device_open(vbus_dev, RT_DEVICE_OFLAG_RDWR);
    if (err != RT_EOK)
    {
        rt_kprintf("open vbus failed: %d\n", err);
        return;
    }

    while (1)
    {
        rt_uint8_t led_value;
        int len;

        len = rt_device_read(vbus_dev, 0, &led_value, sizeof(led_value));
        if (len <= 0)
        {
            rt_kprintf("vbus read err: %d, %d\n", len, rt_get_errno());
        }

        led_dev->write(led_dev, 1, &led_value, sizeof(led_value));
    }
}

int rt_application_init(void)
{
    rt_thread_t tid;
    rt_err_t result;
    tid = rt_thread_create("init",
                           rt_init_thread_entry, RT_NULL,
                           2048, 3, 20);
    if (tid != RT_NULL)
        rt_thread_startup(tid);

    /* init led thread */
    result = rt_thread_init(&led_thread, "led",
                            led_thread_entry, RT_NULL,
                            (rt_uint8_t *)&led_stack[0], sizeof(led_stack),
                            20, 5);
    if (result == RT_EOK)
    {
        rt_thread_startup(&led_thread);
    }
    return 0;
}

