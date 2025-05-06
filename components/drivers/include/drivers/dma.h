/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-02-25     GuEe-GUI     the first version
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

enum rt_dma_transfer_direction
{
    RT_DMA_MEM_TO_MEM,
    RT_DMA_MEM_TO_DEV,
    RT_DMA_DEV_TO_MEM,
    RT_DMA_DEV_TO_DEV,

    RT_DMA_DIR_MAX,
};

enum rt_dma_slave_buswidth
{
    RT_DMA_SLAVE_BUSWIDTH_UNDEFINED     = 0,
    RT_DMA_SLAVE_BUSWIDTH_1_BYTE        = 1,
    RT_DMA_SLAVE_BUSWIDTH_2_BYTES       = 2,
    RT_DMA_SLAVE_BUSWIDTH_3_BYTES       = 3,
    RT_DMA_SLAVE_BUSWIDTH_4_BYTES       = 4,
    RT_DMA_SLAVE_BUSWIDTH_8_BYTES       = 8,
    RT_DMA_SLAVE_BUSWIDTH_16_BYTES      = 16,
    RT_DMA_SLAVE_BUSWIDTH_32_BYTES      = 32,
    RT_DMA_SLAVE_BUSWIDTH_64_BYTES      = 64,
    RT_DMA_SLAVE_BUSWIDTH_128_BYTES     = 128,

    RT_DMA_SLAVE_BUSWIDTH_BYTES_MAX,
};

struct rt_dma_slave_config
{
    enum rt_dma_transfer_direction direction;
    enum rt_dma_slave_buswidth src_addr_width;
    enum rt_dma_slave_buswidth dst_addr_width;

    rt_ubase_t src_addr;
    rt_ubase_t dst_addr;

    rt_uint32_t src_maxburst;
    rt_uint32_t dst_maxburst;
    rt_uint32_t src_port_window_size;
    rt_uint32_t dst_port_window_size;
};

struct rt_dma_slave_transfer
{
    rt_ubase_t src_addr;
    rt_ubase_t dst_addr;

    void *buffer;
    rt_ubase_t dma_handle;
    rt_size_t buffer_len;
    rt_size_t period_len;
};

struct rt_dma_controller
{
    rt_list_t list;

    struct rt_device *dev;

    RT_BITMAP_DECLARE(dir_cap, RT_DMA_DIR_MAX);
    const struct rt_dma_controller_ops *ops;

    rt_list_t channels_nodes;
    struct rt_mutex mutex;
};

struct rt_dma_controller_ops
{
    struct rt_dma_chan *(*request_chan)(struct rt_dma_controller *ctrl,
            struct rt_device *slave, void *fw_data);
    rt_err_t (*release_chan)(struct rt_dma_chan *chan);

    rt_err_t (*start)(struct rt_dma_chan *chan);
    rt_err_t (*stop)(struct rt_dma_chan *chan);
    rt_err_t (*config)(struct rt_dma_chan *chan, struct rt_dma_slave_config *conf);

    rt_err_t (*prep_memcpy)(struct rt_dma_chan *chan,
            rt_ubase_t dma_addr_src, rt_ubase_t dma_addr_dst, rt_size_t len);

    rt_err_t (*prep_cyclic)(struct rt_dma_chan *chan,
            rt_ubase_t dma_buf_addr, rt_size_t buf_len, rt_size_t period_len,
            enum rt_dma_transfer_direction dir);

    rt_err_t (*prep_single)(struct rt_dma_chan *chan,
            rt_ubase_t dma_buf_addr, rt_size_t buf_len,
            enum rt_dma_transfer_direction dir);
};

struct rt_dma_chan
{
    const char *name;

    struct rt_dma_controller *ctrl;
    struct rt_device *slave;

    rt_list_t list;
    rt_err_t conf_err;
    rt_err_t prep_err;
    struct rt_dma_slave_config conf;
    struct rt_dma_slave_transfer transfer;

    void (*callback)(struct rt_dma_chan *chan, rt_size_t size);

    void *priv;
};

struct rt_dma_pool
{
    rt_region_t region;

    rt_list_t list;

    rt_ubase_t flags;

    rt_bitmap_t *map;
    rt_size_t bits;
    rt_ubase_t start;

    struct rt_device *dev;
};

struct rt_dma_map_ops
{
    void *(*alloc)(struct rt_device *dev, rt_size_t size,
            rt_ubase_t *dma_handle, rt_ubase_t flags);
    void (*free)(struct rt_device *dev, rt_size_t size,
            void *cpu_addr, rt_ubase_t dma_handle, rt_ubase_t flags);
    rt_err_t (*sync_out_data)(struct rt_device *dev, void *data, rt_size_t size,
            rt_ubase_t *dma_handle, rt_ubase_t flags);
    rt_err_t (*sync_in_data)(struct rt_device *dev, void *out_data, rt_size_t size,
            rt_ubase_t dma_handle, rt_ubase_t flags);
};

rt_inline void rt_dma_controller_add_direction(struct rt_dma_controller *ctrl,
        enum rt_dma_transfer_direction dir)
{
    RT_ASSERT(ctrl != RT_NULL);
    RT_ASSERT(dir < RT_DMA_DIR_MAX);

    rt_bitmap_set_bit(ctrl->dir_cap, dir);
}

rt_err_t rt_dma_controller_register(struct rt_dma_controller *ctrl);
rt_err_t rt_dma_controller_unregister(struct rt_dma_controller *ctrl);

rt_err_t rt_dma_chan_start(struct rt_dma_chan *chan);
rt_err_t rt_dma_chan_stop(struct rt_dma_chan *chan);
rt_err_t rt_dma_chan_config(struct rt_dma_chan *chan,
        struct rt_dma_slave_config *conf);
rt_err_t rt_dma_chan_done(struct rt_dma_chan *chan, rt_size_t size);

rt_err_t rt_dma_prep_memcpy(struct rt_dma_chan *chan,
        struct rt_dma_slave_transfer *transfer);
rt_err_t rt_dma_prep_cyclic(struct rt_dma_chan *chan,
        struct rt_dma_slave_transfer *transfer);
rt_err_t rt_dma_prep_single(struct rt_dma_chan *chan,
        struct rt_dma_slave_transfer *transfer);

struct rt_dma_chan *rt_dma_chan_request(struct rt_device *dev, const char *name);
rt_err_t rt_dma_chan_release(struct rt_dma_chan *chan);

#define RT_DMA_F_LINEAR     RT_BIT(0)
#define RT_DMA_F_32BITS     RT_BIT(1)
#define RT_DMA_F_NOCACHE    RT_BIT(2)
#define RT_DMA_F_DEVICE     RT_BIT(3)
#define RT_DMA_F_NOMAP      RT_BIT(4)

#define RT_DMA_PAGE_SIZE    ARCH_PAGE_SIZE

void *rt_dma_alloc(struct rt_device *dev, rt_size_t size,
        rt_ubase_t *dma_handle, rt_ubase_t flags);

void rt_dma_free(struct rt_device *dev, rt_size_t size,
        void *cpu_addr, rt_ubase_t dma_handle, rt_ubase_t flags);

rt_inline void *rt_dma_alloc_coherent(struct rt_device *dev, rt_size_t size,
        rt_ubase_t *dma_handle)
{
    return rt_dma_alloc(dev, size, dma_handle,
            RT_DMA_F_NOCACHE | RT_DMA_F_LINEAR);
}

rt_inline void rt_dma_free_coherent(struct rt_device *dev, rt_size_t size,
        void *cpu_addr, rt_ubase_t dma_handle)
{
    rt_dma_free(dev, size, cpu_addr, dma_handle,
            RT_DMA_F_NOCACHE | RT_DMA_F_LINEAR);
}

rt_err_t rt_dma_sync_out_data(struct rt_device *dev, void *data, rt_size_t size,
        rt_ubase_t *dma_handle, rt_ubase_t flags);
rt_err_t rt_dma_sync_in_data(struct rt_device *dev, void *out_data, rt_size_t size,
        rt_ubase_t dma_handle, rt_ubase_t flags);

rt_inline rt_bool_t rt_dma_device_is_coherent(struct rt_device *dev)
{
    return rt_dm_dev_prop_read_bool(dev, "dma-coherent");
}

rt_inline void rt_dma_device_set_ops(struct rt_device *dev,
        const struct rt_dma_map_ops *ops)
{
    dev->dma_ops = ops;
}

struct rt_dma_pool *rt_dma_pool_install(rt_region_t *region);
rt_err_t rt_dma_pool_extract(rt_region_t *region_list, rt_size_t list_len,
        rt_size_t cma_size, rt_size_t coherent_pool_size);

#endif /* __DMA_H__ */
