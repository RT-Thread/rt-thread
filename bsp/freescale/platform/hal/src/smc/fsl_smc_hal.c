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

#include "fsl_smc_hal.h"
#if FSL_FEATURE_SOC_SMC_COUNT

/*******************************************************************************
 * Definitions
 ******************************************************************************/
// Definitions for macros
#if FSL_FEATURE_SMC_USE_VLLSCTRL_REG
    #define SMC_SET_STOP_SUBMODE SMC_BWR_VLLSCTRL_VLLSM
    #define SMC_SET_PORPO        SMC_BWR_VLLSCTRL_PORPO
    #define SMC_SET_RAM2PO       SMC_BWR_VLLSCTRL_RAM2PO
#else
    #define SMC_SET_PORPO        SMC_BWR_STOPCTRL_PORPO
    #define SMC_SET_RAM2PO       SMC_BWR_STOPCTRL_RAM2PO
    #if FSL_FEATURE_SMC_USE_STOPCTRL_VLLSM
        #define SMC_SET_STOP_SUBMODE SMC_BWR_STOPCTRL_VLLSM
    #else
        #define SMC_SET_STOP_SUBMODE SMC_BWR_STOPCTRL_LLSM
    #endif
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : SMC_HAL_SetPowerModeRun
 * Description   : Set RUN mode, this function is used internally.
 *
 *END**************************************************************************/
static void SMC_HAL_SetPowerModeRun(SMC_Type * base)
{
    SMC_BWR_PMCTRL_RUNM(base, kSmcRun);
    while (kStatRun != SMC_HAL_GetStat(base)) { }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMC_HAL_SetPowerModeVlpr
 * Description   : Set to VLPR mode, this function is used internally.
 *
 *END**************************************************************************/
static void SMC_HAL_SetPowerModeVlpr(SMC_Type * base)
{
    SMC_BWR_PMCTRL_RUNM(base, kSmcVlpr);
    while (kStatVlpr != SMC_HAL_GetStat(base)) { }
}

#if FSL_FEATURE_SMC_HAS_HIGH_SPEED_RUN_MODE
/*FUNCTION**********************************************************************
 *
 * Function Name : SMC_HAL_SetPowerModeHsrun
 * Description   : Set HSRUN mode, this function is used internally.
 *
 *END**************************************************************************/
static void SMC_HAL_SetPowerModeHsrun(SMC_Type * base)
{
    SMC_BWR_PMCTRL_RUNM(base, kSmcHsrun);
    while (kStatHsrun != SMC_HAL_GetStat(base)) { }
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : SMC_HAL_SetMode
 * Description   : Config the power mode
 * This function configures the power mode base on configuration structure, if
 * could not switch to the target mode directly, this function could check
 * internally and choose the right path.
 *
 *END**************************************************************************/
smc_hal_error_code_t SMC_HAL_SetMode(SMC_Type * base,
                                     const smc_power_mode_config_t *powerModeConfig)
{
    volatile uint32_t dummyRead;
    smc_stop_mode_t stopMode;
    power_mode_stat_t curPowerMode;

    curPowerMode = SMC_HAL_GetStat(base);

#if FSL_FEATURE_SMC_HAS_LPWUI
    /* Update LPWUI. Only when target mode is VLPR/VLPS/VLPW. */
    if (((kPowerModeVlpr | kPowerModeVlpw | kPowerModeVlps) & (uint32_t)powerModeConfig->powerModeName)
        &&  (powerModeConfig->lpwuiOptionValue != (smc_lpwui_option_t)SMC_BRD_PMCTRL_LPWUI(base)))
    {
        SMC_HAL_SetPowerModeRun(base);
        SMC_BWR_PMCTRL_LPWUI(base, powerModeConfig->lpwuiOptionValue);
        /*
         * Why set to VLPR here:
         * 1. If target mode is VLPS, then LPWUI will be bypassed if enter VLPS
         *    from RUN directly.  So first change to VLPR to make sure LPWUI is
         *    not bypassed.
         * 2. If target mode is VLPR/VLPW, it is OK to set to VLPR first.
         */
        SMC_HAL_SetPowerModeVlpr(base);
        curPowerMode = kStatVlpr;
    }
#endif

    /*
     * Step 1: If could not reach target mode directly, change to the mode that
     *         could reach.
     */
    switch (curPowerMode)
    {
        // If current mode is RUN, target mode is VLPW, change to VLPR first.
        case kStatRun:
            if (kPowerModeVlpw & (uint32_t)powerModeConfig->powerModeName)
            {
                SMC_HAL_SetPowerModeVlpr(base);
            }
            break;
        // If current mode is VLPR, target mode is HSRUN/STOP/WAIT, change to RUN first.
        case kStatVlpr:
            if ((kPowerModeStop
               | kPowerModeWait
#if FSL_FEATURE_SMC_HAS_HIGH_SPEED_RUN_MODE
               | kPowerModeHsrun
#endif
               ) & (uint32_t)powerModeConfig->powerModeName)
            {
                SMC_HAL_SetPowerModeRun(base);
            }
            break;
#if FSL_FEATURE_SMC_HAS_HIGH_SPEED_RUN_MODE
        /* If current mode is HSRUN, target mode is not HSRUN and RUN,
         * change to RUN first, if target mode is VLPW, change to RUN mode,
         * then change to VLPR mode.
         */
        case kStatHsrun:
            if (!((kPowerModeHsrun | kPowerModeRun) & (uint32_t)powerModeConfig->powerModeName))
            {
                SMC_HAL_SetPowerModeRun(base);

                if (kPowerModeVlpw & (uint32_t)powerModeConfig->powerModeName)
                {
                    SMC_HAL_SetPowerModeVlpr(base);
                }
            }
            break;
#endif
        default:
            break;
    }

    // Step 2: Change to target mode.
    switch (powerModeConfig->powerModeName)
    {
        case kPowerModeRun:
            SMC_HAL_SetPowerModeRun(base);
            break;

        case kPowerModeVlpr:
            SMC_HAL_SetPowerModeVlpr(base);
            break;

#if FSL_FEATURE_SMC_HAS_HIGH_SPEED_RUN_MODE
        case kPowerModeHsrun:
            SMC_HAL_SetPowerModeHsrun(base);
            break;
#endif

        /* For wait modes. */
        case kPowerModeWait:
        case kPowerModeVlpw:
            /* Clear the SLEEPDEEP bit to disable deep sleep mode - enter wait mode*/
            SCB->SCR &= ~SCB_SCR_SLEEPDEEP_Msk;
            /*
             * Ensure that all register writes associated with setting up the
             * low power mode being entered have completed before the MCU enters
             * the low power mode.
             */
            dummyRead = SMC_RD_PMCTRL(base);
            dummyRead = dummyRead;
            __WFI();
            break;

        /* For stop modes. */
        case kPowerModeStop:
        case kPowerModeVlps:
#if FSL_FEATURE_SMC_HAS_LOW_LEAKAGE_STOP_MODE
        case kPowerModeLls:
#endif
        case kPowerModeVlls:
#if FSL_FEATURE_SMC_HAS_PSTOPO
            SMC_BWR_STOPCTRL_PSTOPO(base, powerModeConfig->pstopOptionValue);
#endif
#if FSL_FEATURE_SMC_HAS_LPOPO
            SMC_BWR_STOPCTRL_LPOPO(base, powerModeConfig->lpoOptionValue);
#endif
#if FSL_FEATURE_SMC_HAS_PORPO
            SMC_SET_PORPO(base, powerModeConfig->porOptionValue);
#endif
#if FSL_FEATURE_SMC_HAS_RAM2_POWER_OPTION
            SMC_SET_RAM2PO(base, powerModeConfig->ram2OptionValue);
#endif
            if (kPowerModeStop == powerModeConfig->powerModeName)
            {
                stopMode = kSmcStop;
            }
            else if (kPowerModeVlps == powerModeConfig->powerModeName)
            {
                stopMode = kSmcVlps;
            }
#if FSL_FEATURE_SMC_HAS_LOW_LEAKAGE_STOP_MODE
            else if (kPowerModeLls == powerModeConfig->powerModeName)
            {
                stopMode = kSmcLls;
                SMC_SET_STOP_SUBMODE(base, powerModeConfig->stopSubMode);
            }
#endif
            else
            {
                stopMode = kSmcVlls;
                SMC_SET_STOP_SUBMODE(base, powerModeConfig->stopSubMode);
            }

            SMC_BWR_PMCTRL_STOPM(base, stopMode);
            /* Set the SLEEPDEEP bit to enable deep sleep mode - enter stop mode*/
            SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;
            /*
             * Ensure that all register writes associated with setting up the
             * low power mode being entered have completed before the MCU enters
             * the low power mode.
             */
            dummyRead = SMC_RD_PMCTRL(base);
            __WFI();
            break;

        default:
            break;
    }

    return kSmcHalSuccess;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SMC_HAL_GetStat
 * Description   : Get the current power mode stat
 * This function will return the current power mode stat. Once application is 
 * switching the power mode, it should always check the stat to make sure it 
 * runs into the specified mode or not. Also application will need to check 
 * this mode before switching to certain mode. The system will require that
 * only certain mode could switch to other specific mode. Refer to the 
 * reference manual for details. Refer to _power_mode_stat for the meaning
 * of the power stat
 * 
 *END**************************************************************************/
power_mode_stat_t SMC_HAL_GetStat(SMC_Type * base)
{
    return (power_mode_stat_t)SMC_RD_PMSTAT(base); 
}
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/

