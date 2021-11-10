;*******************************************************************************
; file       : startup_es32f065x.s
; description: es32f065x Device Startup File
; author     : AE Team
; data       : 10 Dec 2018
; note
;          Change Logs:
;          Date            Author          Notes
;          10 Dec 2018     AE Team         The first version
;
; Copyright (C) Shanghai Eastsoft Microelectronics Co. Ltd. All rights reserved.
;
; SPDX-License-Identifier: Apache-2.0
;
; Licensed under the Apache License, Version 2.0 (the License); you may
; not use this file except in compliance with the License.
; You may obtain a copy of the License at
;
; www.apache.org/licenses/LICENSE-2.0
;
; Unless required by applicable law or agreed to in writing, software
; distributed under the License is distributed on an AS IS BASIS, WITHOUT
; WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
; See the License for the specific language governing permissions and
; limitations under the License.
;*********************************************************************************

        MODULE  ?cstartup

        ;; Forward declaration of sections.
        SECTION CSTACK:DATA:NOROOT(3)
        SECTION .intvec:CODE:NOROOT(2)

        EXTERN  __iar_program_start
        PUBLIC  __vector_table

        DATA
__vector_table
        DCD     sfe(CSTACK)				;0,  load top of stack
        DCD     Reset_Handler				;1,  reset handler
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
        DCD     DebugMon_Handler			;12, Debug Monitor Handler
        DCD     0					;13, Reserved
        DCD     PendSV_Handler				;14, pendsv handler
        DCD     SysTick_Handler				;15, systick handler
        DCD     WWDG_IWDG_Handler			;16, irq0    WWDG_IWDG handler
        DCD     LVD_Handler				;17, irq1    LVD handler
        DCD     RTC_TSENSE_Handler			;18, irq2    RTC handler
        DCD     CRYPT_TRNG_Handler			;19, irq3    CRYPT handler
        DCD     CMU_Handler				;20, irq4    CMU handler
        DCD     EXTI0_3_Handler				;21, irq5    EXTI0_3 handler
        DCD     EXTI4_7_Handler				;22, irq6    EXTI4_7 handler
        DCD     EXTI8_11_Handler			;23, irq7    EXTI8_11 handler
        DCD     EXTI12_15_Handler			;24, irq8    EXTI12_15 handler
        DCD     DMA_Handler				;25, irq9    DMA handler
        DCD     CAN0_Handler				;26, irq10   CAN0_CRYPT_TRNG handler
        DCD     LPTIM0_SPI2_Handler			;27, irq11   LPTIM0_SPI2 handler
        DCD     ADC_ACMP_Handler			;28, irq12   ADC_ACMP handler
        DCD     AD16C4T0_BRK_UP_TRIG_COM_Handler	;29, irq13   AD16C4T0_BRK_UP_TRIG_COM handler
        DCD     AD16C4T0_CC_Handler			;30, irq14   AD16C4T0_CC handler
        DCD     BS16T0_Handler				;31, irq15   BS16T0 handler
        DCD     0					;32, irq16   Reserved
        DCD     GP16C2T0_Handler			;33, irq17   GP16C2T0 handler
        DCD     GP16C2T1_Handler			;34, irq18   GP16C2T1 handler
        DCD     BS16T1_UART2_Handler			;35, irq19   BS16T1_UART2 handler
        DCD     BS16T2_UART3_Handler			;36, irq20   BS16T2_UART3 handler
        DCD     GP16C4T0_LCD_Handler			;37, irq21   GP16C4T0_LCD handler
        DCD     BS16T3_DAC0_Handler			;38, irq22   BS16T3_DAC0  handler
        DCD     I2C0_Handler				;39, irq23   I2C0 handler
        DCD     I2C1_Handler				;40, irq24   I2C1 handler
        DCD     SPI0_Handler				;41, irq25   SPI0 handler
        DCD     SPI1_Handler				;42, irq26   SPI1 handler
        DCD     UART0_Handler				;43, irq27   UART0 handler
        DCD     UART1_Handler				;44, irq28   UART1 handler
        DCD     USART0_Handler				;45, irq29   USART0 handler
        DCD     USART1_Handler				;46, irq30   USART1 handler
        DCD     LPUART0_Handler				;47, irq31   LPUART0 handler
        
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

        PUBWEAK WWDG_IWDG_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
WWDG_IWDG_Handler
        B WWDG_IWDG_Handler

	PUBWEAK LVD_Handler
	SECTION .text:CODE:NOROOT:REORDER(1)
LVD_Handler
	B LVD_Handler
		
	PUBWEAK RTC_TSENSE_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
RTC_TSENSE_Handler
        B RTC_TSENSE_Handler

        PUBWEAK CRYPT_TRNG_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
CRYPT_TRNG_Handler
        B CRYPT_TRNG_Handler

        PUBWEAK CMU_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
CMU_Handler
        B CMU_Handler

        PUBWEAK EXTI0_3_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI0_3_Handler
        B EXTI0_3_Handler

        PUBWEAK EXTI4_7_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI4_7_Handler
        B EXTI4_7_Handler

        PUBWEAK EXTI8_11_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI8_11_Handler
        B EXTI8_11_Handler

 	PUBWEAK EXTI12_15_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
EXTI12_15_Handler
        B EXTI12_15_Handler

        PUBWEAK DMA_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
DMA_Handler
        B DMA_Handler

        PUBWEAK CAN0_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
CAN0_Handler
        B CAN0_Handler

        PUBWEAK LPTIM0_SPI2_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
LPTIM0_SPI2_Handler
        B LPTIM0_SPI2_Handler

        PUBWEAK ADC_ACMP_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
ADC_ACMP_Handler
        B ADC_ACMP_Handler

        PUBWEAK AD16C4T0_BRK_UP_TRIG_COM_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
AD16C4T0_BRK_UP_TRIG_COM_Handler
        B AD16C4T0_BRK_UP_TRIG_COM_Handler

        PUBWEAK AD16C4T0_CC_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
AD16C4T0_CC_Handler
        B AD16C4T0_CC_Handler

        PUBWEAK BS16T0_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
BS16T0_Handler
        B BS16T0_Handler

        PUBWEAK GP16C2T0_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
GP16C2T0_Handler
        B GP16C2T0_Handler

        PUBWEAK GP16C2T1_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
GP16C2T1_Handler
        B GP16C2T1_Handler

        PUBWEAK BS16T1_UART2_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
BS16T1_UART2_Handler
        B BS16T1_UART2_Handler

        PUBWEAK BS16T2_UART3_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
BS16T2_UART3_Handler
        B BS16T2_UART3_Handler

        PUBWEAK GP16C4T0_LCD_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
GP16C4T0_LCD_Handler
        B GP16C4T0_LCD_Handler

        PUBWEAK BS16T3_DAC0_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
BS16T3_DAC0_Handler
        B BS16T3_DAC0_Handler

	PUBWEAK I2C0_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C0_Handler
        B I2C0_Handler

	PUBWEAK I2C1_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
I2C1_Handler
        B I2C1_Handler

	PUBWEAK SPI0_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI0_Handler
        B SPI0_Handler

	PUBWEAK SPI1_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
SPI1_Handler
        B SPI1_Handler

	PUBWEAK UART0_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART0_Handler
        B UART0_Handler

	PUBWEAK UART1_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
UART1_Handler
        B UART1_Handler

	PUBWEAK USART0_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART0_Handler
        B USART0_Handler

	PUBWEAK USART1_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
USART1_Handler
        B USART1_Handler

	PUBWEAK LPUART0_Handler
        SECTION .text:CODE:NOROOT:REORDER(1)
LPUART0_Handler
        B LPUART0_Handler

        END
