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
**         CMSIS Peripheral Access Layer for XECC
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
 * @file PERI_XECC.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for XECC
 *
 * CMSIS Peripheral Access Layer for XECC
 */

#if !defined(PERI_XECC_H_)
#define PERI_XECC_H_                             /**< Symbol preventing repeated inclusion */

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
   -- XECC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup XECC_Peripheral_Access_Layer XECC Peripheral Access Layer
 * @{
 */

/** XECC - Register Layout Typedef */
typedef struct {
  __IO uint32_t ECC_CTRL;                          /**< ECC Control Register, offset: 0x0 */
  __IO uint32_t ERR_STATUS;                        /**< Error Interrupt Status Register, offset: 0x4 */
  __IO uint32_t ERR_STAT_EN;                       /**< Error Interrupt Status Enable Register, offset: 0x8 */
  __IO uint32_t ERR_SIG_EN;                        /**< Error Interrupt Enable Register, offset: 0xC */
  __IO uint32_t ERR_DATA_INJ;                      /**< Error Injection On Write Data, offset: 0x10 */
  __IO uint32_t ERR_ECC_INJ;                       /**< Error Injection On ECC Code of Write Data, offset: 0x14 */
  __I  uint32_t SINGLE_ERR_ADDR;                   /**< Single Error Address, offset: 0x18 */
  __I  uint32_t SINGLE_ERR_DATA;                   /**< Single Error Read Data, offset: 0x1C */
  __I  uint32_t SINGLE_ERR_ECC;                    /**< Single Error ECC Code, offset: 0x20 */
  __I  uint32_t SINGLE_ERR_POS;                    /**< Single Error Bit Position, offset: 0x24 */
  __I  uint32_t SINGLE_ERR_BIT_FIELD;              /**< Single Error Bit Field, offset: 0x28 */
  __I  uint32_t MULTI_ERR_ADDR;                    /**< Multiple Error Address, offset: 0x2C */
  __I  uint32_t MULTI_ERR_DATA;                    /**< Multiple Error Read Data, offset: 0x30 */
  __I  uint32_t MULTI_ERR_ECC;                     /**< Multiple Error ECC code, offset: 0x34 */
  __I  uint32_t MULTI_ERR_BIT_FIELD;               /**< Multiple Error Bit Field, offset: 0x38 */
  __IO uint32_t ECC_BASE_ADDR0;                    /**< ECC Region 0 Base Address, offset: 0x3C */
  __IO uint32_t ECC_END_ADDR0;                     /**< ECC Region 0 End Address, offset: 0x40 */
  __IO uint32_t ECC_BASE_ADDR1;                    /**< ECC Region 1 Base Address, offset: 0x44 */
  __IO uint32_t ECC_END_ADDR1;                     /**< ECC Region 1 End Address, offset: 0x48 */
  __IO uint32_t ECC_BASE_ADDR2;                    /**< ECC Region 2 Base Address, offset: 0x4C */
  __IO uint32_t ECC_END_ADDR2;                     /**< ECC Region 2 End Address, offset: 0x50 */
  __IO uint32_t ECC_BASE_ADDR3;                    /**< ECC Region 3 Base Address, offset: 0x54 */
  __IO uint32_t ECC_END_ADDR3;                     /**< ECC Region 3 End Address, offset: 0x58 */
} XECC_Type;

/* ----------------------------------------------------------------------------
   -- XECC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup XECC_Register_Masks XECC Register Masks
 * @{
 */

/*! @name ECC_CTRL - ECC Control Register */
/*! @{ */

#define XECC_ECC_CTRL_ECC_EN_MASK                (0x1U)
#define XECC_ECC_CTRL_ECC_EN_SHIFT               (0U)
/*! ECC_EN - ECC Function Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define XECC_ECC_CTRL_ECC_EN(x)                  (((uint32_t)(((uint32_t)(x)) << XECC_ECC_CTRL_ECC_EN_SHIFT)) & XECC_ECC_CTRL_ECC_EN_MASK)

#define XECC_ECC_CTRL_WECC_EN_MASK               (0x2U)
#define XECC_ECC_CTRL_WECC_EN_SHIFT              (1U)
/*! WECC_EN - Write ECC Encode Function Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define XECC_ECC_CTRL_WECC_EN(x)                 (((uint32_t)(((uint32_t)(x)) << XECC_ECC_CTRL_WECC_EN_SHIFT)) & XECC_ECC_CTRL_WECC_EN_MASK)

#define XECC_ECC_CTRL_RECC_EN_MASK               (0x4U)
#define XECC_ECC_CTRL_RECC_EN_SHIFT              (2U)
/*! RECC_EN - Read ECC Function Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define XECC_ECC_CTRL_RECC_EN(x)                 (((uint32_t)(((uint32_t)(x)) << XECC_ECC_CTRL_RECC_EN_SHIFT)) & XECC_ECC_CTRL_RECC_EN_MASK)

#define XECC_ECC_CTRL_SWAP_EN_MASK               (0x8U)
#define XECC_ECC_CTRL_SWAP_EN_SHIFT              (3U)
/*! SWAP_EN - Swap Data Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define XECC_ECC_CTRL_SWAP_EN(x)                 (((uint32_t)(((uint32_t)(x)) << XECC_ECC_CTRL_SWAP_EN_SHIFT)) & XECC_ECC_CTRL_SWAP_EN_MASK)
/*! @} */

/*! @name ERR_STATUS - Error Interrupt Status Register */
/*! @{ */

#define XECC_ERR_STATUS_SINGLE_ERR_MASK          (0x1U)
#define XECC_ERR_STATUS_SINGLE_ERR_SHIFT         (0U)
/*! SINGLE_ERR - Single Bit Error
 *  0b0..Single bit error does not happen.
 *  0b1..Single bit error happens.
 */
#define XECC_ERR_STATUS_SINGLE_ERR(x)            (((uint32_t)(((uint32_t)(x)) << XECC_ERR_STATUS_SINGLE_ERR_SHIFT)) & XECC_ERR_STATUS_SINGLE_ERR_MASK)

#define XECC_ERR_STATUS_MULTI_ERR_MASK           (0x2U)
#define XECC_ERR_STATUS_MULTI_ERR_SHIFT          (1U)
/*! MULTI_ERR - Multiple Bits Error
 *  0b0..Multiple bits error does not happen.
 *  0b1..Multiple bits error happens.
 */
#define XECC_ERR_STATUS_MULTI_ERR(x)             (((uint32_t)(((uint32_t)(x)) << XECC_ERR_STATUS_MULTI_ERR_SHIFT)) & XECC_ERR_STATUS_MULTI_ERR_MASK)

#define XECC_ERR_STATUS_Reserved1_MASK           (0xFFFFFFFCU)
#define XECC_ERR_STATUS_Reserved1_SHIFT          (2U)
/*! Reserved1 - Reserved */
#define XECC_ERR_STATUS_Reserved1(x)             (((uint32_t)(((uint32_t)(x)) << XECC_ERR_STATUS_Reserved1_SHIFT)) & XECC_ERR_STATUS_Reserved1_MASK)
/*! @} */

/*! @name ERR_STAT_EN - Error Interrupt Status Enable Register */
/*! @{ */

#define XECC_ERR_STAT_EN_SINGLE_ERR_STAT_EN_MASK (0x1U)
#define XECC_ERR_STAT_EN_SINGLE_ERR_STAT_EN_SHIFT (0U)
/*! SINGLE_ERR_STAT_EN - Single Bit Error Status Enable
 *  0b0..Masked
 *  0b1..Enabled
 */
#define XECC_ERR_STAT_EN_SINGLE_ERR_STAT_EN(x)   (((uint32_t)(((uint32_t)(x)) << XECC_ERR_STAT_EN_SINGLE_ERR_STAT_EN_SHIFT)) & XECC_ERR_STAT_EN_SINGLE_ERR_STAT_EN_MASK)

#define XECC_ERR_STAT_EN_MULIT_ERR_STAT_EN_MASK  (0x2U)
#define XECC_ERR_STAT_EN_MULIT_ERR_STAT_EN_SHIFT (1U)
/*! MULIT_ERR_STAT_EN - Multiple Bits Error Status Enable
 *  0b0..Masked
 *  0b1..Enabled
 */
#define XECC_ERR_STAT_EN_MULIT_ERR_STAT_EN(x)    (((uint32_t)(((uint32_t)(x)) << XECC_ERR_STAT_EN_MULIT_ERR_STAT_EN_SHIFT)) & XECC_ERR_STAT_EN_MULIT_ERR_STAT_EN_MASK)

#define XECC_ERR_STAT_EN_Reserved1_MASK          (0xFFFFFFFCU)
#define XECC_ERR_STAT_EN_Reserved1_SHIFT         (2U)
/*! Reserved1 - Reserved */
#define XECC_ERR_STAT_EN_Reserved1(x)            (((uint32_t)(((uint32_t)(x)) << XECC_ERR_STAT_EN_Reserved1_SHIFT)) & XECC_ERR_STAT_EN_Reserved1_MASK)
/*! @} */

/*! @name ERR_SIG_EN - Error Interrupt Enable Register */
/*! @{ */

#define XECC_ERR_SIG_EN_SINGLE_ERR_SIG_EN_MASK   (0x1U)
#define XECC_ERR_SIG_EN_SINGLE_ERR_SIG_EN_SHIFT  (0U)
/*! SINGLE_ERR_SIG_EN - Single Bit Error Interrupt Enable
 *  0b0..Masked
 *  0b1..Enabled
 */
#define XECC_ERR_SIG_EN_SINGLE_ERR_SIG_EN(x)     (((uint32_t)(((uint32_t)(x)) << XECC_ERR_SIG_EN_SINGLE_ERR_SIG_EN_SHIFT)) & XECC_ERR_SIG_EN_SINGLE_ERR_SIG_EN_MASK)

#define XECC_ERR_SIG_EN_MULTI_ERR_SIG_EN_MASK    (0x2U)
#define XECC_ERR_SIG_EN_MULTI_ERR_SIG_EN_SHIFT   (1U)
/*! MULTI_ERR_SIG_EN - Multiple Bits Error Interrupt Enable
 *  0b0..Masked
 *  0b1..Enabled
 */
#define XECC_ERR_SIG_EN_MULTI_ERR_SIG_EN(x)      (((uint32_t)(((uint32_t)(x)) << XECC_ERR_SIG_EN_MULTI_ERR_SIG_EN_SHIFT)) & XECC_ERR_SIG_EN_MULTI_ERR_SIG_EN_MASK)

#define XECC_ERR_SIG_EN_Reserved1_MASK           (0xFFFFFFFCU)
#define XECC_ERR_SIG_EN_Reserved1_SHIFT          (2U)
/*! Reserved1 - Reserved */
#define XECC_ERR_SIG_EN_Reserved1(x)             (((uint32_t)(((uint32_t)(x)) << XECC_ERR_SIG_EN_Reserved1_SHIFT)) & XECC_ERR_SIG_EN_Reserved1_MASK)
/*! @} */

/*! @name ERR_DATA_INJ - Error Injection On Write Data */
/*! @{ */

#define XECC_ERR_DATA_INJ_ERR_DATA_INJ_MASK      (0xFFFFFFFFU)
#define XECC_ERR_DATA_INJ_ERR_DATA_INJ_SHIFT     (0U)
/*! ERR_DATA_INJ - Error Injection On Write Data */
#define XECC_ERR_DATA_INJ_ERR_DATA_INJ(x)        (((uint32_t)(((uint32_t)(x)) << XECC_ERR_DATA_INJ_ERR_DATA_INJ_SHIFT)) & XECC_ERR_DATA_INJ_ERR_DATA_INJ_MASK)
/*! @} */

/*! @name ERR_ECC_INJ - Error Injection On ECC Code of Write Data */
/*! @{ */

#define XECC_ERR_ECC_INJ_ERR_ECC_INJ_MASK        (0xFFFFFFFFU)
#define XECC_ERR_ECC_INJ_ERR_ECC_INJ_SHIFT       (0U)
/*! ERR_ECC_INJ - Error Injection On ECC Code of Write Data */
#define XECC_ERR_ECC_INJ_ERR_ECC_INJ(x)          (((uint32_t)(((uint32_t)(x)) << XECC_ERR_ECC_INJ_ERR_ECC_INJ_SHIFT)) & XECC_ERR_ECC_INJ_ERR_ECC_INJ_MASK)
/*! @} */

/*! @name SINGLE_ERR_ADDR - Single Error Address */
/*! @{ */

#define XECC_SINGLE_ERR_ADDR_SINGLE_ERR_ADDR_MASK (0xFFFFFFFFU)
#define XECC_SINGLE_ERR_ADDR_SINGLE_ERR_ADDR_SHIFT (0U)
/*! SINGLE_ERR_ADDR - Single Error Address */
#define XECC_SINGLE_ERR_ADDR_SINGLE_ERR_ADDR(x)  (((uint32_t)(((uint32_t)(x)) << XECC_SINGLE_ERR_ADDR_SINGLE_ERR_ADDR_SHIFT)) & XECC_SINGLE_ERR_ADDR_SINGLE_ERR_ADDR_MASK)
/*! @} */

/*! @name SINGLE_ERR_DATA - Single Error Read Data */
/*! @{ */

#define XECC_SINGLE_ERR_DATA_SINGLE_ERR_DATA_MASK (0xFFFFFFFFU)
#define XECC_SINGLE_ERR_DATA_SINGLE_ERR_DATA_SHIFT (0U)
/*! SINGLE_ERR_DATA - Single Error Read Data */
#define XECC_SINGLE_ERR_DATA_SINGLE_ERR_DATA(x)  (((uint32_t)(((uint32_t)(x)) << XECC_SINGLE_ERR_DATA_SINGLE_ERR_DATA_SHIFT)) & XECC_SINGLE_ERR_DATA_SINGLE_ERR_DATA_MASK)
/*! @} */

/*! @name SINGLE_ERR_ECC - Single Error ECC Code */
/*! @{ */

#define XECC_SINGLE_ERR_ECC_SINGLE_ERR_ECC_MASK  (0xFFFFFFFFU)
#define XECC_SINGLE_ERR_ECC_SINGLE_ERR_ECC_SHIFT (0U)
/*! SINGLE_ERR_ECC - Single Error ECC code */
#define XECC_SINGLE_ERR_ECC_SINGLE_ERR_ECC(x)    (((uint32_t)(((uint32_t)(x)) << XECC_SINGLE_ERR_ECC_SINGLE_ERR_ECC_SHIFT)) & XECC_SINGLE_ERR_ECC_SINGLE_ERR_ECC_MASK)
/*! @} */

/*! @name SINGLE_ERR_POS - Single Error Bit Position */
/*! @{ */

#define XECC_SINGLE_ERR_POS_SINGLE_ERR_POS_MASK  (0xFFFFFFFFU)
#define XECC_SINGLE_ERR_POS_SINGLE_ERR_POS_SHIFT (0U)
/*! SINGLE_ERR_POS - Single Error bit Position */
#define XECC_SINGLE_ERR_POS_SINGLE_ERR_POS(x)    (((uint32_t)(((uint32_t)(x)) << XECC_SINGLE_ERR_POS_SINGLE_ERR_POS_SHIFT)) & XECC_SINGLE_ERR_POS_SINGLE_ERR_POS_MASK)
/*! @} */

/*! @name SINGLE_ERR_BIT_FIELD - Single Error Bit Field */
/*! @{ */

#define XECC_SINGLE_ERR_BIT_FIELD_SINGLE_ERR_BIT_FIELD_MASK (0xFFU)
#define XECC_SINGLE_ERR_BIT_FIELD_SINGLE_ERR_BIT_FIELD_SHIFT (0U)
/*! SINGLE_ERR_BIT_FIELD - Single Error Bit Field */
#define XECC_SINGLE_ERR_BIT_FIELD_SINGLE_ERR_BIT_FIELD(x) (((uint32_t)(((uint32_t)(x)) << XECC_SINGLE_ERR_BIT_FIELD_SINGLE_ERR_BIT_FIELD_SHIFT)) & XECC_SINGLE_ERR_BIT_FIELD_SINGLE_ERR_BIT_FIELD_MASK)

#define XECC_SINGLE_ERR_BIT_FIELD_Reserved1_MASK (0xFFFFFF00U)
#define XECC_SINGLE_ERR_BIT_FIELD_Reserved1_SHIFT (8U)
/*! Reserved1 - Reserved */
#define XECC_SINGLE_ERR_BIT_FIELD_Reserved1(x)   (((uint32_t)(((uint32_t)(x)) << XECC_SINGLE_ERR_BIT_FIELD_Reserved1_SHIFT)) & XECC_SINGLE_ERR_BIT_FIELD_Reserved1_MASK)
/*! @} */

/*! @name MULTI_ERR_ADDR - Multiple Error Address */
/*! @{ */

#define XECC_MULTI_ERR_ADDR_MULTI_ERR_ADDR_MASK  (0xFFFFFFFFU)
#define XECC_MULTI_ERR_ADDR_MULTI_ERR_ADDR_SHIFT (0U)
/*! MULTI_ERR_ADDR - Multiple Error Address */
#define XECC_MULTI_ERR_ADDR_MULTI_ERR_ADDR(x)    (((uint32_t)(((uint32_t)(x)) << XECC_MULTI_ERR_ADDR_MULTI_ERR_ADDR_SHIFT)) & XECC_MULTI_ERR_ADDR_MULTI_ERR_ADDR_MASK)
/*! @} */

/*! @name MULTI_ERR_DATA - Multiple Error Read Data */
/*! @{ */

#define XECC_MULTI_ERR_DATA_MULTI_ERR_DATA_MASK  (0xFFFFFFFFU)
#define XECC_MULTI_ERR_DATA_MULTI_ERR_DATA_SHIFT (0U)
/*! MULTI_ERR_DATA - Multiple Error Read Data */
#define XECC_MULTI_ERR_DATA_MULTI_ERR_DATA(x)    (((uint32_t)(((uint32_t)(x)) << XECC_MULTI_ERR_DATA_MULTI_ERR_DATA_SHIFT)) & XECC_MULTI_ERR_DATA_MULTI_ERR_DATA_MASK)
/*! @} */

/*! @name MULTI_ERR_ECC - Multiple Error ECC code */
/*! @{ */

#define XECC_MULTI_ERR_ECC_MULTI_ERR_ECC_MASK    (0xFFFFFFFFU)
#define XECC_MULTI_ERR_ECC_MULTI_ERR_ECC_SHIFT   (0U)
/*! MULTI_ERR_ECC - Multiple Error ECC code */
#define XECC_MULTI_ERR_ECC_MULTI_ERR_ECC(x)      (((uint32_t)(((uint32_t)(x)) << XECC_MULTI_ERR_ECC_MULTI_ERR_ECC_SHIFT)) & XECC_MULTI_ERR_ECC_MULTI_ERR_ECC_MASK)
/*! @} */

/*! @name MULTI_ERR_BIT_FIELD - Multiple Error Bit Field */
/*! @{ */

#define XECC_MULTI_ERR_BIT_FIELD_MULTI_ERR_BIT_FIELD_MASK (0xFFU)
#define XECC_MULTI_ERR_BIT_FIELD_MULTI_ERR_BIT_FIELD_SHIFT (0U)
/*! MULTI_ERR_BIT_FIELD - Multiple Error Bit Field */
#define XECC_MULTI_ERR_BIT_FIELD_MULTI_ERR_BIT_FIELD(x) (((uint32_t)(((uint32_t)(x)) << XECC_MULTI_ERR_BIT_FIELD_MULTI_ERR_BIT_FIELD_SHIFT)) & XECC_MULTI_ERR_BIT_FIELD_MULTI_ERR_BIT_FIELD_MASK)

#define XECC_MULTI_ERR_BIT_FIELD_Reserved1_MASK  (0xFFFFFF00U)
#define XECC_MULTI_ERR_BIT_FIELD_Reserved1_SHIFT (8U)
/*! Reserved1 - Reserved */
#define XECC_MULTI_ERR_BIT_FIELD_Reserved1(x)    (((uint32_t)(((uint32_t)(x)) << XECC_MULTI_ERR_BIT_FIELD_Reserved1_SHIFT)) & XECC_MULTI_ERR_BIT_FIELD_Reserved1_MASK)
/*! @} */

/*! @name ECC_BASE_ADDR0 - ECC Region 0 Base Address */
/*! @{ */

#define XECC_ECC_BASE_ADDR0_ECC_BASE_ADDR0_MASK  (0xFFFFFFFFU)
#define XECC_ECC_BASE_ADDR0_ECC_BASE_ADDR0_SHIFT (0U)
/*! ECC_BASE_ADDR0 - ECC Region 0 Base Address */
#define XECC_ECC_BASE_ADDR0_ECC_BASE_ADDR0(x)    (((uint32_t)(((uint32_t)(x)) << XECC_ECC_BASE_ADDR0_ECC_BASE_ADDR0_SHIFT)) & XECC_ECC_BASE_ADDR0_ECC_BASE_ADDR0_MASK)
/*! @} */

/*! @name ECC_END_ADDR0 - ECC Region 0 End Address */
/*! @{ */

#define XECC_ECC_END_ADDR0_ECC_END_ADDR0_MASK    (0xFFFFFFFFU)
#define XECC_ECC_END_ADDR0_ECC_END_ADDR0_SHIFT   (0U)
/*! ECC_END_ADDR0 - ECC Region 0 End Address */
#define XECC_ECC_END_ADDR0_ECC_END_ADDR0(x)      (((uint32_t)(((uint32_t)(x)) << XECC_ECC_END_ADDR0_ECC_END_ADDR0_SHIFT)) & XECC_ECC_END_ADDR0_ECC_END_ADDR0_MASK)
/*! @} */

/*! @name ECC_BASE_ADDR1 - ECC Region 1 Base Address */
/*! @{ */

#define XECC_ECC_BASE_ADDR1_ECC_BASE_ADDR1_MASK  (0xFFFFFFFFU)
#define XECC_ECC_BASE_ADDR1_ECC_BASE_ADDR1_SHIFT (0U)
/*! ECC_BASE_ADDR1 - ECC Region 1 Base Address */
#define XECC_ECC_BASE_ADDR1_ECC_BASE_ADDR1(x)    (((uint32_t)(((uint32_t)(x)) << XECC_ECC_BASE_ADDR1_ECC_BASE_ADDR1_SHIFT)) & XECC_ECC_BASE_ADDR1_ECC_BASE_ADDR1_MASK)
/*! @} */

/*! @name ECC_END_ADDR1 - ECC Region 1 End Address */
/*! @{ */

#define XECC_ECC_END_ADDR1_ECC_END_ADDR1_MASK    (0xFFFFFFFFU)
#define XECC_ECC_END_ADDR1_ECC_END_ADDR1_SHIFT   (0U)
/*! ECC_END_ADDR1 - ECC Region 1 End Address */
#define XECC_ECC_END_ADDR1_ECC_END_ADDR1(x)      (((uint32_t)(((uint32_t)(x)) << XECC_ECC_END_ADDR1_ECC_END_ADDR1_SHIFT)) & XECC_ECC_END_ADDR1_ECC_END_ADDR1_MASK)
/*! @} */

/*! @name ECC_BASE_ADDR2 - ECC Region 2 Base Address */
/*! @{ */

#define XECC_ECC_BASE_ADDR2_ECC_BASE_ADDR2_MASK  (0xFFFFFFFFU)
#define XECC_ECC_BASE_ADDR2_ECC_BASE_ADDR2_SHIFT (0U)
/*! ECC_BASE_ADDR2 - ECC Region 2 Base Address */
#define XECC_ECC_BASE_ADDR2_ECC_BASE_ADDR2(x)    (((uint32_t)(((uint32_t)(x)) << XECC_ECC_BASE_ADDR2_ECC_BASE_ADDR2_SHIFT)) & XECC_ECC_BASE_ADDR2_ECC_BASE_ADDR2_MASK)
/*! @} */

/*! @name ECC_END_ADDR2 - ECC Region 2 End Address */
/*! @{ */

#define XECC_ECC_END_ADDR2_ECC_END_ADDR2_MASK    (0xFFFFFFFFU)
#define XECC_ECC_END_ADDR2_ECC_END_ADDR2_SHIFT   (0U)
/*! ECC_END_ADDR2 - ECC Region 2 End Address */
#define XECC_ECC_END_ADDR2_ECC_END_ADDR2(x)      (((uint32_t)(((uint32_t)(x)) << XECC_ECC_END_ADDR2_ECC_END_ADDR2_SHIFT)) & XECC_ECC_END_ADDR2_ECC_END_ADDR2_MASK)
/*! @} */

/*! @name ECC_BASE_ADDR3 - ECC Region 3 Base Address */
/*! @{ */

#define XECC_ECC_BASE_ADDR3_ECC_BASE_ADDR3_MASK  (0xFFFFFFFFU)
#define XECC_ECC_BASE_ADDR3_ECC_BASE_ADDR3_SHIFT (0U)
/*! ECC_BASE_ADDR3 - ECC Region 3 Base Address */
#define XECC_ECC_BASE_ADDR3_ECC_BASE_ADDR3(x)    (((uint32_t)(((uint32_t)(x)) << XECC_ECC_BASE_ADDR3_ECC_BASE_ADDR3_SHIFT)) & XECC_ECC_BASE_ADDR3_ECC_BASE_ADDR3_MASK)
/*! @} */

/*! @name ECC_END_ADDR3 - ECC Region 3 End Address */
/*! @{ */

#define XECC_ECC_END_ADDR3_ECC_END_ADDR3_MASK    (0xFFFFFFFFU)
#define XECC_ECC_END_ADDR3_ECC_END_ADDR3_SHIFT   (0U)
/*! ECC_END_ADDR3 - ECC Region 3 End Address */
#define XECC_ECC_END_ADDR3_ECC_END_ADDR3(x)      (((uint32_t)(((uint32_t)(x)) << XECC_ECC_END_ADDR3_ECC_END_ADDR3_SHIFT)) & XECC_ECC_END_ADDR3_ECC_END_ADDR3_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group XECC_Register_Masks */


/*!
 * @}
 */ /* end of group XECC_Peripheral_Access_Layer */


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


#endif  /* PERI_XECC_H_ */

