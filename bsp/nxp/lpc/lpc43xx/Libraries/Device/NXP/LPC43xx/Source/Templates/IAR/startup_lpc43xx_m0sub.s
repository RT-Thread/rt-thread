/**************************************************
 *
 * Part one of the system initialization code, contains low-level
 * initialization, plain thumb variant.
 *
 * Copyright 2011 IAR Systems. All rights reserved.
 *
 * $Revision: 47876 $
 *
 **************************************************/

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

__vector_table
        DCD     sfe(CSTACK)
        DCD     Reset_Handler
        DCD     NMI_Handler
        DCD     HardFault_Handler
        DCD     MemManage_Handler
        DCD     BusFault_Handler
        DCD     UsageFault_Handler
__vector_table_0x1c
        DCD     0
        DCD     0
        DCD     0
        DCD     0
        DCD     SVC_Handler
        DCD     DebugMon_Handler
        DCD     0
        DCD     PendSV_Handler
        DCD     SysTick_Handler

        ; External Interrupts
		DCD		DAC_IRQHandler
		DCD		M4_IRQHandler
		DCD		DMA_IRQHandler
		DCD		0
		DCD		SGPIO_INPUT_IRQHandler
		DCD		SGPIO_MATCH_IRQHandler
		DCD		SGPIO_SHIFT_IRQHandler
		DCD		SGPIO_POS_IRQHandler
		DCD		USB0_IRQHandler
		DCD		USB1_IRQHandler
		DCD		SCT_IRQHandler
		DCD		RIT_IRQHandler
		DCD		GINT1_IRQHandler
		DCD		TIMER1_IRQHandler
		DCD		TIMER2_IRQHandler
		DCD		GPIO5_IRQHandler
		DCD		MCPWM_IRQHandler
		DCD		ADC0_IRQHandler
		DCD		I2C0_IRQHandler
		DCD		I2C1_IRQHandler
		DCD		SPI_IRQHandler
		DCD		ADC1_IRQHandler
		DCD		SSP0_SSP1_IRQHandler
		DCD		EVRT_IRQHandler
		DCD		UART0_IRQHandler
		DCD		UART1_IRQHandler
		DCD		UART2_CAN1_IRQHandler
		DCD		UART3_IRQHandler
		DCD		I2S0_I2S1_QEI_IRQHandler
		DCD		CAN0_IRQHandler
		DCD		SPIFI_ADCHS_IRQHandler
		DCD		M0APP_IRQHandler
__Vectors_End

__Vectors       EQU   __vector_table
__Vectors_Size 	EQU   __Vectors_End - __Vectors

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

		THUMB

		PUBWEAK Reset_Handler
		SECTION .text:CODE:REORDER(2)
Reset_Handler
		LDR     R0, =SystemInit
		BLX     R0
		LDR     R0, =__iar_program_start
		BX      R0
  
		PUBWEAK NMI_Handler
		PUBWEAK HardFault_Handler
		PUBWEAK MemManage_Handler
		PUBWEAK BusFault_Handler
		PUBWEAK UsageFault_Handler
		PUBWEAK SVC_Handler
		PUBWEAK DebugMon_Handler
		PUBWEAK PendSV_Handler
		PUBWEAK SysTick_Handler

		PUBWEAK DAC_IRQHandler
		PUBWEAK M4_IRQHandler
		PUBWEAK DMA_IRQHandler
		PUBWEAK UnHandled_Vector
		PUBWEAK SGPIO_INPUT_IRQHandler
		PUBWEAK SGPIO_MATCH_IRQHandler
		PUBWEAK SGPIO_SHIFT_IRQHandler
		PUBWEAK SGPIO_POS_IRQHandler
		PUBWEAK USB0_IRQHandler
		PUBWEAK USB1_IRQHandler
		PUBWEAK SCT_IRQHandler
		PUBWEAK RIT_IRQHandler
		PUBWEAK GINT1_IRQHandler
		PUBWEAK TIMER1_IRQHandler
		PUBWEAK TIMER2_IRQHandler
		PUBWEAK GPIO5_IRQHandler
		PUBWEAK MCPWM_IRQHandler
		PUBWEAK ADC0_IRQHandler
		PUBWEAK I2C0_IRQHandler
		PUBWEAK I2C1_IRQHandler
		PUBWEAK SPI_IRQHandler
		PUBWEAK ADC1_IRQHandler
		PUBWEAK SSP0_SSP1_IRQHandler
		PUBWEAK EVRT_IRQHandler
		PUBWEAK UART0_IRQHandler
		PUBWEAK UART1_IRQHandler
		PUBWEAK UART2_CAN1_IRQHandler
		PUBWEAK UART3_IRQHandler
		PUBWEAK I2S0_I2S1_QEI_IRQHandler
		PUBWEAK CAN0_IRQHandler
		PUBWEAK SPIFI_ADCHS_IRQHandler
		PUBWEAK M0APP_IRQHandler

        SECTION .text:CODE:REORDER(1)
NMI_Handler
        B .
SVC_Handler
        B .
DebugMon_Handler
        B .
PendSV_Handler
        B .
SysTick_Handler
        B .
HardFault_Handler
        B .
MemManage_Handler
        B .
BusFault_Handler
        B .
UsageFault_Handler
DAC_IRQHandler
M4_IRQHandler
DMA_IRQHandler
UnHandled_Vector
SGPIO_INPUT_IRQHandler
SGPIO_MATCH_IRQHandler
SGPIO_SHIFT_IRQHandler
SGPIO_POS_IRQHandler
USB0_IRQHandler
USB1_IRQHandler
SCT_IRQHandler
RIT_IRQHandler
GINT1_IRQHandler
TIMER1_IRQHandler
TIMER2_IRQHandler
GPIO5_IRQHandler
MCPWM_IRQHandler
ADC0_IRQHandler
I2C0_IRQHandler
I2C1_IRQHandler
SPI_IRQHandler
ADC1_IRQHandler
SSP0_SSP1_IRQHandler
EVRT_IRQHandler
UART0_IRQHandler
UART1_IRQHandler
UART2_CAN1_IRQHandler
UART3_IRQHandler
I2S0_I2S1_QEI_IRQHandler
CAN0_IRQHandler
SPIFI_ADCHS_IRQHandler
M0APP_IRQHandler
Default_IRQHandler
        B .

/* CRP Section - not needed for flashless devices */

;;;        SECTION .crp:CODE:ROOT(2)
;;;        DATA
/* Code Read Protection
NO_ISP  0x4E697370 -  Prevents sampling of pin PIO0_1 for entering ISP mode
CRP1    0x12345678 - Write to RAM command cannot access RAM below 0x10000300.
                   - Copy RAM to flash command can not write to Sector 0.
                   - Erase command can erase Sector 0 only when all sectors
                     are selected for erase.
                   - Compare command is disabled.
                   - Read Memory command is disabled.
CRP2    0x87654321 - Read Memory is disabled.
                   - Write to RAM is disabled.
                   - "Go" command is disabled.
                   - Copy RAM to flash is disabled.
                   - Compare is disabled.
CRP3    0x43218765 - Access to chip via the SWD pins is disabled. ISP entry
                     by pulling PIO0_1 LOW is disabled if a valid user code is
                     present in flash sector 0.
Caution: If CRP3 is selected, no future factory testing can be
performed on the device.
*/
;;;	    DCD	0xFFFFFFFF
;;;

        END
