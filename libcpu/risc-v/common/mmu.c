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
 * 2025-04-26     GuEe-GUI     Follow the specific and vendor
 */

#include <rthw.h>
#include <rtthread.h>

#define DBG_TAG "hw.mmu"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <cpu.h>
#include <csr.h>
#include <mmu.h>
#include <tlb.h>
#include <cache.h>
#include <ioremap.h>
#include <isa_ext.h>
#include <mm_page.h>
#include <mm_aspace.h>
#ifdef RT_USING_SMART
#include <lwp_user_mm.h>
#endif

#ifndef KERNEL_VADDR_START
#define KERNEL_VADDR_START ARCH_TEXT_OFFSET
#endif

#if defined(RT_USING_SMP) && RT_CPUS_NR > 1
#define MMU_PERCPU
#endif

#if __riscv_xlen == 32
#define VPN_BITS    10
#define VPN_MASK    0x3ffUL
#define PPN_MASK    0xfff00000UL
#define LEVEL_MAX   1
rt_weak rt_uint8_t rt_hw_arch_vaddr_width = 32;
#else
#define VPN_BITS    9
#define VPN_MASK    0x1ffUL
#define PPN_MASK    0x3ffffffffffc00UL
#define LEVEL_MAX   5
rt_weak rt_uint8_t rt_hw_arch_vaddr_width = 39;
#endif

struct mmu_level_info
{
    unsigned long *pos;
    void *page;
};

#ifdef MMU_PERCPU
#define PERCPU_OFFSET rt_hw_cpu_id() * ARCH_PAGE_SIZE
static struct mmu_level_info percpu_level[RT_CPUS_NR][LEVEL_MAX + 1];
#else
#define PERCPU_OFFSET 0
#endif

volatile unsigned long MMUTable[512 * RT_CPUS_NR] rt_align(ARCH_PAGE_SIZE);

static rt_uint8_t satp_level_4k, satp_level_2M;
static unsigned long satp_mode;

struct page_table
{
    unsigned long page[ARCH_PAGE_SIZE / sizeof(unsigned long)];
};
static struct page_table *__init_page_array;

void set_free_page(void *page_array)
{
    __init_page_array = page_array;
}

unsigned long get_free_page(void)
{
    static unsigned long page_off = 0UL;

    if (page_off < ARCH_PAGE_SIZE / sizeof(unsigned long))
    {
        return (unsigned long)(__init_page_array[page_off++].page);
    }

    return 0;
}

static int mmu_map_early(rt_ubase_t *tbl, rt_uint8_t max_level,
        rt_ubase_t va, rt_ubase_t pa, rt_ubase_t attr, rt_bool_t flush)
{
    unsigned long page, *table;
    rt_ubase_t off, level_shift;

    if (max_level == satp_level_2M)
    {
        if ((va & SUPPER_PAGE_MASK) || (pa & SUPPER_PAGE_MASK))
        {
            return MMU_MAP_ERROR_VANOTALIGN;
        }
    }
    else
    {
        if ((va & ARCH_PAGE_MASK) || (pa & ARCH_PAGE_MASK))
        {
            return MMU_MAP_ERROR_VANOTALIGN;
        }
    }

    table = tbl;
    level_shift = rt_hw_arch_vaddr_width - VPN_BITS;

    for (int level = 0; level < max_level; ++level)
    {
        off = (va >> level_shift) & VPN_MASK;

        if (!(table[off] & PTE_V))
        {
            if (!(page = get_free_page()))
            {
                return MMU_MAP_ERROR_NOPAGE;
            }

            rt_memset((void *)page, 0, ARCH_PAGE_SIZE);
            table[off] = ((page >> ARCH_PAGE_SHIFT) << PTE_BITS) | PTE_V;

            if (flush)
            {
                rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, table + off, sizeof(void *));
            }
        }

        if ((table[off] & PTE_ATTR_RWX) != 0)
        {
            /* No a page! */
            return MMU_MAP_ERROR_CONFLICT;
        }

        /* Step into the next level page table */
        page = (table[off] >> PTE_BITS) << ARCH_PAGE_SHIFT;
        table = (unsigned long *)page;

        level_shift -= VPN_BITS;
    }

    off = (va >> level_shift) & VPN_MASK;
    table[off] = ((pa >> ARCH_PAGE_SHIFT) << PTE_BITS) | attr;

    if (flush)
    {
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, table + off, sizeof(void *));
    }

    return 0;
}

#ifdef MMU_PERCPU
static int mmu_map_percpu_early(rt_ubase_t *tbl, rt_ubase_t *tbl_shadow,
                                rt_ubase_t va, rt_ubase_t pa)
{
    unsigned long page;
    rt_ubase_t off, level_shift;

    if (tbl == tbl_shadow)
    {
        return mmu_map_early(tbl, satp_level_4k, va, pa, MMU_MAP_K_RWCB, RT_FALSE);
    }

    level_shift = rt_hw_arch_vaddr_width - VPN_BITS;

    for (int level = 0; level < satp_level_4k; ++level)
    {
        rt_memcpy(tbl_shadow, tbl, ARCH_PAGE_SIZE);

        if (!(page = get_free_page()))
        {
            return MMU_MAP_ERROR_NOPAGE;
        }

        rt_memset((void *)page, 0, ARCH_PAGE_SIZE);

        off = (va >> level_shift) & VPN_MASK;
        tbl_shadow[off] = ((page >> ARCH_PAGE_SHIFT) << PTE_BITS) | PTE_V;

        /* Step into the next level page table */
        tbl = (unsigned long *)((tbl[off] >> PTE_BITS) << ARCH_PAGE_SHIFT);
        tbl_shadow = (unsigned long *)((tbl_shadow[off] >> PTE_BITS) << ARCH_PAGE_SHIFT);

        level_shift -= VPN_BITS;
    }

    off = (va >> level_shift) & VPN_MASK;
    tbl_shadow[off] = ((pa >> ARCH_PAGE_SHIFT) << PTE_BITS) | MMU_MAP_K_RWCB;

    return 0;
}
#endif /* MMU_PERCPU */

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
static rt_uint64_t _asid_acquire(rt_aspace_t aspace)
{
    static rt_uint32_t next_asid = 1;
    static rt_uint64_t global_asid_generation = BIT(SATP_ASID_BITS);

    if ((aspace->asid ^ global_asid_generation) >> SATP_ASID_BITS)
    {
        if (next_asid != MAX_ASID)
        {
            aspace->asid = global_asid_generation | next_asid++;
        }
        else
        {
            global_asid_generation += ASID_FIRST_GENERATION;
            next_asid = 1;
            rt_hw_tlb_invalidate_all_local();

            aspace->asid = global_asid_generation | next_asid++;
        }
    }

    return aspace->asid & SATP_ASID_MASK;
}

void rt_hw_aspace_switch(rt_aspace_t aspace)
{
    rt_uint64_t asid;
    uintptr_t page_table;

#ifdef MMU_PERCPU
    if (aspace == &rt_kernel_space)
#endif
    {
        page_table = (uintptr_t)rt_kmem_v2p(aspace->page_table + PERCPU_OFFSET);
    }
#ifdef MMU_PERCPU
    else
    {
        /* Just sync the per-CPU page */
        int cpu_id = rt_hw_cpu_id();
        unsigned long off = (unsigned long)percpu_level[cpu_id][0].pos;
        unsigned long *table = aspace->page_table, *table_shadow = percpu_level[cpu_id][0].page;

        table[off] = table_shadow[off];
    }
#endif /* MMU_PERCPU */

    asid = _asid_acquire(aspace);

    csr_write(satp, satp_mode | (asid << SATP_ASID_SHIFT) | ((rt_ubase_t)pgtbl >> ARCH_PAGE_SHIFT));

    SFENCE_VMA_ASID(asid);
}

#else /* !ARCH_USING_ASID */
void rt_hw_aspace_switch(rt_aspace_t aspace)
{
    uintptr_t page_table;

#ifdef MMU_PERCPU
    if (aspace == &rt_kernel_space)
#endif
    {
        page_table = (uintptr_t)rt_kmem_v2p(aspace->page_table + PERCPU_OFFSET);
    }
#ifdef MMU_PERCPU
    else
    {
        /* Just sync the per-CPU page */
        int cpu_id = rt_hw_cpu_id();
        unsigned long off = (unsigned long)percpu_level[cpu_id][0].pos;
        unsigned long *table = aspace->page_table, *table_shadow = percpu_level[cpu_id][0].page;

        table[off] = table_shadow[off];
    }
#endif /* MMU_PERCPU */

    csr_write(CSR_SATP, satp_mode | ((rt_ubase_t)page_table >> ARCH_PAGE_SHIFT));

    rt_hw_tlb_invalidate_all_local();
}
#endif /* ARCH_USING_ASID */

void rt_hw_mmu_tbl_set(unsigned long tbl)
{
    tbl += PERCPU_OFFSET;
    tbl += rt_kmem_pvoff();

    csr_write(CSR_SATP, satp_mode | (tbl >> ARCH_PAGE_SHIFT));

    rt_hw_tlb_invalidate_all_local();
}

void *rt_hw_mmu_tbl_get(void)
{
    rt_ubase_t satp = csr_read(CSR_SATP);

    return (void *)((satp & SATP_PPN) << ARCH_PAGE_SHIFT) - rt_kmem_pvoff();
}

void *rt_ioremap_early(void *paddr, size_t size)
{
    rt_ubase_t base;
    volatile size_t count;
    static void *tbl = RT_NULL;

    if (!size)
    {
        return RT_NULL;
    }

    if (!tbl)
    {
        tbl = rt_hw_mmu_tbl_get();
    }

    base = RT_ALIGN_DOWN((rt_size_t)paddr, SUPPER_PAGE_SIZE);
    count = RT_ALIGN((rt_ubase_t)paddr + size - base, SUPPER_PAGE_SIZE) / SUPPER_PAGE_SIZE;

    while (count --> 0)
    {
        if (mmu_map_early(tbl, satp_level_2M, base, base, MMU_MAP_K_DEVICE, RT_TRUE))
        {
            return RT_NULL;
        }

        base += SUPPER_PAGE_SIZE;
    }

    return paddr;
}

#ifdef MMU_PERCPU
static int _map_percpu_area(rt_ubase_t *table, void *va, void *pa, int cpu_id)
{
    unsigned long page;
    rt_ubase_t off, level_shift;

    level_shift = rt_hw_arch_vaddr_width - VPN_BITS;

    for (int level = 0; level < satp_level_4k; ++level)
    {
        if (!(page = (unsigned long)rt_pages_alloc(0)))
        {
            return MMU_MAP_ERROR_NOPAGE;
        }

        rt_memset((void *)page, 0, ARCH_PAGE_SIZE);

        off = ((rt_ubase_t)va >> level_shift) & VPN_MASK;
        table[off] = (((page + rt_kmem_pvoff()) >> ARCH_PAGE_SHIFT) << PTE_BITS) | PTE_V;

        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, table + off, sizeof(void *));

        percpu_level[cpu_id][level].page = (void *)table;
        percpu_level[cpu_id][level].pos = (unsigned long *)off;

        /* Step into the next level page table */
        table = (unsigned long *)(((table[off] >> PTE_BITS) << ARCH_PAGE_SHIFT) - rt_kmem_pvoff());

        level_shift -= VPN_BITS;
    }

    off = ((rt_ubase_t)va >> level_shift) & VPN_MASK;
    table[off] = (((rt_ubase_t)pa >> ARCH_PAGE_SHIFT) << PTE_BITS) | MMU_MAP_K_RWCB;

    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, table + off, sizeof(void *));

    percpu_level[cpu_id][satp_level_4k].page = (void *)table;
    percpu_level[cpu_id][satp_level_4k].pos = (unsigned long *)off;

    return ARCH_PAGE_SIZE;
}

static void percpu_map_sync(struct rt_aspace *aspace, int level, unsigned long *table, rt_ubase_t off)
{
    if (aspace == &rt_kernel_space &&
        percpu_level[0][level].page == table &&
        percpu_level[0][level].pos != (unsigned long *)off)
    {
        unsigned long *table_shadow;

        for (int i = 1; i < RT_CPUS_NR; ++i)
        {
            table_shadow = percpu_level[i][level].page;
            table_shadow[off] = table[off];

            rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, table_shadow + off, sizeof(void *));
        }
    }
}

static void percpu_mmu_init_check(void)
{
    size_t mapped, size;
    void *page_table, *vaddr, *paddr;
    static rt_bool_t inited = RT_FALSE;

    if (inited)
    {
        return;
    }
    inited = RT_TRUE;

    page_table = rt_kernel_space.page_table;

    for (int cpu_id = 0; cpu_id < RT_CPUS_NR; ++cpu_id)
    {
        vaddr = &__percpu_start;
        paddr = vaddr + rt_kmem_pvoff();
        size = (size_t)(&__percpu_end - &__percpu_start);
        /* Offset to per-CPU partition for current CPU */
        paddr += size * cpu_id;

        while (size > 0)
        {
            MM_PGTBL_LOCK(&rt_kernel_space);
            mapped = _map_percpu_area(page_table, vaddr, paddr, cpu_id);
            MM_PGTBL_UNLOCK(&rt_kernel_space);

            RT_ASSERT(mapped > 0);

            size -= mapped;
            vaddr += mapped;
            paddr += mapped;
        }

        page_table += ARCH_PAGE_SIZE;
    }
}
#endif /* MMU_PERCPU */

static size_t _map_area(struct rt_aspace *aspace, void *va, void *pa,
                        size_t attr, size_t max_size)
{
    rt_uint8_t max_level;
    unsigned long page, *table;
    rt_ubase_t off, level_shift;

    if (max_size >= SUPPER_PAGE_SIZE &&
        !((rt_ubase_t)va & SUPPER_PAGE_MASK) &&
        !((rt_ubase_t)pa & SUPPER_PAGE_MASK))
    {
        max_level = satp_level_2M;
        max_size = SUPPER_PAGE_SIZE;
    }
    else
    {
        max_level = satp_level_4k;
        max_size = ARCH_PAGE_SIZE;
    }

    table = aspace->page_table;
    level_shift = rt_hw_arch_vaddr_width - VPN_BITS;

    for (int level = 0; level < max_level; ++level)
    {
        off = ((rt_ubase_t)va >> level_shift) & VPN_MASK;

        if (!(table[off] & PTE_V))
        {
            if (!(page = (unsigned long)rt_pages_alloc(0)))
            {
                return MMU_MAP_ERROR_NOPAGE;
            }

            rt_memset((void *)page, 0, ARCH_PAGE_SIZE);
            table[off] = (((page + rt_kmem_pvoff()) >> ARCH_PAGE_SHIFT) << PTE_BITS) | PTE_V;

            rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, table + off, sizeof(void *));
        }
        else
        {
            page = (table[off] >> PTE_BITS) << ARCH_PAGE_SHIFT;
            page -= rt_kmem_pvoff();

            rt_page_ref_inc((void *)page, 0);
        }

        if ((table[off] & PTE_ATTR_RWX) != 0)
        {
            /* No a page! */
            return MMU_MAP_ERROR_CONFLICT;
        }

    #ifdef MMU_PERCPU
        percpu_map_sync(aspace, level, table, off);
    #endif

        /* Step into the next level page table */
        page = (table[off] >> PTE_BITS) << ARCH_PAGE_SHIFT;
        table = (unsigned long *)(page - rt_kmem_pvoff());

        level_shift -= VPN_BITS;
    }

    off = ((rt_ubase_t)va >> level_shift) & VPN_MASK;
    table[off] = (((rt_ubase_t)pa >> ARCH_PAGE_SHIFT) << PTE_BITS) | attr;

    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, table + off, sizeof(void *));

#ifdef MMU_PERCPU
    percpu_map_sync(aspace, max_level, table, off);
#endif

    return max_size;
}

static size_t _unmap_area(struct rt_aspace *aspace, void *va, size_t max_size)
{
    int level, ref;
    rt_ubase_t off, level_shift;
    unsigned long page, *table, *pos;
    struct mmu_level_info level_info[LEVEL_MAX];

    rt_memset(level_info, 0, sizeof(level_info));

    table = aspace->page_table;
    level_shift = rt_hw_arch_vaddr_width - VPN_BITS;

    /* Max level is 4k */
    for (level = 0; level <= satp_level_4k; ++level)
    {
        off = ((rt_ubase_t)va >> level_shift) & VPN_MASK;
        page = table[off];

        if (!(page & PTE_V))
        {
            break;
        }

        if ((page & PTE_ATTR_RWX) != 0)
        {
            /* No a page! */
            break;
        }

        level_info[level].pos = table + off;

        /* Step into the next level page table */
        page = (page >> PTE_BITS) << ARCH_PAGE_SHIFT;
        table = (unsigned long *)(page - rt_kmem_pvoff());

        level_info[level].page = table;

        level_shift -= VPN_BITS;
    }

    if (level == satp_level_4k)
    {
        max_size = ARCH_PAGE_SIZE;
    }
    else
    {
        max_size = SUPPER_PAGE_SIZE;
    }

    level = satp_level_4k;
    pos = level_info[level].pos;
    if (pos)
    {
        *pos = (unsigned long)RT_NULL;
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, pos, sizeof(void *));
    }
    --level;

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

            #ifdef MMU_PERCPU
                table = percpu_level[0][level].page;

                if (pos >= table && pos < table + (ARCH_PAGE_SIZE / sizeof(unsigned long)))
                {
                    percpu_map_sync(aspace, level, table, pos - table);
                }
            #endif /* MMU_PERCPU */
            }

            rt_pages_free(cur_page, 0);
        }
        else
        {
            break;
        }

        --level;
    }

    return max_size;
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
    size_t mapped;
    void *unmap_va = v_addr;

#ifdef MMU_PERCPU
    percpu_mmu_init_check();
#endif

    while (size > 0)
    {
    #ifdef MMU_PERCPU
        if (v_addr < (void *)&__percpu_start ||
            v_addr >= (void *)&__percpu_real_end)
    #endif
        {
            MM_PGTBL_LOCK(aspace);
            mapped = _map_area(aspace, v_addr, p_addr, attr, size);
            MM_PGTBL_UNLOCK(aspace);
        }
    #ifdef MMU_PERCPU
        else
        {
            /* Make the kernel skip the per-CPU as soon as possible */
            mapped = size > SUPPER_PAGE_SIZE ? SUPPER_PAGE_SIZE : size;
        }
    #endif /* MMU_PERCPU */

        if (mapped && mapped <= size)
        {
            size -= mapped;
            v_addr += mapped;
            p_addr += mapped;

            continue;
        }

        /* Error, undo map */
        while (unmap_va != v_addr)
        {
            MM_PGTBL_LOCK(aspace);
            mapped = _unmap_area(aspace, unmap_va, size);
            MM_PGTBL_UNLOCK(aspace);

            unmap_va += mapped;
        }

        break;
    }

    return unmap_va;
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
    size_t unmapped;

    /* caller guarantee that v_addr & size are page aligned */
    if (!aspace->page_table)
    {
        return;
    }

    while (size > 0)
    {
        MM_PGTBL_LOCK(aspace);
        unmapped = _unmap_area(aspace, v_addr, size);
        MM_PGTBL_UNLOCK(aspace);

        if (unmapped && unmapped <= size)
        {
            size -= unmapped;
            v_addr += unmapped;

            continue;
        }

        /* Region not exist in pgtbl */
        break;
    }
}

rt_inline void _init_region(void *vaddr, size_t size)
{
    rt_ioremap_start = vaddr;
    rt_ioremap_size = size;
    rt_mpr_start = rt_ioremap_start - rt_mpr_size;
    LOG_D("rt_ioremap_start: %p, rt_mpr_start: %p", rt_ioremap_start,
          rt_mpr_start);
}

rt_inline rt_ubase_t get_top_vpn(rt_ubase_t va, rt_uint8_t satp_level)
{
    return (va >> (VPN_BITS * satp_level + 12)) & VPN_MASK;
}

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
    rt_size_t off, va_s, va_e;

    if ((!aspace) || (!vtable))
    {
        return -1;
    }

    va_s = (rt_ubase_t)v_address;
    va_e = (rt_ubase_t)v_address + size - 1;

    if (va_e < va_s)
    {
        return -1;
    }

    /* convert address to top-level index */
    va_s = get_top_vpn(va_s, satp_level_4k);
    va_e = get_top_vpn(va_e, satp_level_4k);

    if (va_s == 0)
    {
        return -1;
    }

    /* vtable initialization check */
    for (off = va_s; off <= va_e; off++)
    {
        rt_size_t v = vtable[off];

        if (v)
        {
            return -1;
        }
    }

    rt_aspace_init(aspace, (void *)KERNEL_VADDR_START, 0UL - KERNEL_VADDR_START,
                   vtable);

    _init_region(v_address, size);

    return 0;
}

static void *mmu_v2p(void *tbl, void *vaddr, int *out_level, rt_base_t **out_pte)
{
    unsigned long page, entry;
    rt_ubase_t off, level_shift, pa, va = (unsigned long)vaddr, *table = (unsigned long *)tbl;

#ifdef MMU_PERCPU
    if (tbl == rt_kernel_space.page_table)
    {
        table = (unsigned long *)(tbl + PERCPU_OFFSET);
    }
#endif /* MMU_PERCPU */

    /* Calculate initial shift based on virtual address width */
    level_shift = rt_hw_arch_vaddr_width - VPN_BITS;

    /* 4k is the max level, translate to the last level */
    for (*out_level = 0; *out_level <= satp_level_4k; ++(*out_level))
    {
        /* Extract VPN (Virtual Page Number) for this level */
        off = (va >> level_shift) & VPN_MASK;
        /* Fetch the page table entry */
        entry = table[off];

        /* If entry is invalid (V bit not set), address translation fails */
        if (!(entry & PTE_V))
        {
            goto _translate_fail;
        }

        /* If entry has any RWX permission bits set, it is a leaf entry */
        if (entry & PTE_ATTR_RWX)
        {
            if (out_pte)
            {
                *out_pte = table + off;
            }

            /* Extract physical page base address and add page offset */
            pa = ((entry >> PTE_BITS) << ARCH_PAGE_SHIFT);

            if (*out_level >= satp_level_4k)
            {
                pa |= va & ARCH_PAGE_MASK;
            }
            else
            {
                pa |= va & SUPPER_PAGE_MASK;
            }

            return (void *)pa;
        }

        /* Otherwise, walk to the next level page table */
        page = (entry >> PTE_BITS) << ARCH_PAGE_SHIFT;
        table = (unsigned long *)(page - rt_kmem_pvoff());

        level_shift -= VPN_BITS;
    }

_translate_fail:
    /* If reached here, it is not a valid mapped address */
    LOG_D("%s: failed at %p", __func__, vaddr);
    return ARCH_MAP_FAILED;
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
 * @note The function queries the page table entry (PTE) for the virtual address using `mmu_v2p`.
 *       If a valid PTE is found, the physical address is extracted and combined with the offset
 *       from the virtual address. If no valid PTE is found, a debug log is recorded, and
 *       `ARCH_MAP_FAILED` is returned.
 */
void *rt_hw_mmu_v2p(struct rt_aspace *aspace, void *vaddr)
{
    int level;

    return mmu_v2p(aspace->page_table, vaddr, &level, RT_NULL);
}

static int _noncache(rt_base_t *pte)
{
    rt_ubase_t entry;

    if (!riscv_isa_ext_test(SVPBMT))
    {
        return -RT_ENOSYS;
    }

    entry = *pte;
    *pte = (entry & ~PTE_VENDOR_MTMASK) | PTE_VENDOR_NOCACHE;

    return 0;
}

static int _cache(rt_base_t *pte)
{
    rt_ubase_t entry;

    if (!riscv_isa_ext_test(SVPBMT))
    {
        return -RT_ENOSYS;
    }

    entry = *pte;
    *pte = (entry & ~PTE_VENDOR_MTMASK) | PTE_VENDOR_PMA;

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
            void *range_end;
            rt_base_t *pte = RT_NULL;

            mmu_v2p(aspace->page_table, vaddr, &level, &pte);

            if (level == satp_level_4k)
            {
                range_end = vaddr + ARCH_PAGE_SIZE;
            }
            else if (level == satp_level_2M)
            {
                range_end = vaddr + SUPPER_PAGE_SIZE;
            }
            else
            {
                /* 1G or larger is not supported. */
                RT_ASSERT(0);
            }

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

    for (size_t i = 0; i < desc_nr; ++i)
    {
        size_t attr;
        struct rt_mm_va_hint hint =
        {
            .flags = MMF_MAP_FIXED,
            .limit_start = aspace->start,
            .limit_range_size = aspace->size,
            .map_size = mdesc->vaddr_end - mdesc->vaddr_start + 1,
            .prefer = (void *)mdesc->vaddr_start
        };

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

        if (mdesc->paddr_start == (rt_uintptr_t)ARCH_MAP_FAILED)
        {
            mdesc->paddr_start = mdesc->vaddr_start + rt_kmem_pvoff();
        }

        rt_aspace_map_phy_static(aspace, &mdesc->varea, &hint, attr,
                                 mdesc->paddr_start >> MM_PAGE_SHIFT, &err);
        mdesc++;
    }

    rt_hw_mmu_tbl_set((unsigned long)rt_kernel_space.page_table);
    rt_page_cleanup();
}

/**
 * @brief Early memory setup function for hardware initialization.
 *
 * This function performs early memory setup tasks, including:
 * - Calculating the physical-to-virtual (PV) offset.
 * - Setting up initial page tables for identity mapping and text region relocation.
 * - Applying new memory mappings by updating the SATP register.
 *
 * @note This function is typically called during the early stages of system initialization (startup_gcc.S),
 *       before the memory management system is fully operational.
 */
void rt_hw_mem_setup_early(rt_ubase_t vaddr_start, rt_ubase_t paddr_start, void *pgtbl)
{
    extern char __text_start, __text_end;

    rt_size_t size = ARCH_EARLY_MAP_SIZE;
    rt_ubase_t *early_pgtbl = pgtbl, paddr_end = paddr_start + size;

    rt_kmem_pvoff_set(paddr_start - vaddr_start);

    switch (rt_hw_arch_vaddr_width)
    {
    case 0:
        satp_mode = SATP_MODE_BARE;
        satp_level_4k = 0;
        satp_level_2M = 0;
    #ifdef RT_USING_SMART
        RT_ASSERT(0);
    #else
        RT_ASSERT(paddr_start == vaddr_start);
    #endif
        /* Do nothing */
        return;
#if __riscv_xlen != 32
    case 64:
        satp_mode = SATP_MODE_64;
        satp_level_4k = 5;
        satp_level_2M = 4;
        break;
    case 57:
        satp_mode = SATP_MODE_57;
        satp_level_4k = 4;
        satp_level_2M = 3;
        break;
    case 48:
        satp_mode = SATP_MODE_48;
        satp_level_4k = 3;
        satp_level_2M = 2;
        break;
    case 39:
    default:
        satp_mode = SATP_MODE_39;
        satp_level_4k = 2;
        satp_level_2M = 1;
        rt_hw_arch_vaddr_width = 39;
#else
    case 32:
    default:
        satp_mode = SATP_MODE_32;
        satp_level_4k = 1;
        satp_level_2M = 0;
        rt_hw_arch_vaddr_width = 32;
#endif /* __riscv_xlen != 32 */
        break;
    }

    vaddr_start = RT_ALIGN_DOWN(vaddr_start, SUPPER_PAGE_SIZE);
    paddr_start = RT_ALIGN_DOWN(paddr_start, SUPPER_PAGE_SIZE);
    paddr_end = RT_ALIGN(paddr_end, SUPPER_PAGE_SIZE);

    rt_memset(early_pgtbl, 0, RT_CPUS_NR * ARCH_PAGE_SIZE);

    if (!rt_kmem_pvoff())
    {
        goto _map_vaddress;
    }

    /* Identical mapping, only map for 'text' */
    size = RT_ALIGN((rt_ubase_t)(&__text_end - &__text_start), SUPPER_PAGE_SIZE);

    /* Check whether the virtual address area and identical area overlap */
    RT_ASSERT(size < rt_kmem_pvoff());

    for (rt_ssize_t pages = size / SUPPER_PAGE_SIZE; pages > 0; --pages)
    {
        mmu_map_early(early_pgtbl, satp_level_2M, paddr_start, paddr_start, MMU_MAP_K_RWCB, RT_FALSE);

        paddr_start += SUPPER_PAGE_SIZE;
    }

    /* Page array for map early */
    paddr_start = RT_ALIGN_DOWN((rt_ubase_t)early_pgtbl, SUPPER_PAGE_SIZE);
    mmu_map_early(early_pgtbl, satp_level_2M, paddr_start, paddr_start, MMU_MAP_K_RWCB, RT_FALSE);

    if ((rt_ubase_t)__init_page_array - paddr_start >= SUPPER_PAGE_SIZE)
    {
        paddr_start = RT_ALIGN_DOWN((rt_ubase_t)__init_page_array, SUPPER_PAGE_SIZE);
        mmu_map_early(early_pgtbl, satp_level_2M, paddr_start, paddr_start, MMU_MAP_K_RWCB, RT_FALSE);
    }

_map_vaddress:
    /* Virtual mapping */
    while (paddr_start < paddr_end)
    {
    #ifdef MMU_PERCPU
        if (paddr_start < (rt_ubase_t)&__percpu_start ||
            paddr_start >= (rt_ubase_t)&__percpu_real_end)
    #endif
        {
            mmu_map_early(early_pgtbl, satp_level_2M, vaddr_start, paddr_start, MMU_MAP_K_RWCB, RT_FALSE);
        }

        paddr_start += SUPPER_PAGE_SIZE;
        vaddr_start += SUPPER_PAGE_SIZE;
    }

#ifdef MMU_PERCPU
    for (int cpu_id = 0; cpu_id < RT_CPUS_NR; ++cpu_id)
    {
        paddr_start = (rt_ubase_t)&__percpu_start;
        vaddr_start = paddr_start - rt_kmem_pvoff();
        size = (rt_size_t)(&__percpu_end - &__percpu_start);
        /* Offset to per-CPU partition for current CPU */
        paddr_start += cpu_id * size;
        paddr_end = paddr_start + size;

        while (paddr_start < paddr_end)
        {
            /* Map physical address per-CPU partition */
            mmu_map_percpu_early(early_pgtbl, (void *)early_pgtbl + cpu_id * ARCH_PAGE_SIZE, vaddr_start, paddr_start);

            paddr_start += ARCH_PAGE_SIZE;
            vaddr_start += ARCH_PAGE_SIZE;
        }
    }
#endif /* MMU_PERCPU */
}

rt_ubase_t mmu_satp_load(void *pgtbl, rt_ubase_t hartid)
{
#ifdef MMU_PERCPU
    pgtbl += riscv_hartid_to_cpu_id(hartid) * ARCH_PAGE_SIZE;
#endif

    return satp_mode | ((rt_ubase_t)pgtbl >> ARCH_PAGE_SHIFT);
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
