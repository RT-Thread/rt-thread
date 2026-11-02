;/***********************************************************************
; * $Id: startup_LPC43xx_M0.s 6473 2011-02-16 17:40:54Z nxp27266 $
; *
; * Project: LPC43xx CMSIS Package
; *
; * Description: Cortex-M0 Core Device Startup File for the NXP LPC43xx
; *              Device Series.
; *
; * Copyright(C) 2011, NXP Semiconductor
; * All rights reserved.
; *
; *                                                      modified by KEIL
; ***********************************************************************
; * Software that is described herein is for illustrative purposes only
; * which provides customers with programming information regarding the
; * products. This software is supplied "AS IS" without any warranties.
; * NXP Semiconductors assumes no responsibility or liability for the
; * use of the software, conveys no license or title under any patent,
; * copyright, or mask work right to the product. NXP Semiconductors
; * reserves the right to make changes in the software without
; * notification. NXP Semiconductors also make no representation or
; * warranty that such application will be suitable for the specified
; * use without further testing or modification.
; **********************************************************************/

; <h> Stack Configuration
;   <o> Stack Size (in Bytes) <0x0-0xFFFFFFFF:8>
; </h>

Stack_Size      EQU     0x00000200

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

Sign_Value      EQU     0x5A5A5A5A

__Vectors       DCD     __initial_sp                      ; 0 Top of Stack
                DCD     Reset_Handler                  ; 1 Reset Handler
                DCD     NMI_Handler                    ; 2 NMI Handler
                DCD     HardFault_Handler              ; 3 Hard Fault Handler
                DCD     0                                 ; 4 Reserved
                DCD     0                                 ; 5 Reserved
                DCD     0                                 ; 6 Reserved
                DCD     0                                 ; 7 Reserved
                DCD     0                                 ; 8 Reserved
                DCD     0                                 ; 9 Reserved
                DCD     0                                 ; 10 Reserved
                DCD     SVC_Handler                    ; 11 SVCall Handler
                DCD     DebugMon_Handler               ; 12 Debug Monitor Handler
                DCD     0                                 ; 13 Reserved
                DCD     PendSV_Handler                 ; 14 PendSV Handler
                DCD     SysTick_Handler                ; 15 SysTick Handler

                ; External Interrupts
                DCD     RTC_IRQHandler                 ; 16 RTC
                DCD     M4CORE_IRQHandler              ; 17 M4 Core
                DCD     DMA_IRQHandler                 ; 18 General Purpose DMA
                DCD     0                                 ; 19 Reserved
                DCD     FLASHEEPROMAT_IRQHandler       ; 20 ORed flash bank A, flash bank B, EEPROM, Atimer
                DCD     ETH_IRQHandler                 ; 21 Ethernet
                DCD     SDIO_IRQHandler                ; 22 SD/MMC
                DCD     LCD_IRQHandler                 ; 23 LCD
                DCD     USB0_IRQHandler                ; 24 USB0
                DCD     USB1_IRQHandler                ; 25 USB1
                DCD     SCT_IRQHandler                 ; 26 State Configurable Timer
                DCD     RIT_OR_WWDT_IRQHandler         ; 27 Repetitive Interrupt Timer or WWDT
                DCD     TIMER0_IRQHandler              ; 28 Timer0
                DCD     GINT1_IRQHandler               ; 29 GPIO global interrupt 1
                DCD     PIN_INT4_IRQHandler               ; 30 GPIO pin interrupt 4
                DCD     TIMER3_IRQHandler              ; 31 Timer3
                DCD     MCPWM_IRQHandler               ; 32 Motor control PWM
                DCD     ADC0_IRQHandler                ; 33 ADC0
                DCD     I2C0_OR_I2C1_IRQHandler        ; 34 I2C or I2C1
                DCD     SGPIO_IRQHandler               ; 35 Serial GPIO
                DCD     SPI_OR_DAC_IRQHandler          ; 36 SPI or DAC
                DCD     ADC1_IRQHandler                ; 37 ADC1
                DCD     SSP0_OR_SSP1_IRQHandler        ; 38 SSP0 or SSP1
                DCD     EVENTROUTER_IRQHandler         ; 39 Event router
                DCD     USART0_IRQHandler              ; 40 USART0
                DCD     UART1_IRQHandler               ; 41 UART1/Modem
                DCD     USART2_OR_C_CAN1_IRQHandler    ; 42 USART2 or C CAN1
                DCD     USART3_IRQHandler              ; 43 USART3
                DCD     I2S0_OR_I2S1_OR_QEI_IRQHandler ; 44 I2S0 or I2S1 or QEI
                DCD     C_CAN0_IRQHandler              ; 45 C CAN0
                DCD     0                                 ; 46 Reserved
                DCD     0                                 ; 47 Reserved

                AREA    |.text|, CODE, READONLY

; Reset Handler

Reset_Handler\
                PROC
                EXPORT  Reset_Handler                    [WEAK]
                IMPORT  __main
                LDR     R0, =__main
                BX      R0
                ENDP

; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler  PROC
                EXPORT  NMI_Handler                      [WEAK]
                B       .
                ENDP

HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler                [WEAK]
                B       .
                ENDP
SVC_Handler  PROC
                EXPORT  SVC_Handler                      [WEAK]
                B       .
                ENDP

DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler                 [WEAK]
                B       .
                ENDP

PendSV_Handler  PROC
                EXPORT  PendSV_Handler                   [WEAK]
                B       .
                ENDP

SysTick_Handler PROC
                EXPORT  SysTick_Handler                  [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT   RTC_IRQHandler                  [WEAK]
                EXPORT   M4CORE_IRQHandler               [WEAK]
                EXPORT   DMA_IRQHandler                  [WEAK]
                EXPORT   FLASHEEPROMAT_IRQHandler        [WEAK]
                EXPORT   ETH_IRQHandler                  [WEAK]
                EXPORT   SDIO_IRQHandler                 [WEAK]
                EXPORT   LCD_IRQHandler                  [WEAK]
                EXPORT   USB0_IRQHandler                 [WEAK]
                EXPORT   USB1_IRQHandler                 [WEAK]
                EXPORT   SCT_IRQHandler                  [WEAK]
                EXPORT   RIT_OR_WWDT_IRQHandler          [WEAK]
                EXPORT   TIMER0_IRQHandler               [WEAK]
                EXPORT   GINT1_IRQHandler                [WEAK]
                EXPORT   PIN_INT4_IRQHandler                [WEAK]
                EXPORT   TIMER3_IRQHandler               [WEAK]
                EXPORT   MCPWM_IRQHandler                [WEAK]
                EXPORT   ADC0_IRQHandler                 [WEAK]
                EXPORT   I2C0_OR_I2C1_IRQHandler         [WEAK]
                EXPORT   SGPIO_IRQHandler                [WEAK]
                EXPORT   SPI_OR_DAC_IRQHandler           [WEAK]
                EXPORT   ADC1_IRQHandler                 [WEAK]
                EXPORT   SSP0_OR_SSP1_IRQHandler         [WEAK]
                EXPORT   EVENTROUTER_IRQHandler          [WEAK]
                EXPORT   USART0_IRQHandler               [WEAK]
                EXPORT   UART1_IRQHandler                [WEAK]
                EXPORT   USART2_OR_C_CAN1_IRQHandler     [WEAK]
                EXPORT   USART3_IRQHandler               [WEAK]
                EXPORT   I2S0_OR_I2S1_OR_QEI_IRQHandler  [WEAK]
                EXPORT   C_CAN0_IRQHandler               [WEAK]


RTC_IRQHandler
M4CORE_IRQHandler
DMA_IRQHandler
FLASHEEPROMAT_IRQHandler
ETH_IRQHandler
SDIO_IRQHandler
LCD_IRQHandler
USB0_IRQHandler
USB1_IRQHandler
SCT_IRQHandler
RIT_OR_WWDT_IRQHandler
TIMER0_IRQHandler
GINT1_IRQHandler
PIN_INT4_IRQHandler
TIMER3_IRQHandler
MCPWM_IRQHandler
ADC0_IRQHandler
I2C0_OR_I2C1_IRQHandler
SGPIO_IRQHandler
SPI_OR_DAC_IRQHandler
ADC1_IRQHandler
SSP0_OR_SSP1_IRQHandler
EVENTROUTER_IRQHandler
USART0_IRQHandler
UART1_IRQHandler
USART2_OR_C_CAN1_IRQHandler
USART3_IRQHandler
I2S0_OR_I2S1_OR_QEI_IRQHandler
C_CAN0_IRQHandler

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

                AREA    |.text|,CODE, READONLY
getPC           PROC
                EXPORT  getPC

                MOV     R0,LR
                BX      LR

                ENDP

                END
