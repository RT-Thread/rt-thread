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
 * @file S32K344_STM.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_STM
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
#if !defined(S32K344_STM_H_)  /* Check if memory map has not been already included */
#define S32K344_STM_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- STM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup STM_Peripheral_Access_Layer STM Peripheral Access Layer
 * @{
 */

/** STM - Size of Registers Arrays */
#define STM_CHANNEL_COUNT                         4u

/** STM - Register Layout Typedef */
typedef struct {
  __IO uint32_t CR;                                /**< Control, offset: 0x0 */
  __IO uint32_t CNT;                               /**< Count, offset: 0x4 */
  uint8_t RESERVED_0[8];
  struct {                                         /* offset: 0x10, array step: 0x10 */
    __IO uint32_t CCR;                               /**< Channel Control, array offset: 0x10, array step: 0x10 */
    __IO uint32_t CIR;                               /**< Channel Interrupt, array offset: 0x14, array step: 0x10 */
    __IO uint32_t CMP;                               /**< Channel Compare, array offset: 0x18, array step: 0x10 */
    uint8_t RESERVED_0[4];
  } CHANNEL[STM_CHANNEL_COUNT];
} STM_Type, *STM_MemMapPtr;

/** Number of instances of the STM module. */
#define STM_INSTANCE_COUNT                       (2u)

/* STM - Peripheral instance base addresses */
/** Peripheral STM_0 base address */
#define IP_STM_0_BASE                            (0x40274000u)
/** Peripheral STM_0 base pointer */
#define IP_STM_0                                 ((STM_Type *)IP_STM_0_BASE)
/** Peripheral STM_1 base address */
#define IP_STM_1_BASE                            (0x40474000u)
/** Peripheral STM_1 base pointer */
#define IP_STM_1                                 ((STM_Type *)IP_STM_1_BASE)
/** Array initializer of STM peripheral base addresses */
#define IP_STM_BASE_ADDRS                        { IP_STM_0_BASE, IP_STM_1_BASE }
/** Array initializer of STM peripheral base pointers */
#define IP_STM_BASE_PTRS                         { IP_STM_0, IP_STM_1 }

/* ----------------------------------------------------------------------------
   -- STM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup STM_Register_Masks STM Register Masks
 * @{
 */

/*! @name CR - Control */
/*! @{ */

#define STM_CR_TEN_MASK                          (0x1U)
#define STM_CR_TEN_SHIFT                         (0U)
#define STM_CR_TEN_WIDTH                         (1U)
#define STM_CR_TEN(x)                            (((uint32_t)(((uint32_t)(x)) << STM_CR_TEN_SHIFT)) & STM_CR_TEN_MASK)

#define STM_CR_FRZ_MASK                          (0x2U)
#define STM_CR_FRZ_SHIFT                         (1U)
#define STM_CR_FRZ_WIDTH                         (1U)
#define STM_CR_FRZ(x)                            (((uint32_t)(((uint32_t)(x)) << STM_CR_FRZ_SHIFT)) & STM_CR_FRZ_MASK)

#define STM_CR_CPS_MASK                          (0xFF00U)
#define STM_CR_CPS_SHIFT                         (8U)
#define STM_CR_CPS_WIDTH                         (8U)
#define STM_CR_CPS(x)                            (((uint32_t)(((uint32_t)(x)) << STM_CR_CPS_SHIFT)) & STM_CR_CPS_MASK)
/*! @} */

/*! @name CNT - Count */
/*! @{ */

#define STM_CNT_CNT_MASK                         (0xFFFFFFFFU)
#define STM_CNT_CNT_SHIFT                        (0U)
#define STM_CNT_CNT_WIDTH                        (32U)
#define STM_CNT_CNT(x)                           (((uint32_t)(((uint32_t)(x)) << STM_CNT_CNT_SHIFT)) & STM_CNT_CNT_MASK)
/*! @} */

/*! @name CCR - Channel Control */
/*! @{ */

#define STM_CCR_CEN_MASK                         (0x1U)
#define STM_CCR_CEN_SHIFT                        (0U)
#define STM_CCR_CEN_WIDTH                        (1U)
#define STM_CCR_CEN(x)                           (((uint32_t)(((uint32_t)(x)) << STM_CCR_CEN_SHIFT)) & STM_CCR_CEN_MASK)
/*! @} */

/*! @name CIR - Channel Interrupt */
/*! @{ */

#define STM_CIR_CIF_MASK                         (0x1U)
#define STM_CIR_CIF_SHIFT                        (0U)
#define STM_CIR_CIF_WIDTH                        (1U)
#define STM_CIR_CIF(x)                           (((uint32_t)(((uint32_t)(x)) << STM_CIR_CIF_SHIFT)) & STM_CIR_CIF_MASK)
/*! @} */

/*! @name CMP - Channel Compare */
/*! @{ */

#define STM_CMP_CMP_MASK                         (0xFFFFFFFFU)
#define STM_CMP_CMP_SHIFT                        (0U)
#define STM_CMP_CMP_WIDTH                        (32U)
#define STM_CMP_CMP(x)                           (((uint32_t)(((uint32_t)(x)) << STM_CMP_CMP_SHIFT)) & STM_CMP_CMP_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group STM_Register_Masks */

/*!
 * @}
 */ /* end of group STM_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_STM_H_) */
