/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "fsl_device_registers.h"
#include "fsl_clock_manager.h"
#include "fsl_os_abstraction.h"
#if defined(FSL_FEATURE_SOC_RTC_COUNT) && (FSL_FEATURE_SOC_RTC_COUNT)
#if defined(FSL_FEATURE_RTC_IS_IRTC) && (FSL_FEATURE_RTC_IS_IRTC)
#include "fsl_irtc_hal.h"
#else
#include "fsl_rtc_hal.h"
#endif
#endif
#include <assert.h>

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/* Macro for clock manager critical section. */
#if (USE_RTOS)
    mutex_t g_clockLock;
    #define CLOCK_SYS_LOCK_INIT()    OSA_MutexCreate(&g_clockLock)
    #define CLOCK_SYS_LOCK()         OSA_MutexLock(&g_clockLock, OSA_WAIT_FOREVER)
    #define CLOCK_SYS_UNLOCK()       OSA_MutexUnlock(&g_clockLock)
    #define CLOCK_SYS_LOCK_DEINIT()  OSA_MutexDestroy(&g_clockLock)
#else
    #define CLOCK_SYS_LOCK_INIT()    do {}while(0)
    #define CLOCK_SYS_LOCK()         do {}while(0)
    #define CLOCK_SYS_UNLOCK()       do {}while(0)
    #define CLOCK_SYS_LOCK_DEINIT()  do {}while(0)
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
static clock_manager_state_t g_clockState;

#if FSL_FEATURE_SYSTICK_HAS_EXT_REF
uint32_t CLOCK_SYS_GetSystickFreq(void)
{
    /* Use external reference clock. */
    if (!(SysTick->CTRL & SysTick_CTRL_CLKSOURCE_Msk))
    {
#if FSL_FEATURE_SYSTICK_EXT_REF_CORE_DIV
        return CLOCK_SYS_GetCoreClockFreq() / FSL_FEATURE_SYSTICK_EXT_REF_CORE_DIV;
#else
        return 0U;
#endif
    }
    else // Use core clock.
    {
        return CLOCK_SYS_GetCoreClockFreq();
    }
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_Init
 * Description   : Install pre-defined clock configurations.
 * This function installs the pre-defined clock configuration table to the
 * clock manager.
 *
 *END**************************************************************************/
clock_manager_error_code_t CLOCK_SYS_Init(clock_manager_user_config_t const **clockConfigsPtr,
                              uint8_t configsNumber,
                              clock_manager_callback_user_config_t **callbacksPtr,
                              uint8_t callbacksNumber)
{
    assert(NULL != clockConfigsPtr);
    assert(NULL != callbacksPtr);

    CLOCK_SYS_LOCK_INIT();

    g_clockState.configTable     = clockConfigsPtr;
    g_clockState.clockConfigNum  = configsNumber;
    g_clockState.callbackConfig  = callbacksPtr;
    g_clockState.callbackNum     = callbacksNumber;

    /*
     * errorCallbackIndex is the index of the callback which returns error
     * during clock mode switch. If all callbacks return success, then the
     * errorCallbackIndex is callbacksnumber.
     */
    g_clockState.errorCallbackIndex = callbacksNumber;

    return kClockManagerSuccess;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_UpdateConfiguration
 * Description   : Send notification and change system clock configuration.
 * This function sends the notification to all callback functions, if all
 * callbacks return OK or forceful policy is used, this function will change
 * system clock configuration.
 *
 *END**************************************************************************/
clock_manager_error_code_t CLOCK_SYS_UpdateConfiguration(uint8_t targetConfigIndex,
                                                   clock_manager_policy_t policy)
{
    uint8_t callbackIdx;
    clock_manager_error_code_t ret = kClockManagerSuccess;

    clock_manager_callback_user_config_t* callbackConfig;

    clock_notify_struct_t notifyStruct;
    notifyStruct.targetClockConfigIndex = targetConfigIndex;
    notifyStruct.policy                 = policy;

    /* Clock configuration index is out of range. */
    if (targetConfigIndex >= g_clockState.clockConfigNum)
    {
        return kClockManagerErrorOutOfRange;
    }

    OSA_EnterCritical(kCriticalLockSched);
    /* Set errorcallbackindex as callbackNum, which means no callback error now.*/
    g_clockState.errorCallbackIndex = g_clockState.callbackNum;

    /* First step: Send "BEFORE" notification. */
    notifyStruct.notifyType = kClockManagerNotifyBefore;

    /* Send notification to all callback. */
    for (callbackIdx=0; callbackIdx<g_clockState.callbackNum; callbackIdx++)
    {
        callbackConfig = g_clockState.callbackConfig[callbackIdx];
        if ((NULL != callbackConfig) &&
            ((uint8_t)callbackConfig->callbackType & (uint8_t)kClockManagerNotifyBefore))
        {
            if (kClockManagerSuccess !=
                    (*callbackConfig->callback)(&notifyStruct,
                        callbackConfig->callbackData))
            {
                g_clockState.errorCallbackIndex = callbackIdx;
                /* Save the error callback index. */
                ret = kClockManagerErrorNotificationBefore;

                if (kClockManagerPolicyAgreement == policy)
                {
                    break;
                }
            }
        }
    }

    /* If all callback success or forceful policy is used. */
    if ((kClockManagerSuccess == ret) ||
        (policy == kClockManagerPolicyForcible))
    {
        /* clock mode switch. */
        OSA_EnterCritical(kCriticalDisableInt);
        CLOCK_SYS_SetConfiguration(g_clockState.configTable[targetConfigIndex]);

        g_clockState.curConfigIndex = targetConfigIndex;
        OSA_ExitCritical(kCriticalDisableInt);

        notifyStruct.notifyType = kClockManagerNotifyAfter;

        for (callbackIdx=0; callbackIdx<g_clockState.callbackNum; callbackIdx++)
        {
            callbackConfig = g_clockState.callbackConfig[callbackIdx];
            if ((NULL != callbackConfig) &&
                ((uint8_t)callbackConfig->callbackType & (uint8_t)kClockManagerNotifyAfter))
            {
                if (kClockManagerSuccess !=
                        (*callbackConfig->callback)(&notifyStruct,
                            callbackConfig->callbackData))
                {
                    g_clockState.errorCallbackIndex = callbackIdx;
                    /* Save the error callback index. */
                    ret = kClockManagerErrorNotificationAfter;

                    if (kClockManagerPolicyAgreement == policy)
                    {
                        break;
                    }
                }
            }
        }
    }
    else /* Error occurs, need to send "RECOVER" notification. */
    {
        notifyStruct.notifyType = kClockManagerNotifyRecover;
        while (callbackIdx--)
        {
            callbackConfig = g_clockState.callbackConfig[callbackIdx];
            if (NULL != callbackConfig)
            {
                (*callbackConfig->callback)(&notifyStruct,
                        callbackConfig->callbackData);
            }
        }
    }

    OSA_ExitCritical(kCriticalLockSched);

    return ret;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetCurrentConfiguration
 * Description   : Get current clock configuration index.
 *
 *END**************************************************************************/
uint8_t CLOCK_SYS_GetCurrentConfiguration(void)
{
    return g_clockState.curConfigIndex;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_GetErrorCallback
 * Description   : Get the callback which returns error in last clock switch.
 *
 *END**************************************************************************/
clock_manager_callback_user_config_t* CLOCK_SYS_GetErrorCallback(void)
{
    /* If all callbacks return success. */
    if (g_clockState.errorCallbackIndex >= g_clockState.clockConfigNum)
    {
        return NULL;
    }
    else
    {
        return g_clockState.callbackConfig[g_clockState.errorCallbackIndex];
    }
}

#if (defined(FSL_FEATURE_SOC_SCG_COUNT) && FSL_FEATURE_SOC_SCG_COUNT)

#elif FSL_FEATURE_SOC_MCGLITE_COUNT
/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_SYS_SetMcgliteMode
 * Description  : Set MCG_Lite to some mode.
 * This function transitions the MCG_lite to some mode according to configuration
 * parameter.
 *
 *END***********************************************************************************/
mcglite_mode_error_t CLOCK_SYS_SetMcgliteMode(mcglite_config_t const *targetConfig)
{
    mcglite_mode_error_t ret = kMcgliteModeErrNone;

    assert(targetConfig->mcglite_mode < kMcgliteModeStop);

    /* MCG_LITE mode change. */
    switch (targetConfig->mcglite_mode)
    {
        case kMcgliteModeLirc8M:
        case kMcgliteModeLirc2M:
        case kMcgliteModeLirc:
            ret = CLOCK_HAL_SetLircMode(MCG,
                                        targetConfig->ircs,
                                        targetConfig->fcrdiv);
            break;
        case kMcgliteModeExt:
            ret = CLOCK_HAL_SetExtMode(MCG);
            break;
        default:
            ret = CLOCK_HAL_SetHircMode(MCG);
            break;
    }

    /* Set other registers. */
    if (kMcgliteModeErrNone == ret)
    {
        /* Enable HIRC when MCG_LITE is not in HIRC mode. */
        CLOCK_HAL_SetHircCmd(MCG, targetConfig->hircEnableInNotHircMode);

        /* Enable IRCLK. */
        CLOCK_HAL_SetLircCmd(MCG, targetConfig->irclkEnable);
        CLOCK_HAL_SetLircStopCmd(MCG, targetConfig->irclkEnableInStop);

        /* Set IRCS. */
        CLOCK_HAL_SetLircSelMode(MCG, targetConfig->ircs);

        /* Set LIRC_DIV2. */
        CLOCK_HAL_SetLircDiv2(MCG, targetConfig->lircDiv2);
    }

    return ret;
}
#else

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_SYS_FllStableDelay
 * Description  : Function to delay at list 1 ms to wait FLL stable.
 *
 *END***********************************************************************************/
static void CLOCK_SYS_FllStableDelay(void)
{
    uint32_t i = 30000U;
    while (i--)
    {
        __asm("nop");
    }
}

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_SYS_BootToFee
 * Description  : This function is used to set MCG to FEE mode when boot up.
 *
 *END***********************************************************************************/
mcg_mode_error_t CLOCK_SYS_BootToFee(const mcg_config_t * config)
{
    mcg_mode_error_t errorCode;

#if FSL_FEATURE_MCG_USE_OSCSEL
    mcg_oscsel_select_t oscsel = config->oscsel;
#else
    mcg_oscsel_select_t oscsel = kMcgOscselOsc;
#endif

    // Set to PEE mode.
#if (defined(FSL_FEATURE_MCG_RESET_IS_BLPI) && FSL_FEATURE_MCG_RESET_IS_BLPI)
    // If reset mode is BLPI, first disable LP to enter FBI mode.
    CLOCK_HAL_SetLowPowerModeCmd(MCG, false);
#endif
    errorCode = CLOCK_HAL_SetFeeMode(MCG, oscsel, config->frdiv,
                                     config->dmx32, config->drs,
                                     CLOCK_SYS_FllStableDelay);

    if (kMcgModeErrNone == errorCode)
    {
        return errorCode;
    }

#if FSL_FEATURE_MCG_HAS_PLL
    // Check if need to enable PLL.
    if (config->pll0EnableInFllMode)
    {
#if (FSL_FEATURE_MCG_HAS_PLL_PRDIV && FSL_FEATURE_MCG_HAS_PLL_VDIV)
        CLOCK_HAL_EnablePll0InFllMode(MCG, config->prdiv0, config->vdiv0, config->pll0EnableInFllMode);
#else
        CLOCK_HAL_EnablePll0InFllMode(MCG, config->pll0EnableInFllMode);
#endif
    }

#if FSL_FEATURE_MCG_HAS_PLL1
    // Check if need to enable PLL1.
    if (config->pll1EnableInFllMode)
    {
        CLOCK_HAL_EnablePll1InFllMode(MCG, config->prdiv1, config->vdiv1, config->pll1EnableInFllMode);
    }
#endif
#endif

    // Set MCGIRCLK.
    if (config->irclkEnable)
    {
        CLOCK_HAL_UpdateInternalRefClk(MCG,
                                       config->ircs,
                                       config->fcrdiv,
                                       config->irclkEnableInStop);
    }

    return errorCode;
}

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_SYS_BootToFei
 * Description  : This function is used to set MCG to FEI mode when boot up.
 *
 *END***********************************************************************************/
mcg_mode_error_t CLOCK_SYS_BootToFei(const mcg_config_t * config)
{
    mcg_mode_error_t errorCode;

#if (defined(FSL_FEATURE_MCG_RESET_IS_BLPI) && FSL_FEATURE_MCG_RESET_IS_BLPI)
    // If reset mode is BLPI, first disable LP to enter FBI mode.
    CLOCK_HAL_SetLowPowerModeCmd(MCG, false);
#endif
    // Set to FEI mode.
    errorCode = CLOCK_HAL_SetFeiMode(MCG, config->drs, CLOCK_SYS_FllStableDelay);

    if (kMcgModeErrNone == errorCode)
    {
        return errorCode;
    }

#if FSL_FEATURE_MCG_HAS_PLL
    // Check if need to enable PLL.
    if (config->pll0EnableInFllMode)
    {
#if (FSL_FEATURE_MCG_HAS_PLL_PRDIV && FSL_FEATURE_MCG_HAS_PLL_VDIV)
        CLOCK_HAL_EnablePll0InFllMode(MCG, config->prdiv0, config->vdiv0, config->pll0EnableInFllMode);
#else
        CLOCK_HAL_EnablePll0InFllMode(MCG, config->pll0EnableInFllMode);
#endif
    }

#if FSL_FEATURE_MCG_HAS_PLL1
    // Check if need to enable PLL1.
    if (config->pll1EnableInFllMode)
    {
        CLOCK_HAL_EnablePll1InFllMode(MCG, config->prdiv1, config->vdiv1, config->pll1EnableInFllMode);
    }
#endif
#endif

    // Set MCGIRCLK.
    if (config->irclkEnable)
    {
        CLOCK_HAL_UpdateInternalRefClk(MCG,
                                       config->ircs,
                                       config->fcrdiv,
                                       config->irclkEnableInStop);
    }

    return errorCode;
}

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_SYS_BootToBlpi
 * Description  : This function is used to set MCG to BLPI mode when boot up.
 *
 *END***********************************************************************************/
mcg_mode_error_t CLOCK_SYS_BootToBlpi(const mcg_config_t * config)
{
    mcg_mode_error_t errorCode;

#if !(defined(FSL_FEATURE_MCG_RESET_IS_BLPI) && FSL_FEATURE_MCG_RESET_IS_BLPI)
    /* Set MCG_C1[CLKS] to change to FBI mode. */
    CLOCK_HAL_SetClkOutSrc(MCG, kMcgClkOutSrcInternal);
    while (CLOCK_HAL_GetClkOutStat(MCG) != kMcgClkOutStatInternal){}
#endif

    /* Change to Blpi mode. */
    errorCode = CLOCK_HAL_SetBlpiMode(MCG, config->fcrdiv, config->ircs);

    if (kMcgModeErrNone == errorCode)
    {
        /* Enable or disalbe IRCLK output. */
        CLOCK_HAL_SetInternalRefClkEnableCmd(MCG, config->irclkEnable);
        CLOCK_HAL_SetInternalRefClkEnableInStopCmd(MCG, config->irclkEnableInStop);
    }

    return errorCode;
}

/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_SYS_BootToBlpe
 * Description  : This function is used to set MCG to BLPE mode when boot up.
 *
 *END***********************************************************************************/
mcg_mode_error_t CLOCK_SYS_BootToBlpe(const mcg_config_t * config)
{
#if (defined(FSL_FEATURE_MCG_RESET_IS_BLPI) && FSL_FEATURE_MCG_RESET_IS_BLPI)
    // If reset mode is BLPI, first disable LP to enter FBI mode.
    CLOCK_HAL_SetLowPowerModeCmd(MCG, false);
#endif

    // First prepare the external OSC clock.
#if FSL_FEATURE_MCG_USE_OSCSEL
    CLOCK_HAL_PrepareOsc(MCG, config->oscsel);
#else
    CLOCK_HAL_PrepareOsc(MCG, kMcgOscselOsc);
#endif

    // Set to FBE mode.
    CLOCK_HAL_SetClksFrdivIrefs(MCG, kMcgClkOutSrcExternal,
                                     config->frdiv,
                                     kMcgFllSrcExternal);

    while (kMcgFllSrcExternal != CLOCK_HAL_GetFllSrc(MCG)) {}
    while (kMcgClkOutStatExternal != CLOCK_HAL_GetClkOutStat(MCG)) {}

    // In FBE now, start to enter BLPE.
    CLOCK_HAL_SetLowPowerModeCmd(MCG, true);

    // Set MCGIRCLK.
    if (config->irclkEnable)
    {
        CLOCK_HAL_UpdateInternalRefClk(MCG,
                                       config->ircs,
                                       config->fcrdiv,
                                       config->irclkEnableInStop);
    }

    return kMcgModeErrNone;
}

#if FSL_FEATURE_MCG_HAS_PLL
/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_SYS_BootToPee
 * Description  : This function is used to set MCG to PEE mode when boot up.
 *
 *END***********************************************************************************/
mcg_mode_error_t CLOCK_SYS_BootToPee(const mcg_config_t * config)
{
    mcg_mode_error_t errorCode;

#if (defined(FSL_FEATURE_MCG_RESET_IS_BLPI) && FSL_FEATURE_MCG_RESET_IS_BLPI)
    /*If reset mode is BLPI, first disable LP to enter FBI mode. */
    CLOCK_HAL_SetLowPowerModeCmd(MCG, false);
#endif

#if FSL_FEATURE_MCG_HAS_PLL1
    mcg_pll_clk_select_t pllcs = config->pllcs;
#elif !(defined(FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE) && FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE)
    mcg_pll_clk_select_t pllcs = kMcgPllClkSelPll0;
#endif

#if FSL_FEATURE_MCG_USE_OSCSEL
    mcg_oscsel_select_t oscsel = config->oscsel;
#else
    mcg_oscsel_select_t oscsel = kMcgOscselOsc;
#endif

    // First prepare the external OSC clock.
    CLOCK_HAL_PrepareOsc(MCG, oscsel);

    // Set to FBE mode.
    CLOCK_HAL_SetClksFrdivIrefs(MCG, kMcgClkOutSrcExternal,
                                     config->frdiv,
                                     kMcgFllSrcExternal);

    while (kMcgFllSrcExternal != CLOCK_HAL_GetFllSrc(MCG)) {}
    while (kMcgClkOutStatExternal != CLOCK_HAL_GetClkOutStat(MCG)) {}

    // Set to PBE mode.
#if FSL_FEATURE_MCG_HAS_PLL1
    if (kMcgPllClkSelPll0 == pllcs)
    {
        errorCode = CLOCK_HAL_SetPbeMode(MCG, oscsel, pllcs, config->prdiv1, config->vdiv1);
    }
    else
    {
        errorCode = CLOCK_HAL_SetPbeMode(MCG, oscsel, pllcs, config->prdiv0, config->vdiv0);
    }
#else
#if (defined(FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE) && FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE)
    errorCode = CLOCK_HAL_SetPbeMode(MCG, oscsel, config->pllRef, config->frdiv);
#else
    errorCode = CLOCK_HAL_SetPbeMode(MCG, oscsel, pllcs, config->prdiv0, config->vdiv0);
#endif
#endif

    // Change to PEE mode.
    if (kMcgModeErrNone == errorCode)
    {
        CLOCK_HAL_SetClkOutSrc(MCG, kMcgClkOutSrcOut);
        while (CLOCK_HAL_GetClkOutStat(MCG) != kMcgClkOutStatPll) {}

        // Set MCGIRCLK.
        if (config->irclkEnable)
        {
            CLOCK_HAL_UpdateInternalRefClk(MCG,
                                           config->ircs,
                                           config->fcrdiv,
                                           config->irclkEnableInStop);
        }
    }

    return errorCode;
}

#if (defined(FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE) && FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE)
/*FUNCTION******************************************************************************
 *
 * Functon name : CLOCK_SYS_BootToPei
 * Description  : This function is used to set MCG to PEI mode when boot up.
 *
 *END***********************************************************************************/
mcg_mode_error_t CLOCK_SYS_BootToPei(const mcg_config_t * config)
{
    // Set to PBI mode and prepare the PLL.
    CLOCK_HAL_SetPbiMode(MCG, config->ircs, config->fcrdiv);

    // Switch to PEI mode.
    CLOCK_HAL_SetPeiMode(MCG);

    return kMcgModeErrNone;
}
#endif

#endif

/* The index definition in mcgModeMatrix. */
#define MCG_MATRIX_FEI  0U
#define MCG_MATRIX_FBI  1U
#define MCG_MATRIX_BLPI 2U
#define MCG_MATRIX_FEE  3U
#define MCG_MATRIX_FBE  4U
#define MCG_MATRIX_BLPE 5U
#define MCG_MATRIX_PBE  6U
#define MCG_MATRIX_PEE  7U
#define MCG_MATRTX_PEI  8U
#define MCG_MATRTX_PBI  9U

/*
 * The transaction matrix. It defines the path for mode switch, the row is for
 * current mode and the column is target mode.
 * For example, switch from FEI to PEE:
 * 1. Current mode FEI, next mode is mcgModeMatrix[FEI][PEE] = FBE, so swith to FBE.
 * 2. Current mode FBE, next mode is mcgModeMatrix[FBE][PEE] = PBE, so swith to PBE.
 * 3. Current mode PBE, next mode is mcgModeMatrix[PBE][PEE] = PEE, so swith to PEE.
 * Thus the MCG mode has changed from FEI to PEE.
 */
#if FSL_FEATURE_MCG_HAS_PLL
#if (defined(FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE) && FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE)
static const uint8_t mcgModeMatrix[10][10] = {
  { MCG_MATRIX_FEI,  MCG_MATRIX_FBI,  MCG_MATRIX_FBI,  MCG_MATRIX_FEE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE, MCG_MATRIX_FBI,  MCG_MATRIX_FBI }, /* FEI */
  { MCG_MATRIX_FEI,  MCG_MATRIX_FBI,  MCG_MATRIX_BLPI, MCG_MATRIX_FEE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE, MCG_MATRIX_FBI,  MCG_MATRIX_FBI }, /* FBI */
  { MCG_MATRIX_FBI,  MCG_MATRIX_FBI,  MCG_MATRIX_BLPI, MCG_MATRIX_FBI,  MCG_MATRIX_FBI,  MCG_MATRIX_FBI,  MCG_MATRIX_FBI,  MCG_MATRIX_FBI, MCG_MATRIX_FBI,  MCG_MATRIX_FBI }, /* BLPI */
  { MCG_MATRIX_FEI,  MCG_MATRIX_FBI,  MCG_MATRIX_FBI,  MCG_MATRIX_FEE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE, MCG_MATRIX_FBI,  MCG_MATRIX_FBI }, /* FEE */
  { MCG_MATRIX_FEI,  MCG_MATRIX_FBI,  MCG_MATRIX_FBI,  MCG_MATRIX_FEE,  MCG_MATRIX_FBE,  MCG_MATRIX_BLPE, MCG_MATRIX_PBE,  MCG_MATRIX_PBE, MCG_MATRIX_FBI,  MCG_MATRIX_FBI }, /* FBE */
  { MCG_MATRIX_FBE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE,  MCG_MATRIX_BLPE, MCG_MATRIX_PBE,  MCG_MATRIX_PBE, MCG_MATRIX_FBE,  MCG_MATRIX_FBE }, /* BLPE */
  { MCG_MATRIX_FBE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE,  MCG_MATRIX_BLPE, MCG_MATRIX_PBE,  MCG_MATRIX_PEE, MCG_MATRIX_FBE,  MCG_MATRIX_FBE }, /* PBE */
  { MCG_MATRIX_PBE,  MCG_MATRIX_PBE,  MCG_MATRIX_PBE,  MCG_MATRIX_PBE,  MCG_MATRIX_PBE,  MCG_MATRIX_PBE,  MCG_MATRIX_PBE,  MCG_MATRIX_PBE, MCG_MATRIX_PBE,  MCG_MATRIX_PBE }, /* PEE */
  { MCG_MATRIX_FBI,  MCG_MATRIX_FBI,  MCG_MATRIX_FBI,  MCG_MATRIX_FBI,  MCG_MATRIX_FBI,  MCG_MATRIX_FBI,  MCG_MATRIX_FBI,  MCG_MATRIX_FBI, MCG_MATRIX_FBI,  MCG_MATRIX_FBI },/* PEI */
  { MCG_MATRIX_FBI,  MCG_MATRIX_FBI,  MCG_MATRIX_BLPI, MCG_MATRIX_FBI,  MCG_MATRIX_FBI,  MCG_MATRIX_FBI,  MCG_MATRIX_FBI,  MCG_MATRIX_FBI, MCG_MATRTX_PEI,  MCG_MATRIX_FBI}  /* PBI */
/*      FEI           FBI           BLPI          FEE           FBE           BLPE          PBE           PEE          PEI           PBI       */
};
#else
static const uint8_t mcgModeMatrix[8][8] = {
  { MCG_MATRIX_FEI,  MCG_MATRIX_FBI,  MCG_MATRIX_FBI,  MCG_MATRIX_FEE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE  }, /* FEI */
  { MCG_MATRIX_FEI,  MCG_MATRIX_FBI,  MCG_MATRIX_BLPI, MCG_MATRIX_FEE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE  }, /* FBI */
  { MCG_MATRIX_FBI,  MCG_MATRIX_FBI,  MCG_MATRIX_BLPI, MCG_MATRIX_FBI,  MCG_MATRIX_FBI,  MCG_MATRIX_FBI,  MCG_MATRIX_FBI,  MCG_MATRIX_FBI  }, /* BLPI */
  { MCG_MATRIX_FEI,  MCG_MATRIX_FBI,  MCG_MATRIX_FBI,  MCG_MATRIX_FEE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE  }, /* FEE */
  { MCG_MATRIX_FEI,  MCG_MATRIX_FBI,  MCG_MATRIX_FBI,  MCG_MATRIX_FEE,  MCG_MATRIX_FBE,  MCG_MATRIX_BLPE, MCG_MATRIX_PBE,  MCG_MATRIX_PBE  }, /* FBE */
  { MCG_MATRIX_FBE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE,  MCG_MATRIX_BLPE, MCG_MATRIX_PBE,  MCG_MATRIX_PBE  }, /* BLPE */
  { MCG_MATRIX_FBE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE,  MCG_MATRIX_BLPE, MCG_MATRIX_PBE,  MCG_MATRIX_PEE  }, /* PBE */
  { MCG_MATRIX_PBE,  MCG_MATRIX_PBE,  MCG_MATRIX_PBE,  MCG_MATRIX_PBE,  MCG_MATRIX_PBE,  MCG_MATRIX_PBE,  MCG_MATRIX_PBE,  MCG_MATRIX_PBE  }  /* PEE */
/*        FEI              FBI              BLPI             FEE              FBE              BLPE             PBE              PEE       */
};
#endif
#else
static const uint8_t mcgModeMatrix[6][6] = {
  { MCG_MATRIX_FEI,  MCG_MATRIX_FBI,  MCG_MATRIX_FBI,  MCG_MATRIX_FEE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE   }, /* FEI */
  { MCG_MATRIX_FEI,  MCG_MATRIX_FBI,  MCG_MATRIX_BLPI, MCG_MATRIX_FEE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE   }, /* FBI */
  { MCG_MATRIX_FBI,  MCG_MATRIX_FBI,  MCG_MATRIX_BLPI, MCG_MATRIX_FBI,  MCG_MATRIX_FBI,  MCG_MATRIX_FBI   }, /* BLPI */
  { MCG_MATRIX_FEI,  MCG_MATRIX_FBI,  MCG_MATRIX_FBI,  MCG_MATRIX_FEE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE   }, /* FEE */
  { MCG_MATRIX_FEI,  MCG_MATRIX_FBI,  MCG_MATRIX_FBI,  MCG_MATRIX_FEE,  MCG_MATRIX_FBE,  MCG_MATRIX_BLPE  }, /* FBE */
  { MCG_MATRIX_FBE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE,  MCG_MATRIX_FBE,  MCG_MATRIX_BLPE  }, /* BLPE */
/*        FEI              FBI              BLPI             FEE              FBE              BLPE      */
};
#endif

/*FUNCTION******************************************************************************
 *
 * Function name : CLOCK_SYS_McgModeToIdx
 * Description  : This function transfers the mcg_modes_t to the index of MCG matrix index.
 *
 *END***********************************************************************************/
static uint8_t CLOCK_SYS_McgModeToIdx(mcg_modes_t mode)
{
    uint8_t idx = 0U;
    assert(mode < kMcgModeSTOP);

    while(!(((uint32_t)mode) & (1U << idx)))
    {
        idx ++;
    }

    return idx;
}

/*FUNCTION******************************************************************************
 *
 * Function name : CLOCK_SYS_SetMcgMode
 * Description  : This function sets MCG to some target mode defined by the configure
 * structure, if can not switch to target mode directly, this function will choose
 * the proper path. If external clock is used in the target mode, please make sure
 * it is enabled, for example, if the external oscillator is used, please setup EREFS/HGO
 * correctly and make sure OSCINIT is set.
 *
 *END***********************************************************************************/
mcg_mode_error_t CLOCK_SYS_SetMcgMode(mcg_config_t const *targetConfig)
{
    uint8_t matrixIdx, matrixIdxTarget;

#if FSL_FEATURE_MCG_USE_OSCSEL
    mcg_oscsel_select_t oscsel = targetConfig->oscsel;
#else
    mcg_oscsel_select_t oscsel = kMcgOscselOsc;
#endif
#if FSL_FEATURE_MCG_HAS_PLL
#if (FSL_FEATURE_MCG_HAS_PLL1 || FSL_FEATURE_MCG_HAS_EXTERNAL_PLL)
    mcg_pll_clk_select_t pllcs = targetConfig->pllcs;
#elif !(defined(FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE) && FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE)
    mcg_pll_clk_select_t pllcs = kMcgPllClkSelPll0;
#endif
#endif

    matrixIdx       = CLOCK_SYS_McgModeToIdx(CLOCK_HAL_GetMcgMode(MCG));
    matrixIdxTarget = CLOCK_SYS_McgModeToIdx(targetConfig->mcg_mode);

    do {
        matrixIdx = mcgModeMatrix[matrixIdx][matrixIdxTarget];

        switch (matrixIdx)
        {
            case MCG_MATRIX_FEI:
                CLOCK_HAL_SetFeiMode(MCG, targetConfig->drs, CLOCK_SYS_FllStableDelay);
                break;
            case MCG_MATRIX_FEE:
                CLOCK_HAL_SetFeeMode(MCG, oscsel, targetConfig->frdiv, targetConfig->dmx32,
                                     targetConfig->drs, CLOCK_SYS_FllStableDelay);
                break;
            case MCG_MATRIX_FBI:
                CLOCK_HAL_SetFbiMode(MCG, targetConfig->drs, targetConfig->ircs,
                                     targetConfig->fcrdiv, NULL);
                break;
            case MCG_MATRIX_FBE:
                CLOCK_HAL_SetFbeMode(MCG, oscsel, targetConfig->frdiv, targetConfig->dmx32,
                                     targetConfig->drs, NULL);
                break;
            case MCG_MATRIX_BLPI:
                CLOCK_HAL_SetBlpiMode(MCG, targetConfig->fcrdiv, targetConfig->ircs);
                break;
            case MCG_MATRIX_BLPE:
                CLOCK_HAL_SetBlpeMode(MCG, oscsel);
                break;
#if FSL_FEATURE_MCG_HAS_PLL
            case MCG_MATRIX_PBE:
#if (defined(FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE) && FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE)
                CLOCK_HAL_SetPbeMode(MCG, oscsel, targetConfig->pllRef, targetConfig->frdiv);
#else
                // If target mode is not PBE or PEE, then only need to set CLKS = EXT here.
                if ((MCG_MATRIX_PEE == matrixIdxTarget) || (MCG_MATRIX_PBE == matrixIdxTarget))
                {

#if FSL_FEATURE_MCG_HAS_PLL1
                    if (kMcgPllClkSelPll0 == pllcs)
                    {
                        CLOCK_HAL_SetPbeMode(MCG, oscsel, pllcs, targetConfig->prdiv0, targetConfig->vdiv0);
                    }
                    else
                    {
                        CLOCK_HAL_SetPbeMode(MCG, oscsel, pllcs, targetConfig->prdiv1, targetConfig->vdiv1);
                    }
#else
                    CLOCK_HAL_SetPbeMode(MCG, oscsel, pllcs, targetConfig->prdiv0, targetConfig->vdiv0);
#endif
                }
                else
                {
                    CLOCK_HAL_SetClkOutSrc(MCG, kMcgClkOutSrcExternal);
                    while (CLOCK_HAL_GetClkOutStat(MCG) != kMcgClkOutStatExternal){}
                }
#endif //FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE
                break;
            case MCG_MATRIX_PEE:
                CLOCK_HAL_SetPeeMode(MCG);
                break;
#if (defined(FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE) && FSL_FEATURE_MCG_HAS_PLL_INTERNAL_MODE)
            case MCG_MATRTX_PBI:
                CLOCK_HAL_SetPbiMode(MCG, targetConfig->ircs, targetConfig->fcrdiv);
                break;
            case MCG_MATRTX_PEI:
                CLOCK_HAL_SetPeiMode(MCG);
                break;
#endif
#endif
            default:
                break;
        }
    } while (matrixIdx != matrixIdxTarget);

    /* Enable MCGIRCLK. */
    CLOCK_HAL_SetInternalRefClkEnableCmd(MCG, targetConfig->irclkEnable);
    CLOCK_HAL_SetInternalRefClkEnableInStopCmd(MCG, targetConfig->irclkEnableInStop);

    /* Configure MCGIRCLK. */
    if (targetConfig->irclkEnable)
    {
        if (kMcgIrcFast == targetConfig->ircs)
        {
            /* Update FCRDIV if necessary. */
            CLOCK_HAL_UpdateFastClkInternalRefDiv(MCG, targetConfig->fcrdiv);
        }

        CLOCK_HAL_SetInternalRefClkMode(MCG, targetConfig->ircs);
        while (targetConfig->ircs != CLOCK_HAL_GetInternalRefClkMode(MCG)) {}
    }

#if FSL_FEATURE_MCG_HAS_PLL
    /* Enable PLL0. */
    if (targetConfig->pll0EnableInFllMode)
    {
#if (FSL_FEATURE_MCG_HAS_PLL_PRDIV && FSL_FEATURE_MCG_HAS_PLL_VDIV)
        CLOCK_HAL_EnablePll0InFllMode(MCG,
                                      targetConfig->prdiv0,
                                      targetConfig->vdiv0,
                                      targetConfig->pll0EnableInStop);
#else
		CLOCK_HAL_EnablePll0InFllMode(MCG, targetConfig->pll0EnableInFllMode);
#endif
    }
    else
    {
        CLOCK_HAL_SetPll0EnableCmd(MCG, false);
    }
#endif

    return kMcgModeErrNone;
}

#endif

#if (defined(FSL_FEATURE_SOC_SCG_COUNT) && FSL_FEATURE_SOC_SCG_COUNT) // USE_SCG

#else

#if FSL_FEATURE_SOC_MCGLITE_COUNT

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_OscInit
 * Description   : Initialize OSC.
 *
 * This function initializes OSC according to configuration.
 *
 *END**************************************************************************/
clock_manager_error_code_t CLOCK_SYS_OscInit(uint32_t instance,
                                             osc_user_config_t *config)
{
    assert(instance < OSC_INSTANCE_COUNT);
    uint32_t capacitorMask = 0U;

    if (kOscSrcOsc == config->erefs) /* oscillator is used. */
    {
        capacitorMask = (config->enableCapacitor2p   ? kOscCapacitor2p   : 0U) |
                        (config->enableCapacitor4p   ? kOscCapacitor4p   : 0U) |
                        (config->enableCapacitor8p   ? kOscCapacitor8p   : 0U) |
                        (config->enableCapacitor16p  ? kOscCapacitor16p  : 0U);
        OSC_HAL_SetCapacitor(g_oscBase[instance], capacitorMask);
    }

#if FSL_FEATURE_MCGLITE_HAS_RANGE0
    CLOCK_HAL_SetRange0Mode(MCG, config->range);
#endif
#if FSL_FEATURE_MCGLITE_HAS_HGO0
    CLOCK_HAL_SetHighGainOsc0Mode(MCG, config->hgo);
#endif
    CLOCK_HAL_SetExtRefSelMode0(MCG, config->erefs);

    CLOCK_SYS_SetOscerConfigration(instance, &(config->oscerConfig));

    /* oscillator is used. */
    if ((kOscSrcOsc == config->erefs) &&
        (true == config->oscerConfig.enable))
    {
        while(!CLOCK_HAL_IsOscStable(MCG)){}
    }

    g_xtal0ClkFreq = config->freq;

    return kClockManagerSuccess;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_OscDeinit
 * Description   : Deinitialize OSC.
 *
 *END**************************************************************************/
void CLOCK_SYS_OscDeinit(uint32_t instance)
{
    assert(instance < OSC_INSTANCE_COUNT);

    OSC_HAL_SetExternalRefClkInStopModeCmd(g_oscBase[instance], false);
    OSC_HAL_SetExternalRefClkCmd(g_oscBase[instance], false);
    CLOCK_HAL_SetExtRefSelMode0(MCG, kOscSrcExt);
#if FSL_FEATURE_MCGLITE_HAS_RANGE0
    CLOCK_HAL_SetRange0Mode(MCG, kOscRangeLow);
#endif
#if FSL_FEATURE_MCGLITE_HAS_HGO0
    CLOCK_HAL_SetHighGainOsc0Mode(MCG, kOscGainLow);
#endif

    g_xtal0ClkFreq = 0U;
}

#else // Use MCG

#if FSL_FEATURE_SOC_OSC_COUNT

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_OscInit
 * Description   : Initialize OSC.
 *
 * This function initializes OSC according to configuration.
 *
 *END**************************************************************************/
clock_manager_error_code_t CLOCK_SYS_OscInit(uint32_t instance,
                                             osc_user_config_t *config)
{
    assert(instance < OSC_INSTANCE_COUNT);
    uint32_t capacitorMask = 0U;

    if (kOscSrcOsc == config->erefs) /* oscillator is used. */
    {
        capacitorMask = (config->enableCapacitor2p   ? kOscCapacitor2p   : 0U) |
                        (config->enableCapacitor4p   ? kOscCapacitor4p   : 0U) |
                        (config->enableCapacitor8p   ? kOscCapacitor8p   : 0U) |
                        (config->enableCapacitor16p  ? kOscCapacitor16p  : 0U);
        OSC_HAL_SetCapacitor(g_oscBase[instance], capacitorMask);
    }

    CLOCK_SYS_SetOscerConfigration(instance, &(config->oscerConfig));

#if (defined(FSL_FEATURE_MCG_HAS_OSC1) && (1U == FSL_FEATURE_MCG_HAS_OSC1))
    if (0U == instance)
    {
#endif
        CLOCK_HAL_SetOsc0Mode(MCG, config->range, config->hgo, config->erefs);

        /* oscillator is used. */
        if ((kOscSrcOsc == config->erefs) &&
            (true == config->oscerConfig.enable))
        {
            while(!CLOCK_HAL_IsOsc0Stable(MCG)){}
        }
        g_xtal0ClkFreq = config->freq;
#if (defined(FSL_FEATURE_MCG_HAS_OSC1) && (1U == FSL_FEATURE_MCG_HAS_OSC1))
    }
    else
    {
        CLOCK_HAL_SetOsc1Mode(MCG, config->range, config->hgo, config->erefs);

        /* oscillator is used. */
        if ((kOscSrcOsc == config->erefs) &&
            (true == config->oscerConfig.enable))
        {
            while(!CLOCK_HAL_IsOsc1Stable(MCG)){}
        }
        g_xtal1ClkFreq = config->freq;
    }
#endif

    return kClockManagerSuccess;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_OscDeinit
 * Description   : Deinitialize OSC.
 *
 *END**************************************************************************/
void CLOCK_SYS_OscDeinit(uint32_t instance)
{
    assert(instance < OSC_INSTANCE_COUNT);
    OSC_HAL_SetExternalRefClkInStopModeCmd(g_oscBase[instance], false);
    OSC_HAL_SetExternalRefClkCmd(g_oscBase[instance], false);

#if (defined(FSL_FEATURE_MCG_HAS_OSC1) && (1U == FSL_FEATURE_MCG_HAS_OSC1))
    if (0U == instance)
    {
#endif
        CLOCK_HAL_SetOsc0Mode(MCG,
                              kOscRangeLow,
                              kOscGainLow,
                              kOscSrcExt);
        g_xtal0ClkFreq = 0U;
#if (defined(FSL_FEATURE_MCG_HAS_OSC1) && (1U == FSL_FEATURE_MCG_HAS_OSC1))
    }
    else
    {
        CLOCK_HAL_SetOsc1Mode(MCG,
                              kOscRangeLow,
                              kOscGainLow,
                              kOscSrcExt);
        g_xtal1ClkFreq = 0U;
    }
#endif
}

#endif

#endif

#if FSL_FEATURE_SOC_OSC_COUNT
/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_SetOscerConfigration
 * Description   : This funtion sets the OSCERCLK for clock transition.
 *
 *END**************************************************************************/
void CLOCK_SYS_SetOscerConfigration(uint32_t instance, oscer_config_t const *config)
{
#if FSL_FEATURE_OSC_HAS_EXT_REF_CLOCK_DIVIDER
    OSC_HAL_SetExternalRefClkDiv(g_oscBase[instance],
                                 config->erclkDiv);
#endif

#if FSL_FEATURE_SOC_OSC_COUNT
    OSC_HAL_SetExternalRefClkCmd(g_oscBase[instance],
                                 config->enable);

    OSC_HAL_SetExternalRefClkInStopModeCmd(g_oscBase[instance],
                                           config->enableInStop);
#endif

}
#endif
#endif

#if defined(FSL_FEATURE_SOC_RTC_COUNT) && (FSL_FEATURE_SOC_RTC_COUNT)
/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_RtcOscInit
 * Description   : This funtion initializes the RTC OSC.
 *
 *END**************************************************************************/
clock_manager_error_code_t CLOCK_SYS_RtcOscInit(uint32_t instance,
                                                rtc_osc_user_config_t *config)
{
    assert(instance < RTC_INSTANCE_COUNT);

    CLOCK_SYS_EnableRtcClock(instance);
    g_xtalRtcClkFreq = config->freq;

#if defined(FSL_FEATURE_RTC_IS_IRTC) && (FSL_FEATURE_RTC_IS_IRTC)
    uint16_t rtcGpDataRagVal = 0; // RTC_GP_DATA_REG register value.

    rtcGpDataRagVal = RTC_RD_GP_DATA_REG(RTC);

    // If the oscillator is not enabled and should be enabled.
    if (((rtcGpDataRagVal & IRTC_OSC_ENABLE_MASK)) && (config->enableOsc))
    {
        rtcGpDataRagVal &= ~(IRTC_OSC_SC2P_MASK |
                            IRTC_OSC_SC4P_MASK |
                            IRTC_OSC_SC8P_MASK |
                            IRTC_OSC_SC16P_MASK);

        if (config->enableCapacitor2p)
        {
            rtcGpDataRagVal |= IRTC_OSC_SC2P_MASK;
        }
        if (config->enableCapacitor4p)
        {
            rtcGpDataRagVal |= IRTC_OSC_SC4P_MASK;
        }
        if (config->enableCapacitor8p)
        {
            rtcGpDataRagVal |= IRTC_OSC_SC8P_MASK;
        }
        if (config->enableCapacitor16p)
        {
            rtcGpDataRagVal |= IRTC_OSC_SC16P_MASK;
        }
        rtcGpDataRagVal &= (~IRTC_OSC_ENABLE_MASK);
    }
    else if (!(config->enableOsc))
    {
        rtcGpDataRagVal |= IRTC_OSC_ENABLE_MASK;
    }

    while (IRTC_HAL_GetStatusFlag(RTC, kIRTCReadOnly))
    {
        IRTC_HAL_SetLockRegisterCmd(RTC, false);
    }

    RTC_WR_GP_DATA_REG(RTC, rtcGpDataRagVal);

#else
    // If the oscillator is not enabled and should be enabled.
    if ((!RTC_HAL_IsOscillatorEnabled(RTC)) && (config->enableOsc))
    {
        RTC_HAL_SetOsc2pfLoadCmd(RTC, config->enableCapacitor2p);
        RTC_HAL_SetOsc4pfLoadCmd(RTC, config->enableCapacitor4p);
        RTC_HAL_SetOsc8pfLoadCmd(RTC, config->enableCapacitor8p);
        RTC_HAL_SetOsc16pfLoadCmd(RTC, config->enableCapacitor16p);
    }
    RTC_HAL_SetOscillatorCmd(RTC, config->enableOsc);
#endif

    return kClockManagerSuccess;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : CLOCK_SYS_RtcOscDeinit
 * Description   : This funtion de-initializes the RTC OSC.
 *
 *END**************************************************************************/
void CLOCK_SYS_RtcOscDeinit(uint32_t instance)
{
    assert(instance < RTC_INSTANCE_COUNT);

    g_xtalRtcClkFreq = 0U;

#if defined(FSL_FEATURE_RTC_IS_IRTC) && (FSL_FEATURE_RTC_IS_IRTC)
    while (IRTC_HAL_GetStatusFlag(RTC, kIRTCReadOnly))
    {
        IRTC_HAL_SetLockRegisterCmd(RTC, false);
    }

    RTC_SET_GP_DATA_REG(RTC, 1U);
#else
    RTC_HAL_SetOscillatorCmd(RTC, false);
#endif
}
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/

