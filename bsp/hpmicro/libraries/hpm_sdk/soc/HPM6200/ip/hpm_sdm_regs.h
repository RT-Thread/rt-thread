/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_SDM_H
#define HPM_SDM_H

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
    } CH[4];
} SDM_Type;


/* Bitfield definition for register: CTRL */
/*
 * SFTRST (RW)
 *
 * software reset the module if asserted to be1’b1.
 */
#define SDM_CTRL_SFTRST_MASK (0x80000000UL)
#define SDM_CTRL_SFTRST_SHIFT (31U)
#define SDM_CTRL_SFTRST_SET(x) (((uint32_t)(x) << SDM_CTRL_SFTRST_SHIFT) & SDM_CTRL_SFTRST_MASK)
#define SDM_CTRL_SFTRST_GET(x) (((uint32_t)(x) & SDM_CTRL_SFTRST_MASK) >> SDM_CTRL_SFTRST_SHIFT)

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
#define SDM_CTRL_CHMD_MASK (0x3FFC000UL)
#define SDM_CTRL_CHMD_SHIFT (14U)
#define SDM_CTRL_CHMD_SET(x) (((uint32_t)(x) << SDM_CTRL_CHMD_SHIFT) & SDM_CTRL_CHMD_MASK)
#define SDM_CTRL_CHMD_GET(x) (((uint32_t)(x) & SDM_CTRL_CHMD_MASK) >> SDM_CTRL_CHMD_SHIFT)

/*
 * SYNC_MCLK (RW)
 *
 * Asserted to double sync the mclk input pin before its usage inside the module
 */
#define SDM_CTRL_SYNC_MCLK_MASK (0x3C00U)
#define SDM_CTRL_SYNC_MCLK_SHIFT (10U)
#define SDM_CTRL_SYNC_MCLK_SET(x) (((uint32_t)(x) << SDM_CTRL_SYNC_MCLK_SHIFT) & SDM_CTRL_SYNC_MCLK_MASK)
#define SDM_CTRL_SYNC_MCLK_GET(x) (((uint32_t)(x) & SDM_CTRL_SYNC_MCLK_MASK) >> SDM_CTRL_SYNC_MCLK_SHIFT)

/*
 * SYNC_MDAT (RW)
 *
 * Asserted to double sync the mdat input pin before its usage inside the module
 */
#define SDM_CTRL_SYNC_MDAT_MASK (0x3C0U)
#define SDM_CTRL_SYNC_MDAT_SHIFT (6U)
#define SDM_CTRL_SYNC_MDAT_SET(x) (((uint32_t)(x) << SDM_CTRL_SYNC_MDAT_SHIFT) & SDM_CTRL_SYNC_MDAT_MASK)
#define SDM_CTRL_SYNC_MDAT_GET(x) (((uint32_t)(x) & SDM_CTRL_SYNC_MDAT_MASK) >> SDM_CTRL_SYNC_MDAT_SHIFT)

/*
 * CH_EN (RW)
 *
 * Channel Enable
 */
#define SDM_CTRL_CH_EN_MASK (0x3CU)
#define SDM_CTRL_CH_EN_SHIFT (2U)
#define SDM_CTRL_CH_EN_SET(x) (((uint32_t)(x) << SDM_CTRL_CH_EN_SHIFT) & SDM_CTRL_CH_EN_MASK)
#define SDM_CTRL_CH_EN_GET(x) (((uint32_t)(x) & SDM_CTRL_CH_EN_MASK) >> SDM_CTRL_CH_EN_SHIFT)

/*
 * IE (RW)
 *
 * Interrupt Enable
 */
#define SDM_CTRL_IE_MASK (0x2U)
#define SDM_CTRL_IE_SHIFT (1U)
#define SDM_CTRL_IE_SET(x) (((uint32_t)(x) << SDM_CTRL_IE_SHIFT) & SDM_CTRL_IE_MASK)
#define SDM_CTRL_IE_GET(x) (((uint32_t)(x) & SDM_CTRL_IE_MASK) >> SDM_CTRL_IE_SHIFT)

/* Bitfield definition for register: INT_EN */
/*
 * CH3DRY (RW)
 *
 * Ch3 Data Ready interrupt enable.
 */
#define SDM_INT_EN_CH3DRY_MASK (0x80U)
#define SDM_INT_EN_CH3DRY_SHIFT (7U)
#define SDM_INT_EN_CH3DRY_SET(x) (((uint32_t)(x) << SDM_INT_EN_CH3DRY_SHIFT) & SDM_INT_EN_CH3DRY_MASK)
#define SDM_INT_EN_CH3DRY_GET(x) (((uint32_t)(x) & SDM_INT_EN_CH3DRY_MASK) >> SDM_INT_EN_CH3DRY_SHIFT)

/*
 * CH2DRY (RW)
 *
 * Ch2 Data Ready interrupt enable
 */
#define SDM_INT_EN_CH2DRY_MASK (0x40U)
#define SDM_INT_EN_CH2DRY_SHIFT (6U)
#define SDM_INT_EN_CH2DRY_SET(x) (((uint32_t)(x) << SDM_INT_EN_CH2DRY_SHIFT) & SDM_INT_EN_CH2DRY_MASK)
#define SDM_INT_EN_CH2DRY_GET(x) (((uint32_t)(x) & SDM_INT_EN_CH2DRY_MASK) >> SDM_INT_EN_CH2DRY_SHIFT)

/*
 * CH1DRY (RW)
 *
 * Ch1 Data Ready interrupt enable
 */
#define SDM_INT_EN_CH1DRY_MASK (0x20U)
#define SDM_INT_EN_CH1DRY_SHIFT (5U)
#define SDM_INT_EN_CH1DRY_SET(x) (((uint32_t)(x) << SDM_INT_EN_CH1DRY_SHIFT) & SDM_INT_EN_CH1DRY_MASK)
#define SDM_INT_EN_CH1DRY_GET(x) (((uint32_t)(x) & SDM_INT_EN_CH1DRY_MASK) >> SDM_INT_EN_CH1DRY_SHIFT)

/*
 * CH0DRY (RW)
 *
 * Ch0 Data Ready interrupt enable
 */
#define SDM_INT_EN_CH0DRY_MASK (0x10U)
#define SDM_INT_EN_CH0DRY_SHIFT (4U)
#define SDM_INT_EN_CH0DRY_SET(x) (((uint32_t)(x) << SDM_INT_EN_CH0DRY_SHIFT) & SDM_INT_EN_CH0DRY_MASK)
#define SDM_INT_EN_CH0DRY_GET(x) (((uint32_t)(x) & SDM_INT_EN_CH0DRY_MASK) >> SDM_INT_EN_CH0DRY_SHIFT)

/*
 * CH3ERR (RW)
 *
 * Ch3 Error interrupt enable.
 */
#define SDM_INT_EN_CH3ERR_MASK (0x8U)
#define SDM_INT_EN_CH3ERR_SHIFT (3U)
#define SDM_INT_EN_CH3ERR_SET(x) (((uint32_t)(x) << SDM_INT_EN_CH3ERR_SHIFT) & SDM_INT_EN_CH3ERR_MASK)
#define SDM_INT_EN_CH3ERR_GET(x) (((uint32_t)(x) & SDM_INT_EN_CH3ERR_MASK) >> SDM_INT_EN_CH3ERR_SHIFT)

/*
 * CH2ERR (RW)
 *
 * Ch2 Error interrupt enable
 */
#define SDM_INT_EN_CH2ERR_MASK (0x4U)
#define SDM_INT_EN_CH2ERR_SHIFT (2U)
#define SDM_INT_EN_CH2ERR_SET(x) (((uint32_t)(x) << SDM_INT_EN_CH2ERR_SHIFT) & SDM_INT_EN_CH2ERR_MASK)
#define SDM_INT_EN_CH2ERR_GET(x) (((uint32_t)(x) & SDM_INT_EN_CH2ERR_MASK) >> SDM_INT_EN_CH2ERR_SHIFT)

/*
 * CH1ERR (RW)
 *
 * Ch1 Error interrupt enable
 */
#define SDM_INT_EN_CH1ERR_MASK (0x2U)
#define SDM_INT_EN_CH1ERR_SHIFT (1U)
#define SDM_INT_EN_CH1ERR_SET(x) (((uint32_t)(x) << SDM_INT_EN_CH1ERR_SHIFT) & SDM_INT_EN_CH1ERR_MASK)
#define SDM_INT_EN_CH1ERR_GET(x) (((uint32_t)(x) & SDM_INT_EN_CH1ERR_MASK) >> SDM_INT_EN_CH1ERR_SHIFT)

/*
 * CH0ERR (RW)
 *
 * Ch0 Error interrupt enable
 */
#define SDM_INT_EN_CH0ERR_MASK (0x1U)
#define SDM_INT_EN_CH0ERR_SHIFT (0U)
#define SDM_INT_EN_CH0ERR_SET(x) (((uint32_t)(x) << SDM_INT_EN_CH0ERR_SHIFT) & SDM_INT_EN_CH0ERR_MASK)
#define SDM_INT_EN_CH0ERR_GET(x) (((uint32_t)(x) & SDM_INT_EN_CH0ERR_MASK) >> SDM_INT_EN_CH0ERR_SHIFT)

/* Bitfield definition for register: STATUS */
/*
 * CH3DRY (RO)
 *
 * Ch3 Data Ready.
 * De-assert this bit by reading the data (or data fifo) registers.
 */
#define SDM_STATUS_CH3DRY_MASK (0x80U)
#define SDM_STATUS_CH3DRY_SHIFT (7U)
#define SDM_STATUS_CH3DRY_GET(x) (((uint32_t)(x) & SDM_STATUS_CH3DRY_MASK) >> SDM_STATUS_CH3DRY_SHIFT)

/*
 * CH2DRY (RO)
 *
 * Ch2 Data Ready
 */
#define SDM_STATUS_CH2DRY_MASK (0x40U)
#define SDM_STATUS_CH2DRY_SHIFT (6U)
#define SDM_STATUS_CH2DRY_GET(x) (((uint32_t)(x) & SDM_STATUS_CH2DRY_MASK) >> SDM_STATUS_CH2DRY_SHIFT)

/*
 * CH1DRY (RO)
 *
 * Ch1 Data Ready
 */
#define SDM_STATUS_CH1DRY_MASK (0x20U)
#define SDM_STATUS_CH1DRY_SHIFT (5U)
#define SDM_STATUS_CH1DRY_GET(x) (((uint32_t)(x) & SDM_STATUS_CH1DRY_MASK) >> SDM_STATUS_CH1DRY_SHIFT)

/*
 * CH0DRY (RO)
 *
 * Ch0 Data Ready
 */
#define SDM_STATUS_CH0DRY_MASK (0x10U)
#define SDM_STATUS_CH0DRY_SHIFT (4U)
#define SDM_STATUS_CH0DRY_GET(x) (((uint32_t)(x) & SDM_STATUS_CH0DRY_MASK) >> SDM_STATUS_CH0DRY_SHIFT)

/*
 * CH3ERR (RO)
 *
 * Ch3 Error.
 * ORed together by channel related error signals and corresponding error interrupt enable signals.
 * De-assert this bit by write-1-clear the corresponding error status bits in the channel status registers.
 */
#define SDM_STATUS_CH3ERR_MASK (0x8U)
#define SDM_STATUS_CH3ERR_SHIFT (3U)
#define SDM_STATUS_CH3ERR_GET(x) (((uint32_t)(x) & SDM_STATUS_CH3ERR_MASK) >> SDM_STATUS_CH3ERR_SHIFT)

/*
 * CH2ERR (RO)
 *
 * Ch2 Error
 */
#define SDM_STATUS_CH2ERR_MASK (0x4U)
#define SDM_STATUS_CH2ERR_SHIFT (2U)
#define SDM_STATUS_CH2ERR_GET(x) (((uint32_t)(x) & SDM_STATUS_CH2ERR_MASK) >> SDM_STATUS_CH2ERR_SHIFT)

/*
 * CH1ERR (RO)
 *
 * Ch1 Error
 */
#define SDM_STATUS_CH1ERR_MASK (0x2U)
#define SDM_STATUS_CH1ERR_SHIFT (1U)
#define SDM_STATUS_CH1ERR_GET(x) (((uint32_t)(x) & SDM_STATUS_CH1ERR_MASK) >> SDM_STATUS_CH1ERR_SHIFT)

/*
 * CH0ERR (RO)
 *
 * Ch0 Error
 */
#define SDM_STATUS_CH0ERR_MASK (0x1U)
#define SDM_STATUS_CH0ERR_SHIFT (0U)
#define SDM_STATUS_CH0ERR_GET(x) (((uint32_t)(x) & SDM_STATUS_CH0ERR_MASK) >> SDM_STATUS_CH0ERR_SHIFT)

/* Bitfield definition for register of struct array CH: SDFIFOCTRL */
/*
 * GATE_SAMPLES (RW)
 *
 * The number-1-3 of input PDM bit samples to be gated when CIC_GATE_EN=1. Max 255. So the minimum gated samples is 4 samples when GATE_SAMPLES=0.
 */
#define SDM_CH_SDFIFOCTRL_GATE_SAMPLES_MASK (0xFF0000UL)
#define SDM_CH_SDFIFOCTRL_GATE_SAMPLES_SHIFT (16U)
#define SDM_CH_SDFIFOCTRL_GATE_SAMPLES_SET(x) (((uint32_t)(x) << SDM_CH_SDFIFOCTRL_GATE_SAMPLES_SHIFT) & SDM_CH_SDFIFOCTRL_GATE_SAMPLES_MASK)
#define SDM_CH_SDFIFOCTRL_GATE_SAMPLES_GET(x) (((uint32_t)(x) & SDM_CH_SDFIFOCTRL_GATE_SAMPLES_MASK) >> SDM_CH_SDFIFOCTRL_GATE_SAMPLES_SHIFT)

/*
 * THRSH (RW)
 *
 * FIFO threshold (0,..,16) (fillings > threshold, then gen int)
 */
#define SDM_CH_SDFIFOCTRL_THRSH_MASK (0x1F0U)
#define SDM_CH_SDFIFOCTRL_THRSH_SHIFT (4U)
#define SDM_CH_SDFIFOCTRL_THRSH_SET(x) (((uint32_t)(x) << SDM_CH_SDFIFOCTRL_THRSH_SHIFT) & SDM_CH_SDFIFOCTRL_THRSH_MASK)
#define SDM_CH_SDFIFOCTRL_THRSH_GET(x) (((uint32_t)(x) & SDM_CH_SDFIFOCTRL_THRSH_MASK) >> SDM_CH_SDFIFOCTRL_THRSH_SHIFT)

/*
 * D_RDY_INT_EN (RW)
 *
 * FIFO data ready interrupt enable
 */
#define SDM_CH_SDFIFOCTRL_D_RDY_INT_EN_MASK (0x4U)
#define SDM_CH_SDFIFOCTRL_D_RDY_INT_EN_SHIFT (2U)
#define SDM_CH_SDFIFOCTRL_D_RDY_INT_EN_SET(x) (((uint32_t)(x) << SDM_CH_SDFIFOCTRL_D_RDY_INT_EN_SHIFT) & SDM_CH_SDFIFOCTRL_D_RDY_INT_EN_MASK)
#define SDM_CH_SDFIFOCTRL_D_RDY_INT_EN_GET(x) (((uint32_t)(x) & SDM_CH_SDFIFOCTRL_D_RDY_INT_EN_MASK) >> SDM_CH_SDFIFOCTRL_D_RDY_INT_EN_SHIFT)

/* Bitfield definition for register of struct array CH: SDCTRLP */
/*
 * MANCH_THR (RW)
 *
 * Manchester Decoding threshold. 3/4 of PERIOD_MCLK[7:0]
 */
#define SDM_CH_SDCTRLP_MANCH_THR_MASK (0xFE000000UL)
#define SDM_CH_SDCTRLP_MANCH_THR_SHIFT (25U)
#define SDM_CH_SDCTRLP_MANCH_THR_SET(x) (((uint32_t)(x) << SDM_CH_SDCTRLP_MANCH_THR_SHIFT) & SDM_CH_SDCTRLP_MANCH_THR_MASK)
#define SDM_CH_SDCTRLP_MANCH_THR_GET(x) (((uint32_t)(x) & SDM_CH_SDCTRLP_MANCH_THR_MASK) >> SDM_CH_SDCTRLP_MANCH_THR_SHIFT)

/*
 * WDOG_THR (RW)
 *
 * Watch dog threshold for channel failure of CLK halting
 */
#define SDM_CH_SDCTRLP_WDOG_THR_MASK (0x1FE0000UL)
#define SDM_CH_SDCTRLP_WDOG_THR_SHIFT (17U)
#define SDM_CH_SDCTRLP_WDOG_THR_SET(x) (((uint32_t)(x) << SDM_CH_SDCTRLP_WDOG_THR_SHIFT) & SDM_CH_SDCTRLP_WDOG_THR_MASK)
#define SDM_CH_SDCTRLP_WDOG_THR_GET(x) (((uint32_t)(x) & SDM_CH_SDCTRLP_WDOG_THR_MASK) >> SDM_CH_SDCTRLP_WDOG_THR_SHIFT)

/*
 * AF_IE (RW)
 *
 * Acknowledge feedback interrupt enable
 */
#define SDM_CH_SDCTRLP_AF_IE_MASK (0x10000UL)
#define SDM_CH_SDCTRLP_AF_IE_SHIFT (16U)
#define SDM_CH_SDCTRLP_AF_IE_SET(x) (((uint32_t)(x) << SDM_CH_SDCTRLP_AF_IE_SHIFT) & SDM_CH_SDCTRLP_AF_IE_MASK)
#define SDM_CH_SDCTRLP_AF_IE_GET(x) (((uint32_t)(x) & SDM_CH_SDCTRLP_AF_IE_MASK) >> SDM_CH_SDCTRLP_AF_IE_SHIFT)

/*
 * DFFOVIE (RW)
 *
 * Ch Data FIFO overflow interrupt enable
 */
#define SDM_CH_SDCTRLP_DFFOVIE_MASK (0x8000U)
#define SDM_CH_SDCTRLP_DFFOVIE_SHIFT (15U)
#define SDM_CH_SDCTRLP_DFFOVIE_SET(x) (((uint32_t)(x) << SDM_CH_SDCTRLP_DFFOVIE_SHIFT) & SDM_CH_SDCTRLP_DFFOVIE_MASK)
#define SDM_CH_SDCTRLP_DFFOVIE_GET(x) (((uint32_t)(x) & SDM_CH_SDCTRLP_DFFOVIE_MASK) >> SDM_CH_SDCTRLP_DFFOVIE_SHIFT)

/*
 * DSATIE (RW)
 *
 * Ch CIC Data Saturation Interrupt Enable
 */
#define SDM_CH_SDCTRLP_DSATIE_MASK (0x4000U)
#define SDM_CH_SDCTRLP_DSATIE_SHIFT (14U)
#define SDM_CH_SDCTRLP_DSATIE_SET(x) (((uint32_t)(x) << SDM_CH_SDCTRLP_DSATIE_SHIFT) & SDM_CH_SDCTRLP_DSATIE_MASK)
#define SDM_CH_SDCTRLP_DSATIE_GET(x) (((uint32_t)(x) & SDM_CH_SDCTRLP_DSATIE_MASK) >> SDM_CH_SDCTRLP_DSATIE_SHIFT)

/*
 * DRIE (RW)
 *
 * Ch Data Ready Interrupt Enable
 */
#define SDM_CH_SDCTRLP_DRIE_MASK (0x2000U)
#define SDM_CH_SDCTRLP_DRIE_SHIFT (13U)
#define SDM_CH_SDCTRLP_DRIE_SET(x) (((uint32_t)(x) << SDM_CH_SDCTRLP_DRIE_SHIFT) & SDM_CH_SDCTRLP_DRIE_MASK)
#define SDM_CH_SDCTRLP_DRIE_GET(x) (((uint32_t)(x) & SDM_CH_SDCTRLP_DRIE_MASK) >> SDM_CH_SDCTRLP_DRIE_SHIFT)

/*
 * SYNCSEL (RW)
 *
 * Select the PWM SYNC Source
 */
#define SDM_CH_SDCTRLP_SYNCSEL_MASK (0x1F80U)
#define SDM_CH_SDCTRLP_SYNCSEL_SHIFT (7U)
#define SDM_CH_SDCTRLP_SYNCSEL_SET(x) (((uint32_t)(x) << SDM_CH_SDCTRLP_SYNCSEL_SHIFT) & SDM_CH_SDCTRLP_SYNCSEL_MASK)
#define SDM_CH_SDCTRLP_SYNCSEL_GET(x) (((uint32_t)(x) & SDM_CH_SDCTRLP_SYNCSEL_MASK) >> SDM_CH_SDCTRLP_SYNCSEL_SHIFT)

/*
 * FFSYNCCLREN (RW)
 *
 * Auto clear FIFO when a new SDSYNC event is found. Only valid when WTSYNCEN=1
 */
#define SDM_CH_SDCTRLP_FFSYNCCLREN_MASK (0x40U)
#define SDM_CH_SDCTRLP_FFSYNCCLREN_SHIFT (6U)
#define SDM_CH_SDCTRLP_FFSYNCCLREN_SET(x) (((uint32_t)(x) << SDM_CH_SDCTRLP_FFSYNCCLREN_SHIFT) & SDM_CH_SDCTRLP_FFSYNCCLREN_MASK)
#define SDM_CH_SDCTRLP_FFSYNCCLREN_GET(x) (((uint32_t)(x) & SDM_CH_SDCTRLP_FFSYNCCLREN_MASK) >> SDM_CH_SDCTRLP_FFSYNCCLREN_SHIFT)

/*
 * WTSYNACLR (RW)
 *
 * 1: Asserted to Auto clear WTSYNFLG when the SDFFINT is gen
 * 0: WTSYNFLG should be cleared manually by WTSYNMCLR
 */
#define SDM_CH_SDCTRLP_WTSYNACLR_MASK (0x20U)
#define SDM_CH_SDCTRLP_WTSYNACLR_SHIFT (5U)
#define SDM_CH_SDCTRLP_WTSYNACLR_SET(x) (((uint32_t)(x) << SDM_CH_SDCTRLP_WTSYNACLR_SHIFT) & SDM_CH_SDCTRLP_WTSYNACLR_MASK)
#define SDM_CH_SDCTRLP_WTSYNACLR_GET(x) (((uint32_t)(x) & SDM_CH_SDCTRLP_WTSYNACLR_MASK) >> SDM_CH_SDCTRLP_WTSYNACLR_SHIFT)

/*
 * WTSYNMCLR (RW)
 *
 * 1: Manually clear WTSYNFLG. Auto-clear.
 */
#define SDM_CH_SDCTRLP_WTSYNMCLR_MASK (0x10U)
#define SDM_CH_SDCTRLP_WTSYNMCLR_SHIFT (4U)
#define SDM_CH_SDCTRLP_WTSYNMCLR_SET(x) (((uint32_t)(x) << SDM_CH_SDCTRLP_WTSYNMCLR_SHIFT) & SDM_CH_SDCTRLP_WTSYNMCLR_MASK)
#define SDM_CH_SDCTRLP_WTSYNMCLR_GET(x) (((uint32_t)(x) & SDM_CH_SDCTRLP_WTSYNMCLR_MASK) >> SDM_CH_SDCTRLP_WTSYNMCLR_SHIFT)

/*
 * WTSYNCEN (RW)
 *
 * 1: Start to store data only after PWM SYNC event
 * 0: Start to store data whenever enabled
 */
#define SDM_CH_SDCTRLP_WTSYNCEN_MASK (0x8U)
#define SDM_CH_SDCTRLP_WTSYNCEN_SHIFT (3U)
#define SDM_CH_SDCTRLP_WTSYNCEN_SET(x) (((uint32_t)(x) << SDM_CH_SDCTRLP_WTSYNCEN_SHIFT) & SDM_CH_SDCTRLP_WTSYNCEN_MASK)
#define SDM_CH_SDCTRLP_WTSYNCEN_GET(x) (((uint32_t)(x) & SDM_CH_SDCTRLP_WTSYNCEN_MASK) >> SDM_CH_SDCTRLP_WTSYNCEN_SHIFT)

/*
 * D32 (RW)
 *
 * 1:32 bit data
 * 0:16 bit data
 */
#define SDM_CH_SDCTRLP_D32_MASK (0x4U)
#define SDM_CH_SDCTRLP_D32_SHIFT (2U)
#define SDM_CH_SDCTRLP_D32_SET(x) (((uint32_t)(x) << SDM_CH_SDCTRLP_D32_SHIFT) & SDM_CH_SDCTRLP_D32_MASK)
#define SDM_CH_SDCTRLP_D32_GET(x) (((uint32_t)(x) & SDM_CH_SDCTRLP_D32_MASK) >> SDM_CH_SDCTRLP_D32_SHIFT)

/*
 * DR_OPT (RW)
 *
 * 1: Use Data FIFO Ready as data ready when fifo fillings are greater than the threshold
 * 0: Use Data Reg Ready as data ready
 */
#define SDM_CH_SDCTRLP_DR_OPT_MASK (0x2U)
#define SDM_CH_SDCTRLP_DR_OPT_SHIFT (1U)
#define SDM_CH_SDCTRLP_DR_OPT_SET(x) (((uint32_t)(x) << SDM_CH_SDCTRLP_DR_OPT_SHIFT) & SDM_CH_SDCTRLP_DR_OPT_MASK)
#define SDM_CH_SDCTRLP_DR_OPT_GET(x) (((uint32_t)(x) & SDM_CH_SDCTRLP_DR_OPT_MASK) >> SDM_CH_SDCTRLP_DR_OPT_SHIFT)

/*
 * EN (RW)
 *
 * Data Path Enable
 */
#define SDM_CH_SDCTRLP_EN_MASK (0x1U)
#define SDM_CH_SDCTRLP_EN_SHIFT (0U)
#define SDM_CH_SDCTRLP_EN_SET(x) (((uint32_t)(x) << SDM_CH_SDCTRLP_EN_SHIFT) & SDM_CH_SDCTRLP_EN_MASK)
#define SDM_CH_SDCTRLP_EN_GET(x) (((uint32_t)(x) & SDM_CH_SDCTRLP_EN_MASK) >> SDM_CH_SDCTRLP_EN_SHIFT)

/* Bitfield definition for register of struct array CH: SDCTRLE */
/*
 * CIC_GATE_TYPE (RW)
 *
 * 1: the gate cycle is determined by SDFIFOCTRLn[GATE_SAMPLES].
 * 0: the gate cycle is determined by the CIC decimation counter, and the minimal gated off PDM bits are determined by SDFIFOCTRLn[GATE_SAMPLES], and at the same time, to keep alignment with normal PCM sampling time.
 */
#define SDM_CH_SDCTRLE_CIC_GATE_TYPE_MASK (0x80000000UL)
#define SDM_CH_SDCTRLE_CIC_GATE_TYPE_SHIFT (31U)
#define SDM_CH_SDCTRLE_CIC_GATE_TYPE_SET(x) (((uint32_t)(x) << SDM_CH_SDCTRLE_CIC_GATE_TYPE_SHIFT) & SDM_CH_SDCTRLE_CIC_GATE_TYPE_MASK)
#define SDM_CH_SDCTRLE_CIC_GATE_TYPE_GET(x) (((uint32_t)(x) & SDM_CH_SDCTRLE_CIC_GATE_TYPE_MASK) >> SDM_CH_SDCTRLE_CIC_GATE_TYPE_SHIFT)

/*
 * CIC_GATE_POL (RW)
 *
 * 1: When mask signal is 1, pause the CIC stage at he rising edge of mask signal.
 * 0: When mask signal is 0, pause the CIC stage at he falling edge of mask signal.
 */
#define SDM_CH_SDCTRLE_CIC_GATE_POL_MASK (0x40000000UL)
#define SDM_CH_SDCTRLE_CIC_GATE_POL_SHIFT (30U)
#define SDM_CH_SDCTRLE_CIC_GATE_POL_SET(x) (((uint32_t)(x) << SDM_CH_SDCTRLE_CIC_GATE_POL_SHIFT) & SDM_CH_SDCTRLE_CIC_GATE_POL_MASK)
#define SDM_CH_SDCTRLE_CIC_GATE_POL_GET(x) (((uint32_t)(x) & SDM_CH_SDCTRLE_CIC_GATE_POL_MASK) >> SDM_CH_SDCTRLE_CIC_GATE_POL_SHIFT)

/*
 * CIC_GATE_SEL (RW)
 *
 * Select the mask signal for CIC gate signal.
 */
#define SDM_CH_SDCTRLE_CIC_GATE_SEL_MASK (0x3C000000UL)
#define SDM_CH_SDCTRLE_CIC_GATE_SEL_SHIFT (26U)
#define SDM_CH_SDCTRLE_CIC_GATE_SEL_SET(x) (((uint32_t)(x) << SDM_CH_SDCTRLE_CIC_GATE_SEL_SHIFT) & SDM_CH_SDCTRLE_CIC_GATE_SEL_MASK)
#define SDM_CH_SDCTRLE_CIC_GATE_SEL_GET(x) (((uint32_t)(x) & SDM_CH_SDCTRLE_CIC_GATE_SEL_MASK) >> SDM_CH_SDCTRLE_CIC_GATE_SEL_SHIFT)

/*
 * CIC_GATE_EN (RW)
 *
 * 1: the CIC stage can be paused by the mask input.
 * 0: the CIC stage won't be paused by the mask input.
 */
#define SDM_CH_SDCTRLE_CIC_GATE_EN_MASK (0x2000000UL)
#define SDM_CH_SDCTRLE_CIC_GATE_EN_SHIFT (25U)
#define SDM_CH_SDCTRLE_CIC_GATE_EN_SET(x) (((uint32_t)(x) << SDM_CH_SDCTRLE_CIC_GATE_EN_SHIFT) & SDM_CH_SDCTRLE_CIC_GATE_EN_MASK)
#define SDM_CH_SDCTRLE_CIC_GATE_EN_GET(x) (((uint32_t)(x) & SDM_CH_SDCTRLE_CIC_GATE_EN_MASK) >> SDM_CH_SDCTRLE_CIC_GATE_EN_SHIFT)

/*
 * TIMESTAMP_TYPE (RW)
 *
 * 1. Use the time (when the data is calculated out) - delta_time_of_filter_span as the timestamp.
 * 0: Use the time when the data is calculated out.
 */
#define SDM_CH_SDCTRLE_TIMESTAMP_TYPE_MASK (0x400000UL)
#define SDM_CH_SDCTRLE_TIMESTAMP_TYPE_SHIFT (22U)
#define SDM_CH_SDCTRLE_TIMESTAMP_TYPE_SET(x) (((uint32_t)(x) << SDM_CH_SDCTRLE_TIMESTAMP_TYPE_SHIFT) & SDM_CH_SDCTRLE_TIMESTAMP_TYPE_MASK)
#define SDM_CH_SDCTRLE_TIMESTAMP_TYPE_GET(x) (((uint32_t)(x) & SDM_CH_SDCTRLE_TIMESTAMP_TYPE_MASK) >> SDM_CH_SDCTRLE_TIMESTAMP_TYPE_SHIFT)

/*
 * DFIFO_S_T (RW)
 *
 * 1: the output of SDFIFO is data and timestamp interleaved. First is data.
 * 0: the output of SDFIFO is data only
 */
#define SDM_CH_SDCTRLE_DFIFO_S_T_MASK (0x200000UL)
#define SDM_CH_SDCTRLE_DFIFO_S_T_SHIFT (21U)
#define SDM_CH_SDCTRLE_DFIFO_S_T_SET(x) (((uint32_t)(x) << SDM_CH_SDCTRLE_DFIFO_S_T_SHIFT) & SDM_CH_SDCTRLE_DFIFO_S_T_MASK)
#define SDM_CH_SDCTRLE_DFIFO_S_T_GET(x) (((uint32_t)(x) & SDM_CH_SDCTRLE_DFIFO_S_T_MASK) >> SDM_CH_SDCTRLE_DFIFO_S_T_SHIFT)

/*
 * DATA_S_T (RW)
 *
 * "1: the read output of SData is data and timestamp interleaved. First is data.
 * 0: the read output of SData is data only"
 */
#define SDM_CH_SDCTRLE_DATA_S_T_MASK (0x100000UL)
#define SDM_CH_SDCTRLE_DATA_S_T_SHIFT (20U)
#define SDM_CH_SDCTRLE_DATA_S_T_SET(x) (((uint32_t)(x) << SDM_CH_SDCTRLE_DATA_S_T_SHIFT) & SDM_CH_SDCTRLE_DATA_S_T_MASK)
#define SDM_CH_SDCTRLE_DATA_S_T_GET(x) (((uint32_t)(x) & SDM_CH_SDCTRLE_DATA_S_T_MASK) >> SDM_CH_SDCTRLE_DATA_S_T_SHIFT)

/*
 * SGD_ORDR (RW)
 *
 * CIC order
 * 0: SYNC1
 * 1: SYNC2
 * 2: SYNC3
 * 3: FAST_SYNC
 */
#define SDM_CH_SDCTRLE_SGD_ORDR_MASK (0x60000UL)
#define SDM_CH_SDCTRLE_SGD_ORDR_SHIFT (17U)
#define SDM_CH_SDCTRLE_SGD_ORDR_SET(x) (((uint32_t)(x) << SDM_CH_SDCTRLE_SGD_ORDR_SHIFT) & SDM_CH_SDCTRLE_SGD_ORDR_MASK)
#define SDM_CH_SDCTRLE_SGD_ORDR_GET(x) (((uint32_t)(x) & SDM_CH_SDCTRLE_SGD_ORDR_MASK) >> SDM_CH_SDCTRLE_SGD_ORDR_SHIFT)

/*
 * PWMSYNC (RW)
 *
 * Asserted to double sync the PWM trigger signal
 */
#define SDM_CH_SDCTRLE_PWMSYNC_MASK (0x10000UL)
#define SDM_CH_SDCTRLE_PWMSYNC_SHIFT (16U)
#define SDM_CH_SDCTRLE_PWMSYNC_SET(x) (((uint32_t)(x) << SDM_CH_SDCTRLE_PWMSYNC_SHIFT) & SDM_CH_SDCTRLE_PWMSYNC_MASK)
#define SDM_CH_SDCTRLE_PWMSYNC_GET(x) (((uint32_t)(x) & SDM_CH_SDCTRLE_PWMSYNC_MASK) >> SDM_CH_SDCTRLE_PWMSYNC_SHIFT)

/*
 * CIC_SCL (RW)
 *
 * CIC shift control
 */
#define SDM_CH_SDCTRLE_CIC_SCL_MASK (0x7800U)
#define SDM_CH_SDCTRLE_CIC_SCL_SHIFT (11U)
#define SDM_CH_SDCTRLE_CIC_SCL_SET(x) (((uint32_t)(x) << SDM_CH_SDCTRLE_CIC_SCL_SHIFT) & SDM_CH_SDCTRLE_CIC_SCL_MASK)
#define SDM_CH_SDCTRLE_CIC_SCL_GET(x) (((uint32_t)(x) & SDM_CH_SDCTRLE_CIC_SCL_MASK) >> SDM_CH_SDCTRLE_CIC_SCL_SHIFT)

/*
 * CIC_DEC_RATIO (RW)
 *
 * CIC decimation ratio. 0 means div-by-256
 */
#define SDM_CH_SDCTRLE_CIC_DEC_RATIO_MASK (0x7F8U)
#define SDM_CH_SDCTRLE_CIC_DEC_RATIO_SHIFT (3U)
#define SDM_CH_SDCTRLE_CIC_DEC_RATIO_SET(x) (((uint32_t)(x) << SDM_CH_SDCTRLE_CIC_DEC_RATIO_SHIFT) & SDM_CH_SDCTRLE_CIC_DEC_RATIO_MASK)
#define SDM_CH_SDCTRLE_CIC_DEC_RATIO_GET(x) (((uint32_t)(x) & SDM_CH_SDCTRLE_CIC_DEC_RATIO_MASK) >> SDM_CH_SDCTRLE_CIC_DEC_RATIO_SHIFT)

/*
 * IGN_INI_SAMPLES (RW)
 *
 * NotZero: Don't store the first samples that are not accurate
 * Zero: Store all samples
 */
#define SDM_CH_SDCTRLE_IGN_INI_SAMPLES_MASK (0x7U)
#define SDM_CH_SDCTRLE_IGN_INI_SAMPLES_SHIFT (0U)
#define SDM_CH_SDCTRLE_IGN_INI_SAMPLES_SET(x) (((uint32_t)(x) << SDM_CH_SDCTRLE_IGN_INI_SAMPLES_SHIFT) & SDM_CH_SDCTRLE_IGN_INI_SAMPLES_MASK)
#define SDM_CH_SDCTRLE_IGN_INI_SAMPLES_GET(x) (((uint32_t)(x) & SDM_CH_SDCTRLE_IGN_INI_SAMPLES_MASK) >> SDM_CH_SDCTRLE_IGN_INI_SAMPLES_SHIFT)

/* Bitfield definition for register of struct array CH: SDST */
/*
 * PERIOD_MCLK (RO)
 *
 * maxim of mclk spacing in cycles, using edges of mclk signal.  In manchester coding mode, it is just the period of MCLK. In other modes, it is almost the half period.
 */
#define SDM_CH_SDST_PERIOD_MCLK_MASK (0x7F800000UL)
#define SDM_CH_SDST_PERIOD_MCLK_SHIFT (23U)
#define SDM_CH_SDST_PERIOD_MCLK_GET(x) (((uint32_t)(x) & SDM_CH_SDST_PERIOD_MCLK_MASK) >> SDM_CH_SDST_PERIOD_MCLK_SHIFT)

/*
 * SDATA_D0_T1 (RO)
 *
 * 1: next readout is timestamp
 * 0: next readout is data
 */
#define SDM_CH_SDST_SDATA_D0_T1_MASK (0x2000U)
#define SDM_CH_SDST_SDATA_D0_T1_SHIFT (13U)
#define SDM_CH_SDST_SDATA_D0_T1_GET(x) (((uint32_t)(x) & SDM_CH_SDST_SDATA_D0_T1_MASK) >> SDM_CH_SDST_SDATA_D0_T1_SHIFT)

/*
 * SDFIFO_D0_T1 (RO)
 *
 * 1: next readout is timestamp
 * 0: next readout is data
 */
#define SDM_CH_SDST_SDFIFO_D0_T1_MASK (0x1000U)
#define SDM_CH_SDST_SDFIFO_D0_T1_SHIFT (12U)
#define SDM_CH_SDST_SDFIFO_D0_T1_GET(x) (((uint32_t)(x) & SDM_CH_SDST_SDFIFO_D0_T1_MASK) >> SDM_CH_SDST_SDFIFO_D0_T1_SHIFT)

/*
 * FIFO_DR (W1C)
 *
 * FIFO data ready
 */
#define SDM_CH_SDST_FIFO_DR_MASK (0x200U)
#define SDM_CH_SDST_FIFO_DR_SHIFT (9U)
#define SDM_CH_SDST_FIFO_DR_SET(x) (((uint32_t)(x) << SDM_CH_SDST_FIFO_DR_SHIFT) & SDM_CH_SDST_FIFO_DR_MASK)
#define SDM_CH_SDST_FIFO_DR_GET(x) (((uint32_t)(x) & SDM_CH_SDST_FIFO_DR_MASK) >> SDM_CH_SDST_FIFO_DR_SHIFT)

/*
 * AF (W1C)
 *
 * Achnowledge flag
 */
#define SDM_CH_SDST_AF_MASK (0x100U)
#define SDM_CH_SDST_AF_SHIFT (8U)
#define SDM_CH_SDST_AF_SET(x) (((uint32_t)(x) << SDM_CH_SDST_AF_SHIFT) & SDM_CH_SDST_AF_MASK)
#define SDM_CH_SDST_AF_GET(x) (((uint32_t)(x) & SDM_CH_SDST_AF_MASK) >> SDM_CH_SDST_AF_SHIFT)

/*
 * DOV_ERR (W1C)
 *
 * Data FIFO Overflow Error. Error flag.
 */
#define SDM_CH_SDST_DOV_ERR_MASK (0x80U)
#define SDM_CH_SDST_DOV_ERR_SHIFT (7U)
#define SDM_CH_SDST_DOV_ERR_SET(x) (((uint32_t)(x) << SDM_CH_SDST_DOV_ERR_SHIFT) & SDM_CH_SDST_DOV_ERR_MASK)
#define SDM_CH_SDST_DOV_ERR_GET(x) (((uint32_t)(x) & SDM_CH_SDST_DOV_ERR_MASK) >> SDM_CH_SDST_DOV_ERR_SHIFT)

/*
 * DSAT_ERR (W1C)
 *
 * CIC out Data saturation err. Error flag.
 */
#define SDM_CH_SDST_DSAT_ERR_MASK (0x40U)
#define SDM_CH_SDST_DSAT_ERR_SHIFT (6U)
#define SDM_CH_SDST_DSAT_ERR_SET(x) (((uint32_t)(x) << SDM_CH_SDST_DSAT_ERR_SHIFT) & SDM_CH_SDST_DSAT_ERR_MASK)
#define SDM_CH_SDST_DSAT_ERR_GET(x) (((uint32_t)(x) & SDM_CH_SDST_DSAT_ERR_MASK) >> SDM_CH_SDST_DSAT_ERR_SHIFT)

/*
 * WTSYNFLG (RO)
 *
 * Wait-for-sync event found
 */
#define SDM_CH_SDST_WTSYNFLG_MASK (0x20U)
#define SDM_CH_SDST_WTSYNFLG_SHIFT (5U)
#define SDM_CH_SDST_WTSYNFLG_GET(x) (((uint32_t)(x) & SDM_CH_SDST_WTSYNFLG_MASK) >> SDM_CH_SDST_WTSYNFLG_SHIFT)

/*
 * FILL (RO)
 *
 * Data FIFO Fillings
 */
#define SDM_CH_SDST_FILL_MASK (0x1FU)
#define SDM_CH_SDST_FILL_SHIFT (0U)
#define SDM_CH_SDST_FILL_GET(x) (((uint32_t)(x) & SDM_CH_SDST_FILL_MASK) >> SDM_CH_SDST_FILL_SHIFT)

/* Bitfield definition for register of struct array CH: SDATA */
/*
 * VAL (RO)
 *
 * Data
 */
#define SDM_CH_SDATA_VAL_MASK (0xFFFFFFFFUL)
#define SDM_CH_SDATA_VAL_SHIFT (0U)
#define SDM_CH_SDATA_VAL_GET(x) (((uint32_t)(x) & SDM_CH_SDATA_VAL_MASK) >> SDM_CH_SDATA_VAL_SHIFT)

/* Bitfield definition for register of struct array CH: SDFIFO */
/*
 * VAL (RO)
 *
 * FIFO Data
 */
#define SDM_CH_SDFIFO_VAL_MASK (0xFFFFFFFFUL)
#define SDM_CH_SDFIFO_VAL_SHIFT (0U)
#define SDM_CH_SDFIFO_VAL_GET(x) (((uint32_t)(x) & SDM_CH_SDFIFO_VAL_MASK) >> SDM_CH_SDFIFO_VAL_SHIFT)

/* Bitfield definition for register of struct array CH: SCAMP */
/*
 * VAL (RO)
 *
 * instant Amplitude Results
 */
#define SDM_CH_SCAMP_VAL_MASK (0xFFFFU)
#define SDM_CH_SCAMP_VAL_SHIFT (0U)
#define SDM_CH_SCAMP_VAL_GET(x) (((uint32_t)(x) & SDM_CH_SCAMP_VAL_MASK) >> SDM_CH_SCAMP_VAL_SHIFT)

/* Bitfield definition for register of struct array CH: SCHTL */
/*
 * VAL (RW)
 *
 * Amplitude Threshold for High Limit
 */
#define SDM_CH_SCHTL_VAL_MASK (0xFFFFU)
#define SDM_CH_SCHTL_VAL_SHIFT (0U)
#define SDM_CH_SCHTL_VAL_SET(x) (((uint32_t)(x) << SDM_CH_SCHTL_VAL_SHIFT) & SDM_CH_SCHTL_VAL_MASK)
#define SDM_CH_SCHTL_VAL_GET(x) (((uint32_t)(x) & SDM_CH_SCHTL_VAL_MASK) >> SDM_CH_SCHTL_VAL_SHIFT)

/* Bitfield definition for register of struct array CH: SCHTLZ */
/*
 * VAL (RW)
 *
 * Amplitude Threshold for zero crossing
 */
#define SDM_CH_SCHTLZ_VAL_MASK (0xFFFFU)
#define SDM_CH_SCHTLZ_VAL_SHIFT (0U)
#define SDM_CH_SCHTLZ_VAL_SET(x) (((uint32_t)(x) << SDM_CH_SCHTLZ_VAL_SHIFT) & SDM_CH_SCHTLZ_VAL_MASK)
#define SDM_CH_SCHTLZ_VAL_GET(x) (((uint32_t)(x) & SDM_CH_SCHTLZ_VAL_MASK) >> SDM_CH_SCHTLZ_VAL_SHIFT)

/* Bitfield definition for register of struct array CH: SCLLT */
/*
 * VAL (RW)
 *
 * Amplitude Threshold for low limit
 */
#define SDM_CH_SCLLT_VAL_MASK (0xFFFFU)
#define SDM_CH_SCLLT_VAL_SHIFT (0U)
#define SDM_CH_SCLLT_VAL_SET(x) (((uint32_t)(x) << SDM_CH_SCLLT_VAL_SHIFT) & SDM_CH_SCLLT_VAL_MASK)
#define SDM_CH_SCLLT_VAL_GET(x) (((uint32_t)(x) & SDM_CH_SCLLT_VAL_MASK) >> SDM_CH_SCLLT_VAL_SHIFT)

/* Bitfield definition for register of struct array CH: SCCTRL */
/*
 * HZ_EN (RW)
 *
 * Zero Crossing Enable
 */
#define SDM_CH_SCCTRL_HZ_EN_MASK (0x800000UL)
#define SDM_CH_SCCTRL_HZ_EN_SHIFT (23U)
#define SDM_CH_SCCTRL_HZ_EN_SET(x) (((uint32_t)(x) << SDM_CH_SCCTRL_HZ_EN_SHIFT) & SDM_CH_SCCTRL_HZ_EN_MASK)
#define SDM_CH_SCCTRL_HZ_EN_GET(x) (((uint32_t)(x) & SDM_CH_SCCTRL_HZ_EN_MASK) >> SDM_CH_SCCTRL_HZ_EN_SHIFT)

/*
 * MF_IE (RW)
 *
 * Module failure Interrupt enable
 */
#define SDM_CH_SCCTRL_MF_IE_MASK (0x400000UL)
#define SDM_CH_SCCTRL_MF_IE_SHIFT (22U)
#define SDM_CH_SCCTRL_MF_IE_SET(x) (((uint32_t)(x) << SDM_CH_SCCTRL_MF_IE_SHIFT) & SDM_CH_SCCTRL_MF_IE_MASK)
#define SDM_CH_SCCTRL_MF_IE_GET(x) (((uint32_t)(x) & SDM_CH_SCCTRL_MF_IE_MASK) >> SDM_CH_SCCTRL_MF_IE_SHIFT)

/*
 * HL_IE (RW)
 *
 * HLT Interrupt Enable
 */
#define SDM_CH_SCCTRL_HL_IE_MASK (0x200000UL)
#define SDM_CH_SCCTRL_HL_IE_SHIFT (21U)
#define SDM_CH_SCCTRL_HL_IE_SET(x) (((uint32_t)(x) << SDM_CH_SCCTRL_HL_IE_SHIFT) & SDM_CH_SCCTRL_HL_IE_MASK)
#define SDM_CH_SCCTRL_HL_IE_GET(x) (((uint32_t)(x) & SDM_CH_SCCTRL_HL_IE_MASK) >> SDM_CH_SCCTRL_HL_IE_SHIFT)

/*
 * LL_IE (RW)
 *
 * LLT interrupt Enable
 */
#define SDM_CH_SCCTRL_LL_IE_MASK (0x100000UL)
#define SDM_CH_SCCTRL_LL_IE_SHIFT (20U)
#define SDM_CH_SCCTRL_LL_IE_SET(x) (((uint32_t)(x) << SDM_CH_SCCTRL_LL_IE_SHIFT) & SDM_CH_SCCTRL_LL_IE_MASK)
#define SDM_CH_SCCTRL_LL_IE_GET(x) (((uint32_t)(x) & SDM_CH_SCCTRL_LL_IE_MASK) >> SDM_CH_SCCTRL_LL_IE_SHIFT)

/*
 * SGD_ORDR (RW)
 *
 * CIC order
 * 0: SYNC1
 * 1: SYNC2
 * 2: SYNC3
 * 3: FAST_SYNC
 */
#define SDM_CH_SCCTRL_SGD_ORDR_MASK (0xC0000UL)
#define SDM_CH_SCCTRL_SGD_ORDR_SHIFT (18U)
#define SDM_CH_SCCTRL_SGD_ORDR_SET(x) (((uint32_t)(x) << SDM_CH_SCCTRL_SGD_ORDR_SHIFT) & SDM_CH_SCCTRL_SGD_ORDR_MASK)
#define SDM_CH_SCCTRL_SGD_ORDR_GET(x) (((uint32_t)(x) & SDM_CH_SCCTRL_SGD_ORDR_MASK) >> SDM_CH_SCCTRL_SGD_ORDR_SHIFT)

/*
 * CIC_DEC_RATIO (RW)
 *
 * CIC decimation ratio. 0 means div-by-32
 */
#define SDM_CH_SCCTRL_CIC_DEC_RATIO_MASK (0x1F0U)
#define SDM_CH_SCCTRL_CIC_DEC_RATIO_SHIFT (4U)
#define SDM_CH_SCCTRL_CIC_DEC_RATIO_SET(x) (((uint32_t)(x) << SDM_CH_SCCTRL_CIC_DEC_RATIO_SHIFT) & SDM_CH_SCCTRL_CIC_DEC_RATIO_MASK)
#define SDM_CH_SCCTRL_CIC_DEC_RATIO_GET(x) (((uint32_t)(x) & SDM_CH_SCCTRL_CIC_DEC_RATIO_MASK) >> SDM_CH_SCCTRL_CIC_DEC_RATIO_SHIFT)

/*
 * IGN_INI_SAMPLES (RW)
 *
 * NotZero: Ignore the first samples that are not accurate
 * Zero: Use all samples
 */
#define SDM_CH_SCCTRL_IGN_INI_SAMPLES_MASK (0xEU)
#define SDM_CH_SCCTRL_IGN_INI_SAMPLES_SHIFT (1U)
#define SDM_CH_SCCTRL_IGN_INI_SAMPLES_SET(x) (((uint32_t)(x) << SDM_CH_SCCTRL_IGN_INI_SAMPLES_SHIFT) & SDM_CH_SCCTRL_IGN_INI_SAMPLES_MASK)
#define SDM_CH_SCCTRL_IGN_INI_SAMPLES_GET(x) (((uint32_t)(x) & SDM_CH_SCCTRL_IGN_INI_SAMPLES_MASK) >> SDM_CH_SCCTRL_IGN_INI_SAMPLES_SHIFT)

/*
 * EN (RW)
 *
 * Amplitude Path Enable
 */
#define SDM_CH_SCCTRL_EN_MASK (0x1U)
#define SDM_CH_SCCTRL_EN_SHIFT (0U)
#define SDM_CH_SCCTRL_EN_SET(x) (((uint32_t)(x) << SDM_CH_SCCTRL_EN_SHIFT) & SDM_CH_SCCTRL_EN_MASK)
#define SDM_CH_SCCTRL_EN_GET(x) (((uint32_t)(x) & SDM_CH_SCCTRL_EN_MASK) >> SDM_CH_SCCTRL_EN_SHIFT)

/* Bitfield definition for register of struct array CH: SCST */
/*
 * HZ (W1C)
 *
 * Amplitude rising above HZ event found.
 */
#define SDM_CH_SCST_HZ_MASK (0x8U)
#define SDM_CH_SCST_HZ_SHIFT (3U)
#define SDM_CH_SCST_HZ_SET(x) (((uint32_t)(x) << SDM_CH_SCST_HZ_SHIFT) & SDM_CH_SCST_HZ_MASK)
#define SDM_CH_SCST_HZ_GET(x) (((uint32_t)(x) & SDM_CH_SCST_HZ_MASK) >> SDM_CH_SCST_HZ_SHIFT)

/*
 * MF (W1C)
 *
 * power modulator Failure found. MCLK not found. Error flag.
 */
#define SDM_CH_SCST_MF_MASK (0x4U)
#define SDM_CH_SCST_MF_SHIFT (2U)
#define SDM_CH_SCST_MF_SET(x) (((uint32_t)(x) << SDM_CH_SCST_MF_SHIFT) & SDM_CH_SCST_MF_MASK)
#define SDM_CH_SCST_MF_GET(x) (((uint32_t)(x) & SDM_CH_SCST_MF_MASK) >> SDM_CH_SCST_MF_SHIFT)

/*
 * CMPH (W1C)
 *
 * HLT out of range. Error flag.
 */
#define SDM_CH_SCST_CMPH_MASK (0x2U)
#define SDM_CH_SCST_CMPH_SHIFT (1U)
#define SDM_CH_SCST_CMPH_SET(x) (((uint32_t)(x) << SDM_CH_SCST_CMPH_SHIFT) & SDM_CH_SCST_CMPH_MASK)
#define SDM_CH_SCST_CMPH_GET(x) (((uint32_t)(x) & SDM_CH_SCST_CMPH_MASK) >> SDM_CH_SCST_CMPH_SHIFT)

/*
 * CMPL (W1C)
 *
 * LLT out of range. Error flag.
 */
#define SDM_CH_SCST_CMPL_MASK (0x1U)
#define SDM_CH_SCST_CMPL_SHIFT (0U)
#define SDM_CH_SCST_CMPL_SET(x) (((uint32_t)(x) << SDM_CH_SCST_CMPL_SHIFT) & SDM_CH_SCST_CMPL_MASK)
#define SDM_CH_SCST_CMPL_GET(x) (((uint32_t)(x) & SDM_CH_SCST_CMPL_MASK) >> SDM_CH_SCST_CMPL_SHIFT)



/* CH register group index macro definition */
#define SDM_CH_0 (0UL)
#define SDM_CH_1 (1UL)
#define SDM_CH_2 (2UL)
#define SDM_CH_3 (3UL)


#endif /* HPM_SDM_H */
