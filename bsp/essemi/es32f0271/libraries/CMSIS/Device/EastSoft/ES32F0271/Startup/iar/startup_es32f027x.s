;*******************************************************************************
; file       : startup_ES32f027x.s
; description: ES32F027x Device Startup File
; author     : Eastsoft MCU Software Team
; data       : 10 Dec 2018
; Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
;*******************************************************************************

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)
        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        PUBLIC  __vector_table

        DATA
__vector_table
        DCD     sfe(CSTACK)				;0,  load top of stack
        DCD     Reset_Handler			;1,  reset handler
        DCD     NMI_Handler				;2,  nmi handler
        DCD     HardFault_Handler			;3,  hard fault handler
        DCD     0					;4,  MPU Fault Handler
        DCD     0					;5,  Bus Fault Handler
        DCD     0					;6,  Usage Fault Handler
        DCD     0					;7,  Reserved
        DCD     0					;8,  Reserved
        DCD     0					;9,  Reserved
        DCD     0					;10, Reserved
        DCD     SVC_Handler				;11, svcall handler
        DCD     0					;12, Reserved
        DCD     0					;13, Reserved
        DCD     PENDSV_Handler             ;14, PENDSV Handler
        DCD     SYSTICK_Handler            ;15, SYSTICK Handler
        DCD     WWDT_IRQHandler            ;16, WWDT IRQHandler
        DCD     PVD_IRQHandler             ;17, PVD IRQHandler
        DCD     RTC_IRQHandler             ;18, RTC IRQHandler
        DCD     LowPowerWakeup_IRQHandler  ;19, LowPowerWakeup IRQHandler
        DCD     0                          ;20, Reserved
        DCD     EXTI0_1_IRQHandler         ;21, EXTI01_1 IRQHandler
        DCD     EXTI2_3_IRQHandler         ;22, EXTI2_3 IRQHandler
        DCD     EXTI4_15_IRQHandler        ;23, EXTI4_15 IRQHandler
        DCD     0                          ;24, Reserved
        DCD     DMA1_CH0_IRQHandler        ;25, DMA1_CH1 IRQHandler
        DCD     DMA1_CH1_2_IRQHandler      ;26, DMA1_CH2_3 IRQHandler
        DCD     DMA1_CH3_5_IRQHandler      ;27, DMA1_CH4_7 IRQHandler
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
        
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:NOROOT:REORDER(2)
Reset_Handler
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
		
    	PUBWEAK PENDSV_Handler
    	SECTION .text:CODE:NOROOT:REORDER(1)
PENDSV_Handler
    	B PENDSV_Handler

   	PUBWEAK SYSTICK_Handler
    	SECTION .text:CODE:NOROOT:REORDER(1)
SYSTICK_Handler
    	B SYSTICK_Handler

        PUBWEAK WWDT_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
WWDT_IRQHandler
        B WWDT_IRQHandler

	PUBWEAK PVD_IRQHandler
	SECTION .text:CODE:NOROOT:REORDER(1)
PVD_IRQHandler
	B PVD_IRQHandler
		
	PUBWEAK RTC_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTC_IRQHandler
        B RTC_IRQHandler

        PUBWEAK LowPowerWakeup_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
LowPowerWakeup_IRQHandler
        B LowPowerWakeup_IRQHandler

        PUBWEAK EXTI0_1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI0_1_IRQHandler
        B EXTI0_1_IRQHandler

        PUBWEAK EXTI2_3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI2_3_IRQHandler
        B EXTI2_3_IRQHandler

        PUBWEAK EXTI4_15_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI4_15_IRQHandler
        B EXTI4_15_IRQHandler

        PUBWEAK DMA1_CH0_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_CH0_IRQHandler
        B DMA1_CH0_IRQHandler

 	PUBWEAK DMA1_CH1_2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_CH1_2_IRQHandler
        B DMA1_CH1_2_IRQHandler

        PUBWEAK DMA1_CH3_5_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA1_CH3_5_IRQHandler
        B DMA1_CH3_5_IRQHandler

        PUBWEAK ADC_CMP_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC_CMP_IRQHandler
        B ADC_CMP_IRQHandler

        PUBWEAK AD16C4T1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
AD16C4T1_IRQHandler
        B AD16C4T1_IRQHandler

        PUBWEAK BS16T1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
BS16T1_IRQHandler
        B BS16T1_IRQHandler

        PUBWEAK GP32C4T1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
GP32C4T1_IRQHandler
        B GP32C4T1_IRQHandler

        PUBWEAK GP16C4T1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
GP16C4T1_IRQHandler
        B GP16C4T1_IRQHandler

        PUBWEAK GP16C4T2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
GP16C4T2_IRQHandler
        B GP16C4T2_IRQHandler

        PUBWEAK GP16C4T3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
GP16C4T3_IRQHandler
        B GP16C4T3_IRQHandler

        PUBWEAK GP16C2T1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
GP16C2T1_IRQHandler
        B GP16C2T1_IRQHandler

        PUBWEAK GP16C2T2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
GP16C2T2_IRQHandler
        B GP16C2T2_IRQHandler

        PUBWEAK GP16C2T3_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
GP16C2T3_IRQHandler
        B GP16C2T3_IRQHandler

        PUBWEAK GP16C2T4_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
GP16C2T4_IRQHandler
        B GP16C2T4_IRQHandler

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

	PUBWEAK UART1_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART1_IRQHandler
        B UART1_IRQHandler

	PUBWEAK UART2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART2_IRQHandler
        B UART2_IRQHandler

	PUBWEAK UART3_AES_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART3_AES_IRQHandler
        B UART3_AES_IRQHandler

	PUBWEAK SUART1_SUART2_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
SUART1_SUART2_IRQHandler
        B SUART1_SUART2_IRQHandler

	PUBWEAK USB_IRQHandler
        SECTION .text:CODE:NOROOT:REORDER(1)
USB_IRQHandler
        B USB_IRQHandler

        END
