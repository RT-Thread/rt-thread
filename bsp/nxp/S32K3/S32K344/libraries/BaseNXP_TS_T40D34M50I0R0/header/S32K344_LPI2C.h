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
 * @file S32K344_LPI2C.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_LPI2C
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
#if !defined(S32K344_LPI2C_H_)  /* Check if memory map has not been already included */
#define S32K344_LPI2C_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- LPI2C Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPI2C_Peripheral_Access_Layer LPI2C Peripheral Access Layer
 * @{
 */

/** LPI2C - Register Layout Typedef */
typedef struct {
  __I  uint32_t VERID;                             /**< Version ID, offset: 0x0 */
  __I  uint32_t PARAM;                             /**< Parameter, offset: 0x4 */
  uint8_t RESERVED_0[8];
  __IO uint32_t MCR;                               /**< Master Control, offset: 0x10 */
  __IO uint32_t MSR;                               /**< Master Status, offset: 0x14 */
  __IO uint32_t MIER;                              /**< Master Interrupt Enable, offset: 0x18 */
  __IO uint32_t MDER;                              /**< Master DMA Enable, offset: 0x1C */
  __IO uint32_t MCFGR0;                            /**< Master Configuration 0, offset: 0x20 */
  __IO uint32_t MCFGR1;                            /**< Master Configuration 1, offset: 0x24 */
  __IO uint32_t MCFGR2;                            /**< Master Configuration 2, offset: 0x28 */
  __IO uint32_t MCFGR3;                            /**< Master Configuration 3, offset: 0x2C */
  uint8_t RESERVED_1[16];
  __IO uint32_t MDMR;                              /**< Master Data Match, offset: 0x40 */
  uint8_t RESERVED_2[4];
  __IO uint32_t MCCR0;                             /**< Master Clock Configuration 0, offset: 0x48 */
  uint8_t RESERVED_3[4];
  __IO uint32_t MCCR1;                             /**< Master Clock Configuration 1, offset: 0x50 */
  uint8_t RESERVED_4[4];
  __IO uint32_t MFCR;                              /**< Master FIFO Control, offset: 0x58 */
  __I  uint32_t MFSR;                              /**< Master FIFO Status, offset: 0x5C */
  __O  uint32_t MTDR;                              /**< Master Transmit Data, offset: 0x60 */
  uint8_t RESERVED_5[12];
  __I  uint32_t MRDR;                              /**< Master Receive Data, offset: 0x70 */
  uint8_t RESERVED_6[156];
  __IO uint32_t SCR;                               /**< Slave Control, offset: 0x110 */
  __IO uint32_t SSR;                               /**< Slave Status, offset: 0x114 */
  __IO uint32_t SIER;                              /**< Slave Interrupt Enable, offset: 0x118 */
  __IO uint32_t SDER;                              /**< Slave DMA Enable, offset: 0x11C */
  uint8_t RESERVED_7[4];
  __IO uint32_t SCFGR1;                            /**< Slave Configuration 1, offset: 0x124 */
  __IO uint32_t SCFGR2;                            /**< Slave Configuration 2, offset: 0x128 */
  uint8_t RESERVED_8[20];
  __IO uint32_t SAMR;                              /**< Slave Address Match, offset: 0x140 */
  uint8_t RESERVED_9[12];
  __I  uint32_t SASR;                              /**< Slave Address Status, offset: 0x150 */
  __IO uint32_t STAR;                              /**< Slave Transmit ACK, offset: 0x154 */
  uint8_t RESERVED_10[8];
  __O  uint32_t STDR;                              /**< Slave Transmit Data, offset: 0x160 */
  uint8_t RESERVED_11[12];
  __I  uint32_t SRDR;                              /**< Slave Receive Data, offset: 0x170 */
} LPI2C_Type, *LPI2C_MemMapPtr;

/** Number of instances of the LPI2C module. */
#define LPI2C_INSTANCE_COUNT                     (2u)

/* LPI2C - Peripheral instance base addresses */
/** Peripheral LPI2C_0 base address */
#define IP_LPI2C_0_BASE                          (0x40350000u)
/** Peripheral LPI2C_0 base pointer */
#define IP_LPI2C_0                               ((LPI2C_Type *)IP_LPI2C_0_BASE)
/** Peripheral LPI2C_1 base address */
#define IP_LPI2C_1_BASE                          (0x40354000u)
/** Peripheral LPI2C_1 base pointer */
#define IP_LPI2C_1                               ((LPI2C_Type *)IP_LPI2C_1_BASE)
/** Array initializer of LPI2C peripheral base addresses */
#define IP_LPI2C_BASE_ADDRS                      { IP_LPI2C_0_BASE, IP_LPI2C_1_BASE }
/** Array initializer of LPI2C peripheral base pointers */
#define IP_LPI2C_BASE_PTRS                       { IP_LPI2C_0, IP_LPI2C_1 }

/* ----------------------------------------------------------------------------
   -- LPI2C Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup LPI2C_Register_Masks LPI2C Register Masks
 * @{
 */

/*! @name VERID - Version ID */
/*! @{ */

#define LPI2C_VERID_FEATURE_MASK                 (0xFFFFU)
#define LPI2C_VERID_FEATURE_SHIFT                (0U)
#define LPI2C_VERID_FEATURE_WIDTH                (16U)
#define LPI2C_VERID_FEATURE(x)                   (((uint32_t)(((uint32_t)(x)) << LPI2C_VERID_FEATURE_SHIFT)) & LPI2C_VERID_FEATURE_MASK)

#define LPI2C_VERID_MINOR_MASK                   (0xFF0000U)
#define LPI2C_VERID_MINOR_SHIFT                  (16U)
#define LPI2C_VERID_MINOR_WIDTH                  (8U)
#define LPI2C_VERID_MINOR(x)                     (((uint32_t)(((uint32_t)(x)) << LPI2C_VERID_MINOR_SHIFT)) & LPI2C_VERID_MINOR_MASK)

#define LPI2C_VERID_MAJOR_MASK                   (0xFF000000U)
#define LPI2C_VERID_MAJOR_SHIFT                  (24U)
#define LPI2C_VERID_MAJOR_WIDTH                  (8U)
#define LPI2C_VERID_MAJOR(x)                     (((uint32_t)(((uint32_t)(x)) << LPI2C_VERID_MAJOR_SHIFT)) & LPI2C_VERID_MAJOR_MASK)
/*! @} */

/*! @name PARAM - Parameter */
/*! @{ */

#define LPI2C_PARAM_MTXFIFO_MASK                 (0xFU)
#define LPI2C_PARAM_MTXFIFO_SHIFT                (0U)
#define LPI2C_PARAM_MTXFIFO_WIDTH                (4U)
#define LPI2C_PARAM_MTXFIFO(x)                   (((uint32_t)(((uint32_t)(x)) << LPI2C_PARAM_MTXFIFO_SHIFT)) & LPI2C_PARAM_MTXFIFO_MASK)

#define LPI2C_PARAM_MRXFIFO_MASK                 (0xF00U)
#define LPI2C_PARAM_MRXFIFO_SHIFT                (8U)
#define LPI2C_PARAM_MRXFIFO_WIDTH                (4U)
#define LPI2C_PARAM_MRXFIFO(x)                   (((uint32_t)(((uint32_t)(x)) << LPI2C_PARAM_MRXFIFO_SHIFT)) & LPI2C_PARAM_MRXFIFO_MASK)
/*! @} */

/*! @name MCR - Master Control */
/*! @{ */

#define LPI2C_MCR_MEN_MASK                       (0x1U)
#define LPI2C_MCR_MEN_SHIFT                      (0U)
#define LPI2C_MCR_MEN_WIDTH                      (1U)
#define LPI2C_MCR_MEN(x)                         (((uint32_t)(((uint32_t)(x)) << LPI2C_MCR_MEN_SHIFT)) & LPI2C_MCR_MEN_MASK)

#define LPI2C_MCR_RST_MASK                       (0x2U)
#define LPI2C_MCR_RST_SHIFT                      (1U)
#define LPI2C_MCR_RST_WIDTH                      (1U)
#define LPI2C_MCR_RST(x)                         (((uint32_t)(((uint32_t)(x)) << LPI2C_MCR_RST_SHIFT)) & LPI2C_MCR_RST_MASK)

#define LPI2C_MCR_DOZEN_MASK                     (0x4U)
#define LPI2C_MCR_DOZEN_SHIFT                    (2U)
#define LPI2C_MCR_DOZEN_WIDTH                    (1U)
#define LPI2C_MCR_DOZEN(x)                       (((uint32_t)(((uint32_t)(x)) << LPI2C_MCR_DOZEN_SHIFT)) & LPI2C_MCR_DOZEN_MASK)

#define LPI2C_MCR_DBGEN_MASK                     (0x8U)
#define LPI2C_MCR_DBGEN_SHIFT                    (3U)
#define LPI2C_MCR_DBGEN_WIDTH                    (1U)
#define LPI2C_MCR_DBGEN(x)                       (((uint32_t)(((uint32_t)(x)) << LPI2C_MCR_DBGEN_SHIFT)) & LPI2C_MCR_DBGEN_MASK)

#define LPI2C_MCR_RTF_MASK                       (0x100U)
#define LPI2C_MCR_RTF_SHIFT                      (8U)
#define LPI2C_MCR_RTF_WIDTH                      (1U)
#define LPI2C_MCR_RTF(x)                         (((uint32_t)(((uint32_t)(x)) << LPI2C_MCR_RTF_SHIFT)) & LPI2C_MCR_RTF_MASK)

#define LPI2C_MCR_RRF_MASK                       (0x200U)
#define LPI2C_MCR_RRF_SHIFT                      (9U)
#define LPI2C_MCR_RRF_WIDTH                      (1U)
#define LPI2C_MCR_RRF(x)                         (((uint32_t)(((uint32_t)(x)) << LPI2C_MCR_RRF_SHIFT)) & LPI2C_MCR_RRF_MASK)
/*! @} */

/*! @name MSR - Master Status */
/*! @{ */

#define LPI2C_MSR_TDF_MASK                       (0x1U)
#define LPI2C_MSR_TDF_SHIFT                      (0U)
#define LPI2C_MSR_TDF_WIDTH                      (1U)
#define LPI2C_MSR_TDF(x)                         (((uint32_t)(((uint32_t)(x)) << LPI2C_MSR_TDF_SHIFT)) & LPI2C_MSR_TDF_MASK)

#define LPI2C_MSR_RDF_MASK                       (0x2U)
#define LPI2C_MSR_RDF_SHIFT                      (1U)
#define LPI2C_MSR_RDF_WIDTH                      (1U)
#define LPI2C_MSR_RDF(x)                         (((uint32_t)(((uint32_t)(x)) << LPI2C_MSR_RDF_SHIFT)) & LPI2C_MSR_RDF_MASK)

#define LPI2C_MSR_EPF_MASK                       (0x100U)
#define LPI2C_MSR_EPF_SHIFT                      (8U)
#define LPI2C_MSR_EPF_WIDTH                      (1U)
#define LPI2C_MSR_EPF(x)                         (((uint32_t)(((uint32_t)(x)) << LPI2C_MSR_EPF_SHIFT)) & LPI2C_MSR_EPF_MASK)

#define LPI2C_MSR_SDF_MASK                       (0x200U)
#define LPI2C_MSR_SDF_SHIFT                      (9U)
#define LPI2C_MSR_SDF_WIDTH                      (1U)
#define LPI2C_MSR_SDF(x)                         (((uint32_t)(((uint32_t)(x)) << LPI2C_MSR_SDF_SHIFT)) & LPI2C_MSR_SDF_MASK)

#define LPI2C_MSR_NDF_MASK                       (0x400U)
#define LPI2C_MSR_NDF_SHIFT                      (10U)
#define LPI2C_MSR_NDF_WIDTH                      (1U)
#define LPI2C_MSR_NDF(x)                         (((uint32_t)(((uint32_t)(x)) << LPI2C_MSR_NDF_SHIFT)) & LPI2C_MSR_NDF_MASK)

#define LPI2C_MSR_ALF_MASK                       (0x800U)
#define LPI2C_MSR_ALF_SHIFT                      (11U)
#define LPI2C_MSR_ALF_WIDTH                      (1U)
#define LPI2C_MSR_ALF(x)                         (((uint32_t)(((uint32_t)(x)) << LPI2C_MSR_ALF_SHIFT)) & LPI2C_MSR_ALF_MASK)

#define LPI2C_MSR_FEF_MASK                       (0x1000U)
#define LPI2C_MSR_FEF_SHIFT                      (12U)
#define LPI2C_MSR_FEF_WIDTH                      (1U)
#define LPI2C_MSR_FEF(x)                         (((uint32_t)(((uint32_t)(x)) << LPI2C_MSR_FEF_SHIFT)) & LPI2C_MSR_FEF_MASK)

#define LPI2C_MSR_PLTF_MASK                      (0x2000U)
#define LPI2C_MSR_PLTF_SHIFT                     (13U)
#define LPI2C_MSR_PLTF_WIDTH                     (1U)
#define LPI2C_MSR_PLTF(x)                        (((uint32_t)(((uint32_t)(x)) << LPI2C_MSR_PLTF_SHIFT)) & LPI2C_MSR_PLTF_MASK)

#define LPI2C_MSR_DMF_MASK                       (0x4000U)
#define LPI2C_MSR_DMF_SHIFT                      (14U)
#define LPI2C_MSR_DMF_WIDTH                      (1U)
#define LPI2C_MSR_DMF(x)                         (((uint32_t)(((uint32_t)(x)) << LPI2C_MSR_DMF_SHIFT)) & LPI2C_MSR_DMF_MASK)

#define LPI2C_MSR_MBF_MASK                       (0x1000000U)
#define LPI2C_MSR_MBF_SHIFT                      (24U)
#define LPI2C_MSR_MBF_WIDTH                      (1U)
#define LPI2C_MSR_MBF(x)                         (((uint32_t)(((uint32_t)(x)) << LPI2C_MSR_MBF_SHIFT)) & LPI2C_MSR_MBF_MASK)

#define LPI2C_MSR_BBF_MASK                       (0x2000000U)
#define LPI2C_MSR_BBF_SHIFT                      (25U)
#define LPI2C_MSR_BBF_WIDTH                      (1U)
#define LPI2C_MSR_BBF(x)                         (((uint32_t)(((uint32_t)(x)) << LPI2C_MSR_BBF_SHIFT)) & LPI2C_MSR_BBF_MASK)
/*! @} */

/*! @name MIER - Master Interrupt Enable */
/*! @{ */

#define LPI2C_MIER_TDIE_MASK                     (0x1U)
#define LPI2C_MIER_TDIE_SHIFT                    (0U)
#define LPI2C_MIER_TDIE_WIDTH                    (1U)
#define LPI2C_MIER_TDIE(x)                       (((uint32_t)(((uint32_t)(x)) << LPI2C_MIER_TDIE_SHIFT)) & LPI2C_MIER_TDIE_MASK)

#define LPI2C_MIER_RDIE_MASK                     (0x2U)
#define LPI2C_MIER_RDIE_SHIFT                    (1U)
#define LPI2C_MIER_RDIE_WIDTH                    (1U)
#define LPI2C_MIER_RDIE(x)                       (((uint32_t)(((uint32_t)(x)) << LPI2C_MIER_RDIE_SHIFT)) & LPI2C_MIER_RDIE_MASK)

#define LPI2C_MIER_EPIE_MASK                     (0x100U)
#define LPI2C_MIER_EPIE_SHIFT                    (8U)
#define LPI2C_MIER_EPIE_WIDTH                    (1U)
#define LPI2C_MIER_EPIE(x)                       (((uint32_t)(((uint32_t)(x)) << LPI2C_MIER_EPIE_SHIFT)) & LPI2C_MIER_EPIE_MASK)

#define LPI2C_MIER_SDIE_MASK                     (0x200U)
#define LPI2C_MIER_SDIE_SHIFT                    (9U)
#define LPI2C_MIER_SDIE_WIDTH                    (1U)
#define LPI2C_MIER_SDIE(x)                       (((uint32_t)(((uint32_t)(x)) << LPI2C_MIER_SDIE_SHIFT)) & LPI2C_MIER_SDIE_MASK)

#define LPI2C_MIER_NDIE_MASK                     (0x400U)
#define LPI2C_MIER_NDIE_SHIFT                    (10U)
#define LPI2C_MIER_NDIE_WIDTH                    (1U)
#define LPI2C_MIER_NDIE(x)                       (((uint32_t)(((uint32_t)(x)) << LPI2C_MIER_NDIE_SHIFT)) & LPI2C_MIER_NDIE_MASK)

#define LPI2C_MIER_ALIE_MASK                     (0x800U)
#define LPI2C_MIER_ALIE_SHIFT                    (11U)
#define LPI2C_MIER_ALIE_WIDTH                    (1U)
#define LPI2C_MIER_ALIE(x)                       (((uint32_t)(((uint32_t)(x)) << LPI2C_MIER_ALIE_SHIFT)) & LPI2C_MIER_ALIE_MASK)

#define LPI2C_MIER_FEIE_MASK                     (0x1000U)
#define LPI2C_MIER_FEIE_SHIFT                    (12U)
#define LPI2C_MIER_FEIE_WIDTH                    (1U)
#define LPI2C_MIER_FEIE(x)                       (((uint32_t)(((uint32_t)(x)) << LPI2C_MIER_FEIE_SHIFT)) & LPI2C_MIER_FEIE_MASK)

#define LPI2C_MIER_PLTIE_MASK                    (0x2000U)
#define LPI2C_MIER_PLTIE_SHIFT                   (13U)
#define LPI2C_MIER_PLTIE_WIDTH                   (1U)
#define LPI2C_MIER_PLTIE(x)                      (((uint32_t)(((uint32_t)(x)) << LPI2C_MIER_PLTIE_SHIFT)) & LPI2C_MIER_PLTIE_MASK)

#define LPI2C_MIER_DMIE_MASK                     (0x4000U)
#define LPI2C_MIER_DMIE_SHIFT                    (14U)
#define LPI2C_MIER_DMIE_WIDTH                    (1U)
#define LPI2C_MIER_DMIE(x)                       (((uint32_t)(((uint32_t)(x)) << LPI2C_MIER_DMIE_SHIFT)) & LPI2C_MIER_DMIE_MASK)
/*! @} */

/*! @name MDER - Master DMA Enable */
/*! @{ */

#define LPI2C_MDER_TDDE_MASK                     (0x1U)
#define LPI2C_MDER_TDDE_SHIFT                    (0U)
#define LPI2C_MDER_TDDE_WIDTH                    (1U)
#define LPI2C_MDER_TDDE(x)                       (((uint32_t)(((uint32_t)(x)) << LPI2C_MDER_TDDE_SHIFT)) & LPI2C_MDER_TDDE_MASK)

#define LPI2C_MDER_RDDE_MASK                     (0x2U)
#define LPI2C_MDER_RDDE_SHIFT                    (1U)
#define LPI2C_MDER_RDDE_WIDTH                    (1U)
#define LPI2C_MDER_RDDE(x)                       (((uint32_t)(((uint32_t)(x)) << LPI2C_MDER_RDDE_SHIFT)) & LPI2C_MDER_RDDE_MASK)
/*! @} */

/*! @name MCFGR0 - Master Configuration 0 */
/*! @{ */

#define LPI2C_MCFGR0_HREN_MASK                   (0x1U)
#define LPI2C_MCFGR0_HREN_SHIFT                  (0U)
#define LPI2C_MCFGR0_HREN_WIDTH                  (1U)
#define LPI2C_MCFGR0_HREN(x)                     (((uint32_t)(((uint32_t)(x)) << LPI2C_MCFGR0_HREN_SHIFT)) & LPI2C_MCFGR0_HREN_MASK)

#define LPI2C_MCFGR0_HRPOL_MASK                  (0x2U)
#define LPI2C_MCFGR0_HRPOL_SHIFT                 (1U)
#define LPI2C_MCFGR0_HRPOL_WIDTH                 (1U)
#define LPI2C_MCFGR0_HRPOL(x)                    (((uint32_t)(((uint32_t)(x)) << LPI2C_MCFGR0_HRPOL_SHIFT)) & LPI2C_MCFGR0_HRPOL_MASK)

#define LPI2C_MCFGR0_HRSEL_MASK                  (0x4U)
#define LPI2C_MCFGR0_HRSEL_SHIFT                 (2U)
#define LPI2C_MCFGR0_HRSEL_WIDTH                 (1U)
#define LPI2C_MCFGR0_HRSEL(x)                    (((uint32_t)(((uint32_t)(x)) << LPI2C_MCFGR0_HRSEL_SHIFT)) & LPI2C_MCFGR0_HRSEL_MASK)

#define LPI2C_MCFGR0_CIRFIFO_MASK                (0x100U)
#define LPI2C_MCFGR0_CIRFIFO_SHIFT               (8U)
#define LPI2C_MCFGR0_CIRFIFO_WIDTH               (1U)
#define LPI2C_MCFGR0_CIRFIFO(x)                  (((uint32_t)(((uint32_t)(x)) << LPI2C_MCFGR0_CIRFIFO_SHIFT)) & LPI2C_MCFGR0_CIRFIFO_MASK)

#define LPI2C_MCFGR0_RDMO_MASK                   (0x200U)
#define LPI2C_MCFGR0_RDMO_SHIFT                  (9U)
#define LPI2C_MCFGR0_RDMO_WIDTH                  (1U)
#define LPI2C_MCFGR0_RDMO(x)                     (((uint32_t)(((uint32_t)(x)) << LPI2C_MCFGR0_RDMO_SHIFT)) & LPI2C_MCFGR0_RDMO_MASK)
/*! @} */

/*! @name MCFGR1 - Master Configuration 1 */
/*! @{ */

#define LPI2C_MCFGR1_PRESCALE_MASK               (0x7U)
#define LPI2C_MCFGR1_PRESCALE_SHIFT              (0U)
#define LPI2C_MCFGR1_PRESCALE_WIDTH              (3U)
#define LPI2C_MCFGR1_PRESCALE(x)                 (((uint32_t)(((uint32_t)(x)) << LPI2C_MCFGR1_PRESCALE_SHIFT)) & LPI2C_MCFGR1_PRESCALE_MASK)

#define LPI2C_MCFGR1_AUTOSTOP_MASK               (0x100U)
#define LPI2C_MCFGR1_AUTOSTOP_SHIFT              (8U)
#define LPI2C_MCFGR1_AUTOSTOP_WIDTH              (1U)
#define LPI2C_MCFGR1_AUTOSTOP(x)                 (((uint32_t)(((uint32_t)(x)) << LPI2C_MCFGR1_AUTOSTOP_SHIFT)) & LPI2C_MCFGR1_AUTOSTOP_MASK)

#define LPI2C_MCFGR1_IGNACK_MASK                 (0x200U)
#define LPI2C_MCFGR1_IGNACK_SHIFT                (9U)
#define LPI2C_MCFGR1_IGNACK_WIDTH                (1U)
#define LPI2C_MCFGR1_IGNACK(x)                   (((uint32_t)(((uint32_t)(x)) << LPI2C_MCFGR1_IGNACK_SHIFT)) & LPI2C_MCFGR1_IGNACK_MASK)

#define LPI2C_MCFGR1_TIMECFG_MASK                (0x400U)
#define LPI2C_MCFGR1_TIMECFG_SHIFT               (10U)
#define LPI2C_MCFGR1_TIMECFG_WIDTH               (1U)
#define LPI2C_MCFGR1_TIMECFG(x)                  (((uint32_t)(((uint32_t)(x)) << LPI2C_MCFGR1_TIMECFG_SHIFT)) & LPI2C_MCFGR1_TIMECFG_MASK)

#define LPI2C_MCFGR1_MATCFG_MASK                 (0x70000U)
#define LPI2C_MCFGR1_MATCFG_SHIFT                (16U)
#define LPI2C_MCFGR1_MATCFG_WIDTH                (3U)
#define LPI2C_MCFGR1_MATCFG(x)                   (((uint32_t)(((uint32_t)(x)) << LPI2C_MCFGR1_MATCFG_SHIFT)) & LPI2C_MCFGR1_MATCFG_MASK)

#define LPI2C_MCFGR1_PINCFG_MASK                 (0x7000000U)
#define LPI2C_MCFGR1_PINCFG_SHIFT                (24U)
#define LPI2C_MCFGR1_PINCFG_WIDTH                (3U)
#define LPI2C_MCFGR1_PINCFG(x)                   (((uint32_t)(((uint32_t)(x)) << LPI2C_MCFGR1_PINCFG_SHIFT)) & LPI2C_MCFGR1_PINCFG_MASK)

#define LPI2C_MCFGR1_FRCHS_MASK                  (0x8000000U)
#define LPI2C_MCFGR1_FRCHS_SHIFT                 (27U)
#define LPI2C_MCFGR1_FRCHS_WIDTH                 (1U)
#define LPI2C_MCFGR1_FRCHS(x)                    (((uint32_t)(((uint32_t)(x)) << LPI2C_MCFGR1_FRCHS_SHIFT)) & LPI2C_MCFGR1_FRCHS_MASK)
/*! @} */

/*! @name MCFGR2 - Master Configuration 2 */
/*! @{ */

#define LPI2C_MCFGR2_BUSIDLE_MASK                (0xFFFU)
#define LPI2C_MCFGR2_BUSIDLE_SHIFT               (0U)
#define LPI2C_MCFGR2_BUSIDLE_WIDTH               (12U)
#define LPI2C_MCFGR2_BUSIDLE(x)                  (((uint32_t)(((uint32_t)(x)) << LPI2C_MCFGR2_BUSIDLE_SHIFT)) & LPI2C_MCFGR2_BUSIDLE_MASK)

#define LPI2C_MCFGR2_FILTSCL_MASK                (0xF0000U)
#define LPI2C_MCFGR2_FILTSCL_SHIFT               (16U)
#define LPI2C_MCFGR2_FILTSCL_WIDTH               (4U)
#define LPI2C_MCFGR2_FILTSCL(x)                  (((uint32_t)(((uint32_t)(x)) << LPI2C_MCFGR2_FILTSCL_SHIFT)) & LPI2C_MCFGR2_FILTSCL_MASK)

#define LPI2C_MCFGR2_FILTSDA_MASK                (0xF000000U)
#define LPI2C_MCFGR2_FILTSDA_SHIFT               (24U)
#define LPI2C_MCFGR2_FILTSDA_WIDTH               (4U)
#define LPI2C_MCFGR2_FILTSDA(x)                  (((uint32_t)(((uint32_t)(x)) << LPI2C_MCFGR2_FILTSDA_SHIFT)) & LPI2C_MCFGR2_FILTSDA_MASK)
/*! @} */

/*! @name MCFGR3 - Master Configuration 3 */
/*! @{ */

#define LPI2C_MCFGR3_PINLOW_MASK                 (0xFFF00U)
#define LPI2C_MCFGR3_PINLOW_SHIFT                (8U)
#define LPI2C_MCFGR3_PINLOW_WIDTH                (12U)
#define LPI2C_MCFGR3_PINLOW(x)                   (((uint32_t)(((uint32_t)(x)) << LPI2C_MCFGR3_PINLOW_SHIFT)) & LPI2C_MCFGR3_PINLOW_MASK)
/*! @} */

/*! @name MDMR - Master Data Match */
/*! @{ */

#define LPI2C_MDMR_MATCH0_MASK                   (0xFFU)
#define LPI2C_MDMR_MATCH0_SHIFT                  (0U)
#define LPI2C_MDMR_MATCH0_WIDTH                  (8U)
#define LPI2C_MDMR_MATCH0(x)                     (((uint32_t)(((uint32_t)(x)) << LPI2C_MDMR_MATCH0_SHIFT)) & LPI2C_MDMR_MATCH0_MASK)

#define LPI2C_MDMR_MATCH1_MASK                   (0xFF0000U)
#define LPI2C_MDMR_MATCH1_SHIFT                  (16U)
#define LPI2C_MDMR_MATCH1_WIDTH                  (8U)
#define LPI2C_MDMR_MATCH1(x)                     (((uint32_t)(((uint32_t)(x)) << LPI2C_MDMR_MATCH1_SHIFT)) & LPI2C_MDMR_MATCH1_MASK)
/*! @} */

/*! @name MCCR0 - Master Clock Configuration 0 */
/*! @{ */

#define LPI2C_MCCR0_CLKLO_MASK                   (0x3FU)
#define LPI2C_MCCR0_CLKLO_SHIFT                  (0U)
#define LPI2C_MCCR0_CLKLO_WIDTH                  (6U)
#define LPI2C_MCCR0_CLKLO(x)                     (((uint32_t)(((uint32_t)(x)) << LPI2C_MCCR0_CLKLO_SHIFT)) & LPI2C_MCCR0_CLKLO_MASK)

#define LPI2C_MCCR0_CLKHI_MASK                   (0x3F00U)
#define LPI2C_MCCR0_CLKHI_SHIFT                  (8U)
#define LPI2C_MCCR0_CLKHI_WIDTH                  (6U)
#define LPI2C_MCCR0_CLKHI(x)                     (((uint32_t)(((uint32_t)(x)) << LPI2C_MCCR0_CLKHI_SHIFT)) & LPI2C_MCCR0_CLKHI_MASK)

#define LPI2C_MCCR0_SETHOLD_MASK                 (0x3F0000U)
#define LPI2C_MCCR0_SETHOLD_SHIFT                (16U)
#define LPI2C_MCCR0_SETHOLD_WIDTH                (6U)
#define LPI2C_MCCR0_SETHOLD(x)                   (((uint32_t)(((uint32_t)(x)) << LPI2C_MCCR0_SETHOLD_SHIFT)) & LPI2C_MCCR0_SETHOLD_MASK)

#define LPI2C_MCCR0_DATAVD_MASK                  (0x3F000000U)
#define LPI2C_MCCR0_DATAVD_SHIFT                 (24U)
#define LPI2C_MCCR0_DATAVD_WIDTH                 (6U)
#define LPI2C_MCCR0_DATAVD(x)                    (((uint32_t)(((uint32_t)(x)) << LPI2C_MCCR0_DATAVD_SHIFT)) & LPI2C_MCCR0_DATAVD_MASK)
/*! @} */

/*! @name MCCR1 - Master Clock Configuration 1 */
/*! @{ */

#define LPI2C_MCCR1_CLKLO_MASK                   (0x3FU)
#define LPI2C_MCCR1_CLKLO_SHIFT                  (0U)
#define LPI2C_MCCR1_CLKLO_WIDTH                  (6U)
#define LPI2C_MCCR1_CLKLO(x)                     (((uint32_t)(((uint32_t)(x)) << LPI2C_MCCR1_CLKLO_SHIFT)) & LPI2C_MCCR1_CLKLO_MASK)

#define LPI2C_MCCR1_CLKHI_MASK                   (0x3F00U)
#define LPI2C_MCCR1_CLKHI_SHIFT                  (8U)
#define LPI2C_MCCR1_CLKHI_WIDTH                  (6U)
#define LPI2C_MCCR1_CLKHI(x)                     (((uint32_t)(((uint32_t)(x)) << LPI2C_MCCR1_CLKHI_SHIFT)) & LPI2C_MCCR1_CLKHI_MASK)

#define LPI2C_MCCR1_SETHOLD_MASK                 (0x3F0000U)
#define LPI2C_MCCR1_SETHOLD_SHIFT                (16U)
#define LPI2C_MCCR1_SETHOLD_WIDTH                (6U)
#define LPI2C_MCCR1_SETHOLD(x)                   (((uint32_t)(((uint32_t)(x)) << LPI2C_MCCR1_SETHOLD_SHIFT)) & LPI2C_MCCR1_SETHOLD_MASK)

#define LPI2C_MCCR1_DATAVD_MASK                  (0x3F000000U)
#define LPI2C_MCCR1_DATAVD_SHIFT                 (24U)
#define LPI2C_MCCR1_DATAVD_WIDTH                 (6U)
#define LPI2C_MCCR1_DATAVD(x)                    (((uint32_t)(((uint32_t)(x)) << LPI2C_MCCR1_DATAVD_SHIFT)) & LPI2C_MCCR1_DATAVD_MASK)
/*! @} */

/*! @name MFCR - Master FIFO Control */
/*! @{ */

#define LPI2C_MFCR_TXWATER_MASK                  (0x3U)
#define LPI2C_MFCR_TXWATER_SHIFT                 (0U)
#define LPI2C_MFCR_TXWATER_WIDTH                 (2U)
#define LPI2C_MFCR_TXWATER(x)                    (((uint32_t)(((uint32_t)(x)) << LPI2C_MFCR_TXWATER_SHIFT)) & LPI2C_MFCR_TXWATER_MASK)

#define LPI2C_MFCR_RXWATER_MASK                  (0x30000U)
#define LPI2C_MFCR_RXWATER_SHIFT                 (16U)
#define LPI2C_MFCR_RXWATER_WIDTH                 (2U)
#define LPI2C_MFCR_RXWATER(x)                    (((uint32_t)(((uint32_t)(x)) << LPI2C_MFCR_RXWATER_SHIFT)) & LPI2C_MFCR_RXWATER_MASK)
/*! @} */

/*! @name MFSR - Master FIFO Status */
/*! @{ */

#define LPI2C_MFSR_TXCOUNT_MASK                  (0x7U)
#define LPI2C_MFSR_TXCOUNT_SHIFT                 (0U)
#define LPI2C_MFSR_TXCOUNT_WIDTH                 (3U)
#define LPI2C_MFSR_TXCOUNT(x)                    (((uint32_t)(((uint32_t)(x)) << LPI2C_MFSR_TXCOUNT_SHIFT)) & LPI2C_MFSR_TXCOUNT_MASK)

#define LPI2C_MFSR_RXCOUNT_MASK                  (0x70000U)
#define LPI2C_MFSR_RXCOUNT_SHIFT                 (16U)
#define LPI2C_MFSR_RXCOUNT_WIDTH                 (3U)
#define LPI2C_MFSR_RXCOUNT(x)                    (((uint32_t)(((uint32_t)(x)) << LPI2C_MFSR_RXCOUNT_SHIFT)) & LPI2C_MFSR_RXCOUNT_MASK)
/*! @} */

/*! @name MTDR - Master Transmit Data */
/*! @{ */

#define LPI2C_MTDR_DATA_MASK                     (0xFFU)
#define LPI2C_MTDR_DATA_SHIFT                    (0U)
#define LPI2C_MTDR_DATA_WIDTH                    (8U)
#define LPI2C_MTDR_DATA(x)                       (((uint32_t)(((uint32_t)(x)) << LPI2C_MTDR_DATA_SHIFT)) & LPI2C_MTDR_DATA_MASK)

#define LPI2C_MTDR_CMD_MASK                      (0x700U)
#define LPI2C_MTDR_CMD_SHIFT                     (8U)
#define LPI2C_MTDR_CMD_WIDTH                     (3U)
#define LPI2C_MTDR_CMD(x)                        (((uint32_t)(((uint32_t)(x)) << LPI2C_MTDR_CMD_SHIFT)) & LPI2C_MTDR_CMD_MASK)
/*! @} */

/*! @name MRDR - Master Receive Data */
/*! @{ */

#define LPI2C_MRDR_DATA_MASK                     (0xFFU)
#define LPI2C_MRDR_DATA_SHIFT                    (0U)
#define LPI2C_MRDR_DATA_WIDTH                    (8U)
#define LPI2C_MRDR_DATA(x)                       (((uint32_t)(((uint32_t)(x)) << LPI2C_MRDR_DATA_SHIFT)) & LPI2C_MRDR_DATA_MASK)

#define LPI2C_MRDR_RXEMPTY_MASK                  (0x4000U)
#define LPI2C_MRDR_RXEMPTY_SHIFT                 (14U)
#define LPI2C_MRDR_RXEMPTY_WIDTH                 (1U)
#define LPI2C_MRDR_RXEMPTY(x)                    (((uint32_t)(((uint32_t)(x)) << LPI2C_MRDR_RXEMPTY_SHIFT)) & LPI2C_MRDR_RXEMPTY_MASK)
/*! @} */

/*! @name SCR - Slave Control */
/*! @{ */

#define LPI2C_SCR_SEN_MASK                       (0x1U)
#define LPI2C_SCR_SEN_SHIFT                      (0U)
#define LPI2C_SCR_SEN_WIDTH                      (1U)
#define LPI2C_SCR_SEN(x)                         (((uint32_t)(((uint32_t)(x)) << LPI2C_SCR_SEN_SHIFT)) & LPI2C_SCR_SEN_MASK)

#define LPI2C_SCR_RST_MASK                       (0x2U)
#define LPI2C_SCR_RST_SHIFT                      (1U)
#define LPI2C_SCR_RST_WIDTH                      (1U)
#define LPI2C_SCR_RST(x)                         (((uint32_t)(((uint32_t)(x)) << LPI2C_SCR_RST_SHIFT)) & LPI2C_SCR_RST_MASK)

#define LPI2C_SCR_FILTEN_MASK                    (0x10U)
#define LPI2C_SCR_FILTEN_SHIFT                   (4U)
#define LPI2C_SCR_FILTEN_WIDTH                   (1U)
#define LPI2C_SCR_FILTEN(x)                      (((uint32_t)(((uint32_t)(x)) << LPI2C_SCR_FILTEN_SHIFT)) & LPI2C_SCR_FILTEN_MASK)

#define LPI2C_SCR_FILTDZ_MASK                    (0x20U)
#define LPI2C_SCR_FILTDZ_SHIFT                   (5U)
#define LPI2C_SCR_FILTDZ_WIDTH                   (1U)
#define LPI2C_SCR_FILTDZ(x)                      (((uint32_t)(((uint32_t)(x)) << LPI2C_SCR_FILTDZ_SHIFT)) & LPI2C_SCR_FILTDZ_MASK)

#define LPI2C_SCR_RTF_MASK                       (0x100U)
#define LPI2C_SCR_RTF_SHIFT                      (8U)
#define LPI2C_SCR_RTF_WIDTH                      (1U)
#define LPI2C_SCR_RTF(x)                         (((uint32_t)(((uint32_t)(x)) << LPI2C_SCR_RTF_SHIFT)) & LPI2C_SCR_RTF_MASK)

#define LPI2C_SCR_RRF_MASK                       (0x200U)
#define LPI2C_SCR_RRF_SHIFT                      (9U)
#define LPI2C_SCR_RRF_WIDTH                      (1U)
#define LPI2C_SCR_RRF(x)                         (((uint32_t)(((uint32_t)(x)) << LPI2C_SCR_RRF_SHIFT)) & LPI2C_SCR_RRF_MASK)
/*! @} */

/*! @name SSR - Slave Status */
/*! @{ */

#define LPI2C_SSR_TDF_MASK                       (0x1U)
#define LPI2C_SSR_TDF_SHIFT                      (0U)
#define LPI2C_SSR_TDF_WIDTH                      (1U)
#define LPI2C_SSR_TDF(x)                         (((uint32_t)(((uint32_t)(x)) << LPI2C_SSR_TDF_SHIFT)) & LPI2C_SSR_TDF_MASK)

#define LPI2C_SSR_RDF_MASK                       (0x2U)
#define LPI2C_SSR_RDF_SHIFT                      (1U)
#define LPI2C_SSR_RDF_WIDTH                      (1U)
#define LPI2C_SSR_RDF(x)                         (((uint32_t)(((uint32_t)(x)) << LPI2C_SSR_RDF_SHIFT)) & LPI2C_SSR_RDF_MASK)

#define LPI2C_SSR_AVF_MASK                       (0x4U)
#define LPI2C_SSR_AVF_SHIFT                      (2U)
#define LPI2C_SSR_AVF_WIDTH                      (1U)
#define LPI2C_SSR_AVF(x)                         (((uint32_t)(((uint32_t)(x)) << LPI2C_SSR_AVF_SHIFT)) & LPI2C_SSR_AVF_MASK)

#define LPI2C_SSR_TAF_MASK                       (0x8U)
#define LPI2C_SSR_TAF_SHIFT                      (3U)
#define LPI2C_SSR_TAF_WIDTH                      (1U)
#define LPI2C_SSR_TAF(x)                         (((uint32_t)(((uint32_t)(x)) << LPI2C_SSR_TAF_SHIFT)) & LPI2C_SSR_TAF_MASK)

#define LPI2C_SSR_RSF_MASK                       (0x100U)
#define LPI2C_SSR_RSF_SHIFT                      (8U)
#define LPI2C_SSR_RSF_WIDTH                      (1U)
#define LPI2C_SSR_RSF(x)                         (((uint32_t)(((uint32_t)(x)) << LPI2C_SSR_RSF_SHIFT)) & LPI2C_SSR_RSF_MASK)

#define LPI2C_SSR_SDF_MASK                       (0x200U)
#define LPI2C_SSR_SDF_SHIFT                      (9U)
#define LPI2C_SSR_SDF_WIDTH                      (1U)
#define LPI2C_SSR_SDF(x)                         (((uint32_t)(((uint32_t)(x)) << LPI2C_SSR_SDF_SHIFT)) & LPI2C_SSR_SDF_MASK)

#define LPI2C_SSR_BEF_MASK                       (0x400U)
#define LPI2C_SSR_BEF_SHIFT                      (10U)
#define LPI2C_SSR_BEF_WIDTH                      (1U)
#define LPI2C_SSR_BEF(x)                         (((uint32_t)(((uint32_t)(x)) << LPI2C_SSR_BEF_SHIFT)) & LPI2C_SSR_BEF_MASK)

#define LPI2C_SSR_FEF_MASK                       (0x800U)
#define LPI2C_SSR_FEF_SHIFT                      (11U)
#define LPI2C_SSR_FEF_WIDTH                      (1U)
#define LPI2C_SSR_FEF(x)                         (((uint32_t)(((uint32_t)(x)) << LPI2C_SSR_FEF_SHIFT)) & LPI2C_SSR_FEF_MASK)

#define LPI2C_SSR_AM0F_MASK                      (0x1000U)
#define LPI2C_SSR_AM0F_SHIFT                     (12U)
#define LPI2C_SSR_AM0F_WIDTH                     (1U)
#define LPI2C_SSR_AM0F(x)                        (((uint32_t)(((uint32_t)(x)) << LPI2C_SSR_AM0F_SHIFT)) & LPI2C_SSR_AM0F_MASK)

#define LPI2C_SSR_AM1F_MASK                      (0x2000U)
#define LPI2C_SSR_AM1F_SHIFT                     (13U)
#define LPI2C_SSR_AM1F_WIDTH                     (1U)
#define LPI2C_SSR_AM1F(x)                        (((uint32_t)(((uint32_t)(x)) << LPI2C_SSR_AM1F_SHIFT)) & LPI2C_SSR_AM1F_MASK)

#define LPI2C_SSR_GCF_MASK                       (0x4000U)
#define LPI2C_SSR_GCF_SHIFT                      (14U)
#define LPI2C_SSR_GCF_WIDTH                      (1U)
#define LPI2C_SSR_GCF(x)                         (((uint32_t)(((uint32_t)(x)) << LPI2C_SSR_GCF_SHIFT)) & LPI2C_SSR_GCF_MASK)

#define LPI2C_SSR_SARF_MASK                      (0x8000U)
#define LPI2C_SSR_SARF_SHIFT                     (15U)
#define LPI2C_SSR_SARF_WIDTH                     (1U)
#define LPI2C_SSR_SARF(x)                        (((uint32_t)(((uint32_t)(x)) << LPI2C_SSR_SARF_SHIFT)) & LPI2C_SSR_SARF_MASK)

#define LPI2C_SSR_SBF_MASK                       (0x1000000U)
#define LPI2C_SSR_SBF_SHIFT                      (24U)
#define LPI2C_SSR_SBF_WIDTH                      (1U)
#define LPI2C_SSR_SBF(x)                         (((uint32_t)(((uint32_t)(x)) << LPI2C_SSR_SBF_SHIFT)) & LPI2C_SSR_SBF_MASK)

#define LPI2C_SSR_BBF_MASK                       (0x2000000U)
#define LPI2C_SSR_BBF_SHIFT                      (25U)
#define LPI2C_SSR_BBF_WIDTH                      (1U)
#define LPI2C_SSR_BBF(x)                         (((uint32_t)(((uint32_t)(x)) << LPI2C_SSR_BBF_SHIFT)) & LPI2C_SSR_BBF_MASK)
/*! @} */

/*! @name SIER - Slave Interrupt Enable */
/*! @{ */

#define LPI2C_SIER_TDIE_MASK                     (0x1U)
#define LPI2C_SIER_TDIE_SHIFT                    (0U)
#define LPI2C_SIER_TDIE_WIDTH                    (1U)
#define LPI2C_SIER_TDIE(x)                       (((uint32_t)(((uint32_t)(x)) << LPI2C_SIER_TDIE_SHIFT)) & LPI2C_SIER_TDIE_MASK)

#define LPI2C_SIER_RDIE_MASK                     (0x2U)
#define LPI2C_SIER_RDIE_SHIFT                    (1U)
#define LPI2C_SIER_RDIE_WIDTH                    (1U)
#define LPI2C_SIER_RDIE(x)                       (((uint32_t)(((uint32_t)(x)) << LPI2C_SIER_RDIE_SHIFT)) & LPI2C_SIER_RDIE_MASK)

#define LPI2C_SIER_AVIE_MASK                     (0x4U)
#define LPI2C_SIER_AVIE_SHIFT                    (2U)
#define LPI2C_SIER_AVIE_WIDTH                    (1U)
#define LPI2C_SIER_AVIE(x)                       (((uint32_t)(((uint32_t)(x)) << LPI2C_SIER_AVIE_SHIFT)) & LPI2C_SIER_AVIE_MASK)

#define LPI2C_SIER_TAIE_MASK                     (0x8U)
#define LPI2C_SIER_TAIE_SHIFT                    (3U)
#define LPI2C_SIER_TAIE_WIDTH                    (1U)
#define LPI2C_SIER_TAIE(x)                       (((uint32_t)(((uint32_t)(x)) << LPI2C_SIER_TAIE_SHIFT)) & LPI2C_SIER_TAIE_MASK)

#define LPI2C_SIER_RSIE_MASK                     (0x100U)
#define LPI2C_SIER_RSIE_SHIFT                    (8U)
#define LPI2C_SIER_RSIE_WIDTH                    (1U)
#define LPI2C_SIER_RSIE(x)                       (((uint32_t)(((uint32_t)(x)) << LPI2C_SIER_RSIE_SHIFT)) & LPI2C_SIER_RSIE_MASK)

#define LPI2C_SIER_SDIE_MASK                     (0x200U)
#define LPI2C_SIER_SDIE_SHIFT                    (9U)
#define LPI2C_SIER_SDIE_WIDTH                    (1U)
#define LPI2C_SIER_SDIE(x)                       (((uint32_t)(((uint32_t)(x)) << LPI2C_SIER_SDIE_SHIFT)) & LPI2C_SIER_SDIE_MASK)

#define LPI2C_SIER_BEIE_MASK                     (0x400U)
#define LPI2C_SIER_BEIE_SHIFT                    (10U)
#define LPI2C_SIER_BEIE_WIDTH                    (1U)
#define LPI2C_SIER_BEIE(x)                       (((uint32_t)(((uint32_t)(x)) << LPI2C_SIER_BEIE_SHIFT)) & LPI2C_SIER_BEIE_MASK)

#define LPI2C_SIER_FEIE_MASK                     (0x800U)
#define LPI2C_SIER_FEIE_SHIFT                    (11U)
#define LPI2C_SIER_FEIE_WIDTH                    (1U)
#define LPI2C_SIER_FEIE(x)                       (((uint32_t)(((uint32_t)(x)) << LPI2C_SIER_FEIE_SHIFT)) & LPI2C_SIER_FEIE_MASK)

#define LPI2C_SIER_AM0IE_MASK                    (0x1000U)
#define LPI2C_SIER_AM0IE_SHIFT                   (12U)
#define LPI2C_SIER_AM0IE_WIDTH                   (1U)
#define LPI2C_SIER_AM0IE(x)                      (((uint32_t)(((uint32_t)(x)) << LPI2C_SIER_AM0IE_SHIFT)) & LPI2C_SIER_AM0IE_MASK)

#define LPI2C_SIER_AM1IE_MASK                    (0x2000U)
#define LPI2C_SIER_AM1IE_SHIFT                   (13U)
#define LPI2C_SIER_AM1IE_WIDTH                   (1U)
#define LPI2C_SIER_AM1IE(x)                      (((uint32_t)(((uint32_t)(x)) << LPI2C_SIER_AM1IE_SHIFT)) & LPI2C_SIER_AM1IE_MASK)

#define LPI2C_SIER_GCIE_MASK                     (0x4000U)
#define LPI2C_SIER_GCIE_SHIFT                    (14U)
#define LPI2C_SIER_GCIE_WIDTH                    (1U)
#define LPI2C_SIER_GCIE(x)                       (((uint32_t)(((uint32_t)(x)) << LPI2C_SIER_GCIE_SHIFT)) & LPI2C_SIER_GCIE_MASK)

#define LPI2C_SIER_SARIE_MASK                    (0x8000U)
#define LPI2C_SIER_SARIE_SHIFT                   (15U)
#define LPI2C_SIER_SARIE_WIDTH                   (1U)
#define LPI2C_SIER_SARIE(x)                      (((uint32_t)(((uint32_t)(x)) << LPI2C_SIER_SARIE_SHIFT)) & LPI2C_SIER_SARIE_MASK)
/*! @} */

/*! @name SDER - Slave DMA Enable */
/*! @{ */

#define LPI2C_SDER_TDDE_MASK                     (0x1U)
#define LPI2C_SDER_TDDE_SHIFT                    (0U)
#define LPI2C_SDER_TDDE_WIDTH                    (1U)
#define LPI2C_SDER_TDDE(x)                       (((uint32_t)(((uint32_t)(x)) << LPI2C_SDER_TDDE_SHIFT)) & LPI2C_SDER_TDDE_MASK)

#define LPI2C_SDER_RDDE_MASK                     (0x2U)
#define LPI2C_SDER_RDDE_SHIFT                    (1U)
#define LPI2C_SDER_RDDE_WIDTH                    (1U)
#define LPI2C_SDER_RDDE(x)                       (((uint32_t)(((uint32_t)(x)) << LPI2C_SDER_RDDE_SHIFT)) & LPI2C_SDER_RDDE_MASK)

#define LPI2C_SDER_AVDE_MASK                     (0x4U)
#define LPI2C_SDER_AVDE_SHIFT                    (2U)
#define LPI2C_SDER_AVDE_WIDTH                    (1U)
#define LPI2C_SDER_AVDE(x)                       (((uint32_t)(((uint32_t)(x)) << LPI2C_SDER_AVDE_SHIFT)) & LPI2C_SDER_AVDE_MASK)
/*! @} */

/*! @name SCFGR1 - Slave Configuration 1 */
/*! @{ */

#define LPI2C_SCFGR1_ADRSTALL_MASK               (0x1U)
#define LPI2C_SCFGR1_ADRSTALL_SHIFT              (0U)
#define LPI2C_SCFGR1_ADRSTALL_WIDTH              (1U)
#define LPI2C_SCFGR1_ADRSTALL(x)                 (((uint32_t)(((uint32_t)(x)) << LPI2C_SCFGR1_ADRSTALL_SHIFT)) & LPI2C_SCFGR1_ADRSTALL_MASK)

#define LPI2C_SCFGR1_RXSTALL_MASK                (0x2U)
#define LPI2C_SCFGR1_RXSTALL_SHIFT               (1U)
#define LPI2C_SCFGR1_RXSTALL_WIDTH               (1U)
#define LPI2C_SCFGR1_RXSTALL(x)                  (((uint32_t)(((uint32_t)(x)) << LPI2C_SCFGR1_RXSTALL_SHIFT)) & LPI2C_SCFGR1_RXSTALL_MASK)

#define LPI2C_SCFGR1_TXDSTALL_MASK               (0x4U)
#define LPI2C_SCFGR1_TXDSTALL_SHIFT              (2U)
#define LPI2C_SCFGR1_TXDSTALL_WIDTH              (1U)
#define LPI2C_SCFGR1_TXDSTALL(x)                 (((uint32_t)(((uint32_t)(x)) << LPI2C_SCFGR1_TXDSTALL_SHIFT)) & LPI2C_SCFGR1_TXDSTALL_MASK)

#define LPI2C_SCFGR1_ACKSTALL_MASK               (0x8U)
#define LPI2C_SCFGR1_ACKSTALL_SHIFT              (3U)
#define LPI2C_SCFGR1_ACKSTALL_WIDTH              (1U)
#define LPI2C_SCFGR1_ACKSTALL(x)                 (((uint32_t)(((uint32_t)(x)) << LPI2C_SCFGR1_ACKSTALL_SHIFT)) & LPI2C_SCFGR1_ACKSTALL_MASK)

#define LPI2C_SCFGR1_GCEN_MASK                   (0x100U)
#define LPI2C_SCFGR1_GCEN_SHIFT                  (8U)
#define LPI2C_SCFGR1_GCEN_WIDTH                  (1U)
#define LPI2C_SCFGR1_GCEN(x)                     (((uint32_t)(((uint32_t)(x)) << LPI2C_SCFGR1_GCEN_SHIFT)) & LPI2C_SCFGR1_GCEN_MASK)

#define LPI2C_SCFGR1_SAEN_MASK                   (0x200U)
#define LPI2C_SCFGR1_SAEN_SHIFT                  (9U)
#define LPI2C_SCFGR1_SAEN_WIDTH                  (1U)
#define LPI2C_SCFGR1_SAEN(x)                     (((uint32_t)(((uint32_t)(x)) << LPI2C_SCFGR1_SAEN_SHIFT)) & LPI2C_SCFGR1_SAEN_MASK)

#define LPI2C_SCFGR1_TXCFG_MASK                  (0x400U)
#define LPI2C_SCFGR1_TXCFG_SHIFT                 (10U)
#define LPI2C_SCFGR1_TXCFG_WIDTH                 (1U)
#define LPI2C_SCFGR1_TXCFG(x)                    (((uint32_t)(((uint32_t)(x)) << LPI2C_SCFGR1_TXCFG_SHIFT)) & LPI2C_SCFGR1_TXCFG_MASK)

#define LPI2C_SCFGR1_RXCFG_MASK                  (0x800U)
#define LPI2C_SCFGR1_RXCFG_SHIFT                 (11U)
#define LPI2C_SCFGR1_RXCFG_WIDTH                 (1U)
#define LPI2C_SCFGR1_RXCFG(x)                    (((uint32_t)(((uint32_t)(x)) << LPI2C_SCFGR1_RXCFG_SHIFT)) & LPI2C_SCFGR1_RXCFG_MASK)

#define LPI2C_SCFGR1_IGNACK_MASK                 (0x1000U)
#define LPI2C_SCFGR1_IGNACK_SHIFT                (12U)
#define LPI2C_SCFGR1_IGNACK_WIDTH                (1U)
#define LPI2C_SCFGR1_IGNACK(x)                   (((uint32_t)(((uint32_t)(x)) << LPI2C_SCFGR1_IGNACK_SHIFT)) & LPI2C_SCFGR1_IGNACK_MASK)

#define LPI2C_SCFGR1_HSMEN_MASK                  (0x2000U)
#define LPI2C_SCFGR1_HSMEN_SHIFT                 (13U)
#define LPI2C_SCFGR1_HSMEN_WIDTH                 (1U)
#define LPI2C_SCFGR1_HSMEN(x)                    (((uint32_t)(((uint32_t)(x)) << LPI2C_SCFGR1_HSMEN_SHIFT)) & LPI2C_SCFGR1_HSMEN_MASK)

#define LPI2C_SCFGR1_ADDRCFG_MASK                (0x70000U)
#define LPI2C_SCFGR1_ADDRCFG_SHIFT               (16U)
#define LPI2C_SCFGR1_ADDRCFG_WIDTH               (3U)
#define LPI2C_SCFGR1_ADDRCFG(x)                  (((uint32_t)(((uint32_t)(x)) << LPI2C_SCFGR1_ADDRCFG_SHIFT)) & LPI2C_SCFGR1_ADDRCFG_MASK)
/*! @} */

/*! @name SCFGR2 - Slave Configuration 2 */
/*! @{ */

#define LPI2C_SCFGR2_CLKHOLD_MASK                (0xFU)
#define LPI2C_SCFGR2_CLKHOLD_SHIFT               (0U)
#define LPI2C_SCFGR2_CLKHOLD_WIDTH               (4U)
#define LPI2C_SCFGR2_CLKHOLD(x)                  (((uint32_t)(((uint32_t)(x)) << LPI2C_SCFGR2_CLKHOLD_SHIFT)) & LPI2C_SCFGR2_CLKHOLD_MASK)

#define LPI2C_SCFGR2_DATAVD_MASK                 (0x3F00U)
#define LPI2C_SCFGR2_DATAVD_SHIFT                (8U)
#define LPI2C_SCFGR2_DATAVD_WIDTH                (6U)
#define LPI2C_SCFGR2_DATAVD(x)                   (((uint32_t)(((uint32_t)(x)) << LPI2C_SCFGR2_DATAVD_SHIFT)) & LPI2C_SCFGR2_DATAVD_MASK)

#define LPI2C_SCFGR2_FILTSCL_MASK                (0xF0000U)
#define LPI2C_SCFGR2_FILTSCL_SHIFT               (16U)
#define LPI2C_SCFGR2_FILTSCL_WIDTH               (4U)
#define LPI2C_SCFGR2_FILTSCL(x)                  (((uint32_t)(((uint32_t)(x)) << LPI2C_SCFGR2_FILTSCL_SHIFT)) & LPI2C_SCFGR2_FILTSCL_MASK)

#define LPI2C_SCFGR2_FILTSDA_MASK                (0xF000000U)
#define LPI2C_SCFGR2_FILTSDA_SHIFT               (24U)
#define LPI2C_SCFGR2_FILTSDA_WIDTH               (4U)
#define LPI2C_SCFGR2_FILTSDA(x)                  (((uint32_t)(((uint32_t)(x)) << LPI2C_SCFGR2_FILTSDA_SHIFT)) & LPI2C_SCFGR2_FILTSDA_MASK)
/*! @} */

/*! @name SAMR - Slave Address Match */
/*! @{ */

#define LPI2C_SAMR_ADDR0_MASK                    (0x7FEU)
#define LPI2C_SAMR_ADDR0_SHIFT                   (1U)
#define LPI2C_SAMR_ADDR0_WIDTH                   (10U)
#define LPI2C_SAMR_ADDR0(x)                      (((uint32_t)(((uint32_t)(x)) << LPI2C_SAMR_ADDR0_SHIFT)) & LPI2C_SAMR_ADDR0_MASK)

#define LPI2C_SAMR_ADDR1_MASK                    (0x7FE0000U)
#define LPI2C_SAMR_ADDR1_SHIFT                   (17U)
#define LPI2C_SAMR_ADDR1_WIDTH                   (10U)
#define LPI2C_SAMR_ADDR1(x)                      (((uint32_t)(((uint32_t)(x)) << LPI2C_SAMR_ADDR1_SHIFT)) & LPI2C_SAMR_ADDR1_MASK)
/*! @} */

/*! @name SASR - Slave Address Status */
/*! @{ */

#define LPI2C_SASR_RADDR_MASK                    (0x7FFU)
#define LPI2C_SASR_RADDR_SHIFT                   (0U)
#define LPI2C_SASR_RADDR_WIDTH                   (11U)
#define LPI2C_SASR_RADDR(x)                      (((uint32_t)(((uint32_t)(x)) << LPI2C_SASR_RADDR_SHIFT)) & LPI2C_SASR_RADDR_MASK)

#define LPI2C_SASR_ANV_MASK                      (0x4000U)
#define LPI2C_SASR_ANV_SHIFT                     (14U)
#define LPI2C_SASR_ANV_WIDTH                     (1U)
#define LPI2C_SASR_ANV(x)                        (((uint32_t)(((uint32_t)(x)) << LPI2C_SASR_ANV_SHIFT)) & LPI2C_SASR_ANV_MASK)
/*! @} */

/*! @name STAR - Slave Transmit ACK */
/*! @{ */

#define LPI2C_STAR_TXNACK_MASK                   (0x1U)
#define LPI2C_STAR_TXNACK_SHIFT                  (0U)
#define LPI2C_STAR_TXNACK_WIDTH                  (1U)
#define LPI2C_STAR_TXNACK(x)                     (((uint32_t)(((uint32_t)(x)) << LPI2C_STAR_TXNACK_SHIFT)) & LPI2C_STAR_TXNACK_MASK)
/*! @} */

/*! @name STDR - Slave Transmit Data */
/*! @{ */

#define LPI2C_STDR_DATA_MASK                     (0xFFU)
#define LPI2C_STDR_DATA_SHIFT                    (0U)
#define LPI2C_STDR_DATA_WIDTH                    (8U)
#define LPI2C_STDR_DATA(x)                       (((uint32_t)(((uint32_t)(x)) << LPI2C_STDR_DATA_SHIFT)) & LPI2C_STDR_DATA_MASK)
/*! @} */

/*! @name SRDR - Slave Receive Data */
/*! @{ */

#define LPI2C_SRDR_DATA_MASK                     (0xFFU)
#define LPI2C_SRDR_DATA_SHIFT                    (0U)
#define LPI2C_SRDR_DATA_WIDTH                    (8U)
#define LPI2C_SRDR_DATA(x)                       (((uint32_t)(((uint32_t)(x)) << LPI2C_SRDR_DATA_SHIFT)) & LPI2C_SRDR_DATA_MASK)

#define LPI2C_SRDR_RADDR_MASK                    (0x700U)
#define LPI2C_SRDR_RADDR_SHIFT                   (8U)
#define LPI2C_SRDR_RADDR_WIDTH                   (3U)
#define LPI2C_SRDR_RADDR(x)                      (((uint32_t)(((uint32_t)(x)) << LPI2C_SRDR_RADDR_SHIFT)) & LPI2C_SRDR_RADDR_MASK)

#define LPI2C_SRDR_RXEMPTY_MASK                  (0x4000U)
#define LPI2C_SRDR_RXEMPTY_SHIFT                 (14U)
#define LPI2C_SRDR_RXEMPTY_WIDTH                 (1U)
#define LPI2C_SRDR_RXEMPTY(x)                    (((uint32_t)(((uint32_t)(x)) << LPI2C_SRDR_RXEMPTY_SHIFT)) & LPI2C_SRDR_RXEMPTY_MASK)

#define LPI2C_SRDR_SOF_MASK                      (0x8000U)
#define LPI2C_SRDR_SOF_SHIFT                     (15U)
#define LPI2C_SRDR_SOF_WIDTH                     (1U)
#define LPI2C_SRDR_SOF(x)                        (((uint32_t)(((uint32_t)(x)) << LPI2C_SRDR_SOF_SHIFT)) & LPI2C_SRDR_SOF_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group LPI2C_Register_Masks */

/*!
 * @}
 */ /* end of group LPI2C_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_LPI2C_H_) */
