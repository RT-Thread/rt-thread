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
 */

#include <rtthread.h>
#include "LPC24xx.h"

/**
 * @addtogroup LPC2478
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

/*@}*/
