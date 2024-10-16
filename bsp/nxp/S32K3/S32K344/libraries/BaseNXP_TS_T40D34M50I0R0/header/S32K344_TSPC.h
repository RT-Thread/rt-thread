/*
** ###################################################################
**     Processor:           S32K344
**     Reference manual:    S32K3xx RM Rev.3
**     Version:             rev. 1.9, 2021-10-27
**     Build:               b211026
**
**     Abstract:
**         Peripheral Access Layer for S32K344
**
**     Copyright 1997-2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2021 NXP
**
**     NXP Confidential. This software is owned or controlled by NXP and may only be
**     used strictly in accordance with the applicable license terms. By expressly
**     accepting such terms or by downloading, installing, activating and/or otherwise
**     using the software, you are agreeing that you have read, and that you agree to
**     comply with and are bound by, such license terms. If you do not agree to be
**     bound by the applicable license terms, then you may not retain, install,
**     activate or otherwise use the software. The production use license in
**     Section 2.3 is expressly granted for this software.
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
** ###################################################################
*/

/*!
 * @file S32K344_TSPC.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_TSPC
 *
 * This file contains register definitions and macros for easy access to their
 * bit fields.
 *
 * This file assumes LITTLE endian system.
 */

/**
* @page misra_violations MISRA-C:2012 violations
*
* @section [global]
* Violates MISRA 2012 Advisory Rule 2.3, local typedef not referenced
* The SoC header defines typedef for all modules.
*
* @section [global]
* Violates MISRA 2012 Advisory Rule 2.5, local macro not referenced
* The SoC header defines macros for all modules and registers.
*
* @section [global]
* Violates MISRA 2012 Advisory Directive 4.9, Function-like macro
* These are generated macros used for accessing the bit-fields from registers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 5.1, identifier clash
* The supported compilers use more than 31 significant characters for identifiers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 5.2, identifier clash
* The supported compilers use more than 31 significant characters for identifiers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 5.4, identifier clash
* The supported compilers use more than 31 significant characters for identifiers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 5.5, identifier clash
* The supported compilers use more than 31 significant characters for identifiers.
*
* @section [global]
* Violates MISRA 2012 Required Rule 21.1, defined macro '__I' is reserved to the compiler
* This type qualifier is needed to ensure correct I/O access and addressing.
*/

/* Prevention from multiple including the same memory map */
#if !defined(S32K344_TSPC_H_)  /* Check if memory map has not been already included */
#define S32K344_TSPC_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- TSPC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TSPC_Peripheral_Access_Layer TSPC Peripheral Access Layer
 * @{
 */

/** TSPC - Size of Registers Arrays */
#define TSPC_GROUP_COUNT                          2u

/** TSPC - Register Layout Typedef */
typedef struct {
  __IO uint32_t GRP_EN;                            /**< Group Enable, offset: 0x0 */
  uint8_t RESERVED_0[76];
  struct {                                         /* offset: 0x50, array step: 0x50 */
    __IO uint32_t GRP_OBE1;                          /**< Group OBE, array offset: 0x50, array step: 0x50 */
    __IO uint32_t GRP_OBE2;                          /**< Group OBE, array offset: 0x54, array step: 0x50 */
    uint8_t RESERVED_0[72];
  } GROUP[TSPC_GROUP_COUNT];
} TSPC_Type, *TSPC_MemMapPtr;

/** Number of instances of the TSPC module. */
#define TSPC_INSTANCE_COUNT                      (1u)

/* TSPC - Peripheral instance base addresses */
/** Peripheral TSPC base address */
#define IP_TSPC_BASE                             (0x402C4000u)
/** Peripheral TSPC base pointer */
#define IP_TSPC                                  ((TSPC_Type *)IP_TSPC_BASE)
/** Array initializer of TSPC peripheral base addresses */
#define IP_TSPC_BASE_ADDRS                       { IP_TSPC_BASE }
/** Array initializer of TSPC peripheral base pointers */
#define IP_TSPC_BASE_PTRS                        { IP_TSPC }

/* ----------------------------------------------------------------------------
   -- TSPC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TSPC_Register_Masks TSPC Register Masks
 * @{
 */

/*! @name GRP_EN - Group Enable */
/*! @{ */

#define TSPC_GRP_EN_GRP1_EN_MASK                 (0x1U)
#define TSPC_GRP_EN_GRP1_EN_SHIFT                (0U)
#define TSPC_GRP_EN_GRP1_EN_WIDTH                (1U)
#define TSPC_GRP_EN_GRP1_EN(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_EN_GRP1_EN_SHIFT)) & TSPC_GRP_EN_GRP1_EN_MASK)

#define TSPC_GRP_EN_GRP2_EN_MASK                 (0x2U)
#define TSPC_GRP_EN_GRP2_EN_SHIFT                (1U)
#define TSPC_GRP_EN_GRP2_EN_WIDTH                (1U)
#define TSPC_GRP_EN_GRP2_EN(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_EN_GRP2_EN_SHIFT)) & TSPC_GRP_EN_GRP2_EN_MASK)
/*! @} */

/*! @name GRP_OBE1 - Group OBE */
/*! @{ */

#define TSPC_GRP_OBE1_OBE0_MASK                  (0x1U)
#define TSPC_GRP_OBE1_OBE0_SHIFT                 (0U)
#define TSPC_GRP_OBE1_OBE0_WIDTH                 (1U)
#define TSPC_GRP_OBE1_OBE0(x)                    (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE1_OBE0_SHIFT)) & TSPC_GRP_OBE1_OBE0_MASK)

#define TSPC_GRP_OBE1_OBE1_MASK                  (0x2U)
#define TSPC_GRP_OBE1_OBE1_SHIFT                 (1U)
#define TSPC_GRP_OBE1_OBE1_WIDTH                 (1U)
#define TSPC_GRP_OBE1_OBE1(x)                    (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE1_OBE1_SHIFT)) & TSPC_GRP_OBE1_OBE1_MASK)

#define TSPC_GRP_OBE1_OBE2_MASK                  (0x4U)
#define TSPC_GRP_OBE1_OBE2_SHIFT                 (2U)
#define TSPC_GRP_OBE1_OBE2_WIDTH                 (1U)
#define TSPC_GRP_OBE1_OBE2(x)                    (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE1_OBE2_SHIFT)) & TSPC_GRP_OBE1_OBE2_MASK)

#define TSPC_GRP_OBE1_OBE3_MASK                  (0x8U)
#define TSPC_GRP_OBE1_OBE3_SHIFT                 (3U)
#define TSPC_GRP_OBE1_OBE3_WIDTH                 (1U)
#define TSPC_GRP_OBE1_OBE3(x)                    (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE1_OBE3_SHIFT)) & TSPC_GRP_OBE1_OBE3_MASK)

#define TSPC_GRP_OBE1_OBE4_MASK                  (0x10U)
#define TSPC_GRP_OBE1_OBE4_SHIFT                 (4U)
#define TSPC_GRP_OBE1_OBE4_WIDTH                 (1U)
#define TSPC_GRP_OBE1_OBE4(x)                    (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE1_OBE4_SHIFT)) & TSPC_GRP_OBE1_OBE4_MASK)

#define TSPC_GRP_OBE1_OBE5_MASK                  (0x20U)
#define TSPC_GRP_OBE1_OBE5_SHIFT                 (5U)
#define TSPC_GRP_OBE1_OBE5_WIDTH                 (1U)
#define TSPC_GRP_OBE1_OBE5(x)                    (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE1_OBE5_SHIFT)) & TSPC_GRP_OBE1_OBE5_MASK)

#define TSPC_GRP_OBE1_OBE6_MASK                  (0x40U)
#define TSPC_GRP_OBE1_OBE6_SHIFT                 (6U)
#define TSPC_GRP_OBE1_OBE6_WIDTH                 (1U)
#define TSPC_GRP_OBE1_OBE6(x)                    (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE1_OBE6_SHIFT)) & TSPC_GRP_OBE1_OBE6_MASK)

#define TSPC_GRP_OBE1_OBE7_MASK                  (0x80U)
#define TSPC_GRP_OBE1_OBE7_SHIFT                 (7U)
#define TSPC_GRP_OBE1_OBE7_WIDTH                 (1U)
#define TSPC_GRP_OBE1_OBE7(x)                    (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE1_OBE7_SHIFT)) & TSPC_GRP_OBE1_OBE7_MASK)

#define TSPC_GRP_OBE1_OBE8_MASK                  (0x100U)
#define TSPC_GRP_OBE1_OBE8_SHIFT                 (8U)
#define TSPC_GRP_OBE1_OBE8_WIDTH                 (1U)
#define TSPC_GRP_OBE1_OBE8(x)                    (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE1_OBE8_SHIFT)) & TSPC_GRP_OBE1_OBE8_MASK)

#define TSPC_GRP_OBE1_OBE9_MASK                  (0x200U)
#define TSPC_GRP_OBE1_OBE9_SHIFT                 (9U)
#define TSPC_GRP_OBE1_OBE9_WIDTH                 (1U)
#define TSPC_GRP_OBE1_OBE9(x)                    (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE1_OBE9_SHIFT)) & TSPC_GRP_OBE1_OBE9_MASK)

#define TSPC_GRP_OBE1_OBE10_MASK                 (0x400U)
#define TSPC_GRP_OBE1_OBE10_SHIFT                (10U)
#define TSPC_GRP_OBE1_OBE10_WIDTH                (1U)
#define TSPC_GRP_OBE1_OBE10(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE1_OBE10_SHIFT)) & TSPC_GRP_OBE1_OBE10_MASK)

#define TSPC_GRP_OBE1_OBE11_MASK                 (0x800U)
#define TSPC_GRP_OBE1_OBE11_SHIFT                (11U)
#define TSPC_GRP_OBE1_OBE11_WIDTH                (1U)
#define TSPC_GRP_OBE1_OBE11(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE1_OBE11_SHIFT)) & TSPC_GRP_OBE1_OBE11_MASK)

#define TSPC_GRP_OBE1_OBE12_MASK                 (0x1000U)
#define TSPC_GRP_OBE1_OBE12_SHIFT                (12U)
#define TSPC_GRP_OBE1_OBE12_WIDTH                (1U)
#define TSPC_GRP_OBE1_OBE12(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE1_OBE12_SHIFT)) & TSPC_GRP_OBE1_OBE12_MASK)

#define TSPC_GRP_OBE1_OBE13_MASK                 (0x2000U)
#define TSPC_GRP_OBE1_OBE13_SHIFT                (13U)
#define TSPC_GRP_OBE1_OBE13_WIDTH                (1U)
#define TSPC_GRP_OBE1_OBE13(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE1_OBE13_SHIFT)) & TSPC_GRP_OBE1_OBE13_MASK)

#define TSPC_GRP_OBE1_OBE14_MASK                 (0x4000U)
#define TSPC_GRP_OBE1_OBE14_SHIFT                (14U)
#define TSPC_GRP_OBE1_OBE14_WIDTH                (1U)
#define TSPC_GRP_OBE1_OBE14(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE1_OBE14_SHIFT)) & TSPC_GRP_OBE1_OBE14_MASK)

#define TSPC_GRP_OBE1_OBE15_MASK                 (0x8000U)
#define TSPC_GRP_OBE1_OBE15_SHIFT                (15U)
#define TSPC_GRP_OBE1_OBE15_WIDTH                (1U)
#define TSPC_GRP_OBE1_OBE15(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE1_OBE15_SHIFT)) & TSPC_GRP_OBE1_OBE15_MASK)

#define TSPC_GRP_OBE1_OBE16_MASK                 (0x10000U)
#define TSPC_GRP_OBE1_OBE16_SHIFT                (16U)
#define TSPC_GRP_OBE1_OBE16_WIDTH                (1U)
#define TSPC_GRP_OBE1_OBE16(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE1_OBE16_SHIFT)) & TSPC_GRP_OBE1_OBE16_MASK)

#define TSPC_GRP_OBE1_OBE17_MASK                 (0x20000U)
#define TSPC_GRP_OBE1_OBE17_SHIFT                (17U)
#define TSPC_GRP_OBE1_OBE17_WIDTH                (1U)
#define TSPC_GRP_OBE1_OBE17(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE1_OBE17_SHIFT)) & TSPC_GRP_OBE1_OBE17_MASK)

#define TSPC_GRP_OBE1_OBE18_MASK                 (0x40000U)
#define TSPC_GRP_OBE1_OBE18_SHIFT                (18U)
#define TSPC_GRP_OBE1_OBE18_WIDTH                (1U)
#define TSPC_GRP_OBE1_OBE18(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE1_OBE18_SHIFT)) & TSPC_GRP_OBE1_OBE18_MASK)

#define TSPC_GRP_OBE1_OBE19_MASK                 (0x80000U)
#define TSPC_GRP_OBE1_OBE19_SHIFT                (19U)
#define TSPC_GRP_OBE1_OBE19_WIDTH                (1U)
#define TSPC_GRP_OBE1_OBE19(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE1_OBE19_SHIFT)) & TSPC_GRP_OBE1_OBE19_MASK)

#define TSPC_GRP_OBE1_OBE20_MASK                 (0x100000U)
#define TSPC_GRP_OBE1_OBE20_SHIFT                (20U)
#define TSPC_GRP_OBE1_OBE20_WIDTH                (1U)
#define TSPC_GRP_OBE1_OBE20(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE1_OBE20_SHIFT)) & TSPC_GRP_OBE1_OBE20_MASK)

#define TSPC_GRP_OBE1_OBE21_MASK                 (0x200000U)
#define TSPC_GRP_OBE1_OBE21_SHIFT                (21U)
#define TSPC_GRP_OBE1_OBE21_WIDTH                (1U)
#define TSPC_GRP_OBE1_OBE21(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE1_OBE21_SHIFT)) & TSPC_GRP_OBE1_OBE21_MASK)

#define TSPC_GRP_OBE1_OBE22_MASK                 (0x400000U)
#define TSPC_GRP_OBE1_OBE22_SHIFT                (22U)
#define TSPC_GRP_OBE1_OBE22_WIDTH                (1U)
#define TSPC_GRP_OBE1_OBE22(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE1_OBE22_SHIFT)) & TSPC_GRP_OBE1_OBE22_MASK)

#define TSPC_GRP_OBE1_OBE23_MASK                 (0x800000U)
#define TSPC_GRP_OBE1_OBE23_SHIFT                (23U)
#define TSPC_GRP_OBE1_OBE23_WIDTH                (1U)
#define TSPC_GRP_OBE1_OBE23(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE1_OBE23_SHIFT)) & TSPC_GRP_OBE1_OBE23_MASK)

#define TSPC_GRP_OBE1_OBE24_MASK                 (0x1000000U)
#define TSPC_GRP_OBE1_OBE24_SHIFT                (24U)
#define TSPC_GRP_OBE1_OBE24_WIDTH                (1U)
#define TSPC_GRP_OBE1_OBE24(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE1_OBE24_SHIFT)) & TSPC_GRP_OBE1_OBE24_MASK)

#define TSPC_GRP_OBE1_OBE25_MASK                 (0x2000000U)
#define TSPC_GRP_OBE1_OBE25_SHIFT                (25U)
#define TSPC_GRP_OBE1_OBE25_WIDTH                (1U)
#define TSPC_GRP_OBE1_OBE25(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE1_OBE25_SHIFT)) & TSPC_GRP_OBE1_OBE25_MASK)

#define TSPC_GRP_OBE1_OBE26_MASK                 (0x4000000U)
#define TSPC_GRP_OBE1_OBE26_SHIFT                (26U)
#define TSPC_GRP_OBE1_OBE26_WIDTH                (1U)
#define TSPC_GRP_OBE1_OBE26(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE1_OBE26_SHIFT)) & TSPC_GRP_OBE1_OBE26_MASK)

#define TSPC_GRP_OBE1_OBE27_MASK                 (0x8000000U)
#define TSPC_GRP_OBE1_OBE27_SHIFT                (27U)
#define TSPC_GRP_OBE1_OBE27_WIDTH                (1U)
#define TSPC_GRP_OBE1_OBE27(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE1_OBE27_SHIFT)) & TSPC_GRP_OBE1_OBE27_MASK)

#define TSPC_GRP_OBE1_OBE28_MASK                 (0x10000000U)
#define TSPC_GRP_OBE1_OBE28_SHIFT                (28U)
#define TSPC_GRP_OBE1_OBE28_WIDTH                (1U)
#define TSPC_GRP_OBE1_OBE28(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE1_OBE28_SHIFT)) & TSPC_GRP_OBE1_OBE28_MASK)

#define TSPC_GRP_OBE1_OBE29_MASK                 (0x20000000U)
#define TSPC_GRP_OBE1_OBE29_SHIFT                (29U)
#define TSPC_GRP_OBE1_OBE29_WIDTH                (1U)
#define TSPC_GRP_OBE1_OBE29(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE1_OBE29_SHIFT)) & TSPC_GRP_OBE1_OBE29_MASK)

#define TSPC_GRP_OBE1_OBE30_MASK                 (0x40000000U)
#define TSPC_GRP_OBE1_OBE30_SHIFT                (30U)
#define TSPC_GRP_OBE1_OBE30_WIDTH                (1U)
#define TSPC_GRP_OBE1_OBE30(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE1_OBE30_SHIFT)) & TSPC_GRP_OBE1_OBE30_MASK)

#define TSPC_GRP_OBE1_OBE31_MASK                 (0x80000000U)
#define TSPC_GRP_OBE1_OBE31_SHIFT                (31U)
#define TSPC_GRP_OBE1_OBE31_WIDTH                (1U)
#define TSPC_GRP_OBE1_OBE31(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE1_OBE31_SHIFT)) & TSPC_GRP_OBE1_OBE31_MASK)
/*! @} */

/*! @name GRP_OBE2 - Group OBE */
/*! @{ */

#define TSPC_GRP_OBE2_OBE32_MASK                 (0x1U)
#define TSPC_GRP_OBE2_OBE32_SHIFT                (0U)
#define TSPC_GRP_OBE2_OBE32_WIDTH                (1U)
#define TSPC_GRP_OBE2_OBE32(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE2_OBE32_SHIFT)) & TSPC_GRP_OBE2_OBE32_MASK)

#define TSPC_GRP_OBE2_OBE33_MASK                 (0x2U)
#define TSPC_GRP_OBE2_OBE33_SHIFT                (1U)
#define TSPC_GRP_OBE2_OBE33_WIDTH                (1U)
#define TSPC_GRP_OBE2_OBE33(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE2_OBE33_SHIFT)) & TSPC_GRP_OBE2_OBE33_MASK)

#define TSPC_GRP_OBE2_OBE34_MASK                 (0x4U)
#define TSPC_GRP_OBE2_OBE34_SHIFT                (2U)
#define TSPC_GRP_OBE2_OBE34_WIDTH                (1U)
#define TSPC_GRP_OBE2_OBE34(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE2_OBE34_SHIFT)) & TSPC_GRP_OBE2_OBE34_MASK)

#define TSPC_GRP_OBE2_OBE35_MASK                 (0x8U)
#define TSPC_GRP_OBE2_OBE35_SHIFT                (3U)
#define TSPC_GRP_OBE2_OBE35_WIDTH                (1U)
#define TSPC_GRP_OBE2_OBE35(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE2_OBE35_SHIFT)) & TSPC_GRP_OBE2_OBE35_MASK)

#define TSPC_GRP_OBE2_OBE36_MASK                 (0x10U)
#define TSPC_GRP_OBE2_OBE36_SHIFT                (4U)
#define TSPC_GRP_OBE2_OBE36_WIDTH                (1U)
#define TSPC_GRP_OBE2_OBE36(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE2_OBE36_SHIFT)) & TSPC_GRP_OBE2_OBE36_MASK)

#define TSPC_GRP_OBE2_OBE37_MASK                 (0x20U)
#define TSPC_GRP_OBE2_OBE37_SHIFT                (5U)
#define TSPC_GRP_OBE2_OBE37_WIDTH                (1U)
#define TSPC_GRP_OBE2_OBE37(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE2_OBE37_SHIFT)) & TSPC_GRP_OBE2_OBE37_MASK)

#define TSPC_GRP_OBE2_OBE38_MASK                 (0x40U)
#define TSPC_GRP_OBE2_OBE38_SHIFT                (6U)
#define TSPC_GRP_OBE2_OBE38_WIDTH                (1U)
#define TSPC_GRP_OBE2_OBE38(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE2_OBE38_SHIFT)) & TSPC_GRP_OBE2_OBE38_MASK)

#define TSPC_GRP_OBE2_OBE39_MASK                 (0x80U)
#define TSPC_GRP_OBE2_OBE39_SHIFT                (7U)
#define TSPC_GRP_OBE2_OBE39_WIDTH                (1U)
#define TSPC_GRP_OBE2_OBE39(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE2_OBE39_SHIFT)) & TSPC_GRP_OBE2_OBE39_MASK)

#define TSPC_GRP_OBE2_OBE40_MASK                 (0x100U)
#define TSPC_GRP_OBE2_OBE40_SHIFT                (8U)
#define TSPC_GRP_OBE2_OBE40_WIDTH                (1U)
#define TSPC_GRP_OBE2_OBE40(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE2_OBE40_SHIFT)) & TSPC_GRP_OBE2_OBE40_MASK)

#define TSPC_GRP_OBE2_OBE41_MASK                 (0x200U)
#define TSPC_GRP_OBE2_OBE41_SHIFT                (9U)
#define TSPC_GRP_OBE2_OBE41_WIDTH                (1U)
#define TSPC_GRP_OBE2_OBE41(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE2_OBE41_SHIFT)) & TSPC_GRP_OBE2_OBE41_MASK)

#define TSPC_GRP_OBE2_OBE42_MASK                 (0x400U)
#define TSPC_GRP_OBE2_OBE42_SHIFT                (10U)
#define TSPC_GRP_OBE2_OBE42_WIDTH                (1U)
#define TSPC_GRP_OBE2_OBE42(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE2_OBE42_SHIFT)) & TSPC_GRP_OBE2_OBE42_MASK)

#define TSPC_GRP_OBE2_OBE43_MASK                 (0x800U)
#define TSPC_GRP_OBE2_OBE43_SHIFT                (11U)
#define TSPC_GRP_OBE2_OBE43_WIDTH                (1U)
#define TSPC_GRP_OBE2_OBE43(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE2_OBE43_SHIFT)) & TSPC_GRP_OBE2_OBE43_MASK)

#define TSPC_GRP_OBE2_OBE44_MASK                 (0x1000U)
#define TSPC_GRP_OBE2_OBE44_SHIFT                (12U)
#define TSPC_GRP_OBE2_OBE44_WIDTH                (1U)
#define TSPC_GRP_OBE2_OBE44(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE2_OBE44_SHIFT)) & TSPC_GRP_OBE2_OBE44_MASK)

#define TSPC_GRP_OBE2_OBE45_MASK                 (0x2000U)
#define TSPC_GRP_OBE2_OBE45_SHIFT                (13U)
#define TSPC_GRP_OBE2_OBE45_WIDTH                (1U)
#define TSPC_GRP_OBE2_OBE45(x)                   (((uint32_t)(((uint32_t)(x)) << TSPC_GRP_OBE2_OBE45_SHIFT)) & TSPC_GRP_OBE2_OBE45_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group TSPC_Register_Masks */

/*!
 * @}
 */ /* end of group TSPC_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_TSPC_H_) */
