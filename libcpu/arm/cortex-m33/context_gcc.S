/*
 * Copyright (c) 2006-2018, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2009-10-11     Bernard      first version
 * 2012-01-01     aozima       support context switch load/store FPU register.
 * 2013-06-18     aozima       add restore MSP feature.
 * 2013-06-23     aozima       support lazy stack optimized.
 * 2018-07-24     aozima       enhancement hard fault exception handler.
 */

/**
 * @addtogroup cortex-m4
 */
/*@{*/

.cpu cortex-m4
.syntax unified
.thumb
.text

.equ    SCB_VTOR,           0xE000ED08              /* Vector Table Offset Register */
.equ    NVIC_INT_CTRL,      0xE000ED04              /* interrupt control state register */
.equ    NVIC_SYSPRI2,       0xE000ED20              /* system priority register (2) */
.equ    NVIC_PENDSV_PRI,    0xFFFF0000              /* PendSV and SysTick priority value (lowest) */
.equ    NVIC_PENDSVSET,     0x10000000              /* value to trigger PendSV exception */

/*
 * rt_base_t rt_hw_interrupt_disable();
 */
.global rt_hw_interrupt_disable
.type rt_hw_interrupt_disable, %function
rt_hw_interrupt_disable:
    MRS     r0, PRIMASK
    CPSID   I
    BX      LR

/*
 * void rt_hw_interrupt_enable(rt_base_t level);
 */
.global rt_hw_interrupt_enable
.type rt_hw_interrupt_enable, %function
rt_hw_interrupt_enable:
    MSR     PRIMASK, r0
    BX      LR

/*
 * void rt_hw_context_switch(rt_uint32 from, rt_uint32 to);
 * r0 --> from
 * r1 --> to
 */
.global rt_hw_context_switch_interrupt
.type rt_hw_context_switch_interrupt, %function
.global rt_hw_context_switch
.type rt_hw_context_switch, %function

rt_hw_context_switch_interrupt:
rt_hw_context_switch:
    /* set rt_thread_switch_interrupt_flag to 1 */
    LDR     r2, =rt_thread_switch_interrupt_flag
    LDR     r3, [r2]
    CMP     r3, #1
    BEQ     _reswitch
    MOV     r3, #1
    STR     r3, [r2]

    LDR     r2, =rt_interrupt_from_thread   /* set rt_interrupt_from_thread */
    STR     r0, [r2]

_reswitch:
    LDR     r2, =rt_interrupt_to_thread     /* set rt_interrupt_to_thread */
    STR     r1, [r2]

    LDR r0, =NVIC_INT_CTRL              /* trigger the PendSV exception (causes context switch) */
    LDR r1, =NVIC_PENDSVSET
    STR r1, [r0]
    BX  LR

/* r0 --> switch from thread stack
 * r1 --> switch to thread stack
 * psr, pc, lr, r12, r3, r2, r1, r0 are pushed into [from] stack
 */
.global PendSV_Handler
.type PendSV_Handler, %function
PendSV_Handler:
    /* disable interrupt to protect context switch */
    MRS r2, PRIMASK
    CPSID   I

    /* get rt_thread_switch_interrupt_flag */
    LDR     r0, =rt_thread_switch_interrupt_flag    /* r0 = &rt_thread_switch_interrupt_flag */
    LDR     r1, [r0]                                /* r1 = *r1 */
    CMP     r1, #0x00                               /* compare r1 == 0x00 */
    BNE     schedule
    MSR     PRIMASK, r2                             /* if r1 == 0x00, do msr PRIMASK, r2 */
    BX      lr                                      /* if r1 == 0x00, do bx lr */

schedule:
    PUSH    {r2}                                    /* store interrupt state */

    /* clear rt_thread_switch_interrupt_flag to 0 */
    MOV     r1, #0x00                               /* r1 = 0x00 */
    STR     r1, [r0]                                /* *r0 = r1 */

    /* skip register save at the first time */
    LDR     r0, =rt_interrupt_from_thread           /* r0 = &rt_interrupt_from_thread */
    LDR     r1, [r0]                                /* r1 = *r0 */
    CBZ     r1, switch_to_thread                    /* if r1 == 0, goto switch_to_thread */

    /* Whether TrustZone thread stack exists */
    LDR     r1,  =rt_trustzone_current_context      /* r1 = &rt_secure_current_context */
    LDR     r1, [r1]                                /* r1 = *r1 */
    CBZ     r1, contex_ns_store                     /* if r1 == 0, goto contex_ns_store */

    /*call TrustZone fun, Save TrustZone stack */
    STMFD   sp!, {r0-r1, lr}                        /* push register */
    MOV     r0, r1                                  /* r0 = rt_secure_current_context */
    BL rt_trustzone_context_store                   /* call TrustZone store fun */
    LDMFD   sp!, {r0-r1, lr}                        /* pop register */

    /* check break from TrustZone */
    MOV     r2, lr                                  /* r2 = lr */
    TST     r2, #0x40                               /* if EXC_RETURN[6] is 1, TrustZone stack was used */
    BEQ     contex_ns_store                         /* if r2 & 0x40 == 0, goto contex_ns_store */

    /* push PSPLIM CONTROL PSP LR current_context to stack */
    MRS     r3, psplim                              /* r3 = psplim */
    MRS     r4, control                             /* r4 = control */
    MRS     r5, psp                                 /* r5 = psp */
    STMFD   r5!, {r1-r4}                            /* push to thread stack */

    /* update from thread stack pointer */
    LDR     r0, [r0]                                /* r0 = rt_thread_switch_interrupt_flag */
    STR     r5, [r0]                                /* *r0 = r5 */
    b switch_to_thread                              /* goto switch_to_thread */

contex_ns_store:

    MRS     r1, psp                                 /* get from thread stack pointer */

#if defined (__VFP_FP__) && !defined(__SOFTFP__)
    TST     lr, #0x10                               /* if(!EXC_RETURN[4]) */
    IT      EQ
    VSTMDBEQ  r1!, {d8 - d15}                       /* push FPU register s16~s31 */
#endif

    STMFD   r1!, {r4 - r11}                         /* push r4 - r11 register */

    LDR     r2,  =rt_trustzone_current_context      /* r2 = &rt_secure_current_context */
    LDR     r2, [r2]                                /* r2 = *r2 */
    MOV     r3, lr                                  /* r3 = lr */
    MRS     r4, psplim                              /* r4 = psplim */
    MRS     r5, control                             /* r5 = control */
    STMFD   r1!, {r2-r5}                            /* push to thread stack */

    LDR     r0, [r0]
    STR     r1, [r0]                                /* update from thread stack pointer */

switch_to_thread:
    LDR     r1, =rt_interrupt_to_thread
    LDR     r1, [r1]
    LDR     r1, [r1]                                /* load thread stack pointer */

    /* update current TrustZone context */
    LDMFD   r1!, {r2-r5}                            /* pop thread stack */
    MSR     psplim, r4                              /* psplim = r4 */
    MSR     control, r5                             /* control = r5 */
    MOV     lr, r3                                  /* lr = r3 */
    LDR     r6,  =rt_trustzone_current_context      /* r6 = &rt_secure_current_context */
    STR     r2, [r6]                                /* *r6 = r2 */
    MOV     r0, r2                                  /* r0 = r2 */

    /* Whether TrustZone thread stack exists */
    CBZ     r0, contex_ns_load                      /* if r0 == 0, goto contex_ns_load */
    PUSH    {r1, r3}                                /* push lr, thread_stack */
    BL rt_trustzone_context_load                    /* call TrustZone load fun */
    POP     {r1, r3}                                /* pop lr, thread_stack */
    MOV     lr, r3                                  /* lr = r1 */
    TST     r3, #0x40                               /* if EXC_RETURN[6] is 1, TrustZone stack was used */
    BEQ     contex_ns_load                          /* if r1 & 0x40 == 0, goto contex_ns_load */
    B pendsv_exit

contex_ns_load:
    LDMFD   r1!, {r4 - r11}                         /* pop r4 - r11 register */

#if defined (__VFP_FP__) && !defined(__SOFTFP__)
    TST     lr, #0x10                               /* if(!EXC_RETURN[4]) */
    IT      EQ
    VLDMIAEQ  r1!, {d8 - d15}                       /* pop FPU register s16~s31 */
#endif

pendsv_exit:
    MSR     psp, r1                                 /* update stack pointer */
    /* restore interrupt */
    POP    {r2}
    MSR     PRIMASK, r2

    BX      lr

/*
 * void rt_hw_context_switch_to(rt_uint32 to);
 * r0 --> to
 */
.global rt_hw_context_switch_to
.type rt_hw_context_switch_to, %function
rt_hw_context_switch_to:
    LDR r1, =rt_interrupt_to_thread
    STR r0, [r1]

#if defined (__VFP_FP__) && !defined(__SOFTFP__)
    /* CLEAR CONTROL.FPCA */
    MRS     r2, CONTROL         /* read */
    BIC     r2, #0x04           /* modify */
    MSR     CONTROL, r2         /* write-back */
#endif

    /* set from thread to 0 */
    LDR r1, =rt_interrupt_from_thread
    MOV r0, #0x0
    STR r0, [r1]

    /* set interrupt flag to 1 */
    LDR     r1, =rt_thread_switch_interrupt_flag
    MOV     r0, #1
    STR     r0, [r1]

    /* set the PendSV and SysTick exception priority */
    LDR r0, =NVIC_SYSPRI2
    LDR r1, =NVIC_PENDSV_PRI
    LDR.W   r2, [r0,#0x00]       /* read       */
    ORR     r1,r1,r2             /* modify     */
    STR     r1, [r0]             /* write-back */

    LDR r0, =NVIC_INT_CTRL      /* trigger the PendSV exception (causes context switch) */
    LDR r1, =NVIC_PENDSVSET
    STR r1, [r0]

    /* restore MSP */
    LDR     r0, =SCB_VTOR
    LDR     r0, [r0]
    LDR     r0, [r0]
    NOP
    MSR     msp, r0

    /* enable interrupts at processor level */
    CPSIE   F
    CPSIE   I

    /* never reach here! */

/* compatible with old version */
.global rt_hw_interrupt_thread_switch
.type rt_hw_interrupt_thread_switch, %function
rt_hw_interrupt_thread_switch:
    BX  lr
    NOP

.global HardFault_Handler
.type HardFault_Handler, %function
HardFault_Handler:
    /* get current context */
    MRS     r0, msp                                 /* get fault context from handler. */
    TST     lr, #0x04                               /* if(!EXC_RETURN[2]) */
    BEQ     get_sp_done
    MRS     r0, psp                                 /* get fault context from thread. */
get_sp_done:

    STMFD   r0!, {r4 - r11}                         /* push r4 - r11 register */

    LDR     r2,  =rt_trustzone_current_context      /* r2 = &rt_secure_current_context */
    LDR     r2, [r2]                                /* r2 = *r2 */
    MOV     r3, lr                                  /* r3 = lr */
    MRS     r4, psplim                              /* r4 = psplim */
    MRS     r5, control                             /* r5 = control */
    STMFD   r0!, {r2-r5}                            /* push to thread stack */

    STMFD   r0!, {lr}                               /* push exec_return register */

    TST     lr, #0x04                               /* if(!EXC_RETURN[2]) */
    BEQ     update_msp
    MSR     psp, r0                                 /* update stack pointer to PSP. */
    B       update_done
update_msp:
    MSR     msp, r0                                 /* update stack pointer to MSP. */
update_done:

    PUSH    {LR}
    BL      rt_hw_hard_fault_exception
    POP     {LR}

    ORR     lr, lr, #0x04
    BX      lr
