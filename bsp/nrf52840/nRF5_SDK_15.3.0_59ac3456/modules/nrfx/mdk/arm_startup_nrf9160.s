; Copyright (c) 2009-2018 ARM Limited. All rights reserved.
; 
;     SPDX-License-Identifier: Apache-2.0
; 
; Licensed under the Apache License, Version 2.0 (the License); you may
; not use this file except in compliance with the License.
; You may obtain a copy of the License at
; 
;     www.apache.org/licenses/LICENSE-2.0
; 
; Unless required by applicable law or agreed to in writing, software
; distributed under the License is distributed on an AS IS BASIS, WITHOUT
; WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; See the License for the specific language governing permissions and
; limitations under the License.
; 
; NOTICE: This file has been modified by Nordic Semiconductor ASA.

                IF :DEF: __STARTUP_CONFIG
#ifdef  __STARTUP_CONFIG
#include "startup_config.h"
#ifndef __STARTUP_CONFIG_STACK_ALIGNEMENT
#define __STARTUP_CONFIG_STACK_ALIGNEMENT 3
#endif
#endif
                ENDIF

                IF :DEF: __STARTUP_CONFIG
Stack_Size      EQU __STARTUP_CONFIG_STACK_SIZE
                ELIF :DEF: __STACK_SIZE
Stack_Size      EQU __STACK_SIZE
                ELSE
Stack_Size      EQU 8192
                ENDIF
                
                IF :DEF: __STARTUP_CONFIG
Stack_Align     EQU __STARTUP_CONFIG_STACK_ALIGNEMENT
                ELSE
Stack_Align     EQU 3
                ENDIF

                AREA    STACK, NOINIT, READWRITE, ALIGN=Stack_Align
Stack_Mem       SPACE   Stack_Size
__initial_sp

                IF :DEF: __STARTUP_CONFIG
Heap_Size       EQU __STARTUP_CONFIG_HEAP_SIZE
                ELIF :DEF: __HEAP_SIZE
Heap_Size       EQU __HEAP_SIZE
                ELSE
Heap_Size       EQU 8192
                ENDIF

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB

; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler
                DCD     NMI_Handler
                DCD     HardFault_Handler
                DCD     MemoryManagement_Handler
                DCD     BusFault_Handler
                DCD     UsageFault_Handler
                DCD     SecureFault_Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler
                DCD     DebugMon_Handler
                DCD     0                         ; Reserved
                DCD     PendSV_Handler
                DCD     SysTick_Handler

                ; External Interrupts
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SPU_IRQHandler
                DCD     0                         ; Reserved
                DCD     CLOCK_POWER_IRQHandler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     UARTE0_SPIM0_SPIS0_TWIM0_TWIS0_IRQHandler
                DCD     UARTE1_SPIM1_SPIS1_TWIM1_TWIS1_IRQHandler
                DCD     UARTE2_SPIM2_SPIS2_TWIM2_TWIS2_IRQHandler
                DCD     UARTE3_SPIM3_SPIS3_TWIM3_TWIS3_IRQHandler
                DCD     0                         ; Reserved
                DCD     GPIOTE0_IRQHandler
                DCD     SAADC_IRQHandler
                DCD     TIMER0_IRQHandler
                DCD     TIMER1_IRQHandler
                DCD     TIMER2_IRQHandler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     RTC0_IRQHandler
                DCD     RTC1_IRQHandler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     WDT_IRQHandler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     EGU0_IRQHandler
                DCD     EGU1_IRQHandler
                DCD     EGU2_IRQHandler
                DCD     EGU3_IRQHandler
                DCD     EGU4_IRQHandler
                DCD     EGU5_IRQHandler
                DCD     PWM0_IRQHandler
                DCD     PWM1_IRQHandler
                DCD     PWM2_IRQHandler
                DCD     PWM3_IRQHandler
                DCD     0                         ; Reserved
                DCD     PDM_IRQHandler
                DCD     0                         ; Reserved
                DCD     I2S_IRQHandler
                DCD     0                         ; Reserved
                DCD     IPC_IRQHandler
                DCD     0                         ; Reserved
                DCD     FPU_IRQHandler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     GPIOTE1_IRQHandler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     KMU_IRQHandler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     CRYPTOCELL_IRQHandler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved

__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

; Reset Handler


Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main


                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP

; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemoryManagement_Handler\
                PROC
                EXPORT  MemoryManagement_Handler  [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SecureFault_Handler\
                PROC
                EXPORT  SecureFault_Handler       [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT   SPU_IRQHandler [WEAK]
                EXPORT   CLOCK_POWER_IRQHandler [WEAK]
                EXPORT   UARTE0_SPIM0_SPIS0_TWIM0_TWIS0_IRQHandler [WEAK]
                EXPORT   UARTE1_SPIM1_SPIS1_TWIM1_TWIS1_IRQHandler [WEAK]
                EXPORT   UARTE2_SPIM2_SPIS2_TWIM2_TWIS2_IRQHandler [WEAK]
                EXPORT   UARTE3_SPIM3_SPIS3_TWIM3_TWIS3_IRQHandler [WEAK]
                EXPORT   GPIOTE0_IRQHandler [WEAK]
                EXPORT   SAADC_IRQHandler [WEAK]
                EXPORT   TIMER0_IRQHandler [WEAK]
                EXPORT   TIMER1_IRQHandler [WEAK]
                EXPORT   TIMER2_IRQHandler [WEAK]
                EXPORT   RTC0_IRQHandler [WEAK]
                EXPORT   RTC1_IRQHandler [WEAK]
                EXPORT   WDT_IRQHandler [WEAK]
                EXPORT   EGU0_IRQHandler [WEAK]
                EXPORT   EGU1_IRQHandler [WEAK]
                EXPORT   EGU2_IRQHandler [WEAK]
                EXPORT   EGU3_IRQHandler [WEAK]
                EXPORT   EGU4_IRQHandler [WEAK]
                EXPORT   EGU5_IRQHandler [WEAK]
                EXPORT   PWM0_IRQHandler [WEAK]
                EXPORT   PWM1_IRQHandler [WEAK]
                EXPORT   PWM2_IRQHandler [WEAK]
                EXPORT   PWM3_IRQHandler [WEAK]
                EXPORT   PDM_IRQHandler [WEAK]
                EXPORT   I2S_IRQHandler [WEAK]
                EXPORT   IPC_IRQHandler [WEAK]
                EXPORT   FPU_IRQHandler [WEAK]
                EXPORT   GPIOTE1_IRQHandler [WEAK]
                EXPORT   KMU_IRQHandler [WEAK]
                EXPORT   CRYPTOCELL_IRQHandler [WEAK]
SPU_IRQHandler
CLOCK_POWER_IRQHandler
UARTE0_SPIM0_SPIS0_TWIM0_TWIS0_IRQHandler
UARTE1_SPIM1_SPIS1_TWIM1_TWIS1_IRQHandler
UARTE2_SPIM2_SPIS2_TWIM2_TWIS2_IRQHandler
UARTE3_SPIM3_SPIS3_TWIM3_TWIS3_IRQHandler
GPIOTE0_IRQHandler
SAADC_IRQHandler
TIMER0_IRQHandler
TIMER1_IRQHandler
TIMER2_IRQHandler
RTC0_IRQHandler
RTC1_IRQHandler
WDT_IRQHandler
EGU0_IRQHandler
EGU1_IRQHandler
EGU2_IRQHandler
EGU3_IRQHandler
EGU4_IRQHandler
EGU5_IRQHandler
PWM0_IRQHandler
PWM1_IRQHandler
PWM2_IRQHandler
PWM3_IRQHandler
PDM_IRQHandler
I2S_IRQHandler
IPC_IRQHandler
FPU_IRQHandler
GPIOTE1_IRQHandler
KMU_IRQHandler
CRYPTOCELL_IRQHandler
                B .
                ENDP
                ALIGN

; User Initial Stack & Heap

                IF      :DEF:__MICROLIB

                EXPORT  __initial_sp
                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap

__user_initial_stackheap PROC

                LDR     R0, = Heap_Mem
                LDR     R1, = (Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem + Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDP

                ALIGN

                ENDIF

                END
