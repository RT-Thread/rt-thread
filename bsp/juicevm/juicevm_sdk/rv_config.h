/*
 * Copyright (c) 2006-2021, JuiceVm Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021/04/22     Juice        the first version
 */


#ifndef __RV_CONFIG_H__
#define __RV_CONFIG_H__

#define RV64I_SUPPORT_ENBALE
#define RV64_MMU_ENBALE            1

#define RV_ENDLESS_LOOP_CHECK_ENBALE            1
#if defined(RV_ENDLESS_LOOP_CHECK_ENBALE) && RV_ENDLESS_LOOP_CHECK_ENBALE == 1
    #define RV_ENDLESS_LOOP_CHECK_BUF_SIZE          (30)
    #define RV_ENDLESS_LOOP_CHECK_EXIT_CNT          (3)
    #define RV_ENDLESS_LOOP_CHECK_MD5_HASH          1
#endif

// #define RISCV_ANGEL_ONLY
#define Machine_Mode_SUPPORT
#define Supervisor_Mode_SUPPORT
// #define User_Mode_SUPPORT
// #define Hypervisor_Mode_SUPPORT

#define ATOMIC_Module_SUPPORT

#define RV_CPU_CSR_DEF_Vendor_ID    0
#define RV_CPU_CSR_DEF_March_ID     0
#define RV_CPU_CSR_DEF_Mimp_ID      0
#define RV_CPU_CSR_DEF_Mhart_ID     0

#define JUICE_VM_LOG_MAX_NUM        (600)

#define JUICE_VM_INC_CHANGELOG      0

#define RAM_SIZE_KB                 (1024)
#define RAM_SIZE_MB                 (1024*RAM_SIZE_KB)

#define RV_CPU_SIM_RAM_START_ADDR   (0x80000000)
#define RV_CPU_SIM_RAM_SIZE         (300 * RAM_SIZE_MB)

#define RV_CPU_SIM_CAUSETABLE_MAX_NUM    100//MXLEN-1 bit

#define RV_CPU_SIM_PERDEV_NUM       50
#define rv_peripheral_device_add_check_dev    1

// | MXLEN-1          MXLEN-2 | MXLEN-3       26| 25                     0 |
// |      MXL[1:0](WARL)      |       WLRL      | Extensions[25:0] (WARL)  |
// |     2                    |     MXLEN-28    |           26             |
//                  Figure 3.1: Machine ISA register (misa).



// Bit | Character | Description
// 0   |    A      |   Atomic extension
// 1   |    B      |   Tentatively reserved for Bit-Manipulation extension
// 2   |    C      |   Compressed extension
// 3   |    D      |   Double-precision floating-point extension
// 4   |    E      |   RV32E base ISA
// 5   |    F      |   Single-precision floating-point extension
// 6   |    G      |   Reserved
// 7   |    H      |   Hypervisor extension
// 8   |    I      |   RV32I/64I/128I base ISA
// 9   |    J      |   Tentatively reserved for Dynamically Translated Languages extension
// 10  |    K      |   Reserved
// 11  |    L      |   Tentatively reserved for Decimal Floating-Point extension
// 12  |    M      |   Integer Multiply/Divide extension
// 13  |    N      |   User-level interrupts supported
// 14  |    O      |   Reserved
// 15  |    P      |   Tentatively reserved for Packed-SIMD extension
// 16  |    Q      |   Quad-precision floating-point extension
// 17  |    R      |   Reserved
// 18  |    S      |   Supervisor mode implemented
// 19  |    T      |   Tentatively reserved for Transactional Memory extension
// 20  |    U      |   User mode implemented
// 21  |    V      |   Tentatively reserved for Vector extension
// 22  |    W      |   Reserved
// 23  |    X      |   Non-standard extensions present
// 24  |    Y      |   Reserved
// 25  |    Z      |   Reserved
#define RV_MISA_ATOMIC_EXT         (1<<0)
#define RV_MISA_INTEGER_EXT        (1<<8)
#define RV_MISA_UMODE_INT_EXT      (1<<13)
#define RV_MISA_SMODE_IMP_EXT      (1<<18)
#define RV_MISA_UMODE_IMP_EXT      (1<<20)

// | MXL |  XLEN  |
// | 1   |   32   |
// | 2   |   64   |
// | 3   |   128  |
#define RV_MISA_XLEN_32            (1<<(32-2))
#define RV_MISA_XLEN_64            (uint64_t)((uint64_t)(2)<<(64-2))
// #define RV_MISA_XLEN_128           ((uint128_t)(3)<<(128-2))



#define RV_MISA_CSR_REGISTER       ((uint64_t)(RV_MISA_XLEN_64 | RV_MISA_ATOMIC_EXT | RV_MISA_INTEGER_EXT /*| RV_MISA_UMODE_INT_EXT*/ | RV_MISA_SMODE_IMP_EXT /*| RV_MISA_UMODE_IMP_EXT*/))


#endif // __RV_CONFIG_H__
