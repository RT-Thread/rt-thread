;/**************************************************************************//**
; * @file     startup_CMSDK_CM4.s
; * @brief    CMSIS Cortex-M4 Core Device Startup File for
; *           Device CMSDK_CM4
; * @version  V3.01
; * @date     06. March 2012
; *
; * @note
; * Copyright (C) 2012 ARM Limited. All rights reserved.
; *
; * @par
; * ARM Limited (ARM) is supplying this software for use with Cortex-M
; * processor based microcontrollers.  This file can be freely distributed
; * within development tools that are supporting such ARM based processors.
; *
; * @par
; * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
; * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
; * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
; * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
; *
; ******************************************************************************/

;/*****************************************************************************/
;/* Startup.s: Startup file for ARM Cortex-M4 Device Family                   */
;/*****************************************************************************/
;/*
;//-------- <<< Use Configuration Wizard in Context Menu >>> ------------------
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

Heap_Size       EQU     0x00000200

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors
                EXPORT  __Vectors_End
                EXPORT  __Vectors_Size

__Vectors       DCD     __initial_sp                   ; Top of Stack
                DCD     Reset_Handler                  ; Reset Handler
                DCD     NMI_Handler                    ; NMI Handler
                DCD     HardFault_Handler              ; Hard Fault Handler
                DCD     MemManage_Handler              ; MPU Fault Handler
                DCD     BusFault_Handler               ; Bus Fault Handler
                DCD     UsageFault_Handler             ; Usage Fault Handler
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     0                              ; Reserved
                DCD     SVC_Handler                    ; SVCall Handler
                DCD     DebugMon_Handler               ; Debug Monitor Handler
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
__Vectors_End

__Vectors_Size  EQU     __Vectors_End - __Vectors

                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP


; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler               [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler         [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler          [WEAK]
                B       .
                ENDP
PendSV_Handler\
                PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler\
                PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC
                EXPORT WWDG_Handler               [WEAK]
                EXPORT PVD_Handler                [WEAK]
                EXPORT TAMP_STAMP_Handler         [WEAK]
                EXPORT RTC_Handler                [WEAK]
                EXPORT FLASH_Handler              [WEAK]
                EXPORT RCC_Handler                [WEAK]
                EXPORT EXTI0_Handler              [WEAK]
                EXPORT EXTI1_Handler              [WEAK]
                EXPORT EXTI2_Handler              [WEAK]
                EXPORT EXTI3_Handler              [WEAK]
                EXPORT EXTI4_Handler              [WEAK]
                EXPORT DMA1_CH0_Handler           [WEAK]
                EXPORT DMA1_CH1_Handler           [WEAK]
                EXPORT DMA1_CH2_Handler           [WEAK]
                EXPORT DMA1_CH3_Handler           [WEAK]
                EXPORT DMA1_CH4_Handler           [WEAK]
                EXPORT DMA1_CH5_Handler           [WEAK]
                EXPORT DMA1_CH6_Handler           [WEAK]
                EXPORT ADC_Handler                [WEAK]
                EXPORT CAN1_Handler               [WEAK]
                EXPORT CAN2_Handler               [WEAK]
                EXPORT CAN3_Handler               [WEAK]
                EXPORT CAN4_Handler               [WEAK]
                EXPORT EXTI9_5_Handler            [WEAK]
                EXPORT TIM1_BRK_TIM9_Handler      [WEAK]
                EXPORT TIM1_UP_TIM1O_Handler      [WEAK]
                EXPORT TIM1_TRG_COM_TIM11_Handler [WEAK]
                EXPORT TIM1_CC_Handler            [WEAK]
                EXPORT TIM2_Handler               [WEAK]
                EXPORT TIM3_Handler               [WEAK]
                EXPORT TIM4_Handler               [WEAK]
                EXPORT I2C1_Handler               [WEAK]
                EXPORT I2C2_Handler               [WEAK]
                EXPORT QSPI_Handler               [WEAK]
                EXPORT SPI1_Handler               [WEAK]
                EXPORT SPI2_Handler               [WEAK]
                EXPORT USART1_Handler             [WEAK]
                EXPORT USART2_Handler             [WEAK]
                EXPORT USART3_Handler             [WEAK]
                EXPORT EXTI15_10_Handler          [WEAK]
                EXPORT RTCAlarm_Handler           [WEAK]
                EXPORT OTG_FS_WKUP_Handler        [WEAK]
                EXPORT TIM8_BRK_TIM12_Handler     [WEAK]
                EXPORT TIM8_UP_TIM13_Handler      [WEAK]
                EXPORT TIM8_TRG_COM_TIM14_Handler [WEAK]
                EXPORT TIM8_CC_Handler            [WEAK]
                EXPORT DMA1_CH7_Handler           [WEAK]
                EXPORT FMC_Handler                [WEAK]
                EXPORT SDIO_Handler               [WEAK]
                EXPORT TIM5_Handler               [WEAK]
                EXPORT SPI3_Handler               [WEAK]
                EXPORT UART4_Handler              [WEAK]
                EXPORT UART5_Handler              [WEAK]
                EXPORT TIM6_DAC_Handler           [WEAK]
                EXPORT TIM7_Handler               [WEAK]
                EXPORT DMA2_CH0_Handler           [WEAK]
                EXPORT DMA2_CH1_Handler           [WEAK]
                EXPORT DMA2_CH2_Handler           [WEAK]
                EXPORT DMA2_CH3_Handler           [WEAK]
                EXPORT DMA2_CH4_Handler           [WEAK]
                EXPORT OTG_FS_Handler             [WEAK]
                EXPORT DMA2_CH5_Handler           [WEAK]
                EXPORT DMA2_CH6_Handler           [WEAK]
                EXPORT DMA2_CH7_Handler           [WEAK]
                EXPORT USART6_Handler             [WEAK]
                EXPORT I2C3_Handler               [WEAK]
                EXPORT OTG_HS_EP1_OUT_Handler     [WEAK]
                EXPORT OTG_HS_EP1_IN_Handler      [WEAK]
                EXPORT OTG_HS_WKUP_Handler        [WEAK]
                EXPORT OTG_HS_Handler             [WEAK]
                EXPORT RNG_Handler                [WEAK]
                EXPORT FPU_Handler                [WEAK]
                EXPORT CRS_Handler                [WEAK]
                EXPORT SPDIF_Handler              [WEAK]
                EXPORT SSI_AC97_Handler           [WEAK]
                EXPORT ETH_WKUP_Handler           [WEAK]
                EXPORT LPUART_Handler             [WEAK]
                EXPORT LPTIM_Handler              [WEAK]
                EXPORT ETH_SBD_Handler            [WEAK]
                EXPORT ETH_PERCHTX_Handler        [WEAK]
                EXPORT ETH_PERCHRX_Handler        [WEAK]
                EXPORT EPWM1_Handler              [WEAK]
                EXPORT EPWM1_TZ_Handler           [WEAK]
                EXPORT EPWM2_Handler              [WEAK]
                EXPORT EPWM2_TZ_Handler           [WEAK]
                EXPORT EPWM3_Handler              [WEAK]
                EXPORT EPWM3_TZ_Handler           [WEAK]
                EXPORT EPWM4_Handler              [WEAK]
                EXPORT EPWM4_TZ_Handler           [WEAK]
                EXPORT ECAP_Handler               [WEAK]
                EXPORT EQEP_Handler               [WEAK]
                EXPORT DLL_CAL_Handler            [WEAK]
                EXPORT COMP1_Handler              [WEAK]
                EXPORT COMP2_Handler              [WEAK]
                EXPORT COMP3_Handler              [WEAK]
                EXPORT COMP4_Handler              [WEAK]
                EXPORT COMP5_Handler              [WEAK]
                EXPORT COMP6_Handler              [WEAK]
                EXPORT ICACHE_Handler             [WEAK]
                EXPORT DCACHE_Handler             [WEAK]
                EXPORT UART7_Handler              [WEAK]


WWDG_Handler
PVD_Handler
TAMP_STAMP_Handler
RTC_Handler
FLASH_Handler
RCC_Handler
EXTI0_Handler
EXTI1_Handler
EXTI2_Handler
EXTI3_Handler
EXTI4_Handler
DMA1_CH0_Handler
DMA1_CH1_Handler
DMA1_CH2_Handler
DMA1_CH3_Handler
DMA1_CH4_Handler
DMA1_CH5_Handler
DMA1_CH6_Handler
ADC_Handler
CAN1_Handler
CAN2_Handler
CAN3_Handler
CAN4_Handler
EXTI9_5_Handler
TIM1_BRK_TIM9_Handler
TIM1_UP_TIM1O_Handler
TIM1_TRG_COM_TIM11_Handler
TIM1_CC_Handler
TIM2_Handler
TIM3_Handler
TIM4_Handler
I2C1_Handler
I2C2_Handler
QSPI_Handler
SPI1_Handler
SPI2_Handler
USART1_Handler
USART2_Handler
USART3_Handler
EXTI15_10_Handler
RTCAlarm_Handler
OTG_FS_WKUP_Handler
TIM8_BRK_TIM12_Handler
TIM8_UP_TIM13_Handler 
TIM8_TRG_COM_TIM14_Handler
TIM8_CC_Handler
DMA1_CH7_Handler
FMC_Handler
SDIO_Handler
TIM5_Handler
SPI3_Handler
UART4_Handler
UART5_Handler
TIM6_DAC_Handler
TIM7_Handler
DMA2_CH0_Handler
DMA2_CH1_Handler
DMA2_CH2_Handler
DMA2_CH3_Handler
DMA2_CH4_Handler
OTG_FS_Handler
DMA2_CH5_Handler
DMA2_CH6_Handler
DMA2_CH7_Handler
USART6_Handler
I2C3_Handler
OTG_HS_EP1_OUT_Handler
OTG_HS_EP1_IN_Handler
OTG_HS_WKUP_Handler
OTG_HS_Handler
RNG_Handler
FPU_Handler
CRS_Handler
SPDIF_Handler
SSI_AC97_Handler
ETH_WKUP_Handler
LPUART_Handler
LPTIM_Handler
ETH_SBD_Handler
ETH_PERCHTX_Handler
ETH_PERCHRX_Handler
EPWM1_Handler
EPWM1_TZ_Handler
EPWM2_Handler
EPWM2_TZ_Handler
EPWM3_Handler
EPWM3_TZ_Handler
EPWM4_Handler
EPWM4_TZ_Handler
ECAP_Handler
EQEP_Handler
DLL_CAL_Handler
COMP1_Handler
COMP2_Handler
COMP3_Handler
COMP4_Handler
COMP5_Handler
COMP6_Handler
ICACHE_Handler
DCACHE_Handler
UART7_Handler

                B       .
                ENDP


                ALIGN


; User Initial Stack & Heap

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
