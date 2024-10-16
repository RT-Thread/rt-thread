/*
** ###################################################################
**     Processor:           S32K344_M7
**     Reference manual:    S32K3xx RM Rev.2. Draft B
**     Version:             rev. 1.6, 2020-03-02
**     Build:               b210302
**
**     Abstract:
**         Peripheral Access Layer for S32K344_M7
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
 * @file S32K344_SYSTICK.h
 * @version 1.5
 * @date 2020-11-11
 * @brief Peripheral Access Layer for S32K344_SYSTICK
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
#if !defined(S32K344_SYSTICK_H_)  /* Check if memory map has not been already included */
#define S32K344_SYSTICK_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- S32_SysTick Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup S32_SysTick_Peripheral_Access_Layer S32_SysTick Peripheral Access Layer
 * @{
 */

/** S32_SysTick - Size of Registers Arrays */

/** S32_SysTick - Register Layout Typedef */
typedef struct {
  __IO uint32_t CSRr;                               /**< SysTick Control and Status Register, offset: 0x0 */
  __IO uint32_t RVR;                               /**< SysTick Reload Value Register, offset: 0x4 */
  __IO uint32_t CVR;                               /**< SysTick Current Value Register, offset: 0x8 */
  __I  uint32_t CALIB;                             /**< SysTick Calibration Value Register, offset: 0xC */
} S32_SysTick_Type, *S32_SysTick_MemMapPtr;

 /** Number of instances of the S32_SysTick module. */
#define S32_SysTick_INSTANCE_COUNT               (1u)



/* S32_SysTick - Peripheral instance base addresses */
/** Peripheral S32_SysTick base address */
#define S32_SysTick_BASE                         (0xE000E010u)
/** Peripheral S32_SysTick base pointer */
#define S32_SysTick                              ((S32_SysTick_Type *)S32_SysTick_BASE)
/** Array initializer of S32_SysTick peripheral base addresses */
#define S32_SysTick_BASE_ADDRS                   { S32_SysTick_BASE }
/** Array initializer of S32_SysTick peripheral base pointers */
#define S32_SysTick_BASE_PTRS                    { S32_SysTick }
 /** Number of interrupt vector arrays for the S32_SysTick module. */
#define S32_SysTick_IRQS_ARR_COUNT               (1u)
 /** Number of interrupt channels for the S32_SysTick module. */
#define S32_SysTick_IRQS_CH_COUNT                (1u)
/** Interrupt vectors for the S32_SysTick peripheral type */
#define S32_SysTick_IRQS                         { SysTick_IRQn }

/* ----------------------------------------------------------------------------
   -- S32_SysTick Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup S32_SysTick_Register_Masks S32_SysTick Register Masks
 * @{
 */

/* CSR Bit Fields */
#define S32_SysTick_CSR_ENABLE_MASK              0x1u
#define S32_SysTick_CSR_ENABLE_SHIFT             0u
#define S32_SysTick_CSR_ENABLE_WIDTH             1u
#define S32_SysTick_CSR_ENABLE(x)                (((uint32_t)(((uint32_t)(x))<<S32_SysTick_CSR_ENABLE_SHIFT))&S32_SysTick_CSR_ENABLE_MASK)
#define S32_SysTick_CSR_TICKINT_MASK             0x2u
#define S32_SysTick_CSR_TICKINT_SHIFT            1u
#define S32_SysTick_CSR_TICKINT_WIDTH            1u
#define S32_SysTick_CSR_TICKINT(x)               (((uint32_t)(((uint32_t)(x))<<S32_SysTick_CSR_TICKINT_SHIFT))&S32_SysTick_CSR_TICKINT_MASK)
#define S32_SysTick_CSR_CLKSOURCE_MASK           0x4u
#define S32_SysTick_CSR_CLKSOURCE_SHIFT          2u
#define S32_SysTick_CSR_CLKSOURCE_WIDTH          1u
#define S32_SysTick_CSR_CLKSOURCE(x)             (((uint32_t)(((uint32_t)(x))<<S32_SysTick_CSR_CLKSOURCE_SHIFT))&S32_SysTick_CSR_CLKSOURCE_MASK)
#define S32_SysTick_CSR_COUNTFLAG_MASK           0x10000u
#define S32_SysTick_CSR_COUNTFLAG_SHIFT          16u
#define S32_SysTick_CSR_COUNTFLAG_WIDTH          1u
#define S32_SysTick_CSR_COUNTFLAG(x)             (((uint32_t)(((uint32_t)(x))<<S32_SysTick_CSR_COUNTFLAG_SHIFT))&S32_SysTick_CSR_COUNTFLAG_MASK)
/* RVR Bit Fields */
#define S32_SysTick_RVR_RELOAD_MASK              0xFFFFFFu
#define S32_SysTick_RVR_RELOAD_SHIFT             0u
#define S32_SysTick_RVR_RELOAD_WIDTH             24u
#define S32_SysTick_RVR_RELOAD(x)                (((uint32_t)(((uint32_t)(x))<<S32_SysTick_RVR_RELOAD_SHIFT))&S32_SysTick_RVR_RELOAD_MASK)
/* CVR Bit Fields */
#define S32_SysTick_CVR_CURRENT_MASK             0xFFFFFFu
#define S32_SysTick_CVR_CURRENT_SHIFT            0u
#define S32_SysTick_CVR_CURRENT_WIDTH            24u
#define S32_SysTick_CVR_CURRENT(x)               (((uint32_t)(((uint32_t)(x))<<S32_SysTick_CVR_CURRENT_SHIFT))&S32_SysTick_CVR_CURRENT_MASK)
/* CALIB Bit Fields */
#define S32_SysTick_CALIB_TENMS_MASK             0xFFFFFFu
#define S32_SysTick_CALIB_TENMS_SHIFT            0u
#define S32_SysTick_CALIB_TENMS_WIDTH            24u
#define S32_SysTick_CALIB_TENMS(x)               (((uint32_t)(((uint32_t)(x))<<S32_SysTick_CALIB_TENMS_SHIFT))&S32_SysTick_CALIB_TENMS_MASK)
#define S32_SysTick_CALIB_SKEW_MASK              0x40000000u
#define S32_SysTick_CALIB_SKEW_SHIFT             30u
#define S32_SysTick_CALIB_SKEW_WIDTH
#define S32_SysTick_CALIB_SKEW(x)                (((uint32_t)(((uint32_t)(x))<<S32_SysTick_CALIB_SKEW_SHIFT))&S32_SysTick_CALIB_SKEW_MASK)
#define S32_SysTick_CALIB_NOREF_MASK             0x80000000u
#define S32_SysTick_CALIB_NOREF_SHIFT            31u
#define S32_SysTick_CALIB_NOREF_WIDTH            1u
#define S32_SysTick_CALIB_NOREF(x)               (((uint32_t)(((uint32_t)(x))<<S32_SysTick_CALIB_NOREF_SHIFT))&S32_SysTick_CALIB_NOREF_MASK)

/*!
 * @}
 */ /* end of group S32_SysTick_Register_Masks */

 /*!
 * @}
 */ /* end of group S32_SysTick_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_SYSTICK_H_) */
