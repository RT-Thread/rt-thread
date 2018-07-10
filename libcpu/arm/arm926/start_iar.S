;/*
; * File      : start.S
; * This file is part of RT-Thread RTOS
; * COPYRIGHT (C) 2006, RT-Thread Development Team
; *
; *  This program is free software; you can redistribute it and/or modify
; *  it under the terms of the GNU General Public License as published by
; *  the Free Software Foundation; either version 2 of the License, or
; *  (at your option) any later version.
; *
; *  This program is distributed in the hope that it will be useful,
; *  but WITHOUT ANY WARRANTY; without even the implied warranty of
; *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
; *  GNU General Public License for more details.
; *
; *  You should have received a copy of the GNU General Public License along
; *  with this program; if not, write to the Free Software Foundation, Inc.,
; *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
; *
; * Change Logs:
; * Date           Author       Notes
; * 2011-01-13     weety      first version
; * 2015-04-15     ArdaFu     Split from AT91SAM9260 BSP
; * 2015-04-21     ArdaFu     Remove remap code. Using mmu to map vector table
; * 2015-06-04     aozima     Align stack address to 8 byte.
; */

#include "rt_low_level_init.h"

#define S_FRAME_SIZE    (18*4)   ;72

;#define S_SPSR          (17*4)   ;SPSR
;#define S_CPSR          (16*4)   ;CPSR
#define S_PC            (15*4)   ;R15
;#define S_LR            (14*4)   ;R14
;#define S_SP            (13*4)   ;R13

;#define S_IP            (12*4)   ;R12
;#define S_FP            (11*4)   ;R11
;#define S_R10           (10*4)
;#define S_R9            (9*4)
;#define S_R8            (8*4)
;#define S_R7            (7*4)
;#define S_R6            (6*4)
;#define S_R5            (5*4)
;#define S_R4            (4*4)
;#define S_R3            (3*4)
;#define S_R2            (2*4)
;#define S_R1            (1*4)
;#define S_R0            (0*4)

#define MODE_SYS        0x1F
#define MODE_FIQ        0x11
#define MODE_IRQ        0x12
#define MODE_SVC        0x13
#define MODE_ABT        0x17
#define MODE_UND        0x1B
#define MODEMASK        0x1F

#define NOINT           0xC0

;----------------------- Stack and Heap Definitions ----------------------------
    MODULE ?cstartup
    SECTION .noinit:DATA:NOROOT(3)
    DATA

    ALIGNRAM 3
    DS8 UND_STK_SIZE
    PUBLIC UND_STACK_START
UND_STACK_START:

    ALIGNRAM 3
    DS8 ABT_STK_SIZE
    PUBLIC ABT_STACK_START
ABT_STACK_START:

    ALIGNRAM 3
    DS8 FIQ_STK_SIZE
    PUBLIC FIQ_STACK_START
FIQ_STACK_START:

    ALIGNRAM 3
    DS8 IRQ_STK_SIZE
    PUBLIC IRQ_STACK_START
IRQ_STACK_START:

    ALIGNRAM 3
    DS8 SYS_STK_SIZE
    PUBLIC SYS_STACK_START
SYS_STACK_START:

    ALIGNRAM 3
    DS8 SVC_STK_SIZE
    PUBLIC SVC_STACK_START
SVC_STACK_START:

;--------------Jump vector table------------------------------------------------
    SECTION .intvec:CODE:ROOT(2)
    ARM
    PUBLIC Entry_Point
Entry_Point:
__iar_init$$done:               ; The interrupt vector is not needed
                                ; until after copy initialization is done
    LDR     PC, vector_reset
    LDR     PC, vector_undef
    LDR     PC, vector_swi
    LDR     PC, vector_pabt
    LDR     PC, vector_dabt
    LDR     PC, vector_resv
    LDR     PC, vector_irq
    LDR     PC, vector_fiq

vector_reset:
    DC32 Reset_Handler
vector_undef:
    DC32 Undef_Handler
vector_swi:
    DC32 SWI_Handler
vector_pabt:
    DC32 PAbt_Handler
vector_dabt:
    DC32 DAbt_Handler
vector_resv:
    DC32 Resv_Handler
vector_irq:
    DC32 IRQ_Handler
vector_fiq:
    DC32 FIQ_Handler

;----------------- Reset Handler -----------------------------------------------
    EXTERN rt_low_level_init
    EXTERN ?main
    PUBLIC __iar_program_start
__iar_program_start:
Reset_Handler:
    ; Set the cpu to SVC32 mode
    MRS     R0, CPSR
    BIC     R0, R0, #MODEMASK
    ORR     R0, R0, #MODE_SVC|NOINT
    MSR     CPSR_cxsf, R0
    
    ; Set CO-Processor
    ; little-end，disbale I/D Cache MMU, vector table is 0x00000000
    MRC     P15, 0, R0, C1, C0, 0   ; Read CP15
    LDR     R1, =0x00003085         ; set clear bits
    BIC     R0, R0, R1
    MCR     P15, 0, R0, C1, C0, 0   ; Write CP15

    ; Call low level init function,
    ; disable and clear all IRQs, Init MMU, Init interrupt controller, etc.
    LDR     SP, =SVC_STACK_START
    LDR     R0, =rt_low_level_init
    BLX     R0

Setup_Stack:
    ; Setup Stack for each mode
    MRS     R0, CPSR
    BIC     R0, R0, #MODEMASK

    ORR     R1, R0, #MODE_UND|NOINT
    MSR     CPSR_cxsf, R1            ; Undef mode
    LDR     SP, =UND_STACK_START

    ORR     R1,R0,#MODE_ABT|NOINT
    MSR     CPSR_cxsf,R1             ; Abort mode
    LDR     SP, =ABT_STACK_START

    ORR     R1,R0,#MODE_IRQ|NOINT
    MSR     CPSR_cxsf,R1             ; IRQ mode
    LDR     SP, =IRQ_STACK_START

    ORR     R1,R0,#MODE_FIQ|NOINT
    MSR     CPSR_cxsf,R1             ; FIQ mode
    LDR     SP, =FIQ_STACK_START

    ORR     R1,R0,#MODE_SYS|NOINT
    MSR     CPSR_cxsf,R1             ; SYS/User mode
    LDR     SP, =SYS_STACK_START

    ORR     R1,R0,#MODE_SVC|NOINT
    MSR     CPSR_cxsf,R1             ; SVC mode
    LDR     SP, =SVC_STACK_START
    
    ; Enter the C code 
    LDR     R0, =?main
    BLX     R0

;----------------- Exception Handler -------------------------------------------
    IMPORT rt_hw_trap_udef
    IMPORT rt_hw_trap_swi
    IMPORT rt_hw_trap_pabt
    IMPORT rt_hw_trap_dabt
    IMPORT rt_hw_trap_resv
    IMPORT rt_hw_trap_irq
    IMPORT rt_hw_trap_fiq

    IMPORT rt_interrupt_enter
    IMPORT rt_interrupt_leave
    IMPORT rt_thread_switch_interrupt_flag
    IMPORT rt_interrupt_from_thread
    IMPORT rt_interrupt_to_thread

    SECTION .text:CODE:ROOT(2)
    ARM
Undef_Handler:
    SUB     SP, SP, #S_FRAME_SIZE
    STMIA   SP, {R0 - R12}          ; Calling R0-R12
    ADD     R8, SP, #S_PC
    STMDB   R8, {SP, LR}            ; Calling SP, LR
    STR     LR, [R8, #0]            ; Save calling PC
    MRS     R6, SPSR
    STR     R6, [R8, #4]            ; Save CPSR
    STR     R0, [R8, #8]            ; Save SPSR
    MOV     R0, SP
    BL      rt_hw_trap_udef

SWI_Handler:
    BL      rt_hw_trap_swi

PAbt_Handler:
    BL      rt_hw_trap_pabt

DAbt_Handler:
    SUB     SP, SP, #S_FRAME_SIZE
    STMIA   SP, {R0 - R12}          ; Calling R0-R12
    ADD     R8, SP, #S_PC
    STMDB   R8, {SP, LR}            ; Calling SP, LR
    STR     LR, [R8, #0]            ; Save calling PC
    MRS     R6, SPSR
    STR     R6, [R8, #4]            ; Save CPSR
    STR     R0, [R8, #8]            ; Save SPSR
    MOV     R0, SP
    BL      rt_hw_trap_dabt

Resv_Handler:
    BL      rt_hw_trap_resv

IRQ_Handler:
    STMFD   SP!, {R0-R12,LR}
    BL      rt_interrupt_enter
    BL      rt_hw_trap_irq
    BL      rt_interrupt_leave

    ; If rt_thread_switch_interrupt_flag set,
    ; jump to rt_hw_context_switch_interrupt_do and don't return
    LDR     R0, =rt_thread_switch_interrupt_flag
    LDR     R1, [R0]
    CMP     R1, #1
    BEQ     rt_hw_context_switch_interrupt_do

    LDMFD   SP!, {R0-R12,LR}
    SUBS    PC, LR, #4

FIQ_Handler:
    STMFD   SP!, {R0-R7,LR}
    BL      rt_hw_trap_fiq
    LDMFD   SP!, {R0-R7,LR}
    SUBS    PC, LR, #4

;------ void rt_hw_context_switch_interrupt_do(rt_base_t flag) -----------------
rt_hw_context_switch_interrupt_do:
    MOV     R1,  #0                 ; Clear flag
    STR     R1,  [R0]               ; Save to flag variable

    LDMFD   SP!, {R0-R12,LR}        ; Reload saved registers
    STMFD   SP, {R0-R2}             ; Save R0-R2
    SUB     R1,  SP, #4*3           ; Save old task's SP to R1
    SUB     R2,  LR, #4             ; Save old task's PC to R2

    MRS     R0,  SPSR               ; Get CPSR of interrupt thread

    MSR     CPSR_c, #MODE_SVC|NOINT ; Switch to SVC mode and no interrupt

    STMFD   SP!, {R2}               ; Push old task's PC
    STMFD   SP!, {R3-R12,LR}        ; Push old task's LR,R12-R3
    LDMFD   R1, {R1-R3}
    STMFD   SP!, {R1-R3}            ; Push old task's R2-R0
    STMFD   SP!, {R0}               ; Push old task's CPSR

    LDR     R4,  =rt_interrupt_from_thread
    LDR     R5,  [R4]               ; R5 = stack ptr in old tasks's TCB
    STR     SP,  [R5]               ; Store SP in preempted tasks's TCB

    LDR     R6,  =rt_interrupt_to_thread
    LDR     R6,  [R6]               ; R6 = stack ptr in new tasks's TCB
    LDR     SP,  [R6]               ; Get new task's stack pointer

    LDMFD   SP!, {R4}               ; Pop new task's SPSR
    MSR     SPSR_cxsf, R4

    LDMFD   SP!, {R0-R12,LR,PC}^    ; pop new task's R0-R12,LR & PC SPSR to CPSR
    END
