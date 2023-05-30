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

/* thread phase init */
void rt_init_thread_entry(void *parameter)
{
#ifdef RT_USING_FINSH
    /* initialize finsh */
    finsh_system_init();
    finsh_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
}
/*the led thread*/
ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t led_stack[ 512 ];
static struct rt_thread led_thread;
static void led_thread_entry(void *parameter)
{
    rt_uint8_t led_value = 0;
    rt_device_t led_dev;
    rt_led_hw_init();
    led_dev = rt_device_find("led");
    if (led_dev == RT_NULL)
    {
        rt_kprintf("can not find the led device!\n");
        return;
    }
    while (1)
    {
        /* led0 on */
        led_value = 1;
        led_dev->write(led_dev, 0, &led_value, 1);
        rt_thread_delay(RT_TICK_PER_SECOND / 2); /* sleep 0.5 second and switch to other thread */

        /* led0 off */
        led_value = 0;
        led_dev->write(led_dev, 0, &led_value, 1);
        rt_thread_delay(RT_TICK_PER_SECOND / 2);
    }
}

int rt_application_init(void)
{
    rt_thread_t tid;
    rt_err_t result;
    tid = rt_thread_create("init",
                           rt_init_thread_entry, RT_NULL,
                           2048, RT_THREAD_PRIORITY_MAX / 3, 20);
    if (tid != RT_NULL) rt_thread_startup(tid);
    /* init led thread */
    result = rt_thread_init(&led_thread,
                            "led",
                            led_thread_entry,
                            RT_NULL,
                            (rt_uint8_t *)&led_stack[0],
                            sizeof(led_stack),
                            20,
                            5);
    if (result == RT_EOK)
    {
        rt_thread_startup(&led_thread);
    }
    return 0;
}
