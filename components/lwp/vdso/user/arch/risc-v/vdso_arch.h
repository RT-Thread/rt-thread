/*
 * Copyright (c) 2006-2026 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author         Notes
 * 2024-07-04     rcitach        init ver.
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

    __asm__ volatile("rdtime %0" : "=r"(value));
    rt_vdso_arch_barrier(fence, rw, rw);

    return value;
}

static inline void rt_vdso_arch_cpu_relax(void)
{
    __asm__ volatile("nop" ::: "memory");
}

static inline void rt_vdso_arch_rmb(void)
{
    rt_vdso_arch_barrier(fence, r, r);
}

#endif
