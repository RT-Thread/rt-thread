/*
** ###################################################################
**     Processors:          MIMXRT1171AVM8A
**                          MIMXRT1171AVM8B
**                          MIMXRT1171CVM8A
**                          MIMXRT1171CVM8B
**                          MIMXRT1171DVMAA
**                          MIMXRT1171DVMAB
**                          MIMXRT1172AVM8A
**                          MIMXRT1172AVM8B
**                          MIMXRT1172CVM8A
**                          MIMXRT1172CVM8B
**                          MIMXRT1172DVMAA
**                          MIMXRT1172DVMAB
**                          MIMXRT1173CVM8A_cm4
**                          MIMXRT1173CVM8A_cm7
**                          MIMXRT1173CVM8B_cm4
**                          MIMXRT1173CVM8B_cm7
**                          MIMXRT1175AVM8A_cm4
**                          MIMXRT1175AVM8A_cm7
**                          MIMXRT1175AVM8B_cm4
**                          MIMXRT1175AVM8B_cm7
**                          MIMXRT1175CVM8A_cm4
**                          MIMXRT1175CVM8A_cm7
**                          MIMXRT1175CVM8B_cm4
**                          MIMXRT1175CVM8B_cm7
**                          MIMXRT1175DVMAA_cm4
**                          MIMXRT1175DVMAA_cm7
**                          MIMXRT1175DVMAB_cm4
**                          MIMXRT1175DVMAB_cm7
**                          MIMXRT1176AVM8A_cm4
**                          MIMXRT1176AVM8A_cm7
**                          MIMXRT1176AVM8B_cm4
**                          MIMXRT1176AVM8B_cm7
**                          MIMXRT1176CVM8A_cm4
**                          MIMXRT1176CVM8A_cm7
**                          MIMXRT1176CVM8B_cm4
**                          MIMXRT1176CVM8B_cm7
**                          MIMXRT1176DVMAA_cm4
**                          MIMXRT1176DVMAA_cm7
**                          MIMXRT1176DVMAB_cm4
**                          MIMXRT1176DVMAB_cm7
**                          MIMXRT117HAVM8A_cm4
**                          MIMXRT117HAVM8A_cm7
**                          MIMXRT117HAVM8B_cm4
**                          MIMXRT117HAVM8B_cm7
**                          MIMXRT117HCVM8A_cm4
**                          MIMXRT117HCVM8A_cm7
**                          MIMXRT117HCVM8B_cm4
**                          MIMXRT117HCVM8B_cm7
**                          MIMXRT117HDVMAA_cm4
**                          MIMXRT117HDVMAA_cm7
**                          MIMXRT117HDVMAB_cm4
**                          MIMXRT117HDVMAB_cm7
**
**     Version:             rev. 2.0, 2024-10-29
**     Build:               b250520
**
**     Abstract:
**         CMSIS Peripheral Access Layer for FLEXRAM
**
**     Copyright 1997-2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2025 NXP
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 0.1 (2018-03-05)
**         Initial version.
**     - rev. 1.0 (2020-12-29)
**         Update header files to align with IMXRT1170RM Rev.0.
**     - rev. 2.0 (2024-10-29)
**         Change the device header file from single flat file to multiple files based on peripherals,
**         each peripheral with dedicated header file located in periphN folder.
**
** ###################################################################
*/

/*!
 * @file PERI_FLEXRAM.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for FLEXRAM
 *
 * CMSIS Peripheral Access Layer for FLEXRAM
 */

#if !defined(PERI_FLEXRAM_H_)
#define PERI_FLEXRAM_H_                          /**< Symbol preventing repeated inclusion */

#if (defined(CPU_MIMXRT1171AVM8A) || defined(CPU_MIMXRT1171AVM8B) || defined(CPU_MIMXRT1171CVM8A) || defined(CPU_MIMXRT1171CVM8B) || defined(CPU_MIMXRT1171DVMAA) || defined(CPU_MIMXRT1171DVMAB))
#include "MIMXRT1171_COMMON.h"
#elif (defined(CPU_MIMXRT1172AVM8A) || defined(CPU_MIMXRT1172AVM8B) || defined(CPU_MIMXRT1172CVM8A) || defined(CPU_MIMXRT1172CVM8B) || defined(CPU_MIMXRT1172DVMAA) || defined(CPU_MIMXRT1172DVMAB))
#include "MIMXRT1172_COMMON.h"
#elif (defined(CPU_MIMXRT1173CVM8A_cm4) || defined(CPU_MIMXRT1173CVM8B_cm4))
#include "MIMXRT1173_cm4_COMMON.h"
#elif (defined(CPU_MIMXRT1173CVM8A_cm7) || defined(CPU_MIMXRT1173CVM8B_cm7))
#include "MIMXRT1173_cm7_COMMON.h"
#elif (defined(CPU_MIMXRT1175AVM8A_cm4) || defined(CPU_MIMXRT1175AVM8B_cm4) || defined(CPU_MIMXRT1175CVM8A_cm4) || defined(CPU_MIMXRT1175CVM8B_cm4) || defined(CPU_MIMXRT1175DVMAA_cm4) || defined(CPU_MIMXRT1175DVMAB_cm4))
#include "MIMXRT1175_cm4_COMMON.h"
#elif (defined(CPU_MIMXRT1175AVM8A_cm7) || defined(CPU_MIMXRT1175AVM8B_cm7) || defined(CPU_MIMXRT1175CVM8A_cm7) || defined(CPU_MIMXRT1175CVM8B_cm7) || defined(CPU_MIMXRT1175DVMAA_cm7) || defined(CPU_MIMXRT1175DVMAB_cm7))
#include "MIMXRT1175_cm7_COMMON.h"
#elif (defined(CPU_MIMXRT1176AVM8A_cm4) || defined(CPU_MIMXRT1176AVM8B_cm4) || defined(CPU_MIMXRT1176CVM8A_cm4) || defined(CPU_MIMXRT1176CVM8B_cm4) || defined(CPU_MIMXRT1176DVMAA_cm4) || defined(CPU_MIMXRT1176DVMAB_cm4))
#include "MIMXRT1176_cm4_COMMON.h"
#elif (defined(CPU_MIMXRT1176AVM8A_cm7) || defined(CPU_MIMXRT1176AVM8B_cm7) || defined(CPU_MIMXRT1176CVM8A_cm7) || defined(CPU_MIMXRT1176CVM8B_cm7) || defined(CPU_MIMXRT1176DVMAA_cm7) || defined(CPU_MIMXRT1176DVMAB_cm7))
#include "MIMXRT1176_cm7_COMMON.h"
#elif (defined(CPU_MIMXRT117HAVM8A_cm4) || defined(CPU_MIMXRT117HAVM8B_cm4) || defined(CPU_MIMXRT117HCVM8A_cm4) || defined(CPU_MIMXRT117HCVM8B_cm4) || defined(CPU_MIMXRT117HDVMAA_cm4) || defined(CPU_MIMXRT117HDVMAB_cm4))
#include "MIMXRT117H_cm4_COMMON.h"
#elif (defined(CPU_MIMXRT117HAVM8A_cm7) || defined(CPU_MIMXRT117HAVM8B_cm7) || defined(CPU_MIMXRT117HCVM8A_cm7) || defined(CPU_MIMXRT117HCVM8B_cm7) || defined(CPU_MIMXRT117HDVMAA_cm7) || defined(CPU_MIMXRT117HDVMAB_cm7))
#include "MIMXRT117H_cm7_COMMON.h"
#else
  #error "No valid CPU defined!"
#endif

/* ----------------------------------------------------------------------------
   -- Device Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Peripheral_access_layer Device Peripheral Access Layer
 * @{
 */


/*
** Start of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic push
  #else
    #pragma push
    #pragma anon_unions
  #endif
#elif defined(__CWCC__)
  #pragma push
  #pragma cpp_extensions on
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=extended
#else
  #error Not supported compiler type
#endif

/* ----------------------------------------------------------------------------
   -- FLEXRAM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FLEXRAM_Peripheral_Access_Layer FLEXRAM Peripheral Access Layer
 * @{
 */

/** FLEXRAM - Register Layout Typedef */
typedef struct {
  __IO uint32_t TCM_CTRL;                          /**< TCM CRTL Register, offset: 0x0 */
  __IO uint32_t OCRAM_MAGIC_ADDR;                  /**< OCRAM Magic Address Register, offset: 0x4 */
  __IO uint32_t DTCM_MAGIC_ADDR;                   /**< DTCM Magic Address Register, offset: 0x8 */
  __IO uint32_t ITCM_MAGIC_ADDR;                   /**< ITCM Magic Address Register, offset: 0xC */
  __IO uint32_t INT_STATUS;                        /**< Interrupt Status Register, offset: 0x10 */
  __IO uint32_t INT_STAT_EN;                       /**< Interrupt Status Enable Register, offset: 0x14 */
  __IO uint32_t INT_SIG_EN;                        /**< Interrupt Enable Register, offset: 0x18 */
  __I  uint32_t OCRAM_ECC_SINGLE_ERROR_INFO;       /**< OCRAM single-bit ECC Error Information Register, offset: 0x1C */
  __I  uint32_t OCRAM_ECC_SINGLE_ERROR_ADDR;       /**< OCRAM single-bit ECC Error Address Register, offset: 0x20 */
  __I  uint32_t OCRAM_ECC_SINGLE_ERROR_DATA_LSB;   /**< OCRAM single-bit ECC Error Data Register, offset: 0x24 */
  __I  uint32_t OCRAM_ECC_SINGLE_ERROR_DATA_MSB;   /**< OCRAM single-bit ECC Error Data Register, offset: 0x28 */
  __I  uint32_t OCRAM_ECC_MULTI_ERROR_INFO;        /**< OCRAM multi-bit ECC Error Information Register, offset: 0x2C */
  __I  uint32_t OCRAM_ECC_MULTI_ERROR_ADDR;        /**< OCRAM multi-bit ECC Error Address Register, offset: 0x30 */
  __I  uint32_t OCRAM_ECC_MULTI_ERROR_DATA_LSB;    /**< OCRAM multi-bit ECC Error Data Register, offset: 0x34 */
  __I  uint32_t OCRAM_ECC_MULTI_ERROR_DATA_MSB;    /**< OCRAM multi-bit ECC Error Data Register, offset: 0x38 */
  __I  uint32_t ITCM_ECC_SINGLE_ERROR_INFO;        /**< ITCM single-bit ECC Error Information Register, offset: 0x3C */
  __I  uint32_t ITCM_ECC_SINGLE_ERROR_ADDR;        /**< ITCM single-bit ECC Error Address Register, offset: 0x40 */
  __I  uint32_t ITCM_ECC_SINGLE_ERROR_DATA_LSB;    /**< ITCM single-bit ECC Error Data Register, offset: 0x44 */
  __I  uint32_t ITCM_ECC_SINGLE_ERROR_DATA_MSB;    /**< ITCM single-bit ECC Error Data Register, offset: 0x48 */
  __I  uint32_t ITCM_ECC_MULTI_ERROR_INFO;         /**< ITCM multi-bit ECC Error Information Register, offset: 0x4C */
  __I  uint32_t ITCM_ECC_MULTI_ERROR_ADDR;         /**< ITCM multi-bit ECC Error Address Register, offset: 0x50 */
  __I  uint32_t ITCM_ECC_MULTI_ERROR_DATA_LSB;     /**< ITCM multi-bit ECC Error Data Register, offset: 0x54 */
  __I  uint32_t ITCM_ECC_MULTI_ERROR_DATA_MSB;     /**< ITCM multi-bit ECC Error Data Register, offset: 0x58 */
  __I  uint32_t D0TCM_ECC_SINGLE_ERROR_INFO;       /**< D0TCM single-bit ECC Error Information Register, offset: 0x5C */
  __I  uint32_t D0TCM_ECC_SINGLE_ERROR_ADDR;       /**< D0TCM single-bit ECC Error Address Register, offset: 0x60 */
  __I  uint32_t D0TCM_ECC_SINGLE_ERROR_DATA;       /**< D0TCM single-bit ECC Error Data Register, offset: 0x64 */
  __I  uint32_t D0TCM_ECC_MULTI_ERROR_INFO;        /**< D0TCM multi-bit ECC Error Information Register, offset: 0x68 */
  __I  uint32_t D0TCM_ECC_MULTI_ERROR_ADDR;        /**< D0TCM multi-bit ECC Error Address Register, offset: 0x6C */
  __I  uint32_t D0TCM_ECC_MULTI_ERROR_DATA;        /**< D0TCM multi-bit ECC Error Data Register, offset: 0x70 */
  __I  uint32_t D1TCM_ECC_SINGLE_ERROR_INFO;       /**< D1TCM single-bit ECC Error Information Register, offset: 0x74 */
  __I  uint32_t D1TCM_ECC_SINGLE_ERROR_ADDR;       /**< D1TCM single-bit ECC Error Address Register, offset: 0x78 */
  __I  uint32_t D1TCM_ECC_SINGLE_ERROR_DATA;       /**< D1TCM single-bit ECC Error Data Register, offset: 0x7C */
  __I  uint32_t D1TCM_ECC_MULTI_ERROR_INFO;        /**< D1TCM multi-bit ECC Error Information Register, offset: 0x80 */
  __I  uint32_t D1TCM_ECC_MULTI_ERROR_ADDR;        /**< D1TCM multi-bit ECC Error Address Register, offset: 0x84 */
  __I  uint32_t D1TCM_ECC_MULTI_ERROR_DATA;        /**< D1TCM multi-bit ECC Error Data Register, offset: 0x88 */
  __IO uint32_t OCRAM_ECC_ERROR_INJEC;             /**< OCRAM ECC Error Injection Register, offset: 0x8C */
  __IO uint32_t ITCM_ECC_ERROR_INJEC;              /**< ITCM ECC Error Injection Register, offset: 0x90 */
  __IO uint32_t D0TCM_ECC_ERROR_INJEC;             /**< D0TCM ECC Error Injection Register, offset: 0x94 */
  __IO uint32_t D1TCM_ECC_ERROR_INJEC;             /**< D1TCM ECC Error Injection Register, offset: 0x98 */
       uint8_t RESERVED_0[108];
  __IO uint32_t FLEXRAM_CTRL;                      /**< FlexRAM feature Control register, offset: 0x108 */
  __I  uint32_t OCRAM_PIPELINE_STATUS;             /**< OCRAM Pipeline Status register, offset: 0x10C */
} FLEXRAM_Type;

/* ----------------------------------------------------------------------------
   -- FLEXRAM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FLEXRAM_Register_Masks FLEXRAM Register Masks
 * @{
 */

/*! @name TCM_CTRL - TCM CRTL Register */
/*! @{ */

#define FLEXRAM_TCM_CTRL_TCM_WWAIT_EN_MASK       (0x1U)
#define FLEXRAM_TCM_CTRL_TCM_WWAIT_EN_SHIFT      (0U)
/*! TCM_WWAIT_EN - TCM Write Wait Mode Enable
 *  0b0..TCM write fast mode: Write RAM accesses are expected to be finished in 1-cycle.
 *  0b1..TCM write wait mode: Write RAM accesses are expected to be finished in 2-cycles.
 */
#define FLEXRAM_TCM_CTRL_TCM_WWAIT_EN(x)         (((uint32_t)(((uint32_t)(x)) << FLEXRAM_TCM_CTRL_TCM_WWAIT_EN_SHIFT)) & FLEXRAM_TCM_CTRL_TCM_WWAIT_EN_MASK)

#define FLEXRAM_TCM_CTRL_TCM_RWAIT_EN_MASK       (0x2U)
#define FLEXRAM_TCM_CTRL_TCM_RWAIT_EN_SHIFT      (1U)
/*! TCM_RWAIT_EN - TCM Read Wait Mode Enable
 *  0b0..TCM read fast mode: Read RAM accesses are expected to be finished in 1-cycle.
 *  0b1..TCM read wait mode: Read RAM accesses are expected to be finished in 2-cycles.
 */
#define FLEXRAM_TCM_CTRL_TCM_RWAIT_EN(x)         (((uint32_t)(((uint32_t)(x)) << FLEXRAM_TCM_CTRL_TCM_RWAIT_EN_SHIFT)) & FLEXRAM_TCM_CTRL_TCM_RWAIT_EN_MASK)

#define FLEXRAM_TCM_CTRL_FORCE_CLK_ON_MASK       (0x4U)
#define FLEXRAM_TCM_CTRL_FORCE_CLK_ON_SHIFT      (2U)
/*! FORCE_CLK_ON - Force RAM Clock Always On */
#define FLEXRAM_TCM_CTRL_FORCE_CLK_ON(x)         (((uint32_t)(((uint32_t)(x)) << FLEXRAM_TCM_CTRL_FORCE_CLK_ON_SHIFT)) & FLEXRAM_TCM_CTRL_FORCE_CLK_ON_MASK)

#define FLEXRAM_TCM_CTRL_Reserved_MASK           (0xFFFFFFF8U)
#define FLEXRAM_TCM_CTRL_Reserved_SHIFT          (3U)
/*! Reserved - Reserved */
#define FLEXRAM_TCM_CTRL_Reserved(x)             (((uint32_t)(((uint32_t)(x)) << FLEXRAM_TCM_CTRL_Reserved_SHIFT)) & FLEXRAM_TCM_CTRL_Reserved_MASK)
/*! @} */

/*! @name OCRAM_MAGIC_ADDR - OCRAM Magic Address Register */
/*! @{ */

#define FLEXRAM_OCRAM_MAGIC_ADDR_OCRAM_WR_RD_SEL_MASK (0x1U)
#define FLEXRAM_OCRAM_MAGIC_ADDR_OCRAM_WR_RD_SEL_SHIFT (0U)
/*! OCRAM_WR_RD_SEL - OCRAM Write Read Select
 *  0b0..When OCRAM read access hits magic address, it will generate interrupt.
 *  0b1..When OCRAM write access hits magic address, it will generate interrupt.
 */
#define FLEXRAM_OCRAM_MAGIC_ADDR_OCRAM_WR_RD_SEL(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_OCRAM_MAGIC_ADDR_OCRAM_WR_RD_SEL_SHIFT)) & FLEXRAM_OCRAM_MAGIC_ADDR_OCRAM_WR_RD_SEL_MASK)

#define FLEXRAM_OCRAM_MAGIC_ADDR_OCRAM_MAGIC_ADDR_MASK (0x3FFFEU)
#define FLEXRAM_OCRAM_MAGIC_ADDR_OCRAM_MAGIC_ADDR_SHIFT (1U)
/*! OCRAM_MAGIC_ADDR - OCRAM Magic Address */
#define FLEXRAM_OCRAM_MAGIC_ADDR_OCRAM_MAGIC_ADDR(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_OCRAM_MAGIC_ADDR_OCRAM_MAGIC_ADDR_SHIFT)) & FLEXRAM_OCRAM_MAGIC_ADDR_OCRAM_MAGIC_ADDR_MASK)

#define FLEXRAM_OCRAM_MAGIC_ADDR_Reserved_MASK   (0xFFFC0000U)
#define FLEXRAM_OCRAM_MAGIC_ADDR_Reserved_SHIFT  (18U)
/*! Reserved - Reserved */
#define FLEXRAM_OCRAM_MAGIC_ADDR_Reserved(x)     (((uint32_t)(((uint32_t)(x)) << FLEXRAM_OCRAM_MAGIC_ADDR_Reserved_SHIFT)) & FLEXRAM_OCRAM_MAGIC_ADDR_Reserved_MASK)
/*! @} */

/*! @name DTCM_MAGIC_ADDR - DTCM Magic Address Register */
/*! @{ */

#define FLEXRAM_DTCM_MAGIC_ADDR_DTCM_WR_RD_SEL_MASK (0x1U)
#define FLEXRAM_DTCM_MAGIC_ADDR_DTCM_WR_RD_SEL_SHIFT (0U)
/*! DTCM_WR_RD_SEL - DTCM Write Read Select
 *  0b0..When DTCM read access hits magic address, it will generate interrupt.
 *  0b1..When DTCM write access hits magic address, it will generate interrupt.
 */
#define FLEXRAM_DTCM_MAGIC_ADDR_DTCM_WR_RD_SEL(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_DTCM_MAGIC_ADDR_DTCM_WR_RD_SEL_SHIFT)) & FLEXRAM_DTCM_MAGIC_ADDR_DTCM_WR_RD_SEL_MASK)

#define FLEXRAM_DTCM_MAGIC_ADDR_DTCM_MAGIC_ADDR_MASK (0x1FFFEU)
#define FLEXRAM_DTCM_MAGIC_ADDR_DTCM_MAGIC_ADDR_SHIFT (1U)
/*! DTCM_MAGIC_ADDR - DTCM Magic Address */
#define FLEXRAM_DTCM_MAGIC_ADDR_DTCM_MAGIC_ADDR(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_DTCM_MAGIC_ADDR_DTCM_MAGIC_ADDR_SHIFT)) & FLEXRAM_DTCM_MAGIC_ADDR_DTCM_MAGIC_ADDR_MASK)

#define FLEXRAM_DTCM_MAGIC_ADDR_Reserved_MASK    (0xFFFE0000U)
#define FLEXRAM_DTCM_MAGIC_ADDR_Reserved_SHIFT   (17U)
/*! Reserved - Reserved */
#define FLEXRAM_DTCM_MAGIC_ADDR_Reserved(x)      (((uint32_t)(((uint32_t)(x)) << FLEXRAM_DTCM_MAGIC_ADDR_Reserved_SHIFT)) & FLEXRAM_DTCM_MAGIC_ADDR_Reserved_MASK)
/*! @} */

/*! @name ITCM_MAGIC_ADDR - ITCM Magic Address Register */
/*! @{ */

#define FLEXRAM_ITCM_MAGIC_ADDR_ITCM_WR_RD_SEL_MASK (0x1U)
#define FLEXRAM_ITCM_MAGIC_ADDR_ITCM_WR_RD_SEL_SHIFT (0U)
/*! ITCM_WR_RD_SEL - ITCM Write Read Select
 *  0b0..When ITCM read access hits magic address, it will generate interrupt.
 *  0b1..When ITCM write access hits magic address, it will generate interrupt.
 */
#define FLEXRAM_ITCM_MAGIC_ADDR_ITCM_WR_RD_SEL(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_ITCM_MAGIC_ADDR_ITCM_WR_RD_SEL_SHIFT)) & FLEXRAM_ITCM_MAGIC_ADDR_ITCM_WR_RD_SEL_MASK)

#define FLEXRAM_ITCM_MAGIC_ADDR_ITCM_MAGIC_ADDR_MASK (0x1FFFEU)
#define FLEXRAM_ITCM_MAGIC_ADDR_ITCM_MAGIC_ADDR_SHIFT (1U)
/*! ITCM_MAGIC_ADDR - ITCM Magic Address */
#define FLEXRAM_ITCM_MAGIC_ADDR_ITCM_MAGIC_ADDR(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_ITCM_MAGIC_ADDR_ITCM_MAGIC_ADDR_SHIFT)) & FLEXRAM_ITCM_MAGIC_ADDR_ITCM_MAGIC_ADDR_MASK)

#define FLEXRAM_ITCM_MAGIC_ADDR_Reserved_MASK    (0xFFFE0000U)
#define FLEXRAM_ITCM_MAGIC_ADDR_Reserved_SHIFT   (17U)
/*! Reserved - Reserved */
#define FLEXRAM_ITCM_MAGIC_ADDR_Reserved(x)      (((uint32_t)(((uint32_t)(x)) << FLEXRAM_ITCM_MAGIC_ADDR_Reserved_SHIFT)) & FLEXRAM_ITCM_MAGIC_ADDR_Reserved_MASK)
/*! @} */

/*! @name INT_STATUS - Interrupt Status Register */
/*! @{ */

#define FLEXRAM_INT_STATUS_ITCM_MAM_STATUS_MASK  (0x1U)
#define FLEXRAM_INT_STATUS_ITCM_MAM_STATUS_SHIFT (0U)
/*! ITCM_MAM_STATUS - ITCM Magic Address Match Status
 *  0b0..ITCM did not access magic address.
 *  0b1..ITCM accessed magic address.
 */
#define FLEXRAM_INT_STATUS_ITCM_MAM_STATUS(x)    (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_STATUS_ITCM_MAM_STATUS_SHIFT)) & FLEXRAM_INT_STATUS_ITCM_MAM_STATUS_MASK)

#define FLEXRAM_INT_STATUS_DTCM_MAM_STATUS_MASK  (0x2U)
#define FLEXRAM_INT_STATUS_DTCM_MAM_STATUS_SHIFT (1U)
/*! DTCM_MAM_STATUS - DTCM Magic Address Match Status
 *  0b0..DTCM did not access magic address.
 *  0b1..DTCM accessed magic address.
 */
#define FLEXRAM_INT_STATUS_DTCM_MAM_STATUS(x)    (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_STATUS_DTCM_MAM_STATUS_SHIFT)) & FLEXRAM_INT_STATUS_DTCM_MAM_STATUS_MASK)

#define FLEXRAM_INT_STATUS_OCRAM_MAM_STATUS_MASK (0x4U)
#define FLEXRAM_INT_STATUS_OCRAM_MAM_STATUS_SHIFT (2U)
/*! OCRAM_MAM_STATUS - OCRAM Magic Address Match Status
 *  0b0..OCRAM did not access magic address.
 *  0b1..OCRAM accessed magic address.
 */
#define FLEXRAM_INT_STATUS_OCRAM_MAM_STATUS(x)   (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_STATUS_OCRAM_MAM_STATUS_SHIFT)) & FLEXRAM_INT_STATUS_OCRAM_MAM_STATUS_MASK)

#define FLEXRAM_INT_STATUS_ITCM_ERR_STATUS_MASK  (0x8U)
#define FLEXRAM_INT_STATUS_ITCM_ERR_STATUS_SHIFT (3U)
/*! ITCM_ERR_STATUS - ITCM Access Error Status
 *  0b0..ITCM access error does not happen
 *  0b1..ITCM access error happens.
 */
#define FLEXRAM_INT_STATUS_ITCM_ERR_STATUS(x)    (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_STATUS_ITCM_ERR_STATUS_SHIFT)) & FLEXRAM_INT_STATUS_ITCM_ERR_STATUS_MASK)

#define FLEXRAM_INT_STATUS_DTCM_ERR_STATUS_MASK  (0x10U)
#define FLEXRAM_INT_STATUS_DTCM_ERR_STATUS_SHIFT (4U)
/*! DTCM_ERR_STATUS - DTCM Access Error Status
 *  0b0..DTCM access error does not happen
 *  0b1..DTCM access error happens.
 */
#define FLEXRAM_INT_STATUS_DTCM_ERR_STATUS(x)    (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_STATUS_DTCM_ERR_STATUS_SHIFT)) & FLEXRAM_INT_STATUS_DTCM_ERR_STATUS_MASK)

#define FLEXRAM_INT_STATUS_OCRAM_ERR_STATUS_MASK (0x20U)
#define FLEXRAM_INT_STATUS_OCRAM_ERR_STATUS_SHIFT (5U)
/*! OCRAM_ERR_STATUS - OCRAM Access Error Status
 *  0b0..OCRAM access error does not happen
 *  0b1..OCRAM access error happens.
 */
#define FLEXRAM_INT_STATUS_OCRAM_ERR_STATUS(x)   (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_STATUS_OCRAM_ERR_STATUS_SHIFT)) & FLEXRAM_INT_STATUS_OCRAM_ERR_STATUS_MASK)

#define FLEXRAM_INT_STATUS_OCRAM_ECC_ERRM_INT_MASK (0x40U)
#define FLEXRAM_INT_STATUS_OCRAM_ECC_ERRM_INT_SHIFT (6U)
/*! OCRAM_ECC_ERRM_INT - OCRAM access multi-bit ECC Error Interrupt Status
 *  0b0..OCRAM multi-bit ECC error does not happen
 *  0b1..OCRAM multi-bit ECC error happens.
 */
#define FLEXRAM_INT_STATUS_OCRAM_ECC_ERRM_INT(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_STATUS_OCRAM_ECC_ERRM_INT_SHIFT)) & FLEXRAM_INT_STATUS_OCRAM_ECC_ERRM_INT_MASK)

#define FLEXRAM_INT_STATUS_OCRAM_ECC_ERRS_INT_MASK (0x80U)
#define FLEXRAM_INT_STATUS_OCRAM_ECC_ERRS_INT_SHIFT (7U)
/*! OCRAM_ECC_ERRS_INT - OCRAM access single-bit ECC Error Interrupt Status
 *  0b0..OCRAM single-bit ECC error does not happen
 *  0b1..OCRAM single-bit ECC error happens.
 */
#define FLEXRAM_INT_STATUS_OCRAM_ECC_ERRS_INT(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_STATUS_OCRAM_ECC_ERRS_INT_SHIFT)) & FLEXRAM_INT_STATUS_OCRAM_ECC_ERRS_INT_MASK)

#define FLEXRAM_INT_STATUS_ITCM_ECC_ERRM_INT_MASK (0x100U)
#define FLEXRAM_INT_STATUS_ITCM_ECC_ERRM_INT_SHIFT (8U)
/*! ITCM_ECC_ERRM_INT - ITCM Access multi-bit ECC Error Interrupt Status
 *  0b0..ITCM multi-bit ECC error does not happen
 *  0b1..ITCM multi-bit ECC error happens.
 */
#define FLEXRAM_INT_STATUS_ITCM_ECC_ERRM_INT(x)  (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_STATUS_ITCM_ECC_ERRM_INT_SHIFT)) & FLEXRAM_INT_STATUS_ITCM_ECC_ERRM_INT_MASK)

#define FLEXRAM_INT_STATUS_ITCM_ECC_ERRS_INT_MASK (0x200U)
#define FLEXRAM_INT_STATUS_ITCM_ECC_ERRS_INT_SHIFT (9U)
/*! ITCM_ECC_ERRS_INT - ITCM access single-bit ECC Error Interrupt Status
 *  0b0..ITCM single-bit ECC error does not happen
 *  0b1..ITCM single-bit ECC error happens.
 */
#define FLEXRAM_INT_STATUS_ITCM_ECC_ERRS_INT(x)  (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_STATUS_ITCM_ECC_ERRS_INT_SHIFT)) & FLEXRAM_INT_STATUS_ITCM_ECC_ERRS_INT_MASK)

#define FLEXRAM_INT_STATUS_D0TCM_ECC_ERRM_INT_MASK (0x400U)
#define FLEXRAM_INT_STATUS_D0TCM_ECC_ERRM_INT_SHIFT (10U)
/*! D0TCM_ECC_ERRM_INT - D0TCM access multi-bit ECC Error Interrupt Status
 *  0b0..D0TCM multi-bit ECC error does not happen
 *  0b1..D0TCM multi-bit ECC error happens.
 */
#define FLEXRAM_INT_STATUS_D0TCM_ECC_ERRM_INT(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_STATUS_D0TCM_ECC_ERRM_INT_SHIFT)) & FLEXRAM_INT_STATUS_D0TCM_ECC_ERRM_INT_MASK)

#define FLEXRAM_INT_STATUS_D0TCM_ECC_ERRS_INT_MASK (0x800U)
#define FLEXRAM_INT_STATUS_D0TCM_ECC_ERRS_INT_SHIFT (11U)
/*! D0TCM_ECC_ERRS_INT - D0TCM access single-bit ECC Error Interrupt Status
 *  0b0..D0TCM single-bit ECC error does not happen
 *  0b1..D0TCM single-bit ECC error happens.
 */
#define FLEXRAM_INT_STATUS_D0TCM_ECC_ERRS_INT(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_STATUS_D0TCM_ECC_ERRS_INT_SHIFT)) & FLEXRAM_INT_STATUS_D0TCM_ECC_ERRS_INT_MASK)

#define FLEXRAM_INT_STATUS_D1TCM_ECC_ERRM_INT_MASK (0x1000U)
#define FLEXRAM_INT_STATUS_D1TCM_ECC_ERRM_INT_SHIFT (12U)
/*! D1TCM_ECC_ERRM_INT - D1TCM access multi-bit ECC Error Interrupt Status
 *  0b0..D1TCM multi-bit ECC error does not happen
 *  0b1..D1TCM multi-bit ECC error happens.
 */
#define FLEXRAM_INT_STATUS_D1TCM_ECC_ERRM_INT(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_STATUS_D1TCM_ECC_ERRM_INT_SHIFT)) & FLEXRAM_INT_STATUS_D1TCM_ECC_ERRM_INT_MASK)

#define FLEXRAM_INT_STATUS_D1TCM_ECC_ERRS_INT_MASK (0x2000U)
#define FLEXRAM_INT_STATUS_D1TCM_ECC_ERRS_INT_SHIFT (13U)
/*! D1TCM_ECC_ERRS_INT - D1TCM access single-bit ECC Error Interrupt Status
 *  0b0..D1TCM single-bit ECC error does not happen
 *  0b1..D1TCM single-bit ECC error happens.
 */
#define FLEXRAM_INT_STATUS_D1TCM_ECC_ERRS_INT(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_STATUS_D1TCM_ECC_ERRS_INT_SHIFT)) & FLEXRAM_INT_STATUS_D1TCM_ECC_ERRS_INT_MASK)

#define FLEXRAM_INT_STATUS_OCRAM_PARTIAL_WR_INT_S_MASK (0x20000U)
#define FLEXRAM_INT_STATUS_OCRAM_PARTIAL_WR_INT_S_SHIFT (17U)
/*! OCRAM_PARTIAL_WR_INT_S - OCRAM Partial Write Interrupt Status
 *  0b0..OCRAM Partial Write does not happen
 *  0b1..OCRAM Partial Write happens.
 */
#define FLEXRAM_INT_STATUS_OCRAM_PARTIAL_WR_INT_S(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_STATUS_OCRAM_PARTIAL_WR_INT_S_SHIFT)) & FLEXRAM_INT_STATUS_OCRAM_PARTIAL_WR_INT_S_MASK)

#define FLEXRAM_INT_STATUS_Reserved_MASK         (0xFFFC0000U)
#define FLEXRAM_INT_STATUS_Reserved_SHIFT        (18U)
/*! Reserved - Reserved */
#define FLEXRAM_INT_STATUS_Reserved(x)           (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_STATUS_Reserved_SHIFT)) & FLEXRAM_INT_STATUS_Reserved_MASK)
/*! @} */

/*! @name INT_STAT_EN - Interrupt Status Enable Register */
/*! @{ */

#define FLEXRAM_INT_STAT_EN_ITCM_MAM_STAT_EN_MASK (0x1U)
#define FLEXRAM_INT_STAT_EN_ITCM_MAM_STAT_EN_SHIFT (0U)
/*! ITCM_MAM_STAT_EN - ITCM Magic Address Match Status Enable
 *  0b0..Masked
 *  0b1..Enabled
 */
#define FLEXRAM_INT_STAT_EN_ITCM_MAM_STAT_EN(x)  (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_STAT_EN_ITCM_MAM_STAT_EN_SHIFT)) & FLEXRAM_INT_STAT_EN_ITCM_MAM_STAT_EN_MASK)

#define FLEXRAM_INT_STAT_EN_DTCM_MAM_STAT_EN_MASK (0x2U)
#define FLEXRAM_INT_STAT_EN_DTCM_MAM_STAT_EN_SHIFT (1U)
/*! DTCM_MAM_STAT_EN - DTCM Magic Address Match Status Enable
 *  0b0..Masked
 *  0b1..Enabled
 */
#define FLEXRAM_INT_STAT_EN_DTCM_MAM_STAT_EN(x)  (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_STAT_EN_DTCM_MAM_STAT_EN_SHIFT)) & FLEXRAM_INT_STAT_EN_DTCM_MAM_STAT_EN_MASK)

#define FLEXRAM_INT_STAT_EN_OCRAM_MAM_STAT_EN_MASK (0x4U)
#define FLEXRAM_INT_STAT_EN_OCRAM_MAM_STAT_EN_SHIFT (2U)
/*! OCRAM_MAM_STAT_EN - OCRAM Magic Address Match Status Enable
 *  0b0..Masked
 *  0b1..Enabled
 */
#define FLEXRAM_INT_STAT_EN_OCRAM_MAM_STAT_EN(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_STAT_EN_OCRAM_MAM_STAT_EN_SHIFT)) & FLEXRAM_INT_STAT_EN_OCRAM_MAM_STAT_EN_MASK)

#define FLEXRAM_INT_STAT_EN_ITCM_ERR_STAT_EN_MASK (0x8U)
#define FLEXRAM_INT_STAT_EN_ITCM_ERR_STAT_EN_SHIFT (3U)
/*! ITCM_ERR_STAT_EN - ITCM Access Error Status Enable
 *  0b0..Masked
 *  0b1..Enabled
 */
#define FLEXRAM_INT_STAT_EN_ITCM_ERR_STAT_EN(x)  (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_STAT_EN_ITCM_ERR_STAT_EN_SHIFT)) & FLEXRAM_INT_STAT_EN_ITCM_ERR_STAT_EN_MASK)

#define FLEXRAM_INT_STAT_EN_DTCM_ERR_STAT_EN_MASK (0x10U)
#define FLEXRAM_INT_STAT_EN_DTCM_ERR_STAT_EN_SHIFT (4U)
/*! DTCM_ERR_STAT_EN - DTCM Access Error Status Enable
 *  0b0..Masked
 *  0b1..Enabled
 */
#define FLEXRAM_INT_STAT_EN_DTCM_ERR_STAT_EN(x)  (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_STAT_EN_DTCM_ERR_STAT_EN_SHIFT)) & FLEXRAM_INT_STAT_EN_DTCM_ERR_STAT_EN_MASK)

#define FLEXRAM_INT_STAT_EN_OCRAM_ERR_STAT_EN_MASK (0x20U)
#define FLEXRAM_INT_STAT_EN_OCRAM_ERR_STAT_EN_SHIFT (5U)
/*! OCRAM_ERR_STAT_EN - OCRAM Access Error Status Enable
 *  0b0..Masked
 *  0b1..Enabled
 */
#define FLEXRAM_INT_STAT_EN_OCRAM_ERR_STAT_EN(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_STAT_EN_OCRAM_ERR_STAT_EN_SHIFT)) & FLEXRAM_INT_STAT_EN_OCRAM_ERR_STAT_EN_MASK)

#define FLEXRAM_INT_STAT_EN_OCRAM_ERRM_INT_EN_MASK (0x40U)
#define FLEXRAM_INT_STAT_EN_OCRAM_ERRM_INT_EN_SHIFT (6U)
/*! OCRAM_ERRM_INT_EN - OCRAM Access multi-bit ECC Error Interrupt Status Enable
 *  0b0..Masked
 *  0b1..Enabled
 */
#define FLEXRAM_INT_STAT_EN_OCRAM_ERRM_INT_EN(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_STAT_EN_OCRAM_ERRM_INT_EN_SHIFT)) & FLEXRAM_INT_STAT_EN_OCRAM_ERRM_INT_EN_MASK)

#define FLEXRAM_INT_STAT_EN_OCRAM_ERRS_INT_EN_MASK (0x80U)
#define FLEXRAM_INT_STAT_EN_OCRAM_ERRS_INT_EN_SHIFT (7U)
/*! OCRAM_ERRS_INT_EN - OCRAM Access single-bit ECC Error Interrupt Status Enable
 *  0b0..Masked
 *  0b1..Enabled
 */
#define FLEXRAM_INT_STAT_EN_OCRAM_ERRS_INT_EN(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_STAT_EN_OCRAM_ERRS_INT_EN_SHIFT)) & FLEXRAM_INT_STAT_EN_OCRAM_ERRS_INT_EN_MASK)

#define FLEXRAM_INT_STAT_EN_ITCM_ERRM_INT_EN_MASK (0x100U)
#define FLEXRAM_INT_STAT_EN_ITCM_ERRM_INT_EN_SHIFT (8U)
/*! ITCM_ERRM_INT_EN - ITCM Access multi-bit ECC Error Interrupt Status Enable
 *  0b0..Masked
 *  0b1..Enabled
 */
#define FLEXRAM_INT_STAT_EN_ITCM_ERRM_INT_EN(x)  (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_STAT_EN_ITCM_ERRM_INT_EN_SHIFT)) & FLEXRAM_INT_STAT_EN_ITCM_ERRM_INT_EN_MASK)

#define FLEXRAM_INT_STAT_EN_ITCM_ERRS_INT_EN_MASK (0x200U)
#define FLEXRAM_INT_STAT_EN_ITCM_ERRS_INT_EN_SHIFT (9U)
/*! ITCM_ERRS_INT_EN - ITCM Access single-bit ECC Error Interrupt Status Enable
 *  0b0..Masked
 *  0b1..Enabled
 */
#define FLEXRAM_INT_STAT_EN_ITCM_ERRS_INT_EN(x)  (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_STAT_EN_ITCM_ERRS_INT_EN_SHIFT)) & FLEXRAM_INT_STAT_EN_ITCM_ERRS_INT_EN_MASK)

#define FLEXRAM_INT_STAT_EN_D0TCM_ERRM_INT_EN_MASK (0x400U)
#define FLEXRAM_INT_STAT_EN_D0TCM_ERRM_INT_EN_SHIFT (10U)
/*! D0TCM_ERRM_INT_EN - D0TCM Access multi-bit ECC Error Interrupt Status Enable
 *  0b0..Masked
 *  0b1..Enabled
 */
#define FLEXRAM_INT_STAT_EN_D0TCM_ERRM_INT_EN(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_STAT_EN_D0TCM_ERRM_INT_EN_SHIFT)) & FLEXRAM_INT_STAT_EN_D0TCM_ERRM_INT_EN_MASK)

#define FLEXRAM_INT_STAT_EN_D0TCM_ERRS_INT_EN_MASK (0x800U)
#define FLEXRAM_INT_STAT_EN_D0TCM_ERRS_INT_EN_SHIFT (11U)
/*! D0TCM_ERRS_INT_EN - D0TCM Access single-bit ECC Error Interrupt Status Enable
 *  0b0..Masked
 *  0b1..Enabled
 */
#define FLEXRAM_INT_STAT_EN_D0TCM_ERRS_INT_EN(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_STAT_EN_D0TCM_ERRS_INT_EN_SHIFT)) & FLEXRAM_INT_STAT_EN_D0TCM_ERRS_INT_EN_MASK)

#define FLEXRAM_INT_STAT_EN_D1TCM_ERRM_INT_EN_MASK (0x1000U)
#define FLEXRAM_INT_STAT_EN_D1TCM_ERRM_INT_EN_SHIFT (12U)
/*! D1TCM_ERRM_INT_EN - D1TCM Access multi-bit ECC Error Interrupt Status Enable
 *  0b0..Masked
 *  0b1..Enabled
 */
#define FLEXRAM_INT_STAT_EN_D1TCM_ERRM_INT_EN(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_STAT_EN_D1TCM_ERRM_INT_EN_SHIFT)) & FLEXRAM_INT_STAT_EN_D1TCM_ERRM_INT_EN_MASK)

#define FLEXRAM_INT_STAT_EN_D1TCM_ERRS_INT_EN_MASK (0x2000U)
#define FLEXRAM_INT_STAT_EN_D1TCM_ERRS_INT_EN_SHIFT (13U)
/*! D1TCM_ERRS_INT_EN - D1TCM Access single-bit ECC Error Interrupt Status Enable
 *  0b0..Masked
 *  0b1..Enabled
 */
#define FLEXRAM_INT_STAT_EN_D1TCM_ERRS_INT_EN(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_STAT_EN_D1TCM_ERRS_INT_EN_SHIFT)) & FLEXRAM_INT_STAT_EN_D1TCM_ERRS_INT_EN_MASK)

#define FLEXRAM_INT_STAT_EN_OCRAM_PARTIAL_WR_INT_S_EN_MASK (0x20000U)
#define FLEXRAM_INT_STAT_EN_OCRAM_PARTIAL_WR_INT_S_EN_SHIFT (17U)
/*! OCRAM_PARTIAL_WR_INT_S_EN - OCRAM Partial Write Interrupt Status Enable
 *  0b0..Masked
 *  0b1..Enabled
 */
#define FLEXRAM_INT_STAT_EN_OCRAM_PARTIAL_WR_INT_S_EN(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_STAT_EN_OCRAM_PARTIAL_WR_INT_S_EN_SHIFT)) & FLEXRAM_INT_STAT_EN_OCRAM_PARTIAL_WR_INT_S_EN_MASK)

#define FLEXRAM_INT_STAT_EN_Reserved_MASK        (0xFFFC0000U)
#define FLEXRAM_INT_STAT_EN_Reserved_SHIFT       (18U)
/*! Reserved - Reserved */
#define FLEXRAM_INT_STAT_EN_Reserved(x)          (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_STAT_EN_Reserved_SHIFT)) & FLEXRAM_INT_STAT_EN_Reserved_MASK)
/*! @} */

/*! @name INT_SIG_EN - Interrupt Enable Register */
/*! @{ */

#define FLEXRAM_INT_SIG_EN_ITCM_MAM_SIG_EN_MASK  (0x1U)
#define FLEXRAM_INT_SIG_EN_ITCM_MAM_SIG_EN_SHIFT (0U)
/*! ITCM_MAM_SIG_EN - ITCM Magic Address Match Interrupt Enable
 *  0b0..Masked
 *  0b1..Enabled
 */
#define FLEXRAM_INT_SIG_EN_ITCM_MAM_SIG_EN(x)    (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_SIG_EN_ITCM_MAM_SIG_EN_SHIFT)) & FLEXRAM_INT_SIG_EN_ITCM_MAM_SIG_EN_MASK)

#define FLEXRAM_INT_SIG_EN_DTCM_MAM_SIG_EN_MASK  (0x2U)
#define FLEXRAM_INT_SIG_EN_DTCM_MAM_SIG_EN_SHIFT (1U)
/*! DTCM_MAM_SIG_EN - DTCM Magic Address Match Interrupt Enable
 *  0b0..Masked
 *  0b1..Enabled
 */
#define FLEXRAM_INT_SIG_EN_DTCM_MAM_SIG_EN(x)    (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_SIG_EN_DTCM_MAM_SIG_EN_SHIFT)) & FLEXRAM_INT_SIG_EN_DTCM_MAM_SIG_EN_MASK)

#define FLEXRAM_INT_SIG_EN_OCRAM_MAM_SIG_EN_MASK (0x4U)
#define FLEXRAM_INT_SIG_EN_OCRAM_MAM_SIG_EN_SHIFT (2U)
/*! OCRAM_MAM_SIG_EN - OCRAM Magic Address Match Interrupt Enable
 *  0b0..Masked
 *  0b1..Enabled
 */
#define FLEXRAM_INT_SIG_EN_OCRAM_MAM_SIG_EN(x)   (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_SIG_EN_OCRAM_MAM_SIG_EN_SHIFT)) & FLEXRAM_INT_SIG_EN_OCRAM_MAM_SIG_EN_MASK)

#define FLEXRAM_INT_SIG_EN_ITCM_ERR_SIG_EN_MASK  (0x8U)
#define FLEXRAM_INT_SIG_EN_ITCM_ERR_SIG_EN_SHIFT (3U)
/*! ITCM_ERR_SIG_EN - ITCM Access Error Interrupt Enable
 *  0b0..Masked
 *  0b1..Enabled
 */
#define FLEXRAM_INT_SIG_EN_ITCM_ERR_SIG_EN(x)    (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_SIG_EN_ITCM_ERR_SIG_EN_SHIFT)) & FLEXRAM_INT_SIG_EN_ITCM_ERR_SIG_EN_MASK)

#define FLEXRAM_INT_SIG_EN_DTCM_ERR_SIG_EN_MASK  (0x10U)
#define FLEXRAM_INT_SIG_EN_DTCM_ERR_SIG_EN_SHIFT (4U)
/*! DTCM_ERR_SIG_EN - DTCM Access Error Interrupt Enable
 *  0b0..Masked
 *  0b1..Enabled
 */
#define FLEXRAM_INT_SIG_EN_DTCM_ERR_SIG_EN(x)    (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_SIG_EN_DTCM_ERR_SIG_EN_SHIFT)) & FLEXRAM_INT_SIG_EN_DTCM_ERR_SIG_EN_MASK)

#define FLEXRAM_INT_SIG_EN_OCRAM_ERR_SIG_EN_MASK (0x20U)
#define FLEXRAM_INT_SIG_EN_OCRAM_ERR_SIG_EN_SHIFT (5U)
/*! OCRAM_ERR_SIG_EN - OCRAM Access Error Interrupt Enable
 *  0b0..Masked
 *  0b1..Enabled
 */
#define FLEXRAM_INT_SIG_EN_OCRAM_ERR_SIG_EN(x)   (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_SIG_EN_OCRAM_ERR_SIG_EN_SHIFT)) & FLEXRAM_INT_SIG_EN_OCRAM_ERR_SIG_EN_MASK)

#define FLEXRAM_INT_SIG_EN_OCRAM_ERRM_INT_SIG_EN_MASK (0x40U)
#define FLEXRAM_INT_SIG_EN_OCRAM_ERRM_INT_SIG_EN_SHIFT (6U)
/*! OCRAM_ERRM_INT_SIG_EN - OCRAM Access multi-bit ECC Error Interrupt Signal Enable
 *  0b0..Masked
 *  0b1..Enabled
 */
#define FLEXRAM_INT_SIG_EN_OCRAM_ERRM_INT_SIG_EN(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_SIG_EN_OCRAM_ERRM_INT_SIG_EN_SHIFT)) & FLEXRAM_INT_SIG_EN_OCRAM_ERRM_INT_SIG_EN_MASK)

#define FLEXRAM_INT_SIG_EN_OCRAM_ERRS_INT_SIG_EN_MASK (0x80U)
#define FLEXRAM_INT_SIG_EN_OCRAM_ERRS_INT_SIG_EN_SHIFT (7U)
/*! OCRAM_ERRS_INT_SIG_EN - OCRAM Access single-bit ECC Error Interrupt Signal Enable
 *  0b0..Masked
 *  0b1..Enabled
 */
#define FLEXRAM_INT_SIG_EN_OCRAM_ERRS_INT_SIG_EN(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_SIG_EN_OCRAM_ERRS_INT_SIG_EN_SHIFT)) & FLEXRAM_INT_SIG_EN_OCRAM_ERRS_INT_SIG_EN_MASK)

#define FLEXRAM_INT_SIG_EN_ITCM_ERRM_INT_SIG_EN_MASK (0x100U)
#define FLEXRAM_INT_SIG_EN_ITCM_ERRM_INT_SIG_EN_SHIFT (8U)
/*! ITCM_ERRM_INT_SIG_EN - ITCM Access multi-bit ECC Error Interrupt Signal Enable
 *  0b0..Masked
 *  0b1..Enabled
 */
#define FLEXRAM_INT_SIG_EN_ITCM_ERRM_INT_SIG_EN(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_SIG_EN_ITCM_ERRM_INT_SIG_EN_SHIFT)) & FLEXRAM_INT_SIG_EN_ITCM_ERRM_INT_SIG_EN_MASK)

#define FLEXRAM_INT_SIG_EN_ITCM_ERRS_INT_SIG_EN_MASK (0x200U)
#define FLEXRAM_INT_SIG_EN_ITCM_ERRS_INT_SIG_EN_SHIFT (9U)
/*! ITCM_ERRS_INT_SIG_EN - ITCM Access single-bit ECC Error Interrupt Signal Enable
 *  0b0..Masked
 *  0b1..Enabled
 */
#define FLEXRAM_INT_SIG_EN_ITCM_ERRS_INT_SIG_EN(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_SIG_EN_ITCM_ERRS_INT_SIG_EN_SHIFT)) & FLEXRAM_INT_SIG_EN_ITCM_ERRS_INT_SIG_EN_MASK)

#define FLEXRAM_INT_SIG_EN_D0TCM_ERRM_INT_SIG_EN_MASK (0x400U)
#define FLEXRAM_INT_SIG_EN_D0TCM_ERRM_INT_SIG_EN_SHIFT (10U)
/*! D0TCM_ERRM_INT_SIG_EN - D0TCM Access multi-bit ECC Error Interrupt Signal Enable
 *  0b0..Masked
 *  0b1..Enabled
 */
#define FLEXRAM_INT_SIG_EN_D0TCM_ERRM_INT_SIG_EN(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_SIG_EN_D0TCM_ERRM_INT_SIG_EN_SHIFT)) & FLEXRAM_INT_SIG_EN_D0TCM_ERRM_INT_SIG_EN_MASK)

#define FLEXRAM_INT_SIG_EN_D0TCM_ERRS_INT_SIG_EN_MASK (0x800U)
#define FLEXRAM_INT_SIG_EN_D0TCM_ERRS_INT_SIG_EN_SHIFT (11U)
/*! D0TCM_ERRS_INT_SIG_EN - D0TCM Access single-bit ECC Error Interrupt Signal Enable
 *  0b0..Masked
 *  0b1..Enabled
 */
#define FLEXRAM_INT_SIG_EN_D0TCM_ERRS_INT_SIG_EN(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_SIG_EN_D0TCM_ERRS_INT_SIG_EN_SHIFT)) & FLEXRAM_INT_SIG_EN_D0TCM_ERRS_INT_SIG_EN_MASK)

#define FLEXRAM_INT_SIG_EN_D1TCM_ERRM_INT_SIG_EN_MASK (0x1000U)
#define FLEXRAM_INT_SIG_EN_D1TCM_ERRM_INT_SIG_EN_SHIFT (12U)
/*! D1TCM_ERRM_INT_SIG_EN - D1TCM Access multi-bit ECC Error Interrupt Signal Enable
 *  0b0..Masked
 *  0b1..Enabled
 */
#define FLEXRAM_INT_SIG_EN_D1TCM_ERRM_INT_SIG_EN(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_SIG_EN_D1TCM_ERRM_INT_SIG_EN_SHIFT)) & FLEXRAM_INT_SIG_EN_D1TCM_ERRM_INT_SIG_EN_MASK)

#define FLEXRAM_INT_SIG_EN_D1TCM_ERRS_INT_SIG_EN_MASK (0x2000U)
#define FLEXRAM_INT_SIG_EN_D1TCM_ERRS_INT_SIG_EN_SHIFT (13U)
/*! D1TCM_ERRS_INT_SIG_EN - D1TCM Access single-bit ECC Error Interrupt Signal Enable
 *  0b0..Masked
 *  0b1..Enabled
 */
#define FLEXRAM_INT_SIG_EN_D1TCM_ERRS_INT_SIG_EN(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_SIG_EN_D1TCM_ERRS_INT_SIG_EN_SHIFT)) & FLEXRAM_INT_SIG_EN_D1TCM_ERRS_INT_SIG_EN_MASK)

#define FLEXRAM_INT_SIG_EN_OCRAM_PARTIAL_WR_INT_SIG_EN_MASK (0x20000U)
#define FLEXRAM_INT_SIG_EN_OCRAM_PARTIAL_WR_INT_SIG_EN_SHIFT (17U)
/*! OCRAM_PARTIAL_WR_INT_SIG_EN - OCRAM Partial Write Interrupt Signal Enable
 *  0b0..Masked
 *  0b1..Enabled
 */
#define FLEXRAM_INT_SIG_EN_OCRAM_PARTIAL_WR_INT_SIG_EN(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_SIG_EN_OCRAM_PARTIAL_WR_INT_SIG_EN_SHIFT)) & FLEXRAM_INT_SIG_EN_OCRAM_PARTIAL_WR_INT_SIG_EN_MASK)

#define FLEXRAM_INT_SIG_EN_Reserved_MASK         (0xFFFC0000U)
#define FLEXRAM_INT_SIG_EN_Reserved_SHIFT        (18U)
/*! Reserved - Reserved */
#define FLEXRAM_INT_SIG_EN_Reserved(x)           (((uint32_t)(((uint32_t)(x)) << FLEXRAM_INT_SIG_EN_Reserved_SHIFT)) & FLEXRAM_INT_SIG_EN_Reserved_MASK)
/*! @} */

/*! @name OCRAM_ECC_SINGLE_ERROR_INFO - OCRAM single-bit ECC Error Information Register */
/*! @{ */

#define FLEXRAM_OCRAM_ECC_SINGLE_ERROR_INFO_OCRAM_ECCS_ERRED_ECC_MASK (0xFFU)
#define FLEXRAM_OCRAM_ECC_SINGLE_ERROR_INFO_OCRAM_ECCS_ERRED_ECC_SHIFT (0U)
/*! OCRAM_ECCS_ERRED_ECC - corresponding ECC cipher of OCRAM single-bit ECC error */
#define FLEXRAM_OCRAM_ECC_SINGLE_ERROR_INFO_OCRAM_ECCS_ERRED_ECC(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_OCRAM_ECC_SINGLE_ERROR_INFO_OCRAM_ECCS_ERRED_ECC_SHIFT)) & FLEXRAM_OCRAM_ECC_SINGLE_ERROR_INFO_OCRAM_ECCS_ERRED_ECC_MASK)

#define FLEXRAM_OCRAM_ECC_SINGLE_ERROR_INFO_OCRAM_ECCS_ERRED_SYN_MASK (0xFF00U)
#define FLEXRAM_OCRAM_ECC_SINGLE_ERROR_INFO_OCRAM_ECCS_ERRED_SYN_SHIFT (8U)
/*! OCRAM_ECCS_ERRED_SYN - corresponding ECC syndrome of OCRAM single-bit ECC error */
#define FLEXRAM_OCRAM_ECC_SINGLE_ERROR_INFO_OCRAM_ECCS_ERRED_SYN(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_OCRAM_ECC_SINGLE_ERROR_INFO_OCRAM_ECCS_ERRED_SYN_SHIFT)) & FLEXRAM_OCRAM_ECC_SINGLE_ERROR_INFO_OCRAM_ECCS_ERRED_SYN_MASK)

#define FLEXRAM_OCRAM_ECC_SINGLE_ERROR_INFO_Reserved_MASK (0xFFFF0000U)
#define FLEXRAM_OCRAM_ECC_SINGLE_ERROR_INFO_Reserved_SHIFT (16U)
/*! Reserved - Reserved */
#define FLEXRAM_OCRAM_ECC_SINGLE_ERROR_INFO_Reserved(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_OCRAM_ECC_SINGLE_ERROR_INFO_Reserved_SHIFT)) & FLEXRAM_OCRAM_ECC_SINGLE_ERROR_INFO_Reserved_MASK)
/*! @} */

/*! @name OCRAM_ECC_SINGLE_ERROR_ADDR - OCRAM single-bit ECC Error Address Register */
/*! @{ */

#define FLEXRAM_OCRAM_ECC_SINGLE_ERROR_ADDR_OCRAM_ECCS_ERRED_ADDR_MASK (0xFFFFFFFFU)
#define FLEXRAM_OCRAM_ECC_SINGLE_ERROR_ADDR_OCRAM_ECCS_ERRED_ADDR_SHIFT (0U)
/*! OCRAM_ECCS_ERRED_ADDR - OCRAM single-bit ECC error address */
#define FLEXRAM_OCRAM_ECC_SINGLE_ERROR_ADDR_OCRAM_ECCS_ERRED_ADDR(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_OCRAM_ECC_SINGLE_ERROR_ADDR_OCRAM_ECCS_ERRED_ADDR_SHIFT)) & FLEXRAM_OCRAM_ECC_SINGLE_ERROR_ADDR_OCRAM_ECCS_ERRED_ADDR_MASK)
/*! @} */

/*! @name OCRAM_ECC_SINGLE_ERROR_DATA_LSB - OCRAM single-bit ECC Error Data Register */
/*! @{ */

#define FLEXRAM_OCRAM_ECC_SINGLE_ERROR_DATA_LSB_OCRAM_ECCS_ERRED_DATA_LSB_MASK (0xFFFFFFFFU)
#define FLEXRAM_OCRAM_ECC_SINGLE_ERROR_DATA_LSB_OCRAM_ECCS_ERRED_DATA_LSB_SHIFT (0U)
/*! OCRAM_ECCS_ERRED_DATA_LSB - OCRAM single-bit ECC error data [31:0] */
#define FLEXRAM_OCRAM_ECC_SINGLE_ERROR_DATA_LSB_OCRAM_ECCS_ERRED_DATA_LSB(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_OCRAM_ECC_SINGLE_ERROR_DATA_LSB_OCRAM_ECCS_ERRED_DATA_LSB_SHIFT)) & FLEXRAM_OCRAM_ECC_SINGLE_ERROR_DATA_LSB_OCRAM_ECCS_ERRED_DATA_LSB_MASK)
/*! @} */

/*! @name OCRAM_ECC_SINGLE_ERROR_DATA_MSB - OCRAM single-bit ECC Error Data Register */
/*! @{ */

#define FLEXRAM_OCRAM_ECC_SINGLE_ERROR_DATA_MSB_OCRAM_ECCS_ERRED_DATA_MSB_MASK (0xFFFFFFFFU)
#define FLEXRAM_OCRAM_ECC_SINGLE_ERROR_DATA_MSB_OCRAM_ECCS_ERRED_DATA_MSB_SHIFT (0U)
/*! OCRAM_ECCS_ERRED_DATA_MSB - OCRAM single-bit ECC error data [63:32] */
#define FLEXRAM_OCRAM_ECC_SINGLE_ERROR_DATA_MSB_OCRAM_ECCS_ERRED_DATA_MSB(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_OCRAM_ECC_SINGLE_ERROR_DATA_MSB_OCRAM_ECCS_ERRED_DATA_MSB_SHIFT)) & FLEXRAM_OCRAM_ECC_SINGLE_ERROR_DATA_MSB_OCRAM_ECCS_ERRED_DATA_MSB_MASK)
/*! @} */

/*! @name OCRAM_ECC_MULTI_ERROR_INFO - OCRAM multi-bit ECC Error Information Register */
/*! @{ */

#define FLEXRAM_OCRAM_ECC_MULTI_ERROR_INFO_OCRAM_ECCM_ERRED_ECC_MASK (0xFFU)
#define FLEXRAM_OCRAM_ECC_MULTI_ERROR_INFO_OCRAM_ECCM_ERRED_ECC_SHIFT (0U)
/*! OCRAM_ECCM_ERRED_ECC - OCRAM multi-bit ECC error corresponding ECC value */
#define FLEXRAM_OCRAM_ECC_MULTI_ERROR_INFO_OCRAM_ECCM_ERRED_ECC(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_OCRAM_ECC_MULTI_ERROR_INFO_OCRAM_ECCM_ERRED_ECC_SHIFT)) & FLEXRAM_OCRAM_ECC_MULTI_ERROR_INFO_OCRAM_ECCM_ERRED_ECC_MASK)

#define FLEXRAM_OCRAM_ECC_MULTI_ERROR_INFO_Reserved_MASK (0xFFFFFF00U)
#define FLEXRAM_OCRAM_ECC_MULTI_ERROR_INFO_Reserved_SHIFT (8U)
/*! Reserved - Reserved */
#define FLEXRAM_OCRAM_ECC_MULTI_ERROR_INFO_Reserved(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_OCRAM_ECC_MULTI_ERROR_INFO_Reserved_SHIFT)) & FLEXRAM_OCRAM_ECC_MULTI_ERROR_INFO_Reserved_MASK)
/*! @} */

/*! @name OCRAM_ECC_MULTI_ERROR_ADDR - OCRAM multi-bit ECC Error Address Register */
/*! @{ */

#define FLEXRAM_OCRAM_ECC_MULTI_ERROR_ADDR_OCRAM_ECCM_ERRED_ADDR_MASK (0xFFFFFFFFU)
#define FLEXRAM_OCRAM_ECC_MULTI_ERROR_ADDR_OCRAM_ECCM_ERRED_ADDR_SHIFT (0U)
/*! OCRAM_ECCM_ERRED_ADDR - OCRAM multi-bit ECC error address */
#define FLEXRAM_OCRAM_ECC_MULTI_ERROR_ADDR_OCRAM_ECCM_ERRED_ADDR(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_OCRAM_ECC_MULTI_ERROR_ADDR_OCRAM_ECCM_ERRED_ADDR_SHIFT)) & FLEXRAM_OCRAM_ECC_MULTI_ERROR_ADDR_OCRAM_ECCM_ERRED_ADDR_MASK)
/*! @} */

/*! @name OCRAM_ECC_MULTI_ERROR_DATA_LSB - OCRAM multi-bit ECC Error Data Register */
/*! @{ */

#define FLEXRAM_OCRAM_ECC_MULTI_ERROR_DATA_LSB_OCRAM_ECCM_ERRED_DATA_LSB_MASK (0xFFFFFFFFU)
#define FLEXRAM_OCRAM_ECC_MULTI_ERROR_DATA_LSB_OCRAM_ECCM_ERRED_DATA_LSB_SHIFT (0U)
/*! OCRAM_ECCM_ERRED_DATA_LSB - OCRAM multi-bit ECC error data [31:0] */
#define FLEXRAM_OCRAM_ECC_MULTI_ERROR_DATA_LSB_OCRAM_ECCM_ERRED_DATA_LSB(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_OCRAM_ECC_MULTI_ERROR_DATA_LSB_OCRAM_ECCM_ERRED_DATA_LSB_SHIFT)) & FLEXRAM_OCRAM_ECC_MULTI_ERROR_DATA_LSB_OCRAM_ECCM_ERRED_DATA_LSB_MASK)
/*! @} */

/*! @name OCRAM_ECC_MULTI_ERROR_DATA_MSB - OCRAM multi-bit ECC Error Data Register */
/*! @{ */

#define FLEXRAM_OCRAM_ECC_MULTI_ERROR_DATA_MSB_OCRAM_ECCM_ERRED_DATA_MSB_MASK (0xFFFFFFFFU)
#define FLEXRAM_OCRAM_ECC_MULTI_ERROR_DATA_MSB_OCRAM_ECCM_ERRED_DATA_MSB_SHIFT (0U)
/*! OCRAM_ECCM_ERRED_DATA_MSB - OCRAM multi-bit ECC error data [63:32] */
#define FLEXRAM_OCRAM_ECC_MULTI_ERROR_DATA_MSB_OCRAM_ECCM_ERRED_DATA_MSB(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_OCRAM_ECC_MULTI_ERROR_DATA_MSB_OCRAM_ECCM_ERRED_DATA_MSB_SHIFT)) & FLEXRAM_OCRAM_ECC_MULTI_ERROR_DATA_MSB_OCRAM_ECCM_ERRED_DATA_MSB_MASK)
/*! @} */

/*! @name ITCM_ECC_SINGLE_ERROR_INFO - ITCM single-bit ECC Error Information Register */
/*! @{ */

#define FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_ITCM_ECCS_EFW_MASK (0x1U)
#define FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_ITCM_ECCS_EFW_SHIFT (0U)
/*! ITCM_ECCS_EFW - ITCM single-bit ECC error corresponding TCM_WR value. */
#define FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_ITCM_ECCS_EFW(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_ITCM_ECCS_EFW_SHIFT)) & FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_ITCM_ECCS_EFW_MASK)

#define FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_ITCM_ECCS_EFSIZ_MASK (0xEU)
#define FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_ITCM_ECCS_EFSIZ_SHIFT (1U)
/*! ITCM_ECCS_EFSIZ - ITCM single-bit ECC error corresponding TCM size */
#define FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_ITCM_ECCS_EFSIZ(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_ITCM_ECCS_EFSIZ_SHIFT)) & FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_ITCM_ECCS_EFSIZ_MASK)

#define FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_ITCM_ECCS_EFMST_MASK (0xF0U)
#define FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_ITCM_ECCS_EFMST_SHIFT (4U)
/*! ITCM_ECCS_EFMST - ITCM single-bit ECC error corresponding TCM_MASTER. */
#define FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_ITCM_ECCS_EFMST(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_ITCM_ECCS_EFMST_SHIFT)) & FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_ITCM_ECCS_EFMST_MASK)

#define FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_ITCM_ECCS_EFPRT_MASK (0xF00U)
#define FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_ITCM_ECCS_EFPRT_SHIFT (8U)
/*! ITCM_ECCS_EFPRT - ITCM single-bit ECC error corresponding TCM_PRIV. */
#define FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_ITCM_ECCS_EFPRT(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_ITCM_ECCS_EFPRT_SHIFT)) & FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_ITCM_ECCS_EFPRT_MASK)

#define FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_ITCM_ECCS_EFSYN_MASK (0xFF000U)
#define FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_ITCM_ECCS_EFSYN_SHIFT (12U)
/*! ITCM_ECCS_EFSYN - ITCM single-bit ECC error corresponding syndrome */
#define FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_ITCM_ECCS_EFSYN(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_ITCM_ECCS_EFSYN_SHIFT)) & FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_ITCM_ECCS_EFSYN_MASK)

#define FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_Reserved_MASK (0xFFF00000U)
#define FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_Reserved_SHIFT (20U)
/*! Reserved - Reserved */
#define FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_Reserved(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_Reserved_SHIFT)) & FLEXRAM_ITCM_ECC_SINGLE_ERROR_INFO_Reserved_MASK)
/*! @} */

/*! @name ITCM_ECC_SINGLE_ERROR_ADDR - ITCM single-bit ECC Error Address Register */
/*! @{ */

#define FLEXRAM_ITCM_ECC_SINGLE_ERROR_ADDR_ITCM_ECCS_ERRED_ADDR_MASK (0xFFFFFFFFU)
#define FLEXRAM_ITCM_ECC_SINGLE_ERROR_ADDR_ITCM_ECCS_ERRED_ADDR_SHIFT (0U)
/*! ITCM_ECCS_ERRED_ADDR - ITCM single-bit ECC error address */
#define FLEXRAM_ITCM_ECC_SINGLE_ERROR_ADDR_ITCM_ECCS_ERRED_ADDR(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_ITCM_ECC_SINGLE_ERROR_ADDR_ITCM_ECCS_ERRED_ADDR_SHIFT)) & FLEXRAM_ITCM_ECC_SINGLE_ERROR_ADDR_ITCM_ECCS_ERRED_ADDR_MASK)
/*! @} */

/*! @name ITCM_ECC_SINGLE_ERROR_DATA_LSB - ITCM single-bit ECC Error Data Register */
/*! @{ */

#define FLEXRAM_ITCM_ECC_SINGLE_ERROR_DATA_LSB_ITCM_ECCS_ERRED_DATA_LSB_MASK (0xFFFFFFFFU)
#define FLEXRAM_ITCM_ECC_SINGLE_ERROR_DATA_LSB_ITCM_ECCS_ERRED_DATA_LSB_SHIFT (0U)
/*! ITCM_ECCS_ERRED_DATA_LSB - ITCM single-bit ECC error data [31:0] */
#define FLEXRAM_ITCM_ECC_SINGLE_ERROR_DATA_LSB_ITCM_ECCS_ERRED_DATA_LSB(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_ITCM_ECC_SINGLE_ERROR_DATA_LSB_ITCM_ECCS_ERRED_DATA_LSB_SHIFT)) & FLEXRAM_ITCM_ECC_SINGLE_ERROR_DATA_LSB_ITCM_ECCS_ERRED_DATA_LSB_MASK)
/*! @} */

/*! @name ITCM_ECC_SINGLE_ERROR_DATA_MSB - ITCM single-bit ECC Error Data Register */
/*! @{ */

#define FLEXRAM_ITCM_ECC_SINGLE_ERROR_DATA_MSB_ITCM_ECCS_ERRED_DATA_MSB_MASK (0xFFFFFFFFU)
#define FLEXRAM_ITCM_ECC_SINGLE_ERROR_DATA_MSB_ITCM_ECCS_ERRED_DATA_MSB_SHIFT (0U)
/*! ITCM_ECCS_ERRED_DATA_MSB - ITCM single-bit ECC error data [63:32] */
#define FLEXRAM_ITCM_ECC_SINGLE_ERROR_DATA_MSB_ITCM_ECCS_ERRED_DATA_MSB(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_ITCM_ECC_SINGLE_ERROR_DATA_MSB_ITCM_ECCS_ERRED_DATA_MSB_SHIFT)) & FLEXRAM_ITCM_ECC_SINGLE_ERROR_DATA_MSB_ITCM_ECCS_ERRED_DATA_MSB_MASK)
/*! @} */

/*! @name ITCM_ECC_MULTI_ERROR_INFO - ITCM multi-bit ECC Error Information Register */
/*! @{ */

#define FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_ITCM_ECCM_EFW_MASK (0x1U)
#define FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_ITCM_ECCM_EFW_SHIFT (0U)
/*! ITCM_ECCM_EFW - ITCM multi-bit ECC error corresponding TCM_WR value */
#define FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_ITCM_ECCM_EFW(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_ITCM_ECCM_EFW_SHIFT)) & FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_ITCM_ECCM_EFW_MASK)

#define FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_ITCM_ECCM_EFSIZ_MASK (0xEU)
#define FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_ITCM_ECCM_EFSIZ_SHIFT (1U)
/*! ITCM_ECCM_EFSIZ - ITCM multi-bit ECC error corresponding tcm access size */
#define FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_ITCM_ECCM_EFSIZ(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_ITCM_ECCM_EFSIZ_SHIFT)) & FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_ITCM_ECCM_EFSIZ_MASK)

#define FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_ITCM_ECCM_EFMST_MASK (0xF0U)
#define FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_ITCM_ECCM_EFMST_SHIFT (4U)
/*! ITCM_ECCM_EFMST - ITCM multi-bit ECC error corresponding TCM_MASTER */
#define FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_ITCM_ECCM_EFMST(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_ITCM_ECCM_EFMST_SHIFT)) & FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_ITCM_ECCM_EFMST_MASK)

#define FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_ITCM_ECCM_EFPRT_MASK (0xF00U)
#define FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_ITCM_ECCM_EFPRT_SHIFT (8U)
/*! ITCM_ECCM_EFPRT - ITCM multi-bit ECC error corresponding TCM_PRIV */
#define FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_ITCM_ECCM_EFPRT(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_ITCM_ECCM_EFPRT_SHIFT)) & FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_ITCM_ECCM_EFPRT_MASK)

#define FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_ITCM_ECCM_EFSYN_MASK (0xFF000U)
#define FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_ITCM_ECCM_EFSYN_SHIFT (12U)
/*! ITCM_ECCM_EFSYN - ITCM multi-bit ECC error corresponding syndrome */
#define FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_ITCM_ECCM_EFSYN(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_ITCM_ECCM_EFSYN_SHIFT)) & FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_ITCM_ECCM_EFSYN_MASK)

#define FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_Reserved_MASK (0xFFF00000U)
#define FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_Reserved_SHIFT (20U)
/*! Reserved - Reserved */
#define FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_Reserved(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_Reserved_SHIFT)) & FLEXRAM_ITCM_ECC_MULTI_ERROR_INFO_Reserved_MASK)
/*! @} */

/*! @name ITCM_ECC_MULTI_ERROR_ADDR - ITCM multi-bit ECC Error Address Register */
/*! @{ */

#define FLEXRAM_ITCM_ECC_MULTI_ERROR_ADDR_ITCM_ECCM_ERRED_ADDR_MASK (0xFFFFFFFFU)
#define FLEXRAM_ITCM_ECC_MULTI_ERROR_ADDR_ITCM_ECCM_ERRED_ADDR_SHIFT (0U)
/*! ITCM_ECCM_ERRED_ADDR - ITCM multi-bit ECC error address */
#define FLEXRAM_ITCM_ECC_MULTI_ERROR_ADDR_ITCM_ECCM_ERRED_ADDR(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_ITCM_ECC_MULTI_ERROR_ADDR_ITCM_ECCM_ERRED_ADDR_SHIFT)) & FLEXRAM_ITCM_ECC_MULTI_ERROR_ADDR_ITCM_ECCM_ERRED_ADDR_MASK)
/*! @} */

/*! @name ITCM_ECC_MULTI_ERROR_DATA_LSB - ITCM multi-bit ECC Error Data Register */
/*! @{ */

#define FLEXRAM_ITCM_ECC_MULTI_ERROR_DATA_LSB_ITCM_ECCM_ERRED_DATA_LSB_MASK (0xFFFFFFFFU)
#define FLEXRAM_ITCM_ECC_MULTI_ERROR_DATA_LSB_ITCM_ECCM_ERRED_DATA_LSB_SHIFT (0U)
/*! ITCM_ECCM_ERRED_DATA_LSB - ITCM multi-bit ECC error data [31:0] */
#define FLEXRAM_ITCM_ECC_MULTI_ERROR_DATA_LSB_ITCM_ECCM_ERRED_DATA_LSB(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_ITCM_ECC_MULTI_ERROR_DATA_LSB_ITCM_ECCM_ERRED_DATA_LSB_SHIFT)) & FLEXRAM_ITCM_ECC_MULTI_ERROR_DATA_LSB_ITCM_ECCM_ERRED_DATA_LSB_MASK)
/*! @} */

/*! @name ITCM_ECC_MULTI_ERROR_DATA_MSB - ITCM multi-bit ECC Error Data Register */
/*! @{ */

#define FLEXRAM_ITCM_ECC_MULTI_ERROR_DATA_MSB_ITCM_ECCM_ERRED_DATA_MSB_MASK (0xFFFFFFFFU)
#define FLEXRAM_ITCM_ECC_MULTI_ERROR_DATA_MSB_ITCM_ECCM_ERRED_DATA_MSB_SHIFT (0U)
/*! ITCM_ECCM_ERRED_DATA_MSB - ITCM multi-bit ECC error data [63:32] */
#define FLEXRAM_ITCM_ECC_MULTI_ERROR_DATA_MSB_ITCM_ECCM_ERRED_DATA_MSB(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_ITCM_ECC_MULTI_ERROR_DATA_MSB_ITCM_ECCM_ERRED_DATA_MSB_SHIFT)) & FLEXRAM_ITCM_ECC_MULTI_ERROR_DATA_MSB_ITCM_ECCM_ERRED_DATA_MSB_MASK)
/*! @} */

/*! @name D0TCM_ECC_SINGLE_ERROR_INFO - D0TCM single-bit ECC Error Information Register */
/*! @{ */

#define FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_D0TCM_ECCS_EFW_MASK (0x1U)
#define FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_D0TCM_ECCS_EFW_SHIFT (0U)
/*! D0TCM_ECCS_EFW - D0TCM single-bit ECC error corresponding TCM_WR value */
#define FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_D0TCM_ECCS_EFW(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_D0TCM_ECCS_EFW_SHIFT)) & FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_D0TCM_ECCS_EFW_MASK)

#define FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_D0TCM_ECCS_EFSIZ_MASK (0xEU)
#define FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_D0TCM_ECCS_EFSIZ_SHIFT (1U)
/*! D0TCM_ECCS_EFSIZ - D0TCM single-bit ECC error corresponding tcm access size */
#define FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_D0TCM_ECCS_EFSIZ(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_D0TCM_ECCS_EFSIZ_SHIFT)) & FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_D0TCM_ECCS_EFSIZ_MASK)

#define FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_D0TCM_ECCS_EFMST_MASK (0xF0U)
#define FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_D0TCM_ECCS_EFMST_SHIFT (4U)
/*! D0TCM_ECCS_EFMST - D0TCM single-bit ECC error corresponding TCM_MASTER */
#define FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_D0TCM_ECCS_EFMST(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_D0TCM_ECCS_EFMST_SHIFT)) & FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_D0TCM_ECCS_EFMST_MASK)

#define FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_D0TCM_ECCS_EFPRT_MASK (0xF00U)
#define FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_D0TCM_ECCS_EFPRT_SHIFT (8U)
/*! D0TCM_ECCS_EFPRT - D0TCM single-bit ECC error corresponding TCM_PRIV */
#define FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_D0TCM_ECCS_EFPRT(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_D0TCM_ECCS_EFPRT_SHIFT)) & FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_D0TCM_ECCS_EFPRT_MASK)

#define FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_D0TCM_ECCS_EFSYN_MASK (0x7F000U)
#define FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_D0TCM_ECCS_EFSYN_SHIFT (12U)
/*! D0TCM_ECCS_EFSYN - D0TCM single-bit ECC error corresponding syndrome */
#define FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_D0TCM_ECCS_EFSYN(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_D0TCM_ECCS_EFSYN_SHIFT)) & FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_D0TCM_ECCS_EFSYN_MASK)

#define FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_Reserved_MASK (0xFFF80000U)
#define FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_Reserved_SHIFT (19U)
/*! Reserved - Reserved */
#define FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_Reserved(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_Reserved_SHIFT)) & FLEXRAM_D0TCM_ECC_SINGLE_ERROR_INFO_Reserved_MASK)
/*! @} */

/*! @name D0TCM_ECC_SINGLE_ERROR_ADDR - D0TCM single-bit ECC Error Address Register */
/*! @{ */

#define FLEXRAM_D0TCM_ECC_SINGLE_ERROR_ADDR_D0TCM_ECCS_ERRED_ADDR_MASK (0xFFFFFFFFU)
#define FLEXRAM_D0TCM_ECC_SINGLE_ERROR_ADDR_D0TCM_ECCS_ERRED_ADDR_SHIFT (0U)
/*! D0TCM_ECCS_ERRED_ADDR - D0TCM single-bit ECC error address */
#define FLEXRAM_D0TCM_ECC_SINGLE_ERROR_ADDR_D0TCM_ECCS_ERRED_ADDR(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D0TCM_ECC_SINGLE_ERROR_ADDR_D0TCM_ECCS_ERRED_ADDR_SHIFT)) & FLEXRAM_D0TCM_ECC_SINGLE_ERROR_ADDR_D0TCM_ECCS_ERRED_ADDR_MASK)
/*! @} */

/*! @name D0TCM_ECC_SINGLE_ERROR_DATA - D0TCM single-bit ECC Error Data Register */
/*! @{ */

#define FLEXRAM_D0TCM_ECC_SINGLE_ERROR_DATA_D0TCM_ECCS_ERRED_DATA_MASK (0xFFFFFFFFU)
#define FLEXRAM_D0TCM_ECC_SINGLE_ERROR_DATA_D0TCM_ECCS_ERRED_DATA_SHIFT (0U)
/*! D0TCM_ECCS_ERRED_DATA - D0TCM single-bit ECC error data */
#define FLEXRAM_D0TCM_ECC_SINGLE_ERROR_DATA_D0TCM_ECCS_ERRED_DATA(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D0TCM_ECC_SINGLE_ERROR_DATA_D0TCM_ECCS_ERRED_DATA_SHIFT)) & FLEXRAM_D0TCM_ECC_SINGLE_ERROR_DATA_D0TCM_ECCS_ERRED_DATA_MASK)
/*! @} */

/*! @name D0TCM_ECC_MULTI_ERROR_INFO - D0TCM multi-bit ECC Error Information Register */
/*! @{ */

#define FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_D0TCM_ECCM_EFW_MASK (0x1U)
#define FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_D0TCM_ECCM_EFW_SHIFT (0U)
/*! D0TCM_ECCM_EFW - D0TCM multi-bit ECC error corresponding TCM_WR value */
#define FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_D0TCM_ECCM_EFW(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_D0TCM_ECCM_EFW_SHIFT)) & FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_D0TCM_ECCM_EFW_MASK)

#define FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_D0TCM_ECCM_EFSIZ_MASK (0xEU)
#define FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_D0TCM_ECCM_EFSIZ_SHIFT (1U)
/*! D0TCM_ECCM_EFSIZ - D0TCM multi-bit ECC error corresponding tcm access size */
#define FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_D0TCM_ECCM_EFSIZ(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_D0TCM_ECCM_EFSIZ_SHIFT)) & FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_D0TCM_ECCM_EFSIZ_MASK)

#define FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_D0TCM_ECCM_EFMST_MASK (0xF0U)
#define FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_D0TCM_ECCM_EFMST_SHIFT (4U)
/*! D0TCM_ECCM_EFMST - D0TCM multi-bit ECC error corresponding TCM_MASTER */
#define FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_D0TCM_ECCM_EFMST(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_D0TCM_ECCM_EFMST_SHIFT)) & FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_D0TCM_ECCM_EFMST_MASK)

#define FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_D0TCM_ECCM_EFPRT_MASK (0xF00U)
#define FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_D0TCM_ECCM_EFPRT_SHIFT (8U)
/*! D0TCM_ECCM_EFPRT - D0TCM multi-bit ECC error corresponding TCM_PRIV */
#define FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_D0TCM_ECCM_EFPRT(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_D0TCM_ECCM_EFPRT_SHIFT)) & FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_D0TCM_ECCM_EFPRT_MASK)

#define FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_D0TCM_ECCM_EFSYN_MASK (0x7F000U)
#define FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_D0TCM_ECCM_EFSYN_SHIFT (12U)
/*! D0TCM_ECCM_EFSYN - D0TCM multi-bit ECC error corresponding syndrome */
#define FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_D0TCM_ECCM_EFSYN(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_D0TCM_ECCM_EFSYN_SHIFT)) & FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_D0TCM_ECCM_EFSYN_MASK)

#define FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_Reserved_MASK (0xFFF80000U)
#define FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_Reserved_SHIFT (19U)
/*! Reserved - Reserved */
#define FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_Reserved(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_Reserved_SHIFT)) & FLEXRAM_D0TCM_ECC_MULTI_ERROR_INFO_Reserved_MASK)
/*! @} */

/*! @name D0TCM_ECC_MULTI_ERROR_ADDR - D0TCM multi-bit ECC Error Address Register */
/*! @{ */

#define FLEXRAM_D0TCM_ECC_MULTI_ERROR_ADDR_D0TCM_ECCM_ERRED_ADDR_MASK (0xFFFFFFFFU)
#define FLEXRAM_D0TCM_ECC_MULTI_ERROR_ADDR_D0TCM_ECCM_ERRED_ADDR_SHIFT (0U)
/*! D0TCM_ECCM_ERRED_ADDR - D0TCM multi-bit ECC error address */
#define FLEXRAM_D0TCM_ECC_MULTI_ERROR_ADDR_D0TCM_ECCM_ERRED_ADDR(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D0TCM_ECC_MULTI_ERROR_ADDR_D0TCM_ECCM_ERRED_ADDR_SHIFT)) & FLEXRAM_D0TCM_ECC_MULTI_ERROR_ADDR_D0TCM_ECCM_ERRED_ADDR_MASK)
/*! @} */

/*! @name D0TCM_ECC_MULTI_ERROR_DATA - D0TCM multi-bit ECC Error Data Register */
/*! @{ */

#define FLEXRAM_D0TCM_ECC_MULTI_ERROR_DATA_D0TCM_ECCM_ERRED_DATA_MASK (0xFFFFFFFFU)
#define FLEXRAM_D0TCM_ECC_MULTI_ERROR_DATA_D0TCM_ECCM_ERRED_DATA_SHIFT (0U)
/*! D0TCM_ECCM_ERRED_DATA - D0TCM multi-bit ECC error data */
#define FLEXRAM_D0TCM_ECC_MULTI_ERROR_DATA_D0TCM_ECCM_ERRED_DATA(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D0TCM_ECC_MULTI_ERROR_DATA_D0TCM_ECCM_ERRED_DATA_SHIFT)) & FLEXRAM_D0TCM_ECC_MULTI_ERROR_DATA_D0TCM_ECCM_ERRED_DATA_MASK)
/*! @} */

/*! @name D1TCM_ECC_SINGLE_ERROR_INFO - D1TCM single-bit ECC Error Information Register */
/*! @{ */

#define FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_D1TCM_ECCS_EFW_MASK (0x1U)
#define FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_D1TCM_ECCS_EFW_SHIFT (0U)
/*! D1TCM_ECCS_EFW - D1TCM single-bit ECC error corresponding TCM_WR value */
#define FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_D1TCM_ECCS_EFW(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_D1TCM_ECCS_EFW_SHIFT)) & FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_D1TCM_ECCS_EFW_MASK)

#define FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_D1TCM_ECCS_EFSIZ_MASK (0xEU)
#define FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_D1TCM_ECCS_EFSIZ_SHIFT (1U)
/*! D1TCM_ECCS_EFSIZ - D1TCM single-bit ECC error corresponding tcm access size */
#define FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_D1TCM_ECCS_EFSIZ(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_D1TCM_ECCS_EFSIZ_SHIFT)) & FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_D1TCM_ECCS_EFSIZ_MASK)

#define FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_D1TCM_ECCS_EFMST_MASK (0xF0U)
#define FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_D1TCM_ECCS_EFMST_SHIFT (4U)
/*! D1TCM_ECCS_EFMST - D1TCM single-bit ECC error corresponding TCM_MASTER */
#define FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_D1TCM_ECCS_EFMST(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_D1TCM_ECCS_EFMST_SHIFT)) & FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_D1TCM_ECCS_EFMST_MASK)

#define FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_D1TCM_ECCS_EFPRT_MASK (0xF00U)
#define FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_D1TCM_ECCS_EFPRT_SHIFT (8U)
/*! D1TCM_ECCS_EFPRT - D1TCM single-bit ECC error corresponding TCM_PRIV */
#define FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_D1TCM_ECCS_EFPRT(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_D1TCM_ECCS_EFPRT_SHIFT)) & FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_D1TCM_ECCS_EFPRT_MASK)

#define FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_D1TCM_ECCS_EFSYN_MASK (0x7F000U)
#define FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_D1TCM_ECCS_EFSYN_SHIFT (12U)
/*! D1TCM_ECCS_EFSYN - D1TCM single-bit ECC error corresponding syndrome */
#define FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_D1TCM_ECCS_EFSYN(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_D1TCM_ECCS_EFSYN_SHIFT)) & FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_D1TCM_ECCS_EFSYN_MASK)

#define FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_Reserved_MASK (0xFFF80000U)
#define FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_Reserved_SHIFT (19U)
/*! Reserved - Reserved */
#define FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_Reserved(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_Reserved_SHIFT)) & FLEXRAM_D1TCM_ECC_SINGLE_ERROR_INFO_Reserved_MASK)
/*! @} */

/*! @name D1TCM_ECC_SINGLE_ERROR_ADDR - D1TCM single-bit ECC Error Address Register */
/*! @{ */

#define FLEXRAM_D1TCM_ECC_SINGLE_ERROR_ADDR_D1TCM_ECCS_ERRED_ADDR_MASK (0xFFFFFFFFU)
#define FLEXRAM_D1TCM_ECC_SINGLE_ERROR_ADDR_D1TCM_ECCS_ERRED_ADDR_SHIFT (0U)
/*! D1TCM_ECCS_ERRED_ADDR - D1TCM single-bit ECC error address */
#define FLEXRAM_D1TCM_ECC_SINGLE_ERROR_ADDR_D1TCM_ECCS_ERRED_ADDR(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D1TCM_ECC_SINGLE_ERROR_ADDR_D1TCM_ECCS_ERRED_ADDR_SHIFT)) & FLEXRAM_D1TCM_ECC_SINGLE_ERROR_ADDR_D1TCM_ECCS_ERRED_ADDR_MASK)
/*! @} */

/*! @name D1TCM_ECC_SINGLE_ERROR_DATA - D1TCM single-bit ECC Error Data Register */
/*! @{ */

#define FLEXRAM_D1TCM_ECC_SINGLE_ERROR_DATA_D1TCM_ECCS_ERRED_DATA_MASK (0xFFFFFFFFU)
#define FLEXRAM_D1TCM_ECC_SINGLE_ERROR_DATA_D1TCM_ECCS_ERRED_DATA_SHIFT (0U)
/*! D1TCM_ECCS_ERRED_DATA - D1TCM single-bit ECC error data */
#define FLEXRAM_D1TCM_ECC_SINGLE_ERROR_DATA_D1TCM_ECCS_ERRED_DATA(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D1TCM_ECC_SINGLE_ERROR_DATA_D1TCM_ECCS_ERRED_DATA_SHIFT)) & FLEXRAM_D1TCM_ECC_SINGLE_ERROR_DATA_D1TCM_ECCS_ERRED_DATA_MASK)
/*! @} */

/*! @name D1TCM_ECC_MULTI_ERROR_INFO - D1TCM multi-bit ECC Error Information Register */
/*! @{ */

#define FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_D1TCM_ECCM_EFW_MASK (0x1U)
#define FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_D1TCM_ECCM_EFW_SHIFT (0U)
/*! D1TCM_ECCM_EFW - D1TCM multi-bit ECC error corresponding TCM_WR value */
#define FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_D1TCM_ECCM_EFW(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_D1TCM_ECCM_EFW_SHIFT)) & FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_D1TCM_ECCM_EFW_MASK)

#define FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_D1TCM_ECCM_EFSIZ_MASK (0xEU)
#define FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_D1TCM_ECCM_EFSIZ_SHIFT (1U)
/*! D1TCM_ECCM_EFSIZ - D1TCM multi-bit ECC error corresponding tcm access size */
#define FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_D1TCM_ECCM_EFSIZ(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_D1TCM_ECCM_EFSIZ_SHIFT)) & FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_D1TCM_ECCM_EFSIZ_MASK)

#define FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_D1TCM_ECCM_EFMST_MASK (0xF0U)
#define FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_D1TCM_ECCM_EFMST_SHIFT (4U)
/*! D1TCM_ECCM_EFMST - D1TCM multi-bit ECC error corresponding TCM_MASTER */
#define FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_D1TCM_ECCM_EFMST(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_D1TCM_ECCM_EFMST_SHIFT)) & FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_D1TCM_ECCM_EFMST_MASK)

#define FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_D1TCM_ECCM_EFPRT_MASK (0xF00U)
#define FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_D1TCM_ECCM_EFPRT_SHIFT (8U)
/*! D1TCM_ECCM_EFPRT - D1TCM multi-bit ECC error corresponding TCM_PRIV */
#define FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_D1TCM_ECCM_EFPRT(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_D1TCM_ECCM_EFPRT_SHIFT)) & FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_D1TCM_ECCM_EFPRT_MASK)

#define FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_D1TCM_ECCM_EFSYN_MASK (0x7F000U)
#define FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_D1TCM_ECCM_EFSYN_SHIFT (12U)
/*! D1TCM_ECCM_EFSYN - D1TCM multi-bit ECC error corresponding syndrome */
#define FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_D1TCM_ECCM_EFSYN(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_D1TCM_ECCM_EFSYN_SHIFT)) & FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_D1TCM_ECCM_EFSYN_MASK)

#define FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_Reserved_MASK (0xFFF80000U)
#define FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_Reserved_SHIFT (19U)
/*! Reserved - Reserved */
#define FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_Reserved(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_Reserved_SHIFT)) & FLEXRAM_D1TCM_ECC_MULTI_ERROR_INFO_Reserved_MASK)
/*! @} */

/*! @name D1TCM_ECC_MULTI_ERROR_ADDR - D1TCM multi-bit ECC Error Address Register */
/*! @{ */

#define FLEXRAM_D1TCM_ECC_MULTI_ERROR_ADDR_D1TCM_ECCM_ERRED_ADDR_MASK (0xFFFFFFFFU)
#define FLEXRAM_D1TCM_ECC_MULTI_ERROR_ADDR_D1TCM_ECCM_ERRED_ADDR_SHIFT (0U)
/*! D1TCM_ECCM_ERRED_ADDR - D1TCM multi-bit ECC error address */
#define FLEXRAM_D1TCM_ECC_MULTI_ERROR_ADDR_D1TCM_ECCM_ERRED_ADDR(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D1TCM_ECC_MULTI_ERROR_ADDR_D1TCM_ECCM_ERRED_ADDR_SHIFT)) & FLEXRAM_D1TCM_ECC_MULTI_ERROR_ADDR_D1TCM_ECCM_ERRED_ADDR_MASK)
/*! @} */

/*! @name D1TCM_ECC_MULTI_ERROR_DATA - D1TCM multi-bit ECC Error Data Register */
/*! @{ */

#define FLEXRAM_D1TCM_ECC_MULTI_ERROR_DATA_D1TCM_ECCM_ERRED_DATA_MASK (0xFFFFFFFFU)
#define FLEXRAM_D1TCM_ECC_MULTI_ERROR_DATA_D1TCM_ECCM_ERRED_DATA_SHIFT (0U)
/*! D1TCM_ECCM_ERRED_DATA - D1TCM multi-bit ECC error data */
#define FLEXRAM_D1TCM_ECC_MULTI_ERROR_DATA_D1TCM_ECCM_ERRED_DATA(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D1TCM_ECC_MULTI_ERROR_DATA_D1TCM_ECCM_ERRED_DATA_SHIFT)) & FLEXRAM_D1TCM_ECC_MULTI_ERROR_DATA_D1TCM_ECCM_ERRED_DATA_MASK)
/*! @} */

/*! @name OCRAM_ECC_ERROR_INJEC - OCRAM ECC Error Injection Register */
/*! @{ */

#define FLEXRAM_OCRAM_ECC_ERROR_INJEC_OCRAM_ERR1BIT_MASK (0xFFU)
#define FLEXRAM_OCRAM_ECC_ERROR_INJEC_OCRAM_ERR1BIT_SHIFT (0U)
/*! OCRAM_ERR1BIT - Bit position of the bit to inject ECC Error. Can be used for single-bit and multi-bit ECC Error injection. */
#define FLEXRAM_OCRAM_ECC_ERROR_INJEC_OCRAM_ERR1BIT(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_OCRAM_ECC_ERROR_INJEC_OCRAM_ERR1BIT_SHIFT)) & FLEXRAM_OCRAM_ECC_ERROR_INJEC_OCRAM_ERR1BIT_MASK)

#define FLEXRAM_OCRAM_ECC_ERROR_INJEC_OCRAM_ERR2BIT_MASK (0xFF00U)
#define FLEXRAM_OCRAM_ECC_ERROR_INJEC_OCRAM_ERR2BIT_SHIFT (8U)
/*! OCRAM_ERR2BIT - Bit position of the second bit to inject multi-bit ECC Error. */
#define FLEXRAM_OCRAM_ECC_ERROR_INJEC_OCRAM_ERR2BIT(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_OCRAM_ECC_ERROR_INJEC_OCRAM_ERR2BIT_SHIFT)) & FLEXRAM_OCRAM_ECC_ERROR_INJEC_OCRAM_ERR2BIT_MASK)

#define FLEXRAM_OCRAM_ECC_ERROR_INJEC_OCRAM_FR11BI_MASK (0x10000U)
#define FLEXRAM_OCRAM_ECC_ERROR_INJEC_OCRAM_FR11BI_SHIFT (16U)
/*! OCRAM_FR11BI - Force One 1-Bit Data Inversion (single-bit ECC error) on OCRAM write access */
#define FLEXRAM_OCRAM_ECC_ERROR_INJEC_OCRAM_FR11BI(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_OCRAM_ECC_ERROR_INJEC_OCRAM_FR11BI_SHIFT)) & FLEXRAM_OCRAM_ECC_ERROR_INJEC_OCRAM_FR11BI_MASK)

#define FLEXRAM_OCRAM_ECC_ERROR_INJEC_OCRAM_FR1NCI_MASK (0x20000U)
#define FLEXRAM_OCRAM_ECC_ERROR_INJEC_OCRAM_FR1NCI_SHIFT (17U)
/*! OCRAM_FR1NCI - Force One Non-correctable Data Inversion(multi-bit ECC error) on OCRAM write access */
#define FLEXRAM_OCRAM_ECC_ERROR_INJEC_OCRAM_FR1NCI(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_OCRAM_ECC_ERROR_INJEC_OCRAM_FR1NCI_SHIFT)) & FLEXRAM_OCRAM_ECC_ERROR_INJEC_OCRAM_FR1NCI_MASK)

#define FLEXRAM_OCRAM_ECC_ERROR_INJEC_OCRAM_FRC1BI_MASK (0x40000U)
#define FLEXRAM_OCRAM_ECC_ERROR_INJEC_OCRAM_FRC1BI_SHIFT (18U)
/*! OCRAM_FRC1BI - Force Continuous 1-Bit Data Inversions (single-bit ECC error) on OCRAM write access */
#define FLEXRAM_OCRAM_ECC_ERROR_INJEC_OCRAM_FRC1BI(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_OCRAM_ECC_ERROR_INJEC_OCRAM_FRC1BI_SHIFT)) & FLEXRAM_OCRAM_ECC_ERROR_INJEC_OCRAM_FRC1BI_MASK)

#define FLEXRAM_OCRAM_ECC_ERROR_INJEC_OCRAM_FRCNCI_MASK (0x80000U)
#define FLEXRAM_OCRAM_ECC_ERROR_INJEC_OCRAM_FRCNCI_SHIFT (19U)
/*! OCRAM_FRCNCI - Force Continuous Non-correctable Data Inversions (multi-bit ECC error) on OCRAM write access */
#define FLEXRAM_OCRAM_ECC_ERROR_INJEC_OCRAM_FRCNCI(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_OCRAM_ECC_ERROR_INJEC_OCRAM_FRCNCI_SHIFT)) & FLEXRAM_OCRAM_ECC_ERROR_INJEC_OCRAM_FRCNCI_MASK)

#define FLEXRAM_OCRAM_ECC_ERROR_INJEC_Reserved_MASK (0xFFF00000U)
#define FLEXRAM_OCRAM_ECC_ERROR_INJEC_Reserved_SHIFT (20U)
/*! Reserved - Reserved */
#define FLEXRAM_OCRAM_ECC_ERROR_INJEC_Reserved(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_OCRAM_ECC_ERROR_INJEC_Reserved_SHIFT)) & FLEXRAM_OCRAM_ECC_ERROR_INJEC_Reserved_MASK)
/*! @} */

/*! @name ITCM_ECC_ERROR_INJEC - ITCM ECC Error Injection Register */
/*! @{ */

#define FLEXRAM_ITCM_ECC_ERROR_INJEC_ITCM_ERR1BIT_MASK (0xFFU)
#define FLEXRAM_ITCM_ECC_ERROR_INJEC_ITCM_ERR1BIT_SHIFT (0U)
/*! ITCM_ERR1BIT - Bit position of the bit to inject ECC Error. Can be used for single-bit and multi-bit ECC Error injection. */
#define FLEXRAM_ITCM_ECC_ERROR_INJEC_ITCM_ERR1BIT(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_ITCM_ECC_ERROR_INJEC_ITCM_ERR1BIT_SHIFT)) & FLEXRAM_ITCM_ECC_ERROR_INJEC_ITCM_ERR1BIT_MASK)

#define FLEXRAM_ITCM_ECC_ERROR_INJEC_ITCM_ERR2BIT_MASK (0xFF00U)
#define FLEXRAM_ITCM_ECC_ERROR_INJEC_ITCM_ERR2BIT_SHIFT (8U)
/*! ITCM_ERR2BIT - Bit position of the second bit to inject multi-bit ECC Error. */
#define FLEXRAM_ITCM_ECC_ERROR_INJEC_ITCM_ERR2BIT(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_ITCM_ECC_ERROR_INJEC_ITCM_ERR2BIT_SHIFT)) & FLEXRAM_ITCM_ECC_ERROR_INJEC_ITCM_ERR2BIT_MASK)

#define FLEXRAM_ITCM_ECC_ERROR_INJEC_ITCM_FR11BI_MASK (0x10000U)
#define FLEXRAM_ITCM_ECC_ERROR_INJEC_ITCM_FR11BI_SHIFT (16U)
/*! ITCM_FR11BI - Force One 1-Bit Data Inversion(single-bit ECC error) on ITCM write access */
#define FLEXRAM_ITCM_ECC_ERROR_INJEC_ITCM_FR11BI(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_ITCM_ECC_ERROR_INJEC_ITCM_FR11BI_SHIFT)) & FLEXRAM_ITCM_ECC_ERROR_INJEC_ITCM_FR11BI_MASK)

#define FLEXRAM_ITCM_ECC_ERROR_INJEC_ITCM_FR1NCI_MASK (0x20000U)
#define FLEXRAM_ITCM_ECC_ERROR_INJEC_ITCM_FR1NCI_SHIFT (17U)
/*! ITCM_FR1NCI - Force One Non-correctable Data Inversion(multi-bit ECC error) on ITCM write access */
#define FLEXRAM_ITCM_ECC_ERROR_INJEC_ITCM_FR1NCI(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_ITCM_ECC_ERROR_INJEC_ITCM_FR1NCI_SHIFT)) & FLEXRAM_ITCM_ECC_ERROR_INJEC_ITCM_FR1NCI_MASK)

#define FLEXRAM_ITCM_ECC_ERROR_INJEC_ITCM_FRC1BI_MASK (0x40000U)
#define FLEXRAM_ITCM_ECC_ERROR_INJEC_ITCM_FRC1BI_SHIFT (18U)
/*! ITCM_FRC1BI - Force Continuous 1-Bit Data Inversions (single-bit ECC error) on ITCM write access */
#define FLEXRAM_ITCM_ECC_ERROR_INJEC_ITCM_FRC1BI(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_ITCM_ECC_ERROR_INJEC_ITCM_FRC1BI_SHIFT)) & FLEXRAM_ITCM_ECC_ERROR_INJEC_ITCM_FRC1BI_MASK)

#define FLEXRAM_ITCM_ECC_ERROR_INJEC_ITCM_FRCNCI_MASK (0x80000U)
#define FLEXRAM_ITCM_ECC_ERROR_INJEC_ITCM_FRCNCI_SHIFT (19U)
/*! ITCM_FRCNCI - Force Continuous Non-correctable Data Inversions (multi-bit ECC error) on ITCM write access */
#define FLEXRAM_ITCM_ECC_ERROR_INJEC_ITCM_FRCNCI(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_ITCM_ECC_ERROR_INJEC_ITCM_FRCNCI_SHIFT)) & FLEXRAM_ITCM_ECC_ERROR_INJEC_ITCM_FRCNCI_MASK)

#define FLEXRAM_ITCM_ECC_ERROR_INJEC_Reserved_MASK (0xFFF00000U)
#define FLEXRAM_ITCM_ECC_ERROR_INJEC_Reserved_SHIFT (20U)
/*! Reserved - Reserved */
#define FLEXRAM_ITCM_ECC_ERROR_INJEC_Reserved(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_ITCM_ECC_ERROR_INJEC_Reserved_SHIFT)) & FLEXRAM_ITCM_ECC_ERROR_INJEC_Reserved_MASK)
/*! @} */

/*! @name D0TCM_ECC_ERROR_INJEC - D0TCM ECC Error Injection Register */
/*! @{ */

#define FLEXRAM_D0TCM_ECC_ERROR_INJEC_D0TCM_ERR1BIT_MASK (0xFFU)
#define FLEXRAM_D0TCM_ECC_ERROR_INJEC_D0TCM_ERR1BIT_SHIFT (0U)
/*! D0TCM_ERR1BIT - Bit position of the bit to inject ECC Error. Can be used for single-bit and multi-bit ECC Error injection. */
#define FLEXRAM_D0TCM_ECC_ERROR_INJEC_D0TCM_ERR1BIT(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D0TCM_ECC_ERROR_INJEC_D0TCM_ERR1BIT_SHIFT)) & FLEXRAM_D0TCM_ECC_ERROR_INJEC_D0TCM_ERR1BIT_MASK)

#define FLEXRAM_D0TCM_ECC_ERROR_INJEC_D0TCM_ERR2BIT_MASK (0xFF00U)
#define FLEXRAM_D0TCM_ECC_ERROR_INJEC_D0TCM_ERR2BIT_SHIFT (8U)
/*! D0TCM_ERR2BIT - Bit position of the second bit to inject multi-bit ECC Error */
#define FLEXRAM_D0TCM_ECC_ERROR_INJEC_D0TCM_ERR2BIT(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D0TCM_ECC_ERROR_INJEC_D0TCM_ERR2BIT_SHIFT)) & FLEXRAM_D0TCM_ECC_ERROR_INJEC_D0TCM_ERR2BIT_MASK)

#define FLEXRAM_D0TCM_ECC_ERROR_INJEC_D0TCM_FR11BI_MASK (0x10000U)
#define FLEXRAM_D0TCM_ECC_ERROR_INJEC_D0TCM_FR11BI_SHIFT (16U)
/*! D0TCM_FR11BI - Force One 1-Bit Data Inversion(single-bit ECC error) on D0TCM write access */
#define FLEXRAM_D0TCM_ECC_ERROR_INJEC_D0TCM_FR11BI(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D0TCM_ECC_ERROR_INJEC_D0TCM_FR11BI_SHIFT)) & FLEXRAM_D0TCM_ECC_ERROR_INJEC_D0TCM_FR11BI_MASK)

#define FLEXRAM_D0TCM_ECC_ERROR_INJEC_D0TCM_FR1NCI_MASK (0x20000U)
#define FLEXRAM_D0TCM_ECC_ERROR_INJEC_D0TCM_FR1NCI_SHIFT (17U)
/*! D0TCM_FR1NCI - Force One Non-correctable Data Inversion(multi-bit ECC error) on D0TCM write access */
#define FLEXRAM_D0TCM_ECC_ERROR_INJEC_D0TCM_FR1NCI(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D0TCM_ECC_ERROR_INJEC_D0TCM_FR1NCI_SHIFT)) & FLEXRAM_D0TCM_ECC_ERROR_INJEC_D0TCM_FR1NCI_MASK)

#define FLEXRAM_D0TCM_ECC_ERROR_INJEC_D0TCM_FRC1BI_MASK (0x40000U)
#define FLEXRAM_D0TCM_ECC_ERROR_INJEC_D0TCM_FRC1BI_SHIFT (18U)
/*! D0TCM_FRC1BI - Force Continuous 1-Bit Data Inversions (single-bit ECC error) on D0TCM write access */
#define FLEXRAM_D0TCM_ECC_ERROR_INJEC_D0TCM_FRC1BI(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D0TCM_ECC_ERROR_INJEC_D0TCM_FRC1BI_SHIFT)) & FLEXRAM_D0TCM_ECC_ERROR_INJEC_D0TCM_FRC1BI_MASK)

#define FLEXRAM_D0TCM_ECC_ERROR_INJEC_D0TCM_FRCNCI_MASK (0x80000U)
#define FLEXRAM_D0TCM_ECC_ERROR_INJEC_D0TCM_FRCNCI_SHIFT (19U)
/*! D0TCM_FRCNCI - Force Continuous Non-correctable Data Inversions (multi-bit ECC error) on D0TCM write access */
#define FLEXRAM_D0TCM_ECC_ERROR_INJEC_D0TCM_FRCNCI(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D0TCM_ECC_ERROR_INJEC_D0TCM_FRCNCI_SHIFT)) & FLEXRAM_D0TCM_ECC_ERROR_INJEC_D0TCM_FRCNCI_MASK)

#define FLEXRAM_D0TCM_ECC_ERROR_INJEC_Reserved_MASK (0xFFF00000U)
#define FLEXRAM_D0TCM_ECC_ERROR_INJEC_Reserved_SHIFT (20U)
/*! Reserved - Reserved */
#define FLEXRAM_D0TCM_ECC_ERROR_INJEC_Reserved(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D0TCM_ECC_ERROR_INJEC_Reserved_SHIFT)) & FLEXRAM_D0TCM_ECC_ERROR_INJEC_Reserved_MASK)
/*! @} */

/*! @name D1TCM_ECC_ERROR_INJEC - D1TCM ECC Error Injection Register */
/*! @{ */

#define FLEXRAM_D1TCM_ECC_ERROR_INJEC_D1TCM_ERR1BIT_MASK (0xFFU)
#define FLEXRAM_D1TCM_ECC_ERROR_INJEC_D1TCM_ERR1BIT_SHIFT (0U)
/*! D1TCM_ERR1BIT - Bit position of the bit to inject ECC Error. Can be used for single-bit and multi-bit ECC Error injection */
#define FLEXRAM_D1TCM_ECC_ERROR_INJEC_D1TCM_ERR1BIT(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D1TCM_ECC_ERROR_INJEC_D1TCM_ERR1BIT_SHIFT)) & FLEXRAM_D1TCM_ECC_ERROR_INJEC_D1TCM_ERR1BIT_MASK)

#define FLEXRAM_D1TCM_ECC_ERROR_INJEC_D1TCM_ERR2BIT_MASK (0xFF00U)
#define FLEXRAM_D1TCM_ECC_ERROR_INJEC_D1TCM_ERR2BIT_SHIFT (8U)
/*! D1TCM_ERR2BIT - Bit position of the second bit to inject multi-bit ECC Error */
#define FLEXRAM_D1TCM_ECC_ERROR_INJEC_D1TCM_ERR2BIT(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D1TCM_ECC_ERROR_INJEC_D1TCM_ERR2BIT_SHIFT)) & FLEXRAM_D1TCM_ECC_ERROR_INJEC_D1TCM_ERR2BIT_MASK)

#define FLEXRAM_D1TCM_ECC_ERROR_INJEC_D1TCM_FR11BI_MASK (0x10000U)
#define FLEXRAM_D1TCM_ECC_ERROR_INJEC_D1TCM_FR11BI_SHIFT (16U)
/*! D1TCM_FR11BI - Force One 1-Bit Data Inversion(single-bit ECC error) on D1TCM write access */
#define FLEXRAM_D1TCM_ECC_ERROR_INJEC_D1TCM_FR11BI(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D1TCM_ECC_ERROR_INJEC_D1TCM_FR11BI_SHIFT)) & FLEXRAM_D1TCM_ECC_ERROR_INJEC_D1TCM_FR11BI_MASK)

#define FLEXRAM_D1TCM_ECC_ERROR_INJEC_D1TCM_FR1NCI_MASK (0x20000U)
#define FLEXRAM_D1TCM_ECC_ERROR_INJEC_D1TCM_FR1NCI_SHIFT (17U)
/*! D1TCM_FR1NCI - Force One Non-correctable Data Inversion(multi-bit ECC error) on D1TCM write access */
#define FLEXRAM_D1TCM_ECC_ERROR_INJEC_D1TCM_FR1NCI(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D1TCM_ECC_ERROR_INJEC_D1TCM_FR1NCI_SHIFT)) & FLEXRAM_D1TCM_ECC_ERROR_INJEC_D1TCM_FR1NCI_MASK)

#define FLEXRAM_D1TCM_ECC_ERROR_INJEC_D1TCM_FRC1BI_MASK (0x40000U)
#define FLEXRAM_D1TCM_ECC_ERROR_INJEC_D1TCM_FRC1BI_SHIFT (18U)
/*! D1TCM_FRC1BI - Force Continuous 1-Bit Data Inversions (single-bit ECC error) on D1TCM write access */
#define FLEXRAM_D1TCM_ECC_ERROR_INJEC_D1TCM_FRC1BI(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D1TCM_ECC_ERROR_INJEC_D1TCM_FRC1BI_SHIFT)) & FLEXRAM_D1TCM_ECC_ERROR_INJEC_D1TCM_FRC1BI_MASK)

#define FLEXRAM_D1TCM_ECC_ERROR_INJEC_D1TCM_FRCNCI_MASK (0x80000U)
#define FLEXRAM_D1TCM_ECC_ERROR_INJEC_D1TCM_FRCNCI_SHIFT (19U)
/*! D1TCM_FRCNCI - Force Continuous Non-correctable Data Inversions (multi-bit ECC error) on D1TCM write access */
#define FLEXRAM_D1TCM_ECC_ERROR_INJEC_D1TCM_FRCNCI(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D1TCM_ECC_ERROR_INJEC_D1TCM_FRCNCI_SHIFT)) & FLEXRAM_D1TCM_ECC_ERROR_INJEC_D1TCM_FRCNCI_MASK)

#define FLEXRAM_D1TCM_ECC_ERROR_INJEC_Reserved_MASK (0xFFF00000U)
#define FLEXRAM_D1TCM_ECC_ERROR_INJEC_Reserved_SHIFT (20U)
/*! Reserved - Reserved */
#define FLEXRAM_D1TCM_ECC_ERROR_INJEC_Reserved(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_D1TCM_ECC_ERROR_INJEC_Reserved_SHIFT)) & FLEXRAM_D1TCM_ECC_ERROR_INJEC_Reserved_MASK)
/*! @} */

/*! @name FLEXRAM_CTRL - FlexRAM feature Control register */
/*! @{ */

#define FLEXRAM_FLEXRAM_CTRL_OCRAM_RDATA_WAIT_EN_MASK (0x1U)
#define FLEXRAM_FLEXRAM_CTRL_OCRAM_RDATA_WAIT_EN_SHIFT (0U)
/*! OCRAM_RDATA_WAIT_EN - Read Data Wait Enable */
#define FLEXRAM_FLEXRAM_CTRL_OCRAM_RDATA_WAIT_EN(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_FLEXRAM_CTRL_OCRAM_RDATA_WAIT_EN_SHIFT)) & FLEXRAM_FLEXRAM_CTRL_OCRAM_RDATA_WAIT_EN_MASK)

#define FLEXRAM_FLEXRAM_CTRL_OCRAM_RADDR_PIPELINE_EN_MASK (0x2U)
#define FLEXRAM_FLEXRAM_CTRL_OCRAM_RADDR_PIPELINE_EN_SHIFT (1U)
/*! OCRAM_RADDR_PIPELINE_EN - Read Address Pipeline Enable */
#define FLEXRAM_FLEXRAM_CTRL_OCRAM_RADDR_PIPELINE_EN(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_FLEXRAM_CTRL_OCRAM_RADDR_PIPELINE_EN_SHIFT)) & FLEXRAM_FLEXRAM_CTRL_OCRAM_RADDR_PIPELINE_EN_MASK)

#define FLEXRAM_FLEXRAM_CTRL_OCRAM_WRDATA_PIPELINE_EN_MASK (0x4U)
#define FLEXRAM_FLEXRAM_CTRL_OCRAM_WRDATA_PIPELINE_EN_SHIFT (2U)
/*! OCRAM_WRDATA_PIPELINE_EN - Write Data Pipeline Enable */
#define FLEXRAM_FLEXRAM_CTRL_OCRAM_WRDATA_PIPELINE_EN(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_FLEXRAM_CTRL_OCRAM_WRDATA_PIPELINE_EN_SHIFT)) & FLEXRAM_FLEXRAM_CTRL_OCRAM_WRDATA_PIPELINE_EN_MASK)

#define FLEXRAM_FLEXRAM_CTRL_OCRAM_WRADDR_PIPELINE_EN_MASK (0x8U)
#define FLEXRAM_FLEXRAM_CTRL_OCRAM_WRADDR_PIPELINE_EN_SHIFT (3U)
/*! OCRAM_WRADDR_PIPELINE_EN - Write Address Pipeline Enable */
#define FLEXRAM_FLEXRAM_CTRL_OCRAM_WRADDR_PIPELINE_EN(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_FLEXRAM_CTRL_OCRAM_WRADDR_PIPELINE_EN_SHIFT)) & FLEXRAM_FLEXRAM_CTRL_OCRAM_WRADDR_PIPELINE_EN_MASK)

#define FLEXRAM_FLEXRAM_CTRL_OCRAM_ECC_EN_MASK   (0x10U)
#define FLEXRAM_FLEXRAM_CTRL_OCRAM_ECC_EN_SHIFT  (4U)
/*! OCRAM_ECC_EN - OCRAM ECC enable */
#define FLEXRAM_FLEXRAM_CTRL_OCRAM_ECC_EN(x)     (((uint32_t)(((uint32_t)(x)) << FLEXRAM_FLEXRAM_CTRL_OCRAM_ECC_EN_SHIFT)) & FLEXRAM_FLEXRAM_CTRL_OCRAM_ECC_EN_MASK)

#define FLEXRAM_FLEXRAM_CTRL_TCM_ECC_EN_MASK     (0x20U)
#define FLEXRAM_FLEXRAM_CTRL_TCM_ECC_EN_SHIFT    (5U)
/*! TCM_ECC_EN - TCM ECC enable */
#define FLEXRAM_FLEXRAM_CTRL_TCM_ECC_EN(x)       (((uint32_t)(((uint32_t)(x)) << FLEXRAM_FLEXRAM_CTRL_TCM_ECC_EN_SHIFT)) & FLEXRAM_FLEXRAM_CTRL_TCM_ECC_EN_MASK)

#define FLEXRAM_FLEXRAM_CTRL_Reserved_MASK       (0xFFFFFFC0U)
#define FLEXRAM_FLEXRAM_CTRL_Reserved_SHIFT      (6U)
/*! Reserved - Reserved */
#define FLEXRAM_FLEXRAM_CTRL_Reserved(x)         (((uint32_t)(((uint32_t)(x)) << FLEXRAM_FLEXRAM_CTRL_Reserved_SHIFT)) & FLEXRAM_FLEXRAM_CTRL_Reserved_MASK)
/*! @} */

/*! @name OCRAM_PIPELINE_STATUS - OCRAM Pipeline Status register */
/*! @{ */

#define FLEXRAM_OCRAM_PIPELINE_STATUS_OCRAM_RDATA_WAIT_EN_UPDATA_PENDING_MASK (0x1U)
#define FLEXRAM_OCRAM_PIPELINE_STATUS_OCRAM_RDATA_WAIT_EN_UPDATA_PENDING_SHIFT (0U)
/*! OCRAM_RDATA_WAIT_EN_UPDATA_PENDING - Read Data Wait Enable Pending */
#define FLEXRAM_OCRAM_PIPELINE_STATUS_OCRAM_RDATA_WAIT_EN_UPDATA_PENDING(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_OCRAM_PIPELINE_STATUS_OCRAM_RDATA_WAIT_EN_UPDATA_PENDING_SHIFT)) & FLEXRAM_OCRAM_PIPELINE_STATUS_OCRAM_RDATA_WAIT_EN_UPDATA_PENDING_MASK)

#define FLEXRAM_OCRAM_PIPELINE_STATUS_OCRAM_RADDR_PIPELINE_EN_UPDATA_PENDING_MASK (0x2U)
#define FLEXRAM_OCRAM_PIPELINE_STATUS_OCRAM_RADDR_PIPELINE_EN_UPDATA_PENDING_SHIFT (1U)
/*! OCRAM_RADDR_PIPELINE_EN_UPDATA_PENDING - Read Address Pipeline Enable Pending */
#define FLEXRAM_OCRAM_PIPELINE_STATUS_OCRAM_RADDR_PIPELINE_EN_UPDATA_PENDING(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_OCRAM_PIPELINE_STATUS_OCRAM_RADDR_PIPELINE_EN_UPDATA_PENDING_SHIFT)) & FLEXRAM_OCRAM_PIPELINE_STATUS_OCRAM_RADDR_PIPELINE_EN_UPDATA_PENDING_MASK)

#define FLEXRAM_OCRAM_PIPELINE_STATUS_OCRAM_WRDATA_PIPELINE_EN_UPDATA_PENDING_MASK (0x4U)
#define FLEXRAM_OCRAM_PIPELINE_STATUS_OCRAM_WRDATA_PIPELINE_EN_UPDATA_PENDING_SHIFT (2U)
/*! OCRAM_WRDATA_PIPELINE_EN_UPDATA_PENDING - Write Data Pipeline Enable Pending */
#define FLEXRAM_OCRAM_PIPELINE_STATUS_OCRAM_WRDATA_PIPELINE_EN_UPDATA_PENDING(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_OCRAM_PIPELINE_STATUS_OCRAM_WRDATA_PIPELINE_EN_UPDATA_PENDING_SHIFT)) & FLEXRAM_OCRAM_PIPELINE_STATUS_OCRAM_WRDATA_PIPELINE_EN_UPDATA_PENDING_MASK)

#define FLEXRAM_OCRAM_PIPELINE_STATUS_OCRAM_WRADDR_PIPELINE_EN_UPDATA_PENDING_MASK (0x8U)
#define FLEXRAM_OCRAM_PIPELINE_STATUS_OCRAM_WRADDR_PIPELINE_EN_UPDATA_PENDING_SHIFT (3U)
/*! OCRAM_WRADDR_PIPELINE_EN_UPDATA_PENDING - Write Address Pipeline Enable Pending */
#define FLEXRAM_OCRAM_PIPELINE_STATUS_OCRAM_WRADDR_PIPELINE_EN_UPDATA_PENDING(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_OCRAM_PIPELINE_STATUS_OCRAM_WRADDR_PIPELINE_EN_UPDATA_PENDING_SHIFT)) & FLEXRAM_OCRAM_PIPELINE_STATUS_OCRAM_WRADDR_PIPELINE_EN_UPDATA_PENDING_MASK)

#define FLEXRAM_OCRAM_PIPELINE_STATUS_Reserved_MASK (0xFFFFFFF0U)
#define FLEXRAM_OCRAM_PIPELINE_STATUS_Reserved_SHIFT (4U)
/*! Reserved - Reserved */
#define FLEXRAM_OCRAM_PIPELINE_STATUS_Reserved(x) (((uint32_t)(((uint32_t)(x)) << FLEXRAM_OCRAM_PIPELINE_STATUS_Reserved_SHIFT)) & FLEXRAM_OCRAM_PIPELINE_STATUS_Reserved_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group FLEXRAM_Register_Masks */


/*!
 * @}
 */ /* end of group FLEXRAM_Peripheral_Access_Layer */


/*
** End of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic pop
  #else
    #pragma pop
  #endif
#elif defined(__CWCC__)
  #pragma pop
#elif defined(__GNUC__)
  /* leave anonymous unions enabled */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=default
#else
  #error Not supported compiler type
#endif

/*!
 * @}
 */ /* end of group Peripheral_access_layer */


#endif  /* PERI_FLEXRAM_H_ */

