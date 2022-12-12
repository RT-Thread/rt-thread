;/*!
;    \file    startup_gd32f10x_hd.s
;    \brief   start up file
;
;    \version 2014-12-26, V1.0.0, firmware for GD32F10x
;    \version 2017-06-20, V2.0.0, firmware for GD32F10x
;    \version 2018-07-31, V2.1.0, firmware for GD32F10x
;    \version 2020-09-30, V2.2.0, firmware for GD32F10x
;*/

;/*
    ;Copyright (c) 2020, GigaDevice Semiconductor Inc.

    ;Redistribution and use in source and binary forms, with or without modification, 
;are permitted provided that the following conditions are met:

    ;1. Redistributions of source code must retain the above copyright notice, this 
       ;list of conditions and the following disclaimer.
    ;2. Redistributions in binary form must reproduce the above copyright notice, 
       ;this list of conditions and the following disclaimer in the documentation 
       ;and/or other materials provided with the distribution.
    ;3. Neither the name of the copyright holder nor the names of its contributors 
       ;may be used to endorse or promote products derived from this software without 
       ;specific prior written permission.

    ;THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
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

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table

        DATA
__vector_table
        DCD     sfe(CSTACK)                       ; top of stack
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
                                                  
        ; External Interrupts                     
        DCD     WWDGT_IRQHandler                  ; Vector Number 16,Window Watchdog Timer
        DCD     LVD_IRQHandler                    ; Vector Number 17,LVD through EXTI Line detect
        DCD     TAMPER_IRQHandler                 ; Vector Number 18,Tamper Interrupt   
        DCD     RTC_IRQHandler                    ; Vector Number 19,RTC through EXTI Line
        DCD     FMC_IRQHandler                    ; Vector Number 20,FMC
        DCD     RCU_IRQHandler                    ; Vector Number 21,RCU
        DCD     EXTI0_IRQHandler                  ; Vector Number 22,EXTI Line 0
        DCD     EXTI1_IRQHandler                  ; Vector Number 23,EXTI Line 1
        DCD     EXTI2_IRQHandler                  ; Vector Number 24,EXTI Line 2
        DCD     EXTI3_IRQHandler                  ; Vector Number 25,EXTI Line 3
        DCD     EXTI4_IRQHandler                  ; Vector Number 26,EXTI Line 4
        DCD     DMA0_Channel0_IRQHandler          ; Vector Number 27,DMA0 Channel 0
        DCD     DMA0_Channel1_IRQHandler          ; Vector Number 28,DMA0 Channel 1
        DCD     DMA0_Channel2_IRQHandler          ; Vector Number 29,DMA0 Channel 2
        DCD     DMA0_Channel3_IRQHandler          ; Vector Number 30,DMA0 Channel 3
        DCD     DMA0_Channel4_IRQHandler          ; Vector Number 31,DMA0 Channel 4
        DCD     DMA0_Channel5_IRQHandler          ; Vector Number 32,DMA0 Channel 5 
        DCD     DMA0_Channel6_IRQHandler          ; Vector Number 33,DMA0 Channel 6
        DCD     ADC0_1_IRQHandler                 ; Vector Number 34,ADC0 and ADC1
        DCD     USBD_HP_CAN0_TX_IRQHandler        ; Vector Number 35,USBD and CAN0 TX
        DCD     USBD_LP_CAN0_RX0_IRQHandler       ; Vector Number 36,USBD and CAN0 RX0
        DCD     CAN0_RX1_IRQHandler               ; Vector Number 37,CAN0 RX1
        DCD     CAN0_EWMC_IRQHandler              ; Vector Number 38,CAN0 EWMC
        DCD     EXTI5_9_IRQHandler                ; Vector Number 39,EXTI Line 5 to EXTI Line 9
        DCD     TIMER0_BRK_IRQHandler             ; Vector Number 40,TIMER0 Break
        DCD     TIMER0_UP_IRQHandler              ; Vector Number 41,TIMER0 Update
        DCD     TIMER0_TRG_CMT_IRQHandler         ; Vector Number 42,TIMER0 Trigger and Commutation
        DCD     TIMER0_Channel_IRQHandler         ; Vector Number 43,TIMER0 Channel Capture Compare
        DCD     TIMER1_IRQHandler                 ; Vector Number 44,TIMER1
        DCD     TIMER2_IRQHandler                 ; Vector Number 45,TIMER2
        DCD     TIMER3_IRQHandler                 ; Vector Number 46,TIMER3
        DCD     I2C0_EV_IRQHandler                ; Vector Number 47,I2C0 Event
        DCD     I2C0_ER_IRQHandler                ; Vector Number 48,I2C0 Error
        DCD     I2C1_EV_IRQHandler                ; Vector Number 49,I2C1 Event
        DCD     I2C1_ER_IRQHandler                ; Vector Number 50,I2C1 Error
        DCD     SPI0_IRQHandler                   ; Vector Number 51,SPI0
        DCD     SPI1_IRQHandler                   ; Vector Number 52,SPI1
        DCD     USART0_IRQHandler                 ; Vector Number 53,USART0
        DCD     USART1_IRQHandler                 ; Vector Number 54,USART1
        DCD     USART2_IRQHandler                 ; Vector Number 55,USART2
        DCD     EXTI10_15_IRQHandler              ; Vector Number 56,EXTI Line 10 to EXTI Line 15
        DCD     RTC_Alarm_IRQHandler              ; Vector Number 57,RTC Alarm through EXTI Line
        DCD     USBD_WKUP_IRQHandler              ; Vector Number 58,USBD WakeUp from suspend through EXTI Line
        DCD     TIMER7_BRK_IRQHandler             ; Vector Number 59,TIMER7 Break Interrupt
        DCD     TIMER7_UP_IRQHandler              ; Vector Number 60,TIMER7 Update Interrupt
        DCD     TIMER7_TRG_CMT_IRQHandler         ; Vector Number 61,TIMER7 Trigger and Commutation Interrupt
        DCD     TIMER7_Channel_IRQHandler         ; Vector Number 62,TIMER7 Channel Capture Compare 
        DCD     ADC2_IRQHandler                   ; Vector Number 63,ADC2
        DCD     EXMC_IRQHandler                   ; Vector Number 64,EXMC
        DCD     SDIO_IRQHandler                   ; Vector Number 65,SDIO
        DCD     TIMER4_IRQHandler                 ; Vector Number 66,TIMER4
        DCD     SPI2_IRQHandler                   ; Vector Number 67,SPI2
        DCD     UART3_IRQHandler                  ; Vector Number 68,UART3
        DCD     UART4_IRQHandler                  ; Vector Number 69,UART4
        DCD     TIMER5_IRQHandler                 ; Vector Number 70,TIMER5
        DCD     TIMER6_IRQHandler                 ; Vector Number 71,TIMER6
        DCD     DMA1_Channel0_IRQHandler          ; Vector Number 72,DMA1 Channel0
        DCD     DMA1_Channel1_IRQHandler          ; Vector Number 73,DMA1 Channel1
        DCD     DMA1_Channel2_IRQHandler          ; Vector Number 74,DMA1 Channel2
        DCD     DMA1_Channel3_4_IRQHandler        ; Vector Number 75,DMA1 Channel4
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:NOROOT:REORDER(2)
Reset_Handler
        LDR     R0, = SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0
        
        PUBWEAK NMI_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
NMI_Handler
        B NMI_Handler
                
        PUBWEAK HardFault_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
HardFault_Handler
        B HardFault_Handler
              
        PUBWEAK MemManage_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
MemManage_Handler
        B MemManage_Handler

        PUBWEAK BusFault_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
BusFault_Handler
        B BusFault_Handler

        PUBWEAK UsageFault_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
UsageFault_Handler
        B UsageFault_Handler
        
        PUBWEAK SVC_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SVC_Handler
        B SVC_Handler
       
        PUBWEAK DebugMon_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
DebugMon_Handler
        B DebugMon_Handler
                
        PUBWEAK PendSV_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
PendSV_Handler
        B PendSV_Handler
                
        PUBWEAK SysTick_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SysTick_Handler
        B SysTick_Handler
                
        PUBWEAK WWDGT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
WWDGT_IRQHandler
        B WWDGT_IRQHandler
                        
        PUBWEAK LVD_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LVD_IRQHandler
        B LVD_IRQHandler
        
        PUBWEAK TAMPER_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TAMPER_IRQHandler
        B TAMPER_IRQHandler

        PUBWEAK RTC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTC_IRQHandler
        B RTC_IRQHandler
                       
        PUBWEAK FMC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FMC_IRQHandler
        B FMC_IRQHandler
                        
        PUBWEAK RCU_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RCU_IRQHandler
        B RCU_IRQHandler
                        
        PUBWEAK EXTI0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI0_IRQHandler
        B EXTI0_IRQHandler
                        
        PUBWEAK EXTI1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI1_IRQHandler
        B EXTI1_IRQHandler
                        
        PUBWEAK EXTI2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI2_IRQHandler
        B EXTI2_IRQHandler

        PUBWEAK EXTI3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI3_IRQHandler
        B EXTI3_IRQHandler

        PUBWEAK EXTI4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI4_IRQHandler
        B EXTI4_IRQHandler
                        
        PUBWEAK DMA0_Channel0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA0_Channel0_IRQHandler
        B DMA0_Channel0_IRQHandler
        
                
        PUBWEAK DMA0_Channel1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA0_Channel1_IRQHandler
        B DMA0_Channel1_IRQHandler

        PUBWEAK DMA0_Channel2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA0_Channel2_IRQHandler
        B DMA0_Channel2_IRQHandler
                        
        PUBWEAK DMA0_Channel3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA0_Channel3_IRQHandler
        B DMA0_Channel3_IRQHandler

        PUBWEAK DMA0_Channel4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA0_Channel4_IRQHandler
        B DMA0_Channel4_IRQHandler
        
        PUBWEAK DMA0_Channel5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA0_Channel5_IRQHandler
        B DMA0_Channel5_IRQHandler

        PUBWEAK DMA0_Channel6_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA0_Channel6_IRQHandler
        B DMA0_Channel6_IRQHandler
                
        PUBWEAK ADC0_1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC0_1_IRQHandler
        B ADC0_1_IRQHandler
                         
        PUBWEAK USBD_HP_CAN0_TX_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USBD_HP_CAN0_TX_IRQHandler
        B USBD_HP_CAN0_TX_IRQHandler
                        
        PUBWEAK USBD_LP_CAN0_RX0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USBD_LP_CAN0_RX0_IRQHandler
        B USBD_LP_CAN0_RX0_IRQHandler
                        
        PUBWEAK CAN0_RX1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN0_RX1_IRQHandler
        B CAN0_RX1_IRQHandler
                        
        PUBWEAK CAN0_EWMC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN0_EWMC_IRQHandler
        B CAN0_EWMC_IRQHandler
                        
        PUBWEAK EXTI5_9_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI5_9_IRQHandler
        B EXTI5_9_IRQHandler
        
        PUBWEAK TIMER0_BRK_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER0_BRK_IRQHandler
        B TIMER0_BRK_IRQHandler
                        
        PUBWEAK TIMER0_UP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER0_UP_IRQHandler
        B TIMER0_UP_IRQHandler
        
        PUBWEAK TIMER0_TRG_CMT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER0_TRG_CMT_IRQHandler
        B TIMER0_TRG_CMT_IRQHandler
                       
        PUBWEAK TIMER0_Channel_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER0_Channel_IRQHandler
        B TIMER0_Channel_IRQHandler
                        
        PUBWEAK TIMER1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER1_IRQHandler
        B TIMER1_IRQHandler
                        
        PUBWEAK TIMER2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER2_IRQHandler
        B TIMER2_IRQHandler
        
       PUBWEAK TIMER3_IRQHandler
       SECTION .text:CODE:NOROOT:REORDER(1)
TIMER3_IRQHandler
       B TIMER3_IRQHandler
                        
        PUBWEAK I2C0_EV_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C0_EV_IRQHandler
        B I2C0_EV_IRQHandler
                
        PUBWEAK I2C0_ER_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C0_ER_IRQHandler
        B I2C0_ER_IRQHandler
                        
        PUBWEAK I2C1_EV_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C1_EV_IRQHandler
        B I2C1_EV_IRQHandler
                       
        PUBWEAK I2C1_ER_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C1_ER_IRQHandler
        B I2C1_ER_IRQHandler
                        
        PUBWEAK SPI0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI0_IRQHandler
        B SPI0_IRQHandler
                        
        PUBWEAK SPI1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI1_IRQHandler
        B SPI1_IRQHandler
        
          PUBWEAK USART0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART0_IRQHandler
        B USART0_IRQHandler
        
        PUBWEAK USART1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART1_IRQHandler
        B USART1_IRQHandler
        
        PUBWEAK USART2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART2_IRQHandler
        B USART2_IRQHandler

        PUBWEAK EXTI10_15_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI10_15_IRQHandler
        B EXTI10_15_IRQHandler
        
        PUBWEAK RTC_Alarm_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTC_Alarm_IRQHandler
        B RTC_Alarm_IRQHandler
        
         PUBWEAK USBD_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USBD_WKUP_IRQHandler
        B USBD_WKUP_IRQHandler
        
        PUBWEAK TIMER7_BRK_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER7_BRK_IRQHandler
        B TIMER7_BRK_IRQHandler

        PUBWEAK TIMER7_UP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER7_UP_IRQHandler
        B TIMER7_UP_IRQHandler

        PUBWEAK TIMER7_TRG_CMT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER7_TRG_CMT_IRQHandler
        B TIMER7_TRG_CMT_IRQHandler

        PUBWEAK TIMER7_Channel_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER7_Channel_IRQHandler
        B TIMER7_Channel_IRQHandler

        PUBWEAK ADC2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC2_IRQHandler
        B ADC2_IRQHandler

        PUBWEAK EXMC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXMC_IRQHandler
        B EXMC_IRQHandler
        
        PUBWEAK SDIO_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SDIO_IRQHandler
        B SDIO_IRQHandler
        
        PUBWEAK TIMER4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER4_IRQHandler
        B TIMER4_IRQHandler

        PUBWEAK SPI2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI2_IRQHandler
        B SPI2_IRQHandler

        PUBWEAK UART3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART3_IRQHandler
        B UART3_IRQHandler

        PUBWEAK UART4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART4_IRQHandler
        B UART4_IRQHandler

        PUBWEAK TIMER5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER5_IRQHandler
        B TIMER5_IRQHandler

        PUBWEAK TIMER6_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER6_IRQHandler
        B TIMER6_IRQHandler

        PUBWEAK DMA1_Channel0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel0_IRQHandler
        B DMA1_Channel0_IRQHandler

        PUBWEAK DMA1_Channel1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel1_IRQHandler
        B DMA1_Channel1_IRQHandler
        
        PUBWEAK DMA1_Channel2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel2_IRQHandler
        B DMA1_Channel2_IRQHandler

        PUBWEAK DMA1_Channel3_4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel3_4_IRQHandler
        B DMA1_Channel3_4_IRQHandler
      
        END
