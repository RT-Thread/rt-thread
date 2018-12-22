/**************************************************
 *
 * Part one of the system initialization code, contains low-level
 * initialization, plain thumb variant.
 *
 * Copyright 2009 IAR Systems. All rights reserved.
 *
 * $Revision: 33183 $
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
        EXTERN  IRC_Only_SystemInit

        PUBLIC  __vector_table
        PUBLIC  __vector_table_0x1c
        DATA
__vector_table
        DCD     sfe(CSTACK)                 ; Top of Stack
        DCD     Reset_Handler               ; Reset Handler
        DCD     NMI_Handler                 ; NMI Handler
        DCD     HardFault_Handler           ; Hard Fault Handler
__vector_table_0x1c
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     SVC_Handler                 ; SVCall Handler
        DCD     0                           ; Reserved
        DCD     0                           ; Reserved
        DCD     PendSV_Handler              ; PendSV Handler
        DCD     SysTick_Handler             ; SysTick Handler


        ; External Interrupts
        DCD     SPI0_IRQHandler             ; SPI0 controller
        DCD     SPI1_IRQHandler             ; SPI1 controller
        DCD     0                           ; Reserved
        DCD     UART0_IRQHandler            ; UART0
        DCD     UART1_IRQHandler            ; UART1
        DCD     UART2_IRQHandler            ; UART2
        DCD     0                           ; Reserved
        DCD     I2C1_IRQHandler             ; I2C1
        DCD     I2C0_IRQHandler             ; I2C0 controller
        DCD     SCT_IRQHandler              ; Smart Counter Timer
        DCD     MRT_IRQHandler              ; Multi-Rate Timer
        DCD     CMP_IRQHandler              ; Comparator
        DCD     WDT_IRQHandler              ; PIO1 (0:11)
        DCD     BOD_IRQHandler              ; Brown Out Detect
        DCD     FLASH_IRQHandler            ; Flash interrupt
        DCD     WKT_IRQHandler              ; Wakeup timer
        DCD     ADC_SEQA_IRQHandler         ; ADC sequence A completeion
        DCD     ADC_SEQB_IRQHandler         ; ADC sequence B completeion
        DCD     ADC_THCMP_IRQHandler        ; ADC threshold compare
        DCD     ADC_OVR_IRQHandler          ; ADC overrun
        DCD     DMA_IRQHandler              ; DMA
        DCD     I2C2_IRQHandler             ; I2C2
        DCD     I2C3_IRQHandler             ; I2C3
        DCD     0                           ; Reserved
        DCD     PININT0_IRQHandler          ; PIO INT0
        DCD     PININT1_IRQHandler         ; PIO INT1
        DCD     PININT2_IRQHandler         ; PIO INT2
        DCD     PININT3_IRQHandler         ; PIO INT3
        DCD     PININT4_IRQHandler         ; PIO INT4
        DCD     PININT5_IRQHandler         ; PIO INT5
        DCD     PININT6_IRQHandler         ; PIO INT6
        DCD     PININT7_IRQHandler         ; PIO INT7

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;
        THUMB
        
        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
Reset_Handler
        LDR     R0, =SystemInit
        BLX     R0
        LDR     R0, =__iar_program_start
        BX      R0

       
 
        SECTION .text:CODE:REORDER:NOROOT(1)

        PUBWEAK NMI_Handler
        PUBWEAK HardFault_Handler
        PUBWEAK SVC_Handler
        PUBWEAK DebugMon_Handler
        PUBWEAK PendSV_Handler
        PUBWEAK SysTick_Handler
        PUBWEAK	SPI0_IRQHandler
        PUBWEAK SPI1_IRQHandler
        PUBWEAK	UART0_IRQHandler
        PUBWEAK UART1_IRQHandler
        PUBWEAK	UART2_IRQHandler
        PUBWEAK	I2C1_IRQHandler
        PUBWEAK	I2C0_IRQHandler
        PUBWEAK	SCT_IRQHandler
        PUBWEAK	MRT_IRQHandler
        PUBWEAK	CMP_IRQHandler
        PUBWEAK	WDT_IRQHandler
        PUBWEAK	BOD_IRQHandler
        PUBWEAK FLASH_IRQHandler
        PUBWEAK	WKT_IRQHandler
        PUBWEAK ADC_SEQA_IRQHandler
        PUBWEAK ADC_SEQB_IRQHandler
        PUBWEAK ADC_THCMP_IRQHandler
        PUBWEAK ADC_OVR_IRQHandler
        PUBWEAK DMA_IRQHandler
        PUBWEAK I2C2_IRQHandler
        PUBWEAK I2C3_IRQHandler
        PUBWEAK	PININT0_IRQHandler
        PUBWEAK	PININT1_IRQHandler
        PUBWEAK	PININT2_IRQHandler
        PUBWEAK	PININT3_IRQHandler
        PUBWEAK	PININT4_IRQHandler
        PUBWEAK	PININT5_IRQHandler
        PUBWEAK	PININT6_IRQHandler
        PUBWEAK	PININT7_IRQHandler

NMI_Handler:
HardFault_Handler:
SVC_Handler:
DebugMon_Handler:
PendSV_Handler:
SysTick_Handler:
SPI0_IRQHandler:
SPI1_IRQHandler:
UART0_IRQHandler:
UART1_IRQHandler:
UART2_IRQHandler:
I2C1_IRQHandler:
I2C0_IRQHandler:
SCT_IRQHandler:
MRT_IRQHandler:
CMP_IRQHandler:
WDT_IRQHandler:
BOD_IRQHandler:
FLASH_IRQHandler:
WKT_IRQHandler:
ADC_SEQA_IRQHandler:
ADC_SEQB_IRQHandler:
ADC_THCMP_IRQHandler:
ADC_OVR_IRQHandler:
DMA_IRQHandler:
I2C2_IRQHandler:
I2C3_IRQHandler:
PININT0_IRQHandler:
PININT1_IRQHandler:
PININT2_IRQHandler:
PININT3_IRQHandler:
PININT4_IRQHandler:
PININT5_IRQHandler:
PININT6_IRQHandler:
PININT7_IRQHandler:
Default_Handler:
        B Default_Handler

        END
