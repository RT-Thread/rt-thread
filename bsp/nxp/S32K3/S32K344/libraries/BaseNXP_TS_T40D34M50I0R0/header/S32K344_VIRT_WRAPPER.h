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
 * @file S32K344_VIRT_WRAPPER.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_VIRT_WRAPPER
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
#if !defined(S32K344_VIRT_WRAPPER_H_)  /* Check if memory map has not been already included */
#define S32K344_VIRT_WRAPPER_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- VIRT_WRAPPER Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup VIRT_WRAPPER_Peripheral_Access_Layer VIRT_WRAPPER Peripheral Access Layer
 * @{
 */

/** VIRT_WRAPPER - Size of Registers Arrays */
#define VIRT_WRAPPER_REG_A_COUNT                  32u
#define VIRT_WRAPPER_REG_B_COUNT                  32u
#define VIRT_WRAPPER_REG_C_COUNT                  1u
#define VIRT_WRAPPER_REG_D_COUNT                  1u

/** VIRT_WRAPPER - Register Layout Typedef */
typedef struct {
  __IO uint32_t REG_A[VIRT_WRAPPER_REG_A_COUNT];   /**< Parameter_n Register, array offset: 0x0, array step: 0x4 */
  __IO uint32_t REG_B[VIRT_WRAPPER_REG_B_COUNT];   /**< Parameter_n Register, array offset: 0x80, array step: 0x4 */
  __IO uint32_t REG_C[VIRT_WRAPPER_REG_C_COUNT];   /**< Parameter_n Register, array offset: 0x100, array step: 0x4 */
  __IO uint32_t REG_D[VIRT_WRAPPER_REG_D_COUNT];   /**< Parameter_n Register, array offset: 0x104, array step: 0x4 */
} VIRT_WRAPPER_Type, *VIRT_WRAPPER_MemMapPtr;

/** Number of instances of the VIRT_WRAPPER module. */
#define VIRT_WRAPPER_INSTANCE_COUNT              (1u)

/* VIRT_WRAPPER - Peripheral instance base addresses */
/** Peripheral VIRT_WRAPPER base address */
#define IP_VIRT_WRAPPER_BASE                     (0x402A8000u)
/** Peripheral VIRT_WRAPPER base pointer */
#define IP_VIRT_WRAPPER                          ((VIRT_WRAPPER_Type *)IP_VIRT_WRAPPER_BASE)
/** Array initializer of VIRT_WRAPPER peripheral base addresses */
#define IP_VIRT_WRAPPER_BASE_ADDRS               { IP_VIRT_WRAPPER_BASE }
/** Array initializer of VIRT_WRAPPER peripheral base pointers */
#define IP_VIRT_WRAPPER_BASE_PTRS                { IP_VIRT_WRAPPER }

/* ----------------------------------------------------------------------------
   -- VIRT_WRAPPER Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup VIRT_WRAPPER_Register_Masks VIRT_WRAPPER Register Masks
 * @{
 */

/*! @name REG_A - Parameter_n Register */
/*! @{ */

#define VIRT_WRAPPER_REG_A_PAD_0_MASK            (0x3U)
#define VIRT_WRAPPER_REG_A_PAD_0_SHIFT           (0U)
#define VIRT_WRAPPER_REG_A_PAD_0_WIDTH           (2U)
#define VIRT_WRAPPER_REG_A_PAD_0(x)              (((uint32_t)(((uint32_t)(x)) << VIRT_WRAPPER_REG_A_PAD_0_SHIFT)) & VIRT_WRAPPER_REG_A_PAD_0_MASK)

#define VIRT_WRAPPER_REG_A_PAD_1_MASK            (0xCU)
#define VIRT_WRAPPER_REG_A_PAD_1_SHIFT           (2U)
#define VIRT_WRAPPER_REG_A_PAD_1_WIDTH           (2U)
#define VIRT_WRAPPER_REG_A_PAD_1(x)              (((uint32_t)(((uint32_t)(x)) << VIRT_WRAPPER_REG_A_PAD_1_SHIFT)) & VIRT_WRAPPER_REG_A_PAD_1_MASK)

#define VIRT_WRAPPER_REG_A_PAD_2_MASK            (0x30U)
#define VIRT_WRAPPER_REG_A_PAD_2_SHIFT           (4U)
#define VIRT_WRAPPER_REG_A_PAD_2_WIDTH           (2U)
#define VIRT_WRAPPER_REG_A_PAD_2(x)              (((uint32_t)(((uint32_t)(x)) << VIRT_WRAPPER_REG_A_PAD_2_SHIFT)) & VIRT_WRAPPER_REG_A_PAD_2_MASK)

#define VIRT_WRAPPER_REG_A_PAD_3_MASK            (0xC0U)
#define VIRT_WRAPPER_REG_A_PAD_3_SHIFT           (6U)
#define VIRT_WRAPPER_REG_A_PAD_3_WIDTH           (2U)
#define VIRT_WRAPPER_REG_A_PAD_3(x)              (((uint32_t)(((uint32_t)(x)) << VIRT_WRAPPER_REG_A_PAD_3_SHIFT)) & VIRT_WRAPPER_REG_A_PAD_3_MASK)

#define VIRT_WRAPPER_REG_A_PAD_4_MASK            (0x300U)
#define VIRT_WRAPPER_REG_A_PAD_4_SHIFT           (8U)
#define VIRT_WRAPPER_REG_A_PAD_4_WIDTH           (2U)
#define VIRT_WRAPPER_REG_A_PAD_4(x)              (((uint32_t)(((uint32_t)(x)) << VIRT_WRAPPER_REG_A_PAD_4_SHIFT)) & VIRT_WRAPPER_REG_A_PAD_4_MASK)

#define VIRT_WRAPPER_REG_A_PAD_5_MASK            (0xC00U)
#define VIRT_WRAPPER_REG_A_PAD_5_SHIFT           (10U)
#define VIRT_WRAPPER_REG_A_PAD_5_WIDTH           (2U)
#define VIRT_WRAPPER_REG_A_PAD_5(x)              (((uint32_t)(((uint32_t)(x)) << VIRT_WRAPPER_REG_A_PAD_5_SHIFT)) & VIRT_WRAPPER_REG_A_PAD_5_MASK)

#define VIRT_WRAPPER_REG_A_PAD_6_MASK            (0x3000U)
#define VIRT_WRAPPER_REG_A_PAD_6_SHIFT           (12U)
#define VIRT_WRAPPER_REG_A_PAD_6_WIDTH           (2U)
#define VIRT_WRAPPER_REG_A_PAD_6(x)              (((uint32_t)(((uint32_t)(x)) << VIRT_WRAPPER_REG_A_PAD_6_SHIFT)) & VIRT_WRAPPER_REG_A_PAD_6_MASK)

#define VIRT_WRAPPER_REG_A_PAD_7_MASK            (0xC000U)
#define VIRT_WRAPPER_REG_A_PAD_7_SHIFT           (14U)
#define VIRT_WRAPPER_REG_A_PAD_7_WIDTH           (2U)
#define VIRT_WRAPPER_REG_A_PAD_7(x)              (((uint32_t)(((uint32_t)(x)) << VIRT_WRAPPER_REG_A_PAD_7_SHIFT)) & VIRT_WRAPPER_REG_A_PAD_7_MASK)

#define VIRT_WRAPPER_REG_A_PAD_8_MASK            (0x30000U)
#define VIRT_WRAPPER_REG_A_PAD_8_SHIFT           (16U)
#define VIRT_WRAPPER_REG_A_PAD_8_WIDTH           (2U)
#define VIRT_WRAPPER_REG_A_PAD_8(x)              (((uint32_t)(((uint32_t)(x)) << VIRT_WRAPPER_REG_A_PAD_8_SHIFT)) & VIRT_WRAPPER_REG_A_PAD_8_MASK)

#define VIRT_WRAPPER_REG_A_PAD_9_MASK            (0xC0000U)
#define VIRT_WRAPPER_REG_A_PAD_9_SHIFT           (18U)
#define VIRT_WRAPPER_REG_A_PAD_9_WIDTH           (2U)
#define VIRT_WRAPPER_REG_A_PAD_9(x)              (((uint32_t)(((uint32_t)(x)) << VIRT_WRAPPER_REG_A_PAD_9_SHIFT)) & VIRT_WRAPPER_REG_A_PAD_9_MASK)

#define VIRT_WRAPPER_REG_A_PAD_10_MASK           (0x300000U)
#define VIRT_WRAPPER_REG_A_PAD_10_SHIFT          (20U)
#define VIRT_WRAPPER_REG_A_PAD_10_WIDTH          (2U)
#define VIRT_WRAPPER_REG_A_PAD_10(x)             (((uint32_t)(((uint32_t)(x)) << VIRT_WRAPPER_REG_A_PAD_10_SHIFT)) & VIRT_WRAPPER_REG_A_PAD_10_MASK)

#define VIRT_WRAPPER_REG_A_PAD_11_MASK           (0xC00000U)
#define VIRT_WRAPPER_REG_A_PAD_11_SHIFT          (22U)
#define VIRT_WRAPPER_REG_A_PAD_11_WIDTH          (2U)
#define VIRT_WRAPPER_REG_A_PAD_11(x)             (((uint32_t)(((uint32_t)(x)) << VIRT_WRAPPER_REG_A_PAD_11_SHIFT)) & VIRT_WRAPPER_REG_A_PAD_11_MASK)

#define VIRT_WRAPPER_REG_A_PAD_12_MASK           (0x3000000U)
#define VIRT_WRAPPER_REG_A_PAD_12_SHIFT          (24U)
#define VIRT_WRAPPER_REG_A_PAD_12_WIDTH          (2U)
#define VIRT_WRAPPER_REG_A_PAD_12(x)             (((uint32_t)(((uint32_t)(x)) << VIRT_WRAPPER_REG_A_PAD_12_SHIFT)) & VIRT_WRAPPER_REG_A_PAD_12_MASK)

#define VIRT_WRAPPER_REG_A_PAD_13_MASK           (0xC000000U)
#define VIRT_WRAPPER_REG_A_PAD_13_SHIFT          (26U)
#define VIRT_WRAPPER_REG_A_PAD_13_WIDTH          (2U)
#define VIRT_WRAPPER_REG_A_PAD_13(x)             (((uint32_t)(((uint32_t)(x)) << VIRT_WRAPPER_REG_A_PAD_13_SHIFT)) & VIRT_WRAPPER_REG_A_PAD_13_MASK)

#define VIRT_WRAPPER_REG_A_PAD_14_MASK           (0x30000000U)
#define VIRT_WRAPPER_REG_A_PAD_14_SHIFT          (28U)
#define VIRT_WRAPPER_REG_A_PAD_14_WIDTH          (2U)
#define VIRT_WRAPPER_REG_A_PAD_14(x)             (((uint32_t)(((uint32_t)(x)) << VIRT_WRAPPER_REG_A_PAD_14_SHIFT)) & VIRT_WRAPPER_REG_A_PAD_14_MASK)

#define VIRT_WRAPPER_REG_A_PAD_15_MASK           (0xC0000000U)
#define VIRT_WRAPPER_REG_A_PAD_15_SHIFT          (30U)
#define VIRT_WRAPPER_REG_A_PAD_15_WIDTH          (2U)
#define VIRT_WRAPPER_REG_A_PAD_15(x)             (((uint32_t)(((uint32_t)(x)) << VIRT_WRAPPER_REG_A_PAD_15_SHIFT)) & VIRT_WRAPPER_REG_A_PAD_15_MASK)
/*! @} */

/*! @name REG_B - Parameter_n Register */
/*! @{ */

#define VIRT_WRAPPER_REG_B_INMUX_0_MASK          (0x3U)
#define VIRT_WRAPPER_REG_B_INMUX_0_SHIFT         (0U)
#define VIRT_WRAPPER_REG_B_INMUX_0_WIDTH         (2U)
#define VIRT_WRAPPER_REG_B_INMUX_0(x)            (((uint32_t)(((uint32_t)(x)) << VIRT_WRAPPER_REG_B_INMUX_0_SHIFT)) & VIRT_WRAPPER_REG_B_INMUX_0_MASK)

#define VIRT_WRAPPER_REG_B_INMUX_1_MASK          (0xCU)
#define VIRT_WRAPPER_REG_B_INMUX_1_SHIFT         (2U)
#define VIRT_WRAPPER_REG_B_INMUX_1_WIDTH         (2U)
#define VIRT_WRAPPER_REG_B_INMUX_1(x)            (((uint32_t)(((uint32_t)(x)) << VIRT_WRAPPER_REG_B_INMUX_1_SHIFT)) & VIRT_WRAPPER_REG_B_INMUX_1_MASK)

#define VIRT_WRAPPER_REG_B_INMUX_2_MASK          (0x30U)
#define VIRT_WRAPPER_REG_B_INMUX_2_SHIFT         (4U)
#define VIRT_WRAPPER_REG_B_INMUX_2_WIDTH         (2U)
#define VIRT_WRAPPER_REG_B_INMUX_2(x)            (((uint32_t)(((uint32_t)(x)) << VIRT_WRAPPER_REG_B_INMUX_2_SHIFT)) & VIRT_WRAPPER_REG_B_INMUX_2_MASK)

#define VIRT_WRAPPER_REG_B_INMUX_3_MASK          (0xC0U)
#define VIRT_WRAPPER_REG_B_INMUX_3_SHIFT         (6U)
#define VIRT_WRAPPER_REG_B_INMUX_3_WIDTH         (2U)
#define VIRT_WRAPPER_REG_B_INMUX_3(x)            (((uint32_t)(((uint32_t)(x)) << VIRT_WRAPPER_REG_B_INMUX_3_SHIFT)) & VIRT_WRAPPER_REG_B_INMUX_3_MASK)

#define VIRT_WRAPPER_REG_B_INMUX_4_MASK          (0x300U)
#define VIRT_WRAPPER_REG_B_INMUX_4_SHIFT         (8U)
#define VIRT_WRAPPER_REG_B_INMUX_4_WIDTH         (2U)
#define VIRT_WRAPPER_REG_B_INMUX_4(x)            (((uint32_t)(((uint32_t)(x)) << VIRT_WRAPPER_REG_B_INMUX_4_SHIFT)) & VIRT_WRAPPER_REG_B_INMUX_4_MASK)

#define VIRT_WRAPPER_REG_B_INMUX_5_MASK          (0xC00U)
#define VIRT_WRAPPER_REG_B_INMUX_5_SHIFT         (10U)
#define VIRT_WRAPPER_REG_B_INMUX_5_WIDTH         (2U)
#define VIRT_WRAPPER_REG_B_INMUX_5(x)            (((uint32_t)(((uint32_t)(x)) << VIRT_WRAPPER_REG_B_INMUX_5_SHIFT)) & VIRT_WRAPPER_REG_B_INMUX_5_MASK)

#define VIRT_WRAPPER_REG_B_INMUX_6_MASK          (0x3000U)
#define VIRT_WRAPPER_REG_B_INMUX_6_SHIFT         (12U)
#define VIRT_WRAPPER_REG_B_INMUX_6_WIDTH         (2U)
#define VIRT_WRAPPER_REG_B_INMUX_6(x)            (((uint32_t)(((uint32_t)(x)) << VIRT_WRAPPER_REG_B_INMUX_6_SHIFT)) & VIRT_WRAPPER_REG_B_INMUX_6_MASK)

#define VIRT_WRAPPER_REG_B_INMUX_7_MASK          (0xC000U)
#define VIRT_WRAPPER_REG_B_INMUX_7_SHIFT         (14U)
#define VIRT_WRAPPER_REG_B_INMUX_7_WIDTH         (2U)
#define VIRT_WRAPPER_REG_B_INMUX_7(x)            (((uint32_t)(((uint32_t)(x)) << VIRT_WRAPPER_REG_B_INMUX_7_SHIFT)) & VIRT_WRAPPER_REG_B_INMUX_7_MASK)

#define VIRT_WRAPPER_REG_B_INMUX_8_MASK          (0x30000U)
#define VIRT_WRAPPER_REG_B_INMUX_8_SHIFT         (16U)
#define VIRT_WRAPPER_REG_B_INMUX_8_WIDTH         (2U)
#define VIRT_WRAPPER_REG_B_INMUX_8(x)            (((uint32_t)(((uint32_t)(x)) << VIRT_WRAPPER_REG_B_INMUX_8_SHIFT)) & VIRT_WRAPPER_REG_B_INMUX_8_MASK)

#define VIRT_WRAPPER_REG_B_INMUX_9_MASK          (0xC0000U)
#define VIRT_WRAPPER_REG_B_INMUX_9_SHIFT         (18U)
#define VIRT_WRAPPER_REG_B_INMUX_9_WIDTH         (2U)
#define VIRT_WRAPPER_REG_B_INMUX_9(x)            (((uint32_t)(((uint32_t)(x)) << VIRT_WRAPPER_REG_B_INMUX_9_SHIFT)) & VIRT_WRAPPER_REG_B_INMUX_9_MASK)

#define VIRT_WRAPPER_REG_B_INMUX_10_MASK         (0x300000U)
#define VIRT_WRAPPER_REG_B_INMUX_10_SHIFT        (20U)
#define VIRT_WRAPPER_REG_B_INMUX_10_WIDTH        (2U)
#define VIRT_WRAPPER_REG_B_INMUX_10(x)           (((uint32_t)(((uint32_t)(x)) << VIRT_WRAPPER_REG_B_INMUX_10_SHIFT)) & VIRT_WRAPPER_REG_B_INMUX_10_MASK)

#define VIRT_WRAPPER_REG_B_INMUX_11_MASK         (0xC00000U)
#define VIRT_WRAPPER_REG_B_INMUX_11_SHIFT        (22U)
#define VIRT_WRAPPER_REG_B_INMUX_11_WIDTH        (2U)
#define VIRT_WRAPPER_REG_B_INMUX_11(x)           (((uint32_t)(((uint32_t)(x)) << VIRT_WRAPPER_REG_B_INMUX_11_SHIFT)) & VIRT_WRAPPER_REG_B_INMUX_11_MASK)

#define VIRT_WRAPPER_REG_B_INMUX_12_MASK         (0x3000000U)
#define VIRT_WRAPPER_REG_B_INMUX_12_SHIFT        (24U)
#define VIRT_WRAPPER_REG_B_INMUX_12_WIDTH        (2U)
#define VIRT_WRAPPER_REG_B_INMUX_12(x)           (((uint32_t)(((uint32_t)(x)) << VIRT_WRAPPER_REG_B_INMUX_12_SHIFT)) & VIRT_WRAPPER_REG_B_INMUX_12_MASK)

#define VIRT_WRAPPER_REG_B_INMUX_13_MASK         (0xC000000U)
#define VIRT_WRAPPER_REG_B_INMUX_13_SHIFT        (26U)
#define VIRT_WRAPPER_REG_B_INMUX_13_WIDTH        (2U)
#define VIRT_WRAPPER_REG_B_INMUX_13(x)           (((uint32_t)(((uint32_t)(x)) << VIRT_WRAPPER_REG_B_INMUX_13_SHIFT)) & VIRT_WRAPPER_REG_B_INMUX_13_MASK)

#define VIRT_WRAPPER_REG_B_INMUX_14_MASK         (0x30000000U)
#define VIRT_WRAPPER_REG_B_INMUX_14_SHIFT        (28U)
#define VIRT_WRAPPER_REG_B_INMUX_14_WIDTH        (2U)
#define VIRT_WRAPPER_REG_B_INMUX_14(x)           (((uint32_t)(((uint32_t)(x)) << VIRT_WRAPPER_REG_B_INMUX_14_SHIFT)) & VIRT_WRAPPER_REG_B_INMUX_14_MASK)

#define VIRT_WRAPPER_REG_B_INMUX_15_MASK         (0xC0000000U)
#define VIRT_WRAPPER_REG_B_INMUX_15_SHIFT        (30U)
#define VIRT_WRAPPER_REG_B_INMUX_15_WIDTH        (2U)
#define VIRT_WRAPPER_REG_B_INMUX_15(x)           (((uint32_t)(((uint32_t)(x)) << VIRT_WRAPPER_REG_B_INMUX_15_SHIFT)) & VIRT_WRAPPER_REG_B_INMUX_15_MASK)
/*! @} */

/*! @name REG_C - Parameter_n Register */
/*! @{ */

#define VIRT_WRAPPER_REG_C_INTC_CTRL_MASK        (0x3U)
#define VIRT_WRAPPER_REG_C_INTC_CTRL_SHIFT       (0U)
#define VIRT_WRAPPER_REG_C_INTC_CTRL_WIDTH       (2U)
#define VIRT_WRAPPER_REG_C_INTC_CTRL(x)          (((uint32_t)(((uint32_t)(x)) << VIRT_WRAPPER_REG_C_INTC_CTRL_SHIFT)) & VIRT_WRAPPER_REG_C_INTC_CTRL_MASK)
/*! @} */

/*! @name REG_D - Parameter_n Register */
/*! @{ */

#define VIRT_WRAPPER_REG_D_REG_GCR_MASK          (0xC0000000U)
#define VIRT_WRAPPER_REG_D_REG_GCR_SHIFT         (30U)
#define VIRT_WRAPPER_REG_D_REG_GCR_WIDTH         (2U)
#define VIRT_WRAPPER_REG_D_REG_GCR(x)            (((uint32_t)(((uint32_t)(x)) << VIRT_WRAPPER_REG_D_REG_GCR_SHIFT)) & VIRT_WRAPPER_REG_D_REG_GCR_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group VIRT_WRAPPER_Register_Masks */

/*!
 * @}
 */ /* end of group VIRT_WRAPPER_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_VIRT_WRAPPER_H_) */
