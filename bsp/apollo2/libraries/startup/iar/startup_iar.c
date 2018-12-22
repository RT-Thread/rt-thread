//*****************************************************************************
//
//! @file startup_iar.c
//!
//! @brief Definitions for interrupt handlers, the vector table, and the stack.
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
// This is part of revision 1.2.9 of the AmbiqSuite Development Package.
//
//*****************************************************************************

#include <stdint.h>

//*****************************************************************************
//
// Enable the IAR extensions for this source file.
//
//*****************************************************************************
#pragma language = extended

//*****************************************************************************
//
// Weak function links.
//
//*****************************************************************************
#pragma weak am_mpufault_isr        = am_fault_isr
#pragma weak am_busfault_isr        = am_fault_isr
#pragma weak am_usagefault_isr      = am_fault_isr
#pragma weak am_svcall_isr          = am_default_isr
#pragma weak am_debugmon_isr        = am_default_isr
#pragma weak am_pendsv_isr          = am_default_isr
#pragma weak am_systick_isr         = am_default_isr
#pragma weak am_brownout_isr        = am_default_isr
#pragma weak am_watchdog_isr        = am_default_isr
#pragma weak am_clkgen_isr          = am_default_isr
#pragma weak am_vcomp_isr           = am_default_isr
#pragma weak am_ioslave_ios_isr     = am_default_isr
#pragma weak am_ioslave_acc_isr     = am_default_isr
#pragma weak am_iomaster0_isr       = am_default_isr
#pragma weak am_iomaster1_isr       = am_default_isr
#pragma weak am_iomaster2_isr       = am_default_isr
#pragma weak am_iomaster3_isr       = am_default_isr
#pragma weak am_iomaster4_isr       = am_default_isr
#pragma weak am_iomaster5_isr       = am_default_isr
#pragma weak am_gpio_isr            = am_default_isr
#pragma weak am_ctimer_isr          = am_default_isr
#pragma weak am_uart_isr            = am_default_isr
#pragma weak am_uart1_isr           = am_default_isr
#pragma weak am_adc_isr             = am_default_isr
#pragma weak am_pdm_isr             = am_default_isr
#pragma weak am_stimer_isr          = am_default_isr
#pragma weak am_stimer_cmpr0_isr    = am_default_isr
#pragma weak am_stimer_cmpr1_isr    = am_default_isr
#pragma weak am_stimer_cmpr2_isr    = am_default_isr
#pragma weak am_stimer_cmpr3_isr    = am_default_isr
#pragma weak am_stimer_cmpr4_isr    = am_default_isr
#pragma weak am_stimer_cmpr5_isr    = am_default_isr
#pragma weak am_stimer_cmpr6_isr    = am_default_isr
#pragma weak am_stimer_cmpr7_isr    = am_default_isr
#pragma weak am_flash_isr           = am_default_isr
#pragma weak am_software0_isr       = am_default_isr
#pragma weak am_software1_isr       = am_default_isr
#pragma weak am_software2_isr       = am_default_isr
#pragma weak am_software3_isr       = am_default_isr


//*****************************************************************************
//
// Forward declaration of the default fault handlers.
//
//*****************************************************************************
extern __stackless void am_reset_isr(void);
extern __weak void am_nmi_isr(void);
extern __weak void am_fault_isr(void);
extern void am_mpufault_isr(void);
extern void am_busfault_isr(void);
extern void am_usagefault_isr(void);
extern void am_svcall_isr(void);
extern void am_debugmon_isr(void);
extern void am_pendsv_isr(void);
extern void am_systick_isr(void);
extern void am_brownout_isr(void);
extern void am_watchdog_isr(void);
extern void am_clkgen_isr(void);
extern void am_vcomp_isr(void);
extern void am_ioslave_ios_isr(void);
extern void am_ioslave_acc_isr(void);
extern void am_iomaster0_isr(void);
extern void am_iomaster1_isr(void);
extern void am_iomaster2_isr(void);
extern void am_iomaster3_isr(void);
extern void am_iomaster4_isr(void);
extern void am_iomaster5_isr(void);
extern void am_gpio_isr(void);
extern void am_ctimer_isr(void);
extern void am_uart_isr(void);
extern void am_uart1_isr(void);
extern void am_adc_isr(void);
extern void am_pdm_isr(void);
extern void am_stimer_isr(void);
extern void am_stimer_cmpr0_isr(void);
extern void am_stimer_cmpr1_isr(void);
extern void am_stimer_cmpr2_isr(void);
extern void am_stimer_cmpr3_isr(void);
extern void am_stimer_cmpr4_isr(void);
extern void am_stimer_cmpr5_isr(void);
extern void am_stimer_cmpr6_isr(void);
extern void am_stimer_cmpr7_isr(void);
extern void am_flash_isr(void);
extern void am_software0_isr(void);
extern void am_software1_isr(void);
extern void am_software2_isr(void);
extern void am_software3_isr(void);

extern void am_default_isr(void);

//*****************************************************************************
//
// The entry point for the application startup code.
//
//*****************************************************************************
extern void __iar_program_start(void);

//*****************************************************************************
//
// Reserve space for the system stack.
//
//*****************************************************************************
static uint32_t pui32Stack[1024] @ ".noinit";

//*****************************************************************************
//
// A union that describes the entries of the vector table.  The union is needed
// since the first entry is the stack pointer and the remainder are function
// pointers.
//
//*****************************************************************************
typedef union
{
    void (*pfnHandler)(void);
    uint32_t ui32Ptr;
}
uVectorEntry;

//*****************************************************************************
//
// The vector table.  Note that the proper constructs must be placed on this to
// ensure that it ends up at physical address 0x0000.0000.
//
// Note: Aliasing and weakly exporting am_mpufault_isr, am_busfault_isr, and
// am_usagefault_isr does not work if am_fault_isr is defined externally.
// Therefore, we'll explicitly use am_fault_isr in the table for those vectors.
//
//*****************************************************************************
__root const uVectorEntry __vector_table[] @ ".intvec" =
{
    { .ui32Ptr = (uint32_t)pui32Stack + sizeof(pui32Stack) },
                                                // The initial stack pointer
    am_reset_isr,                               // The reset handler
    am_nmi_isr,                                 // The NMI handler
    am_fault_isr,                               // The hard fault handler
    am_fault_isr,                               // The MPU fault handler
    am_fault_isr,                               // The bus fault handler
    am_fault_isr,                               // The usage fault handler
    0,                                          // Reserved
    0,                                          // Reserved
    0,                                          // Reserved
    0,                                          // Reserved
    am_svcall_isr,                              // SVCall handle
    am_debugmon_isr,                            // Debug monitor handler
    0,                                          // Reserved
    am_pendsv_isr,                              // The PendSV handler
    am_systick_isr,                             // The SysTick handler

    //
    // Peripheral Interrupts
    //
    am_brownout_isr,                            //  0: Brownout
    am_watchdog_isr,                            //  1: Watchdog
    am_clkgen_isr,                              //  2: CLKGEN
    am_vcomp_isr,                               //  3: Voltage Comparator
    am_ioslave_ios_isr,                         //  4: I/O Slave general
    am_ioslave_acc_isr,                         //  5: I/O Slave access
    am_iomaster0_isr,                           //  6: I/O Master 0
    am_iomaster1_isr,                           //  7: I/O Master 1
    am_iomaster2_isr,                           //  8: I/O Master 2
    am_iomaster3_isr,                           //  9: I/O Master 3
    am_iomaster4_isr,                           // 10: I/O Master 4
    am_iomaster5_isr,                           // 11: I/O Master 5
    am_gpio_isr,                                // 12: GPIO
    am_ctimer_isr,                              // 13: CTIMER
    am_uart_isr,                                // 14: UART0
    am_uart1_isr,                               // 15: UART1
    am_adc_isr,                                 // 16: ADC
    am_pdm_isr,                                 // 17: PDM
    am_stimer_isr,                              // 18: STIMER
    am_stimer_cmpr0_isr,                        // 19: STIMER COMPARE0
    am_stimer_cmpr1_isr,                        // 20: STIMER COMPARE1
    am_stimer_cmpr2_isr,                        // 21: STIMER COMPARE2
    am_stimer_cmpr3_isr,                        // 22: STIMER COMPARE3
    am_stimer_cmpr4_isr,                        // 23: STIMER COMPARE4
    am_stimer_cmpr5_isr,                        // 24: STIMER COMPARE5
    am_stimer_cmpr6_isr,                        // 25: STIMER COMPARE6
    am_stimer_cmpr7_isr,                        // 26: STIMER COMPARE7
    am_flash_isr,                               // 27: FLASH
    am_software0_isr,                           // 28: SOFTWARE0
    am_software1_isr,                           // 29: SOFTWARE1
    am_software2_isr,                           // 30: SOFTWARE2
    am_software3_isr                            // 31: SOFTWARE3
};

//*****************************************************************************
//
// This is the code that gets called when the processor first starts execution
// following a reset event.  Only the absolutely necessary set is performed,
// after which the application supplied entry() routine is called.
//
//*****************************************************************************
void
am_reset_isr(void)
{
    //
    // Call the application's entry point.
    //
    __iar_program_start();
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a NMI.  This
// simply enters an infinite loop, preserving the system state for examination
// by a debugger.
//
//*****************************************************************************
__weak void
am_nmi_isr(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives a fault
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
__weak void
am_fault_isr(void)
{
    //
    // Enter an infinite loop.
    //
    while(1)
    {
    }
}

//*****************************************************************************
//
// This is the code that gets called when the processor receives an unexpected
// interrupt.  This simply enters an infinite loop, preserving the system state
// for examination by a debugger.
//
//*****************************************************************************
static void
am_default_isr(void)
{
    //
    // Go into an infinite loop.
    //
    while(1)
    {
    }
}
