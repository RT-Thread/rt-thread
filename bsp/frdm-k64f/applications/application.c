/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 *
 */

/**
 * @addtogroup k64
 */
/*@{*/

#include <stdint.h>
#include <stdio.h>

#include "MK64F12.h"
#include <board.h>
#include <rtthread.h>

#include "led.h"

void rt_init_thread_entry(void* parameter)
{
#ifdef RT_USING_COMPONENTS_INIT
    /* initialization RT-Thread Components */
    rt_components_init();
#endif
}

float f_var1;
float f_var2;
float f_var3;
float f_var4;

rt_align(RT_ALIGN_SIZE)
static char thread_led1_stack[1024];
struct rt_thread thread_led1;
static void rt_thread_entry_led1(void* parameter)
{
    int n = 0;
    rt_hw_led_init();

    while (1)
    {
        //rt_kprintf("LED\t%d\tis shining\r\n",n);

        rt_hw_led_on(n);
        rt_thread_delay(RT_TICK_PER_SECOND/2);
        rt_hw_led_off(n);
        rt_thread_delay(RT_TICK_PER_SECOND/2);

        n++;

        if (n == LED_MAX)
            n = 0;
    }
}

int rt_application_init()
{
    rt_thread_t init_thread;

    init_thread = rt_thread_create("init",
                                   rt_init_thread_entry, RT_NULL,
                                   2048, RT_THREAD_PRIORITY_MAX/3, 20);

    if (init_thread != RT_NULL)
        rt_thread_startup(init_thread);

    //------- init led1 thread
    rt_thread_init(&thread_led1,
                   "led_demo",
                   rt_thread_entry_led1,
                   RT_NULL,
                   &thread_led1_stack[0],
                   sizeof(thread_led1_stack),11,5);
    rt_thread_startup(&thread_led1);

    return 0;
}

/*@}*/
