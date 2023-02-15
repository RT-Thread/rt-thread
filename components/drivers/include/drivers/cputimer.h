/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author            Notes
 * 2023-02-13     zhkag           first version
 */

#ifndef CPUTIMER_H__
#define CPUTIMER_H__

#include <rtthread.h>

struct rt_cputimer
{
    struct rt_object parent; /**< inherit from rt_object */
    rt_list_t row;
    void (*timeout_func)(void *parameter);
    void *parameter;
    rt_uint64_t init_tick;
    rt_uint64_t timeout_tick;
};
typedef struct rt_cputimer *rt_cputimer_t;

rt_err_t rt_cputimer_detach(rt_cputimer_t timer);

#ifdef RT_USING_HEAP
void rt_cputimer_init(rt_cputimer_t timer,
                      const char *name,
                      void (*timeout)(void *parameter),
                      void *parameter,
                      rt_uint64_t tick,
                      rt_uint8_t flag);
rt_err_t rt_cputimer_delete(rt_cputimer_t timer);
#endif

rt_err_t rt_cputimer_start(rt_cputimer_t timer);
rt_err_t rt_cputimer_stop(rt_cputimer_t timer);
rt_err_t rt_cputimer_control(rt_cputimer_t timer, int cmd, void *arg);
rt_err_t rt_cputime_sleep(rt_uint64_t tick);
rt_err_t rt_cputime_ndelay(rt_uint64_t ns);
rt_err_t rt_cputime_udelay(rt_uint64_t us);
rt_err_t rt_cputime_mdelay(rt_uint64_t ms);

#endif
