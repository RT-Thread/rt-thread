/*
 * Copyright (C) 2017 XRADIO TECHNOLOGY CO., LTD. All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *    1. Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *    2. Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the
 *       distribution.
 *    3. Neither the name of XRADIO TECHNOLOGY CO., LTD. nor the names of
 *       its contributors may be used to endorse or promote products derived
 *       from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef _SYS_INTERRUPT_H_
#define _SYS_INTERRUPT_H_

#include "compiler.h"

#if defined(__CC_ARM)
/* ARM Compiler */

/*
 * CPU interrupt mask handling.
 */
#define IRQMASK_REG_NAME_R primask
#define IRQMASK_REG_NAME_W primask

/*
 * Save the current interrupt enable state & disable IRQs
 */
static __always_inline unsigned long arch_irq_save(void)
{
    unsigned long flags;

    __asm {
        mrs flags, IRQMASK_REG_NAME_R
        cpsid   i
    }
    return flags;
}

/*
 * restore saved IRQ state
 */
static __always_inline void arch_irq_restore(unsigned long flags)
{
    __asm { msr IRQMASK_REG_NAME_W, flags }
}

/*
 * Enable IRQs
 */
#define arch_irq_enable()   __enable_irq()

/*
 * Disable IRQs
 */
#define arch_irq_disable()  __disable_irq()

/*
 * Enable FIQs
 */
#define arch_fiq_enable()   __enable_fiq()

/*
 * Disable FIQs
 */
#define arch_fiq_disable()  __disable_fiq()

#elif defined(__GNUC__)
/* GNU Compiler */

#ifdef __CONFIG_OS_RTTHREAD

/*
 * Save the current interrupt enable state & disable IRQs
 */
#define arch_irq_save(void) rt_hw_interrupt_disable()

/*
 * restore saved IRQ state
 */
#define arch_irq_restore(flags) rt_hw_interrupt_enable(flags)

/*
 * Enable IRQs
 */
#define arch_irq_enable()   rt_hw_interrupt_enable(__irq_level)

/*
 * Disable IRQs
 */
#define arch_irq_disable()  rt_base_t __irq_level = rt_hw_interrupt_disable()

#else /* __CONFIG_OS_RTTHREAD */

/*
 * CPU interrupt mask handling.
 */
#define IRQMASK_REG_NAME_R "primask"
#define IRQMASK_REG_NAME_W "primask"

/*
 * Save the current interrupt enable state & disable IRQs
 */
static __always_inline unsigned long arch_irq_save(void)
{
    unsigned long flags;

    __asm volatile(
        "mrs    %0, " IRQMASK_REG_NAME_R "\n"
        "cpsid  i"
        : "=r" (flags) : : "memory", "cc");
    return flags;
}

/*
 * restore saved IRQ state
 */
static __always_inline void arch_irq_restore(unsigned long flags)
{
    __asm volatile(
        "msr    " IRQMASK_REG_NAME_W ", %0"
        :
        : "r" (flags)
        : "memory", "cc");
}

/*
 * Save the current interrupt enable state.
 */
static __always_inline unsigned long arch_irq_get_flags(void)
{
    unsigned long flags;

    __asm volatile(
        "mrs    %0, " IRQMASK_REG_NAME_R "\n"
        : "=r" (flags) : : "memory", "cc");
    return flags;

}

/*
 * Enable IRQs
 */
#define arch_irq_enable()   __asm volatile("cpsie i" : : : "memory", "cc")

/*
 * Disable IRQs
 */
#define arch_irq_disable()  __asm volatile("cpsid i" : : : "memory", "cc")

/*
 * Enable FIQs
 */
#define arch_fiq_enable()   __asm volatile("cpsie f" : : : "memory", "cc")

/*
 * Disable FIQs
 */
#define arch_fiq_disable()  __asm volatile("cpsid f" : : : "memory", "cc")

#endif /* __CONFIG_OS_RTTHREAD */

#else
#error "Compiler not supported."
#endif

#endif /* _SYS_INTERRUPT_H_ */
