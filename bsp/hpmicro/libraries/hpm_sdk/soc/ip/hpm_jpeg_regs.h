/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_JPEG_H
#define HPM_JPEG_H

typedef struct {
    __RW uint32_t INDMA_MISC;                  /* 0x0: In DMA Misc Control Register */
    __RW uint32_t INDMABASE;                   /* 0x4: In DMA Buf Address */
    __R  uint8_t  RESERVED0[4];                /* 0x8 - 0xB: Reserved */
    __RW uint32_t INDMA_CTRL0;                 /* 0xC: In DMA Buf Control 0 Register */
    __RW uint32_t INDMA_CTRL1;                 /* 0x10: In DMA Buf Control 1 Register */
    __RW uint32_t INXT_CMD;                    /* 0x14: In DMA Next Command Register */
    __R  uint8_t  RESERVED1[8];                /* 0x18 - 0x1F: Reserved */
    __RW uint32_t OUTDMA_MISC;                 /* 0x20: Out DMA Misc Control Register */
    __RW uint32_t OUTDMABASE;                  /* 0x24: Out DMA Buf Address */
    __R  uint8_t  RESERVED2[4];                /* 0x28 - 0x2B: Reserved */
    __RW uint32_t OUTDMA_CTRL0;                /* 0x2C: Out DMA Buf Control 0 Register */
    __RW uint32_t OUTDMA_CTRL1;                /* 0x30: Out DMA Buf Control 1 Register */
    __RW uint32_t ONXT_CMD;                    /* 0x34: Out DMA Next Command Register */
    __R  uint8_t  RESERVED3[8];                /* 0x38 - 0x3F: Reserved */
    __RW uint32_t CFG;                         /* 0x40: Configuration Register */
    __RW uint32_t STAT;                        /* 0x44: Status Register */
    __RW uint32_t WIDTH;                       /* 0x48: Image width register */
    __RW uint32_t HEIGHT;                      /* 0x4C: Image height register */
    __RW uint32_t BUFADDR;                     /* 0x50: Buf Access Addr */
    __RW uint32_t BUFDATA;                     /* 0x54: Buf Access Data */
    __R  uint32_t OUTDMACNT;                   /* 0x58: Out DMA Bytes Counter */
    __RW uint32_t CSC_COEF0;                   /* 0x5C: YUV2RGB coefficients Register 0 */
    __RW uint32_t CSC_COEF1;                   /* 0x60: YUV2RGB coefficients Register 1 */
    __RW uint32_t CSC_COEF2;                   /* 0x64: YUV2RGB coefficients Register 2 */
    __RW uint32_t RGB2YUV_COEF0;               /* 0x68: RGB2YUV coefficients Register 0 */
    __RW uint32_t RGB2YUV_COEF1;               /* 0x6C: RGB2YUV coefficients Register 1 */
    __RW uint32_t RGB2YUV_COEF2;               /* 0x70: RGB2YUV coefficients Register 2 */
    __RW uint32_t RGB2YUV_COEF3;               /* 0x74: RGB2YUV coefficients Register 3 */
    __RW uint32_t RGB2YUV_COEF4;               /* 0x78: RGB2YUV coefficients Register 4 */
    __R  uint8_t  RESERVED4[8];                /* 0x7C - 0x83: Reserved */
    __RW uint32_t IMGREG1;                     /* 0x84: Image Control Register 1 */
    __RW uint32_t IMGREG2;                     /* 0x88: Image Control Register 2 */
    __RW uint32_t IMGREG3;                     /* 0x8C: Image Control Register 3 */
    __RW uint32_t IMGREG[4];                   /* 0x90 - 0x9C: Image Control Register 40 */
} JPEG_Type;


/* Bitfield definition for register: INDMA_MISC */
/*
 * ARQOS (RW)
 *
 * QoS for AXI read channel
 */
#define JPEG_INDMA_MISC_ARQOS_MASK (0x780000UL)
#define JPEG_INDMA_MISC_ARQOS_SHIFT (19U)
#define JPEG_INDMA_MISC_ARQOS_SET(x) (((uint32_t)(x) << JPEG_INDMA_MISC_ARQOS_SHIFT) & JPEG_INDMA_MISC_ARQOS_MASK)
#define JPEG_INDMA_MISC_ARQOS_GET(x) (((uint32_t)(x) & JPEG_INDMA_MISC_ARQOS_MASK) >> JPEG_INDMA_MISC_ARQOS_SHIFT)

/*
 * MAX_OT (RW)
 *
 * max_ot when input are RGB pixels.
 * For 16 bits per pixel, it can be set as 4.
 * For 32 bits per pixel, it will be set as 2.
 */
#define JPEG_INDMA_MISC_MAX_OT_MASK (0x78000UL)
#define JPEG_INDMA_MISC_MAX_OT_SHIFT (15U)
#define JPEG_INDMA_MISC_MAX_OT_SET(x) (((uint32_t)(x) << JPEG_INDMA_MISC_MAX_OT_SHIFT) & JPEG_INDMA_MISC_MAX_OT_MASK)
#define JPEG_INDMA_MISC_MAX_OT_GET(x) (((uint32_t)(x) & JPEG_INDMA_MISC_MAX_OT_MASK) >> JPEG_INDMA_MISC_MAX_OT_SHIFT)

/*
 * INB13_SWAP (RW)
 *
 * Swap bit[31:24] and bit [15:8] before pack dir operation. Only work for pixel data.
 */
#define JPEG_INDMA_MISC_INB13_SWAP_MASK (0x4000U)
#define JPEG_INDMA_MISC_INB13_SWAP_SHIFT (14U)
#define JPEG_INDMA_MISC_INB13_SWAP_SET(x) (((uint32_t)(x) << JPEG_INDMA_MISC_INB13_SWAP_SHIFT) & JPEG_INDMA_MISC_INB13_SWAP_MASK)
#define JPEG_INDMA_MISC_INB13_SWAP_GET(x) (((uint32_t)(x) & JPEG_INDMA_MISC_INB13_SWAP_MASK) >> JPEG_INDMA_MISC_INB13_SWAP_SHIFT)

/*
 * PACK_DIR (RW)
 *
 * Decide the byte sequence of the 32-bit word {A3, A2, A1, A0}. The bit sequence in a byte is not changed. Only work for pixel data.
 * 2'b00: no change {A3, A2, A1, A0}
 * 2'b01: {A2, A3, A0, A1}
 * 2'b10: {A1, A0, A3, A2}
 * 2'b11: {A0, A1, A2, A3}
 */
#define JPEG_INDMA_MISC_PACK_DIR_MASK (0x3000U)
#define JPEG_INDMA_MISC_PACK_DIR_SHIFT (12U)
#define JPEG_INDMA_MISC_PACK_DIR_SET(x) (((uint32_t)(x) << JPEG_INDMA_MISC_PACK_DIR_SHIFT) & JPEG_INDMA_MISC_PACK_DIR_MASK)
#define JPEG_INDMA_MISC_PACK_DIR_GET(x) (((uint32_t)(x) & JPEG_INDMA_MISC_PACK_DIR_MASK) >> JPEG_INDMA_MISC_PACK_DIR_SHIFT)

/*
 * INDMA_RENEW (RW)
 *
 * Renew In DMA. Default is to continue the write address counter when a new DMA request comes. Asserted to reset the write address counter.
 */
#define JPEG_INDMA_MISC_INDMA_RENEW_MASK (0x800U)
#define JPEG_INDMA_MISC_INDMA_RENEW_SHIFT (11U)
#define JPEG_INDMA_MISC_INDMA_RENEW_SET(x) (((uint32_t)(x) << JPEG_INDMA_MISC_INDMA_RENEW_SHIFT) & JPEG_INDMA_MISC_INDMA_RENEW_MASK)
#define JPEG_INDMA_MISC_INDMA_RENEW_GET(x) (((uint32_t)(x) & JPEG_INDMA_MISC_INDMA_RENEW_MASK) >> JPEG_INDMA_MISC_INDMA_RENEW_SHIFT)

/*
 * NXT_IRQ_EN (RW)
 *
 * In DMA Next Interrupt Enable
 */
#define JPEG_INDMA_MISC_NXT_IRQ_EN_MASK (0x400U)
#define JPEG_INDMA_MISC_NXT_IRQ_EN_SHIFT (10U)
#define JPEG_INDMA_MISC_NXT_IRQ_EN_SET(x) (((uint32_t)(x) << JPEG_INDMA_MISC_NXT_IRQ_EN_SHIFT) & JPEG_INDMA_MISC_NXT_IRQ_EN_MASK)
#define JPEG_INDMA_MISC_NXT_IRQ_EN_GET(x) (((uint32_t)(x) & JPEG_INDMA_MISC_NXT_IRQ_EN_MASK) >> JPEG_INDMA_MISC_NXT_IRQ_EN_SHIFT)

/*
 * IN_DMA_DONE_IRQ_EN (RW)
 *
 * In DMA Done enable
 */
#define JPEG_INDMA_MISC_IN_DMA_DONE_IRQ_EN_MASK (0x200U)
#define JPEG_INDMA_MISC_IN_DMA_DONE_IRQ_EN_SHIFT (9U)
#define JPEG_INDMA_MISC_IN_DMA_DONE_IRQ_EN_SET(x) (((uint32_t)(x) << JPEG_INDMA_MISC_IN_DMA_DONE_IRQ_EN_SHIFT) & JPEG_INDMA_MISC_IN_DMA_DONE_IRQ_EN_MASK)
#define JPEG_INDMA_MISC_IN_DMA_DONE_IRQ_EN_GET(x) (((uint32_t)(x) & JPEG_INDMA_MISC_IN_DMA_DONE_IRQ_EN_MASK) >> JPEG_INDMA_MISC_IN_DMA_DONE_IRQ_EN_SHIFT)

/*
 * AXI_ERR_IRQ_EN (RW)
 *
 * In DMA axi bus error inetrrupt enable
 */
#define JPEG_INDMA_MISC_AXI_ERR_IRQ_EN_MASK (0x100U)
#define JPEG_INDMA_MISC_AXI_ERR_IRQ_EN_SHIFT (8U)
#define JPEG_INDMA_MISC_AXI_ERR_IRQ_EN_SET(x) (((uint32_t)(x) << JPEG_INDMA_MISC_AXI_ERR_IRQ_EN_SHIFT) & JPEG_INDMA_MISC_AXI_ERR_IRQ_EN_MASK)
#define JPEG_INDMA_MISC_AXI_ERR_IRQ_EN_GET(x) (((uint32_t)(x) & JPEG_INDMA_MISC_AXI_ERR_IRQ_EN_MASK) >> JPEG_INDMA_MISC_AXI_ERR_IRQ_EN_SHIFT)

/*
 * IRQ_EN (RW)
 *
 * interrupt enable for all interrupt sources of In DMA module
 */
#define JPEG_INDMA_MISC_IRQ_EN_MASK (0x80U)
#define JPEG_INDMA_MISC_IRQ_EN_SHIFT (7U)
#define JPEG_INDMA_MISC_IRQ_EN_SET(x) (((uint32_t)(x) << JPEG_INDMA_MISC_IRQ_EN_SHIFT) & JPEG_INDMA_MISC_IRQ_EN_MASK)
#define JPEG_INDMA_MISC_IRQ_EN_GET(x) (((uint32_t)(x) & JPEG_INDMA_MISC_IRQ_EN_MASK) >> JPEG_INDMA_MISC_IRQ_EN_SHIFT)

/*
 * IN_DMA_ID (RW)
 *
 * 0: Pixel (In)
 * 1: ECS (In)
 * 2: Qmem
 * 3: HuffEnc
 * 4: HuffMin
 * 5: HuffBase
 * 6: HuffSymb
 */
#define JPEG_INDMA_MISC_IN_DMA_ID_MASK (0x70U)
#define JPEG_INDMA_MISC_IN_DMA_ID_SHIFT (4U)
#define JPEG_INDMA_MISC_IN_DMA_ID_SET(x) (((uint32_t)(x) << JPEG_INDMA_MISC_IN_DMA_ID_SHIFT) & JPEG_INDMA_MISC_IN_DMA_ID_MASK)
#define JPEG_INDMA_MISC_IN_DMA_ID_GET(x) (((uint32_t)(x) & JPEG_INDMA_MISC_IN_DMA_ID_MASK) >> JPEG_INDMA_MISC_IN_DMA_ID_SHIFT)

/*
 * IN_DMA_REQ (RW)
 *
 * Asserted to request DMA. Automatically clear after DMA is done.
 */
#define JPEG_INDMA_MISC_IN_DMA_REQ_MASK (0x8U)
#define JPEG_INDMA_MISC_IN_DMA_REQ_SHIFT (3U)
#define JPEG_INDMA_MISC_IN_DMA_REQ_SET(x) (((uint32_t)(x) << JPEG_INDMA_MISC_IN_DMA_REQ_SHIFT) & JPEG_INDMA_MISC_IN_DMA_REQ_MASK)
#define JPEG_INDMA_MISC_IN_DMA_REQ_GET(x) (((uint32_t)(x) & JPEG_INDMA_MISC_IN_DMA_REQ_MASK) >> JPEG_INDMA_MISC_IN_DMA_REQ_SHIFT)

/*
 * INDMA2D (RW)
 *
 * Asserted if In_DMA_ID=Pixel.
 */
#define JPEG_INDMA_MISC_INDMA2D_MASK (0x4U)
#define JPEG_INDMA_MISC_INDMA2D_SHIFT (2U)
#define JPEG_INDMA_MISC_INDMA2D_SET(x) (((uint32_t)(x) << JPEG_INDMA_MISC_INDMA2D_SHIFT) & JPEG_INDMA_MISC_INDMA2D_MASK)
#define JPEG_INDMA_MISC_INDMA2D_GET(x) (((uint32_t)(x) & JPEG_INDMA_MISC_INDMA2D_MASK) >> JPEG_INDMA_MISC_INDMA2D_SHIFT)

/* Bitfield definition for register: INDMABASE */
/*
 * ADDR (RW)
 *
 * Y plane (or Encoded Bit Plane)
 */
#define JPEG_INDMABASE_ADDR_MASK (0xFFFFFFFFUL)
#define JPEG_INDMABASE_ADDR_SHIFT (0U)
#define JPEG_INDMABASE_ADDR_SET(x) (((uint32_t)(x) << JPEG_INDMABASE_ADDR_SHIFT) & JPEG_INDMABASE_ADDR_MASK)
#define JPEG_INDMABASE_ADDR_GET(x) (((uint32_t)(x) & JPEG_INDMABASE_ADDR_MASK) >> JPEG_INDMABASE_ADDR_SHIFT)

/* Bitfield definition for register: INDMA_CTRL0 */
/*
 * TTLEN (RW)
 *
 * Total length (Low 16 bits) in Bytes -1 for transfer when  In_DMA_ID!=Pixel.
 */
#define JPEG_INDMA_CTRL0_TTLEN_MASK (0xFFFF0000UL)
#define JPEG_INDMA_CTRL0_TTLEN_SHIFT (16U)
#define JPEG_INDMA_CTRL0_TTLEN_SET(x) (((uint32_t)(x) << JPEG_INDMA_CTRL0_TTLEN_SHIFT) & JPEG_INDMA_CTRL0_TTLEN_MASK)
#define JPEG_INDMA_CTRL0_TTLEN_GET(x) (((uint32_t)(x) & JPEG_INDMA_CTRL0_TTLEN_MASK) >> JPEG_INDMA_CTRL0_TTLEN_SHIFT)

/*
 * PITCH (RW)
 *
 * Pitch between the starting point of Rows. Only active when  In_DMA_ID=Pixel..
 */
#define JPEG_INDMA_CTRL0_PITCH_MASK (0xFFFFU)
#define JPEG_INDMA_CTRL0_PITCH_SHIFT (0U)
#define JPEG_INDMA_CTRL0_PITCH_SET(x) (((uint32_t)(x) << JPEG_INDMA_CTRL0_PITCH_SHIFT) & JPEG_INDMA_CTRL0_PITCH_MASK)
#define JPEG_INDMA_CTRL0_PITCH_GET(x) (((uint32_t)(x) & JPEG_INDMA_CTRL0_PITCH_MASK) >> JPEG_INDMA_CTRL0_PITCH_SHIFT)

/* Bitfield definition for register: INDMA_CTRL1 */
/*
 * ROWLEN (RW)
 *
 * Total length (High 16 bits) in Bytes -1 for transfer. See reference in InDMA_Ctrl0[TTLEN]
 */
#define JPEG_INDMA_CTRL1_ROWLEN_MASK (0xFFFFU)
#define JPEG_INDMA_CTRL1_ROWLEN_SHIFT (0U)
#define JPEG_INDMA_CTRL1_ROWLEN_SET(x) (((uint32_t)(x) << JPEG_INDMA_CTRL1_ROWLEN_SHIFT) & JPEG_INDMA_CTRL1_ROWLEN_MASK)
#define JPEG_INDMA_CTRL1_ROWLEN_GET(x) (((uint32_t)(x) & JPEG_INDMA_CTRL1_ROWLEN_MASK) >> JPEG_INDMA_CTRL1_ROWLEN_SHIFT)

/* Bitfield definition for register: INXT_CMD */
/*
 * ADDR (RW)
 *
 * The address pointing to the next command
 */
#define JPEG_INXT_CMD_ADDR_MASK (0xFFFFFFFCUL)
#define JPEG_INXT_CMD_ADDR_SHIFT (2U)
#define JPEG_INXT_CMD_ADDR_SET(x) (((uint32_t)(x) << JPEG_INXT_CMD_ADDR_SHIFT) & JPEG_INXT_CMD_ADDR_MASK)
#define JPEG_INXT_CMD_ADDR_GET(x) (((uint32_t)(x) & JPEG_INXT_CMD_ADDR_MASK) >> JPEG_INXT_CMD_ADDR_SHIFT)

/*
 * OP_VALID (RW)
 *
 * asserted if there is either a DATA DMA phase or NXTCMD phase. Automatically cleared. Will trigger the InDMA transfer if CFG[JPEG_EN] is 1.
 */
#define JPEG_INXT_CMD_OP_VALID_MASK (0x2U)
#define JPEG_INXT_CMD_OP_VALID_SHIFT (1U)
#define JPEG_INXT_CMD_OP_VALID_SET(x) (((uint32_t)(x) << JPEG_INXT_CMD_OP_VALID_SHIFT) & JPEG_INXT_CMD_OP_VALID_MASK)
#define JPEG_INXT_CMD_OP_VALID_GET(x) (((uint32_t)(x) & JPEG_INXT_CMD_OP_VALID_MASK) >> JPEG_INXT_CMD_OP_VALID_SHIFT)

/*
 * EN (RW)
 *
 * NXTCMD phase Enable Bit
 */
#define JPEG_INXT_CMD_EN_MASK (0x1U)
#define JPEG_INXT_CMD_EN_SHIFT (0U)
#define JPEG_INXT_CMD_EN_SET(x) (((uint32_t)(x) << JPEG_INXT_CMD_EN_SHIFT) & JPEG_INXT_CMD_EN_MASK)
#define JPEG_INXT_CMD_EN_GET(x) (((uint32_t)(x) & JPEG_INXT_CMD_EN_MASK) >> JPEG_INXT_CMD_EN_SHIFT)

/* Bitfield definition for register: OUTDMA_MISC */
/*
 * AWQOS (RW)
 *
 */
#define JPEG_OUTDMA_MISC_AWQOS_MASK (0x3C000UL)
#define JPEG_OUTDMA_MISC_AWQOS_SHIFT (14U)
#define JPEG_OUTDMA_MISC_AWQOS_SET(x) (((uint32_t)(x) << JPEG_OUTDMA_MISC_AWQOS_SHIFT) & JPEG_OUTDMA_MISC_AWQOS_MASK)
#define JPEG_OUTDMA_MISC_AWQOS_GET(x) (((uint32_t)(x) & JPEG_OUTDMA_MISC_AWQOS_MASK) >> JPEG_OUTDMA_MISC_AWQOS_SHIFT)

/*
 * PACK_DIR (RW)
 *
 * Decide the byte sequence of the 32-bit word {A3, A2, A1, A0}. The bit sequence in a byte is not changed. All outdma data are impacted.
 * 2'b00: no change {A3, A2, A1, A0} (This is used for ecs stream)
 * 2'b01: {A2, A3, A0, A1}
 * 2'b10: {A1, A0, A3, A2}
 * 2'b11: {A0, A1, A2, A3}
 */
#define JPEG_OUTDMA_MISC_PACK_DIR_MASK (0x3000U)
#define JPEG_OUTDMA_MISC_PACK_DIR_SHIFT (12U)
#define JPEG_OUTDMA_MISC_PACK_DIR_SET(x) (((uint32_t)(x) << JPEG_OUTDMA_MISC_PACK_DIR_SHIFT) & JPEG_OUTDMA_MISC_PACK_DIR_MASK)
#define JPEG_OUTDMA_MISC_PACK_DIR_GET(x) (((uint32_t)(x) & JPEG_OUTDMA_MISC_PACK_DIR_MASK) >> JPEG_OUTDMA_MISC_PACK_DIR_SHIFT)

/*
 * EN_OUTCNT (RW)
 *
 * Enable output counter (unit as bytes)
 */
#define JPEG_OUTDMA_MISC_EN_OUTCNT_MASK (0x800U)
#define JPEG_OUTDMA_MISC_EN_OUTCNT_SHIFT (11U)
#define JPEG_OUTDMA_MISC_EN_OUTCNT_SET(x) (((uint32_t)(x) << JPEG_OUTDMA_MISC_EN_OUTCNT_SHIFT) & JPEG_OUTDMA_MISC_EN_OUTCNT_MASK)
#define JPEG_OUTDMA_MISC_EN_OUTCNT_GET(x) (((uint32_t)(x) & JPEG_OUTDMA_MISC_EN_OUTCNT_MASK) >> JPEG_OUTDMA_MISC_EN_OUTCNT_SHIFT)

/*
 * INI_OUTCNT (RW)
 *
 * Asserted to ini output counter
 */
#define JPEG_OUTDMA_MISC_INI_OUTCNT_MASK (0x400U)
#define JPEG_OUTDMA_MISC_INI_OUTCNT_SHIFT (10U)
#define JPEG_OUTDMA_MISC_INI_OUTCNT_SET(x) (((uint32_t)(x) << JPEG_OUTDMA_MISC_INI_OUTCNT_SHIFT) & JPEG_OUTDMA_MISC_INI_OUTCNT_MASK)
#define JPEG_OUTDMA_MISC_INI_OUTCNT_GET(x) (((uint32_t)(x) & JPEG_OUTDMA_MISC_INI_OUTCNT_MASK) >> JPEG_OUTDMA_MISC_INI_OUTCNT_SHIFT)

/*
 * ADD_ODMA_ENDINGS (RW)
 *
 * Add 0xFFD9 to the ending of the odma stream when all original image pixels are processed by the encoder module.
 */
#define JPEG_OUTDMA_MISC_ADD_ODMA_ENDINGS_MASK (0x200U)
#define JPEG_OUTDMA_MISC_ADD_ODMA_ENDINGS_SHIFT (9U)
#define JPEG_OUTDMA_MISC_ADD_ODMA_ENDINGS_SET(x) (((uint32_t)(x) << JPEG_OUTDMA_MISC_ADD_ODMA_ENDINGS_SHIFT) & JPEG_OUTDMA_MISC_ADD_ODMA_ENDINGS_MASK)
#define JPEG_OUTDMA_MISC_ADD_ODMA_ENDINGS_GET(x) (((uint32_t)(x) & JPEG_OUTDMA_MISC_ADD_ODMA_ENDINGS_MASK) >> JPEG_OUTDMA_MISC_ADD_ODMA_ENDINGS_SHIFT)

/*
 * NXT_IRQ_EN (RW)
 *
 * Out DMA Next Interrupt Enable
 */
#define JPEG_OUTDMA_MISC_NXT_IRQ_EN_MASK (0x100U)
#define JPEG_OUTDMA_MISC_NXT_IRQ_EN_SHIFT (8U)
#define JPEG_OUTDMA_MISC_NXT_IRQ_EN_SET(x) (((uint32_t)(x) << JPEG_OUTDMA_MISC_NXT_IRQ_EN_SHIFT) & JPEG_OUTDMA_MISC_NXT_IRQ_EN_MASK)
#define JPEG_OUTDMA_MISC_NXT_IRQ_EN_GET(x) (((uint32_t)(x) & JPEG_OUTDMA_MISC_NXT_IRQ_EN_MASK) >> JPEG_OUTDMA_MISC_NXT_IRQ_EN_SHIFT)

/*
 * OUT_DMA_DONE_IRQ_EN (RW)
 *
 * Out DMA Done interrupt Enable
 */
#define JPEG_OUTDMA_MISC_OUT_DMA_DONE_IRQ_EN_MASK (0x80U)
#define JPEG_OUTDMA_MISC_OUT_DMA_DONE_IRQ_EN_SHIFT (7U)
#define JPEG_OUTDMA_MISC_OUT_DMA_DONE_IRQ_EN_SET(x) (((uint32_t)(x) << JPEG_OUTDMA_MISC_OUT_DMA_DONE_IRQ_EN_SHIFT) & JPEG_OUTDMA_MISC_OUT_DMA_DONE_IRQ_EN_MASK)
#define JPEG_OUTDMA_MISC_OUT_DMA_DONE_IRQ_EN_GET(x) (((uint32_t)(x) & JPEG_OUTDMA_MISC_OUT_DMA_DONE_IRQ_EN_MASK) >> JPEG_OUTDMA_MISC_OUT_DMA_DONE_IRQ_EN_SHIFT)

/*
 * AXI_ERR_IRQ_EN (RW)
 *
 * Out DMA axi bus error inetrrupt enable
 */
#define JPEG_OUTDMA_MISC_AXI_ERR_IRQ_EN_MASK (0x40U)
#define JPEG_OUTDMA_MISC_AXI_ERR_IRQ_EN_SHIFT (6U)
#define JPEG_OUTDMA_MISC_AXI_ERR_IRQ_EN_SET(x) (((uint32_t)(x) << JPEG_OUTDMA_MISC_AXI_ERR_IRQ_EN_SHIFT) & JPEG_OUTDMA_MISC_AXI_ERR_IRQ_EN_MASK)
#define JPEG_OUTDMA_MISC_AXI_ERR_IRQ_EN_GET(x) (((uint32_t)(x) & JPEG_OUTDMA_MISC_AXI_ERR_IRQ_EN_MASK) >> JPEG_OUTDMA_MISC_AXI_ERR_IRQ_EN_SHIFT)

/*
 * IRQ_EN (RW)
 *
 * interrupt enable for all interrupt sources of Out DMA module
 */
#define JPEG_OUTDMA_MISC_IRQ_EN_MASK (0x20U)
#define JPEG_OUTDMA_MISC_IRQ_EN_SHIFT (5U)
#define JPEG_OUTDMA_MISC_IRQ_EN_SET(x) (((uint32_t)(x) << JPEG_OUTDMA_MISC_IRQ_EN_SHIFT) & JPEG_OUTDMA_MISC_IRQ_EN_MASK)
#define JPEG_OUTDMA_MISC_IRQ_EN_GET(x) (((uint32_t)(x) & JPEG_OUTDMA_MISC_IRQ_EN_MASK) >> JPEG_OUTDMA_MISC_IRQ_EN_SHIFT)

/*
 * OUT_DMA_ID (RW)
 *
 * 0: Pixel (Out)
 * 1: ECS (Out)
 */
#define JPEG_OUTDMA_MISC_OUT_DMA_ID_MASK (0x10U)
#define JPEG_OUTDMA_MISC_OUT_DMA_ID_SHIFT (4U)
#define JPEG_OUTDMA_MISC_OUT_DMA_ID_SET(x) (((uint32_t)(x) << JPEG_OUTDMA_MISC_OUT_DMA_ID_SHIFT) & JPEG_OUTDMA_MISC_OUT_DMA_ID_MASK)
#define JPEG_OUTDMA_MISC_OUT_DMA_ID_GET(x) (((uint32_t)(x) & JPEG_OUTDMA_MISC_OUT_DMA_ID_MASK) >> JPEG_OUTDMA_MISC_OUT_DMA_ID_SHIFT)

/*
 * OUT_DMA_REQ (RW)
 *
 * Asserted to enable Out DMA request
 */
#define JPEG_OUTDMA_MISC_OUT_DMA_REQ_MASK (0x8U)
#define JPEG_OUTDMA_MISC_OUT_DMA_REQ_SHIFT (3U)
#define JPEG_OUTDMA_MISC_OUT_DMA_REQ_SET(x) (((uint32_t)(x) << JPEG_OUTDMA_MISC_OUT_DMA_REQ_SHIFT) & JPEG_OUTDMA_MISC_OUT_DMA_REQ_MASK)
#define JPEG_OUTDMA_MISC_OUT_DMA_REQ_GET(x) (((uint32_t)(x) & JPEG_OUTDMA_MISC_OUT_DMA_REQ_MASK) >> JPEG_OUTDMA_MISC_OUT_DMA_REQ_SHIFT)

/*
 * OUTDMA2D (RW)
 *
 * Asserted if Out_DMA_ID==Pixel
 */
#define JPEG_OUTDMA_MISC_OUTDMA2D_MASK (0x4U)
#define JPEG_OUTDMA_MISC_OUTDMA2D_SHIFT (2U)
#define JPEG_OUTDMA_MISC_OUTDMA2D_SET(x) (((uint32_t)(x) << JPEG_OUTDMA_MISC_OUTDMA2D_SHIFT) & JPEG_OUTDMA_MISC_OUTDMA2D_MASK)
#define JPEG_OUTDMA_MISC_OUTDMA2D_GET(x) (((uint32_t)(x) & JPEG_OUTDMA_MISC_OUTDMA2D_MASK) >> JPEG_OUTDMA_MISC_OUTDMA2D_SHIFT)

/* Bitfield definition for register: OUTDMABASE */
/*
 * ADDR (RW)
 *
 * Y plane (or Encoded Bit Plane)
 */
#define JPEG_OUTDMABASE_ADDR_MASK (0xFFFFFFFFUL)
#define JPEG_OUTDMABASE_ADDR_SHIFT (0U)
#define JPEG_OUTDMABASE_ADDR_SET(x) (((uint32_t)(x) << JPEG_OUTDMABASE_ADDR_SHIFT) & JPEG_OUTDMABASE_ADDR_MASK)
#define JPEG_OUTDMABASE_ADDR_GET(x) (((uint32_t)(x) & JPEG_OUTDMABASE_ADDR_MASK) >> JPEG_OUTDMABASE_ADDR_SHIFT)

/* Bitfield definition for register: OUTDMA_CTRL0 */
/*
 * TTLEN (RW)
 *
 * Total length (Low 16 bits) in Bytes -1 for transfer when  Out_DMA_ID!=Pixel.  If Out_DMA_ID=ECS, it can be any value greater than the length of the ECS, for example, the number of encoded bytes.
 */
#define JPEG_OUTDMA_CTRL0_TTLEN_MASK (0xFFFF0000UL)
#define JPEG_OUTDMA_CTRL0_TTLEN_SHIFT (16U)
#define JPEG_OUTDMA_CTRL0_TTLEN_SET(x) (((uint32_t)(x) << JPEG_OUTDMA_CTRL0_TTLEN_SHIFT) & JPEG_OUTDMA_CTRL0_TTLEN_MASK)
#define JPEG_OUTDMA_CTRL0_TTLEN_GET(x) (((uint32_t)(x) & JPEG_OUTDMA_CTRL0_TTLEN_MASK) >> JPEG_OUTDMA_CTRL0_TTLEN_SHIFT)

/*
 * PITCH (RW)
 *
 * Pitch between the starting point of Rows when Out_DMA_ID==Pixel
 */
#define JPEG_OUTDMA_CTRL0_PITCH_MASK (0xFFFFU)
#define JPEG_OUTDMA_CTRL0_PITCH_SHIFT (0U)
#define JPEG_OUTDMA_CTRL0_PITCH_SET(x) (((uint32_t)(x) << JPEG_OUTDMA_CTRL0_PITCH_SHIFT) & JPEG_OUTDMA_CTRL0_PITCH_MASK)
#define JPEG_OUTDMA_CTRL0_PITCH_GET(x) (((uint32_t)(x) & JPEG_OUTDMA_CTRL0_PITCH_MASK) >> JPEG_OUTDMA_CTRL0_PITCH_SHIFT)

/* Bitfield definition for register: OUTDMA_CTRL1 */
/*
 * ROWLEN (RW)
 *
 * Total length (High 16 bits) in Bytes -1 for transfer. See reference in OutDMA_Ctrl0[TTLEN]
 */
#define JPEG_OUTDMA_CTRL1_ROWLEN_MASK (0xFFFFU)
#define JPEG_OUTDMA_CTRL1_ROWLEN_SHIFT (0U)
#define JPEG_OUTDMA_CTRL1_ROWLEN_SET(x) (((uint32_t)(x) << JPEG_OUTDMA_CTRL1_ROWLEN_SHIFT) & JPEG_OUTDMA_CTRL1_ROWLEN_MASK)
#define JPEG_OUTDMA_CTRL1_ROWLEN_GET(x) (((uint32_t)(x) & JPEG_OUTDMA_CTRL1_ROWLEN_MASK) >> JPEG_OUTDMA_CTRL1_ROWLEN_SHIFT)

/* Bitfield definition for register: ONXT_CMD */
/*
 * ADDR (RW)
 *
 * The address pointing to the next command
 */
#define JPEG_ONXT_CMD_ADDR_MASK (0xFFFFFFFCUL)
#define JPEG_ONXT_CMD_ADDR_SHIFT (2U)
#define JPEG_ONXT_CMD_ADDR_SET(x) (((uint32_t)(x) << JPEG_ONXT_CMD_ADDR_SHIFT) & JPEG_ONXT_CMD_ADDR_MASK)
#define JPEG_ONXT_CMD_ADDR_GET(x) (((uint32_t)(x) & JPEG_ONXT_CMD_ADDR_MASK) >> JPEG_ONXT_CMD_ADDR_SHIFT)

/*
 * OP_VALID (RW)
 *
 * asserted if there is either a DATA DMA phase or NXTCMD phase. Automatically cleared. Will trigger the OutDMA and NXTCMD phase transfer if CFG[JPEG_EN] is 1.
 */
#define JPEG_ONXT_CMD_OP_VALID_MASK (0x2U)
#define JPEG_ONXT_CMD_OP_VALID_SHIFT (1U)
#define JPEG_ONXT_CMD_OP_VALID_SET(x) (((uint32_t)(x) << JPEG_ONXT_CMD_OP_VALID_SHIFT) & JPEG_ONXT_CMD_OP_VALID_MASK)
#define JPEG_ONXT_CMD_OP_VALID_GET(x) (((uint32_t)(x) & JPEG_ONXT_CMD_OP_VALID_MASK) >> JPEG_ONXT_CMD_OP_VALID_SHIFT)

/*
 * EN (RW)
 *
 * NXTCMD phase Enable Bit
 */
#define JPEG_ONXT_CMD_EN_MASK (0x1U)
#define JPEG_ONXT_CMD_EN_SHIFT (0U)
#define JPEG_ONXT_CMD_EN_SET(x) (((uint32_t)(x) << JPEG_ONXT_CMD_EN_SHIFT) & JPEG_ONXT_CMD_EN_MASK)
#define JPEG_ONXT_CMD_EN_GET(x) (((uint32_t)(x) & JPEG_ONXT_CMD_EN_MASK) >> JPEG_ONXT_CMD_EN_SHIFT)

/* Bitfield definition for register: CFG */
/*
 * JD_UVSWAP (RW)
 *
 * Normally the default CbCr sequence is that Cb macro block coming before Cr macro blk. If Cr macro block is first, set this bit to 1'b1. This bit only impact the color space conversion from/to RGB.
 */
#define JPEG_CFG_JD_UVSWAP_MASK (0x400000UL)
#define JPEG_CFG_JD_UVSWAP_SHIFT (22U)
#define JPEG_CFG_JD_UVSWAP_SET(x) (((uint32_t)(x) << JPEG_CFG_JD_UVSWAP_SHIFT) & JPEG_CFG_JD_UVSWAP_MASK)
#define JPEG_CFG_JD_UVSWAP_GET(x) (((uint32_t)(x) & JPEG_CFG_JD_UVSWAP_MASK) >> JPEG_CFG_JD_UVSWAP_SHIFT)

/*
 * CFG_IPATH_SEL (RW)
 *
 * 2'b0:2-plane (Y- and UV- plane) or 1-plane (Y-only) as determined by the original data, byte sequence as Y0,Y1, or U,V
 * 2'b01:ARGB8888, byte sequence as B,G,R,A
 * 2'b10:RGB565, byte sequence as B,R
 * 2'b11: YUV422H, byte sequence as Y0,U0,Y1,V0
 */
#define JPEG_CFG_CFG_IPATH_SEL_MASK (0x300000UL)
#define JPEG_CFG_CFG_IPATH_SEL_SHIFT (20U)
#define JPEG_CFG_CFG_IPATH_SEL_SET(x) (((uint32_t)(x) << JPEG_CFG_CFG_IPATH_SEL_SHIFT) & JPEG_CFG_CFG_IPATH_SEL_MASK)
#define JPEG_CFG_CFG_IPATH_SEL_GET(x) (((uint32_t)(x) & JPEG_CFG_CFG_IPATH_SEL_MASK) >> JPEG_CFG_CFG_IPATH_SEL_SHIFT)

/*
 * CODEC_OVER_IRQ_EN (RW)
 *
 * The jpg endec process done interrupt enable
 */
#define JPEG_CFG_CODEC_OVER_IRQ_EN_MASK (0x80000UL)
#define JPEG_CFG_CODEC_OVER_IRQ_EN_SHIFT (19U)
#define JPEG_CFG_CODEC_OVER_IRQ_EN_SET(x) (((uint32_t)(x) << JPEG_CFG_CODEC_OVER_IRQ_EN_SHIFT) & JPEG_CFG_CODEC_OVER_IRQ_EN_MASK)
#define JPEG_CFG_CODEC_OVER_IRQ_EN_GET(x) (((uint32_t)(x) & JPEG_CFG_CODEC_OVER_IRQ_EN_MASK) >> JPEG_CFG_CODEC_OVER_IRQ_EN_SHIFT)

/*
 * CODEC_RESTART_ERR_IRQ_EN (RW)
 *
 * The jpg endec restart error interrupt enable
 */
#define JPEG_CFG_CODEC_RESTART_ERR_IRQ_EN_MASK (0x40000UL)
#define JPEG_CFG_CODEC_RESTART_ERR_IRQ_EN_SHIFT (18U)
#define JPEG_CFG_CODEC_RESTART_ERR_IRQ_EN_SET(x) (((uint32_t)(x) << JPEG_CFG_CODEC_RESTART_ERR_IRQ_EN_SHIFT) & JPEG_CFG_CODEC_RESTART_ERR_IRQ_EN_MASK)
#define JPEG_CFG_CODEC_RESTART_ERR_IRQ_EN_GET(x) (((uint32_t)(x) & JPEG_CFG_CODEC_RESTART_ERR_IRQ_EN_MASK) >> JPEG_CFG_CODEC_RESTART_ERR_IRQ_EN_SHIFT)

/*
 * MEM_DEBUG_CLK_SEL (RW)
 *
 * asserted to use APB clock, so that the memory contents could be read out through APB interface
 */
#define JPEG_CFG_MEM_DEBUG_CLK_SEL_MASK (0x20000UL)
#define JPEG_CFG_MEM_DEBUG_CLK_SEL_SHIFT (17U)
#define JPEG_CFG_MEM_DEBUG_CLK_SEL_SET(x) (((uint32_t)(x) << JPEG_CFG_MEM_DEBUG_CLK_SEL_SHIFT) & JPEG_CFG_MEM_DEBUG_CLK_SEL_MASK)
#define JPEG_CFG_MEM_DEBUG_CLK_SEL_GET(x) (((uint32_t)(x) & JPEG_CFG_MEM_DEBUG_CLK_SEL_MASK) >> JPEG_CFG_MEM_DEBUG_CLK_SEL_SHIFT)

/*
 * CLKGATE (RW)
 *
 * Assert this bit to gate off clock when the module is not working. If reset to zero, the internal clock is always on.
 */
#define JPEG_CFG_CLKGATE_MASK (0x200U)
#define JPEG_CFG_CLKGATE_SHIFT (9U)
#define JPEG_CFG_CLKGATE_SET(x) (((uint32_t)(x) << JPEG_CFG_CLKGATE_SHIFT) & JPEG_CFG_CLKGATE_MASK)
#define JPEG_CFG_CLKGATE_GET(x) (((uint32_t)(x) & JPEG_CFG_CLKGATE_MASK) >> JPEG_CFG_CLKGATE_SHIFT)

/*
 * CFG_OPATH_SEL (RW)
 *
 * 2'b0:2-plane (Y- and UV- plane) or 1-plane (Y-only) as determined by the original data, byte sequence as Y0,Y1, or U,V
 * 2'b01:ARGB8888, byte sequence as B,G,R,A
 * 2'b10:RGB565, byte sequence as R,B
 * 2'b11: YUV422H1P, byte sequence as Y0,U0,Y1,V0
 */
#define JPEG_CFG_CFG_OPATH_SEL_MASK (0x180U)
#define JPEG_CFG_CFG_OPATH_SEL_SHIFT (7U)
#define JPEG_CFG_CFG_OPATH_SEL_SET(x) (((uint32_t)(x) << JPEG_CFG_CFG_OPATH_SEL_SHIFT) & JPEG_CFG_CFG_OPATH_SEL_MASK)
#define JPEG_CFG_CFG_OPATH_SEL_GET(x) (((uint32_t)(x) & JPEG_CFG_CFG_OPATH_SEL_MASK) >> JPEG_CFG_CFG_OPATH_SEL_SHIFT)

/*
 * JDATA_FORMAT (RW)
 *
 * 3'b000: for 420,  hy=2, vy=2, hc=1, vc=1 // 6 sub-blocks per MCU
 * 3'b001: for 422h, hy=2, vy=1, hc=1, vc=1 // 4 sub-blocks per MCU
 * 3'b010: for 422v, hy=1, vy=2, hc=1, vc=1 // 4 sub-blocks per MCU
 * 3'b011: for 444,  hy=1, vy=1, hc=1, vc=1 // 3 sub-blocks per MCU
 * 3'b100: for 400,  hy=2, vy=2, hc=0, vc=0 // 4 sub-blocks  per MCU
 * Others: Undefined
 */
#define JPEG_CFG_JDATA_FORMAT_MASK (0x70U)
#define JPEG_CFG_JDATA_FORMAT_SHIFT (4U)
#define JPEG_CFG_JDATA_FORMAT_SET(x) (((uint32_t)(x) << JPEG_CFG_JDATA_FORMAT_SHIFT) & JPEG_CFG_JDATA_FORMAT_MASK)
#define JPEG_CFG_JDATA_FORMAT_GET(x) (((uint32_t)(x) & JPEG_CFG_JDATA_FORMAT_MASK) >> JPEG_CFG_JDATA_FORMAT_SHIFT)

/*
 * JPEG_SFTRST (RW)
 *
 * Software Reset
 */
#define JPEG_CFG_JPEG_SFTRST_MASK (0x8U)
#define JPEG_CFG_JPEG_SFTRST_SHIFT (3U)
#define JPEG_CFG_JPEG_SFTRST_SET(x) (((uint32_t)(x) << JPEG_CFG_JPEG_SFTRST_SHIFT) & JPEG_CFG_JPEG_SFTRST_MASK)
#define JPEG_CFG_JPEG_SFTRST_GET(x) (((uint32_t)(x) & JPEG_CFG_JPEG_SFTRST_MASK) >> JPEG_CFG_JPEG_SFTRST_SHIFT)

/*
 * START (RW)
 *
 * Asserted if to start a new encoder/decoder conversion.
 * It will at first stop the inner JPEG module, then reset it, and then re-run it.
 * It is a different mode from DMA phase mode.
 * It cannot be configured in the DMA chain descriptor. It should be configured by the core processor.
 * Auto clear.
 */
#define JPEG_CFG_START_MASK (0x4U)
#define JPEG_CFG_START_SHIFT (2U)
#define JPEG_CFG_START_SET(x) (((uint32_t)(x) << JPEG_CFG_START_SHIFT) & JPEG_CFG_START_MASK)
#define JPEG_CFG_START_GET(x) (((uint32_t)(x) & JPEG_CFG_START_MASK) >> JPEG_CFG_START_SHIFT)

/*
 * MODE (RW)
 *
 * 1: decoder, 0:encoder
 */
#define JPEG_CFG_MODE_MASK (0x2U)
#define JPEG_CFG_MODE_SHIFT (1U)
#define JPEG_CFG_MODE_SET(x) (((uint32_t)(x) << JPEG_CFG_MODE_SHIFT) & JPEG_CFG_MODE_MASK)
#define JPEG_CFG_MODE_GET(x) (((uint32_t)(x) & JPEG_CFG_MODE_MASK) >> JPEG_CFG_MODE_SHIFT)

/*
 * JPEG_EN (RW)
 *
 * 1b - Enabled
 */
#define JPEG_CFG_JPEG_EN_MASK (0x1U)
#define JPEG_CFG_JPEG_EN_SHIFT (0U)
#define JPEG_CFG_JPEG_EN_SET(x) (((uint32_t)(x) << JPEG_CFG_JPEG_EN_SHIFT) & JPEG_CFG_JPEG_EN_MASK)
#define JPEG_CFG_JPEG_EN_GET(x) (((uint32_t)(x) & JPEG_CFG_JPEG_EN_MASK) >> JPEG_CFG_JPEG_EN_SHIFT)

/* Bitfield definition for register: STAT */
/*
 * BUSY (RO)
 *
 * When 1 means that the module is busy doing conversion and data transfer.
 */
#define JPEG_STAT_BUSY_MASK (0x80000000UL)
#define JPEG_STAT_BUSY_SHIFT (31U)
#define JPEG_STAT_BUSY_GET(x) (((uint32_t)(x) & JPEG_STAT_BUSY_MASK) >> JPEG_STAT_BUSY_SHIFT)

/*
 * AXI_ERR_ID (RO)
 *
 * the axi err id
 */
#define JPEG_STAT_AXI_ERR_ID_MASK (0x3C00U)
#define JPEG_STAT_AXI_ERR_ID_SHIFT (10U)
#define JPEG_STAT_AXI_ERR_ID_GET(x) (((uint32_t)(x) & JPEG_STAT_AXI_ERR_ID_MASK) >> JPEG_STAT_AXI_ERR_ID_SHIFT)

/*
 * AXI_READ_ERR (RO)
 *
 * in-dma axi bus error
 */
#define JPEG_STAT_AXI_READ_ERR_MASK (0x200U)
#define JPEG_STAT_AXI_READ_ERR_SHIFT (9U)
#define JPEG_STAT_AXI_READ_ERR_GET(x) (((uint32_t)(x) & JPEG_STAT_AXI_READ_ERR_MASK) >> JPEG_STAT_AXI_READ_ERR_SHIFT)

/*
 * AXI_WRITE_ERR (RO)
 *
 * out-dma axi bus error
 */
#define JPEG_STAT_AXI_WRITE_ERR_MASK (0x100U)
#define JPEG_STAT_AXI_WRITE_ERR_SHIFT (8U)
#define JPEG_STAT_AXI_WRITE_ERR_GET(x) (((uint32_t)(x) & JPEG_STAT_AXI_WRITE_ERR_MASK) >> JPEG_STAT_AXI_WRITE_ERR_SHIFT)

/*
 * AXI_ERR (W1C)
 *
 * axi bus error
 */
#define JPEG_STAT_AXI_ERR_MASK (0x80U)
#define JPEG_STAT_AXI_ERR_SHIFT (7U)
#define JPEG_STAT_AXI_ERR_SET(x) (((uint32_t)(x) << JPEG_STAT_AXI_ERR_SHIFT) & JPEG_STAT_AXI_ERR_MASK)
#define JPEG_STAT_AXI_ERR_GET(x) (((uint32_t)(x) & JPEG_STAT_AXI_ERR_MASK) >> JPEG_STAT_AXI_ERR_SHIFT)

/*
 * ONXT_IRQ (W1C)
 *
 * OutDMA next interrupt
 */
#define JPEG_STAT_ONXT_IRQ_MASK (0x40U)
#define JPEG_STAT_ONXT_IRQ_SHIFT (6U)
#define JPEG_STAT_ONXT_IRQ_SET(x) (((uint32_t)(x) << JPEG_STAT_ONXT_IRQ_SHIFT) & JPEG_STAT_ONXT_IRQ_MASK)
#define JPEG_STAT_ONXT_IRQ_GET(x) (((uint32_t)(x) & JPEG_STAT_ONXT_IRQ_MASK) >> JPEG_STAT_ONXT_IRQ_SHIFT)

/*
 * INXT_IRQ (W1C)
 *
 * InDMA next interrupt
 */
#define JPEG_STAT_INXT_IRQ_MASK (0x20U)
#define JPEG_STAT_INXT_IRQ_SHIFT (5U)
#define JPEG_STAT_INXT_IRQ_SET(x) (((uint32_t)(x) << JPEG_STAT_INXT_IRQ_SHIFT) & JPEG_STAT_INXT_IRQ_MASK)
#define JPEG_STAT_INXT_IRQ_GET(x) (((uint32_t)(x) & JPEG_STAT_INXT_IRQ_MASK) >> JPEG_STAT_INXT_IRQ_SHIFT)

/*
 * OUT_DMA_TRANSFER_DONE (W1C)
 *
 * OutDMA process done
 */
#define JPEG_STAT_OUT_DMA_TRANSFER_DONE_MASK (0x10U)
#define JPEG_STAT_OUT_DMA_TRANSFER_DONE_SHIFT (4U)
#define JPEG_STAT_OUT_DMA_TRANSFER_DONE_SET(x) (((uint32_t)(x) << JPEG_STAT_OUT_DMA_TRANSFER_DONE_SHIFT) & JPEG_STAT_OUT_DMA_TRANSFER_DONE_MASK)
#define JPEG_STAT_OUT_DMA_TRANSFER_DONE_GET(x) (((uint32_t)(x) & JPEG_STAT_OUT_DMA_TRANSFER_DONE_MASK) >> JPEG_STAT_OUT_DMA_TRANSFER_DONE_SHIFT)

/*
 * IN_DMA_TRANSFER_DONE (W1C)
 *
 * InDMA process done
 */
#define JPEG_STAT_IN_DMA_TRANSFER_DONE_MASK (0x8U)
#define JPEG_STAT_IN_DMA_TRANSFER_DONE_SHIFT (3U)
#define JPEG_STAT_IN_DMA_TRANSFER_DONE_SET(x) (((uint32_t)(x) << JPEG_STAT_IN_DMA_TRANSFER_DONE_SHIFT) & JPEG_STAT_IN_DMA_TRANSFER_DONE_MASK)
#define JPEG_STAT_IN_DMA_TRANSFER_DONE_GET(x) (((uint32_t)(x) & JPEG_STAT_IN_DMA_TRANSFER_DONE_MASK) >> JPEG_STAT_IN_DMA_TRANSFER_DONE_SHIFT)

/*
 * CODEC_OVER (W1C)
 *
 * Coding or decoding process is over. DMA is not included.
 * The module is completely not busy only when in_dma_transfer_done and out_dma_transfer_done, and codec_over are all asserted.
 */
#define JPEG_STAT_CODEC_OVER_MASK (0x4U)
#define JPEG_STAT_CODEC_OVER_SHIFT (2U)
#define JPEG_STAT_CODEC_OVER_SET(x) (((uint32_t)(x) << JPEG_STAT_CODEC_OVER_SHIFT) & JPEG_STAT_CODEC_OVER_MASK)
#define JPEG_STAT_CODEC_OVER_GET(x) (((uint32_t)(x) & JPEG_STAT_CODEC_OVER_MASK) >> JPEG_STAT_CODEC_OVER_SHIFT)

/*
 * RESTART_MARKER_ERROR (W1C)
 *
 * codec restart marker error interrupt
 */
#define JPEG_STAT_RESTART_MARKER_ERROR_MASK (0x2U)
#define JPEG_STAT_RESTART_MARKER_ERROR_SHIFT (1U)
#define JPEG_STAT_RESTART_MARKER_ERROR_SET(x) (((uint32_t)(x) << JPEG_STAT_RESTART_MARKER_ERROR_SHIFT) & JPEG_STAT_RESTART_MARKER_ERROR_MASK)
#define JPEG_STAT_RESTART_MARKER_ERROR_GET(x) (((uint32_t)(x) & JPEG_STAT_RESTART_MARKER_ERROR_MASK) >> JPEG_STAT_RESTART_MARKER_ERROR_SHIFT)

/* Bitfield definition for register: WIDTH */
/*
 * IMG (RW)
 *
 * Image Width (it is the max index of pixel counting from 0, assuming the top left pixel is indexed as [0,0])
 */
#define JPEG_WIDTH_IMG_MASK (0xFFFFU)
#define JPEG_WIDTH_IMG_SHIFT (0U)
#define JPEG_WIDTH_IMG_SET(x) (((uint32_t)(x) << JPEG_WIDTH_IMG_SHIFT) & JPEG_WIDTH_IMG_MASK)
#define JPEG_WIDTH_IMG_GET(x) (((uint32_t)(x) & JPEG_WIDTH_IMG_MASK) >> JPEG_WIDTH_IMG_SHIFT)

/* Bitfield definition for register: HEIGHT */
/*
 * IMG (RW)
 *
 * Image Height  (it is the max index of pixel counting from 0, assuming the top left pixel is indexed as [0,0])
 */
#define JPEG_HEIGHT_IMG_MASK (0xFFFFU)
#define JPEG_HEIGHT_IMG_SHIFT (0U)
#define JPEG_HEIGHT_IMG_SET(x) (((uint32_t)(x) << JPEG_HEIGHT_IMG_SHIFT) & JPEG_HEIGHT_IMG_MASK)
#define JPEG_HEIGHT_IMG_GET(x) (((uint32_t)(x) & JPEG_HEIGHT_IMG_MASK) >> JPEG_HEIGHT_IMG_SHIFT)

/* Bitfield definition for register: BUFADDR */
/*
 * ADDR (RW)
 *
 * ADDR[31:28] denotes the buffer type:
 * 0x2: Qmem
 * 0x3: HuffEnc
 * 0x4: HuffMin
 * 0x5: HuffBase
 * 0x6: HuffSymb
 * ADDR[27:0] is the address inside the buffer
 */
#define JPEG_BUFADDR_ADDR_MASK (0xFFFFFFFFUL)
#define JPEG_BUFADDR_ADDR_SHIFT (0U)
#define JPEG_BUFADDR_ADDR_SET(x) (((uint32_t)(x) << JPEG_BUFADDR_ADDR_SHIFT) & JPEG_BUFADDR_ADDR_MASK)
#define JPEG_BUFADDR_ADDR_GET(x) (((uint32_t)(x) & JPEG_BUFADDR_ADDR_MASK) >> JPEG_BUFADDR_ADDR_SHIFT)

/* Bitfield definition for register: BUFDATA */
/*
 * DATA (RW)
 *
 * The data write-to/read-from buffer.
 * The n-th address read will be actually the data written for n-1 th address, and the actual stored location is n-1 th address.
 */
#define JPEG_BUFDATA_DATA_MASK (0xFFFFFFFFUL)
#define JPEG_BUFDATA_DATA_SHIFT (0U)
#define JPEG_BUFDATA_DATA_SET(x) (((uint32_t)(x) << JPEG_BUFDATA_DATA_SHIFT) & JPEG_BUFDATA_DATA_MASK)
#define JPEG_BUFDATA_DATA_GET(x) (((uint32_t)(x) & JPEG_BUFDATA_DATA_MASK) >> JPEG_BUFDATA_DATA_SHIFT)

/* Bitfield definition for register: OUTDMACNT */
/*
 * VAL (RO)
 *
 * The out DMA counter
 */
#define JPEG_OUTDMACNT_VAL_MASK (0xFFFFFFFFUL)
#define JPEG_OUTDMACNT_VAL_SHIFT (0U)
#define JPEG_OUTDMACNT_VAL_GET(x) (((uint32_t)(x) & JPEG_OUTDMACNT_VAL_MASK) >> JPEG_OUTDMACNT_VAL_SHIFT)

/* Bitfield definition for register: CSC_COEF0 */
/*
 * YCBCR_MODE (RW)
 *
 * This bit changes the behavior when performing U/V converting.
 * 0b - Converting YUV to RGB data
 * 1b - Converting YCbCr to RGB data
 */
#define JPEG_CSC_COEF0_YCBCR_MODE_MASK (0x80000000UL)
#define JPEG_CSC_COEF0_YCBCR_MODE_SHIFT (31U)
#define JPEG_CSC_COEF0_YCBCR_MODE_SET(x) (((uint32_t)(x) << JPEG_CSC_COEF0_YCBCR_MODE_SHIFT) & JPEG_CSC_COEF0_YCBCR_MODE_MASK)
#define JPEG_CSC_COEF0_YCBCR_MODE_GET(x) (((uint32_t)(x) & JPEG_CSC_COEF0_YCBCR_MODE_MASK) >> JPEG_CSC_COEF0_YCBCR_MODE_SHIFT)

/*
 * ENABLE (RW)
 *
 * Enable the CSC unit.
 * 0b - The CSC is bypassed
 * 1b - The CSC is enabled
 */
#define JPEG_CSC_COEF0_ENABLE_MASK (0x40000000UL)
#define JPEG_CSC_COEF0_ENABLE_SHIFT (30U)
#define JPEG_CSC_COEF0_ENABLE_SET(x) (((uint32_t)(x) << JPEG_CSC_COEF0_ENABLE_SHIFT) & JPEG_CSC_COEF0_ENABLE_MASK)
#define JPEG_CSC_COEF0_ENABLE_GET(x) (((uint32_t)(x) & JPEG_CSC_COEF0_ENABLE_MASK) >> JPEG_CSC_COEF0_ENABLE_SHIFT)

/*
 * C0 (RW)
 *
 * Two's compliment Y multiplier coefficient C0. YUV=0x100 (1.000) YCbCr=0x12A (1.164)
 */
#define JPEG_CSC_COEF0_C0_MASK (0x1FFC0000UL)
#define JPEG_CSC_COEF0_C0_SHIFT (18U)
#define JPEG_CSC_COEF0_C0_SET(x) (((uint32_t)(x) << JPEG_CSC_COEF0_C0_SHIFT) & JPEG_CSC_COEF0_C0_MASK)
#define JPEG_CSC_COEF0_C0_GET(x) (((uint32_t)(x) & JPEG_CSC_COEF0_C0_MASK) >> JPEG_CSC_COEF0_C0_SHIFT)

/*
 * UV_OFFSET (RW)
 *
 * Two's compliment phase offset implicit for CbCr data UV_OFFSET. Generally used for YCbCr to RGB conversion.
 * YCbCr=0x180, YUV=0x000 (typically -128 or 0x180 to indicate normalized -0.5 to 0.5 range).
 */
#define JPEG_CSC_COEF0_UV_OFFSET_MASK (0x3FE00UL)
#define JPEG_CSC_COEF0_UV_OFFSET_SHIFT (9U)
#define JPEG_CSC_COEF0_UV_OFFSET_SET(x) (((uint32_t)(x) << JPEG_CSC_COEF0_UV_OFFSET_SHIFT) & JPEG_CSC_COEF0_UV_OFFSET_MASK)
#define JPEG_CSC_COEF0_UV_OFFSET_GET(x) (((uint32_t)(x) & JPEG_CSC_COEF0_UV_OFFSET_MASK) >> JPEG_CSC_COEF0_UV_OFFSET_SHIFT)

/*
 * Y_OFFSET (RW)
 *
 * Two's compliment amplitude offset implicit in the Y data Y_OFFSET. For YUV, this is typically 0 and for YCbCr, this is
 * typically -16 (0x1F0).
 */
#define JPEG_CSC_COEF0_Y_OFFSET_MASK (0x1FFU)
#define JPEG_CSC_COEF0_Y_OFFSET_SHIFT (0U)
#define JPEG_CSC_COEF0_Y_OFFSET_SET(x) (((uint32_t)(x) << JPEG_CSC_COEF0_Y_OFFSET_SHIFT) & JPEG_CSC_COEF0_Y_OFFSET_MASK)
#define JPEG_CSC_COEF0_Y_OFFSET_GET(x) (((uint32_t)(x) & JPEG_CSC_COEF0_Y_OFFSET_MASK) >> JPEG_CSC_COEF0_Y_OFFSET_SHIFT)

/* Bitfield definition for register: CSC_COEF1 */
/*
 * C1 (RW)
 *
 * Two's compliment Red V/Cr multiplier coefficient C1. YUV=0x123 (1.140) YCbCr=0x198 (1.596).
 */
#define JPEG_CSC_COEF1_C1_MASK (0x7FF0000UL)
#define JPEG_CSC_COEF1_C1_SHIFT (16U)
#define JPEG_CSC_COEF1_C1_SET(x) (((uint32_t)(x) << JPEG_CSC_COEF1_C1_SHIFT) & JPEG_CSC_COEF1_C1_MASK)
#define JPEG_CSC_COEF1_C1_GET(x) (((uint32_t)(x) & JPEG_CSC_COEF1_C1_MASK) >> JPEG_CSC_COEF1_C1_SHIFT)

/*
 * C4 (RW)
 *
 * Two's compliment Blue U/Cb multiplier coefficient C4. YUV=0x208 (2.032) YCbCr=0x204 (2.017).
 */
#define JPEG_CSC_COEF1_C4_MASK (0x7FFU)
#define JPEG_CSC_COEF1_C4_SHIFT (0U)
#define JPEG_CSC_COEF1_C4_SET(x) (((uint32_t)(x) << JPEG_CSC_COEF1_C4_SHIFT) & JPEG_CSC_COEF1_C4_MASK)
#define JPEG_CSC_COEF1_C4_GET(x) (((uint32_t)(x) & JPEG_CSC_COEF1_C4_MASK) >> JPEG_CSC_COEF1_C4_SHIFT)

/* Bitfield definition for register: CSC_COEF2 */
/*
 * C2 (RW)
 *
 * Two's compliment Green V/Cr multiplier coefficient C2. YUV=0x76B (-0.581) YCbCr=0x730 (-0.813).
 */
#define JPEG_CSC_COEF2_C2_MASK (0x7FF0000UL)
#define JPEG_CSC_COEF2_C2_SHIFT (16U)
#define JPEG_CSC_COEF2_C2_SET(x) (((uint32_t)(x) << JPEG_CSC_COEF2_C2_SHIFT) & JPEG_CSC_COEF2_C2_MASK)
#define JPEG_CSC_COEF2_C2_GET(x) (((uint32_t)(x) & JPEG_CSC_COEF2_C2_MASK) >> JPEG_CSC_COEF2_C2_SHIFT)

/*
 * C3 (RW)
 *
 * Two's compliment Green U/Cb multiplier coefficient C3. YUV=0x79C (-0.394) YCbCr=0x79C (-0.392).
 */
#define JPEG_CSC_COEF2_C3_MASK (0x7FFU)
#define JPEG_CSC_COEF2_C3_SHIFT (0U)
#define JPEG_CSC_COEF2_C3_SET(x) (((uint32_t)(x) << JPEG_CSC_COEF2_C3_SHIFT) & JPEG_CSC_COEF2_C3_MASK)
#define JPEG_CSC_COEF2_C3_GET(x) (((uint32_t)(x) & JPEG_CSC_COEF2_C3_MASK) >> JPEG_CSC_COEF2_C3_SHIFT)

/* Bitfield definition for register: RGB2YUV_COEF0 */
/*
 * YCBCR_MODE (RW)
 *
 * Asserted to use YCrCb mode. Must be assigned as 1.
 */
#define JPEG_RGB2YUV_COEF0_YCBCR_MODE_MASK (0x80000000UL)
#define JPEG_RGB2YUV_COEF0_YCBCR_MODE_SHIFT (31U)
#define JPEG_RGB2YUV_COEF0_YCBCR_MODE_SET(x) (((uint32_t)(x) << JPEG_RGB2YUV_COEF0_YCBCR_MODE_SHIFT) & JPEG_RGB2YUV_COEF0_YCBCR_MODE_MASK)
#define JPEG_RGB2YUV_COEF0_YCBCR_MODE_GET(x) (((uint32_t)(x) & JPEG_RGB2YUV_COEF0_YCBCR_MODE_MASK) >> JPEG_RGB2YUV_COEF0_YCBCR_MODE_SHIFT)

/*
 * ENABLE (RW)
 *
 * Asserted to enable this RGB2YCbCr CSC stage
 */
#define JPEG_RGB2YUV_COEF0_ENABLE_MASK (0x40000000UL)
#define JPEG_RGB2YUV_COEF0_ENABLE_SHIFT (30U)
#define JPEG_RGB2YUV_COEF0_ENABLE_SET(x) (((uint32_t)(x) << JPEG_RGB2YUV_COEF0_ENABLE_SHIFT) & JPEG_RGB2YUV_COEF0_ENABLE_MASK)
#define JPEG_RGB2YUV_COEF0_ENABLE_GET(x) (((uint32_t)(x) & JPEG_RGB2YUV_COEF0_ENABLE_MASK) >> JPEG_RGB2YUV_COEF0_ENABLE_SHIFT)

/*
 * C0 (RW)
 *
 * CSC parameters C0
 */
#define JPEG_RGB2YUV_COEF0_C0_MASK (0x1FFC0000UL)
#define JPEG_RGB2YUV_COEF0_C0_SHIFT (18U)
#define JPEG_RGB2YUV_COEF0_C0_SET(x) (((uint32_t)(x) << JPEG_RGB2YUV_COEF0_C0_SHIFT) & JPEG_RGB2YUV_COEF0_C0_MASK)
#define JPEG_RGB2YUV_COEF0_C0_GET(x) (((uint32_t)(x) & JPEG_RGB2YUV_COEF0_C0_MASK) >> JPEG_RGB2YUV_COEF0_C0_SHIFT)

/*
 * UV_OFFSET (RW)
 *
 * CSC parameters UV_OFFSET
 */
#define JPEG_RGB2YUV_COEF0_UV_OFFSET_MASK (0x3FE00UL)
#define JPEG_RGB2YUV_COEF0_UV_OFFSET_SHIFT (9U)
#define JPEG_RGB2YUV_COEF0_UV_OFFSET_SET(x) (((uint32_t)(x) << JPEG_RGB2YUV_COEF0_UV_OFFSET_SHIFT) & JPEG_RGB2YUV_COEF0_UV_OFFSET_MASK)
#define JPEG_RGB2YUV_COEF0_UV_OFFSET_GET(x) (((uint32_t)(x) & JPEG_RGB2YUV_COEF0_UV_OFFSET_MASK) >> JPEG_RGB2YUV_COEF0_UV_OFFSET_SHIFT)

/*
 * Y_OFFSET (RW)
 *
 * CSC parameters Y_OFFSET
 */
#define JPEG_RGB2YUV_COEF0_Y_OFFSET_MASK (0x1FFU)
#define JPEG_RGB2YUV_COEF0_Y_OFFSET_SHIFT (0U)
#define JPEG_RGB2YUV_COEF0_Y_OFFSET_SET(x) (((uint32_t)(x) << JPEG_RGB2YUV_COEF0_Y_OFFSET_SHIFT) & JPEG_RGB2YUV_COEF0_Y_OFFSET_MASK)
#define JPEG_RGB2YUV_COEF0_Y_OFFSET_GET(x) (((uint32_t)(x) & JPEG_RGB2YUV_COEF0_Y_OFFSET_MASK) >> JPEG_RGB2YUV_COEF0_Y_OFFSET_SHIFT)

/* Bitfield definition for register: RGB2YUV_COEF1 */
/*
 * C1 (RW)
 *
 * CSC parameters C1
 */
#define JPEG_RGB2YUV_COEF1_C1_MASK (0x7FF0000UL)
#define JPEG_RGB2YUV_COEF1_C1_SHIFT (16U)
#define JPEG_RGB2YUV_COEF1_C1_SET(x) (((uint32_t)(x) << JPEG_RGB2YUV_COEF1_C1_SHIFT) & JPEG_RGB2YUV_COEF1_C1_MASK)
#define JPEG_RGB2YUV_COEF1_C1_GET(x) (((uint32_t)(x) & JPEG_RGB2YUV_COEF1_C1_MASK) >> JPEG_RGB2YUV_COEF1_C1_SHIFT)

/*
 * C4 (RW)
 *
 * CSC parameters C4
 */
#define JPEG_RGB2YUV_COEF1_C4_MASK (0x7FFU)
#define JPEG_RGB2YUV_COEF1_C4_SHIFT (0U)
#define JPEG_RGB2YUV_COEF1_C4_SET(x) (((uint32_t)(x) << JPEG_RGB2YUV_COEF1_C4_SHIFT) & JPEG_RGB2YUV_COEF1_C4_MASK)
#define JPEG_RGB2YUV_COEF1_C4_GET(x) (((uint32_t)(x) & JPEG_RGB2YUV_COEF1_C4_MASK) >> JPEG_RGB2YUV_COEF1_C4_SHIFT)

/* Bitfield definition for register: RGB2YUV_COEF2 */
/*
 * C2 (RW)
 *
 * CSC parameters C2
 */
#define JPEG_RGB2YUV_COEF2_C2_MASK (0x7FF0000UL)
#define JPEG_RGB2YUV_COEF2_C2_SHIFT (16U)
#define JPEG_RGB2YUV_COEF2_C2_SET(x) (((uint32_t)(x) << JPEG_RGB2YUV_COEF2_C2_SHIFT) & JPEG_RGB2YUV_COEF2_C2_MASK)
#define JPEG_RGB2YUV_COEF2_C2_GET(x) (((uint32_t)(x) & JPEG_RGB2YUV_COEF2_C2_MASK) >> JPEG_RGB2YUV_COEF2_C2_SHIFT)

/*
 * C3 (RW)
 *
 * CSC parameters C3
 */
#define JPEG_RGB2YUV_COEF2_C3_MASK (0x7FFU)
#define JPEG_RGB2YUV_COEF2_C3_SHIFT (0U)
#define JPEG_RGB2YUV_COEF2_C3_SET(x) (((uint32_t)(x) << JPEG_RGB2YUV_COEF2_C3_SHIFT) & JPEG_RGB2YUV_COEF2_C3_MASK)
#define JPEG_RGB2YUV_COEF2_C3_GET(x) (((uint32_t)(x) & JPEG_RGB2YUV_COEF2_C3_MASK) >> JPEG_RGB2YUV_COEF2_C3_SHIFT)

/* Bitfield definition for register: RGB2YUV_COEF3 */
/*
 * C6 (RW)
 *
 * CSC parameters C6
 */
#define JPEG_RGB2YUV_COEF3_C6_MASK (0x7FF0000UL)
#define JPEG_RGB2YUV_COEF3_C6_SHIFT (16U)
#define JPEG_RGB2YUV_COEF3_C6_SET(x) (((uint32_t)(x) << JPEG_RGB2YUV_COEF3_C6_SHIFT) & JPEG_RGB2YUV_COEF3_C6_MASK)
#define JPEG_RGB2YUV_COEF3_C6_GET(x) (((uint32_t)(x) & JPEG_RGB2YUV_COEF3_C6_MASK) >> JPEG_RGB2YUV_COEF3_C6_SHIFT)

/*
 * C5 (RW)
 *
 * CSC parameters C5
 */
#define JPEG_RGB2YUV_COEF3_C5_MASK (0x7FFU)
#define JPEG_RGB2YUV_COEF3_C5_SHIFT (0U)
#define JPEG_RGB2YUV_COEF3_C5_SET(x) (((uint32_t)(x) << JPEG_RGB2YUV_COEF3_C5_SHIFT) & JPEG_RGB2YUV_COEF3_C5_MASK)
#define JPEG_RGB2YUV_COEF3_C5_GET(x) (((uint32_t)(x) & JPEG_RGB2YUV_COEF3_C5_MASK) >> JPEG_RGB2YUV_COEF3_C5_SHIFT)

/* Bitfield definition for register: RGB2YUV_COEF4 */
/*
 * C8 (RW)
 *
 * CSC parameters C8
 */
#define JPEG_RGB2YUV_COEF4_C8_MASK (0x7FF0000UL)
#define JPEG_RGB2YUV_COEF4_C8_SHIFT (16U)
#define JPEG_RGB2YUV_COEF4_C8_SET(x) (((uint32_t)(x) << JPEG_RGB2YUV_COEF4_C8_SHIFT) & JPEG_RGB2YUV_COEF4_C8_MASK)
#define JPEG_RGB2YUV_COEF4_C8_GET(x) (((uint32_t)(x) & JPEG_RGB2YUV_COEF4_C8_MASK) >> JPEG_RGB2YUV_COEF4_C8_SHIFT)

/*
 * C7 (RW)
 *
 * CSC parameters C7
 */
#define JPEG_RGB2YUV_COEF4_C7_MASK (0x7FFU)
#define JPEG_RGB2YUV_COEF4_C7_SHIFT (0U)
#define JPEG_RGB2YUV_COEF4_C7_SET(x) (((uint32_t)(x) << JPEG_RGB2YUV_COEF4_C7_SHIFT) & JPEG_RGB2YUV_COEF4_C7_MASK)
#define JPEG_RGB2YUV_COEF4_C7_GET(x) (((uint32_t)(x) & JPEG_RGB2YUV_COEF4_C7_MASK) >> JPEG_RGB2YUV_COEF4_C7_SHIFT)

/* Bitfield definition for register: IMGREG1 */
/*
 * RE (RW)
 *
 * Encoder Use only.
 * Asseted to enable the Restart Marker processing. A Restart Marker is inserted in the outputted ECS (Entropy Coded Segment) every NRST+1 MCUs
 */
#define JPEG_IMGREG1_RE_MASK (0x4U)
#define JPEG_IMGREG1_RE_SHIFT (2U)
#define JPEG_IMGREG1_RE_SET(x) (((uint32_t)(x) << JPEG_IMGREG1_RE_SHIFT) & JPEG_IMGREG1_RE_MASK)
#define JPEG_IMGREG1_RE_GET(x) (((uint32_t)(x) & JPEG_IMGREG1_RE_MASK) >> JPEG_IMGREG1_RE_SHIFT)

/*
 * NCOL (RW)
 *
 * Ncol is the number of color components in the image data to process minus 1. For example, for a grayscale image Ncol=0, for an RGB image, Ncol=2
 */
#define JPEG_IMGREG1_NCOL_MASK (0x3U)
#define JPEG_IMGREG1_NCOL_SHIFT (0U)
#define JPEG_IMGREG1_NCOL_SET(x) (((uint32_t)(x) << JPEG_IMGREG1_NCOL_SHIFT) & JPEG_IMGREG1_NCOL_MASK)
#define JPEG_IMGREG1_NCOL_GET(x) (((uint32_t)(x) & JPEG_IMGREG1_NCOL_MASK) >> JPEG_IMGREG1_NCOL_SHIFT)

/* Bitfield definition for register: IMGREG2 */
/*
 * NMCU (RW)
 *
 * Encoder Use only.
 * The number of NMCU to be generated in encoder mode
 */
#define JPEG_IMGREG2_NMCU_MASK (0x3FFFFFFUL)
#define JPEG_IMGREG2_NMCU_SHIFT (0U)
#define JPEG_IMGREG2_NMCU_SET(x) (((uint32_t)(x) << JPEG_IMGREG2_NMCU_SHIFT) & JPEG_IMGREG2_NMCU_MASK)
#define JPEG_IMGREG2_NMCU_GET(x) (((uint32_t)(x) & JPEG_IMGREG2_NMCU_MASK) >> JPEG_IMGREG2_NMCU_SHIFT)

/* Bitfield definition for register: IMGREG3 */
/*
 * NRST (RW)
 *
 * Encoder use only.
 * It is the number of MCUs between two Restart Markers (if enabled) minus 1. The content of this register is ignored if the Re bit inregister 1 is not set.
 */
#define JPEG_IMGREG3_NRST_MASK (0xFFFFU)
#define JPEG_IMGREG3_NRST_SHIFT (0U)
#define JPEG_IMGREG3_NRST_SET(x) (((uint32_t)(x) << JPEG_IMGREG3_NRST_SHIFT) & JPEG_IMGREG3_NRST_MASK)
#define JPEG_IMGREG3_NRST_GET(x) (((uint32_t)(x) & JPEG_IMGREG3_NRST_MASK) >> JPEG_IMGREG3_NRST_SHIFT)

/* Bitfield definition for register array: IMGREG */
/*
 * NBLOCK (RW)
 *
 * Encoder use only.
 * The number of data units (8x8 blocks of data) of the color componet contained in the MCU minus 1.
 */
#define JPEG_IMGREG_NBLOCK_MASK (0xF0U)
#define JPEG_IMGREG_NBLOCK_SHIFT (4U)
#define JPEG_IMGREG_NBLOCK_SET(x) (((uint32_t)(x) << JPEG_IMGREG_NBLOCK_SHIFT) & JPEG_IMGREG_NBLOCK_MASK)
#define JPEG_IMGREG_NBLOCK_GET(x) (((uint32_t)(x) & JPEG_IMGREG_NBLOCK_MASK) >> JPEG_IMGREG_NBLOCK_SHIFT)

/*
 * QT (RW)
 *
 * Encoder use only.
 * The selection of the quantization table.
 */
#define JPEG_IMGREG_QT_MASK (0xCU)
#define JPEG_IMGREG_QT_SHIFT (2U)
#define JPEG_IMGREG_QT_SET(x) (((uint32_t)(x) << JPEG_IMGREG_QT_SHIFT) & JPEG_IMGREG_QT_MASK)
#define JPEG_IMGREG_QT_GET(x) (((uint32_t)(x) & JPEG_IMGREG_QT_MASK) >> JPEG_IMGREG_QT_SHIFT)

/*
 * HA (RW)
 *
 * Encoder use only.
 * The selection of the Huffman table for the encoding of the AC coefficients in the data units belonging to the color component.
 */
#define JPEG_IMGREG_HA_MASK (0x2U)
#define JPEG_IMGREG_HA_SHIFT (1U)
#define JPEG_IMGREG_HA_SET(x) (((uint32_t)(x) << JPEG_IMGREG_HA_SHIFT) & JPEG_IMGREG_HA_MASK)
#define JPEG_IMGREG_HA_GET(x) (((uint32_t)(x) & JPEG_IMGREG_HA_MASK) >> JPEG_IMGREG_HA_SHIFT)

/*
 * HD (RW)
 *
 * Encoder use only.
 * The selection of the Huffman table for the encoding of the DC coefficients in the data units belonging to the color component.
 */
#define JPEG_IMGREG_HD_MASK (0x1U)
#define JPEG_IMGREG_HD_SHIFT (0U)
#define JPEG_IMGREG_HD_SET(x) (((uint32_t)(x) << JPEG_IMGREG_HD_SHIFT) & JPEG_IMGREG_HD_MASK)
#define JPEG_IMGREG_HD_GET(x) (((uint32_t)(x) & JPEG_IMGREG_HD_MASK) >> JPEG_IMGREG_HD_SHIFT)



/* IMGREG register group index macro definition */
#define JPEG_IMGREG_REG40 (0UL)
#define JPEG_IMGREG_REG41 (1UL)
#define JPEG_IMGREG_REG42 (2UL)
#define JPEG_IMGREG_REG43 (3UL)


#endif /* HPM_JPEG_H */
