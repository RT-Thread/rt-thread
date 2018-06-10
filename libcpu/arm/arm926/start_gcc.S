/*
 * File      : start_gcc.S
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2015, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2011-01-13     weety      first version
 * 2015-04-15     ArdaFu     Split from AT91SAM9260 BSP
 * 2015-04-21     ArdaFu     Remove remap code. Using mmu to map vector table
 * 2015-06-04     aozima     Align stack address to 8 byte.
 */

#include "rt_low_level_init.h"

#define S_FRAME_SIZE    (18*4)   //72

@#define S_SPSR          (17*4)   //SPSR
@#define S_CPSR          (16*4)   //CPSR
#define S_PC            (15*4)   //R15
@#define S_LR            (14*4)   //R14
@#define S_SP            (13*4)   //R13

@#define S_IP            (12*4)   //R12
@#define S_FP            (11*4)   //R11
@#define S_R10           (10*4)
@#define S_R9            (9*4)
@#define S_R8            (8*4)
@#define S_R7            (7*4)
@#define S_R6            (6*4)
@#define S_R5            (5*4)
@#define S_R4            (4*4)
@#define S_R3            (3*4)
@#define S_R2            (2*4)
@#define S_R1            (1*4)
@#define S_R0            (0*4)

#define MODE_SYS        0x1F
#define MODE_FIQ        0x11
#define MODE_IRQ        0x12
#define MODE_SVC        0x13
#define MODE_ABT        0x17
#define MODE_UND        0x1B
#define MODEMASK        0x1F

#define NOINT           0xC0

@;----------------------- Stack and Heap Definitions ---------------------------
    .section .nobss, "w"

    .space UND_STK_SIZE
    .align 3
    .global UND_STACK_START
UND_STACK_START:

    .space ABT_STK_SIZE
    .align 3
    .global ABT_STACK_START
ABT_STACK_START:

    .space FIQ_STK_SIZE
    .align 3
    .global FIQ_STACK_START
FIQ_STACK_START:

    .space IRQ_STK_SIZE
    .align 3
    .global IRQ_STACK_START
IRQ_STACK_START:

    .skip SYS_STK_SIZE
    .align 3
    .global SYS_STACK_START
SYS_STACK_START:

    .space SVC_STK_SIZE
    .align 3
    .global SVC_STACK_START
SVC_STACK_START:

@;--------------Jump vector table-----------------------------------------------
    .section .init, "ax"
    .arm

    .global start
start:
    LDR     PC, vector_reset
    LDR     PC, vector_undef
    LDR     PC, vector_swi
    LDR     PC, vector_pabt
    LDR     PC, vector_dabt
    LDR     PC, vector_resv
    LDR     PC, vector_irq
    LDR     PC, vector_fiq

vector_reset:
    .word  Reset_Handler
vector_undef:
    .word  Undef_Handler
vector_swi:
    .word  SWI_Handler
vector_pabt:
    .word  PAbt_Handler
vector_dabt:
    .word  DAbt_Handler
vector_resv:
    .word  Resv_Handler
vector_irq:
    .word  IRQ_Handler
vector_fiq:
    .word  FIQ_Handler

    .balignl     16,0xdeadbeef

@;----------------- Reset Handler ---------------------------------------------
    .global rt_low_level_init
    .global main
    .global Reset_Handler
Reset_Handler:
    @; Set the cpu to SVC32 mode
    MRS     R0, CPSR
    BIC     R0, R0, #MODEMASK
    ORR     R0, R0, #MODE_SVC|NOINT
    MSR     CPSR_cxsf, R0
    
    @; Set CO-Processor
    @; little-end，disbale I/D Cache MMU, vector table is 0x00000000
    MRC     P15, 0, R0, C1, C0, 0   @; Read CP15
    LDR     R1, =0x00003085         @; set clear bits
    BIC     R0, R0, R1
    MCR     P15, 0, R0, C1, C0, 0   @; Write CP15

    @; Call low level init function,
    @; disable and clear all IRQs, Init MMU, Init interrupt controller, etc.
    LDR     SP, =SVC_STACK_START
    LDR     R0, =rt_low_level_init
    BLX     R0

Setup_Stack:
    @; Setup Stack for each mode
    MRS     R0, CPSR
    BIC     R0, R0, #MODEMASK

    ORR     R1, R0, #MODE_UND|NOINT
    MSR     CPSR_cxsf, R1            @; Undef mode
    LDR     SP, =UND_STACK_START

    ORR     R1, R0, #MODE_ABT|NOINT
    MSR     CPSR_cxsf, R1            @; Abort mode
    LDR     SP, =ABT_STACK_START

    ORR     R1, R0, #MODE_IRQ|NOINT
    MSR     CPSR_cxsf, R1            @; IRQ mode
    LDR     SP, =IRQ_STACK_START

    ORR     R1, R0, #MODE_FIQ|NOINT
    MSR     CPSR_cxsf, R1            @; FIQ mode
    LDR     SP, =FIQ_STACK_START

    ORR     R1, R0, #MODE_SYS|NOINT
    MSR     CPSR_cxsf,R1             @; SYS/User mode
    LDR     SP, =SYS_STACK_START

    ORR     R1, R0, #MODE_SVC|NOINT
    MSR     CPSR_cxsf, R1            @; SVC mode
    LDR     SP, =SVC_STACK_START

    @; clear .bss
    MOV     R0, #0                   @; get a zero
    LDR     R1, =__bss_start__       @; bss start
    LDR     R2, =__bss_end__         @; bss end

bss_clear_loop:
    CMP     R1, R2                   @; check if data to clear
    STRLO   R0, [R1], #4             @; clear 4 bytes
    BLO     bss_clear_loop           @; loop until done

    @; call C++ constructors of global objects
    LDR     R0, =__ctors_start__
    LDR     R1, =__ctors_end__

ctor_loop:
    CMP     R0, R1
    BEQ     ctor_end
    LDR     R2, [R0], #4
    STMFD   SP!, {R0-R1}
    MOV     LR, PC
    BX      R2
    LDMFD   SP!, {R0-R1}
    B       ctor_loop
ctor_end:

    @; Enter the C code
    LDR     R0, =rtthread_startup
    BLX     R0

@;----------------- Exception Handler -----------------------------------------
    .global rt_hw_trap_udef
    .global rt_hw_trap_swi
    .global rt_hw_trap_pabt
    .global rt_hw_trap_dabt
    .global rt_hw_trap_resv
    .global rt_hw_trap_irq
    .global rt_hw_trap_fiq

    .global rt_interrupt_enter
    .global rt_interrupt_leave
    .global rt_thread_switch_interrupt_flag
    .global rt_interrupt_from_thread
    .global rt_interrupt_to_thread
    
    .align  5
Undef_Handler:
    SUB     SP, SP, #S_FRAME_SIZE
    STMIA   SP, {R0 - R12}          @; Calling R0-R12
    ADD     R8, SP, #S_PC
    STMDB   R8, {SP, LR}            @; Calling SP, LR
    STR     LR, [R8, #0]            @; Save calling PC
    MRS     R6, SPSR
    STR     R6, [R8, #4]            @; Save CPSR
    STR     R0, [R8, #8]            @; Save SPSR
    MOV     R0, SP
    BL      rt_hw_trap_udef
    
    .align  5
SWI_Handler:
    BL      rt_hw_trap_swi
    
    .align  5
PAbt_Handler:
    BL      rt_hw_trap_pabt

    .align  5
DAbt_Handler:
    SUB     SP, SP, #S_FRAME_SIZE
    STMIA   SP, {R0 - R12}          @; Calling R0-R12
    ADD     R8, SP, #S_PC
    STMDB   R8, {SP, LR}            @; Calling SP, LR
    STR     LR, [R8, #0]            @; Save calling PC
    MRS     R6, SPSR
    STR     R6, [R8, #4]            @; Save CPSR
    STR     R0, [R8, #8]            @; Save SPSR
    MOV     R0, SP
    BL      rt_hw_trap_dabt

    .align  5
Resv_Handler:
    BL      rt_hw_trap_resv

    .align  5
FIQ_Handler:
    STMFD   SP!, {R0-R7,LR}
    BL      rt_hw_trap_fiq
    LDMFD   SP!, {R0-R7,LR}
    SUBS    PC, LR, #4

    .align  5
IRQ_Handler:
    STMFD   SP!, {R0-R12,LR}
    BL      rt_interrupt_enter
    BL      rt_hw_trap_irq
    BL      rt_interrupt_leave

    @; If rt_thread_switch_interrupt_flag set,
    @; jump to rt_hw_context_switch_interrupt_do and don't return
    LDR     R0, =rt_thread_switch_interrupt_flag
    LDR     R1, [R0]
    CMP     R1, #1
    BEQ     rt_hw_context_switch_interrupt_do

    LDMFD   SP!, {R0-R12,LR}
    SUBS    PC, LR, #4

@;------ void rt_hw_context_switch_interrupt_do(rt_base_t flag) -----------------
rt_hw_context_switch_interrupt_do:
    MOV     R1,  #0                 @; Clear flag
    STR     R1,  [R0]               @; Save to flag variable

    LDMFD   SP!, {R0-R12,LR}        @; Reload saved registers
    STMFD   SP, {R0-R2}             @; Save R0-R2
    SUB     R1,  SP, #4*3           @; Save old task's SP to R1
    SUB     R2,  LR, #4             @; Save old task's PC to R2

    MRS     R0,  SPSR               @; Get CPSR of interrupt thread

    MSR     CPSR_c, #MODE_SVC|NOINT @; Switch to SVC mode and no interrupt

    STMFD   SP!, {R2}               @; Push old task's PC
    STMFD   SP!, {R3-R12,LR}        @; Push old task's LR,R12-R3
    LDMFD   R1, {R1-R3}
    STMFD   SP!, {R1-R3}            @; Push old task's R2-R0
    STMFD   SP!, {R0}               @; Push old task's CPSR

    LDR     R4,  =rt_interrupt_from_thread
    LDR     R5,  [R4]               @; R5 = stack ptr in old tasks's TCB
    STR     SP,  [R5]               @; Store SP in preempted tasks's TCB

    LDR     R6,  =rt_interrupt_to_thread
    LDR     R6,  [R6]               @; R6 = stack ptr in new tasks's TCB
    LDR     SP,  [R6]               @; Get new task's stack pointer

    LDMFD   SP!, {R4}               @; Pop new task's SPSR
    MSR     SPSR_cxsf, R4

    LDMFD   SP!, {R0-R12,LR,PC}^    @; pop new task's R0-R12,LR & PC SPSR 2 CPSR
