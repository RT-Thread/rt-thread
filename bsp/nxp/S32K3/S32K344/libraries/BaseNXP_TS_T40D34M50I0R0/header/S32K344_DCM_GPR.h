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
 * @file S32K344_DCM_GPR.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_DCM_GPR
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
#if !defined(S32K344_DCM_GPR_H_)  /* Check if memory map has not been already included */
#define S32K344_DCM_GPR_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- DCM_GPR Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DCM_GPR_Peripheral_Access_Layer DCM_GPR Peripheral Access Layer
 * @{
 */

/** DCM_GPR - Register Layout Typedef */
typedef struct {
  uint8_t RESERVED_0[512];
  __IO uint32_t DCMROD1;                           /**< Read Only GPR On Destructive Reset Register, offset: 0x200 */
  uint8_t RESERVED_1[4];
  __IO uint32_t DCMROD3;                           /**< Read Only GPR On Destructive Reset Register, offset: 0x208 */
  __IO uint32_t DCMROD4;                           /**< Read Only GPR On Destructive Reset Register, offset: 0x20C */
  __IO uint32_t DCMROD5;                           /**< Read Only GPR On Destructive Reset Register, offset: 0x210 */
  uint8_t RESERVED_2[236];
  __IO uint32_t DCMROF1;                           /**< Read Only GPR On Functional Reset Register, offset: 0x300 */
  __IO uint32_t DCMROF2;                           /**< Read Only GPR On Functional Reset Register, offset: 0x304 */
  __IO uint32_t DCMROF3;                           /**< Read Only GPR On Functional Reset Register, offset: 0x308 */
  __IO uint32_t DCMROF4;                           /**< Read Only GPR On Functional Reset Register, offset: 0x30C */
  __IO uint32_t DCMROF5;                           /**< Read Only GPR On Functional Reset Register, offset: 0x310 */
  __IO uint32_t DCMROF6;                           /**< Read Only GPR On Functional Reset Register, offset: 0x314 */
  __IO uint32_t DCMROF7;                           /**< Read Only GPR On Functional Reset Register, offset: 0x318 */
  __IO uint32_t DCMROF8;                           /**< Read Only GPR On Functional Reset Register, offset: 0x31C */
  __IO uint32_t DCMROF9;                           /**< Read Only GPR On Functional Reset Register, offset: 0x320 */
  __IO uint32_t DCMROF10;                          /**< Read Only GPR On Functional Reset Register, offset: 0x324 */
  __IO uint32_t DCMROF11;                          /**< Read Only GPR On Functional Reset Register, offset: 0x328 */
  __IO uint32_t DCMROF12;                          /**< Read Only GPR On Functional Reset Register, offset: 0x32C */
  __IO uint32_t DCMROF13;                          /**< Read Only GPR On Functional Reset Register, offset: 0x330 */
  __IO uint32_t DCMROF14;                          /**< Read Only GPR On Functional Reset Register, offset: 0x334 */
  __IO uint32_t DCMROF15;                          /**< Read Only GPR On Functional Reset Register, offset: 0x338 */
  __IO uint32_t DCMROF16;                          /**< Read Only GPR On Functional Reset Register, offset: 0x33C */
  __IO uint32_t DCMROF17;                          /**< Read Only GPR On Functional Reset Register, offset: 0x340 */
  uint8_t RESERVED_3[4];
  __I  uint32_t DCMROF19;                          /**< Read Only GPR On Functional Reset Register, offset: 0x348 */
  __I  uint32_t DCMROF20;                          /**< Read Only GPR On Functional Reset Register, offset: 0x34C */
  __I  uint32_t DCMROF21;                          /**< Read Only GPR On Functional Reset Register, offset: 0x350 */
  uint8_t RESERVED_4[172];
  __IO uint32_t DCMRWP1;                           /**< Read Write GPR On Power On Reset Register, offset: 0x400 */
  uint8_t RESERVED_5[4];
  __IO uint32_t DCMRWP3;                           /**< Read Write GPR On Power On Reset Register, offset: 0x408 */
  uint8_t RESERVED_6[248];
  __IO uint32_t DCMRWD2;                           /**< Read Write GPR On Destructive Reset Register, offset: 0x504 */
  __IO uint32_t DCMRWD3;                           /**< Read Write GPR On Destructive Reset Register, offset: 0x508 */
  __IO uint32_t DCMRWD4;                           /**< Read Write GPR On Destructive Reset Register, offset: 0x50C */
  __IO uint32_t DCMRWD5;                           /**< Read Write GPR On Destructive Reset Register, offset: 0x510 */
  __IO uint32_t DCMRWD6;                           /**< Read Write GPR On Destructive Reset Register, offset: 0x514 */
       uint32_t DCMRWD7;                           /**< Read Write GPR On Destructive Reset Register, offset: 0x518 */
       uint32_t DCMRWD8;                           /**< Read Write GPR On Destructive Reset Register, offset: 0x51C */
       uint32_t DCMRWD9;                           /**< Read Write GPR On Destructive Reset Register, offset: 0x520 */
  uint8_t RESERVED_7[220];
  __IO uint32_t DCMRWF1;                           /**< Read Write GPR On Functional Reset Register, offset: 0x600 */
  __IO uint32_t DCMRWF2;                           /**< Read Write GPR On Functional Reset Register, offset: 0x604 */
  uint8_t RESERVED_8[4];
  __IO uint32_t DCMRWF4;                           /**< Read Write GPR On Functional Reset Register, offset: 0x60C */
  __IO uint32_t DCMRWF5;                           /**< Read Write GPR On Functional Reset Register, offset: 0x610 */
  uint8_t RESERVED_9[236];
  __IO uint32_t DCMROPP1;                          /**< Read Only GPR On PMCPOR Reset, offset: 0x700 */
  __IO uint32_t DCMROPP2;                          /**< Read Only GPR On PMCPOR Reset, offset: 0x704 */
  __IO uint32_t DCMROPP3;                          /**< Read Only GPR On PMCPOR Reset, offset: 0x708 */
  __IO uint32_t DCMROPP4;                          /**< Read Only GPR On PMCPOR Reset, offset: 0x70C */
} DCM_GPR_Type, *DCM_GPR_MemMapPtr;

/** Number of instances of the DCM_GPR module. */
#define DCM_GPR_INSTANCE_COUNT                   (1u)

/* DCM_GPR - Peripheral instance base addresses */
/** Peripheral DCM_GPR base address */
#define IP_DCM_GPR_BASE                          (0x402AC000u)
/** Peripheral DCM_GPR base pointer */
#define IP_DCM_GPR                               ((DCM_GPR_Type *)IP_DCM_GPR_BASE)
/** Array initializer of DCM_GPR peripheral base addresses */
#define IP_DCM_GPR_BASE_ADDRS                    { IP_DCM_GPR_BASE }
/** Array initializer of DCM_GPR peripheral base pointers */
#define IP_DCM_GPR_BASE_PTRS                     { IP_DCM_GPR }

/* ----------------------------------------------------------------------------
   -- DCM_GPR Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DCM_GPR_Register_Masks DCM_GPR Register Masks
 * @{
 */

/*! @name DCMROD1 - Read Only GPR On Destructive Reset Register */
/*! @{ */

#define DCM_GPR_DCMROD1_PCU_ISO_STATUS_MASK      (0x1U)
#define DCM_GPR_DCMROD1_PCU_ISO_STATUS_SHIFT     (0U)
#define DCM_GPR_DCMROD1_PCU_ISO_STATUS_WIDTH     (1U)
#define DCM_GPR_DCMROD1_PCU_ISO_STATUS(x)        (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD1_PCU_ISO_STATUS_SHIFT)) & DCM_GPR_DCMROD1_PCU_ISO_STATUS_MASK)

#define DCM_GPR_DCMROD1_HSE_DCF_VIO_MASK         (0x2U)
#define DCM_GPR_DCMROD1_HSE_DCF_VIO_SHIFT        (1U)
#define DCM_GPR_DCMROD1_HSE_DCF_VIO_WIDTH        (1U)
#define DCM_GPR_DCMROD1_HSE_DCF_VIO(x)           (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD1_HSE_DCF_VIO_SHIFT)) & DCM_GPR_DCMROD1_HSE_DCF_VIO_MASK)

#define DCM_GPR_DCMROD1_KEY_RESP_READY_MASK      (0x4U)
#define DCM_GPR_DCMROD1_KEY_RESP_READY_SHIFT     (2U)
#define DCM_GPR_DCMROD1_KEY_RESP_READY_WIDTH     (1U)
#define DCM_GPR_DCMROD1_KEY_RESP_READY(x)        (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD1_KEY_RESP_READY_SHIFT)) & DCM_GPR_DCMROD1_KEY_RESP_READY_MASK)
/*! @} */

/*! @name DCMROD3 - Read Only GPR On Destructive Reset Register */
/*! @{ */

#define DCM_GPR_DCMROD3_CM7_0_LOCKUP_MASK        (0x1U)
#define DCM_GPR_DCMROD3_CM7_0_LOCKUP_SHIFT       (0U)
#define DCM_GPR_DCMROD3_CM7_0_LOCKUP_WIDTH       (1U)
#define DCM_GPR_DCMROD3_CM7_0_LOCKUP(x)          (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD3_CM7_0_LOCKUP_SHIFT)) & DCM_GPR_DCMROD3_CM7_0_LOCKUP_MASK)

#define DCM_GPR_DCMROD3_HSE_LOCKUP_MASK          (0x4U)
#define DCM_GPR_DCMROD3_HSE_LOCKUP_SHIFT         (2U)
#define DCM_GPR_DCMROD3_HSE_LOCKUP_WIDTH         (1U)
#define DCM_GPR_DCMROD3_HSE_LOCKUP(x)            (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD3_HSE_LOCKUP_SHIFT)) & DCM_GPR_DCMROD3_HSE_LOCKUP_MASK)

#define DCM_GPR_DCMROD3_CM7_RCCU1_ALARM_MASK     (0x8U)
#define DCM_GPR_DCMROD3_CM7_RCCU1_ALARM_SHIFT    (3U)
#define DCM_GPR_DCMROD3_CM7_RCCU1_ALARM_WIDTH    (1U)
#define DCM_GPR_DCMROD3_CM7_RCCU1_ALARM(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD3_CM7_RCCU1_ALARM_SHIFT)) & DCM_GPR_DCMROD3_CM7_RCCU1_ALARM_MASK)

#define DCM_GPR_DCMROD3_CM7_RCCU2_ALARM_MASK     (0x10U)
#define DCM_GPR_DCMROD3_CM7_RCCU2_ALARM_SHIFT    (4U)
#define DCM_GPR_DCMROD3_CM7_RCCU2_ALARM_WIDTH    (1U)
#define DCM_GPR_DCMROD3_CM7_RCCU2_ALARM(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD3_CM7_RCCU2_ALARM_SHIFT)) & DCM_GPR_DCMROD3_CM7_RCCU2_ALARM_MASK)

#define DCM_GPR_DCMROD3_TCM_GSKT_ALARM_MASK      (0x20U)
#define DCM_GPR_DCMROD3_TCM_GSKT_ALARM_SHIFT     (5U)
#define DCM_GPR_DCMROD3_TCM_GSKT_ALARM_WIDTH     (1U)
#define DCM_GPR_DCMROD3_TCM_GSKT_ALARM(x)        (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD3_TCM_GSKT_ALARM_SHIFT)) & DCM_GPR_DCMROD3_TCM_GSKT_ALARM_MASK)

#define DCM_GPR_DCMROD3_DMA_SYS_GSKT_ALARM_MASK  (0x40U)
#define DCM_GPR_DCMROD3_DMA_SYS_GSKT_ALARM_SHIFT (6U)
#define DCM_GPR_DCMROD3_DMA_SYS_GSKT_ALARM_WIDTH (1U)
#define DCM_GPR_DCMROD3_DMA_SYS_GSKT_ALARM(x)    (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD3_DMA_SYS_GSKT_ALARM_SHIFT)) & DCM_GPR_DCMROD3_DMA_SYS_GSKT_ALARM_MASK)

#define DCM_GPR_DCMROD3_DMA_PERIPH_GSKT_ALARM_MASK (0x80U)
#define DCM_GPR_DCMROD3_DMA_PERIPH_GSKT_ALARM_SHIFT (7U)
#define DCM_GPR_DCMROD3_DMA_PERIPH_GSKT_ALARM_WIDTH (1U)
#define DCM_GPR_DCMROD3_DMA_PERIPH_GSKT_ALARM(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD3_DMA_PERIPH_GSKT_ALARM_SHIFT)) & DCM_GPR_DCMROD3_DMA_PERIPH_GSKT_ALARM_MASK)

#define DCM_GPR_DCMROD3_SYS_AXBS_ALARM_MASK      (0x100U)
#define DCM_GPR_DCMROD3_SYS_AXBS_ALARM_SHIFT     (8U)
#define DCM_GPR_DCMROD3_SYS_AXBS_ALARM_WIDTH     (1U)
#define DCM_GPR_DCMROD3_SYS_AXBS_ALARM(x)        (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD3_SYS_AXBS_ALARM_SHIFT)) & DCM_GPR_DCMROD3_SYS_AXBS_ALARM_MASK)

#define DCM_GPR_DCMROD3_DMA_AXBS_ALARM_MASK      (0x200U)
#define DCM_GPR_DCMROD3_DMA_AXBS_ALARM_SHIFT     (9U)
#define DCM_GPR_DCMROD3_DMA_AXBS_ALARM_WIDTH     (1U)
#define DCM_GPR_DCMROD3_DMA_AXBS_ALARM(x)        (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD3_DMA_AXBS_ALARM_SHIFT)) & DCM_GPR_DCMROD3_DMA_AXBS_ALARM_MASK)

#define DCM_GPR_DCMROD3_HSE_GSKT_ALARM_MASK      (0x800U)
#define DCM_GPR_DCMROD3_HSE_GSKT_ALARM_SHIFT     (11U)
#define DCM_GPR_DCMROD3_HSE_GSKT_ALARM_WIDTH     (1U)
#define DCM_GPR_DCMROD3_HSE_GSKT_ALARM(x)        (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD3_HSE_GSKT_ALARM_SHIFT)) & DCM_GPR_DCMROD3_HSE_GSKT_ALARM_MASK)

#define DCM_GPR_DCMROD3_QSPI_GSKT_ALARM_MASK     (0x1000U)
#define DCM_GPR_DCMROD3_QSPI_GSKT_ALARM_SHIFT    (12U)
#define DCM_GPR_DCMROD3_QSPI_GSKT_ALARM_WIDTH    (1U)
#define DCM_GPR_DCMROD3_QSPI_GSKT_ALARM(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD3_QSPI_GSKT_ALARM_SHIFT)) & DCM_GPR_DCMROD3_QSPI_GSKT_ALARM_MASK)

#define DCM_GPR_DCMROD3_AIPS1_GSKT_ALARM_MASK    (0x2000U)
#define DCM_GPR_DCMROD3_AIPS1_GSKT_ALARM_SHIFT   (13U)
#define DCM_GPR_DCMROD3_AIPS1_GSKT_ALARM_WIDTH   (1U)
#define DCM_GPR_DCMROD3_AIPS1_GSKT_ALARM(x)      (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD3_AIPS1_GSKT_ALARM_SHIFT)) & DCM_GPR_DCMROD3_AIPS1_GSKT_ALARM_MASK)

#define DCM_GPR_DCMROD3_AIPS2_GSKT_ALARM_MASK    (0x4000U)
#define DCM_GPR_DCMROD3_AIPS2_GSKT_ALARM_SHIFT   (14U)
#define DCM_GPR_DCMROD3_AIPS2_GSKT_ALARM_WIDTH   (1U)
#define DCM_GPR_DCMROD3_AIPS2_GSKT_ALARM(x)      (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD3_AIPS2_GSKT_ALARM_SHIFT)) & DCM_GPR_DCMROD3_AIPS2_GSKT_ALARM_MASK)

#define DCM_GPR_DCMROD3_ADDR_EDC_ERR_MASK        (0x8000U)
#define DCM_GPR_DCMROD3_ADDR_EDC_ERR_SHIFT       (15U)
#define DCM_GPR_DCMROD3_ADDR_EDC_ERR_WIDTH       (1U)
#define DCM_GPR_DCMROD3_ADDR_EDC_ERR(x)          (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD3_ADDR_EDC_ERR_SHIFT)) & DCM_GPR_DCMROD3_ADDR_EDC_ERR_MASK)

#define DCM_GPR_DCMROD3_DATA_EDC_ERR_MASK        (0x10000U)
#define DCM_GPR_DCMROD3_DATA_EDC_ERR_SHIFT       (16U)
#define DCM_GPR_DCMROD3_DATA_EDC_ERR_WIDTH       (1U)
#define DCM_GPR_DCMROD3_DATA_EDC_ERR(x)          (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD3_DATA_EDC_ERR_SHIFT)) & DCM_GPR_DCMROD3_DATA_EDC_ERR_MASK)

#define DCM_GPR_DCMROD3_TCM_AXBS_ALARM_MASK      (0x20000U)
#define DCM_GPR_DCMROD3_TCM_AXBS_ALARM_SHIFT     (17U)
#define DCM_GPR_DCMROD3_TCM_AXBS_ALARM_WIDTH     (1U)
#define DCM_GPR_DCMROD3_TCM_AXBS_ALARM(x)        (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD3_TCM_AXBS_ALARM_SHIFT)) & DCM_GPR_DCMROD3_TCM_AXBS_ALARM_MASK)

#define DCM_GPR_DCMROD3_MAC_GSKT_ALARM_MASK     (0x40000U)
#define DCM_GPR_DCMROD3_MAC_GSKT_ALARM_SHIFT    (18U)
#define DCM_GPR_DCMROD3_MAC_GSKT_ALARM_WIDTH    (1U)
#define DCM_GPR_DCMROD3_MAC_GSKT_ALARM(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD3_MAC_GSKT_ALARM_SHIFT)) & DCM_GPR_DCMROD3_MAC_GSKT_ALARM_MASK)

#define DCM_GPR_DCMROD3_PERIPH_AXBS_ALARM_MASK   (0x80000U)
#define DCM_GPR_DCMROD3_PERIPH_AXBS_ALARM_SHIFT  (19U)
#define DCM_GPR_DCMROD3_PERIPH_AXBS_ALARM_WIDTH  (1U)
#define DCM_GPR_DCMROD3_PERIPH_AXBS_ALARM(x)     (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD3_PERIPH_AXBS_ALARM_SHIFT)) & DCM_GPR_DCMROD3_PERIPH_AXBS_ALARM_MASK)

#define DCM_GPR_DCMROD3_LC_ERR_MASK              (0x400000U)
#define DCM_GPR_DCMROD3_LC_ERR_SHIFT             (22U)
#define DCM_GPR_DCMROD3_LC_ERR_WIDTH             (1U)
#define DCM_GPR_DCMROD3_LC_ERR(x)                (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD3_LC_ERR_SHIFT)) & DCM_GPR_DCMROD3_LC_ERR_MASK)

#define DCM_GPR_DCMROD3_PRAM1_ECC_ERR_MASK       (0x1000000U)
#define DCM_GPR_DCMROD3_PRAM1_ECC_ERR_SHIFT      (24U)
#define DCM_GPR_DCMROD3_PRAM1_ECC_ERR_WIDTH      (1U)
#define DCM_GPR_DCMROD3_PRAM1_ECC_ERR(x)         (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD3_PRAM1_ECC_ERR_SHIFT)) & DCM_GPR_DCMROD3_PRAM1_ECC_ERR_MASK)

#define DCM_GPR_DCMROD3_PRAM0_ECC_ERR_MASK       (0x2000000U)
#define DCM_GPR_DCMROD3_PRAM0_ECC_ERR_SHIFT      (25U)
#define DCM_GPR_DCMROD3_PRAM0_ECC_ERR_WIDTH      (1U)
#define DCM_GPR_DCMROD3_PRAM0_ECC_ERR(x)         (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD3_PRAM0_ECC_ERR_SHIFT)) & DCM_GPR_DCMROD3_PRAM0_ECC_ERR_MASK)

#define DCM_GPR_DCMROD3_CM7_0_DCDATA_ECC_ERR_MASK (0x4000000U)
#define DCM_GPR_DCMROD3_CM7_0_DCDATA_ECC_ERR_SHIFT (26U)
#define DCM_GPR_DCMROD3_CM7_0_DCDATA_ECC_ERR_WIDTH (1U)
#define DCM_GPR_DCMROD3_CM7_0_DCDATA_ECC_ERR(x)  (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD3_CM7_0_DCDATA_ECC_ERR_SHIFT)) & DCM_GPR_DCMROD3_CM7_0_DCDATA_ECC_ERR_MASK)

#define DCM_GPR_DCMROD3_CM7_0_DCTAG_ECC_ERR_MASK (0x10000000U)
#define DCM_GPR_DCMROD3_CM7_0_DCTAG_ECC_ERR_SHIFT (28U)
#define DCM_GPR_DCMROD3_CM7_0_DCTAG_ECC_ERR_WIDTH (1U)
#define DCM_GPR_DCMROD3_CM7_0_DCTAG_ECC_ERR(x)   (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD3_CM7_0_DCTAG_ECC_ERR_SHIFT)) & DCM_GPR_DCMROD3_CM7_0_DCTAG_ECC_ERR_MASK)

#define DCM_GPR_DCMROD3_CM7_0_ICDATA_ECC_ERR_MASK (0x40000000U)
#define DCM_GPR_DCMROD3_CM7_0_ICDATA_ECC_ERR_SHIFT (30U)
#define DCM_GPR_DCMROD3_CM7_0_ICDATA_ECC_ERR_WIDTH (1U)
#define DCM_GPR_DCMROD3_CM7_0_ICDATA_ECC_ERR(x)  (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD3_CM7_0_ICDATA_ECC_ERR_SHIFT)) & DCM_GPR_DCMROD3_CM7_0_ICDATA_ECC_ERR_MASK)
/*! @} */

/*! @name DCMROD4 - Read Only GPR On Destructive Reset Register */
/*! @{ */

#define DCM_GPR_DCMROD4_CM7_0_ICTAG_ECC_ERR_MASK (0x1U)
#define DCM_GPR_DCMROD4_CM7_0_ICTAG_ECC_ERR_SHIFT (0U)
#define DCM_GPR_DCMROD4_CM7_0_ICTAG_ECC_ERR_WIDTH (1U)
#define DCM_GPR_DCMROD4_CM7_0_ICTAG_ECC_ERR(x)   (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD4_CM7_0_ICTAG_ECC_ERR_SHIFT)) & DCM_GPR_DCMROD4_CM7_0_ICTAG_ECC_ERR_MASK)

#define DCM_GPR_DCMROD4_CM7_0_ITCM_ECC_ERR_MASK  (0x4U)
#define DCM_GPR_DCMROD4_CM7_0_ITCM_ECC_ERR_SHIFT (2U)
#define DCM_GPR_DCMROD4_CM7_0_ITCM_ECC_ERR_WIDTH (1U)
#define DCM_GPR_DCMROD4_CM7_0_ITCM_ECC_ERR(x)    (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD4_CM7_0_ITCM_ECC_ERR_SHIFT)) & DCM_GPR_DCMROD4_CM7_0_ITCM_ECC_ERR_MASK)

#define DCM_GPR_DCMROD4_CM7_0_DTCM0_ECC_ERR_MASK (0x8U)
#define DCM_GPR_DCMROD4_CM7_0_DTCM0_ECC_ERR_SHIFT (3U)
#define DCM_GPR_DCMROD4_CM7_0_DTCM0_ECC_ERR_WIDTH (1U)
#define DCM_GPR_DCMROD4_CM7_0_DTCM0_ECC_ERR(x)   (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD4_CM7_0_DTCM0_ECC_ERR_SHIFT)) & DCM_GPR_DCMROD4_CM7_0_DTCM0_ECC_ERR_MASK)

#define DCM_GPR_DCMROD4_CM7_0_DTCM1_ECC_ERR_MASK (0x10U)
#define DCM_GPR_DCMROD4_CM7_0_DTCM1_ECC_ERR_SHIFT (4U)
#define DCM_GPR_DCMROD4_CM7_0_DTCM1_ECC_ERR_WIDTH (1U)
#define DCM_GPR_DCMROD4_CM7_0_DTCM1_ECC_ERR(x)   (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD4_CM7_0_DTCM1_ECC_ERR_SHIFT)) & DCM_GPR_DCMROD4_CM7_0_DTCM1_ECC_ERR_MASK)

#define DCM_GPR_DCMROD4_CM7_1_ITCM_ECC_ERR_MASK  (0x20U)
#define DCM_GPR_DCMROD4_CM7_1_ITCM_ECC_ERR_SHIFT (5U)
#define DCM_GPR_DCMROD4_CM7_1_ITCM_ECC_ERR_WIDTH (1U)
#define DCM_GPR_DCMROD4_CM7_1_ITCM_ECC_ERR(x)    (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD4_CM7_1_ITCM_ECC_ERR_SHIFT)) & DCM_GPR_DCMROD4_CM7_1_ITCM_ECC_ERR_MASK)

#define DCM_GPR_DCMROD4_CM7_1_DTCM0_ECC_ERR_MASK (0x40U)
#define DCM_GPR_DCMROD4_CM7_1_DTCM0_ECC_ERR_SHIFT (6U)
#define DCM_GPR_DCMROD4_CM7_1_DTCM0_ECC_ERR_WIDTH (1U)
#define DCM_GPR_DCMROD4_CM7_1_DTCM0_ECC_ERR(x)   (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD4_CM7_1_DTCM0_ECC_ERR_SHIFT)) & DCM_GPR_DCMROD4_CM7_1_DTCM0_ECC_ERR_MASK)

#define DCM_GPR_DCMROD4_CM7_1_DTCM1_ECC_ERR_MASK (0x80U)
#define DCM_GPR_DCMROD4_CM7_1_DTCM1_ECC_ERR_SHIFT (7U)
#define DCM_GPR_DCMROD4_CM7_1_DTCM1_ECC_ERR_WIDTH (1U)
#define DCM_GPR_DCMROD4_CM7_1_DTCM1_ECC_ERR(x)   (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD4_CM7_1_DTCM1_ECC_ERR_SHIFT)) & DCM_GPR_DCMROD4_CM7_1_DTCM1_ECC_ERR_MASK)

#define DCM_GPR_DCMROD4_DMA_TCD_RAM_ECC_ERR_MASK (0x100U)
#define DCM_GPR_DCMROD4_DMA_TCD_RAM_ECC_ERR_SHIFT (8U)
#define DCM_GPR_DCMROD4_DMA_TCD_RAM_ECC_ERR_WIDTH (1U)
#define DCM_GPR_DCMROD4_DMA_TCD_RAM_ECC_ERR(x)   (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD4_DMA_TCD_RAM_ECC_ERR_SHIFT)) & DCM_GPR_DCMROD4_DMA_TCD_RAM_ECC_ERR_MASK)

#define DCM_GPR_DCMROD4_PRAM0_FCCU_ALARM_MASK    (0x200U)
#define DCM_GPR_DCMROD4_PRAM0_FCCU_ALARM_SHIFT   (9U)
#define DCM_GPR_DCMROD4_PRAM0_FCCU_ALARM_WIDTH   (1U)
#define DCM_GPR_DCMROD4_PRAM0_FCCU_ALARM(x)      (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD4_PRAM0_FCCU_ALARM_SHIFT)) & DCM_GPR_DCMROD4_PRAM0_FCCU_ALARM_MASK)

#define DCM_GPR_DCMROD4_PRAM1_FCCU_ALARM_MASK    (0x400U)
#define DCM_GPR_DCMROD4_PRAM1_FCCU_ALARM_SHIFT   (10U)
#define DCM_GPR_DCMROD4_PRAM1_FCCU_ALARM_WIDTH   (1U)
#define DCM_GPR_DCMROD4_PRAM1_FCCU_ALARM(x)      (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD4_PRAM1_FCCU_ALARM_SHIFT)) & DCM_GPR_DCMROD4_PRAM1_FCCU_ALARM_MASK)

#define DCM_GPR_DCMROD4_HSE_RAM_ECC_ERR_MASK     (0x800U)
#define DCM_GPR_DCMROD4_HSE_RAM_ECC_ERR_SHIFT    (11U)
#define DCM_GPR_DCMROD4_HSE_RAM_ECC_ERR_WIDTH    (1U)
#define DCM_GPR_DCMROD4_HSE_RAM_ECC_ERR(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD4_HSE_RAM_ECC_ERR_SHIFT)) & DCM_GPR_DCMROD4_HSE_RAM_ECC_ERR_MASK)

#define DCM_GPR_DCMROD4_PF0_CODE_ECC_ERR_MASK    (0x1000U)
#define DCM_GPR_DCMROD4_PF0_CODE_ECC_ERR_SHIFT   (12U)
#define DCM_GPR_DCMROD4_PF0_CODE_ECC_ERR_WIDTH   (1U)
#define DCM_GPR_DCMROD4_PF0_CODE_ECC_ERR(x)      (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD4_PF0_CODE_ECC_ERR_SHIFT)) & DCM_GPR_DCMROD4_PF0_CODE_ECC_ERR_MASK)

#define DCM_GPR_DCMROD4_PF0_DATA_ECC_ERR_MASK    (0x2000U)
#define DCM_GPR_DCMROD4_PF0_DATA_ECC_ERR_SHIFT   (13U)
#define DCM_GPR_DCMROD4_PF0_DATA_ECC_ERR_WIDTH   (1U)
#define DCM_GPR_DCMROD4_PF0_DATA_ECC_ERR(x)      (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD4_PF0_DATA_ECC_ERR_SHIFT)) & DCM_GPR_DCMROD4_PF0_DATA_ECC_ERR_MASK)

#define DCM_GPR_DCMROD4_PF1_CODE_ECC_ERR_MASK    (0x4000U)
#define DCM_GPR_DCMROD4_PF1_CODE_ECC_ERR_SHIFT   (14U)
#define DCM_GPR_DCMROD4_PF1_CODE_ECC_ERR_WIDTH   (1U)
#define DCM_GPR_DCMROD4_PF1_CODE_ECC_ERR(x)      (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD4_PF1_CODE_ECC_ERR_SHIFT)) & DCM_GPR_DCMROD4_PF1_CODE_ECC_ERR_MASK)

#define DCM_GPR_DCMROD4_PF1_DATA_ECC_ERR_MASK    (0x8000U)
#define DCM_GPR_DCMROD4_PF1_DATA_ECC_ERR_SHIFT   (15U)
#define DCM_GPR_DCMROD4_PF1_DATA_ECC_ERR_WIDTH   (1U)
#define DCM_GPR_DCMROD4_PF1_DATA_ECC_ERR(x)      (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD4_PF1_DATA_ECC_ERR_SHIFT)) & DCM_GPR_DCMROD4_PF1_DATA_ECC_ERR_MASK)

#define DCM_GPR_DCMROD4_FLASH_EDC_ERR_MASK       (0x40000U)
#define DCM_GPR_DCMROD4_FLASH_EDC_ERR_SHIFT      (18U)
#define DCM_GPR_DCMROD4_FLASH_EDC_ERR_WIDTH      (1U)
#define DCM_GPR_DCMROD4_FLASH_EDC_ERR(x)         (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD4_FLASH_EDC_ERR_SHIFT)) & DCM_GPR_DCMROD4_FLASH_EDC_ERR_MASK)

#define DCM_GPR_DCMROD4_FLASH_ADDR_ENC_ERR_MASK  (0x80000U)
#define DCM_GPR_DCMROD4_FLASH_ADDR_ENC_ERR_SHIFT (19U)
#define DCM_GPR_DCMROD4_FLASH_ADDR_ENC_ERR_WIDTH (1U)
#define DCM_GPR_DCMROD4_FLASH_ADDR_ENC_ERR(x)    (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD4_FLASH_ADDR_ENC_ERR_SHIFT)) & DCM_GPR_DCMROD4_FLASH_ADDR_ENC_ERR_MASK)

#define DCM_GPR_DCMROD4_FLASH_REF_ERR_MASK       (0x100000U)
#define DCM_GPR_DCMROD4_FLASH_REF_ERR_SHIFT      (20U)
#define DCM_GPR_DCMROD4_FLASH_REF_ERR_WIDTH      (1U)
#define DCM_GPR_DCMROD4_FLASH_REF_ERR(x)         (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD4_FLASH_REF_ERR_SHIFT)) & DCM_GPR_DCMROD4_FLASH_REF_ERR_MASK)

#define DCM_GPR_DCMROD4_FLASH_RST_ERR_MASK       (0x200000U)
#define DCM_GPR_DCMROD4_FLASH_RST_ERR_SHIFT      (21U)
#define DCM_GPR_DCMROD4_FLASH_RST_ERR_WIDTH      (1U)
#define DCM_GPR_DCMROD4_FLASH_RST_ERR(x)         (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD4_FLASH_RST_ERR_SHIFT)) & DCM_GPR_DCMROD4_FLASH_RST_ERR_MASK)

#define DCM_GPR_DCMROD4_FLASH_SCAN_ERR_MASK      (0x400000U)
#define DCM_GPR_DCMROD4_FLASH_SCAN_ERR_SHIFT     (22U)
#define DCM_GPR_DCMROD4_FLASH_SCAN_ERR_WIDTH     (1U)
#define DCM_GPR_DCMROD4_FLASH_SCAN_ERR(x)        (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD4_FLASH_SCAN_ERR_SHIFT)) & DCM_GPR_DCMROD4_FLASH_SCAN_ERR_MASK)

#define DCM_GPR_DCMROD4_FLASH_ACCESS_ERR_MASK    (0x1000000U)
#define DCM_GPR_DCMROD4_FLASH_ACCESS_ERR_SHIFT   (24U)
#define DCM_GPR_DCMROD4_FLASH_ACCESS_ERR_WIDTH   (1U)
#define DCM_GPR_DCMROD4_FLASH_ACCESS_ERR(x)      (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD4_FLASH_ACCESS_ERR_SHIFT)) & DCM_GPR_DCMROD4_FLASH_ACCESS_ERR_MASK)

#define DCM_GPR_DCMROD4_VDD1P1_GNG_ERR_MASK      (0x4000000U)
#define DCM_GPR_DCMROD4_VDD1P1_GNG_ERR_SHIFT     (26U)
#define DCM_GPR_DCMROD4_VDD1P1_GNG_ERR_WIDTH     (1U)
#define DCM_GPR_DCMROD4_VDD1P1_GNG_ERR(x)        (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD4_VDD1P1_GNG_ERR_SHIFT)) & DCM_GPR_DCMROD4_VDD1P1_GNG_ERR_MASK)

#define DCM_GPR_DCMROD4_VDD2P5_GNG_ERR_MASK      (0x8000000U)
#define DCM_GPR_DCMROD4_VDD2P5_GNG_ERR_SHIFT     (27U)
#define DCM_GPR_DCMROD4_VDD2P5_GNG_ERR_WIDTH     (1U)
#define DCM_GPR_DCMROD4_VDD2P5_GNG_ERR(x)        (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD4_VDD2P5_GNG_ERR_SHIFT)) & DCM_GPR_DCMROD4_VDD2P5_GNG_ERR_MASK)

#define DCM_GPR_DCMROD4_TEST_ACTIVATION_0_ERR_MASK (0x20000000U)
#define DCM_GPR_DCMROD4_TEST_ACTIVATION_0_ERR_SHIFT (29U)
#define DCM_GPR_DCMROD4_TEST_ACTIVATION_0_ERR_WIDTH (1U)
#define DCM_GPR_DCMROD4_TEST_ACTIVATION_0_ERR(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD4_TEST_ACTIVATION_0_ERR_SHIFT)) & DCM_GPR_DCMROD4_TEST_ACTIVATION_0_ERR_MASK)

#define DCM_GPR_DCMROD4_TEST_ACTIVATION_1_ERR_MASK (0x40000000U)
#define DCM_GPR_DCMROD4_TEST_ACTIVATION_1_ERR_SHIFT (30U)
#define DCM_GPR_DCMROD4_TEST_ACTIVATION_1_ERR_WIDTH (1U)
#define DCM_GPR_DCMROD4_TEST_ACTIVATION_1_ERR(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD4_TEST_ACTIVATION_1_ERR_SHIFT)) & DCM_GPR_DCMROD4_TEST_ACTIVATION_1_ERR_MASK)
/*! @} */

/*! @name DCMROD5 - Read Only GPR On Destructive Reset Register */
/*! @{ */

#define DCM_GPR_DCMROD5_INTM_0_ERR_MASK          (0x2U)
#define DCM_GPR_DCMROD5_INTM_0_ERR_SHIFT         (1U)
#define DCM_GPR_DCMROD5_INTM_0_ERR_WIDTH         (1U)
#define DCM_GPR_DCMROD5_INTM_0_ERR(x)            (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD5_INTM_0_ERR_SHIFT)) & DCM_GPR_DCMROD5_INTM_0_ERR_MASK)

#define DCM_GPR_DCMROD5_INTM_1_ERR_MASK          (0x4U)
#define DCM_GPR_DCMROD5_INTM_1_ERR_SHIFT         (2U)
#define DCM_GPR_DCMROD5_INTM_1_ERR_WIDTH         (1U)
#define DCM_GPR_DCMROD5_INTM_1_ERR(x)            (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD5_INTM_1_ERR_SHIFT)) & DCM_GPR_DCMROD5_INTM_1_ERR_MASK)

#define DCM_GPR_DCMROD5_INTM_2_ERR_MASK          (0x8U)
#define DCM_GPR_DCMROD5_INTM_2_ERR_SHIFT         (3U)
#define DCM_GPR_DCMROD5_INTM_2_ERR_WIDTH         (1U)
#define DCM_GPR_DCMROD5_INTM_2_ERR(x)            (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD5_INTM_2_ERR_SHIFT)) & DCM_GPR_DCMROD5_INTM_2_ERR_MASK)

#define DCM_GPR_DCMROD5_INTM_3_ERR_MASK          (0x10U)
#define DCM_GPR_DCMROD5_INTM_3_ERR_SHIFT         (4U)
#define DCM_GPR_DCMROD5_INTM_3_ERR_WIDTH         (1U)
#define DCM_GPR_DCMROD5_INTM_3_ERR(x)            (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD5_INTM_3_ERR_SHIFT)) & DCM_GPR_DCMROD5_INTM_3_ERR_MASK)

#define DCM_GPR_DCMROD5_SW_NCF_0_MASK            (0x20U)
#define DCM_GPR_DCMROD5_SW_NCF_0_SHIFT           (5U)
#define DCM_GPR_DCMROD5_SW_NCF_0_WIDTH           (1U)
#define DCM_GPR_DCMROD5_SW_NCF_0(x)              (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD5_SW_NCF_0_SHIFT)) & DCM_GPR_DCMROD5_SW_NCF_0_MASK)

#define DCM_GPR_DCMROD5_SW_NCF_1_MASK            (0x40U)
#define DCM_GPR_DCMROD5_SW_NCF_1_SHIFT           (6U)
#define DCM_GPR_DCMROD5_SW_NCF_1_WIDTH           (1U)
#define DCM_GPR_DCMROD5_SW_NCF_1(x)              (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD5_SW_NCF_1_SHIFT)) & DCM_GPR_DCMROD5_SW_NCF_1_MASK)

#define DCM_GPR_DCMROD5_SW_NCF_2_MASK            (0x80U)
#define DCM_GPR_DCMROD5_SW_NCF_2_SHIFT           (7U)
#define DCM_GPR_DCMROD5_SW_NCF_2_WIDTH           (1U)
#define DCM_GPR_DCMROD5_SW_NCF_2(x)              (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD5_SW_NCF_2_SHIFT)) & DCM_GPR_DCMROD5_SW_NCF_2_MASK)

#define DCM_GPR_DCMROD5_SW_NCF_3_MASK            (0x100U)
#define DCM_GPR_DCMROD5_SW_NCF_3_SHIFT           (8U)
#define DCM_GPR_DCMROD5_SW_NCF_3_WIDTH           (1U)
#define DCM_GPR_DCMROD5_SW_NCF_3(x)              (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD5_SW_NCF_3_SHIFT)) & DCM_GPR_DCMROD5_SW_NCF_3_MASK)

#define DCM_GPR_DCMROD5_STCU_NCF_MASK            (0x200U)
#define DCM_GPR_DCMROD5_STCU_NCF_SHIFT           (9U)
#define DCM_GPR_DCMROD5_STCU_NCF_WIDTH           (1U)
#define DCM_GPR_DCMROD5_STCU_NCF(x)              (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD5_STCU_NCF_SHIFT)) & DCM_GPR_DCMROD5_STCU_NCF_MASK)

#define DCM_GPR_DCMROD5_MBIST_ACTIVATION_ERR_MASK (0x400U)
#define DCM_GPR_DCMROD5_MBIST_ACTIVATION_ERR_SHIFT (10U)
#define DCM_GPR_DCMROD5_MBIST_ACTIVATION_ERR_WIDTH (1U)
#define DCM_GPR_DCMROD5_MBIST_ACTIVATION_ERR(x)  (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD5_MBIST_ACTIVATION_ERR_SHIFT)) & DCM_GPR_DCMROD5_MBIST_ACTIVATION_ERR_MASK)

#define DCM_GPR_DCMROD5_STCU_BIST_USER_CF_MASK   (0x800U)
#define DCM_GPR_DCMROD5_STCU_BIST_USER_CF_SHIFT  (11U)
#define DCM_GPR_DCMROD5_STCU_BIST_USER_CF_WIDTH  (1U)
#define DCM_GPR_DCMROD5_STCU_BIST_USER_CF(x)     (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD5_STCU_BIST_USER_CF_SHIFT)) & DCM_GPR_DCMROD5_STCU_BIST_USER_CF_MASK)

#define DCM_GPR_DCMROD5_MTR_BUS_ERR_MASK         (0x1000U)
#define DCM_GPR_DCMROD5_MTR_BUS_ERR_SHIFT        (12U)
#define DCM_GPR_DCMROD5_MTR_BUS_ERR_WIDTH        (1U)
#define DCM_GPR_DCMROD5_MTR_BUS_ERR(x)           (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD5_MTR_BUS_ERR_SHIFT)) & DCM_GPR_DCMROD5_MTR_BUS_ERR_MASK)

#define DCM_GPR_DCMROD5_DEBUG_ACTIVATION_ERR_MASK (0x2000U)
#define DCM_GPR_DCMROD5_DEBUG_ACTIVATION_ERR_SHIFT (13U)
#define DCM_GPR_DCMROD5_DEBUG_ACTIVATION_ERR_WIDTH (1U)
#define DCM_GPR_DCMROD5_DEBUG_ACTIVATION_ERR(x)  (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD5_DEBUG_ACTIVATION_ERR_SHIFT)) & DCM_GPR_DCMROD5_DEBUG_ACTIVATION_ERR_MASK)

#define DCM_GPR_DCMROD5_TCM_RDATA_EDC_ERR_MASK   (0x4000U)
#define DCM_GPR_DCMROD5_TCM_RDATA_EDC_ERR_SHIFT  (14U)
#define DCM_GPR_DCMROD5_TCM_RDATA_EDC_ERR_WIDTH  (1U)
#define DCM_GPR_DCMROD5_TCM_RDATA_EDC_ERR(x)     (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD5_TCM_RDATA_EDC_ERR_SHIFT)) & DCM_GPR_DCMROD5_TCM_RDATA_EDC_ERR_MASK)

#define DCM_GPR_DCMROD5_MAC_RDATA_EDC_ERR_MASK  (0x8000U)
#define DCM_GPR_DCMROD5_MAC_RDATA_EDC_ERR_SHIFT (15U)
#define DCM_GPR_DCMROD5_MAC_RDATA_EDC_ERR_WIDTH (1U)
#define DCM_GPR_DCMROD5_MAC_RDATA_EDC_ERR(x)    (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD5_MAC_RDATA_EDC_ERR_SHIFT)) & DCM_GPR_DCMROD5_MAC_RDATA_EDC_ERR_MASK)

#define DCM_GPR_DCMROD5_DMA_RDATA_EDC_ERR_MASK   (0x20000U)
#define DCM_GPR_DCMROD5_DMA_RDATA_EDC_ERR_SHIFT  (17U)
#define DCM_GPR_DCMROD5_DMA_RDATA_EDC_ERR_WIDTH  (1U)
#define DCM_GPR_DCMROD5_DMA_RDATA_EDC_ERR(x)     (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD5_DMA_RDATA_EDC_ERR_SHIFT)) & DCM_GPR_DCMROD5_DMA_RDATA_EDC_ERR_MASK)

#define DCM_GPR_DCMROD5_CM7_0_AHBP_RDATA_EDC_ERR_MASK (0x100000U)
#define DCM_GPR_DCMROD5_CM7_0_AHBP_RDATA_EDC_ERR_SHIFT (20U)
#define DCM_GPR_DCMROD5_CM7_0_AHBP_RDATA_EDC_ERR_WIDTH (1U)
#define DCM_GPR_DCMROD5_CM7_0_AHBP_RDATA_EDC_ERR(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD5_CM7_0_AHBP_RDATA_EDC_ERR_SHIFT)) & DCM_GPR_DCMROD5_CM7_0_AHBP_RDATA_EDC_ERR_MASK)

#define DCM_GPR_DCMROD5_CM7_0_AHBM_RDATA_EDC_ERR_MASK (0x200000U)
#define DCM_GPR_DCMROD5_CM7_0_AHBM_RDATA_EDC_ERR_SHIFT (21U)
#define DCM_GPR_DCMROD5_CM7_0_AHBM_RDATA_EDC_ERR_WIDTH (1U)
#define DCM_GPR_DCMROD5_CM7_0_AHBM_RDATA_EDC_ERR(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD5_CM7_0_AHBM_RDATA_EDC_ERR_SHIFT)) & DCM_GPR_DCMROD5_CM7_0_AHBM_RDATA_EDC_ERR_MASK)

#define DCM_GPR_DCMROD5_HSE_RDATA_EDC_ERR_MASK   (0x400000U)
#define DCM_GPR_DCMROD5_HSE_RDATA_EDC_ERR_SHIFT  (22U)
#define DCM_GPR_DCMROD5_HSE_RDATA_EDC_ERR_WIDTH  (1U)
#define DCM_GPR_DCMROD5_HSE_RDATA_EDC_ERR(x)     (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROD5_HSE_RDATA_EDC_ERR_SHIFT)) & DCM_GPR_DCMROD5_HSE_RDATA_EDC_ERR_MASK)
/*! @} */

/*! @name DCMROF1 - Read Only GPR On Functional Reset Register */
/*! @{ */

#define DCM_GPR_DCMROF1_MAC_MDC_CHID_0_MASK     (0x1U)
#define DCM_GPR_DCMROF1_MAC_MDC_CHID_0_SHIFT    (0U)
#define DCM_GPR_DCMROF1_MAC_MDC_CHID_0_WIDTH    (1U)
#define DCM_GPR_DCMROF1_MAC_MDC_CHID_0(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROF1_MAC_MDC_CHID_0_SHIFT)) & DCM_GPR_DCMROF1_MAC_MDC_CHID_0_MASK)

#define DCM_GPR_DCMROF1_MAC_MDC_CHID_1_MASK     (0x2U)
#define DCM_GPR_DCMROF1_MAC_MDC_CHID_1_SHIFT    (1U)
#define DCM_GPR_DCMROF1_MAC_MDC_CHID_1_WIDTH    (1U)
#define DCM_GPR_DCMROF1_MAC_MDC_CHID_1(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROF1_MAC_MDC_CHID_1_SHIFT)) & DCM_GPR_DCMROF1_MAC_MDC_CHID_1_MASK)
/*! @} */

/*! @name DCMROF2 - Read Only GPR On Functional Reset Register */
/*! @{ */

#define DCM_GPR_DCMROF2_DCF_SDID0_MASK           (0xFFFFFFFFU)
#define DCM_GPR_DCMROF2_DCF_SDID0_SHIFT          (0U)
#define DCM_GPR_DCMROF2_DCF_SDID0_WIDTH          (32U)
#define DCM_GPR_DCMROF2_DCF_SDID0(x)             (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROF2_DCF_SDID0_SHIFT)) & DCM_GPR_DCMROF2_DCF_SDID0_MASK)
/*! @} */

/*! @name DCMROF3 - Read Only GPR On Functional Reset Register */
/*! @{ */

#define DCM_GPR_DCMROF3_DCF_SDID1_MASK           (0xFFFFFFFFU)
#define DCM_GPR_DCMROF3_DCF_SDID1_SHIFT          (0U)
#define DCM_GPR_DCMROF3_DCF_SDID1_WIDTH          (32U)
#define DCM_GPR_DCMROF3_DCF_SDID1(x)             (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROF3_DCF_SDID1_SHIFT)) & DCM_GPR_DCMROF3_DCF_SDID1_MASK)
/*! @} */

/*! @name DCMROF4 - Read Only GPR On Functional Reset Register */
/*! @{ */

#define DCM_GPR_DCMROF4_DCF_SDID2_MASK           (0xFFFFFFFFU)
#define DCM_GPR_DCMROF4_DCF_SDID2_SHIFT          (0U)
#define DCM_GPR_DCMROF4_DCF_SDID2_WIDTH          (32U)
#define DCM_GPR_DCMROF4_DCF_SDID2(x)             (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROF4_DCF_SDID2_SHIFT)) & DCM_GPR_DCMROF4_DCF_SDID2_MASK)
/*! @} */

/*! @name DCMROF5 - Read Only GPR On Functional Reset Register */
/*! @{ */

#define DCM_GPR_DCMROF5_DCF_SDID3_MASK           (0xFFFFFFFFU)
#define DCM_GPR_DCMROF5_DCF_SDID3_SHIFT          (0U)
#define DCM_GPR_DCMROF5_DCF_SDID3_WIDTH          (32U)
#define DCM_GPR_DCMROF5_DCF_SDID3(x)             (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROF5_DCF_SDID3_SHIFT)) & DCM_GPR_DCMROF5_DCF_SDID3_MASK)
/*! @} */

/*! @name DCMROF6 - Read Only GPR On Functional Reset Register */
/*! @{ */

#define DCM_GPR_DCMROF6_DCF_SDID4_MASK           (0xFFFFFFFFU)
#define DCM_GPR_DCMROF6_DCF_SDID4_SHIFT          (0U)
#define DCM_GPR_DCMROF6_DCF_SDID4_WIDTH          (32U)
#define DCM_GPR_DCMROF6_DCF_SDID4(x)             (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROF6_DCF_SDID4_SHIFT)) & DCM_GPR_DCMROF6_DCF_SDID4_MASK)
/*! @} */

/*! @name DCMROF7 - Read Only GPR On Functional Reset Register */
/*! @{ */

#define DCM_GPR_DCMROF7_DCF_SDID5_MASK           (0xFFFFFFFFU)
#define DCM_GPR_DCMROF7_DCF_SDID5_SHIFT          (0U)
#define DCM_GPR_DCMROF7_DCF_SDID5_WIDTH          (32U)
#define DCM_GPR_DCMROF7_DCF_SDID5(x)             (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROF7_DCF_SDID5_SHIFT)) & DCM_GPR_DCMROF7_DCF_SDID5_MASK)
/*! @} */

/*! @name DCMROF8 - Read Only GPR On Functional Reset Register */
/*! @{ */

#define DCM_GPR_DCMROF8_DCF_SDID6_MASK           (0xFFFFFFFFU)
#define DCM_GPR_DCMROF8_DCF_SDID6_SHIFT          (0U)
#define DCM_GPR_DCMROF8_DCF_SDID6_WIDTH          (32U)
#define DCM_GPR_DCMROF8_DCF_SDID6(x)             (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROF8_DCF_SDID6_SHIFT)) & DCM_GPR_DCMROF8_DCF_SDID6_MASK)
/*! @} */

/*! @name DCMROF9 - Read Only GPR On Functional Reset Register */
/*! @{ */

#define DCM_GPR_DCMROF9_DCF_SDID7_MASK           (0xFFFFFFFFU)
#define DCM_GPR_DCMROF9_DCF_SDID7_SHIFT          (0U)
#define DCM_GPR_DCMROF9_DCF_SDID7_WIDTH          (32U)
#define DCM_GPR_DCMROF9_DCF_SDID7(x)             (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROF9_DCF_SDID7_SHIFT)) & DCM_GPR_DCMROF9_DCF_SDID7_MASK)
/*! @} */

/*! @name DCMROF10 - Read Only GPR On Functional Reset Register */
/*! @{ */

#define DCM_GPR_DCMROF10_DCF_SDID8_MASK          (0xFFFFFFFFU)
#define DCM_GPR_DCMROF10_DCF_SDID8_SHIFT         (0U)
#define DCM_GPR_DCMROF10_DCF_SDID8_WIDTH         (32U)
#define DCM_GPR_DCMROF10_DCF_SDID8(x)            (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROF10_DCF_SDID8_SHIFT)) & DCM_GPR_DCMROF10_DCF_SDID8_MASK)
/*! @} */

/*! @name DCMROF11 - Read Only GPR On Functional Reset Register */
/*! @{ */

#define DCM_GPR_DCMROF11_DCF_SDID9_MASK          (0xFFFFFFFFU)
#define DCM_GPR_DCMROF11_DCF_SDID9_SHIFT         (0U)
#define DCM_GPR_DCMROF11_DCF_SDID9_WIDTH         (32U)
#define DCM_GPR_DCMROF11_DCF_SDID9(x)            (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROF11_DCF_SDID9_SHIFT)) & DCM_GPR_DCMROF11_DCF_SDID9_MASK)
/*! @} */

/*! @name DCMROF12 - Read Only GPR On Functional Reset Register */
/*! @{ */

#define DCM_GPR_DCMROF12_DCF_SDID10_MASK         (0xFFFFFFFFU)
#define DCM_GPR_DCMROF12_DCF_SDID10_SHIFT        (0U)
#define DCM_GPR_DCMROF12_DCF_SDID10_WIDTH        (32U)
#define DCM_GPR_DCMROF12_DCF_SDID10(x)           (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROF12_DCF_SDID10_SHIFT)) & DCM_GPR_DCMROF12_DCF_SDID10_MASK)
/*! @} */

/*! @name DCMROF13 - Read Only GPR On Functional Reset Register */
/*! @{ */

#define DCM_GPR_DCMROF13_DCF_SDID11_MASK         (0xFFFFFFFFU)
#define DCM_GPR_DCMROF13_DCF_SDID11_SHIFT        (0U)
#define DCM_GPR_DCMROF13_DCF_SDID11_WIDTH        (32U)
#define DCM_GPR_DCMROF13_DCF_SDID11(x)           (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROF13_DCF_SDID11_SHIFT)) & DCM_GPR_DCMROF13_DCF_SDID11_MASK)
/*! @} */

/*! @name DCMROF14 - Read Only GPR On Functional Reset Register */
/*! @{ */

#define DCM_GPR_DCMROF14_DCF_SDID12_MASK         (0xFFFFFFFFU)
#define DCM_GPR_DCMROF14_DCF_SDID12_SHIFT        (0U)
#define DCM_GPR_DCMROF14_DCF_SDID12_WIDTH        (32U)
#define DCM_GPR_DCMROF14_DCF_SDID12(x)           (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROF14_DCF_SDID12_SHIFT)) & DCM_GPR_DCMROF14_DCF_SDID12_MASK)
/*! @} */

/*! @name DCMROF15 - Read Only GPR On Functional Reset Register */
/*! @{ */

#define DCM_GPR_DCMROF15_DCF_SDID13_MASK         (0xFFFFFFFFU)
#define DCM_GPR_DCMROF15_DCF_SDID13_SHIFT        (0U)
#define DCM_GPR_DCMROF15_DCF_SDID13_WIDTH        (32U)
#define DCM_GPR_DCMROF15_DCF_SDID13(x)           (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROF15_DCF_SDID13_SHIFT)) & DCM_GPR_DCMROF15_DCF_SDID13_MASK)
/*! @} */

/*! @name DCMROF16 - Read Only GPR On Functional Reset Register */
/*! @{ */

#define DCM_GPR_DCMROF16_DCF_SDID14_MASK         (0xFFFFFFFFU)
#define DCM_GPR_DCMROF16_DCF_SDID14_SHIFT        (0U)
#define DCM_GPR_DCMROF16_DCF_SDID14_WIDTH        (32U)
#define DCM_GPR_DCMROF16_DCF_SDID14(x)           (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROF16_DCF_SDID14_SHIFT)) & DCM_GPR_DCMROF16_DCF_SDID14_MASK)
/*! @} */

/*! @name DCMROF17 - Read Only GPR On Functional Reset Register */
/*! @{ */

#define DCM_GPR_DCMROF17_DCF_SDID15_MASK         (0xFFFFFFFFU)
#define DCM_GPR_DCMROF17_DCF_SDID15_SHIFT        (0U)
#define DCM_GPR_DCMROF17_DCF_SDID15_WIDTH        (32U)
#define DCM_GPR_DCMROF17_DCF_SDID15(x)           (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROF17_DCF_SDID15_SHIFT)) & DCM_GPR_DCMROF17_DCF_SDID15_MASK)
/*! @} */

/*! @name DCMROF19 - Read Only GPR On Functional Reset Register */
/*! @{ */

#define DCM_GPR_DCMROF19_LOCKSTEP_EN_MASK        (0x20000000U)
#define DCM_GPR_DCMROF19_LOCKSTEP_EN_SHIFT       (29U)
#define DCM_GPR_DCMROF19_LOCKSTEP_EN_WIDTH       (1U)
#define DCM_GPR_DCMROF19_LOCKSTEP_EN(x)          (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROF19_LOCKSTEP_EN_SHIFT)) & DCM_GPR_DCMROF19_LOCKSTEP_EN_MASK)

#define DCM_GPR_DCMROF19_DCM_DONE_MASK           (0x40000000U)
#define DCM_GPR_DCMROF19_DCM_DONE_SHIFT          (30U)
#define DCM_GPR_DCMROF19_DCM_DONE_WIDTH          (1U)
#define DCM_GPR_DCMROF19_DCM_DONE(x)             (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROF19_DCM_DONE_SHIFT)) & DCM_GPR_DCMROF19_DCM_DONE_MASK)

#define DCM_GPR_DCMROF19_FCCU_EOUT_DEDICATED_MASK (0x80000000U)
#define DCM_GPR_DCMROF19_FCCU_EOUT_DEDICATED_SHIFT (31U)
#define DCM_GPR_DCMROF19_FCCU_EOUT_DEDICATED_WIDTH (1U)
#define DCM_GPR_DCMROF19_FCCU_EOUT_DEDICATED(x)  (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROF19_FCCU_EOUT_DEDICATED_SHIFT)) & DCM_GPR_DCMROF19_FCCU_EOUT_DEDICATED_MASK)
/*! @} */

/*! @name DCMROF20 - Read Only GPR On Functional Reset Register */
/*! @{ */

#define DCM_GPR_DCMROF20_POR_WDG_EN_MASK         (0x1U)
#define DCM_GPR_DCMROF20_POR_WDG_EN_SHIFT        (0U)
#define DCM_GPR_DCMROF20_POR_WDG_EN_WIDTH        (1U)
#define DCM_GPR_DCMROF20_POR_WDG_EN(x)           (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROF20_POR_WDG_EN_SHIFT)) & DCM_GPR_DCMROF20_POR_WDG_EN_MASK)

#define DCM_GPR_DCMROF20_LMAUTO_DIS_MASK         (0x2U)
#define DCM_GPR_DCMROF20_LMAUTO_DIS_SHIFT        (1U)
#define DCM_GPR_DCMROF20_LMAUTO_DIS_WIDTH        (1U)
#define DCM_GPR_DCMROF20_LMAUTO_DIS(x)           (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROF20_LMAUTO_DIS_SHIFT)) & DCM_GPR_DCMROF20_LMAUTO_DIS_MASK)

#define DCM_GPR_DCMROF20_DMA_AXBS_IAHB_BYP_MASK  (0x8U)
#define DCM_GPR_DCMROF20_DMA_AXBS_IAHB_BYP_SHIFT (3U)
#define DCM_GPR_DCMROF20_DMA_AXBS_IAHB_BYP_WIDTH (1U)
#define DCM_GPR_DCMROF20_DMA_AXBS_IAHB_BYP(x)    (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROF20_DMA_AXBS_IAHB_BYP_SHIFT)) & DCM_GPR_DCMROF20_DMA_AXBS_IAHB_BYP_MASK)

#define DCM_GPR_DCMROF20_QSPI_IAHB_BYP_MASK      (0x20U)
#define DCM_GPR_DCMROF20_QSPI_IAHB_BYP_SHIFT     (5U)
#define DCM_GPR_DCMROF20_QSPI_IAHB_BYP_WIDTH     (1U)
#define DCM_GPR_DCMROF20_QSPI_IAHB_BYP(x)        (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROF20_QSPI_IAHB_BYP_SHIFT)) & DCM_GPR_DCMROF20_QSPI_IAHB_BYP_MASK)

#define DCM_GPR_DCMROF20_AIPS_IAHB_BYP_MASK      (0x40U)
#define DCM_GPR_DCMROF20_AIPS_IAHB_BYP_SHIFT     (6U)
#define DCM_GPR_DCMROF20_AIPS_IAHB_BYP_WIDTH     (1U)
#define DCM_GPR_DCMROF20_AIPS_IAHB_BYP(x)        (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROF20_AIPS_IAHB_BYP_SHIFT)) & DCM_GPR_DCMROF20_AIPS_IAHB_BYP_MASK)

#define DCM_GPR_DCMROF20_DCF_DEST_RST_ESC_MASK   (0xFFFC0000U)
#define DCM_GPR_DCMROF20_DCF_DEST_RST_ESC_SHIFT  (18U)
#define DCM_GPR_DCMROF20_DCF_DEST_RST_ESC_WIDTH  (14U)
#define DCM_GPR_DCMROF20_DCF_DEST_RST_ESC(x)     (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROF20_DCF_DEST_RST_ESC_SHIFT)) & DCM_GPR_DCMROF20_DCF_DEST_RST_ESC_MASK)
/*! @} */

/*! @name DCMROF21 - Read Only GPR On Functional Reset Register */
/*! @{ */

#define DCM_GPR_DCMROF21_DCF_DEST_RST_ESC_MASK   (0x3FFFFU)
#define DCM_GPR_DCMROF21_DCF_DEST_RST_ESC_SHIFT  (0U)
#define DCM_GPR_DCMROF21_DCF_DEST_RST_ESC_WIDTH  (18U)
#define DCM_GPR_DCMROF21_DCF_DEST_RST_ESC(x)     (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROF21_DCF_DEST_RST_ESC_SHIFT)) & DCM_GPR_DCMROF21_DCF_DEST_RST_ESC_MASK)

#define DCM_GPR_DCMROF21_HSE_CLK_MODE_OPTION_MASK (0x180000U)
#define DCM_GPR_DCMROF21_HSE_CLK_MODE_OPTION_SHIFT (19U)
#define DCM_GPR_DCMROF21_HSE_CLK_MODE_OPTION_WIDTH (2U)
#define DCM_GPR_DCMROF21_HSE_CLK_MODE_OPTION(x)  (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROF21_HSE_CLK_MODE_OPTION_SHIFT)) & DCM_GPR_DCMROF21_HSE_CLK_MODE_OPTION_MASK)
/*! @} */

/*! @name DCMRWP1 - Read Write GPR On Power On Reset Register */
/*! @{ */

#define DCM_GPR_DCMRWP1_CLKOUT_STANDBY_MASK      (0x8U)
#define DCM_GPR_DCMRWP1_CLKOUT_STANDBY_SHIFT     (3U)
#define DCM_GPR_DCMRWP1_CLKOUT_STANDBY_WIDTH     (1U)
#define DCM_GPR_DCMRWP1_CLKOUT_STANDBY(x)        (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWP1_CLKOUT_STANDBY_SHIFT)) & DCM_GPR_DCMRWP1_CLKOUT_STANDBY_MASK)

#define DCM_GPR_DCMRWP1_STANBDY_PWDOG_DIS_MASK   (0x100U)
#define DCM_GPR_DCMRWP1_STANBDY_PWDOG_DIS_SHIFT  (8U)
#define DCM_GPR_DCMRWP1_STANBDY_PWDOG_DIS_WIDTH  (1U)
#define DCM_GPR_DCMRWP1_STANBDY_PWDOG_DIS(x)     (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWP1_STANBDY_PWDOG_DIS_SHIFT)) & DCM_GPR_DCMRWP1_STANBDY_PWDOG_DIS_MASK)

#define DCM_GPR_DCMRWP1_POR_WDOG_TRIM_MASK       (0x600U)
#define DCM_GPR_DCMRWP1_POR_WDOG_TRIM_SHIFT      (9U)
#define DCM_GPR_DCMRWP1_POR_WDOG_TRIM_WIDTH      (2U)
#define DCM_GPR_DCMRWP1_POR_WDOG_TRIM(x)         (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWP1_POR_WDOG_TRIM_SHIFT)) & DCM_GPR_DCMRWP1_POR_WDOG_TRIM_MASK)
/*! @} */

/*! @name DCMRWP3 - Read Write GPR On Power On Reset Register */
/*! @{ */

#define DCM_GPR_DCMRWP3_DEST_RST9_AS_IPI_MASK    (0x200U)
#define DCM_GPR_DCMRWP3_DEST_RST9_AS_IPI_SHIFT   (9U)
#define DCM_GPR_DCMRWP3_DEST_RST9_AS_IPI_WIDTH   (1U)
#define DCM_GPR_DCMRWP3_DEST_RST9_AS_IPI(x)      (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWP3_DEST_RST9_AS_IPI_SHIFT)) & DCM_GPR_DCMRWP3_DEST_RST9_AS_IPI_MASK)
/*! @} */

/*! @name DCMRWD2 - Read Write GPR On Destructive Reset Register */
/*! @{ */

#define DCM_GPR_DCMRWD2_EOUT_STAT_DUR_STEST_MASK (0x80U)
#define DCM_GPR_DCMRWD2_EOUT_STAT_DUR_STEST_SHIFT (7U)
#define DCM_GPR_DCMRWD2_EOUT_STAT_DUR_STEST_WIDTH (1U)
#define DCM_GPR_DCMRWD2_EOUT_STAT_DUR_STEST(x)   (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD2_EOUT_STAT_DUR_STEST_SHIFT)) & DCM_GPR_DCMRWD2_EOUT_STAT_DUR_STEST_MASK)
/*! @} */

/*! @name DCMRWD3 - Read Write GPR On Destructive Reset Register */
/*! @{ */

#define DCM_GPR_DCMRWD3_CM7_0_LOCKUP_EN_MASK     (0x1U)
#define DCM_GPR_DCMRWD3_CM7_0_LOCKUP_EN_SHIFT    (0U)
#define DCM_GPR_DCMRWD3_CM7_0_LOCKUP_EN_WIDTH    (1U)
#define DCM_GPR_DCMRWD3_CM7_0_LOCKUP_EN(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD3_CM7_0_LOCKUP_EN_SHIFT)) & DCM_GPR_DCMRWD3_CM7_0_LOCKUP_EN_MASK)

#define DCM_GPR_DCMRWD3_CM7_RCCU1_ALARM_EN_MASK  (0x8U)
#define DCM_GPR_DCMRWD3_CM7_RCCU1_ALARM_EN_SHIFT (3U)
#define DCM_GPR_DCMRWD3_CM7_RCCU1_ALARM_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD3_CM7_RCCU1_ALARM_EN(x)    (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD3_CM7_RCCU1_ALARM_EN_SHIFT)) & DCM_GPR_DCMRWD3_CM7_RCCU1_ALARM_EN_MASK)

#define DCM_GPR_DCMRWD3_CM7_RCCU2_ALARM_EN_MASK  (0x10U)
#define DCM_GPR_DCMRWD3_CM7_RCCU2_ALARM_EN_SHIFT (4U)
#define DCM_GPR_DCMRWD3_CM7_RCCU2_ALARM_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD3_CM7_RCCU2_ALARM_EN(x)    (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD3_CM7_RCCU2_ALARM_EN_SHIFT)) & DCM_GPR_DCMRWD3_CM7_RCCU2_ALARM_EN_MASK)

#define DCM_GPR_DCMRWD3_TCM_GSKT_ALARM_EN_MASK   (0x20U)
#define DCM_GPR_DCMRWD3_TCM_GSKT_ALARM_EN_SHIFT  (5U)
#define DCM_GPR_DCMRWD3_TCM_GSKT_ALARM_EN_WIDTH  (1U)
#define DCM_GPR_DCMRWD3_TCM_GSKT_ALARM_EN(x)     (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD3_TCM_GSKT_ALARM_EN_SHIFT)) & DCM_GPR_DCMRWD3_TCM_GSKT_ALARM_EN_MASK)

#define DCM_GPR_DCMRWD3_DMA_SYS_GSKT_ALARM_EN_MASK (0x40U)
#define DCM_GPR_DCMRWD3_DMA_SYS_GSKT_ALARM_EN_SHIFT (6U)
#define DCM_GPR_DCMRWD3_DMA_SYS_GSKT_ALARM_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD3_DMA_SYS_GSKT_ALARM_EN(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD3_DMA_SYS_GSKT_ALARM_EN_SHIFT)) & DCM_GPR_DCMRWD3_DMA_SYS_GSKT_ALARM_EN_MASK)

#define DCM_GPR_DCMRWD3_DMA_PERIPH_GSKT_ALARM_EN_MASK (0x80U)
#define DCM_GPR_DCMRWD3_DMA_PERIPH_GSKT_ALARM_EN_SHIFT (7U)
#define DCM_GPR_DCMRWD3_DMA_PERIPH_GSKT_ALARM_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD3_DMA_PERIPH_GSKT_ALARM_EN(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD3_DMA_PERIPH_GSKT_ALARM_EN_SHIFT)) & DCM_GPR_DCMRWD3_DMA_PERIPH_GSKT_ALARM_EN_MASK)

#define DCM_GPR_DCMRWD3_SYS_AXBS_ALARM_EN_MASK   (0x100U)
#define DCM_GPR_DCMRWD3_SYS_AXBS_ALARM_EN_SHIFT  (8U)
#define DCM_GPR_DCMRWD3_SYS_AXBS_ALARM_EN_WIDTH  (1U)
#define DCM_GPR_DCMRWD3_SYS_AXBS_ALARM_EN(x)     (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD3_SYS_AXBS_ALARM_EN_SHIFT)) & DCM_GPR_DCMRWD3_SYS_AXBS_ALARM_EN_MASK)

#define DCM_GPR_DCMRWD3_DMA_AXBS_ALARM_EN_MASK   (0x200U)
#define DCM_GPR_DCMRWD3_DMA_AXBS_ALARM_EN_SHIFT  (9U)
#define DCM_GPR_DCMRWD3_DMA_AXBS_ALARM_EN_WIDTH  (1U)
#define DCM_GPR_DCMRWD3_DMA_AXBS_ALARM_EN(x)     (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD3_DMA_AXBS_ALARM_EN_SHIFT)) & DCM_GPR_DCMRWD3_DMA_AXBS_ALARM_EN_MASK)

#define DCM_GPR_DCMRWD3_HSE_GSKT_ALARM_EN_MASK   (0x800U)
#define DCM_GPR_DCMRWD3_HSE_GSKT_ALARM_EN_SHIFT  (11U)
#define DCM_GPR_DCMRWD3_HSE_GSKT_ALARM_EN_WIDTH  (1U)
#define DCM_GPR_DCMRWD3_HSE_GSKT_ALARM_EN(x)     (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD3_HSE_GSKT_ALARM_EN_SHIFT)) & DCM_GPR_DCMRWD3_HSE_GSKT_ALARM_EN_MASK)

#define DCM_GPR_DCMRWD3_QSPI_GSKT_ALARM_EN_MASK  (0x1000U)
#define DCM_GPR_DCMRWD3_QSPI_GSKT_ALARM_EN_SHIFT (12U)
#define DCM_GPR_DCMRWD3_QSPI_GSKT_ALARM_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD3_QSPI_GSKT_ALARM_EN(x)    (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD3_QSPI_GSKT_ALARM_EN_SHIFT)) & DCM_GPR_DCMRWD3_QSPI_GSKT_ALARM_EN_MASK)

#define DCM_GPR_DCMRWD3_AIPS1_GSKT_ALARM_EN_MASK (0x2000U)
#define DCM_GPR_DCMRWD3_AIPS1_GSKT_ALARM_EN_SHIFT (13U)
#define DCM_GPR_DCMRWD3_AIPS1_GSKT_ALARM_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD3_AIPS1_GSKT_ALARM_EN(x)   (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD3_AIPS1_GSKT_ALARM_EN_SHIFT)) & DCM_GPR_DCMRWD3_AIPS1_GSKT_ALARM_EN_MASK)

#define DCM_GPR_DCMRWD3_AIPS2_GSKT_ALARM_EN_MASK (0x4000U)
#define DCM_GPR_DCMRWD3_AIPS2_GSKT_ALARM_EN_SHIFT (14U)
#define DCM_GPR_DCMRWD3_AIPS2_GSKT_ALARM_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD3_AIPS2_GSKT_ALARM_EN(x)   (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD3_AIPS2_GSKT_ALARM_EN_SHIFT)) & DCM_GPR_DCMRWD3_AIPS2_GSKT_ALARM_EN_MASK)

#define DCM_GPR_DCMRWD3_ADDR_EDC_ERR_EN_MASK     (0x8000U)
#define DCM_GPR_DCMRWD3_ADDR_EDC_ERR_EN_SHIFT    (15U)
#define DCM_GPR_DCMRWD3_ADDR_EDC_ERR_EN_WIDTH    (1U)
#define DCM_GPR_DCMRWD3_ADDR_EDC_ERR_EN(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD3_ADDR_EDC_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD3_ADDR_EDC_ERR_EN_MASK)

#define DCM_GPR_DCMRWD3_DATA_EDC_ERR_EN_MASK     (0x10000U)
#define DCM_GPR_DCMRWD3_DATA_EDC_ERR_EN_SHIFT    (16U)
#define DCM_GPR_DCMRWD3_DATA_EDC_ERR_EN_WIDTH    (1U)
#define DCM_GPR_DCMRWD3_DATA_EDC_ERR_EN(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD3_DATA_EDC_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD3_DATA_EDC_ERR_EN_MASK)

#define DCM_GPR_DCMRWD3_TCM_AXBS_ALARM_EN_MASK   (0x20000U)
#define DCM_GPR_DCMRWD3_TCM_AXBS_ALARM_EN_SHIFT  (17U)
#define DCM_GPR_DCMRWD3_TCM_AXBS_ALARM_EN_WIDTH  (1U)
#define DCM_GPR_DCMRWD3_TCM_AXBS_ALARM_EN(x)     (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD3_TCM_AXBS_ALARM_EN_SHIFT)) & DCM_GPR_DCMRWD3_TCM_AXBS_ALARM_EN_MASK)

#define DCM_GPR_DCMRWD3_MAC_GSKT_ALARM_EN_MASK  (0x40000U)
#define DCM_GPR_DCMRWD3_MAC_GSKT_ALARM_EN_SHIFT (18U)
#define DCM_GPR_DCMRWD3_MAC_GSKT_ALARM_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD3_MAC_GSKT_ALARM_EN(x)    (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD3_MAC_GSKT_ALARM_EN_SHIFT)) & DCM_GPR_DCMRWD3_MAC_GSKT_ALARM_EN_MASK)

#define DCM_GPR_DCMRWD3_PERIPH_AXBS_ALARM_EN_MASK (0x80000U)
#define DCM_GPR_DCMRWD3_PERIPH_AXBS_ALARM_EN_SHIFT (19U)
#define DCM_GPR_DCMRWD3_PERIPH_AXBS_ALARM_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD3_PERIPH_AXBS_ALARM_EN(x)  (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD3_PERIPH_AXBS_ALARM_EN_SHIFT)) & DCM_GPR_DCMRWD3_PERIPH_AXBS_ALARM_EN_MASK)

#define DCM_GPR_DCMRWD3_LC_ERR_EN_MASK           (0x400000U)
#define DCM_GPR_DCMRWD3_LC_ERR_EN_SHIFT          (22U)
#define DCM_GPR_DCMRWD3_LC_ERR_EN_WIDTH          (1U)
#define DCM_GPR_DCMRWD3_LC_ERR_EN(x)             (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD3_LC_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD3_LC_ERR_EN_MASK)

#define DCM_GPR_DCMRWD3_PRAM1_ECC_ERR_EN_MASK    (0x1000000U)
#define DCM_GPR_DCMRWD3_PRAM1_ECC_ERR_EN_SHIFT   (24U)
#define DCM_GPR_DCMRWD3_PRAM1_ECC_ERR_EN_WIDTH   (1U)
#define DCM_GPR_DCMRWD3_PRAM1_ECC_ERR_EN(x)      (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD3_PRAM1_ECC_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD3_PRAM1_ECC_ERR_EN_MASK)

#define DCM_GPR_DCMRWD3_PRAM0_ECC_ERR_EN_MASK    (0x2000000U)
#define DCM_GPR_DCMRWD3_PRAM0_ECC_ERR_EN_SHIFT   (25U)
#define DCM_GPR_DCMRWD3_PRAM0_ECC_ERR_EN_WIDTH   (1U)
#define DCM_GPR_DCMRWD3_PRAM0_ECC_ERR_EN(x)      (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD3_PRAM0_ECC_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD3_PRAM0_ECC_ERR_EN_MASK)

#define DCM_GPR_DCMRWD3_CM7_0_DCDATA_ECC_ERR_EN_MASK (0x4000000U)
#define DCM_GPR_DCMRWD3_CM7_0_DCDATA_ECC_ERR_EN_SHIFT (26U)
#define DCM_GPR_DCMRWD3_CM7_0_DCDATA_ECC_ERR_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD3_CM7_0_DCDATA_ECC_ERR_EN(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD3_CM7_0_DCDATA_ECC_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD3_CM7_0_DCDATA_ECC_ERR_EN_MASK)

#define DCM_GPR_DCMRWD3_CM7_0_DCTAG_ECC_ERR_EN_MASK (0x10000000U)
#define DCM_GPR_DCMRWD3_CM7_0_DCTAG_ECC_ERR_EN_SHIFT (28U)
#define DCM_GPR_DCMRWD3_CM7_0_DCTAG_ECC_ERR_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD3_CM7_0_DCTAG_ECC_ERR_EN(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD3_CM7_0_DCTAG_ECC_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD3_CM7_0_DCTAG_ECC_ERR_EN_MASK)

#define DCM_GPR_DCMRWD3_CM7_0_ICDATA_ECC_ERR_EN_MASK (0x40000000U)
#define DCM_GPR_DCMRWD3_CM7_0_ICDATA_ECC_ERR_EN_SHIFT (30U)
#define DCM_GPR_DCMRWD3_CM7_0_ICDATA_ECC_ERR_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD3_CM7_0_ICDATA_ECC_ERR_EN(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD3_CM7_0_ICDATA_ECC_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD3_CM7_0_ICDATA_ECC_ERR_EN_MASK)
/*! @} */

/*! @name DCMRWD4 - Read Write GPR On Destructive Reset Register */
/*! @{ */

#define DCM_GPR_DCMRWD4_CM7_0_ICTAG_ECC_ERR_EN_MASK (0x1U)
#define DCM_GPR_DCMRWD4_CM7_0_ICTAG_ECC_ERR_EN_SHIFT (0U)
#define DCM_GPR_DCMRWD4_CM7_0_ICTAG_ECC_ERR_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD4_CM7_0_ICTAG_ECC_ERR_EN(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD4_CM7_0_ICTAG_ECC_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD4_CM7_0_ICTAG_ECC_ERR_EN_MASK)

#define DCM_GPR_DCMRWD4_CM7_0_ITCM_ECC_ERR_EN_MASK (0x4U)
#define DCM_GPR_DCMRWD4_CM7_0_ITCM_ECC_ERR_EN_SHIFT (2U)
#define DCM_GPR_DCMRWD4_CM7_0_ITCM_ECC_ERR_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD4_CM7_0_ITCM_ECC_ERR_EN(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD4_CM7_0_ITCM_ECC_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD4_CM7_0_ITCM_ECC_ERR_EN_MASK)

#define DCM_GPR_DCMRWD4_CM7_0_DTCM0_ECC_ERR_EN_MASK (0x8U)
#define DCM_GPR_DCMRWD4_CM7_0_DTCM0_ECC_ERR_EN_SHIFT (3U)
#define DCM_GPR_DCMRWD4_CM7_0_DTCM0_ECC_ERR_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD4_CM7_0_DTCM0_ECC_ERR_EN(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD4_CM7_0_DTCM0_ECC_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD4_CM7_0_DTCM0_ECC_ERR_EN_MASK)

#define DCM_GPR_DCMRWD4_CM7_0_DTCM1_ECC_ERR_EN_MASK (0x10U)
#define DCM_GPR_DCMRWD4_CM7_0_DTCM1_ECC_ERR_EN_SHIFT (4U)
#define DCM_GPR_DCMRWD4_CM7_0_DTCM1_ECC_ERR_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD4_CM7_0_DTCM1_ECC_ERR_EN(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD4_CM7_0_DTCM1_ECC_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD4_CM7_0_DTCM1_ECC_ERR_EN_MASK)

#define DCM_GPR_DCMRWD4_CM7_1_ITCM_ECC_ERR_EN_MASK (0x20U)
#define DCM_GPR_DCMRWD4_CM7_1_ITCM_ECC_ERR_EN_SHIFT (5U)
#define DCM_GPR_DCMRWD4_CM7_1_ITCM_ECC_ERR_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD4_CM7_1_ITCM_ECC_ERR_EN(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD4_CM7_1_ITCM_ECC_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD4_CM7_1_ITCM_ECC_ERR_EN_MASK)

#define DCM_GPR_DCMRWD4_CM7_1_DTCM0_ECC_ERR_EN_MASK (0x40U)
#define DCM_GPR_DCMRWD4_CM7_1_DTCM0_ECC_ERR_EN_SHIFT (6U)
#define DCM_GPR_DCMRWD4_CM7_1_DTCM0_ECC_ERR_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD4_CM7_1_DTCM0_ECC_ERR_EN(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD4_CM7_1_DTCM0_ECC_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD4_CM7_1_DTCM0_ECC_ERR_EN_MASK)

#define DCM_GPR_DCMRWD4_CM7_1_DTCM1_ECC_ERR_EN_MASK (0x80U)
#define DCM_GPR_DCMRWD4_CM7_1_DTCM1_ECC_ERR_EN_SHIFT (7U)
#define DCM_GPR_DCMRWD4_CM7_1_DTCM1_ECC_ERR_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD4_CM7_1_DTCM1_ECC_ERR_EN(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD4_CM7_1_DTCM1_ECC_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD4_CM7_1_DTCM1_ECC_ERR_EN_MASK)

#define DCM_GPR_DCMRWD4_DMA_TCD_RAM_ECC_ERR_EN_MASK (0x100U)
#define DCM_GPR_DCMRWD4_DMA_TCD_RAM_ECC_ERR_EN_SHIFT (8U)
#define DCM_GPR_DCMRWD4_DMA_TCD_RAM_ECC_ERR_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD4_DMA_TCD_RAM_ECC_ERR_EN(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD4_DMA_TCD_RAM_ECC_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD4_DMA_TCD_RAM_ECC_ERR_EN_MASK)

#define DCM_GPR_DCMRWD4_PRAM0_FCCU_ALARM_EN_MASK (0x200U)
#define DCM_GPR_DCMRWD4_PRAM0_FCCU_ALARM_EN_SHIFT (9U)
#define DCM_GPR_DCMRWD4_PRAM0_FCCU_ALARM_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD4_PRAM0_FCCU_ALARM_EN(x)   (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD4_PRAM0_FCCU_ALARM_EN_SHIFT)) & DCM_GPR_DCMRWD4_PRAM0_FCCU_ALARM_EN_MASK)

#define DCM_GPR_DCMRWD4_PRAM1_FCCU_ALARM_EN_MASK (0x400U)
#define DCM_GPR_DCMRWD4_PRAM1_FCCU_ALARM_EN_SHIFT (10U)
#define DCM_GPR_DCMRWD4_PRAM1_FCCU_ALARM_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD4_PRAM1_FCCU_ALARM_EN(x)   (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD4_PRAM1_FCCU_ALARM_EN_SHIFT)) & DCM_GPR_DCMRWD4_PRAM1_FCCU_ALARM_EN_MASK)

#define DCM_GPR_DCMRWD4_HSE_RAM_ECC_ERR_EN_MASK  (0x800U)
#define DCM_GPR_DCMRWD4_HSE_RAM_ECC_ERR_EN_SHIFT (11U)
#define DCM_GPR_DCMRWD4_HSE_RAM_ECC_ERR_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD4_HSE_RAM_ECC_ERR_EN(x)    (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD4_HSE_RAM_ECC_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD4_HSE_RAM_ECC_ERR_EN_MASK)

#define DCM_GPR_DCMRWD4_PF0_CODE_ECC_ERR_EN_MASK (0x1000U)
#define DCM_GPR_DCMRWD4_PF0_CODE_ECC_ERR_EN_SHIFT (12U)
#define DCM_GPR_DCMRWD4_PF0_CODE_ECC_ERR_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD4_PF0_CODE_ECC_ERR_EN(x)   (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD4_PF0_CODE_ECC_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD4_PF0_CODE_ECC_ERR_EN_MASK)

#define DCM_GPR_DCMRWD4_PF0_DATA_ECC_ERR_EN_MASK (0x2000U)
#define DCM_GPR_DCMRWD4_PF0_DATA_ECC_ERR_EN_SHIFT (13U)
#define DCM_GPR_DCMRWD4_PF0_DATA_ECC_ERR_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD4_PF0_DATA_ECC_ERR_EN(x)   (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD4_PF0_DATA_ECC_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD4_PF0_DATA_ECC_ERR_EN_MASK)

#define DCM_GPR_DCMRWD4_PF1_CODE_ECC_ERR_EN_MASK (0x4000U)
#define DCM_GPR_DCMRWD4_PF1_CODE_ECC_ERR_EN_SHIFT (14U)
#define DCM_GPR_DCMRWD4_PF1_CODE_ECC_ERR_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD4_PF1_CODE_ECC_ERR_EN(x)   (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD4_PF1_CODE_ECC_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD4_PF1_CODE_ECC_ERR_EN_MASK)

#define DCM_GPR_DCMRWD4_PF1_DATA_ECC_ERR_EN_MASK (0x8000U)
#define DCM_GPR_DCMRWD4_PF1_DATA_ECC_ERR_EN_SHIFT (15U)
#define DCM_GPR_DCMRWD4_PF1_DATA_ECC_ERR_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD4_PF1_DATA_ECC_ERR_EN(x)   (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD4_PF1_DATA_ECC_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD4_PF1_DATA_ECC_ERR_EN_MASK)

#define DCM_GPR_DCMRWD4_FLASH_EDC_ERR_EN_MASK    (0x40000U)
#define DCM_GPR_DCMRWD4_FLASH_EDC_ERR_EN_SHIFT   (18U)
#define DCM_GPR_DCMRWD4_FLASH_EDC_ERR_EN_WIDTH   (1U)
#define DCM_GPR_DCMRWD4_FLASH_EDC_ERR_EN(x)      (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD4_FLASH_EDC_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD4_FLASH_EDC_ERR_EN_MASK)

#define DCM_GPR_DCMRWD4_FLASH_ADDR_ENC_ERR_EN_MASK (0x80000U)
#define DCM_GPR_DCMRWD4_FLASH_ADDR_ENC_ERR_EN_SHIFT (19U)
#define DCM_GPR_DCMRWD4_FLASH_ADDR_ENC_ERR_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD4_FLASH_ADDR_ENC_ERR_EN(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD4_FLASH_ADDR_ENC_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD4_FLASH_ADDR_ENC_ERR_EN_MASK)

#define DCM_GPR_DCMRWD4_FLASH_REF_ERR_EN_MASK    (0x100000U)
#define DCM_GPR_DCMRWD4_FLASH_REF_ERR_EN_SHIFT   (20U)
#define DCM_GPR_DCMRWD4_FLASH_REF_ERR_EN_WIDTH   (1U)
#define DCM_GPR_DCMRWD4_FLASH_REF_ERR_EN(x)      (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD4_FLASH_REF_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD4_FLASH_REF_ERR_EN_MASK)

#define DCM_GPR_DCMRWD4_FLASH_RST_ERR_EN_MASK    (0x200000U)
#define DCM_GPR_DCMRWD4_FLASH_RST_ERR_EN_SHIFT   (21U)
#define DCM_GPR_DCMRWD4_FLASH_RST_ERR_EN_WIDTH   (1U)
#define DCM_GPR_DCMRWD4_FLASH_RST_ERR_EN(x)      (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD4_FLASH_RST_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD4_FLASH_RST_ERR_EN_MASK)

#define DCM_GPR_DCMRWD4_FLASH_SCAN_ERR_EN_MASK   (0x400000U)
#define DCM_GPR_DCMRWD4_FLASH_SCAN_ERR_EN_SHIFT  (22U)
#define DCM_GPR_DCMRWD4_FLASH_SCAN_ERR_EN_WIDTH  (1U)
#define DCM_GPR_DCMRWD4_FLASH_SCAN_ERR_EN(x)     (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD4_FLASH_SCAN_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD4_FLASH_SCAN_ERR_EN_MASK)

#define DCM_GPR_DCMRWD4_FLASH_ACCESS_ERR_EN_MASK (0x1000000U)
#define DCM_GPR_DCMRWD4_FLASH_ACCESS_ERR_EN_SHIFT (24U)
#define DCM_GPR_DCMRWD4_FLASH_ACCESS_ERR_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD4_FLASH_ACCESS_ERR_EN(x)   (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD4_FLASH_ACCESS_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD4_FLASH_ACCESS_ERR_EN_MASK)

#define DCM_GPR_DCMRWD4_VDD1P1_GNG_ERR_EN_MASK   (0x4000000U)
#define DCM_GPR_DCMRWD4_VDD1P1_GNG_ERR_EN_SHIFT  (26U)
#define DCM_GPR_DCMRWD4_VDD1P1_GNG_ERR_EN_WIDTH  (1U)
#define DCM_GPR_DCMRWD4_VDD1P1_GNG_ERR_EN(x)     (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD4_VDD1P1_GNG_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD4_VDD1P1_GNG_ERR_EN_MASK)

#define DCM_GPR_DCMRWD4_VDD2P5_GNG_ERR_EN_MASK   (0x8000000U)
#define DCM_GPR_DCMRWD4_VDD2P5_GNG_ERR_EN_SHIFT  (27U)
#define DCM_GPR_DCMRWD4_VDD2P5_GNG_ERR_EN_WIDTH  (1U)
#define DCM_GPR_DCMRWD4_VDD2P5_GNG_ERR_EN(x)     (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD4_VDD2P5_GNG_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD4_VDD2P5_GNG_ERR_EN_MASK)

#define DCM_GPR_DCMRWD4_TEST_ACTIVATION_0_ERR_EN_MASK (0x20000000U)
#define DCM_GPR_DCMRWD4_TEST_ACTIVATION_0_ERR_EN_SHIFT (29U)
#define DCM_GPR_DCMRWD4_TEST_ACTIVATION_0_ERR_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD4_TEST_ACTIVATION_0_ERR_EN(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD4_TEST_ACTIVATION_0_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD4_TEST_ACTIVATION_0_ERR_EN_MASK)

#define DCM_GPR_DCMRWD4_TEST_ACTIVATION_1_ERR_EN_MASK (0x40000000U)
#define DCM_GPR_DCMRWD4_TEST_ACTIVATION_1_ERR_EN_SHIFT (30U)
#define DCM_GPR_DCMRWD4_TEST_ACTIVATION_1_ERR_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD4_TEST_ACTIVATION_1_ERR_EN(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD4_TEST_ACTIVATION_1_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD4_TEST_ACTIVATION_1_ERR_EN_MASK)
/*! @} */

/*! @name DCMRWD5 - Read Write GPR On Destructive Reset Register */
/*! @{ */

#define DCM_GPR_DCMRWD5_INTM_0_ERR_EN_MASK       (0x2U)
#define DCM_GPR_DCMRWD5_INTM_0_ERR_EN_SHIFT      (1U)
#define DCM_GPR_DCMRWD5_INTM_0_ERR_EN_WIDTH      (1U)
#define DCM_GPR_DCMRWD5_INTM_0_ERR_EN(x)         (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD5_INTM_0_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD5_INTM_0_ERR_EN_MASK)

#define DCM_GPR_DCMRWD5_INTM_1_ERR_EN_MASK       (0x4U)
#define DCM_GPR_DCMRWD5_INTM_1_ERR_EN_SHIFT      (2U)
#define DCM_GPR_DCMRWD5_INTM_1_ERR_EN_WIDTH      (1U)
#define DCM_GPR_DCMRWD5_INTM_1_ERR_EN(x)         (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD5_INTM_1_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD5_INTM_1_ERR_EN_MASK)

#define DCM_GPR_DCMRWD5_INTM_2_ERR_EN_MASK       (0x8U)
#define DCM_GPR_DCMRWD5_INTM_2_ERR_EN_SHIFT      (3U)
#define DCM_GPR_DCMRWD5_INTM_2_ERR_EN_WIDTH      (1U)
#define DCM_GPR_DCMRWD5_INTM_2_ERR_EN(x)         (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD5_INTM_2_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD5_INTM_2_ERR_EN_MASK)

#define DCM_GPR_DCMRWD5_INTM_3_ERR_EN_MASK       (0x10U)
#define DCM_GPR_DCMRWD5_INTM_3_ERR_EN_SHIFT      (4U)
#define DCM_GPR_DCMRWD5_INTM_3_ERR_EN_WIDTH      (1U)
#define DCM_GPR_DCMRWD5_INTM_3_ERR_EN(x)         (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD5_INTM_3_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD5_INTM_3_ERR_EN_MASK)

#define DCM_GPR_DCMRWD5_SW_NCF_0_EN_MASK         (0x20U)
#define DCM_GPR_DCMRWD5_SW_NCF_0_EN_SHIFT        (5U)
#define DCM_GPR_DCMRWD5_SW_NCF_0_EN_WIDTH        (1U)
#define DCM_GPR_DCMRWD5_SW_NCF_0_EN(x)           (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD5_SW_NCF_0_EN_SHIFT)) & DCM_GPR_DCMRWD5_SW_NCF_0_EN_MASK)

#define DCM_GPR_DCMRWD5_SW_NCF_1_EN_MASK         (0x40U)
#define DCM_GPR_DCMRWD5_SW_NCF_1_EN_SHIFT        (6U)
#define DCM_GPR_DCMRWD5_SW_NCF_1_EN_WIDTH        (1U)
#define DCM_GPR_DCMRWD5_SW_NCF_1_EN(x)           (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD5_SW_NCF_1_EN_SHIFT)) & DCM_GPR_DCMRWD5_SW_NCF_1_EN_MASK)

#define DCM_GPR_DCMRWD5_SW_NCF_2_EN_MASK         (0x80U)
#define DCM_GPR_DCMRWD5_SW_NCF_2_EN_SHIFT        (7U)
#define DCM_GPR_DCMRWD5_SW_NCF_2_EN_WIDTH        (1U)
#define DCM_GPR_DCMRWD5_SW_NCF_2_EN(x)           (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD5_SW_NCF_2_EN_SHIFT)) & DCM_GPR_DCMRWD5_SW_NCF_2_EN_MASK)

#define DCM_GPR_DCMRWD5_SW_NCF_3_EN_MASK         (0x100U)
#define DCM_GPR_DCMRWD5_SW_NCF_3_EN_SHIFT        (8U)
#define DCM_GPR_DCMRWD5_SW_NCF_3_EN_WIDTH        (1U)
#define DCM_GPR_DCMRWD5_SW_NCF_3_EN(x)           (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD5_SW_NCF_3_EN_SHIFT)) & DCM_GPR_DCMRWD5_SW_NCF_3_EN_MASK)

#define DCM_GPR_DCMRWD5_STCU_NCF_EN_MASK         (0x200U)
#define DCM_GPR_DCMRWD5_STCU_NCF_EN_SHIFT        (9U)
#define DCM_GPR_DCMRWD5_STCU_NCF_EN_WIDTH        (1U)
#define DCM_GPR_DCMRWD5_STCU_NCF_EN(x)           (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD5_STCU_NCF_EN_SHIFT)) & DCM_GPR_DCMRWD5_STCU_NCF_EN_MASK)

#define DCM_GPR_DCMRWD5_MBIST_ACTIVATION_ERR_EN_MASK (0x400U)
#define DCM_GPR_DCMRWD5_MBIST_ACTIVATION_ERR_EN_SHIFT (10U)
#define DCM_GPR_DCMRWD5_MBIST_ACTIVATION_ERR_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD5_MBIST_ACTIVATION_ERR_EN(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD5_MBIST_ACTIVATION_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD5_MBIST_ACTIVATION_ERR_EN_MASK)

#define DCM_GPR_DCMRWD5_STCU_BIST_USER_CF_EN_MASK (0x800U)
#define DCM_GPR_DCMRWD5_STCU_BIST_USER_CF_EN_SHIFT (11U)
#define DCM_GPR_DCMRWD5_STCU_BIST_USER_CF_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD5_STCU_BIST_USER_CF_EN(x)  (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD5_STCU_BIST_USER_CF_EN_SHIFT)) & DCM_GPR_DCMRWD5_STCU_BIST_USER_CF_EN_MASK)

#define DCM_GPR_DCMRWD5_MTR_BUS_ERR_EN_MASK      (0x1000U)
#define DCM_GPR_DCMRWD5_MTR_BUS_ERR_EN_SHIFT     (12U)
#define DCM_GPR_DCMRWD5_MTR_BUS_ERR_EN_WIDTH     (1U)
#define DCM_GPR_DCMRWD5_MTR_BUS_ERR_EN(x)        (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD5_MTR_BUS_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD5_MTR_BUS_ERR_EN_MASK)

#define DCM_GPR_DCMRWD5_DEBUG_ACTIVATION_ERR_EN_MASK (0x2000U)
#define DCM_GPR_DCMRWD5_DEBUG_ACTIVATION_ERR_EN_SHIFT (13U)
#define DCM_GPR_DCMRWD5_DEBUG_ACTIVATION_ERR_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD5_DEBUG_ACTIVATION_ERR_EN(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD5_DEBUG_ACTIVATION_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD5_DEBUG_ACTIVATION_ERR_EN_MASK)

#define DCM_GPR_DCMRWD5_TCM_RDATA_EDC_ERR_EN_MASK (0x4000U)
#define DCM_GPR_DCMRWD5_TCM_RDATA_EDC_ERR_EN_SHIFT (14U)
#define DCM_GPR_DCMRWD5_TCM_RDATA_EDC_ERR_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD5_TCM_RDATA_EDC_ERR_EN(x)  (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD5_TCM_RDATA_EDC_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD5_TCM_RDATA_EDC_ERR_EN_MASK)

#define DCM_GPR_DCMRWD5_MAC_RDATA_EDC_ERR_EN_MASK (0x8000U)
#define DCM_GPR_DCMRWD5_MAC_RDATA_EDC_ERR_EN_SHIFT (15U)
#define DCM_GPR_DCMRWD5_MAC_RDATA_EDC_ERR_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD5_MAC_RDATA_EDC_ERR_EN(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD5_MAC_RDATA_EDC_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD5_MAC_RDATA_EDC_ERR_EN_MASK)

#define DCM_GPR_DCMRWD5_DMA_RDATA_EDC_ERR_EN_MASK (0x20000U)
#define DCM_GPR_DCMRWD5_DMA_RDATA_EDC_ERR_EN_SHIFT (17U)
#define DCM_GPR_DCMRWD5_DMA_RDATA_EDC_ERR_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD5_DMA_RDATA_EDC_ERR_EN(x)  (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD5_DMA_RDATA_EDC_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD5_DMA_RDATA_EDC_ERR_EN_MASK)

#define DCM_GPR_DCMRWD5_CM7_0_AHBP_RDATA_EDC_ERR_EN_MASK (0x100000U)
#define DCM_GPR_DCMRWD5_CM7_0_AHBP_RDATA_EDC_ERR_EN_SHIFT (20U)
#define DCM_GPR_DCMRWD5_CM7_0_AHBP_RDATA_EDC_ERR_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD5_CM7_0_AHBP_RDATA_EDC_ERR_EN(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD5_CM7_0_AHBP_RDATA_EDC_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD5_CM7_0_AHBP_RDATA_EDC_ERR_EN_MASK)

#define DCM_GPR_DCMRWD5_CM7_0_AHBM_RDATA_EDC_ERR_EN_MASK (0x200000U)
#define DCM_GPR_DCMRWD5_CM7_0_AHBM_RDATA_EDC_ERR_EN_SHIFT (21U)
#define DCM_GPR_DCMRWD5_CM7_0_AHBM_RDATA_EDC_ERR_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD5_CM7_0_AHBM_RDATA_EDC_ERR_EN(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD5_CM7_0_AHBM_RDATA_EDC_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD5_CM7_0_AHBM_RDATA_EDC_ERR_EN_MASK)

#define DCM_GPR_DCMRWD5_HSE_RDATA_EDC_ERR_EN_MASK (0x400000U)
#define DCM_GPR_DCMRWD5_HSE_RDATA_EDC_ERR_EN_SHIFT (22U)
#define DCM_GPR_DCMRWD5_HSE_RDATA_EDC_ERR_EN_WIDTH (1U)
#define DCM_GPR_DCMRWD5_HSE_RDATA_EDC_ERR_EN(x)  (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD5_HSE_RDATA_EDC_ERR_EN_SHIFT)) & DCM_GPR_DCMRWD5_HSE_RDATA_EDC_ERR_EN_MASK)
/*! @} */

/*! @name DCMRWD6 - Read Write GPR On Destructive Reset Register */
/*! @{ */

#define DCM_GPR_DCMRWD6_EDMA_DBG_DIS_CM7_0_MASK  (0x1U)
#define DCM_GPR_DCMRWD6_EDMA_DBG_DIS_CM7_0_SHIFT (0U)
#define DCM_GPR_DCMRWD6_EDMA_DBG_DIS_CM7_0_WIDTH (1U)
#define DCM_GPR_DCMRWD6_EDMA_DBG_DIS_CM7_0(x)    (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD6_EDMA_DBG_DIS_CM7_0_SHIFT)) & DCM_GPR_DCMRWD6_EDMA_DBG_DIS_CM7_0_MASK)

#define DCM_GPR_DCMRWD6_FCCU_DBG_DIS_CM7_0_MASK  (0x2U)
#define DCM_GPR_DCMRWD6_FCCU_DBG_DIS_CM7_0_SHIFT (1U)
#define DCM_GPR_DCMRWD6_FCCU_DBG_DIS_CM7_0_WIDTH (1U)
#define DCM_GPR_DCMRWD6_FCCU_DBG_DIS_CM7_0(x)    (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD6_FCCU_DBG_DIS_CM7_0_SHIFT)) & DCM_GPR_DCMRWD6_FCCU_DBG_DIS_CM7_0_MASK)

#define DCM_GPR_DCMRWD6_LCU0_DBG_DIS_CM7_0_MASK  (0x4U)
#define DCM_GPR_DCMRWD6_LCU0_DBG_DIS_CM7_0_SHIFT (2U)
#define DCM_GPR_DCMRWD6_LCU0_DBG_DIS_CM7_0_WIDTH (1U)
#define DCM_GPR_DCMRWD6_LCU0_DBG_DIS_CM7_0(x)    (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD6_LCU0_DBG_DIS_CM7_0_SHIFT)) & DCM_GPR_DCMRWD6_LCU0_DBG_DIS_CM7_0_MASK)

#define DCM_GPR_DCMRWD6_LCU1_DBG_DIS_CM7_0_MASK  (0x8U)
#define DCM_GPR_DCMRWD6_LCU1_DBG_DIS_CM7_0_SHIFT (3U)
#define DCM_GPR_DCMRWD6_LCU1_DBG_DIS_CM7_0_WIDTH (1U)
#define DCM_GPR_DCMRWD6_LCU1_DBG_DIS_CM7_0(x)    (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD6_LCU1_DBG_DIS_CM7_0_SHIFT)) & DCM_GPR_DCMRWD6_LCU1_DBG_DIS_CM7_0_MASK)

#define DCM_GPR_DCMRWD6_EMIOS0_DBG_DIS_CM7_0_MASK (0x10U)
#define DCM_GPR_DCMRWD6_EMIOS0_DBG_DIS_CM7_0_SHIFT (4U)
#define DCM_GPR_DCMRWD6_EMIOS0_DBG_DIS_CM7_0_WIDTH (1U)
#define DCM_GPR_DCMRWD6_EMIOS0_DBG_DIS_CM7_0(x)  (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD6_EMIOS0_DBG_DIS_CM7_0_SHIFT)) & DCM_GPR_DCMRWD6_EMIOS0_DBG_DIS_CM7_0_MASK)

#define DCM_GPR_DCMRWD6_EMIOS1_DBG_DIS_CM7_0_MASK (0x20U)
#define DCM_GPR_DCMRWD6_EMIOS1_DBG_DIS_CM7_0_SHIFT (5U)
#define DCM_GPR_DCMRWD6_EMIOS1_DBG_DIS_CM7_0_WIDTH (1U)
#define DCM_GPR_DCMRWD6_EMIOS1_DBG_DIS_CM7_0(x)  (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD6_EMIOS1_DBG_DIS_CM7_0_SHIFT)) & DCM_GPR_DCMRWD6_EMIOS1_DBG_DIS_CM7_0_MASK)

#define DCM_GPR_DCMRWD6_EMIOS2_DBG_DIS_CM7_0_MASK (0x40U)
#define DCM_GPR_DCMRWD6_EMIOS2_DBG_DIS_CM7_0_SHIFT (6U)
#define DCM_GPR_DCMRWD6_EMIOS2_DBG_DIS_CM7_0_WIDTH (1U)
#define DCM_GPR_DCMRWD6_EMIOS2_DBG_DIS_CM7_0(x)  (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD6_EMIOS2_DBG_DIS_CM7_0_SHIFT)) & DCM_GPR_DCMRWD6_EMIOS2_DBG_DIS_CM7_0_MASK)

#define DCM_GPR_DCMRWD6_RTC_DBG_DIS_CM7_0_MASK   (0x80U)
#define DCM_GPR_DCMRWD6_RTC_DBG_DIS_CM7_0_SHIFT  (7U)
#define DCM_GPR_DCMRWD6_RTC_DBG_DIS_CM7_0_WIDTH  (1U)
#define DCM_GPR_DCMRWD6_RTC_DBG_DIS_CM7_0(x)     (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD6_RTC_DBG_DIS_CM7_0_SHIFT)) & DCM_GPR_DCMRWD6_RTC_DBG_DIS_CM7_0_MASK)

#define DCM_GPR_DCMRWD6_SWT0_DBG_DIS_CM7_0_MASK  (0x100U)
#define DCM_GPR_DCMRWD6_SWT0_DBG_DIS_CM7_0_SHIFT (8U)
#define DCM_GPR_DCMRWD6_SWT0_DBG_DIS_CM7_0_WIDTH (1U)
#define DCM_GPR_DCMRWD6_SWT0_DBG_DIS_CM7_0(x)    (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD6_SWT0_DBG_DIS_CM7_0_SHIFT)) & DCM_GPR_DCMRWD6_SWT0_DBG_DIS_CM7_0_MASK)

#define DCM_GPR_DCMRWD6_SWT1_DBG_DIS_CM7_0_MASK  (0x200U)
#define DCM_GPR_DCMRWD6_SWT1_DBG_DIS_CM7_0_SHIFT (9U)
#define DCM_GPR_DCMRWD6_SWT1_DBG_DIS_CM7_0_WIDTH (1U)
#define DCM_GPR_DCMRWD6_SWT1_DBG_DIS_CM7_0(x)    (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD6_SWT1_DBG_DIS_CM7_0_SHIFT)) & DCM_GPR_DCMRWD6_SWT1_DBG_DIS_CM7_0_MASK)

#define DCM_GPR_DCMRWD6_STM0_DBG_DIS_CM7_0_MASK  (0x400U)
#define DCM_GPR_DCMRWD6_STM0_DBG_DIS_CM7_0_SHIFT (10U)
#define DCM_GPR_DCMRWD6_STM0_DBG_DIS_CM7_0_WIDTH (1U)
#define DCM_GPR_DCMRWD6_STM0_DBG_DIS_CM7_0(x)    (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD6_STM0_DBG_DIS_CM7_0_SHIFT)) & DCM_GPR_DCMRWD6_STM0_DBG_DIS_CM7_0_MASK)

#define DCM_GPR_DCMRWD6_STM1_DBG_DIS_CM7_0_MASK  (0x800U)
#define DCM_GPR_DCMRWD6_STM1_DBG_DIS_CM7_0_SHIFT (11U)
#define DCM_GPR_DCMRWD6_STM1_DBG_DIS_CM7_0_WIDTH (1U)
#define DCM_GPR_DCMRWD6_STM1_DBG_DIS_CM7_0(x)    (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD6_STM1_DBG_DIS_CM7_0_SHIFT)) & DCM_GPR_DCMRWD6_STM1_DBG_DIS_CM7_0_MASK)

#define DCM_GPR_DCMRWD6_PIT0_DBG_DIS_CM7_0_MASK  (0x1000U)
#define DCM_GPR_DCMRWD6_PIT0_DBG_DIS_CM7_0_SHIFT (12U)
#define DCM_GPR_DCMRWD6_PIT0_DBG_DIS_CM7_0_WIDTH (1U)
#define DCM_GPR_DCMRWD6_PIT0_DBG_DIS_CM7_0(x)    (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD6_PIT0_DBG_DIS_CM7_0_SHIFT)) & DCM_GPR_DCMRWD6_PIT0_DBG_DIS_CM7_0_MASK)

#define DCM_GPR_DCMRWD6_PIT1_DBG_DIS_CM7_0_MASK  (0x2000U)
#define DCM_GPR_DCMRWD6_PIT1_DBG_DIS_CM7_0_SHIFT (13U)
#define DCM_GPR_DCMRWD6_PIT1_DBG_DIS_CM7_0_WIDTH (1U)
#define DCM_GPR_DCMRWD6_PIT1_DBG_DIS_CM7_0(x)    (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD6_PIT1_DBG_DIS_CM7_0_SHIFT)) & DCM_GPR_DCMRWD6_PIT1_DBG_DIS_CM7_0_MASK)

#define DCM_GPR_DCMRWD6_PIT2_DBG_DIS_CM7_0_MASK  (0x4000U)
#define DCM_GPR_DCMRWD6_PIT2_DBG_DIS_CM7_0_SHIFT (14U)
#define DCM_GPR_DCMRWD6_PIT2_DBG_DIS_CM7_0_WIDTH (1U)
#define DCM_GPR_DCMRWD6_PIT2_DBG_DIS_CM7_0(x)    (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD6_PIT2_DBG_DIS_CM7_0_SHIFT)) & DCM_GPR_DCMRWD6_PIT2_DBG_DIS_CM7_0_MASK)

#define DCM_GPR_DCMRWD6_LPSPI0_DBG_DIS_CM7_0_MASK (0x8000U)
#define DCM_GPR_DCMRWD6_LPSPI0_DBG_DIS_CM7_0_SHIFT (15U)
#define DCM_GPR_DCMRWD6_LPSPI0_DBG_DIS_CM7_0_WIDTH (1U)
#define DCM_GPR_DCMRWD6_LPSPI0_DBG_DIS_CM7_0(x)  (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD6_LPSPI0_DBG_DIS_CM7_0_SHIFT)) & DCM_GPR_DCMRWD6_LPSPI0_DBG_DIS_CM7_0_MASK)

#define DCM_GPR_DCMRWD6_LPSPI1_DBG_DIS_CM7_0_MASK (0x10000U)
#define DCM_GPR_DCMRWD6_LPSPI1_DBG_DIS_CM7_0_SHIFT (16U)
#define DCM_GPR_DCMRWD6_LPSPI1_DBG_DIS_CM7_0_WIDTH (1U)
#define DCM_GPR_DCMRWD6_LPSPI1_DBG_DIS_CM7_0(x)  (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD6_LPSPI1_DBG_DIS_CM7_0_SHIFT)) & DCM_GPR_DCMRWD6_LPSPI1_DBG_DIS_CM7_0_MASK)

#define DCM_GPR_DCMRWD6_LPSPI2_DBG_DIS_CM7_0_MASK (0x20000U)
#define DCM_GPR_DCMRWD6_LPSPI2_DBG_DIS_CM7_0_SHIFT (17U)
#define DCM_GPR_DCMRWD6_LPSPI2_DBG_DIS_CM7_0_WIDTH (1U)
#define DCM_GPR_DCMRWD6_LPSPI2_DBG_DIS_CM7_0(x)  (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD6_LPSPI2_DBG_DIS_CM7_0_SHIFT)) & DCM_GPR_DCMRWD6_LPSPI2_DBG_DIS_CM7_0_MASK)

#define DCM_GPR_DCMRWD6_LPSPI3_DBG_DIS_CM7_0_MASK (0x40000U)
#define DCM_GPR_DCMRWD6_LPSPI3_DBG_DIS_CM7_0_SHIFT (18U)
#define DCM_GPR_DCMRWD6_LPSPI3_DBG_DIS_CM7_0_WIDTH (1U)
#define DCM_GPR_DCMRWD6_LPSPI3_DBG_DIS_CM7_0(x)  (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD6_LPSPI3_DBG_DIS_CM7_0_SHIFT)) & DCM_GPR_DCMRWD6_LPSPI3_DBG_DIS_CM7_0_MASK)

#define DCM_GPR_DCMRWD6_LPSPI4_DBG_DIS_CM7_0_MASK (0x80000U)
#define DCM_GPR_DCMRWD6_LPSPI4_DBG_DIS_CM7_0_SHIFT (19U)
#define DCM_GPR_DCMRWD6_LPSPI4_DBG_DIS_CM7_0_WIDTH (1U)
#define DCM_GPR_DCMRWD6_LPSPI4_DBG_DIS_CM7_0(x)  (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD6_LPSPI4_DBG_DIS_CM7_0_SHIFT)) & DCM_GPR_DCMRWD6_LPSPI4_DBG_DIS_CM7_0_MASK)

#define DCM_GPR_DCMRWD6_LPSPI5_DBG_DIS_CM7_0_MASK (0x100000U)
#define DCM_GPR_DCMRWD6_LPSPI5_DBG_DIS_CM7_0_SHIFT (20U)
#define DCM_GPR_DCMRWD6_LPSPI5_DBG_DIS_CM7_0_WIDTH (1U)
#define DCM_GPR_DCMRWD6_LPSPI5_DBG_DIS_CM7_0(x)  (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD6_LPSPI5_DBG_DIS_CM7_0_SHIFT)) & DCM_GPR_DCMRWD6_LPSPI5_DBG_DIS_CM7_0_MASK)

#define DCM_GPR_DCMRWD6_LPI2C0_DBG_DIS_CM7_0_MASK (0x200000U)
#define DCM_GPR_DCMRWD6_LPI2C0_DBG_DIS_CM7_0_SHIFT (21U)
#define DCM_GPR_DCMRWD6_LPI2C0_DBG_DIS_CM7_0_WIDTH (1U)
#define DCM_GPR_DCMRWD6_LPI2C0_DBG_DIS_CM7_0(x)  (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD6_LPI2C0_DBG_DIS_CM7_0_SHIFT)) & DCM_GPR_DCMRWD6_LPI2C0_DBG_DIS_CM7_0_MASK)

#define DCM_GPR_DCMRWD6_LPI2C1_DBG_DIS_CM7_0_MASK (0x400000U)
#define DCM_GPR_DCMRWD6_LPI2C1_DBG_DIS_CM7_0_SHIFT (22U)
#define DCM_GPR_DCMRWD6_LPI2C1_DBG_DIS_CM7_0_WIDTH (1U)
#define DCM_GPR_DCMRWD6_LPI2C1_DBG_DIS_CM7_0(x)  (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD6_LPI2C1_DBG_DIS_CM7_0_SHIFT)) & DCM_GPR_DCMRWD6_LPI2C1_DBG_DIS_CM7_0_MASK)

#define DCM_GPR_DCMRWD6_FLEXIO_DBG_DIS_CM7_0_MASK (0x800000U)
#define DCM_GPR_DCMRWD6_FLEXIO_DBG_DIS_CM7_0_SHIFT (23U)
#define DCM_GPR_DCMRWD6_FLEXIO_DBG_DIS_CM7_0_WIDTH (1U)
#define DCM_GPR_DCMRWD6_FLEXIO_DBG_DIS_CM7_0(x)  (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD6_FLEXIO_DBG_DIS_CM7_0_SHIFT)) & DCM_GPR_DCMRWD6_FLEXIO_DBG_DIS_CM7_0_MASK)

#define DCM_GPR_DCMRWD6_FLEXCAN0_DBG_DIS_CM7_0_MASK (0x1000000U)
#define DCM_GPR_DCMRWD6_FLEXCAN0_DBG_DIS_CM7_0_SHIFT (24U)
#define DCM_GPR_DCMRWD6_FLEXCAN0_DBG_DIS_CM7_0_WIDTH (1U)
#define DCM_GPR_DCMRWD6_FLEXCAN0_DBG_DIS_CM7_0(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD6_FLEXCAN0_DBG_DIS_CM7_0_SHIFT)) & DCM_GPR_DCMRWD6_FLEXCAN0_DBG_DIS_CM7_0_MASK)

#define DCM_GPR_DCMRWD6_FLEXCAN1_DBG_DIS_CM7_0_MASK (0x2000000U)
#define DCM_GPR_DCMRWD6_FLEXCAN1_DBG_DIS_CM7_0_SHIFT (25U)
#define DCM_GPR_DCMRWD6_FLEXCAN1_DBG_DIS_CM7_0_WIDTH (1U)
#define DCM_GPR_DCMRWD6_FLEXCAN1_DBG_DIS_CM7_0(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD6_FLEXCAN1_DBG_DIS_CM7_0_SHIFT)) & DCM_GPR_DCMRWD6_FLEXCAN1_DBG_DIS_CM7_0_MASK)

#define DCM_GPR_DCMRWD6_FLEXCAN2_DBG_DIS_CM7_0_MASK (0x4000000U)
#define DCM_GPR_DCMRWD6_FLEXCAN2_DBG_DIS_CM7_0_SHIFT (26U)
#define DCM_GPR_DCMRWD6_FLEXCAN2_DBG_DIS_CM7_0_WIDTH (1U)
#define DCM_GPR_DCMRWD6_FLEXCAN2_DBG_DIS_CM7_0(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD6_FLEXCAN2_DBG_DIS_CM7_0_SHIFT)) & DCM_GPR_DCMRWD6_FLEXCAN2_DBG_DIS_CM7_0_MASK)

#define DCM_GPR_DCMRWD6_FLEXCAN3_DBG_DIS_CM7_0_MASK (0x8000000U)
#define DCM_GPR_DCMRWD6_FLEXCAN3_DBG_DIS_CM7_0_SHIFT (27U)
#define DCM_GPR_DCMRWD6_FLEXCAN3_DBG_DIS_CM7_0_WIDTH (1U)
#define DCM_GPR_DCMRWD6_FLEXCAN3_DBG_DIS_CM7_0(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD6_FLEXCAN3_DBG_DIS_CM7_0_SHIFT)) & DCM_GPR_DCMRWD6_FLEXCAN3_DBG_DIS_CM7_0_MASK)

#define DCM_GPR_DCMRWD6_FLEXCAN4_DBG_DIS_CM7_0_MASK (0x10000000U)
#define DCM_GPR_DCMRWD6_FLEXCAN4_DBG_DIS_CM7_0_SHIFT (28U)
#define DCM_GPR_DCMRWD6_FLEXCAN4_DBG_DIS_CM7_0_WIDTH (1U)
#define DCM_GPR_DCMRWD6_FLEXCAN4_DBG_DIS_CM7_0(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD6_FLEXCAN4_DBG_DIS_CM7_0_SHIFT)) & DCM_GPR_DCMRWD6_FLEXCAN4_DBG_DIS_CM7_0_MASK)

#define DCM_GPR_DCMRWD6_FLEXCAN5_DBG_DIS_CM7_0_MASK (0x20000000U)
#define DCM_GPR_DCMRWD6_FLEXCAN5_DBG_DIS_CM7_0_SHIFT (29U)
#define DCM_GPR_DCMRWD6_FLEXCAN5_DBG_DIS_CM7_0_WIDTH (1U)
#define DCM_GPR_DCMRWD6_FLEXCAN5_DBG_DIS_CM7_0(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD6_FLEXCAN5_DBG_DIS_CM7_0_SHIFT)) & DCM_GPR_DCMRWD6_FLEXCAN5_DBG_DIS_CM7_0_MASK)

#define DCM_GPR_DCMRWD6_SAI0_DBG_DIS_CM7_0_MASK  (0x40000000U)
#define DCM_GPR_DCMRWD6_SAI0_DBG_DIS_CM7_0_SHIFT (30U)
#define DCM_GPR_DCMRWD6_SAI0_DBG_DIS_CM7_0_WIDTH (1U)
#define DCM_GPR_DCMRWD6_SAI0_DBG_DIS_CM7_0(x)    (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD6_SAI0_DBG_DIS_CM7_0_SHIFT)) & DCM_GPR_DCMRWD6_SAI0_DBG_DIS_CM7_0_MASK)

#define DCM_GPR_DCMRWD6_SAI1_DBG_DIS_CM7_0_MASK  (0x80000000U)
#define DCM_GPR_DCMRWD6_SAI1_DBG_DIS_CM7_0_SHIFT (31U)
#define DCM_GPR_DCMRWD6_SAI1_DBG_DIS_CM7_0_WIDTH (1U)
#define DCM_GPR_DCMRWD6_SAI1_DBG_DIS_CM7_0(x)    (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWD6_SAI1_DBG_DIS_CM7_0_SHIFT)) & DCM_GPR_DCMRWD6_SAI1_DBG_DIS_CM7_0_MASK)
/*! @} */

/*! @name DCMRWF1 - Read Write GPR On Functional Reset Register */
/*! @{ */

#define DCM_GPR_DCMRWF1_CAN_TIMESTAMP_SEL_MASK   (0x1U)
#define DCM_GPR_DCMRWF1_CAN_TIMESTAMP_SEL_SHIFT  (0U)
#define DCM_GPR_DCMRWF1_CAN_TIMESTAMP_SEL_WIDTH  (1U)
#define DCM_GPR_DCMRWF1_CAN_TIMESTAMP_SEL(x)     (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWF1_CAN_TIMESTAMP_SEL_SHIFT)) & DCM_GPR_DCMRWF1_CAN_TIMESTAMP_SEL_MASK)

#define DCM_GPR_DCMRWF1_CAN_TIMESTAMP_EN_MASK    (0x2U)
#define DCM_GPR_DCMRWF1_CAN_TIMESTAMP_EN_SHIFT   (1U)
#define DCM_GPR_DCMRWF1_CAN_TIMESTAMP_EN_WIDTH   (1U)
#define DCM_GPR_DCMRWF1_CAN_TIMESTAMP_EN(x)      (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWF1_CAN_TIMESTAMP_EN_SHIFT)) & DCM_GPR_DCMRWF1_CAN_TIMESTAMP_EN_MASK)

#define DCM_GPR_DCMRWF1_FCCU_SW_NCF0_MASK        (0x4U)
#define DCM_GPR_DCMRWF1_FCCU_SW_NCF0_SHIFT       (2U)
#define DCM_GPR_DCMRWF1_FCCU_SW_NCF0_WIDTH       (1U)
#define DCM_GPR_DCMRWF1_FCCU_SW_NCF0(x)          (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWF1_FCCU_SW_NCF0_SHIFT)) & DCM_GPR_DCMRWF1_FCCU_SW_NCF0_MASK)

#define DCM_GPR_DCMRWF1_FCCU_SW_NCF1_MASK        (0x8U)
#define DCM_GPR_DCMRWF1_FCCU_SW_NCF1_SHIFT       (3U)
#define DCM_GPR_DCMRWF1_FCCU_SW_NCF1_WIDTH       (1U)
#define DCM_GPR_DCMRWF1_FCCU_SW_NCF1(x)          (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWF1_FCCU_SW_NCF1_SHIFT)) & DCM_GPR_DCMRWF1_FCCU_SW_NCF1_MASK)

#define DCM_GPR_DCMRWF1_FCCU_SW_NCF2_MASK        (0x10U)
#define DCM_GPR_DCMRWF1_FCCU_SW_NCF2_SHIFT       (4U)
#define DCM_GPR_DCMRWF1_FCCU_SW_NCF2_WIDTH       (1U)
#define DCM_GPR_DCMRWF1_FCCU_SW_NCF2(x)          (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWF1_FCCU_SW_NCF2_SHIFT)) & DCM_GPR_DCMRWF1_FCCU_SW_NCF2_MASK)

#define DCM_GPR_DCMRWF1_FCCU_SW_NCF3_MASK        (0x20U)
#define DCM_GPR_DCMRWF1_FCCU_SW_NCF3_SHIFT       (5U)
#define DCM_GPR_DCMRWF1_FCCU_SW_NCF3_WIDTH       (1U)
#define DCM_GPR_DCMRWF1_FCCU_SW_NCF3(x)          (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWF1_FCCU_SW_NCF3_SHIFT)) & DCM_GPR_DCMRWF1_FCCU_SW_NCF3_MASK)

#define DCM_GPR_DCMRWF1_MAC_CONF_SEL_MASK       (0xC0U)
#define DCM_GPR_DCMRWF1_MAC_CONF_SEL_SHIFT      (6U)
#define DCM_GPR_DCMRWF1_MAC_CONF_SEL_WIDTH      (2U)
#define DCM_GPR_DCMRWF1_MAC_CONF_SEL(x)         (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWF1_MAC_CONF_SEL_SHIFT)) & DCM_GPR_DCMRWF1_MAC_CONF_SEL_MASK)

#define DCM_GPR_DCMRWF1_VDD_HV_B_IO_CTRL_LATCH_MASK (0x8000U)
#define DCM_GPR_DCMRWF1_VDD_HV_B_IO_CTRL_LATCH_SHIFT (15U)
#define DCM_GPR_DCMRWF1_VDD_HV_B_IO_CTRL_LATCH_WIDTH (1U)
#define DCM_GPR_DCMRWF1_VDD_HV_B_IO_CTRL_LATCH(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWF1_VDD_HV_B_IO_CTRL_LATCH_SHIFT)) & DCM_GPR_DCMRWF1_VDD_HV_B_IO_CTRL_LATCH_MASK)

#define DCM_GPR_DCMRWF1_STANDBY_IO_CONFIG_MASK   (0x10000U)
#define DCM_GPR_DCMRWF1_STANDBY_IO_CONFIG_SHIFT  (16U)
#define DCM_GPR_DCMRWF1_STANDBY_IO_CONFIG_WIDTH  (1U)
#define DCM_GPR_DCMRWF1_STANDBY_IO_CONFIG(x)     (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWF1_STANDBY_IO_CONFIG_SHIFT)) & DCM_GPR_DCMRWF1_STANDBY_IO_CONFIG_MASK)

#define DCM_GPR_DCMRWF1_SUPPLY_MON_EN_MASK       (0x100000U)
#define DCM_GPR_DCMRWF1_SUPPLY_MON_EN_SHIFT      (20U)
#define DCM_GPR_DCMRWF1_SUPPLY_MON_EN_WIDTH      (1U)
#define DCM_GPR_DCMRWF1_SUPPLY_MON_EN(x)         (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWF1_SUPPLY_MON_EN_SHIFT)) & DCM_GPR_DCMRWF1_SUPPLY_MON_EN_MASK)

#define DCM_GPR_DCMRWF1_SUPPLY_MON_SEL_MASK      (0xE00000U)
#define DCM_GPR_DCMRWF1_SUPPLY_MON_SEL_SHIFT     (21U)
#define DCM_GPR_DCMRWF1_SUPPLY_MON_SEL_WIDTH     (3U)
#define DCM_GPR_DCMRWF1_SUPPLY_MON_SEL(x)        (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWF1_SUPPLY_MON_SEL_SHIFT)) & DCM_GPR_DCMRWF1_SUPPLY_MON_SEL_MASK)

#define DCM_GPR_DCMRWF1_VSS_LV_ANMUX_EN_MASK     (0x1000000U)
#define DCM_GPR_DCMRWF1_VSS_LV_ANMUX_EN_SHIFT    (24U)
#define DCM_GPR_DCMRWF1_VSS_LV_ANMUX_EN_WIDTH    (1U)
#define DCM_GPR_DCMRWF1_VSS_LV_ANMUX_EN(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWF1_VSS_LV_ANMUX_EN_SHIFT)) & DCM_GPR_DCMRWF1_VSS_LV_ANMUX_EN_MASK)

#define DCM_GPR_DCMRWF1_VDD_HV_A_VLT_DVDR_EN_MASK (0x2000000U)
#define DCM_GPR_DCMRWF1_VDD_HV_A_VLT_DVDR_EN_SHIFT (25U)
#define DCM_GPR_DCMRWF1_VDD_HV_A_VLT_DVDR_EN_WIDTH (1U)
#define DCM_GPR_DCMRWF1_VDD_HV_A_VLT_DVDR_EN(x)  (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWF1_VDD_HV_A_VLT_DVDR_EN_SHIFT)) & DCM_GPR_DCMRWF1_VDD_HV_A_VLT_DVDR_EN_MASK)

#define DCM_GPR_DCMRWF1_VDD_HV_B_VLT_DVDR_EN_MASK (0x4000000U)
#define DCM_GPR_DCMRWF1_VDD_HV_B_VLT_DVDR_EN_SHIFT (26U)
#define DCM_GPR_DCMRWF1_VDD_HV_B_VLT_DVDR_EN_WIDTH (1U)
#define DCM_GPR_DCMRWF1_VDD_HV_B_VLT_DVDR_EN(x)  (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWF1_VDD_HV_B_VLT_DVDR_EN_SHIFT)) & DCM_GPR_DCMRWF1_VDD_HV_B_VLT_DVDR_EN_MASK)

#define DCM_GPR_DCMRWF1_VDD_1_5_VLT_DVDR_EN_MASK (0x8000000U)
#define DCM_GPR_DCMRWF1_VDD_1_5_VLT_DVDR_EN_SHIFT (27U)
#define DCM_GPR_DCMRWF1_VDD_1_5_VLT_DVDR_EN_WIDTH (1U)
#define DCM_GPR_DCMRWF1_VDD_1_5_VLT_DVDR_EN(x)   (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWF1_VDD_1_5_VLT_DVDR_EN_SHIFT)) & DCM_GPR_DCMRWF1_VDD_1_5_VLT_DVDR_EN_MASK)
/*! @} */

/*! @name DCMRWF2 - Read Write GPR On Functional Reset Register */
/*! @{ */

#define DCM_GPR_DCMRWF2_DCM_SCAN_BYP_STDBY_EXT_MASK (0x8U)
#define DCM_GPR_DCMRWF2_DCM_SCAN_BYP_STDBY_EXT_SHIFT (3U)
#define DCM_GPR_DCMRWF2_DCM_SCAN_BYP_STDBY_EXT_WIDTH (1U)
#define DCM_GPR_DCMRWF2_DCM_SCAN_BYP_STDBY_EXT(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWF2_DCM_SCAN_BYP_STDBY_EXT_SHIFT)) & DCM_GPR_DCMRWF2_DCM_SCAN_BYP_STDBY_EXT_MASK)

#define DCM_GPR_DCMRWF2_FIRC_TRIM_BYP_STDBY_EXT_MASK (0x10U)
#define DCM_GPR_DCMRWF2_FIRC_TRIM_BYP_STDBY_EXT_SHIFT (4U)
#define DCM_GPR_DCMRWF2_FIRC_TRIM_BYP_STDBY_EXT_WIDTH (1U)
#define DCM_GPR_DCMRWF2_FIRC_TRIM_BYP_STDBY_EXT(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWF2_FIRC_TRIM_BYP_STDBY_EXT_SHIFT)) & DCM_GPR_DCMRWF2_FIRC_TRIM_BYP_STDBY_EXT_MASK)

#define DCM_GPR_DCMRWF2_PMC_TRIM_RGM_DCF_BYP_STDBY_EXT_MASK (0x20U)
#define DCM_GPR_DCMRWF2_PMC_TRIM_RGM_DCF_BYP_STDBY_EXT_SHIFT (5U)
#define DCM_GPR_DCMRWF2_PMC_TRIM_RGM_DCF_BYP_STDBY_EXT_WIDTH (1U)
#define DCM_GPR_DCMRWF2_PMC_TRIM_RGM_DCF_BYP_STDBY_EXT(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWF2_PMC_TRIM_RGM_DCF_BYP_STDBY_EXT_SHIFT)) & DCM_GPR_DCMRWF2_PMC_TRIM_RGM_DCF_BYP_STDBY_EXT_MASK)

#define DCM_GPR_DCMRWF2_SIRC_TRIM_BYP_STDBY_EXT_MASK (0x40U)
#define DCM_GPR_DCMRWF2_SIRC_TRIM_BYP_STDBY_EXT_SHIFT (6U)
#define DCM_GPR_DCMRWF2_SIRC_TRIM_BYP_STDBY_EXT_WIDTH (1U)
#define DCM_GPR_DCMRWF2_SIRC_TRIM_BYP_STDBY_EXT(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWF2_SIRC_TRIM_BYP_STDBY_EXT_SHIFT)) & DCM_GPR_DCMRWF2_SIRC_TRIM_BYP_STDBY_EXT_MASK)

#define DCM_GPR_DCMRWF2_HSE_GSKT_BYPASS_MASK     (0x10000U)
#define DCM_GPR_DCMRWF2_HSE_GSKT_BYPASS_SHIFT    (16U)
#define DCM_GPR_DCMRWF2_HSE_GSKT_BYPASS_WIDTH    (1U)
#define DCM_GPR_DCMRWF2_HSE_GSKT_BYPASS(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWF2_HSE_GSKT_BYPASS_SHIFT)) & DCM_GPR_DCMRWF2_HSE_GSKT_BYPASS_MASK)
/*! @} */

/*! @name DCMRWF4 - Read Write GPR On Functional Reset Register */
/*! @{ */

#define DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC0_S8_MASK (0x2U)
#define DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC0_S8_SHIFT (1U)
#define DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC0_S8_WIDTH (1U)
#define DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC0_S8(x)   (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC0_S8_SHIFT)) & DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC0_S8_MASK)

#define DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC0_S9_MASK (0x4U)
#define DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC0_S9_SHIFT (2U)
#define DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC0_S9_WIDTH (1U)
#define DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC0_S9(x)   (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC0_S9_SHIFT)) & DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC0_S9_MASK)

#define DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC1_S14_MASK (0x8U)
#define DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC1_S14_SHIFT (3U)
#define DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC1_S14_WIDTH (1U)
#define DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC1_S14(x)  (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC1_S14_SHIFT)) & DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC1_S14_MASK)

#define DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC1_S15_MASK (0x10U)
#define DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC1_S15_SHIFT (4U)
#define DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC1_S15_WIDTH (1U)
#define DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC1_S15(x)  (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC1_S15_SHIFT)) & DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC1_S15_MASK)

#define DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC1_S22_MASK (0x20U)
#define DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC1_S22_SHIFT (5U)
#define DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC1_S22_WIDTH (1U)
#define DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC1_S22(x)  (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC1_S22_SHIFT)) & DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC1_S22_MASK)

#define DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC1_S23_MASK (0x40U)
#define DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC1_S23_SHIFT (6U)
#define DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC1_S23_WIDTH (1U)
#define DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC1_S23(x)  (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC1_S23_SHIFT)) & DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC1_S23_MASK)

#define DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC2_S8_MASK (0x200U)
#define DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC2_S8_SHIFT (9U)
#define DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC2_S8_WIDTH (1U)
#define DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC2_S8(x)   (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC2_S8_SHIFT)) & DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC2_S8_MASK)

#define DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC2_S9_MASK (0x400U)
#define DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC2_S9_SHIFT (10U)
#define DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC2_S9_WIDTH (1U)
#define DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC2_S9(x)   (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC2_S9_SHIFT)) & DCM_GPR_DCMRWF4_MUX_MODE_EN_ADC2_S9_MASK)

#define DCM_GPR_DCMRWF4_GLITCH_FIL_TRG_IN0_BYP_MASK (0x2000U)
#define DCM_GPR_DCMRWF4_GLITCH_FIL_TRG_IN0_BYP_SHIFT (13U)
#define DCM_GPR_DCMRWF4_GLITCH_FIL_TRG_IN0_BYP_WIDTH (1U)
#define DCM_GPR_DCMRWF4_GLITCH_FIL_TRG_IN0_BYP(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWF4_GLITCH_FIL_TRG_IN0_BYP_SHIFT)) & DCM_GPR_DCMRWF4_GLITCH_FIL_TRG_IN0_BYP_MASK)

#define DCM_GPR_DCMRWF4_GLITCH_FIL_TRG_IN1_BYP_MASK (0x4000U)
#define DCM_GPR_DCMRWF4_GLITCH_FIL_TRG_IN1_BYP_SHIFT (14U)
#define DCM_GPR_DCMRWF4_GLITCH_FIL_TRG_IN1_BYP_WIDTH (1U)
#define DCM_GPR_DCMRWF4_GLITCH_FIL_TRG_IN1_BYP(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWF4_GLITCH_FIL_TRG_IN1_BYP_SHIFT)) & DCM_GPR_DCMRWF4_GLITCH_FIL_TRG_IN1_BYP_MASK)

#define DCM_GPR_DCMRWF4_GLITCH_FIL_TRG_IN2_BYP_MASK (0x8000U)
#define DCM_GPR_DCMRWF4_GLITCH_FIL_TRG_IN2_BYP_SHIFT (15U)
#define DCM_GPR_DCMRWF4_GLITCH_FIL_TRG_IN2_BYP_WIDTH (1U)
#define DCM_GPR_DCMRWF4_GLITCH_FIL_TRG_IN2_BYP(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWF4_GLITCH_FIL_TRG_IN2_BYP_SHIFT)) & DCM_GPR_DCMRWF4_GLITCH_FIL_TRG_IN2_BYP_MASK)

#define DCM_GPR_DCMRWF4_GLITCH_FIL_TRG_IN3_BYP_MASK (0x10000U)
#define DCM_GPR_DCMRWF4_GLITCH_FIL_TRG_IN3_BYP_SHIFT (16U)
#define DCM_GPR_DCMRWF4_GLITCH_FIL_TRG_IN3_BYP_WIDTH (1U)
#define DCM_GPR_DCMRWF4_GLITCH_FIL_TRG_IN3_BYP(x) (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWF4_GLITCH_FIL_TRG_IN3_BYP_SHIFT)) & DCM_GPR_DCMRWF4_GLITCH_FIL_TRG_IN3_BYP_MASK)

#define DCM_GPR_DCMRWF4_CM7_0_CPUWAIT_MASK       (0x20000U)
#define DCM_GPR_DCMRWF4_CM7_0_CPUWAIT_SHIFT      (17U)
#define DCM_GPR_DCMRWF4_CM7_0_CPUWAIT_WIDTH      (1U)
#define DCM_GPR_DCMRWF4_CM7_0_CPUWAIT(x)         (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWF4_CM7_0_CPUWAIT_SHIFT)) & DCM_GPR_DCMRWF4_CM7_0_CPUWAIT_MASK)
/*! @} */

/*! @name DCMRWF5 - Read Write GPR On Functional Reset Register */
/*! @{ */

#define DCM_GPR_DCMRWF5_BOOT_MODE_MASK           (0x1U)
#define DCM_GPR_DCMRWF5_BOOT_MODE_SHIFT          (0U)
#define DCM_GPR_DCMRWF5_BOOT_MODE_WIDTH          (1U)
#define DCM_GPR_DCMRWF5_BOOT_MODE(x)             (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWF5_BOOT_MODE_SHIFT)) & DCM_GPR_DCMRWF5_BOOT_MODE_MASK)

#define DCM_GPR_DCMRWF5_BOOT_ADDRESS_MASK        (0xFFFFFFFEU)
#define DCM_GPR_DCMRWF5_BOOT_ADDRESS_SHIFT       (1U)
#define DCM_GPR_DCMRWF5_BOOT_ADDRESS_WIDTH       (31U)
#define DCM_GPR_DCMRWF5_BOOT_ADDRESS(x)          (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMRWF5_BOOT_ADDRESS_SHIFT)) & DCM_GPR_DCMRWF5_BOOT_ADDRESS_MASK)
/*! @} */

/*! @name DCMROPP1 - Read Only GPR On PMCPOR Reset */
/*! @{ */

#define DCM_GPR_DCMROPP1_POR_WDG_STAT0_MASK      (0x1U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT0_SHIFT     (0U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT0_WIDTH     (1U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT0(x)        (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP1_POR_WDG_STAT0_SHIFT)) & DCM_GPR_DCMROPP1_POR_WDG_STAT0_MASK)

#define DCM_GPR_DCMROPP1_POR_WDG_STAT1_MASK      (0x2U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT1_SHIFT     (1U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT1_WIDTH     (1U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT1(x)        (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP1_POR_WDG_STAT1_SHIFT)) & DCM_GPR_DCMROPP1_POR_WDG_STAT1_MASK)

#define DCM_GPR_DCMROPP1_POR_WDG_STAT2_MASK      (0x4U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT2_SHIFT     (2U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT2_WIDTH     (1U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT2(x)        (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP1_POR_WDG_STAT2_SHIFT)) & DCM_GPR_DCMROPP1_POR_WDG_STAT2_MASK)

#define DCM_GPR_DCMROPP1_POR_WDG_STAT3_MASK      (0x8U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT3_SHIFT     (3U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT3_WIDTH     (1U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT3(x)        (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP1_POR_WDG_STAT3_SHIFT)) & DCM_GPR_DCMROPP1_POR_WDG_STAT3_MASK)

#define DCM_GPR_DCMROPP1_POR_WDG_STAT4_MASK      (0x10U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT4_SHIFT     (4U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT4_WIDTH     (1U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT4(x)        (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP1_POR_WDG_STAT4_SHIFT)) & DCM_GPR_DCMROPP1_POR_WDG_STAT4_MASK)

#define DCM_GPR_DCMROPP1_POR_WDG_STAT5_MASK      (0x20U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT5_SHIFT     (5U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT5_WIDTH     (1U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT5(x)        (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP1_POR_WDG_STAT5_SHIFT)) & DCM_GPR_DCMROPP1_POR_WDG_STAT5_MASK)

#define DCM_GPR_DCMROPP1_POR_WDG_STAT6_MASK      (0x40U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT6_SHIFT     (6U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT6_WIDTH     (1U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT6(x)        (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP1_POR_WDG_STAT6_SHIFT)) & DCM_GPR_DCMROPP1_POR_WDG_STAT6_MASK)

#define DCM_GPR_DCMROPP1_POR_WDG_STAT10_MASK     (0x400U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT10_SHIFT    (10U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT10_WIDTH    (1U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT10(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP1_POR_WDG_STAT10_SHIFT)) & DCM_GPR_DCMROPP1_POR_WDG_STAT10_MASK)

#define DCM_GPR_DCMROPP1_POR_WDG_STAT11_MASK     (0x800U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT11_SHIFT    (11U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT11_WIDTH    (1U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT11(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP1_POR_WDG_STAT11_SHIFT)) & DCM_GPR_DCMROPP1_POR_WDG_STAT11_MASK)

#define DCM_GPR_DCMROPP1_POR_WDG_STAT14_MASK     (0x4000U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT14_SHIFT    (14U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT14_WIDTH    (1U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT14(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP1_POR_WDG_STAT14_SHIFT)) & DCM_GPR_DCMROPP1_POR_WDG_STAT14_MASK)

#define DCM_GPR_DCMROPP1_POR_WDG_STAT17_MASK     (0x20000U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT17_SHIFT    (17U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT17_WIDTH    (1U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT17(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP1_POR_WDG_STAT17_SHIFT)) & DCM_GPR_DCMROPP1_POR_WDG_STAT17_MASK)

#define DCM_GPR_DCMROPP1_POR_WDG_STAT20_MASK     (0x100000U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT20_SHIFT    (20U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT20_WIDTH    (1U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT20(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP1_POR_WDG_STAT20_SHIFT)) & DCM_GPR_DCMROPP1_POR_WDG_STAT20_MASK)

#define DCM_GPR_DCMROPP1_POR_WDG_STAT29_MASK     (0x20000000U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT29_SHIFT    (29U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT29_WIDTH    (1U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT29(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP1_POR_WDG_STAT29_SHIFT)) & DCM_GPR_DCMROPP1_POR_WDG_STAT29_MASK)

#define DCM_GPR_DCMROPP1_POR_WDG_STAT30_MASK     (0x40000000U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT30_SHIFT    (30U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT30_WIDTH    (1U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT30(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP1_POR_WDG_STAT30_SHIFT)) & DCM_GPR_DCMROPP1_POR_WDG_STAT30_MASK)

#define DCM_GPR_DCMROPP1_POR_WDG_STAT31_MASK     (0x80000000U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT31_SHIFT    (31U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT31_WIDTH    (1U)
#define DCM_GPR_DCMROPP1_POR_WDG_STAT31(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP1_POR_WDG_STAT31_SHIFT)) & DCM_GPR_DCMROPP1_POR_WDG_STAT31_MASK)
/*! @} */

/*! @name DCMROPP2 - Read Only GPR On PMCPOR Reset */
/*! @{ */

#define DCM_GPR_DCMROPP2_POR_WDG_STAT32_MASK     (0x1U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT32_SHIFT    (0U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT32_WIDTH    (1U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT32(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP2_POR_WDG_STAT32_SHIFT)) & DCM_GPR_DCMROPP2_POR_WDG_STAT32_MASK)

#define DCM_GPR_DCMROPP2_POR_WDG_STAT33_MASK     (0x2U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT33_SHIFT    (1U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT33_WIDTH    (1U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT33(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP2_POR_WDG_STAT33_SHIFT)) & DCM_GPR_DCMROPP2_POR_WDG_STAT33_MASK)

#define DCM_GPR_DCMROPP2_POR_WDG_STAT34_MASK     (0x4U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT34_SHIFT    (2U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT34_WIDTH    (1U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT34(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP2_POR_WDG_STAT34_SHIFT)) & DCM_GPR_DCMROPP2_POR_WDG_STAT34_MASK)

#define DCM_GPR_DCMROPP2_POR_WDG_STAT35_MASK     (0x8U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT35_SHIFT    (3U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT35_WIDTH    (1U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT35(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP2_POR_WDG_STAT35_SHIFT)) & DCM_GPR_DCMROPP2_POR_WDG_STAT35_MASK)

#define DCM_GPR_DCMROPP2_POR_WDG_STAT36_MASK     (0x10U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT36_SHIFT    (4U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT36_WIDTH    (1U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT36(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP2_POR_WDG_STAT36_SHIFT)) & DCM_GPR_DCMROPP2_POR_WDG_STAT36_MASK)

#define DCM_GPR_DCMROPP2_POR_WDG_STAT37_MASK     (0x20U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT37_SHIFT    (5U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT37_WIDTH    (1U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT37(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP2_POR_WDG_STAT37_SHIFT)) & DCM_GPR_DCMROPP2_POR_WDG_STAT37_MASK)

#define DCM_GPR_DCMROPP2_POR_WDG_STAT38_MASK     (0x40U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT38_SHIFT    (6U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT38_WIDTH    (1U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT38(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP2_POR_WDG_STAT38_SHIFT)) & DCM_GPR_DCMROPP2_POR_WDG_STAT38_MASK)

#define DCM_GPR_DCMROPP2_POR_WDG_STAT39_MASK     (0x80U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT39_SHIFT    (7U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT39_WIDTH    (1U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT39(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP2_POR_WDG_STAT39_SHIFT)) & DCM_GPR_DCMROPP2_POR_WDG_STAT39_MASK)

#define DCM_GPR_DCMROPP2_POR_WDG_STAT40_MASK     (0x100U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT40_SHIFT    (8U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT40_WIDTH    (1U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT40(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP2_POR_WDG_STAT40_SHIFT)) & DCM_GPR_DCMROPP2_POR_WDG_STAT40_MASK)

#define DCM_GPR_DCMROPP2_POR_WDG_STAT41_MASK     (0x200U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT41_SHIFT    (9U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT41_WIDTH    (1U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT41(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP2_POR_WDG_STAT41_SHIFT)) & DCM_GPR_DCMROPP2_POR_WDG_STAT41_MASK)

#define DCM_GPR_DCMROPP2_POR_WDG_STAT42_MASK     (0x400U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT42_SHIFT    (10U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT42_WIDTH    (1U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT42(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP2_POR_WDG_STAT42_SHIFT)) & DCM_GPR_DCMROPP2_POR_WDG_STAT42_MASK)

#define DCM_GPR_DCMROPP2_POR_WDG_STAT43_MASK     (0x800U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT43_SHIFT    (11U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT43_WIDTH    (1U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT43(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP2_POR_WDG_STAT43_SHIFT)) & DCM_GPR_DCMROPP2_POR_WDG_STAT43_MASK)

#define DCM_GPR_DCMROPP2_POR_WDG_STAT44_MASK     (0x1000U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT44_SHIFT    (12U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT44_WIDTH    (1U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT44(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP2_POR_WDG_STAT44_SHIFT)) & DCM_GPR_DCMROPP2_POR_WDG_STAT44_MASK)

#define DCM_GPR_DCMROPP2_POR_WDG_STAT45_MASK     (0x2000U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT45_SHIFT    (13U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT45_WIDTH    (1U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT45(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP2_POR_WDG_STAT45_SHIFT)) & DCM_GPR_DCMROPP2_POR_WDG_STAT45_MASK)

#define DCM_GPR_DCMROPP2_POR_WDG_STAT46_MASK     (0x4000U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT46_SHIFT    (14U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT46_WIDTH    (1U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT46(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP2_POR_WDG_STAT46_SHIFT)) & DCM_GPR_DCMROPP2_POR_WDG_STAT46_MASK)

#define DCM_GPR_DCMROPP2_POR_WDG_STAT47_MASK     (0x8000U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT47_SHIFT    (15U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT47_WIDTH    (1U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT47(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP2_POR_WDG_STAT47_SHIFT)) & DCM_GPR_DCMROPP2_POR_WDG_STAT47_MASK)

#define DCM_GPR_DCMROPP2_POR_WDG_STAT48_MASK     (0x10000U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT48_SHIFT    (16U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT48_WIDTH    (1U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT48(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP2_POR_WDG_STAT48_SHIFT)) & DCM_GPR_DCMROPP2_POR_WDG_STAT48_MASK)

#define DCM_GPR_DCMROPP2_POR_WDG_STAT49_MASK     (0x20000U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT49_SHIFT    (17U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT49_WIDTH    (1U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT49(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP2_POR_WDG_STAT49_SHIFT)) & DCM_GPR_DCMROPP2_POR_WDG_STAT49_MASK)

#define DCM_GPR_DCMROPP2_POR_WDG_STAT50_MASK     (0x40000U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT50_SHIFT    (18U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT50_WIDTH    (1U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT50(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP2_POR_WDG_STAT50_SHIFT)) & DCM_GPR_DCMROPP2_POR_WDG_STAT50_MASK)

#define DCM_GPR_DCMROPP2_POR_WDG_STAT51_MASK     (0x80000U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT51_SHIFT    (19U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT51_WIDTH    (1U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT51(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP2_POR_WDG_STAT51_SHIFT)) & DCM_GPR_DCMROPP2_POR_WDG_STAT51_MASK)

#define DCM_GPR_DCMROPP2_POR_WDG_STAT52_MASK     (0x100000U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT52_SHIFT    (20U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT52_WIDTH    (1U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT52(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP2_POR_WDG_STAT52_SHIFT)) & DCM_GPR_DCMROPP2_POR_WDG_STAT52_MASK)

#define DCM_GPR_DCMROPP2_POR_WDG_STAT53_MASK     (0x200000U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT53_SHIFT    (21U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT53_WIDTH    (1U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT53(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP2_POR_WDG_STAT53_SHIFT)) & DCM_GPR_DCMROPP2_POR_WDG_STAT53_MASK)

#define DCM_GPR_DCMROPP2_POR_WDG_STAT54_MASK     (0x400000U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT54_SHIFT    (22U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT54_WIDTH    (1U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT54(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP2_POR_WDG_STAT54_SHIFT)) & DCM_GPR_DCMROPP2_POR_WDG_STAT54_MASK)

#define DCM_GPR_DCMROPP2_POR_WDG_STAT55_MASK     (0x800000U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT55_SHIFT    (23U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT55_WIDTH    (1U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT55(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP2_POR_WDG_STAT55_SHIFT)) & DCM_GPR_DCMROPP2_POR_WDG_STAT55_MASK)

#define DCM_GPR_DCMROPP2_POR_WDG_STAT56_MASK     (0x1000000U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT56_SHIFT    (24U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT56_WIDTH    (1U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT56(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP2_POR_WDG_STAT56_SHIFT)) & DCM_GPR_DCMROPP2_POR_WDG_STAT56_MASK)

#define DCM_GPR_DCMROPP2_POR_WDG_STAT57_MASK     (0x2000000U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT57_SHIFT    (25U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT57_WIDTH    (1U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT57(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP2_POR_WDG_STAT57_SHIFT)) & DCM_GPR_DCMROPP2_POR_WDG_STAT57_MASK)

#define DCM_GPR_DCMROPP2_POR_WDG_STAT58_MASK     (0x4000000U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT58_SHIFT    (26U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT58_WIDTH    (1U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT58(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP2_POR_WDG_STAT58_SHIFT)) & DCM_GPR_DCMROPP2_POR_WDG_STAT58_MASK)

#define DCM_GPR_DCMROPP2_POR_WDG_STAT59_MASK     (0x8000000U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT59_SHIFT    (27U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT59_WIDTH    (1U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT59(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP2_POR_WDG_STAT59_SHIFT)) & DCM_GPR_DCMROPP2_POR_WDG_STAT59_MASK)

#define DCM_GPR_DCMROPP2_POR_WDG_STAT60_MASK     (0x10000000U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT60_SHIFT    (28U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT60_WIDTH    (1U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT60(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP2_POR_WDG_STAT60_SHIFT)) & DCM_GPR_DCMROPP2_POR_WDG_STAT60_MASK)

#define DCM_GPR_DCMROPP2_POR_WDG_STAT61_MASK     (0x20000000U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT61_SHIFT    (29U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT61_WIDTH    (1U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT61(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP2_POR_WDG_STAT61_SHIFT)) & DCM_GPR_DCMROPP2_POR_WDG_STAT61_MASK)

#define DCM_GPR_DCMROPP2_POR_WDG_STAT62_MASK     (0x40000000U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT62_SHIFT    (30U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT62_WIDTH    (1U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT62(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP2_POR_WDG_STAT62_SHIFT)) & DCM_GPR_DCMROPP2_POR_WDG_STAT62_MASK)

#define DCM_GPR_DCMROPP2_POR_WDG_STAT63_MASK     (0x80000000U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT63_SHIFT    (31U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT63_WIDTH    (1U)
#define DCM_GPR_DCMROPP2_POR_WDG_STAT63(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP2_POR_WDG_STAT63_SHIFT)) & DCM_GPR_DCMROPP2_POR_WDG_STAT63_MASK)
/*! @} */

/*! @name DCMROPP3 - Read Only GPR On PMCPOR Reset */
/*! @{ */

#define DCM_GPR_DCMROPP3_POR_WDG_STAT64_MASK     (0x1U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT64_SHIFT    (0U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT64_WIDTH    (1U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT64(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP3_POR_WDG_STAT64_SHIFT)) & DCM_GPR_DCMROPP3_POR_WDG_STAT64_MASK)

#define DCM_GPR_DCMROPP3_POR_WDG_STAT65_MASK     (0x2U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT65_SHIFT    (1U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT65_WIDTH    (1U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT65(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP3_POR_WDG_STAT65_SHIFT)) & DCM_GPR_DCMROPP3_POR_WDG_STAT65_MASK)

#define DCM_GPR_DCMROPP3_POR_WDG_STAT66_MASK     (0x4U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT66_SHIFT    (2U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT66_WIDTH    (1U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT66(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP3_POR_WDG_STAT66_SHIFT)) & DCM_GPR_DCMROPP3_POR_WDG_STAT66_MASK)

#define DCM_GPR_DCMROPP3_POR_WDG_STAT67_MASK     (0x8U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT67_SHIFT    (3U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT67_WIDTH    (1U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT67(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP3_POR_WDG_STAT67_SHIFT)) & DCM_GPR_DCMROPP3_POR_WDG_STAT67_MASK)

#define DCM_GPR_DCMROPP3_POR_WDG_STAT68_MASK     (0x10U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT68_SHIFT    (4U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT68_WIDTH    (1U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT68(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP3_POR_WDG_STAT68_SHIFT)) & DCM_GPR_DCMROPP3_POR_WDG_STAT68_MASK)

#define DCM_GPR_DCMROPP3_POR_WDG_STAT69_MASK     (0x20U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT69_SHIFT    (5U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT69_WIDTH    (1U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT69(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP3_POR_WDG_STAT69_SHIFT)) & DCM_GPR_DCMROPP3_POR_WDG_STAT69_MASK)

#define DCM_GPR_DCMROPP3_POR_WDG_STAT70_MASK     (0x40U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT70_SHIFT    (6U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT70_WIDTH    (1U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT70(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP3_POR_WDG_STAT70_SHIFT)) & DCM_GPR_DCMROPP3_POR_WDG_STAT70_MASK)

#define DCM_GPR_DCMROPP3_POR_WDG_STAT71_MASK     (0x80U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT71_SHIFT    (7U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT71_WIDTH    (1U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT71(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP3_POR_WDG_STAT71_SHIFT)) & DCM_GPR_DCMROPP3_POR_WDG_STAT71_MASK)

#define DCM_GPR_DCMROPP3_POR_WDG_STAT72_MASK     (0x100U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT72_SHIFT    (8U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT72_WIDTH    (1U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT72(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP3_POR_WDG_STAT72_SHIFT)) & DCM_GPR_DCMROPP3_POR_WDG_STAT72_MASK)

#define DCM_GPR_DCMROPP3_POR_WDG_STAT73_MASK     (0x200U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT73_SHIFT    (9U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT73_WIDTH    (1U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT73(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP3_POR_WDG_STAT73_SHIFT)) & DCM_GPR_DCMROPP3_POR_WDG_STAT73_MASK)

#define DCM_GPR_DCMROPP3_POR_WDG_STAT74_MASK     (0x400U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT74_SHIFT    (10U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT74_WIDTH    (1U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT74(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP3_POR_WDG_STAT74_SHIFT)) & DCM_GPR_DCMROPP3_POR_WDG_STAT74_MASK)

#define DCM_GPR_DCMROPP3_POR_WDG_STAT75_MASK     (0x800U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT75_SHIFT    (11U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT75_WIDTH    (1U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT75(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP3_POR_WDG_STAT75_SHIFT)) & DCM_GPR_DCMROPP3_POR_WDG_STAT75_MASK)

#define DCM_GPR_DCMROPP3_POR_WDG_STAT76_MASK     (0x1000U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT76_SHIFT    (12U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT76_WIDTH    (1U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT76(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP3_POR_WDG_STAT76_SHIFT)) & DCM_GPR_DCMROPP3_POR_WDG_STAT76_MASK)

#define DCM_GPR_DCMROPP3_POR_WDG_STAT77_MASK     (0x2000U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT77_SHIFT    (13U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT77_WIDTH    (1U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT77(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP3_POR_WDG_STAT77_SHIFT)) & DCM_GPR_DCMROPP3_POR_WDG_STAT77_MASK)

#define DCM_GPR_DCMROPP3_POR_WDG_STAT78_MASK     (0x4000U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT78_SHIFT    (14U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT78_WIDTH    (1U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT78(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP3_POR_WDG_STAT78_SHIFT)) & DCM_GPR_DCMROPP3_POR_WDG_STAT78_MASK)

#define DCM_GPR_DCMROPP3_POR_WDG_STAT79_MASK     (0x8000U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT79_SHIFT    (15U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT79_WIDTH    (1U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT79(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP3_POR_WDG_STAT79_SHIFT)) & DCM_GPR_DCMROPP3_POR_WDG_STAT79_MASK)

#define DCM_GPR_DCMROPP3_POR_WDG_STAT80_MASK     (0x10000U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT80_SHIFT    (16U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT80_WIDTH    (1U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT80(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP3_POR_WDG_STAT80_SHIFT)) & DCM_GPR_DCMROPP3_POR_WDG_STAT80_MASK)

#define DCM_GPR_DCMROPP3_POR_WDG_STAT81_MASK     (0x20000U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT81_SHIFT    (17U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT81_WIDTH    (1U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT81(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP3_POR_WDG_STAT81_SHIFT)) & DCM_GPR_DCMROPP3_POR_WDG_STAT81_MASK)

#define DCM_GPR_DCMROPP3_POR_WDG_STAT82_MASK     (0x40000U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT82_SHIFT    (18U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT82_WIDTH    (1U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT82(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP3_POR_WDG_STAT82_SHIFT)) & DCM_GPR_DCMROPP3_POR_WDG_STAT82_MASK)

#define DCM_GPR_DCMROPP3_POR_WDG_STAT83_MASK     (0x80000U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT83_SHIFT    (19U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT83_WIDTH    (1U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT83(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP3_POR_WDG_STAT83_SHIFT)) & DCM_GPR_DCMROPP3_POR_WDG_STAT83_MASK)

#define DCM_GPR_DCMROPP3_POR_WDG_STAT84_MASK     (0x100000U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT84_SHIFT    (20U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT84_WIDTH    (1U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT84(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP3_POR_WDG_STAT84_SHIFT)) & DCM_GPR_DCMROPP3_POR_WDG_STAT84_MASK)

#define DCM_GPR_DCMROPP3_POR_WDG_STAT85_MASK     (0x200000U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT85_SHIFT    (21U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT85_WIDTH    (1U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT85(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP3_POR_WDG_STAT85_SHIFT)) & DCM_GPR_DCMROPP3_POR_WDG_STAT85_MASK)

#define DCM_GPR_DCMROPP3_POR_WDG_STAT86_MASK     (0x400000U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT86_SHIFT    (22U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT86_WIDTH    (1U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT86(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP3_POR_WDG_STAT86_SHIFT)) & DCM_GPR_DCMROPP3_POR_WDG_STAT86_MASK)

#define DCM_GPR_DCMROPP3_POR_WDG_STAT87_MASK     (0x800000U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT87_SHIFT    (23U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT87_WIDTH    (1U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT87(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP3_POR_WDG_STAT87_SHIFT)) & DCM_GPR_DCMROPP3_POR_WDG_STAT87_MASK)

#define DCM_GPR_DCMROPP3_POR_WDG_STAT88_MASK     (0x1000000U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT88_SHIFT    (24U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT88_WIDTH    (1U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT88(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP3_POR_WDG_STAT88_SHIFT)) & DCM_GPR_DCMROPP3_POR_WDG_STAT88_MASK)

#define DCM_GPR_DCMROPP3_POR_WDG_STAT89_MASK     (0x2000000U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT89_SHIFT    (25U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT89_WIDTH    (1U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT89(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP3_POR_WDG_STAT89_SHIFT)) & DCM_GPR_DCMROPP3_POR_WDG_STAT89_MASK)

#define DCM_GPR_DCMROPP3_POR_WDG_STAT90_MASK     (0x4000000U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT90_SHIFT    (26U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT90_WIDTH    (1U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT90(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP3_POR_WDG_STAT90_SHIFT)) & DCM_GPR_DCMROPP3_POR_WDG_STAT90_MASK)

#define DCM_GPR_DCMROPP3_POR_WDG_STAT91_MASK     (0x8000000U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT91_SHIFT    (27U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT91_WIDTH    (1U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT91(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP3_POR_WDG_STAT91_SHIFT)) & DCM_GPR_DCMROPP3_POR_WDG_STAT91_MASK)

#define DCM_GPR_DCMROPP3_POR_WDG_STAT92_MASK     (0x10000000U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT92_SHIFT    (28U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT92_WIDTH    (1U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT92(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP3_POR_WDG_STAT92_SHIFT)) & DCM_GPR_DCMROPP3_POR_WDG_STAT92_MASK)

#define DCM_GPR_DCMROPP3_POR_WDG_STAT93_MASK     (0x20000000U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT93_SHIFT    (29U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT93_WIDTH    (1U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT93(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP3_POR_WDG_STAT93_SHIFT)) & DCM_GPR_DCMROPP3_POR_WDG_STAT93_MASK)

#define DCM_GPR_DCMROPP3_POR_WDG_STAT94_MASK     (0x40000000U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT94_SHIFT    (30U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT94_WIDTH    (1U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT94(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP3_POR_WDG_STAT94_SHIFT)) & DCM_GPR_DCMROPP3_POR_WDG_STAT94_MASK)

#define DCM_GPR_DCMROPP3_POR_WDG_STAT95_MASK     (0x80000000U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT95_SHIFT    (31U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT95_WIDTH    (1U)
#define DCM_GPR_DCMROPP3_POR_WDG_STAT95(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP3_POR_WDG_STAT95_SHIFT)) & DCM_GPR_DCMROPP3_POR_WDG_STAT95_MASK)
/*! @} */

/*! @name DCMROPP4 - Read Only GPR On PMCPOR Reset */
/*! @{ */

#define DCM_GPR_DCMROPP4_POR_WDG_STAT96_MASK     (0x1U)
#define DCM_GPR_DCMROPP4_POR_WDG_STAT96_SHIFT    (0U)
#define DCM_GPR_DCMROPP4_POR_WDG_STAT96_WIDTH    (1U)
#define DCM_GPR_DCMROPP4_POR_WDG_STAT96(x)       (((uint32_t)(((uint32_t)(x)) << DCM_GPR_DCMROPP4_POR_WDG_STAT96_SHIFT)) & DCM_GPR_DCMROPP4_POR_WDG_STAT96_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group DCM_GPR_Register_Masks */

/*!
 * @}
 */ /* end of group DCM_GPR_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_DCM_GPR_H_) */
