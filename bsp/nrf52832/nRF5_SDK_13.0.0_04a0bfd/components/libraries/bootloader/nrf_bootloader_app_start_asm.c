/**
 * Copyright (c) 2016 - 2017, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
#include <stdint.h>
#include "compiler_abstraction.h"

#if defined ( __CC_ARM )
__ASM void nrf_bootloader_app_start_impl(uint32_t start_addr)
{
    LDR   R5, [R0]              ; Get App initial MSP for bootloader.
    MSR   MSP, R5               ; Set the main stack pointer to the applications MSP.
    LDR   R0, [R0, #0x04]       ; Load Reset handler into R0. This will be first argument to branch instruction (BX).

    MOVS  R4, #0xFF             ; Load ones to R4.
    SXTB  R4, R4                ; Sign extend R4 to obtain 0xFFFFFFFF instead of 0xFF.
    MRS   R5, IPSR              ; Load IPSR to R5 to check for handler or thread mode.
    CMP   R5, #0x00             ; Compare, if 0 then we are in thread mode and can continue to reset handler of bootloader.
    BNE   isr_abort             ; If not zero we need to exit current ISR and jump to reset handler of bootloader.

    MRS   R1, CONTROL           ; Get CONTROL register value
    MOVS  R2, #0x02             ; load 2 to r2
    BICS  R1, R2                ; clear value of CONTROL->SPSEL - > make sure MSP will be used
    MSR   CONTROL, R1           ; set the stack pointer to MSP

    MOV   LR, R4                ; Clear the link register and set to ones to ensure no return, R4 = 0xFFFFFFFF.
    BX    R0                    ; Branch to reset handler of bootloader.

isr_abort
                                ; R4 contains ones from line above. Will be popped as R12 when exiting ISR (Cleaning up the registers).
    MOV   R5, R4                ; Fill with ones before jumping to reset handling. We be popped as LR when exiting ISR. Ensures no return to application.
    MOV   R6, R0                ; Move address of reset handler to R6. Will be popped as PC when exiting ISR. Ensures the reset handler will be executed when exist ISR.
    MOVS  r7, #0x21             ; Move MSB reset value of xPSR to R7. Will be popped as xPSR when exiting ISR. xPSR is 0x21000000 thus MSB is 0x21.
    REV   r7, r7                ; Reverse byte order to put 0x21 as MSB.
    PUSH  {r4-r7}               ; Push everything to new stack to allow interrupt handler to fetch it on exiting the ISR.

    MOVS  R4, #0x00             ; Fill with zeros before jumping to reset handling. We be popped as R0 when exiting ISR (Cleaning up of the registers).
    MOVS  R5, #0x00             ; Fill with zeros before jumping to reset handling. We be popped as R1 when exiting ISR (Cleaning up of the registers).
    MOVS  R6, #0x00             ; Fill with zeros before jumping to reset handling. We be popped as R2 when exiting ISR (Cleaning up of the registers).
    MOVS  R7, #0x00             ; Fill with zeros before jumping to reset handling. We be popped as R3 when exiting ISR (Cleaning up of the registers).
    PUSH  {r4-r7}               ; Push zeros (R4-R7) to stack to prepare for exiting the interrupt routine.

    MOVS  R0, #0xF9             ; Move the execution return command into register, 0xFFFFFFF9.
    SXTB  R0, R0                ; Sign extend R0 to obtain 0xFFFFFFF9 instead of 0xF9.
    BX    R0                    ; No return - Handler mode will be exited. Stack will be popped and execution will continue in reset handler initializing other application.
    ALIGN
}

#elif defined ( __GNUC__ )

void __attribute__ ((noinline)) nrf_bootloader_app_start_impl(uint32_t start_addr)
{
    __ASM volatile(
        "ldr   r0, [%0]\t\n"            // Get App initial MSP for bootloader.
        "msr   msp, r0\t\n"             // Set the main stack pointer to the applications MSP.
        "ldr   r0, [%0, #0x04]\t\n"     // Load Reset handler into R0.

        "movs  r4, #0xFF\t\n"           // Move ones to R4.
        "sxtb  r4, r4\t\n"              // Sign extend R4 to obtain 0xFFFFFFFF instead of 0xFF.

        "mrs   r5, IPSR\t\n"            // Load IPSR to R5 to check for handler or thread mode.
        "cmp   r5, #0x00\t\n"           // Compare, if 0 then we are in thread mode and can continue to reset handler of bootloader.
        "bne   isr_abort\t\n"           // If not zero we need to exit current ISR and jump to reset handler of bootloader.

        "mrs   r1, control\t\n"         // Get CONTROL register value
        "movs  r2, #0x02\t\n"           // load 2 to r2
        "bic   r1, r2\t\n"              // clear value of CONTROL->SPSEL - > make sure MSP will be used
        "msr   control, r1\t\n"         // set the stack pointer to MSP

        "mov   lr, r4\t\n"              // Clear the link register and set to ones to ensure no return.
        "bx    r0\t\n"                  // Branch to reset handler of bootloader.

        "isr_abort:  \t\n"

        "mov   r5, r4\t\n"              // Fill with ones before jumping to reset handling. Will be popped as LR when exiting ISR. Ensures no return to application.
        "mov   r6, r0\t\n"              // Move address of reset handler to R6. Will be popped as PC when exiting ISR. Ensures the reset handler will be executed when exist ISR.
        "movs  r7, #0x21\t\n"           // Move MSB reset value of xPSR to R7. Will be popped as xPSR when exiting ISR. xPSR is 0x21000000 thus MSB is 0x21.
        "rev   r7, r7\t\n"              // Reverse byte order to put 0x21 as MSB.
        "push  {r4-r7}\t\n"             // Push everything to new stack to allow interrupt handler to fetch it on exiting the ISR.

        "movs  r4, #0x00\t\n"           // Fill with zeros before jumping to reset handling. We be popped as R0 when exiting ISR (Cleaning up of the registers).
        "movs  r5, #0x00\t\n"           // Fill with zeros before jumping to reset handling. We be popped as R1 when exiting ISR (Cleaning up of the registers).
        "movs  r6, #0x00\t\n"           // Fill with zeros before jumping to reset handling. We be popped as R2 when exiting ISR (Cleaning up of the registers).
        "movs  r7, #0x00\t\n"           // Fill with zeros before jumping to reset handling. We be popped as R3 when exiting ISR (Cleaning up of the registers).
        "push  {r4-r7}\t\n"             // Push zeros (R4-R7) to stack to prepare for exiting the interrupt routine.

        "movs  r0, #0xF9\t\n"           // Move the execution return command into register, 0xFFFFFFF9.
        "sxtb  r0, r0\t\n"              // Sign extend R0 to obtain 0xFFFFFFF9 instead of 0xF9.
        "bx    r0\t\n"                  // No return - Handler mode will be exited. Stack will be popped and execution will continue in reset handler initializing other application.
        ".align\t\n"
        :: "r" (start_addr)             // Argument list for the gcc assembly. start_addr is %0.
        :  "r0", "r4", "r5", "r6", "r7" // List of register maintained manually.
    );
}

#elif defined ( __ICCARM__ )

void nrf_bootloader_app_start_impl(uint32_t start_addr)
{
    __ASM("ldr   r5, [%0]\n"                    // Get App initial MSP for bootloader.
        "msr   msp, r5\n"                     // Set the main stack pointer to the applications MSP.
        "ldr   r0, [%0, #0x04]\n"             // Load Reset handler into R0.

        "movs  r4, #0x00\n"                   // Load zero into R4.
        "mvns  r4, r4\n"                      // Invert R4 to ensure it contain ones.

        "mrs   r5, IPSR\n"                    // Load IPSR to R5 to check for handler or thread mode
        "cmp   r5, #0x00\n"                   // Compare, if 0 then we are in thread mode and can continue to reset handler of bootloader.
        "bne.n isr_abort\n"                   // If not zero we need to exit current ISR and jump to reset handler of bootloader.

        "mrs   r1, control\n"                 // Get CONTROL register value
        "movs  r2, #0x02\n"                   // load 2 to r2
        "bics  r1, r2\n"                      // clear value of CONTROL->SPSEL - > make sure MSP will be used
        "msr   control, r1\n"                 // set the stack pointer to MSP

        "mov   lr, r4\n"                      // Clear the link register and set to ones to ensure no return.
        "bx    r0\n"                          // Branch to reset handler of bootloader.

        "isr_abort: \n"
                                              // R4 contains ones from line above. We be popped as R12 when exiting ISR (Cleaning up the registers).
        "mov   r5, r4\n"                      // Fill with ones before jumping to reset handling. Will be popped as LR when exiting ISR. Ensures no return to application.
        "mov   r6, r0\n"                      // Move address of reset handler to R6. Will be popped as PC when exiting ISR. Ensures the reset handler will be executed when exist ISR.
        "movs  r7, #0x21\n"                   // Move MSB reset value of xPSR to R7. Will be popped as xPSR when exiting ISR. xPSR is 0x21000000 thus MSB is 0x21.
        "rev   r7, r7\n"                      // Reverse byte order to put 0x21 as MSB.
        "push  {r4-r7}\n"                     // Push everything to new stack to allow interrupt handler to fetch it on exiting the ISR.

        "movs  r4, #0x00\n"                   // Fill with zeros before jumping to reset handling. We be popped as R0 when exiting ISR (Cleaning up of the registers).
        "movs  r5, #0x00\n"                   // Fill with zeros before jumping to reset handling. We be popped as R1 when exiting ISR (Cleaning up of the registers).
        "movs  r6, #0x00\n"                   // Fill with zeros before jumping to reset handling. We be popped as R2 when exiting ISR (Cleaning up of the registers).
        "movs  r7, #0x00\n"                   // Fill with zeros before jumping to reset handling. We be popped as R3 when exiting ISR (Cleaning up of the registers).
        "push  {r4-r7}\n"                     // Push zeros (R4-R7) to stack to prepare for exiting the interrupt routine.

        "movs  r0, #0x06\n"                   // Load 0x06 into R6 to prepare for exec return command.
        "mvns  r0, r0\n"                      // Invert 0x06 to obtain EXEC_RETURN, 0xFFFFFFF9.
        "bx    r0\n"                          // No return - Handler mode will be exited. Stack will be popped and execution will continue in reset handler initializing other application.
        :: "r" (start_addr)                   // Argument list for the IAR assembly. start_addr is %0.
        :  "r0", "r4", "r5", "r6", "r7");     // List of register maintained manually.
}

#else

#error Compiler not supported.

#endif
