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
 * @file S32K344_SAI.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_SAI
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
#if !defined(S32K344_SAI_H_)  /* Check if memory map has not been already included */
#define S32K344_SAI_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- SAI Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SAI_Peripheral_Access_Layer SAI Peripheral Access Layer
 * @{
 */

/** SAI - Size of Registers Arrays */
#define SAI_TDR_COUNT                             4u
#define SAI_TFR_COUNT                             4u
#define SAI_RDR_COUNT                             4u
#define SAI_RFR_COUNT                             4u

/** SAI - Register Layout Typedef */
typedef struct {
  __I  uint32_t VERID;                             /**< Version ID, offset: 0x0 */
  __I  uint32_t PARAM;                             /**< Parameter, offset: 0x4 */
  __IO uint32_t TCSR;                              /**< Transmit Control, offset: 0x8 */
  __IO uint32_t TCR1;                              /**< Transmit Configuration 1, offset: 0xC */
  __IO uint32_t TCR2;                              /**< Transmit Configuration 2, offset: 0x10 */
  __IO uint32_t TCR3;                              /**< Transmit Configuration 3, offset: 0x14 */
  __IO uint32_t TCR4;                              /**< Transmit Configuration 4, offset: 0x18 */
  __IO uint32_t TCR5;                              /**< Transmit Configuration 5, offset: 0x1C */
  __O  uint32_t TDR[SAI_TDR_COUNT];                /**< Transmit Data, array offset: 0x20, array step: 0x4 */
  uint8_t RESERVED_0[16];
  __I  uint32_t TFR[SAI_TFR_COUNT];                /**< Transmit FIFO, array offset: 0x40, array step: 0x4 */
  uint8_t RESERVED_1[16];
  __IO uint32_t TMR;                               /**< Transmit Mask, offset: 0x60 */
  uint8_t RESERVED_2[36];
  __IO uint32_t RCSR;                              /**< Receive Control, offset: 0x88 */
  __IO uint32_t RCR1;                              /**< Receive Configuration 1, offset: 0x8C */
  __IO uint32_t RCR2;                              /**< Receive Configuration 2, offset: 0x90 */
  __IO uint32_t RCR3;                              /**< Receive Configuration 3, offset: 0x94 */
  __IO uint32_t RCR4;                              /**< Receive Configuration 4, offset: 0x98 */
  __IO uint32_t RCR5;                              /**< Receive Configuration 5, offset: 0x9C */
  __I  uint32_t RDR[SAI_RDR_COUNT];                /**< Receive Data, array offset: 0xA0, array step: 0x4 */
  uint8_t RESERVED_3[16];
  __I  uint32_t RFR[SAI_RFR_COUNT];                /**< Receive FIFO, array offset: 0xC0, array step: 0x4 */
  uint8_t RESERVED_4[16];
  __IO uint32_t RMR;                               /**< Receive Mask, offset: 0xE0 */
} SAI_Type, *SAI_MemMapPtr;

/** Number of instances of the SAI module. */
#define SAI_INSTANCE_COUNT                       (2u)

/* SAI - Peripheral instance base addresses */
/** Peripheral SAI_0 base address */
#define IP_SAI_0_BASE                            (0x4036C000u)
/** Peripheral SAI_0 base pointer */
#define IP_SAI_0                                 ((SAI_Type *)IP_SAI_0_BASE)
/** Peripheral SAI_1 base address */
#define IP_SAI_1_BASE                            (0x404DC000u)
/** Peripheral SAI_1 base pointer */
#define IP_SAI_1                                 ((SAI_Type *)IP_SAI_1_BASE)
/** Array initializer of SAI peripheral base addresses */
#define IP_SAI_BASE_ADDRS                        { IP_SAI_0_BASE, IP_SAI_1_BASE }
/** Array initializer of SAI peripheral base pointers */
#define IP_SAI_BASE_PTRS                         { IP_SAI_0, IP_SAI_1 }

/* ----------------------------------------------------------------------------
   -- SAI Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SAI_Register_Masks SAI Register Masks
 * @{
 */

/*! @name VERID - Version ID */
/*! @{ */

#define SAI_VERID_FEATURE_MASK                   (0xFFFFU)
#define SAI_VERID_FEATURE_SHIFT                  (0U)
#define SAI_VERID_FEATURE_WIDTH                  (16U)
#define SAI_VERID_FEATURE(x)                     (((uint32_t)(((uint32_t)(x)) << SAI_VERID_FEATURE_SHIFT)) & SAI_VERID_FEATURE_MASK)

#define SAI_VERID_MINOR_MASK                     (0xFF0000U)
#define SAI_VERID_MINOR_SHIFT                    (16U)
#define SAI_VERID_MINOR_WIDTH                    (8U)
#define SAI_VERID_MINOR(x)                       (((uint32_t)(((uint32_t)(x)) << SAI_VERID_MINOR_SHIFT)) & SAI_VERID_MINOR_MASK)

#define SAI_VERID_MAJOR_MASK                     (0xFF000000U)
#define SAI_VERID_MAJOR_SHIFT                    (24U)
#define SAI_VERID_MAJOR_WIDTH                    (8U)
#define SAI_VERID_MAJOR(x)                       (((uint32_t)(((uint32_t)(x)) << SAI_VERID_MAJOR_SHIFT)) & SAI_VERID_MAJOR_MASK)
/*! @} */

/*! @name PARAM - Parameter */
/*! @{ */

#define SAI_PARAM_DATALINE_MASK                  (0xFU)
#define SAI_PARAM_DATALINE_SHIFT                 (0U)
#define SAI_PARAM_DATALINE_WIDTH                 (4U)
#define SAI_PARAM_DATALINE(x)                    (((uint32_t)(((uint32_t)(x)) << SAI_PARAM_DATALINE_SHIFT)) & SAI_PARAM_DATALINE_MASK)

#define SAI_PARAM_FIFO_MASK                      (0xF00U)
#define SAI_PARAM_FIFO_SHIFT                     (8U)
#define SAI_PARAM_FIFO_WIDTH                     (4U)
#define SAI_PARAM_FIFO(x)                        (((uint32_t)(((uint32_t)(x)) << SAI_PARAM_FIFO_SHIFT)) & SAI_PARAM_FIFO_MASK)

#define SAI_PARAM_FRAME_MASK                     (0xF0000U)
#define SAI_PARAM_FRAME_SHIFT                    (16U)
#define SAI_PARAM_FRAME_WIDTH                    (4U)
#define SAI_PARAM_FRAME(x)                       (((uint32_t)(((uint32_t)(x)) << SAI_PARAM_FRAME_SHIFT)) & SAI_PARAM_FRAME_MASK)
/*! @} */

/*! @name TCSR - Transmit Control */
/*! @{ */

#define SAI_TCSR_FRDE_MASK                       (0x1U)
#define SAI_TCSR_FRDE_SHIFT                      (0U)
#define SAI_TCSR_FRDE_WIDTH                      (1U)
#define SAI_TCSR_FRDE(x)                         (((uint32_t)(((uint32_t)(x)) << SAI_TCSR_FRDE_SHIFT)) & SAI_TCSR_FRDE_MASK)

#define SAI_TCSR_FWDE_MASK                       (0x2U)
#define SAI_TCSR_FWDE_SHIFT                      (1U)
#define SAI_TCSR_FWDE_WIDTH                      (1U)
#define SAI_TCSR_FWDE(x)                         (((uint32_t)(((uint32_t)(x)) << SAI_TCSR_FWDE_SHIFT)) & SAI_TCSR_FWDE_MASK)

#define SAI_TCSR_FRIE_MASK                       (0x100U)
#define SAI_TCSR_FRIE_SHIFT                      (8U)
#define SAI_TCSR_FRIE_WIDTH                      (1U)
#define SAI_TCSR_FRIE(x)                         (((uint32_t)(((uint32_t)(x)) << SAI_TCSR_FRIE_SHIFT)) & SAI_TCSR_FRIE_MASK)

#define SAI_TCSR_FWIE_MASK                       (0x200U)
#define SAI_TCSR_FWIE_SHIFT                      (9U)
#define SAI_TCSR_FWIE_WIDTH                      (1U)
#define SAI_TCSR_FWIE(x)                         (((uint32_t)(((uint32_t)(x)) << SAI_TCSR_FWIE_SHIFT)) & SAI_TCSR_FWIE_MASK)

#define SAI_TCSR_FEIE_MASK                       (0x400U)
#define SAI_TCSR_FEIE_SHIFT                      (10U)
#define SAI_TCSR_FEIE_WIDTH                      (1U)
#define SAI_TCSR_FEIE(x)                         (((uint32_t)(((uint32_t)(x)) << SAI_TCSR_FEIE_SHIFT)) & SAI_TCSR_FEIE_MASK)

#define SAI_TCSR_SEIE_MASK                       (0x800U)
#define SAI_TCSR_SEIE_SHIFT                      (11U)
#define SAI_TCSR_SEIE_WIDTH                      (1U)
#define SAI_TCSR_SEIE(x)                         (((uint32_t)(((uint32_t)(x)) << SAI_TCSR_SEIE_SHIFT)) & SAI_TCSR_SEIE_MASK)

#define SAI_TCSR_WSIE_MASK                       (0x1000U)
#define SAI_TCSR_WSIE_SHIFT                      (12U)
#define SAI_TCSR_WSIE_WIDTH                      (1U)
#define SAI_TCSR_WSIE(x)                         (((uint32_t)(((uint32_t)(x)) << SAI_TCSR_WSIE_SHIFT)) & SAI_TCSR_WSIE_MASK)

#define SAI_TCSR_FRF_MASK                        (0x10000U)
#define SAI_TCSR_FRF_SHIFT                       (16U)
#define SAI_TCSR_FRF_WIDTH                       (1U)
#define SAI_TCSR_FRF(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_TCSR_FRF_SHIFT)) & SAI_TCSR_FRF_MASK)

#define SAI_TCSR_FWF_MASK                        (0x20000U)
#define SAI_TCSR_FWF_SHIFT                       (17U)
#define SAI_TCSR_FWF_WIDTH                       (1U)
#define SAI_TCSR_FWF(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_TCSR_FWF_SHIFT)) & SAI_TCSR_FWF_MASK)

#define SAI_TCSR_FEF_MASK                        (0x40000U)
#define SAI_TCSR_FEF_SHIFT                       (18U)
#define SAI_TCSR_FEF_WIDTH                       (1U)
#define SAI_TCSR_FEF(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_TCSR_FEF_SHIFT)) & SAI_TCSR_FEF_MASK)

#define SAI_TCSR_SEF_MASK                        (0x80000U)
#define SAI_TCSR_SEF_SHIFT                       (19U)
#define SAI_TCSR_SEF_WIDTH                       (1U)
#define SAI_TCSR_SEF(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_TCSR_SEF_SHIFT)) & SAI_TCSR_SEF_MASK)

#define SAI_TCSR_WSF_MASK                        (0x100000U)
#define SAI_TCSR_WSF_SHIFT                       (20U)
#define SAI_TCSR_WSF_WIDTH                       (1U)
#define SAI_TCSR_WSF(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_TCSR_WSF_SHIFT)) & SAI_TCSR_WSF_MASK)

#define SAI_TCSR_SR_MASK                         (0x1000000U)
#define SAI_TCSR_SR_SHIFT                        (24U)
#define SAI_TCSR_SR_WIDTH                        (1U)
#define SAI_TCSR_SR(x)                           (((uint32_t)(((uint32_t)(x)) << SAI_TCSR_SR_SHIFT)) & SAI_TCSR_SR_MASK)

#define SAI_TCSR_FR_MASK                         (0x2000000U)
#define SAI_TCSR_FR_SHIFT                        (25U)
#define SAI_TCSR_FR_WIDTH                        (1U)
#define SAI_TCSR_FR(x)                           (((uint32_t)(((uint32_t)(x)) << SAI_TCSR_FR_SHIFT)) & SAI_TCSR_FR_MASK)

#define SAI_TCSR_BCE_MASK                        (0x10000000U)
#define SAI_TCSR_BCE_SHIFT                       (28U)
#define SAI_TCSR_BCE_WIDTH                       (1U)
#define SAI_TCSR_BCE(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_TCSR_BCE_SHIFT)) & SAI_TCSR_BCE_MASK)

#define SAI_TCSR_DBGE_MASK                       (0x20000000U)
#define SAI_TCSR_DBGE_SHIFT                      (29U)
#define SAI_TCSR_DBGE_WIDTH                      (1U)
#define SAI_TCSR_DBGE(x)                         (((uint32_t)(((uint32_t)(x)) << SAI_TCSR_DBGE_SHIFT)) & SAI_TCSR_DBGE_MASK)

#define SAI_TCSR_TE_MASK                         (0x80000000U)
#define SAI_TCSR_TE_SHIFT                        (31U)
#define SAI_TCSR_TE_WIDTH                        (1U)
#define SAI_TCSR_TE(x)                           (((uint32_t)(((uint32_t)(x)) << SAI_TCSR_TE_SHIFT)) & SAI_TCSR_TE_MASK)
/*! @} */

/*! @name TCR1 - Transmit Configuration 1 */
/*! @{ */

#define SAI_TCR1_TFW_MASK                        (0x7U)
#define SAI_TCR1_TFW_SHIFT                       (0U)
#define SAI_TCR1_TFW_WIDTH                       (3U)
#define SAI_TCR1_TFW(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_TCR1_TFW_SHIFT)) & SAI_TCR1_TFW_MASK)
/*! @} */

/*! @name TCR2 - Transmit Configuration 2 */
/*! @{ */

#define SAI_TCR2_DIV_MASK                        (0xFFU)
#define SAI_TCR2_DIV_SHIFT                       (0U)
#define SAI_TCR2_DIV_WIDTH                       (8U)
#define SAI_TCR2_DIV(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_TCR2_DIV_SHIFT)) & SAI_TCR2_DIV_MASK)

#define SAI_TCR2_BYP_MASK                        (0x800000U)
#define SAI_TCR2_BYP_SHIFT                       (23U)
#define SAI_TCR2_BYP_WIDTH                       (1U)
#define SAI_TCR2_BYP(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_TCR2_BYP_SHIFT)) & SAI_TCR2_BYP_MASK)

#define SAI_TCR2_BCD_MASK                        (0x1000000U)
#define SAI_TCR2_BCD_SHIFT                       (24U)
#define SAI_TCR2_BCD_WIDTH                       (1U)
#define SAI_TCR2_BCD(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_TCR2_BCD_SHIFT)) & SAI_TCR2_BCD_MASK)

#define SAI_TCR2_BCP_MASK                        (0x2000000U)
#define SAI_TCR2_BCP_SHIFT                       (25U)
#define SAI_TCR2_BCP_WIDTH                       (1U)
#define SAI_TCR2_BCP(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_TCR2_BCP_SHIFT)) & SAI_TCR2_BCP_MASK)

#define SAI_TCR2_MSEL_MASK                       (0xC000000U)
#define SAI_TCR2_MSEL_SHIFT                      (26U)
#define SAI_TCR2_MSEL_WIDTH                      (2U)
#define SAI_TCR2_MSEL(x)                         (((uint32_t)(((uint32_t)(x)) << SAI_TCR2_MSEL_SHIFT)) & SAI_TCR2_MSEL_MASK)

#define SAI_TCR2_BCI_MASK                        (0x10000000U)
#define SAI_TCR2_BCI_SHIFT                       (28U)
#define SAI_TCR2_BCI_WIDTH                       (1U)
#define SAI_TCR2_BCI(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_TCR2_BCI_SHIFT)) & SAI_TCR2_BCI_MASK)

#define SAI_TCR2_SYNC_MASK                       (0x40000000U)
#define SAI_TCR2_SYNC_SHIFT                      (30U)
#define SAI_TCR2_SYNC_WIDTH                      (1U)
#define SAI_TCR2_SYNC(x)                         (((uint32_t)(((uint32_t)(x)) << SAI_TCR2_SYNC_SHIFT)) & SAI_TCR2_SYNC_MASK)
/*! @} */

/*! @name TCR3 - Transmit Configuration 3 */
/*! @{ */

#define SAI_TCR3_WDFL_MASK                       (0xFU)
#define SAI_TCR3_WDFL_SHIFT                      (0U)
#define SAI_TCR3_WDFL_WIDTH                      (4U)
#define SAI_TCR3_WDFL(x)                         (((uint32_t)(((uint32_t)(x)) << SAI_TCR3_WDFL_SHIFT)) & SAI_TCR3_WDFL_MASK)

#define SAI_TCR3_TCE_MASK                        (0xF0000U)  /* Merged from fields with different position or width, of widths (1, 4), largest definition used */
#define SAI_TCR3_TCE_SHIFT                       (16U)
#define SAI_TCR3_TCE_WIDTH                       (4U)
#define SAI_TCR3_TCE(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_TCR3_TCE_SHIFT)) & SAI_TCR3_TCE_MASK)  /* Merged from fields with different position or width, of widths (1, 4), largest definition used */

#define SAI_TCR3_CFR_MASK                        (0xF000000U)
#define SAI_TCR3_CFR_SHIFT                       (24U)
#define SAI_TCR3_CFR_WIDTH                       (4U)
#define SAI_TCR3_CFR(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_TCR3_CFR_SHIFT)) & SAI_TCR3_CFR_MASK)
/*! @} */

/*! @name TCR4 - Transmit Configuration 4 */
/*! @{ */

#define SAI_TCR4_FSD_MASK                        (0x1U)
#define SAI_TCR4_FSD_SHIFT                       (0U)
#define SAI_TCR4_FSD_WIDTH                       (1U)
#define SAI_TCR4_FSD(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_TCR4_FSD_SHIFT)) & SAI_TCR4_FSD_MASK)

#define SAI_TCR4_FSP_MASK                        (0x2U)
#define SAI_TCR4_FSP_SHIFT                       (1U)
#define SAI_TCR4_FSP_WIDTH                       (1U)
#define SAI_TCR4_FSP(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_TCR4_FSP_SHIFT)) & SAI_TCR4_FSP_MASK)

#define SAI_TCR4_ONDEM_MASK                      (0x4U)
#define SAI_TCR4_ONDEM_SHIFT                     (2U)
#define SAI_TCR4_ONDEM_WIDTH                     (1U)
#define SAI_TCR4_ONDEM(x)                        (((uint32_t)(((uint32_t)(x)) << SAI_TCR4_ONDEM_SHIFT)) & SAI_TCR4_ONDEM_MASK)

#define SAI_TCR4_FSE_MASK                        (0x8U)
#define SAI_TCR4_FSE_SHIFT                       (3U)
#define SAI_TCR4_FSE_WIDTH                       (1U)
#define SAI_TCR4_FSE(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_TCR4_FSE_SHIFT)) & SAI_TCR4_FSE_MASK)

#define SAI_TCR4_MF_MASK                         (0x10U)
#define SAI_TCR4_MF_SHIFT                        (4U)
#define SAI_TCR4_MF_WIDTH                        (1U)
#define SAI_TCR4_MF(x)                           (((uint32_t)(((uint32_t)(x)) << SAI_TCR4_MF_SHIFT)) & SAI_TCR4_MF_MASK)

#define SAI_TCR4_CHMOD_MASK                      (0x20U)
#define SAI_TCR4_CHMOD_SHIFT                     (5U)
#define SAI_TCR4_CHMOD_WIDTH                     (1U)
#define SAI_TCR4_CHMOD(x)                        (((uint32_t)(((uint32_t)(x)) << SAI_TCR4_CHMOD_SHIFT)) & SAI_TCR4_CHMOD_MASK)

#define SAI_TCR4_SYWD_MASK                       (0x1F00U)
#define SAI_TCR4_SYWD_SHIFT                      (8U)
#define SAI_TCR4_SYWD_WIDTH                      (5U)
#define SAI_TCR4_SYWD(x)                         (((uint32_t)(((uint32_t)(x)) << SAI_TCR4_SYWD_SHIFT)) & SAI_TCR4_SYWD_MASK)

#define SAI_TCR4_FRSZ_MASK                       (0xF0000U)
#define SAI_TCR4_FRSZ_SHIFT                      (16U)
#define SAI_TCR4_FRSZ_WIDTH                      (4U)
#define SAI_TCR4_FRSZ(x)                         (((uint32_t)(((uint32_t)(x)) << SAI_TCR4_FRSZ_SHIFT)) & SAI_TCR4_FRSZ_MASK)

#define SAI_TCR4_FPACK_MASK                      (0x3000000U)
#define SAI_TCR4_FPACK_SHIFT                     (24U)
#define SAI_TCR4_FPACK_WIDTH                     (2U)
#define SAI_TCR4_FPACK(x)                        (((uint32_t)(((uint32_t)(x)) << SAI_TCR4_FPACK_SHIFT)) & SAI_TCR4_FPACK_MASK)

#define SAI_TCR4_FCOMB_MASK                      (0xC000000U)
#define SAI_TCR4_FCOMB_SHIFT                     (26U)
#define SAI_TCR4_FCOMB_WIDTH                     (2U)
#define SAI_TCR4_FCOMB(x)                        (((uint32_t)(((uint32_t)(x)) << SAI_TCR4_FCOMB_SHIFT)) & SAI_TCR4_FCOMB_MASK)

#define SAI_TCR4_FCONT_MASK                      (0x10000000U)
#define SAI_TCR4_FCONT_SHIFT                     (28U)
#define SAI_TCR4_FCONT_WIDTH                     (1U)
#define SAI_TCR4_FCONT(x)                        (((uint32_t)(((uint32_t)(x)) << SAI_TCR4_FCONT_SHIFT)) & SAI_TCR4_FCONT_MASK)
/*! @} */

/*! @name TCR5 - Transmit Configuration 5 */
/*! @{ */

#define SAI_TCR5_FBT_MASK                        (0x1F00U)
#define SAI_TCR5_FBT_SHIFT                       (8U)
#define SAI_TCR5_FBT_WIDTH                       (5U)
#define SAI_TCR5_FBT(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_TCR5_FBT_SHIFT)) & SAI_TCR5_FBT_MASK)

#define SAI_TCR5_W0W_MASK                        (0x1F0000U)
#define SAI_TCR5_W0W_SHIFT                       (16U)
#define SAI_TCR5_W0W_WIDTH                       (5U)
#define SAI_TCR5_W0W(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_TCR5_W0W_SHIFT)) & SAI_TCR5_W0W_MASK)

#define SAI_TCR5_WNW_MASK                        (0x1F000000U)
#define SAI_TCR5_WNW_SHIFT                       (24U)
#define SAI_TCR5_WNW_WIDTH                       (5U)
#define SAI_TCR5_WNW(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_TCR5_WNW_SHIFT)) & SAI_TCR5_WNW_MASK)
/*! @} */

/*! @name TDR - Transmit Data */
/*! @{ */

#define SAI_TDR_TDR_MASK                         (0xFFFFFFFFU)
#define SAI_TDR_TDR_SHIFT                        (0U)
#define SAI_TDR_TDR_WIDTH                        (32U)
#define SAI_TDR_TDR(x)                           (((uint32_t)(((uint32_t)(x)) << SAI_TDR_TDR_SHIFT)) & SAI_TDR_TDR_MASK)
/*! @} */

/*! @name TFR - Transmit FIFO */
/*! @{ */

#define SAI_TFR_RFP_MASK                         (0xFU)
#define SAI_TFR_RFP_SHIFT                        (0U)
#define SAI_TFR_RFP_WIDTH                        (4U)
#define SAI_TFR_RFP(x)                           (((uint32_t)(((uint32_t)(x)) << SAI_TFR_RFP_SHIFT)) & SAI_TFR_RFP_MASK)

#define SAI_TFR_WFP_MASK                         (0xF0000U)
#define SAI_TFR_WFP_SHIFT                        (16U)
#define SAI_TFR_WFP_WIDTH                        (4U)
#define SAI_TFR_WFP(x)                           (((uint32_t)(((uint32_t)(x)) << SAI_TFR_WFP_SHIFT)) & SAI_TFR_WFP_MASK)

#define SAI_TFR_WCP_MASK                         (0x80000000U)
#define SAI_TFR_WCP_SHIFT                        (31U)
#define SAI_TFR_WCP_WIDTH                        (1U)
#define SAI_TFR_WCP(x)                           (((uint32_t)(((uint32_t)(x)) << SAI_TFR_WCP_SHIFT)) & SAI_TFR_WCP_MASK)
/*! @} */

/*! @name TMR - Transmit Mask */
/*! @{ */

#define SAI_TMR_TWM_MASK                         (0xFFFFU)
#define SAI_TMR_TWM_SHIFT                        (0U)
#define SAI_TMR_TWM_WIDTH                        (16U)
#define SAI_TMR_TWM(x)                           (((uint32_t)(((uint32_t)(x)) << SAI_TMR_TWM_SHIFT)) & SAI_TMR_TWM_MASK)
/*! @} */

/*! @name RCSR - Receive Control */
/*! @{ */

#define SAI_RCSR_FRDE_MASK                       (0x1U)
#define SAI_RCSR_FRDE_SHIFT                      (0U)
#define SAI_RCSR_FRDE_WIDTH                      (1U)
#define SAI_RCSR_FRDE(x)                         (((uint32_t)(((uint32_t)(x)) << SAI_RCSR_FRDE_SHIFT)) & SAI_RCSR_FRDE_MASK)

#define SAI_RCSR_FWDE_MASK                       (0x2U)
#define SAI_RCSR_FWDE_SHIFT                      (1U)
#define SAI_RCSR_FWDE_WIDTH                      (1U)
#define SAI_RCSR_FWDE(x)                         (((uint32_t)(((uint32_t)(x)) << SAI_RCSR_FWDE_SHIFT)) & SAI_RCSR_FWDE_MASK)

#define SAI_RCSR_FRIE_MASK                       (0x100U)
#define SAI_RCSR_FRIE_SHIFT                      (8U)
#define SAI_RCSR_FRIE_WIDTH                      (1U)
#define SAI_RCSR_FRIE(x)                         (((uint32_t)(((uint32_t)(x)) << SAI_RCSR_FRIE_SHIFT)) & SAI_RCSR_FRIE_MASK)

#define SAI_RCSR_FWIE_MASK                       (0x200U)
#define SAI_RCSR_FWIE_SHIFT                      (9U)
#define SAI_RCSR_FWIE_WIDTH                      (1U)
#define SAI_RCSR_FWIE(x)                         (((uint32_t)(((uint32_t)(x)) << SAI_RCSR_FWIE_SHIFT)) & SAI_RCSR_FWIE_MASK)

#define SAI_RCSR_FEIE_MASK                       (0x400U)
#define SAI_RCSR_FEIE_SHIFT                      (10U)
#define SAI_RCSR_FEIE_WIDTH                      (1U)
#define SAI_RCSR_FEIE(x)                         (((uint32_t)(((uint32_t)(x)) << SAI_RCSR_FEIE_SHIFT)) & SAI_RCSR_FEIE_MASK)

#define SAI_RCSR_SEIE_MASK                       (0x800U)
#define SAI_RCSR_SEIE_SHIFT                      (11U)
#define SAI_RCSR_SEIE_WIDTH                      (1U)
#define SAI_RCSR_SEIE(x)                         (((uint32_t)(((uint32_t)(x)) << SAI_RCSR_SEIE_SHIFT)) & SAI_RCSR_SEIE_MASK)

#define SAI_RCSR_WSIE_MASK                       (0x1000U)
#define SAI_RCSR_WSIE_SHIFT                      (12U)
#define SAI_RCSR_WSIE_WIDTH                      (1U)
#define SAI_RCSR_WSIE(x)                         (((uint32_t)(((uint32_t)(x)) << SAI_RCSR_WSIE_SHIFT)) & SAI_RCSR_WSIE_MASK)

#define SAI_RCSR_FRF_MASK                        (0x10000U)
#define SAI_RCSR_FRF_SHIFT                       (16U)
#define SAI_RCSR_FRF_WIDTH                       (1U)
#define SAI_RCSR_FRF(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_RCSR_FRF_SHIFT)) & SAI_RCSR_FRF_MASK)

#define SAI_RCSR_FWF_MASK                        (0x20000U)
#define SAI_RCSR_FWF_SHIFT                       (17U)
#define SAI_RCSR_FWF_WIDTH                       (1U)
#define SAI_RCSR_FWF(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_RCSR_FWF_SHIFT)) & SAI_RCSR_FWF_MASK)

#define SAI_RCSR_FEF_MASK                        (0x40000U)
#define SAI_RCSR_FEF_SHIFT                       (18U)
#define SAI_RCSR_FEF_WIDTH                       (1U)
#define SAI_RCSR_FEF(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_RCSR_FEF_SHIFT)) & SAI_RCSR_FEF_MASK)

#define SAI_RCSR_SEF_MASK                        (0x80000U)
#define SAI_RCSR_SEF_SHIFT                       (19U)
#define SAI_RCSR_SEF_WIDTH                       (1U)
#define SAI_RCSR_SEF(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_RCSR_SEF_SHIFT)) & SAI_RCSR_SEF_MASK)

#define SAI_RCSR_WSF_MASK                        (0x100000U)
#define SAI_RCSR_WSF_SHIFT                       (20U)
#define SAI_RCSR_WSF_WIDTH                       (1U)
#define SAI_RCSR_WSF(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_RCSR_WSF_SHIFT)) & SAI_RCSR_WSF_MASK)

#define SAI_RCSR_SR_MASK                         (0x1000000U)
#define SAI_RCSR_SR_SHIFT                        (24U)
#define SAI_RCSR_SR_WIDTH                        (1U)
#define SAI_RCSR_SR(x)                           (((uint32_t)(((uint32_t)(x)) << SAI_RCSR_SR_SHIFT)) & SAI_RCSR_SR_MASK)

#define SAI_RCSR_FR_MASK                         (0x2000000U)
#define SAI_RCSR_FR_SHIFT                        (25U)
#define SAI_RCSR_FR_WIDTH                        (1U)
#define SAI_RCSR_FR(x)                           (((uint32_t)(((uint32_t)(x)) << SAI_RCSR_FR_SHIFT)) & SAI_RCSR_FR_MASK)

#define SAI_RCSR_BCE_MASK                        (0x10000000U)
#define SAI_RCSR_BCE_SHIFT                       (28U)
#define SAI_RCSR_BCE_WIDTH                       (1U)
#define SAI_RCSR_BCE(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_RCSR_BCE_SHIFT)) & SAI_RCSR_BCE_MASK)

#define SAI_RCSR_DBGE_MASK                       (0x20000000U)
#define SAI_RCSR_DBGE_SHIFT                      (29U)
#define SAI_RCSR_DBGE_WIDTH                      (1U)
#define SAI_RCSR_DBGE(x)                         (((uint32_t)(((uint32_t)(x)) << SAI_RCSR_DBGE_SHIFT)) & SAI_RCSR_DBGE_MASK)

#define SAI_RCSR_RE_MASK                         (0x80000000U)
#define SAI_RCSR_RE_SHIFT                        (31U)
#define SAI_RCSR_RE_WIDTH                        (1U)
#define SAI_RCSR_RE(x)                           (((uint32_t)(((uint32_t)(x)) << SAI_RCSR_RE_SHIFT)) & SAI_RCSR_RE_MASK)
/*! @} */

/*! @name RCR1 - Receive Configuration 1 */
/*! @{ */

#define SAI_RCR1_RFW_MASK                        (0x7U)
#define SAI_RCR1_RFW_SHIFT                       (0U)
#define SAI_RCR1_RFW_WIDTH                       (3U)
#define SAI_RCR1_RFW(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_RCR1_RFW_SHIFT)) & SAI_RCR1_RFW_MASK)
/*! @} */

/*! @name RCR2 - Receive Configuration 2 */
/*! @{ */

#define SAI_RCR2_DIV_MASK                        (0xFFU)
#define SAI_RCR2_DIV_SHIFT                       (0U)
#define SAI_RCR2_DIV_WIDTH                       (8U)
#define SAI_RCR2_DIV(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_RCR2_DIV_SHIFT)) & SAI_RCR2_DIV_MASK)

#define SAI_RCR2_BYP_MASK                        (0x800000U)
#define SAI_RCR2_BYP_SHIFT                       (23U)
#define SAI_RCR2_BYP_WIDTH                       (1U)
#define SAI_RCR2_BYP(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_RCR2_BYP_SHIFT)) & SAI_RCR2_BYP_MASK)

#define SAI_RCR2_BCD_MASK                        (0x1000000U)
#define SAI_RCR2_BCD_SHIFT                       (24U)
#define SAI_RCR2_BCD_WIDTH                       (1U)
#define SAI_RCR2_BCD(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_RCR2_BCD_SHIFT)) & SAI_RCR2_BCD_MASK)

#define SAI_RCR2_BCP_MASK                        (0x2000000U)
#define SAI_RCR2_BCP_SHIFT                       (25U)
#define SAI_RCR2_BCP_WIDTH                       (1U)
#define SAI_RCR2_BCP(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_RCR2_BCP_SHIFT)) & SAI_RCR2_BCP_MASK)

#define SAI_RCR2_MSEL_MASK                       (0xC000000U)
#define SAI_RCR2_MSEL_SHIFT                      (26U)
#define SAI_RCR2_MSEL_WIDTH                      (2U)
#define SAI_RCR2_MSEL(x)                         (((uint32_t)(((uint32_t)(x)) << SAI_RCR2_MSEL_SHIFT)) & SAI_RCR2_MSEL_MASK)

#define SAI_RCR2_BCI_MASK                        (0x10000000U)
#define SAI_RCR2_BCI_SHIFT                       (28U)
#define SAI_RCR2_BCI_WIDTH                       (1U)
#define SAI_RCR2_BCI(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_RCR2_BCI_SHIFT)) & SAI_RCR2_BCI_MASK)

#define SAI_RCR2_SYNC_MASK                       (0x40000000U)
#define SAI_RCR2_SYNC_SHIFT                      (30U)
#define SAI_RCR2_SYNC_WIDTH                      (1U)
#define SAI_RCR2_SYNC(x)                         (((uint32_t)(((uint32_t)(x)) << SAI_RCR2_SYNC_SHIFT)) & SAI_RCR2_SYNC_MASK)
/*! @} */

/*! @name RCR3 - Receive Configuration 3 */
/*! @{ */

#define SAI_RCR3_WDFL_MASK                       (0xFU)
#define SAI_RCR3_WDFL_SHIFT                      (0U)
#define SAI_RCR3_WDFL_WIDTH                      (4U)
#define SAI_RCR3_WDFL(x)                         (((uint32_t)(((uint32_t)(x)) << SAI_RCR3_WDFL_SHIFT)) & SAI_RCR3_WDFL_MASK)

#define SAI_RCR3_RCE_MASK                        (0xF0000U)  /* Merged from fields with different position or width, of widths (1, 4), largest definition used */
#define SAI_RCR3_RCE_SHIFT                       (16U)
#define SAI_RCR3_RCE_WIDTH                       (4U)
#define SAI_RCR3_RCE(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_RCR3_RCE_SHIFT)) & SAI_RCR3_RCE_MASK)  /* Merged from fields with different position or width, of widths (1, 4), largest definition used */

#define SAI_RCR3_CFR_MASK                        (0xF000000U)
#define SAI_RCR3_CFR_SHIFT                       (24U)
#define SAI_RCR3_CFR_WIDTH                       (4U)
#define SAI_RCR3_CFR(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_RCR3_CFR_SHIFT)) & SAI_RCR3_CFR_MASK)
/*! @} */

/*! @name RCR4 - Receive Configuration 4 */
/*! @{ */

#define SAI_RCR4_FSD_MASK                        (0x1U)
#define SAI_RCR4_FSD_SHIFT                       (0U)
#define SAI_RCR4_FSD_WIDTH                       (1U)
#define SAI_RCR4_FSD(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_RCR4_FSD_SHIFT)) & SAI_RCR4_FSD_MASK)

#define SAI_RCR4_FSP_MASK                        (0x2U)
#define SAI_RCR4_FSP_SHIFT                       (1U)
#define SAI_RCR4_FSP_WIDTH                       (1U)
#define SAI_RCR4_FSP(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_RCR4_FSP_SHIFT)) & SAI_RCR4_FSP_MASK)

#define SAI_RCR4_ONDEM_MASK                      (0x4U)
#define SAI_RCR4_ONDEM_SHIFT                     (2U)
#define SAI_RCR4_ONDEM_WIDTH                     (1U)
#define SAI_RCR4_ONDEM(x)                        (((uint32_t)(((uint32_t)(x)) << SAI_RCR4_ONDEM_SHIFT)) & SAI_RCR4_ONDEM_MASK)

#define SAI_RCR4_FSE_MASK                        (0x8U)
#define SAI_RCR4_FSE_SHIFT                       (3U)
#define SAI_RCR4_FSE_WIDTH                       (1U)
#define SAI_RCR4_FSE(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_RCR4_FSE_SHIFT)) & SAI_RCR4_FSE_MASK)

#define SAI_RCR4_MF_MASK                         (0x10U)
#define SAI_RCR4_MF_SHIFT                        (4U)
#define SAI_RCR4_MF_WIDTH                        (1U)
#define SAI_RCR4_MF(x)                           (((uint32_t)(((uint32_t)(x)) << SAI_RCR4_MF_SHIFT)) & SAI_RCR4_MF_MASK)

#define SAI_RCR4_SYWD_MASK                       (0x1F00U)
#define SAI_RCR4_SYWD_SHIFT                      (8U)
#define SAI_RCR4_SYWD_WIDTH                      (5U)
#define SAI_RCR4_SYWD(x)                         (((uint32_t)(((uint32_t)(x)) << SAI_RCR4_SYWD_SHIFT)) & SAI_RCR4_SYWD_MASK)

#define SAI_RCR4_FRSZ_MASK                       (0xF0000U)
#define SAI_RCR4_FRSZ_SHIFT                      (16U)
#define SAI_RCR4_FRSZ_WIDTH                      (4U)
#define SAI_RCR4_FRSZ(x)                         (((uint32_t)(((uint32_t)(x)) << SAI_RCR4_FRSZ_SHIFT)) & SAI_RCR4_FRSZ_MASK)

#define SAI_RCR4_FPACK_MASK                      (0x3000000U)
#define SAI_RCR4_FPACK_SHIFT                     (24U)
#define SAI_RCR4_FPACK_WIDTH                     (2U)
#define SAI_RCR4_FPACK(x)                        (((uint32_t)(((uint32_t)(x)) << SAI_RCR4_FPACK_SHIFT)) & SAI_RCR4_FPACK_MASK)

#define SAI_RCR4_FCOMB_MASK                      (0xC000000U)
#define SAI_RCR4_FCOMB_SHIFT                     (26U)
#define SAI_RCR4_FCOMB_WIDTH                     (2U)
#define SAI_RCR4_FCOMB(x)                        (((uint32_t)(((uint32_t)(x)) << SAI_RCR4_FCOMB_SHIFT)) & SAI_RCR4_FCOMB_MASK)

#define SAI_RCR4_FCONT_MASK                      (0x10000000U)
#define SAI_RCR4_FCONT_SHIFT                     (28U)
#define SAI_RCR4_FCONT_WIDTH                     (1U)
#define SAI_RCR4_FCONT(x)                        (((uint32_t)(((uint32_t)(x)) << SAI_RCR4_FCONT_SHIFT)) & SAI_RCR4_FCONT_MASK)
/*! @} */

/*! @name RCR5 - Receive Configuration 5 */
/*! @{ */

#define SAI_RCR5_FBT_MASK                        (0x1F00U)
#define SAI_RCR5_FBT_SHIFT                       (8U)
#define SAI_RCR5_FBT_WIDTH                       (5U)
#define SAI_RCR5_FBT(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_RCR5_FBT_SHIFT)) & SAI_RCR5_FBT_MASK)

#define SAI_RCR5_W0W_MASK                        (0x1F0000U)
#define SAI_RCR5_W0W_SHIFT                       (16U)
#define SAI_RCR5_W0W_WIDTH                       (5U)
#define SAI_RCR5_W0W(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_RCR5_W0W_SHIFT)) & SAI_RCR5_W0W_MASK)

#define SAI_RCR5_WNW_MASK                        (0x1F000000U)
#define SAI_RCR5_WNW_SHIFT                       (24U)
#define SAI_RCR5_WNW_WIDTH                       (5U)
#define SAI_RCR5_WNW(x)                          (((uint32_t)(((uint32_t)(x)) << SAI_RCR5_WNW_SHIFT)) & SAI_RCR5_WNW_MASK)
/*! @} */

/*! @name RDR - Receive Data */
/*! @{ */

#define SAI_RDR_RDR_MASK                         (0xFFFFFFFFU)
#define SAI_RDR_RDR_SHIFT                        (0U)
#define SAI_RDR_RDR_WIDTH                        (32U)
#define SAI_RDR_RDR(x)                           (((uint32_t)(((uint32_t)(x)) << SAI_RDR_RDR_SHIFT)) & SAI_RDR_RDR_MASK)
/*! @} */

/*! @name RFR - Receive FIFO */
/*! @{ */

#define SAI_RFR_RFP_MASK                         (0xFU)
#define SAI_RFR_RFP_SHIFT                        (0U)
#define SAI_RFR_RFP_WIDTH                        (4U)
#define SAI_RFR_RFP(x)                           (((uint32_t)(((uint32_t)(x)) << SAI_RFR_RFP_SHIFT)) & SAI_RFR_RFP_MASK)

#define SAI_RFR_RCP_MASK                         (0x8000U)
#define SAI_RFR_RCP_SHIFT                        (15U)
#define SAI_RFR_RCP_WIDTH                        (1U)
#define SAI_RFR_RCP(x)                           (((uint32_t)(((uint32_t)(x)) << SAI_RFR_RCP_SHIFT)) & SAI_RFR_RCP_MASK)

#define SAI_RFR_WFP_MASK                         (0xF0000U)
#define SAI_RFR_WFP_SHIFT                        (16U)
#define SAI_RFR_WFP_WIDTH                        (4U)
#define SAI_RFR_WFP(x)                           (((uint32_t)(((uint32_t)(x)) << SAI_RFR_WFP_SHIFT)) & SAI_RFR_WFP_MASK)
/*! @} */

/*! @name RMR - Receive Mask */
/*! @{ */

#define SAI_RMR_RWM_MASK                         (0xFFFFU)
#define SAI_RMR_RWM_SHIFT                        (0U)
#define SAI_RMR_RWM_WIDTH                        (16U)
#define SAI_RMR_RWM(x)                           (((uint32_t)(((uint32_t)(x)) << SAI_RMR_RWM_SHIFT)) & SAI_RMR_RWM_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group SAI_Register_Masks */

/*!
 * @}
 */ /* end of group SAI_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_SAI_H_) */
