/*
 * Copyright (c) 2009-2012, Freescale Semiconductor, Inc.
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
 * @file  interrupt.c
 *
 * @ingroup diag_init
 */

#include "core/interrupt.h"
#include "core/gic.h"

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

//! @brief Array of handler functions assigned to each interrupt.
irq_hdlr_t g_interrupt_handlers[IMX_INTERRUPT_COUNT];

//! @brief Current interrupt being handled for each CPU.
//!
//! This variable can be used to determine the interrupt source
//! while being in an interrupt context.
//!
//! Being updated during an interrupt, therefore at any time,
//! that variable shouldn't be used out of this particular context.
volatile uint32_t g_vectNum[4];

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

//! @brief Handles IRQ exceptions.
__attribute__ ((interrupt("IRQ")))
void IRQ_HDLR(void)
{
    // vectNum = RESERVED[31:13] | CPUID[12:10] | INTERRUPT_ID[9:0] 
    // send ack and get ID source 
    uint32_t vectNum = gic_read_irq_ack();
    
    // Check that INT_ID isn't 1023 or 1022 (spurious interrupt) 
    if (vectNum & 0x0200)
    {
        gic_write_end_of_irq(vectNum);  // send end of irq 
    }
    else
    {
        // copy the local value to the global image of CPUID
        unsigned cpu = (vectNum >> 10) & 0x7;
        unsigned irq = vectNum & 0x1FF;
        
        // Store the current interrupt number.
        g_vectNum[cpu] = irq;
        
        // Call the service routine stored in the handlers array. If there isn't
        // one for this IRQ, then call the default handler.
        irq_hdlr_t isr = g_interrupt_handlers[irq];
        if (isr)
        {
            isr();
        }
        else
        {
            default_interrupt_routine();
        }
        
        // Clear current interrupt number.
        g_vectNum[cpu] = 0;
        
        // Signal the end of the irq.
        gic_write_end_of_irq(vectNum);
    }
}

void disable_interrupt(uint32_t irq_id, uint32_t cpu_id)
{
    gic_enable_irq(irq_id, false);
    gic_set_cpu_target(irq_id, cpu_id, false);
}

void enable_interrupt(uint32_t irq_id, uint32_t cpu_id, uint32_t priority)
{
    gic_set_irq_priority(irq_id, priority);
    gic_set_irq_security(irq_id, false);    // set IRQ as non-secure
    gic_set_cpu_target(irq_id, cpu_id, true);
    gic_enable_irq(irq_id, true);
}

// set funcISR as the ISR function for the source ID #
void register_interrupt_routine(uint32_t irq_id, irq_hdlr_t isr)
{
    g_interrupt_handlers[irq_id] = isr;
}

void default_interrupt_routine(void)
{
    // find a way to address an IRQ handled by another CPU. Assumes
    // here that CPU_0 is used.
    printf("Interrupt %d has been asserted\n", g_vectNum[0]);
}

////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
