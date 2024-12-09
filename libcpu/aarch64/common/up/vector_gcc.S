/*
 * Copyright (c) 2006-2020, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-03-28     Shell        Move vector handling codes from context_gcc.S
 */

#ifndef __ASSEMBLY__
#define __ASSEMBLY__
#endif

#include "../include/vector_gcc.h"
#include "context_gcc.h"

#include <rtconfig.h>
#include <asm-generic.h>
#include <asm-fpu.h>
#include <armv8.h>

.section .text

vector_fiq:
    .align  8
    .globl vector_fiq

    SAVE_IRQ_CONTEXT
    bl      rt_hw_trap_fiq

    b       rt_hw_irq_exit

.globl      rt_thread_switch_interrupt_flag
.globl      rt_hw_context_switch_interrupt_do

/**
 * void rt_hw_vector_irq_sched(void *eframe)
 * @brief do IRQ scheduling
 */
rt_hw_vector_irq_sched:
    .globl rt_hw_vector_irq_sched
    .align  8

    /**
     * if rt_thread_switch_interrupt_flag set, jump to
     * rt_hw_context_switch_interrupt_do and don't return
     */
    ldr     x1, =rt_thread_switch_interrupt_flag
    ldr     x2, [x1]
    cmp     x2, #1
    bne     1f

    /* clear flag */
    mov     x2,  #0
    str     x2,  [x1]

    bl      rt_hw_context_switch_interrupt_do

1:
    b       rt_hw_irq_exit
