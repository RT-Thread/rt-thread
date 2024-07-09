/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_SDMV2_H
#define HPM_SDMV2_H

typedef struct {
    __RW uint32_t CTRL;                        /* 0x0: SDM control register */
    __RW uint32_t INT_EN;                      /* 0x4: Interrupt enable register. */
    __R  uint32_t STATUS;                      /* 0x8: Status Registers */
    __R  uint8_t  RESERVED0[4];                /* 0xC - 0xF: Reserved */
    struct {
        __RW uint32_t SDFIFOCTRL;              /* 0x10: Data FIFO Path Control Register */
        __RW uint32_t SDCTRLP;                 /* 0x14: Data Path Control Primary Register */
        __RW uint32_t SDCTRLE;                 /* 0x18: Data Path Control Extra Register */
        __RW uint32_t SDST;                    /* 0x1C: Data Path Status */
        __R  uint32_t SDATA;                   /* 0x20: Data */
        __R  uint32_t SDFIFO;                  /* 0x24: FIFO Data */
        __R  uint32_t SCAMP;                   /* 0x28: instant Amplitude Results */
        __RW uint32_t SCHTL;                   /* 0x2C: Amplitude Threshold for High Limit */
        __RW uint32_t SCHTLZ;                  /* 0x30: Amplitude Threshold for zero crossing */
        __RW uint32_t SCLLT;                   /* 0x34: Amplitude Threshold for low limit */
        __RW uint32_t SCCTRL;                  /* 0x38: Amplitude Path Control */
        __RW uint32_t SCST;                    /* 0x3C: Amplitude Path Status */
        __R  uint8_t  RESERVED0[16];           /* 0x40 - 0x4F: Reserved */
    } CH[1];
} SDMV2_Type;


/* Bitfield definition for register: CTRL */
/*
 * SFTRST (RW)
 *
 * software reset the module if asserted to be1’b1.
 */
#define SDMV2_CTRL_SFTRST_MASK (0x80000000UL)
#define SDMV2_CTRL_SFTRST_SHIFT (31U)
#define SDMV2_CTRL_SFTRST_SET(x) (((uint32_t)(x) << SDMV2_CTRL_SFTRST_SHIFT) & SDMV2_CTRL_SFTRST_MASK)
#define SDMV2_CTRL_SFTRST_GET(x) (((uint32_t)(x) & SDMV2_CTRL_SFTRST_MASK) >> SDMV2_CTRL_SFTRST_SHIFT)

/*
 * CHMD (RW)
 *
 * Channel Rcv mode
 * Bits[2:0] for Ch0.
 * Bits[5:3] for Ch1
 * Bits[8:6] for Ch2
 * Bits[11:9] for Ch3
 * 3'b000: Capture at posedge of MCLK
 * 3'b001: Capture at both posedge and negedge of MCLK
 * 3'b010: Manchestor Mode
 * 3'b011: Capture at negedge of MCLK
 * 3'b100: Capture at every other posedge of MCLK
 * 3'b101: Capture at every other negedge of MCLK
 * Others: Undefined
 */
#define SDMV2_CTRL_CHMD_MASK (0x3FFC000UL)
#define SDMV2_CTRL_CHMD_SHIFT (14U)
#define SDMV2_CTRL_CHMD_SET(x) (((uint32_t)(x) << SDMV2_CTRL_CHMD_SHIFT) & SDMV2_CTRL_CHMD_MASK)
#define SDMV2_CTRL_CHMD_GET(x) (((uint32_t)(x) & SDMV2_CTRL_CHMD_MASK) >> SDMV2_CTRL_CHMD_SHIFT)

/*
 * SYNC_MCLK (RW)
 *
 * Asserted to double sync the mclk input pin before its usage inside the module
 */
#define SDMV2_CTRL_SYNC_MCLK_MASK (0x3C00U)
#define SDMV2_CTRL_SYNC_MCLK_SHIFT (10U)
#define SDMV2_CTRL_SYNC_MCLK_SET(x) (((uint32_t)(x) << SDMV2_CTRL_SYNC_MCLK_SHIFT) & SDMV2_CTRL_SYNC_MCLK_MASK)
#define SDMV2_CTRL_SYNC_MCLK_GET(x) (((uint32_t)(x) & SDMV2_CTRL_SYNC_MCLK_MASK) >> SDMV2_CTRL_SYNC_MCLK_SHIFT)

/*
 * SYNC_MDAT (RW)
 *
 * Asserted to double sync the mdat input pin before its usage inside the module
 */
#define SDMV2_CTRL_SYNC_MDAT_MASK (0x3C0U)
#define SDMV2_CTRL_SYNC_MDAT_SHIFT (6U)
#define SDMV2_CTRL_SYNC_MDAT_SET(x) (((uint32_t)(x) << SDMV2_CTRL_SYNC_MDAT_SHIFT) & SDMV2_CTRL_SYNC_MDAT_MASK)
#define SDMV2_CTRL_SYNC_MDAT_GET(x) (((uint32_t)(x) & SDMV2_CTRL_SYNC_MDAT_MASK) >> SDMV2_CTRL_SYNC_MDAT_SHIFT)

/*
 * CH_EN (RW)
 *
 * Channel Enable
 */
#define SDMV2_CTRL_CH_EN_MASK (0x3CU)
#define SDMV2_CTRL_CH_EN_SHIFT (2U)
#define SDMV2_CTRL_CH_EN_SET(x) (((uint32_t)(x) << SDMV2_CTRL_CH_EN_SHIFT) & SDMV2_CTRL_CH_EN_MASK)
#define SDMV2_CTRL_CH_EN_GET(x) (((uint32_t)(x) & SDMV2_CTRL_CH_EN_MASK) >> SDMV2_CTRL_CH_EN_SHIFT)

/*
 * IE (RW)
 *
 * Interrupt Enable
 */
#define SDMV2_CTRL_IE_MASK (0x2U)
#define SDMV2_CTRL_IE_SHIFT (1U)
#define SDMV2_CTRL_IE_SET(x) (((uint32_t)(x) << SDMV2_CTRL_IE_SHIFT) & SDMV2_CTRL_IE_MASK)
#define SDMV2_CTRL_IE_GET(x) (((uint32_t)(x) & SDMV2_CTRL_IE_MASK) >> SDMV2_CTRL_IE_SHIFT)

/* Bitfield definition for register: INT_EN */
/*
 * CH0DRY (RW)
 *
 * Ch0 Data Ready interrupt enable
 */
#define SDMV2_INT_EN_CH0DRY_MASK (0x10U)
#define SDMV2_INT_EN_CH0DRY_SHIFT (4U)
#define SDMV2_INT_EN_CH0DRY_SET(x) (((uint32_t)(x) << SDMV2_INT_EN_CH0DRY_SHIFT) & SDMV2_INT_EN_CH0DRY_MASK)
#define SDMV2_INT_EN_CH0DRY_GET(x) (((uint32_t)(x) & SDMV2_INT_EN_CH0DRY_MASK) >> SDMV2_INT_EN_CH0DRY_SHIFT)

/*
 * CH0ERR (RW)
 *
 * Ch0 Error interrupt enable
 */
#define SDMV2_INT_EN_CH0ERR_MASK (0x1U)
#define SDMV2_INT_EN_CH0ERR_SHIFT (0U)
#define SDMV2_INT_EN_CH0ERR_SET(x) (((uint32_t)(x) << SDMV2_INT_EN_CH0ERR_SHIFT) & SDMV2_INT_EN_CH0ERR_MASK)
#define SDMV2_INT_EN_CH0ERR_GET(x) (((uint32_t)(x) & SDMV2_INT_EN_CH0ERR_MASK) >> SDMV2_INT_EN_CH0ERR_SHIFT)

/* Bitfield definition for register: STATUS */
/*
 * CH0DRY (RO)
 *
 * Ch0 Data Ready
 */
#define SDMV2_STATUS_CH0DRY_MASK (0x2U)
#define SDMV2_STATUS_CH0DRY_SHIFT (1U)
#define SDMV2_STATUS_CH0DRY_GET(x) (((uint32_t)(x) & SDMV2_STATUS_CH0DRY_MASK) >> SDMV2_STATUS_CH0DRY_SHIFT)

/*
 * CH0ERR (RO)
 *
 * Ch0 Error
 */
#define SDMV2_STATUS_CH0ERR_MASK (0x1U)
#define SDMV2_STATUS_CH0ERR_SHIFT (0U)
#define SDMV2_STATUS_CH0ERR_GET(x) (((uint32_t)(x) & SDMV2_STATUS_CH0ERR_MASK) >> SDMV2_STATUS_CH0ERR_SHIFT)

/* Bitfield definition for register of struct array CH: SDFIFOCTRL */
/*
 * THRSH (RW)
 *
 * FIFO threshold (0,..,16) (fillings > threshold, then gen int)
 */
#define SDMV2_CH_SDFIFOCTRL_THRSH_MASK (0x1F0U)
#define SDMV2_CH_SDFIFOCTRL_THRSH_SHIFT (4U)
#define SDMV2_CH_SDFIFOCTRL_THRSH_SET(x) (((uint32_t)(x) << SDMV2_CH_SDFIFOCTRL_THRSH_SHIFT) & SDMV2_CH_SDFIFOCTRL_THRSH_MASK)
#define SDMV2_CH_SDFIFOCTRL_THRSH_GET(x) (((uint32_t)(x) & SDMV2_CH_SDFIFOCTRL_THRSH_MASK) >> SDMV2_CH_SDFIFOCTRL_THRSH_SHIFT)

/*
 * D_RDY_INT_EN (RW)
 *
 * FIFO data ready interrupt enable
 */
#define SDMV2_CH_SDFIFOCTRL_D_RDY_INT_EN_MASK (0x4U)
#define SDMV2_CH_SDFIFOCTRL_D_RDY_INT_EN_SHIFT (2U)
#define SDMV2_CH_SDFIFOCTRL_D_RDY_INT_EN_SET(x) (((uint32_t)(x) << SDMV2_CH_SDFIFOCTRL_D_RDY_INT_EN_SHIFT) & SDMV2_CH_SDFIFOCTRL_D_RDY_INT_EN_MASK)
#define SDMV2_CH_SDFIFOCTRL_D_RDY_INT_EN_GET(x) (((uint32_t)(x) & SDMV2_CH_SDFIFOCTRL_D_RDY_INT_EN_MASK) >> SDMV2_CH_SDFIFOCTRL_D_RDY_INT_EN_SHIFT)

/* Bitfield definition for register of struct array CH: SDCTRLP */
/*
 * MANCH_THR (RW)
 *
 * Manchester Decoding threshold. 3/4 of PERIOD_MCLK[7:0]
 */
#define SDMV2_CH_SDCTRLP_MANCH_THR_MASK (0xFE000000UL)
#define SDMV2_CH_SDCTRLP_MANCH_THR_SHIFT (25U)
#define SDMV2_CH_SDCTRLP_MANCH_THR_SET(x) (((uint32_t)(x) << SDMV2_CH_SDCTRLP_MANCH_THR_SHIFT) & SDMV2_CH_SDCTRLP_MANCH_THR_MASK)
#define SDMV2_CH_SDCTRLP_MANCH_THR_GET(x) (((uint32_t)(x) & SDMV2_CH_SDCTRLP_MANCH_THR_MASK) >> SDMV2_CH_SDCTRLP_MANCH_THR_SHIFT)

/*
 * WDOG_THR (RW)
 *
 * Watch dog threshold for channel failure of CLK halting
 */
#define SDMV2_CH_SDCTRLP_WDOG_THR_MASK (0x1FE0000UL)
#define SDMV2_CH_SDCTRLP_WDOG_THR_SHIFT (17U)
#define SDMV2_CH_SDCTRLP_WDOG_THR_SET(x) (((uint32_t)(x) << SDMV2_CH_SDCTRLP_WDOG_THR_SHIFT) & SDMV2_CH_SDCTRLP_WDOG_THR_MASK)
#define SDMV2_CH_SDCTRLP_WDOG_THR_GET(x) (((uint32_t)(x) & SDMV2_CH_SDCTRLP_WDOG_THR_MASK) >> SDMV2_CH_SDCTRLP_WDOG_THR_SHIFT)

/*
 * AF_IE (RW)
 *
 * Acknowledge feedback interrupt enable
 */
#define SDMV2_CH_SDCTRLP_AF_IE_MASK (0x10000UL)
#define SDMV2_CH_SDCTRLP_AF_IE_SHIFT (16U)
#define SDMV2_CH_SDCTRLP_AF_IE_SET(x) (((uint32_t)(x) << SDMV2_CH_SDCTRLP_AF_IE_SHIFT) & SDMV2_CH_SDCTRLP_AF_IE_MASK)
#define SDMV2_CH_SDCTRLP_AF_IE_GET(x) (((uint32_t)(x) & SDMV2_CH_SDCTRLP_AF_IE_MASK) >> SDMV2_CH_SDCTRLP_AF_IE_SHIFT)

/*
 * DFFOVIE (RW)
 *
 * Ch Data FIFO overflow interrupt enable
 */
#define SDMV2_CH_SDCTRLP_DFFOVIE_MASK (0x8000U)
#define SDMV2_CH_SDCTRLP_DFFOVIE_SHIFT (15U)
#define SDMV2_CH_SDCTRLP_DFFOVIE_SET(x) (((uint32_t)(x) << SDMV2_CH_SDCTRLP_DFFOVIE_SHIFT) & SDMV2_CH_SDCTRLP_DFFOVIE_MASK)
#define SDMV2_CH_SDCTRLP_DFFOVIE_GET(x) (((uint32_t)(x) & SDMV2_CH_SDCTRLP_DFFOVIE_MASK) >> SDMV2_CH_SDCTRLP_DFFOVIE_SHIFT)

/*
 * DSATIE (RW)
 *
 * Ch CIC Data Saturation Interrupt Enable
 */
#define SDMV2_CH_SDCTRLP_DSATIE_MASK (0x4000U)
#define SDMV2_CH_SDCTRLP_DSATIE_SHIFT (14U)
#define SDMV2_CH_SDCTRLP_DSATIE_SET(x) (((uint32_t)(x) << SDMV2_CH_SDCTRLP_DSATIE_SHIFT) & SDMV2_CH_SDCTRLP_DSATIE_MASK)
#define SDMV2_CH_SDCTRLP_DSATIE_GET(x) (((uint32_t)(x) & SDMV2_CH_SDCTRLP_DSATIE_MASK) >> SDMV2_CH_SDCTRLP_DSATIE_SHIFT)

/*
 * DRIE (RW)
 *
 * Ch Data Ready Interrupt Enable
 */
#define SDMV2_CH_SDCTRLP_DRIE_MASK (0x2000U)
#define SDMV2_CH_SDCTRLP_DRIE_SHIFT (13U)
#define SDMV2_CH_SDCTRLP_DRIE_SET(x) (((uint32_t)(x) << SDMV2_CH_SDCTRLP_DRIE_SHIFT) & SDMV2_CH_SDCTRLP_DRIE_MASK)
#define SDMV2_CH_SDCTRLP_DRIE_GET(x) (((uint32_t)(x) & SDMV2_CH_SDCTRLP_DRIE_MASK) >> SDMV2_CH_SDCTRLP_DRIE_SHIFT)

/*
 * SYNCSEL (RW)
 *
 * Select the PWM SYNC Source
 */
#define SDMV2_CH_SDCTRLP_SYNCSEL_MASK (0x1F80U)
#define SDMV2_CH_SDCTRLP_SYNCSEL_SHIFT (7U)
#define SDMV2_CH_SDCTRLP_SYNCSEL_SET(x) (((uint32_t)(x) << SDMV2_CH_SDCTRLP_SYNCSEL_SHIFT) & SDMV2_CH_SDCTRLP_SYNCSEL_MASK)
#define SDMV2_CH_SDCTRLP_SYNCSEL_GET(x) (((uint32_t)(x) & SDMV2_CH_SDCTRLP_SYNCSEL_MASK) >> SDMV2_CH_SDCTRLP_SYNCSEL_SHIFT)

/*
 * FFSYNCCLREN (RW)
 *
 * Auto clear FIFO when a new SDSYNC event is found. Only valid when WTSYNCEN=1
 */
#define SDMV2_CH_SDCTRLP_FFSYNCCLREN_MASK (0x40U)
#define SDMV2_CH_SDCTRLP_FFSYNCCLREN_SHIFT (6U)
#define SDMV2_CH_SDCTRLP_FFSYNCCLREN_SET(x) (((uint32_t)(x) << SDMV2_CH_SDCTRLP_FFSYNCCLREN_SHIFT) & SDMV2_CH_SDCTRLP_FFSYNCCLREN_MASK)
#define SDMV2_CH_SDCTRLP_FFSYNCCLREN_GET(x) (((uint32_t)(x) & SDMV2_CH_SDCTRLP_FFSYNCCLREN_MASK) >> SDMV2_CH_SDCTRLP_FFSYNCCLREN_SHIFT)

/*
 * WTSYNACLR (RW)
 *
 * 1: Asserted to Auto clear WTSYNFLG when the SDFFINT is gen
 * 0: WTSYNFLG should be cleared manually by WTSYNMCLR
 */
#define SDMV2_CH_SDCTRLP_WTSYNACLR_MASK (0x20U)
#define SDMV2_CH_SDCTRLP_WTSYNACLR_SHIFT (5U)
#define SDMV2_CH_SDCTRLP_WTSYNACLR_SET(x) (((uint32_t)(x) << SDMV2_CH_SDCTRLP_WTSYNACLR_SHIFT) & SDMV2_CH_SDCTRLP_WTSYNACLR_MASK)
#define SDMV2_CH_SDCTRLP_WTSYNACLR_GET(x) (((uint32_t)(x) & SDMV2_CH_SDCTRLP_WTSYNACLR_MASK) >> SDMV2_CH_SDCTRLP_WTSYNACLR_SHIFT)

/*
 * WTSYNMCLR (RW)
 *
 * 1: Manually clear WTSYNFLG. Auto-clear.
 */
#define SDMV2_CH_SDCTRLP_WTSYNMCLR_MASK (0x10U)
#define SDMV2_CH_SDCTRLP_WTSYNMCLR_SHIFT (4U)
#define SDMV2_CH_SDCTRLP_WTSYNMCLR_SET(x) (((uint32_t)(x) << SDMV2_CH_SDCTRLP_WTSYNMCLR_SHIFT) & SDMV2_CH_SDCTRLP_WTSYNMCLR_MASK)
#define SDMV2_CH_SDCTRLP_WTSYNMCLR_GET(x) (((uint32_t)(x) & SDMV2_CH_SDCTRLP_WTSYNMCLR_MASK) >> SDMV2_CH_SDCTRLP_WTSYNMCLR_SHIFT)

/*
 * WTSYNCEN (RW)
 *
 * 1: Start to store data only after PWM SYNC event
 * 0: Start to store data whenever enabled
 */
#define SDMV2_CH_SDCTRLP_WTSYNCEN_MASK (0x8U)
#define SDMV2_CH_SDCTRLP_WTSYNCEN_SHIFT (3U)
#define SDMV2_CH_SDCTRLP_WTSYNCEN_SET(x) (((uint32_t)(x) << SDMV2_CH_SDCTRLP_WTSYNCEN_SHIFT) & SDMV2_CH_SDCTRLP_WTSYNCEN_MASK)
#define SDMV2_CH_SDCTRLP_WTSYNCEN_GET(x) (((uint32_t)(x) & SDMV2_CH_SDCTRLP_WTSYNCEN_MASK) >> SDMV2_CH_SDCTRLP_WTSYNCEN_SHIFT)

/*
 * D32 (RW)
 *
 * 1:32 bit data
 * 0:16 bit data
 */
#define SDMV2_CH_SDCTRLP_D32_MASK (0x4U)
#define SDMV2_CH_SDCTRLP_D32_SHIFT (2U)
#define SDMV2_CH_SDCTRLP_D32_SET(x) (((uint32_t)(x) << SDMV2_CH_SDCTRLP_D32_SHIFT) & SDMV2_CH_SDCTRLP_D32_MASK)
#define SDMV2_CH_SDCTRLP_D32_GET(x) (((uint32_t)(x) & SDMV2_CH_SDCTRLP_D32_MASK) >> SDMV2_CH_SDCTRLP_D32_SHIFT)

/*
 * DR_OPT (RW)
 *
 * 1: Use Data FIFO Ready as data ready when fifo fillings are greater than the threshold
 * 0: Use Data Reg Ready as data ready
 */
#define SDMV2_CH_SDCTRLP_DR_OPT_MASK (0x2U)
#define SDMV2_CH_SDCTRLP_DR_OPT_SHIFT (1U)
#define SDMV2_CH_SDCTRLP_DR_OPT_SET(x) (((uint32_t)(x) << SDMV2_CH_SDCTRLP_DR_OPT_SHIFT) & SDMV2_CH_SDCTRLP_DR_OPT_MASK)
#define SDMV2_CH_SDCTRLP_DR_OPT_GET(x) (((uint32_t)(x) & SDMV2_CH_SDCTRLP_DR_OPT_MASK) >> SDMV2_CH_SDCTRLP_DR_OPT_SHIFT)

/*
 * EN (RW)
 *
 * Data Path Enable
 */
#define SDMV2_CH_SDCTRLP_EN_MASK (0x1U)
#define SDMV2_CH_SDCTRLP_EN_SHIFT (0U)
#define SDMV2_CH_SDCTRLP_EN_SET(x) (((uint32_t)(x) << SDMV2_CH_SDCTRLP_EN_SHIFT) & SDMV2_CH_SDCTRLP_EN_MASK)
#define SDMV2_CH_SDCTRLP_EN_GET(x) (((uint32_t)(x) & SDMV2_CH_SDCTRLP_EN_MASK) >> SDMV2_CH_SDCTRLP_EN_SHIFT)

/* Bitfield definition for register of struct array CH: SDCTRLE */
/*
 * 2ND_CIC_SCL (RW)
 *
 * the shifter pace for the output of the 2ns stage CIC
 * 0: shift right 0
 * …
 * n: shift right n steps
 * max 17, so needs 5 bits
 */
#define SDMV2_CH_SDCTRLE_2ND_CIC_SCL_MASK (0x3E00000UL)
#define SDMV2_CH_SDCTRLE_2ND_CIC_SCL_SHIFT (21U)
#define SDMV2_CH_SDCTRLE_2ND_CIC_SCL_SET(x) (((uint32_t)(x) << SDMV2_CH_SDCTRLE_2ND_CIC_SCL_SHIFT) & SDMV2_CH_SDCTRLE_2ND_CIC_SCL_MASK)
#define SDMV2_CH_SDCTRLE_2ND_CIC_SCL_GET(x) (((uint32_t)(x) & SDMV2_CH_SDCTRLE_2ND_CIC_SCL_MASK) >> SDMV2_CH_SDCTRLE_2ND_CIC_SCL_SHIFT)

/*
 * 2ND_SGD_ORDER (RW)
 *
 * 2nd CIC order
 * 0: SYNC1
 * 1: SYNC2
 * 2: SYNC3
 * 3: FAST_SYNC
 */
#define SDMV2_CH_SDCTRLE_2ND_SGD_ORDER_MASK (0x180000UL)
#define SDMV2_CH_SDCTRLE_2ND_SGD_ORDER_SHIFT (19U)
#define SDMV2_CH_SDCTRLE_2ND_SGD_ORDER_SET(x) (((uint32_t)(x) << SDMV2_CH_SDCTRLE_2ND_SGD_ORDER_SHIFT) & SDMV2_CH_SDCTRLE_2ND_SGD_ORDER_MASK)
#define SDMV2_CH_SDCTRLE_2ND_SGD_ORDER_GET(x) (((uint32_t)(x) & SDMV2_CH_SDCTRLE_2ND_SGD_ORDER_MASK) >> SDMV2_CH_SDCTRLE_2ND_SGD_ORDER_SHIFT)

/*
 * SGD_ORDR (RW)
 *
 * CIC order
 * 0: SYNC1
 * 1: SYNC2
 * 2: SYNC3
 * 3: FAST_SYNC
 */
#define SDMV2_CH_SDCTRLE_SGD_ORDR_MASK (0x60000UL)
#define SDMV2_CH_SDCTRLE_SGD_ORDR_SHIFT (17U)
#define SDMV2_CH_SDCTRLE_SGD_ORDR_SET(x) (((uint32_t)(x) << SDMV2_CH_SDCTRLE_SGD_ORDR_SHIFT) & SDMV2_CH_SDCTRLE_SGD_ORDR_MASK)
#define SDMV2_CH_SDCTRLE_SGD_ORDR_GET(x) (((uint32_t)(x) & SDMV2_CH_SDCTRLE_SGD_ORDR_MASK) >> SDMV2_CH_SDCTRLE_SGD_ORDR_SHIFT)

/*
 * PWMSYNC (RW)
 *
 * Asserted to double sync the PWM trigger signal
 */
#define SDMV2_CH_SDCTRLE_PWMSYNC_MASK (0x10000UL)
#define SDMV2_CH_SDCTRLE_PWMSYNC_SHIFT (16U)
#define SDMV2_CH_SDCTRLE_PWMSYNC_SET(x) (((uint32_t)(x) << SDMV2_CH_SDCTRLE_PWMSYNC_SHIFT) & SDMV2_CH_SDCTRLE_PWMSYNC_MASK)
#define SDMV2_CH_SDCTRLE_PWMSYNC_GET(x) (((uint32_t)(x) & SDMV2_CH_SDCTRLE_PWMSYNC_MASK) >> SDMV2_CH_SDCTRLE_PWMSYNC_SHIFT)

/*
 * USE_ALT (RW)
 *
 * Asserted to use alternative input.
 * Alternative input has a restart_filt to reset the counter and start data transfer, and also it has an intermittent input clock to accompany the input data.
 */
#define SDMV2_CH_SDCTRLE_USE_ALT_MASK (0x8000U)
#define SDMV2_CH_SDCTRLE_USE_ALT_SHIFT (15U)
#define SDMV2_CH_SDCTRLE_USE_ALT_SET(x) (((uint32_t)(x) << SDMV2_CH_SDCTRLE_USE_ALT_SHIFT) & SDMV2_CH_SDCTRLE_USE_ALT_MASK)
#define SDMV2_CH_SDCTRLE_USE_ALT_GET(x) (((uint32_t)(x) & SDMV2_CH_SDCTRLE_USE_ALT_MASK) >> SDMV2_CH_SDCTRLE_USE_ALT_SHIFT)

/*
 * CIC_SCL (RW)
 *
 * CIC shift control
 */
#define SDMV2_CH_SDCTRLE_CIC_SCL_MASK (0x7800U)
#define SDMV2_CH_SDCTRLE_CIC_SCL_SHIFT (11U)
#define SDMV2_CH_SDCTRLE_CIC_SCL_SET(x) (((uint32_t)(x) << SDMV2_CH_SDCTRLE_CIC_SCL_SHIFT) & SDMV2_CH_SDCTRLE_CIC_SCL_MASK)
#define SDMV2_CH_SDCTRLE_CIC_SCL_GET(x) (((uint32_t)(x) & SDMV2_CH_SDCTRLE_CIC_SCL_MASK) >> SDMV2_CH_SDCTRLE_CIC_SCL_SHIFT)

/*
 * CIC_DEC_RATIO (RW)
 *
 * CIC decimation ratio. 0 means div-by-256
 */
#define SDMV2_CH_SDCTRLE_CIC_DEC_RATIO_MASK (0x7F8U)
#define SDMV2_CH_SDCTRLE_CIC_DEC_RATIO_SHIFT (3U)
#define SDMV2_CH_SDCTRLE_CIC_DEC_RATIO_SET(x) (((uint32_t)(x) << SDMV2_CH_SDCTRLE_CIC_DEC_RATIO_SHIFT) & SDMV2_CH_SDCTRLE_CIC_DEC_RATIO_MASK)
#define SDMV2_CH_SDCTRLE_CIC_DEC_RATIO_GET(x) (((uint32_t)(x) & SDMV2_CH_SDCTRLE_CIC_DEC_RATIO_MASK) >> SDMV2_CH_SDCTRLE_CIC_DEC_RATIO_SHIFT)

/*
 * IGN_INI_SAMPLES (RW)
 *
 * NotZero: Don't store the first samples that are not accurate
 * Zero: Store all samples
 */
#define SDMV2_CH_SDCTRLE_IGN_INI_SAMPLES_MASK (0x7U)
#define SDMV2_CH_SDCTRLE_IGN_INI_SAMPLES_SHIFT (0U)
#define SDMV2_CH_SDCTRLE_IGN_INI_SAMPLES_SET(x) (((uint32_t)(x) << SDMV2_CH_SDCTRLE_IGN_INI_SAMPLES_SHIFT) & SDMV2_CH_SDCTRLE_IGN_INI_SAMPLES_MASK)
#define SDMV2_CH_SDCTRLE_IGN_INI_SAMPLES_GET(x) (((uint32_t)(x) & SDMV2_CH_SDCTRLE_IGN_INI_SAMPLES_MASK) >> SDMV2_CH_SDCTRLE_IGN_INI_SAMPLES_SHIFT)

/* Bitfield definition for register of struct array CH: SDST */
/*
 * PERIOD_MCLK (RO)
 *
 * maxim of mclk spacing in cycles, using edges of mclk signal.  In manchester coding mode, it is just the period of MCLK. In other modes, it is almost the half period.
 */
#define SDMV2_CH_SDST_PERIOD_MCLK_MASK (0x7F800000UL)
#define SDMV2_CH_SDST_PERIOD_MCLK_SHIFT (23U)
#define SDMV2_CH_SDST_PERIOD_MCLK_GET(x) (((uint32_t)(x) & SDMV2_CH_SDST_PERIOD_MCLK_MASK) >> SDMV2_CH_SDST_PERIOD_MCLK_SHIFT)

/*
 * 2ND_DSAT_ERR (W1C)
 *
 * CIC out Data saturation err. Error flag.
 */
#define SDMV2_CH_SDST_2ND_DSAT_ERR_MASK (0x800U)
#define SDMV2_CH_SDST_2ND_DSAT_ERR_SHIFT (11U)
#define SDMV2_CH_SDST_2ND_DSAT_ERR_SET(x) (((uint32_t)(x) << SDMV2_CH_SDST_2ND_DSAT_ERR_SHIFT) & SDMV2_CH_SDST_2ND_DSAT_ERR_MASK)
#define SDMV2_CH_SDST_2ND_DSAT_ERR_GET(x) (((uint32_t)(x) & SDMV2_CH_SDST_2ND_DSAT_ERR_MASK) >> SDMV2_CH_SDST_2ND_DSAT_ERR_SHIFT)

/*
 * FIFO_DR (W1C)
 *
 * FIFO data ready
 */
#define SDMV2_CH_SDST_FIFO_DR_MASK (0x200U)
#define SDMV2_CH_SDST_FIFO_DR_SHIFT (9U)
#define SDMV2_CH_SDST_FIFO_DR_SET(x) (((uint32_t)(x) << SDMV2_CH_SDST_FIFO_DR_SHIFT) & SDMV2_CH_SDST_FIFO_DR_MASK)
#define SDMV2_CH_SDST_FIFO_DR_GET(x) (((uint32_t)(x) & SDMV2_CH_SDST_FIFO_DR_MASK) >> SDMV2_CH_SDST_FIFO_DR_SHIFT)

/*
 * AF (W1C)
 *
 * Achnowledge flag
 */
#define SDMV2_CH_SDST_AF_MASK (0x100U)
#define SDMV2_CH_SDST_AF_SHIFT (8U)
#define SDMV2_CH_SDST_AF_SET(x) (((uint32_t)(x) << SDMV2_CH_SDST_AF_SHIFT) & SDMV2_CH_SDST_AF_MASK)
#define SDMV2_CH_SDST_AF_GET(x) (((uint32_t)(x) & SDMV2_CH_SDST_AF_MASK) >> SDMV2_CH_SDST_AF_SHIFT)

/*
 * DOV_ERR (W1C)
 *
 * Data FIFO Overflow Error. Error flag.
 */
#define SDMV2_CH_SDST_DOV_ERR_MASK (0x80U)
#define SDMV2_CH_SDST_DOV_ERR_SHIFT (7U)
#define SDMV2_CH_SDST_DOV_ERR_SET(x) (((uint32_t)(x) << SDMV2_CH_SDST_DOV_ERR_SHIFT) & SDMV2_CH_SDST_DOV_ERR_MASK)
#define SDMV2_CH_SDST_DOV_ERR_GET(x) (((uint32_t)(x) & SDMV2_CH_SDST_DOV_ERR_MASK) >> SDMV2_CH_SDST_DOV_ERR_SHIFT)

/*
 * DSAT_ERR (W1C)
 *
 * CIC out Data saturation err. Error flag.
 */
#define SDMV2_CH_SDST_DSAT_ERR_MASK (0x40U)
#define SDMV2_CH_SDST_DSAT_ERR_SHIFT (6U)
#define SDMV2_CH_SDST_DSAT_ERR_SET(x) (((uint32_t)(x) << SDMV2_CH_SDST_DSAT_ERR_SHIFT) & SDMV2_CH_SDST_DSAT_ERR_MASK)
#define SDMV2_CH_SDST_DSAT_ERR_GET(x) (((uint32_t)(x) & SDMV2_CH_SDST_DSAT_ERR_MASK) >> SDMV2_CH_SDST_DSAT_ERR_SHIFT)

/*
 * WTSYNFLG (RO)
 *
 * Wait-for-sync event found
 */
#define SDMV2_CH_SDST_WTSYNFLG_MASK (0x20U)
#define SDMV2_CH_SDST_WTSYNFLG_SHIFT (5U)
#define SDMV2_CH_SDST_WTSYNFLG_GET(x) (((uint32_t)(x) & SDMV2_CH_SDST_WTSYNFLG_MASK) >> SDMV2_CH_SDST_WTSYNFLG_SHIFT)

/*
 * FILL (RO)
 *
 * Data FIFO Fillings
 */
#define SDMV2_CH_SDST_FILL_MASK (0x1FU)
#define SDMV2_CH_SDST_FILL_SHIFT (0U)
#define SDMV2_CH_SDST_FILL_GET(x) (((uint32_t)(x) & SDMV2_CH_SDST_FILL_MASK) >> SDMV2_CH_SDST_FILL_SHIFT)

/* Bitfield definition for register of struct array CH: SDATA */
/*
 * VAL (RO)
 *
 * Data
 */
#define SDMV2_CH_SDATA_VAL_MASK (0xFFFFFFFFUL)
#define SDMV2_CH_SDATA_VAL_SHIFT (0U)
#define SDMV2_CH_SDATA_VAL_GET(x) (((uint32_t)(x) & SDMV2_CH_SDATA_VAL_MASK) >> SDMV2_CH_SDATA_VAL_SHIFT)

/* Bitfield definition for register of struct array CH: SDFIFO */
/*
 * VAL (RO)
 *
 * FIFO Data
 */
#define SDMV2_CH_SDFIFO_VAL_MASK (0xFFFFFFFFUL)
#define SDMV2_CH_SDFIFO_VAL_SHIFT (0U)
#define SDMV2_CH_SDFIFO_VAL_GET(x) (((uint32_t)(x) & SDMV2_CH_SDFIFO_VAL_MASK) >> SDMV2_CH_SDFIFO_VAL_SHIFT)

/* Bitfield definition for register of struct array CH: SCAMP */
/*
 * VAL (RO)
 *
 * instant Amplitude Results
 */
#define SDMV2_CH_SCAMP_VAL_MASK (0xFFFFU)
#define SDMV2_CH_SCAMP_VAL_SHIFT (0U)
#define SDMV2_CH_SCAMP_VAL_GET(x) (((uint32_t)(x) & SDMV2_CH_SCAMP_VAL_MASK) >> SDMV2_CH_SCAMP_VAL_SHIFT)

/* Bitfield definition for register of struct array CH: SCHTL */
/*
 * VAL (RW)
 *
 * Amplitude Threshold for High Limit
 */
#define SDMV2_CH_SCHTL_VAL_MASK (0xFFFFU)
#define SDMV2_CH_SCHTL_VAL_SHIFT (0U)
#define SDMV2_CH_SCHTL_VAL_SET(x) (((uint32_t)(x) << SDMV2_CH_SCHTL_VAL_SHIFT) & SDMV2_CH_SCHTL_VAL_MASK)
#define SDMV2_CH_SCHTL_VAL_GET(x) (((uint32_t)(x) & SDMV2_CH_SCHTL_VAL_MASK) >> SDMV2_CH_SCHTL_VAL_SHIFT)

/* Bitfield definition for register of struct array CH: SCHTLZ */
/*
 * VAL (RW)
 *
 * Amplitude Threshold for zero crossing
 */
#define SDMV2_CH_SCHTLZ_VAL_MASK (0xFFFFU)
#define SDMV2_CH_SCHTLZ_VAL_SHIFT (0U)
#define SDMV2_CH_SCHTLZ_VAL_SET(x) (((uint32_t)(x) << SDMV2_CH_SCHTLZ_VAL_SHIFT) & SDMV2_CH_SCHTLZ_VAL_MASK)
#define SDMV2_CH_SCHTLZ_VAL_GET(x) (((uint32_t)(x) & SDMV2_CH_SCHTLZ_VAL_MASK) >> SDMV2_CH_SCHTLZ_VAL_SHIFT)

/* Bitfield definition for register of struct array CH: SCLLT */
/*
 * VAL (RW)
 *
 * Amplitude Threshold for low limit
 */
#define SDMV2_CH_SCLLT_VAL_MASK (0xFFFFU)
#define SDMV2_CH_SCLLT_VAL_SHIFT (0U)
#define SDMV2_CH_SCLLT_VAL_SET(x) (((uint32_t)(x) << SDMV2_CH_SCLLT_VAL_SHIFT) & SDMV2_CH_SCLLT_VAL_MASK)
#define SDMV2_CH_SCLLT_VAL_GET(x) (((uint32_t)(x) & SDMV2_CH_SCLLT_VAL_MASK) >> SDMV2_CH_SCLLT_VAL_SHIFT)

/* Bitfield definition for register of struct array CH: SCCTRL */
/*
 * 2ND_SGD_ORDR (RW)
 *
 * CIC decimation ratio. 0 means div-by-256
 */
#define SDMV2_CH_SCCTRL_2ND_SGD_ORDR_MASK (0xFF000000UL)
#define SDMV2_CH_SCCTRL_2ND_SGD_ORDR_SHIFT (24U)
#define SDMV2_CH_SCCTRL_2ND_SGD_ORDR_SET(x) (((uint32_t)(x) << SDMV2_CH_SCCTRL_2ND_SGD_ORDR_SHIFT) & SDMV2_CH_SCCTRL_2ND_SGD_ORDR_MASK)
#define SDMV2_CH_SCCTRL_2ND_SGD_ORDR_GET(x) (((uint32_t)(x) & SDMV2_CH_SCCTRL_2ND_SGD_ORDR_MASK) >> SDMV2_CH_SCCTRL_2ND_SGD_ORDR_SHIFT)

/*
 * HZ_EN (RW)
 *
 * Zero Crossing Enable
 */
#define SDMV2_CH_SCCTRL_HZ_EN_MASK (0x800000UL)
#define SDMV2_CH_SCCTRL_HZ_EN_SHIFT (23U)
#define SDMV2_CH_SCCTRL_HZ_EN_SET(x) (((uint32_t)(x) << SDMV2_CH_SCCTRL_HZ_EN_SHIFT) & SDMV2_CH_SCCTRL_HZ_EN_MASK)
#define SDMV2_CH_SCCTRL_HZ_EN_GET(x) (((uint32_t)(x) & SDMV2_CH_SCCTRL_HZ_EN_MASK) >> SDMV2_CH_SCCTRL_HZ_EN_SHIFT)

/*
 * MF_IE (RW)
 *
 * Module failure Interrupt enable
 */
#define SDMV2_CH_SCCTRL_MF_IE_MASK (0x400000UL)
#define SDMV2_CH_SCCTRL_MF_IE_SHIFT (22U)
#define SDMV2_CH_SCCTRL_MF_IE_SET(x) (((uint32_t)(x) << SDMV2_CH_SCCTRL_MF_IE_SHIFT) & SDMV2_CH_SCCTRL_MF_IE_MASK)
#define SDMV2_CH_SCCTRL_MF_IE_GET(x) (((uint32_t)(x) & SDMV2_CH_SCCTRL_MF_IE_MASK) >> SDMV2_CH_SCCTRL_MF_IE_SHIFT)

/*
 * HL_IE (RW)
 *
 * HLT Interrupt Enable
 */
#define SDMV2_CH_SCCTRL_HL_IE_MASK (0x200000UL)
#define SDMV2_CH_SCCTRL_HL_IE_SHIFT (21U)
#define SDMV2_CH_SCCTRL_HL_IE_SET(x) (((uint32_t)(x) << SDMV2_CH_SCCTRL_HL_IE_SHIFT) & SDMV2_CH_SCCTRL_HL_IE_MASK)
#define SDMV2_CH_SCCTRL_HL_IE_GET(x) (((uint32_t)(x) & SDMV2_CH_SCCTRL_HL_IE_MASK) >> SDMV2_CH_SCCTRL_HL_IE_SHIFT)

/*
 * LL_IE (RW)
 *
 * LLT interrupt Enable
 */
#define SDMV2_CH_SCCTRL_LL_IE_MASK (0x100000UL)
#define SDMV2_CH_SCCTRL_LL_IE_SHIFT (20U)
#define SDMV2_CH_SCCTRL_LL_IE_SET(x) (((uint32_t)(x) << SDMV2_CH_SCCTRL_LL_IE_SHIFT) & SDMV2_CH_SCCTRL_LL_IE_MASK)
#define SDMV2_CH_SCCTRL_LL_IE_GET(x) (((uint32_t)(x) & SDMV2_CH_SCCTRL_LL_IE_MASK) >> SDMV2_CH_SCCTRL_LL_IE_SHIFT)

/*
 * SGD_ORDR (RW)
 *
 * CIC order
 * 0: SYNC1
 * 1: SYNC2
 * 2: SYNC3
 * 3: FAST_SYNC
 */
#define SDMV2_CH_SCCTRL_SGD_ORDR_MASK (0xC0000UL)
#define SDMV2_CH_SCCTRL_SGD_ORDR_SHIFT (18U)
#define SDMV2_CH_SCCTRL_SGD_ORDR_SET(x) (((uint32_t)(x) << SDMV2_CH_SCCTRL_SGD_ORDR_SHIFT) & SDMV2_CH_SCCTRL_SGD_ORDR_MASK)
#define SDMV2_CH_SCCTRL_SGD_ORDR_GET(x) (((uint32_t)(x) & SDMV2_CH_SCCTRL_SGD_ORDR_MASK) >> SDMV2_CH_SCCTRL_SGD_ORDR_SHIFT)

/*
 * CIC_DEC_RATIO (RW)
 *
 * CIC decimation ratio. 0 means div-by-32
 */
#define SDMV2_CH_SCCTRL_CIC_DEC_RATIO_MASK (0x1F0U)
#define SDMV2_CH_SCCTRL_CIC_DEC_RATIO_SHIFT (4U)
#define SDMV2_CH_SCCTRL_CIC_DEC_RATIO_SET(x) (((uint32_t)(x) << SDMV2_CH_SCCTRL_CIC_DEC_RATIO_SHIFT) & SDMV2_CH_SCCTRL_CIC_DEC_RATIO_MASK)
#define SDMV2_CH_SCCTRL_CIC_DEC_RATIO_GET(x) (((uint32_t)(x) & SDMV2_CH_SCCTRL_CIC_DEC_RATIO_MASK) >> SDMV2_CH_SCCTRL_CIC_DEC_RATIO_SHIFT)

/*
 * IGN_INI_SAMPLES (RW)
 *
 * NotZero: Ignore the first samples that are not accurate
 * Zero: Use all samples
 */
#define SDMV2_CH_SCCTRL_IGN_INI_SAMPLES_MASK (0xEU)
#define SDMV2_CH_SCCTRL_IGN_INI_SAMPLES_SHIFT (1U)
#define SDMV2_CH_SCCTRL_IGN_INI_SAMPLES_SET(x) (((uint32_t)(x) << SDMV2_CH_SCCTRL_IGN_INI_SAMPLES_SHIFT) & SDMV2_CH_SCCTRL_IGN_INI_SAMPLES_MASK)
#define SDMV2_CH_SCCTRL_IGN_INI_SAMPLES_GET(x) (((uint32_t)(x) & SDMV2_CH_SCCTRL_IGN_INI_SAMPLES_MASK) >> SDMV2_CH_SCCTRL_IGN_INI_SAMPLES_SHIFT)

/*
 * EN (RW)
 *
 * Amplitude Path Enable
 */
#define SDMV2_CH_SCCTRL_EN_MASK (0x1U)
#define SDMV2_CH_SCCTRL_EN_SHIFT (0U)
#define SDMV2_CH_SCCTRL_EN_SET(x) (((uint32_t)(x) << SDMV2_CH_SCCTRL_EN_SHIFT) & SDMV2_CH_SCCTRL_EN_MASK)
#define SDMV2_CH_SCCTRL_EN_GET(x) (((uint32_t)(x) & SDMV2_CH_SCCTRL_EN_MASK) >> SDMV2_CH_SCCTRL_EN_SHIFT)

/* Bitfield definition for register of struct array CH: SCST */
/*
 * HZ (W1C)
 *
 * Amplitude rising above HZ event found.
 */
#define SDMV2_CH_SCST_HZ_MASK (0x8U)
#define SDMV2_CH_SCST_HZ_SHIFT (3U)
#define SDMV2_CH_SCST_HZ_SET(x) (((uint32_t)(x) << SDMV2_CH_SCST_HZ_SHIFT) & SDMV2_CH_SCST_HZ_MASK)
#define SDMV2_CH_SCST_HZ_GET(x) (((uint32_t)(x) & SDMV2_CH_SCST_HZ_MASK) >> SDMV2_CH_SCST_HZ_SHIFT)

/*
 * MF (W1C)
 *
 * power modulator Failure found. MCLK not found. Error flag.
 */
#define SDMV2_CH_SCST_MF_MASK (0x4U)
#define SDMV2_CH_SCST_MF_SHIFT (2U)
#define SDMV2_CH_SCST_MF_SET(x) (((uint32_t)(x) << SDMV2_CH_SCST_MF_SHIFT) & SDMV2_CH_SCST_MF_MASK)
#define SDMV2_CH_SCST_MF_GET(x) (((uint32_t)(x) & SDMV2_CH_SCST_MF_MASK) >> SDMV2_CH_SCST_MF_SHIFT)

/*
 * CMPH (W1C)
 *
 * HLT out of range. Error flag.
 */
#define SDMV2_CH_SCST_CMPH_MASK (0x2U)
#define SDMV2_CH_SCST_CMPH_SHIFT (1U)
#define SDMV2_CH_SCST_CMPH_SET(x) (((uint32_t)(x) << SDMV2_CH_SCST_CMPH_SHIFT) & SDMV2_CH_SCST_CMPH_MASK)
#define SDMV2_CH_SCST_CMPH_GET(x) (((uint32_t)(x) & SDMV2_CH_SCST_CMPH_MASK) >> SDMV2_CH_SCST_CMPH_SHIFT)

/*
 * CMPL (W1C)
 *
 * LLT out of range. Error flag.
 */
#define SDMV2_CH_SCST_CMPL_MASK (0x1U)
#define SDMV2_CH_SCST_CMPL_SHIFT (0U)
#define SDMV2_CH_SCST_CMPL_SET(x) (((uint32_t)(x) << SDMV2_CH_SCST_CMPL_SHIFT) & SDMV2_CH_SCST_CMPL_MASK)
#define SDMV2_CH_SCST_CMPL_GET(x) (((uint32_t)(x) & SDMV2_CH_SCST_CMPL_MASK) >> SDMV2_CH_SCST_CMPL_SHIFT)



/* CH register group index macro definition */
#define SDMV2_CH_0 (0UL)


#endif /* HPM_SDMV2_H */
