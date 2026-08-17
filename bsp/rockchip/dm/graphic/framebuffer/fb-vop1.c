/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#include "fb-vop1.h"

#include <cpuport.h>

#define DBG_TAG "fb.vop1"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

/* RK3366 Lite (rk3308 / rk3506 / px30-lit class) */
#define VOP1_LIT_CFG_DONE               0x000
#define VOP1_LIT_WIN0_CTRL0             0x050
#define VOP1_LIT_WIN0_VIR               0x05c
#define VOP1_LIT_WIN0_YRGB_MST          0x060
#define VOP1_LIT_WIN0_ACT_INFO          0x068
#define VOP1_LIT_WIN0_DSP_INFO          0x06c
#define VOP1_LIT_WIN0_DSP_ST            0x070
#define VOP1_LIT_WIN0_ALPHA             0x080
#define VOP1_LIT_WIN1_CTRL0             0x090
#define VOP1_LIT_WIN1_VIR               0x098
#define VOP1_LIT_WIN1_MST               0x0a0
#define VOP1_LIT_WIN1_DSP_INFO          0x0a4
#define VOP1_LIT_WIN1_DSP_ST            0x0a8
#define VOP1_LIT_WIN1_ALPHA             0x0bc

/* RK3288-class big VOP (rk3328 / rk3288 / rk3399) */
#define VOP1_BIG_CFG_DONE               0x000

#define VOP1_WIN_EN_MASK                1
#define VOP1_WIN_EN_SHIFT               0
#define VOP1_WIN_FORMAT_MASK            0x7
#define VOP1_WIN_FORMAT_SHIFT           1

/* -------------------------------------------------------------------------- */
/* Lite window maps                                                            */
/* -------------------------------------------------------------------------- */

static const struct vop1fb_win_regs lite_win0_regs =
{
    .ctrl0 = VOP1_LIT_WIN0_CTRL0,
    .vir = VOP1_LIT_WIN0_VIR,
    .yrgb_mst = VOP1_LIT_WIN0_YRGB_MST,
    .act_info = VOP1_LIT_WIN0_ACT_INFO,
    .dsp_info = VOP1_LIT_WIN0_DSP_INFO,
    .dsp_st = VOP1_LIT_WIN0_DSP_ST,
    .alpha = VOP1_LIT_WIN0_ALPHA,
};

static const struct vop1fb_win_regs lite_win1_regs =
{
    .ctrl0 = VOP1_LIT_WIN1_CTRL0,
    .vir = VOP1_LIT_WIN1_VIR,
    .yrgb_mst = VOP1_LIT_WIN1_MST,
    .dsp_info = VOP1_LIT_WIN1_DSP_INFO,
    .dsp_st = VOP1_LIT_WIN1_DSP_ST,
    .alpha = VOP1_LIT_WIN1_ALPHA,
};

static const struct vop1fb_win_desc lite_primary =
{
    .name = "Win0",
    .regs = &lite_win0_regs,
    .z_order = 1,
};

static const struct vop1fb_win_desc lite_cursor =
{
    .name = "Win1",
    .regs = &lite_win1_regs,
    .z_order = 2,
};

/* -------------------------------------------------------------------------- */
/* Big window maps (win-relative offsets from each win base)                   */
/* -------------------------------------------------------------------------- */

#define VOP1_BIG_WIN_CTRL0              0x00
#define VOP1_BIG_WIN_VIR                0x0c
#define VOP1_BIG_WIN_YRGB_MST           0x10
#define VOP1_BIG_WIN_ACT_INFO           0x18
#define VOP1_BIG_WIN_DSP_INFO           0x1c
#define VOP1_BIG_WIN_DSP_ST             0x20
#define VOP1_BIG_WIN_ALPHA              0x30

static const struct vop1fb_win_regs big_win0_regs =
{
    .ctrl0 = 0xd0 + VOP1_BIG_WIN_CTRL0,
    .vir = 0xd0 + VOP1_BIG_WIN_VIR,
    .yrgb_mst = 0xd0 + VOP1_BIG_WIN_YRGB_MST,
    .act_info = 0xd0 + VOP1_BIG_WIN_ACT_INFO,
    .dsp_info = 0xd0 + VOP1_BIG_WIN_DSP_INFO,
    .dsp_st = 0xd0 + VOP1_BIG_WIN_DSP_ST,
    .alpha = 0xd0 + VOP1_BIG_WIN_ALPHA,
};

static const struct vop1fb_win_regs big_win1_regs =
{
    .ctrl0 = 0x1d0 + VOP1_BIG_WIN_CTRL0,
    .vir = 0x1d0 + VOP1_BIG_WIN_VIR,
    .yrgb_mst = 0x1d0 + VOP1_BIG_WIN_YRGB_MST,
    .act_info = 0x1d0 + VOP1_BIG_WIN_ACT_INFO,
    .dsp_info = 0x1d0 + VOP1_BIG_WIN_DSP_INFO,
    .dsp_st = 0x1d0 + VOP1_BIG_WIN_DSP_ST,
    .alpha = 0x1d0 + VOP1_BIG_WIN_ALPHA,
};

static const struct vop1fb_win_regs big_win2_regs =
{
    .ctrl0 = 0x2d0 + VOP1_BIG_WIN_CTRL0,
    .vir = 0x2d0 + VOP1_BIG_WIN_VIR,
    .yrgb_mst = 0x2d0 + VOP1_BIG_WIN_YRGB_MST,
    .act_info = 0x2d0 + VOP1_BIG_WIN_ACT_INFO,
    .dsp_info = 0x2d0 + VOP1_BIG_WIN_DSP_INFO,
    .dsp_st = 0x2d0 + VOP1_BIG_WIN_DSP_ST,
    .alpha = 0x2d0 + VOP1_BIG_WIN_ALPHA,
};

static const struct vop1fb_win_desc big_primary =
{
    .name = "Win0",
    .regs = &big_win0_regs,
    .z_order = 1,
};

static const struct vop1fb_win_desc big_cursor =
{
    .name = "Win2",
    .regs = &big_win2_regs,
    .z_order = 3,
};

static const struct vop1fb_win_desc big_overlays[] =
{
    {
        .name = "Win1",
        .regs = &big_win1_regs,
        .z_order = 2,
    },
};

static const struct vop1fb_soc_data vop1_lite_soc =
{
    .arch = VOP1FB_ARCH_LITE,
    .version = "vop1-lite",
    .reg_size = 0x200,
    .cfg_done = VOP1_LIT_CFG_DONE,
    .primary = &lite_primary,
    .cursor = &lite_cursor,
    .overlay_count = 0,
};

static const struct vop1fb_soc_data vop1_big_soc =
{
    .arch = VOP1FB_ARCH_BIG,
    .version = "vop1-big",
    .reg_size = 0x400,
    .cfg_done = VOP1_BIG_CFG_DONE,
    .primary = &big_primary,
    .cursor = &big_cursor,
    .overlays = big_overlays,
    .overlay_count = RT_ARRAY_SIZE(big_overlays),
};

static rt_uint32_t vop1fb_modes[] =
{
    RTGRAPHIC_PIXEL_FORMAT_ARGB888,
    RTGRAPHIC_PIXEL_FORMAT_RGB888,
    RTGRAPHIC_PIXEL_FORMAT_RGB565,
};

/* -------------------------------------------------------------------------- */
/* Helpers                                                                    */
/* -------------------------------------------------------------------------- */

rt_uint32_t vop1fb_mode_to_hw(rt_uint32_t mode)
{
    switch (mode)
    {
    case RTGRAPHIC_PIXEL_FORMAT_ARGB888:
    case RTGRAPHIC_PIXEL_FORMAT_ABGR888:
        return VOP1FB_FMT_ARGB8888;
    case RTGRAPHIC_PIXEL_FORMAT_RGB888:
    case RTGRAPHIC_PIXEL_FORMAT_BGR888:
        return VOP1FB_FMT_RGB888;
    case RTGRAPHIC_PIXEL_FORMAT_RGB565:
    case RTGRAPHIC_PIXEL_FORMAT_BGR565:
        return VOP1FB_FMT_RGB565;
    default:
        return VOP1FB_FMT_ARGB8888;
    }
}

rt_uint32_t vop1fb_hw_to_bpp(rt_uint32_t hw_fmt)
{
    switch (hw_fmt)
    {
    case VOP1FB_FMT_RGB565:
        return 16;
    case VOP1FB_FMT_RGB888:
        return 24;
    default:
        return 32;
    }
}

static struct vop1fb *vop1fb_from_plane(struct rt_graphic_plane *plane)
{
    return rt_container_of(plane->graphic, struct vop1fb, parent);
}

static struct vop1fb_plane_priv *vop1fb_plane_priv(struct rt_graphic_plane *plane)
{
    return (struct vop1fb_plane_priv *)plane->priv;
}

rt_inline void vop1fb_reg_write(struct vop1fb *vfb, rt_uint32_t offset, rt_uint32_t v)
{
    HWREG32((rt_uint8_t *)vfb->regs + offset) = v;
}

rt_inline void vop1fb_mask_write(struct vop1fb *vfb, rt_uint32_t offset,
        rt_uint32_t mask, rt_uint32_t shift, rt_uint32_t v)
{
    rt_uint32_t cached = HWREG32((rt_uint8_t *)vfb->regs + offset);
    rt_uint32_t newv = (cached & ~(mask << shift)) | ((v & mask) << shift);

    vop1fb_reg_write(vfb, offset, newv);
}

static rt_uint32_t vop1fb_xvir(rt_uint32_t width, rt_uint32_t bpp)
{
    return RT_ALIGN(width * bpp, 32) >> 5;
}

static void vop1fb_cfg_done(struct vop1fb *vfb)
{
    vop1fb_reg_write(vfb, vfb->soc->cfg_done, 1);
}

static void vop1fb_win_disable(struct vop1fb *vfb, const struct vop1fb_win_desc *desc)
{
    const struct vop1fb_win_regs *r = desc->regs;

    vop1fb_mask_write(vfb, r->ctrl0, VOP1_WIN_EN_MASK, VOP1_WIN_EN_SHIFT, 0);
    vop1fb_cfg_done(vfb);
}

static void vop1fb_win_alpha(struct vop1fb *vfb, const struct vop1fb_win_desc *desc,
        rt_uint8_t alpha)
{
    const struct vop1fb_win_regs *r = desc->regs;

    if (!r->alpha)
    {
        return;
    }

    /* alpha_en | alpha_mode | global_alpha */
    vop1fb_reg_write(vfb, r->alpha, RT_BIT(0) | RT_BIT(1) | ((rt_uint32_t)alpha << 4));
}

static rt_err_t vop1fb_win_commit(struct vop1fb *vfb, const struct vop1fb_win_desc *desc,
        rt_ubase_t dma_addr, rt_uint32_t hw_fmt,
        rt_uint32_t src_w, rt_uint32_t src_h,
        rt_uint32_t dst_x, rt_uint32_t dst_y,
        rt_uint32_t dst_w, rt_uint32_t dst_h,
        rt_uint32_t xvir, rt_bool_t enable, rt_uint8_t alpha)
{
    const struct vop1fb_win_regs *r = desc->regs;
    rt_uint32_t act_info, dsp_info, dsp_st;
    rt_uint32_t fmt_shift = VOP1_WIN_FORMAT_SHIFT;

    if (!enable)
    {
        vop1fb_win_disable(vfb, desc);
        return RT_EOK;
    }

    if (vfb->soc->arch == VOP1FB_ARCH_LITE && desc != vfb->soc->primary)
    {
        fmt_shift = 4;
    }

    act_info = ((src_h - 1) << 16) | ((src_w - 1) & 0xffff);
    dsp_info = ((dst_h - 1) << 16) | ((dst_w - 1) & 0xffff);
    dsp_st = (dst_y << 16) | (dst_x & 0xffff);

    vop1fb_mask_write(vfb, r->ctrl0, VOP1_WIN_FORMAT_MASK, fmt_shift, hw_fmt);

    if (r->vir)
    {
        vop1fb_reg_write(vfb, r->vir, xvir);
    }

    vop1fb_reg_write(vfb, r->yrgb_mst, (rt_uint32_t)dma_addr);

    if (r->act_info)
    {
        vop1fb_reg_write(vfb, r->act_info, act_info);
    }

    vop1fb_reg_write(vfb, r->dsp_info, dsp_info);
    vop1fb_reg_write(vfb, r->dsp_st, dsp_st);
    vop1fb_win_alpha(vfb, desc, alpha);
    vop1fb_mask_write(vfb, r->ctrl0, VOP1_WIN_EN_MASK, VOP1_WIN_EN_SHIFT, 1);
    vop1fb_cfg_done(vfb);

    return RT_EOK;
}

static rt_err_t vop1fb_plane_commit(struct rt_graphic_plane *plane, rt_bool_t enable)
{
    struct vop1fb *vfb = vop1fb_from_plane(plane);
    struct vop1fb_plane_priv *priv = vop1fb_plane_priv(plane);
    rt_uint32_t bpp = rt_graphic_mode_bpp(plane->mode);
    rt_uint32_t xvir;
    rt_ubase_t dma;
    rt_uint32_t dst_w, dst_h, dst_x, dst_y;

    if (!priv || !priv->desc)
    {
        return -RT_EINVAL;
    }

    if (!enable || !plane->framebuffer)
    {
        priv->enabled = RT_FALSE;
        vop1fb_win_disable(vfb, priv->desc);
        return RT_EOK;
    }

    dma = priv->dma_handle + priv->pan_offset;
    xvir = vop1fb_xvir(plane->width, bpp);

    if (plane->type == RT_GRAPHIC_PLANE_TYPE_PRIMARY)
    {
        dst_x = 0;
        dst_y = 0;
        dst_w = plane->width;
        dst_h = plane->height;
    }
    else
    {
        dst_x = plane->x;
        dst_y = plane->y;
        dst_w = plane->width;
        dst_h = plane->height;
    }

    priv->enabled = RT_TRUE;

    return vop1fb_win_commit(vfb, priv->desc, dma, vop1fb_mode_to_hw(plane->mode),
            plane->width, plane->height, dst_x, dst_y, dst_w, dst_h, xvir, RT_TRUE,
            plane->alpha ? plane->alpha : 0xff);
}

static void vop1fb_plane_free_fb(struct rt_graphic_plane *plane)
{
    struct vop1fb *vfb = vop1fb_from_plane(plane);
    struct vop1fb_plane_priv *priv = vop1fb_plane_priv(plane);
    struct rt_device *dev = &vfb->parent.parent;

    if (plane->framebuffer)
    {
        rt_dma_free_coherent(dev, plane->framebuffer_len,
                plane->framebuffer, priv->dma_handle);
        plane->framebuffer = RT_NULL;
        plane->framebuffer_len = 0;
        plane->screen_len = 0;
        priv->dma_handle = 0;
        priv->pan_offset = 0;
    }
}

static rt_err_t vop1fb_plane_update(struct rt_graphic_plane *plane,
        struct rt_device_rect_info *rect)
{
    struct vop1fb_plane_priv *priv = vop1fb_plane_priv(plane);

    RT_UNUSED(rect);

    if (priv)
    {
        priv->enabled = RT_TRUE;
    }

    return vop1fb_plane_commit(plane, RT_TRUE);
}

static rt_err_t vop1fb_plane_fb_remap(struct rt_graphic_plane *plane,
        rt_uint32_t mode, struct rt_device_rect_info *rect)
{
    rt_err_t err;
    struct vop1fb *vfb = vop1fb_from_plane(plane);
    struct vop1fb_plane_priv *priv = vop1fb_plane_priv(plane);
    struct rt_device *dev = &vfb->parent.parent;
    rt_uint32_t bpp = rt_graphic_mode_bpp(mode);
    rt_size_t screen_len, fb_len;
    void *fb;

    if (!rect->width || !rect->height || !bpp)
    {
        return -RT_EINVAL;
    }

    vop1fb_plane_free_fb(plane);

    plane->line_length = RT_ALIGN(rect->width * bpp, 32) / 8;
    plane->bits_per_pixel = bpp;
    screen_len = plane->line_length * rect->height;

    if (plane->type == RT_GRAPHIC_PLANE_TYPE_PRIMARY)
    {
        fb_len = screen_len * 2;
    }
    else
    {
        fb_len = screen_len;
    }

    fb = rt_dma_alloc_coherent(dev, fb_len, &priv->dma_handle);

    if (!fb)
    {
        return -RT_ENOMEM;
    }

    rt_memset(fb, 0, fb_len);

    plane->framebuffer = fb;
    plane->screen_len = screen_len;
    plane->framebuffer_len = fb_len;
    plane->width = rect->width;
    plane->height = rect->height;
    plane->mode = mode;
    priv->pan_offset = 0;

    if (vfb->powered && plane->type == RT_GRAPHIC_PLANE_TYPE_PRIMARY)
    {
        err = vop1fb_plane_commit(plane, RT_TRUE);
    }
    else
    {
        err = RT_EOK;
    }

    return err;
}

static rt_err_t vop1fb_plane_fb_pan_display(struct rt_graphic_plane *plane,
        struct rt_device_rect_info *rect)
{
    struct vop1fb_plane_priv *priv = vop1fb_plane_priv(plane);

    if (rect->width != plane->width || rect->height != plane->height)
    {
        return vop1fb_plane_fb_remap(plane, plane->mode, rect);
    }

    if (plane->framebuffer_len <= plane->screen_len)
    {
        plane->x = rect->x;
        plane->y = rect->y;
        return RT_EOK;
    }

    priv->pan_offset = rect->y * plane->line_length + rect->x * (plane->bits_per_pixel / 8);

    if (priv->pan_offset + plane->screen_len > plane->framebuffer_len)
    {
        priv->pan_offset = 0;
        return -RT_EINVAL;
    }

    plane->x = rect->x;
    plane->y = rect->y;

    return vop1fb_plane_commit(plane, RT_TRUE);
}

static rt_err_t vop1fb_plane_fb_cleanup(struct rt_graphic_plane *plane)
{
    struct vop1fb *vfb = vop1fb_from_plane(plane);
    struct vop1fb_plane_priv *priv = vop1fb_plane_priv(plane);

    if (priv && priv->enabled && priv->desc)
    {
        vop1fb_win_disable(vfb, priv->desc);
        priv->enabled = RT_FALSE;
    }

    vop1fb_plane_free_fb(plane);

    return RT_EOK;
}

static rt_err_t vop1fb_plane_prop_set(struct rt_graphic_plane *plane,
        enum rt_graphic_plane_prop prop, void *value)
{
    struct vop1fb *vfb = vop1fb_from_plane(plane);
    struct vop1fb_plane_priv *priv = vop1fb_plane_priv(plane);

    if (!priv || !priv->desc)
    {
        return -RT_EINVAL;
    }

    switch (prop)
    {
    case RT_GRAPHIC_PLANE_PROP_Z:
        if (value)
        {
            plane->z = (rt_uint32_t)(rt_ubase_t)value;
        }
        return RT_EOK;

    case RT_GRAPHIC_PLANE_PROP_ALPHA:
        if (value)
        {
            plane->alpha = (rt_uint8_t)(rt_ubase_t)value;
            vop1fb_win_alpha(vfb, priv->desc, plane->alpha);
            vop1fb_cfg_done(vfb);
        }
        return RT_EOK;

    default:
        return -RT_ENOSYS;
    }
}

static const struct rt_graphic_plane_ops vop1fb_primary_ops =
{
    .update = vop1fb_plane_update,
    .fb_remap = vop1fb_plane_fb_remap,
    .fb_pan_display = vop1fb_plane_fb_pan_display,
    .fb_cleanup = vop1fb_plane_fb_cleanup,
    .prop_set = vop1fb_plane_prop_set,
};

static const struct rt_graphic_plane_ops vop1fb_overlay_ops =
{
    .update = vop1fb_plane_update,
    .fb_remap = vop1fb_plane_fb_remap,
    .fb_cleanup = vop1fb_plane_fb_cleanup,
    .prop_set = vop1fb_plane_prop_set,
};

static const struct rt_graphic_plane_ops vop1fb_cursor_ops =
{
    .update = vop1fb_plane_update,
    .fb_remap = vop1fb_plane_fb_remap,
    .fb_cleanup = vop1fb_plane_fb_cleanup,
    .prop_set = vop1fb_plane_prop_set,
};

static rt_err_t vop1fb_clk_enable(struct vop1fb *vfb)
{
    if (!vfb->clk_enabled && !rt_is_err_or_null(vfb->clks))
    {
        rt_clk_array_prepare_enable(vfb->clks);
        vfb->clk_enabled = RT_TRUE;
    }

    return RT_EOK;
}

static void vop1fb_clk_disable(struct vop1fb *vfb)
{
    if (vfb->clk_enabled && !rt_is_err_or_null(vfb->clks))
    {
        rt_clk_array_disable_unprepare(vfb->clks);
        vfb->clk_enabled = RT_FALSE;
    }
}

static rt_err_t vop1fb_dpms_switch(struct rt_graphic_device *gdev, rt_uint32_t dpms)
{
    struct vop1fb *vfb = rt_container_of(gdev, struct vop1fb, parent);
    rt_size_t i;

    switch (dpms)
    {
    case RT_GRAPHIC_DPMS_ON:
        vop1fb_clk_enable(vfb);
        vfb->powered = RT_TRUE;

        if (vfb->primary && vfb->primary->framebuffer)
        {
            vop1fb_plane_commit(vfb->primary, RT_TRUE);
        }

        for (i = 0; i < vfb->overlay_count; ++i)
        {
            struct rt_graphic_plane *plane = vfb->overlays[i];
            struct vop1fb_plane_priv *priv;

            if (!plane || !plane->framebuffer)
            {
                continue;
            }

            priv = vop1fb_plane_priv(plane);

            if (priv && priv->enabled)
            {
                vop1fb_plane_commit(plane, RT_TRUE);
            }
        }

        if (vfb->cursor && vfb->cursor->framebuffer)
        {
            struct vop1fb_plane_priv *priv = vop1fb_plane_priv(vfb->cursor);

            if (priv && priv->enabled)
            {
                vop1fb_plane_commit(vfb->cursor, RT_TRUE);
            }
        }

        rt_graphic_device_update_auto(gdev, RT_GRAPHIC_UPDATE_MS);
        break;

    case RT_GRAPHIC_DPMS_STANDBY:
    case RT_GRAPHIC_DPMS_SUSPEND:
        rt_graphic_device_update_auto(gdev, 0);

        if (vfb->primary)
        {
            vop1fb_plane_commit(vfb->primary, RT_FALSE);
        }

        for (i = 0; i < vfb->overlay_count; ++i)
        {
            if (vfb->overlays[i])
            {
                vop1fb_plane_commit(vfb->overlays[i], RT_FALSE);
            }
        }

        if (vfb->cursor)
        {
            vop1fb_plane_commit(vfb->cursor, RT_FALSE);
        }
        break;

    case RT_GRAPHIC_DPMS_OFF:
        rt_graphic_device_update_auto(gdev, 0);

        if (vfb->primary)
        {
            vop1fb_plane_commit(vfb->primary, RT_FALSE);
        }

        for (i = 0; i < vfb->overlay_count; ++i)
        {
            if (vfb->overlays[i])
            {
                vop1fb_plane_commit(vfb->overlays[i], RT_FALSE);
            }
        }

        if (vfb->cursor)
        {
            vop1fb_plane_commit(vfb->cursor, RT_FALSE);
        }

        vop1fb_clk_disable(vfb);
        vfb->powered = RT_FALSE;
        break;

    default:
        return -RT_EINVAL;
    }

    gdev->dpms = dpms;

    return RT_EOK;
}

static rt_err_t vop1fb_wait_vsync(struct rt_graphic_device *gdev)
{
    struct vop1fb *vfb = rt_container_of(gdev, struct vop1fb, parent);

    if (vfb->irq >= 0)
    {
        rt_atomic_store(&vfb->vsync, 0);

        if (rt_sem_take(&vfb->vsync_sem, rt_tick_from_millisecond(100)) == RT_EOK)
        {
            return RT_EOK;
        }
    }

    rt_thread_mdelay(16);

    return RT_EOK;
}

static const struct rt_graphic_device_ops vop1fb_ops =
{
    .dpms_switch = vop1fb_dpms_switch,
    .wait_vsync = vop1fb_wait_vsync,
};

static void vop1fb_isr(int irqno, void *param)
{
    struct vop1fb *vfb = param;

    RT_UNUSED(irqno);

    rt_atomic_store(&vfb->vsync, 1);
    rt_sem_release(&vfb->vsync_sem);
}

static void vop1fb_plane_init_fb_state(struct rt_graphic_plane *plane, rt_uint32_t mode)
{
    rt_uint32_t bpp = rt_graphic_mode_bpp(mode);

    plane->mode = mode;
    plane->bits_per_pixel = bpp;
    plane->line_length = RT_ALIGN(plane->width * bpp, 32) / 8;
    plane->screen_len = plane->line_length * plane->height;
    plane->framebuffer = RT_NULL;
    plane->framebuffer_len = 0;
}

static rt_err_t vop1fb_plane_init(struct vop1fb *vfb,
        struct rt_graphic_plane *plane,
        const struct vop1fb_win_desc *desc,
        rt_uint32_t width, rt_uint32_t height,
        rt_uint8_t type)
{
    struct vop1fb_plane_priv *priv = vop1fb_plane_priv(plane);

    priv->desc = desc;
    priv->enabled = RT_FALSE;
    priv->pan_offset = 0;
    plane->z = desc->z_order;
    plane->alpha = 0xff;

    if (type == RT_GRAPHIC_PLANE_TYPE_CURSOR)
    {
        plane->width = VOP1FB_CURSOR_W;
        plane->height = VOP1FB_CURSOR_H;
    }
    else if (type == RT_GRAPHIC_PLANE_TYPE_OVERLAY)
    {
        plane->width = width / 4;
        plane->height = height / 4;
        plane->x = plane->width;
        plane->y = plane->height;
    }
    else
    {
        plane->width = width;
        plane->height = height;
    }

    vop1fb_plane_init_fb_state(plane, RTGRAPHIC_PIXEL_FORMAT_ARGB888);

    return RT_EOK;
}

static rt_err_t vop1fb_primary_plane_create(struct vop1fb *vfb,
        rt_uint32_t width, rt_uint32_t height)
{
    rt_err_t err;
    struct rt_graphic_plane *plane;

    plane = rt_graphic_device_alloc_plane(&vfb->parent, sizeof(struct vop1fb_plane_priv),
            &vop1fb_primary_ops, vop1fb_modes, RT_ARRAY_SIZE(vop1fb_modes),
            RT_GRAPHIC_PLANE_TYPE_PRIMARY);

    if (!plane)
    {
        return -RT_ENOMEM;
    }

    if ((err = rt_graphic_device_add_plane(&vfb->parent, plane)))
    {
        rt_graphic_device_free_plane(plane);
        return err;
    }

    vfb->primary = plane;

    err = vop1fb_plane_init(vfb, plane, vfb->soc->primary, width, height,
            RT_GRAPHIC_PLANE_TYPE_PRIMARY);
    if (err)
    {
        vfb->primary = RT_NULL;
        vfb->parent.primary_plane = RT_NULL;
        rt_graphic_device_free_plane(plane);
    }

    return err;
}

static rt_err_t vop1fb_overlay_planes_create(struct vop1fb *vfb,
        rt_uint32_t width, rt_uint32_t height)
{
    rt_err_t err;
    rt_size_t i;
    struct rt_graphic_plane *plane;

    for (i = 0; i < vfb->overlay_count; ++i)
    {
        plane = rt_graphic_device_alloc_plane(&vfb->parent, sizeof(struct vop1fb_plane_priv),
                &vop1fb_overlay_ops, vop1fb_modes, RT_ARRAY_SIZE(vop1fb_modes),
                RT_GRAPHIC_PLANE_TYPE_OVERLAY);

        if (!plane)
        {
            return -RT_ENOMEM;
        }

        rt_snprintf(plane->name, sizeof(plane->name), "ovl-%s", vfb->soc->overlays[i].name);

        if ((err = rt_graphic_device_add_plane(&vfb->parent, plane)))
        {
            rt_graphic_device_free_plane(plane);
            return err;
        }

        vfb->overlays[i] = plane;

        if ((err = vop1fb_plane_init(vfb, plane, &vfb->soc->overlays[i],
                width, height, RT_GRAPHIC_PLANE_TYPE_OVERLAY)))
        {
            return err;
        }
    }

    return RT_EOK;
}

static rt_err_t vop1fb_cursor_plane_create(struct vop1fb *vfb,
        rt_uint32_t width, rt_uint32_t height)
{
    rt_err_t err;
    struct rt_graphic_plane *plane;

    plane = rt_graphic_device_alloc_plane(&vfb->parent, sizeof(struct vop1fb_plane_priv),
            &vop1fb_cursor_ops, vop1fb_modes, RT_ARRAY_SIZE(vop1fb_modes),
            RT_GRAPHIC_PLANE_TYPE_CURSOR);

    if (!plane)
    {
        return -RT_ENOMEM;
    }

    if ((err = rt_graphic_device_add_plane(&vfb->parent, plane)))
    {
        rt_graphic_device_free_plane(plane);
        return err;
    }

    vfb->cursor = plane;

    return vop1fb_plane_init(vfb, plane, vfb->soc->cursor, width, height,
            RT_GRAPHIC_PLANE_TYPE_CURSOR);
}

static const struct vop1fb_soc_data *vop1fb_soc_from_id(const struct rt_ofw_node_id *id)
{
    if (!id || !id->compatible)
    {
        return RT_NULL;
    }

    /* Lite VOP */
    if (!rt_strcmp(id->compatible, "rockchip,rk3308-vop") ||
        !rt_strcmp(id->compatible, "rockchip,rk3506-vop") ||
        !rt_strcmp(id->compatible, "rockchip,px30-vop-lit"))
    {
        return &vop1_lite_soc;
    }

    /* Big VOP */
    if (!rt_strcmp(id->compatible, "rockchip,rk3328-vop") ||
        !rt_strcmp(id->compatible, "rockchip,rk3288-vop-big") ||
        !rt_strcmp(id->compatible, "rockchip,rk3288-vop-lit") ||
        !rt_strcmp(id->compatible, "rockchip,rk3399-vop-big") ||
        !rt_strcmp(id->compatible, "rockchip,rk3399-vop-lit") ||
        !rt_strcmp(id->compatible, "rockchip,rk3368-vop") ||
        !rt_strcmp(id->compatible, "rockchip,rk3366-vop") ||
        !rt_strcmp(id->compatible, "rockchip,rk3228-vop") ||
        !rt_strcmp(id->compatible, "rockchip,rv1126-vop") ||
        !rt_strcmp(id->compatible, "rockchip,rv1126b-vop") ||
        !rt_strcmp(id->compatible, "rockchip,rv1106-vop"))
    {
        return &vop1_big_soc;
    }

    return RT_NULL;
}

static rt_err_t vop1fb_parse_display(struct vop1fb *vfb, struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;

    vfb->display_w = 1920;
    vfb->display_h = 1080;

    rt_dm_dev_prop_read_u32(dev, "rockchip,fb-width", &vfb->display_w);
    rt_dm_dev_prop_read_u32(dev, "rockchip,fb-height", &vfb->display_h);

    if (!vfb->display_w || !vfb->display_h)
    {
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_err_t vop1fb_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct vop1fb *vfb = rt_calloc(1, sizeof(*vfb));

    if (!vfb)
    {
        return -RT_ENOMEM;
    }

    vfb->soc = vop1fb_soc_from_id(pdev->id);

    if (!vfb->soc)
    {
        err = -RT_ENOSYS;
        goto _fail;
    }

    if ((err = vop1fb_parse_display(vfb, pdev)))
    {
        goto _fail;
    }

    vfb->regs = rt_ofw_iomap(dev->ofw_node, 0);

    if (!vfb->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    vfb->clks = rt_clk_get_array(dev);

    if (rt_is_err(vfb->clks))
    {
        err = rt_ptr_err(vfb->clks);
        goto _fail_unmap;
    }

    vfb->irq = rt_dm_dev_get_irq(dev, 0);

    if (vfb->irq >= 0)
    {
        rt_sem_init(&vfb->vsync_sem, "vop1-vsync", 0, RT_IPC_FLAG_FIFO);
        rt_hw_interrupt_install(vfb->irq, vop1fb_isr, vfb, "vop1");
        rt_hw_interrupt_umask(vfb->irq);
    }

    vfb->parent.ops = &vop1fb_ops;

    if ((err = vop1fb_clk_enable(vfb)))
    {
        goto _fail_irq;
    }

    vfb->powered = RT_TRUE;

    vfb->overlay_count = rt_min_t(rt_size_t, vfb->soc->overlay_count, VOP1FB_OVERLAY_MAX);

    if ((err = vop1fb_primary_plane_create(vfb, vfb->display_w, vfb->display_h)))
    {
        LOG_E("%s: create primary plane failed: %s", rt_dm_dev_get_name(dev), rt_strerror(err));
        goto _fail_clk;
    }

    rt_graphic_device_simple_edid(&vfb->parent, vfb->display_w, vfb->display_h, 60);

    if ((err = rt_graphic_device_register(&vfb->parent)))
    {
        rt_graphic_device_del_plane(&vfb->parent, vfb->primary);
        rt_graphic_device_free_plane(vfb->primary);
        vfb->primary = RT_NULL;
        goto _fail_clk;
    }

    if ((err = vop1fb_overlay_planes_create(vfb, vfb->display_w, vfb->display_h)))
    {
        LOG_E("%s: create overlay planes failed: %s", rt_dm_dev_get_name(dev), rt_strerror(err));
        goto _fail_graphic;
    }

    if ((err = vop1fb_cursor_plane_create(vfb, vfb->display_w, vfb->display_h)))
    {
        LOG_E("%s: create cursor plane failed: %s", rt_dm_dev_get_name(dev), rt_strerror(err));
        goto _fail_graphic;
    }

    vop1fb_dpms_switch(&vfb->parent, RT_GRAPHIC_DPMS_ON);

    pdev->parent.user_data = vfb;

    LOG_I("VOP1 %s (%s): %ux%u, primary=%s, %u overlays, cursor=%s",
            vfb->soc->version, pdev->id->compatible,
            vfb->display_w, vfb->display_h,
            vfb->soc->primary->name, (unsigned)vfb->overlay_count,
            vfb->soc->cursor->name);

    return RT_EOK;

_fail_graphic:
    rt_graphic_device_unregister(&vfb->parent);
_fail_clk:
    vop1fb_clk_disable(vfb);
_fail_irq:
    if (vfb->irq >= 0)
    {
        rt_hw_interrupt_mask(vfb->irq);
        rt_sem_detach(&vfb->vsync_sem);
    }

    if (!rt_is_err_or_null(vfb->clks))
    {
        rt_clk_array_put(vfb->clks);
    }

_fail_unmap:
    if (vfb->regs)
    {
        rt_iounmap(vfb->regs);
    }
_fail:
    rt_free(vfb);

    return err;
}

static rt_err_t vop1fb_remove(struct rt_platform_device *pdev)
{
    struct vop1fb *vfb = pdev->parent.user_data;

    if (!vfb)
    {
        return RT_EOK;
    }

    rt_graphic_device_unregister(&vfb->parent);

    vop1fb_dpms_switch(&vfb->parent, RT_GRAPHIC_DPMS_OFF);

    if (vfb->irq >= 0)
    {
        rt_hw_interrupt_mask(vfb->irq);
        rt_sem_detach(&vfb->vsync_sem);
    }

    if (!rt_is_err_or_null(vfb->clks))
    {
        rt_clk_array_put(vfb->clks);
    }

    rt_iounmap(vfb->regs);
    rt_free(vfb);

    pdev->parent.user_data = RT_NULL;

    return RT_EOK;
}

static const struct rt_ofw_node_id vop1_ofw_ids[] =
{
    /* Lite */
    { .compatible = "rockchip,rk3308-vop" },
    { .compatible = "rockchip,rk3506-vop" },
    { .compatible = "rockchip,px30-vop-lit" },
    /* Big */
    { .compatible = "rockchip,rk3328-vop" },
    { .compatible = "rockchip,rk3288-vop-big" },
    { .compatible = "rockchip,rk3288-vop-lit" },
    { .compatible = "rockchip,rk3399-vop-big" },
    { .compatible = "rockchip,rk3399-vop-lit" },
    { .compatible = "rockchip,rk3368-vop" },
    { .compatible = "rockchip,rk3366-vop" },
    { .compatible = "rockchip,rk3228-vop" },
    { .compatible = "rockchip,rv1126-vop" },
    { .compatible = "rockchip,rv1126b-vop" },
    { .compatible = "rockchip,rv1106-vop" },
    { /* sentinel */ }
};

static struct rt_platform_driver vop1_driver =
{
    .name = "vop1-framebuffer",
    .ids = vop1_ofw_ids,

    .probe = vop1fb_probe,
    .remove = vop1fb_remove,
};
RT_PLATFORM_DRIVER_EXPORT(vop1_driver);
