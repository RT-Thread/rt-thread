;/**************************************************************************//**
; * @file     startup_cm0plus.s
; * @brief    CMSIS Core Device Startup File for
; *           ARMCM0plus Device
; * @version  V1.0.1
; * @date     23. July 2019
; ******************************************************************************/
;/*
; * Copyright (c) 2009-2019 Arm Limited. All rights reserved.
; *
; * SPDX-License-Identifier: Apache-2.0
; *
; * Licensed under the Apache License, Version 2.0 (the License); you may
; * not use this file except in compliance with the License.
; * You may obtain a copy of the License at
; *
; * www.apache.org/licenses/LICENSE-2.0
; *
; * Unless required by applicable law or agreed to in writing, software
; * distributed under the License is distributed on an AS IS BASIS, WITHOUT
; * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; * See the License for the specific language governing permissions and
; * limitations under the License.
; */

;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------


;<h> Stack Configuration
;  <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
;</h>

CPUSS_RAM0_CTL0     EQU 0x40201300
CPUSS_RAM1_CTL0     EQU 0x40201380
CPUSS_RAM2_CTL0     EQU 0x402013a0



                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA     RESET, DATA, READONLY
                EXPORT   __Vectors
                EXPORT   __Vectors_End
                EXPORT   __Vectors_Size

                IMPORT |Image$$ARM_LIB_STACK$$ZI$$Base|
                IMPORT |Image$$ARM_LIB_STACK$$ZI$$Length|

__Vectors       DCD      |Image$$ARM_LIB_STACK$$ZI$$Base| + |Image$$ARM_LIB_STACK$$ZI$$Length|         ;     Top of Stack
                DCD      Reset_Handler                       ;     Reset Handler
                DCD      NMI_Handler                         ; -14 NMI Handler
                DCD      HardFault_Handler                   ; -13 Hard Fault Handler
                DCD      0                                   ;     Reserved
                DCD      0                                   ;     Reserved
                DCD      0                                   ;     Reserved
                DCD      0                                   ;     Reserved
                DCD      0                                   ;     Reserved
                DCD      0                                   ;     Reserved
                DCD      0                                   ;     Reserved
                DCD      SVC_Handler                         ;  -5 SVCall Handler
                DCD      0                                   ;     Reserved
                DCD      0                                   ;     Reserved
                DCD      PendSV_Handler                      ;  -2 PendSV Handler
                DCD      SysTick_Handler                     ;  -1 SysTick Handler

                ; Interrupts
                DCD     Default_Intr_Handler                   ; CPU User Interrupt #0
                DCD     Default_Intr_Handler                   ; CPU User Interrupt #1
                DCD     CM0P_CpuIntr2_Handler                   ; CPU User Interrupt #2
                DCD     CM0P_CpuIntr3_Handler                   ; CPU User Interrupt #3
                DCD     CM0P_CpuIntr4_Handler                   ; CPU User Interrupt #4
                DCD     CM0P_CpuIntr5_Handler                   ; CPU User Interrupt #5
                DCD     CM0P_CpuIntr6_Handler                   ; CPU User Interrupt #6
                DCD     CM0P_CpuIntr7_Handler                   ; CPU User Interrupt #7
                DCD     Default_Intr_Handler                  ; Internal SW Interrupt #0
                DCD     Default_Intr_Handler                  ; Internal SW Interrupt #1
                DCD     Default_Intr_Handler                  ; Internal SW Interrupt #2
                DCD     Default_Intr_Handler                  ; Internal SW Interrupt #3
                DCD     Default_Intr_Handler                  ; Internal SW Interrupt #4
                DCD     Default_Intr_Handler                  ; Internal SW Interrupt #5
                DCD     Default_Intr_Handler                  ; Internal SW Interrupt #6
                DCD     Default_Intr_Handler                  ; Internal SW Interrupt #7

__Vectors_End
__Vectors_Size  EQU      __Vectors_End - __Vectors
                EXPORT __ramVectors
                AREA    RESET_RAM, READWRITE, NOINIT
__ramVectors    SPACE   __Vectors_Size

                AREA     |.text|, CODE, READONLY

; Reset Handler

Reset_Handler   PROC
                EXPORT   Reset_Handler             [WEAK]
                IMPORT   SystemInit
                IMPORT   CyMain

                ; Disable global interrupts
                CPSID I

                ; CM0+ bus width is 32-bit, but SRAM is built with 64-bit based ECC on Traveo II parts with CM7 core
                ; Set CPUSS->RAMx_CTL0.ECC_CHECK_DIS bits to avoid causing unintentional ECC faults during startup while SRAM ECC has not been initialized yet
                ; Generic code can be used, even if RAMx_CTL0 (x > 0) registers are not implemented in a device
                ; or if no ECC_CHECK_DIS bits are available in the registers in case of m4cpuss with 32-bit ECC SRAM
                MOVS r0, #1
                LSLS r0, r0, #19
                LDR  r1, =CPUSS_RAM0_CTL0
                LDR  r2, [r1]
                ORRS r2, r0
                STR  r2, [r1]
                LDR  r1, =CPUSS_RAM1_CTL0
                LDR  r2, [r1]
                ORRS r2, r0
                STR  r2, [r1]
                LDR  r1, =CPUSS_RAM2_CTL0
                LDR  r2, [r1]
                ORRS r2, r0
                STR  r2, [r1]

                ; Initialize ECC of startup stack (needed for local variables in C startup code) by processing 8 bytes per loop iteration,
                ; because the ECC initialization feature uses this generic granularity that will cover any memory (SRAM/TCM) in any TVII device
                ; Prerequisite: Stack Pointer (SP) has not been modified (from the vector table init value) by above code (otherwise code must be adapted)
                LDR     r3, =|Image$$ARM_LIB_STACK$$ZI$$Base|
                LDR     r1, =|Image$$ARM_LIB_STACK$$ZI$$Length|
                ADD     r1, r1, r3 ; r1 = stack top
                MOV     r0, r1
                LDR     r3, =0x100
                SUBS    r0, r0, r3 ; r0 = stack offset

                MOVS    r2, #0  ; clear value
                MOVS    r3, #0  ; clear value
loopstackclean
                STM     r0!, {r2, r3}
                CMP     r0, r1
                BNE     loopstackclean

                LDR      R0, =SystemInit
                BLX      R0
                LDR      R0, =CyMain
                BX       R0
                ENDP

Default_Handler     PROC
                    EXPORT  Default_Handler                         [WEAK]
                    EXPORT  CM0P_CpuIntr2_Handler                   [WEAK]
                    EXPORT  CM0P_CpuIntr3_Handler                   [WEAK]
                    EXPORT  CM0P_CpuIntr4_Handler                   [WEAK]
                    EXPORT  CM0P_CpuIntr5_Handler                   [WEAK]
                    EXPORT  CM0P_CpuIntr6_Handler                   [WEAK]
                    EXPORT  CM0P_CpuIntr7_Handler                   [WEAK]

CM0P_CpuIntr2_Handler
CM0P_CpuIntr3_Handler
CM0P_CpuIntr4_Handler
CM0P_CpuIntr5_Handler
CM0P_CpuIntr6_Handler
CM0P_CpuIntr7_Handler
                    B       .
                    ENDP

Cy_SysLib_FaultHandler PROC
                    EXPORT  Cy_SysLib_FaultHandler    [WEAK]
                    B       .
                    ENDP

; The default macro is not used for HardFault_Handler
; because this results in a poor debug illusion.
HardFault_Handler   PROC
                    EXPORT HardFault_Handler          [WEAK]
                    movs r0, #4
                    mov r1, LR
                    tst r0, r1
                    beq L_MSP
                    mrs r0, PSP
                    bl L_API_call
L_MSP
                    mrs r0, MSP
L_API_call
                    bl Cy_SysLib_FaultHandler
                    ENDP

; Macro to define default exception/interrupt handlers.
; Default handler are weak symbols with an endless loop.
; They can be overwritten by real handlers.
                MACRO
                Set_Default_Handler  $Handler_Name
$Handler_Name   PROC
                EXPORT   $Handler_Name             [WEAK]
                B        .
                ENDP
                MEND


; Default exception/interrupt handler

                Set_Default_Handler  NMI_Handler
                Set_Default_Handler  SVC_Handler
                Set_Default_Handler  PendSV_Handler
                Set_Default_Handler  SysTick_Handler

                Set_Default_Handler  Default_Intr_Handler


                ALIGN


                END

