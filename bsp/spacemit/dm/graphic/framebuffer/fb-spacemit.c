/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#include <cpuport.h>
#include <ioremap.h>
#include "display-spacemit.h"

#define DBG_TAG "fb.spacemit"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define SPACEMIT_DPU_HDMI                   0U
#define SPACEMIT_DPU_DSI                    1U

#define SPACEMIT_DPU_MAX_DIMENSION          8192U
#define SPACEMIT_DPU_HDMI_MCLK_RATE         491520000UL

/* Saturn RDMA3, composer2 and online2 registers used by U-Boot/Linux. */
#define SPACEMIT_DPU_CTL2_NORMAL            0x0560
#define SPACEMIT_DPU_CTL2_CFG_READY         0x056c
#define SPACEMIT_DPU_CTL2_TIMING            0x0588
#define SPACEMIT_DPU_CTL2_SW_START          0x058c

#define SPACEMIT_DPU_INT_ONLINE2_MASK       0x0910
#define SPACEMIT_DPU_INT_ONLINE2_STATUS     0x0938
#define SPACEMIT_DPU_INT_ONLINE2_RAW        0x0960
#define SPACEMIT_DPU_INT_VSYNC              RT_BIT(0)

#define SPACEMIT_DPU_RDMA3_LAYER_CTRL       0x0d80
#define SPACEMIT_DPU_RDMA3_ADDR_LOW         0x0da0
#define SPACEMIT_DPU_RDMA3_ADDR_HIGH        0x0da4
#define SPACEMIT_DPU_RDMA3_STRIDE           0x0db8
#define SPACEMIT_DPU_RDMA3_IMAGE_SIZE       0x0dbc
#define SPACEMIT_DPU_RDMA3_CROP_START       0x0dc0
#define SPACEMIT_DPU_RDMA3_CROP_END         0x0dc4
#define SPACEMIT_DPU_RDMA3_ROT_FORMAT       0x0df0

#define SPACEMIT_DPU_CMPS2_LAYER0           0x4c00
#define SPACEMIT_DPU_CMPS2_HEIGHT           0x4c04
#define SPACEMIT_DPU_CMPS2_SOLID_R          0x4c10
#define SPACEMIT_DPU_CMPS2_SOLID_A          0x4c14
#define SPACEMIT_DPU_CMPS2_BLEND            0x4c38
#define SPACEMIT_DPU_CMPS2_POSITION         0x4c48
#define SPACEMIT_DPU_CMPS2_RIGHT            0x4c4c
#define SPACEMIT_DPU_CMPS2_BOTTOM           0x4c50
#define SPACEMIT_DPU_CMPS2_SOLID_COLOR      0x4c54

#define SPACEMIT_DPU_OUT2_SIZE              0x18000
#define SPACEMIT_DPU_OUT2_CTRL4             0x18018
#define SPACEMIT_DPU_OUT2_CTRL31            0x1807c
#define SPACEMIT_DPU_OUT2_HPORCH            0x18080
#define SPACEMIT_DPU_OUT2_VPORCH            0x18084
#define SPACEMIT_DPU_OUT2_SYNC              0x18088
#define SPACEMIT_DPU_OUT2_ACTIVE_SIZE       0x1808c
#define SPACEMIT_DPU_OUT2_FORMAT            0x18090

#define SPACEMIT_DPU_TOP_MISC               0x0a1c

#define SPACEMIT_DPU_RDMA3_CTRL_VALUE       0x00202040U
#define SPACEMIT_DPU_CTL2_NORMAL_VALUE      0x00040008U
#define SPACEMIT_DPU_CTL2_TIMING_VALUE      0x00000821U
#define SPACEMIT_DPU_OUT_FORMAT_RGB888      2U

enum spacemit_dpu_rdma_format
{
    SPACEMIT_RDMA_FORMAT_ARGB8888 = 4,
    SPACEMIT_RDMA_FORMAT_ABGR8888 = 5,
    SPACEMIT_RDMA_FORMAT_RGB565 = 22,
    SPACEMIT_RDMA_FORMAT_BGR565 = 23,
};

struct spacemit_fb_plane
{
    rt_ubase_t dma_handle;
    rt_ubase_t dma_flags;
    rt_size_t pan_offset;
    rt_bool_t enabled;
    rt_bool_t reserved;
};

struct spacemit_fb
{
    struct rt_graphic_device parent;
    struct rt_device *dev;

    void *regs;
    struct rt_clk_array *clks;
    struct rt_reset_control *rstc;
    struct spacemit_display_connector *connector;
    struct spacemit_display_timing timing;
    rt_bool_t clocks_enabled;
    rt_bool_t connector_enabled;
    rt_bool_t dpu_configured;
    rt_bool_t powered;
    rt_bool_t irq_attached;
    rt_bool_t vsync_sem_initialized;

    rt_uint32_t output_type;
    rt_uint32_t width;
    rt_uint32_t height;
    rt_uint32_t refresh;
    rt_ubase_t reserved_fb_dma;
    rt_size_t reserved_fb_size;
    int irq;
    struct rt_semaphore vsync_sem;
    rt_atomic_t vsync_waiting;
    struct rt_graphic_plane *primary;
};

static const rt_uint32_t spacemit_fb_modes[] =
{
    RTGRAPHIC_PIXEL_FORMAT_ARGB888,
    RTGRAPHIC_PIXEL_FORMAT_ABGR888,
    RTGRAPHIC_PIXEL_FORMAT_RGB565,
    RTGRAPHIC_PIXEL_FORMAT_BGR565,
};

rt_inline rt_uint32_t spacemit_fb_readl(struct spacemit_fb *sfb,
        rt_uint32_t offset)
{
    return HWREG32((rt_uint8_t *)sfb->regs + offset);
}

rt_inline void spacemit_fb_writel(struct spacemit_fb *sfb,
        rt_uint32_t offset, rt_uint32_t value)
{
    HWREG32((rt_uint8_t *)sfb->regs + offset) = value;
}

static void spacemit_fb_isr(int irqno, void *param)
{
    struct spacemit_fb *sfb = param;
    rt_uint32_t status = spacemit_fb_readl(sfb,
            SPACEMIT_DPU_INT_ONLINE2_RAW);

    RT_UNUSED(irqno);

    if (status & SPACEMIT_DPU_INT_VSYNC)
    {
        spacemit_fb_writel(sfb, SPACEMIT_DPU_INT_ONLINE2_STATUS,
                SPACEMIT_DPU_INT_VSYNC);

        if (rt_atomic_load(&sfb->vsync_waiting))
        {
            rt_sem_release(&sfb->vsync_sem);
        }
    }
}

static void spacemit_fb_vsync_irq_enable(struct spacemit_fb *sfb,
        rt_bool_t enable)
{
    rt_uint32_t mask;

    if (!sfb->irq_attached)
    {
        return;
    }

    mask = spacemit_fb_readl(sfb, SPACEMIT_DPU_INT_ONLINE2_MASK);
    if (enable)
    {
        spacemit_fb_writel(sfb, SPACEMIT_DPU_INT_ONLINE2_STATUS,
                SPACEMIT_DPU_INT_VSYNC);
        mask |= SPACEMIT_DPU_INT_VSYNC;
    }
    else
    {
        mask &= ~SPACEMIT_DPU_INT_VSYNC;
    }
    spacemit_fb_writel(sfb, SPACEMIT_DPU_INT_ONLINE2_MASK, mask);
}

static rt_err_t spacemit_fb_irq_setup(struct spacemit_fb *sfb)
{
    rt_err_t err;

    sfb->irq = rt_dm_dev_get_irq_by_name(sfb->dev, "ONLINE_IRQ");
    if (sfb->irq < 0)
    {
        sfb->irq = rt_dm_dev_get_irq(sfb->dev, 0);
    }
    if (sfb->irq < 0)
    {
        return sfb->irq;
    }

    if ((err = rt_sem_init(&sfb->vsync_sem, "dpu-vsync", 0,
            RT_IPC_FLAG_FIFO)))
    {
        return err;
    }
    sfb->vsync_sem_initialized = RT_TRUE;
    rt_atomic_store(&sfb->vsync_waiting, RT_FALSE);

    rt_hw_interrupt_install(sfb->irq, spacemit_fb_isr, sfb, "dpu-online2");
    sfb->irq_attached = RT_TRUE;

    spacemit_fb_vsync_irq_enable(sfb, RT_TRUE);
    rt_hw_interrupt_umask(sfb->irq);

    return RT_EOK;
}

static void spacemit_fb_irq_cleanup(struct spacemit_fb *sfb)
{
    if (sfb->irq_attached)
    {
        spacemit_fb_vsync_irq_enable(sfb, RT_FALSE);
        spacemit_fb_writel(sfb, SPACEMIT_DPU_INT_ONLINE2_STATUS,
                SPACEMIT_DPU_INT_VSYNC);
        rt_hw_interrupt_mask(sfb->irq);
        rt_pic_detach_irq(sfb->irq, sfb);
        sfb->irq_attached = RT_FALSE;
    }
    if (sfb->vsync_sem_initialized)
    {
        rt_sem_detach(&sfb->vsync_sem);
        sfb->vsync_sem_initialized = RT_FALSE;
    }
}

static struct spacemit_fb *spacemit_fb_from_plane(struct rt_graphic_plane *plane)
{
    return rt_container_of(plane->graphic, struct spacemit_fb, parent);
}

static struct spacemit_fb_plane *spacemit_fb_plane_priv(
        struct rt_graphic_plane *plane)
{
    return (struct spacemit_fb_plane *)plane->priv;
}

static rt_uint32_t spacemit_fb_mode_to_hw(rt_uint32_t mode)
{
    switch (mode)
    {
    case RTGRAPHIC_PIXEL_FORMAT_ARGB888:
        return SPACEMIT_RDMA_FORMAT_ARGB8888;
    case RTGRAPHIC_PIXEL_FORMAT_ABGR888:
        return SPACEMIT_RDMA_FORMAT_ABGR8888;
    case RTGRAPHIC_PIXEL_FORMAT_RGB565:
        return SPACEMIT_RDMA_FORMAT_RGB565;
    case RTGRAPHIC_PIXEL_FORMAT_BGR565:
        return SPACEMIT_RDMA_FORMAT_BGR565;
    default:
        return RT_UINT32_MAX;
    }
}

static struct rt_ofw_node *spacemit_fb_find_display_node(
        struct rt_ofw_node *port_np, rt_uint32_t output_type)
{
    const char *compatible;
    struct rt_ofw_node *display_np;

    compatible = output_type == SPACEMIT_DPU_HDMI ?
            "spacemit,saturn-hdmi" : "spacemit,saturn-le";

    rt_ofw_foreach_node_by_compatible(display_np, compatible)
    {
        struct rt_ofw_node *ports_np =
                rt_ofw_parse_phandle(display_np, "ports", 0);
        rt_bool_t matched = ports_np == port_np;

        if (ports_np)
        {
            rt_ofw_node_put(ports_np);
        }
        if (matched)
        {
            return display_np;
        }
    }

    return RT_NULL;
}

static void spacemit_fb_find_reserved_buffer(struct spacemit_fb *sfb)
{
    rt_uint64_t addr, size;
    struct rt_ofw_node *rmem_np, *fb_np;

    rmem_np = rt_ofw_find_node_by_path("/reserved-memory");
    if (!rmem_np)
    {
        return;
    }

    rt_ofw_foreach_child_node(rmem_np, fb_np)
    {
        if (!rt_ofw_node_tag_equ(fb_np, "framebuffer") ||
            rt_ofw_get_address(fb_np, 0, &addr, &size) || !size ||
            addr > (rt_uint64_t)(rt_ubase_t)-1 ||
            size > (rt_uint64_t)(rt_size_t)-1)
        {
            continue;
        }

        sfb->reserved_fb_dma = (rt_ubase_t)addr;
        sfb->reserved_fb_size = (rt_size_t)size;
        rt_ofw_node_put(fb_np);
        break;
    }

    rt_ofw_node_put(rmem_np);
}

static rt_err_t spacemit_fb_clocks_enable(struct spacemit_fb *sfb)
{
    rt_err_t err;

    if (sfb->clocks_enabled)
    {
        return RT_EOK;
    }
    if ((err = rt_clk_array_prepare_enable(sfb->clks)))
    {
        return err;
    }

    if (sfb->output_type == SPACEMIT_DPU_HDMI && sfb->clks->count)
    {
        struct rt_clk *clk = sfb->clks->clks[0];

        if (!rt_is_err_or_null(clk) &&
            (err = rt_clk_set_rate(clk, SPACEMIT_DPU_HDMI_MCLK_RATE)))
        {
            rt_clk_array_disable_unprepare(sfb->clks);
            return err;
        }
    }

    sfb->clocks_enabled = RT_TRUE;
    return RT_EOK;
}

static void spacemit_fb_clocks_disable(struct spacemit_fb *sfb)
{
    if (sfb->clocks_enabled)
    {
        rt_clk_array_disable_unprepare(sfb->clks);
        sfb->clocks_enabled = RT_FALSE;
    }
}

static void spacemit_fb_trigger(struct spacemit_fb *sfb)
{
    spacemit_fb_writel(sfb, SPACEMIT_DPU_CTL2_CFG_READY, 1);
    if (!sfb->dpu_configured)
    {
        spacemit_fb_writel(sfb, SPACEMIT_DPU_CTL2_SW_START, 1);
    }
    rt_hw_dsb();
}

static void spacemit_fb_output_mode_set(struct spacemit_fb *sfb)
{
    const struct spacemit_display_timing *timing = &sfb->timing;
    rt_uint32_t hsp = !!(timing->flags & SPACEMIT_DISPLAY_F_PHSYNC);
    rt_uint32_t vsp = !!(timing->flags & SPACEMIT_DISPLAY_F_PVSYNC);
    rt_uint32_t size = (timing->vactive << 16) | timing->hactive;

    spacemit_fb_writel(sfb, SPACEMIT_DPU_TOP_MISC, 0x2223);
    spacemit_fb_writel(sfb, SPACEMIT_DPU_OUT2_SIZE, size);
    spacemit_fb_writel(sfb, SPACEMIT_DPU_OUT2_CTRL4, 0x20);
    spacemit_fb_writel(sfb, SPACEMIT_DPU_OUT2_CTRL31, 0x100);
    spacemit_fb_writel(sfb, SPACEMIT_DPU_OUT2_HPORCH,
            (timing->hback_porch << 16) | timing->hfront_porch);
    spacemit_fb_writel(sfb, SPACEMIT_DPU_OUT2_VPORCH,
            (timing->vback_porch << 16) | timing->vfront_porch);
    spacemit_fb_writel(sfb, SPACEMIT_DPU_OUT2_SYNC,
            (vsp << 28) | (timing->vsync_len << 16) |
            (hsp << 12) | timing->hsync_len);
    spacemit_fb_writel(sfb, SPACEMIT_DPU_OUT2_ACTIVE_SIZE, size);
    spacemit_fb_writel(sfb, SPACEMIT_DPU_OUT2_FORMAT,
            SPACEMIT_DPU_OUT_FORMAT_RGB888);
}

static void spacemit_fb_composer_enable(struct spacemit_fb *sfb,
        rt_uint32_t width, rt_uint32_t height, rt_bool_t enable)
{
    if (!enable)
    {
        rt_uint32_t value = spacemit_fb_readl(sfb,
                SPACEMIT_DPU_CMPS2_LAYER0);

        spacemit_fb_writel(sfb, SPACEMIT_DPU_CMPS2_LAYER0,
                value & ~RT_BIT(0));
        spacemit_fb_trigger(sfb);
        return;
    }

    spacemit_fb_writel(sfb, SPACEMIT_DPU_CMPS2_LAYER0,
            (width << 8) | 1U);
    spacemit_fb_writel(sfb, SPACEMIT_DPU_CMPS2_HEIGHT, height);
    spacemit_fb_writel(sfb, SPACEMIT_DPU_CMPS2_SOLID_R, 0xff0000);
    spacemit_fb_writel(sfb, SPACEMIT_DPU_CMPS2_SOLID_A, 0xff);
    spacemit_fb_writel(sfb, SPACEMIT_DPU_CMPS2_BLEND, 0x7);
    spacemit_fb_writel(sfb, SPACEMIT_DPU_CMPS2_POSITION, 0);
    spacemit_fb_writel(sfb, SPACEMIT_DPU_CMPS2_RIGHT,
            (width - 1U) << 16);
    spacemit_fb_writel(sfb, SPACEMIT_DPU_CMPS2_BOTTOM, height - 1U);
    spacemit_fb_writel(sfb, SPACEMIT_DPU_CMPS2_SOLID_COLOR, 0xff0000);
}

static rt_err_t spacemit_fb_plane_commit(struct rt_graphic_plane *plane,
        rt_bool_t enable)
{
    struct spacemit_fb *sfb = spacemit_fb_from_plane(plane);
    struct spacemit_fb_plane *priv = spacemit_fb_plane_priv(plane);
    rt_uint32_t hw_format;
    rt_ubase_t dma;

    if (!priv)
    {
        return -RT_EINVAL;
    }
    if (!enable || !plane->framebuffer)
    {
        if (sfb->powered)
        {
            spacemit_fb_composer_enable(sfb, plane->width, plane->height,
                    RT_FALSE);
        }
        priv->enabled = RT_FALSE;
        return RT_EOK;
    }
    if (!sfb->powered)
    {
        priv->enabled = RT_TRUE;
        return RT_EOK;
    }

    hw_format = spacemit_fb_mode_to_hw(plane->mode);
    if (hw_format == RT_UINT32_MAX || !plane->width || !plane->height ||
        plane->line_length > 0xffffU)
    {
        return -RT_EINVAL;
    }

    if (!sfb->dpu_configured)
    {
        LOG_D("initial framebuffer cache flush begin: %u bytes",
                (unsigned)plane->screen_len);
    }
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH,
            (rt_uint8_t *)plane->framebuffer + priv->pan_offset,
            plane->screen_len);
    if (!sfb->dpu_configured)
    {
        LOG_D("initial framebuffer cache flush done");
    }
    dma = priv->dma_handle + priv->pan_offset;

    if (!sfb->dpu_configured)
    {
        LOG_D("DPU init: fb=%p stride=%u format=%u",
                dma, plane->line_length, hw_format);
    }

    spacemit_fb_output_mode_set(sfb);
    spacemit_fb_writel(sfb, SPACEMIT_DPU_RDMA3_LAYER_CTRL,
            SPACEMIT_DPU_RDMA3_CTRL_VALUE);
    spacemit_fb_writel(sfb, SPACEMIT_DPU_RDMA3_ADDR_LOW,
            (rt_uint32_t)dma);
    spacemit_fb_writel(sfb, SPACEMIT_DPU_RDMA3_ADDR_HIGH,
            (rt_uint32_t)(dma >> 32));
    spacemit_fb_writel(sfb, SPACEMIT_DPU_RDMA3_STRIDE,
            plane->line_length);
    spacemit_fb_writel(sfb, SPACEMIT_DPU_RDMA3_IMAGE_SIZE,
            (plane->height << 16) | plane->width);
    spacemit_fb_writel(sfb, SPACEMIT_DPU_RDMA3_CROP_START, 0);
    spacemit_fb_writel(sfb, SPACEMIT_DPU_RDMA3_CROP_END,
            ((plane->height - 1U) << 16) | (plane->width - 1U));
    spacemit_fb_writel(sfb, SPACEMIT_DPU_RDMA3_ROT_FORMAT, hw_format);

    spacemit_fb_composer_enable(sfb, plane->width, plane->height, RT_TRUE);
    spacemit_fb_writel(sfb, SPACEMIT_DPU_CTL2_NORMAL,
            SPACEMIT_DPU_CTL2_NORMAL_VALUE);
    spacemit_fb_writel(sfb, SPACEMIT_DPU_CTL2_TIMING,
            SPACEMIT_DPU_CTL2_TIMING_VALUE);
    spacemit_fb_trigger(sfb);

    priv->enabled = RT_TRUE;
    if (!sfb->dpu_configured)
    {
        sfb->dpu_configured = RT_TRUE;
    }
    return RT_EOK;
}

static void spacemit_fb_plane_free(struct rt_graphic_plane *plane)
{
    struct spacemit_fb *sfb = spacemit_fb_from_plane(plane);
    struct spacemit_fb_plane *priv = spacemit_fb_plane_priv(plane);

    if (plane->framebuffer)
    {
        if (priv->reserved)
        {
            rt_iounmap(plane->framebuffer);
        }
        else
        {
            rt_dma_free(&sfb->parent.parent, plane->framebuffer_len,
                    plane->framebuffer, priv->dma_handle, priv->dma_flags);
        }
        plane->framebuffer = RT_NULL;
        plane->framebuffer_len = 0;
        plane->screen_len = 0;
        priv->dma_handle = 0;
        priv->dma_flags = 0;
        priv->pan_offset = 0;
        priv->reserved = RT_FALSE;
    }
}

static rt_err_t spacemit_fb_plane_flush(struct rt_graphic_plane *plane,
        struct rt_device_rect_info *rect)
{
    struct spacemit_fb_plane *priv = spacemit_fb_plane_priv(plane);
    rt_uint8_t *addr;
    rt_size_t row, row_len, bytes_per_pixel;

    if (!plane->framebuffer || !plane->bits_per_pixel)
    {
        return -RT_EINVAL;
    }

    if (!rect || !rect->width || !rect->height)
    {
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH,
                (rt_uint8_t *)plane->framebuffer + priv->pan_offset,
                plane->screen_len);
        return RT_EOK;
    }

    if (rect->x >= plane->width || rect->y >= plane->height ||
        rect->width > plane->width - rect->x ||
        rect->height > plane->height - rect->y)
    {
        return -RT_EINVAL;
    }

    bytes_per_pixel = plane->bits_per_pixel / 8U;
    row_len = rect->width * bytes_per_pixel;
    addr = (rt_uint8_t *)plane->framebuffer + priv->pan_offset +
            rect->y * plane->line_length + rect->x * bytes_per_pixel;

    if (!rect->x && rect->width == plane->width)
    {
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, addr,
                rect->height * plane->line_length);
        return RT_EOK;
    }

    for (row = 0; row < rect->height; ++row)
    {
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, addr, row_len);
        addr += plane->line_length;
    }

    return RT_EOK;
}

static rt_err_t spacemit_fb_plane_update(struct rt_graphic_plane *plane,
        struct rt_device_rect_info *rect)
{
    struct spacemit_fb_plane *priv = spacemit_fb_plane_priv(plane);

    if (priv->enabled)
    {
        return spacemit_fb_plane_flush(plane, rect);
    }

    return spacemit_fb_plane_commit(plane, RT_TRUE);
}

static rt_err_t spacemit_fb_plane_remap(struct rt_graphic_plane *plane,
        rt_uint32_t mode, struct rt_device_rect_info *rect)
{
    struct spacemit_fb *sfb = spacemit_fb_from_plane(plane);
    struct spacemit_fb_plane *priv = spacemit_fb_plane_priv(plane);
    rt_uint32_t bpp = rt_graphic_mode_bpp(mode);
    rt_size_t screen_len, fb_len;
    void *framebuffer;

    if (!rect || !rect->width || !rect->height ||
        spacemit_fb_mode_to_hw(mode) == RT_UINT32_MAX ||
        (bpp != 16U && bpp != 32U))
    {
        return -RT_EINVAL;
    }

    if (plane->framebuffer)
    {
        spacemit_fb_plane_commit(plane, RT_FALSE);
    }
    spacemit_fb_plane_free(plane);

    plane->line_length = RT_ALIGN(rect->width * (bpp / 8U), 16U);
    if (plane->line_length > 0xffffU ||
        rect->height > (rt_size_t)-1 / plane->line_length)
    {
        return -RT_EINVAL;
    }

    screen_len = plane->line_length * rect->height;
    if (screen_len > (rt_size_t)-1 / 2U)
    {
        return -RT_EINVAL;
    }
    fb_len = screen_len * 2U;
    priv->dma_flags = RT_DMA_F_LINEAR | RT_DMA_F_32BITS;

    framebuffer = RT_NULL;
    if (sfb->reserved_fb_size >= fb_len)
    {
        framebuffer = rt_ioremap_cached((void *)sfb->reserved_fb_dma, fb_len);
        if (framebuffer)
        {
            priv->dma_handle = sfb->reserved_fb_dma;
            priv->reserved = RT_TRUE;
            LOG_D("use reserved framebuffer: va=%p dma=%p len=%u",
                    framebuffer, priv->dma_handle, (unsigned)fb_len);
        }
        else
        {
            LOG_D("map reserved framebuffer failed, fallback to CMA");
        }
    }

    if (!framebuffer)
    {
        priv->dma_handle = 0;
        framebuffer = rt_dma_alloc(&plane->graphic->parent, fb_len,
                &priv->dma_handle, priv->dma_flags);
    }

    if (!framebuffer)
    {
        LOG_W("double buffer allocation failed, fallback to one buffer");
        fb_len = screen_len;

        if (sfb->reserved_fb_size >= fb_len)
        {
            framebuffer = rt_ioremap_cached((void *)sfb->reserved_fb_dma,
                    fb_len);
            if (framebuffer)
            {
                priv->dma_handle = sfb->reserved_fb_dma;
                priv->reserved = RT_TRUE;
            }
        }
        if (!framebuffer)
        {
            priv->dma_handle = 0;
            framebuffer = rt_dma_alloc(&plane->graphic->parent, fb_len,
                    &priv->dma_handle, priv->dma_flags);
        }
    }
    if (!framebuffer)
    {
        priv->dma_flags = 0;
        return -RT_ENOMEM;
    }

    rt_memset(framebuffer, 0, fb_len);

    plane->framebuffer = framebuffer;
    plane->framebuffer_len = fb_len;
    plane->screen_len = screen_len;
    plane->bits_per_pixel = bpp;
    plane->mode = mode;
    plane->width = rect->width;
    plane->height = rect->height;
    plane->x = 0;
    plane->y = 0;
    priv->pan_offset = 0;

    return spacemit_fb_plane_commit(plane, RT_TRUE);
}

static rt_err_t spacemit_fb_plane_pan_display(struct rt_graphic_plane *plane,
        struct rt_device_rect_info *rect)
{
    struct spacemit_fb_plane *priv = spacemit_fb_plane_priv(plane);
    rt_size_t offset;

    if (!rect)
    {
        return -RT_EINVAL;
    }
    if (rect->width != plane->width || rect->height != plane->height)
    {
        return spacemit_fb_plane_remap(plane, plane->mode, rect);
    }

    offset = rect->y * plane->line_length +
            rect->x * (plane->bits_per_pixel / 8U);
    if (offset + plane->screen_len > plane->framebuffer_len)
    {
        return -RT_EINVAL;
    }

    if (offset == priv->pan_offset && priv->enabled)
    {
        return RT_EOK;
    }

    priv->pan_offset = offset;
    plane->x = rect->x;
    plane->y = rect->y;

    return spacemit_fb_plane_commit(plane, RT_TRUE);
}

static rt_err_t spacemit_fb_plane_cleanup(struct rt_graphic_plane *plane)
{
    struct spacemit_fb_plane *priv = spacemit_fb_plane_priv(plane);

    if (priv->enabled)
    {
        spacemit_fb_plane_commit(plane, RT_FALSE);
    }
    spacemit_fb_plane_free(plane);

    return RT_EOK;
}

static const struct rt_graphic_plane_ops spacemit_fb_plane_ops =
{
    .update = spacemit_fb_plane_update,
    .fb_remap = spacemit_fb_plane_remap,
    .fb_pan_display = spacemit_fb_plane_pan_display,
    .fb_cleanup = spacemit_fb_plane_cleanup,
};

static rt_err_t spacemit_fb_dpms_switch(struct rt_graphic_device *gdev,
        rt_uint32_t dpms)
{
    rt_err_t err;
    struct spacemit_fb *sfb = rt_container_of(gdev, struct spacemit_fb, parent);

    switch (dpms)
    {
    case RT_GRAPHIC_DPMS_ON:
        if ((err = spacemit_fb_clocks_enable(sfb)))
        {
            return err;
        }

        if ((err = rt_reset_control_deassert(sfb->rstc)))
        {
            spacemit_fb_clocks_disable(sfb);
            return err;
        }
        rt_hw_us_delay(10);
        spacemit_fb_vsync_irq_enable(sfb, RT_TRUE);

        if (!sfb->connector_enabled)
        {
            err = sfb->connector->ops->enable(sfb->connector, &sfb->timing);
            if (err)
            {
                rt_reset_control_assert(sfb->rstc);
                spacemit_fb_clocks_disable(sfb);
                return err;
            }
            sfb->connector_enabled = RT_TRUE;
        }

        sfb->powered = RT_TRUE;
        if (sfb->primary && sfb->primary->framebuffer &&
            !spacemit_fb_plane_priv(sfb->primary)->enabled)
        {
            sfb->dpu_configured = RT_FALSE;
            if ((err = spacemit_fb_plane_commit(sfb->primary, RT_TRUE)))
            {
                return err;
            }
        }
        break;

    case RT_GRAPHIC_DPMS_STANDBY:
    case RT_GRAPHIC_DPMS_SUSPEND:
        if (sfb->primary)
        {
            spacemit_fb_plane_commit(sfb->primary, RT_FALSE);
        }
        break;

    case RT_GRAPHIC_DPMS_OFF:
        if (sfb->primary)
        {
            spacemit_fb_plane_commit(sfb->primary, RT_FALSE);
        }

        if (sfb->connector_enabled && sfb->connector->ops->disable)
        {
            sfb->connector->ops->disable(sfb->connector);
            sfb->connector_enabled = RT_FALSE;
        }

        spacemit_fb_vsync_irq_enable(sfb, RT_FALSE);
        rt_reset_control_assert(sfb->rstc);
        sfb->powered = RT_FALSE;
        sfb->dpu_configured = RT_FALSE;
        spacemit_fb_clocks_disable(sfb);
        break;

    default:
        return -RT_EINVAL;
    }

    gdev->dpms = dpms;
    return RT_EOK;
}

static rt_err_t spacemit_fb_wait_vsync(struct rt_graphic_device *gdev)
{
    struct spacemit_fb *sfb = rt_container_of(gdev, struct spacemit_fb, parent);
    rt_uint32_t timeout_ms;
    rt_err_t err;

    if (!sfb->powered || !sfb->irq_attached)
    {
        return -RT_EIO;
    }

    while (rt_sem_take(&sfb->vsync_sem, 0) == RT_EOK)
    {
    }

    rt_atomic_store(&sfb->vsync_waiting, RT_TRUE);
    timeout_ms = rt_max(50U, (3000U + sfb->refresh - 1U) / sfb->refresh);
    err = rt_sem_take(&sfb->vsync_sem,
            rt_tick_from_millisecond(timeout_ms));
    rt_atomic_store(&sfb->vsync_waiting, RT_FALSE);

    if (err)
    {
        LOG_W("wait for VSYNC timed out: raw=0x%08x mask=0x%08x",
                spacemit_fb_readl(sfb, SPACEMIT_DPU_INT_ONLINE2_RAW),
                spacemit_fb_readl(sfb, SPACEMIT_DPU_INT_ONLINE2_MASK));
    }

    return err;
}

static const struct rt_graphic_device_ops spacemit_fb_ops =
{
    .dpms_switch = spacemit_fb_dpms_switch,
    .wait_vsync = spacemit_fb_wait_vsync,
};

static rt_err_t spacemit_fb_plane_create(struct spacemit_fb *sfb)
{
    rt_err_t err;
    struct rt_graphic_plane *plane;

    plane = rt_graphic_device_alloc_plane(&sfb->parent,
            sizeof(struct spacemit_fb_plane), &spacemit_fb_plane_ops,
            spacemit_fb_modes, RT_ARRAY_SIZE(spacemit_fb_modes),
            RT_GRAPHIC_PLANE_TYPE_PRIMARY);
    if (!plane)
    {
        return -RT_ENOMEM;
    }
    if ((err = rt_graphic_device_add_plane(&sfb->parent, plane)))
    {
        rt_graphic_device_free_plane(plane);
        return err;
    }

    plane->mode = RTGRAPHIC_PIXEL_FORMAT_ARGB888;
    plane->bits_per_pixel = 32;
    /* Let graphic registration allocate the initial buffer from EDID size. */
    plane->width = 0;
    plane->height = 0;
    plane->alpha = 0xff;
    sfb->primary = plane;

    return RT_EOK;
}

static rt_err_t spacemit_fb_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    const char *connector_compatible;
    struct rt_ofw_node *display_np;
    struct rt_device *dev = &pdev->parent;
    struct spacemit_fb *sfb = rt_calloc(1, sizeof(*sfb));

    if (!sfb)
    {
        return -RT_ENOMEM;
    }

    sfb->dev = dev;
    if (rt_dm_dev_prop_read_u32(dev, "type", &sfb->output_type) ||
        sfb->output_type > SPACEMIT_DPU_DSI)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    display_np = spacemit_fb_find_display_node(dev->ofw_node,
            sfb->output_type);
    if (!display_np)
    {
        LOG_E("cannot find Saturn register node for %s",
                rt_ofw_node_full_name(dev->ofw_node));
        err = -RT_ENOENT;
        goto _fail;
    }

    sfb->regs = rt_ofw_iomap(display_np, 0);
    rt_ofw_node_put(display_np);
    if (!sfb->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    sfb->clks = rt_clk_get_array(dev);
    if (rt_is_err(sfb->clks))
    {
        err = rt_ptr_err(sfb->clks);
        sfb->clks = RT_NULL;
        goto _fail_unmap;
    }
    if ((err = spacemit_fb_clocks_enable(sfb)))
    {
        goto _fail_clks;
    }

    sfb->rstc = rt_reset_control_get_by_name(dev, "hdmi_reset");
    if (rt_is_err(sfb->rstc))
    {
        err = rt_ptr_err(sfb->rstc);
        sfb->rstc = RT_NULL;
        LOG_E("get DPU reset failed: %s", rt_strerror(err));
        goto _fail_power;
    }

    if ((err = rt_reset_control_assert(sfb->rstc)))
    {
        LOG_E("assert DPU reset failed: %s", rt_strerror(err));
        goto _fail_reset;
    }
    rt_hw_us_delay(10);
    if ((err = rt_reset_control_deassert(sfb->rstc)))
    {
        LOG_E("deassert DPU reset failed: %s", rt_strerror(err));
        goto _fail_reset;
    }
    rt_hw_us_delay(10);

    connector_compatible = sfb->output_type == SPACEMIT_DPU_HDMI ?
            "spacemit,hdmi" : "spacemit,dsi2-host";
    sfb->connector = spacemit_display_connector_find(connector_compatible);
    if (!sfb->connector)
    {
        LOG_E("no enabled %s connector found", connector_compatible);
        err = -RT_ENOENT;
        goto _fail_reset;
    }

    if ((err = sfb->connector->ops->get_timing(sfb->connector,
            &sfb->timing)))
    {
        LOG_E("get connector timing failed: %s", rt_strerror(err));
        goto _fail_reset;
    }

    sfb->width = sfb->timing.hactive;
    sfb->height = sfb->timing.vactive;
    sfb->refresh = sfb->timing.refresh;
    if (!sfb->width || !sfb->height || !sfb->refresh ||
        !sfb->timing.pixelclock || !sfb->timing.hsync_len ||
        !sfb->timing.vsync_len ||
        sfb->width > SPACEMIT_DPU_MAX_DIMENSION ||
        sfb->height > SPACEMIT_DPU_MAX_DIMENSION)
    {
        err = -RT_EINVAL;
        goto _fail_reset;
    }

    if ((err = sfb->connector->ops->enable(sfb->connector, &sfb->timing)))
    {
        LOG_E("connector cold init failed: %s", rt_strerror(err));
        goto _fail_reset;
    }
    sfb->connector_enabled = RT_TRUE;
    sfb->powered = RT_TRUE;

    if ((err = spacemit_fb_irq_setup(sfb)))
    {
        LOG_E("setup DPU VSYNC interrupt failed: %s", rt_strerror(err));
        goto _fail_connector;
    }

    spacemit_fb_find_reserved_buffer(sfb);
    if (!sfb->reserved_fb_size)
    {
        LOG_W("no reserved framebuffer found, initial scanout uses CMA");
    }

    sfb->parent.ops = &spacemit_fb_ops;
    if ((err = spacemit_fb_plane_create(sfb)))
    {
        goto _fail_connector;
    }

    if ((err = rt_graphic_device_simple_edid(&sfb->parent, sfb->width,
            sfb->height, sfb->refresh)))
    {
        rt_graphic_device_del_plane(&sfb->parent, sfb->primary);
        rt_graphic_device_free_plane(sfb->primary);
        sfb->primary = RT_NULL;
        goto _fail_connector;
    }
    if ((err = rt_graphic_device_register(&sfb->parent)))
    {
        rt_graphic_device_del_plane(&sfb->parent, sfb->primary);
        rt_graphic_device_free_plane(sfb->primary);
        sfb->primary = RT_NULL;
        goto _fail_connector;
    }

    if ((err = spacemit_fb_dpms_switch(&sfb->parent, RT_GRAPHIC_DPMS_ON)))
    {
        rt_graphic_device_unregister(&sfb->parent);
        sfb->primary = RT_NULL;
        goto _fail_connector;
    }
    pdev->parent.user_data = sfb;

    LOG_D("%s framebuffer fb%u: %ux%u@%u",
            sfb->output_type == SPACEMIT_DPU_HDMI ? "HDMI" : "DSI",
            sfb->parent.parent.device_id, sfb->width, sfb->height,
            sfb->refresh);

    return RT_EOK;

_fail_connector:
    spacemit_fb_irq_cleanup(sfb);
    if (sfb->connector_enabled && sfb->connector->ops->disable)
    {
        sfb->connector->ops->disable(sfb->connector);
        sfb->connector_enabled = RT_FALSE;
    }
    sfb->powered = RT_FALSE;
_fail_reset:
    if (sfb->rstc)
    {
        rt_reset_control_assert(sfb->rstc);
        rt_reset_control_put(sfb->rstc);
    }
_fail_power:
    spacemit_fb_clocks_disable(sfb);
_fail_clks:
    if (sfb->clks)
    {
        rt_clk_array_put(sfb->clks);
    }
_fail_unmap:
    rt_iounmap(sfb->regs);
_fail:
    rt_free(sfb);
    return err;
}

static rt_err_t spacemit_fb_remove(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct spacemit_fb *sfb = pdev->parent.user_data;

    if (!sfb)
    {
        return RT_EOK;
    }

    if ((err = rt_graphic_device_unregister(&sfb->parent)))
    {
        return err;
    }
    sfb->primary = RT_NULL;
    spacemit_fb_irq_cleanup(sfb);
    if (sfb->rstc)
    {
        rt_reset_control_put(sfb->rstc);
    }
    if (sfb->clks)
    {
        rt_clk_array_put(sfb->clks);
    }
    rt_iounmap(sfb->regs);
    rt_free(sfb);
    pdev->parent.user_data = RT_NULL;

    return RT_EOK;
}

static const struct rt_ofw_node_id spacemit_fb_ids[] =
{
    { .compatible = "spacemit,dpu-online2" },
    { /* sentinel */ }
};

static struct rt_platform_driver spacemit_fb_driver =
{
    .name = "spacemit-framebuffer",
    .ids = spacemit_fb_ids,
    .probe = spacemit_fb_probe,
    .remove = spacemit_fb_remove,
};

rt_err_t spacemit_fb_driver_register(void)
{
    return rt_platform_driver_register(&spacemit_fb_driver);
}
