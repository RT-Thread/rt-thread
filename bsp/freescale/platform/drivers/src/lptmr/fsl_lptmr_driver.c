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

#include <assert.h>
#include <string.h>
#include "fsl_lptmr_driver.h"
#include "fsl_interrupt_manager.h"
#include "fsl_clock_manager.h"
#if FSL_FEATURE_SOC_LPTMR_COUNT

/*******************************************************************************
 * Definitions
 *******************************************************************************/
/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Code
 *******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : LPTMR_DRV_Init
 * Description   : initializes the LPTMR driver.
 * This function will initialize the LPTMR driver according to user configure
 * strcuture.
 *
 *END**************************************************************************/
lptmr_status_t LPTMR_DRV_Init(uint32_t instance, lptmr_state_t *userStatePtr, const lptmr_user_config_t* userConfigPtr)
{
    assert(instance < LPTMR_INSTANCE_COUNT);

    LPTMR_Type * base = g_lptmrBase[instance];
    lptmr_prescaler_user_config_t prescalerUserConfig;
    lptmr_working_mode_user_config_t workingModeUserConfig;

    if ((!userConfigPtr) || (!userStatePtr))
    {
        return kStatus_LPTMR_NullArgument;
    }

    /* prescaler value 0 is invalid while working as pulse counter */
    if ((kLptmrTimerModePulseCounter == userConfigPtr->timerMode) &&
         (true == userConfigPtr->prescalerEnable) &&
         (kLptmrPrescalerDivide2 == userConfigPtr->prescalerValue))
    {
        return kStatus_LPTMR_InvalidPrescalerValue;
    }

    /* Enable clock for lptmr */
    CLOCK_SYS_EnableLptmrClock(instance);

    /* Disable lptmr and reset lptmr logic */
    LPTMR_HAL_Disable(base);

    /* LPTMR prescaler configure */
    prescalerUserConfig.prescalerClockSelect = (lptmr_prescaler_clock_select_t)userConfigPtr->prescalerClockSource;
    prescalerUserConfig.prescalerBypass = (uint8_t)(userConfigPtr->prescalerEnable == false);
    prescalerUserConfig.prescalerValue = userConfigPtr->prescalerValue;
    LPTMR_HAL_SetPrescalerMode(base, prescalerUserConfig);

    /* Working Mode configure */
    workingModeUserConfig.timerModeSelect = userConfigPtr->timerMode;
    workingModeUserConfig.freeRunningEnable = userConfigPtr->freeRunningEnable;
    workingModeUserConfig.pinPolarity = userConfigPtr->pinPolarity;
    workingModeUserConfig.pinSelect = userConfigPtr->pinSelect;
    LPTMR_HAL_SetTimerWorkingMode(base,workingModeUserConfig);

    /* Internal context */
    g_lptmrStatePtr[instance] = userStatePtr;

    userStatePtr->userCallbackFunc = NULL;

    /* LPTMR interrupt */
    if (userConfigPtr->isInterruptEnabled)
    {
        LPTMR_HAL_SetIntCmd(base,true);
        INT_SYS_EnableIRQ(g_lptmrIrqId[instance]);
    }
    else
    {
        LPTMR_HAL_SetIntCmd(base,false);
        INT_SYS_DisableIRQ(g_lptmrIrqId[instance]);
    }

    /* Caculate prescaler clock frequency */
    if ( kLptmrTimerModeTimeCounter == userConfigPtr->timerMode)
    {
        userStatePtr->prescalerClockHz = CLOCK_SYS_GetLptmrFreq(instance,
                userConfigPtr->prescalerClockSource);

        if (userConfigPtr->prescalerEnable)
        {
            userStatePtr->prescalerClockHz = (userStatePtr->prescalerClockHz >> ((uint32_t)(userConfigPtr->prescalerValue+1)));
        }
    }

    return kStatus_LPTMR_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPTMR_DRV_Deinit
 * Description   : Deinit the LPTMR driver.
 * This function will deinit the LPTMR driver, disable LPTMR clock,
 * and disable LPTMR interrupt.
 *
 *END**************************************************************************/
lptmr_status_t LPTMR_DRV_Deinit(uint32_t instance)
{
    assert(instance < LPTMR_INSTANCE_COUNT);
    assert(CLOCK_SYS_GetLptmrGateCmd(instance));

    LPTMR_Type * base = g_lptmrBase[instance];

    /* Turn off lptmr hal */
    LPTMR_HAL_Disable(base);

    /* Reset all register to reset value */
    LPTMR_HAL_Init(base);

    /* Disable the interrupt */
    INT_SYS_DisableIRQ(g_lptmrIrqId[instance]);

    /* Disable clock for lptmr */
    CLOCK_SYS_DisableLptmrClock(instance);

    /* Cleared state pointer */
    g_lptmrStatePtr[instance] = NULL;

    return kStatus_LPTMR_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPTMR_DRV_Start
 * Description   : Start LPTMR counter
 * This function will start LPTMR internal counter to count the time or pulse
 *
 *END**************************************************************************/
lptmr_status_t LPTMR_DRV_Start(uint32_t instance)
{
    assert(instance < LPTMR_INSTANCE_COUNT);
    assert(CLOCK_SYS_GetLptmrGateCmd(instance));

    LPTMR_Type * base = g_lptmrBase[instance];

    LPTMR_HAL_Enable(base);

    return kStatus_LPTMR_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPTMR_DRV_Stop
 * Description   : Stop LPTMR counter
 * This function will stop LPTMR internal counter
 *
 *END**************************************************************************/
lptmr_status_t LPTMR_DRV_Stop(uint32_t instance)
{
    assert(instance < LPTMR_INSTANCE_COUNT);
    assert(CLOCK_SYS_GetLptmrGateCmd(instance));

    LPTMR_Type * base = g_lptmrBase[instance];

    LPTMR_HAL_Disable(base);

    return kStatus_LPTMR_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPTMR_DRV_SetTimerPeriodUs
 * Description   : Set LPTMR timer counter period with unit microsecond
 * This function is used to set LPTMR timer counter period with unit microsecond
 *
 *END**************************************************************************/
lptmr_status_t LPTMR_DRV_SetTimerPeriodUs(uint32_t instance, uint32_t us)
{
    assert(instance < LPTMR_INSTANCE_COUNT);
    assert(us > 0);
    assert(CLOCK_SYS_GetLptmrGateCmd(instance));

    LPTMR_Type * base = g_lptmrBase[instance];
    uint32_t tick_count;

    if (g_lptmrStatePtr[instance]->prescalerClockHz < 1000000U)
    {
        tick_count = (us/(1000000U/g_lptmrStatePtr[instance]->prescalerClockHz));
    }
    else
    {
        tick_count = (us*(g_lptmrStatePtr[instance]->prescalerClockHz/1000000U));
    }

    /* CMR register is 16 Bits */
    if (tick_count > 0xFFFFU)
    {
        return kStatus_LPTMR_TimerPeriodUsTooLarge;
    }

    /* CMR of 0 leaves the hardware trigger asserted */
    if (tick_count <= 1)
    {
        return kStatus_LPTMR_TimerPeriodUsTooSmall;
    }

    /* We have to reduce by 1 as interrupt occurs when the CNR register equals the value of
     * of CMR register and then increments
     */
    LPTMR_HAL_SetCompareValue(base, tick_count - 1);

    return kStatus_LPTMR_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPTMR_DRV_GetCurrentTimeUs
 * Description   : Get LPTMR current time with unit microsecond
 * This function is used to get LPTMR current time with unit microsecond
 *
 *END**************************************************************************/
uint32_t LPTMR_DRV_GetCurrentTimeUs(uint32_t instance)
{
    assert(instance < LPTMR_INSTANCE_COUNT);
    assert(CLOCK_SYS_GetLptmrGateCmd(instance));

    LPTMR_Type * base = g_lptmrBase[instance];

    uint32_t us;

    if (g_lptmrStatePtr[instance]->prescalerClockHz < 1000000U)
    {
        us = LPTMR_HAL_GetCounterValue(base)*(1000000U/g_lptmrStatePtr[instance]->prescalerClockHz);
    }
    else
    {
        us = LPTMR_HAL_GetCounterValue(base)/(g_lptmrStatePtr[instance]->prescalerClockHz/1000000U);
    }

    return us;
}


/*FUNCTION**********************************************************************
 *
 * Function Name : LPTMR_DRV_SetPulsePeriodCount
 * Description   : Set the pulse period value while LPTMR working in pulse counter mode
 * This function is used to set the pulse period value while LPTMR working in pulse counter mode
 *
 *END**************************************************************************/
lptmr_status_t LPTMR_DRV_SetPulsePeriodCount(uint32_t instance, uint32_t pulsePeriodCount)
{
    assert(instance < LPTMR_INSTANCE_COUNT);
    assert(pulsePeriodCount > 0);
    assert(CLOCK_SYS_GetLptmrGateCmd(instance));

    LPTMR_Type * base = g_lptmrBase[instance];

    LPTMR_HAL_SetCompareValue(base, pulsePeriodCount);

    return kStatus_LPTMR_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPTMR_DRV_GetCurrentPulseCount
 * Description   : Get current pulse count captured in the pulse input pin
 * This function is used to get current pulse count captured in the pulse input pin
 *
 *END**************************************************************************/
uint32_t LPTMR_DRV_GetCurrentPulseCount(uint32_t instance)
{
    assert(instance < LPTMR_INSTANCE_COUNT);
    assert(CLOCK_SYS_GetLptmrGateCmd(instance));

    LPTMR_Type * base = g_lptmrBase[instance];
    uint32_t count;

    count = LPTMR_HAL_GetCounterValue(base);

    return count;
}


/*FUNCTION*********************************************************************
 *
 * Function Name : LPTMR_DRV_InstallCallback
 * Description   : Install the user-defined callback in LPTMR module.
 * When an LPTMR interrupt request is served, the callback will be executed
 * inside the ISR.
 *
 *END*************************************************************************/
lptmr_status_t LPTMR_DRV_InstallCallback(uint32_t instance, lptmr_callback_t userCallback)
{
    assert(instance < LPTMR_INSTANCE_COUNT);

    assert (instance < LPTMR_INSTANCE_COUNT);
    if (!g_lptmrStatePtr[instance])
    {
        return kStatus_LPTMR_NotInitlialized;
    }
    /* Fill callback function into state structure. */
    g_lptmrStatePtr[instance]->userCallbackFunc = userCallback;

    return kStatus_LPTMR_Success;
}


/*FUNCTION*********************************************************************
 *
 * Function Name : LPTMR_DRV_IRQHandler
 * Description   : The driver-defined ISR in LPTMR module.
 * It includes the process for interrupt mode defined by driver. Currently, it
 * will be called inside the system-defined ISR.
 *
 *END*************************************************************************/
void LPTMR_DRV_IRQHandler(uint32_t instance)
{
    assert(instance < LPTMR_INSTANCE_COUNT);
    assert(CLOCK_SYS_GetLptmrGateCmd(instance));

    LPTMR_Type * base = g_lptmrBase[instance];

    /* Clear interrupt flag */
    LPTMR_HAL_ClearIntFlag(base);

    if (g_lptmrStatePtr[instance])
    {
        if (g_lptmrStatePtr[instance]->userCallbackFunc)
        {
            /* Execute user-defined callback function. */
            (*(g_lptmrStatePtr[instance]->userCallbackFunc))();
        }
    }
}
#endif
/*******************************************************************************
 * EOF
 *******************************************************************************/

