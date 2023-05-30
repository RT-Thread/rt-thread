/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 * 2010-04-09     fify         modified for M16C
 *
 * For       : Renesas M16C
 * Toolchain : IAR's EW for M16C v3.401
 */

#include <rtthread.h>
#include "bsp.h"

static struct rt_thread led;

ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t led_stack[256];

static void rt_thread_entry_led(void *parameter)
{
    while (1)
    {
        led_off();
        rt_thread_delay(100);
        led_on();
        rt_thread_delay(100);
    }
}

int rt_application_init(void)
{
    rt_err_t result;

    /* create led thread */
    result = rt_thread_init(&led,
                            "led",
                            rt_thread_entry_led,
                            RT_NULL,
                            &led_stack[0],
                            sizeof(led_stack),
                            RT_THREAD_PRIORITY_MAX / 2,
                            32);

    if (result == RT_EOK)
        rt_thread_startup(&led);

    return 0;
}
