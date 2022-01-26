/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-11-28     GuEe-GUI     first version
 */

#include <rtthread.h>
#include <rthw.h>

#include <cpuport.h>
#include <mmu.h>

#define ARCH_SECTION_SHIFT  21
#define ARCH_SECTION_SIZE   (1 << ARCH_SECTION_SHIFT)
#define ARCH_SECTION_MASK   (ARCH_SECTION_SIZE - 1)
#define ARCH_PAGE_SHIFT     12
#define ARCH_PAGE_SIZE      (1 << ARCH_PAGE_SHIFT)
#define ARCH_PAGE_MASK      (ARCH_PAGE_SIZE - 1)

#define MMU_LEVEL_MASK      0x1ffUL
#define MMU_LEVEL_SHIFT     9
#define MMU_ADDRESS_BITS    39
#define MMU_ADDRESS_MASK    0x0000fffffffff000UL
#define MMU_ATTRIB_MASK     0xfff0000000000ffcUL

#define MMU_TYPE_MASK       3UL
#define MMU_TYPE_USED       1UL
#define MMU_TYPE_BLOCK      1UL
#define MMU_TYPE_TABLE      3UL
#define MMU_TYPE_PAGE       3UL

#define MMU_TBL_BLOCK_2M_LEVEL  2
#define MMU_TBL_PAGE_NR_MAX     32

/* only map 4G io/memory */
static volatile unsigned long MMUTable[512] __attribute__((aligned(4096)));
static volatile struct
{
    unsigned long entry[512];
} MMUPage[MMU_TBL_PAGE_NR_MAX] __attribute__((aligned(4096)));

static unsigned long _kernel_free_page(void)
{
    static unsigned long i = 0;

    if (i >= MMU_TBL_PAGE_NR_MAX)
    {
        return RT_NULL;
    }

    ++i;

    return (unsigned long)&MMUPage[i - 1].entry;
}

static int _kenrel_map_2M(unsigned long *tbl, unsigned long va, unsigned long pa, unsigned long attr)
{
    int level;
    unsigned long *cur_lv_tbl = tbl;
    unsigned long page;
    unsigned long off;
    int level_shift = MMU_ADDRESS_BITS;

    if (va & ARCH_SECTION_MASK)
    {
        return MMU_MAP_ERROR_VANOTALIGN;
    }
    if (pa & ARCH_SECTION_MASK)
    {
        return MMU_MAP_ERROR_PANOTALIGN;
    }

    for (level = 0; level < MMU_TBL_BLOCK_2M_LEVEL; ++level)
    {
        off = (va >> level_shift);
        off &= MMU_LEVEL_MASK;

        if (!(cur_lv_tbl[off] & MMU_TYPE_USED))
        {
            page = _kernel_free_page();

            if (!page)
            {
                return MMU_MAP_ERROR_NOPAGE;
            }

            rt_memset((char *)page, 0, ARCH_PAGE_SIZE);
            rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, (void *)page, ARCH_PAGE_SIZE);
            cur_lv_tbl[off] = page | MMU_TYPE_TABLE;
            rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, cur_lv_tbl + off, sizeof(void *));
        }
        else
        {
            page = cur_lv_tbl[off];
            page &= MMU_ADDRESS_MASK;
        }

        page = cur_lv_tbl[off];
        if ((page & MMU_TYPE_MASK) == MMU_TYPE_BLOCK)
        {
            /* is block! error! */
            return MMU_MAP_ERROR_CONFLICT;
        }

        /* next level */
        cur_lv_tbl = (unsigned long *)(page & MMU_ADDRESS_MASK);
        level_shift -= MMU_LEVEL_SHIFT;
    }

    attr &= MMU_ATTRIB_MASK;
    pa |= (attr | MMU_TYPE_BLOCK);
    off = (va >> ARCH_SECTION_SHIFT);
    off &= MMU_LEVEL_MASK;
    cur_lv_tbl[off] = pa;
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, cur_lv_tbl + off, sizeof(void *));

    return 0;
}

int rt_hw_mmu_setmtt(unsigned long vaddr_start, unsigned long vaddr_end,
        unsigned long paddr_start, unsigned long attr)
{
    int ret = -1;
    int i;
    unsigned long count;
    unsigned long map_attr = MMU_MAP_CUSTOM(MMU_AP_KAUN, attr);

    if (vaddr_start > vaddr_end)
    {
        goto end;
    }
    if (vaddr_start % ARCH_SECTION_SIZE)
    {
        vaddr_start = (vaddr_start / ARCH_SECTION_SIZE) * ARCH_SECTION_SIZE;
    }
    if (paddr_start % ARCH_SECTION_SIZE)
    {
        paddr_start = (paddr_start / ARCH_SECTION_SIZE) * ARCH_SECTION_SIZE;
    }
    if (vaddr_end % ARCH_SECTION_SIZE)
    {
        vaddr_end = (vaddr_end / ARCH_SECTION_SIZE + 1) * ARCH_SECTION_SIZE;
    }

    count = (vaddr_end - vaddr_start) >> ARCH_SECTION_SHIFT;

    for (i = 0; i < count; i++)
    {
        ret = _kenrel_map_2M((void *)MMUTable, vaddr_start, paddr_start, map_attr);
        vaddr_start += ARCH_SECTION_SIZE;
        paddr_start += ARCH_SECTION_SIZE;

        if (ret != 0)
        {
            goto end;
        }
    }

end:
    return ret;
}

void rt_hw_init_mmu_table(struct mem_desc *mdesc, rt_size_t desc_nr)
{
    rt_memset((void *)MMUTable, 0, sizeof(MMUTable));
    rt_memset((void *)MMUPage, 0, sizeof(MMUPage));

    /* set page table */
    for (; desc_nr > 0; --desc_nr)
    {
        rt_hw_mmu_setmtt(mdesc->vaddr_start, mdesc->vaddr_end, mdesc->paddr_start, mdesc->attr);
        ++mdesc;
    }

    rt_hw_dcache_flush_range((unsigned long)MMUTable, sizeof(MMUTable));
}

void rt_hw_mmu_tlb_invalidate(void)
{
    __asm__ volatile (
        "tlbi vmalle1\n\r"
        "dsb sy\n\r"
        "isb sy\n\r"
        "ic ialluis\n\r"
        "dsb sy\n\r"
        "isb sy");
}

void rt_hw_mmu_init(void)
{
    unsigned long reg_val;

    reg_val = 0x00447fUL;
    __asm__ volatile("msr mair_el1, %0"::"r"(reg_val));

    rt_hw_isb();

    reg_val = (16UL << 0)   /* t0sz 48bit */
            | (0UL  << 6)   /* reserved */
            | (0UL  << 7)   /* epd0 */
            | (3UL  << 8)   /* t0 wb cacheable */
            | (3UL  << 10)  /* inner shareable */
            | (2UL  << 12)  /* t0 outer shareable */
            | (0UL  << 14)  /* t0 4K */
            | (16UL << 16)  /* t1sz 48bit */
            | (0UL  << 22)  /* define asid use ttbr0.asid */
            | (0UL  << 23)  /* epd1 */
            | (3UL  << 24)  /* t1 inner wb cacheable */
            | (3UL  << 26)  /* t1 outer wb cacheable */
            | (2UL  << 28)  /* t1 outer shareable */
            | (2UL  << 30)  /* t1 4k */
            | (1UL  << 32)  /* 001b 64GB PA */
            | (0UL  << 35)  /* reserved */
            | (1UL  << 36)  /* as: 0:8bit 1:16bit */
            | (0UL  << 37)  /* tbi0 */
            | (0UL  << 38); /* tbi1 */
    __asm__ volatile("msr tcr_el1, %0"::"r"(reg_val));

    rt_hw_isb();

    __asm__ volatile ("mrs %0, sctlr_el1":"=r"(reg_val));

    reg_val |= 1 << 2;  /* enable dcache */
    reg_val |= 1 << 0;  /* enable mmu */

    __asm__ volatile (
        "msr ttbr0_el1, %0\n\r"
        "msr sctlr_el1, %1\n\r"
        "dsb sy\n\r"
        "isb sy\n\r"
        ::"r"(MMUTable), "r"(reg_val) :"memory");

    rt_hw_mmu_tlb_invalidate();
}

int rt_hw_mmu_map(unsigned long addr, unsigned long size, unsigned long attr)
{
    int ret;
    rt_ubase_t level;

    level = rt_hw_interrupt_disable();
    ret = rt_hw_mmu_setmtt(addr, addr + size, addr, attr);

    rt_hw_interrupt_enable(level);

    return ret;
}
