/*
 * File      : application.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2014, RT-Thread Development Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2014-07-18     ArdaFu       the first version for TM4C129X
 */

#include <rtthread.h>
#include <board.h>
#include <components.h>

#ifdef RT_USING_LWIP
#include "drv_eth.h"
#endif
/* thread phase init */
void rt_init_thread_entry(void *parameter)
{
    /* Initialization RT-Thread Components */
    rt_components_init();
#ifdef RT_USING_FINSH
    finsh_set_device(RT_CONSOLE_DEVICE_NAME);
#endif
#ifdef RT_USING_LWIP
    rt_hw_tiva_eth_init();
#endif
}

int rt_application_init(void)
{
    rt_thread_t tid;
    tid = rt_thread_create("init",
                           rt_init_thread_entry, RT_NULL,
                           2048, RT_THREAD_PRIORITY_MAX / 3, 20);
    if (tid != RT_NULL) rt_thread_startup(tid);

    return 0;
}
