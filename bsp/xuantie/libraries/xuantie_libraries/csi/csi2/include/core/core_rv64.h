 /*
 * Copyright (C) 2017-2024 Alibaba Group Holding Limited
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


/******************************************************************************
 * @file     core_rv64.h
 * @brief    CSI RV32 Core Peripheral Access Layer Header File
 * @version  V1.0
 * @date     01. Sep 2018
 ******************************************************************************/

#ifndef __CORE_RV64_H_GENERIC
#define __CORE_RV64_H_GENERIC

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *                 CSI definitions
 ******************************************************************************/
/**
  \ingroup RV32
  @{
 */

#ifndef __RV64
#define __RV64                (0x01U)
#endif

/** __FPU_USED indicates whether an FPU is used or not.
    This core does not support an FPU at all
*/
#define __FPU_USED       0U

#if defined ( __GNUC__ )
#if defined (__VFP_FP__) && !defined(__SOFTFP__)
#error "Compiler generates FPU instructions for a device without an FPU (check __FPU_PRESENT)"
#endif
#endif

#if defined(CONFIG_PLIC_BASE)
#ifndef CORET_BASE
#define CORET_BASE                 (CONFIG_PLIC_BASE + 0x4000000UL)               /*!< CORET Base Address */
#endif
#define PLIC                       ((PLIC_Type *)CONFIG_PLIC_BASE)
#else
#error "CONFIG_PLIC_BASE is not defined!"
#endif /* end CONFIG_PLIC_BASE */

#ifdef __cplusplus
}
#endif

#endif /* __CORE_RV32_H_GENERIC */

#ifndef __CSI_GENERIC

#ifndef __CORE_RV32_H_DEPENDANT
#define __CORE_RV32_H_DEPENDANT

#ifdef __cplusplus
extern "C" {
#endif

/* check device defines and use defaults */
#ifndef __RV64_REV
#define __RV64_REV               0x0000U
#endif

#ifndef __VIC_PRIO_BITS
#define __VIC_PRIO_BITS           2U
#endif

#ifndef __Vendor_SysTickConfig
#define __Vendor_SysTickConfig    1U
#endif

#ifndef __MPU_PRESENT
#define __MPU_PRESENT             1U
#endif

#ifndef __ICACHE_PRESENT
#define __ICACHE_PRESENT          1U
#endif

#ifndef __DCACHE_PRESENT
#define __DCACHE_PRESENT          1U
#endif


#ifndef __L2CACHE_PRESENT
#define __L2CACHE_PRESENT          1U
#endif

#include <core/csi_rv64_gcc.h>

/* IO definitions (access restrictions to peripheral registers) */
/**
    \defgroup CSI_glob_defs CSI Global Defines

    <strong>IO Type Qualifiers</strong> are used
    \li to specify the access to peripheral variables.
    \li for automatic generation of peripheral register debug information.
*/
#ifdef __cplusplus
#define     __I      volatile             /*!< Defines 'read only' permissions */
#else
#define     __I      volatile const       /*!< Defines 'read only' permissions */
#endif
#define     __O      volatile             /*!< Defines 'write only' permissions */
#define     __IO     volatile             /*!< Defines 'read / write' permissions */

/* following defines should be used for structure members */
#define     __IM     volatile const       /*! Defines 'read only' structure member permissions */
#define     __OM     volatile             /*! Defines 'write only' structure member permissions */
#define     __IOM    volatile             /*! Defines 'read / write' structure member permissions */

/*@} end of group C9xx/R9xx */

/*******************************************************************************
 *                 Register Abstraction
  Core Register contain:
  - Core Register
  - Core CLINT Register
 ******************************************************************************/
/**
  \defgroup CSI_core_register Defines and Type Definitions
  \brief Type definitions and defines for CK80X processor based devices.
*/

/**
  \ingroup    CSI_core_register
  \defgroup   CSI_CORE  Status and Control Registers
  \brief      Core Register type definitions.
  @{
 */

#if CONFIG_INTC_CLIC_PLIC
/**
  \brief Access to the structure of a CLIC vector interrupt controller.
 */
typedef struct {
    __IOM uint8_t IP;           /*!< Offset: 0x000 (R/W)  Interrupt set pending register */
    __IOM uint8_t IE;           /*!< Offset: 0x004 (R/W)  Interrupt set enable register */
    __IOM uint8_t ATTR;         /*!< Offset: 0x008 (R/W)  Interrupt set attribute register */
    __IOM uint8_t CTL;          /*!< Offset: 0x00C (R/W)  Interrupt control register */
} CLIC_INT_Control;

typedef struct {
    __IOM uint32_t CLICCFG:8;                 /*!< Offset: 0x000 (R/W)  CLIC configure register */
    __IM  uint32_t CLICINFO;
    __IOM uint32_t MINTTHRESH;
    uint32_t RESERVED[1021];
    CLIC_INT_Control CLICINT[4096];
} CLIC_Type;

#define CLIC_INFO_CLICINTCTLBITS_Pos           21U
#define CLIC_INFO_CLICINTCTLBITS_Msk           (0xFUL << CLIC_INFO_CLICINTCTLBITS_Pos)

#define CLIC_INTIP_IP_Pos                      0U                                    /*!< CLIC INTIP: IP Position */
#define CLIC_INTIP_IP_Msk                      (0x1UL << CLIC_INTIP_IP_Pos)          /*!< CLIC INTIP: IP Mask */

#define CLIC_INTIE_IE_Pos                      0U                                    /*!< CLIC INTIE: IE Position */
#define CLIC_INTIE_IE_Msk                      (0x1UL << CLIC_INTIE_IE_Pos)          /*!< CLIC INTIE: IE Mask */

#define CLIC_INTIE_T_Pos                       7U                                    /*!< CLIC INTIE: T Position */
#define CLIC_INTIE_T_Msk                       (0x1UL << CLIC_INTIE_T_Pos)           /*!< CLIC INTIE: T Mask */

#define CLIC_INTATTR_TRIG_Pos                  1U                                    /*!< CLIC INTATTR: TRIG Position */
#define CLIC_INTATTR_TRIG_Msk                  (0x3UL << CLIC_INTATTR_TRIG_Pos)      /*!< CLIC INTATTR: TRIG Mask */

#define CLIC_INTATTR_SHV_Pos                   0U                                    /*!< CLIC INTATTR: SHV Position */
#define CLIC_INTATTR_SHV_Msk                   (0x1UL << CLIC_INTATTR_SHV_Pos)       /*!< CLIC INTATTR: SHV Mask */

#define CLIC_INTCFG_NVBIT_Pos                  5U                                    /*!< CLIC INTCFG: NVBIT Position */
#define CLIC_INTCFG_NVBIT_Msk                  (0x1UL << CLIC_INTCFG_NVBIT_Pos)      /*!< CLIC INTCFG: NVBIT Mask */

#define CLIC_INTCFG_PRIO_Pos                   5U                                    /*!< CLIC INTCFG: INTCFG Position */
#define CLIC_INTCFG_PRIO_Msk                   (0x7UL << CLIC_INTCFG_PRIO_Pos)       /*!< CLIC INTCFG: INTCFG Mask */

#define CLIC_CLICCFG_NVBIT_Pos                 0U                                    /*!< CLIC CLICCFG: NVBIT Position */
#define CLIC_CLICCFG_NVBIT_Msk                 (0x1UL << CLIC_CLICCFG_NVBIT_Pos)     /*!< CLIC CLICCFG: NVBIT Mask */

#define CLIC_CLICCFG_NLBIT_Pos                 1U                                    /*!< CLIC CLICCFG: NLBIT Position */
#define CLIC_CLICCFG_NLBIT_Msk                 (0xFUL << CLIC_CLICCFG_NLBIT_Pos)     /*!< CLIC CLICCFG: NLBIT Mask */

#define CLIC_CLICCFG_NMBIT_Pos                 5U                                    /*!< CLIC CLICCFG: NMBIT Position */
#define CLIC_CLICCFG_NMBIT_Msk                 (0x3UL << CLIC_CLICCFG_NMBIT_Pos)     /*!< CLIC CLICCFG: NMBIT Mask */

#if defined(CONFIG_CLIC_BASE)
#define CLIC                       ((CLIC_Type *)CONFIG_CLIC_BASE)       /*!< CLIC configuration struct */
#else
#error "CONFIG_CLIC_BASE is not defined!"
#endif /* end CONFIG_CLIC_BASE */

#endif /* CONFIG_INTC_CLIC_PLIC */


/**
  \brief Access to the structure of a PLIC vector interrupt controller.
 */

typedef struct {
    uint32_t RESERVED0;                 /*!< Offset: 0x000 (R/W)  CLINT configure register */
    __IOM uint32_t PLIC_PRIO[1023];
    __IOM uint32_t PLIC_IP[32];
    uint32_t RESERVED1[3972 / 4 - 1];
    __IOM uint32_t PLIC_H0_MIE[32];
    __IOM uint32_t PLIC_H0_SIE[32];
    __IOM uint32_t PLIC_H1_MIE[32];
    __IOM uint32_t PLIC_H1_SIE[32];
    __IOM uint32_t PLIC_H2_MIE[32];
    __IOM uint32_t PLIC_H2_SIE[32];
    __IOM uint32_t PLIC_H3_MIE[32];
    __IOM uint32_t PLIC_H3_SIE[32];
    __IOM uint32_t PLIC_H4_MIE[32];
    __IOM uint32_t PLIC_H4_SIE[32];
    __IOM uint32_t PLIC_H5_MIE[32];
    __IOM uint32_t PLIC_H5_SIE[32];
    __IOM uint32_t PLIC_H6_MIE[32];
    __IOM uint32_t PLIC_H6_SIE[32];
    __IOM uint32_t PLIC_H7_MIE[32];
    __IOM uint32_t PLIC_H7_SIE[32];

    uint32_t RESERVED2[(0x01FFFFC - 0x00027FC) / 4 - 1];
    __IOM uint32_t PLIC_PER;
    __IOM uint32_t PLIC_H0_MTH;
    __IOM uint32_t PLIC_H0_MCLAIM;
    uint32_t RESERVED3[0xFFC / 4 - 1];
    __IOM uint32_t PLIC_H0_STH;
    __IOM uint32_t PLIC_H0_SCLAIM;
    uint32_t RESERVED4[0xFFC / 4 - 1];

    __IOM uint32_t PLIC_H1_MTH;
    __IOM uint32_t PLIC_H1_MCLAIM;
    uint32_t RESERVED5[0xFFC / 4 - 1];
    __IOM uint32_t PLIC_H1_STH;
    __IOM uint32_t PLIC_H1_SCLAIM;
    uint32_t RESERVED6[0xFFC / 4 - 1];

    __IOM uint32_t PLIC_H2_MTH;
    __IOM uint32_t PLIC_H2_MCLAIM;
    uint32_t RESERVED7[0xFFC / 4 - 1];
    __IOM uint32_t PLIC_H2_STH;
    __IOM uint32_t PLIC_H2_SCLAIM;
    uint32_t RESERVED8[0xFFC / 4 - 1];

    __IOM uint32_t PLIC_H3_MTH;
    __IOM uint32_t PLIC_H3_MCLAIM;
    uint32_t RESERVED9[0xFFC / 4 - 1];
    __IOM uint32_t PLIC_H3_STH;
    __IOM uint32_t PLIC_H3_SCLAIM;
    uint32_t RESERVED10[0xFFC / 4 - 1];

    __IOM uint32_t PLIC_H4_MTH;
    __IOM uint32_t PLIC_H4_MCLAIM;
    uint32_t RESERVED11[0xFFC / 4 - 1];
    __IOM uint32_t PLIC_H4_STH;
    __IOM uint32_t PLIC_H4_SCLAIM;
    uint32_t RESERVED12[0xFFC / 4 - 1];

    __IOM uint32_t PLIC_H5_MTH;
    __IOM uint32_t PLIC_H5_MCLAIM;
    uint32_t RESERVED13[0xFFC / 4 - 1];
    __IOM uint32_t PLIC_H5_STH;
    __IOM uint32_t PLIC_H5_SCLAIM;
    uint32_t RESERVED14[0xFFC / 4 - 1];

    __IOM uint32_t PLIC_H6_MTH;
    __IOM uint32_t PLIC_H6_MCLAIM;
    uint32_t RESERVED15[0xFFC / 4 - 1];
    __IOM uint32_t PLIC_H6_STH;
    __IOM uint32_t PLIC_H6_SCLAIM;
    uint32_t RESERVED16[0xFFC / 4 - 1];

    __IOM uint32_t PLIC_H7_MTH;
    __IOM uint32_t PLIC_H7_MCLAIM;
    uint32_t RESERVED17[0xFFC / 4 - 1];
    __IOM uint32_t PLIC_H7_STH;
    __IOM uint32_t PLIC_H7_SCLAIM;
    uint32_t RESERVED18[0xFFC / 4 - 1];
} PLIC_Type;


/**
  \ingroup    CSI_core_register
  \defgroup   CSI_PMP Physical Memory Protection (PMP)
  \brief      Type definitions for the PMP Registers
  @{
 */

#define PMP_PMPCFG_R_Pos                       0U                                    /*!< PMP PMPCFG: R Position */
#define PMP_PMPCFG_R_Msk                       (0x1UL << PMP_PMPCFG_R_Pos)           /*!< PMP PMPCFG: R Mask */

#define PMP_PMPCFG_W_Pos                       1U                                    /*!< PMP PMPCFG: W Position */
#define PMP_PMPCFG_W_Msk                       (0x1UL << PMP_PMPCFG_W_Pos)           /*!< PMP PMPCFG: W Mask */

#define PMP_PMPCFG_X_Pos                       2U                                    /*!< PMP PMPCFG: X Position */
#define PMP_PMPCFG_X_Msk                       (0x1UL << PMP_PMPCFG_X_Pos)           /*!< PMP PMPCFG: X Mask */

#define PMP_PMPCFG_A_Pos                       3U                                    /*!< PMP PMPCFG: A Position */
#define PMP_PMPCFG_A_Msk                       (0x3UL << PMP_PMPCFG_A_Pos)           /*!< PMP PMPCFG: A Mask */

#define PMP_PMPCFG_L_Pos                       7U                                    /*!< PMP PMPCFG: L Position */
#define PMP_PMPCFG_L_Msk                       (0x1UL << PMP_PMPCFG_L_Pos)           /*!< PMP PMPCFG: L Mask */

typedef enum {
    REGION_SIZE_4B       = -1,
    REGION_SIZE_8B       = 0,
    REGION_SIZE_16B      = 1,
    REGION_SIZE_32B      = 2,
    REGION_SIZE_64B      = 3,
    REGION_SIZE_128B     = 4,
    REGION_SIZE_256B     = 5,
    REGION_SIZE_512B     = 6,
    REGION_SIZE_1KB      = 7,
    REGION_SIZE_2KB      = 8,
    REGION_SIZE_4KB      = 9,
    REGION_SIZE_8KB      = 10,
    REGION_SIZE_16KB     = 11,
    REGION_SIZE_32KB     = 12,
    REGION_SIZE_64KB     = 13,
    REGION_SIZE_128KB    = 14,
    REGION_SIZE_256KB    = 15,
    REGION_SIZE_512KB    = 16,
    REGION_SIZE_1MB      = 17,
    REGION_SIZE_2MB      = 18,
    REGION_SIZE_4MB      = 19,
    REGION_SIZE_8MB      = 20,
    REGION_SIZE_16MB     = 21,
    REGION_SIZE_32MB     = 22,
    REGION_SIZE_64MB     = 23,
    REGION_SIZE_128MB    = 24,
    REGION_SIZE_256MB    = 25,
    REGION_SIZE_512MB    = 26,
    REGION_SIZE_1GB      = 27,
    REGION_SIZE_2GB      = 28,
    REGION_SIZE_4GB      = 29,
    REGION_SIZE_8GB      = 30,
    REGION_SIZE_16GB     = 31
} region_size_e;

typedef enum {
    ADDRESS_MATCHING_TOR   = 1,
    ADDRESS_MATCHING_NAPOT = 3
} address_matching_e;

typedef struct {
    uint32_t r: 1;           /* readable enable */
    uint32_t w: 1;           /* writeable enable */
    uint32_t x: 1;           /* execable enable */
    address_matching_e a: 2; /* address matching mode */
    uint32_t reserved: 2;    /* reserved */
    uint32_t l: 1;           /* lock enable */
} mpu_region_attr_t;

/*@} end of group CSI_PMP */

/* CACHE Register Definitions */
#define CACHE_MHCR_WBR_Pos                     8U                                            /*!< CACHE MHCR: WBR Position */
#define CACHE_MHCR_WBR_Msk                     (0x1UL << CACHE_MHCR_WBR_Pos)                 /*!< CACHE MHCR: WBR Mask */

#define CACHE_MHCR_IBPE_Pos                    7U                                            /*!< CACHE MHCR: IBPE Position */
#define CACHE_MHCR_IBPE_Msk                    (0x1UL << CACHE_MHCR_IBPE_Pos)                /*!< CACHE MHCR: IBPE Mask */

#define CACHE_MHCR_BTB_Pos                     6U                                            /*!< CACHE MHCR: BTB Position */
#define CACHE_MHCR_BTB_Msk                     (0x1UL << CACHE_MHCR_BTB_Pos)                 /*!< CACHE MHCR: BTB Mask */

#define CACHE_MHCR_BPE_Pos                     5U                                            /*!< CACHE MHCR: BPE Position */
#define CACHE_MHCR_BPE_Msk                     (0x1UL << CACHE_MHCR_BPE_Pos)                 /*!< CACHE MHCR: BPE Mask */

#define CACHE_MHCR_RS_Pos                      4U                                            /*!< CACHE MHCR: RS Position */
#define CACHE_MHCR_RS_Msk                      (0x1UL << CACHE_MHCR_RS_Pos)                  /*!< CACHE MHCR: RS Mask */

#define CACHE_MHCR_WB_Pos                      3U                                            /*!< CACHE MHCR: WB Position */
#define CACHE_MHCR_WB_Msk                      (0x1UL << CACHE_MHCR_WB_Pos)                  /*!< CACHE MHCR: WB Mask */

#define CACHE_MHCR_WA_Pos                      2U                                            /*!< CACHE MHCR: WA Position */
#define CACHE_MHCR_WA_Msk                      (0x1UL << CACHE_MHCR_WA_Pos)                  /*!< CACHE MHCR: WA Mask */

#define CACHE_MHCR_DE_Pos                      1U                                            /*!< CACHE MHCR: DE Position */
#define CACHE_MHCR_DE_Msk                      (0x1UL << CACHE_MHCR_DE_Pos)                  /*!< CACHE MHCR: DE Mask */

#define CACHE_MHCR_IE_Pos                      0U                                            /*!< CACHE MHCR: IE Position */
#define CACHE_MHCR_IE_Msk                      (0x1UL << CACHE_MHCR_IE_Pos)                  /*!< CACHE MHCR: IE Mask */

#if CONFIG_CPU_XUANTIE_R908 || CONFIG_CPU_XUANTIE_R908FD || CONFIG_CPU_XUANTIE_R908FDV \
    || CONFIG_CPU_XUANTIE_R908_CP || CONFIG_CPU_XUANTIE_R908FD_CP || CONFIG_CPU_XUANTIE_R908FDV_CP
#define MCER_ECC_FATAL_Pos           34U
#define MCER_ECC_FATAL_Msk           (0x1ULL << MCER_ECC_FATAL_Pos)

#define MCER_ECC_VLD_Pos             35U
#define MCER_ECC_VLD_Msk             (0x1ULL << MCER_ECC_VLD_Pos)

#define MCER_RAMID_Pos               25U
#define MCER_RAMID_Msk               (0x7ULL << MCER_RAMID_Pos)
#else
#define MCER_ECC_FATAL_Pos           30U
#define MCER_ECC_FATAL_Msk           (0x1ULL << MCER_ECC_FATAL_Pos)
#define MCER_ECC_VLD_Pos             31U
#define MCER_ECC_VLD_Msk             (0x1ULL << MCER_ECC_VLD_Pos)
#define MCER_RAMID_Pos               21U
#define MCER_RAMID_Msk               (0x7ULL << MCER_RAMID_Pos)
#endif

#define CACHE_MCER2_ECC_FATAL_Pos              62U
#define CACHE_MCER2_ECC_FATAL_Msk              (0x1ULL << CACHE_MCER2_ECC_FATAL_Pos)

#define CACHE_MCER2H_ECC_FATAL_Pos             30U
#define CACHE_MCER2H_ECC_FATAL_Msk             (0x1ULL << CACHE_MCER2H_ECC_FATAL_Pos)

#define CACHE_MCER2_ECC_VLD_Pos                63U
#define CACHE_MCER2_ECC_VLD_Msk                (0x1ULL << CACHE_MCER2_ECC_VLD_Pos)

#define CACHE_MCER2H_ECC_VLD_Pos               31U
#define CACHE_MCER2H_ECC_VLD_Msk               (0x1ULL << CACHE_MCER2H_ECC_VLD_Pos)

#define CACHE_MCER2_RAMID_Pos                  53U
#define CACHE_MCER2_RAMID_Msk                  (0x3ULL << CACHE_MCER2_RAMID_Pos)

#define CACHE_MCER2H_RAMID_Pos                 21U
#define CACHE_MCER2H_RAMID_Msk                 (0x3ULL << CACHE_MCER2H_RAMID_Pos)

#define CACHE_INV_ADDR_Pos                     6U
#define CACHE_INV_ADDR_Msk                     (0xFFFFFFFFULL << CACHE_INV_ADDR_Pos)

enum MCER_FAULT_RAMID {
    /* L1 Cache, JTLB and TCM (RAMID of MCER)*/
    MCER_FAULT_RAMID_L1_ICACHE_TAG = 0,
    MCER_FAULT_RAMID_L1_ICACHE_DATA,
    MCER_FAULT_RAMID_L1_DCACHE_TAG,
    MCER_FAULT_RAMID_L1_DCACHE_DATA,
    MCER_FAULT_RAMID_JTLB_TAG,
    MCER_FAULT_RAMID_JTLB_DATA,
    MCER_FAULT_RAMID_DTCM,
    MCER_FAULT_RAMID_ITCM
};

enum MCER2_FAULT_RAMID {
    MCER2_FAULT_RAMID_L2_CACHE_TAG = 0,
    MCER2_FAULT_RAMID_L2_CACHE_DATA,
    MCER2_FAULT_RAMID_L2_CACHE_DIRTY
};

/*@} end of group CSI_CACHE */

// MSTATUS Register
#define MSTATUS_TVM_MASK (1L << 20)     // mstatus.TVM                      [20]
#define MSTATUS_MPP_MASK (3L << 11)     // mstatus.SPP                      [11:12]
#ifndef MSTATUS_MPP_M
#define MSTATUS_MPP_M    (3L << 11)     // Machine mode                     11
#endif
#define MSTATUS_MPP_S    (1L << 11)     // Supervisor mode                  01
#define MSTATUS_MPP_U    (0L << 11)     // User mode                        00

// SSTATUS Register
#define SSTATUS_SPP_MASK (3L << 8)      // sstatus.SPP                      [8:9]
#define SSTATUS_SPP_S    (1L << 8)      // Supervisor mode                  01
#define SSTATUS_SPP_U    (0L << 8)      // User mode                        00

typedef enum {
    USER_MODE        = 0,
    SUPERVISOR_MODE  = 1,
    MACHINE_MODE     = 3,
} cpu_work_mode_t;

/**
  \brief   Get CPU WORK MODE
  \details Returns CPU WORK MODE.
  \return  CPU WORK MODE
 */
__STATIC_INLINE int csi_get_cpu_work_mode(void)
{
    return (int)__get_CPU_WORK_MODE();
}

/**
  \brief   Get current hartid
  \return  hartid
 */
__STATIC_INLINE int csi_get_cpu_id(void)
{
    unsigned long result;

#if defined(CONFIG_RISCV_SMODE) && CONFIG_RISCV_SMODE
    return 0;
#endif
    __ASM volatile("csrr %0, mhartid" : "=r"(result) : : "memory");
    return result;
}

/**
  \brief   Get cache line size
  \return  cache line size
 */
__STATIC_INLINE int csi_get_cache_line_size(void)
{
    return 64;
}


/**
  \ingroup  CSI_core_register
  \defgroup CSI_CINT     Core Local Interrupt (CLINT)
  \brief    Type definitions for the Core Local Interrupt Registers.
  @{
 */

/**
  \brief  The data structure of the access Clint.
 */
typedef struct {
    __IOM uint32_t MSIP0;
    __IOM uint32_t MSIP1;
    __IOM uint32_t MSIP2;
    __IOM uint32_t MSIP3;
    __IOM uint32_t MSIP4;
    __IOM uint32_t MSIP5;
    __IOM uint32_t MSIP6;
    __IOM uint32_t MSIP7;
    uint32_t RESERVED0[(0x4004000 - 0x400001C) / 4 - 1];
    __IOM uint32_t MTIMECMPL0;
    __IOM uint32_t MTIMECMPH0;
    __IOM uint32_t MTIMECMPL1;
    __IOM uint32_t MTIMECMPH1;
    __IOM uint32_t MTIMECMPL2;
    __IOM uint32_t MTIMECMPH2;
    __IOM uint32_t MTIMECMPL3;
    __IOM uint32_t MTIMECMPH3;
    __IOM uint32_t MTIMECMPL4;
    __IOM uint32_t MTIMECMPH4;
    __IOM uint32_t MTIMECMPL5;
    __IOM uint32_t MTIMECMPH5;
    __IOM uint32_t MTIMECMPL6;
    __IOM uint32_t MTIMECMPH6;
    __IOM uint32_t MTIMECMPL7;
    __IOM uint32_t MTIMECMPH7;
    uint32_t RESERVED1[(0x400BFF8 - 0x400403C) / 4 - 1];
    __IOM uint32_t MTIMEL;
    __IOM uint32_t MTIMEH;
    __IOM uint32_t SSIP0;
    __IOM uint32_t SSIP1;
    __IOM uint32_t SSIP2;
    __IOM uint32_t SSIP3;
    __IOM uint32_t SSIP4;
    __IOM uint32_t SSIP5;
    __IOM uint32_t SSIP6;
    __IOM uint32_t SSIP7;
    uint32_t RESERVED2[(0x400D000 - 0x400C01C) / 4 - 1];
    __IOM uint32_t STIMECMPL0;
    __IOM uint32_t STIMECMPH0;
    __IOM uint32_t STIMECMPL1;
    __IOM uint32_t STIMECMPH1;
    __IOM uint32_t STIMECMPL2;
    __IOM uint32_t STIMECMPH2;
    __IOM uint32_t STIMECMPL3;
    __IOM uint32_t STIMECMPH3;
    __IOM uint32_t STIMECMPL4;
    __IOM uint32_t STIMECMPH4;
    __IOM uint32_t STIMECMPL5;
    __IOM uint32_t STIMECMPH5;
    __IOM uint32_t STIMECMPL6;
    __IOM uint32_t STIMECMPH6;
    __IOM uint32_t STIMECMPL7;
    __IOM uint32_t STIMECMPH7;
    uint32_t RESERVED3[(0x400FFF8 - 0x400D03C) / 4 - 1];
    __IOM uint32_t STIMEL;
    __IOM uint32_t STIMEH;
} CLINT_Type;

typedef struct {
#ifdef CONFIG_RISCV_SMODE
    __IOM uint32_t STIMECMPL0;
    __IOM uint32_t STIMECMPH0;
#else
    __IOM uint32_t MTIMECMPL0;
    __IOM uint32_t MTIMECMPH0;
#endif
} CLINT_CMP_Type;

/*@} end of group CSI_SysTick */


/**
  \ingroup    CSI_core_register
  \defgroup   CSI_core_bitfield     Core register bit field macros
  \brief      Macros for use with bit field definitions (xxx_Pos, xxx_Msk).
  @{
 */

/**
  \brief   Mask and shift a bit field value for use in a register bit range.
  \param[in] field  Name of the register bit field.
  \param[in] value  Value of the bit field.
  \return           Masked and shifted value.
*/
#define _VAL2FLD(field, value)    ((value << field ## _Pos) & field ## _Msk)

/**
  \brief     Mask and shift a register value to extract a bit filed value.
  \param[in] field  Name of the register bit field.
  \param[in] value  Value of register.
  \return           Masked and shifted bit field value.
*/
#define _FLD2VAL(field, value)    ((value & field ## _Msk) >> field ## _Pos)

/*@} end of group CSI_core_bitfield */

/**
  \ingroup    CSI_core_register
  \defgroup   CSI_core_base     Core Definitions
  \brief      Definitions for base addresses, unions, and structures.
  @{
 */

/*@} */

/*******************************************************************************
 *                Hardware Abstraction Layer
  Core Function Interface contains:
  - Core VIC Functions
  - Core CORET Functions
  - Core Register Access Functions
 ******************************************************************************/
/**
  \defgroup CSI_Core_FunctionInterface Functions and Instructions Reference
*/

/* ##########################   VIC functions  #################################### */
/**
  \ingroup  CSI_Core_FunctionInterface
  \defgroup CSI_Core_VICFunctions VIC Functions
  \brief    Functions that manage interrupts and exceptions via the VIC.
  @{
 */

/* The following MACROS handle generation of the register offset and byte masks */
#define _BIT_SHIFT(IRQn)         (  ((((uint32_t)(int32_t)(IRQn))         )      &  0x03UL) * 8UL)
#define _IP_IDX(IRQn)            (   (((uint32_t)(int32_t)(IRQn))                >>    5UL)      )
#define _IP2_IDX(IRQn)            (   (((uint32_t)(int32_t)(IRQn))                >>    2UL)      )

#define PLIC_Hn_MSIE_ADDR(msie_base, hartid)        ((unsigned long)(msie_base) + 0x100 * (hartid))
#define PLIC_Hn_MSIE_VAL(msie_base, hartid)         (*(__IOM uint32_t *)(PLIC_Hn_MSIE_ADDR(msie_base, hartid)))
#define PLIC_Hn_MSTH_ADDR(msth_base, hartid)        ((unsigned long)(msth_base) + 0x2000 * (hartid))
#define PLIC_Hn_MSTH_VAL(msth_base, hartid)         (*(__IOM uint32_t *)(PLIC_Hn_MSTH_ADDR(msth_base, hartid)))
#define PLIC_Hn_MSCLAIM_ADDR(msclaim_base, hartid)  ((unsigned long)(msclaim_base) + 0x2000 * (hartid))
#define PLIC_Hn_MSCLAIM_VAL(msclaim_base, hartid)   (*(__IOM uint32_t *)(PLIC_Hn_MSCLAIM_ADDR(msclaim_base, hartid)))

/**
    \brief   Enable External Interrupt
    \details Enable a device-specific interrupt in the VIC interrupt controller.
    \param [in]      IRQn         External interrupt number. Value cannot be negative.
    */
__STATIC_INLINE void csi_vic_enable_irq(int32_t IRQn)
{
    int hartid = csi_get_cpu_id();
    PLIC_Type *plic = (PLIC_Type *)CONFIG_PLIC_BASE;

#if CONFIG_INTC_CLIC_PLIC
    if (IRQn > PLIC_IRQ_OFFSET) {
        IRQn -= PLIC_IRQ_OFFSET;
    } else {
        CLIC->CLICINT[IRQn].IE |= CLIC_INTIE_IE_Msk;
        __DSB();
        return;
    }
#endif
#if defined(CONFIG_RISCV_SMODE) && CONFIG_RISCV_SMODE
    PLIC_Hn_MSIE_VAL(&plic->PLIC_H0_SIE[IRQn/32], hartid) = PLIC_Hn_MSIE_VAL(&plic->PLIC_H0_SIE[IRQn/32], hartid) | (0x1 << (IRQn%32));
#else
    PLIC_Hn_MSIE_VAL(&plic->PLIC_H0_MIE[IRQn/32], hartid) = PLIC_Hn_MSIE_VAL(&plic->PLIC_H0_MIE[IRQn/32], hartid) | (0x1 << (IRQn%32));
#endif
}

/**
  \brief   Enable External Interrupt(deprecated)
  \details Enable a device-specific interrupt in the VIC interrupt controller.
  \param [in]      plic_base    PLIC base address
  \param [in]      IRQn         External interrupt number. Value cannot be negative.
 */
__STATIC_INLINE void csi_plic_enable_irq(unsigned long plic_base, int32_t IRQn)
{
    int hartid = csi_get_cpu_id();
    PLIC_Type *plic = (PLIC_Type *)plic_base;

#if defined(CONFIG_RISCV_SMODE) && CONFIG_RISCV_SMODE
    PLIC_Hn_MSIE_VAL(&plic->PLIC_H0_SIE[IRQn/32], hartid) = PLIC_Hn_MSIE_VAL(&plic->PLIC_H0_SIE[IRQn/32], hartid) | (0x1 << (IRQn%32));
#else
    PLIC_Hn_MSIE_VAL(&plic->PLIC_H0_MIE[IRQn/32], hartid) = PLIC_Hn_MSIE_VAL(&plic->PLIC_H0_MIE[IRQn/32], hartid) | (0x1 << (IRQn%32));
#endif
}

/**
  \brief   Disable External Interrupt
  \details Disable a device-specific interrupt in the VIC interrupt controller.
  \param [in]      IRQn         External interrupt number. Value cannot be negative.
 */
__STATIC_INLINE void csi_vic_disable_irq(int32_t IRQn)
{
    int hartid = csi_get_cpu_id();
    PLIC_Type *plic = (PLIC_Type *)CONFIG_PLIC_BASE;

#if CONFIG_INTC_CLIC_PLIC
    if (IRQn > PLIC_IRQ_OFFSET) {
        IRQn -= PLIC_IRQ_OFFSET;
    } else {
        CLIC->CLICINT[IRQn].IE &= ~CLIC_INTIE_IE_Msk;
        __DSB();
        return;
    }
#endif
#if defined(CONFIG_RISCV_SMODE) && CONFIG_RISCV_SMODE
    PLIC_Hn_MSIE_VAL(&plic->PLIC_H0_SIE[IRQn/32], hartid) = PLIC_Hn_MSIE_VAL(&plic->PLIC_H0_SIE[IRQn/32], hartid) & (~(0x1 << (IRQn%32)));
#else
    PLIC_Hn_MSIE_VAL(&plic->PLIC_H0_MIE[IRQn/32], hartid) = PLIC_Hn_MSIE_VAL(&plic->PLIC_H0_MIE[IRQn/32], hartid) & (~(0x1 << (IRQn%32)));
#endif
}

/**
  \brief   Disable External Interrupt(deprecated)
  \details Disable a device-specific interrupt in the VIC interrupt controller.
  \param [in]      plic_base    PLIC base address
  \param [in]      IRQn         External interrupt number. Value cannot be negative.
 */
__STATIC_INLINE void csi_plic_disable_irq(unsigned long plic_base, int32_t IRQn)
{
    int hartid = csi_get_cpu_id();
    PLIC_Type *plic = (PLIC_Type *)plic_base;

#if defined(CONFIG_RISCV_SMODE) && CONFIG_RISCV_SMODE
    PLIC_Hn_MSIE_VAL(&plic->PLIC_H0_SIE[IRQn/32], hartid) = PLIC_Hn_MSIE_VAL(&plic->PLIC_H0_SIE[IRQn/32], hartid) & (~(0x1 << (IRQn%32)));
#else
    PLIC_Hn_MSIE_VAL(&plic->PLIC_H0_MIE[IRQn/32], hartid) = PLIC_Hn_MSIE_VAL(&plic->PLIC_H0_MIE[IRQn/32], hartid) & (~(0x1 << (IRQn%32)));
#endif
}

/**
  \brief   Check Interrupt is Enabled or not
  \details Read the enabled register in the VIC and returns the pending bit for the specified interrupt.
  \param [in]      IRQn         External interrupt number. Value cannot be negative.
  \return             0  Interrupt status is not enabled.
  \return             1  Interrupt status is enabled.
 */
__STATIC_INLINE uint32_t csi_vic_get_enabled_irq(int32_t IRQn)
{
    int hartid = csi_get_cpu_id();
    PLIC_Type *plic = (PLIC_Type *)CONFIG_PLIC_BASE;

#if CONFIG_INTC_CLIC_PLIC
    if (IRQn > PLIC_IRQ_OFFSET) {
        IRQn -= PLIC_IRQ_OFFSET;
    } else {
        return (uint32_t)(CLIC->CLICINT[IRQn].IE & CLIC_INTIE_IE_Msk);
    }
#endif
#if defined(CONFIG_RISCV_SMODE) && CONFIG_RISCV_SMODE
    return (uint32_t)((PLIC_Hn_MSIE_VAL(&plic->PLIC_H0_SIE[IRQn/32], hartid) >> IRQn%32) & 0x1);
#else
    return (uint32_t)((PLIC_Hn_MSIE_VAL(&plic->PLIC_H0_MIE[IRQn/32], hartid) >> IRQn%32) & 0x1);
#endif
}

/**
  \brief   Check Interrupt is Enabled or not(deprecated)
  \details Read the enabled register in the VIC and returns the pending bit for the specified interrupt.
  \param [in]      IRQn  Interrupt number.
  \return             0  Interrupt status is not enabled.
  \return             1  Interrupt status is enabled.
 */
__STATIC_INLINE uint32_t csi_plic_get_enabled_irq(unsigned long plic_base, int32_t IRQn)
{
    int hartid = csi_get_cpu_id();
    PLIC_Type *plic = (PLIC_Type *)plic_base;

#if defined(CONFIG_RISCV_SMODE) && CONFIG_RISCV_SMODE
    return (uint32_t)((PLIC_Hn_MSIE_VAL(&plic->PLIC_H0_SIE[IRQn/32], hartid) >> IRQn%32) & 0x1);
#else
    return (uint32_t)((PLIC_Hn_MSIE_VAL(&plic->PLIC_H0_MIE[IRQn/32], hartid) >> IRQn%32) & 0x1);
#endif
}

/**
  \brief   Check Interrupt is Pending or not
  \details Read the pending register in the VIC and returns the pending bit for the specified interrupt.
  \param [in]      IRQn  Interrupt number.
  \return             0  Interrupt status is not pending.
  \return             1  Interrupt status is pending.
 */
__STATIC_INLINE uint32_t csi_vic_get_pending_irq(int32_t IRQn)
{
    PLIC_Type *plic = (PLIC_Type *)CONFIG_PLIC_BASE;
#if CONFIG_INTC_CLIC_PLIC
    if (IRQn > PLIC_IRQ_OFFSET) {
        IRQn -= PLIC_IRQ_OFFSET;
    } else {
        return (uint32_t)(CLIC->CLICINT[IRQn].IP & CLIC_INTIP_IP_Msk);
    }
#endif
    return (uint32_t)((plic->PLIC_IP[IRQn/32] >> IRQn%32) & 0x1);
}

/**
  \brief   Set Pending Interrupt
  \details Set the pending bit of an external interrupt.
  \param [in]      IRQn  Interrupt number. Value cannot be negative.
 */
__STATIC_INLINE void csi_vic_set_pending_irq(int32_t IRQn)
{
    PLIC_Type *plic = (PLIC_Type *)CONFIG_PLIC_BASE;
#if CONFIG_INTC_CLIC_PLIC
    if (IRQn > PLIC_IRQ_OFFSET) {
        IRQn -= PLIC_IRQ_OFFSET;
    } else {
        CLIC->CLICINT[IRQn].IP |= CLIC_INTIP_IP_Msk;
        return;
    }
#endif
    plic->PLIC_IP[IRQn/32] = plic->PLIC_IP[IRQn/32] | (0x1 << (IRQn%32));
}

/**
  \brief   Clear Pending Interrupt
  \details Clear the pending bit of an external interrupt.
  \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
__STATIC_INLINE void csi_vic_clear_pending_irq(int32_t IRQn)
{
    PLIC_Type *plic = (PLIC_Type *)CONFIG_PLIC_BASE;
#if CONFIG_INTC_CLIC_PLIC
    if (IRQn > PLIC_IRQ_OFFSET) {
        IRQn -= PLIC_IRQ_OFFSET;
    } else {
        CLIC->CLICINT[IRQn].IP &= ~CLIC_INTIP_IP_Msk;
        return;
    }
#endif
    plic->PLIC_H0_SCLAIM = IRQn;
}

/**
  \brief   Check Interrupt is Pending or not(deprecated)
  \details Read the pending register in the VIC and returns the pending bit for the specified interrupt.
  \param [in]      IRQn  Interrupt number.
  \return             0  Interrupt status is not pending.
  \return             1  Interrupt status is pending.
 */
__STATIC_INLINE uint32_t csi_plic_get_pending_irq(unsigned long plic_base, int32_t IRQn)
{
    PLIC_Type *plic = (PLIC_Type *)plic_base;
    return (uint32_t)((plic->PLIC_IP[IRQn/32] >> IRQn%32) & 0x1);
}

/**
  \brief   Set Pending Interrupt(deprecated)
  \details Set the pending bit of an external interrupt.
  \param [in]      IRQn  Interrupt number. Value cannot be negative.
 */
__STATIC_INLINE void csi_plic_set_pending_irq(unsigned long plic_base, int32_t IRQn)
{
    PLIC_Type *plic = (PLIC_Type *)plic_base;
    plic->PLIC_IP[IRQn/32] = plic->PLIC_IP[IRQn/32] | (0x1 << (IRQn%32));
}

/**
  \brief   Clear Pending Interrupt(deprecated)
  \details Clear the pending bit of an external interrupt.
  \param [in]      IRQn  External interrupt number. Value cannot be negative.
 */
__STATIC_INLINE void csi_plic_clear_pending_irq(unsigned long plic_base, int32_t IRQn)
{
    PLIC_Type *plic = (PLIC_Type *)plic_base;
    plic->PLIC_H0_SCLAIM = IRQn;
}

/**
  \brief   Set Interrupt Priority
  \details Set the priority of an interrupt.
  \note    The priority cannot be set for every core interrupt.
  \param [in]      IRQn  Interrupt number.
  \param [in]  priority  Priority to set.
 */
__STATIC_INLINE void csi_vic_set_prio(int32_t IRQn, uint32_t priority)
{
    PLIC_Type *plic = (PLIC_Type *)CONFIG_PLIC_BASE;
#if CONFIG_INTC_CLIC_PLIC
    if (IRQn > PLIC_IRQ_OFFSET) {
        IRQn -= PLIC_IRQ_OFFSET;
    } else {
        uint8_t nlbits = (CLIC->CLICINFO & CLIC_INFO_CLICINTCTLBITS_Msk) >> CLIC_INFO_CLICINTCTLBITS_Pos;
        CLIC->CLICINT[IRQn].CTL = (CLIC->CLICINT[IRQn].CTL & (~CLIC_INTCFG_PRIO_Msk)) | (priority << (8 - nlbits));
        __DSB();
        return;
    }
#endif
    plic->PLIC_PRIO[IRQn - 1] = priority;
}

/**
  \brief   Get Interrupt Priority
  \details Read the priority of an interrupt.
           The interrupt number can be positive to specify an external (device specific) interrupt,
           or negative to specify an internal (core) interrupt.
  \param [in]   IRQn  Interrupt number.
  \return             Interrupt Priority.
                      Value is aligned automatically to the implemented priority bits of the microcontroller.
 */
__STATIC_INLINE uint32_t csi_vic_get_prio(int32_t IRQn)
{
    PLIC_Type *plic = (PLIC_Type *)CONFIG_PLIC_BASE;
#if CONFIG_INTC_CLIC_PLIC
    if (IRQn > PLIC_IRQ_OFFSET) {
        IRQn -= PLIC_IRQ_OFFSET;
    } else {
        uint8_t nlbits = (CLIC->CLICINFO & CLIC_INFO_CLICINTCTLBITS_Msk) >> CLIC_INFO_CLICINTCTLBITS_Pos;
        return CLIC->CLICINT[IRQn].CTL >> (8 - nlbits);
    }
#endif
    uint32_t prio = plic->PLIC_PRIO[IRQn - 1];
    return prio;
}

/**
  \brief   Set Interrupt Priority(deprecated)
  \details Set the priority of an interrupt.
  \note    The priority cannot be set for every core interrupt.
  \param [in]      IRQn  Interrupt number.
  \param [in]  priority  Priority to set.
 */
__STATIC_INLINE void csi_plic_set_prio(unsigned long plic_base, int32_t IRQn, uint32_t priority)
{
    PLIC_Type *plic = (PLIC_Type *)plic_base;
    plic->PLIC_PRIO[IRQn - 1] = priority;
}

/**
  \brief   Get Interrupt Priority(deprecated)
  \details Read the priority of an interrupt.
           The interrupt number can be positive to specify an external (device specific) interrupt,
           or negative to specify an internal (core) interrupt.
  \param [in]   IRQn  Interrupt number.
  \return             Interrupt Priority.
                      Value is aligned automatically to the implemented priority bits of the microcontroller.
 */
__STATIC_INLINE uint32_t csi_plic_get_prio(unsigned long plic_base, int32_t IRQn)
{
    PLIC_Type *plic = (PLIC_Type *)plic_base;
    uint32_t prio = plic->PLIC_PRIO[IRQn - 1];
    return prio;
}

/*@} end of CSI_Core_VICFunctions */

/* ##########################   PMP functions  #################################### */
/**
  \ingroup  CSI_Core_FunctionInterface
  \defgroup CSI_Core_PMPFunctions PMP Functions
  \brief    Functions that manage interrupts and exceptions via the VIC.
  @{
 */

/**
  \brief  configure memory protected region.
  \details
  \param [in]  idx        memory protected region (0, 1, 2, ..., 15).
  \param [in]  base_addr  base address must be aligned with page size.
  \param [in]  size       \ref region_size_e. memory protected region size.
  \param [in]  attr       \ref region_size_t. memory protected region attribute.
  \param [in]  enable     enable or disable memory protected region.
  */
__STATIC_INLINE void csi_mpu_config_region(uint32_t idx, uint32_t base_addr, region_size_e size,
        mpu_region_attr_t attr, uint32_t enable)
{
    uint8_t  pmpxcfg = 0;
    uint32_t addr = 0;

    if (idx > 15) {
        return;
    }

    if (!enable) {
        attr.a = (address_matching_e)0;
    }

    if (attr.a == ADDRESS_MATCHING_TOR) {
        addr = base_addr >> 2;
    } else {
        if (size == REGION_SIZE_4B) {
            addr = base_addr >> 2;
            attr.a = (address_matching_e)2;
        } else {
            addr = ((base_addr >> 2) & (0xFFFFFFFFU - ((1 << (size + 1)) - 1))) | ((1 << size) - 1);
        }
    }

    __set_PMPADDRx(idx, addr);

    pmpxcfg |= (attr.r << PMP_PMPCFG_R_Pos) | (attr.w << PMP_PMPCFG_W_Pos) |
               (attr.x << PMP_PMPCFG_X_Pos) | (attr.a << PMP_PMPCFG_A_Pos) |
               (attr.l << PMP_PMPCFG_L_Pos);

    __set_PMPxCFG(idx, pmpxcfg);
}

/**
  \brief  disable mpu region by idx.
  \details
  \param [in]  idx        memory protected region (0, 1, 2, ..., 15).
  */
__STATIC_INLINE void csi_mpu_disable_region(uint32_t idx)
{
    __set_PMPxCFG(idx, __get_PMPxCFG(idx) & (~PMP_PMPCFG_A_Msk));
}

/*@} end of CSI_Core_PMPFunctions */

/* ##################################    SysTick function  ############################################ */
/**
  \ingroup  CSI_Core_FunctionInterface
  \defgroup CSI_Core_SysTickFunctions SysTick Functions
  \brief    Functions that configure the System.
  @{
 */

#define CLINT_TIMECMPn_ADDR(time_cmp_base, hartid)  ((unsigned long)(time_cmp_base) + 8 * (hartid))
#define CLINT_TIMECMPn_VAL(time_cmp_base, hartid)   (*(__IOM uint32_t *)(CLINT_TIMECMPn_ADDR(time_cmp_base, hartid)))

__STATIC_INLINE uint32_t _csi_clint_config2(unsigned long coret_base, uint16_t hartid, uint32_t ticks, int32_t IRQn)
{
    CLINT_Type *clint = (CLINT_Type *)coret_base;
#if defined(CONFIG_RISCV_SMODE) && CONFIG_RISCV_SMODE
    uint64_t value = (((uint64_t)(CLINT_TIMECMPn_VAL(&clint->STIMECMPH0, hartid))) << 32) + \
                     (uint64_t)(CLINT_TIMECMPn_VAL(&clint->STIMECMPL0, hartid));

    if ((value != 0) && (value != 0xffffffffffffffff)) {
        value = value + (uint64_t)ticks;
    } else {
        value = __get_MTIME() + ticks;
    }
    CLINT_TIMECMPn_VAL(&clint->STIMECMPH0, hartid) = (uint32_t)(value >> 32);
    CLINT_TIMECMPn_VAL(&clint->STIMECMPL0, hartid) = (uint32_t)value;
#else
    uint64_t value = (((uint64_t)(CLINT_TIMECMPn_VAL(&clint->MTIMECMPH0, hartid))) << 32) + \
                     (uint64_t)(CLINT_TIMECMPn_VAL(&clint->MTIMECMPL0, hartid));

    if ((value != 0) && (value != 0xffffffffffffffff)) {
        value = value + (uint64_t)ticks;
    } else {
        value = __get_MTIME() + ticks;
    }
    CLINT_TIMECMPn_VAL(&clint->MTIMECMPH0, hartid) = (uint32_t)(value >> 32);
    CLINT_TIMECMPn_VAL(&clint->MTIMECMPL0, hartid) = (uint32_t)value;
#endif

    return (0UL);
}

__STATIC_INLINE uint32_t csi_clint_config(unsigned long coret_base, uint32_t ticks, int32_t IRQn)
{
    return _csi_clint_config2(coret_base, 0, ticks, IRQn);
}

__STATIC_INLINE void csi_coret_reset_value2()
{
    uint32_t value = 0x0;
    int hartid = csi_get_cpu_id();
    CLINT_Type *clint = (CLINT_Type *)CORET_BASE;

#if defined(CONFIG_RISCV_SMODE) && CONFIG_RISCV_SMODE
    CLINT_TIMECMPn_VAL(&clint->STIMECMPH0, hartid) = (uint32_t)value;
    CLINT_TIMECMPn_VAL(&clint->STIMECMPL0, hartid) = (uint32_t)value;
#else
    CLINT_TIMECMPn_VAL(&clint->MTIMECMPH0, hartid) = (uint32_t)value;
    CLINT_TIMECMPn_VAL(&clint->MTIMECMPL0, hartid) = (uint32_t)value;
#endif
}

__STATIC_INLINE void csi_coret_reset_value(unsigned long coret_base)
{
    uint32_t value = 0x0;
    int hartid = csi_get_cpu_id();
    CLINT_Type *clint = (CLINT_Type *)coret_base;

#if defined(CONFIG_RISCV_SMODE) && CONFIG_RISCV_SMODE
    CLINT_TIMECMPn_VAL(&clint->STIMECMPH0, hartid) = (uint32_t)value;
    CLINT_TIMECMPn_VAL(&clint->STIMECMPL0, hartid) = (uint32_t)value;
#else
    CLINT_TIMECMPn_VAL(&clint->MTIMECMPH0, hartid) = (uint32_t)value;
    CLINT_TIMECMPn_VAL(&clint->MTIMECMPL0, hartid) = (uint32_t)value;
#endif
}

__STATIC_INLINE uint64_t _csi_clint_get_load2(unsigned long coret_base, uint16_t hartid)
{
    CLINT_Type *clint = (CLINT_Type *)coret_base;
#if defined(CONFIG_RISCV_SMODE) && CONFIG_RISCV_SMODE
    uint64_t value = (((uint64_t)CLINT_TIMECMPn_VAL(&clint->STIMECMPH0, hartid)) << 32) + \
                     (uint64_t)CLINT_TIMECMPn_VAL(&clint->STIMECMPL0, hartid);
#else
    uint64_t value = (((uint64_t)CLINT_TIMECMPn_VAL(&clint->MTIMECMPH0, hartid)) << 32) + \
                     (uint64_t)CLINT_TIMECMPn_VAL(&clint->MTIMECMPL0, hartid);
#endif

    return value;
}

/**
  \brief   get CORE timer reload high value(deprecated)
  \return          CORE timer counter value.
 */
__STATIC_INLINE uint64_t csi_clint_get_load(unsigned long coret_base)
{
    return _csi_clint_get_load2(coret_base, 0);
}

__STATIC_INLINE uint32_t _csi_clint_get_loadh2(unsigned long coret_base, uint16_t hartid)
{
    CLINT_Type *clint = (CLINT_Type *)coret_base;
#if defined(CONFIG_RISCV_SMODE) && CONFIG_RISCV_SMODE
    uint64_t value = (((uint64_t)CLINT_TIMECMPn_VAL(&clint->STIMECMPH0, hartid)) << 32) + \
                     (uint64_t)CLINT_TIMECMPn_VAL(&clint->STIMECMPL0, hartid);
#else
    uint64_t value = (((uint64_t)CLINT_TIMECMPn_VAL(&clint->MTIMECMPH0, hartid)) << 32) + \
                     (uint64_t)CLINT_TIMECMPn_VAL(&clint->MTIMECMPL0, hartid);
#endif

    return (value >> 32) & 0xFFFFFFFF;
}

/**
  \brief   get CORE timer reload high value(deprecated)
  \return          CORE timer counter value.
 */
__STATIC_INLINE uint32_t csi_clint_get_loadh(unsigned long coret_base)
{
    return _csi_clint_get_loadh2(coret_base, 0);
}

/**
  \brief   get CORE timer counter value(deprecated)
  \return          CORE timer counter value.
 */
__STATIC_INLINE unsigned long csi_clint_get_value(void)
{
    unsigned long result;
    __ASM volatile("csrr %0, time" : "=r"(result));
    return result;
}

/**
  \brief   get CORE timer counter high value(deprecated)
  \return          CORE timer counter value.
 */
__STATIC_INLINE uint32_t csi_clint_get_valueh(void)
{
    uint64_t result;
    __ASM volatile("csrr %0, time" : "=r"(result));
    return (result >> 32) & 0xFFFFFFFF;
}

/**
  \brief   CORE timer Configuration
  \details Initializes the System Timer and its interrupt, and starts the System Tick Timer.
           Counter is in free running mode to generate periodic interrupts.
  \param [in]  ticks  Number of ticks between two interrupts.
  \param [in]  IRQn   core timer Interrupt number.
  \return          0  Function succeeded.
  \return          1  Function failed.
  \note    When the variable <b>__Vendor_SysTickConfig</b> is set to 1, then the
           function <b>SysTick_Config</b> is not included. In this case, the file <b><i>device</i>.h</b>
           must contain a vendor-specific implementation of this function.
 */
__STATIC_INLINE uint32_t csi_coret_config(uint32_t ticks, int32_t IRQn)
{
    return _csi_clint_config2(CORET_BASE, csi_get_cpu_id(), ticks, IRQn);
}

/**
  \brief   get CORE timer reload value
  \return          CORE timer counter value.
 */
__STATIC_INLINE uint64_t csi_coret_get_load2(void)
{
    return _csi_clint_get_load2(CORET_BASE, csi_get_cpu_id());
}

/**
  \brief   get CORE timer counter value
  \return          CORE timer counter value.
 */
__STATIC_INLINE uint64_t csi_coret_get_value2()
{
#if __riscv_xlen == 64
    return csi_clint_get_value();
#else
    uint64_t result;
    unsigned long high, low;

    __ASM volatile("csrr %0, timeh" : "=r"(high));
    __ASM volatile("csrr %0, time" : "=r"(low));
    result = ((uint64_t)high << 32) | low;

    return result;
#endif
}

/**
  \brief   Enable CoreTimer(within clint) Interrupts
 */
__ALWAYS_STATIC_INLINE void csi_coret_irq_enable(void)
{
#if CONFIG_INTC_CLIC_PLIC
    extern void soc_irq_enable(uint32_t irq_num);
    return soc_irq_enable(7);
#else
    return __enable_coret_irq();
#endif
}

/**
  \brief   Disable CoreTimer(within clint) Interrupts
 */
__ALWAYS_STATIC_INLINE void csi_coret_irq_disable(void)
{
#if CONFIG_INTC_CLIC_PLIC
    extern void soc_irq_disable(uint32_t irq_num);
    return soc_irq_disable(7);
#else
    return __disable_coret_irq();
#endif
}


/*@} end of CSI_core_DebugFunctions */

/* ##########################  Cache functions  #################################### */
/**
  \ingroup  CSI_Core_FunctionInterface
  \defgroup CSI_Core_CacheFunctions Cache Functions
  \brief    Functions that configure Instruction and Data cache.
  @{
 */

/**
  \brief   whether I-Cache enable
  */
__STATIC_INLINE int csi_icache_is_enable()
{
    uint32_t cache = __get_MHCR();
    return (cache & CACHE_MHCR_IE_Msk) >> CACHE_MHCR_IE_Pos;
}

/**
  \brief   Enable I-Cache
  \details Turns on I-Cache
  */
__STATIC_INLINE void csi_icache_enable(void)
{
#if (__ICACHE_PRESENT == 1U)
    if (!csi_icache_is_enable()) {
        uint32_t cache;
        __DSB();
        __ISB();
        __ICACHE_IALL();
        cache = __get_MHCR();
        cache |= CACHE_MHCR_IE_Msk;
        __set_MHCR(cache);
        __DSB();
        __ISB();
    }
#endif
}


/**
  \brief   Disable I-Cache
  \details Turns off I-Cache
  */
__STATIC_INLINE void csi_icache_disable(void)
{
#if (__ICACHE_PRESENT == 1U)
    if (csi_icache_is_enable()) {
        uint32_t cache;
        __DSB();
        __ISB();
        cache = __get_MHCR();
        cache &= ~CACHE_MHCR_IE_Msk;            /* disable icache */
        __set_MHCR(cache);
        __ICACHE_IALL();                        /* invalidate all icache */
        __DSB();
        __ISB();
    }
#endif
}


/**
  \brief   Invalidate I-Cache
  \details Invalidates I-Cache
  */
__STATIC_INLINE void csi_icache_invalid(void)
{
#if (__ICACHE_PRESENT == 1U)
    __DSB();
    __ISB();
    __ICACHE_IALL();                        /* invalidate all icache */
    __DSB();
    __ISB();
#endif
}

/**
  \brief   whether D-Cache enable
  */
__STATIC_INLINE int csi_dcache_is_enable()
{
    uint32_t cache = __get_MHCR();
    return (cache & CACHE_MHCR_DE_Msk) >> CACHE_MHCR_DE_Pos;
}

/**
  \brief   Enable D-Cache
  \details Turns on D-Cache
  */
__STATIC_INLINE void csi_dcache_enable(void)
{
#if (__DCACHE_PRESENT == 1U)
    if (!csi_dcache_is_enable()) {
        uint32_t cache;
        __DSB();
        __ISB();
        __DCACHE_IALL();                        /* invalidate all dcache */
        cache = __get_MHCR();
        cache |= CACHE_MHCR_DE_Msk;             /* enable dcache */
        __set_MHCR(cache);

        __DSB();
        __ISB();
    }
#endif
}


/**
  \brief   Disable D-Cache
  \details Turns off D-Cache
  */
__STATIC_INLINE void csi_dcache_disable(void)
{
#if (__DCACHE_PRESENT == 1U)
    if (csi_dcache_is_enable()) {
        uint32_t cache;
        __DSB();
        __ISB();
        cache = __get_MHCR();
        cache &= ~(uint32_t)CACHE_MHCR_DE_Msk; /* disable all Cache */
        __set_MHCR(cache);
        __DCACHE_IALL();                             /* invalidate all Cache */
        __DSB();
        __ISB();
    }
#endif
}

/**
  \brief   Invalidate D-Cache
  \details Invalidates D-Cache
  */
__STATIC_INLINE void csi_dcache_invalid(void)
{
#if (__DCACHE_PRESENT == 1U)
    __DSB();
    __ISB();
    __DCACHE_IALL();                            /* invalidate all Cache */
    __DSB();
    __ISB();
#endif
}


/**
  \brief   Clean D-Cache
  \details Cleans D-Cache
  */
__STATIC_INLINE void csi_dcache_clean(void)
{
#if (__DCACHE_PRESENT == 1U)
    __DSB();
    __ISB();
    __DCACHE_CALL();                                     /* clean all Cache */
    __DSB();
    __ISB();
#endif
}


/**
  \brief   Clean & Invalidate D-Cache
  \details Cleans and Invalidates D-Cache
  */
__STATIC_INLINE void csi_dcache_clean_invalid(void)
{
#if (__DCACHE_PRESENT == 1U)
    __DSB();
    __ISB();
    __DCACHE_CIALL();                                   /* clean and inv all Cache */
    __DSB();
    __ISB();
#endif
}

/**
  \brief   D-Cache Invalidate by address
  \details Invalidates D-Cache for the given address
  \param[in]   addr    address (aligned to 64-byte boundary)
  \param[in]   dsize   size of memory block (in number of bytes)
*/
__STATIC_INLINE void csi_dcache_invalid_range(unsigned long *addr, size_t dsize)
{
#if (__DCACHE_PRESENT == 1U)
    int linesize = csi_get_cache_line_size();
    long op_size = dsize + (unsigned long)addr % linesize;
    unsigned long op_addr = (unsigned long)addr;

    __DSB();
#if CBO_INSN_SUPPORT
    while (op_size > 0) {
        __CBO_INVAL(op_addr);
        op_addr += linesize;
        op_size -= linesize;
    }
#else
    cpu_work_mode_t cpu_work_mode;
    cpu_work_mode = (cpu_work_mode_t)__get_CPU_WORK_MODE();

    if (cpu_work_mode == MACHINE_MODE) {
        while (op_size > 0) {
            __DCACHE_IPA(op_addr);
            op_addr += linesize;
            op_size -= linesize;
        }
    } else if (cpu_work_mode == SUPERVISOR_MODE) {
        while (op_size > 0) {
            __DCACHE_IVA(op_addr);
            op_addr += linesize;
            op_size -= linesize;
        }
    }
#endif

    __SYNC_IS();
    __DSB();
#endif
}


/**
  \brief   D-Cache Clean by address
  \details Cleans D-Cache for the given address
  \param[in]   addr    address (aligned to 64-byte boundary)
  \param[in]   dsize   size of memory block (in number of bytes)
*/
__STATIC_INLINE void csi_dcache_clean_range(unsigned long *addr, size_t dsize)
{

#if (__DCACHE_PRESENT == 1)
    int linesize = csi_get_cache_line_size();
    long op_size = dsize + (unsigned long)addr % linesize;
    unsigned long op_addr = (unsigned long) addr & CACHE_INV_ADDR_Msk;

    __DSB();
#if CBO_INSN_SUPPORT
    while (op_size > 0) {
        __CBO_CLEAN(op_addr);
        op_addr += linesize;
        op_size -= linesize;
    }
#else
    cpu_work_mode_t cpu_work_mode;
    cpu_work_mode = (cpu_work_mode_t)__get_CPU_WORK_MODE();

    if (cpu_work_mode == MACHINE_MODE) {
        while (op_size > 0) {
            __DCACHE_CPA(op_addr);
            op_addr += linesize;
            op_size -= linesize;
        }
    } else if (cpu_work_mode == SUPERVISOR_MODE) {
        while (op_size > 0) {
            __DCACHE_CVA(op_addr);
            op_addr += linesize;
            op_size -= linesize;
        }
    }
#endif
    __SYNC_IS();
    __DSB();
#endif

}


/**
  \brief   D-Cache Clean and Invalidate by address
  \details Cleans and invalidates D_Cache for the given address
  \param[in]   addr    address (aligned to 64-byte boundary)
  \param[in]   dsize   size of memory block (aligned to 64-byte boundary)
*/
__STATIC_INLINE void csi_dcache_clean_invalid_range(unsigned long *addr, size_t dsize)
{
#if (__DCACHE_PRESENT == 1U)
    int linesize = csi_get_cache_line_size();
    long op_size = dsize + (unsigned long)addr % linesize;
    unsigned long op_addr = (unsigned long) addr;

    __DSB();
#if CBO_INSN_SUPPORT
    while (op_size > 0) {
        __CBO_FLUSH(op_addr);
        op_addr += linesize;
        op_size -= linesize;
    }
#else
    cpu_work_mode_t cpu_work_mode;
    cpu_work_mode = (cpu_work_mode_t)__get_CPU_WORK_MODE();

    if (cpu_work_mode == MACHINE_MODE) {
        while (op_size > 0) {
            __DCACHE_CIPA(op_addr);
            op_addr += linesize;
            op_size -= linesize;
        }
    } else if (cpu_work_mode == SUPERVISOR_MODE) {
        while (op_size > 0) {
            __DCACHE_CIVA(op_addr);
            op_addr += linesize;
            op_size -= linesize;
        }
    }
#endif

    __SYNC_IS();
    __DSB();
#endif
}

/*@} end of CSI_Core_CacheFunctions */

/* ##########################  FPP functions  #################################### */
/**
  \ingroup  CSI_Core_FPPFunctionInterface
  \defgroup CSI_Core_FPPFunctions FPP Functions
  \brief    Functions that configure FPP.
  @{
 */

/**
 \ingroup    CSI_fpp_register
 \defgroup   CSI_FPP
 \brief      Type definitions for the FPP Registers
 @{
 */

/**
 \brief  Consortium definition for Machine Mode FPP Configuration register(MFPPCR, 0xBC0).
 */
typedef union {
    struct {
        uint64_t EN: 1;                          /*!< bit:     0       FPP enable */
        uint64_t _reversed1: 11;                 /*!< bit:     1  11   Reserved */
        uint64_t Base_Address: 52;               /*!< bit:    12  63   Base Address */
    } b;                                         /*!< Structure        Access by bit */
    uint64_t w;                                  /*!< Type             Access by whole register */
} MFPPCR_Type;

#define MFPPCR_Base_Address_Pos          12U                                                 /*!< MFPPCR: Base_Address Position */
#define MFPPCR_Base_Address_Msk          (0xFFFFFFFFFFFFFULL << MFPPCR_Base_Address_Pos)     /*!< MFPPCR: Base_Address Mask */

#define MFPPCR_Base_EN_Pos               0U                                                  /*!< MFPPCR: Enable Bit Position */
#define MFPPCR_Base_EN_Msk               (0x1U << MFPPCR_Base_EN_Pos)                        /*!< MFPPCR: Enable Bit Mask */

/*@} end of group CSI_FPP_bitfield */

/**
  \brief   Enable FPP
  \details Turns on FPP
  */
__STATIC_INLINE void csi_fpp_enable(void)
{
    __set_MFPPCR(__get_MFPPCR() | MFPPCR_Base_EN_Msk);
}

/**
  \brief   Disable FPP
  \details Turns off FPP
  */
__STATIC_INLINE void csi_fpp_disable(void)
{
    __set_MFPPCR(__get_MFPPCR() & (~MFPPCR_Base_EN_Msk));
}

/**
  \brief   Set FPP Base Address
  \details Set FPP Base Address
  \param [in]  base_addr  FPP Base Address.
  */
__STATIC_INLINE void csi_fpp_set_base_addr(unsigned long base_addr)
{
    __set_MFPPCR((__get_MFPPCR() & (~MFPPCR_Base_Address_Msk))
        | ((base_addr << MFPPCR_Base_Address_Pos) & MFPPCR_Base_Address_Msk));
}

/*@}  end of CSI_Core_FPPFunctions */


/* ##########################  MMU functions  #################################### */
/**
  \ingroup  CSI_Core_FunctionInterface
  \defgroup CSI_Core_MMUFunctions MMU Functions
  \brief    Functions that configure MMU.
  @{
  */

typedef enum {
    PAGE_SIZE_4KB   = 0x1000,
    PAGE_SIZE_2MB   = 0x200000,
    PAGE_SIZE_1GB   = 0x40000000,
} page_size_e;

#define MMU_MODE_32   (0x1)
#define MMU_MODE_39   (0x8)
#define MMU_MODE_48   (0x9)
#define MMU_MODE_57   (0xa)
#define MMU_MODE_64   (0xb)

/**
  \brief  set mmu mode(If there are multiple mmu modes)
  \param[in]   mode    mode of the mmu
  \details
  */
__STATIC_INLINE void csi_mmu_set_mode(int mode)
{
    extern int g_mmu_mode;
    g_mmu_mode = mode;
}

/**
  \brief  enable mmu
  \details
  */
__STATIC_INLINE void csi_mmu_enable()
{
    extern int g_mmu_mode;
#if __riscv_xlen == 64
    __set_SATP(__get_SATP() | ((unsigned long)g_mmu_mode << 60));
#else
    __set_SATP(__get_SATP() | ((unsigned long)g_mmu_mode << 31));
#endif
}

/**
  \brief  disable mmu
  \details
  */
__STATIC_INLINE void csi_mmu_disable(void)
{
#if __riscv_xlen == 64
    __set_SATP(__get_SATP() & (~((unsigned long)0xf << 60)));
#else
    __set_SATP(__get_SATP() & (~((unsigned long)0x1 << 31)));
#endif
}

/**
  \brief  flush all mmu tlb.
  \details
  */
__STATIC_INLINE void csi_mmu_invalid_tlb_all(void)
{
    __ASM volatile("sfence.vma" : : : "memory");
}

/*@} end of CSI_Core_MMUFunctions */

/* ##########################  TCM functions  #################################### */
/**
  \ingroup  CSI_Core_FunctionInterface
  \defgroup CSI_Core_TCMFunctions TCM Functions
  \brief    Functions that configure TCM.
  @{
  */

#if CONFIG_CPU_XUANTIE_C907 || CONFIG_CPU_XUANTIE_C907FD || CONFIG_CPU_XUANTIE_C907FDV || CONFIG_CPU_XUANTIE_C907FDVM \
    || CONFIG_CPU_XUANTIE_C908 || CONFIG_CPU_XUANTIE_C908V || CONFIG_CPU_XUANTIE_C908I \
    || CONFIG_CPU_XUANTIE_C910V2 || CONFIG_CPU_XUANTIE_C920V2 \
    || CONFIG_CPU_XUANTIE_C910V3 || CONFIG_CPU_XUANTIE_C910V3_CP || CONFIG_CPU_XUANTIE_C920V3 || CONFIG_CPU_XUANTIE_C920V3_CP \
    || CONFIG_CPU_XUANTIE_R908 || CONFIG_CPU_XUANTIE_R908FD || CONFIG_CPU_XUANTIE_R908FDV \
    || CONFIG_CPU_XUANTIE_R908_CP || CONFIG_CPU_XUANTIE_R908FD_CP || CONFIG_CPU_XUANTIE_R908FDV_CP \
    || CONFIG_CPU_XUANTIE_R910 || CONFIG_CPU_XUANTIE_R920
/**
 \ingroup    CSI_tcm_register
 \defgroup   CSI_TCM
 \brief      Type definitions for the tcm Registers
 @{
 */

/**
 \brief  Consortium definition for accessing protection area selection register(MITCMCR, 0x7f9).
 */
typedef union {
    struct {
        unsigned long EN: 1;                             /*!< bit:     0  Instruction Tightly-Coupled Memory enable */
        unsigned long ECC_EN: 1;                         /*!< bit:     1  ecc_en */
        unsigned long Interleave: 1;                     /*!< bit:     2  Interleave */
        unsigned long _reserved1: 1;                     /*!< bit:     3  Reserved */
        unsigned long Size: 4;                           /*!< bit:  4..7  Size of ITCM */
        unsigned long _reserved2: 4;                     /*!< bit:  8..11 Reserved */
        unsigned long Base_Address: 52;                  /*!< bit: 12..63 Base address of DTCM */
    } b;                                                 /*!< Structure   Access by bit */
    unsigned long w;                                     /*!< Type        Access by whole register */
} MITCMCR_Type;

#define MITCMCR_Base_Address_Pos             12U                                                 /*!< MITCMCR: Base_Address Position */
#define MITCMCR_Base_Address_Msk             (0xfffffffffffffULL << MITCMCR_Base_Address_Pos)    /*!< MITCMCR: Base_Address Mask */

#define MITCMCR_Size_Pos                     4U                                                  /*!< MITCMCR: Size Position */
#define MITCMCR_Size_Msk                     (0xfULL << MITCMCR_Size_Pos)                        /*!< MITCMCR: Size Mask */

#define MITCMCR_INTERLEAVE_Pos               2U                                                  /*!< MITCMCR: Interleave Position */
#define MITCMCR_INTERLEAVE_Msk               (0x1ULL << MITCMCR_INTERLEAVE_Pos)                  /*!< MITCMCR: Interleave Mask */

#define MITCMCR_ECC_EN_Pos                   1U                                                  /*!< MITCMCR: ECC_EN Position */
#define MITCMCR_ECC_EN_Msk                   (0x1ULL << MITCMCR_ECC_EN_Pos)                      /*!< MITCMCR: ECC_EN Mask */

#define MITCMCR_EN_Pos                       0U                                                  /*!< MITCMCR: EN Position */
#define MITCMCR_EN_Msk                       (0x1ULL << MITCMCR_EN_Pos)                          /*!< MITCMCR: EN Mask */

/**
 \brief  Consortium definition for accessing protection area selection register(MDTCMCR, 0x7f8).
 */
typedef union {
    struct {
        unsigned long EN: 1;                             /*!< bit:     0  Data Tightly-Coupled Memory enable */
        unsigned long ECC_EN: 1;                         /*!< bit:     1  ecc_en */
        unsigned long Interleave: 1;                     /*!< bit:     2  Interleave */
        unsigned long _reserved1: 1;                     /*!< bit:     3  Reserved */
        unsigned long Size: 4;                           /*!< bit:  4..7  Size of ITCM */
        unsigned long _reserved2: 4;                     /*!< bit:  8..11 Reserved */
        unsigned long Base_Address: 52;                  /*!< bit: 12..63 Base address of DTCM */
    } b;                                                 /*!< Structure   Access by bit */
    unsigned long w;                                     /*!< Type        Access by whole register */
} MDTCMCR_Type;

#define MDTCMCR_Base_Address_Pos             12U                                                 /*!< MDTCMCR: Base_Address Position */
#define MDTCMCR_Base_Address_Msk             (0xfffffffffffffULL << MDTCMCR_Base_Address_Pos)    /*!< MDTCMCR: Base_Address Mask */

#define MDTCMCR_Size_Pos                     4U                                                  /*!< MDTCMCR: Size Position */
#define MDTCMCR_Size_Msk                     (0xfULL << MDTCMCR_Size_Pos)                        /*!< MDTCMCR: Size Mask */

#define MDTCMCR_INTERLEAVE_Pos               2U                                                  /*!< MDTCMCR: Interleave Position */
#define MDTCMCR_INTERLEAVE_Msk               (0x1ULL << MDTCMCR_INTERLEAVE_Pos)                  /*!< MDTCMCR: Interleave Mask */

#define MDTCMCR_ECC_EN_Pos                   1U                                                  /*!< MDTCMCR: ECC_EN Position */
#define MDTCMCR_ECC_EN_Msk                   (0x1ULL << MDTCMCR_ECC_EN_Pos)                      /*!< MDTCMCR: ECC_EN Mask */

#define MDTCMCR_EN_Pos                       0U                                                  /*!< MDTCMCR: EN Position */
#define MDTCMCR_EN_Msk                       (0x1ULL << MDTCMCR_EN_Pos)                          /*!< MDTCMCR: EN Mask */

/*@} end of group CSI_TCM_bitfield */

/**
  \brief   Enable ITCM
  \details Turns on ITCM
  */
__STATIC_INLINE void csi_itcm_enable (void)
{
    __set_MITCMCR(__get_MITCMCR() | MITCMCR_EN_Msk);
}

/**
  \brief   Enable DTCM
  \details Turns on DTCM
  */
__STATIC_INLINE void csi_dtcm_enable (void)
{
    __set_MDTCMCR(__get_MDTCMCR() | MDTCMCR_EN_Msk);
}

/**
  \brief   Enable ITCM
  \details Turns on ITCM
  */
__STATIC_INLINE void csi_itcm_disable (void)
{
    __set_MITCMCR(__get_MITCMCR() & (~MITCMCR_EN_Msk));
}

/**
  \brief   Enable DTCM
  \details Turns on DTCM
  */
__STATIC_INLINE void csi_dtcm_disable (void)
{
    __set_MDTCMCR(__get_MDTCMCR() & (~MDTCMCR_EN_Msk));
}

/**
  \brief   Get ITCM Size
  \details Get ITCM Size
  \return         ITCM size (bytes).
  */
__STATIC_INLINE uint32_t csi_itcm_get_size(void)
{
    MITCMCR_Type sizemask;
    uint32_t ret;

    sizemask.w = __get_MITCMCR();
    switch (sizemask.b.Size)
    {
        case 0x3: ret = 8 << 10; break;
        case 0x4: ret = 16 << 10; break;
        case 0x5: ret = 32 << 10; break;
        case 0x6: ret = 64 << 10; break;
        case 0x7: ret = 128 << 10; break;
        case 0x8: ret = 256 << 10; break;
        case 0x9: ret = 512 << 10; break;
        case 0xa: ret = 1024 << 10; break;
        default: ret = 0; break;
    }
    return ret;
}

/**
  \brief   Get DTCM Size
  \details Get DTCM Size
  \return         DTCM size (bytes).
  */
__STATIC_INLINE uint32_t csi_dtcm_get_size(void)
{
    MDTCMCR_Type sizemask;
    uint32_t ret;

    sizemask.w = __get_MDTCMCR();
    switch (sizemask.b.Size)
    {
        case 0x3: ret = 8 << 10; break;
        case 0x4: ret = 16 << 10; break;
        case 0x5: ret = 32 << 10; break;
        case 0x6: ret = 64 << 10; break;
        case 0x8: ret = 128 << 10; break;
        case 0x9: ret = 256 << 10; break;
        case 0xa: ret = 512 << 10; break;
        case 0xb: ret = 1024 << 10; break;
        default:ret = 0; break;
    }
    return ret;
}

/**
  \brief   Set ITCM Base Address
  \details Set ITCM Base Address
  \param [in]  base_addr  itcm base address.
  */
__STATIC_INLINE void csi_itcm_set_base_addr(unsigned long base_addr)
{
    __set_MITCMCR((__get_MITCMCR() & (~MITCMCR_Base_Address_Msk)) | (base_addr << MITCMCR_Base_Address_Pos));
}

/**
  \brief   Set DTCM Base Address
  \details Set DTCM Base Address
  \param [in]  base_addr  dtcm base address.
  */
__STATIC_INLINE void csi_dtcm_set_base_addr(unsigned long base_addr)
{
    __set_MDTCMCR((__get_MDTCMCR() & (~MDTCMCR_Base_Address_Msk)) | (base_addr << MDTCMCR_Base_Address_Pos));
}

/*@} end of CSI_Core_TCMFunctions */

/* ##########################  ECC functions  #################################### */

/**
 *   \brief   Enable ITCM-ECC
 *     \details Turns on ITCM-ECC
 *       */
__STATIC_INLINE void csi_itcm_ecc_enable (void)
{
    __set_MITCMCR(__get_MITCMCR() | MITCMCR_ECC_EN_Msk);
}

/**
 *   \brief   Disable ITCM-ECC
 *     \details Turns off ITCM-ECC
 *       */
__STATIC_INLINE void csi_itcm_ecc_disable (void)
{
    __set_MITCMCR(__get_MITCMCR() & (~MITCMCR_ECC_EN_Msk));
}

/**
 *   \brief   Enable DTCM-ECC
 *     \details Turns on DTCM-ECC
 *       */
__STATIC_INLINE void csi_dtcm_ecc_enable (void)
{
    __set_MDTCMCR(__get_MDTCMCR() | MDTCMCR_ECC_EN_Msk);
}

/**
 *   \brief   Disable DTCM-ECC
 *     \details Turns off DTCM-ECC
 *       */
__STATIC_INLINE void csi_dtcm_ecc_disable (void)
{
    __set_MDTCMCR(__get_MDTCMCR() & (~MDTCMCR_ECC_EN_Msk));
}

/*@} end of CSI_Core_ECCFunctions */
#endif /* end ecc */

/* ##################################    IRQ Functions  ############################################ */

/**
  \brief   Save the Irq context
  \details save the psr result before disable irq.
 */
__STATIC_INLINE unsigned long csi_irq_save(void)
{
    unsigned long result;
#if defined(CONFIG_RISCV_SMODE) && CONFIG_RISCV_SMODE
    result = __get_SSTATUS();
#else
    result = __get_MSTATUS();
#endif
    __disable_irq();
    return(result);
}

/**
  \brief   Restore the Irq context
  \details restore saved primask state.
  \param [in]      irq_state  psr irq state.
 */
__STATIC_INLINE void csi_irq_restore(unsigned long irq_state)
{
#if defined(CONFIG_RISCV_SMODE) && CONFIG_RISCV_SMODE
    __set_SSTATUS(irq_state);
#else
    __set_MSTATUS(irq_state);
#endif
}

/*@} end of IRQ Functions */

/**
  \brief   Get the byte-width of vector register
  \return  the byte-width of vector register
 */
__STATIC_INLINE int csi_vlenb_get_value(void)
{
    int result;
    __ASM volatile("csrr %0, vlenb" : "=r"(result) : : "memory");
    return result;
}

#if __riscv_matrix || __riscv_xtheadmatrix
/**
  \brief   Get the bytes of matrix per register
  \return  the bytes of matrix per register
 */
__STATIC_INLINE int csi_xmlenb_get_value(void)
{
    int result;
    __ASM volatile("csrr %0, xmlenb" : "=r"(result) : : "memory");
    return result;
}
#endif /* __riscv_matrix || __riscv_xtheadmatrix */

#ifdef __cplusplus
}
#endif

#endif /* __CORE_RV32_H_DEPENDANT */

#endif /* __CSI_GENERIC */
