#include "context.h"
#define SPRG0	0x110	/* Special Purpose Register General 0 */
#define SPRG1	0x111	/* Special Purpose Register General 1 */

    .globl rt_hw_interrupt_disable
    .globl rt_hw_interrupt_enable
    .globl rt_hw_context_switch
    .globl rt_hw_context_switch_to
    .globl rt_hw_context_switch_interrupt
    .globl rt_hw_systemcall_entry

/*
 * rt_base_t rt_hw_interrupt_disable();
 * return the interrupt status and disable interrupt
 */
#if 0
rt_hw_interrupt_disable:
    mfmsr   r3          /* Disable interrupts */
    li      r4,0
    ori     r4,r4,MSR_EE
    andc    r4,r4,r3
    SYNC                /* Some chip revs need this... */
    mtmsr   r4
    SYNC
    blr
#else
rt_hw_interrupt_disable:
    addis  r4, r0, 0xFFFD
    ori    r4, r4, 0x7FFF
    mfmsr  r3
    and    r4, r4, 3                                      /* Clear bits 14 and 16, corresponding to...   */
    mtmsr  r4                                            /* ...critical and non-critical interrupts     */
    blr
#endif

/*
 * void rt_hw_interrupt_enable(rt_base_t level);
 * restore interrupt
 */
rt_hw_interrupt_enable:
    mtmsr   r3
    SYNC
    blr

/*
 * void rt_hw_context_switch(rt_uint32 from, rt_uint32 to);
 * r3 --> from
 * r4 --> to
 *
 * r1: stack pointer
 */
rt_hw_systemcall_entry:
    mtspr   SPRG0,r3                            /* save r3 to SPRG0 */
    mtspr   SPRG1,r4                            /* save r4 to SPRG1 */

    lis     r3,rt_thread_switch_interrput_flag@h
    ori     r3,r3,rt_thread_switch_interrput_flag@l
    lwz     r4,0(r3)
    cmpi    cr0,0,r4,0x0                        /* whether is 0     */
    beq     _no_switch                          /* no switch, exit  */
    li      r4,0x0                              /* set rt_thread_switch_interrput_flag to 0 */
    stw     r4,0(r3)

    /* load from thread to r3 */
    lis     r3,rt_interrupt_from_thread@h       /* set rt_interrupt_from_thread */
    ori     r3,r3,rt_interrupt_from_thread@l
    lwz     r3,0(r3)

    cmpi    cr0,0,r3,0x0                        /* whether is 0 */
    beq     _restore                            /* it's first switch, goto _restore */

    /* save r1:sp to thread[from] stack pointer */
    subi    r1, r1, STACK_FRAME_SIZE
    stw     r1, 0(r3)

    /* restore r3, r4 from SPRG */
    mfspr   r3,SPRG0
    mfspr   r4,SPRG0

    /* save registers   */
    stw     r0,GPR0(r1)                         /* save general purpose registers 0    */
    stmw    r2,GPR2(r1)                         /* save general purpose registers 2-31 */

    mfusprg0 r0                                 /* save usprg0  */
    stw     r0,USPRG0(r1)
    mfcr    r0,                                 /* save cr      */
    stw     r0,CR(r1)
    mfxer   r0                                  /* save xer     */
    stw     r0,XER(r1)
    mfctr   r0                                  /* save ctr     */
    stw     r0,CTR(r1)
    mflr    r0                                  /* save lr      */
    stw     r0, LR(r1)

    mfsrr0  r0                                  /* save SRR0 and SRR1   */
    stw     r0,SRR0(r1)
    mfsrr1  r0
    stw     r0,SRR1(r1)

_restore:
    /* get thread[to] stack pointer */
    lis     r4,rt_interrupt_to_thread@h
    ori     r4,r4,rt_interrupt_to_thread@l
    lwz     r1,0(r4)
    lwz     r1,0(r1)

    lwz     r0,SRR1(r1)                         /* restore SRR1 and SRR0   */
    mtsrr1  r0
    lwz     r0,SRR0(r1)
    mtsrr0  r0

    lwz     r0,LR(r1)                           /* restore lr       */
    mtlr    r0
    lwz     r0,CTR(r1)                          /* restore ctr     */
    mtctr   r0
    lwz     r0,XER(r1)                          /* restore xer     */
    mtxer   r0
    lwz     r0,CR(r1)                           /* restore cr      */
    mtcr    r0
    lwz     r0,USPRG0(r1)                       /* restore usprg0  */
    // mtusprg0 r0

    lmw     r2, GPR2(r1)                        /* restore general register */
    lwz     r0,GPR0(r1)
    addi    r1, r1, STACK_FRAME_SIZE
    /* RFI will restore status register and thus the correct priority*/
    rfi

_no_switch:
    /* restore r3, r4 from SPRG */
    mfspr   r3,SPRG0
    mfspr   r4,SPRG0
    rfi

    /* void rt_hw_context_switch_to(to); */
    .globl rt_hw_context_switch_to
rt_hw_context_switch_to:
    /* set rt_thread_switch_interrput_flag = 1 */
    lis     r5,rt_thread_switch_interrput_flag@h
    ori     r5,r5,rt_thread_switch_interrput_flag@l
    li      r6, 0x01
    stw     r6,0(r5)

    /* set rt_interrupt_from_thread = 0 */
    lis     r5,rt_interrupt_from_thread@h
    ori     r5,r5,rt_interrupt_from_thread@l
    li      r6, 0x00
    stw     r6,0(r5)

    /* set rt_interrupt_from_thread = to */
    lis     r5,rt_interrupt_to_thread@h
    ori     r5,r5,rt_interrupt_to_thread@l
    stw     r3,0(r5)

    /* trigger a system call */
    sc

    blr

    /* void rt_hw_context_switch(from, to); */
    .globl rt_hw_context_switch
rt_hw_context_switch:
    /* compare rt_thread_switch_interrupt_flag and set it */
    lis     r5,rt_thread_switch_interrput_flag@h
    ori     r5,r5,rt_thread_switch_interrput_flag@l
    lwz     r6,0(r5)
    cmpi    cr0,0,r6,0x1                        /* whether is 1 */
    beq     _reswitch                           /* set already, goto _reswitch */
    li      r6,0x1                              /* set rt_thread_switch_interrput_flag to 1*/
    stw     r6,0(r5)

    /* set rt_interrupt_from_thread to 'from' */
    lis     r5,rt_interrupt_from_thread@h
    ori     r5,r5,rt_interrupt_from_thread@l
    stw     r3,0(r5)

_reswitch:
    /* set rt_interrupt_to_thread to 'to' */
    lis     r6,rt_interrupt_to_thread@h
    ori     r6,r6,rt_interrupt_to_thread@l
    stw     r4,0(r6)

    /* trigger a system call */
    sc

    blr

    .globl rt_hw_context_switch_interrupt
rt_hw_context_switch_interrupt:
    /* compare rt_thread_switch_interrupt_flag and set it */
    lis     r5,rt_thread_switch_interrput_flag@h
    ori     r5,r5,rt_thread_switch_interrput_flag@l
    lwz     r6,0(r5)
    cmpi    cr0,0,r6,0x1                        /* whether is 1 */
    beq     _int_reswitch                       /* set already, goto _reswitch */
    li      r6,0x1                              /* set rt_thread_switch_interrput_flag to 1*/
    stw     r6,0(r5)

    /* set rt_interrupt_from_thread to 'from' */
    lis     r5,rt_interrupt_from_thread@h
    ori     r5,r5,rt_interrupt_from_thread@l
    stw     r3,0(r5)

_int_reswitch:
    /* set rt_interrupt_to_thread to 'to' */
    lis     r6,rt_interrupt_to_thread@h
    ori     r6,r6,rt_interrupt_to_thread@l
    stw     r4,0(r6)

    blr
