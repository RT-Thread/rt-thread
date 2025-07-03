;/*!
;    \file    startup_gd32f5xx.s
;    \brief   start up file
;
;    \version 2024-07-31, V1.1.0, firmware for GD32F5xx
;*/
;
;/*
; * Copyright (c) 2009-2018 Arm Limited. All rights reserved.
; * Copyright (c) 2024, GigaDevice Semiconductor Inc.
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
;/* This file refers the CMSIS standard, some adjustments are made according to GigaDevice chips */

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table

        DATA
__vector_table
                 DCD     sfe(CSTACK)                            ; top of stack
                 DCD     Reset_Handler                          ; Vector Number 1,Reset Handler
                                                                
                 DCD     NMI_Handler                            ; Vector Number 2,NMI Handler
                 DCD     HardFault_Handler                      ; Vector Number 3,Hard Fault Handler
                 DCD     MemManage_Handler                      ; Vector Number 4,MPU Fault Handler
                 DCD     BusFault_Handler                       ; Vector Number 5,Bus Fault Handler
                 DCD     UsageFault_Handler                     ; Vector Number 6,Usage Fault Handler
                 DCD     0                                      ; Reserved
                 DCD     0                                      ; Reserved
                 DCD     0                                      ; Reserved
                 DCD     0                                      ; Reserved
                 DCD     SVC_Handler                            ; Vector Number 11,SVCall Handler
                 DCD     DebugMon_Handler                       ; Vector Number 12,Debug Monitor Handler
                 DCD     0                                      ; Reserved
                 DCD     PendSV_Handler                         ; Vector Number 14,PendSV Handler
                 DCD     SysTick_Handler                        ; Vector Number 15,SysTick Handler

                ; External Interrupts
                DCD     WWDGT_IRQHandler                        ; 16:Window Watchdog Timer
                DCD     LVD_IRQHandler                          ; 17:LVD through EXTI Line detect
                DCD     TAMPER_STAMP_IRQHandler                 ; 18:Tamper and TimeStamp through EXTI Line detect
                DCD     RTC_WKUP_IRQHandler                     ; 19:RTC Wakeup through EXTI Line
                DCD     FMC_IRQHandler                          ; 20:FMC
                DCD     RCU_CTC_IRQHandler                      ; 21:RCU and CTC
                DCD     EXTI0_IRQHandler                        ; 22:EXTI Line 0
                DCD     EXTI1_IRQHandler                        ; 23:EXTI Line 1
                DCD     EXTI2_IRQHandler                        ; 24:EXTI Line 2
                DCD     EXTI3_IRQHandler                        ; 25:EXTI Line 3
                DCD     EXTI4_IRQHandler                        ; 26:EXTI Line 4
                DCD     DMA0_Channel0_IRQHandler                ; 27:DMA0 Channel0
                DCD     DMA0_Channel1_IRQHandler                ; 28:DMA0 Channel1
                DCD     DMA0_Channel2_IRQHandler                ; 29:DMA0 Channel2
                DCD     DMA0_Channel3_IRQHandler                ; 30:DMA0 Channel3
                DCD     DMA0_Channel4_IRQHandler                ; 31:DMA0 Channel4
                DCD     DMA0_Channel5_IRQHandler                ; 32:DMA0 Channel5
                DCD     DMA0_Channel6_IRQHandler                ; 33:DMA0 Channel6
                DCD     ADC_IRQHandler                          ; 34:ADC
                DCD     CAN0_TX_IRQHandler                      ; 35:CAN0 TX
                DCD     CAN0_RX0_IRQHandler                     ; 36:CAN0 RX0
                DCD     CAN0_RX1_IRQHandler                     ; 37:CAN0 RX1
                DCD     CAN0_EWMC_IRQHandler                    ; 38:CAN0 EWMC
                DCD     EXTI5_9_IRQHandler                      ; 39:EXTI5 to EXTI9
                DCD     TIMER0_BRK_TIMER8_IRQHandler            ; 40:TIMER0 Break and TIMER8
                DCD     TIMER0_UP_TIMER9_IRQHandler             ; 41:TIMER0 Update and TIMER9
                DCD     TIMER0_TRG_CMT_TIMER10_IRQHandler       ; 42:TIMER0 Trigger and Commucation and TIMER10
                DCD     TIMER0_Channel_IRQHandler               ; 43:TIMER0 Channel Capture Compare
                DCD     TIMER1_IRQHandler                       ; 44:TIMER1
                DCD     TIMER2_IRQHandler                       ; 45:TIMER2
                DCD     TIMER3_IRQHandler                       ; 46:TIMER3
                DCD     I2C0_EV_IRQHandler                      ; 47:I2C0 Event
                DCD     I2C0_ER_IRQHandler                      ; 48:I2C0 Error
                DCD     I2C1_EV_IRQHandler                      ; 49:I2C1 Event
                DCD     I2C1_ER_IRQHandler                      ; 50:I2C1 Error
                DCD     SPI0_IRQHandler                         ; 51:SPI0
                DCD     SPI1_IRQHandler                         ; 52:SPI1
                DCD     USART0_IRQHandler                       ; 53:USART0
                DCD     USART1_IRQHandler                       ; 54:USART1
                DCD     USART2_IRQHandler                       ; 55:USART2
                DCD     EXTI10_15_IRQHandler                    ; 56:EXTI10 to EXTI15
                DCD     RTC_Alarm_IRQHandler                    ; 57:RTC Alarm
                DCD     USBFS_WKUP_IRQHandler                   ; 58:USBFS Wakeup
                DCD     TIMER7_BRK_TIMER11_IRQHandler           ; 59:TIMER7 Break and TIMER11
                DCD     TIMER7_UP_TIMER12_IRQHandler            ; 60:TIMER7 Update and TIMER12
                DCD     TIMER7_TRG_CMT_TIMER13_IRQHandler       ; 61:TIMER7 Trigger and Commucation and TIMER13
                DCD     TIMER7_Channel_IRQHandler               ; 62:TIMER7 Channel Capture Compare
                DCD     DMA0_Channel7_IRQHandler                ; 63:DMA0 Channel7
                DCD     EXMC_IRQHandler                         ; 64:EXMC
                DCD     SDIO_IRQHandler                         ; 65:SDIO
                DCD     TIMER4_IRQHandler                       ; 66:TIMER4
                DCD     SPI2_IRQHandler                         ; 67:SPI2
                DCD     UART3_IRQHandler                        ; 68:UART3
                DCD     UART4_IRQHandler                        ; 69:UART4
                DCD     TIMER5_DAC_IRQHandler                   ; 70:TIMER5 and DAC0 DAC1 Underrun error
                DCD     TIMER6_IRQHandler                       ; 71:TIMER6
                DCD     DMA1_Channel0_IRQHandler                ; 72:DMA1 Channel0
                DCD     DMA1_Channel1_IRQHandler                ; 73:DMA1 Channel1
                DCD     DMA1_Channel2_IRQHandler                ; 74:DMA1 Channel2
                DCD     DMA1_Channel3_IRQHandler                ; 75:DMA1 Channel3
                DCD     DMA1_Channel4_IRQHandler                ; 76:DMA1 Channel4
                DCD     ENET_IRQHandler                         ; 77:Ethernet
                DCD     ENET_WKUP_IRQHandler                    ; 78:Ethernet Wakeup through EXTI Line
                DCD     CAN1_TX_IRQHandler                      ; 79:CAN1 TX
                DCD     CAN1_RX0_IRQHandler                     ; 80:CAN1 RX0
                DCD     CAN1_RX1_IRQHandler                     ; 81:CAN1 RX1
                DCD     CAN1_EWMC_IRQHandler                    ; 82:CAN1 EWMC
                DCD     USBFS_IRQHandler                        ; 83:USBFS
                DCD     DMA1_Channel5_IRQHandler                ; 84:DMA1 Channel5
                DCD     DMA1_Channel6_IRQHandler                ; 85:DMA1 Channel6
                DCD     DMA1_Channel7_IRQHandler                ; 86:DMA1 Channel7
                DCD     USART5_IRQHandler                       ; 87:USART5
                DCD     I2C2_EV_IRQHandler                      ; 88:I2C2 Event
                DCD     I2C2_ER_IRQHandler                      ; 89:I2C2 Error
                DCD     USBHS_EP1_Out_IRQHandler                ; 90:USBHS Endpoint 1 Out 
                DCD     USBHS_EP1_In_IRQHandler                 ; 91:USBHS Endpoint 1 in
                DCD     USBHS_WKUP_IRQHandler                   ; 92:USBHS Wakeup through EXTI Line
                DCD     USBHS_IRQHandler                        ; 93:USBHS
                DCD     DCI_IRQHandler                          ; 94:DCI
                DCD     0                                       ; 95:Reserved
                DCD     TRNG_IRQHandler                         ; 96:TRNG
                DCD     FPU_IRQHandler                          ; 97:FPU
                DCD     UART6_IRQHandler                        ; 98:UART6
                DCD     UART7_IRQHandler                        ; 99:UART7
                DCD     SPI3_IRQHandler                         ; 100:SPI3
                DCD     SPI4_IRQHandler                         ; 101:SPI4
                DCD     SPI5_IRQHandler                         ; 102:SPI5
                DCD     SAI_IRQHandler                          ; 103:SAI
                DCD     TLI_IRQHandler                          ; 104:TLI
                DCD     TLI_ER_IRQHandler                       ; 105:TLI Error
                DCD     IPA_IRQHandler                          ; 106:IPA
                DCD     PKCAU_IRQHandler                        ; 107:PKCAU
                DCD     I2C3_EV_IRQHandler                      ; 108:I2C3 Event
                DCD     I2C3_ER_IRQHandler                      ; 109:I2C3 Error
                DCD     I2C4_EV_IRQHandler                      ; 110:I2C4 Event
                DCD     I2C4_ER_IRQHandler                      ; 111:I2C4 Error
                DCD     I2C5_EV_IRQHandler                      ; 112:I2C5 Event
                DCD     I2C5_ER_IRQHandler                      ; 113:I2C5 Error
                DCD     I2C3_WKUP_IRQHandler                    ; 114:I2C3 Wakeup through EXTI Line
                DCD     I2C4_WKUP_IRQHandler                    ; 115:I2C4 Wakeup through EXTI Line
                DCD     I2C5_WKUP_IRQHandler                    ; 116:I2C5 Wakeup through EXTI Line
                DCD     SYSCFG_SINGLE_BIT_ECC_ER_IRQHandler     ; 117:SYSCFG SRAM ECC Error
                DCD     HAU_IRQHandler                          ; 118:HAU
                DCD     CAU_IRQHandler                          ; 119:CAU

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:NOROOT:REORDER(2)
Reset_Handler
                LDR     r2, =0x8000
                LDR     r1, =0x20000000
                MOV     r0, #0x00
        
SRAM_INIT
                STM     r1!, {r0}
                SUBS    r2, r2, #4
                CMP     r2, #0x00
                BNE     SRAM_INIT

        LDR     R0, =SystemInit
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
        
        PUBWEAK TAMPER_STAMP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TAMPER_STAMP_IRQHandler
        B TAMPER_STAMP_IRQHandler
        
        PUBWEAK RTC_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTC_WKUP_IRQHandler
        B RTC_WKUP_IRQHandler
        
        PUBWEAK FMC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FMC_IRQHandler
        B FMC_IRQHandler
        
        PUBWEAK RCU_CTC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RCU_CTC_IRQHandler
        B RCU_CTC_IRQHandler
        
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
        
        PUBWEAK ADC_IRQHandler                    
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC_IRQHandler                    
        B ADC_IRQHandler                    
        
        PUBWEAK CAN0_TX_IRQHandler                
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN0_TX_IRQHandler                
        B CAN0_TX_IRQHandler                
        
        PUBWEAK CAN0_RX0_IRQHandler               
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN0_RX0_IRQHandler               
        B CAN0_RX0_IRQHandler               
        
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
        
        PUBWEAK TIMER0_BRK_TIMER8_IRQHandler    
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER0_BRK_TIMER8_IRQHandler    
        B TIMER0_BRK_TIMER8_IRQHandler    
        
        PUBWEAK TIMER0_UP_TIMER9_IRQHandler   
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER0_UP_TIMER9_IRQHandler   
        B TIMER0_UP_TIMER9_IRQHandler   
        
        PUBWEAK TIMER0_TRG_CMT_TIMER10_IRQHandler 
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER0_TRG_CMT_TIMER10_IRQHandler 
        B TIMER0_TRG_CMT_TIMER10_IRQHandler 
        
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

        PUBWEAK USBFS_WKUP_IRQHandler             
        SECTION .text:CODE:NOROOT:REORDER(1)
USBFS_WKUP_IRQHandler             
        B USBFS_WKUP_IRQHandler             

        PUBWEAK TIMER7_BRK_TIMER11_IRQHandler   
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER7_BRK_TIMER11_IRQHandler   
        B TIMER7_BRK_TIMER11_IRQHandler   

        PUBWEAK TIMER7_UP_TIMER12_IRQHandler  
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER7_UP_TIMER12_IRQHandler  
        B TIMER7_UP_TIMER12_IRQHandler  

        PUBWEAK TIMER7_TRG_CMT_TIMER13_IRQHandler 
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER7_TRG_CMT_TIMER13_IRQHandler 
        B TIMER7_TRG_CMT_TIMER13_IRQHandler 

        PUBWEAK TIMER7_Channel_IRQHandler         
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER7_Channel_IRQHandler         
        B TIMER7_Channel_IRQHandler         

        PUBWEAK DMA0_Channel7_IRQHandler         
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA0_Channel7_IRQHandler         
        B DMA0_Channel7_IRQHandler         

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

        PUBWEAK TIMER5_DAC_IRQHandler             
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER5_DAC_IRQHandler             
        B TIMER5_DAC_IRQHandler             

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

        PUBWEAK DMA1_Channel3_IRQHandler         
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel3_IRQHandler         
        B DMA1_Channel3_IRQHandler         

        PUBWEAK DMA1_Channel4_IRQHandler          
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel4_IRQHandler          
        B DMA1_Channel4_IRQHandler          

        PUBWEAK ENET_IRQHandler                  
        SECTION .text:CODE:NOROOT:REORDER(1)
ENET_IRQHandler                  
        B ENET_IRQHandler                  
        
        PUBWEAK ENET_WKUP_IRQHandler             
        SECTION .text:CODE:NOROOT:REORDER(1)
ENET_WKUP_IRQHandler             
        B ENET_WKUP_IRQHandler             

        PUBWEAK CAN1_TX_IRQHandler                
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN1_TX_IRQHandler                
        B CAN1_TX_IRQHandler                

        PUBWEAK CAN1_RX0_IRQHandler              
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN1_RX0_IRQHandler              
        B CAN1_RX0_IRQHandler              

        PUBWEAK CAN1_RX1_IRQHandler               
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN1_RX1_IRQHandler               
        B CAN1_RX1_IRQHandler               

        PUBWEAK CAN1_EWMC_IRQHandler               
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN1_EWMC_IRQHandler               
        B CAN1_EWMC_IRQHandler               

        PUBWEAK USBFS_IRQHandler                  
        SECTION .text:CODE:NOROOT:REORDER(1)
USBFS_IRQHandler                  
        B USBFS_IRQHandler                  

        PUBWEAK DMA1_Channel5_IRQHandler          
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel5_IRQHandler          
        B DMA1_Channel5_IRQHandler          

        PUBWEAK DMA1_Channel6_IRQHandler          
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel6_IRQHandler          
        B DMA1_Channel6_IRQHandler          

        PUBWEAK DMA1_Channel7_IRQHandler          
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_Channel7_IRQHandler          
        B DMA1_Channel7_IRQHandler          

        PUBWEAK USART5_IRQHandler                 
        SECTION .text:CODE:NOROOT:REORDER(1)
USART5_IRQHandler                 
        B USART5_IRQHandler                 

        PUBWEAK I2C2_EV_IRQHandler               
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C2_EV_IRQHandler               
        B I2C2_EV_IRQHandler               

        PUBWEAK I2C2_ER_IRQHandler                
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C2_ER_IRQHandler                
        B I2C2_ER_IRQHandler                

        PUBWEAK USBHS_EP1_Out_IRQHandler    
        SECTION .text:CODE:NOROOT:REORDER(1)
USBHS_EP1_Out_IRQHandler    
        B USBHS_EP1_Out_IRQHandler    

        PUBWEAK USBHS_EP1_In_IRQHandler     
        SECTION .text:CODE:NOROOT:REORDER(1)
USBHS_EP1_In_IRQHandler     
        B USBHS_EP1_In_IRQHandler     

        PUBWEAK USBHS_WKUP_IRQHandler             
        SECTION .text:CODE:NOROOT:REORDER(1)
USBHS_WKUP_IRQHandler             
        B USBHS_WKUP_IRQHandler             

        PUBWEAK USBHS_IRQHandler                  
        SECTION .text:CODE:NOROOT:REORDER(1)
USBHS_IRQHandler                  
        B USBHS_IRQHandler                  

        PUBWEAK DCI_IRQHandler                    
        SECTION .text:CODE:NOROOT:REORDER(1)
DCI_IRQHandler                    
        B DCI_IRQHandler                    

        PUBWEAK TRNG_IRQHandler                  
        SECTION .text:CODE:NOROOT:REORDER(1)
TRNG_IRQHandler                  
        B TRNG_IRQHandler                  

        PUBWEAK FPU_IRQHandler                    
        SECTION .text:CODE:NOROOT:REORDER(1)
FPU_IRQHandler                    
        B FPU_IRQHandler                    

        PUBWEAK UART6_IRQHandler                  
        SECTION .text:CODE:NOROOT:REORDER(1)
UART6_IRQHandler                  
        B UART6_IRQHandler                  

        PUBWEAK UART7_IRQHandler                  
        SECTION .text:CODE:NOROOT:REORDER(1)
UART7_IRQHandler                  
        B UART7_IRQHandler                  

        PUBWEAK SPI3_IRQHandler                   
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI3_IRQHandler                   
        B SPI3_IRQHandler                   

        PUBWEAK SPI4_IRQHandler                   
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI4_IRQHandler                   
        B SPI4_IRQHandler                   

        PUBWEAK SPI5_IRQHandler                   
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI5_IRQHandler                   
        B SPI5_IRQHandler                   

        PUBWEAK SAI_IRQHandler                   
        SECTION .text:CODE:NOROOT:REORDER(1)
SAI_IRQHandler                   
        B SAI_IRQHandler   

        PUBWEAK TLI_IRQHandler                    
        SECTION .text:CODE:NOROOT:REORDER(1)
TLI_IRQHandler                    
        B TLI_IRQHandler                    

        PUBWEAK TLI_ER_IRQHandler                 
        SECTION .text:CODE:NOROOT:REORDER(1)
TLI_ER_IRQHandler                 
        B TLI_ER_IRQHandler                 

        PUBWEAK IPA_IRQHandler                    
        SECTION .text:CODE:NOROOT:REORDER(1)
IPA_IRQHandler                    
        B IPA_IRQHandler                    

        PUBWEAK PKCAU_IRQHandler                    
        SECTION .text:CODE:NOROOT:REORDER(1)
PKCAU_IRQHandler                    
        B PKCAU_IRQHandler                    

        PUBWEAK I2C3_EV_IRQHandler                    
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C3_EV_IRQHandler                    
        B I2C3_EV_IRQHandler                    

        PUBWEAK I2C3_ER_IRQHandler                    
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C3_ER_IRQHandler                    
        B I2C3_ER_IRQHandler                    

        PUBWEAK I2C4_EV_IRQHandler                    
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C4_EV_IRQHandler                    
        B I2C4_EV_IRQHandler                    

        PUBWEAK I2C4_ER_IRQHandler                    
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C4_ER_IRQHandler                    
        B I2C4_ER_IRQHandler                    

        PUBWEAK I2C5_EV_IRQHandler                    
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C5_EV_IRQHandler                    
        B I2C5_EV_IRQHandler                    

        PUBWEAK I2C5_ER_IRQHandler                    
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C5_ER_IRQHandler                    
        B I2C5_ER_IRQHandler                    

        PUBWEAK I2C3_WKUP_IRQHandler                    
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C3_WKUP_IRQHandler                    
        B I2C3_WKUP_IRQHandler                    

        PUBWEAK I2C4_WKUP_IRQHandler                    
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C4_WKUP_IRQHandler                    
        B I2C4_WKUP_IRQHandler                    

        PUBWEAK I2C5_WKUP_IRQHandler                    
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C5_WKUP_IRQHandler                    
        B I2C5_WKUP_IRQHandler                    

        PUBWEAK SYSCFG_SINGLE_BIT_ECC_ER_IRQHandler                    
        SECTION .text:CODE:NOROOT:REORDER(1)
SYSCFG_SINGLE_BIT_ECC_ER_IRQHandler                    
        B SYSCFG_SINGLE_BIT_ECC_ER_IRQHandler                    

        PUBWEAK HAU_IRQHandler                    
        SECTION .text:CODE:NOROOT:REORDER(1)
HAU_IRQHandler                    
        B HAU_IRQHandler                    

        PUBWEAK CAU_IRQHandler                    
        SECTION .text:CODE:NOROOT:REORDER(1)
CAU_IRQHandler                    
        B CAU_IRQHandler                    

        END