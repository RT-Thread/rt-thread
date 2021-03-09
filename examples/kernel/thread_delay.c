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
 * This is an example for delay thread
 */
static struct rt_thread thread;
static char thread_stack[THREAD_STACK_SIZE];
static void thread_entry(void* parameter)
{
    rt_tick_t tick;
    rt_kprintf("thread inited ok\n");

    rt_kprintf("thread delay 10 tick\n");
    tick = rt_tick_get();
    rt_thread_delay(10);
    if (rt_tick_get() - tick > 11)
    {
        tc_done(TC_STAT_FAILED);
        return;
    }

    rt_kprintf("thread delay 15 tick\n");
    tick = rt_tick_get();
    rt_thread_delay(15);
    if (rt_tick_get() - tick > 16)
    {
        tc_done(TC_STAT_FAILED);
        return;
    }

    rt_kprintf("thread exit\n");

    tc_done(TC_STAT_PASSED);
}

rt_err_t thread_delay_init()
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
int _tc_thread_delay()
{
    thread_delay_init();

    return 30;
}
FINSH_FUNCTION_EXPORT(_tc_thread_delay, a thread delay test);
#else
int rt_application_init()
{
    thread_delay_init();

    return 0;
}
#endif
