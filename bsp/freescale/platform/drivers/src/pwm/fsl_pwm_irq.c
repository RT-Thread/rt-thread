/*
 * Copyright (c) 2014, Freescale Semiconductor, Inc.
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
#include "fsl_pwm_driver.h"

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/* ISR */
void PWM_Reload0(void);

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief Implementation of  handler named in startup code.
 *
 *  Passes 0 to generic PWM IRQ handler.
 */
void PWMA_CMP0_IRQHandler(void)
{
    /* Clear interrupt pending capture flags A0,A1,B0,B1,X0,X1. */
    PWM_HAL_ClearCmpFlags(g_pwmBase[0], 0U, 0x3fU);
}

/*!
 * @brief Implementation of  handler named in startup code.
 *
 *  Passes 0 to generic PWM IRQ handler.
 */
void PWMA_RELOAD0_IRQHandler(void)
{
    /* Call user function */
    PWM_Reload0();

    /* Clear interrupt pending flag. */
    PWM_HAL_ClearReloadFlag(g_pwmBase[0], 0U);
}

/*!
 * @brief Implementation of  handler named in startup code.
 *
 *  Passes 0 to generic PWM IRQ handler.
 */
void PWMA_CMP1_IRQHandler(void)
{
    /* Clear interrupt pending capture flags A0,A1,B0,B1,X0,X1. */
    PWM_HAL_ClearCmpFlags(g_pwmBase[0], 1U, 0x3fU);
}

/*!
 * @brief Implementation of  handler named in startup code.
 *
 *  Passes 0 to generic PWM IRQ handler.
 */
void PWMA_RELOAD1_IRQHandler(void)
{
    /* Clear interrupt pending flag. */
    PWM_HAL_ClearReloadFlag(g_pwmBase[0], 1U);
}

/*!
 * @brief Implementation of  handler named in startup code.
 *
 *  Passes 0 to generic PWM IRQ handler.
 */
void PWMA_CMP2_IRQHandler(void)
{
    /* Clear interrupt pending capture flags A0,A1,B0,B1,X0,X1. */
    PWM_HAL_ClearCmpFlags(g_pwmBase[0];, 2U, 0x3fU);
}

/*!
 * @brief Implementation of  handler named in startup code.
 *
 *  Passes 0 to generic PWM IRQ handler.
 */
void PWMA_RELOAD2_IRQHandler(void)
{
    /* Clear interrupt pending flag. */
    PWM_HAL_ClearReloadFlag(g_pwmBase[0], 2U);
}

/*!
 * @brief Implementation of  handler named in startup code.
 *
 *  Passes 0 to generic PWM IRQ handler.
 */
void PWMA_CMP3_IRQHandler(void)
{
    /* Clear interrupt pending capture flags A0,A1,B0,B1,X0,X1. */
    PWM_HAL_ClearCmpFlags(g_pwmBase[0], 3U, 0x3fU);
}

/*!
 * @brief Implementation of  handler named in startup code.
 *
 *  Passes 0 to generic PWM IRQ handler.
 */
void PWMA_RELOAD3_IRQHandler(void)
{
    /* Clear interrupt pending flag. */
    PWM_HAL_ClearReloadFlag(g_pwmBase[0], 3U);
}

/*!
 * @brief Implementation of  handler named in startup code.
 *
 *  Passes 0 to generic PWM IRQ handler.
 */
void PWMA_CAP_IRQHandler(void)
{
    PWM_Type *pwmBase = g_pwmBase[0];

    /* Clear interrupt pending flags from SM0,1,2. */
    PWM_HAL_ClearCapFlagCF(pwmBase, 0U, kCfa1);
    PWM_HAL_ClearCapFlagCF(pwmBase, 1U, kCfa1);
    PWM_HAL_ClearCapFlagCF(pwmBase, 2U, kCfa1);
}

/*!
 * @brief Implementation of  handler named in startup code.
 *
 *  Passes 0 to generic PWM IRQ handler.
 */
void PWMA_RERR_IRQHandler(void)
{
    PWM_Type *pwmBase = g_pwmBase[0];

    /* Clear interrupt pending flags from SM0,1,2. */
    PWM_HAL_ClearReloadErrFlagREF(pwmBase, 0U);
    PWM_HAL_ClearReloadErrFlagREF(pwmBase, 1U);
    PWM_HAL_ClearReloadErrFlagREF(pwmBase, 2U);
}

/*!
 * @brief Implementation of  handler named in startup code.
 *
 *  Passes 0 to generic PWM IRQ handler.
 */
void PWMA_FAULT_IRQHandler(void)
{
    /* Clear interrupt pending flags from SM0,1,2. */
    PWM_HAL_ClearFaultFlags(g_pwmBase[0], 0x7U);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/

