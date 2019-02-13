/*
 * The Clear BSD License
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 *  that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of the copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
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

#include "fsl_inputmux.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.inputmux"
#endif


/*******************************************************************************
 * Code
 ******************************************************************************/

void INPUTMUX_Init(INPUTMUX_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
#if defined(FSL_FEATURE_INPUTMUX_HAS_NO_INPUTMUX_CLOCK_SOURCE) && FSL_FEATURE_INPUTMUX_HAS_NO_INPUTMUX_CLOCK_SOURCE
    CLOCK_EnableClock(kCLOCK_Sct);
    CLOCK_EnableClock(kCLOCK_Dma);
#else
    CLOCK_EnableClock(kCLOCK_InputMux);
#endif /* FSL_FEATURE_INPUTMUX_HAS_NO_INPUTMUX_CLOCK_SOURCE */
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}

void INPUTMUX_AttachSignal(INPUTMUX_Type *base, uint32_t index, inputmux_connection_t connection)
{
    uint32_t pmux_id;
    uint32_t output_id;

    /* extract pmux to be used */
    pmux_id = ((uint32_t)(connection)) >> PMUX_SHIFT;
    /*  extract function number */
    output_id = ((uint32_t)(connection)) & 0xffffU;
    /* programm signal */
    *(volatile uint32_t *)(((uint32_t)base) + pmux_id + (index * 4)) = output_id;
}

#if defined(FSL_FEATURE_INPUTMUX_HAS_SIGNAL_ENA)
void INPUTMUX_EnableSignal(INPUTMUX_Type *base, inputmux_signal_t signal, bool enable)
{
    uint32_t ena_id;
    uint32_t bit_offset;

    /* extract enable register to be used */
    ena_id = ((uint32_t)(signal)) >> ENA_SHIFT;
    /* extract enable bit offset */
    bit_offset = ((uint32_t)(signal)) & 0xfU;
    /* set signal */
    if (enable)
    {
        *(volatile uint32_t *)(((uint32_t)base) + ena_id) |= (1U << bit_offset);
    }
    else
    {
        *(volatile uint32_t *)(((uint32_t)base) + ena_id) &= ~(1U << bit_offset);
    }
}
#endif

void INPUTMUX_Deinit(INPUTMUX_Type *base)
{
#if !(defined(FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL) && FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL)
#if defined(FSL_FEATURE_INPUTMUX_HAS_NO_INPUTMUX_CLOCK_SOURCE) && FSL_FEATURE_INPUTMUX_HAS_NO_INPUTMUX_CLOCK_SOURCE
    CLOCK_DisableClock(kCLOCK_Sct);
    CLOCK_DisableClock(kCLOCK_Dma);
#else
    CLOCK_DisableClock(kCLOCK_InputMux);
#endif /* FSL_FEATURE_INPUTMUX_HAS_NO_INPUTMUX_CLOCK_SOURCE */
#endif /* FSL_SDK_DISABLE_DRIVER_CLOCK_CONTROL */
}
