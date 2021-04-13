/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 *
 */

#include <rtthread.h>
#include "tc_comm.h"

/*
 * This is an example for static thread
 */
static struct rt_thread thread;
static char thread_stack[THREAD_STACK_SIZE];
static void thread_entry(void* parameter)
{
    rt_kprintf("thread staticly inited ok\n");
    rt_thread_delay(10);
    rt_kprintf("thread exit\n");

    tc_done(TC_STAT_PASSED);
}

rt_err_t thread_static_init()
{
    rt_err_t result;

    result = rt_thread_init(&thread,
        "test",
        thread_entry, RT_NULL,
        &thread_stack[0], sizeof(thread_stack),
        THREAD_PRIORITY, 10);

    if (result == RT_EOK)
        rt_thread_startup(&thread);
    else
        tc_stat(TC_STAT_END | TC_STAT_FAILED);

    return result;
}

#ifdef RT_USING_TC
int _tc_thread_static()
{
    thread_static_init();

    return 20;
}
FINSH_FUNCTION_EXPORT(_tc_thread_static, a static thread test);
#else
int rt_application_init()
{
    thread_static_init();

    return 0;
}
#endif

