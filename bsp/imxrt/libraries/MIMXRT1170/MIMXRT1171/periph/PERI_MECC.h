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
**         CMSIS Peripheral Access Layer for MECC
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
 * @file PERI_MECC.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for MECC
 *
 * CMSIS Peripheral Access Layer for MECC
 */

#if !defined(PERI_MECC_H_)
#define PERI_MECC_H_                             /**< Symbol preventing repeated inclusion */

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
   -- MECC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MECC_Peripheral_Access_Layer MECC Peripheral Access Layer
 * @{
 */

/** MECC - Register Layout Typedef */
typedef struct {
  __IO uint32_t ERR_STATUS;                        /**< Error Interrupt Status Register, offset: 0x0 */
  __IO uint32_t ERR_STAT_EN;                       /**< Error Interrupt Status Enable Register, offset: 0x4 */
  __IO uint32_t ERR_SIG_EN;                        /**< Error Interrupt Enable Register, offset: 0x8 */
  __IO uint32_t ERR_DATA_INJ_LOW0;                 /**< Error Injection On LOW 32 bits Of OCRAM Bank0 Write Data, offset: 0xC */
  __IO uint32_t ERR_DATA_INJ_HIGH0;                /**< Error Injection On HIGH 32 bits Of OCRAM Bank0 Write Data, offset: 0x10 */
  __IO uint32_t ERR_ECC_INJ0;                      /**< Error Injection On 8 bits ECC code Of OCRAM Bank0 Write Data, offset: 0x14 */
  __IO uint32_t ERR_DATA_INJ_LOW1;                 /**< Error Injection On LOW 32 bits Of OCRAM Bank1 Write Data, offset: 0x18 */
  __IO uint32_t ERR_DATA_INJ_HIGH1;                /**< Error Injection On HIGH 32 bits Of OCRAM Bank1 Write Data, offset: 0x1C */
  __IO uint32_t ERR_ECC_INJ1;                      /**< Error Injection On 8 bits ECC code Of OCRAM Bank1 Write Data, offset: 0x20 */
  __IO uint32_t ERR_DATA_INJ_LOW2;                 /**< Error Injection On LOW 32 bits Of OCRAM Bank2 Write Data, offset: 0x24 */
  __IO uint32_t ERR_DATA_INJ_HIGH2;                /**< Error Injection On HIGH 32 bits Of OCRAM Bank2 Write Data, offset: 0x28 */
  __IO uint32_t ERR_ECC_INJ2;                      /**< Error Injection On 8 bits ECC code Of OCRAM Bank2 Write Data, offset: 0x2C */
  __IO uint32_t ERR_DATA_INJ_LOW3;                 /**< Error Injection On LOW 32 bits Of OCRAM Bank3 Write Data, offset: 0x30 */
  __IO uint32_t ERR_DATA_INJ_HIGH3;                /**< Error Injection On HIGH 32 bits Of OCRAM Bank3 Write Data, offset: 0x34 */
  __IO uint32_t ERR_ECC_INJ3;                      /**< Error Injection On 8 bits ECC code Of OCRAM Bank3 Write Data, offset: 0x38 */
  __I  uint32_t SINGLE_ERR_ADDR_ECC0;              /**< Single Error Address And ECC code On OCRAM Bank0, offset: 0x3C */
  __I  uint32_t SINGLE_ERR_DATA_LOW0;              /**< LOW 32 Bits Single Error Read Data On OCRAM Bank0, offset: 0x40 */
  __I  uint32_t SINGLE_ERR_DATA_HIGH0;             /**< HIGH 32 Bits Single Error Read Data On OCRAM Bank0, offset: 0x44 */
  __I  uint32_t SINGLE_ERR_POS_LOW0;               /**< LOW Single Error Bit Position On OCRAM Bank0, offset: 0x48 */
  __I  uint32_t SINGLE_ERR_POS_HIGH0;              /**< HIGH Single Error Bit Position On OCRAM Bank0, offset: 0x4C */
  __I  uint32_t SINGLE_ERR_ADDR_ECC1;              /**< Single Error Address And ECC code On OCRAM Bank1, offset: 0x50 */
  __I  uint32_t SINGLE_ERR_DATA_LOW1;              /**< LOW 32 Bits Single Error Read Data On OCRAM Bank1, offset: 0x54 */
  __I  uint32_t SINGLE_ERR_DATA_HIGH1;             /**< HIGH 32 Bits Single Error Read Data On OCRAM Bank1, offset: 0x58 */
  __I  uint32_t SINGLE_ERR_POS_LOW1;               /**< LOW Single Error Bit Position On OCRAM Bank1, offset: 0x5C */
  __I  uint32_t SINGLE_ERR_POS_HIGH1;              /**< HIGH Single Error Bit Position On OCRAM Bank1, offset: 0x60 */
  __I  uint32_t SINGLE_ERR_ADDR_ECC2;              /**< Single Error Address And ECC code On OCRAM Bank2, offset: 0x64 */
  __I  uint32_t SINGLE_ERR_DATA_LOW2;              /**< LOW 32 Bits Single Error Read Data On OCRAM Bank2, offset: 0x68 */
  __I  uint32_t SINGLE_ERR_DATA_HIGH2;             /**< HIGH 32 Bits Single Error Read Data On OCRAM Bank2, offset: 0x6C */
  __I  uint32_t SINGLE_ERR_POS_LOW2;               /**< LOW Single Error Bit Position On OCRAM Bank2, offset: 0x70 */
  __I  uint32_t SINGLE_ERR_POS_HIGH2;              /**< HIGH Single Error Bit Position On OCRAM Bank2, offset: 0x74 */
  __I  uint32_t SINGLE_ERR_ADDR_ECC3;              /**< Single Error Address And ECC code On OCRAM Bank3, offset: 0x78 */
  __I  uint32_t SINGLE_ERR_DATA_LOW3;              /**< LOW 32 Bits Single Error Read Data On OCRAM Bank3, offset: 0x7C */
  __I  uint32_t SINGLE_ERR_DATA_HIGH3;             /**< HIGH 32 Bits Single Error Read Data On OCRAM Bank3, offset: 0x80 */
  __I  uint32_t SINGLE_ERR_POS_LOW3;               /**< LOW Single Error Bit Position On OCRAM Bank3, offset: 0x84 */
  __I  uint32_t SINGLE_ERR_POS_HIGH3;              /**< HIGH Single Error Bit Position On OCRAM Bank3, offset: 0x88 */
  __I  uint32_t MULTI_ERR_ADDR_ECC0;               /**< Multiple Error Address And ECC code On OCRAM Bank0, offset: 0x8C */
  __I  uint32_t MULTI_ERR_DATA_LOW0;               /**< LOW 32 Bits Multiple Error Read Data On OCRAM Bank0, offset: 0x90 */
  __I  uint32_t MULTI_ERR_DATA_HIGH0;              /**< HIGH 32 Bits Multiple Error Read Data On OCRAM Bank0, offset: 0x94 */
  __I  uint32_t MULTI_ERR_ADDR_ECC1;               /**< Multiple Error Address And ECC code On OCRAM Bank1, offset: 0x98 */
  __I  uint32_t MULTI_ERR_DATA_LOW1;               /**< LOW 32 Bits Multiple Error Read Data On OCRAM Bank1, offset: 0x9C */
  __I  uint32_t MULTI_ERR_DATA_HIGH1;              /**< HIGH 32 Bits Multiple Error Read Data On OCRAM Bank1, offset: 0xA0 */
  __I  uint32_t MULTI_ERR_ADDR_ECC2;               /**< Multiple Error Address And ECC code On OCRAM Bank2, offset: 0xA4 */
  __I  uint32_t MULTI_ERR_DATA_LOW2;               /**< LOW 32 Bits Multiple Error Read Data On OCRAM Bank2, offset: 0xA8 */
  __I  uint32_t MULTI_ERR_DATA_HIGH2;              /**< HIGH 32 Bits Multiple Error Read Data On OCRAM Bank2, offset: 0xAC */
  __I  uint32_t MULTI_ERR_ADDR_ECC3;               /**< Multiple Error Address And ECC code On OCRAM Bank3, offset: 0xB0 */
  __I  uint32_t MULTI_ERR_DATA_LOW3;               /**< LOW 32 Bits Multiple Error Read Data On OCRAM Bank3, offset: 0xB4 */
  __I  uint32_t MULTI_ERR_DATA_HIGH3;              /**< HIGH 32 Bits Multiple Error Read Data On OCRAM Bank3, offset: 0xB8 */
       uint8_t RESERVED_0[68];
  __IO uint32_t PIPE_ECC_EN;                       /**< OCRAM Pipeline And ECC Enable, offset: 0x100 */
  __I  uint32_t PENDING_STAT;                      /**< Pending Status, offset: 0x104 */
} MECC_Type;

/* ----------------------------------------------------------------------------
   -- MECC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MECC_Register_Masks MECC Register Masks
 * @{
 */

/*! @name ERR_STATUS - Error Interrupt Status Register */
/*! @{ */

#define MECC_ERR_STATUS_SINGLE_ERR0_MASK         (0x1U)
#define MECC_ERR_STATUS_SINGLE_ERR0_SHIFT        (0U)
/*! SINGLE_ERR0 - Single Bit Error On OCRAM Bank0
 *  0b0..Single bit error does not happen on OCRAM bank0.
 *  0b1..Single bit error happens on OCRAM bank0.
 */
#define MECC_ERR_STATUS_SINGLE_ERR0(x)           (((uint32_t)(((uint32_t)(x)) << MECC_ERR_STATUS_SINGLE_ERR0_SHIFT)) & MECC_ERR_STATUS_SINGLE_ERR0_MASK)

#define MECC_ERR_STATUS_SINGLE_ERR1_MASK         (0x2U)
#define MECC_ERR_STATUS_SINGLE_ERR1_SHIFT        (1U)
/*! SINGLE_ERR1 - Single Bit Error On OCRAM Bank1
 *  0b0..Single bit error does not happen on OCRAM bank1.
 *  0b1..Single bit error happens on OCRAM bank1.
 */
#define MECC_ERR_STATUS_SINGLE_ERR1(x)           (((uint32_t)(((uint32_t)(x)) << MECC_ERR_STATUS_SINGLE_ERR1_SHIFT)) & MECC_ERR_STATUS_SINGLE_ERR1_MASK)

#define MECC_ERR_STATUS_SINGLE_ERR2_MASK         (0x4U)
#define MECC_ERR_STATUS_SINGLE_ERR2_SHIFT        (2U)
/*! SINGLE_ERR2 - Single Bit Error On OCRAM Bank2
 *  0b0..Single bit error does not happen on OCRAM bank2.
 *  0b1..Single bit error happens on OCRAM bank2.
 */
#define MECC_ERR_STATUS_SINGLE_ERR2(x)           (((uint32_t)(((uint32_t)(x)) << MECC_ERR_STATUS_SINGLE_ERR2_SHIFT)) & MECC_ERR_STATUS_SINGLE_ERR2_MASK)

#define MECC_ERR_STATUS_SINGLE_ERR3_MASK         (0x8U)
#define MECC_ERR_STATUS_SINGLE_ERR3_SHIFT        (3U)
/*! SINGLE_ERR3 - Single Bit Error On OCRAM Bank3
 *  0b0..Single bit error does not happen on OCRAM bank3.
 *  0b1..Single bit error happens on OCRAM bank3.
 */
#define MECC_ERR_STATUS_SINGLE_ERR3(x)           (((uint32_t)(((uint32_t)(x)) << MECC_ERR_STATUS_SINGLE_ERR3_SHIFT)) & MECC_ERR_STATUS_SINGLE_ERR3_MASK)

#define MECC_ERR_STATUS_MULTI_ERR0_MASK          (0x10U)
#define MECC_ERR_STATUS_MULTI_ERR0_SHIFT         (4U)
/*! MULTI_ERR0 - Multiple Bits Error On OCRAM Bank0
 *  0b0..Multiple bits error does not happen on OCRAM bank0.
 *  0b1..Multiple bits error happens on OCRAM bank0.
 */
#define MECC_ERR_STATUS_MULTI_ERR0(x)            (((uint32_t)(((uint32_t)(x)) << MECC_ERR_STATUS_MULTI_ERR0_SHIFT)) & MECC_ERR_STATUS_MULTI_ERR0_MASK)

#define MECC_ERR_STATUS_MULTI_ERR1_MASK          (0x20U)
#define MECC_ERR_STATUS_MULTI_ERR1_SHIFT         (5U)
/*! MULTI_ERR1 - Multiple Bits Error On OCRAM Bank1
 *  0b0..Multiple bits error does not happen on OCRAM bank1.
 *  0b1..Multiple bits error happens on OCRAM bank1.
 */
#define MECC_ERR_STATUS_MULTI_ERR1(x)            (((uint32_t)(((uint32_t)(x)) << MECC_ERR_STATUS_MULTI_ERR1_SHIFT)) & MECC_ERR_STATUS_MULTI_ERR1_MASK)

#define MECC_ERR_STATUS_MULTI_ERR2_MASK          (0x40U)
#define MECC_ERR_STATUS_MULTI_ERR2_SHIFT         (6U)
/*! MULTI_ERR2 - Multiple Bits Error On OCRAM Bank2
 *  0b0..Multiple bits error does not happen on OCRAM bank2.
 *  0b1..Multiple bits error happens on OCRAM bank2.
 */
#define MECC_ERR_STATUS_MULTI_ERR2(x)            (((uint32_t)(((uint32_t)(x)) << MECC_ERR_STATUS_MULTI_ERR2_SHIFT)) & MECC_ERR_STATUS_MULTI_ERR2_MASK)

#define MECC_ERR_STATUS_MULTI_ERR3_MASK          (0x80U)
#define MECC_ERR_STATUS_MULTI_ERR3_SHIFT         (7U)
/*! MULTI_ERR3 - Multiple Bits Error On OCRAM Bank3
 *  0b0..Multiple bits error does not happen on OCRAM bank3.
 *  0b1..Multiple bits error happens on OCRAM bank3.
 */
#define MECC_ERR_STATUS_MULTI_ERR3(x)            (((uint32_t)(((uint32_t)(x)) << MECC_ERR_STATUS_MULTI_ERR3_SHIFT)) & MECC_ERR_STATUS_MULTI_ERR3_MASK)

#define MECC_ERR_STATUS_STRB_ERR0_MASK           (0x100U)
#define MECC_ERR_STATUS_STRB_ERR0_SHIFT          (8U)
/*! STRB_ERR0 - AXI Strobe Error On OCRAM Bank0
 *  0b0..AXI strobe error does not happen on OCRAM bank0.
 *  0b1..AXI strobe error happens on OCRAM bank0.
 */
#define MECC_ERR_STATUS_STRB_ERR0(x)             (((uint32_t)(((uint32_t)(x)) << MECC_ERR_STATUS_STRB_ERR0_SHIFT)) & MECC_ERR_STATUS_STRB_ERR0_MASK)

#define MECC_ERR_STATUS_STRB_ERR1_MASK           (0x200U)
#define MECC_ERR_STATUS_STRB_ERR1_SHIFT          (9U)
/*! STRB_ERR1 - AXI Strobe Error On OCRAM Bank1
 *  0b0..AXI strobe error does not happen on OCRAM bank1.
 *  0b1..AXI strobe error happens on OCRAM bank1.
 */
#define MECC_ERR_STATUS_STRB_ERR1(x)             (((uint32_t)(((uint32_t)(x)) << MECC_ERR_STATUS_STRB_ERR1_SHIFT)) & MECC_ERR_STATUS_STRB_ERR1_MASK)

#define MECC_ERR_STATUS_STRB_ERR2_MASK           (0x400U)
#define MECC_ERR_STATUS_STRB_ERR2_SHIFT          (10U)
/*! STRB_ERR2 - AXI Strobe Error On OCRAM Bank2
 *  0b0..AXI strobe error does not happen on OCRAM bank2.
 *  0b1..AXI strobe error happens on OCRAM bank2.
 */
#define MECC_ERR_STATUS_STRB_ERR2(x)             (((uint32_t)(((uint32_t)(x)) << MECC_ERR_STATUS_STRB_ERR2_SHIFT)) & MECC_ERR_STATUS_STRB_ERR2_MASK)

#define MECC_ERR_STATUS_STRB_ERR3_MASK           (0x800U)
#define MECC_ERR_STATUS_STRB_ERR3_SHIFT          (11U)
/*! STRB_ERR3 - AXI Strobe Error On OCRAM Bank3
 *  0b0..AXI strobe error does not happen on OCRAM bank3.
 *  0b1..AXI strobe error happens on OCRAM bank3.
 */
#define MECC_ERR_STATUS_STRB_ERR3(x)             (((uint32_t)(((uint32_t)(x)) << MECC_ERR_STATUS_STRB_ERR3_SHIFT)) & MECC_ERR_STATUS_STRB_ERR3_MASK)

#define MECC_ERR_STATUS_ADDR_ERR0_MASK           (0x1000U)
#define MECC_ERR_STATUS_ADDR_ERR0_SHIFT          (12U)
/*! ADDR_ERR0 - OCRAM Access Error On Bank0
 *  0b0..OCRAM access error does not happen on OCRAM bank0.
 *  0b1..OCRAM access error happens on OCRAM bank0.
 */
#define MECC_ERR_STATUS_ADDR_ERR0(x)             (((uint32_t)(((uint32_t)(x)) << MECC_ERR_STATUS_ADDR_ERR0_SHIFT)) & MECC_ERR_STATUS_ADDR_ERR0_MASK)

#define MECC_ERR_STATUS_ADDR_ERR1_MASK           (0x2000U)
#define MECC_ERR_STATUS_ADDR_ERR1_SHIFT          (13U)
/*! ADDR_ERR1 - OCRAM Access Error On Bank1
 *  0b0..OCRAM access error does not happen on OCRAM bank1.
 *  0b1..OCRAM access error happens on OCRAM bank1.
 */
#define MECC_ERR_STATUS_ADDR_ERR1(x)             (((uint32_t)(((uint32_t)(x)) << MECC_ERR_STATUS_ADDR_ERR1_SHIFT)) & MECC_ERR_STATUS_ADDR_ERR1_MASK)

#define MECC_ERR_STATUS_ADDR_ERR2_MASK           (0x4000U)
#define MECC_ERR_STATUS_ADDR_ERR2_SHIFT          (14U)
/*! ADDR_ERR2 - OCRAM Access Error On Bank2
 *  0b0..OCRAM access error does not happen on OCRAM bank2.
 *  0b1..OCRAM access error happens on OCRAM bank2.
 */
#define MECC_ERR_STATUS_ADDR_ERR2(x)             (((uint32_t)(((uint32_t)(x)) << MECC_ERR_STATUS_ADDR_ERR2_SHIFT)) & MECC_ERR_STATUS_ADDR_ERR2_MASK)

#define MECC_ERR_STATUS_ADDR_ERR3_MASK           (0x8000U)
#define MECC_ERR_STATUS_ADDR_ERR3_SHIFT          (15U)
/*! ADDR_ERR3 - OCRAM Access Error On Bank3
 *  0b0..OCRAM access error does not happen on OCRAM bank3.
 *  0b1..OCRAM access error happens on OCRAM bank3.
 */
#define MECC_ERR_STATUS_ADDR_ERR3(x)             (((uint32_t)(((uint32_t)(x)) << MECC_ERR_STATUS_ADDR_ERR3_SHIFT)) & MECC_ERR_STATUS_ADDR_ERR3_MASK)
/*! @} */

/*! @name ERR_STAT_EN - Error Interrupt Status Enable Register */
/*! @{ */

#define MECC_ERR_STAT_EN_SINGLE_ERR0_STAT_EN_MASK (0x1U)
#define MECC_ERR_STAT_EN_SINGLE_ERR0_STAT_EN_SHIFT (0U)
/*! SINGLE_ERR0_STAT_EN - Single Bit Error Status Enable On OCRAM Bank0
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define MECC_ERR_STAT_EN_SINGLE_ERR0_STAT_EN(x)  (((uint32_t)(((uint32_t)(x)) << MECC_ERR_STAT_EN_SINGLE_ERR0_STAT_EN_SHIFT)) & MECC_ERR_STAT_EN_SINGLE_ERR0_STAT_EN_MASK)

#define MECC_ERR_STAT_EN_SINGLE_ERR1_STAT_EN_MASK (0x2U)
#define MECC_ERR_STAT_EN_SINGLE_ERR1_STAT_EN_SHIFT (1U)
/*! SINGLE_ERR1_STAT_EN - Single Bit Error Status Enable On OCRAM Bank1
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define MECC_ERR_STAT_EN_SINGLE_ERR1_STAT_EN(x)  (((uint32_t)(((uint32_t)(x)) << MECC_ERR_STAT_EN_SINGLE_ERR1_STAT_EN_SHIFT)) & MECC_ERR_STAT_EN_SINGLE_ERR1_STAT_EN_MASK)

#define MECC_ERR_STAT_EN_SINGLE_ERR2_STAT_EN_MASK (0x4U)
#define MECC_ERR_STAT_EN_SINGLE_ERR2_STAT_EN_SHIFT (2U)
/*! SINGLE_ERR2_STAT_EN - Single Bit Error Status Enable On OCRAM Bank2
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define MECC_ERR_STAT_EN_SINGLE_ERR2_STAT_EN(x)  (((uint32_t)(((uint32_t)(x)) << MECC_ERR_STAT_EN_SINGLE_ERR2_STAT_EN_SHIFT)) & MECC_ERR_STAT_EN_SINGLE_ERR2_STAT_EN_MASK)

#define MECC_ERR_STAT_EN_SINGLE_ERR3_STAT_EN_MASK (0x8U)
#define MECC_ERR_STAT_EN_SINGLE_ERR3_STAT_EN_SHIFT (3U)
/*! SINGLE_ERR3_STAT_EN - Single Bit Error Status Enable On OCRAM Bank3
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define MECC_ERR_STAT_EN_SINGLE_ERR3_STAT_EN(x)  (((uint32_t)(((uint32_t)(x)) << MECC_ERR_STAT_EN_SINGLE_ERR3_STAT_EN_SHIFT)) & MECC_ERR_STAT_EN_SINGLE_ERR3_STAT_EN_MASK)

#define MECC_ERR_STAT_EN_MULTI_ERR0_STAT_EN_MASK (0x10U)
#define MECC_ERR_STAT_EN_MULTI_ERR0_STAT_EN_SHIFT (4U)
/*! MULTI_ERR0_STAT_EN - Multiple Bits Error Status Enable On OCRAM Bank0
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define MECC_ERR_STAT_EN_MULTI_ERR0_STAT_EN(x)   (((uint32_t)(((uint32_t)(x)) << MECC_ERR_STAT_EN_MULTI_ERR0_STAT_EN_SHIFT)) & MECC_ERR_STAT_EN_MULTI_ERR0_STAT_EN_MASK)

#define MECC_ERR_STAT_EN_MULTI_ERR1_STAT_EN_MASK (0x20U)
#define MECC_ERR_STAT_EN_MULTI_ERR1_STAT_EN_SHIFT (5U)
/*! MULTI_ERR1_STAT_EN - Multiple Bits Error Status Enable On OCRAM Bank1
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define MECC_ERR_STAT_EN_MULTI_ERR1_STAT_EN(x)   (((uint32_t)(((uint32_t)(x)) << MECC_ERR_STAT_EN_MULTI_ERR1_STAT_EN_SHIFT)) & MECC_ERR_STAT_EN_MULTI_ERR1_STAT_EN_MASK)

#define MECC_ERR_STAT_EN_MULTI_ERR2_STAT_EN_MASK (0x40U)
#define MECC_ERR_STAT_EN_MULTI_ERR2_STAT_EN_SHIFT (6U)
/*! MULTI_ERR2_STAT_EN - Multiple Bits Error Status Enable On OCRAM Bank2
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define MECC_ERR_STAT_EN_MULTI_ERR2_STAT_EN(x)   (((uint32_t)(((uint32_t)(x)) << MECC_ERR_STAT_EN_MULTI_ERR2_STAT_EN_SHIFT)) & MECC_ERR_STAT_EN_MULTI_ERR2_STAT_EN_MASK)

#define MECC_ERR_STAT_EN_MULTI_ERR3_STAT_EN_MASK (0x80U)
#define MECC_ERR_STAT_EN_MULTI_ERR3_STAT_EN_SHIFT (7U)
/*! MULTI_ERR3_STAT_EN - Multiple Bits Error Status Enable On OCRAM Bank3
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define MECC_ERR_STAT_EN_MULTI_ERR3_STAT_EN(x)   (((uint32_t)(((uint32_t)(x)) << MECC_ERR_STAT_EN_MULTI_ERR3_STAT_EN_SHIFT)) & MECC_ERR_STAT_EN_MULTI_ERR3_STAT_EN_MASK)

#define MECC_ERR_STAT_EN_STRB_ERR0_STAT_EN_MASK  (0x100U)
#define MECC_ERR_STAT_EN_STRB_ERR0_STAT_EN_SHIFT (8U)
/*! STRB_ERR0_STAT_EN - AXI Strobe Error Status Enable On OCRAM Bank0
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define MECC_ERR_STAT_EN_STRB_ERR0_STAT_EN(x)    (((uint32_t)(((uint32_t)(x)) << MECC_ERR_STAT_EN_STRB_ERR0_STAT_EN_SHIFT)) & MECC_ERR_STAT_EN_STRB_ERR0_STAT_EN_MASK)

#define MECC_ERR_STAT_EN_STRB_ERR1_STAT_EN_MASK  (0x200U)
#define MECC_ERR_STAT_EN_STRB_ERR1_STAT_EN_SHIFT (9U)
/*! STRB_ERR1_STAT_EN - AXI Strobe Error Status Enable On OCRAM Bank1
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define MECC_ERR_STAT_EN_STRB_ERR1_STAT_EN(x)    (((uint32_t)(((uint32_t)(x)) << MECC_ERR_STAT_EN_STRB_ERR1_STAT_EN_SHIFT)) & MECC_ERR_STAT_EN_STRB_ERR1_STAT_EN_MASK)

#define MECC_ERR_STAT_EN_STRB_ERR2_STAT_EN_MASK  (0x400U)
#define MECC_ERR_STAT_EN_STRB_ERR2_STAT_EN_SHIFT (10U)
/*! STRB_ERR2_STAT_EN - AXI Strobe Error Status Enable On OCRAM Bank2
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define MECC_ERR_STAT_EN_STRB_ERR2_STAT_EN(x)    (((uint32_t)(((uint32_t)(x)) << MECC_ERR_STAT_EN_STRB_ERR2_STAT_EN_SHIFT)) & MECC_ERR_STAT_EN_STRB_ERR2_STAT_EN_MASK)

#define MECC_ERR_STAT_EN_STRB_ERR3_STAT_EN_MASK  (0x800U)
#define MECC_ERR_STAT_EN_STRB_ERR3_STAT_EN_SHIFT (11U)
/*! STRB_ERR3_STAT_EN - AXI Strobe Error Status Enable On OCRAM Bank3
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define MECC_ERR_STAT_EN_STRB_ERR3_STAT_EN(x)    (((uint32_t)(((uint32_t)(x)) << MECC_ERR_STAT_EN_STRB_ERR3_STAT_EN_SHIFT)) & MECC_ERR_STAT_EN_STRB_ERR3_STAT_EN_MASK)

#define MECC_ERR_STAT_EN_ADDR_ERR0_STAT_EN_MASK  (0x1000U)
#define MECC_ERR_STAT_EN_ADDR_ERR0_STAT_EN_SHIFT (12U)
/*! ADDR_ERR0_STAT_EN - OCRAM Access Error Status Enable On Bank0
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define MECC_ERR_STAT_EN_ADDR_ERR0_STAT_EN(x)    (((uint32_t)(((uint32_t)(x)) << MECC_ERR_STAT_EN_ADDR_ERR0_STAT_EN_SHIFT)) & MECC_ERR_STAT_EN_ADDR_ERR0_STAT_EN_MASK)

#define MECC_ERR_STAT_EN_ADDR_ERR1_STAT_EN_MASK  (0x2000U)
#define MECC_ERR_STAT_EN_ADDR_ERR1_STAT_EN_SHIFT (13U)
/*! ADDR_ERR1_STAT_EN - OCRAM Access Error Status Enable On Bank1
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define MECC_ERR_STAT_EN_ADDR_ERR1_STAT_EN(x)    (((uint32_t)(((uint32_t)(x)) << MECC_ERR_STAT_EN_ADDR_ERR1_STAT_EN_SHIFT)) & MECC_ERR_STAT_EN_ADDR_ERR1_STAT_EN_MASK)

#define MECC_ERR_STAT_EN_ADDR_ERR2_STAT_EN_MASK  (0x4000U)
#define MECC_ERR_STAT_EN_ADDR_ERR2_STAT_EN_SHIFT (14U)
/*! ADDR_ERR2_STAT_EN - OCRAM Access Error Status Enable On Bank2
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define MECC_ERR_STAT_EN_ADDR_ERR2_STAT_EN(x)    (((uint32_t)(((uint32_t)(x)) << MECC_ERR_STAT_EN_ADDR_ERR2_STAT_EN_SHIFT)) & MECC_ERR_STAT_EN_ADDR_ERR2_STAT_EN_MASK)

#define MECC_ERR_STAT_EN_ADDR_ERR3_STAT_EN_MASK  (0x8000U)
#define MECC_ERR_STAT_EN_ADDR_ERR3_STAT_EN_SHIFT (15U)
/*! ADDR_ERR3_STAT_EN - OCRAM Access Error Status Enable On Bank3
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define MECC_ERR_STAT_EN_ADDR_ERR3_STAT_EN(x)    (((uint32_t)(((uint32_t)(x)) << MECC_ERR_STAT_EN_ADDR_ERR3_STAT_EN_SHIFT)) & MECC_ERR_STAT_EN_ADDR_ERR3_STAT_EN_MASK)
/*! @} */

/*! @name ERR_SIG_EN - Error Interrupt Enable Register */
/*! @{ */

#define MECC_ERR_SIG_EN_SINGLE_ERR0_SIG_EN_MASK  (0x1U)
#define MECC_ERR_SIG_EN_SINGLE_ERR0_SIG_EN_SHIFT (0U)
/*! SINGLE_ERR0_SIG_EN - Single Bit Error Interrupt Enable On OCRAM Bank0
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define MECC_ERR_SIG_EN_SINGLE_ERR0_SIG_EN(x)    (((uint32_t)(((uint32_t)(x)) << MECC_ERR_SIG_EN_SINGLE_ERR0_SIG_EN_SHIFT)) & MECC_ERR_SIG_EN_SINGLE_ERR0_SIG_EN_MASK)

#define MECC_ERR_SIG_EN_SINGLE_ERR1_SIG_EN_MASK  (0x2U)
#define MECC_ERR_SIG_EN_SINGLE_ERR1_SIG_EN_SHIFT (1U)
/*! SINGLE_ERR1_SIG_EN - Single Bit Error Interrupt Enable On OCRAM Bank1
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define MECC_ERR_SIG_EN_SINGLE_ERR1_SIG_EN(x)    (((uint32_t)(((uint32_t)(x)) << MECC_ERR_SIG_EN_SINGLE_ERR1_SIG_EN_SHIFT)) & MECC_ERR_SIG_EN_SINGLE_ERR1_SIG_EN_MASK)

#define MECC_ERR_SIG_EN_SINGLE_ERR2_SIG_EN_MASK  (0x4U)
#define MECC_ERR_SIG_EN_SINGLE_ERR2_SIG_EN_SHIFT (2U)
/*! SINGLE_ERR2_SIG_EN - Single Bit Error Interrupt Enable On OCRAM Bank2
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define MECC_ERR_SIG_EN_SINGLE_ERR2_SIG_EN(x)    (((uint32_t)(((uint32_t)(x)) << MECC_ERR_SIG_EN_SINGLE_ERR2_SIG_EN_SHIFT)) & MECC_ERR_SIG_EN_SINGLE_ERR2_SIG_EN_MASK)

#define MECC_ERR_SIG_EN_SINGLE_ERR3_SIG_EN_MASK  (0x8U)
#define MECC_ERR_SIG_EN_SINGLE_ERR3_SIG_EN_SHIFT (3U)
/*! SINGLE_ERR3_SIG_EN - Single Bit Error Interrupt Enable On OCRAM Bank3
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define MECC_ERR_SIG_EN_SINGLE_ERR3_SIG_EN(x)    (((uint32_t)(((uint32_t)(x)) << MECC_ERR_SIG_EN_SINGLE_ERR3_SIG_EN_SHIFT)) & MECC_ERR_SIG_EN_SINGLE_ERR3_SIG_EN_MASK)

#define MECC_ERR_SIG_EN_MULTI_ERR0_SIG_EN_MASK   (0x10U)
#define MECC_ERR_SIG_EN_MULTI_ERR0_SIG_EN_SHIFT  (4U)
/*! MULTI_ERR0_SIG_EN - Multiple Bits Error Interrupt Enable On OCRAM Bank0
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define MECC_ERR_SIG_EN_MULTI_ERR0_SIG_EN(x)     (((uint32_t)(((uint32_t)(x)) << MECC_ERR_SIG_EN_MULTI_ERR0_SIG_EN_SHIFT)) & MECC_ERR_SIG_EN_MULTI_ERR0_SIG_EN_MASK)

#define MECC_ERR_SIG_EN_MULTI_ERR1_SIG_EN_MASK   (0x20U)
#define MECC_ERR_SIG_EN_MULTI_ERR1_SIG_EN_SHIFT  (5U)
/*! MULTI_ERR1_SIG_EN - Multiple Bits Error Interrupt Enable On OCRAM Bank1
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define MECC_ERR_SIG_EN_MULTI_ERR1_SIG_EN(x)     (((uint32_t)(((uint32_t)(x)) << MECC_ERR_SIG_EN_MULTI_ERR1_SIG_EN_SHIFT)) & MECC_ERR_SIG_EN_MULTI_ERR1_SIG_EN_MASK)

#define MECC_ERR_SIG_EN_MULTI_ERR2_SIG_EN_MASK   (0x40U)
#define MECC_ERR_SIG_EN_MULTI_ERR2_SIG_EN_SHIFT  (6U)
/*! MULTI_ERR2_SIG_EN - Multiple Bits Error Interrupt Enable On OCRAM Bank2
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define MECC_ERR_SIG_EN_MULTI_ERR2_SIG_EN(x)     (((uint32_t)(((uint32_t)(x)) << MECC_ERR_SIG_EN_MULTI_ERR2_SIG_EN_SHIFT)) & MECC_ERR_SIG_EN_MULTI_ERR2_SIG_EN_MASK)

#define MECC_ERR_SIG_EN_MULTI_ERR3_SIG_EN_MASK   (0x80U)
#define MECC_ERR_SIG_EN_MULTI_ERR3_SIG_EN_SHIFT  (7U)
/*! MULTI_ERR3_SIG_EN - Multiple Bits Error Interrupt Enable On OCRAM Bank3
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define MECC_ERR_SIG_EN_MULTI_ERR3_SIG_EN(x)     (((uint32_t)(((uint32_t)(x)) << MECC_ERR_SIG_EN_MULTI_ERR3_SIG_EN_SHIFT)) & MECC_ERR_SIG_EN_MULTI_ERR3_SIG_EN_MASK)

#define MECC_ERR_SIG_EN_STRB_ERR0_SIG_EN_MASK    (0x100U)
#define MECC_ERR_SIG_EN_STRB_ERR0_SIG_EN_SHIFT   (8U)
/*! STRB_ERR0_SIG_EN - AXI Strobe Error Interrupt Enable On OCRAM Bank0
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define MECC_ERR_SIG_EN_STRB_ERR0_SIG_EN(x)      (((uint32_t)(((uint32_t)(x)) << MECC_ERR_SIG_EN_STRB_ERR0_SIG_EN_SHIFT)) & MECC_ERR_SIG_EN_STRB_ERR0_SIG_EN_MASK)

#define MECC_ERR_SIG_EN_STRB_ERR1_SIG_EN_MASK    (0x200U)
#define MECC_ERR_SIG_EN_STRB_ERR1_SIG_EN_SHIFT   (9U)
/*! STRB_ERR1_SIG_EN - AXI Strobe Error Interrupt Enable On OCRAM Bank1
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define MECC_ERR_SIG_EN_STRB_ERR1_SIG_EN(x)      (((uint32_t)(((uint32_t)(x)) << MECC_ERR_SIG_EN_STRB_ERR1_SIG_EN_SHIFT)) & MECC_ERR_SIG_EN_STRB_ERR1_SIG_EN_MASK)

#define MECC_ERR_SIG_EN_STRB_ERR2_SIG_EN_MASK    (0x400U)
#define MECC_ERR_SIG_EN_STRB_ERR2_SIG_EN_SHIFT   (10U)
/*! STRB_ERR2_SIG_EN - AXI Strobe Error Interrupt Enable On OCRAM Bank2
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define MECC_ERR_SIG_EN_STRB_ERR2_SIG_EN(x)      (((uint32_t)(((uint32_t)(x)) << MECC_ERR_SIG_EN_STRB_ERR2_SIG_EN_SHIFT)) & MECC_ERR_SIG_EN_STRB_ERR2_SIG_EN_MASK)

#define MECC_ERR_SIG_EN_STRB_ERR3_SIG_EN_MASK    (0x800U)
#define MECC_ERR_SIG_EN_STRB_ERR3_SIG_EN_SHIFT   (11U)
/*! STRB_ERR3_SIG_EN - AXI Strobe Error Interrupt Enable On OCRAM Bank3
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define MECC_ERR_SIG_EN_STRB_ERR3_SIG_EN(x)      (((uint32_t)(((uint32_t)(x)) << MECC_ERR_SIG_EN_STRB_ERR3_SIG_EN_SHIFT)) & MECC_ERR_SIG_EN_STRB_ERR3_SIG_EN_MASK)

#define MECC_ERR_SIG_EN_ADDR_ERR0_SIG_EN_MASK    (0x1000U)
#define MECC_ERR_SIG_EN_ADDR_ERR0_SIG_EN_SHIFT   (12U)
/*! ADDR_ERR0_SIG_EN - OCRAM Access Error Interrupt Enable On Bank0
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define MECC_ERR_SIG_EN_ADDR_ERR0_SIG_EN(x)      (((uint32_t)(((uint32_t)(x)) << MECC_ERR_SIG_EN_ADDR_ERR0_SIG_EN_SHIFT)) & MECC_ERR_SIG_EN_ADDR_ERR0_SIG_EN_MASK)

#define MECC_ERR_SIG_EN_ADDR_ERR1_SIG_EN_MASK    (0x2000U)
#define MECC_ERR_SIG_EN_ADDR_ERR1_SIG_EN_SHIFT   (13U)
/*! ADDR_ERR1_SIG_EN - OCRAM Access Error Interrupt Enable On Bank1
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define MECC_ERR_SIG_EN_ADDR_ERR1_SIG_EN(x)      (((uint32_t)(((uint32_t)(x)) << MECC_ERR_SIG_EN_ADDR_ERR1_SIG_EN_SHIFT)) & MECC_ERR_SIG_EN_ADDR_ERR1_SIG_EN_MASK)

#define MECC_ERR_SIG_EN_ADDR_ERR2_SIG_EN_MASK    (0x4000U)
#define MECC_ERR_SIG_EN_ADDR_ERR2_SIG_EN_SHIFT   (14U)
/*! ADDR_ERR2_SIG_EN - OCRAM Access Error Interrupt Enable On Bank2
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define MECC_ERR_SIG_EN_ADDR_ERR2_SIG_EN(x)      (((uint32_t)(((uint32_t)(x)) << MECC_ERR_SIG_EN_ADDR_ERR2_SIG_EN_SHIFT)) & MECC_ERR_SIG_EN_ADDR_ERR2_SIG_EN_MASK)

#define MECC_ERR_SIG_EN_ADDR_ERR3_SIG_EN_MASK    (0x8000U)
#define MECC_ERR_SIG_EN_ADDR_ERR3_SIG_EN_SHIFT   (15U)
/*! ADDR_ERR3_SIG_EN - OCRAM Access Error Interrupt Enable On Bank3
 *  0b0..Disabled
 *  0b1..Enabled
 */
#define MECC_ERR_SIG_EN_ADDR_ERR3_SIG_EN(x)      (((uint32_t)(((uint32_t)(x)) << MECC_ERR_SIG_EN_ADDR_ERR3_SIG_EN_SHIFT)) & MECC_ERR_SIG_EN_ADDR_ERR3_SIG_EN_MASK)
/*! @} */

/*! @name ERR_DATA_INJ_LOW0 - Error Injection On LOW 32 bits Of OCRAM Bank0 Write Data */
/*! @{ */

#define MECC_ERR_DATA_INJ_LOW0_ERR_DATA_INJ_MASK (0xFFFFFFFFU)
#define MECC_ERR_DATA_INJ_LOW0_ERR_DATA_INJ_SHIFT (0U)
/*! ERR_DATA_INJ - Error Injection On LOW 32 bits Of OCRAM Bank0 Write Data */
#define MECC_ERR_DATA_INJ_LOW0_ERR_DATA_INJ(x)   (((uint32_t)(((uint32_t)(x)) << MECC_ERR_DATA_INJ_LOW0_ERR_DATA_INJ_SHIFT)) & MECC_ERR_DATA_INJ_LOW0_ERR_DATA_INJ_MASK)
/*! @} */

/*! @name ERR_DATA_INJ_HIGH0 - Error Injection On HIGH 32 bits Of OCRAM Bank0 Write Data */
/*! @{ */

#define MECC_ERR_DATA_INJ_HIGH0_ERR_DATA_INJ_MASK (0xFFFFFFFFU)
#define MECC_ERR_DATA_INJ_HIGH0_ERR_DATA_INJ_SHIFT (0U)
/*! ERR_DATA_INJ - Error Injection On HIGH 32 bits Of OCRAM Bank0 Write Data */
#define MECC_ERR_DATA_INJ_HIGH0_ERR_DATA_INJ(x)  (((uint32_t)(((uint32_t)(x)) << MECC_ERR_DATA_INJ_HIGH0_ERR_DATA_INJ_SHIFT)) & MECC_ERR_DATA_INJ_HIGH0_ERR_DATA_INJ_MASK)
/*! @} */

/*! @name ERR_ECC_INJ0 - Error Injection On 8 bits ECC code Of OCRAM Bank0 Write Data */
/*! @{ */

#define MECC_ERR_ECC_INJ0_ERR_ECC_INJ_MASK       (0xFFU)
#define MECC_ERR_ECC_INJ0_ERR_ECC_INJ_SHIFT      (0U)
/*! ERR_ECC_INJ - Error Injection On 8 bits ECC code Of OCRAM Bank0 Write Data */
#define MECC_ERR_ECC_INJ0_ERR_ECC_INJ(x)         (((uint32_t)(((uint32_t)(x)) << MECC_ERR_ECC_INJ0_ERR_ECC_INJ_SHIFT)) & MECC_ERR_ECC_INJ0_ERR_ECC_INJ_MASK)
/*! @} */

/*! @name ERR_DATA_INJ_LOW1 - Error Injection On LOW 32 bits Of OCRAM Bank1 Write Data */
/*! @{ */

#define MECC_ERR_DATA_INJ_LOW1_ERR_DATA_INJ_MASK (0xFFFFFFFFU)
#define MECC_ERR_DATA_INJ_LOW1_ERR_DATA_INJ_SHIFT (0U)
/*! ERR_DATA_INJ - Error Injection On LOW 32 bits Of OCRAM Bank1 Write Data */
#define MECC_ERR_DATA_INJ_LOW1_ERR_DATA_INJ(x)   (((uint32_t)(((uint32_t)(x)) << MECC_ERR_DATA_INJ_LOW1_ERR_DATA_INJ_SHIFT)) & MECC_ERR_DATA_INJ_LOW1_ERR_DATA_INJ_MASK)
/*! @} */

/*! @name ERR_DATA_INJ_HIGH1 - Error Injection On HIGH 32 bits Of OCRAM Bank1 Write Data */
/*! @{ */

#define MECC_ERR_DATA_INJ_HIGH1_ERR_DATA_INJ_MASK (0xFFFFFFFFU)
#define MECC_ERR_DATA_INJ_HIGH1_ERR_DATA_INJ_SHIFT (0U)
/*! ERR_DATA_INJ - Error Injection On HIGH 32 bits Of OCRAM Bank1 Write Data */
#define MECC_ERR_DATA_INJ_HIGH1_ERR_DATA_INJ(x)  (((uint32_t)(((uint32_t)(x)) << MECC_ERR_DATA_INJ_HIGH1_ERR_DATA_INJ_SHIFT)) & MECC_ERR_DATA_INJ_HIGH1_ERR_DATA_INJ_MASK)
/*! @} */

/*! @name ERR_ECC_INJ1 - Error Injection On 8 bits ECC code Of OCRAM Bank1 Write Data */
/*! @{ */

#define MECC_ERR_ECC_INJ1_ERR_ECC_INJ_MASK       (0xFFU)
#define MECC_ERR_ECC_INJ1_ERR_ECC_INJ_SHIFT      (0U)
/*! ERR_ECC_INJ - Error Injection On 8 bits ECC code Of OCRAM Bank1 Write Data */
#define MECC_ERR_ECC_INJ1_ERR_ECC_INJ(x)         (((uint32_t)(((uint32_t)(x)) << MECC_ERR_ECC_INJ1_ERR_ECC_INJ_SHIFT)) & MECC_ERR_ECC_INJ1_ERR_ECC_INJ_MASK)
/*! @} */

/*! @name ERR_DATA_INJ_LOW2 - Error Injection On LOW 32 bits Of OCRAM Bank2 Write Data */
/*! @{ */

#define MECC_ERR_DATA_INJ_LOW2_ERR_DATA_INJ_MASK (0xFFFFFFFFU)
#define MECC_ERR_DATA_INJ_LOW2_ERR_DATA_INJ_SHIFT (0U)
/*! ERR_DATA_INJ - Error Injection On LOW 32 bits Of OCRAM Bank2 Write Data */
#define MECC_ERR_DATA_INJ_LOW2_ERR_DATA_INJ(x)   (((uint32_t)(((uint32_t)(x)) << MECC_ERR_DATA_INJ_LOW2_ERR_DATA_INJ_SHIFT)) & MECC_ERR_DATA_INJ_LOW2_ERR_DATA_INJ_MASK)
/*! @} */

/*! @name ERR_DATA_INJ_HIGH2 - Error Injection On HIGH 32 bits Of OCRAM Bank2 Write Data */
/*! @{ */

#define MECC_ERR_DATA_INJ_HIGH2_ERR_DATA_INJ_MASK (0xFFFFFFFFU)
#define MECC_ERR_DATA_INJ_HIGH2_ERR_DATA_INJ_SHIFT (0U)
/*! ERR_DATA_INJ - Error Injection On HIGH 32 bits Of OCRAM Bank2 Write Data */
#define MECC_ERR_DATA_INJ_HIGH2_ERR_DATA_INJ(x)  (((uint32_t)(((uint32_t)(x)) << MECC_ERR_DATA_INJ_HIGH2_ERR_DATA_INJ_SHIFT)) & MECC_ERR_DATA_INJ_HIGH2_ERR_DATA_INJ_MASK)
/*! @} */

/*! @name ERR_ECC_INJ2 - Error Injection On 8 bits ECC code Of OCRAM Bank2 Write Data */
/*! @{ */

#define MECC_ERR_ECC_INJ2_ERR_ECC_INJ_MASK       (0xFFU)
#define MECC_ERR_ECC_INJ2_ERR_ECC_INJ_SHIFT      (0U)
/*! ERR_ECC_INJ - Error Injection On 8 bits ECC code Of OCRAM Bank2 Write Data */
#define MECC_ERR_ECC_INJ2_ERR_ECC_INJ(x)         (((uint32_t)(((uint32_t)(x)) << MECC_ERR_ECC_INJ2_ERR_ECC_INJ_SHIFT)) & MECC_ERR_ECC_INJ2_ERR_ECC_INJ_MASK)
/*! @} */

/*! @name ERR_DATA_INJ_LOW3 - Error Injection On LOW 32 bits Of OCRAM Bank3 Write Data */
/*! @{ */

#define MECC_ERR_DATA_INJ_LOW3_ERR_DATA_INJ_MASK (0xFFFFFFFFU)
#define MECC_ERR_DATA_INJ_LOW3_ERR_DATA_INJ_SHIFT (0U)
/*! ERR_DATA_INJ - Error Injection On LOW 32 bits Of OCRAM Bank3 Write Data */
#define MECC_ERR_DATA_INJ_LOW3_ERR_DATA_INJ(x)   (((uint32_t)(((uint32_t)(x)) << MECC_ERR_DATA_INJ_LOW3_ERR_DATA_INJ_SHIFT)) & MECC_ERR_DATA_INJ_LOW3_ERR_DATA_INJ_MASK)
/*! @} */

/*! @name ERR_DATA_INJ_HIGH3 - Error Injection On HIGH 32 bits Of OCRAM Bank3 Write Data */
/*! @{ */

#define MECC_ERR_DATA_INJ_HIGH3_ERR_DATA_INJ_MASK (0xFFFFFFFFU)
#define MECC_ERR_DATA_INJ_HIGH3_ERR_DATA_INJ_SHIFT (0U)
/*! ERR_DATA_INJ - Error Injection On HIGH 32 bits Of OCRAM Bank3 Write Data */
#define MECC_ERR_DATA_INJ_HIGH3_ERR_DATA_INJ(x)  (((uint32_t)(((uint32_t)(x)) << MECC_ERR_DATA_INJ_HIGH3_ERR_DATA_INJ_SHIFT)) & MECC_ERR_DATA_INJ_HIGH3_ERR_DATA_INJ_MASK)
/*! @} */

/*! @name ERR_ECC_INJ3 - Error Injection On 8 bits ECC code Of OCRAM Bank3 Write Data */
/*! @{ */

#define MECC_ERR_ECC_INJ3_ERR_ECC_INJ_MASK       (0xFFU)
#define MECC_ERR_ECC_INJ3_ERR_ECC_INJ_SHIFT      (0U)
/*! ERR_ECC_INJ - Error Injection On 8 bits ECC code Of OCRAM Bank3 Write Data */
#define MECC_ERR_ECC_INJ3_ERR_ECC_INJ(x)         (((uint32_t)(((uint32_t)(x)) << MECC_ERR_ECC_INJ3_ERR_ECC_INJ_SHIFT)) & MECC_ERR_ECC_INJ3_ERR_ECC_INJ_MASK)
/*! @} */

/*! @name SINGLE_ERR_ADDR_ECC0 - Single Error Address And ECC code On OCRAM Bank0 */
/*! @{ */

#define MECC_SINGLE_ERR_ADDR_ECC0_SINGLE_ERR_ECC_MASK (0xFFU)
#define MECC_SINGLE_ERR_ADDR_ECC0_SINGLE_ERR_ECC_SHIFT (0U)
/*! SINGLE_ERR_ECC - Single Error ECC code On OCRAM Bank0 */
#define MECC_SINGLE_ERR_ADDR_ECC0_SINGLE_ERR_ECC(x) (((uint32_t)(((uint32_t)(x)) << MECC_SINGLE_ERR_ADDR_ECC0_SINGLE_ERR_ECC_SHIFT)) & MECC_SINGLE_ERR_ADDR_ECC0_SINGLE_ERR_ECC_MASK)

#define MECC_SINGLE_ERR_ADDR_ECC0_SINGLE_ERR_ADDR_MASK (0x7FFFF00U)
#define MECC_SINGLE_ERR_ADDR_ECC0_SINGLE_ERR_ADDR_SHIFT (8U)
/*! SINGLE_ERR_ADDR - Single Error Address On OCRAM Bank0 */
#define MECC_SINGLE_ERR_ADDR_ECC0_SINGLE_ERR_ADDR(x) (((uint32_t)(((uint32_t)(x)) << MECC_SINGLE_ERR_ADDR_ECC0_SINGLE_ERR_ADDR_SHIFT)) & MECC_SINGLE_ERR_ADDR_ECC0_SINGLE_ERR_ADDR_MASK)
/*! @} */

/*! @name SINGLE_ERR_DATA_LOW0 - LOW 32 Bits Single Error Read Data On OCRAM Bank0 */
/*! @{ */

#define MECC_SINGLE_ERR_DATA_LOW0_SINGLE_ERR_DATA_MASK (0xFFFFFFFFU)
#define MECC_SINGLE_ERR_DATA_LOW0_SINGLE_ERR_DATA_SHIFT (0U)
/*! SINGLE_ERR_DATA - LOW 32 Bits Single Error Read Data On OCRAM Bank0 */
#define MECC_SINGLE_ERR_DATA_LOW0_SINGLE_ERR_DATA(x) (((uint32_t)(((uint32_t)(x)) << MECC_SINGLE_ERR_DATA_LOW0_SINGLE_ERR_DATA_SHIFT)) & MECC_SINGLE_ERR_DATA_LOW0_SINGLE_ERR_DATA_MASK)
/*! @} */

/*! @name SINGLE_ERR_DATA_HIGH0 - HIGH 32 Bits Single Error Read Data On OCRAM Bank0 */
/*! @{ */

#define MECC_SINGLE_ERR_DATA_HIGH0_SINGLE_ERR_DATA_MASK (0xFFFFFFFFU)
#define MECC_SINGLE_ERR_DATA_HIGH0_SINGLE_ERR_DATA_SHIFT (0U)
/*! SINGLE_ERR_DATA - HIGH 32 Bits Single Error Read Data On OCRAM Bank0 */
#define MECC_SINGLE_ERR_DATA_HIGH0_SINGLE_ERR_DATA(x) (((uint32_t)(((uint32_t)(x)) << MECC_SINGLE_ERR_DATA_HIGH0_SINGLE_ERR_DATA_SHIFT)) & MECC_SINGLE_ERR_DATA_HIGH0_SINGLE_ERR_DATA_MASK)
/*! @} */

/*! @name SINGLE_ERR_POS_LOW0 - LOW Single Error Bit Position On OCRAM Bank0 */
/*! @{ */

#define MECC_SINGLE_ERR_POS_LOW0_SINGLE_ERR_POS_MASK (0xFFFFFFFFU)
#define MECC_SINGLE_ERR_POS_LOW0_SINGLE_ERR_POS_SHIFT (0U)
/*! SINGLE_ERR_POS - LOW Single Error Bit Position On OCRAM Bank0 */
#define MECC_SINGLE_ERR_POS_LOW0_SINGLE_ERR_POS(x) (((uint32_t)(((uint32_t)(x)) << MECC_SINGLE_ERR_POS_LOW0_SINGLE_ERR_POS_SHIFT)) & MECC_SINGLE_ERR_POS_LOW0_SINGLE_ERR_POS_MASK)
/*! @} */

/*! @name SINGLE_ERR_POS_HIGH0 - HIGH Single Error Bit Position On OCRAM Bank0 */
/*! @{ */

#define MECC_SINGLE_ERR_POS_HIGH0_SINGLE_ERR_POS_MASK (0xFFFFFFFFU)
#define MECC_SINGLE_ERR_POS_HIGH0_SINGLE_ERR_POS_SHIFT (0U)
/*! SINGLE_ERR_POS - HIGH Single Error Bit Position On OCRAM Bank0 */
#define MECC_SINGLE_ERR_POS_HIGH0_SINGLE_ERR_POS(x) (((uint32_t)(((uint32_t)(x)) << MECC_SINGLE_ERR_POS_HIGH0_SINGLE_ERR_POS_SHIFT)) & MECC_SINGLE_ERR_POS_HIGH0_SINGLE_ERR_POS_MASK)
/*! @} */

/*! @name SINGLE_ERR_ADDR_ECC1 - Single Error Address And ECC code On OCRAM Bank1 */
/*! @{ */

#define MECC_SINGLE_ERR_ADDR_ECC1_SINGLE_ERR_ECC_MASK (0xFFU)
#define MECC_SINGLE_ERR_ADDR_ECC1_SINGLE_ERR_ECC_SHIFT (0U)
/*! SINGLE_ERR_ECC - Single Error ECC code On OCRAM Bank1 */
#define MECC_SINGLE_ERR_ADDR_ECC1_SINGLE_ERR_ECC(x) (((uint32_t)(((uint32_t)(x)) << MECC_SINGLE_ERR_ADDR_ECC1_SINGLE_ERR_ECC_SHIFT)) & MECC_SINGLE_ERR_ADDR_ECC1_SINGLE_ERR_ECC_MASK)

#define MECC_SINGLE_ERR_ADDR_ECC1_SINGLE_ERR_ADDR_MASK (0x7FFFF00U)
#define MECC_SINGLE_ERR_ADDR_ECC1_SINGLE_ERR_ADDR_SHIFT (8U)
/*! SINGLE_ERR_ADDR - Single Error Address On OCRAM Bank1 */
#define MECC_SINGLE_ERR_ADDR_ECC1_SINGLE_ERR_ADDR(x) (((uint32_t)(((uint32_t)(x)) << MECC_SINGLE_ERR_ADDR_ECC1_SINGLE_ERR_ADDR_SHIFT)) & MECC_SINGLE_ERR_ADDR_ECC1_SINGLE_ERR_ADDR_MASK)
/*! @} */

/*! @name SINGLE_ERR_DATA_LOW1 - LOW 32 Bits Single Error Read Data On OCRAM Bank1 */
/*! @{ */

#define MECC_SINGLE_ERR_DATA_LOW1_SINGLE_ERR_DATA_MASK (0xFFFFFFFFU)
#define MECC_SINGLE_ERR_DATA_LOW1_SINGLE_ERR_DATA_SHIFT (0U)
/*! SINGLE_ERR_DATA - LOW 32 Bits Single Error Read Data On OCRAM Bank1 */
#define MECC_SINGLE_ERR_DATA_LOW1_SINGLE_ERR_DATA(x) (((uint32_t)(((uint32_t)(x)) << MECC_SINGLE_ERR_DATA_LOW1_SINGLE_ERR_DATA_SHIFT)) & MECC_SINGLE_ERR_DATA_LOW1_SINGLE_ERR_DATA_MASK)
/*! @} */

/*! @name SINGLE_ERR_DATA_HIGH1 - HIGH 32 Bits Single Error Read Data On OCRAM Bank1 */
/*! @{ */

#define MECC_SINGLE_ERR_DATA_HIGH1_SINGLE_ERR_DATA_MASK (0xFFFFFFFFU)
#define MECC_SINGLE_ERR_DATA_HIGH1_SINGLE_ERR_DATA_SHIFT (0U)
/*! SINGLE_ERR_DATA - HIGH 32 Bits Single Error Read Data On OCRAM Bank1 */
#define MECC_SINGLE_ERR_DATA_HIGH1_SINGLE_ERR_DATA(x) (((uint32_t)(((uint32_t)(x)) << MECC_SINGLE_ERR_DATA_HIGH1_SINGLE_ERR_DATA_SHIFT)) & MECC_SINGLE_ERR_DATA_HIGH1_SINGLE_ERR_DATA_MASK)
/*! @} */

/*! @name SINGLE_ERR_POS_LOW1 - LOW Single Error Bit Position On OCRAM Bank1 */
/*! @{ */

#define MECC_SINGLE_ERR_POS_LOW1_SINGLE_ERR_POS_MASK (0xFFFFFFFFU)
#define MECC_SINGLE_ERR_POS_LOW1_SINGLE_ERR_POS_SHIFT (0U)
/*! SINGLE_ERR_POS - LOW Single Error Bit Position On OCRAM Bank1 */
#define MECC_SINGLE_ERR_POS_LOW1_SINGLE_ERR_POS(x) (((uint32_t)(((uint32_t)(x)) << MECC_SINGLE_ERR_POS_LOW1_SINGLE_ERR_POS_SHIFT)) & MECC_SINGLE_ERR_POS_LOW1_SINGLE_ERR_POS_MASK)
/*! @} */

/*! @name SINGLE_ERR_POS_HIGH1 - HIGH Single Error Bit Position On OCRAM Bank1 */
/*! @{ */

#define MECC_SINGLE_ERR_POS_HIGH1_SINGLE_ERR_POS_MASK (0xFFFFFFFFU)
#define MECC_SINGLE_ERR_POS_HIGH1_SINGLE_ERR_POS_SHIFT (0U)
/*! SINGLE_ERR_POS - HIGH Single Error Bit Position On OCRAM Bank1 */
#define MECC_SINGLE_ERR_POS_HIGH1_SINGLE_ERR_POS(x) (((uint32_t)(((uint32_t)(x)) << MECC_SINGLE_ERR_POS_HIGH1_SINGLE_ERR_POS_SHIFT)) & MECC_SINGLE_ERR_POS_HIGH1_SINGLE_ERR_POS_MASK)
/*! @} */

/*! @name SINGLE_ERR_ADDR_ECC2 - Single Error Address And ECC code On OCRAM Bank2 */
/*! @{ */

#define MECC_SINGLE_ERR_ADDR_ECC2_SINGLE_ERR_ECC_MASK (0xFFU)
#define MECC_SINGLE_ERR_ADDR_ECC2_SINGLE_ERR_ECC_SHIFT (0U)
/*! SINGLE_ERR_ECC - Single Error ECC code On OCRAM Bank2 */
#define MECC_SINGLE_ERR_ADDR_ECC2_SINGLE_ERR_ECC(x) (((uint32_t)(((uint32_t)(x)) << MECC_SINGLE_ERR_ADDR_ECC2_SINGLE_ERR_ECC_SHIFT)) & MECC_SINGLE_ERR_ADDR_ECC2_SINGLE_ERR_ECC_MASK)

#define MECC_SINGLE_ERR_ADDR_ECC2_SINGLE_ERR_ADDR_MASK (0x7FFFF00U)
#define MECC_SINGLE_ERR_ADDR_ECC2_SINGLE_ERR_ADDR_SHIFT (8U)
/*! SINGLE_ERR_ADDR - Single Error Address On OCRAM Bank2 */
#define MECC_SINGLE_ERR_ADDR_ECC2_SINGLE_ERR_ADDR(x) (((uint32_t)(((uint32_t)(x)) << MECC_SINGLE_ERR_ADDR_ECC2_SINGLE_ERR_ADDR_SHIFT)) & MECC_SINGLE_ERR_ADDR_ECC2_SINGLE_ERR_ADDR_MASK)
/*! @} */

/*! @name SINGLE_ERR_DATA_LOW2 - LOW 32 Bits Single Error Read Data On OCRAM Bank2 */
/*! @{ */

#define MECC_SINGLE_ERR_DATA_LOW2_SINGLE_ERR_DATA_MASK (0xFFFFFFFFU)
#define MECC_SINGLE_ERR_DATA_LOW2_SINGLE_ERR_DATA_SHIFT (0U)
/*! SINGLE_ERR_DATA - LOW 32 Bits Single Error Read Data On OCRAM Bank2 */
#define MECC_SINGLE_ERR_DATA_LOW2_SINGLE_ERR_DATA(x) (((uint32_t)(((uint32_t)(x)) << MECC_SINGLE_ERR_DATA_LOW2_SINGLE_ERR_DATA_SHIFT)) & MECC_SINGLE_ERR_DATA_LOW2_SINGLE_ERR_DATA_MASK)
/*! @} */

/*! @name SINGLE_ERR_DATA_HIGH2 - HIGH 32 Bits Single Error Read Data On OCRAM Bank2 */
/*! @{ */

#define MECC_SINGLE_ERR_DATA_HIGH2_SINGLE_ERR_DATA_MASK (0xFFFFFFFFU)
#define MECC_SINGLE_ERR_DATA_HIGH2_SINGLE_ERR_DATA_SHIFT (0U)
/*! SINGLE_ERR_DATA - HIGH 32 Bits Single Error Read Data On OCRAM Bank2 */
#define MECC_SINGLE_ERR_DATA_HIGH2_SINGLE_ERR_DATA(x) (((uint32_t)(((uint32_t)(x)) << MECC_SINGLE_ERR_DATA_HIGH2_SINGLE_ERR_DATA_SHIFT)) & MECC_SINGLE_ERR_DATA_HIGH2_SINGLE_ERR_DATA_MASK)
/*! @} */

/*! @name SINGLE_ERR_POS_LOW2 - LOW Single Error Bit Position On OCRAM Bank2 */
/*! @{ */

#define MECC_SINGLE_ERR_POS_LOW2_SINGLE_ERR_POS_MASK (0xFFFFFFFFU)
#define MECC_SINGLE_ERR_POS_LOW2_SINGLE_ERR_POS_SHIFT (0U)
/*! SINGLE_ERR_POS - LOW Single Error Bit Position On OCRAM Bank2 */
#define MECC_SINGLE_ERR_POS_LOW2_SINGLE_ERR_POS(x) (((uint32_t)(((uint32_t)(x)) << MECC_SINGLE_ERR_POS_LOW2_SINGLE_ERR_POS_SHIFT)) & MECC_SINGLE_ERR_POS_LOW2_SINGLE_ERR_POS_MASK)
/*! @} */

/*! @name SINGLE_ERR_POS_HIGH2 - HIGH Single Error Bit Position On OCRAM Bank2 */
/*! @{ */

#define MECC_SINGLE_ERR_POS_HIGH2_SINGLE_ERR_POS_MASK (0xFFFFFFFFU)
#define MECC_SINGLE_ERR_POS_HIGH2_SINGLE_ERR_POS_SHIFT (0U)
/*! SINGLE_ERR_POS - HIGH Single Error Bit Position On OCRAM Bank2 */
#define MECC_SINGLE_ERR_POS_HIGH2_SINGLE_ERR_POS(x) (((uint32_t)(((uint32_t)(x)) << MECC_SINGLE_ERR_POS_HIGH2_SINGLE_ERR_POS_SHIFT)) & MECC_SINGLE_ERR_POS_HIGH2_SINGLE_ERR_POS_MASK)
/*! @} */

/*! @name SINGLE_ERR_ADDR_ECC3 - Single Error Address And ECC code On OCRAM Bank3 */
/*! @{ */

#define MECC_SINGLE_ERR_ADDR_ECC3_SINGLE_ERR_ECC_MASK (0xFFU)
#define MECC_SINGLE_ERR_ADDR_ECC3_SINGLE_ERR_ECC_SHIFT (0U)
/*! SINGLE_ERR_ECC - Single Error ECC code On OCRAM Bank3 */
#define MECC_SINGLE_ERR_ADDR_ECC3_SINGLE_ERR_ECC(x) (((uint32_t)(((uint32_t)(x)) << MECC_SINGLE_ERR_ADDR_ECC3_SINGLE_ERR_ECC_SHIFT)) & MECC_SINGLE_ERR_ADDR_ECC3_SINGLE_ERR_ECC_MASK)

#define MECC_SINGLE_ERR_ADDR_ECC3_SINGLE_ERR_ADDR_MASK (0x7FFFF00U)
#define MECC_SINGLE_ERR_ADDR_ECC3_SINGLE_ERR_ADDR_SHIFT (8U)
/*! SINGLE_ERR_ADDR - Single Error Address On OCRAM Bank3 */
#define MECC_SINGLE_ERR_ADDR_ECC3_SINGLE_ERR_ADDR(x) (((uint32_t)(((uint32_t)(x)) << MECC_SINGLE_ERR_ADDR_ECC3_SINGLE_ERR_ADDR_SHIFT)) & MECC_SINGLE_ERR_ADDR_ECC3_SINGLE_ERR_ADDR_MASK)
/*! @} */

/*! @name SINGLE_ERR_DATA_LOW3 - LOW 32 Bits Single Error Read Data On OCRAM Bank3 */
/*! @{ */

#define MECC_SINGLE_ERR_DATA_LOW3_SINGLE_ERR_DATA_MASK (0xFFFFFFFFU)
#define MECC_SINGLE_ERR_DATA_LOW3_SINGLE_ERR_DATA_SHIFT (0U)
/*! SINGLE_ERR_DATA - LOW 32 Bits Single Error Read Data On OCRAM Bank3 */
#define MECC_SINGLE_ERR_DATA_LOW3_SINGLE_ERR_DATA(x) (((uint32_t)(((uint32_t)(x)) << MECC_SINGLE_ERR_DATA_LOW3_SINGLE_ERR_DATA_SHIFT)) & MECC_SINGLE_ERR_DATA_LOW3_SINGLE_ERR_DATA_MASK)
/*! @} */

/*! @name SINGLE_ERR_DATA_HIGH3 - HIGH 32 Bits Single Error Read Data On OCRAM Bank3 */
/*! @{ */

#define MECC_SINGLE_ERR_DATA_HIGH3_SINGLE_ERR_DATA_MASK (0xFFFFFFFFU)
#define MECC_SINGLE_ERR_DATA_HIGH3_SINGLE_ERR_DATA_SHIFT (0U)
/*! SINGLE_ERR_DATA - HIGH 32 Bits Single Error Read Data On OCRAM Bank3 */
#define MECC_SINGLE_ERR_DATA_HIGH3_SINGLE_ERR_DATA(x) (((uint32_t)(((uint32_t)(x)) << MECC_SINGLE_ERR_DATA_HIGH3_SINGLE_ERR_DATA_SHIFT)) & MECC_SINGLE_ERR_DATA_HIGH3_SINGLE_ERR_DATA_MASK)
/*! @} */

/*! @name SINGLE_ERR_POS_LOW3 - LOW Single Error Bit Position On OCRAM Bank3 */
/*! @{ */

#define MECC_SINGLE_ERR_POS_LOW3_SINGLE_ERR_POS_MASK (0xFFFFFFFFU)
#define MECC_SINGLE_ERR_POS_LOW3_SINGLE_ERR_POS_SHIFT (0U)
/*! SINGLE_ERR_POS - LOW Single Error Bit Position On OCRAM Bank3 */
#define MECC_SINGLE_ERR_POS_LOW3_SINGLE_ERR_POS(x) (((uint32_t)(((uint32_t)(x)) << MECC_SINGLE_ERR_POS_LOW3_SINGLE_ERR_POS_SHIFT)) & MECC_SINGLE_ERR_POS_LOW3_SINGLE_ERR_POS_MASK)
/*! @} */

/*! @name SINGLE_ERR_POS_HIGH3 - HIGH Single Error Bit Position On OCRAM Bank3 */
/*! @{ */

#define MECC_SINGLE_ERR_POS_HIGH3_SINGLE_ERR_POS_MASK (0xFFFFFFFFU)
#define MECC_SINGLE_ERR_POS_HIGH3_SINGLE_ERR_POS_SHIFT (0U)
/*! SINGLE_ERR_POS - HIGH Single Error Bit Position On OCRAM Bank3 */
#define MECC_SINGLE_ERR_POS_HIGH3_SINGLE_ERR_POS(x) (((uint32_t)(((uint32_t)(x)) << MECC_SINGLE_ERR_POS_HIGH3_SINGLE_ERR_POS_SHIFT)) & MECC_SINGLE_ERR_POS_HIGH3_SINGLE_ERR_POS_MASK)
/*! @} */

/*! @name MULTI_ERR_ADDR_ECC0 - Multiple Error Address And ECC code On OCRAM Bank0 */
/*! @{ */

#define MECC_MULTI_ERR_ADDR_ECC0_MULTI_ERR_ECC_MASK (0xFFU)
#define MECC_MULTI_ERR_ADDR_ECC0_MULTI_ERR_ECC_SHIFT (0U)
/*! MULTI_ERR_ECC - Multiple Error ECC code On OCRAM Bank0 */
#define MECC_MULTI_ERR_ADDR_ECC0_MULTI_ERR_ECC(x) (((uint32_t)(((uint32_t)(x)) << MECC_MULTI_ERR_ADDR_ECC0_MULTI_ERR_ECC_SHIFT)) & MECC_MULTI_ERR_ADDR_ECC0_MULTI_ERR_ECC_MASK)

#define MECC_MULTI_ERR_ADDR_ECC0_MULTI_ERR_ADDR_MASK (0x7FFFF00U)
#define MECC_MULTI_ERR_ADDR_ECC0_MULTI_ERR_ADDR_SHIFT (8U)
/*! MULTI_ERR_ADDR - Multiple Error Address On OCRAM Bank0 */
#define MECC_MULTI_ERR_ADDR_ECC0_MULTI_ERR_ADDR(x) (((uint32_t)(((uint32_t)(x)) << MECC_MULTI_ERR_ADDR_ECC0_MULTI_ERR_ADDR_SHIFT)) & MECC_MULTI_ERR_ADDR_ECC0_MULTI_ERR_ADDR_MASK)
/*! @} */

/*! @name MULTI_ERR_DATA_LOW0 - LOW 32 Bits Multiple Error Read Data On OCRAM Bank0 */
/*! @{ */

#define MECC_MULTI_ERR_DATA_LOW0_MULTI_ERR_DATA_MASK (0xFFFFFFFFU)
#define MECC_MULTI_ERR_DATA_LOW0_MULTI_ERR_DATA_SHIFT (0U)
/*! MULTI_ERR_DATA - LOW 32 Bits Multiple Error Read Data On OCRAM Bank0 */
#define MECC_MULTI_ERR_DATA_LOW0_MULTI_ERR_DATA(x) (((uint32_t)(((uint32_t)(x)) << MECC_MULTI_ERR_DATA_LOW0_MULTI_ERR_DATA_SHIFT)) & MECC_MULTI_ERR_DATA_LOW0_MULTI_ERR_DATA_MASK)
/*! @} */

/*! @name MULTI_ERR_DATA_HIGH0 - HIGH 32 Bits Multiple Error Read Data On OCRAM Bank0 */
/*! @{ */

#define MECC_MULTI_ERR_DATA_HIGH0_MULTI_ERR_DATA_MASK (0xFFFFFFFFU)
#define MECC_MULTI_ERR_DATA_HIGH0_MULTI_ERR_DATA_SHIFT (0U)
/*! MULTI_ERR_DATA - HIGH 32 Bits Multiple Error Read Data On OCRAM Bank0 */
#define MECC_MULTI_ERR_DATA_HIGH0_MULTI_ERR_DATA(x) (((uint32_t)(((uint32_t)(x)) << MECC_MULTI_ERR_DATA_HIGH0_MULTI_ERR_DATA_SHIFT)) & MECC_MULTI_ERR_DATA_HIGH0_MULTI_ERR_DATA_MASK)
/*! @} */

/*! @name MULTI_ERR_ADDR_ECC1 - Multiple Error Address And ECC code On OCRAM Bank1 */
/*! @{ */

#define MECC_MULTI_ERR_ADDR_ECC1_MULTI_ERR_ECC_MASK (0xFFU)
#define MECC_MULTI_ERR_ADDR_ECC1_MULTI_ERR_ECC_SHIFT (0U)
/*! MULTI_ERR_ECC - Multiple Error ECC code On OCRAM Bank1 */
#define MECC_MULTI_ERR_ADDR_ECC1_MULTI_ERR_ECC(x) (((uint32_t)(((uint32_t)(x)) << MECC_MULTI_ERR_ADDR_ECC1_MULTI_ERR_ECC_SHIFT)) & MECC_MULTI_ERR_ADDR_ECC1_MULTI_ERR_ECC_MASK)

#define MECC_MULTI_ERR_ADDR_ECC1_MULTI_ERR_ADDR_MASK (0x7FFFF00U)
#define MECC_MULTI_ERR_ADDR_ECC1_MULTI_ERR_ADDR_SHIFT (8U)
/*! MULTI_ERR_ADDR - Multiple Error Address On OCRAM Bank1 */
#define MECC_MULTI_ERR_ADDR_ECC1_MULTI_ERR_ADDR(x) (((uint32_t)(((uint32_t)(x)) << MECC_MULTI_ERR_ADDR_ECC1_MULTI_ERR_ADDR_SHIFT)) & MECC_MULTI_ERR_ADDR_ECC1_MULTI_ERR_ADDR_MASK)
/*! @} */

/*! @name MULTI_ERR_DATA_LOW1 - LOW 32 Bits Multiple Error Read Data On OCRAM Bank1 */
/*! @{ */

#define MECC_MULTI_ERR_DATA_LOW1_MULTI_ERR_DATA_MASK (0xFFFFFFFFU)
#define MECC_MULTI_ERR_DATA_LOW1_MULTI_ERR_DATA_SHIFT (0U)
/*! MULTI_ERR_DATA - LOW 32 Bits Multiple Error Read Data On OCRAM Bank1 */
#define MECC_MULTI_ERR_DATA_LOW1_MULTI_ERR_DATA(x) (((uint32_t)(((uint32_t)(x)) << MECC_MULTI_ERR_DATA_LOW1_MULTI_ERR_DATA_SHIFT)) & MECC_MULTI_ERR_DATA_LOW1_MULTI_ERR_DATA_MASK)
/*! @} */

/*! @name MULTI_ERR_DATA_HIGH1 - HIGH 32 Bits Multiple Error Read Data On OCRAM Bank1 */
/*! @{ */

#define MECC_MULTI_ERR_DATA_HIGH1_MULTI_ERR_DATA_MASK (0xFFFFFFFFU)
#define MECC_MULTI_ERR_DATA_HIGH1_MULTI_ERR_DATA_SHIFT (0U)
/*! MULTI_ERR_DATA - HIGH 32 Bits Multiple Error Read Data On OCRAM Bank1 */
#define MECC_MULTI_ERR_DATA_HIGH1_MULTI_ERR_DATA(x) (((uint32_t)(((uint32_t)(x)) << MECC_MULTI_ERR_DATA_HIGH1_MULTI_ERR_DATA_SHIFT)) & MECC_MULTI_ERR_DATA_HIGH1_MULTI_ERR_DATA_MASK)
/*! @} */

/*! @name MULTI_ERR_ADDR_ECC2 - Multiple Error Address And ECC code On OCRAM Bank2 */
/*! @{ */

#define MECC_MULTI_ERR_ADDR_ECC2_MULTI_ERR_ECC_MASK (0xFFU)
#define MECC_MULTI_ERR_ADDR_ECC2_MULTI_ERR_ECC_SHIFT (0U)
/*! MULTI_ERR_ECC - Multiple Error ECC code On OCRAM Bank2 */
#define MECC_MULTI_ERR_ADDR_ECC2_MULTI_ERR_ECC(x) (((uint32_t)(((uint32_t)(x)) << MECC_MULTI_ERR_ADDR_ECC2_MULTI_ERR_ECC_SHIFT)) & MECC_MULTI_ERR_ADDR_ECC2_MULTI_ERR_ECC_MASK)

#define MECC_MULTI_ERR_ADDR_ECC2_MULTI_ERR_ADDR_MASK (0x7FFFF00U)
#define MECC_MULTI_ERR_ADDR_ECC2_MULTI_ERR_ADDR_SHIFT (8U)
/*! MULTI_ERR_ADDR - Multiple Error Address On OCRAM Bank2 */
#define MECC_MULTI_ERR_ADDR_ECC2_MULTI_ERR_ADDR(x) (((uint32_t)(((uint32_t)(x)) << MECC_MULTI_ERR_ADDR_ECC2_MULTI_ERR_ADDR_SHIFT)) & MECC_MULTI_ERR_ADDR_ECC2_MULTI_ERR_ADDR_MASK)
/*! @} */

/*! @name MULTI_ERR_DATA_LOW2 - LOW 32 Bits Multiple Error Read Data On OCRAM Bank2 */
/*! @{ */

#define MECC_MULTI_ERR_DATA_LOW2_MULTI_ERR_DATA_MASK (0xFFFFFFFFU)
#define MECC_MULTI_ERR_DATA_LOW2_MULTI_ERR_DATA_SHIFT (0U)
/*! MULTI_ERR_DATA - LOW 32 Bits Multiple Error Read Data On OCRAM Bank2 */
#define MECC_MULTI_ERR_DATA_LOW2_MULTI_ERR_DATA(x) (((uint32_t)(((uint32_t)(x)) << MECC_MULTI_ERR_DATA_LOW2_MULTI_ERR_DATA_SHIFT)) & MECC_MULTI_ERR_DATA_LOW2_MULTI_ERR_DATA_MASK)
/*! @} */

/*! @name MULTI_ERR_DATA_HIGH2 - HIGH 32 Bits Multiple Error Read Data On OCRAM Bank2 */
/*! @{ */

#define MECC_MULTI_ERR_DATA_HIGH2_MULTI_ERR_DATA_MASK (0xFFFFFFFFU)
#define MECC_MULTI_ERR_DATA_HIGH2_MULTI_ERR_DATA_SHIFT (0U)
/*! MULTI_ERR_DATA - HIGH 32 Bits Multiple Error Read Data On OCRAM Bank2 */
#define MECC_MULTI_ERR_DATA_HIGH2_MULTI_ERR_DATA(x) (((uint32_t)(((uint32_t)(x)) << MECC_MULTI_ERR_DATA_HIGH2_MULTI_ERR_DATA_SHIFT)) & MECC_MULTI_ERR_DATA_HIGH2_MULTI_ERR_DATA_MASK)
/*! @} */

/*! @name MULTI_ERR_ADDR_ECC3 - Multiple Error Address And ECC code On OCRAM Bank3 */
/*! @{ */

#define MECC_MULTI_ERR_ADDR_ECC3_MULTI_ERR_ECC_MASK (0xFFU)
#define MECC_MULTI_ERR_ADDR_ECC3_MULTI_ERR_ECC_SHIFT (0U)
/*! MULTI_ERR_ECC - Multiple Error ECC code On OCRAM Bank3 */
#define MECC_MULTI_ERR_ADDR_ECC3_MULTI_ERR_ECC(x) (((uint32_t)(((uint32_t)(x)) << MECC_MULTI_ERR_ADDR_ECC3_MULTI_ERR_ECC_SHIFT)) & MECC_MULTI_ERR_ADDR_ECC3_MULTI_ERR_ECC_MASK)

#define MECC_MULTI_ERR_ADDR_ECC3_MULTI_ERR_ADDR_MASK (0x7FFFF00U)
#define MECC_MULTI_ERR_ADDR_ECC3_MULTI_ERR_ADDR_SHIFT (8U)
/*! MULTI_ERR_ADDR - Multiple Error Address On OCRAM Bank3 */
#define MECC_MULTI_ERR_ADDR_ECC3_MULTI_ERR_ADDR(x) (((uint32_t)(((uint32_t)(x)) << MECC_MULTI_ERR_ADDR_ECC3_MULTI_ERR_ADDR_SHIFT)) & MECC_MULTI_ERR_ADDR_ECC3_MULTI_ERR_ADDR_MASK)
/*! @} */

/*! @name MULTI_ERR_DATA_LOW3 - LOW 32 Bits Multiple Error Read Data On OCRAM Bank3 */
/*! @{ */

#define MECC_MULTI_ERR_DATA_LOW3_MULTI_ERR_DATA_MASK (0xFFFFFFFFU)
#define MECC_MULTI_ERR_DATA_LOW3_MULTI_ERR_DATA_SHIFT (0U)
/*! MULTI_ERR_DATA - LOW 32 Bits Multiple Error Read Data On OCRAM Bank3 */
#define MECC_MULTI_ERR_DATA_LOW3_MULTI_ERR_DATA(x) (((uint32_t)(((uint32_t)(x)) << MECC_MULTI_ERR_DATA_LOW3_MULTI_ERR_DATA_SHIFT)) & MECC_MULTI_ERR_DATA_LOW3_MULTI_ERR_DATA_MASK)
/*! @} */

/*! @name MULTI_ERR_DATA_HIGH3 - HIGH 32 Bits Multiple Error Read Data On OCRAM Bank3 */
/*! @{ */

#define MECC_MULTI_ERR_DATA_HIGH3_MULTI_ERR_DATA_MASK (0xFFFFFFFFU)
#define MECC_MULTI_ERR_DATA_HIGH3_MULTI_ERR_DATA_SHIFT (0U)
/*! MULTI_ERR_DATA - HIGH 32 Bits Multiple Error Read Data On OCRAM Bank3 */
#define MECC_MULTI_ERR_DATA_HIGH3_MULTI_ERR_DATA(x) (((uint32_t)(((uint32_t)(x)) << MECC_MULTI_ERR_DATA_HIGH3_MULTI_ERR_DATA_SHIFT)) & MECC_MULTI_ERR_DATA_HIGH3_MULTI_ERR_DATA_MASK)
/*! @} */

/*! @name PIPE_ECC_EN - OCRAM Pipeline And ECC Enable */
/*! @{ */

#define MECC_PIPE_ECC_EN_READ_DATA_WAIT_EN_MASK  (0x1U)
#define MECC_PIPE_ECC_EN_READ_DATA_WAIT_EN_SHIFT (0U)
/*! READ_DATA_WAIT_EN - Read Data Wait Enable
 *  0b0..Disable.
 *  0b1..Enable.
 */
#define MECC_PIPE_ECC_EN_READ_DATA_WAIT_EN(x)    (((uint32_t)(((uint32_t)(x)) << MECC_PIPE_ECC_EN_READ_DATA_WAIT_EN_SHIFT)) & MECC_PIPE_ECC_EN_READ_DATA_WAIT_EN_MASK)

#define MECC_PIPE_ECC_EN_READ_ADDR_PIPE_EN_MASK  (0x2U)
#define MECC_PIPE_ECC_EN_READ_ADDR_PIPE_EN_SHIFT (1U)
/*! READ_ADDR_PIPE_EN - Read Address Pipeline Enable
 *  0b0..Disable.
 *  0b1..Enable.
 */
#define MECC_PIPE_ECC_EN_READ_ADDR_PIPE_EN(x)    (((uint32_t)(((uint32_t)(x)) << MECC_PIPE_ECC_EN_READ_ADDR_PIPE_EN_SHIFT)) & MECC_PIPE_ECC_EN_READ_ADDR_PIPE_EN_MASK)

#define MECC_PIPE_ECC_EN_WRITE_DATA_PIPE_EN_MASK (0x4U)
#define MECC_PIPE_ECC_EN_WRITE_DATA_PIPE_EN_SHIFT (2U)
/*! WRITE_DATA_PIPE_EN - Write Data Pipeline Enable
 *  0b0..Disable.
 *  0b1..Enable.
 */
#define MECC_PIPE_ECC_EN_WRITE_DATA_PIPE_EN(x)   (((uint32_t)(((uint32_t)(x)) << MECC_PIPE_ECC_EN_WRITE_DATA_PIPE_EN_SHIFT)) & MECC_PIPE_ECC_EN_WRITE_DATA_PIPE_EN_MASK)

#define MECC_PIPE_ECC_EN_WRITE_ADDR_PIPE_EN_MASK (0x8U)
#define MECC_PIPE_ECC_EN_WRITE_ADDR_PIPE_EN_SHIFT (3U)
/*! WRITE_ADDR_PIPE_EN - Write Address Pipeline Enable
 *  0b0..Disable.
 *  0b1..Enable.
 */
#define MECC_PIPE_ECC_EN_WRITE_ADDR_PIPE_EN(x)   (((uint32_t)(((uint32_t)(x)) << MECC_PIPE_ECC_EN_WRITE_ADDR_PIPE_EN_SHIFT)) & MECC_PIPE_ECC_EN_WRITE_ADDR_PIPE_EN_MASK)

#define MECC_PIPE_ECC_EN_ECC_EN_MASK             (0x10U)
#define MECC_PIPE_ECC_EN_ECC_EN_SHIFT            (4U)
/*! ECC_EN - ECC Function Enable
 *  0b0..Disable.
 *  0b1..Enable.
 */
#define MECC_PIPE_ECC_EN_ECC_EN(x)               (((uint32_t)(((uint32_t)(x)) << MECC_PIPE_ECC_EN_ECC_EN_SHIFT)) & MECC_PIPE_ECC_EN_ECC_EN_MASK)
/*! @} */

/*! @name PENDING_STAT - Pending Status */
/*! @{ */

#define MECC_PENDING_STAT_READ_DATA_WAIT_PENDING_MASK (0x1U)
#define MECC_PENDING_STAT_READ_DATA_WAIT_PENDING_SHIFT (0U)
/*! READ_DATA_WAIT_PENDING - Read Data Wait Pending
 *  0b0..No update pending status for READ_DATA_WAIT_EN.
 *  0b1..When READ_DATA_WAIT_EN register bit is changed, this register bit will be set until the new setup becomes valid in the controller.
 */
#define MECC_PENDING_STAT_READ_DATA_WAIT_PENDING(x) (((uint32_t)(((uint32_t)(x)) << MECC_PENDING_STAT_READ_DATA_WAIT_PENDING_SHIFT)) & MECC_PENDING_STAT_READ_DATA_WAIT_PENDING_MASK)

#define MECC_PENDING_STAT_READ_ADDR_PIPE_PENDING_MASK (0x2U)
#define MECC_PENDING_STAT_READ_ADDR_PIPE_PENDING_SHIFT (1U)
/*! READ_ADDR_PIPE_PENDING - Read Address Pipeline Pending
 *  0b0..No update pending status for READ_ADDR_PIPE_EN.
 *  0b1..When READ_ADDR_PIPE_EN register bit is changed, this register bit will be set until the new setup becomes valid in the controller.
 */
#define MECC_PENDING_STAT_READ_ADDR_PIPE_PENDING(x) (((uint32_t)(((uint32_t)(x)) << MECC_PENDING_STAT_READ_ADDR_PIPE_PENDING_SHIFT)) & MECC_PENDING_STAT_READ_ADDR_PIPE_PENDING_MASK)

#define MECC_PENDING_STAT_WRITE_DATA_PIPE_PENDING_MASK (0x4U)
#define MECC_PENDING_STAT_WRITE_DATA_PIPE_PENDING_SHIFT (2U)
/*! WRITE_DATA_PIPE_PENDING - Write Data Pipeline Pending
 *  0b0..No update pending status for WRITE_DATA_PIPE_EN.
 *  0b1..When WRITE_DATA_PIPE_EN register bit is changed, this register bit will be set until the new setup becomes valid in the controller.
 */
#define MECC_PENDING_STAT_WRITE_DATA_PIPE_PENDING(x) (((uint32_t)(((uint32_t)(x)) << MECC_PENDING_STAT_WRITE_DATA_PIPE_PENDING_SHIFT)) & MECC_PENDING_STAT_WRITE_DATA_PIPE_PENDING_MASK)

#define MECC_PENDING_STAT_WRITE_ADDR_PIPE_PENDING_MASK (0x8U)
#define MECC_PENDING_STAT_WRITE_ADDR_PIPE_PENDING_SHIFT (3U)
/*! WRITE_ADDR_PIPE_PENDING - Write Address Pipeline Pending
 *  0b0..No update pending status for WRITE_ADDR_PIPE_EN.
 *  0b1..When WRITE_ADDR_PIPE_EN register bit is changed, this register bit will be set until the new setup becomes valid in the controller.
 */
#define MECC_PENDING_STAT_WRITE_ADDR_PIPE_PENDING(x) (((uint32_t)(((uint32_t)(x)) << MECC_PENDING_STAT_WRITE_ADDR_PIPE_PENDING_SHIFT)) & MECC_PENDING_STAT_WRITE_ADDR_PIPE_PENDING_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group MECC_Register_Masks */


/*!
 * @}
 */ /* end of group MECC_Peripheral_Access_Layer */


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


#endif  /* PERI_MECC_H_ */

