/*
 * File      : start_gcc.S
 * Change Logs:
 * Date           Author       Notes
 * 2010-05-17     swkyer       first version
 * 2010-09-04     bernard      porting to Jz47xx
 */

#include "../common/mips.inc"
#include "../common/stackframe.h"
#include "stack.h"

    .section ".start", "ax"
    .set noreorder

    /* the program entry */
    .globl  _start
_start:
    .set    noreorder
    la      ra, _start

    li      t1, 0x00800000
    mtc0    t1, CP0_CAUSE

    /* init cp0 registers. */
    li      t0, 0x0000FC00 /* BEV = 0 and mask all interrupt */
    mtc0    t0, CP0_STATUS

    /* setup stack pointer */
    li      sp, SYSTEM_STACK
    la      gp, _gp

    /* init caches, assumes a 4way * 128set * 32byte I/D cache */
    mtc0    zero, CP0_TAGLO  /* TAGLO reg */
    mtc0    zero, CP0_TAGHI  /* TAGHI reg */
    li      t0, 3            /* enable cache for kseg0 accesses */
    mtc0    t0, CP0_CONFIG   /* CONFIG reg */
    la      t0, 0x80000000   /* an idx op should use an unmappable address */
    ori     t1, t0, 0x4000   /* 16kB cache */

_cache_loop:
    cache   0x8, 0(t0)       /* index store icache tag */
    cache   0x9, 0(t0)       /* index store dcache tag */
    bne     t0, t1, _cache_loop
    addiu   t0, t0, 0x20     /* 32 bytes per cache line */
    nop

    /* invalidate BTB */
    mfc0    t0, CP0_CONFIG
    nop
    ori     t0, 2
    mtc0    t0, CP0_CONFIG
    nop

    /* copy IRAM section */
    la     t0, _iramcopy
    la     t1, _iramstart
    la     t2, _iramend
_iram_loop:
    lw     t3, 0(t0)
    sw     t3, 0(t1)
    addiu  t1, 4
    bne    t1, t2, _iram_loop
    addiu  t0, 4
    /* clear bss */
    la      t0, __bss_start
    la      t1, __bss_end
_clr_bss_loop:
    sw      zero, 0(t0)
    bne     t0, t1, _clr_bss_loop
    addiu   t0, t0, 4

    /* jump to RT-Thread RTOS */
    jal     rtthread_startup
    nop

    /* restart, never die */
    j       _start
    nop
    .set    reorder

    .globl  cp0_get_cause
cp0_get_cause:
    mfc0    v0, CP0_CAUSE
    jr      ra
    nop

    .globl  cp0_get_status
cp0_get_status:
    mfc0    v0, CP0_STATUS
    jr      ra
    nop

    .globl  cp0_get_hi
cp0_get_hi:
    mfhi    v0
    jr      ra
    nop

    .globl  cp0_get_lo
cp0_get_lo:
    mflo    v0
    jr      ra
    nop

    .extern tlb_refill_handler
    .extern cache_error_handler

    /* Exception Handler */
    /* 0x0 - TLB refill handler */
    .section .vectors.1, "ax", %progbits
    j      tlb_refill_handler
    nop
    
    /* 0x100 - Cache error handler */
    .section .vectors.2, "ax", %progbits
    j      cache_error_handler
    nop
    
    /* 0x180 - Exception/Interrupt handler */
    .section .vectors.3, "ax", %progbits
    j      _general_exception_handler
    nop
    
    /* 0x200 - Special Exception Interrupt handler (when IV is set in CP0_CAUSE) */
    .section .vectors.4, "ax", %progbits
    j      _irq_handler
    nop
    
    .section .vectors, "ax", %progbits
    .extern mips_irq_handle

    /* general exception handler */
_general_exception_handler:
    .set    noreorder
    mfc0    k1, CP0_CAUSE
    andi    k1, k1, 0x7c
    srl     k1, k1, 2
    lw      k0, sys_exception_handlers(k1)
    jr      k0
    nop
    .set    reorder

    /* interrupt handler */
_irq_handler:
    .set    noreorder
    la      k0, mips_irq_handle
    jr      k0
    nop
    .set    reorder
