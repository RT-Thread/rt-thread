/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#ifndef __FB_VOP2_H__
#define __FB_VOP2_H__

#include "rockchip-display.h"

#define VOP2FB_CURSOR_W                 64
#define VOP2FB_CURSOR_H                 64

#define VOP2FB_OVERLAY_MAX              6
#define VOP2FB_VP_MAX                   4

/* System */
#define VOP2_REG_CFG_DONE               0x000
#define VOP2_CFG_DONE_EN                RT_BIT(15)

#define VOP2_EN_MASK                    1

/* Cluster layer (RK3568 layout) */
#define VOP2_CLUSTER0_BASE              0x1000
#define VOP2_CLUSTER_STRIDE             0x200

#define VOP2_CLUSTER_WIN0_CTRL0         0x00
#define VOP2_CLUSTER_WIN0_CTRL2         0x08
#define VOP2_CLUSTER_WIN0_YRGB_MST      0x10
#define VOP2_CLUSTER_WIN0_VIR           0x18
#define VOP2_CLUSTER_WIN0_ACT_INFO      0x20
#define VOP2_CLUSTER_WIN0_DSP_INFO      0x24
#define VOP2_CLUSTER_WIN0_DSP_ST        0x28
#define VOP2_CLUSTER_CTRL               0x100
#define VOP2_CLUSTER_EN_SHIFT           0

#define VOP2_CLUSTER_AXI_ID_SHIFT       13
#define VOP2_CLUSTER_AXI_YRGB_ID_SHIFT  0
#define VOP2_CLUSTER_AXI_UV_ID_SHIFT    5
#define VOP2_CLUSTER_AXI_YRGB_ID_MASK   0x1f
#define VOP2_CLUSTER_AXI_UV_ID_MASK     0x1f
#define VOP2_CLUSTER_AXI_ID_MASK        0x1

/* Esmart / Smart shared region layout */
#define VOP2_ESMART0_BASE               0x1800
#define VOP2_SMART0_BASE                0x1C00
#define VOP2_ESMART_STRIDE              0x200
#define VOP2_SMART_STRIDE               0x200

#define VOP2_ESMART_CTRL0               0x00
#define VOP2_ESMART_AXI_CTRL            0x08
#define VOP2_ESMART_CTRL1               0x04
#define VOP2_ESMART_AXI_ID_SHIFT        1
#define VOP2_ESMART_AXI_YRGB_ID_SHIFT   0
#define VOP2_ESMART_AXI_UV_ID_SHIFT     12
#define VOP2_ESMART_AXI_ID_MASK         0x1
#define VOP2_ESMART_AXI_YRGB_ID_MASK    0x1f
#define VOP2_ESMART_AXI_UV_ID_MASK      0x1f
#define VOP2_RGB2YUV_EN_SHIFT           1
#define VOP2_CSC_MODE_SHIFT             2
#define VOP2_CSC_MODE_MASK              0x3

#define VOP2_REGION0_CTRL               0x10
#define VOP2_REGION0_YRGB_MST           0x14
#define VOP2_REGION0_CBR_MST            0x18
#define VOP2_REGION0_VIR                0x1c
#define VOP2_REGION0_ACT_INFO           0x20
#define VOP2_REGION0_DSP_INFO           0x24
#define VOP2_REGION0_DSP_ST             0x28
#define VOP2_REGION0_SCL_CTRL           0x30
#define VOP2_REGION0_SCL_FACTOR_YRGB    0x34
#define VOP2_REGION0_SCL_FACTOR_CBR     0x38
#define VOP2_REGION0_SCL_OFFSET         0x3c
#define VOP2_YMIRROR_EN_SHIFT           31

#define VOP2_WIN_EN_SHIFT               0
#define VOP2_WIN_FORMAT_MASK            0x1f
#define VOP2_WIN_FORMAT_SHIFT           1
#define VOP2_REGION0_DITHER_UP_EN_SHIFT 12
#define VOP2_REGION0_RB_SWAP_SHIFT      14
#define VOP2_YRGB_GT2_SHIFT             8
#define VOP2_YRGB_GT4_SHIFT             9

enum vop2fb_soc
{
    VOP2FB_SOC_RK3568 = 0,
    VOP2FB_SOC_RK3588,
    VOP2FB_SOC_RK3528,
    VOP2FB_SOC_RK3562,
    VOP2FB_SOC_RK3576,
};

enum vop2fb_layer_type
{
    VOP2FB_LAYER_CLUSTER = 0,
    VOP2FB_LAYER_ESMART,
    VOP2FB_LAYER_SMART,
};

enum vop2fb_hw_format
{
    VOP2FB_FMT_ARGB8888 = 0,
    VOP2FB_FMT_RGB888,
    VOP2FB_FMT_RGB565,
};

enum vop2fb_output_if
{
    VOP2FB_OUTPUT_NONE = 0,
    VOP2FB_OUTPUT_HDMI,
    VOP2FB_OUTPUT_EDP,
    VOP2FB_OUTPUT_MIPI0,
    VOP2FB_OUTPUT_MIPI1,
    VOP2FB_OUTPUT_LVDS,
    VOP2FB_OUTPUT_RGB,
};

struct vop2fb_win_desc
{
    const char *name;
    enum vop2fb_layer_type type;
    rt_uint32_t base_offset;
    rt_uint8_t layer_sel_id;
    rt_uint8_t win_sel_port_offset;
    rt_uint8_t z_order;
    rt_uint8_t axi_id;
    rt_uint8_t axi_yrgb_id;
    rt_uint8_t axi_uv_id;
    rt_int8_t plane_id;
    rt_uint32_t mix_alpha_reg;
};

struct vop2fb_soc_data
{
    enum vop2fb_soc soc;
    const char *version;
    rt_size_t reg_size;
    rt_size_t regbak_words;
    const struct vop2fb_win_desc *primary;
    const struct vop2fb_win_desc *cursor;
    const struct vop2fb_win_desc *overlays;
    rt_size_t overlay_count;
    const struct vop2fb_win_desc *const *route_windows;
    rt_size_t route_window_count;
    rt_bool_t axi_config;
    rt_bool_t irq_by_vp;
    rt_uint32_t vp_count;
};

struct vop2fb;

struct vop2fb_plane_priv
{
    struct vop2fb *vfb;
    const struct vop2fb_win_desc *desc;
    rt_ubase_t dma_handle;
    rt_ubase_t dma_flags;
    rt_uint32_t pan_offset;
    rt_uint32_t vp_id;
    rt_bool_t enabled;
};

struct vop2fb_vp_state
{
    struct display_timing timing;
    enum vop2fb_output_if output_if;
    const struct vop2fb_win_desc *scanout;
    struct vop2fb *vfb;
    struct rt_graphic_device auxiliary;
    struct rt_graphic_device *graphic;
    struct rt_graphic_plane *primary;
    rt_atomic_t vsync;
    struct rt_semaphore vsync_sem;
    struct rt_mutex vsync_lock;
    rt_uint32_t vp_id;
    rt_bool_t mode_valid;
    rt_bool_t enabled;
    rt_bool_t dclk_enabled;
    rt_bool_t ipc_ready;
    rt_bool_t registered;
};

struct vop2fb
{
    struct rt_graphic_device parent;
    struct rt_device *dev;

    const struct vop2fb_soc_data *soc;

    void *regs;
    rt_uint32_t *regsbak;

    rt_uint32_t display_w;
    rt_uint32_t display_h;
    rt_uint32_t vp_id;

    rt_uint32_t hw_format;
    enum vop2fb_output_if output_if;

    struct display_timing output_tim;
    rt_bool_t output_tim_valid;
    struct vop2fb_vp_state vp[VOP2FB_VP_MAX];
    rt_uint32_t configured_vp_mask;
    rt_uint32_t active_vp_mask;

    rt_bool_t clk_enabled;
    struct rt_clk_array *clks;
    struct rt_spinlock reg_lock;

    int irq;
    rt_uint32_t post_buf_empty_count[VOP2FB_VP_MAX];
    rt_uint32_t axi_bus_error_count[2];

    struct rt_graphic_plane *primary;
    struct rt_graphic_plane *cursor;
    struct rt_graphic_plane *overlays[VOP2FB_OVERLAY_MAX];
    rt_size_t overlay_count;

    rt_bool_t registered;
    rt_bool_t powered;
};

rt_uint32_t vop2fb_mode_to_hw(rt_uint32_t mode);
rt_uint32_t vop2fb_hw_to_bpp(rt_uint32_t hw_fmt);

rt_inline void vop2fb_reg_write(struct vop2fb *vfb, rt_uint32_t offset, rt_uint32_t v)
{
    rt_uint32_t idx = offset >> 2;

    HWREG32((rt_uint8_t *)vfb->regs + offset) = v;

    if (vfb->regsbak && idx < vfb->soc->regbak_words)
    {
        vfb->regsbak[idx] = v;
    }
}

rt_inline void vop2fb_mask_write(struct vop2fb *vfb, rt_uint32_t offset,
        rt_uint32_t mask, rt_uint32_t shift, rt_uint32_t v)
{
    rt_uint32_t idx = offset >> 2;
    rt_uint32_t cached, newv;

    if (!mask || !vfb->regsbak || idx >= vfb->soc->regbak_words)
    {
        return;
    }

    cached = vfb->regsbak[idx];
    newv = (cached & ~(mask << shift)) | ((v & mask) << shift);
    vop2fb_reg_write(vfb, offset, newv);
}

rt_inline rt_uint32_t vop2fb_cfg_done_pending(struct vop2fb *vfb)
{
    /*
     * RK3568 VP done bits have no hiword write mask.  Preserve any update
     * that another VP has queued but has not latched at frame start yet.
     */
    if (vfb && vfb->regs && vfb->soc &&
            vfb->soc->soc == VOP2FB_SOC_RK3568)
    {
        return HWREG32((rt_uint8_t *)vfb->regs + VOP2_REG_CFG_DONE) & 0x7;
    }

    return 0;
}

rt_inline rt_uint32_t vop2fb_cfg_done_vp_val(struct vop2fb *vfb, rt_uint32_t vp)
{
    if (vfb && vfb->soc && vfb->soc->soc == VOP2FB_SOC_RK3568)
    {
        return VOP2_CFG_DONE_EN | RT_BIT(vp) | vop2fb_cfg_done_pending(vfb);
    }

    return VOP2_CFG_DONE_EN | RT_BIT(vp) | (RT_BIT(vp) << 16);
}

rt_inline rt_uint32_t vop2fb_cfg_done_val(struct vop2fb *vfb)
{
    return vop2fb_cfg_done_vp_val(vfb, vfb->vp_id);
}

rt_inline rt_uint32_t vop2fb_cfg_done_mask_val(struct vop2fb *vfb,
        rt_uint32_t vp_mask)
{
    if (vfb && vfb->soc && vfb->soc->soc == VOP2FB_SOC_RK3568)
    {
        return VOP2_CFG_DONE_EN | vp_mask | vop2fb_cfg_done_pending(vfb);
    }

    return VOP2_CFG_DONE_EN | vp_mask | (vp_mask << 16);
}

#endif /* __FB_VOP2_H__ */
