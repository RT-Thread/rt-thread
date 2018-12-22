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
#ifndef __INTERRUPT_H__
#define __INTERRUPT_H__

#include "sdk_types.h"
#include "irq_numbers.h"

//! @addtogroup diag_interrupt
//! @{

/*!
 * @file interrupt.h
 * @brief Interface for the interrupt manager.
 */

////////////////////////////////////////////////////////////////////////////////
// Definitions
////////////////////////////////////////////////////////////////////////////////

//! @brief
typedef enum {
    CPU_0,
    CPU_1,
    CPU_2,
    CPU_3,
} cpuid_e;

//! @brief Interrupt service routine.
typedef void (*irq_hdlr_t) (void);

////////////////////////////////////////////////////////////////////////////////
// API
////////////////////////////////////////////////////////////////////////////////

#if defined(__cplusplus)
extern "C" {
#endif

//! @brief Enable an interrupt.
//!
//! Sets the interrupt priority and makes it non-secure. Then the interrupt is
//! enabled on the CPU specified by @a cpu_id.
//!
//! @param irq_id The interrupt number to enable.
//! @param cpu_id The index of the CPU for which the interrupt will be enabled.
//! @param priority The interrupt priority, from 0-255. Lower numbers have higher priority.
void enable_interrupt(uint32_t irq_id, uint32_t cpu_id, uint32_t priority);

//! @brief Disable an interrupt on the specified CPU.
//!
//! @param irq_id The interrupt number to disabled.
//! @param cpu_id The index of the CPU for which the interrupt will be disabled.
void disable_interrupt(uint32_t irq_id, uint32_t cpu_id);

//! @brief Set the interrupt service routine for the specified interrupt.
//!
//! @param irq_id The interrupt number.
//! @param isr Function that will be called to handle the interrupt.
void register_interrupt_routine(uint32_t irq_id, irq_hdlr_t isr);

//! @brief Interrupt handler that simply prints a message.
void default_interrupt_routine(void);

#if defined(__cplusplus)
}
#endif

//! @}

#endif
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
