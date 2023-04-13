/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-30     lizhirui     first version
 * 2022-12-13     WangXiaoyao  Port to new mm
 */

#include <rtthread.h>
#include <stddef.h>
#include <stdint.h>

#define DBG_TAG "hw.mmu"
#define DBG_LVL DBG_WARNING
#include <rtdbg.h>

#include <cache.h>
#include <mm_aspace.h>
#include <mm_page.h>
#include <mmu.h>
#include <riscv_mmu.h>
#include <tlb.h>

#ifdef RT_USING_SMART
#include <board.h>
#include <ioremap.h>
#include <lwp_user_mm.h>
#endif

#ifndef RT_USING_SMART
#define USER_VADDR_START 0
#endif

static size_t _unmap_area(struct rt_aspace *aspace, void *v_addr, size_t size);

static void *current_mmu_table = RT_NULL;

volatile __attribute__((aligned(4 * 1024)))
rt_ubase_t MMUTable[__SIZE(VPN2_BIT)];

static rt_uint8_t ASID_BITS = 0;
static rt_uint32_t next_asid;
static rt_uint64_t global_asid_generation;
#define ASID_MASK ((1 << ASID_BITS) - 1)
#define ASID_FIRST_GENERATION (1 << ASID_BITS)
#define MAX_ASID ASID_FIRST_GENERATION

static void _asid_init()
{
    unsigned int satp_reg = read_csr(satp);
    satp_reg |= (((rt_uint64_t)0xffff) << PPN_BITS);
    write_csr(satp, satp_reg);
    unsigned short valid_asid_bit = ((read_csr(satp) >> PPN_BITS) & 0xffff);

    // The maximal value of ASIDLEN, is 9 for Sv32 or 16 for Sv39, Sv48, and Sv57
    for (unsigned i = 0; i < 16; i++)
    {
        if (!(valid_asid_bit & 0x1))
        {
            break;
        }

        valid_asid_bit >>= 1;
        ASID_BITS++;
    }

    global_asid_generation = ASID_FIRST_GENERATION;
    next_asid = 1;
}

static rt_uint64_t _asid_check_switch(rt_aspace_t aspace)
{
    if ((aspace->asid ^ global_asid_generation) >> ASID_BITS) // not same generation
    {
        if (next_asid != MAX_ASID)
        {
            aspace->asid = global_asid_generation | next_asid;
            next_asid++;
        }
        else
        {
            // scroll to next generation
            global_asid_generation += ASID_FIRST_GENERATION;
            next_asid = 1;
            rt_hw_tlb_invalidate_all_local();

            aspace->asid = global_asid_generation | next_asid;
            next_asid++;
        }
    }

    return aspace->asid & ASID_MASK;
}

void rt_hw_aspace_switch(rt_aspace_t aspace)
{
    uintptr_t page_table = (uintptr_t)rt_kmem_v2p(aspace->page_table);
    current_mmu_table = aspace->page_table;

    rt_uint64_t asid = _asid_check_switch(aspace);
    write_csr(satp, (((size_t)SATP_MODE) << SATP_MODE_OFFSET) |
                        (asid << PPN_BITS) |
                        ((rt_ubase_t)page_table >> PAGE_OFFSET_BIT));
    asm volatile("sfence.vma x0,%0"::"r"(asid):"memory");
}

void *rt_hw_mmu_tbl_get()
{
    return current_mmu_table;
}

static int _map_one_page(struct rt_aspace *aspace, void *va, void *pa,
                         size_t attr)
{
    rt_size_t l1_off, l2_off, l3_off;
    rt_size_t *mmu_l1, *mmu_l2, *mmu_l3;

    l1_off = GET_L1((size_t)va);
    l2_off = GET_L2((size_t)va);
    l3_off = GET_L3((size_t)va);

    mmu_l1 = ((rt_size_t *)aspace->page_table) + l1_off;

    if (PTE_USED(*mmu_l1))
    {
        mmu_l2 = (rt_size_t *)PPN_TO_VPN(GET_PADDR(*mmu_l1), PV_OFFSET);
    }
    else
    {
        mmu_l2 = (rt_size_t *)rt_pages_alloc(0);

        if (mmu_l2)
        {
            rt_memset(mmu_l2, 0, PAGE_SIZE);
            rt_hw_cpu_dcache_clean(mmu_l2, PAGE_SIZE);
            *mmu_l1 = COMBINEPTE((rt_size_t)VPN_TO_PPN(mmu_l2, PV_OFFSET),
                                 PAGE_DEFAULT_ATTR_NEXT);
            rt_hw_cpu_dcache_clean(mmu_l1, sizeof(*mmu_l1));
        }
        else
        {
            return -1;
        }
    }

    if (PTE_USED(*(mmu_l2 + l2_off)))
    {
        RT_ASSERT(!PAGE_IS_LEAF(*(mmu_l2 + l2_off)));
        mmu_l3 =
            (rt_size_t *)PPN_TO_VPN(GET_PADDR(*(mmu_l2 + l2_off)), PV_OFFSET);
    }
    else
    {
        mmu_l3 = (rt_size_t *)rt_pages_alloc(0);

        if (mmu_l3)
        {
            rt_memset(mmu_l3, 0, PAGE_SIZE);
            rt_hw_cpu_dcache_clean(mmu_l3, PAGE_SIZE);
            *(mmu_l2 + l2_off) =
                COMBINEPTE((rt_size_t)VPN_TO_PPN(mmu_l3, PV_OFFSET),
                           PAGE_DEFAULT_ATTR_NEXT);
            rt_hw_cpu_dcache_clean(mmu_l2, sizeof(*mmu_l2));
            // declares a reference to parent page table
            rt_page_ref_inc((void *)mmu_l2, 0);
        }
        else
        {
            return -1;
        }
    }

    RT_ASSERT(!PTE_USED(*(mmu_l3 + l3_off)));
    // declares a reference to parent page table
    rt_page_ref_inc((void *)mmu_l3, 0);
    *(mmu_l3 + l3_off) = COMBINEPTE((rt_size_t)pa, attr);
    rt_hw_cpu_dcache_clean(mmu_l3 + l3_off, sizeof(*(mmu_l3 + l3_off)));
    return 0;
}

/** rt_hw_mmu_map will never override existed page table entry */
void *rt_hw_mmu_map(struct rt_aspace *aspace, void *v_addr, void *p_addr,
                    size_t size, size_t attr)
{
    int ret = -1;
    void *unmap_va = v_addr;
    size_t npages = size >> ARCH_PAGE_SHIFT;

    // TODO trying with HUGEPAGE here
    while (npages--)
    {
        MM_PGTBL_LOCK(aspace);
        ret = _map_one_page(aspace, v_addr, p_addr, attr);
        MM_PGTBL_UNLOCK(aspace);
        if (ret != 0)
        {
            /* error, undo map */
            while (unmap_va != v_addr)
            {
                MM_PGTBL_LOCK(aspace);
                _unmap_area(aspace, unmap_va, ARCH_PAGE_SIZE);
                MM_PGTBL_UNLOCK(aspace);
                unmap_va += ARCH_PAGE_SIZE;
            }
            break;
        }
        v_addr += ARCH_PAGE_SIZE;
        p_addr += ARCH_PAGE_SIZE;
    }

    if (ret == 0)
    {
        return unmap_va;
    }

    return NULL;
}

static void _unmap_pte(rt_size_t *pentry, rt_size_t *lvl_entry[], int level)
{
    int loop_flag = 1;
    while (loop_flag)
    {
        loop_flag = 0;
        *pentry = 0;
        rt_hw_cpu_dcache_clean(pentry, sizeof(*pentry));

        // we don't handle level 0, which is maintained by caller
        if (level > 0)
        {
            void *page = (void *)((rt_ubase_t)pentry & ~ARCH_PAGE_MASK);

            // decrease reference from child page to parent
            rt_pages_free(page, 0);

            int free = rt_page_ref_get(page, 0);
            if (free == 1)
            {
                rt_pages_free(page, 0);
                pentry = lvl_entry[--level];
                loop_flag = 1;
            }
        }
    }
}

static size_t _unmap_area(struct rt_aspace *aspace, void *v_addr, size_t size)
{
    rt_size_t loop_va = __UMASKVALUE((rt_size_t)v_addr, PAGE_OFFSET_MASK);
    size_t unmapped = 0;

    int i = 0;
    rt_size_t lvl_off[3];
    rt_size_t *lvl_entry[3];
    lvl_off[0] = (rt_size_t)GET_L1(loop_va);
    lvl_off[1] = (rt_size_t)GET_L2(loop_va);
    lvl_off[2] = (rt_size_t)GET_L3(loop_va);
    unmapped = 1 << (ARCH_PAGE_SHIFT + ARCH_INDEX_WIDTH * 2ul);

    rt_size_t *pentry;
    lvl_entry[i] = ((rt_size_t *)aspace->page_table + lvl_off[i]);
    pentry = lvl_entry[i];

    // find leaf page table entry
    while (PTE_USED(*pentry) && !PAGE_IS_LEAF(*pentry))
    {
        i += 1;
        lvl_entry[i] = ((rt_size_t *)PPN_TO_VPN(GET_PADDR(*pentry), PV_OFFSET) +
                        lvl_off[i]);
        pentry = lvl_entry[i];
        unmapped >>= ARCH_INDEX_WIDTH;
    }

    // clear PTE & setup its
    if (PTE_USED(*pentry))
    {
        _unmap_pte(pentry, lvl_entry, i);
    }

    return unmapped;
}

/** unmap is different from map that it can handle multiple pages */
void rt_hw_mmu_unmap(struct rt_aspace *aspace, void *v_addr, size_t size)
{
    // caller guarantee that v_addr & size are page aligned
    if (!aspace->page_table)
    {
        return;
    }
    size_t unmapped = 0;

    while (size > 0)
    {
        MM_PGTBL_LOCK(aspace);
        unmapped = _unmap_area(aspace, v_addr, size);
        MM_PGTBL_UNLOCK(aspace);

        // when unmapped == 0, region not exist in pgtbl
        if (!unmapped || unmapped > size)
            break;

        size -= unmapped;
        v_addr += unmapped;
    }
}

#ifdef RT_USING_SMART
static inline void _init_region(void *vaddr, size_t size)
{
    rt_ioremap_start = vaddr;
    rt_ioremap_size = size;
    rt_mpr_start = rt_ioremap_start - rt_mpr_size;
    LOG_D("rt_ioremap_start: %p, rt_mpr_start: %p", rt_ioremap_start, rt_mpr_start);
}
#else
static inline void _init_region(void *vaddr, size_t size)
{
    rt_mpr_start = vaddr - rt_mpr_size;
}
#endif

int rt_hw_mmu_map_init(rt_aspace_t aspace, void *v_address, rt_size_t size,
                       rt_size_t *vtable, rt_size_t pv_off)
{
    size_t l1_off, va_s, va_e;
    rt_base_t level;

    if ((!aspace) || (!vtable))
    {
        return -1;
    }

    va_s = (rt_size_t)v_address;
    va_e = ((rt_size_t)v_address) + size - 1;

    if (va_e < va_s)
    {
        return -1;
    }

    // convert address to PPN2 index
    va_s = GET_L1(va_s);
    va_e = GET_L1(va_e);

    if (va_s == 0)
    {
        return -1;
    }

    // vtable initialization check
    for (l1_off = va_s; l1_off <= va_e; l1_off++)
    {
        size_t v = vtable[l1_off];

        if (v)
        {
            return -1;
        }
    }

    rt_aspace_init(&rt_kernel_space, (void *)0x1000, USER_VADDR_START - 0x1000,
                   vtable);

    _init_region(v_address, size);
    return 0;
}

const static int max_level =
    (ARCH_VADDR_WIDTH - ARCH_PAGE_SHIFT) / ARCH_INDEX_WIDTH;

static inline uintptr_t _get_level_size(int level)
{
    return 1ul << (ARCH_PAGE_SHIFT + (max_level - level) * ARCH_INDEX_WIDTH);
}

static rt_size_t *_query(struct rt_aspace *aspace, void *vaddr, int *level)
{
    rt_size_t l1_off, l2_off, l3_off;
    rt_size_t *mmu_l1, *mmu_l2, *mmu_l3;
    rt_size_t pa;

    l1_off = GET_L1((rt_size_t)vaddr);
    l2_off = GET_L2((rt_size_t)vaddr);
    l3_off = GET_L3((rt_size_t)vaddr);

    if (!aspace)
    {
        LOG_W("%s: no aspace", __func__);
        return RT_NULL;
    }

    mmu_l1 = ((rt_size_t *)aspace->page_table) + l1_off;

    if (PTE_USED(*mmu_l1))
    {
        if (*mmu_l1 & PTE_XWR_MASK)
        {
            *level = 1;
            return mmu_l1;
        }

        mmu_l2 = (rt_size_t *)PPN_TO_VPN(GET_PADDR(*mmu_l1), PV_OFFSET);

        if (PTE_USED(*(mmu_l2 + l2_off)))
        {
            if (*(mmu_l2 + l2_off) & PTE_XWR_MASK)
            {
                *level = 2;
                return mmu_l2 + l2_off;
            }

            mmu_l3 = (rt_size_t *)PPN_TO_VPN(GET_PADDR(*(mmu_l2 + l2_off)),
                                             PV_OFFSET);

            if (PTE_USED(*(mmu_l3 + l3_off)))
            {
                *level = 3;
                return mmu_l3 + l3_off;
            }
        }
    }

    return RT_NULL;
}

void *rt_hw_mmu_v2p(struct rt_aspace *aspace, void *vaddr)
{
    int level;
    uintptr_t *pte = _query(aspace, vaddr, &level);
    uintptr_t paddr;

    if (pte)
    {
        paddr = GET_PADDR(*pte);
        paddr |= ((intptr_t)vaddr & (_get_level_size(level) - 1));
    }
    else
    {
        LOG_I("%s: failed at %p", __func__, vaddr);
        paddr = (uintptr_t)ARCH_MAP_FAILED;
    }
    return (void *)paddr;
}

static int _noncache(uintptr_t *pte)
{
    return 0;
}

static int _cache(uintptr_t *pte)
{
    return 0;
}

static int (*control_handler[MMU_CNTL_DUMMY_END])(uintptr_t *pte) = {
    [MMU_CNTL_CACHE] = _cache,
    [MMU_CNTL_NONCACHE] = _noncache,
};

int rt_hw_mmu_control(struct rt_aspace *aspace, void *vaddr, size_t size,
                      enum rt_mmu_cntl cmd)
{
    int level;
    int err = -RT_EINVAL;
    void *vend = vaddr + size;

    int (*handler)(uintptr_t * pte);
    if (cmd >= 0 && cmd < MMU_CNTL_DUMMY_END)
    {
        handler = control_handler[cmd];

        while (vaddr < vend)
        {
            uintptr_t *pte = _query(aspace, vaddr, &level);
            void *range_end = vaddr + _get_level_size(level);
            RT_ASSERT(range_end <= vend);

            if (pte)
            {
                err = handler(pte);
                RT_ASSERT(err == RT_EOK);
            }
            vaddr = range_end;
        }
    }
    else
    {
        err = -RT_ENOSYS;
    }

    return err;
}

/**
 * @brief setup Page Table for kernel space. It's a fixed map
 * and all mappings cannot be changed after initialization.
 *
 * Memory region in struct mem_desc must be page aligned,
 * otherwise is a failure and no report will be
 * returned.
 *
 * @param aspace
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

        rt_aspace_map_phy_static(aspace, &mdesc->varea, &hint, attr,
                                 mdesc->paddr_start >> MM_PAGE_SHIFT, &err);
        mdesc++;
    }

    _asid_init();

    rt_hw_aspace_switch(&rt_kernel_space);
    rt_page_cleanup();
}

void rt_hw_mmu_kernel_map_init(rt_aspace_t aspace, rt_size_t vaddr_start, rt_size_t size)
{
    rt_size_t paddr_start =
        __UMASKVALUE(VPN_TO_PPN(vaddr_start, PV_OFFSET), PAGE_OFFSET_MASK);
    rt_size_t va_s = GET_L1(vaddr_start);
    rt_size_t va_e = GET_L1(vaddr_start + size - 1);
    rt_size_t i;

    for (i = va_s; i <= va_e; i++)
    {
        MMUTable[i] =
            COMBINEPTE(paddr_start, PAGE_ATTR_RWX | PTE_G | PTE_V | PTE_CACHE |
                                        PTE_SHARE | PTE_BUF | PTE_A | PTE_D);
        paddr_start += L1_PAGE_SIZE;
    }

    rt_hw_tlb_invalidate_all_local();
}
