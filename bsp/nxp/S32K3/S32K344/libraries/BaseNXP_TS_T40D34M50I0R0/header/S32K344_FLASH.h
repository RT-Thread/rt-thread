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
 * @file S32K344_FLASH.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_FLASH
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
#if !defined(S32K344_FLASH_H_)  /* Check if memory map has not been already included */
#define S32K344_FLASH_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- FLASH Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FLASH_Peripheral_Access_Layer FLASH Peripheral Access Layer
 * @{
 */

/** FLASH - Size of Registers Arrays */
#define FLASH_UM_COUNT                            9u
#define FLASH_DATA_COUNT                          32u

/** FLASH - Register Layout Typedef */
typedef struct {
  __IO uint32_t MCR;                               /**< Module Configuration, offset: 0x0 */
  __IO uint32_t MCRS;                              /**< Module Configuration Status, offset: 0x4 */
  __I  uint32_t MCRE;                              /**< Extended Module Configuration, offset: 0x8 */
  __IO uint32_t CTL;                               /**< Module Control, offset: 0xC */
  __IO uint32_t ADR;                               /**< Address, offset: 0x10 */
  __I  uint32_t PEADR;                             /**< Program and Erase Address, offset: 0x14 */
  uint8_t RESERVED_0[56];
  __I  uint32_t SPELOCK;                           /**< Sector Program and Erase Hardware Lock, offset: 0x50 */
  __I  uint32_t SSPELOCK;                          /**< Super Sector Program and Erase Hardware Lock, offset: 0x54 */
  uint8_t RESERVED_1[24];
  __I  uint32_t XSPELOCK;                          /**< Express Sector Program and Erase Hardware Lock, offset: 0x70 */
  __I  uint32_t XSSPELOCK;                         /**< Express Super Sector Program and Erase Hardware Lock, offset: 0x74 */
  uint8_t RESERVED_2[24];
  __IO uint32_t TMD;                               /**< Test Mode Disable Password Check, offset: 0x90 */
  __IO uint32_t UT0;                               /**< UTest 0, offset: 0x94 */
  __IO uint32_t UM[FLASH_UM_COUNT];                /**< UMISRn, array offset: 0x98, array step: 0x4 */
  __IO uint32_t UM9;                               /**< UMISR9, offset: 0xBC */
  uint8_t RESERVED_3[16];
  __IO uint32_t UD0;                               /**< UTest Data 0, offset: 0xD0 */
  __IO uint32_t UD1;                               /**< UTest Data 1, offset: 0xD4 */
  __IO uint32_t UD2;                               /**< UTest Data 2, offset: 0xD8 */
  __IO uint32_t UD3;                               /**< UTest Data 3, offset: 0xDC */
  __IO uint32_t UD4;                               /**< UTest Data 4, offset: 0xE0 */
  __IO uint32_t UD5;                               /**< UTest Data 5, offset: 0xE4 */
  __IO uint32_t UA0;                               /**< UTest Address 0, offset: 0xE8 */
  __IO uint32_t UA1;                               /**< UTest Address 1, offset: 0xEC */
  __IO uint32_t XMCR;                              /**< Express Module Configuration, offset: 0xF0 */
  __I  uint32_t XPEADR;                            /**< Express Program Address, offset: 0xF4 */
  uint8_t RESERVED_4[8];
  __IO uint32_t DATA[FLASH_DATA_COUNT];            /**< Program Data, array offset: 0x100, array step: 0x4 */
} FLASH_Type, *FLASH_MemMapPtr;

/** Number of instances of the FLASH module. */
#define FLASH_INSTANCE_COUNT                     (1u)

/* FLASH - Peripheral instance base addresses */
/** Peripheral FLASH base address */
#define IP_FLASH_BASE                            (0x402EC000u)
/** Peripheral FLASH base pointer */
#define IP_FLASH                                 ((FLASH_Type *)IP_FLASH_BASE)
/** Array initializer of FLASH peripheral base addresses */
#define IP_FLASH_BASE_ADDRS                      { IP_FLASH_BASE }
/** Array initializer of FLASH peripheral base pointers */
#define IP_FLASH_BASE_PTRS                       { IP_FLASH }

/* ----------------------------------------------------------------------------
   -- FLASH Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FLASH_Register_Masks FLASH Register Masks
 * @{
 */

/*! @name MCR - Module Configuration */
/*! @{ */

#define FLASH_MCR_EHV_MASK                       (0x1U)
#define FLASH_MCR_EHV_SHIFT                      (0U)
#define FLASH_MCR_EHV_WIDTH                      (1U)
#define FLASH_MCR_EHV(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_MCR_EHV_SHIFT)) & FLASH_MCR_EHV_MASK)

#define FLASH_MCR_ERS_MASK                       (0x10U)
#define FLASH_MCR_ERS_SHIFT                      (4U)
#define FLASH_MCR_ERS_WIDTH                      (1U)
#define FLASH_MCR_ERS(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_MCR_ERS_SHIFT)) & FLASH_MCR_ERS_MASK)

#define FLASH_MCR_ESS_MASK                       (0x20U)
#define FLASH_MCR_ESS_SHIFT                      (5U)
#define FLASH_MCR_ESS_WIDTH                      (1U)
#define FLASH_MCR_ESS(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_MCR_ESS_SHIFT)) & FLASH_MCR_ESS_MASK)

#define FLASH_MCR_PGM_MASK                       (0x100U)
#define FLASH_MCR_PGM_SHIFT                      (8U)
#define FLASH_MCR_PGM_WIDTH                      (1U)
#define FLASH_MCR_PGM(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_MCR_PGM_SHIFT)) & FLASH_MCR_PGM_MASK)

#define FLASH_MCR_WDIE_MASK                      (0x1000U)
#define FLASH_MCR_WDIE_SHIFT                     (12U)
#define FLASH_MCR_WDIE_WIDTH                     (1U)
#define FLASH_MCR_WDIE(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_MCR_WDIE_SHIFT)) & FLASH_MCR_WDIE_MASK)

#define FLASH_MCR_PECIE_MASK                     (0x8000U)
#define FLASH_MCR_PECIE_SHIFT                    (15U)
#define FLASH_MCR_PECIE_WIDTH                    (1U)
#define FLASH_MCR_PECIE(x)                       (((uint32_t)(((uint32_t)(x)) << FLASH_MCR_PECIE_SHIFT)) & FLASH_MCR_PECIE_MASK)

#define FLASH_MCR_PEID_MASK                      (0xFF0000U)
#define FLASH_MCR_PEID_SHIFT                     (16U)
#define FLASH_MCR_PEID_WIDTH                     (8U)
#define FLASH_MCR_PEID(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_MCR_PEID_SHIFT)) & FLASH_MCR_PEID_MASK)
/*! @} */

/*! @name MCRS - Module Configuration Status */
/*! @{ */

#define FLASH_MCRS_RE_MASK                       (0x1U)
#define FLASH_MCRS_RE_SHIFT                      (0U)
#define FLASH_MCRS_RE_WIDTH                      (1U)
#define FLASH_MCRS_RE(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_MCRS_RE_SHIFT)) & FLASH_MCRS_RE_MASK)

#define FLASH_MCRS_TSPELOCK_MASK                 (0x100U)
#define FLASH_MCRS_TSPELOCK_SHIFT                (8U)
#define FLASH_MCRS_TSPELOCK_WIDTH                (1U)
#define FLASH_MCRS_TSPELOCK(x)                   (((uint32_t)(((uint32_t)(x)) << FLASH_MCRS_TSPELOCK_SHIFT)) & FLASH_MCRS_TSPELOCK_MASK)

#define FLASH_MCRS_EPEG_MASK                     (0x200U)
#define FLASH_MCRS_EPEG_SHIFT                    (9U)
#define FLASH_MCRS_EPEG_WIDTH                    (1U)
#define FLASH_MCRS_EPEG(x)                       (((uint32_t)(((uint32_t)(x)) << FLASH_MCRS_EPEG_SHIFT)) & FLASH_MCRS_EPEG_MASK)

#define FLASH_MCRS_WDI_MASK                      (0x1000U)
#define FLASH_MCRS_WDI_SHIFT                     (12U)
#define FLASH_MCRS_WDI_WIDTH                     (1U)
#define FLASH_MCRS_WDI(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_MCRS_WDI_SHIFT)) & FLASH_MCRS_WDI_MASK)

#define FLASH_MCRS_PEG_MASK                      (0x4000U)
#define FLASH_MCRS_PEG_SHIFT                     (14U)
#define FLASH_MCRS_PEG_WIDTH                     (1U)
#define FLASH_MCRS_PEG(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_MCRS_PEG_SHIFT)) & FLASH_MCRS_PEG_MASK)

#define FLASH_MCRS_DONE_MASK                     (0x8000U)
#define FLASH_MCRS_DONE_SHIFT                    (15U)
#define FLASH_MCRS_DONE_WIDTH                    (1U)
#define FLASH_MCRS_DONE(x)                       (((uint32_t)(((uint32_t)(x)) << FLASH_MCRS_DONE_SHIFT)) & FLASH_MCRS_DONE_MASK)

#define FLASH_MCRS_PES_MASK                      (0x10000U)
#define FLASH_MCRS_PES_SHIFT                     (16U)
#define FLASH_MCRS_PES_WIDTH                     (1U)
#define FLASH_MCRS_PES(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_MCRS_PES_SHIFT)) & FLASH_MCRS_PES_MASK)

#define FLASH_MCRS_PEP_MASK                      (0x20000U)
#define FLASH_MCRS_PEP_SHIFT                     (17U)
#define FLASH_MCRS_PEP_WIDTH                     (1U)
#define FLASH_MCRS_PEP(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_MCRS_PEP_SHIFT)) & FLASH_MCRS_PEP_MASK)

#define FLASH_MCRS_RWE_MASK                      (0x100000U)
#define FLASH_MCRS_RWE_SHIFT                     (20U)
#define FLASH_MCRS_RWE_WIDTH                     (1U)
#define FLASH_MCRS_RWE(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_MCRS_RWE_SHIFT)) & FLASH_MCRS_RWE_MASK)

#define FLASH_MCRS_RRE_MASK                      (0x1000000U)
#define FLASH_MCRS_RRE_SHIFT                     (24U)
#define FLASH_MCRS_RRE_WIDTH                     (1U)
#define FLASH_MCRS_RRE(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_MCRS_RRE_SHIFT)) & FLASH_MCRS_RRE_MASK)

#define FLASH_MCRS_RVE_MASK                      (0x2000000U)
#define FLASH_MCRS_RVE_SHIFT                     (25U)
#define FLASH_MCRS_RVE_WIDTH                     (1U)
#define FLASH_MCRS_RVE(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_MCRS_RVE_SHIFT)) & FLASH_MCRS_RVE_MASK)

#define FLASH_MCRS_EEE_MASK                      (0x10000000U)
#define FLASH_MCRS_EEE_SHIFT                     (28U)
#define FLASH_MCRS_EEE_WIDTH                     (1U)
#define FLASH_MCRS_EEE(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_MCRS_EEE_SHIFT)) & FLASH_MCRS_EEE_MASK)

#define FLASH_MCRS_AEE_MASK                      (0x20000000U)
#define FLASH_MCRS_AEE_SHIFT                     (29U)
#define FLASH_MCRS_AEE_WIDTH                     (1U)
#define FLASH_MCRS_AEE(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_MCRS_AEE_SHIFT)) & FLASH_MCRS_AEE_MASK)

#define FLASH_MCRS_SBC_MASK                      (0x40000000U)
#define FLASH_MCRS_SBC_SHIFT                     (30U)
#define FLASH_MCRS_SBC_WIDTH                     (1U)
#define FLASH_MCRS_SBC(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_MCRS_SBC_SHIFT)) & FLASH_MCRS_SBC_MASK)

#define FLASH_MCRS_EER_MASK                      (0x80000000U)
#define FLASH_MCRS_EER_SHIFT                     (31U)
#define FLASH_MCRS_EER_WIDTH                     (1U)
#define FLASH_MCRS_EER(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_MCRS_EER_SHIFT)) & FLASH_MCRS_EER_MASK)
/*! @} */

/*! @name MCRE - Extended Module Configuration */
/*! @{ */

#define FLASH_MCRE_n256K_MASK                    (0xC0U)
#define FLASH_MCRE_n256K_SHIFT                   (6U)
#define FLASH_MCRE_n256K_WIDTH                   (2U)
#define FLASH_MCRE_n256K(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_MCRE_n256K_SHIFT)) & FLASH_MCRE_n256K_MASK)

#define FLASH_MCRE_n512K_MASK                    (0xC000U)
#define FLASH_MCRE_n512K_SHIFT                   (14U)
#define FLASH_MCRE_n512K_WIDTH                   (2U)
#define FLASH_MCRE_n512K(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_MCRE_n512K_SHIFT)) & FLASH_MCRE_n512K_MASK)

#define FLASH_MCRE_n1M_MASK                      (0xE00000U)
#define FLASH_MCRE_n1M_SHIFT                     (21U)
#define FLASH_MCRE_n1M_WIDTH                     (3U)
#define FLASH_MCRE_n1M(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_MCRE_n1M_SHIFT)) & FLASH_MCRE_n1M_MASK)
/*! @} */

/*! @name CTL - Module Control */
/*! @{ */

#define FLASH_CTL_RWSC_MASK                      (0x1F00U)
#define FLASH_CTL_RWSC_SHIFT                     (8U)
#define FLASH_CTL_RWSC_WIDTH                     (5U)
#define FLASH_CTL_RWSC(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_CTL_RWSC_SHIFT)) & FLASH_CTL_RWSC_MASK)

#define FLASH_CTL_RWSL_MASK                      (0x8000U)
#define FLASH_CTL_RWSL_SHIFT                     (15U)
#define FLASH_CTL_RWSL_WIDTH                     (1U)
#define FLASH_CTL_RWSL(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_CTL_RWSL_SHIFT)) & FLASH_CTL_RWSL_MASK)
/*! @} */

/*! @name ADR - Address */
/*! @{ */

#define FLASH_ADR_ADDR_MASK                      (0x7FFFEU)
#define FLASH_ADR_ADDR_SHIFT                     (1U)
#define FLASH_ADR_ADDR_WIDTH                     (18U)
#define FLASH_ADR_ADDR(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_ADR_ADDR_SHIFT)) & FLASH_ADR_ADDR_MASK)

#define FLASH_ADR_A0_MASK                        (0x80000U)
#define FLASH_ADR_A0_SHIFT                       (19U)
#define FLASH_ADR_A0_WIDTH                       (1U)
#define FLASH_ADR_A0(x)                          (((uint32_t)(((uint32_t)(x)) << FLASH_ADR_A0_SHIFT)) & FLASH_ADR_A0_MASK)

#define FLASH_ADR_A1_MASK                        (0x100000U)
#define FLASH_ADR_A1_SHIFT                       (20U)
#define FLASH_ADR_A1_WIDTH                       (1U)
#define FLASH_ADR_A1(x)                          (((uint32_t)(((uint32_t)(x)) << FLASH_ADR_A1_SHIFT)) & FLASH_ADR_A1_MASK)

#define FLASH_ADR_A2_MASK                        (0x200000U)
#define FLASH_ADR_A2_SHIFT                       (21U)
#define FLASH_ADR_A2_WIDTH                       (1U)
#define FLASH_ADR_A2(x)                          (((uint32_t)(((uint32_t)(x)) << FLASH_ADR_A2_SHIFT)) & FLASH_ADR_A2_MASK)

#define FLASH_ADR_A3_MASK                        (0x400000U)
#define FLASH_ADR_A3_SHIFT                       (22U)
#define FLASH_ADR_A3_WIDTH                       (1U)
#define FLASH_ADR_A3(x)                          (((uint32_t)(((uint32_t)(x)) << FLASH_ADR_A3_SHIFT)) & FLASH_ADR_A3_MASK)

#define FLASH_ADR_A4_MASK                        (0x800000U)
#define FLASH_ADR_A4_SHIFT                       (23U)
#define FLASH_ADR_A4_WIDTH                       (1U)
#define FLASH_ADR_A4(x)                          (((uint32_t)(((uint32_t)(x)) << FLASH_ADR_A4_SHIFT)) & FLASH_ADR_A4_MASK)

#define FLASH_ADR_A5_MASK                        (0x1000000U)
#define FLASH_ADR_A5_SHIFT                       (24U)
#define FLASH_ADR_A5_WIDTH                       (1U)
#define FLASH_ADR_A5(x)                          (((uint32_t)(((uint32_t)(x)) << FLASH_ADR_A5_SHIFT)) & FLASH_ADR_A5_MASK)

#define FLASH_ADR_SAD_MASK                       (0x80000000U)
#define FLASH_ADR_SAD_SHIFT                      (31U)
#define FLASH_ADR_SAD_WIDTH                      (1U)
#define FLASH_ADR_SAD(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_ADR_SAD_SHIFT)) & FLASH_ADR_SAD_MASK)
/*! @} */

/*! @name PEADR - Program and Erase Address */
/*! @{ */

#define FLASH_PEADR_PEADDR_MASK                  (0x7FFE0U)
#define FLASH_PEADR_PEADDR_SHIFT                 (5U)
#define FLASH_PEADR_PEADDR_WIDTH                 (14U)
#define FLASH_PEADR_PEADDR(x)                    (((uint32_t)(((uint32_t)(x)) << FLASH_PEADR_PEADDR_SHIFT)) & FLASH_PEADR_PEADDR_MASK)

#define FLASH_PEADR_PEA0_MASK                    (0x80000U)
#define FLASH_PEADR_PEA0_SHIFT                   (19U)
#define FLASH_PEADR_PEA0_WIDTH                   (1U)
#define FLASH_PEADR_PEA0(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_PEADR_PEA0_SHIFT)) & FLASH_PEADR_PEA0_MASK)

#define FLASH_PEADR_PEA1_MASK                    (0x100000U)
#define FLASH_PEADR_PEA1_SHIFT                   (20U)
#define FLASH_PEADR_PEA1_WIDTH                   (1U)
#define FLASH_PEADR_PEA1(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_PEADR_PEA1_SHIFT)) & FLASH_PEADR_PEA1_MASK)

#define FLASH_PEADR_PEA2_MASK                    (0x200000U)
#define FLASH_PEADR_PEA2_SHIFT                   (21U)
#define FLASH_PEADR_PEA2_WIDTH                   (1U)
#define FLASH_PEADR_PEA2(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_PEADR_PEA2_SHIFT)) & FLASH_PEADR_PEA2_MASK)

#define FLASH_PEADR_PEA3_MASK                    (0x400000U)
#define FLASH_PEADR_PEA3_SHIFT                   (22U)
#define FLASH_PEADR_PEA3_WIDTH                   (1U)
#define FLASH_PEADR_PEA3(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_PEADR_PEA3_SHIFT)) & FLASH_PEADR_PEA3_MASK)

#define FLASH_PEADR_PEA4_MASK                    (0x800000U)
#define FLASH_PEADR_PEA4_SHIFT                   (23U)
#define FLASH_PEADR_PEA4_WIDTH                   (1U)
#define FLASH_PEADR_PEA4(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_PEADR_PEA4_SHIFT)) & FLASH_PEADR_PEA4_MASK)

#define FLASH_PEADR_PEA5_MASK                    (0x1000000U)
#define FLASH_PEADR_PEA5_SHIFT                   (24U)
#define FLASH_PEADR_PEA5_WIDTH                   (1U)
#define FLASH_PEADR_PEA5(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_PEADR_PEA5_SHIFT)) & FLASH_PEADR_PEA5_MASK)

#define FLASH_PEADR_PEASAD_MASK                  (0x80000000U)
#define FLASH_PEADR_PEASAD_SHIFT                 (31U)
#define FLASH_PEADR_PEASAD_WIDTH                 (1U)
#define FLASH_PEADR_PEASAD(x)                    (((uint32_t)(((uint32_t)(x)) << FLASH_PEADR_PEASAD_SHIFT)) & FLASH_PEADR_PEASAD_MASK)
/*! @} */

/*! @name SPELOCK - Sector Program and Erase Hardware Lock */
/*! @{ */

#define FLASH_SPELOCK_SPELOCK_MASK               (0xFFFFFFFFU)
#define FLASH_SPELOCK_SPELOCK_SHIFT              (0U)
#define FLASH_SPELOCK_SPELOCK_WIDTH              (32U)
#define FLASH_SPELOCK_SPELOCK(x)                 (((uint32_t)(((uint32_t)(x)) << FLASH_SPELOCK_SPELOCK_SHIFT)) & FLASH_SPELOCK_SPELOCK_MASK)
/*! @} */

/*! @name SSPELOCK - Super Sector Program and Erase Hardware Lock */
/*! @{ */

#define FLASH_SSPELOCK_SSPELOCK_MASK             (0xFFFU)
#define FLASH_SSPELOCK_SSPELOCK_SHIFT            (0U)
#define FLASH_SSPELOCK_SSPELOCK_WIDTH            (12U)
#define FLASH_SSPELOCK_SSPELOCK(x)               (((uint32_t)(((uint32_t)(x)) << FLASH_SSPELOCK_SSPELOCK_SHIFT)) & FLASH_SSPELOCK_SSPELOCK_MASK)
/*! @} */

/*! @name XSPELOCK - Express Sector Program and Erase Hardware Lock */
/*! @{ */

#define FLASH_XSPELOCK_XSPELOCK_MASK             (0xFFFFFFFFU)
#define FLASH_XSPELOCK_XSPELOCK_SHIFT            (0U)
#define FLASH_XSPELOCK_XSPELOCK_WIDTH            (32U)
#define FLASH_XSPELOCK_XSPELOCK(x)               (((uint32_t)(((uint32_t)(x)) << FLASH_XSPELOCK_XSPELOCK_SHIFT)) & FLASH_XSPELOCK_XSPELOCK_MASK)
/*! @} */

/*! @name XSSPELOCK - Express Super Sector Program and Erase Hardware Lock */
/*! @{ */

#define FLASH_XSSPELOCK_XSSPELOCK_MASK           (0xFFFU)
#define FLASH_XSSPELOCK_XSSPELOCK_SHIFT          (0U)
#define FLASH_XSSPELOCK_XSSPELOCK_WIDTH          (12U)
#define FLASH_XSSPELOCK_XSSPELOCK(x)             (((uint32_t)(((uint32_t)(x)) << FLASH_XSSPELOCK_XSSPELOCK_SHIFT)) & FLASH_XSSPELOCK_XSSPELOCK_MASK)
/*! @} */

/*! @name TMD - Test Mode Disable Password Check */
/*! @{ */

#define FLASH_TMD_PWD_MASK                       (0xFFFFFFFFU)
#define FLASH_TMD_PWD_SHIFT                      (0U)
#define FLASH_TMD_PWD_WIDTH                      (32U)
#define FLASH_TMD_PWD(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_TMD_PWD_SHIFT)) & FLASH_TMD_PWD_MASK)
/*! @} */

/*! @name UT0 - UTest 0 */
/*! @{ */

#define FLASH_UT0_AID_MASK                       (0x1U)
#define FLASH_UT0_AID_SHIFT                      (0U)
#define FLASH_UT0_AID_WIDTH                      (1U)
#define FLASH_UT0_AID(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_UT0_AID_SHIFT)) & FLASH_UT0_AID_MASK)

#define FLASH_UT0_AIE_MASK                       (0x2U)
#define FLASH_UT0_AIE_SHIFT                      (1U)
#define FLASH_UT0_AIE_WIDTH                      (1U)
#define FLASH_UT0_AIE(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_UT0_AIE_SHIFT)) & FLASH_UT0_AIE_MASK)

#define FLASH_UT0_AIS_MASK                       (0x4U)
#define FLASH_UT0_AIS_SHIFT                      (2U)
#define FLASH_UT0_AIS_WIDTH                      (1U)
#define FLASH_UT0_AIS(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_UT0_AIS_SHIFT)) & FLASH_UT0_AIS_MASK)

#define FLASH_UT0_MRV_MASK                       (0x10U)
#define FLASH_UT0_MRV_SHIFT                      (4U)
#define FLASH_UT0_MRV_WIDTH                      (1U)
#define FLASH_UT0_MRV(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_UT0_MRV_SHIFT)) & FLASH_UT0_MRV_MASK)

#define FLASH_UT0_MRE_MASK                       (0x20U)
#define FLASH_UT0_MRE_SHIFT                      (5U)
#define FLASH_UT0_MRE_WIDTH                      (1U)
#define FLASH_UT0_MRE(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_UT0_MRE_SHIFT)) & FLASH_UT0_MRE_MASK)

#define FLASH_UT0_AISUS_MASK                     (0x40U)
#define FLASH_UT0_AISUS_SHIFT                    (6U)
#define FLASH_UT0_AISUS_WIDTH                    (1U)
#define FLASH_UT0_AISUS(x)                       (((uint32_t)(((uint32_t)(x)) << FLASH_UT0_AISUS_SHIFT)) & FLASH_UT0_AISUS_MASK)

#define FLASH_UT0_AIBPE_MASK                     (0x100U)
#define FLASH_UT0_AIBPE_SHIFT                    (8U)
#define FLASH_UT0_AIBPE_WIDTH                    (1U)
#define FLASH_UT0_AIBPE(x)                       (((uint32_t)(((uint32_t)(x)) << FLASH_UT0_AIBPE_SHIFT)) & FLASH_UT0_AIBPE_MASK)

#define FLASH_UT0_NAIBP_MASK                     (0x200U)
#define FLASH_UT0_NAIBP_SHIFT                    (9U)
#define FLASH_UT0_NAIBP_WIDTH                    (1U)
#define FLASH_UT0_NAIBP(x)                       (((uint32_t)(((uint32_t)(x)) << FLASH_UT0_NAIBP_SHIFT)) & FLASH_UT0_NAIBP_MASK)

#define FLASH_UT0_EIE_MASK                       (0x1000U)
#define FLASH_UT0_EIE_SHIFT                      (12U)
#define FLASH_UT0_EIE_WIDTH                      (1U)
#define FLASH_UT0_EIE(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_UT0_EIE_SHIFT)) & FLASH_UT0_EIE_MASK)

#define FLASH_UT0_EDIE_MASK                      (0x2000U)
#define FLASH_UT0_EDIE_SHIFT                     (13U)
#define FLASH_UT0_EDIE_WIDTH                     (1U)
#define FLASH_UT0_EDIE(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_UT0_EDIE_SHIFT)) & FLASH_UT0_EDIE_MASK)

#define FLASH_UT0_AEIE_MASK                      (0x4000U)
#define FLASH_UT0_AEIE_SHIFT                     (14U)
#define FLASH_UT0_AEIE_WIDTH                     (1U)
#define FLASH_UT0_AEIE(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_UT0_AEIE_SHIFT)) & FLASH_UT0_AEIE_MASK)

#define FLASH_UT0_RRIE_MASK                      (0x8000U)
#define FLASH_UT0_RRIE_SHIFT                     (15U)
#define FLASH_UT0_RRIE_WIDTH                     (1U)
#define FLASH_UT0_RRIE(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_UT0_RRIE_SHIFT)) & FLASH_UT0_RRIE_MASK)

#define FLASH_UT0_SBCE_MASK                      (0x40000000U)
#define FLASH_UT0_SBCE_SHIFT                     (30U)
#define FLASH_UT0_SBCE_WIDTH                     (1U)
#define FLASH_UT0_SBCE(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_UT0_SBCE_SHIFT)) & FLASH_UT0_SBCE_MASK)

#define FLASH_UT0_UTE_MASK                       (0x80000000U)
#define FLASH_UT0_UTE_SHIFT                      (31U)
#define FLASH_UT0_UTE_WIDTH                      (1U)
#define FLASH_UT0_UTE(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_UT0_UTE_SHIFT)) & FLASH_UT0_UTE_MASK)
/*! @} */

/*! @name UM - UMISRn */
/*! @{ */

#define FLASH_UM_MISR_MASK                       (0xFFFFFFFFU)
#define FLASH_UM_MISR_SHIFT                      (0U)
#define FLASH_UM_MISR_WIDTH                      (32U)
#define FLASH_UM_MISR(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_UM_MISR_SHIFT)) & FLASH_UM_MISR_MASK)
/*! @} */

/*! @name UM9 - UMISR9 */
/*! @{ */

#define FLASH_UM9_MISR_MASK                      (0x1U)
#define FLASH_UM9_MISR_SHIFT                     (0U)
#define FLASH_UM9_MISR_WIDTH                     (1U)
#define FLASH_UM9_MISR(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_UM9_MISR_SHIFT)) & FLASH_UM9_MISR_MASK)
/*! @} */

/*! @name UD0 - UTest Data 0 */
/*! @{ */

#define FLASH_UD0_EDATA_MASK                     (0xFFFFFFFFU)
#define FLASH_UD0_EDATA_SHIFT                    (0U)
#define FLASH_UD0_EDATA_WIDTH                    (32U)
#define FLASH_UD0_EDATA(x)                       (((uint32_t)(((uint32_t)(x)) << FLASH_UD0_EDATA_SHIFT)) & FLASH_UD0_EDATA_MASK)
/*! @} */

/*! @name UD1 - UTest Data 1 */
/*! @{ */

#define FLASH_UD1_EDATA_MASK                     (0xFFFFFFFFU)
#define FLASH_UD1_EDATA_SHIFT                    (0U)
#define FLASH_UD1_EDATA_WIDTH                    (32U)
#define FLASH_UD1_EDATA(x)                       (((uint32_t)(((uint32_t)(x)) << FLASH_UD1_EDATA_SHIFT)) & FLASH_UD1_EDATA_MASK)
/*! @} */

/*! @name UD2 - UTest Data 2 */
/*! @{ */

#define FLASH_UD2_EDATAC_MASK                    (0xFFU)
#define FLASH_UD2_EDATAC_SHIFT                   (0U)
#define FLASH_UD2_EDATAC_WIDTH                   (8U)
#define FLASH_UD2_EDATAC(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_UD2_EDATAC_SHIFT)) & FLASH_UD2_EDATAC_MASK)

#define FLASH_UD2_ED0_MASK                       (0x1000000U)
#define FLASH_UD2_ED0_SHIFT                      (24U)
#define FLASH_UD2_ED0_WIDTH                      (1U)
#define FLASH_UD2_ED0(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_UD2_ED0_SHIFT)) & FLASH_UD2_ED0_MASK)

#define FLASH_UD2_ED1_MASK                       (0x2000000U)
#define FLASH_UD2_ED1_SHIFT                      (25U)
#define FLASH_UD2_ED1_WIDTH                      (1U)
#define FLASH_UD2_ED1(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_UD2_ED1_SHIFT)) & FLASH_UD2_ED1_MASK)

#define FLASH_UD2_ED2_MASK                       (0x4000000U)
#define FLASH_UD2_ED2_SHIFT                      (26U)
#define FLASH_UD2_ED2_WIDTH                      (1U)
#define FLASH_UD2_ED2(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_UD2_ED2_SHIFT)) & FLASH_UD2_ED2_MASK)

#define FLASH_UD2_ED3_MASK                       (0x8000000U)
#define FLASH_UD2_ED3_SHIFT                      (27U)
#define FLASH_UD2_ED3_WIDTH                      (1U)
#define FLASH_UD2_ED3(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_UD2_ED3_SHIFT)) & FLASH_UD2_ED3_MASK)
/*! @} */

/*! @name UD3 - UTest Data 3 */
/*! @{ */

#define FLASH_UD3_EDDATA_MASK                    (0xFFFFFFFFU)
#define FLASH_UD3_EDDATA_SHIFT                   (0U)
#define FLASH_UD3_EDDATA_WIDTH                   (32U)
#define FLASH_UD3_EDDATA(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_UD3_EDDATA_SHIFT)) & FLASH_UD3_EDDATA_MASK)
/*! @} */

/*! @name UD4 - UTest Data 4 */
/*! @{ */

#define FLASH_UD4_EDDATA_MASK                    (0xFFFFFFFFU)
#define FLASH_UD4_EDDATA_SHIFT                   (0U)
#define FLASH_UD4_EDDATA_WIDTH                   (32U)
#define FLASH_UD4_EDDATA(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_UD4_EDDATA_SHIFT)) & FLASH_UD4_EDDATA_MASK)
/*! @} */

/*! @name UD5 - UTest Data 5 */
/*! @{ */

#define FLASH_UD5_EDDATAC_MASK                   (0xFFU)
#define FLASH_UD5_EDDATAC_SHIFT                  (0U)
#define FLASH_UD5_EDDATAC_WIDTH                  (8U)
#define FLASH_UD5_EDDATAC(x)                     (((uint32_t)(((uint32_t)(x)) << FLASH_UD5_EDDATAC_SHIFT)) & FLASH_UD5_EDDATAC_MASK)

#define FLASH_UD5_EDD0_MASK                      (0x1000000U)
#define FLASH_UD5_EDD0_SHIFT                     (24U)
#define FLASH_UD5_EDD0_WIDTH                     (1U)
#define FLASH_UD5_EDD0(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_UD5_EDD0_SHIFT)) & FLASH_UD5_EDD0_MASK)

#define FLASH_UD5_EDD1_MASK                      (0x2000000U)
#define FLASH_UD5_EDD1_SHIFT                     (25U)
#define FLASH_UD5_EDD1_WIDTH                     (1U)
#define FLASH_UD5_EDD1(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_UD5_EDD1_SHIFT)) & FLASH_UD5_EDD1_MASK)

#define FLASH_UD5_EDD2_MASK                      (0x4000000U)
#define FLASH_UD5_EDD2_SHIFT                     (26U)
#define FLASH_UD5_EDD2_WIDTH                     (1U)
#define FLASH_UD5_EDD2(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_UD5_EDD2_SHIFT)) & FLASH_UD5_EDD2_MASK)

#define FLASH_UD5_EDD3_MASK                      (0x8000000U)
#define FLASH_UD5_EDD3_SHIFT                     (27U)
#define FLASH_UD5_EDD3_WIDTH                     (1U)
#define FLASH_UD5_EDD3(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_UD5_EDD3_SHIFT)) & FLASH_UD5_EDD3_MASK)
/*! @} */

/*! @name UA0 - UTest Address 0 */
/*! @{ */

#define FLASH_UA0_AEI_MASK                       (0xFFFFFFFFU)
#define FLASH_UA0_AEI_SHIFT                      (0U)
#define FLASH_UA0_AEI_WIDTH                      (32U)
#define FLASH_UA0_AEI(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_UA0_AEI_SHIFT)) & FLASH_UA0_AEI_MASK)
/*! @} */

/*! @name UA1 - UTest Address 1 */
/*! @{ */

#define FLASH_UA1_AEI_MASK                       (0xFFFFFU)
#define FLASH_UA1_AEI_SHIFT                      (0U)
#define FLASH_UA1_AEI_WIDTH                      (20U)
#define FLASH_UA1_AEI(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_UA1_AEI_SHIFT)) & FLASH_UA1_AEI_MASK)
/*! @} */

/*! @name XMCR - Express Module Configuration */
/*! @{ */

#define FLASH_XMCR_XEHV_MASK                     (0x1U)
#define FLASH_XMCR_XEHV_SHIFT                    (0U)
#define FLASH_XMCR_XEHV_WIDTH                    (1U)
#define FLASH_XMCR_XEHV(x)                       (((uint32_t)(((uint32_t)(x)) << FLASH_XMCR_XEHV_SHIFT)) & FLASH_XMCR_XEHV_MASK)

#define FLASH_XMCR_XPGM_MASK                     (0x100U)
#define FLASH_XMCR_XPGM_SHIFT                    (8U)
#define FLASH_XMCR_XPGM_WIDTH                    (1U)
#define FLASH_XMCR_XPGM(x)                       (((uint32_t)(((uint32_t)(x)) << FLASH_XMCR_XPGM_SHIFT)) & FLASH_XMCR_XPGM_MASK)

#define FLASH_XMCR_XEPEG_MASK                    (0x200U)
#define FLASH_XMCR_XEPEG_SHIFT                   (9U)
#define FLASH_XMCR_XEPEG_WIDTH                   (1U)
#define FLASH_XMCR_XEPEG(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_XMCR_XEPEG_SHIFT)) & FLASH_XMCR_XEPEG_MASK)

#define FLASH_XMCR_XWDIE_MASK                    (0x800U)
#define FLASH_XMCR_XWDIE_SHIFT                   (11U)
#define FLASH_XMCR_XWDIE_WIDTH                   (1U)
#define FLASH_XMCR_XWDIE(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_XMCR_XWDIE_SHIFT)) & FLASH_XMCR_XWDIE_MASK)

#define FLASH_XMCR_XWDI_MASK                     (0x1000U)
#define FLASH_XMCR_XWDI_SHIFT                    (12U)
#define FLASH_XMCR_XWDI_WIDTH                    (1U)
#define FLASH_XMCR_XWDI(x)                       (((uint32_t)(((uint32_t)(x)) << FLASH_XMCR_XWDI_SHIFT)) & FLASH_XMCR_XWDI_MASK)

#define FLASH_XMCR_XDOK_MASK                     (0x2000U)
#define FLASH_XMCR_XDOK_SHIFT                    (13U)
#define FLASH_XMCR_XDOK_WIDTH                    (1U)
#define FLASH_XMCR_XDOK(x)                       (((uint32_t)(((uint32_t)(x)) << FLASH_XMCR_XDOK_SHIFT)) & FLASH_XMCR_XDOK_MASK)

#define FLASH_XMCR_XPEG_MASK                     (0x4000U)
#define FLASH_XMCR_XPEG_SHIFT                    (14U)
#define FLASH_XMCR_XPEG_WIDTH                    (1U)
#define FLASH_XMCR_XPEG(x)                       (((uint32_t)(((uint32_t)(x)) << FLASH_XMCR_XPEG_SHIFT)) & FLASH_XMCR_XPEG_MASK)

#define FLASH_XMCR_XDONE_MASK                    (0x8000U)
#define FLASH_XMCR_XDONE_SHIFT                   (15U)
#define FLASH_XMCR_XDONE_WIDTH                   (1U)
#define FLASH_XMCR_XDONE(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_XMCR_XDONE_SHIFT)) & FLASH_XMCR_XDONE_MASK)

#define FLASH_XMCR_XPEID_MASK                    (0xFF0000U)
#define FLASH_XMCR_XPEID_SHIFT                   (16U)
#define FLASH_XMCR_XPEID_WIDTH                   (8U)
#define FLASH_XMCR_XPEID(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_XMCR_XPEID_SHIFT)) & FLASH_XMCR_XPEID_MASK)
/*! @} */

/*! @name XPEADR - Express Program Address */
/*! @{ */

#define FLASH_XPEADR_XPEADDR_MASK                (0x7FFE0U)
#define FLASH_XPEADR_XPEADDR_SHIFT               (5U)
#define FLASH_XPEADR_XPEADDR_WIDTH               (14U)
#define FLASH_XPEADR_XPEADDR(x)                  (((uint32_t)(((uint32_t)(x)) << FLASH_XPEADR_XPEADDR_SHIFT)) & FLASH_XPEADR_XPEADDR_MASK)

#define FLASH_XPEADR_XPEA0_MASK                  (0x80000U)
#define FLASH_XPEADR_XPEA0_SHIFT                 (19U)
#define FLASH_XPEADR_XPEA0_WIDTH                 (1U)
#define FLASH_XPEADR_XPEA0(x)                    (((uint32_t)(((uint32_t)(x)) << FLASH_XPEADR_XPEA0_SHIFT)) & FLASH_XPEADR_XPEA0_MASK)

#define FLASH_XPEADR_XPEA1_MASK                  (0x100000U)
#define FLASH_XPEADR_XPEA1_SHIFT                 (20U)
#define FLASH_XPEADR_XPEA1_WIDTH                 (1U)
#define FLASH_XPEADR_XPEA1(x)                    (((uint32_t)(((uint32_t)(x)) << FLASH_XPEADR_XPEA1_SHIFT)) & FLASH_XPEADR_XPEA1_MASK)

#define FLASH_XPEADR_XPEA2_MASK                  (0x200000U)
#define FLASH_XPEADR_XPEA2_SHIFT                 (21U)
#define FLASH_XPEADR_XPEA2_WIDTH                 (1U)
#define FLASH_XPEADR_XPEA2(x)                    (((uint32_t)(((uint32_t)(x)) << FLASH_XPEADR_XPEA2_SHIFT)) & FLASH_XPEADR_XPEA2_MASK)

#define FLASH_XPEADR_XPEA3_MASK                  (0x400000U)
#define FLASH_XPEADR_XPEA3_SHIFT                 (22U)
#define FLASH_XPEADR_XPEA3_WIDTH                 (1U)
#define FLASH_XPEADR_XPEA3(x)                    (((uint32_t)(((uint32_t)(x)) << FLASH_XPEADR_XPEA3_SHIFT)) & FLASH_XPEADR_XPEA3_MASK)

#define FLASH_XPEADR_XPEA4_MASK                  (0x800000U)
#define FLASH_XPEADR_XPEA4_SHIFT                 (23U)
#define FLASH_XPEADR_XPEA4_WIDTH                 (1U)
#define FLASH_XPEADR_XPEA4(x)                    (((uint32_t)(((uint32_t)(x)) << FLASH_XPEADR_XPEA4_SHIFT)) & FLASH_XPEADR_XPEA4_MASK)

#define FLASH_XPEADR_XPEA5_MASK                  (0x1000000U)
#define FLASH_XPEADR_XPEA5_SHIFT                 (24U)
#define FLASH_XPEADR_XPEA5_WIDTH                 (1U)
#define FLASH_XPEADR_XPEA5(x)                    (((uint32_t)(((uint32_t)(x)) << FLASH_XPEADR_XPEA5_SHIFT)) & FLASH_XPEADR_XPEA5_MASK)
/*! @} */

/*! @name DATA - Program Data */
/*! @{ */

#define FLASH_DATA_PDATA_MASK                    (0xFFFFFFFFU)
#define FLASH_DATA_PDATA_SHIFT                   (0U)
#define FLASH_DATA_PDATA_WIDTH                   (32U)
#define FLASH_DATA_PDATA(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_DATA_PDATA_SHIFT)) & FLASH_DATA_PDATA_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group FLASH_Register_Masks */

/*!
 * @}
 */ /* end of group FLASH_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_FLASH_H_) */
