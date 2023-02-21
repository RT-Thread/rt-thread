/*
 * Copyright 2020, NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_POWER_H_
#define _FSL_POWER_H_

#include <stdint.h>
#include "fsl_common.h"
#include "fsl_device_registers.h"

/*!
 * @addtogroup power
 * @{
 */
/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @name Driver version */
/*@{*/
/*! @brief power driver version 1.0.0. */
#define FSL_POWER_DRIVER_VERSION (MAKE_VERSION(1, 0, 0))
/*@}*/

/**
 * @brief Low Power Modes configuration
 */
typedef enum _power_mode_config
{
    kPmu_Sleep          = 0U,
    kPmu_Deep_Sleep     = 1U,
    kPmu_PowerDown      = 2U,
    kPmu_Deep_PowerDown = 3U,
} power_mode_cfg_t;

/**
 * @brief Device Reset Causes
 */
typedef enum _power_reset_cause
{
    kRESET_CAUSE_POR            = 0UL, /*!< Power On Reset */
    kRESET_CAUSE_PADRESET       = 1UL, /*!< Hardware Pin Reset */
    kRESET_CAUSE_BODRESET       = 2UL, /*!< Brown-out Detector reset (either BODVBAT or BODCORE) */
    kRESET_CAUSE_ARMSYSTEMRESET = 3UL, /*!< ARM System Reset */
    kRESET_CAUSE_WDTRESET       = 4UL, /*!< Watchdog Timer Reset */
    kRESET_CAUSE_SWRRESET       = 5UL, /*!< Software Reset */
    kRESET_CAUSE_CDOGRESET      = 6UL, /*!< Code Watchdog Reset */
    /* Reset causes in DEEP-POWER-DOWN low power mode */
    kRESET_CAUSE_DPDRESET_WAKEUPIO = 7UL, /*!< Any of the 5 wake-up pins */
    kRESET_CAUSE_DPDRESET_RTC      = 8UL, /*!< Real Time Clock (RTC) */
    kRESET_CAUSE_DPDRESET_OSTIMER  = 9UL, /*!< OS Event Timer (OSTIMER) */
    kRESET_CAUSE_DPDRESET_WAKEUPIO_RTC =
        10UL, /*!< Any of the 5 wake-up pins and RTC (the 2 events occured within 1 nano-second of each other) */
    kRESET_CAUSE_DPDRESET_WAKEUPIO_OSTIMER =
        11UL, /*!< Any of the 5 wake-up pins and OSTIMER (the 2 events occured within 1 nano-second of each other) */
    kRESET_CAUSE_DPDRESET_RTC_OSTIMER =
        12UL, /*!< Real Time Clock or OS Event Timer (the 2 events occured within 1 nano-second of each other) */
    kRESET_CAUSE_DPDRESET_WAKEUPIO_RTC_OSTIMER = 13UL, /*!< Any of the 5 wake-up pins or RTC or OS Event Timer (the 3
                                                          events occured within 1 nano-second of each other) */
    /* Miscallenous */
    kRESET_CAUSE_NOT_RELEVANT =
        14UL, /*!< No reset cause (for example, this code is used when waking up from DEEP-SLEEP low power mode) */
    kRESET_CAUSE_NOT_DETERMINISTIC = 15UL, /*!< Unknown Reset Cause. Should be treated like "Hardware Pin Reset" from an
                                              application point of view. */
} power_reset_cause_t;

/**
 * @brief Device Boot Modes
 */
typedef enum _power_boot_mode
{
    kBOOT_MODE_POWER_UP =
        0UL, /*!< All non Low Power Mode wake up (Power On Reset, Pin Reset, BoD Reset, ARM System Reset ... ) */
    kBOOT_MODE_LP_DEEP_SLEEP      = 1UL, /*!< Wake up from DEEP-SLEEP Low Power mode */
    kBOOT_MODE_LP_POWER_DOWN      = 2UL, /*!< Wake up from POWER-DOWN Low Power mode */
    kBOOT_MODE_LP_DEEP_POWER_DOWN = 4UL, /*!< Wake up from DEEP-POWER-DOWN Low Power mode */
} power_boot_mode_t;

/**
 * @brief Device wake up pins events
 */
typedef enum _power_wakeup_pin_t
{
    kWAKEUP_PIN_NONE     = 0UL,        /*!< No wake up pin event */
    kWAKEUP_PIN_0        = (1UL << 0), /*!< Wake up pin 0 event */
    kWAKEUP_PIN_1        = (1UL << 1), /*!< Wake up pin 1 event */
    kWAKEUP_PIN_2        = (1UL << 2), /*!< Wake up pin 2 event */
    kWAKEUP_PIN_3        = (1UL << 3), /*!< Wake up pin 3 event */
    kWAKEUP_PIN_4        = (1UL << 4), /*!< Wake up pin 4 event */
    kWAKEUP_PIN_MULTIPLE = 0x1FUL, /*!< More than 1 wake up pins events occured (within 1 nano-second of each other) */
} power_wakeup_pin_t;

/**
 * @brief analog components power modes control during low power modes
 */
typedef enum _power_pd_bit
{
    /* Power Down Vector 0 */
    kPDRUNCFG_PD_DCDC       = (1UL << 0),
    kPDRUNCFG_PD_BIAS       = (1UL << 1),
    kPDRUNCFG_PD_BODCORE    = (1UL << 2),
    kPDRUNCFG_PD_BODVDDMAIN = (1UL << 3),
    kPDRUNCFG_PD_FRO1M      = (1UL << 4),
    kPDRUNCFG_PD_FRO192M    = (1UL << 5),
    kPDRUNCFG_PD_FRO32K     = (1UL << 6),
    kPDRUNCFG_PD_XTAL32K    = (1UL << 7),
    kPDRUNCFG_PD_XTALHF     = (1UL << 8),
    kPDRUNCFG_PD_PLL0       = (1UL << 9),
    kPDRUNCFG_PD_PLL1       = (1UL << 10),
    kPDRUNCFG_PD_USBFSPHY   = (1UL << 11),
    // kPDRUNCFG_PD_          = (1UL << 12), /*!< RESERVED */
    kPDRUNCFG_PD_COMP = (1UL << 13),
    // kPDRUNCFG_PD_          = (1UL << 14), /*!< RESERVED */
    // kPDRUNCFG_PD_          = (1UL << 15), /*!< RESERVED */
    kPDRUNCFG_PD_LDOMEM = (1UL << 16),
    // kPDRUNCFG_PD_          = (1UL << 17), /*!< RESERVED */
    kPDRUNCFG_PD_LDOEFUSEPROG = (1UL << 18),
    // kPDRUNCFG_PD_          = (1UL << 19), /*!< RESERVED */
    kPDRUNCFG_PD_LDOXTALHF  = (1UL << 20),
    kPDRUNCFG_PD_LDOFLASHNV = (1UL << 21),
    // kPDRUNCFG_PD_          = (1UL << 22), /*!< RESERVED */
    kPDRUNCFG_PD_PLL0_SSCG = (1UL << 23),
    kPDRUNCFG_PD_ROM       = (1UL << 24),
    kPDRUNCFG_PD_HSCMP0    = (1UL << 25),
    kPDRUNCFG_PD_HSCMP1    = (1UL << 26),
    kPDRUNCFG_PD_HSCMP2    = (1UL << 27),
    kPDRUNCFG_PD_OPAMP0    = (1UL << 28),
    kPDRUNCFG_PD_OPAMP1    = (1UL << 29),
    kPDRUNCFG_PD_OPAMP2    = (1UL << 30),
    kPDRUNCFG_PD_VREF      = (1UL << 31),

    /* Power Down Vector 1 */
    kPDRUNCFG_PD_CMPBIAS    = (1UL << 0) | (1UL << 31),
    kPDRUNCFG_PD_HSCMP0_DAC = (1UL << 1) | (1UL << 31),
    kPDRUNCFG_PD_HSCMP1_DAC = (1UL << 2) | (1UL << 31),
    kPDRUNCFG_PD_HSCMP2_DAC = (1UL << 3) | (1UL << 31),
    kPDRUNCFG_PD_DAC0       = (1UL << 4) | (1UL << 31),
    kPDRUNCFG_PD_DAC1       = (1UL << 5) | (1UL << 31),
    kPDRUNCFG_PD_DAC2       = (1UL << 6) | (1UL << 31),
    kPDRUNCFG_STOP_DAC0     = (1UL << 7) | (1UL << 31),
    kPDRUNCFG_STOP_DAC1     = (1UL << 8) | (1UL << 31),
    kPDRUNCFG_STOP_DAC2     = (1UL << 9) | (1UL << 31),

    /*
       This enum member has no practical meaning,it is used to avoid MISRA issue,
       user should not trying to use it.
       */
    kPDRUNCFG_ForceUnsigned = 0x80000000U,
} pd_bit_t;

/**
 * @brief SRAM instances bit masks
 */
typedef enum _power_sram_bit
{
    kPOWER_SRAM_RAM_X0        = (1UL << 0),  /*!< RAM_X0 */
    kPOWER_SRAM_RAM_00        = (1UL << 1),  /*!< RAM_00 */
    kPOWER_SRAM_RAM_01        = (1UL << 2),  /*!< RAM_01 */
    kPOWER_SRAM_RAM_02        = (1UL << 3),  /*!< RAM_02 */
    kPOWER_SRAM_RAM_03        = (1UL << 4),  /*!< RAM_03 */
    kPOWER_SRAM_RAM_10        = (1UL << 5),  /*!< RAM_10 */
    kPOWER_SRAM_RAM_20        = (1UL << 6),  /*!< RAM_20 */
    kPOWER_SRAM_RAM_30        = (1UL << 7),  /*!< RAM_30 */
    kPOWER_SRAM_RAM_40        = (1UL << 8),  /*!< RAM_40 */
    kPOWER_SRAM_RAM_41        = (1UL << 9),  /*!< RAM_41 */
    kPOWER_SRAM_RAM_42        = (1UL << 10), /*!< RAM_42 */
    kPOWER_SRAM_RAM_43        = (1UL << 11), /*!< RAM_43 */
    kPOWER_SRAM_FLASHCACHE    = (1UL << 12), /*!< Reserved. Flash Cache SRAM instance */
    kPOWER_SRAM_FLEXSPICACHE  = (1UL << 13), /*!< Reserved. FlexSPI Cache SRAM instance */
    kPOWER_SRAM_FLEXSPIH2PREG = (1UL << 14), /*!< Reserved. FlexSPI Dual Port Register Files instances */

    kPOWER_SRAM_DSLP_MASK = 0x7FFFUL, /*!< Reserved. DEEP-SLEEP SRAM instances */
    kPOWER_SRAM_PDWN_MASK = 0xFFFUL,  /*!< Reserved. POWER-DOWN SRAM instances */

#if (defined(LPC55S36_SERIES) || defined(LPC5536_SERIES) || defined(LPC5534_SERIES))
    kPOWER_SRAM_DPWD_MASK = 0xFE6UL, /*!< Reserved. DEEP-POWER-DOWN SRAM instances (RAM_X0, RAM_02 and RAM_03 excluded:
                                        they are used by ROM Boot code) */
#else
    kPOWER_SRAM_DPWD_MASK = 0xF3FUL, /*!< Reserved. DEEP-POWER-DOWN SRAM instances (RAM_20 & RAM_30 excluded).*/
#endif

    /*
       This enum member has no practical meaning,it is used to avoid MISRA issue,
       user should not trying to use it.
       */
    kPOWER_SRAM_ForceUnsigned = 0x80000000U,
} power_sram_bit_t;

/**
 * @brief SRAM instances indexes
 */
typedef enum _power_sram_index
{
    kPOWER_SRAM_IDX_RAM_X0        = 0UL,  /*!< RAM_X0 */
    kPOWER_SRAM_IDX_RAM_00        = 1UL,  /*!< RAM_00 */
    kPOWER_SRAM_IDX_RAM_01        = 2UL,  /*!< RAM_01 */
    kPOWER_SRAM_IDX_RAM_02        = 3UL,  /*!< RAM_02 */
    kPOWER_SRAM_IDX_RAM_03        = 4UL,  /*!< RAM_03 */
    kPOWER_SRAM_IDX_RAM_10        = 5UL,  /*!< RAM_10 */
    kPOWER_SRAM_IDX_RAM_20        = 6UL,  /*!< RAM_20 */
    kPOWER_SRAM_IDX_RAM_30        = 7UL,  /*!< RAM_30 */
    kPOWER_SRAM_IDX_RAM_40        = 8UL,  /*!< RAM_40 */
    kPOWER_SRAM_IDX_RAM_41        = 9UL,  /*!< RAM_41 */
    kPOWER_SRAM_IDX_RAM_42        = 10UL, /*!< RAM_42 */
    kPOWER_SRAM_IDX_RAM_43        = 11UL, /*!< RAM_43 */
    kPOWER_SRAM_IDX_FLASHCACHE    = 12UL, /*!< Reserved. Flash Cache SRAM instance */
    kPOWER_SRAM_IDX_FLEXSPICACHE  = 13UL, /*!< Reserved. FlexSPI Cache SRAM instance */
    kPOWER_SRAM_IDX_FLEXSPIH2PREG = 14UL, /*!< Reserved. FlexSPI Dual Port Register Files instances */
} power_sram_index_t;

/*@brief SRAM Power Mode */
typedef enum _power_sram_pwr_mode
{
    kPOWER_SRAMPwrActive     = 0U, /*!< Active */
    kPOWER_SRAMPwrLightSleep = 1U, /*!< RESERVED, DO NOT USE (Light Sleep) */
    kPOWER_SRAMPwrDeepSleep  = 2U, /*!< Deep Sleep : SRAM content retained */
    kPOWER_SRAMPwrShutDown   = 3U, /*!< Shutdown: SRAM content lost */
} power_sram_pwr_mode_t;

/*@brief BOD VDDMAIN level */
typedef enum _power_bod_vddmain_level
{
    kPOWER_BodVddmainLevel1000mv = 0,  /*!< VDDMAIN Brown out detector level 1V */
    kPOWER_BodVddmainLevel1100mv = 1,  /*!< VDDMAIN Brown out detector level 1.1V */
    kPOWER_BodVddmainLevel1200mv = 2,  /*!< VDDMAIN Brown out detector level 1.2V */
    kPOWER_BodVddmainLevel1300mv = 3,  /*!< VDDMAIN Brown out detector level 1.3V */
    kPOWER_BodVddmainLevel1400mv = 4,  /*!< VDDMAIN Brown out detector level 1.4V */
    kPOWER_BodVddmainLevel1500mv = 5,  /*!< VDDMAIN Brown out detector level 1.5V */
    kPOWER_BodVddmainLevel1600mv = 6,  /*!< VDDMAIN Brown out detector level 1.6V */
    kPOWER_BodVddmainLevel1650mv = 7,  /*!< VDDMAIN Brown out detector level 1.65V */
    kPOWER_BodVddmainLevel1700mv = 8,  /*!< VDDMAIN Brown out detector level 1.7V */
    kPOWER_BodVddmainLevel1750mv = 9,  /*!< VDDMAIN Brown out detector level 1.75V */
    kPOWER_BodVddmainLevel1800mv = 10, /*!< VDDMAIN Brown out detector level 1.8V */
    kPOWER_BodVddmainLevel1900mv = 11, /*!< VDDMAIN Brown out detector level 1.9V */
    kPOWER_BodVddmainLevel2000mv = 12, /*!< VDDMAIN Brown out detector level 2V */
    kPOWER_BodVddmainLevel2100mv = 13, /*!< VDDMAIN Brown out detector level 2.1V */
    kPOWER_BodVddmainLevel2200mv = 14, /*!< VDDMAIN Brown out detector level 2.2V */
    kPOWER_BodVddmainLevel2300mv = 15, /*!< VDDMAIN Brown out detector level 2.3V */
    kPOWER_BodVddmainLevel2400mv = 16, /*!< VDDMAIN Brown out detector level 2.4V */
    kPOWER_BodVddmainLevel2500mv = 17, /*!< VDDMAIN Brown out detector level 2.5V */
    kPOWER_BodVddmainLevel2600mv = 18, /*!< VDDMAIN Brown out detector level 2.6V */
    kPOWER_BodVddmainLevel2700mv = 19, /*!< VDDMAIN Brown out detector level 2.7V */
    kPOWER_BodVddmainLevel2800mv = 20, /*!< VDDMAIN Brown out detector level 2.80 V */
    kPOWER_BodVddmainLevel2900mv = 21, /*!< VDDMAIN Brown out detector level 2.9V */
    kPOWER_BodVddmainLevel3000mv = 22, /*!< VDDMAIN Brown out detector level 3.0V */
    kPOWER_BodVddmainLevel3100mv = 23, /*!< VDDMAIN Brown out detector level 3.1V */
    kPOWER_BodVddmainLevel3200mv = 24, /*!< VDDMAIN Brown out detector level 3.2V */
    kPOWER_BodVddmainLevel3300mv = 25, /*!< VDDMAIN Brown out detector level 3.3V */
} power_bod_vddmain_level_t;

/*@brief BOD core level */
typedef enum _power_bod_core_level
{
    kPOWER_BodCoreLevel600mv = 0, /*!< core Brown out detector level 600mV */
    kPOWER_BodCoreLevel650mv = 1, /*!< core Brown out detector level 650mV */
    kPOWER_BodCoreLevel700mv = 2, /*!< core Brown out detector level 700mV */
    kPOWER_BodCoreLevel750mv = 3, /*!< core Brown out detector level 750mV */
    kPOWER_BodCoreLevel800mv = 4, /*!< core Brown out detector level 800mV */
    kPOWER_BodCoreLevel850mv = 5, /*!< core Brown out detector level 850mV */
    kPOWER_BodCoreLevel900mv = 6, /*!< core Brown out detector level 900mV */
    kPOWER_BodCoreLevel950mv = 7, /*!< core Brown out detector level 950mV */
} power_bod_core_level_t;

/*@brief BODs (VDDMAIN & Core) Hysteresis control */
typedef enum _power_bod_hyst
{
    kPOWER_BodHystLevel25mv  = 0U, /*!< BOD Hysteresis control level 25mv */
    kPOWER_BodHystLevel50mv  = 1U, /*!< BOD Hysteresis control level 50mv */
    kPOWER_BodHystLevel75mv  = 2U, /*!< BOD Hysteresis control level 75mv */
    kPOWER_BodHystLevel100mv = 3U, /*!< BOD Hysteresis control level 100mv */
} power_bod_hyst_t;

/*@brief Core Power Source */
typedef enum _power_core_pwr_source
{
    kPOWER_CoreSrcDCDC      = 0U, /*!< DCDC */
    kPOWER_CoreSrcLDOCoreHP = 1U, /*!< LDO Core High Power Mode */
    kPOWER_CoreSrcLDOCoreLP = 2U, /*!< LDO Core Low Power Mode (DO NOT USE : Reserved for test purposes) */
    kPOWER_CoreSrcExternal  = 3U, /*!< External (DO NOT USE : Reserved for test purposes) */
} power_core_pwr_source_t;

/*@brief Core Regulators Power State */
typedef enum _power_core_pwr_state
{
    kPOWER_CorePwrDisable = 0U, /*!< Disable */
    kPOWER_CorePwrEnable  = 1U, /*!< Enable */
} power_core_pwr_state_t;

/*@brief Generic Power Library APIs Status codes */
typedef enum _power_status
{
    kPOWER_Status_Success = 0U, /*!< OK */
    kPOWER_Status_Fail    = 1U, /*!< Generic error code */
} power_status_t;

/**
 * @brief Low Power Modes Wake up sources
 */
/* Wake up source vector 0 */
#define WAKEUP_SYS              (1UL << 0) /*!< [SLEEP, DEEP SLEEP                             ] */ /* WWDT0_IRQ and BOD_IRQ*/
#define WAKEUP_SDMA0            (1UL << 1)  /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_GPIO_GLOBALINT0  (1UL << 2)  /*!< [SLEEP, DEEP SLEEP, POWER DOWN                 ] */
#define WAKEUP_GPIO_GLOBALINT1  (1UL << 3)  /*!< [SLEEP, DEEP SLEEP, POWER DOWN                 ] */
#define WAKEUP_GPIO_INT0_0      (1UL << 4)  /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_GPIO_INT0_1      (1UL << 5)  /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_GPIO_INT0_2      (1UL << 6)  /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_GPIO_INT0_3      (1UL << 7)  /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_UTICK            (1UL << 8)  /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_MRT              (1UL << 9)  /*!< [SLEEP,                                        ] */
#define WAKEUP_CTIMER0          (1UL << 10) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_CTIMER1          (1UL << 11) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_SCT              (1UL << 12) /*!< [SLEEP,                                        ] */
#define WAKEUP_CTIMER3          (1UL << 13) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_FLEXCOMM0        (1UL << 14) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_FLEXCOMM1        (1UL << 15) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_FLEXCOMM2        (1UL << 16) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_FLEXCOMM3        (1UL << 17) /*!< [SLEEP, DEEP SLEEP, POWER DOWN                 ] */
#define WAKEUP_FLEXCOMM4        (1UL << 18) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_FLEXCOMM5        (1UL << 19) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_FLEXCOMM6        (1UL << 20) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_FLEXCOMM7        (1UL << 21) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_ADC0             (1UL << 22) /*!< [SLEEP,                                        ] */
#define WAKEUP_ADC1             (1UL << 23) /*!< [SLEEP,                                        ] */
#define WAKEUP_ACMP             (1UL << 24) /*!< [SLEEP, DEEP SLEEP, POWER DOWN                 ] */
#define WAKEUP_DMIC             (1UL << 25) /*!< [SLEEP,                                        ] */
#define WAKEUP_HWVAD            (1UL << 26) /*!< [SLEEP, DEEP SLEEP,                            ] */
#define WAKEUP_USB0_NEEDCLK     (1UL << 27) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_USB0             (1UL << 28) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_RTC_ALARM_WAKEUP (1UL << 29) /*!< [SLEEP, DEEP SLEEP, POWER DOWN, DEEP POWER DOWN] */
#define WAKEUP_EZH_ARCH_B       (1UL << 30) /*!< [SLEEP,                                        ] */
#define WAKEUP_WAKEUP_MAILBOX   (1UL << 31) /*!< [SLEEP, DEEP SLEEP,                            ] */

/* Wake up source vector 1 */
#define WAKEUP_GPIO_INT0_4    (1UL << 0) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_GPIO_INT0_5    (1UL << 1) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_GPIO_INT0_6    (1UL << 2) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_GPIO_INT0_7    (1UL << 3) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_CTIMER2        (1UL << 4) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_CTIMER4        (1UL << 5) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_OS_EVENT_TIMER (1UL << 6) /*!< [SLEEP, DEEP SLEEP, POWER DOWN, DEEP POWER DOWN] */
#define WAKEUP_FLEXSPI        (1UL << 7) /*!< [SLEEP,                                        ] */
// reserved                        (1UL << 8)
// reserved                        (1UL << 9)
// reserved                        (1UL << 10)
#define WAKEUP_CAN0_0    (1UL << 11) /*!< [SLEEP,                                        ] */
#define WAKEUP_CAN0_1    (1UL << 12) /*!< [SLEEP,                                        ] */
#define WAKEUP_SPIFILTER (1UL << 13) /*!< [SLEEP,                                        ] */
// reserved                        (1UL << 14)
// reserved                        (1UL << 15)
// reserved                        (1UL << 16)
#define WAKEUP_SEC_HYPERVISOR_CALL (1UL << 17) /*!< [SLEEP,                                        ] */
#define WAKEUP_SEC_GPIO_INT0_0     (1UL << 18) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_SEC_GPIO_INT0_1     (1UL << 19) /*!< [SLEEP, DEEP SLEEP                             ] */
// reserved                        (1UL << 20)
#define WAKEUP_SEC_VIO  (1UL << 21) /*!< [SLEEP,                                        ] */
#define WAKEUP_CSS_IRQ0 (1UL << 22) /*!< [SLEEP,                                        ] */
#define WAKEUP_PKC      (1UL << 23) /*!< [SLEEP,                                        ] */
#define WAKEUP_PUF      (1UL << 24) /*!< [SLEEP,                                        ] */
#define WAKEUP_PQ       (1UL << 25) /*!< [SLEEP,                                        ] */
#define WAKEUP_SDMA1    (1UL << 26) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_LSPI_HS  (1UL << 27) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_CODE_WDG (1UL << 28) /*!< [SLEEP,                                        ] */
// reserved                        (1UL << 29)
#define WAKEUP_I3C (1UL << 30) /*!< [SLEEP, DEEP SLEEP                             ] */
// reserved                        (1UL << 31)

/* Wake up source vector 2 */
#define WAKEUP_NEUTRON  (1UL << 0) /*!< [SLEEP,                                        ] */
#define WAKEUP_CSS_IRQ1 (1UL << 1) /*!< [SLEEP,                                        ] */
// reserved                         (1UL << 2)
#define WAKEUP_ANA_GLITCH_DETECT (1UL << 3)
// reserved                        (1UL << 4)
// reserved                        (1UL << 5)
// reserved                        (1UL << 6)
// reserved                        (1UL << 7)
// reserved                        (1UL << 8)
// reserved                        (1UL << 9)
#define WAKEUP_DAC0                  (1UL << 10) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_DAC1                  (1UL << 11) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_DAC2                  (1UL << 12) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_HS_COMP0              (1UL << 13) /*!< [SLEEP,                                        ] */
#define WAKEUP_HS_COMP1              (1UL << 14) /*!< [SLEEP,                                        ] */
#define WAKEUP_HS_COMP2              (1UL << 15) /*!< [SLEEP,                                        ] */
#define WAKEUP_FLEXPWM0_CAPTURE      (1UL << 16) /*!< [SLEEP,                                        ] */
#define WAKEUP_FLEXPWM0_FAULT        (1UL << 17) /*!< [SLEEP,                                        ] */
#define WAKEUP_FLEXPWM0_RELOAD_ERROR (1UL << 18) /*!< [SLEEP,                                        ] */
#define WAKEUP_FLEXPWM0_COMPARE0     (1UL << 19) /*!< [SLEEP,                                        ] */
#define WAKEUP_FLEXPWM0_RELOAD0      (1UL << 20) /*!< [SLEEP,                                        ] */
#define WAKEUP_FLEXPWM0_COMPARE1     (1UL << 21) /*!< [SLEEP,                                        ] */
#define WAKEUP_FLEXPWM0_RELOAD1      (1UL << 22) /*!< [SLEEP,                                        ] */
#define WAKEUP_FLEXPWM0_COMPARE2     (1UL << 23) /*!< [SLEEP,                                        ] */
#define WAKEUP_FLEXPWM0_RELOAD2      (1UL << 24) /*!< [SLEEP,                                        ] */
#define WAKEUP_FLEXPWM0_COMPARE3     (1UL << 25) /*!< [SLEEP,                                        ] */
#define WAKEUP_FLEXPWM0_RELOAD3      (1UL << 26) /*!< [SLEEP,                                        ] */
#define WAKEUP_FLEXPWM1_CAPTURE      (1UL << 27) /*!< [SLEEP,                                        ] */
#define WAKEUP_FLEXPWM1_FAULT        (1UL << 28) /*!< [SLEEP,                                        ] */
#define WAKEUP_FLEXPWM1_RELOAD_ERROR (1UL << 29) /*!< [SLEEP,                                        ] */
#define WAKEUP_FLEXPWM1_COMPARE0     (1UL << 30) /*!< [SLEEP,                                        ] */
#define WAKEUP_FLEXPWM1_RELOAD0      (1UL << 31) /*!< [SLEEP,                                        ] */

/* Wake up source vector 3 */
#define WAKEUP_FLEXPWM1_COMPARE1 (1UL << 0)  /*!< [SLEEP,                                        ] */
#define WAKEUP_FLEXPWM1_RELOAD1  (1UL << 1)  /*!< [SLEEP,                                        ] */
#define WAKEUP_FLEXPWM1_COMPARE2 (1UL << 2)  /*!< [SLEEP,                                        ] */
#define WAKEUP_FLEXPWM1_RELOAD2  (1UL << 3)  /*!< [SLEEP,                                        ] */
#define WAKEUP_FLEXPWM1_COMPARE3 (1UL << 4)  /*!< [SLEEP,                                        ] */
#define WAKEUP_FLEXPWM1_RELOAD3  (1UL << 5)  /*!< [SLEEP,                                        ] */
#define WAKEUP_ENC0_COMPARE      (1UL << 6)  /*!< [SLEEP,                                        ] */
#define WAKEUP_ENC0_HOME         (1UL << 7)  /*!< [SLEEP,                                        ] */
#define WAKEUP_ENC0_WDG          (1UL << 8)  /*!< [SLEEP,                                        ] */
#define WAKEUP_ENC0_IDX          (1UL << 9)  /*!< [SLEEP,                                        ] */
#define WAKEUP_ENC1_COMPARE      (1UL << 10) /*!< [SLEEP,                                        ] */
#define WAKEUP_ENC1_HOME         (1UL << 11) /*!< [SLEEP,                                        ] */
#define WAKEUP_ENC1_WDG          (1UL << 12) /*!< [SLEEP,                                        ] */
#define WAKEUP_ENC1_IDX          (1UL << 13) /*!< [SLEEP,                                        ] */
#define WAKEUP_ITRC              (1UL << 14) /*!< [SLEEP, DEEP SLEEP, POWER DOWN                 ] */
#define WAKEUP_CF_DSP24L_IRQ0    (1UL << 15) /*!< [SLEEP,                                        ] */
#define WAKEUP_CF_DSP24L_IRQ1    (1UL << 16) /*!< [SLEEP,                                        ] */
#define WAKEUP_FTM0              (1UL << 17) /*!< [SLEEP,                                        ] */
// reserved                        (1UL << 18)
// reserved                        (1UL << 19)
// reserved                        (1UL << 20)
// reserved                        (1UL << 21)
// reserved                        (1UL << 22)
// reserved                        (1UL << 23)
// reserved                        (1UL << 24)
// reserved                        (1UL << 25)
// reserved                        (1UL << 26)
// reserved                        (1UL << 27)
// reserved                        (1UL << 28)
// reserved                        (1UL << 29)
// reserved                        (1UL << 30)
// reserved                        (1UL << 31)

/**
 * @brief Sleep Postpone (DEEP-SLEEP)
 */
#define LOWPOWER_HWWAKE_FORCED (1UL << 0) /*!< Force peripheral clocking to stay on during deep-sleep mode. */
#define LOWPOWER_HWWAKE_PERIPHERALS                                                                                \
    (1UL << 1) /*!< Wake for Flexcomms. Any Flexcomm FIFO reaching the level specified by its own TXLVL will cause \
                  peripheral clocking to wake up temporarily while the related status is asserted */
#define LOWPOWER_HWWAKE_DMIC                                                                                   \
    (1UL << 2) /*!< Wake for DMIC. DMIC being busy will cause peripheral clocking to remain running until DMIC \
                  completes. Used in conjonction with LOWPOWER_HWWAKE_PERIPHERALS */
#define LOWPOWER_HWWAKE_SDMA0                                                                                 \
    (1UL << 3) /*!< Wake for DMA0. DMA0 being busy will cause peripheral clocking to remain running until DMA \
                  completes. Used in conjonction with LOWPOWER_HWWAKE_PERIPHERALS or LOWPOWER_HWWAKE_DAC */
#define LOWPOWER_HWWAKE_SDMA1                                                                                 \
    (1UL << 5) /*!< Wake for DMA1. DMA0 being busy will cause peripheral clocking to remain running until DMA \
                  completes. Used in conjonction with LOWPOWER_HWWAKE_PERIPHERALS or LOWPOWER_HWWAKE_DAC */
#define LOWPOWER_HWWAKE_DAC                                                                                        \
    (1UL << 6) /*!< Wake for DAC0, DAC1, DAC2. Any DAC0/1/2 FIFO reaching the level specified by the configuration \
                 will generate an asynchronous SDMA0 request, and SDMA0 will wake up the bus                       \
                   clock temporarily to transfer data to DAC0/1/2.*/
#define LOWPOWER_HWWAKE_ENABLE_FRO192M                                                                                 \
    (1UL << 31) /*!< Need to be set if FRO192M is disable - via PDCTRL0 - in Deep Sleep mode and any of                \
                   LOWPOWER_HWWAKE_PERIPHERALS, LOWPOWER_HWWAKE_SDMA0, LOWPOWER_HWWAKE_SDMA1 or LOWPOWER_HWWAKE_DAC is \
                   set */

/**
 * @brief CPU State retention (POWER-DOWN)
 */
#define LOWPOWER_CPURETCTRL_ENA_DISABLE 0 /*!< In POWER DOWN mode, CPU Retention is disabled */
#define LOWPOWER_CPURETCTRL_ENA_ENABLE  1 /*!< In POWER DOWN mode, CPU Retention is enabled  */

/**
 * @brief Wake up I/O sources (DEEP POWER-DOWN)
 */
#define LOWPOWER_WAKEUPIOSRC_PIO0_INDEX 0 /*!< Pin P1( 1) */
#define LOWPOWER_WAKEUPIOSRC_PIO1_INDEX 2 /*!< Pin P0(28) */
#define LOWPOWER_WAKEUPIOSRC_PIO2_INDEX 4 /*!< Pin P1(18) */
#define LOWPOWER_WAKEUPIOSRC_PIO3_INDEX 6 /*!< Pin P1(30) */
#define LOWPOWER_WAKEUPIOSRC_PIO4_INDEX 8 /*!< Pin P0(26) */

#define LOWPOWER_WAKEUPIOSRC_DISABLE        0 /*!< Wake up is disable                      */
#define LOWPOWER_WAKEUPIOSRC_RISING         1 /*!< Wake up on rising edge                  */
#define LOWPOWER_WAKEUPIOSRC_FALLING        2 /*!< Wake up on falling edge                 */
#define LOWPOWER_WAKEUPIOSRC_RISING_FALLING 3 /*!< Wake up on both rising or falling edges */

#define LOWPOWER_WAKEUPIOSRC_PIO0MODE_INDEX 10 /*!< Pin P1( 1) */
#define LOWPOWER_WAKEUPIOSRC_PIO1MODE_INDEX 12 /*!< Pin P0(28) */
#define LOWPOWER_WAKEUPIOSRC_PIO2MODE_INDEX 14 /*!< Pin P1(18) */
#define LOWPOWER_WAKEUPIOSRC_PIO3MODE_INDEX 16 /*!< Pin P1(30) */
#define LOWPOWER_WAKEUPIOSRC_PIO4MODE_INDEX 18 /*!< Pin P0(26) */

#define LOWPOWER_WAKEUPIOSRC_IO_MODE_PLAIN    0 /*!< Wake up Pad is plain input */
#define LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLDOWN 1 /*!< Wake up Pad is pull-down   */
#define LOWPOWER_WAKEUPIOSRC_IO_MODE_PULLUP   2 /*!< Wake up Pad is pull-up     */
#define LOWPOWER_WAKEUPIOSRC_IO_MODE_REPEATER 3 /*!< Wake up Pad is in repeater */

#define LOWPOWER_WAKEUPIO_PIO0_DISABLEPULLUPDOWN_INDEX \
    20 /*!< Wake-up I/O 0 pull-up/down disable/enable control index */
#define LOWPOWER_WAKEUPIO_PIO1_DISABLEPULLUPDOWN_INDEX \
    21 /*!< Wake-up I/O 1 pull-up/down disable/enable control index */
#define LOWPOWER_WAKEUPIO_PIO2_DISABLEPULLUPDOWN_INDEX \
    22 /*!< Wake-up I/O 2 pull-up/down disable/enable control index */
#define LOWPOWER_WAKEUPIO_PIO3_DISABLEPULLUPDOWN_INDEX \
    23 /*!< Wake-up I/O 3 pull-up/down disable/enable control index */
#define LOWPOWER_WAKEUPIO_PIO4_DISABLEPULLUPDOWN_INDEX \
    24 /*!< Wake-up I/O 4 pull-up/down disable/enable control index */

#define LOWPOWER_WAKEUPIO_PIO0_DISABLEPULLUPDOWN_MASK \
    (1UL << LOWPOWER_WAKEUPIO_PIO0_DISABLEPULLUPDOWN_INDEX) /*!< Wake-up I/O 0 pull-up/down disable/enable mask */
#define LOWPOWER_WAKEUPIO_PIO1_DISABLEPULLUPDOWN_MASK \
    (1UL << LOWPOWER_WAKEUPIO_PIO1_DISABLEPULLUPDOWN_INDEX) /*!< Wake-up I/O 1 pull-up/down disable/enable mask */
#define LOWPOWER_WAKEUPIO_PIO2_DISABLEPULLUPDOWN_MASK \
    (1UL << LOWPOWER_WAKEUPIO_PIO2_DISABLEPULLUPDOWN_INDEX) /*!< Wake-up I/O 2 pull-up/down disable/enable mask */
#define LOWPOWER_WAKEUPIO_PIO3_DISABLEPULLUPDOWN_MASK \
    (1UL << LOWPOWER_WAKEUPIO_PIO3_DISABLEPULLUPDOWN_INDEX) /*!< Wake-up I/O 3 pull-up/down disable/enable mask */
#define LOWPOWER_WAKEUPIO_PIO4_DISABLEPULLUPDOWN_MASK \
    (1UL << LOWPOWER_WAKEUPIO_PIO4_DISABLEPULLUPDOWN_INDEX) /*!< Wake-up I/O 4 pull-up/down disable/enable mask */

#define LOWPOWER_WAKEUPIO_PIO0_PULLUPDOWN_INDEX 25 /*!< Wake-up I/O 0 pull-up/down configuration index */
#define LOWPOWER_WAKEUPIO_PIO1_PULLUPDOWN_INDEX 26 /*!< Wake-up I/O 1 pull-up/down configuration index */
#define LOWPOWER_WAKEUPIO_PIO2_PULLUPDOWN_INDEX 27 /*!< Wake-up I/O 2 pull-up/down configuration index */
#define LOWPOWER_WAKEUPIO_PIO3_PULLUPDOWN_INDEX 28 /*!< Wake-up I/O 3 pull-up/down configuration index */
#define LOWPOWER_WAKEUPIO_PIO4_PULLUPDOWN_INDEX 29 /*!< Wake-up I/O 4 pull-up/down configuration index */

#define LOWPOWER_WAKEUPIO_PIO0_PULLUPDOWN_MASK \
    (1UL << LOWPOWER_WAKEUPIO_PIO0_PULLUPDOWN_INDEX) /*!< Wake-up I/O 0 pull-up/down mask */
#define LOWPOWER_WAKEUPIO_PIO1_PULLUPDOWN_MASK \
    (1UL << LOWPOWER_WAKEUPIO_PIO1_PULLUPDOWN_INDEX) /*!< Wake-up I/O 1 pull-up/down mask */
#define LOWPOWER_WAKEUPIO_PIO2_PULLUPDOWN_MASK \
    (1UL << LOWPOWER_WAKEUPIO_PIO2_PULLUPDOWN_INDEX) /*!< Wake-up I/O 2 pull-up/down mask */
#define LOWPOWER_WAKEUPIO_PIO3_PULLUPDOWN_MASK \
    (1UL << LOWPOWER_WAKEUPIO_PIO3_PULLUPDOWN_INDEX) /*!< Wake-up I/O 3 pull-up/down mask */
#define LOWPOWER_WAKEUPIO_PIO4_PULLUPDOWN_MASK \
    (1UL << LOWPOWER_WAKEUPIO_PIO4_PULLUPDOWN_INDEX) /*!< Wake-up I/O 4 pull-up/down mask */

#define LOWPOWER_WAKEUPIO_PULLDOWN 0 /*!< Select pull-down */
#define LOWPOWER_WAKEUPIO_PULLUP   1 /*!< Select pull-up   */

#define LOWPOWER_WAKEUPIO_CFG_SRC_IOCON                                                                      \
    0 /*!< Wake-up pins configuration (in/out, pull up/down plain input ...) is coming from IOCON (valid for \
         DEEP-SLEEP and POWER-DOWN) */
#define LOWPOWER_WAKEUPIO_CFG_SRC_PMC                                                                          \
    1 /*!< Wake-up pins configuration (in/out, pull up/down plain input ...) is coming from PMC and set up via \
           the second parameter (wakeup_io_ctrl) of POWER_SetWakeUpPins API (valid for DEEP-SLEEP and POWER-DOWN) */

#ifdef __cplusplus
extern "C" {
#endif
/*******************************************************************************
 * API
 ******************************************************************************/

/*!
 * @brief API to enable PDRUNCFG bit in the Syscon. Note that enabling the bit powers down the peripheral
 *
 * @param en    peripheral for which to enable the PDRUNCFG bit
 * @return none
 */
static inline void POWER_EnablePD(pd_bit_t en)
{
    if (((en & (1UL << 31)) != 0UL) && (en != (1UL << 31)))
    {
        /* PDRUNCFGSET1 */
        PMC->PDRUNCFGSET1 = (uint32_t)(en & ~(1UL << 31));
    }
    else
    {
        /* PDRUNCFGSET0 */
        PMC->PDRUNCFGSET0 = (uint32_t)en;
    }
}

/*!
 * @brief API to disable PDRUNCFG bit in the Syscon. Note that disabling the bit powers up the peripheral
 *
 * @param en    peripheral for which to disable the PDRUNCFG bit
 * @return none
 */
static inline void POWER_DisablePD(pd_bit_t en)
{
    if (((en & (1UL << 31)) != 0UL) && (en != (1UL << 31)))
    {
        /* PDRUNCFGCLR1 */
        PMC->PDRUNCFGCLR1 = (uint32_t)(en & ~(1UL << 31));
    }
    else
    {
        /* PDRUNCFGCLR0 */
        PMC->PDRUNCFGCLR0 = (uint32_t)en;
    }
}

/**
 * @brief   SoC Power Management Controller initialization
 * @return  power_status_t
 */
power_status_t POWER_PowerInit(void);

/**
 * @brief   Selects the core logic supply source
 * @param   pwr_source : Defines which regulator will be used to power the part core logic (internally)
 * @return  power_status_t
 */
power_status_t POWER_SetCorePowerSource(power_core_pwr_source_t pwr_source);

/**
 * @brief   Returns the current core logic supply source.
 * @return  power_core_pwr_source_t
 */
power_core_pwr_source_t POWER_GetCorePowerSource(void);

/**
 * @brief   Allows to control the state (enabled or disabled) of the core logic internal regulators (DCDC, LDO_CORE)
 * @param   pwr_source : Defines which regulator will be enabled or disabled
 * @param   pwr_state : Defines the state of the internal regulator indicated by pwr_source
 * @return  power_status_t
 */
power_status_t POWER_CorePowerSourceControl(power_core_pwr_source_t pwr_source, power_core_pwr_state_t pwr_state);

/**
 * @brief   Allows to configure SRAM instances (low) power modes when the part is in ACTIVE mode.
 * @param   sram_inst : Defines the SRAM instance(s) to be configured.
 * @param   pwr_mode : Defines the SRAM low power mode to be applied to all SRAM instances given by sram_inst
 * @return  power_status_t
 */
power_status_t POWER_SRAMPowerModeControl(power_sram_bit_t sram_inst, power_sram_pwr_mode_t pwr_mode);

/**
 * @brief
 * @param   p_sram_index :
 * @return  power_sram_pwr_mode_t
 */
power_sram_pwr_mode_t POWER_GetSRAMPowerMode(power_sram_index_t sram_index);

/**
 * @brief   Configures and enters in SLEEP low power mode
 * @return  Nothing
 */
void POWER_EnterSleep(void);

/**
 * @brief   Configures and enters in DEEP-SLEEP low power mode
 * @param   exclude_from_pd: defines which analog peripherals shall NOT be powered down (it is a 2 x 32-bit vectors,
 aligned with "pd_bit_t" definition)
 * @param   sram_retention_ctrl:defines which SRAM instances will be put in "retention" mode during deep-sleep (aligned
 with "power_sram_bit_t" definition)
 * @param   wakeup_interrupts: defines which peripheral interrupts can be a wake-up source during deep-sleep (it is a 4
 x 32-bit vectors, aligned with "WAKEUP_" #defines)
 * @param   hardware_wake_ctrl: configure DMA services during deep-sleep without waking up entire device (see
 "LOWPOWER_HWWAKE_*" #defines).

 * @return  Nothing
 *
 *          !!! IMPORTANT NOTES :
 *           1 - CPU & System CLock frequency is switched to FRO12MHz and is NOT restored back by the API.
 */
void POWER_EnterDeepSleep(uint32_t exclude_from_pd[2],
                          uint32_t sram_retention_ctrl,
                          uint32_t wakeup_interrupts[4],
                          uint32_t hardware_wake_ctrl);

/**
 * @brief   Configures and enters in POWERDOWN low power mode
 * @param   exclude_from_pd: defines which analog peripherals shall NOT be powered down (it is a 1 x 32-bit vector,
 aligned with "pd_bit_t" definition)
 * @param   sram_retention_ctrl:defines which SRAM instances will be put in "retention" mode during power-down (aligned
 with "power_sram_bit_t" definition)
 * @param   wakeup_interrupts: defines which peripheral interrupts can be a wake-up source during power-down (it is a 2
 x 32-bit vectors, aligned with "WAKEUP_" #defines)
 * @param   cpu_retention_addr: Must be:
             - Word aligned (address ending by 0x0, 0x4, 0x8 and 0xC).
             - Between 0x2000_0000 and 0x2000_09FC (inside RAM_00) or
             - Between 0x2000_1000 and 0x2000_19FC (inside RAM_01) or
             - Between 0x2000_2000 and 0x2000_29FC (inside RAM_02) or
             - Between 0x2000_3000 and 0x2000_39FC (inside RAM_03)
             - The CPU state will be stored in SRAM from "cpu_retention_addr" to "cpu_retention_addr + 1540".
               Therefore, any data present in this area before calling the function will be lost.

 * @return  Nothing
 *
 *          !!! IMPORTANT NOTES :
 *           1 - CPU0 & System Clock frequency is switched to FRO12MHz and is NOT restored back by the API.
 *           2 - It is the responsability of the user to make sure that SRAM instance containing the application
 *               software stack and variables WILL BE preserved during low power (via parameter "sram_retention_ctrl")
 */
void POWER_EnterPowerDown(uint32_t exclude_from_pd[1],
                          uint32_t sram_retention_ctrl,
                          uint32_t wakeup_interrupts[4],
                          uint32_t cpu_retention_addr);

/**
 * @brief   Configures and enters in DEEPPOWERDOWN low power mode
 * @param   exclude_from_pd: defines which analog peripherals shall NOT be powered down (it is a 1 x 32-bit vector,
 aligned with "pd_bit_t" definition)
 * @param   sram_retention_ctrl: defines which SRAM instances will be put in "retention" mode during deep power-down
 (aligned with "power_sram_bit_t" definition)
 * @param   wakeup_interrupts: defines which peripheral interrupts can be a wake-up source during deep power-down (it is
 a 2 x 32-bit vectors, aligned with "WAKEUP_" #defines)
 * @param   wakeup_io_ctrl: configure the 5 wake-up pins that can wake-up the part from deep power-down mode (see
 "LOWPOWER_WAKEUPIOSRC_*" #defines)

 * @return  Nothing
 *
 *          !!! IMPORTANT NOTES :
 *           1 - CPU0 & System Clock frequency is switched to FRO12MHz and is NOT restored back by the API.
 *           2 - The HARD FAULT handler should execute from SRAM. (The Hard fault handler should initiate a full chip
 reset)
 */
void POWER_EnterDeepPowerDown(uint32_t exclude_from_pd[1],
                              uint32_t sram_retention_ctrl,
                              uint32_t wakeup_interrupts[2],
                              uint32_t wakeup_io_ctrl);

/**
 * @brief   Configures the 5 wake-up pins to wake up the part in DEEP-SLEEP and POWER-DOWN low power modes.
 * @param   wakeup_io_cfg_src : for all wake-up pins : indicates if the config is from IOCON (0) or from PMC (1).
 * @param   wakeup_io_ctrl: the 5 wake-up pins configurations (see "LOWPOWER_WAKEUPIOSRC_*" #defines)

 * @return  Nothing
 *
 *          !!! IMPORTANT NOTES :
 *           1 - To be called just before POWER_EnterDeepSleep() or POWER_EnterPowerDown().
 */
void POWER_SetWakeUpPins(uint32_t wakeup_io_cfg_src, uint32_t wakeup_io_ctrl);

/**
 * @brief   Return some key information related to the device reset causes / wake-up sources, for all power modes.
 * @param   reset_cause   : the device reset cause, according to the definition of power_reset_cause_t type.
 * @param   boot_mode     : the device boot mode, according to the definition of power_boot_mode_t type.
 * @param   wakeup_pin_cause: the wake-up pin sources, according to the definition of power_wakeup_pin_t  type.

 * @return  Nothing
 *
 */
void POWER_GetWakeUpCause(power_reset_cause_t *reset_cause,
                          power_boot_mode_t *boot_mode,
                          power_wakeup_pin_t *wakeup_pin_cause);

/**
 * @brief   Configures the device internal power control settings
 * @param   system_freq_hz: operating frequency required (in Hertz).
 * @return  Nothing
 *
 *          prepare on-chip power regulators (DC-DC Converter / Core and Always-on
 *          Low Drop-Out regulators)  to deliver the amount of power needed for the
 *          requested performance level, as defined by the CPU operating frequency.
 */
void POWER_SetVoltageForFreq(uint32_t system_freq_hz);

#ifdef __cplusplus
}
#endif

#endif /* _FSL_POWER_H_ */
