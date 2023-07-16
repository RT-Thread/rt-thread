//*****************************************************************************
//
// bl_startup_gcc.S - Startup code for GNU.
//
// Copyright (c) 2007-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
//
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
//
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
//
//*****************************************************************************

//*****************************************************************************
//
// Include the assember definitions used to make this code compiler
// independent.
//
//*****************************************************************************
#include "bl_config.h"

//*****************************************************************************
//
// Put the assembler into the correct configuration.
//
//*****************************************************************************
    .syntax unified
    .thumb

//*****************************************************************************
//
// The stack gets placed into the zero-init section.
//
//*****************************************************************************
    .bss

//*****************************************************************************
//
// Allocate storage for the stack.
//
//*****************************************************************************
g_pulStack:
    .space  STACK_SIZE * 4

//*****************************************************************************
//
// This portion of the file goes into the text section.
//
//*****************************************************************************
    .section .isr_vector

//*****************************************************************************
//
// The minimal vector table for a Cortex-M3 processor.
//
//*****************************************************************************
Vectors:
    .word   g_pulStack + (STACK_SIZE * 4)   // Offset 00: Initial stack pointer
    .word   ResetISR - 0x20000000           // Offset 04: Reset handler
    .word   NmiSR - 0x20000000              // Offset 08: NMI handler
    .word   FaultISR - 0x20000000           // Offset 0C: Hard fault handler
    .word   IntDefaultHandler               // Offset 10: MPU fault handler
    .word   IntDefaultHandler               // Offset 14: Bus fault handler
    .word   IntDefaultHandler               // Offset 18: Usage fault handler
    .word   0                               // Offset 1C: Reserved
    .word   0                               // Offset 20: Reserved
    .word   0                               // Offset 24: Reserved
    .word   0                               // Offset 28: Reserved
    .word   UpdateHandler - 0x20000000      // Offset 2C: SVCall handler
    .word   IntDefaultHandler               // Offset 30: Debug monitor handler
    .word   0                               // Offset 34: Reserved
    .word   IntDefaultHandler               // Offset 38: PendSV handler
#if defined(ENET_ENABLE_UPDATE)
    .extern SysTickIntHandler
    .word   SysTickIntHandler               // Offset 3C: SysTick handler
#else
    .word   IntDefaultHandler               // Offset 3C: SysTick handler
#endif
#if defined(UART_ENABLE_UPDATE) && defined(UART_AUTOBAUD)
#if (UART_AUTOBAUD== 0)
    .extern GPIOIntHandler
    .word   GPIOIntHandler                 // Offset 040: GPIO port A handler
#else
    .word   IntDefaultHandler              // Offset 040: GPIO port A handler
#endif
#else
    .word   IntDefaultHandler              // Offset 040: GPIO port A handler
#endif
#if defined(UART_ENABLE_UPDATE) && defined(UART_AUTOBAUD)
#if (UART_AUTOBAUD== 1)
    .extern GPIOIntHandler
    .word   GPIOIntHandler                 // Offset 044: GPIO port B handler
#else
    .word   IntDefaultHandler              // Offset 044: GPIO port B handler
#endif
#else
    .word   IntDefaultHandler              // Offset 044: GPIO port B handler
#endif
#if defined(UART_ENABLE_UPDATE) && defined(UART_AUTOBAUD)
#if (UART_AUTOBAUD== 2)
    .extern GPIOIntHandler
    .word   GPIOIntHandler                 // Offset 048: GPIO port C handler
#else
    .word   IntDefaultHandler              // Offset 048: GPIO port C handler
#endif
#else
    .word   IntDefaultHandler              // Offset 048: GPIO port C handler
#endif
#if defined(UART_ENABLE_UPDATE) && defined(UART_AUTOBAUD)
#if (UART_AUTOBAUD== 3)
    .extern GPIOIntHandler
    .word   GPIOIntHandler                 // Offset 04C: GPIO port D handler
#else
    .word   IntDefaultHandler              // Offset 04C: GPIO port D handler
#endif
#else
    .word   IntDefaultHandler              // Offset 04C: GPIO port D handler
#endif
    .word   IntDefaultHandler              // Offset 050: GPIO Port E
    .word   IntDefaultHandler              // Offset 054: UART0 Rx and Tx
    .word   IntDefaultHandler              // Offset 058: UART1 Rx and Tx
    .word   IntDefaultHandler              // Offset 05C: SSI0 Rx and Tx
    .word   IntDefaultHandler              // Offset 060: I2C0 Master and Slave
    .word   IntDefaultHandler              // Offset 064: PWM Fault
    .word   IntDefaultHandler              // Offset 068: PWM Generator 0
    .word   IntDefaultHandler              // Offset 06C: PWM Generator 1
    .word   IntDefaultHandler              // Offset 070: PWM Generator 2
    .word   IntDefaultHandler              // Offset 074: Quadrature Encoder 0
    .word   IntDefaultHandler              // Offset 078: ADC Sequence 0
    .word   IntDefaultHandler              // Offset 07C: ADC Sequence 1
    .word   IntDefaultHandler              // Offset 080: ADC Sequence 2
    .word   IntDefaultHandler              // Offset 084: ADC Sequence 3
    .word   IntDefaultHandler              // Offset 088: Watchdog timer
    .word   IntDefaultHandler              // Offset 08C: Timer 0 subtimer A
    .word   IntDefaultHandler              // Offset 090: Timer 0 subtimer B
    .word   IntDefaultHandler              // Offset 094: Timer 1 subtimer A
    .word   IntDefaultHandler              // Offset 098: Timer 1 subtimer B
    .word   IntDefaultHandler              // Offset 09C: Timer 2 subtimer A
    .word   IntDefaultHandler              // Offset 0A0: Timer 2 subtimer B
    .word   IntDefaultHandler              // Offset 0A4: Analog Comparator 0
    .word   IntDefaultHandler              // Offset 0A8: Analog Comparator 1
    .word   IntDefaultHandler              // Offset 0AC: Analog Comparator 2
    .word   IntDefaultHandler              // Offset 0B0: System Control
    .word   IntDefaultHandler              // Offset 0B4: FLASH Control
    .word   IntDefaultHandler              // Offset 0B8: GPIO Port F
    .word   IntDefaultHandler              // Offset 0BC: GPIO Port G
#if defined(UART_ENABLE_UPDATE) && defined(UART_AUTOBAUD)
#if (UART_AUTOBAUD== 7)
    .extern GPIOIntHandler
    .word   GPIOIntHandler                 // Offset 0C0: GPIO port H handler
#else
    .word   IntDefaultHandler              // Offset 0C0: GPIO port H handler
#endif
#else
    .word   IntDefaultHandler              // Offset 0C0: GPIO port H handler
#endif
    .word   IntDefaultHandler              // Offset 0C4: UART2 Rx and Tx
    .word   IntDefaultHandler              // Offset 0C8: SSI1 Rx and Tx
    .word   IntDefaultHandler              // Offset 0CC: Timer 3 subtimer A
    .word   IntDefaultHandler              // Offset 0D0: Timer 3 subtimer B
    .word   IntDefaultHandler              // Offset 0D4: I2C1 Master and Slave
    .word   IntDefaultHandler              // Offset 0D8: CAN0
    .word   IntDefaultHandler              // Offset 0DC: CAN1
    .word   IntDefaultHandler              // Offset 0E0: Ethernet
    .word   IntDefaultHandler              // Offset 0E4: Hibernation module
#if defined(USB_ENABLE_UPDATE)
    .extern USB0DeviceIntHandler
    .word   USB0DeviceIntHandler           // Offset 0E8: USB 0 Controller
#else
    .word   IntDefaultHandler              // Offset 0E8: USB 0 Controller
#endif
    .word   IntDefaultHandler              // Offset 0EC: PWM Generator 3
    .word   IntDefaultHandler              // Offset 0F0: uDMA 0 Software
    .word   IntDefaultHandler              // Offset 0F4: uDMA 0 Error
    .word   IntDefaultHandler              // Offset 0F8: ADC 1 Sequence 0
    .word   IntDefaultHandler              // Offset 0FC: ADC 1 Sequence 1
    .word   IntDefaultHandler              // Offset 100: ADC 1 Sequence 2
    .word   IntDefaultHandler              // Offset 104: ADC 1 Sequence 3
    .word   IntDefaultHandler              // Offset 108: EPI 0
#if defined(UART_ENABLE_UPDATE) && defined(UART_AUTOBAUD)
#if (UART_AUTOBAUD== 8)
    .extern GPIOIntHandler
    .word   GPIOIntHandler                 // Offset 10C: GPIO port J handler
#else
    .word   IntDefaultHandler              // Offset 10C: GPIO port J handler
#endif
#else
    .word   IntDefaultHandler              // Offset 10C: GPIO port J handler
#endif
#if defined(UART_ENABLE_UPDATE) && defined(UART_AUTOBAUD)
#if (UART_AUTOBAUD== 9)
    .extern GPIOIntHandler
    .word   GPIOIntHandler                 // Offset 110: GPIO port K handler
#else
    .word   IntDefaultHandler              // Offset 110: GPIO port K handler
#endif
#else
    .word   IntDefaultHandler              // Offset 110: GPIO port K handler
#endif
    .word   IntDefaultHandler              // Offset 114: GPIO Port L
    .word   IntDefaultHandler              // Offset 118: SSI2 Rx and Tx
    .word   IntDefaultHandler              // Offset 11C: SSI3 Rx and Tx
    .word   IntDefaultHandler              // Offset 120: UART3 Rx and Tx
    .word   IntDefaultHandler              // Offset 124: UART4 Rx and Tx
    .word   IntDefaultHandler              // Offset 128: UART5 Rx and Tx
    .word   IntDefaultHandler              // Offset 12C: UART6 Rx and Tx
    .word   IntDefaultHandler              // Offset 130: UART7 Rx and Tx
    .word   IntDefaultHandler              // Offset 134: I2C2 Master and Slave
    .word   IntDefaultHandler              // Offset 138: I2C3 Master and Slave
    .word   IntDefaultHandler              // Offset 13C: Timer 4 subtimer A
    .word   IntDefaultHandler              // Offset 140: Timer 4 subtimer B
    .word   IntDefaultHandler              // Offset 144: Timer 5 subtimer A
    .word   IntDefaultHandler              // Offset 148: Timer 5 subtimer B
    .word   IntDefaultHandler              // Offset 14C: FPU Exception
    .word   IntDefaultHandler              // Offset 150: Reserved
    .word   IntDefaultHandler              // Offset 154: Reserved
    .word   IntDefaultHandler              // Offset 158: I2C4 Master and Slave
    .word   IntDefaultHandler              // Offset 15C: I2C5 Master and Slave
    .word   IntDefaultHandler              // Offset 160: GPIO Port M
    .word   IntDefaultHandler              // Offset 164: GPIO Port N
    .word   IntDefaultHandler              // Offset 168: Reserved
    .word   IntDefaultHandler              // Offset 16C: Tamper
#if defined(UART_ENABLE_UPDATE) && defined(UART_AUTOBAUD)
#if (UART_AUTOBAUD== 13)
    .extern GPIOIntHandler
    .word   GPIOIntHandler                 // Offset 170: GPIO port P handler
#else
    .word   IntDefaultHandler              // Offset 170: GPIO port P handler
#endif
#else
    .word   IntDefaultHandler              // Offset 170: GPIO port P handler
#endif
    .word   IntDefaultHandler              // Offset 174: GPIO Port P1
    .word   IntDefaultHandler              // Offset 178: GPIO Port P2
    .word   IntDefaultHandler              // Offset 17C: GPIO Port P3
    .word   IntDefaultHandler              // Offset 180: GPIO Port P4
    .word   IntDefaultHandler              // Offset 184: GPIO Port P5
    .word   IntDefaultHandler              // Offset 188: GPIO Port P6
    .word   IntDefaultHandler              // Offset 18C: GPIO Port P7
#if defined(UART_ENABLE_UPDATE) && defined(UART_AUTOBAUD)
#if (UART_AUTOBAUD== 14)
    .extern GPIOIntHandler
    .word   GPIOIntHandler                 // Offset 190: GPIO port Q handler
#else
    .word   IntDefaultHandler              // Offset 190: GPIO port Q handler
#endif
#else
    .word   IntDefaultHandler              // Offset 190: GPIO port Q handler
#endif
    .word   IntDefaultHandler              // Offset 194: GPIO Port Q1
    .word   IntDefaultHandler              // Offset 198: GPIO Port Q2
    .word   IntDefaultHandler              // Offset 19C: GPIO Port Q3
    .word   IntDefaultHandler              // Offset 1A0: GPIO Port Q4
    .word   IntDefaultHandler              // Offset 1A4: GPIO Port Q5
    .word   IntDefaultHandler              // Offset 1A8: GPIO Port Q6
    .word   IntDefaultHandler              // Offset 1AC: GPIO Port Q7
#if defined(UART_ENABLE_UPDATE) && defined(UART_AUTOBAUD)
#if (UART_AUTOBAUD== 15)
    .extern GPIOIntHandler
    .word   GPIOIntHandler                 // Offset 1B0: GPIO port R handler
#else
    .word   IntDefaultHandler              // Offset 1B0: GPIO port R handler
#endif
#else
    .word   IntDefaultHandler              // Offset 1B0: GPIO port R handler
#endif
    .word   IntDefaultHandler              // Offset 1B4: GPIO Port S
    .word   IntDefaultHandler              // Offset 1B8: SHA/MD5
    .word   IntDefaultHandler              // Offset 1BC: AES

//*****************************************************************************
//
// This portion of the file goes into the text section.
//
//*****************************************************************************
    .text

//*****************************************************************************
//
// Initialize the processor by copying the boot loader from flash to SRAM, zero
// filling the .bss section, and moving the vector table to the beginning of
// SRAM.  The return address is modified to point to the SRAM copy of the boot
// loader instead of the flash copy, resulting in a branch to the copy now in
// SRAM.
//
//*****************************************************************************
    .thumb_func
ProcessorInit:
    //
    // Copy the code image from flash to SRAM.
    //
    movs    r0, #0x0000
    movs    r1, #0x0000
    movt    r1, #0x2000
    .extern _bss
    ldr     r2, =_bss
copy_loop:
        ldr     r3, [r0], #4
        str     r3, [r1], #4
        cmp     r1, r2
        blt     copy_loop

    //
    // Zero fill the .bss section.
    //
    movs    r0, #0x0000
    .extern _ebss
    ldr     r2, =_ebss
zero_loop:
        str     r0, [r1], #4
        cmp     r1, r2
        blt     zero_loop

    //
    // Set the vector table pointer to the beginning of SRAM.
    //
    movw    r0, #(0xE000ED08 & 0xffff)
    movt    r0, #(0xE000ED08 >> 16)
    movs    r1, #0x0000
    movt    r1, #0x2000
    str     r1, [r0]

    //
    // Set the return address to the code just copied into SRAM.
    //
    orr     lr, lr, #0x20000000

    //
    // Return to the caller.
    //
    bx      lr

//*****************************************************************************
//
// The reset handler, which gets called when the processor starts.
//
//*****************************************************************************
    .globl  ResetISR
    .thumb_func
ResetISR:
    //
    // Enable the floating-point unit.  This must be done here in case any
    // later C functions use floating point.  Note that some toolchains will
    // use the FPU registers for general workspace even if no explicit floating
    // point data types are in use.
    //
    movw    r0, #0xED88
    movt    r0, #0xE000
    ldr     r1, [r0]
    orr     r1, r1, #0x00F00000
    str     r1, [r0]

    //
    // Initialize the processor.
    //
    bl      ProcessorInit

    //
    // Call the user-supplied low level hardware initialization function
    // if provided.
    //
#ifdef BL_HW_INIT_FN_HOOK
    .extern BL_HW_INIT_FN_HOOK
    bl      BL_HW_INIT_FN_HOOK
#endif

    //
    // See if an update should be performed.
    //
    .extern CheckForceUpdate
    bl      CheckForceUpdate
    cbz     r0, CallApplication

    //
    // Configure the microcontroller.
    //
    .thumb_func
EnterBootLoader:
#ifdef ENET_ENABLE_UPDATE
    .extern ConfigureEnet
    bl      ConfigureEnet
#elif defined(CAN_ENABLE_UPDATE)
    .extern ConfigureCAN
    bl      ConfigureCAN
#elif defined(USB_ENABLE_UPDATE)
    .extern ConfigureUSB
    bl      ConfigureUSB
#else
    .extern ConfigureDevice
    bl      ConfigureDevice
#endif

    //
    // Call the user-supplied initialization function if provided.
    //
#ifdef BL_INIT_FN_HOOK
    .extern BL_INIT_FN_HOOK
    bl      BL_INIT_FN_HOOK
#endif

    //
    // Branch to the update handler.
    //
#ifdef ENET_ENABLE_UPDATE
    .extern UpdateBOOTP
    b       UpdateBOOTP
#elif defined(CAN_ENABLE_UPDATE)
    .extern UpdaterCAN
    b       UpdaterCAN
#elif defined(USB_ENABLE_UPDATE)
    .extern UpdaterUSB
    b       UpdaterUSB
#else
    .extern Updater
    b       Updater
#endif

    //
    // This is a second symbol to allow starting the application from the boot
    // loader the linker may not like the perceived jump.
    //
    .globl  StartApplication
    .thumb_func
StartApplication:
    //
    // Call the application via the reset handler in its vector table.  Load
    // the address of the application vector table.
    //
    .thumb_func
CallApplication:
    //
    // Copy the application's vector table to the target address if necessary.
    // Note that incorrect boot loader configuration could cause this to
    // corrupt the code!  Setting VTABLE_START_ADDRESS to 0x20000000 (the start
    // of SRAM) is safe since this will use the same memory that the boot
    // loader already uses for its vector table.  Great care will have to be
    // taken if other addresses are to be used.
    //
#if (APP_START_ADDRESS != VTABLE_START_ADDRESS)
    movw    r0, #(VTABLE_START_ADDRESS & 0xffff)
#if (VTABLE_START_ADDRESS > 0xffff)
    movt    r0, #(VTABLE_START_ADDRESS >> 16)
#endif
    movw    r1, #(APP_START_ADDRESS & 0xffff)
#if (APP_START_ADDRESS > 0xffff)
    movt    r1, #(APP_START_ADDRESS >> 16)
#endif

    //
    // Calculate the end address of the vector table assuming that it has the
    // maximum possible number of vectors.  We don't know how many the app has
    // populated so this is the safest approach though it may copy some non
    // vector data if the app table is smaller than the maximum.
    //
    movw    r2, #(70 * 4)
    adds    r2, r2, r0
VectorCopyLoop:
        ldr     r3, [r1], #4
        str     r3, [r0], #4
        cmp     r0, r2
        blt     VectorCopyLoop
#endif

    //
    // Set the application's vector table start address.  Typically this is the
    // application start address but in some cases an application may relocate
    // this so we can't assume that these two addresses are equal.
    //
    movw    r0, #(VTABLE_START_ADDRESS & 0xffff)
#if (VTABLE_START_ADDRESS > 0xffff)
    movt    r0, #(VTABLE_START_ADDRESS >> 16)
#endif
    movw    r1, #(0xE000ED08 & 0xffff)
    movt    r1, #(0xE000ED08 >> 16)
    str     r0, [r1]

    //
    // Load the stack pointer from the application's vector table.
    //
#if (APP_START_ADDRESS != VTABLE_START_ADDRESS)
    movw    r0, #(APP_START_ADDRESS & 0xffff)
#if (APP_START_ADDRESS > 0xffff)
    movt    r0, #(APP_START_ADDRESS >> 16)
#endif
#endif
    ldr     sp, [r0]

    //
    // Load the initial PC from the application's vector table and branch to
    // the application's entry point.
    //
    ldr     r0, [r0, #4]
    bx      r0

//*****************************************************************************
//
// The update handler, which gets called when the application would like to
// start an update.
//
//*****************************************************************************
    .thumb_func
UpdateHandler:
    //
    // Initialize the processor.
    //
    bl      ProcessorInit

    //
    // Load the stack pointer from the vector table.
    //
    movs    r0, #0x0000
    ldr     sp, [r0]

    //
    // Call the user-supplied low level hardware initialization function
    // if provided.
    //
#ifdef BL_HW_INIT_FN_HOOK
    bl      BL_HW_INIT_FN_HOOK
#endif

    //
    // Call the user-supplied re-initialization function if provided.
    //
#ifdef BL_REINIT_FN_HOOK
    .extern BL_REINIT_FN_HOOK
    bl      BL_REINIT_FN_HOOK
#endif

    //
    // Branch to the update handler.
    //
#ifdef ENET_ENABLE_UPDATE
    b       UpdateBOOTP
#elif defined(CAN_ENABLE_UPDATE)
    .extern AppUpdaterCAN
    b       AppUpdaterCAN
#elif defined(USB_ENABLE_UPDATE)
    .extern AppUpdaterUSB
    b       AppUpdaterUSB
#else
    b       Updater
#endif

//*****************************************************************************
//
// The NMI handler.
//
//*****************************************************************************
    .thumb_func
NmiSR:
#ifdef ENABLE_MOSCFAIL_HANDLER
    //
    // Grab the fault frame from the stack (the stack will be cleared by the
    // processor initialization that follows).
    //
    ldm     sp, {r4-r11}
    mov     r12, lr

    //
    // Initialize the processor.
    //
    bl      ProcessorInit

    //
    // Restore the stack frame.
    //
    mov     lr, r12
    stm     sp, {r4-r11}

    //
    // Save the link register.
    //
    mov     r9, lr

    //
    // Call the user-supplied low level hardware initialization function
    // if provided.
    //
#ifdef BL_HW_INIT_FN_HOOK
    bl      BL_HW_INIT_FN_HOOK
#endif

    //
    // See if an update should be performed.
    //
    bl      CheckForceUpdate
    cbz     r0, EnterApplication

        //
        // Clear the MOSCFAIL bit in RESC.
        //
        movw    r0, #(0x400FE05C & 0xffff)
        movt    r0, #(0x400FE05C >> 16)
        ldr     r1, [r0]
        bic     r1, r1, #0x00010000
        str     r1, [r0]

        //
        // Fix up the PC on the stack so that the boot pin check is bypassed
        // (since it has already been performed).
        //
        ldr     r0, =EnterBootLoader
        bic     r0, #0x00000001
        str     r0, [sp, #0x18]

        //
        // Return from the NMI handler.  This will then start execution of the
        // boot loader.
        //
        bx      r9

    //
    // Restore the link register.
    //
    .thumb_func
EnterApplication:
    mov     lr, r9

    //
    // Copy the application's vector table to the target address if necessary.
    // Note that incorrect boot loader configuration could cause this to
    // corrupt the code!  Setting VTABLE_START_ADDRESS to 0x20000000 (the start
    // of SRAM) is safe since this will use the same memory that the boot
    // loader already uses for its vector table.  Great care will have to be
    // taken if other addresses are to be used.
    //
#if (APP_START_ADDRESS != VTABLE_START_ADDRESS)
    movw    r0, #(VTABLE_START_ADDRESS & 0xffff)
#if (VTABLE_START_ADDRESS > 0xffff)
    movt    r0, #(VTABLE_START_ADDRESS >> 16)
#endif
    movw    r1, #(APP_START_ADDRESS & 0xffff)
#if (APP_START_ADDRESS > 0xffff)
    movt    r1, #(APP_START_ADDRESS >> 16)
#endif

    //
    // Calculate the end address of the vector table assuming that it has the
    // maximum possible number of vectors.  We don't know how many the app has
    // populated so this is the safest approach though it may copy some non
    // vector data if the app table is smaller than the maximum.
    //
    movw    r2, #(70 * 4)
    adds    r2, r2, r0
VectorCopyLoop2:
        ldr     r3, [r1], #4
        str     r3, [r0], #4
        cmp     r0, r2
        blt     VectorCopyLoop2
#endif

    //
    // Set the application's vector table start address.  Typically this is the
    // application start address but in some cases an application may relocate
    // this so we can't assume that these two addresses are equal.
    //
    movw    r0, #(VTABLE_START_ADDRESS & 0xffff)
#if (VTABLE_START_ADDRESS > 0xffff)
    movt    r0, #(VTABLE_START_ADDRESS >> 16)
#endif
    movw    r1, #(0xE000ED08 & 0xffff)
    movt    r1, #(0xE000ED08 >> 16)
    str     r0, [r1]

    //
    // Remove the NMI stack frame from the boot loader's stack.
    //
    ldmia   sp, {r4-r11}

    //
    // Get the application's stack pointer.
    //
#if (APP_START_ADDRESS != VTABLE_START_ADDRESS)
    movw    r0, #(APP_START_ADDRESS & 0xffff)
#if (APP_START_ADDRESS > 0xffff)
    movt    r0, #(APP_START_ADDRESS >> 16)
#endif
#endif
    ldr     sp, [r0, #0x00]

    //
    // Fix up the NMI stack frame's return address to be the reset handler of
    // the application.
    //
    ldr     r10, [r0, #0x04]
    bic     r10, #0x00000001

    //
    // Store the NMI stack frame onto the application's stack.
    //
    stmdb   sp!, {r4-r11}

    //
    // Branch to the application's NMI handler.
    //
    ldr     r0, [r0, #0x08]
    bx      r0
#else
    //
    // Loop forever since there is nothing that we can do about a NMI.
    //
    b       .
#endif

//*****************************************************************************
//
// The hard fault handler.
//
//*****************************************************************************
    .thumb_func
FaultISR:
    //
    // Loop forever since there is nothing that we can do about a hard fault.
    //
    b       .

//*****************************************************************************
//
// The default interrupt handler.
//
//*****************************************************************************
    .thumb_func
IntDefaultHandler:
    //
    // Loop forever since there is nothing that we can do about an unexpected
    // interrupt.
    //
    b       .

//*****************************************************************************
//
// Provides a small delay.  The loop below takes 3 cycles/loop.
//
//*****************************************************************************
    .globl  Delay
    .thumb_func
Delay:
    subs    r0, #1
    bne     Delay
    bx      lr

//*****************************************************************************
//
// This is the end of the file.
//
//*****************************************************************************
    .end
