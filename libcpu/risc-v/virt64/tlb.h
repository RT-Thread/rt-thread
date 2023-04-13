/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-28     WangXiaoyao  the first version
 */
#ifndef __TLB_H__
#define __TLB_H__

#include <stddef.h>
#include <stdint.h>

#include <rtthread.h>
#include <mm_aspace.h>
#include "sbi.h"
#include "riscv_mmu.h"

#define HANDLE_FAULT(ret)                                                      \
    if (__builtin_expect((ret) != SBI_SUCCESS, 0))                             \
        LOG_W("%s failed", __FUNCTION__);

static inline void rt_hw_tlb_invalidate_all(void)
{
    uintptr_t mask = -1ul;
    HANDLE_FAULT(sbi_remote_sfence_vma(&mask, -1ul, 0, mask));
}

static inline void rt_hw_tlb_invalidate_all_local(void)
{
    __asm__ volatile("sfence.vma" ::: "memory");
}

static inline void rt_hw_tlb_invalidate_aspace(rt_aspace_t aspace)
{
    // TODO ASID
    rt_hw_tlb_invalidate_all_local();
}

static inline void rt_hw_tlb_invalidate_page(rt_aspace_t aspace, void *start)
{
    __asm__ volatile("sfence.vma %0, zero" ::"r"(start) : "memory");
}

static inline void rt_hw_tlb_invalidate_range(rt_aspace_t aspace, void *start,
                                              size_t size, size_t stride)
{
    // huge page is taking as normal page
    if (size <= ARCH_PAGE_SIZE)
    {
        rt_hw_tlb_invalidate_page(aspace, start);
    }
    else
    {
        rt_hw_tlb_invalidate_aspace(aspace);
    }
}

#endif /* __TLB_H__ */
