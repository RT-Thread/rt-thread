;/*****************************************************************************/
;/* S3C2440.S: Startup file for Samsung S3C440                                */
;/*****************************************************************************/
;/* <<< Use Configuration Wizard in Context Menu >>>                          */
;/*****************************************************************************/
;/* This file is part of the uVision/ARM development tools.                   */
;/* Copyright (c) 2005-2008 Keil Software. All rights reserved.               */
;/* This software may only be used under the terms of a valid, current,       */
;/* end user licence from KEIL for a compatible version of KEIL software      */
;/* development tools. Nothing else gives you the right to use this software. */
;/*****************************************************************************/


;/*
; *  The S3C2440.S code is executed after CPU Reset. This file may be
; *  translated with the following SET symbols. In uVision these SET
; *  symbols are entered under Options - ASM - Define.
; *
; *  NO_CLOCK_SETUP: when set the startup code will not initialize Clock
; *  (used mostly when clock is aLReady initialized from script .ini
; *  file).
; *
; *  NO_MC_SETUP: when set the startup code will not initialize Memory
; *  Controller (used mostly when clock is aLReady initialized from script
; *  .ini file).
; *
; *  NO_GP_SETUP: when set the startup code will not initialize General Ports
; *  (used mostly when clock is aLReady initialized from script .ini
; *  file).
; *
; *  RAM_INTVEC: when set the startup code copies exception vectors
; *  from execution address to on-chip RAM.
; */

;/*
; * File      : start_rvds.s
; * This file is part of RT-Thread RTOS
; * COPYRIGHT (C) 2006, RT-Thread Development Team
; *
; * The license and diSTRibution terms for this file may be
; * found in the file LICENSE in this diSTRibution or at
; * http://openlab.rt-thread.com/license/LICENSE
; *
; * Change Logs:
; * Date           Author       Notes
; * 2010-01-12     Gary Lee     Change the STRucture of the code, 
;				the configuration file's name is config.inc
; * 2010-01-22	   Gary Lee	Add interrupt config for startup 2440
; * 2010-01-23	   Gary Lee	Add copy myself for startup from nand
; */
		

;  Area Definition and Entry Point
;  Startup Code must be linked first at Address at which it expects to run.
;  Exception Vectors
;  Mapped to Address 0.
;  Absolute addressing mode must be used.
;  Dummy Handlers are implemented as infinite loops which can be modified.

                GET	config.inc

		PRESERVE8


                AREA    RESET, CODE, READONLY
                ARM

		EXPORT Entry_Point
Entry_Point
Vectors         LDR     PC, Reset_Addr
                LDR     PC, Undef_Addr
                LDR     PC, SWI_Addr
                LDR     PC, PAbt_Addr
                LDR     PC, DAbt_Addr
		NOP
                LDR     PC, IRQ_Addr
                LDR     PC, FIQ_Addr

Reset_Addr      DCD     Reset_Handler
Undef_Addr      DCD     Undef_Handler
SWI_Addr        DCD     SWI_Handler
PAbt_Addr       DCD     PAbt_Handler
DAbt_Addr       DCD     DAbt_Handler
                DCD     0                   ; Reserved Address
IRQ_Addr        DCD     IRQ_Handler
FIQ_Addr        DCD     FIQ_Handler

Undef_Handler   B       Undef_Handler
SWI_Handler     B       SWI_Handler
PAbt_Handler    B       PAbt_Handler
DAbt_Handler    B       DAbt_Handler
FIQ_Handler     B       FIQ_Handler

;=========================================================================
; Reset Handler

                EXPORT  Reset_Handler
Reset_Handler

		BL	WatchDog_Config		;  shutdown watchdog
		BL	Interrupt_Config	;  shutdown interrupt
        BL	SysClock_Config		;  setup system clock, default value is 400MHz
        BL	SDRAM_Config		;  setup sdram clock, default value is 100MHz
		;BL	Copymyself_Config	;  copy myself from 0x1000 with size of 1MB to sdram address of 0x30000000
		BL	GPIO_Config			;  setup gpio	
		BL	RAM_INTVEC_Config	;  install interrupt handler to sdram
		BL	Stack_Config		;  setup stack for every mode

								;  a technology about trampoline
		LDR	R1, =ON_THE_RAM
		ADD	PC, R1, #0
		NOP
		NOP
1
		B	%B1

ON_THE_RAM
								; setup by APCS
		MOV	FP, #0				; no previous frame, so fp=0
		MOV	a2, #0				; set argv to NULL
		
		IMPORT  __main
		BL	__main				; call main
		MOV	R0, #FLASH_BASE_ADDR 
		MOV	PC, R0				; otherwise, reboot

;=========================================================================
                IMPORT rt_interrupt_enter
                IMPORT rt_interrupt_leave
                IMPORT rt_thread_switch_interrput_flag
                IMPORT rt_interrupt_from_thread
                IMPORT rt_interrupt_to_thread
                IMPORT rt_hw_trap_irq
				IMPORT nand_read_ll

IRQ_Handler     PROC

                EXPORT IRQ_Handler
                STMFD   SP!, {R0-R12,LR}
                BL  rt_interrupt_enter
                BL  rt_hw_trap_irq
                BL  rt_interrupt_leave

                LDR R0, =rt_thread_switch_interrput_flag
                LDR R1, [R0]
                CMP R1, #1
                BEQ rt_hw_context_switch_interrupt_do

                LDMFD   SP!, {R0-R12,LR}
                SUBS    PC, LR, #4
                ENDP

rt_hw_context_switch_interrupt_do   PROC

                EXPORT rt_hw_context_switch_interrupt_do
                MOV     R1,  #0         ; clear flag
                STR     R1,  [R0]

                LDMFD   SP!, {R0-R12,LR}; reload saved registers
                STMFD   SP!, {R0-R3}    ; save R0-R3
                MOV     R1,  SP
                ADD     SP,  SP, #16    ; restore SP
                SUB     R2,  LR, #4     ; save old task's PC to R2

                MRS     R3,  SPSR       ; get cpsr of interrupt thread

                ; switch to SVC mode and no interrupt
                MSR     cpsr_c, #I_Bit|F_Bit|Mode_SVC

                STMFD   SP!, {R2}       ; push old task's PC
                STMFD   SP!, {r4-R12,LR}; push old task's LR,R12-r4
                MOV     r4,  R1         ; SPecial optimised code below
                MOV     r5,  R3
                LDMFD   r4!, {R0-R3}
                STMFD   SP!, {R0-R3}    ; push old task's R3-R0
                STMFD   SP!, {r5}       ; push old task's cpsr
                MRS     r4,  SPSR
                STMFD   SP!, {r4}       ; push old task's SPsr

                LDR     r4,  =rt_interrupt_from_thread
                LDR     r5,  [r4]
                STR     SP,  [r5]       ; store SP in preempted tasks's TCB

                LDR     r6,  =rt_interrupt_to_thread
                LDR     r6,  [r6]
                LDR     SP,  [r6]       ; get new task's stack pointer

                LDMFD   SP!, {r4}       ; pop new task's SPsr
                MSR     SPSR_cxsf, r4
                LDMFD   SP!, {r4}       ; pop new task's psr
                MSR     cpsr_cxsf, r4

                LDMFD   SP!, {R0-R12,LR} ; pop new task's R0-R12,LR & PC
				LDMFD	SP!, {PC}

                ENDP

; Use microlib
                IF      :DEF:__MICROLIB

                EXPORT  __heap_base
                EXPORT  __heap_limit

                ELSE

; User Initial Stack & Heap
                AREA    |.text|, CODE, READONLY

                IMPORT  __use_two_region_memory
                EXPORT  __user_initial_stackheap
__user_initial_stackheap

                LDR     R0, =  Heap_Mem
                LDR     R1, =(Stack_Mem + USR_Stack_Size)
                LDR     R2, = (Heap_Mem +      Heap_Size)
                LDR     R3, = Stack_Mem
                BX      LR
                ENDIF

;=========================================================================
; Subroutines 
WatchDog_Config	PROC
		IF      WT_SETUP != 0
                LDR     R0, =WT_BASE
                LDR     R1, =WTCON_Val
                LDR     R2, =WTDAT_Val
                STR     R2, [R0, #WTCNT_OFS]
                STR     R2, [R0, #WTDAT_OFS]
                STR     R1, [R0, #WTCON_OFS]
                ENDIF
		
		BX	LR
		ENDP

Interrupt_Config PROC

				LDR		R0,=INTMSK
				LDR		R1,=0xffffffff			;/*all interrupt disable关闭所有中断	*/
				STR		R1,[R0]

				LDR		R0,=INTSUBMSK
				LDR		R1,=0x7fff			;/*all sub interrupt disable关闭子中断	*/
				STR		R1,[R0]
		
				BX		LR
		ENDP
		

SysClock_Config	PROC
		IF      (:LNOT:(:DEF:NO_CLOCK_SETUP)):LAND:(CLOCK_SETUP != 0)
                LDR     R0, =CLOCK_BASE
                LDR     R1,      =LOCKTIME_Val
                STR     R1, [R0, #LOCKTIME_OFS]
                MOV     R1,      #CLKDIVN_Val
                STR     R1, [R0, #CLKDIVN_OFS]
                LDR     R1,      =CAMDIVN_Val
                STR     R1, [R0, #CAMDIVN_OFS]
                LDR     R1,      =MPLLCON_Val
                STR     R1, [R0, #MPLLCON_OFS]
                LDR     R1,      =UPLLCON_Val
                STR     R1, [R0, #UPLLCON_OFS]
                MOV     R1,      #CLKSLOW_Val
                STR     R1, [R0, #CLKSLOW_OFS]
                LDR     R1,      =CLKCON_Val
                STR     R1, [R0, #CLKCON_OFS]
                ENDIF
		
		BX	LR
		ENDP

Copymyself_Config PROC
						
				MOV		R1, #NAND_CTL_BASE				; inital       NAND初始化
				LDR		R2, =((7<<12)|(7<<8)|(7<<4)|(0<<0))	; initial value
				STR		R2, [R1, #oNFCONF]

				; reset nand flash						; 复位NAND
				LDR		R2, [R1, #oNFCONF]
				LDR		R2, =((1<<4)|(0<<1)|(1<<0))		; nFCE active
				STR		R2, [R1, #oNFCONT]
				LDR		R2, [R1, #oNFCONT]

				LDR		R2, =(0x6)						; RnB Clear
				STR		R2, [R1, #oNFSTAT]
				LDR		R2, [R1, #oNFSTAT]
				MOV		R2, #0xff						; reset command
				STRB	R2, [R1, #oNFCMD]

								; 延时
				MOV		R3, #0x0A
1
				SUBS	R3, R3, #1
				BNE		%B1

								; wait idle state 就绪	
2
				LDR		R2, [R1, #oNFSTAT]
				TST		R2, #0x04
				BEQ		%B2

				LDR		R2, [R1, #oNFCONF]
				ORR		R2, R2, #0x2					; nFCE inactive
				STR		R2, [R1, #oNFCONF]	

				LDR		SP, =4096						; nand_read.c needed
				LDR		R0, =0x30000000					; nand_read_ll argument 1  buffer addr
				MOV		R1, #4096						; nand_read_ll argument 2  start addr
				MOV		R2, #0x100000					; nand_read_ll argument 3  copy size
														; 1MB enough for this example
				BL		nand_read_ll

				BX		LR
		ENDP


SDRAM_Config	PROC
                IF      (:LNOT:(:DEF:NO_MC_SETUP)):LAND:(CLOCK_SETUP != 0)
                LDR     R0, =MC_BASE
                LDR     R1,      =BWSCON_Val
                STR     R1, [R0, #BWSCON_OFS]
                LDR     R1,      =BANKCON0_Val
                STR     R1, [R0, #BANKCON0_OFS]
                LDR     R1,      =BANKCON1_Val
                STR     R1, [R0, #BANKCON1_OFS]
                LDR     R1,      =BANKCON2_Val
                STR     R1, [R0, #BANKCON2_OFS]
                LDR     R1,      =BANKCON3_Val
                STR     R1, [R0, #BANKCON3_OFS]
                LDR     R1,      =BANKCON4_Val
                STR     R1, [R0, #BANKCON4_OFS]
                LDR     R1,      =BANKCON5_Val
                STR     R1, [R0, #BANKCON5_OFS]
                LDR     R1,      =BANKCON6_Val
                STR     R1, [R0, #BANKCON6_OFS]
                LDR     R1,      =BANKCON7_Val
                STR     R1, [R0, #BANKCON7_OFS]
                LDR     R1,      =REFRESH_Val
                STR     R1, [R0, #REFRESH_OFS]
                MOV     R1,      #BANKSIZE_Val
                STR     R1, [R0, #BANKSIZE_OFS]
                MOV     R1,      #MRSRB6_Val
                STR     R1, [R0, #MRSRB6_OFS]
                MOV     R1,      #MRSRB7_Val
                STR     R1, [R0, #MRSRB7_OFS]
                ENDIF
		
		BX	LR
		ENDP

GPIO_Config	PROC

		IF      (:LNOT:(:DEF:NO_GP_SETUP)):LAND:(GP_SETUP != 0)

                IF      GPA_SETUP != 0
                LDR     R0, =GPA_BASE
                LDR     R1, =GPACON_Val
                STR     R1, [R0, #GPCON_OFS]
                ENDIF

                IF      GPB_SETUP != 0
                LDR     R0, =GPB_BASE
                LDR     R1, =GPBCON_Val
                STR     R1, [R0, #GPCON_OFS]
                LDR     R1, =GPBUP_Val
                STR     R1, [R0, #GPUP_OFS]
                ENDIF

                IF      GPC_SETUP != 0
                LDR     R0, =GPC_BASE
                LDR     R1, =GPCCON_Val
                STR     R1, [R0, #GPCON_OFS]
                LDR     R1, =GPCUP_Val
                STR     R1, [R0, #GPUP_OFS]
                ENDIF

                IF      GPD_SETUP != 0
                LDR     R0, =GPD_BASE
                LDR     R1, =GPDCON_Val
                STR     R1, [R0, #GPCON_OFS]
                LDR     R1, =GPDUP_Val
                STR     R1, [R0, #GPUP_OFS]
                ENDIF

                IF      GPE_SETUP != 0
                LDR     R0, =GPE_BASE
                LDR     R1, =GPECON_Val
                STR     R1, [R0, #GPCON_OFS]
                LDR     R1, =GPEUP_Val
                STR     R1, [R0, #GPUP_OFS]
                ENDIF

                IF      GPF_SETUP != 0
                LDR     R0, =GPF_BASE
                LDR     R1, =GPFCON_Val
                STR     R1, [R0, #GPCON_OFS]
                LDR     R1, =GPFUP_Val
                STR     R1, [R0, #GPUP_OFS]
                ENDIF

                IF      GPG_SETUP != 0
                LDR     R0, =GPG_BASE
                LDR     R1, =GPGCON_Val
                STR     R1, [R0, #GPCON_OFS]
                LDR     R1, =GPGUP_Val
                STR     R1, [R0, #GPUP_OFS]
                ENDIF

                IF      GPH_SETUP != 0
                LDR     R0, =GPH_BASE
                LDR     R1, =GPHCON_Val
                STR     R1, [R0, #GPCON_OFS]
                LDR     R1, =GPHUP_Val
                STR     R1, [R0, #GPUP_OFS]
                ENDIF

                IF      GPJ_SETUP != 0
                LDR     R0, =GPJ_BASE
                LDR     R1, =GPJCON_Val
                STR     R1, [R0, #GPCON_OFS]
                LDR     R1, =GPJUP_Val
                STR     R1, [R0, #GPUP_OFS]
                ENDIF

                ENDIF
		
		BX	LR
		ENDP

RAM_INTVEC_Config	PROC		
		IF      :DEF:RAM_INTVEC
                ADR     R8,  Vectors    ; Source
                LDR     R9, =IRAM_BASE  ; Destination
                LDMIA   R8!, {R0-R7}    ; Load Vectors
                STMIA   R9!, {R0-R7}    ; Store Vectors
                LDMIA   R8!, {R0-R7}    ; Load Handler Addresses
                STMIA   R9!, {R0-R7}    ; Store Handler Addresses
                ENDIF
		
		BX	LR
		ENDP

Stack_Config	PROC
		LDR     R0, =Stack_Top

                MSR     CPSR_c, #Mode_UND:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #UND_Stack_Size

                MSR     CPSR_c, #Mode_ABT:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #ABT_Stack_Size

                MSR     CPSR_c, #Mode_FIQ:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #FIQ_Stack_Size

                MSR     CPSR_c, #Mode_IRQ:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #IRQ_Stack_Size

                MSR     CPSR_c, #Mode_SVC:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #SVC_Stack_Size

                ; MSR     CPSR_c, #Mode_USR
                MOV     SP, R0
                SUB     SL, SP, #USR_Stack_Size
		
		BX	LR
		ENDP

                END
