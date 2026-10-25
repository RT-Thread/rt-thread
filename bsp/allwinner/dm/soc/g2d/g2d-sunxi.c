/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "g2d.sunxi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <ioremap.h>
#include <sunxi-g2d.h>
#include "g2d_sunxi_hw.h"

#define SUNXI_G2D_THREAD0_OFFSET            0x0100

#define SUNXI_G2D_RESET                     0x0010
#define SUNXI_G2D_CLK_GATE                  0x0014
#define SUNXI_G2D_MCLK_GATE                 0x0018
#define SUNXI_G2D_MODE_CTL                  0x0020
#define SUNXI_G2D_CORE_STATUS               0x0028
#define SUNXI_G2D_VERSION                   0x0000
#define SUNXI_G2D_CACHE_CONTROL             0x0050
#define SUNXI_G2D_CACHE_SIZE0               0x0054
#define SUNXI_G2D_CACHE_SIZE1               0x0058
#define SUNXI_G2D_MBUS_LIMIT                0x0064

#define SUNXI_G2D_THREAD_IRQ_EN             0x0000
#define SUNXI_G2D_THREAD_IRQ                0x0004
#define SUNXI_G2D_THREAD_TASK_ID            0x0008
#define SUNXI_G2D_THREAD_TIMEOUT_INFO       0x000c
#define SUNXI_G2D_THREAD_RCQ_ADDR_LO        0x0010
#define SUNXI_G2D_THREAD_RCQ_ADDR_HI_LEN    0x0014
#define SUNXI_G2D_THREAD_RCQ_ATTR           0x0018
#define SUNXI_G2D_THREAD_RCQ_UPDATE         0x001c

#define SUNXI_G2D_CORE_ENABLE               RT_BIT(0)
#define SUNXI_G2D_THREAD0_ENABLE            RT_BIT(16)
#define SUNXI_G2D_MASTER_MODE               RT_BIT(0)
#define SUNXI_G2D_THREAD_DONE_IRQ           RT_BIT(0)
#define SUNXI_G2D_THREAD_TIMEOUT_IRQ        RT_BIT(8)
#define SUNXI_G2D_THREAD_DONE_IRQ_GEN       RT_BIT(16)
#define SUNXI_G2D_RCQ_UPDATE                RT_BIT(0)

#define SUNXI_G2D_MAX_RCQ_HEADERS           256
#define SUNXI_G2D_DEFAULT_TIMEOUT_MS        100
#define SUNXI_G2D_COMMAND_BYTES              2560

struct sunxi_g2d_buffer_entry
{
    rt_list_t list;
    struct sunxi_g2d_buffer buffer;
    rt_bool_t allocated;
};

struct sunxi_g2d
{
    struct rt_device parent;
    struct rt_device *dev;
    struct rt_clk *mod_clk;
    struct rt_clk *bus_clk;
    struct rt_clk *mbus_clk;
    struct rt_reset_control *resets;
    void *base;
    int irq;

    struct rt_mutex lock;
    struct rt_completion completion;
    rt_list_t buffers;
    struct sunxi_g2d_buffer command_buffer;
    rt_uint32_t version;
    rt_bool_t mod_clock_enabled;
    rt_bool_t bus_clock_enabled;
    rt_bool_t mbus_clock_enabled;
    rt_bool_t lock_initialized;
    rt_bool_t device_registered;
    rt_bool_t irq_installed;
    rt_bool_t running;
    rt_uint32_t completion_status;
};

#define raw_to_sunxi_g2d(raw) \
    rt_container_of(raw, struct sunxi_g2d, parent)

static rt_uint32_t sunxi_g2d_readl(struct sunxi_g2d *g2d,
        rt_uint32_t offset)
{
    return HWREG32(g2d->base + offset);
}

static void sunxi_g2d_writel(struct sunxi_g2d *g2d, rt_uint32_t offset,
        rt_uint32_t value)
{
    HWREG32(g2d->base + offset) = value;
}

static void sunxi_g2d_set_bits(struct sunxi_g2d *g2d, rt_uint32_t offset,
        rt_uint32_t bits)
{
    sunxi_g2d_writel(g2d, offset, sunxi_g2d_readl(g2d, offset) | bits);
}

static void sunxi_g2d_hw_reset(struct sunxi_g2d *g2d)
{
    sunxi_g2d_set_bits(g2d, SUNXI_G2D_CLK_GATE,
            SUNXI_G2D_CORE_ENABLE);
    sunxi_g2d_set_bits(g2d, SUNXI_G2D_MCLK_GATE,
            RT_BIT(0) | RT_BIT(16));
    sunxi_g2d_set_bits(g2d, SUNXI_G2D_RESET,
            SUNXI_G2D_CORE_ENABLE);
    sunxi_g2d_set_bits(g2d, SUNXI_G2D_CLK_GATE,
            SUNXI_G2D_THREAD0_ENABLE);
    sunxi_g2d_set_bits(g2d, SUNXI_G2D_RESET,
            SUNXI_G2D_THREAD0_ENABLE);
}

static void sunxi_g2d_configure_memory(struct sunxi_g2d *g2d)
{
    rt_uint32_t value;

    sunxi_g2d_set_bits(g2d, SUNXI_G2D_CACHE_CONTROL, RT_BIT(16));

    value = sunxi_g2d_readl(g2d, SUNXI_G2D_CACHE_SIZE0);
    sunxi_g2d_writel(g2d, SUNXI_G2D_CACHE_SIZE0,
            (value & ~0xffU) | 0x40U);
    value = sunxi_g2d_readl(g2d, SUNXI_G2D_CACHE_SIZE1);
    sunxi_g2d_writel(g2d, SUNXI_G2D_CACHE_SIZE1,
            (value & ~0xffU) | 0x40U);

    value = sunxi_g2d_readl(g2d, SUNXI_G2D_MBUS_LIMIT);
    value &= ~(0x1ffU | RT_BIT(16));
    sunxi_g2d_writel(g2d, SUNXI_G2D_MBUS_LIMIT,
            value | 0x90U | RT_BIT(16));
}

static struct sunxi_g2d_buffer_entry *sunxi_g2d_find_buffer(
        struct sunxi_g2d *g2d, const struct sunxi_g2d_buffer *buffer)
{
    struct sunxi_g2d_buffer_entry *entry;

    if (!buffer)
    {
        return RT_NULL;
    }

    rt_list_for_each_entry(entry, &g2d->buffers, list)
    {
        if (entry->buffer.virt_addr == buffer->virt_addr &&
            entry->buffer.phys_addr == buffer->phys_addr &&
            entry->buffer.size == buffer->size)
        {
            return entry;
        }
    }

    return RT_NULL;
}

/*
 * F101 currently runs without an MMU, where the nominally coherent DMA-pool
 * mapping is still cacheable.  Keep G2D's command and image buffers coherent
 * at the hardware boundary just as the native DMA driver does.
 */
static void sunxi_g2d_sync_for_device(struct sunxi_g2d *g2d)
{
#ifndef ARCH_MM_MMU
    struct sunxi_g2d_buffer_entry *entry;

    rt_list_for_each_entry(entry, &g2d->buffers, list)
    {
        rt_hw_cpu_dcache_clean_and_invalidate(entry->buffer.virt_addr,
                entry->buffer.size);
    }
    rt_hw_cpu_dcache_clean_and_invalidate(g2d->command_buffer.virt_addr,
            g2d->command_buffer.size);
#else
    RT_UNUSED(g2d);
#endif
}

static void sunxi_g2d_sync_for_cpu(struct sunxi_g2d *g2d)
{
#ifndef ARCH_MM_MMU
    struct sunxi_g2d_buffer_entry *entry;

    rt_list_for_each_entry(entry, &g2d->buffers, list)
    {
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_INVALIDATE, entry->buffer.virt_addr,
                entry->buffer.size);
    }
#else
    RT_UNUSED(g2d);
#endif
}

static rt_err_t sunxi_g2d_alloc_buffer(struct sunxi_g2d *g2d,
        struct sunxi_g2d_buffer *buffer)
{
    struct sunxi_g2d_buffer_entry *entry;
    rt_ubase_t physical;

    if (!buffer || !buffer->size)
    {
        return -RT_EINVAL;
    }

    entry = rt_calloc(1, sizeof(*entry));
    if (!entry)
    {
        return -RT_ENOMEM;
    }

    buffer->virt_addr = rt_dma_alloc_coherent(g2d->dev, buffer->size,
            &physical);
    if (!buffer->virt_addr)
    {
        rt_free(entry);
        return -RT_ENOMEM;
    }

    buffer->phys_addr = physical;
    entry->buffer = *buffer;
    entry->allocated = RT_TRUE;
    rt_list_insert_before(&g2d->buffers, &entry->list);

    return RT_EOK;
}

static rt_err_t sunxi_g2d_free_buffer(struct sunxi_g2d *g2d,
        struct sunxi_g2d_buffer *buffer)
{
    struct sunxi_g2d_buffer_entry *entry;

    entry = sunxi_g2d_find_buffer(g2d, buffer);
    if (!entry)
    {
        return -RT_EINVAL;
    }

    rt_list_remove(&entry->list);
    if (entry->allocated)
    {
        rt_dma_free_coherent(g2d->dev, entry->buffer.size,
                entry->buffer.virt_addr, entry->buffer.phys_addr);
    }
    rt_memset(buffer, 0, sizeof(*buffer));
    rt_free(entry);

    return RT_EOK;
}

static rt_err_t sunxi_g2d_import_buffer(struct sunxi_g2d *g2d,
        struct sunxi_g2d_buffer *buffer)
{
    struct sunxi_g2d_buffer_entry *entry;

    if (!buffer || !buffer->virt_addr || !buffer->size ||
        sunxi_g2d_find_buffer(g2d, buffer))
    {
        return -RT_EINVAL;
    }

    if (!buffer->phys_addr)
    {
        buffer->phys_addr = (rt_ubase_t)rt_kmem_v2p(buffer->virt_addr);
    }
    entry = rt_calloc(1, sizeof(*entry));
    if (!entry)
    {
        return -RT_ENOMEM;
    }
    entry->buffer = *buffer;
    rt_list_insert_before(&g2d->buffers, &entry->list);
    return RT_EOK;
}

static rt_err_t sunxi_g2d_submit_rcq(struct sunxi_g2d *g2d,
        const struct sunxi_g2d_rcq_submit *submit);

static rt_err_t sunxi_g2d_surface_to_backend(struct sunxi_g2d *g2d,
        const struct sunxi_g2d_surface *surface,
        struct g2d_surface *backend)
{
    rt_uint32_t plane;

    if (!surface || !backend ||
        (rt_uint32_t)surface->format >= SUNXI_G2D_FORMAT_MAX)
    {
        return -RT_EINVAL;
    }

    rt_memset(backend, 0, sizeof(*backend));
    backend->format = (enum g2d_format)surface->format;
    backend->width = surface->width;
    backend->height = surface->height;

    for (plane = 0; plane < RT_ARRAY_SIZE(surface->plane); ++plane)
    {
        const struct sunxi_g2d_plane *input = &surface->plane[plane];
        struct sunxi_g2d_buffer_entry *entry;
        rt_ubase_t address;

        if (!input->buffer)
        {
            continue;
        }
        entry = sunxi_g2d_find_buffer(g2d, input->buffer);
        if (!entry || input->offset >= entry->buffer.size)
        {
            return -RT_EINVAL;
        }
        address = entry->buffer.phys_addr + input->offset;
        if ((rt_uint64_t)address >> 32)
        {
            return -RT_EINVAL;
        }
        backend->plane[plane] = (void *)address;
        backend->pitch[plane] = input->pitch;
    }

    return RT_EOK;
}

static void sunxi_g2d_image_to_surface(const struct sunxi_g2d_image *image,
        struct sunxi_g2d_surface *surface)
{
    rt_memset(surface, 0, sizeof(*surface));
    surface->format = image->format;
    surface->width = image->width;
    surface->height = image->height;
    surface->plane[0].buffer = image->buffer;
    surface->plane[0].pitch = image->pitch;
}

static rt_err_t sunxi_g2d_compose(struct sunxi_g2d *g2d,
        const struct sunxi_g2d_operation *operation)
{
    struct sunxi_g2d_buffer *command_buffer = &g2d->command_buffer;
    struct g2d_cmdlist command_list;
    struct g2d_op backend;
    struct sunxi_g2d_rcq_submit submit;
    rt_size_t header_size;
    int ret;

    if (!operation || (rt_uint32_t)operation->type >
            SUNXI_G2D_OPERATION_BLEND)
    {
        return -RT_EINVAL;
    }

    rt_memset(&backend, 0, sizeof(backend));
    backend.type = (enum g2d_op_type)operation->type;
    backend.flags = operation->flags;
    backend.color = operation->color;
    backend.rotation = (enum g2d_rotation)operation->rotation;
    backend.dst_rect.x = operation->destination_rect.x;
    backend.dst_rect.y = operation->destination_rect.y;
    backend.dst_rect.width = operation->destination_rect.width;
    backend.dst_rect.height = operation->destination_rect.height;
    backend.src_rect.x = operation->source_rect.x;
    backend.src_rect.y = operation->source_rect.y;
    backend.src_rect.width = operation->source_rect.width;
    backend.src_rect.height = operation->source_rect.height;
    backend.bg_rect.x = operation->background_rect.x;
    backend.bg_rect.y = operation->background_rect.y;
    backend.bg_rect.width = operation->background_rect.width;
    backend.bg_rect.height = operation->background_rect.height;
    backend.blend.mode = (enum g2d_blend_mode)operation->blend.mode;
    backend.blend.fg_alpha_mode =
            (enum g2d_alpha_mode)operation->blend.foreground_alpha_mode;
    backend.blend.fg_alpha = operation->blend.foreground_alpha;
    backend.blend.bg_alpha_mode =
            (enum g2d_alpha_mode)operation->blend.background_alpha_mode;
    backend.blend.bg_alpha = operation->blend.background_alpha;
    backend.blend.color_key = operation->blend.color_key;
    backend.blend.color_key_min = operation->blend.color_key_min;
    backend.blend.color_key_max = operation->blend.color_key_max;

    ret = sunxi_g2d_surface_to_backend(g2d, &operation->destination,
            &backend.dst);
    if (!ret && operation->type != SUNXI_G2D_OPERATION_FILL)
    {
        ret = sunxi_g2d_surface_to_backend(g2d, &operation->source,
                &backend.src);
    }
    if (!ret && operation->type == SUNXI_G2D_OPERATION_BLEND)
    {
        ret = sunxi_g2d_surface_to_backend(g2d, &operation->background,
                &backend.bg);
    }
    if (ret)
    {
        return ret;
    }

    g2d_cmdlist_init(&command_list, command_buffer->virt_addr,
            command_buffer->size);
    ret = g2d_compose(&command_list, &backend);
    if (ret)
    {
        return ret;
    }
    header_size = g2d_cmdlist_finish(&command_list);
    if (!header_size)
    {
        return -RT_EINVAL;
    }

    submit.buffer = command_buffer;
    submit.header_offset = 0;
    submit.header_count = header_size /
            sizeof(struct sunxi_g2d_rcq_header);
    submit.timeout = operation->timeout;
    return sunxi_g2d_submit_rcq(g2d, &submit);
}

static rt_err_t sunxi_g2d_fill(struct sunxi_g2d *g2d,
        const struct sunxi_g2d_fill *fill)
{
    struct sunxi_g2d_operation operation;

    if (!fill || !fill->destination)
    {
        return -RT_EINVAL;
    }
    rt_memset(&operation, 0, sizeof(operation));
    operation.type = SUNXI_G2D_OPERATION_FILL;
    operation.color = fill->color;
    operation.destination_rect = fill->rect;
    operation.timeout = fill->timeout;
    sunxi_g2d_image_to_surface(fill->destination, &operation.destination);
    return sunxi_g2d_compose(g2d, &operation);
}

static rt_err_t sunxi_g2d_blit(struct sunxi_g2d *g2d,
        const struct sunxi_g2d_blit *blit)
{
    struct sunxi_g2d_operation operation;

    if (!blit || !blit->source || !blit->destination)
    {
        return -RT_EINVAL;
    }
    rt_memset(&operation, 0, sizeof(operation));
    operation.type = SUNXI_G2D_OPERATION_BLIT;
    operation.source_rect = blit->source_rect;
    operation.destination_rect = blit->destination_rect;
    operation.timeout = blit->timeout;
    sunxi_g2d_image_to_surface(blit->source, &operation.source);
    sunxi_g2d_image_to_surface(blit->destination, &operation.destination);
    return sunxi_g2d_compose(g2d, &operation);
}

static rt_err_t sunxi_g2d_submit_rcq(struct sunxi_g2d *g2d,
        const struct sunxi_g2d_rcq_submit *submit)
{
    struct sunxi_g2d_buffer_entry *entry;
    struct sunxi_g2d_buffer *buffer;
    rt_size_t header_bytes;
    rt_tick_t timeout;
    rt_uint64_t header_address;
    rt_uint32_t thread_base = SUNXI_G2D_THREAD0_OFFSET;
    rt_err_t err;

    if (!submit || !submit->buffer || !submit->header_count ||
        submit->header_count > SUNXI_G2D_MAX_RCQ_HEADERS ||
        (submit->header_offset & 31))
    {
        return -RT_EINVAL;
    }

    if (submit->buffer == &g2d->command_buffer)
    {
        buffer = &g2d->command_buffer;
    }
    else
    {
        entry = sunxi_g2d_find_buffer(g2d, submit->buffer);
        buffer = entry ? &entry->buffer : RT_NULL;
    }
    header_bytes = (rt_size_t)submit->header_count *
            sizeof(struct sunxi_g2d_rcq_header);
    if (!buffer || submit->header_offset > buffer->size ||
        header_bytes > buffer->size - submit->header_offset)
    {
        return -RT_EINVAL;
    }
    header_address = (rt_uint64_t)buffer->phys_addr +
            submit->header_offset;
    if (header_address >> 40)
    {
        return -RT_EINVAL;
    }

    timeout = submit->timeout ? submit->timeout :
            rt_tick_from_millisecond(SUNXI_G2D_DEFAULT_TIMEOUT_MS);
    g2d->running = RT_TRUE;
    g2d->completion_status = 0;
    rt_completion_init(&g2d->completion);

    /* Enter master mode for this RCQ submission, as required by G2D-200. */
    sunxi_g2d_set_bits(g2d, SUNXI_G2D_MODE_CTL, SUNXI_G2D_MASTER_MODE);
    sunxi_g2d_writel(g2d, thread_base + SUNXI_G2D_THREAD_IRQ,
            SUNXI_G2D_THREAD_DONE_IRQ | SUNXI_G2D_THREAD_TIMEOUT_IRQ);
    sunxi_g2d_writel(g2d, thread_base + SUNXI_G2D_THREAD_IRQ_EN,
            SUNXI_G2D_THREAD_DONE_IRQ | SUNXI_G2D_THREAD_TIMEOUT_IRQ);
    sunxi_g2d_writel(g2d, thread_base + SUNXI_G2D_THREAD_RCQ_ADDR_LO,
            (rt_uint32_t)header_address);
    sunxi_g2d_writel(g2d, thread_base + SUNXI_G2D_THREAD_RCQ_ADDR_HI_LEN,
            ((rt_uint32_t)(header_address >> 32)) |
            ((rt_uint32_t)header_bytes << 16));
    sunxi_g2d_writel(g2d, thread_base + SUNXI_G2D_THREAD_RCQ_ATTR,
            SUNXI_G2D_THREAD_DONE_IRQ_GEN);
    sunxi_g2d_sync_for_device(g2d);
    rt_hw_dsb();

    sunxi_g2d_writel(g2d, thread_base + SUNXI_G2D_THREAD_RCQ_UPDATE,
            SUNXI_G2D_RCQ_UPDATE);

    err = rt_completion_wait(&g2d->completion, timeout);
    g2d->running = RT_FALSE;
    if (err)
    {
        LOG_E("G2D command timed out: irq=%08x task=%08x timeout=%08x core=%08x",
                sunxi_g2d_readl(g2d, thread_base + SUNXI_G2D_THREAD_IRQ),
                sunxi_g2d_readl(g2d, thread_base + SUNXI_G2D_THREAD_TASK_ID),
                sunxi_g2d_readl(g2d,
                thread_base + SUNXI_G2D_THREAD_TIMEOUT_INFO),
                sunxi_g2d_readl(g2d, SUNXI_G2D_CORE_STATUS));
        sunxi_g2d_hw_reset(g2d);
        return -RT_ETIMEOUT;
    }

    sunxi_g2d_sync_for_cpu(g2d);
    return RT_EOK;
}

static rt_err_t sunxi_g2d_control(rt_device_t dev, int cmd, void *args)
{
    struct sunxi_g2d *g2d = raw_to_sunxi_g2d(dev);
    rt_err_t err;

    rt_mutex_take(&g2d->lock, RT_WAITING_FOREVER);

    switch (cmd)
    {
    case SUNXI_G2D_CMD_ALLOC_BUFFER:
        err = sunxi_g2d_alloc_buffer(g2d, args);
        break;
    case SUNXI_G2D_CMD_FREE_BUFFER:
        err = g2d->running ? -RT_EBUSY : sunxi_g2d_free_buffer(g2d, args);
        break;
    case SUNXI_G2D_CMD_SUBMIT_RCQ:
        err = sunxi_g2d_submit_rcq(g2d, args);
        break;
    case SUNXI_G2D_CMD_GET_VERSION:
        if (!args)
        {
            err = -RT_EINVAL;
        }
        else
        {
            *(rt_uint32_t *)args = g2d->version;
            err = RT_EOK;
        }
        break;
    case SUNXI_G2D_CMD_FILL:
        err = g2d->running ? -RT_EBUSY : sunxi_g2d_fill(g2d, args);
        break;
    case SUNXI_G2D_CMD_BLIT:
        err = g2d->running ? -RT_EBUSY : sunxi_g2d_blit(g2d, args);
        break;
    case SUNXI_G2D_CMD_COMPOSE:
        err = g2d->running ? -RT_EBUSY : sunxi_g2d_compose(g2d, args);
        break;
    case SUNXI_G2D_CMD_IMPORT_BUFFER:
        err = g2d->running ? -RT_EBUSY : sunxi_g2d_import_buffer(g2d, args);
        break;
    default:
        err = -RT_ENOSYS;
        break;
    }

    rt_mutex_release(&g2d->lock);
    return err;
}

#ifdef RT_USING_DEVICE_OPS
static const struct rt_device_ops sunxi_g2d_ops =
{
    .control = sunxi_g2d_control,
};
#endif

static void sunxi_g2d_isr(int irqno, void *param)
{
    struct sunxi_g2d *g2d = param;
    rt_uint32_t status;

    RT_UNUSED(irqno);

    status = sunxi_g2d_readl(g2d, SUNXI_G2D_THREAD0_OFFSET +
            SUNXI_G2D_THREAD_IRQ);
    if (!(status & (SUNXI_G2D_THREAD_DONE_IRQ |
            SUNXI_G2D_THREAD_TIMEOUT_IRQ)))
    {
        return;
    }

    sunxi_g2d_writel(g2d, SUNXI_G2D_THREAD0_OFFSET +
            SUNXI_G2D_THREAD_IRQ, status);
    g2d->completion_status = status;
    rt_completion_done(&g2d->completion);
}

static void sunxi_g2d_release(struct sunxi_g2d *g2d)
{
    struct sunxi_g2d_buffer_entry *entry;
    struct sunxi_g2d_buffer_entry *next;

    rt_list_for_each_entry_safe(entry, next, &g2d->buffers, list)
    {
        rt_list_remove(&entry->list);
        if (entry->allocated)
        {
            rt_dma_free_coherent(g2d->dev, entry->buffer.size,
                    entry->buffer.virt_addr, entry->buffer.phys_addr);
        }
        rt_free(entry);
    }
    if (g2d->device_registered)
    {
        rt_device_unregister(&g2d->parent);
    }
    if (g2d->lock_initialized)
    {
        rt_mutex_detach(&g2d->lock);
    }
    if (!rt_is_err_or_null(g2d->resets))
    {
        rt_reset_control_assert(g2d->resets);
        rt_reset_control_put(g2d->resets);
    }
    if (!rt_is_err_or_null(g2d->mod_clk))
    {
        if (g2d->mod_clock_enabled)
        {
            rt_clk_disable_unprepare(g2d->mod_clk);
        }
        rt_clk_put(g2d->mod_clk);
    }
    if (!rt_is_err_or_null(g2d->mbus_clk))
    {
        if (g2d->mbus_clock_enabled)
        {
            rt_clk_disable_unprepare(g2d->mbus_clk);
        }
        rt_clk_put(g2d->mbus_clk);
    }
    if (!rt_is_err_or_null(g2d->bus_clk))
    {
        if (g2d->bus_clock_enabled)
        {
            rt_clk_disable_unprepare(g2d->bus_clk);
        }
        rt_clk_put(g2d->bus_clk);
    }
    if (g2d->base)
    {
        rt_iounmap(g2d->base);
    }
    if (g2d->command_buffer.virt_addr)
    {
        rt_free_align(g2d->command_buffer.virt_addr);
    }
    rt_free(g2d);
}

static rt_err_t sunxi_g2d_probe(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct sunxi_g2d *g2d;
    const char *name;
    rt_uint32_t clock_rate = 300000000U;
    rt_err_t err;

    g2d = rt_calloc(1, sizeof(*g2d));
    if (!g2d)
    {
        return -RT_ENOMEM;
    }

    g2d->dev = dev;
    g2d->irq = -1;
    rt_list_init(&g2d->buffers);
    g2d->command_buffer.size = SUNXI_G2D_COMMAND_BYTES;
    g2d->command_buffer.virt_addr = rt_malloc_align(
            g2d->command_buffer.size, 64);
    if (!g2d->command_buffer.virt_addr)
    {
        err = -RT_ENOMEM;
        goto _fail;
    }
    g2d->command_buffer.phys_addr = (rt_ubase_t)rt_kmem_v2p(
            g2d->command_buffer.virt_addr);
    rt_memset(g2d->command_buffer.virt_addr, 0,
            g2d->command_buffer.size);

    g2d->base = rt_dm_dev_iomap(dev, 0);
    if (!g2d->base)
    {
        err = -RT_EIO;
        goto _fail;
    }

    g2d->mod_clk = rt_clk_get_by_name(dev, "mod");
    if (rt_is_err_or_null(g2d->mod_clk))
    {
        err = rt_is_err(g2d->mod_clk) ? rt_ptr_err(g2d->mod_clk) : -RT_ENOENT;
        goto _fail;
    }
    g2d->bus_clk = rt_clk_get_by_name(dev, "bus");
    if (rt_is_err_or_null(g2d->bus_clk))
    {
        err = rt_is_err(g2d->bus_clk) ? rt_ptr_err(g2d->bus_clk) : -RT_ENOENT;
        goto _fail;
    }
    g2d->mbus_clk = rt_clk_get_by_name(dev, "mbus");
    if (rt_is_err_or_null(g2d->mbus_clk))
    {
        err = rt_is_err(g2d->mbus_clk) ? rt_ptr_err(g2d->mbus_clk) : -RT_ENOENT;
        goto _fail;
    }

    g2d->resets = rt_reset_control_get_by_index(dev, 0);
    if (rt_is_err(g2d->resets))
    {
        err = rt_ptr_err(g2d->resets);
        goto _fail;
    }
    if ((err = rt_reset_control_assert(g2d->resets)) != RT_EOK)
    {
        goto _fail;
    }
    if ((err = rt_clk_prepare_enable(g2d->bus_clk)) != RT_EOK)
    {
        goto _fail;
    }
    g2d->bus_clock_enabled = RT_TRUE;
    if ((err = rt_clk_prepare_enable(g2d->mbus_clk)) != RT_EOK)
    {
        goto _fail;
    }
    g2d->mbus_clock_enabled = RT_TRUE;
    if ((err = rt_reset_control_deassert(g2d->resets)) != RT_EOK)
    {
        goto _fail;
    }
    rt_dm_dev_prop_read_u32(dev, "clock-frequency", &clock_rate);
    if ((err = rt_clk_set_rate(g2d->mod_clk, clock_rate)) != RT_EOK)
    {
        goto _fail;
    }
    if ((err = rt_clk_prepare_enable(g2d->mod_clk)) != RT_EOK)
    {
        goto _fail;
    }
    g2d->mod_clock_enabled = RT_TRUE;

    g2d->irq = rt_dm_dev_get_irq(dev, 0);
    if (g2d->irq < 0)
    {
        err = g2d->irq;
        goto _fail;
    }

    sunxi_g2d_hw_reset(g2d);
    sunxi_g2d_configure_memory(g2d);
    g2d->version = sunxi_g2d_readl(g2d, SUNXI_G2D_VERSION);
    rt_dm_dev_set_name_auto(&g2d->parent, "g2d");
    name = rt_dm_dev_get_name(&g2d->parent);
    g2d->parent.type = RT_Device_Class_Miscellaneous;
#ifdef RT_USING_DEVICE_OPS
    g2d->parent.ops = &sunxi_g2d_ops;
#else
    g2d->parent.control = sunxi_g2d_control;
#endif

    if ((err = rt_mutex_init(&g2d->lock, name, RT_IPC_FLAG_PRIO)) != RT_EOK)
    {
        goto _fail;
    }
    g2d->lock_initialized = RT_TRUE;
    rt_completion_init(&g2d->completion);

    if ((err = rt_device_register(&g2d->parent, name,
            RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STANDALONE)) != RT_EOK)
    {
        goto _fail;
    }
    g2d->device_registered = RT_TRUE;

    rt_hw_interrupt_install(g2d->irq, sunxi_g2d_isr, g2d, name);
    rt_hw_interrupt_umask(g2d->irq);
    g2d->irq_installed = RT_TRUE;
    dev->user_data = g2d;

    LOG_D("G2D-200 registered as %s, version %08x, clock %u Hz", name,
            g2d->version, (rt_uint32_t)rt_clk_get_rate(g2d->mod_clk));
    return RT_EOK;

_fail:
    sunxi_g2d_release(g2d);
    return err;
}

static rt_err_t sunxi_g2d_remove(struct rt_platform_device *pdev)
{
    struct sunxi_g2d *g2d = pdev->parent.user_data;

    if (g2d->irq_installed)
    {
        rt_hw_interrupt_mask(g2d->irq);
        rt_pic_detach_irq(g2d->irq, g2d);
    }
    sunxi_g2d_release(g2d);

    return RT_EOK;
}

static const struct rt_ofw_node_id sunxi_g2d_ofw_ids[] =
{
    { .compatible = "allwinner,sun252i-f101-g2d200" },
    { .compatible = "allwinner,sunxi-g2d200" },
    { .compatible = "allwinner,sun50i-h616-g2d" },
    { .compatible = "allwinner,sunxi-g2d" },
    { /* sentinel */ }
};

static struct rt_platform_driver sunxi_g2d_driver =
{
    .name = "sunxi-g2d",
    .ids = sunxi_g2d_ofw_ids,
    .probe = sunxi_g2d_probe,
    .remove = sunxi_g2d_remove,
};
RT_PLATFORM_DRIVER_EXPORT(sunxi_g2d_driver);
