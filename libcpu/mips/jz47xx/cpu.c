/*
 * File      : cpu.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2010, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2010-07-09     Bernard      first version
 */
#include <rtthread.h>


/**
 * @addtogroup Jz47xx
 */
/*@{*/

/**
 * this function will reset CPU
 *
 */
void rt_hw_cpu_reset()
{
	/* open the watch-dog */
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

/*@}*/

