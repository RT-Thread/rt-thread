/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-01-05     Bernard      the first version
 */

/**
 * @addtogroup STM32
 */
/*@{*/

#include <rtthread.h>
#include "led.h"

static void rt_thread_entry_led1(void* parameter)
{
    /* init led configuration */
    rt_hw_led_init();

    while (1)
    {
        /* led on */
        rt_kprintf("led1 on\r\n");
        rt_hw_led_on(0);
        rt_thread_delay(50); /* sleep 0.5 second and switch to other thread */

        /* led off */
        rt_kprintf("led1 off\r\n");
        rt_hw_led_off(0);
        rt_thread_delay(50);
    }
}

char thread_led2_stack[1024];
struct rt_thread thread_led2;
void rt_thread_entry_led2(void* parameter)
{
    unsigned int count=0;
    while (1)
    {
        /* led on */
        rt_kprintf("led2 on,count : %d\r\n",count);
        count++;
        rt_hw_led_on(1);
        rt_thread_delay(RT_TICK_PER_SECOND);

        /* led off */
        rt_kprintf("led2 off\r\n");
        rt_hw_led_off(1);
        rt_thread_delay(RT_TICK_PER_SECOND);
    }
}

int rt_application_init()
{
    rt_thread_t thread;

    /* create led1 thread */
    thread = rt_thread_create("led1",
                              rt_thread_entry_led1, RT_NULL,
                              512,
                              20, 5);
    if (thread != RT_NULL)
        rt_thread_startup(thread);

    //------- init led2 thread
    rt_thread_init(&thread_led2,
                   "led2",
                   rt_thread_entry_led2,
                   RT_NULL,
                   &thread_led2_stack[0],
                   sizeof(thread_led2_stack),10,10);
    rt_thread_startup(&thread_led2);

    return 0;
}

/*@}*/
