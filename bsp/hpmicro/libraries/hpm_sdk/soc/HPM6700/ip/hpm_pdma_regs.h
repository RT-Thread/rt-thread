/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_PDMA_H
#define HPM_PDMA_H

typedef struct {
    __RW uint32_t CTRL;                        /* 0x0: Control Register */
    __RW uint32_t STAT;                        /* 0x4: Status Register */
    __RW uint32_t OUT_CTRL;                    /* 0x8: Out Layer Control Register */
    __RW uint32_t OUT_BUF;                     /* 0xC: Output buffer address */
    __R  uint8_t  RESERVED0[4];                /* 0x10 - 0x13: Reserved */
    __RW uint32_t OUT_PITCH;                   /* 0x14: Outlayer Pitch Register */
    __RW uint32_t OUT_LRC;                     /* 0x18: Output Lower Right Corner Register */
    struct {
        __RW uint32_t ULC;                     /* 0x1C: Layer Upper Left Corner Register */
        __RW uint32_t LRC;                     /* 0x20: Layer Lower Right Corner Register */
    } OUT_PS[2];
    __R  uint8_t  RESERVED1[4];                /* 0x2C - 0x2F: Reserved */
    struct {
        __RW uint32_t CTRL;                    /* 0x30: Layer Control Register */
        __RW uint32_t BUF;                     /* 0x34: Layer data buffer address */
        __R  uint8_t  RESERVED0[8];            /* 0x38 - 0x3F: Reserved */
        __RW uint32_t PITCH;                   /* 0x40: Layer data pitch register */
        __RW uint32_t BKGD;                    /* 0x44: Layer background color register */
        __RW uint32_t SCALE;                   /* 0x48: Layer scale register */
        __RW uint32_t OFFSET;                  /* 0x4C: Layer offset register */
        __RW uint32_t CLRKEY_LOW;              /* 0x50: Layer low color key register */
        __RW uint32_t CLRKEY_HIGH;             /* 0x54: Layer high color key register */
        __RW uint32_t ORG;                     /* 0x58: Layer original size register */
        __R  uint8_t  RESERVED1[4];            /* 0x5C - 0x5F: Reserved */
    } PS[2];
    __R  uint8_t  RESERVED2[16];               /* 0x90 - 0x9F: Reserved */
    __RW uint32_t YUV2RGB_COEF0;               /* 0xA0: YUV2RGB coefficients register 0 */
    __RW uint32_t YUV2RGB_COEF1;               /* 0xA4: YUV2RGB coefficients register 1 */
    __RW uint32_t YUV2RGB_COEF2;               /* 0xA8: YUV2RGB coefficients register 2 */
    __RW uint32_t RGB2YUV_COEF0;               /* 0xAC: RGB2YUV coefficients register 0 */
    __RW uint32_t RGB2YUV_COEF1;               /* 0xB0: RGB2YUV coefficients register 1 */
    __RW uint32_t RGB2YUV_COEF2;               /* 0xB4: RGB2YUV coefficients register 2 */
    __RW uint32_t RGB2YUV_COEF3;               /* 0xB8: RGB2YUV coefficients register 3 */
    __RW uint32_t RGB2YUV_COEF4;               /* 0xBC: RGB2YUV coefficients register 4 */
} PDMA_Type;


/* Bitfield definition for register: CTRL */
/*
 * ARQOS (RW)
 *
 * QoS for AXI read bus
 */
#define PDMA_CTRL_ARQOS_MASK (0x780000UL)
#define PDMA_CTRL_ARQOS_SHIFT (19U)
#define PDMA_CTRL_ARQOS_SET(x) (((uint32_t)(x) << PDMA_CTRL_ARQOS_SHIFT) & PDMA_CTRL_ARQOS_MASK)
#define PDMA_CTRL_ARQOS_GET(x) (((uint32_t)(x) & PDMA_CTRL_ARQOS_MASK) >> PDMA_CTRL_ARQOS_SHIFT)

/*
 * AWQOS (RW)
 *
 * QoS for AXI write bus
 */
#define PDMA_CTRL_AWQOS_MASK (0x78000UL)
#define PDMA_CTRL_AWQOS_SHIFT (15U)
#define PDMA_CTRL_AWQOS_SET(x) (((uint32_t)(x) << PDMA_CTRL_AWQOS_SHIFT) & PDMA_CTRL_AWQOS_MASK)
#define PDMA_CTRL_AWQOS_GET(x) (((uint32_t)(x) & PDMA_CTRL_AWQOS_MASK) >> PDMA_CTRL_AWQOS_SHIFT)

/*
 * PACK_DIR (RW)
 *
 * Decide the byte sequence of the 32-bit output word {A3, A2, A1, A0}. The bit sequence ina byte is not changed.
 * 2'b00: no change {A3, A2, A1, A0}
 * 2'b01: {A2, A3, A0, A1}
 * 2'b10: {A1, A0, A3, A2}
 * 2'b11: {A0, A1, A2, A3}
 */
#define PDMA_CTRL_PACK_DIR_MASK (0x6000U)
#define PDMA_CTRL_PACK_DIR_SHIFT (13U)
#define PDMA_CTRL_PACK_DIR_SET(x) (((uint32_t)(x) << PDMA_CTRL_PACK_DIR_SHIFT) & PDMA_CTRL_PACK_DIR_MASK)
#define PDMA_CTRL_PACK_DIR_GET(x) (((uint32_t)(x) & PDMA_CTRL_PACK_DIR_MASK) >> PDMA_CTRL_PACK_DIR_SHIFT)

/*
 * AXIERR_IRQ_EN (RW)
 *
 * Enable interrupt of AXI bus error
 */
#define PDMA_CTRL_AXIERR_IRQ_EN_MASK (0x1000U)
#define PDMA_CTRL_AXIERR_IRQ_EN_SHIFT (12U)
#define PDMA_CTRL_AXIERR_IRQ_EN_SET(x) (((uint32_t)(x) << PDMA_CTRL_AXIERR_IRQ_EN_SHIFT) & PDMA_CTRL_AXIERR_IRQ_EN_MASK)
#define PDMA_CTRL_AXIERR_IRQ_EN_GET(x) (((uint32_t)(x) & PDMA_CTRL_AXIERR_IRQ_EN_MASK) >> PDMA_CTRL_AXIERR_IRQ_EN_SHIFT)

/*
 * PDMA_DONE_IRQ_EN (RW)
 *
 * Enable interrupt of PDMA_DONE
 */
#define PDMA_CTRL_PDMA_DONE_IRQ_EN_MASK (0x800U)
#define PDMA_CTRL_PDMA_DONE_IRQ_EN_SHIFT (11U)
#define PDMA_CTRL_PDMA_DONE_IRQ_EN_SET(x) (((uint32_t)(x) << PDMA_CTRL_PDMA_DONE_IRQ_EN_SHIFT) & PDMA_CTRL_PDMA_DONE_IRQ_EN_MASK)
#define PDMA_CTRL_PDMA_DONE_IRQ_EN_GET(x) (((uint32_t)(x) & PDMA_CTRL_PDMA_DONE_IRQ_EN_MASK) >> PDMA_CTRL_PDMA_DONE_IRQ_EN_SHIFT)

/*
 * CLKGATE (RW)
 *
 * Assert this bit to gate off clock when the module is not working. If reset to zero, the internal clock is always on.
 */
#define PDMA_CTRL_CLKGATE_MASK (0x200U)
#define PDMA_CTRL_CLKGATE_SHIFT (9U)
#define PDMA_CTRL_CLKGATE_SET(x) (((uint32_t)(x) << PDMA_CTRL_CLKGATE_SHIFT) & PDMA_CTRL_CLKGATE_MASK)
#define PDMA_CTRL_CLKGATE_GET(x) (((uint32_t)(x) & PDMA_CTRL_CLKGATE_MASK) >> PDMA_CTRL_CLKGATE_SHIFT)

/*
 * IRQ_EN (RW)
 *
 * Enable normal interrupt
 */
#define PDMA_CTRL_IRQ_EN_MASK (0x40U)
#define PDMA_CTRL_IRQ_EN_SHIFT (6U)
#define PDMA_CTRL_IRQ_EN_SET(x) (((uint32_t)(x) << PDMA_CTRL_IRQ_EN_SHIFT) & PDMA_CTRL_IRQ_EN_MASK)
#define PDMA_CTRL_IRQ_EN_GET(x) (((uint32_t)(x) & PDMA_CTRL_IRQ_EN_MASK) >> PDMA_CTRL_IRQ_EN_SHIFT)

/*
 * BS16 (RW)
 *
 * Asserted when the Block Size is 16x16, else 8x8
 */
#define PDMA_CTRL_BS16_MASK (0x20U)
#define PDMA_CTRL_BS16_SHIFT (5U)
#define PDMA_CTRL_BS16_SET(x) (((uint32_t)(x) << PDMA_CTRL_BS16_SHIFT) & PDMA_CTRL_BS16_MASK)
#define PDMA_CTRL_BS16_GET(x) (((uint32_t)(x) & PDMA_CTRL_BS16_MASK) >> PDMA_CTRL_BS16_SHIFT)

/*
 * P1_EN (RW)
 *
 * Plane 1 Enable
 */
#define PDMA_CTRL_P1_EN_MASK (0x10U)
#define PDMA_CTRL_P1_EN_SHIFT (4U)
#define PDMA_CTRL_P1_EN_SET(x) (((uint32_t)(x) << PDMA_CTRL_P1_EN_SHIFT) & PDMA_CTRL_P1_EN_MASK)
#define PDMA_CTRL_P1_EN_GET(x) (((uint32_t)(x) & PDMA_CTRL_P1_EN_MASK) >> PDMA_CTRL_P1_EN_SHIFT)

/*
 * P0_EN (RW)
 *
 * Plane 0 Enable
 */
#define PDMA_CTRL_P0_EN_MASK (0x8U)
#define PDMA_CTRL_P0_EN_SHIFT (3U)
#define PDMA_CTRL_P0_EN_SET(x) (((uint32_t)(x) << PDMA_CTRL_P0_EN_SHIFT) & PDMA_CTRL_P0_EN_MASK)
#define PDMA_CTRL_P0_EN_GET(x) (((uint32_t)(x) & PDMA_CTRL_P0_EN_MASK) >> PDMA_CTRL_P0_EN_SHIFT)

/*
 * PDMA_SFTRST (RW)
 *
 * Software Reset.
 * Write 1 to clear PDMA internal logic.
 * Write 0 to exit software reset mode.
 */
#define PDMA_CTRL_PDMA_SFTRST_MASK (0x2U)
#define PDMA_CTRL_PDMA_SFTRST_SHIFT (1U)
#define PDMA_CTRL_PDMA_SFTRST_SET(x) (((uint32_t)(x) << PDMA_CTRL_PDMA_SFTRST_SHIFT) & PDMA_CTRL_PDMA_SFTRST_MASK)
#define PDMA_CTRL_PDMA_SFTRST_GET(x) (((uint32_t)(x) & PDMA_CTRL_PDMA_SFTRST_MASK) >> PDMA_CTRL_PDMA_SFTRST_SHIFT)

/*
 * PDMA_EN (RW)
 *
 * 1b - Enabled
 */
#define PDMA_CTRL_PDMA_EN_MASK (0x1U)
#define PDMA_CTRL_PDMA_EN_SHIFT (0U)
#define PDMA_CTRL_PDMA_EN_SET(x) (((uint32_t)(x) << PDMA_CTRL_PDMA_EN_SHIFT) & PDMA_CTRL_PDMA_EN_MASK)
#define PDMA_CTRL_PDMA_EN_GET(x) (((uint32_t)(x) & PDMA_CTRL_PDMA_EN_MASK) >> PDMA_CTRL_PDMA_EN_SHIFT)

/* Bitfield definition for register: STAT */
/*
 * BLOCKY (RO)
 *
 * Y block that is processing
 */
#define PDMA_STAT_BLOCKY_MASK (0xFF000000UL)
#define PDMA_STAT_BLOCKY_SHIFT (24U)
#define PDMA_STAT_BLOCKY_GET(x) (((uint32_t)(x) & PDMA_STAT_BLOCKY_MASK) >> PDMA_STAT_BLOCKY_SHIFT)

/*
 * BLOCKX (RO)
 *
 * X block that is processing
 */
#define PDMA_STAT_BLOCKX_MASK (0xFF0000UL)
#define PDMA_STAT_BLOCKX_SHIFT (16U)
#define PDMA_STAT_BLOCKX_GET(x) (((uint32_t)(x) & PDMA_STAT_BLOCKX_MASK) >> PDMA_STAT_BLOCKX_SHIFT)

/*
 * PDMA_DONE (W1C)
 *
 * PDMA one image done
 */
#define PDMA_STAT_PDMA_DONE_MASK (0x200U)
#define PDMA_STAT_PDMA_DONE_SHIFT (9U)
#define PDMA_STAT_PDMA_DONE_SET(x) (((uint32_t)(x) << PDMA_STAT_PDMA_DONE_SHIFT) & PDMA_STAT_PDMA_DONE_MASK)
#define PDMA_STAT_PDMA_DONE_GET(x) (((uint32_t)(x) & PDMA_STAT_PDMA_DONE_MASK) >> PDMA_STAT_PDMA_DONE_SHIFT)

/*
 * AXI_ERR_ID (RO)
 *
 * AXI error ID
 */
#define PDMA_STAT_AXI_ERR_ID_MASK (0x1E0U)
#define PDMA_STAT_AXI_ERR_ID_SHIFT (5U)
#define PDMA_STAT_AXI_ERR_ID_GET(x) (((uint32_t)(x) & PDMA_STAT_AXI_ERR_ID_MASK) >> PDMA_STAT_AXI_ERR_ID_SHIFT)

/*
 * AXI_0_WRITE_ERR (W1C)
 *
 * AXI0 write err
 */
#define PDMA_STAT_AXI_0_WRITE_ERR_MASK (0x10U)
#define PDMA_STAT_AXI_0_WRITE_ERR_SHIFT (4U)
#define PDMA_STAT_AXI_0_WRITE_ERR_SET(x) (((uint32_t)(x) << PDMA_STAT_AXI_0_WRITE_ERR_SHIFT) & PDMA_STAT_AXI_0_WRITE_ERR_MASK)
#define PDMA_STAT_AXI_0_WRITE_ERR_GET(x) (((uint32_t)(x) & PDMA_STAT_AXI_0_WRITE_ERR_MASK) >> PDMA_STAT_AXI_0_WRITE_ERR_SHIFT)

/*
 * AXI_1_READ_ERR (W1C)
 *
 * AXI1 read err
 */
#define PDMA_STAT_AXI_1_READ_ERR_MASK (0x8U)
#define PDMA_STAT_AXI_1_READ_ERR_SHIFT (3U)
#define PDMA_STAT_AXI_1_READ_ERR_SET(x) (((uint32_t)(x) << PDMA_STAT_AXI_1_READ_ERR_SHIFT) & PDMA_STAT_AXI_1_READ_ERR_MASK)
#define PDMA_STAT_AXI_1_READ_ERR_GET(x) (((uint32_t)(x) & PDMA_STAT_AXI_1_READ_ERR_MASK) >> PDMA_STAT_AXI_1_READ_ERR_SHIFT)

/*
 * AXI_0_READ_ERR (W1C)
 *
 * AXI0 read err
 */
#define PDMA_STAT_AXI_0_READ_ERR_MASK (0x4U)
#define PDMA_STAT_AXI_0_READ_ERR_SHIFT (2U)
#define PDMA_STAT_AXI_0_READ_ERR_SET(x) (((uint32_t)(x) << PDMA_STAT_AXI_0_READ_ERR_SHIFT) & PDMA_STAT_AXI_0_READ_ERR_MASK)
#define PDMA_STAT_AXI_0_READ_ERR_GET(x) (((uint32_t)(x) & PDMA_STAT_AXI_0_READ_ERR_MASK) >> PDMA_STAT_AXI_0_READ_ERR_SHIFT)

/*
 * IRQ (RO)
 *
 * Asserted to indicate a IRQ event
 */
#define PDMA_STAT_IRQ_MASK (0x1U)
#define PDMA_STAT_IRQ_SHIFT (0U)
#define PDMA_STAT_IRQ_GET(x) (((uint32_t)(x) & PDMA_STAT_IRQ_MASK) >> PDMA_STAT_IRQ_SHIFT)

/* Bitfield definition for register: OUT_CTRL */
/*
 * DSTALPHA (RW)
 *
 * The destination (P1) system ALPHA value.
 */
#define PDMA_OUT_CTRL_DSTALPHA_MASK (0xFF000000UL)
#define PDMA_OUT_CTRL_DSTALPHA_SHIFT (24U)
#define PDMA_OUT_CTRL_DSTALPHA_SET(x) (((uint32_t)(x) << PDMA_OUT_CTRL_DSTALPHA_SHIFT) & PDMA_OUT_CTRL_DSTALPHA_MASK)
#define PDMA_OUT_CTRL_DSTALPHA_GET(x) (((uint32_t)(x) & PDMA_OUT_CTRL_DSTALPHA_MASK) >> PDMA_OUT_CTRL_DSTALPHA_SHIFT)

/*
 * SRCALPHA (RW)
 *
 * The source (P0) system ALPHA value.
 */
#define PDMA_OUT_CTRL_SRCALPHA_MASK (0xFF0000UL)
#define PDMA_OUT_CTRL_SRCALPHA_SHIFT (16U)
#define PDMA_OUT_CTRL_SRCALPHA_SET(x) (((uint32_t)(x) << PDMA_OUT_CTRL_SRCALPHA_SHIFT) & PDMA_OUT_CTRL_SRCALPHA_MASK)
#define PDMA_OUT_CTRL_SRCALPHA_GET(x) (((uint32_t)(x) & PDMA_OUT_CTRL_SRCALPHA_MASK) >> PDMA_OUT_CTRL_SRCALPHA_SHIFT)

/*
 * DSTALPHA_OP (RW)
 *
 * The usage of the DSTALPHA[7:0]: (The system alpha value is not the data valid mask, the non-zero alpha value per pixel embedded in the stream indicates a valid pixel. If no such per pixel alpha value, it means all the pixels are valid)
 * 0: the DSTALPHA[7:0] is invalid, use the alpha value embedded in the stream
 * 1: the DSTALPHA[7:0] is used to override the alpha value embedded in the stream.  (useful when the corresponding data stream has no alpha info)
 * 2: the DSTALPHA[7:0] is used to scale the alpha value embedded in the stream
 * Others: Reserved
 */
#define PDMA_OUT_CTRL_DSTALPHA_OP_MASK (0xC000U)
#define PDMA_OUT_CTRL_DSTALPHA_OP_SHIFT (14U)
#define PDMA_OUT_CTRL_DSTALPHA_OP_SET(x) (((uint32_t)(x) << PDMA_OUT_CTRL_DSTALPHA_OP_SHIFT) & PDMA_OUT_CTRL_DSTALPHA_OP_MASK)
#define PDMA_OUT_CTRL_DSTALPHA_OP_GET(x) (((uint32_t)(x) & PDMA_OUT_CTRL_DSTALPHA_OP_MASK) >> PDMA_OUT_CTRL_DSTALPHA_OP_SHIFT)

/*
 * SRCALPHA_OP (RW)
 *
 * The usage of the SRCALPHA[7:0]: (The system alpha value is not the data valid mask, the non-zero alpha value per pixel embedded in the stream indicates a valid pixel. If no such per pixel alpha value, it means all the pixels are valid)
 * 0: the SRCALPHA[7:0] is invalid, use the alpha value embedded in the stream
 * 1: the SRCALPHA[7:0] is used to override the alpha value embedded in the stream .  (useful when the corresponding data stream has no alpha info)
 * 2: the SRCALPHA[7:0] is used to scale the alpha value embedded in the stream
 * Others: Reserved
 */
#define PDMA_OUT_CTRL_SRCALPHA_OP_MASK (0x3000U)
#define PDMA_OUT_CTRL_SRCALPHA_OP_SHIFT (12U)
#define PDMA_OUT_CTRL_SRCALPHA_OP_SET(x) (((uint32_t)(x) << PDMA_OUT_CTRL_SRCALPHA_OP_SHIFT) & PDMA_OUT_CTRL_SRCALPHA_OP_MASK)
#define PDMA_OUT_CTRL_SRCALPHA_OP_GET(x) (((uint32_t)(x) & PDMA_OUT_CTRL_SRCALPHA_OP_MASK) >> PDMA_OUT_CTRL_SRCALPHA_OP_SHIFT)

/*
 * ABLEND_MODE (RW)
 *
 * Alpha Blending Mode
 * 0: SKBlendMode_Clear (If PS1_CTRL[BKGNDCL4CLR] is asserted, use PS1_BKGRND color to fill the range determined by PS1, else fill the range determined by PS1 with zero);
 * 1: SKBlendMode_Src ;
 * 2: SKBlendMode_Dst
 * 3: SKBlendMode_SrcOver
 * 4: SKBlendMode_DstOver
 * 5: SKBlendMode_SrcIn
 * 6: SKBlendMode_DstIn
 * 7: SKBlendMode_SrcOut
 * 8: SKBlendMode_DstOut
 * 9: SKBlendMode_SrcATop
 * 10: SKBlendMode_DstATop
 * 11: SKBlendMode_Xor
 * 12: SKBlendMode_Plus    (The conventional belding mode)
 * 13: SKBlendMode_Modulate
 * 14: SRC org
 * 15: DST org
 * Others: Reserved.
 */
#define PDMA_OUT_CTRL_ABLEND_MODE_MASK (0xF00U)
#define PDMA_OUT_CTRL_ABLEND_MODE_SHIFT (8U)
#define PDMA_OUT_CTRL_ABLEND_MODE_SET(x) (((uint32_t)(x) << PDMA_OUT_CTRL_ABLEND_MODE_SHIFT) & PDMA_OUT_CTRL_ABLEND_MODE_MASK)
#define PDMA_OUT_CTRL_ABLEND_MODE_GET(x) (((uint32_t)(x) & PDMA_OUT_CTRL_ABLEND_MODE_MASK) >> PDMA_OUT_CTRL_ABLEND_MODE_SHIFT)

/*
 * FORMAT (RW)
 *
 * Output buffer format.
 * 0x0 ARGB8888 - 32-bit pixles, byte sequence as B,G,R,A
 * 0xE RGB565 - 16-bit pixels, byte sequence as B,R
 * 0x12 UYVY1P422 - 16-bit pixels (1-plane , byte sequence as U0,Y0,V0,Y1)
 */
#define PDMA_OUT_CTRL_FORMAT_MASK (0x3FU)
#define PDMA_OUT_CTRL_FORMAT_SHIFT (0U)
#define PDMA_OUT_CTRL_FORMAT_SET(x) (((uint32_t)(x) << PDMA_OUT_CTRL_FORMAT_SHIFT) & PDMA_OUT_CTRL_FORMAT_MASK)
#define PDMA_OUT_CTRL_FORMAT_GET(x) (((uint32_t)(x) & PDMA_OUT_CTRL_FORMAT_MASK) >> PDMA_OUT_CTRL_FORMAT_SHIFT)

/* Bitfield definition for register: OUT_BUF */
/*
 * ADDR (RW)
 *
 * Current address pointer for the output frame buffer. The address can have any byte alignment. 64B alignment is recommended for optimal performance.
 */
#define PDMA_OUT_BUF_ADDR_MASK (0xFFFFFFFFUL)
#define PDMA_OUT_BUF_ADDR_SHIFT (0U)
#define PDMA_OUT_BUF_ADDR_SET(x) (((uint32_t)(x) << PDMA_OUT_BUF_ADDR_SHIFT) & PDMA_OUT_BUF_ADDR_MASK)
#define PDMA_OUT_BUF_ADDR_GET(x) (((uint32_t)(x) & PDMA_OUT_BUF_ADDR_MASK) >> PDMA_OUT_BUF_ADDR_SHIFT)

/* Bitfield definition for register: OUT_PITCH */
/*
 * BYTELEN (RW)
 *
 * Indicates the number of bytes in memory between two vertically adjacent pixels.
 */
#define PDMA_OUT_PITCH_BYTELEN_MASK (0xFFFFU)
#define PDMA_OUT_PITCH_BYTELEN_SHIFT (0U)
#define PDMA_OUT_PITCH_BYTELEN_SET(x) (((uint32_t)(x) << PDMA_OUT_PITCH_BYTELEN_SHIFT) & PDMA_OUT_PITCH_BYTELEN_MASK)
#define PDMA_OUT_PITCH_BYTELEN_GET(x) (((uint32_t)(x) & PDMA_OUT_PITCH_BYTELEN_MASK) >> PDMA_OUT_PITCH_BYTELEN_SHIFT)

/* Bitfield definition for register: OUT_LRC */
/*
 * Y (RW)
 *
 * This field indicates the lower right Y-coordinate (in pixels) of the output frame buffer.
 * The value is the height of the output image size.
 */
#define PDMA_OUT_LRC_Y_MASK (0x3FFF0000UL)
#define PDMA_OUT_LRC_Y_SHIFT (16U)
#define PDMA_OUT_LRC_Y_SET(x) (((uint32_t)(x) << PDMA_OUT_LRC_Y_SHIFT) & PDMA_OUT_LRC_Y_MASK)
#define PDMA_OUT_LRC_Y_GET(x) (((uint32_t)(x) & PDMA_OUT_LRC_Y_MASK) >> PDMA_OUT_LRC_Y_SHIFT)

/*
 * X (RW)
 *
 * This field indicates the lower right X-coordinate (in pixels) of the output frame buffer.
 * Should be the width of the output image size.
 */
#define PDMA_OUT_LRC_X_MASK (0x3FFFU)
#define PDMA_OUT_LRC_X_SHIFT (0U)
#define PDMA_OUT_LRC_X_SET(x) (((uint32_t)(x) << PDMA_OUT_LRC_X_SHIFT) & PDMA_OUT_LRC_X_MASK)
#define PDMA_OUT_LRC_X_GET(x) (((uint32_t)(x) & PDMA_OUT_LRC_X_MASK) >> PDMA_OUT_LRC_X_SHIFT)

/* Bitfield definition for register of struct array OUT_PS: ULC */
/*
 * Y (RW)
 *
 * This field indicates the upper left Y-coordinate (in pixels) of the processed surface in the output frame buffer.
 */
#define PDMA_OUT_PS_ULC_Y_MASK (0x3FFF0000UL)
#define PDMA_OUT_PS_ULC_Y_SHIFT (16U)
#define PDMA_OUT_PS_ULC_Y_SET(x) (((uint32_t)(x) << PDMA_OUT_PS_ULC_Y_SHIFT) & PDMA_OUT_PS_ULC_Y_MASK)
#define PDMA_OUT_PS_ULC_Y_GET(x) (((uint32_t)(x) & PDMA_OUT_PS_ULC_Y_MASK) >> PDMA_OUT_PS_ULC_Y_SHIFT)

/*
 * X (RW)
 *
 * This field indicates the upper left X-coordinate (in pixels) of the processed surface in the output frame buffer.
 */
#define PDMA_OUT_PS_ULC_X_MASK (0x3FFFU)
#define PDMA_OUT_PS_ULC_X_SHIFT (0U)
#define PDMA_OUT_PS_ULC_X_SET(x) (((uint32_t)(x) << PDMA_OUT_PS_ULC_X_SHIFT) & PDMA_OUT_PS_ULC_X_MASK)
#define PDMA_OUT_PS_ULC_X_GET(x) (((uint32_t)(x) & PDMA_OUT_PS_ULC_X_MASK) >> PDMA_OUT_PS_ULC_X_SHIFT)

/* Bitfield definition for register of struct array OUT_PS: LRC */
/*
 * Y (RW)
 *
 * This field indicates the lower right Y-coordinate (in pixels) of the processed surface in the output frame buffer.
 */
#define PDMA_OUT_PS_LRC_Y_MASK (0x3FFF0000UL)
#define PDMA_OUT_PS_LRC_Y_SHIFT (16U)
#define PDMA_OUT_PS_LRC_Y_SET(x) (((uint32_t)(x) << PDMA_OUT_PS_LRC_Y_SHIFT) & PDMA_OUT_PS_LRC_Y_MASK)
#define PDMA_OUT_PS_LRC_Y_GET(x) (((uint32_t)(x) & PDMA_OUT_PS_LRC_Y_MASK) >> PDMA_OUT_PS_LRC_Y_SHIFT)

/*
 * X (RW)
 *
 * This field indicates the lower right X-coordinate (in pixels) of the processed surface in the output frame buffer.
 */
#define PDMA_OUT_PS_LRC_X_MASK (0x3FFFU)
#define PDMA_OUT_PS_LRC_X_SHIFT (0U)
#define PDMA_OUT_PS_LRC_X_SET(x) (((uint32_t)(x) << PDMA_OUT_PS_LRC_X_SHIFT) & PDMA_OUT_PS_LRC_X_MASK)
#define PDMA_OUT_PS_LRC_X_GET(x) (((uint32_t)(x) & PDMA_OUT_PS_LRC_X_MASK) >> PDMA_OUT_PS_LRC_X_SHIFT)

/* Bitfield definition for register of struct array PS: CTRL */
/*
 * INB13_SWAP (RW)
 *
 * Swap bit[31:24] and bit [15:8] before pack_dir operation.
 */
#define PDMA_PS_CTRL_INB13_SWAP_MASK (0x100000UL)
#define PDMA_PS_CTRL_INB13_SWAP_SHIFT (20U)
#define PDMA_PS_CTRL_INB13_SWAP_SET(x) (((uint32_t)(x) << PDMA_PS_CTRL_INB13_SWAP_SHIFT) & PDMA_PS_CTRL_INB13_SWAP_MASK)
#define PDMA_PS_CTRL_INB13_SWAP_GET(x) (((uint32_t)(x) & PDMA_PS_CTRL_INB13_SWAP_MASK) >> PDMA_PS_CTRL_INB13_SWAP_SHIFT)

/*
 * PACK_DIR (RW)
 *
 * Decide the byte sequence of the 32-bit word {A3, A2, A1, A0}. The bit sequence ina byte is not changed.
 * 2'b00: no change {A3, A2, A1, A0}
 * 2'b01: {A2, A3, A0, A1}
 * 2'b10: {A1, A0, A3, A2}
 * 2'b11: {A0, A1, A2, A3}
 */
#define PDMA_PS_CTRL_PACK_DIR_MASK (0xC0000UL)
#define PDMA_PS_CTRL_PACK_DIR_SHIFT (18U)
#define PDMA_PS_CTRL_PACK_DIR_SET(x) (((uint32_t)(x) << PDMA_PS_CTRL_PACK_DIR_SHIFT) & PDMA_PS_CTRL_PACK_DIR_MASK)
#define PDMA_PS_CTRL_PACK_DIR_GET(x) (((uint32_t)(x) & PDMA_PS_CTRL_PACK_DIR_MASK) >> PDMA_PS_CTRL_PACK_DIR_SHIFT)

/*
 * BKGCL4CLR (RW)
 *
 * Enable to use background color for clear area
 */
#define PDMA_PS_CTRL_BKGCL4CLR_MASK (0x20000UL)
#define PDMA_PS_CTRL_BKGCL4CLR_SHIFT (17U)
#define PDMA_PS_CTRL_BKGCL4CLR_SET(x) (((uint32_t)(x) << PDMA_PS_CTRL_BKGCL4CLR_SHIFT) & PDMA_PS_CTRL_BKGCL4CLR_MASK)
#define PDMA_PS_CTRL_BKGCL4CLR_GET(x) (((uint32_t)(x) & PDMA_PS_CTRL_BKGCL4CLR_MASK) >> PDMA_PS_CTRL_BKGCL4CLR_SHIFT)

/*
 * YCBCR_MODE (RW)
 *
 * YCbCr mode or YUV mode
 */
#define PDMA_PS_CTRL_YCBCR_MODE_MASK (0x10000UL)
#define PDMA_PS_CTRL_YCBCR_MODE_SHIFT (16U)
#define PDMA_PS_CTRL_YCBCR_MODE_SET(x) (((uint32_t)(x) << PDMA_PS_CTRL_YCBCR_MODE_SHIFT) & PDMA_PS_CTRL_YCBCR_MODE_MASK)
#define PDMA_PS_CTRL_YCBCR_MODE_GET(x) (((uint32_t)(x) & PDMA_PS_CTRL_YCBCR_MODE_MASK) >> PDMA_PS_CTRL_YCBCR_MODE_SHIFT)

/*
 * BYPASS (RW)
 *
 * Asserted to bypass the CSC stage
 */
#define PDMA_PS_CTRL_BYPASS_MASK (0x8000U)
#define PDMA_PS_CTRL_BYPASS_SHIFT (15U)
#define PDMA_PS_CTRL_BYPASS_SET(x) (((uint32_t)(x) << PDMA_PS_CTRL_BYPASS_SHIFT) & PDMA_PS_CTRL_BYPASS_MASK)
#define PDMA_PS_CTRL_BYPASS_GET(x) (((uint32_t)(x) & PDMA_PS_CTRL_BYPASS_MASK) >> PDMA_PS_CTRL_BYPASS_SHIFT)

/*
 * VFLIP (RW)
 *
 * Indicates that the input should be flipped vertically (effect applied before rotation).
 */
#define PDMA_PS_CTRL_VFLIP_MASK (0x4000U)
#define PDMA_PS_CTRL_VFLIP_SHIFT (14U)
#define PDMA_PS_CTRL_VFLIP_SET(x) (((uint32_t)(x) << PDMA_PS_CTRL_VFLIP_SHIFT) & PDMA_PS_CTRL_VFLIP_MASK)
#define PDMA_PS_CTRL_VFLIP_GET(x) (((uint32_t)(x) & PDMA_PS_CTRL_VFLIP_MASK) >> PDMA_PS_CTRL_VFLIP_SHIFT)

/*
 * HFLIP (RW)
 *
 * Indicates that the input should be flipped horizontally (effect applied before rotation).
 */
#define PDMA_PS_CTRL_HFLIP_MASK (0x2000U)
#define PDMA_PS_CTRL_HFLIP_SHIFT (13U)
#define PDMA_PS_CTRL_HFLIP_SET(x) (((uint32_t)(x) << PDMA_PS_CTRL_HFLIP_SHIFT) & PDMA_PS_CTRL_HFLIP_MASK)
#define PDMA_PS_CTRL_HFLIP_GET(x) (((uint32_t)(x) & PDMA_PS_CTRL_HFLIP_MASK) >> PDMA_PS_CTRL_HFLIP_SHIFT)

/*
 * ROTATE (RW)
 *
 * Indicates the clockwise rotation to be applied at the input buffer. The rotation effect is defined as occurring
 * after the FLIP_X and FLIP_Y permutation.
 * 0x0 ROT_0
 * 0x1 ROT_90
 * 0x2 ROT_180
 * 0x3 ROT_270
 */
#define PDMA_PS_CTRL_ROTATE_MASK (0x1800U)
#define PDMA_PS_CTRL_ROTATE_SHIFT (11U)
#define PDMA_PS_CTRL_ROTATE_SET(x) (((uint32_t)(x) << PDMA_PS_CTRL_ROTATE_SHIFT) & PDMA_PS_CTRL_ROTATE_MASK)
#define PDMA_PS_CTRL_ROTATE_GET(x) (((uint32_t)(x) & PDMA_PS_CTRL_ROTATE_MASK) >> PDMA_PS_CTRL_ROTATE_SHIFT)

/*
 * DECY (RW)
 *
 * Verticle pre decimation filter control.
 * 0x0 DISABLE - Disable pre-decimation filter.
 * 0x1 DECY2  - Decimate PS by 2.
 * 0x2 DECY4 - Decimate PS by 4.
 * 0x3 DECY8 - Decimate PS by 8.
 */
#define PDMA_PS_CTRL_DECY_MASK (0x600U)
#define PDMA_PS_CTRL_DECY_SHIFT (9U)
#define PDMA_PS_CTRL_DECY_SET(x) (((uint32_t)(x) << PDMA_PS_CTRL_DECY_SHIFT) & PDMA_PS_CTRL_DECY_MASK)
#define PDMA_PS_CTRL_DECY_GET(x) (((uint32_t)(x) & PDMA_PS_CTRL_DECY_MASK) >> PDMA_PS_CTRL_DECY_SHIFT)

/*
 * DECX (RW)
 *
 * Horizontal pre decimation filter control.
 * 0x0 DISABLE - Disable pre-decimation filter.
 * 0x1 DECX2 - Decimate PS by 2.
 * 0x2 DECX4 - Decimate PS by 4.
 * 0x3 DECX8 - Decimate PS by 8.
 */
#define PDMA_PS_CTRL_DECX_MASK (0x180U)
#define PDMA_PS_CTRL_DECX_SHIFT (7U)
#define PDMA_PS_CTRL_DECX_SET(x) (((uint32_t)(x) << PDMA_PS_CTRL_DECX_SHIFT) & PDMA_PS_CTRL_DECX_MASK)
#define PDMA_PS_CTRL_DECX_GET(x) (((uint32_t)(x) & PDMA_PS_CTRL_DECX_MASK) >> PDMA_PS_CTRL_DECX_SHIFT)

/*
 * HW_BYTE_SWAP (RW)
 *
 * Swap bytes in half-words. For each 16 bit half-word, the two bytes will be swapped.
 */
#define PDMA_PS_CTRL_HW_BYTE_SWAP_MASK (0x40U)
#define PDMA_PS_CTRL_HW_BYTE_SWAP_SHIFT (6U)
#define PDMA_PS_CTRL_HW_BYTE_SWAP_SET(x) (((uint32_t)(x) << PDMA_PS_CTRL_HW_BYTE_SWAP_SHIFT) & PDMA_PS_CTRL_HW_BYTE_SWAP_MASK)
#define PDMA_PS_CTRL_HW_BYTE_SWAP_GET(x) (((uint32_t)(x) & PDMA_PS_CTRL_HW_BYTE_SWAP_MASK) >> PDMA_PS_CTRL_HW_BYTE_SWAP_SHIFT)

/*
 * FORMAT (RW)
 *
 * PS buffer format. To select between YUV and YCbCr formats, see bit 16 of this register.
 * 0x0 ARGB888 - 32-bit pixels, byte sequence as B,G,R,A
 * 0xE RGB565 - 16-bit pixels, byte sequence as B,R
 * 0x13 YUYV1P422 - 16-bit pixels (1-plane byte sequence Y0,U0,Y1,V0 interleaved bytes)
 */
#define PDMA_PS_CTRL_FORMAT_MASK (0x3FU)
#define PDMA_PS_CTRL_FORMAT_SHIFT (0U)
#define PDMA_PS_CTRL_FORMAT_SET(x) (((uint32_t)(x) << PDMA_PS_CTRL_FORMAT_SHIFT) & PDMA_PS_CTRL_FORMAT_MASK)
#define PDMA_PS_CTRL_FORMAT_GET(x) (((uint32_t)(x) & PDMA_PS_CTRL_FORMAT_MASK) >> PDMA_PS_CTRL_FORMAT_SHIFT)

/* Bitfield definition for register of struct array PS: BUF */
/*
 * ADDR (RW)
 *
 * Address pointer for the PS RGB or Y (luma) input buffer.
 */
#define PDMA_PS_BUF_ADDR_MASK (0xFFFFFFFFUL)
#define PDMA_PS_BUF_ADDR_SHIFT (0U)
#define PDMA_PS_BUF_ADDR_SET(x) (((uint32_t)(x) << PDMA_PS_BUF_ADDR_SHIFT) & PDMA_PS_BUF_ADDR_MASK)
#define PDMA_PS_BUF_ADDR_GET(x) (((uint32_t)(x) & PDMA_PS_BUF_ADDR_MASK) >> PDMA_PS_BUF_ADDR_SHIFT)

/* Bitfield definition for register of struct array PS: PITCH */
/*
 * BYTELEN (RW)
 *
 * Indicates the number of bytes in memory between two vertically adjacent pixels.
 */
#define PDMA_PS_PITCH_BYTELEN_MASK (0xFFFFU)
#define PDMA_PS_PITCH_BYTELEN_SHIFT (0U)
#define PDMA_PS_PITCH_BYTELEN_SET(x) (((uint32_t)(x) << PDMA_PS_PITCH_BYTELEN_SHIFT) & PDMA_PS_PITCH_BYTELEN_MASK)
#define PDMA_PS_PITCH_BYTELEN_GET(x) (((uint32_t)(x) & PDMA_PS_PITCH_BYTELEN_MASK) >> PDMA_PS_PITCH_BYTELEN_SHIFT)

/* Bitfield definition for register of struct array PS: BKGD */
/*
 * COLOR (RW)
 *
 * Background color (in 32bpp format) for any pixels not within the scaled range of the picture, but within the buffer range specified by the PS ULC/LRC. The top 8-bit is the alpha channel.
 */
#define PDMA_PS_BKGD_COLOR_MASK (0xFFFFFFFFUL)
#define PDMA_PS_BKGD_COLOR_SHIFT (0U)
#define PDMA_PS_BKGD_COLOR_SET(x) (((uint32_t)(x) << PDMA_PS_BKGD_COLOR_SHIFT) & PDMA_PS_BKGD_COLOR_MASK)
#define PDMA_PS_BKGD_COLOR_GET(x) (((uint32_t)(x) & PDMA_PS_BKGD_COLOR_MASK) >> PDMA_PS_BKGD_COLOR_SHIFT)

/* Bitfield definition for register of struct array PS: SCALE */
/*
 * Y (RW)
 *
 * This is a two bit integer and 12 bit fractional representation (##.####_####_####) of the X scaling factor for the PS source buffer. The maximum value programmed should be 2 since scaling down by a factor greater than 2 is not supported with the bilinear filter. Decimation and the bilinear filter should be used together to achieve scaling by more than a factor of 2.
 */
#define PDMA_PS_SCALE_Y_MASK (0x7FFF0000UL)
#define PDMA_PS_SCALE_Y_SHIFT (16U)
#define PDMA_PS_SCALE_Y_SET(x) (((uint32_t)(x) << PDMA_PS_SCALE_Y_SHIFT) & PDMA_PS_SCALE_Y_MASK)
#define PDMA_PS_SCALE_Y_GET(x) (((uint32_t)(x) & PDMA_PS_SCALE_Y_MASK) >> PDMA_PS_SCALE_Y_SHIFT)

/*
 * X (RW)
 *
 * This is a two bit integer and 12 bit fractional representation (##.####_####_####) of the Y scaling factor for the PS source buffer. The maximum value programmed should be 2 since scaling down by a factor greater than 2 is not supported with the bilinear filter. Decimation and the bilinear filter should be used together to achieve scaling by more than a factor of 2.
 */
#define PDMA_PS_SCALE_X_MASK (0x7FFFU)
#define PDMA_PS_SCALE_X_SHIFT (0U)
#define PDMA_PS_SCALE_X_SET(x) (((uint32_t)(x) << PDMA_PS_SCALE_X_SHIFT) & PDMA_PS_SCALE_X_MASK)
#define PDMA_PS_SCALE_X_GET(x) (((uint32_t)(x) & PDMA_PS_SCALE_X_MASK) >> PDMA_PS_SCALE_X_SHIFT)

/* Bitfield definition for register of struct array PS: OFFSET */
/*
 * Y (RW)
 *
 * This is a 12 bit fractional representation (0.####_####_####) of the Y scaling offset. This represents a fixed pixel offset which gets added to the scaled address to determine source data for the scaling engine.
 * It is applied after the decimation filter stage, and before the bilinear filter stage.
 */
#define PDMA_PS_OFFSET_Y_MASK (0xFFF0000UL)
#define PDMA_PS_OFFSET_Y_SHIFT (16U)
#define PDMA_PS_OFFSET_Y_SET(x) (((uint32_t)(x) << PDMA_PS_OFFSET_Y_SHIFT) & PDMA_PS_OFFSET_Y_MASK)
#define PDMA_PS_OFFSET_Y_GET(x) (((uint32_t)(x) & PDMA_PS_OFFSET_Y_MASK) >> PDMA_PS_OFFSET_Y_SHIFT)

/*
 * X (RW)
 *
 * This is a 12 bit fractional representation (0.####_####_####) of the X scaling offset. This represents a fixed pixel offset which gets added to the scaled address to determine source data for the scaling engine.
 * It is applied after the decimation filter stage, and before the bilinear filter stage.
 */
#define PDMA_PS_OFFSET_X_MASK (0xFFFU)
#define PDMA_PS_OFFSET_X_SHIFT (0U)
#define PDMA_PS_OFFSET_X_SET(x) (((uint32_t)(x) << PDMA_PS_OFFSET_X_SHIFT) & PDMA_PS_OFFSET_X_MASK)
#define PDMA_PS_OFFSET_X_GET(x) (((uint32_t)(x) & PDMA_PS_OFFSET_X_MASK) >> PDMA_PS_OFFSET_X_SHIFT)

/* Bitfield definition for register of struct array PS: CLRKEY_LOW */
/*
 * LIMIT (RW)
 *
 * Low range of color key applied to PS buffer. To disable PS colorkeying, set the low colorkey to 0xFFFFFF and the high colorkey to 0x000000.
 */
#define PDMA_PS_CLRKEY_LOW_LIMIT_MASK (0xFFFFFFUL)
#define PDMA_PS_CLRKEY_LOW_LIMIT_SHIFT (0U)
#define PDMA_PS_CLRKEY_LOW_LIMIT_SET(x) (((uint32_t)(x) << PDMA_PS_CLRKEY_LOW_LIMIT_SHIFT) & PDMA_PS_CLRKEY_LOW_LIMIT_MASK)
#define PDMA_PS_CLRKEY_LOW_LIMIT_GET(x) (((uint32_t)(x) & PDMA_PS_CLRKEY_LOW_LIMIT_MASK) >> PDMA_PS_CLRKEY_LOW_LIMIT_SHIFT)

/* Bitfield definition for register of struct array PS: CLRKEY_HIGH */
/*
 * LIMIT (RW)
 *
 * High range of color key applied to PS buffer. To disable PS colorkeying, set the low colorkey to 0xFFFFFF and the high colorkey to 0x000000
 */
#define PDMA_PS_CLRKEY_HIGH_LIMIT_MASK (0xFFFFFFUL)
#define PDMA_PS_CLRKEY_HIGH_LIMIT_SHIFT (0U)
#define PDMA_PS_CLRKEY_HIGH_LIMIT_SET(x) (((uint32_t)(x) << PDMA_PS_CLRKEY_HIGH_LIMIT_SHIFT) & PDMA_PS_CLRKEY_HIGH_LIMIT_MASK)
#define PDMA_PS_CLRKEY_HIGH_LIMIT_GET(x) (((uint32_t)(x) & PDMA_PS_CLRKEY_HIGH_LIMIT_MASK) >> PDMA_PS_CLRKEY_HIGH_LIMIT_SHIFT)

/* Bitfield definition for register of struct array PS: ORG */
/*
 * HIGHT (RW)
 *
 * The number of vertical pixels of the original frame (not -1)
 */
#define PDMA_PS_ORG_HIGHT_MASK (0x3FFF0000UL)
#define PDMA_PS_ORG_HIGHT_SHIFT (16U)
#define PDMA_PS_ORG_HIGHT_SET(x) (((uint32_t)(x) << PDMA_PS_ORG_HIGHT_SHIFT) & PDMA_PS_ORG_HIGHT_MASK)
#define PDMA_PS_ORG_HIGHT_GET(x) (((uint32_t)(x) & PDMA_PS_ORG_HIGHT_MASK) >> PDMA_PS_ORG_HIGHT_SHIFT)

/*
 * WIDTH (RW)
 *
 * The number of horizontal pixels of the original frame (not -1)
 */
#define PDMA_PS_ORG_WIDTH_MASK (0x3FFFU)
#define PDMA_PS_ORG_WIDTH_SHIFT (0U)
#define PDMA_PS_ORG_WIDTH_SET(x) (((uint32_t)(x) << PDMA_PS_ORG_WIDTH_SHIFT) & PDMA_PS_ORG_WIDTH_MASK)
#define PDMA_PS_ORG_WIDTH_GET(x) (((uint32_t)(x) & PDMA_PS_ORG_WIDTH_MASK) >> PDMA_PS_ORG_WIDTH_SHIFT)

/* Bitfield definition for register: YUV2RGB_COEF0 */
/*
 * C0 (RW)
 *
 * Two's compliment Y multiplier coefficient C0. YUV=0x100 (1.000) YCbCr=0x12A (1.164)
 */
#define PDMA_YUV2RGB_COEF0_C0_MASK (0x1FFC0000UL)
#define PDMA_YUV2RGB_COEF0_C0_SHIFT (18U)
#define PDMA_YUV2RGB_COEF0_C0_SET(x) (((uint32_t)(x) << PDMA_YUV2RGB_COEF0_C0_SHIFT) & PDMA_YUV2RGB_COEF0_C0_MASK)
#define PDMA_YUV2RGB_COEF0_C0_GET(x) (((uint32_t)(x) & PDMA_YUV2RGB_COEF0_C0_MASK) >> PDMA_YUV2RGB_COEF0_C0_SHIFT)

/*
 * UV_OFFSET (RW)
 *
 * Two's compliment phase offset implicit for CbCr data UV_OFFSET. Generally used for YCbCr to RGB conversion.
 * YCbCr=0x180, YUV=0x000 (typically -128 or 0x180 to indicate normalized -0.5 to 0.5 range).
 */
#define PDMA_YUV2RGB_COEF0_UV_OFFSET_MASK (0x3FE00UL)
#define PDMA_YUV2RGB_COEF0_UV_OFFSET_SHIFT (9U)
#define PDMA_YUV2RGB_COEF0_UV_OFFSET_SET(x) (((uint32_t)(x) << PDMA_YUV2RGB_COEF0_UV_OFFSET_SHIFT) & PDMA_YUV2RGB_COEF0_UV_OFFSET_MASK)
#define PDMA_YUV2RGB_COEF0_UV_OFFSET_GET(x) (((uint32_t)(x) & PDMA_YUV2RGB_COEF0_UV_OFFSET_MASK) >> PDMA_YUV2RGB_COEF0_UV_OFFSET_SHIFT)

/*
 * Y_OFFSET (RW)
 *
 * Two's compliment amplitude offset implicit in the Y data Y_OFFSET. For YUV, this is typically 0 and for YCbCr, this is
 * typically -16 (0x1F0).
 */
#define PDMA_YUV2RGB_COEF0_Y_OFFSET_MASK (0x1FFU)
#define PDMA_YUV2RGB_COEF0_Y_OFFSET_SHIFT (0U)
#define PDMA_YUV2RGB_COEF0_Y_OFFSET_SET(x) (((uint32_t)(x) << PDMA_YUV2RGB_COEF0_Y_OFFSET_SHIFT) & PDMA_YUV2RGB_COEF0_Y_OFFSET_MASK)
#define PDMA_YUV2RGB_COEF0_Y_OFFSET_GET(x) (((uint32_t)(x) & PDMA_YUV2RGB_COEF0_Y_OFFSET_MASK) >> PDMA_YUV2RGB_COEF0_Y_OFFSET_SHIFT)

/* Bitfield definition for register: YUV2RGB_COEF1 */
/*
 * C1 (RW)
 *
 * Two's compliment Red V/Cr multiplier coefficient C1. YUV=0x123 (1.140) YCbCr=0x198 (1.596).
 */
#define PDMA_YUV2RGB_COEF1_C1_MASK (0x7FF0000UL)
#define PDMA_YUV2RGB_COEF1_C1_SHIFT (16U)
#define PDMA_YUV2RGB_COEF1_C1_SET(x) (((uint32_t)(x) << PDMA_YUV2RGB_COEF1_C1_SHIFT) & PDMA_YUV2RGB_COEF1_C1_MASK)
#define PDMA_YUV2RGB_COEF1_C1_GET(x) (((uint32_t)(x) & PDMA_YUV2RGB_COEF1_C1_MASK) >> PDMA_YUV2RGB_COEF1_C1_SHIFT)

/*
 * C4 (RW)
 *
 * Two's compliment Blue U/Cb multiplier coefficient C4. YUV=0x208 (2.032) YCbCr=0x204 (2.017).
 */
#define PDMA_YUV2RGB_COEF1_C4_MASK (0x7FFU)
#define PDMA_YUV2RGB_COEF1_C4_SHIFT (0U)
#define PDMA_YUV2RGB_COEF1_C4_SET(x) (((uint32_t)(x) << PDMA_YUV2RGB_COEF1_C4_SHIFT) & PDMA_YUV2RGB_COEF1_C4_MASK)
#define PDMA_YUV2RGB_COEF1_C4_GET(x) (((uint32_t)(x) & PDMA_YUV2RGB_COEF1_C4_MASK) >> PDMA_YUV2RGB_COEF1_C4_SHIFT)

/* Bitfield definition for register: YUV2RGB_COEF2 */
/*
 * C2 (RW)
 *
 * Two's compliment Green V/Cr multiplier coefficient C2. YUV=0x76B (-0.581) YCbCr=0x730 (-0.813).
 */
#define PDMA_YUV2RGB_COEF2_C2_MASK (0x7FF0000UL)
#define PDMA_YUV2RGB_COEF2_C2_SHIFT (16U)
#define PDMA_YUV2RGB_COEF2_C2_SET(x) (((uint32_t)(x) << PDMA_YUV2RGB_COEF2_C2_SHIFT) & PDMA_YUV2RGB_COEF2_C2_MASK)
#define PDMA_YUV2RGB_COEF2_C2_GET(x) (((uint32_t)(x) & PDMA_YUV2RGB_COEF2_C2_MASK) >> PDMA_YUV2RGB_COEF2_C2_SHIFT)

/*
 * C3 (RW)
 *
 * Two's compliment Green U/Cb multiplier coefficient C3. YUV=0x79C (-0.394) YCbCr=0x79C (-0.392).
 */
#define PDMA_YUV2RGB_COEF2_C3_MASK (0x7FFU)
#define PDMA_YUV2RGB_COEF2_C3_SHIFT (0U)
#define PDMA_YUV2RGB_COEF2_C3_SET(x) (((uint32_t)(x) << PDMA_YUV2RGB_COEF2_C3_SHIFT) & PDMA_YUV2RGB_COEF2_C3_MASK)
#define PDMA_YUV2RGB_COEF2_C3_GET(x) (((uint32_t)(x) & PDMA_YUV2RGB_COEF2_C3_MASK) >> PDMA_YUV2RGB_COEF2_C3_SHIFT)

/* Bitfield definition for register: RGB2YUV_COEF0 */
/*
 * YCBCR_MODE (RW)
 *
 * Asserted to use YCrCb mode
 */
#define PDMA_RGB2YUV_COEF0_YCBCR_MODE_MASK (0x80000000UL)
#define PDMA_RGB2YUV_COEF0_YCBCR_MODE_SHIFT (31U)
#define PDMA_RGB2YUV_COEF0_YCBCR_MODE_SET(x) (((uint32_t)(x) << PDMA_RGB2YUV_COEF0_YCBCR_MODE_SHIFT) & PDMA_RGB2YUV_COEF0_YCBCR_MODE_MASK)
#define PDMA_RGB2YUV_COEF0_YCBCR_MODE_GET(x) (((uint32_t)(x) & PDMA_RGB2YUV_COEF0_YCBCR_MODE_MASK) >> PDMA_RGB2YUV_COEF0_YCBCR_MODE_SHIFT)

/*
 * ENABLE (RW)
 *
 * Asserted to enable this RGB2YUV CSC stage
 */
#define PDMA_RGB2YUV_COEF0_ENABLE_MASK (0x40000000UL)
#define PDMA_RGB2YUV_COEF0_ENABLE_SHIFT (30U)
#define PDMA_RGB2YUV_COEF0_ENABLE_SET(x) (((uint32_t)(x) << PDMA_RGB2YUV_COEF0_ENABLE_SHIFT) & PDMA_RGB2YUV_COEF0_ENABLE_MASK)
#define PDMA_RGB2YUV_COEF0_ENABLE_GET(x) (((uint32_t)(x) & PDMA_RGB2YUV_COEF0_ENABLE_MASK) >> PDMA_RGB2YUV_COEF0_ENABLE_SHIFT)

/*
 * C0 (RW)
 *
 * CSC parameters C0
 */
#define PDMA_RGB2YUV_COEF0_C0_MASK (0x1FFC0000UL)
#define PDMA_RGB2YUV_COEF0_C0_SHIFT (18U)
#define PDMA_RGB2YUV_COEF0_C0_SET(x) (((uint32_t)(x) << PDMA_RGB2YUV_COEF0_C0_SHIFT) & PDMA_RGB2YUV_COEF0_C0_MASK)
#define PDMA_RGB2YUV_COEF0_C0_GET(x) (((uint32_t)(x) & PDMA_RGB2YUV_COEF0_C0_MASK) >> PDMA_RGB2YUV_COEF0_C0_SHIFT)

/*
 * UV_OFFSET (RW)
 *
 * CSC parameters UV_OFFSET
 */
#define PDMA_RGB2YUV_COEF0_UV_OFFSET_MASK (0x3FE00UL)
#define PDMA_RGB2YUV_COEF0_UV_OFFSET_SHIFT (9U)
#define PDMA_RGB2YUV_COEF0_UV_OFFSET_SET(x) (((uint32_t)(x) << PDMA_RGB2YUV_COEF0_UV_OFFSET_SHIFT) & PDMA_RGB2YUV_COEF0_UV_OFFSET_MASK)
#define PDMA_RGB2YUV_COEF0_UV_OFFSET_GET(x) (((uint32_t)(x) & PDMA_RGB2YUV_COEF0_UV_OFFSET_MASK) >> PDMA_RGB2YUV_COEF0_UV_OFFSET_SHIFT)

/*
 * Y_OFFSET (RW)
 *
 * CSC parameters Y_OFFSET
 */
#define PDMA_RGB2YUV_COEF0_Y_OFFSET_MASK (0x1FFU)
#define PDMA_RGB2YUV_COEF0_Y_OFFSET_SHIFT (0U)
#define PDMA_RGB2YUV_COEF0_Y_OFFSET_SET(x) (((uint32_t)(x) << PDMA_RGB2YUV_COEF0_Y_OFFSET_SHIFT) & PDMA_RGB2YUV_COEF0_Y_OFFSET_MASK)
#define PDMA_RGB2YUV_COEF0_Y_OFFSET_GET(x) (((uint32_t)(x) & PDMA_RGB2YUV_COEF0_Y_OFFSET_MASK) >> PDMA_RGB2YUV_COEF0_Y_OFFSET_SHIFT)

/* Bitfield definition for register: RGB2YUV_COEF1 */
/*
 * C1 (RW)
 *
 * CSC parameters C1
 */
#define PDMA_RGB2YUV_COEF1_C1_MASK (0x7FF0000UL)
#define PDMA_RGB2YUV_COEF1_C1_SHIFT (16U)
#define PDMA_RGB2YUV_COEF1_C1_SET(x) (((uint32_t)(x) << PDMA_RGB2YUV_COEF1_C1_SHIFT) & PDMA_RGB2YUV_COEF1_C1_MASK)
#define PDMA_RGB2YUV_COEF1_C1_GET(x) (((uint32_t)(x) & PDMA_RGB2YUV_COEF1_C1_MASK) >> PDMA_RGB2YUV_COEF1_C1_SHIFT)

/*
 * C4 (RW)
 *
 * CSC parameters C4
 */
#define PDMA_RGB2YUV_COEF1_C4_MASK (0x7FFU)
#define PDMA_RGB2YUV_COEF1_C4_SHIFT (0U)
#define PDMA_RGB2YUV_COEF1_C4_SET(x) (((uint32_t)(x) << PDMA_RGB2YUV_COEF1_C4_SHIFT) & PDMA_RGB2YUV_COEF1_C4_MASK)
#define PDMA_RGB2YUV_COEF1_C4_GET(x) (((uint32_t)(x) & PDMA_RGB2YUV_COEF1_C4_MASK) >> PDMA_RGB2YUV_COEF1_C4_SHIFT)

/* Bitfield definition for register: RGB2YUV_COEF2 */
/*
 * C2 (RW)
 *
 * CSC parameters C2
 */
#define PDMA_RGB2YUV_COEF2_C2_MASK (0x7FF0000UL)
#define PDMA_RGB2YUV_COEF2_C2_SHIFT (16U)
#define PDMA_RGB2YUV_COEF2_C2_SET(x) (((uint32_t)(x) << PDMA_RGB2YUV_COEF2_C2_SHIFT) & PDMA_RGB2YUV_COEF2_C2_MASK)
#define PDMA_RGB2YUV_COEF2_C2_GET(x) (((uint32_t)(x) & PDMA_RGB2YUV_COEF2_C2_MASK) >> PDMA_RGB2YUV_COEF2_C2_SHIFT)

/*
 * C3 (RW)
 *
 * CSC parameters C3
 */
#define PDMA_RGB2YUV_COEF2_C3_MASK (0x7FFU)
#define PDMA_RGB2YUV_COEF2_C3_SHIFT (0U)
#define PDMA_RGB2YUV_COEF2_C3_SET(x) (((uint32_t)(x) << PDMA_RGB2YUV_COEF2_C3_SHIFT) & PDMA_RGB2YUV_COEF2_C3_MASK)
#define PDMA_RGB2YUV_COEF2_C3_GET(x) (((uint32_t)(x) & PDMA_RGB2YUV_COEF2_C3_MASK) >> PDMA_RGB2YUV_COEF2_C3_SHIFT)

/* Bitfield definition for register: RGB2YUV_COEF3 */
/*
 * C6 (RW)
 *
 * CSC parameters C6
 */
#define PDMA_RGB2YUV_COEF3_C6_MASK (0x7FF0000UL)
#define PDMA_RGB2YUV_COEF3_C6_SHIFT (16U)
#define PDMA_RGB2YUV_COEF3_C6_SET(x) (((uint32_t)(x) << PDMA_RGB2YUV_COEF3_C6_SHIFT) & PDMA_RGB2YUV_COEF3_C6_MASK)
#define PDMA_RGB2YUV_COEF3_C6_GET(x) (((uint32_t)(x) & PDMA_RGB2YUV_COEF3_C6_MASK) >> PDMA_RGB2YUV_COEF3_C6_SHIFT)

/*
 * C5 (RW)
 *
 * CSC parameters C5
 */
#define PDMA_RGB2YUV_COEF3_C5_MASK (0x7FFU)
#define PDMA_RGB2YUV_COEF3_C5_SHIFT (0U)
#define PDMA_RGB2YUV_COEF3_C5_SET(x) (((uint32_t)(x) << PDMA_RGB2YUV_COEF3_C5_SHIFT) & PDMA_RGB2YUV_COEF3_C5_MASK)
#define PDMA_RGB2YUV_COEF3_C5_GET(x) (((uint32_t)(x) & PDMA_RGB2YUV_COEF3_C5_MASK) >> PDMA_RGB2YUV_COEF3_C5_SHIFT)

/* Bitfield definition for register: RGB2YUV_COEF4 */
/*
 * C8 (RW)
 *
 * CSC parameters C8
 */
#define PDMA_RGB2YUV_COEF4_C8_MASK (0x7FF0000UL)
#define PDMA_RGB2YUV_COEF4_C8_SHIFT (16U)
#define PDMA_RGB2YUV_COEF4_C8_SET(x) (((uint32_t)(x) << PDMA_RGB2YUV_COEF4_C8_SHIFT) & PDMA_RGB2YUV_COEF4_C8_MASK)
#define PDMA_RGB2YUV_COEF4_C8_GET(x) (((uint32_t)(x) & PDMA_RGB2YUV_COEF4_C8_MASK) >> PDMA_RGB2YUV_COEF4_C8_SHIFT)

/*
 * C7 (RW)
 *
 * CSC parameters C7
 */
#define PDMA_RGB2YUV_COEF4_C7_MASK (0x7FFU)
#define PDMA_RGB2YUV_COEF4_C7_SHIFT (0U)
#define PDMA_RGB2YUV_COEF4_C7_SET(x) (((uint32_t)(x) << PDMA_RGB2YUV_COEF4_C7_SHIFT) & PDMA_RGB2YUV_COEF4_C7_MASK)
#define PDMA_RGB2YUV_COEF4_C7_GET(x) (((uint32_t)(x) & PDMA_RGB2YUV_COEF4_C7_MASK) >> PDMA_RGB2YUV_COEF4_C7_SHIFT)



/* OUT_PS register group index macro definition */
#define PDMA_OUT_PS_0 (0UL)
#define PDMA_OUT_PS_1 (1UL)

/* PS register group index macro definition */
#define PDMA_PS_0 (0UL)
#define PDMA_PS_1 (1UL)


#endif /* HPM_PDMA_H */
