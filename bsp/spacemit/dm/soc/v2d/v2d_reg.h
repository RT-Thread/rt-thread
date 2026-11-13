/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#ifndef __SPACEMIT_V2D_REG_H__
#define __SPACEMIT_V2D_REG_H__

#define V2D_REG_BASE                        0xC0100000
#define PMUA_REG_BASE                       0xd4282800
#define V2D_TOP_BASE                        0x000
#define V2D_CORE_BASE                       0x100
#define V2D_ENC_BASE                        0x800
#define V2D_L0_DEC_BASE                     0x900
#define V2D_L1_DEC_BASE                     0xa00

/* v2d clk offset */
#define V2D_CLK_RES_CTRL0                   0x44
#define V2D_CLK_RES_CTRL1                   0x4c

/* v2d top offset */
#define V2D_AUTO_CLK_REG                    (0x00 + V2D_TOP_BASE)
#define V2D_ERR_IRQ_MASK                    (0x04 + V2D_TOP_BASE)
#define V2D_IRQ_MASK                        (0x08 + V2D_TOP_BASE)
#define V2D_ERR_IRQ_STATUS                  (0x0C + V2D_TOP_BASE)
#define V2D_IRQ_STATUS                      (0x10 + V2D_TOP_BASE)
#define V2D_ERR_IRQ_RAW                     (0x14 + V2D_TOP_BASE)
#define V2D_IRQ_RAW                         (0x18 + V2D_TOP_BASE)
#define V2D_AXI_BUS_CTRL                    (0x1C + V2D_TOP_BASE)

#define V2D_GLOBAL_RESET                    RT_BIT(8)
#define V2D_AUTO_CLK_EN                     RT_BIT(9)
#define V2D_ENC_AUTO_CLK_EN                 RT_BIT(10)
#define V2D_TOP_AUTO_CLK_EN                 RT_BIT(11)
#define V2D_EOF_IRQ_STATUS                  RT_BIT(0)
#define V2D_FBCENC_IRQ_STATUS               RT_BIT(1)
#define V2D_EOF_IRQ_MASK                    RT_BIT(0)
#define V2D_FBCENC_IRQ_MASK                 RT_BIT(1)

#define V2D_H_ADDR_MASK                     0x3
/* v2d core offset */
#define V2D_CTRL_REG                        (0x00 + V2D_CORE_BASE)
#define V2D_SCALER_COEF_REG0                (0x04 + V2D_CORE_BASE)
#define V2D_SCALER_COEF_RGG1                (0x08 + V2D_CORE_BASE)
#define V2D_SCALER_COEF_REG2                (0x0C + V2D_CORE_BASE)
#define V2D_SCALER_COEF_RGG3                (0x10 + V2D_CORE_BASE)
#define V2D_SCALER_COEF_REG4                (0x14 + V2D_CORE_BASE)
#define V2D_SCALER_COEF_RGG5                (0x18 + V2D_CORE_BASE)
#define V2D_SCALER_COEF_REG6                (0x1C + V2D_CORE_BASE)
#define V2D_SCALER_COEF_RGG7                (0x20 + V2D_CORE_BASE)
#define V2D_SCALER_COEF_REG8                (0x24 + V2D_CORE_BASE)
#define V2D_SCALER_COEF_RGG9                (0x28 + V2D_CORE_BASE)
#define V2D_SCALER_COEF_REG10               (0x2C + V2D_CORE_BASE)
#define V2D_SCALER_COEF_RGG11               (0x30 + V2D_CORE_BASE)
#define V2D_SCALER_COEF_REG12               (0x34 + V2D_CORE_BASE)
#define V2D_SCALER_COEF_RGG13               (0x38 + V2D_CORE_BASE)
#define V2D_SCALER_COEF_REG14               (0x3C + V2D_CORE_BASE)
#define V2D_SCALER_COEF_RGG15               (0x40 + V2D_CORE_BASE)
#define V2D_SCALER_COEF_REG16               (0x44 + V2D_CORE_BASE)
#define V2D_SCALER_COEF_RGG17               (0x48 + V2D_CORE_BASE)
#define V2D_SCALER_COEF_REG18               (0x4C + V2D_CORE_BASE)
#define V2D_SCALER_COEF_RGG19               (0x50 + V2D_CORE_BASE)
#define V2D_SCALER_COEF_REG20               (0x54 + V2D_CORE_BASE)
#define V2D_SCALER_COEF_RGG21               (0x58 + V2D_CORE_BASE)
#define V2D_SCALER_COEF_REG22               (0x5C + V2D_CORE_BASE)
#define V2D_SCALER_COEF_RGG23               (0x60 + V2D_CORE_BASE)
#define V2D_SCALER_COEF_REG(i)              (0x04 * (i + 1) + V2D_CORE_BASE)
#define SCALER_COEF_REG_NUM                 24

#define V2D_BLEND_REG0                      (0x64 + V2D_CORE_BASE)
#define V2D_BLEND_REG1                      (0x68 + V2D_CORE_BASE)
#define V2D_BLD_MASK_REG0                   (0x6C + V2D_CORE_BASE)
#define V2D_BLD_MASK_REG1                   (0x70 + V2D_CORE_BASE)
#define V2D_BLD_MASK_REG2                   (0x74 + V2D_CORE_BASE)

#define V2D_OUTPUT_Y_ADDR_L                 (0x78 + V2D_CORE_BASE)
#define V2D_OUTPUT_Y_ADDR_H                 (0x7C + V2D_CORE_BASE)
#define V2D_OUTPUT_UV_ADDR_L                (0x80 + V2D_CORE_BASE)
#define V2D_OUTPUT_UV_ADDR_H                (0x84 + V2D_CORE_BASE)
#define V2D_OUTPUT_WIDTH                    (0x84 + V2D_CORE_BASE)
#define V2D_OUTPUT_HEIGHT                   (0x88 + V2D_CORE_BASE)
#define V2D_OUTPUT_CRTL0                    (0x8C + V2D_CORE_BASE)
#define V2D_OUTPUT_CRTL1                    (0x90 + V2D_CORE_BASE)
#define V2D_OUTPUT_CRTL2                    (0x94 + V2D_CORE_BASE)

#define V2D_MASK_ADDR_L                     (0x98 + V2D_CORE_BASE)
#define V2D_MASK_ADDR_H                     (0x9C + V2D_CORE_BASE)
#define V2D_MASK_WIDTH                      (0x9C + V2D_CORE_BASE)
#define V2D_MASK_HEIGHT                     (0xA0 + V2D_CORE_BASE)
#define V2D_MASK_CROP_REG0                  (0xA4 + V2D_CORE_BASE)
#define V2D_MASK_CROP_REG1                  (0xA8 + V2D_CORE_BASE)

#define V2D_LAYER0_Y_ADDR_L                 (0xAC + V2D_CORE_BASE)
#define V2D_LAYER0_Y_ADDR_H                 (0xB0 + V2D_CORE_BASE)
#define V2D_LAYER0_UV_ADDR_L                (0xB4 + V2D_CORE_BASE)
#define V2D_LAYER0_UV_ADDR_H                (0xB8 + V2D_CORE_BASE)
#define V2D_LAYER0_BLD_FACTOR               (0xB8 + V2D_CORE_BASE)
#define V2D_LAYER0_WIDTH_HEIGHT             (0xBC + V2D_CORE_BASE)
#define V2D_LAYER0_CTRL                     (0xC0 + V2D_CORE_BASE)
#define V2D_LAYER0_CROP_REG0                (0xC4 + V2D_CORE_BASE)
#define V2D_LAYER0_CROP_REG1                (0xC8 + V2D_CORE_BASE)
#define V2D_LAYER0_SOLIDCOLOR_CTRL0         (0xCC + V2D_CORE_BASE)
#define V2D_LAYER0_SOLIDCOLOR_CTRL1         (0xD0 + V2D_CORE_BASE)
#define V2D_LAYER0_CSC_CRTL0                (0xD0 + V2D_CORE_BASE)
#define V2D_LAYER0_CSC_CRTL1                (0xD4 + V2D_CORE_BASE)
#define V2D_LAYER0_CSC_CRTL2                (0xD8 + V2D_CORE_BASE)
#define V2D_LAYER0_CSC_CRTL3                (0xDC + V2D_CORE_BASE)
#define V2D_LAYER0_CSC_CRTL4                (0xE0 + V2D_CORE_BASE)
#define V2D_LAYER0_CSC_CRTL5                (0xE4 + V2D_CORE_BASE)
#define V2D_LAYER0_CSC_CRTL6                (0xE8 + V2D_CORE_BASE)
#define V2D_LAYER0_SCALE_MODE               (0xE8 + V2D_CORE_BASE)
#define V2D_LAYER0_SCALE_DELTA_X            (0xEC + V2D_CORE_BASE)
#define V2D_LAYER0_SCALE_DELTA_Y            (0xF0 + V2D_CORE_BASE)
#define V2D_LAYER0_BLD_CTRL0                (0xF0 + V2D_CORE_BASE)
#define V2D_LAYER0_BLD_CTRL1                (0xF4 + V2D_CORE_BASE)
#define V2D_LAYER0_BLD_CTRL2                (0xF8 + V2D_CORE_BASE)
#define V2D_LAYER0_BLD_CTRL3                (0xFC + V2D_CORE_BASE)

#define V2D_LAYER1_Y_ADDR_L                 (0x100 + V2D_CORE_BASE)
#define V2D_LAYER1_Y_ADDR_H                 (0x104 + V2D_CORE_BASE)
#define V2D_LAYER1_UV_ADDR_L                (0x108 + V2D_CORE_BASE)
#define V2D_LAYER1_UV_ADDR_H                (0x10C + V2D_CORE_BASE)
#define V2D_LAYER1_BLD_FACTOR               (0x10C + V2D_CORE_BASE)
#define V2D_LAYER1_WIDTH_HEIGHT             (0x110 + V2D_CORE_BASE)
#define V2D_LAYER1_CTRL                     (0x114 + V2D_CORE_BASE)
#define V2D_LAYER1_CROP_REG0                (0x118 + V2D_CORE_BASE)
#define V2D_LAYER1_CROP_REG1                (0x11C + V2D_CORE_BASE)
#define V2D_LAYER1_SOLIDCOLOR_CTRL0         (0x120 + V2D_CORE_BASE)
#define V2D_LAYER1_SOLIDCOLOR_CTRL1         (0x124 + V2D_CORE_BASE)
#define V2D_LAYER1_CSC_CRTL0                (0x124 + V2D_CORE_BASE)
#define V2D_LAYER1_CSC_CRTL1                (0x128 + V2D_CORE_BASE)
#define V2D_LAYER1_CSC_CRTL2                (0x12C + V2D_CORE_BASE)
#define V2D_LAYER1_CSC_CRTL3                (0x130 + V2D_CORE_BASE)
#define V2D_LAYER1_CSC_CRTL4                (0x134 + V2D_CORE_BASE)
#define V2D_LAYER1_CSC_CRTL5                (0x138 + V2D_CORE_BASE)
#define V2D_LAYER1_CSC_CRTL6                (0x13C + V2D_CORE_BASE)
#define V2D_LAYER1_SCALE_MODE               (0x13C + V2D_CORE_BASE)
#define V2D_LAYER1_SCALE_DELTA_X            (0x140 + V2D_CORE_BASE)
#define V2D_LAYER1_SCALE_DELTA_Y            (0x144 + V2D_CORE_BASE)
#define V2D_LAYER1_BLD_CTRL0                (0x144 + V2D_CORE_BASE)
#define V2D_LAYER1_BLD_CTRL1                (0x148 + V2D_CORE_BASE)
#define V2D_LAYER1_BLD_CTRL2                (0x14C + V2D_CORE_BASE)
#define V2D_LAYER1_BLD_CTRL3                (0x150 + V2D_CORE_BASE)

#define V2D_LAYER_Y_ADDR_L_LAYER(i)         (0xAC + i * 0x54 + V2D_CORE_BASE)
#define V2D_LAYER_Y_ADDR_H_LAYER(i)         (0xB0 + i * 0x54 + V2D_CORE_BASE)
#define V2D_LAYER_UV_ADDR_L_LAYER(i)        (0xB4 + i * 0x54 + V2D_CORE_BASE)
#define V2D_LAYER_UV_ADDR_H_LAYER(i)        (0xB8 + i * 0x54 + V2D_CORE_BASE)
#define V2D_LAYER_BLD_FACTOR_LAYER(i)       (0xB8 + i * 0x54 + V2D_CORE_BASE)
#define V2D_LAYER_WIDTH_HEIGHT_LAYER(i)     (0xBC + i * 0x54 + V2D_CORE_BASE)
#define V2D_LAYER_CTRL_LAYER(i)             (0xC0 + i * 0x54 + V2D_CORE_BASE)
#define V2D_LAYER_CROP_REG0_LAYER(i)        (0xC4 + i * 0x54 + V2D_CORE_BASE)
#define V2D_LAYER_CROP_REG1_LAYER(i)        (0xC8 + i * 0x54 + V2D_CORE_BASE)
#define V2D_LAYER_SOLIDCOLOR_CTRL0_LAYER(i) (0xCC + i * 0x54 + V2D_CORE_BASE)
#define V2D_LAYER_SOLIDCOLOR_CTRL1_LAYER(i) (0xD0 + i * 0x54 + V2D_CORE_BASE)
#define V2D_LAYER_CSC_CRTL0_LAYER(i)        (0xD0 + i * 0x54 + V2D_CORE_BASE)
#define V2D_LAYER_CSC_CRTL1_LAYER(i)        (0xD4 + i * 0x54 + V2D_CORE_BASE)
#define V2D_LAYER_CSC_CRTL2_LAYER(i)        (0xD8 + i * 0x54 + V2D_CORE_BASE)
#define V2D_LAYER_CSC_CRTL3_LAYER(i)        (0xDC + i * 0x54 + V2D_CORE_BASE)
#define V2D_LAYER_CSC_CRTL4_LAYER(i)        (0xE0 + i * 0x54 + V2D_CORE_BASE)
#define V2D_LAYER_CSC_CRTL5_LAYER(i)        (0xE4 + i * 0x54 + V2D_CORE_BASE)
#define V2D_LAYER_CSC_CRTL6_LAYER(i)        (0xE8 + i * 0x54 + V2D_CORE_BASE)
#define V2D_LAYER_SCALE_MODE_LAYER(i)       (0xE8 + i * 0x54 + V2D_CORE_BASE)
#define V2D_LAYER_SCALE_DELTA_X_LAYER(i)    (0xEC + i * 0x54 + V2D_CORE_BASE)
#define V2D_LAYER_SCALE_DELTA_Y_LAYER(i)    (0xF0 + i * 0x54 + V2D_CORE_BASE)
#define V2D_LAYER_BLD_CTRL0_LAYER(i)        (0xF0 + i * 0x54 + V2D_CORE_BASE)
#define V2D_LAYER_BLD_CTRL1_LAYER(i)        (0xF4 + i * 0x54 + V2D_CORE_BASE)
#define V2D_LAYER_BLD_CTRL2_LAYER(i)        (0xF8 + i * 0x54 + V2D_CORE_BASE)
#define V2D_LAYER_BLD_CTRL3_LAYER(i)        (0xFC + i * 0x54 + V2D_CORE_BASE)

#define V2D_DEBUG_REG0                      (0x1FC + V2D_CORE_BASE)
#define V2D_DEBUG_REG1                      (0x200 + V2D_CORE_BASE)
#define V2D_DMA_CTRL                        (0x204 + V2D_CORE_BASE)
#define V2D_PALETTE_TABLE(i)                (0x208 + i * 0x4 + V2D_CORE_BASE)

#define V2D_L0_DEC_REG0                     (V2D_L0_DEC_BASE + 0x000)  /* register hdr_base_addr_low */
#define V2D_L0_DEC_REG1                     (V2D_L0_DEC_BASE + 0x004)  /* register hdr_base_addr_high */
#define V2D_L0_DEC_REG2                     (V2D_L0_DEC_BASE + 0x008)  /* register bbox_coor_x */
#define V2D_L0_DEC_REG3                     (V2D_L0_DEC_BASE + 0x00c)  /* register bbox_coor_y */
#define V2D_L0_DEC_REG4                     (V2D_L0_DEC_BASE + 0x010)  /* register image_size */
#define V2D_L0_DEC_REG5                     (V2D_L0_DEC_BASE + 0x014)  /* register dec_mode */
#define V2D_L0_DEC_REG6                     (V2D_L0_DEC_BASE + 0x018)  /* register dmac_ctrl */
#define V2D_L0_DEC_REG7                     (V2D_L0_DEC_BASE + 0x01c)  /* register irq_mask */
#define V2D_L0_DEC_REG8                     (V2D_L0_DEC_BASE + 0x020)  /* register irq_raw */
#define V2D_L0_DEC_REG9                     (V2D_L0_DEC_BASE + 0x024)  /* register irq_status */
#define V2D_L0_DEC_REG10                    (V2D_L0_DEC_BASE + 0x028)  /* register trig_ctrl */
#define V2D_L0_DEC_REG11                    (V2D_L0_DEC_BASE + 0x02c)  /* register output_ybase */
#define V2D_L0_DEC_REG12                    (V2D_L0_DEC_BASE + 0x030)  /* register output_cbase */
#define V2D_L0_DEC_REG13                    (V2D_L0_DEC_BASE + 0x034)  /* register output_stride */

#define V2D_L1_DEC_REG0                     (V2D_L1_DEC_BASE + 0x000)
#define V2D_L1_DEC_REG1                     (V2D_L1_DEC_BASE + 0x004)
#define V2D_L1_DEC_REG2                     (V2D_L1_DEC_BASE + 0x008)
#define V2D_L1_DEC_REG3                     (V2D_L1_DEC_BASE + 0x00c)
#define V2D_L1_DEC_REG4                     (V2D_L1_DEC_BASE + 0x010)
#define V2D_L1_DEC_REG5                     (V2D_L1_DEC_BASE + 0x014)
#define V2D_L1_DEC_REG6                     (V2D_L1_DEC_BASE + 0x018)
#define V2D_L1_DEC_REG7                     (V2D_L1_DEC_BASE + 0x01c)
#define V2D_L1_DEC_REG8                     (V2D_L1_DEC_BASE + 0x020)
#define V2D_L1_DEC_REG9                     (V2D_L1_DEC_BASE + 0x024)
#define V2D_L1_DEC_REG10                    (V2D_L1_DEC_BASE + 0x028)
#define V2D_L1_DEC_REG11                    (V2D_L1_DEC_BASE + 0x02c)
#define V2D_L1_DEC_REG12                    (V2D_L1_DEC_BASE + 0x030)
#define V2D_L1_DEC_REG13                    (V2D_L1_DEC_BASE + 0x034)

#define V2D_LAYER_DEC_REG0_L(i)             (V2D_L0_DEC_BASE + i * 0x100 + 0x000)
#define V2D_LAYER_DEC_REG1_L(i)             (V2D_L0_DEC_BASE + i * 0x100 + 0x004)
#define V2D_LAYER_DEC_REG2_L(i)             (V2D_L0_DEC_BASE + i * 0x100 + 0x008)
#define V2D_LAYER_DEC_REG3_L(i)             (V2D_L0_DEC_BASE + i * 0x100 + 0x00c)
#define V2D_LAYER_DEC_REG4_L(i)             (V2D_L0_DEC_BASE + i * 0x100 + 0x010)
#define V2D_LAYER_DEC_REG5_L(i)             (V2D_L0_DEC_BASE + i * 0x100 + 0x014)
#define V2D_LAYER_DEC_REG6_L(i)             (V2D_L0_DEC_BASE + i * 0x100 + 0x018)
#define V2D_LAYER_DEC_REG7_L(i)             (V2D_L0_DEC_BASE + i * 0x100 + 0x01c)
#define V2D_LAYER_DEC_REG8_L(i)             (V2D_L0_DEC_BASE + i * 0x100 + 0x020)
#define V2D_LAYER_DEC_REG9_L(i)             (V2D_L0_DEC_BASE + i * 0x100 + 0x024)
#define V2D_LAYER_DEC_REG10_L(i)            (V2D_L0_DEC_BASE + i * 0x100 + 0x028)
#define V2D_LAYER_DEC_REG11_L(i)            (V2D_L0_DEC_BASE + i * 0x100 + 0x02c)
#define V2D_LAYER_DEC_REG12_L(i)            (V2D_L0_DEC_BASE + i * 0x100 + 0x030)
#define V2D_LAYER_DEC_REG13_L(i)            (V2D_L0_DEC_BASE + i * 0x100 + 0x034)

#define V2D_ENC_REG0                        (V2D_ENC_BASE + 0x000)  /* REGISTER HEADER_BASE_ADDR_LOW */
#define V2D_ENC_REG1                        (V2D_ENC_BASE + 0x004)  /* REGISTER HEADER_BASE_ADDR_HIGH */
#define V2D_ENC_REG2                        (V2D_ENC_BASE + 0x008)  /* REGISTER PAYLOAD_BASE_ADDR_LOW */
#define V2D_ENC_REG3                        (V2D_ENC_BASE + 0x00c)  /* REGISTER PAYLOAD_BASE_ADDR_HIGH */
#define V2D_ENC_REG4                        (V2D_ENC_BASE + 0x010)  /* REGISTER Bbox_coor_x */
#define V2D_ENC_REG5                        (V2D_ENC_BASE + 0x014)  /* REGISTER Bbox_coor_y */
#define V2D_ENC_REG6                        (V2D_ENC_BASE + 0x018)  /* REGISTER Y_BUF_BASE_ADDR */
#define V2D_ENC_REG7                        (V2D_ENC_BASE + 0x01c)  /* REGISTER Y_BUF_PITCH */
#define V2D_ENC_REG8                        (V2D_ENC_BASE + 0x020)  /* REGISTER UV_BUF_BASE_ADDR */
#define V2D_ENC_REG9                        (V2D_ENC_BASE + 0x024)  /* REGISTER UV_BUF_PITCH */
#define V2D_ENC_REG10                       (V2D_ENC_BASE + 0x028)  /* REGISTER Y_BUF_SIZE */
#define V2D_ENC_REG11                       (V2D_ENC_BASE + 0x02c)  /* REGISTER UV_BUF_SIZE */
#define V2D_ENC_REG12                       (V2D_ENC_BASE + 0x030)  /* REGISTER REG_SHADOW_CTRL */
#define V2D_ENC_REG13                       (V2D_ENC_BASE + 0x034)  /* REGISTER IRQ_MASK */
#define V2D_ENC_REG14                       (V2D_ENC_BASE + 0x038)  /* REGISTER IRQ_CLEAR */
#define V2D_ENC_REG15                       (V2D_ENC_BASE + 0x03c)  /* REGISTER DMAC_CTRL_0 */
#define V2D_ENC_REG16                       (V2D_ENC_BASE + 0x040)  /* REGISTER ENC_MODE */
#define V2D_ENC_REG17                       (V2D_ENC_BASE + 0x044)  /* REGISTER DMAC_LENGTH */
#define V2D_ENC_REG18                       (V2D_ENC_BASE + 0x048)  /* REGISTER IRQ_STATUS */
/* v2d iommu */
#define TBU_NUM 32
#define V2D_MMU_TTBLR_BASE                  0x40
#define V2D_MMU_TTBHR_BASE                  0x44
#define V2D_MMU_TCR0_BASE                   0x48
#define V2D_MMU_TCR1_BASE                   0x4c
#define V2D_MMU_TBU_STATUS_BASE             0x50
#define V2D_MMU_TBUx_STEP                   0x20
#define V2D_MMU_BVA_LO                      0x00
#define V2D_MMU_BVA_HI                      0x04
#define V2D_MMU_TIMEOUT_VA_ADDR_LO          0x08
#define V2D_MMU_TIMEOUT_VA_ADDR_HI          0x0C
#define V2D_MMU_IRQ_STATUS                  0x10
#define V2D_MMU_IRQ_ENABLE                  0x14
#define V2D_MMU_TIMEOUT_VALUE               0x18
#define V2D_MMU_ERROR_CLEAR                 0x1C
#define V2D_MMU_LAST_VA_ADDR_LO             0x20
#define V2D_MMU_LAST_VA_ADDR_HI             0x24
#define V2D_MMU_LAST_PA_ADDR_LO             0x28
#define V2D_MMU_LAST_PA_ADDR_HI             0x2C
#define V2D_MMU_VERSION                     0x3C
#define V2D_IOMMU_BASE_OFFSET               0xB00

/**
 *@brief V2D Control register
 */
typedef union
{
    struct
    {
        unsigned int trigger                  : 1;      /**< trigger v2d to work */
        unsigned int rdma_burst_len           : 3;      /**< set rdma burst lenght */
        unsigned int reserved1                : 4;      /**< Reserved */
        unsigned int wdma_burst_len           : 5;      /**< set wdma burst length */
        unsigned int reserved2                : 19;     /**< Reserved */
    } field;                                            /**< Fields view */
    unsigned int overlay;                               /**< Overlay view */
} v2d_ctrl_reg_t;

/**
 *@brief V2D DMA Control register
 */
typedef union
{
    struct
    {
        unsigned int dmac_arb_mode            : 2;
        unsigned int dmac_arqos               : 4;
        unsigned int reserved                 : 2;      /**< Reserved */
        unsigned int dmac_awqos               : 4;
        unsigned int dmac_axi_sec             : 1;
        unsigned int dmac_max_req_num         : 3;
        unsigned int dmac_postwr_en           : 8;
        unsigned int dmac_rst_n_pwr           : 1;
        unsigned int dmac_rst_req             : 1;
        unsigned int dmac_user_id             : 4;
        unsigned int damc_rd_int_clr          : 1;
        unsigned int damc_wr_int_clr          : 1;
    } field;                                            /**< Fields view */
    unsigned int overlay;                               /**< Overlay view */
} v2d_dma_ctrl_reg_t;

/**
 *@brief V2D Scaler Coefficient register
 */
typedef union
{
    struct
    {
        int scaler_coef0                        : 12;   /**< scaler coefficient0 */
        unsigned int reserved1                  : 4;    /**< Reserved */
        int scaler_coef1                        : 12;   /**< scaler coefficient1 */
        unsigned int reserved2                  : 4;    /**< Reserved */
    } field;                                            /**< Fields view */
    unsigned int overlay;                               /**< Overlay view */
} v2d_scaler_coef_reg_t;

/**
 *@brief V2D Blend Control0 register
 */
typedef union
{
    struct
    {
        unsigned int bld_mode                  :  1;    /**< blend mode alpha blending or ROP operation */
        unsigned int bld_bg_enable             :  1;    /**< background color enable */
        unsigned int reserved                  :  6;    /**< Rerserved */
        unsigned int bld_bg_r                  :  8;    /**< background color R value */
        unsigned int bld_bg_g                  :  8;    /**< background color G value */
        unsigned int bld_bg_b                  :  8;    /**< background color B value */
    } field;                                            /**< Fields view */
    unsigned int overlay;                               /**< Overlay view */
} v2d_blend_ctrl0_reg_t;

/**
 *@brief V2D Blend Control1 register
 */
typedef union
{
    struct
    {
        unsigned int bld_bg_a                  :  8;    /**< background color alpha value */
        unsigned int reserved                  :  24;   /**< Rerserved */
    } field;                                            /**< Fields view */
    unsigned int overlay;                               /**< Overlay view */
} v2d_blend_ctrl1_reg_t;

/**
 *@brief V2D Blend Mask Control0 register
 */
typedef union
{
    struct
    {
        unsigned int bld_mask_enable           : 2;     /**< blend mask enable */
        unsigned int reserved1                 : 6;     /**< Rerserved */
        unsigned int bld_mask_rect_ltop_x      : 16;    /**< blend mask rectangle left-top point x-axis coordinate */
        unsigned int reserved2                 : 8;     /**< Rerserved */
    } field;                                            /**< Fields view */
    unsigned int overlay;                               /**< Overlay view */
} v2d_blend_mask_ctrl0_reg_t;

/**
 *@brief V2D Blend Mask Control1 register
 */
typedef union
{
    struct
    {
        unsigned int bld_mask_rect_ltop_y      : 16;    /**< blend mask rectangle left-top point y-axis coordinate */
        unsigned int bld_mask_rect_width       : 16;    /**< blend mask rectangle width */
    } field;                                            /**< Fields view */
    unsigned int overlay;                               /**< Overlay view */
} v2d_blend_mask_ctrl1_reg_t;

/**
 *@brief V2D Blend Mask Control2 register
 */
typedef union
{
    struct
    {
        unsigned int bld_mask_rect_height      : 16;    /**< blend mask rectangle height */
        unsigned int reserved                  : 16;    /**< Rerserved */
    } field;                                            /**< Fields view */
    unsigned int overlay;                               /**< Overlay view */
} v2d_blend_mask_ctrl2_reg_t;

/**
 *@brief V2D Output Width register
 */
typedef union
{
    struct
    {
        unsigned int out_addr_uv_33_32         : 2;     /**< output uv address_h_bit */
        unsigned int reserved1                 : 6;     /**< Rerserved */
        unsigned int out_ori_width             : 16;    /**< output width */
        unsigned int reserved2                 : 8;     /**< Rerserved */
    } field;                                            /**< Fields view */
    unsigned int overlay;                               /**< Overlay view */
} v2d_output_width_reg_t;

/**
 *@brief V2D Output Height register
 */
typedef union
{
    struct
    {
        unsigned int out_ori_height            : 16;    /**< output height */
        unsigned int out_ori_stride            : 16;    /**< output stride */
    } field;                                            /**< Fields view */
    unsigned int overlay;                               /**< Overlay view */
} v2d_output_height_reg_t;

/**
 *@brief V2D Output Control0 register
 */
typedef union
{
    struct
    {
        unsigned int format                  : 4;       /**< output format */
        unsigned int range                   : 1;       /**< output range yuv narrow/wide */
        unsigned int dither                  : 2;       /**< output dither mode */
        unsigned int swap                    : 1;       /**< output swap */
        unsigned int fbc_en                  : 1;       /**< output fbc enable */
        unsigned int reserved                : 7;       /**< Rerserved */
        unsigned int crop_ltop_x             : 16;      /**< output crop left-top point x-axis coordinate */
    } field;                                            /**< Fields view */
    unsigned int overlay;                               /**< Overlay view */
} v2d_output_ctrl0_reg_t;

/**
 *@brief V2D Output Control1 register
 */
typedef union
{
    struct
    {
        unsigned int crop_ltop_y             : 16;      /**< output crop left-top point y-axis coordinate */
        unsigned int crop_width              : 16;      /**< output crop width */
    } field;                                            /**< Fields view */
    unsigned int overlay;                               /**< Overlay view */
} v2d_output_ctrl1_reg_t;

/**
 *@brief V2D Output Control2 register
 */
typedef union
{
    struct
    {
        unsigned int crop_height             : 16;      /**< output crop height */
        unsigned int reserved                : 16;      /**< Rerserved */
    } field;                                            /**< Fields view */
    unsigned int overlay;                               /**< Overlay view */
} v2d_output_ctrl2_reg_t;

/**
 *@brief V2D mask input Width register
 */
typedef union
{
    struct
    {
        unsigned int mask_addr_33_32         : 2;       /**< mask address_h_bit */
        unsigned int reserved1               : 6;       /**< Rerserved */
        unsigned int mask_ori_width          : 16;      /**< mask in width */
        unsigned int reserved2               : 8;       /**< Rerserved */
    } field;                                            /**< Fields view */
    unsigned int overlay;                               /**< Overlay view */
} v2d_mask_width_reg_t;

/**
 *@brief V2D mask input Height register
 */
typedef union
{
    struct
    {
        unsigned int mask_ori_height            : 16;       /**< mask in height */
        unsigned int mask_ori_stride            : 16;       /**< mask in stride */
    } field;                                                /**< Fields view */
    unsigned int overlay;                                   /**< Overlay view */
} v2d_mask_height_reg_t;

/**
 *@brief V2D mask input crop0 register
 */
typedef union
{
    struct
    {
        unsigned int mask_crop_ltop_x           : 16;       /**< mask crop left-top point x-axis coordinate */
        unsigned int mask_crop_ltop_y           : 16;       /**< mask crop left-top point y-axis coordinate */
    } field;                                                /**< Fields view */
    unsigned int overlay;                                   /**< Overlay view */
} v2d_mask_crop0_reg_t;

/**
 *@brief V2D mask input crop1 register
 */
typedef union
{
    struct
    {
        unsigned int mask_crop_width            : 16;       /**< mask crop in width */
        unsigned int mask_crop_height           : 16;       /**< mask crop in height */
    } field;                                                /**< Fields view */
    unsigned int overlay;                                   /**< Overlay view */
} v2d_mask_crop1_reg_t;

/**
 *@brief V2D Blend Layer Factor register
 */
typedef union
{
    struct
    {
        unsigned int in_addr_uv_33_32               : 2;    /**< input layer uv address_h_bit */
        unsigned int bld_src_color_factor           : 3;    /**< blend source color factor */
        unsigned int bld_dst_color_factor           : 3;    /**< blend dst color factor */
        unsigned int bld_src_alpha_factor           : 3;    /**< blend source alpha factor */
        unsigned int bld_dst_alpha_factor           : 3;    /**< blend dst alpha factor */
        unsigned int reserved1                      : 2;    /**< Reserved */
        unsigned int bld_color_rop2_code            : 4;    /**< ROP color code */
        unsigned int bld_alpha_rop2_code            : 4;    /**< ROP alpha code */
        unsigned int reserved2                      : 8;    /**< Reserved */
    } field;                                                /**< Fields view */
    unsigned int overlay;                                   /**< Overlay view */
} v2d_blend_layer_factor_reg_t;

/**
 *@brief V2D Input Layer width/height register
 */
typedef union
{
    struct
    {
        unsigned int layer_in_ori_width            : 16;    /**< input layer width */
        unsigned int layer_in_ori_height           : 16;    /**< input layer height */
    } field;                                                /**< Fields view */
    unsigned int overlay;                                   /**< Overlay view */
} v2d_input_layer_width_height_reg_t;

/**
 *@brief V2D Input Layer Control register
 */
typedef union
{
    struct
    {
        unsigned int stride               : 16;             /**< input layer stride */
        unsigned int format               : 4;              /**< input layer format */
        unsigned int rotation             : 3;              /**< input layer rotation */
        unsigned int swap                 : 1;              /**< input layer swap */
        unsigned int fbc_en               : 1;              /**< input layer fbc enbale */
        unsigned int reserved             : 7;              /**< Reserved */
    } field;                                                /**< Fields view */
    unsigned int overlay;                                   /**< Overlay view */
} v2d_input_layer_ctrl_reg_t;

/**
 *@brief V2D input layer crop0 register
 */
typedef union
{
    struct
    {
        unsigned int layer_in_crop_ltop_x           : 16;   /**< input layer crop left-top point x-axis coordinate */
        unsigned int layer_in_crop_ltop_y           : 16;   /**< input layer crop left-top point y-axis coordinate */
    } field;                                                /**< Fields view */
    unsigned int overlay;                                   /**< Overlay view */
} v2d_input_layer_crop0_reg_t;

/**
 *@brief V2D input layer crop1 register
 */
typedef union
{
    struct
    {
        unsigned int layer_in_crop_width            : 16;   /**< input layer crop in width */
        unsigned int layer_in_crop_height           : 16;   /**< input layer crop in height */
    } field;                                                /**< Fields view */
    unsigned int overlay;                                   /**< Overlay view */
} v2d_input_layer_crop1_reg_t;

/**
 *@brief V2D input solid color control0 register
 */
typedef union
{
    struct
    {
        unsigned int solid_en              : 1;             /**< input layer solid color enable */
        unsigned int reserved              : 7;             /**< Rrserved */
        unsigned int solid_R               : 8;             /**< solid color R channel value */
        unsigned int solid_G               : 8;             /**< solid color G channel value */
        unsigned int solid_B               : 8;             /**< solid color B channel value */
    } field;                                                /**< Fields view */
    unsigned int overlay;                                   /**< Overlay view */
} v2d_solid_color_ctrl0_reg_t;

/**
 *@brief V2D input solid color control1 register
 */
typedef union
{
    struct
    {
        unsigned int solid_A               : 8;             /**< solid color alpha channel value */
        unsigned int csc_en                : 1;             /**< input layer csc enable */
        unsigned int reserved1             : 7;             /**< Rrserved */
        int csc_matrix0           : 13;                     /**< input layer csc matrix0 */
        unsigned int reserved2             : 3;             /**< Rrserved */
    } field;                                                /**< Fields view */
    unsigned int overlay;                                   /**< Overlay view */
} v2d_solid_color_ctrl1_reg_t;
typedef v2d_solid_color_ctrl1_reg_t v2d_input_layer_csc_ctrl0_reg_t;

/**
 *@brief V2D input layer csc control1~5 register
 */
typedef union
{
    struct
    {
        int csc_matrix1                    : 13;            /**< input layer csc matrix 2*i-1 */
        unsigned int reserved1             : 3;             /**< Rrserved */
        int csc_matrix2                    : 13;            /**< input layer csc matrix 2*i */
        unsigned int reserved2             : 3;             /**< Rrserved */
    } field;                                                /**< Fields view */
    unsigned int overlay;                                   /**< Overlay view */
} v2d_input_layer_csc_ctrl1_reg_t;

/**
 *@brief V2D input layer csc control6 register
 */
typedef union
{
    struct
    {
        int csc_matrix11                   : 13;            /**< input layer csc matrix11  */
        unsigned int scl_mode              : 2;             /**< scaler mode 0:bypass, 1:scale down, 2:scale up */
        unsigned int reserved1             : 17;            /**< Rrserved */
    } field;                                                /**< Fields view */
    unsigned int overlay;                                   /**< Overlay view */
} v2d_input_layer_csc_ctrl2_reg_t;
typedef v2d_input_layer_csc_ctrl2_reg_t v2d_input_layer_scale_mode_reg_t;

/**
 *@brief V2D input layer scale delta x register
 */
typedef union
{
    struct
    {
        unsigned int scl_delta_x           : 20;            /**< input layer scale delta x, (in_width<<16) /bld_rectWidth  */
        unsigned int reserved              : 12;            /**< Rrserved */
    } field;                                                /**< Fields view */
    unsigned int overlay;                                   /**< Overlay view */
} v2d_input_layer_scale_delta_x_reg_t;

/**
 *@brief V2D input layer scale delta y register
 */
typedef union
{
    struct
    {
        unsigned int scl_delta_y           : 20;            /**< input layer scale delta y, (in_height<<16) /bld_rectHeight  */
        unsigned int bld_alpha_source      : 2;             /**< blend alpha source, 0:pixel, 1:golbal, 2: mask value */
        unsigned int bld_pre_alp_func      : 2;             /**< blend premultiplied function, 0:disable, 1:global alpha* src_alpha, 2:mask*src_a */
        unsigned int bld_glb_alp           : 8;             /**< global alpha value */
    } field;                                                /**< Fields view */
    unsigned int overlay;                                   /**< Overlay view */
} v2d_input_layer_scale_delta_y_reg_t;
typedef v2d_input_layer_scale_delta_y_reg_t v2d_blend_layer_ctrl0_reg_t;

/**
 * @brief V2D Blend Layer Control1 register
 */
typedef union
{
    struct
    {
        unsigned int blend_en             : 1;              /**< blend layer enable */
        unsigned int reserved1            : 7;              /**< Reserved */
        unsigned int bld_rect_ltop_x      : 16;             /**< blend layer rectangle left-top point x-axis coordinate */
        unsigned int reserved2            : 8;              /**< Reserved */
    } field;                                                /**< Fields view */
    unsigned int overlay;                                   /**< Overlay view */
} v2d_blend_layer_ctrl1_reg_t;

/**
 * @brief V2D Blend Layer Control2 register
 */
typedef union
{
    struct
    {
        unsigned int bld_rect_ltop_y       : 16;            /**< blend layer rectangle left-top point y-axis coordinate */
        unsigned int bld_rect_width        : 16;            /**< blend layer rectangle width */
    } field;                                                /**< Fields view */
    unsigned int overlay;                                   /**< Overlay view */
} v2d_blend_layer_ctrl2_reg_t;

/**
 * @brief V2D Blend Layer Control3 register
 */
typedef union
{
    struct
    {
        unsigned int bld_rect_height            : 16;       /**< blend layer rectangle height */
        unsigned int reserved                   : 16;       /**< Reserved */
    } field;                                                /**< Fields view */
    unsigned int overlay;                                   /**< Overlay view */
} v2d_blend_layer_ctrl3_reg_t;

/**
 * @brief V2D FBC decoder bbox register
 */
typedef union
{
    struct
    {
        unsigned int bbox_start            : 13;            /**< v2d fbc decoder bbox start */
        unsigned int reserved1             : 3;             /**< Reserved */
        unsigned int bbox_end              : 13;            /**< v2d fbc decoder bbox end */
        unsigned int reserved2             : 3;             /**< Reserved */
    } field;                                                /**< Fields view */
    unsigned int overlay;                                   /**< Overlay view */
} v2d_fbc_decoder_bbox_reg_t;

/**
 * @brief V2D FBC decoder image size register
 */
typedef union
{
    struct
    {
        unsigned int width               : 16;              /**< v2d fbc decoder image width  */
        unsigned int height              : 16;              /**< v2d fbc decoder image height */
    } field;                                                /**< Fields view */
    unsigned int overlay;                                   /**< Overlay view */
} v2d_fbc_decoder_imgae_size_reg_t;

/**
 * @brief V2D FBC decoder mode register
 */
typedef union
{
    struct
    {
        unsigned int mode                : 3;               /**< v2d fbc decoder mode  */
        unsigned int format              : 3;               /**< v2d fbc decoder pixel format */
        unsigned int is_split            : 1;               /**< v2d fbc decoder split mode */
        unsigned int rgb_pack_en         : 1;               /**< v2d fbc decoder rgb pack enable */
        unsigned int reserved            : 24;              /**< Reserved */
    } field;                                                /**< Fields view */
    unsigned int overlay;                                   /**< Overlay view */
} v2d_fbc_decoder_mode_reg_t;

/**
 * @brief V2D FBC decoder dma control register
 */
typedef union
{
    struct
    {
        unsigned int dmac_arqos                : 4;         /**< v2d fbc decoder dma qos  */
        unsigned int damc_axi_sec              : 1;         /**< v2d fbc decoder dma axi sec */
        unsigned int dmac_user_id              : 4;         /**< v2d fbc decoder dma user id */
        unsigned int dmac_rstn_pwr             : 1;         /**< v2d fbc decoder dma rstn pwr */
        unsigned int dmac_rst_req              : 1;         /**< v2d fbc decoder dma rst req*/
        unsigned int dmac_max_req_num          : 3;         /**< v2d fbc decoder dma max req num */
        unsigned int dmac_arb_mode             : 2;         /**< v2d fbc decoder dma arb mode */
        unsigned int rdma_timeout_num          : 16;        /**< v2d fbc decoder dma timeout num */
    } field;                                                /**< Fields view */
    unsigned int overlay;                                   /**< Overlay view */
} v2d_fbc_decoder_dma_ctrl_reg_t;

/**
 * @brief V2D FBC decoder irq mask/raw/status register
 */
typedef union
{
    struct
    {
        unsigned int decode_eof               : 1;         /**< v2d fbc decoder eof irq mask  */
        unsigned int cfg_swaped               : 1;         /**< v2d fbc decoder cfg sswap irq mask */
        unsigned int dmac_err                 : 1;         /**< v2d fbc decoder dmac err irq mask */
        unsigned int rdma_timeout             : 1;         /**< v2d fbc decoder rdma timeout mask */
        unsigned int dec_err                  : 1;         /**< v2d fbc decoder decode err irq mask */
        unsigned int reserved                 : 27;        /**< Reserved */
    } field;                                               /**< Fields view */
    unsigned int overlay;                                  /**< Overlay view */
} v2d_fbc_decoder_irq_ctrl_reg_t;

/**
 * @brief V2D FBC decoder trigger register
 */
typedef union
{
    struct
    {
        unsigned int direct_swap               : 1;         /**< v2d fbc decoder direct swap  */
        unsigned int pending_swap              : 1;         /**< v2d fbc decoder pending swap */
        unsigned int reserved                  : 30;        /**< Reserved */
    } field;                                                /**< Fields view */
    unsigned int overlay;                                   /**< Overlay view */
} v2d_fbc_decoder_trigger_reg_t;

/**
 * @brief V2D FBC encoder bbox register
 */
typedef union
{
    struct
    {
        unsigned int bbox_start            : 16;            /**< v2d fbc encoder bbox start */
        unsigned int bbox_end              : 16;            /**< v2d fbc encoder bbox end */
    } field;                                                /**< Fields view */
    unsigned int overlay;                                   /**< Overlay view */
} v2d_fbc_encoder_bbox_reg_t;

/**
 * @brief V2D FBC encoder y or uv buf szie register
 */
typedef union
{
    struct
    {
        unsigned int x_size              : 16;              /**< v2d fbc encoder buf x size  */
        unsigned int y_size              : 16;              /**< v2d fbc encoder buf y size */
    } field;                                                /**< Fields view */
    unsigned int overlay;                                   /**< Overlay view */
} v2d_fbc_encoder_buf_size_reg_t;

/**
 * @brief V2D FBC encoder trigger register
 */
typedef union
{
    struct
    {
        unsigned int direct_swap               : 1;         /**< v2d fbc encoder direct swap  */
        unsigned int pending_swap              : 1;         /**< v2d fbc encoder pending swap */
        unsigned int reserved                  : 30;        /**< Reserved */
    } field;                                                /**< Fields view */
    unsigned int overlay;                                   /**< Overlay view */
} v2d_fbc_encoder_trigger_reg_t;

/**
 * @brief V2D FBC encoder irq mask,raw,status register
 */
typedef union
{
    struct
    {
        unsigned int dma_wr_err                    : 16;   /**< v2d fbc encoder dma wr err  */
        unsigned int dma_wr_eof                    : 1;    /**< v2d fbc encoder dma wr eof */
        unsigned int cfg_update_done               : 1;    /**< v2d fbc encoder cfg update done */
        unsigned int reserved                      : 14;   /**< Reserved */
    } field;                                               /**< Fields view */
    unsigned int overlay;                                  /**< Overlay view */
} v2d_fbc_encoder_irq_reg_t;

/**
 * @brief V2D FBC encoder mode register
 */
typedef union
{
    struct
    {
        unsigned int encode_enable                    : 1;  /**< v2d fbc encoder enable */
        unsigned int split_mode_en                    : 1;  /**< v2d fbc encoder split mode */
        unsigned int img_pix_format                   : 2;  /**< v2d fbc encoder pixel format */
        unsigned int reserved                         : 28; /**< Reserved */
    } field;                                                /**< Fields view */
    unsigned int overlay;                                   /**< Overlay view */
} v2d_fbc_encoder_mode_reg_t;

/**
 * @brief V2D FBC encoder dmac length register
 */
typedef union
{
    struct
    {
        unsigned int burst_length                     : 7;  /**< v2d fbc encoder dmac burst length */
        unsigned int reserved                         : 25; /**< Reserved */
    } field;                                                /**< Fields view */
    unsigned int overlay;                                   /**< Overlay view */
} v2d_fbc_encoder_dmac_burst_reg_t;

/**
*@brief V2D Top AXI bus control register
*/
typedef union
{
    struct
    {
        unsigned int arqos_m                      : 4;      /**< v2d axi bus read qos */
        unsigned int aruser_m                     : 4;      /**< v2d axi bus read user */
        unsigned int awqos_m                      : 4;      /** <v2d axi bus write qos */
        unsigned int awuser_m                     : 4;      /**< v2d axi bus write user */
        unsigned int shadow_mode                  : 1;      /**< v2d reg cfg is shadow mode */
        unsigned int reserved                     : 15;     /**< Reserved */
    } field;                                                /**< Fields view */
    unsigned int overlay;                                   /**< Overlay view */
} v2d_axi_bus_ctrl_reg_t;

#endif /* __SPACEMIT_V2D_REG_H__ */
