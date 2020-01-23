;*******************************************************************************
; *file       : startup_ES32F027x.s
; *description: ES32F027x Device Startup File
; *author     : Eastsoft MCU Software Team
; *version    : V0.01
; *data       : 12/10/2018
;
; *Copyright (C) 2018 Shanghai Eastsoft Microelectronics Co., Ltd.
; *
; * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
; * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
; * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
; * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
;*******************************************************************************


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

Heap_Size       EQU     0x00000000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


                PRESERVE8
                THUMB


; Vector Table Mapped to Address 0 at Reset

                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors

__Vectors       DCD     __initial_sp               ; Top of Stack
                ; External Interrupts
                DCD     Reset_Handler              ;1, Reset Handler
                DCD     NMI_Handler                ;2, NMI Handler
                DCD     HardFault_Handler           ;3, HARDFAULT Handler
                DCD     0                          ;4, Reserved
                DCD     0                          ;5, Reserved
                DCD     0                          ;6, Reserved
                DCD     0                          ;7, Reserved
                DCD     0                          ;8, Reserved
                DCD     0                          ;9, Reserved
                DCD     0                          ;10, Reserved
                DCD     SVC_Handler                ;11, SVC Handler
                DCD     0                          ;12, Reserved
                DCD     0                          ;13, Reserved
                DCD     PendSV_Handler             ;14, PENDSV Handler
                DCD     SysTick_Handler            ;15, SYSTICK Handler
                DCD     WWDT_IRQHandler            ;16, WWDT IRQHandler
                DCD     PVD_IRQHandler             ;17, PVD IRQHandler
                DCD     RTC_IRQHandler             ;18, RTC IRQHandler
                DCD     LowPowerWakeup_IRQHandler  ;19, LowPowerWakeup IRQHandler
                DCD     0                          ;20, Reserved
                DCD     EXTI0_1_IRQHandler         ;21, EXTI01_1 IRQHandler
                DCD     EXTI2_3_IRQHandler         ;22, EXTI2_3 IRQHandler
                DCD     EXTI4_15_IRQHandler        ;23, EXTI4_15 IRQHandler
                DCD     0                          ;24, Reserved
                DCD     DMA1_CH0_IRQHandler        ;25, DMA1_CH0 IRQHandler
                DCD     DMA1_CH1_2_IRQHandler      ;26, DMA1_CH1_2 IRQHandler
                DCD     DMA1_CH3_5_IRQHandler      ;27, DMA1_CH3_5 IRQHandler
                DCD     ADC_CMP_IRQHandler         ;28, ADC_CMP IRQHandler
                DCD     AD16C4T1_IRQHandler        ;29, AD16C4T1 IRQHandler
                DCD     BS16T1_IRQHandler          ;30, BS16T1 IRQHandler
                DCD     GP32C4T1_IRQHandler        ;31, GP32C4T1 IRQHandler
                DCD     GP16C4T1_IRQHandler        ;32, GP16C4T1 IRQHandler
                DCD     GP16C4T2_IRQHandler        ;33, GP16C4T2 IRQHandler
                DCD     GP16C4T3_IRQHandler        ;34, GP16C4T3 IRQHandler
                DCD     GP16C2T1_IRQHandler        ;35, GP16C2T1 IRQHandler
                DCD     GP16C2T2_IRQHandler        ;36, GP16C2T2 IRQHandler
                DCD     GP16C2T3_IRQHandler        ;37, GP16C2T3 IRQHandler
                DCD     GP16C2T4_IRQHandler        ;38, GP16C2T4 IRQHandler
                DCD     I2C1_IRQHandler            ;39, I2C1 IRQHandler
                DCD     I2C2_IRQHandler            ;40, I2C2 IRQHandler
                DCD     SPI1_IRQHandler            ;41, SPI1 IRQHandler
                DCD     SPI2_IRQHandler            ;42, SPI2 IRQHandler
                DCD     UART1_IRQHandler           ;43, UART1 IRQHandler
                DCD     UART2_IRQHandler           ;44, UART2 IRQHandler
                DCD     UART3_AES_IRQHandler       ;45, UART3_AES IRQHandler
                DCD     SUART1_SUART2_IRQHandler   ;46, SUART1_SUART2 IRQHandler
                DCD     USB_IRQHandler             ;47, USB IRQHandler


                AREA    |.text|, CODE, READONLY


; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler             [WEAK]
                IMPORT  __main
                IMPORT  SystemInit
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP

; Dummy Exception IRQHandlers (infinite loops which can be modified)

NMI_Handler      PROC
            EXPORT  NMI_Handler            [WEAK]
            B       .
            ENDP
HardFault_Handler      PROC
            EXPORT  HardFault_Handler            [WEAK]
            B       .
            ENDP


SVC_Handler      PROC
            EXPORT  SVC_Handler          [WEAK]
            B       .
            ENDP

PendSV_Handler      PROC
            EXPORT  PendSV_Handler       [WEAK]
            B       .
            ENDP
SysTick_Handler      PROC
            EXPORT  SysTick_Handler      [WEAK]
            B       .
            ENDP

Default_Handler PROC



                EXPORT  WWDT_IRQHandler    [WEAK]
                EXPORT  PVD_IRQHandler     [WEAK]
                EXPORT  RTC_IRQHandler     [WEAK]
                EXPORT  LowPowerWakeup_IRQHandler  [WEAK]
                EXPORT  EXTI0_1_IRQHandler    [WEAK]
                EXPORT  EXTI2_3_IRQHandler    [WEAK]
                EXPORT  EXTI4_15_IRQHandler    [WEAK]
                EXPORT  DMA1_CH0_IRQHandler    [WEAK]
                EXPORT  DMA1_CH1_2_IRQHandler    [WEAK]
                EXPORT  DMA1_CH3_5_IRQHandler    [WEAK]
                EXPORT  ADC_CMP_IRQHandler    [WEAK]
                EXPORT  AD16C4T1_IRQHandler   [WEAK]
                EXPORT  BS16T1_IRQHandler     [WEAK]
                EXPORT  GP32C4T1_IRQHandler   [WEAK]
                EXPORT  GP16C4T1_IRQHandler   [WEAK]
                EXPORT  GP16C4T2_IRQHandler   [WEAK]
                EXPORT  GP16C4T3_IRQHandler   [WEAK]
                EXPORT  GP16C2T1_IRQHandler   [WEAK]
                EXPORT  GP16C2T2_IRQHandler   [WEAK]
                EXPORT  GP16C2T3_IRQHandler   [WEAK]
                EXPORT  GP16C2T4_IRQHandler   [WEAK]
                EXPORT  I2C1_IRQHandler    [WEAK]
                EXPORT  I2C2_IRQHandler    [WEAK]
                EXPORT  SPI1_IRQHandler    [WEAK]
                EXPORT  SPI2_IRQHandler    [WEAK]
                EXPORT  UART1_IRQHandler   [WEAK]
                EXPORT  UART2_IRQHandler   [WEAK]
                EXPORT  UART3_AES_IRQHandler     [WEAK]
                EXPORT  SUART1_SUART2_IRQHandler [WEAK]
                EXPORT  USB_IRQHandler     [WEAK]



WWDT_IRQHandler
PVD_IRQHandler
RTC_IRQHandler
LowPowerWakeup_IRQHandler
EXTI0_1_IRQHandler
EXTI2_3_IRQHandler
EXTI4_15_IRQHandler
DMA1_CH0_IRQHandler
DMA1_CH1_2_IRQHandler
DMA1_CH3_5_IRQHandler
ADC_CMP_IRQHandler
AD16C4T1_IRQHandler
BS16T1_IRQHandler
GP32C4T1_IRQHandler
GP16C4T1_IRQHandler
GP16C4T2_IRQHandler
GP16C4T3_IRQHandler
GP16C2T1_IRQHandler
GP16C2T2_IRQHandler
GP16C2T3_IRQHandler
GP16C2T4_IRQHandler
I2C1_IRQHandler
I2C2_IRQHandler
SPI1_IRQHandler
SPI2_IRQHandler
UART1_IRQHandler
UART2_IRQHandler
UART3_AES_IRQHandler
SUART1_SUART2_IRQHandler
USB_IRQHandler


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

__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + Stack_Size)
                LDR     R2, = (Heap_Mem +  Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR

                ALIGN

                ENDIF

                END


