/*
 * Copyright 2022 ~ 2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#include "fsl_cmc.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.mcx_cmc"
#endif

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
#if (defined(FSL_FEATURE_MCX_CMC_HAS_SRAM_DIS_REG) && FSL_FEATURE_MCX_CMC_HAS_SRAM_DIS_REG)
#define CMC_SRAMDIS_RESERVED_MASK                                                                                   \
    (~(kCMC_RAMX0 | kCMC_RAMX1 | kCMC_RAMX2 | kCMC_RAMB | kCMC_RAMC0 | kCMC_RAMC1 | kCMC_RAMD0 | kCMC_RAMD1 |       \
       kCMC_RAME0 | kCMC_RAME1 | kCMC_RAMF0 | kCMC_RAMF1 | kCMC_RAMG0_RAMG1 | kCMC_RAMG2_RAMG3 | kCMC_RAMH0_RAMH1 | \
       kCMC_LPCAC | kCMC_DMA0_DMA1_PKC | kCMC_USB0 | kCMC_PQ | kCMC_CAN0_CAN1_ENET_USB1 | kCMC_FlexSPI))

#define CMC_SRAMRET_RESERVED_MASK (CMC_SRAMDIS_RESERVED_MASK)
#endif /* FSL_FEATURE_MCX_CMC_HAS_SRAM_DIS_REG */
/*******************************************************************************
 * Variables
 ******************************************************************************/
static uint32_t g_savedPrimask;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * brief Sets clock mode.
 *
 * This function configs the amount of clock gating when the core asserts
 * Sleeping due to WFI, WFE or SLEEPONEXIT.
 *
 * param base CMC peripheral base address.
 * param mode System clock mode.
 */
void CMC_SetClockMode(CMC_Type *base, cmc_clock_mode_t mode)
{
    uint32_t reg;

    reg = base->CKCTRL;
    reg &= ~CMC_CKCTRL_CKMODE_MASK;
    reg |= CMC_CKCTRL_CKMODE((mode));
    base->CKCTRL = reg;
}

/*!
 * brief Configures all power mode protection settings.
 *
 * This function configures the power mode protection settings for
 * supported power modes. This should be done before setting the lowPower mode
 * for each power doamin.
 *
 * The allowed lowpower modes are passed as bit map. For example, to allow
 * Sleep and DeepSleep, use CMC_SetPowerModeProtection(CMC_base, kCMC_AllowSleepMode|kCMC_AllowDeepSleepMode).
 * To allow all low power modes, use CMC_SetPowerModeProtection(CMC_base, kCMC_AllowAllLowPowerModes).
 *
 * param base CMC peripheral base address.
 * param allowedModes Bitmaps of the allowed power modes.
 */
void CMC_SetPowerModeProtection(CMC_Type *base, uint32_t allowedModes)
{
    uint32_t reg;

    reg = base->PMPROT;
    reg &= ~0xFUL;
    reg |= allowedModes;

    base->PMPROT = reg;
}

/*!
 * brief Configure reset pin.
 *
 * This function configures reset pin. When enabled, the low power filter is enabled in both
 * Active and Low power modes, the reset filter is only enabled in Active mode. When both filers
 * are enabled, they operate in series.
 *
 * param base CMC peripheral base address.
 * param config Pointer to the reset pin config structure.
 */
void CMC_ConfigResetPin(CMC_Type *base, const cmc_reset_pin_config_t *config)
{
    assert(config != NULL);

    uint32_t reg = base->RPC;

    if (config->lowpowerFilterEnable)
    {
        reg |= CMC_RPC_LPFEN_MASK;
    }
    else
    {
        reg &= ~CMC_RPC_LPFEN_MASK;
    }
    if (config->resetFilterEnable)
    {
        reg |= (CMC_RPC_FILTEN_MASK | CMC_RPC_FILTCFG(config->resetFilterWidth));
    }
    else
    {
        reg &= ~(CMC_RPC_FILTEN_MASK | CMC_RPC_FILTCFG_MASK);
    }
    base->RPC = reg;
}

#if (defined(FSL_FEATURE_MCX_CMC_HAS_SRAM_DIS_REG) && FSL_FEATURE_MCX_CMC_HAS_SRAM_DIS_REG)
/*!
 * brief Power off the selected system SRAM always.
 *
 * This function powers off the selected system SRAM always. The SRAM arrays should
 * not be accessed while they are shut down. SRAM array contents are not retained
 * if they are powered off.
 *
 * param base CMC peripheral base address.
 * param mask Bitmap of the SRAM arrays to be powered off all modes.
 */
void CMC_PowerOffSRAMAllMode(CMC_Type *base, uint32_t mask)
{
    uint32_t reg = base->SRAMDIS[0];

    reg &= ~(CMC_SRAMDIS_DIS_MASK | CMC_SRAMDIS_RESERVED_MASK);
    reg |= CMC_SRAMDIS_DIS(mask);
    base->SRAMDIS[0] = reg;
}

/*!
 * brief Power off the selected system SRAm during low power mode only.
 *
 * This function powers off the selected system SRAM only during low power mode.
 * SRAM array contents are not retained if they are power off.
 *
 * param base CMC peripheral base address.
 * param mask Bitmap of the SRAM arrays to be power off during low power mode only.
 */
void CMC_PowerOffSRAMLowPowerOnly(CMC_Type *base, uint32_t mask)
{
    uint32_t reg = base->SRAMRET[0];

    reg &= ~(CMC_SRAMRET_RET_MASK | CMC_SRAMRET_RESERVED_MASK);
    reg |= CMC_SRAMRET_RET(mask);
    base->SRAMRET[0] = reg;
}
#endif /* FSL_FEATURE_MCX_CMC_HAS_SRAM_DIS_REG */

#if (defined(FSL_FEATURE_MCX_CMC_HAS_NO_FLASHCR_WAKE) && FSL_FEATURE_MCX_CMC_HAS_NO_FLASHCR_WAKE)
/*!
 * brief Configs the low power mode of the on-chip flash memory.
 *
 * This function configs the low power mode of the on-chip flash memory.
 *
 * param base CMC peripheral base address.
 * param doze true: Flash is disabled while core is sleeping
 *             false: No effect.
 * param disable true: Flash memory is placed in low power state.
 *                false: No effect.
 */
void CMC_ConfigFlashMode(CMC_Type *base, bool doze, bool disable)
{
    uint32_t reg = 0UL;

    reg |= (disable ? CMC_FLASHCR_FLASHDIS(1U) : CMC_FLASHCR_FLASHDIS(0U)) |
           (doze ? CMC_FLASHCR_FLASHDOZE(1U) : CMC_FLASHCR_FLASHDOZE(0U));
    base->FLASHCR = reg;
}
#else
/*!
 * brief Configs the low power mode of the on-chip flash memory.
 *
 * This function config the low power mode of the on-chip flash memory.
 *
 * param base CMC peripheral base address.
 * param wake
 *          true    -   Flash will exit low power state during the flash memory accesses.
 *          false   -    No effect.
 * param doze
 *          true    -   Flash is disabled while core is sleeping
 *          false   -   No effect.
 * param disable
 *          true    -   Flash memory is placed in low power state.
 *          false   -   No effect.
 */
void CMC_ConfigFlashMode(CMC_Type *base, bool wake, bool doze, bool disable)
{
    uint32_t reg = 0UL;

    reg |= (disable ? CMC_FLASHCR_FLASHDIS(1U) : CMC_FLASHCR_FLASHDIS(0U)) |
           (doze ? CMC_FLASHCR_FLASHDOZE(1U) : CMC_FLASHCR_FLASHDOZE(0U)) |
           (wake ? CMC_FLASHCR_FLASHWAKE(1U) : CMC_FLASHCR_FLASHWAKE(0U));
    base->FLASHCR = reg;
}
#endif /* FSL_FEATURE_MCX_CMC_HAS_NO_FLASHCR_WAKE */

/*!
 * brief Prepares to enter stop modes.
 *
 * This function should be called before entering low power modes.
 *
 */
void CMC_PreEnterLowPowerMode(void)
{
    g_savedPrimask = DisableGlobalIRQ();
    __ISB();
}

/*!
 * brief Recovers after wake up from stop modes.
 *
 * This function should be called after waking up from low power modes.
 * This function should be used with CMC_PreEnterLowPowerMode()
 *
 */
void CMC_PostExitLowPowerMode(void)
{
    EnableGlobalIRQ(g_savedPrimask);
    __ISB();
}

/*!
 * brief Configs the entry into the same low power mode for each power domains.
 *
 * This function provides the feature to entry into the same low power mode for each power
 * domains. Before invoking this function, please ensure the selected power mode have been allowed.
 *
 * param base CMC peripheral base address.
 * param lowPowerMode The low power mode to be entered. See @ref cmc_low_power_mode_t for the details.
 *
 */
void CMC_GlobalEnterLowPowerMode(CMC_Type *base, cmc_low_power_mode_t lowPowerMode)
{
    /* Note: unlock the CKCTRL register if this API will be reinvoked later. */
    CMC_SetClockMode(base, kCMC_GateAllSystemClocksEnterLowPowerMode);
    CMC_SetGlobalPowerMode(base, lowPowerMode);
    /* Before executing WFI instruction read back the last register to
     * ensure all registers writes have completed. */
    (void)base->GPMCTRL;
    /* Set the core into DeepSleep mode. */
    SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
    __DSB();
    __WFI();
    __ISB();
}

/*!
 * brief Configs the entry into different low power modes for each of the power domains.
 *
 * This function provides the feature to entry into different low power modes for
 * each power domains. Before invoking this function please ensure the selected
 * modes are allowed.
 *
 * param base CMC peripheral base address.
 * param base config Pointer to the cmc_power_domain_config_t structure.
 */
void CMC_EnterLowPowerMode(CMC_Type *base, const cmc_power_domain_config_t *config)
{
    assert(config != NULL);

#if (CMC_PMCTRL_COUNT > 1U)
    /* The WAKE domain must never be configured to a lower power mode compared with main power mode. */
    assert(config->wake_domain <= config->main_domain);
#endif /* (CMC_PMCTRL_COUNT > 1U) */

    if (config->clock_mode < kCMC_GateAllSystemClocksEnterLowPowerMode)
    {
        /* In This case the power domain doesn't need to be placed in low power state. */
        /* Note: unlock the register if this API will be reinvoked later. */
        CMC_SetClockMode(base, config->clock_mode);

        CMC_SetMAINPowerMode(base, kCMC_ActiveOrSleepMode);
#if (CMC_PMCTRL_COUNT > 1U)
        CMC_SetWAKEPowerMode(base, kCMC_ActiveOrSleepMode);
#endif /* (CMC_PMCTRL_COUNT > 1U) */

        /* Before executing WFI instruction read back the last register to
         * ensure all registers writes have completed. */
        (void)base->CKCTRL;
        SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
        __DSB();
        __WFI();
        __ISB();
    }
    else
    {
        /* Note: unlock the register if this API will be reinvoked later. */
        CMC_SetClockMode(base, kCMC_GateAllSystemClocksEnterLowPowerMode);
        CMC_SetMAINPowerMode(base, config->main_domain);
#if (CMC_PMCTRL_COUNT > 1U)
        CMC_SetWAKEPowerMode(base, config->wake_domain);
#endif /* (CMC_PMCTRL_COUNT > 1U) */

        /* Before execute WFI instruction read back the last register to
         * ensure all registers writes have completed. */
#if (CMC_PMCTRL_COUNT > 1U)
        if ((CMC_GetWAKEPowerMode(base) == config->wake_domain) && (CMC_GetMAINPowerMode(base) == config->main_domain))
        {
#endif /* (CMC_PMCTRL_COUNT > 1U) */
            SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
            __DSB();
            __WFI();
            __ISB();
#if (CMC_PMCTRL_COUNT > 1U)
        }
#endif /* (CMC_PMCTRL_COUNT > 1U) */
    }
}
