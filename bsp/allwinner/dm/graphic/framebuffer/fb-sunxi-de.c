/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>

#define DBG_TAG "fb.sunxi"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#include <mm_aspace.h>

#include "sunxi-display-output.h"

#define SUNXI_DE_TOP_RESET              0x0010
#define SUNXI_DE_TOP_AHB_GATE           0x0014
#define SUNXI_DE_TOP_MBUS_GATE          0x0018
#define SUNXI_DE_TOP_CLK_GATE           0x001c
#define SUNXI_DE_GLB_CTL               0x0100
#define SUNXI_DE_GLB_SIZE              0x0108
#define SUNXI_DE_UI0                   0x161000
#define SUNXI_DE_UI_ATTR               0x0000
#define SUNXI_DE_UI_SIZE               0x0004
#define SUNXI_DE_UI_COORD              0x0008
#define SUNXI_DE_UI_PITCH              0x000c
#define SUNXI_DE_UI_LADDR              0x0010
#define SUNXI_DE_UI_HADDR              0x0080
#define SUNXI_DE_BLD                   0x1c1000
#define SUNXI_DE_BLD_FCOLOR_CTL        0x0000
#define SUNXI_DE_BLD_PIPE0_FCOLOR      0x0004
#define SUNXI_DE_BLD_PIPE0_SIZE        0x0008
#define SUNXI_DE_BLD_PIPE0_OFFSET      0x000c
#define SUNXI_DE_BLD_ROUTE             0x007c
#define SUNXI_DE_BLD_PREMULTIPLY       0x0080
#define SUNXI_DE_BLD_BKCOLOR           0x0084
#define SUNXI_DE_BLD_OUTPUT_SIZE       0x0088
#define SUNXI_DE_BLD_MODE0             0x008c

#define SUNXI_TCON_GCTL                0x0000
#define SUNXI_TCON_GINT0               0x0004
#define SUNXI_TCON0_CTL                0x0040
#define SUNXI_TCON0_DCLK               0x0044
#define SUNXI_TCON0_BASIC0             0x0048
#define SUNXI_TCON0_BASIC1             0x004c
#define SUNXI_TCON0_BASIC2             0x0050
#define SUNXI_TCON0_BASIC3             0x0054
#define SUNXI_TCON0_HV_CTL             0x0058
#define SUNXI_TCON0_CPU_CTL            0x0060
#define SUNXI_TCON0_IO_POL             0x0088
#define SUNXI_TCON0_IO_TRI             0x008c
#define SUNXI_TCON_ECC_FIFO             0x00f8
#define SUNXI_TCON0_CPU_TRI0            0x0160
#define SUNXI_TCON0_CPU_TRI1            0x0164
#define SUNXI_TCON0_CPU_TRI2            0x0168
#define SUNXI_TCON_SAFE_PERIOD          0x01f0

#define SUNXI_TCON_TOP_TV_SETUP        0x0000
#define SUNXI_TCON_TOP_DE_PERH         0x001c

#define SUNXI_DE_FMT_ARGB8888          0
#define SUNXI_DE_FMT_ABGR8888          1
#define SUNXI_DE_UI_CHAN               3

struct sunxi_fb
{
    struct rt_graphic_device parent;

    struct rt_device *dev;
    struct rt_clk_array *clks;
    struct rt_reset_control *resets;
    void *de;
    void *tcon;
    void *top;
    void *dsi;
    struct sunxi_fb_timing timing;
    struct sunxi_display_output output;
    rt_uint32_t dclk_div;
    rt_uint32_t rgb_swap;
    rt_uint32_t tcon_ctl;
    rt_ubase_t framebuffer_dma;
    rt_bool_t rb_swap;
    rt_bool_t clks_enabled;
};

static const rt_uint32_t sunxi_fb_modes[] =
{
    RTGRAPHIC_PIXEL_FORMAT_ARGB888,
    RTGRAPHIC_PIXEL_FORMAT_ABGR888,
};

static rt_err_t sunxi_fb_timing_read_u32(struct rt_ofw_node *np,
        const char *prop, rt_uint32_t *value)
{
    int count = rt_ofw_prop_count_of_u32(np, prop);

    if (count <= 0)
    {
        return count ? (rt_err_t)count : -RT_ENOENT;
    }

    /* The timing binding permits <min typical max>; use its typical value. */
    return rt_ofw_prop_read_u32_index(np, prop, count >= 3 ? 1 : 0, value);
}

static rt_err_t sunxi_fb_timing_parse_node(struct rt_ofw_node *np,
        struct sunxi_fb_timing *timing)
{
    rt_uint32_t value;
    rt_uint64_t htotal;
    rt_uint64_t vtotal;

    rt_memset(timing, 0, sizeof(*timing));

    if (sunxi_fb_timing_read_u32(np, "clock-frequency", &timing->pixelclock) ||
        sunxi_fb_timing_read_u32(np, "hactive", &timing->hactive) ||
        sunxi_fb_timing_read_u32(np, "hfront-porch", &timing->hfront_porch) ||
        sunxi_fb_timing_read_u32(np, "hback-porch", &timing->hback_porch) ||
        sunxi_fb_timing_read_u32(np, "hsync-len", &timing->hsync_len) ||
        sunxi_fb_timing_read_u32(np, "vactive", &timing->vactive) ||
        sunxi_fb_timing_read_u32(np, "vfront-porch", &timing->vfront_porch) ||
        sunxi_fb_timing_read_u32(np, "vback-porch", &timing->vback_porch) ||
        sunxi_fb_timing_read_u32(np, "vsync-len", &timing->vsync_len))
    {
        return -RT_EINVAL;
    }

    timing->hsync_active = RT_TRUE;
    timing->vsync_active = RT_TRUE;
    timing->pixelclk_active = RT_TRUE;

    if (!rt_ofw_prop_read_u32(np, "hsync-active", &value))
    {
        timing->hsync_active = !!value;
    }
    if (!rt_ofw_prop_read_u32(np, "vsync-active", &value))
    {
        timing->vsync_active = !!value;
    }
    if (!rt_ofw_prop_read_u32(np, "pixelclk-active", &value))
    {
        timing->pixelclk_active = !!value;
    }

    htotal = (rt_uint64_t)timing->hactive + timing->hfront_porch +
            timing->hback_porch + timing->hsync_len;
    vtotal = (rt_uint64_t)timing->vactive + timing->vfront_porch +
            timing->vback_porch + timing->vsync_len;

    if (!timing->pixelclock || !timing->hactive || !timing->vactive ||
        !timing->hsync_len || !timing->vsync_len ||
        timing->hactive > 4096 || timing->vactive > 4096 ||
        timing->hsync_len > 1024 || timing->vsync_len > 1024 ||
        htotal > 8192 || vtotal > 4095 ||
        timing->hsync_len + timing->hback_porch > 4096 ||
        timing->vsync_len + timing->vback_porch > 4096)
    {
        return -RT_EINVAL;
    }

    timing->htotal = (rt_uint32_t)htotal;
    timing->vtotal = (rt_uint32_t)vtotal;

    return RT_EOK;
}

static rt_err_t sunxi_fb_timing_parse(struct sunxi_fb *fb)
{
    rt_err_t err = -RT_ENOENT;
    struct rt_ofw_node *child;
    struct rt_ofw_node *timings;
    struct rt_ofw_node *np = fb->dev->ofw_node;

    if (!(err = sunxi_fb_timing_parse_node(np, &fb->timing)))
    {
        return RT_EOK;
    }

    child = rt_ofw_get_child_by_tag(np, "panel-timing");
    if (child)
    {
        err = sunxi_fb_timing_parse_node(child, &fb->timing);
        rt_ofw_node_put(child);

        if (!err)
        {
            return RT_EOK;
        }
    }

    timings = rt_ofw_get_child_by_tag(np, "display-timings");
    if (!timings)
    {
        return err;
    }

    child = rt_ofw_parse_phandle(timings, "native-mode", 0);
    if (child)
    {
        err = sunxi_fb_timing_parse_node(child, &fb->timing);
        rt_ofw_node_put(child);

        if (!err)
        {
            rt_ofw_node_put(timings);
            return RT_EOK;
        }
    }

    rt_ofw_foreach_available_child_node(timings, child)
    {
        err = sunxi_fb_timing_parse_node(child, &fb->timing);

        if (!err)
        {
            rt_ofw_node_put(child);
            rt_ofw_node_put(timings);
            return RT_EOK;
        }
    }

    rt_ofw_node_put(timings);

    return err;
}

static rt_uint32_t sunxi_fb_de_format(rt_uint32_t mode)
{
    switch (mode)
    {
    case RTGRAPHIC_PIXEL_FORMAT_ARGB888:
        return SUNXI_DE_FMT_ARGB8888;

    case RTGRAPHIC_PIXEL_FORMAT_ABGR888:
        return SUNXI_DE_FMT_ABGR8888;

    default:
        return RT_UINT32_MAX;
    }
}

static void sunxi_fb_program_plane(struct sunxi_fb *fb,
        struct rt_graphic_plane *plane, rt_ubase_t dma)
{
    rt_uint32_t format = sunxi_fb_de_format(plane->mode);
    rt_uint32_t attr;
    rt_uint32_t size;

    attr = RT_BIT(0) | (format << 8) | (0xff << 24);
    size = (plane->width - 1) | ((plane->height - 1) << 16);

    HWREG32(fb->de + SUNXI_DE_UI0 + SUNXI_DE_UI_SIZE) = size;
    HWREG32(fb->de + SUNXI_DE_UI0 + SUNXI_DE_UI_COORD) = 0;
    HWREG32(fb->de + SUNXI_DE_UI0 + SUNXI_DE_UI_PITCH) = plane->line_length;
    HWREG32(fb->de + SUNXI_DE_UI0 + SUNXI_DE_UI_LADDR) = (rt_uint32_t)dma;
    HWREG32(fb->de + SUNXI_DE_UI0 + SUNXI_DE_UI_HADDR) = 0;
    HWREG32(fb->de + SUNXI_DE_UI0 + SUNXI_DE_UI_ATTR) = attr;
}

static void sunxi_fb_program_de(struct sunxi_fb *fb)
{
    const struct sunxi_fb_timing *timing = &fb->timing;
    rt_uint32_t size = (timing->hactive - 1) |
            ((timing->vactive - 1) << 16);

    HWREG32(fb->de + SUNXI_DE_UI0 + SUNXI_DE_UI_ATTR) = 0;
    HWREG32(fb->de + SUNXI_DE_TOP_RESET) |= RT_BIT(0);
    HWREG32(fb->de + SUNXI_DE_TOP_AHB_GATE) |= RT_BIT(0);
    HWREG32(fb->de + SUNXI_DE_TOP_MBUS_GATE) |= RT_BIT(0);
    HWREG32(fb->de + SUNXI_DE_TOP_CLK_GATE) |= RT_BIT(0);
    HWREG32(fb->de + SUNXI_DE_GLB_SIZE) = size;
    HWREG32(fb->de + SUNXI_DE_BLD + SUNXI_DE_BLD_FCOLOR_CTL) =
            RT_BIT(0) | RT_BIT(8);
    HWREG32(fb->de + SUNXI_DE_BLD + SUNXI_DE_BLD_PIPE0_FCOLOR) = 0xff000000;
    HWREG32(fb->de + SUNXI_DE_BLD + SUNXI_DE_BLD_PIPE0_SIZE) = size;
    HWREG32(fb->de + SUNXI_DE_BLD + SUNXI_DE_BLD_PIPE0_OFFSET) = 0;
    HWREG32(fb->de + SUNXI_DE_BLD + SUNXI_DE_BLD_ROUTE) = SUNXI_DE_UI_CHAN;
    HWREG32(fb->de + SUNXI_DE_BLD + SUNXI_DE_BLD_PREMULTIPLY) = 0;
    HWREG32(fb->de + SUNXI_DE_BLD + SUNXI_DE_BLD_BKCOLOR) = 0xff000000;
    HWREG32(fb->de + SUNXI_DE_BLD + SUNXI_DE_BLD_OUTPUT_SIZE) = size;
    HWREG32(fb->de + SUNXI_DE_BLD + SUNXI_DE_BLD_MODE0) = 0x00010001;
    HWREG32(fb->de + SUNXI_DE_GLB_CTL) = RT_BIT(0);
}

static void sunxi_fb_route_de_to_tcon(struct sunxi_fb *fb)
{
    rt_uint32_t value;

    /* DISPLAY_TOP routes DE port 0 to TCON 0 through bits [1:0]. */
    value = HWREG32(fb->top + SUNXI_TCON_TOP_DE_PERH);
    value &= ~0x3;
    HWREG32(fb->top + SUNXI_TCON_TOP_DE_PERH) = value;

    /* RGB and LVDS leave TCON 0 through the LCD pads. */
    if (fb->output.type != SUNXI_DISPLAY_OUTPUT_DSI)
    {
        HWREG32(fb->top + SUNXI_TCON_TOP_TV_SETUP) &= ~RT_BIT(8);
    }
}

static void sunxi_fb_program_tcon(struct sunxi_fb *fb)
{
    const struct sunxi_fb_timing *timing = &fb->timing;
    rt_uint32_t hbp = timing->hsync_len + timing->hback_porch;
    rt_uint32_t vbp = timing->vsync_len + timing->vback_porch;
    rt_int32_t start_delay;
    rt_uint32_t dclk_div = fb->dclk_div;
    rt_uint32_t safe_period;
    rt_uint32_t io_pol = 0;
    rt_uint32_t ctl;

    if (timing->hsync_active)
    {
        io_pol |= RT_BIT(25);
    }
    if (timing->vsync_active)
    {
        io_pol |= RT_BIT(24);
    }
    if (!timing->pixelclk_active)
    {
        io_pol |= RT_BIT(26);
    }

    /* F101's TCON interrupt flags are cleared by writing zero. */
    HWREG32(fb->tcon + SUNXI_TCON_GCTL) = RT_BIT(1);
    HWREG32(fb->tcon + SUNXI_TCON_GINT0) = 0;
    HWREG32(fb->tcon + SUNXI_TCON0_CTL) = 0;
    HWREG32(fb->tcon + SUNXI_TCON0_DCLK) = dclk_div | (0xf << 28);
    HWREG32(fb->tcon + SUNXI_TCON0_BASIC0) =
            (timing->vactive - 1) | ((timing->hactive - 1) << 16);
    HWREG32(fb->tcon + SUNXI_TCON0_BASIC1) =
            (hbp - 1) | ((timing->htotal - 1) << 16);
    HWREG32(fb->tcon + SUNXI_TCON0_BASIC2) =
            (vbp - 1) | ((timing->vtotal * 2) << 16);
    HWREG32(fb->tcon + SUNXI_TCON0_BASIC3) =
            (timing->vsync_len - 1) | ((timing->hsync_len - 1) << 16);
    HWREG32(fb->tcon + SUNXI_TCON0_HV_CTL) = RT_BIT(19);
    HWREG32(fb->tcon + SUNXI_TCON0_IO_POL) = io_pol;
    HWREG32(fb->tcon + SUNXI_TCON0_IO_TRI) = 0;

    start_delay = (rt_int32_t)timing->vtotal - timing->vactive - 8;
    if (start_delay < 10)
    {
        start_delay = 10;
    }
    else if (start_delay > 31)
    {
        start_delay = 31;
    }
    safe_period = timing->pixelclock / 1000000 * 15;
    if (safe_period > 0x1fffU)
    {
        safe_period = 0x1fffU;
    }
    HWREG32(fb->tcon + SUNXI_TCON_SAFE_PERIOD) =
            3 | (safe_period << 16);

    if (fb->output.type == SUNXI_DISPLAY_OUTPUT_DSI)
    {
        rt_uint32_t vbp = timing->vsync_len + timing->vback_porch;
        rt_uint32_t delay_lines = vbp > timing->vsync_len + 3 ? 3 : vbp;
        rt_uint32_t tri_start_delay = delay_lines * timing->htotal / 8;

        if (tri_start_delay)
        {
            tri_start_delay--;
        }

        /* TCON0 produces one RGB888 video line request for every active line. */
        HWREG32(fb->tcon + SUNXI_TCON0_CPU_CTL) = (1 << 28) | RT_BIT(26) |
                RT_BIT(16) | RT_BIT(2) | RT_BIT(0);
        HWREG32(fb->tcon + SUNXI_TCON_ECC_FIFO) = 1 << 3;
        HWREG32(fb->tcon + SUNXI_TCON0_CPU_TRI0) =
                (timing->hactive - 1) |
                (((timing->htotal - timing->hactive) / 2) << 16);
        HWREG32(fb->tcon + SUNXI_TCON0_CPU_TRI1) = timing->vactive - 1;
        HWREG32(fb->tcon + SUNXI_TCON0_CPU_TRI2) =
                (tri_start_delay << 16) | 10;
    }

    ctl = ((rt_uint32_t)start_delay << 4) | (fb->rgb_swap << 16) |
            (fb->rb_swap ? RT_BIT(23) : 0) |
            RT_BIT(31);
    if (fb->output.type == SUNXI_DISPLAY_OUTPUT_DSI)
    {
        ctl |= RT_BIT(24);
    }
    fb->tcon_ctl = ctl;

    sunxi_fb_route_de_to_tcon(fb);
}

static void sunxi_fb_enable_tcon(struct sunxi_fb *fb)
{
    HWREG32(fb->tcon + SUNXI_TCON0_CTL) = fb->tcon_ctl;
    HWREG32(fb->tcon + SUNXI_TCON_GCTL) = RT_BIT(1) | RT_BIT(31);
}

static void sunxi_fb_hw_disable(struct sunxi_fb *fb)
{
    sunxi_display_output_disable(&fb->output);

    if (fb->de)
    {
        HWREG32(fb->de + SUNXI_DE_UI0 + SUNXI_DE_UI_ATTR) = 0;
        HWREG32(fb->de + SUNXI_DE_GLB_CTL) = 0;
        HWREG32(fb->de + SUNXI_DE_TOP_CLK_GATE) &= ~RT_BIT(0);
        HWREG32(fb->de + SUNXI_DE_TOP_MBUS_GATE) &= ~RT_BIT(0);
        HWREG32(fb->de + SUNXI_DE_TOP_AHB_GATE) &= ~RT_BIT(0);
        HWREG32(fb->de + SUNXI_DE_TOP_RESET) &= ~RT_BIT(0);
    }

    if (fb->tcon)
    {
        HWREG32(fb->tcon + SUNXI_TCON0_CTL) = 0;
        HWREG32(fb->tcon + SUNXI_TCON0_DCLK) = 0;
        HWREG32(fb->tcon + SUNXI_TCON_GCTL) = 0;
    }
}

static rt_err_t sunxi_fb_plane_update(struct rt_graphic_plane *plane,
        struct rt_device_rect_info *rect)
{
    struct sunxi_fb *fb = rt_container_of(plane->graphic, struct sunxi_fb, parent);
    RT_UNUSED(rect);

    if (!plane->framebuffer || !fb->framebuffer_dma)
    {
        return -RT_EINVAL;
    }

    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, plane->framebuffer, plane->screen_len);
    sunxi_fb_program_plane(fb, plane, fb->framebuffer_dma);

    return RT_EOK;
}

static rt_err_t sunxi_fb_plane_fb_remap(struct rt_graphic_plane *plane,
        rt_uint32_t mode, struct rt_device_rect_info *rect)
{
    struct sunxi_fb *fb = rt_container_of(plane->graphic, struct sunxi_fb, parent);
    rt_uint32_t bpp = rt_graphic_mode_bpp(mode);
    rt_size_t screen_len;
    rt_ubase_t dma;
    void *buffer;

    if (!rect->width || !rect->height || !bpp ||
        rect->width != fb->timing.hactive || rect->height != fb->timing.vactive ||
        sunxi_fb_de_format(mode) == RT_UINT32_MAX)
    {
        return -RT_EINVAL;
    }

    plane->line_length = RT_ALIGN(rect->width * bpp, 64) / 8;
    screen_len = plane->line_length * rect->height;
    buffer = rt_malloc_align(screen_len, 64);
    if (!buffer)
    {
        return -RT_ENOMEM;
    }

    dma = (rt_ubase_t)rt_kmem_v2p(buffer);
    if ((rt_uint64_t)dma > RT_UINT32_MAX)
    {
        rt_free_align(buffer);

        return -RT_EINVAL;
    }

    rt_memset(buffer, 0, screen_len);
    rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH, buffer, screen_len);

    plane->bits_per_pixel = bpp;
    plane->framebuffer = buffer;
    plane->screen_len = screen_len;
    plane->framebuffer_len = screen_len;
    plane->width = rect->width;
    plane->height = rect->height;
    fb->framebuffer_dma = dma;
    sunxi_fb_program_plane(fb, plane, dma);

    return RT_EOK;
}

static rt_err_t sunxi_fb_plane_fb_cleanup(struct rt_graphic_plane *plane)
{
    struct sunxi_fb *fb = rt_container_of(plane->graphic, struct sunxi_fb, parent);

    if (fb->de)
    {
        HWREG32(fb->de + SUNXI_DE_UI0 + SUNXI_DE_UI_ATTR) = 0;
    }

    if (plane->framebuffer)
    {
        rt_free_align(plane->framebuffer);
        plane->framebuffer = RT_NULL;
        fb->framebuffer_dma = 0;
        plane->screen_len = 0;
        plane->framebuffer_len = 0;
    }

    return RT_EOK;
}

static const struct rt_graphic_plane_ops sunxi_fb_plane_ops =
{
    .update = sunxi_fb_plane_update,
    .fb_remap = sunxi_fb_plane_fb_remap,
    .fb_cleanup = sunxi_fb_plane_fb_cleanup,
};

static void sunxi_fb_resource_put(struct sunxi_fb *fb)
{
    if (!rt_is_err_or_null(fb->resets))
    {
        rt_reset_control_put(fb->resets);
    }
    if (!rt_is_err_or_null(fb->clks))
    {
        rt_clk_array_put(fb->clks);
    }
    if (fb->tcon)
    {
        rt_iounmap(fb->tcon);
    }
    if (fb->dsi)
    {
        rt_iounmap(fb->dsi);
    }
    if (fb->top)
    {
        rt_iounmap(fb->top);
    }
    if (fb->de)
    {
        rt_iounmap(fb->de);
    }
}

static rt_err_t sunxi_fb_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint32_t refresh_hz;
    rt_uint64_t frame_clocks;
    struct rt_device *dev = &pdev->parent;
    struct sunxi_fb *fb = rt_calloc(1, sizeof(*fb));

    if (!fb)
    {
        return -RT_ENOMEM;
    }

    fb->dev = dev;

    if ((err = sunxi_display_output_parse(dev, &fb->output)))
    {
        goto _fail;
    }

    if ((err = sunxi_fb_timing_parse(fb)))
    {
        LOG_E("%s: valid display timing is required", rt_dm_dev_get_name(dev));
        goto _fail;
    }

    if ((err = rt_dm_dev_prop_read_u32(dev, "allwinner,tcon-dclk-div",
            &fb->dclk_div)) || fb->dclk_div > 0x7f)
    {
        LOG_E("%s: valid tcon dclk divider is required", rt_dm_dev_get_name(dev));
        err = -RT_EINVAL;
        goto _fail;
    }

    rt_dm_dev_prop_read_u32(dev, "allwinner,rgb-swap", &fb->rgb_swap);
    fb->rb_swap = rt_dm_dev_prop_read_bool(dev, "allwinner,rb-swap");
    if (fb->rgb_swap > 7)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    fb->de = rt_ofw_iomap_by_name(dev->ofw_node, "de");
    fb->tcon = rt_ofw_iomap_by_name(dev->ofw_node, "tcon");
    fb->top = rt_ofw_iomap_by_name(dev->ofw_node, "display-top");
    if (!fb->de || !fb->tcon || !fb->top)
    {
        LOG_E("%s: DE, TCON, and display-top resources are required",
                rt_dm_dev_get_name(dev));
        err = -RT_EIO;
        goto _fail;
    }

    fb->output.tcon = fb->tcon;
    fb->output.top = fb->top;
    if (fb->output.type != SUNXI_DISPLAY_OUTPUT_RGB)
    {
        fb->dsi = rt_ofw_iomap_by_name(dev->ofw_node, "dsi");
        if (!fb->dsi)
        {
            LOG_E("%s: output needs the dsi register resource", rt_dm_dev_get_name(dev));
            err = -RT_EIO;
            goto _fail;
        }
        fb->output.dsi = fb->dsi;
        fb->output.dphy = fb->dsi + 0x1000;
    }
    fb->clks = rt_clk_get_array(dev);
    if (rt_is_err(fb->clks))
    {
        err = rt_ptr_err(fb->clks);
        goto _fail;
    }
    if (!fb->clks)
    {
        err = -RT_ENOENT;
        goto _fail;
    }

    fb->resets = rt_reset_control_get_array(dev);
    if (rt_is_err(fb->resets))
    {
        err = rt_ptr_err(fb->resets);
        goto _fail;
    }
    if (!fb->resets)
    {
        err = -RT_ENOENT;
        goto _fail;
    }

    if ((err = rt_pin_ctrl_confs_apply_by_name(dev, RT_NULL)))
    {
        LOG_E("%s: default pinctrl state is required", rt_dm_dev_get_name(dev));
        goto _fail;
    }

    if ((err = rt_clk_array_prepare_enable(fb->clks)))
    {
        goto _fail;
    }
    fb->clks_enabled = RT_TRUE;

    if ((err = rt_reset_control_deassert(fb->resets)))
    {
        goto _fail;
    }

    sunxi_fb_program_de(fb);
    sunxi_fb_program_tcon(fb);
    if ((err = sunxi_display_output_prepare(&fb->output, &fb->timing)))
    {
        goto _fail;
    }
    if ((err = sunxi_display_output_panel_init(&fb->output)))
    {
        LOG_E("%s: panel initialization failed: %s", rt_dm_dev_get_name(dev),
                rt_strerror(err));
        goto _fail;
    }
    sunxi_fb_enable_tcon(fb);
    sunxi_display_output_enable(&fb->output);

    frame_clocks = (rt_uint64_t)fb->timing.htotal * fb->timing.vtotal;
    refresh_hz = frame_clocks ? fb->timing.pixelclock / frame_clocks : 0;

    if ((err = rt_graphic_device_simple_register(&fb->parent,
            fb->timing.hactive, fb->timing.vactive, refresh_hz,
            &sunxi_fb_plane_ops, sunxi_fb_modes, RT_ARRAY_SIZE(sunxi_fb_modes))))
    {
        goto _fail;
    }

    dev->user_data = fb;

    return RT_EOK;

_fail:
    sunxi_fb_hw_disable(fb);
    if (!rt_is_err_or_null(fb->resets))
    {
        rt_reset_control_assert(fb->resets);
    }
    if (fb->clks_enabled)
    {
        rt_clk_array_disable_unprepare(fb->clks);
    }
    sunxi_fb_resource_put(fb);
    rt_free(fb);

    return err;
}

static rt_err_t sunxi_fb_remove(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct sunxi_fb *fb = pdev->parent.user_data;

    if ((err = rt_graphic_device_simple_unregister(&fb->parent)))
    {
        return err;
    }
    sunxi_fb_hw_disable(fb);
    rt_reset_control_assert(fb->resets);

    if (fb->clks_enabled)
    {
        rt_clk_array_disable_unprepare(fb->clks);
    }

    sunxi_fb_resource_put(fb);
    rt_free(fb);

    return RT_EOK;
}

static const struct rt_ofw_node_id sunxi_fb_ofw_ids[] =
{
    { .compatible = "allwinner,sun252i-f101-de0" },
    { /* sentinel */ }
};

static struct rt_platform_driver sunxi_fb_driver =
{
    .name = "sunxi-de",
    .ids = sunxi_fb_ofw_ids,
    .probe = sunxi_fb_probe,
    .remove = sunxi_fb_remove,
};
RT_PLATFORM_DRIVER_EXPORT(sunxi_fb_driver);
