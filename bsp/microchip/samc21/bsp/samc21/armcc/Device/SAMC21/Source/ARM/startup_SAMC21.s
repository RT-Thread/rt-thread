;/**************************************************************************//**
; * @file     startup_SAMC21.s
; * @brief    CMSIS Cortex-M0+ Core Device Startup File for
; *           Atmel SAMC21 Device Series
; * @version  V1.0.0
; * @date     10. February 2015
; *
; * @note
; * Copyright (C) 2015 ARM Limited. All rights reserved.
; *
; * @par
; * ARM Limited (ARM) is supplying this software for use with Cortex-M
; * processor based microcontrollers.  This file can be freely distributed
; * within development tools that are supporting such ARM based processors.
; *
; * @par
; * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
; * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
; * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
; * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
; *
; ******************************************************************************/
;/*
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
;*/


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000200

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000000

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

__Vectors       DCD     __initial_sp              ;    Top of Stack
                DCD     Reset_Handler             ;    Reset Handler
                DCD     NMI_Handler               ;    NMI Handler
                DCD     HardFault_Handler         ;    Hard Fault Handler
                DCD     0                         ;    Reserved
                DCD     0                         ;    Reserved
                DCD     0                         ;    Reserved
                DCD     0                         ;    Reserved
                DCD     0                         ;    Reserved
                DCD     0                         ;    Reserved
                DCD     0                         ;    Reserved
                DCD     SVC_Handler               ;    SVCall Handler
                DCD     0                         ;    Reserved
                DCD     0                         ;    Reserved
                DCD     PendSV_Handler            ;    PendSV Handler
                DCD     SysTick_Handler           ;    SysTick Handler

                ; External Interrupts
                DCD     SYSTEM_Handler            ;  0 Main Clock, Oscillators Control, 32k Oscillators Control, Peripheral Access Controller, Power Manager, Supply Controller, Trigger Allocator
                DCD     WDT_Handler               ;  1 Watchdog Timer
                DCD     RTC_Handler               ;  2 Real-Time Counter
                DCD     EIC_Handler               ;  3 External Interrupt Controller
                DCD     FREQM_Handler             ;  4 Frequency Meter
                DCD     TSENS_Handler             ;  5 Temperature Sensor
                DCD     NVMCTRL_Handler           ;  6 Non-Volatile Memory Controller
                DCD     DMAC_Handler              ;  7 Direct Memory Access Controller
                DCD     EVSYS_Handler             ;  8 Event System Interface
                DCD     SERCOM0_Handler           ;  9 Serial Communication Interface 0
                DCD     SERCOM1_Handler           ; 10 Serial Communication Interface 1
                DCD     SERCOM2_Handler           ; 11 Serial Communication Interface 2
                DCD     SERCOM3_Handler           ; 12 Serial Communication Interface 3
                DCD     SERCOM4_Handler           ; 13 Serial Communication Interface 4
                DCD     SERCOM5_Handler           ; 14 Serial Communication Interface 5
                DCD     CAN0_Handler              ; 15 Control Area Network 0
                DCD     CAN1_Handler              ; 16 Control Area Network 1
                DCD     TCC0_Handler              ; 17 Timer Counter Control 0
                DCD     TCC1_Handler              ; 18 Timer Counter Control 1
                DCD     TCC2_Handler              ; 19 Timer Counter Control 2
                DCD     TC0_Handler               ; 20 Basic Timer Counter 0
                DCD     TC1_Handler               ; 21 Basic Timer Counter 1
                DCD     TC2_Handler               ; 22 Basic Timer Counter 2
                DCD     TC3_Handler               ; 23 Basic Timer Counter 3
                DCD     TC4_Handler               ; 24 Basic Timer Counter 4
                DCD     ADC0_Handler              ; 25 Analog Digital Converter 0
                DCD     ADC1_Handler              ; 26 Analog Digital Converter 1
                DCD     AC_Handler                ; 27 Analog Comparators
                DCD     DAC_Handler               ; 28 Digital Analog Converter
                DCD     SDADC_Handler             ; 29 Sigma-Delta Analog Digital Converter
                DCD     PTC_Handler               ; 30 Peripheral Touch Controller
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
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
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
                EXPORT  SYSTEM_Handler            [WEAK]
                EXPORT  WDT_Handler               [WEAK]
                EXPORT  RTC_Handler               [WEAK]
                EXPORT  EIC_Handler               [WEAK]
                EXPORT  FREQM_Handler             [WEAK]
                EXPORT  TSENS_Handler             [WEAK]
                EXPORT  NVMCTRL_Handler           [WEAK]
                EXPORT  DMAC_Handler              [WEAK]
                EXPORT  EVSYS_Handler             [WEAK]
                EXPORT  SERCOM0_Handler           [WEAK]
                EXPORT  SERCOM1_Handler           [WEAK]
                EXPORT  SERCOM2_Handler           [WEAK]
                EXPORT  SERCOM3_Handler           [WEAK]
                EXPORT  SERCOM4_Handler           [WEAK]
                EXPORT  SERCOM5_Handler           [WEAK]
                EXPORT  CAN0_Handler              [WEAK]
                EXPORT  CAN1_Handler              [WEAK]
                EXPORT  TCC0_Handler              [WEAK]
                EXPORT  TCC1_Handler              [WEAK]
                EXPORT  TCC2_Handler              [WEAK]
                EXPORT  TC0_Handler               [WEAK]
                EXPORT  TC1_Handler               [WEAK]
                EXPORT  TC2_Handler               [WEAK]
                EXPORT  TC3_Handler               [WEAK]
                EXPORT  TC4_Handler               [WEAK]
                EXPORT  ADC0_Handler              [WEAK]
                EXPORT  ADC1_Handler              [WEAK]
                EXPORT  AC_Handler                [WEAK]
                EXPORT  DAC_Handler               [WEAK]
                EXPORT  SDADC_Handler             [WEAK]
                EXPORT  PTC_Handler               [WEAK]

SYSTEM_Handler
WDT_Handler
RTC_Handler
EIC_Handler
FREQM_Handler
TSENS_Handler
NVMCTRL_Handler
DMAC_Handler
EVSYS_Handler
SERCOM0_Handler
SERCOM1_Handler
SERCOM2_Handler
SERCOM3_Handler
SERCOM4_Handler
SERCOM5_Handler
CAN0_Handler
CAN1_Handler
TCC0_Handler
TCC1_Handler
TCC2_Handler
TC0_Handler
TC1_Handler
TC2_Handler
TC3_Handler
TC4_Handler
ADC0_Handler
ADC1_Handler
AC_Handler
DAC_Handler
SDADC_Handler
PTC_Handler
                B       .
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
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF


                END
