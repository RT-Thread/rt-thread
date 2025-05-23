/*
 * Copyright (c) 2006-2025, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2025-04-20     GuEe-GUI     The first version
 */

#ifndef __ISA_EXT_H__
#define __ISA_EXT_H__

#include <rtdef.h>

#define RISCV_ISA_EXT_I                 0
#define RISCV_ISA_EXT_M                 1
#define RISCV_ISA_EXT_A                 2
#define RISCV_ISA_EXT_F                 3
#define RISCV_ISA_EXT_D                 4
#define RISCV_ISA_EXT_Q                 5
#define RISCV_ISA_EXT_C                 6
#define RISCV_ISA_EXT_V                 7
#define RISCV_ISA_EXT_H                 8

#define RISCV_ISA_EXT_BASE              26

#define RISCV_ISA_EXT_SSCOFPMF          26
#define RISCV_ISA_EXT_SSTC              27
#define RISCV_ISA_EXT_SVINVAL           28
#define RISCV_ISA_EXT_SVPBMT            29
#define RISCV_ISA_EXT_ZBB               30
#define RISCV_ISA_EXT_ZICBOM            31
#define RISCV_ISA_EXT_ZIHINTPAUSE       32
#define RISCV_ISA_EXT_SVNAPOT           33
#define RISCV_ISA_EXT_ZICBOZ            34
#define RISCV_ISA_EXT_SMAIA             35
#define RISCV_ISA_EXT_SSAIA             36
#define RISCV_ISA_EXT_ZBA               37
#define RISCV_ISA_EXT_ZBS               38
#define RISCV_ISA_EXT_ZICNTR            39
#define RISCV_ISA_EXT_ZICSR             40
#define RISCV_ISA_EXT_ZIFENCEI          41
#define RISCV_ISA_EXT_ZIHPM             42
#define RISCV_ISA_EXT_SMSTATEEN         43
#define RISCV_ISA_EXT_ZICOND            44
#define RISCV_ISA_EXT_ZBC               45
#define RISCV_ISA_EXT_ZBKB              46
#define RISCV_ISA_EXT_ZBKC              47
#define RISCV_ISA_EXT_ZBKX              48
#define RISCV_ISA_EXT_ZKND              49
#define RISCV_ISA_EXT_ZKNE              50
#define RISCV_ISA_EXT_ZKNH              51
#define RISCV_ISA_EXT_ZKR               52
#define RISCV_ISA_EXT_ZKSED             53
#define RISCV_ISA_EXT_ZKSH              54
#define RISCV_ISA_EXT_ZKT               55
#define RISCV_ISA_EXT_ZVBB              56
#define RISCV_ISA_EXT_ZVBC              57
#define RISCV_ISA_EXT_ZVKB              58
#define RISCV_ISA_EXT_ZVKG              59
#define RISCV_ISA_EXT_ZVKNED            60
#define RISCV_ISA_EXT_ZVKNHA            61
#define RISCV_ISA_EXT_ZVKNHB            62
#define RISCV_ISA_EXT_ZVKSED            63
#define RISCV_ISA_EXT_ZVKSH             64
#define RISCV_ISA_EXT_ZVKT              65
#define RISCV_ISA_EXT_ZFH               66
#define RISCV_ISA_EXT_ZFHMIN            67
#define RISCV_ISA_EXT_ZIHINTNTL         68
#define RISCV_ISA_EXT_ZVFH              69
#define RISCV_ISA_EXT_ZVFHMIN           70
#define RISCV_ISA_EXT_ZFA               71
#define RISCV_ISA_EXT_ZTSO              72
#define RISCV_ISA_EXT_ZACAS             73
#define RISCV_ISA_EXT_XANDESPMU         74

#define RISCV_ISA_EXT_MAX               75
#define RISCV_ISA_EXT_INVALID           RT_UINT32_MAX

#ifdef ARCH_RISCV_M_MODE
#define RISCV_ISA_EXT_SxAIA				RISCV_ISA_EXT_SMAIA
#else
#define RISCV_ISA_EXT_SxAIA				RISCV_ISA_EXT_SSAIA
#endif

void riscv_isa_ext_set_raw(rt_uint32_t isa);
void riscv_isa_ext_clear_raw(rt_uint32_t isa);
rt_bool_t riscv_isa_ext_test_raw(rt_uint32_t isa);

#define riscv_isa_ext_set(isa)      	riscv_isa_ext_set_raw(RISCV_ISA_EXT_##isa)
#define riscv_isa_ext_clear(isa)    	riscv_isa_ext_clear_raw(RISCV_ISA_EXT_##isa)
#define riscv_isa_ext_test(isa)     	riscv_isa_ext_test_raw(RISCV_ISA_EXT_##isa)

#endif /* __ISA_EXT_H__ */
