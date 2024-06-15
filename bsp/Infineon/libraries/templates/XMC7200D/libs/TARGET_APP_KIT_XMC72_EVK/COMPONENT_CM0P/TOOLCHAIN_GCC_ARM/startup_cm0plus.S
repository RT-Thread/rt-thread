/**************************************************************************//**
 * @file     startup_cm0plus.S
 * @brief    CMSIS-Core(M) Device Startup File for Cortex-M0plus Device
 * @version  V2.2.0
 * @date     26. May 2021
 ******************************************************************************/
/*
 * Copyright (c) 2009-2021 Arm Limited. All rights reserved.
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

#define CPUSS_RAM0_CTL0     0x40201300
#define CPUSS_RAM1_CTL0     0x40201380
#define CPUSS_RAM2_CTL0     0x402013a0


                .syntax  unified
                .arch    armv6-m

                .section .vectors
                .align   2
                .globl   __Vectors
                .globl   __Vectors_End
                .globl   __Vectors_Size
                .global  CM0P_CpuIntr2_Handler
                .global  CM0P_CpuIntr3_Handler
                .global  CM0P_CpuIntr4_Handler
                .global  CM0P_CpuIntr5_Handler
                .global  CM0P_CpuIntr6_Handler
                .global  CM0P_CpuIntr7_Handler

__Vectors:
                .long    __StackTop                         /*     Top of Stack */
                .long    Reset_Handler                      /*     Reset Handler */
                .long    NMI_Handler                        /* -14 NMI Handler */
                .long    HardFault_Handler                  /* -13 Hard Fault Handler */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    SVC_Handler                        /*  -5 SVCall Handler */
                .long    0                                  /*     Reserved */
                .long    0                                  /*     Reserved */
                .long    PendSV_Handler                     /*  -2 PendSV Handler */
                .long    SysTick_Handler                    /*  -1 SysTick Handler */

                /* Interrupts */
                .long    Default_Intr_Handler               /* CPU User Interrupt #0 */
                .long    Default_Intr_Handler               /* CPU User Interrupt #1 */
                .long    CM0P_CpuIntr2_Handler              /* CPU User Interrupt #2 */
                .long    CM0P_CpuIntr3_Handler              /* CPU User Interrupt #3 */
                .long    CM0P_CpuIntr4_Handler              /* CPU User Interrupt #4 */
                .long    CM0P_CpuIntr5_Handler              /* CPU User Interrupt #5 */
                .long    CM0P_CpuIntr6_Handler              /* CPU User Interrupt #6 */
                .long    CM0P_CpuIntr7_Handler              /* CPU User Interrupt #7 */
                .long    Default_Intr_Handler               /* Internal SW Interrupt #0 */
                .long    Default_Intr_Handler               /* Internal SW Interrupt #1 */
                .long    Default_Intr_Handler               /* Internal SW Interrupt #2 */
                .long    Default_Intr_Handler               /* Internal SW Interrupt #3 */
                .long    Default_Intr_Handler               /* Internal SW Interrupt #4 */
                .long    Default_Intr_Handler               /* Internal SW Interrupt #5 */
                .long    Default_Intr_Handler               /* Internal SW Interrupt #6 */
                .long    Default_Intr_Handler               /* Internal SW Interrupt #7 */

__Vectors_End:
                .equ     __Vectors_Size, __Vectors_End - __Vectors
                .size    __Vectors, . - __Vectors

                .section .ram_vectors
                .align 2
                .globl __ramVectors
__ramVectors:
                .space  __Vectors_Size
                .size   __ramVectors, . - __ramVectors

                .thumb
                .section .text
                .align   2

                .thumb_func
                .type    Reset_Handler, %function
                .globl   Reset_Handler
                .extern  __cmsis_start
                .fnstart
Reset_Handler:
                /* CM0+ bus width is 32-bit, but SRAM is built with 64-bit based ECC on Traveo II parts with CM7 core
                 * Set CPUSS->RAMx_CTL0.ECC_CHECK_DIS bits to avoid causing unintentional ECC faults during startup while SRAM ECC has not been initialized yet
                 * Generic code can be used, even if RAMx_CTL0 (x > 0) registers are not implemented in a device
                 * or if no ECC_CHECK_DIS bits are available in the registers in case of m4cpuss with 32-bit ECC SRAM
                 */
                movs r0, #1
                lsls r0, r0, #19
                ldr  r1, =CPUSS_RAM0_CTL0
                ldr  r2, [r1]
                orrs r2, r0
                str  r2, [r1]
                ldr  r1, =CPUSS_RAM1_CTL0
                ldr  r2, [r1]
                orrs r2, r0
                str  r2, [r1]
                ldr  r1, =CPUSS_RAM2_CTL0
                ldr  r2, [r1]
                orrs r2, r0
                str  r2, [r1]

                /* Initialize ECC of startup stack (needed for local variables in C startup code) by processing 8 bytes per loop iteration,
                 * because the ECC initialization feature uses this generic granularity that will cover any memory (SRAM/TCM) in any TVII device
                 * Prerequisite: Stack Pointer (SP) has not been modified (from the vector table init value) by above code (otherwise code must be adapted)
                 */
                ldr     r0, =__StackTop-0x100
                ldr     r1, =__StackTop
                movs    r2, #0
                movs    r3, #0
loopstackclean:
                stmia   r0!, {r2, r3}
                cmp     r0, r1
                bcc.n   loopstackclean

                bl       SystemInit

                bl       CyMain

                .fnend
                .size    Reset_Handler, . - Reset_Handler

                .thumb_func
                .type    Default_Handler, %function
                .weak    Default_Handler
Default_Handler:
                b        .
                .size    Default_Handler, . - Default_Handler
                .weak    Cy_SysLib_FaultHandler
                .type    Cy_SysLib_FaultHandler, %function

Cy_SysLib_FaultHandler:
                b    .
                .size    Cy_SysLib_FaultHandler, . - Cy_SysLib_FaultHandler
                .type Fault_Handler, %function

Fault_Handler:
/*              Storing LR content for Creator call stack trace */
                push {LR}
                movs r0, #4
                mov r1, LR
                tst r0, r1
                beq .L_MSP
                mrs r0, PSP
                b .L_API_call
.L_MSP:
                mrs r0, MSP
/*              Compensation of stack pointer address due to pushing 4 bytes of LR */
                adds r0, r0, #4
.L_API_call:
                bl Cy_SysLib_FaultHandler
                b   .
                .size    Fault_Handler, . - Fault_Handler

                .macro    Def_Fault_Handler    fault_handler_name
                .weak    \fault_handler_name
                .set    \fault_handler_name, Fault_Handler
                .endm

/*              Macro to define default exception/interrupt handlers.
 *              Default handler are weak symbols with an endless loop.
 *              They can be overwritten by real handlers.
 */
                .macro   Def_Irq_Handler  Handler_Name
                .weak    \Handler_Name
                .set     \Handler_Name, Default_Handler
                .endm

/*              Default exception/interrupt handlers */
                Def_Irq_Handler  NMI_Handler

                Def_Fault_Handler    HardFault_Handler

                Def_Irq_Handler  SVC_Handler
                Def_Irq_Handler  PendSV_Handler
                Def_Irq_Handler  SysTick_Handler
                Def_Irq_Handler  Default_Intr_Handler

                .end

/* [] END OF FILE */
