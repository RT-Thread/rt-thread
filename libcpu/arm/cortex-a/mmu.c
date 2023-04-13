/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-01-10     bernard      porting to AM1808
 */

#include <rthw.h>
#include <rtthread.h>

#define DBG_TAG "hw.mmu"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#include <board.h>
#include "cp15.h"
#include "mm_page.h"
#include "mmu.h"
#include <mm_aspace.h>
#include <tlb.h>

#ifdef RT_USING_SMART
#include <lwp_mm.h>
#include <lwp_arch.h>
#include "ioremap.h"
#else
#define KERNEL_VADDR_START 0
#endif

/* level1 page table, each entry for 1MB memory. */
volatile unsigned long MMUTable[4 * 1024] __attribute__((aligned(16 * 1024)));

unsigned long rt_hw_set_domain_register(unsigned long domain_val)
{
    unsigned long old_domain;

    asm volatile ("mrc p15, 0, %0, c3, c0\n" : "=r" (old_domain));
    asm volatile ("mcr p15, 0, %0, c3, c0\n" : :"r" (domain_val) : "memory");

    return old_domain;
}

void rt_hw_mmu_setmtt(rt_uint32_t vaddrStart, rt_uint32_t vaddrEnd,
                      rt_uint32_t paddrStart, rt_uint32_t attr)
{
    volatile rt_uint32_t *pTT;
    volatile int i, nSec;
    pTT  = (rt_uint32_t *)MMUTable + (vaddrStart >> 20);
    nSec = (vaddrEnd >> 20) - (vaddrStart >> 20);
    for(i = 0; i <= nSec; i++)
    {
        *pTT = attr | (((paddrStart >> 20) + i) << 20);
        pTT++;
    }
}

void rt_hw_init_mmu_table(struct mem_desc *mdesc, rt_uint32_t size)
{
    void *vaddr;
    size_t length;
    /* init kernel space */
#ifdef RT_USING_SMART
    rt_aspace_init(&rt_kernel_space, (void *)USER_VADDR_TOP, -USER_VADDR_TOP, (void *)MMUTable);
#else
    rt_aspace_init(&rt_kernel_space, (void *)0x1000, 0 - 0x1000, (void *)MMUTable);
#endif /* RT_USING_SMART */

    /* set page table */
    for(; size > 0; size--)
    {
        if (mdesc->paddr_start == (rt_uint32_t)ARCH_MAP_FAILED)
            mdesc->paddr_start = mdesc->vaddr_start + PV_OFFSET;

        vaddr = (void *)mdesc->vaddr_start;
        length = mdesc->vaddr_end - mdesc->vaddr_start;
        rt_aspace_map_static(&rt_kernel_space, &mdesc->varea, &vaddr, length,
                             mdesc->attr, MMF_MAP_FIXED, &rt_mm_dummy_mapper, 0);

        rt_hw_mmu_setmtt(mdesc->vaddr_start, mdesc->vaddr_end,
                mdesc->paddr_start, mdesc->attr);
        mdesc++;
    }

    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, (void*)MMUTable, sizeof MMUTable);
}

void rt_hw_mmu_init(void)
{
    rt_cpu_dcache_clean_flush();
    rt_cpu_icache_flush();
    rt_hw_cpu_dcache_disable();
    rt_hw_cpu_icache_disable();
    rt_cpu_mmu_disable();

    /*rt_hw_cpu_dump_page_table(MMUTable);*/
    rt_hw_set_domain_register(0x55555555);

    rt_cpu_tlb_set(MMUTable);

    rt_cpu_mmu_enable();

    rt_hw_cpu_icache_enable();
    rt_hw_cpu_dcache_enable();
}

int rt_hw_mmu_map_init(struct rt_aspace *aspace, void* v_address, size_t size, size_t *vtable, size_t pv_off)
{
    size_t l1_off, va_s, va_e;

    if (!aspace || !vtable)
    {
        return -1;
    }

    va_s = (size_t)v_address;
    va_e = (size_t)v_address + size - 1;

    if ( va_e < va_s)
    {
        return -1;
    }

    va_s >>= ARCH_SECTION_SHIFT;
    va_e >>= ARCH_SECTION_SHIFT;

    if (va_s == 0)
    {
        return -1;
    }

    for (l1_off = va_s; l1_off <= va_e; l1_off++)
    {
        size_t v = vtable[l1_off];

        if (v & ARCH_MMU_USED_MASK)
        {
            return -1;
        }
    }

#ifdef RT_USING_SMART
    rt_ioremap_start = v_address;
    rt_ioremap_size = size;
    rt_mpr_start = rt_ioremap_start - rt_mpr_size;
#else
    rt_mpr_start = (void *)0 - rt_mpr_size;
#endif

    return 0;
}

int rt_hw_mmu_ioremap_init(rt_aspace_t aspace, void* v_address, size_t size)
{
#ifdef RT_IOREMAP_LATE
    size_t loop_va;
    size_t l1_off;
    size_t *mmu_l1, *mmu_l2;
    size_t sections;

    /* for kernel ioremap */
    if ((size_t)v_address < KERNEL_VADDR_START)
    {
        return -1;
    }
    /* must align to section */
    if ((size_t)v_address & ARCH_SECTION_MASK)
    {
        return -1;
    }
    /* must align to section */
    if (size & ARCH_SECTION_MASK)
    {
        return -1;
    }

    loop_va = (size_t)v_address;
    sections = (size >> ARCH_SECTION_SHIFT);
    while (sections--)
    {
        l1_off = (loop_va >> ARCH_SECTION_SHIFT);
        mmu_l1 =  (size_t*)aspace->page_table + l1_off;

        RT_ASSERT((*mmu_l1 & ARCH_MMU_USED_MASK) == 0);
        mmu_l2 = (size_t*)rt_pages_alloc(0);
        if (mmu_l2)
        {
            rt_memset(mmu_l2, 0, ARCH_PAGE_TBL_SIZE * 2);
            /* cache maintain */
            rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, mmu_l2, ARCH_PAGE_TBL_SIZE);

            *mmu_l1 = (((size_t)mmu_l2 + PV_OFFSET) | 0x1);
            /* cache maintain */
            rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, mmu_l1, 4);
        }
        else
        {
            /* error */
            return -1;
        }

        loop_va += ARCH_SECTION_SIZE;
    }
#endif

    return 0;
}




static void _kenrel_unmap_4K(unsigned long *lv0_tbl, void *v_addr)
{
    size_t loop_va = (size_t)v_addr & ~ARCH_PAGE_MASK;
    size_t l1_off, l2_off;
    size_t *mmu_l1, *mmu_l2;

    l1_off = (loop_va >> ARCH_SECTION_SHIFT);

    l2_off = ((loop_va & ARCH_SECTION_MASK) >> ARCH_PAGE_SHIFT);
    mmu_l1 = (size_t *)lv0_tbl + l1_off;

    if (*mmu_l1 & ARCH_MMU_USED_MASK)
    {
        mmu_l2 = (size_t *)((*mmu_l1 & ~ARCH_PAGE_TBL_MASK) - PV_OFFSET);
    }
    else
    {
        return;
    }

    if (*(mmu_l2 + l2_off) & ARCH_MMU_USED_MASK)
    {
        *(mmu_l2 + l2_off) = 0;
        /* cache maintain */
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, mmu_l2 + l2_off, 4);

        if (rt_pages_free(mmu_l2, 0))
        {
            *mmu_l1 = 0;
            rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, mmu_l1, 4);
        }
    }
    loop_va += ARCH_PAGE_SIZE;
}

static int _kenrel_map_4K(unsigned long *lv0_tbl, void *v_addr, void *p_addr,
                          size_t attr)
{
    size_t loop_va = (size_t)v_addr & ~ARCH_PAGE_MASK;
    size_t loop_pa = (size_t)p_addr & ~ARCH_PAGE_MASK;
    size_t l1_off, l2_off;
    size_t *mmu_l1, *mmu_l2;

    l1_off = (loop_va >> ARCH_SECTION_SHIFT);
    l2_off = ((loop_va & ARCH_SECTION_MASK) >> ARCH_PAGE_SHIFT);
    mmu_l1 = (size_t *)lv0_tbl + l1_off;

    if (*mmu_l1 & ARCH_MMU_USED_MASK)
    {
        mmu_l2 = (size_t *)((*mmu_l1 & ~ARCH_PAGE_TBL_MASK) - PV_OFFSET);
        rt_page_ref_inc(mmu_l2, 0);
    }
    else
    {
        mmu_l2 = (size_t *)rt_pages_alloc(0);
        if (mmu_l2)
        {
            rt_memset(mmu_l2, 0, ARCH_PAGE_TBL_SIZE * 2);
            /* cache maintain */
            rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, mmu_l2, ARCH_PAGE_TBL_SIZE);

            *mmu_l1 = (((size_t)mmu_l2 + PV_OFFSET) | 0x1);
            /* cache maintain */
            rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, mmu_l1, 4);
        }
        else
        {
            /* error, quit */
            return -1;
        }
    }

    *(mmu_l2 + l2_off) = (loop_pa | attr);
    /* cache maintain */
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, mmu_l2 + l2_off, 4);

    loop_va += ARCH_PAGE_SIZE;
    loop_pa += ARCH_PAGE_SIZE;

    return 0;
}

void *rt_hw_mmu_map(rt_aspace_t aspace, void *v_addr, void *p_addr, size_t size,
                    size_t attr)
{
    int ret = -1;
    void *unmap_va = v_addr;
    size_t npages = size >> ARCH_PAGE_SHIFT;

    // TODO trying with HUGEPAGE here
    while (npages--)
    {
        ret = _kenrel_map_4K(aspace->page_table, v_addr, p_addr, attr);
        if (ret != 0)
        {
            /* error, undo map */
            while (unmap_va != v_addr)
            {
                rt_enter_critical();
                _kenrel_unmap_4K(aspace->page_table, (void *)unmap_va);
                rt_exit_critical();

                unmap_va += ARCH_PAGE_SIZE;
            }
            break;
        }
        v_addr += ARCH_PAGE_SIZE;
        p_addr += ARCH_PAGE_SIZE;
    }

    if (ret == 0)
    {
        return v_addr;
    }

    return NULL;
}

void rt_hw_mmu_unmap(rt_aspace_t aspace, void *v_addr, size_t size)
{
    // caller guarantee that v_addr & size are page aligned
    size_t npages = size >> ARCH_PAGE_SHIFT;

    if (!aspace->page_table)
    {
        return;
    }

    while (npages--)
    {
        rt_enter_critical();
        _kenrel_unmap_4K(aspace->page_table, v_addr);
        rt_exit_critical();

        v_addr += ARCH_PAGE_SIZE;
    }
}

void rt_hw_aspace_switch(rt_aspace_t aspace)
{
    if (aspace != &rt_kernel_space)
    {
        void *pgtbl = aspace->page_table;
        pgtbl = rt_kmem_v2p(pgtbl);

        rt_hw_mmu_switch(pgtbl);

        rt_hw_tlb_invalidate_all_local();
    }
}

void init_mm_setup(unsigned int *mtbl, unsigned int size, unsigned int pv_off)
{
    unsigned int va;

    for (va = 0; va < 0x1000; va++)
    {
        unsigned int vaddr = (va << 20);

        if (vaddr >= KERNEL_VADDR_START && vaddr - KERNEL_VADDR_START < size)
        {
            mtbl[va] = ((va << 20) + pv_off) | NORMAL_MEM;
        }
        else if (vaddr >= (KERNEL_VADDR_START + pv_off) && vaddr - (KERNEL_VADDR_START + pv_off) < size)
        {
            mtbl[va] = (va << 20) | NORMAL_MEM;
        }
        else
        {
            mtbl[va] = 0;
        }
    }
}

void *rt_hw_mmu_v2p(rt_aspace_t aspace, void* v_addr)
{
    size_t l1_off, l2_off;
    size_t *mmu_l1, *mmu_l2;
    size_t tmp;
    size_t pa;

    l1_off = (size_t)v_addr >> ARCH_SECTION_SHIFT;

    RT_ASSERT(aspace);

    mmu_l1 =  (size_t*)aspace->page_table + l1_off;

    tmp = *mmu_l1;

    switch (tmp & ARCH_MMU_USED_MASK)
    {
        case 0: /* not used */
            break;
        case 1: /* page table */
            mmu_l2 = (size_t *)((tmp & ~ARCH_PAGE_TBL_MASK) - PV_OFFSET);
            l2_off = (((size_t)v_addr & ARCH_SECTION_MASK) >> ARCH_PAGE_SHIFT);
            pa = *(mmu_l2 + l2_off);
            if (pa & ARCH_MMU_USED_MASK)
            {
                if ((pa & ARCH_MMU_USED_MASK) == 1)
                {
                    /* large page, not support */
                    break;
                }
                pa &= ~(ARCH_PAGE_MASK);
                pa += ((size_t)v_addr & ARCH_PAGE_MASK);
                return (void*)pa;
            }
            break;
        case 2:
        case 3:
            /* section */
            if (tmp & ARCH_TYPE_SUPERSECTION)
            {
                /* super section, not support */
                break;
            }
            pa = (tmp & ~ARCH_SECTION_MASK);
            pa += ((size_t)v_addr & ARCH_SECTION_MASK);
            return (void*)pa;
    }
    return ARCH_MAP_FAILED;
}

int rt_hw_mmu_control(struct rt_aspace *aspace, void *vaddr, size_t size,
                      enum rt_mmu_cntl cmd)
{
    return -RT_ENOSYS;
}
