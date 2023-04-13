/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/10/28     Bernard      The unify RISC-V porting implementation
 * 2018/12/27     Jesven       Add SMP support
 * 2021/02/02     lizhirui     Add userspace support
 * 2022/10/22     WangXiaoyao  Support User mode RVV;
 *                             Trimming process switch context
 */

#include "cpuport.h"
#include "stackframe.h"

.macro PUSH_8 reg
    addi    sp, sp, -8
    STORE   \reg, (sp)
.endm

.macro POP_8 reg
    LOAD    \reg, (sp)
    addi    sp, sp, 8
.endm

.macro RESERVE_CONTEXT
    PUSH_8  tp
    PUSH_8  ra
    PUSH_8  s0
    PUSH_8  s1
    PUSH_8  s2
    PUSH_8  s3
    PUSH_8  s4
    PUSH_8  s5
    PUSH_8  s6
    PUSH_8  s7
    PUSH_8  s8
    PUSH_8  s9
    PUSH_8  s10
    PUSH_8  s11
    csrr    s11, sstatus
    li      s10, (SSTATUS_SPP)
    or      s11, s11, s10
    PUSH_8  s11
.endm

.macro RESTORE_CONTEXT
    POP_8   s11
    csrw    sstatus, s11
    POP_8   s11
    POP_8   s10
    POP_8   s9
    POP_8   s8
    POP_8   s7
    POP_8   s6
    POP_8   s5
    POP_8   s4
    POP_8   s3
    POP_8   s2
    POP_8   s1
    POP_8   s0
    POP_8   ra
    POP_8   tp
    csrw    sepc, ra
.endm

/*
 * void rt_hw_context_switch_to(rt_ubase_t to);
 *
 * a0 --> to SP pointer
 */
.globl rt_hw_context_switch_to
rt_hw_context_switch_to:
    LOAD sp, (a0)

    la s0, rt_current_thread
    LOAD s1, (s0)

    #ifdef RT_USING_SMART
        mv a0, s1
        jal lwp_aspace_switch
    #endif

    RESTORE_CONTEXT
    sret

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
    RESERVE_CONTEXT
    STORE sp, (a0)

    // restore to thread SP
    LOAD sp, (a1)

    // restore Address Space
    la s0, rt_current_thread
    LOAD s1, (s0)

    #ifdef RT_USING_SMART
        mv a0, s1
        jal lwp_aspace_switch
    #endif

    RESTORE_CONTEXT
    sret

#ifdef ENABLE_VECTOR
/**
 * @param a0 pointer to frame bottom
 */
.global rt_hw_vector_ctx_save
rt_hw_vector_ctx_save:
    SAVE_VECTOR a0
    ret

/**
 * @param a0 pointer to frame bottom
 */
.global rt_hw_vector_ctx_restore
rt_hw_vector_ctx_restore:
    RESTORE_VECTOR a0
    ret

.global rt_hw_disable_vector
rt_hw_disable_vector:
    li t0, SSTATUS_VS
    csrc sstatus, t0
    ret

.global rt_hw_enable_vector
rt_hw_enable_vector:
    li t0, SSTATUS_VS
    csrs sstatus, t0
    ret
#endif /* ENABLE_VECTOR */
