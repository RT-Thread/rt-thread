;/**************************************************************************//**
; * @file     startup_cm0plus.s
; * @brief    CMSIS Core Device Startup File for
; *           ARMCM0plus Device
; * @version  V1.0.0
; * @date     09. July 2018
; ******************************************************************************/
;/*
; * Copyright (c) 2009-2018 Arm Limited. All rights reserved.
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

;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; The name "__vector_table" has special meaning for C-SPY:
; it is where the SP start value is found, and the NVIC vector
; table register (VTOR) is initialized to this address if != 0.
;
; Cortex-M version
;

        MODULE  ?cstartup


;************************************************************************
;* Local definitions
;************************************************************************

; Set a sufficient startup stack size for correct operation of C startup code (startup.c)
STARTUP_STACK_SIZE_DOUBLE_WORDS    EQU 32

VTOR                               EQU 0xe000ed08

CPUSS_RAM0_CTL0                    EQU 0x40201300
CPUSS_RAM1_CTL0                    EQU 0x40201380
CPUSS_RAM2_CTL0                    EQU 0x402013a0


;************************************************************************
;* Import symbols
;************************************************************************

        EXTERN  CM0P_CpuIntr2_Handler
        EXTERN  CM0P_CpuIntr3_Handler
        EXTERN  CM0P_CpuIntr4_Handler
        EXTERN  CM0P_CpuIntr5_Handler
        EXTERN  CM0P_CpuIntr6_Handler
        EXTERN  CM0P_CpuIntr7_Handler
        EXTERN  __iar_program_start
        EXTERN  __iar_data_init3
        EXTERN  __iar_dynamic_initialization
        EXTERN  SystemInit
        EXTERN  CyMain


;************************************************************************
;* Export symbols
;************************************************************************

        PUBLIC  __vector_table
        PUBLIC  __vector_table_0x1c
        PUBLIC  __Vectors
        PUBLIC  __Vectors_End
        PUBLIC  __Vectors_Size
        PUBLIC  __ramVectors
        PUBLIC  Cy_u32StartupStackStartAddress
        PUBLIC  Cy_u32StartupStackEndAddress


;************************************************************************
;* Vector Table and RAM Vector Table
;************************************************************************

        SECTION CSTACK:DATA:NOROOT(3)

        ; align to 256 byte, because CM0_VECTOR_TABLE_BASE register only supports address bits [31:8] (Note: for VTOR a 128-byte alignment would be ok)
        SECTION .intvec:CODE:ROOT(8)
        DATA

__vector_table:
        DCD     sfe(CSTACK)
        DCD     Reset_Handler
        DCD     NMI_Handler
        DCD     HardFault_Handler
        DCD     0
        DCD     0
        DCD     0
__vector_table_0x1c:
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     SVC_Handler
        DCD     0
        DCD     0
        DCD     PendSV_Handler
        DCD     SysTick_Handler

        ; External interrupts              PowerMode    Description

        DCD     DefaultInt_Handler           ; DeepSleep    CPU User Interrupt #0 ; updated in RAM vector table with corresponding SROM vector table entry (after ROM-to-RAM copy)
        DCD     DefaultInt_Handler           ; DeepSleep    CPU User Interrupt #1 ; updated in RAM vector table with corresponding SROM vector table entry (after ROM-to-RAM copy)
        DCD     CM0P_CpuIntr2_Handler      ; DeepSleep    CPU User Interrupt #2
        DCD     CM0P_CpuIntr3_Handler      ; DeepSleep    CPU User Interrupt #3
        DCD     CM0P_CpuIntr4_Handler      ; DeepSleep    CPU User Interrupt #4
        DCD     CM0P_CpuIntr5_Handler      ; DeepSleep    CPU User Interrupt #5
        DCD     CM0P_CpuIntr6_Handler      ; DeepSleep    CPU User Interrupt #6
        DCD     CM0P_CpuIntr7_Handler      ; DeepSleep    CPU User Interrupt #7

        ; These IRQs can only be triggered by SW via NVIC regs
        DCD     CpuUserInt8_Handler      ; Active       CPU User Interrupt #8
        DCD     CpuUserInt9_Handler      ; Active       CPU User Interrupt #9
        DCD     CpuUserInt10_Handler     ; Active       CPU User Interrupt #10
        DCD     CpuUserInt11_Handler     ; Active       CPU User Interrupt #11
        DCD     CpuUserInt12_Handler     ; Active       CPU User Interrupt #12
        DCD     CpuUserInt13_Handler     ; Active       CPU User Interrupt #13
        DCD     CpuUserInt14_Handler     ; Active       CPU User Interrupt #14
        DCD     CpuUserInt15_Handler     ; Active       CPU User Interrupt #15
__Vectors_End:

__Vectors       EQU   __vector_table
__Vectors_Size  EQU   __Vectors_End - __Vectors

        ; use same alignment like vector table in ROM above (even though VTOR minimum requirement would be 128 bytes if not used in combination with CM0_VECTOR_TABLE_BASE register)
        SECTION .intvec_ram:DATA:ROOT(8)
__ramVectors:
        DS8     __Vectors_Size


;************************************************************************
;* Start-up Code
;************************************************************************

        THUMB
        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler:

; Disable global interrupts
        CPSID   I

; Update Vector Table Offset Register with address of user ROM table
; (will be updated later to user RAM table address in C startup code)
        LDR  r0, =__vector_table
        LDR  r1, =VTOR
        STR  r0, [r1]
        DSB

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
        MOVS r0, #0 ; clear value
        MOVS r1, #0 ; clear value
        LDR  r2, Cy_u32StartupStackStartAddress
startup_stack_ecc_init_loop:
        STM  r2!, {r0, r1}
        CMP  r2, sp
        BNE  startup_stack_ecc_init_loop
; Call C startup code (no ANSI C context established yet!)
        LDR   r0, =SystemInit
        BLX   r0

        LDR   r0, =CyMain
        BLX   r0

; Note: Control flow does not necessarily return here.
; On some tool-chains (e.g. IAR) control flow will never return from
; the system library.
Cy_Main_Exited:
        B    Cy_Main_Exited

;************************************************************************
;* Literal pool
;************************************************************************

        ALIGNROM 2

        LTORG

        DATA

        ALIGNROM 2

STARTUP_STACK_SIZE_BYTES    EQU (STARTUP_STACK_SIZE_DOUBLE_WORDS * 8)  ; Multiplication does not work in below data definition directive, so an additional define is created

Cy_u32StartupStackStartAddress:
        DCD (sfe(CSTACK) - STARTUP_STACK_SIZE_BYTES)

Cy_u32StartupStackEndAddress:
        DCD (sfe(CSTACK) - 1)



;************************************************************************
;* Default and weak implementation of interrupt handlers
;************************************************************************


        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
NMI_Handler:
        B NMI_Handler

;-----------------------------------------

        PUBWEAK Cy_SysLib_FaultHandler
        SECTION .text:CODE:REORDER:NOROOT(2)
Cy_SysLib_FaultHandler:
        B Cy_SysLib_FaultHandler

;-----------------------------------------

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
HardFault_Handler:
        IMPORT Cy_SysLib_FaultHandler
        MOVS r0, #4
        MOV  r1, lr
        TST  r0, r1
        BEQ  L_MSP
        MRS  r0, PSP
        B    L_API_call
L_MSP
        MRS  r0, MSP
L_API_call
        ; Storing LR content for Creator call stack trace
        PUSH {lr}
        LDR  r1, =Cy_SysLib_FaultHandler
        BLX  r1

;-----------------------------------------

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
SVC_Handler:
        B SVC_Handler

;-----------------------------------------

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
PendSV_Handler:
        B PendSV_Handler

;-----------------------------------------

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
SysTick_Handler:
        B SysTick_Handler


;-----------------------------------------


        PUBWEAK DefaultInt_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
DefaultInt_Handler:
        B DefaultInt_Handler

;-----------------------------------------

        ; External interrupts
        ; Traveo II CPU User Interrupts 0-7 handlers are defined in the project interrupt mapping file
        ; Traveo II CPU User Interrupts 8-15 can only be used as SW interrupts and need to be defined by user (weak implementation provided below)


        PUBWEAK CpuUserInt8_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
CpuUserInt8_Handler:
        B CpuUserInt8_Handler

;-----------------------------------------

        PUBWEAK CpuUserInt9_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
CpuUserInt9_Handler:
        B CpuUserInt9_Handler

;-----------------------------------------

        PUBWEAK CpuUserInt10_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
CpuUserInt10_Handler:
        B CpuUserInt10_Handler

;-----------------------------------------

        PUBWEAK CpuUserInt11_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
CpuUserInt11_Handler:
        B CpuUserInt11_Handler

;-----------------------------------------

        PUBWEAK CpuUserInt12_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
CpuUserInt12_Handler:
        B CpuUserInt12_Handler

;-----------------------------------------

        PUBWEAK CpuUserInt13_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
CpuUserInt13_Handler:
        B CpuUserInt13_Handler

;-----------------------------------------

        PUBWEAK CpuUserInt14_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
CpuUserInt14_Handler:
        B CpuUserInt14_Handler

;-----------------------------------------

        PUBWEAK CpuUserInt15_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
CpuUserInt15_Handler:
        B CpuUserInt15_Handler

;-----------------------------------------


;************************************************************************
;* File end
;************************************************************************

        END


