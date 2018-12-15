/*
 * File      : cpu.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-09-15     Bernard      first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <board.h>

/**
 * @addtogroup AM33xx
 */
/*@{*/

/** shutdown CPU */
void rt_hw_cpu_shutdown()
{
	rt_uint32_t level;
	rt_kprintf("shutdown...\n");

	level = rt_hw_interrupt_disable();
	while (level)
	{
		RT_ASSERT(0);
	}
}

/*@}*/
