/*
 * Copyright (c) 2026, Linumiz
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2026-11-06     Parthiban    first version
 */

#ifndef __RH850_ASM_H__
#define __RH850_ASM_H__

#include "rh850_sysreg.h"

/* GCC v850 puts __USER_LABEL_PREFIX__ ("_") in front of C symbols */
#define RH850_CAT2(a, b) a##b
#define RH850_CAT(a, b)  RH850_CAT2(a, b)
#define C_SYM(s)         RH850_CAT(__USER_LABEL_PREFIX__, s)

/* clang-format off */
#ifdef __ASSEMBLER__
    .macro rh850_stsr id, sel, reg
    stsr    \id, \reg, \sel
    .endm
#endif
/* clang-format on */

#endif
