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

    .align  8
    .globl vector_fiq
vector_fiq:
    SAVE_IRQ_CONTEXT
    bl      rt_hw_trap_fiq
    RESTORE_IRQ_CONTEXT

.globl      rt_interrupt_enter
.globl      rt_interrupt_leave
.globl      rt_thread_switch_interrupt_flag
.globl      rt_interrupt_from_thread
.globl      rt_interrupt_to_thread
.globl      rt_hw_context_switch_interrupt_do

    .align  8
    .globl vector_irq
vector_irq:
    SAVE_IRQ_CONTEXT

    bl      rt_interrupt_enter
    bl      rt_hw_trap_irq
    bl      rt_interrupt_leave

    /**
     * if rt_thread_switch_interrupt_flag set, jump to
     * rt_hw_context_switch_interrupt_do and don't return
     */
    ldr     x1, =rt_thread_switch_interrupt_flag
    ldr     x2, [x1]
    cmp     x2, #1
    b.ne    vector_irq_exit

    mov     x2,  #0         // clear flag
    str     x2,  [x1]

    bl      rt_hw_context_switch_interrupt_do

vector_irq_exit:
    RESTORE_IRQ_CONTEXT_WITHOUT_MMU_SWITCH
