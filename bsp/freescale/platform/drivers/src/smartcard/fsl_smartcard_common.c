/*
 * Copyright (c) 2014 - 2015, Freescale Semiconductor, Inc.
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

/*******************************************************************************
 * Variables
 ******************************************************************************/
#if defined(FSL_FEATURE_UART_HAS_SMART_CARD_SUPPORT)
#if (FSL_FEATURE_UART_HAS_SMART_CARD_SUPPORT == 1)
#define HW_SMARTCARD_INSTANCE_COUNT  UART_INSTANCE_COUNT
#endif
#elif defined(FSL_FEATURE_SOC_EMVSIM_COUNT)
#define HW_SMARTCARD_INSTANCE_COUNT  FSL_FEATURE_SOC_EMVSIM_COUNT
/* Pointer to emvsim runtime state structure.*/
void * g_emvsimStatePtr[EMVSIM_INSTANCE_COUNT] = { NULL };

/* Table of base addresses for emvsim instances. */
EMVSIM_Type * const g_emvsimBase[EMVSIM_INSTANCE_COUNT] = EMVSIM_BASE_PTRS;

/* Table to save UART IRQ numbers defined in CMSIS files. */
IRQn_Type g_emvsimRxTxIrqId[EMVSIM_INSTANCE_COUNT] = EMVSIM_IRQS;
#else
    #error "No valid Smart Card Module defined!"
#endif

#if defined(HW_SMARTCARD_INSTANCE_COUNT)
/* Pointer to smartcard runtime state structure.*/
void * g_smartcardStatePtr[HW_SMARTCARD_INSTANCE_COUNT] = { NULL };
/* Pointer to interface/PHY runtime state structure.*/
void * g_smartcardInterfaceStatePtr[HW_SMARTCARD_INSTANCE_COUNT] = { NULL };
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/

