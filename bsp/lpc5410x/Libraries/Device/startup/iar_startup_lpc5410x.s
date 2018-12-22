;/*****************************************************************************
; * @file:    startup_LPC5410x.s
; * @purpose: CMSIS Cortex-M4/M0+ Core Device Startup File
; *           for the NXP LPC5410x Device Series (manually edited)
; * @version: V1.00
; * @date:    19. October 2009
; *----------------------------------------------------------------------------
; *
; * Copyright (C) 2009 ARM Limited. All rights reserved.
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
        DCD     0							; Checksum of the first 7 words
        DCD     0
        DCD     0							; Enhanced image marker, set to 0x0 for legacy boot
        DCD     0							; Pointer to enhanced boot block, set to 0x0 for legacy boot
        DCD     SVC_Handler
        DCD     DebugMon_Handler
        DCD     0
        DCD     PendSV_Handler
        DCD     SysTick_Handler

        ; External Interrupts
        DCD     WDT_IRQHandler              ; Watchdog
        DCD     BOD_IRQHandler              ; Brown Out Detect
        DCD     Reserved_IRQHandler         ; Reserved
        DCD     DMA_IRQHandler              ; DMA Controller
        DCD     GINT0_IRQHandler            ; GPIO Group0 Interrupt
        DCD     PIN_INT0_IRQHandler         ; PIO INT0
        DCD     PIN_INT1_IRQHandler         ; PIO INT1
        DCD     PIN_INT2_IRQHandler         ; PIO INT2
        DCD     PIN_INT3_IRQHandler         ; PIO INT3
        DCD     UTICK_IRQHandler            ; UTICK timer  				
        DCD     MRT_IRQHandler              ; Multi-Rate Timer
        DCD     CT32B0_IRQHandler           ; CT32B0
        DCD     CT32B1_IRQHandler           ; CT32B1
        DCD     CT32B2_IRQHandler           ; CT32B2
        DCD     CT32B3_IRQHandler           ; CT32B3
        DCD     CT32B4_IRQHandler           ; CT32B4
        DCD     SCT0_IRQHandler             ; Smart Counter Timer 
        DCD     UART0_IRQHandler            ; UART0             
        DCD     UART1_IRQHandler            ; UART1            
        DCD     UART2_IRQHandler            ; UART2
        DCD     UART3_IRQHandler            ; UART3
        DCD     I2C0_IRQHandler             ; I2C0 controller  
        DCD     I2C1_IRQHandler             ; I2C1 controller  
        DCD     I2C2_IRQHandler             ; I2C2 controller  
        DCD     SPI0_IRQHandler             ; SPI0 controller				
        DCD     SPI1_IRQHandler             ; SPI1 controller
        DCD     ADC_SEQA_IRQHandler         ; ADC0 A sequence (A/D Converter) interrupt
        DCD     ADC_SEQB_IRQHandler         ; ADC0 B sequence (A/D Converter) interrupt
        DCD     ADC_THCMP_IRQHandler        ; ADC THCMP and OVERRUN ORed
        DCD     RTC_IRQHandler              ; RTC Timer
        DCD     Reserved_IRQHandler         ; Reserved
        DCD     MAILBOX_IRQHandler          ; Mailbox 
        DCD     GINT1_IRQHandler            ; GPIO Group1 Interrupt
        DCD     PIN_INT4_IRQHandler         ; PIO INT4
        DCD     PIN_INT5_IRQHandler         ; PIO INT5
        DCD     PIN_INT6_IRQHandler         ; PIO INT6
        DCD     PIN_INT7_IRQHandler         ; PIO INT7
        DCD     Reserved_IRQHandler         ; Reserved				
        DCD     Reserved_IRQHandler         ; Reserved				
        DCD     Reserved_IRQHandler         ; Reserved
        DCD     RIT_IRQHandler              ; RITimer
        DCD     Reserved41_IRQHandler       ; Reserved                         
        DCD     Reserved42_IRQHandler       ; Reserved                         
        DCD     Reserved43_IRQHandler       ; Reserved                         
        DCD     Reserved44_IRQHandler       ; Reserved                         
__Vectors_End

__Vectors       EQU   __vector_table
__Vectors_Size 	EQU 	__Vectors_End - __Vectors


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;
;; Default interrupt handlers.
;;

#if !defined(SLAVEBOOT)
        DATA
cpu_id	 		EQU		0xE000ED00
cpu_ctrl 		EQU		0x40000300
coproc_boot 	EQU		0x40000304
coproc_stack	EQU		0x40000308
rel_vals
				DC32	cpu_id, cpu_ctrl, coproc_boot, coproc_stack
				DC16	0xFFF, 0xC24
#endif

        THUMB

        PUBWEAK Reset_Handler
        SECTION .text:CODE:REORDER:NOROOT(2)
; Reset Handler - shared for both cores
Reset_Handler

#if !defined(SLAVEBOOT)
; Both the M0+ and M4 core come via this shared startup code,
				; but the M0+ and M4 core have different vector tables.
				; Determine if the core executing this code is the master or
				; the slave and handle each core state individually.
shared_boot_entry
				LDR		r6, =rel_vals
				MOVS	r4, #0							; Flag for slave core (0)
				MOVS	r5, #1

				; Determine which core (M0+ or M4) this code is running on
				; r2 = (((*cpu_id) >> 4) & 0xFFF); (M4 core == 0xC24)
get_current_core_id
				LDR		r0, [r6, #0]
				LDR		r1, [r0]						; r1 = CPU ID status
				LSRS	r1, r1, #4						; Right justify 12 CPU ID bits
				LDRH	r2, [r6, #16]					; Mask for CPU ID bits
				ANDS	r2, r1, r2						; r2 = ARM COrtex CPU ID
				LDRH	r3, [r6, #18]					; Mask for CPU ID bits
				CMP		r3, r2							; Core ID matches M4 identifier
				BNE		get_master_status
				MOV		r4, r5							; Set flag for master core (1)

				; Determine if M4 core is the master or slave
				; r3 = ((*cpu_ctrl) & 1); (0 == m0+, 1 == M4)
get_master_status
				LDR		r0, [r6, #4]
				LDR		r3, [r0]			            ; r3 = SYSCON co-processor CPU control status
				ANDS	r3, r3, r5						; r3 = (Bit 0: 1 = M4 is master, 0 = M4 is slave)

				; Select boot based on selected master core and core ID
select_boot
				EORS 	r3, r3, r4						; r4 = (Bit 0: 0 = master, 1 = slave)
				BNE		slave_boot
				B		normal_boot

				; Slave boot
slave_boot
				LDR		r0, [r6, #8]
				LDR		r2, [r0]						; r1 = SYSCON co-processor boot address
				CMP		r2, #0							; Slave boot address = 0 (not set up)?
				BEQ		cpu_sleep
				LDR		r0, [r6, #12]
				LDR		r1, [r0]						; r5 = SYSCON co-processor stack address
				MOV		sp, r1							; Update slave CPU stack pointer
				; Be sure to update VTOR for the slave MCU to point to the
				; slave vector table in boot memory
				BX		r2								; Jump to slave boot address

				; Slave isn't yet setup for system boot from the master
				; so sleep until the master sets it up and then reboots it
cpu_sleep
				MOV		sp, r5							; Will force exception if something happens
cpu_sleep_wfi
				WFI										; Sleep forever until master reboots
				B		cpu_sleep_wfi
#endif ; defined(SLAVEBOOT)

				; Normal boot for master/slave
normal_boot
				LDR		r0, =SystemInit
				BLX		r0
				LDR		r0, =__iar_program_start
				BX		r0

; For cores with SystemInit() or __iar_program_start(), the code will sleep the MCU
        PUBWEAK SystemInit
        SECTION .text:CODE:REORDER:NOROOT(1)
SystemInit
        BX		LR

        PUBWEAK NMI_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
NMI_Handler
        B .

        PUBWEAK HardFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
HardFault_Handler
        B .

        PUBWEAK MemManage_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
MemManage_Handler
        B .

        PUBWEAK BusFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
BusFault_Handler
        B .

        PUBWEAK UsageFault_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
UsageFault_Handler
        B .

        PUBWEAK SVC_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SVC_Handler
        B .

        PUBWEAK DebugMon_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
DebugMon_Handler
        B .

        PUBWEAK PendSV_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
PendSV_Handler
        B .

        PUBWEAK SysTick_Handler
        SECTION .text:CODE:REORDER:NOROOT(1)
SysTick_Handler
        B .

	PUBWEAK Reserved_IRQHandler
        SECTION .text:CODE:REORDER:NOROOT(1)
Reserved_IRQHandler
        B .

		PUBWEAK WDT_IRQHandler              ; Watchdog
		PUBWEAK BOD_IRQHandler              ; Brown Out Detect
		PUBWEAK DMA_IRQHandler              ; DMA Controller
		PUBWEAK GINT0_IRQHandler            ; GPIO Group0 Interrupt
		PUBWEAK PIN_INT0_IRQHandler         ; PIO INT0
		PUBWEAK PIN_INT1_IRQHandler         ; PIO INT1
		PUBWEAK PIN_INT2_IRQHandler         ; PIO INT2
		PUBWEAK PIN_INT3_IRQHandler         ; PIO INT3
		PUBWEAK UTICK_IRQHandler            ; UTICK timer  				
		PUBWEAK MRT_IRQHandler              ; Multi-Rate Timer
		PUBWEAK CT32B0_IRQHandler           ; CT32B0
		PUBWEAK CT32B1_IRQHandler           ; CT32B1
		PUBWEAK CT32B2_IRQHandler           ; CT32B2
		PUBWEAK CT32B3_IRQHandler           ; CT32B3
		PUBWEAK CT32B4_IRQHandler           ; CT32B4
		PUBWEAK UART0_IRQHandler            ; UART0             
		PUBWEAK SCT0_IRQHandler             ; Smart Counter Timer 
		PUBWEAK UART1_IRQHandler            ; UART1            
		PUBWEAK UART2_IRQHandler            ; UART2
		PUBWEAK UART3_IRQHandler            ; UART3
		PUBWEAK I2C0_IRQHandler             ; I2C0 controller  
		PUBWEAK I2C1_IRQHandler             ; I2C1 controller  
		PUBWEAK I2C2_IRQHandler             ; I2C2 controller  
		PUBWEAK SPI0_IRQHandler             ; SPI0 controller				
		PUBWEAK SPI1_IRQHandler             ; SPI1 controller
		PUBWEAK ADC_SEQA_IRQHandler         ; ADC0 A sequence (A/D Converter) interrupt
		PUBWEAK ADC_SEQB_IRQHandler         ; ADC0 B sequence (A/D Converter) interrupt
		PUBWEAK ADC_THCMP_IRQHandler        ; ADC THCMP and OVERRUN ORed
		PUBWEAK RTC_IRQHandler              ; RTC Timer
		PUBWEAK MAILBOX_IRQHandler          ; Mailbox 
		PUBWEAK GINT1_IRQHandler            ; GPIO Group1 Interrupt
		PUBWEAK PIN_INT4_IRQHandler         ; PIO INT4
		PUBWEAK PIN_INT5_IRQHandler         ; PIO INT5
		PUBWEAK PIN_INT6_IRQHandler         ; PIO INT6
		PUBWEAK PIN_INT7_IRQHandler         ; PIO INT7
		PUBWEAK RIT_IRQHandler              ; RITimer
		PUBWEAK Reserved41_IRQHandler       ; Reserved                         
		PUBWEAK Reserved42_IRQHandler       ; Reserved       
		PUBWEAK Reserved43_IRQHandler       ; Reserved                         
		PUBWEAK Reserved44_IRQHandler       ; Reserved  

WDT_IRQHandler              ; Watchdog
BOD_IRQHandler              ; Brown Out Detect
DMA_IRQHandler              ; DMA Controller
GINT0_IRQHandler            ; GPIO Group0 Interrupt
PIN_INT0_IRQHandler         ; PIO INT0
PIN_INT1_IRQHandler         ; PIO INT1
PIN_INT2_IRQHandler         ; PIO INT2
PIN_INT3_IRQHandler         ; PIO INT3
UTICK_IRQHandler            ; UTICK timer  				
MRT_IRQHandler              ; Multi-Rate Timer
CT32B0_IRQHandler           ; CT32B0
CT32B1_IRQHandler           ; CT32B1
CT32B2_IRQHandler           ; CT32B2
CT32B3_IRQHandler           ; CT32B3
CT32B4_IRQHandler           ; CT32B4
UART0_IRQHandler            ; UART0             
SCT0_IRQHandler             ; Smart Counter Timer 
UART1_IRQHandler            ; UART1            
UART2_IRQHandler            ; UART2
UART3_IRQHandler            ; UART3
I2C0_IRQHandler             ; I2C0 controller  
I2C1_IRQHandler             ; I2C1 controller  
I2C2_IRQHandler             ; I2C2 controller  
SPI0_IRQHandler             ; SPI0 controller				
SPI1_IRQHandler             ; SPI1 controller
ADC_SEQA_IRQHandler         ; ADC0 A sequence (A/D Converter) interrupt
ADC_SEQB_IRQHandler         ; ADC0 B sequence (A/D Converter) interrupt
ADC_THCMP_IRQHandler        ; ADC THCMP and OVERRUN ORed
RTC_IRQHandler              ; RTC Timer
MAILBOX_IRQHandler          ; Mailbox 
GINT1_IRQHandler            ; GPIO Group1 Interrupt
PIN_INT4_IRQHandler         ; PIO INT4
PIN_INT5_IRQHandler         ; PIO INT5
PIN_INT6_IRQHandler         ; PIO INT6
PIN_INT7_IRQHandler         ; PIO INT7
RIT_IRQHandler              ; RITimer
Reserved41_IRQHandler       ; Reserved                         
Reserved42_IRQHandler       ; Reserved       
Reserved43_IRQHandler       ; Reserved                         
Reserved44_IRQHandler       ; Reserved  

Default_Handler:
        B .

        END
