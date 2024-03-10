;/*****************************************************************************
; * @file:    startup_LPC18xx.s
; * @purpose: CMSIS Cortex-M3 Core Device Startup File
; *           for the NXP LPC18xx Device Series
; * @version: V1.00
; * @date:    24. May. 2011
; *----------------------------------------------------------------------------
; *
; * Copyright (C) 2010 ARM Limited. All rights reserved.
; *
; * ARM Limited (ARM) is supplying this software for use with Cortex-Mx
; * processor based microcontrollers.  This file can be freely distributed
; * within development tools that are supporting such ARM based processors.
; *
; * THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
; * OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
; * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
; * ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR
; * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
; *
; ******************************************************************************/


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
        PUBLIC  __vector_table_0x1c
        PUBLIC  __Vectors
        PUBLIC  __Vectors_End
        PUBLIC  __Vectors_Size

        DATA

Sign_Value		EQU		0x5A5A5A5A

__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler

        DCD     NMI_Handler
        DCD     HardFault_Handler
        DCD     MemManage_Handler
        DCD     BusFault_Handler
        DCD     UsageFault_Handler
__vector_table_0x1c
        DCD     Sign_Value
        DCD     0
        DCD     0
        DCD     0
        DCD     SVC_Handler
        DCD     DebugMon_Handler
        DCD     0
        DCD     PendSV_Handler
        DCD     SysTick_Handler

        ; External Interrupts
        DCD		DAC_IRQHandler	 			; 16 D/A Converter
	DCD		0					; 17 Event Router
        DCD		DMA_IRQHandler				; 18 General Purpose DMA
        DCD		0				        ; 19 Reserved
        DCD		0				        ; 20 Reserved
        DCD		ETH_IRQHandler				; 21 Ethernet
        DCD		SDIO_IRQHandler				; 22 SD/MMC
        DCD		LCD_IRQHandler				; 23 LCD
        DCD		USB0_IRQHandler				; 24 USB0
        DCD		USB1_IRQHandler				; 25 USB1
        DCD		SCT_IRQHandler				; 26 State Configurable Timer
        DCD		RIT_IRQHandler				; 27 Repetitive Interrupt Timer
        DCD		TIMER0_IRQHandler			; 28 Timer0
        DCD		TIMER1_IRQHandler			; 29 Timer1
        DCD		TIMER2_IRQHandler			; 30 Timer2
        DCD		TIMER3_IRQHandler			; 31 Timer3
        DCD		MCPWM_IRQHandler			; 32 Motor Control PWM
        DCD		ADC0_IRQHandler				; 33 A/D Converter 0
        DCD		I2C0_IRQHandler				; 34 I2C0
        DCD		I2C1_IRQHandler				; 35 I2C1
        DCD		0					; 36 Reserved
        DCD		ADC1_IRQHandler				; 37 A/D Converter 1
        DCD		SSP0_IRQHandler				; 38 SSP0
        DCD		SSP1_IRQHandler				; 39 SSP1
        DCD		UART0_IRQHandler			; 40 UART0
        DCD		UART1_IRQHandler			; 41 UART1
        DCD		UART2_IRQHandler			; 42 UART2
        DCD		UART3_IRQHandler			; 43 UART3
	DCD		I2S0_IRQHandler				; 44 I2S0
	DCD		I2S1_IRQHandler				; 45 I2S1
	DCD		SPIFI_IRQHandler			; 46 SPI Flash Interface
	DCD		SGPIO_IRQHandler			; 47 SGPIO
	DCD		GPIO0_IRQHandler			; 48 GPIO0
	DCD		GPIO1_IRQHandler			; 49 GPIO1
	DCD		GPIO2_IRQHandler			; 50 GPIO2
	DCD		GPIO3_IRQHandler			; 51 GPIO3
	DCD		GPIO4_IRQHandler			; 52 GPIO4
	DCD		GPIO5_IRQHandler			; 53 GPIO5
	DCD		GPIO6_IRQHandler			; 54 GPIO6
	DCD		GPIO7_IRQHandler			; 55 GPIO7
	DCD		GINT0_IRQHandler			; 56 GINT0
	DCD		GINT1_IRQHandler			; 57 GINT1
	DCD		EVRT_IRQHandler				; 58 Event Router
	DCD		CAN1_IRQHandler				; 59 C_CAN1
	DCD		0							; 60 Reserved
	DCD		0       				; 61 VADC
	DCD		ATIMER_IRQHandler			; 62 ATIMER
	DCD		RTC_IRQHandler				; 63 RTC
	DCD		0							; 64 Reserved
	DCD		WDT_IRQHandler				; 65 WDT
	DCD		0       				; 66 M0s
	DCD		CAN0_IRQHandler				; 67 C_CAN0
	DCD 	QEI_IRQHandler				; 68 QEI
__Vectors_End

__Vectors       EQU   __vector_table
__Vectors_Size 	EQU 	__Vectors_End - __Vectors


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER(2)
Reset_Handler
        LDR     R0, =__iar_program_start
        BX      R0

        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER(1)
NMI_Handler
        B NMI_Handler

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER(1)
HardFault_Handler
        B HardFault_Handler

        PUBWEAK MemManage_Handler
        SECTION .text:CODE:REORDER(1)
MemManage_Handler
        B MemManage_Handler

        PUBWEAK BusFault_Handler
        SECTION .text:CODE:REORDER(1)
BusFault_Handler
        B BusFault_Handler

        PUBWEAK UsageFault_Handler
        SECTION .text:CODE:REORDER(1)
UsageFault_Handler
        B UsageFault_Handler

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER(1)
SVC_Handler
        B SVC_Handler

        PUBWEAK DebugMon_Handler
        SECTION .text:CODE:REORDER(1)
DebugMon_Handler
        B DebugMon_Handler

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER(1)
PendSV_Handler
        B PendSV_Handler

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER(1)
SysTick_Handler
        B SysTick_Handler

        PUBWEAK DAC_IRQHandler
        SECTION .text:CODE:REORDER(1)
DAC_IRQHandler
        B DAC_IRQHandler

        PUBWEAK EVRT_IRQHandler
        SECTION .text:CODE:REORDER(1)
EVRT_IRQHandler
        B EVRT_IRQHandler

        PUBWEAK DMA_IRQHandler
        SECTION .text:CODE:REORDER(1)
DMA_IRQHandler
        B DMA_IRQHandler

        PUBWEAK ETH_IRQHandler
        SECTION .text:CODE:REORDER(1)
ETH_IRQHandler
        B ETH_IRQHandler

        PUBWEAK SDIO_IRQHandler
        SECTION .text:CODE:REORDER(1)
SDIO_IRQHandler
        B SDIO_IRQHandler

        PUBWEAK LCD_IRQHandler
        SECTION .text:CODE:REORDER(1)
LCD_IRQHandler
        B LCD_IRQHandler

        PUBWEAK USB0_IRQHandler
        SECTION .text:CODE:REORDER(1)
USB0_IRQHandler
        B USB0_IRQHandler

        PUBWEAK USB1_IRQHandler
        SECTION .text:CODE:REORDER(1)
USB1_IRQHandler
        B USB1_IRQHandler

        PUBWEAK SCT_IRQHandler
        SECTION .text:CODE:REORDER(1)
SCT_IRQHandler
        B SCT_IRQHandler

        PUBWEAK RIT_IRQHandler
        SECTION .text:CODE:REORDER(1)
RIT_IRQHandler
        B RIT_IRQHandler

        PUBWEAK TIMER0_IRQHandler
        SECTION .text:CODE:REORDER(1)
TIMER0_IRQHandler
        B TIMER0_IRQHandler

        PUBWEAK TIMER1_IRQHandler
        SECTION .text:CODE:REORDER(1)
TIMER1_IRQHandler
        B TIMER1_IRQHandler

        PUBWEAK TIMER2_IRQHandler
        SECTION .text:CODE:REORDER(1)
TIMER2_IRQHandler
        B TIMER2_IRQHandler

        PUBWEAK TIMER3_IRQHandler
        SECTION .text:CODE:REORDER(1)
TIMER3_IRQHandler
        B TIMER3_IRQHandler

        PUBWEAK MCPWM_IRQHandler
        SECTION .text:CODE:REORDER(1)
MCPWM_IRQHandler
        B MCPWM_IRQHandler

        PUBWEAK ADC0_IRQHandler
        SECTION .text:CODE:REORDER(1)
ADC0_IRQHandler
        B ADC0_IRQHandler

        PUBWEAK I2C0_IRQHandler
        SECTION .text:CODE:REORDER(1)
I2C0_IRQHandler
        B I2C0_IRQHandler

        PUBWEAK I2C1_IRQHandler
        SECTION .text:CODE:REORDER(1)
I2C1_IRQHandler
        B I2C1_IRQHandler

        PUBWEAK ADC1_IRQHandler
        SECTION .text:CODE:REORDER(1)
ADC1_IRQHandler
        B ADC1_IRQHandler

        PUBWEAK SSP0_IRQHandler
        SECTION .text:CODE:REORDER(1)
SSP0_IRQHandler
        B SSP0_IRQHandler

        PUBWEAK SSP1_IRQHandler
        SECTION .text:CODE:REORDER(1)
SSP1_IRQHandler
        B SSP1_IRQHandler

        PUBWEAK UART0_IRQHandler
        SECTION .text:CODE:REORDER(1)
UART0_IRQHandler
        B UART0_IRQHandler

        PUBWEAK UART1_IRQHandler
        SECTION .text:CODE:REORDER(1)
UART1_IRQHandler
        B UART1_IRQHandler

        PUBWEAK UART2_IRQHandler
        SECTION .text:CODE:REORDER(1)
UART2_IRQHandler
        B UART2_IRQHandler

        PUBWEAK UART3_IRQHandler
        SECTION .text:CODE:REORDER(1)
UART3_IRQHandler
        B UART3_IRQHandler

        PUBWEAK I2S0_IRQHandler
        SECTION .text:CODE:REORDER(1)
I2S0_IRQHandler
        B I2S0_IRQHandler

        PUBWEAK I2S1_IRQHandler
        SECTION .text:CODE:REORDER(1)
I2S1_IRQHandler
        B I2S1_IRQHandler
        
        PUBWEAK AES_IRQHandler
        SECTION .text:CODE:REORDER(1)
AES_IRQHandler
        B AES_IRQHandler

        PUBWEAK SPIFI_IRQHandler
        SECTION .text:CODE:REORDER(1)
SPIFI_IRQHandler
        B SPIFI_IRQHandler

        PUBWEAK SGPIO_IRQHandler
        SECTION .text:CODE:REORDER(1)
SGPIO_IRQHandler
        B SGPIO_IRQHandler

        PUBWEAK GPIO0_IRQHandler
        SECTION .text:CODE:REORDER(1)
GPIO0_IRQHandler
        B GPIO0_IRQHandler

        PUBWEAK GPIO1_IRQHandler
        SECTION .text:CODE:REORDER(1)
GPIO1_IRQHandler
        B GPIO1_IRQHandler
        
        PUBWEAK GPIO2_IRQHandler
        SECTION .text:CODE:REORDER(1)
GPIO2_IRQHandler
        B GPIO2_IRQHandler
        
        PUBWEAK GPIO3_IRQHandler
        SECTION .text:CODE:REORDER(1)
GPIO3_IRQHandler
        B GPIO3_IRQHandler
        
        PUBWEAK GPIO4_IRQHandler
        SECTION .text:CODE:REORDER(1)
GPIO4_IRQHandler
        B GPIO4_IRQHandler
        
        PUBWEAK GPIO5_IRQHandler
        SECTION .text:CODE:REORDER(1)
GPIO5_IRQHandler
        B GPIO5_IRQHandler
        
        PUBWEAK GPIO6_IRQHandler
        SECTION .text:CODE:REORDER(1)
GPIO6_IRQHandler
        B GPIO6_IRQHandler
        
        PUBWEAK GPIO7_IRQHandler
        SECTION .text:CODE:REORDER(1)
GPIO7_IRQHandler
        B GPIO7_IRQHandler
        
        PUBWEAK GINT0_IRQHandler
        SECTION .text:CODE:REORDER(1)
GINT0_IRQHandler
        B GINT0_IRQHandler
        
        PUBWEAK GINT1_IRQHandler
        SECTION .text:CODE:REORDER(1)
GINT1_IRQHandler
        B GINT1_IRQHandler
        
        PUBWEAK CAN1_IRQHandler
        SECTION .text:CODE:REORDER(1)
CAN1_IRQHandler
        B CAN1_IRQHandler
        
        PUBWEAK ATIMER_IRQHandler
        SECTION .text:CODE:REORDER(1)
ATIMER_IRQHandler
        B ATIMER_IRQHandler
        
        PUBWEAK RTC_IRQHandler
        SECTION .text:CODE:REORDER(1)
RTC_IRQHandler
        B RTC_IRQHandler
        
        PUBWEAK WDT_IRQHandler
        SECTION .text:CODE:REORDER(1)
WDT_IRQHandler
        B WDT_IRQHandler
        
        PUBWEAK CAN0_IRQHandler
        SECTION .text:CODE:REORDER(1)
CAN0_IRQHandler
        B CAN0_IRQHandler
        
        PUBWEAK QEI_IRQHandler
        SECTION .text:CODE:REORDER(1)
QEI_IRQHandler
        B QEI_IRQHandler
        
        PUBWEAK getPC
        SECTION .text:CODE:REORDER(2)
getPC
      MOV   R0,LR
      BX    LR        
        END
