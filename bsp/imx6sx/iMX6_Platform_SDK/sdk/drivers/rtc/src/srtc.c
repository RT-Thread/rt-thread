/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
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

/*!
 * @file srtc.c
 * @brief  SRTC driver source file.
 *
 * @ingroup diag_timer
 */

#include "sdk.h"
#include "rtc/srtc.h"
#include "registers/regssnvs.h"
#include "irq_numbers.h"
#include "interrupt.h"
#include "snvs/snvs.h"

/*!
 * @brief SRTC strucures used by the driver.
 */
typedef struct snvs_srtc_module_ {
    srtc_callback_t onetime_timer_callback;
    void * callbackArg;
} snvs_srtc_module_t;

void snvs_srtc_setup_interrupt(void (*irq_subroutine)(void), uint8_t state);

static snvs_srtc_module_t s_snvs_srtc_module;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

/*!
 * @brief Setup SNVS interrupt.
 *
 * Enables or disables the related HW module interrupt, and attached the related
 * sub-routine into the vector table.
 *
 * @param   port Pointer to the SNVS module structure.
 * @param   state true to enable or false to disable.
 */
void snvs_srtc_setup_interrupt(void (*irq_subroutine)(void), uint8_t state)
{
    uint32_t irq_id = IMX_INT_SNVS;

    if (state)
    {
        // register the IRQ sub-routine 
        register_interrupt_routine(irq_id, irq_subroutine);
        
        // enable the IRQ 
        enable_interrupt(irq_id, CPU_0, 0);
    }
    else
    {
        // disable the IRQ 
        disable_interrupt(irq_id, CPU_0);
    }
}

/*!
 * @brief SNVS SRTC interrupt handler.
 */
void snvs_srtc_interrupt_handler(void)
{
    snvs_srtc_setup_interrupt(NULL, false);

    if (HW_SNVS_LPSR.B.LPTA && s_snvs_srtc_module.onetime_timer_callback != NULL)
    {
        HW_SNVS_LPSR_CLR(BM_SNVS_LPSR_LPTA);

        s_snvs_srtc_module.onetime_timer_callback(s_snvs_srtc_module.callbackArg);
        s_snvs_srtc_module.onetime_timer_callback = NULL;
        s_snvs_srtc_module.callbackArg = 0;
        snvs_srtc_alarm(false);
    }   
    else
    {
        snvs_srtc_setup_interrupt(snvs_srtc_interrupt_handler, true);
    }
}

void srtc_init(void)
{
    // Clear state.
    s_snvs_srtc_module.onetime_timer_callback = NULL;
    s_snvs_srtc_module.callbackArg = 0;

    // Initialize SNVS driver 
    snvs_init();

    // Start SRTC counter 
    snvs_srtc_counter(true);

    // Keep time alarm disabled 
    snvs_srtc_alarm(false);
}

void srtc_deinit(void)
{
    // Disable the interrupt 
    snvs_srtc_setup_interrupt(NULL, false);

    // Disable the counter 
    snvs_srtc_counter(false);
    snvs_srtc_alarm(false);

    // Deinitialize SNVS 
    snvs_deinit();
}

void srtc_setup_onetime_timer(uint32_t timeout, srtc_callback_t callback, void * arg)
{
    // Disables the interrupt 
    snvs_srtc_setup_interrupt(NULL, false);

    // Clear the SRTC counter 
    snvs_srtc_set_counter(0);

    // Program the timeout value 
    snvs_srtc_set_alarm_timeout(timeout);

    // Set the callback function 
    s_snvs_srtc_module.onetime_timer_callback = callback;
    s_snvs_srtc_module.callbackArg = arg;

    // Reanable the interrupt 
    snvs_srtc_setup_interrupt(snvs_srtc_interrupt_handler, true);
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
