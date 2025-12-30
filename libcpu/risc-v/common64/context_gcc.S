/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2018/10/28     Bernard      The unify RISC-V porting implementation
 * 2018/12/27     Jesven       Add SMP support
 * 2021/02/02     lizhirui     Add userspace support
 * 2022/10/22     Shell        Support User mode RVV;
 *                             Trimming process switch context
 */

#include "cpuport.h"
#include "stackframe.h"
#define _REG_IDX(name) RT_HW_SWITCH_CONTEXT_##name
#define REG_IDX(name) _REG_IDX(name)

.macro SAVE_REG reg, index
    STORE \reg, \index*REGBYTES(sp)
.endm

.macro LOAD_REG reg, index
    LOAD \reg, \index*REGBYTES(sp)
.endm

.macro RESERVE_CONTEXT
    addi        sp, sp, -(RT_HW_SWITCH_CONTEXT_SIZE * REGBYTES)
    SAVE_REG    tp, REG_IDX(TP)
    SAVE_REG    ra, REG_IDX(RA)
    SAVE_REG    s0, REG_IDX(S0)
    SAVE_REG    s1, REG_IDX(S1)
    SAVE_REG    s2, REG_IDX(S2)
    SAVE_REG    s3, REG_IDX(S3)
    SAVE_REG    s4, REG_IDX(S4)
    SAVE_REG    s5, REG_IDX(S5)
    SAVE_REG    s6, REG_IDX(S6)
    SAVE_REG    s7, REG_IDX(S7)
    SAVE_REG    s8, REG_IDX(S8)
    SAVE_REG    s9, REG_IDX(S9)
    SAVE_REG    s10, REG_IDX(S10)
    SAVE_REG    s11, REG_IDX(S11)
    csrr        s11, sstatus
    li          s10, (SSTATUS_SPP)
    or          s11, s11, s10
    SAVE_REG    s11, REG_IDX(SSTATUS)
.endm

.macro RESTORE_CONTEXT
    LOAD_REG    s11, REG_IDX(SSTATUS)
    csrw        sstatus, s11
    LOAD_REG    s11, REG_IDX(S11)
    LOAD_REG    s10, REG_IDX(S10)
    LOAD_REG    s9, REG_IDX(S9)
    LOAD_REG    s8, REG_IDX(S8)
    LOAD_REG    s7, REG_IDX(S7)
    LOAD_REG    s6, REG_IDX(S6)
    LOAD_REG    s5, REG_IDX(S5)
    LOAD_REG    s4, REG_IDX(S4)
    LOAD_REG    s3, REG_IDX(S3)
    LOAD_REG    s2, REG_IDX(S2)
    LOAD_REG    s1, REG_IDX(S1)
    LOAD_REG    s0, REG_IDX(S0)
    LOAD_REG    ra, REG_IDX(RA)
    LOAD_REG    tp, REG_IDX(TP)
    addi        sp, sp, RT_HW_SWITCH_CONTEXT_SIZE * REGBYTES
    csrw        sepc, ra
.endm

/*
 * #ifdef RT_USING_SMP
 * void rt_hw_context_switch_to(rt_ubase_t to, stuct rt_thread *to_thread);
 * #else
 * void rt_hw_context_switch_to(rt_ubase_t to);
 * #endif
 * a0 --> to
 * a1 --> to_thread
 */
.globl rt_hw_context_switch_to
rt_hw_context_switch_to:
    LOAD sp, (a0)

#ifdef RT_USING_SMP
    /* Pass the previous CPU lock status to rt_cpus_lock_status_restore for restoration */
    mv   a0,   a1
    call  rt_cpus_lock_status_restore
#endif

    call rt_thread_self
    mv s1, a0

#ifndef RT_USING_SMP
    //if enable RT_USING_SMP, it will finished by rt_cpus_lock_status_restore.
    #ifdef RT_USING_SMART
      call lwp_aspace_switch
    #endif
#endif

    RESTORE_CONTEXT
    sret

/*
 * #ifdef RT_USING_SMP
 * void rt_hw_context_switch(rt_ubase_t from, rt_ubase_t to, struct rt_thread *to_thread);
 * #else
 * void rt_hw_context_switch(rt_ubase_t from, rt_ubase_t to);
 * #endif
 *
 * a0 --> from SP pointer
 * a1 --> to SP pointer
 * a2 --> to_thread
 *
 * It should only be used on local interrupt disable
 */
.globl rt_hw_context_switch
rt_hw_context_switch:
    RESERVE_CONTEXT
    STORE sp, (a0)

    // restore to thread SP
    LOAD sp, (a1)

#ifdef RT_USING_SMP
    /* Pass the previous CPU lock status to rt_cpus_lock_status_restore for restoration */
    mv   a0,   a2
    call  rt_cpus_lock_status_restore
#endif /*RT_USING_SMP*/

    // restore Address Space
    call rt_thread_self
    mv s1, a0

#ifndef RT_USING_SMP
    // if enable RT_USING_SMP, it will finished by rt_cpus_lock_status_restore.
    #ifdef RT_USING_SMART
       call lwp_aspace_switch
    #endif
#endif

    RESTORE_CONTEXT
    sret
