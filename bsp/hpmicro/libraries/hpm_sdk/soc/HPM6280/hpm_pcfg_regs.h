/*
 * Copyright (c) 2021-2024 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_PCFG_H
#define HPM_PCFG_H

typedef struct {
    __RW uint32_t BANDGAP;                     /* 0x0: BANGGAP control */
    __RW uint32_t LDO1P1;                      /* 0x4: 1V LDO config */
    __RW uint32_t LDO2P5;                      /* 0x8: 2.5V LDO config */
    __R  uint8_t  RESERVED0[4];                /* 0xC - 0xF: Reserved */
    __RW uint32_t DCDC_MODE;                   /* 0x10: DCDC mode select */
    __RW uint32_t DCDC_LPMODE;                 /* 0x14: DCDC low power mode */
    __RW uint32_t DCDC_PROT;                   /* 0x18: DCDC protection */
    __RW uint32_t DCDC_CURRENT;                /* 0x1C: DCDC current estimation */
    __RW uint32_t DCDC_ADVMODE;                /* 0x20: DCDC advance setting */
    __RW uint32_t DCDC_ADVPARAM;               /* 0x24: DCDC advance parameter */
    __RW uint32_t DCDC_MISC;                   /* 0x28: DCDC misc parameter */
    __RW uint32_t DCDC_DEBUG;                  /* 0x2C: DCDC Debug */
    __RW uint32_t DCDC_START_TIME;             /* 0x30: DCDC ramp time */
    __RW uint32_t DCDC_RESUME_TIME;            /* 0x34: DCDC resume time */
    __R  uint8_t  RESERVED1[8];                /* 0x38 - 0x3F: Reserved */
    __RW uint32_t POWER_TRAP;                  /* 0x40: SOC power trap */
    __RW uint32_t WAKE_CAUSE;                  /* 0x44: Wake up source */
    __RW uint32_t WAKE_MASK;                   /* 0x48: Wake up mask */
    __RW uint32_t SCG_CTRL;                    /* 0x4C: Clock gate control in PMIC */
    __RW uint32_t DEBUG_STOP;                  /* 0x50: Debug stop config */
    __R  uint8_t  RESERVED2[12];               /* 0x54 - 0x5F: Reserved */
    __RW uint32_t RC24M;                       /* 0x60: RC 24M config */
    __RW uint32_t RC24M_TRACK;                 /* 0x64: RC 24M track mode */
    __RW uint32_t TRACK_TARGET;                /* 0x68: RC 24M track target */
    __R  uint32_t STATUS;                      /* 0x6C: RC 24M track status */
} PCFG_Type;


/* Bitfield definition for register: BANDGAP */
/*
 * VBG_TRIMMED (RW)
 *
 * Bandgap trim happened, this bit set by hardware after trim value loaded, and stop load, write 0 will clear this bit and reload trim value
 * 0: bandgap is not trimmed
 * 1: bandgap is trimmed
 */
#define PCFG_BANDGAP_VBG_TRIMMED_MASK (0x80000000UL)
#define PCFG_BANDGAP_VBG_TRIMMED_SHIFT (31U)
#define PCFG_BANDGAP_VBG_TRIMMED_SET(x) (((uint32_t)(x) << PCFG_BANDGAP_VBG_TRIMMED_SHIFT) & PCFG_BANDGAP_VBG_TRIMMED_MASK)
#define PCFG_BANDGAP_VBG_TRIMMED_GET(x) (((uint32_t)(x) & PCFG_BANDGAP_VBG_TRIMMED_MASK) >> PCFG_BANDGAP_VBG_TRIMMED_SHIFT)

/*
 * LOWPOWER_MODE (RW)
 *
 * Banggap work in low power mode, banggap function limited
 * 0: banggap works in normal mode
 * 1: banggap works in low power mode
 */
#define PCFG_BANDGAP_LOWPOWER_MODE_MASK (0x2000000UL)
#define PCFG_BANDGAP_LOWPOWER_MODE_SHIFT (25U)
#define PCFG_BANDGAP_LOWPOWER_MODE_SET(x) (((uint32_t)(x) << PCFG_BANDGAP_LOWPOWER_MODE_SHIFT) & PCFG_BANDGAP_LOWPOWER_MODE_MASK)
#define PCFG_BANDGAP_LOWPOWER_MODE_GET(x) (((uint32_t)(x) & PCFG_BANDGAP_LOWPOWER_MODE_MASK) >> PCFG_BANDGAP_LOWPOWER_MODE_SHIFT)

/*
 * POWER_SAVE (RW)
 *
 * Banggap work in power save mode, banggap function normally
 * 0: banggap works in high performance mode
 * 1: banggap works in power saving mode
 */
#define PCFG_BANDGAP_POWER_SAVE_MASK (0x1000000UL)
#define PCFG_BANDGAP_POWER_SAVE_SHIFT (24U)
#define PCFG_BANDGAP_POWER_SAVE_SET(x) (((uint32_t)(x) << PCFG_BANDGAP_POWER_SAVE_SHIFT) & PCFG_BANDGAP_POWER_SAVE_MASK)
#define PCFG_BANDGAP_POWER_SAVE_GET(x) (((uint32_t)(x) & PCFG_BANDGAP_POWER_SAVE_MASK) >> PCFG_BANDGAP_POWER_SAVE_SHIFT)

/*
 * VBG_1P0_TRIM (RW)
 *
 * Banggap 1.0V output trim value
 */
#define PCFG_BANDGAP_VBG_1P0_TRIM_MASK (0x1F0000UL)
#define PCFG_BANDGAP_VBG_1P0_TRIM_SHIFT (16U)
#define PCFG_BANDGAP_VBG_1P0_TRIM_SET(x) (((uint32_t)(x) << PCFG_BANDGAP_VBG_1P0_TRIM_SHIFT) & PCFG_BANDGAP_VBG_1P0_TRIM_MASK)
#define PCFG_BANDGAP_VBG_1P0_TRIM_GET(x) (((uint32_t)(x) & PCFG_BANDGAP_VBG_1P0_TRIM_MASK) >> PCFG_BANDGAP_VBG_1P0_TRIM_SHIFT)

/*
 * VBG_P65_TRIM (RW)
 *
 * Banggap 1.0V output trim value
 */
#define PCFG_BANDGAP_VBG_P65_TRIM_MASK (0x1F00U)
#define PCFG_BANDGAP_VBG_P65_TRIM_SHIFT (8U)
#define PCFG_BANDGAP_VBG_P65_TRIM_SET(x) (((uint32_t)(x) << PCFG_BANDGAP_VBG_P65_TRIM_SHIFT) & PCFG_BANDGAP_VBG_P65_TRIM_MASK)
#define PCFG_BANDGAP_VBG_P65_TRIM_GET(x) (((uint32_t)(x) & PCFG_BANDGAP_VBG_P65_TRIM_MASK) >> PCFG_BANDGAP_VBG_P65_TRIM_SHIFT)

/*
 * VBG_P50_TRIM (RW)
 *
 * Banggap 1.0V output trim value
 */
#define PCFG_BANDGAP_VBG_P50_TRIM_MASK (0x1FU)
#define PCFG_BANDGAP_VBG_P50_TRIM_SHIFT (0U)
#define PCFG_BANDGAP_VBG_P50_TRIM_SET(x) (((uint32_t)(x) << PCFG_BANDGAP_VBG_P50_TRIM_SHIFT) & PCFG_BANDGAP_VBG_P50_TRIM_MASK)
#define PCFG_BANDGAP_VBG_P50_TRIM_GET(x) (((uint32_t)(x) & PCFG_BANDGAP_VBG_P50_TRIM_MASK) >> PCFG_BANDGAP_VBG_P50_TRIM_SHIFT)

/* Bitfield definition for register: LDO1P1 */
/*
 * VOLT (RW)
 *
 * LDO output voltage in mV,  value valid through 700-1320, , step 20mV.  Hardware select voltage no less than target if not on valid steps, with maximum 1320mV.
 * 700: 700mV
 * 720: 720mV
 * . . .
 * 1320:1320mV
 */
#define PCFG_LDO1P1_VOLT_MASK (0xFFFU)
#define PCFG_LDO1P1_VOLT_SHIFT (0U)
#define PCFG_LDO1P1_VOLT_SET(x) (((uint32_t)(x) << PCFG_LDO1P1_VOLT_SHIFT) & PCFG_LDO1P1_VOLT_MASK)
#define PCFG_LDO1P1_VOLT_GET(x) (((uint32_t)(x) & PCFG_LDO1P1_VOLT_MASK) >> PCFG_LDO1P1_VOLT_SHIFT)

/* Bitfield definition for register: LDO2P5 */
/*
 * READY (RO)
 *
 * Ready flag, will set 1ms after enabled or voltage change
 * 0: LDO is not ready for use
 * 1: LDO is ready
 */
#define PCFG_LDO2P5_READY_MASK (0x10000000UL)
#define PCFG_LDO2P5_READY_SHIFT (28U)
#define PCFG_LDO2P5_READY_GET(x) (((uint32_t)(x) & PCFG_LDO2P5_READY_MASK) >> PCFG_LDO2P5_READY_SHIFT)

/*
 * ENABLE (RW)
 *
 * LDO enable
 * 0: turn off LDO
 * 1: turn on LDO
 */
#define PCFG_LDO2P5_ENABLE_MASK (0x10000UL)
#define PCFG_LDO2P5_ENABLE_SHIFT (16U)
#define PCFG_LDO2P5_ENABLE_SET(x) (((uint32_t)(x) << PCFG_LDO2P5_ENABLE_SHIFT) & PCFG_LDO2P5_ENABLE_MASK)
#define PCFG_LDO2P5_ENABLE_GET(x) (((uint32_t)(x) & PCFG_LDO2P5_ENABLE_MASK) >> PCFG_LDO2P5_ENABLE_SHIFT)

/*
 * VOLT (RW)
 *
 * LDO output voltage in mV,  value valid through 2125-2900, step 25mV.  Hardware select voltage no less than target if not on valid steps, with maximum 2900mV.
 * 2125: 2125mV
 * 2150: 2150mV
 * . . .
 * 2900:2900mV
 */
#define PCFG_LDO2P5_VOLT_MASK (0xFFFU)
#define PCFG_LDO2P5_VOLT_SHIFT (0U)
#define PCFG_LDO2P5_VOLT_SET(x) (((uint32_t)(x) << PCFG_LDO2P5_VOLT_SHIFT) & PCFG_LDO2P5_VOLT_MASK)
#define PCFG_LDO2P5_VOLT_GET(x) (((uint32_t)(x) & PCFG_LDO2P5_VOLT_MASK) >> PCFG_LDO2P5_VOLT_SHIFT)

/* Bitfield definition for register: DCDC_MODE */
/*
 * READY (RO)
 *
 * Ready flag
 * 0: DCDC is applying new change
 * 1: DCDC is ready
 */
#define PCFG_DCDC_MODE_READY_MASK (0x10000000UL)
#define PCFG_DCDC_MODE_READY_SHIFT (28U)
#define PCFG_DCDC_MODE_READY_GET(x) (((uint32_t)(x) & PCFG_DCDC_MODE_READY_MASK) >> PCFG_DCDC_MODE_READY_SHIFT)

/*
 * MODE (RW)
 *
 * DCDC work mode
 * XX0: turn off
 * 001: basic mode
 * 011: generic mode
 * 101: automatic mode
 * 111: expert mode
 */
#define PCFG_DCDC_MODE_MODE_MASK (0x70000UL)
#define PCFG_DCDC_MODE_MODE_SHIFT (16U)
#define PCFG_DCDC_MODE_MODE_SET(x) (((uint32_t)(x) << PCFG_DCDC_MODE_MODE_SHIFT) & PCFG_DCDC_MODE_MODE_MASK)
#define PCFG_DCDC_MODE_MODE_GET(x) (((uint32_t)(x) & PCFG_DCDC_MODE_MODE_MASK) >> PCFG_DCDC_MODE_MODE_SHIFT)

/*
 * VOLT (RW)
 *
 * DCDC voltage in mV in normal mode,  value valid through 600-1375, , step 25mV.  Hardware select voltage no less than target if not on valid steps, with maximum 1375mV.
 * 600: 600mV
 * 625: 625mV
 * . . .
 * 1375:1375mV
 */
#define PCFG_DCDC_MODE_VOLT_MASK (0xFFFU)
#define PCFG_DCDC_MODE_VOLT_SHIFT (0U)
#define PCFG_DCDC_MODE_VOLT_SET(x) (((uint32_t)(x) << PCFG_DCDC_MODE_VOLT_SHIFT) & PCFG_DCDC_MODE_VOLT_MASK)
#define PCFG_DCDC_MODE_VOLT_GET(x) (((uint32_t)(x) & PCFG_DCDC_MODE_VOLT_MASK) >> PCFG_DCDC_MODE_VOLT_SHIFT)

/* Bitfield definition for register: DCDC_LPMODE */
/*
 * STBY_VOLT (RW)
 *
 * DCDC voltage in mV in standby mode,  ,  value valid through 600-1375, , step 25mV.  Hardware select voltage no less than target if not on valid steps, with maximum 1375mV.
 * 600: 600mV
 * 625: 625mV
 * . . .
 * 1375:1375mV
 */
#define PCFG_DCDC_LPMODE_STBY_VOLT_MASK (0xFFFU)
#define PCFG_DCDC_LPMODE_STBY_VOLT_SHIFT (0U)
#define PCFG_DCDC_LPMODE_STBY_VOLT_SET(x) (((uint32_t)(x) << PCFG_DCDC_LPMODE_STBY_VOLT_SHIFT) & PCFG_DCDC_LPMODE_STBY_VOLT_MASK)
#define PCFG_DCDC_LPMODE_STBY_VOLT_GET(x) (((uint32_t)(x) & PCFG_DCDC_LPMODE_STBY_VOLT_MASK) >> PCFG_DCDC_LPMODE_STBY_VOLT_SHIFT)

/* Bitfield definition for register: DCDC_PROT */
/*
 * ILIMIT_LP (RW)
 *
 * over current setting for low power mode
 * 0:250mA
 * 1:200mA
 */
#define PCFG_DCDC_PROT_ILIMIT_LP_MASK (0x10000000UL)
#define PCFG_DCDC_PROT_ILIMIT_LP_SHIFT (28U)
#define PCFG_DCDC_PROT_ILIMIT_LP_SET(x) (((uint32_t)(x) << PCFG_DCDC_PROT_ILIMIT_LP_SHIFT) & PCFG_DCDC_PROT_ILIMIT_LP_MASK)
#define PCFG_DCDC_PROT_ILIMIT_LP_GET(x) (((uint32_t)(x) & PCFG_DCDC_PROT_ILIMIT_LP_MASK) >> PCFG_DCDC_PROT_ILIMIT_LP_SHIFT)

/*
 * OVERLOAD_LP (RO)
 *
 * over current in low power mode
 * 0: current is below setting
 * 1: overcurrent happened in low power mode
 */
#define PCFG_DCDC_PROT_OVERLOAD_LP_MASK (0x1000000UL)
#define PCFG_DCDC_PROT_OVERLOAD_LP_SHIFT (24U)
#define PCFG_DCDC_PROT_OVERLOAD_LP_GET(x) (((uint32_t)(x) & PCFG_DCDC_PROT_OVERLOAD_LP_MASK) >> PCFG_DCDC_PROT_OVERLOAD_LP_SHIFT)

/*
 * DISABLE_POWER_LOSS (RW)
 *
 * disable power loss protection
 * 0: power loss protection enabled, DCDC shuts down when power loss
 * 1: power loss protection disabled, DCDC try working after power voltage drop
 */
#define PCFG_DCDC_PROT_DISABLE_POWER_LOSS_MASK (0x800000UL)
#define PCFG_DCDC_PROT_DISABLE_POWER_LOSS_SHIFT (23U)
#define PCFG_DCDC_PROT_DISABLE_POWER_LOSS_SET(x) (((uint32_t)(x) << PCFG_DCDC_PROT_DISABLE_POWER_LOSS_SHIFT) & PCFG_DCDC_PROT_DISABLE_POWER_LOSS_MASK)
#define PCFG_DCDC_PROT_DISABLE_POWER_LOSS_GET(x) (((uint32_t)(x) & PCFG_DCDC_PROT_DISABLE_POWER_LOSS_MASK) >> PCFG_DCDC_PROT_DISABLE_POWER_LOSS_SHIFT)

/*
 * POWER_LOSS_FLAG (RO)
 *
 * power loss
 * 0: input power is good
 * 1: input power is too low
 */
#define PCFG_DCDC_PROT_POWER_LOSS_FLAG_MASK (0x10000UL)
#define PCFG_DCDC_PROT_POWER_LOSS_FLAG_SHIFT (16U)
#define PCFG_DCDC_PROT_POWER_LOSS_FLAG_GET(x) (((uint32_t)(x) & PCFG_DCDC_PROT_POWER_LOSS_FLAG_MASK) >> PCFG_DCDC_PROT_POWER_LOSS_FLAG_SHIFT)

/*
 * DISABLE_OVERVOLTAGE (RW)
 *
 * output over voltage protection
 * 0: protection enabled, DCDC will shut down is output voltage is unexpected high
 * 1: protection disabled, DCDC continue to adjust output voltage
 */
#define PCFG_DCDC_PROT_DISABLE_OVERVOLTAGE_MASK (0x8000U)
#define PCFG_DCDC_PROT_DISABLE_OVERVOLTAGE_SHIFT (15U)
#define PCFG_DCDC_PROT_DISABLE_OVERVOLTAGE_SET(x) (((uint32_t)(x) << PCFG_DCDC_PROT_DISABLE_OVERVOLTAGE_SHIFT) & PCFG_DCDC_PROT_DISABLE_OVERVOLTAGE_MASK)
#define PCFG_DCDC_PROT_DISABLE_OVERVOLTAGE_GET(x) (((uint32_t)(x) & PCFG_DCDC_PROT_DISABLE_OVERVOLTAGE_MASK) >> PCFG_DCDC_PROT_DISABLE_OVERVOLTAGE_SHIFT)

/*
 * OVERVOLT_FLAG (RO)
 *
 * output over voltage flag
 * 0: output is normal
 * 1: output is unexpected high
 */
#define PCFG_DCDC_PROT_OVERVOLT_FLAG_MASK (0x100U)
#define PCFG_DCDC_PROT_OVERVOLT_FLAG_SHIFT (8U)
#define PCFG_DCDC_PROT_OVERVOLT_FLAG_GET(x) (((uint32_t)(x) & PCFG_DCDC_PROT_OVERVOLT_FLAG_MASK) >> PCFG_DCDC_PROT_OVERVOLT_FLAG_SHIFT)

/*
 * DISABLE_SHORT (RW)
 *
 * disable output short circuit protection
 * 0: short circuits protection enabled, DCDC shut down if short circuit on output detected
 * 1: short circuit protection disabled
 */
#define PCFG_DCDC_PROT_DISABLE_SHORT_MASK (0x80U)
#define PCFG_DCDC_PROT_DISABLE_SHORT_SHIFT (7U)
#define PCFG_DCDC_PROT_DISABLE_SHORT_SET(x) (((uint32_t)(x) << PCFG_DCDC_PROT_DISABLE_SHORT_SHIFT) & PCFG_DCDC_PROT_DISABLE_SHORT_MASK)
#define PCFG_DCDC_PROT_DISABLE_SHORT_GET(x) (((uint32_t)(x) & PCFG_DCDC_PROT_DISABLE_SHORT_MASK) >> PCFG_DCDC_PROT_DISABLE_SHORT_SHIFT)

/*
 * SHORT_CURRENT (RW)
 *
 * short circuit current setting
 * 0: 2.0A,
 * 1: 1.3A
 */
#define PCFG_DCDC_PROT_SHORT_CURRENT_MASK (0x10U)
#define PCFG_DCDC_PROT_SHORT_CURRENT_SHIFT (4U)
#define PCFG_DCDC_PROT_SHORT_CURRENT_SET(x) (((uint32_t)(x) << PCFG_DCDC_PROT_SHORT_CURRENT_SHIFT) & PCFG_DCDC_PROT_SHORT_CURRENT_MASK)
#define PCFG_DCDC_PROT_SHORT_CURRENT_GET(x) (((uint32_t)(x) & PCFG_DCDC_PROT_SHORT_CURRENT_MASK) >> PCFG_DCDC_PROT_SHORT_CURRENT_SHIFT)

/*
 * SHORT_FLAG (RO)
 *
 * short circuit flag
 * 0: current is within limit
 * 1: short circuits detected
 */
#define PCFG_DCDC_PROT_SHORT_FLAG_MASK (0x1U)
#define PCFG_DCDC_PROT_SHORT_FLAG_SHIFT (0U)
#define PCFG_DCDC_PROT_SHORT_FLAG_GET(x) (((uint32_t)(x) & PCFG_DCDC_PROT_SHORT_FLAG_MASK) >> PCFG_DCDC_PROT_SHORT_FLAG_SHIFT)

/* Bitfield definition for register: DCDC_CURRENT */
/*
 * ESTI_EN (RW)
 *
 * enable current measure
 */
#define PCFG_DCDC_CURRENT_ESTI_EN_MASK (0x8000U)
#define PCFG_DCDC_CURRENT_ESTI_EN_SHIFT (15U)
#define PCFG_DCDC_CURRENT_ESTI_EN_SET(x) (((uint32_t)(x) << PCFG_DCDC_CURRENT_ESTI_EN_SHIFT) & PCFG_DCDC_CURRENT_ESTI_EN_MASK)
#define PCFG_DCDC_CURRENT_ESTI_EN_GET(x) (((uint32_t)(x) & PCFG_DCDC_CURRENT_ESTI_EN_MASK) >> PCFG_DCDC_CURRENT_ESTI_EN_SHIFT)

/*
 * VALID (RO)
 *
 * Current level valid
 * 0: data is invalid
 * 1: data is valid
 */
#define PCFG_DCDC_CURRENT_VALID_MASK (0x100U)
#define PCFG_DCDC_CURRENT_VALID_SHIFT (8U)
#define PCFG_DCDC_CURRENT_VALID_GET(x) (((uint32_t)(x) & PCFG_DCDC_CURRENT_VALID_MASK) >> PCFG_DCDC_CURRENT_VALID_SHIFT)

/*
 * LEVEL (RO)
 *
 * DCDC current level, current level is num * 50mA
 */
#define PCFG_DCDC_CURRENT_LEVEL_MASK (0x1FU)
#define PCFG_DCDC_CURRENT_LEVEL_SHIFT (0U)
#define PCFG_DCDC_CURRENT_LEVEL_GET(x) (((uint32_t)(x) & PCFG_DCDC_CURRENT_LEVEL_MASK) >> PCFG_DCDC_CURRENT_LEVEL_SHIFT)

/* Bitfield definition for register: DCDC_ADVMODE */
/*
 * EN_RCSCALE (RW)
 *
 * Enable RC scale
 */
#define PCFG_DCDC_ADVMODE_EN_RCSCALE_MASK (0x7000000UL)
#define PCFG_DCDC_ADVMODE_EN_RCSCALE_SHIFT (24U)
#define PCFG_DCDC_ADVMODE_EN_RCSCALE_SET(x) (((uint32_t)(x) << PCFG_DCDC_ADVMODE_EN_RCSCALE_SHIFT) & PCFG_DCDC_ADVMODE_EN_RCSCALE_MASK)
#define PCFG_DCDC_ADVMODE_EN_RCSCALE_GET(x) (((uint32_t)(x) & PCFG_DCDC_ADVMODE_EN_RCSCALE_MASK) >> PCFG_DCDC_ADVMODE_EN_RCSCALE_SHIFT)

/*
 * DC_C (RW)
 *
 * Loop C number
 */
#define PCFG_DCDC_ADVMODE_DC_C_MASK (0x300000UL)
#define PCFG_DCDC_ADVMODE_DC_C_SHIFT (20U)
#define PCFG_DCDC_ADVMODE_DC_C_SET(x) (((uint32_t)(x) << PCFG_DCDC_ADVMODE_DC_C_SHIFT) & PCFG_DCDC_ADVMODE_DC_C_MASK)
#define PCFG_DCDC_ADVMODE_DC_C_GET(x) (((uint32_t)(x) & PCFG_DCDC_ADVMODE_DC_C_MASK) >> PCFG_DCDC_ADVMODE_DC_C_SHIFT)

/*
 * DC_R (RW)
 *
 * Loop R number
 */
#define PCFG_DCDC_ADVMODE_DC_R_MASK (0xF0000UL)
#define PCFG_DCDC_ADVMODE_DC_R_SHIFT (16U)
#define PCFG_DCDC_ADVMODE_DC_R_SET(x) (((uint32_t)(x) << PCFG_DCDC_ADVMODE_DC_R_SHIFT) & PCFG_DCDC_ADVMODE_DC_R_MASK)
#define PCFG_DCDC_ADVMODE_DC_R_GET(x) (((uint32_t)(x) & PCFG_DCDC_ADVMODE_DC_R_MASK) >> PCFG_DCDC_ADVMODE_DC_R_SHIFT)

/*
 * EN_FF_DET (RW)
 *
 * enable feed forward detect
 * 0: feed forward detect is disabled
 * 1: feed forward detect is enabled
 */
#define PCFG_DCDC_ADVMODE_EN_FF_DET_MASK (0x40U)
#define PCFG_DCDC_ADVMODE_EN_FF_DET_SHIFT (6U)
#define PCFG_DCDC_ADVMODE_EN_FF_DET_SET(x) (((uint32_t)(x) << PCFG_DCDC_ADVMODE_EN_FF_DET_SHIFT) & PCFG_DCDC_ADVMODE_EN_FF_DET_MASK)
#define PCFG_DCDC_ADVMODE_EN_FF_DET_GET(x) (((uint32_t)(x) & PCFG_DCDC_ADVMODE_EN_FF_DET_MASK) >> PCFG_DCDC_ADVMODE_EN_FF_DET_SHIFT)

/*
 * EN_FF_LOOP (RW)
 *
 * enable feed forward loop
 * 0: feed forward loop is disabled
 * 1: feed forward loop is enabled
 */
#define PCFG_DCDC_ADVMODE_EN_FF_LOOP_MASK (0x20U)
#define PCFG_DCDC_ADVMODE_EN_FF_LOOP_SHIFT (5U)
#define PCFG_DCDC_ADVMODE_EN_FF_LOOP_SET(x) (((uint32_t)(x) << PCFG_DCDC_ADVMODE_EN_FF_LOOP_SHIFT) & PCFG_DCDC_ADVMODE_EN_FF_LOOP_MASK)
#define PCFG_DCDC_ADVMODE_EN_FF_LOOP_GET(x) (((uint32_t)(x) & PCFG_DCDC_ADVMODE_EN_FF_LOOP_MASK) >> PCFG_DCDC_ADVMODE_EN_FF_LOOP_SHIFT)

/*
 * EN_DCM_EXIT (RW)
 *
 * avoid over voltage
 * 0: stay in DCM mode when voltage excess
 * 1: change to CCM mode when voltage excess
 */
#define PCFG_DCDC_ADVMODE_EN_DCM_EXIT_MASK (0x8U)
#define PCFG_DCDC_ADVMODE_EN_DCM_EXIT_SHIFT (3U)
#define PCFG_DCDC_ADVMODE_EN_DCM_EXIT_SET(x) (((uint32_t)(x) << PCFG_DCDC_ADVMODE_EN_DCM_EXIT_SHIFT) & PCFG_DCDC_ADVMODE_EN_DCM_EXIT_MASK)
#define PCFG_DCDC_ADVMODE_EN_DCM_EXIT_GET(x) (((uint32_t)(x) & PCFG_DCDC_ADVMODE_EN_DCM_EXIT_MASK) >> PCFG_DCDC_ADVMODE_EN_DCM_EXIT_SHIFT)

/*
 * EN_SKIP (RW)
 *
 * enable skip on narrow pulse
 * 0: do not skip narrow pulse
 * 1: skip narrow pulse
 */
#define PCFG_DCDC_ADVMODE_EN_SKIP_MASK (0x4U)
#define PCFG_DCDC_ADVMODE_EN_SKIP_SHIFT (2U)
#define PCFG_DCDC_ADVMODE_EN_SKIP_SET(x) (((uint32_t)(x) << PCFG_DCDC_ADVMODE_EN_SKIP_SHIFT) & PCFG_DCDC_ADVMODE_EN_SKIP_MASK)
#define PCFG_DCDC_ADVMODE_EN_SKIP_GET(x) (((uint32_t)(x) & PCFG_DCDC_ADVMODE_EN_SKIP_MASK) >> PCFG_DCDC_ADVMODE_EN_SKIP_SHIFT)

/*
 * EN_IDLE (RW)
 *
 * enable skip when voltage is higher than threshold
 * 0: do not skip
 * 1: skip if voltage is excess
 */
#define PCFG_DCDC_ADVMODE_EN_IDLE_MASK (0x2U)
#define PCFG_DCDC_ADVMODE_EN_IDLE_SHIFT (1U)
#define PCFG_DCDC_ADVMODE_EN_IDLE_SET(x) (((uint32_t)(x) << PCFG_DCDC_ADVMODE_EN_IDLE_SHIFT) & PCFG_DCDC_ADVMODE_EN_IDLE_MASK)
#define PCFG_DCDC_ADVMODE_EN_IDLE_GET(x) (((uint32_t)(x) & PCFG_DCDC_ADVMODE_EN_IDLE_MASK) >> PCFG_DCDC_ADVMODE_EN_IDLE_SHIFT)

/*
 * EN_DCM (RW)
 *
 * DCM mode
 * 0: CCM mode
 * 1: DCM mode
 */
#define PCFG_DCDC_ADVMODE_EN_DCM_MASK (0x1U)
#define PCFG_DCDC_ADVMODE_EN_DCM_SHIFT (0U)
#define PCFG_DCDC_ADVMODE_EN_DCM_SET(x) (((uint32_t)(x) << PCFG_DCDC_ADVMODE_EN_DCM_SHIFT) & PCFG_DCDC_ADVMODE_EN_DCM_MASK)
#define PCFG_DCDC_ADVMODE_EN_DCM_GET(x) (((uint32_t)(x) & PCFG_DCDC_ADVMODE_EN_DCM_MASK) >> PCFG_DCDC_ADVMODE_EN_DCM_SHIFT)

/* Bitfield definition for register: DCDC_ADVPARAM */
/*
 * MIN_DUT (RW)
 *
 * minimum duty cycle
 */
#define PCFG_DCDC_ADVPARAM_MIN_DUT_MASK (0x7F00U)
#define PCFG_DCDC_ADVPARAM_MIN_DUT_SHIFT (8U)
#define PCFG_DCDC_ADVPARAM_MIN_DUT_SET(x) (((uint32_t)(x) << PCFG_DCDC_ADVPARAM_MIN_DUT_SHIFT) & PCFG_DCDC_ADVPARAM_MIN_DUT_MASK)
#define PCFG_DCDC_ADVPARAM_MIN_DUT_GET(x) (((uint32_t)(x) & PCFG_DCDC_ADVPARAM_MIN_DUT_MASK) >> PCFG_DCDC_ADVPARAM_MIN_DUT_SHIFT)

/*
 * MAX_DUT (RW)
 *
 * maximum duty cycle
 */
#define PCFG_DCDC_ADVPARAM_MAX_DUT_MASK (0x7FU)
#define PCFG_DCDC_ADVPARAM_MAX_DUT_SHIFT (0U)
#define PCFG_DCDC_ADVPARAM_MAX_DUT_SET(x) (((uint32_t)(x) << PCFG_DCDC_ADVPARAM_MAX_DUT_SHIFT) & PCFG_DCDC_ADVPARAM_MAX_DUT_MASK)
#define PCFG_DCDC_ADVPARAM_MAX_DUT_GET(x) (((uint32_t)(x) & PCFG_DCDC_ADVPARAM_MAX_DUT_MASK) >> PCFG_DCDC_ADVPARAM_MAX_DUT_SHIFT)

/* Bitfield definition for register: DCDC_MISC */
/*
 * EN_HYST (RW)
 *
 * hysteres enable
 */
#define PCFG_DCDC_MISC_EN_HYST_MASK (0x10000000UL)
#define PCFG_DCDC_MISC_EN_HYST_SHIFT (28U)
#define PCFG_DCDC_MISC_EN_HYST_SET(x) (((uint32_t)(x) << PCFG_DCDC_MISC_EN_HYST_SHIFT) & PCFG_DCDC_MISC_EN_HYST_MASK)
#define PCFG_DCDC_MISC_EN_HYST_GET(x) (((uint32_t)(x) & PCFG_DCDC_MISC_EN_HYST_MASK) >> PCFG_DCDC_MISC_EN_HYST_SHIFT)

/*
 * HYST_SIGN (RW)
 *
 * hysteres sign
 */
#define PCFG_DCDC_MISC_HYST_SIGN_MASK (0x2000000UL)
#define PCFG_DCDC_MISC_HYST_SIGN_SHIFT (25U)
#define PCFG_DCDC_MISC_HYST_SIGN_SET(x) (((uint32_t)(x) << PCFG_DCDC_MISC_HYST_SIGN_SHIFT) & PCFG_DCDC_MISC_HYST_SIGN_MASK)
#define PCFG_DCDC_MISC_HYST_SIGN_GET(x) (((uint32_t)(x) & PCFG_DCDC_MISC_HYST_SIGN_MASK) >> PCFG_DCDC_MISC_HYST_SIGN_SHIFT)

/*
 * HYST_THRS (RW)
 *
 * hysteres threshold
 */
#define PCFG_DCDC_MISC_HYST_THRS_MASK (0x1000000UL)
#define PCFG_DCDC_MISC_HYST_THRS_SHIFT (24U)
#define PCFG_DCDC_MISC_HYST_THRS_SET(x) (((uint32_t)(x) << PCFG_DCDC_MISC_HYST_THRS_SHIFT) & PCFG_DCDC_MISC_HYST_THRS_MASK)
#define PCFG_DCDC_MISC_HYST_THRS_GET(x) (((uint32_t)(x) & PCFG_DCDC_MISC_HYST_THRS_MASK) >> PCFG_DCDC_MISC_HYST_THRS_SHIFT)

/*
 * RC_SCALE (RW)
 *
 * Loop RC scale threshold
 */
#define PCFG_DCDC_MISC_RC_SCALE_MASK (0x100000UL)
#define PCFG_DCDC_MISC_RC_SCALE_SHIFT (20U)
#define PCFG_DCDC_MISC_RC_SCALE_SET(x) (((uint32_t)(x) << PCFG_DCDC_MISC_RC_SCALE_SHIFT) & PCFG_DCDC_MISC_RC_SCALE_MASK)
#define PCFG_DCDC_MISC_RC_SCALE_GET(x) (((uint32_t)(x) & PCFG_DCDC_MISC_RC_SCALE_MASK) >> PCFG_DCDC_MISC_RC_SCALE_SHIFT)

/*
 * DC_FF (RW)
 *
 * Loop feed forward number
 */
#define PCFG_DCDC_MISC_DC_FF_MASK (0x70000UL)
#define PCFG_DCDC_MISC_DC_FF_SHIFT (16U)
#define PCFG_DCDC_MISC_DC_FF_SET(x) (((uint32_t)(x) << PCFG_DCDC_MISC_DC_FF_SHIFT) & PCFG_DCDC_MISC_DC_FF_MASK)
#define PCFG_DCDC_MISC_DC_FF_GET(x) (((uint32_t)(x) & PCFG_DCDC_MISC_DC_FF_MASK) >> PCFG_DCDC_MISC_DC_FF_SHIFT)

/*
 * OL_THRE (RW)
 *
 * overload for threshold for lod power mode
 */
#define PCFG_DCDC_MISC_OL_THRE_MASK (0x300U)
#define PCFG_DCDC_MISC_OL_THRE_SHIFT (8U)
#define PCFG_DCDC_MISC_OL_THRE_SET(x) (((uint32_t)(x) << PCFG_DCDC_MISC_OL_THRE_SHIFT) & PCFG_DCDC_MISC_OL_THRE_MASK)
#define PCFG_DCDC_MISC_OL_THRE_GET(x) (((uint32_t)(x) & PCFG_DCDC_MISC_OL_THRE_MASK) >> PCFG_DCDC_MISC_OL_THRE_SHIFT)

/*
 * OL_HYST (RW)
 *
 * current hysteres range
 * 0: 12.5mV
 * 1: 25mV
 */
#define PCFG_DCDC_MISC_OL_HYST_MASK (0x10U)
#define PCFG_DCDC_MISC_OL_HYST_SHIFT (4U)
#define PCFG_DCDC_MISC_OL_HYST_SET(x) (((uint32_t)(x) << PCFG_DCDC_MISC_OL_HYST_SHIFT) & PCFG_DCDC_MISC_OL_HYST_MASK)
#define PCFG_DCDC_MISC_OL_HYST_GET(x) (((uint32_t)(x) & PCFG_DCDC_MISC_OL_HYST_MASK) >> PCFG_DCDC_MISC_OL_HYST_SHIFT)

/*
 * DELAY (RW)
 *
 * enable delay
 * 0: delay disabled,
 * 1: delay enabled
 */
#define PCFG_DCDC_MISC_DELAY_MASK (0x4U)
#define PCFG_DCDC_MISC_DELAY_SHIFT (2U)
#define PCFG_DCDC_MISC_DELAY_SET(x) (((uint32_t)(x) << PCFG_DCDC_MISC_DELAY_SHIFT) & PCFG_DCDC_MISC_DELAY_MASK)
#define PCFG_DCDC_MISC_DELAY_GET(x) (((uint32_t)(x) & PCFG_DCDC_MISC_DELAY_MASK) >> PCFG_DCDC_MISC_DELAY_SHIFT)

/*
 * CLK_SEL (RW)
 *
 * clock selection
 * 0: select DCDC internal oscillator
 * 1: select RC24M oscillator
 */
#define PCFG_DCDC_MISC_CLK_SEL_MASK (0x2U)
#define PCFG_DCDC_MISC_CLK_SEL_SHIFT (1U)
#define PCFG_DCDC_MISC_CLK_SEL_SET(x) (((uint32_t)(x) << PCFG_DCDC_MISC_CLK_SEL_SHIFT) & PCFG_DCDC_MISC_CLK_SEL_MASK)
#define PCFG_DCDC_MISC_CLK_SEL_GET(x) (((uint32_t)(x) & PCFG_DCDC_MISC_CLK_SEL_MASK) >> PCFG_DCDC_MISC_CLK_SEL_SHIFT)

/*
 * EN_STEP (RW)
 *
 * enable stepping in voltage change
 * 0: stepping disabled,
 * 1: steping enabled
 */
#define PCFG_DCDC_MISC_EN_STEP_MASK (0x1U)
#define PCFG_DCDC_MISC_EN_STEP_SHIFT (0U)
#define PCFG_DCDC_MISC_EN_STEP_SET(x) (((uint32_t)(x) << PCFG_DCDC_MISC_EN_STEP_SHIFT) & PCFG_DCDC_MISC_EN_STEP_MASK)
#define PCFG_DCDC_MISC_EN_STEP_GET(x) (((uint32_t)(x) & PCFG_DCDC_MISC_EN_STEP_MASK) >> PCFG_DCDC_MISC_EN_STEP_SHIFT)

/* Bitfield definition for register: DCDC_DEBUG */
/*
 * UPDATE_TIME (RW)
 *
 * DCDC voltage change time in 24M clock cycles, default value is 1mS
 */
#define PCFG_DCDC_DEBUG_UPDATE_TIME_MASK (0xFFFFFUL)
#define PCFG_DCDC_DEBUG_UPDATE_TIME_SHIFT (0U)
#define PCFG_DCDC_DEBUG_UPDATE_TIME_SET(x) (((uint32_t)(x) << PCFG_DCDC_DEBUG_UPDATE_TIME_SHIFT) & PCFG_DCDC_DEBUG_UPDATE_TIME_MASK)
#define PCFG_DCDC_DEBUG_UPDATE_TIME_GET(x) (((uint32_t)(x) & PCFG_DCDC_DEBUG_UPDATE_TIME_MASK) >> PCFG_DCDC_DEBUG_UPDATE_TIME_SHIFT)

/* Bitfield definition for register: DCDC_START_TIME */
/*
 * START_TIME (RW)
 *
 * Start delay for DCDC to turn on, in 24M clock cycles, default value is 3mS
 */
#define PCFG_DCDC_START_TIME_START_TIME_MASK (0xFFFFFUL)
#define PCFG_DCDC_START_TIME_START_TIME_SHIFT (0U)
#define PCFG_DCDC_START_TIME_START_TIME_SET(x) (((uint32_t)(x) << PCFG_DCDC_START_TIME_START_TIME_SHIFT) & PCFG_DCDC_START_TIME_START_TIME_MASK)
#define PCFG_DCDC_START_TIME_START_TIME_GET(x) (((uint32_t)(x) & PCFG_DCDC_START_TIME_START_TIME_MASK) >> PCFG_DCDC_START_TIME_START_TIME_SHIFT)

/* Bitfield definition for register: DCDC_RESUME_TIME */
/*
 * RESUME_TIME (RW)
 *
 * Resume delay for DCDC to recover from low power mode, in 24M clock cycles, default value is 1.5mS
 */
#define PCFG_DCDC_RESUME_TIME_RESUME_TIME_MASK (0xFFFFFUL)
#define PCFG_DCDC_RESUME_TIME_RESUME_TIME_SHIFT (0U)
#define PCFG_DCDC_RESUME_TIME_RESUME_TIME_SET(x) (((uint32_t)(x) << PCFG_DCDC_RESUME_TIME_RESUME_TIME_SHIFT) & PCFG_DCDC_RESUME_TIME_RESUME_TIME_MASK)
#define PCFG_DCDC_RESUME_TIME_RESUME_TIME_GET(x) (((uint32_t)(x) & PCFG_DCDC_RESUME_TIME_RESUME_TIME_MASK) >> PCFG_DCDC_RESUME_TIME_RESUME_TIME_SHIFT)

/* Bitfield definition for register: POWER_TRAP */
/*
 * TRIGGERED (RW)
 *
 * Low power trap status, thit bit will set when power related low power flow triggered, write 1 to clear this flag.
 * 0: low power trap is not triggered
 * 1: low power trap triggered
 */
#define PCFG_POWER_TRAP_TRIGGERED_MASK (0x80000000UL)
#define PCFG_POWER_TRAP_TRIGGERED_SHIFT (31U)
#define PCFG_POWER_TRAP_TRIGGERED_SET(x) (((uint32_t)(x) << PCFG_POWER_TRAP_TRIGGERED_SHIFT) & PCFG_POWER_TRAP_TRIGGERED_MASK)
#define PCFG_POWER_TRAP_TRIGGERED_GET(x) (((uint32_t)(x) & PCFG_POWER_TRAP_TRIGGERED_MASK) >> PCFG_POWER_TRAP_TRIGGERED_SHIFT)

/*
 * RETENTION (RW)
 *
 * DCDC enter standby mode, which will reduce voltage for memory content retention
 * 0: Shutdown DCDC
 * 1: reduce DCDC voltage
 */
#define PCFG_POWER_TRAP_RETENTION_MASK (0x10000UL)
#define PCFG_POWER_TRAP_RETENTION_SHIFT (16U)
#define PCFG_POWER_TRAP_RETENTION_SET(x) (((uint32_t)(x) << PCFG_POWER_TRAP_RETENTION_SHIFT) & PCFG_POWER_TRAP_RETENTION_MASK)
#define PCFG_POWER_TRAP_RETENTION_GET(x) (((uint32_t)(x) & PCFG_POWER_TRAP_RETENTION_MASK) >> PCFG_POWER_TRAP_RETENTION_SHIFT)

/*
 * TRAP (RW)
 *
 * Enable trap of SOC power supply, trap is used to hold SOC in low power mode for DCDC to enter further low power mode, this bit will self-clear when power related low pwer flow triggered
 * 0: trap not enabled, pmic side low power function disabled
 * 1: trap enabled, STOP operation leads to PMIC low power flow if SOC is not retentioned.
 */
#define PCFG_POWER_TRAP_TRAP_MASK (0x1U)
#define PCFG_POWER_TRAP_TRAP_SHIFT (0U)
#define PCFG_POWER_TRAP_TRAP_SET(x) (((uint32_t)(x) << PCFG_POWER_TRAP_TRAP_SHIFT) & PCFG_POWER_TRAP_TRAP_MASK)
#define PCFG_POWER_TRAP_TRAP_GET(x) (((uint32_t)(x) & PCFG_POWER_TRAP_TRAP_MASK) >> PCFG_POWER_TRAP_TRAP_SHIFT)

/* Bitfield definition for register: WAKE_CAUSE */
/*
 * CAUSE (RW)
 *
 * wake up cause, each bit represents one wake up source, write 1 to clear the register bit
 * 0: wake up source is not active during last wakeup
 * 1: wake up source is active furing last wakeup
 * bit 0: pmic_enable
 * bit 1: debug wakeup
 * bit 4: fuse interrupt
 * bit 7: UART interrupt
 * bit 8: TMR interrupt
 * bit 9: WDG interrupt
 * bit10: GPIO in PMIC interrupt
 * bit11: Security monitor interrupt
 * bit12: Security in PMIC event
 * bit16: Security violation in BATT
 * bit17: GPIO in BATT interrupt
 * bit18: BATT Button interrupt
 * bit19: RTC alarm interrupt
 */
#define PCFG_WAKE_CAUSE_CAUSE_MASK (0xFFFFFFFFUL)
#define PCFG_WAKE_CAUSE_CAUSE_SHIFT (0U)
#define PCFG_WAKE_CAUSE_CAUSE_SET(x) (((uint32_t)(x) << PCFG_WAKE_CAUSE_CAUSE_SHIFT) & PCFG_WAKE_CAUSE_CAUSE_MASK)
#define PCFG_WAKE_CAUSE_CAUSE_GET(x) (((uint32_t)(x) & PCFG_WAKE_CAUSE_CAUSE_MASK) >> PCFG_WAKE_CAUSE_CAUSE_SHIFT)

/* Bitfield definition for register: WAKE_MASK */
/*
 * MASK (RW)
 *
 * mask for wake up sources, each bit represents one wakeup source
 * 0: allow source to wake up system
 * 1: disallow source to wakeup system
 * bit 0: pmic_enable
 * bit 1: debug wakeup
 * bit 4: fuse interrupt
 * bit 7: UART interrupt
 * bit 8: TMR interrupt
 * bit 9: WDG interrupt
 * bit10: GPIO in PMIC interrupt
 * bit11: Security monitor interrupt
 * bit12: Security in PMIC event
 * bit16: Security violation in BATT
 * bit17: GPIO in BATT interrupt
 * bit18: BATT Button interrupt
 * bit19: RTC alarm interrupt
 */
#define PCFG_WAKE_MASK_MASK_MASK (0xFFFFFFFFUL)
#define PCFG_WAKE_MASK_MASK_SHIFT (0U)
#define PCFG_WAKE_MASK_MASK_SET(x) (((uint32_t)(x) << PCFG_WAKE_MASK_MASK_SHIFT) & PCFG_WAKE_MASK_MASK_MASK)
#define PCFG_WAKE_MASK_MASK_GET(x) (((uint32_t)(x) & PCFG_WAKE_MASK_MASK_MASK) >> PCFG_WAKE_MASK_MASK_SHIFT)

/* Bitfield definition for register: SCG_CTRL */
/*
 * SCG (RW)
 *
 * control whether clock being gated during PMIC low power flow, 2 bits for each peripheral
 * 00,01: reserved
 * 10: clock is always off
 * 11: clock is always on
 * bit0-1: fuse
 * bit6-7:gpio
 * bit8-9:ioc
 * bit10-11: timer
 * bit12-13:wdog
 * bit14-15:uart
 * bit16-17:debug
 */
#define PCFG_SCG_CTRL_SCG_MASK (0xFFFFFFFFUL)
#define PCFG_SCG_CTRL_SCG_SHIFT (0U)
#define PCFG_SCG_CTRL_SCG_SET(x) (((uint32_t)(x) << PCFG_SCG_CTRL_SCG_SHIFT) & PCFG_SCG_CTRL_SCG_MASK)
#define PCFG_SCG_CTRL_SCG_GET(x) (((uint32_t)(x) & PCFG_SCG_CTRL_SCG_MASK) >> PCFG_SCG_CTRL_SCG_SHIFT)

/* Bitfield definition for register: DEBUG_STOP */
/*
 * CPU1 (RW)
 *
 * Stop peripheral when CPU1 enter debug mode
 * 0: peripheral keep running when CPU1 in debug mode
 * 1: peripheral enter debug mode when CPU1 enter debug
 */
#define PCFG_DEBUG_STOP_CPU1_MASK (0x2U)
#define PCFG_DEBUG_STOP_CPU1_SHIFT (1U)
#define PCFG_DEBUG_STOP_CPU1_SET(x) (((uint32_t)(x) << PCFG_DEBUG_STOP_CPU1_SHIFT) & PCFG_DEBUG_STOP_CPU1_MASK)
#define PCFG_DEBUG_STOP_CPU1_GET(x) (((uint32_t)(x) & PCFG_DEBUG_STOP_CPU1_MASK) >> PCFG_DEBUG_STOP_CPU1_SHIFT)

/*
 * CPU0 (RW)
 *
 * Stop peripheral when CPU0 enter debug mode
 * 0: peripheral keep running when CPU0 in debug mode
 * 1: peripheral enter debug mode when CPU0 enter debug
 */
#define PCFG_DEBUG_STOP_CPU0_MASK (0x1U)
#define PCFG_DEBUG_STOP_CPU0_SHIFT (0U)
#define PCFG_DEBUG_STOP_CPU0_SET(x) (((uint32_t)(x) << PCFG_DEBUG_STOP_CPU0_SHIFT) & PCFG_DEBUG_STOP_CPU0_MASK)
#define PCFG_DEBUG_STOP_CPU0_GET(x) (((uint32_t)(x) & PCFG_DEBUG_STOP_CPU0_MASK) >> PCFG_DEBUG_STOP_CPU0_SHIFT)

/* Bitfield definition for register: RC24M */
/*
 * RC_TRIMMED (RW)
 *
 * RC24M trim happened, this bit set by hardware after trim value loaded, and stop load, write 0 will clear this bit and reload trim value
 * 0: RC is not trimmed
 * 1: RC is trimmed
 */
#define PCFG_RC24M_RC_TRIMMED_MASK (0x80000000UL)
#define PCFG_RC24M_RC_TRIMMED_SHIFT (31U)
#define PCFG_RC24M_RC_TRIMMED_SET(x) (((uint32_t)(x) << PCFG_RC24M_RC_TRIMMED_SHIFT) & PCFG_RC24M_RC_TRIMMED_MASK)
#define PCFG_RC24M_RC_TRIMMED_GET(x) (((uint32_t)(x) & PCFG_RC24M_RC_TRIMMED_MASK) >> PCFG_RC24M_RC_TRIMMED_SHIFT)

/*
 * TRIM_C (RW)
 *
 * Coarse trim for RC24M, bigger value means faster
 */
#define PCFG_RC24M_TRIM_C_MASK (0x700U)
#define PCFG_RC24M_TRIM_C_SHIFT (8U)
#define PCFG_RC24M_TRIM_C_SET(x) (((uint32_t)(x) << PCFG_RC24M_TRIM_C_SHIFT) & PCFG_RC24M_TRIM_C_MASK)
#define PCFG_RC24M_TRIM_C_GET(x) (((uint32_t)(x) & PCFG_RC24M_TRIM_C_MASK) >> PCFG_RC24M_TRIM_C_SHIFT)

/*
 * TRIM_F (RW)
 *
 * Fine trim for RC24M, bigger value means faster
 */
#define PCFG_RC24M_TRIM_F_MASK (0x1FU)
#define PCFG_RC24M_TRIM_F_SHIFT (0U)
#define PCFG_RC24M_TRIM_F_SET(x) (((uint32_t)(x) << PCFG_RC24M_TRIM_F_SHIFT) & PCFG_RC24M_TRIM_F_MASK)
#define PCFG_RC24M_TRIM_F_GET(x) (((uint32_t)(x) & PCFG_RC24M_TRIM_F_MASK) >> PCFG_RC24M_TRIM_F_SHIFT)

/* Bitfield definition for register: RC24M_TRACK */
/*
 * SEL24M (RW)
 *
 * Select track reference
 * 0: select 32K as reference
 * 1: select 24M XTAL as reference
 */
#define PCFG_RC24M_TRACK_SEL24M_MASK (0x10000UL)
#define PCFG_RC24M_TRACK_SEL24M_SHIFT (16U)
#define PCFG_RC24M_TRACK_SEL24M_SET(x) (((uint32_t)(x) << PCFG_RC24M_TRACK_SEL24M_SHIFT) & PCFG_RC24M_TRACK_SEL24M_MASK)
#define PCFG_RC24M_TRACK_SEL24M_GET(x) (((uint32_t)(x) & PCFG_RC24M_TRACK_SEL24M_MASK) >> PCFG_RC24M_TRACK_SEL24M_SHIFT)

/*
 * RETURN (RW)
 *
 * Retrun default value when XTAL loss
 * 0: remain last tracking value
 * 1: switch to default value
 */
#define PCFG_RC24M_TRACK_RETURN_MASK (0x10U)
#define PCFG_RC24M_TRACK_RETURN_SHIFT (4U)
#define PCFG_RC24M_TRACK_RETURN_SET(x) (((uint32_t)(x) << PCFG_RC24M_TRACK_RETURN_SHIFT) & PCFG_RC24M_TRACK_RETURN_MASK)
#define PCFG_RC24M_TRACK_RETURN_GET(x) (((uint32_t)(x) & PCFG_RC24M_TRACK_RETURN_MASK) >> PCFG_RC24M_TRACK_RETURN_SHIFT)

/*
 * TRACK (RW)
 *
 * track mode
 * 0: RC24M free running
 * 1: track RC24M to external XTAL
 */
#define PCFG_RC24M_TRACK_TRACK_MASK (0x1U)
#define PCFG_RC24M_TRACK_TRACK_SHIFT (0U)
#define PCFG_RC24M_TRACK_TRACK_SET(x) (((uint32_t)(x) << PCFG_RC24M_TRACK_TRACK_SHIFT) & PCFG_RC24M_TRACK_TRACK_MASK)
#define PCFG_RC24M_TRACK_TRACK_GET(x) (((uint32_t)(x) & PCFG_RC24M_TRACK_TRACK_MASK) >> PCFG_RC24M_TRACK_TRACK_SHIFT)

/* Bitfield definition for register: TRACK_TARGET */
/*
 * PRE_DIV (RW)
 *
 * Divider for reference source
 */
#define PCFG_TRACK_TARGET_PRE_DIV_MASK (0xFFFF0000UL)
#define PCFG_TRACK_TARGET_PRE_DIV_SHIFT (16U)
#define PCFG_TRACK_TARGET_PRE_DIV_SET(x) (((uint32_t)(x) << PCFG_TRACK_TARGET_PRE_DIV_SHIFT) & PCFG_TRACK_TARGET_PRE_DIV_MASK)
#define PCFG_TRACK_TARGET_PRE_DIV_GET(x) (((uint32_t)(x) & PCFG_TRACK_TARGET_PRE_DIV_MASK) >> PCFG_TRACK_TARGET_PRE_DIV_SHIFT)

/*
 * TARGET (RW)
 *
 * Target frequency multiplier of divided source
 */
#define PCFG_TRACK_TARGET_TARGET_MASK (0xFFFFU)
#define PCFG_TRACK_TARGET_TARGET_SHIFT (0U)
#define PCFG_TRACK_TARGET_TARGET_SET(x) (((uint32_t)(x) << PCFG_TRACK_TARGET_TARGET_SHIFT) & PCFG_TRACK_TARGET_TARGET_MASK)
#define PCFG_TRACK_TARGET_TARGET_GET(x) (((uint32_t)(x) & PCFG_TRACK_TARGET_TARGET_MASK) >> PCFG_TRACK_TARGET_TARGET_SHIFT)

/* Bitfield definition for register: STATUS */
/*
 * SEL32K (RO)
 *
 * track is using XTAL32K
 * 0: track is not using XTAL32K
 * 1: track is using XTAL32K
 */
#define PCFG_STATUS_SEL32K_MASK (0x100000UL)
#define PCFG_STATUS_SEL32K_SHIFT (20U)
#define PCFG_STATUS_SEL32K_GET(x) (((uint32_t)(x) & PCFG_STATUS_SEL32K_MASK) >> PCFG_STATUS_SEL32K_SHIFT)

/*
 * SEL24M (RO)
 *
 * track is using XTAL24M
 * 0: track is not using XTAL24M
 * 1: track is using XTAL24M
 */
#define PCFG_STATUS_SEL24M_MASK (0x10000UL)
#define PCFG_STATUS_SEL24M_SHIFT (16U)
#define PCFG_STATUS_SEL24M_GET(x) (((uint32_t)(x) & PCFG_STATUS_SEL24M_MASK) >> PCFG_STATUS_SEL24M_SHIFT)

/*
 * EN_TRIM (RO)
 *
 * default value takes effect
 * 0: default value is invalid
 * 1: default value is valid
 */
#define PCFG_STATUS_EN_TRIM_MASK (0x8000U)
#define PCFG_STATUS_EN_TRIM_SHIFT (15U)
#define PCFG_STATUS_EN_TRIM_GET(x) (((uint32_t)(x) & PCFG_STATUS_EN_TRIM_MASK) >> PCFG_STATUS_EN_TRIM_SHIFT)

/*
 * TRIM_C (RO)
 *
 * default coarse trim value
 */
#define PCFG_STATUS_TRIM_C_MASK (0x700U)
#define PCFG_STATUS_TRIM_C_SHIFT (8U)
#define PCFG_STATUS_TRIM_C_GET(x) (((uint32_t)(x) & PCFG_STATUS_TRIM_C_MASK) >> PCFG_STATUS_TRIM_C_SHIFT)

/*
 * TRIM_F (RO)
 *
 * default fine trim value
 */
#define PCFG_STATUS_TRIM_F_MASK (0x1FU)
#define PCFG_STATUS_TRIM_F_SHIFT (0U)
#define PCFG_STATUS_TRIM_F_GET(x) (((uint32_t)(x) & PCFG_STATUS_TRIM_F_MASK) >> PCFG_STATUS_TRIM_F_SHIFT)




#endif /* HPM_PCFG_H */
