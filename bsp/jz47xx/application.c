/*
 * File      : app.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-06-25     Bernard      first version
 */

/**
 * @addtogroup JZ47xx
 */
/*@{*/
#include <rtthread.h>

#include <jz4755.h>

static struct rt_thread thread1;
static rt_uint8_t thread1_stack[1024];

void thread_entry(void* parameter)
{
	while (1)
	{
		rt_kprintf("IPR: 0x%08x, SR : 0x%08x, CAUSE: 0x%08x\n", INTC_IPR, read_c0_status(), read_c0_cause());

		rt_thread_delay(100);
	}
}

int rt_application_init()
{
	rt_err_t result;

	result = rt_thread_init(&thread1, "t1",
		thread_entry, RT_NULL,
		&thread1_stack[0], sizeof(thread1_stack),
		200, 10);
	if (result == RT_EOK)
		rt_thread_startup(&thread1);

	return 0;
}

/*@}*/
