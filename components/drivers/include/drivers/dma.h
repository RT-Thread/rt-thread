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
 * @file dma.h
 * @brief DMA (Direct Memory Access) controller framework public API
 *
 * Defines the DMA controller, channel, memory pool, and mapping operations
 * interfaces. Provides APIs for controller registration, channel lifecycle
 * management, transfer preparation (memcpy, cyclic, single), DMA buffer
 * allocation with cache coherence management, and device tree integration.
 */

#ifndef __DMA_H__
#define __DMA_H__

#include <rtthread.h>
#include <drivers/ofw.h>
#include <drivers/misc.h>
#include <drivers/core/dm.h>

#include <mmu.h>
#include <mm_page.h>
#include <bitmap.h>

struct rt_dma_chan;
struct rt_dma_controller_ops;

/**
 * @brief DMA transfer direction
 *
 * Defines the data flow direction for a DMA transfer. The controller's
 * dir_cap bitmap indicates which directions are supported.
 */
enum rt_dma_transfer_direction
{
    RT_DMA_MEM_TO_MEM,  /**< Memory-to-memory copy (no peripheral involved) */
    RT_DMA_MEM_TO_DEV,  /**< Memory to peripheral (TX / playback) */
    RT_DMA_DEV_TO_MEM,  /**< Peripheral to memory (RX / capture) */
    RT_DMA_DEV_TO_DEV,  /**< Device-to-device (rare, may not be supported) */

    RT_DMA_DIR_MAX,     /**< Sentinel: total number of direction types */
};

/**
 * @brief DMA slave bus width options
 *
 * Specifies the transfer width for source and destination on the
 * DMA bus. Must match the peripheral's FIFO width for correct operation.
 */
enum rt_dma_slave_buswidth
{
    RT_DMA_SLAVE_BUSWIDTH_UNDEFINED = 0,    /**< Undefined / not configured */
    RT_DMA_SLAVE_BUSWIDTH_1_BYTE = 1,    /**< 8-bit transfers */
    RT_DMA_SLAVE_BUSWIDTH_2_BYTES = 2,    /**< 16-bit transfers */
    RT_DMA_SLAVE_BUSWIDTH_3_BYTES = 3,    /**< 24-bit transfers */
    RT_DMA_SLAVE_BUSWIDTH_4_BYTES = 4,    /**< 32-bit transfers */
    RT_DMA_SLAVE_BUSWIDTH_8_BYTES = 8,    /**< 64-bit transfers */
    RT_DMA_SLAVE_BUSWIDTH_16_BYTES = 16,   /**< 128-bit transfers */
    RT_DMA_SLAVE_BUSWIDTH_32_BYTES = 32,   /**< 256-bit transfers */
    RT_DMA_SLAVE_BUSWIDTH_64_BYTES = 64,   /**< 512-bit transfers */
    RT_DMA_SLAVE_BUSWIDTH_128_BYTES = 128,  /**< 1024-bit transfers */

    RT_DMA_SLAVE_BUSWIDTH_BYTES_MAX,            /**< Sentinel: maximum bus width enum value */
};

/**
 * @brief DMA slave channel configuration
 *
 * Passed to rt_dma_chan_config() to set up a channel before starting
 * transfers. Defines transfer direction, address widths, fixed source/
 * destination addresses, and burst sizes.
 */
struct rt_dma_slave_config
{
    enum rt_dma_transfer_direction direction;    /**< Transfer direction (MEM_TO_DEV, DEV_TO_MEM, etc.) */
    enum rt_dma_slave_buswidth src_addr_width;   /**< Source bus width in bytes */
    enum rt_dma_slave_buswidth dst_addr_width;   /**< Destination bus width in bytes */

    rt_ubase_t src_addr;                         /**< Fixed source address (peripheral FIFO register) */
    rt_ubase_t dst_addr;                         /**< Fixed destination address (peripheral FIFO register) */

    rt_uint32_t src_maxburst;                    /**< Maximum source burst size in transfer-width units */
    rt_uint32_t dst_maxburst;                    /**< Maximum destination burst size in transfer-width units */
    rt_uint32_t src_port_window_size;            /**< Source port window size (for scatter-gather) */
    rt_uint32_t dst_port_window_size;            /**< Destination port window size (for scatter-gather) */
};

/**
 * @brief DMA slave transfer descriptor
 *
 * Describes a single DMA transfer: source/destination buffer addresses,
 * total buffer length, and period length for cyclic transfers. Passed
 * to rt_dma_prep_memcpy(), rt_dma_prep_cyclic(), or rt_dma_prep_single().
 */
struct rt_dma_slave_transfer
{
    rt_ubase_t src_addr;         /**< Source buffer physical address */
    rt_ubase_t dst_addr;         /**< Destination buffer physical address */

    void *buffer;                /**< Virtual address of the DMA buffer (if mapped) */
    rt_ubase_t dma_handle;       /**< DMA bus address of the buffer */
    rt_size_t buffer_len;        /**< Total buffer length in bytes */
    rt_size_t period_len;        /**< Period length in bytes (for cyclic transfers only) */
};

/**
 * @brief DMA controller descriptor
 *
 * Represents a single DMA controller instance. Each controller has
 * a set of operations (ops), supported transfer directions (dir_cap),
 * an address mask for validating transfer addresses, and a list of
 * currently allocated channels.
 */
struct rt_dma_controller
{
    rt_list_t list;                              /**< Node in the global controller list */

    struct rt_device *dev;                       /**< Owning platform device */

#define RT_DMA_ADDR_MASK(n) (((n) == 64) ? ~0ULL : ((1ULL << (n)) - 1))
    /** @brief Compute DMA address mask from bit width (e.g., RT_DMA_ADDR_MASK(32) = 0xFFFFFFFF) */
    rt_uint64_t addr_mask;                       /**< Address mask: bits outside this mask are invalid for DMA */
    RT_BITMAP_DECLARE(dir_cap, RT_DMA_DIR_MAX);  /**< Bitmap of supported transfer directions */
    const struct rt_dma_controller_ops *ops;     /**< Controller-specific operations */

    rt_list_t channels_nodes;                    /**< List of currently allocated channels */
    struct rt_mutex mutex;                       /**< Mutex for controller-level operations */
};

/**
 * @brief DMA controller operations vtable
 *
 * Each DMA controller driver provides implementations of these operations.
 * start, stop, and config are mandatory; the rest are optional.
 */
struct rt_dma_controller_ops
{
    /**
     * @brief Request a DMA channel (optional)
     *
     * @param[in] ctrl     DMA controller
     * @param[in] slave    Device requesting the channel
     * @param[in] fw_data  Device tree cell args (NULL for mem-to-mem)
     *
     * @return Channel pointer, RT_NULL, or error pointer
     */
    struct rt_dma_chan *(*request_chan)(struct rt_dma_controller *ctrl,
                                        struct rt_device *slave, void *fw_data);

    /**
     * @brief Release a DMA channel (optional)
     *
     * @param[in] chan  Channel to release
     *
     * @return RT_EOK on success
     */
    rt_err_t (*release_chan)(struct rt_dma_chan *chan);

    /**
     * @brief Start a prepared transfer (mandatory)
     *
     * @param[in] chan  Channel with a successfully prepared transfer
     *
     * @return RT_EOK on success
     */
    rt_err_t (*start)(struct rt_dma_chan *chan);

    /**
     * @brief Pause a running transfer (optional)
     *
     * If not implemented, the framework falls back to stop().
     *
     * @param[in] chan  Channel to pause
     *
     * @return RT_EOK on success
     */
    rt_err_t (*pause)(struct rt_dma_chan *chan);

    /**
     * @brief Stop a running transfer (mandatory)
     *
     * @param[in] chan  Channel to stop
     *
     * @return RT_EOK on success
     */
    rt_err_t (*stop)(struct rt_dma_chan *chan);

    /**
     * @brief Configure a DMA channel (mandatory)
     *
     * @param[in] chan  Channel to configure
     * @param[in] conf  Slave configuration
     *
     * @return RT_EOK on success
     */
    rt_err_t (*config)(struct rt_dma_chan *chan, struct rt_dma_slave_config *conf);

    /**
     * @brief Prepare a memory-to-memory transfer (optional)
     *
     * @param[in] chan          DMA channel
     * @param[in] dma_addr_src  Source physical address
     * @param[in] dma_addr_dst  Destination physical address
     * @param[in] len           Transfer length in bytes
     *
     * @return RT_EOK on success
     */
    rt_err_t (*prep_memcpy)(struct rt_dma_chan *chan,
                            rt_ubase_t dma_addr_src, rt_ubase_t dma_addr_dst, rt_size_t len);

    /**
     * @brief Prepare a cyclic (repeating) transfer (optional)
     *
     * @param[in] chan          DMA channel
     * @param[in] dma_buf_addr  Buffer physical address
     * @param[in] buf_len       Total buffer length in bytes
     * @param[in] period_len    Bytes per period (callback interval)
     * @param[in] dir           Transfer direction
     *
     * @return RT_EOK on success
     */
    rt_err_t (*prep_cyclic)(struct rt_dma_chan *chan,
                            rt_ubase_t dma_buf_addr, rt_size_t buf_len, rt_size_t period_len,
                            enum rt_dma_transfer_direction dir);

    /**
     * @brief Prepare a single (one-shot) transfer (optional)
     *
     * @param[in] chan          DMA channel
     * @param[in] dma_buf_addr  Buffer physical address
     * @param[in] buf_len       Transfer length in bytes
     * @param[in] dir           Transfer direction
     *
     * @return RT_EOK on success
     */
    rt_err_t (*prep_single)(struct rt_dma_chan *chan,
                            rt_ubase_t dma_buf_addr, rt_size_t buf_len,
                            enum rt_dma_transfer_direction dir);
};

/**
 * @brief DMA channel descriptor
 *
 * Represents an allocated DMA channel bound to a specific slave device.
 * Tracks configuration and preparation errors to prevent operations on
 * improperly set up channels.
 */
struct rt_dma_chan
{
    const char *name;                            /**< Channel name (from dma-names in device tree) */

    struct rt_dma_controller *ctrl;              /**< Parent DMA controller */
    struct rt_device *slave;                     /**< Slave device that requested this channel */

    rt_list_t list;                              /**< Node in the controller's channels list */
    rt_err_t conf_err;                           /**< Last configuration error (-RT_ERROR = not configured) */
    rt_err_t prep_err;                           /**< Last preparation error (-RT_ERROR = not prepared) */
    struct rt_dma_slave_config conf;             /**< Saved slave configuration */
    struct rt_dma_slave_transfer transfer;       /**< Saved transfer descriptor */

    void (*callback)(struct rt_dma_chan *chan, rt_size_t size);  /**< Transfer completion callback */

    void *priv;                                  /**< Controller driver private data */
};

/**
 * @brief DMA memory pool descriptor
 *
 * Manages a contiguous physical memory region for DMA allocations.
 * Uses a bitmap to track free/used pages. Pools are organized in
 * a global linked list.
 */
struct rt_dma_pool
{
    rt_region_t region;          /**< Memory region (name, start, end) */

    rt_list_t list;              /**< Node in the global pool list */

    rt_ubase_t flags;            /**< Pool flags (RT_DMA_F_LINEAR, RT_DMA_F_32BITS, etc.) */

    rt_bitmap_t *map;            /**< Page allocation bitmap (1 bit per page) */
    rt_size_t bits;              /**< Total number of pages in this pool */
    rt_ubase_t start;            /**< Page-aligned start address */

    struct rt_device *dev;       /**< Device that owns this pool (for RT_DMA_F_DEVICE) */
};

/**
 * @brief DMA memory mapping operations vtable
 *
 * Abstracts device-specific DMA memory management: allocation, freeing,
 * and cache synchronization for coherent and non-coherent devices.
 * Devices may override these via dev->dma_ops or the device tree.
 */
struct rt_dma_map_ops
{
    /**
     * @brief Allocate a DMA buffer (optional, may fall back to default)
     *
     * @param[in]  dev        DMA-capable device
     * @param[in]  size       Requested size in bytes
     * @param[out] dma_handle Physical DMA address
     * @param[in]  flags      Allocation flags (RT_DMA_F_*)
     *
     * @return Kernel virtual address, or RT_NULL on failure
     */
    void *(*alloc)(struct rt_device *dev, rt_size_t size,
                   rt_ubase_t *dma_handle, rt_ubase_t flags);

    /**
     * @brief Free a DMA buffer (optional)
     *
     * @param[in] dev        DMA-capable device
     * @param[in] size       Buffer size in bytes
     * @param[in] cpu_addr   Kernel virtual address
     * @param[in] dma_handle Physical DMA address
     * @param[in] flags      Allocation flags
     */
    void (*free)(struct rt_device *dev, rt_size_t size,
                 void *cpu_addr, rt_ubase_t dma_handle, rt_ubase_t flags);

    /**
     * @brief Synchronize data for DMA output (CPU → device)
     *
     * Performs any necessary cache flush and returns the DMA bus address.
     *
     * @param[in]  dev        DMA-capable device
     * @param[in]  data       Virtual address of data buffer
     * @param[in]  size       Buffer size in bytes
     * @param[out] dma_handle DMA bus address (may be NULL)
     * @param[in]  flags      Sync flags
     *
     * @return RT_EOK on success
     */
    rt_err_t (*sync_out_data)(struct rt_device *dev, void *data, rt_size_t size,
                              rt_ubase_t *dma_handle, rt_ubase_t flags);

    /**
     * @brief Synchronize data for DMA input (device → CPU)
     *
     * Performs any necessary cache invalidation.
     *
     * @param[in] dev        DMA-capable device
     * @param[in] out_data   Virtual address of data buffer
     * @param[in] size       Buffer size in bytes
     * @param[in] dma_handle DMA bus address
     * @param[in] flags      Sync flags
     *
     * @return RT_EOK on success
     */
    rt_err_t (*sync_in_data)(struct rt_device *dev, void *out_data, rt_size_t size,
                             rt_ubase_t dma_handle, rt_ubase_t flags);
};

/**
 * @brief Add a supported transfer direction to a DMA controller
 *
 * Controllers call this during probe to declare which directions they support.
 *
 * @param[in] ctrl  DMA controller
 * @param[in] dir   Transfer direction to add
 */
rt_inline void rt_dma_controller_add_direction(struct rt_dma_controller *ctrl,
                                               enum rt_dma_transfer_direction dir)
{
    RT_ASSERT(ctrl != RT_NULL);
    RT_ASSERT(dir < RT_DMA_DIR_MAX);

    rt_bitmap_set_bit(ctrl->dir_cap, dir);
}

/**
 * @brief Set the address mask for a DMA controller
 *
 * The mask defines the valid address range for DMA transfers.
 * For example, RT_DMA_ADDR_MASK(32) limits transfers to the lower 4GB.
 *
 * @param[in] ctrl  DMA controller
 * @param[in] mask  Address bit mask
 */
rt_inline void rt_dma_controller_set_addr_mask(struct rt_dma_controller *ctrl,
                                               rt_uint64_t mask)
{
    RT_ASSERT(ctrl != RT_NULL);

    ctrl->addr_mask = mask;
}

/** @brief Register a DMA controller with the framework */
rt_err_t rt_dma_controller_register(struct rt_dma_controller *ctrl);

/** @brief Unregister a DMA controller (fails if channels are in use) */
rt_err_t rt_dma_controller_unregister(struct rt_dma_controller *ctrl);

/** @brief Start a prepared DMA transfer on a channel */
rt_err_t rt_dma_chan_start(struct rt_dma_chan *chan);

/** @brief Pause a running DMA transfer (falls back to stop if not supported) */
rt_err_t rt_dma_chan_pause(struct rt_dma_chan *chan);

/** @brief Stop a running DMA transfer */
rt_err_t rt_dma_chan_stop(struct rt_dma_chan *chan);

/** @brief Configure a DMA channel with slave-specific parameters */
rt_err_t rt_dma_chan_config(struct rt_dma_chan *chan,
                            struct rt_dma_slave_config *conf);

/** @brief Signal transfer completion (called by controller ISR) */
rt_err_t rt_dma_chan_done(struct rt_dma_chan *chan, rt_size_t size);

/** @brief Prepare a memory-to-memory DMA transfer */
rt_err_t rt_dma_prep_memcpy(struct rt_dma_chan *chan,
                            struct rt_dma_slave_transfer *transfer);

/** @brief Prepare a cyclic (repeating) DMA transfer */
rt_err_t rt_dma_prep_cyclic(struct rt_dma_chan *chan,
                            struct rt_dma_slave_transfer *transfer);

/** @brief Prepare a single (one-shot) DMA transfer */
rt_err_t rt_dma_prep_single(struct rt_dma_chan *chan,
                            struct rt_dma_slave_transfer *transfer);

/** @brief Request a DMA channel for a slave device (by DT name or auto) */
struct rt_dma_chan *rt_dma_chan_request(struct rt_device *dev, const char *name);

/** @brief Release a DMA channel back to the controller */
rt_err_t rt_dma_chan_release(struct rt_dma_chan *chan);

/** @brief DMA pool: linear address space (all DMA pools have this flag) */
#define RT_DMA_F_LINEAR RT_BIT(0)
/** @brief DMA pool: limited to 32-bit addressable memory (below 4GB) */
#define RT_DMA_F_32BITS RT_BIT(1)
/** @brief DMA allocation: use non-cacheable memory mapping */
#define RT_DMA_F_NOCACHE RT_BIT(2)
/** @brief DMA pool: device-private pool (matches pool->dev) */
#define RT_DMA_F_DEVICE RT_BIT(3)
/** @brief DMA allocation: do not map virtual address, return physical */
#define RT_DMA_F_NOMAP RT_BIT(4)
/** @brief DMA allocation: use write-through cache mapping */
#define RT_DMA_F_WT RT_BIT(5)

/** @brief DMA pool page size matches architecture page size */
#define RT_DMA_PAGE_SIZE ARCH_PAGE_SIZE

/** @brief Allocate a DMA-capable memory buffer */
void *rt_dma_alloc(struct rt_device *dev, rt_size_t size,
                   rt_ubase_t *dma_handle, rt_ubase_t flags);

/** @brief Free a DMA buffer previously allocated with rt_dma_alloc() */
void rt_dma_free(struct rt_device *dev, rt_size_t size,
                 void *cpu_addr, rt_ubase_t dma_handle, rt_ubase_t flags);

/**
 * @brief Allocate a coherent (non-cacheable) DMA buffer
 *
 * Convenience wrapper around rt_dma_alloc() with RT_DMA_F_NOCACHE | RT_DMA_F_LINEAR.
 *
 * @param[in]  dev        DMA-capable device
 * @param[in]  size       Requested size in bytes
 * @param[out] dma_handle Physical DMA address
 *
 * @return Kernel virtual address, or RT_NULL on failure
 */
rt_inline void *rt_dma_alloc_coherent(struct rt_device *dev, rt_size_t size,
                                      rt_ubase_t *dma_handle)
{
    return rt_dma_alloc(dev, size, dma_handle,
                        RT_DMA_F_NOCACHE | RT_DMA_F_LINEAR);
}

/**
 * @brief Free a coherent DMA buffer
 *
 * @param[in] dev        DMA-capable device
 * @param[in] size       Buffer size in bytes
 * @param[in] cpu_addr   Kernel virtual address
 * @param[in] dma_handle Physical DMA address
 */
rt_inline void rt_dma_free_coherent(struct rt_device *dev, rt_size_t size,
                                    void *cpu_addr, rt_ubase_t dma_handle)
{
    rt_dma_free(dev, size, cpu_addr, dma_handle,
                RT_DMA_F_NOCACHE | RT_DMA_F_LINEAR);
}

/** @brief Synchronize CPU cache for DMA output (CPU → device) */
rt_err_t rt_dma_sync_out_data(struct rt_device *dev, void *data, rt_size_t size,
                              rt_ubase_t *dma_handle, rt_ubase_t flags);

/** @brief Synchronize CPU cache for DMA input (device → CPU) */
rt_err_t rt_dma_sync_in_data(struct rt_device *dev, void *out_data, rt_size_t size,
                             rt_ubase_t dma_handle, rt_ubase_t flags);

/**
 * @brief Check if a device is DMA-coherent
 *
 * Reads the "dma-coherent" boolean property from the device's
 * device tree node (if present).
 *
 * @param[in] dev  Device to check
 *
 * @return RT_TRUE if the device is DMA-coherent
 */
rt_inline rt_bool_t rt_dma_device_is_coherent(struct rt_device *dev)
{
    return rt_dm_dev_prop_read_bool(dev, "dma-coherent");
}

/**
 * @brief Override the DMA mapping operations for a device
 *
 * @param[in] dev  Device to configure
 * @param[in] ops  Custom DMA map operations (or NULL to reset)
 */
rt_inline void rt_dma_device_set_ops(struct rt_device *dev,
                                     const struct rt_dma_map_ops *ops)
{
    dev->dma_ops = ops;
}

/** @brief Install a DMA memory pool from a region descriptor */
struct rt_dma_pool *rt_dma_pool_install(rt_region_t *region);

/** @brief Extract coherent pool and CMA from memblock reserved memory */
rt_err_t rt_dma_pool_extract(rt_size_t cma_size, rt_size_t coherent_pool_size);

#endif /* __DMA_H__ */
