/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 * Copyright (c) 2021, Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2020/08/20     zx.chen      The T-HEAD RISC-V CPU E906 porting implementation
 * 2021/08/13     zx.chen      update T-HEAD E9xx-series(E906/7/F/D/P) CPU porting code.
 */

#include "cpuport.h"

#ifdef RT_USING_SMP
#define rt_hw_interrupt_disable rt_hw_local_irq_disable
#define rt_hw_interrupt_enable  rt_hw_local_irq_enable
#endif

/*
 * Functions: vPortYield
 */
.global vPortYield
.type   vPortYield, %function
vPortYield:
    li      t0, 0xE080100C
    lb      t1, (t0)
    li      t2, 0x01
    or      t1, t1, t2
    sb      t1, (t0)

    ret

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
    /* save a0 to to_thread */
    la      t0, rt_interrupt_to_thread
    STORE   a0, (t0)

    /* save 0 to from_thread */
    la      t0, rt_interrupt_from_thread
    li      t1, 0
    STORE   t1, (t0)

    /* set rt_thread_switch_interrupt_flag=1 */
    la      t0, rt_thread_switch_interrupt_flag
    li      t1, 1
    STORE   t1, (t0)

    /* enable mexstatus SPUSHEN */
#ifdef CONFIG_THEAD_EXT_SPUSHEN
    li      t0, 0x10000
    csrs    mexstatus, t0
#endif

    csrw    mscratch, sp
    /* set software interrupt */
    li      t0, 0xE080100C
    lb      t1, (t0)
    li      t2, 0x01
    or      t1, t1, t2
    sb      t1, (t0)

    /* enable global interrup */
    csrsi   mstatus, 8

    ret

/*
 * #ifdef RT_USING_SMP
 * void rt_hw_context_switch(rt_ubase_t from, rt_ubase_t to, struct rt_thread *to_thread);
 * #else
 * void rt_hw_context_switch(rt_ubase_t from, rt_ubase_t to);
 * #endif
 *
 * a0 --> from
 * a1 --> to
 * a2 --> to_thread
 */
    .globl rt_hw_context_switch
rt_hw_context_switch:
    .globl rt_hw_context_switch_interrupt
rt_hw_context_switch_interrupt:
    /* check rt_thread_switch_interrupt_flag */
    la      t0, rt_thread_switch_interrupt_flag
    lw      t1, (t0)
    li      t2, 1
    beq     t1, t2, .reswitch
    /*  set rt_thread_switch_interrupt_flag=1 */
    STORE   t2, (t0)

    /* update from_thread */
    la      t0, rt_interrupt_from_thread
    STORE   a0, (t0)

.reswitch:
    /* update to_thread */
    la      t0, rt_interrupt_to_thread
    STORE   a1, (t0)
    /* set software interrupt */
    li      t0, 0xE080100C
    lb      t1, (t0)
    li      t2, 0x01
    or      t1, t1, t2
    sb      t1, (t0)

    ret

/*
 *    PendSV_Handler
 */
.global PendSV_Handler
.type   PendSV_Handler, %function
PendSV_Handler:

    /* check rt_thread_switch_interrupt_flag */
    sw      t0, (-4)(sp)
    sw      t1, (-8)(sp)
    la      t0, rt_thread_switch_interrupt_flag
    lw      t1, (t0)
    beqz    t1, .pendsv_exit

    /* clear rt_thread_switch_interrupt_flag */
    li      t1, 0x0
    sw      t1, (t0)

    /* check rt_interrupt_from_thread */
    la      t0, rt_interrupt_from_thread
    lw      t1, (t0)
    beqz    t1, .switch_to_thead

    /* restore from thread context t0,t1 */
    lw      t0, (-4)(sp)
    lw      t1, (-8)(sp)

#ifdef ARCH_RISCV_FPU
    addi    sp, sp, -32 * FREGBYTES

    FSTORE  f0, 0 * FREGBYTES(sp)
    FSTORE  f1, 1 * FREGBYTES(sp)
    FSTORE  f2, 2 * FREGBYTES(sp)
    FSTORE  f3, 3 * FREGBYTES(sp)
    FSTORE  f4, 4 * FREGBYTES(sp)
    FSTORE  f5, 5 * FREGBYTES(sp)
    FSTORE  f6, 6 * FREGBYTES(sp)
    FSTORE  f7, 7 * FREGBYTES(sp)
    FSTORE  f8, 8 * FREGBYTES(sp)
    FSTORE  f9, 9 * FREGBYTES(sp)
    FSTORE  f10, 10 * FREGBYTES(sp)
    FSTORE  f11, 11 * FREGBYTES(sp)
    FSTORE  f12, 12 * FREGBYTES(sp)
    FSTORE  f13, 13 * FREGBYTES(sp)
    FSTORE  f14, 14 * FREGBYTES(sp)
    FSTORE  f15, 15 * FREGBYTES(sp)
    FSTORE  f16, 16 * FREGBYTES(sp)
    FSTORE  f17, 17 * FREGBYTES(sp)
    FSTORE  f18, 18 * FREGBYTES(sp)
    FSTORE  f19, 19 * FREGBYTES(sp)
    FSTORE  f20, 20 * FREGBYTES(sp)
    FSTORE  f21, 21 * FREGBYTES(sp)
    FSTORE  f22, 22 * FREGBYTES(sp)
    FSTORE  f23, 23 * FREGBYTES(sp)
    FSTORE  f24, 24 * FREGBYTES(sp)
    FSTORE  f25, 25 * FREGBYTES(sp)
    FSTORE  f26, 26 * FREGBYTES(sp)
    FSTORE  f27, 27 * FREGBYTES(sp)
    FSTORE  f28, 28 * FREGBYTES(sp)
    FSTORE  f29, 29 * FREGBYTES(sp)
    FSTORE  f30, 30 * FREGBYTES(sp)
    FSTORE  f31, 31 * FREGBYTES(sp)
#endif

#ifdef ARCH_RISCV_DSP
    addi    sp, sp, -33 * REGBYTES
#else
    addi    sp, sp, -32 * REGBYTES
#endif

    STORE   x1, 1 * REGBYTES(sp)
    csrr    x1, mepc
    STORE   x1, 0 * REGBYTES(sp)
    csrr    x1, mstatus
    STORE   x1, 2 * REGBYTES(sp)
    /* x3 don't need save */
    STORE   x4, 4 * REGBYTES(sp)
    STORE   x5, 5 * REGBYTES(sp)
    STORE   x6, 6 * REGBYTES(sp)
    STORE   x7, 7 * REGBYTES(sp)
    STORE   x8, 8 * REGBYTES(sp)
    STORE   x9, 9 * REGBYTES(sp)
    STORE   x10, 10 * REGBYTES(sp)
    STORE   x11, 11 * REGBYTES(sp)
    STORE   x12, 12 * REGBYTES(sp)
    STORE   x13, 13 * REGBYTES(sp)
    STORE   x14, 14 * REGBYTES(sp)
    STORE   x15, 15 * REGBYTES(sp)
    STORE   x16, 16 * REGBYTES(sp)
    STORE   x17, 17 * REGBYTES(sp)
    STORE   x18, 18 * REGBYTES(sp)
    STORE   x19, 19 * REGBYTES(sp)
    STORE   x20, 20 * REGBYTES(sp)
    STORE   x21, 21 * REGBYTES(sp)
    STORE   x22, 22 * REGBYTES(sp)
    STORE   x23, 23 * REGBYTES(sp)
    STORE   x24, 24 * REGBYTES(sp)
    STORE   x25, 25 * REGBYTES(sp)
    STORE   x26, 26 * REGBYTES(sp)
    STORE   x27, 27 * REGBYTES(sp)
    STORE   x28, 28 * REGBYTES(sp)
    STORE   x29, 29 * REGBYTES(sp)
    STORE   x30, 30 * REGBYTES(sp)
    STORE   x31, 31 * REGBYTES(sp)
#ifdef ARCH_RISCV_DSP
    csrr    t0, vxsat
    STORE   t0, 32 * REGBYTES(sp)
#endif

    /* store from_thread sp */
    la      t0, rt_interrupt_from_thread
    lw      t0, (t0)
    sw      sp, (t0)

.switch_to_thead:
    /* restore to thread context
     * sp(0) -> epc;
     * sp(1) -> ra;
     * sp(i) -> x(i+2)
     */
    la      t0, rt_interrupt_to_thread
    lw      t0, (t0)
    LOAD    sp, (t0)


#ifdef ARCH_RISCV_DSP
    LOAD    a1, 32 * REGBYTES(sp)
    csrw    vxsat, a1
#endif

    /* restore ra to mepc */
    LOAD    a1, 0 * REGBYTES(sp)
    csrw    mepc, a1
    LOAD    x1, 1 * REGBYTES(sp)

    /* force to machine mode(MPP=11) */
    LOAD    a1, 2 * REGBYTES(sp)
    csrw    mstatus, a1
    /* x3 don't need restore */
    LOAD    x4, 4 * REGBYTES(sp)
    LOAD    x5, 5 * REGBYTES(sp)
    LOAD    x6, 6 * REGBYTES(sp)
    LOAD    x7, 7 * REGBYTES(sp)
    LOAD    x8, 8 * REGBYTES(sp)
    LOAD    x9, 9 * REGBYTES(sp)
    LOAD    x10, 10 * REGBYTES(sp)
    LOAD    x11, 11 * REGBYTES(sp)
    LOAD    x12, 12 * REGBYTES(sp)
    LOAD    x13, 13 * REGBYTES(sp)
    LOAD    x14, 14 * REGBYTES(sp)
    LOAD    x15, 15 * REGBYTES(sp)
    LOAD    x16, 16 * REGBYTES(sp)
    LOAD    x17, 17 * REGBYTES(sp)
    LOAD    x18, 18 * REGBYTES(sp)
    LOAD    x19, 19 * REGBYTES(sp)
    LOAD    x20, 20 * REGBYTES(sp)
    LOAD    x21, 21 * REGBYTES(sp)
    LOAD    x22, 22 * REGBYTES(sp)
    LOAD    x23, 23 * REGBYTES(sp)
    LOAD    x24, 24 * REGBYTES(sp)
    LOAD    x25, 25 * REGBYTES(sp)
    LOAD    x26, 26 * REGBYTES(sp)
    LOAD    x27, 27 * REGBYTES(sp)
    LOAD    x28, 28 * REGBYTES(sp)
    LOAD    x29, 29 * REGBYTES(sp)
    LOAD    x30, 30 * REGBYTES(sp)
    LOAD    x31, 31 * REGBYTES(sp)

#ifdef ARCH_RISCV_DSP
    addi    sp, sp, 33 * REGBYTES
#else
    addi    sp, sp, 32 * REGBYTES
#endif

#ifdef ARCH_RISCV_FPU
    FLOAD   f0, 0 * FREGBYTES(sp)
    FLOAD   f1, 1 * FREGBYTES(sp)
    FLOAD   f2, 2 * FREGBYTES(sp)
    FLOAD   f3, 3 * FREGBYTES(sp)
    FLOAD   f4, 4 * FREGBYTES(sp)
    FLOAD   f5, 5 * FREGBYTES(sp)
    FLOAD   f6, 6 * FREGBYTES(sp)
    FLOAD   f7, 7 * FREGBYTES(sp)
    FLOAD   f8, 8 * FREGBYTES(sp)
    FLOAD   f9, 9 * FREGBYTES(sp)
    FLOAD   f10, 10 * FREGBYTES(sp)
    FLOAD   f11, 11 * FREGBYTES(sp)
    FLOAD   f12, 12 * FREGBYTES(sp)
    FLOAD   f13, 13 * FREGBYTES(sp)
    FLOAD   f14, 14 * FREGBYTES(sp)
    FLOAD   f15, 15 * FREGBYTES(sp)
    FLOAD   f16, 16 * FREGBYTES(sp)
    FLOAD   f17, 17 * FREGBYTES(sp)
    FLOAD   f18, 18 * FREGBYTES(sp)
    FLOAD   f19, 19 * FREGBYTES(sp)
    FLOAD   f20, 20 * FREGBYTES(sp)
    FLOAD   f21, 21 * FREGBYTES(sp)
    FLOAD   f22, 22 * FREGBYTES(sp)
    FLOAD   f23, 23 * FREGBYTES(sp)
    FLOAD   f24, 24 * FREGBYTES(sp)
    FLOAD   f25, 25 * FREGBYTES(sp)
    FLOAD   f26, 26 * FREGBYTES(sp)
    FLOAD   f27, 27 * FREGBYTES(sp)
    FLOAD   f28, 28 * FREGBYTES(sp)
    FLOAD   f29, 29 * FREGBYTES(sp)
    FLOAD   f30, 30 * FREGBYTES(sp)
    FLOAD   f31, 31 * FREGBYTES(sp)

    addi    sp, sp, 32 * FREGBYTES
#endif

.pendsv_exit:
    mret

/*
 * rt_base_t rt_hw_interrupt_disable(void);
 */
    .globl rt_hw_interrupt_disable
    .type   rt_hw_interrupt_disable, %function
rt_hw_interrupt_disable:
    csrrci a0, mstatus, 8
    ret


/*
 * void rt_hw_interrupt_enable(rt_base_t level);
 */
    .globl rt_hw_interrupt_enable
    .type   rt_hw_interrupt_enable, %function
rt_hw_interrupt_enable:
    csrw mstatus, a0
    ret

