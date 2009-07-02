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
 * 2006-03-13     Bernard      first version
 */

#include <rtthread.h>

/**
 * @addtogroup S3C2410
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
