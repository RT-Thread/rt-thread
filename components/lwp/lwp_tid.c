/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-15     shaojinchun  first version
 */

#include <rthw.h>
#include <rtthread.h>

#include "lwp.h"

#ifdef RT_USING_USERSPACE
#include "lwp_user_mm.h"

#ifdef RT_USING_GDBSERVER
#include <hw_breakpoint.h>
#include <lwp_gdbserver.h>
#endif

#endif

#define DBG_TAG    "LWP_TID"
#define DBG_LVL    DBG_INFO
#include <rtdbg.h>

static rt_thread_t lwp_tid_ary[LWP_TID_MAX_NR];
static rt_thread_t *lwp_tid_free_head = RT_NULL;
static int lwp_tid_ary_alloced = 1; /* 0 is reserved */

int lwp_tid_get(void)
{
    int ret = 0;
    rt_base_t level = rt_hw_interrupt_disable();
    rt_thread_t *p = lwp_tid_free_head;

    if (p)
    {
        lwp_tid_free_head = (rt_thread_t*)*p;
    }
    else if (lwp_tid_ary_alloced < LWP_TID_MAX_NR)
    {
        p = lwp_tid_ary + lwp_tid_ary_alloced;
        lwp_tid_ary_alloced++;
    }
    if (p)
    {
        *p = RT_NULL;
        ret = p - lwp_tid_ary;
    }
    rt_hw_interrupt_enable(level);
    return ret;
}

void lwp_tid_put(int tid)
{
    rt_thread_t *p = RT_NULL;
    rt_base_t level = rt_hw_interrupt_disable();

    if (tid > 0 && tid < LWP_TID_MAX_NR)
    {
        p = lwp_tid_ary + tid;
        *p = (rt_thread_t)lwp_tid_free_head;
        lwp_tid_free_head = p;
    }
    rt_hw_interrupt_enable(level);
}

rt_thread_t lwp_tid_get_thread(int tid)
{
    rt_thread_t thread = RT_NULL;

    if (tid > 0 && tid < LWP_TID_MAX_NR)
    {
        thread = lwp_tid_ary[tid];
        if ((thread >= (rt_thread_t)lwp_tid_ary)
                && (thread < (rt_thread_t)(lwp_tid_ary + LWP_TID_MAX_NR)))
        {
            /* the tid is not used */
            thread = RT_NULL;
        }
    }
    return thread;
}

void lwp_tid_set_thread(int tid, rt_thread_t thread)
{
    if (tid > 0 && tid < LWP_TID_MAX_NR)
    {
        lwp_tid_ary[tid] = thread;
    }
}
