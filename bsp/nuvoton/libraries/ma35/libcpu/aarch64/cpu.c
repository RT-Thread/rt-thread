/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-09-15     Bernard      first version
 * 2019-07-28     zdzn         add smp support
 */

#include <rthw.h>
#include <rtthread.h>
#include <board.h>
#include "cp15.h"

int rt_hw_cpu_id(void)
{
    int cpu_id;
    rt_base_t value;

    __asm__ volatile(
        "mrs %0, mpidr_el1"
        :"=r"(value)
    );
    cpu_id = value & 0xf;
    return cpu_id;
};

#ifdef RT_USING_SMP
void rt_hw_spin_lock_init(rt_hw_spinlock_t *lock)
{
    lock->slock = 0;
}

void rt_hw_spin_lock(rt_hw_spinlock_t *lock)
{
    unsigned long tmp;
    unsigned long newval;
    rt_hw_spinlock_t lockval;

    __asm__ __volatile__(
        "      prfm    pstl1strm, %3\n"
        "1:    ldaxr    %w0, %3\n"
        "      add    %w1, %w0, %w5\n"
        "    stxr    %w2, %w1, %3\n"
        "    cbnz    %w2, 1b\n"
        /* Did we get the lock? */
        "    eor    %w1, %w0, %w0, ror #16\n"
        "    cbz    %w1, 3f\n"
        "    sevl\n"
        "2:    wfe\n"
        "    ldaxrh    %w2, %4\n"
        "    eor    %w1, %w2, %w0, lsr #16\n"
        "    cbnz    %w1, 2b\n"
        "3:"
        : "=&r"(lockval), "=&r"(newval), "=&r"(tmp), "+Q"(*lock)
        : "Q"(lock->slock), "I"(1 << 16)
        : "memory");


}

void rt_hw_spin_unlock(rt_hw_spinlock_t *lock)
{
    __DMB();
    lock->tickets.owner++;
    __DSB();
    __SEV();
}
#endif /*RT_USING_SMP*/

/**
 * @addtogroup ARM CPU
 */
/*@{*/

/** shutdown CPU */
RT_WEAK void rt_hw_cpu_shutdown()
{
    rt_uint32_t level;
    rt_kprintf("shutdown...\n");

    level = rt_hw_interrupt_disable();
    while (level)
    {
        RT_ASSERT(0);
    }
}

#ifdef RT_USING_CPU_FFS
/**
 * This function finds the first bit set (beginning with the least significant bit)
 * in value and return the index of that bit.
 *
 * Bits are numbered starting at 1 (the least significant bit).  A return value of
 * zero from any of these functions means that the argument was zero.
 *
 * @return return the index of the first bit set. If value is 0, then this function
 * shall return 0.
 */
int __rt_ffs(int value)
{
    return __builtin_ffs(value);
}
#endif

/*@}*/
