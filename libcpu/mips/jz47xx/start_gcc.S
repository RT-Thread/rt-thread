/*
 * File      : start_gcc.S
 * Change Logs:
 * Date           Author       Notes
 * 2010-05-17     swkyer       first version
 */
#include "../common/mips.inc"
#include "../common/stackframe.h"
#include "jz47xx.h"

    .section ".start", "ax"
    .set noreorder

    .extern sys_exception_handlers
    .extern tlbmiss_handle

    .globl _entry
    /* exception entry */
_entry:
.org 0x0
    .set    noreorder
    mfc0    t0, $14
    jal     tlbmiss_handle
    move    a0, t0
    j       _sys_dead                /* TLB Miss, should never happen */
    nop
    .set    reorder

    /*
     * void config_tick_timer(uint32_t perio)
     */
    .globl  config_tick_timer
config_tick_timer:
    mfc0    t0, $9          /* count */
    nop
    addu    t1, t0, a0
    mtc0    t1, $11         /* compare */
    jr      ra
    nop

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

.org 0x100
    .set    noreorder
    j       _sys_dead                /* cache error exception handle */
    nop
    .set    reorder


    .globl  disable_cp0_counter
disable_cp0_counter:
    .set    noreorder
    mfc0    t0, CP0_CAUSE
    lui     t1, 0x0800
    or      t0, t1
    mtc0    t0, CP0_CAUSE
    jr      ra
    nop
    .set    reorder

    .globl  enable_cp0_counter
enable_cp0_counter:
    .set    noreorder
    mfc0    t0, CP0_CAUSE
    lui     t1, 0x0800
    not     t2, t1
    and     t0, t0, t2
    mtc0    t0, CP0_CAUSE
    jr      ra
    nop
    .set    reorder

    // general exception handle
.org 0x180
_gen_exp_handle:
    .set    noreorder
    mfc0    k1, CP0_CAUSE
    andi    k1, k1, 0x7c
    srl     k1, k1, 2
    lw      k0, sys_exception_handlers(k1)
    jr      k0
    nop
    .set    reorder

    /* error happens */
_sys_dead:
    .set    noreorder
    jal     rt_hw_cpu_reset
    nop
    /* should never return here */
    j       _sys_dead
    nop
    .set    reorder


    .globl mips_irq_handle
    /* interrupt handle */
.org 0x200
_irq_handle:
    .set    noreorder
    la      k0, mips_irq_handle
    jr      k0
    nop
    .set    reorder


    /* the REAL program entry */
    .extern mips32_cfg_init
    .extern r4k_cache_init
    .extern install_default_execpt_handle
    .globl  _start
.org 0x400
_start:
    .set    noreorder
    la      ra, _start

    /* init cp0 registers. */
    li	    t0, 0x0040FC00
    mtc0    t0, CP0_STATUS

    li	    t1, 0x00800000
    mtc0    t1, CP0_CAUSE

    /* setup stack pointer */
    li      sp, SYSTEM_STACK
    la      gp, _gp

    /* clear bss */
    la      t0, __bss_start
    la      t1, __bss_end
_clr_bss_loop:
    sw      zero, 0(t0)
    bne     t0, t1, _clr_bss_loop
    addiu   t0, t0, 4

    /* read core config */
    jal     mips32_cfg_init
    nop

    /* initialize cache */
    jal     r4k_cache_init
    nop

    /* setup default exception handle */
    jal     install_default_execpt_handle
    nop

    /* jump to RT-Thread RTOS */
    jal     rtthread_startup
    nop

    /* restart, never die */
    j       _start
    nop
    .set    reorder
