/*
 * File      : cpu.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://openlab.rt-thread.com/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2008-12-11     XuXinming    first version
 * 2013-05-24     Grissiom     port to RM48x50
 */

#include <rtthread.h>

/**
 * @addtogroup RM48x50
 */
/*@{*/

/**
 * this function will reset CPU
 *
 */
void rt_hw_cpu_reset()
{
}

/**
 * this function will shutdown CPU
 *
 */
void rt_hw_cpu_shutdown()
{
	rt_kprintf("shutdown...\n");

	while (1);
}

#ifdef RT_USING_CPU_FFS
int __rt_ffs(int value)
{
	if (value == 0)
		return value;

	__asm("    rsb r1, r0, #0");
	__asm("    and r1, r1, r0");
	__asm("    clz r1, r1");
	__asm("    rsb r0, r1, #32");
}
#endif

/*@}*/
