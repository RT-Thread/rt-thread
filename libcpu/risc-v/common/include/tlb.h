/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-28     WangXiaoyao  the first version
 * 2025-04-26     GuEe-GUI     Follow the specific and vendor
 */

#ifndef __TLB_H__
#define __TLB_H__

#include <rtthread.h>

#include <csr.h>
#include <sbi.h>
#include <page_def.h>
#include <mm_aspace.h>

#define SFENCE_VMA_ASID(asid) \
        __asm__ volatile ("sfence.vma x0, %0"::"r"(asid) : "memory");

#define SFENCE_VMA_ADDR_INV(start) \
        __asm__ volatile ("sfence.vma %0, zero" ::"r"(start) : "memory");

rt_inline void rt_hw_tlb_invalidate_all(void)
{
    union
    {
        unsigned long mask;
        unsigned long all;
    } flush = { -1UL };

    if (sbi_remote_sfence_vma(&flush.mask, flush.all, 0, flush.all) == SBI_SUCCESS)
    {
        return;
    }

    LOG_W("TLB invalidate all failed");
}

rt_inline void rt_hw_tlb_invalidate_all_local(void)
{
    __asm__ volatile ("sfence.vma" ::: "memory");
}

rt_inline void rt_hw_tlb_invalidate_aspace(rt_aspace_t aspace)
{
#if defined(ARCH_RISCV_DISABLE_SFENCE_VMA_ASID) || !defined(ARCH_USING_ASID)
    rt_hw_tlb_invalidate_all_local();
#else
    rt_uint64_t asid_value = aspace->asid & SATP_ASID_MASK;

    SFENCE_VMA_ASID(asid_value);
#endif
}

rt_inline void rt_hw_tlb_invalidate_page(rt_aspace_t aspace, void *start)
{
    RT_UNUSED(aspace);
    SFENCE_VMA_ADDR_INV(start);
}

rt_inline void rt_hw_tlb_invalidate_range(rt_aspace_t aspace, void *start,
                                              size_t size, size_t stride)
{
    /* huge page is taking as normal page */
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
