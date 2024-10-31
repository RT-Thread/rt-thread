/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/9/12      zhujiale     the first version
 * 2024/10/24     Shell        added non-blocking IPI calling method
 */

#ifndef __SMP_IPI_H__
#define __SMP_IPI_H__
#include <rtthread.h>

/* callback of smp call */
typedef void (*rt_smp_call_cb_t)(void *data);
typedef rt_bool_t (*rt_smp_cond_t)(int cpu, void *info);

#define SMP_CALL_EVENT_GLOB_ASYNC 0x1
#define SMP_CALL_EVENT_GLOB_SYNC  0x2
#define SMP_CALL_EVENT_REQUEST    0x4

#define SMP_CALL_WAIT_ALL (1ul << 0)
#define SMP_CALL_NO_LOCAL (1ul << 1)
#define SMP_CALL_SIGNAL   (1ul << 2)

#define RT_ALL_CPU ((1 << RT_CPUS_NR) - 1)
struct rt_smp_event
{
    int                   event_id;
    void                 *data;
    rt_smp_call_cb_t      func;

    union
    {
        rt_atomic_t      *calling_cpu_mask;
        rt_atomic_t       usage_tracer;
    } typed;
};

struct rt_smp_call_req
{
    /* handle the busy status synchronization */
    rt_hw_spinlock_t    freed_lock;
    struct rt_smp_event event;
    rt_ll_slist_t       slist_node;
};

void rt_smp_call_ipi_handler(int vector, void *param);
void rt_smp_call_each_cpu(rt_smp_call_cb_t func, void *data, rt_uint8_t flags);
void rt_smp_call_each_cpu_cond(rt_smp_call_cb_t func, void *data, rt_uint8_t flag, rt_smp_cond_t cond_func);
void rt_smp_call_cpu_mask(rt_ubase_t cpu_mask, rt_smp_call_cb_t func, void *data, rt_uint8_t flags);
void rt_smp_call_cpu_mask_cond(rt_ubase_t cpu_mask, rt_smp_call_cb_t func, void *data, rt_uint8_t flag, rt_smp_cond_t cond_func);
void rt_smp_call_init(void);

rt_err_t rt_smp_call_request(int callcpu, rt_uint8_t flags, struct rt_smp_call_req *call_req);
void rt_smp_call_req_init(struct rt_smp_call_req *call_req,
                          rt_smp_call_cb_t func, void *data);
void rt_smp_request_wait_freed(struct rt_smp_call_req *req);

#define rt_smp_for_each_cpu(_iter) for (_iter = 0; (_iter) < RT_CPUS_NR; (_iter)++)
rt_inline size_t rt_smp_get_next_remote(size_t iter, size_t cpuid)
{
    iter++;
    return iter == cpuid ? iter + 1 : iter;
}
#define rt_smp_for_each_remote_cpu(_iter, _cpuid) for (_iter = rt_smp_get_next_remote(-1, _cpuid); (_iter) < RT_CPUS_NR; _iter=rt_smp_get_next_remote(_iter, _cpuid))
#endif
