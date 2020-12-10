/*
 * Copyright (c) 2020-2020, BLUETRUM Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "ab32vg1.h"

.global _start
.section .reset, "ax"
_start:
    //load comm
    la      a0, __comm_vma
    la      a1, __comm_lma
    la      a2, __comm_size

    /* memcpy start */
    //先按32 BYTE一个循环来copy
    mv      t0, a0              //备份dst
    srli    t1, a2, 5           //长度除32的商

    slli    t1, t1, 5
    add     t1, a0, t1          //t1存放对齐的结束地址

    _memcpy_loop1:              //8 WORDS every cycle
    lw      a2, 0(a1)
    lw      a3, 4(a1)
    lw      a4, 8(a1)
    lw      a5, 12(a1)
    sw      a2, 0(a0)
    sw      a3, 4(a0)
    sw      a4, 8(a0)
    sw      a5, 12(a0)

    lw      a2, 16(a1)
    lw      a3, 20(a1)
    lw      a4, 24(a1)
    lw      a5, 28(a1)
    sw      a2, 16(a0)
    sw      a3, 20(a0)
    sw      a4, 24(a0)
    sw      a5, 28(a0)

    addi    a0, a0, 32
    addi    a1, a1, 32
    blt     a0, t1, _memcpy_loop1

    mv      a0, t0              //返回dst
    /* memcpy end */

    la      a0, __irq_stack_start           //Stack清成0x23
    li      a1, 0x23
    la      a2, __irq_stack_size
    call    memset
    la      ra, __irq_stack
    lui	    a5, 0x1
    sw	    zero, -1920(a5)
    sw	    zero, -1916(a5)

    //clear bss
    la      a0, __bss_start
    li      a1, 0
    la      a2, __bss_size
    call    memset

    la      a0, __comm_vma
    sw      a0, PICADR(zero)

    call    entry
//    la      ra, __exception
//    jr      ra

.section .vector, "ax"
//    .org    0x10
//__exception:
//    li      sp, 0x10600                     //出错后，不破坏错误点的堆栈数据
//    jal     exception_isr
//    1: j       1b
//    mret

    .org    0x40
    jal x0, low_prio_irq
    mret

    .global cpu_irq_comm
    .section .com_text.irq
cpu_irq_comm:
    la      a5, __irq_stack
    mv      sp, a5
    j       cpu_irq_comm_do

    ret
