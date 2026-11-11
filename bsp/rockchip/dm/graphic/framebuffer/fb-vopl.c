/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#include "fb-vopl.h"

#include <cpuport.h>

#define DBG_TAG "fb.vopl"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define EBC_CONFIG_DONE               0x0050
#define EBC_WIN_MST2                  0x0058
#define EBC_WIN2_CTRL                 0x006c
#define EBC_VOP_SYS_CTRL              0x0100
#define EBC_VOP_DSP_CTRL0             0x0104
#define EBC_VOP_DSP_CTRL1             0x0108
#define EBC_DSP_HTOTAL_HS_END         0x0110
#define EBC_DSP_HACT_ST_END           0x0114
#define EBC_DSP_VTOTAL_VS_END         0x0118
#define EBC_DSP_VACT_ST_END           0x011c
#define EBC_VOP_WIN_VIR               0x0150
#define EBC_VOP_WIN_DSP_INFO          0x0158
#define EBC_VOP_WIN_DSP_ST            0x015c

#define VOPLFB_OUT_MODE_P888          0

struct voplfb_plane_priv
{
    rt_ubase_t dma_handle;
    rt_uint32_t pan_offset;
    rt_bool_t enabled;
};

static rt_uint32_t voplfb_modes[] =
{
    RTGRAPHIC_PIXEL_FORMAT_ARGB888,
    RTGRAPHIC_PIXEL_FORMAT_RGB888,
    RTGRAPHIC_PIXEL_FORMAT_RGB565,
};

rt_uint32_t voplfb_mode_to_hw(rt_uint32_t mode)
{
    switch (mode)
    {
    case RTGRAPHIC_PIXEL_FORMAT_ARGB888:
    case RTGRAPHIC_PIXEL_FORMAT_ABGR888:
        return VOPLFB_FMT_ARGB8888;
    case RTGRAPHIC_PIXEL_FORMAT_RGB888:
    case RTGRAPHIC_PIXEL_FORMAT_BGR888:
        return VOPLFB_FMT_RGB888;
    case RTGRAPHIC_PIXEL_FORMAT_RGB565:
    case RTGRAPHIC_PIXEL_FORMAT_BGR565:
        return VOPLFB_FMT_RGB565;
    default:
        return VOPLFB_FMT_ARGB8888;
    }
}

rt_uint32_t voplfb_hw_to_bpp(rt_uint32_t hw_fmt)
{
    switch (hw_fmt)
    {
    case VOPLFB_FMT_RGB565:
        return 16;
    case VOPLFB_FMT_RGB888:
        return 24;
    default:
        return 32;
    }
}

static struct voplfb *voplfb_from_plane(struct rt_graphic_plane *plane)
{
    return rt_container_of(plane->graphic, struct voplfb, parent);
}

static struct voplfb_plane_priv *voplfb_plane_priv(struct rt_graphic_plane *plane)
{
    return (struct voplfb_plane_priv *)plane->priv;
}

rt_inline void voplfb_reg_write(struct voplfb *vfb, rt_uint32_t offset, rt_uint32_t v)
{
    HWREG32((rt_uint8_t *)vfb->regs + offset) = v;
}

rt_inline void voplfb_mask_write(struct voplfb *vfb, rt_uint32_t offset,
        rt_uint32_t mask, rt_uint32_t shift, rt_uint32_t v)
{
    rt_uint32_t cached = HWREG32((rt_uint8_t *)vfb->regs + offset);
    rt_uint32_t newv = (cached & ~(mask << shift)) | ((v & mask) << shift);

    voplfb_reg_write(vfb, offset, newv);
}

static void voplfb_cfg_done(struct voplfb *vfb)
{
    voplfb_reg_write(vfb, EBC_CONFIG_DONE, 1);
}

static rt_uint32_t voplfb_xvir(rt_uint32_t width, rt_uint32_t bpp)
{
    return RT_ALIGN(width * bpp, 32) >> 5;
}

static rt_err_t voplfb_output_mode_set(struct voplfb *vfb, const struct display_timing *tim)
{
    rt_uint32_t hact_st, hact_end, vact_st, vact_end;

    if (!vfb || !tim)
    {
        return -RT_EINVAL;
    }

    hact_st = tim->hfront_porch + tim->hsync_len;
    hact_end = hact_st + tim->hactive;
    vact_st = tim->vfront_porch + tim->vsync_len;
    vact_end = vact_st + tim->vactive;

    voplfb_reg_write(vfb, EBC_DSP_HTOTAL_HS_END, (tim->htotal << 16) | tim->hsync_len);
    voplfb_reg_write(vfb, EBC_DSP_HACT_ST_END, (hact_st << 16) | hact_end);
    voplfb_reg_write(vfb, EBC_DSP_VTOTAL_VS_END, (tim->vtotal << 16) | tim->vsync_len);
    voplfb_reg_write(vfb, EBC_DSP_VACT_ST_END, (vact_st << 16) | vact_end);

    voplfb_mask_write(vfb, EBC_VOP_DSP_CTRL1, 0xf, 16, VOPLFB_OUT_MODE_P888);
    voplfb_mask_write(vfb, EBC_VOP_DSP_CTRL0, 1, 15, 0);
    voplfb_mask_write(vfb, EBC_VOP_DSP_CTRL0, 1, 31, 1);
    voplfb_mask_write(vfb, EBC_VOP_SYS_CTRL, 1, 0, 1);
    voplfb_mask_write(vfb, EBC_VOP_SYS_CTRL, 1, 8, 1);

    vfb->display_w = tim->hactive;
    vfb->display_h = tim->vactive;

    return RT_EOK;
}

static rt_err_t voplfb_output_enable(struct voplfb *vfb, rt_bool_t enable)
{
    voplfb_mask_write(vfb, EBC_VOP_DSP_CTRL0, 1, 15, enable ? 0 : 1);
    voplfb_cfg_done(vfb);

    return RT_EOK;
}

static rt_err_t voplfb_plane_commit(struct voplfb *vfb, struct rt_graphic_plane *plane,
        rt_bool_t enable)
{
    struct voplfb_plane_priv *priv = voplfb_plane_priv(plane);
    rt_ubase_t dma;
    rt_uint32_t xvir, act_info, dsp_info, dsp_st;

    if (!priv || !plane)
    {
        return -RT_EINVAL;
    }

    if (!enable || !plane->framebuffer)
    {
        voplfb_mask_write(vfb, EBC_WIN2_CTRL, 1, 0, 0);
        voplfb_cfg_done(vfb);
        priv->enabled = RT_FALSE;
        return RT_EOK;
    }

    dma = priv->dma_handle + priv->pan_offset;
    xvir = voplfb_xvir(plane->width, plane->bits_per_pixel);
    act_info = ((plane->height - 1) << 16) | ((plane->width - 1) & 0xffff);
    dsp_info = act_info;
    dsp_st = (plane->y << 16) | (plane->x & 0xffff);

    voplfb_mask_write(vfb, EBC_VOP_SYS_CTRL, 0x3, 4, voplfb_mode_to_hw(plane->mode));
    voplfb_reg_write(vfb, EBC_VOP_WIN_VIR, xvir);
    voplfb_reg_write(vfb, EBC_WIN_MST2, (rt_uint32_t)dma);
    voplfb_reg_write(vfb, EBC_VOP_WIN_DSP_INFO, dsp_info);
    voplfb_reg_write(vfb, EBC_VOP_WIN_DSP_ST, dsp_st);
    voplfb_mask_write(vfb, EBC_WIN2_CTRL, 1, 0, 1);
    voplfb_cfg_done(vfb);

    priv->enabled = RT_TRUE;

    return RT_EOK;
}

static void voplfb_plane_free_fb(struct rt_graphic_plane *plane)
{
    struct voplfb *vfb = voplfb_from_plane(plane);
    struct voplfb_plane_priv *priv = voplfb_plane_priv(plane);
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

static rt_err_t voplfb_plane_update(struct rt_graphic_plane *plane,
        struct rt_device_rect_info *rect)
{
    struct voplfb *vfb = voplfb_from_plane(plane);
    struct voplfb_plane_priv *priv = voplfb_plane_priv(plane);

    RT_UNUSED(rect);

    if (priv)
    {
        priv->enabled = RT_TRUE;
    }

    return voplfb_plane_commit(vfb, plane, RT_TRUE);
}

static rt_err_t voplfb_plane_fb_remap(struct rt_graphic_plane *plane,
        rt_uint32_t mode, struct rt_device_rect_info *rect)
{
    rt_err_t err;
    struct voplfb *vfb = voplfb_from_plane(plane);
    struct voplfb_plane_priv *priv = voplfb_plane_priv(plane);
    struct rt_device *dev = &vfb->parent.parent;
    rt_uint32_t bpp = rt_graphic_mode_bpp(mode);
    rt_size_t screen_len, fb_len;
    void *fb;

    if (!rect->width || !rect->height || !bpp)
    {
        return -RT_EINVAL;
    }

    voplfb_plane_free_fb(plane);

    plane->line_length = RT_ALIGN(rect->width * bpp, 32) / 8;
    plane->bits_per_pixel = bpp;
    screen_len = plane->line_length * rect->height;
    fb_len = screen_len * 2;

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

    if (vfb->powered)
    {
        err = voplfb_plane_commit(vfb, plane, RT_TRUE);
    }
    else
    {
        err = RT_EOK;
    }

    return err;
}

static rt_err_t voplfb_plane_fb_pan_display(struct rt_graphic_plane *plane,
        struct rt_device_rect_info *rect)
{
    struct voplfb *vfb = voplfb_from_plane(plane);
    struct voplfb_plane_priv *priv = voplfb_plane_priv(plane);

    if (rect->width != plane->width || rect->height != plane->height)
    {
        return voplfb_plane_fb_remap(plane, plane->mode, rect);
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

    return voplfb_plane_commit(vfb, plane, RT_TRUE);
}

static rt_err_t voplfb_plane_fb_cleanup(struct rt_graphic_plane *plane)
{
    struct voplfb *vfb = voplfb_from_plane(plane);
    struct voplfb_plane_priv *priv = voplfb_plane_priv(plane);

    if (priv && priv->enabled)
    {
        voplfb_plane_commit(vfb, plane, RT_FALSE);
    }

    voplfb_plane_free_fb(plane);

    return RT_EOK;
}

static const struct rt_graphic_plane_ops voplfb_primary_ops =
{
    .update = voplfb_plane_update,
    .fb_remap = voplfb_plane_fb_remap,
    .fb_pan_display = voplfb_plane_fb_pan_display,
    .fb_cleanup = voplfb_plane_fb_cleanup,
};

static rt_err_t voplfb_clk_enable(struct voplfb *vfb)
{
    if (!vfb->clk_enabled && !rt_is_err_or_null(vfb->clks))
    {
        rt_clk_array_prepare_enable(vfb->clks);
        vfb->clk_enabled = RT_TRUE;
    }

    return RT_EOK;
}

static void voplfb_clk_disable(struct voplfb *vfb)
{
    if (vfb->clk_enabled && !rt_is_err_or_null(vfb->clks))
    {
        rt_clk_array_disable_unprepare(vfb->clks);
        vfb->clk_enabled = RT_FALSE;
    }
}

static rt_err_t voplfb_dpms_switch(struct rt_graphic_device *gdev, rt_uint32_t dpms)
{
    struct voplfb *vfb = rt_container_of(gdev, struct voplfb, parent);

    switch (dpms)
    {
    case RT_GRAPHIC_DPMS_ON:
        voplfb_clk_enable(vfb);
        vfb->powered = RT_TRUE;

        if (vfb->primary && vfb->primary->framebuffer)
        {
            voplfb_plane_commit(vfb, vfb->primary, RT_TRUE);
        }

        rt_graphic_device_update_auto(gdev, RT_GRAPHIC_UPDATE_MS);
        break;

    case RT_GRAPHIC_DPMS_STANDBY:
    case RT_GRAPHIC_DPMS_SUSPEND:
        rt_graphic_device_update_auto(gdev, 0);

        if (vfb->primary)
        {
            voplfb_plane_commit(vfb, vfb->primary, RT_FALSE);
        }
        break;

    case RT_GRAPHIC_DPMS_OFF:
        rt_graphic_device_update_auto(gdev, 0);

        if (vfb->primary)
        {
            voplfb_plane_commit(vfb, vfb->primary, RT_FALSE);
        }

        voplfb_clk_disable(vfb);
        vfb->powered = RT_FALSE;
        break;

    default:
        return -RT_EINVAL;
    }

    gdev->dpms = dpms;

    return RT_EOK;
}

static rt_err_t voplfb_wait_vsync(struct rt_graphic_device *gdev)
{
    struct voplfb *vfb = rt_container_of(gdev, struct voplfb, parent);

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

static void voplfb_isr(int irq, void *param)
{
    struct voplfb *vfb = param;

    RT_UNUSED(irq);

    if (rt_atomic_load(&vfb->vsync) == 0)
    {
        rt_atomic_store(&vfb->vsync, 1);
        rt_sem_release(&vfb->vsync_sem);
    }
}

static const struct rt_graphic_device_ops voplfb_ops =
{
    .dpms_switch = voplfb_dpms_switch,
    .wait_vsync = voplfb_wait_vsync,
};

static rt_err_t voplfb_crtc_mode_set(void *priv, const struct display_route *route,
        const struct display_timing *tim)
{
    struct voplfb *vfb = priv;

    RT_UNUSED(route);

    if (!vfb)
    {
        return -RT_EINVAL;
    }

    vfb->output_tim = *tim;
    vfb->output_tim_valid = RT_TRUE;

    return voplfb_output_mode_set(vfb, tim);
}

static rt_err_t voplfb_crtc_enable(void *priv, rt_uint32_t vp_id, rt_bool_t enable)
{
    struct voplfb *vfb = priv;

    RT_UNUSED(vp_id);

    return voplfb_output_enable(vfb, enable);
}

static const struct rockchip_crtc_ops voplfb_crtc_ops =
{
    .mode_set = voplfb_crtc_mode_set,
    .enable = voplfb_crtc_enable,
};

static void voplfb_plane_init_fb_state(struct rt_graphic_plane *plane, rt_uint32_t mode)
{
    rt_uint32_t bpp = rt_graphic_mode_bpp(mode);

    plane->mode = mode;
    plane->bits_per_pixel = bpp;
    plane->line_length = RT_ALIGN(plane->width * bpp, 32) / 8;
    plane->screen_len = plane->line_length * plane->height;
    plane->framebuffer = RT_NULL;
    plane->framebuffer_len = 0;
}

static rt_err_t voplfb_plane_init(struct voplfb *vfb, struct rt_graphic_plane *plane,
        rt_uint32_t width, rt_uint32_t height)
{
    struct voplfb_plane_priv *priv = voplfb_plane_priv(plane);

    priv->enabled = RT_FALSE;
    priv->pan_offset = 0;
    plane->z = 1;
    plane->alpha = 0xff;
    plane->x = 0;
    plane->y = 0;
    plane->width = width;
    plane->height = height;

    voplfb_plane_init_fb_state(plane, RTGRAPHIC_PIXEL_FORMAT_ARGB888);

    return RT_EOK;
}

static rt_err_t voplfb_planes_create(struct voplfb *vfb, rt_uint32_t width, rt_uint32_t height)
{
    rt_err_t err;
    struct rt_graphic_plane *plane;

    plane = rt_graphic_device_alloc_plane(&vfb->parent, sizeof(struct voplfb_plane_priv),
            &voplfb_primary_ops, voplfb_modes, RT_ARRAY_SIZE(voplfb_modes),
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

    return voplfb_plane_init(vfb, plane, width, height);
}

static rt_err_t voplfb_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    struct rt_device *dev = &pdev->parent;
    struct rt_ofw_node *np = dev->ofw_node;
    struct voplfb *vfb = rt_calloc(1, sizeof(*vfb));

    if (!vfb)
    {
        return -RT_ENOMEM;
    }

    vfb->display_w = 1920;
    vfb->display_h = 1080;
    rt_dm_dev_prop_read_u32(dev, "rockchip,fb-width", &vfb->display_w);
    rt_dm_dev_prop_read_u32(dev, "rockchip,fb-height", &vfb->display_h);

    if (!vfb->display_w || !vfb->display_h)
    {
        err = -RT_EINVAL;
        goto _fail;
    }

    vfb->regs = rt_ofw_iomap(np, 0);

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
        rt_sem_init(&vfb->vsync_sem, "vopl-vsync", 0, RT_IPC_FLAG_FIFO);
        rt_hw_interrupt_install(vfb->irq, voplfb_isr, vfb, "vopl");
        rt_hw_interrupt_umask(vfb->irq);
    }

    vfb->parent.ops = &voplfb_ops;

    if ((err = voplfb_clk_enable(vfb)))
    {
        goto _fail_irq;
    }

    vfb->powered = RT_TRUE;

    rockchip_display_register_crtc(np, &voplfb_crtc_ops, vfb);

    if ((err = voplfb_planes_create(vfb, vfb->display_w, vfb->display_h)))
    {
        goto _fail_clk;
    }

    rt_graphic_device_simple_edid(&vfb->parent, vfb->display_w, vfb->display_h, 60);

    if ((err = rt_graphic_device_register(&vfb->parent)))
    {
        goto _fail_clk;
    }

    voplfb_dpms_switch(&vfb->parent, RT_GRAPHIC_DPMS_ON);

    pdev->parent.user_data = vfb;

    LOG_I("VOPL rk3576: %ux%u", vfb->display_w, vfb->display_h);

    return RT_EOK;

_fail_clk:
    voplfb_clk_disable(vfb);
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
    rt_iounmap(vfb->regs);
_fail:
    rt_free(vfb);

    return err;
}

static const struct rt_ofw_node_id voplfb_ids[] =
{
    { .compatible = "rockchip,rk3576-vop-lit" },
    { /* sentinel */ }
};

static struct rt_platform_driver voplfb_driver =
{
    .name = "vopl-framebuffer",
    .ids = voplfb_ids,
    .probe = voplfb_probe,
};
RT_PLATFORM_DRIVER_EXPORT(voplfb_driver);
