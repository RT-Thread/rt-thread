;*******************************************************************************
;* File Name          : startup_ft32f407xe.s
;* Author             : MCD Application Team
;* Description        : FT32F407xE devices vector table for EWARM toolchain.
;*                      This module performs:
;*                      - Set the initial SP
;*                      - Set the initial PC == __iar_program_start,
;*                      - Set the vector table entries with the exceptions ISR 
;*                        address,
;*                      - Branches to main in the C library (which eventually
;*                        calls main()).
;*                      After Reset the Cortex-M4 processor is in Thread mode,
;*                      priority is Privileged, and the Stack is set to Main.
;*******************************************************************************
;* @attention
;*
;* Copyright (c) 2006-2025 Fremontmicro.
;* All rights reserved.
;*
;* This software component is licensed by FMD under BSD 3-Clause license,
;* the "License"; You may not use this file except in compliance with the
;* License. You may obtain a copy of the License at:
;*                        opensource.org/licenses/BSD-3-Clause
;*
;*******************************************************************************
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
        DCD     Reset_Handler                  ; Reset Handler

        DCD     NMI_Handler                    ; NMI Handler
        DCD     HardFault_Handler              ; Hard Fault Handler
        DCD     MemManage_Handler              ; MemManage_Handler
        DCD     BusFault_Handler               ; BusFault_Handler
        DCD     UsageFault_Handler             ; UsageFault_Handler
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     0                              ; Reserved
        DCD     SVC_Handler                    ; SVCall Handler
        DCD     DebugMon_Handler               ; DebugMon_Handler
        DCD     0                              ; Reserved
        DCD     PendSV_Handler                 ; PendSV Handler
        DCD     SysTick_Handler                ; SysTick Handler

        ; External Interrupts
        DCD     WWDG_Handler                   ; 16+ 0: Window Watchdog
        DCD     PVD_Handler                    ; 16+ 1: PVD PROG VDDIO Handler
        DCD     TAMP_STAMP_Handler             ; 16+ 2: TAMP and STAMP Handler
        DCD     RTC_Handler                    ; 16+ 3: RTC Handler
        DCD     FLASH_Handler                  ; 16+ 4: FLASH Handler
        DCD     RCC_Handler                    ; 16+ 5: RCC Handler
        DCD     EXTI0_Handler                  ; 16+ 6: EXTI 0 handler
        DCD     EXTI1_Handler                  ; 16+ 7: EXTI 1 Handler
        DCD     EXTI2_Handler                  ; 16+ 8: EXTI 2 Handler
        DCD     EXTI3_Handler                  ; 16+ 9: EXTI 3 Handler
        DCD     EXTI4_Handler                  ; 16+10: EXTI 4 Handler
        DCD     DMA1_CH0_Handler               ; 16+11: DMA1 CH0 Handler
        DCD     DMA1_CH1_Handler               ; 16+12: DMA1 CH1 Handler
        DCD     DMA1_CH2_Handler               ; 16+13: DMA1 CH2 Handler
        DCD     DMA1_CH3_Handler               ; 16+14: DMA1 CH3 Handler
        DCD     DMA1_CH4_Handler               ; 16+15: DMA1 CH4 Handler
        DCD     DMA1_CH5_Handler               ; 16+16: DMA1 CH5 Handler
        DCD     DMA1_CH6_Handler               ; 16+17: DMA1 CH6 Handler
        DCD     ADC_Handler                    ; 16+18: ADC  Handler
        DCD     CAN1_Handler                   ; 16+19: FDxCAN1 Handler
        DCD     CAN2_Handler                   ; 16+20: FDxCAN2 Handler
        DCD     CAN3_Handler                   ; 16+21: FDxCAN3 Handler
        DCD     CAN4_Handler                   ; 16+22: FDxCAN4 Handler
        DCD     EXTI9_5_Handler                ; 16+23: EXTI[9:5] Handler
        DCD     TIM1_BRK_TIM9_Handler          ; 16+24: TIM1 BRK and TIM9 Handler
        DCD     TIM1_UP_TIM1O_Handler          ; 16+25: TIM1 UP and TIM10 Handler
        DCD     TIM1_TRG_COM_TIM11_Handler     ; 16+26: TIM1 TRG/COM and TIM10 Hand
        DCD     TIM1_CC_Handler                ; 16+27: TIM1 CC Handler
        DCD     TIM2_Handler                   ; 16+28: TIM2 Handler
        DCD     TIM3_Handler                   ; 16+29: TIM3 Handler
        DCD     TIM4_Handler                   ; 16+30: TIM4 Handler
        DCD     I2C1_Handler                   ; 16+31: I2C1 Handler
        DCD     I2C2_Handler                   ; 16+32: I2C2 Handler
        DCD     QSPI_Handler                   ; 16+33: QSPI Handler
        DCD     SPI1_Handler                   ; 16+34: SPI1 Handler
        DCD     SPI2_Handler                   ; 16+35: SPI2 Handler
        DCD     USART1_Handler                 ; 16+36: USART1 Handler
        DCD     USART2_Handler                 ; 16+37: USART2 Handler
        DCD     USART3_Handler                 ; 16+38: USART3 Handler
        DCD     EXTI15_10_Handler              ; 16+39: EXTI[15:10] Handler
        DCD     RTCAlarm_Handler               ; 16+40: RTC Alarm Handler
        DCD     OTG_FS_WKUP_Handler            ; 16+41: Connect EXTI USB OTG WKUP H
        DCD     TIM8_BRK_TIM12_Handler         ; 16+42: TIM8 BRK and TIM12 Handler
        DCD     TIM8_UP_TIM13_Handler          ; 16+43: TIM8 UP and TIM13 Handler
        DCD     TIM8_TRG_COM_TIM14_Handler     ; 16+44: TIM8 TRG/COM and TIM14 Hand
        DCD     TIM8_CC_Handler                ; 16+45: TIM8 CC Handler
        DCD     DMA1_CH7_Handler               ; 16+46: DMA1 CH7 Handler
        DCD     FMC_Handler                    ; 16+47: FMC Handler
        DCD     SDIO_Handler                   ; 16+48: SDIO Handler
        DCD     TIM5_Handler                   ; 16+49: TIM5 Handler
        DCD     SPI3_Handler                   ; 16+50: SPI3 Handler
        DCD     UART4_Handler                  ; 16+51: UART4 Handler
        DCD     UART5_Handler                  ; 16+52: UART5 Handler
        DCD     TIM6_DAC_Handler               ; 16+53: TIM6 DAC Handler
        DCD     TIM7_Handler                   ; 16+54: TIM7 Handler
        DCD     DMA2_CH0_Handler               ; 16+55: DMA2 CH0 Handler
        DCD     DMA2_CH1_Handler               ; 16+56: DMA2 CH1 Handler
        DCD     DMA2_CH2_Handler               ; 16+57: DMA2 CH2 Handler
        DCD     DMA2_CH3_Handler               ; 16+58: DMA2 CH3 Handler
        DCD     DMA2_CH4_Handler               ; 16+59: DMA2 CH4 Handler
        DCD     OTG_FS_Handler                 ; 16+60: OTG FS Handler
        DCD     DMA2_CH5_Handler               ; 16+61: DMA2 CH5 Handler
        DCD     DMA2_CH6_Handler               ; 16+62: DMA2 CH6 Handler
        DCD     DMA2_CH7_Handler               ; 16+63: DMA2 CH7 Handler
        DCD     USART6_Handler                 ; 16+64: USART6 Handler
        DCD     I2C3_Handler                   ; 16+65: I2C3 Handler
        DCD     OTG_HS_EP1_OUT_Handler         ; 16+66: OTG HS EP1OUT Handler
        DCD     OTG_HS_EP1_IN_Handler          ; 16+67: OTG HS EP1IN Handler
        DCD     OTG_HS_WKUP_Handler            ; 16+68: OTG HS WKUP Handler
        DCD     OTG_HS_Handler                 ; 16+69: OTG HS Handler
        DCD     RNG_Handler                    ; 16+70: RNG Handler
        DCD     FPU_Handler                    ; 16+71: FPU Handler
        DCD     CRS_Handler                    ; 16+72: CRS Handler
        DCD     SPDIF_Handler                  ; 16+73: SPDIF Handler
        DCD     SSI_AC97_Handler               ; 16+74: SSI_AC97 Handler
        DCD     ETH_WKUP_Handler               ; 16+75: ETH_WKUP Handler
        DCD     LPUART_Handler                 ; 16+76: LPUART Handler
        DCD     LPTIM_Handler                  ; 16+77: LPTIM Handler
        DCD     ETH_SBD_Handler                ; 16+78: ETH_SBD Handler
        DCD     ETH_PERCHTX_Handler            ; 16+79: ETH_PERCHTX Handler
        DCD     ETH_PERCHRX_Handler            ; 16+80: ETH_PERCHRX Handler
        DCD     EPWM1_Handler                  ; 16+81: EPWM1 Handler
        DCD     EPWM1_TZ_Handler               ; 16+82: EPWM1 TZ Handler
        DCD     EPWM2_Handler                  ; 16+83: EPWM2 Handler
        DCD     EPWM2_TZ_Handler               ; 16+84: EPWM2 TZ Handler
        DCD     EPWM3_Handler                  ; 16+85: EPWM3 Handler
        DCD     EPWM3_TZ_Handler               ; 16+86: EPWM3 TZ Handler
        DCD     EPWM4_Handler                  ; 16+87: EPWM4 Handler
        DCD     EPWM4_TZ_Handler               ; 16+88: EPWM4 TZ Handler
        DCD     ECAP_Handler                   ; 16+89: ECAP Handler
        DCD     EQEP_Handler                   ; 16+90: EQEP Handler
        DCD     DLL_CAL_Handler                ; 16+91: DLL CAL Handler
        DCD     COMP1_Handler                  ; 16+92: COMP1 Handler
        DCD     COMP2_Handler                  ; 16+93: COMP2 Handler
        DCD     COMP3_Handler                  ; 16+94: COMP3 Handler
        DCD     COMP4_Handler                  ; 16+95: COMP4 Handler
        DCD     COMP5_Handler                  ; 16+96: COMP5 Handler
        DCD     COMP6_Handler                  ; 16+97: COMP6 Handler
        DCD     ICACHE_Handler                 ; 16+98: ICACHE Handler
        DCD     DCACHE_Handler                 ; 16+99: DCACHE Handler
        DCD     UART7_Handler                  ; 16+100: UART7 Handler

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

        PUBWEAK WWDG_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
WWDG_Handler
        B WWDG_Handler

        PUBWEAK PVD_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
PVD_Handler
        B PVD_Handler

        PUBWEAK TAMP_STAMP_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
TAMP_STAMP_Handler
        B TAMP_STAMP_Handler

        PUBWEAK RTC_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTC_Handler
        B RTC_Handler

        PUBWEAK FLASH_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
FLASH_Handler
        B FLASH_Handler

        PUBWEAK RCC_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
RCC_Handler
        B RCC_Handler

        PUBWEAK EXTI0_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI0_Handler
        B EXTI0_Handler

        PUBWEAK EXTI1_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI1_Handler
        B EXTI1_Handler

        PUBWEAK EXTI2_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI2_Handler
        B EXTI2_Handler

        PUBWEAK EXTI3_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI3_Handler
        B EXTI3_Handler

        PUBWEAK EXTI4_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI4_Handler
        B EXTI4_Handler

        PUBWEAK DMA1_CH0_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_CH0_Handler
        B DMA1_CH0_Handler

        PUBWEAK DMA1_CH1_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_CH1_Handler
        B DMA1_CH1_Handler

        PUBWEAK DMA1_CH2_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_CH2_Handler
        B DMA1_CH2_Handler

        PUBWEAK DMA1_CH3_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_CH3_Handler
        B DMA1_CH3_Handler

        PUBWEAK DMA1_CH4_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_CH4_Handler
        B DMA1_CH4_Handler

        PUBWEAK DMA1_CH5_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_CH5_Handler
        B DMA1_CH5_Handler

        PUBWEAK DMA1_CH6_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_CH6_Handler
        B DMA1_CH6_Handler

        PUBWEAK ADC_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC_Handler
        B ADC_Handler

        PUBWEAK CAN1_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN1_Handler
        B CAN1_Handler

        PUBWEAK CAN2_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN2_Handler
        B CAN2_Handler

        PUBWEAK CAN3_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN3_Handler
        B CAN3_Handler

        PUBWEAK CAN4_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN4_Handler
        B CAN4_Handler

        PUBWEAK EXTI9_5_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI9_5_Handler
        B EXTI9_5_Handler

        PUBWEAK TIM1_BRK_TIM9_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM1_BRK_TIM9_Handler
        B TIM1_BRK_TIM9_Handler

        PUBWEAK TIM1_UP_TIM1O_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM1_UP_TIM1O_Handler
        B TIM1_UP_TIM1O_Handler

        PUBWEAK TIM1_TRG_COM_TIM11_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM1_TRG_COM_TIM11_Handler
        B TIM1_TRG_COM_TIM11_Handler

        PUBWEAK TIM1_CC_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM1_CC_Handler
        B TIM1_CC_Handler

        PUBWEAK TIM2_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM2_Handler
        B TIM2_Handler

        PUBWEAK TIM3_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM3_Handler
        B TIM3_Handler

        PUBWEAK TIM4_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM4_Handler
        B TIM4_Handler

        PUBWEAK I2C1_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C1_Handler
        B I2C1_Handler

        PUBWEAK I2C2_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C2_Handler
        B I2C2_Handler

        PUBWEAK QSPI_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
QSPI_Handler
        B QSPI_Handler

        PUBWEAK SPI1_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI1_Handler
        B SPI1_Handler

        PUBWEAK SPI2_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI2_Handler
        B SPI2_Handler

        PUBWEAK USART1_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART1_Handler
        B USART1_Handler

        PUBWEAK USART2_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART2_Handler
        B USART2_Handler

        PUBWEAK USART3_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART3_Handler
        B USART3_Handler

        PUBWEAK EXTI15_10_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI15_10_Handler
        B EXTI15_10_Handler

        PUBWEAK RTCAlarm_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTCAlarm_Handler
        B RTCAlarm_Handler

        PUBWEAK OTG_FS_WKUP_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
OTG_FS_WKUP_Handler
        B OTG_FS_WKUP_Handler

        PUBWEAK TIM8_BRK_TIM12_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM8_BRK_TIM12_Handler
        B TIM8_BRK_TIM12_Handler

        PUBWEAK TIM8_UP_TIM13_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM8_UP_TIM13_Handler
        B TIM8_UP_TIM13_Handler

        PUBWEAK TIM8_TRG_COM_TIM14_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM8_TRG_COM_TIM14_Handler
        B TIM8_TRG_COM_TIM14_Handler

        PUBWEAK TIM8_CC_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM8_CC_Handler
        B TIM8_CC_Handler

        PUBWEAK DMA1_CH7_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_CH7_Handler
        B DMA1_CH7_Handler

        PUBWEAK FMC_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
FMC_Handler
        B FMC_Handler

        PUBWEAK SDIO_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SDIO_Handler
        B SDIO_Handler
        
        PUBWEAK TIM5_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM5_Handler
        B TIM5_Handler

        PUBWEAK SPI3_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI3_Handler
        B SPI3_Handler

        PUBWEAK UART4_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART4_Handler
        B UART4_Handler

        PUBWEAK UART5_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART5_Handler
        B UART5_Handler

        PUBWEAK TIM6_DAC_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM6_DAC_Handler
        B TIM6_DAC_Handler

        PUBWEAK TIM7_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
TIM7_Handler
        B TIM7_Handler

        PUBWEAK DMA2_CH0_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA2_CH0_Handler
        B DMA2_CH0_Handler

        PUBWEAK DMA2_CH1_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA2_CH1_Handler
        B DMA2_CH1_Handler

        PUBWEAK DMA2_CH2_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA2_CH2_Handler
        B DMA2_CH2_Handler

        PUBWEAK DMA2_CH3_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA2_CH3_Handler
        B DMA2_CH3_Handler

        PUBWEAK DMA2_CH4_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA2_CH4_Handler
        B DMA2_CH4_Handler

        PUBWEAK OTG_FS_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
OTG_FS_Handler
        B OTG_FS_Handler

        PUBWEAK DMA2_CH5_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA2_CH5_Handler
        B DMA2_CH5_Handler

        PUBWEAK DMA2_CH6_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA2_CH6_Handler
        B DMA2_CH6_Handler

        PUBWEAK DMA2_CH7_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA2_CH7_Handler
        B DMA2_CH7_Handler

        PUBWEAK USART6_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART6_Handler
        B USART6_Handler

        PUBWEAK I2C3_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C3_Handler
        B I2C3_Handler

        PUBWEAK OTG_HS_EP1_OUT_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
OTG_HS_EP1_OUT_Handler
        B OTG_HS_EP1_OUT_Handler

        PUBWEAK OTG_HS_EP1_IN_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
OTG_HS_EP1_IN_Handler
        B OTG_HS_EP1_IN_Handler

        PUBWEAK OTG_HS_WKUP_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
OTG_HS_WKUP_Handler
        B OTG_HS_WKUP_Handler

        PUBWEAK OTG_HS_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
OTG_HS_Handler
        B OTG_HS_Handler

        PUBWEAK RNG_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
RNG_Handler
        B RNG_Handler

        PUBWEAK FPU_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
FPU_Handler
        B FPU_Handler

        PUBWEAK CRS_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
CRS_Handler
        B CRS_Handler

        PUBWEAK SPDIF_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPDIF_Handler
        B SPDIF_Handler

        PUBWEAK SSI_AC97_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SSI_AC97_Handler
        B SSI_AC97_Handler

        PUBWEAK ETH_WKUP_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
ETH_WKUP_Handler
        B ETH_WKUP_Handler

        PUBWEAK LPUART_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
LPUART_Handler
        B LPUART_Handler

        PUBWEAK LPTIM_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
LPTIM_Handler
        B LPTIM_Handler

        PUBWEAK ETH_SBD_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
ETH_SBD_Handler
        B ETH_SBD_Handler

        PUBWEAK ETH_PERCHTX_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
ETH_PERCHTX_Handler
        B ETH_PERCHTX_Handler

        PUBWEAK ETH_PERCHRX_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
ETH_PERCHRX_Handler
        B ETH_PERCHRX_Handler

        PUBWEAK EPWM1_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EPWM1_Handler
        B EPWM1_Handler

        PUBWEAK EPWM1_TZ_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EPWM1_TZ_Handler
        B EPWM1_TZ_Handler

        PUBWEAK EPWM2_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EPWM2_Handler
        B EPWM2_Handler

        PUBWEAK EPWM2_TZ_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EPWM2_TZ_Handler
        B EPWM2_TZ_Handler

        PUBWEAK EPWM3_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EPWM3_Handler
        B EPWM3_Handler

        PUBWEAK EPWM3_TZ_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EPWM3_TZ_Handler
        B EPWM3_TZ_Handler

        PUBWEAK EPWM4_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EPWM4_Handler
        B EPWM4_Handler

        PUBWEAK EPWM4_TZ_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EPWM4_TZ_Handler
        B EPWM4_TZ_Handler

        PUBWEAK ECAP_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
ECAP_Handler
        B ECAP_Handler

        PUBWEAK EQEP_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EQEP_Handler
        B EQEP_Handler

        PUBWEAK DLL_CAL_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
DLL_CAL_Handler
        B DLL_CAL_Handler

        PUBWEAK COMP1_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
COMP1_Handler
        B COMP1_Handler

        PUBWEAK COMP2_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
COMP2_Handler
        B COMP2_Handler

        PUBWEAK COMP3_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
COMP3_Handler
        B COMP3_Handler

        PUBWEAK COMP4_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
COMP4_Handler
        B COMP4_Handler

        PUBWEAK COMP5_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
COMP5_Handler
        B COMP5_Handler

        PUBWEAK COMP6_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
COMP6_Handler
        B COMP6_Handler

        PUBWEAK ICACHE_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
ICACHE_Handler
        B ICACHE_Handler

        PUBWEAK DCACHE_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
DCACHE_Handler
        B DCACHE_Handler

        PUBWEAK UART7_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART7_Handler
        B UART7_Handler

        END
;************************ (C) COPYRIGHT Fremontmicro *****END OF FILE*****
