/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_GWC_H
#define HPM_GWC_H

typedef struct {
    __RW uint32_t GLB_CTRL;                    /* 0x0: control reg */
    __RW uint32_t IRQ_MASK;                    /* 0x4: interrupt enable */
    __RW uint32_t IRQ_STS;                     /* 0x8: interrupt status */
    __R  uint8_t  RESERVED0[4];                /* 0xC - 0xF: Reserved */
    struct {
        __RW uint32_t CFG0;                    /* 0x10: config reg 0 */
        __RW uint32_t CFG1;                    /* 0x14: config reg 1 */
        __RW uint32_t REFCRC;                  /* 0x18: reference CRC */
        __RW uint32_t CALCRC;                  /* 0x1C: calculated CRC */
    } CHANNEL[16];
} GWC_Type;


/* Bitfield definition for register: GLB_CTRL */
/*
 * CLK_POL (RW)
 *
 * graphic clock polarity.
 * set to invert input graphic clock
 */
#define GWC_GLB_CTRL_CLK_POL_MASK (0x80U)
#define GWC_GLB_CTRL_CLK_POL_SHIFT (7U)
#define GWC_GLB_CTRL_CLK_POL_SET(x) (((uint32_t)(x) << GWC_GLB_CTRL_CLK_POL_SHIFT) & GWC_GLB_CTRL_CLK_POL_MASK)
#define GWC_GLB_CTRL_CLK_POL_GET(x) (((uint32_t)(x) & GWC_GLB_CTRL_CLK_POL_MASK) >> GWC_GLB_CTRL_CLK_POL_SHIFT)

/*
 * GWC_EN (RW)
 *
 * graphic window check enable.
 * set to enable the whole block
 */
#define GWC_GLB_CTRL_GWC_EN_MASK (0x1U)
#define GWC_GLB_CTRL_GWC_EN_SHIFT (0U)
#define GWC_GLB_CTRL_GWC_EN_SET(x) (((uint32_t)(x) << GWC_GLB_CTRL_GWC_EN_SHIFT) & GWC_GLB_CTRL_GWC_EN_MASK)
#define GWC_GLB_CTRL_GWC_EN_GET(x) (((uint32_t)(x) & GWC_GLB_CTRL_GWC_EN_MASK) >> GWC_GLB_CTRL_GWC_EN_SHIFT)

/* Bitfield definition for register: IRQ_MASK */
/*
 * MASK_RREEZ (RW)
 *
 * freeze mask, set to disable changing ERR_MASK and FUNC_MASK.
 * can only be cleared by system reset
 */
#define GWC_IRQ_MASK_MASK_RREEZ_MASK (0x8U)
#define GWC_IRQ_MASK_MASK_RREEZ_SHIFT (3U)
#define GWC_IRQ_MASK_MASK_RREEZ_SET(x) (((uint32_t)(x) << GWC_IRQ_MASK_MASK_RREEZ_SHIFT) & GWC_IRQ_MASK_MASK_RREEZ_MASK)
#define GWC_IRQ_MASK_MASK_RREEZ_GET(x) (((uint32_t)(x) & GWC_IRQ_MASK_MASK_RREEZ_MASK) >> GWC_IRQ_MASK_MASK_RREEZ_SHIFT)

/*
 * FUNC_MASK (RW)
 *
 * function interrupt mask
 */
#define GWC_IRQ_MASK_FUNC_MASK_MASK (0x2U)
#define GWC_IRQ_MASK_FUNC_MASK_SHIFT (1U)
#define GWC_IRQ_MASK_FUNC_MASK_SET(x) (((uint32_t)(x) << GWC_IRQ_MASK_FUNC_MASK_SHIFT) & GWC_IRQ_MASK_FUNC_MASK_MASK)
#define GWC_IRQ_MASK_FUNC_MASK_GET(x) (((uint32_t)(x) & GWC_IRQ_MASK_FUNC_MASK_MASK) >> GWC_IRQ_MASK_FUNC_MASK_SHIFT)

/*
 * ERR_MASK (RW)
 *
 * error interrupt mask
 */
#define GWC_IRQ_MASK_ERR_MASK_MASK (0x1U)
#define GWC_IRQ_MASK_ERR_MASK_SHIFT (0U)
#define GWC_IRQ_MASK_ERR_MASK_SET(x) (((uint32_t)(x) << GWC_IRQ_MASK_ERR_MASK_SHIFT) & GWC_IRQ_MASK_ERR_MASK_MASK)
#define GWC_IRQ_MASK_ERR_MASK_GET(x) (((uint32_t)(x) & GWC_IRQ_MASK_ERR_MASK_MASK) >> GWC_IRQ_MASK_ERR_MASK_SHIFT)

/* Bitfield definition for register: IRQ_STS */
/*
 * FUNC_STS (W1C)
 *
 * function interrupt status.
 * it's set when detect two VSYNC signals after the block is enabled(GWC_EN is set)
 * software write 1 to clear.
 */
#define GWC_IRQ_STS_FUNC_STS_MASK (0x20000UL)
#define GWC_IRQ_STS_FUNC_STS_SHIFT (17U)
#define GWC_IRQ_STS_FUNC_STS_SET(x) (((uint32_t)(x) << GWC_IRQ_STS_FUNC_STS_SHIFT) & GWC_IRQ_STS_FUNC_STS_MASK)
#define GWC_IRQ_STS_FUNC_STS_GET(x) (((uint32_t)(x) & GWC_IRQ_STS_FUNC_STS_MASK) >> GWC_IRQ_STS_FUNC_STS_SHIFT)

/*
 * ERR_STS (RO)
 *
 * error status, it's OR of GWC_FAIL_STS[15:0]
 */
#define GWC_IRQ_STS_ERR_STS_MASK (0x10000UL)
#define GWC_IRQ_STS_ERR_STS_SHIFT (16U)
#define GWC_IRQ_STS_ERR_STS_GET(x) (((uint32_t)(x) & GWC_IRQ_STS_ERR_STS_MASK) >> GWC_IRQ_STS_ERR_STS_SHIFT)

/*
 * GWC_FAIL_STS (W1C)
 *
 * graphic window check fail interrupt status.
 * will be set if the calculated CRC not equal reference CRC.
 * one bit for each channel.
 * software write 1 to clear.
 */
#define GWC_IRQ_STS_GWC_FAIL_STS_MASK (0xFFFFU)
#define GWC_IRQ_STS_GWC_FAIL_STS_SHIFT (0U)
#define GWC_IRQ_STS_GWC_FAIL_STS_SET(x) (((uint32_t)(x) << GWC_IRQ_STS_GWC_FAIL_STS_SHIFT) & GWC_IRQ_STS_GWC_FAIL_STS_MASK)
#define GWC_IRQ_STS_GWC_FAIL_STS_GET(x) (((uint32_t)(x) & GWC_IRQ_STS_GWC_FAIL_STS_MASK) >> GWC_IRQ_STS_GWC_FAIL_STS_SHIFT)

/* Bitfield definition for register of struct array CHANNEL: CFG0 */
/*
 * ENABLE (RW)
 *
 * channel enable
 */
#define GWC_CHANNEL_CFG0_ENABLE_MASK (0x80000000UL)
#define GWC_CHANNEL_CFG0_ENABLE_SHIFT (31U)
#define GWC_CHANNEL_CFG0_ENABLE_SET(x) (((uint32_t)(x) << GWC_CHANNEL_CFG0_ENABLE_SHIFT) & GWC_CHANNEL_CFG0_ENABLE_MASK)
#define GWC_CHANNEL_CFG0_ENABLE_GET(x) (((uint32_t)(x) & GWC_CHANNEL_CFG0_ENABLE_MASK) >> GWC_CHANNEL_CFG0_ENABLE_SHIFT)

/*
 * FREEZE (RW)
 *
 * freeze config. set to freeze all other config registers for current channel.
 * can only be cleared by system reset
 */
#define GWC_CHANNEL_CFG0_FREEZE_MASK (0x40000000UL)
#define GWC_CHANNEL_CFG0_FREEZE_SHIFT (30U)
#define GWC_CHANNEL_CFG0_FREEZE_SET(x) (((uint32_t)(x) << GWC_CHANNEL_CFG0_FREEZE_SHIFT) & GWC_CHANNEL_CFG0_FREEZE_MASK)
#define GWC_CHANNEL_CFG0_FREEZE_GET(x) (((uint32_t)(x) & GWC_CHANNEL_CFG0_FREEZE_MASK) >> GWC_CHANNEL_CFG0_FREEZE_SHIFT)

/*
 * START_ROW (RW)
 *
 * define the window start row number
 */
#define GWC_CHANNEL_CFG0_START_ROW_MASK (0xFFF0000UL)
#define GWC_CHANNEL_CFG0_START_ROW_SHIFT (16U)
#define GWC_CHANNEL_CFG0_START_ROW_SET(x) (((uint32_t)(x) << GWC_CHANNEL_CFG0_START_ROW_SHIFT) & GWC_CHANNEL_CFG0_START_ROW_MASK)
#define GWC_CHANNEL_CFG0_START_ROW_GET(x) (((uint32_t)(x) & GWC_CHANNEL_CFG0_START_ROW_MASK) >> GWC_CHANNEL_CFG0_START_ROW_SHIFT)

/*
 * START_COL (RW)
 *
 * define the window start column number
 */
#define GWC_CHANNEL_CFG0_START_COL_MASK (0x1FFFU)
#define GWC_CHANNEL_CFG0_START_COL_SHIFT (0U)
#define GWC_CHANNEL_CFG0_START_COL_SET(x) (((uint32_t)(x) << GWC_CHANNEL_CFG0_START_COL_SHIFT) & GWC_CHANNEL_CFG0_START_COL_MASK)
#define GWC_CHANNEL_CFG0_START_COL_GET(x) (((uint32_t)(x) & GWC_CHANNEL_CFG0_START_COL_MASK) >> GWC_CHANNEL_CFG0_START_COL_SHIFT)

/* Bitfield definition for register of struct array CHANNEL: CFG1 */
/*
 * END_ROW (RW)
 *
 * define the window end row number
 */
#define GWC_CHANNEL_CFG1_END_ROW_MASK (0xFFF0000UL)
#define GWC_CHANNEL_CFG1_END_ROW_SHIFT (16U)
#define GWC_CHANNEL_CFG1_END_ROW_SET(x) (((uint32_t)(x) << GWC_CHANNEL_CFG1_END_ROW_SHIFT) & GWC_CHANNEL_CFG1_END_ROW_MASK)
#define GWC_CHANNEL_CFG1_END_ROW_GET(x) (((uint32_t)(x) & GWC_CHANNEL_CFG1_END_ROW_MASK) >> GWC_CHANNEL_CFG1_END_ROW_SHIFT)

/*
 * END_COL (RW)
 *
 * define the window end column number
 */
#define GWC_CHANNEL_CFG1_END_COL_MASK (0x1FFFU)
#define GWC_CHANNEL_CFG1_END_COL_SHIFT (0U)
#define GWC_CHANNEL_CFG1_END_COL_SET(x) (((uint32_t)(x) << GWC_CHANNEL_CFG1_END_COL_SHIFT) & GWC_CHANNEL_CFG1_END_COL_MASK)
#define GWC_CHANNEL_CFG1_END_COL_GET(x) (((uint32_t)(x) & GWC_CHANNEL_CFG1_END_COL_MASK) >> GWC_CHANNEL_CFG1_END_COL_SHIFT)

/* Bitfield definition for register of struct array CHANNEL: REFCRC */
/*
 * REF_CRC (RW)
 *
 * reference CRC
 * polynomial function:  0x104C11DB7
 */
#define GWC_CHANNEL_REFCRC_REF_CRC_MASK (0xFFFFFFFFUL)
#define GWC_CHANNEL_REFCRC_REF_CRC_SHIFT (0U)
#define GWC_CHANNEL_REFCRC_REF_CRC_SET(x) (((uint32_t)(x) << GWC_CHANNEL_REFCRC_REF_CRC_SHIFT) & GWC_CHANNEL_REFCRC_REF_CRC_MASK)
#define GWC_CHANNEL_REFCRC_REF_CRC_GET(x) (((uint32_t)(x) & GWC_CHANNEL_REFCRC_REF_CRC_MASK) >> GWC_CHANNEL_REFCRC_REF_CRC_SHIFT)

/* Bitfield definition for register of struct array CHANNEL: CALCRC */
/*
 * CAL_CRC (RW)
 *
 * calculated CRC for last frame
 */
#define GWC_CHANNEL_CALCRC_CAL_CRC_MASK (0xFFFFFFFFUL)
#define GWC_CHANNEL_CALCRC_CAL_CRC_SHIFT (0U)
#define GWC_CHANNEL_CALCRC_CAL_CRC_SET(x) (((uint32_t)(x) << GWC_CHANNEL_CALCRC_CAL_CRC_SHIFT) & GWC_CHANNEL_CALCRC_CAL_CRC_MASK)
#define GWC_CHANNEL_CALCRC_CAL_CRC_GET(x) (((uint32_t)(x) & GWC_CHANNEL_CALCRC_CAL_CRC_MASK) >> GWC_CHANNEL_CALCRC_CAL_CRC_SHIFT)



/* CHANNEL register group index macro definition */
#define GWC_CHANNEL_CH0 (0UL)
#define GWC_CHANNEL_CH15 (15UL)


#endif /* HPM_GWC_H */
