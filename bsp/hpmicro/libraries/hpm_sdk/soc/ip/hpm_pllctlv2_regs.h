/*
 * Copyright (c) 2021-2023 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */


#ifndef HPM_PLLCTLV2_H
#define HPM_PLLCTLV2_H

typedef struct {
    __RW uint32_t XTAL;                        /* 0x0: OSC configuration */
    __R  uint8_t  RESERVED0[124];              /* 0x4 - 0x7F: Reserved */
    struct {
        __RW uint32_t MFI;                     /* 0x80: PLL0 multiple register */
        __RW uint32_t MFN;                     /* 0x84: PLL0 fraction numerator register */
        __RW uint32_t MFD;                     /* 0x88: PLL0 fraction demoninator register */
        __RW uint32_t SS_STEP;                 /* 0x8C: PLL0 spread spectrum step register */
        __RW uint32_t SS_STOP;                 /* 0x90: PLL0 spread spectrum stop register */
        __RW uint32_t CONFIG;                  /* 0x94: PLL0 confguration register */
        __RW uint32_t LOCKTIME;                /* 0x98: PLL0 lock time register */
        __RW uint32_t STEPTIME;                /* 0x9C: PLL0 step time register */
        __RW uint32_t ADVANCED;                /* 0xA0: PLL0 advance configuration register */
        __R  uint8_t  RESERVED0[28];           /* 0xA4 - 0xBF: Reserved */
        __RW uint32_t DIV[3];                  /* 0xC0 - 0xC8: PLL0 divider output 0 configuration register */
        __R  uint8_t  RESERVED1[52];           /* 0xCC - 0xFF: Reserved */
    } PLL[3];
} PLLCTLV2_Type;


/* Bitfield definition for register: XTAL */
/*
 * BUSY (RO)
 *
 * Busy flag
 * 0: Oscillator is working or shutdown
 * 1: Oscillator is changing status
 */
#define PLLCTLV2_XTAL_BUSY_MASK (0x80000000UL)
#define PLLCTLV2_XTAL_BUSY_SHIFT (31U)
#define PLLCTLV2_XTAL_BUSY_GET(x) (((uint32_t)(x) & PLLCTLV2_XTAL_BUSY_MASK) >> PLLCTLV2_XTAL_BUSY_SHIFT)

/*
 * RESPONSE (RO)
 *
 * Crystal oscillator status
 * 0: Oscillator is not stable
 * 1: Oscillator is stable for use
 */
#define PLLCTLV2_XTAL_RESPONSE_MASK (0x20000000UL)
#define PLLCTLV2_XTAL_RESPONSE_SHIFT (29U)
#define PLLCTLV2_XTAL_RESPONSE_GET(x) (((uint32_t)(x) & PLLCTLV2_XTAL_RESPONSE_MASK) >> PLLCTLV2_XTAL_RESPONSE_SHIFT)

/*
 * ENABLE (RO)
 *
 * Crystal oscillator enable status
 * 0: Oscillator is off
 * 1: Oscillator is on
 */
#define PLLCTLV2_XTAL_ENABLE_MASK (0x10000000UL)
#define PLLCTLV2_XTAL_ENABLE_SHIFT (28U)
#define PLLCTLV2_XTAL_ENABLE_GET(x) (((uint32_t)(x) & PLLCTLV2_XTAL_ENABLE_MASK) >> PLLCTLV2_XTAL_ENABLE_SHIFT)

/*
 * RAMP_TIME (RW)
 *
 * Rampup time of XTAL oscillator in cycles of RC24M clock
 * 0: 0 cycle
 * 1: 1 cycle
 * 2: 2 cycle
 * 1048575: 1048575 cycles
 */
#define PLLCTLV2_XTAL_RAMP_TIME_MASK (0xFFFFFUL)
#define PLLCTLV2_XTAL_RAMP_TIME_SHIFT (0U)
#define PLLCTLV2_XTAL_RAMP_TIME_SET(x) (((uint32_t)(x) << PLLCTLV2_XTAL_RAMP_TIME_SHIFT) & PLLCTLV2_XTAL_RAMP_TIME_MASK)
#define PLLCTLV2_XTAL_RAMP_TIME_GET(x) (((uint32_t)(x) & PLLCTLV2_XTAL_RAMP_TIME_MASK) >> PLLCTLV2_XTAL_RAMP_TIME_SHIFT)

/* Bitfield definition for register of struct array PLL: MFI */
/*
 * BUSY (RO)
 *
 * Busy flag
 * 0: PLL is stable or shutdown
 * 1: PLL is changing status
 */
#define PLLCTLV2_PLL_MFI_BUSY_MASK (0x80000000UL)
#define PLLCTLV2_PLL_MFI_BUSY_SHIFT (31U)
#define PLLCTLV2_PLL_MFI_BUSY_GET(x) (((uint32_t)(x) & PLLCTLV2_PLL_MFI_BUSY_MASK) >> PLLCTLV2_PLL_MFI_BUSY_SHIFT)

/*
 * RESPONSE (RO)
 *
 * PLL status
 * 0: PLL is not stable
 * 1: PLL is stable for use
 */
#define PLLCTLV2_PLL_MFI_RESPONSE_MASK (0x20000000UL)
#define PLLCTLV2_PLL_MFI_RESPONSE_SHIFT (29U)
#define PLLCTLV2_PLL_MFI_RESPONSE_GET(x) (((uint32_t)(x) & PLLCTLV2_PLL_MFI_RESPONSE_MASK) >> PLLCTLV2_PLL_MFI_RESPONSE_SHIFT)

/*
 * ENABLE (RO)
 *
 * PLL enable status
 * 0: PLL is off
 * 1: PLL is on
 */
#define PLLCTLV2_PLL_MFI_ENABLE_MASK (0x10000000UL)
#define PLLCTLV2_PLL_MFI_ENABLE_SHIFT (28U)
#define PLLCTLV2_PLL_MFI_ENABLE_GET(x) (((uint32_t)(x) & PLLCTLV2_PLL_MFI_ENABLE_MASK) >> PLLCTLV2_PLL_MFI_ENABLE_SHIFT)

/*
 * MFI (RW)
 *
 * loop back divider of PLL, support from 13 to 42, f=fref*(mfi + mfn/mfd)
 * 0-15: invalid
 * 16: divide by 16
 * 17: divide by17
 * . . .
 * 42: divide by 42
 * 43~:invalid
 */
#define PLLCTLV2_PLL_MFI_MFI_MASK (0x7FU)
#define PLLCTLV2_PLL_MFI_MFI_SHIFT (0U)
#define PLLCTLV2_PLL_MFI_MFI_SET(x) (((uint32_t)(x) << PLLCTLV2_PLL_MFI_MFI_SHIFT) & PLLCTLV2_PLL_MFI_MFI_MASK)
#define PLLCTLV2_PLL_MFI_MFI_GET(x) (((uint32_t)(x) & PLLCTLV2_PLL_MFI_MFI_MASK) >> PLLCTLV2_PLL_MFI_MFI_SHIFT)

/* Bitfield definition for register of struct array PLL: MFN */
/*
 * MFN (RW)
 *
 * Numeratorof fractional part,f=fref*(mfi + mfn/mfd). This field supports changing while running.
 */
#define PLLCTLV2_PLL_MFN_MFN_MASK (0x3FFFFFFFUL)
#define PLLCTLV2_PLL_MFN_MFN_SHIFT (0U)
#define PLLCTLV2_PLL_MFN_MFN_SET(x) (((uint32_t)(x) << PLLCTLV2_PLL_MFN_MFN_SHIFT) & PLLCTLV2_PLL_MFN_MFN_MASK)
#define PLLCTLV2_PLL_MFN_MFN_GET(x) (((uint32_t)(x) & PLLCTLV2_PLL_MFN_MFN_MASK) >> PLLCTLV2_PLL_MFN_MFN_SHIFT)

/* Bitfield definition for register of struct array PLL: MFD */
/*
 * MFD (RW)
 *
 * Demoninator of fraction part,f=fref*(mfi + mfn/mfd).  This field should not be changed during PLL enabled.  If changed, change will take efftect when PLL re-enabled.
 */
#define PLLCTLV2_PLL_MFD_MFD_MASK (0x3FFFFFFFUL)
#define PLLCTLV2_PLL_MFD_MFD_SHIFT (0U)
#define PLLCTLV2_PLL_MFD_MFD_SET(x) (((uint32_t)(x) << PLLCTLV2_PLL_MFD_MFD_SHIFT) & PLLCTLV2_PLL_MFD_MFD_MASK)
#define PLLCTLV2_PLL_MFD_MFD_GET(x) (((uint32_t)(x) & PLLCTLV2_PLL_MFD_MFD_MASK) >> PLLCTLV2_PLL_MFD_MFD_SHIFT)

/* Bitfield definition for register of struct array PLL: SS_STEP */
/*
 * STEP (RW)
 *
 * Step of spread spectrum modulator.
 * This register should not be changed during PLL and spread spectrum enabled.  If changed, new value will take effect when PLL disabled or spread spectrum disabled.
 */
#define PLLCTLV2_PLL_SS_STEP_STEP_MASK (0x3FFFFFFFUL)
#define PLLCTLV2_PLL_SS_STEP_STEP_SHIFT (0U)
#define PLLCTLV2_PLL_SS_STEP_STEP_SET(x) (((uint32_t)(x) << PLLCTLV2_PLL_SS_STEP_STEP_SHIFT) & PLLCTLV2_PLL_SS_STEP_STEP_MASK)
#define PLLCTLV2_PLL_SS_STEP_STEP_GET(x) (((uint32_t)(x) & PLLCTLV2_PLL_SS_STEP_STEP_MASK) >> PLLCTLV2_PLL_SS_STEP_STEP_SHIFT)

/* Bitfield definition for register of struct array PLL: SS_STOP */
/*
 * STOP (RW)
 *
 * Stop point of spread spectrum modulator
 * This register should not be changed during PLL and spread spectrum enabled.  If changed, new value will take effect when PLL disabled or spread spectrum disabled.
 */
#define PLLCTLV2_PLL_SS_STOP_STOP_MASK (0x3FFFFFFFUL)
#define PLLCTLV2_PLL_SS_STOP_STOP_SHIFT (0U)
#define PLLCTLV2_PLL_SS_STOP_STOP_SET(x) (((uint32_t)(x) << PLLCTLV2_PLL_SS_STOP_STOP_SHIFT) & PLLCTLV2_PLL_SS_STOP_STOP_MASK)
#define PLLCTLV2_PLL_SS_STOP_STOP_GET(x) (((uint32_t)(x) & PLLCTLV2_PLL_SS_STOP_STOP_MASK) >> PLLCTLV2_PLL_SS_STOP_STOP_SHIFT)

/* Bitfield definition for register of struct array PLL: CONFIG */
/*
 * SPREAD (RW)
 *
 * Enable spread spectrum function.  This field supports changing during PLL running.
 */
#define PLLCTLV2_PLL_CONFIG_SPREAD_MASK (0x100U)
#define PLLCTLV2_PLL_CONFIG_SPREAD_SHIFT (8U)
#define PLLCTLV2_PLL_CONFIG_SPREAD_SET(x) (((uint32_t)(x) << PLLCTLV2_PLL_CONFIG_SPREAD_SHIFT) & PLLCTLV2_PLL_CONFIG_SPREAD_MASK)
#define PLLCTLV2_PLL_CONFIG_SPREAD_GET(x) (((uint32_t)(x) & PLLCTLV2_PLL_CONFIG_SPREAD_MASK) >> PLLCTLV2_PLL_CONFIG_SPREAD_SHIFT)

/*
 * REFSEL (RW)
 *
 * Select reference clock, This filed support changing while running, but application must take frequency error and jitter into consideration.  And if MFN changed before reference switch, application need make sure time is enough for MFN updating.
 * 0: XTAL24M
 * 1: IRC24M
 */
#define PLLCTLV2_PLL_CONFIG_REFSEL_MASK (0x1U)
#define PLLCTLV2_PLL_CONFIG_REFSEL_SHIFT (0U)
#define PLLCTLV2_PLL_CONFIG_REFSEL_SET(x) (((uint32_t)(x) << PLLCTLV2_PLL_CONFIG_REFSEL_SHIFT) & PLLCTLV2_PLL_CONFIG_REFSEL_MASK)
#define PLLCTLV2_PLL_CONFIG_REFSEL_GET(x) (((uint32_t)(x) & PLLCTLV2_PLL_CONFIG_REFSEL_MASK) >> PLLCTLV2_PLL_CONFIG_REFSEL_SHIFT)

/* Bitfield definition for register of struct array PLL: LOCKTIME */
/*
 * LOCKTIME (RW)
 *
 * Lock time of PLL in 24M clock cycles, typical value is 2500.  If MFI changed during PLL startup, PLL lock time may be longer than this setting.
 */
#define PLLCTLV2_PLL_LOCKTIME_LOCKTIME_MASK (0xFFFFU)
#define PLLCTLV2_PLL_LOCKTIME_LOCKTIME_SHIFT (0U)
#define PLLCTLV2_PLL_LOCKTIME_LOCKTIME_SET(x) (((uint32_t)(x) << PLLCTLV2_PLL_LOCKTIME_LOCKTIME_SHIFT) & PLLCTLV2_PLL_LOCKTIME_LOCKTIME_MASK)
#define PLLCTLV2_PLL_LOCKTIME_LOCKTIME_GET(x) (((uint32_t)(x) & PLLCTLV2_PLL_LOCKTIME_LOCKTIME_MASK) >> PLLCTLV2_PLL_LOCKTIME_LOCKTIME_SHIFT)

/* Bitfield definition for register of struct array PLL: STEPTIME */
/*
 * STEPTIME (RW)
 *
 * Step time for MFI on-the-fly change in 24M clock cycles, typical value is 2500.
 */
#define PLLCTLV2_PLL_STEPTIME_STEPTIME_MASK (0xFFFFU)
#define PLLCTLV2_PLL_STEPTIME_STEPTIME_SHIFT (0U)
#define PLLCTLV2_PLL_STEPTIME_STEPTIME_SET(x) (((uint32_t)(x) << PLLCTLV2_PLL_STEPTIME_STEPTIME_SHIFT) & PLLCTLV2_PLL_STEPTIME_STEPTIME_MASK)
#define PLLCTLV2_PLL_STEPTIME_STEPTIME_GET(x) (((uint32_t)(x) & PLLCTLV2_PLL_STEPTIME_STEPTIME_MASK) >> PLLCTLV2_PLL_STEPTIME_STEPTIME_SHIFT)

/* Bitfield definition for register of struct array PLL: ADVANCED */
/*
 * SLOW (RW)
 *
 * Use slow lock flow, PLL lock expendite is disabled.  This mode might be stabler. And software need config LOCKTIME field accordingly.
 * 0: fast lock enabled, lock time is 100us
 * 1: fast lock disabled, lock time is 400us
 */
#define PLLCTLV2_PLL_ADVANCED_SLOW_MASK (0x10000000UL)
#define PLLCTLV2_PLL_ADVANCED_SLOW_SHIFT (28U)
#define PLLCTLV2_PLL_ADVANCED_SLOW_SET(x) (((uint32_t)(x) << PLLCTLV2_PLL_ADVANCED_SLOW_SHIFT) & PLLCTLV2_PLL_ADVANCED_SLOW_MASK)
#define PLLCTLV2_PLL_ADVANCED_SLOW_GET(x) (((uint32_t)(x) & PLLCTLV2_PLL_ADVANCED_SLOW_MASK) >> PLLCTLV2_PLL_ADVANCED_SLOW_SHIFT)

/*
 * DITHER (RW)
 *
 * Enable dither function
 */
#define PLLCTLV2_PLL_ADVANCED_DITHER_MASK (0x1000000UL)
#define PLLCTLV2_PLL_ADVANCED_DITHER_SHIFT (24U)
#define PLLCTLV2_PLL_ADVANCED_DITHER_SET(x) (((uint32_t)(x) << PLLCTLV2_PLL_ADVANCED_DITHER_SHIFT) & PLLCTLV2_PLL_ADVANCED_DITHER_MASK)
#define PLLCTLV2_PLL_ADVANCED_DITHER_GET(x) (((uint32_t)(x) & PLLCTLV2_PLL_ADVANCED_DITHER_MASK) >> PLLCTLV2_PLL_ADVANCED_DITHER_SHIFT)

/* Bitfield definition for register of struct array PLL: DIV0 */
/*
 * BUSY (RO)
 *
 * Busy flag
 * 0: divider is working
 * 1: divider is changing status
 */
#define PLLCTLV2_PLL_DIV_BUSY_MASK (0x80000000UL)
#define PLLCTLV2_PLL_DIV_BUSY_SHIFT (31U)
#define PLLCTLV2_PLL_DIV_BUSY_GET(x) (((uint32_t)(x) & PLLCTLV2_PLL_DIV_BUSY_MASK) >> PLLCTLV2_PLL_DIV_BUSY_SHIFT)

/*
 * RESPONSE (RO)
 *
 * Divider response status
 * 0: Divider is not stable
 * 1: Divider is stable for use
 */
#define PLLCTLV2_PLL_DIV_RESPONSE_MASK (0x20000000UL)
#define PLLCTLV2_PLL_DIV_RESPONSE_SHIFT (29U)
#define PLLCTLV2_PLL_DIV_RESPONSE_GET(x) (((uint32_t)(x) & PLLCTLV2_PLL_DIV_RESPONSE_MASK) >> PLLCTLV2_PLL_DIV_RESPONSE_SHIFT)

/*
 * ENABLE (RO)
 *
 * Divider enable status
 * 0: Divider is off
 * 1: Divider is on
 */
#define PLLCTLV2_PLL_DIV_ENABLE_MASK (0x10000000UL)
#define PLLCTLV2_PLL_DIV_ENABLE_SHIFT (28U)
#define PLLCTLV2_PLL_DIV_ENABLE_GET(x) (((uint32_t)(x) & PLLCTLV2_PLL_DIV_ENABLE_MASK) >> PLLCTLV2_PLL_DIV_ENABLE_SHIFT)

/*
 * DIV (RW)
 *
 * Divider factor, divider factor is DIV/5 + 1
 * 0: divide by 1
 * 1: divide by 1.2
 * 2: divide by 1.4
 * . . .
 * 63: divide by 13.6
 */
#define PLLCTLV2_PLL_DIV_DIV_MASK (0x3FU)
#define PLLCTLV2_PLL_DIV_DIV_SHIFT (0U)
#define PLLCTLV2_PLL_DIV_DIV_SET(x) (((uint32_t)(x) << PLLCTLV2_PLL_DIV_DIV_SHIFT) & PLLCTLV2_PLL_DIV_DIV_MASK)
#define PLLCTLV2_PLL_DIV_DIV_GET(x) (((uint32_t)(x) & PLLCTLV2_PLL_DIV_DIV_MASK) >> PLLCTLV2_PLL_DIV_DIV_SHIFT)



/* DIV register group index macro definition */
#define PLLCTLV2_PLL_DIV_DIV0 (0UL)
#define PLLCTLV2_PLL_DIV_DIV1 (1UL)
#define PLLCTLV2_PLL_DIV_DIV2 (2UL)

/* PLL register group index macro definition */
#define PLLCTLV2_PLL_PLL0 (0UL)
#define PLLCTLV2_PLL_PLL1 (1UL)
#define PLLCTLV2_PLL_PLL2 (2UL)


#endif /* HPM_PLLCTLV2_H */
