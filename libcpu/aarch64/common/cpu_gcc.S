/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Date           Author       Notes
 * 2018-10-06     ZhaoXiaowei    the first version
 * 2024-04-28     Shell        add generic spinlock implementation
 */

.text
.globl rt_hw_get_current_el
rt_hw_get_current_el:
    MRS        X0, CurrentEL
    CMP        X0, 0xc
    B.EQ    3f
    CMP        X0, 0x8
    B.EQ    2f
    CMP        X0, 0x4
    B.EQ    1f

    LDR        X0, =0
    B        0f
3:
    LDR        X0, =3
    B        0f
2:
    LDR        X0, =2
    B        0f
1:
    LDR        X0, =1
    B        0f
0:
    RET


.globl rt_hw_set_current_vbar
rt_hw_set_current_vbar:
    MRS        X1, CurrentEL
    CMP        X1, 0xc
    B.EQ    3f
    CMP        X1, 0x8
    B.EQ    2f
    CMP        X1, 0x4
    B.EQ    1f
    B        0f
3:
    MSR        VBAR_EL3,X0
    B        0f
2:
    MSR        VBAR_EL2,X0
    B        0f
1:
    MSR        VBAR_EL1,X0
    B        0f
0:
    RET

.globl rt_hw_set_elx_env
rt_hw_set_elx_env:
    MRS        X1, CurrentEL
    CMP        X1, 0xc
    B.EQ    3f
    CMP        X1, 0x8
    B.EQ    2f
    CMP        X1, 0x4
    B.EQ    1f
    B        0f
3:
    MRS        X0, SCR_EL3
    ORR        X0, X0, #0xF            /* SCR_EL3.NS|IRQ|FIQ|EA */
    MSR        SCR_EL3, X0
    B        0f
2:
    MRS    X0, HCR_EL2
    ORR    X0, X0, #0x38
    MSR    HCR_EL2, X0
    B        0f
1:
    B        0f
0:
    RET

.globl rt_cpu_vector_set_base
rt_cpu_vector_set_base:
    MSR        VBAR_EL1,X0
    RET


/**
 * unsigned long rt_hw_ffz(unsigned long x)
 */
.globl rt_hw_ffz
rt_hw_ffz:
    mvn     x1, x0
    clz     x0, x1
    mov     x1, #0x3f
    sub     x0, x1, x0
    ret

.globl rt_hw_clz
rt_hw_clz:
    clz     x0, x0
    ret

/**
 * Spinlock (fallback implementation)
 */

rt_hw_spin_lock_init:
    .weak   rt_hw_spin_lock_init
    stlr    wzr, [x0]
    ret

rt_hw_spin_trylock:
    .weak   rt_hw_spin_trylock
    sub     sp, sp, #16
    ldar    w2, [x0]
    add     x1, sp, 8
    stlr    w2, [x1]
    ldarh   w1, [x1]
    and     w1, w1, 65535
    add     x3, sp, 10
    ldarh   w3, [x3]
    cmp     w1, w3, uxth
    beq     1f
    mov     w0, 0
    add     sp, sp, 16
    ret
1:
    add     x1, sp, 10
2:
    ldaxrh  w3, [x1]
    add     w3, w3, 1
    stlxrh  w4, w3, [x1]
    cbnz    w4, 2b
    add     x1, sp, 8
    ldar    w1, [x1]
3:
    ldaxr   w3, [x0]
    cmp     w3, w2
    bne     4f
    stxr    w4, w1, [x0]
    cbnz    w4, 3b
4:
    cset    w0, eq
    add     sp, sp, 16
    ret

rt_hw_spin_lock:
    .weak   rt_hw_spin_lock
    add     x1, x0, 2
1:
    ldxrh   w2, [x1]
    add     w3, w2, 1
    stxrh   w4, w3, [x1]
    cbnz    w4, 1b
    and     w2, w2, 65535
    ldarh   w1, [x0]
    cmp     w2, w1, uxth
    beq     3f
    sevl
2:
    wfe
    ldaxrh  w1, [x0]
    cmp     w2, w1
    bne     2b
3:
    ret

rt_hw_spin_unlock:
    .weak   rt_hw_spin_unlock
    ldxrh   w1, [x0]
    add     w1, w1, 1
    stlxrh  w2, w1, [x0]
    cbnz    w2, rt_hw_spin_unlock
    ret
