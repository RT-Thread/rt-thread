/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_SDADC_H
#define HPM_SDADC_H

typedef struct {
    __RW uint32_t CTRL;                        /* 0x0: SDADC control register */
    __RW uint32_t CLK_DIV;                     /* 0x4: clock divider */
    __RW uint32_t TTB;                         /* 0x8: Total Transfer Bits */
    __RW uint32_t START_OP;                    /* 0xC: Start_Of_Operation */
    __RW uint32_t MISC;                        /* 0x10: Misc Control */
    __R  uint32_t ST;                          /* 0x14: Status Register */
} SDADC_Type;


/* Bitfield definition for register: CTRL */
/*
 * SDM_CFG (RW)
 *
 * SDM analog part Configuration
 */
#define SDADC_CTRL_SDM_CFG_MASK (0xFF00000UL)
#define SDADC_CTRL_SDM_CFG_SHIFT (20U)
#define SDADC_CTRL_SDM_CFG_SET(x) (((uint32_t)(x) << SDADC_CTRL_SDM_CFG_SHIFT) & SDADC_CTRL_SDM_CFG_MASK)
#define SDADC_CTRL_SDM_CFG_GET(x) (((uint32_t)(x) & SDADC_CTRL_SDM_CFG_MASK) >> SDADC_CTRL_SDM_CFG_SHIFT)

/*
 * SDM_PGA_CE_SEL (RW)
 *
 * SDM_PGA_CE_SEL
 */
#define SDADC_CTRL_SDM_PGA_CE_SEL_MASK (0xC0000UL)
#define SDADC_CTRL_SDM_PGA_CE_SEL_SHIFT (18U)
#define SDADC_CTRL_SDM_PGA_CE_SEL_SET(x) (((uint32_t)(x) << SDADC_CTRL_SDM_PGA_CE_SEL_SHIFT) & SDADC_CTRL_SDM_PGA_CE_SEL_MASK)
#define SDADC_CTRL_SDM_PGA_CE_SEL_GET(x) (((uint32_t)(x) & SDADC_CTRL_SDM_PGA_CE_SEL_MASK) >> SDADC_CTRL_SDM_PGA_CE_SEL_SHIFT)

/*
 * SDM_PGA_CH_SEL (RW)
 *
 * SDM_PGA_CH_SEL
 */
#define SDADC_CTRL_SDM_PGA_CH_SEL_MASK (0x3C000UL)
#define SDADC_CTRL_SDM_PGA_CH_SEL_SHIFT (14U)
#define SDADC_CTRL_SDM_PGA_CH_SEL_SET(x) (((uint32_t)(x) << SDADC_CTRL_SDM_PGA_CH_SEL_SHIFT) & SDADC_CTRL_SDM_PGA_CH_SEL_MASK)
#define SDADC_CTRL_SDM_PGA_CH_SEL_GET(x) (((uint32_t)(x) & SDADC_CTRL_SDM_PGA_CH_SEL_MASK) >> SDADC_CTRL_SDM_PGA_CH_SEL_SHIFT)

/*
 * CFG_CDS_CMD (RW)
 *
 * config the common mode voltage of CDS CAP
 */
#define SDADC_CTRL_CFG_CDS_CMD_MASK (0x2000U)
#define SDADC_CTRL_CFG_CDS_CMD_SHIFT (13U)
#define SDADC_CTRL_CFG_CDS_CMD_SET(x) (((uint32_t)(x) << SDADC_CTRL_CFG_CDS_CMD_SHIFT) & SDADC_CTRL_CFG_CDS_CMD_MASK)
#define SDADC_CTRL_CFG_CDS_CMD_GET(x) (((uint32_t)(x) & SDADC_CTRL_CFG_CDS_CMD_MASK) >> SDADC_CTRL_CFG_CDS_CMD_SHIFT)

/*
 * LP_MODE_SDM (RW)
 *
 * lowpower mode of SDM
 */
#define SDADC_CTRL_LP_MODE_SDM_MASK (0xE00U)
#define SDADC_CTRL_LP_MODE_SDM_SHIFT (9U)
#define SDADC_CTRL_LP_MODE_SDM_SET(x) (((uint32_t)(x) << SDADC_CTRL_LP_MODE_SDM_SHIFT) & SDADC_CTRL_LP_MODE_SDM_MASK)
#define SDADC_CTRL_LP_MODE_SDM_GET(x) (((uint32_t)(x) & SDADC_CTRL_LP_MODE_SDM_MASK) >> SDADC_CTRL_LP_MODE_SDM_SHIFT)

/*
 * LP_MODE_PGA (RW)
 *
 * lowpower mode of PGA
 */
#define SDADC_CTRL_LP_MODE_PGA_MASK (0x1C0U)
#define SDADC_CTRL_LP_MODE_PGA_SHIFT (6U)
#define SDADC_CTRL_LP_MODE_PGA_SET(x) (((uint32_t)(x) << SDADC_CTRL_LP_MODE_PGA_SHIFT) & SDADC_CTRL_LP_MODE_PGA_MASK)
#define SDADC_CTRL_LP_MODE_PGA_GET(x) (((uint32_t)(x) & SDADC_CTRL_LP_MODE_PGA_MASK) >> SDADC_CTRL_LP_MODE_PGA_SHIFT)

/*
 * ANA_PWUP (RW)
 *
 * 1. Asserted to power up the analog part
 * 0: Shut off the power for the analog part
 */
#define SDADC_CTRL_ANA_PWUP_MASK (0x20U)
#define SDADC_CTRL_ANA_PWUP_SHIFT (5U)
#define SDADC_CTRL_ANA_PWUP_SET(x) (((uint32_t)(x) << SDADC_CTRL_ANA_PWUP_SHIFT) & SDADC_CTRL_ANA_PWUP_MASK)
#define SDADC_CTRL_ANA_PWUP_GET(x) (((uint32_t)(x) & SDADC_CTRL_ANA_PWUP_MASK) >> SDADC_CTRL_ANA_PWUP_SHIFT)

/*
 * BYPASS_PGA (RW)
 *
 * 1: PGA is bypassed
 * 0: PGA is enabled
 */
#define SDADC_CTRL_BYPASS_PGA_MASK (0x10U)
#define SDADC_CTRL_BYPASS_PGA_SHIFT (4U)
#define SDADC_CTRL_BYPASS_PGA_SET(x) (((uint32_t)(x) << SDADC_CTRL_BYPASS_PGA_SHIFT) & SDADC_CTRL_BYPASS_PGA_MASK)
#define SDADC_CTRL_BYPASS_PGA_GET(x) (((uint32_t)(x) & SDADC_CTRL_BYPASS_PGA_MASK) >> SDADC_CTRL_BYPASS_PGA_SHIFT)

/*
 * CONT_MODE (RW)
 *
 * 1: continuous mode of ADC conversion
 * 0: burst mode of ADC conversion.
 */
#define SDADC_CTRL_CONT_MODE_MASK (0x8U)
#define SDADC_CTRL_CONT_MODE_SHIFT (3U)
#define SDADC_CTRL_CONT_MODE_SET(x) (((uint32_t)(x) << SDADC_CTRL_CONT_MODE_SHIFT) & SDADC_CTRL_CONT_MODE_MASK)
#define SDADC_CTRL_CONT_MODE_GET(x) (((uint32_t)(x) & SDADC_CTRL_CONT_MODE_MASK) >> SDADC_CTRL_CONT_MODE_SHIFT)

/*
 * RST_SDM (RW)
 *
 * 1: reset  SDM. Should be de-asserted by software
 * 0: no reset SDM
 */
#define SDADC_CTRL_RST_SDM_MASK (0x4U)
#define SDADC_CTRL_RST_SDM_SHIFT (2U)
#define SDADC_CTRL_RST_SDM_SET(x) (((uint32_t)(x) << SDADC_CTRL_RST_SDM_SHIFT) & SDADC_CTRL_RST_SDM_MASK)
#define SDADC_CTRL_RST_SDM_GET(x) (((uint32_t)(x) & SDADC_CTRL_RST_SDM_MASK) >> SDADC_CTRL_RST_SDM_SHIFT)

/*
 * RST_PGA (RW)
 *
 * 1: reset  PGA. Should be de-asserted by software
 * 0: no reset PGA
 */
#define SDADC_CTRL_RST_PGA_MASK (0x2U)
#define SDADC_CTRL_RST_PGA_SHIFT (1U)
#define SDADC_CTRL_RST_PGA_SET(x) (((uint32_t)(x) << SDADC_CTRL_RST_PGA_SHIFT) & SDADC_CTRL_RST_PGA_MASK)
#define SDADC_CTRL_RST_PGA_GET(x) (((uint32_t)(x) & SDADC_CTRL_RST_PGA_MASK) >> SDADC_CTRL_RST_PGA_SHIFT)

/*
 * EN (RW)
 *
 * Module enable, to enable clok divder. Etc
 */
#define SDADC_CTRL_EN_MASK (0x1U)
#define SDADC_CTRL_EN_SHIFT (0U)
#define SDADC_CTRL_EN_SET(x) (((uint32_t)(x) << SDADC_CTRL_EN_SHIFT) & SDADC_CTRL_EN_MASK)
#define SDADC_CTRL_EN_GET(x) (((uint32_t)(x) & SDADC_CTRL_EN_MASK) >> SDADC_CTRL_EN_SHIFT)

/* Bitfield definition for register: CLK_DIV */
/*
 * FACTOR (RW)
 *
 * 0: disable clock output
 * 1: bypass the clock divider
 * 2: divide the clock by 2
 * …
 * n: divide the clock by n
 */
#define SDADC_CLK_DIV_FACTOR_MASK (0xFFU)
#define SDADC_CLK_DIV_FACTOR_SHIFT (0U)
#define SDADC_CLK_DIV_FACTOR_SET(x) (((uint32_t)(x) << SDADC_CLK_DIV_FACTOR_SHIFT) & SDADC_CLK_DIV_FACTOR_MASK)
#define SDADC_CLK_DIV_FACTOR_GET(x) (((uint32_t)(x) & SDADC_CLK_DIV_FACTOR_MASK) >> SDADC_CLK_DIV_FACTOR_SHIFT)

/* Bitfield definition for register: TTB */
/*
 * VAL (RW)
 *
 * the maximal number of output bits when ADC is in burst mode
 */
#define SDADC_TTB_VAL_MASK (0xFFFFFUL)
#define SDADC_TTB_VAL_SHIFT (0U)
#define SDADC_TTB_VAL_SET(x) (((uint32_t)(x) << SDADC_TTB_VAL_SHIFT) & SDADC_TTB_VAL_MASK)
#define SDADC_TTB_VAL_GET(x) (((uint32_t)(x) & SDADC_TTB_VAL_MASK) >> SDADC_TTB_VAL_SHIFT)

/* Bitfield definition for register: START_OP */
/*
 * SDM_EN (RW)
 *
 * 1. Enable sigma-delta ADC.  Auto clear in burst mode when TTB bits are received. In cont mode, must be cleared manually.
 * 0: disable sigma-delta ADC
 */
#define SDADC_START_OP_SDM_EN_MASK (0x1U)
#define SDADC_START_OP_SDM_EN_SHIFT (0U)
#define SDADC_START_OP_SDM_EN_SET(x) (((uint32_t)(x) << SDADC_START_OP_SDM_EN_SHIFT) & SDADC_START_OP_SDM_EN_MASK)
#define SDADC_START_OP_SDM_EN_GET(x) (((uint32_t)(x) & SDADC_START_OP_SDM_EN_MASK) >> SDADC_START_OP_SDM_EN_SHIFT)

/* Bitfield definition for register: MISC */
/*
 * BURST_DONE_IE (RW)
 *
 * Asserted to enable BURST_DONE event interrupt. Should not be asserted for continuous mode.
 */
#define SDADC_MISC_BURST_DONE_IE_MASK (0x2U)
#define SDADC_MISC_BURST_DONE_IE_SHIFT (1U)
#define SDADC_MISC_BURST_DONE_IE_SET(x) (((uint32_t)(x) << SDADC_MISC_BURST_DONE_IE_SHIFT) & SDADC_MISC_BURST_DONE_IE_MASK)
#define SDADC_MISC_BURST_DONE_IE_GET(x) (((uint32_t)(x) & SDADC_MISC_BURST_DONE_IE_MASK) >> SDADC_MISC_BURST_DONE_IE_SHIFT)

/*
 * PDM_CLK_SEL (RW)
 *
 * Asserted to use PDM clk input. Default to use MCLK which is directly from PLL.
 */
#define SDADC_MISC_PDM_CLK_SEL_MASK (0x1U)
#define SDADC_MISC_PDM_CLK_SEL_SHIFT (0U)
#define SDADC_MISC_PDM_CLK_SEL_SET(x) (((uint32_t)(x) << SDADC_MISC_PDM_CLK_SEL_SHIFT) & SDADC_MISC_PDM_CLK_SEL_MASK)
#define SDADC_MISC_PDM_CLK_SEL_GET(x) (((uint32_t)(x) & SDADC_MISC_PDM_CLK_SEL_MASK) >> SDADC_MISC_PDM_CLK_SEL_SHIFT)

/* Bitfield definition for register: ST */
/*
 * ANA_RST (RO)
 *
 * Asserted when analog module is in reset mode.
 */
#define SDADC_ST_ANA_RST_MASK (0x4U)
#define SDADC_ST_ANA_RST_SHIFT (2U)
#define SDADC_ST_ANA_RST_GET(x) (((uint32_t)(x) & SDADC_ST_ANA_RST_MASK) >> SDADC_ST_ANA_RST_SHIFT)

/*
 * DIV_STABLE (RO)
 *
 * Asserted when CLK_DIV reaches stable status. Cleared automatically when CLK_DIV[FACTOR] is assigned a different value.
 */
#define SDADC_ST_DIV_STABLE_MASK (0x2U)
#define SDADC_ST_DIV_STABLE_SHIFT (1U)
#define SDADC_ST_DIV_STABLE_GET(x) (((uint32_t)(x) & SDADC_ST_DIV_STABLE_MASK) >> SDADC_ST_DIV_STABLE_SHIFT)

/*
 * BURST_DONE (RO)
 *
 * Asserted when burst transfer is done. Auto cleared after the ST register is read while this bit is asserted.
 */
#define SDADC_ST_BURST_DONE_MASK (0x1U)
#define SDADC_ST_BURST_DONE_SHIFT (0U)
#define SDADC_ST_BURST_DONE_GET(x) (((uint32_t)(x) & SDADC_ST_BURST_DONE_MASK) >> SDADC_ST_BURST_DONE_SHIFT)




#endif /* HPM_SDADC_H */
