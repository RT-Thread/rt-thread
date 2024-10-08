/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-09     Shell        Add portable asm support
 */
#ifndef __OPCODE_H__
#define __OPCODE_H__

/**
 * @brief binary opcode pseudo operations
 * Used to bypass toolchain restriction on extension ISA
 *
 */

/**
 * @brief RISC-V instruction formats
 */

/**
 * R type: .insn r opcode6, func3, func7, rd, rs1, rs2
 *
 * +-------+-----+-----+-------+----+---------+
 * | func7 | rs2 | rs1 | func3 | rd | opcode6 |
 * +-------+-----+-----+-------+----+---------+
 * 31      25    20    15      12   7        0
 */
#define __OPC_INSN_FORMAT_R(opcode, func3, func7, rd, rs1, rs2) \
    ".insn r "RT_STRINGIFY(opcode)","RT_STRINGIFY(func3)","RT_STRINGIFY(func7)","RT_STRINGIFY(rd)","RT_STRINGIFY(rs1)","RT_STRINGIFY(rs2)

#ifdef _TOOLCHAIN_SUPP_ZIFENCEI_ISA_
#define OPC_FENCE_I             "fence.i"
#else /* !_TOOLCHAIN_SUPP_ZIFENCEI_ISA_ */
#define OPC_FENCE_I             ".long 0x0000100F"
#endif /* _TOOLCHAIN_SUPP_ZIFENCEI_ISA_ */

#endif /* __OPCODE_H__ */