/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-25     GuEe-GUI     first version
 */

/**
 * @file mem.c
 * @brief PCI Endpoint memory allocator
 *
 * Manages the endpoint's local memory pool used for exposing memory
 * regions to the PCIe host. Uses a bitmap-based allocator to track
 * free/used pages within the endpoint's address space.
 *
 * This is needed for:
 * - BAR memory backing
 * - MSI/MSI-X message memory
 * - DMA buffer allocation visible to the host
 */

#include <drivers/pci_endpoint.h>

#define DBG_TAG "pci.ep.mem"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/**
 * @brief Initialize an array of memory regions for an endpoint
 *
 * Each memory region is described by a CPU physical address, size,
 * and page size. A bitmap is allocated for each region to track page usage.
 *
 * @param[in] ep       PCI endpoint controller
 * @param[in] mems     Array of memory region descriptors
 * @param[in] mems_nr  Number of regions in the array
 * @return RT_EOK on success, -RT_ENOMEM on allocation failure
 */
rt_err_t rt_pci_ep_mem_array_init(struct rt_pci_ep *ep,
        struct rt_pci_ep_mem *mems, rt_size_t mems_nr)
{
    rt_size_t idx;
    rt_err_t err = RT_EOK;

    if (!ep || !mems)
    {
        return -RT_EINVAL;
    }

    rt_mutex_take(&ep->lock, RT_WAITING_FOREVER);

    ep->mems_nr = mems_nr;
    ep->mems = rt_calloc(mems_nr, sizeof(*ep->mems));

    if (!ep->mems)
    {
        return -RT_ENOMEM;
    }

    for (idx = 0; idx < mems_nr; ++idx)
    {
        struct rt_pci_ep_mem *mem = &ep->mems[idx];

        mem->cpu_addr = mems->cpu_addr;
        mem->size = mems->size;
        mem->page_size = mems->page_size;
        mem->bits = mems->size / mems->page_size;
        mem->map = rt_calloc(RT_BITMAP_LEN(mem->bits), sizeof(*mem->map));

        if (!mem->map)
        {
            err = -RT_ENOMEM;
            goto _out_lock;
        }
    }

_out_lock:
    if (err)
    {
        while (idx --> 0)
        {
            rt_free(ep->mems[idx].map);
        }
        rt_free(ep->mems);

        ep->mems_nr = 0;
        ep->mems = RT_NULL;
    }

    rt_mutex_release(&ep->lock);

    return err;
}

/**
 * @brief Initialize a single memory region for an endpoint
 *
 * Convenience wrapper around rt_pci_ep_mem_array_init() for a single region.
 *
 * @param[in] ep        PCI endpoint controller
 * @param[in] cpu_addr  CPU physical base address of the region
 * @param[in] size      Total size of the region in bytes
 * @param[in] page_size Allocation granularity (page size) in bytes
 * @return RT_EOK on success
 */
rt_err_t rt_pci_ep_mem_init(struct rt_pci_ep *ep,
        rt_ubase_t cpu_addr, rt_size_t size, rt_size_t page_size)
{
    struct rt_pci_ep_mem mem;

    if (!ep)
    {
        return -RT_EINVAL;
    }

    mem.cpu_addr = cpu_addr;
    mem.size = size;
    mem.page_size = page_size;

    return rt_pci_ep_mem_array_init(ep, &mem, 1);
}

/**
 * @brief Allocate a contiguous range of pages from a memory region
 *
 * Uses a first-fit bitmap scan. Each page is represented by one bit
 * in the region's bitmap. Allocated pages are marked as used.
 *
 * @param[in] mem  PCI EP memory region to allocate from
 * @param[in] size Allocation size in bytes (must be page-aligned)
 * @return CPU physical address of the allocated range, or ~0ULL on failure
 */
static rt_ubase_t bitmap_region_alloc(struct rt_pci_ep_mem *mem, rt_size_t size)
{
    rt_size_t bit, next_bit, end_bit, max_bits;

    size /= mem->page_size;
    max_bits = mem->bits - size;

    rt_bitmap_for_each_clear_bit(mem->map, bit, max_bits)
    {
        end_bit = bit + size;

        for (next_bit = bit + 1; next_bit < end_bit; ++next_bit)
        {
            if (rt_bitmap_test_bit(mem->map, next_bit))
            {
                bit = next_bit;
                goto _next;
            }
        }

        if (next_bit == end_bit)
        {
            while (next_bit --> bit)
            {
                rt_bitmap_set_bit(mem->map, next_bit);
            }

            return mem->cpu_addr + bit * mem->page_size;
        }
    _next:
        ;
    }

    return ~0ULL;
}

/**
 * @brief Free a previously allocated range of pages
 *
 * Clears the bits in the region's bitmap for the freed pages.
 *
 * @param[in] mem      PCI EP memory region
 * @param[in] cpu_addr CPU physical address of the allocation
 * @param[in] size     Size of the allocation in bytes
 */
static void bitmap_region_free(struct rt_pci_ep_mem *mem,
        rt_ubase_t cpu_addr, rt_size_t size)
{
    rt_size_t bit = (cpu_addr - mem->cpu_addr) / mem->page_size, end_bit;

    size /= mem->page_size;
    end_bit = bit + size;

    for (; bit < end_bit; ++bit)
    {
        rt_bitmap_clear_bit(mem->map, bit);
    }
}

/**
 * @brief Allocate memory from the endpoint's pool
 *
 * Iterates through all registered memory regions and tries to
 * allocate a contiguous range. On success, also maps the physical
 * address to a kernel virtual address via rt_ioremap().
 *
 * @param[in]  ep           PCI endpoint controller
 * @param[out] out_cpu_addr CPU physical address of the allocation
 * @param[in]  size         Allocation size in bytes
 * @return Kernel virtual address, or RT_NULL on failure
 */
void *rt_pci_ep_mem_alloc(struct rt_pci_ep *ep,
        rt_ubase_t *out_cpu_addr, rt_size_t size)
{
    void *vaddr = RT_NULL;

    if (!ep || !out_cpu_addr)
    {
        return vaddr;
    }

    rt_mutex_take(&ep->lock, RT_WAITING_FOREVER);

    for (rt_size_t idx = 0; idx < ep->mems_nr; ++idx)
    {
        rt_ubase_t cpu_addr;
        struct rt_pci_ep_mem *mem = &ep->mems[idx];

        cpu_addr = bitmap_region_alloc(mem, size);

        if (cpu_addr != ~0ULL)
        {
            vaddr = rt_ioremap((void *)cpu_addr, size);

            if (!vaddr)
            {
                bitmap_region_free(mem, cpu_addr, size);

                /* Try next memory */
                continue;
            }

            *out_cpu_addr = cpu_addr;
            break;
        }
    }

    rt_mutex_release(&ep->lock);

    return vaddr;
}

/**
 * @brief Free memory from the endpoint's pool
 *
 * Finds the memory region containing the allocation (by checking
 * if the address falls within each region's range), unmaps the
 * virtual address, and frees the bitmap pages.
 *
 * @param[in] ep       PCI endpoint controller
 * @param[in] vaddr    Kernel virtual address to free (unmapped)
 * @param[in] cpu_addr CPU physical address of the allocation
 * @param[in] size     Size of the allocation in bytes
 */
void rt_pci_ep_mem_free(struct rt_pci_ep *ep,
        void *vaddr, rt_ubase_t cpu_addr, rt_size_t size)
{
    if (!ep || !vaddr || !size)
    {
        return;
    }

    rt_mutex_take(&ep->lock, RT_WAITING_FOREVER);

    for (rt_size_t idx = 0; idx < ep->mems_nr; ++idx)
    {
        struct rt_pci_ep_mem *mem = &ep->mems[idx];

        if (mem->cpu_addr > cpu_addr &&
            mem->cpu_addr + mem->size >= cpu_addr + size)
        {
            rt_iounmap(mem);
            bitmap_region_free(mem, cpu_addr, size);

            break;
        }
    }

    rt_mutex_release(&ep->lock);
}
