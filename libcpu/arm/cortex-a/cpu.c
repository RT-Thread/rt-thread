/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-09-15     Bernard      first version
 * 2018-11-22     Jesven       add rt_hw_cpu_id()
 */

#include <rthw.h>
#include <rtthread.h>
#include <board.h>

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
            "pld [%0]"
            ::"r"(&lock->slock)
            );

    __asm__ __volatile__(
            "1: ldrex   %0, [%3]\n"
            "   add %1, %0, %4\n"
            "   strex   %2, %1, [%3]\n"
            "   teq %2, #0\n"
            "   bne 1b"
            : "=&r" (lockval), "=&r" (newval), "=&r" (tmp)
            : "r" (&lock->slock), "I" (1 << 16)
            : "cc");

    while (lockval.tickets.next != lockval.tickets.owner) {
        __asm__ __volatile__("wfe":::"memory");
        lockval.tickets.owner = *(volatile unsigned short *)(&lock->tickets.owner);
    }

    __asm__ volatile ("dmb":::"memory");
}

void rt_hw_spin_unlock(rt_hw_spinlock_t *lock)
{
    __asm__ volatile ("dmb":::"memory");
    lock->tickets.owner++;
    __asm__ volatile ("dsb ishst\nsev":::"memory");
}
#endif /*RT_USING_SMP*/

/**
 * @addtogroup ARM CPU
 */
/*@{*/

/** shutdown CPU */
RT_WEAK void rt_hw_cpu_shutdown()
{
    rt_base_t level;
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
