/*
 * Copyright (c) 2006-2024, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2024-5-1       GuEe-GUI     first version
 */

#ifndef __FIRMWARE_SPACEMIT_H__
#define __FIRMWARE_SPACEMIT_H__

#ifdef __ASSEMBLY__
#include <asm-generic.h>

.macro SPACEMIT_FIRMWARE_DEFINE name
    .align RISCV_SZPTR
firmware_\name:
    .ascii "\name" "\0"
firmware_\name\()_start:
    .incbin "\name"
firmware_\name\()_end:
.endm

.macro SPACEMIT_FIRMWARE_REF name
    RISCV_PTR firmware_\name
    RISCV_PTR firmware_\name\()_start
    RISCV_PTR firmware_\name\()_end
.endm

.macro SPACEMIT_FIRMWARE_START
    .align RISCV_SZPTR
    .globl spacemit_firmwares_start
spacemit_firmwares_start:
.endm

.macro SPACEMIT_FIRMWARE_END
    .globl spacemit_firmwares_end
spacemit_firmwares_end:
.endm
#else
#include <rtdef.h>

rt_bool_t spacemit_firmware_find(const char *name, rt_ubase_t *out_base, rt_size_t *out_size);
rt_err_t spacemit_firmware_load_elf(const char *name, rt_ubase_t phy_addr);

#endif /* __ASSEMBLY__ */

#endif /* __FIRMWARE_SPACEMIT_H__ */
