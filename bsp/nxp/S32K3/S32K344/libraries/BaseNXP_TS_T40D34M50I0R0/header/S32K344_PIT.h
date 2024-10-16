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
 * @file S32K344_PIT.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_PIT
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
#if !defined(S32K344_PIT_H_)  /* Check if memory map has not been already included */
#define S32K344_PIT_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- PIT Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PIT_Peripheral_Access_Layer PIT Peripheral Access Layer
 * @{
 */

/** PIT - Size of Registers Arrays */
#define PIT_TIMER_COUNT                           4u

/** PIT - Register Layout Typedef */
typedef struct {
  __IO uint32_t MCR;                               /**< PIT Module Control Register, offset: 0x0 */
  uint8_t RESERVED_0[220];
  __I  uint32_t LTMR64H;                           /**< PIT Upper Lifetime Timer Register, offset: 0xE0 */
  __I  uint32_t LTMR64L;                           /**< PIT Lower Lifetime Timer Register, offset: 0xE4 */
  uint8_t RESERVED_1[4];
  __IO uint32_t RTI_LDVAL_STAT;                    /**< RTI Timer Load Value Sync Status Register, offset: 0xEC */
  __IO uint32_t RTI_LDVAL;                         /**< Timer Load Value Register, offset: 0xF0 */
  __I  uint32_t RTI_CVAL;                          /**< Current Timer Value Register, offset: 0xF4 */
  __IO uint32_t RTI_TCTRL;                         /**< Timer Control Register, offset: 0xF8 */
  __IO uint32_t RTI_TFLG;                          /**< Timer Flag Register, offset: 0xFC */
  struct {                                         /* offset: 0x100, array step: 0x10 */
    __IO uint32_t LDVAL;                             /**< Timer Load Value Register, array offset: 0x100, array step: 0x10 */
    __I  uint32_t CVAL;                              /**< Current Timer Value Register, array offset: 0x104, array step: 0x10 */
    __IO uint32_t TCTRL;                             /**< Timer Control Register, array offset: 0x108, array step: 0x10 */
    __IO uint32_t TFLG;                              /**< Timer Flag Register, array offset: 0x10C, array step: 0x10 */
  } TIMER[PIT_TIMER_COUNT];
} PIT_Type, *PIT_MemMapPtr;

/** Number of instances of the PIT module. */
#define PIT_INSTANCE_COUNT                       (3u)

/* PIT - Peripheral instance base addresses */
/** Peripheral PIT_0 base address */
#define IP_PIT_0_BASE                            (0x400B0000u)
/** Peripheral PIT_0 base pointer */
#define IP_PIT_0                                 ((PIT_Type *)IP_PIT_0_BASE)
/** Peripheral PIT_1 base address */
#define IP_PIT_1_BASE                            (0x400B4000u)
/** Peripheral PIT_1 base pointer */
#define IP_PIT_1                                 ((PIT_Type *)IP_PIT_1_BASE)
/** Peripheral PIT_2 base address */
#define IP_PIT_2_BASE                            (0x402FC000u)
/** Peripheral PIT_2 base pointer */
#define IP_PIT_2                                 ((PIT_Type *)IP_PIT_2_BASE)
/** Array initializer of PIT peripheral base addresses */
#define IP_PIT_BASE_ADDRS                        { IP_PIT_0_BASE, IP_PIT_1_BASE, IP_PIT_2_BASE }
/** Array initializer of PIT peripheral base pointers */
#define IP_PIT_BASE_PTRS                         { IP_PIT_0, IP_PIT_1, IP_PIT_2 }

/* ----------------------------------------------------------------------------
   -- PIT Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PIT_Register_Masks PIT Register Masks
 * @{
 */

/*! @name MCR - PIT Module Control Register */
/*! @{ */

#define PIT_MCR_FRZ_MASK                         (0x1U)
#define PIT_MCR_FRZ_SHIFT                        (0U)
#define PIT_MCR_FRZ_WIDTH                        (1U)
#define PIT_MCR_FRZ(x)                           (((uint32_t)(((uint32_t)(x)) << PIT_MCR_FRZ_SHIFT)) & PIT_MCR_FRZ_MASK)

#define PIT_MCR_MDIS_MASK                        (0x2U)
#define PIT_MCR_MDIS_SHIFT                       (1U)
#define PIT_MCR_MDIS_WIDTH                       (1U)
#define PIT_MCR_MDIS(x)                          (((uint32_t)(((uint32_t)(x)) << PIT_MCR_MDIS_SHIFT)) & PIT_MCR_MDIS_MASK)

#define PIT_MCR_MDIS_RTI_MASK                    (0x4U)
#define PIT_MCR_MDIS_RTI_SHIFT                   (2U)
#define PIT_MCR_MDIS_RTI_WIDTH                   (1U)
#define PIT_MCR_MDIS_RTI(x)                      (((uint32_t)(((uint32_t)(x)) << PIT_MCR_MDIS_RTI_SHIFT)) & PIT_MCR_MDIS_RTI_MASK)
/*! @} */

/*! @name LTMR64H - PIT Upper Lifetime Timer Register */
/*! @{ */

#define PIT_LTMR64H_LTH_MASK                     (0xFFFFFFFFU)
#define PIT_LTMR64H_LTH_SHIFT                    (0U)
#define PIT_LTMR64H_LTH_WIDTH                    (32U)
#define PIT_LTMR64H_LTH(x)                       (((uint32_t)(((uint32_t)(x)) << PIT_LTMR64H_LTH_SHIFT)) & PIT_LTMR64H_LTH_MASK)
/*! @} */

/*! @name LTMR64L - PIT Lower Lifetime Timer Register */
/*! @{ */

#define PIT_LTMR64L_LTL_MASK                     (0xFFFFFFFFU)
#define PIT_LTMR64L_LTL_SHIFT                    (0U)
#define PIT_LTMR64L_LTL_WIDTH                    (32U)
#define PIT_LTMR64L_LTL(x)                       (((uint32_t)(((uint32_t)(x)) << PIT_LTMR64L_LTL_SHIFT)) & PIT_LTMR64L_LTL_MASK)
/*! @} */

/*! @name RTI_LDVAL_STAT - RTI Timer Load Value Sync Status Register */
/*! @{ */

#define PIT_RTI_LDVAL_STAT_RT_STAT_MASK          (0x1U)
#define PIT_RTI_LDVAL_STAT_RT_STAT_SHIFT         (0U)
#define PIT_RTI_LDVAL_STAT_RT_STAT_WIDTH         (1U)
#define PIT_RTI_LDVAL_STAT_RT_STAT(x)            (((uint32_t)(((uint32_t)(x)) << PIT_RTI_LDVAL_STAT_RT_STAT_SHIFT)) & PIT_RTI_LDVAL_STAT_RT_STAT_MASK)
/*! @} */

/*! @name RTI_LDVAL - Timer Load Value Register */
/*! @{ */

#define PIT_RTI_LDVAL_TSV_MASK                   (0xFFFFFFFFU)
#define PIT_RTI_LDVAL_TSV_SHIFT                  (0U)
#define PIT_RTI_LDVAL_TSV_WIDTH                  (32U)
#define PIT_RTI_LDVAL_TSV(x)                     (((uint32_t)(((uint32_t)(x)) << PIT_RTI_LDVAL_TSV_SHIFT)) & PIT_RTI_LDVAL_TSV_MASK)
/*! @} */

/*! @name RTI_CVAL - Current Timer Value Register */
/*! @{ */

#define PIT_RTI_CVAL_TVL_MASK                    (0xFFFFFFFFU)
#define PIT_RTI_CVAL_TVL_SHIFT                   (0U)
#define PIT_RTI_CVAL_TVL_WIDTH                   (32U)
#define PIT_RTI_CVAL_TVL(x)                      (((uint32_t)(((uint32_t)(x)) << PIT_RTI_CVAL_TVL_SHIFT)) & PIT_RTI_CVAL_TVL_MASK)
/*! @} */

/*! @name RTI_TCTRL - Timer Control Register */
/*! @{ */

#define PIT_RTI_TCTRL_TEN_MASK                   (0x1U)
#define PIT_RTI_TCTRL_TEN_SHIFT                  (0U)
#define PIT_RTI_TCTRL_TEN_WIDTH                  (1U)
#define PIT_RTI_TCTRL_TEN(x)                     (((uint32_t)(((uint32_t)(x)) << PIT_RTI_TCTRL_TEN_SHIFT)) & PIT_RTI_TCTRL_TEN_MASK)

#define PIT_RTI_TCTRL_TIE_MASK                   (0x2U)
#define PIT_RTI_TCTRL_TIE_SHIFT                  (1U)
#define PIT_RTI_TCTRL_TIE_WIDTH                  (1U)
#define PIT_RTI_TCTRL_TIE(x)                     (((uint32_t)(((uint32_t)(x)) << PIT_RTI_TCTRL_TIE_SHIFT)) & PIT_RTI_TCTRL_TIE_MASK)

#define PIT_RTI_TCTRL_CHN_MASK                   (0x4U)
#define PIT_RTI_TCTRL_CHN_SHIFT                  (2U)
#define PIT_RTI_TCTRL_CHN_WIDTH                  (1U)
#define PIT_RTI_TCTRL_CHN(x)                     (((uint32_t)(((uint32_t)(x)) << PIT_RTI_TCTRL_CHN_SHIFT)) & PIT_RTI_TCTRL_CHN_MASK)
/*! @} */

/*! @name RTI_TFLG - Timer Flag Register */
/*! @{ */

#define PIT_RTI_TFLG_TIF_MASK                    (0x1U)
#define PIT_RTI_TFLG_TIF_SHIFT                   (0U)
#define PIT_RTI_TFLG_TIF_WIDTH                   (1U)
#define PIT_RTI_TFLG_TIF(x)                      (((uint32_t)(((uint32_t)(x)) << PIT_RTI_TFLG_TIF_SHIFT)) & PIT_RTI_TFLG_TIF_MASK)
/*! @} */

/*! @name LDVAL - Timer Load Value Register */
/*! @{ */

#define PIT_LDVAL_TSV_MASK                       (0xFFFFFFFFU)
#define PIT_LDVAL_TSV_SHIFT                      (0U)
#define PIT_LDVAL_TSV_WIDTH                      (32U)
#define PIT_LDVAL_TSV(x)                         (((uint32_t)(((uint32_t)(x)) << PIT_LDVAL_TSV_SHIFT)) & PIT_LDVAL_TSV_MASK)
/*! @} */

/*! @name CVAL - Current Timer Value Register */
/*! @{ */

#define PIT_CVAL_TVL_MASK                        (0xFFFFFFFFU)
#define PIT_CVAL_TVL_SHIFT                       (0U)
#define PIT_CVAL_TVL_WIDTH                       (32U)
#define PIT_CVAL_TVL(x)                          (((uint32_t)(((uint32_t)(x)) << PIT_CVAL_TVL_SHIFT)) & PIT_CVAL_TVL_MASK)
/*! @} */

/*! @name TCTRL - Timer Control Register */
/*! @{ */

#define PIT_TCTRL_TEN_MASK                       (0x1U)
#define PIT_TCTRL_TEN_SHIFT                      (0U)
#define PIT_TCTRL_TEN_WIDTH                      (1U)
#define PIT_TCTRL_TEN(x)                         (((uint32_t)(((uint32_t)(x)) << PIT_TCTRL_TEN_SHIFT)) & PIT_TCTRL_TEN_MASK)

#define PIT_TCTRL_TIE_MASK                       (0x2U)
#define PIT_TCTRL_TIE_SHIFT                      (1U)
#define PIT_TCTRL_TIE_WIDTH                      (1U)
#define PIT_TCTRL_TIE(x)                         (((uint32_t)(((uint32_t)(x)) << PIT_TCTRL_TIE_SHIFT)) & PIT_TCTRL_TIE_MASK)

#define PIT_TCTRL_CHN_MASK                       (0x4U)
#define PIT_TCTRL_CHN_SHIFT                      (2U)
#define PIT_TCTRL_CHN_WIDTH                      (1U)
#define PIT_TCTRL_CHN(x)                         (((uint32_t)(((uint32_t)(x)) << PIT_TCTRL_CHN_SHIFT)) & PIT_TCTRL_CHN_MASK)
/*! @} */

/*! @name TFLG - Timer Flag Register */
/*! @{ */

#define PIT_TFLG_TIF_MASK                        (0x1U)
#define PIT_TFLG_TIF_SHIFT                       (0U)
#define PIT_TFLG_TIF_WIDTH                       (1U)
#define PIT_TFLG_TIF(x)                          (((uint32_t)(((uint32_t)(x)) << PIT_TFLG_TIF_SHIFT)) & PIT_TFLG_TIF_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group PIT_Register_Masks */

/*!
 * @}
 */ /* end of group PIT_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_PIT_H_) */
