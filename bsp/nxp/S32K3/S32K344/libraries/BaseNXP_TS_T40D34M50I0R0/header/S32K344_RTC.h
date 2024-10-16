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
 * @file S32K344_RTC.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_RTC
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
#if !defined(S32K344_RTC_H_)  /* Check if memory map has not been already included */
#define S32K344_RTC_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- RTC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTC_Peripheral_Access_Layer RTC Peripheral Access Layer
 * @{
 */

/** RTC - Register Layout Typedef */
typedef struct {
  __IO uint32_t RTCSUPV;                           /**< RTC Supervisor control register, offset: 0x0 */
  __IO uint32_t RTCC;                              /**< RTC Control register, offset: 0x4 */
  __IO uint32_t RTCS;                              /**< RTC Status register, offset: 0x8 */
  __I  uint32_t RTCCNT;                            /**< RTC Counter register, offset: 0xC */
  __IO uint32_t APIVAL;                            /**< API Compare value register, offset: 0x10 */
  __IO uint32_t RTCVAL;                            /**< RTC Compare value register, offset: 0x14 */
} RTC_Type, *RTC_MemMapPtr;

/** Number of instances of the RTC module. */
#define RTC_INSTANCE_COUNT                       (1u)

/* RTC - Peripheral instance base addresses */
/** Peripheral RTC base address */
#define IP_RTC_BASE                              (0x40288000u)
/** Peripheral RTC base pointer */
#define IP_RTC                                   ((RTC_Type *)IP_RTC_BASE)
/** Array initializer of RTC peripheral base addresses */
#define IP_RTC_BASE_ADDRS                        { IP_RTC_BASE }
/** Array initializer of RTC peripheral base pointers */
#define IP_RTC_BASE_PTRS                         { IP_RTC }

/* ----------------------------------------------------------------------------
   -- RTC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTC_Register_Masks RTC Register Masks
 * @{
 */

/*! @name RTCSUPV - RTC Supervisor control register */
/*! @{ */

#define RTC_RTCSUPV_SUPV_MASK                    (0x80000000U)
#define RTC_RTCSUPV_SUPV_SHIFT                   (31U)
#define RTC_RTCSUPV_SUPV_WIDTH                   (1U)
#define RTC_RTCSUPV_SUPV(x)                      (((uint32_t)(((uint32_t)(x)) << RTC_RTCSUPV_SUPV_SHIFT)) & RTC_RTCSUPV_SUPV_MASK)
/*! @} */

/*! @name RTCC - RTC Control register */
/*! @{ */

#define RTC_RTCC_TRIG_EN_MASK                    (0x1U)
#define RTC_RTCC_TRIG_EN_SHIFT                   (0U)
#define RTC_RTCC_TRIG_EN_WIDTH                   (1U)
#define RTC_RTCC_TRIG_EN(x)                      (((uint32_t)(((uint32_t)(x)) << RTC_RTCC_TRIG_EN_SHIFT)) & RTC_RTCC_TRIG_EN_MASK)

#define RTC_RTCC_DIV32EN_MASK                    (0x400U)
#define RTC_RTCC_DIV32EN_SHIFT                   (10U)
#define RTC_RTCC_DIV32EN_WIDTH                   (1U)
#define RTC_RTCC_DIV32EN(x)                      (((uint32_t)(((uint32_t)(x)) << RTC_RTCC_DIV32EN_SHIFT)) & RTC_RTCC_DIV32EN_MASK)

#define RTC_RTCC_DIV512EN_MASK                   (0x800U)
#define RTC_RTCC_DIV512EN_SHIFT                  (11U)
#define RTC_RTCC_DIV512EN_WIDTH                  (1U)
#define RTC_RTCC_DIV512EN(x)                     (((uint32_t)(((uint32_t)(x)) << RTC_RTCC_DIV512EN_SHIFT)) & RTC_RTCC_DIV512EN_MASK)

#define RTC_RTCC_CLKSEL_MASK                     (0x3000U)
#define RTC_RTCC_CLKSEL_SHIFT                    (12U)
#define RTC_RTCC_CLKSEL_WIDTH                    (2U)
#define RTC_RTCC_CLKSEL(x)                       (((uint32_t)(((uint32_t)(x)) << RTC_RTCC_CLKSEL_SHIFT)) & RTC_RTCC_CLKSEL_MASK)

#define RTC_RTCC_APIIE_MASK                      (0x4000U)
#define RTC_RTCC_APIIE_SHIFT                     (14U)
#define RTC_RTCC_APIIE_WIDTH                     (1U)
#define RTC_RTCC_APIIE(x)                        (((uint32_t)(((uint32_t)(x)) << RTC_RTCC_APIIE_SHIFT)) & RTC_RTCC_APIIE_MASK)

#define RTC_RTCC_APIEN_MASK                      (0x8000U)
#define RTC_RTCC_APIEN_SHIFT                     (15U)
#define RTC_RTCC_APIEN_WIDTH                     (1U)
#define RTC_RTCC_APIEN(x)                        (((uint32_t)(((uint32_t)(x)) << RTC_RTCC_APIEN_SHIFT)) & RTC_RTCC_APIEN_MASK)

#define RTC_RTCC_ROVREN_MASK                     (0x10000000U)
#define RTC_RTCC_ROVREN_SHIFT                    (28U)
#define RTC_RTCC_ROVREN_WIDTH                    (1U)
#define RTC_RTCC_ROVREN(x)                       (((uint32_t)(((uint32_t)(x)) << RTC_RTCC_ROVREN_SHIFT)) & RTC_RTCC_ROVREN_MASK)

#define RTC_RTCC_FRZEN_MASK                      (0x20000000U)
#define RTC_RTCC_FRZEN_SHIFT                     (29U)
#define RTC_RTCC_FRZEN_WIDTH                     (1U)
#define RTC_RTCC_FRZEN(x)                        (((uint32_t)(((uint32_t)(x)) << RTC_RTCC_FRZEN_SHIFT)) & RTC_RTCC_FRZEN_MASK)

#define RTC_RTCC_RTCIE_MASK                      (0x40000000U)
#define RTC_RTCC_RTCIE_SHIFT                     (30U)
#define RTC_RTCC_RTCIE_WIDTH                     (1U)
#define RTC_RTCC_RTCIE(x)                        (((uint32_t)(((uint32_t)(x)) << RTC_RTCC_RTCIE_SHIFT)) & RTC_RTCC_RTCIE_MASK)

#define RTC_RTCC_CNTEN_MASK                      (0x80000000U)
#define RTC_RTCC_CNTEN_SHIFT                     (31U)
#define RTC_RTCC_CNTEN_WIDTH                     (1U)
#define RTC_RTCC_CNTEN(x)                        (((uint32_t)(((uint32_t)(x)) << RTC_RTCC_CNTEN_SHIFT)) & RTC_RTCC_CNTEN_MASK)
/*! @} */

/*! @name RTCS - RTC Status register */
/*! @{ */

#define RTC_RTCS_ROVRF_MASK                      (0x400U)
#define RTC_RTCS_ROVRF_SHIFT                     (10U)
#define RTC_RTCS_ROVRF_WIDTH                     (1U)
#define RTC_RTCS_ROVRF(x)                        (((uint32_t)(((uint32_t)(x)) << RTC_RTCS_ROVRF_SHIFT)) & RTC_RTCS_ROVRF_MASK)

#define RTC_RTCS_APIF_MASK                       (0x2000U)
#define RTC_RTCS_APIF_SHIFT                      (13U)
#define RTC_RTCS_APIF_WIDTH                      (1U)
#define RTC_RTCS_APIF(x)                         (((uint32_t)(((uint32_t)(x)) << RTC_RTCS_APIF_SHIFT)) & RTC_RTCS_APIF_MASK)

#define RTC_RTCS_INV_API_MASK                    (0x20000U)
#define RTC_RTCS_INV_API_SHIFT                   (17U)
#define RTC_RTCS_INV_API_WIDTH                   (1U)
#define RTC_RTCS_INV_API(x)                      (((uint32_t)(((uint32_t)(x)) << RTC_RTCS_INV_API_SHIFT)) & RTC_RTCS_INV_API_MASK)

#define RTC_RTCS_INV_RTC_MASK                    (0x40000U)
#define RTC_RTCS_INV_RTC_SHIFT                   (18U)
#define RTC_RTCS_INV_RTC_WIDTH                   (1U)
#define RTC_RTCS_INV_RTC(x)                      (((uint32_t)(((uint32_t)(x)) << RTC_RTCS_INV_RTC_SHIFT)) & RTC_RTCS_INV_RTC_MASK)

#define RTC_RTCS_RTCF_MASK                       (0x20000000U)
#define RTC_RTCS_RTCF_SHIFT                      (29U)
#define RTC_RTCS_RTCF_WIDTH                      (1U)
#define RTC_RTCS_RTCF(x)                         (((uint32_t)(((uint32_t)(x)) << RTC_RTCS_RTCF_SHIFT)) & RTC_RTCS_RTCF_MASK)
/*! @} */

/*! @name RTCCNT - RTC Counter register */
/*! @{ */

#define RTC_RTCCNT_RTCCNT_MASK                   (0xFFFFFFFFU)
#define RTC_RTCCNT_RTCCNT_SHIFT                  (0U)
#define RTC_RTCCNT_RTCCNT_WIDTH                  (32U)
#define RTC_RTCCNT_RTCCNT(x)                     (((uint32_t)(((uint32_t)(x)) << RTC_RTCCNT_RTCCNT_SHIFT)) & RTC_RTCCNT_RTCCNT_MASK)
/*! @} */

/*! @name APIVAL - API Compare value register */
/*! @{ */

#define RTC_APIVAL_APIVAL_MASK                   (0xFFFFFFFFU)
#define RTC_APIVAL_APIVAL_SHIFT                  (0U)
#define RTC_APIVAL_APIVAL_WIDTH                  (32U)
#define RTC_APIVAL_APIVAL(x)                     (((uint32_t)(((uint32_t)(x)) << RTC_APIVAL_APIVAL_SHIFT)) & RTC_APIVAL_APIVAL_MASK)
/*! @} */

/*! @name RTCVAL - RTC Compare value register */
/*! @{ */

#define RTC_RTCVAL_RTCVAL_MASK                   (0xFFFFFFFFU)
#define RTC_RTCVAL_RTCVAL_SHIFT                  (0U)
#define RTC_RTCVAL_RTCVAL_WIDTH                  (32U)
#define RTC_RTCVAL_RTCVAL(x)                     (((uint32_t)(((uint32_t)(x)) << RTC_RTCVAL_RTCVAL_SHIFT)) & RTC_RTCVAL_RTCVAL_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group RTC_Register_Masks */

/*!
 * @}
 */ /* end of group RTC_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_RTC_H_) */
