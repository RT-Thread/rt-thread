/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2014-08-03     aozima       first implementation
 */

#include <board.h>
#include <rtthread.h>

void rt_init_thread_entry(void* parameter)
{
    rt_components_init();

#ifdef RT_USING_LWIP
    cme_m7_eth_init();

    set_if("e0", "192.168.1.99", "192.168.1.1", "255.255.255.0");
#endif /* RT_USING_LWIP */
}

int rt_application_init()
{
    rt_thread_t tid;

    tid = rt_thread_create("init",
        rt_init_thread_entry,
        RT_NULL,
        2048,
        RT_THREAD_PRIORITY_MAX/3,
        20);

    if (tid != RT_NULL)
        rt_thread_startup(tid);

    return 0;
}

/*@}*/
