;/***********************************************************************
; * $Id: startup_LPC43xx.s 6473 2011-02-16 17:40:54Z nxp27266 $
; *
; * Project: LPC43xx CMSIS Package
; *
; * Description: Cortex-M3 Core Device Startup File for the NXP LPC43xx 
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

Sign_Value      EQU     0x5A5A5A5A

__Vectors       DCD     __initial_sp              ; 0 Top of Stack
                DCD     Reset_Handler             ; 1 Reset Handler
                DCD     NMI_Handler               ; 2 NMI Handler
                DCD     HardFault_Handler         ; 3 Hard Fault Handler
                DCD     MemManage_Handler         ; 4 MPU Fault Handler
                DCD     BusFault_Handler          ; 5 Bus Fault Handler
                DCD     UsageFault_Handler        ; 6 Usage Fault Handler
                DCD     Sign_Value                ; 7 Reserved
                DCD     0                         ; 8 Reserved
                DCD     0                         ; 9 Reserved
                DCD     0                         ; 10 Reserved
                DCD     SVC_Handler               ; 11 SVCall Handler
                DCD     DebugMon_Handler          ; 12 Debug Monitor Handler
                DCD     0                         ; 13 Reserved
                DCD     PendSV_Handler            ; 14 PendSV Handler
                DCD     SysTick_Handler           ; 15 SysTick Handler

                ; External Interrupts
                DCD     DAC_IRQHandler            ; 16 D/A Converter
                DCD     M0CORE_IRQHandler         ; 17 M0 Core
                DCD     DMA_IRQHandler            ; 18 General Purpose DMA
                DCD     EZH_IRQHandler            ; 19 EZH/EDM
                DCD     FLASH_EEPROM_IRQHandler   ; 20 Reserved for Typhoon
                DCD     ETH_IRQHandler            ; 21 Ethernet
                DCD     SDIO_IRQHandler           ; 22 SD/MMC
                DCD     LCD_IRQHandler            ; 23 LCD
                DCD     USB0_IRQHandler           ; 24 USB0
                DCD     USB1_IRQHandler           ; 25 USB1
                DCD     SCT_IRQHandler            ; 26 State Configurable Timer
                DCD     RIT_IRQHandler            ; 27 Repetitive Interrupt Timer
                DCD     TIMER0_IRQHandler         ; 28 Timer0
                DCD     TIMER1_IRQHandler         ; 29 Timer1
                DCD     TIMER2_IRQHandler         ; 30 Timer2
                DCD     TIMER3_IRQHandler         ; 31 Timer3
                DCD     MCPWM_IRQHandler          ; 32 Motor Control PWM
                DCD     ADC0_IRQHandler           ; 33 A/D Converter 0
                DCD     I2C0_IRQHandler           ; 34 I2C0
                DCD     I2C1_IRQHandler           ; 35 I2C1
                DCD     SPI_IRQHandler            ; 36 SPI
                DCD     ADC1_IRQHandler           ; 37 A/D Converter 1
                DCD     SSP0_IRQHandler           ; 38 SSP0
                DCD     SSP1_IRQHandler           ; 39 SSP1
                DCD     UART0_IRQHandler          ; 40 UART0
                DCD     UART1_IRQHandler          ; 41 UART1
                DCD     UART2_IRQHandler          ; 42 UART2
                DCD     UART3_IRQHandler          ; 43 UART3
                DCD     I2S0_IRQHandler           ; 44 I2S0
                DCD     I2S1_IRQHandler           ; 45 I2S1
                DCD     SPIFI_IRQHandler          ; 46 SPI Flash Interface
                DCD     SGPIO_IRQHandler          ; 47 SGPIO
                DCD     GPIO0_IRQHandler          ; 48 GPIO0
                DCD     GPIO1_IRQHandler          ; 49 GPIO1
                DCD     GPIO2_IRQHandler          ; 50 GPIO2
                DCD     GPIO3_IRQHandler          ; 51 GPIO3
                DCD     GPIO4_IRQHandler          ; 52 GPIO4
                DCD     GPIO5_IRQHandler          ; 53 GPIO5
                DCD     GPIO6_IRQHandler          ; 54 GPIO6
                DCD     GPIO7_IRQHandler          ; 55 GPIO7
                DCD     GINT0_IRQHandler          ; 56 GINT0
                DCD     GINT1_IRQHandler          ; 57 GINT1
                DCD     EVRT_IRQHandler           ; 58 Event Router
                DCD     CAN1_IRQHandler           ; 59 C_CAN1
                DCD     0                         ; 60 Reserved
                DCD     VADC_IRQHandler           ; 61 VADC
                DCD     ATIMER_IRQHandler         ; 62 ATIMER
                DCD     RTC_IRQHandler            ; 63 RTC
                DCD     0                         ; 64 Reserved
                DCD     WDT_IRQHandler            ; 65 WDT
                DCD     M0s_IRQHandler            ; 66 M0s
                DCD     CAN0_IRQHandler           ; 67 C_CAN0
                DCD     QEI_IRQHandler            ; 68 QEI



                AREA    |.text|, CODE, READONLY

; Reset Handler

Reset_Handler   PROC
                EXPORT  Reset_Handler           [WEAK]
                IMPORT  SystemInit
                IMPORT  __main
                LDR     R0, =SystemInit
                BLX     R0
                LDR     R0, =__main
                BX      R0
                ENDP

; Dummy Exception Handlers (infinite loops which can be modified)

NMI_Handler     PROC
                EXPORT  NMI_Handler             [WEAK]
                B       .
                ENDP
HardFault_Handler\
                PROC
                EXPORT  HardFault_Handler       [WEAK]
                B       .
                ENDP
MemManage_Handler\
                PROC
                EXPORT  MemManage_Handler       [WEAK]
                B       .
                ENDP
BusFault_Handler\
                PROC
                EXPORT  BusFault_Handler        [WEAK]
                B       .
                ENDP
UsageFault_Handler\
                PROC
                EXPORT  UsageFault_Handler      [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler             [WEAK]
                B       .
                ENDP
DebugMon_Handler\
                PROC
                EXPORT  DebugMon_Handler        [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler          [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler         [WEAK]
                B       .
                ENDP

Default_Handler PROC

                EXPORT  DAC_IRQHandler          [WEAK]
                EXPORT  M0CORE_IRQHandler       [WEAK]
                EXPORT  DMA_IRQHandler          [WEAK]
                EXPORT  EZH_IRQHandler          [WEAK]
                EXPORT  FLASH_EEPROM_IRQHandler [WEAK]
                EXPORT  ETH_IRQHandler          [WEAK]
                EXPORT  SDIO_IRQHandler         [WEAK]
                EXPORT  LCD_IRQHandler          [WEAK]
                EXPORT  USB0_IRQHandler         [WEAK]
                EXPORT  USB1_IRQHandler         [WEAK]
                EXPORT  SCT_IRQHandler          [WEAK]
                EXPORT  RIT_IRQHandler          [WEAK]
                EXPORT  TIMER0_IRQHandler       [WEAK]
                EXPORT  TIMER1_IRQHandler       [WEAK]
                EXPORT  TIMER2_IRQHandler       [WEAK]
                EXPORT  TIMER3_IRQHandler       [WEAK]
                EXPORT  MCPWM_IRQHandler        [WEAK]
                EXPORT  ADC0_IRQHandler         [WEAK]
                EXPORT  I2C0_IRQHandler         [WEAK]
                EXPORT  I2C1_IRQHandler         [WEAK]
                EXPORT  SPI_IRQHandler          [WEAK]
                EXPORT  ADC1_IRQHandler         [WEAK]
                EXPORT  SSP0_IRQHandler         [WEAK]
                EXPORT  SSP1_IRQHandler         [WEAK]
                EXPORT  UART0_IRQHandler        [WEAK]
                EXPORT  UART1_IRQHandler        [WEAK]
                EXPORT  UART2_IRQHandler        [WEAK]
                EXPORT  UART3_IRQHandler        [WEAK]
                EXPORT  I2S0_IRQHandler         [WEAK]
                EXPORT  I2S1_IRQHandler         [WEAK]
                EXPORT  SPIFI_IRQHandler        [WEAK]
                EXPORT  SGPIO_IRQHandler        [WEAK]
                EXPORT  GPIO0_IRQHandler        [WEAK]
                EXPORT  GPIO1_IRQHandler        [WEAK]
                EXPORT  GPIO2_IRQHandler        [WEAK]
                EXPORT  GPIO3_IRQHandler        [WEAK]
                EXPORT  GPIO4_IRQHandler        [WEAK]
                EXPORT  GPIO5_IRQHandler        [WEAK]
                EXPORT  GPIO6_IRQHandler        [WEAK]
                EXPORT  GPIO7_IRQHandler        [WEAK]
                EXPORT  GINT0_IRQHandler        [WEAK]
                EXPORT  GINT1_IRQHandler        [WEAK]
                EXPORT  EVRT_IRQHandler         [WEAK]
                EXPORT  CAN1_IRQHandler         [WEAK]
                EXPORT  VADC_IRQHandler         [WEAK]
                EXPORT  ATIMER_IRQHandler       [WEAK]
                EXPORT  RTC_IRQHandler          [WEAK]
                EXPORT  WDT_IRQHandler          [WEAK]
                EXPORT  M0s_IRQHandler          [WEAK]
                EXPORT  CAN0_IRQHandler         [WEAK]
                EXPORT  QEI_IRQHandler          [WEAK]

DAC_IRQHandler
M0CORE_IRQHandler
DMA_IRQHandler
EZH_IRQHandler
FLASH_EEPROM_IRQHandler
ETH_IRQHandler
SDIO_IRQHandler
LCD_IRQHandler
USB0_IRQHandler
USB1_IRQHandler
SCT_IRQHandler
RIT_IRQHandler
TIMER0_IRQHandler
TIMER1_IRQHandler
TIMER2_IRQHandler
TIMER3_IRQHandler
MCPWM_IRQHandler
ADC0_IRQHandler
I2C0_IRQHandler
I2C1_IRQHandler
SPI_IRQHandler
ADC1_IRQHandler
SSP0_IRQHandler
SSP1_IRQHandler
UART0_IRQHandler
UART1_IRQHandler
UART2_IRQHandler
UART3_IRQHandler
I2S0_IRQHandler
I2S1_IRQHandler
SPIFI_IRQHandler
SGPIO_IRQHandler
GPIO0_IRQHandler
GPIO1_IRQHandler
GPIO2_IRQHandler
GPIO3_IRQHandler
GPIO4_IRQHandler
GPIO5_IRQHandler
GPIO6_IRQHandler
GPIO7_IRQHandler
GINT0_IRQHandler
GINT1_IRQHandler
EVRT_IRQHandler
CAN1_IRQHandler
VADC_IRQHandler
ATIMER_IRQHandler
RTC_IRQHandler
WDT_IRQHandler
M0s_IRQHandler
CAN0_IRQHandler
QEI_IRQHandler

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
