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
 * @file S32K344_FIRC.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_FIRC
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
#if !defined(S32K344_FIRC_H_)  /* Check if memory map has not been already included */
#define S32K344_FIRC_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- FIRC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FIRC_Peripheral_Access_Layer FIRC Peripheral Access Layer
 * @{
 */

/** FIRC - Register Layout Typedef */
typedef struct {
  uint8_t RESERVED_0[4];
  __I  uint32_t STATUS_REGISTER;                   /**< Status Register, offset: 0x4 */
  __IO uint32_t STDBY_ENABLE;                      /**< Standby Enable Register, offset: 0x8 */
} FIRC_Type, *FIRC_MemMapPtr;

/** Number of instances of the FIRC module. */
#define FIRC_INSTANCE_COUNT                      (1u)

/* FIRC - Peripheral instance base addresses */
/** Peripheral FIRC base address */
#define IP_FIRC_BASE                             (0x402D0000u)
/** Peripheral FIRC base pointer */
#define IP_FIRC                                  ((FIRC_Type *)IP_FIRC_BASE)
/** Array initializer of FIRC peripheral base addresses */
#define IP_FIRC_BASE_ADDRS                       { IP_FIRC_BASE }
/** Array initializer of FIRC peripheral base pointers */
#define IP_FIRC_BASE_PTRS                        { IP_FIRC }

/* ----------------------------------------------------------------------------
   -- FIRC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FIRC_Register_Masks FIRC Register Masks
 * @{
 */

/*! @name STATUS_REGISTER - Status Register */
/*! @{ */

#define FIRC_STATUS_REGISTER_STATUS_MASK         (0x1U)
#define FIRC_STATUS_REGISTER_STATUS_SHIFT        (0U)
#define FIRC_STATUS_REGISTER_STATUS_WIDTH        (1U)
#define FIRC_STATUS_REGISTER_STATUS(x)           (((uint32_t)(((uint32_t)(x)) << FIRC_STATUS_REGISTER_STATUS_SHIFT)) & FIRC_STATUS_REGISTER_STATUS_MASK)
/*! @} */

/*! @name STDBY_ENABLE - Standby Enable Register */
/*! @{ */

#define FIRC_STDBY_ENABLE_STDBY_EN_MASK          (0x1U)
#define FIRC_STDBY_ENABLE_STDBY_EN_SHIFT         (0U)
#define FIRC_STDBY_ENABLE_STDBY_EN_WIDTH         (1U)
#define FIRC_STDBY_ENABLE_STDBY_EN(x)            (((uint32_t)(((uint32_t)(x)) << FIRC_STDBY_ENABLE_STDBY_EN_SHIFT)) & FIRC_STDBY_ENABLE_STDBY_EN_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group FIRC_Register_Masks */

/*!
 * @}
 */ /* end of group FIRC_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_FIRC_H_) */
