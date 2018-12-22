;/*
; * @brief LPC5410x startup code for Keil
; *
; * @note
; * Copyright(C) NXP Semiconductors, 2014
; * All rights reserved.
; *
; * @par
; * Software that is described herein is for illustrative purposes only
; * which provides customers with programming information regarding the
; * LPC products.  This software is supplied "AS IS" without any warranties of
; * any kind, and NXP Semiconductors and its licensor disclaim any and
; * all warranties, express or implied, including all implied warranties of
; * merchantability, fitness for a particular purpose and non-infringement of
; * intellectual property rights.  NXP Semiconductors assumes no responsibility
; * or liability for the use of the software, conveys no license or rights under any
; * patent, copyright, mask work right, or any other intellectual property rights in
; * or to any products. NXP Semiconductors reserves the right to make changes
; * in the software without notification. NXP Semiconductors also makes no
; * representation or warranty that such application will be suitable for the
; * specified use without further testing or modification.
; *
; * @par
; * Permission to use, copy, modify, and distribute this software and its
; * documentation is hereby granted, under NXP Semiconductors' and its
; * licensor's relevant copyrights in the software, without fee, provided that it
; * is used in conjunction with NXP Semiconductors microcontrollers.  This
; * copyright, permission, and disclaimer notice must appear in all copies of
; * this code.
; */

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

Heap_Size       EQU     0x00000100

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit

                PRESERVE8
                THUMB

; Vector Table Mapped to Address 0 at Reset
                AREA    RESET, DATA, READONLY
                EXPORT  __Vectors

__Vectors       DCD     __initial_sp              ; Top of Stack
                DCD     Reset_Handler             ; Reset Handler

                DCD     NMI_Handler
                DCD     HardFault_Handler
                DCD     MemManage_Handler
                DCD     BusFault_Handler
                DCD     UsageFault_Handler
__vector_table_0x1c
                DCD     0                         ; Checksum of the first 7 words
                DCD     0
                DCD     0                         ; Enhanced image marker, set to 0x0 for legacy boot
                DCD     0                         ; Pointer to enhanced boot block, set to 0x0 for legacy boot
                DCD     SVC_Handler
                DCD     DebugMon_Handler
                DCD     0
                DCD     PendSV_Handler
                DCD     SysTick_Handler

        ; External Interrupts
                DCD     WDT_IRQHandler            ; Watchdog
                DCD     BOD_IRQHandler            ; Brown Out Detect
                DCD     Reserved_IRQHandler       ; Reserved
                DCD     DMA_IRQHandler            ; DMA Controller
                DCD     GINT0_IRQHandler          ; GPIO Group0 Interrupt
                DCD     PIN_INT0_IRQHandler       ; PIO INT0
                DCD     PIN_INT1_IRQHandler       ; PIO INT1
                DCD     PIN_INT2_IRQHandler       ; PIO INT2
                DCD     PIN_INT3_IRQHandler       ; PIO INT3
                DCD     UTICK_IRQHandler          ; UTICK timer  				
                DCD     MRT_IRQHandler            ; Multi-Rate Timer
                DCD     CT32B0_IRQHandler         ; CT32B0
                DCD     CT32B1_IRQHandler         ; CT32B1
                DCD     CT32B2_IRQHandler         ; CT32B2
                DCD     CT32B3_IRQHandler         ; CT32B3
                DCD     CT32B4_IRQHandler         ; CT32B4
                DCD     SCT0_IRQHandler           ; Smart Counter Timer 
                DCD     UART0_IRQHandler          ; UART0             
                DCD     UART1_IRQHandler          ; UART1            
                DCD     UART2_IRQHandler          ; UART2
                DCD     UART3_IRQHandler          ; UART3
                DCD     I2C0_IRQHandler           ; I2C0 controller  
                DCD     I2C1_IRQHandler           ; I2C1 controller  
                DCD     I2C2_IRQHandler           ; I2C2 controller  
                DCD     SPI0_IRQHandler           ; SPI0 controller				
                DCD     SPI1_IRQHandler           ; SPI1 controller
                DCD     ADC_SEQA_IRQHandler       ; ADC0 A sequence (A/D Converter) interrupt
                DCD     ADC_SEQB_IRQHandler       ; ADC0 B sequence (A/D Converter) interrupt
                DCD     ADC_THCMP_IRQHandler      ; ADC THCMP and OVERRUN ORed
                DCD     RTC_IRQHandler            ; RTC Timer
                DCD     Reserved_IRQHandler       ; Reserved
                DCD     MAILBOX_IRQHandler        ; Mailbox 
                DCD     GINT1_IRQHandler          ; GPIO Group1 Interrupt
                DCD     PIN_INT4_IRQHandler       ; PIO INT4
                DCD     PIN_INT5_IRQHandler       ; PIO INT5
                DCD     PIN_INT6_IRQHandler       ; PIO INT6
                DCD     PIN_INT7_IRQHandler       ; PIO INT7
                DCD     Reserved_IRQHandler       ; Reserved				
                DCD     Reserved_IRQHandler       ; Reserved				
                DCD     Reserved_IRQHandler       ; Reserved
                DCD     RIT_IRQHandler            ; RITimer
                DCD     Reserved41_IRQHandler     ; Reserved                         
                DCD     Reserved42_IRQHandler     ; Reserved                         
                DCD     Reserved43_IRQHandler     ; Reserved                         
                DCD     Reserved44_IRQHandler     ; Reserved      

;//   <h> Code Read Protection level (CRP)
;//     <o>    CRP_Level:
;//                     <0xFFFFFFFF=> Disabled
;//                     <0x4E697370=> NO_ISP
;//                     <0x12345678=> CRP1
;//                     <0x87654321=> CRP2
;//                     <0x43218765=> CRP3 (Are you sure?)
;//   </h>
;CRP_Level		EQU		0xFFFFFFFF

				;IF		:LNOT::DEF:NO_CRP
				;AREA	|.ARM.__at_0x02FC|, CODE, READONLY
;CRP_Key			DCD		0xFFFFFFFF
				;ENDIF

				AREA	|.text|, CODE, READONLY

;cpu_id	 		EQU		0xE000ED00
;cpu_ctrl 		EQU		0x40000300
;coproc_boot 	EQU		0x40000304
;coproc_stack	EQU		0x40000308

;rel_vals
				;DCD		cpu_id, cpu_ctrl, coproc_boot, coproc_stack
				;DCW		0xFFF, 0xC24

; Reset Handler - shared for both cores
Reset_Handler   PROC
                EXPORT	Reset_Handler				[WEAK]
                EXPORT	SystemInit					[WEAK]
                IMPORT	__main

				;IF		:LNOT::DEF:SLAVEBOOT
				 ;Both the M0+ and M4 core come via this shared startup code,
				 ;but the M0+ and M4 core have different vector tables.
				 ;Determine if the core executing this code is the master or
				 ;the slave and handle each core state individually.
;shared_boot_entry
				;LDR		r6, =rel_vals
				;MOVS	r4, #0							; Flag for slave core (0)
				;MOVS	r5, #1

				;; Determine which core (M0+ or M4) this code is running on
				;; r2 = (((*cpu_id) >> 4) & 0xFFF); (M4 core == 0xC24)
;get_current_core_id
				;LDR		r0, [r6, #0]
				;LDR		r1, [r0]						; r1 = CPU ID status
				;LSRS	r1, r1, #4						; Right justify 12 CPU ID bits
				;LDRH	r2, [r6, #16]					; Mask for CPU ID bits
				;ANDS	r2, r1, r2						; r2 = ARM COrtex CPU ID
				;LDRH	r3, [r6, #18]					; Mask for CPU ID bits
				;CMP		r3, r2							; Core ID matches M4 identifier
				;BNE		get_master_status
				;MOV		r4, r5							; Set flag for master core (1)

				;; Determine if M4 core is the master or slave
				;; r3 = ((*cpu_ctrl) & 1); (0 == m0+, 1 == M4)
;get_master_status
				;LDR		r0, [r6, #4]
				;LDR		r3, [r0]			            ; r3 = SYSCON co-processor CPU control status
				;ANDS	r3, r3, r5						; r3 = (Bit 0: 1 = M4 is master, 0 = M4 is slave)

				;; Select boot based on selected master core and core ID
;select_boot
				;EORS 	r3, r3, r4						; r4 = (Bit 0: 0 = master, 1 = slave)
				;BNE		slave_boot
				;B		normal_boot

				;; Slave boot
;slave_boot
				;LDR		r0, [r6, #8]
				;LDR		r2, [r0]						; r1 = SYSCON co-processor boot address
				;CMP		r2, #0							; Slave boot address = 0 (not set up)?
				;BEQ		cpu_sleep
				;LDR		r0, [r6, #12]
				;LDR		r1, [r0]						; r5 = SYSCON co-processor stack address
				;MOV		sp, r1							; Update slave CPU stack pointer
				;; Be sure to update VTOR for the slave MCU to point to the
				;; slave vector table in boot memory
				;BX		r2								; Jump to slave boot address

				;; Slave isn't yet setup for system boot from the master
				;; so sleep until the master sets it up and then reboots it
;cpu_sleep
				;MOV		sp, r5							; Will force exception if something happens
;cpu_sleep_wfi
				;WFI										; Sleep forever until master reboots
				;B		cpu_sleep_wfi
				;ENDIF

				; Normal boot for master/slave
;normal_boot
				LDR		r0, =SystemInit
				BLX		r0
				LDR		r0, =__main
				BX		r0
				ENDP

; For cores with SystemInit() or __main(), the code will sleep the MCU
SystemInit		PROC
                EXPORT  SystemInit					[WEAK]
				BX		lr
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
MemManage_Handler     PROC
                EXPORT  MemManage_Handler         [WEAK]
                B       .
                ENDP
BusFault_Handler PROC
                EXPORT  BusFault_Handler          [WEAK]
                B       .
                ENDP
UsageFault_Handler PROC
                EXPORT  UsageFault_Handler        [WEAK]
                B       .
                ENDP
SVC_Handler     PROC
                EXPORT  SVC_Handler               [WEAK]
                B       .
                ENDP
DebugMon_Handler PROC
                EXPORT  DebugMon_Handler               [WEAK]
                B       .
                ENDP
PendSV_Handler  PROC
                EXPORT  PendSV_Handler            [WEAK]
                B       .
                ENDP
SysTick_Handler PROC
                EXPORT  SysTick_Handler           [WEAK]
                B       .
                ENDP

Default_Handler PROC
               EXPORT WDT_IRQHandler              [WEAK] ; Watchdog
               EXPORT BOD_IRQHandler              [WEAK] ; Brown Out Detect
               EXPORT DMA_IRQHandler              [WEAK] ; DMA Controller
               EXPORT GINT0_IRQHandler            [WEAK] ; GPIO Group0 Interrupt
               EXPORT PIN_INT0_IRQHandler         [WEAK] ; PIO INT0
               EXPORT PIN_INT1_IRQHandler         [WEAK] ; PIO INT1
               EXPORT PIN_INT2_IRQHandler         [WEAK] ; PIO INT2
               EXPORT PIN_INT3_IRQHandler         [WEAK] ; PIO INT3
               EXPORT UTICK_IRQHandler            [WEAK] ; UTICK timer  				
               EXPORT MRT_IRQHandler              [WEAK] ; Multi-Rate Timer
               EXPORT CT32B0_IRQHandler           [WEAK] ; CT32B0
               EXPORT CT32B1_IRQHandler           [WEAK] ; CT32B1
               EXPORT CT32B2_IRQHandler           [WEAK] ; CT32B2
               EXPORT CT32B3_IRQHandler           [WEAK] ; CT32B3
               EXPORT CT32B4_IRQHandler           [WEAK] ; CT32B4
               EXPORT UART0_IRQHandler            [WEAK] ; UART0             
               EXPORT SCT0_IRQHandler             [WEAK] ; Smart Counter Timer 
               EXPORT UART1_IRQHandler            [WEAK] ; UART1            
               EXPORT UART2_IRQHandler            [WEAK] ; UART2
               EXPORT UART3_IRQHandler            [WEAK] ; UART3
               EXPORT I2C0_IRQHandler             [WEAK] ; I2C0 controller  
               EXPORT I2C1_IRQHandler             [WEAK] ; I2C1 controller  
               EXPORT I2C2_IRQHandler             [WEAK] ; I2C2 controller  
               EXPORT SPI0_IRQHandler             [WEAK] ; SPI0 controller				
               EXPORT SPI1_IRQHandler             [WEAK] ; SPI1 controller
               EXPORT ADC_SEQA_IRQHandler         [WEAK] ; ADC0 A sequence (A/D Converter) interrupt
               EXPORT ADC_SEQB_IRQHandler         [WEAK] ; ADC0 B sequence (A/D Converter) interrupt
               EXPORT ADC_THCMP_IRQHandler        [WEAK] ; ADC THCMP and OVERRUN ORed
               EXPORT RTC_IRQHandler              [WEAK] ; RTC Timer
               EXPORT MAILBOX_IRQHandler          [WEAK] ; Mailbox 
               EXPORT GINT1_IRQHandler            [WEAK] ; GPIO Group1 Interrupt
               EXPORT PIN_INT4_IRQHandler         [WEAK] ; PIO INT4
               EXPORT PIN_INT5_IRQHandler         [WEAK] ; PIO INT5
               EXPORT PIN_INT6_IRQHandler         [WEAK] ; PIO INT6
               EXPORT PIN_INT7_IRQHandler         [WEAK] ; PIO INT7
               EXPORT RIT_IRQHandler              [WEAK] ; RITimer
               EXPORT Reserved41_IRQHandler       [WEAK] ; Reserved                         
               EXPORT Reserved42_IRQHandler       [WEAK] ; Reserved       
               EXPORT Reserved43_IRQHandler       [WEAK] ; Reserved                         
               EXPORT Reserved44_IRQHandler       [WEAK] ; Reserved  
               EXPORT Reserved_IRQHandler         [WEAK] ; Reserved  

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
Reserved_IRQHandler         ; Reserved  

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
