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
 * @file S32K344_WKPU.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_WKPU
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
#if !defined(S32K344_WKPU_H_)  /* Check if memory map has not been already included */
#define S32K344_WKPU_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- WKPU Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup WKPU_Peripheral_Access_Layer WKPU Peripheral Access Layer
 * @{
 */

/** WKPU - Register Layout Typedef */
typedef struct {
  __IO uint32_t NSR;                               /**< NMI Status Flag Register, offset: 0x0 */
  uint8_t RESERVED_0[4];
  __IO uint32_t NCR;                               /**< NMI Configuration Register, offset: 0x8 */
  uint8_t RESERVED_1[8];
  __IO uint32_t WISR;                              /**< Wakeup/Interrupt Status Flag Register, offset: 0x14 */
  __IO uint32_t IRER;                              /**< Interrupt Request Enable Register, offset: 0x18 */
  __IO uint32_t WRER;                              /**< Wakeup Request Enable Register, offset: 0x1C */
  uint8_t RESERVED_2[8];
  __IO uint32_t WIREER;                            /**< Wakeup/Interrupt Rising-Edge Event Enable Register, offset: 0x28 */
  __IO uint32_t WIFEER;                            /**< Wakeup/Interrupt Falling-Edge Event Enable Register, offset: 0x2C */
  __IO uint32_t WIFER;                             /**< Wakeup/Interrupt Filter Enable Register, offset: 0x30 */
  uint8_t RESERVED_3[32];
  __IO uint32_t WISR_64;                           /**< Wakeup/Interrupt Status Flag Register, offset: 0x54 */
  __IO uint32_t IRER_64;                           /**< Interrupt Request Enable Register, offset: 0x58 */
  __IO uint32_t WRER_64;                           /**< Wakeup Request Enable Register, offset: 0x5C */
  uint8_t RESERVED_4[8];
  __IO uint32_t WIREER_64;                         /**< Wakeup/Interrupt Rising-Edge Event Enable Register, offset: 0x68 */
  __IO uint32_t WIFEER_64;                         /**< Wakeup/Interrupt Falling-Edge Event Enable Register, offset: 0x6C */
  __IO uint32_t WIFER_64;                          /**< Wakeup/Interrupt Filter Enable Register, offset: 0x70 */
} WKPU_Type, *WKPU_MemMapPtr;

/** Number of instances of the WKPU module. */
#define WKPU_INSTANCE_COUNT                      (1u)

/* WKPU - Peripheral instance base addresses */
/** Peripheral WKPU base address */
#define IP_WKPU_BASE                             (0x402B4000u)
/** Peripheral WKPU base pointer */
#define IP_WKPU                                  ((WKPU_Type *)IP_WKPU_BASE)
/** Array initializer of WKPU peripheral base addresses */
#define IP_WKPU_BASE_ADDRS                       { IP_WKPU_BASE }
/** Array initializer of WKPU peripheral base pointers */
#define IP_WKPU_BASE_PTRS                        { IP_WKPU }

/* ----------------------------------------------------------------------------
   -- WKPU Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup WKPU_Register_Masks WKPU Register Masks
 * @{
 */

/*! @name NSR - NMI Status Flag Register */
/*! @{ */

#define WKPU_NSR_NOVF1_MASK                      (0x400000U)
#define WKPU_NSR_NOVF1_SHIFT                     (22U)
#define WKPU_NSR_NOVF1_WIDTH                     (1U)
#define WKPU_NSR_NOVF1(x)                        (((uint32_t)(((uint32_t)(x)) << WKPU_NSR_NOVF1_SHIFT)) & WKPU_NSR_NOVF1_MASK)

#define WKPU_NSR_NIF1_MASK                       (0x800000U)
#define WKPU_NSR_NIF1_SHIFT                      (23U)
#define WKPU_NSR_NIF1_WIDTH                      (1U)
#define WKPU_NSR_NIF1(x)                         (((uint32_t)(((uint32_t)(x)) << WKPU_NSR_NIF1_SHIFT)) & WKPU_NSR_NIF1_MASK)

#define WKPU_NSR_NOVF0_MASK                      (0x40000000U)
#define WKPU_NSR_NOVF0_SHIFT                     (30U)
#define WKPU_NSR_NOVF0_WIDTH                     (1U)
#define WKPU_NSR_NOVF0(x)                        (((uint32_t)(((uint32_t)(x)) << WKPU_NSR_NOVF0_SHIFT)) & WKPU_NSR_NOVF0_MASK)

#define WKPU_NSR_NIF0_MASK                       (0x80000000U)
#define WKPU_NSR_NIF0_SHIFT                      (31U)
#define WKPU_NSR_NIF0_WIDTH                      (1U)
#define WKPU_NSR_NIF0(x)                         (((uint32_t)(((uint32_t)(x)) << WKPU_NSR_NIF0_SHIFT)) & WKPU_NSR_NIF0_MASK)
/*! @} */

/*! @name NCR - NMI Configuration Register */
/*! @{ */

#define WKPU_NCR_NFE1_MASK                       (0x10000U)
#define WKPU_NCR_NFE1_SHIFT                      (16U)
#define WKPU_NCR_NFE1_WIDTH                      (1U)
#define WKPU_NCR_NFE1(x)                         (((uint32_t)(((uint32_t)(x)) << WKPU_NCR_NFE1_SHIFT)) & WKPU_NCR_NFE1_MASK)

#define WKPU_NCR_NFEE1_MASK                      (0x20000U)
#define WKPU_NCR_NFEE1_SHIFT                     (17U)
#define WKPU_NCR_NFEE1_WIDTH                     (1U)
#define WKPU_NCR_NFEE1(x)                        (((uint32_t)(((uint32_t)(x)) << WKPU_NCR_NFEE1_SHIFT)) & WKPU_NCR_NFEE1_MASK)

#define WKPU_NCR_NREE1_MASK                      (0x40000U)
#define WKPU_NCR_NREE1_SHIFT                     (18U)
#define WKPU_NCR_NREE1_WIDTH                     (1U)
#define WKPU_NCR_NREE1(x)                        (((uint32_t)(((uint32_t)(x)) << WKPU_NCR_NREE1_SHIFT)) & WKPU_NCR_NREE1_MASK)

#define WKPU_NCR_NWRE1_MASK                      (0x100000U)
#define WKPU_NCR_NWRE1_SHIFT                     (20U)
#define WKPU_NCR_NWRE1_WIDTH                     (1U)
#define WKPU_NCR_NWRE1(x)                        (((uint32_t)(((uint32_t)(x)) << WKPU_NCR_NWRE1_SHIFT)) & WKPU_NCR_NWRE1_MASK)

#define WKPU_NCR_NDSS1_MASK                      (0x600000U)
#define WKPU_NCR_NDSS1_SHIFT                     (21U)
#define WKPU_NCR_NDSS1_WIDTH                     (2U)
#define WKPU_NCR_NDSS1(x)                        (((uint32_t)(((uint32_t)(x)) << WKPU_NCR_NDSS1_SHIFT)) & WKPU_NCR_NDSS1_MASK)

#define WKPU_NCR_NLOCK1_MASK                     (0x800000U)
#define WKPU_NCR_NLOCK1_SHIFT                    (23U)
#define WKPU_NCR_NLOCK1_WIDTH                    (1U)
#define WKPU_NCR_NLOCK1(x)                       (((uint32_t)(((uint32_t)(x)) << WKPU_NCR_NLOCK1_SHIFT)) & WKPU_NCR_NLOCK1_MASK)

#define WKPU_NCR_NFE0_MASK                       (0x1000000U)
#define WKPU_NCR_NFE0_SHIFT                      (24U)
#define WKPU_NCR_NFE0_WIDTH                      (1U)
#define WKPU_NCR_NFE0(x)                         (((uint32_t)(((uint32_t)(x)) << WKPU_NCR_NFE0_SHIFT)) & WKPU_NCR_NFE0_MASK)

#define WKPU_NCR_NFEE0_MASK                      (0x2000000U)
#define WKPU_NCR_NFEE0_SHIFT                     (25U)
#define WKPU_NCR_NFEE0_WIDTH                     (1U)
#define WKPU_NCR_NFEE0(x)                        (((uint32_t)(((uint32_t)(x)) << WKPU_NCR_NFEE0_SHIFT)) & WKPU_NCR_NFEE0_MASK)

#define WKPU_NCR_NREE0_MASK                      (0x4000000U)
#define WKPU_NCR_NREE0_SHIFT                     (26U)
#define WKPU_NCR_NREE0_WIDTH                     (1U)
#define WKPU_NCR_NREE0(x)                        (((uint32_t)(((uint32_t)(x)) << WKPU_NCR_NREE0_SHIFT)) & WKPU_NCR_NREE0_MASK)

#define WKPU_NCR_NWRE0_MASK                      (0x10000000U)
#define WKPU_NCR_NWRE0_SHIFT                     (28U)
#define WKPU_NCR_NWRE0_WIDTH                     (1U)
#define WKPU_NCR_NWRE0(x)                        (((uint32_t)(((uint32_t)(x)) << WKPU_NCR_NWRE0_SHIFT)) & WKPU_NCR_NWRE0_MASK)

#define WKPU_NCR_NDSS0_MASK                      (0x60000000U)
#define WKPU_NCR_NDSS0_SHIFT                     (29U)
#define WKPU_NCR_NDSS0_WIDTH                     (2U)
#define WKPU_NCR_NDSS0(x)                        (((uint32_t)(((uint32_t)(x)) << WKPU_NCR_NDSS0_SHIFT)) & WKPU_NCR_NDSS0_MASK)

#define WKPU_NCR_NLOCK0_MASK                     (0x80000000U)
#define WKPU_NCR_NLOCK0_SHIFT                    (31U)
#define WKPU_NCR_NLOCK0_WIDTH                    (1U)
#define WKPU_NCR_NLOCK0(x)                       (((uint32_t)(((uint32_t)(x)) << WKPU_NCR_NLOCK0_SHIFT)) & WKPU_NCR_NLOCK0_MASK)
/*! @} */

/*! @name WISR - Wakeup/Interrupt Status Flag Register */
/*! @{ */

#define WKPU_WISR_EIF_MASK                       (0xFFFFFFFFU)
#define WKPU_WISR_EIF_SHIFT                      (0U)
#define WKPU_WISR_EIF_WIDTH                      (32U)
#define WKPU_WISR_EIF(x)                         (((uint32_t)(((uint32_t)(x)) << WKPU_WISR_EIF_SHIFT)) & WKPU_WISR_EIF_MASK)
/*! @} */

/*! @name IRER - Interrupt Request Enable Register */
/*! @{ */

#define WKPU_IRER_EIRE_MASK                      (0xFFFFFFFFU)
#define WKPU_IRER_EIRE_SHIFT                     (0U)
#define WKPU_IRER_EIRE_WIDTH                     (32U)
#define WKPU_IRER_EIRE(x)                        (((uint32_t)(((uint32_t)(x)) << WKPU_IRER_EIRE_SHIFT)) & WKPU_IRER_EIRE_MASK)
/*! @} */

/*! @name WRER - Wakeup Request Enable Register */
/*! @{ */

#define WKPU_WRER_WRE_MASK                       (0xFFFFFFFFU)
#define WKPU_WRER_WRE_SHIFT                      (0U)
#define WKPU_WRER_WRE_WIDTH                      (32U)
#define WKPU_WRER_WRE(x)                         (((uint32_t)(((uint32_t)(x)) << WKPU_WRER_WRE_SHIFT)) & WKPU_WRER_WRE_MASK)
/*! @} */

/*! @name WIREER - Wakeup/Interrupt Rising-Edge Event Enable Register */
/*! @{ */

#define WKPU_WIREER_IREE_MASK                    (0xFFFFFFFFU)
#define WKPU_WIREER_IREE_SHIFT                   (0U)
#define WKPU_WIREER_IREE_WIDTH                   (32U)
#define WKPU_WIREER_IREE(x)                      (((uint32_t)(((uint32_t)(x)) << WKPU_WIREER_IREE_SHIFT)) & WKPU_WIREER_IREE_MASK)
/*! @} */

/*! @name WIFEER - Wakeup/Interrupt Falling-Edge Event Enable Register */
/*! @{ */

#define WKPU_WIFEER_IFEEx_MASK                   (0xFFFFFFFFU)
#define WKPU_WIFEER_IFEEx_SHIFT                  (0U)
#define WKPU_WIFEER_IFEEx_WIDTH                  (32U)
#define WKPU_WIFEER_IFEEx(x)                     (((uint32_t)(((uint32_t)(x)) << WKPU_WIFEER_IFEEx_SHIFT)) & WKPU_WIFEER_IFEEx_MASK)
/*! @} */

/*! @name WIFER - Wakeup/Interrupt Filter Enable Register */
/*! @{ */

#define WKPU_WIFER_IFE_MASK                      (0xFFFFFFFFU)
#define WKPU_WIFER_IFE_SHIFT                     (0U)
#define WKPU_WIFER_IFE_WIDTH                     (32U)
#define WKPU_WIFER_IFE(x)                        (((uint32_t)(((uint32_t)(x)) << WKPU_WIFER_IFE_SHIFT)) & WKPU_WIFER_IFE_MASK)
/*! @} */

/*! @name WISR_64 - Wakeup/Interrupt Status Flag Register */
/*! @{ */

#define WKPU_WISR_64_EIF_1_MASK                  (0xFFFFFFFFU)
#define WKPU_WISR_64_EIF_1_SHIFT                 (0U)
#define WKPU_WISR_64_EIF_1_WIDTH                 (32U)
#define WKPU_WISR_64_EIF_1(x)                    (((uint32_t)(((uint32_t)(x)) << WKPU_WISR_64_EIF_1_SHIFT)) & WKPU_WISR_64_EIF_1_MASK)
/*! @} */

/*! @name IRER_64 - Interrupt Request Enable Register */
/*! @{ */

#define WKPU_IRER_64_EIRE_1_MASK                 (0xFFFFFFFFU)
#define WKPU_IRER_64_EIRE_1_SHIFT                (0U)
#define WKPU_IRER_64_EIRE_1_WIDTH                (32U)
#define WKPU_IRER_64_EIRE_1(x)                   (((uint32_t)(((uint32_t)(x)) << WKPU_IRER_64_EIRE_1_SHIFT)) & WKPU_IRER_64_EIRE_1_MASK)
/*! @} */

/*! @name WRER_64 - Wakeup Request Enable Register */
/*! @{ */

#define WKPU_WRER_64_WRE_1_MASK                  (0xFFFFFFFFU)
#define WKPU_WRER_64_WRE_1_SHIFT                 (0U)
#define WKPU_WRER_64_WRE_1_WIDTH                 (32U)
#define WKPU_WRER_64_WRE_1(x)                    (((uint32_t)(((uint32_t)(x)) << WKPU_WRER_64_WRE_1_SHIFT)) & WKPU_WRER_64_WRE_1_MASK)
/*! @} */

/*! @name WIREER_64 - Wakeup/Interrupt Rising-Edge Event Enable Register */
/*! @{ */

#define WKPU_WIREER_64_IREE_1_MASK               (0xFFFFFFFFU)
#define WKPU_WIREER_64_IREE_1_SHIFT              (0U)
#define WKPU_WIREER_64_IREE_1_WIDTH              (32U)
#define WKPU_WIREER_64_IREE_1(x)                 (((uint32_t)(((uint32_t)(x)) << WKPU_WIREER_64_IREE_1_SHIFT)) & WKPU_WIREER_64_IREE_1_MASK)
/*! @} */

/*! @name WIFEER_64 - Wakeup/Interrupt Falling-Edge Event Enable Register */
/*! @{ */

#define WKPU_WIFEER_64_IFEEx_1_MASK              (0xFFFFFFFFU)
#define WKPU_WIFEER_64_IFEEx_1_SHIFT             (0U)
#define WKPU_WIFEER_64_IFEEx_1_WIDTH             (32U)
#define WKPU_WIFEER_64_IFEEx_1(x)                (((uint32_t)(((uint32_t)(x)) << WKPU_WIFEER_64_IFEEx_1_SHIFT)) & WKPU_WIFEER_64_IFEEx_1_MASK)
/*! @} */

/*! @name WIFER_64 - Wakeup/Interrupt Filter Enable Register */
/*! @{ */

#define WKPU_WIFER_64_IFE_1_MASK                 (0xFFFFFFFFU)
#define WKPU_WIFER_64_IFE_1_SHIFT                (0U)
#define WKPU_WIFER_64_IFE_1_WIDTH                (32U)
#define WKPU_WIFER_64_IFE_1(x)                   (((uint32_t)(((uint32_t)(x)) << WKPU_WIFER_64_IFE_1_SHIFT)) & WKPU_WIFER_64_IFE_1_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group WKPU_Register_Masks */

/*!
 * @}
 */ /* end of group WKPU_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_WKPU_H_) */
