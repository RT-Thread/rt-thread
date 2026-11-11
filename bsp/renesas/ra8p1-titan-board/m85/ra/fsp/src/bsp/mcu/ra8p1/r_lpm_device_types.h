/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU_RA8P1
 * @{
 **********************************************************************************************************************/

/** @} (end addtogroup BSP_MCU_RA8P1) */

#ifndef R_LPM_DEVICE_TYPES_H
#define R_LPM_DEVICE_TYPES_H

/***********************************************************************************************************************
 * Includes
 **********************************************************************************************************************/

/* Common macro for FSP header files. There is also a corresponding FSP_FOOTER macro at the end of this file. */
FSP_HEADER

/**********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/
#define BSP_OVERRIDE_LPM_STANDBY_WAKE_SOURCE_T
#define BSP_OVERRIDE_LPM_SNOOZE_CANCEL_T

/**********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Wake from deep sleep or standby mode sources, does not apply to sleep or deep standby modes */
typedef enum e_lpm_standby_wake_source
{
    LPM_STANDBY_WAKE_SOURCE_IRQ0    = 0x00000001ULL,         ///< IRQ0
    LPM_STANDBY_WAKE_SOURCE_IRQ1    = 0x00000002ULL,         ///< IRQ1
    LPM_STANDBY_WAKE_SOURCE_IRQ2    = 0x00000004ULL,         ///< IRQ2
    LPM_STANDBY_WAKE_SOURCE_IRQ3    = 0x00000008ULL,         ///< IRQ3
    LPM_STANDBY_WAKE_SOURCE_IRQ4    = 0x00000010ULL,         ///< IRQ4
    LPM_STANDBY_WAKE_SOURCE_IRQ5    = 0x00000020ULL,         ///< IRQ5
    LPM_STANDBY_WAKE_SOURCE_IRQ6    = 0x00000040ULL,         ///< IRQ6
    LPM_STANDBY_WAKE_SOURCE_IRQ7    = 0x00000080ULL,         ///< IRQ7
    LPM_STANDBY_WAKE_SOURCE_IRQ8    = 0x00000100ULL,         ///< IRQ8
    LPM_STANDBY_WAKE_SOURCE_IRQ9    = 0x00000200ULL,         ///< IRQ9
    LPM_STANDBY_WAKE_SOURCE_IRQ10   = 0x00000400ULL,         ///< IRQ10
    LPM_STANDBY_WAKE_SOURCE_IRQ11   = 0x00000800ULL,         ///< IRQ11
    LPM_STANDBY_WAKE_SOURCE_IRQ12   = 0x00001000ULL,         ///< IRQ12
    LPM_STANDBY_WAKE_SOURCE_IRQ13   = 0x00002000ULL,         ///< IRQ13
    LPM_STANDBY_WAKE_SOURCE_IRQ14   = 0x00004000ULL,         ///< IRQ14
    LPM_STANDBY_WAKE_SOURCE_IRQ15   = 0x00008000ULL,         ///< IRQ15
    LPM_STANDBY_WAKE_SOURCE_IWDT    = 0x00010000ULL,         ///< Independent watchdog interrupt
    LPM_STANDBY_WAKE_SOURCE_LVD1    = 0x00040000ULL,         ///< Low Voltage Detection 1 interrupt
    LPM_STANDBY_WAKE_SOURCE_LVD2    = 0x00080000ULL,         ///< Low Voltage Detection 2 interrupt
    LPM_STANDBY_WAKE_SOURCE_VBATT   = 0x00100000ULL,         ///< VBATT Monitor interrupt
    LPM_STANDBY_WAKE_SOURCE_RTCALM  = 0x01000000ULL,         ///< RTC Alarm interrupt
    LPM_STANDBY_WAKE_SOURCE_RTCPRD  = 0x02000000ULL,         ///< RTC Period interrupt
    LPM_STANDBY_WAKE_SOURCE_USBHS   = 0x04000000ULL,         ///< USB High-speed interrupt
    LPM_STANDBY_WAKE_SOURCE_USBFS   = 0x08000000ULL,         ///< USB Full-speed interrupt
    LPM_STANDBY_WAKE_SOURCE_AGT1UD  = 0x10000000ULL,         ///< AGT1 Underflow interrupt
    LPM_STANDBY_WAKE_SOURCE_AGT1CA  = 0x20000000ULL,         ///< AGT1 Compare Match A interrupt
    LPM_STANDBY_WAKE_SOURCE_AGT1CB  = 0x40000000ULL,         ///< AGT1 Compare Match B interrupt
    LPM_STANDBY_WAKE_SOURCE_IIC0    = 0x80000000ULL,         ///< I2C 0 interrupt
    LPM_STANDBY_WAKE_SOURCE_COMPHS0 = 0x800000000ULL,        ///< Comparator-HS0 Interrupt
    LPM_STANDBY_WAKE_SOURCE_SOSTD   = 0x8000000000ULL,       ///< SOSTD interrupt
    LPM_STANDBY_WAKE_SOURCE_ULP0U   = 0x10000000000ULL,      ///< ULPT0 Underflow Interrupt
    LPM_STANDBY_WAKE_SOURCE_ULP0A   = 0x20000000000ULL,      ///< ULPT0 Compare Match A Interrupt
    LPM_STANDBY_WAKE_SOURCE_ULP0B   = 0x40000000000ULL,      ///< ULPT0 Compare Match B Interrupt
    LPM_STANDBY_WAKE_SOURCE_I3C0    = 0x80000000000ULL,      ///< I3C0 address match interrupt
    LPM_STANDBY_WAKE_SOURCE_ULP1U   = 0x100000000000ULL,     ///< ULPT1 Underflow Interrupt
    LPM_STANDBY_WAKE_SOURCE_ULP1A   = 0x200000000000ULL,     ///< ULPT1 Compare Match A Interrupt
    LPM_STANDBY_WAKE_SOURCE_ULP1B   = 0x400000000000ULL,     ///< ULPT1 Compare Match B Interrupt
    LPM_STANDBY_WAKE_SOURCE_PDM     = 0x800000000000ULL,     ///< PDM Sound Detection
    LPM_STANDBY_WAKE_SOURCE_IRQ16   = 0x1000000000000ULL,    ///< IRQ16
    LPM_STANDBY_WAKE_SOURCE_IRQ17   = 0x2000000000000ULL,    ///< IRQ17
    LPM_STANDBY_WAKE_SOURCE_IRQ18   = 0x4000000000000ULL,    ///< IRQ18
    LPM_STANDBY_WAKE_SOURCE_IRQ19   = 0x8000000000000ULL,    ///< IRQ19
    LPM_STANDBY_WAKE_SOURCE_IRQ20   = 0x10000000000000ULL,   ///< IRQ20
    LPM_STANDBY_WAKE_SOURCE_IRQ21   = 0x20000000000000ULL,   ///< IRQ21
    LPM_STANDBY_WAKE_SOURCE_IRQ22   = 0x40000000000000ULL,   ///< IRQ22
    LPM_STANDBY_WAKE_SOURCE_IRQ23   = 0x80000000000000ULL,   ///< IRQ23
    LPM_STANDBY_WAKE_SOURCE_IRQ24   = 0x100000000000000ULL,  ///< IRQ24
    LPM_STANDBY_WAKE_SOURCE_IRQ25   = 0x200000000000000ULL,  ///< IRQ25
    LPM_STANDBY_WAKE_SOURCE_IRQ26   = 0x400000000000000ULL,  ///< IRQ26
    LPM_STANDBY_WAKE_SOURCE_IRQ27   = 0x800000000000000ULL,  ///< IRQ27
    LPM_STANDBY_WAKE_SOURCE_IRQ28   = 0x1000000000000000ULL, ///< IRQ28
    LPM_STANDBY_WAKE_SOURCE_IRQ29   = 0x2000000000000000ULL, ///< IRQ29
    LPM_STANDBY_WAKE_SOURCE_IRQ30   = 0x4000000000000000ULL, ///< IRQ30
    LPM_STANDBY_WAKE_SOURCE_IRQ31   = 0x8000000000000000ULL, ///< IRQ31
} lpm_standby_wake_source_t;

typedef uint64_t lpm_standby_wake_source_bits_t;

/** Snooze cancel control */
typedef enum e_lpm_snooze_cancel
{
    LPM_SNOOZE_CANCEL_SOURCE_NONE = 0, ///< No snooze cancel source
} lpm_snooze_cancel_t;

/** Common macro for FSP header files. There is also a corresponding FSP_HEADER macro at the top of this file. */
FSP_FOOTER

#endif
