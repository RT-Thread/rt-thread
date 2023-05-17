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

#define START_POINT(funcname)               \
    .type funcname, %function;	            \
    .global funcname;                       \
    funcname:                               \
    .cfi_sections .debug_frame, .eh_frame;  \
    .cfi_startproc;                         \
    .cfi_undefined lr

#define START_POINT_END(name)   \
    .cfi_endproc;               \
    .size name, .-name;

#endif /* __ASM_GENERIC_H__ */
