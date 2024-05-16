/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-18     Jesven       the first version
 * 2023-06-24     WangXiaoyao  Support backtrace for user thread
 * 2024-01-06     Shell        Fix barrier on irq_disable/enable
 * 2024-01-18     Shell        fix implicit dependency of cpuid management
 */

#ifndef __ASSEMBLY__
#define __ASSEMBLY__
#endif

#include "rtconfig.h"
#include "asm-generic.h"
#include "asm-fpu.h"
#include "armv8.h"
#include "include/context_gcc.h"

.text

/**
 * #ifdef RT_USING_OFW
 * void rt_hw_cpu_id_set(long cpuid)
 * #else
 * void rt_hw_cpu_id_set(void)
 * #endif
 */
.type rt_hw_cpu_id_set, @function
rt_hw_cpu_id_set:
#ifdef ARCH_USING_GENERIC_CPUID
    .globl  rt_hw_cpu_id_set
#else /* !ARCH_USING_GENERIC_CPUID */
    .weak   rt_hw_cpu_id_set
#endif /* ARCH_USING_GENERIC_CPUID */

#ifndef RT_USING_OFW
    mrs     x0, mpidr_el1           /* MPIDR_EL1: Multi-Processor Affinity Register */
#ifdef ARCH_ARM_CORTEX_A55
    lsr     x0, x0, #8
#endif /* ARCH_ARM_CORTEX_A55 */
    and     x0, x0, #15
#endif /* !RT_USING_OFW */

#ifdef ARCH_USING_HW_THREAD_SELF
    msr     tpidrro_el0, x0
#else /* !ARCH_USING_HW_THREAD_SELF */
    msr     tpidr_el1, x0
#endif /* ARCH_USING_HW_THREAD_SELF */
    ret

/*
int rt_hw_cpu_id(void)
*/
.type rt_hw_cpu_id, @function
rt_hw_cpu_id:
#ifdef ARCH_USING_GENERIC_CPUID
    .globl rt_hw_cpu_id
#else /* !ARCH_USING_GENERIC_CPUID */
    .weak rt_hw_cpu_id
#endif /* ARCH_USING_GENERIC_CPUID */

#if RT_CPUS_NR > 1
    #ifdef ARCH_USING_GENERIC_CPUID
        mrs x0, tpidrro_el0
    #else /* !ARCH_USING_GENERIC_CPUID */
        mrs x0, tpidr_el1
    #endif /* ARCH_USING_GENERIC_CPUID */
#else /* RT_CPUS_NR == 1 */
    mov x0, xzr
#endif
    ret

/*
void rt_hw_set_process_id(size_t id)
*/
.global rt_hw_set_process_id
rt_hw_set_process_id:
    msr CONTEXTIDR_EL1, x0
    ret

  /*
 *enable gtimer
 */
.globl rt_hw_gtimer_enable
rt_hw_gtimer_enable:
    MOV X0,#1
    MSR CNTP_CTL_EL0,X0
    RET

/*
 *set gtimer CNTP_TVAL_EL0 value
 */
.globl rt_hw_set_gtimer_val
rt_hw_set_gtimer_val:
    MSR CNTP_TVAL_EL0,X0
    RET

/*
 *get gtimer CNTP_TVAL_EL0 value
 */
.globl rt_hw_get_gtimer_val
rt_hw_get_gtimer_val:
    MRS X0,CNTP_TVAL_EL0
    RET


.globl rt_hw_get_cntpct_val
rt_hw_get_cntpct_val:
    MRS X0, CNTPCT_EL0
    RET

/*
 *get gtimer frq value
 */
.globl rt_hw_get_gtimer_frq
rt_hw_get_gtimer_frq:
    MRS X0,CNTFRQ_EL0
    RET

START_POINT(_thread_start)
    blr x19
    mov x29, #0
    blr x20
    b   .   /* never here */
START_POINT_END(_thread_start)

.macro SAVE_CONTEXT
    /* Save the entire context. */
    SAVE_FPU SP
    STP     X0, X1, [SP, #-0x10]!
    STP     X2, X3, [SP, #-0x10]!
    STP     X4, X5, [SP, #-0x10]!
    STP     X6, X7, [SP, #-0x10]!
    STP     X8, X9, [SP, #-0x10]!
    STP     X10, X11, [SP, #-0x10]!
    STP     X12, X13, [SP, #-0x10]!
    STP     X14, X15, [SP, #-0x10]!
    STP     X16, X17, [SP, #-0x10]!
    STP     X18, X19, [SP, #-0x10]!
    STP     X20, X21, [SP, #-0x10]!
    STP     X22, X23, [SP, #-0x10]!
    STP     X24, X25, [SP, #-0x10]!
    STP     X26, X27, [SP, #-0x10]!
    STP     X28, X29, [SP, #-0x10]!
    MRS     X28, FPCR
    MRS     X29, FPSR
    STP     X28, X29, [SP, #-0x10]!
    MRS     X29, SP_EL0
    STP     X29, X30, [SP, #-0x10]!

    MRS     X3, SPSR_EL1
    MRS     X2, ELR_EL1

    STP     X2, X3, [SP, #-0x10]!

    MOV     X0, SP   /* Move SP into X0 for saving. */
.endm

.macro RESTORE_CONTEXT_WITHOUT_MMU_SWITCH
    /* the SP is already ok */
    LDP     X2, X3, [SP], #0x10  /* SPSR and ELR. */

    TST     X3, #0x1f
    MSR     SPSR_EL1, X3
    MSR     ELR_EL1, X2

    LDP     X29, X30, [SP], #0x10
    MSR     SP_EL0, X29
    LDP     X28, X29, [SP], #0x10
    MSR     FPCR, X28
    MSR     FPSR, X29
    LDP     X28, X29, [SP], #0x10
    LDP     X26, X27, [SP], #0x10
    LDP     X24, X25, [SP], #0x10
    LDP     X22, X23, [SP], #0x10
    LDP     X20, X21, [SP], #0x10
    LDP     X18, X19, [SP], #0x10
    LDP     X16, X17, [SP], #0x10
    LDP     X14, X15, [SP], #0x10
    LDP     X12, X13, [SP], #0x10
    LDP     X10, X11, [SP], #0x10
    LDP     X8, X9, [SP], #0x10
    LDP     X6, X7, [SP], #0x10
    LDP     X4, X5, [SP], #0x10
    LDP     X2, X3, [SP], #0x10
    LDP     X0, X1, [SP], #0x10
    RESTORE_FPU SP
#ifdef RT_USING_SMART
    BEQ     arch_ret_to_user
#endif
    ERET
.endm

.macro SAVE_USER_CTX
    MRS     X1, SPSR_EL1
    AND     X1, X1, 0xf
    CMP     X1, XZR

    BNE     1f
    BL      lwp_uthread_ctx_save
    LDP     X0, X1, [SP]
1:
.endm

.macro RESTORE_USER_CTX, ctx
    LDR     X1, [\ctx, #CONTEXT_OFFSET_SPSR_EL1]
    AND     X1, X1, 0x1f
    CMP     X1, XZR

    BNE     1f
    BL      lwp_uthread_ctx_restore
1:
.endm

#ifdef RT_USING_SMP
#define rt_hw_interrupt_disable rt_hw_local_irq_disable
#define rt_hw_interrupt_enable rt_hw_local_irq_enable
#endif

.text

.global rt_hw_interrupt_is_disabled
rt_hw_interrupt_is_disabled:
    MRS     X0, DAIF
    TST     X0, #0xc0
    CSET    X0, NE
    RET

/*
 * rt_base_t rt_hw_interrupt_disable();
 */
.globl rt_hw_interrupt_disable
rt_hw_interrupt_disable:
    MRS     X0, DAIF
    AND     X0, X0, #0xc0
    CMP     X0, #0xc0
    /* branch if bits not both set(zero) */
    BNE     1f
    RET
1:
    MSR     DAIFSet, #3
    DSB     NSH
    ISB
    RET

/*
 * void rt_hw_interrupt_enable(rt_base_t level);
 */
.globl rt_hw_interrupt_enable
rt_hw_interrupt_enable:
    AND     X0, X0, #0xc0
    CMP     X0, #0xc0
    /* branch if one of the bits not set(zero) */
    BNE     1f
    RET
1:
    ISB
    DSB     NSH
    AND     X0, X0, #0xc0
    MRS     X1, DAIF
    BIC     X1, X1, #0xc0
    ORR     X0, X0, X1
    MSR     DAIF, X0
    RET

.text

#ifdef RT_USING_SMP

#else   /* !RT_USING_SMP */


#endif  /* RT_USING_SMP */

// -------------------------------------------------
