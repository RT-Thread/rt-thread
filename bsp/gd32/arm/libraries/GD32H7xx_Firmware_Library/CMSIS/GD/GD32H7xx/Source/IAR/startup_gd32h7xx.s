;/*!
;    \file    startup_gd32h7xx.s
;    \brief   start up file

;    \version 2024-01-05, V1.2.0, firmware for GD32H7xx
;*/

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

;               /* external interrupts handler */
                DCD     WWDGT_IRQHandler                             ; 16:Window Watchdog Timer
                DCD     AVD_LVD_OVD_IRQHandler                       ; 17:AVD/LVD/OVD through EXTI Line detect
                DCD     TAMPER_STAMP_LXTAL_IRQHandler                ; 18:RTC Tamper and TimeStamp through EXTI Line detect, LXTAL clock security system interrupt
                DCD     RTC_WKUP_IRQHandler                          ; 19:RTC Wakeup from EXTI interrupt
                DCD     FMC_IRQHandler                               ; 20:FMC global interrupt
                DCD     RCU_IRQHandler                               ; 21:RCU global interrupt
                DCD     EXTI0_IRQHandler                             ; 22:EXTI Line 0
                DCD     EXTI1_IRQHandler                             ; 23:EXTI Line 1
                DCD     EXTI2_IRQHandler                             ; 24:EXTI Line 2
                DCD     EXTI3_IRQHandler                             ; 25:EXTI Line 3
                DCD     EXTI4_IRQHandler                             ; 26:EXTI Line 4
                DCD     DMA0_Channel0_IRQHandler                     ; 27:DMA0 Channel 0
                DCD     DMA0_Channel1_IRQHandler                     ; 28:DMA0 Channel 1
                DCD     DMA0_Channel2_IRQHandler                     ; 29:DMA0 Channel 2
                DCD     DMA0_Channel3_IRQHandler                     ; 30:DMA0 Channel 3
                DCD     DMA0_Channel4_IRQHandler                     ; 31:DMA0 Channel 4
                DCD     DMA0_Channel5_IRQHandler                     ; 32:DMA0 Channel 5
                DCD     DMA0_Channel6_IRQHandler                     ; 33:DMA0 Channel 6
                DCD     ADC0_1_IRQHandler                            ; 34:ADC0 and ADC1 interrupt
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     EXTI5_9_IRQHandler                           ; 39:EXTI5 to EXTI9
                DCD     TIMER0_BRK_IRQHandler                        ; 40:TIMER0 Break
                DCD     TIMER0_UP_IRQHandler                         ; 41:TIMER0 Update
                DCD     TIMER0_TRG_CMT_IRQHandler                    ; 42:TIMER0 Trigger and Commutation
                DCD     TIMER0_Channel_IRQHandler                    ; 43:TIMER0 Capture Compare
                DCD     TIMER1_IRQHandler                            ; 44:TIMER1
                DCD     TIMER2_IRQHandler                            ; 45:TIMER2
                DCD     TIMER3_IRQHandler                            ; 46:TIMER3
                DCD     I2C0_EV_IRQHandler                           ; 47:I2C0 Event
                DCD     I2C0_ER_IRQHandler                           ; 48:I2C0 Error
                DCD     I2C1_EV_IRQHandler                           ; 49:I2C1 Event
                DCD     I2C1_ER_IRQHandler                           ; 50:I2C1 Error
                DCD     SPI0_IRQHandler                              ; 51:SPI0
                DCD     SPI1_IRQHandler                              ; 52:SPI1
                DCD     USART0_IRQHandler                            ; 53:USART0 global and wakeup
                DCD     USART1_IRQHandler                            ; 54:USART1 global and wakeup
                DCD     USART2_IRQHandler                            ; 55:USART2 global and wakeup
                DCD     EXTI10_15_IRQHandler                         ; 56:EXTI10 to EXTI15
                DCD     RTC_Alarm_IRQHandler                         ; 57:RTC Alarm
                DCD     0                                            ; Reserved
                DCD     TIMER7_BRK_IRQHandler                        ; 59:TIMER7 Break
                DCD     TIMER7_UP_IRQHandler                         ; 60:TIMER7 Update
                DCD     TIMER7_TRG_CMT_IRQHandler                    ; 61:TIMER7 Trigger and Commutation
                DCD     TIMER7_Channel_IRQHandler                    ; 62:TIMER7 Channel Capture Compare
                DCD     DMA0_Channel7_IRQHandler                     ; 63:DMA0 Channel 7
                DCD     EXMC_IRQHandler                              ; 64:EXMC
                DCD     SDIO0_IRQHandler                             ; 65:SDIO0
                DCD     TIMER4_IRQHandler                            ; 66:TIMER4
                DCD     SPI2_IRQHandler                              ; 67:SPI2
                DCD     UART3_IRQHandler                             ; 68:UART3
                DCD     UART4_IRQHandler                             ; 69:UART4
                DCD     TIMER5_DAC_UDR_IRQHandler                    ; 70:TIMER5 global interrupt and DAC1/DAC0 underrun error
                DCD     TIMER6_IRQHandler                            ; 71:TIMER6
                DCD     DMA1_Channel0_IRQHandler                     ; 72:DMA1 Channel0
                DCD     DMA1_Channel1_IRQHandler                     ; 73:DMA1 Channel1
                DCD     DMA1_Channel2_IRQHandler                     ; 74:DMA1 Channel2
                DCD     DMA1_Channel3_IRQHandler                     ; 75:DMA1 Channel3
                DCD     DMA1_Channel4_IRQHandler                     ; 76:DMA1 Channel4
                DCD     ENET0_IRQHandler                             ; 77:Ethernet0
                DCD     ENET0_WKUP_IRQHandler                        ; 78:Ethernet0 Wakeup through EXTI Line
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     DMA1_Channel5_IRQHandler                     ; 84:DMA1 Channel5
                DCD     DMA1_Channel6_IRQHandler                     ; 85:DMA1 Channel6
                DCD     DMA1_Channel7_IRQHandler                     ; 86:DMA1 Channel7
                DCD     USART5_IRQHandler                            ; 87:USART5 global and wakeup
                DCD     I2C2_EV_IRQHandler                           ; 88:I2C2 Event
                DCD     I2C2_ER_IRQHandler                           ; 89:I2C2 Error
                DCD     USBHS0_EP1_OUT_IRQHandler                    ; 90:USBHS0 Endpoint 1 Out 
                DCD     USBHS0_EP1_IN_IRQHandler                     ; 91:USBHS0 Endpoint 1 in
                DCD     USBHS0_WKUP_IRQHandler                       ; 92:USBHS0 Wakeup through EXTI Line
                DCD     USBHS0_IRQHandler                            ; 93:USBHS0
                DCD     DCI_IRQHandler                               ; 94:DCI
                DCD     CAU_IRQHandler                               ; 95:CAU
                DCD     HAU_TRNG_IRQHandler                          ; 96:HAU and TRNG
                DCD     FPU_IRQHandler                               ; 97:FPU
                DCD     UART6_IRQHandler                             ; 98:UART6
                DCD     UART7_IRQHandler                             ; 99:UART7
                DCD     SPI3_IRQHandler                              ; 100:SPI3
                DCD     SPI4_IRQHandler                              ; 101:SPI4
                DCD     SPI5_IRQHandler                              ; 102:SPI5
                DCD     SAI0_IRQHandler                              ; 103:SAI0
                DCD     TLI_IRQHandler                               ; 104:TLI
                DCD     TLI_ER_IRQHandler                            ; 105:TLI Error
                DCD     IPA_IRQHandler                               ; 106:IPA
                DCD     SAI1_IRQHandler                              ; 107:SAI1
                DCD     OSPI0_IRQHandler                             ; 108:OSPI0
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     I2C3_EV_IRQHandler                           ; 111:I2C3 Event
                DCD     I2C3_ER_IRQHandler                           ; 112:I2C3 Error
                DCD     RSPDIF_IRQHandler                            ; 113:RSPDIF
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     DMAMUX_OVR_IRQHandler                        ; 118:DMAMUX Overrun interrupt
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     HPDF_INT0_IRQHandler                         ; 126:HPDF global interrupt 0
                DCD     HPDF_INT1_IRQHandler                         ; 127:HPDF global interrupt 1
                DCD     HPDF_INT2_IRQHandler                         ; 128:HPDF global interrupt 2
                DCD     HPDF_INT3_IRQHandler                         ; 129:HPDF global interrupt 3
                DCD     SAI2_IRQHandler                              ; 130:SAI2 global interrupt
                DCD     0                                            ; Reserved
                DCD     TIMER14_IRQHandler                           ; 132:TIMER14
                DCD     TIMER15_IRQHandler                           ; 133:TIMER15
                DCD     TIMER16_IRQHandler                           ; 134:TIMER16
                DCD     0                                            ; Reserved
                DCD     MDIO_IRQHandler                              ; 136:MDIO
                DCD     0                                            ; Reserved
                DCD     MDMA_IRQHandler                              ; 138:MDMA
                DCD     0                                            ; Reserved
                DCD     SDIO1_IRQHandler                             ; 140:SDIO1
                DCD     HWSEM_IRQHandler                             ; 141:HWSEM
                DCD     0                                            ; Reserved
                DCD     ADC2_IRQHandler                              ; 143:ADC2   
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     CMP0_1_IRQHandler                            ; 153:CMP0 and CMP1
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     CTC_IRQHandler                               ; 160:Clock Recovery System
                DCD     RAMECCMU_IRQHandler                          ; 161:RAMECCMU
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     OSPI1_IRQHandler                             ; 166:OSPI1
                DCD     RTDEC0_IRQHandler                            ; 167:RTDEC0
                DCD     RTDEC1_IRQHandler                            ; 168:RTDEC1
                DCD     FAC_IRQHandler                               ; 169:FAC
                DCD     TMU_IRQHandler                               ; 170:TMU
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     0                                            ; Reserved
                DCD     TIMER22_IRQHandler                           ; 177:TIMER22
                DCD     TIMER23_IRQHandler                           ; 178:TIMER23
                DCD     TIMER30_IRQHandler                           ; 179:TIMER30
                DCD     TIMER31_IRQHandler                           ; 180:TIMER31
                DCD     TIMER40_IRQHandler                           ; 181:TIMER40
                DCD     TIMER41_IRQHandler                           ; 182:TIMER41
                DCD     TIMER42_IRQHandler                           ; 183:TIMER42
                DCD     TIMER43_IRQHandler                           ; 184:TIMER43
                DCD     TIMER44_IRQHandler                           ; 185:TIMER44
                DCD     TIMER50_IRQHandler                           ; 186:TIMER50
                DCD     TIMER51_IRQHandler                           ; 187:TIMER51
                DCD     USBHS1_EP1_OUT_IRQHandler                    ; 188:USBHS1 endpoint 1 out
                DCD     USBHS1_EP1_IN_IRQHandler                     ; 189:USBHS1 endpoint 1 in
                DCD     USBHS1_WKUP_IRQHandler                       ; 190:USBHS1 wakeup
                DCD     USBHS1_IRQHandler                            ; 191:USBHS1
                DCD     ENET1_IRQHandler                             ; 192:Ethernet1
                DCD     ENET1_WKUP_IRQHandler                        ; 193:Ethernet1 wakeup
                DCD     0                                            ; Reserved
                DCD     CAN0_WKUP_IRQHandler                         ; 195:CAN0 wakeup
                DCD     CAN0_Message_IRQHandler                      ; 196:CAN0 interrupt for message buffer
                DCD     CAN0_Busoff_IRQHandler                       ; 197:CAN0 interrupt for Bus off / Bus off done
                DCD     CAN0_Error_IRQHandler                        ; 198:CAN0 interrupt for Error
                DCD     CAN0_FastError_IRQHandler                    ; 199:CAN0 interrupt for Error in fast transmission
                DCD     CAN0_TEC_IRQHandler                          ; 200:CAN0 interrupt for Transmit warning
                DCD     CAN0_REC_IRQHandler                          ; 201:CAN0 interrupt for Receive warning
                DCD     CAN1_WKUP_IRQHandler                         ; 202:CAN1 wakeup
                DCD     CAN1_Message_IRQHandler                      ; 203:CAN1 interrupt for message buffer
                DCD     CAN1_Busoff_IRQHandler                       ; 204:CAN1 interrupt for Bus off / Bus off done
                DCD     CAN1_Error_IRQHandler                        ; 205:CAN1 interrupt for Error
                DCD     CAN1_FastError_IRQHandler                    ; 206:CAN1 interrupt for Error in fast transmission
                DCD     CAN1_TEC_IRQHandler                          ; 207:CAN1 interrupt for Transmit warning
                DCD     CAN1_REC_IRQHandler                          ; 208:CAN1 interrupt for Receive warning
                DCD     CAN2_WKUP_IRQHandler                         ; 209:CAN2 wakeup
                DCD     CAN2_Message_IRQHandler                      ; 210:CAN2 interrupt for message buffer
                DCD     CAN2_Busoff_IRQHandler                       ; 211:CAN2 interrupt for Bus off / Bus off done
                DCD     CAN2_Error_IRQHandler                        ; 212:CAN2 interrupt for Error
                DCD     CAN2_FastError_IRQHandler                    ; 213:CAN2 interrupt for Error in fast transmission
                DCD     CAN2_TEC_IRQHandler                          ; 214:CAN2 interrupt for Transmit warning
                DCD     CAN2_REC_IRQHandler                          ; 215:CAN2 interrupt for Receive warning
                DCD     EFUSE_IRQHandler                             ; 216:EFUSE
                DCD     I2C0_WKUP_IRQHandler                         ; 217:I2C0 wakeup
                DCD     I2C1_WKUP_IRQHandler                         ; 218:I2C1 wakeup
                DCD     I2C2_WKUP_IRQHandler                         ; 219:I2C2 wakeup
                DCD     I2C3_WKUP_IRQHandler                         ; 220:I2C3 wakeup
                DCD     LPDTS_IRQHandler                             ; 221:LPDTS
                DCD     LPDTS_WKUP_IRQHandler                        ; 222:LPDTS wakeup
                DCD     TIMER0_DEC_IRQHandler                        ; 223:TIMER0 DEC
                DCD     TIMER7_DEC_IRQHandler                        ; 224:TIMER7 DEC
                DCD     TIMER1_DEC_IRQHandler                        ; 225:TIMER1 DEC
                DCD     TIMER2_DEC_IRQHandler                        ; 226:TIMER2 DEC
                DCD     TIMER3_DEC_IRQHandler                        ; 227:TIMER3 DEC
                DCD     TIMER4_DEC_IRQHandler                        ; 228:TIMER4 DEC
                DCD     TIMER22_DEC_IRQHandler                       ; 229:TIMER22 DEC
                DCD     TIMER23_DEC_IRQHandler                       ; 230:TIMER23 DEC
                DCD     TIMER30_DEC_IRQHandler                       ; 231:TIMER30 DEC
                DCD     TIMER31_DEC_IRQHandler                       ; 232:TIMER31 DEC
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:NOROOT:REORDER(2)
Reset_Handler

                 LDR     R0, = 0x24000000
                 ADD     R1, R0, #0x8000
                 LDR     R2, =0x0
MEM_INIT         STRD    R2, R2, [ R0 ] , #8
                 CMP     R0, R1
                 BNE     MEM_INIT

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

        PUBWEAK AVD_LVD_OVD_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
AVD_LVD_OVD_IRQHandler
        B AVD_LVD_OVD_IRQHandler

        PUBWEAK TAMPER_STAMP_LXTAL_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TAMPER_STAMP_LXTAL_IRQHandler
        B TAMPER_STAMP_LXTAL_IRQHandler

        PUBWEAK RTC_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTC_WKUP_IRQHandler
        B RTC_WKUP_IRQHandler

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

        PUBWEAK DMA0_Channel7_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA0_Channel7_IRQHandler
        B DMA0_Channel7_IRQHandler

        PUBWEAK EXMC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXMC_IRQHandler
        B EXMC_IRQHandler

        PUBWEAK SDIO0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SDIO0_IRQHandler
        B SDIO0_IRQHandler

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

        PUBWEAK TIMER5_DAC_UDR_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER5_DAC_UDR_IRQHandler
        B TIMER5_DAC_UDR_IRQHandler

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

        PUBWEAK ENET0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ENET0_IRQHandler
        B ENET0_IRQHandler

        PUBWEAK ENET0_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ENET0_WKUP_IRQHandler
        B ENET0_WKUP_IRQHandler

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

        PUBWEAK USBHS0_EP1_OUT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USBHS0_EP1_OUT_IRQHandler
        B USBHS0_EP1_OUT_IRQHandler

        PUBWEAK USBHS0_EP1_IN_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USBHS0_EP1_IN_IRQHandler
        B USBHS0_EP1_IN_IRQHandler

        PUBWEAK USBHS0_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USBHS0_WKUP_IRQHandler
        B USBHS0_WKUP_IRQHandler

        PUBWEAK USBHS0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USBHS0_IRQHandler
        B USBHS0_IRQHandler

        PUBWEAK DCI_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DCI_IRQHandler
        B DCI_IRQHandler

        PUBWEAK CAU_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAU_IRQHandler
        B CAU_IRQHandler

        PUBWEAK HAU_TRNG_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HAU_TRNG_IRQHandler
        B HAU_TRNG_IRQHandler

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

        PUBWEAK SAI0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SAI0_IRQHandler
        B SAI0_IRQHandler

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

        PUBWEAK SAI1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SAI1_IRQHandler
        B SAI1_IRQHandler

        PUBWEAK OSPI0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
OSPI0_IRQHandler
        B OSPI0_IRQHandler

        PUBWEAK I2C3_EV_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C3_EV_IRQHandler
        B I2C3_EV_IRQHandler

        PUBWEAK I2C3_ER_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C3_ER_IRQHandler
        B I2C3_ER_IRQHandler

        PUBWEAK RSPDIF_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RSPDIF_IRQHandler
        B RSPDIF_IRQHandler

        PUBWEAK DMAMUX_OVR_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMAMUX_OVR_IRQHandler
        B DMAMUX_OVR_IRQHandler

        PUBWEAK HPDF_INT0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDF_INT0_IRQHandler
        B HPDF_INT0_IRQHandler

        PUBWEAK HPDF_INT1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDF_INT1_IRQHandler
        B HPDF_INT1_IRQHandler

        PUBWEAK HPDF_INT2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDF_INT2_IRQHandler
        B HPDF_INT2_IRQHandler

        PUBWEAK HPDF_INT3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HPDF_INT3_IRQHandler
        B HPDF_INT3_IRQHandler

        PUBWEAK SAI2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SAI2_IRQHandler
        B SAI2_IRQHandler

        PUBWEAK TIMER14_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER14_IRQHandler
        B TIMER14_IRQHandler

        PUBWEAK TIMER15_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER15_IRQHandler
        B TIMER15_IRQHandler

        PUBWEAK TIMER16_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER16_IRQHandler
        B TIMER16_IRQHandler

        PUBWEAK MDIO_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
MDIO_IRQHandler
        B MDIO_IRQHandler

        PUBWEAK MDMA_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
MDMA_IRQHandler
        B MDMA_IRQHandler

        PUBWEAK SDIO1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SDIO1_IRQHandler
        B SDIO1_IRQHandler

        PUBWEAK HWSEM_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HWSEM_IRQHandler
        B HWSEM_IRQHandler

        PUBWEAK ADC2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC2_IRQHandler
        B ADC2_IRQHandler

        PUBWEAK CMP0_1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CMP0_1_IRQHandler
        B CMP0_1_IRQHandler

        PUBWEAK CTC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CTC_IRQHandler
        B CTC_IRQHandler

        PUBWEAK RAMECCMU_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RAMECCMU_IRQHandler
        B RAMECCMU_IRQHandler

        PUBWEAK OSPI1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
OSPI1_IRQHandler
        B OSPI1_IRQHandler

        PUBWEAK RTDEC0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTDEC0_IRQHandler
        B RTDEC0_IRQHandler

        PUBWEAK RTDEC1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTDEC1_IRQHandler
        B RTDEC1_IRQHandler

        PUBWEAK FAC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FAC_IRQHandler
        B FAC_IRQHandler

        PUBWEAK TMU_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TMU_IRQHandler
        B TMU_IRQHandler

        PUBWEAK TIMER22_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER22_IRQHandler
        B TIMER22_IRQHandler

        PUBWEAK TIMER23_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER23_IRQHandler
        B TIMER23_IRQHandler

        PUBWEAK TIMER30_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER30_IRQHandler
        B TIMER30_IRQHandler

        PUBWEAK TIMER31_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER31_IRQHandler
        B TIMER31_IRQHandler

        PUBWEAK TIMER40_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER40_IRQHandler
        B TIMER40_IRQHandler

        PUBWEAK TIMER41_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER41_IRQHandler
        B TIMER41_IRQHandler

        PUBWEAK TIMER42_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER42_IRQHandler
        B TIMER42_IRQHandler

        PUBWEAK TIMER43_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER43_IRQHandler
        B TIMER43_IRQHandler

        PUBWEAK TIMER44_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER44_IRQHandler
        B TIMER44_IRQHandler

        PUBWEAK TIMER50_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER50_IRQHandler
        B TIMER50_IRQHandler

        PUBWEAK TIMER51_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER51_IRQHandler
        B TIMER51_IRQHandler

        PUBWEAK USBHS1_EP1_OUT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USBHS1_EP1_OUT_IRQHandler
        B USBHS1_EP1_OUT_IRQHandler

        PUBWEAK USBHS1_EP1_IN_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USBHS1_EP1_IN_IRQHandler
        B USBHS1_EP1_IN_IRQHandler

        PUBWEAK USBHS1_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USBHS1_WKUP_IRQHandler
        B USBHS1_WKUP_IRQHandler

        PUBWEAK USBHS1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USBHS1_IRQHandler
        B USBHS1_IRQHandler

        PUBWEAK ENET1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ENET1_IRQHandler
        B ENET1_IRQHandler

        PUBWEAK ENET1_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ENET1_WKUP_IRQHandler
        B ENET1_WKUP_IRQHandler

        PUBWEAK CAN0_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN0_WKUP_IRQHandler
        B CAN0_WKUP_IRQHandler

        PUBWEAK CAN0_Message_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN0_Message_IRQHandler
        B CAN0_Message_IRQHandler

        PUBWEAK CAN0_Busoff_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN0_Busoff_IRQHandler
        B CAN0_Busoff_IRQHandler

        PUBWEAK CAN0_Error_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN0_Error_IRQHandler
        B CAN0_Error_IRQHandler

        PUBWEAK CAN0_FastError_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN0_FastError_IRQHandler
        B CAN0_FastError_IRQHandler

        PUBWEAK CAN0_TEC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN0_TEC_IRQHandler
        B CAN0_TEC_IRQHandler

        PUBWEAK CAN0_REC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN0_REC_IRQHandler
        B CAN0_REC_IRQHandler

        PUBWEAK CAN1_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN1_WKUP_IRQHandler
        B CAN1_WKUP_IRQHandler

        PUBWEAK CAN1_Message_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN1_Message_IRQHandler
        B CAN1_Message_IRQHandler

        PUBWEAK CAN1_Busoff_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN1_Busoff_IRQHandler
        B CAN1_Busoff_IRQHandler

        PUBWEAK CAN1_Error_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN1_Error_IRQHandler
        B CAN1_Error_IRQHandler

        PUBWEAK CAN1_FastError_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN1_FastError_IRQHandler
        B CAN1_FastError_IRQHandler

        PUBWEAK CAN1_TEC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN1_TEC_IRQHandler
        B CAN1_TEC_IRQHandler

        PUBWEAK CAN1_REC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN1_REC_IRQHandler
        B CAN1_REC_IRQHandler

        PUBWEAK CAN2_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN2_WKUP_IRQHandler
        B CAN2_WKUP_IRQHandler

        PUBWEAK CAN2_Message_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN2_Message_IRQHandler
        B CAN2_Message_IRQHandler

        PUBWEAK CAN2_Busoff_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN2_Busoff_IRQHandler
        B CAN2_Busoff_IRQHandler

        PUBWEAK CAN2_Error_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN2_Error_IRQHandler
        B CAN2_Error_IRQHandler

        PUBWEAK CAN2_FastError_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN2_FastError_IRQHandler
        B CAN2_FastError_IRQHandler

        PUBWEAK CAN2_TEC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN2_TEC_IRQHandler
        B CAN2_TEC_IRQHandler

        PUBWEAK CAN2_REC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN2_REC_IRQHandler
        B CAN2_REC_IRQHandler

        PUBWEAK EFUSE_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EFUSE_IRQHandler
        B EFUSE_IRQHandler

        PUBWEAK I2C0_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C0_WKUP_IRQHandler
        B I2C0_WKUP_IRQHandler

        PUBWEAK I2C1_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C1_WKUP_IRQHandler
        B I2C1_WKUP_IRQHandler

        PUBWEAK I2C2_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C2_WKUP_IRQHandler
        B I2C2_WKUP_IRQHandler

        PUBWEAK I2C3_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C3_WKUP_IRQHandler
        B I2C3_WKUP_IRQHandler

        PUBWEAK LPDTS_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LPDTS_IRQHandler
        B LPDTS_IRQHandler

        PUBWEAK LPDTS_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LPDTS_WKUP_IRQHandler
        B LPDTS_WKUP_IRQHandler

        PUBWEAK TIMER0_DEC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER0_DEC_IRQHandler
        B TIMER0_DEC_IRQHandler

        PUBWEAK TIMER7_DEC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER7_DEC_IRQHandler
        B TIMER7_DEC_IRQHandler

        PUBWEAK TIMER1_DEC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER1_DEC_IRQHandler
        B TIMER1_DEC_IRQHandler

        PUBWEAK TIMER2_DEC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER2_DEC_IRQHandler
        B TIMER2_DEC_IRQHandler

        PUBWEAK TIMER3_DEC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER3_DEC_IRQHandler
        B TIMER3_DEC_IRQHandler

        PUBWEAK TIMER4_DEC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER4_DEC_IRQHandler
        B TIMER4_DEC_IRQHandler

        PUBWEAK TIMER22_DEC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER22_DEC_IRQHandler
        B TIMER22_DEC_IRQHandler

        PUBWEAK TIMER23_DEC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER23_DEC_IRQHandler
        B TIMER23_DEC_IRQHandler

        PUBWEAK TIMER30_DEC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER30_DEC_IRQHandler
        B TIMER30_DEC_IRQHandler

        PUBWEAK TIMER31_DEC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIMER31_DEC_IRQHandler
        B TIMER31_DEC_IRQHandler

        END
