/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-11-20     Shell        Add cond var API in kernel
 */

#ifndef __LWP_TERMINAL_CONDVAR_H__
#define __LWP_TERMINAL_CONDVAR_H__

#include <rtthread.h>

typedef struct rt_condvar
{
#ifdef USING_RT_OBJECT
    struct rt_object parent;
#endif
    rt_atomic_t waiters_cnt;
    rt_atomic_t waiting_mtx;
    struct rt_wqueue event;
} *rt_condvar_t;

void rt_condvar_init(rt_condvar_t cv, char *name);
int rt_condvar_timedwait(rt_condvar_t cv, rt_mutex_t mtx, int suspend_flag,
                         rt_tick_t timeout);
int rt_condvar_signal(rt_condvar_t cv);
int rt_condvar_broadcast(rt_condvar_t cv);

rt_inline void rt_condvar_detach(rt_condvar_t cv)
{
    return ;
}

#endif /* __LWP_TERMINAL_CONDVAR_H__ */
