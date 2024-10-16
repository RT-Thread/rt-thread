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
 * @file S32K344_SIRC.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_SIRC
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
#if !defined(S32K344_SIRC_H_)  /* Check if memory map has not been already included */
#define S32K344_SIRC_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- SIRC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SIRC_Peripheral_Access_Layer SIRC Peripheral Access Layer
 * @{
 */

/** SIRC - Register Layout Typedef */
typedef struct {
  uint8_t RESERVED_0[4];
  __I  uint32_t SR;                                /**< Status Register, offset: 0x4 */
  uint8_t RESERVED_1[4];
  __IO uint32_t MISCELLANEOUS_IN;                  /**< Miscellaneous input, offset: 0xC */
} SIRC_Type, *SIRC_MemMapPtr;

/** Number of instances of the SIRC module. */
#define SIRC_INSTANCE_COUNT                      (1u)

/* SIRC - Peripheral instance base addresses */
/** Peripheral SIRC base address */
#define IP_SIRC_BASE                             (0x402C8000u)
/** Peripheral SIRC base pointer */
#define IP_SIRC                                  ((SIRC_Type *)IP_SIRC_BASE)
/** Array initializer of SIRC peripheral base addresses */
#define IP_SIRC_BASE_ADDRS                       { IP_SIRC_BASE }
/** Array initializer of SIRC peripheral base pointers */
#define IP_SIRC_BASE_PTRS                        { IP_SIRC }

/* ----------------------------------------------------------------------------
   -- SIRC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SIRC_Register_Masks SIRC Register Masks
 * @{
 */

/*! @name SR - Status Register */
/*! @{ */

#define SIRC_SR_STATUS_MASK                      (0x1U)
#define SIRC_SR_STATUS_SHIFT                     (0U)
#define SIRC_SR_STATUS_WIDTH                     (1U)
#define SIRC_SR_STATUS(x)                        (((uint32_t)(((uint32_t)(x)) << SIRC_SR_STATUS_SHIFT)) & SIRC_SR_STATUS_MASK)
/*! @} */

/*! @name MISCELLANEOUS_IN - Miscellaneous input */
/*! @{ */

#define SIRC_MISCELLANEOUS_IN_STANDBY_ENABLE_MASK (0x100U)
#define SIRC_MISCELLANEOUS_IN_STANDBY_ENABLE_SHIFT (8U)
#define SIRC_MISCELLANEOUS_IN_STANDBY_ENABLE_WIDTH (1U)
#define SIRC_MISCELLANEOUS_IN_STANDBY_ENABLE(x)  (((uint32_t)(((uint32_t)(x)) << SIRC_MISCELLANEOUS_IN_STANDBY_ENABLE_SHIFT)) & SIRC_MISCELLANEOUS_IN_STANDBY_ENABLE_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group SIRC_Register_Masks */

/*!
 * @}
 */ /* end of group SIRC_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_SIRC_H_) */
