/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-09-15     Bernard      first version
 * 2019-07-28     zdzn         add smp support
 * 2021-12-21     GuEe-GUI     set tpidr_el1 as multiprocessor id instead of mpidr_el1
 * 2021-12-28     GuEe-GUI     add spinlock for aarch64
 */

#include <rthw.h>
#include <rtthread.h>
#include <cpuport.h>

#ifdef RT_USING_SMP
/* The more common mpidr_el1 table, redefine it in BSP if it is in other cases */
RT_WEAK rt_uint64_t rt_cpu_mpidr_early[] =
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
#endif

int rt_hw_cpu_id(void)
{
    rt_base_t value;

    __asm__ volatile ("mrs %0, tpidr_el1":"=r"(value));

    return value;
}

#ifdef RT_USING_SMP
void rt_hw_spin_lock_init(rt_hw_spinlock_t *lock)
{
    lock->slock = 0;
}

void rt_hw_spin_lock(rt_hw_spinlock_t *lock)
{
    rt_hw_spinlock_t lock_val, new_lockval;
    unsigned int tmp;

    __asm__ volatile (
        /* Increment the next ticket. */
        "   prfm    pstl1strm, %3\n"
        "1: ldaxr   %w0, %3\n"
        "   add %w1, %w0, %w5\n"
        "   stxr    %w2, %w1, %3\n"
        "   cbnz    %w2, 1b\n"
        /* Check wether we get the lock */
        "   eor     %w1, %w0, %w0, ror #16\n"
        "   cbz     %w1, 3f\n"
        /*
         * Didn't get lock and spin on the owner.
         * Should send a local event to avoid missing an
         * unlock before the exclusive load.
         */
        "   sevl\n"
        "2: wfe\n"
        "   ldaxrh  %w2, %4\n"
        "   eor     %w1, %w2, %w0, lsr #16\n"
        "   cbnz    %w1, 2b\n"
        /* got the lock. */
        "3:"
        : "=&r" (lock_val), "=&r" (new_lockval), "=&r" (tmp), "+Q" (*lock)
        : "Q" (lock->tickets.owner), "I" (1 << 16)
        : "memory");
    __DMB();
}

void rt_hw_spin_unlock(rt_hw_spinlock_t *lock)
{
    __DMB();
    __asm__ volatile (
        "stlrh   %w1, %0\n"
        : "=Q" (lock->tickets.owner)
        : "r" (lock->tickets.owner + 1)
        : "memory");
}
#endif /*RT_USING_SMP*/

/**
 * @addtogroup ARM CPU
 */
/*@{*/

/** shutdown CPU */
RT_WEAK void rt_hw_cpu_shutdown()
{
    register rt_int32_t level;
    rt_kprintf("shutdown...\n");

    level = rt_hw_interrupt_disable();
    while (level)
    {
        RT_ASSERT(0);
    }
}

/*@}*/
