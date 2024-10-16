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
 * @file S32K344_MSCM.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_MSCM
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
#if !defined(S32K344_MSCM_H_)  /* Check if memory map has not been already included */
#define S32K344_MSCM_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- MSCM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MSCM_Peripheral_Access_Layer MSCM Peripheral Access Layer
 * @{
 */

/** MSCM - Size of Registers Arrays */
#define MSCM_IRSPRC_COUNT                         240u

/** MSCM - Register Layout Typedef */
typedef struct {
  __I  uint32_t CPXTYPE;                           /**< Processor X Type, offset: 0x0 */
  __I  uint32_t CPXNUM;                            /**< Processor X Number, offset: 0x4 */
  __I  uint32_t CPXREV;                            /**< Processor X Revision, offset: 0x8 */
  __I  uint32_t CPXCFG0;                           /**< Processor X Configuration 0, offset: 0xC */
  __I  uint32_t CPXCFG1;                           /**< Processor X Configuration 1, offset: 0x10 */
  __I  uint32_t CPXCFG2;                           /**< Processor X Configuration 2, offset: 0x14 */
  __I  uint32_t CPXCFG3;                           /**< Processor x Configuration 3, offset: 0x18 */
  uint8_t RESERVED_0[4];
  __I  uint32_t CP0TYPE;                           /**< Processor 0 Type, offset: 0x20 */
  __I  uint32_t CP0NUM;                            /**< Processor 0 Number, offset: 0x24 */
  __I  uint32_t CP0REV;                            /**< Processor 0 Count, offset: 0x28 */
  __I  uint32_t CP0CFG0;                           /**< Processor 0 Configuration 0, offset: 0x2C */
  __I  uint32_t CP0CFG1;                           /**< Processor 0 Configuration 1, offset: 0x30 */
  __I  uint32_t CP0CFG2;                           /**< Processor 0 Configuration 2, offset: 0x34 */
  __I  uint32_t CP0CFG3;                           /**< Processor 0 Configuration 3, offset: 0x38 */
  uint8_t RESERVED_1[452];
  __IO uint32_t IRCP0ISR0;                         /**< Interrupt Router CP0 Interrupt Status, offset: 0x200 */
  __O  uint32_t IRCP0IGR0;                         /**< Interrupt Router CP0 Interrupt Generation, offset: 0x204 */
  __IO uint32_t IRCP0ISR1;                         /**< Interrupt Router CP0 Interrupt Status, offset: 0x208 */
  __O  uint32_t IRCP0IGR1;                         /**< Interrupt Router CP0 Interrupt Generation, offset: 0x20C */
  __IO uint32_t IRCP0ISR2;                         /**< Interrupt Router CP0 Interrupt Status, offset: 0x210 */
  __O  uint32_t IRCP0IGR2;                         /**< Interrupt Router CP0 Interrupt Generation, offset: 0x214 */
  __IO uint32_t IRCP0ISR3;                         /**< Interrupt Router CP0 Interrupt Status, offset: 0x218 */
  __O  uint32_t IRCP0IGR3;                         /**< Interrupt Router CP0 Interrupt Generation, offset: 0x21C */
  __IO uint32_t IRCP1ISR0;                         /**< Interrupt Router CP1 Interrupt Status, offset: 0x220 */
  __O  uint32_t IRCP1IGR0;                         /**< Interrupt Router CP1 Interrupt Generation, offset: 0x224 */
  __IO uint32_t IRCP1ISR1;                         /**< Interrupt Router CP1 Interrupt Status, offset: 0x228 */
  __O  uint32_t IRCP1IGR1;                         /**< Interrupt Router CP1 Interrupt Generation, offset: 0x22C */
  __IO uint32_t IRCP1ISR2;                         /**< Interrupt Router CP1 Interrupt Status, offset: 0x230 */
  __O  uint32_t IRCP1IGR2;                         /**< Interrupt Router CP1 Interrupt Generation, offset: 0x234 */
  __IO uint32_t IRCP1ISR3;                         /**< Interrupt Router CP1 Interrupt Status, offset: 0x238 */
  __O  uint32_t IRCP1IGR3;                         /**< Interrupt Router CP1 Interrupt Generation, offset: 0x23C */
  uint8_t RESERVED_2[448];
  __IO uint32_t IRCPCFG;                           /**< Interrupt Router Configuration, offset: 0x400 */
  uint8_t RESERVED_3[508];
  __IO uint32_t ENEDC;                             /**< Enable Interconnect Error Detection, offset: 0x600 */
  uint8_t RESERVED_4[252];
  __IO uint32_t IAHBCFGREG;                        /**< AHB Gasket Configuration, offset: 0x700 */
  uint8_t RESERVED_5[380];
  __IO uint16_t IRSPRC[MSCM_IRSPRC_COUNT];         /**< Interrupt Router Shared Peripheral Routing Control, array offset: 0x880, array step: 0x2 */
} MSCM_Type, *MSCM_MemMapPtr;

/** Number of instances of the MSCM module. */
#define MSCM_INSTANCE_COUNT                      (1u)

/* MSCM - Peripheral instance base addresses */
/** Peripheral MSCM base address */
#define IP_MSCM_BASE                             (0x40260000u)
/** Peripheral MSCM base pointer */
#define IP_MSCM                                  ((MSCM_Type *)IP_MSCM_BASE)
/** Array initializer of MSCM peripheral base addresses */
#define IP_MSCM_BASE_ADDRS                       { IP_MSCM_BASE }
/** Array initializer of MSCM peripheral base pointers */
#define IP_MSCM_BASE_PTRS                        { IP_MSCM }

/* ----------------------------------------------------------------------------
   -- MSCM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MSCM_Register_Masks MSCM Register Masks
 * @{
 */

/*! @name CPXTYPE - Processor X Type */
/*! @{ */

#define MSCM_CPXTYPE_PERSONALITY_MASK            (0xFFFFFFFFU)
#define MSCM_CPXTYPE_PERSONALITY_SHIFT           (0U)
#define MSCM_CPXTYPE_PERSONALITY_WIDTH           (32U)
#define MSCM_CPXTYPE_PERSONALITY(x)              (((uint32_t)(((uint32_t)(x)) << MSCM_CPXTYPE_PERSONALITY_SHIFT)) & MSCM_CPXTYPE_PERSONALITY_MASK)
/*! @} */

/*! @name CPXNUM - Processor X Number */
/*! @{ */

#define MSCM_CPXNUM_CPN_MASK                     (0x3U)
#define MSCM_CPXNUM_CPN_SHIFT                    (0U)
#define MSCM_CPXNUM_CPN_WIDTH                    (2U)
#define MSCM_CPXNUM_CPN(x)                       (((uint32_t)(((uint32_t)(x)) << MSCM_CPXNUM_CPN_SHIFT)) & MSCM_CPXNUM_CPN_MASK)
/*! @} */

/*! @name CPXREV - Processor X Revision */
/*! @{ */

#define MSCM_CPXREV_RYPZ_MASK                    (0xFFU)
#define MSCM_CPXREV_RYPZ_SHIFT                   (0U)
#define MSCM_CPXREV_RYPZ_WIDTH                   (8U)
#define MSCM_CPXREV_RYPZ(x)                      (((uint32_t)(((uint32_t)(x)) << MSCM_CPXREV_RYPZ_SHIFT)) & MSCM_CPXREV_RYPZ_MASK)
/*! @} */

/*! @name CPXCFG0 - Processor X Configuration 0 */
/*! @{ */

#define MSCM_CPXCFG0_DCWY_MASK                   (0xFFU)
#define MSCM_CPXCFG0_DCWY_SHIFT                  (0U)
#define MSCM_CPXCFG0_DCWY_WIDTH                  (8U)
#define MSCM_CPXCFG0_DCWY(x)                     (((uint32_t)(((uint32_t)(x)) << MSCM_CPXCFG0_DCWY_SHIFT)) & MSCM_CPXCFG0_DCWY_MASK)

#define MSCM_CPXCFG0_DCSZ_MASK                   (0xFF00U)
#define MSCM_CPXCFG0_DCSZ_SHIFT                  (8U)
#define MSCM_CPXCFG0_DCSZ_WIDTH                  (8U)
#define MSCM_CPXCFG0_DCSZ(x)                     (((uint32_t)(((uint32_t)(x)) << MSCM_CPXCFG0_DCSZ_SHIFT)) & MSCM_CPXCFG0_DCSZ_MASK)

#define MSCM_CPXCFG0_ICWY_MASK                   (0xFF0000U)
#define MSCM_CPXCFG0_ICWY_SHIFT                  (16U)
#define MSCM_CPXCFG0_ICWY_WIDTH                  (8U)
#define MSCM_CPXCFG0_ICWY(x)                     (((uint32_t)(((uint32_t)(x)) << MSCM_CPXCFG0_ICWY_SHIFT)) & MSCM_CPXCFG0_ICWY_MASK)

#define MSCM_CPXCFG0_ICSZ_MASK                   (0xFF000000U)
#define MSCM_CPXCFG0_ICSZ_SHIFT                  (24U)
#define MSCM_CPXCFG0_ICSZ_WIDTH                  (8U)
#define MSCM_CPXCFG0_ICSZ(x)                     (((uint32_t)(((uint32_t)(x)) << MSCM_CPXCFG0_ICSZ_SHIFT)) & MSCM_CPXCFG0_ICSZ_MASK)
/*! @} */

/*! @name CPXCFG1 - Processor X Configuration 1 */
/*! @{ */

#define MSCM_CPXCFG1_L2WY_MASK                   (0xFF0000U)
#define MSCM_CPXCFG1_L2WY_SHIFT                  (16U)
#define MSCM_CPXCFG1_L2WY_WIDTH                  (8U)
#define MSCM_CPXCFG1_L2WY(x)                     (((uint32_t)(((uint32_t)(x)) << MSCM_CPXCFG1_L2WY_SHIFT)) & MSCM_CPXCFG1_L2WY_MASK)

#define MSCM_CPXCFG1_L2SZ_MASK                   (0xFF000000U)
#define MSCM_CPXCFG1_L2SZ_SHIFT                  (24U)
#define MSCM_CPXCFG1_L2SZ_WIDTH                  (8U)
#define MSCM_CPXCFG1_L2SZ(x)                     (((uint32_t)(((uint32_t)(x)) << MSCM_CPXCFG1_L2SZ_SHIFT)) & MSCM_CPXCFG1_L2SZ_MASK)
/*! @} */

/*! @name CPXCFG2 - Processor X Configuration 2 */
/*! @{ */

#define MSCM_CPXCFG2_ITCMSZ_MASK                 (0xFF0000U)
#define MSCM_CPXCFG2_ITCMSZ_SHIFT                (16U)
#define MSCM_CPXCFG2_ITCMSZ_WIDTH                (8U)
#define MSCM_CPXCFG2_ITCMSZ(x)                   (((uint32_t)(((uint32_t)(x)) << MSCM_CPXCFG2_ITCMSZ_SHIFT)) & MSCM_CPXCFG2_ITCMSZ_MASK)

#define MSCM_CPXCFG2_DTCMSZ_MASK                 (0xFF000000U)
#define MSCM_CPXCFG2_DTCMSZ_SHIFT                (24U)
#define MSCM_CPXCFG2_DTCMSZ_WIDTH                (8U)
#define MSCM_CPXCFG2_DTCMSZ(x)                   (((uint32_t)(((uint32_t)(x)) << MSCM_CPXCFG2_DTCMSZ_SHIFT)) & MSCM_CPXCFG2_DTCMSZ_MASK)
/*! @} */

/*! @name CPXCFG3 - Processor x Configuration 3 */
/*! @{ */

#define MSCM_CPXCFG3_FPU_MASK                    (0x1U)
#define MSCM_CPXCFG3_FPU_SHIFT                   (0U)
#define MSCM_CPXCFG3_FPU_WIDTH                   (1U)
#define MSCM_CPXCFG3_FPU(x)                      (((uint32_t)(((uint32_t)(x)) << MSCM_CPXCFG3_FPU_SHIFT)) & MSCM_CPXCFG3_FPU_MASK)

#define MSCM_CPXCFG3_SIMD_MASK                   (0x2U)
#define MSCM_CPXCFG3_SIMD_SHIFT                  (1U)
#define MSCM_CPXCFG3_SIMD_WIDTH                  (1U)
#define MSCM_CPXCFG3_SIMD(x)                     (((uint32_t)(((uint32_t)(x)) << MSCM_CPXCFG3_SIMD_SHIFT)) & MSCM_CPXCFG3_SIMD_MASK)

#define MSCM_CPXCFG3_MMU_MASK                    (0x4U)
#define MSCM_CPXCFG3_MMU_SHIFT                   (2U)
#define MSCM_CPXCFG3_MMU_WIDTH                   (1U)
#define MSCM_CPXCFG3_MMU(x)                      (((uint32_t)(((uint32_t)(x)) << MSCM_CPXCFG3_MMU_SHIFT)) & MSCM_CPXCFG3_MMU_MASK)

#define MSCM_CPXCFG3_CMP_MASK                    (0x8U)
#define MSCM_CPXCFG3_CMP_SHIFT                   (3U)
#define MSCM_CPXCFG3_CMP_WIDTH                   (1U)
#define MSCM_CPXCFG3_CMP(x)                      (((uint32_t)(((uint32_t)(x)) << MSCM_CPXCFG3_CMP_SHIFT)) & MSCM_CPXCFG3_CMP_MASK)

#define MSCM_CPXCFG3_CPY_MASK                    (0x10U)
#define MSCM_CPXCFG3_CPY_SHIFT                   (4U)
#define MSCM_CPXCFG3_CPY_WIDTH                   (1U)
#define MSCM_CPXCFG3_CPY(x)                      (((uint32_t)(((uint32_t)(x)) << MSCM_CPXCFG3_CPY_SHIFT)) & MSCM_CPXCFG3_CPY_MASK)
/*! @} */

/*! @name CP0TYPE - Processor 0 Type */
/*! @{ */

#define MSCM_CP0TYPE_PERSONALITY_MASK            (0xFFFFFFFFU)
#define MSCM_CP0TYPE_PERSONALITY_SHIFT           (0U)
#define MSCM_CP0TYPE_PERSONALITY_WIDTH           (32U)
#define MSCM_CP0TYPE_PERSONALITY(x)              (((uint32_t)(((uint32_t)(x)) << MSCM_CP0TYPE_PERSONALITY_SHIFT)) & MSCM_CP0TYPE_PERSONALITY_MASK)
/*! @} */

/*! @name CP0NUM - Processor 0 Number */
/*! @{ */

#define MSCM_CP0NUM_CPN_MASK                     (0x3U)
#define MSCM_CP0NUM_CPN_SHIFT                    (0U)
#define MSCM_CP0NUM_CPN_WIDTH                    (2U)
#define MSCM_CP0NUM_CPN(x)                       (((uint32_t)(((uint32_t)(x)) << MSCM_CP0NUM_CPN_SHIFT)) & MSCM_CP0NUM_CPN_MASK)
/*! @} */

/*! @name CP0REV - Processor 0 Count */
/*! @{ */

#define MSCM_CP0REV_RYPZ_MASK                    (0xFFU)
#define MSCM_CP0REV_RYPZ_SHIFT                   (0U)
#define MSCM_CP0REV_RYPZ_WIDTH                   (8U)
#define MSCM_CP0REV_RYPZ(x)                      (((uint32_t)(((uint32_t)(x)) << MSCM_CP0REV_RYPZ_SHIFT)) & MSCM_CP0REV_RYPZ_MASK)
/*! @} */

/*! @name CP0CFG0 - Processor 0 Configuration 0 */
/*! @{ */

#define MSCM_CP0CFG0_DCWY_MASK                   (0xFFU)
#define MSCM_CP0CFG0_DCWY_SHIFT                  (0U)
#define MSCM_CP0CFG0_DCWY_WIDTH                  (8U)
#define MSCM_CP0CFG0_DCWY(x)                     (((uint32_t)(((uint32_t)(x)) << MSCM_CP0CFG0_DCWY_SHIFT)) & MSCM_CP0CFG0_DCWY_MASK)

#define MSCM_CP0CFG0_DCSZ_MASK                   (0xFF00U)
#define MSCM_CP0CFG0_DCSZ_SHIFT                  (8U)
#define MSCM_CP0CFG0_DCSZ_WIDTH                  (8U)
#define MSCM_CP0CFG0_DCSZ(x)                     (((uint32_t)(((uint32_t)(x)) << MSCM_CP0CFG0_DCSZ_SHIFT)) & MSCM_CP0CFG0_DCSZ_MASK)

#define MSCM_CP0CFG0_ICWY_MASK                   (0xFF0000U)
#define MSCM_CP0CFG0_ICWY_SHIFT                  (16U)
#define MSCM_CP0CFG0_ICWY_WIDTH                  (8U)
#define MSCM_CP0CFG0_ICWY(x)                     (((uint32_t)(((uint32_t)(x)) << MSCM_CP0CFG0_ICWY_SHIFT)) & MSCM_CP0CFG0_ICWY_MASK)

#define MSCM_CP0CFG0_ICSZ_MASK                   (0xFF000000U)
#define MSCM_CP0CFG0_ICSZ_SHIFT                  (24U)
#define MSCM_CP0CFG0_ICSZ_WIDTH                  (8U)
#define MSCM_CP0CFG0_ICSZ(x)                     (((uint32_t)(((uint32_t)(x)) << MSCM_CP0CFG0_ICSZ_SHIFT)) & MSCM_CP0CFG0_ICSZ_MASK)
/*! @} */

/*! @name CP0CFG1 - Processor 0 Configuration 1 */
/*! @{ */

#define MSCM_CP0CFG1_L2WY_MASK                   (0xFF0000U)
#define MSCM_CP0CFG1_L2WY_SHIFT                  (16U)
#define MSCM_CP0CFG1_L2WY_WIDTH                  (8U)
#define MSCM_CP0CFG1_L2WY(x)                     (((uint32_t)(((uint32_t)(x)) << MSCM_CP0CFG1_L2WY_SHIFT)) & MSCM_CP0CFG1_L2WY_MASK)

#define MSCM_CP0CFG1_L2SZ_MASK                   (0xFF000000U)
#define MSCM_CP0CFG1_L2SZ_SHIFT                  (24U)
#define MSCM_CP0CFG1_L2SZ_WIDTH                  (8U)
#define MSCM_CP0CFG1_L2SZ(x)                     (((uint32_t)(((uint32_t)(x)) << MSCM_CP0CFG1_L2SZ_SHIFT)) & MSCM_CP0CFG1_L2SZ_MASK)
/*! @} */

/*! @name CP0CFG2 - Processor 0 Configuration 2 */
/*! @{ */

#define MSCM_CP0CFG2_ITCMSZ_MASK                 (0xFF0000U)
#define MSCM_CP0CFG2_ITCMSZ_SHIFT                (16U)
#define MSCM_CP0CFG2_ITCMSZ_WIDTH                (8U)
#define MSCM_CP0CFG2_ITCMSZ(x)                   (((uint32_t)(((uint32_t)(x)) << MSCM_CP0CFG2_ITCMSZ_SHIFT)) & MSCM_CP0CFG2_ITCMSZ_MASK)

#define MSCM_CP0CFG2_DTCMSZ_MASK                 (0xFF000000U)
#define MSCM_CP0CFG2_DTCMSZ_SHIFT                (24U)
#define MSCM_CP0CFG2_DTCMSZ_WIDTH                (8U)
#define MSCM_CP0CFG2_DTCMSZ(x)                   (((uint32_t)(((uint32_t)(x)) << MSCM_CP0CFG2_DTCMSZ_SHIFT)) & MSCM_CP0CFG2_DTCMSZ_MASK)
/*! @} */

/*! @name CP0CFG3 - Processor 0 Configuration 3 */
/*! @{ */

#define MSCM_CP0CFG3_FPU_MASK                    (0x1U)
#define MSCM_CP0CFG3_FPU_SHIFT                   (0U)
#define MSCM_CP0CFG3_FPU_WIDTH                   (1U)
#define MSCM_CP0CFG3_FPU(x)                      (((uint32_t)(((uint32_t)(x)) << MSCM_CP0CFG3_FPU_SHIFT)) & MSCM_CP0CFG3_FPU_MASK)

#define MSCM_CP0CFG3_SIMD_MASK                   (0x2U)
#define MSCM_CP0CFG3_SIMD_SHIFT                  (1U)
#define MSCM_CP0CFG3_SIMD_WIDTH                  (1U)
#define MSCM_CP0CFG3_SIMD(x)                     (((uint32_t)(((uint32_t)(x)) << MSCM_CP0CFG3_SIMD_SHIFT)) & MSCM_CP0CFG3_SIMD_MASK)

#define MSCM_CP0CFG3_MMU_MASK                    (0x4U)
#define MSCM_CP0CFG3_MMU_SHIFT                   (2U)
#define MSCM_CP0CFG3_MMU_WIDTH                   (1U)
#define MSCM_CP0CFG3_MMU(x)                      (((uint32_t)(((uint32_t)(x)) << MSCM_CP0CFG3_MMU_SHIFT)) & MSCM_CP0CFG3_MMU_MASK)

#define MSCM_CP0CFG3_CMP_MASK                    (0x8U)
#define MSCM_CP0CFG3_CMP_SHIFT                   (3U)
#define MSCM_CP0CFG3_CMP_WIDTH                   (1U)
#define MSCM_CP0CFG3_CMP(x)                      (((uint32_t)(((uint32_t)(x)) << MSCM_CP0CFG3_CMP_SHIFT)) & MSCM_CP0CFG3_CMP_MASK)

#define MSCM_CP0CFG3_CPY_MASK                    (0x10U)
#define MSCM_CP0CFG3_CPY_SHIFT                   (4U)
#define MSCM_CP0CFG3_CPY_WIDTH                   (1U)
#define MSCM_CP0CFG3_CPY(x)                      (((uint32_t)(((uint32_t)(x)) << MSCM_CP0CFG3_CPY_SHIFT)) & MSCM_CP0CFG3_CPY_MASK)
/*! @} */

/*! @name IRCP0ISR0 - Interrupt Router CP0 Interrupt Status */
/*! @{ */

#define MSCM_IRCP0ISR0_CP0_INT_MASK              (0x1U)
#define MSCM_IRCP0ISR0_CP0_INT_SHIFT             (0U)
#define MSCM_IRCP0ISR0_CP0_INT_WIDTH             (1U)
#define MSCM_IRCP0ISR0_CP0_INT(x)                (((uint32_t)(((uint32_t)(x)) << MSCM_IRCP0ISR0_CP0_INT_SHIFT)) & MSCM_IRCP0ISR0_CP0_INT_MASK)
/*! @} */

/*! @name IRCP0IGR0 - Interrupt Router CP0 Interrupt Generation */
/*! @{ */

#define MSCM_IRCP0IGR0_INT_EN_MASK               (0x1U)
#define MSCM_IRCP0IGR0_INT_EN_SHIFT              (0U)
#define MSCM_IRCP0IGR0_INT_EN_WIDTH              (1U)
#define MSCM_IRCP0IGR0_INT_EN(x)                 (((uint32_t)(((uint32_t)(x)) << MSCM_IRCP0IGR0_INT_EN_SHIFT)) & MSCM_IRCP0IGR0_INT_EN_MASK)
/*! @} */

/*! @name IRCP0ISR1 - Interrupt Router CP0 Interrupt Status */
/*! @{ */

#define MSCM_IRCP0ISR1_CP0_INT_MASK              (0x1U)
#define MSCM_IRCP0ISR1_CP0_INT_SHIFT             (0U)
#define MSCM_IRCP0ISR1_CP0_INT_WIDTH             (1U)
#define MSCM_IRCP0ISR1_CP0_INT(x)                (((uint32_t)(((uint32_t)(x)) << MSCM_IRCP0ISR1_CP0_INT_SHIFT)) & MSCM_IRCP0ISR1_CP0_INT_MASK)
/*! @} */

/*! @name IRCP0IGR1 - Interrupt Router CP0 Interrupt Generation */
/*! @{ */

#define MSCM_IRCP0IGR1_INT_EN_MASK               (0x1U)
#define MSCM_IRCP0IGR1_INT_EN_SHIFT              (0U)
#define MSCM_IRCP0IGR1_INT_EN_WIDTH              (1U)
#define MSCM_IRCP0IGR1_INT_EN(x)                 (((uint32_t)(((uint32_t)(x)) << MSCM_IRCP0IGR1_INT_EN_SHIFT)) & MSCM_IRCP0IGR1_INT_EN_MASK)
/*! @} */

/*! @name IRCP0ISR2 - Interrupt Router CP0 Interrupt Status */
/*! @{ */

#define MSCM_IRCP0ISR2_CP0_INT_MASK              (0x1U)
#define MSCM_IRCP0ISR2_CP0_INT_SHIFT             (0U)
#define MSCM_IRCP0ISR2_CP0_INT_WIDTH             (1U)
#define MSCM_IRCP0ISR2_CP0_INT(x)                (((uint32_t)(((uint32_t)(x)) << MSCM_IRCP0ISR2_CP0_INT_SHIFT)) & MSCM_IRCP0ISR2_CP0_INT_MASK)
/*! @} */

/*! @name IRCP0IGR2 - Interrupt Router CP0 Interrupt Generation */
/*! @{ */

#define MSCM_IRCP0IGR2_INT_EN_MASK               (0x1U)
#define MSCM_IRCP0IGR2_INT_EN_SHIFT              (0U)
#define MSCM_IRCP0IGR2_INT_EN_WIDTH              (1U)
#define MSCM_IRCP0IGR2_INT_EN(x)                 (((uint32_t)(((uint32_t)(x)) << MSCM_IRCP0IGR2_INT_EN_SHIFT)) & MSCM_IRCP0IGR2_INT_EN_MASK)
/*! @} */

/*! @name IRCP0ISR3 - Interrupt Router CP0 Interrupt Status */
/*! @{ */

#define MSCM_IRCP0ISR3_CP0_INT_MASK              (0x1U)
#define MSCM_IRCP0ISR3_CP0_INT_SHIFT             (0U)
#define MSCM_IRCP0ISR3_CP0_INT_WIDTH             (1U)
#define MSCM_IRCP0ISR3_CP0_INT(x)                (((uint32_t)(((uint32_t)(x)) << MSCM_IRCP0ISR3_CP0_INT_SHIFT)) & MSCM_IRCP0ISR3_CP0_INT_MASK)
/*! @} */

/*! @name IRCP0IGR3 - Interrupt Router CP0 Interrupt Generation */
/*! @{ */

#define MSCM_IRCP0IGR3_INT_EN_MASK               (0x1U)
#define MSCM_IRCP0IGR3_INT_EN_SHIFT              (0U)
#define MSCM_IRCP0IGR3_INT_EN_WIDTH              (1U)
#define MSCM_IRCP0IGR3_INT_EN(x)                 (((uint32_t)(((uint32_t)(x)) << MSCM_IRCP0IGR3_INT_EN_SHIFT)) & MSCM_IRCP0IGR3_INT_EN_MASK)
/*! @} */

/*! @name IRCP1ISR0 - Interrupt Router CP1 Interrupt Status */
/*! @{ */

#define MSCM_IRCP1ISR0_CP0_INT_MASK              (0x1U)
#define MSCM_IRCP1ISR0_CP0_INT_SHIFT             (0U)
#define MSCM_IRCP1ISR0_CP0_INT_WIDTH             (1U)
#define MSCM_IRCP1ISR0_CP0_INT(x)                (((uint32_t)(((uint32_t)(x)) << MSCM_IRCP1ISR0_CP0_INT_SHIFT)) & MSCM_IRCP1ISR0_CP0_INT_MASK)
/*! @} */

/*! @name IRCP1IGR0 - Interrupt Router CP1 Interrupt Generation */
/*! @{ */

#define MSCM_IRCP1IGR0_INT_EN_MASK               (0x1U)
#define MSCM_IRCP1IGR0_INT_EN_SHIFT              (0U)
#define MSCM_IRCP1IGR0_INT_EN_WIDTH              (1U)
#define MSCM_IRCP1IGR0_INT_EN(x)                 (((uint32_t)(((uint32_t)(x)) << MSCM_IRCP1IGR0_INT_EN_SHIFT)) & MSCM_IRCP1IGR0_INT_EN_MASK)
/*! @} */

/*! @name IRCP1ISR1 - Interrupt Router CP1 Interrupt Status */
/*! @{ */

#define MSCM_IRCP1ISR1_CP0_INT_MASK              (0x1U)
#define MSCM_IRCP1ISR1_CP0_INT_SHIFT             (0U)
#define MSCM_IRCP1ISR1_CP0_INT_WIDTH             (1U)
#define MSCM_IRCP1ISR1_CP0_INT(x)                (((uint32_t)(((uint32_t)(x)) << MSCM_IRCP1ISR1_CP0_INT_SHIFT)) & MSCM_IRCP1ISR1_CP0_INT_MASK)
/*! @} */

/*! @name IRCP1IGR1 - Interrupt Router CP1 Interrupt Generation */
/*! @{ */

#define MSCM_IRCP1IGR1_INT_EN_MASK               (0x1U)
#define MSCM_IRCP1IGR1_INT_EN_SHIFT              (0U)
#define MSCM_IRCP1IGR1_INT_EN_WIDTH              (1U)
#define MSCM_IRCP1IGR1_INT_EN(x)                 (((uint32_t)(((uint32_t)(x)) << MSCM_IRCP1IGR1_INT_EN_SHIFT)) & MSCM_IRCP1IGR1_INT_EN_MASK)
/*! @} */

/*! @name IRCP1ISR2 - Interrupt Router CP1 Interrupt Status */
/*! @{ */

#define MSCM_IRCP1ISR2_CP0_INT_MASK              (0x1U)
#define MSCM_IRCP1ISR2_CP0_INT_SHIFT             (0U)
#define MSCM_IRCP1ISR2_CP0_INT_WIDTH             (1U)
#define MSCM_IRCP1ISR2_CP0_INT(x)                (((uint32_t)(((uint32_t)(x)) << MSCM_IRCP1ISR2_CP0_INT_SHIFT)) & MSCM_IRCP1ISR2_CP0_INT_MASK)
/*! @} */

/*! @name IRCP1IGR2 - Interrupt Router CP1 Interrupt Generation */
/*! @{ */

#define MSCM_IRCP1IGR2_INT_EN_MASK               (0x1U)
#define MSCM_IRCP1IGR2_INT_EN_SHIFT              (0U)
#define MSCM_IRCP1IGR2_INT_EN_WIDTH              (1U)
#define MSCM_IRCP1IGR2_INT_EN(x)                 (((uint32_t)(((uint32_t)(x)) << MSCM_IRCP1IGR2_INT_EN_SHIFT)) & MSCM_IRCP1IGR2_INT_EN_MASK)
/*! @} */

/*! @name IRCP1ISR3 - Interrupt Router CP1 Interrupt Status */
/*! @{ */

#define MSCM_IRCP1ISR3_CP0_INT_MASK              (0x1U)
#define MSCM_IRCP1ISR3_CP0_INT_SHIFT             (0U)
#define MSCM_IRCP1ISR3_CP0_INT_WIDTH             (1U)
#define MSCM_IRCP1ISR3_CP0_INT(x)                (((uint32_t)(((uint32_t)(x)) << MSCM_IRCP1ISR3_CP0_INT_SHIFT)) & MSCM_IRCP1ISR3_CP0_INT_MASK)
/*! @} */

/*! @name IRCP1IGR3 - Interrupt Router CP1 Interrupt Generation */
/*! @{ */

#define MSCM_IRCP1IGR3_INT_EN_MASK               (0x1U)
#define MSCM_IRCP1IGR3_INT_EN_SHIFT              (0U)
#define MSCM_IRCP1IGR3_INT_EN_WIDTH              (1U)
#define MSCM_IRCP1IGR3_INT_EN(x)                 (((uint32_t)(((uint32_t)(x)) << MSCM_IRCP1IGR3_INT_EN_SHIFT)) & MSCM_IRCP1IGR3_INT_EN_MASK)
/*! @} */

/*! @name IRCPCFG - Interrupt Router Configuration */
/*! @{ */

#define MSCM_IRCPCFG_CP0_TR_MASK                 (0x1U)
#define MSCM_IRCPCFG_CP0_TR_SHIFT                (0U)
#define MSCM_IRCPCFG_CP0_TR_WIDTH                (1U)
#define MSCM_IRCPCFG_CP0_TR(x)                   (((uint32_t)(((uint32_t)(x)) << MSCM_IRCPCFG_CP0_TR_SHIFT)) & MSCM_IRCPCFG_CP0_TR_MASK)

#define MSCM_IRCPCFG_LOCK_MASK                   (0x80000000U)
#define MSCM_IRCPCFG_LOCK_SHIFT                  (31U)
#define MSCM_IRCPCFG_LOCK_WIDTH                  (1U)
#define MSCM_IRCPCFG_LOCK(x)                     (((uint32_t)(((uint32_t)(x)) << MSCM_IRCPCFG_LOCK_SHIFT)) & MSCM_IRCPCFG_LOCK_MASK)
/*! @} */

/*! @name ENEDC - Enable Interconnect Error Detection */
/*! @{ */

#define MSCM_ENEDC_EN_RD_CM7_0_AHBM_MASK         (0x1U)
#define MSCM_ENEDC_EN_RD_CM7_0_AHBM_SHIFT        (0U)
#define MSCM_ENEDC_EN_RD_CM7_0_AHBM_WIDTH        (1U)
#define MSCM_ENEDC_EN_RD_CM7_0_AHBM(x)           (((uint32_t)(((uint32_t)(x)) << MSCM_ENEDC_EN_RD_CM7_0_AHBM_SHIFT)) & MSCM_ENEDC_EN_RD_CM7_0_AHBM_MASK)

#define MSCM_ENEDC_EN_RD_CM7_0_AHBP_MASK         (0x2U)
#define MSCM_ENEDC_EN_RD_CM7_0_AHBP_SHIFT        (1U)
#define MSCM_ENEDC_EN_RD_CM7_0_AHBP_WIDTH        (1U)
#define MSCM_ENEDC_EN_RD_CM7_0_AHBP(x)           (((uint32_t)(((uint32_t)(x)) << MSCM_ENEDC_EN_RD_CM7_0_AHBP_SHIFT)) & MSCM_ENEDC_EN_RD_CM7_0_AHBP_MASK)

#define MSCM_ENEDC_EN_RD_EDMA_MASK               (0x4U)
#define MSCM_ENEDC_EN_RD_EDMA_SHIFT              (2U)
#define MSCM_ENEDC_EN_RD_EDMA_WIDTH              (1U)
#define MSCM_ENEDC_EN_RD_EDMA(x)                 (((uint32_t)(((uint32_t)(x)) << MSCM_ENEDC_EN_RD_EDMA_SHIFT)) & MSCM_ENEDC_EN_RD_EDMA_MASK)

#define MSCM_ENEDC_EN_RD_HSE_MASK                (0x10U)
#define MSCM_ENEDC_EN_RD_HSE_SHIFT               (4U)
#define MSCM_ENEDC_EN_RD_HSE_WIDTH               (1U)
#define MSCM_ENEDC_EN_RD_HSE(x)                  (((uint32_t)(((uint32_t)(x)) << MSCM_ENEDC_EN_RD_HSE_SHIFT)) & MSCM_ENEDC_EN_RD_HSE_MASK)

#define MSCM_ENEDC_EN_RD_EMAC_MASK               (0x20U)
#define MSCM_ENEDC_EN_RD_EMAC_SHIFT              (5U)
#define MSCM_ENEDC_EN_RD_EMAC_WIDTH              (1U)
#define MSCM_ENEDC_EN_RD_EMAC(x)                 (((uint32_t)(((uint32_t)(x)) << MSCM_ENEDC_EN_RD_EMAC_SHIFT)) & MSCM_ENEDC_EN_RD_EMAC_MASK)

#define MSCM_ENEDC_EN_RD_CM7_1_AHBM_MASK         (0x40U)
#define MSCM_ENEDC_EN_RD_CM7_1_AHBM_SHIFT        (6U)
#define MSCM_ENEDC_EN_RD_CM7_1_AHBM_WIDTH        (1U)
#define MSCM_ENEDC_EN_RD_CM7_1_AHBM(x)           (((uint32_t)(((uint32_t)(x)) << MSCM_ENEDC_EN_RD_CM7_1_AHBM_SHIFT)) & MSCM_ENEDC_EN_RD_CM7_1_AHBM_MASK)

#define MSCM_ENEDC_EN_RD_CM7_1_AHBP_MASK         (0x80U)
#define MSCM_ENEDC_EN_RD_CM7_1_AHBP_SHIFT        (7U)
#define MSCM_ENEDC_EN_RD_CM7_1_AHBP_WIDTH        (1U)
#define MSCM_ENEDC_EN_RD_CM7_1_AHBP(x)           (((uint32_t)(((uint32_t)(x)) << MSCM_ENEDC_EN_RD_CM7_1_AHBP_SHIFT)) & MSCM_ENEDC_EN_RD_CM7_1_AHBP_MASK)

#define MSCM_ENEDC_EN_RD_TCM_MASK                (0x100U)
#define MSCM_ENEDC_EN_RD_TCM_SHIFT               (8U)
#define MSCM_ENEDC_EN_RD_TCM_WIDTH               (1U)
#define MSCM_ENEDC_EN_RD_TCM(x)                  (((uint32_t)(((uint32_t)(x)) << MSCM_ENEDC_EN_RD_TCM_SHIFT)) & MSCM_ENEDC_EN_RD_TCM_MASK)

#define MSCM_ENEDC_EN_ADD_PFLASH_PORT0_MASK      (0x200U)
#define MSCM_ENEDC_EN_ADD_PFLASH_PORT0_SHIFT     (9U)
#define MSCM_ENEDC_EN_ADD_PFLASH_PORT0_WIDTH     (1U)
#define MSCM_ENEDC_EN_ADD_PFLASH_PORT0(x)        (((uint32_t)(((uint32_t)(x)) << MSCM_ENEDC_EN_ADD_PFLASH_PORT0_SHIFT)) & MSCM_ENEDC_EN_ADD_PFLASH_PORT0_MASK)

#define MSCM_ENEDC_EN_ADD_PFLASH_PORT1_MASK      (0x400U)
#define MSCM_ENEDC_EN_ADD_PFLASH_PORT1_SHIFT     (10U)
#define MSCM_ENEDC_EN_ADD_PFLASH_PORT1_WIDTH     (1U)
#define MSCM_ENEDC_EN_ADD_PFLASH_PORT1(x)        (((uint32_t)(((uint32_t)(x)) << MSCM_ENEDC_EN_ADD_PFLASH_PORT1_SHIFT)) & MSCM_ENEDC_EN_ADD_PFLASH_PORT1_MASK)

#define MSCM_ENEDC_EN_ADD_PFLASH_PORT2_MASK      (0x800U)
#define MSCM_ENEDC_EN_ADD_PFLASH_PORT2_SHIFT     (11U)
#define MSCM_ENEDC_EN_ADD_PFLASH_PORT2_WIDTH     (1U)
#define MSCM_ENEDC_EN_ADD_PFLASH_PORT2(x)        (((uint32_t)(((uint32_t)(x)) << MSCM_ENEDC_EN_ADD_PFLASH_PORT2_SHIFT)) & MSCM_ENEDC_EN_ADD_PFLASH_PORT2_MASK)

#define MSCM_ENEDC_EN_WR_PRAM0_MASK              (0x1000U)
#define MSCM_ENEDC_EN_WR_PRAM0_SHIFT             (12U)
#define MSCM_ENEDC_EN_WR_PRAM0_WIDTH             (1U)
#define MSCM_ENEDC_EN_WR_PRAM0(x)                (((uint32_t)(((uint32_t)(x)) << MSCM_ENEDC_EN_WR_PRAM0_SHIFT)) & MSCM_ENEDC_EN_WR_PRAM0_MASK)

#define MSCM_ENEDC_EN_ADD_PRAM0_MASK             (0x2000U)
#define MSCM_ENEDC_EN_ADD_PRAM0_SHIFT            (13U)
#define MSCM_ENEDC_EN_ADD_PRAM0_WIDTH            (1U)
#define MSCM_ENEDC_EN_ADD_PRAM0(x)               (((uint32_t)(((uint32_t)(x)) << MSCM_ENEDC_EN_ADD_PRAM0_SHIFT)) & MSCM_ENEDC_EN_ADD_PRAM0_MASK)

#define MSCM_ENEDC_EN_WR_PRAM1_MASK              (0x4000U)
#define MSCM_ENEDC_EN_WR_PRAM1_SHIFT             (14U)
#define MSCM_ENEDC_EN_WR_PRAM1_WIDTH             (1U)
#define MSCM_ENEDC_EN_WR_PRAM1(x)                (((uint32_t)(((uint32_t)(x)) << MSCM_ENEDC_EN_WR_PRAM1_SHIFT)) & MSCM_ENEDC_EN_WR_PRAM1_MASK)

#define MSCM_ENEDC_EN_ADD_PRAM1_MASK             (0x8000U)
#define MSCM_ENEDC_EN_ADD_PRAM1_SHIFT            (15U)
#define MSCM_ENEDC_EN_ADD_PRAM1_WIDTH            (1U)
#define MSCM_ENEDC_EN_ADD_PRAM1(x)               (((uint32_t)(((uint32_t)(x)) << MSCM_ENEDC_EN_ADD_PRAM1_SHIFT)) & MSCM_ENEDC_EN_ADD_PRAM1_MASK)

#define MSCM_ENEDC_EN_WR_TCM_MASK                (0x10000U)
#define MSCM_ENEDC_EN_WR_TCM_SHIFT               (16U)
#define MSCM_ENEDC_EN_WR_TCM_WIDTH               (1U)
#define MSCM_ENEDC_EN_WR_TCM(x)                  (((uint32_t)(((uint32_t)(x)) << MSCM_ENEDC_EN_WR_TCM_SHIFT)) & MSCM_ENEDC_EN_WR_TCM_MASK)

#define MSCM_ENEDC_EN_ADD_TCM_MASK               (0x20000U)
#define MSCM_ENEDC_EN_ADD_TCM_SHIFT              (17U)
#define MSCM_ENEDC_EN_ADD_TCM_WIDTH              (1U)
#define MSCM_ENEDC_EN_ADD_TCM(x)                 (((uint32_t)(((uint32_t)(x)) << MSCM_ENEDC_EN_ADD_TCM_SHIFT)) & MSCM_ENEDC_EN_ADD_TCM_MASK)

#define MSCM_ENEDC_EN_ADD_QSPI_MASK              (0x80000U)
#define MSCM_ENEDC_EN_ADD_QSPI_SHIFT             (19U)
#define MSCM_ENEDC_EN_ADD_QSPI_WIDTH             (1U)
#define MSCM_ENEDC_EN_ADD_QSPI(x)                (((uint32_t)(((uint32_t)(x)) << MSCM_ENEDC_EN_ADD_QSPI_SHIFT)) & MSCM_ENEDC_EN_ADD_QSPI_MASK)

#define MSCM_ENEDC_EN_WR_AIPS0_MASK              (0x100000U)
#define MSCM_ENEDC_EN_WR_AIPS0_SHIFT             (20U)
#define MSCM_ENEDC_EN_WR_AIPS0_WIDTH             (1U)
#define MSCM_ENEDC_EN_WR_AIPS0(x)                (((uint32_t)(((uint32_t)(x)) << MSCM_ENEDC_EN_WR_AIPS0_SHIFT)) & MSCM_ENEDC_EN_WR_AIPS0_MASK)

#define MSCM_ENEDC_EN_ADD_AIPS0_MASK             (0x200000U)
#define MSCM_ENEDC_EN_ADD_AIPS0_SHIFT            (21U)
#define MSCM_ENEDC_EN_ADD_AIPS0_WIDTH            (1U)
#define MSCM_ENEDC_EN_ADD_AIPS0(x)               (((uint32_t)(((uint32_t)(x)) << MSCM_ENEDC_EN_ADD_AIPS0_SHIFT)) & MSCM_ENEDC_EN_ADD_AIPS0_MASK)

#define MSCM_ENEDC_EN_WR_AIPS1_MASK              (0x400000U)
#define MSCM_ENEDC_EN_WR_AIPS1_SHIFT             (22U)
#define MSCM_ENEDC_EN_WR_AIPS1_WIDTH             (1U)
#define MSCM_ENEDC_EN_WR_AIPS1(x)                (((uint32_t)(((uint32_t)(x)) << MSCM_ENEDC_EN_WR_AIPS1_SHIFT)) & MSCM_ENEDC_EN_WR_AIPS1_MASK)

#define MSCM_ENEDC_EN_ADD_AIPS1_MASK             (0x800000U)
#define MSCM_ENEDC_EN_ADD_AIPS1_SHIFT            (23U)
#define MSCM_ENEDC_EN_ADD_AIPS1_WIDTH            (1U)
#define MSCM_ENEDC_EN_ADD_AIPS1(x)               (((uint32_t)(((uint32_t)(x)) << MSCM_ENEDC_EN_ADD_AIPS1_SHIFT)) & MSCM_ENEDC_EN_ADD_AIPS1_MASK)

#define MSCM_ENEDC_EN_WR_AIPS2_MASK              (0x1000000U)
#define MSCM_ENEDC_EN_WR_AIPS2_SHIFT             (24U)
#define MSCM_ENEDC_EN_WR_AIPS2_WIDTH             (1U)
#define MSCM_ENEDC_EN_WR_AIPS2(x)                (((uint32_t)(((uint32_t)(x)) << MSCM_ENEDC_EN_WR_AIPS2_SHIFT)) & MSCM_ENEDC_EN_WR_AIPS2_MASK)

#define MSCM_ENEDC_EN_ADD_AIPS2_MASK             (0x2000000U)
#define MSCM_ENEDC_EN_ADD_AIPS2_SHIFT            (25U)
#define MSCM_ENEDC_EN_ADD_AIPS2_WIDTH            (1U)
#define MSCM_ENEDC_EN_ADD_AIPS2(x)               (((uint32_t)(((uint32_t)(x)) << MSCM_ENEDC_EN_ADD_AIPS2_SHIFT)) & MSCM_ENEDC_EN_ADD_AIPS2_MASK)

#define MSCM_ENEDC_EN_WR_CM7_0_TCM_MASK          (0x4000000U)
#define MSCM_ENEDC_EN_WR_CM7_0_TCM_SHIFT         (26U)
#define MSCM_ENEDC_EN_WR_CM7_0_TCM_WIDTH         (1U)
#define MSCM_ENEDC_EN_WR_CM7_0_TCM(x)            (((uint32_t)(((uint32_t)(x)) << MSCM_ENEDC_EN_WR_CM7_0_TCM_SHIFT)) & MSCM_ENEDC_EN_WR_CM7_0_TCM_MASK)

#define MSCM_ENEDC_EN_ADD_CM7_0_TCM_MASK         (0x8000000U)
#define MSCM_ENEDC_EN_ADD_CM7_0_TCM_SHIFT        (27U)
#define MSCM_ENEDC_EN_ADD_CM7_0_TCM_WIDTH        (1U)
#define MSCM_ENEDC_EN_ADD_CM7_0_TCM(x)           (((uint32_t)(((uint32_t)(x)) << MSCM_ENEDC_EN_ADD_CM7_0_TCM_SHIFT)) & MSCM_ENEDC_EN_ADD_CM7_0_TCM_MASK)

#define MSCM_ENEDC_EN_WR_CM7_1_TCM_MASK          (0x10000000U)
#define MSCM_ENEDC_EN_WR_CM7_1_TCM_SHIFT         (28U)
#define MSCM_ENEDC_EN_WR_CM7_1_TCM_WIDTH         (1U)
#define MSCM_ENEDC_EN_WR_CM7_1_TCM(x)            (((uint32_t)(((uint32_t)(x)) << MSCM_ENEDC_EN_WR_CM7_1_TCM_SHIFT)) & MSCM_ENEDC_EN_WR_CM7_1_TCM_MASK)

#define MSCM_ENEDC_EN_ADD_CM7_1_TCM_MASK         (0x20000000U)
#define MSCM_ENEDC_EN_ADD_CM7_1_TCM_SHIFT        (29U)
#define MSCM_ENEDC_EN_ADD_CM7_1_TCM_WIDTH        (1U)
#define MSCM_ENEDC_EN_ADD_CM7_1_TCM(x)           (((uint32_t)(((uint32_t)(x)) << MSCM_ENEDC_EN_ADD_CM7_1_TCM_SHIFT)) & MSCM_ENEDC_EN_ADD_CM7_1_TCM_MASK)
/*! @} */

/*! @name IAHBCFGREG - AHB Gasket Configuration */
/*! @{ */

#define MSCM_IAHBCFGREG_EMAC_DIS_WR_OPT_MASK     (0x1U)
#define MSCM_IAHBCFGREG_EMAC_DIS_WR_OPT_SHIFT    (0U)
#define MSCM_IAHBCFGREG_EMAC_DIS_WR_OPT_WIDTH    (1U)
#define MSCM_IAHBCFGREG_EMAC_DIS_WR_OPT(x)       (((uint32_t)(((uint32_t)(x)) << MSCM_IAHBCFGREG_EMAC_DIS_WR_OPT_SHIFT)) & MSCM_IAHBCFGREG_EMAC_DIS_WR_OPT_MASK)

#define MSCM_IAHBCFGREG_DMA_AXBS_S0_DIS_WR_OPT_MASK (0x10U)
#define MSCM_IAHBCFGREG_DMA_AXBS_S0_DIS_WR_OPT_SHIFT (4U)
#define MSCM_IAHBCFGREG_DMA_AXBS_S0_DIS_WR_OPT_WIDTH (1U)
#define MSCM_IAHBCFGREG_DMA_AXBS_S0_DIS_WR_OPT(x) (((uint32_t)(((uint32_t)(x)) << MSCM_IAHBCFGREG_DMA_AXBS_S0_DIS_WR_OPT_SHIFT)) & MSCM_IAHBCFGREG_DMA_AXBS_S0_DIS_WR_OPT_MASK)

#define MSCM_IAHBCFGREG_DMA_AXBS_S1_DIS_WR_OPT_MASK (0x100U)
#define MSCM_IAHBCFGREG_DMA_AXBS_S1_DIS_WR_OPT_SHIFT (8U)
#define MSCM_IAHBCFGREG_DMA_AXBS_S1_DIS_WR_OPT_WIDTH (1U)
#define MSCM_IAHBCFGREG_DMA_AXBS_S1_DIS_WR_OPT(x) (((uint32_t)(((uint32_t)(x)) << MSCM_IAHBCFGREG_DMA_AXBS_S1_DIS_WR_OPT_SHIFT)) & MSCM_IAHBCFGREG_DMA_AXBS_S1_DIS_WR_OPT_MASK)

#define MSCM_IAHBCFGREG_HSE_DIS_WR_OPT_MASK      (0x1000U)
#define MSCM_IAHBCFGREG_HSE_DIS_WR_OPT_SHIFT     (12U)
#define MSCM_IAHBCFGREG_HSE_DIS_WR_OPT_WIDTH     (1U)
#define MSCM_IAHBCFGREG_HSE_DIS_WR_OPT(x)        (((uint32_t)(((uint32_t)(x)) << MSCM_IAHBCFGREG_HSE_DIS_WR_OPT_SHIFT)) & MSCM_IAHBCFGREG_HSE_DIS_WR_OPT_MASK)

#define MSCM_IAHBCFGREG_TCM_DIS_WR_OPT_MASK      (0x10000U)
#define MSCM_IAHBCFGREG_TCM_DIS_WR_OPT_SHIFT     (16U)
#define MSCM_IAHBCFGREG_TCM_DIS_WR_OPT_WIDTH     (1U)
#define MSCM_IAHBCFGREG_TCM_DIS_WR_OPT(x)        (((uint32_t)(((uint32_t)(x)) << MSCM_IAHBCFGREG_TCM_DIS_WR_OPT_SHIFT)) & MSCM_IAHBCFGREG_TCM_DIS_WR_OPT_MASK)

#define MSCM_IAHBCFGREG_QSPI_DIS_WR_OPT_MASK     (0x100000U)
#define MSCM_IAHBCFGREG_QSPI_DIS_WR_OPT_SHIFT    (20U)
#define MSCM_IAHBCFGREG_QSPI_DIS_WR_OPT_WIDTH    (1U)
#define MSCM_IAHBCFGREG_QSPI_DIS_WR_OPT(x)       (((uint32_t)(((uint32_t)(x)) << MSCM_IAHBCFGREG_QSPI_DIS_WR_OPT_SHIFT)) & MSCM_IAHBCFGREG_QSPI_DIS_WR_OPT_MASK)

#define MSCM_IAHBCFGREG_AIPS1_DIS_WR_OPT_MASK    (0x1000000U)
#define MSCM_IAHBCFGREG_AIPS1_DIS_WR_OPT_SHIFT   (24U)
#define MSCM_IAHBCFGREG_AIPS1_DIS_WR_OPT_WIDTH   (1U)
#define MSCM_IAHBCFGREG_AIPS1_DIS_WR_OPT(x)      (((uint32_t)(((uint32_t)(x)) << MSCM_IAHBCFGREG_AIPS1_DIS_WR_OPT_SHIFT)) & MSCM_IAHBCFGREG_AIPS1_DIS_WR_OPT_MASK)

#define MSCM_IAHBCFGREG_AIPS2_DIS_WR_OPT_MASK    (0x10000000U)
#define MSCM_IAHBCFGREG_AIPS2_DIS_WR_OPT_SHIFT   (28U)
#define MSCM_IAHBCFGREG_AIPS2_DIS_WR_OPT_WIDTH   (1U)
#define MSCM_IAHBCFGREG_AIPS2_DIS_WR_OPT(x)      (((uint32_t)(((uint32_t)(x)) << MSCM_IAHBCFGREG_AIPS2_DIS_WR_OPT_SHIFT)) & MSCM_IAHBCFGREG_AIPS2_DIS_WR_OPT_MASK)
/*! @} */

/*! @name IRSPRC - Interrupt Router Shared Peripheral Routing Control */
/*! @{ */

#define MSCM_IRSPRC_M7_0_MASK                    (0x1U)
#define MSCM_IRSPRC_M7_0_SHIFT                   (0U)
#define MSCM_IRSPRC_M7_0_WIDTH                   (1U)
#define MSCM_IRSPRC_M7_0(x)                      (((uint16_t)(((uint16_t)(x)) << MSCM_IRSPRC_M7_0_SHIFT)) & MSCM_IRSPRC_M7_0_MASK)

#define MSCM_IRSPRC_LOCK_MASK                    (0x8000U)
#define MSCM_IRSPRC_LOCK_SHIFT                   (15U)
#define MSCM_IRSPRC_LOCK_WIDTH                   (1U)
#define MSCM_IRSPRC_LOCK(x)                      (((uint16_t)(((uint16_t)(x)) << MSCM_IRSPRC_LOCK_SHIFT)) & MSCM_IRSPRC_LOCK_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group MSCM_Register_Masks */

/*!
 * @}
 */ /* end of group MSCM_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_MSCM_H_) */
