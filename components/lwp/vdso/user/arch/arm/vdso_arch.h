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
    uint32_t lo;
    uint32_t hi;

    __asm__ volatile("mrrc p15, 1, %0, %1, c14" : "=r"(lo), "=r"(hi));
    rt_vdso_arch_barrier(dmb, ish);

    return ((uint64_t)hi << 32) | lo;
}

static inline void rt_vdso_arch_cpu_relax(void)
{
    __asm__ volatile("yield" ::: "memory");
}

static inline void rt_vdso_arch_rmb(void)
{
    rt_vdso_arch_barrier(dmb, ish);
}

#endif
