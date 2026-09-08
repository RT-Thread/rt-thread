/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include "v2d_internal.h"
#include "v2d_reg.h"

#include <spacemit.h>

#define V2D_TIMEOUT_MS              2500
#define V2D_CORE_RATE               409600000UL
#define V2D_ADDRESS_MASK            0x3ffffffffULL

struct spacemit_v2d_buffer
{
    rt_list_t list;
    V2D_BUFFER_S buffer;
};

struct spacemit_v2d
{
    struct rt_device parent;
    struct rt_device *dev;
    void *regs;
    int irq;

    struct rt_clk *clk_core;
    struct rt_clk *clk_io;
    struct rt_reset_control *reset;

    struct rt_mutex lock;
    struct rt_completion completion;
    rt_list_t buffers;

    rt_bool_t clocks_enabled;
    rt_bool_t reset_deasserted;
    rt_bool_t lock_initialized;
    rt_bool_t device_registered;

    rt_uint32_t irq_status;
    rt_uint32_t error_status;
    rt_err_t error;
};

rt_inline struct spacemit_v2d *raw_to_spacemit_v2d(struct rt_device *dev)
{
    return rt_container_of(dev, struct spacemit_v2d, parent);
}

static rt_uint64_t v2d_surface_y_address(const V2D_SURFACE_S *surface)
{
    return (rt_uint64_t)surface->phyaddr_y_l |
            ((rt_uint64_t)surface->phyaddr_y_h << 32);
}

static rt_uint64_t v2d_surface_uv_address(const V2D_SURFACE_S *surface)
{
    return (rt_uint64_t)surface->phyaddr_uv_l |
            ((rt_uint64_t)surface->phyaddr_uv_h << 32);
}

static int v2d_format_bpp(V2D_COLOR_FORMAT_E format)
{
    switch (format)
    {
    case V2D_COLOR_FORMAT_NV12:
    case V2D_COLOR_FORMAT_NV21:
    case V2D_COLOR_FORMAT_A8:
    case V2D_COLOR_FORMAT_Y8:
    case V2D_COLOR_FORMAT_L8_RGBA8888:
    case V2D_COLOR_FORMAT_L8_RGB888:
    case V2D_COLOR_FORMAT_L8_RGB565:
    case V2D_COLOR_FORMAT_L8_BGRA8888:
    case V2D_COLOR_FORMAT_L8_BGR888:
    case V2D_COLOR_FORMAT_L8_BGR565:
        return 1;
    case V2D_COLOR_FORMAT_RGB565:
    case V2D_COLOR_FORMAT_BGR565:
        return 2;
    case V2D_COLOR_FORMAT_RGB888:
    case V2D_COLOR_FORMAT_BGR888:
    case V2D_COLOR_FORMAT_RGBA5658:
    case V2D_COLOR_FORMAT_ARGB8565:
    case V2D_COLOR_FORMAT_BGRA5658:
    case V2D_COLOR_FORMAT_ABGR8565:
        return 3;
    case V2D_COLOR_FORMAT_RGBX8888:
    case V2D_COLOR_FORMAT_RGBA8888:
    case V2D_COLOR_FORMAT_ARGB8888:
    case V2D_COLOR_FORMAT_BGRX8888:
    case V2D_COLOR_FORMAT_BGRA8888:
    case V2D_COLOR_FORMAT_ABGR8888:
        return 4;
    default:
        return 0;
    }
}

static rt_bool_t v2d_range_is_allocated(struct spacemit_v2d *v2d,
        rt_uint64_t address, rt_uint64_t size)
{
    struct spacemit_v2d_buffer *entry;

    if (!address || !size || address > V2D_ADDRESS_MASK ||
        size - 1 > V2D_ADDRESS_MASK - address)
    {
        return RT_FALSE;
    }

    rt_list_for_each_entry(entry, &v2d->buffers, list)
    {
        rt_uint64_t start = entry->buffer.phys_addr;
        rt_uint64_t end = start + entry->buffer.size;

        if (address >= start && address + size <= end)
        {
            return RT_TRUE;
        }
    }

    return RT_FALSE;
}

static rt_err_t v2d_validate_rect(const V2D_AREA_S *rect,
        rt_uint16_t width, rt_uint16_t height)
{
    if (!rect->w || !rect->h || rect->x >= width || rect->y >= height ||
        rect->w > width - rect->x || rect->h > height - rect->y)
    {
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t v2d_validate_surface(struct spacemit_v2d *v2d,
        const V2D_SURFACE_S *surface, const V2D_AREA_S *rect)
{
    rt_uint64_t y_size;
    rt_uint64_t min_stride;
    rt_uint64_t address;
    int bpp;

    if (surface->fbc_enable)
    {
        return -RT_ENOSYS;
    }
    if (!surface->w || !surface->h || !surface->stride ||
        !(bpp = v2d_format_bpp(surface->format)))
    {
        return -RT_EINVAL;
    }
    if (v2d_validate_rect(rect, surface->w, surface->h) != RT_EOK)
    {
        return -RT_EINVAL;
    }

    min_stride = (rt_uint64_t)surface->w * bpp;
    if (surface->stride < min_stride)
    {
        return -RT_EINVAL;
    }

    address = v2d_surface_y_address(surface);
    y_size = (rt_uint64_t)(surface->h - 1) * surface->stride + min_stride;
    if (!v2d_range_is_allocated(v2d, address, y_size))
    {
        return -RT_EINVAL;
    }

    if (surface->format == V2D_COLOR_FORMAT_NV12 ||
        surface->format == V2D_COLOR_FORMAT_NV21)
    {
        rt_uint64_t uv_address = v2d_surface_uv_address(surface);
        rt_uint64_t uv_size = (rt_uint64_t)surface->stride *
                RT_DIV_ROUND_UP(surface->h, 2);

        if (!v2d_range_is_allocated(v2d, uv_address, uv_size))
        {
            return -RT_EINVAL;
        }
    }

    return RT_EOK;
}

static rt_bool_t v2d_layer_enabled(const V2D_SURFACE_S *surface)
{
    return surface->solidcolor.enable || surface->fbc_enable ||
            v2d_surface_y_address(surface) != 0;
}

static rt_bool_t v2d_blend_layer_valid(const V2D_BLEND_LAYER_CONF_S *blend,
        V2D_BLENDCMD_E command)
{
    if ((unsigned int)blend->blend_alpha_source >=
            V2D_BLENDALPHA_SOURCE_BUTT ||
        (unsigned int)blend->blend_pre_alpha_func >=
            V2D_BLEND_PRE_ALPHA_FUNC_BUTT)
    {
        return RT_FALSE;
    }

    if (command == V2D_BLENDCMD_ALPHA)
    {
        return (unsigned int)blend->stBlendFactor.srcColorFactor <
                    V2D_BLEND_BUTT &&
                (unsigned int)blend->stBlendFactor.dstColorFactor <
                    V2D_BLEND_BUTT &&
                (unsigned int)blend->stBlendFactor.srcAlphaFactor <
                    V2D_BLEND_BUTT &&
                (unsigned int)blend->stBlendFactor.dstAlphaFactor <
                    V2D_BLEND_BUTT;
    }

    return (unsigned int)blend->stRop2Code.colorRop2Code < V2D_ROP2_BUTT &&
            (unsigned int)blend->stRop2Code.alphaRop2Code < V2D_ROP2_BUTT;
}

static rt_err_t v2d_validate_layer(struct spacemit_v2d *v2d,
        const V2D_SURFACE_S *surface, const V2D_AREA_S *source,
        const V2D_BLEND_LAYER_CONF_S *blend, const V2D_SURFACE_S *dst)
{
    if (!v2d_layer_enabled(surface))
    {
        return RT_EOK;
    }
    if (!blend->blend_area.w || !blend->blend_area.h ||
        blend->blend_area.x >= dst->w || blend->blend_area.y >= dst->h ||
        blend->blend_area.w > dst->w - blend->blend_area.x ||
        blend->blend_area.h > dst->h - blend->blend_area.y)
    {
        return -RT_EINVAL;
    }
    if (surface->solidcolor.enable)
    {
        return surface->solidcolor.fillcolor.format < V2D_COLOR_FORMAT_BUTT ?
                RT_EOK : -RT_EINVAL;
    }

    return v2d_validate_surface(v2d, surface, source);
}

static rt_err_t v2d_validate_task(struct spacemit_v2d *v2d,
        V2D_SUBMIT_TASK_S *task)
{
    V2D_PARAM_S *param;
    rt_err_t err;

    if (!task)
    {
        return -RT_EINVAL;
    }
    param = &task->param;

    if (task->acquireFencefd != -1 ||
        param->dst.fbc_enable || param->mask.fbc_enable ||
        (unsigned int)param->l0_rt > V2D_ROT_FLIP ||
        (unsigned int)param->l1_rt > V2D_ROT_FLIP ||
        (unsigned int)param->l0_csc > V2D_CSC_MODE_BUTT ||
        (unsigned int)param->l1_csc > V2D_CSC_MODE_BUTT ||
        (unsigned int)param->dither > V2D_DITHER_8X8 ||
        (unsigned int)param->blendconf.blend_cmd >= V2D_BLENDCMD_BUTT ||
        (unsigned int)param->blendconf.mask_cmd >= V2D_MASKCMD_BUTT ||
        param->palette.len < 0 ||
        param->palette.len > (int)sizeof(param->palette.palVal) ||
        !v2d_blend_layer_valid(&param->blendconf.blendlayer[0],
                param->blendconf.blend_cmd) ||
        !v2d_blend_layer_valid(&param->blendconf.blendlayer[1],
                param->blendconf.blend_cmd))
    {
        return -RT_EINVAL;
    }
    if ((err = v2d_validate_surface(v2d, &param->dst,
            &param->dst_rect)) != RT_EOK)
    {
        return err;
    }
    if ((err = v2d_validate_layer(v2d, &param->layer0, &param->l0_rect,
            &param->blendconf.blendlayer[0], &param->dst)) != RT_EOK)
    {
        return err;
    }
    if ((err = v2d_validate_layer(v2d, &param->layer1, &param->l1_rect,
            &param->blendconf.blendlayer[1], &param->dst)) != RT_EOK)
    {
        return err;
    }
    if (!v2d_layer_enabled(&param->layer0) &&
        !v2d_layer_enabled(&param->layer1) &&
        !param->blendconf.bgcolor.enable)
    {
        return -RT_EINVAL;
    }
    if (v2d_surface_y_address(&param->mask))
    {
        if ((err = v2d_validate_surface(v2d, &param->mask,
                &param->mask_rect)) != RT_EOK)
        {
            return err;
        }
    }

    return RT_EOK;
}

static rt_err_t v2d_buffer_alloc(struct spacemit_v2d *v2d,
        V2D_BUFFER_S *buffer)
{
    struct spacemit_v2d_buffer *entry;
    rt_ubase_t phys_addr;

    if (!buffer || !buffer->size || buffer->size > V2D_BUFFER_MAX_SIZE)
    {
        return -RT_EINVAL;
    }

    entry = rt_calloc(1, sizeof(*entry));
    if (!entry)
    {
        return -RT_ENOMEM;
    }

    buffer->virt_addr = rt_dma_alloc_coherent(v2d->dev, buffer->size,
            &phys_addr);
    if (!buffer->virt_addr)
    {
        rt_free(entry);
        return -RT_ENOMEM;
    }
    buffer->phys_addr = phys_addr;
    entry->buffer = *buffer;
    rt_list_insert_before(&v2d->buffers, &entry->list);

    return RT_EOK;
}

static rt_err_t v2d_buffer_free(struct spacemit_v2d *v2d,
        V2D_BUFFER_S *buffer)
{
    struct spacemit_v2d_buffer *entry;

    if (!buffer || !buffer->virt_addr || !buffer->size)
    {
        return -RT_EINVAL;
    }

    rt_list_for_each_entry(entry, &v2d->buffers, list)
    {
        if (entry->buffer.virt_addr == buffer->virt_addr &&
            entry->buffer.phys_addr == buffer->phys_addr &&
            entry->buffer.size == buffer->size)
        {
            rt_list_remove(&entry->list);
            rt_dma_free_coherent(v2d->dev, entry->buffer.size,
                    entry->buffer.virt_addr, entry->buffer.phys_addr);
            rt_free(entry);
            buffer->virt_addr = RT_NULL;
            buffer->phys_addr = 0;
            return RT_EOK;
        }
    }

    return -RT_EINVAL;
}

static rt_err_t v2d_hard_reset(struct spacemit_v2d *v2d)
{
    rt_err_t err;

    v2d_irq_disable();
    if (!rt_is_err_or_null(v2d->reset))
    {
        if ((err = rt_reset_control_assert(v2d->reset)) != RT_EOK)
        {
            return err;
        }
        v2d->reset_deasserted = RT_FALSE;
        rt_hw_us_delay(5);
        if ((err = rt_reset_control_deassert(v2d->reset)) != RT_EOK)
        {
            return err;
        }
        v2d->reset_deasserted = RT_TRUE;
    }

    return v2d_global_reset();
}

static rt_err_t v2d_submit(struct spacemit_v2d *v2d,
        V2D_SUBMIT_TASK_S *task)
{
    rt_uint32_t status;
    rt_err_t err;

    if ((err = v2d_validate_task(v2d, task)) != RT_EOK)
    {
        return err;
    }
    task->completeFencefd = -1;

    status = v2d_irq_status();
    if (status)
    {
        v2d_irq_clear(status);
    }
    status = v2d_irqerr_status();
    if (status)
    {
        v2d_irqerr_clear(status);
    }

    rt_completion_init(&v2d->completion);
    v2d->irq_status = 0;
    v2d->error_status = 0;
    v2d->error = RT_EOK;

    v2d_irq_enable();
    config_v2d_hw(task);

    if (rt_completion_wait(&v2d->completion,
            rt_tick_from_millisecond(V2D_TIMEOUT_MS)) != RT_EOK)
    {
        LOG_E("job timeout");
        v2d_dump_irqraw_status();
        v2d_hard_reset(v2d);
        return -RT_ETIMEOUT;
    }

    v2d_irq_disable();
    if (v2d->error != RT_EOK)
    {
        LOG_E("job failed: irq=%08x error=%08x",
                v2d->irq_status, v2d->error_status);
        v2d_dump_irqraw_status();
        v2d_hard_reset(v2d);
    }

    return v2d->error;
}

static rt_err_t spacemit_v2d_control(rt_device_t dev, int cmd, void *args)
{
    rt_err_t err;
    struct spacemit_v2d *v2d = raw_to_spacemit_v2d(dev);

    rt_mutex_take(&v2d->lock, RT_WAITING_FOREVER);

    switch (cmd)
    {
    case V2D_SUBMIT:
        err = v2d_submit(v2d, args);
        break;
    case V2D_ALLOC_BUFFER:
        err = v2d_buffer_alloc(v2d, args);
        break;
    case V2D_FREE_BUFFER:
        err = v2d_buffer_free(v2d, args);
        break;
    case V2D_RESET:
        err = v2d_hard_reset(v2d);
        break;
    default:
        err = -RT_ENOSYS;
        break;
    }

    rt_mutex_release(&v2d->lock);

    return err;
}

#ifdef RT_USING_DEVICE_OPS
static const struct rt_device_ops spacemit_v2d_ops =
{
    .control = spacemit_v2d_control,
};
#endif

static void spacemit_v2d_isr(int irqno, void *param)
{
    rt_uint32_t irq_status;
    rt_uint32_t error_status;
    struct spacemit_v2d *v2d = param;

    RT_UNUSED(irqno);

    irq_status = v2d_irq_status();
    error_status = v2d_irqerr_status();

    if (error_status)
    {
        v2d_irqerr_clear(error_status);
        v2d->error_status |= error_status;
        v2d->error = -RT_EIO;
    }
    if (irq_status)
    {
        v2d_irq_clear(irq_status);
        v2d->irq_status |= irq_status;
    }

    if (error_status || (irq_status &
        (V2D_EOF_IRQ_STATUS | V2D_FBCENC_IRQ_STATUS)))
    {
        rt_completion_done(&v2d->completion);
    }
}

static rt_err_t v2d_clocks_enable(struct spacemit_v2d *v2d)
{
    rt_err_t err;

    if ((err = rt_clk_prepare_enable(v2d->clk_core)) != RT_EOK)
    {
        return err;
    }
    if ((err = rt_clk_prepare_enable(v2d->clk_io)) != RT_EOK)
    {
        rt_clk_disable_unprepare(v2d->clk_core);
        return err;
    }

    v2d->clocks_enabled = RT_TRUE;

    return RT_EOK;
}

static void v2d_clocks_disable(struct spacemit_v2d *v2d)
{
    if (!v2d->clocks_enabled)
    {
        return;
    }

    if (!rt_is_err_or_null(v2d->clk_io))
    {
        rt_clk_disable_unprepare(v2d->clk_io);
    }
    if (!rt_is_err_or_null(v2d->clk_core))
    {
        rt_clk_disable_unprepare(v2d->clk_core);
    }
    v2d->clocks_enabled = RT_FALSE;
}

static void spacemit_v2d_free(struct spacemit_v2d *v2d)
{
    struct spacemit_v2d_buffer *entry, *next;

    if (v2d->dev && v2d->dev->user_data == v2d)
    {
        v2d->dev->user_data = RT_NULL;
    }

    rt_list_for_each_entry_safe(entry, next, &v2d->buffers, list)
    {
        rt_list_remove(&entry->list);
        rt_dma_free_coherent(v2d->dev, entry->buffer.size,
                entry->buffer.virt_addr, entry->buffer.phys_addr);
        rt_free(entry);
    }

    if (v2d->device_registered)
    {
        rt_device_unregister(&v2d->parent);
        v2d->device_registered = RT_FALSE;
    }
    if (v2d->lock_initialized)
    {
        rt_mutex_detach(&v2d->lock);
        v2d->lock_initialized = RT_FALSE;
    }

    if (v2d->reset_deasserted && !rt_is_err_or_null(v2d->reset))
    {
        rt_reset_control_assert(v2d->reset);
        v2d->reset_deasserted = RT_FALSE;
    }

    v2d_clocks_disable(v2d);

    if (!rt_is_err_or_null(v2d->clk_io))
    {
        rt_clk_put(v2d->clk_io);
    }
    if (!rt_is_err_or_null(v2d->clk_core))
    {
        rt_clk_put(v2d->clk_core);
    }
    if (!rt_is_err_or_null(v2d->reset))
    {
        rt_reset_control_put(v2d->reset);
    }
    if (v2d->regs)
    {
        v2d_hw_set_base(RT_NULL);
        rt_iounmap(v2d->regs);
    }

    rt_free(v2d);
}

static rt_err_t spacemit_v2d_probe(struct rt_platform_device *pdev)
{
    const char *dev_name;
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct spacemit_v2d *v2d = rt_calloc(1, sizeof(*v2d));

    if (!v2d)
    {
        return -RT_ENOMEM;
    }
    v2d->dev = dev;
    rt_list_init(&v2d->buffers);

    v2d->regs = rt_dm_dev_iomap(dev, 0);
    if (!v2d->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }
    v2d_hw_set_base(v2d->regs);

    v2d->clk_core = rt_clk_get_by_name(dev, "v2d-core");
    if (rt_is_err(v2d->clk_core))
    {
        err = rt_ptr_err(v2d->clk_core);
        goto _fail;
    }
    v2d->clk_io = rt_clk_get_by_name(dev, "v2d-io");
    if (rt_is_err(v2d->clk_io))
    {
        err = rt_ptr_err(v2d->clk_io);
        goto _fail;
    }
    if ((err = v2d_clocks_enable(v2d)) != RT_EOK)
    {
        goto _fail;
    }
    if ((err = rt_clk_set_rate(v2d->clk_core, V2D_CORE_RATE)) != RT_EOK)
    {
        goto _fail;
    }

    v2d->reset = rt_reset_control_get_by_name(dev, "v2d_reset");
    if (rt_is_err(v2d->reset))
    {
        err = rt_ptr_err(v2d->reset);
        goto _fail;
    }
    if ((err = rt_reset_control_deassert(v2d->reset)) != RT_EOK)
    {
        goto _fail;
    }
    v2d->reset_deasserted = RT_TRUE;
    if ((err = v2d_global_reset()) != RT_EOK)
    {
        goto _fail;
    }

    v2d->irq = rt_dm_dev_get_irq(dev, 0);
    if (v2d->irq < 0)
    {
        err = v2d->irq;
        goto _fail;
    }

    if ((err = rt_dm_dev_set_name_auto(&v2d->parent, "v2d")) < 0)
    {
        goto _fail;
    }
    dev_name = rt_dm_dev_get_name(&v2d->parent);
    v2d->parent.type = RT_Device_Class_Char;
#ifdef RT_USING_DEVICE_OPS
    v2d->parent.ops = &spacemit_v2d_ops;
#else
    v2d->parent.control = spacemit_v2d_control;
#endif
    dev->user_data = v2d;

    if ((err = rt_mutex_init(&v2d->lock, dev_name,
            RT_IPC_FLAG_PRIO)) != RT_EOK)
    {
        goto _fail;
    }
    v2d->lock_initialized = RT_TRUE;
    rt_completion_init(&v2d->completion);

    if ((err = rt_device_register(&v2d->parent, dev_name,
            RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STANDALONE)) != RT_EOK)
    {
        goto _fail;
    }
    v2d->device_registered = RT_TRUE;

    v2d_irq_disable();

    rt_hw_interrupt_install(v2d->irq, spacemit_v2d_isr, v2d, "v2d");
    rt_hw_interrupt_umask(v2d->irq);

    return RT_EOK;

_fail:
    spacemit_v2d_free(v2d);
    return err;
}

static rt_err_t spacemit_v2d_remove(struct rt_platform_device *pdev)
{
    struct spacemit_v2d *v2d = pdev->parent.user_data;

    rt_hw_interrupt_mask(v2d->irq);
    rt_pic_detach_irq(v2d->irq, v2d);
    spacemit_v2d_free(v2d);

    return RT_EOK;
}

static const struct rt_ofw_node_id spacemit_v2d_ofw_ids[] =
{
    { .compatible = "spacemit,v2d" },
    { /* sentinel */ }
};

static struct rt_platform_driver spacemit_v2d_driver =
{
    .name = "spacemit-v2d",
    .ids = spacemit_v2d_ofw_ids,
    .probe = spacemit_v2d_probe,
    .remove = spacemit_v2d_remove,
};
RT_PLATFORM_DRIVER_EXPORT(spacemit_v2d_driver);
