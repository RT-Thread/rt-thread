/*
 * Copyright (c) 2006-2024 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024/10/28     Shell        Added smp.smoke
 */

#include <rtdevice.h>
#include <utest.h>
#include <utest_assert.h>
#include <smp_call.h>

#define PERCPU_TEST_COUNT 10000
#define NEWLINE_ON 80
#define MAX_RETRIES (RT_TICK_PER_SECOND)

static struct rt_semaphore _utestd_exited;
static rt_thread_t _utestd[RT_CPUS_NR];
static rt_atomic_t _entry_counts[RT_CPUS_NR];
static struct rt_smp_call_req _callreq_data[RT_CPUS_NR][RT_CPUS_NR];
static rt_ubase_t _masks_data[RT_CPUS_NR];
static RT_DEFINE_SPINLOCK(_test_data_lock);

static void _logging_progress(char id)
{
    static rt_atomic_t counts;
    rt_ubase_t old;

    rt_kprintf("%c", id);
    old = rt_atomic_add(&counts, 1);
    if (old % NEWLINE_ON == 0)
    {
        rt_kputs("\n");
    }
}

static void _reentr_isr_cb(void *param)
{
    rt_ubase_t *maskp;
    int  oncpu;

    if (!rt_hw_interrupt_is_disabled())
    {
        /* SYNC.004 */
        uassert_true(0);
    }

    rt_spin_lock(&_test_data_lock);

    oncpu   = rt_hw_cpu_id();
    maskp   = (rt_ubase_t *)param;
    *maskp  |= (1 << oncpu);

    rt_spin_unlock(&_test_data_lock);

    _logging_progress('0' + (maskp - _masks_data));
}

static void _test_smp_call_isr(void *param)
{
    rt_err_t error;
    rt_ubase_t iter, oncpu = (rt_ubase_t)param;
    struct rt_smp_call_req *callreqp = _callreq_data[oncpu];

    if (rt_hw_cpu_id() != oncpu)
    {
        /* SYNC.004 */
        uassert_true(0);
    }

    if (!rt_hw_interrupt_is_disabled())
    {
        /* SYNC.004, PRIV.001 */
        uassert_true(0);
    }

    rt_smp_for_each_remote_cpu(iter, oncpu)
    {
        error = rt_smp_call_request(iter, SMP_CALL_NO_LOCAL, &callreqp[iter]);
        if (error)
        {
            /* SYNC.002 */
            uassert_false(error);
        }
    }
}

static rt_ubase_t _wait_for_update(rt_ubase_t *maskp, rt_ubase_t exp, int cpuid, rt_thread_t curthr)
{
    rt_ubase_t level, current_mask;

    for (size_t i = cpuid; i < RT_CPUS_NR; i++)
    {
        rt_thread_control(curthr, RT_THREAD_CTRL_BIND_CPU, (void *)(i % RT_CPUS_NR));
    }

    for (size_t i = 0; i < MAX_RETRIES; i++)
    {
        level = rt_spin_lock_irqsave(&_test_data_lock);
        current_mask = *maskp;
        rt_spin_unlock_irqrestore(&_test_data_lock, level);

        if (current_mask == exp)
        {
            break;
        }
        rt_thread_delay(1);
    }

    return current_mask;
}
static void _utestd_entry(void *oncpu_param)
{
    rt_thread_t curthr = rt_thread_self();
    rt_ubase_t oncpu = (rt_ubase_t)oncpu_param;
    rt_ubase_t worker_id = (oncpu + 1) % RT_CPUS_NR;
    int cpu_mask = 1ul << worker_id;
    rt_ubase_t req_cpus_mask = ~cpu_mask & RT_ALL_CPU;
    rt_ubase_t *mask_data = &_masks_data[worker_id];
    rt_ubase_t current_mask;
    rt_ubase_t level;

    for (size_t i = 0; i < PERCPU_TEST_COUNT; i++)
    {
        rt_smp_call_cpu_mask(cpu_mask, _test_smp_call_isr, (void *)worker_id, 0);

        current_mask = _wait_for_update(mask_data, req_cpus_mask, worker_id, curthr);
        if (current_mask != req_cpus_mask)
        {
            LOG_I("current mask 0x%x, last fetch 0x%x", *mask_data, current_mask);

            /* MP.002, TARG.001 */
            uassert_true(0);
            break;
        }
        else
        {
            rt_ubase_t iter;
            level = rt_spin_lock_irqsave(&_test_data_lock);
            *mask_data = 0;
            rt_spin_unlock_irqrestore(&_test_data_lock, level);

            rt_smp_for_each_remote_cpu(iter, worker_id)
            {
                rt_smp_request_wait_freed(&_callreq_data[worker_id][iter]);
            }
        }
    }

    rt_sem_release(&_utestd_exited);
}

static void _test_reentr_isr_main(void)
{
    for (size_t i = 0; i < RT_CPUS_NR; i++)
    {
        rt_thread_startup(_utestd[i]);
    }

    for (size_t i = 0; i < RT_CPUS_NR; i++)
    {
        rt_sem_take(&_utestd_exited, RT_WAITING_FOREVER);
    }
}

static rt_err_t utest_tc_init(void)
{
    size_t iter_x, iter_y;
    rt_smp_for_each_cpu(iter_x)
    {
        rt_smp_for_each_cpu(iter_y)
        {
            rt_smp_call_req_init(&_callreq_data[iter_x][iter_y],
                                 _reentr_isr_cb, &_masks_data[iter_x]);
        }
    }

    for (size_t i = 0; i < RT_CPUS_NR; i++)
    {
        _masks_data[i] = 0;
        rt_atomic_store(&_entry_counts[i], 0);
        _utestd[i] = rt_thread_create("utestd", _utestd_entry, (void *)i,
                                      UTEST_THR_STACK_SIZE, UTEST_THR_PRIORITY + 1,
                                      20);
        rt_thread_control(_utestd[i], RT_THREAD_CTRL_BIND_CPU, (void *)i);
        uassert_true(_utestd[i] != RT_NULL);
    }

    rt_sem_init(&_utestd_exited, "utestd", 0, RT_IPC_FLAG_PRIO);
    srand(rt_tick_get());

    return RT_EOK;
}

static rt_err_t utest_tc_cleanup(void)
{
    rt_sem_detach(&_utestd_exited);

    return RT_EOK;
}

static void _testcase(void)
{
    UTEST_UNIT_RUN(_test_reentr_isr_main);
}

UTEST_TC_EXPORT(_testcase, "testcase.smp.smoke.004", utest_tc_init, utest_tc_cleanup, 10);
