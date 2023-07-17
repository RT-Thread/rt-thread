/*
 * Copyright (c) 2018, Synopsys, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#define __ASSEMBLY__
#include "include/arc/arc.h"
#include "include/arc/arc_asm_common.h"

.global rt_interrupt_enter;
.global rt_interrupt_leave;
.global rt_thread_switch_interrupt_flag;
.global rt_interrupt_from_thread;
.global rt_interrupt_to_thread;
.global exc_nest_count;
.global set_hw_stack_check;

    .text
    .align 4
dispatcher:
    st sp, [r0]
    ld sp, [r1]
#if ARC_FEATURE_STACK_CHECK
#if ARC_FEATURE_SEC_PRESENT
    lr r0, [AUX_SEC_STAT]
    bclr r0, r0, AUX_SEC_STAT_BIT_SSC
    sflag r0
#else
    lr r0, [AUX_STATUS32]
    bclr r0, r0, AUX_STATUS_BIT_SC
    kflag r0
#endif
    jl  set_hw_stack_check
#if ARC_FEATURE_SEC_PRESENT
    lr r0, [AUX_SEC_STAT]
    bset r0, r0, AUX_SEC_STAT_BIT_SSC
    sflag r0
#else
    lr r0, [AUX_STATUS32]
    bset r0, r0, AUX_STATUS_BIT_SC
    kflag r0
#endif
#endif
    pop r0
    j [r0]

/* return routine when task dispatch happened in task context */
dispatch_r:
    RESTORE_NONSCRATCH_REGS
    RESTORE_R0_TO_R12
    j   [blink]

/*
 * rt_base_t rt_hw_interrupt_disable();
 */
    .global rt_hw_interrupt_disable
    .align 4
rt_hw_interrupt_disable:
    clri r0
    j [blink]


/*
 * void rt_hw_interrupt_enable(rt_base_t level);
 */
    .global rt_hw_interrupt_enable
    .align 4
rt_hw_interrupt_enable:
    seti r0
    j [blink]


    .global rt_hw_context_switch_interrupt
    .align 4
rt_hw_context_switch_interrupt:
    ld r2, [rt_thread_switch_interrupt_flag]
    breq r2, 1, _reswitch    /* Check the flag, if it is 1, skip to reswitch */
    mov r2, 1
    st r2, [rt_thread_switch_interrupt_flag]
    st r0, [rt_interrupt_from_thread]
_reswitch:
    st r1, [rt_interrupt_to_thread]
    j [blink]


/*
 * void rt_hw_context_switch(rt_uint32 from, rt_uint32 to);
 * r0 --> from
 * r1 --> to
 */
    .global rt_hw_context_switch
    .align 4
rt_hw_context_switch:
    SAVE_R0_TO_R12
    SAVE_NONSCRATCH_REGS
    mov r2, dispatch_r
    push r2
    b dispatcher


/*
 * void rt_hw_context_switch_to(rt_uint32 to);
 * r0 --> to
 */
    .global rt_hw_context_switch_to
    .align 4
rt_hw_context_switch_to:
    ld sp, [r0]
#if ARC_FEATURE_STACK_CHECK
    mov r1, r0
#if ARC_FEATURE_SEC_PRESENT
    lr r0, [AUX_SEC_STAT]
    bclr r0, r0, AUX_SEC_STAT_BIT_SSC
    sflag r0
#else
    lr r0, [AUX_STATUS32]
    bclr r0, r0, AUX_STATUS_BIT_SC
    kflag r0
#endif
    jl  set_hw_stack_check
#if ARC_FEATURE_SEC_PRESENT
    lr r0, [AUX_SEC_STAT]
    bset r0, r0, AUX_SEC_STAT_BIT_SSC
    sflag r0
#else
    lr r0, [AUX_STATUS32]
    bset r0, r0, AUX_STATUS_BIT_SC
    kflag r0
#endif
#endif
    pop r0
    j [r0]

    .global start_r
    .align 4
start_r:
    pop blink;
    pop r1
    pop r2
    pop r0

    j_s.d [r1]
    kflag r2

/*
 * int __rt_ffs(int value);
 * r0 --> value
 */
    .global __rt_ffs
    .align 4
__rt_ffs:
    breq r0, 0, __rt_ffs_return
    ffs r1, r0
    add r0, r1, 1
__rt_ffs_return:
    j [blink]

/****** exceptions and interrupts handing ******/
/****** entry for exception handling ******/
    .global exc_entry_cpu
    .align 4
exc_entry_cpu:

    EXCEPTION_PROLOGUE

    mov blink,  sp
    mov r3, sp      /* as exception handler's para(p_excinfo) */

    ld  r0, [exc_nest_count]
    add r1, r0, 1
    st  r1, [exc_nest_count]
    brne    r0, 0, exc_handler_1
/* change to exception stack if interrupt happened in task context */
    mov sp, _e_stack
exc_handler_1:
    PUSH    blink

    lr  r0, [AUX_ECR]
    lsr r0, r0, 16
    mov r1, exc_int_handler_table
    ld.as   r2, [r1, r0]

    mov r0, r3
    jl  [r2]

/* interrupts are not allowed */
ret_exc:
    POP sp
    mov r1, exc_nest_count
    ld  r0, [r1]
    sub r0, r0, 1
    st  r0, [r1]
    brne    r0, 0, ret_exc_1 /* nest exception case */
    lr  r1, [AUX_IRQ_ACT] /* nest interrupt case */
    brne    r1, 0, ret_exc_1

    ld  r0, [rt_thread_switch_interrupt_flag]
    brne    r0, 0, ret_exc_2
ret_exc_1:  /* return from non-task context, interrupts or exceptions are nested */
    EXCEPTION_EPILOGUE
    rtie

/* there is a dispatch request */
ret_exc_2:
    /* clear dispatch request */
    mov r0, 0
    st  r0, [rt_thread_switch_interrupt_flag]

    SAVE_CALLEE_REGS    /* save callee save registers */

    /* clear exception bit to do exception exit by SW */
    lr  r0, [AUX_STATUS32]
    bclr    r0, r0, AUX_STATUS_BIT_AE
    kflag   r0

    mov r1, ret_exc_r   /* save return address */
    PUSH    r1

    ld  r0, [rt_interrupt_from_thread]
    ld  r1, [rt_interrupt_to_thread]
    b   dispatcher

ret_exc_r:
    /* recover exception status */
    lr  r0, [AUX_STATUS32]
    bset    r0, r0, AUX_STATUS_BIT_AE
    kflag   r0

    RESTORE_CALLEE_REGS
    EXCEPTION_EPILOGUE
    rtie

/****** entry for normal interrupt exception handling ******/
    .global exc_entry_int   /* entry for interrupt handling */
    .align 4
exc_entry_int:
#if ARC_FEATURE_FIRQ == 1
/*  check whether it is P0 interrupt */
#if ARC_FEATURE_RGF_NUM_BANKS > 1
    lr  r0, [AUX_IRQ_ACT]
    btst    r0, 0
    jnz exc_entry_firq
#else
    PUSH    r10
    lr  r10, [AUX_IRQ_ACT]
    btst    r10, 0
    POP r10
    jnz exc_entry_firq
#endif
#endif
    INTERRUPT_PROLOGUE

    mov blink, sp

    clri    /* disable interrupt */
    ld  r3, [exc_nest_count]
    add r2, r3, 1
    st  r2, [exc_nest_count]
    seti    /* enable higher priority interrupt */

    brne    r3, 0, irq_handler_1
/* change to exception stack if interrupt happened in task context */
    mov sp, _e_stack
#if ARC_FEATURE_STACK_CHECK
#if ARC_FEATURE_SEC_PRESENT
    lr r0, [AUX_SEC_STAT]
    bclr r0, r0, AUX_SEC_STAT_BIT_SSC
    sflag r0
#else
    lr r0, [AUX_STATUS32]
    bclr r0, r0, AUX_STATUS_BIT_SC
    kflag r0
#endif
#endif
irq_handler_1:
    PUSH    blink

    jl  rt_interrupt_enter

    lr  r0, [AUX_IRQ_CAUSE]
    sr  r0, [AUX_IRQ_SELECT]
    mov r1, exc_int_handler_table
    ld.as   r2, [r1, r0]    /* r2 = exc_int_handler_table + irqno *4 */
/* handle software triggered interrupt */
    lr  r3, [AUX_IRQ_HINT]
    cmp r3, r0
    bne.d irq_hint_handled
    xor r3, r3, r3
    sr  r3, [AUX_IRQ_HINT]
irq_hint_handled:
    lr  r3, [AUX_IRQ_PRIORITY]
    PUSH    r3      /* save irq priority */

    jl  [r2]        /* jump to interrupt handler */
    jl  rt_interrupt_leave
ret_int:
    clri            /* disable interrupt */
    POP r3      /* irq priority */
    POP sp
    mov r1, exc_nest_count
    ld  r0, [r1]
    sub r0, r0, 1
    st  r0, [r1]
/* if there are multi-bits set in IRQ_ACT, it's still in nest interrupt */
    lr  r0, [AUX_IRQ_CAUSE]
    sr  r0, [AUX_IRQ_SELECT]
    lr  r3, [AUX_IRQ_PRIORITY]
    lr  r1, [AUX_IRQ_ACT]
    bclr    r2, r1, r3
    brne    r2, 0, ret_int_1

    ld  r0, [rt_thread_switch_interrupt_flag]
    brne    r0, 0, ret_int_2
ret_int_1:  /* return from non-task context */
    INTERRUPT_EPILOGUE
    rtie
/* there is a dispatch request */
ret_int_2:
    /* clear dispatch request */
    mov r0, 0
    st  r0, [rt_thread_switch_interrupt_flag]

    /* interrupt return by SW */
    lr  r10, [AUX_IRQ_ACT]
    PUSH    r10
    bclr    r10, r10, r3    /* clear related bits in IRQ_ACT */
    sr  r10, [AUX_IRQ_ACT]

    SAVE_CALLEE_REGS    /* save callee save registers */
    mov r1, ret_int_r   /* save return address */
    PUSH    r1

    ld  r0, [rt_interrupt_from_thread]
    ld  r1, [rt_interrupt_to_thread]
    b   dispatcher

ret_int_r:
    RESTORE_CALLEE_REGS
    /* recover AUX_IRQ_ACT to restore the interrup status */
    POPAX   AUX_IRQ_ACT
    INTERRUPT_EPILOGUE
    rtie

/****** entry for fast irq exception handling ******/
    .global exc_entry_firq
    .weak exc_entry_firq
    .align 4
exc_entry_firq:
    SAVE_FIQ_EXC_REGS

    lr  r0, [AUX_IRQ_CAUSE]
    mov r1, exc_int_handler_table
/* r2 = _kernel_exc_tbl + irqno *4 */
    ld.as   r2, [r1, r0]

/* for the case of software triggered interrupt */
    lr  r3, [AUX_IRQ_HINT]
    cmp r3, r0
    bne.d   firq_hint_handled
    xor r3, r3, r3
    sr  r3, [AUX_IRQ_HINT]
firq_hint_handled:
/* jump to interrupt handler */
    mov r0, sp
    jl  [r2]

firq_return:
    RESTORE_FIQ_EXC_REGS
    rtie
