/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-07-03     rcitach      test case
 */

#ifndef PERF_TC_H__
#define PERF_TC_H__

#include <rtthread.h>
#include <rtdevice.h>
#include <rtservice.h>
#include <rttypes.h>

#define THREAD_STACK_SIZE       2048
#define THREAD_PRIORITY         10
#define THREAD_TIMESLICE        5
typedef struct rt_perf
{
    char name[64];
    volatile rt_uint32_t begin_time;
    volatile rt_uint32_t real_time;
    volatile rt_uint32_t tot_time;
    volatile rt_uint32_t max_time;
    volatile rt_uint32_t min_time;
    volatile rt_uint32_t count;
    volatile double avg_time;
    volatile rt_uint32_t tmp_time;  /* Temporary data */
    rt_mutex_t lock;
    void (*local_modify)(struct rt_perf *perf);
    rt_bool_t dump_head;
} rt_perf_t;

void rt_perf_start_impl(rt_perf_t *perf, rt_hwtimerval_t *timeout);
void rt_perf_stop(rt_perf_t *perf);
void rt_perf_dump( rt_perf_t *perf);

static inline void rt_perf_start(rt_perf_t *perf)
{
    rt_perf_start_impl(perf, RT_NULL);
}

rt_err_t context_switch_test(rt_perf_t *perf);
rt_err_t rt_perf_irq_latency(rt_perf_t *perf);
rt_err_t rt_perf_thread_sem(rt_perf_t *perf);
rt_err_t rt_perf_thread_event(rt_perf_t *perf);
rt_err_t rt_perf_thread_mq(rt_perf_t *perf);
rt_err_t rt_perf_thread_mbox(rt_perf_t *perf);

#endif /* PERF_TC_H__ */

