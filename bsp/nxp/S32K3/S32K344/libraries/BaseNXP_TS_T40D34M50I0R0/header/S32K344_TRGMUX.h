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
 * @file S32K344_TRGMUX.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_TRGMUX
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
#if !defined(S32K344_TRGMUX_H_)  /* Check if memory map has not been already included */
#define S32K344_TRGMUX_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- TRGMUX Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TRGMUX_Peripheral_Access_Layer TRGMUX Peripheral Access Layer
 * @{
 */

/** TRGMUX - Size of Registers Arrays */
#define TRGMUX_TRGMUXn_COUNT                      40u

/** TRGMUX - Register Layout Typedef */
typedef struct {
  __IO uint32_t TRGMUXn[TRGMUX_TRGMUXn_COUNT];     /**< TRGMUX ADC12_0 Register..TRGMUX CM7_RXEV Register, array offset: 0x0, array step: 0x4 */
} TRGMUX_Type, *TRGMUX_MemMapPtr;

/** Number of instances of the TRGMUX module. */
#define TRGMUX_INSTANCE_COUNT                    (1u)

/* TRGMUX - Peripheral instance base addresses */
/** Peripheral TRGMUX base address */
#define IP_TRGMUX_BASE                           (0x40080000u)
/** Peripheral TRGMUX base pointer */
#define IP_TRGMUX                                ((TRGMUX_Type *)IP_TRGMUX_BASE)
/** Array initializer of TRGMUX peripheral base addresses */
#define IP_TRGMUX_BASE_ADDRS                     { IP_TRGMUX_BASE }
/** Array initializer of TRGMUX peripheral base pointers */
#define IP_TRGMUX_BASE_PTRS                      { IP_TRGMUX }

/* ----------------------------------------------------------------------------
   -- TRGMUX Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup TRGMUX_Register_Masks TRGMUX Register Masks
 * @{
 */

/*! @name TRGMUXn - TRGMUX ADC12_0 Register..TRGMUX CM7_RXEV Register */
/*! @{ */

#define TRGMUX_TRGMUXn_SEL0_MASK                 (0x7FU)
#define TRGMUX_TRGMUXn_SEL0_SHIFT                (0U)
#define TRGMUX_TRGMUXn_SEL0_WIDTH                (7U)
#define TRGMUX_TRGMUXn_SEL0(x)                   (((uint32_t)(((uint32_t)(x)) << TRGMUX_TRGMUXn_SEL0_SHIFT)) & TRGMUX_TRGMUXn_SEL0_MASK)

#define TRGMUX_TRGMUXn_SEL1_MASK                 (0x7F00U)
#define TRGMUX_TRGMUXn_SEL1_SHIFT                (8U)
#define TRGMUX_TRGMUXn_SEL1_WIDTH                (7U)
#define TRGMUX_TRGMUXn_SEL1(x)                   (((uint32_t)(((uint32_t)(x)) << TRGMUX_TRGMUXn_SEL1_SHIFT)) & TRGMUX_TRGMUXn_SEL1_MASK)

#define TRGMUX_TRGMUXn_SEL2_MASK                 (0x7F0000U)
#define TRGMUX_TRGMUXn_SEL2_SHIFT                (16U)
#define TRGMUX_TRGMUXn_SEL2_WIDTH                (7U)
#define TRGMUX_TRGMUXn_SEL2(x)                   (((uint32_t)(((uint32_t)(x)) << TRGMUX_TRGMUXn_SEL2_SHIFT)) & TRGMUX_TRGMUXn_SEL2_MASK)

#define TRGMUX_TRGMUXn_SEL3_MASK                 (0x7F000000U)
#define TRGMUX_TRGMUXn_SEL3_SHIFT                (24U)
#define TRGMUX_TRGMUXn_SEL3_WIDTH                (7U)
#define TRGMUX_TRGMUXn_SEL3(x)                   (((uint32_t)(((uint32_t)(x)) << TRGMUX_TRGMUXn_SEL3_SHIFT)) & TRGMUX_TRGMUXn_SEL3_MASK)

#define TRGMUX_TRGMUXn_LK_MASK                   (0x80000000U)
#define TRGMUX_TRGMUXn_LK_SHIFT                  (31U)
#define TRGMUX_TRGMUXn_LK_WIDTH                  (1U)
#define TRGMUX_TRGMUXn_LK(x)                     (((uint32_t)(((uint32_t)(x)) << TRGMUX_TRGMUXn_LK_SHIFT)) & TRGMUX_TRGMUXn_LK_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group TRGMUX_Register_Masks */
#define TRGMUX_ADC12_0_INDEX 0
#define TRGMUX_ADC12_1_INDEX 1
#define TRGMUX_ADC12_2_INDEX 2
#define TRGMUX_LPCMP_0_INDEX 3
#define TRGMUX_LPCMP_1_INDEX 4
#define TRGMUX_LPCMP_2_INDEX 5
#define TRGMUX_BCTU_INDEX 6
#define TRGMUX_eMIOS012_ODIS_INDEX 7
#define TRGMUX_eMIOS0_0_INDEX 8
#define TRGMUX_eMIOS0_1_INDEX 9
#define TRGMUX_eMIOS0_2_INDEX 10
#define TRGMUX_eMIOS0_3_INDEX 11
#define TRGMUX_eMIOS1_0_INDEX 12
#define TRGMUX_eMIOS1_1_INDEX 13
#define TRGMUX_eMIOS1_2_INDEX 14
#define TRGMUX_eMIOS1_3_INDEX 15
#define TRGMUX_FlexIO_INDEX 16
#define TRGMUX_SIUL_OUT0_INDEX 17
#define TRGMUX_SIUL_OUT1_INDEX 18
#define TRGMUX_SIUL_OUT2_INDEX 19
#define TRGMUX_SIUL_OUT3_INDEX 20
#define TRGMUX_LPI2C_0_INDEX 21
#define TRGMUX_LPSPI_0_INDEX 22
#define TRGMUX_LPSPI_1_INDEX 23
#define TRGMUX_LPSPI_2_INDEX 24
#define TRGMUX_LPUART_0_INDEX 25
#define TRGMUX_LPUART_1_INDEX 26
#define TRGMUX_LPUART_2_INDEX 27
#define TRGMUX_LPUART_3_INDEX 28
#define TRGMUX_LCU0_SYNC_INDEX 29
#define TRGMUX_LCU0_FORCE_INDEX 30
#define TRGMUX_LCU0_0_INDEX 31
#define TRGMUX_LCU0_1_INDEX 32
#define TRGMUX_LCU0_2_INDEX 33
#define TRGMUX_LCU1_SYNC_INDEX 34
#define TRGMUX_LCU1_FORCE_INDEX 35
#define TRGMUX_LCU1_0_INDEX 36
#define TRGMUX_LCU1_1_INDEX 37
#define TRGMUX_LCU1_2_INDEX 38
#define TRGMUX_CM7_RXEV_INDEX 39


/*!
 * @}
 */ /* end of group TRGMUX_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_TRGMUX_H_) */
