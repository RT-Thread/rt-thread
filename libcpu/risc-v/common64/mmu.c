/*
 * Copyright (c) 2006-2025 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-01-30     lizhirui     first version
 * 2022-12-13     WangXiaoyao  Port to new mm
 * 2023-10-12     Shell        Add permission control API
 */

#include <rtthread.h>
#include <stddef.h>
#include <stdint.h>

#define DBG_TAG "hw.mmu"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <board.h>
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

/**
 * @brief Switch the current address space to the specified one.
 *
 * This function is responsible for switching the address space by updating the page table
 * and related hardware state. The behavior depends on whether the architecture supports
 * Address Space Identifiers (ASIDs), devided by macro definition of ARCH_USING_ASID.
 *
 * @param aspace Pointer to the address space structure containing the new page table.
 *
 * @note If ASID is supported (`ARCH_USING_ASID` is defined), the function will call
 *       `rt_hw_asid_switch_pgtbl` to switch the page table and update the ASID.
 *       Otherwise, it will directly write the `satp` CSR to switch the page table
 *       and invalidate the TLB.
 */
#ifdef ARCH_USING_ASID
void rt_hw_aspace_switch(rt_aspace_t aspace)
{
    uintptr_t page_table = (uintptr_t)rt_kmem_v2p(aspace->page_table);
    current_mmu_table = aspace->page_table;

    rt_hw_asid_switch_pgtbl(aspace, page_table);
}

#else /* !ARCH_USING_ASID */
void rt_hw_aspace_switch(rt_aspace_t aspace)
{
    uintptr_t page_table = (uintptr_t)rt_kmem_v2p(aspace->page_table);
    current_mmu_table = aspace->page_table;

    write_csr(satp, (((size_t)SATP_MODE) << SATP_MODE_OFFSET) |
                        ((rt_ubase_t)page_table >> PAGE_OFFSET_BIT));
    rt_hw_tlb_invalidate_all_local();
}

void rt_hw_asid_init(void)
{
}
#endif /* ARCH_USING_ASID */

/* get current page table. */
void *rt_hw_mmu_tbl_get()
{
    return current_mmu_table;
}

/* Map a single virtual address page to a physical address page in the page table. */
static int _map_one_page(struct rt_aspace *aspace, void *va, void *pa,
                         size_t attr)
{
    rt_ubase_t l1_off, l2_off, l3_off;
    rt_ubase_t *mmu_l1, *mmu_l2, *mmu_l3;

    l1_off = GET_L1((size_t)va);
    l2_off = GET_L2((size_t)va);
    l3_off = GET_L3((size_t)va);

    mmu_l1 = ((rt_ubase_t *)aspace->page_table) + l1_off;

    if (PTE_USED(*mmu_l1))
    {
        mmu_l2 = (rt_ubase_t *)PPN_TO_VPN(GET_PADDR(*mmu_l1), PV_OFFSET);
    }
    else
    {
        mmu_l2 = (rt_ubase_t *)rt_pages_alloc(0);

        if (mmu_l2)
        {
            rt_memset(mmu_l2, 0, PAGE_SIZE);
            rt_hw_cpu_dcache_clean(mmu_l2, PAGE_SIZE);
            *mmu_l1 = COMBINEPTE((rt_ubase_t)VPN_TO_PPN(mmu_l2, PV_OFFSET),
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
            (rt_ubase_t *)PPN_TO_VPN(GET_PADDR(*(mmu_l2 + l2_off)), PV_OFFSET);
    }
    else
    {
        mmu_l3 = (rt_ubase_t *)rt_pages_alloc(0);

        if (mmu_l3)
        {
            rt_memset(mmu_l3, 0, PAGE_SIZE);
            rt_hw_cpu_dcache_clean(mmu_l3, PAGE_SIZE);
            *(mmu_l2 + l2_off) =
                COMBINEPTE((rt_ubase_t)VPN_TO_PPN(mmu_l3, PV_OFFSET),
                           PAGE_DEFAULT_ATTR_NEXT);
            rt_hw_cpu_dcache_clean(mmu_l2, sizeof(*mmu_l2));
            /* declares a reference to parent page table */
            rt_page_ref_inc((void *)mmu_l2, 0);
        }
        else
        {
            return -1;
        }
    }

    RT_ASSERT(!PTE_USED(*(mmu_l3 + l3_off)));
    /* declares a reference to parent page table */
    rt_page_ref_inc((void *)mmu_l3, 0);
    *(mmu_l3 + l3_off) = COMBINEPTE((rt_ubase_t)pa, attr);
    rt_hw_cpu_dcache_clean(mmu_l3 + l3_off, sizeof(*(mmu_l3 + l3_off)));
    return 0;
}

/**
 * @brief Maps a virtual address space to a physical address space.
 *
 * This function maps a specified range of virtual addresses to a range of physical addresses
 * and sets the attributes of the page table entries (PTEs). If an error occurs during the
 * mapping process, the function will automatically roll back any partially completed mappings.
 *
 * @param aspace Pointer to the address space structure containing the page table information.
 * @param v_addr The starting virtual address to be mapped.
 * @param p_addr The starting physical address to be mapped.
 * @param size The size of the memory to be mapped (in bytes).
 * @param attr The attributes of the page table entries (e.g., read/write permissions, cache policies).
 *
 * @return On success, returns the starting virtual address `v_addr`;
 *         On failure, returns `NULL`.
 *
 * @note This function will not override existing page table entries.
 * @warning The caller must ensure that `v_addr` and `p_addr` are page-aligned,
 *          and `size` is a multiple of the page size.
 *
 */
void *rt_hw_mmu_map(struct rt_aspace *aspace, void *v_addr, void *p_addr,
                    size_t size, size_t attr)
{
    int ret = -1;
    void *unmap_va = v_addr;
    size_t npages = size >> ARCH_PAGE_SHIFT;

    /* TODO trying with HUGEPAGE here */
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

/* unmap page table entry */
static void _unmap_pte(rt_ubase_t *pentry, rt_ubase_t *lvl_entry[], int level)
{
    int loop_flag = 1;
    while (loop_flag)
    {
        loop_flag = 0;
        *pentry = 0;
        rt_hw_cpu_dcache_clean(pentry, sizeof(*pentry));

        /* we don't handle level 0, which is maintained by caller */
        if (level > 0)
        {
            void *page = (void *)((rt_ubase_t)pentry & ~ARCH_PAGE_MASK);

            /* decrease reference from child page to parent */
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

/* Unmaps a virtual address range from the page table. */
static size_t _unmap_area(struct rt_aspace *aspace, void *v_addr, size_t size)
{
    rt_ubase_t loop_va = __UMASKVALUE((rt_ubase_t)v_addr, PAGE_OFFSET_MASK);
    size_t unmapped = 0;

    int i = 0;
    rt_ubase_t lvl_off[3];
    rt_ubase_t *lvl_entry[3];
    lvl_off[0] = (rt_ubase_t)GET_L1(loop_va);
    lvl_off[1] = (rt_ubase_t)GET_L2(loop_va);
    lvl_off[2] = (rt_ubase_t)GET_L3(loop_va);
    unmapped = 1 << (ARCH_PAGE_SHIFT + ARCH_INDEX_WIDTH * 2ul);

    rt_ubase_t *pentry;
    lvl_entry[i] = ((rt_ubase_t *)aspace->page_table + lvl_off[i]);
    pentry = lvl_entry[i];

    /* find leaf page table entry */
    while (PTE_USED(*pentry) && !PAGE_IS_LEAF(*pentry))
    {
        i += 1;
        lvl_entry[i] = ((rt_ubase_t *)PPN_TO_VPN(GET_PADDR(*pentry), PV_OFFSET) +
                        lvl_off[i]);
        pentry = lvl_entry[i];
        unmapped >>= ARCH_INDEX_WIDTH;
    }

    /* clear PTE & setup its */
    if (PTE_USED(*pentry))
    {
        _unmap_pte(pentry, lvl_entry, i);
    }

    return unmapped;
}

/**
 * @brief Unmaps a range of virtual memory addresses from the specified address space.
 *
 * This function is responsible for unmapping a contiguous region of virtual memory
 * from the given address space. It handles multiple pages and ensures thread safety
 * by locking the page table during the unmapping operation.
 *
 * @param aspace Pointer to the address space structure from which the memory will be unmapped.
 * @param v_addr Starting virtual address to unmap. Must be page-aligned.
 * @param size Size of the memory region to unmap. Must be page-aligned.
 *
 * @note The caller must ensure that both `v_addr` and `size` are page-aligned.
 *
 * @details The function operates in a loop, unmapping memory in chunks. It uses the
 * `_unmap_area` function to perform the actual unmapping, which is called within a
 * locked section to ensure thread safety. The loop continues until the entire region
 * is unmapped.
 *
 * @see _unmap_area
 * @note unmap is different from map that it can handle multiple pages
 */
void rt_hw_mmu_unmap(struct rt_aspace *aspace, void *v_addr, size_t size)
{
    /* caller guarantee that v_addr & size are page aligned */
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

        /* when unmapped == 0, region not exist in pgtbl */
        if (!unmapped || unmapped > size) break;

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
    LOG_D("rt_ioremap_start: %p, rt_mpr_start: %p", rt_ioremap_start,
          rt_mpr_start);
}
#else
static inline void _init_region(void *vaddr, size_t size)
{
    rt_mpr_start = vaddr - rt_mpr_size;
}
#endif

#if defined(RT_USING_SMART) && defined(ARCH_REMAP_KERNEL)
#define KERN_SPACE_START ((void *)KERNEL_VADDR_START)
#define KERN_SPACE_SIZE  (0xfffffffffffff000UL - KERNEL_VADDR_START + 0x1000)
#else
#define KERN_SPACE_START ((void *)0x1000)
#define KERN_SPACE_SIZE  ((size_t)USER_VADDR_START - 0x1000)
#endif

/**
 * @brief Initialize the MMU (Memory Management Unit) mapping.
 *
 * This function initializes the MMU mapping, incluing these steps as follows:
 * 1. Check the validity of the input parameters,
 * 2. Calculate the start and end virtual addresses based on the input virtual address and size.
 * 3. Convert the virtual addresses to PPN2 indices.
 * 4. Check the initialization of the page table. If any entry in the page table within
 *    the specified range is non-zero, it returns -1.
 * 5. It initializes the kernel address space using rt_aspace_init() and initializes the specified region
 *    using _init_region.
 *
 * @param aspace Pointer to the address space. Must not be NULL.
 * @param v_address The starting virtual address.
 * @param size The size of the virtual address space.
 * @param vtable Pointer to the page table. Must not be NULL.
 * @param pv_off The page table offset.
 *
 * @return Returns 0 if the initialization is successful. Returns -1 if any input parameter is invalid
 *         or the page table initialization check fails.
 */
int rt_hw_mmu_map_init(rt_aspace_t aspace, void *v_address, rt_ubase_t size,
                       rt_ubase_t *vtable, rt_ubase_t pv_off)
{
    size_t l1_off, va_s, va_e;

    if ((!aspace) || (!vtable))
    {
        return -1;
    }

    va_s = (rt_ubase_t)v_address;
    va_e = ((rt_ubase_t)v_address) + size - 1;

    if (va_e < va_s)
    {
        return -1;
    }

    /* convert address to PPN2 index */
    va_s = GET_L1(va_s);
    va_e = GET_L1(va_e);

    if (va_s == 0)
    {
        return -1;
    }

    /* vtable initialization check */
    for (l1_off = va_s; l1_off <= va_e; l1_off++)
    {
        size_t v = vtable[l1_off];

        if (v)
        {
            return -1;
        }
    }

    rt_aspace_init(&rt_kernel_space, KERN_SPACE_START, KERN_SPACE_SIZE, vtable);

    _init_region(v_address, size);
    return 0;
}

const static int max_level =
    (ARCH_VADDR_WIDTH - ARCH_PAGE_SHIFT) / ARCH_INDEX_WIDTH;

static inline uintptr_t _get_level_size(int level)
{
    return 1ul << (ARCH_PAGE_SHIFT + (max_level - level) * ARCH_INDEX_WIDTH);
}

static rt_ubase_t *_query(struct rt_aspace *aspace, void *vaddr, int *level)
{
    rt_ubase_t l1_off, l2_off, l3_off;
    rt_ubase_t *mmu_l1, *mmu_l2, *mmu_l3;
    rt_ubase_t pa;

    l1_off = GET_L1((rt_uintptr_t)vaddr);
    l2_off = GET_L2((rt_uintptr_t)vaddr);
    l3_off = GET_L3((rt_uintptr_t)vaddr);

    if (!aspace)
    {
        LOG_W("%s: no aspace", __func__);
        return RT_NULL;
    }

    mmu_l1 = ((rt_ubase_t *)aspace->page_table) + l1_off;

    if (PTE_USED(*mmu_l1))
    {
        if (*mmu_l1 & PTE_XWR_MASK)
        {
            *level = 1;
            return mmu_l1;
        }

        mmu_l2 = (rt_ubase_t *)PPN_TO_VPN(GET_PADDR(*mmu_l1), PV_OFFSET);

        if (PTE_USED(*(mmu_l2 + l2_off)))
        {
            if (*(mmu_l2 + l2_off) & PTE_XWR_MASK)
            {
                *level = 2;
                return mmu_l2 + l2_off;
            }

            mmu_l3 = (rt_ubase_t *)PPN_TO_VPN(GET_PADDR(*(mmu_l2 + l2_off)),
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

/**
 * @brief Translate a virtual address to a physical address.
 *
 * This function translates a given virtual address (`vaddr`) to its corresponding
 * physical address (`paddr`) using the page table in the specified address space (`aspace`).
 *
 * @param aspace Pointer to the address space structure containing the page table.
 * @param vaddr The virtual address to be translated.
 *
 * @return The translated physical address. If the translation fails, `ARCH_MAP_FAILED` is returned.
 *
 * @note The function queries the page table entry (PTE) for the virtual address using `_query`.
 *       If a valid PTE is found, the physical address is extracted and combined with the offset
 *       from the virtual address. If no valid PTE is found, a debug log is recorded, and
 *       `ARCH_MAP_FAILED` is returned.
 */
void *rt_hw_mmu_v2p(struct rt_aspace *aspace, void *vaddr)
{
    int level;
    rt_ubase_t *pte = _query(aspace, vaddr, &level);
    uintptr_t paddr;

    if (pte)
    {
        paddr = GET_PADDR(*pte);
        paddr |= ((intptr_t)vaddr & (_get_level_size(level) - 1));
    }
    else
    {
        LOG_D("%s: failed at %p", __func__, vaddr);
        paddr = (uintptr_t)ARCH_MAP_FAILED;
    }
    return (void *)paddr;
}

static int _noncache(rt_base_t *pte)
{
    return 0;
}

static int _cache(rt_base_t *pte)
{
    return 0;
}

static int (*control_handler[MMU_CNTL_DUMMY_END])(rt_base_t *pte)=
{
    [MMU_CNTL_CACHE] = _cache,
    [MMU_CNTL_NONCACHE] = _noncache,
};

/**
 * @brief Control the page table entries (PTEs) for a specified virtual address range.
 *
 * This function applies a control command (e.g., cache control) to the page table entries
 * (PTEs) corresponding to the specified virtual address range (`vaddr` to `vaddr + size`).
 *
 * @param aspace Pointer to the address space structure containing the page table.
 * @param vaddr The starting virtual address of the range.
 * @param size The size of the virtual address range.
 * @param cmd The control command to apply (e.g., `MMU_CNTL_CACHE`, `MMU_CNTL_NONCACHE`.etc.).
 *
 * @return `RT_EOK` on success, or an error code (`-RT_EINVAL` or `-RT_ENOSYS`) on failure.
 *
 * @note The function uses the `control_handler` array to map the command to a handler function.
 *       It iterates over the virtual address range, queries the PTEs, and applies the handler
 *       to each valid PTE. If the command is invalid, `-RT_ENOSYS` is returned.
 */
int rt_hw_mmu_control(struct rt_aspace *aspace, void *vaddr, size_t size,
                      enum rt_mmu_cntl cmd)
{
    int level;
    int err = -RT_EINVAL;
    void *vend = vaddr + size;

    int (*handler)(rt_base_t *pte);
    if (cmd >= 0 && cmd < MMU_CNTL_DUMMY_END)
    {
        handler = control_handler[cmd];

        while (vaddr < vend)
        {
            rt_base_t *pte = _query(aspace, vaddr, &level);
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
 * @param aspace Pointer to the address space structure.
 * @param mdesc Pointer to the array of memory descriptors.
 * @param desc_nr Number of memory descriptors in the array.
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

        struct rt_mm_va_hint hint = {
            .flags = MMF_MAP_FIXED,
            .limit_start = aspace->start,
            .limit_range_size = aspace->size,
            .map_size = mdesc->vaddr_end - mdesc->vaddr_start + 1,
            .prefer = (void *)mdesc->vaddr_start};

        if (mdesc->paddr_start == (rt_uintptr_t)ARCH_MAP_FAILED)
            mdesc->paddr_start = mdesc->vaddr_start + PV_OFFSET;

        rt_aspace_map_phy_static(aspace, &mdesc->varea, &hint, attr,
                                 mdesc->paddr_start >> MM_PAGE_SHIFT, &err);
        mdesc++;
    }

    rt_hw_asid_init();

    rt_hw_aspace_switch(&rt_kernel_space);
    rt_page_cleanup();
}

#define SATP_BASE ((rt_ubase_t)SATP_MODE << SATP_MODE_OFFSET)
void rt_hw_mem_setup_early(void)
{
    rt_ubase_t pv_off;
    rt_ubase_t ps = 0x0;
    rt_ubase_t vs = 0x0;
    rt_ubase_t *early_pgtbl = (rt_ubase_t *)(((size_t)&__bss_end + 4095) & ~0xfff);

    /* calculate pv_offset */
    void *symb_pc;
    void *symb_linker;
    __asm__ volatile("la %0, _start\n" : "=r"(symb_pc));
    __asm__ volatile("la %0, _start_link_addr\n" : "=r"(symb_linker));
    symb_linker = *(void **)symb_linker;
    pv_off = symb_pc - symb_linker;
    rt_kmem_pvoff_set(pv_off);

    if (pv_off)
    {
        if (pv_off & ((1ul << (ARCH_INDEX_WIDTH * 2 + ARCH_PAGE_SHIFT)) - 1))
        {
            LOG_E("%s: not aligned virtual address. pv_offset %p", __func__,
                  pv_off);
            RT_ASSERT(0);
        }

        /**
         * identical mapping,
         * PC are still at lower region before relocating to high memory
         */
        for (size_t i = 0; i < __SIZE(PPN0_BIT); i++)
        {
            early_pgtbl[i] = COMBINEPTE(ps, MMU_MAP_EARLY);
            ps += L1_PAGE_SIZE;
        }

        /* relocate text region */
        __asm__ volatile("la %0, _start\n" : "=r"(ps));
        ps &= ~(L1_PAGE_SIZE - 1);
        vs = ps - pv_off;

        /* relocate region */
        rt_ubase_t vs_idx = GET_L1(vs);
        rt_ubase_t ve_idx = GET_L1(vs + 0x80000000);
        for (size_t i = vs_idx; i < ve_idx; i++)
        {
            early_pgtbl[i] = COMBINEPTE(ps, MMU_MAP_EARLY);
            ps += L1_PAGE_SIZE;
        }

        /* apply new mapping */
        asm volatile("sfence.vma x0, x0");
        write_csr(satp, SATP_BASE | ((size_t)early_pgtbl >> PAGE_OFFSET_BIT));
        asm volatile("sfence.vma x0, x0");
    }
    /* return to lower text section */
}

/**
 * @brief Creates and initializes a new MMU page table.
 *
 * This function allocates a new MMU page table, copies the kernel space
 * page table into it, and flushes the data cache to ensure consistency.
 *
 * @return
 * - A pointer to the newly allocated MMU page table on success.
 * - RT_NULL if the allocation fails.
 */
void *rt_hw_mmu_pgtbl_create(void)
{
    rt_ubase_t *mmu_table;
    mmu_table = (rt_ubase_t *)rt_pages_alloc_ext(0, PAGE_ANY_AVAILABLE);
    if (!mmu_table)
    {
        return RT_NULL;
    }
    rt_memcpy(mmu_table, rt_kernel_space.page_table, ARCH_PAGE_SIZE);
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, mmu_table, ARCH_PAGE_SIZE);

    return mmu_table;
}

/**
 * @brief Deletes an MMU page table.
 *
 * This function frees the memory allocated for the given MMU page table.
 *
 * @param pgtbl Pointer to the MMU page table to be deleted.
 */
void rt_hw_mmu_pgtbl_delete(void *pgtbl)
{
    rt_pages_free(pgtbl, 0);
}