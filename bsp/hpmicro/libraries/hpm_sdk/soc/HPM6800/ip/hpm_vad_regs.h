/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_VAD_H
#define HPM_VAD_H

typedef struct {
    __RW uint32_t CTRL;                        /* 0x0: Control Register */
    __RW uint32_t FILTCTRL;                    /* 0x4: Filter Control Register */
    __RW uint32_t DEC_CTRL0;                   /* 0x8: Decision Control Register 0 */
    __RW uint32_t DEC_CTRL1;                   /* 0xC: Decision Control Register 1 */
    __RW uint32_t DEC_CTRL2;                   /* 0x10: Decision Control Register 2 */
    __R  uint8_t  RESERVED0[4];                /* 0x14 - 0x17: Reserved */
    __RW uint32_t ST;                          /* 0x18: Status */
    __RW uint32_t OFIFO;                       /* 0x1C: Out FIFO */
    __RW uint32_t RUN;                         /* 0x20: Run Command Register */
    __RW uint32_t OFIFO_CTRL;                  /* 0x24: Out FIFO Control Register */
    __RW uint32_t CIC_CFG;                     /* 0x28: CIC Configuration Register */
    __R  uint8_t  RESERVED1[116];              /* 0x2C - 0x9F: Reserved */
    __R  uint32_t COEF[1];                     /* 0xA0: Short Time Energy Register */
} VAD_Type;


/* Bitfield definition for register: CTRL */
/*
 * CAPT_DLY (RW)
 *
 * Capture cycle delay>=0, should be less than PDM_CLK_HFDIV
 */
#define VAD_CTRL_CAPT_DLY_MASK (0xF000000UL)
#define VAD_CTRL_CAPT_DLY_SHIFT (24U)
#define VAD_CTRL_CAPT_DLY_SET(x) (((uint32_t)(x) << VAD_CTRL_CAPT_DLY_SHIFT) & VAD_CTRL_CAPT_DLY_MASK)
#define VAD_CTRL_CAPT_DLY_GET(x) (((uint32_t)(x) & VAD_CTRL_CAPT_DLY_MASK) >> VAD_CTRL_CAPT_DLY_SHIFT)

/*
 * PDM_CLK_HFDIV (RW)
 *
 * The clock divider will work at least 4.
 * 0: div-by-2,
 * 1: div-by-4
 * . . .
 * n: div-by-2*(n+1)
 */
#define VAD_CTRL_PDM_CLK_HFDIV_MASK (0xF00000UL)
#define VAD_CTRL_PDM_CLK_HFDIV_SHIFT (20U)
#define VAD_CTRL_PDM_CLK_HFDIV_SET(x) (((uint32_t)(x) << VAD_CTRL_PDM_CLK_HFDIV_SHIFT) & VAD_CTRL_PDM_CLK_HFDIV_MASK)
#define VAD_CTRL_PDM_CLK_HFDIV_GET(x) (((uint32_t)(x) & VAD_CTRL_PDM_CLK_HFDIV_MASK) >> VAD_CTRL_PDM_CLK_HFDIV_SHIFT)

/*
 * VAD_IE (RW)
 *
 * VAD event interrupt enable
 */
#define VAD_CTRL_VAD_IE_MASK (0x40000UL)
#define VAD_CTRL_VAD_IE_SHIFT (18U)
#define VAD_CTRL_VAD_IE_SET(x) (((uint32_t)(x) << VAD_CTRL_VAD_IE_SHIFT) & VAD_CTRL_VAD_IE_MASK)
#define VAD_CTRL_VAD_IE_GET(x) (((uint32_t)(x) & VAD_CTRL_VAD_IE_MASK) >> VAD_CTRL_VAD_IE_SHIFT)

/*
 * OFIFO_AV_IE (RW)
 *
 * OFIFO data available interrupt enable
 */
#define VAD_CTRL_OFIFO_AV_IE_MASK (0x20000UL)
#define VAD_CTRL_OFIFO_AV_IE_SHIFT (17U)
#define VAD_CTRL_OFIFO_AV_IE_SET(x) (((uint32_t)(x) << VAD_CTRL_OFIFO_AV_IE_SHIFT) & VAD_CTRL_OFIFO_AV_IE_MASK)
#define VAD_CTRL_OFIFO_AV_IE_GET(x) (((uint32_t)(x) & VAD_CTRL_OFIFO_AV_IE_MASK) >> VAD_CTRL_OFIFO_AV_IE_SHIFT)

/*
 * MEMBUF_EMPTY_IE (RW)
 *
 * Buf empty interrupt enable
 */
#define VAD_CTRL_MEMBUF_EMPTY_IE_MASK (0x10000UL)
#define VAD_CTRL_MEMBUF_EMPTY_IE_SHIFT (16U)
#define VAD_CTRL_MEMBUF_EMPTY_IE_SET(x) (((uint32_t)(x) << VAD_CTRL_MEMBUF_EMPTY_IE_SHIFT) & VAD_CTRL_MEMBUF_EMPTY_IE_MASK)
#define VAD_CTRL_MEMBUF_EMPTY_IE_GET(x) (((uint32_t)(x) & VAD_CTRL_MEMBUF_EMPTY_IE_MASK) >> VAD_CTRL_MEMBUF_EMPTY_IE_SHIFT)

/*
 * OFIFO_OVFL_ERR_IE (RW)
 *
 * OFIFO overflow error interrupt enable
 */
#define VAD_CTRL_OFIFO_OVFL_ERR_IE_MASK (0x8000U)
#define VAD_CTRL_OFIFO_OVFL_ERR_IE_SHIFT (15U)
#define VAD_CTRL_OFIFO_OVFL_ERR_IE_SET(x) (((uint32_t)(x) << VAD_CTRL_OFIFO_OVFL_ERR_IE_SHIFT) & VAD_CTRL_OFIFO_OVFL_ERR_IE_MASK)
#define VAD_CTRL_OFIFO_OVFL_ERR_IE_GET(x) (((uint32_t)(x) & VAD_CTRL_OFIFO_OVFL_ERR_IE_MASK) >> VAD_CTRL_OFIFO_OVFL_ERR_IE_SHIFT)

/*
 * IIR_OVLD_ERR_IE (RW)
 *
 * IIR overload error interrupt enable
 */
#define VAD_CTRL_IIR_OVLD_ERR_IE_MASK (0x4000U)
#define VAD_CTRL_IIR_OVLD_ERR_IE_SHIFT (14U)
#define VAD_CTRL_IIR_OVLD_ERR_IE_SET(x) (((uint32_t)(x) << VAD_CTRL_IIR_OVLD_ERR_IE_SHIFT) & VAD_CTRL_IIR_OVLD_ERR_IE_MASK)
#define VAD_CTRL_IIR_OVLD_ERR_IE_GET(x) (((uint32_t)(x) & VAD_CTRL_IIR_OVLD_ERR_IE_MASK) >> VAD_CTRL_IIR_OVLD_ERR_IE_SHIFT)

/*
 * IIR_OVFL_ERR_IE (RW)
 *
 * IIR overflow error interrupt enable
 */
#define VAD_CTRL_IIR_OVFL_ERR_IE_MASK (0x2000U)
#define VAD_CTRL_IIR_OVFL_ERR_IE_SHIFT (13U)
#define VAD_CTRL_IIR_OVFL_ERR_IE_SET(x) (((uint32_t)(x) << VAD_CTRL_IIR_OVFL_ERR_IE_SHIFT) & VAD_CTRL_IIR_OVFL_ERR_IE_MASK)
#define VAD_CTRL_IIR_OVFL_ERR_IE_GET(x) (((uint32_t)(x) & VAD_CTRL_IIR_OVFL_ERR_IE_MASK) >> VAD_CTRL_IIR_OVFL_ERR_IE_SHIFT)

/*
 * CIC_OVLD_ERR_IE (RW)
 *
 * CIC overload Interrupt Enable
 */
#define VAD_CTRL_CIC_OVLD_ERR_IE_MASK (0x1000U)
#define VAD_CTRL_CIC_OVLD_ERR_IE_SHIFT (12U)
#define VAD_CTRL_CIC_OVLD_ERR_IE_SET(x) (((uint32_t)(x) << VAD_CTRL_CIC_OVLD_ERR_IE_SHIFT) & VAD_CTRL_CIC_OVLD_ERR_IE_MASK)
#define VAD_CTRL_CIC_OVLD_ERR_IE_GET(x) (((uint32_t)(x) & VAD_CTRL_CIC_OVLD_ERR_IE_MASK) >> VAD_CTRL_CIC_OVLD_ERR_IE_SHIFT)

/*
 * CIC_SAT_ERR_IE (RW)
 *
 * CIC saturation Interrupt Enable
 */
#define VAD_CTRL_CIC_SAT_ERR_IE_MASK (0x800U)
#define VAD_CTRL_CIC_SAT_ERR_IE_SHIFT (11U)
#define VAD_CTRL_CIC_SAT_ERR_IE_SET(x) (((uint32_t)(x) << VAD_CTRL_CIC_SAT_ERR_IE_SHIFT) & VAD_CTRL_CIC_SAT_ERR_IE_MASK)
#define VAD_CTRL_CIC_SAT_ERR_IE_GET(x) (((uint32_t)(x) & VAD_CTRL_CIC_SAT_ERR_IE_MASK) >> VAD_CTRL_CIC_SAT_ERR_IE_SHIFT)

/*
 * MEMBUF_DISABLE (RW)
 *
 * asserted to disable membuf
 */
#define VAD_CTRL_MEMBUF_DISABLE_MASK (0x200U)
#define VAD_CTRL_MEMBUF_DISABLE_SHIFT (9U)
#define VAD_CTRL_MEMBUF_DISABLE_SET(x) (((uint32_t)(x) << VAD_CTRL_MEMBUF_DISABLE_SHIFT) & VAD_CTRL_MEMBUF_DISABLE_MASK)
#define VAD_CTRL_MEMBUF_DISABLE_GET(x) (((uint32_t)(x) & VAD_CTRL_MEMBUF_DISABLE_MASK) >> VAD_CTRL_MEMBUF_DISABLE_SHIFT)

/*
 * FIFO_THRSH (RW)
 *
 * OFIFO threshold to generate ofifo_av (when fillings >= threshold) (fifo size: max 16 items, 16*32bits)
 */
#define VAD_CTRL_FIFO_THRSH_MASK (0x1E0U)
#define VAD_CTRL_FIFO_THRSH_SHIFT (5U)
#define VAD_CTRL_FIFO_THRSH_SET(x) (((uint32_t)(x) << VAD_CTRL_FIFO_THRSH_SHIFT) & VAD_CTRL_FIFO_THRSH_MASK)
#define VAD_CTRL_FIFO_THRSH_GET(x) (((uint32_t)(x) & VAD_CTRL_FIFO_THRSH_MASK) >> VAD_CTRL_FIFO_THRSH_SHIFT)

/*
 * PDM_CLK_DIV_BYPASS (RW)
 *
 * asserted to bypass the pdm clock divider
 */
#define VAD_CTRL_PDM_CLK_DIV_BYPASS_MASK (0x10U)
#define VAD_CTRL_PDM_CLK_DIV_BYPASS_SHIFT (4U)
#define VAD_CTRL_PDM_CLK_DIV_BYPASS_SET(x) (((uint32_t)(x) << VAD_CTRL_PDM_CLK_DIV_BYPASS_SHIFT) & VAD_CTRL_PDM_CLK_DIV_BYPASS_MASK)
#define VAD_CTRL_PDM_CLK_DIV_BYPASS_GET(x) (((uint32_t)(x) & VAD_CTRL_PDM_CLK_DIV_BYPASS_MASK) >> VAD_CTRL_PDM_CLK_DIV_BYPASS_SHIFT)

/*
 * PDM_CLK_OE (RW)
 *
 * pdm_clk_output_en
 */
#define VAD_CTRL_PDM_CLK_OE_MASK (0x8U)
#define VAD_CTRL_PDM_CLK_OE_SHIFT (3U)
#define VAD_CTRL_PDM_CLK_OE_SET(x) (((uint32_t)(x) << VAD_CTRL_PDM_CLK_OE_SHIFT) & VAD_CTRL_PDM_CLK_OE_MASK)
#define VAD_CTRL_PDM_CLK_OE_GET(x) (((uint32_t)(x) & VAD_CTRL_PDM_CLK_OE_MASK) >> VAD_CTRL_PDM_CLK_OE_SHIFT)

/*
 * CH_POL (RW)
 *
 * Asserted to select PDM_CLK high level captured, otherwise to select PDM_CLK low level captured.
 */
#define VAD_CTRL_CH_POL_MASK (0x6U)
#define VAD_CTRL_CH_POL_SHIFT (1U)
#define VAD_CTRL_CH_POL_SET(x) (((uint32_t)(x) << VAD_CTRL_CH_POL_SHIFT) & VAD_CTRL_CH_POL_MASK)
#define VAD_CTRL_CH_POL_GET(x) (((uint32_t)(x) & VAD_CTRL_CH_POL_MASK) >> VAD_CTRL_CH_POL_SHIFT)

/*
 * CHNUM (RW)
 *
 * the number of channels to be stored in buffer. Asserted to enable 2 channels.
 */
#define VAD_CTRL_CHNUM_MASK (0x1U)
#define VAD_CTRL_CHNUM_SHIFT (0U)
#define VAD_CTRL_CHNUM_SET(x) (((uint32_t)(x) << VAD_CTRL_CHNUM_SHIFT) & VAD_CTRL_CHNUM_MASK)
#define VAD_CTRL_CHNUM_GET(x) (((uint32_t)(x) & VAD_CTRL_CHNUM_MASK) >> VAD_CTRL_CHNUM_SHIFT)

/* Bitfield definition for register: FILTCTRL */
/*
 * DECRATIO (RW)
 *
 * the decimation ratio of iir after CIC -1
 * 2: means dec-by-3
 */
#define VAD_FILTCTRL_DECRATIO_MASK (0x700U)
#define VAD_FILTCTRL_DECRATIO_SHIFT (8U)
#define VAD_FILTCTRL_DECRATIO_SET(x) (((uint32_t)(x) << VAD_FILTCTRL_DECRATIO_SHIFT) & VAD_FILTCTRL_DECRATIO_MASK)
#define VAD_FILTCTRL_DECRATIO_GET(x) (((uint32_t)(x) & VAD_FILTCTRL_DECRATIO_MASK) >> VAD_FILTCTRL_DECRATIO_SHIFT)

/*
 * IIR_SLOT_EN (RW)
 *
 * IIR slot enable
 */
#define VAD_FILTCTRL_IIR_SLOT_EN_MASK (0xFFU)
#define VAD_FILTCTRL_IIR_SLOT_EN_SHIFT (0U)
#define VAD_FILTCTRL_IIR_SLOT_EN_SET(x) (((uint32_t)(x) << VAD_FILTCTRL_IIR_SLOT_EN_SHIFT) & VAD_FILTCTRL_IIR_SLOT_EN_MASK)
#define VAD_FILTCTRL_IIR_SLOT_EN_GET(x) (((uint32_t)(x) & VAD_FILTCTRL_IIR_SLOT_EN_MASK) >> VAD_FILTCTRL_IIR_SLOT_EN_SHIFT)

/* Bitfield definition for register: DEC_CTRL0 */
/*
 * NOISE_TOL (RW)
 *
 * the value of amplitude for noise determination when calculationg ZCR
 */
#define VAD_DEC_CTRL0_NOISE_TOL_MASK (0xFFFF0000UL)
#define VAD_DEC_CTRL0_NOISE_TOL_SHIFT (16U)
#define VAD_DEC_CTRL0_NOISE_TOL_SET(x) (((uint32_t)(x) << VAD_DEC_CTRL0_NOISE_TOL_SHIFT) & VAD_DEC_CTRL0_NOISE_TOL_MASK)
#define VAD_DEC_CTRL0_NOISE_TOL_GET(x) (((uint32_t)(x) & VAD_DEC_CTRL0_NOISE_TOL_MASK) >> VAD_DEC_CTRL0_NOISE_TOL_SHIFT)

/*
 * BLK_CFG (RW)
 *
 * asserted to have 3 sub-blocks, otherwise to have 2 sub-blocks
 */
#define VAD_DEC_CTRL0_BLK_CFG_MASK (0x200U)
#define VAD_DEC_CTRL0_BLK_CFG_SHIFT (9U)
#define VAD_DEC_CTRL0_BLK_CFG_SET(x) (((uint32_t)(x) << VAD_DEC_CTRL0_BLK_CFG_SHIFT) & VAD_DEC_CTRL0_BLK_CFG_MASK)
#define VAD_DEC_CTRL0_BLK_CFG_GET(x) (((uint32_t)(x) & VAD_DEC_CTRL0_BLK_CFG_MASK) >> VAD_DEC_CTRL0_BLK_CFG_SHIFT)

/*
 * SUBBLK_LEN (RW)
 *
 * length of sub-block
 */
#define VAD_DEC_CTRL0_SUBBLK_LEN_MASK (0x1FFU)
#define VAD_DEC_CTRL0_SUBBLK_LEN_SHIFT (0U)
#define VAD_DEC_CTRL0_SUBBLK_LEN_SET(x) (((uint32_t)(x) << VAD_DEC_CTRL0_SUBBLK_LEN_SHIFT) & VAD_DEC_CTRL0_SUBBLK_LEN_MASK)
#define VAD_DEC_CTRL0_SUBBLK_LEN_GET(x) (((uint32_t)(x) & VAD_DEC_CTRL0_SUBBLK_LEN_MASK) >> VAD_DEC_CTRL0_SUBBLK_LEN_SHIFT)

/* Bitfield definition for register: DEC_CTRL1 */
/*
 * ZCR_HIGH (RW)
 *
 * ZCR high limit
 */
#define VAD_DEC_CTRL1_ZCR_HIGH_MASK (0x3FF800UL)
#define VAD_DEC_CTRL1_ZCR_HIGH_SHIFT (11U)
#define VAD_DEC_CTRL1_ZCR_HIGH_SET(x) (((uint32_t)(x) << VAD_DEC_CTRL1_ZCR_HIGH_SHIFT) & VAD_DEC_CTRL1_ZCR_HIGH_MASK)
#define VAD_DEC_CTRL1_ZCR_HIGH_GET(x) (((uint32_t)(x) & VAD_DEC_CTRL1_ZCR_HIGH_MASK) >> VAD_DEC_CTRL1_ZCR_HIGH_SHIFT)

/*
 * ZCR_LOW (RW)
 *
 * ZCR low limit
 */
#define VAD_DEC_CTRL1_ZCR_LOW_MASK (0x7FFU)
#define VAD_DEC_CTRL1_ZCR_LOW_SHIFT (0U)
#define VAD_DEC_CTRL1_ZCR_LOW_SET(x) (((uint32_t)(x) << VAD_DEC_CTRL1_ZCR_LOW_SHIFT) & VAD_DEC_CTRL1_ZCR_LOW_MASK)
#define VAD_DEC_CTRL1_ZCR_LOW_GET(x) (((uint32_t)(x) & VAD_DEC_CTRL1_ZCR_LOW_MASK) >> VAD_DEC_CTRL1_ZCR_LOW_SHIFT)

/* Bitfield definition for register: DEC_CTRL2 */
/*
 * AMP_HIGH (RW)
 *
 * amplitude high limit
 */
#define VAD_DEC_CTRL2_AMP_HIGH_MASK (0xFFFF0000UL)
#define VAD_DEC_CTRL2_AMP_HIGH_SHIFT (16U)
#define VAD_DEC_CTRL2_AMP_HIGH_SET(x) (((uint32_t)(x) << VAD_DEC_CTRL2_AMP_HIGH_SHIFT) & VAD_DEC_CTRL2_AMP_HIGH_MASK)
#define VAD_DEC_CTRL2_AMP_HIGH_GET(x) (((uint32_t)(x) & VAD_DEC_CTRL2_AMP_HIGH_MASK) >> VAD_DEC_CTRL2_AMP_HIGH_SHIFT)

/*
 * AMP_LOW (RW)
 *
 * amplitude low limit
 */
#define VAD_DEC_CTRL2_AMP_LOW_MASK (0xFFFFU)
#define VAD_DEC_CTRL2_AMP_LOW_SHIFT (0U)
#define VAD_DEC_CTRL2_AMP_LOW_SET(x) (((uint32_t)(x) << VAD_DEC_CTRL2_AMP_LOW_SHIFT) & VAD_DEC_CTRL2_AMP_LOW_MASK)
#define VAD_DEC_CTRL2_AMP_LOW_GET(x) (((uint32_t)(x) & VAD_DEC_CTRL2_AMP_LOW_MASK) >> VAD_DEC_CTRL2_AMP_LOW_SHIFT)

/* Bitfield definition for register: ST */
/*
 * VAD (W1C)
 *
 * VAD event found
 */
#define VAD_ST_VAD_MASK (0x80U)
#define VAD_ST_VAD_SHIFT (7U)
#define VAD_ST_VAD_SET(x) (((uint32_t)(x) << VAD_ST_VAD_SHIFT) & VAD_ST_VAD_MASK)
#define VAD_ST_VAD_GET(x) (((uint32_t)(x) & VAD_ST_VAD_MASK) >> VAD_ST_VAD_SHIFT)

/*
 * OFIFO_AV (RO)
 *
 * OFIFO data available
 */
#define VAD_ST_OFIFO_AV_MASK (0x40U)
#define VAD_ST_OFIFO_AV_SHIFT (6U)
#define VAD_ST_OFIFO_AV_GET(x) (((uint32_t)(x) & VAD_ST_OFIFO_AV_MASK) >> VAD_ST_OFIFO_AV_SHIFT)

/*
 * MEMBUF_EMPTY (W1C)
 *
 * Buf empty
 */
#define VAD_ST_MEMBUF_EMPTY_MASK (0x20U)
#define VAD_ST_MEMBUF_EMPTY_SHIFT (5U)
#define VAD_ST_MEMBUF_EMPTY_SET(x) (((uint32_t)(x) << VAD_ST_MEMBUF_EMPTY_SHIFT) & VAD_ST_MEMBUF_EMPTY_MASK)
#define VAD_ST_MEMBUF_EMPTY_GET(x) (((uint32_t)(x) & VAD_ST_MEMBUF_EMPTY_MASK) >> VAD_ST_MEMBUF_EMPTY_SHIFT)

/*
 * OFIFO_OVFL (W1C)
 *
 * OFIFO overflow
 */
#define VAD_ST_OFIFO_OVFL_MASK (0x10U)
#define VAD_ST_OFIFO_OVFL_SHIFT (4U)
#define VAD_ST_OFIFO_OVFL_SET(x) (((uint32_t)(x) << VAD_ST_OFIFO_OVFL_SHIFT) & VAD_ST_OFIFO_OVFL_MASK)
#define VAD_ST_OFIFO_OVFL_GET(x) (((uint32_t)(x) & VAD_ST_OFIFO_OVFL_MASK) >> VAD_ST_OFIFO_OVFL_SHIFT)

/*
 * IIR_OVLD (W1C)
 *
 * IIR overloading
 */
#define VAD_ST_IIR_OVLD_MASK (0x8U)
#define VAD_ST_IIR_OVLD_SHIFT (3U)
#define VAD_ST_IIR_OVLD_SET(x) (((uint32_t)(x) << VAD_ST_IIR_OVLD_SHIFT) & VAD_ST_IIR_OVLD_MASK)
#define VAD_ST_IIR_OVLD_GET(x) (((uint32_t)(x) & VAD_ST_IIR_OVLD_MASK) >> VAD_ST_IIR_OVLD_SHIFT)

/*
 * IIR_OVFL (W1C)
 *
 * IIR oberflow
 */
#define VAD_ST_IIR_OVFL_MASK (0x4U)
#define VAD_ST_IIR_OVFL_SHIFT (2U)
#define VAD_ST_IIR_OVFL_SET(x) (((uint32_t)(x) << VAD_ST_IIR_OVFL_SHIFT) & VAD_ST_IIR_OVFL_MASK)
#define VAD_ST_IIR_OVFL_GET(x) (((uint32_t)(x) & VAD_ST_IIR_OVFL_MASK) >> VAD_ST_IIR_OVFL_SHIFT)

/*
 * CIC_OVLD_ERR (W1C)
 *
 * CIC overload
 */
#define VAD_ST_CIC_OVLD_ERR_MASK (0x2U)
#define VAD_ST_CIC_OVLD_ERR_SHIFT (1U)
#define VAD_ST_CIC_OVLD_ERR_SET(x) (((uint32_t)(x) << VAD_ST_CIC_OVLD_ERR_SHIFT) & VAD_ST_CIC_OVLD_ERR_MASK)
#define VAD_ST_CIC_OVLD_ERR_GET(x) (((uint32_t)(x) & VAD_ST_CIC_OVLD_ERR_MASK) >> VAD_ST_CIC_OVLD_ERR_SHIFT)

/*
 * CIC_SAT_ERR (W1C)
 *
 * CIC saturation
 */
#define VAD_ST_CIC_SAT_ERR_MASK (0x1U)
#define VAD_ST_CIC_SAT_ERR_SHIFT (0U)
#define VAD_ST_CIC_SAT_ERR_SET(x) (((uint32_t)(x) << VAD_ST_CIC_SAT_ERR_SHIFT) & VAD_ST_CIC_SAT_ERR_MASK)
#define VAD_ST_CIC_SAT_ERR_GET(x) (((uint32_t)(x) & VAD_ST_CIC_SAT_ERR_MASK) >> VAD_ST_CIC_SAT_ERR_SHIFT)

/* Bitfield definition for register: OFIFO */
/*
 * D (RW)
 *
 * The PCM data.
 * When there is only one channel, the samples are from Ch0, and the 2 samples in the 32-bits are: bit [31:16]: the samples earlier in time ([T-1]). Bit [15:0]: the samples later in time ([T]).
 * When there is two channels, the samples in the 32-bits are: bit [31:16]: the samples belong to Ch 1 (when ch_pol[1:0]==2, the data is captured at the positive part of the pdm clk). bit [15:0]: the samples belong to Ch 0 (when ch_pol[1:0]==2, the data is captured at the negtive part of the pdm clk).
 */
#define VAD_OFIFO_D_MASK (0xFFFFFFFFUL)
#define VAD_OFIFO_D_SHIFT (0U)
#define VAD_OFIFO_D_SET(x) (((uint32_t)(x) << VAD_OFIFO_D_SHIFT) & VAD_OFIFO_D_MASK)
#define VAD_OFIFO_D_GET(x) (((uint32_t)(x) & VAD_OFIFO_D_MASK) >> VAD_OFIFO_D_SHIFT)

/* Bitfield definition for register: RUN */
/*
 * SFTRST (RW)
 *
 * software reset. Self-clear
 */
#define VAD_RUN_SFTRST_MASK (0x2U)
#define VAD_RUN_SFTRST_SHIFT (1U)
#define VAD_RUN_SFTRST_SET(x) (((uint32_t)(x) << VAD_RUN_SFTRST_SHIFT) & VAD_RUN_SFTRST_MASK)
#define VAD_RUN_SFTRST_GET(x) (((uint32_t)(x) & VAD_RUN_SFTRST_MASK) >> VAD_RUN_SFTRST_SHIFT)

/*
 * VAD_EN (RW)
 *
 * module enable
 */
#define VAD_RUN_VAD_EN_MASK (0x1U)
#define VAD_RUN_VAD_EN_SHIFT (0U)
#define VAD_RUN_VAD_EN_SET(x) (((uint32_t)(x) << VAD_RUN_VAD_EN_SHIFT) & VAD_RUN_VAD_EN_MASK)
#define VAD_RUN_VAD_EN_GET(x) (((uint32_t)(x) & VAD_RUN_VAD_EN_MASK) >> VAD_RUN_VAD_EN_SHIFT)

/* Bitfield definition for register: OFIFO_CTRL */
/*
 * EN (RW)
 *
 * Asserted to enable OFIFO
 */
#define VAD_OFIFO_CTRL_EN_MASK (0x1U)
#define VAD_OFIFO_CTRL_EN_SHIFT (0U)
#define VAD_OFIFO_CTRL_EN_SET(x) (((uint32_t)(x) << VAD_OFIFO_CTRL_EN_SHIFT) & VAD_OFIFO_CTRL_EN_MASK)
#define VAD_OFIFO_CTRL_EN_GET(x) (((uint32_t)(x) & VAD_OFIFO_CTRL_EN_MASK) >> VAD_OFIFO_CTRL_EN_SHIFT)

/* Bitfield definition for register: CIC_CFG */
/*
 * POST_SCALE (RW)
 *
 * the shift value after CIC results.
 */
#define VAD_CIC_CFG_POST_SCALE_MASK (0xFC00U)
#define VAD_CIC_CFG_POST_SCALE_SHIFT (10U)
#define VAD_CIC_CFG_POST_SCALE_SET(x) (((uint32_t)(x) << VAD_CIC_CFG_POST_SCALE_SHIFT) & VAD_CIC_CFG_POST_SCALE_MASK)
#define VAD_CIC_CFG_POST_SCALE_GET(x) (((uint32_t)(x) & VAD_CIC_CFG_POST_SCALE_MASK) >> VAD_CIC_CFG_POST_SCALE_SHIFT)

/* Bitfield definition for register array: COEF */
/*
 * VAL (RO)
 *
 * The current detected short time energy
 */
#define VAD_COEF_VAL_MASK (0xFFFFFFFFUL)
#define VAD_COEF_VAL_SHIFT (0U)
#define VAD_COEF_VAL_GET(x) (((uint32_t)(x) & VAD_COEF_VAL_MASK) >> VAD_COEF_VAL_SHIFT)



/* COEF register group index macro definition */
#define VAD_COEF_STE_ACT (0UL)


#endif /* HPM_VAD_H */
