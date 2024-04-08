/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-10-25     Shell        Move ffs to cpuport, add general implementation
 *                             by inline assembly
 */

#ifndef  CPUPORT_H__
#define  CPUPORT_H__

#include <armv8.h>
#include <rtcompiler.h>
#include <rtdef.h>

#ifdef RT_USING_SMP
typedef struct {
    volatile unsigned int lock;
} rt_hw_spinlock_t;
#endif

#define rt_hw_barrier(cmd, ...) \
    __asm__ volatile (RT_STRINGIFY(cmd) " "RT_STRINGIFY(__VA_ARGS__):::"memory")

#define rt_hw_isb() rt_hw_barrier(isb)
#define rt_hw_dmb() rt_hw_barrier(dmb, ish)
#define rt_hw_wmb() rt_hw_barrier(dmb, ishst)
#define rt_hw_rmb() rt_hw_barrier(dmb, ishld)
#define rt_hw_dsb() rt_hw_barrier(dsb, ish)

#define rt_hw_wfi() rt_hw_barrier(wfi)
#define rt_hw_wfe() rt_hw_barrier(wfe)
#define rt_hw_sev() rt_hw_barrier(sev)

#define rt_hw_cpu_relax() rt_hw_barrier(yield)

#define rt_hw_sysreg_write(sysreg, val) \
    __asm__ volatile ("msr "RT_STRINGIFY(sysreg)", %0"::"r"((rt_uint64_t)(val)))

#define rt_hw_sysreg_read(sysreg, val) \
    __asm__ volatile ("mrs %0, "RT_STRINGIFY(sysreg)"":"=r"((val)))

void _thread_start(void);

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
rt_inline int __rt_ffs(int value)
{
#ifdef __GNUC__
    return __builtin_ffs(value);
#else
    __asm__ volatile (
        "rbit w1, %w0\n"
        "cmp %w0, 0\n"
        "clz w1, w1\n"
        "csinc %w0, wzr, w1, eq\n"
        : "=r"(value)
        : "0"(value)
    );
    return value;
#endif
}

#endif /* RT_USING_CPU_FFS */

#endif  /*CPUPORT_H__*/
