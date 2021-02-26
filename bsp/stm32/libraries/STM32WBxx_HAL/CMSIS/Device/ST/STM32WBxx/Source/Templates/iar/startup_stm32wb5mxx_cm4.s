;******************************************************************************
;* File Name          : startup_stm32wb5mxx_cm4.s
;* Author             : MCD Application Team
;* Description        : M4 core vector table of the STM32WB5Mxx devices for the
;*                      IAR (EWARM) toolchain.
;*
;*                      This module performs:
;*                      - Set the initial SP
;*                      - Set the initial PC == _iar_program_start,
;*                      - Set the vector table entries with the exceptions ISR
;*                        address.
;*                      - Branches to main in the C library (which eventually
;*                        calls main()).
;*                      After Reset the Cortex-M4 processor is in Thread mode,
;*                      priority is Privileged, and the Stack is set to Main.
;******************************************************************************
;* @attention
;*
;* <h2><center>&copy; Copyright (c) 2019 STMicroelectronics. 
;* All rights reserved.</center></h2>
;*
;* This software component is licensed by ST under BSD 3-Clause license,
;* the "License"; You may not use this file except in compliance with the 
;* License. You may obtain a copy of the License at:
;*                        opensource.org/licenses/BSD-3-Clause
;*
;******************************************************************************
;
;
; The modules in this file are included in the libraries, and may be replaced
; by any user-defined modules that define the PUBLIC symbol _program_start or
; a user defined start symbol.
; To override the cstartup defined in the library, simply add your modified
; version to the workbench project.
;
; The vector table is normally located at address 0.
; When debugging in RAM, it can be located in RAM, aligned to at least 2^6.
; The name "__vector_table" has special meaning for C-SPY:
; it is where the SP start value is found, and the NVIC vector
; table register (VTOR) is initialized to this address if != 0.
;
; Cortex-M version
;

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
        DCD     WWDG_IRQHandler                   ; Window WatchDog
        DCD     PVD_PVM_IRQHandler                ; PVD and PVM Interrupt
        DCD     TAMP_STAMP_LSECSS_IRQHandler      ; RTC Tamper, TimeStamp Interrupts and LSECSS Interrupts
        DCD     RTC_WKUP_IRQHandler               ; RTC Wakeup Interrupt
        DCD     FLASH_IRQHandler                  ; FLASH global Interrupt
        DCD     RCC_IRQHandler                    ; RCC Interrupt
        DCD     EXTI0_IRQHandler                  ; EXTI Line 0 Interrupt
        DCD     EXTI1_IRQHandler                  ; EXTI Line 1 Interrupt
        DCD     EXTI2_IRQHandler                  ; EXTI Line 2 Interrupt
        DCD     EXTI3_IRQHandler                  ; EXTI Line 3 Interrup
        DCD     EXTI4_IRQHandler                  ; EXTI Line 4 Interrupt
        DCD     DMA1_Channel1_IRQHandler          ; DMA1 Channel 1 Interrupt
        DCD     DMA1_Channel2_IRQHandler          ; DMA1 Channel 2 Interrupt
        DCD     DMA1_Channel3_IRQHandler          ; DMA1 Channel 3 Interrupt
        DCD     DMA1_Channel4_IRQHandler          ; DMA1 Channel 4 Interrupt
        DCD     DMA1_Channel5_IRQHandler          ; DMA1 Channel 5 Interrupt
        DCD     DMA1_Channel6_IRQHandler          ; DMA1 Channel 6 Interrupt
        DCD     DMA1_Channel7_IRQHandler          ; DMA1 Channel 7 Interrupt
        DCD     ADC1_IRQHandler                   ; ADC1 Interrupt
        DCD     USB_HP_IRQHandler                 ; USB High Priority Interrupt
        DCD     USB_LP_IRQHandler                 ; USB Low Priority Interrupt
        DCD     C2SEV_PWR_C2H_IRQHandler          ; CPU M0+ SEV Interrupt
        DCD     COMP_IRQHandler                   ; COMP1 and COMP2  Interrupts
        DCD     EXTI9_5_IRQHandler                ; EXTI Lines [9:5] Interrupt
        DCD     TIM1_BRK_IRQHandler               ; TIM1 Break Interrupt
        DCD     TIM1_UP_TIM16_IRQHandler          ; TIM1 Update and TIM16 global Interrupts
        DCD     TIM1_TRG_COM_TIM17_IRQHandler     ; TIM1 Trigger and Communication and TIM17 global Interrupts
        DCD     TIM1_CC_IRQHandler                ; TIM1 Capture Compare Interrupt
        DCD     TIM2_IRQHandler                   ; TIM2 Global Interrupt
        DCD     PKA_IRQHandler                    ; PKA Interrupt
        DCD     I2C1_EV_IRQHandler                ; I2C1 Event Interrupt
        DCD     I2C1_ER_IRQHandler                ; I2C1 Error Interrupt
        DCD     I2C3_EV_IRQHandler                ; I2C3 Event Interrupt
        DCD     I2C3_ER_IRQHandler                ; I2C3 Error Interrupt
        DCD     SPI1_IRQHandler                   ; SPI1 Interrupt
        DCD     SPI2_IRQHandler                   ; SPI2 Interrupt
        DCD     USART1_IRQHandler                 ; USART1 Interrupt
        DCD     LPUART1_IRQHandler                ; LPUART1 Interrupt
        DCD     SAI1_IRQHandler                   ; SAI Interrupt
        DCD     TSC_IRQHandler                    ; TSC Interrupt
        DCD     EXTI15_10_IRQHandler              ; EXTI Lines1[15:10 ]Interrupts
        DCD     RTC_Alarm_IRQHandler              ; RTC Alarms (A and B) Interrupt
        DCD     CRS_IRQHandler                    ; CRS interrupt
        DCD     PWR_SOTF_BLEACT_802ACT_RFPHASE_IRQHandler ; WKUP Interrupt from PWR
        DCD     IPCC_C1_RX_IRQHandler             ; IPCC CPU1 RX occupied interrupt
        DCD     IPCC_C1_TX_IRQHandler             ; IPCC CPU1 RX free interrupt
        DCD     HSEM_IRQHandler                   ; HSEM0 Interrupt
        DCD     LPTIM1_IRQHandler                 ; LPTIM1 Interrupt
        DCD     LPTIM2_IRQHandler                 ; LPTIM2 Interrupt
        DCD     LCD_IRQHandler                    ; LCD Interrupt
        DCD     QUADSPI_IRQHandler                ; QUADSPI Interrupt
        DCD     AES1_IRQHandler                   ; AES1 Interrupt
        DCD     AES2_IRQHandler                   ; AES2 Interrupt
        DCD     RNG_IRQHandler                    ; RNG1 Interrupt
        DCD     FPU_IRQHandler                    ; FPU Interrupt
        DCD     DMA2_Channel1_IRQHandler          ; DMA2 Channel 1 Interrupt
        DCD     DMA2_Channel2_IRQHandler          ; DMA2 Channel 2 Interrupt
        DCD     DMA2_Channel3_IRQHandler          ; DMA2 Channel 3 Interrupt
        DCD     DMA2_Channel4_IRQHandler          ; DMA2 Channel 4 Interrupt
        DCD     DMA2_Channel5_IRQHandler          ; DMA2 Channel 5 Interrupt
        DCD     DMA2_Channel6_IRQHandler          ; DMA2 Channel 6 Interrupt
        DCD     DMA2_Channel7_IRQHandler          ; DMA2 Channel 7 Interrupt
        DCD     DMAMUX1_OVR_IRQHandler            ; DMAMUX overrun Interrupt

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:NOROOT:REORDER(2)
Reset_Handler
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

        PUBWEAK WWDG_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
WWDG_IRQHandler
        B WWDG_IRQHandler

        PUBWEAK PVD_PVM_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
PVD_PVM_IRQHandler
        B PVD_PVM_IRQHandler

        PUBWEAK TAMP_STAMP_LSECSS_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TAMP_STAMP_LSECSS_IRQHandler
        B TAMP_STAMP_LSECSS_IRQHandler

        PUBWEAK RTC_WKUP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTC_WKUP_IRQHandler
        B RTC_WKUP_IRQHandler

        PUBWEAK FLASH_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FLASH_IRQHandler
        B FLASH_IRQHandler

        PUBWEAK RCC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RCC_IRQHandler
        B RCC_IRQHandler

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

        PUBWEAK ADC1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC1_IRQHandler
        B ADC1_IRQHandler

        PUBWEAK USB_HP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USB_HP_IRQHandler
        B USB_HP_IRQHandler

        PUBWEAK USB_LP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USB_LP_IRQHandler
        B USB_LP_IRQHandler

        PUBWEAK C2SEV_PWR_C2H_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
C2SEV_PWR_C2H_IRQHandler
        B C2SEV_PWR_C2H_IRQHandler

        PUBWEAK COMP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
COMP_IRQHandler
        B COMP_IRQHandler

        PUBWEAK EXTI9_5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI9_5_IRQHandler
        B EXTI9_5_IRQHandler

        PUBWEAK TIM1_BRK_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM1_BRK_IRQHandler
        B TIM1_BRK_IRQHandler

        PUBWEAK TIM1_UP_TIM16_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM1_UP_TIM16_IRQHandler
        B TIM1_UP_TIM16_IRQHandler

        PUBWEAK TIM1_TRG_COM_TIM17_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM1_TRG_COM_TIM17_IRQHandler
        B TIM1_TRG_COM_TIM17_IRQHandler

        PUBWEAK TIM1_CC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM1_CC_IRQHandler
        B TIM1_CC_IRQHandler

        PUBWEAK TIM2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM2_IRQHandler
        B TIM2_IRQHandler

        PUBWEAK PKA_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
PKA_IRQHandler
        B PKA_IRQHandler

        PUBWEAK I2C1_EV_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C1_EV_IRQHandler
        B I2C1_EV_IRQHandler

        PUBWEAK I2C1_ER_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C1_ER_IRQHandler
        B I2C1_ER_IRQHandler

        PUBWEAK I2C3_EV_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C3_EV_IRQHandler
        B I2C3_EV_IRQHandler

        PUBWEAK I2C3_ER_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C3_ER_IRQHandler
        B I2C3_ER_IRQHandler

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

        PUBWEAK LPUART1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LPUART1_IRQHandler
        B LPUART1_IRQHandler

        PUBWEAK SAI1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SAI1_IRQHandler
        B SAI1_IRQHandler

        PUBWEAK TSC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
TSC_IRQHandler
        B TSC_IRQHandler

        PUBWEAK EXTI15_10_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI15_10_IRQHandler
        B EXTI15_10_IRQHandler

        PUBWEAK RTC_Alarm_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTC_Alarm_IRQHandler
        B RTC_Alarm_IRQHandler

        PUBWEAK CRS_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
CRS_IRQHandler
        B CRS_IRQHandler

        PUBWEAK PWR_SOTF_BLEACT_802ACT_RFPHASE_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
PWR_SOTF_BLEACT_802ACT_RFPHASE_IRQHandler
        B PWR_SOTF_BLEACT_802ACT_RFPHASE_IRQHandler

        PUBWEAK IPCC_C1_RX_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
IPCC_C1_RX_IRQHandler
        B IPCC_C1_RX_IRQHandler

        PUBWEAK IPCC_C1_TX_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
IPCC_C1_TX_IRQHandler
        B IPCC_C1_TX_IRQHandler

        PUBWEAK HSEM_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
HSEM_IRQHandler
        B HSEM_IRQHandler

        PUBWEAK LPTIM1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LPTIM1_IRQHandler
        B LPTIM1_IRQHandler

        PUBWEAK LPTIM2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LPTIM2_IRQHandler
        B LPTIM2_IRQHandler

        PUBWEAK LCD_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LCD_IRQHandler
        B LCD_IRQHandler

        PUBWEAK QUADSPI_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
QUADSPI_IRQHandler
        B QUADSPI_IRQHandler

        PUBWEAK AES1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
AES1_IRQHandler
        B AES1_IRQHandler

        PUBWEAK AES2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
AES2_IRQHandler
        B AES2_IRQHandler

        PUBWEAK RNG_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RNG_IRQHandler
        B RNG_IRQHandler

        PUBWEAK FPU_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
FPU_IRQHandler
        B FPU_IRQHandler

        PUBWEAK DMA2_Channel1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA2_Channel1_IRQHandler
        B DMA2_Channel1_IRQHandler

        PUBWEAK DMA2_Channel2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA2_Channel2_IRQHandler
        B DMA2_Channel2_IRQHandler

        PUBWEAK DMA2_Channel3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA2_Channel3_IRQHandler
        B DMA2_Channel3_IRQHandler

        PUBWEAK DMA2_Channel4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA2_Channel4_IRQHandler
        B DMA2_Channel4_IRQHandler

        PUBWEAK DMA2_Channel5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA2_Channel5_IRQHandler
        B DMA2_Channel5_IRQHandler

        PUBWEAK DMA2_Channel6_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA2_Channel6_IRQHandler
        B DMA2_Channel6_IRQHandler

        PUBWEAK DMA2_Channel7_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA2_Channel7_IRQHandler
        B DMA2_Channel7_IRQHandler

        PUBWEAK DMAMUX1_OVR_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMAMUX1_OVR_IRQHandler
        B DMAMUX1_OVR_IRQHandler

        END

;************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE*****
