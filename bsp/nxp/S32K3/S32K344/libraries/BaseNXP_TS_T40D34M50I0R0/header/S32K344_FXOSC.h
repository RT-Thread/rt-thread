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
 * @file S32K344_FXOSC.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_FXOSC
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
#if !defined(S32K344_FXOSC_H_)  /* Check if memory map has not been already included */
#define S32K344_FXOSC_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- FXOSC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FXOSC_Peripheral_Access_Layer FXOSC Peripheral Access Layer
 * @{
 */

/** FXOSC - Register Layout Typedef */
typedef struct {
  __IO uint32_t CTRL;                              /**< FXOSC Control Register, offset: 0x0 */
  __I  uint32_t STAT;                              /**< Oscillator Status Register, offset: 0x4 */
} FXOSC_Type, *FXOSC_MemMapPtr;

/** Number of instances of the FXOSC module. */
#define FXOSC_INSTANCE_COUNT                     (1u)

/* FXOSC - Peripheral instance base addresses */
/** Peripheral FXOSC base address */
#define IP_FXOSC_BASE                            (0x402D4000u)
/** Peripheral FXOSC base pointer */
#define IP_FXOSC                                 ((FXOSC_Type *)IP_FXOSC_BASE)
/** Array initializer of FXOSC peripheral base addresses */
#define IP_FXOSC_BASE_ADDRS                      { IP_FXOSC_BASE }
/** Array initializer of FXOSC peripheral base pointers */
#define IP_FXOSC_BASE_PTRS                       { IP_FXOSC }

/* ----------------------------------------------------------------------------
   -- FXOSC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FXOSC_Register_Masks FXOSC Register Masks
 * @{
 */

/*! @name CTRL - FXOSC Control Register */
/*! @{ */

#define FXOSC_CTRL_OSCON_MASK                    (0x1U)
#define FXOSC_CTRL_OSCON_SHIFT                   (0U)
#define FXOSC_CTRL_OSCON_WIDTH                   (1U)
#define FXOSC_CTRL_OSCON(x)                      (((uint32_t)(((uint32_t)(x)) << FXOSC_CTRL_OSCON_SHIFT)) & FXOSC_CTRL_OSCON_MASK)

#define FXOSC_CTRL_GM_SEL_MASK                   (0xF0U)
#define FXOSC_CTRL_GM_SEL_SHIFT                  (4U)
#define FXOSC_CTRL_GM_SEL_WIDTH                  (4U)
#define FXOSC_CTRL_GM_SEL(x)                     (((uint32_t)(((uint32_t)(x)) << FXOSC_CTRL_GM_SEL_SHIFT)) & FXOSC_CTRL_GM_SEL_MASK)

#define FXOSC_CTRL_EOCV_MASK                     (0xFF0000U)
#define FXOSC_CTRL_EOCV_SHIFT                    (16U)
#define FXOSC_CTRL_EOCV_WIDTH                    (8U)
#define FXOSC_CTRL_EOCV(x)                       (((uint32_t)(((uint32_t)(x)) << FXOSC_CTRL_EOCV_SHIFT)) & FXOSC_CTRL_EOCV_MASK)

#define FXOSC_CTRL_COMP_EN_MASK                  (0x1000000U)
#define FXOSC_CTRL_COMP_EN_SHIFT                 (24U)
#define FXOSC_CTRL_COMP_EN_WIDTH                 (1U)
#define FXOSC_CTRL_COMP_EN(x)                    (((uint32_t)(((uint32_t)(x)) << FXOSC_CTRL_COMP_EN_SHIFT)) & FXOSC_CTRL_COMP_EN_MASK)

#define FXOSC_CTRL_OSC_BYP_MASK                  (0x80000000U)
#define FXOSC_CTRL_OSC_BYP_SHIFT                 (31U)
#define FXOSC_CTRL_OSC_BYP_WIDTH                 (1U)
#define FXOSC_CTRL_OSC_BYP(x)                    (((uint32_t)(((uint32_t)(x)) << FXOSC_CTRL_OSC_BYP_SHIFT)) & FXOSC_CTRL_OSC_BYP_MASK)
/*! @} */

/*! @name STAT - Oscillator Status Register */
/*! @{ */

#define FXOSC_STAT_OSC_STAT_MASK                 (0x80000000U)
#define FXOSC_STAT_OSC_STAT_SHIFT                (31U)
#define FXOSC_STAT_OSC_STAT_WIDTH                (1U)
#define FXOSC_STAT_OSC_STAT(x)                   (((uint32_t)(((uint32_t)(x)) << FXOSC_STAT_OSC_STAT_SHIFT)) & FXOSC_STAT_OSC_STAT_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group FXOSC_Register_Masks */

/*!
 * @}
 */ /* end of group FXOSC_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_FXOSC_H_) */
