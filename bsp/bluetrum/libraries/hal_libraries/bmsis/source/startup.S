/*
 * Copyright (c) 2020-2020, BLUETRUM Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "ab32vg1.h"

.global _start
.section .reset, "ax"
_start:
    la      tp, _tp
    la      gp, _gp

    //load comm
    la      a0, __comm_vma
    la      a1, __comm_lma
    la      a2, __comm_size
    call    _memcpy

    //load ram1
    la      a0, __ram1_vma
    la      a1, __ram1_lma
    la      a2, __ram1_size
    call    _memcpy

    la      a0, __irq_stack_start           //Stack清成0x23
    li      a1, 0x23
    la      a2, __irq_stack_size
    call    rt_memset
    la      ra, __irq_stack
    lui	    a5, 0x1
    sw	    zero, -1920(a5)
    sw	    zero, -1916(a5)

    //clear bss
    la      a0, __bss_start
    li      a1, 0
    la      a2, __bss_size
    call    rt_memset

    call    cache_init

    la      a0, __comm_vma
    sw      a0, PICADR(zero)

    call    entry
    la      ra, __exception
    jr      ra

.section .vector, "ax"
    .org    0x10
__exception:
    li      sp, 0x10600                     //出错后，不破坏错误点的堆栈数据
    jal     exception_isr
    1: j       1b
    mret

    .org    0x40
    jal x0, low_prio_irq

    .org    0x80
#define METHOD 1
#if METHOD == 1
    addi    sp, sp, -6*4
    # lw      a0, PICEN(zero)
    lw      a1, EPC(zero)
    lw      a2, EPICCON(zero)
    # sw      a0, 3*4(sp)
    sw      a1, 4*4(sp)
    sw      a2, 5*4(sp)
    # andi    a0, a0, 1
    # sw      a0, PICEN(zero)
    li      a2, 0
    sw      a2, EPICCON(zero)
    la      a0, 0f
    sw      a0, EPC(zero)
    j       isr_cache
0:
    sw      a0, 0(sp)
    sw      a1, 4(sp)
    sw      a2, 8(sp)

    # lw      a0, 3*4(sp)
    lw      a1, 4*4(sp)
    lw      a2, 5*4(sp)
    # sw      a0, PICEN(zero)
    sw      a1, EPC(zero)
    sw      a2, EPICCON(zero)

    lw      a0, 0(sp)
    lw      a1, 4(sp)
    lw      a2, 8(sp)
    addi    sp, sp, 6*4
    mret
#endif

    .org    0x1e0
    1: j       1b
    nop
    mret

    .global cpu_irq_comm
cpu_irq_comm:
    la      a5, __irq_stack
    mv      sp, a5
    j       cpu_irq_comm_do

    ret

    .global _tp
    .set    _tp,        0x84800

    .set    _memcpy,    0x84044