/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#include "fb-vop2-vp.h"

#define DBG_TAG "fb.vop2.vp"
#define DBG_LVL DBG_INFO
#include <rtdbg.h>

#define VOP2_CLUSTER0_MIX_SRC_ALPHA    0x618
#define VOP2_MIX0_SRC_ALPHA            0x658
#define VOP2_MIX_ALPHA_STRIDE          0x8

#define VOP2_VP_CLK_CTRL               0xC0C
#define VOP2_PLL_LIMIT_HZ              594000000UL
#define RK3568_NR_MIXERS               5

static rt_uint16_t vop2fb_scl_cal_scale2(rt_uint32_t src, rt_uint32_t dst)
{
    if (src <= 1 || dst <= 1)
    {
        return 0x1000;
    }

    return (rt_uint16_t)(((src - 1) << 12) / (dst - 1));
}

static rt_uint8_t vop2fb_rk3576_pixel_rate(rt_uint32_t vp_id)
{
    return vp_id == 0 ? 2 : 1;
}

static void vop2fb_reg_field(struct vop2fb *vfb, rt_uint32_t offset,
        rt_uint32_t mask, rt_uint32_t shift, rt_uint32_t v)
{
    rt_uint32_t regv = HWREG32((rt_uint8_t *)vfb->regs + offset);

    regv &= ~(mask << shift);
    regv |= (v & mask) << shift;
    vop2fb_reg_write(vfb, offset, regv);
}

static rt_uint32_t vop2fb_output_pol(const struct display_timing *tim)
{
    rt_uint32_t pol = 0;

    if (!tim)
    {
        return 0;
    }

    if (tim->flags & DISPLAY_TIMING_F_PHSYNC)
    {
        pol |= RK3568_HSYNC_POSITIVE;
    }

    if (tim->flags & DISPLAY_TIMING_F_PVSYNC)
    {
        pol |= RK3568_VSYNC_POSITIVE;
    }

    return pol;
}

static rt_uint32_t vop2fb_vp_out_mode(struct vop2fb *vfb)
{
    if (!vfb || !vfb->soc)
    {
        return RK3576_VP_OUT_MODE_P888;
    }

    /*
     * Keep RK3568 HDMI aligned with Linux/U-Boot: RGB888 over HDMI uses
     * OUT_MODE_AAAA instead of plain P888.
     */
    if (vfb->soc->soc == VOP2FB_SOC_RK3568 &&
        vfb->output_if == VOP2FB_OUTPUT_HDMI)
    {
        return RK3568_VP_OUT_MODE_AAAA;
    }

    return RK3576_VP_OUT_MODE_P888;
}

static void vop2fb_rk3568_disable_outputs(struct vop2fb *vfb)
{
    vop2fb_mask_write(vfb, RK3568_DSP_IF_EN, 1, RK3568_RGB_EN_SHIFT, 0);
    vop2fb_mask_write(vfb, RK3568_DSP_IF_EN, 1, RK3568_HDMI0_EN_SHIFT, 0);
    vop2fb_mask_write(vfb, RK3568_DSP_IF_EN, 1, RK3568_EDP0_EN_SHIFT, 0);
    vop2fb_mask_write(vfb, RK3568_DSP_IF_EN, 1, RK3568_MIPI0_EN_SHIFT, 0);
    vop2fb_mask_write(vfb, RK3568_DSP_IF_EN, 1, RK3568_LVDS0_EN_SHIFT, 0);
    vop2fb_mask_write(vfb, RK3568_DSP_IF_EN, 1, RK3568_MIPI1_EN_SHIFT, 0);
    vop2fb_mask_write(vfb, RK3568_DSP_IF_EN, 1, RK3568_LVDS1_EN_SHIFT, 0);
}

void vop2fb_output_disable(struct vop2fb *vfb, enum vop2fb_output_if output_if)
{
    rt_uint32_t shift;

    if (!vfb || !vfb->soc || vfb->soc->soc != VOP2FB_SOC_RK3568)
    {
        return;
    }

    switch (output_if)
    {
    case VOP2FB_OUTPUT_HDMI:
        shift = RK3568_HDMI0_EN_SHIFT;
        break;
    case VOP2FB_OUTPUT_EDP:
        shift = RK3568_EDP0_EN_SHIFT;
        break;
    case VOP2FB_OUTPUT_MIPI0:
        shift = RK3568_MIPI0_EN_SHIFT;
        break;
    case VOP2FB_OUTPUT_MIPI1:
        shift = RK3568_MIPI1_EN_SHIFT;
        break;
    case VOP2FB_OUTPUT_LVDS:
        shift = RK3568_LVDS0_EN_SHIFT;
        break;
    case VOP2FB_OUTPUT_RGB:
        shift = RK3568_RGB_EN_SHIFT;
        break;
    default:
        return;
    }

    vop2fb_mask_write(vfb, RK3568_DSP_IF_EN, 1, shift, 0);
}

static void vop2fb_rk3568_if_cfg(struct vop2fb *vfb, rt_uint32_t vp_id,
        const struct display_timing *tim)
{
    rt_uint32_t dclk_inv, pol;

    if (!vfb || !tim || vfb->soc->soc != VOP2FB_SOC_RK3568)
    {
        return;
    }

    pol = vop2fb_output_pol(tim);
    dclk_inv = !!(tim->flags & DISPLAY_TIMING_F_PIXDATA_NEGEDGE);

    /*
     * Clear inherited bootloader routing for the first configured VP only.
     * Later mode sets must preserve already-running outputs (for example
     * HDMI0 on VP0 while MIPI1 is attached to VP1).
     */
    if (!vfb->configured_vp_mask)
    {
        vop2fb_rk3568_disable_outputs(vfb);
    }
    vop2fb_mask_write(vfb, RK3568_DSP_IF_POL, 1,
            RK3568_IF_CTRL_REG_DONE_IMD_SHIFT, 1);

    switch (vfb->output_if)
    {
    case VOP2FB_OUTPUT_HDMI:
        vop2fb_mask_write(vfb, RK3568_DSP_IF_EN, 1, RK3568_HDMI0_EN_SHIFT, 1);
        vop2fb_mask_write(vfb, RK3568_DSP_IF_EN, RK3568_IF_MUX_MASK,
                RK3568_HDMI0_MUX_SHIFT, vp_id);
        vop2fb_mask_write(vfb, RK3568_DSP_IF_POL, 1,
                RK3568_IF_CRTL_HDMI_DCLK_POL_SHIFT, 1);
        vop2fb_mask_write(vfb, RK3568_DSP_IF_POL, RK3568_IF_PIN_POL_MASK,
                RK3568_IF_CRTL_HDMI_PIN_POL_SHIFT, pol);
        break;

    case VOP2FB_OUTPUT_EDP:
        vop2fb_mask_write(vfb, RK3568_DSP_IF_EN, 1, RK3568_EDP0_EN_SHIFT, 1);
        vop2fb_mask_write(vfb, RK3568_DSP_IF_EN, RK3568_IF_MUX_MASK,
                RK3568_EDP0_MUX_SHIFT, vp_id);
        vop2fb_mask_write(vfb, RK3568_DSP_IF_POL, 1,
                RK3568_IF_CRTL_EDP_DCLK_POL_SHIFT, 1);
        vop2fb_mask_write(vfb, RK3568_DSP_IF_POL, RK3568_IF_PIN_POL_MASK,
                RK3568_IF_CTRL_EDP_PIN_POL_SHIFT, pol);
        break;

    case VOP2FB_OUTPUT_MIPI0:
        vop2fb_mask_write(vfb, RK3568_DSP_IF_EN, 1, RK3568_MIPI0_EN_SHIFT, 1);
        vop2fb_mask_write(vfb, RK3568_DSP_IF_EN, RK3568_IF_MUX_MASK,
                RK3568_MIPI0_MUX_SHIFT, vp_id);
        vop2fb_mask_write(vfb, RK3568_DSP_IF_POL, 1,
                RK3568_IF_CRTL_MIPI_DCLK_POL_SHIFT, dclk_inv);
        vop2fb_mask_write(vfb, RK3568_DSP_IF_POL, RK3568_IF_PIN_POL_MASK,
                RK3568_IF_CTRL_MIPI_PIN_POL_SHIFT, pol);
        break;

    case VOP2FB_OUTPUT_MIPI1:
        vop2fb_mask_write(vfb, RK3568_DSP_IF_EN, 1, RK3568_MIPI1_EN_SHIFT, 1);
        vop2fb_mask_write(vfb, RK3568_DSP_IF_EN, RK3568_IF_MUX_MASK,
                RK3568_MIPI1_MUX_SHIFT, vp_id);
        vop2fb_mask_write(vfb, RK3568_DSP_IF_POL, 1,
                RK3568_IF_CRTL_MIPI_DCLK_POL_SHIFT, dclk_inv);
        vop2fb_mask_write(vfb, RK3568_DSP_IF_POL, RK3568_IF_PIN_POL_MASK,
                RK3568_IF_CTRL_MIPI_PIN_POL_SHIFT, pol);
        break;

    case VOP2FB_OUTPUT_LVDS:
        vop2fb_mask_write(vfb, RK3568_DSP_IF_EN, 1, RK3568_LVDS0_EN_SHIFT, 1);
        vop2fb_mask_write(vfb, RK3568_DSP_IF_EN, RK3568_IF_MUX_MASK,
                RK3568_LVDS0_MUX_SHIFT, vp_id);
        vop2fb_mask_write(vfb, RK3568_DSP_IF_POL, RK3568_IF_PIN_POL_MASK,
                RK3568_IF_CTRL_RGB_PIN_POL_SHIFT, pol);
        break;

    case VOP2FB_OUTPUT_RGB:
        vop2fb_mask_write(vfb, RK3568_DSP_IF_EN, 1, RK3568_RGB_EN_SHIFT, 1);
        vop2fb_mask_write(vfb, RK3568_DSP_IF_EN, RK3568_IF_MUX_MASK,
                RK3568_RGB_MUX_SHIFT, vp_id);
        vop2fb_mask_write(vfb, RK3568_DSP_IF_POL, RK3568_IF_PIN_POL_MASK,
                RK3568_IF_CTRL_RGB_PIN_POL_SHIFT, pol);
        break;

    default:
        break;
    }
}

void vop2fb_vp_irq_ctrl(struct vop2fb *vfb, rt_uint32_t vp_id, rt_bool_t enable)
{
    rt_uint32_t axi_irq = RK3568_SYS_BUS_ERROR_INTR;
    rt_uint32_t clear_irqs = VOP2_VP_FS_FIELD_INTR |
            VOP2_VP_POST_BUF_EMPTY_INTR;
    rt_uint32_t enable_irqs = VOP2_VP_FS_FIELD_INTR;

    if (!vfb || vfb->soc->soc != VOP2FB_SOC_RK3568 || vp_id >= vfb->soc->vp_count)
    {
        return;
    }

    HWREG32((rt_uint8_t *)vfb->regs + RK3568_VP_INT_CLR(vp_id)) =
            (clear_irqs << 16) | clear_irqs;
    HWREG32((rt_uint8_t *)vfb->regs + RK3568_SYS0_INT_CLR) = axi_irq << 16 | axi_irq;
    HWREG32((rt_uint8_t *)vfb->regs + RK3568_SYS1_INT_CLR) = axi_irq << 16 | axi_irq;

    if (enable)
    {
        /*
         * POST_BUF_EMPTY is diagnostic-only in Linux and may generate an
         * interrupt storm while no plane is scanning out.  RT has no Linux
         * recovery workqueue, so keep it masked and use FS_FIELD for vsync.
         */
        HWREG32((rt_uint8_t *)vfb->regs + RK3568_VP_INT_EN(vp_id)) =
                (clear_irqs << 16) | enable_irqs;
        HWREG32((rt_uint8_t *)vfb->regs + RK3568_SYS0_INT_EN) = axi_irq << 16 | axi_irq;
        HWREG32((rt_uint8_t *)vfb->regs + RK3568_SYS1_INT_EN) = axi_irq << 16 | axi_irq;
    }
    else
    {
        HWREG32((rt_uint8_t *)vfb->regs + RK3568_VP_INT_EN(vp_id)) =
                clear_irqs << 16;
        HWREG32((rt_uint8_t *)vfb->regs + RK3568_SYS0_INT_EN) = axi_irq << 16;
        HWREG32((rt_uint8_t *)vfb->regs + RK3568_SYS1_INT_EN) = axi_irq << 16;
    }
}

static void vop2fb_rk3568_dither_setup(struct vop2fb *vfb, rt_uint32_t vp_id)
{
    rt_uint32_t base;
    rt_bool_t pre_dither_down_en;

    if (!vfb || !vfb->regs || !vfb->soc || vfb->soc->soc != VOP2FB_SOC_RK3568)
    {
        return;
    }

    /*
     * The current RT display stack only drives 24-bit RGB style outputs on
     * RK3568. Match Linux/U-Boot and keep pre-dither enabled so VP0_DSP_CTRL
     * aligns with the working Linux value (for HDMI 1280x720p60 this is
     * 0x0001000f instead of 0x0000000f).
     */
    pre_dither_down_en = vfb->output_if != VOP2FB_OUTPUT_NONE;
    base = VOP2_VP_DSP_CTRL + vp_id * VOP2FB_VP_STRIDE;

    vop2fb_mask_write(vfb, base, 1, VOP2_VP_PRE_DITHER_DOWN_EN_SHIFT,
            pre_dither_down_en ? 1 : 0);
    vop2fb_mask_write(vfb, base, 1, VOP2_VP_DITHER_DOWN_EN_SHIFT, 0);
}

#if DBG_LVL >= DBG_LOG
static void vop2fb_rk3568_dump_route_regs(struct vop2fb *vfb, rt_uint32_t vp_id)
{
    rt_uint32_t base;

    if (!vfb || !vfb->regs || !vfb->soc || vfb->soc->soc != VOP2FB_SOC_RK3568)
    {
        return;
    }

    base = VOP2_VP_DSP_CTRL + vp_id * VOP2FB_VP_STRIDE;

    LOG_D("VP%u route regs: IF_EN=0x%08x IF_POL=0x%08x OVL_SEL=0x%08x OVL_PORT=0x%08x OVL_CTRL=0x%08x DSP_CTRL=0x%08x DSP_BG=0x%08x",
            vp_id,
            HWREG32((rt_uint8_t *)vfb->regs + RK3568_DSP_IF_EN),
            HWREG32((rt_uint8_t *)vfb->regs + RK3568_DSP_IF_POL),
            HWREG32((rt_uint8_t *)vfb->regs + VOP2_OVL_LAYER_SEL),
            HWREG32((rt_uint8_t *)vfb->regs + VOP2_OVL_PORT_SEL),
            HWREG32((rt_uint8_t *)vfb->regs + VOP2_OVL_CTRL),
            HWREG32((rt_uint8_t *)vfb->regs + base),
            HWREG32((rt_uint8_t *)vfb->regs + base + (VOP2_VP_DSP_BG - VOP2_VP_DSP_CTRL)));
}
#endif /* DBG_LVL >= DBG_LOG */

static rt_uint32_t vop2fb_rk3568_pre_scan_max_dly(rt_uint32_t vp_id)
{
    switch (vp_id)
    {
    case 0:
        return 42;
    case 1:
    case 2:
        return 40;
    default:
        return 40;
    }
}

static rt_uint32_t vop2fb_rk3568_bg_ovl_dly(struct vop2fb *vfb, rt_uint32_t vp_id)
{
    rt_uint32_t port_mux;

    if (!vfb || !vfb->regs)
    {
        return 0;
    }

    port_mux = (HWREG32((rt_uint8_t *)vfb->regs + VOP2_OVL_PORT_SEL) >> (vp_id * 4)) & 0xf;

    if (port_mux >= RK3568_NR_MIXERS)
    {
        return 0;
    }

    return (RK3568_NR_MIXERS - port_mux) << 1;
}

rt_err_t vop2fb_vp_post_config(struct vop2fb *vfb, rt_uint32_t vp_id,
        const struct display_timing *tim)
{
    rt_uint32_t hdisplay_round2;
    rt_uint32_t hsync_len;
    rt_uint32_t hact_st;
    rt_uint32_t hact_end;
    rt_uint32_t vact_st;
    rt_uint32_t vact_end;
    rt_uint32_t hsync_start;
    rt_uint32_t vsync_start;
    rt_uint32_t hscale;
    rt_uint32_t vscale;
    rt_uint32_t bg_dly;
    rt_uint32_t bg_ovl_dly;
    rt_uint32_t pre_scan_dly;

    if (!vfb || !tim || !vfb->regs || !vfb->soc ||
        vfb->soc->soc != VOP2FB_SOC_RK3568)
    {
        return RT_EOK;
    }

    hdisplay_round2 = (tim->hactive + 1) & ~1u;
    hsync_len = tim->hsync_len ? tim->hsync_len : 1;
    bg_dly = vop2fb_rk3568_pre_scan_max_dly(vp_id);
    bg_ovl_dly = vop2fb_rk3568_bg_ovl_dly(vfb, vp_id);

    if (bg_dly > bg_ovl_dly)
    {
        bg_dly -= bg_ovl_dly;
    }
    else
    {
        bg_dly = 0;
    }

    pre_scan_dly = bg_dly + (hdisplay_round2 >> 1) - 1;
    hsync_start = tim->hactive + tim->hfront_porch;
    vsync_start = tim->vactive + tim->vfront_porch;
    hact_st = tim->htotal - hsync_start;
    hact_end = hact_st + tim->hactive;
    vact_st = tim->vtotal - vsync_start;
    vact_end = vact_st + tim->vactive;
    hscale = vop2fb_scl_cal_scale2(tim->hactive, tim->hactive);
    vscale = vop2fb_scl_cal_scale2(tim->vactive, tim->vactive);

    vop2fb_mask_write(vfb, RK3568_VP0_BG_MIX_CTRL + vp_id * 4,
            RK3568_BG_MIX_CTRL_MASK, RK3568_BG_MIX_CTRL_SHIFT, bg_dly);
    vop2fb_reg_write(vfb, VOP2_VP_DSP_BG + vp_id * VOP2FB_VP_STRIDE, 0);
    vop2fb_reg_write(vfb, RK3568_VP0_POST_DSP_HACT_INFO + vp_id * VOP2FB_VP_STRIDE,
            (hact_st << 16) | hact_end);
    vop2fb_reg_write(vfb, RK3568_VP0_POST_DSP_VACT_INFO + vp_id * VOP2FB_VP_STRIDE,
            (vact_st << 16) | vact_end);
    vop2fb_reg_write(vfb, RK3568_VP0_POST_SCL_FACTOR_YRGB + vp_id * VOP2FB_VP_STRIDE,
            (vscale << 16) | hscale);
    vop2fb_mask_write(vfb, RK3568_VP0_POST_SCL_CTRL + vp_id * VOP2FB_VP_STRIDE,
            1, RK3568_POST_HORIZONTAL_SCALEDOWN_EN_SHIFT, 0);
    vop2fb_mask_write(vfb, RK3568_VP0_POST_SCL_CTRL + vp_id * VOP2FB_VP_STRIDE,
            1, RK3568_POST_VERTICAL_SCALEDOWN_EN_SHIFT, 0);
    vop2fb_reg_write(vfb, RK3568_VP0_PRE_SCAN_HTIMING + vp_id * VOP2FB_VP_STRIDE,
            (pre_scan_dly << 16) | hsync_len);
    vop2fb_reg_write(vfb, VOP2_REG_CFG_DONE,
            vop2fb_cfg_done_vp_val(vfb, vp_id));

#if DBG_LVL >= DBG_LOG
    LOG_D("VP%u post cfg: port_mux=%u bg_ovl_dly=%u bg_dly=%u PRE_SCAN=0x%08x BG_MIX=0x%08x",
            vp_id,
            (HWREG32((rt_uint8_t *)vfb->regs + VOP2_OVL_PORT_SEL) >> (vp_id * 4)) & 0xf,
            bg_ovl_dly, bg_dly,
            HWREG32((rt_uint8_t *)vfb->regs + RK3568_VP0_PRE_SCAN_HTIMING +
                    vp_id * VOP2FB_VP_STRIDE),
            HWREG32((rt_uint8_t *)vfb->regs + RK3568_VP0_BG_MIX_CTRL + vp_id * 4));
    LOG_D("VP%u post regs: HACT=0x%08x VACT=0x%08x SCL=0x%08x SCL_CTRL=0x%08x DSP_BG=0x%08x",
            vp_id,
            HWREG32((rt_uint8_t *)vfb->regs + RK3568_VP0_POST_DSP_HACT_INFO +
                    vp_id * VOP2FB_VP_STRIDE),
            HWREG32((rt_uint8_t *)vfb->regs + RK3568_VP0_POST_DSP_VACT_INFO +
                    vp_id * VOP2FB_VP_STRIDE),
            HWREG32((rt_uint8_t *)vfb->regs + RK3568_VP0_POST_SCL_FACTOR_YRGB +
                    vp_id * VOP2FB_VP_STRIDE),
            HWREG32((rt_uint8_t *)vfb->regs + RK3568_VP0_POST_SCL_CTRL +
                    vp_id * VOP2FB_VP_STRIDE),
            HWREG32((rt_uint8_t *)vfb->regs + VOP2_VP_DSP_BG + vp_id * VOP2FB_VP_STRIDE));
#endif /* DBG_LVL >= DBG_LOG */

    return RT_EOK;
}

static rt_err_t vop2fb_vp_dclk_set_rate(struct vop2fb *vfb, rt_uint32_t vp_id, rt_ubase_t rate)
{
    struct rt_device *dev = &vfb->parent.parent;
    char name[20];
    struct rt_clk *dclk, *src, *parent, *pll;
    rt_err_t err;
    rt_ubase_t actual_rate, pll_rate;
    rt_uint32_t div;

    rt_snprintf(name, sizeof(name), "dclk_vp%u", vp_id);
    dclk = rt_clk_get_by_name(dev, name);

    if (rt_is_err_or_null(dclk))
    {
        rt_snprintf(name, sizeof(name), "dclk_vop%u", vp_id);
        dclk = rt_clk_get_by_name(dev, name);
    }

    if (rt_is_err_or_null(dclk))
    {
        LOG_W("VP%u dclk not found", vp_id);
        return RT_EOK;
    }

    /*
     * RK3568 feeds the DW-HDMI PHY reference clock directly from HPLL.
     * Keep HPLL and dclk_vop0 at the same pixel rate.  A divided 594 MHz HPLL
     * produces the requested VOP dclk but leaves the PHY reference unstable.
     */
    parent = rt_clk_get_parent(dclk);

    if (vfb->soc->soc == VOP2FB_SOC_RK3568 &&
            vfb->output_if == VOP2FB_OUTPUT_HDMI &&
            parent && parent->cell && parent->cell->name &&
            !rt_strcmp(parent->cell->name, "hpll"))
    {
        if ((err = rt_clk_set_rate(parent, rate)))
        {
            LOG_W("VP%u hpll set %lu failed: %s",
                    vp_id, rate, rt_strerror(err));
            goto _put_parent;
        }

        if ((err = rt_clk_set_rate(dclk, rate)))
        {
            LOG_W("VP%u dclk set %lu failed: %s",
                    vp_id, rate, rt_strerror(err));
            goto _put_parent;
        }

        actual_rate = rt_clk_get_rate(dclk);
        if (!actual_rate ||
                (actual_rate > rate ? actual_rate - rate : rate - actual_rate) >
                rate / 1000)
        {
            LOG_E("VP%u dclk mismatch: req %lu actual %lu parent=hpll rate=%lu",
                    vp_id, rate, actual_rate, rt_clk_get_rate(parent));
            err = -RT_EIO;
            goto _put_parent;
        }

        LOG_D("VP%u dclk: req %lu actual %lu parent=hpll rate=%lu",
                vp_id, rate, actual_rate, rt_clk_get_rate(parent));
        rt_clk_put(parent);
        rt_clk_put(dclk);
        return RT_EOK;
    }

    /*
     * RK3568 dclk_vop[0-2] are direct mux/div clocks.  For non-HDMI
     * outputs the device tree selects VPLL so it can be retuned to an
     * integer multiple of the requested pixel clock.  Merely changing the
     * divider leaves the boot-time 594 MHz VPLL in place (70 MHz then
     * becomes 66 MHz), while the DSI host still computes its line timers
     * from 70 MHz.
     */
    if (vfb->soc->soc == VOP2FB_SOC_RK3568 &&
            parent && parent->cell && parent->cell->name &&
            !rt_strcmp(parent->cell->name, "vpll"))
    {
        pll_rate = rt_clk_get_rate(parent);

        if (pll_rate < VOP2_PLL_LIMIT_HZ || (pll_rate % rate) != 0)
        {
            div = (rt_uint32_t)RT_DIV_ROUND_UP(VOP2_PLL_LIMIT_HZ, rate);

            if (div & 1)
            {
                div++;
            }

            pll_rate = rate * div;
            if ((err = rt_clk_set_rate(parent, pll_rate)))
            {
                LOG_W("VP%u vpll set %lu failed: %s",
                        vp_id, pll_rate, rt_strerror(err));
                goto _put_parent;
            }
        }

        if ((err = rt_clk_set_rate(dclk, rate)))
        {
            LOG_W("VP%u dclk set %lu failed: %s",
                    vp_id, rate, rt_strerror(err));
            goto _put_parent;
        }

        if (rt_clk_get_rate(dclk) != rate)
        {
            LOG_W("VP%u dclk mismatch: req %lu actual %lu parent=vpll rate=%lu",
                    vp_id, rate, rt_clk_get_rate(dclk), rt_clk_get_rate(parent));
            err = -RT_EIO;
            goto _put_parent;
        }

        LOG_D("VP%u dclk: req %lu actual %lu parent=vpll rate=%lu",
                vp_id, rate, rt_clk_get_rate(dclk), rt_clk_get_rate(parent));
        rt_clk_put(parent);
        rt_clk_put(dclk);
        return RT_EOK;
    }

    if (parent)
    {
        rt_clk_put(parent);
        parent = RT_NULL;
    }

    rt_snprintf(name, sizeof(name), "dclk_src_vp%u", vp_id);
    src = rt_clk_get_by_name(dev, name);

    if (rt_is_err_or_null(src))
    {
        rt_snprintf(name, sizeof(name), "dclk_vop_src%u", vp_id);
        src = rt_clk_get_by_name(dev, name);
    }

    pll = RT_NULL;

    if (src)
    {
        parent = rt_clk_get_parent(src);

        if (parent)
        {
            pll = rt_clk_get_parent(parent);
        }
    }

    if (pll && pll->cell && pll->cell->name && !rt_strcmp(pll->cell->name, "vpll"))
    {
        pll_rate = rt_clk_get_rate(pll);

        if (pll_rate >= VOP2_PLL_LIMIT_HZ && (pll_rate % rate) == 0)
        {
            rt_clk_set_rate(dclk, rate);
        }
        else
        {
            div = (rt_uint32_t)((VOP2_PLL_LIMIT_HZ + rate - 1) / rate);

            if (div & 1)
            {
                div++;
            }

            rt_clk_set_rate(pll, rate * div);
            rt_clk_set_rate(dclk, rate);
        }
    }
    else
    {
        rt_clk_set_rate(dclk, rate);
    }

    LOG_D("VP%u dclk: req %lu actual %lu", vp_id, rate, rt_clk_get_rate(dclk));

    if (src)
    {
        rt_clk_put(src);
    }

    rt_clk_put(dclk);

    return RT_EOK;

_put_parent:
    if (parent)
    {
        rt_clk_put(parent);
    }
    rt_clk_put(dclk);

    return err;
}

static rt_err_t vop2fb_rk3576_cru_cfg(struct vop2fb *vfb, rt_uint32_t vp_id,
        const struct display_timing *tim)
{
    rt_uint64_t pixclk = tim->pixelclock;
    rt_uint8_t port_pix_rate = vop2fb_rk3576_pixel_rate(vp_id);
    rt_uint32_t clk_ctrl = VOP2_VP_CLK_CTRL + vp_id * VOP2FB_VP_STRIDE;
    rt_ubase_t crtc_hz, dclk_in, dclk_core;
    rt_uint32_t post_dclk_core_sel, post_dclk_out_sel;
    rt_uint32_t interface_dclk_sel, interface_pix_clk_sel;
    rt_uint32_t mipi_val;

    if (!pixclk)
    {
        pixclk = (rt_uint64_t)tim->htotal * tim->vtotal * 60;
    }

    crtc_hz = (rt_ubase_t)pixclk;
    dclk_in = crtc_hz;
    dclk_core = crtc_hz / port_pix_rate;

    post_dclk_core_sel = dclk_in > dclk_core ? 1 : 0;
    post_dclk_out_sel = 0;
    interface_dclk_sel = 0;
    interface_pix_clk_sel = port_pix_rate == 1 ? 1 : 0;

    vop2fb_reg_field(vfb, clk_ctrl, 0x1, 0, post_dclk_core_sel);
    vop2fb_reg_field(vfb, clk_ctrl, 0x1, 2, post_dclk_out_sel);

    mipi_val = RT_BIT(0) | RT_BIT(1) | ((vp_id & 0x3) << 2) | (0x3 << 4) | RT_BIT(31);

    if (interface_pix_clk_sel)
    {
        mipi_val |= RT_BIT(20);
    }

    if (interface_dclk_sel)
    {
        mipi_val |= RT_BIT(21);
    }

    vop2fb_reg_write(vfb, RK3576_MIPI0_IF_CTRL, mipi_val);

    return vop2fb_vp_dclk_set_rate(vfb, vp_id, crtc_hz);
}

rt_err_t vop2fb_vp_mode_set(struct vop2fb *vfb, rt_uint32_t vp_id,
        const struct display_timing *tim)
{
    rt_uint32_t base = VOP2_VP_DSP_CTRL + vp_id * VOP2FB_VP_STRIDE;
    rt_uint32_t hact_st, hact_end, vact_st, vact_end;
    rt_uint32_t hsync_start, vsync_start;
    rt_uint32_t out_mode;
    rt_err_t err;

    if (!vfb || !tim || !vfb->regs)
    {
        return -RT_EINVAL;
    }

    if (tim->pixelclock)
    {
        if ((err = vop2fb_vp_dclk_set_rate(vfb, vp_id,
                (rt_ubase_t)tim->pixelclock)))
        {
            return err;
        }
    }

    /*
     * RK3568 VOP2 expects the active-window start relative to the sync
     * boundary on the back-porch side, matching Linux/U-Boot:
     *
     *   hact_st = htotal - hsync_start = hsync_len + hback_porch
     *   vact_st = vtotal - vsync_start = vsync_len + vback_porch
     *
     * Using front-porch based values here shifts the whole active area and
     * can leave HDMI running with valid clocks but no visible signal.
     */
    hsync_start = tim->hactive + tim->hfront_porch;
    vsync_start = tim->vactive + tim->vfront_porch;

    hact_st = tim->htotal - hsync_start;
    hact_end = hact_st + tim->hactive;
    vact_st = tim->vtotal - vsync_start;
    vact_end = vact_st + tim->vactive;

    out_mode = vop2fb_vp_out_mode(vfb);
    vop2fb_mask_write(vfb, base, VOP2_VP_OUT_MODE_MASK, VOP2_VP_OUT_MODE_SHIFT, out_mode);
    LOG_D("VP%u out_mode=%u if=%d", vp_id, out_mode, vfb->output_if);

    HWREG32((rt_uint8_t *)vfb->regs + base + (VOP2_VP_DSP_HTOTAL_HS_END - VOP2_VP_DSP_CTRL)) =
            (tim->htotal << 16) | tim->hsync_len;

    HWREG32((rt_uint8_t *)vfb->regs + base + (VOP2_VP_DSP_HACT_ST_END - VOP2_VP_DSP_CTRL)) =
            (hact_st << 16) | hact_end;

    HWREG32((rt_uint8_t *)vfb->regs + base + (VOP2_VP_DSP_VACT_ST_END - VOP2_VP_DSP_CTRL)) =
            (vact_st << 16) | vact_end;

    HWREG32((rt_uint8_t *)vfb->regs + base + (VOP2_VP_DSP_VTOTAL_VS_END - VOP2_VP_DSP_CTRL)) =
            (tim->vtotal << 16) | tim->vsync_len;

    LOG_D("VP%u timing regs: HTOTAL_HS=0x%08x HACT=0x%08x VTOTAL_VS=0x%08x VACT=0x%08x",
            vp_id,
            (tim->htotal << 16) | tim->hsync_len,
            (hact_st << 16) | hact_end,
            (tim->vtotal << 16) | tim->vsync_len,
            (vact_st << 16) | vact_end);

    vfb->display_w = tim->hactive;
    vfb->display_h = tim->vactive;

    if (vfb->soc && vfb->soc->soc == VOP2FB_SOC_RK3576)
    {
        vop2fb_rk3576_cru_cfg(vfb, vp_id, tim);
    }
    else
    {
        vop2fb_rk3568_if_cfg(vfb, vp_id, tim);
    }

    vop2fb_rk3568_dither_setup(vfb, vp_id);
#if DBG_LVL >= DBG_LOG
    vop2fb_rk3568_dump_route_regs(vfb, vp_id);
#endif

    return RT_EOK;
}

rt_err_t vop2fb_mipi_output_enable(struct vop2fb *vfb, rt_uint32_t vp_id, rt_bool_t enable)
{
    rt_uint32_t val;

    if (!vfb || !vfb->regs || !enable)
    {
        return RT_EOK;
    }

    /* mipi0_en | dclk_out | mux=vp | hsync/vsync positive | regdone_imd */
    val = RT_BIT(0) | RT_BIT(1) | ((vp_id & 0x3) << 2) | (0x3 << 4) | RT_BIT(31);
    vop2fb_reg_write(vfb, RK3576_MIPI0_IF_CTRL, val);
    vop2fb_reg_write(vfb, VOP2_REG_CFG_DONE,
            vop2fb_cfg_done_vp_val(vfb, vp_id));

    return RT_EOK;
}

rt_err_t vop2fb_vp_enable(struct vop2fb *vfb, rt_uint32_t vp_id, rt_bool_t enable)
{
    rt_uint32_t base = VOP2_VP_DSP_CTRL + vp_id * VOP2FB_VP_STRIDE;

    if (!vfb || !vfb->regs)
    {
        return -RT_EINVAL;
    }

    vop2fb_vp_irq_ctrl(vfb, vp_id, enable);
    vop2fb_mask_write(vfb, base, 1, VOP2_VP_STANDBY_SHIFT, enable ? 0 : 1);
    vop2fb_reg_write(vfb, VOP2_REG_CFG_DONE,
            vop2fb_cfg_done_vp_val(vfb, vp_id));

    return RT_EOK;
}

rt_err_t vop2fb_mix_alpha_set(struct vop2fb *vfb, rt_uint32_t mix_reg, rt_uint8_t alpha)
{
    if (!vfb || !vfb->regs)
    {
        return -RT_EINVAL;
    }

    /*
     * Opaque primary scanout should not rewrite RK3568 mix registers during
     * bring-up. Clearing these registers can turn a valid timing stream into
     * a fully black output, while the bootloader defaults are already good
     * enough for the single-layer path we are using here.
     */
    if (alpha == 0xff)
    {
        return RT_EOK;
    }

    LOG_W("ignore partial alpha=%u on rk3568 simple scanout path", alpha);

    return RT_EOK;
}

struct vop2fb_layer_cfg
{
    const struct vop2fb_win_desc *desc;
    rt_uint32_t z;
};

static void vop2fb_layer_cfg_insert(struct vop2fb_layer_cfg *layers,
        rt_size_t *count, rt_size_t max_layers,
        const struct vop2fb_win_desc *desc, rt_uint32_t z)
{
    rt_size_t i;

    if (!layers || !count || !desc || *count >= max_layers)
    {
        return;
    }

    i = *count;

    while (i > 0 && layers[i - 1].z > z)
    {
        layers[i] = layers[i - 1];
        i--;
    }

    layers[i].desc = desc;
    layers[i].z = z;
    (*count)++;
}

static void vop2fb_collect_plane_cfg(struct vop2fb_layer_cfg *layers,
        rt_size_t *count, rt_size_t max_layers,
        struct rt_graphic_plane *plane)
{
    struct vop2fb_plane_priv *priv;

    if (!plane)
    {
        return;
    }

    priv = (struct vop2fb_plane_priv *)plane->priv;

    if (!priv->desc)
    {
        return;
    }

    if (!priv->enabled || !plane->framebuffer)
    {
        return;
    }

    vop2fb_layer_cfg_insert(layers, count, max_layers, priv->desc, plane->z);
}

rt_err_t vop2fb_overlay_init(struct vop2fb *vfb)
{
    if (!vfb || !vfb->soc)
    {
        return -RT_EINVAL;
    }

    /* RK3568 uses shared OVL_LAYER_SEL; newer VOP2 SoCs use per-VP port blocks. */
    if (vfb->soc->soc == VOP2FB_SOC_RK3568)
    {
        rt_uint32_t active_vps = vfb->active_vp_mask;

        if (active_vps && (active_vps & (active_vps - 1)))
        {
            rt_uint32_t layer_sel = 0;
            rt_uint32_t port_sel = 0;
            rt_uint32_t layer_count[VOP2FB_VP_MAX] = { 0 };
            rt_uint32_t owner, vp_id, used_layers = 0;
            rt_size_t i, slot = 0;

            for (i = 0; i < vfb->soc->route_window_count; ++i)
            {
                layer_sel |= 0x5u << (i * 4);
            }

            /*
             * Layers feeding one VP must occupy adjacent mixer stages.
             * Preserve the canonical RK3568 window order inside each VP,
             * moving only the extra scanout windows to their target VPs.
             */
            for (vp_id = 0; vp_id < vfb->soc->vp_count; ++vp_id)
            {
                for (i = 0; i < vfb->soc->route_window_count; ++i)
                {
                    const struct vop2fb_win_desc *desc =
                            vfb->soc->route_windows[i];
                    rt_uint32_t scanout_vp;

                    owner = vfb->vp_id;

                    for (scanout_vp = 0;
                            scanout_vp < vfb->soc->vp_count &&
                            scanout_vp < VOP2FB_VP_MAX; ++scanout_vp)
                    {
                        if (vfb->vp[scanout_vp].enabled &&
                                vfb->vp[scanout_vp].scanout == desc)
                        {
                            owner = scanout_vp;
                            break;
                        }
                    }

                    if (owner != vp_id)
                    {
                        continue;
                    }

                    layer_sel &= ~(0xfu << (slot * 4));
                    layer_sel |= ((rt_uint32_t)desc->layer_sel_id & 0xfu) <<
                            (slot * 4);
                    port_sel &= ~(0x3u <<
                            (16 + desc->win_sel_port_offset * 2));
                    port_sel |= (owner & 0x3u) <<
                            (16 + desc->win_sel_port_offset * 2);
                    layer_count[owner]++;
                    slot++;
                }
            }

            for (vp_id = 0; vp_id + 1 < vfb->soc->vp_count; ++vp_id)
            {
                rt_uint32_t port_mux;

                used_layers += layer_count[vp_id];
                port_mux = used_layers ? used_layers - 1 : 8;
                port_sel |= (port_mux & 0xfu) << (vp_id * 4);
            }

            /* RK3568 VP2 is hard-wired to the final mixer stage. */
            port_sel |= 7u << ((vfb->soc->vp_count - 1) * 4);

            vop2fb_reg_write(vfb, VOP2_OVL_LAYER_SEL, layer_sel);
            vop2fb_reg_write(vfb, VOP2_OVL_PORT_SEL, port_sel);

            for (vp_id = 0; vp_id < vfb->soc->vp_count; ++vp_id)
            {
                if (active_vps & RT_BIT(vp_id))
                {
                    vop2fb_mask_write(vfb, VOP2_OVL_CTRL, 1,
                            VOP2_OVL_MODE_SEL_SHIFT + vp_id, 0);
                }
            }

            vop2fb_mask_write(vfb, VOP2_OVL_CTRL, 1,
                    RK3568_OVL_LAYERSEL_REGDONE_IMD_SHIFT, 1);
            vop2fb_reg_write(vfb, VOP2_REG_CFG_DONE,
                    vop2fb_cfg_done_mask_val(vfb, active_vps));

            LOG_D("rk3568 ovl multi: active=0x%x layer_sel=0x%08x port_sel=0x%08x",
                    active_vps, layer_sel, port_sel);

            return RT_EOK;
        }

        /*
         * Match the working U-Boot single-display chain on RK3568:
         *   Cluster0 -> Esmart0 -> Smart0 -> Cluster1 -> Esmart1 -> Smart1
         * with VP0 taking mixer output 5.
         *
         * Using only the currently-active layer count here can route VP0 to
         * mixer stage 0, which still produces valid HDMI timing but no
         * visible pixels.
         */
        if ((!active_vps && vfb->vp_id == 0) ||
                active_vps == RT_BIT(0))
        {
            rt_uint32_t layer_sel = 0x00761320;
            rt_uint32_t port_sel = 0x00000755;

            vop2fb_reg_write(vfb, VOP2_OVL_LAYER_SEL, layer_sel);
            vop2fb_reg_write(vfb, VOP2_OVL_PORT_SEL, port_sel);
            vop2fb_mask_write(vfb, VOP2_OVL_CTRL, 1,
                    VOP2_OVL_MODE_SEL_SHIFT + vfb->vp_id, 0);
            vop2fb_mask_write(vfb, VOP2_OVL_CTRL, 1,
                    RK3568_OVL_LAYERSEL_REGDONE_IMD_SHIFT, 1);

            LOG_D("rk3568 ovl init: vp%u fixed layer_sel=0x%08x port_sel=0x%08x",
                    vfb->vp_id, layer_sel, port_sel);

            vop2fb_reg_write(vfb, VOP2_REG_CFG_DONE, vop2fb_cfg_done_val(vfb));
            return RT_EOK;
        }

        struct vop2fb_layer_cfg layers[6];
        rt_uint32_t layer_sel = 0;
        rt_uint32_t port_sel = 0;
        rt_size_t i;
        rt_size_t count = 0;
        rt_uint32_t port_mux;

        for (i = 0; i < RT_ARRAY_SIZE(layers); ++i)
        {
            layer_sel |= 0x5u << (i * 4);
        }

        port_sel |= 0x8u << 0;
        port_sel |= 0x8u << 4;
        port_sel |= 0x8u << 8;

        vop2fb_collect_plane_cfg(layers, &count, RT_ARRAY_SIZE(layers), vfb->primary);

        for (i = 0; i < vfb->overlay_count; ++i)
        {
            vop2fb_collect_plane_cfg(layers, &count, RT_ARRAY_SIZE(layers), vfb->overlays[i]);
        }

        vop2fb_collect_plane_cfg(layers, &count, RT_ARRAY_SIZE(layers), vfb->cursor);

        if (!count && vfb->soc->primary)
        {
            vop2fb_layer_cfg_insert(layers, &count, RT_ARRAY_SIZE(layers),
                    vfb->soc->primary, 0);
        }

        for (i = 0; i < count; ++i)
        {
            const struct vop2fb_win_desc *desc = layers[i].desc;
            rt_uint32_t sel_shift = desc->win_sel_port_offset * 2;

            layer_sel &= ~(0xfu << (i * 4));
            layer_sel |= ((rt_uint32_t)desc->layer_sel_id & 0xfu) << (i * 4);

            port_sel &= ~(0x3u << (16 + sel_shift));
            port_sel |= (vfb->vp_id & 0x3u) << (16 + sel_shift);
        }

        port_mux = count ? (rt_uint32_t)(count - 1) : 0x8u;
        port_sel &= ~(0xfu << (vfb->vp_id * 4));
        port_sel |= (port_mux & 0xfu) << (vfb->vp_id * 4);

        vop2fb_reg_write(vfb, VOP2_OVL_LAYER_SEL, layer_sel);
        vop2fb_reg_write(vfb, VOP2_OVL_PORT_SEL, port_sel);
        vop2fb_mask_write(vfb, VOP2_OVL_CTRL, 1,
                RK3568_OVL_LAYERSEL_REGDONE_IMD_SHIFT, 1);

        LOG_D("rk3568 ovl init: vp%u layers=%u layer_sel=0x%08x port_sel=0x%08x",
                vfb->vp_id, (unsigned)count, layer_sel, port_sel);
    }
    else if (vfb->soc->soc == VOP2FB_SOC_RK3576)
    {
        rt_uint32_t port_ctrl = (vfb->vp_id == 2) ? 0x800 :
                                (vfb->vp_id == 1) ? 0x700 : 0x600;

        vop2fb_reg_write(vfb, port_ctrl, 1);
    }

    vop2fb_reg_write(vfb, VOP2_REG_CFG_DONE, vop2fb_cfg_done_val(vfb));

    return RT_EOK;
}

static const struct vop2fb_win_desc *vop2fb_win_by_plane_id(struct vop2fb *vfb, rt_uint32_t plane_id)
{
    rt_size_t i;

    if (vfb->soc->primary && vfb->soc->primary->plane_id == plane_id)
    {
        return vfb->soc->primary;
    }

    if (vfb->soc->cursor && vfb->soc->cursor->plane_id == plane_id)
    {
        return vfb->soc->cursor;
    }

    for (i = 0; i < vfb->soc->overlay_count; ++i)
    {
        if (vfb->soc->overlays[i].plane_id == plane_id)
        {
            return &vfb->soc->overlays[i];
        }
    }

    return RT_NULL;
}

rt_err_t vop2fb_parse_port_planes(struct vop2fb *vfb, struct rt_ofw_node *vop_np,
        rt_uint32_t vp_id)
{
    struct rt_ofw_node *ports_np, *port_np, *child;
    rt_uint32_t reg, primary_id = RK_PLANE_ESMART0, cursor_id = RK_PLANE_SMART1;

    RT_UNUSED(vop2fb_win_by_plane_id);

    if (!vfb || !vop_np)
    {
        return -RT_EINVAL;
    }

    ports_np = rt_ofw_get_child_by_tag(vop_np, "ports");

    if (!ports_np)
    {
        return -RT_ENOENT;
    }

    port_np = RT_NULL;

    rt_ofw_foreach_child_node(ports_np, child)
    {
        if (!rt_ofw_prop_read_u32(child, "reg", &reg) && reg == vp_id)
        {
            port_np = child;
            break;
        }
    }

    if (!port_np)
    {
        return -RT_ENOENT;
    }

    rt_ofw_prop_read_u32(port_np, "rockchip,primary-plane", &primary_id);
    rt_ofw_prop_read_u32(port_np, "cursor-win-id", &cursor_id);

    LOG_D("VP%u primary-plane=%u cursor-win-id=%u", vp_id, primary_id, cursor_id);

    return RT_EOK;
}
