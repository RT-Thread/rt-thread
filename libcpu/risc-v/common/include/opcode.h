/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-09     Shell        Add portable asm support
 * 2025-04-26     GuEe-GUI     Follow the specific and vendor
 */

#ifndef __OPCODE_H__
#define __OPCODE_H__

#include <rtcompiler.h>

#include <asm-generic.h>
#ifdef __HAS_OPCODE_VENDOR__
#include <opcode_vendor.h>
#endif

/**
 * @brief binary opcode pseudo operations
 * Used to bypass toolchain restriction on extension ISA
 *
 */

/**
 * @brief RISC-V instruction formats
 */

#define OPCODE_MISC_MEM     15
#define OPCODE_SYSTEM       115

#ifndef __OPC_INSN_FORMAT_R
/**
 * R type: .insn r opcode6, func3, func7, rd, rs1, rs2
 *
 * +-------+-----+-----+-------+----+---------+
 * | func7 | rs2 | rs1 | func3 | rd | opcode6 |
 * +-------+-----+-----+-------+----+---------+
 * 31      25    20    15      12   7        0
 */
#define __OPC_INSN_FORMAT_R(opcode, func3, func7, rd, rs1, rs2) \
    ".insn r "RT_STRINGIFY(opcode)","RT_STRINGIFY(func3)","RT_STRINGIFY(func7)","RT_STRINGIFY(rd)","RT_STRINGIFY(rs1)","RT_STRINGIFY(rs2)"\n\t"
#endif /* !__OPC_INSN_FORMAT_R */

#ifndef __OPC_INSN_FORMAT_I
/**
 * I type: .insn i opcode6, func3, rd, rs1, simm12
 *
 * +--------+-----+-------+----+---------+
 * | simm12 | rs1 | func3 | rd | opcode6 |
 * +--------+-----+-------+----+---------+
 * 31      20     15      12   7        0
 */
#define __OPC_INSN_FORMAT_I(opcode, func3, rd, rs1, simm12) \
    ".insn i "RT_STRINGIFY(opcode)","RT_STRINGIFY(func3)","RT_STRINGIFY(rd)","RT_STRINGIFY(rs1)","RT_STRINGIFY(simm12)"\n\t"
#endif /* !__OPC_INSN_FORMAT_I */

#ifndef OPC_CBO_INVAL
#define OPC_CBO_INVAL(base)     __OPC_INSN_FORMAT_I(OPCODE_MISC_MEM, 2, x0, base, 0)
#endif

#ifndef OPC_CBO_CLEAN
#define OPC_CBO_CLEAN(base)     __OPC_INSN_FORMAT_I(OPCODE_MISC_MEM, 2, x0, base, 1)
#endif

#ifndef OPC_FENCE_I
#ifdef ARCH_TOOLCHAIN_HAS_ZIFENCEI_ISA
#define OPC_FENCE_I             __ASM_STR(fence.i)
#else /* !ARCH_TOOLCHAIN_HAS_ZIFENCEI_ISA */
#define OPC_FENCE_I             __ASM_STR(.long 0x0000100f)
#endif /* ARCH_TOOLCHAIN_HAS_ZIFENCEI_ISA */
#endif /* !OPC_FENCE_I */

#ifndef OPC_PAUSE_I
#ifdef ARCH_TOOLCHAIN_HAS_ZIHINTPAUSE
#define OPC_PAUSE_I             __ASM_STR(pause)
#else /* !ARCH_TOOLCHAIN_HAS_ZIHINTPAUSE */
#define OPC_PAUSE_I             __ASM_STR(.4byte 0x0100000f)
#endif /* ARCH_TOOLCHAIN_HAS_ZIHINTPAUSE */
#endif /* !OPC_PAUSE_I */

#endif /* __OPCODE_H__ */