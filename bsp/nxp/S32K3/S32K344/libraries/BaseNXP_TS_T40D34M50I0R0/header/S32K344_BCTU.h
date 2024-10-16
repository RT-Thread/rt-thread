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
 * @file S32K344_BCTU.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_BCTU
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
#if !defined(S32K344_BCTU_H_)  /* Check if memory map has not been already included */
#define S32K344_BCTU_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- BCTU Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup BCTU_Peripheral_Access_Layer BCTU Peripheral Access Layer
 * @{
 */

/** BCTU - Size of Registers Arrays */
#define BCTU_TRGCFG_COUNT                         72u
#define BCTU_ADCDR_COUNT                          3u
#define BCTU_LISTCHR_COUNT                        16u

/** BCTU - Register Layout Typedef */
typedef struct {
  __IO uint32_t MCR;                               /**< Module Configuration, offset: 0x0 */
  uint8_t RESERVED_0[4];
  __IO uint32_t MSR;                               /**< Module Status, offset: 0x8 */
  uint8_t RESERVED_1[12];
  __IO uint32_t TRGCFG[BCTU_TRGCFG_COUNT];         /**< Trigger Configuration, array offset: 0x18, array step: 0x4 */
  uint8_t RESERVED_2[240];
  __IO uint32_t WRPROT;                            /**< Write Protection, offset: 0x228 */
  __IO uint32_t SFTRGR1;                           /**< Software Trigger 1, offset: 0x22C */
  __IO uint32_t SFTRGR2;                           /**< Software Trigger 2, offset: 0x230 */
  __IO uint32_t SFTRGR3;                           /**< Software Trigger 3, offset: 0x234 */
  uint8_t RESERVED_3[4];
  __I  uint32_t ADCDR[BCTU_ADCDR_COUNT];           /**< ADC0 Result Data..ADC2 Result Data, array offset: 0x23C, array step: 0x4 */
  uint8_t RESERVED_4[4];
  __I  uint32_t LISTSTAR;                          /**< CL Size Status, offset: 0x24C */
  __IO uint32_t LISTCHR[BCTU_LISTCHR_COUNT];       /**< CL Channel Address, array offset: 0x250, array step: 0x4 */
  uint8_t RESERVED_5[448];
  __I  uint32_t FIFO1DR;                           /**< FIFO Result Data, offset: 0x450 */
  __I  uint32_t FIFO2DR;                           /**< FIFO Result Data, offset: 0x454 */
  uint8_t RESERVED_6[8];
  __IO uint32_t FIFOCR;                            /**< FIFO Control, offset: 0x460 */
  __IO uint32_t FIFOWM;                            /**< FIFO Watermark Configuration, offset: 0x464 */
  __IO uint32_t FIFOERR;                           /**< FIFO Error/Status, offset: 0x468 */
  __I  uint32_t FIFOSR;                            /**< FIFO Status, offset: 0x46C */
  __I  uint32_t FIFOCNTR;                          /**< FIFO Counter, offset: 0x470 */
} BCTU_Type, *BCTU_MemMapPtr;

/** Number of instances of the BCTU module. */
#define BCTU_INSTANCE_COUNT                      (1u)

/* BCTU - Peripheral instance base addresses */
/** Peripheral BCTU base address */
#define IP_BCTU_BASE                             (0x40084000u)
/** Peripheral BCTU base pointer */
#define IP_BCTU                                  ((BCTU_Type *)IP_BCTU_BASE)
/** Array initializer of BCTU peripheral base addresses */
#define IP_BCTU_BASE_ADDRS                       { IP_BCTU_BASE }
/** Array initializer of BCTU peripheral base pointers */
#define IP_BCTU_BASE_PTRS                        { IP_BCTU }

/* ----------------------------------------------------------------------------
   -- BCTU Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup BCTU_Register_Masks BCTU Register Masks
 * @{
 */

/*! @name MCR - Module Configuration */
/*! @{ */

#define BCTU_MCR_IEN0_MASK                       (0x1U)
#define BCTU_MCR_IEN0_SHIFT                      (0U)
#define BCTU_MCR_IEN0_WIDTH                      (1U)
#define BCTU_MCR_IEN0(x)                         (((uint32_t)(((uint32_t)(x)) << BCTU_MCR_IEN0_SHIFT)) & BCTU_MCR_IEN0_MASK)

#define BCTU_MCR_IEN1_MASK                       (0x2U)
#define BCTU_MCR_IEN1_SHIFT                      (1U)
#define BCTU_MCR_IEN1_WIDTH                      (1U)
#define BCTU_MCR_IEN1(x)                         (((uint32_t)(((uint32_t)(x)) << BCTU_MCR_IEN1_SHIFT)) & BCTU_MCR_IEN1_MASK)

#define BCTU_MCR_IEN2_MASK                       (0x4U)
#define BCTU_MCR_IEN2_SHIFT                      (2U)
#define BCTU_MCR_IEN2_WIDTH                      (1U)
#define BCTU_MCR_IEN2(x)                         (((uint32_t)(((uint32_t)(x)) << BCTU_MCR_IEN2_SHIFT)) & BCTU_MCR_IEN2_MASK)

#define BCTU_MCR_LIST_IEN_MASK                   (0x20U)
#define BCTU_MCR_LIST_IEN_SHIFT                  (5U)
#define BCTU_MCR_LIST_IEN_WIDTH                  (1U)
#define BCTU_MCR_LIST_IEN(x)                     (((uint32_t)(((uint32_t)(x)) << BCTU_MCR_LIST_IEN_SHIFT)) & BCTU_MCR_LIST_IEN_MASK)

#define BCTU_MCR_TRGEN_MASK                      (0x80U)
#define BCTU_MCR_TRGEN_SHIFT                     (7U)
#define BCTU_MCR_TRGEN_WIDTH                     (1U)
#define BCTU_MCR_TRGEN(x)                        (((uint32_t)(((uint32_t)(x)) << BCTU_MCR_TRGEN_SHIFT)) & BCTU_MCR_TRGEN_MASK)

#define BCTU_MCR_DMA0_MASK                       (0x10000U)
#define BCTU_MCR_DMA0_SHIFT                      (16U)
#define BCTU_MCR_DMA0_WIDTH                      (1U)
#define BCTU_MCR_DMA0(x)                         (((uint32_t)(((uint32_t)(x)) << BCTU_MCR_DMA0_SHIFT)) & BCTU_MCR_DMA0_MASK)

#define BCTU_MCR_DMA1_MASK                       (0x20000U)
#define BCTU_MCR_DMA1_SHIFT                      (17U)
#define BCTU_MCR_DMA1_WIDTH                      (1U)
#define BCTU_MCR_DMA1(x)                         (((uint32_t)(((uint32_t)(x)) << BCTU_MCR_DMA1_SHIFT)) & BCTU_MCR_DMA1_MASK)

#define BCTU_MCR_DMA2_MASK                       (0x40000U)
#define BCTU_MCR_DMA2_SHIFT                      (18U)
#define BCTU_MCR_DMA2_WIDTH                      (1U)
#define BCTU_MCR_DMA2(x)                         (((uint32_t)(((uint32_t)(x)) << BCTU_MCR_DMA2_SHIFT)) & BCTU_MCR_DMA2_MASK)

#define BCTU_MCR_GTRGEN_MASK                     (0x4000000U)
#define BCTU_MCR_GTRGEN_SHIFT                    (26U)
#define BCTU_MCR_GTRGEN_WIDTH                    (1U)
#define BCTU_MCR_GTRGEN(x)                       (((uint32_t)(((uint32_t)(x)) << BCTU_MCR_GTRGEN_SHIFT)) & BCTU_MCR_GTRGEN_MASK)

#define BCTU_MCR_FRZ_MASK                        (0x20000000U)
#define BCTU_MCR_FRZ_SHIFT                       (29U)
#define BCTU_MCR_FRZ_WIDTH                       (1U)
#define BCTU_MCR_FRZ(x)                          (((uint32_t)(((uint32_t)(x)) << BCTU_MCR_FRZ_SHIFT)) & BCTU_MCR_FRZ_MASK)

#define BCTU_MCR_MDIS_MASK                       (0x40000000U)
#define BCTU_MCR_MDIS_SHIFT                      (30U)
#define BCTU_MCR_MDIS_WIDTH                      (1U)
#define BCTU_MCR_MDIS(x)                         (((uint32_t)(((uint32_t)(x)) << BCTU_MCR_MDIS_SHIFT)) & BCTU_MCR_MDIS_MASK)

#define BCTU_MCR_Software_Reset_MASK             (0x80000000U)
#define BCTU_MCR_Software_Reset_SHIFT            (31U)
#define BCTU_MCR_Software_Reset_WIDTH            (1U)
#define BCTU_MCR_Software_Reset(x)               (((uint32_t)(((uint32_t)(x)) << BCTU_MCR_Software_Reset_SHIFT)) & BCTU_MCR_Software_Reset_MASK)
/*! @} */

/*! @name MSR - Module Status */
/*! @{ */

#define BCTU_MSR_NDATA0_MASK                     (0x1U)
#define BCTU_MSR_NDATA0_SHIFT                    (0U)
#define BCTU_MSR_NDATA0_WIDTH                    (1U)
#define BCTU_MSR_NDATA0(x)                       (((uint32_t)(((uint32_t)(x)) << BCTU_MSR_NDATA0_SHIFT)) & BCTU_MSR_NDATA0_MASK)

#define BCTU_MSR_NDATA1_MASK                     (0x2U)
#define BCTU_MSR_NDATA1_SHIFT                    (1U)
#define BCTU_MSR_NDATA1_WIDTH                    (1U)
#define BCTU_MSR_NDATA1(x)                       (((uint32_t)(((uint32_t)(x)) << BCTU_MSR_NDATA1_SHIFT)) & BCTU_MSR_NDATA1_MASK)

#define BCTU_MSR_NDATA2_MASK                     (0x4U)
#define BCTU_MSR_NDATA2_SHIFT                    (2U)
#define BCTU_MSR_NDATA2_WIDTH                    (1U)
#define BCTU_MSR_NDATA2(x)                       (((uint32_t)(((uint32_t)(x)) << BCTU_MSR_NDATA2_SHIFT)) & BCTU_MSR_NDATA2_MASK)

#define BCTU_MSR_DATAOVR0_MASK                   (0x10U)
#define BCTU_MSR_DATAOVR0_SHIFT                  (4U)
#define BCTU_MSR_DATAOVR0_WIDTH                  (1U)
#define BCTU_MSR_DATAOVR0(x)                     (((uint32_t)(((uint32_t)(x)) << BCTU_MSR_DATAOVR0_SHIFT)) & BCTU_MSR_DATAOVR0_MASK)

#define BCTU_MSR_DATAOVR1_MASK                   (0x20U)
#define BCTU_MSR_DATAOVR1_SHIFT                  (5U)
#define BCTU_MSR_DATAOVR1_WIDTH                  (1U)
#define BCTU_MSR_DATAOVR1(x)                     (((uint32_t)(((uint32_t)(x)) << BCTU_MSR_DATAOVR1_SHIFT)) & BCTU_MSR_DATAOVR1_MASK)

#define BCTU_MSR_DATAOVR2_MASK                   (0x40U)
#define BCTU_MSR_DATAOVR2_SHIFT                  (6U)
#define BCTU_MSR_DATAOVR2_WIDTH                  (1U)
#define BCTU_MSR_DATAOVR2(x)                     (((uint32_t)(((uint32_t)(x)) << BCTU_MSR_DATAOVR2_SHIFT)) & BCTU_MSR_DATAOVR2_MASK)

#define BCTU_MSR_LIST0_Last_MASK                 (0x100U)
#define BCTU_MSR_LIST0_Last_SHIFT                (8U)
#define BCTU_MSR_LIST0_Last_WIDTH                (1U)
#define BCTU_MSR_LIST0_Last(x)                   (((uint32_t)(((uint32_t)(x)) << BCTU_MSR_LIST0_Last_SHIFT)) & BCTU_MSR_LIST0_Last_MASK)

#define BCTU_MSR_LIST1_Last_MASK                 (0x200U)
#define BCTU_MSR_LIST1_Last_SHIFT                (9U)
#define BCTU_MSR_LIST1_Last_WIDTH                (1U)
#define BCTU_MSR_LIST1_Last(x)                   (((uint32_t)(((uint32_t)(x)) << BCTU_MSR_LIST1_Last_SHIFT)) & BCTU_MSR_LIST1_Last_MASK)

#define BCTU_MSR_LIST2_Last_MASK                 (0x400U)
#define BCTU_MSR_LIST2_Last_SHIFT                (10U)
#define BCTU_MSR_LIST2_Last_WIDTH                (1U)
#define BCTU_MSR_LIST2_Last(x)                   (((uint32_t)(((uint32_t)(x)) << BCTU_MSR_LIST2_Last_SHIFT)) & BCTU_MSR_LIST2_Last_MASK)

#define BCTU_MSR_TRGF_MASK                       (0x8000U)
#define BCTU_MSR_TRGF_SHIFT                      (15U)
#define BCTU_MSR_TRGF_WIDTH                      (1U)
#define BCTU_MSR_TRGF(x)                         (((uint32_t)(((uint32_t)(x)) << BCTU_MSR_TRGF_SHIFT)) & BCTU_MSR_TRGF_MASK)

#define BCTU_MSR_NDATA0_CLR_MASK                 (0x10000U)
#define BCTU_MSR_NDATA0_CLR_SHIFT                (16U)
#define BCTU_MSR_NDATA0_CLR_WIDTH                (1U)
#define BCTU_MSR_NDATA0_CLR(x)                   (((uint32_t)(((uint32_t)(x)) << BCTU_MSR_NDATA0_CLR_SHIFT)) & BCTU_MSR_NDATA0_CLR_MASK)

#define BCTU_MSR_NDATA1_CLR_MASK                 (0x20000U)
#define BCTU_MSR_NDATA1_CLR_SHIFT                (17U)
#define BCTU_MSR_NDATA1_CLR_WIDTH                (1U)
#define BCTU_MSR_NDATA1_CLR(x)                   (((uint32_t)(((uint32_t)(x)) << BCTU_MSR_NDATA1_CLR_SHIFT)) & BCTU_MSR_NDATA1_CLR_MASK)

#define BCTU_MSR_NDATA2_CLR_MASK                 (0x40000U)
#define BCTU_MSR_NDATA2_CLR_SHIFT                (18U)
#define BCTU_MSR_NDATA2_CLR_WIDTH                (1U)
#define BCTU_MSR_NDATA2_CLR(x)                   (((uint32_t)(((uint32_t)(x)) << BCTU_MSR_NDATA2_CLR_SHIFT)) & BCTU_MSR_NDATA2_CLR_MASK)

#define BCTU_MSR_DATAOVR0_CLR_MASK               (0x100000U)
#define BCTU_MSR_DATAOVR0_CLR_SHIFT              (20U)
#define BCTU_MSR_DATAOVR0_CLR_WIDTH              (1U)
#define BCTU_MSR_DATAOVR0_CLR(x)                 (((uint32_t)(((uint32_t)(x)) << BCTU_MSR_DATAOVR0_CLR_SHIFT)) & BCTU_MSR_DATAOVR0_CLR_MASK)

#define BCTU_MSR_DATAOVR1_CLR_MASK               (0x200000U)
#define BCTU_MSR_DATAOVR1_CLR_SHIFT              (21U)
#define BCTU_MSR_DATAOVR1_CLR_WIDTH              (1U)
#define BCTU_MSR_DATAOVR1_CLR(x)                 (((uint32_t)(((uint32_t)(x)) << BCTU_MSR_DATAOVR1_CLR_SHIFT)) & BCTU_MSR_DATAOVR1_CLR_MASK)

#define BCTU_MSR_DATAOVR2_CLR_MASK               (0x400000U)
#define BCTU_MSR_DATAOVR2_CLR_SHIFT              (22U)
#define BCTU_MSR_DATAOVR2_CLR_WIDTH              (1U)
#define BCTU_MSR_DATAOVR2_CLR(x)                 (((uint32_t)(((uint32_t)(x)) << BCTU_MSR_DATAOVR2_CLR_SHIFT)) & BCTU_MSR_DATAOVR2_CLR_MASK)

#define BCTU_MSR_LIST0_Last_CLR_MASK             (0x1000000U)
#define BCTU_MSR_LIST0_Last_CLR_SHIFT            (24U)
#define BCTU_MSR_LIST0_Last_CLR_WIDTH            (1U)
#define BCTU_MSR_LIST0_Last_CLR(x)               (((uint32_t)(((uint32_t)(x)) << BCTU_MSR_LIST0_Last_CLR_SHIFT)) & BCTU_MSR_LIST0_Last_CLR_MASK)

#define BCTU_MSR_LIST1_Last_CLR_MASK             (0x2000000U)
#define BCTU_MSR_LIST1_Last_CLR_SHIFT            (25U)
#define BCTU_MSR_LIST1_Last_CLR_WIDTH            (1U)
#define BCTU_MSR_LIST1_Last_CLR(x)               (((uint32_t)(((uint32_t)(x)) << BCTU_MSR_LIST1_Last_CLR_SHIFT)) & BCTU_MSR_LIST1_Last_CLR_MASK)

#define BCTU_MSR_LIST2_Last_CLR_MASK             (0x4000000U)
#define BCTU_MSR_LIST2_Last_CLR_SHIFT            (26U)
#define BCTU_MSR_LIST2_Last_CLR_WIDTH            (1U)
#define BCTU_MSR_LIST2_Last_CLR(x)               (((uint32_t)(((uint32_t)(x)) << BCTU_MSR_LIST2_Last_CLR_SHIFT)) & BCTU_MSR_LIST2_Last_CLR_MASK)

#define BCTU_MSR_TRGF_CLR_MASK                   (0x80000000U)
#define BCTU_MSR_TRGF_CLR_SHIFT                  (31U)
#define BCTU_MSR_TRGF_CLR_WIDTH                  (1U)
#define BCTU_MSR_TRGF_CLR(x)                     (((uint32_t)(((uint32_t)(x)) << BCTU_MSR_TRGF_CLR_SHIFT)) & BCTU_MSR_TRGF_CLR_MASK)
/*! @} */

/*! @name TRGCFG - Trigger Configuration */
/*! @{ */

#define BCTU_TRGCFG_CHANNEL_VALUE_OR_LADDR_MASK  (0x7FU)
#define BCTU_TRGCFG_CHANNEL_VALUE_OR_LADDR_SHIFT (0U)
#define BCTU_TRGCFG_CHANNEL_VALUE_OR_LADDR_WIDTH (7U)
#define BCTU_TRGCFG_CHANNEL_VALUE_OR_LADDR(x)    (((uint32_t)(((uint32_t)(x)) << BCTU_TRGCFG_CHANNEL_VALUE_OR_LADDR_SHIFT)) & BCTU_TRGCFG_CHANNEL_VALUE_OR_LADDR_MASK)

#define BCTU_TRGCFG_ADC_SEL0_MASK                (0x100U)
#define BCTU_TRGCFG_ADC_SEL0_SHIFT               (8U)
#define BCTU_TRGCFG_ADC_SEL0_WIDTH               (1U)
#define BCTU_TRGCFG_ADC_SEL0(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_TRGCFG_ADC_SEL0_SHIFT)) & BCTU_TRGCFG_ADC_SEL0_MASK)

#define BCTU_TRGCFG_ADC_SEL1_MASK                (0x200U)
#define BCTU_TRGCFG_ADC_SEL1_SHIFT               (9U)
#define BCTU_TRGCFG_ADC_SEL1_WIDTH               (1U)
#define BCTU_TRGCFG_ADC_SEL1(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_TRGCFG_ADC_SEL1_SHIFT)) & BCTU_TRGCFG_ADC_SEL1_MASK)

#define BCTU_TRGCFG_ADC_SEL2_MASK                (0x400U)
#define BCTU_TRGCFG_ADC_SEL2_SHIFT               (10U)
#define BCTU_TRGCFG_ADC_SEL2_WIDTH               (1U)
#define BCTU_TRGCFG_ADC_SEL2(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_TRGCFG_ADC_SEL2_SHIFT)) & BCTU_TRGCFG_ADC_SEL2_MASK)

#define BCTU_TRGCFG_TRS_MASK                     (0x2000U)
#define BCTU_TRGCFG_TRS_SHIFT                    (13U)
#define BCTU_TRGCFG_TRS_WIDTH                    (1U)
#define BCTU_TRGCFG_TRS(x)                       (((uint32_t)(((uint32_t)(x)) << BCTU_TRGCFG_TRS_SHIFT)) & BCTU_TRGCFG_TRS_MASK)

#define BCTU_TRGCFG_TRG_FLAG_MASK                (0x4000U)
#define BCTU_TRGCFG_TRG_FLAG_SHIFT               (14U)
#define BCTU_TRGCFG_TRG_FLAG_WIDTH               (1U)
#define BCTU_TRGCFG_TRG_FLAG(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_TRGCFG_TRG_FLAG_SHIFT)) & BCTU_TRGCFG_TRG_FLAG_MASK)

#define BCTU_TRGCFG_TRIGEN_MASK                  (0x8000U)
#define BCTU_TRGCFG_TRIGEN_SHIFT                 (15U)
#define BCTU_TRGCFG_TRIGEN_WIDTH                 (1U)
#define BCTU_TRGCFG_TRIGEN(x)                    (((uint32_t)(((uint32_t)(x)) << BCTU_TRGCFG_TRIGEN_SHIFT)) & BCTU_TRGCFG_TRIGEN_MASK)

#define BCTU_TRGCFG_DATA_DEST_MASK               (0x70000000U)
#define BCTU_TRGCFG_DATA_DEST_SHIFT              (28U)
#define BCTU_TRGCFG_DATA_DEST_WIDTH              (3U)
#define BCTU_TRGCFG_DATA_DEST(x)                 (((uint32_t)(((uint32_t)(x)) << BCTU_TRGCFG_DATA_DEST_SHIFT)) & BCTU_TRGCFG_DATA_DEST_MASK)

#define BCTU_TRGCFG_LOOP_MASK                    (0x80000000U)
#define BCTU_TRGCFG_LOOP_SHIFT                   (31U)
#define BCTU_TRGCFG_LOOP_WIDTH                   (1U)
#define BCTU_TRGCFG_LOOP(x)                      (((uint32_t)(((uint32_t)(x)) << BCTU_TRGCFG_LOOP_SHIFT)) & BCTU_TRGCFG_LOOP_MASK)
/*! @} */

/*! @name WRPROT - Write Protection */
/*! @{ */

#define BCTU_WRPROT_PROTEC_CODE_MASK             (0xFU)
#define BCTU_WRPROT_PROTEC_CODE_SHIFT            (0U)
#define BCTU_WRPROT_PROTEC_CODE_WIDTH            (4U)
#define BCTU_WRPROT_PROTEC_CODE(x)               (((uint32_t)(((uint32_t)(x)) << BCTU_WRPROT_PROTEC_CODE_SHIFT)) & BCTU_WRPROT_PROTEC_CODE_MASK)
/*! @} */

/*! @name SFTRGR1 - Software Trigger 1 */
/*! @{ */

#define BCTU_SFTRGR1_SFTRG0_MASK                 (0x1U)
#define BCTU_SFTRGR1_SFTRG0_SHIFT                (0U)
#define BCTU_SFTRGR1_SFTRG0_WIDTH                (1U)
#define BCTU_SFTRGR1_SFTRG0(x)                   (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR1_SFTRG0_SHIFT)) & BCTU_SFTRGR1_SFTRG0_MASK)

#define BCTU_SFTRGR1_SFTRG1_MASK                 (0x2U)
#define BCTU_SFTRGR1_SFTRG1_SHIFT                (1U)
#define BCTU_SFTRGR1_SFTRG1_WIDTH                (1U)
#define BCTU_SFTRGR1_SFTRG1(x)                   (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR1_SFTRG1_SHIFT)) & BCTU_SFTRGR1_SFTRG1_MASK)

#define BCTU_SFTRGR1_SFTRG2_MASK                 (0x4U)
#define BCTU_SFTRGR1_SFTRG2_SHIFT                (2U)
#define BCTU_SFTRGR1_SFTRG2_WIDTH                (1U)
#define BCTU_SFTRGR1_SFTRG2(x)                   (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR1_SFTRG2_SHIFT)) & BCTU_SFTRGR1_SFTRG2_MASK)

#define BCTU_SFTRGR1_SFTRG3_MASK                 (0x8U)
#define BCTU_SFTRGR1_SFTRG3_SHIFT                (3U)
#define BCTU_SFTRGR1_SFTRG3_WIDTH                (1U)
#define BCTU_SFTRGR1_SFTRG3(x)                   (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR1_SFTRG3_SHIFT)) & BCTU_SFTRGR1_SFTRG3_MASK)

#define BCTU_SFTRGR1_SFTRG4_MASK                 (0x10U)
#define BCTU_SFTRGR1_SFTRG4_SHIFT                (4U)
#define BCTU_SFTRGR1_SFTRG4_WIDTH                (1U)
#define BCTU_SFTRGR1_SFTRG4(x)                   (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR1_SFTRG4_SHIFT)) & BCTU_SFTRGR1_SFTRG4_MASK)

#define BCTU_SFTRGR1_SFTRG5_MASK                 (0x20U)
#define BCTU_SFTRGR1_SFTRG5_SHIFT                (5U)
#define BCTU_SFTRGR1_SFTRG5_WIDTH                (1U)
#define BCTU_SFTRGR1_SFTRG5(x)                   (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR1_SFTRG5_SHIFT)) & BCTU_SFTRGR1_SFTRG5_MASK)

#define BCTU_SFTRGR1_SFTRG6_MASK                 (0x40U)
#define BCTU_SFTRGR1_SFTRG6_SHIFT                (6U)
#define BCTU_SFTRGR1_SFTRG6_WIDTH                (1U)
#define BCTU_SFTRGR1_SFTRG6(x)                   (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR1_SFTRG6_SHIFT)) & BCTU_SFTRGR1_SFTRG6_MASK)

#define BCTU_SFTRGR1_SFTRG7_MASK                 (0x80U)
#define BCTU_SFTRGR1_SFTRG7_SHIFT                (7U)
#define BCTU_SFTRGR1_SFTRG7_WIDTH                (1U)
#define BCTU_SFTRGR1_SFTRG7(x)                   (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR1_SFTRG7_SHIFT)) & BCTU_SFTRGR1_SFTRG7_MASK)

#define BCTU_SFTRGR1_SFTRG8_MASK                 (0x100U)
#define BCTU_SFTRGR1_SFTRG8_SHIFT                (8U)
#define BCTU_SFTRGR1_SFTRG8_WIDTH                (1U)
#define BCTU_SFTRGR1_SFTRG8(x)                   (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR1_SFTRG8_SHIFT)) & BCTU_SFTRGR1_SFTRG8_MASK)

#define BCTU_SFTRGR1_SFTRG9_MASK                 (0x200U)
#define BCTU_SFTRGR1_SFTRG9_SHIFT                (9U)
#define BCTU_SFTRGR1_SFTRG9_WIDTH                (1U)
#define BCTU_SFTRGR1_SFTRG9(x)                   (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR1_SFTRG9_SHIFT)) & BCTU_SFTRGR1_SFTRG9_MASK)

#define BCTU_SFTRGR1_SFTRG10_MASK                (0x400U)
#define BCTU_SFTRGR1_SFTRG10_SHIFT               (10U)
#define BCTU_SFTRGR1_SFTRG10_WIDTH               (1U)
#define BCTU_SFTRGR1_SFTRG10(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR1_SFTRG10_SHIFT)) & BCTU_SFTRGR1_SFTRG10_MASK)

#define BCTU_SFTRGR1_SFTRG11_MASK                (0x800U)
#define BCTU_SFTRGR1_SFTRG11_SHIFT               (11U)
#define BCTU_SFTRGR1_SFTRG11_WIDTH               (1U)
#define BCTU_SFTRGR1_SFTRG11(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR1_SFTRG11_SHIFT)) & BCTU_SFTRGR1_SFTRG11_MASK)

#define BCTU_SFTRGR1_SFTRG12_MASK                (0x1000U)
#define BCTU_SFTRGR1_SFTRG12_SHIFT               (12U)
#define BCTU_SFTRGR1_SFTRG12_WIDTH               (1U)
#define BCTU_SFTRGR1_SFTRG12(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR1_SFTRG12_SHIFT)) & BCTU_SFTRGR1_SFTRG12_MASK)

#define BCTU_SFTRGR1_SFTRG13_MASK                (0x2000U)
#define BCTU_SFTRGR1_SFTRG13_SHIFT               (13U)
#define BCTU_SFTRGR1_SFTRG13_WIDTH               (1U)
#define BCTU_SFTRGR1_SFTRG13(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR1_SFTRG13_SHIFT)) & BCTU_SFTRGR1_SFTRG13_MASK)

#define BCTU_SFTRGR1_SFTRG14_MASK                (0x4000U)
#define BCTU_SFTRGR1_SFTRG14_SHIFT               (14U)
#define BCTU_SFTRGR1_SFTRG14_WIDTH               (1U)
#define BCTU_SFTRGR1_SFTRG14(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR1_SFTRG14_SHIFT)) & BCTU_SFTRGR1_SFTRG14_MASK)

#define BCTU_SFTRGR1_SFTRG15_MASK                (0x8000U)
#define BCTU_SFTRGR1_SFTRG15_SHIFT               (15U)
#define BCTU_SFTRGR1_SFTRG15_WIDTH               (1U)
#define BCTU_SFTRGR1_SFTRG15(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR1_SFTRG15_SHIFT)) & BCTU_SFTRGR1_SFTRG15_MASK)

#define BCTU_SFTRGR1_SFTRG16_MASK                (0x10000U)
#define BCTU_SFTRGR1_SFTRG16_SHIFT               (16U)
#define BCTU_SFTRGR1_SFTRG16_WIDTH               (1U)
#define BCTU_SFTRGR1_SFTRG16(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR1_SFTRG16_SHIFT)) & BCTU_SFTRGR1_SFTRG16_MASK)

#define BCTU_SFTRGR1_SFTRG17_MASK                (0x20000U)
#define BCTU_SFTRGR1_SFTRG17_SHIFT               (17U)
#define BCTU_SFTRGR1_SFTRG17_WIDTH               (1U)
#define BCTU_SFTRGR1_SFTRG17(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR1_SFTRG17_SHIFT)) & BCTU_SFTRGR1_SFTRG17_MASK)

#define BCTU_SFTRGR1_SFTRG18_MASK                (0x40000U)
#define BCTU_SFTRGR1_SFTRG18_SHIFT               (18U)
#define BCTU_SFTRGR1_SFTRG18_WIDTH               (1U)
#define BCTU_SFTRGR1_SFTRG18(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR1_SFTRG18_SHIFT)) & BCTU_SFTRGR1_SFTRG18_MASK)

#define BCTU_SFTRGR1_SFTRG19_MASK                (0x80000U)
#define BCTU_SFTRGR1_SFTRG19_SHIFT               (19U)
#define BCTU_SFTRGR1_SFTRG19_WIDTH               (1U)
#define BCTU_SFTRGR1_SFTRG19(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR1_SFTRG19_SHIFT)) & BCTU_SFTRGR1_SFTRG19_MASK)

#define BCTU_SFTRGR1_SFTRG20_MASK                (0x100000U)
#define BCTU_SFTRGR1_SFTRG20_SHIFT               (20U)
#define BCTU_SFTRGR1_SFTRG20_WIDTH               (1U)
#define BCTU_SFTRGR1_SFTRG20(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR1_SFTRG20_SHIFT)) & BCTU_SFTRGR1_SFTRG20_MASK)

#define BCTU_SFTRGR1_SFTRG21_MASK                (0x200000U)
#define BCTU_SFTRGR1_SFTRG21_SHIFT               (21U)
#define BCTU_SFTRGR1_SFTRG21_WIDTH               (1U)
#define BCTU_SFTRGR1_SFTRG21(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR1_SFTRG21_SHIFT)) & BCTU_SFTRGR1_SFTRG21_MASK)

#define BCTU_SFTRGR1_SFTRG22_MASK                (0x400000U)
#define BCTU_SFTRGR1_SFTRG22_SHIFT               (22U)
#define BCTU_SFTRGR1_SFTRG22_WIDTH               (1U)
#define BCTU_SFTRGR1_SFTRG22(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR1_SFTRG22_SHIFT)) & BCTU_SFTRGR1_SFTRG22_MASK)

#define BCTU_SFTRGR1_SFTRG23_MASK                (0x800000U)
#define BCTU_SFTRGR1_SFTRG23_SHIFT               (23U)
#define BCTU_SFTRGR1_SFTRG23_WIDTH               (1U)
#define BCTU_SFTRGR1_SFTRG23(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR1_SFTRG23_SHIFT)) & BCTU_SFTRGR1_SFTRG23_MASK)

#define BCTU_SFTRGR1_SFTRG24_MASK                (0x1000000U)
#define BCTU_SFTRGR1_SFTRG24_SHIFT               (24U)
#define BCTU_SFTRGR1_SFTRG24_WIDTH               (1U)
#define BCTU_SFTRGR1_SFTRG24(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR1_SFTRG24_SHIFT)) & BCTU_SFTRGR1_SFTRG24_MASK)

#define BCTU_SFTRGR1_SFTRG25_MASK                (0x2000000U)
#define BCTU_SFTRGR1_SFTRG25_SHIFT               (25U)
#define BCTU_SFTRGR1_SFTRG25_WIDTH               (1U)
#define BCTU_SFTRGR1_SFTRG25(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR1_SFTRG25_SHIFT)) & BCTU_SFTRGR1_SFTRG25_MASK)

#define BCTU_SFTRGR1_SFTRG26_MASK                (0x4000000U)
#define BCTU_SFTRGR1_SFTRG26_SHIFT               (26U)
#define BCTU_SFTRGR1_SFTRG26_WIDTH               (1U)
#define BCTU_SFTRGR1_SFTRG26(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR1_SFTRG26_SHIFT)) & BCTU_SFTRGR1_SFTRG26_MASK)

#define BCTU_SFTRGR1_SFTRG27_MASK                (0x8000000U)
#define BCTU_SFTRGR1_SFTRG27_SHIFT               (27U)
#define BCTU_SFTRGR1_SFTRG27_WIDTH               (1U)
#define BCTU_SFTRGR1_SFTRG27(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR1_SFTRG27_SHIFT)) & BCTU_SFTRGR1_SFTRG27_MASK)

#define BCTU_SFTRGR1_SFTRG28_MASK                (0x10000000U)
#define BCTU_SFTRGR1_SFTRG28_SHIFT               (28U)
#define BCTU_SFTRGR1_SFTRG28_WIDTH               (1U)
#define BCTU_SFTRGR1_SFTRG28(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR1_SFTRG28_SHIFT)) & BCTU_SFTRGR1_SFTRG28_MASK)

#define BCTU_SFTRGR1_SFTRG29_MASK                (0x20000000U)
#define BCTU_SFTRGR1_SFTRG29_SHIFT               (29U)
#define BCTU_SFTRGR1_SFTRG29_WIDTH               (1U)
#define BCTU_SFTRGR1_SFTRG29(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR1_SFTRG29_SHIFT)) & BCTU_SFTRGR1_SFTRG29_MASK)

#define BCTU_SFTRGR1_SFTRG30_MASK                (0x40000000U)
#define BCTU_SFTRGR1_SFTRG30_SHIFT               (30U)
#define BCTU_SFTRGR1_SFTRG30_WIDTH               (1U)
#define BCTU_SFTRGR1_SFTRG30(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR1_SFTRG30_SHIFT)) & BCTU_SFTRGR1_SFTRG30_MASK)

#define BCTU_SFTRGR1_SFTRG31_MASK                (0x80000000U)
#define BCTU_SFTRGR1_SFTRG31_SHIFT               (31U)
#define BCTU_SFTRGR1_SFTRG31_WIDTH               (1U)
#define BCTU_SFTRGR1_SFTRG31(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR1_SFTRG31_SHIFT)) & BCTU_SFTRGR1_SFTRG31_MASK)
/*! @} */

/*! @name SFTRGR2 - Software Trigger 2 */
/*! @{ */

#define BCTU_SFTRGR2_SFTRG32_MASK                (0x1U)
#define BCTU_SFTRGR2_SFTRG32_SHIFT               (0U)
#define BCTU_SFTRGR2_SFTRG32_WIDTH               (1U)
#define BCTU_SFTRGR2_SFTRG32(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR2_SFTRG32_SHIFT)) & BCTU_SFTRGR2_SFTRG32_MASK)

#define BCTU_SFTRGR2_SFTRG33_MASK                (0x2U)
#define BCTU_SFTRGR2_SFTRG33_SHIFT               (1U)
#define BCTU_SFTRGR2_SFTRG33_WIDTH               (1U)
#define BCTU_SFTRGR2_SFTRG33(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR2_SFTRG33_SHIFT)) & BCTU_SFTRGR2_SFTRG33_MASK)

#define BCTU_SFTRGR2_SFTRG34_MASK                (0x4U)
#define BCTU_SFTRGR2_SFTRG34_SHIFT               (2U)
#define BCTU_SFTRGR2_SFTRG34_WIDTH               (1U)
#define BCTU_SFTRGR2_SFTRG34(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR2_SFTRG34_SHIFT)) & BCTU_SFTRGR2_SFTRG34_MASK)

#define BCTU_SFTRGR2_SFTRG35_MASK                (0x8U)
#define BCTU_SFTRGR2_SFTRG35_SHIFT               (3U)
#define BCTU_SFTRGR2_SFTRG35_WIDTH               (1U)
#define BCTU_SFTRGR2_SFTRG35(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR2_SFTRG35_SHIFT)) & BCTU_SFTRGR2_SFTRG35_MASK)

#define BCTU_SFTRGR2_SFTRG36_MASK                (0x10U)
#define BCTU_SFTRGR2_SFTRG36_SHIFT               (4U)
#define BCTU_SFTRGR2_SFTRG36_WIDTH               (1U)
#define BCTU_SFTRGR2_SFTRG36(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR2_SFTRG36_SHIFT)) & BCTU_SFTRGR2_SFTRG36_MASK)

#define BCTU_SFTRGR2_SFTRG37_MASK                (0x20U)
#define BCTU_SFTRGR2_SFTRG37_SHIFT               (5U)
#define BCTU_SFTRGR2_SFTRG37_WIDTH               (1U)
#define BCTU_SFTRGR2_SFTRG37(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR2_SFTRG37_SHIFT)) & BCTU_SFTRGR2_SFTRG37_MASK)

#define BCTU_SFTRGR2_SFTRG38_MASK                (0x40U)
#define BCTU_SFTRGR2_SFTRG38_SHIFT               (6U)
#define BCTU_SFTRGR2_SFTRG38_WIDTH               (1U)
#define BCTU_SFTRGR2_SFTRG38(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR2_SFTRG38_SHIFT)) & BCTU_SFTRGR2_SFTRG38_MASK)

#define BCTU_SFTRGR2_SFTRG39_MASK                (0x80U)
#define BCTU_SFTRGR2_SFTRG39_SHIFT               (7U)
#define BCTU_SFTRGR2_SFTRG39_WIDTH               (1U)
#define BCTU_SFTRGR2_SFTRG39(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR2_SFTRG39_SHIFT)) & BCTU_SFTRGR2_SFTRG39_MASK)

#define BCTU_SFTRGR2_SFTRG40_MASK                (0x100U)
#define BCTU_SFTRGR2_SFTRG40_SHIFT               (8U)
#define BCTU_SFTRGR2_SFTRG40_WIDTH               (1U)
#define BCTU_SFTRGR2_SFTRG40(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR2_SFTRG40_SHIFT)) & BCTU_SFTRGR2_SFTRG40_MASK)

#define BCTU_SFTRGR2_SFTRG41_MASK                (0x200U)
#define BCTU_SFTRGR2_SFTRG41_SHIFT               (9U)
#define BCTU_SFTRGR2_SFTRG41_WIDTH               (1U)
#define BCTU_SFTRGR2_SFTRG41(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR2_SFTRG41_SHIFT)) & BCTU_SFTRGR2_SFTRG41_MASK)

#define BCTU_SFTRGR2_SFTRG42_MASK                (0x400U)
#define BCTU_SFTRGR2_SFTRG42_SHIFT               (10U)
#define BCTU_SFTRGR2_SFTRG42_WIDTH               (1U)
#define BCTU_SFTRGR2_SFTRG42(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR2_SFTRG42_SHIFT)) & BCTU_SFTRGR2_SFTRG42_MASK)

#define BCTU_SFTRGR2_SFTRG43_MASK                (0x800U)
#define BCTU_SFTRGR2_SFTRG43_SHIFT               (11U)
#define BCTU_SFTRGR2_SFTRG43_WIDTH               (1U)
#define BCTU_SFTRGR2_SFTRG43(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR2_SFTRG43_SHIFT)) & BCTU_SFTRGR2_SFTRG43_MASK)

#define BCTU_SFTRGR2_SFTRG44_MASK                (0x1000U)
#define BCTU_SFTRGR2_SFTRG44_SHIFT               (12U)
#define BCTU_SFTRGR2_SFTRG44_WIDTH               (1U)
#define BCTU_SFTRGR2_SFTRG44(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR2_SFTRG44_SHIFT)) & BCTU_SFTRGR2_SFTRG44_MASK)

#define BCTU_SFTRGR2_SFTRG45_MASK                (0x2000U)
#define BCTU_SFTRGR2_SFTRG45_SHIFT               (13U)
#define BCTU_SFTRGR2_SFTRG45_WIDTH               (1U)
#define BCTU_SFTRGR2_SFTRG45(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR2_SFTRG45_SHIFT)) & BCTU_SFTRGR2_SFTRG45_MASK)

#define BCTU_SFTRGR2_SFTRG46_MASK                (0x4000U)
#define BCTU_SFTRGR2_SFTRG46_SHIFT               (14U)
#define BCTU_SFTRGR2_SFTRG46_WIDTH               (1U)
#define BCTU_SFTRGR2_SFTRG46(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR2_SFTRG46_SHIFT)) & BCTU_SFTRGR2_SFTRG46_MASK)

#define BCTU_SFTRGR2_SFTRG47_MASK                (0x8000U)
#define BCTU_SFTRGR2_SFTRG47_SHIFT               (15U)
#define BCTU_SFTRGR2_SFTRG47_WIDTH               (1U)
#define BCTU_SFTRGR2_SFTRG47(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR2_SFTRG47_SHIFT)) & BCTU_SFTRGR2_SFTRG47_MASK)

#define BCTU_SFTRGR2_SFTRG48_MASK                (0x10000U)
#define BCTU_SFTRGR2_SFTRG48_SHIFT               (16U)
#define BCTU_SFTRGR2_SFTRG48_WIDTH               (1U)
#define BCTU_SFTRGR2_SFTRG48(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR2_SFTRG48_SHIFT)) & BCTU_SFTRGR2_SFTRG48_MASK)

#define BCTU_SFTRGR2_SFTRG49_MASK                (0x20000U)
#define BCTU_SFTRGR2_SFTRG49_SHIFT               (17U)
#define BCTU_SFTRGR2_SFTRG49_WIDTH               (1U)
#define BCTU_SFTRGR2_SFTRG49(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR2_SFTRG49_SHIFT)) & BCTU_SFTRGR2_SFTRG49_MASK)

#define BCTU_SFTRGR2_SFTRG50_MASK                (0x40000U)
#define BCTU_SFTRGR2_SFTRG50_SHIFT               (18U)
#define BCTU_SFTRGR2_SFTRG50_WIDTH               (1U)
#define BCTU_SFTRGR2_SFTRG50(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR2_SFTRG50_SHIFT)) & BCTU_SFTRGR2_SFTRG50_MASK)

#define BCTU_SFTRGR2_SFTRG51_MASK                (0x80000U)
#define BCTU_SFTRGR2_SFTRG51_SHIFT               (19U)
#define BCTU_SFTRGR2_SFTRG51_WIDTH               (1U)
#define BCTU_SFTRGR2_SFTRG51(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR2_SFTRG51_SHIFT)) & BCTU_SFTRGR2_SFTRG51_MASK)

#define BCTU_SFTRGR2_SFTRG52_MASK                (0x100000U)
#define BCTU_SFTRGR2_SFTRG52_SHIFT               (20U)
#define BCTU_SFTRGR2_SFTRG52_WIDTH               (1U)
#define BCTU_SFTRGR2_SFTRG52(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR2_SFTRG52_SHIFT)) & BCTU_SFTRGR2_SFTRG52_MASK)

#define BCTU_SFTRGR2_SFTRG53_MASK                (0x200000U)
#define BCTU_SFTRGR2_SFTRG53_SHIFT               (21U)
#define BCTU_SFTRGR2_SFTRG53_WIDTH               (1U)
#define BCTU_SFTRGR2_SFTRG53(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR2_SFTRG53_SHIFT)) & BCTU_SFTRGR2_SFTRG53_MASK)

#define BCTU_SFTRGR2_SFTRG54_MASK                (0x400000U)
#define BCTU_SFTRGR2_SFTRG54_SHIFT               (22U)
#define BCTU_SFTRGR2_SFTRG54_WIDTH               (1U)
#define BCTU_SFTRGR2_SFTRG54(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR2_SFTRG54_SHIFT)) & BCTU_SFTRGR2_SFTRG54_MASK)

#define BCTU_SFTRGR2_SFTRG55_MASK                (0x800000U)
#define BCTU_SFTRGR2_SFTRG55_SHIFT               (23U)
#define BCTU_SFTRGR2_SFTRG55_WIDTH               (1U)
#define BCTU_SFTRGR2_SFTRG55(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR2_SFTRG55_SHIFT)) & BCTU_SFTRGR2_SFTRG55_MASK)

#define BCTU_SFTRGR2_SFTRG56_MASK                (0x1000000U)
#define BCTU_SFTRGR2_SFTRG56_SHIFT               (24U)
#define BCTU_SFTRGR2_SFTRG56_WIDTH               (1U)
#define BCTU_SFTRGR2_SFTRG56(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR2_SFTRG56_SHIFT)) & BCTU_SFTRGR2_SFTRG56_MASK)

#define BCTU_SFTRGR2_SFTRG57_MASK                (0x2000000U)
#define BCTU_SFTRGR2_SFTRG57_SHIFT               (25U)
#define BCTU_SFTRGR2_SFTRG57_WIDTH               (1U)
#define BCTU_SFTRGR2_SFTRG57(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR2_SFTRG57_SHIFT)) & BCTU_SFTRGR2_SFTRG57_MASK)

#define BCTU_SFTRGR2_SFTRG58_MASK                (0x4000000U)
#define BCTU_SFTRGR2_SFTRG58_SHIFT               (26U)
#define BCTU_SFTRGR2_SFTRG58_WIDTH               (1U)
#define BCTU_SFTRGR2_SFTRG58(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR2_SFTRG58_SHIFT)) & BCTU_SFTRGR2_SFTRG58_MASK)

#define BCTU_SFTRGR2_SFTRG59_MASK                (0x8000000U)
#define BCTU_SFTRGR2_SFTRG59_SHIFT               (27U)
#define BCTU_SFTRGR2_SFTRG59_WIDTH               (1U)
#define BCTU_SFTRGR2_SFTRG59(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR2_SFTRG59_SHIFT)) & BCTU_SFTRGR2_SFTRG59_MASK)

#define BCTU_SFTRGR2_SFTRG60_MASK                (0x10000000U)
#define BCTU_SFTRGR2_SFTRG60_SHIFT               (28U)
#define BCTU_SFTRGR2_SFTRG60_WIDTH               (1U)
#define BCTU_SFTRGR2_SFTRG60(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR2_SFTRG60_SHIFT)) & BCTU_SFTRGR2_SFTRG60_MASK)

#define BCTU_SFTRGR2_SFTRG61_MASK                (0x20000000U)
#define BCTU_SFTRGR2_SFTRG61_SHIFT               (29U)
#define BCTU_SFTRGR2_SFTRG61_WIDTH               (1U)
#define BCTU_SFTRGR2_SFTRG61(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR2_SFTRG61_SHIFT)) & BCTU_SFTRGR2_SFTRG61_MASK)

#define BCTU_SFTRGR2_SFTRG62_MASK                (0x40000000U)
#define BCTU_SFTRGR2_SFTRG62_SHIFT               (30U)
#define BCTU_SFTRGR2_SFTRG62_WIDTH               (1U)
#define BCTU_SFTRGR2_SFTRG62(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR2_SFTRG62_SHIFT)) & BCTU_SFTRGR2_SFTRG62_MASK)

#define BCTU_SFTRGR2_SFTRG63_MASK                (0x80000000U)
#define BCTU_SFTRGR2_SFTRG63_SHIFT               (31U)
#define BCTU_SFTRGR2_SFTRG63_WIDTH               (1U)
#define BCTU_SFTRGR2_SFTRG63(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR2_SFTRG63_SHIFT)) & BCTU_SFTRGR2_SFTRG63_MASK)
/*! @} */

/*! @name SFTRGR3 - Software Trigger 3 */
/*! @{ */

#define BCTU_SFTRGR3_SFTRG64_MASK                (0x1U)
#define BCTU_SFTRGR3_SFTRG64_SHIFT               (0U)
#define BCTU_SFTRGR3_SFTRG64_WIDTH               (1U)
#define BCTU_SFTRGR3_SFTRG64(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR3_SFTRG64_SHIFT)) & BCTU_SFTRGR3_SFTRG64_MASK)

#define BCTU_SFTRGR3_SFTRG65_MASK                (0x2U)
#define BCTU_SFTRGR3_SFTRG65_SHIFT               (1U)
#define BCTU_SFTRGR3_SFTRG65_WIDTH               (1U)
#define BCTU_SFTRGR3_SFTRG65(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR3_SFTRG65_SHIFT)) & BCTU_SFTRGR3_SFTRG65_MASK)

#define BCTU_SFTRGR3_SFTRG66_MASK                (0x4U)
#define BCTU_SFTRGR3_SFTRG66_SHIFT               (2U)
#define BCTU_SFTRGR3_SFTRG66_WIDTH               (1U)
#define BCTU_SFTRGR3_SFTRG66(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR3_SFTRG66_SHIFT)) & BCTU_SFTRGR3_SFTRG66_MASK)

#define BCTU_SFTRGR3_SFTRG67_MASK                (0x8U)
#define BCTU_SFTRGR3_SFTRG67_SHIFT               (3U)
#define BCTU_SFTRGR3_SFTRG67_WIDTH               (1U)
#define BCTU_SFTRGR3_SFTRG67(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR3_SFTRG67_SHIFT)) & BCTU_SFTRGR3_SFTRG67_MASK)

#define BCTU_SFTRGR3_SFTRG68_MASK                (0x10U)
#define BCTU_SFTRGR3_SFTRG68_SHIFT               (4U)
#define BCTU_SFTRGR3_SFTRG68_WIDTH               (1U)
#define BCTU_SFTRGR3_SFTRG68(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR3_SFTRG68_SHIFT)) & BCTU_SFTRGR3_SFTRG68_MASK)

#define BCTU_SFTRGR3_SFTRG69_MASK                (0x20U)
#define BCTU_SFTRGR3_SFTRG69_SHIFT               (5U)
#define BCTU_SFTRGR3_SFTRG69_WIDTH               (1U)
#define BCTU_SFTRGR3_SFTRG69(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR3_SFTRG69_SHIFT)) & BCTU_SFTRGR3_SFTRG69_MASK)

#define BCTU_SFTRGR3_SFTRG70_MASK                (0x40U)
#define BCTU_SFTRGR3_SFTRG70_SHIFT               (6U)
#define BCTU_SFTRGR3_SFTRG70_WIDTH               (1U)
#define BCTU_SFTRGR3_SFTRG70(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR3_SFTRG70_SHIFT)) & BCTU_SFTRGR3_SFTRG70_MASK)

#define BCTU_SFTRGR3_SFTRG71_MASK                (0x80U)
#define BCTU_SFTRGR3_SFTRG71_SHIFT               (7U)
#define BCTU_SFTRGR3_SFTRG71_WIDTH               (1U)
#define BCTU_SFTRGR3_SFTRG71(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_SFTRGR3_SFTRG71_SHIFT)) & BCTU_SFTRGR3_SFTRG71_MASK)
/*! @} */

/*! @name ADCDR - ADC0 Result Data..ADC2 Result Data */
/*! @{ */

#define BCTU_ADCDR_ADC_DATA_MASK                 (0x7FFFU)
#define BCTU_ADCDR_ADC_DATA_SHIFT                (0U)
#define BCTU_ADCDR_ADC_DATA_WIDTH                (15U)
#define BCTU_ADCDR_ADC_DATA(x)                   (((uint32_t)(((uint32_t)(x)) << BCTU_ADCDR_ADC_DATA_SHIFT)) & BCTU_ADCDR_ADC_DATA_MASK)

#define BCTU_ADCDR_LAST_MASK                     (0x10000U)
#define BCTU_ADCDR_LAST_SHIFT                    (16U)
#define BCTU_ADCDR_LAST_WIDTH                    (1U)
#define BCTU_ADCDR_LAST(x)                       (((uint32_t)(((uint32_t)(x)) << BCTU_ADCDR_LAST_SHIFT)) & BCTU_ADCDR_LAST_MASK)

#define BCTU_ADCDR_LIST_MASK                     (0x20000U)
#define BCTU_ADCDR_LIST_SHIFT                    (17U)
#define BCTU_ADCDR_LIST_WIDTH                    (1U)
#define BCTU_ADCDR_LIST(x)                       (((uint32_t)(((uint32_t)(x)) << BCTU_ADCDR_LIST_SHIFT)) & BCTU_ADCDR_LIST_MASK)

#define BCTU_ADCDR_CH_MASK                       (0x1FC0000U)
#define BCTU_ADCDR_CH_SHIFT                      (18U)
#define BCTU_ADCDR_CH_WIDTH                      (7U)
#define BCTU_ADCDR_CH(x)                         (((uint32_t)(((uint32_t)(x)) << BCTU_ADCDR_CH_SHIFT)) & BCTU_ADCDR_CH_MASK)

#define BCTU_ADCDR_TRG_SRC_MASK                  (0xFE000000U)
#define BCTU_ADCDR_TRG_SRC_SHIFT                 (25U)
#define BCTU_ADCDR_TRG_SRC_WIDTH                 (7U)
#define BCTU_ADCDR_TRG_SRC(x)                    (((uint32_t)(((uint32_t)(x)) << BCTU_ADCDR_TRG_SRC_SHIFT)) & BCTU_ADCDR_TRG_SRC_MASK)
/*! @} */

/*! @name LISTSTAR - CL Size Status */
/*! @{ */

#define BCTU_LISTSTAR_LISTSZ_MASK                (0xFFU)
#define BCTU_LISTSTAR_LISTSZ_SHIFT               (0U)
#define BCTU_LISTSTAR_LISTSZ_WIDTH               (8U)
#define BCTU_LISTSTAR_LISTSZ(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_LISTSTAR_LISTSZ_SHIFT)) & BCTU_LISTSTAR_LISTSZ_MASK)
/*! @} */

/*! @name LISTCHR - CL Channel Address */
/*! @{ */

#define BCTU_LISTCHR_ADC_CHL_y_plus_1_MASK       (0x7FU)
#define BCTU_LISTCHR_ADC_CHL_y_plus_1_SHIFT      (0U)
#define BCTU_LISTCHR_ADC_CHL_y_plus_1_WIDTH      (7U)
#define BCTU_LISTCHR_ADC_CHL_y_plus_1(x)         (((uint32_t)(((uint32_t)(x)) << BCTU_LISTCHR_ADC_CHL_y_plus_1_SHIFT)) & BCTU_LISTCHR_ADC_CHL_y_plus_1_MASK)

#define BCTU_LISTCHR_NEXT_CH_WAIT_ON_TRIG_y_plus_1_MASK (0x4000U)
#define BCTU_LISTCHR_NEXT_CH_WAIT_ON_TRIG_y_plus_1_SHIFT (14U)
#define BCTU_LISTCHR_NEXT_CH_WAIT_ON_TRIG_y_plus_1_WIDTH (1U)
#define BCTU_LISTCHR_NEXT_CH_WAIT_ON_TRIG_y_plus_1(x) (((uint32_t)(((uint32_t)(x)) << BCTU_LISTCHR_NEXT_CH_WAIT_ON_TRIG_y_plus_1_SHIFT)) & BCTU_LISTCHR_NEXT_CH_WAIT_ON_TRIG_y_plus_1_MASK)

#define BCTU_LISTCHR_LAST_y_plus_1_MASK          (0x8000U)
#define BCTU_LISTCHR_LAST_y_plus_1_SHIFT         (15U)
#define BCTU_LISTCHR_LAST_y_plus_1_WIDTH         (1U)
#define BCTU_LISTCHR_LAST_y_plus_1(x)            (((uint32_t)(((uint32_t)(x)) << BCTU_LISTCHR_LAST_y_plus_1_SHIFT)) & BCTU_LISTCHR_LAST_y_plus_1_MASK)

#define BCTU_LISTCHR_ADC_CH_y_MASK               (0x7F0000U)
#define BCTU_LISTCHR_ADC_CH_y_SHIFT              (16U)
#define BCTU_LISTCHR_ADC_CH_y_WIDTH              (7U)
#define BCTU_LISTCHR_ADC_CH_y(x)                 (((uint32_t)(((uint32_t)(x)) << BCTU_LISTCHR_ADC_CH_y_SHIFT)) & BCTU_LISTCHR_ADC_CH_y_MASK)

#define BCTU_LISTCHR_NEXT_CH_WAIT_ON_TRIG_y_MASK (0x40000000U)
#define BCTU_LISTCHR_NEXT_CH_WAIT_ON_TRIG_y_SHIFT (30U)
#define BCTU_LISTCHR_NEXT_CH_WAIT_ON_TRIG_y_WIDTH (1U)
#define BCTU_LISTCHR_NEXT_CH_WAIT_ON_TRIG_y(x)   (((uint32_t)(((uint32_t)(x)) << BCTU_LISTCHR_NEXT_CH_WAIT_ON_TRIG_y_SHIFT)) & BCTU_LISTCHR_NEXT_CH_WAIT_ON_TRIG_y_MASK)

#define BCTU_LISTCHR_LAST_y_MASK                 (0x80000000U)
#define BCTU_LISTCHR_LAST_y_SHIFT                (31U)
#define BCTU_LISTCHR_LAST_y_WIDTH                (1U)
#define BCTU_LISTCHR_LAST_y(x)                   (((uint32_t)(((uint32_t)(x)) << BCTU_LISTCHR_LAST_y_SHIFT)) & BCTU_LISTCHR_LAST_y_MASK)
/*! @} */

/*! @name FIFO1DR - FIFO Result Data */
/*! @{ */

#define BCTU_FIFO1DR_ADC_DATA_MASK               (0x7FFFU)
#define BCTU_FIFO1DR_ADC_DATA_SHIFT              (0U)
#define BCTU_FIFO1DR_ADC_DATA_WIDTH              (15U)
#define BCTU_FIFO1DR_ADC_DATA(x)                 (((uint32_t)(((uint32_t)(x)) << BCTU_FIFO1DR_ADC_DATA_SHIFT)) & BCTU_FIFO1DR_ADC_DATA_MASK)

#define BCTU_FIFO1DR_ADC_NUM_MASK                (0x30000U)
#define BCTU_FIFO1DR_ADC_NUM_SHIFT               (16U)
#define BCTU_FIFO1DR_ADC_NUM_WIDTH               (2U)
#define BCTU_FIFO1DR_ADC_NUM(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_FIFO1DR_ADC_NUM_SHIFT)) & BCTU_FIFO1DR_ADC_NUM_MASK)

#define BCTU_FIFO1DR_CH_MASK                     (0x1FC0000U)
#define BCTU_FIFO1DR_CH_SHIFT                    (18U)
#define BCTU_FIFO1DR_CH_WIDTH                    (7U)
#define BCTU_FIFO1DR_CH(x)                       (((uint32_t)(((uint32_t)(x)) << BCTU_FIFO1DR_CH_SHIFT)) & BCTU_FIFO1DR_CH_MASK)

#define BCTU_FIFO1DR_TRG_SRC_MASK                (0xFE000000U)
#define BCTU_FIFO1DR_TRG_SRC_SHIFT               (25U)
#define BCTU_FIFO1DR_TRG_SRC_WIDTH               (7U)
#define BCTU_FIFO1DR_TRG_SRC(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_FIFO1DR_TRG_SRC_SHIFT)) & BCTU_FIFO1DR_TRG_SRC_MASK)
/*! @} */

/*! @name FIFO2DR - FIFO Result Data */
/*! @{ */

#define BCTU_FIFO2DR_ADC_DATA_MASK               (0x7FFFU)
#define BCTU_FIFO2DR_ADC_DATA_SHIFT              (0U)
#define BCTU_FIFO2DR_ADC_DATA_WIDTH              (15U)
#define BCTU_FIFO2DR_ADC_DATA(x)                 (((uint32_t)(((uint32_t)(x)) << BCTU_FIFO2DR_ADC_DATA_SHIFT)) & BCTU_FIFO2DR_ADC_DATA_MASK)

#define BCTU_FIFO2DR_ADC_NUM_MASK                (0x30000U)
#define BCTU_FIFO2DR_ADC_NUM_SHIFT               (16U)
#define BCTU_FIFO2DR_ADC_NUM_WIDTH               (2U)
#define BCTU_FIFO2DR_ADC_NUM(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_FIFO2DR_ADC_NUM_SHIFT)) & BCTU_FIFO2DR_ADC_NUM_MASK)

#define BCTU_FIFO2DR_CH_MASK                     (0x1FC0000U)
#define BCTU_FIFO2DR_CH_SHIFT                    (18U)
#define BCTU_FIFO2DR_CH_WIDTH                    (7U)
#define BCTU_FIFO2DR_CH(x)                       (((uint32_t)(((uint32_t)(x)) << BCTU_FIFO2DR_CH_SHIFT)) & BCTU_FIFO2DR_CH_MASK)

#define BCTU_FIFO2DR_TRG_SRC_MASK                (0xFE000000U)
#define BCTU_FIFO2DR_TRG_SRC_SHIFT               (25U)
#define BCTU_FIFO2DR_TRG_SRC_WIDTH               (7U)
#define BCTU_FIFO2DR_TRG_SRC(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_FIFO2DR_TRG_SRC_SHIFT)) & BCTU_FIFO2DR_TRG_SRC_MASK)
/*! @} */

/*! @name FIFOCR - FIFO Control */
/*! @{ */

#define BCTU_FIFOCR_IEN_FIFO1_MASK               (0x10000U)
#define BCTU_FIFOCR_IEN_FIFO1_SHIFT              (16U)
#define BCTU_FIFOCR_IEN_FIFO1_WIDTH              (1U)
#define BCTU_FIFOCR_IEN_FIFO1(x)                 (((uint32_t)(((uint32_t)(x)) << BCTU_FIFOCR_IEN_FIFO1_SHIFT)) & BCTU_FIFOCR_IEN_FIFO1_MASK)

#define BCTU_FIFOCR_IEN_FIFO2_MASK               (0x20000U)
#define BCTU_FIFOCR_IEN_FIFO2_SHIFT              (17U)
#define BCTU_FIFOCR_IEN_FIFO2_WIDTH              (1U)
#define BCTU_FIFOCR_IEN_FIFO2(x)                 (((uint32_t)(((uint32_t)(x)) << BCTU_FIFOCR_IEN_FIFO2_SHIFT)) & BCTU_FIFOCR_IEN_FIFO2_MASK)

#define BCTU_FIFOCR_DMA_EN_FIFO1_MASK            (0x1000000U)
#define BCTU_FIFOCR_DMA_EN_FIFO1_SHIFT           (24U)
#define BCTU_FIFOCR_DMA_EN_FIFO1_WIDTH           (1U)
#define BCTU_FIFOCR_DMA_EN_FIFO1(x)              (((uint32_t)(((uint32_t)(x)) << BCTU_FIFOCR_DMA_EN_FIFO1_SHIFT)) & BCTU_FIFOCR_DMA_EN_FIFO1_MASK)

#define BCTU_FIFOCR_DMA_EN_FIFO2_MASK            (0x2000000U)
#define BCTU_FIFOCR_DMA_EN_FIFO2_SHIFT           (25U)
#define BCTU_FIFOCR_DMA_EN_FIFO2_WIDTH           (1U)
#define BCTU_FIFOCR_DMA_EN_FIFO2(x)              (((uint32_t)(((uint32_t)(x)) << BCTU_FIFOCR_DMA_EN_FIFO2_SHIFT)) & BCTU_FIFOCR_DMA_EN_FIFO2_MASK)
/*! @} */

/*! @name FIFOWM - FIFO Watermark Configuration */
/*! @{ */

#define BCTU_FIFOWM_WM_FIFO1_MASK                (0xFU)
#define BCTU_FIFOWM_WM_FIFO1_SHIFT               (0U)
#define BCTU_FIFOWM_WM_FIFO1_WIDTH               (4U)
#define BCTU_FIFOWM_WM_FIFO1(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_FIFOWM_WM_FIFO1_SHIFT)) & BCTU_FIFOWM_WM_FIFO1_MASK)

#define BCTU_FIFOWM_WM_FIFO2_MASK                (0x700U)
#define BCTU_FIFOWM_WM_FIFO2_SHIFT               (8U)
#define BCTU_FIFOWM_WM_FIFO2_WIDTH               (3U)
#define BCTU_FIFOWM_WM_FIFO2(x)                  (((uint32_t)(((uint32_t)(x)) << BCTU_FIFOWM_WM_FIFO2_SHIFT)) & BCTU_FIFOWM_WM_FIFO2_MASK)
/*! @} */

/*! @name FIFOERR - FIFO Error/Status */
/*! @{ */

#define BCTU_FIFOERR_WM_INT_FIFO1_MASK           (0x10000U)
#define BCTU_FIFOERR_WM_INT_FIFO1_SHIFT          (16U)
#define BCTU_FIFOERR_WM_INT_FIFO1_WIDTH          (1U)
#define BCTU_FIFOERR_WM_INT_FIFO1(x)             (((uint32_t)(((uint32_t)(x)) << BCTU_FIFOERR_WM_INT_FIFO1_SHIFT)) & BCTU_FIFOERR_WM_INT_FIFO1_MASK)

#define BCTU_FIFOERR_WM_INT_FIFO2_MASK           (0x20000U)
#define BCTU_FIFOERR_WM_INT_FIFO2_SHIFT          (17U)
#define BCTU_FIFOERR_WM_INT_FIFO2_WIDTH          (1U)
#define BCTU_FIFOERR_WM_INT_FIFO2(x)             (((uint32_t)(((uint32_t)(x)) << BCTU_FIFOERR_WM_INT_FIFO2_SHIFT)) & BCTU_FIFOERR_WM_INT_FIFO2_MASK)

#define BCTU_FIFOERR_OVR_ERR_FIFO1_MASK          (0x1000000U)
#define BCTU_FIFOERR_OVR_ERR_FIFO1_SHIFT         (24U)
#define BCTU_FIFOERR_OVR_ERR_FIFO1_WIDTH         (1U)
#define BCTU_FIFOERR_OVR_ERR_FIFO1(x)            (((uint32_t)(((uint32_t)(x)) << BCTU_FIFOERR_OVR_ERR_FIFO1_SHIFT)) & BCTU_FIFOERR_OVR_ERR_FIFO1_MASK)

#define BCTU_FIFOERR_UNDR_ERR_FIFO1_MASK         (0x2000000U)
#define BCTU_FIFOERR_UNDR_ERR_FIFO1_SHIFT        (25U)
#define BCTU_FIFOERR_UNDR_ERR_FIFO1_WIDTH        (1U)
#define BCTU_FIFOERR_UNDR_ERR_FIFO1(x)           (((uint32_t)(((uint32_t)(x)) << BCTU_FIFOERR_UNDR_ERR_FIFO1_SHIFT)) & BCTU_FIFOERR_UNDR_ERR_FIFO1_MASK)

#define BCTU_FIFOERR_OVR_ERR_FIFO2_MASK          (0x4000000U)
#define BCTU_FIFOERR_OVR_ERR_FIFO2_SHIFT         (26U)
#define BCTU_FIFOERR_OVR_ERR_FIFO2_WIDTH         (1U)
#define BCTU_FIFOERR_OVR_ERR_FIFO2(x)            (((uint32_t)(((uint32_t)(x)) << BCTU_FIFOERR_OVR_ERR_FIFO2_SHIFT)) & BCTU_FIFOERR_OVR_ERR_FIFO2_MASK)

#define BCTU_FIFOERR_UNDR_ERR_FIFO2_MASK         (0x8000000U)
#define BCTU_FIFOERR_UNDR_ERR_FIFO2_SHIFT        (27U)
#define BCTU_FIFOERR_UNDR_ERR_FIFO2_WIDTH        (1U)
#define BCTU_FIFOERR_UNDR_ERR_FIFO2(x)           (((uint32_t)(((uint32_t)(x)) << BCTU_FIFOERR_UNDR_ERR_FIFO2_SHIFT)) & BCTU_FIFOERR_UNDR_ERR_FIFO2_MASK)
/*! @} */

/*! @name FIFOSR - FIFO Status */
/*! @{ */

#define BCTU_FIFOSR_FULL_FIFO1_MASK              (0x1U)
#define BCTU_FIFOSR_FULL_FIFO1_SHIFT             (0U)
#define BCTU_FIFOSR_FULL_FIFO1_WIDTH             (1U)
#define BCTU_FIFOSR_FULL_FIFO1(x)                (((uint32_t)(((uint32_t)(x)) << BCTU_FIFOSR_FULL_FIFO1_SHIFT)) & BCTU_FIFOSR_FULL_FIFO1_MASK)

#define BCTU_FIFOSR_FULL_FIFO2_MASK              (0x2U)
#define BCTU_FIFOSR_FULL_FIFO2_SHIFT             (1U)
#define BCTU_FIFOSR_FULL_FIFO2_WIDTH             (1U)
#define BCTU_FIFOSR_FULL_FIFO2(x)                (((uint32_t)(((uint32_t)(x)) << BCTU_FIFOSR_FULL_FIFO2_SHIFT)) & BCTU_FIFOSR_FULL_FIFO2_MASK)
/*! @} */

/*! @name FIFOCNTR - FIFO Counter */
/*! @{ */

#define BCTU_FIFOCNTR_CNTR_FIFO1_MASK            (0x1FU)
#define BCTU_FIFOCNTR_CNTR_FIFO1_SHIFT           (0U)
#define BCTU_FIFOCNTR_CNTR_FIFO1_WIDTH           (5U)
#define BCTU_FIFOCNTR_CNTR_FIFO1(x)              (((uint32_t)(((uint32_t)(x)) << BCTU_FIFOCNTR_CNTR_FIFO1_SHIFT)) & BCTU_FIFOCNTR_CNTR_FIFO1_MASK)

#define BCTU_FIFOCNTR_CNTR_FIFO2_MASK            (0xF00U)
#define BCTU_FIFOCNTR_CNTR_FIFO2_SHIFT           (8U)
#define BCTU_FIFOCNTR_CNTR_FIFO2_WIDTH           (4U)
#define BCTU_FIFOCNTR_CNTR_FIFO2(x)              (((uint32_t)(((uint32_t)(x)) << BCTU_FIFOCNTR_CNTR_FIFO2_SHIFT)) & BCTU_FIFOCNTR_CNTR_FIFO2_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group BCTU_Register_Masks */

/*!
 * @}
 */ /* end of group BCTU_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_BCTU_H_) */
