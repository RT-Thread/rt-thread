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
 * @file S32K344_PLL.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_PLL
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
#if !defined(S32K344_PLL_H_)  /* Check if memory map has not been already included */
#define S32K344_PLL_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- PLL Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PLL_Peripheral_Access_Layer PLL Peripheral Access Layer
 * @{
 */

/** PLL - Size of Registers Arrays */
#define PLL_PLLODIV_COUNT                         2u

/** PLL - Register Layout Typedef */
typedef struct {
  __IO uint32_t PLLCR;                             /**< PLL Control, offset: 0x0 */
  __IO uint32_t PLLSR;                             /**< PLL Status, offset: 0x4 */
  __IO uint32_t PLLDV;                             /**< PLL Divider, offset: 0x8 */
  __IO uint32_t PLLFM;                             /**< PLL Frequency Modulation, offset: 0xC */
  __IO uint32_t PLLFD;                             /**< PLL Fractional Divider, offset: 0x10 */
  uint8_t RESERVED_0[4];
  __IO uint32_t PLLCAL2;                           /**< PLL Calibration Register 2, offset: 0x18 */
  uint8_t RESERVED_1[100];
  __IO uint32_t PLLODIV[PLL_PLLODIV_COUNT];        /**< PLL Output Divider, array offset: 0x80, array step: 0x4 */
} PLL_Type, *PLL_MemMapPtr;

/** Number of instances of the PLL module. */
#define PLL_INSTANCE_COUNT                       (1u)

/* PLL - Peripheral instance base addresses */
/** Peripheral PLL base address */
#define IP_PLL_BASE                              (0x402E0000u)
/** Peripheral PLL base pointer */
#define IP_PLL                                   ((PLL_Type *)IP_PLL_BASE)
/** Array initializer of PLL peripheral base addresses */
#define IP_PLL_BASE_ADDRS                        { IP_PLL_BASE }
/** Array initializer of PLL peripheral base pointers */
#define IP_PLL_BASE_PTRS                         { IP_PLL }

/* ----------------------------------------------------------------------------
   -- PLL Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PLL_Register_Masks PLL Register Masks
 * @{
 */

/*! @name PLLCR - PLL Control */
/*! @{ */

#define PLL_PLLCR_PLLPD_MASK                     (0x80000000U)
#define PLL_PLLCR_PLLPD_SHIFT                    (31U)
#define PLL_PLLCR_PLLPD_WIDTH                    (1U)
#define PLL_PLLCR_PLLPD(x)                       (((uint32_t)(((uint32_t)(x)) << PLL_PLLCR_PLLPD_SHIFT)) & PLL_PLLCR_PLLPD_MASK)
/*! @} */

/*! @name PLLSR - PLL Status */
/*! @{ */

#define PLL_PLLSR_LOCK_MASK                      (0x4U)
#define PLL_PLLSR_LOCK_SHIFT                     (2U)
#define PLL_PLLSR_LOCK_WIDTH                     (1U)
#define PLL_PLLSR_LOCK(x)                        (((uint32_t)(((uint32_t)(x)) << PLL_PLLSR_LOCK_SHIFT)) & PLL_PLLSR_LOCK_MASK)

#define PLL_PLLSR_LOL_MASK                       (0x8U)
#define PLL_PLLSR_LOL_SHIFT                      (3U)
#define PLL_PLLSR_LOL_WIDTH                      (1U)
#define PLL_PLLSR_LOL(x)                         (((uint32_t)(((uint32_t)(x)) << PLL_PLLSR_LOL_SHIFT)) & PLL_PLLSR_LOL_MASK)
/*! @} */

/*! @name PLLDV - PLL Divider */
/*! @{ */

#define PLL_PLLDV_MFI_MASK                       (0xFFU)
#define PLL_PLLDV_MFI_SHIFT                      (0U)
#define PLL_PLLDV_MFI_WIDTH                      (8U)
#define PLL_PLLDV_MFI(x)                         (((uint32_t)(((uint32_t)(x)) << PLL_PLLDV_MFI_SHIFT)) & PLL_PLLDV_MFI_MASK)

#define PLL_PLLDV_RDIV_MASK                      (0x7000U)
#define PLL_PLLDV_RDIV_SHIFT                     (12U)
#define PLL_PLLDV_RDIV_WIDTH                     (3U)
#define PLL_PLLDV_RDIV(x)                        (((uint32_t)(((uint32_t)(x)) << PLL_PLLDV_RDIV_SHIFT)) & PLL_PLLDV_RDIV_MASK)

#define PLL_PLLDV_ODIV2_MASK                     (0x7E000000U)
#define PLL_PLLDV_ODIV2_SHIFT                    (25U)
#define PLL_PLLDV_ODIV2_WIDTH                    (6U)
#define PLL_PLLDV_ODIV2(x)                       (((uint32_t)(((uint32_t)(x)) << PLL_PLLDV_ODIV2_SHIFT)) & PLL_PLLDV_ODIV2_MASK)
/*! @} */

/*! @name PLLFM - PLL Frequency Modulation */
/*! @{ */

#define PLL_PLLFM_STEPNO_MASK                    (0x7FFU)
#define PLL_PLLFM_STEPNO_SHIFT                   (0U)
#define PLL_PLLFM_STEPNO_WIDTH                   (11U)
#define PLL_PLLFM_STEPNO(x)                      (((uint32_t)(((uint32_t)(x)) << PLL_PLLFM_STEPNO_SHIFT)) & PLL_PLLFM_STEPNO_MASK)

#define PLL_PLLFM_STEPSIZE_MASK                  (0x3FF0000U)
#define PLL_PLLFM_STEPSIZE_SHIFT                 (16U)
#define PLL_PLLFM_STEPSIZE_WIDTH                 (10U)
#define PLL_PLLFM_STEPSIZE(x)                    (((uint32_t)(((uint32_t)(x)) << PLL_PLLFM_STEPSIZE_SHIFT)) & PLL_PLLFM_STEPSIZE_MASK)

#define PLL_PLLFM_SPREADCTL_MASK                 (0x20000000U)
#define PLL_PLLFM_SPREADCTL_SHIFT                (29U)
#define PLL_PLLFM_SPREADCTL_WIDTH                (1U)
#define PLL_PLLFM_SPREADCTL(x)                   (((uint32_t)(((uint32_t)(x)) << PLL_PLLFM_SPREADCTL_SHIFT)) & PLL_PLLFM_SPREADCTL_MASK)

#define PLL_PLLFM_SSCGBYP_MASK                   (0x40000000U)
#define PLL_PLLFM_SSCGBYP_SHIFT                  (30U)
#define PLL_PLLFM_SSCGBYP_WIDTH                  (1U)
#define PLL_PLLFM_SSCGBYP(x)                     (((uint32_t)(((uint32_t)(x)) << PLL_PLLFM_SSCGBYP_SHIFT)) & PLL_PLLFM_SSCGBYP_MASK)
/*! @} */

/*! @name PLLFD - PLL Fractional Divider */
/*! @{ */

#define PLL_PLLFD_MFN_MASK                       (0x7FFFU)
#define PLL_PLLFD_MFN_SHIFT                      (0U)
#define PLL_PLLFD_MFN_WIDTH                      (15U)
#define PLL_PLLFD_MFN(x)                         (((uint32_t)(((uint32_t)(x)) << PLL_PLLFD_MFN_SHIFT)) & PLL_PLLFD_MFN_MASK)

#define PLL_PLLFD_SDM3_MASK                      (0x10000000U)
#define PLL_PLLFD_SDM3_SHIFT                     (28U)
#define PLL_PLLFD_SDM3_WIDTH                     (1U)
#define PLL_PLLFD_SDM3(x)                        (((uint32_t)(((uint32_t)(x)) << PLL_PLLFD_SDM3_SHIFT)) & PLL_PLLFD_SDM3_MASK)

#define PLL_PLLFD_SDM2_MASK                      (0x20000000U)
#define PLL_PLLFD_SDM2_SHIFT                     (29U)
#define PLL_PLLFD_SDM2_WIDTH                     (1U)
#define PLL_PLLFD_SDM2(x)                        (((uint32_t)(((uint32_t)(x)) << PLL_PLLFD_SDM2_SHIFT)) & PLL_PLLFD_SDM2_MASK)

#define PLL_PLLFD_SDMEN_MASK                     (0x40000000U)
#define PLL_PLLFD_SDMEN_SHIFT                    (30U)
#define PLL_PLLFD_SDMEN_WIDTH                    (1U)
#define PLL_PLLFD_SDMEN(x)                       (((uint32_t)(((uint32_t)(x)) << PLL_PLLFD_SDMEN_SHIFT)) & PLL_PLLFD_SDMEN_MASK)
/*! @} */

/*! @name PLLCAL2 - PLL Calibration Register 2 */
/*! @{ */

#define PLL_PLLCAL2_ULKCTL_MASK                  (0x180U)
#define PLL_PLLCAL2_ULKCTL_SHIFT                 (7U)
#define PLL_PLLCAL2_ULKCTL_WIDTH                 (2U)
#define PLL_PLLCAL2_ULKCTL(x)                    (((uint32_t)(((uint32_t)(x)) << PLL_PLLCAL2_ULKCTL_SHIFT)) & PLL_PLLCAL2_ULKCTL_MASK)
/*! @} */

/*! @name PLLODIV - PLL Output Divider */
/*! @{ */

#define PLL_PLLODIV_DIV_MASK                     (0xF0000U)
#define PLL_PLLODIV_DIV_SHIFT                    (16U)
#define PLL_PLLODIV_DIV_WIDTH                    (4U)
#define PLL_PLLODIV_DIV(x)                       (((uint32_t)(((uint32_t)(x)) << PLL_PLLODIV_DIV_SHIFT)) & PLL_PLLODIV_DIV_MASK)

#define PLL_PLLODIV_DE_MASK                      (0x80000000U)
#define PLL_PLLODIV_DE_SHIFT                     (31U)
#define PLL_PLLODIV_DE_WIDTH                     (1U)
#define PLL_PLLODIV_DE(x)                        (((uint32_t)(((uint32_t)(x)) << PLL_PLLODIV_DE_SHIFT)) & PLL_PLLODIV_DE_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group PLL_Register_Masks */

/*!
 * @}
 */ /* end of group PLL_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_PLL_H_) */
