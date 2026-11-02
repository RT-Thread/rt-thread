/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#include "fb-vop2.h"
#include "fb-vop2-vp.h"

#include <cpuport.h>

#define DBG_TAG "fb.vop2"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

static enum vop2fb_output_if vop2fb_output_from_connector(
        struct rt_ofw_node *connector_np);

/* -------------------------------------------------------------------------- */
/* SoC window maps                                                            */
/* -------------------------------------------------------------------------- */

static const struct vop2fb_win_desc rk3568_primary =
{
    .name = "Smart0",
    .type = VOP2FB_LAYER_SMART,
    .base_offset = VOP2_SMART0_BASE,
    .layer_sel_id = 3,
    .win_sel_port_offset = 6,
    .z_order = 2,
    .plane_id = RK_PLANE_SMART0,
    .mix_alpha_reg = 0x658,
};

static const struct vop2fb_win_desc rk3568_cursor =
{
    .name = "Smart1",
    .type = VOP2FB_LAYER_SMART,
    .base_offset = VOP2_SMART0_BASE + VOP2_SMART_STRIDE,
    .layer_sel_id = 7,
    .win_sel_port_offset = 7,
    .z_order = 5,
    .plane_id = RK_PLANE_SMART1,
};

static const struct vop2fb_win_desc rk3568_overlays[] =
{
    {
        .name = "Cluster0",
        .type = VOP2FB_LAYER_CLUSTER,
        .base_offset = VOP2_CLUSTER0_BASE,
        .layer_sel_id = 0,
        .win_sel_port_offset = 0,
        .z_order = 0,
        .plane_id = RK_PLANE_CLUSTER0,
        .mix_alpha_reg = 0x618,
    },
    {
        .name = "Esmart1",
        .type = VOP2FB_LAYER_ESMART,
        .base_offset = VOP2_ESMART0_BASE + VOP2_ESMART_STRIDE,
        .layer_sel_id = 6,
        .win_sel_port_offset = 5,
        .z_order = 3,
        .plane_id = RK_PLANE_ESMART1,
        .mix_alpha_reg = 0x660,
    },
    {
        .name = "Esmart0",
        .type = VOP2FB_LAYER_ESMART,
        .base_offset = VOP2_ESMART0_BASE,
        .layer_sel_id = 2,
        .win_sel_port_offset = 4,
        .z_order = 4,
        .plane_id = RK_PLANE_ESMART0,
        .mix_alpha_reg = 0x658,
    },
};

/*
 * Cluster1 is not exposed as a userspace plane in the compact RK3568
 * framebuffer setup, but it still occupies one slot in the shared overlay
 * mixer.  Keep a routing-only descriptor so multi-VP layer selection matches
 * the hardware window order used by Linux/U-Boot.
 */
static const struct vop2fb_win_desc rk3568_cluster1_route =
{
    .name = "Cluster1",
    .type = VOP2FB_LAYER_CLUSTER,
    .base_offset = VOP2_CLUSTER0_BASE + VOP2_CLUSTER_STRIDE,
    .layer_sel_id = 1,
    .win_sel_port_offset = 1,
    .plane_id = -1,
};

static const struct vop2fb_win_desc *const rk3568_route_windows[] =
{
    &rk3568_overlays[0],         /* Cluster0 */
    &rk3568_overlays[2],         /* Esmart0 */
    &rk3568_primary,             /* Smart0 */
    &rk3568_cluster1_route,      /* Cluster1 */
    &rk3568_overlays[1],         /* Esmart1 */
    &rk3568_cursor,              /* Smart1 */
};

static const struct vop2fb_win_desc rk3528_primary =
{
    .name = "Esmart0",
    .type = VOP2FB_LAYER_ESMART,
    .base_offset = VOP2_ESMART0_BASE,
    .z_order = 2,
    .axi_yrgb_id = 0x06,
    .axi_uv_id = 0x07,
};

static const struct vop2fb_win_desc rk3528_cursor =
{
    .name = "Esmart3",
    .type = VOP2FB_LAYER_ESMART,
    .base_offset = VOP2_ESMART0_BASE + VOP2_ESMART_STRIDE * 3,
    .z_order = 5,
    .axi_yrgb_id = 0x0c,
    .axi_uv_id = 0x0d,
};

static const struct vop2fb_win_desc rk3528_overlays[] =
{
    {
        .name = "Cluster0",
        .type = VOP2FB_LAYER_CLUSTER,
        .base_offset = VOP2_CLUSTER0_BASE,
        .z_order = 0,
        .axi_yrgb_id = 0x02,
        .axi_uv_id = 0x03,
    },
    {
        .name = "Esmart1",
        .type = VOP2FB_LAYER_ESMART,
        .base_offset = VOP2_ESMART0_BASE + VOP2_ESMART_STRIDE,
        .z_order = 3,
        .axi_yrgb_id = 0x08,
        .axi_uv_id = 0x09,
    },
    {
        .name = "Esmart2",
        .type = VOP2FB_LAYER_ESMART,
        .base_offset = VOP2_ESMART0_BASE + VOP2_ESMART_STRIDE * 2,
        .z_order = 4,
        .axi_yrgb_id = 0x0a,
        .axi_uv_id = 0x0b,
    },
};

static const struct vop2fb_win_desc rk3562_primary =
{
    .name = "Esmart0",
    .type = VOP2FB_LAYER_ESMART,
    .base_offset = VOP2_ESMART0_BASE,
    .z_order = 2,
    .axi_yrgb_id = 0x02,
    .axi_uv_id = 0x03,
};

static const struct vop2fb_win_desc rk3562_cursor =
{
    .name = "Esmart3",
    .type = VOP2FB_LAYER_ESMART,
    .base_offset = VOP2_ESMART0_BASE + VOP2_ESMART_STRIDE * 3,
    .z_order = 5,
    .axi_yrgb_id = 0x08,
    .axi_uv_id = 0x09,
};

static const struct vop2fb_win_desc rk3562_overlays[] =
{
    {
        .name = "Esmart1",
        .type = VOP2FB_LAYER_ESMART,
        .base_offset = VOP2_ESMART0_BASE + VOP2_ESMART_STRIDE,
        .z_order = 3,
        .axi_yrgb_id = 0x04,
        .axi_uv_id = 0x05,
    },
    {
        .name = "Esmart2",
        .type = VOP2FB_LAYER_ESMART,
        .base_offset = VOP2_ESMART0_BASE + VOP2_ESMART_STRIDE * 2,
        .z_order = 4,
        .axi_yrgb_id = 0x06,
        .axi_uv_id = 0x07,
    },
};

static const struct vop2fb_win_desc rk3588_primary =
{
    .name = "Esmart0",
    .type = VOP2FB_LAYER_ESMART,
    .base_offset = VOP2_ESMART0_BASE,
    .z_order = 4,
    .axi_yrgb_id = 0x10,
    .axi_uv_id = 0x11,
};

static const struct vop2fb_win_desc rk3588_cursor =
{
    .name = "Esmart3",
    .type = VOP2FB_LAYER_ESMART,
    .base_offset = VOP2_ESMART0_BASE + VOP2_ESMART_STRIDE * 3,
    .z_order = 7,
    .axi_yrgb_id = 0x16,
    .axi_uv_id = 0x17,
};

static const struct vop2fb_win_desc rk3588_overlays[] =
{
    {
        .name = "Cluster0",
        .type = VOP2FB_LAYER_CLUSTER,
        .base_offset = VOP2_CLUSTER0_BASE,
        .z_order = 0,
        .axi_yrgb_id = 0x02,
        .axi_uv_id = 0x03,
    },
    {
        .name = "Cluster1",
        .type = VOP2FB_LAYER_CLUSTER,
        .base_offset = VOP2_CLUSTER0_BASE + VOP2_CLUSTER_STRIDE,
        .z_order = 1,
        .axi_yrgb_id = 0x04,
        .axi_uv_id = 0x05,
    },
    {
        .name = "Esmart1",
        .type = VOP2FB_LAYER_ESMART,
        .base_offset = VOP2_ESMART0_BASE + VOP2_ESMART_STRIDE,
        .z_order = 5,
        .axi_yrgb_id = 0x12,
        .axi_uv_id = 0x13,
    },
    {
        .name = "Esmart2",
        .type = VOP2FB_LAYER_ESMART,
        .base_offset = VOP2_ESMART0_BASE + VOP2_ESMART_STRIDE * 2,
        .z_order = 6,
        .axi_yrgb_id = 0x14,
        .axi_uv_id = 0x15,
    },
};

/* RK3576 reuses RK3588-class layer map (same register layout). */
static const struct vop2fb_win_desc rk3576_primary =
{
    .name = "Esmart0",
    .type = VOP2FB_LAYER_ESMART,
    .base_offset = VOP2_ESMART0_BASE,
    .z_order = 4,
    .axi_yrgb_id = 0x10,
    .axi_uv_id = 0x11,
};

static const struct vop2fb_win_desc rk3576_cursor =
{
    .name = "Esmart3",
    .type = VOP2FB_LAYER_ESMART,
    .base_offset = VOP2_ESMART0_BASE + VOP2_ESMART_STRIDE * 3,
    .z_order = 7,
    .axi_yrgb_id = 0x0c,
    .axi_uv_id = 0x0d,
};

static const struct vop2fb_win_desc rk3576_overlays[] =
{
    {
        .name = "Cluster0",
        .type = VOP2FB_LAYER_CLUSTER,
        .base_offset = VOP2_CLUSTER0_BASE,
        .z_order = 0,
        .axi_yrgb_id = 0x0a,
        .axi_uv_id = 0x0b,
    },
    {
        .name = "Cluster1",
        .type = VOP2FB_LAYER_CLUSTER,
        .base_offset = VOP2_CLUSTER0_BASE + VOP2_CLUSTER_STRIDE,
        .z_order = 1,
        .axi_yrgb_id = 0x0e,
        .axi_uv_id = 0x0f,
    },
    {
        .name = "Esmart1",
        .type = VOP2FB_LAYER_ESMART,
        .base_offset = VOP2_ESMART0_BASE + VOP2_ESMART_STRIDE,
        .z_order = 5,
        .axi_yrgb_id = 0x12,
        .axi_uv_id = 0x13,
    },
    {
        .name = "Esmart2",
        .type = VOP2FB_LAYER_ESMART,
        .base_offset = VOP2_ESMART0_BASE + VOP2_ESMART_STRIDE * 2,
        .z_order = 6,
        .axi_yrgb_id = 0x0a,
        .axi_uv_id = 0x0b,
        .axi_id = 1,
    },
};

static const struct vop2fb_soc_data rk3568_soc_data =
{
    .soc = VOP2FB_SOC_RK3568,
    .version = "rk3568",
    .reg_size = 0x3000,
    .regbak_words = 0x3000 / 4,
    .primary = &rk3568_primary,
    .cursor = &rk3568_cursor,
    .overlays = rk3568_overlays,
    /*
     * Esmart0/Esmart1 are reserved as primary scanout windows for additional
     * VPs. Cluster0 remains available as the first framebuffer's overlay.
     */
    .overlay_count = 1,
    .route_windows = rk3568_route_windows,
    .route_window_count = RT_ARRAY_SIZE(rk3568_route_windows),
    .axi_config = RT_FALSE,
    .vp_count = 3,
};

static const struct vop2fb_soc_data rk3588_soc_data =
{
    .soc = VOP2FB_SOC_RK3588,
    .version = "rk3588",
    .reg_size = 0x4200,
    .regbak_words = 0x4200 / 4,
    .primary = &rk3588_primary,
    .cursor = &rk3588_cursor,
    .overlays = rk3588_overlays,
    .overlay_count = RT_ARRAY_SIZE(rk3588_overlays),
    .axi_config = RT_TRUE,
    .vp_count = 4,
};

static const struct vop2fb_soc_data rk3528_soc_data =
{
    .soc = VOP2FB_SOC_RK3528,
    .version = "rk3528",
    .reg_size = 0x3000,
    .regbak_words = 0x3000 / 4,
    .primary = &rk3528_primary,
    .cursor = &rk3528_cursor,
    .overlays = rk3528_overlays,
    .overlay_count = RT_ARRAY_SIZE(rk3528_overlays),
    .axi_config = RT_TRUE,
    .vp_count = 2,
};

static const struct vop2fb_soc_data rk3562_soc_data =
{
    .soc = VOP2FB_SOC_RK3562,
    .version = "rk3562",
    .reg_size = 0x2000,
    .regbak_words = 0x2000 / 4,
    .primary = &rk3562_primary,
    .cursor = &rk3562_cursor,
    .overlays = rk3562_overlays,
    .overlay_count = RT_ARRAY_SIZE(rk3562_overlays),
    .axi_config = RT_TRUE,
    .vp_count = 1,
};

static const struct vop2fb_soc_data rk3576_soc_data =
{
    .soc = VOP2FB_SOC_RK3576,
    .version = "rk3576",
    .reg_size = 0x3000,
    .regbak_words = 0x3000 / 4,
    .primary = &rk3576_primary,
    .cursor = &rk3576_cursor,
    .overlays = rk3576_overlays,
    .overlay_count = RT_ARRAY_SIZE(rk3576_overlays),
    .axi_config = RT_TRUE,
    .irq_by_vp = RT_TRUE,
    .vp_count = 3,
};

static rt_uint32_t vop2fb_modes[] =
{
    RTGRAPHIC_PIXEL_FORMAT_ARGB888,
    RTGRAPHIC_PIXEL_FORMAT_RGB888,
    RTGRAPHIC_PIXEL_FORMAT_RGB565,
};

/* -------------------------------------------------------------------------- */
/* Helpers                                                                    */
/* -------------------------------------------------------------------------- */

rt_uint32_t vop2fb_mode_to_hw(rt_uint32_t mode)
{
    switch (mode)
    {
    case RTGRAPHIC_PIXEL_FORMAT_ARGB888:
    case RTGRAPHIC_PIXEL_FORMAT_ABGR888:
        return VOP2FB_FMT_ARGB8888;
    case RTGRAPHIC_PIXEL_FORMAT_RGB888:
    case RTGRAPHIC_PIXEL_FORMAT_BGR888:
        return VOP2FB_FMT_RGB888;
    case RTGRAPHIC_PIXEL_FORMAT_RGB565:
    case RTGRAPHIC_PIXEL_FORMAT_BGR565:
        return VOP2FB_FMT_RGB565;
    default:
        return VOP2FB_FMT_ARGB8888;
    }
}

rt_uint32_t vop2fb_hw_to_bpp(rt_uint32_t hw_fmt)
{
    switch (hw_fmt)
    {
    case VOP2FB_FMT_RGB565:
        return 16;
    case VOP2FB_FMT_RGB888:
        return 24;
    default:
        return 32;
    }
}

static struct vop2fb *vop2fb_from_plane(struct rt_graphic_plane *plane)
{
    struct vop2fb_plane_priv *priv;

    if (!plane)
    {
        return RT_NULL;
    }

    priv = (struct vop2fb_plane_priv *)plane->priv;

    return priv->vfb;
}

static struct vop2fb_plane_priv *vop2fb_plane_priv(struct rt_graphic_plane *plane)
{
    return (struct vop2fb_plane_priv *)plane->priv;
}

static struct vop2fb_vp_state *vop2fb_output_from_graphic(
        struct rt_graphic_device *gdev)
{
    if (!gdev)
    {
        return RT_NULL;
    }

    return (struct vop2fb_vp_state *)gdev->parent.user_data;
}

static rt_uint32_t vop2fb_xvir(rt_uint32_t line_length)
{
    /*
     * Rockchip VOP2 VIR registers use a 32-bit word stride, not the older
     * VOP-style 32-byte unit. Linux/U-Boot program this as pitch / 4.
     */
    return line_length >> 2;
}

static rt_bool_t vop2fb_mode_rb_swap(rt_uint32_t mode)
{
    switch (mode)
    {
    case RTGRAPHIC_PIXEL_FORMAT_ABGR888:
    case RTGRAPHIC_PIXEL_FORMAT_BGR888:
    case RTGRAPHIC_PIXEL_FORMAT_BGR565:
        return RT_TRUE;
    default:
        return RT_FALSE;
    }
}

static rt_bool_t vop2fb_hw_fmt_dither_up(rt_uint32_t hw_fmt)
{
    return hw_fmt == VOP2FB_FMT_RGB565;
}

static void vop2fb_regsbak_sync(struct vop2fb *vfb)
{
    rt_size_t i;
    volatile rt_uint32_t *regs;

    if (!vfb || !vfb->regs || !vfb->regsbak || !vfb->soc)
    {
        return;
    }

    regs = (volatile rt_uint32_t *)vfb->regs;

    for (i = 0; i < vfb->soc->regbak_words; ++i)
    {
        vfb->regsbak[i] = regs[i];
    }
}

static void vop2fb_rk3568_smart_prepare(struct vop2fb *vfb,
        const struct vop2fb_win_desc *desc, rt_uint32_t hw_fmt, rt_uint32_t mode)
{
    rt_uint32_t base;

    if (!vfb || !vfb->soc || !desc || vfb->soc->soc != VOP2FB_SOC_RK3568)
    {
        return;
    }

    if (desc->type != VOP2FB_LAYER_SMART && desc->type != VOP2FB_LAYER_ESMART)
    {
        return;
    }

    base = desc->base_offset;

    /*
     * Force Smart/Esmart into a known-good 1:1 RGB scanout state.
     * The RT bring-up path previously only touched format/addr/size, so any
     * stale boot ROM/U-Boot scale or swap bits could keep HDMI black even
     * though timing and DMA were already alive.
     */
    vop2fb_mask_write(vfb, base + VOP2_ESMART_CTRL0,
            1, VOP2_RGB2YUV_EN_SHIFT, 0);
    vop2fb_mask_write(vfb, base + VOP2_ESMART_CTRL0,
            VOP2_CSC_MODE_MASK, VOP2_CSC_MODE_SHIFT, 0);
    vop2fb_mask_write(vfb, base + VOP2_ESMART_CTRL1,
            1, VOP2_YMIRROR_EN_SHIFT, 0);
    vop2fb_mask_write(vfb, base + VOP2_REGION0_CTRL,
            1, VOP2_REGION0_DITHER_UP_EN_SHIFT,
            vop2fb_hw_fmt_dither_up(hw_fmt) ? 1 : 0);
    vop2fb_mask_write(vfb, base + VOP2_REGION0_CTRL,
            1, VOP2_REGION0_RB_SWAP_SHIFT,
            vop2fb_mode_rb_swap(mode) ? 1 : 0);
    vop2fb_mask_write(vfb, base + VOP2_REGION0_CTRL,
            1, VOP2_YRGB_GT2_SHIFT, 0);
    vop2fb_mask_write(vfb, base + VOP2_REGION0_CTRL,
            1, VOP2_YRGB_GT4_SHIFT, 0);
}

static void vop2fb_rk3568_dump_win_regs(struct vop2fb *vfb,
        const struct vop2fb_win_desc *desc)
{
    rt_uint32_t base;

    if (!vfb || !vfb->regs || !vfb->soc || !desc || vfb->soc->soc != VOP2FB_SOC_RK3568)
    {
        return;
    }

    if (desc->type != VOP2FB_LAYER_SMART && desc->type != VOP2FB_LAYER_ESMART)
    {
        return;
    }

    base = desc->base_offset;
    RT_UNUSED(base);

    LOG_D("%s regs: CTRL0=0x%08x CTRL1=0x%08x R0_CTRL=0x%08x YRGB_MST=0x%08x CBR_MST=0x%08x VIR=0x%08x ACT=0x%08x DSP=0x%08x ST=0x%08x SCL=0x%08x FAC=0x%08x",
            desc->name,
            HWREG32((rt_uint8_t *)vfb->regs + base + VOP2_ESMART_CTRL0),
            HWREG32((rt_uint8_t *)vfb->regs + base + VOP2_ESMART_CTRL1),
            HWREG32((rt_uint8_t *)vfb->regs + base + VOP2_REGION0_CTRL),
            HWREG32((rt_uint8_t *)vfb->regs + base + VOP2_REGION0_YRGB_MST),
            HWREG32((rt_uint8_t *)vfb->regs + base + VOP2_REGION0_CBR_MST),
            HWREG32((rt_uint8_t *)vfb->regs + base + VOP2_REGION0_VIR),
            HWREG32((rt_uint8_t *)vfb->regs + base + VOP2_REGION0_ACT_INFO),
            HWREG32((rt_uint8_t *)vfb->regs + base + VOP2_REGION0_DSP_INFO),
            HWREG32((rt_uint8_t *)vfb->regs + base + VOP2_REGION0_DSP_ST),
            HWREG32((rt_uint8_t *)vfb->regs + base + VOP2_REGION0_SCL_CTRL),
            HWREG32((rt_uint8_t *)vfb->regs + base + VOP2_REGION0_SCL_FACTOR_YRGB));

    if (desc->mix_alpha_reg >= 0x8)
    {
        LOG_D("%s mix regs: SRC_COLOR=0x%08x DST_COLOR=0x%08x SRC_ALPHA=0x%08x DST_ALPHA=0x%08x",
                desc->name,
                HWREG32((rt_uint8_t *)vfb->regs + desc->mix_alpha_reg - 0x8),
                HWREG32((rt_uint8_t *)vfb->regs + desc->mix_alpha_reg - 0x4),
                HWREG32((rt_uint8_t *)vfb->regs + desc->mix_alpha_reg),
                HWREG32((rt_uint8_t *)vfb->regs + desc->mix_alpha_reg + 0x4));
    }
}

static void vop2fb_axi_config(struct vop2fb *vfb, const struct vop2fb_win_desc *desc)
{
    rt_uint32_t base = desc->base_offset;

    if (!vfb->soc->axi_config)
    {
        return;
    }

    switch (desc->type)
    {
    case VOP2FB_LAYER_CLUSTER:
        vop2fb_mask_write(vfb, base + VOP2_CLUSTER_CTRL,
                VOP2_CLUSTER_AXI_ID_MASK, VOP2_CLUSTER_AXI_ID_SHIFT, desc->axi_id);
        vop2fb_mask_write(vfb, base + VOP2_CLUSTER_WIN0_CTRL2,
                VOP2_CLUSTER_AXI_YRGB_ID_MASK, VOP2_CLUSTER_AXI_YRGB_ID_SHIFT,
                desc->axi_yrgb_id);
        vop2fb_mask_write(vfb, base + VOP2_CLUSTER_WIN0_CTRL2,
                VOP2_CLUSTER_AXI_UV_ID_MASK, VOP2_CLUSTER_AXI_UV_ID_SHIFT,
                desc->axi_uv_id);
        break;

    case VOP2FB_LAYER_ESMART:
    case VOP2FB_LAYER_SMART:
        vop2fb_mask_write(vfb, base + VOP2_ESMART_AXI_CTRL,
                VOP2_ESMART_AXI_ID_MASK, VOP2_ESMART_AXI_ID_SHIFT, desc->axi_id);
        vop2fb_mask_write(vfb, base + VOP2_ESMART_CTRL1,
                VOP2_ESMART_AXI_YRGB_ID_MASK, VOP2_ESMART_AXI_YRGB_ID_SHIFT,
                desc->axi_yrgb_id);
        vop2fb_mask_write(vfb, base + VOP2_ESMART_CTRL1,
                VOP2_ESMART_AXI_UV_ID_MASK, VOP2_ESMART_AXI_UV_ID_SHIFT,
                desc->axi_uv_id);
        break;
    }
}

static void vop2fb_win_disable(struct vop2fb *vfb, const struct vop2fb_win_desc *desc)
{
    rt_uint32_t base = desc->base_offset;

    switch (desc->type)
    {
    case VOP2FB_LAYER_CLUSTER:
        vop2fb_mask_write(vfb, base + VOP2_CLUSTER_WIN0_CTRL0,
                VOP2_EN_MASK, VOP2_WIN_EN_SHIFT, 0);
        vop2fb_mask_write(vfb, base + VOP2_CLUSTER_CTRL,
                VOP2_EN_MASK, VOP2_CLUSTER_EN_SHIFT, 0);
        break;
    case VOP2FB_LAYER_ESMART:
    case VOP2FB_LAYER_SMART:
        vop2fb_mask_write(vfb, base + VOP2_REGION0_CTRL,
                VOP2_EN_MASK, VOP2_WIN_EN_SHIFT, 0);
        break;
    }
}

static rt_uint32_t vop2fb_scale_mode(rt_uint32_t src, rt_uint32_t dst)
{
    if (src == dst)
    {
        return 0;
    }

    return src < dst ? 1 : 2;
}

static rt_uint32_t vop2fb_scale_factor(rt_uint32_t mode,
        rt_uint32_t src, rt_uint32_t dst)
{
    rt_uint32_t factor, shift;
    int i;

    if (!mode || src < 2 || dst < 2)
    {
        return 0;
    }

    shift = mode == 2 ? 12 : 16;
    factor = (rt_uint32_t)(((rt_uint64_t)(src - 1) << shift) /
            (dst - 1));

    for (i = 0; i < 100 && factor; ++i)
    {
        if ((((rt_uint64_t)factor * (dst - 1)) >> shift) < src - 1)
        {
            break;
        }

        factor--;
    }

    return factor;
}

static void vop2fb_smart_scale_setup(struct vop2fb *vfb,
        const struct vop2fb_win_desc *desc,
        rt_uint32_t src_w, rt_uint32_t src_h,
        rt_uint32_t dst_w, rt_uint32_t dst_h)
{
    rt_uint32_t base, hmode, vmode, hfilter, vfilter;
    rt_uint32_t hfactor, vfactor, scl_ctrl;

    if (!vfb->soc || vfb->soc->soc != VOP2FB_SOC_RK3568 ||
            (desc->type != VOP2FB_LAYER_ESMART &&
             desc->type != VOP2FB_LAYER_SMART))
    {
        return;
    }

    base = desc->base_offset;
    hmode = vop2fb_scale_mode(src_w, dst_w);
    vmode = vop2fb_scale_mode(src_h, dst_h);

    /*
     * RK3568 Smart/Esmart filter encodings follow Linux VOP2:
     * upscale uses bicubic (2), downscale uses bilinear (1).
     */
    hfilter = hmode == 1 ? 2 : hmode == 2 ? 1 : 0;
    vfilter = vmode == 1 ? 2 : vmode == 2 ? 1 : 0;
    hfactor = vop2fb_scale_factor(hmode, src_w, dst_w);
    vfactor = vop2fb_scale_factor(vmode, src_h, dst_h);
    scl_ctrl = hmode | (hfilter << 2) | (vmode << 4) | (vfilter << 6);

    vop2fb_reg_write(vfb, base + VOP2_REGION0_SCL_CTRL, scl_ctrl);
    vop2fb_reg_write(vfb, base + VOP2_REGION0_SCL_FACTOR_YRGB,
            (vfactor << 16) | hfactor);
    vop2fb_reg_write(vfb, base + VOP2_REGION0_SCL_FACTOR_CBR,
            (vfactor << 16) | hfactor);
}

static rt_err_t vop2fb_win_commit(struct vop2fb *vfb, rt_uint32_t vp_id,
        const struct vop2fb_win_desc *desc,
        rt_ubase_t dma_addr, rt_uint32_t mode, rt_uint32_t hw_fmt,
        rt_uint32_t src_w, rt_uint32_t src_h,
        rt_uint32_t dst_x, rt_uint32_t dst_y,
        rt_uint32_t dst_w, rt_uint32_t dst_h,
        rt_uint32_t xvir, rt_bool_t enable)
{
    rt_uint32_t base = desc->base_offset;
    rt_uint32_t act_info, dsp_info, dsp_st;

    if (!enable)
    {
        vop2fb_win_disable(vfb, desc);
        vop2fb_reg_write(vfb, VOP2_REG_CFG_DONE,
                vop2fb_cfg_done_vp_val(vfb, vp_id));
        return RT_EOK;
    }

    act_info = ((src_h - 1) << 16) | ((src_w - 1) & 0xffff);
    dsp_info = ((dst_h - 1) << 16) | ((dst_w - 1) & 0xffff);
    dsp_st = (dst_y << 16) | (dst_x & 0xffff);

    vop2fb_axi_config(vfb, desc);
    vop2fb_rk3568_smart_prepare(vfb, desc, hw_fmt, mode);
    vop2fb_smart_scale_setup(vfb, desc, src_w, src_h, dst_w, dst_h);

    switch (desc->type)
    {
    case VOP2FB_LAYER_CLUSTER:
        vop2fb_mask_write(vfb, base + VOP2_CLUSTER_WIN0_CTRL0,
                VOP2_WIN_FORMAT_MASK, VOP2_WIN_FORMAT_SHIFT, hw_fmt);
        vop2fb_reg_write(vfb, base + VOP2_CLUSTER_WIN0_VIR, xvir);
        vop2fb_reg_write(vfb, base + VOP2_CLUSTER_WIN0_YRGB_MST, (rt_uint32_t)dma_addr);
        vop2fb_reg_write(vfb, base + VOP2_CLUSTER_WIN0_ACT_INFO, act_info);
        vop2fb_reg_write(vfb, base + VOP2_CLUSTER_WIN0_DSP_INFO, dsp_info);
        vop2fb_reg_write(vfb, base + VOP2_CLUSTER_WIN0_DSP_ST, dsp_st);
        vop2fb_mask_write(vfb, base + VOP2_CLUSTER_WIN0_CTRL0,
                VOP2_EN_MASK, VOP2_WIN_EN_SHIFT, 1);
        vop2fb_mask_write(vfb, base + VOP2_CLUSTER_CTRL,
                VOP2_EN_MASK, VOP2_CLUSTER_EN_SHIFT, 1);
        break;

    case VOP2FB_LAYER_ESMART:
    case VOP2FB_LAYER_SMART:
        vop2fb_mask_write(vfb, base + VOP2_REGION0_CTRL,
                VOP2_WIN_FORMAT_MASK, VOP2_WIN_FORMAT_SHIFT, hw_fmt);
        vop2fb_reg_write(vfb, base + VOP2_REGION0_VIR, xvir);
        vop2fb_reg_write(vfb, base + VOP2_REGION0_YRGB_MST, (rt_uint32_t)dma_addr);
        vop2fb_reg_write(vfb, base + VOP2_REGION0_ACT_INFO, act_info);
        vop2fb_reg_write(vfb, base + VOP2_REGION0_DSP_INFO, dsp_info);
        vop2fb_reg_write(vfb, base + VOP2_REGION0_DSP_ST, dsp_st);
        vop2fb_mask_write(vfb, base + VOP2_REGION0_CTRL,
                VOP2_EN_MASK, VOP2_WIN_EN_SHIFT, 1);
        break;
    }

    vop2fb_reg_write(vfb, VOP2_REG_CFG_DONE,
            vop2fb_cfg_done_vp_val(vfb, vp_id));
    vop2fb_rk3568_dump_win_regs(vfb, desc);

    return RT_EOK;
}

static const struct vop2fb_win_desc *vop2fb_alloc_scanout(struct vop2fb *vfb,
        rt_uint32_t vp_id)
{
    static const rt_uint8_t scanout_indices[] = { 2, 1 };
    rt_size_t i, j;
    const struct vop2fb_win_desc *candidate;

    if (!vfb || !vfb->soc || vfb->soc->soc != VOP2FB_SOC_RK3568 ||
            vp_id >= VOP2FB_VP_MAX)
    {
        return RT_NULL;
    }

    if (vfb->vp[vp_id].scanout)
    {
        return vfb->vp[vp_id].scanout;
    }

    for (i = 0; i < RT_ARRAY_SIZE(scanout_indices); ++i)
    {
        candidate = &rk3568_overlays[scanout_indices[i]];

        for (j = 0; j < VOP2FB_VP_MAX; ++j)
        {
            if (vfb->vp[j].scanout == candidate)
            {
                break;
            }
        }

        if (j == VOP2FB_VP_MAX)
        {
            return candidate;
        }
    }

    return RT_NULL;
}

static rt_err_t vop2fb_plane_commit(struct rt_graphic_plane *plane, rt_bool_t enable)
{
    struct vop2fb *vfb = vop2fb_from_plane(plane);
    struct vop2fb_plane_priv *priv = vop2fb_plane_priv(plane);
    rt_err_t err;
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
        rt_spin_lock(&vfb->reg_lock);
        vop2fb_win_disable(vfb, priv->desc);
        vop2fb_reg_write(vfb, VOP2_REG_CFG_DONE,
                vop2fb_cfg_done_vp_val(vfb, priv->vp_id));
        rt_spin_unlock(&vfb->reg_lock);

        return RT_EOK;
    }

    if (!vfb->powered)
    {
        priv->enabled = RT_TRUE;
        return RT_EOK;
    }

    if (priv->dma_flags & RT_DMA_F_NOCACHE)
    {
        dma = priv->dma_handle + priv->pan_offset;
    }
    else
    {
        /*
         * RK3568 VOP is non-coherent.  The generic DMA fallback currently
         * treats a non-coherent device as if its allocation were uncached,
         * so sync_out_data() can skip the writeback for this cached LINEAR
         * framebuffer.  Flush it explicitly before the continuously running
         * scanout engine reads it.
         */
        rt_hw_cpu_dcache_ops(RT_HW_CACHE_FLUSH,
                plane->framebuffer + priv->pan_offset, plane->screen_len);
        dma = priv->dma_handle + priv->pan_offset;
    }

    xvir = vop2fb_xvir(plane->line_length);

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

    rt_spin_lock(&vfb->reg_lock);

    if (priv->desc->mix_alpha_reg)
    {
        vop2fb_mix_alpha_set(vfb, priv->desc->mix_alpha_reg, plane->alpha);
    }

    LOG_D("%s commit: dma=0x%08x xvir=%u src=%ux%u dst=%u,%u %ux%u pitch=%u alpha=%u",
            plane->name, (rt_uint32_t)dma, xvir,
            plane->width, plane->height,
            dst_x, dst_y, dst_w, dst_h,
            plane->line_length, plane->alpha);

    err = vop2fb_win_commit(vfb, priv->vp_id, priv->desc, dma,
            plane->mode, vop2fb_mode_to_hw(plane->mode),
            plane->width, plane->height, dst_x, dst_y, dst_w, dst_h,
            xvir, RT_TRUE);

    rt_spin_unlock(&vfb->reg_lock);

    return err;
}

static void vop2fb_fill_primary_background(struct rt_graphic_plane *plane)
{
    rt_uint8_t *fb;
    rt_size_t pixels, i;

    if (!plane || !plane->framebuffer || !plane->framebuffer_len)
    {
        return;
    }

    fb = plane->framebuffer;

    if (plane->bits_per_pixel != 32)
    {
        rt_memset(fb, 0, plane->framebuffer_len);
        return;
    }

    pixels = plane->framebuffer_len / sizeof(rt_uint32_t);

    for (i = 0; i < pixels; ++i)
    {
        ((rt_uint32_t *)fb)[i] = 0xff000000;
    }
}

static void vop2fb_plane_free_fb(struct rt_graphic_plane *plane)
{
    struct vop2fb *vfb = vop2fb_from_plane(plane);
    struct vop2fb_plane_priv *priv = vop2fb_plane_priv(plane);
    struct rt_device *dev = vfb->dev;

    if (plane->framebuffer)
    {
        rt_dma_free(dev, plane->framebuffer_len, plane->framebuffer,
                priv->dma_handle, priv->dma_flags);
        plane->framebuffer = RT_NULL;
        plane->framebuffer_len = 0;
        plane->screen_len = 0;
        priv->dma_handle = 0;
        priv->dma_flags = 0;
        priv->pan_offset = 0;
    }
}

/* -------------------------------------------------------------------------- */
/* Plane ops                                                                  */
/* -------------------------------------------------------------------------- */

static rt_err_t vop2fb_plane_update(struct rt_graphic_plane *plane,
        struct rt_device_rect_info *rect)
{
    struct vop2fb_plane_priv *priv = vop2fb_plane_priv(plane);

    RT_UNUSED(rect);

    if (priv)
    {
        priv->enabled = RT_TRUE;
    }

    return vop2fb_plane_commit(plane, RT_TRUE);
}

static rt_err_t vop2fb_plane_fb_remap(struct rt_graphic_plane *plane,
        rt_uint32_t mode, struct rt_device_rect_info *rect)
{
    rt_err_t err;
    struct vop2fb *vfb = vop2fb_from_plane(plane);
    struct vop2fb_plane_priv *priv = vop2fb_plane_priv(plane);
    struct rt_device *dev = vfb->dev;
    rt_uint32_t bpp = rt_graphic_mode_bpp(mode);
    rt_size_t screen_len, fb_len;
    rt_ubase_t dma_flags;
    void *fb;

    if (!rect->width || !rect->height || !bpp)
    {
        return -RT_EINVAL;
    }

    vop2fb_plane_free_fb(plane);

    plane->line_length = RT_ALIGN(rect->width * bpp, 32) / 8;
    plane->bits_per_pixel = bpp;
    screen_len = plane->line_length * rect->height;

    if (plane->type == RT_GRAPHIC_PLANE_TYPE_PRIMARY)
    {
        fb_len = screen_len * 2;
        dma_flags = RT_DMA_F_LINEAR;
    }
    else
    {
        fb_len = screen_len;
        dma_flags = RT_DMA_F_NOCACHE | RT_DMA_F_LINEAR;
    }

    fb = rt_dma_alloc(dev, fb_len, &priv->dma_handle, dma_flags);

    if (!fb && plane->type == RT_GRAPHIC_PLANE_TYPE_PRIMARY && fb_len > screen_len)
    {
        LOG_W("%s: alloc double buffer failed, fallback to single buffer", plane->name);
        fb_len = screen_len;
        fb = rt_dma_alloc(dev, fb_len, &priv->dma_handle, dma_flags);
    }

    if (!fb)
    {
        LOG_E("%s: alloc fb failed mode=%u rect=%ux%u fb_len=%u",
              plane->name, mode, rect->width, rect->height, (unsigned)fb_len);
        return -RT_ENOMEM;
    }

    rt_memset(fb, 0, fb_len);

    plane->framebuffer = fb;
    plane->screen_len = screen_len;
    plane->framebuffer_len = fb_len;
    plane->width = rect->width;
    plane->height = rect->height;
    plane->mode = mode;
    priv->dma_flags = dma_flags;
    priv->pan_offset = 0;

    if (plane->type == RT_GRAPHIC_PLANE_TYPE_PRIMARY)
    {
        vop2fb_fill_primary_background(plane);
    }

    if (vfb->powered && plane->type == RT_GRAPHIC_PLANE_TYPE_PRIMARY)
    {
        err = vop2fb_plane_commit(plane, RT_TRUE);
    }
    else
    {
        err = RT_EOK;
    }

    return err;
}

static rt_err_t vop2fb_plane_fb_pan_display(struct rt_graphic_plane *plane,
        struct rt_device_rect_info *rect)
{
    struct vop2fb_plane_priv *priv = vop2fb_plane_priv(plane);

    if (rect->width != plane->width || rect->height != plane->height)
    {
        return vop2fb_plane_fb_remap(plane, plane->mode, rect);
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

    return vop2fb_plane_commit(plane, RT_TRUE);
}

static rt_err_t vop2fb_plane_fb_cleanup(struct rt_graphic_plane *plane)
{
    struct vop2fb *vfb = vop2fb_from_plane(plane);
    struct vop2fb_plane_priv *priv = vop2fb_plane_priv(plane);

    if (priv && priv->enabled && priv->desc)
    {
        rt_spin_lock(&vfb->reg_lock);
        vop2fb_win_disable(vfb, priv->desc);
        vop2fb_reg_write(vfb, VOP2_REG_CFG_DONE,
                vop2fb_cfg_done_vp_val(vfb, priv->vp_id));
        rt_spin_unlock(&vfb->reg_lock);
        priv->enabled = RT_FALSE;
    }

    vop2fb_plane_free_fb(plane);

    return RT_EOK;
}

static rt_err_t vop2fb_plane_prop_set(struct rt_graphic_plane *plane,
        enum rt_graphic_plane_prop prop, void *value)
{
    struct vop2fb *vfb = vop2fb_from_plane(plane);
    struct vop2fb_plane_priv *priv = vop2fb_plane_priv(plane);
    rt_uint32_t base;

    if (!priv || !priv->desc)
    {
        return -RT_EINVAL;
    }

    base = priv->desc->base_offset;

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

            if (priv->desc->mix_alpha_reg)
            {
                rt_spin_lock(&vfb->reg_lock);
                vop2fb_mix_alpha_set(vfb, priv->desc->mix_alpha_reg, plane->alpha);
                vop2fb_reg_write(vfb, VOP2_REG_CFG_DONE,
                        vop2fb_cfg_done_vp_val(vfb, priv->vp_id));
                rt_spin_unlock(&vfb->reg_lock);
            }
        }
        return RT_EOK;

    case RT_GRAPHIC_PLANE_PROP_ROTATE:
        if (value)
        {
            rt_uint8_t rot = (rt_uint8_t)(rt_ubase_t)value;

            plane->rotate = rot;

            if (priv->desc->type == VOP2FB_LAYER_ESMART ||
                priv->desc->type == VOP2FB_LAYER_SMART)
            {
                rt_spin_lock(&vfb->reg_lock);
                vop2fb_mask_write(vfb, base + VOP2_ESMART_CTRL1,
                        VOP2_EN_MASK, VOP2_YMIRROR_EN_SHIFT,
                        rot == RT_GRAPHIC_PLANE_ROTATE_180 ? 1 : 0);
                vop2fb_reg_write(vfb, VOP2_REG_CFG_DONE,
                        vop2fb_cfg_done_vp_val(vfb, priv->vp_id));
                rt_spin_unlock(&vfb->reg_lock);
            }
        }
        return RT_EOK;

    default:
        return -RT_ENOSYS;
    }
}

static const struct rt_graphic_plane_ops vop2fb_primary_ops =
{
    .update = vop2fb_plane_update,
    .fb_remap = vop2fb_plane_fb_remap,
    .fb_pan_display = vop2fb_plane_fb_pan_display,
    .fb_cleanup = vop2fb_plane_fb_cleanup,
    .prop_set = vop2fb_plane_prop_set,
};

static const struct rt_graphic_plane_ops vop2fb_overlay_ops =
{
    .update = vop2fb_plane_update,
    .fb_remap = vop2fb_plane_fb_remap,
    .fb_cleanup = vop2fb_plane_fb_cleanup,
    .prop_set = vop2fb_plane_prop_set,
};

static const struct rt_graphic_plane_ops vop2fb_cursor_ops =
{
    .update = vop2fb_plane_update,
    .fb_remap = vop2fb_plane_fb_remap,
    .fb_cleanup = vop2fb_plane_fb_cleanup,
};

/* -------------------------------------------------------------------------- */
/* Device ops                                                                 */
/* -------------------------------------------------------------------------- */

static struct rt_clk *vop2fb_clk_find(struct vop2fb *vfb, const char *name)
{
    rt_size_t i;

    if (!vfb || rt_is_err_or_null(vfb->clks) || !name)
    {
        return RT_NULL;
    }

    for (i = 0; i < vfb->clks->count; ++i)
    {
        struct rt_clk *clk = vfb->clks->clks[i];

        if (!rt_is_err_or_null(clk) && clk->con_id &&
                !rt_strcmp(clk->con_id, name))
        {
            return clk;
        }
    }

    return RT_NULL;
}

static rt_err_t vop2fb_clk_enable(struct vop2fb *vfb)
{
    struct rt_clk *hclk, *aclk, *pclk;
    rt_err_t err;

    if (vfb->clk_enabled)
    {
        return RT_EOK;
    }

    hclk = vop2fb_clk_find(vfb, "hclk_vop");
    aclk = vop2fb_clk_find(vfb, "aclk_vop");
    pclk = vop2fb_clk_find(vfb, "pclk_vop");

    if (!hclk || !aclk)
    {
        LOG_E("vop2: missing core clock hclk_vop=%s aclk_vop=%s",
                hclk ? "yes" : "no", aclk ? "yes" : "no");
        return -RT_ENOENT;
    }

    if ((err = rt_clk_prepare_enable(hclk)))
    {
        return err;
    }

    if ((err = rt_clk_prepare_enable(aclk)))
    {
        rt_clk_disable_unprepare(hclk);
        return err;
    }

    if (pclk && (err = rt_clk_prepare_enable(pclk)))
    {
        rt_clk_disable_unprepare(aclk);
        rt_clk_disable_unprepare(hclk);
        return err;
    }

    vfb->clk_enabled = RT_TRUE;

    return RT_EOK;
}

static void vop2fb_clk_disable(struct vop2fb *vfb)
{
    struct rt_clk *hclk, *aclk, *pclk;

    if (!vfb->clk_enabled)
    {
        return;
    }

    hclk = vop2fb_clk_find(vfb, "hclk_vop");
    aclk = vop2fb_clk_find(vfb, "aclk_vop");
    pclk = vop2fb_clk_find(vfb, "pclk_vop");

    if (pclk)
    {
        rt_clk_disable_unprepare(pclk);
    }
    if (aclk)
    {
        rt_clk_disable_unprepare(aclk);
    }
    if (hclk)
    {
        rt_clk_disable_unprepare(hclk);
    }

    vfb->clk_enabled = RT_FALSE;
}

static struct rt_clk *vop2fb_vp_clk_find(struct vop2fb *vfb,
        rt_uint32_t vp_id)
{
    char name[16];
    struct rt_clk *clk;

    rt_snprintf(name, sizeof(name), "dclk_vp%u", vp_id);
    clk = vop2fb_clk_find(vfb, name);

    if (!clk)
    {
        rt_snprintf(name, sizeof(name), "dclk_vop%u", vp_id);
        clk = vop2fb_clk_find(vfb, name);
    }

    return clk;
}

static rt_err_t vop2fb_vp_clk_enable(struct vop2fb *vfb, rt_uint32_t vp_id)
{
    rt_err_t err;
    struct rt_clk *dclk;
    struct vop2fb_vp_state *state;

    if (!vfb || vp_id >= vfb->soc->vp_count || vp_id >= VOP2FB_VP_MAX)
    {
        return -RT_EINVAL;
    }

    state = &vfb->vp[vp_id];

    if (state->dclk_enabled)
    {
        return RT_EOK;
    }

    dclk = vop2fb_vp_clk_find(vfb, vp_id);
    if (!dclk)
    {
        return -RT_ENOENT;
    }

    err = rt_clk_prepare_enable(dclk);
    if (!err)
    {
        state->dclk_enabled = RT_TRUE;
    }

    return err;
}

static void vop2fb_vp_clk_disable(struct vop2fb *vfb, rt_uint32_t vp_id)
{
    struct rt_clk *dclk;
    struct vop2fb_vp_state *state;

    if (!vfb || vp_id >= vfb->soc->vp_count || vp_id >= VOP2FB_VP_MAX)
    {
        return;
    }

    state = &vfb->vp[vp_id];
    if (!state->dclk_enabled)
    {
        return;
    }

    dclk = vop2fb_vp_clk_find(vfb, vp_id);
    if (dclk)
    {
        rt_clk_disable_unprepare(dclk);
    }

    state->dclk_enabled = RT_FALSE;
}

static void vop2fb_output_wins_disable(struct vop2fb_vp_state *state)
{
    rt_size_t i;
    struct vop2fb *vfb;

    if (!state || !(vfb = state->vfb))
    {
        return;
    }

    if (state->primary)
    {
        vop2fb_plane_commit(state->primary, RT_FALSE);
    }

    if (state->graphic != &vfb->parent)
    {
        return;
    }

    if (vfb->cursor)
    {
        vop2fb_plane_commit(vfb->cursor, RT_FALSE);
    }

    for (i = 0; i < vfb->overlay_count; ++i)
    {
        if (vfb->overlays[i])
        {
            vop2fb_plane_commit(vfb->overlays[i], RT_FALSE);
        }
    }
}

static rt_err_t vop2fb_output_wins_enable(struct vop2fb_vp_state *state)
{
    rt_err_t err;
    rt_size_t i;
    struct vop2fb *vfb;

    if (!state || !(vfb = state->vfb))
    {
        return -RT_EINVAL;
    }

    if (state->primary && state->primary->framebuffer)
    {
        if ((err = vop2fb_plane_commit(state->primary, RT_TRUE)))
        {
            return err;
        }
    }

    if (state->graphic != &vfb->parent)
    {
        return RT_EOK;
    }

    for (i = 0; i < vfb->overlay_count; ++i)
    {
        struct rt_graphic_plane *plane = vfb->overlays[i];
        struct vop2fb_plane_priv *priv;

        if (!plane || !plane->framebuffer)
        {
            continue;
        }

        priv = vop2fb_plane_priv(plane);

        if (priv && priv->enabled)
        {
            vop2fb_plane_commit(plane, RT_TRUE);
        }
    }

    if (vfb->cursor && vfb->cursor->framebuffer)
    {
        struct vop2fb_plane_priv *priv = vop2fb_plane_priv(vfb->cursor);

        if (priv && priv->enabled)
        {
            vop2fb_plane_commit(vfb->cursor, RT_TRUE);
        }
    }

    return RT_EOK;
}

static rt_err_t vop2fb_dpms_switch(struct rt_graphic_device *gdev, rt_uint32_t dpms)
{
    rt_err_t err;
    struct vop2fb_vp_state *state = vop2fb_output_from_graphic(gdev);

    if (!state || !state->vfb)
    {
        return -RT_EINVAL;
    }

    switch (dpms)
    {
    case RT_GRAPHIC_DPMS_ON:
        err = vop2fb_output_wins_enable(state);
        break;

    case RT_GRAPHIC_DPMS_STANDBY:
    case RT_GRAPHIC_DPMS_SUSPEND:
        vop2fb_output_wins_disable(state);
        err = RT_EOK;
        break;

    case RT_GRAPHIC_DPMS_OFF:
        vop2fb_output_wins_disable(state);
        err = RT_EOK;
        break;

    default:
        return -RT_EINVAL;
    }

    gdev->dpms = dpms;

    return err;
}

static rt_err_t vop2fb_wait_vsync(struct rt_graphic_device *gdev)
{
    struct vop2fb_vp_state *state = vop2fb_output_from_graphic(gdev);
    struct vop2fb *vfb;
    rt_err_t err;

    if (!state || !(vfb = state->vfb))
    {
        return -RT_EINVAL;
    }

    /* No frame can arrive before a route has completed fb registration. */
    if (!state->registered)
    {
        return RT_EOK;
    }

    if (vfb->irq >= 0)
    {
        if ((err = rt_mutex_take(&state->vsync_lock,
                rt_tick_from_millisecond(100))))
        {
            LOG_W("vop2: wait vsync lock timeout on vp%u", state->vp_id);
            return err;
        }

        /*
         * Do not consume an interrupt token left by an older frame.  The ISR
         * only releases the semaphore on the 0 -> 1 transition, so this also
         * prevents the semaphore count from growing while nobody is waiting.
         */
        rt_atomic_store(&state->vsync, 0);

        while (rt_sem_trytake(&state->vsync_sem) == RT_EOK)
        {
        }

        if (rt_atomic_load(&state->vsync))
        {
            err = RT_EOK;
            goto _unlock;
        }

        if (rt_sem_take(&state->vsync_sem, rt_tick_from_millisecond(100)) == RT_EOK)
        {
            err = RT_EOK;
            goto _unlock;
        }

        LOG_W("vop2: wait vsync timeout on vp%u", state->vp_id);
        err = -RT_ETIMEOUT;

_unlock:
        rt_mutex_release(&state->vsync_lock);

        return err;
    }

    rt_thread_mdelay(16);

    return RT_EOK;
}

static const struct rt_graphic_device_ops vop2fb_ops =
{
    .dpms_switch = vop2fb_dpms_switch,
    .wait_vsync = vop2fb_wait_vsync,
};

static void vop2fb_rk3568_irqs_quiesce(struct vop2fb *vfb)
{
    rt_uint32_t vp_id;
    const rt_uint32_t vp_irqs = 0xffff;
    const rt_uint32_t sys_irqs = 0xfe;

    if (!vfb || !vfb->regs || !vfb->soc ||
            vfb->soc->soc != VOP2FB_SOC_RK3568 || !vfb->clk_enabled)
    {
        return;
    }

    /*
     * The merged VOP2 interrupt is level-triggered.  Mask and clear every
     * source before exposing it to GIC, including state inherited from the
     * bootloader on VPs that RT-Thread does not use.
     */
    for (vp_id = 0; vp_id < vfb->soc->vp_count &&
            vp_id < VOP2FB_VP_MAX; ++vp_id)
    {
        HWREG32((rt_uint8_t *)vfb->regs + RK3568_VP_INT_EN(vp_id)) =
                vp_irqs << 16;
        HWREG32((rt_uint8_t *)vfb->regs + RK3568_VP_INT_CLR(vp_id)) =
                (vp_irqs << 16) | vp_irqs;
    }

    HWREG32((rt_uint8_t *)vfb->regs + RK3568_SYS0_INT_EN) = sys_irqs << 16;
    HWREG32((rt_uint8_t *)vfb->regs + RK3568_SYS0_INT_CLR) =
            (sys_irqs << 16) | sys_irqs;
    HWREG32((rt_uint8_t *)vfb->regs + RK3568_SYS1_INT_EN) = sys_irqs << 16;
    HWREG32((rt_uint8_t *)vfb->regs + RK3568_SYS1_INT_CLR) =
            (sys_irqs << 16) | sys_irqs;
}

static void vop2fb_isr(int irqno, void *param)
{
    struct vop2fb *vfb = param;
    rt_uint32_t vp_id, vp_mask, irqs, sys0_irqs, sys1_irqs;
    rt_uint32_t vp_irqs[VOP2FB_VP_MAX] = { 0 };
    rt_bool_t pending = RT_FALSE;

    RT_UNUSED(irqno);

    if (!vfb || !vfb->regs)
    {
        return;
    }

    sys0_irqs = HWREG32((rt_uint8_t *)vfb->regs + RK3568_SYS0_INT_STATUS) &
            RK3568_SYS_BUS_ERROR_INTR;
    sys1_irqs = HWREG32((rt_uint8_t *)vfb->regs + RK3568_SYS1_INT_STATUS) &
            RK3568_SYS_BUS_ERROR_INTR;
    vp_mask = vfb->configured_vp_mask | vfb->active_vp_mask;

    for (vp_id = 0; vp_id < vfb->soc->vp_count &&
            vp_id < VOP2FB_VP_MAX; ++vp_id)
    {
        vp_irqs[vp_id] =
                HWREG32((rt_uint8_t *)vfb->regs + RK3568_VP_INT_STATUS(vp_id));
        pending |= vp_irqs[vp_id] ? RT_TRUE : RT_FALSE;
    }

    if (!pending && !sys0_irqs && !sys1_irqs)
    {
        return;
    }

    if (sys0_irqs)
    {
        HWREG32((rt_uint8_t *)vfb->regs + RK3568_SYS0_INT_CLR) =
                (sys0_irqs << 16) | sys0_irqs;
        vfb->axi_bus_error_count[0]++;

        if (!(vfb->axi_bus_error_count[0] & (vfb->axi_bus_error_count[0] - 1)))
        {
            LOG_W("vop2: AXI0 bus error count=%u", vfb->axi_bus_error_count[0]);
        }
    }

    if (sys1_irqs)
    {
        HWREG32((rt_uint8_t *)vfb->regs + RK3568_SYS1_INT_CLR) =
                (sys1_irqs << 16) | sys1_irqs;
        vfb->axi_bus_error_count[1]++;

        if (!(vfb->axi_bus_error_count[1] & (vfb->axi_bus_error_count[1] - 1)))
        {
            LOG_W("vop2: AXI1 bus error count=%u", vfb->axi_bus_error_count[1]);
        }
    }

    for (vp_id = 0; vp_id < vfb->soc->vp_count &&
            vp_id < VOP2FB_VP_MAX; ++vp_id)
    {
        irqs = vp_irqs[vp_id];

        if (!irqs)
        {
            continue;
        }

        HWREG32((rt_uint8_t *)vfb->regs + RK3568_VP_INT_CLR(vp_id)) =
                (irqs << 16) | irqs;

        if (!(vp_mask & RT_BIT(vp_id)))
        {
            continue;
        }

        if (irqs & VOP2_VP_POST_BUF_EMPTY_INTR)
        {
            vfb->post_buf_empty_count[vp_id]++;

            if (!(vfb->post_buf_empty_count[vp_id] &
                    (vfb->post_buf_empty_count[vp_id] - 1)))
            {
                LOG_W("vop2: vp%u post buffer empty count=%u",
                        vp_id, vfb->post_buf_empty_count[vp_id]);
            }
        }

        if (!(irqs & VOP2_VP_FS_FIELD_INTR) ||
                !vfb->vp[vp_id].ipc_ready)
        {
            continue;
        }

        if (rt_atomic_exchange(&vfb->vp[vp_id].vsync, 1) == 0)
        {
            rt_sem_release(&vfb->vp[vp_id].vsync_sem);
        }
    }
}

/* -------------------------------------------------------------------------- */
/* Plane setup                                                                */
/* -------------------------------------------------------------------------- */

static void vop2fb_plane_init_fb_state(struct rt_graphic_plane *plane, rt_uint32_t mode)
{
    rt_uint32_t bpp = rt_graphic_mode_bpp(mode);

    plane->mode = mode;
    plane->bits_per_pixel = bpp;
    plane->line_length = RT_ALIGN(plane->width * bpp, 32) / 8;
    plane->screen_len = plane->line_length * plane->height;
    plane->framebuffer = RT_NULL;
    plane->framebuffer_len = 0;
}

static void vop2fb_primary_plane_prepare_register(struct rt_graphic_plane *plane)
{
    plane->x = 0;
    plane->y = 0;
    plane->width = 0;
    plane->height = 0;
    plane->line_length = 0;
    plane->screen_len = 0;
    plane->framebuffer = RT_NULL;
    plane->framebuffer_len = 0;
}

static void vop2fb_clear_plane_refs(struct vop2fb *vfb)
{
    rt_size_t i;

    vfb->primary = RT_NULL;
    vfb->cursor = RT_NULL;

    for (i = 0; i < RT_ARRAY_SIZE(vfb->overlays); ++i)
    {
        vfb->overlays[i] = RT_NULL;
    }
}

static void vop2fb_clear_output_refs(struct vop2fb_vp_state *state)
{
    struct vop2fb *vfb;

    if (!state || !(vfb = state->vfb))
    {
        return;
    }

    if (state->graphic == &vfb->parent)
    {
        vop2fb_clear_plane_refs(vfb);
        vfb->registered = RT_FALSE;
    }

    state->primary = RT_NULL;
    state->registered = RT_FALSE;
}

static rt_err_t vop2fb_cleanup_planes(struct vop2fb *vfb)
{
    rt_uint32_t vp_id;
    rt_size_t i;
    rt_err_t err;

    for (vp_id = 0; vp_id < vfb->soc->vp_count &&
            vp_id < VOP2FB_VP_MAX; ++vp_id)
    {
        struct vop2fb_vp_state *state = &vfb->vp[vp_id];

        if (state->registered)
        {
            err = rt_graphic_device_unregister(state->graphic);
            if (err)
            {
                return err;
            }
            vop2fb_clear_output_refs(state);
        }
        else if (state->primary && state->graphic)
        {
            rt_graphic_device_del_plane(state->graphic, state->primary);
            rt_graphic_device_free_plane(state->primary);
            if (state->graphic == &vfb->parent)
            {
                vfb->primary = RT_NULL;
            }
            state->primary = RT_NULL;
        }
    }

    /*
     * Probe creates the first primary before a route chooses its VP.  Release
     * it here if no route ever claimed it.
     */
    for (i = 0; i < vfb->overlay_count; ++i)
    {
        if (vfb->overlays[i])
        {
            rt_graphic_device_del_plane(&vfb->parent, vfb->overlays[i]);
            rt_graphic_device_free_plane(vfb->overlays[i]);
            vfb->overlays[i] = RT_NULL;
        }
    }

    if (vfb->cursor)
    {
        rt_graphic_device_del_plane(&vfb->parent, vfb->cursor);
        rt_graphic_device_free_plane(vfb->cursor);
        vfb->cursor = RT_NULL;
    }

    if (vfb->primary)
    {
        rt_graphic_device_del_plane(&vfb->parent, vfb->primary);
        rt_graphic_device_free_plane(vfb->primary);
        vfb->primary = RT_NULL;
    }

    return RT_EOK;
}

static rt_err_t vop2fb_plane_init(struct vop2fb *vfb,
        struct vop2fb_vp_state *state,
        struct rt_graphic_plane *plane,
        const struct vop2fb_win_desc *desc,
        rt_uint32_t width, rt_uint32_t height,
        rt_uint8_t type)
{
    struct vop2fb_plane_priv *priv = vop2fb_plane_priv(plane);

    priv->vfb = vfb;
    priv->desc = desc;
    priv->enabled = RT_FALSE;
    priv->pan_offset = 0;
    priv->vp_id = state->vp_id;
    plane->z = desc->z_order;
    plane->alpha = 0xff;

    if (type == RT_GRAPHIC_PLANE_TYPE_CURSOR)
    {
        plane->width = VOP2FB_CURSOR_W;
        plane->height = VOP2FB_CURSOR_H;
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

    vop2fb_plane_init_fb_state(plane, RTGRAPHIC_PIXEL_FORMAT_ARGB888);

    return RT_EOK;
}

static rt_err_t vop2fb_primary_plane_create(struct vop2fb *vfb,
        struct vop2fb_vp_state *state,
        const struct vop2fb_win_desc *desc,
        rt_uint32_t width, rt_uint32_t height)
{
    rt_err_t err;
    struct rt_graphic_plane *plane;
    struct rt_graphic_device *gdev = state->graphic;

    plane = rt_graphic_device_alloc_plane(gdev, sizeof(struct vop2fb_plane_priv),
            &vop2fb_primary_ops, vop2fb_modes, RT_ARRAY_SIZE(vop2fb_modes),
            RT_GRAPHIC_PLANE_TYPE_PRIMARY);

    if (!plane)
    {
        return -RT_ENOMEM;
    }

    if ((err = rt_graphic_device_add_plane(gdev, plane)))
    {
        rt_graphic_device_free_plane(plane);
        return err;
    }

    state->primary = plane;
    if (gdev == &vfb->parent)
    {
        vfb->primary = plane;
    }

    err = vop2fb_plane_init(vfb, state, plane, desc, width, height,
            RT_GRAPHIC_PLANE_TYPE_PRIMARY);
    if (err)
    {
        rt_graphic_device_del_plane(gdev, plane);
        state->primary = RT_NULL;
        if (gdev == &vfb->parent)
        {
            vfb->primary = RT_NULL;
        }
        rt_graphic_device_free_plane(plane);
        return err;
    }

    vop2fb_primary_plane_prepare_register(plane);

    return RT_EOK;
}

static rt_err_t vop2fb_overlay_planes_create(struct vop2fb *vfb,
        struct vop2fb_vp_state *state,
        rt_uint32_t width, rt_uint32_t height)
{
    rt_err_t err;
    rt_size_t i;
    struct rt_graphic_plane *plane;

    for (i = 0; i < vfb->overlay_count; ++i)
    {
        plane = rt_graphic_device_alloc_plane(&vfb->parent, sizeof(struct vop2fb_plane_priv),
                &vop2fb_overlay_ops, vop2fb_modes, RT_ARRAY_SIZE(vop2fb_modes),
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

        if ((err = vop2fb_plane_init(vfb, state, plane, &vfb->soc->overlays[i],
                width, height, RT_GRAPHIC_PLANE_TYPE_OVERLAY)))
        {
            return err;
        }
    }

    return RT_EOK;
}

static rt_err_t vop2fb_cursor_plane_create(struct vop2fb *vfb,
        struct vop2fb_vp_state *state,
        rt_uint32_t width, rt_uint32_t height)
{
    rt_err_t err;
    struct rt_graphic_plane *plane;

    plane = rt_graphic_device_alloc_plane(&vfb->parent, sizeof(struct vop2fb_plane_priv),
            &vop2fb_cursor_ops, vop2fb_modes, RT_ARRAY_SIZE(vop2fb_modes),
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

    return vop2fb_plane_init(vfb, state, plane, vfb->soc->cursor, width, height,
            RT_GRAPHIC_PLANE_TYPE_CURSOR);
}

/* -------------------------------------------------------------------------- */
/* Display pipeline hooks                                                     */
/* -------------------------------------------------------------------------- */

static rt_err_t vop2fb_crtc_mode_set(void *priv,
        const struct display_route *route, const struct display_timing *tim)
{
    struct vop2fb *vfb = priv;
    struct vop2fb_vp_state *state;
    const struct vop2fb_win_desc *saved_scanout;
    enum vop2fb_output_if saved_output_if;
    enum vop2fb_output_if state_output_if;
    struct display_timing state_timing;
    struct display_timing saved_timing;
    rt_uint32_t saved_vp, saved_w, saved_h;
    rt_bool_t state_mode_valid;
    rt_bool_t saved_timing_valid;
    rt_bool_t primary_output;
    rt_err_t err;
    rt_uint32_t vp_id;

    if (!vfb || !route || !tim)
    {
        return -RT_EINVAL;
    }

    vp_id = route->vp_id;

    if (vp_id >= vfb->soc->vp_count ||
            vp_id >= VOP2FB_VP_MAX)
    {
        return -RT_EINVAL;
    }

    saved_vp = vfb->vp_id;
    saved_output_if = vfb->output_if;
    saved_timing = vfb->output_tim;
    saved_timing_valid = vfb->output_tim_valid;
    saved_w = vfb->display_w;
    saved_h = vfb->display_h;
    primary_output = !saved_timing_valid || vp_id == saved_vp;
    state = &vfb->vp[vp_id];
    state_timing = state->timing;
    state_output_if = state->output_if;
    saved_scanout = state->scanout;
    state_mode_valid = state->mode_valid;

    vfb->vp_id = vp_id;
    vfb->output_if = vop2fb_output_from_connector(route->connector_np);

    if (vfb->output_if == VOP2FB_OUTPUT_NONE)
    {
        err = -RT_ENOSYS;
        goto _restore;
    }

    state->timing = *tim;
    state->output_if = vfb->output_if;
    state->mode_valid = RT_TRUE;

    if (primary_output)
    {
        state->scanout = vfb->soc->primary;
        state->graphic = &vfb->parent;
    }
    else
    {
        state->scanout = vop2fb_alloc_scanout(vfb, vp_id);

        if (!state->scanout)
        {
            state->mode_valid = RT_FALSE;
            err = -RT_ENOSYS;
            goto _restore;
        }

        state->graphic = &state->auxiliary;
    }

    state->vfb = vfb;
    state->vp_id = vp_id;
    state->graphic->ops = &vop2fb_ops;
    state->graphic->parent.ofw_node = vfb->dev->ofw_node;
    state->graphic->parent.user_data = state;

    err = vop2fb_vp_mode_set(vfb, vp_id, tim);

    if (err)
    {
        state->mode_valid = RT_FALSE;
        goto _restore;
    }

    if (!state->primary &&
            (err = vop2fb_primary_plane_create(vfb, state, state->scanout,
                    tim->hactive, tim->vactive)))
    {
        state->mode_valid = RT_FALSE;
        goto _restore;
    }

    vfb->configured_vp_mask |= RT_BIT(vp_id);

    if (primary_output)
    {
        vfb->output_tim = *tim;
        vfb->output_tim_valid = RT_TRUE;
        vfb->display_w = tim->hactive;
        vfb->display_h = tim->vactive;
        return RT_EOK;
    }

_restore:
    if (err)
    {
        state->timing = state_timing;
        state->output_if = state_output_if;
        state->scanout = saved_scanout;
        state->mode_valid = state_mode_valid;
    }
    vfb->vp_id = saved_vp;
    vfb->output_if = saved_output_if;
    vfb->output_tim = saved_timing;
    vfb->output_tim_valid = saved_timing_valid;
    vfb->display_w = saved_w;
    vfb->display_h = saved_h;

    return err;
}

static rt_err_t vop2fb_graphic_register(struct vop2fb *vfb, rt_uint32_t vp_id)
{
    rt_err_t err;
    struct vop2fb_vp_state *state = &vfb->vp[vp_id];
    struct rt_graphic_device *gdev = state->graphic;
    rt_uint32_t width = state->timing.hactive;
    rt_uint32_t height = state->timing.vactive;

    if (state->registered)
    {
        LOG_D("vop2: graphic device already registered on vp%u", vp_id);
        return RT_EOK;
    }

    if (!gdev || !state->primary || !width || !height)
    {
        LOG_W("vop2: register skipped primary=%p size=%ux%u",
                state->primary, width, height);
        return -RT_EINVAL;
    }

    LOG_D("vop2: register graphic device %ux%u on vp%u",
            width, height, vp_id);
    rt_graphic_device_simple_edid(gdev, width, height, 60);
    vop2fb_primary_plane_prepare_register(state->primary);

    if ((err = rt_graphic_device_register(gdev)))
    {
        LOG_E("vop2: register vp%u graphic device failed: %s",
                vp_id, rt_strerror(err));
        return err;
    }

    state->registered = RT_TRUE;

    if (gdev == &vfb->parent)
    {
        vfb->registered = RT_TRUE;

        if ((err = vop2fb_overlay_planes_create(vfb, state, width, height)))
        {
            LOG_W("vop2: create overlay planes failed, use primary only: %s",
                    rt_strerror(err));
        }

        if ((err = vop2fb_cursor_plane_create(vfb, state, width, height)))
        {
            LOG_W("vop2: create cursor plane failed, continue without cursor: %s",
                    rt_strerror(err));
        }
    }

    /*
     * The route has already enabled VOP2, its VP clock and the connector.
     * Calling DPMS ON here would repeat window commits during registration.
     * VOP2 scans out continuously; callers flush cached drawing through the
     * plane update API instead of a periodic hard-timer commit.
     */
    gdev->dpms = RT_GRAPHIC_DPMS_ON;
    LOG_I("vop2: vp%u %s registered as %s (%ux%u)",
            vp_id, state->scanout->name,
            rt_dm_dev_get_name(&gdev->parent), width, height);

    return RT_EOK;
}

static rt_err_t vop2fb_crtc_enable(void *priv, rt_uint32_t vp_id, rt_bool_t enable)
{
    struct vop2fb *vfb = priv;
    struct vop2fb_vp_state *state;
    enum vop2fb_output_if saved_output_if;
    rt_err_t err;
    rt_bool_t vp_started = RT_FALSE;
    rt_bool_t dclk_started = RT_FALSE;

    if (!vfb || vp_id >= vfb->soc->vp_count || vp_id >= VOP2FB_VP_MAX)
    {
        return -RT_EINVAL;
    }

    state = &vfb->vp[vp_id];
    saved_output_if = vfb->output_if;

    if (enable)
    {
        LOG_D("vop2: crtc enable vp%u registered=%d mode_valid=%d size=%ux%u",
                vp_id, state->registered, state->mode_valid,
                state->timing.hactive, state->timing.vactive);

        if (!state->mode_valid)
        {
            return -RT_EINVAL;
        }

        if (!state->dclk_enabled)
        {
            if ((err = vop2fb_vp_clk_enable(vfb, vp_id)))
            {
                LOG_W("vop2: vp%u dclk enable failed: %s",
                        vp_id, rt_strerror(err));
                return err;
            }
            dclk_started = RT_TRUE;
        }

        state->enabled = RT_TRUE;
        vfb->active_vp_mask |= RT_BIT(vp_id);
        vfb->output_if = state->output_if;

        if ((err = vop2fb_overlay_init(vfb)))
        {
            LOG_W("vop2: overlay init failed on vp%u: %s", vp_id, rt_strerror(err));
            goto _rollback;
        }

        if ((err = vop2fb_vp_post_config(vfb, vp_id, &state->timing)))
        {
            LOG_W("vop2: vp%u post config failed: %s", vp_id, rt_strerror(err));
            goto _rollback;
        }

        if ((err = vop2fb_vp_enable(vfb, vp_id, enable)))
        {
            LOG_W("vop2: vp%u enable failed: %s", vp_id, rt_strerror(err));
            goto _rollback;
        }
        vp_started = RT_TRUE;

        vfb->output_if = saved_output_if;
        return RT_EOK;

_rollback:
        if (vp_started)
        {
            (void)vop2fb_vp_enable(vfb, vp_id, RT_FALSE);
        }
        vop2fb_output_disable(vfb, state->output_if);
        vop2fb_reg_write(vfb, VOP2_REG_CFG_DONE,
                vop2fb_cfg_done_vp_val(vfb, vp_id));
        if (state->scanout)
        {
            vop2fb_win_disable(vfb, state->scanout);
            vop2fb_reg_write(vfb, VOP2_REG_CFG_DONE,
                    vop2fb_cfg_done_vp_val(vfb, vp_id));
        }
        state->enabled = RT_FALSE;
        vfb->active_vp_mask &= ~RT_BIT(vp_id);
        vfb->configured_vp_mask &= ~RT_BIT(vp_id);
        state->mode_valid = RT_FALSE;
        state->output_if = VOP2FB_OUTPUT_NONE;
        state->scanout = RT_NULL;
        rt_memset(&state->timing, 0, sizeof(state->timing));
        if (vp_id == vfb->vp_id && !vfb->active_vp_mask)
        {
            vfb->output_if = VOP2FB_OUTPUT_NONE;
            vfb->output_tim_valid = RT_FALSE;
            rt_memset(&vfb->output_tim, 0, sizeof(vfb->output_tim));
        }
        else
        {
            vfb->output_if = saved_output_if;
        }
        (void)vop2fb_overlay_init(vfb);
        if (dclk_started)
        {
            vop2fb_vp_clk_disable(vfb, vp_id);
        }

        return err;
    }

    LOG_D("vop2: crtc disable vp%u", vp_id);
    vfb->output_if = state->output_if;

    if (state->scanout)
    {
        vop2fb_win_disable(vfb, state->scanout);
        vop2fb_reg_write(vfb, VOP2_REG_CFG_DONE,
                vop2fb_cfg_done_vp_val(vfb, vp_id));
    }

    err = vop2fb_vp_enable(vfb, vp_id, enable);
    vop2fb_output_disable(vfb, state->output_if);
    vop2fb_reg_write(vfb, VOP2_REG_CFG_DONE,
            vop2fb_cfg_done_vp_val(vfb, vp_id));
    state->enabled = RT_FALSE;
    vfb->active_vp_mask &= ~RT_BIT(vp_id);
    vfb->configured_vp_mask &= ~RT_BIT(vp_id);
    state->mode_valid = RT_FALSE;
    state->output_if = VOP2FB_OUTPUT_NONE;
    state->scanout = RT_NULL;
    rt_memset(&state->timing, 0, sizeof(state->timing));
    if (vp_id == vfb->vp_id && !vfb->active_vp_mask)
    {
        vfb->output_if = VOP2FB_OUTPUT_NONE;
        vfb->output_tim_valid = RT_FALSE;
        rt_memset(&vfb->output_tim, 0, sizeof(vfb->output_tim));
    }
    else
    {
        vfb->output_if = saved_output_if;
    }
    (void)vop2fb_overlay_init(vfb);
    vop2fb_vp_clk_disable(vfb, vp_id);

    return err;
}

static rt_err_t vop2fb_crtc_complete(void *priv, rt_uint32_t vp_id)
{
    rt_err_t err;
    struct vop2fb *vfb = priv;

    if (!vfb || vp_id >= vfb->soc->vp_count || vp_id >= VOP2FB_VP_MAX ||
            !vfb->vp[vp_id].enabled)
    {
        return -RT_EINVAL;
    }

    if ((err = vop2fb_graphic_register(vfb, vp_id)))
    {
        return err;
    }

    return RT_EOK;
}

static const struct rockchip_crtc_ops vop2fb_crtc_ops =
{
    .mode_set = vop2fb_crtc_mode_set,
    .enable = vop2fb_crtc_enable,
    .complete = vop2fb_crtc_complete,
};

/* -------------------------------------------------------------------------- */
/* Probe / remove                                                             */
/* -------------------------------------------------------------------------- */

static const struct vop2fb_soc_data *vop2fb_soc_from_id(const struct rt_ofw_node_id *id)
{
    if (!id || !id->compatible[0])
    {
        return RT_NULL;
    }

    if (!rt_strcmp(id->compatible, "rockchip,rk3568-vop"))
    {
        return &rk3568_soc_data;
    }

    if (!rt_strcmp(id->compatible, "rockchip,rk3588-vop"))
    {
        return &rk3588_soc_data;
    }

    if (!rt_strcmp(id->compatible, "rockchip,rk3528-vop"))
    {
        return &rk3528_soc_data;
    }

    if (!rt_strcmp(id->compatible, "rockchip,rk3562-vop"))
    {
        return &rk3562_soc_data;
    }

    if (!rt_strcmp(id->compatible, "rockchip,rk3576-vop"))
    {
        return &rk3576_soc_data;
    }

    return RT_NULL;
}

static void vop2fb_axi_init_all(struct vop2fb *vfb)
{
    rt_size_t i;

    if (!vfb->soc->axi_config)
    {
        return;
    }

    vop2fb_axi_config(vfb, vfb->soc->primary);
    vop2fb_axi_config(vfb, vfb->soc->cursor);

    for (i = 0; i < vfb->soc->overlay_count; ++i)
    {
        vop2fb_axi_config(vfb, &vfb->soc->overlays[i]);
    }
}

static int vop2fb_request_irq(struct vop2fb *vfb, struct rt_device *dev)
{
    char irq_name[16];

    if (vfb->soc->irq_by_vp && vfb->vp_id < vfb->soc->vp_count)
    {
        rt_snprintf(irq_name, sizeof(irq_name), "vop-vp%u", vfb->vp_id);
        vfb->irq = rt_dm_dev_get_irq_by_name(dev, irq_name);

        if (vfb->irq < 0)
        {
            vfb->irq = rt_dm_dev_get_irq(dev, vfb->vp_id + 1);
        }
    }
    else
    {
        vfb->irq = rt_dm_dev_get_irq(dev, 0);
    }

    return vfb->irq;
}

static rt_err_t vop2fb_parse_display(struct vop2fb *vfb, struct rt_platform_device *pdev)
{
    struct rt_device *dev = &pdev->parent;

    vfb->display_w = 1920;
    vfb->display_h = 1080;
    vfb->vp_id = 0;

    rt_dm_dev_prop_read_u32(dev, "rockchip,fb-width", &vfb->display_w);
    rt_dm_dev_prop_read_u32(dev, "rockchip,fb-height", &vfb->display_h);
    rt_dm_dev_prop_read_u32(dev, "rockchip,active-vp", &vfb->vp_id);

    if (vfb->soc && vfb->vp_id >= vfb->soc->vp_count)
    {
        vfb->vp_id = 0;
    }

    if (!vfb->display_w || !vfb->display_h)
    {
        return -RT_EINVAL;
    }

    return RT_EOK;
}

static rt_bool_t vop2fb_route_is_legacy_hdmi(struct rt_ofw_node *connector_np)
{
    if (!connector_np)
    {
        return RT_FALSE;
    }

    return rt_ofw_node_is_compatible(connector_np, "rockchip,rk3568-dw-hdmi") ||
           rt_ofw_node_is_compatible(connector_np, "rockchip,rk3528-dw-hdmi");
}

#if DBG_LVL >= DBG_LOG
static const char *vop2fb_output_name(enum vop2fb_output_if output_if)
{
    switch (output_if)
    {
    case VOP2FB_OUTPUT_HDMI:
        return "hdmi";
    case VOP2FB_OUTPUT_EDP:
        return "edp";
    case VOP2FB_OUTPUT_MIPI0:
        return "mipi0";
    case VOP2FB_OUTPUT_MIPI1:
        return "mipi1";
    case VOP2FB_OUTPUT_LVDS:
        return "lvds";
    case VOP2FB_OUTPUT_RGB:
        return "rgb";
    default:
        return "none";
    }
}
#endif /* DBG_LVL >= DBG_LOG */

static enum vop2fb_output_if vop2fb_output_from_connector(struct rt_ofw_node *connector_np)
{
    rt_uint64_t addr;

    if (!connector_np)
    {
        return VOP2FB_OUTPUT_NONE;
    }

    if (vop2fb_route_is_legacy_hdmi(connector_np))
    {
        return VOP2FB_OUTPUT_HDMI;
    }

    if (rt_ofw_node_is_compatible(connector_np, "rockchip,rk3568-edp"))
    {
        return VOP2FB_OUTPUT_EDP;
    }

    if (rt_ofw_node_is_compatible(connector_np, "rockchip,rk3568-lvds"))
    {
        return VOP2FB_OUTPUT_LVDS;
    }

    if (rt_ofw_node_is_compatible(connector_np, "rockchip,rk3568-rgb"))
    {
        return VOP2FB_OUTPUT_RGB;
    }

    if (rt_ofw_node_is_compatible(connector_np, "rockchip,rk3568-mipi-dsi"))
    {
        if (!rt_ofw_get_address(connector_np, 0, &addr, RT_NULL) &&
                addr == 0xfe070000ULL)
        {
            return VOP2FB_OUTPUT_MIPI1;
        }

        return VOP2FB_OUTPUT_MIPI0;
    }

    return VOP2FB_OUTPUT_NONE;
}

static rt_err_t vop2fb_probe(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_bool_t irq_ready = RT_FALSE;
    rt_uint32_t vp_id;
    char ipc_name[RT_NAME_MAX];
    struct rt_device *dev = &pdev->parent;
    struct vop2fb *vfb = rt_calloc(1, sizeof(*vfb));

    if (!vfb)
    {
        return -RT_ENOMEM;
    }

    vfb->dev = dev;
    vfb->soc = vop2fb_soc_from_id(pdev->id);

    if (!vfb->soc)
    {
        err = -RT_ENOSYS;
        goto _fail;
    }

    if ((err = vop2fb_parse_display(vfb, pdev)))
    {
        goto _fail;
    }

    vfb->regs = rt_ofw_iomap(dev->ofw_node, 0);

    if (!vfb->regs)
    {
        err = -RT_EIO;
        goto _fail;
    }

    vfb->regsbak = rt_calloc(vfb->soc->regbak_words, sizeof(rt_uint32_t));

    if (!vfb->regsbak)
    {
        err = -RT_ENOMEM;
        goto _fail_unmap;
    }

    vfb->clks = rt_clk_get_array(dev);

    if (rt_is_err(vfb->clks))
    {
        err = rt_ptr_err(vfb->clks);
        goto _fail_regsbak;
    }

    vfb->irq = vop2fb_request_irq(vfb, dev);
    rt_spin_lock_init(&vfb->reg_lock);

    vfb->parent.ops = &vop2fb_ops;
    vfb->parent.parent.ofw_node = dev->ofw_node;

    if ((err = vop2fb_clk_enable(vfb)))
    {
        goto _fail_clks;
    }

    vfb->powered = RT_TRUE;
    vop2fb_regsbak_sync(vfb);
    vop2fb_rk3568_irqs_quiesce(vfb);

    vop2fb_axi_init_all(vfb);
    vop2fb_overlay_init(vfb);
    vop2fb_parse_port_planes(vfb, dev->ofw_node, vfb->vp_id);

    vfb->overlay_count = rt_min_t(rt_size_t, vfb->soc->overlay_count, VOP2FB_OVERLAY_MAX);
    pdev->parent.user_data = vfb;

    for (vp_id = 0; vp_id < vfb->soc->vp_count &&
            vp_id < VOP2FB_VP_MAX; ++vp_id)
    {
        struct vop2fb_vp_state *state = &vfb->vp[vp_id];

        state->vfb = vfb;
        state->vp_id = vp_id;

        if (vfb->irq < 0)
        {
            continue;
        }

        rt_snprintf(ipc_name, sizeof(ipc_name), "vop-vs%u", vp_id);
        if ((err = rt_sem_init(&state->vsync_sem, ipc_name, 0,
                RT_IPC_FLAG_FIFO)))
        {
            goto _fail_clk;
        }

        rt_snprintf(ipc_name, sizeof(ipc_name), "vop-vl%u", vp_id);
        if ((err = rt_mutex_init(&state->vsync_lock, ipc_name,
                RT_IPC_FLAG_PRIO)))
        {
            rt_sem_detach(&state->vsync_sem);
            goto _fail_clk;
        }

        state->ipc_ready = RT_TRUE;
    }

    /*
     * Publish the CRTC only after every resource needed by a route exists.
     * Otherwise a plane allocation failure leaves a global display entity
     * pointing at the vfb object freed by the probe error path.
     */
    if ((err = rockchip_display_register_crtc(dev->ofw_node, &vop2fb_crtc_ops, vfb)))
    {
        goto _fail_clk;
    }

    /*
     * Keep this last, matching Linux.  A level interrupt may run as soon as
     * GIC is unmasked, so all objects touched by the handler must be ready.
     */
    if (vfb->irq >= 0)
    {
        rt_hw_interrupt_install(vfb->irq, vop2fb_isr, vfb, "vop2");
        rt_hw_interrupt_umask(vfb->irq);
        irq_ready = RT_TRUE;
    }

    LOG_I("VOP2 %s: max %ux%u, primary=%s, %u overlays, cursor=%s, per-VP fb on route complete",
            vfb->soc->version, vfb->display_w, vfb->display_h,
            vfb->soc->primary->name, (unsigned)vfb->overlay_count,
            vfb->soc->cursor->name);

    return RT_EOK;

_fail_clk:
    (void)vop2fb_cleanup_planes(vfb);
    if (irq_ready)
    {
        rt_hw_interrupt_mask(vfb->irq);
    }
    for (vp_id = 0; vp_id < vfb->soc->vp_count &&
            vp_id < VOP2FB_VP_MAX; ++vp_id)
    {
        if (vfb->vp[vp_id].ipc_ready)
        {
            rt_sem_detach(&vfb->vp[vp_id].vsync_sem);
            rt_mutex_detach(&vfb->vp[vp_id].vsync_lock);
            vfb->vp[vp_id].ipc_ready = RT_FALSE;
        }
    }
    vop2fb_rk3568_irqs_quiesce(vfb);
    vop2fb_clk_disable(vfb);
_fail_clks:
    if (!rt_is_err_or_null(vfb->clks))
    {
        rt_clk_array_put(vfb->clks);
    }
_fail_regsbak:
    rt_free(vfb->regsbak);
_fail_unmap:
    if (vfb->regs)
    {
        rt_iounmap(vfb->regs);
    }
_fail:
    pdev->parent.user_data = RT_NULL;
    rt_free(vfb);

    return err;
}

static rt_err_t vop2fb_remove(struct rt_platform_device *pdev)
{
    rt_err_t err;
    rt_uint32_t vp_id;
    struct vop2fb *vfb = pdev->parent.user_data;

    if (!vfb)
    {
        return RT_EOK;
    }

    err = vop2fb_cleanup_planes(vfb);
    if (err)
    {
        return err;
    }

    if (vfb->irq >= 0)
    {
        rt_hw_interrupt_mask(vfb->irq);
    }

    for (vp_id = 0; vp_id < vfb->soc->vp_count &&
            vp_id < VOP2FB_VP_MAX; ++vp_id)
    {
        if (vfb->vp[vp_id].ipc_ready)
        {
            rt_sem_detach(&vfb->vp[vp_id].vsync_sem);
            rt_mutex_detach(&vfb->vp[vp_id].vsync_lock);
            vfb->vp[vp_id].ipc_ready = RT_FALSE;
        }
    }

    vop2fb_rk3568_irqs_quiesce(vfb);

    for (vp_id = 0; vp_id < vfb->soc->vp_count &&
            vp_id < VOP2FB_VP_MAX; ++vp_id)
    {
        vop2fb_vp_clk_disable(vfb, vp_id);
    }
    vop2fb_clk_disable(vfb);

    if (!rt_is_err_or_null(vfb->clks))
    {
        rt_clk_array_put(vfb->clks);
    }

    rt_iounmap(vfb->regs);
    rt_free(vfb->regsbak);
    rt_free(vfb);

    pdev->parent.user_data = RT_NULL;

    return RT_EOK;
}

static const struct rt_ofw_node_id vop2_ofw_ids[] =
{
    { .compatible = "rockchip,rk3568-vop" },
    { .compatible = "rockchip,rk3588-vop" },
    { .compatible = "rockchip,rk3528-vop" },
    { .compatible = "rockchip,rk3562-vop" },
    { .compatible = "rockchip,rk3576-vop" },
    { /* sentinel */ }
};

static struct rt_platform_driver vop2_driver =
{
    .name = "vop2-framebuffer",
    .ids = vop2_ofw_ids,

    .probe = vop2fb_probe,
    .remove = vop2fb_remove,
};
RT_PLATFORM_DRIVER_EXPORT(vop2_driver);
