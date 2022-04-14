/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
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
RT_WEAK void rt_hw_cpu_reset()
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
