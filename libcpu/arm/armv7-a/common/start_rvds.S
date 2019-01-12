/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#include "rtconfig.h"

    AREA	START, CODE, READONLY, ALIGN=5
    PRESERVE8

#define Mode_USR		0x10
#define Mode_FIQ		0x11
#define Mode_IRQ		0x12
#define Mode_SVC		0x13
#define Mode_ABT		0x17
#define Mode_UND		0x1B
#define Mode_SYS		0x1F
#define Mode_MASK		0x1F

#define T_Bit			0x20			        // When the T bit is set, it is in the thumb state, otherwise it is in the arm state.
#define F_Bit			0x40			        // Disable FIQ interrupt when F bit is set
#define I_Bit			0x80			        // Disable IRQ interrupt when I bit is set

#define UND_Stack_Size	0x00000200
#define SVC_Stack_Size	0x00000400
#define ABT_Stack_Size	0x00000200
#define FIQ_Stack_Size	0x00000200
#define IRQ_Stack_Size	0x00000400
#define USR_Stack_Size	0x00000200

#define ISR_Stack_Size  (UND_Stack_Size + SVC_Stack_Size + ABT_Stack_Size + FIQ_Stack_Size + IRQ_Stack_Size + USR_Stack_Size)

    EXPORT      stack_start
    EXPORT      stack_top
stack_start
    SPACE       ISR_Stack_Size
stack_top

    EXPORT      _reset
_reset
    mrs         r0, cpsr
    bic         r0, r0, #Mode_MASK
    orr         r0, r0, #(Mode_SVC + I_Bit + F_Bit)
    msr         cpsr_c, r0

    bl          stack_setup

    // disable cache(icache/dcache/branch prediction)
    IMPORT      rt_cpu_cache_disable
    bl          rt_cpu_cache_disable
    // disable mmu
    IMPORT      rt_cpu_mmu_disable
    bl          rt_cpu_mmu_disable
    // enable cache
    IMPORT      rt_cpu_cache_enable
    bl          rt_cpu_cache_enable

    IMPORT      rt_cpu_vfp_neon_access_enable
    bl          rt_cpu_vfp_neon_access_enable

    // FPEXC, Floating-Point Exception Control register
    // [ref]DDI0406C_d_armv7ar_arm.pdf: B4.1.57 FPEXC, Floating-Point Exception Control register, VMSA
    //      Bit     Field               Description
    //      31      EX                  Exception bit.
    //      30      EN                  Enable bit.
    //      29      reverse
    mov         r0, #0x40000000                     // enable vfp&neon
    vmsr        fpexc, r0

    // init fpscr
    IMPORT      rt_cpu_fpscr_init
    bl          rt_cpu_fpscr_init

    ldr         pc, _rtthread_startup
_rtthread_startup
    IMPORT	    __main
    dcd		    __main

stack_setup
    ldr         r0, =stack_top

    // Set the UNDEF mode stack pointer
    msr         cpsr_c, #(Mode_UND + I_Bit + F_Bit)
    mov         sp, r0
    sub         r0, r0, #UND_Stack_Size

    // Set the ABORT mode stack pointer
    msr         cpsr_c, #(Mode_ABT + I_Bit + F_Bit)
    mov         sp, r0
    sub         r0, r0, #ABT_Stack_Size

    // Set the FIQ mode stack pointer
    msr         cpsr_c, #(Mode_FIQ + I_Bit + F_Bit)
    mov         sp, r0
    sub         r0, r0, #FIQ_Stack_Size

    // Set the IRQ mode stack pointer
    msr         cpsr_c, #(Mode_IRQ + I_Bit + F_Bit)
    mov         sp, r0
    sub         r0, r0, #IRQ_Stack_Size

    // Set the SVC mode stack pointer
    msr         cpsr_c, #(Mode_SVC + I_Bit + F_Bit)
    mov         sp, r0
    sub         r0, r0, #SVC_Stack_Size

    // Set the USER mode stack pointer
    mov         sp, r0
    sub         sl, sp, #USR_Stack_Size
    bx          lr

trap_vectors
    IMPORT      rt_hw_trap_undef
    dcd         rt_hw_trap_undef
    IMPORT      rt_hw_trap_swi
    dcd         rt_hw_trap_swi
    IMPORT      rt_hw_trap_pabt
    dcd         rt_hw_trap_pabt
    IMPORT      rt_hw_trap_dabt
    dcd         rt_hw_trap_dabt

    // rt_hw_register
    //              offset
    // |  rev  |    68, Make the number of registers pushed in even(8 bytes align)
    // |  cpsr |    64
    // |  pc   |    60
    // |  lr   |    56
    // |  sp   |    52
    // |  r12  |    48
    // |  ...  |
    // |  r0   |    0
exception_deal
    mrs         r2, cpsr
    mrs         r3, spsr
    orr         r3, r3, #(I_Bit + F_Bit)
    msr         cpsr_c, r3						    // return to previous mode and mask irq/fiq
    mov         r0, r0							    // delay
    str         sp, [r0, #52]					    // rt_hw_register.sp
    str         lr, [r0, #56]					    // rt_hw_register.lr
    msr         cpsr_c, r2						    // return undef mode

    str         lr, [r0, #60]					    // rt_hw_register.pc
    mrs         r3, spsr
    str         r3, [r0, #64]					    // rt_hw_register.cpsr
    str         r0, [r0, #68]   				    // rt_hw_register.rev

    mov         r0, sp
    ldr         lr, =trap_vectors
    add         pc, lr, r1, LSL #2
    b           .                                   // dead loop

    EXPORT      vector_undef
vector_undef
    sub         lr, lr, #4
    sub         sp, sp, #72						    // 72 = sizeof(rt_hw_register)
    stmia       sp, {r0-r12}                        // 1) save r0~r12
    mov         r0, sp
    mov         r1, #0
    b           exception_deal

    EXPORT	    vector_swi
vector_swi
    sub         lr, lr, #4
    sub         sp, sp, #72						    // 72 = sizeof(rt_hw_register)
    stmia       sp, {r0-r12}                        // 1) save r0~r12
    mov         r0, sp
    mov         r1, #1
    b           exception_deal

    EXPORT	    vector_pabt
vector_pabt
    sub         lr, lr, #4
    sub         sp, sp, #72						    // 72 = sizeof(rt_hw_register)
    stmia       sp, {r0-r12}                        // 1) save r0~r12
    mov         r0, sp
    mov         r1, #2
    b           exception_deal

    EXPORT	    vector_dabt
vector_dabt
    sub         lr, lr, #4
    sub         sp, sp, #72						    // 72 = sizeof(rt_hw_register)
    stmia       sp, {r0-r12}                        // 1) save r0~r12
    mov         r0, sp
    mov         r1, #3
    b           exception_deal

    EXPORT	    vector_resv
vector_resv
    b           .

    EXPORT	    vector_fiq
vector_fiq
    sub         lr, lr, #4
    stmfd       sp!, {r0-r4, lr}                    // r4 is used to ensure that the stack is aligned 8 bytes.
    IMPORT	    rt_hw_trap_fiq
    bl          rt_hw_trap_fiq
    ldmfd       sp!, {r0-r4, lr}
    movs        pc, lr

    IMPORT	    rt_interrupt_enter
    IMPORT	    rt_interrupt_leave
    IMPORT	    rt_thread_switch_interrupt_flag
    IMPORT	    rt_interrupt_from_thread
    IMPORT	    rt_interrupt_to_thread

    // [ref]IHI0042F_aapcs.pdf: VFP register usage conventions (VFP v2, v3 and the Advanced SIMD Extension)
    // Registers s16-s31 (d8-d15, q4-q7) must be preserved across subroutine calls; 
    // registers s0-s15 (d0-d7, q0-q3) do not need to be preserved (and can be used for passing arguments or returning results in standard procedure-call variants). 
    // Registers d16-d31 (q8-q15), if present, do not need to be preserved.
    EXPORT	    vector_irq
vector_irq
    sub         lr, lr, #4
    stmfd       sp!, {r0-r3, lr}                // 1) push {r0-r3, lr}

    vmrs        r3, fpscr
    stmfd       sp!, {r3}                       // 2) push {fpscr}
#if defined(RT_USING_VFP_NEON_Q16)
    vpush       {q8-q15}                        // 3) push {q8-q15}
#endif
    vpush       {q0-q3}                         // 4) push {q0-q3}

    bl          rt_interrupt_enter
    IMPORT	    rt_hw_trap_irq
    bl          rt_hw_trap_irq
    bl          rt_interrupt_leave

    ldr         r0, =rt_thread_switch_interrupt_flag
    ldr         r1, [r0]
    cmp         r1, #1
    beq         rt_hw_context_switch_interrupt_do

    // if rt_thread_switch_interrupt_flag == 0
    vpop        {q0-q3}                         // 1) pop {q0-q3}
#if defined(RT_USING_VFP_NEON_Q16)
    vpop        {q8-q15}                        // 2) pop {q8-q15}
#endif
    ldmfd       sp!, {r3}                       // 3) pop {fpscr}
    vmsr        fpscr, r3                       //    Restore fpscr

    ldmfd       sp!, {r0-r3, pc}^               // 4) pop {r0-r3, pc}

    // if rt_thread_switch_interrupt_flag == 1
rt_hw_context_switch_interrupt_do
    mov         r1, #0
    str         r1, [r0]                        // rt_thread_switch_interrupt_flag = 0

    vpop        {q0-q3}                         // 1) pop {q0-q3}
#if defined(RT_USING_VFP_NEON_Q16)
    vpop        {q8-q15}                        // 2) pop {q8-q15}
#endif
    ldmfd       sp!, {r3}                       // 3) pop {fpscr}
    vmsr        fpscr, r3                       // Restore fpscr

    ldmfd       sp!, {r0-r3, lr}                // 4) pop {r0-r3, pc}

    stmfd       sp, {r0-r2}
    sub         r1, sp, #4*3
    // --------SP
    // |  r2  |
    // |  r1  |
    // |  r0  | r1 is now pointing here

    mrs         r0, spsr
    bic         r0, #T_Bit
    tst         lr, #0x01
    orrne       r0, r0, #T_Bit                  // r0: cpsr
    mov         r2, lr                          // r2: pc

    // enter svc mode, and disable irq/fiq
    msr         cpsr_c, #(I_Bit + F_Bit + Mode_SVC)

    // thread stack
    //              words           note
    // |  pc  |     1(4bytes)
    // |  lr  |     1
    // |  r12 |     1
    // |  ... |
    // |  r1  |     1
    // |  r0  |     1
    // | cpsr |     1
    // | fpscr|     1
    // |   0  |     1               Make the number of registers pushed in even
    // |  q15 |     4               RT_USING_VFP_NEON_Q16
    // |  ... |     4               RT_USING_VFP_NEON_Q16
    // |  q8  |     4               RT_USING_VFP_NEON_Q16
    // |  q7  |     4
    // |  ... |     4
    // |  q0  |     4
    // --------SP
    stmfd       sp!, {r2}                       // 1) push {pc}
    stmfd       sp!, {r3-r12, lr}               // 2) push {r3-r12, lr_svc}
    ldmfd       r1, {r1-r3}                     //    r0-r2 is restored to r1-r3
    stmfd       sp!, {r1-r3}                    //    push {r0-r2}
    stmfd       sp!, {r0}                       // 3) push {cpsr}

    vmrs        r3, fpscr
    mov         r2, #0
    stmfd       sp!, {r2-r3}                    // 4) push {0,fpscr}
#if defined(RT_USING_VFP_NEON_Q16)
    vpush       {q8-q15}                        // 5) push {q8-q15}
#endif
    vpush       {q0-q7}                         // 6) push {q0-q7}

    ldr         r4,  =rt_interrupt_from_thread
    ldr         r5,  [r4]
    str         sp,  [r5]                       // save sp of old thread to rt_interrupt_from_thread

    ldr         r6,  =rt_interrupt_to_thread
    ldr         r6,  [r6]
    ldr         sp,  [r6]                       // load sp of new thread from rt_interrupt_to_thread

    IMPORT      _restore_thread
    b           _restore_thread

    END
