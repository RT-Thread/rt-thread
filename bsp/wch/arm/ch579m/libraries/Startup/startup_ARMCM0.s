;/**************************************************************************//**
; * @file     startup_ARMCM0.s
; * @brief    CMSIS Core Device Startup File for
; *           ARMCM0 Device Series
; * @version  V1.08
; * @date     23. November 2012
; *
; * @note
; *
; ******************************************************************************/
;/* Copyright (c) 2011 - 2012 ARM LIMITED
;
;   All rights reserved.
;   Redistribution and use in source and binary forms, with or without
;   modification, are permitted provided that the following conditions are met:
;   - Redistributions of source code must retain the above copyright
;     notice, this list of conditions and the following disclaimer.
;   - Redistributions in binary form must reproduce the above copyright
;     notice, this list of conditions and the following disclaimer in the
;     documentation and/or other materials provided with the distribution.
;   - Neither the name of ARM nor the names of its contributors may be used
;     to endorse or promote products derived from this software without
;     specific prior written permission.
;   *
;   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
;   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
;   IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
;   ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
;   LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
;   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
;   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
;   INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
;   CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
;   ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
;   POSSIBILITY OF SUCH DAMAGE.
;   ---------------------------------------------------------------------------*/
;/*
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
;*/


; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp    EQU     0x20008000


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x00000400

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
                DCD     Reset_Handler             ; Reset Handler
                DCD     NMI_Handler               ; NMI Handler
                DCD     HardFault_Handler         ; Hard Fault Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     SVC_Handler               ; SVCall Handler
                DCD     0                         ; Reserved
                DCD     0                         ; Reserved
                DCD     PendSV_Handler            ; PendSV Handler
                DCD     SysTick_Handler           ; SysTick Handler

                ; External Interrupts
                DCD     TMR0_IRQHandler           ;  0:  TMR0
                DCD     GPIO_IRQHandler           ;  1:  GPIO
                DCD     SLAVE_IRQHandler          ;  2:  SLAVE
                DCD     SPI0_IRQHandler           ;  3:  SPI0
                DCD     BB_IRQHandler             ;  4:  BB
                DCD     LLE_IRQHandler            ;  5:  LLE
                DCD     USB_IRQHandler            ;  6:  USB
                DCD     ETH_IRQHandler            ;  7:  ETH
                DCD     TMR1_IRQHandler           ;  8:  TMR1
                DCD     TMR2_IRQHandler           ;  9:  TMR2
                DCD     UART0_IRQHandler          ; 10:  UART0
                DCD     UART1_IRQHandler          ; 11:  UART1
                DCD     RTC_IRQHandler            ; 12:  RTC
                DCD     ADC_IRQHandler            ; 13:  ADC
                DCD     SPI1_IRQHandler           ; 14:  SPI1
                DCD     LED_IRQHandler            ; 15:  LED
                DCD     TMR3_IRQHandler           ; 16:  TMR3 
                DCD     UART2_IRQHandler          ; 17:  UART2
                DCD     UART3_IRQHandler          ; 18:  UART3
                DCD     WDT_IRQHandler            ; 19:  WDT
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
				;LDR     R0, =0x1007058	
				;MOV     SP, R0
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
;                B       .
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

                EXPORT     TMR0_IRQHandler           [WEAK];  0:  TMR0
                EXPORT     GPIO_IRQHandler           [WEAK];  1:  GPIO
                EXPORT     SLAVE_IRQHandler          [WEAK];  2:  SLAVE
                EXPORT     SPI0_IRQHandler           [WEAK];  3:  SPI0
                EXPORT     BB_IRQHandler             [WEAK];  4:  BB
                EXPORT     LLE_IRQHandler            [WEAK];  5:  LLE
                EXPORT     USB_IRQHandler            [WEAK];  6:  USB
                EXPORT     ETH_IRQHandler            [WEAK];  7:  ETH
                EXPORT     TMR1_IRQHandler           [WEAK];  8:  TMR1
                EXPORT     TMR2_IRQHandler           [WEAK];  9:  TMR2
                EXPORT     UART0_IRQHandler          [WEAK]; 10:  UART0
                EXPORT     UART1_IRQHandler          [WEAK]; 11:  UART1
                EXPORT     RTC_IRQHandler            [WEAK]; 12:  RTC
                EXPORT     ADC_IRQHandler            [WEAK]; 13:  ADC
                EXPORT     SPI1_IRQHandler           [WEAK]; 14:  SPI1
                EXPORT     LED_IRQHandler            [WEAK]; 15:  LED
                EXPORT     TMR3_IRQHandler           [WEAK]; 16:  TMR3 
                EXPORT     UART2_IRQHandler          [WEAK]; 17:  UART2
                EXPORT     UART3_IRQHandler          [WEAK]; 18:  UART3
                EXPORT     WDT_IRQHandler            [WEAK]; 19:  WDT

TMR0_IRQHandler           ;  0:  TMR0
GPIO_IRQHandler           ;  1:  GPIO
SLAVE_IRQHandler          ;  2:  SLAVE
SPI0_IRQHandler           ;  3:  SPI0
BB_IRQHandler             ;  4:  BB
LLE_IRQHandler            ;  5:  LLE
USB_IRQHandler            ;  6:  USB
ETH_IRQHandler            ;  7:  ETH
TMR1_IRQHandler           ;  8:  TMR1
TMR2_IRQHandler           ;  9:  TMR2
UART0_IRQHandler          ; 10:  UART0
UART1_IRQHandler          ; 11:  UART1
RTC_IRQHandler            ; 12:  RTC
ADC_IRQHandler            ; 13:  ADC
SPI1_IRQHandler           ; 14:  SPI1
LED_IRQHandler            ; 15:  LED
TMR3_IRQHandler           ; 16:  TMR3 
UART2_IRQHandler          ; 17:  UART2
UART3_IRQHandler          ; 18:  UART3
WDT_IRQHandler            ; 19:  WDT
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

__user_initial_stackheap PROC
                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDP

                ALIGN

                ENDIF


                END
