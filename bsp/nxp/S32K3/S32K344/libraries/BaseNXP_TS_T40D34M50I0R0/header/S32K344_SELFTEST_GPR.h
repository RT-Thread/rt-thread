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
 * @file S32K344_SELFTEST_GPR.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_SELFTEST_GPR
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
#if !defined(S32K344_SELFTEST_GPR_H_)  /* Check if memory map has not been already included */
#define S32K344_SELFTEST_GPR_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- SELFTEST_GPR Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SELFTEST_GPR_Peripheral_Access_Layer SELFTEST_GPR Peripheral Access Layer
 * @{
 */

/** SELFTEST_GPR - Register Layout Typedef */
typedef struct {
  __IO uint32_t CONFIG_REG;                        /**< Configuration register, offset: 0x0 */
  uint8_t RESERVED_0[16];
  __IO uint32_t LBIST_PROG_REG;                    /**< LBIST Program, offset: 0x14 */
} SELFTEST_GPR_Type, *SELFTEST_GPR_MemMapPtr;

/** Number of instances of the SELFTEST_GPR module. */
#define SELFTEST_GPR_INSTANCE_COUNT              (1u)

/* SELFTEST_GPR - Peripheral instance base addresses */
/** Peripheral SELFTEST_GPR base address */
#define IP_SELFTEST_GPR_BASE                     (0x403B0000u)
/** Peripheral SELFTEST_GPR base pointer */
#define IP_SELFTEST_GPR                          ((SELFTEST_GPR_Type *)IP_SELFTEST_GPR_BASE)
/** Array initializer of SELFTEST_GPR peripheral base addresses */
#define IP_SELFTEST_GPR_BASE_ADDRS               { IP_SELFTEST_GPR_BASE }
/** Array initializer of SELFTEST_GPR peripheral base pointers */
#define IP_SELFTEST_GPR_BASE_PTRS                { IP_SELFTEST_GPR }

/* ----------------------------------------------------------------------------
   -- SELFTEST_GPR Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SELFTEST_GPR_Register_Masks SELFTEST_GPR Register Masks
 * @{
 */

/*! @name CONFIG_REG - Configuration register */
/*! @{ */

#define SELFTEST_GPR_CONFIG_REG_PCS_STEP_SIZE_MASK (0x70U)
#define SELFTEST_GPR_CONFIG_REG_PCS_STEP_SIZE_SHIFT (4U)
#define SELFTEST_GPR_CONFIG_REG_PCS_STEP_SIZE_WIDTH (3U)
#define SELFTEST_GPR_CONFIG_REG_PCS_STEP_SIZE(x) (((uint32_t)(((uint32_t)(x)) << SELFTEST_GPR_CONFIG_REG_PCS_STEP_SIZE_SHIFT)) & SELFTEST_GPR_CONFIG_REG_PCS_STEP_SIZE_MASK)

#define SELFTEST_GPR_CONFIG_REG_PCS_ENABLE_START_MASK (0x80U)
#define SELFTEST_GPR_CONFIG_REG_PCS_ENABLE_START_SHIFT (7U)
#define SELFTEST_GPR_CONFIG_REG_PCS_ENABLE_START_WIDTH (1U)
#define SELFTEST_GPR_CONFIG_REG_PCS_ENABLE_START(x) (((uint32_t)(((uint32_t)(x)) << SELFTEST_GPR_CONFIG_REG_PCS_ENABLE_START_SHIFT)) & SELFTEST_GPR_CONFIG_REG_PCS_ENABLE_START_MASK)

#define SELFTEST_GPR_CONFIG_REG_PCS_ENABLE_END_MASK (0x100U)
#define SELFTEST_GPR_CONFIG_REG_PCS_ENABLE_END_SHIFT (8U)
#define SELFTEST_GPR_CONFIG_REG_PCS_ENABLE_END_WIDTH (1U)
#define SELFTEST_GPR_CONFIG_REG_PCS_ENABLE_END(x) (((uint32_t)(((uint32_t)(x)) << SELFTEST_GPR_CONFIG_REG_PCS_ENABLE_END_SHIFT)) & SELFTEST_GPR_CONFIG_REG_PCS_ENABLE_END_MASK)
/*! @} */

/*! @name LBIST_PROG_REG - LBIST Program */
/*! @{ */

#define SELFTEST_GPR_LBIST_PROG_REG_LBIST_SHIFT_COUNT_MASK (0xFFU)
#define SELFTEST_GPR_LBIST_PROG_REG_LBIST_SHIFT_COUNT_SHIFT (0U)
#define SELFTEST_GPR_LBIST_PROG_REG_LBIST_SHIFT_COUNT_WIDTH (8U)
#define SELFTEST_GPR_LBIST_PROG_REG_LBIST_SHIFT_COUNT(x) (((uint32_t)(((uint32_t)(x)) << SELFTEST_GPR_LBIST_PROG_REG_LBIST_SHIFT_COUNT_SHIFT)) & SELFTEST_GPR_LBIST_PROG_REG_LBIST_SHIFT_COUNT_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group SELFTEST_GPR_Register_Masks */

/*!
 * @}
 */ /* end of group SELFTEST_GPR_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_SELFTEST_GPR_H_) */
