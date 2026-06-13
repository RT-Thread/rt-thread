/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
 */

/**
 * @file dma_pool.c
 * @brief DMA memory pool and buffer allocation framework
 *
 * Manages DMA-capable memory regions (coherent pool and CMA) for
 * allocating DMA buffers. Provides coherent and non-coherent buffer
 * allocation with optional device tree "memory-region" integration,
 * cache synchronization via the rt_dma_map_ops interface, and a
 * bitmap-based page allocator within DMA pools.
 *
 * Pools are organized as:
 * - coherent-pool: smaller pool for cache-coherent DMA (ioremap_cached)
 * - CMA (Contiguous Memory Allocator): larger pool for general DMA
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "dma.pool"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <mm_aspace.h>
#include <mm_memblock.h>
#include <dt-bindings/size.h>

static RT_DEFINE_SPINLOCK(dma_pools_lock);
static rt_list_t dma_pool_nodes = RT_LIST_OBJECT_INIT(dma_pool_nodes);

static struct rt_dma_pool *dma_pool_install(rt_region_t *region);

static void *dma_alloc(struct rt_device *dev, rt_size_t size,
                       rt_ubase_t *dma_handle, rt_ubase_t flags);
static void dma_free(struct rt_device *dev, rt_size_t size,
                     void *cpu_addr, rt_ubase_t dma_handle, rt_ubase_t flags);

/** @brief Acquire the DMA pool spinlock */
rt_inline void region_pool_lock(void)
{
    rt_hw_spin_lock(&dma_pools_lock.lock);
}

/** @brief Release the DMA pool spinlock */
rt_inline void region_pool_unlock(void)
{
    rt_hw_spin_unlock(&dma_pools_lock.lock);
}

/**
 * @brief Synchronize output data for a coherent DMA device
 *
 * Converts the virtual address to a physical DMA handle and flushes
 * the CPU data cache to ensure the DMA engine sees the latest data.
 *
 * @param[in]  dev        DMA-capable device
 * @param[in]  data       Virtual address of the data buffer
 * @param[in]  size       Buffer size in bytes
 * @param[out] dma_handle Physical DMA address (filled if non-NULL)
 * @param[in]  flags      Allocation flags (unused)
 *
 * @return RT_EOK
 */
static rt_err_t dma_map_coherent_sync_out_data(struct rt_device *dev,
                                               void *data, rt_size_t size, rt_ubase_t *dma_handle, rt_ubase_t flags)
{
    if (dma_handle)
    {
        *dma_handle = (rt_ubase_t)rt_kmem_v2p(data);
    }
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, data, size);

    return RT_EOK;
}

/**
 * @brief Synchronize input data for a coherent DMA device
 *
 * Invalidates the CPU data cache so the CPU sees the data written
 * by the DMA engine.
 *
 * @param[in] dev        DMA-capable device
 * @param[in] out_data   Virtual address of the data buffer
 * @param[in] size       Buffer size in bytes
 * @param[in] dma_handle Physical DMA address (unused)
 * @param[in] flags      Allocation flags (unused)
 *
 * @return RT_EOK
 */
static rt_err_t dma_map_coherent_sync_in_data(struct rt_device *dev,
                                              void *out_data, rt_size_t size, rt_ubase_t dma_handle, rt_ubase_t flags)
{
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, out_data, size);

    return RT_EOK;
}

/** @brief DMA map operations for cache-coherent devices */
static const struct rt_dma_map_ops dma_map_coherent_ops = {
    .sync_out_data = dma_map_coherent_sync_out_data,
    .sync_in_data = dma_map_coherent_sync_in_data,
};

/**
 * @brief Synchronize output data for a non-coherent DMA device
 *
 * Converts virtual address to physical DMA handle. No cache flush
 * is performed since the memory is non-cacheable.
 *
 * @param[in]  dev        DMA-capable device
 * @param[in]  data       Virtual address of the data buffer
 * @param[in]  size       Buffer size in bytes
 * @param[out] dma_handle Physical DMA address (filled if non-NULL)
 * @param[in]  flags      Allocation flags (unused)
 *
 * @return RT_EOK
 */
static rt_err_t dma_map_nocoherent_sync_out_data(struct rt_device *dev,
                                                 void *data, rt_size_t size, rt_ubase_t *dma_handle, rt_ubase_t flags)
{
    if (dma_handle)
    {
        *dma_handle = (rt_ubase_t)rt_kmem_v2p(data);
    }

    return RT_EOK;
}

/**
 * @brief Synchronize input data for a non-coherent DMA device
 *
 * No cache operations needed for non-cacheable memory.
 *
 * @param[in] dev        DMA-capable device
 * @param[in] out_data   Virtual address of the data buffer
 * @param[in] size       Buffer size in bytes
 * @param[in] dma_handle Physical DMA address (unused)
 * @param[in] flags      Allocation flags (unused)
 *
 * @return RT_EOK
 */
static rt_err_t dma_map_nocoherent_sync_in_data(struct rt_device *dev,
                                                void *out_data, rt_size_t size, rt_ubase_t dma_handle, rt_ubase_t flags)
{
    return RT_EOK;
}

/** @brief DMA map operations for non-cache-coherent devices */
static const struct rt_dma_map_ops dma_map_nocoherent_ops = {
    .sync_out_data = dma_map_nocoherent_sync_out_data,
    .sync_in_data = dma_map_nocoherent_sync_in_data,
};

#ifdef RT_USING_OFW

/**
 * @brief Translate a CPU address to a DMA address via device tree
 *
 * @param[in] dev  Device with an ofw_node
 * @param[in] addr CPU physical address
 *
 * @return DMA address
 */
rt_inline rt_ubase_t ofw_addr_cpu2dma(struct rt_device *dev, rt_ubase_t addr)
{
    return (rt_ubase_t)rt_ofw_translate_cpu2dma(dev->ofw_node, addr);
}

/**
 * @brief Translate a DMA address to a CPU address via device tree
 *
 * @param[in] dev  Device with an ofw_node
 * @param[in] addr DMA address
 *
 * @return CPU physical address
 */
rt_inline rt_ubase_t ofw_addr_dma2cpu(struct rt_device *dev, rt_ubase_t addr)
{
    return (rt_ubase_t)rt_ofw_translate_dma2cpu(dev->ofw_node, addr);
}

/**
 * @brief Allocate a DMA buffer and translate to DMA address space
 *
 * @param[in]  dev        DMA-capable device
 * @param[in]  size       Requested size in bytes
 * @param[out] dma_handle DMA address (device tree translated)
 * @param[in]  flags      Allocation flags
 *
 * @return Virtual address of the buffer, or RT_NULL on failure
 */
static void *ofw_dma_map_alloc(struct rt_device *dev, rt_size_t size,
                               rt_ubase_t *dma_handle, rt_ubase_t flags)
{
    void *cpu_addr = dma_alloc(dev, size, dma_handle, flags);

    if (cpu_addr && dma_handle)
    {
        *dma_handle = ofw_addr_cpu2dma(dev, *dma_handle);
    }

    return cpu_addr;
}

/**
 * @brief Free a DMA buffer, translating DMA address back to CPU space
 *
 * @param[in] dev        DMA-capable device
 * @param[in] size       Buffer size in bytes
 * @param[in] cpu_addr   Virtual address of the buffer
 * @param[in] dma_handle DMA address (will be translated back to CPU)
 * @param[in] flags      Allocation flags
 */
static void ofw_dma_map_free(struct rt_device *dev, rt_size_t size,
                             void *cpu_addr, rt_ubase_t dma_handle, rt_ubase_t flags)
{
    dma_handle = ofw_addr_dma2cpu(dev, dma_handle);

    dma_free(dev, size, cpu_addr, dma_handle, flags);
}

/**
 * @brief Sync output data with device tree DMA address translation
 *
 * Chooses coherent or non-coherent sync based on RT_DMA_F_NOCACHE flag,
 * then translates the DMA handle to device bus address space.
 *
 * @param[in]  dev        DMA-capable device
 * @param[in]  data       Virtual address of the data buffer
 * @param[in]  size       Buffer size in bytes
 * @param[out] dma_handle DMA address (translated)
 * @param[in]  flags      Sync flags
 *
 * @return RT_EOK on success
 */
static rt_err_t ofw_dma_map_sync_out_data(struct rt_device *dev,
                                          void *data, rt_size_t size,
                                          rt_ubase_t *dma_handle, rt_ubase_t flags)
{
    rt_err_t err;

    if (flags & RT_DMA_F_NOCACHE)
    {
        err = dma_map_nocoherent_sync_out_data(dev, data, size, dma_handle, flags);
    }
    else
    {
        err = dma_map_coherent_sync_out_data(dev, data, size, dma_handle, flags);
    }

    if (!err && dma_handle)
    {
        *dma_handle = ofw_addr_cpu2dma(dev, *dma_handle);
    }

    return err;
}

/**
 * @brief Sync input data with device tree DMA address back-translation
 *
 * Translates the DMA handle from bus address space back to CPU space,
 * then performs coherent or non-coherent cache invalidation.
 *
 * @param[in] dev        DMA-capable device
 * @param[in] out_data   Virtual address of the data buffer
 * @param[in] size       Buffer size in bytes
 * @param[in] dma_handle DMA address (translated back from bus space)
 * @param[in] flags      Sync flags
 *
 * @return RT_EOK on success
 */
static rt_err_t ofw_dma_map_sync_in_data(struct rt_device *dev,
                                         void *out_data, rt_size_t size,
                                         rt_ubase_t dma_handle, rt_ubase_t flags)
{
    dma_handle = ofw_addr_dma2cpu(dev, dma_handle);

    if (flags & RT_DMA_F_NOCACHE)
    {
        return dma_map_nocoherent_sync_in_data(dev, out_data, size, dma_handle, flags);
    }

    return dma_map_coherent_sync_in_data(dev, out_data, size, dma_handle, flags);
}

/** @brief DMA map operations with device tree address translation */
static const struct rt_dma_map_ops ofw_dma_map_ops = {
    .alloc = ofw_dma_map_alloc,
    .free = ofw_dma_map_free,
    .sync_out_data = ofw_dma_map_sync_out_data,
    .sync_in_data = ofw_dma_map_sync_in_data,
};

/**
 * @brief Determine DMA operations for a device tree device with memory-region
 *
 * Parses the "memory-region" property to install DMA pools from
 * reserved-memory nodes. Sets RT_DMA_F_NOMAP if "no-map" is set,
 * and RT_DMA_F_NOCACHE if the device is not DMA-coherent.
 *
 * @param[in] dev  Device to configure DMA operations for
 *
 * @return Pointer to DMA map ops (ofw_dma_map_ops) if regions were found,
 *         RT_NULL otherwise
 */
static const struct rt_dma_map_ops *ofw_device_dma_ops(struct rt_device *dev)
{
    rt_err_t err;
    int region_nr = 0;
    const fdt32_t *cell;
    rt_phandle phandle;
    rt_region_t region;
    struct rt_ofw_prop *prop;
    struct rt_dma_pool *dma_pool;
    const struct rt_dma_map_ops *ops = RT_NULL;
    struct rt_ofw_node *mem_np, *np = dev->ofw_node;

    rt_ofw_foreach_prop_u32(np, "memory-region", prop, cell, phandle)
    {
        rt_uint64_t addr, size;

        if (!(mem_np = rt_ofw_find_node_by_phandle(phandle)))
        {
            if (region_nr == 0)
            {
                return RT_NULL;
            }

            break;
        }

        if ((err = rt_ofw_get_address(mem_np, 0, &addr, &size)))
        {
            LOG_E("%s: Read '%s' error = %s", rt_ofw_node_full_name(mem_np),
                  "memory-region", rt_strerror(err));

            rt_ofw_node_put(mem_np);
            continue;
        }

        region.start = addr;
        region.end = addr + size;
        region.name = rt_dm_dev_get_name(dev);

        rt_ofw_node_put(mem_np);

        if (!(dma_pool = dma_pool_install(&region)))
        {
            return RT_NULL;
        }

        if (rt_ofw_prop_read_bool(mem_np, "no-map"))
        {
            dma_pool->flags |= RT_DMA_F_NOMAP;
        }

        if (!rt_dma_device_is_coherent(dev))
        {
            dma_pool->flags |= RT_DMA_F_NOCACHE;
        }

        dma_pool->dev = dev;
        ++region_nr;
    }

    if (region_nr)
    {
        ops = &ofw_dma_map_ops;
    }

    return ops;
}
#endif /* RT_USING_OFW */

/**
 * @brief Select DMA operations for a device
 *
 * Priority:
 * 1. Device-specific dma_ops (if already set)
 * 2. Device tree memory-region ops (if device has ofw_node)
 * 3. Coherent or non-coherent fallback based on device property
 *
 * The result is cached in dev->dma_ops for subsequent calls.
 *
 * @param[in] dev  Device to query
 *
 * @return DMA map operations for this device
 */
static const struct rt_dma_map_ops *device_dma_ops(struct rt_device *dev)
{
    const struct rt_dma_map_ops *ops = dev->dma_ops;

    if (ops)
    {
        return ops;
    }

#ifdef RT_USING_OFW
    if (dev->ofw_node && (ops = ofw_device_dma_ops(dev)))
    {
        return ops;
    }
#endif

    if (rt_dma_device_is_coherent(dev))
    {
        ops = &dma_map_coherent_ops;
    }
    else
    {
        ops = &dma_map_nocoherent_ops;
    }

    dev->dma_ops = ops;

    return ops;
}

/**
 * @brief Allocate a contiguous range of pages from a DMA pool
 *
 * Uses a first-fit bitmap scan to find a contiguous block of free pages.
 * Pages are tracked by individual bits; ARCH_PAGE_SIZE is the granularity.
 *
 * @param[in] pool  DMA memory pool
 * @param[in] size  Requested size in bytes
 *
 * @return Physical offset within the pool, or RT_NULL on failure
 */
static rt_ubase_t dma_pool_alloc(struct rt_dma_pool *pool, rt_size_t size)
{
    rt_size_t bit, next_bit, end_bit, max_bits;

    size = RT_DIV_ROUND_UP(size, ARCH_PAGE_SIZE);
    max_bits = pool->bits - size;

    rt_bitmap_for_each_clear_bit(pool->map, bit, max_bits)
    {
        end_bit = bit + size;

        for (next_bit = bit + 1; next_bit < end_bit; ++next_bit)
        {
            if (rt_bitmap_test_bit(pool->map, next_bit))
            {
                bit = next_bit;
                goto _next;
            }
        }

        if (next_bit == end_bit)
        {
            while (next_bit-- > bit)
            {
                rt_bitmap_set_bit(pool->map, next_bit);
            }

            LOG_D("%s offset = %p, pages = %d", "Alloc",
                  pool->start + bit * ARCH_PAGE_SIZE, size);

            return pool->start + bit * ARCH_PAGE_SIZE;
        }
    _next:;
    }

    return RT_NULL;
}

/**
 * @brief Free a range of pages back to the DMA pool
 *
 * @param[in] pool   DMA memory pool
 * @param[in] offset Physical offset within the pool (from dma_pool_alloc)
 * @param[in] size   Size in bytes
 */
static void dma_pool_free(struct rt_dma_pool *pool, rt_ubase_t offset, rt_size_t size)
{
    rt_size_t bit = (offset - pool->start) / ARCH_PAGE_SIZE, end_bit;

    size = RT_DIV_ROUND_UP(size, ARCH_PAGE_SIZE);
    end_bit = bit + size;

    for (; bit < end_bit; ++bit)
    {
        rt_bitmap_clear_bit(pool->map, bit);
    }

    LOG_D("%s offset = %p, pages = %d", "Free", offset, size);
}

/**
 * @brief Internal DMA buffer allocator (page-based from pools)
 *
 * Iterates through all registered DMA pools, matching the requested flags
 * against pool capabilities (RT_DMA_F_DEVICE, RT_DMA_F_NOMAP, RT_DMA_F_32BITS).
 * On success, remaps the physical pages to a virtual address with the
 * appropriate cache attributes.
 *
 * @param[in]  dev        DMA-capable device
 * @param[in]  size       Requested size in bytes
 * @param[out] dma_handle Physical DMA address of the allocation
 * @param[in]  flags      Allocation flags (RT_DMA_F_*)
 *
 * @return Kernel virtual address, or RT_NULL on failure
 */
static void *dma_alloc(struct rt_device *dev, rt_size_t size,
                       rt_ubase_t *dma_handle, rt_ubase_t flags)
{
    void *dma_buffer = RT_NULL;
    struct rt_dma_pool *pool;

    region_pool_lock();

    rt_list_for_each_entry(pool, &dma_pool_nodes, list)
    {
        if (pool->flags & RT_DMA_F_DEVICE)
        {
            if (!(flags & RT_DMA_F_DEVICE) || pool->dev != dev)
            {
                continue;
            }
        }
        else if ((flags & RT_DMA_F_DEVICE))
        {
            continue;
        }

        if ((flags & RT_DMA_F_NOMAP) && !((pool->flags & RT_DMA_F_NOMAP)))
        {
            continue;
        }

        if ((flags & RT_DMA_F_32BITS) && !((pool->flags & RT_DMA_F_32BITS)))
        {
            continue;
        }

        *dma_handle = dma_pool_alloc(pool, size);

        if (*dma_handle && !(flags & RT_DMA_F_NOMAP))
        {
            if (flags & RT_DMA_F_NOCACHE)
            {
                dma_buffer = rt_ioremap_nocache((void *)*dma_handle, size);
            }
            else if (flags & RT_DMA_F_WT)
            {
                dma_buffer = rt_ioremap_wt((void *)*dma_handle, size);
            }
            else
            {
                dma_buffer = rt_ioremap_cached((void *)*dma_handle, size);
            }

            if (!dma_buffer)
            {
                dma_pool_free(pool, *dma_handle, size);

                continue;
            }

            break;
        }
        else if (*dma_handle)
        {
            dma_buffer = (void *)*dma_handle;

            break;
        }
    }

    region_pool_unlock();

    return dma_buffer;
}

/**
 * @brief Internal DMA buffer free (returns pages to the pool)
 *
 * Finds the pool containing the DMA handle and frees the pages.
 *
 * @param[in] dev        DMA-capable device
 * @param[in] size       Buffer size in bytes
 * @param[in] cpu_addr   Kernel virtual address (unmapped)
 * @param[in] dma_handle Physical DMA address
 * @param[in] flags      Allocation flags
 */
static void dma_free(struct rt_device *dev, rt_size_t size,
                     void *cpu_addr, rt_ubase_t dma_handle, rt_ubase_t flags)
{
    struct rt_dma_pool *pool;

    region_pool_lock();

    rt_list_for_each_entry(pool, &dma_pool_nodes, list)
    {
        if (dma_handle >= pool->region.start &&
            dma_handle <= pool->region.end)
        {
            rt_iounmap(cpu_addr);

            dma_pool_free(pool, dma_handle, size);

            break;
        }
    }

    region_pool_unlock();
}

/**
 * @brief Allocate a DMA-capable buffer
 *
 * Public API for allocating memory suitable for DMA transfers.
 * Uses device-specific DMA operations when available.
 *
 * @param[in]  dev        DMA-capable device
 * @param[in]  size       Requested buffer size in bytes
 * @param[out] dma_handle Physical DMA address (can be NULL if not needed)
 * @param[in]  flags      Allocation flags (RT_DMA_F_NOCACHE, RT_DMA_F_NOMAP, etc.)
 *
 * @return Kernel virtual address of the buffer, or RT_NULL on failure
 */
void *rt_dma_alloc(struct rt_device *dev, rt_size_t size,
                   rt_ubase_t *dma_handle, rt_ubase_t flags)
{
    void *dma_buffer = RT_NULL;
    rt_ubase_t dma_handle_s = 0;
    const struct rt_dma_map_ops *ops;

    if (!dev || !size)
    {
        return RT_NULL;
    }

    ops = device_dma_ops(dev);

    if (ops->alloc)
    {
        dma_buffer = ops->alloc(dev, size, &dma_handle_s, flags);
    }
    else
    {
        dma_buffer = dma_alloc(dev, size, &dma_handle_s, flags);
    }

    if (!dma_buffer)
    {
        return dma_buffer;
    }

    if (dma_handle)
    {
        *dma_handle = dma_handle_s;
    }

    return dma_buffer;
}

/**
 * @brief Free a DMA buffer previously allocated with rt_dma_alloc()
 *
 * @param[in] dev        DMA-capable device
 * @param[in] size       Buffer size in bytes
 * @param[in] cpu_addr   Kernel virtual address of the buffer
 * @param[in] dma_handle Physical DMA address from rt_dma_alloc()
 * @param[in] flags      Allocation flags used when allocating
 */
void rt_dma_free(struct rt_device *dev, rt_size_t size,
                 void *cpu_addr, rt_ubase_t dma_handle, rt_ubase_t flags)
{
    const struct rt_dma_map_ops *ops;

    if (!dev || !size || !cpu_addr)
    {
        return;
    }

    ops = device_dma_ops(dev);

    if (ops->free)
    {
        ops->free(dev, size, cpu_addr, dma_handle, flags);
    }
    else
    {
        dma_free(dev, size, cpu_addr, dma_handle, flags);
    }
}

/**
 * @brief Synchronize data for a DMA output transfer (CPU→device)
 *
 * Ensures the DMA engine sees the latest CPU-written data by performing
 * any necessary cache flushes and returning the DMA bus address.
 *
 * @param[in]  dev        DMA-capable device
 * @param[in]  data       Virtual address of the data buffer
 * @param[in]  size       Buffer size in bytes
 * @param[out] dma_handle DMA bus address (can be NULL)
 * @param[in]  flags      Sync flags (RT_DMA_F_NOCACHE, etc.)
 *
 * @return RT_EOK on success, -RT_EINVAL if data or size is 0
 */
rt_err_t rt_dma_sync_out_data(struct rt_device *dev, void *data, rt_size_t size,
                              rt_ubase_t *dma_handle, rt_ubase_t flags)
{
    rt_err_t err;
    rt_ubase_t dma_handle_s = 0;
    const struct rt_dma_map_ops *ops;

    if (!data || !size)
    {
        return -RT_EINVAL;
    }

    ops = device_dma_ops(dev);
    err = ops->sync_out_data(dev, data, size, &dma_handle_s, flags);

    if (dma_handle)
    {
        *dma_handle = dma_handle_s;
    }

    return err;
}

/**
 * @brief Synchronize data for a DMA input transfer (device→CPU)
 *
 * Ensures the CPU sees the latest DMA engine data by performing
 * any necessary cache invalidations.
 *
 * @param[in] dev        DMA-capable device
 * @param[in] out_data   Virtual address of the data buffer
 * @param[in] size       Buffer size in bytes
 * @param[in] dma_handle DMA bus address from the transfer
 * @param[in] flags      Sync flags
 *
 * @return RT_EOK on success, -RT_EINVAL if out_data or size is 0
 */
rt_err_t rt_dma_sync_in_data(struct rt_device *dev, void *out_data, rt_size_t size,
                             rt_ubase_t dma_handle, rt_ubase_t flags)
{
    rt_err_t err;
    const struct rt_dma_map_ops *ops;

    if (!out_data || !size)
    {
        return -RT_EINVAL;
    }

    ops = device_dma_ops(dev);
    err = ops->sync_in_data(dev, out_data, size, dma_handle, flags);

    return err;
}

/**
 * @brief Install a DMA memory pool from a region descriptor
 *
 * Creates a new DMA pool covering the given memory region. Allocates
 * a bitmap for page tracking. Pools under 4GB are marked RT_DMA_F_32BITS.
 * Pools are automatically marked RT_DMA_F_LINEAR.
 *
 * Must be called with the DMA pools lock NOT held.
 *
 * @param[in] region  Memory region descriptor (start, end, name)
 *
 * @return New DMA pool pointer, or RT_NULL on failure
 */
static struct rt_dma_pool *dma_pool_install(rt_region_t *region)
{
    rt_err_t err;
    struct rt_dma_pool *pool;

    if (!(pool = rt_calloc(1, sizeof(*pool))))
    {
        LOG_E("Install pool[%p, %p] error = %s",
              region->start, region->end, rt_strerror(-RT_ENOMEM));

        return RT_NULL;
    }

    rt_memcpy(&pool->region, region, sizeof(*region));

    pool->flags |= RT_DMA_F_LINEAR;

    if (region->end < 4UL * SIZE_GB)
    {
        pool->flags |= RT_DMA_F_32BITS;
    }

    pool->start = RT_ALIGN(pool->region.start, ARCH_PAGE_SIZE);
    pool->bits = (pool->region.end - pool->start) / ARCH_PAGE_SIZE;

    if (!pool->bits)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    pool->map = rt_calloc(RT_BITMAP_LEN(pool->bits), sizeof(*pool->map));

    if (!pool->map)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }

    rt_list_init(&pool->list);

    region_pool_lock();
    rt_list_insert_before(&dma_pool_nodes, &pool->list);
    region_pool_unlock();

    return pool;

_fail:
    rt_free(pool);

    LOG_E("Install pool[%p, %p] error = %s",
          region->start, region->end, rt_strerror(err));

    return RT_NULL;
}

/**
 * @brief Public API: install a DMA memory pool
 *
 * Wrapper around dma_pool_install() with logging of the reserved region.
 *
 * @param[in] region  Memory region descriptor
 *
 * @return New DMA pool pointer, or RT_NULL on failure
 */
struct rt_dma_pool *rt_dma_pool_install(rt_region_t *region)
{
    struct rt_dma_pool *pool;

    if (!region)
    {
        return RT_NULL;
    }

    if ((pool = dma_pool_install(region)))
    {
        region = &pool->region;

        LOG_I("%s: Reserved %u.%u MiB at %p",
              region->name,
              (region->end - region->start) / SIZE_MB,
              (region->end - region->start) / SIZE_KB & (SIZE_KB - 1),
              region->start);
    }

    return pool;
}

/**
 * @brief Extract DMA pools from memblock reserved memory
 *
 * Creates two pools from the "dma-pool" reserved memory region:
 * 1. coherent-pool: for coherent DMA allocations
 * 2. CMA (Contiguous Memory Allocator): remaining space for general DMA
 *
 * Prefers regions below 4GB for 32-bit DMA compatibility.
 *
 * @param[in] cma_size           Total CMA region size in bytes
 * @param[in] coherent_pool_size Size of the coherent pool in bytes (must
 *                               be <= cma_size)
 *
 * @return RT_EOK on success, -RT_EINVAL if sizes are invalid,
 *         -RT_ENOSYS if memblock is not available,
 *         -RT_EEMPTY if no suitable dma-pool region found
 */
rt_err_t rt_dma_pool_extract(rt_size_t cma_size, rt_size_t coherent_pool_size)
{
    struct rt_dma_pool *pool;
    struct rt_mmblk_reg *reg, *reg_high;
    struct rt_memblock *memblock = rt_memblock_get_reserved();
    rt_region_t *region, *region_high = RT_NULL, cma, coherent_pool;

    if (!memblock)
    {
        return -RT_ENOSYS;
    }

    /* Coherent pool is included in CMA */
    if (cma_size < coherent_pool_size)
    {
        return -RT_EINVAL;
    }

    rt_slist_for_each_entry(reg, &memblock->reg_list, node)
    {
        if (!reg->alloc || (reg->flags & MEMBLOCK_HOTPLUG))
        {
            continue;
        }

        region = &reg->memreg;
        if (rt_strcmp(region->name, "dma-pool") || !reg->memreg.name)
        {
            continue;
        }

        /* Always use low address in 4G */
        if (region->end - region->start >= cma_size)
        {
            if ((rt_ssize_t)((4UL * SIZE_GB) - region->start) < cma_size)
            {
                region_high = region;
                reg_high = reg;
                continue;
            }

            goto _found;
        }
    }

    if (region_high)
    {
        region = region_high;
        reg = reg_high;
        LOG_W("No available DMA zone in 4G");

        goto _found;
    }

    return -RT_EEMPTY;

_found:
    if (region->end - region->start != cma_size)
    {
        cma.start = region->start;
        cma.end = cma.start + cma_size;
    }
    else
    {
        rt_memcpy(&cma, region, sizeof(cma));
    }

    coherent_pool.name = "coherent-pool";
    coherent_pool.start = cma.start;
    coherent_pool.end = coherent_pool.start + coherent_pool_size;

    cma.name = "cma";
    cma.start += coherent_pool_size;

    if (!(pool = rt_dma_pool_install(&coherent_pool)))
    {
        return -RT_ENOMEM;
    }

    /* Use: CMA > coherent-pool */
    if (!(pool = rt_dma_pool_install(&cma)))
    {
        return -RT_ENOMEM;
    }

    reg->alloc = RT_FALSE;

    return RT_EOK;
}

#if defined(RT_USING_CONSOLE) && defined(RT_USING_MSH)
/**
 * @brief MSH command: list all DMA memory pools
 *
 * Displays each pool's name, start, and end address.
 *
 * @param[in] argc  Argument count (unused)
 * @param[in] argv  Argument values (unused)
 *
 * @return 0
 */
static int list_dma_pool(int argc, char **argv)
{
    int count = 0;
    rt_region_t *region;
    struct rt_dma_pool *pool;

    rt_kprintf("%-*.s Region\n", RT_NAME_MAX, "Name");

    region_pool_lock();

    rt_list_for_each_entry(pool, &dma_pool_nodes, list)
    {
        region = &pool->region;

        rt_kprintf("%-*.s [%p, %p]\n", RT_NAME_MAX, region->name,
                   region->start, region->end);

        ++count;
    }

    rt_kprintf("%d DMA memory found\n", count);

    region_pool_unlock();

    return 0;
}
MSH_CMD_EXPORT(list_dma_pool, dump all dma memory pool);
#endif /* RT_USING_CONSOLE && RT_USING_MSH */
