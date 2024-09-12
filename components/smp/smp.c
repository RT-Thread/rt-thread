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

struct smp_call global_work[RT_CPUS_NR];
rt_atomic_t wait;
rt_err_t smp_call_handler(struct smp_event *event)
{
    switch(event->event_id)
    {
    case SMP_CALL_EVENT_FUNC:
        event->func(event->data);
        rt_atomic_add(&wait,1);
        break;
    default:
        LOG_E("error event id\n");
        return RT_ERROR;
    }
    return RT_EOK;
}
void rt_smp_call_ipi_handler(int vector, void *param)
{
    int err;
    int cur_cpu = rt_hw_cpu_id();
    rt_spin_lock(&global_work[cur_cpu].lock);
    if(global_work[cur_cpu].event.event_id)
    {
        err = smp_call_handler(&global_work[cur_cpu].event);
        if(err)
        {
            LOG_E("Have no event\n");
            rt_memset(&global_work[cur_cpu].event,0,sizeof(struct smp_event));
            rt_spin_unlock(&global_work[cur_cpu].lock);
        }
        rt_memset(&global_work[cur_cpu].event,0,sizeof(struct smp_event));
    }
    rt_spin_unlock(&global_work[cur_cpu].lock);

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
void rt_smp_call_func_cond(int cpu_mask, smp_call_func_back func, void *data,rt_uint8_t flag,smp_cond cond)
{
    RT_DEBUG_NOT_IN_INTERRUPT;
    struct smp_event event;
    rt_bool_t need_call = RT_TRUE,need_wait = RT_FALSE;
    int cur_cpu = rt_hw_cpu_id();
    int cpuid = 1 << cur_cpu;
    int tmp_id = 0,cpu_nr = 0;
    int tmp_mask;

    if(flag == SMP_CALL_WAIT_ALL)
    {
        need_wait = RT_TRUE;
        rt_atomic_store(&wait,0);
    }

    if(cpuid & cpu_mask)
    {
        func(data);
        cpu_mask = cpu_mask & (~cpuid);
    }

    if(!cpu_mask)
        need_call = RT_FALSE;

    tmp_mask = cpu_mask;
    if(need_call)
    {
        while(tmp_mask)
        {
            if((tmp_mask & 1) && (tmp_id < RT_CPUS_NR))
            {
                if(cond && !cond(tmp_id,data))
                    continue;
                cpu_nr++;
                event.event_id = SMP_CALL_EVENT_FUNC;
                event.func = func;
                event.data = data;
                event.cpu_mask = cpu_mask;
                rt_spin_lock(&global_work[tmp_id].lock);
                global_work[tmp_id].event = event;
                rt_spin_unlock(&global_work[tmp_id].lock);
            }
            tmp_id++;
            tmp_mask = tmp_mask >> 1;
        }
        rt_hw_ipi_send(RT_IPI_FUNC, cpu_mask);
    }

    if(need_wait)
    {
        while(rt_atomic_load(&wait) != cpu_nr);
    }
}

void rt_call_each_cpu(smp_call_func_back func, void *data,rt_uint8_t flag)
{
    rt_smp_call_func_cond(RT_ALL_CPU,func,data,flag,RT_NULL);
}

void rt_call_each_cpu_cond(smp_call_func_back func, void *data,rt_uint8_t flag,smp_cond cond_func)
{
    rt_smp_call_func_cond(RT_ALL_CPU,func,data,flag,cond_func);
}
void rt_call_any_cpu(int cpu_mask,smp_call_func_back func, void *data,rt_uint8_t flag)
{
    rt_smp_call_func_cond(cpu_mask,func,data,flag,RT_NULL);
}

void rt_call_any_cpu_cond(int cpu_mask,smp_call_func_back func, void *data,rt_uint8_t flag,smp_cond cond_func)
{
    rt_smp_call_func_cond(cpu_mask,func,data,flag,cond_func);
}

void smp_init(void)
{
    for(int i = 0; i < RT_CPUS_NR; i++)
    {
        rt_memset(&global_work[i],0,sizeof(struct smp_call));
        rt_spin_lock_init(&global_work[i].lock);
    }
}

