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
 * @file S32K344_CMU_FC.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_CMU_FC
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
#if !defined(S32K344_CMU_FC_H_)  /* Check if memory map has not been already included */
#define S32K344_CMU_FC_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- CMU_FC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CMU_FC_Peripheral_Access_Layer CMU_FC Peripheral Access Layer
 * @{
 */

/** CMU_FC - Register Layout Typedef */
typedef struct {
  __IO uint32_t GCR;                               /**< Global Configuration Register, offset: 0x0 */
  __IO uint32_t RCCR;                              /**< Reference Count Configuration Register, offset: 0x4 */
  __IO uint32_t HTCR;                              /**< High Threshold Configuration Register, offset: 0x8 */
  __IO uint32_t LTCR;                              /**< Low Threshold Configuration Register, offset: 0xC */
  __IO uint32_t SR;                                /**< Status Register, offset: 0x10 */
  __IO uint32_t IER;                               /**< Interrupt Enable Register, offset: 0x14 */
} CMU_FC_Type, *CMU_FC_MemMapPtr;

/** Number of instances of the CMU_FC module. */
#define CMU_FC_INSTANCE_COUNT                    (4u)

/* CMU_FC - Peripheral instance base addresses */
/** Peripheral CMU_0 base address */
#define IP_CMU_0_BASE                            (0x402BC000u)
/** Peripheral CMU_0 base pointer */
#define IP_CMU_0                                 ((CMU_FC_Type *)IP_CMU_0_BASE)
/** Peripheral CMU_3 base address */
#define IP_CMU_3_BASE                            (0x402BC060u)
/** Peripheral CMU_3 base pointer */
#define IP_CMU_3                                 ((CMU_FC_Type *)IP_CMU_3_BASE)
/** Peripheral CMU_4 base address */
#define IP_CMU_4_BASE                            (0x402BC080u)
/** Peripheral CMU_4 base pointer */
#define IP_CMU_4                                 ((CMU_FC_Type *)IP_CMU_4_BASE)
/** Peripheral CMU_5 base address */
#define IP_CMU_5_BASE                            (0x402BC0A0u)
/** Peripheral CMU_5 base pointer */
#define IP_CMU_5                                 ((CMU_FC_Type *)IP_CMU_5_BASE)
/** Array initializer of CMU_FC peripheral base addresses */
#define IP_CMU_FC_BASE_ADDRS                     { IP_CMU_0_BASE, IP_CMU_3_BASE, IP_CMU_4_BASE, IP_CMU_5_BASE }
/** Array initializer of CMU_FC peripheral base pointers */
#define IP_CMU_FC_BASE_PTRS                      { IP_CMU_0, IP_CMU_3, IP_CMU_4, IP_CMU_5 }

/* ----------------------------------------------------------------------------
   -- CMU_FC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CMU_FC_Register_Masks CMU_FC Register Masks
 * @{
 */

/*! @name GCR - Global Configuration Register */
/*! @{ */

#define CMU_FC_GCR_FCE_MASK                      (0x1U)
#define CMU_FC_GCR_FCE_SHIFT                     (0U)
#define CMU_FC_GCR_FCE_WIDTH                     (1U)
#define CMU_FC_GCR_FCE(x)                        (((uint32_t)(((uint32_t)(x)) << CMU_FC_GCR_FCE_SHIFT)) & CMU_FC_GCR_FCE_MASK)
/*! @} */

/*! @name RCCR - Reference Count Configuration Register */
/*! @{ */

#define CMU_FC_RCCR_REF_CNT_MASK                 (0xFFFFU)
#define CMU_FC_RCCR_REF_CNT_SHIFT                (0U)
#define CMU_FC_RCCR_REF_CNT_WIDTH                (16U)
#define CMU_FC_RCCR_REF_CNT(x)                   (((uint32_t)(((uint32_t)(x)) << CMU_FC_RCCR_REF_CNT_SHIFT)) & CMU_FC_RCCR_REF_CNT_MASK)
/*! @} */

/*! @name HTCR - High Threshold Configuration Register */
/*! @{ */

#define CMU_FC_HTCR_HFREF_MASK                   (0xFFFFFFU)
#define CMU_FC_HTCR_HFREF_SHIFT                  (0U)
#define CMU_FC_HTCR_HFREF_WIDTH                  (24U)
#define CMU_FC_HTCR_HFREF(x)                     (((uint32_t)(((uint32_t)(x)) << CMU_FC_HTCR_HFREF_SHIFT)) & CMU_FC_HTCR_HFREF_MASK)
/*! @} */

/*! @name LTCR - Low Threshold Configuration Register */
/*! @{ */

#define CMU_FC_LTCR_LFREF_MASK                   (0xFFFFFFU)
#define CMU_FC_LTCR_LFREF_SHIFT                  (0U)
#define CMU_FC_LTCR_LFREF_WIDTH                  (24U)
#define CMU_FC_LTCR_LFREF(x)                     (((uint32_t)(((uint32_t)(x)) << CMU_FC_LTCR_LFREF_SHIFT)) & CMU_FC_LTCR_LFREF_MASK)
/*! @} */

/*! @name SR - Status Register */
/*! @{ */

#define CMU_FC_SR_FLL_MASK                       (0x1U)
#define CMU_FC_SR_FLL_SHIFT                      (0U)
#define CMU_FC_SR_FLL_WIDTH                      (1U)
#define CMU_FC_SR_FLL(x)                         (((uint32_t)(((uint32_t)(x)) << CMU_FC_SR_FLL_SHIFT)) & CMU_FC_SR_FLL_MASK)

#define CMU_FC_SR_FHH_MASK                       (0x2U)
#define CMU_FC_SR_FHH_SHIFT                      (1U)
#define CMU_FC_SR_FHH_WIDTH                      (1U)
#define CMU_FC_SR_FHH(x)                         (((uint32_t)(((uint32_t)(x)) << CMU_FC_SR_FHH_SHIFT)) & CMU_FC_SR_FHH_MASK)

#define CMU_FC_SR_RS_MASK                        (0x10U)
#define CMU_FC_SR_RS_SHIFT                       (4U)
#define CMU_FC_SR_RS_WIDTH                       (1U)
#define CMU_FC_SR_RS(x)                          (((uint32_t)(((uint32_t)(x)) << CMU_FC_SR_RS_SHIFT)) & CMU_FC_SR_RS_MASK)
/*! @} */

/*! @name IER - Interrupt Enable Register */
/*! @{ */

#define CMU_FC_IER_FLLIE_MASK                    (0x1U)
#define CMU_FC_IER_FLLIE_SHIFT                   (0U)
#define CMU_FC_IER_FLLIE_WIDTH                   (1U)
#define CMU_FC_IER_FLLIE(x)                      (((uint32_t)(((uint32_t)(x)) << CMU_FC_IER_FLLIE_SHIFT)) & CMU_FC_IER_FLLIE_MASK)

#define CMU_FC_IER_FHHIE_MASK                    (0x2U)
#define CMU_FC_IER_FHHIE_SHIFT                   (1U)
#define CMU_FC_IER_FHHIE_WIDTH                   (1U)
#define CMU_FC_IER_FHHIE(x)                      (((uint32_t)(((uint32_t)(x)) << CMU_FC_IER_FHHIE_SHIFT)) & CMU_FC_IER_FHHIE_MASK)

#define CMU_FC_IER_FLLAIE_MASK                   (0x4U)
#define CMU_FC_IER_FLLAIE_SHIFT                  (2U)
#define CMU_FC_IER_FLLAIE_WIDTH                  (1U)
#define CMU_FC_IER_FLLAIE(x)                     (((uint32_t)(((uint32_t)(x)) << CMU_FC_IER_FLLAIE_SHIFT)) & CMU_FC_IER_FLLAIE_MASK)

#define CMU_FC_IER_FHHAIE_MASK                   (0x8U)
#define CMU_FC_IER_FHHAIE_SHIFT                  (3U)
#define CMU_FC_IER_FHHAIE_WIDTH                  (1U)
#define CMU_FC_IER_FHHAIE(x)                     (((uint32_t)(((uint32_t)(x)) << CMU_FC_IER_FHHAIE_SHIFT)) & CMU_FC_IER_FHHAIE_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group CMU_FC_Register_Masks */

/*!
 * @}
 */ /* end of group CMU_FC_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_CMU_FC_H_) */
