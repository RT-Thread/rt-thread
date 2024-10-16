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
 * @file S32K344_MDM_AP.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_MDM_AP
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
#if !defined(S32K344_MDM_AP_H_)  /* Check if memory map has not been already included */
#define S32K344_MDM_AP_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- MDM_AP Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MDM_AP_Peripheral_Access_Layer MDM_AP Peripheral Access Layer
 * @{
 */

/** MDM_AP - Register Layout Typedef */
typedef struct {
  __I  uint32_t MDMAPSTTS;                         /**< Status, offset: 0x0 */
  __IO uint32_t MDMAPCTL;                          /**< Control, offset: 0x4 */
  uint8_t RESERVED_0[40];
  __IO uint32_t MDMAPWIREN;                        /**< WIR Enable, offset: 0x30 */
  __I  uint32_t MDMAPWIRSTTS;                      /**< WIR Status, offset: 0x34 */
  __IO uint32_t MDMAPWIRREL;                       /**< WIR Release, offset: 0x38 */
  uint8_t RESERVED_1[192];
  __I  uint32_t ID;                                /**< Identity, offset: 0xFC */
} MDM_AP_Type, *MDM_AP_MemMapPtr;

/** Number of instances of the MDM_AP module. */
#define MDM_AP_INSTANCE_COUNT                    (1u)

/* MDM_AP - Peripheral instance base addresses */
/** Peripheral MDM_AP base address */
#define IP_MDM_AP_BASE                           (0x40250600u)
/** Peripheral MDM_AP base pointer */
#define IP_MDM_AP                                ((MDM_AP_Type *)IP_MDM_AP_BASE)
/** Array initializer of MDM_AP peripheral base addresses */
#define IP_MDM_AP_BASE_ADDRS                     { IP_MDM_AP_BASE }
/** Array initializer of MDM_AP peripheral base pointers */
#define IP_MDM_AP_BASE_PTRS                      { IP_MDM_AP }

/* ----------------------------------------------------------------------------
   -- MDM_AP Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MDM_AP_Register_Masks MDM_AP Register Masks
 * @{
 */

/*! @name MDMAPSTTS - Status */
/*! @{ */

#define MDM_AP_MDMAPSTTS_DESTRST_MASK            (0x2U)
#define MDM_AP_MDMAPSTTS_DESTRST_SHIFT           (1U)
#define MDM_AP_MDMAPSTTS_DESTRST_WIDTH           (1U)
#define MDM_AP_MDMAPSTTS_DESTRST(x)              (((uint32_t)(((uint32_t)(x)) << MDM_AP_MDMAPSTTS_DESTRST_SHIFT)) & MDM_AP_MDMAPSTTS_DESTRST_MASK)

#define MDM_AP_MDMAPSTTS_FUNCRST_MASK            (0x4U)
#define MDM_AP_MDMAPSTTS_FUNCRST_SHIFT           (2U)
#define MDM_AP_MDMAPSTTS_FUNCRST_WIDTH           (1U)
#define MDM_AP_MDMAPSTTS_FUNCRST(x)              (((uint32_t)(((uint32_t)(x)) << MDM_AP_MDMAPSTTS_FUNCRST_SHIFT)) & MDM_AP_MDMAPSTTS_FUNCRST_MASK)

#define MDM_AP_MDMAPSTTS_CM70HLT_MASK            (0x1000U)
#define MDM_AP_MDMAPSTTS_CM70HLT_SHIFT           (12U)
#define MDM_AP_MDMAPSTTS_CM70HLT_WIDTH           (1U)
#define MDM_AP_MDMAPSTTS_CM70HLT(x)              (((uint32_t)(((uint32_t)(x)) << MDM_AP_MDMAPSTTS_CM70HLT_SHIFT)) & MDM_AP_MDMAPSTTS_CM70HLT_MASK)

#define MDM_AP_MDMAPSTTS_CM70DPSLP_MASK          (0x10000U)
#define MDM_AP_MDMAPSTTS_CM70DPSLP_SHIFT         (16U)
#define MDM_AP_MDMAPSTTS_CM70DPSLP_WIDTH         (1U)
#define MDM_AP_MDMAPSTTS_CM70DPSLP(x)            (((uint32_t)(((uint32_t)(x)) << MDM_AP_MDMAPSTTS_CM70DPSLP_SHIFT)) & MDM_AP_MDMAPSTTS_CM70DPSLP_MASK)

#define MDM_AP_MDMAPSTTS_CM70SLPNG_MASK          (0x100000U)
#define MDM_AP_MDMAPSTTS_CM70SLPNG_SHIFT         (20U)
#define MDM_AP_MDMAPSTTS_CM70SLPNG_WIDTH         (1U)
#define MDM_AP_MDMAPSTTS_CM70SLPNG(x)            (((uint32_t)(((uint32_t)(x)) << MDM_AP_MDMAPSTTS_CM70SLPNG_SHIFT)) & MDM_AP_MDMAPSTTS_CM70SLPNG_MASK)

#define MDM_AP_MDMAPSTTS_CM70DBGRSTRD_MASK       (0x10000000U)
#define MDM_AP_MDMAPSTTS_CM70DBGRSTRD_SHIFT      (28U)
#define MDM_AP_MDMAPSTTS_CM70DBGRSTRD_WIDTH      (1U)
#define MDM_AP_MDMAPSTTS_CM70DBGRSTRD(x)         (((uint32_t)(((uint32_t)(x)) << MDM_AP_MDMAPSTTS_CM70DBGRSTRD_SHIFT)) & MDM_AP_MDMAPSTTS_CM70DBGRSTRD_MASK)
/*! @} */

/*! @name MDMAPCTL - Control */
/*! @{ */

#define MDM_AP_MDMAPCTL_SYSRESETREQ_MASK         (0x10U)
#define MDM_AP_MDMAPCTL_SYSRESETREQ_SHIFT        (4U)
#define MDM_AP_MDMAPCTL_SYSRESETREQ_WIDTH        (1U)
#define MDM_AP_MDMAPCTL_SYSRESETREQ(x)           (((uint32_t)(((uint32_t)(x)) << MDM_AP_MDMAPCTL_SYSRESETREQ_SHIFT)) & MDM_AP_MDMAPCTL_SYSRESETREQ_MASK)

#define MDM_AP_MDMAPCTL_SYSFUNCRST_MASK          (0x20U)
#define MDM_AP_MDMAPCTL_SYSFUNCRST_SHIFT         (5U)
#define MDM_AP_MDMAPCTL_SYSFUNCRST_WIDTH         (1U)
#define MDM_AP_MDMAPCTL_SYSFUNCRST(x)            (((uint32_t)(((uint32_t)(x)) << MDM_AP_MDMAPCTL_SYSFUNCRST_SHIFT)) & MDM_AP_MDMAPCTL_SYSFUNCRST_MASK)

#define MDM_AP_MDMAPCTL_CM70DBGREQ_MASK          (0x100U)
#define MDM_AP_MDMAPCTL_CM70DBGREQ_SHIFT         (8U)
#define MDM_AP_MDMAPCTL_CM70DBGREQ_WIDTH         (1U)
#define MDM_AP_MDMAPCTL_CM70DBGREQ(x)            (((uint32_t)(((uint32_t)(x)) << MDM_AP_MDMAPCTL_CM70DBGREQ_SHIFT)) & MDM_AP_MDMAPCTL_CM70DBGREQ_MASK)

#define MDM_AP_MDMAPCTL_DBGRSTSLOWPAD_MASK       (0x1000U)
#define MDM_AP_MDMAPCTL_DBGRSTSLOWPAD_SHIFT      (12U)
#define MDM_AP_MDMAPCTL_DBGRSTSLOWPAD_WIDTH      (1U)
#define MDM_AP_MDMAPCTL_DBGRSTSLOWPAD(x)         (((uint32_t)(((uint32_t)(x)) << MDM_AP_MDMAPCTL_DBGRSTSLOWPAD_SHIFT)) & MDM_AP_MDMAPCTL_DBGRSTSLOWPAD_MASK)

#define MDM_AP_MDMAPCTL_DBGRSTFASTPAD_MASK       (0x2000U)
#define MDM_AP_MDMAPCTL_DBGRSTFASTPAD_SHIFT      (13U)
#define MDM_AP_MDMAPCTL_DBGRSTFASTPAD_WIDTH      (1U)
#define MDM_AP_MDMAPCTL_DBGRSTFASTPAD(x)         (((uint32_t)(((uint32_t)(x)) << MDM_AP_MDMAPCTL_DBGRSTFASTPAD_SHIFT)) & MDM_AP_MDMAPCTL_DBGRSTFASTPAD_MASK)

#define MDM_AP_MDMAPCTL_POR_WDG_DIS_MASK         (0x8000U)
#define MDM_AP_MDMAPCTL_POR_WDG_DIS_SHIFT        (15U)
#define MDM_AP_MDMAPCTL_POR_WDG_DIS_WIDTH        (1U)
#define MDM_AP_MDMAPCTL_POR_WDG_DIS(x)           (((uint32_t)(((uint32_t)(x)) << MDM_AP_MDMAPCTL_POR_WDG_DIS_SHIFT)) & MDM_AP_MDMAPCTL_POR_WDG_DIS_MASK)

#define MDM_AP_MDMAPCTL_TRIUOVRD_MASK            (0x100000U)
#define MDM_AP_MDMAPCTL_TRIUOVRD_SHIFT           (20U)
#define MDM_AP_MDMAPCTL_TRIUOVRD_WIDTH           (1U)
#define MDM_AP_MDMAPCTL_TRIUOVRD(x)              (((uint32_t)(((uint32_t)(x)) << MDM_AP_MDMAPCTL_TRIUOVRD_SHIFT)) & MDM_AP_MDMAPCTL_TRIUOVRD_MASK)

#define MDM_AP_MDMAPCTL_SWOOVRD_MASK             (0x400000U)
#define MDM_AP_MDMAPCTL_SWOOVRD_SHIFT            (22U)
#define MDM_AP_MDMAPCTL_SWOOVRD_WIDTH            (1U)
#define MDM_AP_MDMAPCTL_SWOOVRD(x)               (((uint32_t)(((uint32_t)(x)) << MDM_AP_MDMAPCTL_SWOOVRD_SHIFT)) & MDM_AP_MDMAPCTL_SWOOVRD_MASK)

#define MDM_AP_MDMAPCTL_CM70DBGRSRT_MASK         (0x10000000U)
#define MDM_AP_MDMAPCTL_CM70DBGRSRT_SHIFT        (28U)
#define MDM_AP_MDMAPCTL_CM70DBGRSRT_WIDTH        (1U)
#define MDM_AP_MDMAPCTL_CM70DBGRSRT(x)           (((uint32_t)(((uint32_t)(x)) << MDM_AP_MDMAPCTL_CM70DBGRSRT_SHIFT)) & MDM_AP_MDMAPCTL_CM70DBGRSRT_MASK)
/*! @} */

/*! @name MDMAPWIREN - WIR Enable */
/*! @{ */

#define MDM_AP_MDMAPWIREN_LWPWREN_MASK           (0x1U)
#define MDM_AP_MDMAPWIREN_LWPWREN_SHIFT          (0U)
#define MDM_AP_MDMAPWIREN_LWPWREN_WIDTH          (1U)
#define MDM_AP_MDMAPWIREN_LWPWREN(x)             (((uint32_t)(((uint32_t)(x)) << MDM_AP_MDMAPWIREN_LWPWREN_SHIFT)) & MDM_AP_MDMAPWIREN_LWPWREN_MASK)

#define MDM_AP_MDMAPWIREN_LWPRSTPRVT_MASK        (0x2U)
#define MDM_AP_MDMAPWIREN_LWPRSTPRVT_SHIFT       (1U)
#define MDM_AP_MDMAPWIREN_LWPRSTPRVT_WIDTH       (1U)
#define MDM_AP_MDMAPWIREN_LWPRSTPRVT(x)          (((uint32_t)(((uint32_t)(x)) << MDM_AP_MDMAPWIREN_LWPRSTPRVT_SHIFT)) & MDM_AP_MDMAPWIREN_LWPRSTPRVT_MASK)
/*! @} */

/*! @name MDMAPWIRSTTS - WIR Status */
/*! @{ */

#define MDM_AP_MDMAPWIRSTTS_MDM_DAP_WIR_STATUS_MASK (0xFFFFFFFFU)
#define MDM_AP_MDMAPWIRSTTS_MDM_DAP_WIR_STATUS_SHIFT (0U)
#define MDM_AP_MDMAPWIRSTTS_MDM_DAP_WIR_STATUS_WIDTH (32U)
#define MDM_AP_MDMAPWIRSTTS_MDM_DAP_WIR_STATUS(x) (((uint32_t)(((uint32_t)(x)) << MDM_AP_MDMAPWIRSTTS_MDM_DAP_WIR_STATUS_SHIFT)) & MDM_AP_MDMAPWIRSTTS_MDM_DAP_WIR_STATUS_MASK)
/*! @} */

/*! @name MDMAPWIRREL - WIR Release */
/*! @{ */

#define MDM_AP_MDMAPWIRREL_WTRSTRGM_MASK         (0x1U)
#define MDM_AP_MDMAPWIRREL_WTRSTRGM_SHIFT        (0U)
#define MDM_AP_MDMAPWIRREL_WTRSTRGM_WIDTH        (1U)
#define MDM_AP_MDMAPWIRREL_WTRSTRGM(x)           (((uint32_t)(((uint32_t)(x)) << MDM_AP_MDMAPWIRREL_WTRSTRGM_SHIFT)) & MDM_AP_MDMAPWIRREL_WTRSTRGM_MASK)

#define MDM_AP_MDMAPWIRREL_PRVNTRSTRGM_MASK      (0x2U)
#define MDM_AP_MDMAPWIRREL_PRVNTRSTRGM_SHIFT     (1U)
#define MDM_AP_MDMAPWIRREL_PRVNTRSTRGM_WIDTH     (1U)
#define MDM_AP_MDMAPWIRREL_PRVNTRSTRGM(x)        (((uint32_t)(((uint32_t)(x)) << MDM_AP_MDMAPWIRREL_PRVNTRSTRGM_SHIFT)) & MDM_AP_MDMAPWIRREL_PRVNTRSTRGM_MASK)
/*! @} */

/*! @name ID - Identity */
/*! @{ */

#define MDM_AP_ID_ID_MASK                        (0xFFFFFFFFU)
#define MDM_AP_ID_ID_SHIFT                       (0U)
#define MDM_AP_ID_ID_WIDTH                       (32U)
#define MDM_AP_ID_ID(x)                          (((uint32_t)(((uint32_t)(x)) << MDM_AP_ID_ID_SHIFT)) & MDM_AP_ID_ID_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group MDM_AP_Register_Masks */

/*!
 * @}
 */ /* end of group MDM_AP_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_MDM_AP_H_) */
