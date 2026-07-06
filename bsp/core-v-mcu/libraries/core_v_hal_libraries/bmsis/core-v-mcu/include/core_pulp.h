/**************************************************************************//**
 * @file     core_pulp.h
 * @brief    CMSIS PULP Core Peripheral Access Layer Header File
 * @version  V0.0.1
 * @date     04. April 2020
 ******************************************************************************/
/*
 * Copyright (c) 2017 GreenWaves Technologies SAS. All rights reserved.
 * Copyright (c) 2020 ETH Zurich
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef __CORE_PULP_H_GENERIC__
#define __CORE_PULP_H_GENERIC__

#include <stdint.h>
#include <assert.h>
#include "core-v-mcu-memory-map.h"

#include "pmsis_gcc.h"
#include "csr.h"
#include "bits.h"
#include "pulp_io.h"
#include "core-v-mcu-periph.h"


#ifdef __cplusplus
 extern "C" {
#endif

/*******************************************************************************
 *                 CMSIS definitions
 ******************************************************************************/
/**
  \ingroup PULP
  @{
 */

/*  CMSIS PULP definitions */
#define __PULP_CMSIS_VERSION_MAIN  ( 5U)                                  /*!< [31:16] CMSIS HAL main version */
#define __PULP_CMSIS_VERSION_SUB   ( 0U)                                  /*!< [15:0]  CMSIS HAL sub version */
#define __PULP_CMSIS_VERSION       ((__PULP_CMSIS_VERSION_MAIN << 16U) | \
				    __PULP_CMSIS_VERSION_SUB           )  /*!< CMSIS HAL version number */

#define __PULP_V                   (1U)                                   /*!< PULP Core Version */

#include "pmsis_gcc.h"               /* CMSIS compiler specific defines */


#ifdef __cplusplus
}
#endif

#endif /* __CORE_PULP_H_GENERIC */

#ifndef __CMSIS_GENERIC

#ifndef __CORE_PULP_H_DEPENDANT
#define __CORE_PULP_H_DEPENDANT

#ifdef __cplusplus
 extern "C" {
#endif

/* check device defines and use defaults */
#if defined __CHECK_DEVICE_DEFINES
  #ifndef __PULP_REV
    #define __PULP_REV               0x0000U
    #warning "__PULP_REV not defined in device header file; using default!"
  #endif

  #ifndef __FPU_PRESENT
    #define __FPU_PRESENT             0U
    #warning "__FPU_PRESENT not defined in device header file; using default!"
  #endif

  #ifndef __MPU_PRESENT
    #define __MPU_PRESENT             0U
    #warning "__MPU_PRESENT not defined in device header file; using default!"
  #endif

  #ifndef __NVIC_PRIO_BITS
    #define __NVIC_PRIO_BITS          0U
    #warning "__NVIC_PRIO_BITS not defined in device header file; using default!"
  #endif

  #ifndef __Vendor_SysTickConfig
    #define __Vendor_SysTickConfig    0U
    #warning "__Vendor_SysTickConfig not defined in device header file; using default!"
  #endif
#endif

/* IO definitions (access restrictions to peripheral registers) */
/**
    \defgroup CMSIS_glob_defs CMSIS Global Defines

    <strong>IO Type Qualifiers</strong> are used
    \li to specify the access to peripheral variables.
    \li for automatic generation of peripheral register debug information.
*/
#ifdef __cplusplus
  #define   __I     volatile             /*!< Defines 'read only' permissions */
#else
  #define   __I     volatile const       /*!< Defines 'read only' permissions */
#endif
#define     __O     volatile             /*!< Defines 'write only' permissions */
#define     __IO    volatile             /*!< Defines 'read / write' permissions */

/* following defines should be used for structure members */
#define     __IM     volatile const      /*! Defines 'read only' structure member permissions */
#define     __OM     volatile            /*! Defines 'write only' structure member permissions */
#define     __IOM    volatile            /*! Defines 'read / write' structure member permissions */

/*@} end of group PULP */

/*******************************************************************************
 *                 Register Abstraction
  Core Register contain:
  - Core Register
  - Core NVIC Register
  - Core SCB Register
  - Core SysTick Register
  - Core Debug Register
  - Core MPU Register
  - Core FPU Register
******************************************************************************/
/**
   \defgroup CMSIS_core_register Defines and Type Definitions
   \brief Type definitions and defines for PULP processor based devices.
*/

/**
  \ingroup    CMSIS_core_register
  \defgroup   CMSIS_CORE  Status and Control Registers
  \brief      Core Register type definitions.
  @{
 */
#define MSTATUS_ADDR    0x300             /*!< Machine Status Register */
#define MISA_ADDR       0x301             /*!< ISA and Extensions Register */
#define MIE_ADDR	0x304             /*!< Machine interrupt enable Register */
#define MTVEC_ADDR      0x305             /*!< Machine Trap-handler Base Address Register */
#define MSCRATCH_ADDR   0x340             /*!< Machine Scratch Register */
#define MEPC_ADDR       0x341             /*!< Machine Exception Program Counter Register */
#define MCAUSE_ADDR     0x342             /*!< Machine Trap Cause Register */
#define MTVAL_ADDR      0x343             /*!< Machine Trap Value Register */
#define MIP_ADDR        0x344             /*!< Machine Interrupt Pending Register */
#define PMPCFG0_ADDR    0x3a0             /*!< PMP Configuration Register 0 */
#define PMPADDR0_ADDR   0x3b0             /*!< PMP Address Register 0 */

#define MVENDORID_ADDR  0xF11             /*!< Vendor ID Register */
#define MARCHID_ADDR    0xF12             /*!< Architecture ID Register */
#define MIMPID_ADDR     0xF13             /*!< Implementation ID Register */
#define MHARTID_ADDR    0xF14             /*!< Hardware Thread ID Register */

#define PCER_ADDR       0x7E0             /*!< Performance Counter Event Register */
#define PCMR_ADDR       0x7E1             /*!< Performance Counter Mode Register */

/* #ifndef ASIC */
#define PERF_CYCLE_OFFSET      0x00       /*!< Performance Counter Counter CYCLE Register */
#define PERF_INSTR_OFFSET      0x01       /*!< Performance Counter Counter INSTR Register */
#define PERF_LD_STALL_OFFSET   0x02       /*!< Performance Counter Counter LD_STALL Register */
#define PERF_JR_STALL_OFFSET   0x03       /*!< Performance Counter Counter JR_STALL Register */
#define PERF_IMISS_OFFSET      0x04       /*!< Performance Counter Counter IMISS Register */
#define PERF_LD_OFFSET         0x05       /*!< Performance Counter Counter LD Register */
#define PERF_ST_OFFSET         0x06       /*!< Performance Counter Counter ST Register */
#define PERF_JUMP_OFFSET       0x07       /*!< Performance Counter Counter JUMP Register */
#define PERF_BRANCH_OFFSET     0x08       /*!< Performance Counter Counter BRANCH Register */
#define PERF_BTAKEN_OFFSET     0x09       /*!< Performance Counter Counter BTAKEN Register */
#define PERF_RVC_OFFSET        0x0A       /*!< Performance Counter Counter RVC Register */
#define PERF_LD_EXT_OFFSET     0x0B       /*!< Performance Counter Counter LD_EXT Register */
#define PERF_ST_EXT_OFFSET     0x0C       /*!< Performance Counter Counter ST_EXT Register */
#define PERF_LD_EXT_CYC_OFFSET 0x0D       /*!< Performance Counter Counter LD_EXT_CYC Register */
#define PERF_ST_EXT_CYC_OFFSET 0x0E       /*!< Performance Counter Counter ST_EXT_CYC Register */
#define PERF_TCDM_COUNT_OFFSET 0x0F       /*!< Performance Counter Counter TCDM_CONT Register */
/* #endif */
#define PERF_ALL_OFFSET        0x1F       /*!< Performance Counter Counter ALL Register, used to reset all counters */

#define PCCR_ADDR(x)    (0x780 + x)       /*!< Performance Counter Counter access */

#define HWLP_S0_ADDR    0x7C0             /*!< Hardware Loop Start0 Register */
#define HWLP_E0_ADDR    0x7C1             /*!< Hardware Loop End0 Register */
#define HWLP_C0_ADDR    0x7C2             /*!< Hardware Loop Count0 Register */
#define HWLP_S1_ADDR    0x7C3             /*!< Hardware Loop Start1 Register */
#define HWLP_E1_ADDR    0x7C4             /*!< Hardware Loop End1 Register */
#define HWLP_C1_ADDR    0x7C5             /*!< Hardware Loop Count1 Register */

#define UEPC_ADDR       0x041             /*!< User Exception Program Counter Register */
#define CPRIV_ADDR      0xC10             /*!< Current Privilege Level Register (unofficial) */
#define UCAUSE_ADDR     0x042             /*!< FC User Trap Cause Register */

/**
  \brief  Union type to access the Vendor ID Register (MVENDORID).
 */
typedef union
{
  struct
  {
    uint32_t OFFSET:7;                   /*!< bit:  0..6   */
    uint32_t BANK:25;                    /*!< bit:  7..31  */
  } b;                                   /*!< Structure used for bit  access */
  uint32_t w;                            /*!< Type      used for word access */
} MVENDORID_Type;

/* MVENDORID Register Definitions */
#define MVENDORID_BANK_Pos                 7U                                            /*!< MVENDORID: BANK Position */
#define MVENDORID_BANK_Msk                 (0x1FFFFFFUL /*<< MVENDORID_BANK_Pos*/)       /*!< MVENDORID: BANK Mask */

#define MVENDORID_OFFSET_Pos               0U                                            /*!< MVENDORID: OFFSET Position */
#define MVENDORID_OFFSET_Msk               (0x7FUL /*<< MVENDORID_OFFSET_Pos*/)          /*!< MVENDORID: OFFSET Mask */


/**
  \brief  Union type to access the Hart ID Register (MHARTID).
 */
typedef union
{
  struct
  {
    uint32_t OFFSET:5;                   /*!< bit:  0..4  Hardware thread id */
    uint32_t BANK:27;                    /*!< bit:  5..31 Reserved */
  } b;                                   /*!< Structure used for bit  access */
  uint32_t w;                            /*!< Type      used for word access */
} MHARTID_Type;

/* MHARTID Register Definitions */
#define MHARTID_BANK_Pos                 0U                                            /*!< MHARTID: BANK Position */
#define MHARTID_BANK_Msk                 (0x1FUL /*<< MHARTID_BANK_Pos*/)              /*!< MHARTID: BANK Mask */


/**
  \brief  Union type to access the ISA and Extensions Register (MISA).
 */
typedef union
{
  struct
  {
    uint32_t EXTENSION:26;               /*!< bit:  0.. 25  ISA Extension */
    uint32_t WIRI:4;                     /*!< bit:  26..29  Reserved */
    uint32_t MXL:2;                      /*!< bit:  30..31  Machine XLEN */
  } b;                                   /*!< Structure used for bit  access */
  uint32_t w;                            /*!< Type      used for word access */
} MISA_Type;

/* MISA Register Definitions */
#define MISA_MXL_Pos                       30U                                          /*!< MISA: MXL Position */
#define MISA_MXL_Msk                       (0x3UL << MISA_MXL_Pos)                      /*!< MISA: MXL Mask */

#define MISA_EXTENSION_Pos                 0U                                           /*!< MISA: EXTENSION Position */
#define MISA_EXTENSION_Msk                 (0x3FFFFFFUL /*<< MISA_EXTENSION_Pos*/)      /*!< MISA: EXTENSION Mask */


/**
   \brief  Union type to access the Machine Mode Status Register (MSTATUS).
*/
typedef union
{
  struct
  {
    uint32_t UIE:1;                      /*!< bit:  0       User Interrupt-enable bit */
    uint32_t SIE:1;                      /*!< bit:  1       Supervisor Interrupt-enable bit */
    uint32_t WPRI0:1;                    /*!< bit:  2       Reserved */
    uint32_t MIE:1;                      /*!< bit:  3       Machine Interrupt-enable bit */
    uint32_t UPIE:1;                     /*!< bit:  4       Prior User Interrupt-enable bit on trap */
    uint32_t SPIE:1;                     /*!< bit:  5       Prior Supervisor Interrupt-enable bit on trap */
    uint32_t WPRI1:1;                    /*!< bit:  6       Reserved */
    uint32_t MPIE:1;                     /*!< bit:  7       Prior Machine Interrupt-enable bit on trap */
    uint32_t SPP:1;                      /*!< bit:  8       Supervisor previous privilege value, up to supervisor mode*/
    uint32_t WPRI2:2;                    /*!< bit:  9, 10   Reserved */
    uint32_t MPP:2;                      /*!< bit:  11, 12  Supervise previous privilege value, up to machine mode */
    uint32_t FS:2;                       /*!< bit:  13, 14  Reserved */
    uint32_t XS:2;                       /*!< bit:  15, 16  Reserved */
    uint32_t MPRV:1;                     /*!< bit:  17      Reserved */
    uint32_t SUM:1;                      /*!< bit:  18      Reserved */
    uint32_t MXR:1;                      /*!< bit:  19      Reserved */
    uint32_t TVM:1;                      /*!< bit:  20      Reserved */
    uint32_t TW:1;                       /*!< bit:  21      Reserved */
    uint32_t TSR:1;                      /*!< bit:  22      Reserved */
    uint32_t WPRI3:8;                    /*!< bit:  23..30  Reserved */
    uint32_t SD:1;                       /*!< bit:  31      Reserved */
  } b;                                   /*!< Structure used for bit  access */
  uint32_t w;                            /*!< Type      used for word access */
} MSTATUS_Type;


/* MSTATUS Register Definitions */
#define MSTATUS_SD_Pos                         31U                                            /*!< MSTATUS: SD Position */
#define MSTATUS_SD_Msk                         (1UL << MSTATUS_SD_Pos)                        /*!< MSTATUS: SD Mask */

#define MSTATUS_TSR_Pos                        22U                                            /*!< MSTATUS: TSR Position */
#define MSTATUS_TSR_Msk                        (1UL << MSTATUS_TSR_Pos)                       /*!< MSTATUS: TSR Mask */

#define MSTATUS_TW_Pos                         21U                                            /*!< MSTATUS: TW Position */
#define MSTATUS_TW_Msk                         (1UL << MSTATUS_TW_Pos)                        /*!< MSTATUS: TW Mask */

#define MSTATUS_TVM_Pos                        20U                                            /*!< MSTATUS: TVM Position */
#define MSTATUS_TVM_Msk                        (1UL << MSTATUS_TVM_Pos)                       /*!< MSTATUS: TVM Mask */

#define MSTATUS_MXR_Pos                        19U                                            /*!< MSTATUS: MXR Position */
#define MSTATUS_MXR_Msk                        (1UL << MSTATUS_MXR_Pos)                       /*!< MSTATUS: MXR Mask */

#define MSTATUS_SUM_Pos                        18U                                            /*!< MSTATUS: SUM Position */
#define MSTATUS_SUM_Msk                        (1UL << MSTATUS_SUM_Pos)                       /*!< MSTATUS: SUM Mask */

#define MSTATUS_MPRV_Pos                       17U                                            /*!< MSTATUS: MPRV Position */
#define MSTATUS_MPRV_Msk                       (1UL << MSTATUS_MPRV_Pos)                      /*!< MSTATUS: MPRV Mask */

#define MSTATUS_XS_Pos                         15U                                            /*!< MSTATUS: XS Position */
#define MSTATUS_XS_Msk                         (3UL << MSTATUS_XS_Pos)                        /*!< MSTATUS: XS Mask */

#define MSTATUS_FS_Pos                         13U                                            /*!< MSTATUS: FS Position */
#define MSTATUS_FS_Msk                         (3UL << MSTATUS_FS_Pos)                        /*!< MSTATUS: FS Mask */

#define MSTATUS_MPP_Pos                        11U                                            /*!< MSTATUS: MPP Position */
#define MSTATUS_MPP_Msk                        (3UL << MSTATUS_MPP_Pos)                       /*!< MSTATUS: MPP Mask */

#define MSTATUS_SPP_Pos                        8U                                             /*!< MSTATUS: SPP Position */
#define MSTATUS_SPP_Msk                        (1UL << MSTATUS_SPP_Pos)                       /*!< MSTATUS: SPP Mask */

#define MSTATUS_MPIE_Pos                       7U                                             /*!< MSTATUS: MPIE Position */
#define MSTATUS_MPIE_Msk                       (1UL << MSTATUS_MPIE_Pos)                      /*!< MSTATUS: MPIE Mask */

#define MSTATUS_SPIE_Pos                       5U                                             /*!< MSTATUS: SPIE Position */
#define MSTATUS_SPIE_Msk                       (1UL << MSTATUS_SPIE_Pos)                      /*!< MSTATUS: SPIE Mask */

#define MSTATUS_UPIE_Pos                        4U                                            /*!< MSTATUS: UPIE Position */
#define MSTATUS_UPIE_Msk                        (1UL << MSTATUS_UPIE_Pos)                     /*!< MSTATUS: UPIE Mask */

#define MSTATUS_MIE_Pos                         3U                                            /*!< MSTATUS: MIE Position */
#define MSTATUS_MIE_Msk                         (1UL << MSTATUS_MIE_Pos)                      /*!< MSTATUS: MIE Mask */

#define MSTATUS_SIE_Pos                         1U                                            /*!< MSTATUS: SIE Position */
#define MSTATUS_SIE_Msk                         (1UL << MSTATUS_SIE_Pos)                      /*!< MSTATUS: SIE Mask */

#define MSTATUS_UIE_Pos                         0U                                            /*!< MSTATUS: UIE Position */
#define MSTATUS_UIE_Msk                         (1UL /* << MSTATUS_UIE_Pos */)                /*!< MSTATUS: UIE Mask */

/**
  \brief  Union type to access the Machine Trap-Vector Baser-Address Register (MTVEC).
 */
typedef union
{
  struct
  {
    uint32_t MODE:2;                     /*!< bit:  0..1  vector mode */
    uint32_t BASE:30;                    /*!< bit:  2..31 vector base address */
  } b;                                   /*!< Structure used for bit  access */
  uint32_t w;                            /*!< Type      used for word access */
} MTVEC_Type;

/* MTVEC Register Definitions */
#define MTVEC_BASE_Pos                 2U                                            /*!< MTVEC: BASE Position */
#define MTVEC_BASE_Msk                 (0x3FFFFFFFUL << MTVEC_BASE_Pos)              /*!< MTVEC: BASE Mask */

#define MTVEC_MODE_Pos                 0U                                            /*!< MTVEC: MODE Position */
#define MTVEC_MODE_Msk                 (0x3UL /*<< MTVEC_MODE_Pos*/)                 /*!< MTVEC: MODE Mask */


/**
  \brief  Union type to access the Machine Trap Cause Register (MCAUSE).
 */
typedef union
{
  struct
  {
    uint32_t EC:31;                       /*!< bit: 0..30  Exception code */
    uint32_t IRQ:1;                      /*!< bit:  31 Interrupt flag */
  } b;                                   /*!< Structure used for bit  access */
  uint32_t w;                            /*!< Type      used for word access */
} MCAUSE_Type;

/* MCAUSE Register Definitions */
#define MCAUSE_IRQ_Pos                31U                                            /*!< MCAUSE: IRQ Position */
#define MCAUSE_IRQ_Msk                (0x1UL << MCAUSE_IRQ_Pos)                      /*!< MCAUSE: IRQ Mask */

#define MCAUSE_EC_Pos                 0U                                             /*!< MCAUSE: EC Position */
#define MCAUSE_EC_Msk                 (0x1FFFFFFFUL /*<< MCAUSE_EC_Pos*/)                  /*!< MCAUSE: EC Mask */


/**
  \brief  Union type to access the Current Privilege Level Register (CPRIV).
 */
typedef union
{
  struct
  {
    uint32_t PRIV:2;                     /*!< bit:  0..1  Current privilege level */
    uint32_t _reserved0:30;               /*!< bit:  2..31 Reserved */
  } b;                                   /*!< Structure used for bit  access */
  uint32_t w;                            /*!< Type      used for word access */
} CPRIV_Type;

/* CPRIV Register Definitions */
#define CPRIV_PRIV_Pos                 0U                                            /*!< CPRIV: PRIV Position */
#define CPRIV_PRIV_Msk                 (0x3UL /*<< CPRIV_PRIV_Pos*/)                 /*!< CPRIV: PRIV Mask */


/**
  \brief  Union type to access the Performance Counter Mode Register (PCMR).
 */
typedef union
{
  struct
  {
    uint32_t GLBEN:1;                    /*!< bit:  0  Enbable all Performance counter */
    uint32_t SATU:1;                     /*!< bit:  1  Use saturating arithmetic */
    uint32_t _reserved0:30;              /*!< bit:  2..31 Reserved */
  } b;                                   /*!< Structure used for bit  access */
  uint32_t w;                            /*!< Type      used for word access */
} PCMR_Type;

/* PCMR Register Definitions */
#define PCMR_GLBEN_Pos                 0U                                            /*!< PCMR: GLBEN Position */
#define PCMR_GLBEN_Msk                 (0x1UL /*<< PCMR_GLBEN_Pos*/)                 /*!< PCMR: GLBEN Mask */

#define PCMR_SATU_Pos                  1U                                            /*!< PCMR: SATU Position */
#define PCMR_SATU_Msk                  (0x1UL << PCMR_SATU_Pos)                 /*!< PCMR: SATU Mask */


/**
  \brief  Union type to access the Performance Counter Event Register (PCER).
 */
typedef union
{
  struct
  {
    uint32_t CYCLE:1;                     /*!< bit:  0  CYCLE */
    uint32_t INSTR:1;                     /*!< bit:  1  INSTR */
    uint32_t LD_STALL:1;                  /*!< bit:  2  LD_STALL */
    uint32_t JMP_STALL:1;                 /*!< bit:  3  JMP_STALL */
    uint32_t IMISS:1;                     /*!< bit:  4  IMISS */
    uint32_t WBRANCH:1;                   /*!< bit:  5  WBRANCH */
    uint32_t WBRANCH_CYC:1;               /*!< bit:  6  WBRANCH_CYC */
    uint32_t LD:1;                        /*!< bit:  7  LD */
    uint32_t ST:1;                        /*!< bit:  8  ST */
    uint32_t JUMP:1;                      /*!< bit:  9  JUMP */
    uint32_t BRANCH:1;                    /*!< bit:  10  BRANCH */
    uint32_t DELAY_SLOT:1;                /*!< bit:  11  DELAY_SLOT */
    uint32_t LD_EXT:1;                    /*!< bit:  12  LD_EXT */
    uint32_t ST_EXT:1;                    /*!< bit:  13  ST_EXT */
    uint32_t LD_EXT_CYC:1;                /*!< bit:  14  LD_EXT_CYC */
    uint32_t ST_EXT_CYC:1;                /*!< bit:  15  ST_EXT_CYC */
    uint32_t TCDM_CONT:1;                 /*!< bit:  16  TCDM_CONT */
    uint32_t _reserved0:15;               /*!< bit:  17..31 Reserved */
  } b;                                    /*!< Structure used for bit  access */
  uint32_t w;                             /*!< Type      used for word access */
} PCER_Type;

/* PCER Register Definitions */
#define PCER_CYCLE_Pos                 0U                                            /*!< PCER: CYCLE Position */
#define PCER_CYCLE_Msk                 (0x1UL /*<< PCER_CYCLE_Pos*/)                 /*!< PCER: CYCLE Mask */

#define PCER_INSTR_Pos                 1U                                            /*!< PCER: _INSTR Position */
#define PCER_INSTR_Msk                 (0x1UL << PCER_INSTR_Pos)                     /*!< PCER: _INSTR Mask */

#define PCER_LD_STALL_Pos              2U                                            /*!< PCER: LD_STALL Position */
#define PCER_LD_STALL_Msk              (0x1UL << PCER_LD_STALL_Pos)                  /*!< PCER: LD_STALL Mask */

#define PCER_JMP_STALL_Pos             3U                                            /*!< PCER: JMP_STALL Position */
#define PCER_JMP_STALL_Msk             (0x1UL << PCER_JMP_STALL_Pos)                 /*!< PCER: JMP_STALL Mask */

#define PCER_IMISS_Pos                 4U                                            /*!< PCER: IMISS Position */
#define PCER_IMISS_Msk                 (0x1UL << PCER_IMISS_Pos)                     /*!< PCER: IMISS Mask */

#define PCER_WBRANCH_Pos               5U                                            /*!< PCER: WBRANCH Position */
#define PCER_WBRANCH_Msk               (0x1UL << PCER_WBRANCH_Pos)                   /*!< PCER: WBRANCH Mask */

#define PCER_WBRANCH_CYC_Pos           6U                                            /*!< PCER: WBRANCH_CYC Position */
#define PCER_WBRANCH_CYC_Msk           (0x1UL << PCER_WBRANCH_CYC_Pos)               /*!< PCER: WBRANCH_CYC Mask */

#define PCER_LD_Pos                    7U                                            /*!< PCER: LD Position */
#define PCER_LD_Msk                    (0x1UL << PCER_LD_Pos)                        /*!< PCER: LD Mask */

#define PCER_ST_Pos                    8U                                            /*!< PCER: ST Position */
#define PCER_ST_Msk                    (0x1UL << PCER_ST_Pos)                        /*!< PCER: ST Mask */

#define PCER_JUMP_Pos                  9U                                            /*!< PCER: JUMP Position */
#define PCER_JUMP_Msk                  (0x1UL << PCER_JUMP_Pos)                      /*!< PCER: JUMP Mask */

#define PCER_BRANCH_Pos                10U                                           /*!< PCER: BRANCH Position */
#define PCER_BRANCH_Msk                (0x1UL << PCER_BRANCH_Pos)                    /*!< PCER: BRANCH Mask */

#define PCER_DELAY_SLOT_Pos            11U                                           /*!< PCER: DELAY_SLOT Position */
#define PCER_DELAY_SLOT_Msk            (0x1UL << PCER_DELAY_SLOT_Pos)                /*!< PCER: DELAY_SLOT Mask */

#define PCER_LD_EXT_Pos                12U                                           /*!< PCER: LD_EXT Position */
#define PCER_LD_EXT_Msk                (0x1UL << PCER_LD_EXT_Pos)                    /*!< PCER: LD_EXT Mask */

#define PCER_ST_EXT_Pos                13U                                           /*!< PCER: ST_EXT Position */
#define PCER_ST_EXT_Msk                (0x1UL << PCER_ST_EXT_Pos)                    /*!< PCER: ST_EXT Mask */

#define PCER_LD_EXT_CYC_Pos            14U                                           /*!< PCER: LD_EXT_CYC Position */
#define PCER_LD_EXT_CYC_Msk            (0x1UL << PCER_LD_EXT_CYC_Pos)                /*!< PCER: LD_EXT_CYC Mask */

#define PCER_ST_EXT_CYC_Pos            15U                                           /*!< PCER: ST_EXT_CYC Position */
#define PCER_ST_EXT_CYC_Msk            (0x1UL << PCER_ST_EXT_CYC_Pos)                /*!< PCER: ST_EXT_CYC Mask */

#define PCER_TCDM_CONT_Pos             16U                                           /*!< PCER: TCDM_CONT Position */
#define PCER_TCDM_CONT_Msk             (0x1UL << PCER_TCDM_CONT_Pos)                 /*!< PCER: TCDM_CONT Mask */

#define PCER_EVENTS_NUM                17U                                           /*!< PCER: All events number */
/*@} end of group CMSIS_CORE */




/**
  \ingroup    CMSIS_core_register
  \defgroup   CMSIS_NVIC  Nested Vectored Interrupt Controller (NVIC)
  \brief      Type definitions for the NVIC Registers
  @{
*/

/**
  \brief  Structure type to access the Nested Vectored Interrupt Controller (NVIC).
 */
typedef struct
{
  __IOM  uint32_t MASK;                    /**< Interrupt Controller mask register, offset: 0x00 */
  __IOM  uint32_t MASK_SET;                /**< Interrupt Controller mask set register, offset: 0x04 */
  __IOM  uint32_t MASK_CLEAR;              /**< Interrupt Controller mask clear register, offset: 0x08 */
  __IOM  uint32_t IRQ;                     /**< Interrupt Controller irq register, offset: 0x0C */
  __IOM  uint32_t IRQ_SET;                 /**< Interrupt Controller irq set register, offset: 0x10 */
  __IOM  uint32_t IRQ_CLEAR;               /**< Interrupt Controller irq clear register, offset: 0x14 */
  __IOM  uint32_t ACK;                     /**< Interrupt Controller ack register, offset: 0x18 */
  __IOM  uint32_t ACK_SET;                 /**< Interrupt Controller ack set register, offset: 0x1C */
  __IOM  uint32_t ACK_CLEAR;               /**< Interrupt Controller ack clear register, offset: 0x20 */
  __IOM  uint32_t FIFO;                    /**< Interrupt Controller soc event fifo register, offset: 0x24 */
}  NVIC_Type;
/*@} end of group CMSIS_NVIC */

#define IRQ_REG_MASK_OFFSET	  0x000
#define IRQ_REG_MASK_SET_OFFSET	  0x004
#define IRQ_REG_MASK_CLEAR_OFFSET 0x008
#define IRQ_REG_INT_OFFSET	  0x00C
#define IRQ_REG_INT_SET_OFFSET	  0x010
#define IRQ_REG_INT_CLEAR_OFFSET  0x014
#define IRQ_REG_ACK_OFFSET	  0x018
#define IRQ_REG_ACK_SET_OFFSET	  0x01C
#define IRQ_REG_ACK_CLEAR_OFFSET  0x020
#define IRQ_REG_FIFO_OFFSET	  0x024

/* Interrupt line masks: these interrupts directly go to the core (after being
 * serialized as reqest + id). We refer to these interrupts with the prefix IRQ.
 * Events on the other we strictly use to refer to "interrupts/events" that are
 * signaled through (muxed) EU SoC interrupts (IRQ_FC_EVT_SOC_EVT) and need
 * additional handling by the user through the Event Unit.
 */
#define IRQ_FC_EVT_SW0	      BIT(0)
#define IRQ_FC_EVT_SW1	      BIT(1)
#define IRQ_FC_EVT_SW2	      BIT(2)
#define IRQ_FC_EVT_SW3	      BIT(3)
#define IRQ_FC_EVT_SW4	      BIT(4)
#define IRQ_FC_EVT_SW5	      BIT(5)
#define IRQ_FC_EVT_SW6	      BIT(6)
#define IRQ_FC_EVT_SW7	      BIT(7)
#define IRQ_FC_EVT_DMA_PE_EVT BIT(8)
#define IRQ_FC_EVT_DMA_PE_IRQ BIT(9)
#define IRQ_FC_EVT_TIMER0_LO  BIT(10)
#define IRQ_FC_EVT_TIMER0_HI  BIT(11)
#define IRQ_FC_EVT_PF	      BIT(12)
#define IRQ_FC_EVT_CLK_REF    BIT(14)
#define IRQ_FC_EVT_GPIO	      BIT(15)
/* doesn't exist in pulp */
/*#define IRQ_FC_EVT_RTC		   16 */
#define IRQ_FC_EVT_ADV_TIMER0 BIT(17)
#define IRQ_FC_EVT_ADV_TIMER1 BIT(18)
#define IRQ_FC_EVT_ADV_TIMER2 BIT(19)
#define IRQ_FC_EVT_ADV_TIMER3 BIT(20)
/* doesn't exist in pulp */
/* #define IRQ_FC_EVT_CLUSTER_NOT_BUSY 21 */
/* #define IRQ_FC_EVT_CLUSTER_POK	   22 */
/* #define IRQ_FC_EVT_CLUSTER_CG_OK	   23 */
/* #define IRQ_FC_EVT_PICL_OK     24 */
/* #define IRQ_FC_EVT_SCU_OK      25 */
/*
 * SoC event unit events: Many events get implicitely muxed into this interrupt.
 * A user that gets such an interrupt has to check the event unit's registers to
 * see what happened
 */
#define IRQ_FC_EVT_SOC_EVT BIT(26)
/*
 * Event queue error: If we don't process event unit events quickly enough
 * internal fifos can overflow and we get this error interrupt
 */
#define IRQ_FC_EVT_QUIRQE_ERROR BIT(29)
/* High priority peripheral events: these are hardcoded to directly go to the
 * core using a dedicated interrupt line
 */
#define IRQ_FC_EVT_PERIPH0 BIT(30)
#define IRQ_FC_EVT_PERIPH1 BIT(31)



/**
  \ingroup  CMSIS_core_register
  \defgroup CMSIS_SysTick     System Tick Timer (SysTick)
  \brief    Type definitions for the System Timer Registers.
  @{
 */

/**
  \brief  Structure type to access the System Timer (SysTick).
 */
typedef struct
{
  __IOM uint32_t CFG_REG_LO;                   /*!< Offset: 0x000 (R/W)  SysTick Configuration Register for lower 32-bits */
  __IOM uint32_t CFG_REG_HI;                   /*!< Offset: 0x004 (R/W)  SysTick Configuration Register for high 32-bits */
  __IOM uint32_t VALUE_LO;                     /*!< Offset: 0x008 (R/W)  SysTick Timer Value Register for low 32-bits */
  __IOM uint32_t VALUE_HI;                     /*!< Offset: 0x00C (R/W)  SysTick Timer Value Register for high 32-bits */
  __IOM uint32_t CMP_LO;                       /*!< Offset: 0x010 (R/W)  SysTick Timer comparator Register for low 32-bits */
  __IOM uint32_t CMP_HI;                       /*!< Offset: 0x014 (R/W)  SysTick Timer comparator Register for high 32-bits */
  __OM  uint32_t START_LO;                     /*!< Offset: 0x014 (R/W)  SysTick Timer start Register for low 32-bits */
  __OM  uint32_t START_HI;                     /*!< Offset: 0x014 (R/W)  SysTick Timer start Register for high 32-bits */
  __OM  uint32_t RESET_LO;                     /*!< Offset: 0x014 (R/W)  SysTick Timer reset Register for low 32-bits */
  __OM  uint32_t RESET_HI;                     /*!< Offset: 0x014 (R/W)  SysTick Timer reset Register for high 32-bits */

} SysTick_Type, timer_periph_t;

/**
  \brief  Structure type to access the System Timer Low.
 */
typedef struct
{
  __IOM uint32_t CTRL;                         /*!< Offset: 0x000 (R/W)  TIMERL Configuration Register for lower 32-bits */
	uint32_t _reserved0;                   /*!< Offset: 0x004 (R/W)  Empty Registers */
  __IOM uint32_t VALUE;                        /*!< Offset: 0x008 (R/W)  TIMERL Timer Value Register for low 32-bits */
	uint32_t _reserved1;                   /*!< Offset: 0x00C (R/W)  Empty Registers */
  __IOM uint32_t COMPARE;                      /*!< Offset: 0x010 (R/W)  TIMERL Timer comparator Register for low 32-bits */
	uint32_t _reserved2;                   /*!< Offset: 0x014 (R/W)  Empty Registers */
  __OM  uint32_t START;                        /*!< Offset: 0x014 (R/W)  SysTick Timer start Register for low 32-bits */
	uint32_t _reserved3;                   /*!< Offset: 0x014 (R/W)  Empty Registers */
  __OM  uint32_t RESET;                        /*!< Offset: 0x014 (R/W)  SysTick Timer reset Register for low 32-bits */
} TimerL_Type;

/**
  \brief  Structure type to access the System Timer Low.
 */
typedef struct
{
	uint32_t _reserved0;                   /*!< Offset: 0x000 (R/W)  Empty Registers */
  __IOM uint32_t CTRL;                         /*!< Offset: 0x004 (R/W)  TIMERH Configuration Register for high 32-bits */
	uint32_t _reserved1;                   /*!< Offset: 0x008 (R/W)  Empty Registers */
  __IOM uint32_t VALUE;                        /*!< Offset: 0x00C (R/W)  TIMERH Timer Value Register for high 32-bits */
	uint32_t _reserved2;                   /*!< Offset: 0x010 (R/W)  Empty Registers */
  __IOM uint32_t COMPARE;                      /*!< Offset: 0x014 (R/W)  TIMERH Timer comparator Register for high 32-bits */
	uint32_t _reserved3;                   /*!< Offset: 0x014 (R/W)  Empty Registers */
  __OM  uint32_t START;                        /*!< Offset: 0x014 (R/W)  SysTick Timer start Register for high 32-bits */
	uint32_t _reserved4;                   /*!< Offset: 0x014 (R/W)  Empty Registers */
  __OM  uint32_t RESET;                        /*!< Offset: 0x014 (R/W)  SysTick Timer reset Register for high 32-bits */
} TimerH_Type;


/* TIMERL configuration low Register Definitions */
#define TIMERL_CFG_REG_LOW_64BIT_Pos         31U                                            /*!< TIMERL CFG_REG_LOW: 64BIT Position */
#define TIMERL_CFG_REG_LOW_64BIT_Msk         (1UL << TIMERL_CFG_REG_LOW_64BIT_Pos)         /*!< TIMERL CFG_REG_LOW: 64BIT Mask */

#define TIMERL_CFG_REG_LOW_PRESCALER_Pos     8U                                             /*!< TIMERL CFG_REG_LOW: PRESCALER Position */
#define TIMERL_CFG_REG_LOW_PRESCALER_Msk     (FFUL << TIMERL_CFG_REG_LOW_PRESCALER_Pos)    /*!< TIMERL CFG_REG_LOW: PRESCALER Mask */

#define TIMERL_CFG_REG_LOW_CLKS_Pos          7U                                             /*!< TIMERL CFG_REG_LOW: CLKS Position */
#define TIMERL_CFG_REG_LOW_CLKS_Msk          (1UL << TIMERL_CFG_REG_LOW_CLKS_Pos)          /*!< TIMERL CFG_REG_LOW: CLKS Mask */

#define TIMERL_CFG_REG_LOW_PRESCALERE_Pos    6U                                             /*!< TIMERL CFG_REG_LOW: PRESCALERE Position */
#define TIMERL_CFG_REG_LOW_PRESCALERE_Msk    (1UL << TIMERL_CFG_REG_LOW_PRESCALERE_Pos)    /*!< TIMERL CFG_REG_LOW: PRESCALERE Mask */

#define TIMERL_CFG_REG_LOW_ONE_SHOT_Pos      5U                                             /*!< TIMERL CFG_REG_LOW: ONE_SHOT Position */
#define TIMERL_CFG_REG_LOW_ONE_SHOT_Msk      (1UL << TIMERL_CFG_REG_LOW_ONE_SHOT_Pos)      /*!< TIMERL CFG_REG_LOW: ONE_SHOT Mask */

#define TIMERL_CFG_REG_LOW_CMP_CLR_Pos       4U                                             /*!< TIMERL CFG_REG_LOW: CMP_CLR Position */
#define TIMERL_CFG_REG_LOW_CMP_CLR_Msk       (1UL << TIMERL_CFG_REG_LOW_CMP_CLR_Pos)       /*!< TIMERL CFG_REG_LOW: CMP_CLR Mask */

#define TIMERL_CFG_REG_LOW_IEM_Pos           3U                                             /*!< TIMERL CFG_REG_LOW: IEM Position */
#define TIMERL_CFG_REG_LOW_IEM_Msk           (1UL << TIMERL_CFG_REG_LOW_IEM_Pos)           /*!< TIMERL CFG_REG_LOW: IEM Mask */

#define TIMERL_CFG_REG_LOW_IRQE_Pos          2U                                             /*!< TIMERL CFG_REG_LOW: IRQE Position */
#define TIMERL_CFG_REG_LOW_IRQE_Msk          (1UL << TIMERL_CFG_REG_LOW_IRQE_Pos)          /*!< TIMERL CFG_REG_LOW: IRQE Mask */

#define TIMERL_CFG_REG_LOW_RESET_Pos         1U                                             /*!< TIMERL CFG_REG_LOW: RESET Position */
#define TIMERL_CFG_REG_LOW_RESET_Msk         (1UL << TIMERL_CFG_REG_LOW_RESET_Pos)         /*!< TIMERL CFG_REG_LOW: RESET Mask */

#define TIMERL_CFG_REG_LOW_ENABLE_Pos        0U                                             /*!< TIMERL CFG_REG_LOW: ENABLE Position */
#define TIMERL_CFG_REG_LOW_ENABLE_Msk        (1UL << TIMERL_CFG_REG_LOW_ENABLE_Pos)        /*!< TIMERL CFG_REG_LOW: ENABLE Mask */

/* TIMERH configuration high Register Definitions */
#define TIMERH_CFG_REG_HIGH_ERCLK_Pos        7U                                             /*!< TIMERH CFG_REG_HIGH: Enable ref clock Position */
#define TIMERH_CFG_REG_HIGH_ERCLK_Msk        (1UL << TIMERH_CFG_REG_HIGH_ERCLK_Pos)        /*!< TIMERH CFG_REG_HIGH: Enable ref clock Mask */

#define TIMERH_CFG_REG_HIGH_PRESCALERE_Pos   6U                                             /*!< TIMERH CFG_REG_HIGH: PRESCALERE Position */
#define TIMERH_CFG_REG_HIGH_PRESCALERE_Msk   (1UL << TIMERH_CFG_REG_HIGH_PRESCALERE_Pos)   /*!< TIMERH CFG_REG_HIGH: PRESCALERE Mask */

#define TIMERH_CFG_REG_HIGH_ONE_SHOT_Pos     5U                                             /*!< TIMERH CFG_REG_HIGH: ONE_SHOT Position */
#define TIMERH_CFG_REG_HIGH_ONE_SHOT_Msk     (1UL << TIMERH_CFG_REG_HIGH_ONE_SHOT_Pos)     /*!< TIMERH CFG_REG_HIGH: ONE_SHOT Mask */

#define TIMERH_CFG_REG_HIGH_CMP_CLR_Pos      4U                                             /*!< TIMERH CFG_REG_HIGH: CMP_CLR Position */
#define TIMERH_CFG_REG_HIGH_CMP_CLR_Msk      (1UL << TIMERH_CFG_REG_HIGH_CMP_CLR_Pos)      /*!< TIMERH CFG_REG_HIGH: CMP_CLR Mask */

#define TIMERH_CFG_REG_HIGH_IEM_Pos          3U                                             /*!< TIMERH CFG_REG_HIGH: IEM Position */
#define TIMERH_CFG_REG_HIGH_IEM_Msk          (1UL << TIMERH_CFG_REG_HIGH_IEM_Pos)          /*!< TIMERH CFG_REG_HIGH: IEM Mask */

#define TIMERH_CFG_REG_HIGH_IRQE_Pos         2U                                             /*!< TIMERH CFG_REG_HIGH: IRQE Position */
#define TIMERH_CFG_REG_HIGH_IRQE_Msk         (1UL << TIMERH_CFG_REG_HIGH_IRQE_Pos)         /*!< TIMERH CFG_REG_HIGH: IRQE Mask */

#define TIMERH_CFG_REG_HIGH_RESET_Pos        1U                                             /*!< TIMERH CFG_REG_HIGH: RESET Position */
#define TIMERH_CFG_REG_HIGH_RESET_Msk        (1UL << TIMERH_CFG_REG_HIGH_RESET_Pos)        /*!< TIMERH CFG_REG_HIGH: RESET Mask */

#define TIMERH_CFG_REG_HIGH_ENABLE_Pos       0U                                             /*!< TIMERH CFG_REG_HIGH: ENABLE Position */
#define TIMERH_CFG_REG_HIGH_ENABLE_Msk       (1UL << /*TIMERH_CFG_REG_HIGH_ENABLE_Pos*/)   /*!< TIMERH CFG_REG_HIGH: ENABLE Mask */


/* SysTick configuration low Register Definitions */
#define SysTick_CFG_REG_LOW_64BIT_Pos         TIMERL_CFG_REG_LOW_64BIT_Pos
#define SysTick_CFG_REG_LOW_64BIT_Msk         TIMERL_CFG_REG_LOW_64BIT_Msk

#define SysTick_CFG_REG_LOW_PRESCALER_Pos     TIMERL_CFG_REG_LOW_PRESCALER_Pos
#define SysTick_CFG_REG_LOW_PRESCALER_Msk     TIMERL_CFG_REG_LOW_PRESCALER_Msk

#define SysTick_CFG_REG_LOW_CLKS_Pos          TIMERL_CFG_REG_LOW_CLKS_Pos
#define SysTick_CFG_REG_LOW_CLKS_Msk          TIMERL_CFG_REG_LOW_CLKS_Msk

#define SysTick_CFG_REG_LOW_PRESCALERE_Pos    TIMERL_CFG_REG_LOW_PRESCALERE_Pos
#define SysTick_CFG_REG_LOW_PRESCALERE_Msk    TIMERL_CFG_REG_LOW_PRESCALERE_Msk

#define SysTick_CFG_REG_LOW_ONE_SHOT_Pos      TIMERL_CFG_REG_LOW_ONE_SHOT_Pos
#define SysTick_CFG_REG_LOW_ONE_SHOT_Msk      TIMERL_CFG_REG_LOW_ONE_SHOT_Msk

#define SysTick_CFG_REG_LOW_CMP_CLR_Pos       TIMERL_CFG_REG_LOW_CMP_CLR_Pos
#define SysTick_CFG_REG_LOW_CMP_CLR_Msk       TIMERL_CFG_REG_LOW_CMP_CLR_Msk

#define SysTick_CFG_REG_LOW_IEM_Pos           TIMERL_CFG_REG_LOW_IEM_Pos
#define SysTick_CFG_REG_LOW_IEM_Msk           TIMERL_CFG_REG_LOW_IEM_Msk

#define SysTick_CFG_REG_LOW_IRQE_Pos          TIMERL_CFG_REG_LOW_IRQE_Pos
#define SysTick_CFG_REG_LOW_IRQE_Msk          TIMERL_CFG_REG_LOW_IRQE_Msk

#define SysTick_CFG_REG_LOW_RESET_Pos         TIMERL_CFG_REG_LOW_RESET_Pos
#define SysTick_CFG_REG_LOW_RESET_Msk         TIMERL_CFG_REG_LOW_RESET_Msk

#define SysTick_CFG_REG_LOW_ENABLE_Pos        TIMERL_CFG_REG_LOW_ENABLE_Pos
#define SysTick_CFG_REG_LOW_ENABLE_Msk        TIMERL_CFG_REG_LOW_ENABLE_Msk

/* SysTick configuration high Register Definitions */
#define SysTick_CFG_REG_HIGH_ERCLK_Pos        TIMERH_CFG_REG_HIGH_ERCLK_Pos
#define SysTick_CFG_REG_HIGH_ERCLK_Msk        TIMERH_CFG_REG_HIGH_ERCLK_Msk

#define SysTick_CFG_REG_HIGH_PRESCALERE_Pos   TIMERH_CFG_REG_HIGH_PRESCALERE_Pos
#define SysTick_CFG_REG_HIGH_PRESCALERE_Msk   TIMERH_CFG_REG_HIGH_PRESCALERE_Msk

#define SysTick_CFG_REG_HIGH_ONE_SHOT_Pos     TIMERH_CFG_REG_HIGH_ONE_SHOT_Pos
#define SysTick_CFG_REG_HIGH_ONE_SHOT_Msk     TIMERH_CFG_REG_HIGH_ONE_SHOT_Msk

#define SysTick_CFG_REG_HIGH_CMP_CLR_Pos      TIMERH_CFG_REG_HIGH_CMP_CLR_Pos
#define SysTick_CFG_REG_HIGH_CMP_CLR_Msk      TIMERH_CFG_REG_HIGH_CMP_CLR_Msk

#define SysTick_CFG_REG_HIGH_IEM_Pos          TIMERH_CFG_REG_HIGH_IEM_Pos
#define SysTick_CFG_REG_HIGH_IEM_Msk          TIMERH_CFG_REG_HIGH_IEM_Msk

#define SysTick_CFG_REG_HIGH_IRQE_Pos         TIMERH_CFG_REG_HIGH_IRQE_Pos
#define SysTick_CFG_REG_HIGH_IRQE_Msk         TIMERH_CFG_REG_HIGH_IRQE_Msk

#define SysTick_CFG_REG_HIGH_RESET_Pos        TIMERH_CFG_REG_HIGH_RESET_Pos
#define SysTick_CFG_REG_HIGH_RESET_Msk        TIMERH_CFG_REG_HIGH_RESET_Msk

#define SysTick_CFG_REG_HIGH_ENABLE_Pos       TIMERH_CFG_REG_HIGH_ENABLE_Pos
#define SysTick_CFG_REG_HIGH_ENABLE_Msk       TIMERH_CFG_REG_HIGH_ENABLE_Msk
/*@} end of group CMSIS_SysTick */



#if defined (__MPU_PRESENT) && (__MPU_PRESENT == 1U)
#error "PULP doesn't have an MPU"
/**
  \ingroup  CMSIS_core_register
  \defgroup CMSIS_MPU     Memory Protection Unit (MPU)
  \brief    Type definitions for the Memory Protection Unit (MPU)
  @{
 */

/**
  \brief  Structure type to access the Memory Protection Unit (MPU).
 */
typedef struct
{
  __IOM uint32_t MPU_ENABLE;                 /*!< Offset: 0x000 (R/W)  MPU Enable Register */
  __IOM uint32_t _reserved0[15];             /*!< Offset: 0x004 (R/W)  Empty Registers */
  __IOM uint32_t FC_TCDM_RULE[8];            /*!< Offset: 0x040 (R/W)  MPU FC TCMD Rules Registers */
  __IOM uint32_t _reserved1[8];              /*!< Offset: 0x060 (R/W)  Empty Registers */
  __IOM uint32_t L2_RULE[8];                 /*!< Offset: 0x080 (R/W)  MPU L2 Rules Registers */
  __IOM uint32_t _reserved2[8];              /*!< Offset: 0x0A0 (R/W)  Empty Registers */
  __IOM uint32_t APB_RULE[8];                /*!< Offset: 0x0C0 (R/W)  MPU APB Rules Registers */
} MPU_Type;

/* MPU Type Register Definitions */
#define MPU_TYPE_ENABLE_Pos               0U                                            /*!< MPU TYPE: ENABLE Position */
#define MPU_TYPE_ENABLE_Msk               (0x1L /*<< MPU_TYPE_ENABLE_Pos*/)             /*!< MPU TYPE: ENABLE Mask */

#define MPU_TYPE_RULE_STATE_Pos           0U                                            /*!< MPU TYPE: RULE_STATE Position */
#define MPU_TYPE_RULE_STATE_Msk           (0x1L /*<< MPU_TYPE_RULE_STATE_Pos*/)             /*!< MPU TYPE: RULE_STATE Mask */

#define MPU_TYPE_RULE_SIZE_Pos            1U                                            /*!< MPU TYPE: RULE_SIZE Position */
#define MPU_TYPE_RULE_SIZE_Msk            (0x3FFFL << MPU_TYPE_RULE_SIZE_Pos)           /*!< MPU TYPE: RULE_SIZE Mask */

#define MPU_TYPE_RULE_BASE_Pos            15U                                           /*!< MPU TYPE: RULE_BASE Position */
#define MPU_TYPE_RULE_BASE_Msk            (0x7FFFL << MPU_TYPE_RULE_BASE_Pos)           /*!< MPU TYPE: RULE_BASE Mask */

#define MPU_TYPE_RULE_AREA_Pos            30U                                           /*!< MPU TYPE: RULE_AREA Position */
#define MPU_TYPE_RULE_AREA_Msk            (0x3L << MPU_TYPE_RULE_AREA_Pos)              /*!< MPU TYPE: RULE_AREA Mask */

/*@} end of group CMSIS_MPU */
#endif /* defined (__MPU_PRESENT) && (__MPU_PRESENT == 1U) */


/**
  \ingroup    CMSIS_core_register
  \defgroup   CMSIS_core_base     Core Definitions
  \brief      Definitions for base addresses, unions, and structures.
  @{
 */

/* Memory mapping of Core Hardware */
/* #define CL_PERI_BASE        (0x10000000UL) */

#define FC_BASE             (0x1B000000UL)                             /*!< FC Base Address */

#define SOC_ROM_BASE        ROM_ADDR                                   /*!< SOC ROM Base Address */
// phasing out
//#define SOC_PERI_BASE       SOC_PERIPHERALS_ADDR                       /*!< SOC Peripherals Base Address */

#define CORE_PERI_BASE      (0x00200000UL)                             /*!< RISC Core Peripheral Base Address */
#define CORE_SCB_BASE       (CORE_PERI_BASE)                           /*!< RISC Core System Control Block Base Address */
#define CORE_SCBC_BASE      (CORE_PERI_BASE +  0x1400UL)               /*!< RISC Core System Control Block Cache Base Address */

#define CORE_EU_BASE        (0x00200800UL)                             /*!< RISC Core Event Unit Base Address */
#define CORE_EU_BARRIER_BASE         (CORE_EU_BASE + 0x0400UL)         /*!< RISC Core Event Unit HW Barrier Base Address */
#define CORE_EU_SW_EVENTS_BASE       (CORE_EU_BASE + 0x0600UL)         /*!< RISC Core Event Unit SW Events Base Address */
#define CORE_EU_SOC_EVENTS_BASE      (CORE_EU_BASE + 0x0700UL)         /*!< RISC Core Event Unit SOC Events Base Address */
#define CORE_EU_EXT_EVENTS_BASE      (CORE_EU_BASE + 0x0780UL)         /*!< RISC Core Event Unit External Events Base Address */


#define CORE_EU_DEMUX_BASE  (0x00204000UL)                             /*!< RISC Core Event Unit Demux Base Address */
#define CORE_EU_CORE_DEMUX_BASE      (CORE_EU_DEMUX_BASE)              /*!< RISC Core Event Unit Core Demux Base Address */
#define CORE_EU_SEC_DEMUX_BASE       (CORE_EU_DEMUX_BASE + 0x0040UL)   /*!< RISC Core Event Unit Security Demux Base Address */
#define CORE_EU_LOOP_DEMUX_BASE      (CORE_EU_DEMUX_BASE + 0x0060UL)   /*!< RISC Core Event Unit Loop Demux Base Address */
#define CORE_EU_DISPATCH_DEMUX_BASE  (CORE_EU_DEMUX_BASE + 0x0080UL)   /*!< RISC Core Event Unit Dispatch Demux Base Address */
#define CORE_EU_MUTEX_DEMUX_BASE     (CORE_EU_DEMUX_BASE + 0x00C0UL)   /*!< RISC Core Event Unit Mutex Demux Base Address */
#define CORE_EU_SW_EVENTS_DEMUX_BASE (CORE_EU_DEMUX_BASE + 0x0100UL)   /*!< RISC Core Event Unit SW Event Demux Base Address */
#define CORE_EU_BARRIER_DEMUX_BASE   (CORE_EU_DEMUX_BASE + 0x0200UL)   /*!< RISC Core Event Unit HW Barrier Demux Base Address */


#define CORE_MCHAN_BASE     (CORE_EU_DEMUX_BASE + 0x0400UL)            /*!< RISC Core DMAMCHAN Base Address between L2 and Cluster TCDM */

/* FC core Memory map */
#define FC_SCBC_BASE        (FC_BASE + CORE_SCBC_BASE)                 /*!< FC System Control Block Cache Base Address */

#define FC_EU_BARRIER_BASE         (FC_BASE + CORE_EU_BARRIER_BASE)    /*!< FC Event Unit HW Barrier Base Address */
#define FC_EU_SW_EVENTS_BASE       (FC_BASE + CORE_EU_SW_EVENTS_BASE)  /*!< FC Event Unit SW Events Base Address */
#define FC_EU_SOC_EVENTS_BASE      (FC_BASE + CORE_EU_SOC_EVENTS_BASE) /*!< FC Event Unit SOC Events Base Address */
#define FC_EU_EXT_EVENTS_BASE      (FC_BASE + CORE_EU_EXT_EVENTS_BASE) /*!< FC Event Unit EXT Events Base Address */


#define FC_EU_CORE_DEMUX_BASE      (FC_BASE + CORE_EU_CORE_DEMUX_BASE)        /*!< FC Event Unit Core Demux Base Address */
#define FC_EU_SEC_DEMUX_BASE       (FC_BASE + CORE_EU_SEC_DEMUX_BASE)         /*!< FC Event Unit Security Demux Base Address */
#define FC_EU_LOOP_DEMUX_BASE      (FC_BASE + CORE_EU_LOOP_DEMUX_BASE)        /*!< FC Event Unit Loop Demux Base Address */
#define FC_EU_DISPATCH_DEMUX_BASE  (FC_BASE + CORE_EU_DISPATCH_DEMUX_BASE)    /*!< FC Event Unit Dispatch Demux Base Address */
#define FC_EU_MUTEX_DEMUX_BASE     (FC_BASE + CORE_EU_MUTEX_DEMUX_BASE)       /*!< FC Event Unit Mutex Demux Base Address */
#define FC_EU_SW_EVENTS_DEMUX_BASE (FC_BASE + CORE_EU_SW_EVENTS_DEMUX_BASE)   /*!< FC Event Unit SW Events Demux Base Address */
#define FC_EU_BARRIER_DEMUX_BASE   (FC_BASE + CORE_EU_BARRIER_DEMUX_BASE)     /*!< FC Event Unit Barrier Demux Base Address */

#define FC_MCHAN_BASE              (FC_BASE + CORE_MCHAN_BASE)                /*!< FC DMAMCHAN Base Address between L2 and Cluster TCDM */

#define SCBC                ((SCBC_Type   *)   CORE_SCBC_BASE )               /*!< Icache SCBC configuration struct */

/* Core Structrue definitions */
#define SysTick             ((SysTick_Type *) FC_TIMER_ADDR)    /*!< SysTick configuration struct */
#define TIMERL              ((TimerL_Type  *) FC_TIMER_ADDR)    /*!< SysTick configuration struct */
#define TIMERH              ((TimerH_Type  *) FC_TIMER_ADDR)    /*!< SysTick configuration struct */

#if defined (__MPU_PRESENT) && (__MPU_PRESENT == 1U)
  #define FC_MPU_BASE       (FC_BASE + CORE_PERI_BASE + 0x4400UL)         /*!< Memory Protection Unit */
  #define MPU               ((MPU_Type       *)     FC_MPU_BASE      )   /*!< Memory Protection Unit */
#endif

#define EU_SW_EVENTS         ((EU_SW_EVENTS_DEMUX_Type   *)  CORE_EU_SW_EVENTS_BASE)          /*!< EU_SW_EVENTS_DEMUX configuration struct */
#define EU_SOC_EVENTS        ((EU_SOC_EVENTS_Type   *)      CORE_EU_SOC_EVENTS_BASE)          /*!< EU_SW_EVENTS_DEMUX configuration struct */


#define NVIC                ((NVIC_Type   *)      FC_IRQ_ADDR)                       /*!< NVIC configuration struct */

#define EU_CORE_DEMUX       ((EU_CORE_DEMUX_Type   *)      CORE_EU_CORE_DEMUX_BASE)         /*!< EU_CORE_DEMUX configuration struct */
#define EU_SEC_DEMUX        ((EU_SEC_DEMUX_Type   *)       CORE_EU_SEC_DEMUX_BASE)          /*!< EU_SEC_DEMUX configuration struct */
#define EU_LOOP_DEMUX       ((EU_LOOP_DEMUX_Type   *)      CORE_EU_LOOP_DEMUX_BASE)         /*!< EU_LOOP_DEMUX configuration struct */
#define EU_DISPATCH_DEMUX   ((EU_DISPATCH_DEMUX_Type   *)  CORE_EU_DISPATCH_DEMUX_BASE)     /*!< EU_DISPATCH_DEMUX configuration struct */
#define EU_MUTEX_DEMUX      ((EU_MUTEX_DEMUX_Type   *)     CORE_EU_MUTEX_DEMUX_BASE)        /*!< EU_MUTEX_DEMUX configuration struct */
#define EU_SW_EVENTS_DEMUX  ((EU_SW_EVENTS_DEMUX_Type   *) CORE_EU_SW_EVENTS_DEMUX_BASE)    /*!< EU_SW_EVENTS_DEMUX configuration struct */
#define EU_BARRIER_DEMUX(id) ((EU_BARRIER_DEMUX_Type   *)   (CORE_EU_BARRIER_DEMUX_BASE+(id*sizeof(EU_BARRIER_DEMUX_Type))))      /*!< EU_BARRIER_DEMUX configuration struct */
#define DMAMCHAN            ((DMAMCHAN_Type   *)   CORE_MCHAN_BASE)                              /*!< MCHAN DMA configuration struct */
#define DMAMCHAN_COMPRESSOR ((decompressor_t *) CORE_MCHAN_COMPRESSOR_BASE)

#define FC_EU_SW_EVENTS      ((EU_SW_EVENTS_DEMUX_Type   *)  FC_EU_SW_EVENTS_BASE)            /*!< EU_SW_EVENTS_DEMUX configuration struct */

/** FC_CLUSTER_ID Definitions */
#define FC_CLUSTER_ID                 32                /**< FC CLuster ID */
/*@} */


/*******************************************************************************
 *                Hardware Abstraction Layer
  Core Function Interface contains:
  - Core Function Access
  - Core NVIC Functions
  - Core SysTick Functions
  - Core Debug Functions
  - Core Register Access Functions
 ******************************************************************************/
/**
  \defgroup CMSIS_Core_FunctionInterface Functions and Instructions Reference
*/




/* ###########################  Core Function Access  ########################### */
/** \ingroup  CMSIS_Core_FunctionInterface
    \defgroup CMSIS_Core_RegAccFunctions CMSIS Core Register Access Functions
  @{
 */
/**
  \brief   Get PRIVLVL Register
  \details Returns the content of the PRIVLVL Register.
  \return               PRIVLVL Register value
 */
__attribute__((always_inline)) __STATIC_INLINE uint32_t __get_CPRIV(void)
{
    uint32_t result = csr_read(CPRIV_ADDR);
    return result;
}

/**
  \brief   Restore the MIE bit
  \details Restore the MIE bit of MSTATUS
 */
__attribute__((always_inline)) __STATIC_INLINE void __restore_irq(int irq)
{
    // We are in machine mode, already mask all interrupt, so just set MIE = irq
    /* __builtin_pulp_spr_write(0x300, irq); */
    csr_write(MSTATUS_ADDR, irq);
}

/**
  \brief   Enable IRQ Interrupts
  \details Enables IRQ interrupts by setting the MPIE-bit in the MSTATUS.
           Can only be executed in Privileged modes.
 */
__attribute__((always_inline)) __STATIC_INLINE void __enable_irq(void)
{
    csr_read_set(MSTATUS_ADDR, BIT(MSTATUS_MIE_Pos));
}

/**
  \brief   Disable IRQ Interrupts
  \details Disables IRQ interrupts by clearing the MPIE-bit in the CPSR.
           Can only be executed in Privileged modes.
 */
__attribute__((always_inline)) __STATIC_INLINE int __disable_irq(void)
{
    uint32_t val = csr_read_clear(MSTATUS_ADDR, BIT(MSTATUS_MIE_Pos));
    return val;
}

/**
  \brief   Set ustatus Register
  \details Writes the given value to the ustatus Register.
  \param [in]    control  ustatus Register value to set
 */
__attribute__((always_inline)) __STATIC_INLINE void __set_USTATUS(uint32_t control)
{
    assert(0);
}

/**
  \brief   Set mstatus Register
  \details Writes the given value to the mstatus Register.
  \param [in]    control  mstatus Register value to set
 */
__attribute__((always_inline)) __STATIC_INLINE void __set_MSTATUS(uint32_t control)
{
    csr_write(MSTATUS_ADDR, control);
}

/**
  \brief   Get MCAUSE Register
  \details Returns the content of the MCAUSE Register.
  \return               MCAUSE Register value
 */
__attribute__((always_inline)) __STATIC_INLINE uint32_t __get_MCAUSE(void)
{
    uint32_t result = csr_read(MCAUSE_ADDR);
    return result;
}

/**
  \brief   Get UCAUSE Register
  \details Returns the content of the UCAUSE Register.
  \return               UCAUSE Register value
 */
__attribute__((always_inline)) __STATIC_INLINE uint32_t __get_UCAUSE(void)
{
    uint32_t result = csr_read(UCAUSE_ADDR);
    return result;
}

/**
  \brief   Get MSTATUS Register
  \details Returns the content of the MSTATUS Register.
  \return               MSTATUS Register value
 */
__attribute__((always_inline)) __STATIC_INLINE uint32_t __get_MSTATUS(void)
{
    uint32_t result = csr_read(MSTATUS_ADDR);
    return result;
}


/**
  \brief   Get USTATUS Register
  \details Returns the content of the USTATUS Register.
  \return               USTATUS Register value
 */
__attribute__((always_inline)) __STATIC_INLINE uint32_t __get_USTATUS(void)
{
    assert(0);
}

/**
  \brief   Get Process Stack Pointer
  \details Returns the current value of the Process Stack Pointer (PSP).
  \return               PSP Register value
 */
__attribute__((always_inline)) __STATIC_INLINE uint32_t __get_PSP(void)
{
    assert(0);
  /* register uint32_t result; */

  /* __ASM volatile ("lw %0, (userStack)"  : "=r" (result) ); */
  /* return(result); */
}

/**
  \brief   Set Process Stack Pointer
  \details Assigns the given value to the Process Stack Pointer (PSP).
  \param [in]    topOfProcStack  Process Stack Pointer value to set
 */
__attribute__((always_inline)) __STATIC_INLINE void __set_PSP(uint32_t topOfProcStack)
{
    assert(0);
  /* __ASM volatile ("sw %0, (userStack)(x0)"  :: "r" (topOfProcStack) ); */
}

/**
  \brief   Get Main Stack Pointer
  \details Returns the current value of the Main Stack Pointer (MSP).
  \return               MSP Register value
 */
__attribute__((always_inline)) __STATIC_INLINE uint32_t __get_MSP(void)
{
    assert(0);
  /* register uint32_t result; */

  /* __ASM volatile ("lw %0, (kernelStack)" : "=r" (result) ); */
  /* return(result); */
}

/**
  \brief   Set Main Stack Pointer
  \details Assigns the given value to the Main Stack Pointer (MSP).
  \param [in]    topOfMainStack  Main Stack Pointer value to set
 */
__attribute__((always_inline)) __STATIC_INLINE void __set_MSP(uint32_t topOfMainStack)
{
    assert(0);
    /*__ASM volatile ("sw %0, (kernelStack)(x0)"  :: "r" (topOfMainStack) ); */
}

/**
  \brief   Get the running mode is User Mode
  \details Read 0xC10 privilege register
  \return               Is User mode
 */
__attribute__((always_inline)) __STATIC_INLINE uint32_t __is_U_Mode()
{
    uint32_t mode = csr_read(CPRIV_ADDR);
    return ((mode & 0x3) == 0);
}

/**
  \brief   Get the running mode is Machine Mode
  \details Read 0xC10 privilege register
  \return               Is Machine mode
 */
__attribute__((always_inline)) __STATIC_INLINE uint32_t __is_M_Mode()
{
    uint32_t mode = csr_read(CPRIV_ADDR);
    return ((mode & 0x3) == 1);
}


/* ##########################   NVIC functions  #################################### */
/**
  \ingroup  CMSIS_Core_FunctionInterface
  \defgroup CMSIS_Core_NVICFunctions NVIC Functions
  \brief    Functions that manage interrupts and exceptions via the NVIC.
  @{
 */

#ifdef CMSIS_NVIC_VIRTUAL
  #ifndef CMSIS_NVIC_VIRTUAL_HEADER_FILE
    #define CMSIS_NVIC_VIRTUAL_HEADER_FILE "cmsis_nvic_virtual.h"
  #endif
  #include CMSIS_NVIC_VIRTUAL_HEADER_FILE
#else
/* keeps this for backwards compatibility */
  #define NVIC_EnableIRQ              __irq_enable
  #define NVIC_GetEnableIRQ           __irq_get_enable
  #define NVIC_DisableIRQ             __irq_disable
  #define NVIC_GetPendingIRQ          __irq_get_pending
  #define NVIC_SetPendingIRQ          __irq_set_pending
  #define NVIC_ClearPendingIRQ        __irq_clear_pending
  #define NVIC_GetActive              __irq_get_active
  #define NVIC_SystemReset            __irq_system_reset
/* saner names for irqs */
  #define irqn_enable                 __irq_enable
  #define irqn_get_enable             __irq_get_enable
  #define irqn_disable                __irq_disable
  #define irqn_get_pending            __irq_get_pending
  #define irqn_set_pending            __irq_set_pending
  #define irqn_clear_pending          __irq_clear_pending
  #define irqn_get_active             __irq_get_active
  #define irqn_system_reset           __irq_system_reset
#endif /* CMSIS_NVIC_VIRTUAL */

#ifdef CMSIS_VECTAB_VIRTUAL
  #ifndef CMSIS_VECTAB_VIRTUAL_HEADER_FILE
   #define CMSIS_VECTAB_VIRTUAL_HEADER_FILE "cmsis_vectab_virtual.h"
  #endif
  #include CMSIS_VECTAB_VIRTUAL_HEADER_FILE
#else
  #define NVIC_SetVector              __irq_set_vector
  #define NVIC_GetVector              __irq_get_vector
#endif  /* (CMSIS_VECTAB_VIRTUAL) */

#define NVIC_USER_IRQ_OFFSET          0
#define NVIC_M_IRQ_OFFSET            32


/**
  \brief   Enable Interrupt
  \details Enables a device specific interrupt in the NVIC interrupt controller.
  \param [in]      IRQn  Device specific interrupt number.
  \note    IRQn must not be negative.
 */
__STATIC_INLINE void __irq_enable(IRQn_Type IRQn)
{
  /* U mode does not has the right */
  /* NVIC->MASK_SET = (1UL << IRQn); */
  writew(1UL << IRQn, (uintptr_t)(FC_IRQ_ADDR + IRQ_REG_MASK_SET_OFFSET));
}

/**
  \brief   Get Interrupt Enable status
  \details Returns a device specific interrupt enable status from the NVIC interrupt controller.
  \param [in]      IRQn  Device specific interrupt number.
  \return             0  Interrupt is not enabled.
  \return             1  Interrupt is enabled.
  \note    IRQn must not be negative.
 */
__STATIC_INLINE uint32_t __irq_get_enable(IRQn_Type IRQn)
{
  /* U mode does not has the right */
  /* return ((uint32_t)((NVIC->MASK_IRQ & (1UL << IRQn)) ? 1UL : 0UL)); */
  uint32_t mask = readw((uintptr_t)(FC_IRQ_ADDR + IRQ_REG_MASK_OFFSET));
  return (mask >> IRQn) & 1;
}


/**
  \brief   Disable Interrupt
  \details Disables a device specific interrupt in the NVIC interrupt controller.
  \param [in]      IRQn  Device specific interrupt number.
  \note    IRQn must not be negative.
 */
__STATIC_INLINE void __irq_disable(IRQn_Type IRQn)
{
  /* U mode does not has the right */
  /* NVIC->MASK_IRQ_AND = (1UL << IRQn); */
  writew(1UL << IRQn, (uintptr_t)(FC_IRQ_ADDR + IRQ_REG_MASK_CLEAR_OFFSET));
}


/**
  \brief   Get Pending Interrupt
  \details Reads the NVIC pending register and returns the pending bit for the specified device specific interrupt.
  \param [in]      IRQn  Device specific interrupt number.
  \return             0  Interrupt status is not pending.
  \return             1  Interrupt status is pending.
  \note    IRQn must not be negative.
 */
__STATIC_INLINE uint32_t __irq_get_pending(IRQn_Type IRQn)
{
    /* return(0U); */
    uint32_t pending = readw((uintptr_t)(FC_IRQ_ADDR + IRQ_REG_INT_OFFSET));
    return (pending >> IRQn) & 1;
}


/**
  \brief   Set Pending Interrupt
  \details Sets the pending bit of a device specific interrupt in the NVIC pending register.
  \param [in]      IRQn  Device specific interrupt number.
  \note    IRQn must not be negative.
 */
__STATIC_INLINE void __irq_set_pending(IRQn_Type IRQn)
{
  writew(1UL << IRQn,(uintptr_t)(FC_IRQ_ADDR + IRQ_REG_INT_SET_OFFSET));
}


/**
  \brief   Clear Pending Interrupt
  \details Clears the pending bit of a device specific interrupt in the NVIC pending register.
  \param [in]      IRQn  Device specific interrupt number.
  \note    IRQn must not be negative.
 */
__STATIC_INLINE void __irq_clear_pending(IRQn_Type IRQn)
{
  writew(1UL << IRQn,(uintptr_t)(FC_IRQ_ADDR + IRQ_REG_INT_CLEAR_OFFSET));
}


/**
  \brief   Get Active Interrupt
  \details Reads the active register in the NVIC and returns the active bit for the device specific interrupt.
  \param [in]      IRQn  Device specific interrupt number.
  \return             0  Interrupt status is not active.
  \return             1  Interrupt status is active.
  \note    IRQn must not be negative.
 */
__STATIC_INLINE uint32_t __irq_get_active(IRQn_Type IRQn)
{
  assert(0);
  /* U mode does not has the right */
  /* return ((uint32_t)((NVIC->STATUS & (1UL << IRQn)) ? 1UL : 0UL)); */
  /* TODO */
  return -1;
}

__STATIC_INLINE uint32_t __irq_forge_it_vect(uint32_t ItBaseAddr, uint32_t ItIndex, uint32_t ItHandler)

{
  assert(0);
  /* Prepare 32bit container to be stored at
   *(ItBaseAddr+ItIndex) containing a relative jump from
    (ItBaseAddr+ItIndex) to Handler */

  uint32_t S = ((uint32_t) ItHandler - (ItBaseAddr+ItIndex*4));
  uint32_t R = 0x6F; /* Jal opcode with x0 as target, eg no return */

  /* Forge JAL x0, Address: with Address = S => Bin[31:0] = [S20
  | S10:1 | S11 | S19:12 | 00000 01101111] */


  R = __BIT_INSERT(R, __BIT_EXTRACT(S,  1, 20),  1, 31);
  R = __BIT_INSERT(R, __BIT_EXTRACT(S, 10,  1), 10, 21);
  R = __BIT_INSERT(R, __BIT_EXTRACT(S,  1, 11),  1, 20);
  R = __BIT_INSERT(R, __BIT_EXTRACT(S,  8, 12),  8, 12);

  return R;
}

/**
  \brief   Set Interrupt Vector
  \details Sets an interrupt vector in SRAM based interrupt vector table.
	   The interrupt number can be positive to specify a device specific interrupt,
	   or negative to specify a processor exception.
	   VTOR must been relocated to SRAM before.
  \param [in]   IRQn      Interrupt number
  \param [in]   vector    Address of interrupt handler function
 */
__STATIC_INLINE void __irq_set_vector(IRQn_Type IRQn, uint32_t vector)
{
  assert(0);
  /*
  volatile uint32_t *vectors;

  if((__get_CPRIV() & CPRIV_PRIV_Msk) != 0U) {
    vectors = (uint32_t *)(__builtin_pulp_spr_read(0x305));
  } else {
    vectors = (uint32_t *)(0x1C000000);
  }
  vectors[IRQn] = __NVIC_ForgeItVect((uint32_t)vectors, IRQn, vector);
  */
}

/**
  \brief   Get Interrupt Vector
  \details Reads an interrupt vector from interrupt vector table.
	   The interrupt number can be positive to specify a device specific interrupt,
	   or negative to specify a processor exception.
  \param [in]   IRQn      Interrupt number.
  \return                 Address of interrupt handler function
 */
__STATIC_INLINE uint32_t __irq_get_vector(IRQn_Type IRQn)
{
  assert(0);
  /*
  volatile uint32_t *vectors;
  if((__get_CPRIV() & CPRIV_PRIV_Msk) != 0U) {
    vectors = (uint32_t *)(__builtin_pulp_spr_read(0x305));
  } else {
    vectors = (uint32_t *)(0x1C000000);
  }
  return vectors[IRQn];
  */
}


/**
  \brief   System Reset
  \details Initiates a system reset request to reset the MCU.
 */
__STATIC_INLINE void __irq_system_reset(void)
{
  assert(0);
}

/*@} end of CMSIS_Core_NVICFunctions */

/* ##########################  MPU functions  #################################### */

#if defined (__MPU_PRESENT) && (__MPU_PRESENT == 1U)
#error "PULP doens't support MPU"
#include "mpu_gap.h"

#endif

/* ##########################   CORE ID functions  #################################### */
/**
  \ingroup  CMSIS_Core_IDFunctionInterface
  \defgroup CMSIS_Core_IDFunctions ID Functions
  \brief    Functions that manage Cluster and Core ID.
  @{
 */

__attribute__((always_inline)) __STATIC_INLINE uint32_t __core_ID() {
  /* encoding of mhartid: {21'b0, cluster_id_i[5:0], 1'b0, core_id_i[3:0]} */
  uint32_t mhartid = csr_read(MHARTID_ADDR);
  return mhartid & 0x01f;

}

__attribute__((always_inline)) __STATIC_INLINE uint32_t __cluster_ID() {
  /* encoding of mhartid {21'b0, cluster_id_i[5:0], 1'b0, core_id_i[3:0]} */
  uint32_t mhartid = csr_read(MHARTID_ADDR);
  return (mhartid >> 5) & 0x3f;
}

__attribute__((always_inline)) __STATIC_INLINE uint32_t __is_FC() {
#ifndef FEATURE_CLUSTER
  return 1;
#else
  return ( __cluster_ID() == FC_CLUSTER_ID);
#endif
}
/*@} end of CMSIS_Core_IDFunctions */



/* ##########################   CORE ID functions  #################################### */
/**
  \ingroup  CMSIS_Core_PerformanceFunctionInterface
  \defgroup CMSIS_Core_PerformanceFunctions Performance Functions
  \brief    Functions that manage Core performance.
  @{
 */

/* Configure the active events. eventMask is an OR of events got through SPR_PCER_EVENT_MASK */
__attribute__((always_inline)) __STATIC_INLINE void __PCER_Set(uint32_t eventMask)
{
    csr_write(PCER_ADDR, eventMask);
}

/* Return events configuration */
__attribute__((always_inline)) __STATIC_INLINE uint32_t __PCER_Get()
{
    uint32_t result = csr_read(PCER_ADDR);
    return result;
}

/* Configure the mode. confMask is an OR of all SPR_PCMR_* macros */
__attribute__((always_inline)) __STATIC_INLINE void __PCMR_Set(uint32_t value)
{
    csr_write(PCMR_ADDR, value);
}

/* Get the PCMR */
__attribute__((always_inline)) __STATIC_INLINE uint32_t __PCMR_Get()
{
    uint32_t result = csr_read(PCER_ADDR);
    return result;
}

/* Return the value of the specified counter */
__attribute__((always_inline)) __STATIC_INLINE uint32_t __PCCRs_Get(const uint32_t counterId)
{
  uint32_t value = 0;

  switch (counterId)
  {
      /* CYCLE */
  case PERF_CYCLE_OFFSET: __ASM volatile ("csrr %0, 0x780" : "=r" (value)); break;
      /* INSTR */
  case PERF_INSTR_OFFSET: __ASM volatile ("csrr %0, 0x781" : "=r" (value)); break;
      /* LD_STALL */
  case PERF_LD_STALL_OFFSET: __ASM volatile ("csrr %0, 0x782" : "=r" (value)); break;
      /* JR_STALL */
  case PERF_JR_STALL_OFFSET: __ASM volatile ("csrr %0, 0x783" : "=r" (value)); break;
      /* IMISS */
  case PERF_IMISS_OFFSET: __ASM volatile ("csrr %0, 0x784" : "=r" (value)); break;
      /* LD */
  case PERF_LD_OFFSET: __ASM volatile ("csrr %0, 0x785" : "=r" (value)); break;
      /* ST */
  case PERF_ST_OFFSET: __ASM volatile ("csrr %0, 0x786" : "=r" (value)); break;
      /* JUMP */
  case PERF_JUMP_OFFSET: __ASM volatile ("csrr %0, 0x787" : "=r" (value)); break;
      /* BRANCH */
  case PERF_BRANCH_OFFSET: __ASM volatile ("csrr %0, 0x788" : "=r" (value)); break;
      /* BTAKEN */
  case PERF_BTAKEN_OFFSET: __ASM volatile ("csrr %0, 0x789" : "=r" (value)); break;
      /* RVC */
  case PERF_RVC_OFFSET: __ASM volatile ("csrr %0, 0x78A" : "=r" (value)); break;
      /* LD_EXT */
  case PERF_LD_EXT_OFFSET: __ASM volatile ("csrr %0, 0x78B" : "=r" (value)); break;
      /* ST_EXT */
  case PERF_ST_EXT_OFFSET: __ASM volatile ("csrr %0, 0x78C" : "=r" (value)); break;
      /* LD_EXT_CYC */
  case PERF_LD_EXT_CYC_OFFSET: __ASM volatile ("csrr %0, 0x78D" : "=r" (value)); break;
      /* ST_EXT_CYC */
  case PERF_ST_EXT_CYC_OFFSET: __ASM volatile ("csrr %0, 0x78E" : "=r" (value)); break;
      /* TCDM_COUNT */
  case PERF_TCDM_COUNT_OFFSET: __ASM volatile ("csrr %0, 0x78F" : "=r" (value)); break;
  }
  return value;
}

/* Special Register, a write to this register will set all counter to the supplied value */
__attribute__((always_inline)) __STATIC_INLINE void __PCCR31_Set(uint32_t value)
{
    __ASM volatile ("csrw 0x79F, %0" :: "r" (value));
}

/*@} end of CMSIS_Core_PerformanceFunctions */


#ifdef __cplusplus
}
#endif

#endif /* __CORE_PULP_H_DEPENDANT */

#endif /* __CMSIS_GENERIC */
