/*
 * Copyright (c) 2006-2022, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-04-06     zchong      change to iar compiler from convert from cp15_gcc.S
 */

    SECTION .text:CODE:NOROOT(2)

    ARM

    EXPORT  rt_cpu_vector_set_base
rt_cpu_vector_set_base:
        MCR     p15, #0, r0, c12, c0, #0
        DSB
        BX      lr

    EXPORT  rt_cpu_vector_get_base
rt_cpu_vector_get_base:
        MRC     p15, #0, r0, c12, c0, #0
        BX      lr

    EXPORT  rt_cpu_get_sctlr
rt_cpu_get_sctlr:
        MRC     p15, #0, r0, c1, c0, #0
        BX      lr

    EXPORT  rt_cpu_dcache_enable
rt_cpu_dcache_enable:
        MRC     p15, #0, r0, c1, c0, #0
        ORR     r0,  r0, #0x00000004
        MCR     p15, #0, r0, c1, c0, #0
        BX      lr

    EXPORT  rt_cpu_icache_enable
rt_cpu_icache_enable:
        MRC     p15, #0, r0, c1, c0, #0
        ORR     r0,  r0, #0x00001000
        MCR     p15, #0, r0, c1, c0, #0
        BX      lr

;_FLD_MAX_WAY DEFINE 0x3ff
;_FLD_MAX_IDX DEFINE 0x7ff


    EXPORT  rt_cpu_dcache_clean_flush
rt_cpu_dcache_clean_flush:
        PUSH    {r4-r11}
        DMB
        MRC     p15, #1, r0, c0, c0, #1  ; read clid register
        ANDS    r3, r0, #0x7000000       ; get level of coherency
        MOV     r3, r3, lsr #23
        BEQ     finished
        MOV     r10, #0
loop1:
        ADD     r2, r10, r10, lsr #1
        MOV     r1, r0, lsr r2
        AND     r1, r1, #7
        CMP     r1, #2
        BLT     skip
        MCR     p15, #2, r10, c0, c0, #0
        ISB
        MRC     p15, #1, r1, c0, c0, #0
        AND     r2, r1, #7
        ADD     r2, r2, #4
        ;LDR     r4, _FLD_MAX_WAY
        LDR     r4, =0x3FF
        ANDS    r4, r4, r1, lsr #3
        CLZ     r5, r4
        ;LDR     r7, _FLD_MAX_IDX
        LDR     r7, =0x7FF
        ANDS    r7, r7, r1, lsr #13
loop2:
        MOV     r9, r4
loop3:
        ORR     r11, r10, r9, lsl r5
        ORR     r11, r11, r7, lsl r2
        MCR     p15, #0, r11, c7, c14, #2
        SUBS    r9, r9, #1
        BGE     loop3
        SUBS    r7, r7, #1
        BGE     loop2
skip:
        ADD     r10, r10, #2
        CMP     r3, r10
        BGT     loop1

finished:
        DSB
        ISB
        POP     {r4-r11}
        BX      lr


    EXPORT  rt_cpu_dcache_disable
rt_cpu_dcache_disable:
        PUSH    {r4-r11, lr}
        MRC     p15, #0, r0, c1, c0, #0
        BIC     r0,  r0, #0x00000004
        MCR     p15, #0, r0, c1, c0, #0
        BL      rt_cpu_dcache_clean_flush
        POP     {r4-r11, lr}
        BX      lr


    EXPORT  rt_cpu_icache_disable
rt_cpu_icache_disable:
        MRC     p15, #0, r0, c1, c0, #0
        BIC     r0,  r0, #0x00001000
        MCR     p15, #0, r0, c1, c0, #0
        BX      lr

    EXPORT  rt_cpu_mmu_disable
rt_cpu_mmu_disable:
        MCR     p15, #0, r0, c8, c7, #0    ; invalidate tlb
        MRC     p15, #0, r0, c1, c0, #0
        BIC     r0, r0, #1
        MCR     p15, #0, r0, c1, c0, #0    ; clear mmu bit
        DSB
        BX      lr

    EXPORT  rt_cpu_mmu_enable
rt_cpu_mmu_enable:
        MRC     p15, #0, r0, c1, c0, #0
        ORR     r0, r0, #0x001
        MCR     p15, #0, r0, c1, c0, #0    ; set mmu enable bit
        DSB
        BX      lr

    EXPORT  rt_cpu_tlb_set
rt_cpu_tlb_set:
        MCR     p15, #0, r0, c2, c0, #0
        DMB
        BX      lr

    END
