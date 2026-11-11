/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU_RA4M1
 * @{
 **********************************************************************************************************************/

/** @} (end addtogroup BSP_MCU_RA4M1) */

#ifndef BSP_OVERRIDE_H
#define BSP_OVERRIDE_H

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Define overrides required for this MCU. */
#define BSP_OVERRIDE_LPM_SNOOZE_REQUEST_T

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/** Snooze request sources */
typedef enum e_lpm_snooze_request
{
    LPM_SNOOZE_REQUEST_RXD0_FALLING   = 0x00000000ULL, ///< Enable RXD0 falling edge snooze request
    LPM_SNOOZE_REQUEST_IRQ0           = 0x00000001ULL, ///< Enable IRQ0 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ1           = 0x00000002ULL, ///< Enable IRQ1 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ2           = 0x00000004ULL, ///< Enable IRQ2 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ3           = 0x00000008ULL, ///< Enable IRQ3 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ4           = 0x00000010ULL, ///< Enable IRQ4 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ5           = 0x00000020ULL, ///< Enable IRQ5 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ6           = 0x00000040ULL, ///< Enable IRQ6 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ7           = 0x00000080ULL, ///< Enable IRQ7 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ8           = 0x00000100ULL, ///< Enable IRQ8 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ9           = 0x00000200ULL, ///< Enable IRQ9 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ10          = 0x00000400ULL, ///< Enable IRQ10 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ11          = 0x00000800ULL, ///< Enable IRQ11 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ12          = 0x00001000ULL, ///< Enable IRQ12 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ14          = 0x00004000ULL, ///< Enable IRQ14 pin snooze request
    LPM_SNOOZE_REQUEST_IRQ15          = 0x00008000ULL, ///< Enable IRQ15 pin snooze request
    LPM_SNOOZE_REQUEST_KEY            = 0x00020000ULL, ///< Enable KR snooze request
    LPM_SNOOZE_REQUEST_ACMPLP0        = 0x00800000ULL, ///< Enable Low-speed analog comparator 0 snooze request
    LPM_SNOOZE_REQUEST_RTC_ALARM      = 0x01000000ULL, ///< Enable RTC alarm snooze request
    LPM_SNOOZE_REQUEST_RTC_PERIOD     = 0x02000000ULL, ///< Enable RTC period snooze request
    LPM_SNOOZE_REQUEST_AGT1_UNDERFLOW = 0x10000000ULL, ///< Enable AGT1 underflow snooze request
    LPM_SNOOZE_REQUEST_AGT1_COMPARE_A = 0x20000000ULL, ///< Enable AGT1 compare match A snooze request
    LPM_SNOOZE_REQUEST_AGT1_COMPARE_B = 0x40000000ULL, ///< Enable AGT1 compare match B snooze request
} lpm_snooze_request_t;

/***********************************************************************************************************************
 * Exported global variables
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global functions (to be accessed by other files)
 **********************************************************************************************************************/

#endif
