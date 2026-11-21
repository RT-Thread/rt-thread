/*
 * Copyright (c) 2006-2026, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 */

    .section .rodata.dtb, "a"
    .balign 8
    .global rt_hw_builtin_fdt
    .global rt_hw_builtin_fdt_end
    .type rt_hw_builtin_fdt, %object
rt_hw_builtin_fdt:
    .incbin "board/board.dtb"
rt_hw_builtin_fdt_end:
    .size rt_hw_builtin_fdt, . - rt_hw_builtin_fdt
