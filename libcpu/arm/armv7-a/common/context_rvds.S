/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

    AREA	CONTEXT, CODE, READONLY, ALIGN=5
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

// disable irq
// @return the value of cpsr
// rt_base_t rt_hw_interrupt_disable(void);
    EXPORT      rt_hw_interrupt_disable
rt_hw_interrupt_disable
    mrs         r0, cpsr
    cpsid       if
    bx          lr

// enable irq
// @param cpsrVal cpsr value when interrupt is disabled
// void rt_hw_interrupt_enable(rt_base_t cpsrVal);
    EXPORT      rt_hw_interrupt_enable
rt_hw_interrupt_enable
    msr         cpsr_c, r0
    bx          lr

    EXPORT      rt_hw_get_vfp_neon_qreg_nums
rt_hw_get_vfp_neon_qreg_nums
#if defined(RT_USING_VFP_NEON_Q16)
    mov         r0, #16
#else
    mov         r0, #8
#endif
    bx          lr

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

// Switch from current thread to new thread
// @param from Used to save the stack address of the current thread
// @param to Store the stack address of the new thread
// void rt_hw_context_switch(uint32_t* pFrom, uint32_t* pTo);
    EXPORT      rt_hw_context_switch
rt_hw_context_switch
    stmfd       sp!, {lr}                       // 1) push {pc}
    stmfd       sp!, {r0-r12, lr}               // 2) push {r0-r12,lr}
    mrs         r4, cpsr
    tst         lr, #0x01
    orrne       r4, r4, #T_Bit
    stmfd       sp!, {r4}                       // 3) push {cpsr}

    vmrs        r3, fpscr
    mov         r2, #0
    stmfd       sp!, {r2-r3}                    // 4) push {0,fpscr}
#if defined(RT_USING_VFP_NEON_Q16)
    vpush       {q8-q15}                        // 5) push {q8-q15}
#endif
    vpush       {q0-q7}                         // 6) push {q0-q7}

    str         sp, [r0]                        // *pFrom = sp, save the stack address of the current thread
    ldr         sp, [r1]                        // sp = *pTo, load the stack address of the new thread 

    EXPORT  _restore_thread
_restore_thread
    vpop        {q0-q7}                         // 1) pop {q0-q7}
#if defined(RT_USING_VFP_NEON_Q16)
    vpop        {q8-q15}                        // 2) pop {q8-q15}
#endif
    ldmfd       sp!, {r2-r3}                    // 3) pop {0,fpscr}
    vmsr        fpscr, r3                       //    Restore fpscr

    ldmfd       sp!, {r0}                       // 4) pop {cpsr}
    msr         spsr_cxsf, r0                   //    Restore cpsr to spsr
    ldmfd       sp!, {r0-r12, lr, pc}^          // 5) pop {r0-r12,lr,pc}, and switch to new thread

// switch to new thread
// @param to the stack address of new thread
// void rt_hw_context_switch_to(rt_uint32 to);
    EXPORT      rt_hw_context_switch_to
rt_hw_context_switch_to
    ldr         sp, [r0]
    b           _restore_thread

// Switch from current thread to new thread, when exit from irq
// @param from Used to save the stack address of the current thread
// @param to Store the stack address of the new thread
// void rt_hw_context_switch_interrupt(uint32_t* pFrom, uint32_t* pTo);
// void rt_hw_context_switch_interrupt(rt_uint32 from, rt_uint32 to);
    IMPORT      rt_thread_switch_interrupt_flag
    IMPORT      rt_interrupt_from_thread
    IMPORT      rt_interrupt_to_thread
    EXPORT      rt_hw_context_switch_interrupt
rt_hw_context_switch_interrupt
    ldr         r2, =rt_thread_switch_interrupt_flag
    ldr         r3, [r2]
    cmp         r3, #1
    beq         _reswitch
    mov         r3, #1							// set rt_thread_switch_interrupt_flag = 1
    str         r3, [r2]
    ldr         r2, =rt_interrupt_from_thread
    str         r0, [r2]                        // set rt_interrupt_from_thread
_reswitch
    ldr         r2, =rt_interrupt_to_thread		// set rt_interrupt_to_thread
    str         r1, [r2]
    bx          lr

    END
