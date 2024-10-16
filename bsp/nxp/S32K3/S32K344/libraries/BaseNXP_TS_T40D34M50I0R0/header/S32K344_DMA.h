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
 * @file S32K344_DMA.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_DMA
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
#if !defined(S32K344_DMA_H_)  /* Check if memory map has not been already included */
#define S32K344_DMA_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- eDMA Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup eDMA_Peripheral_Access_Layer eDMA Peripheral Access Layer
 * @{
 */

/** eDMA - Size of Registers Arrays */
#define eDMA_MP_GRPRI_COUNT                       32u

/** eDMA - Register Layout Typedef */
typedef struct {
  __IO uint32_t CSR;                               /**< Management Page Control, offset: 0x0 */
  __I  uint32_t ES;                                /**< Management Page Error Status, offset: 0x4 */
  __I  uint32_t INT;                               /**< Management Page Interrupt Request Status, offset: 0x8 */
  __I  uint32_t HRS;                               /**< Management Page Hardware Request Status, offset: 0xC */
  uint8_t RESERVED_0[240];
  __IO uint32_t CH_GRPRI[eDMA_MP_GRPRI_COUNT];     /**< Channel Arbitration Group, array offset: 0x100, array step: 0x4 */
} eDMA_Type, *eDMA_MemMapPtr;

/** Number of instances of the eDMA module. */
#define eDMA_INSTANCE_COUNT                      (1u)

/* eDMA - Peripheral instance base addresses */
/** Peripheral EDMA base address */
#define IP_EDMA_BASE                             (0x4020C000u)
/** Peripheral EDMA base pointer */
#define IP_EDMA                                  ((eDMA_Type *)IP_EDMA_BASE)
/** Array initializer of eDMA peripheral base addresses */
#define IP_eDMA_BASE_ADDRS                       { IP_EDMA_BASE }
/** Array initializer of eDMA peripheral base pointers */
#define IP_eDMA_BASE_PTRS                        { IP_EDMA }

/* ----------------------------------------------------------------------------
   -- eDMA Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup eDMA_Register_Masks eDMA Register Masks
 * @{
 */

/*! @name CSR - Management Page Control */
/*! @{ */

#define eDMA_CSR_EDBG_MASK                       (0x2U)
#define eDMA_CSR_EDBG_SHIFT                      (1U)
#define eDMA_CSR_EDBG_WIDTH                      (1U)
#define eDMA_CSR_EDBG(x)                         (((uint32_t)(((uint32_t)(x)) << eDMA_CSR_EDBG_SHIFT)) & eDMA_CSR_EDBG_MASK)

#define eDMA_CSR_ERCA_MASK                       (0x4U)
#define eDMA_CSR_ERCA_SHIFT                      (2U)
#define eDMA_CSR_ERCA_WIDTH                      (1U)
#define eDMA_CSR_ERCA(x)                         (((uint32_t)(((uint32_t)(x)) << eDMA_CSR_ERCA_SHIFT)) & eDMA_CSR_ERCA_MASK)

#define eDMA_CSR_HAE_MASK                        (0x10U)
#define eDMA_CSR_HAE_SHIFT                       (4U)
#define eDMA_CSR_HAE_WIDTH                       (1U)
#define eDMA_CSR_HAE(x)                          (((uint32_t)(((uint32_t)(x)) << eDMA_CSR_HAE_SHIFT)) & eDMA_CSR_HAE_MASK)

#define eDMA_CSR_HALT_MASK                       (0x20U)
#define eDMA_CSR_HALT_SHIFT                      (5U)
#define eDMA_CSR_HALT_WIDTH                      (1U)
#define eDMA_CSR_HALT(x)                         (((uint32_t)(((uint32_t)(x)) << eDMA_CSR_HALT_SHIFT)) & eDMA_CSR_HALT_MASK)

#define eDMA_CSR_GCLC_MASK                       (0x40U)
#define eDMA_CSR_GCLC_SHIFT                      (6U)
#define eDMA_CSR_GCLC_WIDTH                      (1U)
#define eDMA_CSR_GCLC(x)                         (((uint32_t)(((uint32_t)(x)) << eDMA_CSR_GCLC_SHIFT)) & eDMA_CSR_GCLC_MASK)

#define eDMA_CSR_GMRC_MASK                       (0x80U)
#define eDMA_CSR_GMRC_SHIFT                      (7U)
#define eDMA_CSR_GMRC_WIDTH                      (1U)
#define eDMA_CSR_GMRC(x)                         (((uint32_t)(((uint32_t)(x)) << eDMA_CSR_GMRC_SHIFT)) & eDMA_CSR_GMRC_MASK)

#define eDMA_CSR_ECX_MASK                        (0x100U)
#define eDMA_CSR_ECX_SHIFT                       (8U)
#define eDMA_CSR_ECX_WIDTH                       (1U)
#define eDMA_CSR_ECX(x)                          (((uint32_t)(((uint32_t)(x)) << eDMA_CSR_ECX_SHIFT)) & eDMA_CSR_ECX_MASK)

#define eDMA_CSR_CX_MASK                         (0x200U)
#define eDMA_CSR_CX_SHIFT                        (9U)
#define eDMA_CSR_CX_WIDTH                        (1U)
#define eDMA_CSR_CX(x)                           (((uint32_t)(((uint32_t)(x)) << eDMA_CSR_CX_SHIFT)) & eDMA_CSR_CX_MASK)

#define eDMA_CSR_ACTIVE_ID_MASK                  (0x1F000000U)
#define eDMA_CSR_ACTIVE_ID_SHIFT                 (24U)
#define eDMA_CSR_ACTIVE_ID_WIDTH                 (5U)
#define eDMA_CSR_ACTIVE_ID(x)                    (((uint32_t)(((uint32_t)(x)) << eDMA_CSR_ACTIVE_ID_SHIFT)) & eDMA_CSR_ACTIVE_ID_MASK)

#define eDMA_CSR_ACTIVE_MASK                     (0x80000000U)
#define eDMA_CSR_ACTIVE_SHIFT                    (31U)
#define eDMA_CSR_ACTIVE_WIDTH                    (1U)
#define eDMA_CSR_ACTIVE(x)                       (((uint32_t)(((uint32_t)(x)) << eDMA_CSR_ACTIVE_SHIFT)) & eDMA_CSR_ACTIVE_MASK)
/*! @} */

/*! @name ES - Management Page Error Status */
/*! @{ */

#define eDMA_ES_DBE_MASK                         (0x1U)
#define eDMA_ES_DBE_SHIFT                        (0U)
#define eDMA_ES_DBE_WIDTH                        (1U)
#define eDMA_ES_DBE(x)                           (((uint32_t)(((uint32_t)(x)) << eDMA_ES_DBE_SHIFT)) & eDMA_ES_DBE_MASK)

#define eDMA_ES_SBE_MASK                         (0x2U)
#define eDMA_ES_SBE_SHIFT                        (1U)
#define eDMA_ES_SBE_WIDTH                        (1U)
#define eDMA_ES_SBE(x)                           (((uint32_t)(((uint32_t)(x)) << eDMA_ES_SBE_SHIFT)) & eDMA_ES_SBE_MASK)

#define eDMA_ES_SGE_MASK                         (0x4U)
#define eDMA_ES_SGE_SHIFT                        (2U)
#define eDMA_ES_SGE_WIDTH                        (1U)
#define eDMA_ES_SGE(x)                           (((uint32_t)(((uint32_t)(x)) << eDMA_ES_SGE_SHIFT)) & eDMA_ES_SGE_MASK)

#define eDMA_ES_NCE_MASK                         (0x8U)
#define eDMA_ES_NCE_SHIFT                        (3U)
#define eDMA_ES_NCE_WIDTH                        (1U)
#define eDMA_ES_NCE(x)                           (((uint32_t)(((uint32_t)(x)) << eDMA_ES_NCE_SHIFT)) & eDMA_ES_NCE_MASK)

#define eDMA_ES_DOE_MASK                         (0x10U)
#define eDMA_ES_DOE_SHIFT                        (4U)
#define eDMA_ES_DOE_WIDTH                        (1U)
#define eDMA_ES_DOE(x)                           (((uint32_t)(((uint32_t)(x)) << eDMA_ES_DOE_SHIFT)) & eDMA_ES_DOE_MASK)

#define eDMA_ES_DAE_MASK                         (0x20U)
#define eDMA_ES_DAE_SHIFT                        (5U)
#define eDMA_ES_DAE_WIDTH                        (1U)
#define eDMA_ES_DAE(x)                           (((uint32_t)(((uint32_t)(x)) << eDMA_ES_DAE_SHIFT)) & eDMA_ES_DAE_MASK)

#define eDMA_ES_SOE_MASK                         (0x40U)
#define eDMA_ES_SOE_SHIFT                        (6U)
#define eDMA_ES_SOE_WIDTH                        (1U)
#define eDMA_ES_SOE(x)                           (((uint32_t)(((uint32_t)(x)) << eDMA_ES_SOE_SHIFT)) & eDMA_ES_SOE_MASK)

#define eDMA_ES_SAE_MASK                         (0x80U)
#define eDMA_ES_SAE_SHIFT                        (7U)
#define eDMA_ES_SAE_WIDTH                        (1U)
#define eDMA_ES_SAE(x)                           (((uint32_t)(((uint32_t)(x)) << eDMA_ES_SAE_SHIFT)) & eDMA_ES_SAE_MASK)

#define eDMA_ES_ECX_MASK                         (0x100U)
#define eDMA_ES_ECX_SHIFT                        (8U)
#define eDMA_ES_ECX_WIDTH                        (1U)
#define eDMA_ES_ECX(x)                           (((uint32_t)(((uint32_t)(x)) << eDMA_ES_ECX_SHIFT)) & eDMA_ES_ECX_MASK)

#define eDMA_ES_UCE_MASK                         (0x200U)
#define eDMA_ES_UCE_SHIFT                        (9U)
#define eDMA_ES_UCE_WIDTH                        (1U)
#define eDMA_ES_UCE(x)                           (((uint32_t)(((uint32_t)(x)) << eDMA_ES_UCE_SHIFT)) & eDMA_ES_UCE_MASK)

#define eDMA_ES_ERRCHN_MASK                      (0x1F000000U)
#define eDMA_ES_ERRCHN_SHIFT                     (24U)
#define eDMA_ES_ERRCHN_WIDTH                     (5U)
#define eDMA_ES_ERRCHN(x)                        (((uint32_t)(((uint32_t)(x)) << eDMA_ES_ERRCHN_SHIFT)) & eDMA_ES_ERRCHN_MASK)

#define eDMA_ES_VLD_MASK                         (0x80000000U)
#define eDMA_ES_VLD_SHIFT                        (31U)
#define eDMA_ES_VLD_WIDTH                        (1U)
#define eDMA_ES_VLD(x)                           (((uint32_t)(((uint32_t)(x)) << eDMA_ES_VLD_SHIFT)) & eDMA_ES_VLD_MASK)
/*! @} */

/*! @name INT - Management Page Interrupt Request Status */
/*! @{ */

#define eDMA_INT_INT_MASK                        (0xFFFFFFFFU)
#define eDMA_INT_INT_SHIFT                       (0U)
#define eDMA_INT_INT_WIDTH                       (32U)
#define eDMA_INT_INT(x)                          (((uint32_t)(((uint32_t)(x)) << eDMA_INT_INT_SHIFT)) & eDMA_INT_INT_MASK)
/*! @} */

/*! @name HRS - Management Page Hardware Request Status */
/*! @{ */

#define eDMA_HRS_HRS_MASK                        (0xFFFFFFFFU)
#define eDMA_HRS_HRS_SHIFT                       (0U)
#define eDMA_HRS_HRS_WIDTH                       (32U)
#define eDMA_HRS_HRS(x)                          (((uint32_t)(((uint32_t)(x)) << eDMA_HRS_HRS_SHIFT)) & eDMA_HRS_HRS_MASK)
/*! @} */

/*! @name CH_GRPRI - Channel Arbitration Group */
/*! @{ */

#define eDMA_CH_GRPRI_GRPRI_MASK                 (0x1FU)
#define eDMA_CH_GRPRI_GRPRI_SHIFT                (0U)
#define eDMA_CH_GRPRI_GRPRI_WIDTH                (5U)
#define eDMA_CH_GRPRI_GRPRI(x)                   (((uint32_t)(((uint32_t)(x)) << eDMA_CH_GRPRI_GRPRI_SHIFT)) & eDMA_CH_GRPRI_GRPRI_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group eDMA_Register_Masks */

/*!
 * @}
 */ /* end of group eDMA_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_DMA_H_) */
