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
 * @file S32K344_ERM.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_ERM
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
#if !defined(S32K344_ERM_H_)  /* Check if memory map has not been already included */
#define S32K344_ERM_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- ERM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ERM_Peripheral_Access_Layer ERM Peripheral Access Layer
 * @{
 */

/** ERM - Register Layout Typedef */
typedef struct {
  __IO uint32_t CR0;                               /**< ERM Configuration Register 0, offset: 0x0 */
  __IO uint32_t CR1;                               /**< ERM Configuration Register 1, offset: 0x4 */
  __IO uint32_t CR2;                               /**< ERM Configuration Register 2, offset: 0x8 */
  uint8_t RESERVED_0[4];
  __IO uint32_t SR0;                               /**< ERM Status Register 0, offset: 0x10 */
  __IO uint32_t SR1;                               /**< ERM Status Register 1, offset: 0x14 */
  __IO uint32_t SR2;                               /**< ERM Status Register 2, offset: 0x18 */
  uint8_t RESERVED_1[228];
  __I  uint32_t EAR0;                              /**< ERM Memory 0 Error Address Register, offset: 0x100 */
  __I  uint32_t SYN0;                              /**< ERM Memory 0 Syndrome Register, offset: 0x104 */
  __IO uint32_t CORR_ERR_CNT0;                     /**< ERM Memory 0 Correctable Error Count Register, offset: 0x108 */
  uint8_t RESERVED_2[4];
  __I  uint32_t EAR1;                              /**< ERM Memory 1 Error Address Register, offset: 0x110 */
  __I  uint32_t SYN1;                              /**< ERM Memory 1 Syndrome Register, offset: 0x114 */
  __IO uint32_t CORR_ERR_CNT1;                     /**< ERM Memory 1 Correctable Error Count Register, offset: 0x118 */
  uint8_t RESERVED_3[12];
  __IO uint32_t CORR_ERR_CNT2;                     /**< ERM Memory 2 Correctable Error Count Register, offset: 0x128 */
  uint8_t RESERVED_4[12];
  __IO uint32_t CORR_ERR_CNT3;                     /**< ERM Memory 3 Correctable Error Count Register, offset: 0x138 */
  uint8_t RESERVED_5[12];
  __IO uint32_t CORR_ERR_CNT4;                     /**< ERM Memory 4 Correctable Error Count Register, offset: 0x148 */
  uint8_t RESERVED_6[12];
  __IO uint32_t CORR_ERR_CNT5;                     /**< ERM Memory 5 Correctable Error Count Register, offset: 0x158 */
  uint8_t RESERVED_7[12];
  __IO uint32_t CORR_ERR_CNT6;                     /**< ERM Memory 6 Correctable Error Count Register, offset: 0x168 */
  uint8_t RESERVED_8[12];
  __IO uint32_t CORR_ERR_CNT7;                     /**< ERM Memory 7 Correctable Error Count Register, offset: 0x178 */
  uint8_t RESERVED_9[12];
  __IO uint32_t CORR_ERR_CNT8;                     /**< ERM Memory 8 Correctable Error Count Register, offset: 0x188 */
  uint8_t RESERVED_10[12];
  __IO uint32_t CORR_ERR_CNT9;                     /**< ERM Memory 9 Correctable Error Count Register, offset: 0x198 */
  uint8_t RESERVED_11[4];
  __I  uint32_t EAR10;                             /**< ERM Memory 10 Error Address Register, offset: 0x1A0 */
  __I  uint32_t SYN10;                             /**< ERM Memory 10 Syndrome Register, offset: 0x1A4 */
  __IO uint32_t CORR_ERR_CNT10;                    /**< ERM Memory 10 Correctable Error Count Register, offset: 0x1A8 */
  uint8_t RESERVED_12[4];
  __I  uint32_t EAR11;                             /**< ERM Memory 11 Error Address Register, offset: 0x1B0 */
  __I  uint32_t SYN11;                             /**< ERM Memory 11 Syndrome Register, offset: 0x1B4 */
  __IO uint32_t CORR_ERR_CNT11;                    /**< ERM Memory 11 Correctable Error Count Register, offset: 0x1B8 */
  uint8_t RESERVED_13[4];
  __I  uint32_t EAR12;                             /**< ERM Memory 12 Error Address Register, offset: 0x1C0 */
  __I  uint32_t SYN12;                             /**< ERM Memory 12 Syndrome Register, offset: 0x1C4 */
  __IO uint32_t CORR_ERR_CNT12;                    /**< ERM Memory 12 Correctable Error Count Register, offset: 0x1C8 */
  uint8_t RESERVED_14[4];
  __I  uint32_t EAR13;                             /**< ERM Memory 13 Error Address Register, offset: 0x1D0 */
  __I  uint32_t SYN13;                             /**< ERM Memory 13 Syndrome Register, offset: 0x1D4 */
  __IO uint32_t CORR_ERR_CNT13;                    /**< ERM Memory 13 Correctable Error Count Register, offset: 0x1D8 */
  uint8_t RESERVED_15[4];
  __I  uint32_t EAR14;                             /**< ERM Memory 14 Error Address Register, offset: 0x1E0 */
  __I  uint32_t SYN14;                             /**< ERM Memory 14 Syndrome Register, offset: 0x1E4 */
  __IO uint32_t CORR_ERR_CNT14;                    /**< ERM Memory 14 Correctable Error Count Register, offset: 0x1E8 */
  uint8_t RESERVED_16[4];
  __I  uint32_t EAR15;                             /**< ERM Memory 15 Error Address Register, offset: 0x1F0 */
  __I  uint32_t SYN15;                             /**< ERM Memory 15 Syndrome Register, offset: 0x1F4 */
  __IO uint32_t CORR_ERR_CNT15;                    /**< ERM Memory 15 Correctable Error Count Register, offset: 0x1F8 */
  uint8_t RESERVED_17[4];
  __I  uint32_t EAR16;                             /**< ERM Memory 16 Error Address Register, offset: 0x200 */
  __I  uint32_t SYN16;                             /**< ERM Memory 16 Syndrome Register, offset: 0x204 */
  __IO uint32_t CORR_ERR_CNT16;                    /**< ERM Memory 16 Correctable Error Count Register, offset: 0x208 */
  uint8_t RESERVED_18[4];
  __I  uint32_t EAR17;                             /**< ERM Memory 17 Error Address Register, offset: 0x210 */
  uint8_t RESERVED_19[4];
  __IO uint32_t CORR_ERR_CNT17;                    /**< ERM Memory 17 Correctable Error Count Register, offset: 0x218 */
  uint8_t RESERVED_20[4];
  __I  uint32_t EAR18;                             /**< ERM Memory 18 Error Address Register, offset: 0x220 */
  uint8_t RESERVED_21[4];
  __IO uint32_t CORR_ERR_CNT18;                    /**< ERM Memory 18 Correctable Error Count Register, offset: 0x228 */
  uint8_t RESERVED_22[4];
  __I  uint32_t EAR19;                             /**< ERM Memory 19 Error Address Register, offset: 0x230 */
  uint8_t RESERVED_23[4];
  __IO uint32_t CORR_ERR_CNT19;                    /**< ERM Memory 19 Correctable Error Count Register, offset: 0x238 */
} ERM_Type, *ERM_MemMapPtr;

/** Number of instances of the ERM module. */
#define ERM_INSTANCE_COUNT                       (1u)

/* ERM - Peripheral instance base addresses */
/** Peripheral ERM base address */
#define IP_ERM_BASE                              (0x4025C000u)
/** Peripheral ERM base pointer */
#define IP_ERM                                   ((ERM_Type *)IP_ERM_BASE)
/** Array initializer of ERM peripheral base addresses */
#define IP_ERM_BASE_ADDRS                        { IP_ERM_BASE }
/** Array initializer of ERM peripheral base pointers */
#define IP_ERM_BASE_PTRS                         { IP_ERM }

/* ----------------------------------------------------------------------------
   -- ERM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ERM_Register_Masks ERM Register Masks
 * @{
 */

/*! @name CR0 - ERM Configuration Register 0 */
/*! @{ */

#define ERM_CR0_ENCIE7_MASK                      (0x4U)
#define ERM_CR0_ENCIE7_SHIFT                     (2U)
#define ERM_CR0_ENCIE7_WIDTH                     (1U)
#define ERM_CR0_ENCIE7(x)                        (((uint32_t)(((uint32_t)(x)) << ERM_CR0_ENCIE7_SHIFT)) & ERM_CR0_ENCIE7_MASK)

#define ERM_CR0_ESCIE7_MASK                      (0x8U)
#define ERM_CR0_ESCIE7_SHIFT                     (3U)
#define ERM_CR0_ESCIE7_WIDTH                     (1U)
#define ERM_CR0_ESCIE7(x)                        (((uint32_t)(((uint32_t)(x)) << ERM_CR0_ESCIE7_SHIFT)) & ERM_CR0_ESCIE7_MASK)

#define ERM_CR0_ENCIE6_MASK                      (0x40U)
#define ERM_CR0_ENCIE6_SHIFT                     (6U)
#define ERM_CR0_ENCIE6_WIDTH                     (1U)
#define ERM_CR0_ENCIE6(x)                        (((uint32_t)(((uint32_t)(x)) << ERM_CR0_ENCIE6_SHIFT)) & ERM_CR0_ENCIE6_MASK)

#define ERM_CR0_ESCIE6_MASK                      (0x80U)
#define ERM_CR0_ESCIE6_SHIFT                     (7U)
#define ERM_CR0_ESCIE6_WIDTH                     (1U)
#define ERM_CR0_ESCIE6(x)                        (((uint32_t)(((uint32_t)(x)) << ERM_CR0_ESCIE6_SHIFT)) & ERM_CR0_ESCIE6_MASK)

#define ERM_CR0_ENCIE5_MASK                      (0x400U)
#define ERM_CR0_ENCIE5_SHIFT                     (10U)
#define ERM_CR0_ENCIE5_WIDTH                     (1U)
#define ERM_CR0_ENCIE5(x)                        (((uint32_t)(((uint32_t)(x)) << ERM_CR0_ENCIE5_SHIFT)) & ERM_CR0_ENCIE5_MASK)

#define ERM_CR0_ESCIE5_MASK                      (0x800U)
#define ERM_CR0_ESCIE5_SHIFT                     (11U)
#define ERM_CR0_ESCIE5_WIDTH                     (1U)
#define ERM_CR0_ESCIE5(x)                        (((uint32_t)(((uint32_t)(x)) << ERM_CR0_ESCIE5_SHIFT)) & ERM_CR0_ESCIE5_MASK)

#define ERM_CR0_ENCIE4_MASK                      (0x4000U)
#define ERM_CR0_ENCIE4_SHIFT                     (14U)
#define ERM_CR0_ENCIE4_WIDTH                     (1U)
#define ERM_CR0_ENCIE4(x)                        (((uint32_t)(((uint32_t)(x)) << ERM_CR0_ENCIE4_SHIFT)) & ERM_CR0_ENCIE4_MASK)

#define ERM_CR0_ESCIE4_MASK                      (0x8000U)
#define ERM_CR0_ESCIE4_SHIFT                     (15U)
#define ERM_CR0_ESCIE4_WIDTH                     (1U)
#define ERM_CR0_ESCIE4(x)                        (((uint32_t)(((uint32_t)(x)) << ERM_CR0_ESCIE4_SHIFT)) & ERM_CR0_ESCIE4_MASK)

#define ERM_CR0_ENCIE3_MASK                      (0x40000U)
#define ERM_CR0_ENCIE3_SHIFT                     (18U)
#define ERM_CR0_ENCIE3_WIDTH                     (1U)
#define ERM_CR0_ENCIE3(x)                        (((uint32_t)(((uint32_t)(x)) << ERM_CR0_ENCIE3_SHIFT)) & ERM_CR0_ENCIE3_MASK)

#define ERM_CR0_ESCIE3_MASK                      (0x80000U)
#define ERM_CR0_ESCIE3_SHIFT                     (19U)
#define ERM_CR0_ESCIE3_WIDTH                     (1U)
#define ERM_CR0_ESCIE3(x)                        (((uint32_t)(((uint32_t)(x)) << ERM_CR0_ESCIE3_SHIFT)) & ERM_CR0_ESCIE3_MASK)

#define ERM_CR0_ENCIE2_MASK                      (0x400000U)
#define ERM_CR0_ENCIE2_SHIFT                     (22U)
#define ERM_CR0_ENCIE2_WIDTH                     (1U)
#define ERM_CR0_ENCIE2(x)                        (((uint32_t)(((uint32_t)(x)) << ERM_CR0_ENCIE2_SHIFT)) & ERM_CR0_ENCIE2_MASK)

#define ERM_CR0_ESCIE2_MASK                      (0x800000U)
#define ERM_CR0_ESCIE2_SHIFT                     (23U)
#define ERM_CR0_ESCIE2_WIDTH                     (1U)
#define ERM_CR0_ESCIE2(x)                        (((uint32_t)(((uint32_t)(x)) << ERM_CR0_ESCIE2_SHIFT)) & ERM_CR0_ESCIE2_MASK)

#define ERM_CR0_ENCIE1_MASK                      (0x4000000U)
#define ERM_CR0_ENCIE1_SHIFT                     (26U)
#define ERM_CR0_ENCIE1_WIDTH                     (1U)
#define ERM_CR0_ENCIE1(x)                        (((uint32_t)(((uint32_t)(x)) << ERM_CR0_ENCIE1_SHIFT)) & ERM_CR0_ENCIE1_MASK)

#define ERM_CR0_ESCIE1_MASK                      (0x8000000U)
#define ERM_CR0_ESCIE1_SHIFT                     (27U)
#define ERM_CR0_ESCIE1_WIDTH                     (1U)
#define ERM_CR0_ESCIE1(x)                        (((uint32_t)(((uint32_t)(x)) << ERM_CR0_ESCIE1_SHIFT)) & ERM_CR0_ESCIE1_MASK)

#define ERM_CR0_ENCIE0_MASK                      (0x40000000U)
#define ERM_CR0_ENCIE0_SHIFT                     (30U)
#define ERM_CR0_ENCIE0_WIDTH                     (1U)
#define ERM_CR0_ENCIE0(x)                        (((uint32_t)(((uint32_t)(x)) << ERM_CR0_ENCIE0_SHIFT)) & ERM_CR0_ENCIE0_MASK)

#define ERM_CR0_ESCIE0_MASK                      (0x80000000U)
#define ERM_CR0_ESCIE0_SHIFT                     (31U)
#define ERM_CR0_ESCIE0_WIDTH                     (1U)
#define ERM_CR0_ESCIE0(x)                        (((uint32_t)(((uint32_t)(x)) << ERM_CR0_ESCIE0_SHIFT)) & ERM_CR0_ESCIE0_MASK)
/*! @} */

/*! @name CR1 - ERM Configuration Register 1 */
/*! @{ */

#define ERM_CR1_ENCIE15_MASK                     (0x4U)
#define ERM_CR1_ENCIE15_SHIFT                    (2U)
#define ERM_CR1_ENCIE15_WIDTH                    (1U)
#define ERM_CR1_ENCIE15(x)                       (((uint32_t)(((uint32_t)(x)) << ERM_CR1_ENCIE15_SHIFT)) & ERM_CR1_ENCIE15_MASK)

#define ERM_CR1_ESCIE15_MASK                     (0x8U)
#define ERM_CR1_ESCIE15_SHIFT                    (3U)
#define ERM_CR1_ESCIE15_WIDTH                    (1U)
#define ERM_CR1_ESCIE15(x)                       (((uint32_t)(((uint32_t)(x)) << ERM_CR1_ESCIE15_SHIFT)) & ERM_CR1_ESCIE15_MASK)

#define ERM_CR1_ENCIE14_MASK                     (0x40U)
#define ERM_CR1_ENCIE14_SHIFT                    (6U)
#define ERM_CR1_ENCIE14_WIDTH                    (1U)
#define ERM_CR1_ENCIE14(x)                       (((uint32_t)(((uint32_t)(x)) << ERM_CR1_ENCIE14_SHIFT)) & ERM_CR1_ENCIE14_MASK)

#define ERM_CR1_ESCIE14_MASK                     (0x80U)
#define ERM_CR1_ESCIE14_SHIFT                    (7U)
#define ERM_CR1_ESCIE14_WIDTH                    (1U)
#define ERM_CR1_ESCIE14(x)                       (((uint32_t)(((uint32_t)(x)) << ERM_CR1_ESCIE14_SHIFT)) & ERM_CR1_ESCIE14_MASK)

#define ERM_CR1_ENCIE13_MASK                     (0x400U)
#define ERM_CR1_ENCIE13_SHIFT                    (10U)
#define ERM_CR1_ENCIE13_WIDTH                    (1U)
#define ERM_CR1_ENCIE13(x)                       (((uint32_t)(((uint32_t)(x)) << ERM_CR1_ENCIE13_SHIFT)) & ERM_CR1_ENCIE13_MASK)

#define ERM_CR1_ESCIE13_MASK                     (0x800U)
#define ERM_CR1_ESCIE13_SHIFT                    (11U)
#define ERM_CR1_ESCIE13_WIDTH                    (1U)
#define ERM_CR1_ESCIE13(x)                       (((uint32_t)(((uint32_t)(x)) << ERM_CR1_ESCIE13_SHIFT)) & ERM_CR1_ESCIE13_MASK)

#define ERM_CR1_ENCIE12_MASK                     (0x4000U)
#define ERM_CR1_ENCIE12_SHIFT                    (14U)
#define ERM_CR1_ENCIE12_WIDTH                    (1U)
#define ERM_CR1_ENCIE12(x)                       (((uint32_t)(((uint32_t)(x)) << ERM_CR1_ENCIE12_SHIFT)) & ERM_CR1_ENCIE12_MASK)

#define ERM_CR1_ESCIE12_MASK                     (0x8000U)
#define ERM_CR1_ESCIE12_SHIFT                    (15U)
#define ERM_CR1_ESCIE12_WIDTH                    (1U)
#define ERM_CR1_ESCIE12(x)                       (((uint32_t)(((uint32_t)(x)) << ERM_CR1_ESCIE12_SHIFT)) & ERM_CR1_ESCIE12_MASK)

#define ERM_CR1_ENCIE11_MASK                     (0x40000U)
#define ERM_CR1_ENCIE11_SHIFT                    (18U)
#define ERM_CR1_ENCIE11_WIDTH                    (1U)
#define ERM_CR1_ENCIE11(x)                       (((uint32_t)(((uint32_t)(x)) << ERM_CR1_ENCIE11_SHIFT)) & ERM_CR1_ENCIE11_MASK)

#define ERM_CR1_ESCIE11_MASK                     (0x80000U)
#define ERM_CR1_ESCIE11_SHIFT                    (19U)
#define ERM_CR1_ESCIE11_WIDTH                    (1U)
#define ERM_CR1_ESCIE11(x)                       (((uint32_t)(((uint32_t)(x)) << ERM_CR1_ESCIE11_SHIFT)) & ERM_CR1_ESCIE11_MASK)

#define ERM_CR1_ENCIE10_MASK                     (0x400000U)
#define ERM_CR1_ENCIE10_SHIFT                    (22U)
#define ERM_CR1_ENCIE10_WIDTH                    (1U)
#define ERM_CR1_ENCIE10(x)                       (((uint32_t)(((uint32_t)(x)) << ERM_CR1_ENCIE10_SHIFT)) & ERM_CR1_ENCIE10_MASK)

#define ERM_CR1_ESCIE10_MASK                     (0x800000U)
#define ERM_CR1_ESCIE10_SHIFT                    (23U)
#define ERM_CR1_ESCIE10_WIDTH                    (1U)
#define ERM_CR1_ESCIE10(x)                       (((uint32_t)(((uint32_t)(x)) << ERM_CR1_ESCIE10_SHIFT)) & ERM_CR1_ESCIE10_MASK)

#define ERM_CR1_ENCIE9_MASK                      (0x4000000U)
#define ERM_CR1_ENCIE9_SHIFT                     (26U)
#define ERM_CR1_ENCIE9_WIDTH                     (1U)
#define ERM_CR1_ENCIE9(x)                        (((uint32_t)(((uint32_t)(x)) << ERM_CR1_ENCIE9_SHIFT)) & ERM_CR1_ENCIE9_MASK)

#define ERM_CR1_ESCIE9_MASK                      (0x8000000U)
#define ERM_CR1_ESCIE9_SHIFT                     (27U)
#define ERM_CR1_ESCIE9_WIDTH                     (1U)
#define ERM_CR1_ESCIE9(x)                        (((uint32_t)(((uint32_t)(x)) << ERM_CR1_ESCIE9_SHIFT)) & ERM_CR1_ESCIE9_MASK)

#define ERM_CR1_ENCIE8_MASK                      (0x40000000U)
#define ERM_CR1_ENCIE8_SHIFT                     (30U)
#define ERM_CR1_ENCIE8_WIDTH                     (1U)
#define ERM_CR1_ENCIE8(x)                        (((uint32_t)(((uint32_t)(x)) << ERM_CR1_ENCIE8_SHIFT)) & ERM_CR1_ENCIE8_MASK)

#define ERM_CR1_ESCIE8_MASK                      (0x80000000U)
#define ERM_CR1_ESCIE8_SHIFT                     (31U)
#define ERM_CR1_ESCIE8_WIDTH                     (1U)
#define ERM_CR1_ESCIE8(x)                        (((uint32_t)(((uint32_t)(x)) << ERM_CR1_ESCIE8_SHIFT)) & ERM_CR1_ESCIE8_MASK)
/*! @} */

/*! @name CR2 - ERM Configuration Register 2 */
/*! @{ */

#define ERM_CR2_ENCIE19_MASK                     (0x40000U)
#define ERM_CR2_ENCIE19_SHIFT                    (18U)
#define ERM_CR2_ENCIE19_WIDTH                    (1U)
#define ERM_CR2_ENCIE19(x)                       (((uint32_t)(((uint32_t)(x)) << ERM_CR2_ENCIE19_SHIFT)) & ERM_CR2_ENCIE19_MASK)

#define ERM_CR2_ESCIE19_MASK                     (0x80000U)
#define ERM_CR2_ESCIE19_SHIFT                    (19U)
#define ERM_CR2_ESCIE19_WIDTH                    (1U)
#define ERM_CR2_ESCIE19(x)                       (((uint32_t)(((uint32_t)(x)) << ERM_CR2_ESCIE19_SHIFT)) & ERM_CR2_ESCIE19_MASK)

#define ERM_CR2_ENCIE18_MASK                     (0x400000U)
#define ERM_CR2_ENCIE18_SHIFT                    (22U)
#define ERM_CR2_ENCIE18_WIDTH                    (1U)
#define ERM_CR2_ENCIE18(x)                       (((uint32_t)(((uint32_t)(x)) << ERM_CR2_ENCIE18_SHIFT)) & ERM_CR2_ENCIE18_MASK)

#define ERM_CR2_ESCIE18_MASK                     (0x800000U)
#define ERM_CR2_ESCIE18_SHIFT                    (23U)
#define ERM_CR2_ESCIE18_WIDTH                    (1U)
#define ERM_CR2_ESCIE18(x)                       (((uint32_t)(((uint32_t)(x)) << ERM_CR2_ESCIE18_SHIFT)) & ERM_CR2_ESCIE18_MASK)

#define ERM_CR2_ENCIE17_MASK                     (0x4000000U)
#define ERM_CR2_ENCIE17_SHIFT                    (26U)
#define ERM_CR2_ENCIE17_WIDTH                    (1U)
#define ERM_CR2_ENCIE17(x)                       (((uint32_t)(((uint32_t)(x)) << ERM_CR2_ENCIE17_SHIFT)) & ERM_CR2_ENCIE17_MASK)

#define ERM_CR2_ESCIE17_MASK                     (0x8000000U)
#define ERM_CR2_ESCIE17_SHIFT                    (27U)
#define ERM_CR2_ESCIE17_WIDTH                    (1U)
#define ERM_CR2_ESCIE17(x)                       (((uint32_t)(((uint32_t)(x)) << ERM_CR2_ESCIE17_SHIFT)) & ERM_CR2_ESCIE17_MASK)

#define ERM_CR2_ENCIE16_MASK                     (0x40000000U)
#define ERM_CR2_ENCIE16_SHIFT                    (30U)
#define ERM_CR2_ENCIE16_WIDTH                    (1U)
#define ERM_CR2_ENCIE16(x)                       (((uint32_t)(((uint32_t)(x)) << ERM_CR2_ENCIE16_SHIFT)) & ERM_CR2_ENCIE16_MASK)

#define ERM_CR2_ESCIE16_MASK                     (0x80000000U)
#define ERM_CR2_ESCIE16_SHIFT                    (31U)
#define ERM_CR2_ESCIE16_WIDTH                    (1U)
#define ERM_CR2_ESCIE16(x)                       (((uint32_t)(((uint32_t)(x)) << ERM_CR2_ESCIE16_SHIFT)) & ERM_CR2_ESCIE16_MASK)
/*! @} */

/*! @name SR0 - ERM Status Register 0 */
/*! @{ */

#define ERM_SR0_NCE7_MASK                        (0x4U)
#define ERM_SR0_NCE7_SHIFT                       (2U)
#define ERM_SR0_NCE7_WIDTH                       (1U)
#define ERM_SR0_NCE7(x)                          (((uint32_t)(((uint32_t)(x)) << ERM_SR0_NCE7_SHIFT)) & ERM_SR0_NCE7_MASK)

#define ERM_SR0_SBC7_MASK                        (0x8U)
#define ERM_SR0_SBC7_SHIFT                       (3U)
#define ERM_SR0_SBC7_WIDTH                       (1U)
#define ERM_SR0_SBC7(x)                          (((uint32_t)(((uint32_t)(x)) << ERM_SR0_SBC7_SHIFT)) & ERM_SR0_SBC7_MASK)

#define ERM_SR0_NCE6_MASK                        (0x40U)
#define ERM_SR0_NCE6_SHIFT                       (6U)
#define ERM_SR0_NCE6_WIDTH                       (1U)
#define ERM_SR0_NCE6(x)                          (((uint32_t)(((uint32_t)(x)) << ERM_SR0_NCE6_SHIFT)) & ERM_SR0_NCE6_MASK)

#define ERM_SR0_SBC6_MASK                        (0x80U)
#define ERM_SR0_SBC6_SHIFT                       (7U)
#define ERM_SR0_SBC6_WIDTH                       (1U)
#define ERM_SR0_SBC6(x)                          (((uint32_t)(((uint32_t)(x)) << ERM_SR0_SBC6_SHIFT)) & ERM_SR0_SBC6_MASK)

#define ERM_SR0_NCE5_MASK                        (0x400U)
#define ERM_SR0_NCE5_SHIFT                       (10U)
#define ERM_SR0_NCE5_WIDTH                       (1U)
#define ERM_SR0_NCE5(x)                          (((uint32_t)(((uint32_t)(x)) << ERM_SR0_NCE5_SHIFT)) & ERM_SR0_NCE5_MASK)

#define ERM_SR0_SBC5_MASK                        (0x800U)
#define ERM_SR0_SBC5_SHIFT                       (11U)
#define ERM_SR0_SBC5_WIDTH                       (1U)
#define ERM_SR0_SBC5(x)                          (((uint32_t)(((uint32_t)(x)) << ERM_SR0_SBC5_SHIFT)) & ERM_SR0_SBC5_MASK)

#define ERM_SR0_NCE4_MASK                        (0x4000U)
#define ERM_SR0_NCE4_SHIFT                       (14U)
#define ERM_SR0_NCE4_WIDTH                       (1U)
#define ERM_SR0_NCE4(x)                          (((uint32_t)(((uint32_t)(x)) << ERM_SR0_NCE4_SHIFT)) & ERM_SR0_NCE4_MASK)

#define ERM_SR0_SBC4_MASK                        (0x8000U)
#define ERM_SR0_SBC4_SHIFT                       (15U)
#define ERM_SR0_SBC4_WIDTH                       (1U)
#define ERM_SR0_SBC4(x)                          (((uint32_t)(((uint32_t)(x)) << ERM_SR0_SBC4_SHIFT)) & ERM_SR0_SBC4_MASK)

#define ERM_SR0_NCE3_MASK                        (0x40000U)
#define ERM_SR0_NCE3_SHIFT                       (18U)
#define ERM_SR0_NCE3_WIDTH                       (1U)
#define ERM_SR0_NCE3(x)                          (((uint32_t)(((uint32_t)(x)) << ERM_SR0_NCE3_SHIFT)) & ERM_SR0_NCE3_MASK)

#define ERM_SR0_SBC3_MASK                        (0x80000U)
#define ERM_SR0_SBC3_SHIFT                       (19U)
#define ERM_SR0_SBC3_WIDTH                       (1U)
#define ERM_SR0_SBC3(x)                          (((uint32_t)(((uint32_t)(x)) << ERM_SR0_SBC3_SHIFT)) & ERM_SR0_SBC3_MASK)

#define ERM_SR0_NCE2_MASK                        (0x400000U)
#define ERM_SR0_NCE2_SHIFT                       (22U)
#define ERM_SR0_NCE2_WIDTH                       (1U)
#define ERM_SR0_NCE2(x)                          (((uint32_t)(((uint32_t)(x)) << ERM_SR0_NCE2_SHIFT)) & ERM_SR0_NCE2_MASK)

#define ERM_SR0_SBC2_MASK                        (0x800000U)
#define ERM_SR0_SBC2_SHIFT                       (23U)
#define ERM_SR0_SBC2_WIDTH                       (1U)
#define ERM_SR0_SBC2(x)                          (((uint32_t)(((uint32_t)(x)) << ERM_SR0_SBC2_SHIFT)) & ERM_SR0_SBC2_MASK)

#define ERM_SR0_NCE1_MASK                        (0x4000000U)
#define ERM_SR0_NCE1_SHIFT                       (26U)
#define ERM_SR0_NCE1_WIDTH                       (1U)
#define ERM_SR0_NCE1(x)                          (((uint32_t)(((uint32_t)(x)) << ERM_SR0_NCE1_SHIFT)) & ERM_SR0_NCE1_MASK)

#define ERM_SR0_SBC1_MASK                        (0x8000000U)
#define ERM_SR0_SBC1_SHIFT                       (27U)
#define ERM_SR0_SBC1_WIDTH                       (1U)
#define ERM_SR0_SBC1(x)                          (((uint32_t)(((uint32_t)(x)) << ERM_SR0_SBC1_SHIFT)) & ERM_SR0_SBC1_MASK)

#define ERM_SR0_NCE0_MASK                        (0x40000000U)
#define ERM_SR0_NCE0_SHIFT                       (30U)
#define ERM_SR0_NCE0_WIDTH                       (1U)
#define ERM_SR0_NCE0(x)                          (((uint32_t)(((uint32_t)(x)) << ERM_SR0_NCE0_SHIFT)) & ERM_SR0_NCE0_MASK)

#define ERM_SR0_SBC0_MASK                        (0x80000000U)
#define ERM_SR0_SBC0_SHIFT                       (31U)
#define ERM_SR0_SBC0_WIDTH                       (1U)
#define ERM_SR0_SBC0(x)                          (((uint32_t)(((uint32_t)(x)) << ERM_SR0_SBC0_SHIFT)) & ERM_SR0_SBC0_MASK)
/*! @} */

/*! @name SR1 - ERM Status Register 1 */
/*! @{ */

#define ERM_SR1_NCE15_MASK                       (0x4U)
#define ERM_SR1_NCE15_SHIFT                      (2U)
#define ERM_SR1_NCE15_WIDTH                      (1U)
#define ERM_SR1_NCE15(x)                         (((uint32_t)(((uint32_t)(x)) << ERM_SR1_NCE15_SHIFT)) & ERM_SR1_NCE15_MASK)

#define ERM_SR1_SBC15_MASK                       (0x8U)
#define ERM_SR1_SBC15_SHIFT                      (3U)
#define ERM_SR1_SBC15_WIDTH                      (1U)
#define ERM_SR1_SBC15(x)                         (((uint32_t)(((uint32_t)(x)) << ERM_SR1_SBC15_SHIFT)) & ERM_SR1_SBC15_MASK)

#define ERM_SR1_NCE14_MASK                       (0x40U)
#define ERM_SR1_NCE14_SHIFT                      (6U)
#define ERM_SR1_NCE14_WIDTH                      (1U)
#define ERM_SR1_NCE14(x)                         (((uint32_t)(((uint32_t)(x)) << ERM_SR1_NCE14_SHIFT)) & ERM_SR1_NCE14_MASK)

#define ERM_SR1_SBC14_MASK                       (0x80U)
#define ERM_SR1_SBC14_SHIFT                      (7U)
#define ERM_SR1_SBC14_WIDTH                      (1U)
#define ERM_SR1_SBC14(x)                         (((uint32_t)(((uint32_t)(x)) << ERM_SR1_SBC14_SHIFT)) & ERM_SR1_SBC14_MASK)

#define ERM_SR1_NCE13_MASK                       (0x400U)
#define ERM_SR1_NCE13_SHIFT                      (10U)
#define ERM_SR1_NCE13_WIDTH                      (1U)
#define ERM_SR1_NCE13(x)                         (((uint32_t)(((uint32_t)(x)) << ERM_SR1_NCE13_SHIFT)) & ERM_SR1_NCE13_MASK)

#define ERM_SR1_SBC13_MASK                       (0x800U)
#define ERM_SR1_SBC13_SHIFT                      (11U)
#define ERM_SR1_SBC13_WIDTH                      (1U)
#define ERM_SR1_SBC13(x)                         (((uint32_t)(((uint32_t)(x)) << ERM_SR1_SBC13_SHIFT)) & ERM_SR1_SBC13_MASK)

#define ERM_SR1_NCE12_MASK                       (0x4000U)
#define ERM_SR1_NCE12_SHIFT                      (14U)
#define ERM_SR1_NCE12_WIDTH                      (1U)
#define ERM_SR1_NCE12(x)                         (((uint32_t)(((uint32_t)(x)) << ERM_SR1_NCE12_SHIFT)) & ERM_SR1_NCE12_MASK)

#define ERM_SR1_SBC12_MASK                       (0x8000U)
#define ERM_SR1_SBC12_SHIFT                      (15U)
#define ERM_SR1_SBC12_WIDTH                      (1U)
#define ERM_SR1_SBC12(x)                         (((uint32_t)(((uint32_t)(x)) << ERM_SR1_SBC12_SHIFT)) & ERM_SR1_SBC12_MASK)

#define ERM_SR1_NCE11_MASK                       (0x40000U)
#define ERM_SR1_NCE11_SHIFT                      (18U)
#define ERM_SR1_NCE11_WIDTH                      (1U)
#define ERM_SR1_NCE11(x)                         (((uint32_t)(((uint32_t)(x)) << ERM_SR1_NCE11_SHIFT)) & ERM_SR1_NCE11_MASK)

#define ERM_SR1_SBC11_MASK                       (0x80000U)
#define ERM_SR1_SBC11_SHIFT                      (19U)
#define ERM_SR1_SBC11_WIDTH                      (1U)
#define ERM_SR1_SBC11(x)                         (((uint32_t)(((uint32_t)(x)) << ERM_SR1_SBC11_SHIFT)) & ERM_SR1_SBC11_MASK)

#define ERM_SR1_NCE10_MASK                       (0x400000U)
#define ERM_SR1_NCE10_SHIFT                      (22U)
#define ERM_SR1_NCE10_WIDTH                      (1U)
#define ERM_SR1_NCE10(x)                         (((uint32_t)(((uint32_t)(x)) << ERM_SR1_NCE10_SHIFT)) & ERM_SR1_NCE10_MASK)

#define ERM_SR1_SBC10_MASK                       (0x800000U)
#define ERM_SR1_SBC10_SHIFT                      (23U)
#define ERM_SR1_SBC10_WIDTH                      (1U)
#define ERM_SR1_SBC10(x)                         (((uint32_t)(((uint32_t)(x)) << ERM_SR1_SBC10_SHIFT)) & ERM_SR1_SBC10_MASK)

#define ERM_SR1_NCE9_MASK                        (0x4000000U)
#define ERM_SR1_NCE9_SHIFT                       (26U)
#define ERM_SR1_NCE9_WIDTH                       (1U)
#define ERM_SR1_NCE9(x)                          (((uint32_t)(((uint32_t)(x)) << ERM_SR1_NCE9_SHIFT)) & ERM_SR1_NCE9_MASK)

#define ERM_SR1_SBC9_MASK                        (0x8000000U)
#define ERM_SR1_SBC9_SHIFT                       (27U)
#define ERM_SR1_SBC9_WIDTH                       (1U)
#define ERM_SR1_SBC9(x)                          (((uint32_t)(((uint32_t)(x)) << ERM_SR1_SBC9_SHIFT)) & ERM_SR1_SBC9_MASK)

#define ERM_SR1_NCE8_MASK                        (0x40000000U)
#define ERM_SR1_NCE8_SHIFT                       (30U)
#define ERM_SR1_NCE8_WIDTH                       (1U)
#define ERM_SR1_NCE8(x)                          (((uint32_t)(((uint32_t)(x)) << ERM_SR1_NCE8_SHIFT)) & ERM_SR1_NCE8_MASK)

#define ERM_SR1_SBC8_MASK                        (0x80000000U)
#define ERM_SR1_SBC8_SHIFT                       (31U)
#define ERM_SR1_SBC8_WIDTH                       (1U)
#define ERM_SR1_SBC8(x)                          (((uint32_t)(((uint32_t)(x)) << ERM_SR1_SBC8_SHIFT)) & ERM_SR1_SBC8_MASK)
/*! @} */

/*! @name SR2 - ERM Status Register 2 */
/*! @{ */

#define ERM_SR2_NCE19_MASK                       (0x40000U)
#define ERM_SR2_NCE19_SHIFT                      (18U)
#define ERM_SR2_NCE19_WIDTH                      (1U)
#define ERM_SR2_NCE19(x)                         (((uint32_t)(((uint32_t)(x)) << ERM_SR2_NCE19_SHIFT)) & ERM_SR2_NCE19_MASK)

#define ERM_SR2_SBC19_MASK                       (0x80000U)
#define ERM_SR2_SBC19_SHIFT                      (19U)
#define ERM_SR2_SBC19_WIDTH                      (1U)
#define ERM_SR2_SBC19(x)                         (((uint32_t)(((uint32_t)(x)) << ERM_SR2_SBC19_SHIFT)) & ERM_SR2_SBC19_MASK)

#define ERM_SR2_NCE18_MASK                       (0x400000U)
#define ERM_SR2_NCE18_SHIFT                      (22U)
#define ERM_SR2_NCE18_WIDTH                      (1U)
#define ERM_SR2_NCE18(x)                         (((uint32_t)(((uint32_t)(x)) << ERM_SR2_NCE18_SHIFT)) & ERM_SR2_NCE18_MASK)

#define ERM_SR2_SBC18_MASK                       (0x800000U)
#define ERM_SR2_SBC18_SHIFT                      (23U)
#define ERM_SR2_SBC18_WIDTH                      (1U)
#define ERM_SR2_SBC18(x)                         (((uint32_t)(((uint32_t)(x)) << ERM_SR2_SBC18_SHIFT)) & ERM_SR2_SBC18_MASK)

#define ERM_SR2_NCE17_MASK                       (0x4000000U)
#define ERM_SR2_NCE17_SHIFT                      (26U)
#define ERM_SR2_NCE17_WIDTH                      (1U)
#define ERM_SR2_NCE17(x)                         (((uint32_t)(((uint32_t)(x)) << ERM_SR2_NCE17_SHIFT)) & ERM_SR2_NCE17_MASK)

#define ERM_SR2_SBC17_MASK                       (0x8000000U)
#define ERM_SR2_SBC17_SHIFT                      (27U)
#define ERM_SR2_SBC17_WIDTH                      (1U)
#define ERM_SR2_SBC17(x)                         (((uint32_t)(((uint32_t)(x)) << ERM_SR2_SBC17_SHIFT)) & ERM_SR2_SBC17_MASK)

#define ERM_SR2_NCE16_MASK                       (0x40000000U)
#define ERM_SR2_NCE16_SHIFT                      (30U)
#define ERM_SR2_NCE16_WIDTH                      (1U)
#define ERM_SR2_NCE16(x)                         (((uint32_t)(((uint32_t)(x)) << ERM_SR2_NCE16_SHIFT)) & ERM_SR2_NCE16_MASK)

#define ERM_SR2_SBC16_MASK                       (0x80000000U)
#define ERM_SR2_SBC16_SHIFT                      (31U)
#define ERM_SR2_SBC16_WIDTH                      (1U)
#define ERM_SR2_SBC16(x)                         (((uint32_t)(((uint32_t)(x)) << ERM_SR2_SBC16_SHIFT)) & ERM_SR2_SBC16_MASK)
/*! @} */

/*! @name EAR0 - ERM Memory 0 Error Address Register */
/*! @{ */

#define ERM_EAR0_EAR_MASK                        (0xFFFFFFFFU)
#define ERM_EAR0_EAR_SHIFT                       (0U)
#define ERM_EAR0_EAR_WIDTH                       (32U)
#define ERM_EAR0_EAR(x)                          (((uint32_t)(((uint32_t)(x)) << ERM_EAR0_EAR_SHIFT)) & ERM_EAR0_EAR_MASK)
/*! @} */

/*! @name SYN0 - ERM Memory 0 Syndrome Register */
/*! @{ */

#define ERM_SYN0_SYNDROME_MASK                   (0xFF000000U)
#define ERM_SYN0_SYNDROME_SHIFT                  (24U)
#define ERM_SYN0_SYNDROME_WIDTH                  (8U)
#define ERM_SYN0_SYNDROME(x)                     (((uint32_t)(((uint32_t)(x)) << ERM_SYN0_SYNDROME_SHIFT)) & ERM_SYN0_SYNDROME_MASK)
/*! @} */

/*! @name CORR_ERR_CNT0 - ERM Memory 0 Correctable Error Count Register */
/*! @{ */

#define ERM_CORR_ERR_CNT0_COUNT_MASK             (0xFFU)
#define ERM_CORR_ERR_CNT0_COUNT_SHIFT            (0U)
#define ERM_CORR_ERR_CNT0_COUNT_WIDTH            (8U)
#define ERM_CORR_ERR_CNT0_COUNT(x)               (((uint32_t)(((uint32_t)(x)) << ERM_CORR_ERR_CNT0_COUNT_SHIFT)) & ERM_CORR_ERR_CNT0_COUNT_MASK)
/*! @} */

/*! @name EAR1 - ERM Memory 1 Error Address Register */
/*! @{ */

#define ERM_EAR1_EAR_MASK                        (0xFFFFFFFFU)
#define ERM_EAR1_EAR_SHIFT                       (0U)
#define ERM_EAR1_EAR_WIDTH                       (32U)
#define ERM_EAR1_EAR(x)                          (((uint32_t)(((uint32_t)(x)) << ERM_EAR1_EAR_SHIFT)) & ERM_EAR1_EAR_MASK)
/*! @} */

/*! @name SYN1 - ERM Memory 1 Syndrome Register */
/*! @{ */

#define ERM_SYN1_SYNDROME_MASK                   (0xFF000000U)
#define ERM_SYN1_SYNDROME_SHIFT                  (24U)
#define ERM_SYN1_SYNDROME_WIDTH                  (8U)
#define ERM_SYN1_SYNDROME(x)                     (((uint32_t)(((uint32_t)(x)) << ERM_SYN1_SYNDROME_SHIFT)) & ERM_SYN1_SYNDROME_MASK)
/*! @} */

/*! @name CORR_ERR_CNT1 - ERM Memory 1 Correctable Error Count Register */
/*! @{ */

#define ERM_CORR_ERR_CNT1_COUNT_MASK             (0xFFU)
#define ERM_CORR_ERR_CNT1_COUNT_SHIFT            (0U)
#define ERM_CORR_ERR_CNT1_COUNT_WIDTH            (8U)
#define ERM_CORR_ERR_CNT1_COUNT(x)               (((uint32_t)(((uint32_t)(x)) << ERM_CORR_ERR_CNT1_COUNT_SHIFT)) & ERM_CORR_ERR_CNT1_COUNT_MASK)
/*! @} */

/*! @name CORR_ERR_CNT2 - ERM Memory 2 Correctable Error Count Register */
/*! @{ */

#define ERM_CORR_ERR_CNT2_COUNT_MASK             (0xFFU)
#define ERM_CORR_ERR_CNT2_COUNT_SHIFT            (0U)
#define ERM_CORR_ERR_CNT2_COUNT_WIDTH            (8U)
#define ERM_CORR_ERR_CNT2_COUNT(x)               (((uint32_t)(((uint32_t)(x)) << ERM_CORR_ERR_CNT2_COUNT_SHIFT)) & ERM_CORR_ERR_CNT2_COUNT_MASK)
/*! @} */

/*! @name CORR_ERR_CNT3 - ERM Memory 3 Correctable Error Count Register */
/*! @{ */

#define ERM_CORR_ERR_CNT3_COUNT_MASK             (0xFFU)
#define ERM_CORR_ERR_CNT3_COUNT_SHIFT            (0U)
#define ERM_CORR_ERR_CNT3_COUNT_WIDTH            (8U)
#define ERM_CORR_ERR_CNT3_COUNT(x)               (((uint32_t)(((uint32_t)(x)) << ERM_CORR_ERR_CNT3_COUNT_SHIFT)) & ERM_CORR_ERR_CNT3_COUNT_MASK)
/*! @} */

/*! @name CORR_ERR_CNT4 - ERM Memory 4 Correctable Error Count Register */
/*! @{ */

#define ERM_CORR_ERR_CNT4_COUNT_MASK             (0xFFU)
#define ERM_CORR_ERR_CNT4_COUNT_SHIFT            (0U)
#define ERM_CORR_ERR_CNT4_COUNT_WIDTH            (8U)
#define ERM_CORR_ERR_CNT4_COUNT(x)               (((uint32_t)(((uint32_t)(x)) << ERM_CORR_ERR_CNT4_COUNT_SHIFT)) & ERM_CORR_ERR_CNT4_COUNT_MASK)
/*! @} */

/*! @name CORR_ERR_CNT5 - ERM Memory 5 Correctable Error Count Register */
/*! @{ */

#define ERM_CORR_ERR_CNT5_COUNT_MASK             (0xFFU)
#define ERM_CORR_ERR_CNT5_COUNT_SHIFT            (0U)
#define ERM_CORR_ERR_CNT5_COUNT_WIDTH            (8U)
#define ERM_CORR_ERR_CNT5_COUNT(x)               (((uint32_t)(((uint32_t)(x)) << ERM_CORR_ERR_CNT5_COUNT_SHIFT)) & ERM_CORR_ERR_CNT5_COUNT_MASK)
/*! @} */

/*! @name CORR_ERR_CNT6 - ERM Memory 6 Correctable Error Count Register */
/*! @{ */

#define ERM_CORR_ERR_CNT6_COUNT_MASK             (0xFFU)
#define ERM_CORR_ERR_CNT6_COUNT_SHIFT            (0U)
#define ERM_CORR_ERR_CNT6_COUNT_WIDTH            (8U)
#define ERM_CORR_ERR_CNT6_COUNT(x)               (((uint32_t)(((uint32_t)(x)) << ERM_CORR_ERR_CNT6_COUNT_SHIFT)) & ERM_CORR_ERR_CNT6_COUNT_MASK)
/*! @} */

/*! @name CORR_ERR_CNT7 - ERM Memory 7 Correctable Error Count Register */
/*! @{ */

#define ERM_CORR_ERR_CNT7_COUNT_MASK             (0xFFU)
#define ERM_CORR_ERR_CNT7_COUNT_SHIFT            (0U)
#define ERM_CORR_ERR_CNT7_COUNT_WIDTH            (8U)
#define ERM_CORR_ERR_CNT7_COUNT(x)               (((uint32_t)(((uint32_t)(x)) << ERM_CORR_ERR_CNT7_COUNT_SHIFT)) & ERM_CORR_ERR_CNT7_COUNT_MASK)
/*! @} */

/*! @name CORR_ERR_CNT8 - ERM Memory 8 Correctable Error Count Register */
/*! @{ */

#define ERM_CORR_ERR_CNT8_COUNT_MASK             (0xFFU)
#define ERM_CORR_ERR_CNT8_COUNT_SHIFT            (0U)
#define ERM_CORR_ERR_CNT8_COUNT_WIDTH            (8U)
#define ERM_CORR_ERR_CNT8_COUNT(x)               (((uint32_t)(((uint32_t)(x)) << ERM_CORR_ERR_CNT8_COUNT_SHIFT)) & ERM_CORR_ERR_CNT8_COUNT_MASK)
/*! @} */

/*! @name CORR_ERR_CNT9 - ERM Memory 9 Correctable Error Count Register */
/*! @{ */

#define ERM_CORR_ERR_CNT9_COUNT_MASK             (0xFFU)
#define ERM_CORR_ERR_CNT9_COUNT_SHIFT            (0U)
#define ERM_CORR_ERR_CNT9_COUNT_WIDTH            (8U)
#define ERM_CORR_ERR_CNT9_COUNT(x)               (((uint32_t)(((uint32_t)(x)) << ERM_CORR_ERR_CNT9_COUNT_SHIFT)) & ERM_CORR_ERR_CNT9_COUNT_MASK)
/*! @} */

/*! @name EAR10 - ERM Memory 10 Error Address Register */
/*! @{ */

#define ERM_EAR10_EAR_MASK                       (0xFFFFFFFFU)
#define ERM_EAR10_EAR_SHIFT                      (0U)
#define ERM_EAR10_EAR_WIDTH                      (32U)
#define ERM_EAR10_EAR(x)                         (((uint32_t)(((uint32_t)(x)) << ERM_EAR10_EAR_SHIFT)) & ERM_EAR10_EAR_MASK)
/*! @} */

/*! @name SYN10 - ERM Memory 10 Syndrome Register */
/*! @{ */

#define ERM_SYN10_SYNDROME_MASK                  (0xFF000000U)
#define ERM_SYN10_SYNDROME_SHIFT                 (24U)
#define ERM_SYN10_SYNDROME_WIDTH                 (8U)
#define ERM_SYN10_SYNDROME(x)                    (((uint32_t)(((uint32_t)(x)) << ERM_SYN10_SYNDROME_SHIFT)) & ERM_SYN10_SYNDROME_MASK)
/*! @} */

/*! @name CORR_ERR_CNT10 - ERM Memory 10 Correctable Error Count Register */
/*! @{ */

#define ERM_CORR_ERR_CNT10_COUNT_MASK            (0xFFU)
#define ERM_CORR_ERR_CNT10_COUNT_SHIFT           (0U)
#define ERM_CORR_ERR_CNT10_COUNT_WIDTH           (8U)
#define ERM_CORR_ERR_CNT10_COUNT(x)              (((uint32_t)(((uint32_t)(x)) << ERM_CORR_ERR_CNT10_COUNT_SHIFT)) & ERM_CORR_ERR_CNT10_COUNT_MASK)
/*! @} */

/*! @name EAR11 - ERM Memory 11 Error Address Register */
/*! @{ */

#define ERM_EAR11_EAR_MASK                       (0xFFFFFFFFU)
#define ERM_EAR11_EAR_SHIFT                      (0U)
#define ERM_EAR11_EAR_WIDTH                      (32U)
#define ERM_EAR11_EAR(x)                         (((uint32_t)(((uint32_t)(x)) << ERM_EAR11_EAR_SHIFT)) & ERM_EAR11_EAR_MASK)
/*! @} */

/*! @name SYN11 - ERM Memory 11 Syndrome Register */
/*! @{ */

#define ERM_SYN11_SYNDROME_MASK                  (0xFF000000U)
#define ERM_SYN11_SYNDROME_SHIFT                 (24U)
#define ERM_SYN11_SYNDROME_WIDTH                 (8U)
#define ERM_SYN11_SYNDROME(x)                    (((uint32_t)(((uint32_t)(x)) << ERM_SYN11_SYNDROME_SHIFT)) & ERM_SYN11_SYNDROME_MASK)
/*! @} */

/*! @name CORR_ERR_CNT11 - ERM Memory 11 Correctable Error Count Register */
/*! @{ */

#define ERM_CORR_ERR_CNT11_COUNT_MASK            (0xFFU)
#define ERM_CORR_ERR_CNT11_COUNT_SHIFT           (0U)
#define ERM_CORR_ERR_CNT11_COUNT_WIDTH           (8U)
#define ERM_CORR_ERR_CNT11_COUNT(x)              (((uint32_t)(((uint32_t)(x)) << ERM_CORR_ERR_CNT11_COUNT_SHIFT)) & ERM_CORR_ERR_CNT11_COUNT_MASK)
/*! @} */

/*! @name EAR12 - ERM Memory 12 Error Address Register */
/*! @{ */

#define ERM_EAR12_EAR_MASK                       (0xFFFFFFFFU)
#define ERM_EAR12_EAR_SHIFT                      (0U)
#define ERM_EAR12_EAR_WIDTH                      (32U)
#define ERM_EAR12_EAR(x)                         (((uint32_t)(((uint32_t)(x)) << ERM_EAR12_EAR_SHIFT)) & ERM_EAR12_EAR_MASK)
/*! @} */

/*! @name SYN12 - ERM Memory 12 Syndrome Register */
/*! @{ */

#define ERM_SYN12_SYNDROME_MASK                  (0xFF000000U)
#define ERM_SYN12_SYNDROME_SHIFT                 (24U)
#define ERM_SYN12_SYNDROME_WIDTH                 (8U)
#define ERM_SYN12_SYNDROME(x)                    (((uint32_t)(((uint32_t)(x)) << ERM_SYN12_SYNDROME_SHIFT)) & ERM_SYN12_SYNDROME_MASK)
/*! @} */

/*! @name CORR_ERR_CNT12 - ERM Memory 12 Correctable Error Count Register */
/*! @{ */

#define ERM_CORR_ERR_CNT12_COUNT_MASK            (0xFFU)
#define ERM_CORR_ERR_CNT12_COUNT_SHIFT           (0U)
#define ERM_CORR_ERR_CNT12_COUNT_WIDTH           (8U)
#define ERM_CORR_ERR_CNT12_COUNT(x)              (((uint32_t)(((uint32_t)(x)) << ERM_CORR_ERR_CNT12_COUNT_SHIFT)) & ERM_CORR_ERR_CNT12_COUNT_MASK)
/*! @} */

/*! @name EAR13 - ERM Memory 13 Error Address Register */
/*! @{ */

#define ERM_EAR13_EAR_MASK                       (0xFFFFFFFFU)
#define ERM_EAR13_EAR_SHIFT                      (0U)
#define ERM_EAR13_EAR_WIDTH                      (32U)
#define ERM_EAR13_EAR(x)                         (((uint32_t)(((uint32_t)(x)) << ERM_EAR13_EAR_SHIFT)) & ERM_EAR13_EAR_MASK)
/*! @} */

/*! @name SYN13 - ERM Memory 13 Syndrome Register */
/*! @{ */

#define ERM_SYN13_SYNDROME_MASK                  (0xFF000000U)
#define ERM_SYN13_SYNDROME_SHIFT                 (24U)
#define ERM_SYN13_SYNDROME_WIDTH                 (8U)
#define ERM_SYN13_SYNDROME(x)                    (((uint32_t)(((uint32_t)(x)) << ERM_SYN13_SYNDROME_SHIFT)) & ERM_SYN13_SYNDROME_MASK)
/*! @} */

/*! @name CORR_ERR_CNT13 - ERM Memory 13 Correctable Error Count Register */
/*! @{ */

#define ERM_CORR_ERR_CNT13_COUNT_MASK            (0xFFU)
#define ERM_CORR_ERR_CNT13_COUNT_SHIFT           (0U)
#define ERM_CORR_ERR_CNT13_COUNT_WIDTH           (8U)
#define ERM_CORR_ERR_CNT13_COUNT(x)              (((uint32_t)(((uint32_t)(x)) << ERM_CORR_ERR_CNT13_COUNT_SHIFT)) & ERM_CORR_ERR_CNT13_COUNT_MASK)
/*! @} */

/*! @name EAR14 - ERM Memory 14 Error Address Register */
/*! @{ */

#define ERM_EAR14_EAR_MASK                       (0xFFFFFFFFU)
#define ERM_EAR14_EAR_SHIFT                      (0U)
#define ERM_EAR14_EAR_WIDTH                      (32U)
#define ERM_EAR14_EAR(x)                         (((uint32_t)(((uint32_t)(x)) << ERM_EAR14_EAR_SHIFT)) & ERM_EAR14_EAR_MASK)
/*! @} */

/*! @name SYN14 - ERM Memory 14 Syndrome Register */
/*! @{ */

#define ERM_SYN14_SYNDROME_MASK                  (0xFF000000U)
#define ERM_SYN14_SYNDROME_SHIFT                 (24U)
#define ERM_SYN14_SYNDROME_WIDTH                 (8U)
#define ERM_SYN14_SYNDROME(x)                    (((uint32_t)(((uint32_t)(x)) << ERM_SYN14_SYNDROME_SHIFT)) & ERM_SYN14_SYNDROME_MASK)
/*! @} */

/*! @name CORR_ERR_CNT14 - ERM Memory 14 Correctable Error Count Register */
/*! @{ */

#define ERM_CORR_ERR_CNT14_COUNT_MASK            (0xFFU)
#define ERM_CORR_ERR_CNT14_COUNT_SHIFT           (0U)
#define ERM_CORR_ERR_CNT14_COUNT_WIDTH           (8U)
#define ERM_CORR_ERR_CNT14_COUNT(x)              (((uint32_t)(((uint32_t)(x)) << ERM_CORR_ERR_CNT14_COUNT_SHIFT)) & ERM_CORR_ERR_CNT14_COUNT_MASK)
/*! @} */

/*! @name EAR15 - ERM Memory 15 Error Address Register */
/*! @{ */

#define ERM_EAR15_EAR_MASK                       (0xFFFFFFFFU)
#define ERM_EAR15_EAR_SHIFT                      (0U)
#define ERM_EAR15_EAR_WIDTH                      (32U)
#define ERM_EAR15_EAR(x)                         (((uint32_t)(((uint32_t)(x)) << ERM_EAR15_EAR_SHIFT)) & ERM_EAR15_EAR_MASK)
/*! @} */

/*! @name SYN15 - ERM Memory 15 Syndrome Register */
/*! @{ */

#define ERM_SYN15_SYNDROME_MASK                  (0xFF000000U)
#define ERM_SYN15_SYNDROME_SHIFT                 (24U)
#define ERM_SYN15_SYNDROME_WIDTH                 (8U)
#define ERM_SYN15_SYNDROME(x)                    (((uint32_t)(((uint32_t)(x)) << ERM_SYN15_SYNDROME_SHIFT)) & ERM_SYN15_SYNDROME_MASK)
/*! @} */

/*! @name CORR_ERR_CNT15 - ERM Memory 15 Correctable Error Count Register */
/*! @{ */

#define ERM_CORR_ERR_CNT15_COUNT_MASK            (0xFFU)
#define ERM_CORR_ERR_CNT15_COUNT_SHIFT           (0U)
#define ERM_CORR_ERR_CNT15_COUNT_WIDTH           (8U)
#define ERM_CORR_ERR_CNT15_COUNT(x)              (((uint32_t)(((uint32_t)(x)) << ERM_CORR_ERR_CNT15_COUNT_SHIFT)) & ERM_CORR_ERR_CNT15_COUNT_MASK)
/*! @} */

/*! @name EAR16 - ERM Memory 16 Error Address Register */
/*! @{ */

#define ERM_EAR16_EAR_MASK                       (0xFFFFFFFFU)
#define ERM_EAR16_EAR_SHIFT                      (0U)
#define ERM_EAR16_EAR_WIDTH                      (32U)
#define ERM_EAR16_EAR(x)                         (((uint32_t)(((uint32_t)(x)) << ERM_EAR16_EAR_SHIFT)) & ERM_EAR16_EAR_MASK)
/*! @} */

/*! @name SYN16 - ERM Memory 16 Syndrome Register */
/*! @{ */

#define ERM_SYN16_SYNDROME_MASK                  (0xFF000000U)
#define ERM_SYN16_SYNDROME_SHIFT                 (24U)
#define ERM_SYN16_SYNDROME_WIDTH                 (8U)
#define ERM_SYN16_SYNDROME(x)                    (((uint32_t)(((uint32_t)(x)) << ERM_SYN16_SYNDROME_SHIFT)) & ERM_SYN16_SYNDROME_MASK)
/*! @} */

/*! @name CORR_ERR_CNT16 - ERM Memory 16 Correctable Error Count Register */
/*! @{ */

#define ERM_CORR_ERR_CNT16_COUNT_MASK            (0xFFU)
#define ERM_CORR_ERR_CNT16_COUNT_SHIFT           (0U)
#define ERM_CORR_ERR_CNT16_COUNT_WIDTH           (8U)
#define ERM_CORR_ERR_CNT16_COUNT(x)              (((uint32_t)(((uint32_t)(x)) << ERM_CORR_ERR_CNT16_COUNT_SHIFT)) & ERM_CORR_ERR_CNT16_COUNT_MASK)
/*! @} */

/*! @name EAR17 - ERM Memory 17 Error Address Register */
/*! @{ */

#define ERM_EAR17_EAR_MASK                       (0xFFFFFFFFU)
#define ERM_EAR17_EAR_SHIFT                      (0U)
#define ERM_EAR17_EAR_WIDTH                      (32U)
#define ERM_EAR17_EAR(x)                         (((uint32_t)(((uint32_t)(x)) << ERM_EAR17_EAR_SHIFT)) & ERM_EAR17_EAR_MASK)
/*! @} */

/*! @name CORR_ERR_CNT17 - ERM Memory 17 Correctable Error Count Register */
/*! @{ */

#define ERM_CORR_ERR_CNT17_COUNT_MASK            (0xFFU)
#define ERM_CORR_ERR_CNT17_COUNT_SHIFT           (0U)
#define ERM_CORR_ERR_CNT17_COUNT_WIDTH           (8U)
#define ERM_CORR_ERR_CNT17_COUNT(x)              (((uint32_t)(((uint32_t)(x)) << ERM_CORR_ERR_CNT17_COUNT_SHIFT)) & ERM_CORR_ERR_CNT17_COUNT_MASK)
/*! @} */

/*! @name EAR18 - ERM Memory 18 Error Address Register */
/*! @{ */

#define ERM_EAR18_EAR_MASK                       (0xFFFFFFFFU)
#define ERM_EAR18_EAR_SHIFT                      (0U)
#define ERM_EAR18_EAR_WIDTH                      (32U)
#define ERM_EAR18_EAR(x)                         (((uint32_t)(((uint32_t)(x)) << ERM_EAR18_EAR_SHIFT)) & ERM_EAR18_EAR_MASK)
/*! @} */

/*! @name CORR_ERR_CNT18 - ERM Memory 18 Correctable Error Count Register */
/*! @{ */

#define ERM_CORR_ERR_CNT18_COUNT_MASK            (0xFFU)
#define ERM_CORR_ERR_CNT18_COUNT_SHIFT           (0U)
#define ERM_CORR_ERR_CNT18_COUNT_WIDTH           (8U)
#define ERM_CORR_ERR_CNT18_COUNT(x)              (((uint32_t)(((uint32_t)(x)) << ERM_CORR_ERR_CNT18_COUNT_SHIFT)) & ERM_CORR_ERR_CNT18_COUNT_MASK)
/*! @} */

/*! @name EAR19 - ERM Memory 19 Error Address Register */
/*! @{ */

#define ERM_EAR19_EAR_MASK                       (0xFFFFFFFFU)
#define ERM_EAR19_EAR_SHIFT                      (0U)
#define ERM_EAR19_EAR_WIDTH                      (32U)
#define ERM_EAR19_EAR(x)                         (((uint32_t)(((uint32_t)(x)) << ERM_EAR19_EAR_SHIFT)) & ERM_EAR19_EAR_MASK)
/*! @} */

/*! @name CORR_ERR_CNT19 - ERM Memory 19 Correctable Error Count Register */
/*! @{ */

#define ERM_CORR_ERR_CNT19_COUNT_MASK            (0xFFU)
#define ERM_CORR_ERR_CNT19_COUNT_SHIFT           (0U)
#define ERM_CORR_ERR_CNT19_COUNT_WIDTH           (8U)
#define ERM_CORR_ERR_CNT19_COUNT(x)              (((uint32_t)(((uint32_t)(x)) << ERM_CORR_ERR_CNT19_COUNT_SHIFT)) & ERM_CORR_ERR_CNT19_COUNT_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group ERM_Register_Masks */

/*!
 * @}
 */ /* end of group ERM_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_ERM_H_) */
