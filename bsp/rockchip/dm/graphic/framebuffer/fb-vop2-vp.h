/*
 * Copyright (c) 2006-2023, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-09-23     GuEe-GUI     first version
 */

#ifndef __FB_VOP2_VP_H__
#define __FB_VOP2_VP_H__

#include "fb-vop2.h"
#include "rockchip-display.h"

#define VOP2FB_VP_STRIDE                            0x100

#define VOP2_VP_DSP_CTRL                            0xC00
#define VOP2_VP_DSP_BG                              0xC2C
#define RK3568_VP0_PRE_SCAN_HTIMING                 0xC30
#define RK3568_VP0_POST_DSP_HACT_INFO               0xC34
#define RK3568_VP0_POST_DSP_VACT_INFO               0xC38
#define RK3568_VP0_POST_SCL_FACTOR_YRGB             0xC3C
#define RK3568_VP0_POST_SCL_CTRL                    0xC40
#define RK3568_VP0_POST_DSP_VACT_INFO_F1            0xC44
#define VOP2_VP_DSP_HTOTAL_HS_END                   0xC48
#define VOP2_VP_DSP_HACT_ST_END                     0xC4C
#define VOP2_VP_DSP_VTOTAL_VS_END                   0xC50
#define VOP2_VP_DSP_VACT_ST_END                     0xC54

#define VOP2_OVL_CTRL                               0x600
#define VOP2_OVL_MODE_SEL_SHIFT                     0
#define VOP2_OVL_LAYER_SEL                          0x604
#define VOP2_OVL_PORT_SEL                           0x608
#define RK3568_VP0_BG_MIX_CTRL                      0x6E0
#define RK3568_BG_MIX_CTRL_MASK                     0xff
#define RK3568_BG_MIX_CTRL_SHIFT                    24
#define RK3568_OVL_LAYERSEL_REGDONE_IMD_SHIFT       28
#define RK3568_POST_HORIZONTAL_SCALEDOWN_EN_SHIFT   0
#define RK3568_POST_VERTICAL_SCALEDOWN_EN_SHIFT     1

#define RK3568_DSP_IF_EN                            0x028
#define RK3568_DSP_IF_POL                           0x030

#define RK3568_VP0_INT_EN                           0x0A0
#define RK3568_VP0_INT_CLR                          0x0A4
#define RK3568_VP0_INT_STATUS                       0x0A8

#define VOP2_VP_STANDBY_SHIFT                       31
#define VOP2_VP_OUT_MODE_SHIFT                      0
#define VOP2_VP_OUT_MODE_MASK                       0xf
#define VOP2_VP_PRE_DITHER_DOWN_EN_SHIFT            16
#define VOP2_VP_DITHER_DOWN_EN_SHIFT                17

#define RK3568_HDMI0_EN_SHIFT                       1
#define RK3568_EDP0_EN_SHIFT                        3
#define RK3568_MIPI0_EN_SHIFT                       4
#define RK3568_LVDS0_EN_SHIFT                       5
#define RK3568_RGB_EN_SHIFT                         0
#define RK3568_MIPI1_EN_SHIFT                       20
#define RK3568_LVDS1_EN_SHIFT                       24

#define RK3568_HDMI0_MUX_SHIFT                      10
#define RK3568_EDP0_MUX_SHIFT                       14
#define RK3568_MIPI0_MUX_SHIFT                      16
#define RK3568_LVDS0_MUX_SHIFT                      18
#define RK3568_RGB_MUX_SHIFT                        8
#define RK3568_MIPI1_MUX_SHIFT                      21
#define RK3568_LVDS1_MUX_SHIFT                      25
#define RK3568_IF_MUX_MASK                          0x3

#define RK3568_IF_CTRL_REG_DONE_IMD_SHIFT           28
#define RK3568_IF_CRTL_MIPI_DCLK_POL_SHIFT          19
#define RK3568_IF_CTRL_MIPI_PIN_POL_SHIFT            16
#define RK3568_IF_CRTL_EDP_DCLK_POL_SHIFT           15
#define RK3568_IF_CTRL_EDP_PIN_POL_SHIFT            12
#define RK3568_IF_CRTL_HDMI_DCLK_POL_SHIFT          7
#define RK3568_IF_CRTL_HDMI_PIN_POL_SHIFT           4
#define RK3568_IF_CTRL_RGB_DCLK_POL_SHIFT           3
#define RK3568_IF_CTRL_RGB_PIN_POL_SHIFT            0
#define RK3568_IF_PIN_POL_MASK                      0x7

#define RK3568_HSYNC_POSITIVE                       RT_BIT(0)
#define RK3568_VSYNC_POSITIVE                       RT_BIT(1)

#define VOP2_VP_FS_INTR                             RT_BIT(0)
#define VOP2_VP_FS_NEW_INTR                         RT_BIT(1)
#define VOP2_VP_POST_BUF_EMPTY_INTR                 RT_BIT(4)
#define VOP2_VP_FS_FIELD_INTR                       RT_BIT(5)

#define RK3568_SYS0_INT_EN                          0x080
#define RK3568_SYS0_INT_CLR                         0x084
#define RK3568_SYS0_INT_STATUS                      0x088
#define RK3568_SYS1_INT_EN                          0x090
#define RK3568_SYS1_INT_CLR                         0x094
#define RK3568_SYS1_INT_STATUS                      0x098
#define RK3568_SYS_BUS_ERROR_INTR                   RT_BIT(1)

#define RK3568_VP_INT_EN(vp_id)                     (RK3568_VP0_INT_EN + ((vp_id) * 0x10))
#define RK3568_VP_INT_CLR(vp_id)                    (RK3568_VP0_INT_CLR + ((vp_id) * 0x10))
#define RK3568_VP_INT_STATUS(vp_id)                 (RK3568_VP0_INT_STATUS + ((vp_id) * 0x10))

#define RK3576_MIPI0_IF_CTRL                        0x180
#define RK3576_VP_OUT_MODE_P888                     0
#define RK3568_VP_OUT_MODE_AAAA                     15

rt_err_t vop2fb_vp_mode_set(struct vop2fb *vfb, rt_uint32_t vp_id,
        const struct display_timing *tim);
void vop2fb_vp_irq_ctrl(struct vop2fb *vfb, rt_uint32_t vp_id, rt_bool_t enable);
rt_err_t vop2fb_vp_enable(struct vop2fb *vfb, rt_uint32_t vp_id, rt_bool_t enable);
void vop2fb_output_disable(struct vop2fb *vfb, enum vop2fb_output_if output_if);
rt_err_t vop2fb_vp_post_config(struct vop2fb *vfb, rt_uint32_t vp_id,
        const struct display_timing *tim);
rt_err_t vop2fb_mipi_output_enable(struct vop2fb *vfb, rt_uint32_t vp_id, rt_bool_t enable);
rt_err_t vop2fb_overlay_init(struct vop2fb *vfb);
rt_err_t vop2fb_mix_alpha_set(struct vop2fb *vfb, rt_uint32_t mix_reg, rt_uint8_t alpha);
rt_err_t vop2fb_parse_port_planes(struct vop2fb *vfb, struct rt_ofw_node *vop_np,
        rt_uint32_t vp_id);

#endif /* __FB_VOP2_VP_H__ */
