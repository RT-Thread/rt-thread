;/*!
;    \file    startup_gd32f10x_xd.s
;    \brief   start up file
;
;    \version 2014-12-26, V1.0.0, firmware for GD32F10x
;    \version 2017-06-20, V2.0.0, firmware for GD32F10x
;    \version 2018-07-31, V2.1.0, firmware for GD32F10x
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

Stack_Size          EQU     0x00002000

                    AREA    STACK, NOINIT, READWRITE, ALIGN = 3
Stack_Mem           SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size           EQU     0x00002000

                    AREA    HEAP, NOINIT, READWRITE, ALIGN = 3
__heap_base
Heap_Mem            SPACE   Heap_Size
__heap_limit


                    PRESERVE8
                    THUMB

;                   /* reset Vector Mapped to at Address 0 */
                    AREA    RESET, DATA, READONLY
                    EXPORT  __Vectors
                    EXPORT  __Vectors_End
                    EXPORT  __Vectors_Size

__Vectors           DCD     __initial_sp                      ; Top of Stack
                    DCD     Reset_Handler                     ; Reset Handler
                    DCD     NMI_Handler                       ; NMI Handler
                    DCD     HardFault_Handler                 ; Hard Fault Handler
                    DCD     MemManage_Handler                 ; MPU Fault Handler
                    DCD     BusFault_Handler                  ; Bus Fault Handler
                    DCD     UsageFault_Handler                ; Usage Fault Handler
                    DCD     0                                 ; Reserved
                    DCD     0                                 ; Reserved
                    DCD     0                                 ; Reserved
                    DCD     0                                 ; Reserved
                    DCD     SVC_Handler                       ; SVCall Handler
                    DCD     DebugMon_Handler                  ; Debug Monitor Handler
                    DCD     0                                 ; Reserved
                    DCD     PendSV_Handler                    ; PendSV Handler
                    DCD     SysTick_Handler                   ; SysTick Handler

;                   /* external interrupts handler */
                    DCD     WWDGT_IRQHandler                  ; 16:Window Watchdog Timer
                    DCD     LVD_IRQHandler                    ; 17:LVD through EXTI Line detect
                    DCD     TAMPER_IRQHandler                 ; 18:Tamper Interrupt   
                    DCD     RTC_IRQHandler                    ; 19:RTC through EXTI Line
                    DCD     FMC_IRQHandler                    ; 20:FMC
                    DCD     RCU_IRQHandler                    ; 21:RCU
                    DCD     EXTI0_IRQHandler                  ; 22:EXTI Line 0
                    DCD     EXTI1_IRQHandler                  ; 23:EXTI Line 1
                    DCD     EXTI2_IRQHandler                  ; 24:EXTI Line 2
                    DCD     EXTI3_IRQHandler                  ; 25:EXTI Line 3
                    DCD     EXTI4_IRQHandler                  ; 26:EXTI Line 4
                    DCD     DMA0_Channel0_IRQHandler          ; 27:DMA0 Channel 0
                    DCD     DMA0_Channel1_IRQHandler          ; 28:DMA0 Channel 1
                    DCD     DMA0_Channel2_IRQHandler          ; 29:DMA0 Channel 2
                    DCD     DMA0_Channel3_IRQHandler          ; 30:DMA0 Channel 3
                    DCD     DMA0_Channel4_IRQHandler          ; 31:DMA0 Channel 4
                    DCD     DMA0_Channel5_IRQHandler          ; 32:DMA0 Channel 5 
                    DCD     DMA0_Channel6_IRQHandler          ; 33:DMA0 Channel 6
                    DCD     ADC0_1_IRQHandler                 ; 34:ADC0 and ADC1
                    DCD     USBD_HP_CAN0_TX_IRQHandler        ; 35:USBD and CAN0 TX
                    DCD     USBD_LP_CAN0_RX0_IRQHandler       ; 36:USBD and CAN0 RX0
                    DCD     CAN0_RX1_IRQHandler               ; 37:CAN0 RX1
                    DCD     CAN0_EWMC_IRQHandler              ; 38:CAN0 EWMC
                    DCD     EXTI5_9_IRQHandler                ; 39:EXTI Line 5 to EXTI Line 9
                    DCD     TIMER0_BRK_TIMER8_IRQHandler      ; 40:TIMER0 Break and TIMER8 global
                    DCD     TIMER0_UP_TIMER9_IRQHandler       ; 41:TIMER0 Update and TIMER9 global
                    DCD     TIMER0_TRG_CMT_TIMER10_IRQHandler ; 42:TIMER0 Trigger and Commutation and TIMER10 global
                    DCD     TIMER0_Channel_IRQHandler         ; 43:TIMER0 Channel Capture Compare
                    DCD     TIMER1_IRQHandler                 ; 44:TIMER1
                    DCD     TIMER2_IRQHandler                 ; 45:TIMER2
                    DCD     TIMER3_IRQHandler                 ; 46:TIMER3
                    DCD     I2C0_EV_IRQHandler                ; 47:I2C0 Event
                    DCD     I2C0_ER_IRQHandler                ; 48:I2C0 Error
                    DCD     I2C1_EV_IRQHandler                ; 49:I2C1 Event
                    DCD     I2C1_ER_IRQHandler                ; 50:I2C1 Error
                    DCD     SPI0_IRQHandler                   ; 51:SPI0
                    DCD     SPI1_IRQHandler                   ; 52:SPI1
                    DCD     USART0_IRQHandler                 ; 53:USART0
                    DCD     USART1_IRQHandler                 ; 54:USART1
                    DCD     USART2_IRQHandler                 ; 55:USART2
                    DCD     EXTI10_15_IRQHandler              ; 56:EXTI Line 10 to EXTI Line 15
                    DCD     RTC_Alarm_IRQHandler              ; 57:RTC Alarm through EXTI Line
                    DCD     USBD_WKUP_IRQHandler              ; 58:USBD WakeUp from suspend through EXTI Line
                    DCD     TIMER7_BRK_TIMER11_IRQHandler     ; 59:TIMER7 Break Interrupt and TIMER11 global
                    DCD     TIMER7_UP_TIMER12_IRQHandler      ; 60:TIMER7 Update Interrupt and TIMER12 global
                    DCD     TIMER7_TRG_CMT_TIMER13_IRQHandler ; 61:TIMER7 Trigger and Commutation Interrupt and TIMER13 global
                    DCD     TIMER7_Channel_IRQHandler         ; 62:TIMER7 Channel Capture Compare 
                    DCD     ADC2_IRQHandler                   ; 63:ADC2
                    DCD     EXMC_IRQHandler                   ; 64:EXMC
                    DCD     SDIO_IRQHandler                   ; 65:SDIO
                    DCD     TIMER4_IRQHandler                 ; 66:TIMER4
                    DCD     SPI2_IRQHandler                   ; 67:SPI2
                    DCD     UART3_IRQHandler                  ; 68:UART3
                    DCD     UART4_IRQHandler                  ; 69:UART4
                    DCD     TIMER5_IRQHandler                 ; 70:TIMER5
                    DCD     TIMER6_IRQHandler                 ; 71:TIMER6
                    DCD     DMA1_Channel0_IRQHandler          ; 72:DMA1 Channel0
                    DCD     DMA1_Channel1_IRQHandler          ; 73:DMA1 Channel1
                    DCD     DMA1_Channel2_IRQHandler          ; 74:DMA1 Channel2
                    DCD     DMA1_Channel3_4_IRQHandler        ; 75:DMA1 Channel3 and Channel4

__Vectors_End

__Vectors_Size      EQU  __Vectors_End - __Vectors

                    AREA    |.text|, CODE, READONLY

;/* reset Handler */
Reset_Handler       PROC
                    EXPORT  Reset_Handler                     [WEAK]
                    IMPORT  __main
                    IMPORT  SystemInit  
                    LDR     R0, =SystemInit
                    BLX     R0
                    LDR     R0, =__main
                    BX      R0
                    ENDP

;/* dummy Exception Handlers */
NMI_Handler         PROC
                    EXPORT  NMI_Handler                         [WEAK]
                    B       .
                    ENDP

HardFault_Handler   PROC
                    EXPORT  HardFault_Handler                   [WEAK]
                    B       .
                    ENDP

MemManage_Handler   PROC
                    EXPORT  MemManage_Handler                   [WEAK]
                    B       .
                    ENDP

BusFault_Handler    PROC
                    EXPORT  BusFault_Handler                    [WEAK]
                    B       .
                    ENDP

UsageFault_Handler  PROC
                    EXPORT  UsageFault_Handler                  [WEAK]
                    B       .
                    ENDP

SVC_Handler         PROC
                    EXPORT  SVC_Handler                         [WEAK]
                    B       .
                    ENDP

DebugMon_Handler    PROC
                    EXPORT  DebugMon_Handler                    [WEAK]
                    B       .
                    ENDP

PendSV_Handler      PROC
                    EXPORT  PendSV_Handler                      [WEAK]
                    B       .
                    ENDP

SysTick_Handler     PROC
                    EXPORT  SysTick_Handler                     [WEAK]
                    B       .
                    ENDP

Default_Handler     PROC
;                   /* external interrupts handler */    
                    EXPORT  WWDGT_IRQHandler                    [WEAK]
                    EXPORT  LVD_IRQHandler                      [WEAK]
                    EXPORT  TAMPER_IRQHandler                   [WEAK]
                    EXPORT  RTC_IRQHandler                      [WEAK]
                    EXPORT  FMC_IRQHandler                      [WEAK]
                    EXPORT  RCU_IRQHandler                      [WEAK]
                    EXPORT  EXTI0_IRQHandler                    [WEAK]
                    EXPORT  EXTI1_IRQHandler                    [WEAK]
                    EXPORT  EXTI2_IRQHandler                    [WEAK]
                    EXPORT  EXTI3_IRQHandler                    [WEAK]
                    EXPORT  EXTI4_IRQHandler                    [WEAK]
                    EXPORT  DMA0_Channel0_IRQHandler            [WEAK]
                    EXPORT  DMA0_Channel1_IRQHandler            [WEAK]
                    EXPORT  DMA0_Channel2_IRQHandler            [WEAK]
                    EXPORT  DMA0_Channel3_IRQHandler            [WEAK]
                    EXPORT  DMA0_Channel4_IRQHandler            [WEAK]
                    EXPORT  DMA0_Channel5_IRQHandler            [WEAK]
                    EXPORT  DMA0_Channel6_IRQHandler            [WEAK]
                    EXPORT  ADC0_1_IRQHandler                   [WEAK]
                    EXPORT  USBD_HP_CAN0_TX_IRQHandler          [WEAK]
                    EXPORT  USBD_LP_CAN0_RX0_IRQHandler         [WEAK]
                    EXPORT  CAN0_RX1_IRQHandler                 [WEAK]
                    EXPORT  CAN0_EWMC_IRQHandler                [WEAK]
                    EXPORT  EXTI5_9_IRQHandler                  [WEAK]
                    EXPORT  TIMER0_BRK_TIMER8_IRQHandler        [WEAK]
                    EXPORT  TIMER0_UP_TIMER9_IRQHandler         [WEAK]
                    EXPORT  TIMER0_TRG_CMT_TIMER10_IRQHandler   [WEAK]
                    EXPORT  TIMER0_Channel_IRQHandler           [WEAK]
                    EXPORT  TIMER1_IRQHandler                   [WEAK]
                    EXPORT  TIMER2_IRQHandler                   [WEAK]
                    EXPORT  TIMER3_IRQHandler                   [WEAK]
                    EXPORT  I2C0_EV_IRQHandler                  [WEAK]
                    EXPORT  I2C0_ER_IRQHandler                  [WEAK]
                    EXPORT  I2C1_EV_IRQHandler                  [WEAK]
                    EXPORT  I2C1_ER_IRQHandler                  [WEAK]
                    EXPORT  SPI0_IRQHandler                     [WEAK]
                    EXPORT  SPI1_IRQHandler                     [WEAK]
                    EXPORT  USART0_IRQHandler                   [WEAK]
                    EXPORT  USART1_IRQHandler                   [WEAK]
                    EXPORT  USART2_IRQHandler                   [WEAK]
                    EXPORT  EXTI10_15_IRQHandler                [WEAK]
                    EXPORT  RTC_Alarm_IRQHandler                [WEAK]
                    EXPORT  USBD_WKUP_IRQHandler                [WEAK]
                    EXPORT  TIMER7_BRK_TIMER11_IRQHandler       [WEAK]
                    EXPORT  TIMER7_UP_TIMER12_IRQHandler        [WEAK]
                    EXPORT  TIMER7_TRG_CMT_TIMER13_IRQHandler   [WEAK]
                    EXPORT  TIMER7_Channel_IRQHandler           [WEAK]
                    EXPORT  ADC2_IRQHandler                     [WEAK]
                    EXPORT  EXMC_IRQHandler                     [WEAK]
                    EXPORT  SDIO_IRQHandler                     [WEAK]
                    EXPORT  TIMER4_IRQHandler                   [WEAK]
                    EXPORT  SPI2_IRQHandler                     [WEAK]
                    EXPORT  UART3_IRQHandler                    [WEAK]
                    EXPORT  UART4_IRQHandler                    [WEAK]
                    EXPORT  TIMER5_IRQHandler                   [WEAK]
                    EXPORT  TIMER6_IRQHandler                   [WEAK]
                    EXPORT  DMA1_Channel0_IRQHandler            [WEAK]
                    EXPORT  DMA1_Channel1_IRQHandler            [WEAK]
                    EXPORT  DMA1_Channel2_IRQHandler            [WEAK]
                    EXPORT  DMA1_Channel3_4_IRQHandler          [WEAK]
   

;/* external interrupts handler */
WWDGT_IRQHandler
LVD_IRQHandler
TAMPER_IRQHandler
RTC_IRQHandler
FMC_IRQHandler 
RCU_IRQHandler
EXTI0_IRQHandler
EXTI1_IRQHandler
EXTI2_IRQHandler
EXTI3_IRQHandler
EXTI4_IRQHandler
DMA0_Channel0_IRQHandler
DMA0_Channel1_IRQHandler
DMA0_Channel2_IRQHandler
DMA0_Channel3_IRQHandler
DMA0_Channel4_IRQHandler
DMA0_Channel5_IRQHandler
DMA0_Channel6_IRQHandler
ADC0_1_IRQHandler
USBD_HP_CAN0_TX_IRQHandler
USBD_LP_CAN0_RX0_IRQHandler
CAN0_RX1_IRQHandler
CAN0_EWMC_IRQHandler
EXTI5_9_IRQHandler
TIMER0_BRK_TIMER8_IRQHandler
TIMER0_UP_TIMER9_IRQHandler
TIMER0_TRG_CMT_TIMER10_IRQHandler
TIMER0_Channel_IRQHandler
TIMER1_IRQHandler
TIMER2_IRQHandler
TIMER3_IRQHandler
I2C0_EV_IRQHandler
I2C0_ER_IRQHandler
I2C1_EV_IRQHandler
I2C1_ER_IRQHandler
SPI0_IRQHandler
SPI1_IRQHandler
USART0_IRQHandler
USART1_IRQHandler
USART2_IRQHandler
EXTI10_15_IRQHandler
RTC_Alarm_IRQHandler
USBD_WKUP_IRQHandler
TIMER7_BRK_TIMER11_IRQHandler
TIMER7_UP_TIMER12_IRQHandler
TIMER7_TRG_CMT_TIMER13_IRQHandler
TIMER7_Channel_IRQHandler
ADC2_IRQHandler
EXMC_IRQHandler
SDIO_IRQHandler
TIMER4_IRQHandler
SPI2_IRQHandler
UART3_IRQHandler
UART4_IRQHandler
TIMER5_IRQHandler
TIMER6_IRQHandler
DMA1_Channel0_IRQHandler
DMA1_Channel1_IRQHandler
DMA1_Channel2_IRQHandler
DMA1_Channel3_4_IRQHandler



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
