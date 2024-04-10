/*
 * Copyright (c) 2011-2022, Shanghai Real-Thread Electronic Technology Co.,Ltd
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-08-29     RT-Thread    first version
 */


.globl rt_cpu_get_smp_id
rt_cpu_get_smp_id:
    mrc     p15, #0, r0, c0, c0, #5
    bx      lr

.globl rt_cpu_vector_set_base
rt_cpu_vector_set_base:
    /* clear SCTRL.V to customize the vector address */
    mrc     p15, #0, r1, c1, c0, #0
    bic     r1, #(1 << 13)
    mcr     p15, #0, r1, c1, c0, #0
    /* set up the vector address */
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
   .word  0x7fff

.globl rt_cpu_dcache_clean_flush
rt_cpu_dcache_clean_flush:
stmfd   sp!, {r0-r12, lr}
    bl  v7_flush_dcache_all
    mov r0, #0
    mcr p15, 0, r0, c7, c5, 0       @ I+BTB cache invalidate
    dsb
    isb
    ldmfd   sp!, {r0-r12, lr}
    mov pc, lr

v7_flush_dcache_all:
    dmb                 @ ensure ordering with previous memory accesses
    mrc p15, 1, r0, c0, c0, 1       @ read clidr
    ands    r3, r0, #0x7000000      @ extract loc from clidr
    mov r3, r3, lsr #23         @ left align loc bit field
    beq finished            @ if loc is 0, then no need to clean
    mov r10, #0             @ start clean at cache level 0
loop1:
    add r2, r10, r10, lsr #1        @ work out 3x current cache level
    mov r1, r0, lsr r2          @ extract cache type bits from clidr
    and r1, r1, #7          @ mask of the bits for current cache only
    cmp r1, #2              @ see what cache we have at this level
    blt skip                @ skip if no cache, or just i-cache
    mcr p15, 2, r10, c0, c0, 0      @ select current cache level in cssr
    isb                 @ isb to sych the new cssr&csidr
    mrc p15, 1, r1, c0, c0, 0       @ read the new csidr
    and r2, r1, #7          @ extract the length of the cache lines
    add r2, r2, #4          @ add 4 (line length offset)
    ldr r4, =0x3ff
    ands    r4, r4, r1, lsr #3      @ find maximum number on the way size
    clz r5, r4              @ find bit position of way size increment
    ldr r7, =0x7fff
    ands    r7, r7, r1, lsr #13     @ extract max number of the index size
loop2:
    mov r9, r4              @ create working copy of max way size
loop3:
    orr r11, r10, r9, lsl r5        @ factor way and cache number into r11
    orr r11, r11, r7, lsl r2        @ factor index number into r11
    mcr p15, 0, r11, c7, c14, 2     @ clean & invalidate by set/way
    subs    r9, r9, #1          @ decrement the way
    bge loop3
    subs    r7, r7, #1          @ decrement the index
    bge loop2
skip:
    add r10, r10, #2            @ increment cache number
        cmp r3, r10
        bgt loop1
finished:
    mov r10, #0             @ swith back to cache level 0
    mcr p15, 2, r10, c0, c0, 0      @ select current cache level in cssr
    dsb
    isb
    mov pc, lr
#if 0
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
#endif
.globl rt_cpu_icache_flush
rt_cpu_icache_flush:
    mov r0, #0
    mcr p15, 0, r0, c7, c5, 0       @ I+BTB cache invalidate
    dsb
    isb
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
