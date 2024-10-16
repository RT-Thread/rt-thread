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
 * @file S32K344_SXOSC.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_SXOSC
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
#if !defined(S32K344_SXOSC_H_)  /* Check if memory map has not been already included */
#define S32K344_SXOSC_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- SXOSC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SXOSC_Peripheral_Access_Layer SXOSC Peripheral Access Layer
 * @{
 */

/** SXOSC - Register Layout Typedef */
typedef struct {
  __IO uint32_t SXOSC_CTRL;                        /**< Oscillator Control, offset: 0x0 */
  __I  uint32_t SXOSC_STAT;                        /**< Oscillator Status, offset: 0x4 */
} SXOSC_Type, *SXOSC_MemMapPtr;

/** Number of instances of the SXOSC module. */
#define SXOSC_INSTANCE_COUNT                     (1u)

/* SXOSC - Peripheral instance base addresses */
/** Peripheral SXOSC base address */
#define IP_SXOSC_BASE                            (0x402CC000u)
/** Peripheral SXOSC base pointer */
#define IP_SXOSC                                 ((SXOSC_Type *)IP_SXOSC_BASE)
/** Array initializer of SXOSC peripheral base addresses */
#define IP_SXOSC_BASE_ADDRS                      { IP_SXOSC_BASE }
/** Array initializer of SXOSC peripheral base pointers */
#define IP_SXOSC_BASE_PTRS                       { IP_SXOSC }

/* ----------------------------------------------------------------------------
   -- SXOSC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SXOSC_Register_Masks SXOSC Register Masks
 * @{
 */

/*! @name SXOSC_CTRL - Oscillator Control */
/*! @{ */

#define SXOSC_SXOSC_CTRL_OSCON_MASK              (0x1U)
#define SXOSC_SXOSC_CTRL_OSCON_SHIFT             (0U)
#define SXOSC_SXOSC_CTRL_OSCON_WIDTH             (1U)
#define SXOSC_SXOSC_CTRL_OSCON(x)                (((uint32_t)(((uint32_t)(x)) << SXOSC_SXOSC_CTRL_OSCON_SHIFT)) & SXOSC_SXOSC_CTRL_OSCON_MASK)

#define SXOSC_SXOSC_CTRL_EOCV_MASK               (0xFF0000U)
#define SXOSC_SXOSC_CTRL_EOCV_SHIFT              (16U)
#define SXOSC_SXOSC_CTRL_EOCV_WIDTH              (8U)
#define SXOSC_SXOSC_CTRL_EOCV(x)                 (((uint32_t)(((uint32_t)(x)) << SXOSC_SXOSC_CTRL_EOCV_SHIFT)) & SXOSC_SXOSC_CTRL_EOCV_MASK)
/*! @} */

/*! @name SXOSC_STAT - Oscillator Status */
/*! @{ */

#define SXOSC_SXOSC_STAT_OSC_STAT_MASK           (0x80000000U)
#define SXOSC_SXOSC_STAT_OSC_STAT_SHIFT          (31U)
#define SXOSC_SXOSC_STAT_OSC_STAT_WIDTH          (1U)
#define SXOSC_SXOSC_STAT_OSC_STAT(x)             (((uint32_t)(((uint32_t)(x)) << SXOSC_SXOSC_STAT_OSC_STAT_SHIFT)) & SXOSC_SXOSC_STAT_OSC_STAT_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group SXOSC_Register_Masks */

/*!
 * @}
 */ /* end of group SXOSC_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_SXOSC_H_) */
