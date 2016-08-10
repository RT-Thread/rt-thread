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

#if FSL_FEATURE_SOC_PWM_COUNT

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Table of base addresses for PWM instances. */
PWM_Type * const g_pwmBase[PWM_INSTANCE_COUNT] = PWM_BASE_PTRS;

/* Table to save PWM IRQ enum numbers defined in CMSIS header file. */
const IRQn_Type g_pwmCmpIrqId[FSL_FEATURE_PWM_CMP_INT_HANDLER_COUNT] = PWM_CMP_IRQS;
const IRQn_Type g_pwmReloadIrqId[FSL_FEATURE_PWM_RELOAD_INT_HANDLER_COUNT] = PWM_RELOAD_IRQS;
const IRQn_Type g_pwmCapIrqId[FSL_FEATURE_PWM_CAP_INT_HANDLER_COUNT] = PWM_CAP_IRQS;
const IRQn_Type g_pwmRerrIrqId[FSL_FEATURE_PWM_RERR_INT_HANDLER_COUNT] = PWM_RERR_IRQS;
const IRQn_Type g_pwmFaultIrqId[FSL_FEATURE_PWM_FAULT_INT_HANDLER_COUNT] = PWM_FAULT_IRQS;

#endif /* FSL_FEATURE_SOC_PWM_COUNT */

/*******************************************************************************
 * EOF
 ******************************************************************************/

