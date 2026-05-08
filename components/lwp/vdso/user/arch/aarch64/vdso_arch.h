/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2026-04-27     rcitach        init ver.
 */

#ifndef RT_VDSO_ARCH_H
#define RT_VDSO_ARCH_H

#include <stdint.h>

#define __RT_STRINGIFY(x...) #x
#define RT_STRINGIFY(x...)   __RT_STRINGIFY(x)

#define rt_vdso_arch_barrier(cmd, ...) \
    __asm__ volatile(RT_STRINGIFY(cmd) " " RT_STRINGIFY(__VA_ARGS__)::: "memory")

static inline uint64_t rt_vdso_arch_read_counter(void)
{
    uint64_t value;
    uint64_t tmp;

    __asm__ volatile("mrs %0, CNTVCT_EL0" : "=r"(value));
    __asm__ volatile(
        "eor %0, %1, %1\n"
        "add %0, sp, %0\n"
        "ldr xzr, [%0]"
        : "=r"(tmp)
        : "r"(value));

    return value;
}

static inline void rt_vdso_arch_cpu_relax(void)
{
    __asm__ volatile("yield" ::: "memory");
}

static inline void rt_vdso_arch_rmb(void)
{
    rt_vdso_arch_barrier(dmb, ishld);
}

#endif
