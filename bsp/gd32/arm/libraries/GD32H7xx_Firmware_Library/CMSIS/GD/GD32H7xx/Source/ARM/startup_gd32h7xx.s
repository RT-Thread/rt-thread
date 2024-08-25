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

; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00001000

                AREA    STACK, NOINIT, READWRITE, ALIGN=3
Stack_Mem       SPACE   Stack_Size
__initial_sp


; <h> Heap Configuration
;   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Heap_Size       EQU     0x000000800

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

__Vectors_End

__Vectors_Size  EQU  __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY

;/* reset Handler */
Reset_Handler    PROC
                 EXPORT  Reset_Handler                    [WEAK]
                 IMPORT  SystemInit
                 IMPORT  __main
                 IMPORT |Image$$RW_IRAM1$$RW$$Base|
                     
                 LDR     R0, =|Image$$RW_IRAM1$$RW$$Base|
                 ADD     R1, R0, #0x8000
                 LDR     R2, =0x0
MEM_INIT         STRD    R2, R2, [ R0 ] , #8
                 CMP     R0, R1
                 BNE     MEM_INIT

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
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler                 [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler                  [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler                [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler                       [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler                  [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler                    [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler                   [WEAK]
                B       .
                ENDP                                     

Default_Handler PROC                                      
;               /* external interrupts handler */
                EXPORT  WWDGT_IRQHandler                  [WEAK]
                EXPORT  AVD_LVD_OVD_IRQHandler            [WEAK]
                EXPORT  TAMPER_STAMP_LXTAL_IRQHandler     [WEAK]
                EXPORT  RTC_WKUP_IRQHandler               [WEAK]
                EXPORT  FMC_IRQHandler                    [WEAK]
                EXPORT  RCU_IRQHandler                    [WEAK]
                EXPORT  EXTI0_IRQHandler                  [WEAK]
                EXPORT  EXTI1_IRQHandler                  [WEAK]
                EXPORT  EXTI2_IRQHandler                  [WEAK]
                EXPORT  EXTI3_IRQHandler                  [WEAK]
                EXPORT  EXTI4_IRQHandler                  [WEAK]
                EXPORT  DMA0_Channel0_IRQHandler          [WEAK]
                EXPORT  DMA0_Channel1_IRQHandler          [WEAK]
                EXPORT  DMA0_Channel2_IRQHandler          [WEAK]
                EXPORT  DMA0_Channel3_IRQHandler          [WEAK]
                EXPORT  DMA0_Channel4_IRQHandler          [WEAK]
                EXPORT  DMA0_Channel5_IRQHandler          [WEAK]
                EXPORT  DMA0_Channel6_IRQHandler          [WEAK]
                EXPORT  ADC0_1_IRQHandler                 [WEAK]
                EXPORT  EXTI5_9_IRQHandler                [WEAK]
                EXPORT  TIMER0_BRK_IRQHandler             [WEAK]
                EXPORT  TIMER0_UP_IRQHandler              [WEAK]
                EXPORT  TIMER0_TRG_CMT_IRQHandler         [WEAK]
                EXPORT  TIMER0_Channel_IRQHandler         [WEAK]
                EXPORT  TIMER1_IRQHandler                 [WEAK]
                EXPORT  TIMER2_IRQHandler                 [WEAK]
                EXPORT  TIMER3_IRQHandler                 [WEAK]
                EXPORT  I2C0_EV_IRQHandler                [WEAK]
                EXPORT  I2C0_ER_IRQHandler                [WEAK]
                EXPORT  I2C1_EV_IRQHandler                [WEAK]
                EXPORT  I2C1_ER_IRQHandler                [WEAK]
                EXPORT  SPI0_IRQHandler                   [WEAK]
                EXPORT  SPI1_IRQHandler                   [WEAK]
                EXPORT  USART0_IRQHandler                 [WEAK]
                EXPORT  USART1_IRQHandler                 [WEAK]
                EXPORT  USART2_IRQHandler                 [WEAK]
                EXPORT  EXTI10_15_IRQHandler              [WEAK]
                EXPORT  RTC_Alarm_IRQHandler              [WEAK]
                EXPORT  TIMER7_BRK_IRQHandler             [WEAK]
                EXPORT  TIMER7_UP_IRQHandler              [WEAK]
                EXPORT  TIMER7_TRG_CMT_IRQHandler         [WEAK]
                EXPORT  TIMER7_Channel_IRQHandler         [WEAK]
                EXPORT  DMA0_Channel7_IRQHandler          [WEAK]
                EXPORT  EXMC_IRQHandler                   [WEAK]
                EXPORT  SDIO0_IRQHandler                  [WEAK]
                EXPORT  TIMER4_IRQHandler                 [WEAK]
                EXPORT  SPI2_IRQHandler                   [WEAK]
                EXPORT  UART3_IRQHandler                  [WEAK]
                EXPORT  UART4_IRQHandler                  [WEAK]
                EXPORT  TIMER5_DAC_UDR_IRQHandler         [WEAK]
                EXPORT  TIMER6_IRQHandler                 [WEAK]
                EXPORT  DMA1_Channel0_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel1_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel2_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel3_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel4_IRQHandler          [WEAK]
                EXPORT  ENET0_IRQHandler                  [WEAK]
                EXPORT  ENET0_WKUP_IRQHandler             [WEAK]
                EXPORT  DMA1_Channel5_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel6_IRQHandler          [WEAK]
                EXPORT  DMA1_Channel7_IRQHandler          [WEAK]
                EXPORT  USART5_IRQHandler                 [WEAK]
                EXPORT  I2C2_EV_IRQHandler                [WEAK]
                EXPORT  I2C2_ER_IRQHandler                [WEAK]
                EXPORT  USBHS0_EP1_OUT_IRQHandler         [WEAK]
                EXPORT  USBHS0_EP1_IN_IRQHandler          [WEAK]
                EXPORT  USBHS0_WKUP_IRQHandler            [WEAK]
                EXPORT  USBHS0_IRQHandler                 [WEAK]
                EXPORT  DCI_IRQHandler                    [WEAK]
                EXPORT  CAU_IRQHandler                    [WEAK]
                EXPORT  HAU_TRNG_IRQHandler               [WEAK]
                EXPORT  FPU_IRQHandler                    [WEAK]
                EXPORT  UART6_IRQHandler                  [WEAK]
                EXPORT  UART7_IRQHandler                  [WEAK]
                EXPORT  SPI3_IRQHandler                   [WEAK]
                EXPORT  SPI4_IRQHandler                   [WEAK]
                EXPORT  SPI5_IRQHandler                   [WEAK]
                EXPORT  SAI0_IRQHandler                   [WEAK]
                EXPORT  TLI_IRQHandler                    [WEAK]
                EXPORT  TLI_ER_IRQHandler                 [WEAK]
                EXPORT  IPA_IRQHandler                    [WEAK]
                EXPORT  SAI1_IRQHandler                   [WEAK]
                EXPORT  OSPI0_IRQHandler                  [WEAK]
                EXPORT  I2C3_EV_IRQHandler                [WEAK]
                EXPORT  I2C3_ER_IRQHandler                [WEAK]
                EXPORT  RSPDIF_IRQHandler                 [WEAK]
                EXPORT  DMAMUX_OVR_IRQHandler             [WEAK]
                EXPORT  HPDF_INT0_IRQHandler              [WEAK]
                EXPORT  HPDF_INT1_IRQHandler              [WEAK]
                EXPORT  HPDF_INT2_IRQHandler              [WEAK]
                EXPORT  HPDF_INT3_IRQHandler              [WEAK]
                EXPORT  SAI2_IRQHandler                   [WEAK]
                EXPORT  TIMER14_IRQHandler                [WEAK]
                EXPORT  TIMER15_IRQHandler                [WEAK]
                EXPORT  TIMER16_IRQHandler                [WEAK]
                EXPORT  MDIO_IRQHandler                   [WEAK]
                EXPORT  MDMA_IRQHandler                   [WEAK]
                EXPORT  SDIO1_IRQHandler                  [WEAK]
                EXPORT  HWSEM_IRQHandler                  [WEAK]
                EXPORT  ADC2_IRQHandler                   [WEAK]
                EXPORT  CMP0_1_IRQHandler                 [WEAK]
                EXPORT  CTC_IRQHandler                    [WEAK]
                EXPORT  RAMECCMU_IRQHandler               [WEAK]
                EXPORT  OSPI1_IRQHandler                  [WEAK]
                EXPORT  RTDEC0_IRQHandler                 [WEAK]
                EXPORT  RTDEC1_IRQHandler                 [WEAK]
                EXPORT  FAC_IRQHandler                    [WEAK]
                EXPORT  TMU_IRQHandler                    [WEAK]
                EXPORT  TIMER22_IRQHandler                [WEAK]
                EXPORT  TIMER23_IRQHandler                [WEAK]
                EXPORT  TIMER30_IRQHandler                [WEAK]
                EXPORT  TIMER31_IRQHandler                [WEAK]
                EXPORT  TIMER40_IRQHandler                [WEAK]
                EXPORT  TIMER41_IRQHandler                [WEAK]
                EXPORT  TIMER42_IRQHandler                [WEAK]
                EXPORT  TIMER43_IRQHandler                [WEAK]
                EXPORT  TIMER44_IRQHandler                [WEAK]
                EXPORT  TIMER50_IRQHandler                [WEAK]
                EXPORT  TIMER51_IRQHandler                [WEAK]
                EXPORT  USBHS1_EP1_OUT_IRQHandler         [WEAK]
                EXPORT  USBHS1_EP1_IN_IRQHandler          [WEAK]
                EXPORT  USBHS1_WKUP_IRQHandler            [WEAK]
                EXPORT  USBHS1_IRQHandler                 [WEAK]
                EXPORT  ENET1_IRQHandler                  [WEAK]
                EXPORT  ENET1_WKUP_IRQHandler             [WEAK]
                EXPORT  CAN0_WKUP_IRQHandler              [WEAK]
                EXPORT  CAN0_Message_IRQHandler           [WEAK]
                EXPORT  CAN0_Busoff_IRQHandler            [WEAK]
                EXPORT  CAN0_Error_IRQHandler             [WEAK]
                EXPORT  CAN0_FastError_IRQHandler         [WEAK]
                EXPORT  CAN0_TEC_IRQHandler               [WEAK]
                EXPORT  CAN0_REC_IRQHandler               [WEAK]
                EXPORT  CAN1_WKUP_IRQHandler              [WEAK]
                EXPORT  CAN1_Message_IRQHandler           [WEAK]
                EXPORT  CAN1_Busoff_IRQHandler            [WEAK]
                EXPORT  CAN1_Error_IRQHandler             [WEAK]
                EXPORT  CAN1_FastError_IRQHandler         [WEAK]
                EXPORT  CAN1_TEC_IRQHandler               [WEAK]
                EXPORT  CAN1_REC_IRQHandler               [WEAK]
                EXPORT  CAN2_WKUP_IRQHandler              [WEAK]
                EXPORT  CAN2_Message_IRQHandler           [WEAK]
                EXPORT  CAN2_Busoff_IRQHandler            [WEAK]
                EXPORT  CAN2_Error_IRQHandler             [WEAK]
                EXPORT  CAN2_FastError_IRQHandler         [WEAK]
                EXPORT  CAN2_TEC_IRQHandler               [WEAK]
                EXPORT  CAN2_REC_IRQHandler               [WEAK]
                EXPORT  EFUSE_IRQHandler                  [WEAK]
                EXPORT  I2C0_WKUP_IRQHandler              [WEAK]
                EXPORT  I2C1_WKUP_IRQHandler              [WEAK]
                EXPORT  I2C2_WKUP_IRQHandler              [WEAK]
                EXPORT  I2C3_WKUP_IRQHandler              [WEAK]
                EXPORT  LPDTS_IRQHandler                  [WEAK]
                EXPORT  LPDTS_WKUP_IRQHandler             [WEAK]
                EXPORT  TIMER0_DEC_IRQHandler             [WEAK]
                EXPORT  TIMER7_DEC_IRQHandler             [WEAK]
                EXPORT  TIMER1_DEC_IRQHandler             [WEAK]
                EXPORT  TIMER2_DEC_IRQHandler             [WEAK]
                EXPORT  TIMER3_DEC_IRQHandler             [WEAK]
                EXPORT  TIMER4_DEC_IRQHandler             [WEAK]
                EXPORT  TIMER22_DEC_IRQHandler            [WEAK]
                EXPORT  TIMER23_DEC_IRQHandler            [WEAK]
                EXPORT  TIMER30_DEC_IRQHandler            [WEAK]
                EXPORT  TIMER31_DEC_IRQHandler            [WEAK]

;/* external interrupts handler */
WWDGT_IRQHandler
AVD_LVD_OVD_IRQHandler
TAMPER_STAMP_LXTAL_IRQHandler
RTC_WKUP_IRQHandler
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
EXTI5_9_IRQHandler
TIMER0_BRK_IRQHandler
TIMER0_UP_IRQHandler
TIMER0_TRG_CMT_IRQHandler
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
TIMER7_BRK_IRQHandler
TIMER7_UP_IRQHandler
TIMER7_TRG_CMT_IRQHandler
TIMER7_Channel_IRQHandler
DMA0_Channel7_IRQHandler
EXMC_IRQHandler
SDIO0_IRQHandler
TIMER4_IRQHandler
SPI2_IRQHandler
UART3_IRQHandler
UART4_IRQHandler
TIMER5_DAC_UDR_IRQHandler
TIMER6_IRQHandler
DMA1_Channel0_IRQHandler
DMA1_Channel1_IRQHandler
DMA1_Channel2_IRQHandler
DMA1_Channel3_IRQHandler
DMA1_Channel4_IRQHandler
ENET0_IRQHandler
ENET0_WKUP_IRQHandler
DMA1_Channel5_IRQHandler
DMA1_Channel6_IRQHandler
DMA1_Channel7_IRQHandler
USART5_IRQHandler
I2C2_EV_IRQHandler
I2C2_ER_IRQHandler
USBHS0_EP1_OUT_IRQHandler
USBHS0_EP1_IN_IRQHandler
USBHS0_WKUP_IRQHandler
USBHS0_IRQHandler
DCI_IRQHandler
CAU_IRQHandler
HAU_TRNG_IRQHandler
FPU_IRQHandler
UART6_IRQHandler
UART7_IRQHandler
SPI3_IRQHandler
SPI4_IRQHandler
SPI5_IRQHandler
SAI0_IRQHandler
TLI_IRQHandler
TLI_ER_IRQHandler
IPA_IRQHandler
SAI1_IRQHandler
OSPI0_IRQHandler
I2C3_EV_IRQHandler
I2C3_ER_IRQHandler
RSPDIF_IRQHandler
DMAMUX_OVR_IRQHandler
HPDF_INT0_IRQHandler
HPDF_INT1_IRQHandler
HPDF_INT2_IRQHandler
HPDF_INT3_IRQHandler
SAI2_IRQHandler
TIMER14_IRQHandler
TIMER15_IRQHandler
TIMER16_IRQHandler
MDIO_IRQHandler
MDMA_IRQHandler
SDIO1_IRQHandler
HWSEM_IRQHandler
ADC2_IRQHandler
CMP0_1_IRQHandler
CTC_IRQHandler
RAMECCMU_IRQHandler
OSPI1_IRQHandler
RTDEC0_IRQHandler
RTDEC1_IRQHandler
FAC_IRQHandler
TMU_IRQHandler
TIMER22_IRQHandler
TIMER23_IRQHandler
TIMER30_IRQHandler
TIMER31_IRQHandler
TIMER40_IRQHandler
TIMER41_IRQHandler
TIMER42_IRQHandler
TIMER43_IRQHandler
TIMER44_IRQHandler
TIMER50_IRQHandler
TIMER51_IRQHandler
USBHS1_EP1_OUT_IRQHandler
USBHS1_EP1_IN_IRQHandler
USBHS1_WKUP_IRQHandler
USBHS1_IRQHandler
ENET1_IRQHandler
ENET1_WKUP_IRQHandler
CAN0_WKUP_IRQHandler
CAN0_Message_IRQHandler
CAN0_Busoff_IRQHandler
CAN0_Error_IRQHandler
CAN0_FastError_IRQHandler
CAN0_TEC_IRQHandler
CAN0_REC_IRQHandler
CAN1_WKUP_IRQHandler
CAN1_Message_IRQHandler
CAN1_Busoff_IRQHandler
CAN1_Error_IRQHandler
CAN1_FastError_IRQHandler
CAN1_TEC_IRQHandler
CAN1_REC_IRQHandler
CAN2_WKUP_IRQHandler
CAN2_Message_IRQHandler
CAN2_Busoff_IRQHandler
CAN2_Error_IRQHandler
CAN2_FastError_IRQHandler
CAN2_TEC_IRQHandler
CAN2_REC_IRQHandler
EFUSE_IRQHandler
I2C0_WKUP_IRQHandler
I2C1_WKUP_IRQHandler
I2C2_WKUP_IRQHandler
I2C3_WKUP_IRQHandler
LPDTS_IRQHandler
LPDTS_WKUP_IRQHandler
TIMER0_DEC_IRQHandler
TIMER7_DEC_IRQHandler
TIMER1_DEC_IRQHandler
TIMER2_DEC_IRQHandler
TIMER3_DEC_IRQHandler
TIMER4_DEC_IRQHandler
TIMER22_DEC_IRQHandler
TIMER23_DEC_IRQHandler
TIMER30_DEC_IRQHandler
TIMER31_DEC_IRQHandler

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
                 
__user_initial_stackheap

                 LDR     R0, =  Heap_Mem
                 LDR     R1, =(Stack_Mem + Stack_Size)
                 LDR     R2, = (Heap_Mem +  Heap_Size)
                 LDR     R3, = Stack_Mem
                 BX      LR

                 ALIGN

                 ENDIF

                 END
