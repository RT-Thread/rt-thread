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
 * @file S32K344_eMIOS.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_eMIOS
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
#if !defined(S32K344_eMIOS_H_)  /* Check if memory map has not been already included */
#define S32K344_eMIOS_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- eMIOS Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup eMIOS_Peripheral_Access_Layer eMIOS Peripheral Access Layer
 * @{
 */

/** eMIOS - Size of Registers Arrays */
#define eMIOS_CH_UC_UC_COUNT                      24u

/** eMIOS - Register Layout Typedef */
typedef struct {
  __IO uint32_t MCR;                               /**< Module Configuration, offset: 0x0 */
  __I  uint32_t GFLAG;                             /**< Global Flag, offset: 0x4 */
  __IO uint32_t OUDIS;                             /**< Output Update Disable, offset: 0x8 */
  __IO uint32_t UCDIS;                             /**< Disable Channel, offset: 0xC */
  uint8_t RESERVED_0[16];
  union {                                          /* offset: 0x20 */
    struct {                                         /* offset: 0x20, array step: 0x20 */
      __IO uint32_t A;                                 /**< UC A 0..UC A 23, array offset: 0x20, array step: 0x20 */
      __IO uint32_t B;                                 /**< UC B 0..UC B 23, array offset: 0x24, array step: 0x20 */
      __IO uint32_t CNT;                               /**< UC Counter 0..UC Counter 23, array offset: 0x28, array step: 0x20 */
      __IO uint32_t C;                                 /**< UC Control 0..UC Control 23, array offset: 0x2C, array step: 0x20 */
      __IO uint32_t S;                                 /**< UC Status 0..UC Status 23, array offset: 0x30, array step: 0x20 */
      __IO uint32_t ALTA;                              /**< Alternate Address 0..Alternate Address 23, array offset: 0x34, array step: 0x20 */
      __IO uint32_t C2;                                /**< UC Control 2 0..UC Control 2 23, array offset: 0x38, array step: 0x20 */
      uint8_t RESERVED_0[4];
    } UC[eMIOS_CH_UC_UC_COUNT];
  } CH;
} eMIOS_Type, *eMIOS_MemMapPtr;

/** Number of instances of the eMIOS module. */
#define eMIOS_INSTANCE_COUNT                     (3u)

/* eMIOS - Peripheral instance base addresses */
/** Peripheral EMIOS_0 base address */
#define IP_EMIOS_0_BASE                          (0x40088000u)
/** Peripheral EMIOS_0 base pointer */
#define IP_EMIOS_0                               ((eMIOS_Type *)IP_EMIOS_0_BASE)
/** Peripheral EMIOS_1 base address */
#define IP_EMIOS_1_BASE                          (0x4008C000u)
/** Peripheral EMIOS_1 base pointer */
#define IP_EMIOS_1                               ((eMIOS_Type *)IP_EMIOS_1_BASE)
/** Peripheral EMIOS_2 base address */
#define IP_EMIOS_2_BASE                          (0x40090000u)
/** Peripheral EMIOS_2 base pointer */
#define IP_EMIOS_2                               ((eMIOS_Type *)IP_EMIOS_2_BASE)
/** Array initializer of eMIOS peripheral base addresses */
#define IP_eMIOS_BASE_ADDRS                      { IP_EMIOS_0_BASE, IP_EMIOS_1_BASE, IP_EMIOS_2_BASE }
/** Array initializer of eMIOS peripheral base pointers */
#define IP_eMIOS_BASE_PTRS                       { IP_EMIOS_0, IP_EMIOS_1, IP_EMIOS_2 }

/* ----------------------------------------------------------------------------
   -- eMIOS Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup eMIOS_Register_Masks eMIOS Register Masks
 * @{
 */

/*! @name MCR - Module Configuration */
/*! @{ */

#define eMIOS_MCR_GPRE_MASK                      (0xFF00U)
#define eMIOS_MCR_GPRE_SHIFT                     (8U)
#define eMIOS_MCR_GPRE_WIDTH                     (8U)
#define eMIOS_MCR_GPRE(x)                        (((uint32_t)(((uint32_t)(x)) << eMIOS_MCR_GPRE_SHIFT)) & eMIOS_MCR_GPRE_MASK)

#define eMIOS_MCR_GPREN_MASK                     (0x4000000U)
#define eMIOS_MCR_GPREN_SHIFT                    (26U)
#define eMIOS_MCR_GPREN_WIDTH                    (1U)
#define eMIOS_MCR_GPREN(x)                       (((uint32_t)(((uint32_t)(x)) << eMIOS_MCR_GPREN_SHIFT)) & eMIOS_MCR_GPREN_MASK)

#define eMIOS_MCR_GTBE_MASK                      (0x10000000U)
#define eMIOS_MCR_GTBE_SHIFT                     (28U)
#define eMIOS_MCR_GTBE_WIDTH                     (1U)
#define eMIOS_MCR_GTBE(x)                        (((uint32_t)(((uint32_t)(x)) << eMIOS_MCR_GTBE_SHIFT)) & eMIOS_MCR_GTBE_MASK)

#define eMIOS_MCR_FRZ_MASK                       (0x20000000U)
#define eMIOS_MCR_FRZ_SHIFT                      (29U)
#define eMIOS_MCR_FRZ_WIDTH                      (1U)
#define eMIOS_MCR_FRZ(x)                         (((uint32_t)(((uint32_t)(x)) << eMIOS_MCR_FRZ_SHIFT)) & eMIOS_MCR_FRZ_MASK)

#define eMIOS_MCR_MDIS_MASK                      (0x40000000U)
#define eMIOS_MCR_MDIS_SHIFT                     (30U)
#define eMIOS_MCR_MDIS_WIDTH                     (1U)
#define eMIOS_MCR_MDIS(x)                        (((uint32_t)(((uint32_t)(x)) << eMIOS_MCR_MDIS_SHIFT)) & eMIOS_MCR_MDIS_MASK)
/*! @} */

/*! @name GFLAG - Global Flag */
/*! @{ */

#define eMIOS_GFLAG_F0_MASK                      (0x1U)
#define eMIOS_GFLAG_F0_SHIFT                     (0U)
#define eMIOS_GFLAG_F0_WIDTH                     (1U)
#define eMIOS_GFLAG_F0(x)                        (((uint32_t)(((uint32_t)(x)) << eMIOS_GFLAG_F0_SHIFT)) & eMIOS_GFLAG_F0_MASK)

#define eMIOS_GFLAG_F1_MASK                      (0x2U)
#define eMIOS_GFLAG_F1_SHIFT                     (1U)
#define eMIOS_GFLAG_F1_WIDTH                     (1U)
#define eMIOS_GFLAG_F1(x)                        (((uint32_t)(((uint32_t)(x)) << eMIOS_GFLAG_F1_SHIFT)) & eMIOS_GFLAG_F1_MASK)

#define eMIOS_GFLAG_F2_MASK                      (0x4U)
#define eMIOS_GFLAG_F2_SHIFT                     (2U)
#define eMIOS_GFLAG_F2_WIDTH                     (1U)
#define eMIOS_GFLAG_F2(x)                        (((uint32_t)(((uint32_t)(x)) << eMIOS_GFLAG_F2_SHIFT)) & eMIOS_GFLAG_F2_MASK)

#define eMIOS_GFLAG_F3_MASK                      (0x8U)
#define eMIOS_GFLAG_F3_SHIFT                     (3U)
#define eMIOS_GFLAG_F3_WIDTH                     (1U)
#define eMIOS_GFLAG_F3(x)                        (((uint32_t)(((uint32_t)(x)) << eMIOS_GFLAG_F3_SHIFT)) & eMIOS_GFLAG_F3_MASK)

#define eMIOS_GFLAG_F4_MASK                      (0x10U)
#define eMIOS_GFLAG_F4_SHIFT                     (4U)
#define eMIOS_GFLAG_F4_WIDTH                     (1U)
#define eMIOS_GFLAG_F4(x)                        (((uint32_t)(((uint32_t)(x)) << eMIOS_GFLAG_F4_SHIFT)) & eMIOS_GFLAG_F4_MASK)

#define eMIOS_GFLAG_F5_MASK                      (0x20U)
#define eMIOS_GFLAG_F5_SHIFT                     (5U)
#define eMIOS_GFLAG_F5_WIDTH                     (1U)
#define eMIOS_GFLAG_F5(x)                        (((uint32_t)(((uint32_t)(x)) << eMIOS_GFLAG_F5_SHIFT)) & eMIOS_GFLAG_F5_MASK)

#define eMIOS_GFLAG_F6_MASK                      (0x40U)
#define eMIOS_GFLAG_F6_SHIFT                     (6U)
#define eMIOS_GFLAG_F6_WIDTH                     (1U)
#define eMIOS_GFLAG_F6(x)                        (((uint32_t)(((uint32_t)(x)) << eMIOS_GFLAG_F6_SHIFT)) & eMIOS_GFLAG_F6_MASK)

#define eMIOS_GFLAG_F7_MASK                      (0x80U)
#define eMIOS_GFLAG_F7_SHIFT                     (7U)
#define eMIOS_GFLAG_F7_WIDTH                     (1U)
#define eMIOS_GFLAG_F7(x)                        (((uint32_t)(((uint32_t)(x)) << eMIOS_GFLAG_F7_SHIFT)) & eMIOS_GFLAG_F7_MASK)

#define eMIOS_GFLAG_F8_MASK                      (0x100U)
#define eMIOS_GFLAG_F8_SHIFT                     (8U)
#define eMIOS_GFLAG_F8_WIDTH                     (1U)
#define eMIOS_GFLAG_F8(x)                        (((uint32_t)(((uint32_t)(x)) << eMIOS_GFLAG_F8_SHIFT)) & eMIOS_GFLAG_F8_MASK)

#define eMIOS_GFLAG_F9_MASK                      (0x200U)
#define eMIOS_GFLAG_F9_SHIFT                     (9U)
#define eMIOS_GFLAG_F9_WIDTH                     (1U)
#define eMIOS_GFLAG_F9(x)                        (((uint32_t)(((uint32_t)(x)) << eMIOS_GFLAG_F9_SHIFT)) & eMIOS_GFLAG_F9_MASK)

#define eMIOS_GFLAG_F10_MASK                     (0x400U)
#define eMIOS_GFLAG_F10_SHIFT                    (10U)
#define eMIOS_GFLAG_F10_WIDTH                    (1U)
#define eMIOS_GFLAG_F10(x)                       (((uint32_t)(((uint32_t)(x)) << eMIOS_GFLAG_F10_SHIFT)) & eMIOS_GFLAG_F10_MASK)

#define eMIOS_GFLAG_F11_MASK                     (0x800U)
#define eMIOS_GFLAG_F11_SHIFT                    (11U)
#define eMIOS_GFLAG_F11_WIDTH                    (1U)
#define eMIOS_GFLAG_F11(x)                       (((uint32_t)(((uint32_t)(x)) << eMIOS_GFLAG_F11_SHIFT)) & eMIOS_GFLAG_F11_MASK)

#define eMIOS_GFLAG_F12_MASK                     (0x1000U)
#define eMIOS_GFLAG_F12_SHIFT                    (12U)
#define eMIOS_GFLAG_F12_WIDTH                    (1U)
#define eMIOS_GFLAG_F12(x)                       (((uint32_t)(((uint32_t)(x)) << eMIOS_GFLAG_F12_SHIFT)) & eMIOS_GFLAG_F12_MASK)

#define eMIOS_GFLAG_F13_MASK                     (0x2000U)
#define eMIOS_GFLAG_F13_SHIFT                    (13U)
#define eMIOS_GFLAG_F13_WIDTH                    (1U)
#define eMIOS_GFLAG_F13(x)                       (((uint32_t)(((uint32_t)(x)) << eMIOS_GFLAG_F13_SHIFT)) & eMIOS_GFLAG_F13_MASK)

#define eMIOS_GFLAG_F14_MASK                     (0x4000U)
#define eMIOS_GFLAG_F14_SHIFT                    (14U)
#define eMIOS_GFLAG_F14_WIDTH                    (1U)
#define eMIOS_GFLAG_F14(x)                       (((uint32_t)(((uint32_t)(x)) << eMIOS_GFLAG_F14_SHIFT)) & eMIOS_GFLAG_F14_MASK)

#define eMIOS_GFLAG_F15_MASK                     (0x8000U)
#define eMIOS_GFLAG_F15_SHIFT                    (15U)
#define eMIOS_GFLAG_F15_WIDTH                    (1U)
#define eMIOS_GFLAG_F15(x)                       (((uint32_t)(((uint32_t)(x)) << eMIOS_GFLAG_F15_SHIFT)) & eMIOS_GFLAG_F15_MASK)

#define eMIOS_GFLAG_F16_MASK                     (0x10000U)
#define eMIOS_GFLAG_F16_SHIFT                    (16U)
#define eMIOS_GFLAG_F16_WIDTH                    (1U)
#define eMIOS_GFLAG_F16(x)                       (((uint32_t)(((uint32_t)(x)) << eMIOS_GFLAG_F16_SHIFT)) & eMIOS_GFLAG_F16_MASK)

#define eMIOS_GFLAG_F17_MASK                     (0x20000U)
#define eMIOS_GFLAG_F17_SHIFT                    (17U)
#define eMIOS_GFLAG_F17_WIDTH                    (1U)
#define eMIOS_GFLAG_F17(x)                       (((uint32_t)(((uint32_t)(x)) << eMIOS_GFLAG_F17_SHIFT)) & eMIOS_GFLAG_F17_MASK)

#define eMIOS_GFLAG_F18_MASK                     (0x40000U)
#define eMIOS_GFLAG_F18_SHIFT                    (18U)
#define eMIOS_GFLAG_F18_WIDTH                    (1U)
#define eMIOS_GFLAG_F18(x)                       (((uint32_t)(((uint32_t)(x)) << eMIOS_GFLAG_F18_SHIFT)) & eMIOS_GFLAG_F18_MASK)

#define eMIOS_GFLAG_F19_MASK                     (0x80000U)
#define eMIOS_GFLAG_F19_SHIFT                    (19U)
#define eMIOS_GFLAG_F19_WIDTH                    (1U)
#define eMIOS_GFLAG_F19(x)                       (((uint32_t)(((uint32_t)(x)) << eMIOS_GFLAG_F19_SHIFT)) & eMIOS_GFLAG_F19_MASK)

#define eMIOS_GFLAG_F20_MASK                     (0x100000U)
#define eMIOS_GFLAG_F20_SHIFT                    (20U)
#define eMIOS_GFLAG_F20_WIDTH                    (1U)
#define eMIOS_GFLAG_F20(x)                       (((uint32_t)(((uint32_t)(x)) << eMIOS_GFLAG_F20_SHIFT)) & eMIOS_GFLAG_F20_MASK)

#define eMIOS_GFLAG_F21_MASK                     (0x200000U)
#define eMIOS_GFLAG_F21_SHIFT                    (21U)
#define eMIOS_GFLAG_F21_WIDTH                    (1U)
#define eMIOS_GFLAG_F21(x)                       (((uint32_t)(((uint32_t)(x)) << eMIOS_GFLAG_F21_SHIFT)) & eMIOS_GFLAG_F21_MASK)

#define eMIOS_GFLAG_F22_MASK                     (0x400000U)
#define eMIOS_GFLAG_F22_SHIFT                    (22U)
#define eMIOS_GFLAG_F22_WIDTH                    (1U)
#define eMIOS_GFLAG_F22(x)                       (((uint32_t)(((uint32_t)(x)) << eMIOS_GFLAG_F22_SHIFT)) & eMIOS_GFLAG_F22_MASK)

#define eMIOS_GFLAG_F23_MASK                     (0x800000U)
#define eMIOS_GFLAG_F23_SHIFT                    (23U)
#define eMIOS_GFLAG_F23_WIDTH                    (1U)
#define eMIOS_GFLAG_F23(x)                       (((uint32_t)(((uint32_t)(x)) << eMIOS_GFLAG_F23_SHIFT)) & eMIOS_GFLAG_F23_MASK)
/*! @} */

/*! @name OUDIS - Output Update Disable */
/*! @{ */

#define eMIOS_OUDIS_OU0_MASK                     (0x1U)
#define eMIOS_OUDIS_OU0_SHIFT                    (0U)
#define eMIOS_OUDIS_OU0_WIDTH                    (1U)
#define eMIOS_OUDIS_OU0(x)                       (((uint32_t)(((uint32_t)(x)) << eMIOS_OUDIS_OU0_SHIFT)) & eMIOS_OUDIS_OU0_MASK)

#define eMIOS_OUDIS_OU1_MASK                     (0x2U)
#define eMIOS_OUDIS_OU1_SHIFT                    (1U)
#define eMIOS_OUDIS_OU1_WIDTH                    (1U)
#define eMIOS_OUDIS_OU1(x)                       (((uint32_t)(((uint32_t)(x)) << eMIOS_OUDIS_OU1_SHIFT)) & eMIOS_OUDIS_OU1_MASK)

#define eMIOS_OUDIS_OU2_MASK                     (0x4U)
#define eMIOS_OUDIS_OU2_SHIFT                    (2U)
#define eMIOS_OUDIS_OU2_WIDTH                    (1U)
#define eMIOS_OUDIS_OU2(x)                       (((uint32_t)(((uint32_t)(x)) << eMIOS_OUDIS_OU2_SHIFT)) & eMIOS_OUDIS_OU2_MASK)

#define eMIOS_OUDIS_OU3_MASK                     (0x8U)
#define eMIOS_OUDIS_OU3_SHIFT                    (3U)
#define eMIOS_OUDIS_OU3_WIDTH                    (1U)
#define eMIOS_OUDIS_OU3(x)                       (((uint32_t)(((uint32_t)(x)) << eMIOS_OUDIS_OU3_SHIFT)) & eMIOS_OUDIS_OU3_MASK)

#define eMIOS_OUDIS_OU4_MASK                     (0x10U)
#define eMIOS_OUDIS_OU4_SHIFT                    (4U)
#define eMIOS_OUDIS_OU4_WIDTH                    (1U)
#define eMIOS_OUDIS_OU4(x)                       (((uint32_t)(((uint32_t)(x)) << eMIOS_OUDIS_OU4_SHIFT)) & eMIOS_OUDIS_OU4_MASK)

#define eMIOS_OUDIS_OU5_MASK                     (0x20U)
#define eMIOS_OUDIS_OU5_SHIFT                    (5U)
#define eMIOS_OUDIS_OU5_WIDTH                    (1U)
#define eMIOS_OUDIS_OU5(x)                       (((uint32_t)(((uint32_t)(x)) << eMIOS_OUDIS_OU5_SHIFT)) & eMIOS_OUDIS_OU5_MASK)

#define eMIOS_OUDIS_OU6_MASK                     (0x40U)
#define eMIOS_OUDIS_OU6_SHIFT                    (6U)
#define eMIOS_OUDIS_OU6_WIDTH                    (1U)
#define eMIOS_OUDIS_OU6(x)                       (((uint32_t)(((uint32_t)(x)) << eMIOS_OUDIS_OU6_SHIFT)) & eMIOS_OUDIS_OU6_MASK)

#define eMIOS_OUDIS_OU7_MASK                     (0x80U)
#define eMIOS_OUDIS_OU7_SHIFT                    (7U)
#define eMIOS_OUDIS_OU7_WIDTH                    (1U)
#define eMIOS_OUDIS_OU7(x)                       (((uint32_t)(((uint32_t)(x)) << eMIOS_OUDIS_OU7_SHIFT)) & eMIOS_OUDIS_OU7_MASK)

#define eMIOS_OUDIS_OU8_MASK                     (0x100U)
#define eMIOS_OUDIS_OU8_SHIFT                    (8U)
#define eMIOS_OUDIS_OU8_WIDTH                    (1U)
#define eMIOS_OUDIS_OU8(x)                       (((uint32_t)(((uint32_t)(x)) << eMIOS_OUDIS_OU8_SHIFT)) & eMIOS_OUDIS_OU8_MASK)

#define eMIOS_OUDIS_OU9_MASK                     (0x200U)
#define eMIOS_OUDIS_OU9_SHIFT                    (9U)
#define eMIOS_OUDIS_OU9_WIDTH                    (1U)
#define eMIOS_OUDIS_OU9(x)                       (((uint32_t)(((uint32_t)(x)) << eMIOS_OUDIS_OU9_SHIFT)) & eMIOS_OUDIS_OU9_MASK)

#define eMIOS_OUDIS_OU10_MASK                    (0x400U)
#define eMIOS_OUDIS_OU10_SHIFT                   (10U)
#define eMIOS_OUDIS_OU10_WIDTH                   (1U)
#define eMIOS_OUDIS_OU10(x)                      (((uint32_t)(((uint32_t)(x)) << eMIOS_OUDIS_OU10_SHIFT)) & eMIOS_OUDIS_OU10_MASK)

#define eMIOS_OUDIS_OU11_MASK                    (0x800U)
#define eMIOS_OUDIS_OU11_SHIFT                   (11U)
#define eMIOS_OUDIS_OU11_WIDTH                   (1U)
#define eMIOS_OUDIS_OU11(x)                      (((uint32_t)(((uint32_t)(x)) << eMIOS_OUDIS_OU11_SHIFT)) & eMIOS_OUDIS_OU11_MASK)

#define eMIOS_OUDIS_OU12_MASK                    (0x1000U)
#define eMIOS_OUDIS_OU12_SHIFT                   (12U)
#define eMIOS_OUDIS_OU12_WIDTH                   (1U)
#define eMIOS_OUDIS_OU12(x)                      (((uint32_t)(((uint32_t)(x)) << eMIOS_OUDIS_OU12_SHIFT)) & eMIOS_OUDIS_OU12_MASK)

#define eMIOS_OUDIS_OU13_MASK                    (0x2000U)
#define eMIOS_OUDIS_OU13_SHIFT                   (13U)
#define eMIOS_OUDIS_OU13_WIDTH                   (1U)
#define eMIOS_OUDIS_OU13(x)                      (((uint32_t)(((uint32_t)(x)) << eMIOS_OUDIS_OU13_SHIFT)) & eMIOS_OUDIS_OU13_MASK)

#define eMIOS_OUDIS_OU14_MASK                    (0x4000U)
#define eMIOS_OUDIS_OU14_SHIFT                   (14U)
#define eMIOS_OUDIS_OU14_WIDTH                   (1U)
#define eMIOS_OUDIS_OU14(x)                      (((uint32_t)(((uint32_t)(x)) << eMIOS_OUDIS_OU14_SHIFT)) & eMIOS_OUDIS_OU14_MASK)

#define eMIOS_OUDIS_OU15_MASK                    (0x8000U)
#define eMIOS_OUDIS_OU15_SHIFT                   (15U)
#define eMIOS_OUDIS_OU15_WIDTH                   (1U)
#define eMIOS_OUDIS_OU15(x)                      (((uint32_t)(((uint32_t)(x)) << eMIOS_OUDIS_OU15_SHIFT)) & eMIOS_OUDIS_OU15_MASK)

#define eMIOS_OUDIS_OU16_MASK                    (0x10000U)
#define eMIOS_OUDIS_OU16_SHIFT                   (16U)
#define eMIOS_OUDIS_OU16_WIDTH                   (1U)
#define eMIOS_OUDIS_OU16(x)                      (((uint32_t)(((uint32_t)(x)) << eMIOS_OUDIS_OU16_SHIFT)) & eMIOS_OUDIS_OU16_MASK)

#define eMIOS_OUDIS_OU17_MASK                    (0x20000U)
#define eMIOS_OUDIS_OU17_SHIFT                   (17U)
#define eMIOS_OUDIS_OU17_WIDTH                   (1U)
#define eMIOS_OUDIS_OU17(x)                      (((uint32_t)(((uint32_t)(x)) << eMIOS_OUDIS_OU17_SHIFT)) & eMIOS_OUDIS_OU17_MASK)

#define eMIOS_OUDIS_OU18_MASK                    (0x40000U)
#define eMIOS_OUDIS_OU18_SHIFT                   (18U)
#define eMIOS_OUDIS_OU18_WIDTH                   (1U)
#define eMIOS_OUDIS_OU18(x)                      (((uint32_t)(((uint32_t)(x)) << eMIOS_OUDIS_OU18_SHIFT)) & eMIOS_OUDIS_OU18_MASK)

#define eMIOS_OUDIS_OU19_MASK                    (0x80000U)
#define eMIOS_OUDIS_OU19_SHIFT                   (19U)
#define eMIOS_OUDIS_OU19_WIDTH                   (1U)
#define eMIOS_OUDIS_OU19(x)                      (((uint32_t)(((uint32_t)(x)) << eMIOS_OUDIS_OU19_SHIFT)) & eMIOS_OUDIS_OU19_MASK)

#define eMIOS_OUDIS_OU20_MASK                    (0x100000U)
#define eMIOS_OUDIS_OU20_SHIFT                   (20U)
#define eMIOS_OUDIS_OU20_WIDTH                   (1U)
#define eMIOS_OUDIS_OU20(x)                      (((uint32_t)(((uint32_t)(x)) << eMIOS_OUDIS_OU20_SHIFT)) & eMIOS_OUDIS_OU20_MASK)

#define eMIOS_OUDIS_OU21_MASK                    (0x200000U)
#define eMIOS_OUDIS_OU21_SHIFT                   (21U)
#define eMIOS_OUDIS_OU21_WIDTH                   (1U)
#define eMIOS_OUDIS_OU21(x)                      (((uint32_t)(((uint32_t)(x)) << eMIOS_OUDIS_OU21_SHIFT)) & eMIOS_OUDIS_OU21_MASK)

#define eMIOS_OUDIS_OU22_MASK                    (0x400000U)
#define eMIOS_OUDIS_OU22_SHIFT                   (22U)
#define eMIOS_OUDIS_OU22_WIDTH                   (1U)
#define eMIOS_OUDIS_OU22(x)                      (((uint32_t)(((uint32_t)(x)) << eMIOS_OUDIS_OU22_SHIFT)) & eMIOS_OUDIS_OU22_MASK)

#define eMIOS_OUDIS_OU23_MASK                    (0x800000U)
#define eMIOS_OUDIS_OU23_SHIFT                   (23U)
#define eMIOS_OUDIS_OU23_WIDTH                   (1U)
#define eMIOS_OUDIS_OU23(x)                      (((uint32_t)(((uint32_t)(x)) << eMIOS_OUDIS_OU23_SHIFT)) & eMIOS_OUDIS_OU23_MASK)
/*! @} */

/*! @name UCDIS - Disable Channel */
/*! @{ */

#define eMIOS_UCDIS_UCDIS0_MASK                  (0x1U)
#define eMIOS_UCDIS_UCDIS0_SHIFT                 (0U)
#define eMIOS_UCDIS_UCDIS0_WIDTH                 (1U)
#define eMIOS_UCDIS_UCDIS0(x)                    (((uint32_t)(((uint32_t)(x)) << eMIOS_UCDIS_UCDIS0_SHIFT)) & eMIOS_UCDIS_UCDIS0_MASK)

#define eMIOS_UCDIS_UCDIS1_MASK                  (0x2U)
#define eMIOS_UCDIS_UCDIS1_SHIFT                 (1U)
#define eMIOS_UCDIS_UCDIS1_WIDTH                 (1U)
#define eMIOS_UCDIS_UCDIS1(x)                    (((uint32_t)(((uint32_t)(x)) << eMIOS_UCDIS_UCDIS1_SHIFT)) & eMIOS_UCDIS_UCDIS1_MASK)

#define eMIOS_UCDIS_UCDIS2_MASK                  (0x4U)
#define eMIOS_UCDIS_UCDIS2_SHIFT                 (2U)
#define eMIOS_UCDIS_UCDIS2_WIDTH                 (1U)
#define eMIOS_UCDIS_UCDIS2(x)                    (((uint32_t)(((uint32_t)(x)) << eMIOS_UCDIS_UCDIS2_SHIFT)) & eMIOS_UCDIS_UCDIS2_MASK)

#define eMIOS_UCDIS_UCDIS3_MASK                  (0x8U)
#define eMIOS_UCDIS_UCDIS3_SHIFT                 (3U)
#define eMIOS_UCDIS_UCDIS3_WIDTH                 (1U)
#define eMIOS_UCDIS_UCDIS3(x)                    (((uint32_t)(((uint32_t)(x)) << eMIOS_UCDIS_UCDIS3_SHIFT)) & eMIOS_UCDIS_UCDIS3_MASK)

#define eMIOS_UCDIS_UCDIS4_MASK                  (0x10U)
#define eMIOS_UCDIS_UCDIS4_SHIFT                 (4U)
#define eMIOS_UCDIS_UCDIS4_WIDTH                 (1U)
#define eMIOS_UCDIS_UCDIS4(x)                    (((uint32_t)(((uint32_t)(x)) << eMIOS_UCDIS_UCDIS4_SHIFT)) & eMIOS_UCDIS_UCDIS4_MASK)

#define eMIOS_UCDIS_UCDIS5_MASK                  (0x20U)
#define eMIOS_UCDIS_UCDIS5_SHIFT                 (5U)
#define eMIOS_UCDIS_UCDIS5_WIDTH                 (1U)
#define eMIOS_UCDIS_UCDIS5(x)                    (((uint32_t)(((uint32_t)(x)) << eMIOS_UCDIS_UCDIS5_SHIFT)) & eMIOS_UCDIS_UCDIS5_MASK)

#define eMIOS_UCDIS_UCDIS6_MASK                  (0x40U)
#define eMIOS_UCDIS_UCDIS6_SHIFT                 (6U)
#define eMIOS_UCDIS_UCDIS6_WIDTH                 (1U)
#define eMIOS_UCDIS_UCDIS6(x)                    (((uint32_t)(((uint32_t)(x)) << eMIOS_UCDIS_UCDIS6_SHIFT)) & eMIOS_UCDIS_UCDIS6_MASK)

#define eMIOS_UCDIS_UCDIS7_MASK                  (0x80U)
#define eMIOS_UCDIS_UCDIS7_SHIFT                 (7U)
#define eMIOS_UCDIS_UCDIS7_WIDTH                 (1U)
#define eMIOS_UCDIS_UCDIS7(x)                    (((uint32_t)(((uint32_t)(x)) << eMIOS_UCDIS_UCDIS7_SHIFT)) & eMIOS_UCDIS_UCDIS7_MASK)

#define eMIOS_UCDIS_UCDIS8_MASK                  (0x100U)
#define eMIOS_UCDIS_UCDIS8_SHIFT                 (8U)
#define eMIOS_UCDIS_UCDIS8_WIDTH                 (1U)
#define eMIOS_UCDIS_UCDIS8(x)                    (((uint32_t)(((uint32_t)(x)) << eMIOS_UCDIS_UCDIS8_SHIFT)) & eMIOS_UCDIS_UCDIS8_MASK)

#define eMIOS_UCDIS_UCDIS9_MASK                  (0x200U)
#define eMIOS_UCDIS_UCDIS9_SHIFT                 (9U)
#define eMIOS_UCDIS_UCDIS9_WIDTH                 (1U)
#define eMIOS_UCDIS_UCDIS9(x)                    (((uint32_t)(((uint32_t)(x)) << eMIOS_UCDIS_UCDIS9_SHIFT)) & eMIOS_UCDIS_UCDIS9_MASK)

#define eMIOS_UCDIS_UCDIS10_MASK                 (0x400U)
#define eMIOS_UCDIS_UCDIS10_SHIFT                (10U)
#define eMIOS_UCDIS_UCDIS10_WIDTH                (1U)
#define eMIOS_UCDIS_UCDIS10(x)                   (((uint32_t)(((uint32_t)(x)) << eMIOS_UCDIS_UCDIS10_SHIFT)) & eMIOS_UCDIS_UCDIS10_MASK)

#define eMIOS_UCDIS_UCDIS11_MASK                 (0x800U)
#define eMIOS_UCDIS_UCDIS11_SHIFT                (11U)
#define eMIOS_UCDIS_UCDIS11_WIDTH                (1U)
#define eMIOS_UCDIS_UCDIS11(x)                   (((uint32_t)(((uint32_t)(x)) << eMIOS_UCDIS_UCDIS11_SHIFT)) & eMIOS_UCDIS_UCDIS11_MASK)

#define eMIOS_UCDIS_UCDIS12_MASK                 (0x1000U)
#define eMIOS_UCDIS_UCDIS12_SHIFT                (12U)
#define eMIOS_UCDIS_UCDIS12_WIDTH                (1U)
#define eMIOS_UCDIS_UCDIS12(x)                   (((uint32_t)(((uint32_t)(x)) << eMIOS_UCDIS_UCDIS12_SHIFT)) & eMIOS_UCDIS_UCDIS12_MASK)

#define eMIOS_UCDIS_UCDIS13_MASK                 (0x2000U)
#define eMIOS_UCDIS_UCDIS13_SHIFT                (13U)
#define eMIOS_UCDIS_UCDIS13_WIDTH                (1U)
#define eMIOS_UCDIS_UCDIS13(x)                   (((uint32_t)(((uint32_t)(x)) << eMIOS_UCDIS_UCDIS13_SHIFT)) & eMIOS_UCDIS_UCDIS13_MASK)

#define eMIOS_UCDIS_UCDIS14_MASK                 (0x4000U)
#define eMIOS_UCDIS_UCDIS14_SHIFT                (14U)
#define eMIOS_UCDIS_UCDIS14_WIDTH                (1U)
#define eMIOS_UCDIS_UCDIS14(x)                   (((uint32_t)(((uint32_t)(x)) << eMIOS_UCDIS_UCDIS14_SHIFT)) & eMIOS_UCDIS_UCDIS14_MASK)

#define eMIOS_UCDIS_UCDIS15_MASK                 (0x8000U)
#define eMIOS_UCDIS_UCDIS15_SHIFT                (15U)
#define eMIOS_UCDIS_UCDIS15_WIDTH                (1U)
#define eMIOS_UCDIS_UCDIS15(x)                   (((uint32_t)(((uint32_t)(x)) << eMIOS_UCDIS_UCDIS15_SHIFT)) & eMIOS_UCDIS_UCDIS15_MASK)

#define eMIOS_UCDIS_UCDIS16_MASK                 (0x10000U)
#define eMIOS_UCDIS_UCDIS16_SHIFT                (16U)
#define eMIOS_UCDIS_UCDIS16_WIDTH                (1U)
#define eMIOS_UCDIS_UCDIS16(x)                   (((uint32_t)(((uint32_t)(x)) << eMIOS_UCDIS_UCDIS16_SHIFT)) & eMIOS_UCDIS_UCDIS16_MASK)

#define eMIOS_UCDIS_UCDIS17_MASK                 (0x20000U)
#define eMIOS_UCDIS_UCDIS17_SHIFT                (17U)
#define eMIOS_UCDIS_UCDIS17_WIDTH                (1U)
#define eMIOS_UCDIS_UCDIS17(x)                   (((uint32_t)(((uint32_t)(x)) << eMIOS_UCDIS_UCDIS17_SHIFT)) & eMIOS_UCDIS_UCDIS17_MASK)

#define eMIOS_UCDIS_UCDIS18_MASK                 (0x40000U)
#define eMIOS_UCDIS_UCDIS18_SHIFT                (18U)
#define eMIOS_UCDIS_UCDIS18_WIDTH                (1U)
#define eMIOS_UCDIS_UCDIS18(x)                   (((uint32_t)(((uint32_t)(x)) << eMIOS_UCDIS_UCDIS18_SHIFT)) & eMIOS_UCDIS_UCDIS18_MASK)

#define eMIOS_UCDIS_UCDIS19_MASK                 (0x80000U)
#define eMIOS_UCDIS_UCDIS19_SHIFT                (19U)
#define eMIOS_UCDIS_UCDIS19_WIDTH                (1U)
#define eMIOS_UCDIS_UCDIS19(x)                   (((uint32_t)(((uint32_t)(x)) << eMIOS_UCDIS_UCDIS19_SHIFT)) & eMIOS_UCDIS_UCDIS19_MASK)

#define eMIOS_UCDIS_UCDIS20_MASK                 (0x100000U)
#define eMIOS_UCDIS_UCDIS20_SHIFT                (20U)
#define eMIOS_UCDIS_UCDIS20_WIDTH                (1U)
#define eMIOS_UCDIS_UCDIS20(x)                   (((uint32_t)(((uint32_t)(x)) << eMIOS_UCDIS_UCDIS20_SHIFT)) & eMIOS_UCDIS_UCDIS20_MASK)

#define eMIOS_UCDIS_UCDIS21_MASK                 (0x200000U)
#define eMIOS_UCDIS_UCDIS21_SHIFT                (21U)
#define eMIOS_UCDIS_UCDIS21_WIDTH                (1U)
#define eMIOS_UCDIS_UCDIS21(x)                   (((uint32_t)(((uint32_t)(x)) << eMIOS_UCDIS_UCDIS21_SHIFT)) & eMIOS_UCDIS_UCDIS21_MASK)

#define eMIOS_UCDIS_UCDIS22_MASK                 (0x400000U)
#define eMIOS_UCDIS_UCDIS22_SHIFT                (22U)
#define eMIOS_UCDIS_UCDIS22_WIDTH                (1U)
#define eMIOS_UCDIS_UCDIS22(x)                   (((uint32_t)(((uint32_t)(x)) << eMIOS_UCDIS_UCDIS22_SHIFT)) & eMIOS_UCDIS_UCDIS22_MASK)

#define eMIOS_UCDIS_UCDIS23_MASK                 (0x800000U)
#define eMIOS_UCDIS_UCDIS23_SHIFT                (23U)
#define eMIOS_UCDIS_UCDIS23_WIDTH                (1U)
#define eMIOS_UCDIS_UCDIS23(x)                   (((uint32_t)(((uint32_t)(x)) << eMIOS_UCDIS_UCDIS23_SHIFT)) & eMIOS_UCDIS_UCDIS23_MASK)
/*! @} */

/*! @name A - UC A 0..UC A 23 */
/*! @{ */

#define eMIOS_A_A_MASK                           (0xFFFFU)
#define eMIOS_A_A_SHIFT                          (0U)
#define eMIOS_A_A_WIDTH                          (16U)
#define eMIOS_A_A(x)                             (((uint32_t)(((uint32_t)(x)) << eMIOS_A_A_SHIFT)) & eMIOS_A_A_MASK)
/*! @} */

/*! @name B - UC B 0..UC B 23 */
/*! @{ */

#define eMIOS_B_B_MASK                           (0xFFFFU)
#define eMIOS_B_B_SHIFT                          (0U)
#define eMIOS_B_B_WIDTH                          (16U)
#define eMIOS_B_B(x)                             (((uint32_t)(((uint32_t)(x)) << eMIOS_B_B_SHIFT)) & eMIOS_B_B_MASK)
/*! @} */

/*! @name CNT - UC Counter 0..UC Counter 23 */
/*! @{ */

#define eMIOS_CNT_C_MASK                         (0xFFFFU)
#define eMIOS_CNT_C_SHIFT                        (0U)
#define eMIOS_CNT_C_WIDTH                        (16U)
#define eMIOS_CNT_C(x)                           (((uint32_t)(((uint32_t)(x)) << eMIOS_CNT_C_SHIFT)) & eMIOS_CNT_C_MASK)
/*! @} */

/*! @name C - UC Control 0..UC Control 23 */
/*! @{ */

#define eMIOS_C_MODE_MASK                        (0x7FU)
#define eMIOS_C_MODE_SHIFT                       (0U)
#define eMIOS_C_MODE_WIDTH                       (7U)
#define eMIOS_C_MODE(x)                          (((uint32_t)(((uint32_t)(x)) << eMIOS_C_MODE_SHIFT)) & eMIOS_C_MODE_MASK)

#define eMIOS_C_EDPOL_MASK                       (0x80U)
#define eMIOS_C_EDPOL_SHIFT                      (7U)
#define eMIOS_C_EDPOL_WIDTH                      (1U)
#define eMIOS_C_EDPOL(x)                         (((uint32_t)(((uint32_t)(x)) << eMIOS_C_EDPOL_SHIFT)) & eMIOS_C_EDPOL_MASK)

#define eMIOS_C_EDSEL_MASK                       (0x100U)
#define eMIOS_C_EDSEL_SHIFT                      (8U)
#define eMIOS_C_EDSEL_WIDTH                      (1U)
#define eMIOS_C_EDSEL(x)                         (((uint32_t)(((uint32_t)(x)) << eMIOS_C_EDSEL_SHIFT)) & eMIOS_C_EDSEL_MASK)

#define eMIOS_C_BSL_MASK                         (0x600U)
#define eMIOS_C_BSL_SHIFT                        (9U)
#define eMIOS_C_BSL_WIDTH                        (2U)
#define eMIOS_C_BSL(x)                           (((uint32_t)(((uint32_t)(x)) << eMIOS_C_BSL_SHIFT)) & eMIOS_C_BSL_MASK)

#define eMIOS_C_FORCMB_MASK                      (0x1000U)
#define eMIOS_C_FORCMB_SHIFT                     (12U)
#define eMIOS_C_FORCMB_WIDTH                     (1U)
#define eMIOS_C_FORCMB(x)                        (((uint32_t)(((uint32_t)(x)) << eMIOS_C_FORCMB_SHIFT)) & eMIOS_C_FORCMB_MASK)

#define eMIOS_C_FORCMA_MASK                      (0x2000U)
#define eMIOS_C_FORCMA_SHIFT                     (13U)
#define eMIOS_C_FORCMA_WIDTH                     (1U)
#define eMIOS_C_FORCMA(x)                        (((uint32_t)(((uint32_t)(x)) << eMIOS_C_FORCMA_SHIFT)) & eMIOS_C_FORCMA_MASK)

#define eMIOS_C_FEN_MASK                         (0x20000U)
#define eMIOS_C_FEN_SHIFT                        (17U)
#define eMIOS_C_FEN_WIDTH                        (1U)
#define eMIOS_C_FEN(x)                           (((uint32_t)(((uint32_t)(x)) << eMIOS_C_FEN_SHIFT)) & eMIOS_C_FEN_MASK)

#define eMIOS_C_FCK_MASK                         (0x40000U)
#define eMIOS_C_FCK_SHIFT                        (18U)
#define eMIOS_C_FCK_WIDTH                        (1U)
#define eMIOS_C_FCK(x)                           (((uint32_t)(((uint32_t)(x)) << eMIOS_C_FCK_SHIFT)) & eMIOS_C_FCK_MASK)

#define eMIOS_C_IF_MASK                          (0x780000U)
#define eMIOS_C_IF_SHIFT                         (19U)
#define eMIOS_C_IF_WIDTH                         (4U)
#define eMIOS_C_IF(x)                            (((uint32_t)(((uint32_t)(x)) << eMIOS_C_IF_SHIFT)) & eMIOS_C_IF_MASK)

#define eMIOS_C_DMA_MASK                         (0x1000000U)
#define eMIOS_C_DMA_SHIFT                        (24U)
#define eMIOS_C_DMA_WIDTH                        (1U)
#define eMIOS_C_DMA(x)                           (((uint32_t)(((uint32_t)(x)) << eMIOS_C_DMA_SHIFT)) & eMIOS_C_DMA_MASK)

#define eMIOS_C_UCPREN_MASK                      (0x2000000U)
#define eMIOS_C_UCPREN_SHIFT                     (25U)
#define eMIOS_C_UCPREN_WIDTH                     (1U)
#define eMIOS_C_UCPREN(x)                        (((uint32_t)(((uint32_t)(x)) << eMIOS_C_UCPREN_SHIFT)) & eMIOS_C_UCPREN_MASK)

#define eMIOS_C_UCPRE_MASK                       (0xC000000U)
#define eMIOS_C_UCPRE_SHIFT                      (26U)
#define eMIOS_C_UCPRE_WIDTH                      (2U)
#define eMIOS_C_UCPRE(x)                         (((uint32_t)(((uint32_t)(x)) << eMIOS_C_UCPRE_SHIFT)) & eMIOS_C_UCPRE_MASK)

#define eMIOS_C_ODISSL_MASK                      (0x30000000U)
#define eMIOS_C_ODISSL_SHIFT                     (28U)
#define eMIOS_C_ODISSL_WIDTH                     (2U)
#define eMIOS_C_ODISSL(x)                        (((uint32_t)(((uint32_t)(x)) << eMIOS_C_ODISSL_SHIFT)) & eMIOS_C_ODISSL_MASK)

#define eMIOS_C_ODIS_MASK                        (0x40000000U)
#define eMIOS_C_ODIS_SHIFT                       (30U)
#define eMIOS_C_ODIS_WIDTH                       (1U)
#define eMIOS_C_ODIS(x)                          (((uint32_t)(((uint32_t)(x)) << eMIOS_C_ODIS_SHIFT)) & eMIOS_C_ODIS_MASK)

#define eMIOS_C_FREN_MASK                        (0x80000000U)
#define eMIOS_C_FREN_SHIFT                       (31U)
#define eMIOS_C_FREN_WIDTH                       (1U)
#define eMIOS_C_FREN(x)                          (((uint32_t)(((uint32_t)(x)) << eMIOS_C_FREN_SHIFT)) & eMIOS_C_FREN_MASK)
/*! @} */

/*! @name S - UC Status 0..UC Status 23 */
/*! @{ */

#define eMIOS_S_FLAG_MASK                        (0x1U)
#define eMIOS_S_FLAG_SHIFT                       (0U)
#define eMIOS_S_FLAG_WIDTH                       (1U)
#define eMIOS_S_FLAG(x)                          (((uint32_t)(((uint32_t)(x)) << eMIOS_S_FLAG_SHIFT)) & eMIOS_S_FLAG_MASK)

#define eMIOS_S_UCOUT_MASK                       (0x2U)
#define eMIOS_S_UCOUT_SHIFT                      (1U)
#define eMIOS_S_UCOUT_WIDTH                      (1U)
#define eMIOS_S_UCOUT(x)                         (((uint32_t)(((uint32_t)(x)) << eMIOS_S_UCOUT_SHIFT)) & eMIOS_S_UCOUT_MASK)

#define eMIOS_S_UCIN_MASK                        (0x4U)
#define eMIOS_S_UCIN_SHIFT                       (2U)
#define eMIOS_S_UCIN_WIDTH                       (1U)
#define eMIOS_S_UCIN(x)                          (((uint32_t)(((uint32_t)(x)) << eMIOS_S_UCIN_SHIFT)) & eMIOS_S_UCIN_MASK)

#define eMIOS_S_OVFL_MASK                        (0x8000U)
#define eMIOS_S_OVFL_SHIFT                       (15U)
#define eMIOS_S_OVFL_WIDTH                       (1U)
#define eMIOS_S_OVFL(x)                          (((uint32_t)(((uint32_t)(x)) << eMIOS_S_OVFL_SHIFT)) & eMIOS_S_OVFL_MASK)

#define eMIOS_S_OVR_MASK                         (0x80000000U)
#define eMIOS_S_OVR_SHIFT                        (31U)
#define eMIOS_S_OVR_WIDTH                        (1U)
#define eMIOS_S_OVR(x)                           (((uint32_t)(((uint32_t)(x)) << eMIOS_S_OVR_SHIFT)) & eMIOS_S_OVR_MASK)
/*! @} */

/*! @name ALTA - Alternate Address 0..Alternate Address 23 */
/*! @{ */

#define eMIOS_ALTA_ALTA_MASK                     (0xFFFFU)
#define eMIOS_ALTA_ALTA_SHIFT                    (0U)
#define eMIOS_ALTA_ALTA_WIDTH                    (16U)
#define eMIOS_ALTA_ALTA(x)                       (((uint32_t)(((uint32_t)(x)) << eMIOS_ALTA_ALTA_SHIFT)) & eMIOS_ALTA_ALTA_MASK)
/*! @} */

/*! @name C2 - UC Control 2 0..UC Control 2 23 */
/*! @{ */

#define eMIOS_C2_UCRELDEL_INT_MASK               (0x1FU)
#define eMIOS_C2_UCRELDEL_INT_SHIFT              (0U)
#define eMIOS_C2_UCRELDEL_INT_WIDTH              (5U)
#define eMIOS_C2_UCRELDEL_INT(x)                 (((uint32_t)(((uint32_t)(x)) << eMIOS_C2_UCRELDEL_INT_SHIFT)) & eMIOS_C2_UCRELDEL_INT_MASK)

#define eMIOS_C2_UCPRECLK_MASK                   (0x4000U)
#define eMIOS_C2_UCPRECLK_SHIFT                  (14U)
#define eMIOS_C2_UCPRECLK_WIDTH                  (1U)
#define eMIOS_C2_UCPRECLK(x)                     (((uint32_t)(((uint32_t)(x)) << eMIOS_C2_UCPRECLK_SHIFT)) & eMIOS_C2_UCPRECLK_MASK)

#define eMIOS_C2_UCEXTPRE_MASK                   (0xF0000U)
#define eMIOS_C2_UCEXTPRE_SHIFT                  (16U)
#define eMIOS_C2_UCEXTPRE_WIDTH                  (4U)
#define eMIOS_C2_UCEXTPRE(x)                     (((uint32_t)(((uint32_t)(x)) << eMIOS_C2_UCEXTPRE_SHIFT)) & eMIOS_C2_UCEXTPRE_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group eMIOS_Register_Masks */

/*!
 * @}
 */ /* end of group eMIOS_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_eMIOS_H_) */
