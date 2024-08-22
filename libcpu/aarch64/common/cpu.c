/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-09-15     Bernard      first version
 * 2019-07-28     zdzn         add smp support
 * 2023-02-21     GuEe-GUI     mov cpu ofw init to setup
 * 2024-04-29     Shell        Add generic ticket spinlock using C11 atomic
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include <cpu.h>

#define DBG_TAG "libcpu.aarch64.cpu"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#ifdef RT_USING_SMP

#define REPORT_ERR(retval) LOG_E("got error code %d in %s(), %s:%d", (retval), __func__, __FILE__, __LINE__)
#define CHECK_RETVAL(retval) if (retval) {REPORT_ERR(retval);}
#define cpuid_to_hwid(cpuid) \
    ((((cpuid) >= 0) && ((cpuid) < RT_CPUS_NR)) ? rt_cpu_mpidr_early[cpuid] : ID_ERROR)
#define set_hwid(cpuid, hwid) \
    ((((cpuid) >= 0) && ((cpuid) < RT_CPUS_NR)) ? (rt_cpu_mpidr_early[cpuid] = (hwid)) : ID_ERROR)
#define get_cpu_node(cpuid) \
    ((((cpuid) >= 0) && ((cpuid) < RT_CPUS_NR)) ? _cpu_node[cpuid] : NULL)
#define set_cpu_node(cpuid, node) \
    ((((cpuid) >= 0) && ((cpuid) < RT_CPUS_NR)) ? (_cpu_node[cpuid] = node) : NULL)

typedef rt_hw_spinlock_t arch_spinlock_t;
struct cpu_ops_t *cpu_ops_tbl[RT_CPUS_NR];

#ifdef RT_USING_SMART
// _id_to_mpidr is a table translate logical id to mpid, which is a 64-bit value
rt_uint64_t rt_cpu_mpidr_early[RT_CPUS_NR] rt_weak = {[0 ... RT_CPUS_NR - 1] = ID_ERROR};
#else
/* The more common mpidr_el1 table, redefine it in BSP if it is in other cases */
rt_weak rt_uint64_t rt_cpu_mpidr_early[] =
{
    [0] = 0x80000000,
    [1] = 0x80000001,
    [2] = 0x80000002,
    [3] = 0x80000003,
    [4] = 0x80000004,
    [5] = 0x80000005,
    [6] = 0x80000006,
    [7] = 0x80000007,
    [RT_CPUS_NR] = 0
};
#endif /* RT_USING_SMART */

/* in support of C11 atomic */
#if __STDC_VERSION__ >= 201112L
#include <stdatomic.h>

union _spinlock
{
    _Atomic(rt_uint32_t) _value;
    struct
    {
        _Atomic(rt_uint16_t) owner;
        _Atomic(rt_uint16_t) next;
    } ticket;
};

void rt_hw_spin_lock_init(rt_hw_spinlock_t *_lock)
{
    union _spinlock *lock = (void *)_lock;

    /**
     * just a dummy note that this is an atomic operation, though it alway is
     * even without usage of atomic API in arm64
     */
    atomic_store_explicit(&lock->_value, 0, memory_order_relaxed);
}

rt_bool_t rt_hw_spin_trylock(rt_hw_spinlock_t *_lock)
{
    rt_bool_t rc;
    rt_uint32_t readonce;
    union _spinlock temp;
    union _spinlock *lock = (void *)_lock;

    readonce = atomic_load_explicit(&lock->_value, memory_order_acquire);
    temp._value = readonce;

    if (temp.ticket.owner != temp.ticket.next)
    {
        rc = RT_FALSE;
    }
    else
    {
        temp.ticket.next += 1;
        rc = atomic_compare_exchange_strong_explicit(
            &lock->_value, &readonce, temp._value,
            memory_order_acquire, memory_order_relaxed);
    }
    return rc;
}

rt_inline rt_base_t _load_acq_exclusive(_Atomic(rt_uint16_t) *halfword)
{
    rt_uint32_t old;
    __asm__ volatile("ldaxrh %w0, [%1]"
                     : "=&r"(old)
                     : "r"(halfword)
                     :  "memory");
    return old;
}

rt_inline void _send_event_local(void)
{
    __asm__ volatile("sevl");
}

rt_inline void _wait_for_event(void)
{
    __asm__ volatile("wfe" ::: "memory");
}

void rt_hw_spin_lock(rt_hw_spinlock_t *_lock)
{
    union _spinlock *lock = (void *)_lock;
    rt_uint16_t ticket =
        atomic_fetch_add_explicit(&lock->ticket.next, 1, memory_order_relaxed);

    if (atomic_load_explicit(&lock->ticket.owner, memory_order_acquire) !=
        ticket)
    {
        _send_event_local();
        do
        {
            _wait_for_event();
        }
        while (_load_acq_exclusive(&lock->ticket.owner) != ticket);
    }
}

void rt_hw_spin_unlock(rt_hw_spinlock_t *_lock)
{
    union _spinlock *lock = (void *)_lock;
    atomic_fetch_add_explicit(&lock->ticket.owner, 1, memory_order_release);
}

#endif

static int _cpus_init_data_hardcoded(int num_cpus, rt_uint64_t *cpu_hw_ids, struct cpu_ops_t *cpu_ops[])
{
    // load in cpu_hw_ids in cpuid_to_hwid,
    // cpu_ops to cpu_ops_tbl
    if (num_cpus > RT_CPUS_NR)
    {
        LOG_W("num_cpus (%d) greater than RT_CPUS_NR (%d)\n", num_cpus, RT_CPUS_NR);
        num_cpus = RT_CPUS_NR;
    }

    for (int i = 0; i < num_cpus; i++)
    {
        set_hwid(i, cpu_hw_ids[i]);
        cpu_ops_tbl[i] = cpu_ops[i];
    }
    return 0;
}

/** init cpu with hardcoded infomation or parsing from FDT */
static int _cpus_init(int num_cpus, rt_uint64_t *cpu_hw_ids, struct cpu_ops_t *cpu_ops[])
{
    int retval;

    // first setup cpu_ops_tbl and cpuid_to_hwid
    if (num_cpus > 0)
        retval = _cpus_init_data_hardcoded(num_cpus, cpu_hw_ids, cpu_ops);
    else
    {
        retval = -1;
    }

    if (retval)
        return retval;

    // using cpuid_to_hwid and cpu_ops_tbl to call method_init and cpu_init
    // assuming that cpuid 0 has already init
    for (int i = 1; i < RT_CPUS_NR; i++)
    {
        if (rt_cpu_mpidr_early[i] == ID_ERROR)
        {
            LOG_E("Failed to find hardware id of CPU %d", i);
            continue;
        }

        if (cpu_ops_tbl[i] && cpu_ops_tbl[i]->cpu_init)
        {
            retval = cpu_ops_tbl[i]->cpu_init(i, RT_NULL);
            CHECK_RETVAL(retval);
        }
        else
        {
            LOG_E("Failed to find cpu_init for cpu %d with cpu_ops[%p], cpu_ops->cpu_init[%p]"
                , rt_cpu_mpidr_early[i], cpu_ops_tbl[i], cpu_ops_tbl[i] ? cpu_ops_tbl[i]->cpu_init : NULL);
        }
    }
    return 0;
}

/**
 * @brief boot cpu with hardcoded data
 *
 * @param num_cpus number of cpus
 * @param cpu_hw_ids each element represents a hwid of cpu[i]
 * @param cpu_ops each element represents a pointer to cpu_ops of cpu[i]
 * @return int 0 on success,
 */
int rt_hw_cpu_boot_secondary(int num_cpus, rt_uint64_t *cpu_hw_ids, struct cpu_ops_t *cpu_ops[])
{
    int retval = 0;
    if (num_cpus < 1 || !cpu_hw_ids || !cpu_ops)
        return -1;

    retval = _cpus_init(num_cpus, cpu_hw_ids, cpu_ops);
    CHECK_RETVAL(retval);

    return retval;
}

#endif /*RT_USING_SMP*/

/**
 * @addtogroup ARM CPU
 */
/*@{*/

const char *rt_hw_cpu_arch(void)
{
    return "aarch64";
}

/*@}*/
