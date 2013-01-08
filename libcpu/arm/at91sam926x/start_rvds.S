;/*
; * File      : start_rvds.S
; * This file is part of RT-Thread RTOS
; * COPYRIGHT (C) 2006, RT-Thread Development Team
; *
; * The license and distribution terms for this file may be
; * found in the file LICENSE in this distribution or at
; * http://www.rt-thread.org/license/LICENSE
; *
; * Change Logs:
; * Date           Author       Notes
; * 2011-08-14     weety      first version
; */


; Standard definitions of Mode bits and Interrupt (I & F) flags in PSRs

Mode_USR        EQU     0x10
Mode_FIQ        EQU     0x11
Mode_IRQ        EQU     0x12
Mode_SVC        EQU     0x13
Mode_ABT        EQU     0x17
Mode_UND        EQU     0x1B
Mode_SYS        EQU     0x1F

SVCMODE         EQU   		0x13
MODEMASK        EQU   		0x1f

I_Bit           EQU     0x80            ; when I bit is set, IRQ is disabled
F_Bit           EQU     0x40            ; when F bit is set, FIQ is disabled


;----------------------- Stack and Heap Definitions ----------------------------

;// <h> Stack Configuration (Stack Sizes in Bytes)
;//   <o0> Undefined Mode      <0x0-0xFFFFFFFF:8>
;//   <o1> Supervisor Mode     <0x0-0xFFFFFFFF:8>
;//   <o2> Abort Mode          <0x0-0xFFFFFFFF:8>
;//   <o3> Fast Interrupt Mode <0x0-0xFFFFFFFF:8>
;//   <o4> Interrupt Mode      <0x0-0xFFFFFFFF:8>
;//   <o5> User/System Mode    <0x0-0xFFFFFFFF:8>
;// </h>

UND_Stack_Size  EQU     512
SVC_Stack_Size  EQU     4096
ABT_Stack_Size  EQU     512
FIQ_Stack_Size  EQU     1024
IRQ_Stack_Size  EQU     1024
USR_Stack_Size  EQU     512

ISR_Stack_Size  EQU     (UND_Stack_Size + SVC_Stack_Size + ABT_Stack_Size + \
                         FIQ_Stack_Size + IRQ_Stack_Size)

                AREA    STACK, NOINIT, READWRITE, ALIGN=3

Stack_Mem       SPACE   USR_Stack_Size
__initial_sp    SPACE   ISR_Stack_Size
Stack_Top


;// <h> Heap Configuration
;//   <o>  Heap Size (in Bytes) <0x0-0xFFFFFFFF>
;// </h>

Heap_Size       EQU     0x00000000

                AREA    HEAP, NOINIT, READWRITE, ALIGN=3
__heap_base
Heap_Mem        SPACE   Heap_Size
__heap_limit


;----------------------- Memory Definitions ------------------------------------

AT91_MATRIX_BASE    EQU  0xffffee00
AT91_MATRIX_MRCR	   EQU  (AT91_MATRIX_BASE + 0x100)
AT91_MATRIX_RCB0    EQU  0x00000001
AT91_MATRIX_RCB1    EQU  0x00000002
AT91_AIC_BASE       EQU  0xfffff000
AT91_AIC_IDCR       EQU  0x124
AT91_AIC_ICCR       EQU  0x128

;----------------------- CODE --------------------------------------------------

                PRESERVE8


; Area Definition and Entry Point
;  Startup Code must be linked first at Address at which it expects to run.

                AREA    RESET, CODE, READONLY
                ARM

; Exception Vectors
;  Mapped to Address 0.
;  Absolute addressing mode must be used.
;  Dummy Handlers are implemented as infinite loops which can be modified.

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
;DAbt_Handler    B       DAbt_Handler
FIQ_Handler     B       FIQ_Handler

;*
;*************************************************************************
;*
;* Interrupt handling
;*
;*************************************************************************
;*
; DAbt Handler
DAbt_Handler
               IMPORT rt_hw_trap_dabt

                	sub 	sp, sp, #72
	                stmia 	sp, {r0 - r12}   		;/* Calling r0-r12					*/
                    add		r8, sp, #60
	                stmdb   r8, {sp, lr}            ;/* Calling SP, LR					*/
	                str		lr, [r8, #0]            ;/* Save calling PC					*/
	                mrs		r6, spsr
	                str		r6, [r8, #4]            ;/* Save CPSR						*/
	                str		r0, [r8, #8]            ;/* Save OLD_R0						*/
	                mov		r0, sp

	                bl 		rt_hw_trap_dabt


;##########################################
; Reset Handler

                EXPORT  Reset_Handler
Reset_Handler


; set the cpu to SVC32 mode-----------------------------------------------------

                MRS		R0,CPSR
               	BIC		R0,R0,#MODEMASK
	               ORR		R0,R0,#SVCMODE
	               MSR		CPSR_cxsf,R0
                LDR	R1, =AT91_AIC_BASE
	               LDR	R0, =0xffffffff
	               STR	R0, [R1, #AT91_AIC_IDCR]
	               STR	R0, [R1, #AT91_AIC_ICCR]

; remap internal ram to 0x00000000 address
	               LDR	R0, =AT91_MATRIX_MRCR
	               LDR	R1, =(AT91_MATRIX_RCB0|AT91_MATRIX_RCB1)
	               STR	R1, [R0]


; Copy Exception Vectors to Internal RAM ---------------------------------------

                ADR     R8,  Vectors    ; Source
                LDR     R9, =0x00  ; Destination
                LDMIA   R8!, {R0-R7}    ; Load Vectors
                STMIA   R9!, {R0-R7}    ; Store Vectors
                LDMIA   R8!, {R0-R7}    ; Load Handler Addresses
                STMIA   R9!, {R0-R7}    ; Store Handler Addresses


; Setup Stack for each mode ----------------------------------------------------

                LDR     R0, =Stack_Top

;  Enter Undefined Instruction Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_UND:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #UND_Stack_Size

;  Enter Abort Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_ABT:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #ABT_Stack_Size

;  Enter FIQ Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_FIQ:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #FIQ_Stack_Size

;  Enter IRQ Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_IRQ:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #IRQ_Stack_Size

;  Enter Supervisor Mode and set its Stack Pointer
                MSR     CPSR_c, #Mode_SVC:OR:I_Bit:OR:F_Bit
                MOV     SP, R0
                SUB     R0, R0, #SVC_Stack_Size

;  Enter User Mode and set its Stack Pointer
                ; MSR     CPSR_c, #Mode_USR
                MOV     SP, R0
                SUB     SL, SP, #USR_Stack_Size

; Enter the C code -------------------------------------------------------------

                IMPORT  __main
                LDR     R0, =__main
                BX      R0

                IMPORT rt_interrupt_enter
                IMPORT rt_interrupt_leave
                IMPORT rt_thread_switch_interrupt_flag
                IMPORT rt_interrupt_from_thread
                IMPORT rt_interrupt_to_thread
                IMPORT rt_hw_trap_irq

IRQ_Handler     PROC
                EXPORT IRQ_Handler
                STMFD   sp!, {r0-r12,lr}
                BL  rt_interrupt_enter
                BL  rt_hw_trap_irq
                BL  rt_interrupt_leave

                ; if rt_thread_switch_interrupt_flag set, jump to
                ; rt_hw_context_switch_interrupt_do and don't return
                LDR r0, =rt_thread_switch_interrupt_flag
                LDR r1, [r0]
                CMP r1, #1
                BEQ rt_hw_context_switch_interrupt_do

                LDMFD   sp!, {r0-r12,lr}
                SUBS    pc, lr, #4
                ENDP

; /*
; * void rt_hw_context_switch_interrupt_do(rt_base_t flag)
; */
rt_hw_context_switch_interrupt_do   PROC
                EXPORT rt_hw_context_switch_interrupt_do
                MOV     r1,  #0         ; clear flag
                STR     r1,  [r0]

                LDMFD   sp!, {r0-r12,lr}; reload saved registers
                STMFD   sp!, {r0-r3}    ; save r0-r3
                MOV     r1,  sp
                ADD     sp,  sp, #16    ; restore sp
                SUB     r2,  lr, #4     ; save old task's pc to r2

                MRS     r3,  spsr       ; get cpsr of interrupt thread

                ; switch to SVC mode and no interrupt
				MSR 	cpsr_c, #I_Bit:OR:F_Bit:OR:Mode_SVC

                STMFD   sp!, {r2}       ; push old task's pc
                STMFD   sp!, {r4-r12,lr}; push old task's lr,r12-r4
                MOV     r4,  r1         ; Special optimised code below
                MOV     r5,  r3
                LDMFD   r4!, {r0-r3}
                STMFD   sp!, {r0-r3}    ; push old task's r3-r0
                STMFD   sp!, {r5}       ; push old task's cpsr
                MRS     r4,  spsr
                STMFD   sp!, {r4}       ; push old task's spsr

                LDR     r4,  =rt_interrupt_from_thread
                LDR     r5,  [r4]
                STR     sp,  [r5]       ; store sp in preempted tasks's TCB

                LDR     r6,  =rt_interrupt_to_thread
                LDR     r6,  [r6]
                LDR     sp,  [r6]       ; get new task's stack pointer

                LDMFD   sp!, {r4}       ; pop new task's spsr
                MSR     spsr_cxsf, r4
                LDMFD   sp!, {r4}       ; pop new task's psr
                MSR     cpsr_cxsf, r4

                LDMFD   sp!, {r0-r12,lr,pc} ; pop new task's r0-r12,lr & pc
                ENDP

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


                END

