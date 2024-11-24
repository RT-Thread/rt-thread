/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/9/12      zhujiale     the first version
 * 2024/10/24     Shell        added non-blocking IPI calling method;
 *                             fixup data racing
 */

#include "smp_call.h"

#define DBG_TAG "SMP"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static struct smp_data
{
    /* call request data to each cores */
    struct rt_smp_call_req call_req_cores[RT_CPUS_NR];

    /* call queue of this core */
    rt_ll_slist_t call_queue;
} _smp_data_cores[RT_CPUS_NR];

#define _CALL_REQ_USAGE_FREED 0
#define _CALL_REQ_USAGE_BUSY 1
static void _call_req_take(struct rt_smp_call_req *req)
{
    rt_base_t exp;
    do
    {
        exp = _CALL_REQ_USAGE_FREED;
    }
    while (!rt_atomic_compare_exchange_strong(&req->event.typed.usage_tracer, &exp, _CALL_REQ_USAGE_BUSY));
}

static void _call_req_release(struct rt_smp_call_req *req)
{
    rt_atomic_store(&req->event.typed.usage_tracer, _CALL_REQ_USAGE_FREED);
}

void rt_smp_request_wait_freed(struct rt_smp_call_req *req)
{
    rt_base_t usage_tracer;

    RT_DEBUG_IN_THREAD_CONTEXT;

    usage_tracer = rt_atomic_load(&req->event.typed.usage_tracer);
    while (usage_tracer != _CALL_REQ_USAGE_FREED)
    {
        rt_thread_yield();
        usage_tracer = rt_atomic_load(&req->event.typed.usage_tracer);
    }
}

static void _mask_out_cpu(struct rt_smp_event *event, int oncpu)
{
    rt_base_t new_mask, old_mask;
    rt_atomic_t *maskp = event->typed.calling_cpu_mask;
    do
    {
        old_mask = rt_atomic_load(maskp);
        new_mask = old_mask & ~(1ul << oncpu);
    } while (!rt_atomic_compare_exchange_strong(maskp, &old_mask, new_mask));
}

static void _do_glob_request(struct rt_smp_call_req *req_global,
                                             struct rt_smp_call_req *req_local)
{
    struct rt_smp_event *event;

    /* release the global request data */
    rt_memcpy(req_local, req_global, sizeof(struct rt_smp_call_req));
    rt_hw_spin_unlock(&req_global->freed_lock);

    event = &req_local->event;
    RT_ASSERT(!!event->func);
    event->func(event->data);

    return ;
}

static void _do_request(struct rt_smp_call_req *req)
{
    struct rt_smp_event *event;

    event = &req->event;
    RT_ASSERT(!!event->func);
    event->func(event->data);

    _call_req_release(req);
    return ;
}

static rt_err_t _smp_call_handler(struct rt_smp_call_req *req, int oncpu)
{
    switch (req->event.event_id)
    {
    case SMP_CALL_EVENT_GLOB_SYNC:
    {
        struct rt_smp_call_req req_local;
        _do_glob_request(req, &req_local);
        _mask_out_cpu(&req_local.event, oncpu);
        break;
    }
    case SMP_CALL_EVENT_GLOB_ASYNC:
    {
        struct rt_smp_call_req req_local;
        _do_glob_request(req, &req_local);
        break;
    }
    case SMP_CALL_EVENT_REQUEST:
    {
        _do_request(req);
        break;
    }
    default:
        LOG_E("error event id\n");
        return -RT_ERROR;
    }
    return RT_EOK;
}

void rt_smp_call_ipi_handler(int vector, void *param)
{
    int oncpu = rt_hw_cpu_id();
    struct rt_smp_call_req *request;

    RT_ASSERT(rt_interrupt_get_nest());

    while (1)
    {
        rt_ll_slist_t *node = rt_ll_slist_dequeue(&_smp_data_cores[oncpu].call_queue);
        if (node)
        {
            request = rt_list_entry(node, struct rt_smp_call_req, slist_node);

            _smp_call_handler(request, oncpu);
        }
        else
        {
            break;
        }
    }
}

static void _smp_call_remote_request(int callcpu, rt_smp_call_cb_t func,
                                     void *data, rt_uint8_t flags,
                                     struct rt_smp_call_req *call_req)
{
    rt_base_t cpu_mask = 1ul << callcpu;

    _call_req_take(call_req);

    rt_ll_slist_enqueue(&_smp_data_cores[callcpu].call_queue, &call_req->slist_node);

    rt_hw_ipi_send(RT_SMP_CALL_IPI, cpu_mask);
}

/**
 * @brief SMP call request with user provided @call_req. Compare to
 *        rt_smp_call_func* family, you can call it in ISR or IRQ-masked
 *        environment.
 *
 * @param callcpu the logical core id of the target
 * @param flags control flags of your request
 * @param call_req the pre-initialized request data
 * @return rt_err_t RT_EOK on succeed, otherwise the errno to failure
 */
rt_err_t rt_smp_call_request(int callcpu, rt_uint8_t flags, struct rt_smp_call_req *call_req)
{
    rt_ubase_t clvl;
    int oncpu;

    if (rt_atomic_load(&call_req->event.typed.usage_tracer) ==
        _CALL_REQ_USAGE_BUSY)
    {
        return -RT_EBUSY;
    }

    if (flags & SMP_CALL_WAIT_ALL)
    {
        return -RT_EINVAL;
    }

    clvl = rt_enter_critical();
    oncpu = rt_hw_cpu_id();

    if (oncpu == callcpu && !(flags & SMP_CALL_NO_LOCAL))
    {
        rt_ubase_t level;

        /* handle IPI on irq-masked environment */
        level = rt_hw_local_irq_disable();
        call_req->event.func(call_req->event.data);
        rt_hw_local_irq_enable(level);
    }
    else if (callcpu < RT_CPUS_NR)
    {
        _smp_call_remote_request(callcpu, call_req->event.func, call_req->event.data, flags, call_req);
    }

    rt_exit_critical_safe(clvl);

    return RT_EOK;
}

void rt_smp_call_req_init(struct rt_smp_call_req *call_req,
                          rt_smp_call_cb_t func, void *data)
{
    call_req->event.typed.usage_tracer = 0;
    call_req->event.data = data;
    call_req->event.func = func;
    call_req->event.event_id = SMP_CALL_EVENT_REQUEST;
}

static void _smp_call_func_cond(int oncpu, rt_ubase_t cpu_mask,
                                rt_smp_call_cb_t func, void *data,
                                rt_uint8_t flags, rt_smp_cond_t cond)
{
    rt_ubase_t          tmp_mask;
    rt_bool_t           sync_call = RT_FALSE;
    rt_ubase_t          oncpu_mask = 1 << oncpu;
    rt_atomic_t         calling_cpu_mask, *maskp;
    int                 tmp_id = 0, rcpu_cnt = 0, event_id, call_local;

    if (!(flags & SMP_CALL_NO_LOCAL) && (oncpu_mask & cpu_mask))
    {
        call_local = RT_TRUE;
        cpu_mask = cpu_mask & (~oncpu_mask);
    }
    else
    {
        call_local = RT_FALSE;
    }

    if (cpu_mask)
    {
        tmp_mask = cpu_mask;

        if (flags & SMP_CALL_WAIT_ALL)
        {
            sync_call = RT_TRUE;
            maskp = &calling_cpu_mask;
            event_id = SMP_CALL_EVENT_GLOB_SYNC;
            rt_atomic_store(maskp, cpu_mask);
        }
        else
        {
            event_id = SMP_CALL_EVENT_GLOB_ASYNC;
            maskp = RT_NULL;
        }

        while (tmp_mask)
        {
            struct rt_smp_call_req *call_req;
            struct rt_smp_event *event;
            int lz_bit = __rt_ffsl(tmp_mask);

            tmp_id = lz_bit - 1;
            tmp_mask &= ~(1ul << tmp_id);

            if (cond && !cond(tmp_id, data))
            {
                cpu_mask &= ~(1ul << tmp_id);
                continue;
            }

            /* need to wait one more */
            rcpu_cnt++;

            call_req = &_smp_data_cores[oncpu].call_req_cores[tmp_id];

            /* very careful here, spinning wait on previous occupation */
            rt_hw_spin_lock(&call_req->freed_lock);

            event                   = &call_req->event;
            event->event_id         = event_id;
            event->func             = func;
            event->data             = data;
            event->typed.calling_cpu_mask = maskp;

            rt_ll_slist_enqueue(&_smp_data_cores[tmp_id].call_queue, &call_req->slist_node);
        }

        if (cpu_mask)
        {
            RT_ASSERT(rcpu_cnt);

            rt_hw_ipi_send(RT_SMP_CALL_IPI, cpu_mask);
        }
    }

    if (call_local && (!cond || cond(tmp_id, data)))
    {
        rt_ubase_t level;

        /* callback on local with sims ISR */
        level = rt_hw_local_irq_disable();
        func(data);
        rt_hw_local_irq_enable(level);
    }

    if (sync_call && rcpu_cnt)
    {
        while (rt_atomic_load(maskp) & cpu_mask)
            ;
    }
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
void rt_smp_call_func_cond(rt_ubase_t cpu_mask, rt_smp_call_cb_t func, void *data, rt_uint8_t flag, rt_smp_cond_t cond)
{
    int oncpu;
    rt_ubase_t clvl;

    RT_ASSERT(!rt_hw_interrupt_is_disabled());

    clvl = rt_enter_critical();
    oncpu = rt_hw_cpu_id();

    if (cpu_mask <= RT_ALL_CPU)
    {
        _smp_call_func_cond(oncpu, cpu_mask, func, data, flag, cond);
    }

    rt_exit_critical_safe(clvl);
}

void rt_smp_call_each_cpu(rt_smp_call_cb_t func, void *data, rt_uint8_t flag)
{
    rt_smp_call_func_cond(RT_ALL_CPU, func, data, flag, RT_NULL);
}

void rt_smp_call_each_cpu_cond(rt_smp_call_cb_t func, void *data, rt_uint8_t flag, rt_smp_cond_t cond_func)
{
    rt_smp_call_func_cond(RT_ALL_CPU, func, data, flag, cond_func);
}

void rt_smp_call_cpu_mask(rt_ubase_t cpu_mask, rt_smp_call_cb_t func, void *data, rt_uint8_t flag)
{
    rt_smp_call_func_cond(cpu_mask, func, data, flag, RT_NULL);
}

void rt_smp_call_cpu_mask_cond(rt_ubase_t cpu_mask, rt_smp_call_cb_t func, void *data, rt_uint8_t flag, rt_smp_cond_t cond_func)
{
    rt_smp_call_func_cond(cpu_mask, func, data, flag, cond_func);
}

void rt_smp_call_init(void)
{
    rt_memset(&_smp_data_cores, 0, sizeof(_smp_data_cores));

    for (int i = 0; i < RT_CPUS_NR; i++)
    {
        for (int j = 0; j < RT_CPUS_NR; j++)
        {
            rt_hw_spin_lock_init(&_smp_data_cores[i].call_req_cores[j].freed_lock);
        }
    }
}
