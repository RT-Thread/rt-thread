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

#include <rthw.h>
#include <rtthread.h>
#include "dm36x.h"

/**
 * @addtogroup DM36X
 */
/*@{*/

/**
 * reset cpu by dog's time-out
 *
 */
void machine_reset()
{
	reset_system();
}

/**
 *  shutdown CPU
 *
 */
void machine_shutdown()
{

}

#ifdef RT_USING_FINSH

#include <finsh.h>
FINSH_FUNCTION_EXPORT_ALIAS(rt_hw_cpu_reset, reset, restart the system);

#ifdef FINSH_USING_MSH
int cmd_reset(int argc, char** argv)
{
	rt_hw_cpu_reset();
	return 0;
}

int cmd_shutdown(int argc, char** argv)
{
	rt_hw_cpu_shutdown();
	return 0;
}

FINSH_FUNCTION_EXPORT_ALIAS(cmd_reset, __cmd_reset, restart the system.);
FINSH_FUNCTION_EXPORT_ALIAS(cmd_shutdown, __cmd_shutdown, shutdown the system.);

#endif
#endif

/*@}*/
