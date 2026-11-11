/*
* Copyright (c) 2020 - 2025 Renesas Electronics Corporation and/or its affiliates
*
* SPDX-License-Identifier: BSD-3-Clause
*/

/***********************************************************************************************************************
 * Includes   <System Includes> , "Project Includes"
 **********************************************************************************************************************/
#include "bsp_api.h"

/***********************************************************************************************************************
 * Macro definitions
 **********************************************************************************************************************/

/* Key code for writing PRCR register. */
#define BSP_PRV_PRCR_KEY    (0xA500U)

/***********************************************************************************************************************
 * Typedef definitions
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Exported global variables (to be accessed by other files)
 **********************************************************************************************************************/

/***********************************************************************************************************************
 * Private global variables and functions
 **********************************************************************************************************************/

/** Used for holding reference counters for protection bits. */
volatile uint16_t g_protect_counters[4] BSP_SECTION_EARLY_INIT;

/** Masks for setting or clearing the PRCR register. Use -1 for size because PWPR in MPC is used differently. */
static const uint16_t g_prcr_masks[] =
{
    0x0001U,                           /* PRC0. */
    0x0002U,                           /* PRC1. */
    0x0008U,                           /* PRC3. */
    0x0010U,                           /* PRC4. */
};

/*******************************************************************************************************************//**
 * @addtogroup BSP_MCU
 *
 * @{
 **********************************************************************************************************************/

/*******************************************************************************************************************//**
 *        Enable register protection. Registers that are protected cannot be written to. Register protection is
 *          enabled by using the Protect Register (PRCR) and the MPC's Write-Protect Register (PWPR).
 *
 * @param[in] regs_to_protect Registers which have write protection enabled.
 **********************************************************************************************************************/
void R_BSP_RegisterProtectEnable (bsp_reg_protect_t regs_to_protect)
{
    /** Get/save the current state of interrupts */
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    /* Is it safe to disable write access? */
    if (0U != g_protect_counters[regs_to_protect])
    {
        /* Decrement the protect counter */
        g_protect_counters[regs_to_protect]--;
    }

    /* Is it safe to disable write access? */
    if (0U == g_protect_counters[regs_to_protect])
    {
        /** Enable protection using PRCR register.
         *
         * When writing to the PRCR register the upper 8-bits must be the correct key. Set lower bits to 0 to
         * disable writes. */
#if BSP_TZ_NONSECURE_BUILD && BSP_FEATURE_TZ_VERSION == 2
        R_SYSTEM->PRCR_NS = ((R_SYSTEM->PRCR_NS | BSP_PRV_PRCR_KEY) & (uint16_t) (~g_prcr_masks[regs_to_protect]));
#else
        R_SYSTEM->PRCR = ((R_SYSTEM->PRCR | BSP_PRV_PRCR_KEY) & (uint16_t) (~g_prcr_masks[regs_to_protect]));
#endif
    }

    /** Restore the interrupt state */
    FSP_CRITICAL_SECTION_EXIT;
}

/*******************************************************************************************************************//**
 *        Disable register protection. Registers that are protected cannot be written to. Register protection is
 *          disabled by using the Protect Register (PRCR) and the MPC's Write-Protect Register (PWPR).
 *
 * @param[in] regs_to_unprotect Registers which have write protection disabled.
 **********************************************************************************************************************/
void R_BSP_RegisterProtectDisable (bsp_reg_protect_t regs_to_unprotect)
{
    /** Get/save the current state of interrupts */
    FSP_CRITICAL_SECTION_DEFINE;
    FSP_CRITICAL_SECTION_ENTER;

    /* If this is first entry then disable protection. */
    if (0U == g_protect_counters[regs_to_unprotect])
    {
        /** Disable protection using PRCR register.
         *
         * When writing to the PRCR register the upper 8-bits must be the correct key. Set lower bits to 0 to
         * disable writes. */
#if BSP_TZ_NONSECURE_BUILD && BSP_FEATURE_TZ_VERSION == 2
        R_SYSTEM->PRCR_NS = ((R_SYSTEM->PRCR_NS | BSP_PRV_PRCR_KEY) | g_prcr_masks[regs_to_unprotect]);
#else
        R_SYSTEM->PRCR = ((R_SYSTEM->PRCR | BSP_PRV_PRCR_KEY) | g_prcr_masks[regs_to_unprotect]);
#endif
    }

    /** Increment the protect counter */
    g_protect_counters[regs_to_unprotect]++;

    /** Restore the interrupt state */
    FSP_CRITICAL_SECTION_EXIT;
}

/** @} (end addtogroup BSP_MCU) */
