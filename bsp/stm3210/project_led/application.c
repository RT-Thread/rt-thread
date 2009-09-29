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

void led(void* parameter)
{
	/* init led configuration */
	rt_hw_led_init();
	
	while (1)
	{
		/* led on */
		rt_hw_led_on(0);
		rt_thread_delay(50); /* sleep 0.5 second and switch to other thread */
		
		/* led off */
		rt_hw_led_off(0);
		rt_thread_delay(50);
	}
}

int rt_application_init()
{
	rt_thread_t thread;
	
	/* create led thread */
	thread = rt_thread_create("led", 
		led, RT_NULL,
		512,
		20, 5);
	if (thread != RT_NULL)
		rt_thread_startup(thread);

	return 0;
}

/*@}*/
