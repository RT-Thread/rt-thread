/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_GPTMR_H
#define HPM_GPTMR_H

typedef struct {
    struct {
        __RW uint32_t CR;                      /* 0x0: Control Register */
        __RW uint32_t CMP[2];                  /* 0x4 - 0x8: Comparator register 0 */
        __RW uint32_t RLD;                     /* 0xC: Reload register */
        __RW uint32_t CNTUPTVAL;               /* 0x10: Counter update value register */
        __R  uint8_t  RESERVED0[12];           /* 0x14 - 0x1F: Reserved */
        __R  uint32_t CAPPOS;                  /* 0x20: Capture rising edge register */
        __R  uint32_t CAPNEG;                  /* 0x24: Capture falling edge register */
        __R  uint32_t CAPPRD;                  /* 0x28: PWM period measure register */
        __R  uint32_t CAPDTY;                  /* 0x2C: PWM duty cycle measure register */
        __R  uint32_t CNT;                     /* 0x30: Counter */
        __R  uint8_t  RESERVED1[12];           /* 0x34 - 0x3F: Reserved */
    } CHANNEL[4];
    __R  uint8_t  RESERVED0[256];              /* 0x100 - 0x1FF: Reserved */
    __RW uint32_t SR;                          /* 0x200: Status register */
    __RW uint32_t IRQEN;                       /* 0x204: Interrupt request enable register */
    __RW uint32_t GCR;                         /* 0x208: Global control register */
} GPTMR_Type;


/* Bitfield definition for register of struct array CHANNEL: CR */
/*
 * CNTUPT (WO)
 *
 * 1- update counter to new value as CNTUPTVAL
 * This bit will be auto cleared after 1 cycle
 */
#define GPTMR_CHANNEL_CR_CNTUPT_MASK (0x80000000UL)
#define GPTMR_CHANNEL_CR_CNTUPT_SHIFT (31U)
#define GPTMR_CHANNEL_CR_CNTUPT_SET(x) (((uint32_t)(x) << GPTMR_CHANNEL_CR_CNTUPT_SHIFT) & GPTMR_CHANNEL_CR_CNTUPT_MASK)
#define GPTMR_CHANNEL_CR_CNTUPT_GET(x) (((uint32_t)(x) & GPTMR_CHANNEL_CR_CNTUPT_MASK) >> GPTMR_CHANNEL_CR_CNTUPT_SHIFT)

/*
 * OPMODE (RW)
 *
 * 0:  round mode
 * 1:  one-shot mode, timer will stopped at reload point.
 * NOTE: reload irq will be always set at one-shot mode at end
 */
#define GPTMR_CHANNEL_CR_OPMODE_MASK (0x20000UL)
#define GPTMR_CHANNEL_CR_OPMODE_SHIFT (17U)
#define GPTMR_CHANNEL_CR_OPMODE_SET(x) (((uint32_t)(x) << GPTMR_CHANNEL_CR_OPMODE_SHIFT) & GPTMR_CHANNEL_CR_OPMODE_MASK)
#define GPTMR_CHANNEL_CR_OPMODE_GET(x) (((uint32_t)(x) & GPTMR_CHANNEL_CR_OPMODE_MASK) >> GPTMR_CHANNEL_CR_OPMODE_SHIFT)

/*
 * MONITOR_SEL (RW)
 *
 * set to monitor input signal high level time(chan_meas_high)
 * clr to monitor input signal period(chan_meas_prd)
 */
#define GPTMR_CHANNEL_CR_MONITOR_SEL_MASK (0x10000UL)
#define GPTMR_CHANNEL_CR_MONITOR_SEL_SHIFT (16U)
#define GPTMR_CHANNEL_CR_MONITOR_SEL_SET(x) (((uint32_t)(x) << GPTMR_CHANNEL_CR_MONITOR_SEL_SHIFT) & GPTMR_CHANNEL_CR_MONITOR_SEL_MASK)
#define GPTMR_CHANNEL_CR_MONITOR_SEL_GET(x) (((uint32_t)(x) & GPTMR_CHANNEL_CR_MONITOR_SEL_MASK) >> GPTMR_CHANNEL_CR_MONITOR_SEL_SHIFT)

/*
 * MONITOR_EN (RW)
 *
 * set to monitor input signal period or high level time.
 * When this bit is set, if detected period less than val_0 or more than val_1, will set related irq_sts
 * * only can be used when trig_mode is selected as measure mode(100)
 * * the time may not correct after reload, so monitor is disabled after reload point, and enabled again after two continul posedge.
 * if no posedge after reload for more than val_1, will also assert irq_capt
 */
#define GPTMR_CHANNEL_CR_MONITOR_EN_MASK (0x8000U)
#define GPTMR_CHANNEL_CR_MONITOR_EN_SHIFT (15U)
#define GPTMR_CHANNEL_CR_MONITOR_EN_SET(x) (((uint32_t)(x) << GPTMR_CHANNEL_CR_MONITOR_EN_SHIFT) & GPTMR_CHANNEL_CR_MONITOR_EN_MASK)
#define GPTMR_CHANNEL_CR_MONITOR_EN_GET(x) (((uint32_t)(x) & GPTMR_CHANNEL_CR_MONITOR_EN_MASK) >> GPTMR_CHANNEL_CR_MONITOR_EN_SHIFT)

/*
 * CNTRST (RW)
 *
 * 1- reset counter
 */
#define GPTMR_CHANNEL_CR_CNTRST_MASK (0x4000U)
#define GPTMR_CHANNEL_CR_CNTRST_SHIFT (14U)
#define GPTMR_CHANNEL_CR_CNTRST_SET(x) (((uint32_t)(x) << GPTMR_CHANNEL_CR_CNTRST_SHIFT) & GPTMR_CHANNEL_CR_CNTRST_MASK)
#define GPTMR_CHANNEL_CR_CNTRST_GET(x) (((uint32_t)(x) & GPTMR_CHANNEL_CR_CNTRST_MASK) >> GPTMR_CHANNEL_CR_CNTRST_SHIFT)

/*
 * SYNCFLW (RW)
 *
 * 1- enable this channel to reset counter to reload(RLD) together with its previous channel.
 * This bit is not valid for channel 0.
 */
#define GPTMR_CHANNEL_CR_SYNCFLW_MASK (0x2000U)
#define GPTMR_CHANNEL_CR_SYNCFLW_SHIFT (13U)
#define GPTMR_CHANNEL_CR_SYNCFLW_SET(x) (((uint32_t)(x) << GPTMR_CHANNEL_CR_SYNCFLW_SHIFT) & GPTMR_CHANNEL_CR_SYNCFLW_MASK)
#define GPTMR_CHANNEL_CR_SYNCFLW_GET(x) (((uint32_t)(x) & GPTMR_CHANNEL_CR_SYNCFLW_MASK) >> GPTMR_CHANNEL_CR_SYNCFLW_SHIFT)

/*
 * SYNCIFEN (RW)
 *
 * 1- SYNCI is valid on its falling edge
 */
#define GPTMR_CHANNEL_CR_SYNCIFEN_MASK (0x1000U)
#define GPTMR_CHANNEL_CR_SYNCIFEN_SHIFT (12U)
#define GPTMR_CHANNEL_CR_SYNCIFEN_SET(x) (((uint32_t)(x) << GPTMR_CHANNEL_CR_SYNCIFEN_SHIFT) & GPTMR_CHANNEL_CR_SYNCIFEN_MASK)
#define GPTMR_CHANNEL_CR_SYNCIFEN_GET(x) (((uint32_t)(x) & GPTMR_CHANNEL_CR_SYNCIFEN_MASK) >> GPTMR_CHANNEL_CR_SYNCIFEN_SHIFT)

/*
 * SYNCIREN (RW)
 *
 * 1- SYNCI is valid on its rising edge
 */
#define GPTMR_CHANNEL_CR_SYNCIREN_MASK (0x800U)
#define GPTMR_CHANNEL_CR_SYNCIREN_SHIFT (11U)
#define GPTMR_CHANNEL_CR_SYNCIREN_SET(x) (((uint32_t)(x) << GPTMR_CHANNEL_CR_SYNCIREN_SHIFT) & GPTMR_CHANNEL_CR_SYNCIREN_MASK)
#define GPTMR_CHANNEL_CR_SYNCIREN_GET(x) (((uint32_t)(x) & GPTMR_CHANNEL_CR_SYNCIREN_MASK) >> GPTMR_CHANNEL_CR_SYNCIREN_SHIFT)

/*
 * CEN (RW)
 *
 * 1- counter enable
 */
#define GPTMR_CHANNEL_CR_CEN_MASK (0x400U)
#define GPTMR_CHANNEL_CR_CEN_SHIFT (10U)
#define GPTMR_CHANNEL_CR_CEN_SET(x) (((uint32_t)(x) << GPTMR_CHANNEL_CR_CEN_SHIFT) & GPTMR_CHANNEL_CR_CEN_MASK)
#define GPTMR_CHANNEL_CR_CEN_GET(x) (((uint32_t)(x) & GPTMR_CHANNEL_CR_CEN_MASK) >> GPTMR_CHANNEL_CR_CEN_SHIFT)

/*
 * CMPINIT (RW)
 *
 * Output compare initial poliarity
 * 1- The channel output initial level is high
 * 0- The channel output initial level is low
 * User should set this bit before set CMPEN to 1.
 */
#define GPTMR_CHANNEL_CR_CMPINIT_MASK (0x200U)
#define GPTMR_CHANNEL_CR_CMPINIT_SHIFT (9U)
#define GPTMR_CHANNEL_CR_CMPINIT_SET(x) (((uint32_t)(x) << GPTMR_CHANNEL_CR_CMPINIT_SHIFT) & GPTMR_CHANNEL_CR_CMPINIT_MASK)
#define GPTMR_CHANNEL_CR_CMPINIT_GET(x) (((uint32_t)(x) & GPTMR_CHANNEL_CR_CMPINIT_MASK) >> GPTMR_CHANNEL_CR_CMPINIT_SHIFT)

/*
 * CMPEN (RW)
 *
 * 1- Enable the channel output compare function. The output signal can be generated per comparator (CMPx) settings.
 */
#define GPTMR_CHANNEL_CR_CMPEN_MASK (0x100U)
#define GPTMR_CHANNEL_CR_CMPEN_SHIFT (8U)
#define GPTMR_CHANNEL_CR_CMPEN_SET(x) (((uint32_t)(x) << GPTMR_CHANNEL_CR_CMPEN_SHIFT) & GPTMR_CHANNEL_CR_CMPEN_MASK)
#define GPTMR_CHANNEL_CR_CMPEN_GET(x) (((uint32_t)(x) & GPTMR_CHANNEL_CR_CMPEN_MASK) >> GPTMR_CHANNEL_CR_CMPEN_SHIFT)

/*
 * DMASEL (RW)
 *
 * select one of DMA request:
 * 00- CMP0 flag
 * 01- CMP1 flag
 * 10- Input signal toggle captured
 * 11- RLD flag, counter reload;
 */
#define GPTMR_CHANNEL_CR_DMASEL_MASK (0xC0U)
#define GPTMR_CHANNEL_CR_DMASEL_SHIFT (6U)
#define GPTMR_CHANNEL_CR_DMASEL_SET(x) (((uint32_t)(x) << GPTMR_CHANNEL_CR_DMASEL_SHIFT) & GPTMR_CHANNEL_CR_DMASEL_MASK)
#define GPTMR_CHANNEL_CR_DMASEL_GET(x) (((uint32_t)(x) & GPTMR_CHANNEL_CR_DMASEL_MASK) >> GPTMR_CHANNEL_CR_DMASEL_SHIFT)

/*
 * DMAEN (RW)
 *
 * 1- enable dma
 */
#define GPTMR_CHANNEL_CR_DMAEN_MASK (0x20U)
#define GPTMR_CHANNEL_CR_DMAEN_SHIFT (5U)
#define GPTMR_CHANNEL_CR_DMAEN_SET(x) (((uint32_t)(x) << GPTMR_CHANNEL_CR_DMAEN_SHIFT) & GPTMR_CHANNEL_CR_DMAEN_MASK)
#define GPTMR_CHANNEL_CR_DMAEN_GET(x) (((uint32_t)(x) & GPTMR_CHANNEL_CR_DMAEN_MASK) >> GPTMR_CHANNEL_CR_DMAEN_SHIFT)

/*
 * SWSYNCIEN (RW)
 *
 * 1- enable software sync. When this bit is set, counter will reset to RLD when swsynct bit is set
 */
#define GPTMR_CHANNEL_CR_SWSYNCIEN_MASK (0x10U)
#define GPTMR_CHANNEL_CR_SWSYNCIEN_SHIFT (4U)
#define GPTMR_CHANNEL_CR_SWSYNCIEN_SET(x) (((uint32_t)(x) << GPTMR_CHANNEL_CR_SWSYNCIEN_SHIFT) & GPTMR_CHANNEL_CR_SWSYNCIEN_MASK)
#define GPTMR_CHANNEL_CR_SWSYNCIEN_GET(x) (((uint32_t)(x) & GPTMR_CHANNEL_CR_SWSYNCIEN_MASK) >> GPTMR_CHANNEL_CR_SWSYNCIEN_SHIFT)

/*
 * DBGPAUSE (RW)
 *
 * 1- counter will pause if chip is in debug mode
 */
#define GPTMR_CHANNEL_CR_DBGPAUSE_MASK (0x8U)
#define GPTMR_CHANNEL_CR_DBGPAUSE_SHIFT (3U)
#define GPTMR_CHANNEL_CR_DBGPAUSE_SET(x) (((uint32_t)(x) << GPTMR_CHANNEL_CR_DBGPAUSE_SHIFT) & GPTMR_CHANNEL_CR_DBGPAUSE_MASK)
#define GPTMR_CHANNEL_CR_DBGPAUSE_GET(x) (((uint32_t)(x) & GPTMR_CHANNEL_CR_DBGPAUSE_MASK) >> GPTMR_CHANNEL_CR_DBGPAUSE_SHIFT)

/*
 * CAPMODE (RW)
 *
 * This bitfield define the input capture mode
 * 100:  width measure mode, timer will calculate the input signal period and duty cycle
 * 011:  capture at both rising edge and falling edge
 * 010:  capture at falling edge
 * 001:  capture at rising edge
 * 000:  No capture
 */
#define GPTMR_CHANNEL_CR_CAPMODE_MASK (0x7U)
#define GPTMR_CHANNEL_CR_CAPMODE_SHIFT (0U)
#define GPTMR_CHANNEL_CR_CAPMODE_SET(x) (((uint32_t)(x) << GPTMR_CHANNEL_CR_CAPMODE_SHIFT) & GPTMR_CHANNEL_CR_CAPMODE_MASK)
#define GPTMR_CHANNEL_CR_CAPMODE_GET(x) (((uint32_t)(x) & GPTMR_CHANNEL_CR_CAPMODE_MASK) >> GPTMR_CHANNEL_CR_CAPMODE_SHIFT)

/* Bitfield definition for register of struct array CHANNEL: CMP0 */
/*
 * CMP (RW)
 *
 * compare value 0
 */
#define GPTMR_CHANNEL_CMP_CMP_MASK (0xFFFFFFFFUL)
#define GPTMR_CHANNEL_CMP_CMP_SHIFT (0U)
#define GPTMR_CHANNEL_CMP_CMP_SET(x) (((uint32_t)(x) << GPTMR_CHANNEL_CMP_CMP_SHIFT) & GPTMR_CHANNEL_CMP_CMP_MASK)
#define GPTMR_CHANNEL_CMP_CMP_GET(x) (((uint32_t)(x) & GPTMR_CHANNEL_CMP_CMP_MASK) >> GPTMR_CHANNEL_CMP_CMP_SHIFT)

/* Bitfield definition for register of struct array CHANNEL: RLD */
/*
 * RLD (RW)
 *
 * reload value
 */
#define GPTMR_CHANNEL_RLD_RLD_MASK (0xFFFFFFFFUL)
#define GPTMR_CHANNEL_RLD_RLD_SHIFT (0U)
#define GPTMR_CHANNEL_RLD_RLD_SET(x) (((uint32_t)(x) << GPTMR_CHANNEL_RLD_RLD_SHIFT) & GPTMR_CHANNEL_RLD_RLD_MASK)
#define GPTMR_CHANNEL_RLD_RLD_GET(x) (((uint32_t)(x) & GPTMR_CHANNEL_RLD_RLD_MASK) >> GPTMR_CHANNEL_RLD_RLD_SHIFT)

/* Bitfield definition for register of struct array CHANNEL: CNTUPTVAL */
/*
 * CNTUPTVAL (RW)
 *
 * counter will be set to this value when software write cntupt bit in CR
 */
#define GPTMR_CHANNEL_CNTUPTVAL_CNTUPTVAL_MASK (0xFFFFFFFFUL)
#define GPTMR_CHANNEL_CNTUPTVAL_CNTUPTVAL_SHIFT (0U)
#define GPTMR_CHANNEL_CNTUPTVAL_CNTUPTVAL_SET(x) (((uint32_t)(x) << GPTMR_CHANNEL_CNTUPTVAL_CNTUPTVAL_SHIFT) & GPTMR_CHANNEL_CNTUPTVAL_CNTUPTVAL_MASK)
#define GPTMR_CHANNEL_CNTUPTVAL_CNTUPTVAL_GET(x) (((uint32_t)(x) & GPTMR_CHANNEL_CNTUPTVAL_CNTUPTVAL_MASK) >> GPTMR_CHANNEL_CNTUPTVAL_CNTUPTVAL_SHIFT)

/* Bitfield definition for register of struct array CHANNEL: CAPPOS */
/*
 * CAPPOS (RO)
 *
 * This register contains the counter value captured at input signal rising edge
 */
#define GPTMR_CHANNEL_CAPPOS_CAPPOS_MASK (0xFFFFFFFFUL)
#define GPTMR_CHANNEL_CAPPOS_CAPPOS_SHIFT (0U)
#define GPTMR_CHANNEL_CAPPOS_CAPPOS_GET(x) (((uint32_t)(x) & GPTMR_CHANNEL_CAPPOS_CAPPOS_MASK) >> GPTMR_CHANNEL_CAPPOS_CAPPOS_SHIFT)

/* Bitfield definition for register of struct array CHANNEL: CAPNEG */
/*
 * CAPNEG (RO)
 *
 * This register contains the counter value captured at input signal falling edge
 */
#define GPTMR_CHANNEL_CAPNEG_CAPNEG_MASK (0xFFFFFFFFUL)
#define GPTMR_CHANNEL_CAPNEG_CAPNEG_SHIFT (0U)
#define GPTMR_CHANNEL_CAPNEG_CAPNEG_GET(x) (((uint32_t)(x) & GPTMR_CHANNEL_CAPNEG_CAPNEG_MASK) >> GPTMR_CHANNEL_CAPNEG_CAPNEG_SHIFT)

/* Bitfield definition for register of struct array CHANNEL: CAPPRD */
/*
 * CAPPRD (RO)
 *
 * This register contains the input signal period when channel is configured to input capture measure mode.
 */
#define GPTMR_CHANNEL_CAPPRD_CAPPRD_MASK (0xFFFFFFFFUL)
#define GPTMR_CHANNEL_CAPPRD_CAPPRD_SHIFT (0U)
#define GPTMR_CHANNEL_CAPPRD_CAPPRD_GET(x) (((uint32_t)(x) & GPTMR_CHANNEL_CAPPRD_CAPPRD_MASK) >> GPTMR_CHANNEL_CAPPRD_CAPPRD_SHIFT)

/* Bitfield definition for register of struct array CHANNEL: CAPDTY */
/*
 * MEAS_HIGH (RO)
 *
 * This register contains the input signal duty cycle when channel is configured to input capture measure mode.
 */
#define GPTMR_CHANNEL_CAPDTY_MEAS_HIGH_MASK (0xFFFFFFFFUL)
#define GPTMR_CHANNEL_CAPDTY_MEAS_HIGH_SHIFT (0U)
#define GPTMR_CHANNEL_CAPDTY_MEAS_HIGH_GET(x) (((uint32_t)(x) & GPTMR_CHANNEL_CAPDTY_MEAS_HIGH_MASK) >> GPTMR_CHANNEL_CAPDTY_MEAS_HIGH_SHIFT)

/* Bitfield definition for register of struct array CHANNEL: CNT */
/*
 * COUNTER (RO)
 *
 * 32 bit counter value
 */
#define GPTMR_CHANNEL_CNT_COUNTER_MASK (0xFFFFFFFFUL)
#define GPTMR_CHANNEL_CNT_COUNTER_SHIFT (0U)
#define GPTMR_CHANNEL_CNT_COUNTER_GET(x) (((uint32_t)(x) & GPTMR_CHANNEL_CNT_COUNTER_MASK) >> GPTMR_CHANNEL_CNT_COUNTER_SHIFT)

/* Bitfield definition for register: SR */
/*
 * CH3CMP1F (W1C)
 *
 * channel 3 compare value 1 match flag
 */
#define GPTMR_SR_CH3CMP1F_MASK (0x8000U)
#define GPTMR_SR_CH3CMP1F_SHIFT (15U)
#define GPTMR_SR_CH3CMP1F_SET(x) (((uint32_t)(x) << GPTMR_SR_CH3CMP1F_SHIFT) & GPTMR_SR_CH3CMP1F_MASK)
#define GPTMR_SR_CH3CMP1F_GET(x) (((uint32_t)(x) & GPTMR_SR_CH3CMP1F_MASK) >> GPTMR_SR_CH3CMP1F_SHIFT)

/*
 * CH3CMP0F (W1C)
 *
 * channel 3 compare value 1 match flag
 */
#define GPTMR_SR_CH3CMP0F_MASK (0x4000U)
#define GPTMR_SR_CH3CMP0F_SHIFT (14U)
#define GPTMR_SR_CH3CMP0F_SET(x) (((uint32_t)(x) << GPTMR_SR_CH3CMP0F_SHIFT) & GPTMR_SR_CH3CMP0F_MASK)
#define GPTMR_SR_CH3CMP0F_GET(x) (((uint32_t)(x) & GPTMR_SR_CH3CMP0F_MASK) >> GPTMR_SR_CH3CMP0F_SHIFT)

/*
 * CH3CAPF (W1C)
 *
 * channel 3 capture flag, the flag will be set at the valid capture edge per CAPMODE setting. If the capture channel is set to measure mode, the flag will be set at rising edge.
 */
#define GPTMR_SR_CH3CAPF_MASK (0x2000U)
#define GPTMR_SR_CH3CAPF_SHIFT (13U)
#define GPTMR_SR_CH3CAPF_SET(x) (((uint32_t)(x) << GPTMR_SR_CH3CAPF_SHIFT) & GPTMR_SR_CH3CAPF_MASK)
#define GPTMR_SR_CH3CAPF_GET(x) (((uint32_t)(x) & GPTMR_SR_CH3CAPF_MASK) >> GPTMR_SR_CH3CAPF_SHIFT)

/*
 * CH3RLDF (W1C)
 *
 * channel 3 counter reload flag
 */
#define GPTMR_SR_CH3RLDF_MASK (0x1000U)
#define GPTMR_SR_CH3RLDF_SHIFT (12U)
#define GPTMR_SR_CH3RLDF_SET(x) (((uint32_t)(x) << GPTMR_SR_CH3RLDF_SHIFT) & GPTMR_SR_CH3RLDF_MASK)
#define GPTMR_SR_CH3RLDF_GET(x) (((uint32_t)(x) & GPTMR_SR_CH3RLDF_MASK) >> GPTMR_SR_CH3RLDF_SHIFT)

/*
 * CH2CMP1F (W1C)
 *
 * channel 2 compare value 1 match flag
 */
#define GPTMR_SR_CH2CMP1F_MASK (0x800U)
#define GPTMR_SR_CH2CMP1F_SHIFT (11U)
#define GPTMR_SR_CH2CMP1F_SET(x) (((uint32_t)(x) << GPTMR_SR_CH2CMP1F_SHIFT) & GPTMR_SR_CH2CMP1F_MASK)
#define GPTMR_SR_CH2CMP1F_GET(x) (((uint32_t)(x) & GPTMR_SR_CH2CMP1F_MASK) >> GPTMR_SR_CH2CMP1F_SHIFT)

/*
 * CH2CMP0F (W1C)
 *
 * channel 2 compare value 1 match flag
 */
#define GPTMR_SR_CH2CMP0F_MASK (0x400U)
#define GPTMR_SR_CH2CMP0F_SHIFT (10U)
#define GPTMR_SR_CH2CMP0F_SET(x) (((uint32_t)(x) << GPTMR_SR_CH2CMP0F_SHIFT) & GPTMR_SR_CH2CMP0F_MASK)
#define GPTMR_SR_CH2CMP0F_GET(x) (((uint32_t)(x) & GPTMR_SR_CH2CMP0F_MASK) >> GPTMR_SR_CH2CMP0F_SHIFT)

/*
 * CH2CAPF (W1C)
 *
 * channel 2 capture flag, the flag will be set at the valid capture edge per CAPMODE setting. If the capture channel is set to measure mode, the flag will be set at rising edge.
 */
#define GPTMR_SR_CH2CAPF_MASK (0x200U)
#define GPTMR_SR_CH2CAPF_SHIFT (9U)
#define GPTMR_SR_CH2CAPF_SET(x) (((uint32_t)(x) << GPTMR_SR_CH2CAPF_SHIFT) & GPTMR_SR_CH2CAPF_MASK)
#define GPTMR_SR_CH2CAPF_GET(x) (((uint32_t)(x) & GPTMR_SR_CH2CAPF_MASK) >> GPTMR_SR_CH2CAPF_SHIFT)

/*
 * CH2RLDF (W1C)
 *
 * channel 2 counter reload flag
 */
#define GPTMR_SR_CH2RLDF_MASK (0x100U)
#define GPTMR_SR_CH2RLDF_SHIFT (8U)
#define GPTMR_SR_CH2RLDF_SET(x) (((uint32_t)(x) << GPTMR_SR_CH2RLDF_SHIFT) & GPTMR_SR_CH2RLDF_MASK)
#define GPTMR_SR_CH2RLDF_GET(x) (((uint32_t)(x) & GPTMR_SR_CH2RLDF_MASK) >> GPTMR_SR_CH2RLDF_SHIFT)

/*
 * CH1CMP1F (W1C)
 *
 * channel 1 compare value 1 match flag
 */
#define GPTMR_SR_CH1CMP1F_MASK (0x80U)
#define GPTMR_SR_CH1CMP1F_SHIFT (7U)
#define GPTMR_SR_CH1CMP1F_SET(x) (((uint32_t)(x) << GPTMR_SR_CH1CMP1F_SHIFT) & GPTMR_SR_CH1CMP1F_MASK)
#define GPTMR_SR_CH1CMP1F_GET(x) (((uint32_t)(x) & GPTMR_SR_CH1CMP1F_MASK) >> GPTMR_SR_CH1CMP1F_SHIFT)

/*
 * CH1CMP0F (W1C)
 *
 * channel 1 compare value 1 match flag
 */
#define GPTMR_SR_CH1CMP0F_MASK (0x40U)
#define GPTMR_SR_CH1CMP0F_SHIFT (6U)
#define GPTMR_SR_CH1CMP0F_SET(x) (((uint32_t)(x) << GPTMR_SR_CH1CMP0F_SHIFT) & GPTMR_SR_CH1CMP0F_MASK)
#define GPTMR_SR_CH1CMP0F_GET(x) (((uint32_t)(x) & GPTMR_SR_CH1CMP0F_MASK) >> GPTMR_SR_CH1CMP0F_SHIFT)

/*
 * CH1CAPF (W1C)
 *
 * channel 1 capture flag, the flag will be set at the valid capture edge per CAPMODE setting. If the capture channel is set to measure mode, the flag will be set at rising edge.
 */
#define GPTMR_SR_CH1CAPF_MASK (0x20U)
#define GPTMR_SR_CH1CAPF_SHIFT (5U)
#define GPTMR_SR_CH1CAPF_SET(x) (((uint32_t)(x) << GPTMR_SR_CH1CAPF_SHIFT) & GPTMR_SR_CH1CAPF_MASK)
#define GPTMR_SR_CH1CAPF_GET(x) (((uint32_t)(x) & GPTMR_SR_CH1CAPF_MASK) >> GPTMR_SR_CH1CAPF_SHIFT)

/*
 * CH1RLDF (W1C)
 *
 * channel 1 counter reload flag
 */
#define GPTMR_SR_CH1RLDF_MASK (0x10U)
#define GPTMR_SR_CH1RLDF_SHIFT (4U)
#define GPTMR_SR_CH1RLDF_SET(x) (((uint32_t)(x) << GPTMR_SR_CH1RLDF_SHIFT) & GPTMR_SR_CH1RLDF_MASK)
#define GPTMR_SR_CH1RLDF_GET(x) (((uint32_t)(x) & GPTMR_SR_CH1RLDF_MASK) >> GPTMR_SR_CH1RLDF_SHIFT)

/*
 * CH0CMP1F (W1C)
 *
 * channel 1 compare value 1 match flag
 */
#define GPTMR_SR_CH0CMP1F_MASK (0x8U)
#define GPTMR_SR_CH0CMP1F_SHIFT (3U)
#define GPTMR_SR_CH0CMP1F_SET(x) (((uint32_t)(x) << GPTMR_SR_CH0CMP1F_SHIFT) & GPTMR_SR_CH0CMP1F_MASK)
#define GPTMR_SR_CH0CMP1F_GET(x) (((uint32_t)(x) & GPTMR_SR_CH0CMP1F_MASK) >> GPTMR_SR_CH0CMP1F_SHIFT)

/*
 * CH0CMP0F (W1C)
 *
 * channel 1 compare value 1 match flag
 */
#define GPTMR_SR_CH0CMP0F_MASK (0x4U)
#define GPTMR_SR_CH0CMP0F_SHIFT (2U)
#define GPTMR_SR_CH0CMP0F_SET(x) (((uint32_t)(x) << GPTMR_SR_CH0CMP0F_SHIFT) & GPTMR_SR_CH0CMP0F_MASK)
#define GPTMR_SR_CH0CMP0F_GET(x) (((uint32_t)(x) & GPTMR_SR_CH0CMP0F_MASK) >> GPTMR_SR_CH0CMP0F_SHIFT)

/*
 * CH0CAPF (W1C)
 *
 * channel 1 capture flag, the flag will be set at the valid capture edge per CAPMODE setting. If the capture channel is set to measure mode, the flag will be set at rising edge.
 */
#define GPTMR_SR_CH0CAPF_MASK (0x2U)
#define GPTMR_SR_CH0CAPF_SHIFT (1U)
#define GPTMR_SR_CH0CAPF_SET(x) (((uint32_t)(x) << GPTMR_SR_CH0CAPF_SHIFT) & GPTMR_SR_CH0CAPF_MASK)
#define GPTMR_SR_CH0CAPF_GET(x) (((uint32_t)(x) & GPTMR_SR_CH0CAPF_MASK) >> GPTMR_SR_CH0CAPF_SHIFT)

/*
 * CH0RLDF (W1C)
 *
 * channel 1 counter reload flag
 */
#define GPTMR_SR_CH0RLDF_MASK (0x1U)
#define GPTMR_SR_CH0RLDF_SHIFT (0U)
#define GPTMR_SR_CH0RLDF_SET(x) (((uint32_t)(x) << GPTMR_SR_CH0RLDF_SHIFT) & GPTMR_SR_CH0RLDF_MASK)
#define GPTMR_SR_CH0RLDF_GET(x) (((uint32_t)(x) & GPTMR_SR_CH0RLDF_MASK) >> GPTMR_SR_CH0RLDF_SHIFT)

/* Bitfield definition for register: IRQEN */
/*
 * CH3CMP1EN (RW)
 *
 * 1- generate interrupt request when ch3cmp1f flag is set
 */
#define GPTMR_IRQEN_CH3CMP1EN_MASK (0x8000U)
#define GPTMR_IRQEN_CH3CMP1EN_SHIFT (15U)
#define GPTMR_IRQEN_CH3CMP1EN_SET(x) (((uint32_t)(x) << GPTMR_IRQEN_CH3CMP1EN_SHIFT) & GPTMR_IRQEN_CH3CMP1EN_MASK)
#define GPTMR_IRQEN_CH3CMP1EN_GET(x) (((uint32_t)(x) & GPTMR_IRQEN_CH3CMP1EN_MASK) >> GPTMR_IRQEN_CH3CMP1EN_SHIFT)

/*
 * CH3CMP0EN (RW)
 *
 * 1- generate interrupt request when ch3cmp0f flag is set
 */
#define GPTMR_IRQEN_CH3CMP0EN_MASK (0x4000U)
#define GPTMR_IRQEN_CH3CMP0EN_SHIFT (14U)
#define GPTMR_IRQEN_CH3CMP0EN_SET(x) (((uint32_t)(x) << GPTMR_IRQEN_CH3CMP0EN_SHIFT) & GPTMR_IRQEN_CH3CMP0EN_MASK)
#define GPTMR_IRQEN_CH3CMP0EN_GET(x) (((uint32_t)(x) & GPTMR_IRQEN_CH3CMP0EN_MASK) >> GPTMR_IRQEN_CH3CMP0EN_SHIFT)

/*
 * CH3CAPEN (RW)
 *
 * 1- generate interrupt request when ch3capf flag is set
 */
#define GPTMR_IRQEN_CH3CAPEN_MASK (0x2000U)
#define GPTMR_IRQEN_CH3CAPEN_SHIFT (13U)
#define GPTMR_IRQEN_CH3CAPEN_SET(x) (((uint32_t)(x) << GPTMR_IRQEN_CH3CAPEN_SHIFT) & GPTMR_IRQEN_CH3CAPEN_MASK)
#define GPTMR_IRQEN_CH3CAPEN_GET(x) (((uint32_t)(x) & GPTMR_IRQEN_CH3CAPEN_MASK) >> GPTMR_IRQEN_CH3CAPEN_SHIFT)

/*
 * CH3RLDEN (RW)
 *
 * 1- generate interrupt request when ch3rldf flag is set
 */
#define GPTMR_IRQEN_CH3RLDEN_MASK (0x1000U)
#define GPTMR_IRQEN_CH3RLDEN_SHIFT (12U)
#define GPTMR_IRQEN_CH3RLDEN_SET(x) (((uint32_t)(x) << GPTMR_IRQEN_CH3RLDEN_SHIFT) & GPTMR_IRQEN_CH3RLDEN_MASK)
#define GPTMR_IRQEN_CH3RLDEN_GET(x) (((uint32_t)(x) & GPTMR_IRQEN_CH3RLDEN_MASK) >> GPTMR_IRQEN_CH3RLDEN_SHIFT)

/*
 * CH2CMP1EN (RW)
 *
 * 1- generate interrupt request when ch2cmp1f flag is set
 */
#define GPTMR_IRQEN_CH2CMP1EN_MASK (0x800U)
#define GPTMR_IRQEN_CH2CMP1EN_SHIFT (11U)
#define GPTMR_IRQEN_CH2CMP1EN_SET(x) (((uint32_t)(x) << GPTMR_IRQEN_CH2CMP1EN_SHIFT) & GPTMR_IRQEN_CH2CMP1EN_MASK)
#define GPTMR_IRQEN_CH2CMP1EN_GET(x) (((uint32_t)(x) & GPTMR_IRQEN_CH2CMP1EN_MASK) >> GPTMR_IRQEN_CH2CMP1EN_SHIFT)

/*
 * CH2CMP0EN (RW)
 *
 * 1- generate interrupt request when ch2cmp0f flag is set
 */
#define GPTMR_IRQEN_CH2CMP0EN_MASK (0x400U)
#define GPTMR_IRQEN_CH2CMP0EN_SHIFT (10U)
#define GPTMR_IRQEN_CH2CMP0EN_SET(x) (((uint32_t)(x) << GPTMR_IRQEN_CH2CMP0EN_SHIFT) & GPTMR_IRQEN_CH2CMP0EN_MASK)
#define GPTMR_IRQEN_CH2CMP0EN_GET(x) (((uint32_t)(x) & GPTMR_IRQEN_CH2CMP0EN_MASK) >> GPTMR_IRQEN_CH2CMP0EN_SHIFT)

/*
 * CH2CAPEN (RW)
 *
 * 1- generate interrupt request when ch2capf flag is set
 */
#define GPTMR_IRQEN_CH2CAPEN_MASK (0x200U)
#define GPTMR_IRQEN_CH2CAPEN_SHIFT (9U)
#define GPTMR_IRQEN_CH2CAPEN_SET(x) (((uint32_t)(x) << GPTMR_IRQEN_CH2CAPEN_SHIFT) & GPTMR_IRQEN_CH2CAPEN_MASK)
#define GPTMR_IRQEN_CH2CAPEN_GET(x) (((uint32_t)(x) & GPTMR_IRQEN_CH2CAPEN_MASK) >> GPTMR_IRQEN_CH2CAPEN_SHIFT)

/*
 * CH2RLDEN (RW)
 *
 * 1- generate interrupt request when ch2rldf flag is set
 */
#define GPTMR_IRQEN_CH2RLDEN_MASK (0x100U)
#define GPTMR_IRQEN_CH2RLDEN_SHIFT (8U)
#define GPTMR_IRQEN_CH2RLDEN_SET(x) (((uint32_t)(x) << GPTMR_IRQEN_CH2RLDEN_SHIFT) & GPTMR_IRQEN_CH2RLDEN_MASK)
#define GPTMR_IRQEN_CH2RLDEN_GET(x) (((uint32_t)(x) & GPTMR_IRQEN_CH2RLDEN_MASK) >> GPTMR_IRQEN_CH2RLDEN_SHIFT)

/*
 * CH1CMP1EN (RW)
 *
 * 1- generate interrupt request when ch1cmp1f flag is set
 */
#define GPTMR_IRQEN_CH1CMP1EN_MASK (0x80U)
#define GPTMR_IRQEN_CH1CMP1EN_SHIFT (7U)
#define GPTMR_IRQEN_CH1CMP1EN_SET(x) (((uint32_t)(x) << GPTMR_IRQEN_CH1CMP1EN_SHIFT) & GPTMR_IRQEN_CH1CMP1EN_MASK)
#define GPTMR_IRQEN_CH1CMP1EN_GET(x) (((uint32_t)(x) & GPTMR_IRQEN_CH1CMP1EN_MASK) >> GPTMR_IRQEN_CH1CMP1EN_SHIFT)

/*
 * CH1CMP0EN (RW)
 *
 * 1- generate interrupt request when ch1cmp0f flag is set
 */
#define GPTMR_IRQEN_CH1CMP0EN_MASK (0x40U)
#define GPTMR_IRQEN_CH1CMP0EN_SHIFT (6U)
#define GPTMR_IRQEN_CH1CMP0EN_SET(x) (((uint32_t)(x) << GPTMR_IRQEN_CH1CMP0EN_SHIFT) & GPTMR_IRQEN_CH1CMP0EN_MASK)
#define GPTMR_IRQEN_CH1CMP0EN_GET(x) (((uint32_t)(x) & GPTMR_IRQEN_CH1CMP0EN_MASK) >> GPTMR_IRQEN_CH1CMP0EN_SHIFT)

/*
 * CH1CAPEN (RW)
 *
 * 1- generate interrupt request when ch1capf flag is set
 */
#define GPTMR_IRQEN_CH1CAPEN_MASK (0x20U)
#define GPTMR_IRQEN_CH1CAPEN_SHIFT (5U)
#define GPTMR_IRQEN_CH1CAPEN_SET(x) (((uint32_t)(x) << GPTMR_IRQEN_CH1CAPEN_SHIFT) & GPTMR_IRQEN_CH1CAPEN_MASK)
#define GPTMR_IRQEN_CH1CAPEN_GET(x) (((uint32_t)(x) & GPTMR_IRQEN_CH1CAPEN_MASK) >> GPTMR_IRQEN_CH1CAPEN_SHIFT)

/*
 * CH1RLDEN (RW)
 *
 * 1- generate interrupt request when ch1rldf flag is set
 */
#define GPTMR_IRQEN_CH1RLDEN_MASK (0x10U)
#define GPTMR_IRQEN_CH1RLDEN_SHIFT (4U)
#define GPTMR_IRQEN_CH1RLDEN_SET(x) (((uint32_t)(x) << GPTMR_IRQEN_CH1RLDEN_SHIFT) & GPTMR_IRQEN_CH1RLDEN_MASK)
#define GPTMR_IRQEN_CH1RLDEN_GET(x) (((uint32_t)(x) & GPTMR_IRQEN_CH1RLDEN_MASK) >> GPTMR_IRQEN_CH1RLDEN_SHIFT)

/*
 * CH0CMP1EN (RW)
 *
 * 1- generate interrupt request when ch0cmp1f flag is set
 */
#define GPTMR_IRQEN_CH0CMP1EN_MASK (0x8U)
#define GPTMR_IRQEN_CH0CMP1EN_SHIFT (3U)
#define GPTMR_IRQEN_CH0CMP1EN_SET(x) (((uint32_t)(x) << GPTMR_IRQEN_CH0CMP1EN_SHIFT) & GPTMR_IRQEN_CH0CMP1EN_MASK)
#define GPTMR_IRQEN_CH0CMP1EN_GET(x) (((uint32_t)(x) & GPTMR_IRQEN_CH0CMP1EN_MASK) >> GPTMR_IRQEN_CH0CMP1EN_SHIFT)

/*
 * CH0CMP0EN (RW)
 *
 * 1- generate interrupt request when ch0cmp0f flag is set
 */
#define GPTMR_IRQEN_CH0CMP0EN_MASK (0x4U)
#define GPTMR_IRQEN_CH0CMP0EN_SHIFT (2U)
#define GPTMR_IRQEN_CH0CMP0EN_SET(x) (((uint32_t)(x) << GPTMR_IRQEN_CH0CMP0EN_SHIFT) & GPTMR_IRQEN_CH0CMP0EN_MASK)
#define GPTMR_IRQEN_CH0CMP0EN_GET(x) (((uint32_t)(x) & GPTMR_IRQEN_CH0CMP0EN_MASK) >> GPTMR_IRQEN_CH0CMP0EN_SHIFT)

/*
 * CH0CAPEN (RW)
 *
 * 1- generate interrupt request when ch0capf flag is set
 */
#define GPTMR_IRQEN_CH0CAPEN_MASK (0x2U)
#define GPTMR_IRQEN_CH0CAPEN_SHIFT (1U)
#define GPTMR_IRQEN_CH0CAPEN_SET(x) (((uint32_t)(x) << GPTMR_IRQEN_CH0CAPEN_SHIFT) & GPTMR_IRQEN_CH0CAPEN_MASK)
#define GPTMR_IRQEN_CH0CAPEN_GET(x) (((uint32_t)(x) & GPTMR_IRQEN_CH0CAPEN_MASK) >> GPTMR_IRQEN_CH0CAPEN_SHIFT)

/*
 * CH0RLDEN (RW)
 *
 * 1- generate interrupt request when ch0rldf flag is set
 */
#define GPTMR_IRQEN_CH0RLDEN_MASK (0x1U)
#define GPTMR_IRQEN_CH0RLDEN_SHIFT (0U)
#define GPTMR_IRQEN_CH0RLDEN_SET(x) (((uint32_t)(x) << GPTMR_IRQEN_CH0RLDEN_SHIFT) & GPTMR_IRQEN_CH0RLDEN_MASK)
#define GPTMR_IRQEN_CH0RLDEN_GET(x) (((uint32_t)(x) & GPTMR_IRQEN_CH0RLDEN_MASK) >> GPTMR_IRQEN_CH0RLDEN_SHIFT)

/* Bitfield definition for register: GCR */
/*
 * SWSYNCT (RW)
 *
 * set this bitfield to trigger software coutner sync event
 */
#define GPTMR_GCR_SWSYNCT_MASK (0xFU)
#define GPTMR_GCR_SWSYNCT_SHIFT (0U)
#define GPTMR_GCR_SWSYNCT_SET(x) (((uint32_t)(x) << GPTMR_GCR_SWSYNCT_SHIFT) & GPTMR_GCR_SWSYNCT_MASK)
#define GPTMR_GCR_SWSYNCT_GET(x) (((uint32_t)(x) & GPTMR_GCR_SWSYNCT_MASK) >> GPTMR_GCR_SWSYNCT_SHIFT)



/* CMP register group index macro definition */
#define GPTMR_CHANNEL_CMP_CMP0 (0UL)
#define GPTMR_CHANNEL_CMP_CMP1 (1UL)

/* CHANNEL register group index macro definition */
#define GPTMR_CHANNEL_CH0 (0UL)
#define GPTMR_CHANNEL_CH1 (1UL)
#define GPTMR_CHANNEL_CH2 (2UL)
#define GPTMR_CHANNEL_CH3 (3UL)


#endif /* HPM_GPTMR_H */
