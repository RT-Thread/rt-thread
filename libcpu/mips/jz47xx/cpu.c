/*
 * File      : cpu.c
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

