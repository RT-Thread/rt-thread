/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-21     GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "soc.rockchip.rga2"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include "rga2_internal.h"
#include "rga2_reg.h"

#define RGA2_TIMEOUT_MS                500
#define RGA2_MAX_WIDTH                 8192
#define RGA2_MAX_HEIGHT                8192
#define RGA2_MAX_OUTPUT                4096

struct rockchip_rga2_buffer
{
    rt_list_t list;
    struct rga2_buffer buffer;
};

struct rockchip_rga2
{
    struct rt_device parent;
    struct rt_device *dev;
    void *regs;
    int irq;
    struct rt_clk_array *clocks;

    struct rt_mutex lock;
    struct rt_completion completion;
    rt_list_t buffers;
    rt_uint32_t version;
    rt_uint32_t irq_status;
    rt_err_t error;
    rt_bool_t clocks_enabled;
    rt_bool_t lock_initialized;
    rt_bool_t device_registered;
};

#define raw_to_rockchip_rga2(raw) \
    rt_container_of(raw, struct rockchip_rga2, parent)

static rt_uint32_t rga2_read(struct rockchip_rga2 *rga2, rt_uint32_t offset)
{
    return HWREG32(rga2->regs + offset);
}

static void rga2_write(struct rockchip_rga2 *rga2, rt_uint32_t offset,
        rt_uint32_t value)
{
    HWREG32(rga2->regs + offset) = value;
}

static void rockchip_rga2_reset(struct rockchip_rga2 *rga2)
{
    int timeout = 1000;

    rga2_write(rga2, RGA2_INT, RGA2_INT_CLEAR_MASK);
    rga2_write(rga2, RGA2_SYS_CTRL,
            RGA2_SYS_SOFT_RESET | RGA2_SYS_RESET_PROTECT);
    while ((rga2_read(rga2, RGA2_SYS_CTRL) & RGA2_SYS_START) && timeout--)
    {
        rt_hw_us_delay(1);
    }
    if (timeout < 0)
    {
        LOG_E("soft reset timeout");
    }
}

static int rga2_format_bpp(rt_uint16_t format)
{
    switch (format)
    {
    case RGA2_FORMAT_RGBA8888:
    case RGA2_FORMAT_BGRA8888:
    case RGA2_FORMAT_RGBX8888:
    case RGA2_FORMAT_BGRX8888:
        return 4;
    case RGA2_FORMAT_RGB888:
    case RGA2_FORMAT_BGR888:
        return 3;
    case RGA2_FORMAT_RGB565:
    case RGA2_FORMAT_BGR565:
        return 2;
    default:
        return 0;
    }
}

static rt_bool_t rga2_range_allocated(struct rockchip_rga2 *rga2,
        rt_uint64_t address, rt_uint64_t size)
{
    struct rockchip_rga2_buffer *entry;

    if (!address || !size || address > UINT32_MAX ||
        size - 1 > UINT32_MAX - address)
    {
        return RT_FALSE;
    }

    rt_list_for_each_entry(entry, &rga2->buffers, list)
    {
        rt_uint64_t start = entry->buffer.phys_addr;

        if (address >= start && address + size <= start + entry->buffer.size)
        {
            return RT_TRUE;
        }
    }

    return RT_FALSE;
}

static rt_err_t rga2_validate_image(struct rockchip_rga2 *rga2,
        const struct rga2_image *image)
{
    const struct rga2_rect *rect = &image->rect;
    rt_uint64_t size;
    int bpp = rga2_format_bpp(image->format);

    if (!bpp || !image->width || !image->height ||
        image->width > RGA2_MAX_WIDTH || image->height > RGA2_MAX_HEIGHT ||
        image->stride < image->width * bpp || (image->stride & 3) ||
        !rect->width || !rect->height || rect->x >= image->width ||
        rect->y >= image->height || rect->width > image->width - rect->x ||
        rect->height > image->height - rect->y)
    {
        return -RT_EINVAL;
    }

    size = (rt_uint64_t)(image->height - 1) * image->stride +
            (rt_uint64_t)image->width * bpp;
    return rga2_range_allocated(rga2, image->address, size) ?
            RT_EOK : -RT_EINVAL;
}

static rt_err_t rga2_validate_request(struct rockchip_rga2 *rga2,
        const struct rga2_req *req)
{
    rt_err_t err;

    if (!req || req->rotate > RGA2_ROTATE_270 || req->mirror > 3 ||
        (req->render_mode != RGA2_MODE_BITBLT &&
         req->render_mode != RGA2_MODE_COLOR_FILL))
    {
        return -RT_EINVAL;
    }

    if ((err = rga2_validate_image(rga2, &req->dst)) != RT_EOK)
    {
        return err;
    }
    if (req->dst.rect.width > RGA2_MAX_OUTPUT ||
        req->dst.rect.height > RGA2_MAX_OUTPUT)
    {
        return -RT_EINVAL;
    }
    if (req->render_mode == RGA2_MODE_COLOR_FILL)
    {
        return RT_EOK;
    }
    if ((err = rga2_validate_image(rga2, &req->src)) != RT_EOK)
    {
        return err;
    }

    if (req->src.rect.width >
            ((req->rotate & 1) ? req->dst.rect.height : req->dst.rect.width) * 16U ||
        ((req->rotate & 1) ? req->dst.rect.height : req->dst.rect.width) >
            req->src.rect.width * 16U ||
        req->src.rect.height >
            ((req->rotate & 1) ? req->dst.rect.width : req->dst.rect.height) * 16U ||
        ((req->rotate & 1) ? req->dst.rect.width : req->dst.rect.height) >
            req->src.rect.height * 16U)
    {
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t rga2_alloc_buffer(struct rockchip_rga2 *rga2,
        struct rga2_buffer *buffer)
{
    struct rockchip_rga2_buffer *entry;
    rt_ubase_t physical;

    if (!buffer || !buffer->size || buffer->size > RGA2_BUFFER_MAX_SIZE)
    {
        return -RT_EINVAL;
    }
    entry = rt_calloc(1, sizeof(*entry));
    if (!entry)
    {
        return -RT_ENOMEM;
    }

    buffer->virt_addr = rt_dma_alloc_coherent(rga2->dev, buffer->size,
            &physical);
    if (!buffer->virt_addr)
    {
        rt_free(entry);
        return -RT_ENOMEM;
    }
    if (physical > UINT32_MAX)
    {
        rt_dma_free_coherent(rga2->dev, buffer->size, buffer->virt_addr,
                physical);
        buffer->virt_addr = RT_NULL;
        rt_free(entry);
        return -RT_EINVAL;
    }

    buffer->phys_addr = physical;
    entry->buffer = *buffer;
    rt_list_insert_before(&rga2->buffers, &entry->list);
    return RT_EOK;
}

static rt_err_t rga2_free_buffer(struct rockchip_rga2 *rga2,
        struct rga2_buffer *buffer)
{
    struct rockchip_rga2_buffer *entry;

    if (!buffer)
    {
        return -RT_EINVAL;
    }
    rt_list_for_each_entry(entry, &rga2->buffers, list)
    {
        if (entry->buffer.virt_addr == buffer->virt_addr &&
            entry->buffer.phys_addr == buffer->phys_addr &&
            entry->buffer.size == buffer->size)
        {
            rt_list_remove(&entry->list);
            rt_dma_free_coherent(rga2->dev, entry->buffer.size,
                    entry->buffer.virt_addr, entry->buffer.phys_addr);
            rt_free(entry);
            rt_memset(buffer, 0, sizeof(*buffer));
            return RT_EOK;
        }
    }
    return -RT_EINVAL;
}

static rt_err_t rga2_submit(struct rockchip_rga2 *rga2,
        struct rga2_req *req)
{
    rt_uint32_t command[RGA2_COMMAND_WORDS];
    rt_err_t err;
    int i;

    if ((err = rga2_validate_request(rga2, req)) != RT_EOK ||
        (err = rockchip_rga2_build_command(req, command)) != RT_EOK)
    {
        return err;
    }

    rockchip_rga2_reset(rga2);
    rga2->irq_status = 0;
    rga2->error = RT_EOK;
    rt_completion_init(&rga2->completion);

    for (i = 0; i < RGA2_COMMAND_WORDS; ++i)
    {
        rga2_write(rga2, RGA2_CMD_REG_BASE + i * 4, command[i]);
    }
    rga2_write(rga2, RGA2_INT, RGA2_INT_ENABLE_MASK | RGA2_INT_CLEAR_MASK);
    rt_hw_dsb();
    rga2_write(rga2, RGA2_SYS_CTRL, RGA2_SYS_AUTO_RESET |
            RGA2_SYS_AUTO_CLOCK | RGA2_SYS_START);

    if (rt_completion_wait(&rga2->completion,
            rt_tick_from_millisecond(RGA2_TIMEOUT_MS)) != RT_EOK)
    {
        LOG_E("job timeout, status1=%08x status2=%08x",
                rga2_read(rga2, RGA2_STATUS1),
                rga2_read(rga2, RGA2_STATUS2));
        rockchip_rga2_reset(rga2);
        return -RT_ETIMEOUT;
    }

    req->irq_status = rga2->irq_status;
    return rga2->error;
}

static rt_err_t rockchip_rga2_control(rt_device_t dev, int cmd, void *args)
{
    struct rockchip_rga2 *rga2 = raw_to_rockchip_rga2(dev);
    rt_err_t err;

    rt_mutex_take(&rga2->lock, RT_WAITING_FOREVER);
    switch (cmd)
    {
    case RGA2_SUBMIT:
        err = rga2_submit(rga2, args);
        break;
    case RGA2_ALLOC_BUFFER:
        err = rga2_alloc_buffer(rga2, args);
        break;
    case RGA2_FREE_BUFFER:
        err = rga2_free_buffer(rga2, args);
        break;
    case RGA2_GET_VERSION:
        if (!args)
        {
            err = -RT_EINVAL;
        }
        else
        {
            *(rt_uint32_t *)args = rga2->version;
            err = RT_EOK;
        }
        break;
    case RGA2_RESET:
        rockchip_rga2_reset(rga2);
        err = RT_EOK;
        break;
    default:
        err = -RT_ENOSYS;
        break;
    }
    rt_mutex_release(&rga2->lock);
    return err;
}

#ifdef RT_USING_DEVICE_OPS
static const struct rt_device_ops rockchip_rga2_ops =
{
    .control = rockchip_rga2_control,
};
#endif

static void rockchip_rga2_isr(int irqno, void *param)
{
    struct rockchip_rga2 *rga2 = param;
    rt_uint32_t status = rga2_read(rga2, RGA2_INT);

    RT_UNUSED(irqno);
    if (!(status & (RGA2_INT_ALL_DONE | RGA2_INT_ERROR_MASK)))
    {
        return;
    }

    rga2->irq_status |= status;
    if (status & RGA2_INT_ERROR_MASK)
    {
        rga2->error = -RT_EIO;
    }
    rga2_write(rga2, RGA2_INT, RGA2_INT_ENABLE_MASK | RGA2_INT_CLEAR_MASK);
    rt_completion_done(&rga2->completion);
}

static void rockchip_rga2_free(struct rockchip_rga2 *rga2)
{
    struct rockchip_rga2_buffer *entry, *next;

    rt_list_for_each_entry_safe(entry, next, &rga2->buffers, list)
    {
        rt_list_remove(&entry->list);
        rt_dma_free_coherent(rga2->dev, entry->buffer.size,
                entry->buffer.virt_addr, entry->buffer.phys_addr);
        rt_free(entry);
    }
    if (rga2->device_registered)
    {
        rt_device_unregister(&rga2->parent);
    }
    if (rga2->lock_initialized)
    {
        rt_mutex_detach(&rga2->lock);
    }
    if (rga2->clocks_enabled)
    {
        rt_clk_array_disable_unprepare(rga2->clocks);
    }
    if (!rt_is_err_or_null(rga2->clocks))
    {
        rt_clk_array_put(rga2->clocks);
    }
    if (rga2->regs)
    {
        rt_iounmap(rga2->regs);
    }
    rt_free(rga2);
}

static rt_err_t rockchip_rga2_probe(struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;
    struct rockchip_rga2 *rga2;
    const char *name;
    rt_err_t err;

    rga2 = rt_calloc(1, sizeof(*rga2));
    if (!rga2)
    {
        return -RT_ENOMEM;
    }
    rga2->dev = dev;
    rt_list_init(&rga2->buffers);

    rga2->regs = rt_dm_dev_iomap(dev, 0);
    if (!rga2->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }
    rga2->clocks = rt_clk_get_array(dev);
    if (rt_is_err(rga2->clocks))
    {
        err = rt_ptr_err(rga2->clocks);
        goto _fail;
    }
    if ((err = rt_clk_array_prepare_enable(rga2->clocks)) != RT_EOK)
    {
        goto _fail;
    }
    rga2->clocks_enabled = RT_TRUE;
    rga2->irq = rt_dm_dev_get_irq(dev, 0);
    if (rga2->irq < 0)
    {
        err = rga2->irq;
        goto _fail;
    }

    rga2->version = rga2_read(rga2, RGA2_VERSION_NUM);
    rockchip_rga2_reset(rga2);
    rt_dm_dev_set_name_auto(&rga2->parent, RGA2_NAME);
    name = rt_dm_dev_get_name(&rga2->parent);
    rga2->parent.type = RT_Device_Class_Char;
#ifdef RT_USING_DEVICE_OPS
    rga2->parent.ops = &rockchip_rga2_ops;
#else
    rga2->parent.control = rockchip_rga2_control;
#endif
    dev->user_data = rga2;

    if ((err = rt_mutex_init(&rga2->lock, name, RT_IPC_FLAG_PRIO)) != RT_EOK)
    {
        goto _fail;
    }
    rga2->lock_initialized = RT_TRUE;
    rt_completion_init(&rga2->completion);
    if ((err = rt_device_register(&rga2->parent, name,
            RT_DEVICE_FLAG_RDWR | RT_DEVICE_FLAG_STANDALONE)) != RT_EOK)
    {
        goto _fail;
    }
    rga2->device_registered = RT_TRUE;

    rt_hw_interrupt_install(rga2->irq, rockchip_rga2_isr, rga2, name);
    rt_hw_interrupt_umask(rga2->irq);
    LOG_I("RGA2 registered as %s, version %08x", name, rga2->version);
    return RT_EOK;

_fail:
    rockchip_rga2_free(rga2);
    return err;
}

static rt_err_t rockchip_rga2_remove(struct rt_platform_device *pdev)
{
    struct rockchip_rga2 *rga2 = pdev->parent.user_data;

    rt_hw_interrupt_mask(rga2->irq);
    rt_pic_detach_irq(rga2->irq, rga2);
    rockchip_rga2_free(rga2);
    return RT_EOK;
}

static const struct rt_ofw_node_id rockchip_rga2_ofw_ids[] =
{
    { .compatible = "rockchip,rga2" },
    { /* sentinel */ }
};

static struct rt_platform_driver rockchip_rga2_driver =
{
    .name = "rockchip-rga2",
    .ids = rockchip_rga2_ofw_ids,
    .probe = rockchip_rga2_probe,
    .remove = rockchip_rga2_remove,
};
RT_PLATFORM_DRIVER_EXPORT(rockchip_rga2_driver);
