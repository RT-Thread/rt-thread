/***********************************************************************************
 *                           SEGGER Microcontroller GmbH                           *
 *                               The Embedded Experts                              *
 ***********************************************************************************
 *                                                                                 *
 *                   (c) 2014 - 2018 SEGGER Microcontroller GmbH                   *
 *                                                                                 *
 *                  www.segger.com     Support: support@segger.com                 *
 *                                                                                 *
 ***********************************************************************************
 *                                                                                 *
 *        All rights reserved.                                                     *
 *                                                                                 *
 *        Redistribution and use in source and binary forms, with or               *
 *        without modification, are permitted provided that the following          *
 *        conditions are met:                                                      *
 *                                                                                 *
 *        - Redistributions of source code must retain the above copyright         *
 *          notice, this list of conditions and the following disclaimer.          *
 *                                                                                 *
 *        - Neither the name of SEGGER Microcontroller GmbH                        *
 *          nor the names of its contributors may be used to endorse or            *
 *          promote products derived from this software without specific           *
 *          prior written permission.                                              *
 *                                                                                 *
 *        THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND                   *
 *        CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,              *
 *        INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF                 *
 *        MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE                 *
 *        DISCLAIMED.                                                              *
 *        IN NO EVENT SHALL SEGGER Microcontroller GmbH BE LIABLE FOR              *
 *        ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR                 *
 *        CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT        *
 *        OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;          *
 *        OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF            *
 *        LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT                *
 *        (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE        *
 *        USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH         *
 *        DAMAGE.                                                                  *
 *                                                                                 *
 ***********************************************************************************/

/************************************************************************************
 *                         Preprocessor Definitions                                 *
 *                         ------------------------                                 *
 * NO_FPU_ENABLE                                                                    *
 *                                                                                  *
 *   If defined, FPU will not be enabled.                                           *
 *                                                                                  *
 * NO_STACK_INIT                                                                    *
 *                                                                                  *
 *   If defined, the stack pointer will not be initialised.                         *
 *                                                                                  *
 * NO_SYSTEM_INIT                                                                   *
 *                                                                                  *
 *   If defined, the SystemInit() function will not be called. By default           *
 *   SystemInit() is called after reset to enable the clocks and memories to        *
 *   be initialised prior to any C startup initialisation.                          *
 *                                                                                  *
 * NO_VTOR_CONFIG                                                                   *
 *                                                                                  *
 *   If defined, the vector table offset register will not be configured.           *
 *                                                                                  *
 * MEMORY_INIT                                                                      *
 *                                                                                  *
 *   If defined, the MemoryInit() function will be called. By default               *
 *   MemoryInit() is called after SystemInit() to enable an external memory         *
 *   controller.                                                                    *
 *                                                                                  *
 * STACK_INIT_VAL                                                                   *
 *                                                                                  *
 *   If defined, specifies the initial stack pointer value. If undefined,           *
 *   the stack pointer will be initialised to point to the end of the               *
 *   RAM segment.                                                                   *
 *                                                                                  *
 * VECTORS_IN_RAM                                                                   *
 *                                                                                  *
 *   If defined, the exception vectors will be copied from Flash to RAM.            *
 *                                                                                  *
 ************************************************************************************/

  .syntax unified

  .global Reset_Handler
#ifdef INITIALIZE_USER_SECTIONS  
  .global InitializeUserMemorySections
#endif
  .extern _vectors
  .extern nRFInitialize

  .section .init, "ax"
  .thumb_func

  .equ VTOR_REG, 0xE000ED08
  .equ FPU_CPACR_REG, 0xE000ED88

#ifndef STACK_INIT_VAL
#define STACK_INIT_VAL __RAM_segment_end__
#endif

Reset_Handler:

  /* Perform prestart tasks. */
  ldr r0, =nRFInitialize
  blx r0
  
#ifndef NO_STACK_INIT
  /* Initialise main stack */
  ldr r0, =STACK_INIT_VAL
  ldr r1, =0x7
  bics r0, r1
  mov sp, r0
#endif

#ifndef NO_SYSTEM_INIT
  /* Initialise system */
  ldr r0, =SystemInit
  blx r0
#endif

#ifdef MEMORY_INIT
  ldr r0, =MemoryInit
  blx r0
#endif

#ifdef VECTORS_IN_RAM
  /* Copy exception vectors into RAM */
  ldr r0, =__vectors_start__
  ldr r1, =__vectors_end__
  ldr r2, =__vectors_ram_start__
1:
  cmp r0, r1
  beq 2f
  ldr r3, [r0]
  str r3, [r2]
  adds r0, r0, #4
  adds r2, r2, #4
  b 1b
2:
#endif

#ifndef NO_VTOR_CONFIG
  /* Configure vector table offset register */
  ldr r0, =VTOR_REG
#ifdef VECTORS_IN_RAM
  ldr r1, =_vectors_ram
#else
  ldr r1, =_vectors
#endif
  str r1, [r0]
#endif

#if (defined(__ARM_ARCH_FPV4_SP_D16__) || defined(__ARM_ARCH_FPV5_D16__)) && !defined(NO_FPU_ENABLE)
  /* Enable FPU */
  ldr r0, =FPU_CPACR_REG
  ldr r1, [r0]
  orr r1, r1, #(0xF << 20)
  str r1, [r0]
  dsb
  isb
#endif

  /* Jump to program start */
  b _start

#ifdef INITIALIZE_USER_SECTIONS  
  .thumb_func
InitializeUserMemorySections:
  ldr r0, =__start_nrf_sections
  ldr r1, =__start_nrf_sections_run
  ldr r2, =__end_nrf_sections_run
  cmp r0, r1
  beq 2f
  subs r2, r2, r1
  beq 2f
1:
  ldrb r3, [r0]
  adds r0, r0, #1
  strb r3, [r1]
  adds r1, r1, #1
  subs r2, r2, #1
  bne 1b
2:
  bx lr
#endif