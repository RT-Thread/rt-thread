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

#include "fsl_ewm_hal.h"
#if FSL_FEATURE_SOC_EWM_COUNT

/*******************************************************************************
 * Definitions
 *******************************************************************************/

/*******************************************************************************
 * Variables
 *******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : EWM_HAL_SetConfig
 * Description   : Initialize EWM peripheral to workable state.
 *
 *END**************************************************************************/
void EWM_HAL_SetConfig(EWM_Type * base, const ewm_config_t *ewmConfigPtr)
{
	uint32_t value = 0;
	assert(ewmConfigPtr);
	value = EWM_CTRL_EWMEN(ewmConfigPtr->ewmEnable) | EWM_CTRL_ASSIN(ewmConfigPtr->ewmInAssertLogic) | 
		EWM_CTRL_INEN(ewmConfigPtr->ewmInEnable) | EWM_CTRL_INTEN(ewmConfigPtr->intEnable);
#if FSL_FEATURE_EWM_HAS_PRESCALER
        EWM_WR_CLKPRESCALER(base, ewmConfigPtr->ewmPrescalerValue);
#endif
        EWM_WR_CMPL(base, ewmConfigPtr->ewmCmpLowValue);
        EWM_WR_CMPH(base, ewmConfigPtr->ewmCmpHighValue);
	EWM_WR_CTRL(base, value);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EWM_HAL_Init
 * Description   : Initialize EWM peripheral to workable state.
 *
 *END**************************************************************************/
void EWM_HAL_Init(EWM_Type * base)
{
    ewm_config_t ewmCommonConfig;
    ewmCommonConfig.ewmEnable         = true;
    ewmCommonConfig.ewmInEnable       = true;
    ewmCommonConfig.ewmInAssertLogic  = true;
    ewmCommonConfig.intEnable         = true;
#if FSL_FEATURE_EWM_HAS_PRESCALER
    ewmCommonConfig.ewmPrescalerValue = 0;
#endif
    ewmCommonConfig.ewmCmpLowValue    = 0x00;
    ewmCommonConfig.ewmCmpHighValue   = 0xfe;
    EWM_HAL_SetConfig(base, &ewmCommonConfig);
}

#endif
/*******************************************************************************
 * EOF
 *******************************************************************************/

