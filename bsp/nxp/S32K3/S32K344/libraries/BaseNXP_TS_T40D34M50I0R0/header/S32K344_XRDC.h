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
 * @file S32K344_XRDC.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_XRDC
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
#if !defined(S32K344_XRDC_H_)  /* Check if memory map has not been already included */
#define S32K344_XRDC_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- XRDC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup XRDC_Peripheral_Access_Layer XRDC Peripheral Access Layer
 * @{
 */

/** XRDC - Size of Registers Arrays */
#define XRDC_MDAC_COUNT                           6u
#define XRDC_MRC_COUNT                            3u
#define XRDC_DERRLOC_COUNT                        3u
#define XRDC_DERRW0_COUNT                         19u
#define XRDC_PID_COUNT                            4u
#define XRDC_PDAC_SLOT_PDACN_COUNT                109u
#define XRDC_PDAC_SLOT_COUNT                      3u
#define XRDC_MRCN_COUNT                           3u
#define XRDC_MRCN_MRGDN_COUNT                     16u

/** XRDC - Register Layout Typedef */
typedef struct {
  __IO uint32_t CR;                                /**< Control, offset: 0x0 */
  uint8_t RESERVED_0[236];
  __I  uint32_t HWCFG0;                            /**< Hardware Configuration 0, offset: 0xF0 */
  __I  uint32_t HWCFG1;                            /**< Hardware Configuration 1, offset: 0xF4 */
  __I  uint32_t HWCFG2;                            /**< Hardware Configuration 2, offset: 0xF8 */
  uint8_t RESERVED_1[4];
  __I  uint8_t MDACFG[XRDC_MDAC_COUNT];            /**< Master Domain Assignment Configuration, array offset: 0x100, array step: 0x1 */
  uint8_t RESERVED_2[58];
  __I  uint8_t MRCFG[XRDC_MRC_COUNT];              /**< Memory Region Configuration, array offset: 0x140, array step: 0x1 */
  uint8_t RESERVED_3[189];
  __I  uint32_t DERRLOC[XRDC_DERRLOC_COUNT];       /**< Domain Error Location, array offset: 0x200, array step: 0x4 */
  uint8_t RESERVED_4[500];
  struct {                                         /* offset: 0x400, array step: 0x10 */
    __I  uint32_t DERR_W0;                           /**< Domain Error Word 0, array offset: 0x400, array step: 0x10 */
    __I  uint32_t DERR_W1;                           /**< Domain Error Word 1, array offset: 0x404, array step: 0x10 */
    uint8_t RESERVED_0[4];
    __O  uint32_t DERR_W3;                           /**< Domain Error Word 3, array offset: 0x40C, array step: 0x10 */
  } DERRW0[XRDC_DERRW0_COUNT];
  uint8_t RESERVED_5[464];
  __IO uint32_t PID[XRDC_PID_COUNT];               /**< Process Identifier, array offset: 0x700, array step: 0x4 */
  uint8_t RESERVED_6[240];
  __IO uint32_t MDA_W0_0_DFMT0;                    /**< Master Domain Assignment, offset: 0x800 */
  uint8_t RESERVED_7[28];
  __IO uint32_t MDA_W0_1_DFMT1;                    /**< Master Domain Assignment, offset: 0x820 */
  uint8_t RESERVED_8[28];
  __IO uint32_t MDA_W0_2_DFMT1;                    /**< Master Domain Assignment, offset: 0x840 */
  uint8_t RESERVED_9[28];
  __IO uint32_t MDA_W0_3_DFMT0;                    /**< Master Domain Assignment, offset: 0x860 */
  uint8_t RESERVED_10[60];
  __IO uint32_t MDA_W0_5_DFMT1;                    /**< Master Domain Assignment, offset: 0x8A0 */
  uint8_t RESERVED_11[1884];
  struct {                                         /* offset: 0x1000, array step: 0x400 */
    struct {                                         /* offset: 0x1000, array step: index*0x400, index2*0x8 */
      __IO uint32_t PDAC_W0;                           /**< Peripheral Domain Access Control Word 0, array offset: 0x1000, array step: index*0x400, index2*0x8 */
      __IO uint32_t PDAC_W1;                           /**< Peripheral Domain Access Control Word 1, array offset: 0x1004, array step: index*0x400, index2*0x8 */
    } PDACN[XRDC_PDAC_SLOT_PDACN_COUNT];
    uint8_t RESERVED_0[152];
  } PDAC_SLOT[XRDC_PDAC_SLOT_COUNT];
  uint8_t RESERVED_12[1024];
  struct {                                         /* offset: 0x2000, array step: index*0x200, index2*0x20 */
    __IO uint32_t XRDC_MRGD_W0;                      /**< Memory Region Descriptor Word 0, array offset: 0x2000, array step: index*0x200, index2*0x20 */
    __IO uint32_t XRDC_MRGD_W1;                      /**< Memory Region Descriptor Word 1, array offset: 0x2004, array step: index*0x200, index2*0x20 */
    __IO uint32_t XRDC_MRGD_W2;                      /**< Memory Region Descriptor Word 2, array offset: 0x2008, array step: index*0x200, index2*0x20 */
    __IO uint32_t XRDC_MRGD_W3;                      /**< Memory Region Descriptor Word 3, array offset: 0x200C, array step: index*0x200, index2*0x20 */
    uint8_t RESERVED_0[16];
  } MRGDN[XRDC_MRCN_COUNT][XRDC_MRCN_MRGDN_COUNT];
} XRDC_Type, *XRDC_MemMapPtr;

/** Number of instances of the XRDC module. */
#define XRDC_INSTANCE_COUNT                      (1u)

/* XRDC - Peripheral instance base addresses */
/** Peripheral XRDC base address */
#define IP_XRDC_BASE                             (0x40278000u)
/** Peripheral XRDC base pointer */
#define IP_XRDC                                  ((XRDC_Type *)IP_XRDC_BASE)
/** Array initializer of XRDC peripheral base addresses */
#define IP_XRDC_BASE_ADDRS                       { IP_XRDC_BASE }
/** Array initializer of XRDC peripheral base pointers */
#define IP_XRDC_BASE_PTRS                        { IP_XRDC }

/* ----------------------------------------------------------------------------
   -- XRDC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup XRDC_Register_Masks XRDC Register Masks
 * @{
 */

/*! @name CR - Control */
/*! @{ */

#define XRDC_CR_GVLD_MASK                        (0x1U)
#define XRDC_CR_GVLD_SHIFT                       (0U)
#define XRDC_CR_GVLD_WIDTH                       (1U)
#define XRDC_CR_GVLD(x)                          (((uint32_t)(((uint32_t)(x)) << XRDC_CR_GVLD_SHIFT)) & XRDC_CR_GVLD_MASK)

#define XRDC_CR_HRL_MASK                         (0x1EU)
#define XRDC_CR_HRL_SHIFT                        (1U)
#define XRDC_CR_HRL_WIDTH                        (4U)
#define XRDC_CR_HRL(x)                           (((uint32_t)(((uint32_t)(x)) << XRDC_CR_HRL_SHIFT)) & XRDC_CR_HRL_MASK)

#define XRDC_CR_MRF_MASK                         (0x80U)
#define XRDC_CR_MRF_SHIFT                        (7U)
#define XRDC_CR_MRF_WIDTH                        (1U)
#define XRDC_CR_MRF(x)                           (((uint32_t)(((uint32_t)(x)) << XRDC_CR_MRF_SHIFT)) & XRDC_CR_MRF_MASK)

#define XRDC_CR_VAW_MASK                         (0x100U)
#define XRDC_CR_VAW_SHIFT                        (8U)
#define XRDC_CR_VAW_WIDTH                        (1U)
#define XRDC_CR_VAW(x)                           (((uint32_t)(((uint32_t)(x)) << XRDC_CR_VAW_SHIFT)) & XRDC_CR_VAW_MASK)

#define XRDC_CR_LK1_MASK                         (0x40000000U)
#define XRDC_CR_LK1_SHIFT                        (30U)
#define XRDC_CR_LK1_WIDTH                        (1U)
#define XRDC_CR_LK1(x)                           (((uint32_t)(((uint32_t)(x)) << XRDC_CR_LK1_SHIFT)) & XRDC_CR_LK1_MASK)
/*! @} */

/*! @name HWCFG0 - Hardware Configuration 0 */
/*! @{ */

#define XRDC_HWCFG0_NDID_MASK                    (0xFFU)
#define XRDC_HWCFG0_NDID_SHIFT                   (0U)
#define XRDC_HWCFG0_NDID_WIDTH                   (8U)
#define XRDC_HWCFG0_NDID(x)                      (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG0_NDID_SHIFT)) & XRDC_HWCFG0_NDID_MASK)

#define XRDC_HWCFG0_NMSTR_MASK                   (0xFF00U)
#define XRDC_HWCFG0_NMSTR_SHIFT                  (8U)
#define XRDC_HWCFG0_NMSTR_WIDTH                  (8U)
#define XRDC_HWCFG0_NMSTR(x)                     (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG0_NMSTR_SHIFT)) & XRDC_HWCFG0_NMSTR_MASK)

#define XRDC_HWCFG0_NMRC_MASK                    (0xFF0000U)
#define XRDC_HWCFG0_NMRC_SHIFT                   (16U)
#define XRDC_HWCFG0_NMRC_WIDTH                   (8U)
#define XRDC_HWCFG0_NMRC(x)                      (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG0_NMRC_SHIFT)) & XRDC_HWCFG0_NMRC_MASK)

#define XRDC_HWCFG0_NPAC_MASK                    (0xF000000U)
#define XRDC_HWCFG0_NPAC_SHIFT                   (24U)
#define XRDC_HWCFG0_NPAC_WIDTH                   (4U)
#define XRDC_HWCFG0_NPAC(x)                      (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG0_NPAC_SHIFT)) & XRDC_HWCFG0_NPAC_MASK)

#define XRDC_HWCFG0_MID_MASK                     (0xF0000000U)
#define XRDC_HWCFG0_MID_SHIFT                    (28U)
#define XRDC_HWCFG0_MID_WIDTH                    (4U)
#define XRDC_HWCFG0_MID(x)                       (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG0_MID_SHIFT)) & XRDC_HWCFG0_MID_MASK)
/*! @} */

/*! @name HWCFG1 - Hardware Configuration 1 */
/*! @{ */

#define XRDC_HWCFG1_DID_MASK                     (0xFU)
#define XRDC_HWCFG1_DID_SHIFT                    (0U)
#define XRDC_HWCFG1_DID_WIDTH                    (4U)
#define XRDC_HWCFG1_DID(x)                       (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG1_DID_SHIFT)) & XRDC_HWCFG1_DID_MASK)
/*! @} */

/*! @name HWCFG2 - Hardware Configuration 2 */
/*! @{ */

#define XRDC_HWCFG2_PIDP0_MASK                   (0x1U)
#define XRDC_HWCFG2_PIDP0_SHIFT                  (0U)
#define XRDC_HWCFG2_PIDP0_WIDTH                  (1U)
#define XRDC_HWCFG2_PIDP0(x)                     (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG2_PIDP0_SHIFT)) & XRDC_HWCFG2_PIDP0_MASK)

#define XRDC_HWCFG2_PIDP1_MASK                   (0x2U)
#define XRDC_HWCFG2_PIDP1_SHIFT                  (1U)
#define XRDC_HWCFG2_PIDP1_WIDTH                  (1U)
#define XRDC_HWCFG2_PIDP1(x)                     (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG2_PIDP1_SHIFT)) & XRDC_HWCFG2_PIDP1_MASK)

#define XRDC_HWCFG2_PIDP2_MASK                   (0x4U)
#define XRDC_HWCFG2_PIDP2_SHIFT                  (2U)
#define XRDC_HWCFG2_PIDP2_WIDTH                  (1U)
#define XRDC_HWCFG2_PIDP2(x)                     (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG2_PIDP2_SHIFT)) & XRDC_HWCFG2_PIDP2_MASK)

#define XRDC_HWCFG2_PIDP3_MASK                   (0x8U)
#define XRDC_HWCFG2_PIDP3_SHIFT                  (3U)
#define XRDC_HWCFG2_PIDP3_WIDTH                  (1U)
#define XRDC_HWCFG2_PIDP3(x)                     (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG2_PIDP3_SHIFT)) & XRDC_HWCFG2_PIDP3_MASK)

#define XRDC_HWCFG2_PIDP4_MASK                   (0x10U)
#define XRDC_HWCFG2_PIDP4_SHIFT                  (4U)
#define XRDC_HWCFG2_PIDP4_WIDTH                  (1U)
#define XRDC_HWCFG2_PIDP4(x)                     (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG2_PIDP4_SHIFT)) & XRDC_HWCFG2_PIDP4_MASK)

#define XRDC_HWCFG2_PIDP5_MASK                   (0x20U)
#define XRDC_HWCFG2_PIDP5_SHIFT                  (5U)
#define XRDC_HWCFG2_PIDP5_WIDTH                  (1U)
#define XRDC_HWCFG2_PIDP5(x)                     (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG2_PIDP5_SHIFT)) & XRDC_HWCFG2_PIDP5_MASK)

#define XRDC_HWCFG2_PIDP6_MASK                   (0x40U)
#define XRDC_HWCFG2_PIDP6_SHIFT                  (6U)
#define XRDC_HWCFG2_PIDP6_WIDTH                  (1U)
#define XRDC_HWCFG2_PIDP6(x)                     (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG2_PIDP6_SHIFT)) & XRDC_HWCFG2_PIDP6_MASK)

#define XRDC_HWCFG2_PIDP7_MASK                   (0x80U)
#define XRDC_HWCFG2_PIDP7_SHIFT                  (7U)
#define XRDC_HWCFG2_PIDP7_WIDTH                  (1U)
#define XRDC_HWCFG2_PIDP7(x)                     (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG2_PIDP7_SHIFT)) & XRDC_HWCFG2_PIDP7_MASK)

#define XRDC_HWCFG2_PIDP8_MASK                   (0x100U)
#define XRDC_HWCFG2_PIDP8_SHIFT                  (8U)
#define XRDC_HWCFG2_PIDP8_WIDTH                  (1U)
#define XRDC_HWCFG2_PIDP8(x)                     (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG2_PIDP8_SHIFT)) & XRDC_HWCFG2_PIDP8_MASK)

#define XRDC_HWCFG2_PIDP9_MASK                   (0x200U)
#define XRDC_HWCFG2_PIDP9_SHIFT                  (9U)
#define XRDC_HWCFG2_PIDP9_WIDTH                  (1U)
#define XRDC_HWCFG2_PIDP9(x)                     (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG2_PIDP9_SHIFT)) & XRDC_HWCFG2_PIDP9_MASK)

#define XRDC_HWCFG2_PIDP10_MASK                  (0x400U)
#define XRDC_HWCFG2_PIDP10_SHIFT                 (10U)
#define XRDC_HWCFG2_PIDP10_WIDTH                 (1U)
#define XRDC_HWCFG2_PIDP10(x)                    (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG2_PIDP10_SHIFT)) & XRDC_HWCFG2_PIDP10_MASK)

#define XRDC_HWCFG2_PIDP11_MASK                  (0x800U)
#define XRDC_HWCFG2_PIDP11_SHIFT                 (11U)
#define XRDC_HWCFG2_PIDP11_WIDTH                 (1U)
#define XRDC_HWCFG2_PIDP11(x)                    (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG2_PIDP11_SHIFT)) & XRDC_HWCFG2_PIDP11_MASK)

#define XRDC_HWCFG2_PIDP12_MASK                  (0x1000U)
#define XRDC_HWCFG2_PIDP12_SHIFT                 (12U)
#define XRDC_HWCFG2_PIDP12_WIDTH                 (1U)
#define XRDC_HWCFG2_PIDP12(x)                    (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG2_PIDP12_SHIFT)) & XRDC_HWCFG2_PIDP12_MASK)

#define XRDC_HWCFG2_PIDP13_MASK                  (0x2000U)
#define XRDC_HWCFG2_PIDP13_SHIFT                 (13U)
#define XRDC_HWCFG2_PIDP13_WIDTH                 (1U)
#define XRDC_HWCFG2_PIDP13(x)                    (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG2_PIDP13_SHIFT)) & XRDC_HWCFG2_PIDP13_MASK)

#define XRDC_HWCFG2_PIDP14_MASK                  (0x4000U)
#define XRDC_HWCFG2_PIDP14_SHIFT                 (14U)
#define XRDC_HWCFG2_PIDP14_WIDTH                 (1U)
#define XRDC_HWCFG2_PIDP14(x)                    (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG2_PIDP14_SHIFT)) & XRDC_HWCFG2_PIDP14_MASK)

#define XRDC_HWCFG2_PIDP15_MASK                  (0x8000U)
#define XRDC_HWCFG2_PIDP15_SHIFT                 (15U)
#define XRDC_HWCFG2_PIDP15_WIDTH                 (1U)
#define XRDC_HWCFG2_PIDP15(x)                    (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG2_PIDP15_SHIFT)) & XRDC_HWCFG2_PIDP15_MASK)

#define XRDC_HWCFG2_PIDP16_MASK                  (0x10000U)
#define XRDC_HWCFG2_PIDP16_SHIFT                 (16U)
#define XRDC_HWCFG2_PIDP16_WIDTH                 (1U)
#define XRDC_HWCFG2_PIDP16(x)                    (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG2_PIDP16_SHIFT)) & XRDC_HWCFG2_PIDP16_MASK)

#define XRDC_HWCFG2_PIDP17_MASK                  (0x20000U)
#define XRDC_HWCFG2_PIDP17_SHIFT                 (17U)
#define XRDC_HWCFG2_PIDP17_WIDTH                 (1U)
#define XRDC_HWCFG2_PIDP17(x)                    (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG2_PIDP17_SHIFT)) & XRDC_HWCFG2_PIDP17_MASK)

#define XRDC_HWCFG2_PIDP18_MASK                  (0x40000U)
#define XRDC_HWCFG2_PIDP18_SHIFT                 (18U)
#define XRDC_HWCFG2_PIDP18_WIDTH                 (1U)
#define XRDC_HWCFG2_PIDP18(x)                    (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG2_PIDP18_SHIFT)) & XRDC_HWCFG2_PIDP18_MASK)

#define XRDC_HWCFG2_PIDP19_MASK                  (0x80000U)
#define XRDC_HWCFG2_PIDP19_SHIFT                 (19U)
#define XRDC_HWCFG2_PIDP19_WIDTH                 (1U)
#define XRDC_HWCFG2_PIDP19(x)                    (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG2_PIDP19_SHIFT)) & XRDC_HWCFG2_PIDP19_MASK)

#define XRDC_HWCFG2_PIDP20_MASK                  (0x100000U)
#define XRDC_HWCFG2_PIDP20_SHIFT                 (20U)
#define XRDC_HWCFG2_PIDP20_WIDTH                 (1U)
#define XRDC_HWCFG2_PIDP20(x)                    (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG2_PIDP20_SHIFT)) & XRDC_HWCFG2_PIDP20_MASK)

#define XRDC_HWCFG2_PIDP21_MASK                  (0x200000U)
#define XRDC_HWCFG2_PIDP21_SHIFT                 (21U)
#define XRDC_HWCFG2_PIDP21_WIDTH                 (1U)
#define XRDC_HWCFG2_PIDP21(x)                    (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG2_PIDP21_SHIFT)) & XRDC_HWCFG2_PIDP21_MASK)

#define XRDC_HWCFG2_PIDP22_MASK                  (0x400000U)
#define XRDC_HWCFG2_PIDP22_SHIFT                 (22U)
#define XRDC_HWCFG2_PIDP22_WIDTH                 (1U)
#define XRDC_HWCFG2_PIDP22(x)                    (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG2_PIDP22_SHIFT)) & XRDC_HWCFG2_PIDP22_MASK)

#define XRDC_HWCFG2_PIDP23_MASK                  (0x800000U)
#define XRDC_HWCFG2_PIDP23_SHIFT                 (23U)
#define XRDC_HWCFG2_PIDP23_WIDTH                 (1U)
#define XRDC_HWCFG2_PIDP23(x)                    (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG2_PIDP23_SHIFT)) & XRDC_HWCFG2_PIDP23_MASK)

#define XRDC_HWCFG2_PIDP24_MASK                  (0x1000000U)
#define XRDC_HWCFG2_PIDP24_SHIFT                 (24U)
#define XRDC_HWCFG2_PIDP24_WIDTH                 (1U)
#define XRDC_HWCFG2_PIDP24(x)                    (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG2_PIDP24_SHIFT)) & XRDC_HWCFG2_PIDP24_MASK)

#define XRDC_HWCFG2_PIDP25_MASK                  (0x2000000U)
#define XRDC_HWCFG2_PIDP25_SHIFT                 (25U)
#define XRDC_HWCFG2_PIDP25_WIDTH                 (1U)
#define XRDC_HWCFG2_PIDP25(x)                    (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG2_PIDP25_SHIFT)) & XRDC_HWCFG2_PIDP25_MASK)

#define XRDC_HWCFG2_PIDP26_MASK                  (0x4000000U)
#define XRDC_HWCFG2_PIDP26_SHIFT                 (26U)
#define XRDC_HWCFG2_PIDP26_WIDTH                 (1U)
#define XRDC_HWCFG2_PIDP26(x)                    (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG2_PIDP26_SHIFT)) & XRDC_HWCFG2_PIDP26_MASK)

#define XRDC_HWCFG2_PIDP27_MASK                  (0x8000000U)
#define XRDC_HWCFG2_PIDP27_SHIFT                 (27U)
#define XRDC_HWCFG2_PIDP27_WIDTH                 (1U)
#define XRDC_HWCFG2_PIDP27(x)                    (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG2_PIDP27_SHIFT)) & XRDC_HWCFG2_PIDP27_MASK)

#define XRDC_HWCFG2_PIDP28_MASK                  (0x10000000U)
#define XRDC_HWCFG2_PIDP28_SHIFT                 (28U)
#define XRDC_HWCFG2_PIDP28_WIDTH                 (1U)
#define XRDC_HWCFG2_PIDP28(x)                    (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG2_PIDP28_SHIFT)) & XRDC_HWCFG2_PIDP28_MASK)

#define XRDC_HWCFG2_PIDP29_MASK                  (0x20000000U)
#define XRDC_HWCFG2_PIDP29_SHIFT                 (29U)
#define XRDC_HWCFG2_PIDP29_WIDTH                 (1U)
#define XRDC_HWCFG2_PIDP29(x)                    (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG2_PIDP29_SHIFT)) & XRDC_HWCFG2_PIDP29_MASK)

#define XRDC_HWCFG2_PIDP30_MASK                  (0x40000000U)
#define XRDC_HWCFG2_PIDP30_SHIFT                 (30U)
#define XRDC_HWCFG2_PIDP30_WIDTH                 (1U)
#define XRDC_HWCFG2_PIDP30(x)                    (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG2_PIDP30_SHIFT)) & XRDC_HWCFG2_PIDP30_MASK)

#define XRDC_HWCFG2_PIDP31_MASK                  (0x80000000U)
#define XRDC_HWCFG2_PIDP31_SHIFT                 (31U)
#define XRDC_HWCFG2_PIDP31_WIDTH                 (1U)
#define XRDC_HWCFG2_PIDP31(x)                    (((uint32_t)(((uint32_t)(x)) << XRDC_HWCFG2_PIDP31_SHIFT)) & XRDC_HWCFG2_PIDP31_MASK)
/*! @} */

/*! @name MDACFG - Master Domain Assignment Configuration */
/*! @{ */

#define XRDC_MDACFG_NMDAR_MASK                   (0xFU)
#define XRDC_MDACFG_NMDAR_SHIFT                  (0U)
#define XRDC_MDACFG_NMDAR_WIDTH                  (4U)
#define XRDC_MDACFG_NMDAR(x)                     (((uint8_t)(((uint8_t)(x)) << XRDC_MDACFG_NMDAR_SHIFT)) & XRDC_MDACFG_NMDAR_MASK)

#define XRDC_MDACFG_NCM_MASK                     (0x80U)
#define XRDC_MDACFG_NCM_SHIFT                    (7U)
#define XRDC_MDACFG_NCM_WIDTH                    (1U)
#define XRDC_MDACFG_NCM(x)                       (((uint8_t)(((uint8_t)(x)) << XRDC_MDACFG_NCM_SHIFT)) & XRDC_MDACFG_NCM_MASK)
/*! @} */

/*! @name MRCFG - Memory Region Configuration */
/*! @{ */

#define XRDC_MRCFG_NMRGD_MASK                    (0x1FU)
#define XRDC_MRCFG_NMRGD_SHIFT                   (0U)
#define XRDC_MRCFG_NMRGD_WIDTH                   (5U)
#define XRDC_MRCFG_NMRGD(x)                      (((uint8_t)(((uint8_t)(x)) << XRDC_MRCFG_NMRGD_SHIFT)) & XRDC_MRCFG_NMRGD_MASK)
/*! @} */

/*! @name DERRLOC - Domain Error Location */
/*! @{ */

#define XRDC_DERRLOC_MRCINST_MASK                (0xFFFFU)
#define XRDC_DERRLOC_MRCINST_SHIFT               (0U)
#define XRDC_DERRLOC_MRCINST_WIDTH               (16U)
#define XRDC_DERRLOC_MRCINST(x)                  (((uint32_t)(((uint32_t)(x)) << XRDC_DERRLOC_MRCINST_SHIFT)) & XRDC_DERRLOC_MRCINST_MASK)

#define XRDC_DERRLOC_PACINST_MASK                (0xF0000U)
#define XRDC_DERRLOC_PACINST_SHIFT               (16U)
#define XRDC_DERRLOC_PACINST_WIDTH               (4U)
#define XRDC_DERRLOC_PACINST(x)                  (((uint32_t)(((uint32_t)(x)) << XRDC_DERRLOC_PACINST_SHIFT)) & XRDC_DERRLOC_PACINST_MASK)
/*! @} */

/*! @name DERR_W0 - Domain Error Word 0 */
/*! @{ */

#define XRDC_DERR_W0_EADDR_MASK                  (0xFFFFFFFFU)
#define XRDC_DERR_W0_EADDR_SHIFT                 (0U)
#define XRDC_DERR_W0_EADDR_WIDTH                 (32U)
#define XRDC_DERR_W0_EADDR(x)                    (((uint32_t)(((uint32_t)(x)) << XRDC_DERR_W0_EADDR_SHIFT)) & XRDC_DERR_W0_EADDR_MASK)
/*! @} */

/*! @name DERR_W1 - Domain Error Word 1 */
/*! @{ */

#define XRDC_DERR_W1_EDID_MASK                   (0xFU)
#define XRDC_DERR_W1_EDID_SHIFT                  (0U)
#define XRDC_DERR_W1_EDID_WIDTH                  (4U)
#define XRDC_DERR_W1_EDID(x)                     (((uint32_t)(((uint32_t)(x)) << XRDC_DERR_W1_EDID_SHIFT)) & XRDC_DERR_W1_EDID_MASK)

#define XRDC_DERR_W1_EATR_MASK                   (0x700U)
#define XRDC_DERR_W1_EATR_SHIFT                  (8U)
#define XRDC_DERR_W1_EATR_WIDTH                  (3U)
#define XRDC_DERR_W1_EATR(x)                     (((uint32_t)(((uint32_t)(x)) << XRDC_DERR_W1_EATR_SHIFT)) & XRDC_DERR_W1_EATR_MASK)

#define XRDC_DERR_W1_ERW_MASK                    (0x800U)
#define XRDC_DERR_W1_ERW_SHIFT                   (11U)
#define XRDC_DERR_W1_ERW_WIDTH                   (1U)
#define XRDC_DERR_W1_ERW(x)                      (((uint32_t)(((uint32_t)(x)) << XRDC_DERR_W1_ERW_SHIFT)) & XRDC_DERR_W1_ERW_MASK)

#define XRDC_DERR_W1_EPORT_MASK                  (0x7000000U)
#define XRDC_DERR_W1_EPORT_SHIFT                 (24U)
#define XRDC_DERR_W1_EPORT_WIDTH                 (3U)
#define XRDC_DERR_W1_EPORT(x)                    (((uint32_t)(((uint32_t)(x)) << XRDC_DERR_W1_EPORT_SHIFT)) & XRDC_DERR_W1_EPORT_MASK)

#define XRDC_DERR_W1_EST_MASK                    (0xC0000000U)
#define XRDC_DERR_W1_EST_SHIFT                   (30U)
#define XRDC_DERR_W1_EST_WIDTH                   (2U)
#define XRDC_DERR_W1_EST(x)                      (((uint32_t)(((uint32_t)(x)) << XRDC_DERR_W1_EST_SHIFT)) & XRDC_DERR_W1_EST_MASK)
/*! @} */

/*! @name DERR_W3 - Domain Error Word 3 */
/*! @{ */

#define XRDC_DERR_W3_RECR_MASK                   (0xC0000000U)
#define XRDC_DERR_W3_RECR_SHIFT                  (30U)
#define XRDC_DERR_W3_RECR_WIDTH                  (2U)
#define XRDC_DERR_W3_RECR(x)                     (((uint32_t)(((uint32_t)(x)) << XRDC_DERR_W3_RECR_SHIFT)) & XRDC_DERR_W3_RECR_MASK)
/*! @} */

/*! @name PID - Process Identifier */
/*! @{ */

#define XRDC_PID_PID_MASK                        (0x3FU)
#define XRDC_PID_PID_SHIFT                       (0U)
#define XRDC_PID_PID_WIDTH                       (6U)
#define XRDC_PID_PID(x)                          (((uint32_t)(((uint32_t)(x)) << XRDC_PID_PID_SHIFT)) & XRDC_PID_PID_MASK)

#define XRDC_PID_TSM_MASK                        (0x10000000U)
#define XRDC_PID_TSM_SHIFT                       (28U)
#define XRDC_PID_TSM_WIDTH                       (1U)
#define XRDC_PID_TSM(x)                          (((uint32_t)(((uint32_t)(x)) << XRDC_PID_TSM_SHIFT)) & XRDC_PID_TSM_MASK)

#define XRDC_PID_LK2_MASK                        (0x60000000U)
#define XRDC_PID_LK2_SHIFT                       (29U)
#define XRDC_PID_LK2_WIDTH                       (2U)
#define XRDC_PID_LK2(x)                          (((uint32_t)(((uint32_t)(x)) << XRDC_PID_LK2_SHIFT)) & XRDC_PID_LK2_MASK)
/*! @} */

/*! @name MDA_W0_0_DFMT0 - Master Domain Assignment */
/*! @{ */

#define XRDC_MDA_W0_0_DFMT0_DID_MASK             (0x3U)
#define XRDC_MDA_W0_0_DFMT0_DID_SHIFT            (0U)
#define XRDC_MDA_W0_0_DFMT0_DID_WIDTH            (2U)
#define XRDC_MDA_W0_0_DFMT0_DID(x)               (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_0_DFMT0_DID_SHIFT)) & XRDC_MDA_W0_0_DFMT0_DID_MASK)

#define XRDC_MDA_W0_0_DFMT0_DIDS_MASK            (0x30U)
#define XRDC_MDA_W0_0_DFMT0_DIDS_SHIFT           (4U)
#define XRDC_MDA_W0_0_DFMT0_DIDS_WIDTH           (2U)
#define XRDC_MDA_W0_0_DFMT0_DIDS(x)              (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_0_DFMT0_DIDS_SHIFT)) & XRDC_MDA_W0_0_DFMT0_DIDS_MASK)

#define XRDC_MDA_W0_0_DFMT0_PE_MASK              (0xC0U)
#define XRDC_MDA_W0_0_DFMT0_PE_SHIFT             (6U)
#define XRDC_MDA_W0_0_DFMT0_PE_WIDTH             (2U)
#define XRDC_MDA_W0_0_DFMT0_PE(x)                (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_0_DFMT0_PE_SHIFT)) & XRDC_MDA_W0_0_DFMT0_PE_MASK)

#define XRDC_MDA_W0_0_DFMT0_PIDM_MASK            (0x3F00U)
#define XRDC_MDA_W0_0_DFMT0_PIDM_SHIFT           (8U)
#define XRDC_MDA_W0_0_DFMT0_PIDM_WIDTH           (6U)
#define XRDC_MDA_W0_0_DFMT0_PIDM(x)              (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_0_DFMT0_PIDM_SHIFT)) & XRDC_MDA_W0_0_DFMT0_PIDM_MASK)

#define XRDC_MDA_W0_0_DFMT0_PID_MASK             (0x3F0000U)
#define XRDC_MDA_W0_0_DFMT0_PID_SHIFT            (16U)
#define XRDC_MDA_W0_0_DFMT0_PID_WIDTH            (6U)
#define XRDC_MDA_W0_0_DFMT0_PID(x)               (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_0_DFMT0_PID_SHIFT)) & XRDC_MDA_W0_0_DFMT0_PID_MASK)

#define XRDC_MDA_W0_0_DFMT0_DFMT_MASK            (0x20000000U)
#define XRDC_MDA_W0_0_DFMT0_DFMT_SHIFT           (29U)
#define XRDC_MDA_W0_0_DFMT0_DFMT_WIDTH           (1U)
#define XRDC_MDA_W0_0_DFMT0_DFMT(x)              (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_0_DFMT0_DFMT_SHIFT)) & XRDC_MDA_W0_0_DFMT0_DFMT_MASK)

#define XRDC_MDA_W0_0_DFMT0_LK1_MASK             (0x40000000U)
#define XRDC_MDA_W0_0_DFMT0_LK1_SHIFT            (30U)
#define XRDC_MDA_W0_0_DFMT0_LK1_WIDTH            (1U)
#define XRDC_MDA_W0_0_DFMT0_LK1(x)               (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_0_DFMT0_LK1_SHIFT)) & XRDC_MDA_W0_0_DFMT0_LK1_MASK)

#define XRDC_MDA_W0_0_DFMT0_VLD_MASK             (0x80000000U)
#define XRDC_MDA_W0_0_DFMT0_VLD_SHIFT            (31U)
#define XRDC_MDA_W0_0_DFMT0_VLD_WIDTH            (1U)
#define XRDC_MDA_W0_0_DFMT0_VLD(x)               (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_0_DFMT0_VLD_SHIFT)) & XRDC_MDA_W0_0_DFMT0_VLD_MASK)
/*! @} */

/*! @name MDA_W0_1_DFMT1 - Master Domain Assignment */
/*! @{ */

#define XRDC_MDA_W0_1_DFMT1_DID_MASK             (0x3U)
#define XRDC_MDA_W0_1_DFMT1_DID_SHIFT            (0U)
#define XRDC_MDA_W0_1_DFMT1_DID_WIDTH            (2U)
#define XRDC_MDA_W0_1_DFMT1_DID(x)               (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_1_DFMT1_DID_SHIFT)) & XRDC_MDA_W0_1_DFMT1_DID_MASK)

#define XRDC_MDA_W0_1_DFMT1_PA_MASK              (0x30U)
#define XRDC_MDA_W0_1_DFMT1_PA_SHIFT             (4U)
#define XRDC_MDA_W0_1_DFMT1_PA_WIDTH             (2U)
#define XRDC_MDA_W0_1_DFMT1_PA(x)                (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_1_DFMT1_PA_SHIFT)) & XRDC_MDA_W0_1_DFMT1_PA_MASK)

#define XRDC_MDA_W0_1_DFMT1_SA_MASK              (0xC0U)
#define XRDC_MDA_W0_1_DFMT1_SA_SHIFT             (6U)
#define XRDC_MDA_W0_1_DFMT1_SA_WIDTH             (2U)
#define XRDC_MDA_W0_1_DFMT1_SA(x)                (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_1_DFMT1_SA_SHIFT)) & XRDC_MDA_W0_1_DFMT1_SA_MASK)

#define XRDC_MDA_W0_1_DFMT1_DIDB_MASK            (0x100U)
#define XRDC_MDA_W0_1_DFMT1_DIDB_SHIFT           (8U)
#define XRDC_MDA_W0_1_DFMT1_DIDB_WIDTH           (1U)
#define XRDC_MDA_W0_1_DFMT1_DIDB(x)              (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_1_DFMT1_DIDB_SHIFT)) & XRDC_MDA_W0_1_DFMT1_DIDB_MASK)

#define XRDC_MDA_W0_1_DFMT1_DFMT_MASK            (0x20000000U)
#define XRDC_MDA_W0_1_DFMT1_DFMT_SHIFT           (29U)
#define XRDC_MDA_W0_1_DFMT1_DFMT_WIDTH           (1U)
#define XRDC_MDA_W0_1_DFMT1_DFMT(x)              (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_1_DFMT1_DFMT_SHIFT)) & XRDC_MDA_W0_1_DFMT1_DFMT_MASK)

#define XRDC_MDA_W0_1_DFMT1_LK1_MASK             (0x40000000U)
#define XRDC_MDA_W0_1_DFMT1_LK1_SHIFT            (30U)
#define XRDC_MDA_W0_1_DFMT1_LK1_WIDTH            (1U)
#define XRDC_MDA_W0_1_DFMT1_LK1(x)               (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_1_DFMT1_LK1_SHIFT)) & XRDC_MDA_W0_1_DFMT1_LK1_MASK)

#define XRDC_MDA_W0_1_DFMT1_VLD_MASK             (0x80000000U)
#define XRDC_MDA_W0_1_DFMT1_VLD_SHIFT            (31U)
#define XRDC_MDA_W0_1_DFMT1_VLD_WIDTH            (1U)
#define XRDC_MDA_W0_1_DFMT1_VLD(x)               (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_1_DFMT1_VLD_SHIFT)) & XRDC_MDA_W0_1_DFMT1_VLD_MASK)
/*! @} */

/*! @name MDA_W0_2_DFMT1 - Master Domain Assignment */
/*! @{ */

#define XRDC_MDA_W0_2_DFMT1_DID_MASK             (0x3U)
#define XRDC_MDA_W0_2_DFMT1_DID_SHIFT            (0U)
#define XRDC_MDA_W0_2_DFMT1_DID_WIDTH            (2U)
#define XRDC_MDA_W0_2_DFMT1_DID(x)               (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_2_DFMT1_DID_SHIFT)) & XRDC_MDA_W0_2_DFMT1_DID_MASK)

#define XRDC_MDA_W0_2_DFMT1_PA_MASK              (0x30U)
#define XRDC_MDA_W0_2_DFMT1_PA_SHIFT             (4U)
#define XRDC_MDA_W0_2_DFMT1_PA_WIDTH             (2U)
#define XRDC_MDA_W0_2_DFMT1_PA(x)                (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_2_DFMT1_PA_SHIFT)) & XRDC_MDA_W0_2_DFMT1_PA_MASK)

#define XRDC_MDA_W0_2_DFMT1_SA_MASK              (0xC0U)
#define XRDC_MDA_W0_2_DFMT1_SA_SHIFT             (6U)
#define XRDC_MDA_W0_2_DFMT1_SA_WIDTH             (2U)
#define XRDC_MDA_W0_2_DFMT1_SA(x)                (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_2_DFMT1_SA_SHIFT)) & XRDC_MDA_W0_2_DFMT1_SA_MASK)

#define XRDC_MDA_W0_2_DFMT1_DIDB_MASK            (0x100U)
#define XRDC_MDA_W0_2_DFMT1_DIDB_SHIFT           (8U)
#define XRDC_MDA_W0_2_DFMT1_DIDB_WIDTH           (1U)
#define XRDC_MDA_W0_2_DFMT1_DIDB(x)              (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_2_DFMT1_DIDB_SHIFT)) & XRDC_MDA_W0_2_DFMT1_DIDB_MASK)

#define XRDC_MDA_W0_2_DFMT1_DFMT_MASK            (0x20000000U)
#define XRDC_MDA_W0_2_DFMT1_DFMT_SHIFT           (29U)
#define XRDC_MDA_W0_2_DFMT1_DFMT_WIDTH           (1U)
#define XRDC_MDA_W0_2_DFMT1_DFMT(x)              (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_2_DFMT1_DFMT_SHIFT)) & XRDC_MDA_W0_2_DFMT1_DFMT_MASK)

#define XRDC_MDA_W0_2_DFMT1_LK1_MASK             (0x40000000U)
#define XRDC_MDA_W0_2_DFMT1_LK1_SHIFT            (30U)
#define XRDC_MDA_W0_2_DFMT1_LK1_WIDTH            (1U)
#define XRDC_MDA_W0_2_DFMT1_LK1(x)               (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_2_DFMT1_LK1_SHIFT)) & XRDC_MDA_W0_2_DFMT1_LK1_MASK)

#define XRDC_MDA_W0_2_DFMT1_VLD_MASK             (0x80000000U)
#define XRDC_MDA_W0_2_DFMT1_VLD_SHIFT            (31U)
#define XRDC_MDA_W0_2_DFMT1_VLD_WIDTH            (1U)
#define XRDC_MDA_W0_2_DFMT1_VLD(x)               (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_2_DFMT1_VLD_SHIFT)) & XRDC_MDA_W0_2_DFMT1_VLD_MASK)
/*! @} */

/*! @name MDA_W0_3_DFMT0 - Master Domain Assignment */
/*! @{ */

#define XRDC_MDA_W0_3_DFMT0_DID_MASK             (0x3U)
#define XRDC_MDA_W0_3_DFMT0_DID_SHIFT            (0U)
#define XRDC_MDA_W0_3_DFMT0_DID_WIDTH            (2U)
#define XRDC_MDA_W0_3_DFMT0_DID(x)               (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_3_DFMT0_DID_SHIFT)) & XRDC_MDA_W0_3_DFMT0_DID_MASK)

#define XRDC_MDA_W0_3_DFMT0_DIDS_MASK            (0x30U)
#define XRDC_MDA_W0_3_DFMT0_DIDS_SHIFT           (4U)
#define XRDC_MDA_W0_3_DFMT0_DIDS_WIDTH           (2U)
#define XRDC_MDA_W0_3_DFMT0_DIDS(x)              (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_3_DFMT0_DIDS_SHIFT)) & XRDC_MDA_W0_3_DFMT0_DIDS_MASK)

#define XRDC_MDA_W0_3_DFMT0_PE_MASK              (0xC0U)
#define XRDC_MDA_W0_3_DFMT0_PE_SHIFT             (6U)
#define XRDC_MDA_W0_3_DFMT0_PE_WIDTH             (2U)
#define XRDC_MDA_W0_3_DFMT0_PE(x)                (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_3_DFMT0_PE_SHIFT)) & XRDC_MDA_W0_3_DFMT0_PE_MASK)

#define XRDC_MDA_W0_3_DFMT0_PIDM_MASK            (0x3F00U)
#define XRDC_MDA_W0_3_DFMT0_PIDM_SHIFT           (8U)
#define XRDC_MDA_W0_3_DFMT0_PIDM_WIDTH           (6U)
#define XRDC_MDA_W0_3_DFMT0_PIDM(x)              (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_3_DFMT0_PIDM_SHIFT)) & XRDC_MDA_W0_3_DFMT0_PIDM_MASK)

#define XRDC_MDA_W0_3_DFMT0_PID_MASK             (0x3F0000U)
#define XRDC_MDA_W0_3_DFMT0_PID_SHIFT            (16U)
#define XRDC_MDA_W0_3_DFMT0_PID_WIDTH            (6U)
#define XRDC_MDA_W0_3_DFMT0_PID(x)               (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_3_DFMT0_PID_SHIFT)) & XRDC_MDA_W0_3_DFMT0_PID_MASK)

#define XRDC_MDA_W0_3_DFMT0_DFMT_MASK            (0x20000000U)
#define XRDC_MDA_W0_3_DFMT0_DFMT_SHIFT           (29U)
#define XRDC_MDA_W0_3_DFMT0_DFMT_WIDTH           (1U)
#define XRDC_MDA_W0_3_DFMT0_DFMT(x)              (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_3_DFMT0_DFMT_SHIFT)) & XRDC_MDA_W0_3_DFMT0_DFMT_MASK)

#define XRDC_MDA_W0_3_DFMT0_LK1_MASK             (0x40000000U)
#define XRDC_MDA_W0_3_DFMT0_LK1_SHIFT            (30U)
#define XRDC_MDA_W0_3_DFMT0_LK1_WIDTH            (1U)
#define XRDC_MDA_W0_3_DFMT0_LK1(x)               (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_3_DFMT0_LK1_SHIFT)) & XRDC_MDA_W0_3_DFMT0_LK1_MASK)

#define XRDC_MDA_W0_3_DFMT0_VLD_MASK             (0x80000000U)
#define XRDC_MDA_W0_3_DFMT0_VLD_SHIFT            (31U)
#define XRDC_MDA_W0_3_DFMT0_VLD_WIDTH            (1U)
#define XRDC_MDA_W0_3_DFMT0_VLD(x)               (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_3_DFMT0_VLD_SHIFT)) & XRDC_MDA_W0_3_DFMT0_VLD_MASK)
/*! @} */

/*! @name MDA_W0_5_DFMT1 - Master Domain Assignment */
/*! @{ */

#define XRDC_MDA_W0_5_DFMT1_DID_MASK             (0x3U)
#define XRDC_MDA_W0_5_DFMT1_DID_SHIFT            (0U)
#define XRDC_MDA_W0_5_DFMT1_DID_WIDTH            (2U)
#define XRDC_MDA_W0_5_DFMT1_DID(x)               (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_5_DFMT1_DID_SHIFT)) & XRDC_MDA_W0_5_DFMT1_DID_MASK)

#define XRDC_MDA_W0_5_DFMT1_PA_MASK              (0x30U)
#define XRDC_MDA_W0_5_DFMT1_PA_SHIFT             (4U)
#define XRDC_MDA_W0_5_DFMT1_PA_WIDTH             (2U)
#define XRDC_MDA_W0_5_DFMT1_PA(x)                (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_5_DFMT1_PA_SHIFT)) & XRDC_MDA_W0_5_DFMT1_PA_MASK)

#define XRDC_MDA_W0_5_DFMT1_SA_MASK              (0xC0U)
#define XRDC_MDA_W0_5_DFMT1_SA_SHIFT             (6U)
#define XRDC_MDA_W0_5_DFMT1_SA_WIDTH             (2U)
#define XRDC_MDA_W0_5_DFMT1_SA(x)                (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_5_DFMT1_SA_SHIFT)) & XRDC_MDA_W0_5_DFMT1_SA_MASK)

#define XRDC_MDA_W0_5_DFMT1_DIDB_MASK            (0x100U)
#define XRDC_MDA_W0_5_DFMT1_DIDB_SHIFT           (8U)
#define XRDC_MDA_W0_5_DFMT1_DIDB_WIDTH           (1U)
#define XRDC_MDA_W0_5_DFMT1_DIDB(x)              (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_5_DFMT1_DIDB_SHIFT)) & XRDC_MDA_W0_5_DFMT1_DIDB_MASK)

#define XRDC_MDA_W0_5_DFMT1_DFMT_MASK            (0x20000000U)
#define XRDC_MDA_W0_5_DFMT1_DFMT_SHIFT           (29U)
#define XRDC_MDA_W0_5_DFMT1_DFMT_WIDTH           (1U)
#define XRDC_MDA_W0_5_DFMT1_DFMT(x)              (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_5_DFMT1_DFMT_SHIFT)) & XRDC_MDA_W0_5_DFMT1_DFMT_MASK)

#define XRDC_MDA_W0_5_DFMT1_LK1_MASK             (0x40000000U)
#define XRDC_MDA_W0_5_DFMT1_LK1_SHIFT            (30U)
#define XRDC_MDA_W0_5_DFMT1_LK1_WIDTH            (1U)
#define XRDC_MDA_W0_5_DFMT1_LK1(x)               (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_5_DFMT1_LK1_SHIFT)) & XRDC_MDA_W0_5_DFMT1_LK1_MASK)

#define XRDC_MDA_W0_5_DFMT1_VLD_MASK             (0x80000000U)
#define XRDC_MDA_W0_5_DFMT1_VLD_SHIFT            (31U)
#define XRDC_MDA_W0_5_DFMT1_VLD_WIDTH            (1U)
#define XRDC_MDA_W0_5_DFMT1_VLD(x)               (((uint32_t)(((uint32_t)(x)) << XRDC_MDA_W0_5_DFMT1_VLD_SHIFT)) & XRDC_MDA_W0_5_DFMT1_VLD_MASK)
/*! @} */

/*! @name PDAC_W0 - Peripheral Domain Access Control Word 0 */
/*! @{ */

#define XRDC_PDAC_W0_D0ACP_MASK                  (0x7U)
#define XRDC_PDAC_W0_D0ACP_SHIFT                 (0U)
#define XRDC_PDAC_W0_D0ACP_WIDTH                 (3U)
#define XRDC_PDAC_W0_D0ACP(x)                    (((uint32_t)(((uint32_t)(x)) << XRDC_PDAC_W0_D0ACP_SHIFT)) & XRDC_PDAC_W0_D0ACP_MASK)

#define XRDC_PDAC_W0_D1ACP_MASK                  (0x38U)
#define XRDC_PDAC_W0_D1ACP_SHIFT                 (3U)
#define XRDC_PDAC_W0_D1ACP_WIDTH                 (3U)
#define XRDC_PDAC_W0_D1ACP(x)                    (((uint32_t)(((uint32_t)(x)) << XRDC_PDAC_W0_D1ACP_SHIFT)) & XRDC_PDAC_W0_D1ACP_MASK)

#define XRDC_PDAC_W0_D2ACP_MASK                  (0x1C0U)
#define XRDC_PDAC_W0_D2ACP_SHIFT                 (6U)
#define XRDC_PDAC_W0_D2ACP_WIDTH                 (3U)
#define XRDC_PDAC_W0_D2ACP(x)                    (((uint32_t)(((uint32_t)(x)) << XRDC_PDAC_W0_D2ACP_SHIFT)) & XRDC_PDAC_W0_D2ACP_MASK)

#define XRDC_PDAC_W0_SNUM_MASK                   (0xF000000U)
#define XRDC_PDAC_W0_SNUM_SHIFT                  (24U)
#define XRDC_PDAC_W0_SNUM_WIDTH                  (4U)
#define XRDC_PDAC_W0_SNUM(x)                     (((uint32_t)(((uint32_t)(x)) << XRDC_PDAC_W0_SNUM_SHIFT)) & XRDC_PDAC_W0_SNUM_MASK)

#define XRDC_PDAC_W0_SE_MASK                     (0x40000000U)
#define XRDC_PDAC_W0_SE_SHIFT                    (30U)
#define XRDC_PDAC_W0_SE_WIDTH                    (1U)
#define XRDC_PDAC_W0_SE(x)                       (((uint32_t)(((uint32_t)(x)) << XRDC_PDAC_W0_SE_SHIFT)) & XRDC_PDAC_W0_SE_MASK)
/*! @} */

/*! @name PDAC_W1 - Peripheral Domain Access Control Word 1 */
/*! @{ */

#define XRDC_PDAC_W1_LK2_MASK                    (0x60000000U)
#define XRDC_PDAC_W1_LK2_SHIFT                   (29U)
#define XRDC_PDAC_W1_LK2_WIDTH                   (2U)
#define XRDC_PDAC_W1_LK2(x)                      (((uint32_t)(((uint32_t)(x)) << XRDC_PDAC_W1_LK2_SHIFT)) & XRDC_PDAC_W1_LK2_MASK)

#define XRDC_PDAC_W1_VLD_MASK                    (0x80000000U)
#define XRDC_PDAC_W1_VLD_SHIFT                   (31U)
#define XRDC_PDAC_W1_VLD_WIDTH                   (1U)
#define XRDC_PDAC_W1_VLD(x)                      (((uint32_t)(((uint32_t)(x)) << XRDC_PDAC_W1_VLD_SHIFT)) & XRDC_PDAC_W1_VLD_MASK)
/*! @} */

/*! @name XRDC_MRGD_W0 - Memory Region Descriptor Word 0 */
/*! @{ */

#define XRDC_XRDC_MRGD_W0_SRTADDR_MASK           (0xFFFFFFE0U)
#define XRDC_XRDC_MRGD_W0_SRTADDR_SHIFT          (5U)
#define XRDC_XRDC_MRGD_W0_SRTADDR_WIDTH          (27U)
#define XRDC_XRDC_MRGD_W0_SRTADDR(x)             (((uint32_t)(((uint32_t)(x)) << XRDC_XRDC_MRGD_W0_SRTADDR_SHIFT)) & XRDC_XRDC_MRGD_W0_SRTADDR_MASK)
/*! @} */

/*! @name XRDC_MRGD_W1 - Memory Region Descriptor Word 1 */
/*! @{ */

#define XRDC_XRDC_MRGD_W1_ENDADDR_MASK           (0xFFFFFFE0U)
#define XRDC_XRDC_MRGD_W1_ENDADDR_SHIFT          (5U)
#define XRDC_XRDC_MRGD_W1_ENDADDR_WIDTH          (27U)
#define XRDC_XRDC_MRGD_W1_ENDADDR(x)             (((uint32_t)(((uint32_t)(x)) << XRDC_XRDC_MRGD_W1_ENDADDR_SHIFT)) & XRDC_XRDC_MRGD_W1_ENDADDR_MASK)
/*! @} */

/*! @name XRDC_MRGD_W2 - Memory Region Descriptor Word 2 */
/*! @{ */

#define XRDC_XRDC_MRGD_W2_D0ACP_MASK             (0x7U)
#define XRDC_XRDC_MRGD_W2_D0ACP_SHIFT            (0U)
#define XRDC_XRDC_MRGD_W2_D0ACP_WIDTH            (3U)
#define XRDC_XRDC_MRGD_W2_D0ACP(x)               (((uint32_t)(((uint32_t)(x)) << XRDC_XRDC_MRGD_W2_D0ACP_SHIFT)) & XRDC_XRDC_MRGD_W2_D0ACP_MASK)

#define XRDC_XRDC_MRGD_W2_D1ACP_MASK             (0x38U)
#define XRDC_XRDC_MRGD_W2_D1ACP_SHIFT            (3U)
#define XRDC_XRDC_MRGD_W2_D1ACP_WIDTH            (3U)
#define XRDC_XRDC_MRGD_W2_D1ACP(x)               (((uint32_t)(((uint32_t)(x)) << XRDC_XRDC_MRGD_W2_D1ACP_SHIFT)) & XRDC_XRDC_MRGD_W2_D1ACP_MASK)

#define XRDC_XRDC_MRGD_W2_D2ACP_MASK             (0x1C0U)
#define XRDC_XRDC_MRGD_W2_D2ACP_SHIFT            (6U)
#define XRDC_XRDC_MRGD_W2_D2ACP_WIDTH            (3U)
#define XRDC_XRDC_MRGD_W2_D2ACP(x)               (((uint32_t)(((uint32_t)(x)) << XRDC_XRDC_MRGD_W2_D2ACP_SHIFT)) & XRDC_XRDC_MRGD_W2_D2ACP_MASK)

#define XRDC_XRDC_MRGD_W2_SNUM_MASK              (0xF000000U)
#define XRDC_XRDC_MRGD_W2_SNUM_SHIFT             (24U)
#define XRDC_XRDC_MRGD_W2_SNUM_WIDTH             (4U)
#define XRDC_XRDC_MRGD_W2_SNUM(x)                (((uint32_t)(((uint32_t)(x)) << XRDC_XRDC_MRGD_W2_SNUM_SHIFT)) & XRDC_XRDC_MRGD_W2_SNUM_MASK)

#define XRDC_XRDC_MRGD_W2_SE_MASK                (0x40000000U)
#define XRDC_XRDC_MRGD_W2_SE_SHIFT               (30U)
#define XRDC_XRDC_MRGD_W2_SE_WIDTH               (1U)
#define XRDC_XRDC_MRGD_W2_SE(x)                  (((uint32_t)(((uint32_t)(x)) << XRDC_XRDC_MRGD_W2_SE_SHIFT)) & XRDC_XRDC_MRGD_W2_SE_MASK)
/*! @} */

/*! @name XRDC_MRGD_W3 - Memory Region Descriptor Word 3 */
/*! @{ */

#define XRDC_XRDC_MRGD_W3_LK2_MASK               (0x60000000U)
#define XRDC_XRDC_MRGD_W3_LK2_SHIFT              (29U)
#define XRDC_XRDC_MRGD_W3_LK2_WIDTH              (2U)
#define XRDC_XRDC_MRGD_W3_LK2(x)                 (((uint32_t)(((uint32_t)(x)) << XRDC_XRDC_MRGD_W3_LK2_SHIFT)) & XRDC_XRDC_MRGD_W3_LK2_MASK)

#define XRDC_XRDC_MRGD_W3_VLD_MASK               (0x80000000U)
#define XRDC_XRDC_MRGD_W3_VLD_SHIFT              (31U)
#define XRDC_XRDC_MRGD_W3_VLD_WIDTH              (1U)
#define XRDC_XRDC_MRGD_W3_VLD(x)                 (((uint32_t)(((uint32_t)(x)) << XRDC_XRDC_MRGD_W3_VLD_SHIFT)) & XRDC_XRDC_MRGD_W3_VLD_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group XRDC_Register_Masks */

/*!
 * @}
 */ /* end of group XRDC_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_XRDC_H_) */
