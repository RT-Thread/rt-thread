/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2017-09-14     Haley        the first version
 */

/**
 * @addtogroup APOLLO2
 */
/*@{*/

#include <rtthread.h>
#include <stdint.h>
#ifdef RT_USING_FINSH
#include <finsh.h>
#include <shell.h>
#endif

#include "hw_led.h"

ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t led_stack[ 512 ];
static struct rt_thread led_thread;

static void led_thread_entry(void* parameter)
{
    unsigned int count=0;

		rt_hw_led_init(0);
		rt_hw_led_init(1);
	
    while (1)
    {
        /* led1 on */
#ifndef RT_USING_FINSH
        rt_kprintf("led on, count : %d\r\n",count);
#endif
        count++;
        rt_hw_led_on(0);
        rt_thread_delay( RT_TICK_PER_SECOND/2 ); /* sleep 0.5 second and switch to other thread */

        /* led1 off */
#ifndef RT_USING_FINSH
        rt_kprintf("led off\r\n");
#endif
        rt_hw_led_off(0);
        rt_thread_delay( RT_TICK_PER_SECOND/2 );
    }
}

void rt_init_thread_entry(void* parameter)
{
		#ifdef RT_USING_COMPONENTS_INIT
		/* initialization RT-Thread Components */
		rt_components_init();
		#endif	
}

int rt_application_init(void)
{
    rt_thread_t init_thread;

    rt_err_t result;

    /* init led thread */
    result = rt_thread_init(&led_thread,
                            "led",
                            led_thread_entry,
                            RT_NULL,
                            (rt_uint8_t*)&led_stack[0],
                            sizeof(led_stack),
                            7,
                            5);
    if (result == RT_EOK)
    {
        rt_thread_startup(&led_thread);
    }
		
    init_thread = rt_thread_create("init", rt_init_thread_entry, RT_NULL, 1024,
                            RT_THREAD_PRIORITY_MAX / 3, 20);
    if (init_thread != RT_NULL)
        rt_thread_startup(init_thread);

    return 0;
}

/*@}*/
