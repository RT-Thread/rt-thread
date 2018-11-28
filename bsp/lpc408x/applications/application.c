/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2014-01-02    xiaonong       the first version for lpc408x
 */

#include <rtthread.h>

#ifdef RT_USING_FINSH
#include <shell.h>
#include <finsh.h>
#endif

/* thread phase init */
void rt_init_thread_entry(void *parameter)
{
    /* Initialization RT-Thread Components */
#ifdef RT_USING_COMPONENTS_INIT
    rt_components_init();
#elif defined(RT_USING_FINSH)
    finsh_system_init();
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
