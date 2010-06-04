/*
 * File      : app.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2008-12-11     xuxinming    the first version
 */

#include <rtthread.h>

/**
 * @addtogroup LPC2478
 */
/*@{*/

char thread1_stack[512];
char thread2_stack[512];

struct rt_thread thread1;
struct rt_thread thread2;

void thread1_entry(void* parameter)
{
	int i;

	while (1)
	{
		for (i = 0; i < 10; i ++)
		{
			rt_kprintf("%d\n", i);
			rt_thread_delay(100);
		}
	}
}

void thread2_entry(void* parameter)
{
	int count = 0;
	while (1)
	{
		rt_kprintf("Thread2 count:%d\n", count++);
		rt_thread_delay(50);
	}
}

int rt_application_init()
{
	rt_thread_init(&thread1,
		"thread1",
		thread1_entry, RT_NULL,
		&thread1_stack[0], sizeof(thread1_stack),
		20, 10);

	rt_thread_init(&thread2,
		"thread2",
		thread2_entry, RT_NULL,
		&thread2_stack[0], sizeof(thread2_stack),
		25, 8);

	rt_thread_startup(&thread1);
	rt_thread_startup(&thread2);

	return 0;
}

/*@}*/
