/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 */

#ifndef  CPUPORT_H__
#define  CPUPORT_H__

#include <armv8.h>
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

#define sysreg_write(sysreg, val) \
    __asm__ volatile ("msr "RT_STRINGIFY(sysreg)", %0"::"r"((rt_uint64_t)(val)))

#define sysreg_read(sysreg, val) \
    __asm__ volatile ("mrs %0, "RT_STRINGIFY(sysreg)"":"=r"((val)))

void _thread_start(void);
#endif  /*CPUPORT_H__*/
