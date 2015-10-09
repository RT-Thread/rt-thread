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

#include "fsl_lptmr_hal.h"
#if FSL_FEATURE_SOC_LPTMR_COUNT

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*******************************************************************************
 * Variables
 *******************************************************************************/

/*******************************************************************************
 * Code
 *******************************************************************************/
#endif

/*******************************************************************************
 * EOF
 *******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : LPTMR_HAL_Init
 * Description   : Initialize LPTMR module to reset state.
 *
 *END**************************************************************************/
void LPTMR_HAL_Init(LPTMR_Type * base)
{
    lptmr_working_mode_user_config_t working_mode_config;
    lptmr_prescaler_user_config_t prescaler_config;
    
    LPTMR_HAL_Disable(base);
    LPTMR_HAL_ClearIntFlag(base);

    working_mode_config.timerModeSelect = kLptmrTimerModeTimeCounter;
    working_mode_config.freeRunningEnable = false;
    working_mode_config.pinPolarity = kLptmrPinPolarityActiveHigh;
    working_mode_config.pinSelect = kLptmrPinSelectInput0;
    LPTMR_HAL_SetTimerWorkingMode(base, working_mode_config);
    
    prescaler_config.prescalerValue = kLptmrPrescalerDivide2;
    prescaler_config.prescalerBypass = true;
    prescaler_config.prescalerClockSelect = kLptmrPrescalerClock0;
    LPTMR_HAL_SetPrescalerMode(base, prescaler_config);
    
    LPTMR_HAL_SetCompareValue(base, 0U);
    LPTMR_HAL_SetIntCmd(base, false);
}

 /*FUNCTION**********************************************************************
 *
 * Function Name : LPTMR_HAL_SetTimerWorkingMode
 * Description   : Config the LPTMR working mode.
 *
 *END**************************************************************************/
void LPTMR_HAL_SetTimerWorkingMode(LPTMR_Type * base,  lptmr_working_mode_user_config_t timerMode)
{
    uint32_t csr;
    
    csr = LPTMR_RD_CSR(base);
    csr &= ~(LPTMR_CSR_TCF_MASK | LPTMR_CSR_TMS_MASK | LPTMR_CSR_TFC_MASK 
             | LPTMR_CSR_TPP_MASK | LPTMR_CSR_TPS_MASK);
    csr |= LPTMR_CSR_TMS(timerMode.timerModeSelect) 
        | LPTMR_CSR_TFC(timerMode.freeRunningEnable)
        | LPTMR_CSR_TPP(timerMode.pinPolarity) 
        | LPTMR_CSR_TPS(timerMode.pinSelect); 
    
    LPTMR_WR_CSR(base, csr);
}

 /*FUNCTION**********************************************************************
 *
 * Function Name : LPTMR_HAL_SetPrescalerMode
 * Description   : Set the LPTMR prescaler mode.
 *
 *END**************************************************************************/
void LPTMR_HAL_SetPrescalerMode(LPTMR_Type * base,  lptmr_prescaler_user_config_t prescaler_config)
{
    uint32_t psr;
    
    psr = LPTMR_PSR_PCS(prescaler_config.prescalerClockSelect)
        | LPTMR_PSR_PBYP(prescaler_config.prescalerBypass)
        | LPTMR_PSR_PRESCALE(prescaler_config.prescalerValue);

    LPTMR_WR_PSR(base, psr);
}

 /*FUNCTION**********************************************************************
 *
 * Function Name : LPTMR_HAL_GetCounterValue
 * Description   : Gets the LPTMR counter value..
 *
 *END**************************************************************************/
uint32_t LPTMR_HAL_GetCounterValue(LPTMR_Type * base)
{
    LPTMR_BWR_CNR_COUNTER(base, 0);  /* Must first write to the CNR with any value */
    return (uint32_t)(LPTMR_BRD_CNR_COUNTER(base));
}
