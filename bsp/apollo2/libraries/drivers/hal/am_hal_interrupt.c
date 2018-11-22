//*****************************************************************************
//
//  am_hal_interrupt.c
//! @file
//!
//! @brief Helper functions supporting interrupts and NVIC operation.
//!
//! These functions may be used for NVIC-level interrupt configuration.
//!
//! @addtogroup interrupt2 Interrupt (ARM NVIC support functions)
//! @ingroup apollo2hal
//! @{
//
//*****************************************************************************

//*****************************************************************************
//
// Copyright (c) 2017, Ambiq Micro
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice,
// this list of conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its
// contributors may be used to endorse or promote products derived from this
// software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//
// This is part of revision 1.2.11 of the AmbiqSuite Development Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "am_mcu_apollo.h"

//*****************************************************************************
//
//! @brief Enable an interrupt.
//!
//! @param ui32Interrupt The ISR number of the interrupt to be enabled.
//!
//! This function enables an interrupt signal to the NVIC based on the provided
//! ISR number.
//!
//! @return None
//
//*****************************************************************************
void
am_hal_interrupt_enable(uint32_t ui32Interrupt)
{
    //
    // Check to see what type of interrupt this is.
    //
    if ( ui32Interrupt > 15 )
    {
        //
        // If this ISR number corresponds to a "normal" peripheral interrupt,
        // enable it using the NVIC register.
        //
        AM_REG(NVIC, ISER0) = 0x1 << ((ui32Interrupt - 16) & 0x1F);
    }
    else
    {
        //
        // If this is an ARM internal interrupt number, route it to the
        // appropriate enable register.
        //
        switch(ui32Interrupt)
        {
            case AM_HAL_INTERRUPT_BUSFAULT:
                AM_BFW(SYSCTRL, SHCSR, BUSFAULTENA, 1);
            break;

            case AM_HAL_INTERRUPT_USAGEFAULT:
                AM_BFW(SYSCTRL, SHCSR, USAGEFAULTENA, 1);
            break;

            case AM_HAL_INTERRUPT_MPUFAULT:
                AM_BFW(SYSCTRL, SHCSR, MEMFAULTENA, 1);
            break;
        }
    }
}

//*****************************************************************************
//
//! @brief Disable an interrupt.
//!
//! @param ui32Interrupt The ISR number of the interrupt to be disabled.
//!
//! This function disables an interrupt signal to the NVIC based on the
//! provided ISR number.
//!
//! @return None
//
//*****************************************************************************
void
am_hal_interrupt_disable(uint32_t ui32Interrupt)
{
    //
    // Check to see what type of interrupt this is.
    //
    if ( ui32Interrupt > 15 )
    {
        //
        // If this ISR number corresponds to a "normal" peripheral interrupt,
        // disable it using the NVIC register.
        //
        AM_REG(NVIC, ICER0) = 0x1 << ((ui32Interrupt - 16) & 0x1F);
    }
    else
    {
        //
        // If this is an ARM internal interrupt number, route it to the
        // appropriate enable register.
        //
        switch(ui32Interrupt)
        {
            case AM_HAL_INTERRUPT_BUSFAULT:
                AM_BFW(SYSCTRL, SHCSR, BUSFAULTENA, 0);
            break;

            case AM_HAL_INTERRUPT_USAGEFAULT:
                AM_BFW(SYSCTRL, SHCSR, USAGEFAULTENA, 0);
            break;

            case AM_HAL_INTERRUPT_MPUFAULT:
                AM_BFW(SYSCTRL, SHCSR, MEMFAULTENA, 0);
            break;
        }
    }
}

//*****************************************************************************
//
//! @brief Set the priority of an interrupt vector.
//!
//! @param ui32Interrupt is the ISR number of the interrupt to change.
//! @param ui32Priority is the new ISR priority value.
//!
//! This function changes the priority value in the NVIC for the given
//! interrupt vector number.
//!
//! @return None
//
//*****************************************************************************
void
am_hal_interrupt_priority_set(uint32_t ui32Interrupt, uint32_t ui32Priority)
{
    volatile uint32_t *pui32PriorityReg;
    volatile uint32_t ui32OldPriority;
    uint32_t ui32Shift;

    //
    // Find the correct priority register.
    //
    pui32PriorityReg = (volatile uint32_t *) AM_REG_NVIC_IPR0_O;
    pui32PriorityReg += ((ui32Interrupt - 16) >> 2);

    //
    // Find the correct shift value.
    //
    ui32Shift = (((ui32Interrupt - 16) & 0x3) * 8);

    //
    // Mask out the old priority.
    //
    ui32OldPriority = *pui32PriorityReg;
    ui32OldPriority &= ~(0xFF << ui32Shift);

    //
    // OR in the new priority.
    //
    *pui32PriorityReg = ui32OldPriority | (ui32Priority << ui32Shift);
}

//*****************************************************************************
//
//! @brief Set a pending interrupt bit in the NVIC (Software Interrupt)
//!
//! @param ui32Interrupt is the ISR number of the interrupt to change.
//!
//! This function sets the specified bit in the Interrupt Set Pending (ISPR0)
//! register. For future MCUs there may be more than one ISPR.
//!
//! @return None
//
//*****************************************************************************
void am_hal_interrupt_pend_set(uint32_t ui32Interrupt)
{
    //
    // Check to see if the specified interrupt is valid for this MCU
    //
    if ( ui32Interrupt > AM_HAL_INTERRUPT_MAX )
    {
        return;
    }

    //
    // Check to see what type of interrupt this is.
    //
    if ( ui32Interrupt > 15 )
    {
        //
        // If this ISR number corresponds to a "normal" peripheral interrupt,
        // disable it using the NVIC register.
        //
        AM_REG(NVIC, ISPR0) = 0x1 << ((ui32Interrupt - 16) & 0x1F);
    }
}

//*****************************************************************************
//
//! @brief Clear a pending interrupt bit in the NVIC without servicing it
//!
//! @param ui32Interrupt is the ISR number of the interrupt to change.
//!
//! This function clears the specified bit in the Interrupt Clear Pending
//! (ICPR0) register. For future MCUs there may be more than one ICPR. This
//! function is useful immediately following a WFI before interrupts are
//! re-enabled.
//!
//! @return None
//
//*****************************************************************************
void am_hal_interrupt_pend_clear(uint32_t ui32Interrupt)
{
    //
    // Check to see if the specified interrupt is valid for this MCU
    //
    if ( ui32Interrupt > AM_HAL_INTERRUPT_MAX )
    {
        return;
    }

    //
    // Check to see what type of interrupt this is.
    //
    if ( ui32Interrupt > 15 )
    {
        //
        // If this ISR number corresponds to a "normal" peripheral interrupt,
        // disable it using the NVIC register.
        //
        AM_REG(NVIC, ICPR0) = 0x1 << ((ui32Interrupt - 16) & 0x1F);
    }
}

//*****************************************************************************
//
//! @brief Globally enable interrupt service routines
//!
//! This function allows interrupt signals from the NVIC to trigger ISR entry
//! in the CPU. This function must be called if interrupts are to be serviced
//! in software.
//!
//! @return 1 if interrupts were previously disabled, 0 otherwise.
//
//*****************************************************************************
#if defined(__GNUC_STDC_INLINE__)
uint32_t __attribute__((naked))
am_hal_interrupt_master_enable(void)
{
    __asm("    mrs     r0, PRIMASK");
    __asm("    cpsie i");
    __asm("    bx lr");
}
#elif defined(__ARMCC_VERSION)
__asm uint32_t
am_hal_interrupt_master_enable(void)
{
    mrs     r0, PRIMASK
    cpsie   i
    bx      lr
}
#elif defined(__IAR_SYSTEMS_ICC__)
#pragma diag_suppress = Pe940   // Suppress IAR compiler warning about missing
                                // return statement on a non-void function
__stackless uint32_t
am_hal_interrupt_master_enable(void)
{
    __asm("    mrs     r0, PRIMASK");
    __asm("    cpsie i");
    __asm("    bx lr");
}
#pragma diag_default = Pe940    // Restore IAR compiler warning
#endif

//*****************************************************************************
//
//! @brief Globally disable interrupt service routines
//!
//! This function prevents interrupt signals from the NVIC from triggering ISR
//! entry in the CPU. This will effectively stop incoming interrupt sources
//! from triggering their corresponding ISRs.
//!
//! @note Any external interrupt signal that occurs while the master interrupt
//! disable is active will still reach the "pending" state in the NVIC, but it
//! will not be allowed to reach the "active" state or trigger the
//! corresponding ISR. Instead, these interrupts are essentially "queued" until
//! the next time the master interrupt enable instruction is executed. At that
//! time, the interrupt handlers will be executed in order of decreasing
//! priority.
//!
//! @return 1 if interrupts were previously disabled, 0 otherwise.
//
//*****************************************************************************
#if defined(__GNUC_STDC_INLINE__)
uint32_t __attribute__((naked))
am_hal_interrupt_master_disable(void)
{
    __asm("    mrs     r0, PRIMASK");
    __asm("    cpsid i");
    __asm("    bx lr");
}
#elif defined(__ARMCC_VERSION)
__asm uint32_t
am_hal_interrupt_master_disable(void)
{
    mrs     r0, PRIMASK
    cpsid   i
    bx      lr
}
#elif defined(__IAR_SYSTEMS_ICC__)
#pragma diag_suppress = Pe940   // Suppress IAR compiler warning about missing
                                // return statement on a non-void function
__stackless uint32_t
am_hal_interrupt_master_disable(void)
{
    __asm("    mrs     r0, PRIMASK");
    __asm("    cpsid i");
    __asm("    bx lr");
}
#pragma diag_default = Pe940    // Restore IAR compiler warning
#endif

//*****************************************************************************
//
//! @brief Sets the master interrupt state based on the input.
//!
//! @param ui32InterruptState - Desired PRIMASK value.
//!
//! This function directly writes the PRIMASK register in the ARM core. A value
//! of 1 will disable interrupts, while a value of zero will enable them.
//!
//! This function may be used along with am_hal_interrupt_master_disable() to
//! implement a nesting critical section. To do this, call
//! am_hal_interrupt_master_disable() to start the critical section, and save
//! its return value. To complete the critical section, call
//! am_hal_interrupt_master_set() using the saved return value as \e
//! ui32InterruptState. This will safely restore PRIMASK to the value it
//! contained just before the start of the critical section.
//!
//! @return None.
//
//*****************************************************************************
#if defined(__GNUC_STDC_INLINE__)
void __attribute__((naked))
am_hal_interrupt_master_set(uint32_t ui32InterruptState)
{
    __asm("    msr     PRIMASK, r0");
    __asm("    bx lr");
}
#elif defined(__ARMCC_VERSION)
__asm void
am_hal_interrupt_master_set(uint32_t ui32InterruptState)
{
    msr     PRIMASK, r0
    bx      lr
}
#elif defined(__IAR_SYSTEMS_ICC__)
#pragma diag_suppress = Pe940   // Suppress IAR compiler warning about missing
                                // return statement on a non-void function
__stackless void
am_hal_interrupt_master_set(uint32_t ui32InterruptState)
{
    __asm("    msr     PRIMASK, r0");
    __asm("    bx lr");
}
#pragma diag_default = Pe940    // Restore IAR compiler warning
#endif

//*****************************************************************************
//
// End Doxygen group.
//! @}
//
//*****************************************************************************
