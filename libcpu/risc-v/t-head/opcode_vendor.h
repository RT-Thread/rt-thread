/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-11-09     WangXiaoyao  Add portable asm support
 * 2022-03-16     WangXiaoyao  Porting to xtheadsync & xtheadcmo ISA extension
 */

#ifndef __VENDOR_OPCODE_H__
#define __VENDOR_OPCODE_H__

/**
 * @brief binary opcode pseudo operations
 * Used to bypass toolchain restriction on extension ISA
 *
 * WARNING: Xuantie ISAs are not compatible to each other in opcode.
 * It's painful to port this file, and should be really careful.
 */

/**
 * @brief RISC-V instruction formats
 */

/**
 * @brief Xuantie T-HEAD extension ISA format
 * Compatible to Xuantie C906R2S1 user manual v06 and C908 user manual v03
 */
#define __OPC_INSN_FORMAT_CACHE(func7, rs2, rs1) \
    __OPC_INSN_FORMAT_R(0x0b, 0x0, func7, x0, rs1, rs2)

#ifdef ARCH_TOOLCHAIN_SUPP_XTHEADE_ISA
#define OPC_SYNC                "sync"
#define OPC_SYNC_S              "sync.s"
#define OPC_SYNC_I              "sync.i"
#define OPC_SYNC_IS             "sync.is"

#define OPC_DCACHE_CALL         "dcache.call"
#define OPC_DCACHE_IALL         "dcache.iall"
#define OPC_DCACHE_CIALL        "dcache.ciall"
#define OPC_DCACHE_CVAL1(rs1)   "dcache.cval1 "_TOSTR(rs1)

#define OPC_ICACHE_IALL         "icache.iall"

#define OPC_DCACHE_CVA(rs1)     "dcache.cva "RT_STRINGIFY(rs1)
#define OPC_DCACHE_IVA(rs1)     "dcache.iva "RT_STRINGIFY(rs1)
#define OPC_DCACHE_CIVA(rs1)    "dcache.civa "RT_STRINGIFY(rs1)

#define OPC_ICACHE_IVA(rs1)     "icache.iva "RT_STRINGIFY(rs1)
#else /* !ARCH_TOOLCHAIN_NOT_SUPP_THEAD_ISA */

#define OPC_SYNC                ".long 0x0180000B"
#define OPC_SYNC_S              ".long 0x0190000B"
#define OPC_SYNC_I              ".long 0x01A0000B"
#define OPC_SYNC_IS             ".long 0x01B0000B"

#define OPC_DCACHE_CALL         ".long 0x0010000B"
#define OPC_DCACHE_IALL         ".long 0x0020000B"
#define OPC_DCACHE_CIALL        ".long 0x0030000B"
#define OPC_DCACHE_CVAL1(rs1)   __OPC_INSN_FORMAT_CACHE(0x1, x4, rs1)

#define OPC_ICACHE_IALL         ".long 0x0100000B"

#define OPC_DCACHE_CVA(rs1)     __OPC_INSN_FORMAT_CACHE(0x1, x5, rs1)
#define OPC_DCACHE_IVA(rs1)     __OPC_INSN_FORMAT_CACHE(0x1, x6, rs1)
#define OPC_DCACHE_CIVA(rs1)    __OPC_INSN_FORMAT_CACHE(0x1, x7, rs1)

#define OPC_ICACHE_IVA(rs1)     __OPC_INSN_FORMAT_CACHE(0x1, x16, rs1)
#endif /* ARCH_TOOLCHAIN_NOT_SUPP_THEAD_ISA */

/**
 * @brief RISC-V zifencei ISA
 */
#ifdef ARCH_TOOLCHAIN_SUPP_ZIFENCEI_ISA
#define OPC_FENCE_I             "fence.i"
#else /* !ARCH_TOOLCHAIN_SUPP_ZIFENCEI_ISA */
#define OPC_FENCE_I             ".long 0x0000100F"
#endif /* ARCH_TOOLCHAIN_SUPP_ZIFENCEI_ISA */

#endif /* __VENDOR_OPCODE_H__ */
