/**************************************************************************//**
 * @file     startup_psoc6_01_cm0plus.S
 * @brief    CMSIS Core Device Startup File for
 *           ARMCM0plus Device Series
 * @version  V5.00
 * @date     02. March 2016
 ******************************************************************************/
/*
 * Copyright (c) 2009-2016 ARM Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

    /* Address of the NMI handler */
    #define CY_NMI_HANLDER_ADDR         0x0000000D

    /* The CPU VTOR register */
    #define CY_CPU_VTOR_ADDR            0xE000ED08

    .syntax    unified

    .section __STACK, __stack
    .align    3
#ifdef __STACK_SIZE
    .equ    Stack_Size, __STACK_SIZE
#else
    .equ    Stack_Size, 0x00001000
#endif
    .globl    __StackTop
    .globl    __StackLimit

__StackLimit:
    .space    Stack_Size
    .equ    __StackTop, . - Stack_Size

    .section __HEAP, __heap
    .align    3
#ifdef __HEAP_SIZE
    .equ    Heap_Size, __HEAP_SIZE
#else
    .equ    Heap_Size, 0x00000400
#endif
    .globl    __HeapBase
__HeapBase:
    .if    Heap_Size
    .space    Heap_Size
    .endif

    .section __VECT, ___Vectors
    .align 2
    .globl    ___Vectors
___Vectors:
    .long    __StackTop            /* Top of Stack */
    .long    Reset_Handler         /* Reset Handler */
    .long    CY_NMI_HANLDER_ADDR   /* NMI Handler */
    .long    HardFault_Handler     /* Hard Fault Handler */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    SVC_Handler           /* SVCall Handler */
    .long    0                     /* Reserved */
    .long    0                     /* Reserved */
    .long    PendSV_Handler        /* PendSV Handler */
    .long    SysTick_Handler       /* SysTick Handler */

     /* External interrupts                             Description */
    .long    NvicMux0_IRQHandler                     /* CM0+ NVIC Mux input 0 */
    .long    NvicMux1_IRQHandler                     /* CM0+ NVIC Mux input 1 */
    .long    NvicMux2_IRQHandler                     /* CM0+ NVIC Mux input 2 */
    .long    NvicMux3_IRQHandler                     /* CM0+ NVIC Mux input 3 */
    .long    NvicMux4_IRQHandler                     /* CM0+ NVIC Mux input 4 */
    .long    NvicMux5_IRQHandler                     /* CM0+ NVIC Mux input 5 */
    .long    NvicMux6_IRQHandler                     /* CM0+ NVIC Mux input 6 */
    .long    NvicMux7_IRQHandler                     /* CM0+ NVIC Mux input 7 */
    .long    NvicMux8_IRQHandler                     /* CM0+ NVIC Mux input 8 */
    .long    NvicMux9_IRQHandler                     /* CM0+ NVIC Mux input 9 */
    .long    NvicMux10_IRQHandler                    /* CM0+ NVIC Mux input 10 */
    .long    NvicMux11_IRQHandler                    /* CM0+ NVIC Mux input 11 */
    .long    NvicMux12_IRQHandler                    /* CM0+ NVIC Mux input 12 */
    .long    NvicMux13_IRQHandler                    /* CM0+ NVIC Mux input 13 */
    .long    NvicMux14_IRQHandler                    /* CM0+ NVIC Mux input 14 */
    .long    NvicMux15_IRQHandler                    /* CM0+ NVIC Mux input 15 */
    .long    NvicMux16_IRQHandler                    /* CM0+ NVIC Mux input 16 */
    .long    NvicMux17_IRQHandler                    /* CM0+ NVIC Mux input 17 */
    .long    NvicMux18_IRQHandler                    /* CM0+ NVIC Mux input 18 */
    .long    NvicMux19_IRQHandler                    /* CM0+ NVIC Mux input 19 */
    .long    NvicMux20_IRQHandler                    /* CM0+ NVIC Mux input 20 */
    .long    NvicMux21_IRQHandler                    /* CM0+ NVIC Mux input 21 */
    .long    NvicMux22_IRQHandler                    /* CM0+ NVIC Mux input 22 */
    .long    NvicMux23_IRQHandler                    /* CM0+ NVIC Mux input 23 */
    .long    NvicMux24_IRQHandler                    /* CM0+ NVIC Mux input 24 */
    .long    NvicMux25_IRQHandler                    /* CM0+ NVIC Mux input 25 */
    .long    NvicMux26_IRQHandler                    /* CM0+ NVIC Mux input 26 */
    .long    NvicMux27_IRQHandler                    /* CM0+ NVIC Mux input 27 */
    .long    NvicMux28_IRQHandler                    /* CM0+ NVIC Mux input 28 */
    .long    NvicMux29_IRQHandler                    /* CM0+ NVIC Mux input 29 */
    .long    NvicMux30_IRQHandler                    /* CM0+ NVIC Mux input 30 */
    .long    NvicMux31_IRQHandler                    /* CM0+ NVIC Mux input 31 */

    .equ    __VectorsSize, . - ___Vectors

    .section __RAMVECTORS, ___ramVectors
    .align 2
    .globl ___ramVectors

___ramVectors:
    .space  __VectorsSize


    .text
    .thumb_func
    .align 2
    /* Reset handler */
    .globl Reset_Handler

Reset_Handler:
    bl Cy_OnResetUser
    cpsid i

/*  Single section scheme.
 *
 *  The ranges of copy from/to are specified by following symbols
 *    __etext: LMA of start of the section to copy from. Usually end of text
 *    __data_start__: VMA of start of the section to copy to
 *    __data_end__: VMA of end of the section to copy to
 *
 *  All addresses must be aligned to 4 bytes boundary.
 */
    ldr    r0, =___ramVectors
    ldr    r1, =___Vectors
    ldr    r2, =__VectorsSize
    bl     _memcpy

    ldr    r0, =segment$start$__DATA
    ldr    r1, =segment$end$__TEXT
    ldr    r2, =section$start$__DATA$__zerofill
    sub    r2, r0
    bl     _memcpy

    ldr    r0, =section$start$__DATA$__zerofill
    eor    r1, r1
    ldr    r2, =section$end$__DATA$__zerofill
    sub    r2, r0
    bl     _memset

    /* Update Vector Table Offset Register. */
    ldr r0, =___ramVectors
    ldr r1, =CY_CPU_VTOR_ADDR
    str r0, [r1]
    dsb 0xF

    bl _HeapInit
#ifndef __NO_SYSTEM_INIT
    bl  _SystemInit
#endif

    bl  _main

    /* Should never get here */
    b   .

    .pool

    .text
    .thumb
    .thumb_func
    .align 2

    /* Device startup customization */
    .weak_definition   Cy_OnResetUser
    .global Cy_OnResetUser, Cy_OnResetUser
Cy_OnResetUser:
    bx lr

    .text
    .align    1
    .thumb_func
    .weak_reference    Default_Handler

Default_Handler:
    b    .

    .text
    .thumb_func
    .align  2
    .weak_definition    Cy_SysLib_FaultHandler

Cy_SysLib_FaultHandler:
    b    .

    .text
    .thumb_func
    .align  2

Fault_Handler:
    /* Storing LR content for Creator call stack trace */
    push {LR}
    movs r0, #4
    mov r1, LR
    tst r0, r1
    beq .L_MSP
    mrs r0, PSP
    b .L_API_call
.L_MSP:
    mrs r0, MSP
.L_API_call:
    /* Compensation of stack pointer address due to pushing 4 bytes of LR */
    adds r0, r0, #4
    bl Cy_SysLib_FaultHandler
    b   .

.macro    def_fault_Handler    fault_handler_name
    .weak_definition    \fault_handler_name
    .set    \fault_handler_name, Fault_Handler
    .endm

/*    Macro to define default handlers. Default handler
 *    will be weak symbol and just dead loops. They can be
 *    overwritten by other handlers */
    .macro    def_irq_handler    handler_name
    .weak_definition    \handler_name
    .set    \handler_name, Default_Handler
    .endm

    def_irq_handler    NMI_Handler

    def_fault_Handler  HardFault_Handler

    def_irq_handler    SVC_Handler
    def_irq_handler    PendSV_Handler
    def_irq_handler    SysTick_Handler

    def_irq_handler  NvicMux0_IRQHandler                     /* CM0+ NVIC Mux input 0 */
    def_irq_handler  NvicMux1_IRQHandler                     /* CM0+ NVIC Mux input 1 */
    def_irq_handler  NvicMux2_IRQHandler                     /* CM0+ NVIC Mux input 2 */
    def_irq_handler  NvicMux3_IRQHandler                     /* CM0+ NVIC Mux input 3 */
    def_irq_handler  NvicMux4_IRQHandler                     /* CM0+ NVIC Mux input 4 */
    def_irq_handler  NvicMux5_IRQHandler                     /* CM0+ NVIC Mux input 5 */
    def_irq_handler  NvicMux6_IRQHandler                     /* CM0+ NVIC Mux input 6 */
    def_irq_handler  NvicMux7_IRQHandler                     /* CM0+ NVIC Mux input 7 */
    def_irq_handler  NvicMux8_IRQHandler                     /* CM0+ NVIC Mux input 8 */
    def_irq_handler  NvicMux9_IRQHandler                     /* CM0+ NVIC Mux input 9 */
    def_irq_handler  NvicMux10_IRQHandler                    /* CM0+ NVIC Mux input 10 */
    def_irq_handler  NvicMux11_IRQHandler                    /* CM0+ NVIC Mux input 11 */
    def_irq_handler  NvicMux12_IRQHandler                    /* CM0+ NVIC Mux input 12 */
    def_irq_handler  NvicMux13_IRQHandler                    /* CM0+ NVIC Mux input 13 */
    def_irq_handler  NvicMux14_IRQHandler                    /* CM0+ NVIC Mux input 14 */
    def_irq_handler  NvicMux15_IRQHandler                    /* CM0+ NVIC Mux input 15 */
    def_irq_handler  NvicMux16_IRQHandler                    /* CM0+ NVIC Mux input 16 */
    def_irq_handler  NvicMux17_IRQHandler                    /* CM0+ NVIC Mux input 17 */
    def_irq_handler  NvicMux18_IRQHandler                    /* CM0+ NVIC Mux input 18 */
    def_irq_handler  NvicMux19_IRQHandler                    /* CM0+ NVIC Mux input 19 */
    def_irq_handler  NvicMux20_IRQHandler                    /* CM0+ NVIC Mux input 20 */
    def_irq_handler  NvicMux21_IRQHandler                    /* CM0+ NVIC Mux input 21 */
    def_irq_handler  NvicMux22_IRQHandler                    /* CM0+ NVIC Mux input 22 */
    def_irq_handler  NvicMux23_IRQHandler                    /* CM0+ NVIC Mux input 23 */
    def_irq_handler  NvicMux24_IRQHandler                    /* CM0+ NVIC Mux input 24 */
    def_irq_handler  NvicMux25_IRQHandler                    /* CM0+ NVIC Mux input 25 */
    def_irq_handler  NvicMux26_IRQHandler                    /* CM0+ NVIC Mux input 26 */
    def_irq_handler  NvicMux27_IRQHandler                    /* CM0+ NVIC Mux input 27 */
    def_irq_handler  NvicMux28_IRQHandler                    /* CM0+ NVIC Mux input 28 */
    def_irq_handler  NvicMux29_IRQHandler                    /* CM0+ NVIC Mux input 29 */
    def_irq_handler  NvicMux30_IRQHandler                    /* CM0+ NVIC Mux input 30 */
    def_irq_handler  NvicMux31_IRQHandler                    /* CM0+ NVIC Mux input 31 */

    .end


/* [] END OF FILE */
