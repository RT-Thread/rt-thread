/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-01-10     bernard      porting to AM1808
 * 2020-07-26     lizhirui     porting to ls2k
 */

#include <rtthread.h>
#include <rthw.h>
#include <board.h>

#include "cache.h"
#include "mips_mmu.h"
#include "mmu.h"

void *current_mmu_table = RT_NULL;

void *mmu_table_get()
{
    return current_mmu_table;
}

void switch_mmu(void *mmu_table)
{
    current_mmu_table = mmu_table;

    mmu_clear_tlb();
    mmu_clear_itlb();
}

/* dump 2nd level page table */
void rt_hw_cpu_dump_page_table_2nd(rt_uint32_t *ptb)
{
    int i;
    int fcnt = 0;

    for (i = 0; i < 256; i++)
    {
        rt_uint32_t pte2 = ptb[i];
        if ((pte2 & 0x3) == 0)
        {
            if (fcnt == 0)
                rt_kprintf("    ");
            rt_kprintf("%04x: ", i);
            fcnt++;
            if (fcnt == 16)
            {
                rt_kprintf("fault\n");
                fcnt = 0;
            }
            continue;
        }
        if (fcnt != 0)
        {
            rt_kprintf("fault\n");
            fcnt = 0;
        }

        rt_kprintf("    %04x: %x: ", i, pte2);
        if ((pte2 & 0x3) == 0x1)
        {
            rt_kprintf("L,ap:%x,xn:%d,texcb:%02x\n",
                       ((pte2 >> 7) | (pte2 >> 4))& 0xf,
                       (pte2 >> 15) & 0x1,
                       ((pte2 >> 10) | (pte2 >> 2)) & 0x1f);
        }
        else
        {
            rt_kprintf("S,ap:%x,xn:%d,texcb:%02x\n",
                       ((pte2 >> 7) | (pte2 >> 4))& 0xf, pte2 & 0x1,
                       ((pte2 >> 4) | (pte2 >> 2)) & 0x1f);
        }
    }
}

void rt_hw_cpu_dump_page_table(rt_uint32_t *ptb)
{
    int i;
    int fcnt = 0;

    rt_kprintf("page table@%p\n", ptb);
    for (i = 0; i < 1024*4; i++)
    {
        rt_uint32_t pte1 = ptb[i];
        if ((pte1 & 0x3) == 0)
        {
            rt_kprintf("%03x: ", i);
            fcnt++;
            if (fcnt == 16)
            {
                rt_kprintf("fault\n");
                fcnt = 0;
            }
            continue;
        }
        if (fcnt != 0)
        {
            rt_kprintf("fault\n");
            fcnt = 0;
        }

        rt_kprintf("%03x: %08x: ", i, pte1);
        if ((pte1 & 0x3) == 0x3)
        {
            rt_kprintf("LPAE\n");
        }
        else if ((pte1 & 0x3) == 0x1)
        {
            rt_kprintf("pte,ns:%d,domain:%d\n",
                       (pte1 >> 3) & 0x1, (pte1 >> 5) & 0xf);
            /*
             *rt_hw_cpu_dump_page_table_2nd((void*)((pte1 & 0xfffffc000)
             *                               - 0x80000000 + 0xC0000000));
             */
        }
        else if (pte1 & (1 << 18))
        {
            rt_kprintf("super section,ns:%d,ap:%x,xn:%d,texcb:%02x\n",
                       (pte1 >> 19) & 0x1,
                       ((pte1 >> 13) | (pte1 >> 10))& 0xf,
                       (pte1 >> 4) & 0x1,
                       ((pte1 >> 10) | (pte1 >> 2)) & 0x1f);
        }
        else
        {
            rt_kprintf("section,ns:%d,ap:%x,"
                       "xn:%d,texcb:%02x,domain:%d\n",
                       (pte1 >> 19) & 0x1,
                       ((pte1 >> 13) | (pte1 >> 10))& 0xf,
                       (pte1 >> 4) & 0x1,
                       (((pte1 & (0x7 << 12)) >> 10) |
                        ((pte1 &        0x0c) >>  2)) & 0x1f,
                       (pte1 >> 5) & 0xf);
        }
    }
}

/* level1 page table, each entry for 1MB memory. */
volatile unsigned long MMUTable[4*1024] __attribute__((aligned(16*1024)));
void rt_hw_mmu_setmtt(rt_uint32_t vaddrStart,
                      rt_uint32_t vaddrEnd,
                      rt_uint32_t paddrStart,
                      rt_uint32_t attr)
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

unsigned long rt_hw_set_domain_register(unsigned long domain_val)
{
    unsigned long old_domain;

    //asm volatile ("mrc p15, 0, %0, c3, c0\n" : "=r" (old_domain));
    //asm volatile ("mcr p15, 0, %0, c3, c0\n" : :"r" (domain_val) : "memory");

    return old_domain;
}

void rt_hw_cpu_dcache_clean(void *addr, int size);
void rt_hw_init_mmu_table(struct mem_desc *mdesc, rt_uint32_t size)
{
    /* set page table */
    for(; size > 0; size--)
    {
        rt_hw_mmu_setmtt(mdesc->vaddr_start, mdesc->vaddr_end,
                mdesc->paddr_start, mdesc->attr);
        mdesc++;
    }
    rt_hw_cpu_dcache_clean((void*)MMUTable, sizeof MMUTable);
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

/*
 mem map
*/

void rt_hw_cpu_dcache_clean(void *addr, int size);

int rt_hw_mmu_map_init(rt_mmu_info *mmu_info, void* v_address, size_t size, size_t *vtable, size_t pv_off)
{
    size_t l1_off, va_s, va_e;
    rt_base_t level;

    if (!mmu_info || !vtable)
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

    level = rt_hw_interrupt_disable();

    for (l1_off = va_s; l1_off <= va_e; l1_off++)
    {
        size_t v = vtable[l1_off];

        if (v & ARCH_MMU_USED_MASK)
        {
            rt_kprintf("Error:vtable[%d] = 0x%p(is not zero),va_s = 0x%p,va_e = 0x%p!\n",l1_off,v,va_s,va_e);
            rt_hw_interrupt_enable(level);
            return -1;
        }
    }

    mmu_info->vtable = vtable;
    mmu_info->vstart = va_s;
    mmu_info->vend = va_e;
    mmu_info->pv_off = pv_off;

    rt_hw_interrupt_enable(level);

    return 0;
}

static size_t find_vaddr(rt_mmu_info *mmu_info, int pages)
{
    size_t l1_off, l2_off;
    size_t *mmu_l1, *mmu_l2;
    size_t find_off = 0;
    size_t find_va = 0;
    int n = 0;

    if (!pages)
    {
        return 0;
    }

    if (!mmu_info)
    {
        return 0;
    }

    for (l1_off = mmu_info->vstart; l1_off <= mmu_info->vend; l1_off++)
    {
        mmu_l1 =  (size_t*)mmu_info->vtable + l1_off;
        if (*mmu_l1 & ARCH_MMU_USED_MASK)
        {
            mmu_l2 = (size_t *)((*mmu_l1 & ~ARCH_PAGE_TBL_MASK) - mmu_info->pv_off);
            for (l2_off = 0; l2_off < (ARCH_SECTION_SIZE/ARCH_PAGE_SIZE); l2_off++)
            {
                if (*(mmu_l2 + l2_off) & ARCH_MMU_USED_MASK)
                {
                    /* in use */
                    n = 0;
                }
                else
                {
                    if (!n)
                    {
                        find_va = l1_off;
                        find_off = l2_off;
                    }
                    n++;
                    if (n >= pages)
                    {
                        return (find_va << ARCH_SECTION_SHIFT) + (find_off << ARCH_PAGE_SHIFT);
                    }
                }
            }
        }
        else
        {
            if (!n)
            {
                find_va = l1_off;
                find_off = 0;
            }
            n += (ARCH_SECTION_SIZE/ARCH_PAGE_SIZE);
            if (n >= pages)
            {
                return (find_va << ARCH_SECTION_SHIFT) + (find_off << ARCH_PAGE_SHIFT);
            }
        }
    }
    return 0;
}

#ifdef RT_USING_USERSPACE
static int check_vaddr(rt_mmu_info *mmu_info, void *va, int pages)
{
    size_t loop_va = (size_t)va & ~ARCH_PAGE_MASK;
    size_t l1_off, l2_off;
    size_t *mmu_l1, *mmu_l2;

    if (!pages)
    {
        return -1;
    }

    if (!mmu_info)
    {
        return -1;
    }

    while (pages--)
    {
        l1_off = (loop_va >> ARCH_SECTION_SHIFT);
        l2_off = ((loop_va & ARCH_SECTION_MASK) >> ARCH_PAGE_SHIFT);
        mmu_l1 =  (size_t*)mmu_info->vtable + l1_off;

        if (*mmu_l1 & ARCH_MMU_USED_MASK)
        {
            mmu_l2 = (size_t *)((*mmu_l1 & ~ARCH_PAGE_TBL_MASK) - mmu_info->pv_off);
            if (*(mmu_l2 + l2_off) & ARCH_MMU_USED_MASK)
            {
                return -1;
            }
        }
        loop_va += ARCH_PAGE_SIZE;
    }
    return 0;
}
#endif

static void __rt_hw_mmu_unmap(rt_mmu_info *mmu_info, void* v_addr, size_t npages)
{
    size_t loop_va = (size_t)v_addr & ~ARCH_PAGE_MASK;
    size_t l1_off, l2_off;
    size_t *mmu_l1, *mmu_l2;
    size_t *ref_cnt;

    if (!mmu_info)
    {
        return;
    }

    while (npages--)
    {
        l1_off = (loop_va >> ARCH_SECTION_SHIFT);
        if (l1_off < mmu_info->vstart || l1_off > mmu_info->vend)
        {
            return;
        }

        l2_off = ((loop_va & ARCH_SECTION_MASK) >> ARCH_PAGE_SHIFT);
        mmu_l1 =  (size_t*)mmu_info->vtable + l1_off;

        if (*mmu_l1 & ARCH_MMU_USED_MASK)
        {
            mmu_l2 = (size_t *)((*mmu_l1 & ~ARCH_PAGE_TBL_MASK) - mmu_info->pv_off);
        }
        else
        {
            return;
        }

        if (*(mmu_l2 + l2_off) & ARCH_MMU_USED_MASK) 
        {
            *(mmu_l2 + l2_off) = 0;
            /* cache maintain */
            rt_hw_cpu_dcache_clean(mmu_l2 + l2_off, 4);

            ref_cnt = mmu_l2 + (ARCH_SECTION_SIZE/ARCH_PAGE_SIZE);
            (*ref_cnt)--;
            if (!*ref_cnt)
            {
#ifdef RT_USING_USERSPACE
                rt_pages_free(mmu_l2, 0);
#else
                rt_free_align(mmu_l2);
#endif
                *mmu_l1 = 0;

                /* cache maintain */
                rt_hw_cpu_dcache_clean(mmu_l1, 4);
            }
        }
        loop_va += ARCH_PAGE_SIZE;
    }
}

static int __rt_hw_mmu_map(rt_mmu_info *mmu_info, void* v_addr, void* p_addr, size_t npages, size_t attr)
{
    size_t loop_va = (size_t)v_addr & ~ARCH_PAGE_MASK;
    size_t loop_pa = (size_t)p_addr & ~ARCH_PAGE_MASK;
    size_t l1_off, l2_off;
    size_t *mmu_l1, *mmu_l2;
    size_t *ref_cnt;

    if (!mmu_info)
    {
        return -1;
    }

    while (npages--)
    {
        l1_off = (loop_va >> ARCH_SECTION_SHIFT);
        l2_off = ((loop_va & ARCH_SECTION_MASK) >> ARCH_PAGE_SHIFT);
        mmu_l1 =  (size_t*)mmu_info->vtable + l1_off;

        if (*mmu_l1 & ARCH_MMU_USED_MASK)
        {
            mmu_l2 = (size_t *)((*mmu_l1 & ~ARCH_PAGE_TBL_MASK) - mmu_info->pv_off);
        }
        else
        {
#ifdef RT_USING_USERSPACE
            mmu_l2 = (size_t*)rt_pages_alloc(0);
#else
            mmu_l2 = (size_t*)rt_malloc_align(ARCH_PAGE_TBL_SIZE * 2, ARCH_PAGE_TBL_SIZE);
#endif
            if (mmu_l2)
            {
                rt_memset(mmu_l2, 0, ARCH_PAGE_TBL_SIZE * 2);
                /* cache maintain */
                rt_hw_cpu_dcache_clean(mmu_l2, ARCH_PAGE_TBL_SIZE);

                *mmu_l1 = (((size_t)mmu_l2 + mmu_info->pv_off) | 0x1);
                /* cache maintain */
                rt_hw_cpu_dcache_clean(mmu_l1, 4);
            }
            else
            {
                /* error, unmap and quit */
                __rt_hw_mmu_unmap(mmu_info, v_addr, npages);
                return -1;
            }
        }

        ref_cnt = mmu_l2 + (ARCH_SECTION_SIZE/ARCH_PAGE_SIZE);
        (*ref_cnt)++;

        *(mmu_l2 + l2_off) = (loop_pa | attr);
        /* cache maintain */
        rt_hw_cpu_dcache_clean(mmu_l2 + l2_off, 4);

        loop_va += ARCH_PAGE_SIZE;
        loop_pa += ARCH_PAGE_SIZE;
    }
    return 0;
}

static void rt_hw_cpu_tlb_invalidate(void)
{
    mmu_clear_tlb();
    mmu_clear_itlb();
}

#ifdef RT_USING_USERSPACE
void *_rt_hw_mmu_map(rt_mmu_info *mmu_info, void *v_addr, void* p_addr, size_t size, size_t attr)
{
    size_t pa_s, pa_e;
    size_t vaddr;
    int pages;
    int ret;

    if (!size)
    {
        return 0;
    }
    pa_s = (size_t)p_addr;
    pa_e = (size_t)p_addr + size - 1;
    pa_s >>= ARCH_PAGE_SHIFT;
    pa_e >>= ARCH_PAGE_SHIFT;
    pages = pa_e - pa_s + 1;
    if (v_addr)
    {
        vaddr = (size_t)v_addr;
        pa_s = (size_t)p_addr;
        if ((vaddr & ARCH_PAGE_MASK) != (pa_s & ARCH_PAGE_MASK))
        {
            return 0;
        }
        vaddr &= ~ARCH_PAGE_MASK;
        if (check_vaddr(mmu_info, (void*)vaddr, pages) != 0)
        {
            return 0;
        }
    }
    else
    {
        vaddr = find_vaddr(mmu_info, pages);
    }
    if (vaddr) {
        ret = __rt_hw_mmu_map(mmu_info, (void*)vaddr, p_addr, pages, attr);
        if (ret == 0)
        {
            rt_hw_cpu_tlb_invalidate();
            return (void*)(vaddr + ((size_t)p_addr & ARCH_PAGE_MASK));
        }
    }
    return 0;
}
#else
void *_rt_hw_mmu_map(rt_mmu_info *mmu_info, void* p_addr, size_t size, size_t attr)
{
    size_t pa_s, pa_e;
    size_t vaddr;
    int pages;
    int ret;

    pa_s = (size_t)p_addr;
    pa_e = (size_t)p_addr + size - 1;
    pa_s >>= ARCH_PAGE_SHIFT;
    pa_e >>= ARCH_PAGE_SHIFT;
    pages = pa_e - pa_s + 1;
    vaddr = find_vaddr(mmu_info, pages);
    if (vaddr) {
        ret = __rt_hw_mmu_map(mmu_info, (void*)vaddr, p_addr, pages, attr);
        if (ret == 0)
        {
            rt_hw_cpu_tlb_invalidate();
            return (void*)(vaddr + ((size_t)p_addr & ARCH_PAGE_MASK));
        }
    }
    return 0;
}
#endif

#ifdef RT_USING_USERSPACE
static int __rt_hw_mmu_map_auto(rt_mmu_info *mmu_info, void* v_addr, size_t npages, size_t attr)
{
    size_t loop_va = (size_t)v_addr & ~ARCH_PAGE_MASK;
    size_t loop_pa;
    size_t l1_off, l2_off;
    size_t *mmu_l1, *mmu_l2;
    size_t *ref_cnt;

    if (!mmu_info)
    {
        return -1;
    }

    while (npages--)
    {
        loop_pa = (size_t)rt_pages_alloc(0) + mmu_info->pv_off;
        if (!loop_pa)
            goto err;

        //rt_kprintf("vaddr = %08x is mapped to paddr = %08x\n",v_addr,loop_pa);
        l1_off = (loop_va >> ARCH_SECTION_SHIFT);
        l2_off = ((loop_va & ARCH_SECTION_MASK) >> ARCH_PAGE_SHIFT);
        mmu_l1 =  (size_t*)mmu_info->vtable + l1_off;

        if (*mmu_l1 & ARCH_MMU_USED_MASK)
        {
            mmu_l2 = (size_t *)((*mmu_l1 & ~ARCH_PAGE_TBL_MASK) - mmu_info->pv_off);
        }
        else
        {
            //mmu_l2 = (size_t*)rt_malloc_align(ARCH_PAGE_TBL_SIZE * 2, ARCH_PAGE_TBL_SIZE);
            mmu_l2 = (size_t*)rt_pages_alloc(0);
            if (mmu_l2)
            {
                rt_memset(mmu_l2, 0, ARCH_PAGE_TBL_SIZE * 2);
                /* cache maintain */
                rt_hw_cpu_dcache_clean(mmu_l2, ARCH_PAGE_TBL_SIZE);

                *mmu_l1 = (((size_t)mmu_l2 + mmu_info->pv_off) | 0x1);
                /* cache maintain */
                rt_hw_cpu_dcache_clean(mmu_l1, 4);
            }
            else
                goto err;
        }

        ref_cnt = mmu_l2 + (ARCH_SECTION_SIZE/ARCH_PAGE_SIZE);
        (*ref_cnt)++;

        //loop_pa += mmu_info->pv_off;
        *(mmu_l2 + l2_off) = (loop_pa | attr);
        /* cache maintain */
        rt_hw_cpu_dcache_clean(mmu_l2 + l2_off, 4);

        loop_va += ARCH_PAGE_SIZE;
    }
    return 0;
err:
    {
        /* error, unmap and quit */
        int i;
        void *va, *pa;

        va = (void*)((size_t)v_addr & ~ARCH_PAGE_MASK);
        for (i = 0; i < npages; i++)
        {
            pa = rt_hw_mmu_v2p(mmu_info, va);
            pa -= mmu_info->pv_off;
            rt_pages_free(pa, 0);
            va += ARCH_PAGE_SIZE;
        }

        __rt_hw_mmu_unmap(mmu_info, v_addr, npages);
        return -1;
    }
}

void *_rt_hw_mmu_map_auto(rt_mmu_info *mmu_info, void *v_addr, size_t size, size_t attr)
{
    size_t vaddr;
    size_t offset;
    int pages;
    int ret;

    if (!size)
    {
        return 0;
    }
    offset = (size_t)v_addr & ARCH_PAGE_MASK;
    size += (offset + ARCH_PAGE_SIZE - 1);
    pages = (size >> ARCH_PAGE_SHIFT);
    if (v_addr)
    {
        vaddr = (size_t)v_addr;
        vaddr &= ~ARCH_PAGE_MASK;
        if (check_vaddr(mmu_info, (void*)vaddr, pages) != 0)
        {
            return 0;
        }
    }
    else
    {
        vaddr = find_vaddr(mmu_info, pages);
    }
    if (vaddr) {
        ret = __rt_hw_mmu_map_auto(mmu_info, (void*)vaddr, pages, attr);
        if (ret == 0)
        {
            rt_hw_cpu_tlb_invalidate();
            return (void*)vaddr + offset;
        }
    }
    return 0;
}
#endif

void _rt_hw_mmu_unmap(rt_mmu_info *mmu_info, void* v_addr, size_t size)
{
    size_t va_s, va_e;
    int pages;

    va_s = (size_t)v_addr;
    va_e = (size_t)v_addr + size - 1;
    va_s >>= ARCH_PAGE_SHIFT;
    va_e >>= ARCH_PAGE_SHIFT;
    pages = va_e - va_s + 1;
    __rt_hw_mmu_unmap(mmu_info, v_addr, pages);
    rt_hw_cpu_tlb_invalidate();
}

//va --> pa
void *rt_hw_kernel_virt_to_phys(void *v_addr, size_t size)
{
    void *p_addr = 0;

    return p_addr;
}

//pa --> va
void *rt_hw_kernel_phys_to_virt(void *p_addr, size_t size)
{   
    void *v_addr = 0;

    #ifdef RT_USING_USERSPACE
    extern rt_mmu_info mmu_info;
    v_addr = rt_hw_mmu_map(&mmu_info, 0, p_addr, size, MMU_MAP_K_RW);
    #else
    v_addr = p_addr;
    #endif

    return v_addr;
}

#ifdef RT_USING_USERSPACE
void *rt_hw_mmu_map(rt_mmu_info *mmu_info, void *v_addr, void* p_addr, size_t size, size_t attr)
{
    void *ret;
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    ret = _rt_hw_mmu_map(mmu_info, v_addr, p_addr, size, attr);
    rt_hw_interrupt_enable(level);
    return ret;
}

void *rt_hw_mmu_map_auto(rt_mmu_info *mmu_info, void *v_addr, size_t size, size_t attr)
{
    void *ret;
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    ret = _rt_hw_mmu_map_auto(mmu_info, v_addr, size, attr);
    rt_hw_interrupt_enable(level);
    return ret;
}
#endif

void rt_hw_mmu_unmap(rt_mmu_info *mmu_info, void* v_addr, size_t size)
{
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    _rt_hw_mmu_unmap(mmu_info, v_addr, size);
    rt_hw_interrupt_enable(level);
}

void *_rt_hw_mmu_v2p(rt_mmu_info *mmu_info, void* v_addr)
{
    size_t l1_off, l2_off;
    size_t *mmu_l1, *mmu_l2;
    size_t tmp;
    size_t pa;

    l1_off = (size_t)v_addr >> ARCH_SECTION_SHIFT;

    if (!mmu_info)
    {
        return (void*)0;
    }

    mmu_l1 =  (size_t*)mmu_info->vtable + l1_off;

    tmp = *mmu_l1;

    switch (tmp & ARCH_MMU_USED_MASK)
    {
        case 0: /* not used */
            break;
        case 1: /* page table */
            mmu_l2 = (size_t *)((tmp & ~ARCH_PAGE_TBL_MASK) - mmu_info->pv_off);
            l2_off = (((size_t)v_addr & ARCH_SECTION_MASK) >> ARCH_PAGE_SHIFT);
            pa = *(mmu_l2 + l2_off);
            if (pa & ARCH_MMU_USED_MASK)
            {
                if ((pa & ARCH_MMU_USED_MASK) == 1)
                {
                    /* lage page, not support */
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
    return (void*)0;
}

void *rt_hw_mmu_v2p(rt_mmu_info *mmu_info, void* v_addr)
{
    void *ret;
    rt_base_t level;

    level = rt_hw_interrupt_disable();
    ret = _rt_hw_mmu_v2p(mmu_info, v_addr);
    rt_hw_interrupt_enable(level);
    return ret;
}

#ifdef RT_USING_USERSPACE
void init_mm_setup(unsigned int *mtbl, unsigned int size, unsigned int pv_off) {
    unsigned int va;

    for (va = 0; va < 0x1000; va++) {
        unsigned int vaddr = (va << 20);
        if (vaddr >= KERNEL_VADDR_START && vaddr - KERNEL_VADDR_START < size) {
            mtbl[va] = ((va << 20) + pv_off) | NORMAL_MEM;
        } else if (vaddr >= (KERNEL_VADDR_START + pv_off) && vaddr - (KERNEL_VADDR_START + pv_off) < size) {
            mtbl[va] = (va << 20) | NORMAL_MEM;
        } else {
            mtbl[va] = 0;
        }
    }
}
#endif
