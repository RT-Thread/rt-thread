/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Date           Author       Notes
 * 2018-10-06     ZhaoXiaowei  the first version (cpu_gcc.S)
 * 2021-05-18     Jesven       the first version (context_gcc.S)
 * 2024-01-06     Shell        Fix barrier on irq_disable/enable
 * 2024-01-18     Shell        fix implicit dependency of cpuid management
 * 2024-03-28     Shell        Move cpu codes from context_gcc.S
 */

#ifndef __ASSEMBLY__
#define __ASSEMBLY__
#endif

#include "rtconfig.h"
#include "asm-generic.h"
#include "asm-fpu.h"
#include "armv8.h"

#ifdef RT_USING_SMP
#define rt_hw_interrupt_disable rt_hw_local_irq_disable
#define rt_hw_interrupt_enable rt_hw_local_irq_enable
#endif /* RT_USING_SMP */

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
    msr     CONTEXTIDR_EL1, x0
    ret

/*
 *enable gtimer
 */
.globl rt_hw_gtimer_enable
rt_hw_gtimer_enable:
    mov     x0, #1
    msr     CNTP_CTL_EL0, x0
    ret

/*
 *set gtimer CNTP_TVAL_EL0 value
 */
.globl rt_hw_set_gtimer_val
rt_hw_set_gtimer_val:
    msr     CNTP_TVAL_EL0, x0
    ret

/*
 *get gtimer CNTP_TVAL_EL0 value
 */
.globl rt_hw_get_gtimer_val
rt_hw_get_gtimer_val:
    mrs     x0, CNTP_TVAL_EL0
    ret


.globl rt_hw_get_cntpct_val
rt_hw_get_cntpct_val:
    mrs     x0, CNTPCT_EL0
    ret

/*
 *get gtimer frq value
 */
.globl rt_hw_get_gtimer_frq
rt_hw_get_gtimer_frq:
    mrs     x0, CNTFRQ_EL0
    ret

.global rt_hw_interrupt_is_disabled
rt_hw_interrupt_is_disabled:
    mrs     x0, DAIF
    tst     x0, #0xc0
    cset    x0, NE
    ret

/*
 * rt_base_t rt_hw_interrupt_disable();
 */
.globl rt_hw_interrupt_disable
rt_hw_interrupt_disable:
    mrs     x0, DAIF
    and     x0, x0, #0xc0
    cmp     x0, #0xc0
    /* branch if bits not both set(zero) */
    bne     1f
    ret
1:
    msr     DAIFSet, #3
    dsb     nsh
    isb
    ret

/*
 * void rt_hw_interrupt_enable(rt_base_t level);
 */
.globl rt_hw_interrupt_enable
rt_hw_interrupt_enable:
    and     x0, x0, #0xc0
    cmp     x0, #0xc0
    /* branch if one of the bits not set(zero) */
    bne     1f
    ret
1:
    isb
    dsb     nsh
    and     x0, x0, #0xc0
    mrs     x1, DAIF
    bic     x1, x1, #0xc0
    orr     x0, x0, x1
    msr     DAIF, x0
    ret

.globl rt_hw_get_current_el
rt_hw_get_current_el:
    mrs     x0, CurrentEL
    cmp     x0, 0xc
    b.eq    3f
    cmp     x0, 0x8
    b.eq    2f
    cmp     x0, 0x4
    b.eq    1f

    ldr     x0, =0
    b       0f
3:
    ldr     x0, =3
    b       0f
2:
    ldr     x0, =2
    b       0f
1:
    ldr     x0, =1
    b       0f
0:
    ret


.globl rt_hw_set_current_vbar
rt_hw_set_current_vbar:
    mrs     x1, CurrentEL
    cmp     x1, 0xc
    b.eq    3f
    cmp     x1, 0x8
    b.eq    2f
    cmp     x1, 0x4
    b.eq    1f
    b       0f
3:
    msr     VBAR_EL3,x0
    b       0f
2:
    msr     VBAR_EL2,x0
    b       0f
1:
    msr     VBAR_EL1,x0
    b       0f
0:
    ret

.globl rt_hw_set_elx_env
rt_hw_set_elx_env:
    mrs     x1, CurrentEL
    cmp     x1, 0xc
    b.eq    3f
    cmp     x1, 0x8
    b.eq    2f
    cmp     x1, 0x4
    b.eq    1f
    b       0f
3:
    mrs     x0, SCR_EL3
    orr     x0, x0, #0xf             /* SCR_EL3.NS|IRQ|FIQ|EA */
    msr     SCR_EL3, x0
    b       0f
2:
    mrs     x0, HCR_EL2
    orr     x0, x0, #0x38
    msr     HCR_EL2, x0
    b       0f
1:
    b       0f
0:
    ret

.globl rt_cpu_vector_set_base
rt_cpu_vector_set_base:
    msr     VBAR_EL1, x0
    ret


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
