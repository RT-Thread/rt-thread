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
 * 2009-01-05     Bernard      the first version
 */

/**
 * @addtogroup LM3S
 */
/*@{*/

#include <rthw.h>
#include <rtthread.h>

char thread1_stack[0x120];
struct rt_thread thread1;

void thread1_entry(void* parameter)
{
	rt_uint32_t i = 0;

	while (1)
	{
		rt_kprintf("thread1 --> %d\n", ++i);
		rt_thread_delay(100);
	}
}

void thread_test()
{
	rt_thread_init(&thread1,
		"thread1",
		thread1_entry, RT_NULL,
		&thread1_stack[0], sizeof(thread1_stack),
		20, 15);

	rt_thread_startup(&thread1);
}
#ifdef RT_USING_FINSH
#include <finsh.h>
FINSH_FUNCTION_EXPORT(thread_test, test a basic thread)
#endif

int rt_application_init()
{
	return 0;
}
/*@}*/
