/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-12     WangXiaoyao  the first version
 */
#ifndef __TLB_H__
#define __TLB_H__

#include "mm_aspace.h"
#include <rtthread.h>
#include <stddef.h>
#include <stdint.h>

#define dsb(scope)      __asm__ volatile("dsb " #scope : : : "memory")
#define isb()           __asm__ volatile("isb" : : : "memory")
#define STORE_CP32(r, name...) "mcr " RT_STRINGIFY(CP32(%r, name)) ";"

#define WRITE_CP32(v, name...) do {                             \
    register uint32_t _r = (v);                                 \
    asm volatile(STORE_CP32(0, name) : : "r" (_r));             \
} while (0)

static inline void rt_hw_tlb_invalidate_all(void)
{
    asm volatile ("mcr p15, 0, r0, c8, c7, 0\ndsb\nisb" ::: "memory");
}

static inline void rt_hw_tlb_invalidate_all_local(void)
{
    rt_hw_tlb_invalidate_all();
}

static inline void rt_hw_tlb_invalidate_aspace(rt_aspace_t aspace)
{
    rt_hw_tlb_invalidate_all();
}

static inline void rt_hw_tlb_invalidate_range(rt_aspace_t aspace, void *start,
                                              size_t size, size_t stride)
{
    rt_hw_tlb_invalidate_all();
}

#endif /* __TLB_H__ */
