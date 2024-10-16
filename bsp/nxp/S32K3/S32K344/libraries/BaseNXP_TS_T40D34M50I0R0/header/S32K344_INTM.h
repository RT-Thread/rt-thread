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
 * @file S32K344_INTM.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_INTM
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
#if !defined(S32K344_INTM_H_)  /* Check if memory map has not been already included */
#define S32K344_INTM_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- INTM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup INTM_Peripheral_Access_Layer INTM Peripheral Access Layer
 * @{
 */

/** INTM - Size of Registers Arrays */
#define INTM_MON_COUNT                            4u

/** INTM - Register Layout Typedef */
typedef struct {
  __IO uint32_t INTM_MM;                           /**< Monitor Mode, offset: 0x0 */
  __O  uint32_t INTM_IACK;                         /**< Interrupt Acknowledge, offset: 0x4 */
  struct {                                         /* offset: 0x8, array step: 0x10 */
    __IO uint32_t INTM_IRQSEL;                       /**< Interrupt Request Select 0..Interrupt Request Select 3, array offset: 0x8, array step: 0x10 */
    __IO uint32_t INTM_LATENCY;                      /**< INTM_LATENCY0..INTM_LATENCY3, array offset: 0xC, array step: 0x10 */
    __IO uint32_t INTM_TIMER;                        /**< Timer 0..Timer 3, array offset: 0x10, array step: 0x10 */
    __I  uint32_t INTM_STATUS;                       /**< Status 0..Status 3, array offset: 0x14, array step: 0x10 */
  } MON[INTM_MON_COUNT];
} INTM_Type, *INTM_MemMapPtr;

/** Number of instances of the INTM module. */
#define INTM_INSTANCE_COUNT                      (1u)

/* INTM - Peripheral instance base addresses */
/** Peripheral INTM base address */
#define IP_INTM_BASE                             (0x4027C000u)
/** Peripheral INTM base pointer */
#define IP_INTM                                  ((INTM_Type *)IP_INTM_BASE)
/** Array initializer of INTM peripheral base addresses */
#define IP_INTM_BASE_ADDRS                       { IP_INTM_BASE }
/** Array initializer of INTM peripheral base pointers */
#define IP_INTM_BASE_PTRS                        { IP_INTM }

/* ----------------------------------------------------------------------------
   -- INTM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup INTM_Register_Masks INTM Register Masks
 * @{
 */

/*! @name INTM_MM - Monitor Mode */
/*! @{ */

#define INTM_INTM_MM_MM_MASK                     (0x1U)
#define INTM_INTM_MM_MM_SHIFT                    (0U)
#define INTM_INTM_MM_MM_WIDTH                    (1U)
#define INTM_INTM_MM_MM(x)                       (((uint32_t)(((uint32_t)(x)) << INTM_INTM_MM_MM_SHIFT)) & INTM_INTM_MM_MM_MASK)
/*! @} */

/*! @name INTM_IACK - Interrupt Acknowledge */
/*! @{ */

#define INTM_INTM_IACK_IRQ_MASK                  (0x3FFU)
#define INTM_INTM_IACK_IRQ_SHIFT                 (0U)
#define INTM_INTM_IACK_IRQ_WIDTH                 (10U)
#define INTM_INTM_IACK_IRQ(x)                    (((uint32_t)(((uint32_t)(x)) << INTM_INTM_IACK_IRQ_SHIFT)) & INTM_INTM_IACK_IRQ_MASK)
/*! @} */

/*! @name INTM_IRQSEL - Interrupt Request Select 0..Interrupt Request Select 3 */
/*! @{ */

#define INTM_INTM_IRQSEL_IRQ_MASK                (0x3FFU)
#define INTM_INTM_IRQSEL_IRQ_SHIFT               (0U)
#define INTM_INTM_IRQSEL_IRQ_WIDTH               (10U)
#define INTM_INTM_IRQSEL_IRQ(x)                  (((uint32_t)(((uint32_t)(x)) << INTM_INTM_IRQSEL_IRQ_SHIFT)) & INTM_INTM_IRQSEL_IRQ_MASK)
/*! @} */

/*! @name INTM_LATENCY - INTM_LATENCY0..INTM_LATENCY3 */
/*! @{ */

#define INTM_INTM_LATENCY_LAT_MASK               (0xFFFFFFU)
#define INTM_INTM_LATENCY_LAT_SHIFT              (0U)
#define INTM_INTM_LATENCY_LAT_WIDTH              (24U)
#define INTM_INTM_LATENCY_LAT(x)                 (((uint32_t)(((uint32_t)(x)) << INTM_INTM_LATENCY_LAT_SHIFT)) & INTM_INTM_LATENCY_LAT_MASK)
/*! @} */

/*! @name INTM_TIMER - Timer 0..Timer 3 */
/*! @{ */

#define INTM_INTM_TIMER_TIMER_MASK               (0xFFFFFFU)
#define INTM_INTM_TIMER_TIMER_SHIFT              (0U)
#define INTM_INTM_TIMER_TIMER_WIDTH              (24U)
#define INTM_INTM_TIMER_TIMER(x)                 (((uint32_t)(((uint32_t)(x)) << INTM_INTM_TIMER_TIMER_SHIFT)) & INTM_INTM_TIMER_TIMER_MASK)
/*! @} */

/*! @name INTM_STATUS - Status 0..Status 3 */
/*! @{ */

#define INTM_INTM_STATUS_STATUS_MASK             (0x1U)
#define INTM_INTM_STATUS_STATUS_SHIFT            (0U)
#define INTM_INTM_STATUS_STATUS_WIDTH            (1U)
#define INTM_INTM_STATUS_STATUS(x)               (((uint32_t)(((uint32_t)(x)) << INTM_INTM_STATUS_STATUS_SHIFT)) & INTM_INTM_STATUS_STATUS_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group INTM_Register_Masks */

/*!
 * @}
 */ /* end of group INTM_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_INTM_H_) */
