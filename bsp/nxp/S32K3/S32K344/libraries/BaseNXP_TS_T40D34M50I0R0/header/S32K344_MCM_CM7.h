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
 * @file S32K344_MCM_CM7.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_MCM_CM7
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
#if !defined(S32K344_MCM_CM7_H_)  /* Check if memory map has not been already included */
#define S32K344_MCM_CM7_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- MCM_CM7 Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCM_CM7_Peripheral_Access_Layer MCM_CM7 Peripheral Access Layer
 * @{
 */

/** MCM_CM7 - Size of Registers Arrays */
#define MCM_CM7_LMEM_DESC__COUNT                  5u

/** MCM_CM7 - Register Layout Typedef */
typedef struct {
  __I  uint16_t PLREV;                             /**< SoC-defined Platform Revision, offset: 0x0 */
  __I  uint16_t PCT;                               /**< Processor Core Type, offset: 0x2 */
  uint8_t RESERVED_0[8];
  __IO uint32_t CPCR;                              /**< Core Platform Control, offset: 0xC */
  __IO uint32_t ISCR;                              /**< Interrupt Status and Control, offset: 0x10 */
  uint8_t RESERVED_1[1004];
  __I  uint32_t LMEM_DESC[MCM_CM7_LMEM_DESC__COUNT]; /**< Local Memory Descriptor 0..Local Memory Descriptor 4, array offset: 0x400, array step: 0x4 */
} MCM_CM7_Type, *MCM_CM7_MemMapPtr;

/** Number of instances of the MCM_CM7 module. */
#define MCM_CM7_INSTANCE_COUNT                   (1u)

/* MCM_CM7 - Peripheral instance base addresses */
/** Peripheral MCM_0_CM7 base address */
#define IP_MCM_0_CM7_BASE                        (0xE0080000u)
/** Peripheral MCM_0_CM7 base pointer */
#define IP_MCM_0_CM7                             ((MCM_CM7_Type *)IP_MCM_0_CM7_BASE)
/** Array initializer of MCM_CM7 peripheral base addresses */
#define IP_MCM_CM7_BASE_ADDRS                    { IP_MCM_0_CM7_BASE }
/** Array initializer of MCM_CM7 peripheral base pointers */
#define IP_MCM_CM7_BASE_PTRS                     { IP_MCM_0_CM7 }

/* ----------------------------------------------------------------------------
   -- MCM_CM7 Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MCM_CM7_Register_Masks MCM_CM7 Register Masks
 * @{
 */

/*! @name PLREV - SoC-defined Platform Revision */
/*! @{ */

#define MCM_CM7_PLREV_PLREV_MASK                 (0xFFFFU)
#define MCM_CM7_PLREV_PLREV_SHIFT                (0U)
#define MCM_CM7_PLREV_PLREV_WIDTH                (16U)
#define MCM_CM7_PLREV_PLREV(x)                   (((uint16_t)(((uint16_t)(x)) << MCM_CM7_PLREV_PLREV_SHIFT)) & MCM_CM7_PLREV_PLREV_MASK)
/*! @} */

/*! @name PCT - Processor Core Type */
/*! @{ */

#define MCM_CM7_PCT_PCT_MASK                     (0xFFFFU)
#define MCM_CM7_PCT_PCT_SHIFT                    (0U)
#define MCM_CM7_PCT_PCT_WIDTH                    (16U)
#define MCM_CM7_PCT_PCT(x)                       (((uint16_t)(((uint16_t)(x)) << MCM_CM7_PCT_PCT_SHIFT)) & MCM_CM7_PCT_PCT_MASK)
/*! @} */

/*! @name CPCR - Core Platform Control */
/*! @{ */

#define MCM_CM7_CPCR_CM7_AHBSPRI_MASK            (0x8000000U)
#define MCM_CM7_CPCR_CM7_AHBSPRI_SHIFT           (27U)
#define MCM_CM7_CPCR_CM7_AHBSPRI_WIDTH           (1U)
#define MCM_CM7_CPCR_CM7_AHBSPRI(x)              (((uint32_t)(((uint32_t)(x)) << MCM_CM7_CPCR_CM7_AHBSPRI_SHIFT)) & MCM_CM7_CPCR_CM7_AHBSPRI_MASK)
/*! @} */

/*! @name ISCR - Interrupt Status and Control */
/*! @{ */

#define MCM_CM7_ISCR_WABS_MASK                   (0x20U)
#define MCM_CM7_ISCR_WABS_SHIFT                  (5U)
#define MCM_CM7_ISCR_WABS_WIDTH                  (1U)
#define MCM_CM7_ISCR_WABS(x)                     (((uint32_t)(((uint32_t)(x)) << MCM_CM7_ISCR_WABS_SHIFT)) & MCM_CM7_ISCR_WABS_MASK)

#define MCM_CM7_ISCR_WABSO_MASK                  (0x40U)
#define MCM_CM7_ISCR_WABSO_SHIFT                 (6U)
#define MCM_CM7_ISCR_WABSO_WIDTH                 (1U)
#define MCM_CM7_ISCR_WABSO(x)                    (((uint32_t)(((uint32_t)(x)) << MCM_CM7_ISCR_WABSO_SHIFT)) & MCM_CM7_ISCR_WABSO_MASK)

#define MCM_CM7_ISCR_FIOC_MASK                   (0x100U)
#define MCM_CM7_ISCR_FIOC_SHIFT                  (8U)
#define MCM_CM7_ISCR_FIOC_WIDTH                  (1U)
#define MCM_CM7_ISCR_FIOC(x)                     (((uint32_t)(((uint32_t)(x)) << MCM_CM7_ISCR_FIOC_SHIFT)) & MCM_CM7_ISCR_FIOC_MASK)

#define MCM_CM7_ISCR_FDZC_MASK                   (0x200U)
#define MCM_CM7_ISCR_FDZC_SHIFT                  (9U)
#define MCM_CM7_ISCR_FDZC_WIDTH                  (1U)
#define MCM_CM7_ISCR_FDZC(x)                     (((uint32_t)(((uint32_t)(x)) << MCM_CM7_ISCR_FDZC_SHIFT)) & MCM_CM7_ISCR_FDZC_MASK)

#define MCM_CM7_ISCR_FOFC_MASK                   (0x400U)
#define MCM_CM7_ISCR_FOFC_SHIFT                  (10U)
#define MCM_CM7_ISCR_FOFC_WIDTH                  (1U)
#define MCM_CM7_ISCR_FOFC(x)                     (((uint32_t)(((uint32_t)(x)) << MCM_CM7_ISCR_FOFC_SHIFT)) & MCM_CM7_ISCR_FOFC_MASK)

#define MCM_CM7_ISCR_FUFC_MASK                   (0x800U)
#define MCM_CM7_ISCR_FUFC_SHIFT                  (11U)
#define MCM_CM7_ISCR_FUFC_WIDTH                  (1U)
#define MCM_CM7_ISCR_FUFC(x)                     (((uint32_t)(((uint32_t)(x)) << MCM_CM7_ISCR_FUFC_SHIFT)) & MCM_CM7_ISCR_FUFC_MASK)

#define MCM_CM7_ISCR_FIXC_MASK                   (0x1000U)
#define MCM_CM7_ISCR_FIXC_SHIFT                  (12U)
#define MCM_CM7_ISCR_FIXC_WIDTH                  (1U)
#define MCM_CM7_ISCR_FIXC(x)                     (((uint32_t)(((uint32_t)(x)) << MCM_CM7_ISCR_FIXC_SHIFT)) & MCM_CM7_ISCR_FIXC_MASK)

#define MCM_CM7_ISCR_FIDC_MASK                   (0x8000U)
#define MCM_CM7_ISCR_FIDC_SHIFT                  (15U)
#define MCM_CM7_ISCR_FIDC_WIDTH                  (1U)
#define MCM_CM7_ISCR_FIDC(x)                     (((uint32_t)(((uint32_t)(x)) << MCM_CM7_ISCR_FIDC_SHIFT)) & MCM_CM7_ISCR_FIDC_MASK)

#define MCM_CM7_ISCR_WABE_MASK                   (0x200000U)
#define MCM_CM7_ISCR_WABE_SHIFT                  (21U)
#define MCM_CM7_ISCR_WABE_WIDTH                  (1U)
#define MCM_CM7_ISCR_WABE(x)                     (((uint32_t)(((uint32_t)(x)) << MCM_CM7_ISCR_WABE_SHIFT)) & MCM_CM7_ISCR_WABE_MASK)

#define MCM_CM7_ISCR_FIOCE_MASK                  (0x1000000U)
#define MCM_CM7_ISCR_FIOCE_SHIFT                 (24U)
#define MCM_CM7_ISCR_FIOCE_WIDTH                 (1U)
#define MCM_CM7_ISCR_FIOCE(x)                    (((uint32_t)(((uint32_t)(x)) << MCM_CM7_ISCR_FIOCE_SHIFT)) & MCM_CM7_ISCR_FIOCE_MASK)

#define MCM_CM7_ISCR_FDZCE_MASK                  (0x2000000U)
#define MCM_CM7_ISCR_FDZCE_SHIFT                 (25U)
#define MCM_CM7_ISCR_FDZCE_WIDTH                 (1U)
#define MCM_CM7_ISCR_FDZCE(x)                    (((uint32_t)(((uint32_t)(x)) << MCM_CM7_ISCR_FDZCE_SHIFT)) & MCM_CM7_ISCR_FDZCE_MASK)

#define MCM_CM7_ISCR_FOFCE_MASK                  (0x4000000U)
#define MCM_CM7_ISCR_FOFCE_SHIFT                 (26U)
#define MCM_CM7_ISCR_FOFCE_WIDTH                 (1U)
#define MCM_CM7_ISCR_FOFCE(x)                    (((uint32_t)(((uint32_t)(x)) << MCM_CM7_ISCR_FOFCE_SHIFT)) & MCM_CM7_ISCR_FOFCE_MASK)

#define MCM_CM7_ISCR_FUFCE_MASK                  (0x8000000U)
#define MCM_CM7_ISCR_FUFCE_SHIFT                 (27U)
#define MCM_CM7_ISCR_FUFCE_WIDTH                 (1U)
#define MCM_CM7_ISCR_FUFCE(x)                    (((uint32_t)(((uint32_t)(x)) << MCM_CM7_ISCR_FUFCE_SHIFT)) & MCM_CM7_ISCR_FUFCE_MASK)

#define MCM_CM7_ISCR_FIXCE_MASK                  (0x10000000U)
#define MCM_CM7_ISCR_FIXCE_SHIFT                 (28U)
#define MCM_CM7_ISCR_FIXCE_WIDTH                 (1U)
#define MCM_CM7_ISCR_FIXCE(x)                    (((uint32_t)(((uint32_t)(x)) << MCM_CM7_ISCR_FIXCE_SHIFT)) & MCM_CM7_ISCR_FIXCE_MASK)

#define MCM_CM7_ISCR_FIDCE_MASK                  (0x80000000U)
#define MCM_CM7_ISCR_FIDCE_SHIFT                 (31U)
#define MCM_CM7_ISCR_FIDCE_WIDTH                 (1U)
#define MCM_CM7_ISCR_FIDCE(x)                    (((uint32_t)(((uint32_t)(x)) << MCM_CM7_ISCR_FIDCE_SHIFT)) & MCM_CM7_ISCR_FIDCE_MASK)
/*! @} */

/*! @name LMEM_DESC - Local Memory Descriptor 0..Local Memory Descriptor 4 */
/*! @{ */

#define MCM_CM7_LMEM_DESC_MT_MASK                (0xE000U)
#define MCM_CM7_LMEM_DESC_MT_SHIFT               (13U)
#define MCM_CM7_LMEM_DESC_MT_WIDTH               (3U)
#define MCM_CM7_LMEM_DESC_MT(x)                  (((uint32_t)(((uint32_t)(x)) << MCM_CM7_LMEM_DESC_MT_SHIFT)) & MCM_CM7_LMEM_DESC_MT_MASK)

#define MCM_CM7_LMEM_DESC_DPW_MASK               (0xE0000U)
#define MCM_CM7_LMEM_DESC_DPW_SHIFT              (17U)
#define MCM_CM7_LMEM_DESC_DPW_WIDTH              (3U)
#define MCM_CM7_LMEM_DESC_DPW(x)                 (((uint32_t)(((uint32_t)(x)) << MCM_CM7_LMEM_DESC_DPW_SHIFT)) & MCM_CM7_LMEM_DESC_DPW_MASK)

#define MCM_CM7_LMEM_DESC_WY_MASK                (0xF00000U)
#define MCM_CM7_LMEM_DESC_WY_SHIFT               (20U)
#define MCM_CM7_LMEM_DESC_WY_WIDTH               (4U)
#define MCM_CM7_LMEM_DESC_WY(x)                  (((uint32_t)(((uint32_t)(x)) << MCM_CM7_LMEM_DESC_WY_SHIFT)) & MCM_CM7_LMEM_DESC_WY_MASK)

#define MCM_CM7_LMEM_DESC_LMSZ_MASK              (0xF000000U)
#define MCM_CM7_LMEM_DESC_LMSZ_SHIFT             (24U)
#define MCM_CM7_LMEM_DESC_LMSZ_WIDTH             (4U)
#define MCM_CM7_LMEM_DESC_LMSZ(x)                (((uint32_t)(((uint32_t)(x)) << MCM_CM7_LMEM_DESC_LMSZ_SHIFT)) & MCM_CM7_LMEM_DESC_LMSZ_MASK)

#define MCM_CM7_LMEM_DESC_LMSZH_MASK             (0x10000000U)
#define MCM_CM7_LMEM_DESC_LMSZH_SHIFT            (28U)
#define MCM_CM7_LMEM_DESC_LMSZH_WIDTH            (1U)
#define MCM_CM7_LMEM_DESC_LMSZH(x)               (((uint32_t)(((uint32_t)(x)) << MCM_CM7_LMEM_DESC_LMSZH_SHIFT)) & MCM_CM7_LMEM_DESC_LMSZH_MASK)

#define MCM_CM7_LMEM_DESC_LMV_MASK               (0x80000000U)
#define MCM_CM7_LMEM_DESC_LMV_SHIFT              (31U)
#define MCM_CM7_LMEM_DESC_LMV_WIDTH              (1U)
#define MCM_CM7_LMEM_DESC_LMV(x)                 (((uint32_t)(((uint32_t)(x)) << MCM_CM7_LMEM_DESC_LMV_SHIFT)) & MCM_CM7_LMEM_DESC_LMV_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group MCM_CM7_Register_Masks */

/*!
 * @}
 */ /* end of group MCM_CM7_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_MCM_CM7_H_) */
