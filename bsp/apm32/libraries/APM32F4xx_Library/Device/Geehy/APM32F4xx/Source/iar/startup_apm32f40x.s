;/*!
; * @file        startup_apm32f40x.s
; *
; * @brief       CMSIS Cortex-M4 based Core Device Startup File for Device startup_apm32f40x
; *
; * @version     V1.0.2
; *
; * @date        2022-06-23
; *
; * @attention
; *
; *  Copyright (C) 2021-2022 Geehy Semiconductor
; *
; *  You may not use this file except in compliance with the
; *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
; *
; *  The program is only for reference, which is distributed in the hope
; *  that it will be usefull and instructional for customers to develop
; *  their software. Unless required by applicable law or agreed to in
; *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
; *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
; *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
; *  and limitations under the License.
; */

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table

        DATA
__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler             ; Reset Handler

                DCD     NMI_Handler                ; NMI Handler
                DCD     HardFault_Handler          ; Hard Fault Handler
                DCD     MemManage_Handler          ; MPU Fault Handler
                DCD     BusFault_Handler           ; Bus Fault Handler
                DCD     UsageFault_Handler         ; Usage Fault Handler
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     0                          ; Reserved
                DCD     SVC_Handler                ; SVCall Handler
                DCD     DebugMon_Handler           ; Debug Monitor Handler
                DCD     0                          ; Reserved
                DCD     PendSV_Handler             ; PendSV Handler
                DCD     SysTick_Handler            ; SysTick Handler

                ; External Interrupts
                DCD     WWDT_IRQHandler                 ; Window WatchDog
                DCD     PVD_IRQHandler                  ; PVD through EINT Line detection
                DCD     TAMP_STAMP_IRQHandler           ; Tamper and TimeStamps through the EINT line
                DCD     RTC_WKUP_IRQHandler             ; RTC Wakeup through the EINT line
                DCD     FLASH_IRQHandler                ; FLASH
                DCD     RCM_IRQHandler                  ; RCM
                DCD     EINT0_IRQHandler                ; EINT Line0
                DCD     EINT1_IRQHandler                ; EINT Line1
                DCD     EINT2_IRQHandler                ; EINT Line2
                DCD     EINT3_IRQHandler                ; EINT Line3
                DCD     EINT4_IRQHandler                ; EINT Line4
                DCD     DMA1_STR0_IRQHandler            ; DMA1 Stream 0
                DCD     DMA1_STR1_IRQHandler            ; DMA1 Stream 1
                DCD     DMA1_STR2_IRQHandler            ; DMA1 Stream 2
                DCD     DMA1_STR3_IRQHandler            ; DMA1 Stream 3
                DCD     DMA1_STR4_IRQHandler            ; DMA1 Stream 4
                DCD     DMA1_STR5_IRQHandler            ; DMA1 Stream 5
                DCD     DMA1_STR6_IRQHandler            ; DMA1 Stream 6
                DCD     ADC_IRQHandler                  ; ADC1, ADC2 and ADC3s
                DCD     CAN1_TX_IRQHandler              ; CAN1 TX
                DCD     CAN1_RX0_IRQHandler             ; CAN1 RX0
                DCD     CAN1_RX1_IRQHandler             ; CAN1 RX1
                DCD     CAN1_SCE_IRQHandler             ; CAN1 SCE
                DCD     EINT9_5_IRQHandler              ; External Line[9:5]s
                DCD     TMR1_BRK_TMR9_IRQHandler        ; TMR1 Break and TMR9
                DCD     TMR1_UP_TMR10_IRQHandler        ; TMR1 Update and TMR10
                DCD     TMR1_TRG_COM_TMR11_IRQHandler   ; TMR1 Trigger and Commutation and TMR11
                DCD     TMR1_CC_IRQHandler              ; TMR1 Capture Compare
                DCD     TMR2_IRQHandler                 ; TMR2
                DCD     TMR3_IRQHandler                 ; TMR3
                DCD     TMR4_IRQHandler                 ; TMR4
                DCD     I2C1_EV_IRQHandler              ; I2C1 Event
                DCD     I2C1_ER_IRQHandler              ; I2C1 Error
                DCD     I2C2_EV_IRQHandler              ; I2C2 Event
                DCD     I2C2_ER_IRQHandler              ; I2C2 Error
                DCD     SPI1_IRQHandler                 ; SPI1
                DCD     SPI2_IRQHandler                 ; SPI2
                DCD     USART1_IRQHandler               ; USART1
                DCD     USART2_IRQHandler               ; USART2
                DCD     USART3_IRQHandler               ; USART3
                DCD     EINT15_10_IRQHandler            ; External Line[15:10]s
                DCD     RTC_Alarm_IRQHandler            ; RTC Alarm (A and B) through EINT Line
                DCD     OTG_FS_WKUP_IRQHandler          ; OTG_FS Wakeup through EINT line
                DCD     TMR8_BRK_TMR12_IRQHandler       ; TMR8 Break and TMR12
                DCD     TMR8_UP_TMR13_IRQHandler        ; TMR8 Update and TMR13
                DCD     TMR8_TRG_COM_TMR14_IRQHandler   ; TMR8 Trigger and Commutation and TMR14
                DCD     TMR8_CC_IRQHandler              ; TMR8 Capture Compare
                DCD     DMA1_STR7_IRQHandler            ; DMA1 Stream 7
                DCD     EMMC_IRQHandler                 ; EMMC
                DCD     SDIO_IRQHandler                 ; SDIO
                DCD     TMR5_IRQHandler                 ; TMR5
                DCD     SPI3_IRQHandler                 ; SPI3
                DCD     UART4_IRQHandler                ; UART4
                DCD     UART5_IRQHandler                ; UART5
                DCD     TMR6_DAC_IRQHandler             ; TMR6 and DAC1&2 underrun errors
                DCD     TMR7_IRQHandler                 ; TMR7
                DCD     DMA2_STR0_IRQHandler            ; DMA2 Stream 0
                DCD     DMA2_STR1_IRQHandler            ; DMA2 Stream 1
                DCD     DMA2_STR2_IRQHandler            ; DMA2 Stream 2
                DCD     DMA2_STR3_IRQHandler            ; DMA2 Stream 3
                DCD     DMA2_STR4_IRQHandler            ; DMA2 Stream 4
                DCD     ETH_IRQHandler                  ; Ethernet
                DCD     ETH_WKUP_IRQHandler             ; Ethernet Wakeup through EINT line
                DCD     CAN2_TX_IRQHandler              ; CAN2 TX
                DCD     CAN2_RX0_IRQHandler             ; CAN2 RX0
                DCD     CAN2_RX1_IRQHandler             ; CAN2 RX1
                DCD     CAN2_SCE_IRQHandler             ; CAN2 SCE
                DCD     OTG_FS_IRQHandler               ; OTG_FS
                DCD     DMA2_STR5_IRQHandler            ; DMA2 Stream 5
                DCD     DMA2_STR6_IRQHandler            ; DMA2 Stream 6
                DCD     DMA2_STR7_IRQHandler            ; DMA2 Stream 7
                DCD     USART6_IRQHandler               ; USART6
                DCD     I2C3_EV_IRQHandler              ; I2C3 event
                DCD     I2C3_ER_IRQHandler              ; I2C3 error
                DCD     OTG_HS1_EP1_OUT_IRQHandler      ; OTG_HS1 End Point 1 Out
                DCD     OTG_HS1_EP1_IN_IRQHandler       ; OTG_HS1 End Point 1 In
                DCD     OTG_HS1_WKUP_IRQHandler         ; OTG_HS1 Wakeup through EINT
                DCD     OTG_HS1_IRQHandler              ; OTG_HS1
                DCD     DCI_IRQHandler                  ; DCI
                DCD     0                               ; Reserved
                DCD     0                               ; Reserved
                DCD     FPU_IRQHandler                  ; FPU
                DCD     SM3_IRQHandler                  ; SM3
                DCD     SM4_IRQHandler                  ; SM4
                DCD     BN_IRQHandler                   ; BN

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB
        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler

        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0

        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
        B NMI_Handler

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
HardFault_Handler
        B HardFault_Handler

        PUBWEAK MemManage_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
MemManage_Handler
        B MemManage_Handler

        PUBWEAK BusFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BusFault_Handler
        B BusFault_Handler

        PUBWEAK UsageFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
UsageFault_Handler
        B UsageFault_Handler

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SVC_Handler
        B SVC_Handler

        PUBWEAK DebugMon_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
DebugMon_Handler
        B DebugMon_Handler

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PendSV_Handler
        B PendSV_Handler

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SysTick_Handler
        B SysTick_Handler

        PUBWEAK WWDT_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
WWDT_IRQHandler
        B WWDT_IRQHandler

        PUBWEAK PVD_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
PVD_IRQHandler
        B PVD_IRQHandler

        PUBWEAK TAMP_STAMP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TAMP_STAMP_IRQHandler
        B TAMP_STAMP_IRQHandler

        PUBWEAK RTC_WKUP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RTC_WKUP_IRQHandler
        B RTC_WKUP_IRQHandler

        PUBWEAK FLASH_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FLASH_IRQHandler
        B FLASH_IRQHandler

        PUBWEAK RCM_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RCM_IRQHandler
        B RCM_IRQHandler

        PUBWEAK EINT0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EINT0_IRQHandler
        B EINT0_IRQHandler

        PUBWEAK EINT1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EINT1_IRQHandler
        B EINT1_IRQHandler

        PUBWEAK EINT2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EINT2_IRQHandler
        B EINT2_IRQHandler

        PUBWEAK EINT3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EINT3_IRQHandler
        B EINT3_IRQHandler

        PUBWEAK EINT4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EINT4_IRQHandler
        B EINT4_IRQHandler

        PUBWEAK DMA1_STR0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_STR0_IRQHandler
        B DMA1_STR0_IRQHandler

        PUBWEAK DMA1_STR1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_STR1_IRQHandler
        B DMA1_STR1_IRQHandler

        PUBWEAK DMA1_STR2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_STR2_IRQHandler
        B DMA1_STR2_IRQHandler

        PUBWEAK DMA1_STR3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_STR3_IRQHandler
        B DMA1_STR3_IRQHandler

        PUBWEAK DMA1_STR4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_STR4_IRQHandler
        B DMA1_STR4_IRQHandler

        PUBWEAK DMA1_STR5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_STR5_IRQHandler
        B DMA1_STR5_IRQHandler

        PUBWEAK DMA1_STR6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_STR6_IRQHandler
        B DMA1_STR6_IRQHandler

        PUBWEAK ADC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ADC_IRQHandler
        B ADC_IRQHandler

        PUBWEAK CAN1_TX_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CAN1_TX_IRQHandler
        B CAN1_TX_IRQHandler

        PUBWEAK CAN1_RX0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CAN1_RX0_IRQHandler
        B CAN1_RX0_IRQHandler

        PUBWEAK CAN1_RX1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CAN1_RX1_IRQHandler
        B CAN1_RX1_IRQHandler

        PUBWEAK CAN1_SCE_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CAN1_SCE_IRQHandler
        B CAN1_SCE_IRQHandler

        PUBWEAK EINT9_5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EINT9_5_IRQHandler
        B EINT9_5_IRQHandler

        PUBWEAK TMR1_BRK_TMR9_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR1_BRK_TMR9_IRQHandler
        B TMR1_BRK_TMR9_IRQHandler

        PUBWEAK TMR1_UP_TMR10_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR1_UP_TMR10_IRQHandler
        B TMR1_UP_TMR10_IRQHandler

        PUBWEAK TMR1_TRG_COM_TMR11_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR1_TRG_COM_TMR11_IRQHandler
        B TMR1_TRG_COM_TMR11_IRQHandler

        PUBWEAK TMR1_CC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR1_CC_IRQHandler
        B TMR1_CC_IRQHandler

        PUBWEAK TMR2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR2_IRQHandler
        B TMR2_IRQHandler

        PUBWEAK TMR3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR3_IRQHandler
        B TMR3_IRQHandler

        PUBWEAK TMR4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR4_IRQHandler
        B TMR4_IRQHandler

        PUBWEAK I2C1_EV_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C1_EV_IRQHandler
        B I2C1_EV_IRQHandler

        PUBWEAK I2C1_ER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C1_ER_IRQHandler
        B I2C1_ER_IRQHandler

        PUBWEAK I2C2_EV_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C2_EV_IRQHandler
        B I2C2_EV_IRQHandler

        PUBWEAK I2C2_ER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C2_ER_IRQHandler
        B I2C2_ER_IRQHandler

        PUBWEAK SPI1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI1_IRQHandler
        B SPI1_IRQHandler

        PUBWEAK SPI2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI2_IRQHandler
        B SPI2_IRQHandler

        PUBWEAK USART1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART1_IRQHandler
        B USART1_IRQHandler

        PUBWEAK USART2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART2_IRQHandler
        B USART2_IRQHandler

        PUBWEAK USART3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART3_IRQHandler
        B USART3_IRQHandler

        PUBWEAK EINT15_10_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EINT15_10_IRQHandler
        B EINT15_10_IRQHandler

        PUBWEAK RTC_Alarm_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
RTC_Alarm_IRQHandler
        B RTC_Alarm_IRQHandler

        PUBWEAK OTG_FS_WKUP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
OTG_FS_WKUP_IRQHandler
        B OTG_FS_WKUP_IRQHandler

        PUBWEAK TMR8_BRK_TMR12_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR8_BRK_TMR12_IRQHandler
        B TMR8_BRK_TMR12_IRQHandler

        PUBWEAK TMR8_UP_TMR13_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR8_UP_TMR13_IRQHandler
        B TMR8_UP_TMR13_IRQHandler

        PUBWEAK TMR8_TRG_COM_TMR14_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR8_TRG_COM_TMR14_IRQHandler
        B TMR8_TRG_COM_TMR14_IRQHandler

        PUBWEAK TMR8_CC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR8_CC_IRQHandler
        B TMR8_CC_IRQHandler

        PUBWEAK DMA1_STR7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA1_STR7_IRQHandler
        B DMA1_STR7_IRQHandler

        PUBWEAK EMMC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
EMMC_IRQHandler
        B EMMC_IRQHandler

        PUBWEAK SDIO_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SDIO_IRQHandler
        B SDIO_IRQHandler

        PUBWEAK TMR5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR5_IRQHandler
        B TMR5_IRQHandler

        PUBWEAK SPI3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SPI3_IRQHandler
        B SPI3_IRQHandler

        PUBWEAK UART4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
UART4_IRQHandler
        B UART4_IRQHandler

        PUBWEAK UART5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
UART5_IRQHandler
        B UART5_IRQHandler

        PUBWEAK TMR6_DAC_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR6_DAC_IRQHandler
        B TMR6_DAC_IRQHandler

        PUBWEAK TMR7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
TMR7_IRQHandler
        B TMR7_IRQHandler

        PUBWEAK DMA2_STR0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_STR0_IRQHandler
        B DMA2_STR0_IRQHandler

        PUBWEAK DMA2_STR1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_STR1_IRQHandler
        B DMA2_STR1_IRQHandler

        PUBWEAK DMA2_STR2_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_STR2_IRQHandler
        B DMA2_STR2_IRQHandler

        PUBWEAK DMA2_STR3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_STR3_IRQHandler
        B DMA2_STR3_IRQHandler

        PUBWEAK DMA2_STR4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_STR4_IRQHandler
        B DMA2_STR4_IRQHandler

        PUBWEAK ETH_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ETH_IRQHandler
        B ETH_IRQHandler

        PUBWEAK ETH_WKUP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
ETH_WKUP_IRQHandler
        B ETH_WKUP_IRQHandler

        PUBWEAK CAN2_TX_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CAN2_TX_IRQHandler
        B CAN2_TX_IRQHandler

        PUBWEAK CAN2_RX0_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CAN2_RX0_IRQHandler
        B CAN2_RX0_IRQHandler

        PUBWEAK CAN2_RX1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CAN2_RX1_IRQHandler
        B CAN2_RX1_IRQHandler

        PUBWEAK CAN2_SCE_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
CAN2_SCE_IRQHandler
        B CAN2_SCE_IRQHandler

        PUBWEAK OTG_FS_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
OTG_FS_IRQHandler
        B OTG_FS_IRQHandler

        PUBWEAK DMA2_STR5_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_STR5_IRQHandler
        B DMA2_STR5_IRQHandler

        PUBWEAK DMA2_STR6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_STR6_IRQHandler
        B DMA2_STR6_IRQHandler

        PUBWEAK DMA2_STR7_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DMA2_STR7_IRQHandler
        B DMA2_STR7_IRQHandler

        PUBWEAK USART6_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
USART6_IRQHandler
        B USART6_IRQHandler

        PUBWEAK I2C3_EV_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C3_EV_IRQHandler
        B I2C3_EV_IRQHandler

        PUBWEAK I2C3_ER_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
I2C3_ER_IRQHandler
        B I2C3_ER_IRQHandler

        PUBWEAK OTG_HS1_EP1_OUT_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
OTG_HS1_EP1_OUT_IRQHandler
        B OTG_HS1_EP1_OUT_IRQHandler

        PUBWEAK OTG_HS1_EP1_IN_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
OTG_HS1_EP1_IN_IRQHandler
        B OTG_HS1_EP1_IN_IRQHandler

        PUBWEAK OTG_HS1_WKUP_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
OTG_HS1_WKUP_IRQHandler
        B OTG_HS1_WKUP_IRQHandler

        PUBWEAK OTG_HS1_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
OTG_HS1_IRQHandler
        B OTG_HS1_IRQHandler

        PUBWEAK DCI_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
DCI_IRQHandler
        B DCI_IRQHandler

        PUBWEAK FPU_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
FPU_IRQHandler
        B FPU_IRQHandler

        PUBWEAK SM3_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SM3_IRQHandler
        B SM3_IRQHandler

        PUBWEAK SM4_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
SM4_IRQHandler
        B SM4_IRQHandler

        PUBWEAK BN_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
BN_IRQHandler
        B BN_IRQHandler

        END
