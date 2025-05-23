/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-28     Bernard      The unify RISC-V porting code.
 * 2025-04-20     GuEe-GUI     Port ffsN and clz, spinlock
 */

#include <rthw.h>
#include <rtthread.h>

#include <asm-generic.h>

#ifdef RT_USING_CPU_FFS

int __rt_ffs(int value)
{
#ifdef __GNUC__
    return __builtin_ffs(value);
#else
#error Unsupport ffs
#endif
}

unsigned long __rt_ffsl(unsigned long value)
{
#ifdef __GNUC__
    return __builtin_ffsl(value);
#else
#error Unsupport ffsl
#endif
}

unsigned long __rt_clz(unsigned long value)
{
#ifdef __GNUC__
    return __builtin_clz(value);
#else
#error Unsupport clz
#endif
}
#endif /* RT_USING_CPU_FFS */

#ifdef RT_USING_SMART
extern void percpu_write(rt_ubase_t offset, const void *data, rt_size_t size);

void rt_hw_set_process_id(int pid)
{
    percpu_write(0, &pid, sizeof(pid));
}
#endif /* RT_USING_SMART */

#ifdef RT_USING_SMP
void rt_hw_spin_lock_init(rt_hw_spinlock_t *lock)
{
    lock->slock = 0;
}

void rt_hw_spin_lock(rt_hw_spinlock_t *lock)
{
    unsigned long tmp, new_val, mask;
    unsigned short ticket;

    __asm__ volatile (
            "1:\n\t"
            "   lr." REG_WIDTH ".aq %0, (%3)\n\t"
            "   srli    %1, %0, 16\n\t"
            "   addi    %1, %1, 1\n\t"
            "   slli    %1, %1, 16\n\t"
            "   li      %2, 0xffff\n\t"
            "   and     %2, %0, %2\n\t"
            "   or      %1, %1, %2\n\t"
            "   sc." REG_WIDTH ".rl %1, %1, (%3)\n\t"
            "   bnez    %1, 1b"
            : "=&r" (tmp), "=&r" (new_val), "=&r" (mask)
            : "r" (&lock->slock)
            : "memory");

    ticket = (tmp >> 16) & 0xffff;

    while (HWREG16(&lock->tickets.owner) != ticket)
    {
        __asm__ volatile (OPC_PAUSE_I);
    }
}

void rt_hw_spin_unlock(rt_hw_spinlock_t *lock)
{
    unsigned long tmp, new_val, mask;

    __asm__ volatile (
            "1:\n\t"
            "   lr." REG_WIDTH ".aq %0, (%3)\n\t"
            "   addi    %1, %0, 1\n\t"
            "   li      %2, 0xffff\n\t"
            "   and     %1, %1, %2\n\t"
            "   slli    %2, %2, 16\n\t"
            "   and     %0, %0, %2\n\t"
            "   or      %1, %0, %1\n\t"
            "   sc." REG_WIDTH ".rl %1, %1, (%3)\n\t"
            "   bnez    %1, 1b"
            : "=&r" (tmp), "=&r" (new_val), "=&r" (mask)
            : "r" (&lock->slock)
            : "memory");

    rt_hw_barrier();
}
#endif /* RT_USING_SMP */
