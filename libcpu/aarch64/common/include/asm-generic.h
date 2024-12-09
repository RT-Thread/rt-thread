/*
 * Copyright (c) 2006-2023 RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2023-03-12     WangXiaoyao  the first version
 */
#ifndef __ASM_GENERIC_H__
#define __ASM_GENERIC_H__

/* use to mark a start point where every task start from */
#define START_POINT(funcname)               \
    .global funcname;                       \
    .type funcname, %function;              \
    funcname:                               \
    .cfi_sections .debug_frame, .eh_frame;  \
    .cfi_startproc;                         \
    .cfi_undefined x30

#define START_POINT_END(name)   \
    .cfi_endproc;               \
    .size name, .-name;

#define TRACE_SYMBOL(name)

.macro NEVER_RETURN
#ifdef RT_USING_DEBUG
    b       .
#endif /* RT_USING_DEBUG */
.endm

.macro GET_THREAD_SELF, dst:req
#ifdef ARCH_USING_HW_THREAD_SELF
    mrs     x0, tpidr_el1
#else  /* !ARCH_USING_HW_THREAD_SELF */
    bl      rt_thread_self
#endif /* ARCH_USING_HW_THREAD_SELF */
    .if \dst != x0
    mov     dst, x0
    .endif
.endm

#endif /* __ASM_GENERIC_H__ */
