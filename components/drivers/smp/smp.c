/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/9/12      zhujiale     the first version
 */

#include "smp.h"

#define DBG_TAG "SMP"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static struct rt_smp_call rt_smp_work[RT_CPUS_NR];
static rt_atomic_t        rt_smp_wait;

static rt_err_t smp_call_handler(struct rt_smp_event *event)
{
    switch (event->event_id)
    {
    case SMP_CALL_EVENT_FUNC:
        event->func(event->data);
        rt_atomic_add(&rt_smp_wait, 1);
        break;
    default:
        LOG_E("error event id\n");
        return -RT_ERROR;
    }
    return RT_EOK;
}
void rt_smp_call_ipi_handler(int vector, void *param)
{
    int cur_cpu = rt_hw_cpu_id();

    rt_spin_lock(&rt_smp_work[cur_cpu].lock);
    if (rt_smp_work[cur_cpu].event.event_id)
    {
        if (smp_call_handler(&rt_smp_work[cur_cpu].event) != RT_EOK)
        {
            LOG_E("Have no event\n");
        }
        rt_memset(&rt_smp_work[cur_cpu].event, 0, sizeof(struct rt_smp_event));
    }
    rt_spin_unlock(&rt_smp_work[cur_cpu].lock);
}

/**
 * @brief call function on specified CPU ,
 *
 * @param cpu_mask cpu mask for call
 * @param func the function pointer
 * @param data the data pointer
 * @param flag call flag if you set SMP_CALL_WAIT_ALL
 *             then it will wait all cpu call finish and return
 *             else it will call function on specified CPU and return immediately
 * @param cond the condition function pointer,if you set it then it will call function only when cond return true
 */
void rt_smp_call_func_cond(int cpu_mask, rt_smp_call_func_back func, void *data, rt_uint8_t flag, rt_smp_cond cond)
{
    RT_DEBUG_NOT_IN_INTERRUPT;
    struct rt_smp_event event;
    rt_bool_t           need_call = RT_TRUE, need_wait = RT_FALSE;
    int                 cur_cpu = rt_hw_cpu_id();
    int                 cpuid   = 1 << cur_cpu;
    int                 tmp_id = 0, cpu_nr = 0;
    int                 tmp_mask;
    int                 irq_flag;

    if (flag == SMP_CALL_WAIT_ALL)
    {
        need_wait = RT_TRUE;
        rt_atomic_store(&rt_smp_wait, 0);
    }

    if (cpuid & cpu_mask)
    {
        func(data);
        cpu_mask = cpu_mask & (~cpuid);
    }

    if (!cpu_mask)
        need_call = RT_FALSE;

    tmp_mask = cpu_mask;
    if (need_call)
    {
        while (tmp_mask)
        {
            if ((tmp_mask & 1) && (tmp_id < RT_CPUS_NR))
            {
                if (cond && !cond(tmp_id, data))
                    continue;
                cpu_nr++;
                event.event_id = SMP_CALL_EVENT_FUNC;
                event.func     = func;
                event.data     = data;
                event.cpu_mask = cpu_mask;
                irq_flag       = rt_spin_lock_irqsave(&rt_smp_work[tmp_id].lock);
                rt_smp_work[tmp_id].event = event;
                rt_spin_unlock_irqrestore(&rt_smp_work[tmp_id].lock,irq_flag);
            }
            tmp_id++;
            tmp_mask = tmp_mask >> 1;
        }
        rt_hw_ipi_send(RT_FUNC_IPI, cpu_mask);
    }

    if (need_wait)
    {
        while (rt_atomic_load(&rt_smp_wait) != cpu_nr);
    }
}

void rt_smp_call_each_cpu(rt_smp_call_func_back func, void *data, rt_uint8_t flag)
{
    rt_smp_call_func_cond(RT_ALL_CPU, func, data, flag, RT_NULL);
}

void rt_smp_call_each_cpu_cond(rt_smp_call_func_back func, void *data, rt_uint8_t flag, rt_smp_cond cond_func)
{
    rt_smp_call_func_cond(RT_ALL_CPU, func, data, flag, cond_func);
}
void rt_smp_call_any_cpu(int cpu_mask, rt_smp_call_func_back func, void *data, rt_uint8_t flag)
{
    rt_smp_call_func_cond(cpu_mask, func, data, flag, RT_NULL);
}

void rt_smp_call_any_cpu_cond(int cpu_mask, rt_smp_call_func_back func, void *data, rt_uint8_t flag, rt_smp_cond cond_func)
{
    rt_smp_call_func_cond(cpu_mask, func, data, flag, cond_func);
}

void rt_smp_init(void)
{
    for (int i = 0; i < RT_CPUS_NR; i++)
    {
        rt_memset(&rt_smp_work[i], 0, sizeof(struct rt_smp_call));
        rt_spin_lock_init(&rt_smp_work[i].lock);
    }
}
