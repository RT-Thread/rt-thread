/*
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hardware/platform_defs.h"
#include "pico/config.h"

#define WRAPPER_FUNC_NAME(x) __wrap_##x
#define SECTION_NAME(x) .text.##x
#define RAM_SECTION_NAME(x) .time_critical.##x
#define rom_table_code(c1, c2) ((c1) | ((c2) << 8))

// do not put align in here as it is used mid function sometimes
.macro regular_func x
.global \x
.type \x,%function
.thumb_func
\x:
.endm

.macro regular_func_with_section x
.section .text.\x
regular_func \x
.endm

// do not put align in here as it is used mid function sometimes
.macro wrapper_func x
regular_func WRAPPER_FUNC_NAME(\x)
.endm

.macro __pre_init func, priority_string
.section .preinit_array.\priority_string
.align 2
.word \func
.endm

