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
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#ifdef RT_USING_SMP
void rt_hw_spin_lock_init(rt_hw_spinlock_t *lock)
{
    lock->slock = 0;
}

#define TICKET_SHIFT 16
void rt_hw_spin_lock(rt_hw_spinlock_t *lock)
{
    unsigned int tmp;
    struct __arch_tickets lockval, newval;

    asm volatile(
        /* Atomically increment the next ticket. */
        "   prfm    pstl1strm, %3\n"
        "1: ldaxr   %w0, %3\n"
        "   add %w1, %w0, %w5\n"
        "   stxr    %w2, %w1, %3\n"
        "   cbnz    %w2, 1b\n"
        /* Did we get the lock? */
        "   eor %w1, %w0, %w0, ror #16\n"
        "   cbz %w1, 3f\n"
        /*
         * No: spin on the owner. Send a local event to avoid missing an
         * unlock before the exclusive load.
         */
        "   sevl\n"
        "2: wfe\n"
        "   ldaxrh  %w2, %4\n"
        "   eor %w1, %w2, %w0, lsr #16\n"
        "   cbnz    %w1, 2b\n"
        /* We got the lock. Critical section starts here. */
        "3:"
        : "=&r"(lockval), "=&r"(newval), "=&r"(tmp), "+Q"(*lock)
        : "Q"(lock->tickets.owner), "I"(1 << TICKET_SHIFT)
        : "memory");
    rt_hw_dmb();
}

void rt_hw_spin_unlock(rt_hw_spinlock_t *lock)
{
    rt_hw_dmb();
    asm volatile(
        "   stlrh   %w1, %0\n"
        : "=Q"(lock->tickets.owner)
        : "r"(lock->tickets.owner + 1)
        : "memory");
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

/** shutdown CPU */
rt_weak void rt_hw_cpu_shutdown()
{
    register rt_ubase_t level;

    rt_kprintf("shutdown...\n");

    level = rt_hw_interrupt_disable();
    while (level)
    {
        RT_ASSERT(0);
    }
}
MSH_CMD_EXPORT_ALIAS(rt_hw_cpu_shutdown, shutdown, shutdown machine);

/** reset CPU */
rt_weak void rt_hw_cpu_reset()
{
    register rt_ubase_t level;

    rt_kprintf("reset...\n");

    level = rt_hw_interrupt_disable();
    while (level)
    {
        RT_ASSERT(0);
    }
}
MSH_CMD_EXPORT_ALIAS(rt_hw_cpu_reset, reset, reset...);

/*@}*/
