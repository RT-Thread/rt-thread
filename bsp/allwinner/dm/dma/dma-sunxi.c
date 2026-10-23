/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rtthread.h>
#include <rtdevice.h>

#define SUNXI_DMA_IRQ_ENABLE(index)      ((index) * 0x04)
#define SUNXI_DMA_IRQ_STATUS(index)      ((index) * 0x04 + 0x10)
#define SUNXI_DMA_IRQ_HALF               RT_BIT(0)
#define SUNXI_DMA_IRQ_PACKAGE            RT_BIT(1)
#define SUNXI_DMA_IRQ_QUEUE              RT_BIT(2)
#define SUNXI_DMA_IRQ_MASK               (SUNXI_DMA_IRQ_PACKAGE | SUNXI_DMA_IRQ_QUEUE)
#define SUNXI_DMA_IRQ_CHANNELS           8
#define SUNXI_DMA_IRQ_WIDTH              4

#define SUNXI_DMA_CHANNEL_BASE           0x100
#define SUNXI_DMA_CHANNEL_STRIDE         0x040
#define SUNXI_DMA_CHANNEL_ENABLE         0x00
#define SUNXI_DMA_CHANNEL_PAUSE          0x04
#define SUNXI_DMA_CHANNEL_LLI            0x08

#define SUNXI_DMA_CHANNEL_START          RT_BIT(0)
#define SUNXI_DMA_CHANNEL_PAUSE_RESUME   0

#define SUNXI_DMA_CFG_SRC_DRQ(value)     ((value) & 0x3f)
#define SUNXI_DMA_CFG_SRC_MODE(value)    (((value) & 0x1) << 8)
#define SUNXI_DMA_CFG_SRC_BURST(value)   (((value) & 0x3) << 6)
#define SUNXI_DMA_CFG_SRC_WIDTH(value)   (((value) & 0x3) << 9)
#define SUNXI_DMA_CFG_DST_DRQ(value)     (SUNXI_DMA_CFG_SRC_DRQ(value) << 16)
#define SUNXI_DMA_CFG_DST_MODE(value)    (SUNXI_DMA_CFG_SRC_MODE(value) << 16)
#define SUNXI_DMA_CFG_DST_BURST(value)   (SUNXI_DMA_CFG_SRC_BURST(value) << 16)
#define SUNXI_DMA_CFG_DST_WIDTH(value)   (SUNXI_DMA_CFG_SRC_WIDTH(value) << 16)

#define SUNXI_DMA_DRQ_SDRAM              1
#define SUNXI_DMA_MODE_LINEAR            0
#define SUNXI_DMA_MODE_IO                1
#define SUNXI_DMA_LLI_LAST               0xfffff800
#define SUNXI_DMA_LLI_WAIT               64
#define SUNXI_DMA_MAX_CHANNELS           16
#define SUNXI_DMA_MAX_REQUESTS           48
#define SUNXI_DMA_MAX_TRANSFER           0x00ffffff

struct sunxi_dma_lli
{
    rt_uint32_t config;
    rt_uint32_t src;
    rt_uint32_t dst;
    rt_uint32_t length;
    rt_uint32_t parameter;
    rt_uint32_t next;
};

struct sunxi_dma;

struct sunxi_dma_channel
{
    struct rt_dma_chan parent;
    struct sunxi_dma *dma;
    struct sunxi_dma_lli *llis;
    rt_ubase_t llis_dma;
    rt_size_t llis_size;
    rt_size_t transfer_size;
    rt_size_t period_size;
    rt_ubase_t memory;
    rt_uint8_t id;
    rt_uint8_t request;
    rt_bool_t allocated;
    rt_bool_t active;
    rt_bool_t cyclic;
    enum rt_dma_transfer_direction direction;
};

struct sunxi_dma
{
    struct rt_dma_controller parent;
    struct sunxi_dma_channel *channels;
    void *base;
    struct rt_clk *bus_clk;
    struct rt_clk *mbus_clk;
    struct rt_reset_control *reset;
    rt_uint32_t channels_nr;
    rt_uint32_t requests_nr;
    int irq;
    rt_bool_t irq_installed;
    rt_bool_t reset_deasserted;
    rt_bool_t bus_clk_enabled;
    rt_bool_t mbus_clk_enabled;
};

struct sunxi_dma_soc_data
{
    rt_uint32_t requests_max;
    rt_bool_t enable_mbus;
};

static const struct sunxi_dma_soc_data sunxi_dma_data =
{
    .requests_max = SUNXI_DMA_MAX_REQUESTS,
};

static const struct sunxi_dma_soc_data sunxi_dma_h616_data =
{
    .requests_max = 49,
    .enable_mbus = RT_TRUE,
};

#define to_sunxi_dma(raw) rt_container_of(raw, struct sunxi_dma, parent)
#define to_sunxi_dma_channel(raw) rt_container_of(raw, struct sunxi_dma_channel, parent)

rt_inline void *sunxi_dma_channel_base(struct sunxi_dma_channel *channel)
{
    return channel->dma->base + SUNXI_DMA_CHANNEL_BASE +
            channel->id * SUNXI_DMA_CHANNEL_STRIDE;
}

rt_inline rt_uint32_t sunxi_dma_width_code(enum rt_dma_slave_buswidth width)
{
    switch (width)
    {
    case RT_DMA_SLAVE_BUSWIDTH_1_BYTE:
        return 0;
    case RT_DMA_SLAVE_BUSWIDTH_2_BYTES:
        return 1;
    case RT_DMA_SLAVE_BUSWIDTH_4_BYTES:
        return 2;
    case RT_DMA_SLAVE_BUSWIDTH_8_BYTES:
        return 3;
    default:
        return RT_UINT32_MAX;
    }
}

static void sunxi_dma_free_llis(struct sunxi_dma_channel *channel)
{
    if (channel->llis)
    {
        rt_dma_free_coherent(channel->dma->parent.dev, channel->llis_size,
                channel->llis, channel->llis_dma);
        channel->llis = RT_NULL;
        channel->llis_dma = 0;
        channel->llis_size = 0;
    }
}

static rt_err_t sunxi_dma_alloc_llis(struct sunxi_dma_channel *channel,
        rt_size_t count)
{
    rt_size_t size;

    if (!count || count > (rt_size_t)-1 / sizeof(*channel->llis))
    {
        return -RT_EINVAL;
    }

    sunxi_dma_free_llis(channel);
    size = count * sizeof(*channel->llis);
    channel->llis = rt_dma_alloc_coherent(channel->dma->parent.dev, size,
            &channel->llis_dma);
    if (!channel->llis)
    {
        return -RT_ENOMEM;
    }

    channel->llis_size = size;
    return RT_EOK;
}

static rt_uint32_t sunxi_dma_burst_code(rt_uint32_t burst)
{
    if (burst <= 1)
    {
        return 0;
    }
    if (burst <= 4)
    {
        return 1;
    }
    if (burst <= 8)
    {
        return 2;
    }
    return 3;
}

static rt_uint32_t sunxi_dma_config_value(struct sunxi_dma_channel *channel,
        enum rt_dma_transfer_direction direction)
{
    struct rt_dma_slave_config *config = &channel->parent.conf;
    rt_uint32_t src_width = 2;
    rt_uint32_t dst_width = 2;
    rt_uint32_t src_burst = 0;
    rt_uint32_t dst_burst = 0;
    rt_uint32_t src_drq = SUNXI_DMA_DRQ_SDRAM;
    rt_uint32_t dst_drq = SUNXI_DMA_DRQ_SDRAM;
    rt_uint32_t src_mode = SUNXI_DMA_MODE_LINEAR;
    rt_uint32_t dst_mode = SUNXI_DMA_MODE_LINEAR;

    if (config->src_addr_width != RT_DMA_SLAVE_BUSWIDTH_UNDEFINED)
    {
        src_width = sunxi_dma_width_code(config->src_addr_width);
    }
    if (config->dst_addr_width != RT_DMA_SLAVE_BUSWIDTH_UNDEFINED)
    {
        dst_width = sunxi_dma_width_code(config->dst_addr_width);
    }
    src_burst = sunxi_dma_burst_code(config->src_maxburst);
    dst_burst = sunxi_dma_burst_code(config->dst_maxburst);

    if (direction == RT_DMA_MEM_TO_DEV)
    {
        dst_drq = channel->request;
        dst_mode = SUNXI_DMA_MODE_IO;
    }
    else if (direction == RT_DMA_DEV_TO_MEM)
    {
        src_drq = channel->request;
        src_mode = SUNXI_DMA_MODE_IO;
    }

    return SUNXI_DMA_CFG_SRC_DRQ(src_drq) |
            SUNXI_DMA_CFG_SRC_MODE(src_mode) |
            SUNXI_DMA_CFG_SRC_BURST(src_burst) |
            SUNXI_DMA_CFG_SRC_WIDTH(src_width) |
            SUNXI_DMA_CFG_DST_DRQ(dst_drq) |
            SUNXI_DMA_CFG_DST_MODE(dst_mode) |
            SUNXI_DMA_CFG_DST_BURST(dst_burst) |
            SUNXI_DMA_CFG_DST_WIDTH(dst_width);
}

/*
 * On F101's no-MMU configuration, rt_ioremap_nocache() is an identity
 * mapping.  DMA-pool allocations therefore still need cache maintenance at
 * the hardware boundary.
 */
static void sunxi_dma_sync_for_device(struct sunxi_dma_channel *channel)
{
#ifndef ARCH_MM_MMU
    if (channel->direction == RT_DMA_MEM_TO_MEM)
    {
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH,
                (void *)channel->llis[0].src, channel->transfer_size);
        rt_hw_cpu_dcache_clean_and_invalidate((void *)channel->llis[0].dst,
                channel->transfer_size);
    }
    else if (channel->direction == RT_DMA_MEM_TO_DEV)
    {
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, (void *)channel->memory,
                channel->transfer_size);
    }
    else if (channel->direction == RT_DMA_DEV_TO_MEM)
    {
        rt_hw_cpu_dcache_clean_and_invalidate((void *)channel->memory,
                channel->transfer_size);
    }
#else
    RT_UNUSED(channel);
#endif
}

static void sunxi_dma_sync_for_cpu(struct sunxi_dma_channel *channel)
{
#ifndef ARCH_MM_MMU
    if (channel->direction == RT_DMA_MEM_TO_MEM)
    {
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE,
                (void *)channel->llis[0].dst, channel->transfer_size);
    }
    else if (channel->direction == RT_DMA_DEV_TO_MEM)
    {
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, (void *)channel->memory,
                channel->transfer_size);
    }
#else
    RT_UNUSED(channel);
#endif
}

static rt_err_t sunxi_dma_build_llis(struct sunxi_dma_channel *channel,
        rt_ubase_t memory, rt_size_t length, rt_size_t period,
        enum rt_dma_transfer_direction direction, rt_bool_t cyclic)
{
    rt_size_t count;
    rt_size_t index;
    rt_ubase_t source;
    rt_ubase_t destination;
    rt_uint32_t config;
    rt_err_t err;

    if (!length || (!cyclic && length > SUNXI_DMA_MAX_TRANSFER) ||
            (cyclic && (!period || length % period ||
                        period > SUNXI_DMA_MAX_TRANSFER)))
    {
        return -RT_EINVAL;
    }

    count = cyclic ? length / period : 1;
    if ((err = sunxi_dma_alloc_llis(channel, count)))
    {
        return err;
    }

    config = sunxi_dma_config_value(channel, direction);
    for (index = 0; index < count; ++index)
    {
        struct sunxi_dma_lli *lli = &channel->llis[index];
        rt_size_t item_length = cyclic ? period : length;

        if (direction == RT_DMA_MEM_TO_DEV)
        {
            source = memory + index * item_length;
            destination = channel->parent.conf.dst_addr;
        }
        else if (direction == RT_DMA_DEV_TO_MEM)
        {
            source = channel->parent.conf.src_addr;
            destination = memory + index * item_length;
        }
        else
        {
            source = channel->parent.transfer.src_addr;
            destination = channel->parent.transfer.dst_addr;
        }

        /* The LLI format stores byte addresses in 32 bits. */
        if (source > RT_UINT32_MAX || destination > RT_UINT32_MAX ||
                item_length - 1 > RT_UINT32_MAX - source ||
                item_length - 1 > RT_UINT32_MAX - destination)
        {
            return -RT_EINVAL;
        }
        lli->config = config;
        lli->src = source;
        lli->dst = destination;
        lli->length = item_length;
        lli->parameter = SUNXI_DMA_LLI_WAIT;
        if (index + 1 < count)
        {
            lli->next = channel->llis_dma + (index + 1) * sizeof(*lli);
        }
        else if (cyclic)
        {
            lli->next = channel->llis_dma;
        }
        else
        {
            lli->next = SUNXI_DMA_LLI_LAST;
        }
    }

    channel->transfer_size = length;
    channel->period_size = cyclic ? period : length;
    channel->memory = memory;
    channel->direction = direction;
    channel->cyclic = cyclic;
    return RT_EOK;
}

static struct rt_dma_chan *sunxi_dma_request_channel(
        struct rt_dma_controller *controller, struct rt_device *slave,
        void *fw_data)
{
    struct rt_ofw_cell_args *args = fw_data;
    struct sunxi_dma *dma = to_sunxi_dma(controller);
    struct sunxi_dma_channel *channel = RT_NULL;
    rt_uint32_t request = 0;
    rt_size_t index;

    if (args)
    {
        if (args->args_count != 1 || args->args[0] >= dma->requests_nr)
        {
            return rt_err_ptr(-RT_EINVAL);
        }
        request = args->args[0];
    }

    for (index = 0; index < dma->channels_nr; ++index)
    {
        if (!dma->channels[index].allocated)
        {
            channel = &dma->channels[index];
            break;
        }
    }
    if (!channel)
    {
        return rt_err_ptr(-RT_EBUSY);
    }

    channel->allocated = RT_TRUE;
    channel->active = RT_FALSE;
    channel->cyclic = RT_FALSE;
    channel->request = request;
    channel->parent.slave = slave;

    return &channel->parent;
}

static rt_err_t sunxi_dma_stop(struct rt_dma_chan *raw);

static rt_err_t sunxi_dma_release_channel(struct rt_dma_chan *raw)
{
    struct sunxi_dma_channel *channel = to_sunxi_dma_channel(raw);

    sunxi_dma_stop(raw);
    sunxi_dma_free_llis(channel);
    channel->allocated = RT_FALSE;
    channel->active = RT_FALSE;
    channel->cyclic = RT_FALSE;
    return RT_EOK;
}

static rt_err_t sunxi_dma_stop(struct rt_dma_chan *raw)
{
    struct sunxi_dma_channel *channel = to_sunxi_dma_channel(raw);
    void *base = sunxi_dma_channel_base(channel);

    HWREG32(base + SUNXI_DMA_CHANNEL_ENABLE) = 0;
    HWREG32(base + SUNXI_DMA_CHANNEL_PAUSE) = SUNXI_DMA_CHANNEL_PAUSE_RESUME;
    channel->active = RT_FALSE;
    return RT_EOK;
}

static rt_err_t sunxi_dma_pause(struct rt_dma_chan *raw)
{
    struct sunxi_dma_channel *channel = to_sunxi_dma_channel(raw);

    HWREG32(sunxi_dma_channel_base(channel) + SUNXI_DMA_CHANNEL_PAUSE) = RT_BIT(1);
    return RT_EOK;
}

static rt_err_t sunxi_dma_config(struct rt_dma_chan *raw,
        struct rt_dma_slave_config *config)
{
    RT_UNUSED(raw);

    if (config->direction == RT_DMA_MEM_TO_DEV)
    {
        if (sunxi_dma_width_code(config->dst_addr_width) == RT_UINT32_MAX ||
                (config->src_addr_width != RT_DMA_SLAVE_BUSWIDTH_UNDEFINED &&
                 sunxi_dma_width_code(config->src_addr_width) == RT_UINT32_MAX))
        {
            return -RT_EINVAL;
        }
    }
    else if (config->direction == RT_DMA_DEV_TO_MEM)
    {
        if (sunxi_dma_width_code(config->src_addr_width) == RT_UINT32_MAX ||
                (config->dst_addr_width != RT_DMA_SLAVE_BUSWIDTH_UNDEFINED &&
                 sunxi_dma_width_code(config->dst_addr_width) == RT_UINT32_MAX))
        {
            return -RT_EINVAL;
        }
    }
    else if (config->direction != RT_DMA_MEM_TO_MEM)
    {
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t sunxi_dma_prep_memcpy(struct rt_dma_chan *raw,
        rt_ubase_t source, rt_ubase_t destination, rt_size_t length)
{
    struct sunxi_dma_channel *channel = to_sunxi_dma_channel(raw);

    channel->parent.transfer.src_addr = source;
    channel->parent.transfer.dst_addr = destination;
    return sunxi_dma_build_llis(channel, 0, length, 0, RT_DMA_MEM_TO_MEM,
            RT_FALSE);
}

static rt_err_t sunxi_dma_prep_single(struct rt_dma_chan *raw,
        rt_ubase_t memory, rt_size_t length, enum rt_dma_transfer_direction direction)
{
    return sunxi_dma_build_llis(to_sunxi_dma_channel(raw), memory, length, 0,
            direction, RT_FALSE);
}

static rt_err_t sunxi_dma_prep_cyclic(struct rt_dma_chan *raw,
        rt_ubase_t memory, rt_size_t length, rt_size_t period,
        enum rt_dma_transfer_direction direction)
{
    return sunxi_dma_build_llis(to_sunxi_dma_channel(raw), memory, length,
            period, direction, RT_TRUE);
}

static rt_err_t sunxi_dma_start(struct rt_dma_chan *raw)
{
    struct sunxi_dma_channel *channel = to_sunxi_dma_channel(raw);
    struct sunxi_dma *dma = channel->dma;
    rt_uint32_t shift = (channel->id % SUNXI_DMA_IRQ_CHANNELS) *
            SUNXI_DMA_IRQ_WIDTH;
    rt_uint32_t group = channel->id / SUNXI_DMA_IRQ_CHANNELS;
    rt_uint32_t irq_mask = channel->cyclic ? SUNXI_DMA_IRQ_PACKAGE :
            SUNXI_DMA_IRQ_QUEUE;
    rt_uint32_t value;
    void *base = sunxi_dma_channel_base(channel);

    if (!channel->llis || channel->active)
    {
        return -RT_EBUSY;
    }

    value = HWREG32(dma->base + SUNXI_DMA_IRQ_STATUS(group));
    HWREG32(dma->base + SUNXI_DMA_IRQ_STATUS(group)) = value;
    value = HWREG32(dma->base + SUNXI_DMA_IRQ_ENABLE(group));
    value &= ~(SUNXI_DMA_IRQ_MASK << shift);
    value |= irq_mask << shift;
    HWREG32(dma->base + SUNXI_DMA_IRQ_ENABLE(group)) = value;

    sunxi_dma_sync_for_device(channel);
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, channel->llis, channel->llis_size);
    HWREG32(base + SUNXI_DMA_CHANNEL_LLI) = channel->llis_dma;
    HWREG32(base + SUNXI_DMA_CHANNEL_PAUSE) = SUNXI_DMA_CHANNEL_PAUSE_RESUME;
    HWREG32(base + SUNXI_DMA_CHANNEL_ENABLE) = SUNXI_DMA_CHANNEL_START;
    channel->active = RT_TRUE;
    return RT_EOK;
}

static const struct rt_dma_controller_ops sunxi_dma_ops =
{
    .request_chan = sunxi_dma_request_channel,
    .release_chan = sunxi_dma_release_channel,
    .start = sunxi_dma_start,
    .pause = sunxi_dma_pause,
    .stop = sunxi_dma_stop,
    .config = sunxi_dma_config,
    .prep_memcpy = sunxi_dma_prep_memcpy,
    .prep_cyclic = sunxi_dma_prep_cyclic,
    .prep_single = sunxi_dma_prep_single,
};

static void sunxi_dma_isr(int irq, void *parameter)
{
    struct sunxi_dma *dma = parameter;
    rt_uint32_t group;

    RT_UNUSED(irq);

    for (group = 0; group < (dma->channels_nr + SUNXI_DMA_IRQ_CHANNELS - 1) /
            SUNXI_DMA_IRQ_CHANNELS; ++group)
    {
        rt_uint32_t pending = HWREG32(dma->base + SUNXI_DMA_IRQ_STATUS(group));
        rt_uint32_t index;

        if (!pending)
        {
            continue;
        }
        HWREG32(dma->base + SUNXI_DMA_IRQ_STATUS(group)) = pending;

        for (index = 0; index < SUNXI_DMA_IRQ_CHANNELS; ++index)
        {
            rt_uint32_t status = (pending >> (index * SUNXI_DMA_IRQ_WIDTH)) & 0xf;
            rt_uint32_t channel_id = group * SUNXI_DMA_IRQ_CHANNELS + index;
            struct sunxi_dma_channel *channel;

            if (!status || channel_id >= dma->channels_nr)
            {
                continue;
            }

            channel = &dma->channels[channel_id];
            if (!channel->active)
            {
                continue;
            }

            if (channel->cyclic && (status & SUNXI_DMA_IRQ_PACKAGE))
            {
                rt_dma_chan_done(&channel->parent, channel->period_size);
            }
            else if (!channel->cyclic && (status & SUNXI_DMA_IRQ_QUEUE))
            {
                HWREG32(sunxi_dma_channel_base(channel) +
                        SUNXI_DMA_CHANNEL_ENABLE) = 0;
                channel->active = RT_FALSE;
                sunxi_dma_sync_for_cpu(channel);
                rt_dma_chan_done(&channel->parent, channel->transfer_size);
            }
        }
    }
}

static void sunxi_dma_release(struct sunxi_dma *dma)
{
    if (dma->irq_installed)
    {
        rt_hw_interrupt_mask(dma->irq);
        rt_pic_detach_irq(dma->irq, dma);
    }
    if (dma->mbus_clk_enabled)
    {
        rt_clk_disable_unprepare(dma->mbus_clk);
    }
    if (!rt_is_err_or_null(dma->mbus_clk))
    {
        rt_clk_put(dma->mbus_clk);
    }
    if (dma->bus_clk_enabled)
    {
        rt_clk_disable_unprepare(dma->bus_clk);
    }
    if (!rt_is_err_or_null(dma->bus_clk))
    {
        rt_clk_put(dma->bus_clk);
    }
    if (dma->reset_deasserted)
    {
        rt_reset_control_assert(dma->reset);
    }
    if (!rt_is_err_or_null(dma->reset))
    {
        rt_reset_control_put(dma->reset);
    }
    if (dma->base)
    {
        rt_iounmap(dma->base);
    }
    rt_free(dma->channels);
    rt_free(dma);
}

static rt_err_t sunxi_dma_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    const struct sunxi_dma_soc_data *soc_data = pdev->id->data;
    struct sunxi_dma *dma;
    rt_size_t index;

    if (!soc_data)
    {
        return -RT_EINVAL;
    }
    dma = rt_calloc(1, sizeof(*dma));
    if (!dma)
    {
        return -RT_ENOMEM;
    }
    dma->irq = -1;
    dma->channels_nr = SUNXI_DMA_MAX_CHANNELS;
    dma->requests_nr = soc_data->requests_max;

    dma->base = rt_dm_dev_iomap(dev, 0);
    if (!dma->base)
    {
        err = -RT_EIO;
        goto _fail;
    }
    dma->bus_clk = rt_clk_get_by_index(dev, 0);
    dma->mbus_clk = rt_clk_get_by_index(dev, 1);
    dma->reset = rt_reset_control_get_by_index(dev, 0);
    if (rt_is_err(dma->bus_clk) || rt_is_err(dma->mbus_clk) || rt_is_err(dma->reset))
    {
        err = rt_is_err(dma->bus_clk) ? rt_ptr_err(dma->bus_clk) :
                (rt_is_err(dma->mbus_clk) ? rt_ptr_err(dma->mbus_clk) :
                rt_ptr_err(dma->reset));
        goto _fail;
    }
    rt_dm_dev_prop_read_u32(dev, "dma-channels", &dma->channels_nr);
    rt_dm_dev_prop_read_u32(dev, "dma-requests", &dma->requests_nr);
    if (!dma->channels_nr || dma->channels_nr > SUNXI_DMA_MAX_CHANNELS ||
            !dma->requests_nr || dma->requests_nr >
            soc_data->requests_max)
    {
        err = -RT_EINVAL;
        goto _fail;
    }
    if ((dma->irq = rt_dm_dev_get_irq(dev, 0)) < 0)
    {
        err = dma->irq;
        goto _fail;
    }
    if ((err = rt_reset_control_deassert(dma->reset)))
    {
        goto _fail;
    }
    dma->reset_deasserted = RT_TRUE;
    if ((err = rt_clk_prepare_enable(dma->bus_clk)))
    {
        goto _fail;
    }
    dma->bus_clk_enabled = RT_TRUE;
    if ((err = rt_clk_prepare_enable(dma->mbus_clk)))
    {
        goto _fail;
    }
    dma->mbus_clk_enabled = RT_TRUE;

    if (soc_data->enable_mbus)
    {
        /* H616 manual: keep the MCLK interface active during initialization. */
        HWREG32(dma->base + 0x28) |= RT_BIT(2);
    }
    dma->channels = rt_calloc(dma->channels_nr, sizeof(*dma->channels));
    if (!dma->channels)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }
    for (index = 0; index < dma->channels_nr; ++index)
    {
        dma->channels[index].dma = dma;
        dma->channels[index].id = index;
    }

    dma->parent.dev = dev;
    dma->parent.ops = &sunxi_dma_ops;
    rt_dma_controller_set_addr_mask(&dma->parent, RT_DMA_ADDR_MASK(32));
    rt_dma_controller_add_direction(&dma->parent, RT_DMA_MEM_TO_MEM);
    rt_dma_controller_add_direction(&dma->parent, RT_DMA_MEM_TO_DEV);
    rt_dma_controller_add_direction(&dma->parent, RT_DMA_DEV_TO_MEM);
    if ((err = rt_dma_controller_register(&dma->parent)))
    {
        goto _fail;
    }

    rt_hw_interrupt_install(dma->irq, sunxi_dma_isr, dma, "sunxi-dma");
    dma->irq_installed = RT_TRUE;
    rt_hw_interrupt_umask(dma->irq);
    dev->user_data = dma;
    return RT_EOK;

_fail:
    sunxi_dma_release(dma);
    return err;
}

static rt_err_t sunxi_dma_remove(struct rt_platform_device *pdev)
{
    struct sunxi_dma *dma = pdev->parent.user_data;

    if (rt_dma_controller_unregister(&dma->parent))
    {
        return -RT_EBUSY;
    }
    sunxi_dma_release(dma);
    return RT_EOK;
}

static const struct rt_ofw_node_id sunxi_dma_ofw_ids[] =
{
    { .compatible = "allwinner,sun252i-f101-dma", .data = &sunxi_dma_data },
    { .compatible = "allwinner,sun20i-d1-dma", .data = &sunxi_dma_data },
    { .compatible = "allwinner,sun50i-h616-dma", .data = &sunxi_dma_h616_data },
    { /* sentinel */ }
};

static struct rt_platform_driver sunxi_dma_driver =
{
    .name = "sunxi-dma",
    .ids = sunxi_dma_ofw_ids,
    .probe = sunxi_dma_probe,
    .remove = sunxi_dma_remove,
};

/* Register the DMA provider before devices request slave channels. */
static int sunxi_dma_driver_register(void)
{
    return rt_platform_driver_register(&sunxi_dma_driver);
}
INIT_SUBSYS_EXPORT(sunxi_dma_driver_register);
