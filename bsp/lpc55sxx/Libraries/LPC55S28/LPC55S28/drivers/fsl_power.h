/*
 * Copyright 2017, NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef _FSL_POWER_H_
#define _FSL_POWER_H_

#include "fsl_common.h"
#include "fsl_device_registers.h"
#include <stdint.h>

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

/* Power mode configuration API parameter */
typedef enum _power_mode_config
{
    kPmu_Sleep          = 0U,
    kPmu_Deep_Sleep     = 1U,
    kPmu_PowerDown      = 2U,
    kPmu_Deep_PowerDown = 3U,
} power_mode_cfg_t;

/**
 * @brief Analog components power modes control during low power modes
 */
typedef enum pd_bits
{
    kPDRUNCFG_PD_DCDC         = (1UL << 0),
    kPDRUNCFG_PD_BIAS         = (1UL << 1),
    kPDRUNCFG_PD_BODCORE      = (1UL << 2),
    kPDRUNCFG_PD_BODVBAT      = (1UL << 3),
    kPDRUNCFG_PD_FRO1M        = (1UL << 4),
    kPDRUNCFG_PD_FRO192M      = (1UL << 5),
    kPDRUNCFG_PD_FRO32K       = (1UL << 6),
    kPDRUNCFG_PD_XTAL32K      = (1UL << 7),
    kPDRUNCFG_PD_XTAL32M      = (1UL << 8),
    kPDRUNCFG_PD_PLL0         = (1UL << 9),
    kPDRUNCFG_PD_PLL1         = (1UL << 10),
    kPDRUNCFG_PD_USB0_PHY     = (1UL << 11),
    kPDRUNCFG_PD_USB1_PHY     = (1UL << 12),
    kPDRUNCFG_PD_COMP         = (1UL << 13),
    kPDRUNCFG_PD_TEMPSENS     = (1UL << 14),
    kPDRUNCFG_PD_GPADC        = (1UL << 15),
    kPDRUNCFG_PD_LDOMEM       = (1UL << 16),
    kPDRUNCFG_PD_LDODEEPSLEEP = (1UL << 17),
    kPDRUNCFG_PD_LDOUSBHS     = (1UL << 18),
    kPDRUNCFG_PD_LDOGPADC     = (1UL << 19),
    kPDRUNCFG_PD_LDOXO32M     = (1UL << 20),
    kPDRUNCFG_PD_LDOFLASHNV   = (1UL << 21),
    kPDRUNCFG_PD_RNG          = (1UL << 22),
    kPDRUNCFG_PD_PLL0_SSCG    = (1UL << 23),
    kPDRUNCFG_PD_ROM          = (1UL << 24),
    /*
       This enum member has no practical meaning,it is used to avoid MISRA issue,
       user should not trying to use it.
       */
    kPDRUNCFG_ForceUnsigned = 0x80000000U,
} pd_bit_t;

/*! @brief BOD VBAT level */
typedef enum _power_bod_vbat_level
{
    kPOWER_BodVbatLevel1000mv = 0,  /*!< Brown out detector VBAT level 1V */
    kPOWER_BodVbatLevel1100mv = 1,  /*!< Brown out detector VBAT level 1.1V */
    kPOWER_BodVbatLevel1200mv = 2,  /*!< Brown out detector VBAT level 1.2V */
    kPOWER_BodVbatLevel1300mv = 3,  /*!< Brown out detector VBAT level 1.3V */
    kPOWER_BodVbatLevel1400mv = 4,  /*!< Brown out detector VBAT level 1.4V */
    kPOWER_BodVbatLevel1500mv = 5,  /*!< Brown out detector VBAT level 1.5V */
    kPOWER_BodVbatLevel1600mv = 6,  /*!< Brown out detector VBAT level 1.6V */
    kPOWER_BodVbatLevel1650mv = 7,  /*!< Brown out detector VBAT level 1.65V */
    kPOWER_BodVbatLevel1700mv = 8,  /*!< Brown out detector VBAT level 1.7V */
    kPOWER_BodVbatLevel1750mv = 9,  /*!< Brown out detector VBAT level 1.75V */
    kPOWER_BodVbatLevel1800mv = 10, /*!< Brown out detector VBAT level 1.8V */
    kPOWER_BodVbatLevel1900mv = 11, /*!< Brown out detector VBAT level 1.9V */
    kPOWER_BodVbatLevel2000mv = 12, /*!< Brown out detector VBAT level 2V */
    kPOWER_BodVbatLevel2100mv = 13, /*!< Brown out detector VBAT level 2.1V */
    kPOWER_BodVbatLevel2200mv = 14, /*!< Brown out detector VBAT level 2.2V */
    kPOWER_BodVbatLevel2300mv = 15, /*!< Brown out detector VBAT level 2.3V */
    kPOWER_BodVbatLevel2400mv = 16, /*!< Brown out detector VBAT level 2.4V */
    kPOWER_BodVbatLevel2500mv = 17, /*!< Brown out detector VBAT level 2.5V */
    kPOWER_BodVbatLevel2600mv = 18, /*!< Brown out detector VBAT level 2.6V */
    kPOWER_BodVbatLevel2700mv = 19, /*!< Brown out detector VBAT level 2.7V */
    kPOWER_BodVbatLevel2806mv = 20, /*!< Brown out detector VBAT level 2.806V */
    kPOWER_BodVbatLevel2900mv = 21, /*!< Brown out detector VBAT level 2.9V */
    kPOWER_BodVbatLevel3000mv = 22, /*!< Brown out detector VBAT level 3.0V */
    kPOWER_BodVbatLevel3100mv = 23, /*!< Brown out detector VBAT level 3.1V */
    kPOWER_BodVbatLevel3200mv = 24, /*!< Brown out detector VBAT level 3.2V */
    kPOWER_BodVbatLevel3300mv = 25, /*!< Brown out detector VBAT level 3.3V */
} power_bod_vbat_level_t;

/*! @brief BOD Hysteresis control */
typedef enum _power_bod_hyst
{
    kPOWER_BodHystLevel25mv  = 0U, /*!< BOD Hysteresis control level 25mv */
    kPOWER_BodHystLevel50mv  = 1U, /*!< BOD Hysteresis control level 50mv */
    kPOWER_BodHystLevel75mv  = 2U, /*!< BOD Hysteresis control level 75mv */
    kPOWER_BodHystLevel100mv = 3U, /*!< BOD Hysteresis control level 100mv */
} power_bod_hyst_t;

/*! @brief BOD core level */
typedef enum _power_bod_core_level
{
    kPOWER_BodCoreLevel600mv = 0, /*!< Brown out detector core level 600mV */
    kPOWER_BodCoreLevel650mv = 1, /*!< Brown out detector core level 650mV */
    kPOWER_BodCoreLevel700mv = 2, /*!< Brown out detector core level 700mV */
    kPOWER_BodCoreLevel750mv = 3, /*!< Brown out detector core level 750mV */
    kPOWER_BodCoreLevel800mv = 4, /*!< Brown out detector core level 800mV */
    kPOWER_BodCoreLevel850mv = 5, /*!< Brown out detector core level 850mV */
    kPOWER_BodCoreLevel900mv = 6, /*!< Brown out detector core level 900mV */
    kPOWER_BodCoreLevel950mv = 7, /*!< Brown out detector core level 950mV */
} power_bod_core_level_t;

/**
 * @brief Device Reset Causes
 */
typedef enum _power_device_reset_cause
{
    kRESET_CAUSE_POR            = 0UL, /*!< Power On Reset */
    kRESET_CAUSE_PADRESET       = 1UL, /*!< Hardware Pin Reset */
    kRESET_CAUSE_BODRESET       = 2UL, /*!< Brown-out Detector reset (either BODVBAT or BODCORE) */
    kRESET_CAUSE_ARMSYSTEMRESET = 3UL, /*!< ARM System Reset */
    kRESET_CAUSE_WDTRESET       = 4UL, /*!< Watchdog Timer Reset */
    kRESET_CAUSE_SWRRESET       = 5UL, /*!< Software Reset */
    kRESET_CAUSE_CDOGRESET      = 6UL, /*!< Code Watchdog Reset */
    /* Reset causes in DEEP-POWER-DOWN low power mode */
    kRESET_CAUSE_DPDRESET_WAKEUPIO     = 7UL,  /*!< Any of the 4 wake-up pins */
    kRESET_CAUSE_DPDRESET_RTC          = 8UL,  /*!< Real Time Counter (RTC) */
    kRESET_CAUSE_DPDRESET_OSTIMER      = 9UL,  /*!< OS Event Timer (OSTIMER) */
    kRESET_CAUSE_DPDRESET_WAKEUPIO_RTC = 10UL, /*!< Any of the 4 wake-up pins and RTC (it is not possible to distinguish
                                                  which of these 2 events occured first) */
    kRESET_CAUSE_DPDRESET_WAKEUPIO_OSTIMER = 11UL,     /*!< Any of the 4 wake-up pins and OSTIMER (it is not possible to
                                                          distinguish which of these 2 events occured first) */
    kRESET_CAUSE_DPDRESET_RTC_OSTIMER = 12UL,          /*!< Real Time Counter or OS Event Timer (it is not possible to
                                                          distinguish which of these 2 events occured first) */
    kRESET_CAUSE_DPDRESET_WAKEUPIO_RTC_OSTIMER = 13UL, /*!< Any of the 4 wake-up pins (it is not possible to distinguish
                                                          which of these 3 events occured first) */
    /* Miscallenous */
    kRESET_CAUSE_NOT_RELEVANT =
        14UL, /*!< No reset cause (for example, this code is used when waking up from DEEP-SLEEP low power mode) */
    kRESET_CAUSE_NOT_DETERMINISTIC = 15UL, /*!< Unknown Reset Cause. Should be treated like "Hardware Pin Reset" from an
                                              application point of view. */
} power_device_reset_cause_t;

/**
 * @brief Device Boot Modes
 */
typedef enum _power_device_boot_mode
{
    kBOOT_MODE_POWER_UP =
        0UL, /*!< All non Low Power Mode wake up (Power On Reset, Pin Reset, BoD Reset, ARM System Reset ... ) */
    kBOOT_MODE_LP_DEEP_SLEEP      = 1UL, /*!< Wake up from DEEP-SLEEP Low Power mode */
    kBOOT_MODE_LP_POWER_DOWN      = 2UL, /*!< Wake up from POWER-DOWN Low Power mode */
    kBOOT_MODE_LP_DEEP_POWER_DOWN = 4UL, /*!< Wake up from DEEP-POWER-DOWN Low Power mode */
} power_device_boot_mode_t;

/**
 * @brief SRAM instances retention control during low power modes
 */
#define LOWPOWER_SRAMRETCTRL_RETEN_RAMX0 \
    (1UL << 0) /*!< Enable SRAMX_0 retention when entering in Low power modes       */
#define LOWPOWER_SRAMRETCTRL_RETEN_RAMX1 \
    (1UL << 1) /*!< Enable SRAMX_1 retention when entering in Low power modes       */
#define LOWPOWER_SRAMRETCTRL_RETEN_RAMX2 \
    (1UL << 2) /*!< Enable SRAMX_2 retention when entering in Low power modes       */
#define LOWPOWER_SRAMRETCTRL_RETEN_RAMX3 \
    (1UL << 3) /*!< Enable SRAMX_3 retention when entering in Low power modes       */
#define LOWPOWER_SRAMRETCTRL_RETEN_RAM00 \
    (1UL << 4) /*!< Enable SRAM0_0 retention when entering in Low power modes       */
#define LOWPOWER_SRAMRETCTRL_RETEN_RAM01 \
    (1UL << 5) /*!< Enable SRAM0_1 retention when entering in Low power modes       */
#define LOWPOWER_SRAMRETCTRL_RETEN_RAM10 \
    (1UL << 6) /*!< Enable SRAM1_0 retention when entering in Low power modes       */
#define LOWPOWER_SRAMRETCTRL_RETEN_RAM20 \
    (1UL << 7) /*!< Enable SRAM2_0 retention when entering in Low power modes       */
#define LOWPOWER_SRAMRETCTRL_RETEN_RAM30 \
    (1UL << 8) /*!< Enable SRAM3_0 retention when entering in Low power modes       */
#define LOWPOWER_SRAMRETCTRL_RETEN_RAM31 \
    (1UL << 9) /*!< Enable SRAM3_1 retention when entering in Low power modes       */
#define LOWPOWER_SRAMRETCTRL_RETEN_RAM40 \
    (1UL << 10) /*!< Enable SRAM4_0 retention when entering in Low power modes       */
#define LOWPOWER_SRAMRETCTRL_RETEN_RAM41 \
    (1UL << 11) /*!< Enable SRAM4_1 retention when entering in Low power modes       */
#define LOWPOWER_SRAMRETCTRL_RETEN_RAM42 \
    (1UL << 12) /*!< Enable SRAM4_2 retention when entering in Low power modes       */
#define LOWPOWER_SRAMRETCTRL_RETEN_RAM43 \
    (1UL << 13) /*!< Enable SRAM4_3 retention when entering in Low power modes       */
#define LOWPOWER_SRAMRETCTRL_RETEN_RAM_USB_HS \
    (1UL << 14) /*!< Enable SRAM USB HS retention when entering in Low power modes   */
#define LOWPOWER_SRAMRETCTRL_RETEN_RAM_PUF \
    (1UL << 15) /*!< Enable SRAM PUFF retention when entering in Low power modes     */

/**
 * @brief Low Power Modes Wake up sources
 */
#define WAKEUP_SYS             (1ULL << 0) /*!< [SLEEP, DEEP SLEEP                             ] */ /* WWDT0_IRQ and BOD_IRQ*/
#define WAKEUP_SDMA0           (1ULL << 1)  /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_GPIO_GLOBALINT0 (1ULL << 2)  /*!< [SLEEP, DEEP SLEEP, POWER DOWN                 ] */
#define WAKEUP_GPIO_GLOBALINT1 (1ULL << 3)  /*!< [SLEEP, DEEP SLEEP, POWER DOWN                 ] */
#define WAKEUP_GPIO_INT0_0     (1ULL << 4)  /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_GPIO_INT0_1     (1ULL << 5)  /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_GPIO_INT0_2     (1ULL << 6)  /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_GPIO_INT0_3     (1ULL << 7)  /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_UTICK           (1ULL << 8)  /*!< [SLEEP,                                        ] */
#define WAKEUP_MRT             (1ULL << 9)  /*!< [SLEEP,                                        ] */
#define WAKEUP_CTIMER0         (1ULL << 10) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_CTIMER1         (1ULL << 11) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_SCT             (1ULL << 12) /*!< [SLEEP,                                        ] */
#define WAKEUP_CTIMER3         (1ULL << 13) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_FLEXCOMM0       (1ULL << 14) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_FLEXCOMM1       (1ULL << 15) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_FLEXCOMM2       (1ULL << 16) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_FLEXCOMM3       (1ULL << 17) /*!< [SLEEP, DEEP SLEEP, POWER DOWN                 ] */
#define WAKEUP_FLEXCOMM4       (1ULL << 18) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_FLEXCOMM5       (1ULL << 19) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_FLEXCOMM6       (1ULL << 20) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_FLEXCOMM7       (1ULL << 21) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_ADC             (1ULL << 22) /*!< [SLEEP,                                        ] */
#define WAKEUP_ACMP_CAPT       (1ULL << 24) /*!< [SLEEP, DEEP SLEEP, POWER DOWN                 ] */
// reserved                                         (1ULL << 25)
// reserved                                         (1ULL << 26)
#define WAKEUP_USB0_NEEDCLK          (1ULL << 27) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_USB0                  (1ULL << 28) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_RTC_LITE_ALARM_WAKEUP (1ULL << 29) /*!< [SLEEP, DEEP SLEEP, POWER DOWN, DEEP POWER DOWN] */
#define WAKEUP_EZH_ARCH_B            (1ULL << 30) /*!< [SLEEP,                                        ] */
#define WAKEUP_WAKEUP_MAILBOX        (1ULL << 31) /*!< [SLEEP, DEEP SLEEP, POWER DOWN                 ] */
#define WAKEUP_GPIO_INT0_4           (1ULL << 32) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_GPIO_INT0_5           (1ULL << 33) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_GPIO_INT0_6           (1ULL << 34) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_GPIO_INT0_7           (1ULL << 35) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_CTIMER2               (1ULL << 36) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_CTIMER4               (1ULL << 37) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_OS_EVENT_TIMER        (1ULL << 38) /*!< [SLEEP, DEEP SLEEP, POWER DOWN, DEEP POWER DOWN] */
// reserved                                         (1ULL << 39)
// reserved                                         (1ULL << 40)
// reserved                                         (1ULL << 41)
#define WAKEUP_SDIO (1ULL << 42) /*!< [SLEEP,                                        ] */
// reserved                                         (1ULL << 43)
// reserved                                         (1ULL << 44)
// reserved                                         (1ULL << 45)
// reserved                                         (1ULL << 46)
#define WAKEUP_USB1                (1ULL << 47) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_USB1_NEEDCLK        (1ULL << 48) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_SEC_HYPERVISOR_CALL (1ULL << 49) /*!< [SLEEP,                                        ] */
#define WAKEUP_SEC_GPIO_INT0_0     (1ULL << 50) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_SEC_GPIO_INT0_1     (1ULL << 51) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_PLU                 (1ULL << 52) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_SEC_VIO             (1ULL << 53)
#define WAKEUP_SHA                 (1ULL << 54) /*!< [SLEEP,                                        ] */
#define WAKEUP_CASPER              (1ULL << 55) /*!< [SLEEP,                                        ] */
#define WAKEUP_PUFF                (1ULL << 56) /*!< [SLEEP,                                        ] */
#define WAKEUP_PQ                  (1ULL << 57) /*!< [SLEEP,                                        ] */
#define WAKEUP_SDMA1               (1ULL << 58) /*!< [SLEEP, DEEP SLEEP                             ] */
#define WAKEUP_LSPI_HS             (1ULL << 59) /*!< [SLEEP, DEEP SLEEP                             ] */
// reserved WAKEUP_PVTVF0_AMBER                     (1ULL << 60)
// reserved WAKEUP_PVTVF0_RED                       (1ULL << 61)
// reserved WAKEUP_PVTVF1_AMBER                     (1ULL << 62)
#define WAKEUP_ALLWAKEUPIOS (1ULL << 63) /*!< [                             , DEEP POWER DOWN] */

/**
 * @brief Sleep Postpone
 */
#define LOWPOWER_HWWAKE_FORCED (1UL << 0) /*!< Force peripheral clocking to stay on during deep-sleep mode. */
#define LOWPOWER_HWWAKE_PERIPHERALS                                                                                \
    (1UL << 1) /*!< Wake for Flexcomms. Any Flexcomm FIFO reaching the level specified by its own TXLVL will cause \
                  peripheral clocking to wake up temporarily while the related status is asserted */
#define LOWPOWER_HWWAKE_SDMA0                                                                                 \
    (1UL << 3) /*!< Wake for DMA0. DMA0 being busy will cause peripheral clocking to remain running until DMA \
                  completes. Used in conjonction with LOWPOWER_HWWAKE_PERIPHERALS */
#define LOWPOWER_HWWAKE_SDMA1                                                                                 \
    (1UL << 5) /*!< Wake for DMA1. DMA0 being busy will cause peripheral clocking to remain running until DMA \
                  completes. Used in conjonction with LOWPOWER_HWWAKE_PERIPHERALS */
#define LOWPOWER_HWWAKE_ENABLE_FRO192M                                                                  \
    (1UL << 31) /*!< Need to be set if FRO192M is disable - via PDCTRL0 - in Deep Sleep mode and any of \
                   LOWPOWER_HWWAKE_PERIPHERALS, LOWPOWER_HWWAKE_SDMA0 or LOWPOWER_HWWAKE_SDMA1 is set */

#define LOWPOWER_CPURETCTRL_ENA_DISABLE 0 /*!< In POWER DOWN mode, CPU Retention is disabled */
#define LOWPOWER_CPURETCTRL_ENA_ENABLE  1 /*!< In POWER DOWN mode, CPU Retention is enabled  */
/**
 * @brief Wake up I/O sources
 */
#define LOWPOWER_WAKEUPIOSRC_PIO0_INDEX 0 /*!< Pin P1( 1) */
#define LOWPOWER_WAKEUPIOSRC_PIO1_INDEX 2 /*!< Pin P0(28) */
#define LOWPOWER_WAKEUPIOSRC_PIO2_INDEX 4 /*!< Pin P1(18) */
#define LOWPOWER_WAKEUPIOSRC_PIO3_INDEX 6 /*!< Pin P1(30) */

#define LOWPOWER_WAKEUPIOSRC_DISABLE        0 /*!< Wake up is disable                      */
#define LOWPOWER_WAKEUPIOSRC_RISING         1 /*!< Wake up on rising edge                  */
#define LOWPOWER_WAKEUPIOSRC_FALLING        2 /*!< Wake up on falling edge                 */
#define LOWPOWER_WAKEUPIOSRC_RISING_FALLING 3 /*!< Wake up on both rising or falling edges */

#define LOWPOWER_WAKEUPIO_PIO0_PULLUPDOWN_INDEX 8  /*!< Wake-up I/O 0 pull-up/down configuration index */
#define LOWPOWER_WAKEUPIO_PIO1_PULLUPDOWN_INDEX 9  /*!< Wake-up I/O 1 pull-up/down configuration index */
#define LOWPOWER_WAKEUPIO_PIO2_PULLUPDOWN_INDEX 10 /*!< Wake-up I/O 2 pull-up/down configuration index */
#define LOWPOWER_WAKEUPIO_PIO3_PULLUPDOWN_INDEX 11 /*!< Wake-up I/O 3 pull-up/down configuration index */

#define LOWPOWER_WAKEUPIO_PIO0_PULLUPDOWN_MASK \
    (1UL << LOWPOWER_WAKEUPIO_PIO0_PULLUPDOWN_INDEX) /*!< Wake-up I/O 0 pull-up/down mask */
#define LOWPOWER_WAKEUPIO_PIO1_PULLUPDOWN_MASK \
    (1UL << LOWPOWER_WAKEUPIO_PIO1_PULLUPDOWN_INDEX) /*!< Wake-up I/O 1 pull-up/down mask */
#define LOWPOWER_WAKEUPIO_PIO2_PULLUPDOWN_MASK \
    (1UL << LOWPOWER_WAKEUPIO_PIO2_PULLUPDOWN_INDEX) /*!< Wake-up I/O 2 pull-up/down mask */
#define LOWPOWER_WAKEUPIO_PIO3_PULLUPDOWN_MASK \
    (1UL << LOWPOWER_WAKEUPIO_PIO3_PULLUPDOWN_INDEX) /*!< Wake-up I/O 3 pull-up/down mask */

#define LOWPOWER_WAKEUPIO_PULLDOWN 0 /*!< Select pull-down                */
#define LOWPOWER_WAKEUPIO_PULLUP   1 /*!< Select pull-up                  */

#define LOWPOWER_WAKEUPIO_PIO0_DISABLEPULLUPDOWN_INDEX \
    12 /*!< Wake-up I/O 0 pull-up/down disable/enable control index */
#define LOWPOWER_WAKEUPIO_PIO1_DISABLEPULLUPDOWN_INDEX \
    13 /*!< Wake-up I/O 1 pull-up/down disable/enable control index */
#define LOWPOWER_WAKEUPIO_PIO2_DISABLEPULLUPDOWN_INDEX \
    14 /*!< Wake-up I/O 2 pull-up/down disable/enable control index */
#define LOWPOWER_WAKEUPIO_PIO3_DISABLEPULLUPDOWN_INDEX \
    15 /*!< Wake-up I/O 3 pull-up/down disable/enable control index */
#define LOWPOWER_WAKEUPIO_PIO0_DISABLEPULLUPDOWN_MASK \
    (1UL << LOWPOWER_WAKEUPIO_PIO0_DISABLEPULLUPDOWN_INDEX) /*!< Wake-up I/O 0 pull-up/down disable/enable mask */
#define LOWPOWER_WAKEUPIO_PIO1_DISABLEPULLUPDOWN_MASK \
    (1UL << LOWPOWER_WAKEUPIO_PIO1_DISABLEPULLUPDOWN_INDEX) /*!< Wake-up I/O 1 pull-up/down disable/enable mask */
#define LOWPOWER_WAKEUPIO_PIO2_DISABLEPULLUPDOWN_MASK \
    (1UL << LOWPOWER_WAKEUPIO_PIO2_DISABLEPULLUPDOWN_INDEX) /*!< Wake-up I/O 2 pull-up/down disable/enable mask */
#define LOWPOWER_WAKEUPIO_PIO3_DISABLEPULLUPDOWN_MASK \
    (1UL << LOWPOWER_WAKEUPIO_PIO3_DISABLEPULLUPDOWN_INDEX) /*!< Wake-up I/O 3 pull-up/down disable/enable mask */

#define LOWPOWER_WAKEUPIO_PIO0_USEEXTERNALPULLUPDOWN_INDEX \
    (16) /*!< Wake-up I/O 0 use external pull-up/down disable/enable control index*/
#define LOWPOWER_WAKEUPIO_PIO1_USEEXTERNALPULLUPDOWN_INDEX \
    (17) /*!< Wake-up I/O 1 use external pull-up/down disable/enable control index */
#define LOWPOWER_WAKEUPIO_PIO2_USEEXTERNALPULLUPDOWN_INDEX \
    (18) /*!< Wake-up I/O 2 use external pull-up/down disable/enable control index */
#define LOWPOWER_WAKEUPIO_PIO3_USEEXTERNALPULLUPDOWN_INDEX \
    (19) /*!< Wake-up I/O 3 use external pull-up/down disable/enable control index */
#define LOWPOWER_WAKEUPIO_PIO0_USEEXTERNALPULLUPDOWN_MASK                                                    \
    (1UL << LOWPOWER_WAKEUPIO_PIO0_USEEXTERNALPULLUPDOWN_INDEX) /*!< Wake-up I/O 0 use external pull-up/down \
                                                                   disable/enable mask, 0: disable, 1: enable */
#define LOWPOWER_WAKEUPIO_PIO1_USEEXTERNALPULLUPDOWN_MASK                                                    \
    (1UL << LOWPOWER_WAKEUPIO_PIO1_USEEXTERNALPULLUPDOWN_INDEX) /*!< Wake-up I/O 1 use external pull-up/down \
                                                                   disable/enable mask, 0: disable, 1: enable */
#define LOWPOWER_WAKEUPIO_PIO2_USEEXTERNALPULLUPDOWN_MASK                                                    \
    (1UL << LOWPOWER_WAKEUPIO_PIO2_USEEXTERNALPULLUPDOWN_INDEX) /*!< Wake-up I/O 2 use external pull-up/down \
                                                                   disable/enable mask, 0: disable, 1: enable */
#define LOWPOWER_WAKEUPIO_PIO3_USEEXTERNALPULLUPDOWN_MASK                                                    \
    (1UL << LOWPOWER_WAKEUPIO_PIO3_USEEXTERNALPULLUPDOWN_INDEX) /*!< Wake-up I/O 3 use external pull-up/down \
                                                                   disable/enable mask, 0: disable, 1: enable */

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
    /* PDRUNCFGSET */
    PMC->PDRUNCFGSET0 = (uint32_t)en;
}

/*!
 * @brief API to disable PDRUNCFG bit in the Syscon. Note that disabling the bit powers up the peripheral
 *
 * @param en    peripheral for which to disable the PDRUNCFG bit
 * @return none
 */
static inline void POWER_DisablePD(pd_bit_t en)
{
    /* PDRUNCFGCLR */
    PMC->PDRUNCFGCLR0 = (uint32_t)en;
}

/*!
 * @brief set BOD VBAT level.
 *
 * @param level BOD detect level
 * @param hyst BoD Hysteresis control
 * @param enBodVbatReset VBAT brown out detect reset
 */
static inline void POWER_SetBodVbatLevel(power_bod_vbat_level_t level, power_bod_hyst_t hyst, bool enBodVbatReset)
{
    PMC->BODVBAT = (PMC->BODVBAT & (~(PMC_BODVBAT_TRIGLVL_MASK | PMC_BODVBAT_HYST_MASK))) | PMC_BODVBAT_TRIGLVL(level) |
                   PMC_BODVBAT_HYST(hyst);
    PMC->RESETCTRL =
        (PMC->RESETCTRL & (~PMC_RESETCTRL_BODVBATRESETENABLE_MASK)) | PMC_RESETCTRL_BODVBATRESETENABLE(enBodVbatReset);
}

#if defined(PMC_BODCORE_TRIGLVL_MASK)
/*!
 * @brief set BOD core level.
 *
 * @param level BOD detect level
 * @param hyst BoD Hysteresis control
 * @param enBodCoreReset core brown out detect reset
 */
static inline void POWER_SetBodCoreLevel(power_bod_core_level_t level, power_bod_hyst_t hyst, bool enBodCoreReset)
{
    PMC->BODCORE = (PMC->BODCORE & (~(PMC_BODCORE_TRIGLVL_MASK | PMC_BODCORE_HYST_MASK))) | PMC_BODCORE_TRIGLVL(level) |
                   PMC_BODCORE_HYST(hyst);
    PMC->RESETCTRL =
        (PMC->RESETCTRL & (~PMC_RESETCTRL_BODCORERESETENABLE_MASK)) | PMC_RESETCTRL_BODCORERESETENABLE(enBodCoreReset);
}
#endif

/*!
 * @brief API to enable deep sleep bit in the ARM Core.
 *
 * @return none
 */
static inline void POWER_EnableDeepSleep(void)
{
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
}

/*!
 * @brief API to disable deep sleep bit in the ARM Core.
 *
 * @return none
 */
static inline void POWER_DisableDeepSleep(void)
{
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
}

/**
 * @brief   Shut off the Flash and execute the _WFI(), then power up the Flash after wake-up event
 *  This MUST BE EXECUTED outside the Flash:
 *  either from ROM or from SRAM. The rest could stay in Flash. But, for consistency, it is
 *  preferable to have all functions defined in this file implemented in ROM.
 *
 * @return  Nothing
 */
void POWER_CycleCpuAndFlash(void);

/**
 * @brief   Configures and enters in DEEP-SLEEP low power mode
 * @param   exclude_from_pd:
 * @param   sram_retention_ctrl:
 * @param   wakeup_interrupts:
 * @param   hardware_wake_ctrl:

 * @return  Nothing
 *
 *          !!! IMPORTANT NOTES :
 0 - CPU0 & System CLock frequency is switched to FRO12MHz and is NOT restored back by the API.
 *           1 - CPU0 Interrupt Enable registers (NVIC->ISER) are modified by this function. They are restored back in
 case of CPU retention or if POWERDOWN is not taken (for instance because an interrupt is pending).
 *           2 - The Non Maskable Interrupt (NMI) is disabled and its configuration before calling this function will be
 restored back if POWERDOWN is not taken (for instance because an RTC or OSTIMER interrupt is pending).
 *           3 - The HARD FAULT handler should execute from SRAM. (The Hard fault handler should initiate a full chip
 reset) reset)
 */
void POWER_EnterDeepSleep(uint32_t exclude_from_pd,
                          uint32_t sram_retention_ctrl,
                          uint64_t wakeup_interrupts,
                          uint32_t hardware_wake_ctrl);

/**
 * @brief   Configures and enters in POWERDOWN low power mode
 * @param   exclude_from_pd:
 * @param   sram_retention_ctrl:
 * @param   wakeup_interrupts:
 * @param   cpu_retention_ctrl:  0 = CPU retention is disable / 1 = CPU retention is enabled, all other values are
 RESERVED.

 * @return  Nothing
 *
 *          !!! IMPORTANT NOTES :
 0 - CPU0 & System CLock frequency is switched to FRO12MHz and is NOT restored back by the API.
 *           1 - CPU0 Interrupt Enable registers (NVIC->ISER) are modified by this function. They are restored back in
 case of CPU retention or if POWERDOWN is not taken (for instance because an interrupt is pending).
 *           2 - The Non Maskable Interrupt (NMI) is disabled and its configuration before calling this function will be
 restored back if POWERDOWN is not taken (for instance because an RTC or OSTIMER interrupt is pending).
 *           3 - In case of CPU retention, it is the responsability of the user to make sure that SRAM instance
 containing the stack used to call this function WILL BE preserved during low power (via parameter
 "sram_retention_ctrl")
 *           4 - The HARD FAULT handler should execute from SRAM. (The Hard fault handler should initiate a full chip
 reset) reset)
 */

void POWER_EnterPowerDown(uint32_t exclude_from_pd,
                          uint32_t sram_retention_ctrl,
                          uint64_t wakeup_interrupts,
                          uint32_t cpu_retention_ctrl);

/**
 * @brief   Configures and enters in DEEPPOWERDOWN low power mode
 * @param   exclude_from_pd:
 * @param   sram_retention_ctrl:
 * @param   wakeup_interrupts:
 * @param   wakeup_io_ctrl:

 * @return  Nothing
 *
 *          !!! IMPORTANT NOTES :
 0 - CPU0 & System CLock frequency is switched to FRO12MHz and is NOT restored back by the API.
 *           1 - CPU0 Interrupt Enable registers (NVIC->ISER) are modified by this function. They are restored back if
 DEEPPOWERDOWN is not taken (for instance because an RTC or OSTIMER interrupt is pending).
 *           2 - The Non Maskable Interrupt (NMI) is disabled and its configuration before calling this function will be
 restored back if DEEPPOWERDOWN is not taken (for instance because an RTC or OSTIMER interrupt is pending).
 *           3 - The HARD FAULT handler should execute from SRAM. (The Hard fault handler should initiate a full chip
 reset)
 */
void POWER_EnterDeepPowerDown(uint32_t exclude_from_pd,
                              uint32_t sram_retention_ctrl,
                              uint64_t wakeup_interrupts,
                              uint32_t wakeup_io_ctrl);

/**
 * @brief   Configures and enters in SLEEP low power mode
 * @param   :
 * @return  Nothing
 */
void POWER_EnterSleep(void);

/*!
 * @brief Power Library API to choose normal regulation and set the voltage for the desired operating frequency.
 *
 * @param system_freq_hz  - The desired frequency (in Hertz) at which the part would like to operate,
 *                note that the voltage and flash wait states should be set before changing frequency
 * @return none
 */
void POWER_SetVoltageForFreq(uint32_t system_freq_hz);

/**
 * @brief   Sets board-specific trim values for 16MHz XTAL
 * @param   pi32_16MfXtalIecLoadpF_x100 Load capacitance, pF x 100. For example, 6pF becomes 600, 1.2pF becomes 120
 * @param   pi32_16MfXtalPPcbParCappF_x100 PCB +ve parasitic capacitance, pF x 100. For example, 6pF becomes 600, 1.2pF
 * becomes 120
 * @param   pi32_16MfXtalNPcbParCappF_x100 PCB -ve parasitic capacitance, pF x 100. For example, 6pF becomes 600, 1.2pF
 * becomes 120
 * @return  none
 * @note    Following default Values can be used:
 *          pi32_32MfXtalIecLoadpF_x100    Load capacitance, pF x 100 : 600
 *          pi32_32MfXtalPPcbParCappF_x100 PCB +ve parasitic capacitance, pF x 100 : 20
 *          pi32_32MfXtalNPcbParCappF_x100 PCB -ve parasitic capacitance, pF x 100 : 40
 */
extern void POWER_Xtal16mhzCapabankTrim(int32_t pi32_16MfXtalIecLoadpF_x100,
                                        int32_t pi32_16MfXtalPPcbParCappF_x100,
                                        int32_t pi32_16MfXtalNPcbParCappF_x100);
/**
 * @brief   Sets board-specific trim values for 32kHz XTAL
 * @param   pi32_32kfXtalIecLoadpF_x100 Load capacitance, pF x 100. For example, 6pF becomes 600, 1.2pF becomes 120
 * @param   pi32_32kfXtalPPcbParCappF_x100 PCB +ve parasitic capacitance, pF x 100. For example, 6pF becomes 600, 1.2pF
 becomes 120
 * @param   pi32_32kfXtalNPcbParCappF_x100 PCB -ve parasitic capacitance, pF x 100. For example, 6pF becomes 600, 1.2pF
 becomes 120

 * @return  none
 * @note    Following default Values can be used:
 *          pi32_32kfXtalIecLoadpF_x100    Load capacitance, pF x 100 : 600
 *          pi32_32kfXtalPPcbParCappF_x100 PCB +ve parasitic capacitance, pF x 100 : 40
 *          pi32_32kfXtalNPcbParCappF_x100 PCB -ve parasitic capacitance, pF x 100 : 40
 */
extern void POWER_Xtal32khzCapabankTrim(int32_t pi32_32kfXtalIecLoadpF_x100,
                                        int32_t pi32_32kfXtalPPcbParCappF_x100,
                                        int32_t pi32_32kfXtalNPcbParCappF_x100);
/**
 * @brief   Enables and sets LDO for 16MHz XTAL
 *
 * @return  none
 */
extern void POWER_SetXtal16mhzLdo(void);

/**
 * @brief   Return some key information related to the device reset causes / wake-up sources, for all power modes.
 * @param   p_reset_cause   : the device reset cause, according to the definition of power_device_reset_cause_t type.
 * @param   p_boot_mode     : the device boot mode, according to the definition of power_device_boot_mode_t type.
 * @param   p_wakeupio_cause: the wake-up pin sources, according to the definition of register PMC->WAKEIOCAUSE[3:0].

 * @return  Nothing
 *
 *         !!!  IMPORTANT ERRATA - IMPORTANT ERRATA - IMPORTANT ERRATA     !!!
 *         !!!   valid ONLY for LPC55S69 (not for LPC55S16 and LPC55S06)   !!!
 *         !!!   when FALLING EDGE DETECTION is enabled on wake-up pins:   !!!
 *         - 1. p_wakeupio_cause is NOT ACCURATE
 *         - 2. Spurious kRESET_CAUSE_DPDRESET_WAKEUPIO* event is reported when
 *              several wake-up sources are enabled during DEEP-POWER-DOWN
 *              (like enabling wake-up on RTC and Falling edge wake-up pins)
 *
 */
void POWER_GetWakeUpCause(power_device_reset_cause_t *p_reset_cause,
                          power_device_boot_mode_t *p_boot_mode,
                          uint32_t *p_wakeupio_cause);
#ifdef __cplusplus
}
#endif

/**
 * @}
 */

#endif /* _FSL_POWER_H_ */
