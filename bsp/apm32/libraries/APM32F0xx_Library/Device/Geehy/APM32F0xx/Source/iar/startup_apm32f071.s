;/*!
; * @file       startup_apm32f071.s
; *
; * @brief      APM32F071 devices vector table for EWARM toolchain.
; *
; * @version    V1.0.0
; *
; * @date       2022-02-21
; *
; * @attention
; *
; *  Copyright (C) 2020-2022 Geehy Semiconductor
; *
; *  You may not use this file except in compliance with the
; *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
; *
; *  The program is only for reference, which is distributed in the hope
; *  that it will be useful and instructional for customers to develop
; *  their software. Unless required by applicable law or agreed to in
; *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
; *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
; *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
; *  and limitations under the License.
; */

        MODULE  ?cstartup

        SECTION CSTACK:DATA:NOROOT(3)

        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        EXTERN  SystemInit
        PUBLIC  __vector_table

        DATA
__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler                  ; Reset Handler

        DCD     NMI_Handler                    ; NMI Handler
        DCD     HardFault_Handler              ; Hard Fault Handler
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     SVC_Handler                    ; SVCall Handler
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     PendSV_Handler                 ; PendSV Handler
        DCD     SysTick_Handler                ; SysTick Handler

        ; External Interrupts
        DCD     WWDT_IRQHandler                ; Window Watchdog
        DCD     PVD_VDDIO2_IRQHandler          ; PVD and VDDIO2 through EINT Line detect
        DCD     RTC_IRQHandler                 ; RTC through EXTI Line
        DCD     FLASH_IRQHandler               ; FLASH
        DCD     RCM_IRQHandler                 ; RCC
        DCD     EINT0_1_IRQHandler             ; EINT Line 0 and 1
        DCD     EINT2_3_IRQHandler             ; EINT Line 2 and 3
        DCD     EINT4_15_IRQHandler            ; EINT Line 4 to 15
        DCD     TSC_IRQHandler                 ; TSC
        DCD     DMA1_CH1_IRQHandler            ; DMA1 Channel 1
        DCD     DMA1_CH2_3_IRQHandler          ; DMA1 Channel 2 and Channel 3
        DCD     DMA1_CH4_5_6_7_IRQHandler      ; DMA1 Channel 4, Channel 5, Channel 6 and Channel 7
        DCD     ADC1_COMP_IRQHandler           ; ADC1, COMP1 and COMP2
        DCD     TMR1_BRK_UP_TRG_COM_IRQHandler ; TMR1 Break, Update, Trigger and Commutation
        DCD     TMR1_CC_IRQHandler             ; TMR1 Capture Compare
        DCD     TMR2_IRQHandler                ; TMR2
        DCD     TMR3_IRQHandler                ; TMR3
        DCD     TMR6_DAC_IRQHandler            ; TMR6 and DAC
        DCD     TMR7_IRQHandler                ; TMR7
        DCD     TMR14_IRQHandler               ; TMR14
        DCD     TMR15_IRQHandler               ; TMR15
        DCD     TMR16_IRQHandler               ; TMR16
        DCD     TMR17_IRQHandler               ; TMR17
        DCD     I2C1_IRQHandler                ; I2C1
        DCD     I2C2_IRQHandler                ; I2C2
        DCD     SPI1_IRQHandler                ; SPI1
        DCD     SPI2_IRQHandler                ; SPI2
        DCD     USART1_IRQHandler              ; USART1
        DCD     USART2_IRQHandler              ; USART2
        DCD     USART3_4_IRQHandler            ; USART3 and USART4
        DCD     CEC_IRQHandler                 ; CEC

        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:NOROOT:REORDER(2)
Reset_Handler

        LDR     R0, =sfe(CSTACK)          ; set stack pointer
        MSR     MSP, R0

        LDR R0,=0x00000004
        LDR R1, [R0]
        LSRS R1, R1, #24
        LDR R2,=0x1F
        CMP R1, R2

        BNE ApplicationStart

        LDR R0,=0x40021018
        LDR R1,=0x00000001
        STR R1, [R0]

        LDR R0,=0x40010000
        LDR R1,=0x00000000
        STR R1, [R0]
ApplicationStart
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

        PUBWEAK SVC_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SVC_Handler
        B SVC_Handler

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
PendSV_Handler
        B PendSV_Handler

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SysTick_Handler
        B SysTick_Handler

        PUBWEAK WWDT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
WWDT_IRQHandler
        B WWDT_IRQHandler

        PUBWEAK PVD_VDDIO2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
PVD_VDDIO2_IRQHandler
        B PVD_VDDIO2_IRQHandler

        PUBWEAK RTC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTC_IRQHandler
        B RTC_IRQHandler

        PUBWEAK FLASH_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FLASH_IRQHandler
        B FLASH_IRQHandler

        PUBWEAK RCM_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RCM_IRQHandler
        B RCM_IRQHandler

        PUBWEAK EINT0_1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EINT0_1_IRQHandler
        B EINT0_1_IRQHandler

        PUBWEAK EINT2_3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EINT2_3_IRQHandler
        B EINT2_3_IRQHandler

        PUBWEAK EINT4_15_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EINT4_15_IRQHandler
        B EINT4_15_IRQHandler

        PUBWEAK TSC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TSC_IRQHandler
        B TSC_IRQHandler

        PUBWEAK DMA1_CH1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_CH1_IRQHandler
        B DMA1_CH1_IRQHandler

        PUBWEAK DMA1_CH2_3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_CH2_3_IRQHandler
        B DMA1_CH2_3_IRQHandler

        PUBWEAK DMA1_CH4_5_6_7_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_CH4_5_6_7_IRQHandler
        B DMA1_CH4_5_6_7_IRQHandler

        PUBWEAK ADC1_COMP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC1_COMP_IRQHandler
        B ADC1_COMP_IRQHandler

        PUBWEAK TMR1_BRK_UP_TRG_COM_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TMR1_BRK_UP_TRG_COM_IRQHandler
        B TMR1_BRK_UP_TRG_COM_IRQHandler

        PUBWEAK TMR1_CC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TMR1_CC_IRQHandler
        B TMR1_CC_IRQHandler

        PUBWEAK TMR2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TMR2_IRQHandler
        B TMR2_IRQHandler

        PUBWEAK TMR3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TMR3_IRQHandler
        B TMR3_IRQHandler

        PUBWEAK TMR6_DAC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TMR6_DAC_IRQHandler
        B TMR6_DAC_IRQHandler

        PUBWEAK TMR7_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TMR7_IRQHandler
        B TMR7_IRQHandler

        PUBWEAK TMR14_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TMR14_IRQHandler
        B TMR14_IRQHandler

        PUBWEAK TMR15_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TMR15_IRQHandler
        B TMR15_IRQHandler

        PUBWEAK TMR16_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TMR16_IRQHandler
        B TMR16_IRQHandler

        PUBWEAK TMR17_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TMR17_IRQHandler
        B TMR17_IRQHandler

        PUBWEAK I2C1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C1_IRQHandler
        B I2C1_IRQHandler

        PUBWEAK I2C2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C2_IRQHandler
        B I2C2_IRQHandler

        PUBWEAK SPI1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI1_IRQHandler
        B SPI1_IRQHandler

        PUBWEAK SPI2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI2_IRQHandler
        B SPI2_IRQHandler

        PUBWEAK USART1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART1_IRQHandler
        B USART1_IRQHandler

        PUBWEAK USART2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART2_IRQHandler
        B USART2_IRQHandler

        PUBWEAK USART3_4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART3_4_IRQHandler
        B USART3_4_IRQHandler

        PUBWEAK CEC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CEC_IRQHandler
        B CEC_IRQHandler

        END
