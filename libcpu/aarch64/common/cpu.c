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
typedef rt_hw_spinlock_t arch_spinlock_t;

static inline void arch_spin_lock(arch_spinlock_t *lock)
{
    unsigned int tmp;

    asm volatile(
    "   sevl\n"
    "1: wfe\n"
    "2: ldaxr   %w0, %1\n"
    "   cbnz    %w0, 1b\n"
    "   stxr    %w0, %w2, %1\n"
    "   cbnz    %w0, 2b\n"
    : "=&r" (tmp), "+Q" (lock->lock)
    : "r" (1)
    : "cc", "memory");
}

static inline int arch_spin_trylock(arch_spinlock_t *lock)
{
    unsigned int tmp;

    asm volatile(
    "  ldaxr   %w0, %1\n"
    "  cbnz    %w0, 1f\n"
    "  stxr    %w0, %w2, %1\n"
    "1:\n"
    : "=&r" (tmp), "+Q" (lock->lock)
    : "r" (1)
    : "cc", "memory");

    return !tmp;
}

static inline void arch_spin_unlock(arch_spinlock_t *lock)
{
    asm volatile(
    " stlr    %w1, %0\n"
    : "=Q" (lock->lock) : "r" (0) : "memory");
}

void rt_hw_spin_lock_init(arch_spinlock_t *lock)
{
    lock->lock = 0;
}

void rt_hw_spin_lock(rt_hw_spinlock_t *lock)
{
    arch_spin_lock(lock);
}

void rt_hw_spin_unlock(rt_hw_spinlock_t *lock)
{
    arch_spin_unlock(lock);
}

rt_bool_t rt_hw_spin_trylock(rt_hw_spinlock_t *lock)
{
    return arch_spin_trylock(lock);
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
rt_weak void rt_hw_cpu_shutdown(void)
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
