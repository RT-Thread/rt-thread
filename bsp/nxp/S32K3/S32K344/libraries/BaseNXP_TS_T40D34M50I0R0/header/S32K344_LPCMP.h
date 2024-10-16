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
 * @file S32K344_LPCMP.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_LPCMP
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
#if !defined(S32K344_LPCMP_H_)  /* Check if memory map has not been already included */
#define S32K344_LPCMP_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- LPCMP Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPCMP_Peripheral_Access_Layer LPCMP Peripheral Access Layer
 * @{
 */

/** LPCMP - Register Layout Typedef */
typedef struct {
  __I  uint32_t VERID;                             /**< Version ID Register, offset: 0x0 */
  __I  uint32_t PARAM;                             /**< Parameter Register, offset: 0x4 */
  __IO uint32_t CCR0;                              /**< Comparator Control Register 0, offset: 0x8 */
  __IO uint32_t CCR1;                              /**< Comparator Control Register 1, offset: 0xC */
  __IO uint32_t CCR2;                              /**< Comparator Control Register 2, offset: 0x10 */
  uint8_t RESERVED_0[4];
  __IO uint32_t DCR;                               /**< DAC Control Register, offset: 0x18 */
  __IO uint32_t IER;                               /**< Interrupt Enable Register, offset: 0x1C */
  __IO uint32_t CSR;                               /**< Comparator Status Register, offset: 0x20 */
  __IO uint32_t RRCR0;                             /**< Round Robin Control Register 0, offset: 0x24 */
  __IO uint32_t RRCR1;                             /**< Round Robin Control Register 1, offset: 0x28 */
  __IO uint32_t RRCSR;                             /**< Round Robin Control and Status Register, offset: 0x2C */
  __IO uint32_t RRSR;                              /**< Round Robin Status Register, offset: 0x30 */
} LPCMP_Type, *LPCMP_MemMapPtr;

/** Number of instances of the LPCMP module. */
#define LPCMP_INSTANCE_COUNT                     (3u)

/* LPCMP - Peripheral instance base addresses */
/** Peripheral LPCMP_0 base address */
#define IP_LPCMP_0_BASE                          (0x40370000u)
/** Peripheral LPCMP_0 base pointer */
#define IP_LPCMP_0                               ((LPCMP_Type *)IP_LPCMP_0_BASE)
/** Peripheral LPCMP_1 base address */
#define IP_LPCMP_1_BASE                          (0x40374000u)
/** Peripheral LPCMP_1 base pointer */
#define IP_LPCMP_1                               ((LPCMP_Type *)IP_LPCMP_1_BASE)
/** Peripheral LPCMP_2 base address */
#define IP_LPCMP_2_BASE                          (0x404E8000u)
/** Peripheral LPCMP_2 base pointer */
#define IP_LPCMP_2                               ((LPCMP_Type *)IP_LPCMP_2_BASE)
/** Array initializer of LPCMP peripheral base addresses */
#define IP_LPCMP_BASE_ADDRS                      { IP_LPCMP_0_BASE, IP_LPCMP_1_BASE, IP_LPCMP_2_BASE }
/** Array initializer of LPCMP peripheral base pointers */
#define IP_LPCMP_BASE_PTRS                       { IP_LPCMP_0, IP_LPCMP_1, IP_LPCMP_2 }

/* ----------------------------------------------------------------------------
   -- LPCMP Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPCMP_Register_Masks LPCMP Register Masks
 * @{
 */

/*! @name VERID - Version ID Register */
/*! @{ */

#define LPCMP_VERID_FEATURE_MASK                 (0xFFFFU)
#define LPCMP_VERID_FEATURE_SHIFT                (0U)
#define LPCMP_VERID_FEATURE_WIDTH                (16U)
#define LPCMP_VERID_FEATURE(x)                   (((uint32_t)(((uint32_t)(x)) << LPCMP_VERID_FEATURE_SHIFT)) & LPCMP_VERID_FEATURE_MASK)

#define LPCMP_VERID_MINOR_MASK                   (0xFF0000U)
#define LPCMP_VERID_MINOR_SHIFT                  (16U)
#define LPCMP_VERID_MINOR_WIDTH                  (8U)
#define LPCMP_VERID_MINOR(x)                     (((uint32_t)(((uint32_t)(x)) << LPCMP_VERID_MINOR_SHIFT)) & LPCMP_VERID_MINOR_MASK)

#define LPCMP_VERID_MAJOR_MASK                   (0xFF000000U)
#define LPCMP_VERID_MAJOR_SHIFT                  (24U)
#define LPCMP_VERID_MAJOR_WIDTH                  (8U)
#define LPCMP_VERID_MAJOR(x)                     (((uint32_t)(((uint32_t)(x)) << LPCMP_VERID_MAJOR_SHIFT)) & LPCMP_VERID_MAJOR_MASK)
/*! @} */

/*! @name PARAM - Parameter Register */
/*! @{ */

#define LPCMP_PARAM_DAC_RES_MASK                 (0xFU)
#define LPCMP_PARAM_DAC_RES_SHIFT                (0U)
#define LPCMP_PARAM_DAC_RES_WIDTH                (4U)
#define LPCMP_PARAM_DAC_RES(x)                   (((uint32_t)(((uint32_t)(x)) << LPCMP_PARAM_DAC_RES_SHIFT)) & LPCMP_PARAM_DAC_RES_MASK)
/*! @} */

/*! @name CCR0 - Comparator Control Register 0 */
/*! @{ */

#define LPCMP_CCR0_CMP_EN_MASK                   (0x1U)
#define LPCMP_CCR0_CMP_EN_SHIFT                  (0U)
#define LPCMP_CCR0_CMP_EN_WIDTH                  (1U)
#define LPCMP_CCR0_CMP_EN(x)                     (((uint32_t)(((uint32_t)(x)) << LPCMP_CCR0_CMP_EN_SHIFT)) & LPCMP_CCR0_CMP_EN_MASK)

#define LPCMP_CCR0_CMP_STOP_EN_MASK              (0x2U)
#define LPCMP_CCR0_CMP_STOP_EN_SHIFT             (1U)
#define LPCMP_CCR0_CMP_STOP_EN_WIDTH             (1U)
#define LPCMP_CCR0_CMP_STOP_EN(x)                (((uint32_t)(((uint32_t)(x)) << LPCMP_CCR0_CMP_STOP_EN_SHIFT)) & LPCMP_CCR0_CMP_STOP_EN_MASK)

#define LPCMP_CCR0_LINKEN_MASK                   (0x4U)
#define LPCMP_CCR0_LINKEN_SHIFT                  (2U)
#define LPCMP_CCR0_LINKEN_WIDTH                  (1U)
#define LPCMP_CCR0_LINKEN(x)                     (((uint32_t)(((uint32_t)(x)) << LPCMP_CCR0_LINKEN_SHIFT)) & LPCMP_CCR0_LINKEN_MASK)
/*! @} */

/*! @name CCR1 - Comparator Control Register 1 */
/*! @{ */

#define LPCMP_CCR1_WINDOW_EN_MASK                (0x1U)
#define LPCMP_CCR1_WINDOW_EN_SHIFT               (0U)
#define LPCMP_CCR1_WINDOW_EN_WIDTH               (1U)
#define LPCMP_CCR1_WINDOW_EN(x)                  (((uint32_t)(((uint32_t)(x)) << LPCMP_CCR1_WINDOW_EN_SHIFT)) & LPCMP_CCR1_WINDOW_EN_MASK)

#define LPCMP_CCR1_SAMPLE_EN_MASK                (0x2U)
#define LPCMP_CCR1_SAMPLE_EN_SHIFT               (1U)
#define LPCMP_CCR1_SAMPLE_EN_WIDTH               (1U)
#define LPCMP_CCR1_SAMPLE_EN(x)                  (((uint32_t)(((uint32_t)(x)) << LPCMP_CCR1_SAMPLE_EN_SHIFT)) & LPCMP_CCR1_SAMPLE_EN_MASK)

#define LPCMP_CCR1_DMA_EN_MASK                   (0x4U)
#define LPCMP_CCR1_DMA_EN_SHIFT                  (2U)
#define LPCMP_CCR1_DMA_EN_WIDTH                  (1U)
#define LPCMP_CCR1_DMA_EN(x)                     (((uint32_t)(((uint32_t)(x)) << LPCMP_CCR1_DMA_EN_SHIFT)) & LPCMP_CCR1_DMA_EN_MASK)

#define LPCMP_CCR1_COUT_INV_MASK                 (0x8U)
#define LPCMP_CCR1_COUT_INV_SHIFT                (3U)
#define LPCMP_CCR1_COUT_INV_WIDTH                (1U)
#define LPCMP_CCR1_COUT_INV(x)                   (((uint32_t)(((uint32_t)(x)) << LPCMP_CCR1_COUT_INV_SHIFT)) & LPCMP_CCR1_COUT_INV_MASK)

#define LPCMP_CCR1_COUT_SEL_MASK                 (0x10U)
#define LPCMP_CCR1_COUT_SEL_SHIFT                (4U)
#define LPCMP_CCR1_COUT_SEL_WIDTH                (1U)
#define LPCMP_CCR1_COUT_SEL(x)                   (((uint32_t)(((uint32_t)(x)) << LPCMP_CCR1_COUT_SEL_SHIFT)) & LPCMP_CCR1_COUT_SEL_MASK)

#define LPCMP_CCR1_COUT_PEN_MASK                 (0x20U)
#define LPCMP_CCR1_COUT_PEN_SHIFT                (5U)
#define LPCMP_CCR1_COUT_PEN_WIDTH                (1U)
#define LPCMP_CCR1_COUT_PEN(x)                   (((uint32_t)(((uint32_t)(x)) << LPCMP_CCR1_COUT_PEN_SHIFT)) & LPCMP_CCR1_COUT_PEN_MASK)

#define LPCMP_CCR1_COUTA_OWEN_MASK               (0x40U)
#define LPCMP_CCR1_COUTA_OWEN_SHIFT              (6U)
#define LPCMP_CCR1_COUTA_OWEN_WIDTH              (1U)
#define LPCMP_CCR1_COUTA_OWEN(x)                 (((uint32_t)(((uint32_t)(x)) << LPCMP_CCR1_COUTA_OWEN_SHIFT)) & LPCMP_CCR1_COUTA_OWEN_MASK)

#define LPCMP_CCR1_COUTA_OW_MASK                 (0x80U)
#define LPCMP_CCR1_COUTA_OW_SHIFT                (7U)
#define LPCMP_CCR1_COUTA_OW_WIDTH                (1U)
#define LPCMP_CCR1_COUTA_OW(x)                   (((uint32_t)(((uint32_t)(x)) << LPCMP_CCR1_COUTA_OW_SHIFT)) & LPCMP_CCR1_COUTA_OW_MASK)

#define LPCMP_CCR1_WINDOW_INV_MASK               (0x100U)
#define LPCMP_CCR1_WINDOW_INV_SHIFT              (8U)
#define LPCMP_CCR1_WINDOW_INV_WIDTH              (1U)
#define LPCMP_CCR1_WINDOW_INV(x)                 (((uint32_t)(((uint32_t)(x)) << LPCMP_CCR1_WINDOW_INV_SHIFT)) & LPCMP_CCR1_WINDOW_INV_MASK)

#define LPCMP_CCR1_WINDOW_CLS_MASK               (0x200U)
#define LPCMP_CCR1_WINDOW_CLS_SHIFT              (9U)
#define LPCMP_CCR1_WINDOW_CLS_WIDTH              (1U)
#define LPCMP_CCR1_WINDOW_CLS(x)                 (((uint32_t)(((uint32_t)(x)) << LPCMP_CCR1_WINDOW_CLS_SHIFT)) & LPCMP_CCR1_WINDOW_CLS_MASK)

#define LPCMP_CCR1_EVT_SEL_MASK                  (0xC00U)
#define LPCMP_CCR1_EVT_SEL_SHIFT                 (10U)
#define LPCMP_CCR1_EVT_SEL_WIDTH                 (2U)
#define LPCMP_CCR1_EVT_SEL(x)                    (((uint32_t)(((uint32_t)(x)) << LPCMP_CCR1_EVT_SEL_SHIFT)) & LPCMP_CCR1_EVT_SEL_MASK)

#define LPCMP_CCR1_FILT_CNT_MASK                 (0x70000U)
#define LPCMP_CCR1_FILT_CNT_SHIFT                (16U)
#define LPCMP_CCR1_FILT_CNT_WIDTH                (3U)
#define LPCMP_CCR1_FILT_CNT(x)                   (((uint32_t)(((uint32_t)(x)) << LPCMP_CCR1_FILT_CNT_SHIFT)) & LPCMP_CCR1_FILT_CNT_MASK)

#define LPCMP_CCR1_FILT_PER_MASK                 (0xFF000000U)
#define LPCMP_CCR1_FILT_PER_SHIFT                (24U)
#define LPCMP_CCR1_FILT_PER_WIDTH                (8U)
#define LPCMP_CCR1_FILT_PER(x)                   (((uint32_t)(((uint32_t)(x)) << LPCMP_CCR1_FILT_PER_SHIFT)) & LPCMP_CCR1_FILT_PER_MASK)
/*! @} */

/*! @name CCR2 - Comparator Control Register 2 */
/*! @{ */

#define LPCMP_CCR2_CMP_HPMD_MASK                 (0x1U)
#define LPCMP_CCR2_CMP_HPMD_SHIFT                (0U)
#define LPCMP_CCR2_CMP_HPMD_WIDTH                (1U)
#define LPCMP_CCR2_CMP_HPMD(x)                   (((uint32_t)(((uint32_t)(x)) << LPCMP_CCR2_CMP_HPMD_SHIFT)) & LPCMP_CCR2_CMP_HPMD_MASK)

#define LPCMP_CCR2_OFFSET_MASK                   (0x4U)
#define LPCMP_CCR2_OFFSET_SHIFT                  (2U)
#define LPCMP_CCR2_OFFSET_WIDTH                  (1U)
#define LPCMP_CCR2_OFFSET(x)                     (((uint32_t)(((uint32_t)(x)) << LPCMP_CCR2_OFFSET_SHIFT)) & LPCMP_CCR2_OFFSET_MASK)

#define LPCMP_CCR2_HYSTCTR_MASK                  (0x30U)
#define LPCMP_CCR2_HYSTCTR_SHIFT                 (4U)
#define LPCMP_CCR2_HYSTCTR_WIDTH                 (2U)
#define LPCMP_CCR2_HYSTCTR(x)                    (((uint32_t)(((uint32_t)(x)) << LPCMP_CCR2_HYSTCTR_SHIFT)) & LPCMP_CCR2_HYSTCTR_MASK)

#define LPCMP_CCR2_PSEL_MASK                     (0x70000U)
#define LPCMP_CCR2_PSEL_SHIFT                    (16U)
#define LPCMP_CCR2_PSEL_WIDTH                    (3U)
#define LPCMP_CCR2_PSEL(x)                       (((uint32_t)(((uint32_t)(x)) << LPCMP_CCR2_PSEL_SHIFT)) & LPCMP_CCR2_PSEL_MASK)

#define LPCMP_CCR2_MSEL_MASK                     (0x700000U)
#define LPCMP_CCR2_MSEL_SHIFT                    (20U)
#define LPCMP_CCR2_MSEL_WIDTH                    (3U)
#define LPCMP_CCR2_MSEL(x)                       (((uint32_t)(((uint32_t)(x)) << LPCMP_CCR2_MSEL_SHIFT)) & LPCMP_CCR2_MSEL_MASK)

#define LPCMP_CCR2_INPSEL_MASK                   (0x3000000U)
#define LPCMP_CCR2_INPSEL_SHIFT                  (24U)
#define LPCMP_CCR2_INPSEL_WIDTH                  (2U)
#define LPCMP_CCR2_INPSEL(x)                     (((uint32_t)(((uint32_t)(x)) << LPCMP_CCR2_INPSEL_SHIFT)) & LPCMP_CCR2_INPSEL_MASK)

#define LPCMP_CCR2_INMSEL_MASK                   (0x30000000U)
#define LPCMP_CCR2_INMSEL_SHIFT                  (28U)
#define LPCMP_CCR2_INMSEL_WIDTH                  (2U)
#define LPCMP_CCR2_INMSEL(x)                     (((uint32_t)(((uint32_t)(x)) << LPCMP_CCR2_INMSEL_SHIFT)) & LPCMP_CCR2_INMSEL_MASK)
/*! @} */

/*! @name DCR - DAC Control Register */
/*! @{ */

#define LPCMP_DCR_DAC_EN_MASK                    (0x1U)
#define LPCMP_DCR_DAC_EN_SHIFT                   (0U)
#define LPCMP_DCR_DAC_EN_WIDTH                   (1U)
#define LPCMP_DCR_DAC_EN(x)                      (((uint32_t)(((uint32_t)(x)) << LPCMP_DCR_DAC_EN_SHIFT)) & LPCMP_DCR_DAC_EN_MASK)

#define LPCMP_DCR_VRSEL_MASK                     (0x100U)
#define LPCMP_DCR_VRSEL_SHIFT                    (8U)
#define LPCMP_DCR_VRSEL_WIDTH                    (1U)
#define LPCMP_DCR_VRSEL(x)                       (((uint32_t)(((uint32_t)(x)) << LPCMP_DCR_VRSEL_SHIFT)) & LPCMP_DCR_VRSEL_MASK)

#define LPCMP_DCR_DAC_DATA_MASK                  (0xFF0000U)
#define LPCMP_DCR_DAC_DATA_SHIFT                 (16U)
#define LPCMP_DCR_DAC_DATA_WIDTH                 (8U)
#define LPCMP_DCR_DAC_DATA(x)                    (((uint32_t)(((uint32_t)(x)) << LPCMP_DCR_DAC_DATA_SHIFT)) & LPCMP_DCR_DAC_DATA_MASK)
/*! @} */

/*! @name IER - Interrupt Enable Register */
/*! @{ */

#define LPCMP_IER_CFR_IE_MASK                    (0x1U)
#define LPCMP_IER_CFR_IE_SHIFT                   (0U)
#define LPCMP_IER_CFR_IE_WIDTH                   (1U)
#define LPCMP_IER_CFR_IE(x)                      (((uint32_t)(((uint32_t)(x)) << LPCMP_IER_CFR_IE_SHIFT)) & LPCMP_IER_CFR_IE_MASK)

#define LPCMP_IER_CFF_IE_MASK                    (0x2U)
#define LPCMP_IER_CFF_IE_SHIFT                   (1U)
#define LPCMP_IER_CFF_IE_WIDTH                   (1U)
#define LPCMP_IER_CFF_IE(x)                      (((uint32_t)(((uint32_t)(x)) << LPCMP_IER_CFF_IE_SHIFT)) & LPCMP_IER_CFF_IE_MASK)

#define LPCMP_IER_RRF_IE_MASK                    (0x4U)
#define LPCMP_IER_RRF_IE_SHIFT                   (2U)
#define LPCMP_IER_RRF_IE_WIDTH                   (1U)
#define LPCMP_IER_RRF_IE(x)                      (((uint32_t)(((uint32_t)(x)) << LPCMP_IER_RRF_IE_SHIFT)) & LPCMP_IER_RRF_IE_MASK)
/*! @} */

/*! @name CSR - Comparator Status Register */
/*! @{ */

#define LPCMP_CSR_CFR_MASK                       (0x1U)
#define LPCMP_CSR_CFR_SHIFT                      (0U)
#define LPCMP_CSR_CFR_WIDTH                      (1U)
#define LPCMP_CSR_CFR(x)                         (((uint32_t)(((uint32_t)(x)) << LPCMP_CSR_CFR_SHIFT)) & LPCMP_CSR_CFR_MASK)

#define LPCMP_CSR_CFF_MASK                       (0x2U)
#define LPCMP_CSR_CFF_SHIFT                      (1U)
#define LPCMP_CSR_CFF_WIDTH                      (1U)
#define LPCMP_CSR_CFF(x)                         (((uint32_t)(((uint32_t)(x)) << LPCMP_CSR_CFF_SHIFT)) & LPCMP_CSR_CFF_MASK)

#define LPCMP_CSR_RRF_MASK                       (0x4U)
#define LPCMP_CSR_RRF_SHIFT                      (2U)
#define LPCMP_CSR_RRF_WIDTH                      (1U)
#define LPCMP_CSR_RRF(x)                         (((uint32_t)(((uint32_t)(x)) << LPCMP_CSR_RRF_SHIFT)) & LPCMP_CSR_RRF_MASK)

#define LPCMP_CSR_COUT_MASK                      (0x100U)
#define LPCMP_CSR_COUT_SHIFT                     (8U)
#define LPCMP_CSR_COUT_WIDTH                     (1U)
#define LPCMP_CSR_COUT(x)                        (((uint32_t)(((uint32_t)(x)) << LPCMP_CSR_COUT_SHIFT)) & LPCMP_CSR_COUT_MASK)
/*! @} */

/*! @name RRCR0 - Round Robin Control Register 0 */
/*! @{ */

#define LPCMP_RRCR0_RR_EN_MASK                   (0x1U)
#define LPCMP_RRCR0_RR_EN_SHIFT                  (0U)
#define LPCMP_RRCR0_RR_EN_WIDTH                  (1U)
#define LPCMP_RRCR0_RR_EN(x)                     (((uint32_t)(((uint32_t)(x)) << LPCMP_RRCR0_RR_EN_SHIFT)) & LPCMP_RRCR0_RR_EN_MASK)

#define LPCMP_RRCR0_RR_NSAM_MASK                 (0x300U)
#define LPCMP_RRCR0_RR_NSAM_SHIFT                (8U)
#define LPCMP_RRCR0_RR_NSAM_WIDTH                (2U)
#define LPCMP_RRCR0_RR_NSAM(x)                   (((uint32_t)(((uint32_t)(x)) << LPCMP_RRCR0_RR_NSAM_SHIFT)) & LPCMP_RRCR0_RR_NSAM_MASK)

#define LPCMP_RRCR0_RR_INITMOD_MASK              (0x3F0000U)
#define LPCMP_RRCR0_RR_INITMOD_SHIFT             (16U)
#define LPCMP_RRCR0_RR_INITMOD_WIDTH             (6U)
#define LPCMP_RRCR0_RR_INITMOD(x)                (((uint32_t)(((uint32_t)(x)) << LPCMP_RRCR0_RR_INITMOD_SHIFT)) & LPCMP_RRCR0_RR_INITMOD_MASK)
/*! @} */

/*! @name RRCR1 - Round Robin Control Register 1 */
/*! @{ */

#define LPCMP_RRCR1_RR_CH0EN_MASK                (0x1U)
#define LPCMP_RRCR1_RR_CH0EN_SHIFT               (0U)
#define LPCMP_RRCR1_RR_CH0EN_WIDTH               (1U)
#define LPCMP_RRCR1_RR_CH0EN(x)                  (((uint32_t)(((uint32_t)(x)) << LPCMP_RRCR1_RR_CH0EN_SHIFT)) & LPCMP_RRCR1_RR_CH0EN_MASK)

#define LPCMP_RRCR1_RR_CH1EN_MASK                (0x2U)
#define LPCMP_RRCR1_RR_CH1EN_SHIFT               (1U)
#define LPCMP_RRCR1_RR_CH1EN_WIDTH               (1U)
#define LPCMP_RRCR1_RR_CH1EN(x)                  (((uint32_t)(((uint32_t)(x)) << LPCMP_RRCR1_RR_CH1EN_SHIFT)) & LPCMP_RRCR1_RR_CH1EN_MASK)

#define LPCMP_RRCR1_RR_CH2EN_MASK                (0x4U)
#define LPCMP_RRCR1_RR_CH2EN_SHIFT               (2U)
#define LPCMP_RRCR1_RR_CH2EN_WIDTH               (1U)
#define LPCMP_RRCR1_RR_CH2EN(x)                  (((uint32_t)(((uint32_t)(x)) << LPCMP_RRCR1_RR_CH2EN_SHIFT)) & LPCMP_RRCR1_RR_CH2EN_MASK)

#define LPCMP_RRCR1_RR_CH3EN_MASK                (0x8U)
#define LPCMP_RRCR1_RR_CH3EN_SHIFT               (3U)
#define LPCMP_RRCR1_RR_CH3EN_WIDTH               (1U)
#define LPCMP_RRCR1_RR_CH3EN(x)                  (((uint32_t)(((uint32_t)(x)) << LPCMP_RRCR1_RR_CH3EN_SHIFT)) & LPCMP_RRCR1_RR_CH3EN_MASK)

#define LPCMP_RRCR1_RR_CH4EN_MASK                (0x10U)
#define LPCMP_RRCR1_RR_CH4EN_SHIFT               (4U)
#define LPCMP_RRCR1_RR_CH4EN_WIDTH               (1U)
#define LPCMP_RRCR1_RR_CH4EN(x)                  (((uint32_t)(((uint32_t)(x)) << LPCMP_RRCR1_RR_CH4EN_SHIFT)) & LPCMP_RRCR1_RR_CH4EN_MASK)

#define LPCMP_RRCR1_RR_CH5EN_MASK                (0x20U)
#define LPCMP_RRCR1_RR_CH5EN_SHIFT               (5U)
#define LPCMP_RRCR1_RR_CH5EN_WIDTH               (1U)
#define LPCMP_RRCR1_RR_CH5EN(x)                  (((uint32_t)(((uint32_t)(x)) << LPCMP_RRCR1_RR_CH5EN_SHIFT)) & LPCMP_RRCR1_RR_CH5EN_MASK)

#define LPCMP_RRCR1_RR_CH6EN_MASK                (0x40U)
#define LPCMP_RRCR1_RR_CH6EN_SHIFT               (6U)
#define LPCMP_RRCR1_RR_CH6EN_WIDTH               (1U)
#define LPCMP_RRCR1_RR_CH6EN(x)                  (((uint32_t)(((uint32_t)(x)) << LPCMP_RRCR1_RR_CH6EN_SHIFT)) & LPCMP_RRCR1_RR_CH6EN_MASK)

#define LPCMP_RRCR1_RR_CH7EN_MASK                (0x80U)
#define LPCMP_RRCR1_RR_CH7EN_SHIFT               (7U)
#define LPCMP_RRCR1_RR_CH7EN_WIDTH               (1U)
#define LPCMP_RRCR1_RR_CH7EN(x)                  (((uint32_t)(((uint32_t)(x)) << LPCMP_RRCR1_RR_CH7EN_SHIFT)) & LPCMP_RRCR1_RR_CH7EN_MASK)

#define LPCMP_RRCR1_FIXP_MASK                    (0x10000U)
#define LPCMP_RRCR1_FIXP_SHIFT                   (16U)
#define LPCMP_RRCR1_FIXP_WIDTH                   (1U)
#define LPCMP_RRCR1_FIXP(x)                      (((uint32_t)(((uint32_t)(x)) << LPCMP_RRCR1_FIXP_SHIFT)) & LPCMP_RRCR1_FIXP_MASK)

#define LPCMP_RRCR1_FIXCH_MASK                   (0x700000U)
#define LPCMP_RRCR1_FIXCH_SHIFT                  (20U)
#define LPCMP_RRCR1_FIXCH_WIDTH                  (3U)
#define LPCMP_RRCR1_FIXCH(x)                     (((uint32_t)(((uint32_t)(x)) << LPCMP_RRCR1_FIXCH_SHIFT)) & LPCMP_RRCR1_FIXCH_MASK)
/*! @} */

/*! @name RRCSR - Round Robin Control and Status Register */
/*! @{ */

#define LPCMP_RRCSR_RR_CH0OUT_MASK               (0x1U)
#define LPCMP_RRCSR_RR_CH0OUT_SHIFT              (0U)
#define LPCMP_RRCSR_RR_CH0OUT_WIDTH              (1U)
#define LPCMP_RRCSR_RR_CH0OUT(x)                 (((uint32_t)(((uint32_t)(x)) << LPCMP_RRCSR_RR_CH0OUT_SHIFT)) & LPCMP_RRCSR_RR_CH0OUT_MASK)

#define LPCMP_RRCSR_RR_CH1OUT_MASK               (0x2U)
#define LPCMP_RRCSR_RR_CH1OUT_SHIFT              (1U)
#define LPCMP_RRCSR_RR_CH1OUT_WIDTH              (1U)
#define LPCMP_RRCSR_RR_CH1OUT(x)                 (((uint32_t)(((uint32_t)(x)) << LPCMP_RRCSR_RR_CH1OUT_SHIFT)) & LPCMP_RRCSR_RR_CH1OUT_MASK)

#define LPCMP_RRCSR_RR_CH2OUT_MASK               (0x4U)
#define LPCMP_RRCSR_RR_CH2OUT_SHIFT              (2U)
#define LPCMP_RRCSR_RR_CH2OUT_WIDTH              (1U)
#define LPCMP_RRCSR_RR_CH2OUT(x)                 (((uint32_t)(((uint32_t)(x)) << LPCMP_RRCSR_RR_CH2OUT_SHIFT)) & LPCMP_RRCSR_RR_CH2OUT_MASK)

#define LPCMP_RRCSR_RR_CH3OUT_MASK               (0x8U)
#define LPCMP_RRCSR_RR_CH3OUT_SHIFT              (3U)
#define LPCMP_RRCSR_RR_CH3OUT_WIDTH              (1U)
#define LPCMP_RRCSR_RR_CH3OUT(x)                 (((uint32_t)(((uint32_t)(x)) << LPCMP_RRCSR_RR_CH3OUT_SHIFT)) & LPCMP_RRCSR_RR_CH3OUT_MASK)

#define LPCMP_RRCSR_RR_CH4OUT_MASK               (0x10U)
#define LPCMP_RRCSR_RR_CH4OUT_SHIFT              (4U)
#define LPCMP_RRCSR_RR_CH4OUT_WIDTH              (1U)
#define LPCMP_RRCSR_RR_CH4OUT(x)                 (((uint32_t)(((uint32_t)(x)) << LPCMP_RRCSR_RR_CH4OUT_SHIFT)) & LPCMP_RRCSR_RR_CH4OUT_MASK)

#define LPCMP_RRCSR_RR_CH5OUT_MASK               (0x20U)
#define LPCMP_RRCSR_RR_CH5OUT_SHIFT              (5U)
#define LPCMP_RRCSR_RR_CH5OUT_WIDTH              (1U)
#define LPCMP_RRCSR_RR_CH5OUT(x)                 (((uint32_t)(((uint32_t)(x)) << LPCMP_RRCSR_RR_CH5OUT_SHIFT)) & LPCMP_RRCSR_RR_CH5OUT_MASK)

#define LPCMP_RRCSR_RR_CH6OUT_MASK               (0x40U)
#define LPCMP_RRCSR_RR_CH6OUT_SHIFT              (6U)
#define LPCMP_RRCSR_RR_CH6OUT_WIDTH              (1U)
#define LPCMP_RRCSR_RR_CH6OUT(x)                 (((uint32_t)(((uint32_t)(x)) << LPCMP_RRCSR_RR_CH6OUT_SHIFT)) & LPCMP_RRCSR_RR_CH6OUT_MASK)

#define LPCMP_RRCSR_RR_CH7OUT_MASK               (0x80U)
#define LPCMP_RRCSR_RR_CH7OUT_SHIFT              (7U)
#define LPCMP_RRCSR_RR_CH7OUT_WIDTH              (1U)
#define LPCMP_RRCSR_RR_CH7OUT(x)                 (((uint32_t)(((uint32_t)(x)) << LPCMP_RRCSR_RR_CH7OUT_SHIFT)) & LPCMP_RRCSR_RR_CH7OUT_MASK)
/*! @} */

/*! @name RRSR - Round Robin Status Register */
/*! @{ */

#define LPCMP_RRSR_RR_CH0F_MASK                  (0x1U)
#define LPCMP_RRSR_RR_CH0F_SHIFT                 (0U)
#define LPCMP_RRSR_RR_CH0F_WIDTH                 (1U)
#define LPCMP_RRSR_RR_CH0F(x)                    (((uint32_t)(((uint32_t)(x)) << LPCMP_RRSR_RR_CH0F_SHIFT)) & LPCMP_RRSR_RR_CH0F_MASK)

#define LPCMP_RRSR_RR_CH1F_MASK                  (0x2U)
#define LPCMP_RRSR_RR_CH1F_SHIFT                 (1U)
#define LPCMP_RRSR_RR_CH1F_WIDTH                 (1U)
#define LPCMP_RRSR_RR_CH1F(x)                    (((uint32_t)(((uint32_t)(x)) << LPCMP_RRSR_RR_CH1F_SHIFT)) & LPCMP_RRSR_RR_CH1F_MASK)

#define LPCMP_RRSR_RR_CH2F_MASK                  (0x4U)
#define LPCMP_RRSR_RR_CH2F_SHIFT                 (2U)
#define LPCMP_RRSR_RR_CH2F_WIDTH                 (1U)
#define LPCMP_RRSR_RR_CH2F(x)                    (((uint32_t)(((uint32_t)(x)) << LPCMP_RRSR_RR_CH2F_SHIFT)) & LPCMP_RRSR_RR_CH2F_MASK)

#define LPCMP_RRSR_RR_CH3F_MASK                  (0x8U)
#define LPCMP_RRSR_RR_CH3F_SHIFT                 (3U)
#define LPCMP_RRSR_RR_CH3F_WIDTH                 (1U)
#define LPCMP_RRSR_RR_CH3F(x)                    (((uint32_t)(((uint32_t)(x)) << LPCMP_RRSR_RR_CH3F_SHIFT)) & LPCMP_RRSR_RR_CH3F_MASK)

#define LPCMP_RRSR_RR_CH4F_MASK                  (0x10U)
#define LPCMP_RRSR_RR_CH4F_SHIFT                 (4U)
#define LPCMP_RRSR_RR_CH4F_WIDTH                 (1U)
#define LPCMP_RRSR_RR_CH4F(x)                    (((uint32_t)(((uint32_t)(x)) << LPCMP_RRSR_RR_CH4F_SHIFT)) & LPCMP_RRSR_RR_CH4F_MASK)

#define LPCMP_RRSR_RR_CH5F_MASK                  (0x20U)
#define LPCMP_RRSR_RR_CH5F_SHIFT                 (5U)
#define LPCMP_RRSR_RR_CH5F_WIDTH                 (1U)
#define LPCMP_RRSR_RR_CH5F(x)                    (((uint32_t)(((uint32_t)(x)) << LPCMP_RRSR_RR_CH5F_SHIFT)) & LPCMP_RRSR_RR_CH5F_MASK)

#define LPCMP_RRSR_RR_CH6F_MASK                  (0x40U)
#define LPCMP_RRSR_RR_CH6F_SHIFT                 (6U)
#define LPCMP_RRSR_RR_CH6F_WIDTH                 (1U)
#define LPCMP_RRSR_RR_CH6F(x)                    (((uint32_t)(((uint32_t)(x)) << LPCMP_RRSR_RR_CH6F_SHIFT)) & LPCMP_RRSR_RR_CH6F_MASK)

#define LPCMP_RRSR_RR_CH7F_MASK                  (0x80U)
#define LPCMP_RRSR_RR_CH7F_SHIFT                 (7U)
#define LPCMP_RRSR_RR_CH7F_WIDTH                 (1U)
#define LPCMP_RRSR_RR_CH7F(x)                    (((uint32_t)(((uint32_t)(x)) << LPCMP_RRSR_RR_CH7F_SHIFT)) & LPCMP_RRSR_RR_CH7F_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group LPCMP_Register_Masks */

/*!
 * @}
 */ /* end of group LPCMP_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_LPCMP_H_) */
