/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2012-01-10     bernard      porting to AM1808
 * 2021-11-28     GuEe-GUI     first version
 * 2022-12-10     WangXiaoyao  porting to MM
 */

#define DBG_TAG "hw.mmu"
#define DBG_LVL DBG_LOG
#include <rtdbg.h>

#include <rthw.h>
#include <rtthread.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define __MMU_INTERNAL

#include "mm_aspace.h"
#include "mm_page.h"
#include "mmu.h"
#include "tlb.h"

#include "ioremap.h"
#ifdef RT_USING_SMART
#include <lwp_mm.h>
#endif

#define TCR_CONFIG_TBI0     rt_hw_mmu_config_tbi(0)
#define TCR_CONFIG_TBI1     rt_hw_mmu_config_tbi(1)

#define MMU_LEVEL_MASK   0x1ffUL
#define MMU_LEVEL_SHIFT  9
#define MMU_ADDRESS_BITS 39
#define MMU_ADDRESS_MASK 0x0000fffffffff000UL
#define MMU_ATTRIB_MASK  0xfff0000000000ffcUL

#define MMU_TYPE_MASK  3UL
#define MMU_TYPE_USED  1UL
#define MMU_TYPE_BLOCK 1UL
#define MMU_TYPE_TABLE 3UL
#define MMU_TYPE_PAGE  3UL

#define MMU_TBL_BLOCK_2M_LEVEL 2
#define MMU_TBL_PAGE_4k_LEVEL  3
#define MMU_TBL_LEVEL_NR       4

#ifndef KERNEL_VADDR_START
#define KERNEL_VADDR_START ARCH_TEXT_OFFSET
#endif

volatile unsigned long MMUTable[512] __attribute__((aligned(4 * 1024)));

struct mmu_level_info
{
    unsigned long *pos;
    void *page;
};

static void _kenrel_unmap_4K(unsigned long *lv0_tbl, void *v_addr)
{
    int level;
    unsigned long va = (unsigned long)v_addr;
    unsigned long *cur_lv_tbl = lv0_tbl;
    unsigned long page;
    unsigned long off;
    struct mmu_level_info level_info[4];
    int ref;
    int level_shift = MMU_ADDRESS_BITS;
    unsigned long *pos;

    rt_memset(level_info, 0, sizeof level_info);
    for (level = 0; level < MMU_TBL_LEVEL_NR; level++)
    {
        off = (va >> level_shift);
        off &= MMU_LEVEL_MASK;
        page = cur_lv_tbl[off];
        if (!(page & MMU_TYPE_USED))
        {
            break;
        }
        if ((page & MMU_TYPE_MASK) == MMU_TYPE_BLOCK)
        {
            break;
        }
        /* next table entry in current level */
        level_info[level].pos = cur_lv_tbl + off;
        cur_lv_tbl = (unsigned long *)(page & MMU_ADDRESS_MASK);
        cur_lv_tbl = (unsigned long *)((unsigned long)cur_lv_tbl - PV_OFFSET);
        level_info[level].page = cur_lv_tbl;
        level_shift -= MMU_LEVEL_SHIFT;
    }

    level = MMU_TBL_PAGE_4k_LEVEL;
    pos = level_info[level].pos;
    if (pos)
    {
        *pos = (unsigned long)RT_NULL;
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, pos, sizeof(void *));
    }
    level--;

    while (level >= 0)
    {
        pos = level_info[level].pos;
        if (pos)
        {
            void *cur_page = level_info[level].page;
            ref = rt_page_ref_get(cur_page, 0);
            if (ref == 1)
            {
                *pos = (unsigned long)RT_NULL;
                rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, pos, sizeof(void *));
            }
            rt_pages_free(cur_page, 0);
        }
        else
        {
            break;
        }
        level--;
    }

    return;
}

static int _kernel_map_4K(unsigned long *lv0_tbl, void *vaddr, void *paddr, unsigned long attr)
{
    int ret = 0;
    int level;
    unsigned long *cur_lv_tbl = lv0_tbl;
    unsigned long page;
    unsigned long off;
    intptr_t va = (intptr_t)vaddr;
    intptr_t pa = (intptr_t)paddr;
    int level_shift = MMU_ADDRESS_BITS;

    if (va & ARCH_PAGE_MASK)
    {
        return MMU_MAP_ERROR_VANOTALIGN;
    }
    if (pa & ARCH_PAGE_MASK)
    {
        return MMU_MAP_ERROR_PANOTALIGN;
    }
    for (level = 0; level < MMU_TBL_PAGE_4k_LEVEL; level++)
    {
        off = (va >> level_shift);
        off &= MMU_LEVEL_MASK;
        if (!(cur_lv_tbl[off] & MMU_TYPE_USED))
        {
            page = (unsigned long)rt_pages_alloc_ext(0, PAGE_ANY_AVAILABLE);
            if (!page)
            {
                ret = MMU_MAP_ERROR_NOPAGE;
                goto err;
            }
            rt_memset((void *)page, 0, ARCH_PAGE_SIZE);
            rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, (void *)page, ARCH_PAGE_SIZE);
            cur_lv_tbl[off] = (page + PV_OFFSET) | MMU_TYPE_TABLE;
            rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, cur_lv_tbl + off, sizeof(void *));
        }
        else
        {
            page = cur_lv_tbl[off];
            page &= MMU_ADDRESS_MASK;
            /* page to va */
            page -= PV_OFFSET;
            rt_page_ref_inc((void *)page, 0);
        }
        page = cur_lv_tbl[off];
        if ((page & MMU_TYPE_MASK) == MMU_TYPE_BLOCK)
        {
            /* is block! error! */
            ret = MMU_MAP_ERROR_CONFLICT;
            goto err;
        }
        cur_lv_tbl = (unsigned long *)(page & MMU_ADDRESS_MASK);
        cur_lv_tbl = (unsigned long *)((unsigned long)cur_lv_tbl - PV_OFFSET);
        level_shift -= MMU_LEVEL_SHIFT;
    }
    /* now is level page */
    attr &= MMU_ATTRIB_MASK;
    pa |= (attr | MMU_TYPE_PAGE); /* page */
    off = (va >> ARCH_PAGE_SHIFT);
    off &= MMU_LEVEL_MASK;
    cur_lv_tbl[off] = pa; /* page */
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, cur_lv_tbl + off, sizeof(void *));
    return ret;
err:
    _kenrel_unmap_4K(lv0_tbl, (void *)va);
    return ret;
}

static int _kernel_map_2M(unsigned long *lv0_tbl, void *vaddr, void *paddr, unsigned long attr)
{
    int ret = 0;
    int level;
    unsigned long *cur_lv_tbl = lv0_tbl;
    unsigned long page;
    unsigned long off;
    unsigned long va = (unsigned long)vaddr;
    unsigned long pa = (unsigned long)paddr;

    int level_shift = MMU_ADDRESS_BITS;

    if (va & ARCH_SECTION_MASK)
    {
        return MMU_MAP_ERROR_VANOTALIGN;
    }
    if (pa & ARCH_PAGE_MASK)
    {
        return MMU_MAP_ERROR_PANOTALIGN;
    }
    for (level = 0; level < MMU_TBL_BLOCK_2M_LEVEL; level++)
    {
        off = (va >> level_shift);
        off &= MMU_LEVEL_MASK;
        if (!(cur_lv_tbl[off] & MMU_TYPE_USED))
        {
            page = (unsigned long)rt_pages_alloc_ext(0, PAGE_ANY_AVAILABLE);
            if (!page)
            {
                ret = MMU_MAP_ERROR_NOPAGE;
                goto err;
            }
            rt_memset((char *)page, 0, ARCH_PAGE_SIZE);
            rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, (void *)page, ARCH_PAGE_SIZE);
            cur_lv_tbl[off] = (page + PV_OFFSET) | MMU_TYPE_TABLE;
            rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, cur_lv_tbl + off, sizeof(void *));
        }
        else
        {
            page = cur_lv_tbl[off];
            page &= MMU_ADDRESS_MASK;
            /* page to va */
            page -= PV_OFFSET;
            rt_page_ref_inc((void *)page, 0);
        }
        page = cur_lv_tbl[off];
        if ((page & MMU_TYPE_MASK) == MMU_TYPE_BLOCK)
        {
            /* is block! error! */
            ret = MMU_MAP_ERROR_CONFLICT;
            goto err;
        }
        cur_lv_tbl = (unsigned long *)(page & MMU_ADDRESS_MASK);
        cur_lv_tbl = (unsigned long *)((unsigned long)cur_lv_tbl - PV_OFFSET);
        level_shift -= MMU_LEVEL_SHIFT;
    }
    /* now is level page */
    attr &= MMU_ATTRIB_MASK;
    pa |= (attr | MMU_TYPE_BLOCK); /* block */
    off = (va >> ARCH_SECTION_SHIFT);
    off &= MMU_LEVEL_MASK;
    cur_lv_tbl[off] = pa;
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, cur_lv_tbl + off, sizeof(void *));
    return ret;
err:
    _kenrel_unmap_4K(lv0_tbl, (void *)va);
    return ret;
}

void *rt_hw_mmu_map(rt_aspace_t aspace, void *v_addr, void *p_addr, size_t size,
                    size_t attr)
{
    int ret = -1;

    void *unmap_va = v_addr;
    size_t npages;
    size_t stride;
    int (*mapper)(unsigned long *lv0_tbl, void *vaddr, void *paddr, unsigned long attr);

    if (((rt_ubase_t)v_addr & ARCH_SECTION_MASK) || (size & ARCH_SECTION_MASK))
    {
        /* legacy 4k mapping */
        npages = size >> ARCH_PAGE_SHIFT;
        stride = ARCH_PAGE_SIZE;
        mapper = _kernel_map_4K;
    }
    else
    {
        /* 2m huge page */
        npages = size >> ARCH_SECTION_SHIFT;
        stride = ARCH_SECTION_SIZE;
        mapper = _kernel_map_2M;
    }

    while (npages--)
    {
        MM_PGTBL_LOCK(aspace);
        ret = mapper(aspace->page_table, v_addr, p_addr, attr);
        MM_PGTBL_UNLOCK(aspace);

        if (ret != 0)
        {
            /* other types of return value are taken as programming error */
            RT_ASSERT(ret == MMU_MAP_ERROR_NOPAGE);
            /* error, undo map */
            while (unmap_va != v_addr)
            {
                MM_PGTBL_LOCK(aspace);
                _kenrel_unmap_4K(aspace->page_table, (void *)unmap_va);
                MM_PGTBL_UNLOCK(aspace);
                unmap_va = (char *)unmap_va + stride;
            }
            break;
        }
        v_addr = (char *)v_addr + stride;
        p_addr = (char *)p_addr + stride;
    }

    if (ret == 0)
    {
        return unmap_va;
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
        MM_PGTBL_LOCK(aspace);
        if (rt_hw_mmu_v2p(aspace, v_addr) != ARCH_MAP_FAILED)
            _kenrel_unmap_4K(aspace->page_table, v_addr);
        MM_PGTBL_UNLOCK(aspace);
        v_addr = (char *)v_addr + ARCH_PAGE_SIZE;
    }
}

void rt_hw_aspace_switch(rt_aspace_t aspace)
{
    if (aspace != &rt_kernel_space)
    {
        void *pgtbl = aspace->page_table;
        pgtbl = rt_kmem_v2p(pgtbl);
        rt_ubase_t tcr;

        __asm__ volatile("msr ttbr0_el1, %0" ::"r"(pgtbl) : "memory");

        __asm__ volatile("mrs %0, tcr_el1" : "=r"(tcr));
        tcr &= ~(1ul << 7);
        __asm__ volatile("msr tcr_el1, %0\n"
                         "isb" ::"r"(tcr)
                         : "memory");

        rt_hw_tlb_invalidate_all_local();
    }
}

void rt_hw_mmu_ktbl_set(unsigned long tbl)
{
#ifdef RT_USING_SMART
    tbl += PV_OFFSET;
    __asm__ volatile("msr TTBR1_EL1, %0\n dsb sy\nisb" ::"r"(tbl) : "memory");
#else
    __asm__ volatile("msr TTBR0_EL1, %0\n dsb sy\nisb" ::"r"(tbl) : "memory");
#endif
    __asm__ volatile("tlbi vmalle1\n dsb sy\nisb" ::: "memory");
    __asm__ volatile("ic ialluis\n dsb sy\nisb" ::: "memory");
}

/**
 * @brief setup Page Table for kernel space. It's a fixed map
 * and all mappings cannot be changed after initialization.
 *
 * Memory region in struct mem_desc must be page aligned,
 * otherwise is a failure and no report will be
 * returned.
 *
 * @param mmu_info
 * @param mdesc
 * @param desc_nr
 */
void rt_hw_mmu_setup(rt_aspace_t aspace, struct mem_desc *mdesc, int desc_nr)
{
    void *err;
    for (size_t i = 0; i < desc_nr; i++)
    {
        size_t attr;
        switch (mdesc->attr)
        {
        case NORMAL_MEM:
            attr = MMU_MAP_K_RWCB;
            break;
        case NORMAL_NOCACHE_MEM:
            attr = MMU_MAP_K_RWCB;
            break;
        case DEVICE_MEM:
            attr = MMU_MAP_K_DEVICE;
            break;
        default:
            attr = MMU_MAP_K_DEVICE;
        }

        struct rt_mm_va_hint hint = {.flags = MMF_MAP_FIXED,
                                    .limit_start = aspace->start,
                                    .limit_range_size = aspace->size,
                                    .map_size = mdesc->vaddr_end -
                                                mdesc->vaddr_start + 1,
                                    .prefer = (void *)mdesc->vaddr_start};

        if (mdesc->paddr_start == (rt_size_t)ARCH_MAP_FAILED)
            mdesc->paddr_start = mdesc->vaddr_start + PV_OFFSET;
        int retval;
        retval = rt_aspace_map_phy_static(aspace, &mdesc->varea, &hint, attr,
                                 mdesc->paddr_start >> MM_PAGE_SHIFT, &err);
        if (retval)
        {
            LOG_E("%s: map failed with code %d", retval);
            RT_ASSERT(0);
        }
        mdesc++;
    }

    rt_hw_mmu_ktbl_set((unsigned long)rt_kernel_space.page_table);
    rt_page_cleanup();
}

static void _init_region(void *vaddr, size_t size)
{
    rt_ioremap_start = vaddr;
    rt_ioremap_size = size;
    rt_mpr_start = (char *)rt_ioremap_start - rt_mpr_size;
}


/**
 * This function will initialize rt_mmu_info structure.
 *
 * @param mmu_info   rt_mmu_info structure
 * @param v_address  virtual address
 * @param size       map size
 * @param vtable     mmu table
 * @param pv_off     pv offset in kernel space
 *
 * @return 0 on successful and -1 for fail
 */
int rt_hw_mmu_map_init(rt_aspace_t aspace, void *v_address, size_t size,
                       size_t *vtable, size_t pv_off)
{
    size_t va_s, va_e;

    if (!aspace || !vtable)
    {
        return -1;
    }

    va_s = (size_t)v_address;
    va_e = (size_t)v_address + size - 1;

    if (va_e < va_s)
    {
        return -1;
    }

    va_s >>= ARCH_SECTION_SHIFT;
    va_e >>= ARCH_SECTION_SHIFT;

    if (va_s == 0)
    {
        return -1;
    }

    rt_aspace_init(aspace, (void *)KERNEL_VADDR_START, 0 - KERNEL_VADDR_START,
                   vtable);

    _init_region(v_address, size);

    return 0;
}

rt_weak long rt_hw_mmu_config_tbi(int tbi_index)
{
    return 0;
}

/************ setting el1 mmu register**************
  MAIR_EL1
  index 0 : memory outer writeback, write/read alloc
  index 1 : memory nocache
  index 2 : device nGnRnE
 *****************************************************/
void mmu_tcr_init(void)
{
    unsigned long val64;
    unsigned long pa_range;

    val64 = 0x00447fUL;
    __asm__ volatile("msr MAIR_EL1, %0\n dsb sy\n" ::"r"(val64));

    __asm__ volatile ("mrs %0, ID_AA64MMFR0_EL1":"=r"(val64));
    pa_range = val64 & 0xf; /* PARange */

    /* TCR_EL1 */
    val64 = (16UL << 0)                /* t0sz 48bit */
            | (0x0UL << 6)             /* reserved */
            | (0x0UL << 7)             /* epd0 */
            | (0x3UL << 8)             /* t0 wb cacheable */
            | (0x3UL << 10)            /* inner shareable */
            | (0x2UL << 12)            /* t0 outer shareable */
            | (0x0UL << 14)            /* t0 4K */
            | (16UL << 16)             /* t1sz 48bit */
            | (0x0UL << 22)            /* define asid use ttbr0.asid */
            | (0x0UL << 23)            /* epd1 */
            | (0x3UL << 24)            /* t1 inner wb cacheable */
            | (0x3UL << 26)            /* t1 outer wb cacheable */
            | (0x2UL << 28)            /* t1 outer shareable */
            | (0x2UL << 30)            /* t1 4k */
            | (pa_range << 32)         /* PA range */
            | (0x0UL << 35)            /* reserved */
            | (0x1UL << 36)            /* as: 0:8bit 1:16bit */
            | (TCR_CONFIG_TBI0 << 37)  /* tbi0 */
            | (TCR_CONFIG_TBI1 << 38); /* tbi1 */
    __asm__ volatile("msr TCR_EL1, %0\n" ::"r"(val64));
}

struct page_table
{
    unsigned long page[512];
};

/*  */
static struct page_table* __init_page_array;
static unsigned long __page_off = 0UL;
unsigned long get_ttbrn_base(void)
{
    return (unsigned long) __init_page_array;
}

void set_free_page(void *page_array)
{
    __init_page_array = page_array;
}

unsigned long get_free_page(void)
{
    return (unsigned long) (__init_page_array[__page_off++].page);
}

static int _map_single_page_2M(unsigned long *lv0_tbl, unsigned long va,
                               unsigned long pa, unsigned long attr)
{
    int level;
    unsigned long *cur_lv_tbl = lv0_tbl;
    unsigned long page;
    unsigned long off;
    int level_shift = MMU_ADDRESS_BITS;

    if (va & ARCH_SECTION_MASK)
    {
        return MMU_MAP_ERROR_VANOTALIGN;
    }
    if (pa & ARCH_PAGE_MASK)
    {
        return MMU_MAP_ERROR_PANOTALIGN;
    }
    for (level = 0; level < MMU_TBL_BLOCK_2M_LEVEL; level++)
    {
        off = (va >> level_shift);
        off &= MMU_LEVEL_MASK;
        if (!(cur_lv_tbl[off] & MMU_TYPE_USED))
        {
            page = get_free_page();
            if (!page)
            {
                return MMU_MAP_ERROR_NOPAGE;
            }
            rt_memset((char *)page, 0, ARCH_PAGE_SIZE);
            cur_lv_tbl[off] = page | MMU_TYPE_TABLE;
        }
        page = cur_lv_tbl[off];
        if ((page & MMU_TYPE_MASK) == MMU_TYPE_BLOCK)
        {
            /* is block! error! */
            return MMU_MAP_ERROR_CONFLICT;
        }
        cur_lv_tbl = (unsigned long *)(page & MMU_ADDRESS_MASK);
        level_shift -= MMU_LEVEL_SHIFT;
    }
    attr &= MMU_ATTRIB_MASK;
    pa |= (attr | MMU_TYPE_BLOCK); /* block */
    off = (va >> ARCH_SECTION_SHIFT);
    off &= MMU_LEVEL_MASK;
    cur_lv_tbl[off] = pa;
    return 0;
}

void *rt_hw_mmu_tbl_get(void)
{
    uintptr_t tbl;
    __asm__ volatile("MRS %0, TTBR0_EL1" : "=r"(tbl));
    return rt_kmem_p2v((void *)(tbl & ((1ul << 48) - 2)));
}

void *rt_ioremap_early(void *paddr, size_t size)
{
    volatile size_t count;
    rt_ubase_t base;
    static void *tbl = RT_NULL;

    if (!size)
    {
        return RT_NULL;
    }

    if (!tbl)
    {
        tbl = rt_hw_mmu_tbl_get();
    }

    /* get the total size required including overhead for alignment */
    count = (size + ((rt_ubase_t)paddr & ARCH_SECTION_MASK)
            + ARCH_SECTION_MASK) >> ARCH_SECTION_SHIFT;
    base = (rt_ubase_t)paddr & (~ARCH_SECTION_MASK);

    while (count --> 0)
    {
        if (_map_single_page_2M(tbl, base, base, MMU_MAP_K_DEVICE))
        {
            return RT_NULL;
        }

        base += ARCH_SECTION_SIZE;
    }

    return paddr;
}

static int _init_map_2M(unsigned long *lv0_tbl, unsigned long va,
                        unsigned long pa, unsigned long count,
                        unsigned long attr)
{
    unsigned long i;
    int ret;

    if (va & ARCH_SECTION_MASK)
    {
        return -1;
    }
    if (pa & ARCH_SECTION_MASK)
    {
        return -1;
    }
    for (i = 0; i < count; i++)
    {
        ret = _map_single_page_2M(lv0_tbl, va, pa, attr);
        va += ARCH_SECTION_SIZE;
        pa += ARCH_SECTION_SIZE;
        if (ret != 0)
        {
            return ret;
        }
    }
    return 0;
}

static unsigned long *_query(rt_aspace_t aspace, void *vaddr, int *plvl_shf)
{
    int level;
    unsigned long va = (unsigned long)vaddr;
    unsigned long *cur_lv_tbl;
    unsigned long page;
    unsigned long off;
    int level_shift = MMU_ADDRESS_BITS;

    cur_lv_tbl = aspace->page_table;
    RT_ASSERT(cur_lv_tbl);

    for (level = 0; level < MMU_TBL_PAGE_4k_LEVEL; level++)
    {
        off = (va >> level_shift);
        off &= MMU_LEVEL_MASK;

        if (!(cur_lv_tbl[off] & MMU_TYPE_USED))
        {
            *plvl_shf = level_shift;
            return (void *)0;
        }

        page = cur_lv_tbl[off];
        if ((page & MMU_TYPE_MASK) == MMU_TYPE_BLOCK)
        {
            *plvl_shf = level_shift;
            return &cur_lv_tbl[off];
        }

        cur_lv_tbl = (unsigned long *)(page & MMU_ADDRESS_MASK);
        cur_lv_tbl = (unsigned long *)((unsigned long)cur_lv_tbl - PV_OFFSET);
        level_shift -= MMU_LEVEL_SHIFT;
    }
    /* now is level MMU_TBL_PAGE_4k_LEVEL */
    off = (va >> ARCH_PAGE_SHIFT);
    off &= MMU_LEVEL_MASK;
    page = cur_lv_tbl[off];

    *plvl_shf = level_shift;
    if (!(page & MMU_TYPE_USED))
    {
        return (void *)0;
    }
    return &cur_lv_tbl[off];
}

void *rt_hw_mmu_v2p(rt_aspace_t aspace, void *v_addr)
{
    int level_shift;
    unsigned long paddr;

    if (aspace == &rt_kernel_space)
    {
        paddr = (unsigned long)rt_hw_mmu_kernel_v2p(v_addr);
    }
    else
    {
        unsigned long *pte = _query(aspace, v_addr, &level_shift);

        if (pte)
        {
            paddr = *pte & MMU_ADDRESS_MASK;
            paddr |= (rt_ubase_t)v_addr & ((1ul << level_shift) - 1);
        }
        else
        {
            paddr = (unsigned long)ARCH_MAP_FAILED;
        }
    }

    return (void *)paddr;
}

static int _noncache(rt_ubase_t *pte)
{
    int err = 0;
    const rt_ubase_t idx_shift = 2;
    const rt_ubase_t idx_mask = 0x7 << idx_shift;
    rt_ubase_t entry = *pte;
    if ((entry & idx_mask) == (NORMAL_MEM << idx_shift))
    {
        *pte = (entry & ~idx_mask) | (NORMAL_NOCACHE_MEM << idx_shift);
    }
    else
    {
        // do not support other type to be noncache
        err = -RT_ENOSYS;
    }
    return err;
}

static int _cache(rt_ubase_t *pte)
{
    int err = 0;
    const rt_ubase_t idx_shift = 2;
    const rt_ubase_t idx_mask = 0x7 << idx_shift;
    rt_ubase_t entry = *pte;
    if ((entry & idx_mask) == (NORMAL_NOCACHE_MEM << idx_shift))
    {
        *pte = (entry & ~idx_mask) | (NORMAL_MEM << idx_shift);
    }
    else
    {
        // do not support other type to be cache
        err = -RT_ENOSYS;
    }
    return err;
}

static int (*control_handler[MMU_CNTL_DUMMY_END])(rt_ubase_t *pte) = {
    [MMU_CNTL_CACHE] = _cache,
    [MMU_CNTL_NONCACHE] = _noncache,
};

int rt_hw_mmu_control(struct rt_aspace *aspace, void *vaddr, size_t size,
                      enum rt_mmu_cntl cmd)
{
    int level_shift;
    int err = -RT_EINVAL;
    rt_ubase_t vstart = (rt_ubase_t)vaddr;
    rt_ubase_t vend = vstart + size;

    int (*handler)(rt_ubase_t * pte);
    if (cmd >= 0 && cmd < MMU_CNTL_DUMMY_END)
    {
        handler = control_handler[cmd];

        while (vstart < vend)
        {
            rt_ubase_t *pte = _query(aspace, (void *)vstart, &level_shift);
            rt_ubase_t range_end = vstart + (1ul << level_shift);
            RT_ASSERT(range_end <= vend);

            if (pte)
            {
                err = handler(pte);
                RT_ASSERT(err == RT_EOK);
            }
            vstart = range_end;
        }
    }
    else
    {
        err = -RT_ENOSYS;
    }

    return err;
}

void rt_hw_mem_setup_early(unsigned long *tbl0, unsigned long *tbl1,
                           unsigned long size, unsigned long pv_off)
{
    int ret;
    unsigned long count = (size + ARCH_SECTION_MASK) >> ARCH_SECTION_SHIFT;
    unsigned long normal_attr = MMU_MAP_CUSTOM(MMU_AP_KAUN, NORMAL_MEM);

#ifdef RT_USING_SMART
    unsigned long va = KERNEL_VADDR_START;
#else
    extern unsigned char _start;
    unsigned long va = (unsigned long) &_start;
    va = RT_ALIGN_DOWN(va, 0x200000);
#endif

    /* setup pv off */
    rt_kmem_pvoff_set(pv_off);

    /* clean the first two pages */
    rt_memset((char *)tbl0, 0, ARCH_PAGE_SIZE);
    rt_memset((char *)tbl1, 0, ARCH_PAGE_SIZE);

    ret = _init_map_2M(tbl1, va, va + pv_off, count, normal_attr);
    if (ret != 0)
    {
        while (1);
    }
    ret = _init_map_2M(tbl0, va + pv_off, va + pv_off, count, normal_attr);
    if (ret != 0)
    {
        while (1);
    }
}

void *rt_hw_mmu_pgtbl_create(void)
{
    size_t *mmu_table;
    mmu_table = (size_t *)rt_pages_alloc_ext(0, PAGE_ANY_AVAILABLE);
    if (!mmu_table)
    {
        return RT_NULL;
    }

    memset(mmu_table, 0, ARCH_PAGE_SIZE);
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, mmu_table, ARCH_PAGE_SIZE);
    return mmu_table;
}

void rt_hw_mmu_pgtbl_delete(void *pgtbl)
{
    rt_pages_free(pgtbl, 0);
}
