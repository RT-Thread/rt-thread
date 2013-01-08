/*
 * File      : cpu.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-03-30     Kyle         First version
 */

#include <rtthread.h>

/**
 * @addtogroup AVR32UC3
 */
/*@{*/

/**
 * reset cpu by dog's time-out
 *
 */
void rt_hw_cpu_reset()
{
	/*NOTREACHED*/
}

/**
 *  shutdown CPU
 *
 */
void rt_hw_cpu_shutdown()
{
	rt_kprintf("shutdown...\n");

	RT_ASSERT(0);
}

/*@}*/
