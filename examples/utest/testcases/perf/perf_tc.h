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
    rt_list_t data_list;
#ifdef UTEST_SYS_IRQ_LATENCY
    void *user_data;
#endif

} rt_perf_t;

void rt_perf_start(rt_perf_t *perf);
void rt_perf_stop(rt_perf_t *perf);

rt_err_t context_switch_test(rt_perf_t *perf);
rt_err_t rt_perf_irq_latency(rt_perf_t *perf);
rt_err_t rt_perf_thread_sem(rt_perf_t *perf);
rt_err_t rt_perf_thread_event(rt_perf_t *perf);
rt_err_t rt_perf_thread_mq(rt_perf_t *perf);
rt_err_t rt_perf_thread_mbox(rt_perf_t *perf);

#endif /* PERF_TC_H__ */

