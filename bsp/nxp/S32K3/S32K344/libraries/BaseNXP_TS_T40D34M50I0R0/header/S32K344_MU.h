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
 * @file S32K344_MU.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_MU
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
#if !defined(S32K344_MU_H_)  /* Check if memory map has not been already included */
#define S32K344_MU_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- MU Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MU_Peripheral_Access_Layer MU Peripheral Access Layer
 * @{
 */

/** MU - Size of Registers Arrays */
#define MU_TR_COUNT                               4u
#define MU_RR_COUNT                               4u

/** MU - Register Layout Typedef */
typedef struct {
  __I  uint32_t VER;                               /**< Version ID Register, offset: 0x0 */
  __I  uint32_t PAR;                               /**< Parameter Register, offset: 0x4 */
  __IO uint32_t CR;                                /**< Control Register, offset: 0x8 */
  __IO uint32_t SR;                                /**< Status Register, offset: 0xC */
  __IO uint32_t CCR0;                              /**< Core Control Register 0, offset: 0x10 */
  uint8_t RESERVED_0[4];
  __IO uint32_t CSSR0;                             /**< Core Sticky Status Register 0, offset: 0x18 */
  uint8_t RESERVED_1[228];
  __IO uint32_t FCR;                               /**< Flag Control Register, offset: 0x100 */
  __I  uint32_t FSR;                               /**< Flag Status Register, offset: 0x104 */
  uint8_t RESERVED_2[8];
  __IO uint32_t GIER;                              /**< General Interrupt Enable Register, offset: 0x110 */
  __IO uint32_t GCR;                               /**< General Control Register, offset: 0x114 */
  __IO uint32_t GSR;                               /**< General Status Register, offset: 0x118 */
  uint8_t RESERVED_3[4];
  __IO uint32_t TCR;                               /**< Transmit Control Register, offset: 0x120 */
  __I  uint32_t TSR;                               /**< Transmit Status Register, offset: 0x124 */
  __IO uint32_t RCR;                               /**< Receive Control Register, offset: 0x128 */
  __I  uint32_t RSR;                               /**< Receive Status Register, offset: 0x12C */
  uint8_t RESERVED_4[208];
  __IO uint32_t TR[MU_TR_COUNT];                   /**< Transmit Register, array offset: 0x200, array step: 0x4 */
  uint8_t RESERVED_5[112];
  __I  uint32_t RR[MU_RR_COUNT];                   /**< Receive Register, array offset: 0x280, array step: 0x4 */
} MU_Type, *MU_MemMapPtr;

/** Number of instances of the MU module. */
#define MU_INSTANCE_COUNT                        (2u)

/* MU - Peripheral instance base addresses */
/** Peripheral MU_0__MUB base address */
#define IP_MU_0__MUB_BASE                        (0x4038C000u)
/** Peripheral MU_0__MUB base pointer */
#define IP_MU_0__MUB                             ((MU_Type *)IP_MU_0__MUB_BASE)
/** Peripheral MU_1__MUB base address */
#define IP_MU_1__MUB_BASE                        (0x404EC000u)
/** Peripheral MU_1__MUB base pointer */
#define IP_MU_1__MUB                             ((MU_Type *)IP_MU_1__MUB_BASE)
/** Array initializer of MU peripheral base addresses */
#define IP_MU_BASE_ADDRS                         { IP_MU_0__MUB_BASE, IP_MU_1__MUB_BASE }
/** Array initializer of MU peripheral base pointers */
#define IP_MU_BASE_PTRS                          { IP_MU_0__MUB, IP_MU_1__MUB }

/* ----------------------------------------------------------------------------
   -- MU Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MU_Register_Masks MU Register Masks
 * @{
 */

/*! @name VER - Version ID Register */
/*! @{ */

#define MU_VER_FEATURE_MASK                      (0xFFFFU)
#define MU_VER_FEATURE_SHIFT                     (0U)
#define MU_VER_FEATURE_WIDTH                     (16U)
#define MU_VER_FEATURE(x)                        (((uint32_t)(((uint32_t)(x)) << MU_VER_FEATURE_SHIFT)) & MU_VER_FEATURE_MASK)

#define MU_VER_MINOR_MASK                        (0xFF0000U)
#define MU_VER_MINOR_SHIFT                       (16U)
#define MU_VER_MINOR_WIDTH                       (8U)
#define MU_VER_MINOR(x)                          (((uint32_t)(((uint32_t)(x)) << MU_VER_MINOR_SHIFT)) & MU_VER_MINOR_MASK)

#define MU_VER_MAJOR_MASK                        (0xFF000000U)
#define MU_VER_MAJOR_SHIFT                       (24U)
#define MU_VER_MAJOR_WIDTH                       (8U)
#define MU_VER_MAJOR(x)                          (((uint32_t)(((uint32_t)(x)) << MU_VER_MAJOR_SHIFT)) & MU_VER_MAJOR_MASK)
/*! @} */

/*! @name PAR - Parameter Register */
/*! @{ */

#define MU_PAR_TR_NUM_MASK                       (0xFFU)
#define MU_PAR_TR_NUM_SHIFT                      (0U)
#define MU_PAR_TR_NUM_WIDTH                      (8U)
#define MU_PAR_TR_NUM(x)                         (((uint32_t)(((uint32_t)(x)) << MU_PAR_TR_NUM_SHIFT)) & MU_PAR_TR_NUM_MASK)

#define MU_PAR_RR_NUM_MASK                       (0xFF00U)
#define MU_PAR_RR_NUM_SHIFT                      (8U)
#define MU_PAR_RR_NUM_WIDTH                      (8U)
#define MU_PAR_RR_NUM(x)                         (((uint32_t)(((uint32_t)(x)) << MU_PAR_RR_NUM_SHIFT)) & MU_PAR_RR_NUM_MASK)

#define MU_PAR_GIR_NUM_MASK                      (0xFF0000U)
#define MU_PAR_GIR_NUM_SHIFT                     (16U)
#define MU_PAR_GIR_NUM_WIDTH                     (8U)
#define MU_PAR_GIR_NUM(x)                        (((uint32_t)(((uint32_t)(x)) << MU_PAR_GIR_NUM_SHIFT)) & MU_PAR_GIR_NUM_MASK)

#define MU_PAR_FLAG_WIDTH_MASK                   (0xFF000000U)
#define MU_PAR_FLAG_WIDTH_SHIFT                  (24U)
#define MU_PAR_FLAG_WIDTH_WIDTH                  (8U)
#define MU_PAR_FLAG_WIDTH(x)                     (((uint32_t)(((uint32_t)(x)) << MU_PAR_FLAG_WIDTH_SHIFT)) & MU_PAR_FLAG_WIDTH_MASK)
/*! @} */

/*! @name CR - Control Register */
/*! @{ */

#define MU_CR_MUR_MASK                           (0x1U)
#define MU_CR_MUR_SHIFT                          (0U)
#define MU_CR_MUR_WIDTH                          (1U)
#define MU_CR_MUR(x)                             (((uint32_t)(((uint32_t)(x)) << MU_CR_MUR_SHIFT)) & MU_CR_MUR_MASK)

#define MU_CR_MURIE_MASK                         (0x2U)
#define MU_CR_MURIE_SHIFT                        (1U)
#define MU_CR_MURIE_WIDTH                        (1U)
#define MU_CR_MURIE(x)                           (((uint32_t)(((uint32_t)(x)) << MU_CR_MURIE_SHIFT)) & MU_CR_MURIE_MASK)
/*! @} */

/*! @name SR - Status Register */
/*! @{ */

#define MU_SR_MURS_MASK                          (0x1U)
#define MU_SR_MURS_SHIFT                         (0U)
#define MU_SR_MURS_WIDTH                         (1U)
#define MU_SR_MURS(x)                            (((uint32_t)(((uint32_t)(x)) << MU_SR_MURS_SHIFT)) & MU_SR_MURS_MASK)

#define MU_SR_MURIP_MASK                         (0x2U)
#define MU_SR_MURIP_SHIFT                        (1U)
#define MU_SR_MURIP_WIDTH                        (1U)
#define MU_SR_MURIP(x)                           (((uint32_t)(((uint32_t)(x)) << MU_SR_MURIP_SHIFT)) & MU_SR_MURIP_MASK)

#define MU_SR_EP_MASK                            (0x4U)
#define MU_SR_EP_SHIFT                           (2U)
#define MU_SR_EP_WIDTH                           (1U)
#define MU_SR_EP(x)                              (((uint32_t)(((uint32_t)(x)) << MU_SR_EP_SHIFT)) & MU_SR_EP_MASK)

#define MU_SR_FUP_MASK                           (0x8U)
#define MU_SR_FUP_SHIFT                          (3U)
#define MU_SR_FUP_WIDTH                          (1U)
#define MU_SR_FUP(x)                             (((uint32_t)(((uint32_t)(x)) << MU_SR_FUP_SHIFT)) & MU_SR_FUP_MASK)

#define MU_SR_GIRP_MASK                          (0x10U)
#define MU_SR_GIRP_SHIFT                         (4U)
#define MU_SR_GIRP_WIDTH                         (1U)
#define MU_SR_GIRP(x)                            (((uint32_t)(((uint32_t)(x)) << MU_SR_GIRP_SHIFT)) & MU_SR_GIRP_MASK)

#define MU_SR_TEP_MASK                           (0x20U)
#define MU_SR_TEP_SHIFT                          (5U)
#define MU_SR_TEP_WIDTH                          (1U)
#define MU_SR_TEP(x)                             (((uint32_t)(((uint32_t)(x)) << MU_SR_TEP_SHIFT)) & MU_SR_TEP_MASK)

#define MU_SR_RFP_MASK                           (0x40U)
#define MU_SR_RFP_SHIFT                          (6U)
#define MU_SR_RFP_WIDTH                          (1U)
#define MU_SR_RFP(x)                             (((uint32_t)(((uint32_t)(x)) << MU_SR_RFP_SHIFT)) & MU_SR_RFP_MASK)
/*! @} */

/*! @name CCR0 - Core Control Register 0 */
/*! @{ */

#define MU_CCR0_NMI_MASK                         (0x1U)
#define MU_CCR0_NMI_SHIFT                        (0U)
#define MU_CCR0_NMI_WIDTH                        (1U)
#define MU_CCR0_NMI(x)                           (((uint32_t)(((uint32_t)(x)) << MU_CCR0_NMI_SHIFT)) & MU_CCR0_NMI_MASK)
/*! @} */

/*! @name CSSR0 - Core Sticky Status Register 0 */
/*! @{ */

#define MU_CSSR0_NMIC_MASK                       (0x1U)
#define MU_CSSR0_NMIC_SHIFT                      (0U)
#define MU_CSSR0_NMIC_WIDTH                      (1U)
#define MU_CSSR0_NMIC(x)                         (((uint32_t)(((uint32_t)(x)) << MU_CSSR0_NMIC_SHIFT)) & MU_CSSR0_NMIC_MASK)
/*! @} */

/*! @name FCR - Flag Control Register */
/*! @{ */

#define MU_FCR_F0_MASK                           (0x1U)
#define MU_FCR_F0_SHIFT                          (0U)
#define MU_FCR_F0_WIDTH                          (1U)
#define MU_FCR_F0(x)                             (((uint32_t)(((uint32_t)(x)) << MU_FCR_F0_SHIFT)) & MU_FCR_F0_MASK)

#define MU_FCR_F1_MASK                           (0x2U)
#define MU_FCR_F1_SHIFT                          (1U)
#define MU_FCR_F1_WIDTH                          (1U)
#define MU_FCR_F1(x)                             (((uint32_t)(((uint32_t)(x)) << MU_FCR_F1_SHIFT)) & MU_FCR_F1_MASK)

#define MU_FCR_F2_MASK                           (0x4U)
#define MU_FCR_F2_SHIFT                          (2U)
#define MU_FCR_F2_WIDTH                          (1U)
#define MU_FCR_F2(x)                             (((uint32_t)(((uint32_t)(x)) << MU_FCR_F2_SHIFT)) & MU_FCR_F2_MASK)

#define MU_FCR_F3_MASK                           (0x8U)
#define MU_FCR_F3_SHIFT                          (3U)
#define MU_FCR_F3_WIDTH                          (1U)
#define MU_FCR_F3(x)                             (((uint32_t)(((uint32_t)(x)) << MU_FCR_F3_SHIFT)) & MU_FCR_F3_MASK)

#define MU_FCR_F4_MASK                           (0x10U)
#define MU_FCR_F4_SHIFT                          (4U)
#define MU_FCR_F4_WIDTH                          (1U)
#define MU_FCR_F4(x)                             (((uint32_t)(((uint32_t)(x)) << MU_FCR_F4_SHIFT)) & MU_FCR_F4_MASK)

#define MU_FCR_F5_MASK                           (0x20U)
#define MU_FCR_F5_SHIFT                          (5U)
#define MU_FCR_F5_WIDTH                          (1U)
#define MU_FCR_F5(x)                             (((uint32_t)(((uint32_t)(x)) << MU_FCR_F5_SHIFT)) & MU_FCR_F5_MASK)

#define MU_FCR_F6_MASK                           (0x40U)
#define MU_FCR_F6_SHIFT                          (6U)
#define MU_FCR_F6_WIDTH                          (1U)
#define MU_FCR_F6(x)                             (((uint32_t)(((uint32_t)(x)) << MU_FCR_F6_SHIFT)) & MU_FCR_F6_MASK)

#define MU_FCR_F7_MASK                           (0x80U)
#define MU_FCR_F7_SHIFT                          (7U)
#define MU_FCR_F7_WIDTH                          (1U)
#define MU_FCR_F7(x)                             (((uint32_t)(((uint32_t)(x)) << MU_FCR_F7_SHIFT)) & MU_FCR_F7_MASK)

#define MU_FCR_F8_MASK                           (0x100U)
#define MU_FCR_F8_SHIFT                          (8U)
#define MU_FCR_F8_WIDTH                          (1U)
#define MU_FCR_F8(x)                             (((uint32_t)(((uint32_t)(x)) << MU_FCR_F8_SHIFT)) & MU_FCR_F8_MASK)

#define MU_FCR_F9_MASK                           (0x200U)
#define MU_FCR_F9_SHIFT                          (9U)
#define MU_FCR_F9_WIDTH                          (1U)
#define MU_FCR_F9(x)                             (((uint32_t)(((uint32_t)(x)) << MU_FCR_F9_SHIFT)) & MU_FCR_F9_MASK)

#define MU_FCR_F10_MASK                          (0x400U)
#define MU_FCR_F10_SHIFT                         (10U)
#define MU_FCR_F10_WIDTH                         (1U)
#define MU_FCR_F10(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FCR_F10_SHIFT)) & MU_FCR_F10_MASK)

#define MU_FCR_F11_MASK                          (0x800U)
#define MU_FCR_F11_SHIFT                         (11U)
#define MU_FCR_F11_WIDTH                         (1U)
#define MU_FCR_F11(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FCR_F11_SHIFT)) & MU_FCR_F11_MASK)

#define MU_FCR_F12_MASK                          (0x1000U)
#define MU_FCR_F12_SHIFT                         (12U)
#define MU_FCR_F12_WIDTH                         (1U)
#define MU_FCR_F12(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FCR_F12_SHIFT)) & MU_FCR_F12_MASK)

#define MU_FCR_F13_MASK                          (0x2000U)
#define MU_FCR_F13_SHIFT                         (13U)
#define MU_FCR_F13_WIDTH                         (1U)
#define MU_FCR_F13(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FCR_F13_SHIFT)) & MU_FCR_F13_MASK)

#define MU_FCR_F14_MASK                          (0x4000U)
#define MU_FCR_F14_SHIFT                         (14U)
#define MU_FCR_F14_WIDTH                         (1U)
#define MU_FCR_F14(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FCR_F14_SHIFT)) & MU_FCR_F14_MASK)

#define MU_FCR_F15_MASK                          (0x8000U)
#define MU_FCR_F15_SHIFT                         (15U)
#define MU_FCR_F15_WIDTH                         (1U)
#define MU_FCR_F15(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FCR_F15_SHIFT)) & MU_FCR_F15_MASK)

#define MU_FCR_F16_MASK                          (0x10000U)
#define MU_FCR_F16_SHIFT                         (16U)
#define MU_FCR_F16_WIDTH                         (1U)
#define MU_FCR_F16(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FCR_F16_SHIFT)) & MU_FCR_F16_MASK)

#define MU_FCR_F17_MASK                          (0x20000U)
#define MU_FCR_F17_SHIFT                         (17U)
#define MU_FCR_F17_WIDTH                         (1U)
#define MU_FCR_F17(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FCR_F17_SHIFT)) & MU_FCR_F17_MASK)

#define MU_FCR_F18_MASK                          (0x40000U)
#define MU_FCR_F18_SHIFT                         (18U)
#define MU_FCR_F18_WIDTH                         (1U)
#define MU_FCR_F18(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FCR_F18_SHIFT)) & MU_FCR_F18_MASK)

#define MU_FCR_F19_MASK                          (0x80000U)
#define MU_FCR_F19_SHIFT                         (19U)
#define MU_FCR_F19_WIDTH                         (1U)
#define MU_FCR_F19(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FCR_F19_SHIFT)) & MU_FCR_F19_MASK)

#define MU_FCR_F20_MASK                          (0x100000U)
#define MU_FCR_F20_SHIFT                         (20U)
#define MU_FCR_F20_WIDTH                         (1U)
#define MU_FCR_F20(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FCR_F20_SHIFT)) & MU_FCR_F20_MASK)

#define MU_FCR_F21_MASK                          (0x200000U)
#define MU_FCR_F21_SHIFT                         (21U)
#define MU_FCR_F21_WIDTH                         (1U)
#define MU_FCR_F21(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FCR_F21_SHIFT)) & MU_FCR_F21_MASK)

#define MU_FCR_F22_MASK                          (0x400000U)
#define MU_FCR_F22_SHIFT                         (22U)
#define MU_FCR_F22_WIDTH                         (1U)
#define MU_FCR_F22(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FCR_F22_SHIFT)) & MU_FCR_F22_MASK)

#define MU_FCR_F23_MASK                          (0x800000U)
#define MU_FCR_F23_SHIFT                         (23U)
#define MU_FCR_F23_WIDTH                         (1U)
#define MU_FCR_F23(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FCR_F23_SHIFT)) & MU_FCR_F23_MASK)

#define MU_FCR_F24_MASK                          (0x1000000U)
#define MU_FCR_F24_SHIFT                         (24U)
#define MU_FCR_F24_WIDTH                         (1U)
#define MU_FCR_F24(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FCR_F24_SHIFT)) & MU_FCR_F24_MASK)

#define MU_FCR_F25_MASK                          (0x2000000U)
#define MU_FCR_F25_SHIFT                         (25U)
#define MU_FCR_F25_WIDTH                         (1U)
#define MU_FCR_F25(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FCR_F25_SHIFT)) & MU_FCR_F25_MASK)

#define MU_FCR_F26_MASK                          (0x4000000U)
#define MU_FCR_F26_SHIFT                         (26U)
#define MU_FCR_F26_WIDTH                         (1U)
#define MU_FCR_F26(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FCR_F26_SHIFT)) & MU_FCR_F26_MASK)

#define MU_FCR_F27_MASK                          (0x8000000U)
#define MU_FCR_F27_SHIFT                         (27U)
#define MU_FCR_F27_WIDTH                         (1U)
#define MU_FCR_F27(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FCR_F27_SHIFT)) & MU_FCR_F27_MASK)

#define MU_FCR_F28_MASK                          (0x10000000U)
#define MU_FCR_F28_SHIFT                         (28U)
#define MU_FCR_F28_WIDTH                         (1U)
#define MU_FCR_F28(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FCR_F28_SHIFT)) & MU_FCR_F28_MASK)

#define MU_FCR_F29_MASK                          (0x20000000U)
#define MU_FCR_F29_SHIFT                         (29U)
#define MU_FCR_F29_WIDTH                         (1U)
#define MU_FCR_F29(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FCR_F29_SHIFT)) & MU_FCR_F29_MASK)

#define MU_FCR_F30_MASK                          (0x40000000U)
#define MU_FCR_F30_SHIFT                         (30U)
#define MU_FCR_F30_WIDTH                         (1U)
#define MU_FCR_F30(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FCR_F30_SHIFT)) & MU_FCR_F30_MASK)

#define MU_FCR_F31_MASK                          (0x80000000U)
#define MU_FCR_F31_SHIFT                         (31U)
#define MU_FCR_F31_WIDTH                         (1U)
#define MU_FCR_F31(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FCR_F31_SHIFT)) & MU_FCR_F31_MASK)
/*! @} */

/*! @name FSR - Flag Status Register */
/*! @{ */

#define MU_FSR_F0_MASK                           (0x1U)
#define MU_FSR_F0_SHIFT                          (0U)
#define MU_FSR_F0_WIDTH                          (1U)
#define MU_FSR_F0(x)                             (((uint32_t)(((uint32_t)(x)) << MU_FSR_F0_SHIFT)) & MU_FSR_F0_MASK)

#define MU_FSR_F1_MASK                           (0x2U)
#define MU_FSR_F1_SHIFT                          (1U)
#define MU_FSR_F1_WIDTH                          (1U)
#define MU_FSR_F1(x)                             (((uint32_t)(((uint32_t)(x)) << MU_FSR_F1_SHIFT)) & MU_FSR_F1_MASK)

#define MU_FSR_F2_MASK                           (0x4U)
#define MU_FSR_F2_SHIFT                          (2U)
#define MU_FSR_F2_WIDTH                          (1U)
#define MU_FSR_F2(x)                             (((uint32_t)(((uint32_t)(x)) << MU_FSR_F2_SHIFT)) & MU_FSR_F2_MASK)

#define MU_FSR_F3_MASK                           (0x8U)
#define MU_FSR_F3_SHIFT                          (3U)
#define MU_FSR_F3_WIDTH                          (1U)
#define MU_FSR_F3(x)                             (((uint32_t)(((uint32_t)(x)) << MU_FSR_F3_SHIFT)) & MU_FSR_F3_MASK)

#define MU_FSR_F4_MASK                           (0x10U)
#define MU_FSR_F4_SHIFT                          (4U)
#define MU_FSR_F4_WIDTH                          (1U)
#define MU_FSR_F4(x)                             (((uint32_t)(((uint32_t)(x)) << MU_FSR_F4_SHIFT)) & MU_FSR_F4_MASK)

#define MU_FSR_F5_MASK                           (0x20U)
#define MU_FSR_F5_SHIFT                          (5U)
#define MU_FSR_F5_WIDTH                          (1U)
#define MU_FSR_F5(x)                             (((uint32_t)(((uint32_t)(x)) << MU_FSR_F5_SHIFT)) & MU_FSR_F5_MASK)

#define MU_FSR_F6_MASK                           (0x40U)
#define MU_FSR_F6_SHIFT                          (6U)
#define MU_FSR_F6_WIDTH                          (1U)
#define MU_FSR_F6(x)                             (((uint32_t)(((uint32_t)(x)) << MU_FSR_F6_SHIFT)) & MU_FSR_F6_MASK)

#define MU_FSR_F7_MASK                           (0x80U)
#define MU_FSR_F7_SHIFT                          (7U)
#define MU_FSR_F7_WIDTH                          (1U)
#define MU_FSR_F7(x)                             (((uint32_t)(((uint32_t)(x)) << MU_FSR_F7_SHIFT)) & MU_FSR_F7_MASK)

#define MU_FSR_F8_MASK                           (0x100U)
#define MU_FSR_F8_SHIFT                          (8U)
#define MU_FSR_F8_WIDTH                          (1U)
#define MU_FSR_F8(x)                             (((uint32_t)(((uint32_t)(x)) << MU_FSR_F8_SHIFT)) & MU_FSR_F8_MASK)

#define MU_FSR_F9_MASK                           (0x200U)
#define MU_FSR_F9_SHIFT                          (9U)
#define MU_FSR_F9_WIDTH                          (1U)
#define MU_FSR_F9(x)                             (((uint32_t)(((uint32_t)(x)) << MU_FSR_F9_SHIFT)) & MU_FSR_F9_MASK)

#define MU_FSR_F10_MASK                          (0x400U)
#define MU_FSR_F10_SHIFT                         (10U)
#define MU_FSR_F10_WIDTH                         (1U)
#define MU_FSR_F10(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FSR_F10_SHIFT)) & MU_FSR_F10_MASK)

#define MU_FSR_F11_MASK                          (0x800U)
#define MU_FSR_F11_SHIFT                         (11U)
#define MU_FSR_F11_WIDTH                         (1U)
#define MU_FSR_F11(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FSR_F11_SHIFT)) & MU_FSR_F11_MASK)

#define MU_FSR_F12_MASK                          (0x1000U)
#define MU_FSR_F12_SHIFT                         (12U)
#define MU_FSR_F12_WIDTH                         (1U)
#define MU_FSR_F12(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FSR_F12_SHIFT)) & MU_FSR_F12_MASK)

#define MU_FSR_F13_MASK                          (0x2000U)
#define MU_FSR_F13_SHIFT                         (13U)
#define MU_FSR_F13_WIDTH                         (1U)
#define MU_FSR_F13(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FSR_F13_SHIFT)) & MU_FSR_F13_MASK)

#define MU_FSR_F14_MASK                          (0x4000U)
#define MU_FSR_F14_SHIFT                         (14U)
#define MU_FSR_F14_WIDTH                         (1U)
#define MU_FSR_F14(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FSR_F14_SHIFT)) & MU_FSR_F14_MASK)

#define MU_FSR_F15_MASK                          (0x8000U)
#define MU_FSR_F15_SHIFT                         (15U)
#define MU_FSR_F15_WIDTH                         (1U)
#define MU_FSR_F15(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FSR_F15_SHIFT)) & MU_FSR_F15_MASK)

#define MU_FSR_F16_MASK                          (0x10000U)
#define MU_FSR_F16_SHIFT                         (16U)
#define MU_FSR_F16_WIDTH                         (1U)
#define MU_FSR_F16(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FSR_F16_SHIFT)) & MU_FSR_F16_MASK)

#define MU_FSR_F17_MASK                          (0x20000U)
#define MU_FSR_F17_SHIFT                         (17U)
#define MU_FSR_F17_WIDTH                         (1U)
#define MU_FSR_F17(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FSR_F17_SHIFT)) & MU_FSR_F17_MASK)

#define MU_FSR_F18_MASK                          (0x40000U)
#define MU_FSR_F18_SHIFT                         (18U)
#define MU_FSR_F18_WIDTH                         (1U)
#define MU_FSR_F18(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FSR_F18_SHIFT)) & MU_FSR_F18_MASK)

#define MU_FSR_F19_MASK                          (0x80000U)
#define MU_FSR_F19_SHIFT                         (19U)
#define MU_FSR_F19_WIDTH                         (1U)
#define MU_FSR_F19(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FSR_F19_SHIFT)) & MU_FSR_F19_MASK)

#define MU_FSR_F20_MASK                          (0x100000U)
#define MU_FSR_F20_SHIFT                         (20U)
#define MU_FSR_F20_WIDTH                         (1U)
#define MU_FSR_F20(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FSR_F20_SHIFT)) & MU_FSR_F20_MASK)

#define MU_FSR_F21_MASK                          (0x200000U)
#define MU_FSR_F21_SHIFT                         (21U)
#define MU_FSR_F21_WIDTH                         (1U)
#define MU_FSR_F21(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FSR_F21_SHIFT)) & MU_FSR_F21_MASK)

#define MU_FSR_F22_MASK                          (0x400000U)
#define MU_FSR_F22_SHIFT                         (22U)
#define MU_FSR_F22_WIDTH                         (1U)
#define MU_FSR_F22(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FSR_F22_SHIFT)) & MU_FSR_F22_MASK)

#define MU_FSR_F23_MASK                          (0x800000U)
#define MU_FSR_F23_SHIFT                         (23U)
#define MU_FSR_F23_WIDTH                         (1U)
#define MU_FSR_F23(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FSR_F23_SHIFT)) & MU_FSR_F23_MASK)

#define MU_FSR_F24_MASK                          (0x1000000U)
#define MU_FSR_F24_SHIFT                         (24U)
#define MU_FSR_F24_WIDTH                         (1U)
#define MU_FSR_F24(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FSR_F24_SHIFT)) & MU_FSR_F24_MASK)

#define MU_FSR_F25_MASK                          (0x2000000U)
#define MU_FSR_F25_SHIFT                         (25U)
#define MU_FSR_F25_WIDTH                         (1U)
#define MU_FSR_F25(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FSR_F25_SHIFT)) & MU_FSR_F25_MASK)

#define MU_FSR_F26_MASK                          (0x4000000U)
#define MU_FSR_F26_SHIFT                         (26U)
#define MU_FSR_F26_WIDTH                         (1U)
#define MU_FSR_F26(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FSR_F26_SHIFT)) & MU_FSR_F26_MASK)

#define MU_FSR_F27_MASK                          (0x8000000U)
#define MU_FSR_F27_SHIFT                         (27U)
#define MU_FSR_F27_WIDTH                         (1U)
#define MU_FSR_F27(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FSR_F27_SHIFT)) & MU_FSR_F27_MASK)

#define MU_FSR_F28_MASK                          (0x10000000U)
#define MU_FSR_F28_SHIFT                         (28U)
#define MU_FSR_F28_WIDTH                         (1U)
#define MU_FSR_F28(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FSR_F28_SHIFT)) & MU_FSR_F28_MASK)

#define MU_FSR_F29_MASK                          (0x20000000U)
#define MU_FSR_F29_SHIFT                         (29U)
#define MU_FSR_F29_WIDTH                         (1U)
#define MU_FSR_F29(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FSR_F29_SHIFT)) & MU_FSR_F29_MASK)

#define MU_FSR_F30_MASK                          (0x40000000U)
#define MU_FSR_F30_SHIFT                         (30U)
#define MU_FSR_F30_WIDTH                         (1U)
#define MU_FSR_F30(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FSR_F30_SHIFT)) & MU_FSR_F30_MASK)

#define MU_FSR_F31_MASK                          (0x80000000U)
#define MU_FSR_F31_SHIFT                         (31U)
#define MU_FSR_F31_WIDTH                         (1U)
#define MU_FSR_F31(x)                            (((uint32_t)(((uint32_t)(x)) << MU_FSR_F31_SHIFT)) & MU_FSR_F31_MASK)
/*! @} */

/*! @name GIER - General Interrupt Enable Register */
/*! @{ */

#define MU_GIER_GIE0_MASK                        (0x1U)
#define MU_GIER_GIE0_SHIFT                       (0U)
#define MU_GIER_GIE0_WIDTH                       (1U)
#define MU_GIER_GIE0(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE0_SHIFT)) & MU_GIER_GIE0_MASK)

#define MU_GIER_GIE1_MASK                        (0x2U)
#define MU_GIER_GIE1_SHIFT                       (1U)
#define MU_GIER_GIE1_WIDTH                       (1U)
#define MU_GIER_GIE1(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE1_SHIFT)) & MU_GIER_GIE1_MASK)

#define MU_GIER_GIE2_MASK                        (0x4U)
#define MU_GIER_GIE2_SHIFT                       (2U)
#define MU_GIER_GIE2_WIDTH                       (1U)
#define MU_GIER_GIE2(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE2_SHIFT)) & MU_GIER_GIE2_MASK)

#define MU_GIER_GIE3_MASK                        (0x8U)
#define MU_GIER_GIE3_SHIFT                       (3U)
#define MU_GIER_GIE3_WIDTH                       (1U)
#define MU_GIER_GIE3(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE3_SHIFT)) & MU_GIER_GIE3_MASK)

#define MU_GIER_GIE4_MASK                        (0x10U)
#define MU_GIER_GIE4_SHIFT                       (4U)
#define MU_GIER_GIE4_WIDTH                       (1U)
#define MU_GIER_GIE4(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE4_SHIFT)) & MU_GIER_GIE4_MASK)

#define MU_GIER_GIE5_MASK                        (0x20U)
#define MU_GIER_GIE5_SHIFT                       (5U)
#define MU_GIER_GIE5_WIDTH                       (1U)
#define MU_GIER_GIE5(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE5_SHIFT)) & MU_GIER_GIE5_MASK)

#define MU_GIER_GIE6_MASK                        (0x40U)
#define MU_GIER_GIE6_SHIFT                       (6U)
#define MU_GIER_GIE6_WIDTH                       (1U)
#define MU_GIER_GIE6(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE6_SHIFT)) & MU_GIER_GIE6_MASK)

#define MU_GIER_GIE7_MASK                        (0x80U)
#define MU_GIER_GIE7_SHIFT                       (7U)
#define MU_GIER_GIE7_WIDTH                       (1U)
#define MU_GIER_GIE7(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE7_SHIFT)) & MU_GIER_GIE7_MASK)

#define MU_GIER_GIE8_MASK                        (0x100U)
#define MU_GIER_GIE8_SHIFT                       (8U)
#define MU_GIER_GIE8_WIDTH                       (1U)
#define MU_GIER_GIE8(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE8_SHIFT)) & MU_GIER_GIE8_MASK)

#define MU_GIER_GIE9_MASK                        (0x200U)
#define MU_GIER_GIE9_SHIFT                       (9U)
#define MU_GIER_GIE9_WIDTH                       (1U)
#define MU_GIER_GIE9(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE9_SHIFT)) & MU_GIER_GIE9_MASK)

#define MU_GIER_GIE10_MASK                       (0x400U)
#define MU_GIER_GIE10_SHIFT                      (10U)
#define MU_GIER_GIE10_WIDTH                      (1U)
#define MU_GIER_GIE10(x)                         (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE10_SHIFT)) & MU_GIER_GIE10_MASK)

#define MU_GIER_GIE11_MASK                       (0x800U)
#define MU_GIER_GIE11_SHIFT                      (11U)
#define MU_GIER_GIE11_WIDTH                      (1U)
#define MU_GIER_GIE11(x)                         (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE11_SHIFT)) & MU_GIER_GIE11_MASK)

#define MU_GIER_GIE12_MASK                       (0x1000U)
#define MU_GIER_GIE12_SHIFT                      (12U)
#define MU_GIER_GIE12_WIDTH                      (1U)
#define MU_GIER_GIE12(x)                         (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE12_SHIFT)) & MU_GIER_GIE12_MASK)

#define MU_GIER_GIE13_MASK                       (0x2000U)
#define MU_GIER_GIE13_SHIFT                      (13U)
#define MU_GIER_GIE13_WIDTH                      (1U)
#define MU_GIER_GIE13(x)                         (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE13_SHIFT)) & MU_GIER_GIE13_MASK)

#define MU_GIER_GIE14_MASK                       (0x4000U)
#define MU_GIER_GIE14_SHIFT                      (14U)
#define MU_GIER_GIE14_WIDTH                      (1U)
#define MU_GIER_GIE14(x)                         (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE14_SHIFT)) & MU_GIER_GIE14_MASK)

#define MU_GIER_GIE15_MASK                       (0x8000U)
#define MU_GIER_GIE15_SHIFT                      (15U)
#define MU_GIER_GIE15_WIDTH                      (1U)
#define MU_GIER_GIE15(x)                         (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE15_SHIFT)) & MU_GIER_GIE15_MASK)

#define MU_GIER_GIE16_MASK                       (0x10000U)
#define MU_GIER_GIE16_SHIFT                      (16U)
#define MU_GIER_GIE16_WIDTH                      (1U)
#define MU_GIER_GIE16(x)                         (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE16_SHIFT)) & MU_GIER_GIE16_MASK)

#define MU_GIER_GIE17_MASK                       (0x20000U)
#define MU_GIER_GIE17_SHIFT                      (17U)
#define MU_GIER_GIE17_WIDTH                      (1U)
#define MU_GIER_GIE17(x)                         (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE17_SHIFT)) & MU_GIER_GIE17_MASK)

#define MU_GIER_GIE18_MASK                       (0x40000U)
#define MU_GIER_GIE18_SHIFT                      (18U)
#define MU_GIER_GIE18_WIDTH                      (1U)
#define MU_GIER_GIE18(x)                         (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE18_SHIFT)) & MU_GIER_GIE18_MASK)

#define MU_GIER_GIE19_MASK                       (0x80000U)
#define MU_GIER_GIE19_SHIFT                      (19U)
#define MU_GIER_GIE19_WIDTH                      (1U)
#define MU_GIER_GIE19(x)                         (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE19_SHIFT)) & MU_GIER_GIE19_MASK)

#define MU_GIER_GIE20_MASK                       (0x100000U)
#define MU_GIER_GIE20_SHIFT                      (20U)
#define MU_GIER_GIE20_WIDTH                      (1U)
#define MU_GIER_GIE20(x)                         (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE20_SHIFT)) & MU_GIER_GIE20_MASK)

#define MU_GIER_GIE21_MASK                       (0x200000U)
#define MU_GIER_GIE21_SHIFT                      (21U)
#define MU_GIER_GIE21_WIDTH                      (1U)
#define MU_GIER_GIE21(x)                         (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE21_SHIFT)) & MU_GIER_GIE21_MASK)

#define MU_GIER_GIE22_MASK                       (0x400000U)
#define MU_GIER_GIE22_SHIFT                      (22U)
#define MU_GIER_GIE22_WIDTH                      (1U)
#define MU_GIER_GIE22(x)                         (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE22_SHIFT)) & MU_GIER_GIE22_MASK)

#define MU_GIER_GIE23_MASK                       (0x800000U)
#define MU_GIER_GIE23_SHIFT                      (23U)
#define MU_GIER_GIE23_WIDTH                      (1U)
#define MU_GIER_GIE23(x)                         (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE23_SHIFT)) & MU_GIER_GIE23_MASK)

#define MU_GIER_GIE24_MASK                       (0x1000000U)
#define MU_GIER_GIE24_SHIFT                      (24U)
#define MU_GIER_GIE24_WIDTH                      (1U)
#define MU_GIER_GIE24(x)                         (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE24_SHIFT)) & MU_GIER_GIE24_MASK)

#define MU_GIER_GIE25_MASK                       (0x2000000U)
#define MU_GIER_GIE25_SHIFT                      (25U)
#define MU_GIER_GIE25_WIDTH                      (1U)
#define MU_GIER_GIE25(x)                         (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE25_SHIFT)) & MU_GIER_GIE25_MASK)

#define MU_GIER_GIE26_MASK                       (0x4000000U)
#define MU_GIER_GIE26_SHIFT                      (26U)
#define MU_GIER_GIE26_WIDTH                      (1U)
#define MU_GIER_GIE26(x)                         (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE26_SHIFT)) & MU_GIER_GIE26_MASK)

#define MU_GIER_GIE27_MASK                       (0x8000000U)
#define MU_GIER_GIE27_SHIFT                      (27U)
#define MU_GIER_GIE27_WIDTH                      (1U)
#define MU_GIER_GIE27(x)                         (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE27_SHIFT)) & MU_GIER_GIE27_MASK)

#define MU_GIER_GIE28_MASK                       (0x10000000U)
#define MU_GIER_GIE28_SHIFT                      (28U)
#define MU_GIER_GIE28_WIDTH                      (1U)
#define MU_GIER_GIE28(x)                         (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE28_SHIFT)) & MU_GIER_GIE28_MASK)

#define MU_GIER_GIE29_MASK                       (0x20000000U)
#define MU_GIER_GIE29_SHIFT                      (29U)
#define MU_GIER_GIE29_WIDTH                      (1U)
#define MU_GIER_GIE29(x)                         (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE29_SHIFT)) & MU_GIER_GIE29_MASK)

#define MU_GIER_GIE30_MASK                       (0x40000000U)
#define MU_GIER_GIE30_SHIFT                      (30U)
#define MU_GIER_GIE30_WIDTH                      (1U)
#define MU_GIER_GIE30(x)                         (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE30_SHIFT)) & MU_GIER_GIE30_MASK)

#define MU_GIER_GIE31_MASK                       (0x80000000U)
#define MU_GIER_GIE31_SHIFT                      (31U)
#define MU_GIER_GIE31_WIDTH                      (1U)
#define MU_GIER_GIE31(x)                         (((uint32_t)(((uint32_t)(x)) << MU_GIER_GIE31_SHIFT)) & MU_GIER_GIE31_MASK)
/*! @} */

/*! @name GCR - General Control Register */
/*! @{ */

#define MU_GCR_GIR0_MASK                         (0x1U)
#define MU_GCR_GIR0_SHIFT                        (0U)
#define MU_GCR_GIR0_WIDTH                        (1U)
#define MU_GCR_GIR0(x)                           (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR0_SHIFT)) & MU_GCR_GIR0_MASK)

#define MU_GCR_GIR1_MASK                         (0x2U)
#define MU_GCR_GIR1_SHIFT                        (1U)
#define MU_GCR_GIR1_WIDTH                        (1U)
#define MU_GCR_GIR1(x)                           (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR1_SHIFT)) & MU_GCR_GIR1_MASK)

#define MU_GCR_GIR2_MASK                         (0x4U)
#define MU_GCR_GIR2_SHIFT                        (2U)
#define MU_GCR_GIR2_WIDTH                        (1U)
#define MU_GCR_GIR2(x)                           (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR2_SHIFT)) & MU_GCR_GIR2_MASK)

#define MU_GCR_GIR3_MASK                         (0x8U)
#define MU_GCR_GIR3_SHIFT                        (3U)
#define MU_GCR_GIR3_WIDTH                        (1U)
#define MU_GCR_GIR3(x)                           (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR3_SHIFT)) & MU_GCR_GIR3_MASK)

#define MU_GCR_GIR4_MASK                         (0x10U)
#define MU_GCR_GIR4_SHIFT                        (4U)
#define MU_GCR_GIR4_WIDTH                        (1U)
#define MU_GCR_GIR4(x)                           (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR4_SHIFT)) & MU_GCR_GIR4_MASK)

#define MU_GCR_GIR5_MASK                         (0x20U)
#define MU_GCR_GIR5_SHIFT                        (5U)
#define MU_GCR_GIR5_WIDTH                        (1U)
#define MU_GCR_GIR5(x)                           (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR5_SHIFT)) & MU_GCR_GIR5_MASK)

#define MU_GCR_GIR6_MASK                         (0x40U)
#define MU_GCR_GIR6_SHIFT                        (6U)
#define MU_GCR_GIR6_WIDTH                        (1U)
#define MU_GCR_GIR6(x)                           (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR6_SHIFT)) & MU_GCR_GIR6_MASK)

#define MU_GCR_GIR7_MASK                         (0x80U)
#define MU_GCR_GIR7_SHIFT                        (7U)
#define MU_GCR_GIR7_WIDTH                        (1U)
#define MU_GCR_GIR7(x)                           (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR7_SHIFT)) & MU_GCR_GIR7_MASK)

#define MU_GCR_GIR8_MASK                         (0x100U)
#define MU_GCR_GIR8_SHIFT                        (8U)
#define MU_GCR_GIR8_WIDTH                        (1U)
#define MU_GCR_GIR8(x)                           (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR8_SHIFT)) & MU_GCR_GIR8_MASK)

#define MU_GCR_GIR9_MASK                         (0x200U)
#define MU_GCR_GIR9_SHIFT                        (9U)
#define MU_GCR_GIR9_WIDTH                        (1U)
#define MU_GCR_GIR9(x)                           (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR9_SHIFT)) & MU_GCR_GIR9_MASK)

#define MU_GCR_GIR10_MASK                        (0x400U)
#define MU_GCR_GIR10_SHIFT                       (10U)
#define MU_GCR_GIR10_WIDTH                       (1U)
#define MU_GCR_GIR10(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR10_SHIFT)) & MU_GCR_GIR10_MASK)

#define MU_GCR_GIR11_MASK                        (0x800U)
#define MU_GCR_GIR11_SHIFT                       (11U)
#define MU_GCR_GIR11_WIDTH                       (1U)
#define MU_GCR_GIR11(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR11_SHIFT)) & MU_GCR_GIR11_MASK)

#define MU_GCR_GIR12_MASK                        (0x1000U)
#define MU_GCR_GIR12_SHIFT                       (12U)
#define MU_GCR_GIR12_WIDTH                       (1U)
#define MU_GCR_GIR12(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR12_SHIFT)) & MU_GCR_GIR12_MASK)

#define MU_GCR_GIR13_MASK                        (0x2000U)
#define MU_GCR_GIR13_SHIFT                       (13U)
#define MU_GCR_GIR13_WIDTH                       (1U)
#define MU_GCR_GIR13(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR13_SHIFT)) & MU_GCR_GIR13_MASK)

#define MU_GCR_GIR14_MASK                        (0x4000U)
#define MU_GCR_GIR14_SHIFT                       (14U)
#define MU_GCR_GIR14_WIDTH                       (1U)
#define MU_GCR_GIR14(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR14_SHIFT)) & MU_GCR_GIR14_MASK)

#define MU_GCR_GIR15_MASK                        (0x8000U)
#define MU_GCR_GIR15_SHIFT                       (15U)
#define MU_GCR_GIR15_WIDTH                       (1U)
#define MU_GCR_GIR15(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR15_SHIFT)) & MU_GCR_GIR15_MASK)

#define MU_GCR_GIR16_MASK                        (0x10000U)
#define MU_GCR_GIR16_SHIFT                       (16U)
#define MU_GCR_GIR16_WIDTH                       (1U)
#define MU_GCR_GIR16(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR16_SHIFT)) & MU_GCR_GIR16_MASK)

#define MU_GCR_GIR17_MASK                        (0x20000U)
#define MU_GCR_GIR17_SHIFT                       (17U)
#define MU_GCR_GIR17_WIDTH                       (1U)
#define MU_GCR_GIR17(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR17_SHIFT)) & MU_GCR_GIR17_MASK)

#define MU_GCR_GIR18_MASK                        (0x40000U)
#define MU_GCR_GIR18_SHIFT                       (18U)
#define MU_GCR_GIR18_WIDTH                       (1U)
#define MU_GCR_GIR18(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR18_SHIFT)) & MU_GCR_GIR18_MASK)

#define MU_GCR_GIR19_MASK                        (0x80000U)
#define MU_GCR_GIR19_SHIFT                       (19U)
#define MU_GCR_GIR19_WIDTH                       (1U)
#define MU_GCR_GIR19(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR19_SHIFT)) & MU_GCR_GIR19_MASK)

#define MU_GCR_GIR20_MASK                        (0x100000U)
#define MU_GCR_GIR20_SHIFT                       (20U)
#define MU_GCR_GIR20_WIDTH                       (1U)
#define MU_GCR_GIR20(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR20_SHIFT)) & MU_GCR_GIR20_MASK)

#define MU_GCR_GIR21_MASK                        (0x200000U)
#define MU_GCR_GIR21_SHIFT                       (21U)
#define MU_GCR_GIR21_WIDTH                       (1U)
#define MU_GCR_GIR21(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR21_SHIFT)) & MU_GCR_GIR21_MASK)

#define MU_GCR_GIR22_MASK                        (0x400000U)
#define MU_GCR_GIR22_SHIFT                       (22U)
#define MU_GCR_GIR22_WIDTH                       (1U)
#define MU_GCR_GIR22(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR22_SHIFT)) & MU_GCR_GIR22_MASK)

#define MU_GCR_GIR23_MASK                        (0x800000U)
#define MU_GCR_GIR23_SHIFT                       (23U)
#define MU_GCR_GIR23_WIDTH                       (1U)
#define MU_GCR_GIR23(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR23_SHIFT)) & MU_GCR_GIR23_MASK)

#define MU_GCR_GIR24_MASK                        (0x1000000U)
#define MU_GCR_GIR24_SHIFT                       (24U)
#define MU_GCR_GIR24_WIDTH                       (1U)
#define MU_GCR_GIR24(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR24_SHIFT)) & MU_GCR_GIR24_MASK)

#define MU_GCR_GIR25_MASK                        (0x2000000U)
#define MU_GCR_GIR25_SHIFT                       (25U)
#define MU_GCR_GIR25_WIDTH                       (1U)
#define MU_GCR_GIR25(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR25_SHIFT)) & MU_GCR_GIR25_MASK)

#define MU_GCR_GIR26_MASK                        (0x4000000U)
#define MU_GCR_GIR26_SHIFT                       (26U)
#define MU_GCR_GIR26_WIDTH                       (1U)
#define MU_GCR_GIR26(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR26_SHIFT)) & MU_GCR_GIR26_MASK)

#define MU_GCR_GIR27_MASK                        (0x8000000U)
#define MU_GCR_GIR27_SHIFT                       (27U)
#define MU_GCR_GIR27_WIDTH                       (1U)
#define MU_GCR_GIR27(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR27_SHIFT)) & MU_GCR_GIR27_MASK)

#define MU_GCR_GIR28_MASK                        (0x10000000U)
#define MU_GCR_GIR28_SHIFT                       (28U)
#define MU_GCR_GIR28_WIDTH                       (1U)
#define MU_GCR_GIR28(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR28_SHIFT)) & MU_GCR_GIR28_MASK)

#define MU_GCR_GIR29_MASK                        (0x20000000U)
#define MU_GCR_GIR29_SHIFT                       (29U)
#define MU_GCR_GIR29_WIDTH                       (1U)
#define MU_GCR_GIR29(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR29_SHIFT)) & MU_GCR_GIR29_MASK)

#define MU_GCR_GIR30_MASK                        (0x40000000U)
#define MU_GCR_GIR30_SHIFT                       (30U)
#define MU_GCR_GIR30_WIDTH                       (1U)
#define MU_GCR_GIR30(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR30_SHIFT)) & MU_GCR_GIR30_MASK)

#define MU_GCR_GIR31_MASK                        (0x80000000U)
#define MU_GCR_GIR31_SHIFT                       (31U)
#define MU_GCR_GIR31_WIDTH                       (1U)
#define MU_GCR_GIR31(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GCR_GIR31_SHIFT)) & MU_GCR_GIR31_MASK)
/*! @} */

/*! @name GSR - General Status Register */
/*! @{ */

#define MU_GSR_GIP0_MASK                         (0x1U)
#define MU_GSR_GIP0_SHIFT                        (0U)
#define MU_GSR_GIP0_WIDTH                        (1U)
#define MU_GSR_GIP0(x)                           (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP0_SHIFT)) & MU_GSR_GIP0_MASK)

#define MU_GSR_GIP1_MASK                         (0x2U)
#define MU_GSR_GIP1_SHIFT                        (1U)
#define MU_GSR_GIP1_WIDTH                        (1U)
#define MU_GSR_GIP1(x)                           (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP1_SHIFT)) & MU_GSR_GIP1_MASK)

#define MU_GSR_GIP2_MASK                         (0x4U)
#define MU_GSR_GIP2_SHIFT                        (2U)
#define MU_GSR_GIP2_WIDTH                        (1U)
#define MU_GSR_GIP2(x)                           (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP2_SHIFT)) & MU_GSR_GIP2_MASK)

#define MU_GSR_GIP3_MASK                         (0x8U)
#define MU_GSR_GIP3_SHIFT                        (3U)
#define MU_GSR_GIP3_WIDTH                        (1U)
#define MU_GSR_GIP3(x)                           (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP3_SHIFT)) & MU_GSR_GIP3_MASK)

#define MU_GSR_GIP4_MASK                         (0x10U)
#define MU_GSR_GIP4_SHIFT                        (4U)
#define MU_GSR_GIP4_WIDTH                        (1U)
#define MU_GSR_GIP4(x)                           (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP4_SHIFT)) & MU_GSR_GIP4_MASK)

#define MU_GSR_GIP5_MASK                         (0x20U)
#define MU_GSR_GIP5_SHIFT                        (5U)
#define MU_GSR_GIP5_WIDTH                        (1U)
#define MU_GSR_GIP5(x)                           (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP5_SHIFT)) & MU_GSR_GIP5_MASK)

#define MU_GSR_GIP6_MASK                         (0x40U)
#define MU_GSR_GIP6_SHIFT                        (6U)
#define MU_GSR_GIP6_WIDTH                        (1U)
#define MU_GSR_GIP6(x)                           (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP6_SHIFT)) & MU_GSR_GIP6_MASK)

#define MU_GSR_GIP7_MASK                         (0x80U)
#define MU_GSR_GIP7_SHIFT                        (7U)
#define MU_GSR_GIP7_WIDTH                        (1U)
#define MU_GSR_GIP7(x)                           (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP7_SHIFT)) & MU_GSR_GIP7_MASK)

#define MU_GSR_GIP8_MASK                         (0x100U)
#define MU_GSR_GIP8_SHIFT                        (8U)
#define MU_GSR_GIP8_WIDTH                        (1U)
#define MU_GSR_GIP8(x)                           (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP8_SHIFT)) & MU_GSR_GIP8_MASK)

#define MU_GSR_GIP9_MASK                         (0x200U)
#define MU_GSR_GIP9_SHIFT                        (9U)
#define MU_GSR_GIP9_WIDTH                        (1U)
#define MU_GSR_GIP9(x)                           (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP9_SHIFT)) & MU_GSR_GIP9_MASK)

#define MU_GSR_GIP10_MASK                        (0x400U)
#define MU_GSR_GIP10_SHIFT                       (10U)
#define MU_GSR_GIP10_WIDTH                       (1U)
#define MU_GSR_GIP10(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP10_SHIFT)) & MU_GSR_GIP10_MASK)

#define MU_GSR_GIP11_MASK                        (0x800U)
#define MU_GSR_GIP11_SHIFT                       (11U)
#define MU_GSR_GIP11_WIDTH                       (1U)
#define MU_GSR_GIP11(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP11_SHIFT)) & MU_GSR_GIP11_MASK)

#define MU_GSR_GIP12_MASK                        (0x1000U)
#define MU_GSR_GIP12_SHIFT                       (12U)
#define MU_GSR_GIP12_WIDTH                       (1U)
#define MU_GSR_GIP12(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP12_SHIFT)) & MU_GSR_GIP12_MASK)

#define MU_GSR_GIP13_MASK                        (0x2000U)
#define MU_GSR_GIP13_SHIFT                       (13U)
#define MU_GSR_GIP13_WIDTH                       (1U)
#define MU_GSR_GIP13(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP13_SHIFT)) & MU_GSR_GIP13_MASK)

#define MU_GSR_GIP14_MASK                        (0x4000U)
#define MU_GSR_GIP14_SHIFT                       (14U)
#define MU_GSR_GIP14_WIDTH                       (1U)
#define MU_GSR_GIP14(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP14_SHIFT)) & MU_GSR_GIP14_MASK)

#define MU_GSR_GIP15_MASK                        (0x8000U)
#define MU_GSR_GIP15_SHIFT                       (15U)
#define MU_GSR_GIP15_WIDTH                       (1U)
#define MU_GSR_GIP15(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP15_SHIFT)) & MU_GSR_GIP15_MASK)

#define MU_GSR_GIP16_MASK                        (0x10000U)
#define MU_GSR_GIP16_SHIFT                       (16U)
#define MU_GSR_GIP16_WIDTH                       (1U)
#define MU_GSR_GIP16(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP16_SHIFT)) & MU_GSR_GIP16_MASK)

#define MU_GSR_GIP17_MASK                        (0x20000U)
#define MU_GSR_GIP17_SHIFT                       (17U)
#define MU_GSR_GIP17_WIDTH                       (1U)
#define MU_GSR_GIP17(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP17_SHIFT)) & MU_GSR_GIP17_MASK)

#define MU_GSR_GIP18_MASK                        (0x40000U)
#define MU_GSR_GIP18_SHIFT                       (18U)
#define MU_GSR_GIP18_WIDTH                       (1U)
#define MU_GSR_GIP18(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP18_SHIFT)) & MU_GSR_GIP18_MASK)

#define MU_GSR_GIP19_MASK                        (0x80000U)
#define MU_GSR_GIP19_SHIFT                       (19U)
#define MU_GSR_GIP19_WIDTH                       (1U)
#define MU_GSR_GIP19(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP19_SHIFT)) & MU_GSR_GIP19_MASK)

#define MU_GSR_GIP20_MASK                        (0x100000U)
#define MU_GSR_GIP20_SHIFT                       (20U)
#define MU_GSR_GIP20_WIDTH                       (1U)
#define MU_GSR_GIP20(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP20_SHIFT)) & MU_GSR_GIP20_MASK)

#define MU_GSR_GIP21_MASK                        (0x200000U)
#define MU_GSR_GIP21_SHIFT                       (21U)
#define MU_GSR_GIP21_WIDTH                       (1U)
#define MU_GSR_GIP21(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP21_SHIFT)) & MU_GSR_GIP21_MASK)

#define MU_GSR_GIP22_MASK                        (0x400000U)
#define MU_GSR_GIP22_SHIFT                       (22U)
#define MU_GSR_GIP22_WIDTH                       (1U)
#define MU_GSR_GIP22(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP22_SHIFT)) & MU_GSR_GIP22_MASK)

#define MU_GSR_GIP23_MASK                        (0x800000U)
#define MU_GSR_GIP23_SHIFT                       (23U)
#define MU_GSR_GIP23_WIDTH                       (1U)
#define MU_GSR_GIP23(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP23_SHIFT)) & MU_GSR_GIP23_MASK)

#define MU_GSR_GIP24_MASK                        (0x1000000U)
#define MU_GSR_GIP24_SHIFT                       (24U)
#define MU_GSR_GIP24_WIDTH                       (1U)
#define MU_GSR_GIP24(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP24_SHIFT)) & MU_GSR_GIP24_MASK)

#define MU_GSR_GIP25_MASK                        (0x2000000U)
#define MU_GSR_GIP25_SHIFT                       (25U)
#define MU_GSR_GIP25_WIDTH                       (1U)
#define MU_GSR_GIP25(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP25_SHIFT)) & MU_GSR_GIP25_MASK)

#define MU_GSR_GIP26_MASK                        (0x4000000U)
#define MU_GSR_GIP26_SHIFT                       (26U)
#define MU_GSR_GIP26_WIDTH                       (1U)
#define MU_GSR_GIP26(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP26_SHIFT)) & MU_GSR_GIP26_MASK)

#define MU_GSR_GIP27_MASK                        (0x8000000U)
#define MU_GSR_GIP27_SHIFT                       (27U)
#define MU_GSR_GIP27_WIDTH                       (1U)
#define MU_GSR_GIP27(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP27_SHIFT)) & MU_GSR_GIP27_MASK)

#define MU_GSR_GIP28_MASK                        (0x10000000U)
#define MU_GSR_GIP28_SHIFT                       (28U)
#define MU_GSR_GIP28_WIDTH                       (1U)
#define MU_GSR_GIP28(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP28_SHIFT)) & MU_GSR_GIP28_MASK)

#define MU_GSR_GIP29_MASK                        (0x20000000U)
#define MU_GSR_GIP29_SHIFT                       (29U)
#define MU_GSR_GIP29_WIDTH                       (1U)
#define MU_GSR_GIP29(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP29_SHIFT)) & MU_GSR_GIP29_MASK)

#define MU_GSR_GIP30_MASK                        (0x40000000U)
#define MU_GSR_GIP30_SHIFT                       (30U)
#define MU_GSR_GIP30_WIDTH                       (1U)
#define MU_GSR_GIP30(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP30_SHIFT)) & MU_GSR_GIP30_MASK)

#define MU_GSR_GIP31_MASK                        (0x80000000U)
#define MU_GSR_GIP31_SHIFT                       (31U)
#define MU_GSR_GIP31_WIDTH                       (1U)
#define MU_GSR_GIP31(x)                          (((uint32_t)(((uint32_t)(x)) << MU_GSR_GIP31_SHIFT)) & MU_GSR_GIP31_MASK)
/*! @} */

/*! @name TCR - Transmit Control Register */
/*! @{ */

#define MU_TCR_TIE0_MASK                         (0x1U)
#define MU_TCR_TIE0_SHIFT                        (0U)
#define MU_TCR_TIE0_WIDTH                        (1U)
#define MU_TCR_TIE0(x)                           (((uint32_t)(((uint32_t)(x)) << MU_TCR_TIE0_SHIFT)) & MU_TCR_TIE0_MASK)

#define MU_TCR_TIE1_MASK                         (0x2U)
#define MU_TCR_TIE1_SHIFT                        (1U)
#define MU_TCR_TIE1_WIDTH                        (1U)
#define MU_TCR_TIE1(x)                           (((uint32_t)(((uint32_t)(x)) << MU_TCR_TIE1_SHIFT)) & MU_TCR_TIE1_MASK)

#define MU_TCR_TIE2_MASK                         (0x4U)
#define MU_TCR_TIE2_SHIFT                        (2U)
#define MU_TCR_TIE2_WIDTH                        (1U)
#define MU_TCR_TIE2(x)                           (((uint32_t)(((uint32_t)(x)) << MU_TCR_TIE2_SHIFT)) & MU_TCR_TIE2_MASK)

#define MU_TCR_TIE3_MASK                         (0x8U)
#define MU_TCR_TIE3_SHIFT                        (3U)
#define MU_TCR_TIE3_WIDTH                        (1U)
#define MU_TCR_TIE3(x)                           (((uint32_t)(((uint32_t)(x)) << MU_TCR_TIE3_SHIFT)) & MU_TCR_TIE3_MASK)
/*! @} */

/*! @name TSR - Transmit Status Register */
/*! @{ */

#define MU_TSR_TE0_MASK                          (0x1U)
#define MU_TSR_TE0_SHIFT                         (0U)
#define MU_TSR_TE0_WIDTH                         (1U)
#define MU_TSR_TE0(x)                            (((uint32_t)(((uint32_t)(x)) << MU_TSR_TE0_SHIFT)) & MU_TSR_TE0_MASK)

#define MU_TSR_TE1_MASK                          (0x2U)
#define MU_TSR_TE1_SHIFT                         (1U)
#define MU_TSR_TE1_WIDTH                         (1U)
#define MU_TSR_TE1(x)                            (((uint32_t)(((uint32_t)(x)) << MU_TSR_TE1_SHIFT)) & MU_TSR_TE1_MASK)

#define MU_TSR_TE2_MASK                          (0x4U)
#define MU_TSR_TE2_SHIFT                         (2U)
#define MU_TSR_TE2_WIDTH                         (1U)
#define MU_TSR_TE2(x)                            (((uint32_t)(((uint32_t)(x)) << MU_TSR_TE2_SHIFT)) & MU_TSR_TE2_MASK)

#define MU_TSR_TE3_MASK                          (0x8U)
#define MU_TSR_TE3_SHIFT                         (3U)
#define MU_TSR_TE3_WIDTH                         (1U)
#define MU_TSR_TE3(x)                            (((uint32_t)(((uint32_t)(x)) << MU_TSR_TE3_SHIFT)) & MU_TSR_TE3_MASK)
/*! @} */

/*! @name RCR - Receive Control Register */
/*! @{ */

#define MU_RCR_RIE0_MASK                         (0x1U)
#define MU_RCR_RIE0_SHIFT                        (0U)
#define MU_RCR_RIE0_WIDTH                        (1U)
#define MU_RCR_RIE0(x)                           (((uint32_t)(((uint32_t)(x)) << MU_RCR_RIE0_SHIFT)) & MU_RCR_RIE0_MASK)

#define MU_RCR_RIE1_MASK                         (0x2U)
#define MU_RCR_RIE1_SHIFT                        (1U)
#define MU_RCR_RIE1_WIDTH                        (1U)
#define MU_RCR_RIE1(x)                           (((uint32_t)(((uint32_t)(x)) << MU_RCR_RIE1_SHIFT)) & MU_RCR_RIE1_MASK)

#define MU_RCR_RIE2_MASK                         (0x4U)
#define MU_RCR_RIE2_SHIFT                        (2U)
#define MU_RCR_RIE2_WIDTH                        (1U)
#define MU_RCR_RIE2(x)                           (((uint32_t)(((uint32_t)(x)) << MU_RCR_RIE2_SHIFT)) & MU_RCR_RIE2_MASK)

#define MU_RCR_RIE3_MASK                         (0x8U)
#define MU_RCR_RIE3_SHIFT                        (3U)
#define MU_RCR_RIE3_WIDTH                        (1U)
#define MU_RCR_RIE3(x)                           (((uint32_t)(((uint32_t)(x)) << MU_RCR_RIE3_SHIFT)) & MU_RCR_RIE3_MASK)
/*! @} */

/*! @name RSR - Receive Status Register */
/*! @{ */

#define MU_RSR_RF0_MASK                          (0x1U)
#define MU_RSR_RF0_SHIFT                         (0U)
#define MU_RSR_RF0_WIDTH                         (1U)
#define MU_RSR_RF0(x)                            (((uint32_t)(((uint32_t)(x)) << MU_RSR_RF0_SHIFT)) & MU_RSR_RF0_MASK)

#define MU_RSR_RF1_MASK                          (0x2U)
#define MU_RSR_RF1_SHIFT                         (1U)
#define MU_RSR_RF1_WIDTH                         (1U)
#define MU_RSR_RF1(x)                            (((uint32_t)(((uint32_t)(x)) << MU_RSR_RF1_SHIFT)) & MU_RSR_RF1_MASK)

#define MU_RSR_RF2_MASK                          (0x4U)
#define MU_RSR_RF2_SHIFT                         (2U)
#define MU_RSR_RF2_WIDTH                         (1U)
#define MU_RSR_RF2(x)                            (((uint32_t)(((uint32_t)(x)) << MU_RSR_RF2_SHIFT)) & MU_RSR_RF2_MASK)

#define MU_RSR_RF3_MASK                          (0x8U)
#define MU_RSR_RF3_SHIFT                         (3U)
#define MU_RSR_RF3_WIDTH                         (1U)
#define MU_RSR_RF3(x)                            (((uint32_t)(((uint32_t)(x)) << MU_RSR_RF3_SHIFT)) & MU_RSR_RF3_MASK)
/*! @} */

/*! @name TR - Transmit Register */
/*! @{ */

#define MU_TR_TR_DATA_MASK                       (0xFFFFFFFFU)
#define MU_TR_TR_DATA_SHIFT                      (0U)
#define MU_TR_TR_DATA_WIDTH                      (32U)
#define MU_TR_TR_DATA(x)                         (((uint32_t)(((uint32_t)(x)) << MU_TR_TR_DATA_SHIFT)) & MU_TR_TR_DATA_MASK)
/*! @} */

/*! @name RR - Receive Register */
/*! @{ */

#define MU_RR_RR_DATA_MASK                       (0xFFFFFFFFU)
#define MU_RR_RR_DATA_SHIFT                      (0U)
#define MU_RR_RR_DATA_WIDTH                      (32U)
#define MU_RR_RR_DATA(x)                         (((uint32_t)(((uint32_t)(x)) << MU_RR_RR_DATA_SHIFT)) & MU_RR_RR_DATA_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group MU_Register_Masks */

/*!
 * @}
 */ /* end of group MU_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_MU_H_) */
