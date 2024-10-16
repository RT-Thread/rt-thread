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
 * @file S32K344_SWT.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_SWT
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
#if !defined(S32K344_SWT_H_)  /* Check if memory map has not been already included */
#define S32K344_SWT_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- SWT Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SWT_Peripheral_Access_Layer SWT Peripheral Access Layer
 * @{
 */

/** SWT - Register Layout Typedef */
typedef struct {
  __IO uint32_t CR;                                /**< Control, offset: 0x0 */
  __IO uint32_t IR;                                /**< Interrupt, offset: 0x4 */
  __IO uint32_t TO;                                /**< Timeout, offset: 0x8 */
  __IO uint32_t WN;                                /**< Window, offset: 0xC */
  __O  uint32_t SR;                                /**< Service, offset: 0x10 */
  __I  uint32_t CO;                                /**< Counter Output, offset: 0x14 */
  __IO uint32_t SK;                                /**< Service Key, offset: 0x18 */
  __IO uint32_t RRR;                               /**< Event Request, offset: 0x1C */
} SWT_Type, *SWT_MemMapPtr;

/** Number of instances of the SWT module. */
#define SWT_INSTANCE_COUNT                       (1u)

/* SWT - Peripheral instance base addresses */
/** Peripheral SWT_0 base address */
#define IP_SWT_0_BASE                            (0x40270000u)
/** Peripheral SWT_0 base pointer */
#define IP_SWT_0                                 ((SWT_Type *)IP_SWT_0_BASE)
/** Array initializer of SWT peripheral base addresses */
#define IP_SWT_BASE_ADDRS                        { IP_SWT_0_BASE }
/** Array initializer of SWT peripheral base pointers */
#define IP_SWT_BASE_PTRS                         { IP_SWT_0 }

/* ----------------------------------------------------------------------------
   -- SWT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SWT_Register_Masks SWT Register Masks
 * @{
 */

/*! @name CR - Control */
/*! @{ */

#define SWT_CR_WEN_MASK                          (0x1U)
#define SWT_CR_WEN_SHIFT                         (0U)
#define SWT_CR_WEN_WIDTH                         (1U)
#define SWT_CR_WEN(x)                            (((uint32_t)(((uint32_t)(x)) << SWT_CR_WEN_SHIFT)) & SWT_CR_WEN_MASK)

#define SWT_CR_FRZ_MASK                          (0x2U)
#define SWT_CR_FRZ_SHIFT                         (1U)
#define SWT_CR_FRZ_WIDTH                         (1U)
#define SWT_CR_FRZ(x)                            (((uint32_t)(((uint32_t)(x)) << SWT_CR_FRZ_SHIFT)) & SWT_CR_FRZ_MASK)

#define SWT_CR_STP_MASK                          (0x4U)
#define SWT_CR_STP_SHIFT                         (2U)
#define SWT_CR_STP_WIDTH                         (1U)
#define SWT_CR_STP(x)                            (((uint32_t)(((uint32_t)(x)) << SWT_CR_STP_SHIFT)) & SWT_CR_STP_MASK)

#define SWT_CR_SLK_MASK                          (0x10U)
#define SWT_CR_SLK_SHIFT                         (4U)
#define SWT_CR_SLK_WIDTH                         (1U)
#define SWT_CR_SLK(x)                            (((uint32_t)(((uint32_t)(x)) << SWT_CR_SLK_SHIFT)) & SWT_CR_SLK_MASK)

#define SWT_CR_HLK_MASK                          (0x20U)
#define SWT_CR_HLK_SHIFT                         (5U)
#define SWT_CR_HLK_WIDTH                         (1U)
#define SWT_CR_HLK(x)                            (((uint32_t)(((uint32_t)(x)) << SWT_CR_HLK_SHIFT)) & SWT_CR_HLK_MASK)

#define SWT_CR_ITR_MASK                          (0x40U)
#define SWT_CR_ITR_SHIFT                         (6U)
#define SWT_CR_ITR_WIDTH                         (1U)
#define SWT_CR_ITR(x)                            (((uint32_t)(((uint32_t)(x)) << SWT_CR_ITR_SHIFT)) & SWT_CR_ITR_MASK)

#define SWT_CR_WND_MASK                          (0x80U)
#define SWT_CR_WND_SHIFT                         (7U)
#define SWT_CR_WND_WIDTH                         (1U)
#define SWT_CR_WND(x)                            (((uint32_t)(((uint32_t)(x)) << SWT_CR_WND_SHIFT)) & SWT_CR_WND_MASK)

#define SWT_CR_RIA_MASK                          (0x100U)
#define SWT_CR_RIA_SHIFT                         (8U)
#define SWT_CR_RIA_WIDTH                         (1U)
#define SWT_CR_RIA(x)                            (((uint32_t)(((uint32_t)(x)) << SWT_CR_RIA_SHIFT)) & SWT_CR_RIA_MASK)

#define SWT_CR_SMD_MASK                          (0x600U)
#define SWT_CR_SMD_SHIFT                         (9U)
#define SWT_CR_SMD_WIDTH                         (2U)
#define SWT_CR_SMD(x)                            (((uint32_t)(((uint32_t)(x)) << SWT_CR_SMD_SHIFT)) & SWT_CR_SMD_MASK)

#define SWT_CR_MAP7_MASK                         (0x1000000U)
#define SWT_CR_MAP7_SHIFT                        (24U)
#define SWT_CR_MAP7_WIDTH                        (1U)
#define SWT_CR_MAP7(x)                           (((uint32_t)(((uint32_t)(x)) << SWT_CR_MAP7_SHIFT)) & SWT_CR_MAP7_MASK)

#define SWT_CR_MAP6_MASK                         (0x2000000U)
#define SWT_CR_MAP6_SHIFT                        (25U)
#define SWT_CR_MAP6_WIDTH                        (1U)
#define SWT_CR_MAP6(x)                           (((uint32_t)(((uint32_t)(x)) << SWT_CR_MAP6_SHIFT)) & SWT_CR_MAP6_MASK)

#define SWT_CR_MAP5_MASK                         (0x4000000U)
#define SWT_CR_MAP5_SHIFT                        (26U)
#define SWT_CR_MAP5_WIDTH                        (1U)
#define SWT_CR_MAP5(x)                           (((uint32_t)(((uint32_t)(x)) << SWT_CR_MAP5_SHIFT)) & SWT_CR_MAP5_MASK)

#define SWT_CR_MAP4_MASK                         (0x8000000U)
#define SWT_CR_MAP4_SHIFT                        (27U)
#define SWT_CR_MAP4_WIDTH                        (1U)
#define SWT_CR_MAP4(x)                           (((uint32_t)(((uint32_t)(x)) << SWT_CR_MAP4_SHIFT)) & SWT_CR_MAP4_MASK)

#define SWT_CR_MAP3_MASK                         (0x10000000U)
#define SWT_CR_MAP3_SHIFT                        (28U)
#define SWT_CR_MAP3_WIDTH                        (1U)
#define SWT_CR_MAP3(x)                           (((uint32_t)(((uint32_t)(x)) << SWT_CR_MAP3_SHIFT)) & SWT_CR_MAP3_MASK)

#define SWT_CR_MAP2_MASK                         (0x20000000U)
#define SWT_CR_MAP2_SHIFT                        (29U)
#define SWT_CR_MAP2_WIDTH                        (1U)
#define SWT_CR_MAP2(x)                           (((uint32_t)(((uint32_t)(x)) << SWT_CR_MAP2_SHIFT)) & SWT_CR_MAP2_MASK)

#define SWT_CR_MAP1_MASK                         (0x40000000U)
#define SWT_CR_MAP1_SHIFT                        (30U)
#define SWT_CR_MAP1_WIDTH                        (1U)
#define SWT_CR_MAP1(x)                           (((uint32_t)(((uint32_t)(x)) << SWT_CR_MAP1_SHIFT)) & SWT_CR_MAP1_MASK)

#define SWT_CR_MAP0_MASK                         (0x80000000U)
#define SWT_CR_MAP0_SHIFT                        (31U)
#define SWT_CR_MAP0_WIDTH                        (1U)
#define SWT_CR_MAP0(x)                           (((uint32_t)(((uint32_t)(x)) << SWT_CR_MAP0_SHIFT)) & SWT_CR_MAP0_MASK)
/*! @} */

/*! @name IR - Interrupt */
/*! @{ */

#define SWT_IR_TIF_MASK                          (0x1U)
#define SWT_IR_TIF_SHIFT                         (0U)
#define SWT_IR_TIF_WIDTH                         (1U)
#define SWT_IR_TIF(x)                            (((uint32_t)(((uint32_t)(x)) << SWT_IR_TIF_SHIFT)) & SWT_IR_TIF_MASK)
/*! @} */

/*! @name TO - Timeout */
/*! @{ */

#define SWT_TO_WTO_MASK                          (0xFFFFFFFFU)
#define SWT_TO_WTO_SHIFT                         (0U)
#define SWT_TO_WTO_WIDTH                         (32U)
#define SWT_TO_WTO(x)                            (((uint32_t)(((uint32_t)(x)) << SWT_TO_WTO_SHIFT)) & SWT_TO_WTO_MASK)
/*! @} */

/*! @name WN - Window */
/*! @{ */

#define SWT_WN_WST_MASK                          (0xFFFFFFFFU)
#define SWT_WN_WST_SHIFT                         (0U)
#define SWT_WN_WST_WIDTH                         (32U)
#define SWT_WN_WST(x)                            (((uint32_t)(((uint32_t)(x)) << SWT_WN_WST_SHIFT)) & SWT_WN_WST_MASK)
/*! @} */

/*! @name SR - Service */
/*! @{ */

#define SWT_SR_WSC_MASK                          (0xFFFFU)
#define SWT_SR_WSC_SHIFT                         (0U)
#define SWT_SR_WSC_WIDTH                         (16U)
#define SWT_SR_WSC(x)                            (((uint32_t)(((uint32_t)(x)) << SWT_SR_WSC_SHIFT)) & SWT_SR_WSC_MASK)
/*! @} */

/*! @name CO - Counter Output */
/*! @{ */

#define SWT_CO_CNT_MASK                          (0xFFFFFFFFU)
#define SWT_CO_CNT_SHIFT                         (0U)
#define SWT_CO_CNT_WIDTH                         (32U)
#define SWT_CO_CNT(x)                            (((uint32_t)(((uint32_t)(x)) << SWT_CO_CNT_SHIFT)) & SWT_CO_CNT_MASK)
/*! @} */

/*! @name SK - Service Key */
/*! @{ */

#define SWT_SK_SK_MASK                           (0xFFFFU)
#define SWT_SK_SK_SHIFT                          (0U)
#define SWT_SK_SK_WIDTH                          (16U)
#define SWT_SK_SK(x)                             (((uint32_t)(((uint32_t)(x)) << SWT_SK_SK_SHIFT)) & SWT_SK_SK_MASK)
/*! @} */

/*! @name RRR - Event Request */
/*! @{ */

#define SWT_RRR_RRF_MASK                         (0x1U)
#define SWT_RRR_RRF_SHIFT                        (0U)
#define SWT_RRR_RRF_WIDTH                        (1U)
#define SWT_RRR_RRF(x)                           (((uint32_t)(((uint32_t)(x)) << SWT_RRR_RRF_SHIFT)) & SWT_RRR_RRF_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group SWT_Register_Masks */

/*!
 * @}
 */ /* end of group SWT_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_SWT_H_) */
