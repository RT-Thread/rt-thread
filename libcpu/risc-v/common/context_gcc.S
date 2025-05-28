/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018-10-28     Bernard      The unify RISC-V porting implementation
 * 2018-12-27     Jesven       Add SMP support
 * 2021-02-02     lizhirui     Add userspace support
 * 2022-10-22     Shell        Support User mode RVV;
 *                             Trimming process switch context
 * 2025-04-20     GuEe-GUI     Support SMP
 */

#include "asm.h"
#include "csr.h"

#define REG_IDX(name)   RT_HW_SWITCH_CONTEXT_##name

.macro SAVE_REG reg, index
    REG_S   \reg, \index * SZREG(sp)
.endm

.macro LOAD_REG reg, index
    REG_L   \reg, \index * SZREG(sp)
.endm

.macro SAVE_CONTEXT
    addi        sp, sp, -(RT_HW_SWITCH_CONTEXT_SIZE * SZREG)
    SAVE_REG    tp, REG_IDX(TP)
    SAVE_REG    ra, REG_IDX(RA)
    SAVE_REG    s0, REG_IDX(S0)
    SAVE_REG    s1, REG_IDX(S1)
    csrr        s1, CSR_STATUS
    li          s0, (SR_PP)
    or          s1, s1, s0
    SAVE_REG    s1, REG_IDX(XSTATUS)
.endm

.macro RESTORE_CONTEXT
    LOAD_REG    s1, REG_IDX(XSTATUS)
    csrw        CSR_STATUS, s1
    LOAD_REG    s1, REG_IDX(S1)
    LOAD_REG    s0, REG_IDX(S0)
    LOAD_REG    ra, REG_IDX(RA)
    LOAD_REG    tp, REG_IDX(TP)
    addi        sp, sp, RT_HW_SWITCH_CONTEXT_SIZE * SZREG
    csrw        CSR_EPC, ra
.endm

    .section ".text","ax"

#ifdef RT_USING_SMP
/*
 * void rt_hw_context_switch_to(rt_ubase_t to, struct rt_thread *to_thread);
 * a0 --> to (thread stack)
 * a1 --> to_thread
 */
.globl rt_hw_context_switch_to
rt_hw_context_switch_to:
    REG_L   sp, (a0)

    /* Reserved to_thread */
    mv      s1, a1

    mv      a0, s1
    call    rt_cpus_lock_status_restore
#ifdef RT_USING_SMART
    mv      a0, s1
    call    lwp_user_setting_restore
#endif

    j       _context_switch_exit

/*
 * void rt_hw_context_switch(rt_ubase_t from, rt_ubase_t to, struct rt_thread *to_thread);
 * a0 --> from (from_thread stack)
 * a1 --> to (to_thread stack)
 * a2 --> to_thread
 */
.globl rt_hw_context_switch
rt_hw_context_switch:
    SAVE_CONTEXT
    mv      a3, sp
    REG_S   a3, (a0)            /* Store sp in preempted tasks TCB */
    REG_L   a0, (a1)            /* Get new task stack pointer */
    mv      sp, a0

    /* Backup thread self */
    mv      s1, a2

    mv      a0, s1
    call    rt_cpus_lock_status_restore
#ifdef RT_USING_SMART
    mv      a0, s1
    call    lwp_user_setting_restore
#endif
    j       _context_switch_exit

#define EXP_FRAME   t0
#define FROM_SPP    t1
#define TO_SPP      t2
#define TO_TCB      a4
#define TMP         a5

/*
 * void rt_hw_context_switch_interrupt(rt_ubase_t context, rt_ubase_t from, rt_ubase_t to, struct rt_thread *to_thread)
 * a0 --> interrupt context
 * a1 --> addr of from_thread's sp
 * a2 --> addr of to_thread's sp
 * a3 --> to_thread's tcb
 */
.globl rt_hw_context_switch_interrupt
rt_hw_context_switch_interrupt:
#ifdef RT_USING_DEBUG
    /* Debug frame for backtrace */
#if __riscv_xlen == 64
    addi    sp, sp, -(48)
    sd      ra, 40(sp)
    sd      s0, 32(sp)
#elif __riscv_xlen == 32
    addi    sp, sp, -(32)
    sw      ra, 28(sp)
    sw      s0, 24(sp)
#else
#error "Unexpected __riscv_xlen"
#endif
#endif /* RT_USING_DEBUG */

    /* We can discard all the previous ABI here */
    mv      EXP_FRAME, a0
    mv      FROM_SPP, a1
    mv      TO_SPP, a2
    mv      TO_TCB, a3

#ifdef RT_USING_SMART
    PUSH    EXP_FRAME
    PUSH    FROM_SPP
    PUSH    TO_SPP
    PUSH    TO_TCB

    call    rt_thread_self
    call    lwp_user_setting_save

    POP     TO_TCB
    POP     TO_SPP
    POP     FROM_SPP
    POP     EXP_FRAME
#endif /* RT_USING_SMART */

    /* Reset SP of from-thread */
    mv      sp, EXP_FRAME

    addi    sp, sp, -(RT_HW_SWITCH_CONTEXT_SIZE * SZREG)
    /* Push context for swtich */
    la      ra, rt_hw_resume_kernel
    /* Save the entire context */
    li      TMP, (K_XSTATUS_DEFAULT & ~SR_PIE)
    REG_S   TMP, REG_IDX(XSTATUS) * SZREG(sp)
    REG_S   ra, REG_IDX(RA) * SZREG(sp)

    /* Save SP of from-thread */
    mv      a0, sp
    REG_S   a0, (FROM_SPP)

    /* Setup SP to to-thread's */
    REG_L   a0, (TO_SPP)
    mv      sp, a0

#ifdef RT_USING_SMART
    PUSH    TO_TCB
#endif
    mv      a0, TO_TCB
    call    rt_cpus_lock_status_restore
#ifdef RT_USING_SMART
    POP     a0  /* TO_TCB */
    call    lwp_user_setting_restore
#endif
    j       _context_switch_exit

#else /* !RT_USING_SMP */
    .section ".data"

    .align RISCV_SZPTR
/**
 * @brief from thread used interrupt context switch
 */
.globl rt_interrupt_from_thread
rt_interrupt_from_thread:
    RISCV_PTR 0

/**
 * @brief to thread used interrupt context switch
 */
.globl rt_interrupt_to_thread
rt_interrupt_to_thread:
    RISCV_PTR 0

/**
 * @brief flag to indicate context switch in interrupt or not
 */
.globl rt_thread_switch_interrupt_flag
rt_thread_switch_interrupt_flag:
    RISCV_PTR 0

/*
 * void rt_hw_context_switch_to(rt_ubase_t to);
 *
 * a0 --> to SP pointer
 */
.globl rt_hw_context_switch_to
rt_hw_context_switch_to:
    REG_L   sp, (a0)

    call    rt_thread_self
    mv      s1, a0

#ifdef RT_USING_SMART
    call    lwp_aspace_switch
#endif

    j       _context_switch_exit

/*
 * void rt_hw_context_switch(rt_ubase_t from, rt_ubase_t to);
 *
 * a0 --> from SP pointer
 * a1 --> to SP pointer
 *
 * It should only be used on local interrupt disable
 */
.globl rt_hw_context_switch
rt_hw_context_switch:
    SAVE_CONTEXT
    REG_S   sp, (a0)

    /* Restore to thread SP */
    REG_L   sp, (a1)

    /* Restore Address Space */
    call    rt_thread_self
    mv      s1, a0

#ifdef RT_USING_SMART
    call    lwp_aspace_switch
#endif

    j       _context_switch_exit

/*
 * void rt_hw_context_switch_interrupt(rt_ubase_t from, rt_ubase_t to, rt_thread_t from_thread, rt_thread_t to_thread)
 * a0 --> from_thread's sp
 * a1 --> to_thread's sp
 * a2 --> from_thread's tcb
 * a3 --> to_thread's tcb
 */
.globl rt_hw_context_switch_interrupt
rt_hw_context_switch_interrupt:
    la      t0, rt_thread_switch_interrupt_flag
    REG_L   t1, (t0)
    bne     t1, zero, _init_to_thread

    la      t1, rt_interrupt_from_thread
    REG_S   a0, (t1)

_init_to_thread:
    la      t1, rt_interrupt_to_thread
    REG_S   a1, (t1)

    li      t1, 1
    REG_S   t1, (t0)

    ret
#endif /* RT_USING_SMP */

.local _context_switch_exit
_context_switch_exit:
    RESTORE_CONTEXT
    XRET
