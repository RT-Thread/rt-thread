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
 * 2018-11-22     Jesven       add rt_hw_cpu_id()
 */

#include <rthw.h>
#include <rtthread.h>
#include <board.h>

#ifdef RT_USING_SMP
int rt_hw_cpu_id(void)
{
    int cpu_id;
    __asm__ volatile (
            "mrc p15, 0, %0, c0, c0, 5"
            :"=r"(cpu_id)
            );
    cpu_id &= 0xf;
    return cpu_id;
};
#endif

/**
 * @addtogroup ARM CPU
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
