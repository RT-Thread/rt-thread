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

#include "fsl_wdog_hal.h"
#if FSL_FEATURE_SOC_WDOG_COUNT

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
 * Function Name : WDOG_HAL_SetConfig
 * Description   : Configures WDOG control register.
 *
 *END**************************************************************************/
void WDOG_HAL_SetConfig(WDOG_Type * base, const wdog_config_t *configPtr)
{
    assert(configPtr);
    uint32_t value = 0;
    value = WDOG_STCTRLH_WDOGEN(configPtr->wdogEnable) | WDOG_STCTRLH_CLKSRC(configPtr->clkSrc) | 
            WDOG_STCTRLH_IRQRSTEN(configPtr->intEnable) | WDOG_STCTRLH_WINEN(configPtr->winEnable) | 
            WDOG_STCTRLH_ALLOWUPDATE(configPtr->updateEnable) | WDOG_STCTRLH_DBGEN(configPtr->workMode.kWdogEnableInDebugMode) | 
            WDOG_STCTRLH_STOPEN(configPtr->workMode.kWdogEnableInStopMode) |
#if FSL_FEATURE_WDOG_HAS_WAITEN
            WDOG_STCTRLH_WAITEN(configPtr->workMode.kWdogEnableInWaitMode) |
#endif
            WDOG_STCTRLH_DISTESTWDOG(1U);
    WDOG_BWR_PRESC_PRESCVAL(base, configPtr->prescaler);
    WDOG_WR_WINH(base, (uint16_t)((configPtr->windowValue>>16U) & 0xFFFFU));
    WDOG_WR_WINL(base, (uint16_t)((configPtr->windowValue) & 0xFFFFU));
    WDOG_WR_TOVALH(base, (uint16_t)((configPtr->timeoutValue >> 16U) & 0xFFFFU));
    WDOG_WR_TOVALL(base, (uint16_t)((configPtr->timeoutValue) & 0xFFFFU));
    WDOG_WR_STCTRLH(base, value);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : WDOG_HAL_Init
 * Description   : Initialize WDOG peripheral to workable state.
 *
 *END**************************************************************************/
void WDOG_HAL_Init(WDOG_Type * base)
{
    wdog_work_mode_t initWorkmode;
#if FSL_FEATURE_WDOG_HAS_WAITEN
    initWorkmode.kWdogEnableInWaitMode  = true;
#endif
    initWorkmode.kWdogEnableInStopMode  = false;
    initWorkmode.kWdogEnableInDebugMode = false;
    wdog_config_t initConfig;
    initConfig.wdogEnable   = true;
    initConfig.clkSrc       = kWdogLpoClkSrc;
    initConfig.prescaler    = kWdogClkPrescalerDivide1;
    initConfig.workMode     = initWorkmode;
    initConfig.updateEnable = true;
    initConfig.intEnable    = false;
    initConfig.winEnable    = false;
    WDOG_HAL_Unlock(base);
    WDOG_HAL_SetTimeoutValue(base, 0x004C4B4C);
    WDOG_HAL_SetWindowValue(base, 0);
    WDOG_HAL_SetConfig(base, &initConfig);
}
#endif

/*******************************************************************************
 * EOF
 *******************************************************************************/

