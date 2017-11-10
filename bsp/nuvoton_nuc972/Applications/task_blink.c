/*
 * File      : task_blink.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author		Notes
 * 2017/11/08     Urey			first version
 */
#include <rtthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "nuc97x.h"
#include "nuc97x_gpio.h"

extern int rt_hw_led_init(void);
extern void rt_hw_led_set(rt_uint8_t value);

void task_blink_entry(void *parameter)
{
    rt_uint8_t bcount = 0;
    // rt_uint8_t  bValue;
    rt_hw_led_init();

    while (1)
    {
        rt_hw_led_set(bcount++);
        rt_thread_delay(100);
    }
}

int task_blink_init(void)
{
    rt_thread_t tid;

    tid = rt_thread_create("blink",
                           task_blink_entry, RT_NULL,
                           512,
                           RT_THREAD_PRIORITY_MAX - 1,
                           20);

    if (tid != RT_NULL)
        rt_thread_startup(tid);

    return 0;
}
INIT_ENV_EXPORT(task_blink_init);
