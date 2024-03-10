/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */
#include <rtthread.h>
#include "drv_led.h"
#include "drv_uart.h"

static void thread1_entry(void* parameter)
{
    while(1)
    {
            Led_Control(0,1);
            rt_thread_delay(RT_TICK_PER_SECOND);
            Led_Control(0,0);
            rt_thread_delay(RT_TICK_PER_SECOND);
    }
}

static void thread2_entry(void* parameter)
{
    while(1)
    {
            Led_Control(1,1);
            rt_thread_delay(RT_TICK_PER_SECOND);
            Led_Control(1,0);
            rt_thread_delay(RT_TICK_PER_SECOND);
    }
}


int demo_init(void)
{
    rt_thread_t  thread1 = RT_NULL;
    rt_thread_t  thread2 = RT_NULL;


    rt_led_hw_init();


  thread1 = rt_thread_create("t1",thread1_entry, RT_NULL,512,10,5);
  if (thread1 != RT_NULL)
            rt_thread_startup(thread1);

    thread2 = rt_thread_create("t2",thread2_entry, RT_NULL,512,10,5);
    if (thread2 != RT_NULL)
            rt_thread_startup(thread2);


    return 0;

}
