#include <p32xxxx.h>
#include "../common/mips.inc"
#include "../common/stackframe.h"

    .section ".text", "ax"
	.set 		noat
    .set noreorder

/*
 * rt_base_t rt_hw_interrupt_disable()
 */
    .globl rt_hw_interrupt_disable
rt_hw_interrupt_disable:
    mfc0    v0, CP0_STATUS    /* v0 = status */
    addiu   v1, zero,   -2    /* v1 = 0-2 = 0xFFFFFFFE */
    and     v1, v0, v1        /* v1 = v0 & 0xFFFFFFFE */
    mtc0    v1, CP0_STATUS    /* status = v1 */
    jr      ra
    nop

/*
 * void rt_hw_interrupt_enable(rt_base_t level)
 */
    .globl rt_hw_interrupt_enable
rt_hw_interrupt_enable:
    mtc0    a0, CP0_STATUS
    jr      ra
    nop

/*
 * void rt_hw_context_switch_to(rt_uint32 to)/*
 * a0 --> to
 */
    .globl rt_hw_context_switch_to
rt_hw_context_switch_to:
    lw      sp, 0(a0)       /* get new task stack pointer */

    RESTORE_ALL_AND_RET

/*
 * void rt_hw_context_switch(rt_uint32 from, rt_uint32 to)
 * a0 --> from
 * a1 --> to
 */
    .globl rt_hw_context_switch
rt_hw_context_switch:
    mtc0    ra, CP0_EPC
    SAVE_ALL

    sw      sp, 0(a0)       /* store sp in preempted tasks TCB */
    lw      sp, 0(a1)       /* get new task stack pointer */

    RESTORE_ALL_AND_RET

/*
 * void rt_hw_context_switch_interrupt(rt_uint32 from, rt_uint32 to)/*
 */
    .globl rt_thread_switch_interrupt_flag
    .globl rt_interrupt_from_thread
    .globl rt_interrupt_to_thread
    .globl rt_hw_context_switch_interrupt
rt_hw_context_switch_interrupt:
    la      t0, rt_thread_switch_interrupt_flag
    lw      t1, 0(t0)
    nop
    bnez    t1, _reswitch
    nop
    li      t1, 0x01                       /* set rt_thread_switch_interrupt_flag to 1 */
    sw      t1, 0(t0)
    la      t0, rt_interrupt_from_thread   /* set rt_interrupt_from_thread */
    sw      a0, 0(t0)
_reswitch:
    la      t0, rt_interrupt_to_thread     /* set rt_interrupt_to_thread */
    sw      a1, 0(t0)

    /* trigger the soft exception (causes context switch) */
    mfc0    t0, CP0_CAUSE                  /* t0 = Cause */
    ori     t0, t0, (1<<8)                 /* t0 |= (1<<8) */
    mtc0    t0, CP0_CAUSE                  /* cause = t0 */
    addiu   t1,	zero,   -257               /* t1 = ~(1<<8) */
    and     t0, t0, t1                     /* t0 &= t1 */
    mtc0    t0, CP0_CAUSE                  /* cause = t0 */
    jr      ra
    nop

/*
 * void __ISR(_CORE_SOFTWARE_0_VECTOR, ipl2) CoreSW0Handler(void)
 */
    .section ".text", "ax"
    .set noreorder
	.set 		noat
 	.ent		CoreSW0Handler

	    .globl CoreSW0Handler
CoreSW0Handler:
    SAVE_ALL

	/* mCS0ClearIntFlag(); */
	la      t0, IFS0CLR             /* t0 = IFS0CLR */
	addiu   t1,zero,0x02            /* t1 = (1<<2) */
	sw      t1, 0(t0)               /* IFS0CLR = t1 */

    la      k0, rt_thread_switch_interrupt_flag
    sw      zero, 0(k0)                     /* clear flag */

    /*
     * switch to the new thread
     */
    la      k0, rt_interrupt_from_thread
    lw      k1, 0(k0)
    nop
    sw      sp, 0(k1)                       /* store sp in preempted tasks's TCB */

    la      k0, rt_interrupt_to_thread
    lw      k1, 0(k0)
    nop
    lw      sp, 0(k1)                       /* get new task's stack pointer */

    RESTORE_ALL_AND_RET

	.end		CoreSW0Handler
