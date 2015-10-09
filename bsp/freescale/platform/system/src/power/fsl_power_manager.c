/*
 * Copyright (c) 2014-2015, Freescale Semiconductor, Inc.
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

#include "fsl_power_manager_common.h"
#include "fsl_power_manager.h"
#include "fsl_smc_hal.h"
#include "fsl_pmc_hal.h"
#include "fsl_rcm_hal.h"
#include "fsl_sim_hal.h"
#include "fsl_os_abstraction.h"
#include "fsl_clock_manager.h"
#include <string.h>

/* Checks mcg version */
#if defined(FSL_FEATURE_MCGLITE_MCGLITE)
#if (FSL_FEATURE_MCGLITE_MCGLITE)
#define POWER_VLPR_MCG_LITE 1
#endif
#endif

/* Includes mcg or mcglite hal */
#if defined(POWER_VLPR_MCG_LITE)
#include "fsl_mcglite_hal_modes.h"
#include "fsl_mcglite_hal.h"
#else
#include "fsl_mcg_hal_modes.h"
#include "fsl_mcg_hal.h"
#endif

/* Maximum allowed clocks for VLPR mode */
#define POWER_VLPR_MAX_CLK 4000000UL
#if !defined(POWER_VLPR_MCG_LITE)
#define POWER_VLPR_MCG_LITE 0
#endif

#define POWER_VLPR_MAX_FLASH_BLPE_CLK 1000000UL
/*! For BLPI mode the maximum allowed flash clock in VLPR mode is 800 kHz or 1 MHz, see RM for details */
#define POWER_VLPR_MAX_FLASH_BLPI_CLK 1000000UL

/*******************************************************************************
 * Internal Variables
 ******************************************************************************/

/*! @brief Power manager internal structure. */
static power_manager_state_t gPowerManagerState;

/*! @brief Power manager internal structure lock. */
mutex_t gPowerManagerStateSync;

/*******************************************************************************
 * PROTOTYPES
 ******************************************************************************/

static power_manager_error_code_t POWER_SYS_WaitForRunStatus(void);
static power_manager_error_code_t POWER_SYS_WaitForVlprStatus(void);
static power_manager_error_code_t POWER_SYS_CheckClocks(power_manager_modes_t mode);

/*!
 * @brief Macros for power manager lock mechanism.
 *
 * Mutex is used when operating system is present otherwise critical section
 * (global interrupt disable).
 *
 */
#if (USE_RTOS)
    #define POWER_SYS_LOCK_INIT()    OSA_MutexCreate(&gPowerManagerStateSync)
    #define POWER_SYS_LOCK()         OSA_MutexLock(&gPowerManagerStateSync, OSA_WAIT_FOREVER)
    #define POWER_SYS_UNLOCK()       OSA_MutexUnlock(&gPowerManagerStateSync)
    #define POWER_SYS_LOCK_DEINIT()  OSA_MutexDestroy(&gPowerManagerStateSync)
#else
    #define POWER_SYS_LOCK_INIT()    do {}while(0)
    #define POWER_SYS_LOCK()         OSA_EnterCritical(kCriticalDisableInt)
    #define POWER_SYS_UNLOCK()       OSA_ExitCritical(kCriticalDisableInt)
    #define POWER_SYS_LOCK_DEINIT()  do {}while(0)
#endif

/*! Timeout used for waiting to set new mode */
#define POWER_SET_MODE_TIMEOUT 1000U
/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : POWER_SYS_Init
 * Description   : Initializes the Power manager for operation.
 * This function initializes the Power manager and its run-time state structure.
 * Reference to an array of Power mode configuration structures has to be passed
 * as parameter along with parameter specifying its size. At least one power mode
 * configuration is required. Optionally, reference to array of predefined
 * call-backs can be passed with its size parameter.
 * For details about call-backs refer to the power_manager_callback_user_config_t.
 * As Power manager stores only references to array of these structures they have
 * to exist while Power manager is used.
 * It is expected that prior POWER_SYS_Init() call the write-once protection
 * register was configured appropriately allowing to enter all required low power
 * modes.
 * The following is an example of how to set up two power modes and three
 * call-backs and initialize the Power manager with structures containing their settings.
 * The example shows two possible ways how where the configuration structures can be stored
 * (ROM or RAM) although it is expected that they will be placed rather in the read-only
 * memory to save the RAM space. (Note: In the example it is assumed that the programmed chip
 * doesn't support any optional power options described in the power_manager_user_config_t)
 *
 *END**************************************************************************/
power_manager_error_code_t POWER_SYS_Init(power_manager_user_config_t const ** powerConfigsPtr,
                                          uint8_t configsNumber,
                                          power_manager_callback_user_config_t ** callbacksPtr,
                                          uint8_t callbacksNumber)
{
    /* Check input parameter - at least one power mode configuration is required */
    if ((powerConfigsPtr == NULL) || (configsNumber == 0U))
    {
        return kPowerManagerError;
    }
    /* Initialize internal state structure lock */
    POWER_SYS_LOCK_INIT();
    /* Initialize internal state structure */
    memset(&gPowerManagerState, 0, sizeof(power_manager_state_t));
    /* Store references to user-defined power mode configurations */
    gPowerManagerState.configs = powerConfigsPtr;
    gPowerManagerState.configsNumber = configsNumber;
    /* Store references to user-defined callback configurations and increment call-back handle counter */
    if (callbacksPtr != NULL)
    {
        gPowerManagerState.staticCallbacks = callbacksPtr;
        gPowerManagerState.staticCallbacksNumber = callbacksNumber;
        /* Default value of handle of last call-back that returned error */
        gPowerManagerState.errorCallbackIndex = callbacksNumber;
    }
    /* Enables clock gate for LLWU */
#if FSL_FEATURE_SIM_HAS_SCGC_LLWU
    SIM_HAL_EnableClock(SIM,kSimClockGateLlwu0);
#endif
    return kPowerManagerSuccess;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : POWER_SYS_Deinit
 * Description   : Deinitializes the Power manager.
 *
 *END**************************************************************************/
power_manager_error_code_t POWER_SYS_Deinit(void)
{
    /* Deinitialize internal state structure lock */
    POWER_SYS_LOCK_DEINIT();
    return kPowerManagerSuccess;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : POWER_SYS_SetMode
 * Description   : Configures the power mode.
 *
 * This function switches to one of the defined power modes. Requested mode number is passed
 * as an input parameter. This function notifies all registered callback functions before
 * the mode change (using  kPowerManagerCallbackBefore set as callback type parameter),
 * sets specific power options defined in the power mode configuration and enters the specified
 * mode. In case of run modes (for example, Run, Very low power run, or High speed run), this function
 * also invokes all registered callbacks after the mode change (using kPowerManagerCallbackAfter).
 * In case of sleep or deep sleep modes, if the requested mode is not exited through
 * a reset, these notifications are sent after the core wakes up.
 * Callbacks are invoked in the following order: All registered callbacks are notified
 * ordered by index in the callbacks array (see callbacksPtr parameter of POWER_SYS_Init()).
 * The same order is used for before and after switch notifications.
 * The notifications before the power mode switch can be used to obtain confirmation about
 * the change from registered callbacks. If any registered callback denies the power
 * mode change, further execution of this function depends on mode change policy: the mode
 * change is either forced (kPowerManagerPolicyForcible) or exited (kPowerManagerPolicyAgreement).
 * When mode change is forced, the result of the before switch notifications are ignored. If
 * agreement is required, if any callback returns an error code then further notifications
 * before switch notifications are cancelled and all already notified callbacks are re-invoked
 * with kPowerManagerCallbackAfter set as callback type parameter. The index of the callback
 * which returned error code during pre-switch notifications is stored (any error codes during
 * callbacks re-invocation are ignored) and POWER_SYS_GetErrorCallback() can be used to get it.
 * Regardless of the policies, if any callback returned an error code, an error code denoting in which phase
 * the error occurred is returned when POWER_SYS_SetMode() exits.
 * It is possible to enter any mode supported by the processor. Refer to the chip reference manual
 * for list of available power modes. If it is necessary to switch into intermediate power mode prior to
 * entering requested mode (for example, when switching from Run into Very low power wait through Very low
 * power run mode), then the intermediate mode is entered without invoking the callback mechanism.
 *
 *END**************************************************************************/
power_manager_error_code_t POWER_SYS_SetMode(uint8_t powerModeIndex, power_manager_policy_t policy)
{
    power_manager_user_config_t const * configPtr; /* Local pointer to the requested user-defined power mode configuration */
    power_manager_modes_t mode;         /* Local variable with requested power mode */
    smc_power_mode_config_t halModeConfig; /* SMC HAL layer configuration structure */
    uint8_t currentStaticCallback = 0U;      /* Index to array of statically registered call-backs */
    power_manager_error_code_t returnCode = kPowerManagerSuccess; /* Function return */
    power_manager_error_code_t clockCheckRetCode; /* Return code from clock checks */
    power_manager_notify_struct_t notifyStruct; /*  Callback notification structure */ 
    power_manager_callback_user_config_t * callbackConfig; /* Pointer to callback configuration */
    
    /* Default value of handle of last call-back that returned error */
    gPowerManagerState.errorCallbackIndex = gPowerManagerState.staticCallbacksNumber;
    
    POWER_SYS_LOCK();
    /* Requested power mode configuration availability check */
    if (powerModeIndex >= gPowerManagerState.configsNumber)
    {
        POWER_SYS_UNLOCK();
        return kPowerManagerErrorOutOfRange;
    }

    /* Initialization of local variables from the Power manager state structure */
    configPtr = gPowerManagerState.configs[powerModeIndex];
    mode = configPtr->mode;
    notifyStruct.policy = policy;
    notifyStruct.targetPowerConfigIndex = powerModeIndex;
    notifyStruct.targetPowerConfigPtr = configPtr;

    /* Check that requested power mode is not protected */
    if ((mode == kPowerManagerVlpr) || (mode == kPowerManagerVlpw) || (mode == kPowerManagerVlps))
    {
        if (!SMC_HAL_GetProtection(SMC, kAllowPowerModeVlp))
        {
            POWER_SYS_UNLOCK();
            return kPowerManagerError;
        }
    }
#if FSL_FEATURE_SMC_HAS_LOW_LEAKAGE_STOP_MODE
#if FSL_FEATURE_SMC_HAS_STOP_SUBMODE0             
    else if ((mode >= kPowerManagerLls) && (mode < kPowerManagerVlls0))
#else
    else if ((mode >= kPowerManagerLls) && (mode < kPowerManagerVlls1))
#endif      
    {
        if (!SMC_HAL_GetProtection(SMC, kAllowPowerModeLls))
        {
            POWER_SYS_UNLOCK();
            return kPowerManagerError;
        }
    }
#endif
#if FSL_FEATURE_SMC_HAS_STOP_SUBMODE0    
    else if (mode >= kPowerManagerVlls0)
#else
    else if (mode >= kPowerManagerVlls1)
#endif      
    {
        if (!SMC_HAL_GetProtection(SMC, kAllowPowerModeVlls))
        {
            POWER_SYS_UNLOCK();
            return kPowerManagerError;
        }
    }
        
    notifyStruct.notifyType = kPowerManagerNotifyBefore;
        /* From all statically registered call-backs... */
        for (currentStaticCallback = 0U; currentStaticCallback < gPowerManagerState.staticCallbacksNumber; currentStaticCallback++)
        {   
            callbackConfig = (gPowerManagerState.staticCallbacks[currentStaticCallback]);
            /* Check pointer to static callback configuration */
            if ( callbackConfig != NULL ){
                /* ...notify only those which asked to be called before the power mode change */
                if (((uint32_t)callbackConfig->callbackType) & kPowerManagerCallbackBefore)
                {
                    /* In case that call-back returned error code mark it, store the call-back handle and eventually cancel the mode switch */
                    if (callbackConfig->callback(&notifyStruct, callbackConfig->callbackData) != kPowerManagerSuccess)
                    {
                        returnCode = kPowerManagerErrorNotificationBefore;
                        gPowerManagerState.errorCallbackIndex = currentStaticCallback;
                        /* If not forcing power mode switch, call all already notified call-backs to revert their state as the mode change is canceled */
                        if (policy != kPowerManagerPolicyForcible)
                        {
                            break;
                        }
                    }
                }
              }
          }

    POWER_SYS_UNLOCK();

    /* Clocks should be in desired range. Some registered callback can change the clock so checks clock after callbacks */
    clockCheckRetCode = POWER_SYS_CheckClocks(mode);

    /* Power mode switch */

    /* In case that any call-back returned error code and  policy doesn't force the mode switch go to after switch call-backs */
    if ( ((policy == kPowerManagerPolicyForcible) || (returnCode == kPowerManagerSuccess)) && (clockCheckRetCode == kPowerManagerSuccess))
    {
#if  FSL_FEATURE_SMC_HAS_LPWUI
        halModeConfig.lpwuiOptionValue = configPtr->lowPowerWakeUpOnInterruptValue;
#endif
                
        /* Configure the HAL layer */
        switch (mode) {
#if FSL_FEATURE_SMC_HAS_HIGH_SPEED_RUN_MODE
        /* High speed run mode */
        case kPowerManagerHsrun:
            halModeConfig.powerModeName = kPowerModeHsrun;
            break;
#endif
        /* Run mode */
        case kPowerManagerRun:
            halModeConfig.powerModeName = kPowerModeRun;
            break;
        /* Very low power run mode */
        case kPowerManagerVlpr:
            halModeConfig.powerModeName = kPowerModeVlpr;
            break;
        /* Wait mode */
        case kPowerManagerWait:
            halModeConfig.powerModeName = kPowerModeWait;
            break;
        /* Very low power wait mode */
        case kPowerManagerVlpw:
            halModeConfig.powerModeName = kPowerModeVlpw;
            break;
#if FSL_FEATURE_SMC_HAS_LOW_LEAKAGE_STOP_MODE            
        /* Low leakage stop modes */
        case kPowerManagerLls:
            halModeConfig.powerModeName = kPowerModeLls;
            break;
#if FSL_FEATURE_SMC_HAS_LLS_SUBMODE
        case kPowerManagerLls2:
            halModeConfig.powerModeName = kPowerModeLls;
            halModeConfig.stopSubMode = kSmcStopSub2;
            break;
        case kPowerManagerLls3:
            halModeConfig.powerModeName = kPowerModeLls;
            halModeConfig.stopSubMode = kSmcStopSub3;
            break;
#endif
#endif
        /* Very low leakage stop modes */
#if FSL_FEATURE_SMC_HAS_STOP_SUBMODE0            
        case kPowerManagerVlls0:
            halModeConfig.powerModeName = kPowerModeVlls;
            halModeConfig.stopSubMode = kSmcStopSub0;
#if FSL_FEATURE_SMC_HAS_PORPO
            /* Optionally setup the power-on-reset detect circuit in VLLS0 */
            halModeConfig.porOptionValue = configPtr->powerOnResetDetectionValue;
#endif
            break;
#endif            
        case kPowerManagerVlls1:
            halModeConfig.powerModeName = kPowerModeVlls;
            halModeConfig.stopSubMode = kSmcStopSub1;
            break;
#if FSL_FEATURE_SMC_HAS_STOP_SUBMODE2            
        case kPowerManagerVlls2:
            halModeConfig.powerModeName = kPowerModeVlls;
            halModeConfig.stopSubMode = kSmcStopSub2;
#if FSL_FEATURE_SMC_HAS_RAM2_POWER_OPTION
            /* Optionally setup the RAM2 partition retention in VLLS2 */
            halModeConfig.ram2OptionValue = configPtr->RAM2PartitionValue;
#endif
            break;
#endif            
        case kPowerManagerVlls3:
            halModeConfig.powerModeName = kPowerModeVlls;
            halModeConfig.stopSubMode = kSmcStopSub3;
            break;
#if FSL_FEATURE_SMC_HAS_PSTOPO
        /* Partial stop modes */
        case kPowerManagerPstop1:
            halModeConfig.powerModeName = kPowerModeStop;
            halModeConfig.pstopOptionValue = kSmcPstopStop1;
            break;
        case kPowerManagerPstop2:
            halModeConfig.powerModeName = kPowerModeStop;
            halModeConfig.pstopOptionValue = kSmcPstopStop2;
            break;
#endif
        /* Stop mode */
        case kPowerManagerStop:
            halModeConfig.powerModeName = kPowerModeStop;
#if FSL_FEATURE_SMC_HAS_PSTOPO
            halModeConfig.pstopOptionValue = kSmcPstopStop;
#endif
            break;
        /* Very low power stop mode */
        case kPowerManagerVlps:
            halModeConfig.powerModeName = kPowerModeVlps;
            break;
        default:
            return kPowerManagerErrorSwitch;
        }

#if FSL_FEATURE_SMC_HAS_LPOPO
#if FSL_FEATURE_SMC_HAS_LOW_LEAKAGE_STOP_MODE        
        if ((mode >= kPowerManagerLls) && (mode <= kPowerManagerVlls3))
#else
#if FSL_FEATURE_SMC_HAS_STOP_SUBMODE0
        if ((mode >= kPowerManagerVlls0) && (mode <= kPowerManagerVlls3))          
#else
        if ((mode >= kPowerManagerVlls1) && (mode <= kPowerManagerVlls3))          
#endif
#endif
        {
            /* Optionally setup the LPO operation in LLSx/VLLSx */
            halModeConfig.lpoOptionValue = configPtr->lowPowerOscillatorValue;
        }
#endif

        /* Configure ARM core what to do after interrupt invoked in (deep) sleep state */
        if (mode >= kPowerManagerWait)
        {
            if (configPtr->sleepOnExitValue)
            {
                /* Go back to (deep) sleep state on ISR exit */
                SCB->SCR |= SCB_SCR_SLEEPONEXIT_Msk;
            }
            else
            {
                /* Do not re-enter (deep) sleep state on ISR exit */
                SCB->SCR &= ~(SCB_SCR_SLEEPONEXIT_Msk);
            }
        }

        /* Switch the mode */
        if (SMC_HAL_SetMode(SMC, &halModeConfig) != kSmcHalSuccess)
        {
            returnCode = kPowerManagerErrorSwitch;
        }

        /* Wait until new run mode is entered */
        if (mode == kPowerManagerRun)
        {
            returnCode = POWER_SYS_WaitForRunStatus();
            
            if(returnCode != kPowerManagerSuccess)
            {
                return returnCode;
            }
        }
        else if (mode == kPowerManagerVlpr)
        {
            returnCode = POWER_SYS_WaitForVlprStatus();

            if(returnCode != kPowerManagerSuccess)
            {
                return returnCode;
            }
        }

        /* End of successful switch */
              
        POWER_SYS_LOCK();
        /* Update current configuration index */
        gPowerManagerState.currentConfig = powerModeIndex;
        notifyStruct.notifyType = kPowerManagerNotifyAfter;
        /* From all statically registered call-backs... */
        for (currentStaticCallback = 0U; currentStaticCallback < gPowerManagerState.staticCallbacksNumber; currentStaticCallback++)
        {   
            callbackConfig = (gPowerManagerState.staticCallbacks[currentStaticCallback]);
            /* Check pointer to static callback configuration */
            if ( callbackConfig != NULL ){
                /* ...notify only those which asked to be called after the power mode change */
                if (((uint32_t)callbackConfig->callbackType) & kPowerManagerCallbackAfter)
                {
                    /* In case that call-back returned error code mark it and store the call-back handle */
                    if (callbackConfig->callback(&notifyStruct, callbackConfig->callbackData) != kPowerManagerSuccess)
                    {
                        returnCode = kPowerManagerErrorNotificationAfter;
                        gPowerManagerState.errorCallbackIndex = currentStaticCallback;

                    }
                }
            }
        }
        POWER_SYS_UNLOCK();
    }
    else
    {
        /* End of unsuccessful switch */

        /* Checks if we can't switch due to clock */
        if((policy == kPowerManagerPolicyForcible) || (returnCode == kPowerManagerSuccess))
        {
            returnCode = clockCheckRetCode;
        }

        POWER_SYS_LOCK();
        
        notifyStruct.notifyType = kPowerManagerNotifyRecover;
        while(currentStaticCallback--)
        {   
            callbackConfig = (gPowerManagerState.staticCallbacks[currentStaticCallback]);
            /* Check pointer to static callback configuration */
            if ( callbackConfig != NULL ){
                if (((uint32_t)callbackConfig->callbackType) & kPowerManagerCallbackBefore)
                {
                    callbackConfig->callback(&notifyStruct, callbackConfig->callbackData);
                }
            }
        }
        POWER_SYS_UNLOCK();

    }

    return returnCode;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : POWER_SYS_GetLastModeIndex
 * Description   : This function returns power mode set as the last one.
 *
 * This function returns index of power mode which was set using POWER_SYS_SetMode() as the last one.
 * If the power mode was entered although some of the registered call-back denied the mode change
 * or if any of the call-backs invoked after the entering/restoring run mode failed then the return
 * code of this function has kPowerManagerError value.
 * value.
 *
 *END**************************************************************************/
power_manager_error_code_t POWER_SYS_GetLastMode(uint8_t *powerModeIndexPtr)
{
    POWER_SYS_LOCK();
    /* Pass index of user-defined configuration structure of currently running power mode */
    *powerModeIndexPtr = gPowerManagerState.currentConfig;
    /* Return whether all call-backs executed without error */
    if (gPowerManagerState.errorCallbackIndex == gPowerManagerState.staticCallbacksNumber)
    {
        POWER_SYS_UNLOCK();
        return kPowerManagerSuccess;
    }
    else
    {
        POWER_SYS_UNLOCK();
        return kPowerManagerError;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : POWER_SYS_GetLastModeConfig
 * Description   : This function returns user configuration structure of power mode set as the last one.
 *
 * This function returns reference to configuration structure which was set using POWER_SYS_SetMode()
 * as the last one. If the current power mode was entered although some of the registered call-back denied
 * the mode change or if any of the call-backs invoked after the entering/restoring run mode failed then
 * the return code of this function has kPowerManagerError value.
 *
 *END**************************************************************************/
power_manager_error_code_t POWER_SYS_GetLastModeConfig(power_manager_user_config_t const ** powerModePtr)
{
    POWER_SYS_LOCK();
    /* Pass reference to user-defined configuration structure of currently running power mode */
    *powerModePtr = gPowerManagerState.configs[gPowerManagerState.currentConfig];
    /* Return whether all call-backs executed without error */
    if (gPowerManagerState.errorCallbackIndex == gPowerManagerState.staticCallbacksNumber)
    {
        POWER_SYS_UNLOCK();
        return kPowerManagerSuccess;
    }
    else
    {
        POWER_SYS_UNLOCK();
        return kPowerManagerError;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : POWER_SYS_GetCurrentMode
 * Description   : Returns currently running power mode.
 *
 *END**************************************************************************/
power_manager_modes_t POWER_SYS_GetCurrentMode(void)
{
    power_manager_modes_t retVal;
    switch (SMC_HAL_GetStat(SMC))
    {
#if FSL_FEATURE_SMC_HAS_HIGH_SPEED_RUN_MODE
        /* High speed run mode */
        case kStatHsrun:
            retVal = kPowerManagerHsrun;
            break;
#endif
        /* Run mode */
        case kStatRun:
            retVal = kPowerManagerRun;
            break;
        /* Very low power run mode */
        case kStatVlpr:
            retVal = kPowerManagerVlpr;
            break;
        /* This should never happen - core has to be in some run mode to execute code */
        default:
            retVal = kPowerManagerMax;
            break;
    }
    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : POWER_SYS_GetErrorCallbackIndex
 * Description   : Returns the last failed notification callback.
 *
 * This function returns index of the last call-back that failed during the power mode switch while
 * the last POWER_SYS_SetMode() was called. If the last POWER_SYS_SetMode() call ended successfully 
 * value equal to callbacks number is returned. Returned value represents index in the array of 
 * static call-backs.
 *
 *END**************************************************************************/
uint8_t POWER_SYS_GetErrorCallbackIndex (void)
{
    return gPowerManagerState.errorCallbackIndex;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : POWER_SYS_GetErrorCallback
 * Description   : Get the callback which returns error in last mode switch.
 *
 *END**************************************************************************/
power_manager_callback_user_config_t* POWER_SYS_GetErrorCallback(void)
{
    /* If all callbacks return success. */
    if (gPowerManagerState.errorCallbackIndex >= gPowerManagerState.staticCallbacksNumber)
    {
        return NULL;
    }
    else
    {
        return gPowerManagerState.staticCallbacks[gPowerManagerState.errorCallbackIndex];
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : POWER_SYS_GetVeryLowPowerModeStatus
 * Description   : Returns whether very low power mode is running.
 *
 *END**************************************************************************/
bool POWER_SYS_GetVeryLowPowerModeStatus(void)
{
    /* Get current power mode and return true if it is very low power mode */
    uint8_t status = SMC_HAL_GetStat(SMC);
    if (status == kStatVlpr)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : POWER_SYS_GetLowLeakageWakeupResetStatus
 * Description   : Returns whether reset was caused by low leakage wake up.
 *
 *END**************************************************************************/
bool POWER_SYS_GetLowLeakageWakeupResetStatus(void)
{
    return RCM_HAL_GetSrcStatus(RCM, kRcmWakeup);
}
/*FUNCTION**********************************************************************
 *
 * Function Name : POWER_SYS_GetAckIsolation
 * Description   : Returns true if ACK isolation is set.
 *
 *END**************************************************************************/
bool POWER_SYS_GetAckIsolation(void)
{
    return PMC_HAL_GetAckIsolation(PMC)?true:false;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : POWER_SYS_ClearAckIsolation
 * Description   : Clears the acknowledge isolation flag.
 *
 *END**************************************************************************/
void POWER_SYS_ClearAckIsolation(void)
{
    if( PMC_HAL_GetAckIsolation(PMC) )
    {
        PMC_HAL_ClearAckIsolation(PMC);
    }
}

#if FSL_FEATURE_SOC_LLWU_COUNT
#if FSL_FEATURE_LLWU_HAS_INTERNAL_MODULE
/*FUNCTION**********************************************************************
 *
 * Function Name : POWER_SYS_SetWakeupModule
 * Description   : This function allows to set wake up module in low leakage wake up unit (LLWU).
 *
 *END**************************************************************************/
void POWER_SYS_SetWakeupModule(power_wakeup_module_t module,bool enable)
{   
    /* Checks module range which is defined by enumeration type */
    assert( module < kPowerManagerWakeupMax);
    /* Set module */
    LLWU_HAL_SetInternalModuleCmd(LLWU, (llwu_wakeup_module_t)module, enable);
    
}

/*FUNCTION**********************************************************************
 *
 * Function Name : POWER_SYS_GetWakeupModuleFlag
 * Description   : This function allows to get wake up module flag in LLWU.
 *
 *END**************************************************************************/
bool POWER_SYS_GetWakeupModuleFlag(power_wakeup_module_t module)
{
    /* Checks module range which is defined by enumeration type */
    assert( module < kPowerManagerWakeupMax);
    return LLWU_HAL_GetInternalModuleWakeupFlag(LLWU, (llwu_wakeup_module_t)module);
}
#endif
#if FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN
/*FUNCTION**********************************************************************
 *
 * Function Name : POWER_SYS_SetWakeupPin
 * Description   : This function allows to set wake up pin in low leakage wake up unit (LLWU).
 * Each of the available wake-up sources can be individually enabled or disabled.
 *
 *END**************************************************************************/
void POWER_SYS_SetWakeupPin(power_wakeup_pin_t pin, llwu_external_pin_modes_t pinMode, const gpio_input_pin_t * config)
{
    llwu_wakeup_pin_t llwuPin = POWER_EXTRACT_LLWU_PIN(pin);
    uint32_t gpioPin =  POWER_EXTRACT_GPIO_PINNAME(pin);
      
    assert( (uint32_t)llwuPin < FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN);
    LLWU_HAL_SetExternalInputPinMode(LLWU,pinMode, llwuPin);
    
    /* Configures gpio pin if config is passed */
    if( (gpioPin != POWER_GPIO_RESERVED) && (config != NULL) )
    {
        /* Configures pin as input pin and configures electrical parameters */
        gpio_input_pin_user_config_t pinConfig;
        
        pinConfig.pinName = gpioPin;
        pinConfig.config  = *config;
        GPIO_DRV_InputPinInit(&pinConfig);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : POWER_SYS_GetWakeupPinFlag
 * Description   : This function allows to get wake up pin flag in low leakage wake up unit (LLWU).
 *
 *END**************************************************************************/
bool POWER_SYS_GetWakeupPinFlag(power_wakeup_pin_t pin)
{
    llwu_wakeup_pin_t llwuPin = POWER_EXTRACT_LLWU_PIN(pin);
    
    assert( (uint32_t)llwuPin < FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN);
    return LLWU_HAL_GetExternalPinWakeupFlag(LLWU, llwuPin);
}
/*FUNCTION**********************************************************************
 *
 * Function Name : POWER_SYS_ClearWakeupPinFlag
 * Description   : This function allows to clear wake up pin flag in low leakage wake up unit (LLWU).
 *
 *END**************************************************************************/
void POWER_SYS_ClearWakeupPinFlag(power_wakeup_pin_t pin)
{
    llwu_wakeup_pin_t llwuPin = POWER_EXTRACT_LLWU_PIN(pin);
    
    assert( (uint32_t)llwuPin < FSL_FEATURE_LLWU_HAS_EXTERNAL_PIN);
    LLWU_HAL_ClearExternalPinWakeupFlag(LLWU, llwuPin);
}
#endif
#endif
/*FUNCTION**********************************************************************
 * Function Name : POWER_SYS_WaitForRunStatus
 * Description   :Internal function used by POWER_SYS_SetMode function
 *END**************************************************************************/
static power_manager_error_code_t POWER_SYS_WaitForRunStatus(void)
{
    uint32_t i;
    
    for (i=0; !PMC_HAL_GetRegulatorStatus(PMC); i++)
    {
        if(i > POWER_SET_MODE_TIMEOUT)
        {
            return kPowerManagerErrorSwitch;
        }
    }
    
    for (i=0; SMC_HAL_GetStat(SMC) != kStatRun; i++)
    {
        if(i > POWER_SET_MODE_TIMEOUT)
        {
            return kPowerManagerErrorSwitch;
        }
    }
    
    return kPowerManagerSuccess;
}

/*FUNCTION**********************************************************************
 * Function Name : POWER_SYS_WaitForVlprStatus
 * Description   :Internal function used by POWER_SYS_SetMode function
 *END**************************************************************************/
static power_manager_error_code_t POWER_SYS_WaitForVlprStatus(void)
{
    uint32_t i;
    
    for (i=0; SMC_HAL_GetStat(SMC) != kStatVlpr; i++)
    {
        if(i > POWER_SET_MODE_TIMEOUT)
        {
            return kPowerManagerErrorSwitch;
        }
    }
    
    return kPowerManagerSuccess;
}

/*FUNCTION**********************************************************************
 * Function Name : POWER_SYS_CheckClocks
 * Description   :Internal function used by POWER_SYS_SetMode function
 *END**************************************************************************/
static power_manager_error_code_t POWER_SYS_CheckClocks(power_manager_modes_t mode)
{   
#if POWER_VLPR_MCG_LITE  
    mcglite_mode_t mcgMode = CLOCK_HAL_GetMode(MCG);
#else
    mcg_modes_t mcgMode = CLOCK_HAL_GetMcgMode(MCG);
   
    /* Check clock monitors */
    switch(mode)
    {
#if FSL_FEATURE_SMC_HAS_HIGH_SPEED_RUN_MODE
    case kPowerManagerHsrun:
#endif      
    case kPowerManagerRun:
    case kPowerManagerWait:
        /* Clock monitors can be enabled */
        break;
    default:
        /* For other modes clock monitors should be disabled */
#if FSL_FEATURE_MCG_HAS_EXTERNAL_CLOCK_MONITOR
        if( CLOCK_HAL_IsOsc0MonitorEnabled(MCG) )
        {
            return kPowerManagerErrorClock;
        }    
#endif        
#if FSL_FEATURE_MCG_HAS_RTC_32K
        if( CLOCK_HAL_IsRtcOscMonitorEnabled(MCG) )
        {
            return kPowerManagerErrorClock;
        }    
#endif
#if FSL_FEATURE_MCG_USE_PLLREFSEL        
        if( CLOCK_HAL_IsOsc1MonitorEnabled(MCG) )
        {
            return kPowerManagerErrorClock;
        }
#endif        
        break;
    }
#endif
    
    /* We need check clocks if goes into VLPR or VLPW over VLPR */
    if( (mode!=kPowerManagerVlpr) && (mode!=kPowerManagerVlpw) )
    {
        return kPowerManagerSuccess;
    }
    
#if POWER_VLPR_MCG_LITE 
    switch(mcgMode)
    {
    case kMcgliteModeLirc8M:
    case kMcgliteModeLirc2M:
    case kMcgliteModeExt:
        /* allowed modes */
        break;
    default:
        return kPowerManagerErrorClock;
    }
    
    if(CLOCK_SYS_GetFlashClockFreq() > POWER_VLPR_MAX_FLASH_BLPE_CLK)
    {
        return kPowerManagerErrorClock;
    }
#else
    switch(mcgMode)
    {
    case kMcgModeBLPI:
        /* fast IRC must be selected */
        if(CLOCK_HAL_GetInternalRefClkMode(MCG) != kMcgIrcFast)
        {
            return kPowerManagerErrorClock;
        }
        if(CLOCK_SYS_GetFlashClockFreq() > POWER_VLPR_MAX_FLASH_BLPI_CLK)
        {
            return kPowerManagerErrorClock;
        }
        break;
    case kMcgModeBLPE:
        if(CLOCK_SYS_GetFlashClockFreq() > POWER_VLPR_MAX_FLASH_BLPE_CLK)
        {
            return kPowerManagerErrorClock;
        }
        break;
    default:
        return kPowerManagerErrorClock;
    }  
#endif
    if(CLOCK_SYS_GetCoreClockFreq() > POWER_VLPR_MAX_CLK)
    {
        return kPowerManagerErrorClock;
    }
    
    if(CLOCK_SYS_GetBusClockFreq() > POWER_VLPR_MAX_CLK)
    {
        return kPowerManagerErrorClock;
    }
    
    if(CLOCK_SYS_GetSystemClockFreq() > POWER_VLPR_MAX_CLK)
    {
        return kPowerManagerErrorClock;
    }
    
    return kPowerManagerSuccess;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/

