/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_PDM_H
#define HPM_PDM_H

typedef struct {
    __RW uint32_t CTRL;                        /* 0x0: Control Register */
    __RW uint32_t CH_CTRL;                     /* 0x4: Channel Control Register */
    __W  uint32_t ST;                          /* 0x8: Status Register */
    __RW uint32_t CH_CFG;                      /* 0xC: Channel Configuration Register */
    __RW uint32_t CIC_CFG;                     /* 0x10: CIC configuration register */
    __RW uint32_t CTRL_INBUF;                  /* 0x14: In Buf Control Register */
    __RW uint32_t CTRL_FILT0;                  /* 0x18: Filter 0 Control Register */
    __RW uint32_t CTRL_FILT1;                  /* 0x1C: Filter 1 Control Register */
    __RW uint32_t RUN;                         /* 0x20: Run Register */
    __RW uint32_t MEMADDR;                     /* 0x24: Memory Access Address */
    __RW uint32_t MEMDATA;                     /* 0x28: Memory Access Data */
    __RW uint32_t HPF_MA;                      /* 0x2C: HPF A Coef Register */
    __RW uint32_t HPF_B;                       /* 0x30: HPF B Coef Register */
} PDM_Type;


/* Bitfield definition for register: CTRL */
/*
 * SFTRST (RW)
 *
 * software reset the module. Self-clear.
 */
#define PDM_CTRL_SFTRST_MASK (0x80000000UL)
#define PDM_CTRL_SFTRST_SHIFT (31U)
#define PDM_CTRL_SFTRST_SET(x) (((uint32_t)(x) << PDM_CTRL_SFTRST_SHIFT) & PDM_CTRL_SFTRST_MASK)
#define PDM_CTRL_SFTRST_GET(x) (((uint32_t)(x) & PDM_CTRL_SFTRST_MASK) >> PDM_CTRL_SFTRST_SHIFT)

/*
 * SOF_FEDGE (RW)
 *
 * asserted if the falling edge of the ref fclk from DAO is the start of a new frame. This is used to to align DAO feedback signal.
 */
#define PDM_CTRL_SOF_FEDGE_MASK (0x800000UL)
#define PDM_CTRL_SOF_FEDGE_SHIFT (23U)
#define PDM_CTRL_SOF_FEDGE_SET(x) (((uint32_t)(x) << PDM_CTRL_SOF_FEDGE_SHIFT) & PDM_CTRL_SOF_FEDGE_MASK)
#define PDM_CTRL_SOF_FEDGE_GET(x) (((uint32_t)(x) & PDM_CTRL_SOF_FEDGE_MASK) >> PDM_CTRL_SOF_FEDGE_SHIFT)

/*
 * USE_COEF_RAM (RW)
 *
 * Asserted to use Coef RAM instead of Coef ROM
 */
#define PDM_CTRL_USE_COEF_RAM_MASK (0x100000UL)
#define PDM_CTRL_USE_COEF_RAM_SHIFT (20U)
#define PDM_CTRL_USE_COEF_RAM_SET(x) (((uint32_t)(x) << PDM_CTRL_USE_COEF_RAM_SHIFT) & PDM_CTRL_USE_COEF_RAM_MASK)
#define PDM_CTRL_USE_COEF_RAM_GET(x) (((uint32_t)(x) & PDM_CTRL_USE_COEF_RAM_MASK) >> PDM_CTRL_USE_COEF_RAM_SHIFT)

/*
 * FILT_CRX_ERR_IE (RW)
 *
 * data accessed out of boundary error interruput enable. The error happens when the module cannot calculate the enough number of data in time.
 */
#define PDM_CTRL_FILT_CRX_ERR_IE_MASK (0x80000UL)
#define PDM_CTRL_FILT_CRX_ERR_IE_SHIFT (19U)
#define PDM_CTRL_FILT_CRX_ERR_IE_SET(x) (((uint32_t)(x) << PDM_CTRL_FILT_CRX_ERR_IE_SHIFT) & PDM_CTRL_FILT_CRX_ERR_IE_MASK)
#define PDM_CTRL_FILT_CRX_ERR_IE_GET(x) (((uint32_t)(x) & PDM_CTRL_FILT_CRX_ERR_IE_MASK) >> PDM_CTRL_FILT_CRX_ERR_IE_SHIFT)

/*
 * OFIFO_OVFL_ERR_IE (RW)
 *
 * output fifo overflow error interrupt enable
 */
#define PDM_CTRL_OFIFO_OVFL_ERR_IE_MASK (0x40000UL)
#define PDM_CTRL_OFIFO_OVFL_ERR_IE_SHIFT (18U)
#define PDM_CTRL_OFIFO_OVFL_ERR_IE_SET(x) (((uint32_t)(x) << PDM_CTRL_OFIFO_OVFL_ERR_IE_SHIFT) & PDM_CTRL_OFIFO_OVFL_ERR_IE_MASK)
#define PDM_CTRL_OFIFO_OVFL_ERR_IE_GET(x) (((uint32_t)(x) & PDM_CTRL_OFIFO_OVFL_ERR_IE_MASK) >> PDM_CTRL_OFIFO_OVFL_ERR_IE_SHIFT)

/*
 * CIC_OVLD_ERR_IE (RW)
 *
 * CIC overload error interrupt enable
 */
#define PDM_CTRL_CIC_OVLD_ERR_IE_MASK (0x20000UL)
#define PDM_CTRL_CIC_OVLD_ERR_IE_SHIFT (17U)
#define PDM_CTRL_CIC_OVLD_ERR_IE_SET(x) (((uint32_t)(x) << PDM_CTRL_CIC_OVLD_ERR_IE_SHIFT) & PDM_CTRL_CIC_OVLD_ERR_IE_MASK)
#define PDM_CTRL_CIC_OVLD_ERR_IE_GET(x) (((uint32_t)(x) & PDM_CTRL_CIC_OVLD_ERR_IE_MASK) >> PDM_CTRL_CIC_OVLD_ERR_IE_SHIFT)

/*
 * CIC_SAT_ERR_IE (RW)
 *
 * Error interrupt enable
 * This bit controls the generation of an interrupt when an error condition  (CIC saturation) occurs.
 * 0: Error interrupt is masked
 * 1: Error interrupt is enabled
 */
#define PDM_CTRL_CIC_SAT_ERR_IE_MASK (0x10000UL)
#define PDM_CTRL_CIC_SAT_ERR_IE_SHIFT (16U)
#define PDM_CTRL_CIC_SAT_ERR_IE_SET(x) (((uint32_t)(x) << PDM_CTRL_CIC_SAT_ERR_IE_SHIFT) & PDM_CTRL_CIC_SAT_ERR_IE_MASK)
#define PDM_CTRL_CIC_SAT_ERR_IE_GET(x) (((uint32_t)(x) & PDM_CTRL_CIC_SAT_ERR_IE_MASK) >> PDM_CTRL_CIC_SAT_ERR_IE_SHIFT)

/*
 * DEC_AFT_CIC (RW)
 *
 * decimation rate after CIC. Now it is forced to be 3.
 */
#define PDM_CTRL_DEC_AFT_CIC_MASK (0xF000U)
#define PDM_CTRL_DEC_AFT_CIC_SHIFT (12U)
#define PDM_CTRL_DEC_AFT_CIC_SET(x) (((uint32_t)(x) << PDM_CTRL_DEC_AFT_CIC_SHIFT) & PDM_CTRL_DEC_AFT_CIC_MASK)
#define PDM_CTRL_DEC_AFT_CIC_GET(x) (((uint32_t)(x) & PDM_CTRL_DEC_AFT_CIC_MASK) >> PDM_CTRL_DEC_AFT_CIC_SHIFT)

/*
 * CAPT_DLY (RW)
 *
 * Capture cycle delay>=0, should be less than PDM_CLK_HFDIV
 */
#define PDM_CTRL_CAPT_DLY_MASK (0x780U)
#define PDM_CTRL_CAPT_DLY_SHIFT (7U)
#define PDM_CTRL_CAPT_DLY_SET(x) (((uint32_t)(x) << PDM_CTRL_CAPT_DLY_SHIFT) & PDM_CTRL_CAPT_DLY_MASK)
#define PDM_CTRL_CAPT_DLY_GET(x) (((uint32_t)(x) & PDM_CTRL_CAPT_DLY_MASK) >> PDM_CTRL_CAPT_DLY_SHIFT)

/*
 * PDM_CLK_HFDIV (RW)
 *
 * The clock divider will work at least 4.
 * 0: div-by-2,
 * 1: div-by-4
 * . . .
 * n: div-by-2*(n+1)
 */
#define PDM_CTRL_PDM_CLK_HFDIV_MASK (0x78U)
#define PDM_CTRL_PDM_CLK_HFDIV_SHIFT (3U)
#define PDM_CTRL_PDM_CLK_HFDIV_SET(x) (((uint32_t)(x) << PDM_CTRL_PDM_CLK_HFDIV_SHIFT) & PDM_CTRL_PDM_CLK_HFDIV_MASK)
#define PDM_CTRL_PDM_CLK_HFDIV_GET(x) (((uint32_t)(x) & PDM_CTRL_PDM_CLK_HFDIV_MASK) >> PDM_CTRL_PDM_CLK_HFDIV_SHIFT)

/*
 * PDM_CLK_DIV_BYPASS (RW)
 *
 * asserted to bypass the pdm clock divider
 */
#define PDM_CTRL_PDM_CLK_DIV_BYPASS_MASK (0x4U)
#define PDM_CTRL_PDM_CLK_DIV_BYPASS_SHIFT (2U)
#define PDM_CTRL_PDM_CLK_DIV_BYPASS_SET(x) (((uint32_t)(x) << PDM_CTRL_PDM_CLK_DIV_BYPASS_SHIFT) & PDM_CTRL_PDM_CLK_DIV_BYPASS_MASK)
#define PDM_CTRL_PDM_CLK_DIV_BYPASS_GET(x) (((uint32_t)(x) & PDM_CTRL_PDM_CLK_DIV_BYPASS_MASK) >> PDM_CTRL_PDM_CLK_DIV_BYPASS_SHIFT)

/*
 * PDM_CLK_OE (RW)
 *
 * pdm_clk_output_en
 */
#define PDM_CTRL_PDM_CLK_OE_MASK (0x2U)
#define PDM_CTRL_PDM_CLK_OE_SHIFT (1U)
#define PDM_CTRL_PDM_CLK_OE_SET(x) (((uint32_t)(x) << PDM_CTRL_PDM_CLK_OE_SHIFT) & PDM_CTRL_PDM_CLK_OE_MASK)
#define PDM_CTRL_PDM_CLK_OE_GET(x) (((uint32_t)(x) & PDM_CTRL_PDM_CLK_OE_MASK) >> PDM_CTRL_PDM_CLK_OE_SHIFT)

/*
 * HPF_EN (RW)
 *
 * pdm high pass filter enable. This order-1 HPF only applies to the PDM mic data.
 */
#define PDM_CTRL_HPF_EN_MASK (0x1U)
#define PDM_CTRL_HPF_EN_SHIFT (0U)
#define PDM_CTRL_HPF_EN_SET(x) (((uint32_t)(x) << PDM_CTRL_HPF_EN_SHIFT) & PDM_CTRL_HPF_EN_MASK)
#define PDM_CTRL_HPF_EN_GET(x) (((uint32_t)(x) & PDM_CTRL_HPF_EN_MASK) >> PDM_CTRL_HPF_EN_SHIFT)

/* Bitfield definition for register: CH_CTRL */
/*
 * CH_POL (RW)
 *
 * Asserted to select PDM_CLK high level captured, otherwise to select PDM_CLK low level captured.
 */
#define PDM_CH_CTRL_CH_POL_MASK (0xFF0000UL)
#define PDM_CH_CTRL_CH_POL_SHIFT (16U)
#define PDM_CH_CTRL_CH_POL_SET(x) (((uint32_t)(x) << PDM_CH_CTRL_CH_POL_SHIFT) & PDM_CH_CTRL_CH_POL_MASK)
#define PDM_CH_CTRL_CH_POL_GET(x) (((uint32_t)(x) & PDM_CH_CTRL_CH_POL_MASK) >> PDM_CH_CTRL_CH_POL_SHIFT)

/*
 * CH_EN (RW)
 *
 * Asserted to enable the channel.
 * Ch8 & 9 are refs.
 * Ch0-7 are pdm mics.
 */
#define PDM_CH_CTRL_CH_EN_MASK (0x3FFU)
#define PDM_CH_CTRL_CH_EN_SHIFT (0U)
#define PDM_CH_CTRL_CH_EN_SET(x) (((uint32_t)(x) << PDM_CH_CTRL_CH_EN_SHIFT) & PDM_CH_CTRL_CH_EN_MASK)
#define PDM_CH_CTRL_CH_EN_GET(x) (((uint32_t)(x) & PDM_CH_CTRL_CH_EN_MASK) >> PDM_CH_CTRL_CH_EN_SHIFT)

/* Bitfield definition for register: ST */
/*
 * FILT_CRX_ERR (W1C)
 *
 * data accessed out of boundary error
 */
#define PDM_ST_FILT_CRX_ERR_MASK (0x8U)
#define PDM_ST_FILT_CRX_ERR_SHIFT (3U)
#define PDM_ST_FILT_CRX_ERR_SET(x) (((uint32_t)(x) << PDM_ST_FILT_CRX_ERR_SHIFT) & PDM_ST_FILT_CRX_ERR_MASK)
#define PDM_ST_FILT_CRX_ERR_GET(x) (((uint32_t)(x) & PDM_ST_FILT_CRX_ERR_MASK) >> PDM_ST_FILT_CRX_ERR_SHIFT)

/*
 * OFIFO_OVFL_ERR (W1C)
 *
 * output fifo overflow error. The reason may be sampling frequency mismatch, either fast or slow.
 */
#define PDM_ST_OFIFO_OVFL_ERR_MASK (0x4U)
#define PDM_ST_OFIFO_OVFL_ERR_SHIFT (2U)
#define PDM_ST_OFIFO_OVFL_ERR_SET(x) (((uint32_t)(x) << PDM_ST_OFIFO_OVFL_ERR_SHIFT) & PDM_ST_OFIFO_OVFL_ERR_MASK)
#define PDM_ST_OFIFO_OVFL_ERR_GET(x) (((uint32_t)(x) & PDM_ST_OFIFO_OVFL_ERR_MASK) >> PDM_ST_OFIFO_OVFL_ERR_SHIFT)

/*
 * CIC_OVLD_ERR (W1C)
 *
 * CIC overload error. write 1 clear
 */
#define PDM_ST_CIC_OVLD_ERR_MASK (0x2U)
#define PDM_ST_CIC_OVLD_ERR_SHIFT (1U)
#define PDM_ST_CIC_OVLD_ERR_SET(x) (((uint32_t)(x) << PDM_ST_CIC_OVLD_ERR_SHIFT) & PDM_ST_CIC_OVLD_ERR_MASK)
#define PDM_ST_CIC_OVLD_ERR_GET(x) (((uint32_t)(x) & PDM_ST_CIC_OVLD_ERR_MASK) >> PDM_ST_CIC_OVLD_ERR_SHIFT)

/*
 * CIC_SAT_ERR (W1C)
 *
 * CIC saturation. Write 1 clear
 */
#define PDM_ST_CIC_SAT_ERR_MASK (0x1U)
#define PDM_ST_CIC_SAT_ERR_SHIFT (0U)
#define PDM_ST_CIC_SAT_ERR_SET(x) (((uint32_t)(x) << PDM_ST_CIC_SAT_ERR_SHIFT) & PDM_ST_CIC_SAT_ERR_MASK)
#define PDM_ST_CIC_SAT_ERR_GET(x) (((uint32_t)(x) & PDM_ST_CIC_SAT_ERR_MASK) >> PDM_ST_CIC_SAT_ERR_SHIFT)

/* Bitfield definition for register: CH_CFG */
/*
 * CH9_TYPE (RW)
 *
 */
#define PDM_CH_CFG_CH9_TYPE_MASK (0xC0000UL)
#define PDM_CH_CFG_CH9_TYPE_SHIFT (18U)
#define PDM_CH_CFG_CH9_TYPE_SET(x) (((uint32_t)(x) << PDM_CH_CFG_CH9_TYPE_SHIFT) & PDM_CH_CFG_CH9_TYPE_MASK)
#define PDM_CH_CFG_CH9_TYPE_GET(x) (((uint32_t)(x) & PDM_CH_CFG_CH9_TYPE_MASK) >> PDM_CH_CFG_CH9_TYPE_SHIFT)

/*
 * CH8_TYPE (RW)
 *
 */
#define PDM_CH_CFG_CH8_TYPE_MASK (0x30000UL)
#define PDM_CH_CFG_CH8_TYPE_SHIFT (16U)
#define PDM_CH_CFG_CH8_TYPE_SET(x) (((uint32_t)(x) << PDM_CH_CFG_CH8_TYPE_SHIFT) & PDM_CH_CFG_CH8_TYPE_MASK)
#define PDM_CH_CFG_CH8_TYPE_GET(x) (((uint32_t)(x) & PDM_CH_CFG_CH8_TYPE_MASK) >> PDM_CH_CFG_CH8_TYPE_SHIFT)

/*
 * CH7_TYPE (RW)
 *
 */
#define PDM_CH_CFG_CH7_TYPE_MASK (0xC000U)
#define PDM_CH_CFG_CH7_TYPE_SHIFT (14U)
#define PDM_CH_CFG_CH7_TYPE_SET(x) (((uint32_t)(x) << PDM_CH_CFG_CH7_TYPE_SHIFT) & PDM_CH_CFG_CH7_TYPE_MASK)
#define PDM_CH_CFG_CH7_TYPE_GET(x) (((uint32_t)(x) & PDM_CH_CFG_CH7_TYPE_MASK) >> PDM_CH_CFG_CH7_TYPE_SHIFT)

/*
 * CH6_TYPE (RW)
 *
 */
#define PDM_CH_CFG_CH6_TYPE_MASK (0x3000U)
#define PDM_CH_CFG_CH6_TYPE_SHIFT (12U)
#define PDM_CH_CFG_CH6_TYPE_SET(x) (((uint32_t)(x) << PDM_CH_CFG_CH6_TYPE_SHIFT) & PDM_CH_CFG_CH6_TYPE_MASK)
#define PDM_CH_CFG_CH6_TYPE_GET(x) (((uint32_t)(x) & PDM_CH_CFG_CH6_TYPE_MASK) >> PDM_CH_CFG_CH6_TYPE_SHIFT)

/*
 * CH5_TYPE (RW)
 *
 */
#define PDM_CH_CFG_CH5_TYPE_MASK (0xC00U)
#define PDM_CH_CFG_CH5_TYPE_SHIFT (10U)
#define PDM_CH_CFG_CH5_TYPE_SET(x) (((uint32_t)(x) << PDM_CH_CFG_CH5_TYPE_SHIFT) & PDM_CH_CFG_CH5_TYPE_MASK)
#define PDM_CH_CFG_CH5_TYPE_GET(x) (((uint32_t)(x) & PDM_CH_CFG_CH5_TYPE_MASK) >> PDM_CH_CFG_CH5_TYPE_SHIFT)

/*
 * CH4_TYPE (RW)
 *
 */
#define PDM_CH_CFG_CH4_TYPE_MASK (0x300U)
#define PDM_CH_CFG_CH4_TYPE_SHIFT (8U)
#define PDM_CH_CFG_CH4_TYPE_SET(x) (((uint32_t)(x) << PDM_CH_CFG_CH4_TYPE_SHIFT) & PDM_CH_CFG_CH4_TYPE_MASK)
#define PDM_CH_CFG_CH4_TYPE_GET(x) (((uint32_t)(x) & PDM_CH_CFG_CH4_TYPE_MASK) >> PDM_CH_CFG_CH4_TYPE_SHIFT)

/*
 * CH3_TYPE (RW)
 *
 */
#define PDM_CH_CFG_CH3_TYPE_MASK (0xC0U)
#define PDM_CH_CFG_CH3_TYPE_SHIFT (6U)
#define PDM_CH_CFG_CH3_TYPE_SET(x) (((uint32_t)(x) << PDM_CH_CFG_CH3_TYPE_SHIFT) & PDM_CH_CFG_CH3_TYPE_MASK)
#define PDM_CH_CFG_CH3_TYPE_GET(x) (((uint32_t)(x) & PDM_CH_CFG_CH3_TYPE_MASK) >> PDM_CH_CFG_CH3_TYPE_SHIFT)

/*
 * CH2_TYPE (RW)
 *
 */
#define PDM_CH_CFG_CH2_TYPE_MASK (0x30U)
#define PDM_CH_CFG_CH2_TYPE_SHIFT (4U)
#define PDM_CH_CFG_CH2_TYPE_SET(x) (((uint32_t)(x) << PDM_CH_CFG_CH2_TYPE_SHIFT) & PDM_CH_CFG_CH2_TYPE_MASK)
#define PDM_CH_CFG_CH2_TYPE_GET(x) (((uint32_t)(x) & PDM_CH_CFG_CH2_TYPE_MASK) >> PDM_CH_CFG_CH2_TYPE_SHIFT)

/*
 * CH1_TYPE (RW)
 *
 */
#define PDM_CH_CFG_CH1_TYPE_MASK (0xCU)
#define PDM_CH_CFG_CH1_TYPE_SHIFT (2U)
#define PDM_CH_CFG_CH1_TYPE_SET(x) (((uint32_t)(x) << PDM_CH_CFG_CH1_TYPE_SHIFT) & PDM_CH_CFG_CH1_TYPE_MASK)
#define PDM_CH_CFG_CH1_TYPE_GET(x) (((uint32_t)(x) & PDM_CH_CFG_CH1_TYPE_MASK) >> PDM_CH_CFG_CH1_TYPE_SHIFT)

/*
 * CH0_TYPE (RW)
 *
 * Type of Channel 0
 * 2'b00: dec-by-3 wiith filter type0 (CIC Compenstation+norm filter)
 * 2'b01: dec-by-3 with filter type 1 (No CIC compenstation, only norm filter)
 */
#define PDM_CH_CFG_CH0_TYPE_MASK (0x3U)
#define PDM_CH_CFG_CH0_TYPE_SHIFT (0U)
#define PDM_CH_CFG_CH0_TYPE_SET(x) (((uint32_t)(x) << PDM_CH_CFG_CH0_TYPE_SHIFT) & PDM_CH_CFG_CH0_TYPE_MASK)
#define PDM_CH_CFG_CH0_TYPE_GET(x) (((uint32_t)(x) & PDM_CH_CFG_CH0_TYPE_MASK) >> PDM_CH_CFG_CH0_TYPE_SHIFT)

/* Bitfield definition for register: CIC_CFG */
/*
 * POST_SCALE (RW)
 *
 * the shift value after CIC results.
 */
#define PDM_CIC_CFG_POST_SCALE_MASK (0xFC00U)
#define PDM_CIC_CFG_POST_SCALE_SHIFT (10U)
#define PDM_CIC_CFG_POST_SCALE_SET(x) (((uint32_t)(x) << PDM_CIC_CFG_POST_SCALE_SHIFT) & PDM_CIC_CFG_POST_SCALE_MASK)
#define PDM_CIC_CFG_POST_SCALE_GET(x) (((uint32_t)(x) & PDM_CIC_CFG_POST_SCALE_MASK) >> PDM_CIC_CFG_POST_SCALE_SHIFT)

/*
 * SGD (RW)
 *
 * Sigma_delta_order[1:0]
 * 2'b00: 7
 * 2'b01: 6
 * 2'b10: 5
 * Others: unused
 */
#define PDM_CIC_CFG_SGD_MASK (0x300U)
#define PDM_CIC_CFG_SGD_SHIFT (8U)
#define PDM_CIC_CFG_SGD_SET(x) (((uint32_t)(x) << PDM_CIC_CFG_SGD_SHIFT) & PDM_CIC_CFG_SGD_MASK)
#define PDM_CIC_CFG_SGD_GET(x) (((uint32_t)(x) & PDM_CIC_CFG_SGD_MASK) >> PDM_CIC_CFG_SGD_SHIFT)

/*
 * CIC_DEC_RATIO (RW)
 *
 * CIC decimation factor
 */
#define PDM_CIC_CFG_CIC_DEC_RATIO_MASK (0xFFU)
#define PDM_CIC_CFG_CIC_DEC_RATIO_SHIFT (0U)
#define PDM_CIC_CFG_CIC_DEC_RATIO_SET(x) (((uint32_t)(x) << PDM_CIC_CFG_CIC_DEC_RATIO_SHIFT) & PDM_CIC_CFG_CIC_DEC_RATIO_MASK)
#define PDM_CIC_CFG_CIC_DEC_RATIO_GET(x) (((uint32_t)(x) & PDM_CIC_CFG_CIC_DEC_RATIO_MASK) >> PDM_CIC_CFG_CIC_DEC_RATIO_SHIFT)

/* Bitfield definition for register: CTRL_INBUF */
/*
 * MAX_PTR (RW)
 *
 * The buf size-1 for each channel
 */
#define PDM_CTRL_INBUF_MAX_PTR_MASK (0x3FC00000UL)
#define PDM_CTRL_INBUF_MAX_PTR_SHIFT (22U)
#define PDM_CTRL_INBUF_MAX_PTR_SET(x) (((uint32_t)(x) << PDM_CTRL_INBUF_MAX_PTR_SHIFT) & PDM_CTRL_INBUF_MAX_PTR_MASK)
#define PDM_CTRL_INBUF_MAX_PTR_GET(x) (((uint32_t)(x) & PDM_CTRL_INBUF_MAX_PTR_MASK) >> PDM_CTRL_INBUF_MAX_PTR_SHIFT)

/*
 * PITCH (RW)
 *
 * The spacing between starting address of adjacent channels
 */
#define PDM_CTRL_INBUF_PITCH_MASK (0x3FF800UL)
#define PDM_CTRL_INBUF_PITCH_SHIFT (11U)
#define PDM_CTRL_INBUF_PITCH_SET(x) (((uint32_t)(x) << PDM_CTRL_INBUF_PITCH_SHIFT) & PDM_CTRL_INBUF_PITCH_MASK)
#define PDM_CTRL_INBUF_PITCH_GET(x) (((uint32_t)(x) & PDM_CTRL_INBUF_PITCH_MASK) >> PDM_CTRL_INBUF_PITCH_SHIFT)

/*
 * START_ADDR (RW)
 *
 * The starting address of channel 0 in filter data buffer
 */
#define PDM_CTRL_INBUF_START_ADDR_MASK (0x7FFU)
#define PDM_CTRL_INBUF_START_ADDR_SHIFT (0U)
#define PDM_CTRL_INBUF_START_ADDR_SET(x) (((uint32_t)(x) << PDM_CTRL_INBUF_START_ADDR_SHIFT) & PDM_CTRL_INBUF_START_ADDR_MASK)
#define PDM_CTRL_INBUF_START_ADDR_GET(x) (((uint32_t)(x) & PDM_CTRL_INBUF_START_ADDR_MASK) >> PDM_CTRL_INBUF_START_ADDR_SHIFT)

/* Bitfield definition for register: CTRL_FILT0 */
/*
 * COEF_LEN_M0 (RW)
 *
 * Coef length of filter type 2'b00 in coef memory
 */
#define PDM_CTRL_FILT0_COEF_LEN_M0_MASK (0xFF00U)
#define PDM_CTRL_FILT0_COEF_LEN_M0_SHIFT (8U)
#define PDM_CTRL_FILT0_COEF_LEN_M0_SET(x) (((uint32_t)(x) << PDM_CTRL_FILT0_COEF_LEN_M0_SHIFT) & PDM_CTRL_FILT0_COEF_LEN_M0_MASK)
#define PDM_CTRL_FILT0_COEF_LEN_M0_GET(x) (((uint32_t)(x) & PDM_CTRL_FILT0_COEF_LEN_M0_MASK) >> PDM_CTRL_FILT0_COEF_LEN_M0_SHIFT)

/*
 * COEF_START_ADDR (RW)
 *
 * Starting address of Coef of filter type 2'b00 in coef memory
 */
#define PDM_CTRL_FILT0_COEF_START_ADDR_MASK (0xFFU)
#define PDM_CTRL_FILT0_COEF_START_ADDR_SHIFT (0U)
#define PDM_CTRL_FILT0_COEF_START_ADDR_SET(x) (((uint32_t)(x) << PDM_CTRL_FILT0_COEF_START_ADDR_SHIFT) & PDM_CTRL_FILT0_COEF_START_ADDR_MASK)
#define PDM_CTRL_FILT0_COEF_START_ADDR_GET(x) (((uint32_t)(x) & PDM_CTRL_FILT0_COEF_START_ADDR_MASK) >> PDM_CTRL_FILT0_COEF_START_ADDR_SHIFT)

/* Bitfield definition for register: CTRL_FILT1 */
/*
 * COEF_LEN_M1 (RW)
 *
 * Coef length of filter type 2'b01 in coef memory
 */
#define PDM_CTRL_FILT1_COEF_LEN_M1_MASK (0xFF00U)
#define PDM_CTRL_FILT1_COEF_LEN_M1_SHIFT (8U)
#define PDM_CTRL_FILT1_COEF_LEN_M1_SET(x) (((uint32_t)(x) << PDM_CTRL_FILT1_COEF_LEN_M1_SHIFT) & PDM_CTRL_FILT1_COEF_LEN_M1_MASK)
#define PDM_CTRL_FILT1_COEF_LEN_M1_GET(x) (((uint32_t)(x) & PDM_CTRL_FILT1_COEF_LEN_M1_MASK) >> PDM_CTRL_FILT1_COEF_LEN_M1_SHIFT)

/*
 * COEF_START_ADDR (RW)
 *
 * Starting address of Coef of filter type 2'b01 in coef memory
 */
#define PDM_CTRL_FILT1_COEF_START_ADDR_MASK (0xFFU)
#define PDM_CTRL_FILT1_COEF_START_ADDR_SHIFT (0U)
#define PDM_CTRL_FILT1_COEF_START_ADDR_SET(x) (((uint32_t)(x) << PDM_CTRL_FILT1_COEF_START_ADDR_SHIFT) & PDM_CTRL_FILT1_COEF_START_ADDR_MASK)
#define PDM_CTRL_FILT1_COEF_START_ADDR_GET(x) (((uint32_t)(x) & PDM_CTRL_FILT1_COEF_START_ADDR_MASK) >> PDM_CTRL_FILT1_COEF_START_ADDR_SHIFT)

/* Bitfield definition for register: RUN */
/*
 * PDM_EN (RW)
 *
 * Asserted to enable the module
 */
#define PDM_RUN_PDM_EN_MASK (0x1U)
#define PDM_RUN_PDM_EN_SHIFT (0U)
#define PDM_RUN_PDM_EN_SET(x) (((uint32_t)(x) << PDM_RUN_PDM_EN_SHIFT) & PDM_RUN_PDM_EN_MASK)
#define PDM_RUN_PDM_EN_GET(x) (((uint32_t)(x) & PDM_RUN_PDM_EN_MASK) >> PDM_RUN_PDM_EN_SHIFT)

/* Bitfield definition for register: MEMADDR */
/*
 * ADDR (RW)
 *
 * 0--0x0FFFFFFF: COEF_RAM
 * 0x10000000--0x1FFFFFFF: DATA_RAM
 */
#define PDM_MEMADDR_ADDR_MASK (0xFFFFFFFFUL)
#define PDM_MEMADDR_ADDR_SHIFT (0U)
#define PDM_MEMADDR_ADDR_SET(x) (((uint32_t)(x) << PDM_MEMADDR_ADDR_SHIFT) & PDM_MEMADDR_ADDR_MASK)
#define PDM_MEMADDR_ADDR_GET(x) (((uint32_t)(x) & PDM_MEMADDR_ADDR_MASK) >> PDM_MEMADDR_ADDR_SHIFT)

/* Bitfield definition for register: MEMDATA */
/*
 * DATA (RW)
 *
 * The data write-to/read-from buffer
 */
#define PDM_MEMDATA_DATA_MASK (0xFFFFFFFFUL)
#define PDM_MEMDATA_DATA_SHIFT (0U)
#define PDM_MEMDATA_DATA_SET(x) (((uint32_t)(x) << PDM_MEMDATA_DATA_SHIFT) & PDM_MEMDATA_DATA_MASK)
#define PDM_MEMDATA_DATA_GET(x) (((uint32_t)(x) & PDM_MEMDATA_DATA_MASK) >> PDM_MEMDATA_DATA_SHIFT)

/* Bitfield definition for register: HPF_MA */
/*
 * COEF (RW)
 *
 * Composite value of  coef A of the Order-1 HPF
 */
#define PDM_HPF_MA_COEF_MASK (0xFFFFFFFFUL)
#define PDM_HPF_MA_COEF_SHIFT (0U)
#define PDM_HPF_MA_COEF_SET(x) (((uint32_t)(x) << PDM_HPF_MA_COEF_SHIFT) & PDM_HPF_MA_COEF_MASK)
#define PDM_HPF_MA_COEF_GET(x) (((uint32_t)(x) & PDM_HPF_MA_COEF_MASK) >> PDM_HPF_MA_COEF_SHIFT)

/* Bitfield definition for register: HPF_B */
/*
 * COEF (RW)
 *
 * coef B of the Order-1 HPF
 */
#define PDM_HPF_B_COEF_MASK (0xFFFFFFFFUL)
#define PDM_HPF_B_COEF_SHIFT (0U)
#define PDM_HPF_B_COEF_SET(x) (((uint32_t)(x) << PDM_HPF_B_COEF_SHIFT) & PDM_HPF_B_COEF_MASK)
#define PDM_HPF_B_COEF_GET(x) (((uint32_t)(x) & PDM_HPF_B_COEF_MASK) >> PDM_HPF_B_COEF_SHIFT)




#endif /* HPM_PDM_H */
