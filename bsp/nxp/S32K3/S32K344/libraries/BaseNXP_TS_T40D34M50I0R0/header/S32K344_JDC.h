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
 * @file S32K344_JDC.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_JDC
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
#if !defined(S32K344_JDC_H_)  /* Check if memory map has not been already included */
#define S32K344_JDC_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- JDC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup JDC_Peripheral_Access_Layer JDC Peripheral Access Layer
 * @{
 */

/** JDC - Register Layout Typedef */
typedef struct {
  __IO uint32_t MCR;                               /**< Module Configuration Register, offset: 0x0 */
  __IO uint32_t MSR;                               /**< Module Status Register, offset: 0x4 */
  __IO uint32_t JOUT_IPS;                          /**< JTAG Output Data Register, offset: 0x8 */
  __I  uint32_t JIN_IPS;                           /**< JTAG Input Data Register, offset: 0xC */
} JDC_Type, *JDC_MemMapPtr;

/** Number of instances of the JDC module. */
#define JDC_INSTANCE_COUNT                       (1u)

/* JDC - Peripheral instance base addresses */
/** Peripheral JDC base address */
#define IP_JDC_BASE                              (0x40394000u)
/** Peripheral JDC base pointer */
#define IP_JDC                                   ((JDC_Type *)IP_JDC_BASE)
/** Array initializer of JDC peripheral base addresses */
#define IP_JDC_BASE_ADDRS                        { IP_JDC_BASE }
/** Array initializer of JDC peripheral base pointers */
#define IP_JDC_BASE_PTRS                         { IP_JDC }

/* ----------------------------------------------------------------------------
   -- JDC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup JDC_Register_Masks JDC Register Masks
 * @{
 */

/*! @name MCR - Module Configuration Register */
/*! @{ */

#define JDC_MCR_JOUT_IEN_MASK                    (0x1U)
#define JDC_MCR_JOUT_IEN_SHIFT                   (0U)
#define JDC_MCR_JOUT_IEN_WIDTH                   (1U)
#define JDC_MCR_JOUT_IEN(x)                      (((uint32_t)(((uint32_t)(x)) << JDC_MCR_JOUT_IEN_SHIFT)) & JDC_MCR_JOUT_IEN_MASK)

#define JDC_MCR_JIN_IEN_MASK                     (0x10000U)
#define JDC_MCR_JIN_IEN_SHIFT                    (16U)
#define JDC_MCR_JIN_IEN_WIDTH                    (1U)
#define JDC_MCR_JIN_IEN(x)                       (((uint32_t)(((uint32_t)(x)) << JDC_MCR_JIN_IEN_SHIFT)) & JDC_MCR_JIN_IEN_MASK)
/*! @} */

/*! @name MSR - Module Status Register */
/*! @{ */

#define JDC_MSR_JOUT_INT_MASK                    (0x1U)
#define JDC_MSR_JOUT_INT_SHIFT                   (0U)
#define JDC_MSR_JOUT_INT_WIDTH                   (1U)
#define JDC_MSR_JOUT_INT(x)                      (((uint32_t)(((uint32_t)(x)) << JDC_MSR_JOUT_INT_SHIFT)) & JDC_MSR_JOUT_INT_MASK)

#define JDC_MSR_JOUT_RDY_MASK                    (0x4U)
#define JDC_MSR_JOUT_RDY_SHIFT                   (2U)
#define JDC_MSR_JOUT_RDY_WIDTH                   (1U)
#define JDC_MSR_JOUT_RDY(x)                      (((uint32_t)(((uint32_t)(x)) << JDC_MSR_JOUT_RDY_SHIFT)) & JDC_MSR_JOUT_RDY_MASK)

#define JDC_MSR_JIN_INT_MASK                     (0x10000U)
#define JDC_MSR_JIN_INT_SHIFT                    (16U)
#define JDC_MSR_JIN_INT_WIDTH                    (1U)
#define JDC_MSR_JIN_INT(x)                       (((uint32_t)(((uint32_t)(x)) << JDC_MSR_JIN_INT_SHIFT)) & JDC_MSR_JIN_INT_MASK)

#define JDC_MSR_JIN_RDY_MASK                     (0x40000U)
#define JDC_MSR_JIN_RDY_SHIFT                    (18U)
#define JDC_MSR_JIN_RDY_WIDTH                    (1U)
#define JDC_MSR_JIN_RDY(x)                       (((uint32_t)(((uint32_t)(x)) << JDC_MSR_JIN_RDY_SHIFT)) & JDC_MSR_JIN_RDY_MASK)
/*! @} */

/*! @name JOUT_IPS - JTAG Output Data Register */
/*! @{ */

#define JDC_JOUT_IPS_Data_MASK                   (0xFFFFFFFFU)
#define JDC_JOUT_IPS_Data_SHIFT                  (0U)
#define JDC_JOUT_IPS_Data_WIDTH                  (32U)
#define JDC_JOUT_IPS_Data(x)                     (((uint32_t)(((uint32_t)(x)) << JDC_JOUT_IPS_Data_SHIFT)) & JDC_JOUT_IPS_Data_MASK)
/*! @} */

/*! @name JIN_IPS - JTAG Input Data Register */
/*! @{ */

#define JDC_JIN_IPS_Data_MASK                    (0xFFFFFFFFU)
#define JDC_JIN_IPS_Data_SHIFT                   (0U)
#define JDC_JIN_IPS_Data_WIDTH                   (32U)
#define JDC_JIN_IPS_Data(x)                      (((uint32_t)(((uint32_t)(x)) << JDC_JIN_IPS_Data_SHIFT)) & JDC_JIN_IPS_Data_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group JDC_Register_Masks */

/*!
 * @}
 */ /* end of group JDC_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_JDC_H_) */
