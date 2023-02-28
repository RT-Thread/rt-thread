/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2006-08-23     Bernard      first version
 */

#include <rtthread.h>


/**
 * @addtogroup AT91SAM7X
 */
/*@{*/

/**
 * this function will reset CPU
 *
 */
rt_weak void rt_hw_cpu_reset()
{
}

/**
 * this function will shutdown CPU
 *
 */
rt_weak void rt_hw_cpu_shutdown()
{
    rt_kprintf("shutdown...\n");

    while (1);
}

/*@}*/
