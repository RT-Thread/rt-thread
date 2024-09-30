/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_CLC_H
#define HPM_CLC_H

typedef struct {
    struct {
        __RW uint32_t MODE;                    /* 0x0:  mode ctrl */
        __RW uint32_t ADC_EXPECT;              /* 0x4:  adc expect */
        __RW uint32_t ADC_CHAN;                /* 0x8:  adc used channel */
        __RW uint32_t ADC_OFFSET;              /* 0xC:  adc used offset */
        __RW uint32_t EADC_LOWTH;              /* 0x10:  eadc_lowth value used in error adc cofficient selection */
        __RW uint32_t EADC_HIGHTH;             /* 0x14:  eadc_highth value used in error adc cofficient selection */
        __RW uint32_t EADC_MIDLOWTH;           /* 0x18:  eadc_midlowth value used in error adc cofficient selection */
        __RW uint32_t EADC_MIDHIGHTH;          /* 0x1C:  eadc_midhighth value used in error adc cofficient selection */
        __RW uint32_t P2Z2_CLAMP_LO;           /* 0x20:  2p2z output clamp low threshold */
        __RW uint32_t P2Z2_CLAMP_HI;           /* 0x24:  2p2z output clamp high threshold */
        __RW uint32_t P3Z3_CLAMP_LO;           /* 0x28:  3p3z output clamp low threshold */
        __RW uint32_t P3Z3_CLAMP_HI;           /* 0x2C:  3p3z output clamp high threshold */
        __R  uint8_t  RESERVED0[16];           /* 0x30 - 0x3F: Reserved */
        struct {
            __RW uint32_t COEFF_B0;            /* 0x40:  zone  b0 */
            __RW uint32_t COEFF_B1;            /* 0x44:  zone  b1 */
            __RW uint32_t COEFF_B2;            /* 0x48:  zone  b2 */
            __RW uint32_t COEFF_B3;            /* 0x4C:  zone  b3 */
            __RW uint32_t COEFF_A0;            /* 0x50:  zone  a0 */
            __RW uint32_t COEFF_A1;            /* 0x54:  zone  a1 */
            __RW uint32_t COEFF_A2;            /* 0x58:  zone  a2 */
            __RW uint32_t COEFF_KS;            /* 0x5C:  zone  kscaling */
        } COEFF[3];
        __RW uint32_t PWM_PERIOD;              /* 0xA0:  pwm_period */
        __R  uint32_t OUTPUT_VALUE;            /* 0xA4:  output value */
        __R  uint32_t TIMESTAMP;               /* 0xA8:  adc timestamp used */
        __RW uint32_t EADC_CURR;               /* 0xAC:  error adc latest value */
        __RW uint32_t EADC_PRE0;               /* 0xB0:  error adc previous0 value */
        __RW uint32_t EADC_PRE1;               /* 0xB4:  error adc previous1 value */
        __RW uint32_t P2Z2_CURR;               /* 0xB8:  2p2z latest value */
        __RW uint32_t P2Z2_PRE0;               /* 0xBC:  2p2z previous0 value */
        __R  uint8_t  RESERVED1[4];            /* 0xC0 - 0xC3: Reserved */
        __RW uint32_t P3Z3_CURR;               /* 0xC4:  3p3z latest value */
        __R  uint8_t  RESERVED2[4];            /* 0xC8 - 0xCB: Reserved */
        __RW uint32_t P3Z3_FORBID_LO;          /* 0xCC:  3p3z output forbid low threshold */
        __RW uint32_t P3Z3_FORBID_MD;          /* 0xD0:  3p3z output forbid middle threshold */
        __RW uint32_t P3Z3_FORBID_HI;          /* 0xD4:  3p3z output forbid high threshold */
        __R  uint8_t  RESERVED3[8];            /* 0xD8 - 0xDF: Reserved */
        __RW uint32_t ADC_SW;                  /* 0xE0:  adc software inject value */
        __R  uint8_t  RESERVED4[24];           /* 0xE4 - 0xFB: Reserved */
        __W  uint32_t STATUS;                  /* 0xFC:  irq_status */
    } VDVQ_CHAN[2];
    __W  uint32_t DQ_ADC_SW_READY;             /* 0x200: enable d/q chan software inject adc value */
} CLC_Type;


/* Bitfield definition for register of struct array VDVQ_CHAN: MODE */
/*
 * ENABLE_CLC (RW)
 *
 * enable CLC
 */
#define CLC_VDVQ_CHAN_MODE_ENABLE_CLC_MASK (0x80000000UL)
#define CLC_VDVQ_CHAN_MODE_ENABLE_CLC_SHIFT (31U)
#define CLC_VDVQ_CHAN_MODE_ENABLE_CLC_SET(x) (((uint32_t)(x) << CLC_VDVQ_CHAN_MODE_ENABLE_CLC_SHIFT) & CLC_VDVQ_CHAN_MODE_ENABLE_CLC_MASK)
#define CLC_VDVQ_CHAN_MODE_ENABLE_CLC_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_MODE_ENABLE_CLC_MASK) >> CLC_VDVQ_CHAN_MODE_ENABLE_CLC_SHIFT)

/*
 * MASK_MODE (RW)
 *
 * open mode: CLC keep working even if bad irq status ocurred
 */
#define CLC_VDVQ_CHAN_MODE_MASK_MODE_MASK (0x1000000UL)
#define CLC_VDVQ_CHAN_MODE_MASK_MODE_SHIFT (24U)
#define CLC_VDVQ_CHAN_MODE_MASK_MODE_SET(x) (((uint32_t)(x) << CLC_VDVQ_CHAN_MODE_MASK_MODE_SHIFT) & CLC_VDVQ_CHAN_MODE_MASK_MODE_MASK)
#define CLC_VDVQ_CHAN_MODE_MASK_MODE_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_MODE_MASK_MODE_MASK) >> CLC_VDVQ_CHAN_MODE_MASK_MODE_SHIFT)

/*
 * DQ_MODE (RW)
 *
 * dq mode
 */
#define CLC_VDVQ_CHAN_MODE_DQ_MODE_MASK (0x10000UL)
#define CLC_VDVQ_CHAN_MODE_DQ_MODE_SHIFT (16U)
#define CLC_VDVQ_CHAN_MODE_DQ_MODE_SET(x) (((uint32_t)(x) << CLC_VDVQ_CHAN_MODE_DQ_MODE_SHIFT) & CLC_VDVQ_CHAN_MODE_DQ_MODE_MASK)
#define CLC_VDVQ_CHAN_MODE_DQ_MODE_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_MODE_DQ_MODE_MASK) >> CLC_VDVQ_CHAN_MODE_DQ_MODE_SHIFT)

/*
 * ENABLE_IRQ (RW)
 *
 * enable irq:
 * irq_data_in_forbid     , // 10
 * irq_forb_err_boundary  , // 9
 * irq_p3z3_over_lo       , // 8
 * irq_p3z3_over_hi       , // 7
 * irq_p3z3_err_boundary  , // 6
 * irq_z2_over_sf         , // 5
 * irq_z2_over_lo         , // 4
 * irq_z2_over_hi         , // 3
 * irq_z2_err_boundary    , // 2
 * irq_coef_err_boundary  , // 1
 * irq_valid_clc            // 0
 */
#define CLC_VDVQ_CHAN_MODE_ENABLE_IRQ_MASK (0x7FFU)
#define CLC_VDVQ_CHAN_MODE_ENABLE_IRQ_SHIFT (0U)
#define CLC_VDVQ_CHAN_MODE_ENABLE_IRQ_SET(x) (((uint32_t)(x) << CLC_VDVQ_CHAN_MODE_ENABLE_IRQ_SHIFT) & CLC_VDVQ_CHAN_MODE_ENABLE_IRQ_MASK)
#define CLC_VDVQ_CHAN_MODE_ENABLE_IRQ_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_MODE_ENABLE_IRQ_MASK) >> CLC_VDVQ_CHAN_MODE_ENABLE_IRQ_SHIFT)

/* Bitfield definition for register of struct array VDVQ_CHAN: ADC_EXPECT */
/*
 * ADC_EXPECT (RW)
 *
 * adc expect value
 */
#define CLC_VDVQ_CHAN_ADC_EXPECT_ADC_EXPECT_MASK (0xFFFFFFFFUL)
#define CLC_VDVQ_CHAN_ADC_EXPECT_ADC_EXPECT_SHIFT (0U)
#define CLC_VDVQ_CHAN_ADC_EXPECT_ADC_EXPECT_SET(x) (((uint32_t)(x) << CLC_VDVQ_CHAN_ADC_EXPECT_ADC_EXPECT_SHIFT) & CLC_VDVQ_CHAN_ADC_EXPECT_ADC_EXPECT_MASK)
#define CLC_VDVQ_CHAN_ADC_EXPECT_ADC_EXPECT_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_ADC_EXPECT_ADC_EXPECT_MASK) >> CLC_VDVQ_CHAN_ADC_EXPECT_ADC_EXPECT_SHIFT)

/* Bitfield definition for register of struct array VDVQ_CHAN: ADC_CHAN */
/*
 * ADC_CHAN (RW)
 *
 * adc used chan ID
 */
#define CLC_VDVQ_CHAN_ADC_CHAN_ADC_CHAN_MASK (0x1FU)
#define CLC_VDVQ_CHAN_ADC_CHAN_ADC_CHAN_SHIFT (0U)
#define CLC_VDVQ_CHAN_ADC_CHAN_ADC_CHAN_SET(x) (((uint32_t)(x) << CLC_VDVQ_CHAN_ADC_CHAN_ADC_CHAN_SHIFT) & CLC_VDVQ_CHAN_ADC_CHAN_ADC_CHAN_MASK)
#define CLC_VDVQ_CHAN_ADC_CHAN_ADC_CHAN_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_ADC_CHAN_ADC_CHAN_MASK) >> CLC_VDVQ_CHAN_ADC_CHAN_ADC_CHAN_SHIFT)

/* Bitfield definition for register of struct array VDVQ_CHAN: ADC_OFFSET */
/*
 * ADC_OFFSET (RW)
 *
 * adc used offset
 */
#define CLC_VDVQ_CHAN_ADC_OFFSET_ADC_OFFSET_MASK (0xFFFFFFFFUL)
#define CLC_VDVQ_CHAN_ADC_OFFSET_ADC_OFFSET_SHIFT (0U)
#define CLC_VDVQ_CHAN_ADC_OFFSET_ADC_OFFSET_SET(x) (((uint32_t)(x) << CLC_VDVQ_CHAN_ADC_OFFSET_ADC_OFFSET_SHIFT) & CLC_VDVQ_CHAN_ADC_OFFSET_ADC_OFFSET_MASK)
#define CLC_VDVQ_CHAN_ADC_OFFSET_ADC_OFFSET_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_ADC_OFFSET_ADC_OFFSET_MASK) >> CLC_VDVQ_CHAN_ADC_OFFSET_ADC_OFFSET_SHIFT)

/* Bitfield definition for register of struct array VDVQ_CHAN: EADC_LOWTH */
/*
 * EADC_LOWTH (RW)
 *
 * if error adc not bigger than eadc_lowth or not less than eadc_highth, use zone 2 cofficient；if not less than midlowth and not bigger than midhighth, use zone 0 cofficient；otherwire, use zone 1 cofficient
 */
#define CLC_VDVQ_CHAN_EADC_LOWTH_EADC_LOWTH_MASK (0xFFFFFFFFUL)
#define CLC_VDVQ_CHAN_EADC_LOWTH_EADC_LOWTH_SHIFT (0U)
#define CLC_VDVQ_CHAN_EADC_LOWTH_EADC_LOWTH_SET(x) (((uint32_t)(x) << CLC_VDVQ_CHAN_EADC_LOWTH_EADC_LOWTH_SHIFT) & CLC_VDVQ_CHAN_EADC_LOWTH_EADC_LOWTH_MASK)
#define CLC_VDVQ_CHAN_EADC_LOWTH_EADC_LOWTH_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_EADC_LOWTH_EADC_LOWTH_MASK) >> CLC_VDVQ_CHAN_EADC_LOWTH_EADC_LOWTH_SHIFT)

/* Bitfield definition for register of struct array VDVQ_CHAN: EADC_HIGHTH */
/*
 * EADC_HIGHTH (RW)
 *
 * if error adc not bigger than eadc_lowth or not less than eadc_highth, use zone 2 cofficient；if not less than midlowth and not bigger than midhighth, use zone 0 cofficient；otherwire, use zone 1 cofficient
 */
#define CLC_VDVQ_CHAN_EADC_HIGHTH_EADC_HIGHTH_MASK (0xFFFFFFFFUL)
#define CLC_VDVQ_CHAN_EADC_HIGHTH_EADC_HIGHTH_SHIFT (0U)
#define CLC_VDVQ_CHAN_EADC_HIGHTH_EADC_HIGHTH_SET(x) (((uint32_t)(x) << CLC_VDVQ_CHAN_EADC_HIGHTH_EADC_HIGHTH_SHIFT) & CLC_VDVQ_CHAN_EADC_HIGHTH_EADC_HIGHTH_MASK)
#define CLC_VDVQ_CHAN_EADC_HIGHTH_EADC_HIGHTH_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_EADC_HIGHTH_EADC_HIGHTH_MASK) >> CLC_VDVQ_CHAN_EADC_HIGHTH_EADC_HIGHTH_SHIFT)

/* Bitfield definition for register of struct array VDVQ_CHAN: EADC_MIDLOWTH */
/*
 * EADC_MIDLOWTH (RW)
 *
 * if error adc not bigger than eadc_lowth or not less than eadc_highth, use zone 2 cofficient；if not less than midlowth and not bigger than midhighth, use zone 0 cofficient；otherwire, use zone 1 cofficient
 */
#define CLC_VDVQ_CHAN_EADC_MIDLOWTH_EADC_MIDLOWTH_MASK (0xFFFFFFFFUL)
#define CLC_VDVQ_CHAN_EADC_MIDLOWTH_EADC_MIDLOWTH_SHIFT (0U)
#define CLC_VDVQ_CHAN_EADC_MIDLOWTH_EADC_MIDLOWTH_SET(x) (((uint32_t)(x) << CLC_VDVQ_CHAN_EADC_MIDLOWTH_EADC_MIDLOWTH_SHIFT) & CLC_VDVQ_CHAN_EADC_MIDLOWTH_EADC_MIDLOWTH_MASK)
#define CLC_VDVQ_CHAN_EADC_MIDLOWTH_EADC_MIDLOWTH_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_EADC_MIDLOWTH_EADC_MIDLOWTH_MASK) >> CLC_VDVQ_CHAN_EADC_MIDLOWTH_EADC_MIDLOWTH_SHIFT)

/* Bitfield definition for register of struct array VDVQ_CHAN: EADC_MIDHIGHTH */
/*
 * EADC_MIDHIGHTH (RW)
 *
 * if error adc not bigger than eadc_lowth or not less than eadc_highth, use zone 2 cofficient；if not less than midlowth and not bigger than midhighth, use zone 0 cofficient；otherwire, use zone 1 cofficient
 */
#define CLC_VDVQ_CHAN_EADC_MIDHIGHTH_EADC_MIDHIGHTH_MASK (0xFFFFFFFFUL)
#define CLC_VDVQ_CHAN_EADC_MIDHIGHTH_EADC_MIDHIGHTH_SHIFT (0U)
#define CLC_VDVQ_CHAN_EADC_MIDHIGHTH_EADC_MIDHIGHTH_SET(x) (((uint32_t)(x) << CLC_VDVQ_CHAN_EADC_MIDHIGHTH_EADC_MIDHIGHTH_SHIFT) & CLC_VDVQ_CHAN_EADC_MIDHIGHTH_EADC_MIDHIGHTH_MASK)
#define CLC_VDVQ_CHAN_EADC_MIDHIGHTH_EADC_MIDHIGHTH_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_EADC_MIDHIGHTH_EADC_MIDHIGHTH_MASK) >> CLC_VDVQ_CHAN_EADC_MIDHIGHTH_EADC_MIDHIGHTH_SHIFT)

/* Bitfield definition for register of struct array VDVQ_CHAN: P2Z2_CLAMP_LO */
/*
 * 2P2Z_CLAMP_LO (RW)
 *
 * 2p2z output clamp low threshold
 */
#define CLC_VDVQ_CHAN_P2Z2_CLAMP_LO_2P2Z_CLAMP_LO_MASK (0xFFFFFFFFUL)
#define CLC_VDVQ_CHAN_P2Z2_CLAMP_LO_2P2Z_CLAMP_LO_SHIFT (0U)
#define CLC_VDVQ_CHAN_P2Z2_CLAMP_LO_2P2Z_CLAMP_LO_SET(x) (((uint32_t)(x) << CLC_VDVQ_CHAN_P2Z2_CLAMP_LO_2P2Z_CLAMP_LO_SHIFT) & CLC_VDVQ_CHAN_P2Z2_CLAMP_LO_2P2Z_CLAMP_LO_MASK)
#define CLC_VDVQ_CHAN_P2Z2_CLAMP_LO_2P2Z_CLAMP_LO_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_P2Z2_CLAMP_LO_2P2Z_CLAMP_LO_MASK) >> CLC_VDVQ_CHAN_P2Z2_CLAMP_LO_2P2Z_CLAMP_LO_SHIFT)

/* Bitfield definition for register of struct array VDVQ_CHAN: P2Z2_CLAMP_HI */
/*
 * 2P2Z_CLAMP_HI (RW)
 *
 * 2p2z output clamp high threshold
 */
#define CLC_VDVQ_CHAN_P2Z2_CLAMP_HI_2P2Z_CLAMP_HI_MASK (0xFFFFFFFFUL)
#define CLC_VDVQ_CHAN_P2Z2_CLAMP_HI_2P2Z_CLAMP_HI_SHIFT (0U)
#define CLC_VDVQ_CHAN_P2Z2_CLAMP_HI_2P2Z_CLAMP_HI_SET(x) (((uint32_t)(x) << CLC_VDVQ_CHAN_P2Z2_CLAMP_HI_2P2Z_CLAMP_HI_SHIFT) & CLC_VDVQ_CHAN_P2Z2_CLAMP_HI_2P2Z_CLAMP_HI_MASK)
#define CLC_VDVQ_CHAN_P2Z2_CLAMP_HI_2P2Z_CLAMP_HI_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_P2Z2_CLAMP_HI_2P2Z_CLAMP_HI_MASK) >> CLC_VDVQ_CHAN_P2Z2_CLAMP_HI_2P2Z_CLAMP_HI_SHIFT)

/* Bitfield definition for register of struct array VDVQ_CHAN: P3Z3_CLAMP_LO */
/*
 * 3P3Z_CLAMP_LO (RW)
 *
 * 3p3z output clamp low threshold
 */
#define CLC_VDVQ_CHAN_P3Z3_CLAMP_LO_3P3Z_CLAMP_LO_MASK (0xFFFFFFFFUL)
#define CLC_VDVQ_CHAN_P3Z3_CLAMP_LO_3P3Z_CLAMP_LO_SHIFT (0U)
#define CLC_VDVQ_CHAN_P3Z3_CLAMP_LO_3P3Z_CLAMP_LO_SET(x) (((uint32_t)(x) << CLC_VDVQ_CHAN_P3Z3_CLAMP_LO_3P3Z_CLAMP_LO_SHIFT) & CLC_VDVQ_CHAN_P3Z3_CLAMP_LO_3P3Z_CLAMP_LO_MASK)
#define CLC_VDVQ_CHAN_P3Z3_CLAMP_LO_3P3Z_CLAMP_LO_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_P3Z3_CLAMP_LO_3P3Z_CLAMP_LO_MASK) >> CLC_VDVQ_CHAN_P3Z3_CLAMP_LO_3P3Z_CLAMP_LO_SHIFT)

/* Bitfield definition for register of struct array VDVQ_CHAN: P3Z3_CLAMP_HI */
/*
 * 3P3Z_CLAMP_HI (RW)
 *
 * 3p3z output clamp high threshold
 */
#define CLC_VDVQ_CHAN_P3Z3_CLAMP_HI_3P3Z_CLAMP_HI_MASK (0xFFFFFFFFUL)
#define CLC_VDVQ_CHAN_P3Z3_CLAMP_HI_3P3Z_CLAMP_HI_SHIFT (0U)
#define CLC_VDVQ_CHAN_P3Z3_CLAMP_HI_3P3Z_CLAMP_HI_SET(x) (((uint32_t)(x) << CLC_VDVQ_CHAN_P3Z3_CLAMP_HI_3P3Z_CLAMP_HI_SHIFT) & CLC_VDVQ_CHAN_P3Z3_CLAMP_HI_3P3Z_CLAMP_HI_MASK)
#define CLC_VDVQ_CHAN_P3Z3_CLAMP_HI_3P3Z_CLAMP_HI_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_P3Z3_CLAMP_HI_3P3Z_CLAMP_HI_MASK) >> CLC_VDVQ_CHAN_P3Z3_CLAMP_HI_3P3Z_CLAMP_HI_SHIFT)

/* Bitfield definition for register of struct array VDVQ_CHAN: COEFF_B0 */
/*
 * COEFF_B0 (RW)
 *
 * coefficient b0
 */
#define CLC_VDVQ_CHAN_COEFF_COEFF_B0_COEFF_B0_MASK (0xFFFFFFFFUL)
#define CLC_VDVQ_CHAN_COEFF_COEFF_B0_COEFF_B0_SHIFT (0U)
#define CLC_VDVQ_CHAN_COEFF_COEFF_B0_COEFF_B0_SET(x) (((uint32_t)(x) << CLC_VDVQ_CHAN_COEFF_COEFF_B0_COEFF_B0_SHIFT) & CLC_VDVQ_CHAN_COEFF_COEFF_B0_COEFF_B0_MASK)
#define CLC_VDVQ_CHAN_COEFF_COEFF_B0_COEFF_B0_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_COEFF_COEFF_B0_COEFF_B0_MASK) >> CLC_VDVQ_CHAN_COEFF_COEFF_B0_COEFF_B0_SHIFT)

/* Bitfield definition for register of struct array VDVQ_CHAN: COEFF_B1 */
/*
 * COEFF_B1 (RW)
 *
 * coefficient b1
 */
#define CLC_VDVQ_CHAN_COEFF_COEFF_B1_COEFF_B1_MASK (0xFFFFFFFFUL)
#define CLC_VDVQ_CHAN_COEFF_COEFF_B1_COEFF_B1_SHIFT (0U)
#define CLC_VDVQ_CHAN_COEFF_COEFF_B1_COEFF_B1_SET(x) (((uint32_t)(x) << CLC_VDVQ_CHAN_COEFF_COEFF_B1_COEFF_B1_SHIFT) & CLC_VDVQ_CHAN_COEFF_COEFF_B1_COEFF_B1_MASK)
#define CLC_VDVQ_CHAN_COEFF_COEFF_B1_COEFF_B1_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_COEFF_COEFF_B1_COEFF_B1_MASK) >> CLC_VDVQ_CHAN_COEFF_COEFF_B1_COEFF_B1_SHIFT)

/* Bitfield definition for register of struct array VDVQ_CHAN: COEFF_B2 */
/*
 * COEFF_B2 (RW)
 *
 * coefficient b2
 */
#define CLC_VDVQ_CHAN_COEFF_COEFF_B2_COEFF_B2_MASK (0xFFFFFFFFUL)
#define CLC_VDVQ_CHAN_COEFF_COEFF_B2_COEFF_B2_SHIFT (0U)
#define CLC_VDVQ_CHAN_COEFF_COEFF_B2_COEFF_B2_SET(x) (((uint32_t)(x) << CLC_VDVQ_CHAN_COEFF_COEFF_B2_COEFF_B2_SHIFT) & CLC_VDVQ_CHAN_COEFF_COEFF_B2_COEFF_B2_MASK)
#define CLC_VDVQ_CHAN_COEFF_COEFF_B2_COEFF_B2_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_COEFF_COEFF_B2_COEFF_B2_MASK) >> CLC_VDVQ_CHAN_COEFF_COEFF_B2_COEFF_B2_SHIFT)

/* Bitfield definition for register of struct array VDVQ_CHAN: COEFF_B3 */
/*
 * COEFF_B3 (RW)
 *
 * coefficient b3
 */
#define CLC_VDVQ_CHAN_COEFF_COEFF_B3_COEFF_B3_MASK (0xFFFFFFFFUL)
#define CLC_VDVQ_CHAN_COEFF_COEFF_B3_COEFF_B3_SHIFT (0U)
#define CLC_VDVQ_CHAN_COEFF_COEFF_B3_COEFF_B3_SET(x) (((uint32_t)(x) << CLC_VDVQ_CHAN_COEFF_COEFF_B3_COEFF_B3_SHIFT) & CLC_VDVQ_CHAN_COEFF_COEFF_B3_COEFF_B3_MASK)
#define CLC_VDVQ_CHAN_COEFF_COEFF_B3_COEFF_B3_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_COEFF_COEFF_B3_COEFF_B3_MASK) >> CLC_VDVQ_CHAN_COEFF_COEFF_B3_COEFF_B3_SHIFT)

/* Bitfield definition for register of struct array VDVQ_CHAN: COEFF_A0 */
/*
 * COEFF_A0 (RW)
 *
 * coefficient a0
 */
#define CLC_VDVQ_CHAN_COEFF_COEFF_A0_COEFF_A0_MASK (0xFFFFFFFFUL)
#define CLC_VDVQ_CHAN_COEFF_COEFF_A0_COEFF_A0_SHIFT (0U)
#define CLC_VDVQ_CHAN_COEFF_COEFF_A0_COEFF_A0_SET(x) (((uint32_t)(x) << CLC_VDVQ_CHAN_COEFF_COEFF_A0_COEFF_A0_SHIFT) & CLC_VDVQ_CHAN_COEFF_COEFF_A0_COEFF_A0_MASK)
#define CLC_VDVQ_CHAN_COEFF_COEFF_A0_COEFF_A0_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_COEFF_COEFF_A0_COEFF_A0_MASK) >> CLC_VDVQ_CHAN_COEFF_COEFF_A0_COEFF_A0_SHIFT)

/* Bitfield definition for register of struct array VDVQ_CHAN: COEFF_A1 */
/*
 * COEFF_A1 (RW)
 *
 * coefficient a1
 */
#define CLC_VDVQ_CHAN_COEFF_COEFF_A1_COEFF_A1_MASK (0xFFFFFFFFUL)
#define CLC_VDVQ_CHAN_COEFF_COEFF_A1_COEFF_A1_SHIFT (0U)
#define CLC_VDVQ_CHAN_COEFF_COEFF_A1_COEFF_A1_SET(x) (((uint32_t)(x) << CLC_VDVQ_CHAN_COEFF_COEFF_A1_COEFF_A1_SHIFT) & CLC_VDVQ_CHAN_COEFF_COEFF_A1_COEFF_A1_MASK)
#define CLC_VDVQ_CHAN_COEFF_COEFF_A1_COEFF_A1_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_COEFF_COEFF_A1_COEFF_A1_MASK) >> CLC_VDVQ_CHAN_COEFF_COEFF_A1_COEFF_A1_SHIFT)

/* Bitfield definition for register of struct array VDVQ_CHAN: COEFF_A2 */
/*
 * COEFF_A2 (RW)
 *
 * coefficient a2
 */
#define CLC_VDVQ_CHAN_COEFF_COEFF_A2_COEFF_A2_MASK (0xFFFFFFFFUL)
#define CLC_VDVQ_CHAN_COEFF_COEFF_A2_COEFF_A2_SHIFT (0U)
#define CLC_VDVQ_CHAN_COEFF_COEFF_A2_COEFF_A2_SET(x) (((uint32_t)(x) << CLC_VDVQ_CHAN_COEFF_COEFF_A2_COEFF_A2_SHIFT) & CLC_VDVQ_CHAN_COEFF_COEFF_A2_COEFF_A2_MASK)
#define CLC_VDVQ_CHAN_COEFF_COEFF_A2_COEFF_A2_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_COEFF_COEFF_A2_COEFF_A2_MASK) >> CLC_VDVQ_CHAN_COEFF_COEFF_A2_COEFF_A2_SHIFT)

/* Bitfield definition for register of struct array VDVQ_CHAN: COEFF_KS */
/*
 * COEFF_KSCALING (RW)
 *
 * coefficient kscaling
 */
#define CLC_VDVQ_CHAN_COEFF_COEFF_KS_COEFF_KSCALING_MASK (0x1FU)
#define CLC_VDVQ_CHAN_COEFF_COEFF_KS_COEFF_KSCALING_SHIFT (0U)
#define CLC_VDVQ_CHAN_COEFF_COEFF_KS_COEFF_KSCALING_SET(x) (((uint32_t)(x) << CLC_VDVQ_CHAN_COEFF_COEFF_KS_COEFF_KSCALING_SHIFT) & CLC_VDVQ_CHAN_COEFF_COEFF_KS_COEFF_KSCALING_MASK)
#define CLC_VDVQ_CHAN_COEFF_COEFF_KS_COEFF_KSCALING_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_COEFF_COEFF_KS_COEFF_KSCALING_MASK) >> CLC_VDVQ_CHAN_COEFF_COEFF_KS_COEFF_KSCALING_SHIFT)

/* Bitfield definition for register of struct array VDVQ_CHAN: PWM_PERIOD */
/*
 * PWM_PERIOD (RW)
 *
 * pwm_period
 */
#define CLC_VDVQ_CHAN_PWM_PERIOD_PWM_PERIOD_MASK (0xFFFFFFFFUL)
#define CLC_VDVQ_CHAN_PWM_PERIOD_PWM_PERIOD_SHIFT (0U)
#define CLC_VDVQ_CHAN_PWM_PERIOD_PWM_PERIOD_SET(x) (((uint32_t)(x) << CLC_VDVQ_CHAN_PWM_PERIOD_PWM_PERIOD_SHIFT) & CLC_VDVQ_CHAN_PWM_PERIOD_PWM_PERIOD_MASK)
#define CLC_VDVQ_CHAN_PWM_PERIOD_PWM_PERIOD_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_PWM_PERIOD_PWM_PERIOD_MASK) >> CLC_VDVQ_CHAN_PWM_PERIOD_PWM_PERIOD_SHIFT)

/* Bitfield definition for register of struct array VDVQ_CHAN: OUTPUT_VALUE */
/*
 * OUTPUT_VALUE (RO)
 *
 * output_value
 */
#define CLC_VDVQ_CHAN_OUTPUT_VALUE_OUTPUT_VALUE_MASK (0xFFFFFFFFUL)
#define CLC_VDVQ_CHAN_OUTPUT_VALUE_OUTPUT_VALUE_SHIFT (0U)
#define CLC_VDVQ_CHAN_OUTPUT_VALUE_OUTPUT_VALUE_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_OUTPUT_VALUE_OUTPUT_VALUE_MASK) >> CLC_VDVQ_CHAN_OUTPUT_VALUE_OUTPUT_VALUE_SHIFT)

/* Bitfield definition for register of struct array VDVQ_CHAN: TIMESTAMP */
/*
 * TIMESTAMP (RO)
 *
 * timestamp
 */
#define CLC_VDVQ_CHAN_TIMESTAMP_TIMESTAMP_MASK (0xFFFFFFFFUL)
#define CLC_VDVQ_CHAN_TIMESTAMP_TIMESTAMP_SHIFT (0U)
#define CLC_VDVQ_CHAN_TIMESTAMP_TIMESTAMP_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_TIMESTAMP_TIMESTAMP_MASK) >> CLC_VDVQ_CHAN_TIMESTAMP_TIMESTAMP_SHIFT)

/* Bitfield definition for register of struct array VDVQ_CHAN: EADC_CURR */
/*
 * EADC_CURR (RW)
 *
 * error adc latest value
 */
#define CLC_VDVQ_CHAN_EADC_CURR_EADC_CURR_MASK (0xFFFFFFFFUL)
#define CLC_VDVQ_CHAN_EADC_CURR_EADC_CURR_SHIFT (0U)
#define CLC_VDVQ_CHAN_EADC_CURR_EADC_CURR_SET(x) (((uint32_t)(x) << CLC_VDVQ_CHAN_EADC_CURR_EADC_CURR_SHIFT) & CLC_VDVQ_CHAN_EADC_CURR_EADC_CURR_MASK)
#define CLC_VDVQ_CHAN_EADC_CURR_EADC_CURR_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_EADC_CURR_EADC_CURR_MASK) >> CLC_VDVQ_CHAN_EADC_CURR_EADC_CURR_SHIFT)

/* Bitfield definition for register of struct array VDVQ_CHAN: EADC_PRE0 */
/*
 * EADC_PRE0 (RW)
 *
 * error adc previous 0 value
 */
#define CLC_VDVQ_CHAN_EADC_PRE0_EADC_PRE0_MASK (0xFFFFFFFFUL)
#define CLC_VDVQ_CHAN_EADC_PRE0_EADC_PRE0_SHIFT (0U)
#define CLC_VDVQ_CHAN_EADC_PRE0_EADC_PRE0_SET(x) (((uint32_t)(x) << CLC_VDVQ_CHAN_EADC_PRE0_EADC_PRE0_SHIFT) & CLC_VDVQ_CHAN_EADC_PRE0_EADC_PRE0_MASK)
#define CLC_VDVQ_CHAN_EADC_PRE0_EADC_PRE0_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_EADC_PRE0_EADC_PRE0_MASK) >> CLC_VDVQ_CHAN_EADC_PRE0_EADC_PRE0_SHIFT)

/* Bitfield definition for register of struct array VDVQ_CHAN: EADC_PRE1 */
/*
 * EADC_PRE1 (RW)
 *
 * error adc previous 1 value
 */
#define CLC_VDVQ_CHAN_EADC_PRE1_EADC_PRE1_MASK (0xFFFFFFFFUL)
#define CLC_VDVQ_CHAN_EADC_PRE1_EADC_PRE1_SHIFT (0U)
#define CLC_VDVQ_CHAN_EADC_PRE1_EADC_PRE1_SET(x) (((uint32_t)(x) << CLC_VDVQ_CHAN_EADC_PRE1_EADC_PRE1_SHIFT) & CLC_VDVQ_CHAN_EADC_PRE1_EADC_PRE1_MASK)
#define CLC_VDVQ_CHAN_EADC_PRE1_EADC_PRE1_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_EADC_PRE1_EADC_PRE1_MASK) >> CLC_VDVQ_CHAN_EADC_PRE1_EADC_PRE1_SHIFT)

/* Bitfield definition for register of struct array VDVQ_CHAN: P2Z2_CURR */
/*
 * 2P2Z_CURR (RW)
 *
 * 2p2z latest value
 */
#define CLC_VDVQ_CHAN_P2Z2_CURR_2P2Z_CURR_MASK (0xFFFFFFFFUL)
#define CLC_VDVQ_CHAN_P2Z2_CURR_2P2Z_CURR_SHIFT (0U)
#define CLC_VDVQ_CHAN_P2Z2_CURR_2P2Z_CURR_SET(x) (((uint32_t)(x) << CLC_VDVQ_CHAN_P2Z2_CURR_2P2Z_CURR_SHIFT) & CLC_VDVQ_CHAN_P2Z2_CURR_2P2Z_CURR_MASK)
#define CLC_VDVQ_CHAN_P2Z2_CURR_2P2Z_CURR_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_P2Z2_CURR_2P2Z_CURR_MASK) >> CLC_VDVQ_CHAN_P2Z2_CURR_2P2Z_CURR_SHIFT)

/* Bitfield definition for register of struct array VDVQ_CHAN: P2Z2_PRE0 */
/*
 * 2P2Z_PRE0 (RW)
 *
 * 2p2z previous 0 value
 */
#define CLC_VDVQ_CHAN_P2Z2_PRE0_2P2Z_PRE0_MASK (0xFFFFFFFFUL)
#define CLC_VDVQ_CHAN_P2Z2_PRE0_2P2Z_PRE0_SHIFT (0U)
#define CLC_VDVQ_CHAN_P2Z2_PRE0_2P2Z_PRE0_SET(x) (((uint32_t)(x) << CLC_VDVQ_CHAN_P2Z2_PRE0_2P2Z_PRE0_SHIFT) & CLC_VDVQ_CHAN_P2Z2_PRE0_2P2Z_PRE0_MASK)
#define CLC_VDVQ_CHAN_P2Z2_PRE0_2P2Z_PRE0_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_P2Z2_PRE0_2P2Z_PRE0_MASK) >> CLC_VDVQ_CHAN_P2Z2_PRE0_2P2Z_PRE0_SHIFT)

/* Bitfield definition for register of struct array VDVQ_CHAN: P3Z3_CURR */
/*
 * 3P3Z_CURR (RW)
 *
 * 3p3z latest value
 */
#define CLC_VDVQ_CHAN_P3Z3_CURR_3P3Z_CURR_MASK (0xFFFFFFFFUL)
#define CLC_VDVQ_CHAN_P3Z3_CURR_3P3Z_CURR_SHIFT (0U)
#define CLC_VDVQ_CHAN_P3Z3_CURR_3P3Z_CURR_SET(x) (((uint32_t)(x) << CLC_VDVQ_CHAN_P3Z3_CURR_3P3Z_CURR_SHIFT) & CLC_VDVQ_CHAN_P3Z3_CURR_3P3Z_CURR_MASK)
#define CLC_VDVQ_CHAN_P3Z3_CURR_3P3Z_CURR_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_P3Z3_CURR_3P3Z_CURR_MASK) >> CLC_VDVQ_CHAN_P3Z3_CURR_3P3Z_CURR_SHIFT)

/* Bitfield definition for register of struct array VDVQ_CHAN: P3Z3_FORBID_LO */
/*
 * 3P3Z_FORBID_LO (RW)
 *
 * 3p3z output forbid low threshold
 */
#define CLC_VDVQ_CHAN_P3Z3_FORBID_LO_3P3Z_FORBID_LO_MASK (0xFFFFFFFFUL)
#define CLC_VDVQ_CHAN_P3Z3_FORBID_LO_3P3Z_FORBID_LO_SHIFT (0U)
#define CLC_VDVQ_CHAN_P3Z3_FORBID_LO_3P3Z_FORBID_LO_SET(x) (((uint32_t)(x) << CLC_VDVQ_CHAN_P3Z3_FORBID_LO_3P3Z_FORBID_LO_SHIFT) & CLC_VDVQ_CHAN_P3Z3_FORBID_LO_3P3Z_FORBID_LO_MASK)
#define CLC_VDVQ_CHAN_P3Z3_FORBID_LO_3P3Z_FORBID_LO_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_P3Z3_FORBID_LO_3P3Z_FORBID_LO_MASK) >> CLC_VDVQ_CHAN_P3Z3_FORBID_LO_3P3Z_FORBID_LO_SHIFT)

/* Bitfield definition for register of struct array VDVQ_CHAN: P3Z3_FORBID_MD */
/*
 * 3P3Z_FORBID_MD (RW)
 *
 * 3p3z output forbid middle threshold
 */
#define CLC_VDVQ_CHAN_P3Z3_FORBID_MD_3P3Z_FORBID_MD_MASK (0xFFFFFFFFUL)
#define CLC_VDVQ_CHAN_P3Z3_FORBID_MD_3P3Z_FORBID_MD_SHIFT (0U)
#define CLC_VDVQ_CHAN_P3Z3_FORBID_MD_3P3Z_FORBID_MD_SET(x) (((uint32_t)(x) << CLC_VDVQ_CHAN_P3Z3_FORBID_MD_3P3Z_FORBID_MD_SHIFT) & CLC_VDVQ_CHAN_P3Z3_FORBID_MD_3P3Z_FORBID_MD_MASK)
#define CLC_VDVQ_CHAN_P3Z3_FORBID_MD_3P3Z_FORBID_MD_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_P3Z3_FORBID_MD_3P3Z_FORBID_MD_MASK) >> CLC_VDVQ_CHAN_P3Z3_FORBID_MD_3P3Z_FORBID_MD_SHIFT)

/* Bitfield definition for register of struct array VDVQ_CHAN: P3Z3_FORBID_HI */
/*
 * 3P3Z_FORBID_HI (RW)
 *
 * 3p3z output forbid high threshold
 */
#define CLC_VDVQ_CHAN_P3Z3_FORBID_HI_3P3Z_FORBID_HI_MASK (0xFFFFFFFFUL)
#define CLC_VDVQ_CHAN_P3Z3_FORBID_HI_3P3Z_FORBID_HI_SHIFT (0U)
#define CLC_VDVQ_CHAN_P3Z3_FORBID_HI_3P3Z_FORBID_HI_SET(x) (((uint32_t)(x) << CLC_VDVQ_CHAN_P3Z3_FORBID_HI_3P3Z_FORBID_HI_SHIFT) & CLC_VDVQ_CHAN_P3Z3_FORBID_HI_3P3Z_FORBID_HI_MASK)
#define CLC_VDVQ_CHAN_P3Z3_FORBID_HI_3P3Z_FORBID_HI_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_P3Z3_FORBID_HI_3P3Z_FORBID_HI_MASK) >> CLC_VDVQ_CHAN_P3Z3_FORBID_HI_3P3Z_FORBID_HI_SHIFT)

/* Bitfield definition for register of struct array VDVQ_CHAN: ADC_SW */
/*
 * ADC_SW (RW)
 *
 * adc software inject value
 */
#define CLC_VDVQ_CHAN_ADC_SW_ADC_SW_MASK (0xFFFFFFFFUL)
#define CLC_VDVQ_CHAN_ADC_SW_ADC_SW_SHIFT (0U)
#define CLC_VDVQ_CHAN_ADC_SW_ADC_SW_SET(x) (((uint32_t)(x) << CLC_VDVQ_CHAN_ADC_SW_ADC_SW_SHIFT) & CLC_VDVQ_CHAN_ADC_SW_ADC_SW_MASK)
#define CLC_VDVQ_CHAN_ADC_SW_ADC_SW_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_ADC_SW_ADC_SW_MASK) >> CLC_VDVQ_CHAN_ADC_SW_ADC_SW_SHIFT)

/* Bitfield definition for register of struct array VDVQ_CHAN: STATUS */
/*
 * STATUS (W1C)
 *
 * status, write 1 to clear it. :
 * irq_data_in_forbid     , // 10
 * irq_forb_err_boundary  , // 9
 * irq_p3z3_over_lo       , // 8
 * irq_p3z3_over_hi       , // 7
 * irq_p3z3_err_boundary  , // 6
 * irq_z2_over_sf         , // 5
 * irq_z2_over_lo         , // 4
 * irq_z2_over_hi         , // 3
 * irq_z2_err_boundary    , // 2
 * irq_coef_err_boundary  , // 1
 * irq_valid_clc            // 0
 */
#define CLC_VDVQ_CHAN_STATUS_STATUS_MASK (0x7FFU)
#define CLC_VDVQ_CHAN_STATUS_STATUS_SHIFT (0U)
#define CLC_VDVQ_CHAN_STATUS_STATUS_SET(x) (((uint32_t)(x) << CLC_VDVQ_CHAN_STATUS_STATUS_SHIFT) & CLC_VDVQ_CHAN_STATUS_STATUS_MASK)
#define CLC_VDVQ_CHAN_STATUS_STATUS_GET(x) (((uint32_t)(x) & CLC_VDVQ_CHAN_STATUS_STATUS_MASK) >> CLC_VDVQ_CHAN_STATUS_STATUS_SHIFT)

/* Bitfield definition for register: DQ_ADC_SW_READY */
/*
 * DQ_ADC_SW_READY (W1C)
 *
 * enable d/q chan software inject adc value
 */
#define CLC_DQ_ADC_SW_READY_DQ_ADC_SW_READY_MASK (0x1U)
#define CLC_DQ_ADC_SW_READY_DQ_ADC_SW_READY_SHIFT (0U)
#define CLC_DQ_ADC_SW_READY_DQ_ADC_SW_READY_SET(x) (((uint32_t)(x) << CLC_DQ_ADC_SW_READY_DQ_ADC_SW_READY_SHIFT) & CLC_DQ_ADC_SW_READY_DQ_ADC_SW_READY_MASK)
#define CLC_DQ_ADC_SW_READY_DQ_ADC_SW_READY_GET(x) (((uint32_t)(x) & CLC_DQ_ADC_SW_READY_DQ_ADC_SW_READY_MASK) >> CLC_DQ_ADC_SW_READY_DQ_ADC_SW_READY_SHIFT)



/* COEFF register group index macro definition */
#define CLC_COEFF_0 (0UL)
#define CLC_COEFF_1 (1UL)
#define CLC_COEFF_2 (2UL)

/* VDVQ_CHAN register group index macro definition */
#define CLC_VDVQ_CHAN_VD (0UL)
#define CLC_VDVQ_CHAN_VQ (1UL)


#endif /* HPM_CLC_H */
