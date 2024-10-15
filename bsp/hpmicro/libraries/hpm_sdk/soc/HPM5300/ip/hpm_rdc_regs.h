/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_RDC_H
#define HPM_RDC_H

typedef struct {
    __RW uint32_t RDC_CTL;                     /* 0x0: rdc control */
    __R  uint32_t ACC_I;                       /* 0x4: accumulate result of i_channel */
    __R  uint32_t ACC_Q;                       /* 0x8: accumulate result of q_channel */
    __RW uint32_t IN_CTL;                      /* 0xC: input channel selection */
    __RW uint32_t OUT_CTL;                     /* 0x10: output channel selection */
    __R  uint8_t  RESERVED0[32];               /* 0x14 - 0x33: Reserved */
    __RW uint32_t EXC_TIMMING;                 /* 0x34: excitation signal timming setting */
    __RW uint32_t EXC_SCALING;                 /* 0x38: amplitude scaling for excitation */
    __RW uint32_t EXC_OFFSET;                  /* 0x3C: amplitude offset setting */
    __RW uint32_t PWM_SCALING;                 /* 0x40: amplitude scaling for excitation */
    __RW uint32_t PWM_OFFSET;                  /* 0x44: amplitude offset setting */
    __RW uint32_t TRIG_OUT0_CFG;               /* 0x48: Configuration for trigger out 0 in clock cycle */
    __RW uint32_t TRIG_OUT1_CFG;               /* 0x4C: Configuration for trigger out 1 in clock cycle */
    __RW uint32_t PWM_DZ;                      /* 0x50: pwm dead zone control in clock cycle */
    __RW uint32_t SYNC_OUT_CTRL;               /* 0x54: synchronize output signal control */
    __RW uint32_t EXC_SYNC_DLY;                /* 0x58: trigger in delay timming in soc bus cycle */
    __R  uint8_t  RESERVED1[20];               /* 0x5C - 0x6F: Reserved */
    __RW uint32_t MAX_I;                       /* 0x70: max value of  i_channel */
    __RW uint32_t MIN_I;                       /* 0x74: min value of  i_channel */
    __RW uint32_t MAX_Q;                       /* 0x78: max value of  q_channel */
    __RW uint32_t MIN_Q;                       /* 0x7C: min value of  q_channel */
    __RW uint32_t THRS_I;                      /* 0x80: the offset setting for edge detection of the i_channel */
    __RW uint32_t THRS_Q;                      /* 0x84: the offset setting for edge detection of the q_channel */
    __RW uint32_t EDG_DET_CTL;                 /* 0x88: the control for edge detection */
    __RW uint32_t ACC_SCALING;                 /* 0x8C: scaling for accumulation result */
    __RW uint32_t EXC_PERIOD;                  /* 0x90: period of excitation */
    __R  uint8_t  RESERVED2[12];               /* 0x94 - 0x9F: Reserved */
    __RW uint32_t SYNC_DELAY_I;                /* 0xA0: delay  setting in clock cycle for synchronous signal */
    __R  uint8_t  RESERVED3[4];                /* 0xA4 - 0xA7: Reserved */
    __R  uint32_t RISE_DELAY_I;                /* 0xA8: delay in clock cycle between excitation synchrnous signal and rising edge of i_channel data */
    __R  uint32_t FALL_DELAY_I;                /* 0xAC: delay in clock cycle between excitation synchrnous signal and falling edge of i_channel data */
    __R  uint32_t SAMPLE_RISE_I;               /* 0xB0: sample value on rising edge of rectify signal */
    __R  uint32_t SAMPLE_FALL_I;               /* 0xB4: sample value on falling edge of rectify signal */
    __R  uint32_t ACC_CNT_I;                   /* 0xB8: number of accumulation */
    __R  uint32_t SIGN_CNT_I;                  /* 0xBC: sample counter of opposite sign with rectify signal */
    __RW uint32_t SYNC_DELAY_Q;                /* 0xC0: delay  setting in clock cycle for synchronous signal */
    __R  uint8_t  RESERVED4[4];                /* 0xC4 - 0xC7: Reserved */
    __R  uint32_t RISE_DELAY_Q;                /* 0xC8: delay in clock cycle between excitation synchrnous signal and rising edge of q_channel data */
    __R  uint32_t FALL_DELAY_Q;                /* 0xCC: delay in clock cycle between excitation synchrnous signal and falling edge of q_channel data */
    __R  uint32_t SAMPLE_RISE_Q;               /* 0xD0: sample value on rising edge of rectify signal */
    __R  uint32_t SAMPLE_FALL_Q;               /* 0xD4: sample value on falling edge of rectify signal */
    __R  uint32_t ACC_CNT_Q;                   /* 0xD8: number of accumulation */
    __R  uint32_t SIGN_CNT_Q;                  /* 0xDC: sample counter of opposite sign with rectify signal */
    __RW uint32_t AMP_MAX;                     /* 0xE0: the maximum of acc amplitude */
    __RW uint32_t AMP_MIN;                     /* 0xE4: the minimum of acc amplitude */
    __RW uint32_t INT_EN;                      /* 0xE8: the interrupt mask control */
    __W  uint32_t ADC_INT_STATE;               /* 0xEC: the interrupt state */
} RDC_Type;


/* Bitfield definition for register: RDC_CTL */
/*
 * TS_SEL (RW)
 *
 * Time stamp selection for accumulation
 * 0: end of accumulation
 * 1: start of accumulation
 * 2: center of accumulation
 */
#define RDC_RDC_CTL_TS_SEL_MASK (0x300000UL)
#define RDC_RDC_CTL_TS_SEL_SHIFT (20U)
#define RDC_RDC_CTL_TS_SEL_SET(x) (((uint32_t)(x) << RDC_RDC_CTL_TS_SEL_SHIFT) & RDC_RDC_CTL_TS_SEL_MASK)
#define RDC_RDC_CTL_TS_SEL_GET(x) (((uint32_t)(x) & RDC_RDC_CTL_TS_SEL_MASK) >> RDC_RDC_CTL_TS_SEL_SHIFT)

/*
 * ACC_LEN (RW)
 *
 * Accumulate time, support on the fly change
 * 0：1 cycle
 * 1：2 cycles
 * …
 * 255: 256 cycles
 */
#define RDC_RDC_CTL_ACC_LEN_MASK (0xFF000UL)
#define RDC_RDC_CTL_ACC_LEN_SHIFT (12U)
#define RDC_RDC_CTL_ACC_LEN_SET(x) (((uint32_t)(x) << RDC_RDC_CTL_ACC_LEN_SHIFT) & RDC_RDC_CTL_ACC_LEN_MASK)
#define RDC_RDC_CTL_ACC_LEN_GET(x) (((uint32_t)(x) & RDC_RDC_CTL_ACC_LEN_MASK) >> RDC_RDC_CTL_ACC_LEN_SHIFT)

/*
 * RECTIFY_SEL (RW)
 *
 * Select reference point of rectify signal
 * 0: 0 phase of internal exciting signal
 * 1: 90 phase of internal exciting signal
 * 2: 180 phase of internal exciting signal
 * 3: 270 phase of internal exciting signal
 * 4: use value on external pin
 * 5: use  invert value on external pin
 */
#define RDC_RDC_CTL_RECTIFY_SEL_MASK (0x70U)
#define RDC_RDC_CTL_RECTIFY_SEL_SHIFT (4U)
#define RDC_RDC_CTL_RECTIFY_SEL_SET(x) (((uint32_t)(x) << RDC_RDC_CTL_RECTIFY_SEL_SHIFT) & RDC_RDC_CTL_RECTIFY_SEL_MASK)
#define RDC_RDC_CTL_RECTIFY_SEL_GET(x) (((uint32_t)(x) & RDC_RDC_CTL_RECTIFY_SEL_MASK) >> RDC_RDC_CTL_RECTIFY_SEL_SHIFT)

/*
 * ACC_EN (RW)
 *
 * Enable rdc accumulate
 * 0: rdc disable
 * 1: rdc enable
 */
#define RDC_RDC_CTL_ACC_EN_MASK (0x4U)
#define RDC_RDC_CTL_ACC_EN_SHIFT (2U)
#define RDC_RDC_CTL_ACC_EN_SET(x) (((uint32_t)(x) << RDC_RDC_CTL_ACC_EN_SHIFT) & RDC_RDC_CTL_ACC_EN_MASK)
#define RDC_RDC_CTL_ACC_EN_GET(x) (((uint32_t)(x) & RDC_RDC_CTL_ACC_EN_MASK) >> RDC_RDC_CTL_ACC_EN_SHIFT)

/*
 * EXC_START (RW1C)
 *
 * Write 1 start excite signal, always read 0
 * 0: no effect
 * 1: start excite signal
 */
#define RDC_RDC_CTL_EXC_START_MASK (0x2U)
#define RDC_RDC_CTL_EXC_START_SHIFT (1U)
#define RDC_RDC_CTL_EXC_START_SET(x) (((uint32_t)(x) << RDC_RDC_CTL_EXC_START_SHIFT) & RDC_RDC_CTL_EXC_START_MASK)
#define RDC_RDC_CTL_EXC_START_GET(x) (((uint32_t)(x) & RDC_RDC_CTL_EXC_START_MASK) >> RDC_RDC_CTL_EXC_START_SHIFT)

/*
 * EXC_EN (RW)
 *
 * Enable rdc excite signal
 * 0: rdc disable
 * 1: rdc enable
 */
#define RDC_RDC_CTL_EXC_EN_MASK (0x1U)
#define RDC_RDC_CTL_EXC_EN_SHIFT (0U)
#define RDC_RDC_CTL_EXC_EN_SET(x) (((uint32_t)(x) << RDC_RDC_CTL_EXC_EN_SHIFT) & RDC_RDC_CTL_EXC_EN_MASK)
#define RDC_RDC_CTL_EXC_EN_GET(x) (((uint32_t)(x) & RDC_RDC_CTL_EXC_EN_MASK) >> RDC_RDC_CTL_EXC_EN_SHIFT)

/* Bitfield definition for register: ACC_I */
/*
 * ACC (RO)
 *
 * accumulate result of i_channel, this is a signed number
 */
#define RDC_ACC_I_ACC_MASK (0xFFFFFFFFUL)
#define RDC_ACC_I_ACC_SHIFT (0U)
#define RDC_ACC_I_ACC_GET(x) (((uint32_t)(x) & RDC_ACC_I_ACC_MASK) >> RDC_ACC_I_ACC_SHIFT)

/* Bitfield definition for register: ACC_Q */
/*
 * ACC (RO)
 *
 * accumulate result of q_channel, this is a signed number
 */
#define RDC_ACC_Q_ACC_MASK (0xFFFFFFFFUL)
#define RDC_ACC_Q_ACC_SHIFT (0U)
#define RDC_ACC_Q_ACC_GET(x) (((uint32_t)(x) & RDC_ACC_Q_ACC_MASK) >> RDC_ACC_Q_ACC_SHIFT)

/* Bitfield definition for register: IN_CTL */
/*
 * PORT_Q_SEL (RW)
 *
 * Input port selection for q_channel,
 * 0:sel port0
 * 1:sel port1
 */
#define RDC_IN_CTL_PORT_Q_SEL_MASK (0x100000UL)
#define RDC_IN_CTL_PORT_Q_SEL_SHIFT (20U)
#define RDC_IN_CTL_PORT_Q_SEL_SET(x) (((uint32_t)(x) << RDC_IN_CTL_PORT_Q_SEL_SHIFT) & RDC_IN_CTL_PORT_Q_SEL_MASK)
#define RDC_IN_CTL_PORT_Q_SEL_GET(x) (((uint32_t)(x) & RDC_IN_CTL_PORT_Q_SEL_MASK) >> RDC_IN_CTL_PORT_Q_SEL_SHIFT)

/*
 * CH_Q_SEL (RW)
 *
 * Input channel selection for q_channel
 * 0: channel 0 selected
 * 1: channel 1 selected
 * …
 * 31: channel 31 selected
 */
#define RDC_IN_CTL_CH_Q_SEL_MASK (0x1F000UL)
#define RDC_IN_CTL_CH_Q_SEL_SHIFT (12U)
#define RDC_IN_CTL_CH_Q_SEL_SET(x) (((uint32_t)(x) << RDC_IN_CTL_CH_Q_SEL_SHIFT) & RDC_IN_CTL_CH_Q_SEL_MASK)
#define RDC_IN_CTL_CH_Q_SEL_GET(x) (((uint32_t)(x) & RDC_IN_CTL_CH_Q_SEL_MASK) >> RDC_IN_CTL_CH_Q_SEL_SHIFT)

/*
 * PORT_I_SEL (RW)
 *
 * Input port selection for i_channel,
 * 0:sel port0
 * 1:sel port1
 */
#define RDC_IN_CTL_PORT_I_SEL_MASK (0x100U)
#define RDC_IN_CTL_PORT_I_SEL_SHIFT (8U)
#define RDC_IN_CTL_PORT_I_SEL_SET(x) (((uint32_t)(x) << RDC_IN_CTL_PORT_I_SEL_SHIFT) & RDC_IN_CTL_PORT_I_SEL_MASK)
#define RDC_IN_CTL_PORT_I_SEL_GET(x) (((uint32_t)(x) & RDC_IN_CTL_PORT_I_SEL_MASK) >> RDC_IN_CTL_PORT_I_SEL_SHIFT)

/*
 * CH_I_SEL (RW)
 *
 * Input channel selection for i_channel
 * 0: channel 0 selected
 * 1: channel 1 selected
 * …
 * 31: channel 31 selected
 */
#define RDC_IN_CTL_CH_I_SEL_MASK (0x1FU)
#define RDC_IN_CTL_CH_I_SEL_SHIFT (0U)
#define RDC_IN_CTL_CH_I_SEL_SET(x) (((uint32_t)(x) << RDC_IN_CTL_CH_I_SEL_SHIFT) & RDC_IN_CTL_CH_I_SEL_MASK)
#define RDC_IN_CTL_CH_I_SEL_GET(x) (((uint32_t)(x) & RDC_IN_CTL_CH_I_SEL_MASK) >> RDC_IN_CTL_CH_I_SEL_SHIFT)

/* Bitfield definition for register: OUT_CTL */
/*
 * CH_Q_SEL (RW)
 *
 * Output channel selection for q_channel
 */
#define RDC_OUT_CTL_CH_Q_SEL_MASK (0x1F00U)
#define RDC_OUT_CTL_CH_Q_SEL_SHIFT (8U)
#define RDC_OUT_CTL_CH_Q_SEL_SET(x) (((uint32_t)(x) << RDC_OUT_CTL_CH_Q_SEL_SHIFT) & RDC_OUT_CTL_CH_Q_SEL_MASK)
#define RDC_OUT_CTL_CH_Q_SEL_GET(x) (((uint32_t)(x) & RDC_OUT_CTL_CH_Q_SEL_MASK) >> RDC_OUT_CTL_CH_Q_SEL_SHIFT)

/*
 * CH_I_SEL (RW)
 *
 * Output channel selection for i_channel
 */
#define RDC_OUT_CTL_CH_I_SEL_MASK (0x1FU)
#define RDC_OUT_CTL_CH_I_SEL_SHIFT (0U)
#define RDC_OUT_CTL_CH_I_SEL_SET(x) (((uint32_t)(x) << RDC_OUT_CTL_CH_I_SEL_SHIFT) & RDC_OUT_CTL_CH_I_SEL_MASK)
#define RDC_OUT_CTL_CH_I_SEL_GET(x) (((uint32_t)(x) & RDC_OUT_CTL_CH_I_SEL_MASK) >> RDC_OUT_CTL_CH_I_SEL_SHIFT)

/* Bitfield definition for register: EXC_TIMMING */
/*
 * SWAP (RW)
 *
 * Swap output of PWM and DAC
 * 0: disable swap
 * 1: swap output
 */
#define RDC_EXC_TIMMING_SWAP_MASK (0x1000000UL)
#define RDC_EXC_TIMMING_SWAP_SHIFT (24U)
#define RDC_EXC_TIMMING_SWAP_SET(x) (((uint32_t)(x) << RDC_EXC_TIMMING_SWAP_SHIFT) & RDC_EXC_TIMMING_SWAP_MASK)
#define RDC_EXC_TIMMING_SWAP_GET(x) (((uint32_t)(x) & RDC_EXC_TIMMING_SWAP_MASK) >> RDC_EXC_TIMMING_SWAP_SHIFT)

/*
 * PWM_PRD (RW)
 *
 * Pwm period in samples，
 * 0：1 sample period
 * 1:   2 sample period
 * ...
 * 15: 16 sample period
 */
#define RDC_EXC_TIMMING_PWM_PRD_MASK (0xF00000UL)
#define RDC_EXC_TIMMING_PWM_PRD_SHIFT (20U)
#define RDC_EXC_TIMMING_PWM_PRD_SET(x) (((uint32_t)(x) << RDC_EXC_TIMMING_PWM_PRD_SHIFT) & RDC_EXC_TIMMING_PWM_PRD_MASK)
#define RDC_EXC_TIMMING_PWM_PRD_GET(x) (((uint32_t)(x) & RDC_EXC_TIMMING_PWM_PRD_MASK) >> RDC_EXC_TIMMING_PWM_PRD_SHIFT)

/*
 * SMP_NUM (RW)
 *
 * Number of sample every excitation period
 * 0: 4 point
 * 1: 8 point
 * …
 * 8: 1024 point
 */
#define RDC_EXC_TIMMING_SMP_NUM_MASK (0xF0000UL)
#define RDC_EXC_TIMMING_SMP_NUM_SHIFT (16U)
#define RDC_EXC_TIMMING_SMP_NUM_SET(x) (((uint32_t)(x) << RDC_EXC_TIMMING_SMP_NUM_SHIFT) & RDC_EXC_TIMMING_SMP_NUM_MASK)
#define RDC_EXC_TIMMING_SMP_NUM_GET(x) (((uint32_t)(x) & RDC_EXC_TIMMING_SMP_NUM_MASK) >> RDC_EXC_TIMMING_SMP_NUM_SHIFT)

/*
 * SMP_RATE (RW)
 *
 * The period for excitation sample in clock cycle，
 * 0: not allowed
 * 1: 1 cycle
 * 2: 2 cycles
 * …
 * 65535 : 65535 cycles
 */
#define RDC_EXC_TIMMING_SMP_RATE_MASK (0xFFFFU)
#define RDC_EXC_TIMMING_SMP_RATE_SHIFT (0U)
#define RDC_EXC_TIMMING_SMP_RATE_SET(x) (((uint32_t)(x) << RDC_EXC_TIMMING_SMP_RATE_SHIFT) & RDC_EXC_TIMMING_SMP_RATE_MASK)
#define RDC_EXC_TIMMING_SMP_RATE_GET(x) (((uint32_t)(x) & RDC_EXC_TIMMING_SMP_RATE_MASK) >> RDC_EXC_TIMMING_SMP_RATE_SHIFT)

/* Bitfield definition for register: EXC_SCALING */
/*
 * AMP_EXP (RW)
 *
 * Amplitude scaling for excitation,  amplitude = [table value] x man / 2^exp
 */
#define RDC_EXC_SCALING_AMP_EXP_MASK (0xF0U)
#define RDC_EXC_SCALING_AMP_EXP_SHIFT (4U)
#define RDC_EXC_SCALING_AMP_EXP_SET(x) (((uint32_t)(x) << RDC_EXC_SCALING_AMP_EXP_SHIFT) & RDC_EXC_SCALING_AMP_EXP_MASK)
#define RDC_EXC_SCALING_AMP_EXP_GET(x) (((uint32_t)(x) & RDC_EXC_SCALING_AMP_EXP_MASK) >> RDC_EXC_SCALING_AMP_EXP_SHIFT)

/*
 * AMP_MAN (RW)
 *
 * Amplitude scaling for excitation,  amplitude = [table value] x man / 2^exp
 */
#define RDC_EXC_SCALING_AMP_MAN_MASK (0xFU)
#define RDC_EXC_SCALING_AMP_MAN_SHIFT (0U)
#define RDC_EXC_SCALING_AMP_MAN_SET(x) (((uint32_t)(x) << RDC_EXC_SCALING_AMP_MAN_SHIFT) & RDC_EXC_SCALING_AMP_MAN_MASK)
#define RDC_EXC_SCALING_AMP_MAN_GET(x) (((uint32_t)(x) & RDC_EXC_SCALING_AMP_MAN_MASK) >> RDC_EXC_SCALING_AMP_MAN_SHIFT)

/* Bitfield definition for register: EXC_OFFSET */
/*
 * AMP_OFFSET (RW)
 *
 * Offset for excitation
 */
#define RDC_EXC_OFFSET_AMP_OFFSET_MASK (0xFFFFFFUL)
#define RDC_EXC_OFFSET_AMP_OFFSET_SHIFT (0U)
#define RDC_EXC_OFFSET_AMP_OFFSET_SET(x) (((uint32_t)(x) << RDC_EXC_OFFSET_AMP_OFFSET_SHIFT) & RDC_EXC_OFFSET_AMP_OFFSET_MASK)
#define RDC_EXC_OFFSET_AMP_OFFSET_GET(x) (((uint32_t)(x) & RDC_EXC_OFFSET_AMP_OFFSET_MASK) >> RDC_EXC_OFFSET_AMP_OFFSET_SHIFT)

/* Bitfield definition for register: PWM_SCALING */
/*
 * N_POL (RW)
 *
 * Polarity of exc_n signal
 * 0: high active
 * 1: low active
 */
#define RDC_PWM_SCALING_N_POL_MASK (0x2000U)
#define RDC_PWM_SCALING_N_POL_SHIFT (13U)
#define RDC_PWM_SCALING_N_POL_SET(x) (((uint32_t)(x) << RDC_PWM_SCALING_N_POL_SHIFT) & RDC_PWM_SCALING_N_POL_MASK)
#define RDC_PWM_SCALING_N_POL_GET(x) (((uint32_t)(x) & RDC_PWM_SCALING_N_POL_MASK) >> RDC_PWM_SCALING_N_POL_SHIFT)

/*
 * P_POL (RW)
 *
 * Polarity of exc_p signal
 * 0: high active
 * 1: low active
 */
#define RDC_PWM_SCALING_P_POL_MASK (0x1000U)
#define RDC_PWM_SCALING_P_POL_SHIFT (12U)
#define RDC_PWM_SCALING_P_POL_SET(x) (((uint32_t)(x) << RDC_PWM_SCALING_P_POL_SHIFT) & RDC_PWM_SCALING_P_POL_MASK)
#define RDC_PWM_SCALING_P_POL_GET(x) (((uint32_t)(x) & RDC_PWM_SCALING_P_POL_MASK) >> RDC_PWM_SCALING_P_POL_SHIFT)

/*
 * DITHER (RW)
 *
 * Enable dither of pwm
 * 0: disable
 * 1: enable
 */
#define RDC_PWM_SCALING_DITHER_MASK (0x100U)
#define RDC_PWM_SCALING_DITHER_SHIFT (8U)
#define RDC_PWM_SCALING_DITHER_SET(x) (((uint32_t)(x) << RDC_PWM_SCALING_DITHER_SHIFT) & RDC_PWM_SCALING_DITHER_MASK)
#define RDC_PWM_SCALING_DITHER_GET(x) (((uint32_t)(x) & RDC_PWM_SCALING_DITHER_MASK) >> RDC_PWM_SCALING_DITHER_SHIFT)

/*
 * AMP_EXP (RW)
 *
 * Amplitude scaling for excitation,  amplitude = [table value] x man / 2^exp
 */
#define RDC_PWM_SCALING_AMP_EXP_MASK (0xF0U)
#define RDC_PWM_SCALING_AMP_EXP_SHIFT (4U)
#define RDC_PWM_SCALING_AMP_EXP_SET(x) (((uint32_t)(x) << RDC_PWM_SCALING_AMP_EXP_SHIFT) & RDC_PWM_SCALING_AMP_EXP_MASK)
#define RDC_PWM_SCALING_AMP_EXP_GET(x) (((uint32_t)(x) & RDC_PWM_SCALING_AMP_EXP_MASK) >> RDC_PWM_SCALING_AMP_EXP_SHIFT)

/*
 * AMP_MAN (RW)
 *
 * Amplitude scaling for excitation,  amplitude = [table value] x man / 2^exp
 */
#define RDC_PWM_SCALING_AMP_MAN_MASK (0xFU)
#define RDC_PWM_SCALING_AMP_MAN_SHIFT (0U)
#define RDC_PWM_SCALING_AMP_MAN_SET(x) (((uint32_t)(x) << RDC_PWM_SCALING_AMP_MAN_SHIFT) & RDC_PWM_SCALING_AMP_MAN_MASK)
#define RDC_PWM_SCALING_AMP_MAN_GET(x) (((uint32_t)(x) & RDC_PWM_SCALING_AMP_MAN_MASK) >> RDC_PWM_SCALING_AMP_MAN_SHIFT)

/* Bitfield definition for register: PWM_OFFSET */
/*
 * AMP_OFFSET (RW)
 *
 * Offset for excitation
 */
#define RDC_PWM_OFFSET_AMP_OFFSET_MASK (0xFFFFFFUL)
#define RDC_PWM_OFFSET_AMP_OFFSET_SHIFT (0U)
#define RDC_PWM_OFFSET_AMP_OFFSET_SET(x) (((uint32_t)(x) << RDC_PWM_OFFSET_AMP_OFFSET_SHIFT) & RDC_PWM_OFFSET_AMP_OFFSET_MASK)
#define RDC_PWM_OFFSET_AMP_OFFSET_GET(x) (((uint32_t)(x) & RDC_PWM_OFFSET_AMP_OFFSET_MASK) >> RDC_PWM_OFFSET_AMP_OFFSET_SHIFT)

/* Bitfield definition for register: TRIG_OUT0_CFG */
/*
 * ENABLE (RW)
 *
 * Enable trigger out0
 * 0: disable
 * 1: enable
 */
#define RDC_TRIG_OUT0_CFG_ENABLE_MASK (0x100000UL)
#define RDC_TRIG_OUT0_CFG_ENABLE_SHIFT (20U)
#define RDC_TRIG_OUT0_CFG_ENABLE_SET(x) (((uint32_t)(x) << RDC_TRIG_OUT0_CFG_ENABLE_SHIFT) & RDC_TRIG_OUT0_CFG_ENABLE_MASK)
#define RDC_TRIG_OUT0_CFG_ENABLE_GET(x) (((uint32_t)(x) & RDC_TRIG_OUT0_CFG_ENABLE_MASK) >> RDC_TRIG_OUT0_CFG_ENABLE_SHIFT)

/*
 * LEAD_TIM (RW)
 *
 * Lead time for trigger out0 from center of low level , this is a signed value
 * …
 * 2: 2 cycle befor center of low level
 * 1: 1 cycle before center of low level
 * 0: center of low level
 * -1: 1cycle after center of low level
 * -2: 2cycle after center of low level
 */
#define RDC_TRIG_OUT0_CFG_LEAD_TIM_MASK (0xFFFFFUL)
#define RDC_TRIG_OUT0_CFG_LEAD_TIM_SHIFT (0U)
#define RDC_TRIG_OUT0_CFG_LEAD_TIM_SET(x) (((uint32_t)(x) << RDC_TRIG_OUT0_CFG_LEAD_TIM_SHIFT) & RDC_TRIG_OUT0_CFG_LEAD_TIM_MASK)
#define RDC_TRIG_OUT0_CFG_LEAD_TIM_GET(x) (((uint32_t)(x) & RDC_TRIG_OUT0_CFG_LEAD_TIM_MASK) >> RDC_TRIG_OUT0_CFG_LEAD_TIM_SHIFT)

/* Bitfield definition for register: TRIG_OUT1_CFG */
/*
 * ENABLE (RW)
 *
 * Enable trigger out1
 * 0: disable
 * 1: enable
 */
#define RDC_TRIG_OUT1_CFG_ENABLE_MASK (0x100000UL)
#define RDC_TRIG_OUT1_CFG_ENABLE_SHIFT (20U)
#define RDC_TRIG_OUT1_CFG_ENABLE_SET(x) (((uint32_t)(x) << RDC_TRIG_OUT1_CFG_ENABLE_SHIFT) & RDC_TRIG_OUT1_CFG_ENABLE_MASK)
#define RDC_TRIG_OUT1_CFG_ENABLE_GET(x) (((uint32_t)(x) & RDC_TRIG_OUT1_CFG_ENABLE_MASK) >> RDC_TRIG_OUT1_CFG_ENABLE_SHIFT)

/*
 * LEAD_TIM (RW)
 *
 * Lead time for trigger out0 from center of hight level , this is a signed value
 * …
 * 2: 2 cycle befor center of hight level
 * 1: 1 cycle before center of hight level
 * 0: center of hight level
 * -1: 1cycle after center of hight level
 * -2: 2cycle after center of hight level
 */
#define RDC_TRIG_OUT1_CFG_LEAD_TIM_MASK (0xFFFFFUL)
#define RDC_TRIG_OUT1_CFG_LEAD_TIM_SHIFT (0U)
#define RDC_TRIG_OUT1_CFG_LEAD_TIM_SET(x) (((uint32_t)(x) << RDC_TRIG_OUT1_CFG_LEAD_TIM_SHIFT) & RDC_TRIG_OUT1_CFG_LEAD_TIM_MASK)
#define RDC_TRIG_OUT1_CFG_LEAD_TIM_GET(x) (((uint32_t)(x) & RDC_TRIG_OUT1_CFG_LEAD_TIM_MASK) >> RDC_TRIG_OUT1_CFG_LEAD_TIM_SHIFT)

/* Bitfield definition for register: PWM_DZ */
/*
 * DZ_N (RW)
 *
 * Exc_n dead zone  in clock cycle before swap
 * 0: no dead zone
 * 1: 1 cycle dead zone
 * 2: 2 cycle dead zone
 * …
 */
#define RDC_PWM_DZ_DZ_N_MASK (0xFF00U)
#define RDC_PWM_DZ_DZ_N_SHIFT (8U)
#define RDC_PWM_DZ_DZ_N_SET(x) (((uint32_t)(x) << RDC_PWM_DZ_DZ_N_SHIFT) & RDC_PWM_DZ_DZ_N_MASK)
#define RDC_PWM_DZ_DZ_N_GET(x) (((uint32_t)(x) & RDC_PWM_DZ_DZ_N_MASK) >> RDC_PWM_DZ_DZ_N_SHIFT)

/*
 * DZ_P (RW)
 *
 * Exc_p dead zone  in clock cycle before swap
 * 0: no dead zone
 * 1: 1 cycle dead zone
 * 2: 2 cycle dead zone
 * …
 */
#define RDC_PWM_DZ_DZ_P_MASK (0xFFU)
#define RDC_PWM_DZ_DZ_P_SHIFT (0U)
#define RDC_PWM_DZ_DZ_P_SET(x) (((uint32_t)(x) << RDC_PWM_DZ_DZ_P_SHIFT) & RDC_PWM_DZ_DZ_P_MASK)
#define RDC_PWM_DZ_DZ_P_GET(x) (((uint32_t)(x) & RDC_PWM_DZ_DZ_P_MASK) >> RDC_PWM_DZ_DZ_P_SHIFT)

/* Bitfield definition for register: SYNC_OUT_CTRL */
/*
 * PWM_OUT_DLY (RO)
 *
 * Delay bettween the delyed trigger and the first pwm pulse in clock cycle
 * 1: 1 cycle
 * 2: 2 cycle
 * …
 */
#define RDC_SYNC_OUT_CTRL_PWM_OUT_DLY_MASK (0xFFFF0000UL)
#define RDC_SYNC_OUT_CTRL_PWM_OUT_DLY_SHIFT (16U)
#define RDC_SYNC_OUT_CTRL_PWM_OUT_DLY_GET(x) (((uint32_t)(x) & RDC_SYNC_OUT_CTRL_PWM_OUT_DLY_MASK) >> RDC_SYNC_OUT_CTRL_PWM_OUT_DLY_SHIFT)

/*
 * MIN2TRIG_EN (RW)
 *
 * Enable trigger out from the min point of exciting signal
 * 1: enable
 * 0: disable
 */
#define RDC_SYNC_OUT_CTRL_MIN2TRIG_EN_MASK (0x20U)
#define RDC_SYNC_OUT_CTRL_MIN2TRIG_EN_SHIFT (5U)
#define RDC_SYNC_OUT_CTRL_MIN2TRIG_EN_SET(x) (((uint32_t)(x) << RDC_SYNC_OUT_CTRL_MIN2TRIG_EN_SHIFT) & RDC_SYNC_OUT_CTRL_MIN2TRIG_EN_MASK)
#define RDC_SYNC_OUT_CTRL_MIN2TRIG_EN_GET(x) (((uint32_t)(x) & RDC_SYNC_OUT_CTRL_MIN2TRIG_EN_MASK) >> RDC_SYNC_OUT_CTRL_MIN2TRIG_EN_SHIFT)

/*
 * MAX2TRIG_EN (RW)
 *
 * Enable trigger out from the max point of exciting signal
 * 1: enable
 * 0: disable
 */
#define RDC_SYNC_OUT_CTRL_MAX2TRIG_EN_MASK (0x10U)
#define RDC_SYNC_OUT_CTRL_MAX2TRIG_EN_SHIFT (4U)
#define RDC_SYNC_OUT_CTRL_MAX2TRIG_EN_SET(x) (((uint32_t)(x) << RDC_SYNC_OUT_CTRL_MAX2TRIG_EN_SHIFT) & RDC_SYNC_OUT_CTRL_MAX2TRIG_EN_MASK)
#define RDC_SYNC_OUT_CTRL_MAX2TRIG_EN_GET(x) (((uint32_t)(x) & RDC_SYNC_OUT_CTRL_MAX2TRIG_EN_MASK) >> RDC_SYNC_OUT_CTRL_MAX2TRIG_EN_SHIFT)

/*
 * SYNC_OUT_SEL (RW)
 *
 * Select output synchornize signal
 * 0: 0 phase of internal exciting signal
 * 1: 90 phase of internal exciting signal
 * 2: 180 phase of internal exciting signal
 * 3: 270 phase of internal exciting signal
 */
#define RDC_SYNC_OUT_CTRL_SYNC_OUT_SEL_MASK (0x3U)
#define RDC_SYNC_OUT_CTRL_SYNC_OUT_SEL_SHIFT (0U)
#define RDC_SYNC_OUT_CTRL_SYNC_OUT_SEL_SET(x) (((uint32_t)(x) << RDC_SYNC_OUT_CTRL_SYNC_OUT_SEL_SHIFT) & RDC_SYNC_OUT_CTRL_SYNC_OUT_SEL_MASK)
#define RDC_SYNC_OUT_CTRL_SYNC_OUT_SEL_GET(x) (((uint32_t)(x) & RDC_SYNC_OUT_CTRL_SYNC_OUT_SEL_MASK) >> RDC_SYNC_OUT_CTRL_SYNC_OUT_SEL_SHIFT)

/* Bitfield definition for register: EXC_SYNC_DLY */
/*
 * DISABLE (RW)
 *
 * Disable hardware trigger input
 * 0: enable
 * 1: disable
 */
#define RDC_EXC_SYNC_DLY_DISABLE_MASK (0x1000000UL)
#define RDC_EXC_SYNC_DLY_DISABLE_SHIFT (24U)
#define RDC_EXC_SYNC_DLY_DISABLE_SET(x) (((uint32_t)(x) << RDC_EXC_SYNC_DLY_DISABLE_SHIFT) & RDC_EXC_SYNC_DLY_DISABLE_MASK)
#define RDC_EXC_SYNC_DLY_DISABLE_GET(x) (((uint32_t)(x) & RDC_EXC_SYNC_DLY_DISABLE_MASK) >> RDC_EXC_SYNC_DLY_DISABLE_SHIFT)

/*
 * DELAY (RW)
 *
 * Trigger in delay timming in bus cycle from rising edge of trigger signal
 * 0:   1 cycle
 * 1:  2 cycle
 * …
 * 0xffffff:  2^24 cycle
 */
#define RDC_EXC_SYNC_DLY_DELAY_MASK (0xFFFFFFUL)
#define RDC_EXC_SYNC_DLY_DELAY_SHIFT (0U)
#define RDC_EXC_SYNC_DLY_DELAY_SET(x) (((uint32_t)(x) << RDC_EXC_SYNC_DLY_DELAY_SHIFT) & RDC_EXC_SYNC_DLY_DELAY_MASK)
#define RDC_EXC_SYNC_DLY_DELAY_GET(x) (((uint32_t)(x) & RDC_EXC_SYNC_DLY_DELAY_MASK) >> RDC_EXC_SYNC_DLY_DELAY_SHIFT)

/* Bitfield definition for register: MAX_I */
/*
 * MAX (RWC)
 *
 * Max value of  i_channel, write clear
 */
#define RDC_MAX_I_MAX_MASK (0xFFFFFF00UL)
#define RDC_MAX_I_MAX_SHIFT (8U)
#define RDC_MAX_I_MAX_SET(x) (((uint32_t)(x) << RDC_MAX_I_MAX_SHIFT) & RDC_MAX_I_MAX_MASK)
#define RDC_MAX_I_MAX_GET(x) (((uint32_t)(x) & RDC_MAX_I_MAX_MASK) >> RDC_MAX_I_MAX_SHIFT)

/*
 * VALID (RWC)
 *
 * Max value valid, write clear
 * 0: max value is not valid
 * 1: max value is valid
 */
#define RDC_MAX_I_VALID_MASK (0x1U)
#define RDC_MAX_I_VALID_SHIFT (0U)
#define RDC_MAX_I_VALID_SET(x) (((uint32_t)(x) << RDC_MAX_I_VALID_SHIFT) & RDC_MAX_I_VALID_MASK)
#define RDC_MAX_I_VALID_GET(x) (((uint32_t)(x) & RDC_MAX_I_VALID_MASK) >> RDC_MAX_I_VALID_SHIFT)

/* Bitfield definition for register: MIN_I */
/*
 * MIN (RWC)
 *
 * Min value of  i_channel, write clear
 */
#define RDC_MIN_I_MIN_MASK (0xFFFFFF00UL)
#define RDC_MIN_I_MIN_SHIFT (8U)
#define RDC_MIN_I_MIN_SET(x) (((uint32_t)(x) << RDC_MIN_I_MIN_SHIFT) & RDC_MIN_I_MIN_MASK)
#define RDC_MIN_I_MIN_GET(x) (((uint32_t)(x) & RDC_MIN_I_MIN_MASK) >> RDC_MIN_I_MIN_SHIFT)

/*
 * VALID (RWC)
 *
 * Min value valid, write clear
 * 0: min value is not valid
 * 1: min value is valid
 */
#define RDC_MIN_I_VALID_MASK (0x1U)
#define RDC_MIN_I_VALID_SHIFT (0U)
#define RDC_MIN_I_VALID_SET(x) (((uint32_t)(x) << RDC_MIN_I_VALID_SHIFT) & RDC_MIN_I_VALID_MASK)
#define RDC_MIN_I_VALID_GET(x) (((uint32_t)(x) & RDC_MIN_I_VALID_MASK) >> RDC_MIN_I_VALID_SHIFT)

/* Bitfield definition for register: MAX_Q */
/*
 * MAX (RWC)
 *
 * Max value of  q_channel, write clear
 */
#define RDC_MAX_Q_MAX_MASK (0xFFFFFF00UL)
#define RDC_MAX_Q_MAX_SHIFT (8U)
#define RDC_MAX_Q_MAX_SET(x) (((uint32_t)(x) << RDC_MAX_Q_MAX_SHIFT) & RDC_MAX_Q_MAX_MASK)
#define RDC_MAX_Q_MAX_GET(x) (((uint32_t)(x) & RDC_MAX_Q_MAX_MASK) >> RDC_MAX_Q_MAX_SHIFT)

/*
 * VALID (RWC)
 *
 * Max value valid, write clear
 * 0: max value is not valid
 * 1: max value is valid
 */
#define RDC_MAX_Q_VALID_MASK (0x1U)
#define RDC_MAX_Q_VALID_SHIFT (0U)
#define RDC_MAX_Q_VALID_SET(x) (((uint32_t)(x) << RDC_MAX_Q_VALID_SHIFT) & RDC_MAX_Q_VALID_MASK)
#define RDC_MAX_Q_VALID_GET(x) (((uint32_t)(x) & RDC_MAX_Q_VALID_MASK) >> RDC_MAX_Q_VALID_SHIFT)

/* Bitfield definition for register: MIN_Q */
/*
 * MIN (RWC)
 *
 * Min value of  q_channel, write clear
 */
#define RDC_MIN_Q_MIN_MASK (0xFFFFFF00UL)
#define RDC_MIN_Q_MIN_SHIFT (8U)
#define RDC_MIN_Q_MIN_SET(x) (((uint32_t)(x) << RDC_MIN_Q_MIN_SHIFT) & RDC_MIN_Q_MIN_MASK)
#define RDC_MIN_Q_MIN_GET(x) (((uint32_t)(x) & RDC_MIN_Q_MIN_MASK) >> RDC_MIN_Q_MIN_SHIFT)

/*
 * VALID (RWC)
 *
 * Min value valid, write clear
 * 0: min value is not valid
 * 1: min value is valid
 */
#define RDC_MIN_Q_VALID_MASK (0x1U)
#define RDC_MIN_Q_VALID_SHIFT (0U)
#define RDC_MIN_Q_VALID_SET(x) (((uint32_t)(x) << RDC_MIN_Q_VALID_SHIFT) & RDC_MIN_Q_VALID_MASK)
#define RDC_MIN_Q_VALID_GET(x) (((uint32_t)(x) & RDC_MIN_Q_VALID_MASK) >> RDC_MIN_Q_VALID_SHIFT)

/* Bitfield definition for register: THRS_I */
/*
 * THRS (RW)
 *
 * The offset setting for edge detection of the i_channel, signed number
 * …
 * 2: the offset is 0x800000+2
 * 1: the offset is 0x800000+1
 * 0: the offset is 0x800000
 * -1: the offset is 0x800000-1
 * -2: the offset is 0x800000-2
 * …
 */
#define RDC_THRS_I_THRS_MASK (0xFFFFFF00UL)
#define RDC_THRS_I_THRS_SHIFT (8U)
#define RDC_THRS_I_THRS_SET(x) (((uint32_t)(x) << RDC_THRS_I_THRS_SHIFT) & RDC_THRS_I_THRS_MASK)
#define RDC_THRS_I_THRS_GET(x) (((uint32_t)(x) & RDC_THRS_I_THRS_MASK) >> RDC_THRS_I_THRS_SHIFT)

/* Bitfield definition for register: THRS_Q */
/*
 * THRS (RW)
 *
 * The offset setting for edge detection of the q_channel, signed number
 * …
 * 2: the offset is 0x800000+2
 * 1: the offset is 0x800000+1
 * 0: the offset is 0x800000
 * -1: the offset is 0x800000-1
 * -2: the offset is 0x800000-2
 * …
 */
#define RDC_THRS_Q_THRS_MASK (0xFFFFFF00UL)
#define RDC_THRS_Q_THRS_SHIFT (8U)
#define RDC_THRS_Q_THRS_SET(x) (((uint32_t)(x) << RDC_THRS_Q_THRS_SHIFT) & RDC_THRS_Q_THRS_MASK)
#define RDC_THRS_Q_THRS_GET(x) (((uint32_t)(x) & RDC_THRS_Q_THRS_MASK) >> RDC_THRS_Q_THRS_SHIFT)

/* Bitfield definition for register: EDG_DET_CTL */
/*
 * HOLD (RW)
 *
 * The minimum edge distance  in sample
 * 0:1 sample
 * 1:2 sample
 * 2:3 samples
 * …
 * 63:64 samples
 */
#define RDC_EDG_DET_CTL_HOLD_MASK (0x3F0U)
#define RDC_EDG_DET_CTL_HOLD_SHIFT (4U)
#define RDC_EDG_DET_CTL_HOLD_SET(x) (((uint32_t)(x) << RDC_EDG_DET_CTL_HOLD_SHIFT) & RDC_EDG_DET_CTL_HOLD_MASK)
#define RDC_EDG_DET_CTL_HOLD_GET(x) (((uint32_t)(x) & RDC_EDG_DET_CTL_HOLD_MASK) >> RDC_EDG_DET_CTL_HOLD_SHIFT)

/*
 * FILTER (RW)
 *
 * The continuous positive or negative number for edge detection
 * 0: 1
 * 1: 2
 * …
 * 7: 8
 */
#define RDC_EDG_DET_CTL_FILTER_MASK (0x7U)
#define RDC_EDG_DET_CTL_FILTER_SHIFT (0U)
#define RDC_EDG_DET_CTL_FILTER_SET(x) (((uint32_t)(x) << RDC_EDG_DET_CTL_FILTER_SHIFT) & RDC_EDG_DET_CTL_FILTER_MASK)
#define RDC_EDG_DET_CTL_FILTER_GET(x) (((uint32_t)(x) & RDC_EDG_DET_CTL_FILTER_MASK) >> RDC_EDG_DET_CTL_FILTER_SHIFT)

/* Bitfield definition for register: ACC_SCALING */
/*
 * TOXIC_LK (RW)
 *
 * Toxic accumulation data be removed control
 * 1: enable
 * 0: disable
 */
#define RDC_ACC_SCALING_TOXIC_LK_MASK (0x100U)
#define RDC_ACC_SCALING_TOXIC_LK_SHIFT (8U)
#define RDC_ACC_SCALING_TOXIC_LK_SET(x) (((uint32_t)(x) << RDC_ACC_SCALING_TOXIC_LK_SHIFT) & RDC_ACC_SCALING_TOXIC_LK_MASK)
#define RDC_ACC_SCALING_TOXIC_LK_GET(x) (((uint32_t)(x) & RDC_ACC_SCALING_TOXIC_LK_MASK) >> RDC_ACC_SCALING_TOXIC_LK_SHIFT)

/*
 * ACC_SHIFT (RW)
 *
 * Accumulation value shift control, this is a sign number.
 * 0: {acc[39],acc[38:8]}
 * 1: {acc[39],acc[37:7]}
 * 2: {acc[39],acc[36:6]}
 * …
 * 7: {acc[39],acc[31:1]}
 * 8: {acc[39],acc[30:0]}
 * 9: acc/2^9
 * 10: acc/2^10
 * …
 * 15:acc/2^15
 */
#define RDC_ACC_SCALING_ACC_SHIFT_MASK (0xFU)
#define RDC_ACC_SCALING_ACC_SHIFT_SHIFT (0U)
#define RDC_ACC_SCALING_ACC_SHIFT_SET(x) (((uint32_t)(x) << RDC_ACC_SCALING_ACC_SHIFT_SHIFT) & RDC_ACC_SCALING_ACC_SHIFT_MASK)
#define RDC_ACC_SCALING_ACC_SHIFT_GET(x) (((uint32_t)(x) & RDC_ACC_SCALING_ACC_SHIFT_MASK) >> RDC_ACC_SCALING_ACC_SHIFT_SHIFT)

/* Bitfield definition for register: EXC_PERIOD */
/*
 * EXC_PERIOD (RW)
 *
 * The num in clock cycle for period of excitation
 * 0: invalid value
 * 1:1 cycle
 * 2:2 cycles
 * …
 */
#define RDC_EXC_PERIOD_EXC_PERIOD_MASK (0xFFFFFFFFUL)
#define RDC_EXC_PERIOD_EXC_PERIOD_SHIFT (0U)
#define RDC_EXC_PERIOD_EXC_PERIOD_SET(x) (((uint32_t)(x) << RDC_EXC_PERIOD_EXC_PERIOD_SHIFT) & RDC_EXC_PERIOD_EXC_PERIOD_MASK)
#define RDC_EXC_PERIOD_EXC_PERIOD_GET(x) (((uint32_t)(x) & RDC_EXC_PERIOD_EXC_PERIOD_MASK) >> RDC_EXC_PERIOD_EXC_PERIOD_SHIFT)

/* Bitfield definition for register: SYNC_DELAY_I */
/*
 * DELAY (RW)
 *
 * Delay  in clock cycle for synchronous signal, the value shoud less than half of exc_period.exc_period.
 * 0: invalid value
 * 1: 1 cycles
 * 2: 2 cycles
 * ...
 */
#define RDC_SYNC_DELAY_I_DELAY_MASK (0xFFFFFFFFUL)
#define RDC_SYNC_DELAY_I_DELAY_SHIFT (0U)
#define RDC_SYNC_DELAY_I_DELAY_SET(x) (((uint32_t)(x) << RDC_SYNC_DELAY_I_DELAY_SHIFT) & RDC_SYNC_DELAY_I_DELAY_MASK)
#define RDC_SYNC_DELAY_I_DELAY_GET(x) (((uint32_t)(x) & RDC_SYNC_DELAY_I_DELAY_MASK) >> RDC_SYNC_DELAY_I_DELAY_SHIFT)

/* Bitfield definition for register: RISE_DELAY_I */
/*
 * RISE_DELAY (RO)
 *
 * Delay value on rising edge of  i_channel data
 * 0: 1 cycle
 * 1: 2 cycles
 * …
 */
#define RDC_RISE_DELAY_I_RISE_DELAY_MASK (0xFFFFFFFFUL)
#define RDC_RISE_DELAY_I_RISE_DELAY_SHIFT (0U)
#define RDC_RISE_DELAY_I_RISE_DELAY_GET(x) (((uint32_t)(x) & RDC_RISE_DELAY_I_RISE_DELAY_MASK) >> RDC_RISE_DELAY_I_RISE_DELAY_SHIFT)

/* Bitfield definition for register: FALL_DELAY_I */
/*
 * FALL_DELAY (RO)
 *
 * Delay value on falling edge of  i_channel data
 * 0: 1 cycle
 * 1: 2 cycles
 * …
 */
#define RDC_FALL_DELAY_I_FALL_DELAY_MASK (0xFFFFFFFFUL)
#define RDC_FALL_DELAY_I_FALL_DELAY_SHIFT (0U)
#define RDC_FALL_DELAY_I_FALL_DELAY_GET(x) (((uint32_t)(x) & RDC_FALL_DELAY_I_FALL_DELAY_MASK) >> RDC_FALL_DELAY_I_FALL_DELAY_SHIFT)

/* Bitfield definition for register: SAMPLE_RISE_I */
/*
 * VALUE (RO)
 *
 * sample value on rising edge of rectify signal
 */
#define RDC_SAMPLE_RISE_I_VALUE_MASK (0xFFFFFF00UL)
#define RDC_SAMPLE_RISE_I_VALUE_SHIFT (8U)
#define RDC_SAMPLE_RISE_I_VALUE_GET(x) (((uint32_t)(x) & RDC_SAMPLE_RISE_I_VALUE_MASK) >> RDC_SAMPLE_RISE_I_VALUE_SHIFT)

/* Bitfield definition for register: SAMPLE_FALL_I */
/*
 * VALUE (RO)
 *
 * sample value on falling edge of rectify signal
 */
#define RDC_SAMPLE_FALL_I_VALUE_MASK (0xFFFFFF00UL)
#define RDC_SAMPLE_FALL_I_VALUE_SHIFT (8U)
#define RDC_SAMPLE_FALL_I_VALUE_GET(x) (((uint32_t)(x) & RDC_SAMPLE_FALL_I_VALUE_MASK) >> RDC_SAMPLE_FALL_I_VALUE_SHIFT)

/* Bitfield definition for register: ACC_CNT_I */
/*
 * CNT_NEG (RO)
 *
 * sample number during the negtive of rectify signal
 * 1: 1
 * 2: 2
 * …
 */
#define RDC_ACC_CNT_I_CNT_NEG_MASK (0xFFFF0000UL)
#define RDC_ACC_CNT_I_CNT_NEG_SHIFT (16U)
#define RDC_ACC_CNT_I_CNT_NEG_GET(x) (((uint32_t)(x) & RDC_ACC_CNT_I_CNT_NEG_MASK) >> RDC_ACC_CNT_I_CNT_NEG_SHIFT)

/*
 * CNT_POS (RO)
 *
 * sample number during the positive of rectify signal
 * 1: 1
 * 2: 2
 * …
 */
#define RDC_ACC_CNT_I_CNT_POS_MASK (0xFFFFU)
#define RDC_ACC_CNT_I_CNT_POS_SHIFT (0U)
#define RDC_ACC_CNT_I_CNT_POS_GET(x) (((uint32_t)(x) & RDC_ACC_CNT_I_CNT_POS_MASK) >> RDC_ACC_CNT_I_CNT_POS_SHIFT)

/* Bitfield definition for register: SIGN_CNT_I */
/*
 * CNT_NEG (RO)
 *
 * Positive sample counter during negative rectify signal
 */
#define RDC_SIGN_CNT_I_CNT_NEG_MASK (0xFFFF0000UL)
#define RDC_SIGN_CNT_I_CNT_NEG_SHIFT (16U)
#define RDC_SIGN_CNT_I_CNT_NEG_GET(x) (((uint32_t)(x) & RDC_SIGN_CNT_I_CNT_NEG_MASK) >> RDC_SIGN_CNT_I_CNT_NEG_SHIFT)

/*
 * CNT_POS (RO)
 *
 * Negative sample counter during positive rectify signal
 */
#define RDC_SIGN_CNT_I_CNT_POS_MASK (0xFFFFU)
#define RDC_SIGN_CNT_I_CNT_POS_SHIFT (0U)
#define RDC_SIGN_CNT_I_CNT_POS_GET(x) (((uint32_t)(x) & RDC_SIGN_CNT_I_CNT_POS_MASK) >> RDC_SIGN_CNT_I_CNT_POS_SHIFT)

/* Bitfield definition for register: SYNC_DELAY_Q */
/*
 * DELAY (RW)
 *
 * Delay  in clock cycle for synchronous signal, the value shoud less than half of exc_period.exc_period.
 * 0: invalid value
 * 1: 1 cycles
 * 2: 2 cycles
 * ...
 */
#define RDC_SYNC_DELAY_Q_DELAY_MASK (0xFFFFFFFFUL)
#define RDC_SYNC_DELAY_Q_DELAY_SHIFT (0U)
#define RDC_SYNC_DELAY_Q_DELAY_SET(x) (((uint32_t)(x) << RDC_SYNC_DELAY_Q_DELAY_SHIFT) & RDC_SYNC_DELAY_Q_DELAY_MASK)
#define RDC_SYNC_DELAY_Q_DELAY_GET(x) (((uint32_t)(x) & RDC_SYNC_DELAY_Q_DELAY_MASK) >> RDC_SYNC_DELAY_Q_DELAY_SHIFT)

/* Bitfield definition for register: RISE_DELAY_Q */
/*
 * RISE_DELAY (RO)
 *
 * Delay value on rising edge of  q_channel data
 * 0: 1 cycle
 * 1: 2 cycles
 * …
 */
#define RDC_RISE_DELAY_Q_RISE_DELAY_MASK (0xFFFFFFFFUL)
#define RDC_RISE_DELAY_Q_RISE_DELAY_SHIFT (0U)
#define RDC_RISE_DELAY_Q_RISE_DELAY_GET(x) (((uint32_t)(x) & RDC_RISE_DELAY_Q_RISE_DELAY_MASK) >> RDC_RISE_DELAY_Q_RISE_DELAY_SHIFT)

/* Bitfield definition for register: FALL_DELAY_Q */
/*
 * FALL_DELAY (RO)
 *
 * Delay value on falling edge of  q_channel data
 * 0: 1 cycle
 * 1: 2 cycles
 * …
 */
#define RDC_FALL_DELAY_Q_FALL_DELAY_MASK (0xFFFFFFFFUL)
#define RDC_FALL_DELAY_Q_FALL_DELAY_SHIFT (0U)
#define RDC_FALL_DELAY_Q_FALL_DELAY_GET(x) (((uint32_t)(x) & RDC_FALL_DELAY_Q_FALL_DELAY_MASK) >> RDC_FALL_DELAY_Q_FALL_DELAY_SHIFT)

/* Bitfield definition for register: SAMPLE_RISE_Q */
/*
 * VALUE (RO)
 *
 * sample value on rising edge of rectify signal
 */
#define RDC_SAMPLE_RISE_Q_VALUE_MASK (0xFFFFFF00UL)
#define RDC_SAMPLE_RISE_Q_VALUE_SHIFT (8U)
#define RDC_SAMPLE_RISE_Q_VALUE_GET(x) (((uint32_t)(x) & RDC_SAMPLE_RISE_Q_VALUE_MASK) >> RDC_SAMPLE_RISE_Q_VALUE_SHIFT)

/* Bitfield definition for register: SAMPLE_FALL_Q */
/*
 * VALUE (RO)
 *
 * sample value on falling edge of rectify signal
 */
#define RDC_SAMPLE_FALL_Q_VALUE_MASK (0xFFFFFF00UL)
#define RDC_SAMPLE_FALL_Q_VALUE_SHIFT (8U)
#define RDC_SAMPLE_FALL_Q_VALUE_GET(x) (((uint32_t)(x) & RDC_SAMPLE_FALL_Q_VALUE_MASK) >> RDC_SAMPLE_FALL_Q_VALUE_SHIFT)

/* Bitfield definition for register: ACC_CNT_Q */
/*
 * CNT_NEG (RO)
 *
 * sample number during the negtive of rectify signal
 * 1: 1
 * 2: 2
 * …
 */
#define RDC_ACC_CNT_Q_CNT_NEG_MASK (0xFFFF0000UL)
#define RDC_ACC_CNT_Q_CNT_NEG_SHIFT (16U)
#define RDC_ACC_CNT_Q_CNT_NEG_GET(x) (((uint32_t)(x) & RDC_ACC_CNT_Q_CNT_NEG_MASK) >> RDC_ACC_CNT_Q_CNT_NEG_SHIFT)

/*
 * CNT_POS (RO)
 *
 * sample number during the positive of rectify signal
 * 1: 1
 * 2: 2
 * …
 */
#define RDC_ACC_CNT_Q_CNT_POS_MASK (0xFFFFU)
#define RDC_ACC_CNT_Q_CNT_POS_SHIFT (0U)
#define RDC_ACC_CNT_Q_CNT_POS_GET(x) (((uint32_t)(x) & RDC_ACC_CNT_Q_CNT_POS_MASK) >> RDC_ACC_CNT_Q_CNT_POS_SHIFT)

/* Bitfield definition for register: SIGN_CNT_Q */
/*
 * CNT_NEG (RO)
 *
 * Positive sample counter during negative rectify signal
 */
#define RDC_SIGN_CNT_Q_CNT_NEG_MASK (0xFFFF0000UL)
#define RDC_SIGN_CNT_Q_CNT_NEG_SHIFT (16U)
#define RDC_SIGN_CNT_Q_CNT_NEG_GET(x) (((uint32_t)(x) & RDC_SIGN_CNT_Q_CNT_NEG_MASK) >> RDC_SIGN_CNT_Q_CNT_NEG_SHIFT)

/*
 * CNT_POS (RO)
 *
 * Negative sample counter during positive rectify signal
 */
#define RDC_SIGN_CNT_Q_CNT_POS_MASK (0xFFFFU)
#define RDC_SIGN_CNT_Q_CNT_POS_SHIFT (0U)
#define RDC_SIGN_CNT_Q_CNT_POS_GET(x) (((uint32_t)(x) & RDC_SIGN_CNT_Q_CNT_POS_MASK) >> RDC_SIGN_CNT_Q_CNT_POS_SHIFT)

/* Bitfield definition for register: AMP_MAX */
/*
 * MAX (RW)
 *
 * the maximum of acc amplitude
 */
#define RDC_AMP_MAX_MAX_MASK (0xFFFFFFFFUL)
#define RDC_AMP_MAX_MAX_SHIFT (0U)
#define RDC_AMP_MAX_MAX_SET(x) (((uint32_t)(x) << RDC_AMP_MAX_MAX_SHIFT) & RDC_AMP_MAX_MAX_MASK)
#define RDC_AMP_MAX_MAX_GET(x) (((uint32_t)(x) & RDC_AMP_MAX_MAX_MASK) >> RDC_AMP_MAX_MAX_SHIFT)

/* Bitfield definition for register: AMP_MIN */
/*
 * MIN (RW)
 *
 * the minimum of acc amplitude
 */
#define RDC_AMP_MIN_MIN_MASK (0xFFFFFFFFUL)
#define RDC_AMP_MIN_MIN_SHIFT (0U)
#define RDC_AMP_MIN_MIN_SET(x) (((uint32_t)(x) << RDC_AMP_MIN_MIN_SHIFT) & RDC_AMP_MIN_MIN_MASK)
#define RDC_AMP_MIN_MIN_GET(x) (((uint32_t)(x) & RDC_AMP_MIN_MIN_MASK) >> RDC_AMP_MIN_MIN_SHIFT)

/* Bitfield definition for register: INT_EN */
/*
 * INT_EN (RW)
 *
 * enable interrupt output
 */
#define RDC_INT_EN_INT_EN_MASK (0x80000000UL)
#define RDC_INT_EN_INT_EN_SHIFT (31U)
#define RDC_INT_EN_INT_EN_SET(x) (((uint32_t)(x) << RDC_INT_EN_INT_EN_SHIFT) & RDC_INT_EN_INT_EN_MASK)
#define RDC_INT_EN_INT_EN_GET(x) (((uint32_t)(x) & RDC_INT_EN_INT_EN_MASK) >> RDC_INT_EN_INT_EN_SHIFT)

/*
 * ACC_VLD_I_EN (RW)
 *
 * i_channel accumulate valid interrupt enable for i_channel
 */
#define RDC_INT_EN_ACC_VLD_I_EN_MASK (0x8000U)
#define RDC_INT_EN_ACC_VLD_I_EN_SHIFT (15U)
#define RDC_INT_EN_ACC_VLD_I_EN_SET(x) (((uint32_t)(x) << RDC_INT_EN_ACC_VLD_I_EN_SHIFT) & RDC_INT_EN_ACC_VLD_I_EN_MASK)
#define RDC_INT_EN_ACC_VLD_I_EN_GET(x) (((uint32_t)(x) & RDC_INT_EN_ACC_VLD_I_EN_MASK) >> RDC_INT_EN_ACC_VLD_I_EN_SHIFT)

/*
 * ACC_VLD_Q_EN (RW)
 *
 * q_channel accumulate valid interrupt enable for i_channel
 */
#define RDC_INT_EN_ACC_VLD_Q_EN_MASK (0x4000U)
#define RDC_INT_EN_ACC_VLD_Q_EN_SHIFT (14U)
#define RDC_INT_EN_ACC_VLD_Q_EN_SET(x) (((uint32_t)(x) << RDC_INT_EN_ACC_VLD_Q_EN_SHIFT) & RDC_INT_EN_ACC_VLD_Q_EN_MASK)
#define RDC_INT_EN_ACC_VLD_Q_EN_GET(x) (((uint32_t)(x) & RDC_INT_EN_ACC_VLD_Q_EN_MASK) >> RDC_INT_EN_ACC_VLD_Q_EN_SHIFT)

/*
 * RISING_DELAY_I_EN (RW)
 *
 * i_channel delayed rectify signal rising edge interrupt enable
 */
#define RDC_INT_EN_RISING_DELAY_I_EN_MASK (0x2000U)
#define RDC_INT_EN_RISING_DELAY_I_EN_SHIFT (13U)
#define RDC_INT_EN_RISING_DELAY_I_EN_SET(x) (((uint32_t)(x) << RDC_INT_EN_RISING_DELAY_I_EN_SHIFT) & RDC_INT_EN_RISING_DELAY_I_EN_MASK)
#define RDC_INT_EN_RISING_DELAY_I_EN_GET(x) (((uint32_t)(x) & RDC_INT_EN_RISING_DELAY_I_EN_MASK) >> RDC_INT_EN_RISING_DELAY_I_EN_SHIFT)

/*
 * FALLING_DELAY_I_EN (RW)
 *
 * i_channel delayed rectify signal falling edge interrupt enable
 */
#define RDC_INT_EN_FALLING_DELAY_I_EN_MASK (0x1000U)
#define RDC_INT_EN_FALLING_DELAY_I_EN_SHIFT (12U)
#define RDC_INT_EN_FALLING_DELAY_I_EN_SET(x) (((uint32_t)(x) << RDC_INT_EN_FALLING_DELAY_I_EN_SHIFT) & RDC_INT_EN_FALLING_DELAY_I_EN_MASK)
#define RDC_INT_EN_FALLING_DELAY_I_EN_GET(x) (((uint32_t)(x) & RDC_INT_EN_FALLING_DELAY_I_EN_MASK) >> RDC_INT_EN_FALLING_DELAY_I_EN_SHIFT)

/*
 * RISING_DELAY_Q_EN (RW)
 *
 * q_channel delayed rectify signal rising edge interrupt enable
 */
#define RDC_INT_EN_RISING_DELAY_Q_EN_MASK (0x800U)
#define RDC_INT_EN_RISING_DELAY_Q_EN_SHIFT (11U)
#define RDC_INT_EN_RISING_DELAY_Q_EN_SET(x) (((uint32_t)(x) << RDC_INT_EN_RISING_DELAY_Q_EN_SHIFT) & RDC_INT_EN_RISING_DELAY_Q_EN_MASK)
#define RDC_INT_EN_RISING_DELAY_Q_EN_GET(x) (((uint32_t)(x) & RDC_INT_EN_RISING_DELAY_Q_EN_MASK) >> RDC_INT_EN_RISING_DELAY_Q_EN_SHIFT)

/*
 * FALLING_DELAY_Q_EN (RW)
 *
 * q_channel delayed rectify signal falling edge interrupt enable
 */
#define RDC_INT_EN_FALLING_DELAY_Q_EN_MASK (0x400U)
#define RDC_INT_EN_FALLING_DELAY_Q_EN_SHIFT (10U)
#define RDC_INT_EN_FALLING_DELAY_Q_EN_SET(x) (((uint32_t)(x) << RDC_INT_EN_FALLING_DELAY_Q_EN_SHIFT) & RDC_INT_EN_FALLING_DELAY_Q_EN_MASK)
#define RDC_INT_EN_FALLING_DELAY_Q_EN_GET(x) (((uint32_t)(x) & RDC_INT_EN_FALLING_DELAY_Q_EN_MASK) >> RDC_INT_EN_FALLING_DELAY_Q_EN_SHIFT)

/*
 * SAMPLE_RISING_I_EN (RW)
 *
 * i_channel rising edge interrupt enable
 */
#define RDC_INT_EN_SAMPLE_RISING_I_EN_MASK (0x200U)
#define RDC_INT_EN_SAMPLE_RISING_I_EN_SHIFT (9U)
#define RDC_INT_EN_SAMPLE_RISING_I_EN_SET(x) (((uint32_t)(x) << RDC_INT_EN_SAMPLE_RISING_I_EN_SHIFT) & RDC_INT_EN_SAMPLE_RISING_I_EN_MASK)
#define RDC_INT_EN_SAMPLE_RISING_I_EN_GET(x) (((uint32_t)(x) & RDC_INT_EN_SAMPLE_RISING_I_EN_MASK) >> RDC_INT_EN_SAMPLE_RISING_I_EN_SHIFT)

/*
 * SAMPLE_FALLING_I_EN (RW)
 *
 * i_channel falling edge interrupt enable
 */
#define RDC_INT_EN_SAMPLE_FALLING_I_EN_MASK (0x100U)
#define RDC_INT_EN_SAMPLE_FALLING_I_EN_SHIFT (8U)
#define RDC_INT_EN_SAMPLE_FALLING_I_EN_SET(x) (((uint32_t)(x) << RDC_INT_EN_SAMPLE_FALLING_I_EN_SHIFT) & RDC_INT_EN_SAMPLE_FALLING_I_EN_MASK)
#define RDC_INT_EN_SAMPLE_FALLING_I_EN_GET(x) (((uint32_t)(x) & RDC_INT_EN_SAMPLE_FALLING_I_EN_MASK) >> RDC_INT_EN_SAMPLE_FALLING_I_EN_SHIFT)

/*
 * SAMPLE_RISING_Q_EN (RW)
 *
 * q_channel rising edge interrupt enable
 */
#define RDC_INT_EN_SAMPLE_RISING_Q_EN_MASK (0x80U)
#define RDC_INT_EN_SAMPLE_RISING_Q_EN_SHIFT (7U)
#define RDC_INT_EN_SAMPLE_RISING_Q_EN_SET(x) (((uint32_t)(x) << RDC_INT_EN_SAMPLE_RISING_Q_EN_SHIFT) & RDC_INT_EN_SAMPLE_RISING_Q_EN_MASK)
#define RDC_INT_EN_SAMPLE_RISING_Q_EN_GET(x) (((uint32_t)(x) & RDC_INT_EN_SAMPLE_RISING_Q_EN_MASK) >> RDC_INT_EN_SAMPLE_RISING_Q_EN_SHIFT)

/*
 * SAMPLE_FALLING_Q_EN (RW)
 *
 * q_channel falling edge interrupt enable
 */
#define RDC_INT_EN_SAMPLE_FALLING_Q_EN_MASK (0x40U)
#define RDC_INT_EN_SAMPLE_FALLING_Q_EN_SHIFT (6U)
#define RDC_INT_EN_SAMPLE_FALLING_Q_EN_SET(x) (((uint32_t)(x) << RDC_INT_EN_SAMPLE_FALLING_Q_EN_SHIFT) & RDC_INT_EN_SAMPLE_FALLING_Q_EN_MASK)
#define RDC_INT_EN_SAMPLE_FALLING_Q_EN_GET(x) (((uint32_t)(x) & RDC_INT_EN_SAMPLE_FALLING_Q_EN_MASK) >> RDC_INT_EN_SAMPLE_FALLING_Q_EN_SHIFT)

/*
 * ACC_VLD_I_OVH_EN (RW)
 *
 * i_channel accumulate overflow interrupt enable
 */
#define RDC_INT_EN_ACC_VLD_I_OVH_EN_MASK (0x20U)
#define RDC_INT_EN_ACC_VLD_I_OVH_EN_SHIFT (5U)
#define RDC_INT_EN_ACC_VLD_I_OVH_EN_SET(x) (((uint32_t)(x) << RDC_INT_EN_ACC_VLD_I_OVH_EN_SHIFT) & RDC_INT_EN_ACC_VLD_I_OVH_EN_MASK)
#define RDC_INT_EN_ACC_VLD_I_OVH_EN_GET(x) (((uint32_t)(x) & RDC_INT_EN_ACC_VLD_I_OVH_EN_MASK) >> RDC_INT_EN_ACC_VLD_I_OVH_EN_SHIFT)

/*
 * ACC_VLD_Q_OVH_EN (RW)
 *
 * q_channel accumulate overflow interrupt enable
 */
#define RDC_INT_EN_ACC_VLD_Q_OVH_EN_MASK (0x10U)
#define RDC_INT_EN_ACC_VLD_Q_OVH_EN_SHIFT (4U)
#define RDC_INT_EN_ACC_VLD_Q_OVH_EN_SET(x) (((uint32_t)(x) << RDC_INT_EN_ACC_VLD_Q_OVH_EN_SHIFT) & RDC_INT_EN_ACC_VLD_Q_OVH_EN_MASK)
#define RDC_INT_EN_ACC_VLD_Q_OVH_EN_GET(x) (((uint32_t)(x) & RDC_INT_EN_ACC_VLD_Q_OVH_EN_MASK) >> RDC_INT_EN_ACC_VLD_Q_OVH_EN_SHIFT)

/*
 * ACC_VLD_I_OVL_EN (RW)
 *
 * i_channel accumulate underflow interrupt enable
 */
#define RDC_INT_EN_ACC_VLD_I_OVL_EN_MASK (0x8U)
#define RDC_INT_EN_ACC_VLD_I_OVL_EN_SHIFT (3U)
#define RDC_INT_EN_ACC_VLD_I_OVL_EN_SET(x) (((uint32_t)(x) << RDC_INT_EN_ACC_VLD_I_OVL_EN_SHIFT) & RDC_INT_EN_ACC_VLD_I_OVL_EN_MASK)
#define RDC_INT_EN_ACC_VLD_I_OVL_EN_GET(x) (((uint32_t)(x) & RDC_INT_EN_ACC_VLD_I_OVL_EN_MASK) >> RDC_INT_EN_ACC_VLD_I_OVL_EN_SHIFT)

/*
 * ACC_VLD_Q_OVL_EN (RW)
 *
 * q_channel accumulate underflow interrupt enable
 */
#define RDC_INT_EN_ACC_VLD_Q_OVL_EN_MASK (0x4U)
#define RDC_INT_EN_ACC_VLD_Q_OVL_EN_SHIFT (2U)
#define RDC_INT_EN_ACC_VLD_Q_OVL_EN_SET(x) (((uint32_t)(x) << RDC_INT_EN_ACC_VLD_Q_OVL_EN_SHIFT) & RDC_INT_EN_ACC_VLD_Q_OVL_EN_MASK)
#define RDC_INT_EN_ACC_VLD_Q_OVL_EN_GET(x) (((uint32_t)(x) & RDC_INT_EN_ACC_VLD_Q_OVL_EN_MASK) >> RDC_INT_EN_ACC_VLD_Q_OVL_EN_SHIFT)

/*
 * ACC_AMP_OVH_EN (RW)
 *
 * accumulate ample overflow interrupt enable
 */
#define RDC_INT_EN_ACC_AMP_OVH_EN_MASK (0x2U)
#define RDC_INT_EN_ACC_AMP_OVH_EN_SHIFT (1U)
#define RDC_INT_EN_ACC_AMP_OVH_EN_SET(x) (((uint32_t)(x) << RDC_INT_EN_ACC_AMP_OVH_EN_SHIFT) & RDC_INT_EN_ACC_AMP_OVH_EN_MASK)
#define RDC_INT_EN_ACC_AMP_OVH_EN_GET(x) (((uint32_t)(x) & RDC_INT_EN_ACC_AMP_OVH_EN_MASK) >> RDC_INT_EN_ACC_AMP_OVH_EN_SHIFT)

/*
 * ACC_AMP_OVL_EN (RW)
 *
 * accumulate ample underflow interrupt enable
 */
#define RDC_INT_EN_ACC_AMP_OVL_EN_MASK (0x1U)
#define RDC_INT_EN_ACC_AMP_OVL_EN_SHIFT (0U)
#define RDC_INT_EN_ACC_AMP_OVL_EN_SET(x) (((uint32_t)(x) << RDC_INT_EN_ACC_AMP_OVL_EN_SHIFT) & RDC_INT_EN_ACC_AMP_OVL_EN_MASK)
#define RDC_INT_EN_ACC_AMP_OVL_EN_GET(x) (((uint32_t)(x) & RDC_INT_EN_ACC_AMP_OVL_EN_MASK) >> RDC_INT_EN_ACC_AMP_OVL_EN_SHIFT)

/* Bitfield definition for register: ADC_INT_STATE */
/*
 * ACC_VLD_I_STA (W1C)
 *
 * i_channel accumulate valid interrupt status for i_channel
 */
#define RDC_ADC_INT_STATE_ACC_VLD_I_STA_MASK (0x8000U)
#define RDC_ADC_INT_STATE_ACC_VLD_I_STA_SHIFT (15U)
#define RDC_ADC_INT_STATE_ACC_VLD_I_STA_SET(x) (((uint32_t)(x) << RDC_ADC_INT_STATE_ACC_VLD_I_STA_SHIFT) & RDC_ADC_INT_STATE_ACC_VLD_I_STA_MASK)
#define RDC_ADC_INT_STATE_ACC_VLD_I_STA_GET(x) (((uint32_t)(x) & RDC_ADC_INT_STATE_ACC_VLD_I_STA_MASK) >> RDC_ADC_INT_STATE_ACC_VLD_I_STA_SHIFT)

/*
 * ACC_VLD_Q_STA (W1C)
 *
 * q_channel accumulate valid interrupt status for i_channel
 */
#define RDC_ADC_INT_STATE_ACC_VLD_Q_STA_MASK (0x4000U)
#define RDC_ADC_INT_STATE_ACC_VLD_Q_STA_SHIFT (14U)
#define RDC_ADC_INT_STATE_ACC_VLD_Q_STA_SET(x) (((uint32_t)(x) << RDC_ADC_INT_STATE_ACC_VLD_Q_STA_SHIFT) & RDC_ADC_INT_STATE_ACC_VLD_Q_STA_MASK)
#define RDC_ADC_INT_STATE_ACC_VLD_Q_STA_GET(x) (((uint32_t)(x) & RDC_ADC_INT_STATE_ACC_VLD_Q_STA_MASK) >> RDC_ADC_INT_STATE_ACC_VLD_Q_STA_SHIFT)

/*
 * RISING_DELAY_I_STA (W1C)
 *
 * i_channel delayed rectify signal rising edge interrupt status
 */
#define RDC_ADC_INT_STATE_RISING_DELAY_I_STA_MASK (0x2000U)
#define RDC_ADC_INT_STATE_RISING_DELAY_I_STA_SHIFT (13U)
#define RDC_ADC_INT_STATE_RISING_DELAY_I_STA_SET(x) (((uint32_t)(x) << RDC_ADC_INT_STATE_RISING_DELAY_I_STA_SHIFT) & RDC_ADC_INT_STATE_RISING_DELAY_I_STA_MASK)
#define RDC_ADC_INT_STATE_RISING_DELAY_I_STA_GET(x) (((uint32_t)(x) & RDC_ADC_INT_STATE_RISING_DELAY_I_STA_MASK) >> RDC_ADC_INT_STATE_RISING_DELAY_I_STA_SHIFT)

/*
 * FALLING_DELAY_I_STA (W1C)
 *
 * i_channel delayed rectify signal falling edge interrupt status
 */
#define RDC_ADC_INT_STATE_FALLING_DELAY_I_STA_MASK (0x1000U)
#define RDC_ADC_INT_STATE_FALLING_DELAY_I_STA_SHIFT (12U)
#define RDC_ADC_INT_STATE_FALLING_DELAY_I_STA_SET(x) (((uint32_t)(x) << RDC_ADC_INT_STATE_FALLING_DELAY_I_STA_SHIFT) & RDC_ADC_INT_STATE_FALLING_DELAY_I_STA_MASK)
#define RDC_ADC_INT_STATE_FALLING_DELAY_I_STA_GET(x) (((uint32_t)(x) & RDC_ADC_INT_STATE_FALLING_DELAY_I_STA_MASK) >> RDC_ADC_INT_STATE_FALLING_DELAY_I_STA_SHIFT)

/*
 * RISING_DELAY_Q_STA (W1C)
 *
 * q_channel delayed rectify signal rising edge interrupt status
 */
#define RDC_ADC_INT_STATE_RISING_DELAY_Q_STA_MASK (0x800U)
#define RDC_ADC_INT_STATE_RISING_DELAY_Q_STA_SHIFT (11U)
#define RDC_ADC_INT_STATE_RISING_DELAY_Q_STA_SET(x) (((uint32_t)(x) << RDC_ADC_INT_STATE_RISING_DELAY_Q_STA_SHIFT) & RDC_ADC_INT_STATE_RISING_DELAY_Q_STA_MASK)
#define RDC_ADC_INT_STATE_RISING_DELAY_Q_STA_GET(x) (((uint32_t)(x) & RDC_ADC_INT_STATE_RISING_DELAY_Q_STA_MASK) >> RDC_ADC_INT_STATE_RISING_DELAY_Q_STA_SHIFT)

/*
 * FALLING_DELAY_Q_STA (W1C)
 *
 * q_channel delayed rectify signal falling edge interrupt status
 */
#define RDC_ADC_INT_STATE_FALLING_DELAY_Q_STA_MASK (0x400U)
#define RDC_ADC_INT_STATE_FALLING_DELAY_Q_STA_SHIFT (10U)
#define RDC_ADC_INT_STATE_FALLING_DELAY_Q_STA_SET(x) (((uint32_t)(x) << RDC_ADC_INT_STATE_FALLING_DELAY_Q_STA_SHIFT) & RDC_ADC_INT_STATE_FALLING_DELAY_Q_STA_MASK)
#define RDC_ADC_INT_STATE_FALLING_DELAY_Q_STA_GET(x) (((uint32_t)(x) & RDC_ADC_INT_STATE_FALLING_DELAY_Q_STA_MASK) >> RDC_ADC_INT_STATE_FALLING_DELAY_Q_STA_SHIFT)

/*
 * SAMPLE_RISING_I_STA (W1C)
 *
 * i_channel rising edge interrupt status
 */
#define RDC_ADC_INT_STATE_SAMPLE_RISING_I_STA_MASK (0x200U)
#define RDC_ADC_INT_STATE_SAMPLE_RISING_I_STA_SHIFT (9U)
#define RDC_ADC_INT_STATE_SAMPLE_RISING_I_STA_SET(x) (((uint32_t)(x) << RDC_ADC_INT_STATE_SAMPLE_RISING_I_STA_SHIFT) & RDC_ADC_INT_STATE_SAMPLE_RISING_I_STA_MASK)
#define RDC_ADC_INT_STATE_SAMPLE_RISING_I_STA_GET(x) (((uint32_t)(x) & RDC_ADC_INT_STATE_SAMPLE_RISING_I_STA_MASK) >> RDC_ADC_INT_STATE_SAMPLE_RISING_I_STA_SHIFT)

/*
 * SAMPLE_FALLING_I_STA (W1C)
 *
 * i_channel falling edge interrupt status
 */
#define RDC_ADC_INT_STATE_SAMPLE_FALLING_I_STA_MASK (0x100U)
#define RDC_ADC_INT_STATE_SAMPLE_FALLING_I_STA_SHIFT (8U)
#define RDC_ADC_INT_STATE_SAMPLE_FALLING_I_STA_SET(x) (((uint32_t)(x) << RDC_ADC_INT_STATE_SAMPLE_FALLING_I_STA_SHIFT) & RDC_ADC_INT_STATE_SAMPLE_FALLING_I_STA_MASK)
#define RDC_ADC_INT_STATE_SAMPLE_FALLING_I_STA_GET(x) (((uint32_t)(x) & RDC_ADC_INT_STATE_SAMPLE_FALLING_I_STA_MASK) >> RDC_ADC_INT_STATE_SAMPLE_FALLING_I_STA_SHIFT)

/*
 * SAMPLE_RISING_Q_STA (W1C)
 *
 * q_channel rising edge interrupt status
 */
#define RDC_ADC_INT_STATE_SAMPLE_RISING_Q_STA_MASK (0x80U)
#define RDC_ADC_INT_STATE_SAMPLE_RISING_Q_STA_SHIFT (7U)
#define RDC_ADC_INT_STATE_SAMPLE_RISING_Q_STA_SET(x) (((uint32_t)(x) << RDC_ADC_INT_STATE_SAMPLE_RISING_Q_STA_SHIFT) & RDC_ADC_INT_STATE_SAMPLE_RISING_Q_STA_MASK)
#define RDC_ADC_INT_STATE_SAMPLE_RISING_Q_STA_GET(x) (((uint32_t)(x) & RDC_ADC_INT_STATE_SAMPLE_RISING_Q_STA_MASK) >> RDC_ADC_INT_STATE_SAMPLE_RISING_Q_STA_SHIFT)

/*
 * SAMPLE_FALLING_Q_STA (W1C)
 *
 * q_channel falling edge interrupt status
 */
#define RDC_ADC_INT_STATE_SAMPLE_FALLING_Q_STA_MASK (0x40U)
#define RDC_ADC_INT_STATE_SAMPLE_FALLING_Q_STA_SHIFT (6U)
#define RDC_ADC_INT_STATE_SAMPLE_FALLING_Q_STA_SET(x) (((uint32_t)(x) << RDC_ADC_INT_STATE_SAMPLE_FALLING_Q_STA_SHIFT) & RDC_ADC_INT_STATE_SAMPLE_FALLING_Q_STA_MASK)
#define RDC_ADC_INT_STATE_SAMPLE_FALLING_Q_STA_GET(x) (((uint32_t)(x) & RDC_ADC_INT_STATE_SAMPLE_FALLING_Q_STA_MASK) >> RDC_ADC_INT_STATE_SAMPLE_FALLING_Q_STA_SHIFT)

/*
 * ACC_VLD_I_OVH_STA (W1C)
 *
 * i_channel accumulate overflow interrupt status
 */
#define RDC_ADC_INT_STATE_ACC_VLD_I_OVH_STA_MASK (0x20U)
#define RDC_ADC_INT_STATE_ACC_VLD_I_OVH_STA_SHIFT (5U)
#define RDC_ADC_INT_STATE_ACC_VLD_I_OVH_STA_SET(x) (((uint32_t)(x) << RDC_ADC_INT_STATE_ACC_VLD_I_OVH_STA_SHIFT) & RDC_ADC_INT_STATE_ACC_VLD_I_OVH_STA_MASK)
#define RDC_ADC_INT_STATE_ACC_VLD_I_OVH_STA_GET(x) (((uint32_t)(x) & RDC_ADC_INT_STATE_ACC_VLD_I_OVH_STA_MASK) >> RDC_ADC_INT_STATE_ACC_VLD_I_OVH_STA_SHIFT)

/*
 * ACC_VLD_Q_OVH_STA (W1C)
 *
 * q_channel accumulate overflow interrupt status
 */
#define RDC_ADC_INT_STATE_ACC_VLD_Q_OVH_STA_MASK (0x10U)
#define RDC_ADC_INT_STATE_ACC_VLD_Q_OVH_STA_SHIFT (4U)
#define RDC_ADC_INT_STATE_ACC_VLD_Q_OVH_STA_SET(x) (((uint32_t)(x) << RDC_ADC_INT_STATE_ACC_VLD_Q_OVH_STA_SHIFT) & RDC_ADC_INT_STATE_ACC_VLD_Q_OVH_STA_MASK)
#define RDC_ADC_INT_STATE_ACC_VLD_Q_OVH_STA_GET(x) (((uint32_t)(x) & RDC_ADC_INT_STATE_ACC_VLD_Q_OVH_STA_MASK) >> RDC_ADC_INT_STATE_ACC_VLD_Q_OVH_STA_SHIFT)

/*
 * ACC_VLD_I_OVL_STA (W1C)
 *
 * i_channel accumulate underflow interrupt status
 */
#define RDC_ADC_INT_STATE_ACC_VLD_I_OVL_STA_MASK (0x8U)
#define RDC_ADC_INT_STATE_ACC_VLD_I_OVL_STA_SHIFT (3U)
#define RDC_ADC_INT_STATE_ACC_VLD_I_OVL_STA_SET(x) (((uint32_t)(x) << RDC_ADC_INT_STATE_ACC_VLD_I_OVL_STA_SHIFT) & RDC_ADC_INT_STATE_ACC_VLD_I_OVL_STA_MASK)
#define RDC_ADC_INT_STATE_ACC_VLD_I_OVL_STA_GET(x) (((uint32_t)(x) & RDC_ADC_INT_STATE_ACC_VLD_I_OVL_STA_MASK) >> RDC_ADC_INT_STATE_ACC_VLD_I_OVL_STA_SHIFT)

/*
 * ACC_VLD_Q_OVL_STA (W1C)
 *
 * q_channel accumulate underflow interrupt status
 */
#define RDC_ADC_INT_STATE_ACC_VLD_Q_OVL_STA_MASK (0x4U)
#define RDC_ADC_INT_STATE_ACC_VLD_Q_OVL_STA_SHIFT (2U)
#define RDC_ADC_INT_STATE_ACC_VLD_Q_OVL_STA_SET(x) (((uint32_t)(x) << RDC_ADC_INT_STATE_ACC_VLD_Q_OVL_STA_SHIFT) & RDC_ADC_INT_STATE_ACC_VLD_Q_OVL_STA_MASK)
#define RDC_ADC_INT_STATE_ACC_VLD_Q_OVL_STA_GET(x) (((uint32_t)(x) & RDC_ADC_INT_STATE_ACC_VLD_Q_OVL_STA_MASK) >> RDC_ADC_INT_STATE_ACC_VLD_Q_OVL_STA_SHIFT)

/*
 * ACC_AMP_OVH_STA (W1C)
 *
 * accumulate ample overflow interrupt status
 */
#define RDC_ADC_INT_STATE_ACC_AMP_OVH_STA_MASK (0x2U)
#define RDC_ADC_INT_STATE_ACC_AMP_OVH_STA_SHIFT (1U)
#define RDC_ADC_INT_STATE_ACC_AMP_OVH_STA_SET(x) (((uint32_t)(x) << RDC_ADC_INT_STATE_ACC_AMP_OVH_STA_SHIFT) & RDC_ADC_INT_STATE_ACC_AMP_OVH_STA_MASK)
#define RDC_ADC_INT_STATE_ACC_AMP_OVH_STA_GET(x) (((uint32_t)(x) & RDC_ADC_INT_STATE_ACC_AMP_OVH_STA_MASK) >> RDC_ADC_INT_STATE_ACC_AMP_OVH_STA_SHIFT)

/*
 * ACC_AMP_OVL_STA (W1C)
 *
 * accumulate ample underflow interrupt status
 */
#define RDC_ADC_INT_STATE_ACC_AMP_OVL_STA_MASK (0x1U)
#define RDC_ADC_INT_STATE_ACC_AMP_OVL_STA_SHIFT (0U)
#define RDC_ADC_INT_STATE_ACC_AMP_OVL_STA_SET(x) (((uint32_t)(x) << RDC_ADC_INT_STATE_ACC_AMP_OVL_STA_SHIFT) & RDC_ADC_INT_STATE_ACC_AMP_OVL_STA_MASK)
#define RDC_ADC_INT_STATE_ACC_AMP_OVL_STA_GET(x) (((uint32_t)(x) & RDC_ADC_INT_STATE_ACC_AMP_OVL_STA_MASK) >> RDC_ADC_INT_STATE_ACC_AMP_OVL_STA_SHIFT)




#endif /* HPM_RDC_H */
