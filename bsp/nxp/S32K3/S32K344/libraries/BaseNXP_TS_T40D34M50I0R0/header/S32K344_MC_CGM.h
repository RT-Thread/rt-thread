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
 * @file S32K344_MC_CGM.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_MC_CGM
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
#if !defined(S32K344_MC_CGM_H_)  /* Check if memory map has not been already included */
#define S32K344_MC_CGM_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- MC_CGM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MC_CGM_Peripheral_Access_Layer MC_CGM Peripheral Access Layer
 * @{
 */

/** MC_CGM - Register Layout Typedef */
typedef struct {
  __IO uint32_t PCFS_SDUR;                         /**< PCFS Step Duration, offset: 0x0 */
  uint8_t RESERVED_0[84];
  __IO uint32_t PCFS_DIVC8;                        /**< PCFS Divider Change 8 Register, offset: 0x58 */
  __IO uint32_t PCFS_DIVE8;                        /**< PCFS Divider End 8 Register, offset: 0x5C */
  __IO uint32_t PCFS_DIVS8;                        /**< PCFS Divider Start 8 Register, offset: 0x60 */
  uint8_t RESERVED_1[668];
  __IO uint32_t MUX_0_CSC;                         /**< Clock Mux 0 Select Control Register, offset: 0x300 */
  __I  uint32_t MUX_0_CSS;                         /**< Clock Mux 0 Select Status Register, offset: 0x304 */
  __IO uint32_t MUX_0_DC_0;                        /**< Clock Mux 0 Divider 0 Control Register, offset: 0x308 */
  __IO uint32_t MUX_0_DC_1;                        /**< Clock Mux 0 Divider 1 Control Register, offset: 0x30C */
  __IO uint32_t MUX_0_DC_2;                        /**< Clock Mux 0 Divider 2 Control Register, offset: 0x310 */
  __IO uint32_t MUX_0_DC_3;                        /**< Clock Mux 0 Divider 3 Control Register, offset: 0x314 */
  __IO uint32_t MUX_0_DC_4;                        /**< Clock Mux 0 Divider 4 Control Register, offset: 0x318 */
  __IO uint32_t MUX_0_DC_5;                        /**< Clock Mux 0 Divider 5 Control Register, offset: 0x31C */
  __IO uint32_t MUX_0_DC_6;                        /**< Clock Mux 0 Divider 6 Control Register, offset: 0x320 */
  uint8_t RESERVED_2[16];
  __IO uint32_t MUX_0_DIV_TRIG_CTRL;               /**< Clock Mux 0 Divider Trigger Control Register, offset: 0x334 */
  __O  uint32_t MUX_0_DIV_TRIG;                    /**< Clock Mux 0 Divider Trigger Register, offset: 0x338 */
  __I  uint32_t MUX_0_DIV_UPD_STAT;                /**< Clock Mux 0 Divider Update Status Register, offset: 0x33C */
  __IO uint32_t MUX_1_CSC;                         /**< Clock Mux 1 Select Control Register, offset: 0x340 */
  __I  uint32_t MUX_1_CSS;                         /**< Clock Mux 1 Select Status Register, offset: 0x344 */
  __IO uint32_t MUX_1_DC_0;                        /**< Clock Mux 1 Divider 0 Control Register, offset: 0x348 */
  uint8_t RESERVED_3[48];
  __I  uint32_t MUX_1_DIV_UPD_STAT;                /**< Clock Mux 1 Divider Update Status Register, offset: 0x37C */
  __IO uint32_t MUX_2_CSC;                         /**< Clock Mux 2 Select Control Register, offset: 0x380 */
  __I  uint32_t MUX_2_CSS;                         /**< Clock Mux 2 Select Status Register, offset: 0x384 */
  __IO uint32_t MUX_2_DC_0;                        /**< Clock Mux 2 Divider 0 Control Register, offset: 0x388 */
  uint8_t RESERVED_4[48];
  __I  uint32_t MUX_2_DIV_UPD_STAT;                /**< Clock Mux 2 Divider Update Status Register, offset: 0x3BC */
  __IO uint32_t MUX_3_CSC;                         /**< Clock Mux 3 Select Control Register, offset: 0x3C0 */
  __I  uint32_t MUX_3_CSS;                         /**< Clock Mux 3 Select Status Register, offset: 0x3C4 */
  __IO uint32_t MUX_3_DC_0;                        /**< Clock Mux 3 Divider 0 Control Register, offset: 0x3C8 */
  uint8_t RESERVED_5[48];
  __I  uint32_t MUX_3_DIV_UPD_STAT;                /**< Clock Mux 3 Divider Update Status Register, offset: 0x3FC */
  __IO uint32_t MUX_4_CSC;                         /**< Clock Mux 4 Select Control Register, offset: 0x400 */
  __I  uint32_t MUX_4_CSS;                         /**< Clock Mux 4 Select Status Register, offset: 0x404 */
  __IO uint32_t MUX_4_DC_0;                        /**< Clock Mux 4 Divider 0 Control Register, offset: 0x408 */
  uint8_t RESERVED_6[48];
  __I  uint32_t MUX_4_DIV_UPD_STAT;                /**< Clock Mux 4 Divider Update Status Register, offset: 0x43C */
  __IO uint32_t MUX_5_CSC;                         /**< Clock Mux 5 Select Control Register, offset: 0x440 */
  __I  uint32_t MUX_5_CSS;                         /**< Clock Mux 5 Select Status Register, offset: 0x444 */
  __IO uint32_t MUX_5_DC_0;                        /**< Clock Mux 5 Divider 0 Control Register, offset: 0x448 */
  uint8_t RESERVED_7[48];
  __I  uint32_t MUX_5_DIV_UPD_STAT;                /**< Clock Mux 5 Divider Update Status Register, offset: 0x47C */
  __IO uint32_t MUX_6_CSC;                         /**< Clock Mux 6 Select Control Register, offset: 0x480 */
  __I  uint32_t MUX_6_CSS;                         /**< Clock Mux 6 Select Status Register, offset: 0x484 */
  __IO uint32_t MUX_6_DC_0;                        /**< Clock Mux 6 Divider 0 Control Register, offset: 0x488 */
  uint8_t RESERVED_8[48];
  __I  uint32_t MUX_6_DIV_UPD_STAT;                /**< Clock Mux 6 Divider Update Status Register, offset: 0x4BC */
  __IO uint32_t MUX_7_CSC;                         /**< Clock Mux 7 Select Control Register, offset: 0x4C0 */
  __I  uint32_t MUX_7_CSS;                         /**< Clock Mux 7 Select Status Register, offset: 0x4C4 */
  __IO uint32_t MUX_7_DC_0;                        /**< Clock Mux 7 Divider 0 Control Register, offset: 0x4C8 */
  uint8_t RESERVED_9[48];
  __I  uint32_t MUX_7_DIV_UPD_STAT;                /**< Clock Mux 7 Divider Update Status Register, offset: 0x4FC */
  __IO uint32_t MUX_8_CSC;                         /**< Clock Mux 8 Select Control Register, offset: 0x500 */
  __I  uint32_t MUX_8_CSS;                         /**< Clock Mux 8 Select Status Register, offset: 0x504 */
  __IO uint32_t MUX_8_DC_0;                        /**< Clock Mux 8 Divider 0 Control Register, offset: 0x508 */
  uint8_t RESERVED_10[48];
  __I  uint32_t MUX_8_DIV_UPD_STAT;                /**< Clock Mux 8 Divider Update Status Register, offset: 0x53C */
  __IO uint32_t MUX_9_CSC;                         /**< Clock Mux 9 Select Control Register, offset: 0x540 */
  __I  uint32_t MUX_9_CSS;                         /**< Clock Mux 9 Select Status Register, offset: 0x544 */
  __IO uint32_t MUX_9_DC_0;                        /**< Clock Mux 9 Divider 0 Control Register, offset: 0x548 */
  uint8_t RESERVED_11[48];
  __I  uint32_t MUX_9_DIV_UPD_STAT;                /**< Clock Mux 9 Divider Update Status Register, offset: 0x57C */
  __IO uint32_t MUX_10_CSC;                        /**< Clock Mux 10 Select Control Register, offset: 0x580 */
  __I  uint32_t MUX_10_CSS;                        /**< Clock Mux 10 Select Status Register, offset: 0x584 */
  __IO uint32_t MUX_10_DC_0;                       /**< Clock Mux 10 Divider 0 Control Register, offset: 0x588 */
  uint8_t RESERVED_12[48];
  __I  uint32_t MUX_10_DIV_UPD_STAT;               /**< Clock Mux 10 Divider Update Status Register, offset: 0x5BC */
  __IO uint32_t MUX_11_CSC;                        /**< Clock Mux 11 Select Control Register, offset: 0x5C0 */
  __I  uint32_t MUX_11_CSS;                        /**< Clock Mux 11 Select Status Register, offset: 0x5C4 */
  __IO uint32_t MUX_11_DC_0;                       /**< Clock Mux 11 Divider 0 Control Register, offset: 0x5C8 */
  uint8_t RESERVED_13[48];
  __I  uint32_t MUX_11_DIV_UPD_STAT;               /**< Clock Mux 11 Divider Update Status Register, offset: 0x5FC */
} MC_CGM_Type, *MC_CGM_MemMapPtr;

/** Number of instances of the MC_CGM module. */
#define MC_CGM_INSTANCE_COUNT                    (1u)

/* MC_CGM - Peripheral instance base addresses */
/** Peripheral MC_CGM base address */
#define IP_MC_CGM_BASE                           (0x402D8000u)
/** Peripheral MC_CGM base pointer */
#define IP_MC_CGM                                ((MC_CGM_Type *)IP_MC_CGM_BASE)
/** Array initializer of MC_CGM peripheral base addresses */
#define IP_MC_CGM_BASE_ADDRS                     { IP_MC_CGM_BASE }
/** Array initializer of MC_CGM peripheral base pointers */
#define IP_MC_CGM_BASE_PTRS                      { IP_MC_CGM }

/* ----------------------------------------------------------------------------
   -- MC_CGM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MC_CGM_Register_Masks MC_CGM Register Masks
 * @{
 */

/*! @name PCFS_SDUR - PCFS Step Duration */
/*! @{ */

#define MC_CGM_PCFS_SDUR_SDUR_MASK               (0xFFFFU)
#define MC_CGM_PCFS_SDUR_SDUR_SHIFT              (0U)
#define MC_CGM_PCFS_SDUR_SDUR_WIDTH              (16U)
#define MC_CGM_PCFS_SDUR_SDUR(x)                 (((uint32_t)(((uint32_t)(x)) << MC_CGM_PCFS_SDUR_SDUR_SHIFT)) & MC_CGM_PCFS_SDUR_SDUR_MASK)
/*! @} */

/*! @name PCFS_DIVC8 - PCFS Divider Change 8 Register */
/*! @{ */

#define MC_CGM_PCFS_DIVC8_RATE_MASK              (0xFFU)
#define MC_CGM_PCFS_DIVC8_RATE_SHIFT             (0U)
#define MC_CGM_PCFS_DIVC8_RATE_WIDTH             (8U)
#define MC_CGM_PCFS_DIVC8_RATE(x)                (((uint32_t)(((uint32_t)(x)) << MC_CGM_PCFS_DIVC8_RATE_SHIFT)) & MC_CGM_PCFS_DIVC8_RATE_MASK)

#define MC_CGM_PCFS_DIVC8_INIT_MASK              (0xFFFF0000U)
#define MC_CGM_PCFS_DIVC8_INIT_SHIFT             (16U)
#define MC_CGM_PCFS_DIVC8_INIT_WIDTH             (16U)
#define MC_CGM_PCFS_DIVC8_INIT(x)                (((uint32_t)(((uint32_t)(x)) << MC_CGM_PCFS_DIVC8_INIT_SHIFT)) & MC_CGM_PCFS_DIVC8_INIT_MASK)
/*! @} */

/*! @name PCFS_DIVE8 - PCFS Divider End 8 Register */
/*! @{ */

#define MC_CGM_PCFS_DIVE8_DIVE_MASK              (0xFFFFFU)
#define MC_CGM_PCFS_DIVE8_DIVE_SHIFT             (0U)
#define MC_CGM_PCFS_DIVE8_DIVE_WIDTH             (20U)
#define MC_CGM_PCFS_DIVE8_DIVE(x)                (((uint32_t)(((uint32_t)(x)) << MC_CGM_PCFS_DIVE8_DIVE_SHIFT)) & MC_CGM_PCFS_DIVE8_DIVE_MASK)
/*! @} */

/*! @name PCFS_DIVS8 - PCFS Divider Start 8 Register */
/*! @{ */

#define MC_CGM_PCFS_DIVS8_DIVS_MASK              (0xFFFFFU)
#define MC_CGM_PCFS_DIVS8_DIVS_SHIFT             (0U)
#define MC_CGM_PCFS_DIVS8_DIVS_WIDTH             (20U)
#define MC_CGM_PCFS_DIVS8_DIVS(x)                (((uint32_t)(((uint32_t)(x)) << MC_CGM_PCFS_DIVS8_DIVS_SHIFT)) & MC_CGM_PCFS_DIVS8_DIVS_MASK)
/*! @} */

/*! @name MUX_0_CSC - Clock Mux 0 Select Control Register */
/*! @{ */

#define MC_CGM_MUX_0_CSC_RAMPUP_MASK             (0x1U)
#define MC_CGM_MUX_0_CSC_RAMPUP_SHIFT            (0U)
#define MC_CGM_MUX_0_CSC_RAMPUP_WIDTH            (1U)
#define MC_CGM_MUX_0_CSC_RAMPUP(x)               (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_CSC_RAMPUP_SHIFT)) & MC_CGM_MUX_0_CSC_RAMPUP_MASK)

#define MC_CGM_MUX_0_CSC_RAMPDOWN_MASK           (0x2U)
#define MC_CGM_MUX_0_CSC_RAMPDOWN_SHIFT          (1U)
#define MC_CGM_MUX_0_CSC_RAMPDOWN_WIDTH          (1U)
#define MC_CGM_MUX_0_CSC_RAMPDOWN(x)             (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_CSC_RAMPDOWN_SHIFT)) & MC_CGM_MUX_0_CSC_RAMPDOWN_MASK)

#define MC_CGM_MUX_0_CSC_CLK_SW_MASK             (0x4U)
#define MC_CGM_MUX_0_CSC_CLK_SW_SHIFT            (2U)
#define MC_CGM_MUX_0_CSC_CLK_SW_WIDTH            (1U)
#define MC_CGM_MUX_0_CSC_CLK_SW(x)               (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_CSC_CLK_SW_SHIFT)) & MC_CGM_MUX_0_CSC_CLK_SW_MASK)

#define MC_CGM_MUX_0_CSC_SAFE_SW_MASK            (0x8U)
#define MC_CGM_MUX_0_CSC_SAFE_SW_SHIFT           (3U)
#define MC_CGM_MUX_0_CSC_SAFE_SW_WIDTH           (1U)
#define MC_CGM_MUX_0_CSC_SAFE_SW(x)              (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_CSC_SAFE_SW_SHIFT)) & MC_CGM_MUX_0_CSC_SAFE_SW_MASK)

#define MC_CGM_MUX_0_CSC_SELCTL_MASK             (0xF000000U)
#define MC_CGM_MUX_0_CSC_SELCTL_SHIFT            (24U)
#define MC_CGM_MUX_0_CSC_SELCTL_WIDTH            (4U)
#define MC_CGM_MUX_0_CSC_SELCTL(x)               (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_CSC_SELCTL_SHIFT)) & MC_CGM_MUX_0_CSC_SELCTL_MASK)
/*! @} */

/*! @name MUX_0_CSS - Clock Mux 0 Select Status Register */
/*! @{ */

#define MC_CGM_MUX_0_CSS_RAMPUP_MASK             (0x1U)
#define MC_CGM_MUX_0_CSS_RAMPUP_SHIFT            (0U)
#define MC_CGM_MUX_0_CSS_RAMPUP_WIDTH            (1U)
#define MC_CGM_MUX_0_CSS_RAMPUP(x)               (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_CSS_RAMPUP_SHIFT)) & MC_CGM_MUX_0_CSS_RAMPUP_MASK)

#define MC_CGM_MUX_0_CSS_RAMPDOWN_MASK           (0x2U)
#define MC_CGM_MUX_0_CSS_RAMPDOWN_SHIFT          (1U)
#define MC_CGM_MUX_0_CSS_RAMPDOWN_WIDTH          (1U)
#define MC_CGM_MUX_0_CSS_RAMPDOWN(x)             (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_CSS_RAMPDOWN_SHIFT)) & MC_CGM_MUX_0_CSS_RAMPDOWN_MASK)

#define MC_CGM_MUX_0_CSS_CLK_SW_MASK             (0x4U)
#define MC_CGM_MUX_0_CSS_CLK_SW_SHIFT            (2U)
#define MC_CGM_MUX_0_CSS_CLK_SW_WIDTH            (1U)
#define MC_CGM_MUX_0_CSS_CLK_SW(x)               (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_CSS_CLK_SW_SHIFT)) & MC_CGM_MUX_0_CSS_CLK_SW_MASK)

#define MC_CGM_MUX_0_CSS_SAFE_SW_MASK            (0x8U)
#define MC_CGM_MUX_0_CSS_SAFE_SW_SHIFT           (3U)
#define MC_CGM_MUX_0_CSS_SAFE_SW_WIDTH           (1U)
#define MC_CGM_MUX_0_CSS_SAFE_SW(x)              (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_CSS_SAFE_SW_SHIFT)) & MC_CGM_MUX_0_CSS_SAFE_SW_MASK)

#define MC_CGM_MUX_0_CSS_SWIP_MASK               (0x10000U)
#define MC_CGM_MUX_0_CSS_SWIP_SHIFT              (16U)
#define MC_CGM_MUX_0_CSS_SWIP_WIDTH              (1U)
#define MC_CGM_MUX_0_CSS_SWIP(x)                 (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_CSS_SWIP_SHIFT)) & MC_CGM_MUX_0_CSS_SWIP_MASK)

#define MC_CGM_MUX_0_CSS_SWTRG_MASK              (0xE0000U)
#define MC_CGM_MUX_0_CSS_SWTRG_SHIFT             (17U)
#define MC_CGM_MUX_0_CSS_SWTRG_WIDTH             (3U)
#define MC_CGM_MUX_0_CSS_SWTRG(x)                (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_CSS_SWTRG_SHIFT)) & MC_CGM_MUX_0_CSS_SWTRG_MASK)

#define MC_CGM_MUX_0_CSS_SELSTAT_MASK            (0xF000000U)
#define MC_CGM_MUX_0_CSS_SELSTAT_SHIFT           (24U)
#define MC_CGM_MUX_0_CSS_SELSTAT_WIDTH           (4U)
#define MC_CGM_MUX_0_CSS_SELSTAT(x)              (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_CSS_SELSTAT_SHIFT)) & MC_CGM_MUX_0_CSS_SELSTAT_MASK)
/*! @} */

/*! @name MUX_0_DC_0 - Clock Mux 0 Divider 0 Control Register */
/*! @{ */

#define MC_CGM_MUX_0_DC_0_DIV_MASK               (0x70000U)
#define MC_CGM_MUX_0_DC_0_DIV_SHIFT              (16U)
#define MC_CGM_MUX_0_DC_0_DIV_WIDTH              (3U)
#define MC_CGM_MUX_0_DC_0_DIV(x)                 (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_DC_0_DIV_SHIFT)) & MC_CGM_MUX_0_DC_0_DIV_MASK)

#define MC_CGM_MUX_0_DC_0_DE_MASK                (0x80000000U)
#define MC_CGM_MUX_0_DC_0_DE_SHIFT               (31U)
#define MC_CGM_MUX_0_DC_0_DE_WIDTH               (1U)
#define MC_CGM_MUX_0_DC_0_DE(x)                  (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_DC_0_DE_SHIFT)) & MC_CGM_MUX_0_DC_0_DE_MASK)
/*! @} */

/*! @name MUX_0_DC_1 - Clock Mux 0 Divider 1 Control Register */
/*! @{ */

#define MC_CGM_MUX_0_DC_1_DIV_MASK               (0x70000U)
#define MC_CGM_MUX_0_DC_1_DIV_SHIFT              (16U)
#define MC_CGM_MUX_0_DC_1_DIV_WIDTH              (3U)
#define MC_CGM_MUX_0_DC_1_DIV(x)                 (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_DC_1_DIV_SHIFT)) & MC_CGM_MUX_0_DC_1_DIV_MASK)

#define MC_CGM_MUX_0_DC_1_DE_MASK                (0x80000000U)
#define MC_CGM_MUX_0_DC_1_DE_SHIFT               (31U)
#define MC_CGM_MUX_0_DC_1_DE_WIDTH               (1U)
#define MC_CGM_MUX_0_DC_1_DE(x)                  (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_DC_1_DE_SHIFT)) & MC_CGM_MUX_0_DC_1_DE_MASK)
/*! @} */

/*! @name MUX_0_DC_2 - Clock Mux 0 Divider 2 Control Register */
/*! @{ */

#define MC_CGM_MUX_0_DC_2_DIV_MASK               (0xF0000U)
#define MC_CGM_MUX_0_DC_2_DIV_SHIFT              (16U)
#define MC_CGM_MUX_0_DC_2_DIV_WIDTH              (4U)
#define MC_CGM_MUX_0_DC_2_DIV(x)                 (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_DC_2_DIV_SHIFT)) & MC_CGM_MUX_0_DC_2_DIV_MASK)

#define MC_CGM_MUX_0_DC_2_DE_MASK                (0x80000000U)
#define MC_CGM_MUX_0_DC_2_DE_SHIFT               (31U)
#define MC_CGM_MUX_0_DC_2_DE_WIDTH               (1U)
#define MC_CGM_MUX_0_DC_2_DE(x)                  (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_DC_2_DE_SHIFT)) & MC_CGM_MUX_0_DC_2_DE_MASK)
/*! @} */

/*! @name MUX_0_DC_3 - Clock Mux 0 Divider 3 Control Register */
/*! @{ */

#define MC_CGM_MUX_0_DC_3_DIV_MASK               (0x70000U)
#define MC_CGM_MUX_0_DC_3_DIV_SHIFT              (16U)
#define MC_CGM_MUX_0_DC_3_DIV_WIDTH              (3U)
#define MC_CGM_MUX_0_DC_3_DIV(x)                 (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_DC_3_DIV_SHIFT)) & MC_CGM_MUX_0_DC_3_DIV_MASK)

#define MC_CGM_MUX_0_DC_3_DE_MASK                (0x80000000U)
#define MC_CGM_MUX_0_DC_3_DE_SHIFT               (31U)
#define MC_CGM_MUX_0_DC_3_DE_WIDTH               (1U)
#define MC_CGM_MUX_0_DC_3_DE(x)                  (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_DC_3_DE_SHIFT)) & MC_CGM_MUX_0_DC_3_DE_MASK)
/*! @} */

/*! @name MUX_0_DC_4 - Clock Mux 0 Divider 4 Control Register */
/*! @{ */

#define MC_CGM_MUX_0_DC_4_DIV_MASK               (0x70000U)
#define MC_CGM_MUX_0_DC_4_DIV_SHIFT              (16U)
#define MC_CGM_MUX_0_DC_4_DIV_WIDTH              (3U)
#define MC_CGM_MUX_0_DC_4_DIV(x)                 (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_DC_4_DIV_SHIFT)) & MC_CGM_MUX_0_DC_4_DIV_MASK)

#define MC_CGM_MUX_0_DC_4_DE_MASK                (0x80000000U)
#define MC_CGM_MUX_0_DC_4_DE_SHIFT               (31U)
#define MC_CGM_MUX_0_DC_4_DE_WIDTH               (1U)
#define MC_CGM_MUX_0_DC_4_DE(x)                  (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_DC_4_DE_SHIFT)) & MC_CGM_MUX_0_DC_4_DE_MASK)
/*! @} */

/*! @name MUX_0_DC_5 - Clock Mux 0 Divider 5 Control Register */
/*! @{ */

#define MC_CGM_MUX_0_DC_5_DIV_MASK               (0x70000U)
#define MC_CGM_MUX_0_DC_5_DIV_SHIFT              (16U)
#define MC_CGM_MUX_0_DC_5_DIV_WIDTH              (3U)
#define MC_CGM_MUX_0_DC_5_DIV(x)                 (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_DC_5_DIV_SHIFT)) & MC_CGM_MUX_0_DC_5_DIV_MASK)

#define MC_CGM_MUX_0_DC_5_DE_MASK                (0x80000000U)
#define MC_CGM_MUX_0_DC_5_DE_SHIFT               (31U)
#define MC_CGM_MUX_0_DC_5_DE_WIDTH               (1U)
#define MC_CGM_MUX_0_DC_5_DE(x)                  (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_DC_5_DE_SHIFT)) & MC_CGM_MUX_0_DC_5_DE_MASK)
/*! @} */

/*! @name MUX_0_DC_6 - Clock Mux 0 Divider 6 Control Register */
/*! @{ */

#define MC_CGM_MUX_0_DC_6_DIV_MASK               (0x70000U)
#define MC_CGM_MUX_0_DC_6_DIV_SHIFT              (16U)
#define MC_CGM_MUX_0_DC_6_DIV_WIDTH              (3U)
#define MC_CGM_MUX_0_DC_6_DIV(x)                 (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_DC_6_DIV_SHIFT)) & MC_CGM_MUX_0_DC_6_DIV_MASK)

#define MC_CGM_MUX_0_DC_6_DE_MASK                (0x80000000U)
#define MC_CGM_MUX_0_DC_6_DE_SHIFT               (31U)
#define MC_CGM_MUX_0_DC_6_DE_WIDTH               (1U)
#define MC_CGM_MUX_0_DC_6_DE(x)                  (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_DC_6_DE_SHIFT)) & MC_CGM_MUX_0_DC_6_DE_MASK)
/*! @} */

/*! @name MUX_0_DIV_TRIG_CTRL - Clock Mux 0 Divider Trigger Control Register */
/*! @{ */

#define MC_CGM_MUX_0_DIV_TRIG_CTRL_TCTL_MASK     (0x1U)
#define MC_CGM_MUX_0_DIV_TRIG_CTRL_TCTL_SHIFT    (0U)
#define MC_CGM_MUX_0_DIV_TRIG_CTRL_TCTL_WIDTH    (1U)
#define MC_CGM_MUX_0_DIV_TRIG_CTRL_TCTL(x)       (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_DIV_TRIG_CTRL_TCTL_SHIFT)) & MC_CGM_MUX_0_DIV_TRIG_CTRL_TCTL_MASK)

#define MC_CGM_MUX_0_DIV_TRIG_CTRL_HHEN_MASK     (0x80000000U)
#define MC_CGM_MUX_0_DIV_TRIG_CTRL_HHEN_SHIFT    (31U)
#define MC_CGM_MUX_0_DIV_TRIG_CTRL_HHEN_WIDTH    (1U)
#define MC_CGM_MUX_0_DIV_TRIG_CTRL_HHEN(x)       (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_DIV_TRIG_CTRL_HHEN_SHIFT)) & MC_CGM_MUX_0_DIV_TRIG_CTRL_HHEN_MASK)
/*! @} */

/*! @name MUX_0_DIV_TRIG - Clock Mux 0 Divider Trigger Register */
/*! @{ */

#define MC_CGM_MUX_0_DIV_TRIG_TRIGGER_MASK       (0xFFFFFFFFU)
#define MC_CGM_MUX_0_DIV_TRIG_TRIGGER_SHIFT      (0U)
#define MC_CGM_MUX_0_DIV_TRIG_TRIGGER_WIDTH      (32U)
#define MC_CGM_MUX_0_DIV_TRIG_TRIGGER(x)         (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_DIV_TRIG_TRIGGER_SHIFT)) & MC_CGM_MUX_0_DIV_TRIG_TRIGGER_MASK)
/*! @} */

/*! @name MUX_0_DIV_UPD_STAT - Clock Mux 0 Divider Update Status Register */
/*! @{ */

#define MC_CGM_MUX_0_DIV_UPD_STAT_DIV_STAT_MASK  (0x1U)
#define MC_CGM_MUX_0_DIV_UPD_STAT_DIV_STAT_SHIFT (0U)
#define MC_CGM_MUX_0_DIV_UPD_STAT_DIV_STAT_WIDTH (1U)
#define MC_CGM_MUX_0_DIV_UPD_STAT_DIV_STAT(x)    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_0_DIV_UPD_STAT_DIV_STAT_SHIFT)) & MC_CGM_MUX_0_DIV_UPD_STAT_DIV_STAT_MASK)
/*! @} */

/*! @name MUX_1_CSC - Clock Mux 1 Select Control Register */
/*! @{ */

#define MC_CGM_MUX_1_CSC_CLK_SW_MASK             (0x4U)
#define MC_CGM_MUX_1_CSC_CLK_SW_SHIFT            (2U)
#define MC_CGM_MUX_1_CSC_CLK_SW_WIDTH            (1U)
#define MC_CGM_MUX_1_CSC_CLK_SW(x)               (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_1_CSC_CLK_SW_SHIFT)) & MC_CGM_MUX_1_CSC_CLK_SW_MASK)

#define MC_CGM_MUX_1_CSC_SAFE_SW_MASK            (0x8U)
#define MC_CGM_MUX_1_CSC_SAFE_SW_SHIFT           (3U)
#define MC_CGM_MUX_1_CSC_SAFE_SW_WIDTH           (1U)
#define MC_CGM_MUX_1_CSC_SAFE_SW(x)              (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_1_CSC_SAFE_SW_SHIFT)) & MC_CGM_MUX_1_CSC_SAFE_SW_MASK)

#define MC_CGM_MUX_1_CSC_SELCTL_MASK             (0x1F000000U)
#define MC_CGM_MUX_1_CSC_SELCTL_SHIFT            (24U)
#define MC_CGM_MUX_1_CSC_SELCTL_WIDTH            (5U)
#define MC_CGM_MUX_1_CSC_SELCTL(x)               (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_1_CSC_SELCTL_SHIFT)) & MC_CGM_MUX_1_CSC_SELCTL_MASK)
/*! @} */

/*! @name MUX_1_CSS - Clock Mux 1 Select Status Register */
/*! @{ */

#define MC_CGM_MUX_1_CSS_CLK_SW_MASK             (0x4U)
#define MC_CGM_MUX_1_CSS_CLK_SW_SHIFT            (2U)
#define MC_CGM_MUX_1_CSS_CLK_SW_WIDTH            (1U)
#define MC_CGM_MUX_1_CSS_CLK_SW(x)               (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_1_CSS_CLK_SW_SHIFT)) & MC_CGM_MUX_1_CSS_CLK_SW_MASK)

#define MC_CGM_MUX_1_CSS_SAFE_SW_MASK            (0x8U)
#define MC_CGM_MUX_1_CSS_SAFE_SW_SHIFT           (3U)
#define MC_CGM_MUX_1_CSS_SAFE_SW_WIDTH           (1U)
#define MC_CGM_MUX_1_CSS_SAFE_SW(x)              (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_1_CSS_SAFE_SW_SHIFT)) & MC_CGM_MUX_1_CSS_SAFE_SW_MASK)

#define MC_CGM_MUX_1_CSS_SWIP_MASK               (0x10000U)
#define MC_CGM_MUX_1_CSS_SWIP_SHIFT              (16U)
#define MC_CGM_MUX_1_CSS_SWIP_WIDTH              (1U)
#define MC_CGM_MUX_1_CSS_SWIP(x)                 (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_1_CSS_SWIP_SHIFT)) & MC_CGM_MUX_1_CSS_SWIP_MASK)

#define MC_CGM_MUX_1_CSS_SWTRG_MASK              (0xE0000U)
#define MC_CGM_MUX_1_CSS_SWTRG_SHIFT             (17U)
#define MC_CGM_MUX_1_CSS_SWTRG_WIDTH             (3U)
#define MC_CGM_MUX_1_CSS_SWTRG(x)                (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_1_CSS_SWTRG_SHIFT)) & MC_CGM_MUX_1_CSS_SWTRG_MASK)

#define MC_CGM_MUX_1_CSS_SELSTAT_MASK            (0x1F000000U)
#define MC_CGM_MUX_1_CSS_SELSTAT_SHIFT           (24U)
#define MC_CGM_MUX_1_CSS_SELSTAT_WIDTH           (5U)
#define MC_CGM_MUX_1_CSS_SELSTAT(x)              (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_1_CSS_SELSTAT_SHIFT)) & MC_CGM_MUX_1_CSS_SELSTAT_MASK)
/*! @} */

/*! @name MUX_1_DC_0 - Clock Mux 1 Divider 0 Control Register */
/*! @{ */

#define MC_CGM_MUX_1_DC_0_DIV_MASK               (0x10000U)
#define MC_CGM_MUX_1_DC_0_DIV_SHIFT              (16U)
#define MC_CGM_MUX_1_DC_0_DIV_WIDTH              (1U)
#define MC_CGM_MUX_1_DC_0_DIV(x)                 (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_1_DC_0_DIV_SHIFT)) & MC_CGM_MUX_1_DC_0_DIV_MASK)

#define MC_CGM_MUX_1_DC_0_DE_MASK                (0x80000000U)
#define MC_CGM_MUX_1_DC_0_DE_SHIFT               (31U)
#define MC_CGM_MUX_1_DC_0_DE_WIDTH               (1U)
#define MC_CGM_MUX_1_DC_0_DE(x)                  (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_1_DC_0_DE_SHIFT)) & MC_CGM_MUX_1_DC_0_DE_MASK)
/*! @} */

/*! @name MUX_1_DIV_UPD_STAT - Clock Mux 1 Divider Update Status Register */
/*! @{ */

#define MC_CGM_MUX_1_DIV_UPD_STAT_DIV_STAT_MASK  (0x1U)
#define MC_CGM_MUX_1_DIV_UPD_STAT_DIV_STAT_SHIFT (0U)
#define MC_CGM_MUX_1_DIV_UPD_STAT_DIV_STAT_WIDTH (1U)
#define MC_CGM_MUX_1_DIV_UPD_STAT_DIV_STAT(x)    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_1_DIV_UPD_STAT_DIV_STAT_SHIFT)) & MC_CGM_MUX_1_DIV_UPD_STAT_DIV_STAT_MASK)
/*! @} */

/*! @name MUX_2_CSC - Clock Mux 2 Select Control Register */
/*! @{ */

#define MC_CGM_MUX_2_CSC_CLK_SW_MASK             (0x4U)
#define MC_CGM_MUX_2_CSC_CLK_SW_SHIFT            (2U)
#define MC_CGM_MUX_2_CSC_CLK_SW_WIDTH            (1U)
#define MC_CGM_MUX_2_CSC_CLK_SW(x)               (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_2_CSC_CLK_SW_SHIFT)) & MC_CGM_MUX_2_CSC_CLK_SW_MASK)

#define MC_CGM_MUX_2_CSC_SAFE_SW_MASK            (0x8U)
#define MC_CGM_MUX_2_CSC_SAFE_SW_SHIFT           (3U)
#define MC_CGM_MUX_2_CSC_SAFE_SW_WIDTH           (1U)
#define MC_CGM_MUX_2_CSC_SAFE_SW(x)              (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_2_CSC_SAFE_SW_SHIFT)) & MC_CGM_MUX_2_CSC_SAFE_SW_MASK)

#define MC_CGM_MUX_2_CSC_SELCTL_MASK             (0x1F000000U)
#define MC_CGM_MUX_2_CSC_SELCTL_SHIFT            (24U)
#define MC_CGM_MUX_2_CSC_SELCTL_WIDTH            (5U)
#define MC_CGM_MUX_2_CSC_SELCTL(x)               (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_2_CSC_SELCTL_SHIFT)) & MC_CGM_MUX_2_CSC_SELCTL_MASK)
/*! @} */

/*! @name MUX_2_CSS - Clock Mux 2 Select Status Register */
/*! @{ */

#define MC_CGM_MUX_2_CSS_CLK_SW_MASK             (0x4U)
#define MC_CGM_MUX_2_CSS_CLK_SW_SHIFT            (2U)
#define MC_CGM_MUX_2_CSS_CLK_SW_WIDTH            (1U)
#define MC_CGM_MUX_2_CSS_CLK_SW(x)               (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_2_CSS_CLK_SW_SHIFT)) & MC_CGM_MUX_2_CSS_CLK_SW_MASK)

#define MC_CGM_MUX_2_CSS_SAFE_SW_MASK            (0x8U)
#define MC_CGM_MUX_2_CSS_SAFE_SW_SHIFT           (3U)
#define MC_CGM_MUX_2_CSS_SAFE_SW_WIDTH           (1U)
#define MC_CGM_MUX_2_CSS_SAFE_SW(x)              (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_2_CSS_SAFE_SW_SHIFT)) & MC_CGM_MUX_2_CSS_SAFE_SW_MASK)

#define MC_CGM_MUX_2_CSS_SWIP_MASK               (0x10000U)
#define MC_CGM_MUX_2_CSS_SWIP_SHIFT              (16U)
#define MC_CGM_MUX_2_CSS_SWIP_WIDTH              (1U)
#define MC_CGM_MUX_2_CSS_SWIP(x)                 (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_2_CSS_SWIP_SHIFT)) & MC_CGM_MUX_2_CSS_SWIP_MASK)

#define MC_CGM_MUX_2_CSS_SWTRG_MASK              (0xE0000U)
#define MC_CGM_MUX_2_CSS_SWTRG_SHIFT             (17U)
#define MC_CGM_MUX_2_CSS_SWTRG_WIDTH             (3U)
#define MC_CGM_MUX_2_CSS_SWTRG(x)                (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_2_CSS_SWTRG_SHIFT)) & MC_CGM_MUX_2_CSS_SWTRG_MASK)

#define MC_CGM_MUX_2_CSS_SELSTAT_MASK            (0x1F000000U)
#define MC_CGM_MUX_2_CSS_SELSTAT_SHIFT           (24U)
#define MC_CGM_MUX_2_CSS_SELSTAT_WIDTH           (5U)
#define MC_CGM_MUX_2_CSS_SELSTAT(x)              (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_2_CSS_SELSTAT_SHIFT)) & MC_CGM_MUX_2_CSS_SELSTAT_MASK)
/*! @} */

/*! @name MUX_2_DC_0 - Clock Mux 2 Divider 0 Control Register */
/*! @{ */

#define MC_CGM_MUX_2_DC_0_DIV_MASK               (0x10000U)
#define MC_CGM_MUX_2_DC_0_DIV_SHIFT              (16U)
#define MC_CGM_MUX_2_DC_0_DIV_WIDTH              (1U)
#define MC_CGM_MUX_2_DC_0_DIV(x)                 (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_2_DC_0_DIV_SHIFT)) & MC_CGM_MUX_2_DC_0_DIV_MASK)

#define MC_CGM_MUX_2_DC_0_DE_MASK                (0x80000000U)
#define MC_CGM_MUX_2_DC_0_DE_SHIFT               (31U)
#define MC_CGM_MUX_2_DC_0_DE_WIDTH               (1U)
#define MC_CGM_MUX_2_DC_0_DE(x)                  (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_2_DC_0_DE_SHIFT)) & MC_CGM_MUX_2_DC_0_DE_MASK)
/*! @} */

/*! @name MUX_2_DIV_UPD_STAT - Clock Mux 2 Divider Update Status Register */
/*! @{ */

#define MC_CGM_MUX_2_DIV_UPD_STAT_DIV_STAT_MASK  (0x1U)
#define MC_CGM_MUX_2_DIV_UPD_STAT_DIV_STAT_SHIFT (0U)
#define MC_CGM_MUX_2_DIV_UPD_STAT_DIV_STAT_WIDTH (1U)
#define MC_CGM_MUX_2_DIV_UPD_STAT_DIV_STAT(x)    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_2_DIV_UPD_STAT_DIV_STAT_SHIFT)) & MC_CGM_MUX_2_DIV_UPD_STAT_DIV_STAT_MASK)
/*! @} */

/*! @name MUX_3_CSC - Clock Mux 3 Select Control Register */
/*! @{ */

#define MC_CGM_MUX_3_CSC_CLK_SW_MASK             (0x4U)
#define MC_CGM_MUX_3_CSC_CLK_SW_SHIFT            (2U)
#define MC_CGM_MUX_3_CSC_CLK_SW_WIDTH            (1U)
#define MC_CGM_MUX_3_CSC_CLK_SW(x)               (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_CSC_CLK_SW_SHIFT)) & MC_CGM_MUX_3_CSC_CLK_SW_MASK)

#define MC_CGM_MUX_3_CSC_SAFE_SW_MASK            (0x8U)
#define MC_CGM_MUX_3_CSC_SAFE_SW_SHIFT           (3U)
#define MC_CGM_MUX_3_CSC_SAFE_SW_WIDTH           (1U)
#define MC_CGM_MUX_3_CSC_SAFE_SW(x)              (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_CSC_SAFE_SW_SHIFT)) & MC_CGM_MUX_3_CSC_SAFE_SW_MASK)

#define MC_CGM_MUX_3_CSC_SELCTL_MASK             (0x1F000000U)
#define MC_CGM_MUX_3_CSC_SELCTL_SHIFT            (24U)
#define MC_CGM_MUX_3_CSC_SELCTL_WIDTH            (5U)
#define MC_CGM_MUX_3_CSC_SELCTL(x)               (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_CSC_SELCTL_SHIFT)) & MC_CGM_MUX_3_CSC_SELCTL_MASK)
/*! @} */

/*! @name MUX_3_CSS - Clock Mux 3 Select Status Register */
/*! @{ */

#define MC_CGM_MUX_3_CSS_CLK_SW_MASK             (0x4U)
#define MC_CGM_MUX_3_CSS_CLK_SW_SHIFT            (2U)
#define MC_CGM_MUX_3_CSS_CLK_SW_WIDTH            (1U)
#define MC_CGM_MUX_3_CSS_CLK_SW(x)               (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_CSS_CLK_SW_SHIFT)) & MC_CGM_MUX_3_CSS_CLK_SW_MASK)

#define MC_CGM_MUX_3_CSS_SAFE_SW_MASK            (0x8U)
#define MC_CGM_MUX_3_CSS_SAFE_SW_SHIFT           (3U)
#define MC_CGM_MUX_3_CSS_SAFE_SW_WIDTH           (1U)
#define MC_CGM_MUX_3_CSS_SAFE_SW(x)              (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_CSS_SAFE_SW_SHIFT)) & MC_CGM_MUX_3_CSS_SAFE_SW_MASK)

#define MC_CGM_MUX_3_CSS_SWIP_MASK               (0x10000U)
#define MC_CGM_MUX_3_CSS_SWIP_SHIFT              (16U)
#define MC_CGM_MUX_3_CSS_SWIP_WIDTH              (1U)
#define MC_CGM_MUX_3_CSS_SWIP(x)                 (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_CSS_SWIP_SHIFT)) & MC_CGM_MUX_3_CSS_SWIP_MASK)

#define MC_CGM_MUX_3_CSS_SWTRG_MASK              (0xE0000U)
#define MC_CGM_MUX_3_CSS_SWTRG_SHIFT             (17U)
#define MC_CGM_MUX_3_CSS_SWTRG_WIDTH             (3U)
#define MC_CGM_MUX_3_CSS_SWTRG(x)                (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_CSS_SWTRG_SHIFT)) & MC_CGM_MUX_3_CSS_SWTRG_MASK)

#define MC_CGM_MUX_3_CSS_SELSTAT_MASK            (0x1F000000U)
#define MC_CGM_MUX_3_CSS_SELSTAT_SHIFT           (24U)
#define MC_CGM_MUX_3_CSS_SELSTAT_WIDTH           (5U)
#define MC_CGM_MUX_3_CSS_SELSTAT(x)              (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_CSS_SELSTAT_SHIFT)) & MC_CGM_MUX_3_CSS_SELSTAT_MASK)
/*! @} */

/*! @name MUX_3_DC_0 - Clock Mux 3 Divider 0 Control Register */
/*! @{ */

#define MC_CGM_MUX_3_DC_0_DIV_MASK               (0x30000U)
#define MC_CGM_MUX_3_DC_0_DIV_SHIFT              (16U)
#define MC_CGM_MUX_3_DC_0_DIV_WIDTH              (2U)
#define MC_CGM_MUX_3_DC_0_DIV(x)                 (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_DC_0_DIV_SHIFT)) & MC_CGM_MUX_3_DC_0_DIV_MASK)

#define MC_CGM_MUX_3_DC_0_DE_MASK                (0x80000000U)
#define MC_CGM_MUX_3_DC_0_DE_SHIFT               (31U)
#define MC_CGM_MUX_3_DC_0_DE_WIDTH               (1U)
#define MC_CGM_MUX_3_DC_0_DE(x)                  (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_DC_0_DE_SHIFT)) & MC_CGM_MUX_3_DC_0_DE_MASK)
/*! @} */

/*! @name MUX_3_DIV_UPD_STAT - Clock Mux 3 Divider Update Status Register */
/*! @{ */

#define MC_CGM_MUX_3_DIV_UPD_STAT_DIV_STAT_MASK  (0x1U)
#define MC_CGM_MUX_3_DIV_UPD_STAT_DIV_STAT_SHIFT (0U)
#define MC_CGM_MUX_3_DIV_UPD_STAT_DIV_STAT_WIDTH (1U)
#define MC_CGM_MUX_3_DIV_UPD_STAT_DIV_STAT(x)    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_3_DIV_UPD_STAT_DIV_STAT_SHIFT)) & MC_CGM_MUX_3_DIV_UPD_STAT_DIV_STAT_MASK)
/*! @} */

/*! @name MUX_4_CSC - Clock Mux 4 Select Control Register */
/*! @{ */

#define MC_CGM_MUX_4_CSC_CLK_SW_MASK             (0x4U)
#define MC_CGM_MUX_4_CSC_CLK_SW_SHIFT            (2U)
#define MC_CGM_MUX_4_CSC_CLK_SW_WIDTH            (1U)
#define MC_CGM_MUX_4_CSC_CLK_SW(x)               (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_4_CSC_CLK_SW_SHIFT)) & MC_CGM_MUX_4_CSC_CLK_SW_MASK)

#define MC_CGM_MUX_4_CSC_SAFE_SW_MASK            (0x8U)
#define MC_CGM_MUX_4_CSC_SAFE_SW_SHIFT           (3U)
#define MC_CGM_MUX_4_CSC_SAFE_SW_WIDTH           (1U)
#define MC_CGM_MUX_4_CSC_SAFE_SW(x)              (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_4_CSC_SAFE_SW_SHIFT)) & MC_CGM_MUX_4_CSC_SAFE_SW_MASK)

#define MC_CGM_MUX_4_CSC_SELCTL_MASK             (0x1F000000U)
#define MC_CGM_MUX_4_CSC_SELCTL_SHIFT            (24U)
#define MC_CGM_MUX_4_CSC_SELCTL_WIDTH            (5U)
#define MC_CGM_MUX_4_CSC_SELCTL(x)               (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_4_CSC_SELCTL_SHIFT)) & MC_CGM_MUX_4_CSC_SELCTL_MASK)
/*! @} */

/*! @name MUX_4_CSS - Clock Mux 4 Select Status Register */
/*! @{ */

#define MC_CGM_MUX_4_CSS_CLK_SW_MASK             (0x4U)
#define MC_CGM_MUX_4_CSS_CLK_SW_SHIFT            (2U)
#define MC_CGM_MUX_4_CSS_CLK_SW_WIDTH            (1U)
#define MC_CGM_MUX_4_CSS_CLK_SW(x)               (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_4_CSS_CLK_SW_SHIFT)) & MC_CGM_MUX_4_CSS_CLK_SW_MASK)

#define MC_CGM_MUX_4_CSS_SAFE_SW_MASK            (0x8U)
#define MC_CGM_MUX_4_CSS_SAFE_SW_SHIFT           (3U)
#define MC_CGM_MUX_4_CSS_SAFE_SW_WIDTH           (1U)
#define MC_CGM_MUX_4_CSS_SAFE_SW(x)              (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_4_CSS_SAFE_SW_SHIFT)) & MC_CGM_MUX_4_CSS_SAFE_SW_MASK)

#define MC_CGM_MUX_4_CSS_SWIP_MASK               (0x10000U)
#define MC_CGM_MUX_4_CSS_SWIP_SHIFT              (16U)
#define MC_CGM_MUX_4_CSS_SWIP_WIDTH              (1U)
#define MC_CGM_MUX_4_CSS_SWIP(x)                 (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_4_CSS_SWIP_SHIFT)) & MC_CGM_MUX_4_CSS_SWIP_MASK)

#define MC_CGM_MUX_4_CSS_SWTRG_MASK              (0xE0000U)
#define MC_CGM_MUX_4_CSS_SWTRG_SHIFT             (17U)
#define MC_CGM_MUX_4_CSS_SWTRG_WIDTH             (3U)
#define MC_CGM_MUX_4_CSS_SWTRG(x)                (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_4_CSS_SWTRG_SHIFT)) & MC_CGM_MUX_4_CSS_SWTRG_MASK)

#define MC_CGM_MUX_4_CSS_SELSTAT_MASK            (0x1F000000U)
#define MC_CGM_MUX_4_CSS_SELSTAT_SHIFT           (24U)
#define MC_CGM_MUX_4_CSS_SELSTAT_WIDTH           (5U)
#define MC_CGM_MUX_4_CSS_SELSTAT(x)              (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_4_CSS_SELSTAT_SHIFT)) & MC_CGM_MUX_4_CSS_SELSTAT_MASK)
/*! @} */

/*! @name MUX_4_DC_0 - Clock Mux 4 Divider 0 Control Register */
/*! @{ */

#define MC_CGM_MUX_4_DC_0_DIV_MASK               (0x30000U)
#define MC_CGM_MUX_4_DC_0_DIV_SHIFT              (16U)
#define MC_CGM_MUX_4_DC_0_DIV_WIDTH              (2U)
#define MC_CGM_MUX_4_DC_0_DIV(x)                 (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_4_DC_0_DIV_SHIFT)) & MC_CGM_MUX_4_DC_0_DIV_MASK)

#define MC_CGM_MUX_4_DC_0_DE_MASK                (0x80000000U)
#define MC_CGM_MUX_4_DC_0_DE_SHIFT               (31U)
#define MC_CGM_MUX_4_DC_0_DE_WIDTH               (1U)
#define MC_CGM_MUX_4_DC_0_DE(x)                  (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_4_DC_0_DE_SHIFT)) & MC_CGM_MUX_4_DC_0_DE_MASK)
/*! @} */

/*! @name MUX_4_DIV_UPD_STAT - Clock Mux 4 Divider Update Status Register */
/*! @{ */

#define MC_CGM_MUX_4_DIV_UPD_STAT_DIV_STAT_MASK  (0x1U)
#define MC_CGM_MUX_4_DIV_UPD_STAT_DIV_STAT_SHIFT (0U)
#define MC_CGM_MUX_4_DIV_UPD_STAT_DIV_STAT_WIDTH (1U)
#define MC_CGM_MUX_4_DIV_UPD_STAT_DIV_STAT(x)    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_4_DIV_UPD_STAT_DIV_STAT_SHIFT)) & MC_CGM_MUX_4_DIV_UPD_STAT_DIV_STAT_MASK)
/*! @} */

/*! @name MUX_5_CSC - Clock Mux 5 Select Control Register */
/*! @{ */

#define MC_CGM_MUX_5_CSC_CG_MASK                 (0x4U)
#define MC_CGM_MUX_5_CSC_CG_SHIFT                (2U)
#define MC_CGM_MUX_5_CSC_CG_WIDTH                (1U)
#define MC_CGM_MUX_5_CSC_CG(x)                   (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_5_CSC_CG_SHIFT)) & MC_CGM_MUX_5_CSC_CG_MASK)

#define MC_CGM_MUX_5_CSC_FCG_MASK                (0x8U)
#define MC_CGM_MUX_5_CSC_FCG_SHIFT               (3U)
#define MC_CGM_MUX_5_CSC_FCG_WIDTH               (1U)
#define MC_CGM_MUX_5_CSC_FCG(x)                  (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_5_CSC_FCG_SHIFT)) & MC_CGM_MUX_5_CSC_FCG_MASK)

#define MC_CGM_MUX_5_CSC_SELCTL_MASK             (0x3F000000U)
#define MC_CGM_MUX_5_CSC_SELCTL_SHIFT            (24U)
#define MC_CGM_MUX_5_CSC_SELCTL_WIDTH            (6U)
#define MC_CGM_MUX_5_CSC_SELCTL(x)               (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_5_CSC_SELCTL_SHIFT)) & MC_CGM_MUX_5_CSC_SELCTL_MASK)
/*! @} */

/*! @name MUX_5_CSS - Clock Mux 5 Select Status Register */
/*! @{ */

#define MC_CGM_MUX_5_CSS_GRIP_MASK               (0x10000U)
#define MC_CGM_MUX_5_CSS_GRIP_SHIFT              (16U)
#define MC_CGM_MUX_5_CSS_GRIP_WIDTH              (1U)
#define MC_CGM_MUX_5_CSS_GRIP(x)                 (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_5_CSS_GRIP_SHIFT)) & MC_CGM_MUX_5_CSS_GRIP_MASK)

#define MC_CGM_MUX_5_CSS_CS_MASK                 (0x20000U)
#define MC_CGM_MUX_5_CSS_CS_SHIFT                (17U)
#define MC_CGM_MUX_5_CSS_CS_WIDTH                (1U)
#define MC_CGM_MUX_5_CSS_CS(x)                   (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_5_CSS_CS_SHIFT)) & MC_CGM_MUX_5_CSS_CS_MASK)

#define MC_CGM_MUX_5_CSS_SELSTAT_MASK            (0x3F000000U)
#define MC_CGM_MUX_5_CSS_SELSTAT_SHIFT           (24U)
#define MC_CGM_MUX_5_CSS_SELSTAT_WIDTH           (6U)
#define MC_CGM_MUX_5_CSS_SELSTAT(x)              (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_5_CSS_SELSTAT_SHIFT)) & MC_CGM_MUX_5_CSS_SELSTAT_MASK)
/*! @} */

/*! @name MUX_5_DC_0 - Clock Mux 5 Divider 0 Control Register */
/*! @{ */

#define MC_CGM_MUX_5_DC_0_DIV_MASK               (0x70000U)
#define MC_CGM_MUX_5_DC_0_DIV_SHIFT              (16U)
#define MC_CGM_MUX_5_DC_0_DIV_WIDTH              (3U)
#define MC_CGM_MUX_5_DC_0_DIV(x)                 (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_5_DC_0_DIV_SHIFT)) & MC_CGM_MUX_5_DC_0_DIV_MASK)

#define MC_CGM_MUX_5_DC_0_DE_MASK                (0x80000000U)
#define MC_CGM_MUX_5_DC_0_DE_SHIFT               (31U)
#define MC_CGM_MUX_5_DC_0_DE_WIDTH               (1U)
#define MC_CGM_MUX_5_DC_0_DE(x)                  (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_5_DC_0_DE_SHIFT)) & MC_CGM_MUX_5_DC_0_DE_MASK)
/*! @} */

/*! @name MUX_5_DIV_UPD_STAT - Clock Mux 5 Divider Update Status Register */
/*! @{ */

#define MC_CGM_MUX_5_DIV_UPD_STAT_DIV_STAT_MASK  (0x1U)
#define MC_CGM_MUX_5_DIV_UPD_STAT_DIV_STAT_SHIFT (0U)
#define MC_CGM_MUX_5_DIV_UPD_STAT_DIV_STAT_WIDTH (1U)
#define MC_CGM_MUX_5_DIV_UPD_STAT_DIV_STAT(x)    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_5_DIV_UPD_STAT_DIV_STAT_SHIFT)) & MC_CGM_MUX_5_DIV_UPD_STAT_DIV_STAT_MASK)
/*! @} */

/*! @name MUX_6_CSC - Clock Mux 6 Select Control Register */
/*! @{ */

#define MC_CGM_MUX_6_CSC_CG_MASK                 (0x4U)
#define MC_CGM_MUX_6_CSC_CG_SHIFT                (2U)
#define MC_CGM_MUX_6_CSC_CG_WIDTH                (1U)
#define MC_CGM_MUX_6_CSC_CG(x)                   (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_6_CSC_CG_SHIFT)) & MC_CGM_MUX_6_CSC_CG_MASK)

#define MC_CGM_MUX_6_CSC_FCG_MASK                (0x8U)
#define MC_CGM_MUX_6_CSC_FCG_SHIFT               (3U)
#define MC_CGM_MUX_6_CSC_FCG_WIDTH               (1U)
#define MC_CGM_MUX_6_CSC_FCG(x)                  (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_6_CSC_FCG_SHIFT)) & MC_CGM_MUX_6_CSC_FCG_MASK)

#define MC_CGM_MUX_6_CSC_SELCTL_MASK             (0x3F000000U)
#define MC_CGM_MUX_6_CSC_SELCTL_SHIFT            (24U)
#define MC_CGM_MUX_6_CSC_SELCTL_WIDTH            (6U)
#define MC_CGM_MUX_6_CSC_SELCTL(x)               (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_6_CSC_SELCTL_SHIFT)) & MC_CGM_MUX_6_CSC_SELCTL_MASK)
/*! @} */

/*! @name MUX_6_CSS - Clock Mux 6 Select Status Register */
/*! @{ */

#define MC_CGM_MUX_6_CSS_GRIP_MASK               (0x10000U)
#define MC_CGM_MUX_6_CSS_GRIP_SHIFT              (16U)
#define MC_CGM_MUX_6_CSS_GRIP_WIDTH              (1U)
#define MC_CGM_MUX_6_CSS_GRIP(x)                 (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_6_CSS_GRIP_SHIFT)) & MC_CGM_MUX_6_CSS_GRIP_MASK)

#define MC_CGM_MUX_6_CSS_CS_MASK                 (0x20000U)
#define MC_CGM_MUX_6_CSS_CS_SHIFT                (17U)
#define MC_CGM_MUX_6_CSS_CS_WIDTH                (1U)
#define MC_CGM_MUX_6_CSS_CS(x)                   (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_6_CSS_CS_SHIFT)) & MC_CGM_MUX_6_CSS_CS_MASK)

#define MC_CGM_MUX_6_CSS_SELSTAT_MASK            (0x3F000000U)
#define MC_CGM_MUX_6_CSS_SELSTAT_SHIFT           (24U)
#define MC_CGM_MUX_6_CSS_SELSTAT_WIDTH           (6U)
#define MC_CGM_MUX_6_CSS_SELSTAT(x)              (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_6_CSS_SELSTAT_SHIFT)) & MC_CGM_MUX_6_CSS_SELSTAT_MASK)
/*! @} */

/*! @name MUX_6_DC_0 - Clock Mux 6 Divider 0 Control Register */
/*! @{ */

#define MC_CGM_MUX_6_DC_0_DIV_MASK               (0x3F0000U)
#define MC_CGM_MUX_6_DC_0_DIV_SHIFT              (16U)
#define MC_CGM_MUX_6_DC_0_DIV_WIDTH              (6U)
#define MC_CGM_MUX_6_DC_0_DIV(x)                 (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_6_DC_0_DIV_SHIFT)) & MC_CGM_MUX_6_DC_0_DIV_MASK)

#define MC_CGM_MUX_6_DC_0_DE_MASK                (0x80000000U)
#define MC_CGM_MUX_6_DC_0_DE_SHIFT               (31U)
#define MC_CGM_MUX_6_DC_0_DE_WIDTH               (1U)
#define MC_CGM_MUX_6_DC_0_DE(x)                  (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_6_DC_0_DE_SHIFT)) & MC_CGM_MUX_6_DC_0_DE_MASK)
/*! @} */

/*! @name MUX_6_DIV_UPD_STAT - Clock Mux 6 Divider Update Status Register */
/*! @{ */

#define MC_CGM_MUX_6_DIV_UPD_STAT_DIV_STAT_MASK  (0x1U)
#define MC_CGM_MUX_6_DIV_UPD_STAT_DIV_STAT_SHIFT (0U)
#define MC_CGM_MUX_6_DIV_UPD_STAT_DIV_STAT_WIDTH (1U)
#define MC_CGM_MUX_6_DIV_UPD_STAT_DIV_STAT(x)    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_6_DIV_UPD_STAT_DIV_STAT_SHIFT)) & MC_CGM_MUX_6_DIV_UPD_STAT_DIV_STAT_MASK)
/*! @} */

/*! @name MUX_7_CSC - Clock Mux 7 Select Control Register */
/*! @{ */

#define MC_CGM_MUX_7_CSC_CLK_SW_MASK             (0x4U)
#define MC_CGM_MUX_7_CSC_CLK_SW_SHIFT            (2U)
#define MC_CGM_MUX_7_CSC_CLK_SW_WIDTH            (1U)
#define MC_CGM_MUX_7_CSC_CLK_SW(x)               (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_7_CSC_CLK_SW_SHIFT)) & MC_CGM_MUX_7_CSC_CLK_SW_MASK)

#define MC_CGM_MUX_7_CSC_SAFE_SW_MASK            (0x8U)
#define MC_CGM_MUX_7_CSC_SAFE_SW_SHIFT           (3U)
#define MC_CGM_MUX_7_CSC_SAFE_SW_WIDTH           (1U)
#define MC_CGM_MUX_7_CSC_SAFE_SW(x)              (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_7_CSC_SAFE_SW_SHIFT)) & MC_CGM_MUX_7_CSC_SAFE_SW_MASK)

#define MC_CGM_MUX_7_CSC_SELCTL_MASK             (0x1F000000U)
#define MC_CGM_MUX_7_CSC_SELCTL_SHIFT            (24U)
#define MC_CGM_MUX_7_CSC_SELCTL_WIDTH            (5U)
#define MC_CGM_MUX_7_CSC_SELCTL(x)               (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_7_CSC_SELCTL_SHIFT)) & MC_CGM_MUX_7_CSC_SELCTL_MASK)
/*! @} */

/*! @name MUX_7_CSS - Clock Mux 7 Select Status Register */
/*! @{ */

#define MC_CGM_MUX_7_CSS_CLK_SW_MASK             (0x4U)
#define MC_CGM_MUX_7_CSS_CLK_SW_SHIFT            (2U)
#define MC_CGM_MUX_7_CSS_CLK_SW_WIDTH            (1U)
#define MC_CGM_MUX_7_CSS_CLK_SW(x)               (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_7_CSS_CLK_SW_SHIFT)) & MC_CGM_MUX_7_CSS_CLK_SW_MASK)

#define MC_CGM_MUX_7_CSS_SAFE_SW_MASK            (0x8U)
#define MC_CGM_MUX_7_CSS_SAFE_SW_SHIFT           (3U)
#define MC_CGM_MUX_7_CSS_SAFE_SW_WIDTH           (1U)
#define MC_CGM_MUX_7_CSS_SAFE_SW(x)              (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_7_CSS_SAFE_SW_SHIFT)) & MC_CGM_MUX_7_CSS_SAFE_SW_MASK)

#define MC_CGM_MUX_7_CSS_SWIP_MASK               (0x10000U)
#define MC_CGM_MUX_7_CSS_SWIP_SHIFT              (16U)
#define MC_CGM_MUX_7_CSS_SWIP_WIDTH              (1U)
#define MC_CGM_MUX_7_CSS_SWIP(x)                 (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_7_CSS_SWIP_SHIFT)) & MC_CGM_MUX_7_CSS_SWIP_MASK)

#define MC_CGM_MUX_7_CSS_SWTRG_MASK              (0xE0000U)
#define MC_CGM_MUX_7_CSS_SWTRG_SHIFT             (17U)
#define MC_CGM_MUX_7_CSS_SWTRG_WIDTH             (3U)
#define MC_CGM_MUX_7_CSS_SWTRG(x)                (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_7_CSS_SWTRG_SHIFT)) & MC_CGM_MUX_7_CSS_SWTRG_MASK)

#define MC_CGM_MUX_7_CSS_SELSTAT_MASK            (0x1F000000U)
#define MC_CGM_MUX_7_CSS_SELSTAT_SHIFT           (24U)
#define MC_CGM_MUX_7_CSS_SELSTAT_WIDTH           (5U)
#define MC_CGM_MUX_7_CSS_SELSTAT(x)              (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_7_CSS_SELSTAT_SHIFT)) & MC_CGM_MUX_7_CSS_SELSTAT_MASK)
/*! @} */

/*! @name MUX_7_DC_0 - Clock Mux 7 Divider 0 Control Register */
/*! @{ */

#define MC_CGM_MUX_7_DC_0_DIV_MASK               (0x3F0000U)
#define MC_CGM_MUX_7_DC_0_DIV_SHIFT              (16U)
#define MC_CGM_MUX_7_DC_0_DIV_WIDTH              (6U)
#define MC_CGM_MUX_7_DC_0_DIV(x)                 (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_7_DC_0_DIV_SHIFT)) & MC_CGM_MUX_7_DC_0_DIV_MASK)

#define MC_CGM_MUX_7_DC_0_DE_MASK                (0x80000000U)
#define MC_CGM_MUX_7_DC_0_DE_SHIFT               (31U)
#define MC_CGM_MUX_7_DC_0_DE_WIDTH               (1U)
#define MC_CGM_MUX_7_DC_0_DE(x)                  (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_7_DC_0_DE_SHIFT)) & MC_CGM_MUX_7_DC_0_DE_MASK)
/*! @} */

/*! @name MUX_7_DIV_UPD_STAT - Clock Mux 7 Divider Update Status Register */
/*! @{ */

#define MC_CGM_MUX_7_DIV_UPD_STAT_DIV_STAT_MASK  (0x1U)
#define MC_CGM_MUX_7_DIV_UPD_STAT_DIV_STAT_SHIFT (0U)
#define MC_CGM_MUX_7_DIV_UPD_STAT_DIV_STAT_WIDTH (1U)
#define MC_CGM_MUX_7_DIV_UPD_STAT_DIV_STAT(x)    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_7_DIV_UPD_STAT_DIV_STAT_SHIFT)) & MC_CGM_MUX_7_DIV_UPD_STAT_DIV_STAT_MASK)
/*! @} */

/*! @name MUX_8_CSC - Clock Mux 8 Select Control Register */
/*! @{ */

#define MC_CGM_MUX_8_CSC_CLK_SW_MASK             (0x4U)
#define MC_CGM_MUX_8_CSC_CLK_SW_SHIFT            (2U)
#define MC_CGM_MUX_8_CSC_CLK_SW_WIDTH            (1U)
#define MC_CGM_MUX_8_CSC_CLK_SW(x)               (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_8_CSC_CLK_SW_SHIFT)) & MC_CGM_MUX_8_CSC_CLK_SW_MASK)

#define MC_CGM_MUX_8_CSC_SAFE_SW_MASK            (0x8U)
#define MC_CGM_MUX_8_CSC_SAFE_SW_SHIFT           (3U)
#define MC_CGM_MUX_8_CSC_SAFE_SW_WIDTH           (1U)
#define MC_CGM_MUX_8_CSC_SAFE_SW(x)              (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_8_CSC_SAFE_SW_SHIFT)) & MC_CGM_MUX_8_CSC_SAFE_SW_MASK)

#define MC_CGM_MUX_8_CSC_SELCTL_MASK             (0x1F000000U)
#define MC_CGM_MUX_8_CSC_SELCTL_SHIFT            (24U)
#define MC_CGM_MUX_8_CSC_SELCTL_WIDTH            (5U)
#define MC_CGM_MUX_8_CSC_SELCTL(x)               (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_8_CSC_SELCTL_SHIFT)) & MC_CGM_MUX_8_CSC_SELCTL_MASK)
/*! @} */

/*! @name MUX_8_CSS - Clock Mux 8 Select Status Register */
/*! @{ */

#define MC_CGM_MUX_8_CSS_CLK_SW_MASK             (0x4U)
#define MC_CGM_MUX_8_CSS_CLK_SW_SHIFT            (2U)
#define MC_CGM_MUX_8_CSS_CLK_SW_WIDTH            (1U)
#define MC_CGM_MUX_8_CSS_CLK_SW(x)               (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_8_CSS_CLK_SW_SHIFT)) & MC_CGM_MUX_8_CSS_CLK_SW_MASK)

#define MC_CGM_MUX_8_CSS_SAFE_SW_MASK            (0x8U)
#define MC_CGM_MUX_8_CSS_SAFE_SW_SHIFT           (3U)
#define MC_CGM_MUX_8_CSS_SAFE_SW_WIDTH           (1U)
#define MC_CGM_MUX_8_CSS_SAFE_SW(x)              (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_8_CSS_SAFE_SW_SHIFT)) & MC_CGM_MUX_8_CSS_SAFE_SW_MASK)

#define MC_CGM_MUX_8_CSS_SWIP_MASK               (0x10000U)
#define MC_CGM_MUX_8_CSS_SWIP_SHIFT              (16U)
#define MC_CGM_MUX_8_CSS_SWIP_WIDTH              (1U)
#define MC_CGM_MUX_8_CSS_SWIP(x)                 (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_8_CSS_SWIP_SHIFT)) & MC_CGM_MUX_8_CSS_SWIP_MASK)

#define MC_CGM_MUX_8_CSS_SWTRG_MASK              (0xE0000U)
#define MC_CGM_MUX_8_CSS_SWTRG_SHIFT             (17U)
#define MC_CGM_MUX_8_CSS_SWTRG_WIDTH             (3U)
#define MC_CGM_MUX_8_CSS_SWTRG(x)                (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_8_CSS_SWTRG_SHIFT)) & MC_CGM_MUX_8_CSS_SWTRG_MASK)

#define MC_CGM_MUX_8_CSS_SELSTAT_MASK            (0x1F000000U)
#define MC_CGM_MUX_8_CSS_SELSTAT_SHIFT           (24U)
#define MC_CGM_MUX_8_CSS_SELSTAT_WIDTH           (5U)
#define MC_CGM_MUX_8_CSS_SELSTAT(x)              (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_8_CSS_SELSTAT_SHIFT)) & MC_CGM_MUX_8_CSS_SELSTAT_MASK)
/*! @} */

/*! @name MUX_8_DC_0 - Clock Mux 8 Divider 0 Control Register */
/*! @{ */

#define MC_CGM_MUX_8_DC_0_DIV_MASK               (0x3F0000U)
#define MC_CGM_MUX_8_DC_0_DIV_SHIFT              (16U)
#define MC_CGM_MUX_8_DC_0_DIV_WIDTH              (6U)
#define MC_CGM_MUX_8_DC_0_DIV(x)                 (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_8_DC_0_DIV_SHIFT)) & MC_CGM_MUX_8_DC_0_DIV_MASK)

#define MC_CGM_MUX_8_DC_0_DE_MASK                (0x80000000U)
#define MC_CGM_MUX_8_DC_0_DE_SHIFT               (31U)
#define MC_CGM_MUX_8_DC_0_DE_WIDTH               (1U)
#define MC_CGM_MUX_8_DC_0_DE(x)                  (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_8_DC_0_DE_SHIFT)) & MC_CGM_MUX_8_DC_0_DE_MASK)
/*! @} */

/*! @name MUX_8_DIV_UPD_STAT - Clock Mux 8 Divider Update Status Register */
/*! @{ */

#define MC_CGM_MUX_8_DIV_UPD_STAT_DIV_STAT_MASK  (0x1U)
#define MC_CGM_MUX_8_DIV_UPD_STAT_DIV_STAT_SHIFT (0U)
#define MC_CGM_MUX_8_DIV_UPD_STAT_DIV_STAT_WIDTH (1U)
#define MC_CGM_MUX_8_DIV_UPD_STAT_DIV_STAT(x)    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_8_DIV_UPD_STAT_DIV_STAT_SHIFT)) & MC_CGM_MUX_8_DIV_UPD_STAT_DIV_STAT_MASK)
/*! @} */

/*! @name MUX_9_CSC - Clock Mux 9 Select Control Register */
/*! @{ */

#define MC_CGM_MUX_9_CSC_CLK_SW_MASK             (0x4U)
#define MC_CGM_MUX_9_CSC_CLK_SW_SHIFT            (2U)
#define MC_CGM_MUX_9_CSC_CLK_SW_WIDTH            (1U)
#define MC_CGM_MUX_9_CSC_CLK_SW(x)               (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_9_CSC_CLK_SW_SHIFT)) & MC_CGM_MUX_9_CSC_CLK_SW_MASK)

#define MC_CGM_MUX_9_CSC_SAFE_SW_MASK            (0x8U)
#define MC_CGM_MUX_9_CSC_SAFE_SW_SHIFT           (3U)
#define MC_CGM_MUX_9_CSC_SAFE_SW_WIDTH           (1U)
#define MC_CGM_MUX_9_CSC_SAFE_SW(x)              (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_9_CSC_SAFE_SW_SHIFT)) & MC_CGM_MUX_9_CSC_SAFE_SW_MASK)

#define MC_CGM_MUX_9_CSC_SELCTL_MASK             (0x1F000000U)
#define MC_CGM_MUX_9_CSC_SELCTL_SHIFT            (24U)
#define MC_CGM_MUX_9_CSC_SELCTL_WIDTH            (5U)
#define MC_CGM_MUX_9_CSC_SELCTL(x)               (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_9_CSC_SELCTL_SHIFT)) & MC_CGM_MUX_9_CSC_SELCTL_MASK)
/*! @} */

/*! @name MUX_9_CSS - Clock Mux 9 Select Status Register */
/*! @{ */

#define MC_CGM_MUX_9_CSS_CLK_SW_MASK             (0x4U)
#define MC_CGM_MUX_9_CSS_CLK_SW_SHIFT            (2U)
#define MC_CGM_MUX_9_CSS_CLK_SW_WIDTH            (1U)
#define MC_CGM_MUX_9_CSS_CLK_SW(x)               (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_9_CSS_CLK_SW_SHIFT)) & MC_CGM_MUX_9_CSS_CLK_SW_MASK)

#define MC_CGM_MUX_9_CSS_SAFE_SW_MASK            (0x8U)
#define MC_CGM_MUX_9_CSS_SAFE_SW_SHIFT           (3U)
#define MC_CGM_MUX_9_CSS_SAFE_SW_WIDTH           (1U)
#define MC_CGM_MUX_9_CSS_SAFE_SW(x)              (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_9_CSS_SAFE_SW_SHIFT)) & MC_CGM_MUX_9_CSS_SAFE_SW_MASK)

#define MC_CGM_MUX_9_CSS_SWIP_MASK               (0x10000U)
#define MC_CGM_MUX_9_CSS_SWIP_SHIFT              (16U)
#define MC_CGM_MUX_9_CSS_SWIP_WIDTH              (1U)
#define MC_CGM_MUX_9_CSS_SWIP(x)                 (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_9_CSS_SWIP_SHIFT)) & MC_CGM_MUX_9_CSS_SWIP_MASK)

#define MC_CGM_MUX_9_CSS_SWTRG_MASK              (0xE0000U)
#define MC_CGM_MUX_9_CSS_SWTRG_SHIFT             (17U)
#define MC_CGM_MUX_9_CSS_SWTRG_WIDTH             (3U)
#define MC_CGM_MUX_9_CSS_SWTRG(x)                (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_9_CSS_SWTRG_SHIFT)) & MC_CGM_MUX_9_CSS_SWTRG_MASK)

#define MC_CGM_MUX_9_CSS_SELSTAT_MASK            (0x1F000000U)
#define MC_CGM_MUX_9_CSS_SELSTAT_SHIFT           (24U)
#define MC_CGM_MUX_9_CSS_SELSTAT_WIDTH           (5U)
#define MC_CGM_MUX_9_CSS_SELSTAT(x)              (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_9_CSS_SELSTAT_SHIFT)) & MC_CGM_MUX_9_CSS_SELSTAT_MASK)
/*! @} */

/*! @name MUX_9_DC_0 - Clock Mux 9 Divider 0 Control Register */
/*! @{ */

#define MC_CGM_MUX_9_DC_0_DIV_MASK               (0x3F0000U)
#define MC_CGM_MUX_9_DC_0_DIV_SHIFT              (16U)
#define MC_CGM_MUX_9_DC_0_DIV_WIDTH              (6U)
#define MC_CGM_MUX_9_DC_0_DIV(x)                 (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_9_DC_0_DIV_SHIFT)) & MC_CGM_MUX_9_DC_0_DIV_MASK)

#define MC_CGM_MUX_9_DC_0_DE_MASK                (0x80000000U)
#define MC_CGM_MUX_9_DC_0_DE_SHIFT               (31U)
#define MC_CGM_MUX_9_DC_0_DE_WIDTH               (1U)
#define MC_CGM_MUX_9_DC_0_DE(x)                  (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_9_DC_0_DE_SHIFT)) & MC_CGM_MUX_9_DC_0_DE_MASK)
/*! @} */

/*! @name MUX_9_DIV_UPD_STAT - Clock Mux 9 Divider Update Status Register */
/*! @{ */

#define MC_CGM_MUX_9_DIV_UPD_STAT_DIV_STAT_MASK  (0x1U)
#define MC_CGM_MUX_9_DIV_UPD_STAT_DIV_STAT_SHIFT (0U)
#define MC_CGM_MUX_9_DIV_UPD_STAT_DIV_STAT_WIDTH (1U)
#define MC_CGM_MUX_9_DIV_UPD_STAT_DIV_STAT(x)    (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_9_DIV_UPD_STAT_DIV_STAT_SHIFT)) & MC_CGM_MUX_9_DIV_UPD_STAT_DIV_STAT_MASK)
/*! @} */

/*! @name MUX_10_CSC - Clock Mux 10 Select Control Register */
/*! @{ */

#define MC_CGM_MUX_10_CSC_CLK_SW_MASK            (0x4U)
#define MC_CGM_MUX_10_CSC_CLK_SW_SHIFT           (2U)
#define MC_CGM_MUX_10_CSC_CLK_SW_WIDTH           (1U)
#define MC_CGM_MUX_10_CSC_CLK_SW(x)              (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_10_CSC_CLK_SW_SHIFT)) & MC_CGM_MUX_10_CSC_CLK_SW_MASK)

#define MC_CGM_MUX_10_CSC_SAFE_SW_MASK           (0x8U)
#define MC_CGM_MUX_10_CSC_SAFE_SW_SHIFT          (3U)
#define MC_CGM_MUX_10_CSC_SAFE_SW_WIDTH          (1U)
#define MC_CGM_MUX_10_CSC_SAFE_SW(x)             (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_10_CSC_SAFE_SW_SHIFT)) & MC_CGM_MUX_10_CSC_SAFE_SW_MASK)

#define MC_CGM_MUX_10_CSC_SELCTL_MASK            (0xF000000U)
#define MC_CGM_MUX_10_CSC_SELCTL_SHIFT           (24U)
#define MC_CGM_MUX_10_CSC_SELCTL_WIDTH           (4U)
#define MC_CGM_MUX_10_CSC_SELCTL(x)              (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_10_CSC_SELCTL_SHIFT)) & MC_CGM_MUX_10_CSC_SELCTL_MASK)
/*! @} */

/*! @name MUX_10_CSS - Clock Mux 10 Select Status Register */
/*! @{ */

#define MC_CGM_MUX_10_CSS_CLK_SW_MASK            (0x4U)
#define MC_CGM_MUX_10_CSS_CLK_SW_SHIFT           (2U)
#define MC_CGM_MUX_10_CSS_CLK_SW_WIDTH           (1U)
#define MC_CGM_MUX_10_CSS_CLK_SW(x)              (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_10_CSS_CLK_SW_SHIFT)) & MC_CGM_MUX_10_CSS_CLK_SW_MASK)

#define MC_CGM_MUX_10_CSS_SAFE_SW_MASK           (0x8U)
#define MC_CGM_MUX_10_CSS_SAFE_SW_SHIFT          (3U)
#define MC_CGM_MUX_10_CSS_SAFE_SW_WIDTH          (1U)
#define MC_CGM_MUX_10_CSS_SAFE_SW(x)             (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_10_CSS_SAFE_SW_SHIFT)) & MC_CGM_MUX_10_CSS_SAFE_SW_MASK)

#define MC_CGM_MUX_10_CSS_SWIP_MASK              (0x10000U)
#define MC_CGM_MUX_10_CSS_SWIP_SHIFT             (16U)
#define MC_CGM_MUX_10_CSS_SWIP_WIDTH             (1U)
#define MC_CGM_MUX_10_CSS_SWIP(x)                (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_10_CSS_SWIP_SHIFT)) & MC_CGM_MUX_10_CSS_SWIP_MASK)

#define MC_CGM_MUX_10_CSS_SWTRG_MASK             (0xE0000U)
#define MC_CGM_MUX_10_CSS_SWTRG_SHIFT            (17U)
#define MC_CGM_MUX_10_CSS_SWTRG_WIDTH            (3U)
#define MC_CGM_MUX_10_CSS_SWTRG(x)               (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_10_CSS_SWTRG_SHIFT)) & MC_CGM_MUX_10_CSS_SWTRG_MASK)

#define MC_CGM_MUX_10_CSS_SELSTAT_MASK           (0xF000000U)
#define MC_CGM_MUX_10_CSS_SELSTAT_SHIFT          (24U)
#define MC_CGM_MUX_10_CSS_SELSTAT_WIDTH          (4U)
#define MC_CGM_MUX_10_CSS_SELSTAT(x)             (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_10_CSS_SELSTAT_SHIFT)) & MC_CGM_MUX_10_CSS_SELSTAT_MASK)
/*! @} */

/*! @name MUX_10_DC_0 - Clock Mux 10 Divider 0 Control Register */
/*! @{ */

#define MC_CGM_MUX_10_DC_0_DIV_MASK              (0x70000U)
#define MC_CGM_MUX_10_DC_0_DIV_SHIFT             (16U)
#define MC_CGM_MUX_10_DC_0_DIV_WIDTH             (3U)
#define MC_CGM_MUX_10_DC_0_DIV(x)                (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_10_DC_0_DIV_SHIFT)) & MC_CGM_MUX_10_DC_0_DIV_MASK)

#define MC_CGM_MUX_10_DC_0_DE_MASK               (0x80000000U)
#define MC_CGM_MUX_10_DC_0_DE_SHIFT              (31U)
#define MC_CGM_MUX_10_DC_0_DE_WIDTH              (1U)
#define MC_CGM_MUX_10_DC_0_DE(x)                 (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_10_DC_0_DE_SHIFT)) & MC_CGM_MUX_10_DC_0_DE_MASK)
/*! @} */

/*! @name MUX_10_DIV_UPD_STAT - Clock Mux 10 Divider Update Status Register */
/*! @{ */

#define MC_CGM_MUX_10_DIV_UPD_STAT_DIV_STAT_MASK (0x1U)
#define MC_CGM_MUX_10_DIV_UPD_STAT_DIV_STAT_SHIFT (0U)
#define MC_CGM_MUX_10_DIV_UPD_STAT_DIV_STAT_WIDTH (1U)
#define MC_CGM_MUX_10_DIV_UPD_STAT_DIV_STAT(x)   (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_10_DIV_UPD_STAT_DIV_STAT_SHIFT)) & MC_CGM_MUX_10_DIV_UPD_STAT_DIV_STAT_MASK)
/*! @} */

/*! @name MUX_11_CSC - Clock Mux 11 Select Control Register */
/*! @{ */

#define MC_CGM_MUX_11_CSC_CG_MASK                (0x4U)
#define MC_CGM_MUX_11_CSC_CG_SHIFT               (2U)
#define MC_CGM_MUX_11_CSC_CG_WIDTH               (1U)
#define MC_CGM_MUX_11_CSC_CG(x)                  (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_11_CSC_CG_SHIFT)) & MC_CGM_MUX_11_CSC_CG_MASK)

#define MC_CGM_MUX_11_CSC_FCG_MASK               (0x8U)
#define MC_CGM_MUX_11_CSC_FCG_SHIFT              (3U)
#define MC_CGM_MUX_11_CSC_FCG_WIDTH              (1U)
#define MC_CGM_MUX_11_CSC_FCG(x)                 (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_11_CSC_FCG_SHIFT)) & MC_CGM_MUX_11_CSC_FCG_MASK)

#define MC_CGM_MUX_11_CSC_SELCTL_MASK            (0xF000000U)
#define MC_CGM_MUX_11_CSC_SELCTL_SHIFT           (24U)
#define MC_CGM_MUX_11_CSC_SELCTL_WIDTH           (4U)
#define MC_CGM_MUX_11_CSC_SELCTL(x)              (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_11_CSC_SELCTL_SHIFT)) & MC_CGM_MUX_11_CSC_SELCTL_MASK)
/*! @} */

/*! @name MUX_11_CSS - Clock Mux 11 Select Status Register */
/*! @{ */

#define MC_CGM_MUX_11_CSS_GRIP_MASK              (0x10000U)
#define MC_CGM_MUX_11_CSS_GRIP_SHIFT             (16U)
#define MC_CGM_MUX_11_CSS_GRIP_WIDTH             (1U)
#define MC_CGM_MUX_11_CSS_GRIP(x)                (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_11_CSS_GRIP_SHIFT)) & MC_CGM_MUX_11_CSS_GRIP_MASK)

#define MC_CGM_MUX_11_CSS_CS_MASK                (0x20000U)
#define MC_CGM_MUX_11_CSS_CS_SHIFT               (17U)
#define MC_CGM_MUX_11_CSS_CS_WIDTH               (1U)
#define MC_CGM_MUX_11_CSS_CS(x)                  (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_11_CSS_CS_SHIFT)) & MC_CGM_MUX_11_CSS_CS_MASK)

#define MC_CGM_MUX_11_CSS_SELSTAT_MASK           (0xF000000U)
#define MC_CGM_MUX_11_CSS_SELSTAT_SHIFT          (24U)
#define MC_CGM_MUX_11_CSS_SELSTAT_WIDTH          (4U)
#define MC_CGM_MUX_11_CSS_SELSTAT(x)             (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_11_CSS_SELSTAT_SHIFT)) & MC_CGM_MUX_11_CSS_SELSTAT_MASK)
/*! @} */

/*! @name MUX_11_DC_0 - Clock Mux 11 Divider 0 Control Register */
/*! @{ */

#define MC_CGM_MUX_11_DC_0_DIV_MASK              (0xF0000U)
#define MC_CGM_MUX_11_DC_0_DIV_SHIFT             (16U)
#define MC_CGM_MUX_11_DC_0_DIV_WIDTH             (4U)
#define MC_CGM_MUX_11_DC_0_DIV(x)                (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_11_DC_0_DIV_SHIFT)) & MC_CGM_MUX_11_DC_0_DIV_MASK)

#define MC_CGM_MUX_11_DC_0_DE_MASK               (0x80000000U)
#define MC_CGM_MUX_11_DC_0_DE_SHIFT              (31U)
#define MC_CGM_MUX_11_DC_0_DE_WIDTH              (1U)
#define MC_CGM_MUX_11_DC_0_DE(x)                 (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_11_DC_0_DE_SHIFT)) & MC_CGM_MUX_11_DC_0_DE_MASK)
/*! @} */

/*! @name MUX_11_DIV_UPD_STAT - Clock Mux 11 Divider Update Status Register */
/*! @{ */

#define MC_CGM_MUX_11_DIV_UPD_STAT_DIV_STAT_MASK (0x1U)
#define MC_CGM_MUX_11_DIV_UPD_STAT_DIV_STAT_SHIFT (0U)
#define MC_CGM_MUX_11_DIV_UPD_STAT_DIV_STAT_WIDTH (1U)
#define MC_CGM_MUX_11_DIV_UPD_STAT_DIV_STAT(x)   (((uint32_t)(((uint32_t)(x)) << MC_CGM_MUX_11_DIV_UPD_STAT_DIV_STAT_SHIFT)) & MC_CGM_MUX_11_DIV_UPD_STAT_DIV_STAT_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group MC_CGM_Register_Masks */

/*!
 * @}
 */ /* end of group MC_CGM_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_MC_CGM_H_) */
