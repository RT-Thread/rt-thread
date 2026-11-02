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
    return __builtin_clzl(value);
#else
#error Unsupport clz
#endif
}
#endif /* RT_USING_CPU_FFS */

#ifdef RT_USING_SMART
#if defined(RT_USING_SMP) && RT_CPUS_NR > 1
extern void percpu_write(rt_ubase_t offset, const void *data, rt_size_t size);

void rt_hw_set_process_id(int pid)
{
    percpu_write(0, &pid, sizeof(pid));
}
#else
static int process_id;

void rt_hw_set_process_id(int pid)
{
    process_id = pid;
}
#endif /* RT_USING_SMP && RT_CPUS_NR > 1 */
#endif /* RT_USING_SMART */

#ifdef RT_USING_SMP
void rt_hw_spin_lock_init(rt_hw_spinlock_t *lock)
{
    lock->slock = 0;
}

void rt_hw_spin_lock(rt_hw_spinlock_t *lock)
{
    unsigned long tmp;
    unsigned short ticket;

    /*
     * The two 16-bit counters occupy the low word, also on RV64.
     * Use an AMO so ticket allocation cannot livelock with an unlock
     * retrying LR/SC on the same reservation. Word width wraps next at 16 bits.
     */
    __asm__ volatile (
            "amoadd.w.aqrl %0, %2, (%1)"
            : "=&r" (tmp)
            : "r" (&lock->slock), "r" (1UL << 16)
            : "memory");

    ticket = (tmp >> 16) & 0xffff;

    while (HWREG16(&lock->tickets.owner) != ticket)
    {
        __asm__ volatile (OPC_PAUSE_I);
    }

    /* Order critical-section accesses after observing the owner's release. */
    rt_hw_barrier();
}

void rt_hw_spin_unlock(rt_hw_spinlock_t *lock)
{
    /*
     * Only the holder writes owner. Publish critical-section accesses before
     * advancing it; a halfword store preserves concurrently allocated tickets.
     */
    rt_hw_barrier();
    HWREG16(&lock->tickets.owner) =
            (unsigned short)(HWREG16(&lock->tickets.owner) + 1);

    rt_hw_barrier();
}
#endif /* RT_USING_SMP */
