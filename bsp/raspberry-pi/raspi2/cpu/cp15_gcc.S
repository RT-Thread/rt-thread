/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-05     Bernard      the first version
 */

.globl rt_cpu_get_smp_id
rt_cpu_get_smp_id:
    mrc     p15, #0, r0, c0, c0, #5
    bx      lr

.globl rt_cpu_vector_set_base
rt_cpu_vector_set_base:
    mcr     p15, #0, r0, c12, c0, #0
    dsb
    bx      lr

.globl rt_hw_cpu_dcache_enable
rt_hw_cpu_dcache_enable:
    mrc     p15, #0, r0, c1, c0, #0
    orr     r0,  r0, #0x00000004
    mcr     p15, #0, r0, c1, c0, #0
    bx      lr

.globl rt_hw_cpu_icache_enable
rt_hw_cpu_icache_enable:
    mrc     p15, #0, r0, c1, c0, #0
    orr     r0,  r0, #0x00001000
    mcr     p15, #0, r0, c1, c0, #0
    bx      lr

_FLD_MAX_WAY:
   .word  0x3ff
_FLD_MAX_IDX:
   .word  0x7ff

.globl rt_cpu_dcache_clean_flush
rt_cpu_dcache_clean_flush:
    push    {r4-r11}
    dmb
    mrc     p15, #1, r0, c0, c0, #1  @ read clid register
    ands    r3, r0, #0x7000000       @ get level of coherency
    mov     r3, r3, lsr #23
    beq     finished
    mov     r10, #0
loop1:
    add     r2, r10, r10, lsr #1
    mov     r1, r0, lsr r2
    and     r1, r1, #7
    cmp     r1, #2
    blt     skip
    mcr     p15, #2, r10, c0, c0, #0
    isb
    mrc     p15, #1, r1, c0, c0, #0
    and     r2, r1, #7
    add     r2, r2, #4
    ldr     r4, _FLD_MAX_WAY
    ands    r4, r4, r1, lsr #3
    clz     r5, r4
    ldr     r7, _FLD_MAX_IDX
    ands    r7, r7, r1, lsr #13
loop2:
    mov     r9, r4
loop3:
    orr     r11, r10, r9, lsl r5
    orr     r11, r11, r7, lsl r2
    mcr     p15, #0, r11, c7, c14, #2
    subs    r9, r9, #1
    bge     loop3
    subs    r7, r7, #1
    bge     loop2
skip:
    add     r10, r10, #2
    cmp     r3, r10
    bgt     loop1

finished:
    dsb
    isb
    pop     {r4-r11}
    bx      lr

.globl rt_hw_cpu_dcache_disable
rt_hw_cpu_dcache_disable:
    push    {r4-r11, lr}
    bl      rt_cpu_dcache_clean_flush
    mrc     p15, #0, r0, c1, c0, #0
    bic     r0,  r0, #0x00000004
    mcr     p15, #0, r0, c1, c0, #0
    pop     {r4-r11, lr}
    bx      lr

.globl rt_hw_cpu_icache_disable
rt_hw_cpu_icache_disable:
    mrc     p15, #0, r0, c1, c0, #0
    bic     r0,  r0, #0x00001000
    mcr     p15, #0, r0, c1, c0, #0
    bx      lr

.globl rt_cpu_mmu_disable
rt_cpu_mmu_disable:
    mcr     p15, #0, r0, c8, c7, #0    @ invalidate tlb
    mrc     p15, #0, r0, c1, c0, #0
    bic     r0, r0, #1
    mcr     p15, #0, r0, c1, c0, #0    @ clear mmu bit
    dsb
    bx      lr

.globl rt_cpu_mmu_enable
rt_cpu_mmu_enable:
    mrc     p15, #0, r0, c1, c0, #0
    orr     r0, r0, #0x001
    mcr     p15, #0, r0, c1, c0, #0    @ set mmu enable bit
    dsb
    bx      lr

.globl rt_cpu_tlb_set
rt_cpu_tlb_set:
    mcr     p15, #0, r0, c2, c0, #0
    dmb
    bx      lr
