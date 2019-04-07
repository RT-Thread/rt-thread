;/*!
;    \file    startup_gd32e230.s
;    \brief   start up file
;
;    \version 2018-6-19, V1.0.0, firmware for GD32E230
;*/
;
;/*
;    Copyright (c) 2018, GigaDevice Semiconductor Inc.
;
;    All rights reserved.
;
;    Redistribution and use in source and binary forms, with or without modification, 
;are permitted provided that the following conditions are met:
;
;    1. Redistributions of source code must retain the above copyright notice, this 
;       list of conditions and the following disclaimer.
;    2. Redistributions in binary form must reproduce the above copyright notice, 
;       this list of conditions and the following disclaimer in the documentation 
;       and/or other materials provided with the distribution.
;    3. Neither the name of the copyright holder nor the names of its contributors 
;       may be used to endorse or promote products derived from this software without 
;       specific prior written permission.
;
;    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
;AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
;WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
;IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
;INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT 
;NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR 
;PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
;WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
;ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
;OF SUCH DAMAGE.
;*/

; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000400

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


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

;               /* reset Vector Mapped to at Address 0 */
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp                      ; Top of Stack
                DCD     Reset_Handler                     ; Reset Handler
                DCD     NMI_Handler                       ; NMI Handler
                DCD     HardFault_Handler                 ; Hard Fault Handler
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     SVC_Handler                       ; SVCall Handler
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     PendSV_Handler                    ; PendSV Handler
                DCD     SysTick_Handler                   ; SysTick Handler

;               /* external interrupts handler */
                DCD     WWDGT_IRQHandler                  ; 16:Window Watchdog Timer
                DCD     LVD_IRQHandler                    ; 17:LVD through EXTI Line detect
                DCD     RTC_IRQHandler                    ; 18:RTC through EXTI Line
                DCD     FMC_IRQHandler                    ; 19:FMC
                DCD     RCU_IRQHandler                    ; 20:RCU
                DCD     EXTI0_1_IRQHandler                ; 21:EXTI Line 0 and EXTI Line 1
                DCD     EXTI2_3_IRQHandler                ; 22:EXTI Line 2 and EXTI Line 3
                DCD     EXTI4_15_IRQHandler               ; 23:EXTI Line 4 to EXTI Line 15
                DCD     0                                 ; Reserved
                DCD     DMA_Channel0_IRQHandler           ; 25:DMA Channel 0 
                DCD     DMA_Channel1_2_IRQHandler         ; 26:DMA Channel 1 and DMA Channel 2
                DCD     DMA_Channel3_4_IRQHandler         ; 27:DMA Channel 3 and DMA Channel 4
                DCD     ADC_CMP_IRQHandler                ; 28:ADC and Comparator
                DCD     TIMER0_BRK_UP_TRG_COM_IRQHandler  ; 29:TIMER0 Break,Update,Trigger and Commutation
                DCD     TIMER0_Channel_IRQHandler         ; 30:TIMER0 Channel Capture Compare
                DCD     0                                 ; Reserved
                DCD     TIMER2_IRQHandler                 ; 32:TIMER2
                DCD     TIMER5_IRQHandler                 ; 33:TIMER5
                DCD     0                                 ; Reserved
                DCD     TIMER13_IRQHandler                ; 35:TIMER13
                DCD     TIMER14_IRQHandler                ; 36:TIMER14
                DCD     TIMER15_IRQHandler                ; 37:TIMER15
                DCD     TIMER16_IRQHandler                ; 38:TIMER16
                DCD     I2C0_EV_IRQHandler                ; 39:I2C0 Event
                DCD     I2C1_EV_IRQHandler                ; 40:I2C1 Event
                DCD     SPI0_IRQHandler                   ; 41:SPI0
                DCD     SPI1_IRQHandler                   ; 42:SPI1
                DCD     USART0_IRQHandler                 ; 43:USART0
                DCD     USART1_IRQHandler                 ; 44:USART1
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     0                                 ; Reserved
                DCD     I2C0_ER_IRQHandler                ; 48:I2C0 Error
                DCD     0                                 ; Reserved
                DCD     I2C1_ER_IRQHandler                ; 50:I2C1 Error
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

;/* reset Handler */
Reset_Handler   PROC
                EXPORT  Reset_Handler                     [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP

;/* dummy Exception Handlers */
NMI_Handler\
                PROC
                EXPORT  NMI_Handler                       [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler                 [WEAK]
                B       .
                ENDP
SVC_Handler\
                PROC
                EXPORT  SVC_Handler                       [WEAK]
                B       .
                ENDP
PendSV_Handler\
                PROC
                EXPORT  PendSV_Handler                    [WEAK]
                B       .
                ENDP
SysTick_Handler\
                PROC
                EXPORT  SysTick_Handler                   [WEAK]
                B       .
                ENDP

Default_Handler PROC
;               /* external interrupts handler */
                EXPORT  WWDGT_IRQHandler                  [WEAK]
                EXPORT  LVD_IRQHandler                    [WEAK]
                EXPORT  RTC_IRQHandler                    [WEAK]
                EXPORT  FMC_IRQHandler                    [WEAK]
                EXPORT  RCU_IRQHandler                    [WEAK]
                EXPORT  EXTI0_1_IRQHandler                [WEAK]
                EXPORT  EXTI2_3_IRQHandler                [WEAK]
                EXPORT  EXTI4_15_IRQHandler               [WEAK]
                EXPORT  DMA_Channel0_IRQHandler           [WEAK]
                EXPORT  DMA_Channel1_2_IRQHandler         [WEAK]
                EXPORT  DMA_Channel3_4_IRQHandler         [WEAK]
                EXPORT  ADC_CMP_IRQHandler                [WEAK]
                EXPORT  TIMER0_BRK_UP_TRG_COM_IRQHandler  [WEAK]
                EXPORT  TIMER0_Channel_IRQHandler         [WEAK]
                EXPORT  TIMER2_IRQHandler                 [WEAK]
                EXPORT  TIMER5_IRQHandler                 [WEAK]
                EXPORT  TIMER13_IRQHandler                [WEAK]
                EXPORT  TIMER14_IRQHandler                [WEAK]
                EXPORT  TIMER15_IRQHandler                [WEAK]
                EXPORT  TIMER16_IRQHandler                [WEAK]
                EXPORT  I2C0_EV_IRQHandler                [WEAK]
                EXPORT  I2C1_EV_IRQHandler                [WEAK]
                EXPORT  SPI0_IRQHandler                   [WEAK]
                EXPORT  SPI1_IRQHandler                   [WEAK]
                EXPORT  USART0_IRQHandler                 [WEAK]
                EXPORT  USART1_IRQHandler                 [WEAK]
                EXPORT  I2C0_ER_IRQHandler                [WEAK]
                EXPORT  I2C1_ER_IRQHandler                [WEAK]

;/* external interrupts handler */
WWDGT_IRQHandler
LVD_IRQHandler
RTC_IRQHandler
FMC_IRQHandler
RCU_IRQHandler
EXTI0_1_IRQHandler
EXTI2_3_IRQHandler
EXTI4_15_IRQHandler
DMA_Channel0_IRQHandler
DMA_Channel1_2_IRQHandler
DMA_Channel3_4_IRQHandler
ADC_CMP_IRQHandler
TIMER0_BRK_UP_TRG_COM_IRQHandler
TIMER0_Channel_IRQHandler
TIMER2_IRQHandler
TIMER5_IRQHandler
TIMER13_IRQHandler
TIMER14_IRQHandler
TIMER15_IRQHandler
TIMER16_IRQHandler
I2C0_EV_IRQHandler
I2C1_EV_IRQHandler
SPI0_IRQHandler
SPI1_IRQHandler
USART0_IRQHandler
USART1_IRQHandler
I2C0_ER_IRQHandler
I2C1_ER_IRQHandler

                B       .
                ENDP

                ALIGN

; user Initial Stack & Heap

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
