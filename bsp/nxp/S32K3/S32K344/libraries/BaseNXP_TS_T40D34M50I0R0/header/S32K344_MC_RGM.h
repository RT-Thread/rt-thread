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
 * @file S32K344_MC_RGM.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_MC_RGM
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
#if !defined(S32K344_MC_RGM_H_)  /* Check if memory map has not been already included */
#define S32K344_MC_RGM_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- MC_RGM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MC_RGM_Peripheral_Access_Layer MC_RGM Peripheral Access Layer
 * @{
 */

/** MC_RGM - Register Layout Typedef */
typedef struct {
  __IO uint32_t DES;                               /**< Destructive Event Status Register, offset: 0x0 */
  uint8_t RESERVED_0[4];
  __IO uint32_t FES;                               /**< Functional /External Reset Status Register, offset: 0x8 */
  __IO uint32_t FERD;                              /**< Functional Event Reset Disable Register, offset: 0xC */
  __IO uint32_t FBRE;                              /**< Functional Bidirectional Reset Enable Register, offset: 0x10 */
  __IO uint32_t FREC;                              /**< Functional Reset Escalation Counter Register, offset: 0x14 */
  __IO uint32_t FRET;                              /**< Functional Reset Escalation Threshold Register, offset: 0x18 */
  __IO uint32_t DRET;                              /**< Destructive Reset Escalation Threshold Register, offset: 0x1C */
  __IO uint32_t ERCTRL;                            /**< External Reset Control Register, offset: 0x20 */
  __IO uint32_t RDSS;                              /**< Reset During Standby Status Register, offset: 0x24 */
  __IO uint32_t FRENTC;                            /**< Functional Reset Entry Timeout Control Register, offset: 0x28 */
  __I  uint32_t LPDEBUG;                           /**< Low Power Debug Control Register, offset: 0x2C */
} MC_RGM_Type, *MC_RGM_MemMapPtr;

/** Number of instances of the MC_RGM module. */
#define MC_RGM_INSTANCE_COUNT                    (1u)

/* MC_RGM - Peripheral instance base addresses */
/** Peripheral MC_RGM base address */
#define IP_MC_RGM_BASE                           (0x4028C000u)
/** Peripheral MC_RGM base pointer */
#define IP_MC_RGM                                ((MC_RGM_Type *)IP_MC_RGM_BASE)
/** Array initializer of MC_RGM peripheral base addresses */
#define IP_MC_RGM_BASE_ADDRS                     { IP_MC_RGM_BASE }
/** Array initializer of MC_RGM peripheral base pointers */
#define IP_MC_RGM_BASE_PTRS                      { IP_MC_RGM }

/* ----------------------------------------------------------------------------
   -- MC_RGM Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup MC_RGM_Register_Masks MC_RGM Register Masks
 * @{
 */

/*! @name DES - Destructive Event Status Register */
/*! @{ */

#define MC_RGM_DES_F_POR_MASK                    (0x1U)
#define MC_RGM_DES_F_POR_SHIFT                   (0U)
#define MC_RGM_DES_F_POR_WIDTH                   (1U)
#define MC_RGM_DES_F_POR(x)                      (((uint32_t)(((uint32_t)(x)) << MC_RGM_DES_F_POR_SHIFT)) & MC_RGM_DES_F_POR_MASK)

#define MC_RGM_DES_FCCU_FTR_MASK                 (0x8U)
#define MC_RGM_DES_FCCU_FTR_SHIFT                (3U)
#define MC_RGM_DES_FCCU_FTR_WIDTH                (1U)
#define MC_RGM_DES_FCCU_FTR(x)                   (((uint32_t)(((uint32_t)(x)) << MC_RGM_DES_FCCU_FTR_SHIFT)) & MC_RGM_DES_FCCU_FTR_MASK)

#define MC_RGM_DES_STCU_URF_MASK                 (0x10U)
#define MC_RGM_DES_STCU_URF_SHIFT                (4U)
#define MC_RGM_DES_STCU_URF_WIDTH                (1U)
#define MC_RGM_DES_STCU_URF(x)                   (((uint32_t)(((uint32_t)(x)) << MC_RGM_DES_STCU_URF_SHIFT)) & MC_RGM_DES_STCU_URF_MASK)

#define MC_RGM_DES_MC_RGM_FRE_MASK               (0x40U)
#define MC_RGM_DES_MC_RGM_FRE_SHIFT              (6U)
#define MC_RGM_DES_MC_RGM_FRE_WIDTH              (1U)
#define MC_RGM_DES_MC_RGM_FRE(x)                 (((uint32_t)(((uint32_t)(x)) << MC_RGM_DES_MC_RGM_FRE_SHIFT)) & MC_RGM_DES_MC_RGM_FRE_MASK)

#define MC_RGM_DES_FXOSC_FAIL_MASK               (0x100U)
#define MC_RGM_DES_FXOSC_FAIL_SHIFT              (8U)
#define MC_RGM_DES_FXOSC_FAIL_WIDTH              (1U)
#define MC_RGM_DES_FXOSC_FAIL(x)                 (((uint32_t)(((uint32_t)(x)) << MC_RGM_DES_FXOSC_FAIL_SHIFT)) & MC_RGM_DES_FXOSC_FAIL_MASK)

#define MC_RGM_DES_PLL_LOL_MASK                  (0x200U)
#define MC_RGM_DES_PLL_LOL_SHIFT                 (9U)
#define MC_RGM_DES_PLL_LOL_WIDTH                 (1U)
#define MC_RGM_DES_PLL_LOL(x)                    (((uint32_t)(((uint32_t)(x)) << MC_RGM_DES_PLL_LOL_SHIFT)) & MC_RGM_DES_PLL_LOL_MASK)

#define MC_RGM_DES_CORE_CLK_FAIL_MASK            (0x400U)
#define MC_RGM_DES_CORE_CLK_FAIL_SHIFT           (10U)
#define MC_RGM_DES_CORE_CLK_FAIL_WIDTH           (1U)
#define MC_RGM_DES_CORE_CLK_FAIL(x)              (((uint32_t)(((uint32_t)(x)) << MC_RGM_DES_CORE_CLK_FAIL_SHIFT)) & MC_RGM_DES_CORE_CLK_FAIL_MASK)

#define MC_RGM_DES_AIPS_PLAT_CLK_FAIL_MASK       (0x1000U)
#define MC_RGM_DES_AIPS_PLAT_CLK_FAIL_SHIFT      (12U)
#define MC_RGM_DES_AIPS_PLAT_CLK_FAIL_WIDTH      (1U)
#define MC_RGM_DES_AIPS_PLAT_CLK_FAIL(x)         (((uint32_t)(((uint32_t)(x)) << MC_RGM_DES_AIPS_PLAT_CLK_FAIL_SHIFT)) & MC_RGM_DES_AIPS_PLAT_CLK_FAIL_MASK)

#define MC_RGM_DES_HSE_CLK_FAIL_MASK             (0x4000U)
#define MC_RGM_DES_HSE_CLK_FAIL_SHIFT            (14U)
#define MC_RGM_DES_HSE_CLK_FAIL_WIDTH            (1U)
#define MC_RGM_DES_HSE_CLK_FAIL(x)               (((uint32_t)(((uint32_t)(x)) << MC_RGM_DES_HSE_CLK_FAIL_SHIFT)) & MC_RGM_DES_HSE_CLK_FAIL_MASK)

#define MC_RGM_DES_SYS_DIV_FAIL_MASK             (0x8000U)
#define MC_RGM_DES_SYS_DIV_FAIL_SHIFT            (15U)
#define MC_RGM_DES_SYS_DIV_FAIL_WIDTH            (1U)
#define MC_RGM_DES_SYS_DIV_FAIL(x)               (((uint32_t)(((uint32_t)(x)) << MC_RGM_DES_SYS_DIV_FAIL_SHIFT)) & MC_RGM_DES_SYS_DIV_FAIL_MASK)

#define MC_RGM_DES_HSE_TMPR_RST_MASK             (0x20000U)
#define MC_RGM_DES_HSE_TMPR_RST_SHIFT            (17U)
#define MC_RGM_DES_HSE_TMPR_RST_WIDTH            (1U)
#define MC_RGM_DES_HSE_TMPR_RST(x)               (((uint32_t)(((uint32_t)(x)) << MC_RGM_DES_HSE_TMPR_RST_SHIFT)) & MC_RGM_DES_HSE_TMPR_RST_MASK)

#define MC_RGM_DES_HSE_SNVS_RST_MASK             (0x40000U)
#define MC_RGM_DES_HSE_SNVS_RST_SHIFT            (18U)
#define MC_RGM_DES_HSE_SNVS_RST_WIDTH            (1U)
#define MC_RGM_DES_HSE_SNVS_RST(x)               (((uint32_t)(((uint32_t)(x)) << MC_RGM_DES_HSE_SNVS_RST_SHIFT)) & MC_RGM_DES_HSE_SNVS_RST_MASK)

#define MC_RGM_DES_SW_DEST_MASK                  (0x20000000U)
#define MC_RGM_DES_SW_DEST_SHIFT                 (29U)
#define MC_RGM_DES_SW_DEST_WIDTH                 (1U)
#define MC_RGM_DES_SW_DEST(x)                    (((uint32_t)(((uint32_t)(x)) << MC_RGM_DES_SW_DEST_SHIFT)) & MC_RGM_DES_SW_DEST_MASK)

#define MC_RGM_DES_DEBUG_DEST_MASK               (0x40000000U)
#define MC_RGM_DES_DEBUG_DEST_SHIFT              (30U)
#define MC_RGM_DES_DEBUG_DEST_WIDTH              (1U)
#define MC_RGM_DES_DEBUG_DEST(x)                 (((uint32_t)(((uint32_t)(x)) << MC_RGM_DES_DEBUG_DEST_SHIFT)) & MC_RGM_DES_DEBUG_DEST_MASK)
/*! @} */

/*! @name FES - Functional /External Reset Status Register */
/*! @{ */

#define MC_RGM_FES_F_EXR_MASK                    (0x1U)
#define MC_RGM_FES_F_EXR_SHIFT                   (0U)
#define MC_RGM_FES_F_EXR_WIDTH                   (1U)
#define MC_RGM_FES_F_EXR(x)                      (((uint32_t)(((uint32_t)(x)) << MC_RGM_FES_F_EXR_SHIFT)) & MC_RGM_FES_F_EXR_MASK)

#define MC_RGM_FES_FCCU_RST_MASK                 (0x8U)
#define MC_RGM_FES_FCCU_RST_SHIFT                (3U)
#define MC_RGM_FES_FCCU_RST_WIDTH                (1U)
#define MC_RGM_FES_FCCU_RST(x)                   (((uint32_t)(((uint32_t)(x)) << MC_RGM_FES_FCCU_RST_SHIFT)) & MC_RGM_FES_FCCU_RST_MASK)

#define MC_RGM_FES_ST_DONE_MASK                  (0x10U)
#define MC_RGM_FES_ST_DONE_SHIFT                 (4U)
#define MC_RGM_FES_ST_DONE_WIDTH                 (1U)
#define MC_RGM_FES_ST_DONE(x)                    (((uint32_t)(((uint32_t)(x)) << MC_RGM_FES_ST_DONE_SHIFT)) & MC_RGM_FES_ST_DONE_MASK)

#define MC_RGM_FES_SWT0_RST_MASK                 (0x40U)
#define MC_RGM_FES_SWT0_RST_SHIFT                (6U)
#define MC_RGM_FES_SWT0_RST_WIDTH                (1U)
#define MC_RGM_FES_SWT0_RST(x)                   (((uint32_t)(((uint32_t)(x)) << MC_RGM_FES_SWT0_RST_SHIFT)) & MC_RGM_FES_SWT0_RST_MASK)

#define MC_RGM_FES_JTAG_RST_MASK                 (0x200U)
#define MC_RGM_FES_JTAG_RST_SHIFT                (9U)
#define MC_RGM_FES_JTAG_RST_WIDTH                (1U)
#define MC_RGM_FES_JTAG_RST(x)                   (((uint32_t)(((uint32_t)(x)) << MC_RGM_FES_JTAG_RST_SHIFT)) & MC_RGM_FES_JTAG_RST_MASK)

#define MC_RGM_FES_HSE_SWT_RST_MASK              (0x10000U)
#define MC_RGM_FES_HSE_SWT_RST_SHIFT             (16U)
#define MC_RGM_FES_HSE_SWT_RST_WIDTH             (1U)
#define MC_RGM_FES_HSE_SWT_RST(x)                (((uint32_t)(((uint32_t)(x)) << MC_RGM_FES_HSE_SWT_RST_SHIFT)) & MC_RGM_FES_HSE_SWT_RST_MASK)

#define MC_RGM_FES_HSE_BOOT_RST_MASK             (0x100000U)
#define MC_RGM_FES_HSE_BOOT_RST_SHIFT            (20U)
#define MC_RGM_FES_HSE_BOOT_RST_WIDTH            (1U)
#define MC_RGM_FES_HSE_BOOT_RST(x)               (((uint32_t)(((uint32_t)(x)) << MC_RGM_FES_HSE_BOOT_RST_SHIFT)) & MC_RGM_FES_HSE_BOOT_RST_MASK)

#define MC_RGM_FES_SW_FUNC_MASK                  (0x20000000U)
#define MC_RGM_FES_SW_FUNC_SHIFT                 (29U)
#define MC_RGM_FES_SW_FUNC_WIDTH                 (1U)
#define MC_RGM_FES_SW_FUNC(x)                    (((uint32_t)(((uint32_t)(x)) << MC_RGM_FES_SW_FUNC_SHIFT)) & MC_RGM_FES_SW_FUNC_MASK)

#define MC_RGM_FES_DEBUG_FUNC_MASK               (0x40000000U)
#define MC_RGM_FES_DEBUG_FUNC_SHIFT              (30U)
#define MC_RGM_FES_DEBUG_FUNC_WIDTH              (1U)
#define MC_RGM_FES_DEBUG_FUNC(x)                 (((uint32_t)(((uint32_t)(x)) << MC_RGM_FES_DEBUG_FUNC_SHIFT)) & MC_RGM_FES_DEBUG_FUNC_MASK)
/*! @} */

/*! @name FERD - Functional Event Reset Disable Register */
/*! @{ */

#define MC_RGM_FERD_D_FCCU_RST_MASK              (0x8U)
#define MC_RGM_FERD_D_FCCU_RST_SHIFT             (3U)
#define MC_RGM_FERD_D_FCCU_RST_WIDTH             (1U)
#define MC_RGM_FERD_D_FCCU_RST(x)                (((uint32_t)(((uint32_t)(x)) << MC_RGM_FERD_D_FCCU_RST_SHIFT)) & MC_RGM_FERD_D_FCCU_RST_MASK)

#define MC_RGM_FERD_D_SWT0_RST_MASK              (0x40U)
#define MC_RGM_FERD_D_SWT0_RST_SHIFT             (6U)
#define MC_RGM_FERD_D_SWT0_RST_WIDTH             (1U)
#define MC_RGM_FERD_D_SWT0_RST(x)                (((uint32_t)(((uint32_t)(x)) << MC_RGM_FERD_D_SWT0_RST_SHIFT)) & MC_RGM_FERD_D_SWT0_RST_MASK)

#define MC_RGM_FERD_D_JTAG_RST_MASK              (0x200U)
#define MC_RGM_FERD_D_JTAG_RST_SHIFT             (9U)
#define MC_RGM_FERD_D_JTAG_RST_WIDTH             (1U)
#define MC_RGM_FERD_D_JTAG_RST(x)                (((uint32_t)(((uint32_t)(x)) << MC_RGM_FERD_D_JTAG_RST_SHIFT)) & MC_RGM_FERD_D_JTAG_RST_MASK)

#define MC_RGM_FERD_D_DEBUG_FUNC_MASK            (0x40000000U)
#define MC_RGM_FERD_D_DEBUG_FUNC_SHIFT           (30U)
#define MC_RGM_FERD_D_DEBUG_FUNC_WIDTH           (1U)
#define MC_RGM_FERD_D_DEBUG_FUNC(x)              (((uint32_t)(((uint32_t)(x)) << MC_RGM_FERD_D_DEBUG_FUNC_SHIFT)) & MC_RGM_FERD_D_DEBUG_FUNC_MASK)
/*! @} */

/*! @name FBRE - Functional Bidirectional Reset Enable Register */
/*! @{ */

#define MC_RGM_FBRE_BE_FCCU_RST_MASK             (0x8U)
#define MC_RGM_FBRE_BE_FCCU_RST_SHIFT            (3U)
#define MC_RGM_FBRE_BE_FCCU_RST_WIDTH            (1U)
#define MC_RGM_FBRE_BE_FCCU_RST(x)               (((uint32_t)(((uint32_t)(x)) << MC_RGM_FBRE_BE_FCCU_RST_SHIFT)) & MC_RGM_FBRE_BE_FCCU_RST_MASK)

#define MC_RGM_FBRE_BE_ST_DONE_MASK              (0x10U)
#define MC_RGM_FBRE_BE_ST_DONE_SHIFT             (4U)
#define MC_RGM_FBRE_BE_ST_DONE_WIDTH             (1U)
#define MC_RGM_FBRE_BE_ST_DONE(x)                (((uint32_t)(((uint32_t)(x)) << MC_RGM_FBRE_BE_ST_DONE_SHIFT)) & MC_RGM_FBRE_BE_ST_DONE_MASK)

#define MC_RGM_FBRE_BE_SWT0_RST_MASK             (0x40U)
#define MC_RGM_FBRE_BE_SWT0_RST_SHIFT            (6U)
#define MC_RGM_FBRE_BE_SWT0_RST_WIDTH            (1U)
#define MC_RGM_FBRE_BE_SWT0_RST(x)               (((uint32_t)(((uint32_t)(x)) << MC_RGM_FBRE_BE_SWT0_RST_SHIFT)) & MC_RGM_FBRE_BE_SWT0_RST_MASK)

#define MC_RGM_FBRE_BE_JTAG_RST_MASK             (0x200U)
#define MC_RGM_FBRE_BE_JTAG_RST_SHIFT            (9U)
#define MC_RGM_FBRE_BE_JTAG_RST_WIDTH            (1U)
#define MC_RGM_FBRE_BE_JTAG_RST(x)               (((uint32_t)(((uint32_t)(x)) << MC_RGM_FBRE_BE_JTAG_RST_SHIFT)) & MC_RGM_FBRE_BE_JTAG_RST_MASK)

#define MC_RGM_FBRE_BE_HSE_SWT_RST_MASK          (0x10000U)
#define MC_RGM_FBRE_BE_HSE_SWT_RST_SHIFT         (16U)
#define MC_RGM_FBRE_BE_HSE_SWT_RST_WIDTH         (1U)
#define MC_RGM_FBRE_BE_HSE_SWT_RST(x)            (((uint32_t)(((uint32_t)(x)) << MC_RGM_FBRE_BE_HSE_SWT_RST_SHIFT)) & MC_RGM_FBRE_BE_HSE_SWT_RST_MASK)

#define MC_RGM_FBRE_BE_HSE_BOOT_RST_MASK         (0x100000U)
#define MC_RGM_FBRE_BE_HSE_BOOT_RST_SHIFT        (20U)
#define MC_RGM_FBRE_BE_HSE_BOOT_RST_WIDTH        (1U)
#define MC_RGM_FBRE_BE_HSE_BOOT_RST(x)           (((uint32_t)(((uint32_t)(x)) << MC_RGM_FBRE_BE_HSE_BOOT_RST_SHIFT)) & MC_RGM_FBRE_BE_HSE_BOOT_RST_MASK)

#define MC_RGM_FBRE_BE_SW_FUNC_MASK              (0x20000000U)
#define MC_RGM_FBRE_BE_SW_FUNC_SHIFT             (29U)
#define MC_RGM_FBRE_BE_SW_FUNC_WIDTH             (1U)
#define MC_RGM_FBRE_BE_SW_FUNC(x)                (((uint32_t)(((uint32_t)(x)) << MC_RGM_FBRE_BE_SW_FUNC_SHIFT)) & MC_RGM_FBRE_BE_SW_FUNC_MASK)

#define MC_RGM_FBRE_BE_DEBUG_FUNC_MASK           (0x40000000U)
#define MC_RGM_FBRE_BE_DEBUG_FUNC_SHIFT          (30U)
#define MC_RGM_FBRE_BE_DEBUG_FUNC_WIDTH          (1U)
#define MC_RGM_FBRE_BE_DEBUG_FUNC(x)             (((uint32_t)(((uint32_t)(x)) << MC_RGM_FBRE_BE_DEBUG_FUNC_SHIFT)) & MC_RGM_FBRE_BE_DEBUG_FUNC_MASK)
/*! @} */

/*! @name FREC - Functional Reset Escalation Counter Register */
/*! @{ */

#define MC_RGM_FREC_FREC_MASK                    (0xFU)
#define MC_RGM_FREC_FREC_SHIFT                   (0U)
#define MC_RGM_FREC_FREC_WIDTH                   (4U)
#define MC_RGM_FREC_FREC(x)                      (((uint32_t)(((uint32_t)(x)) << MC_RGM_FREC_FREC_SHIFT)) & MC_RGM_FREC_FREC_MASK)
/*! @} */

/*! @name FRET - Functional Reset Escalation Threshold Register */
/*! @{ */

#define MC_RGM_FRET_FRET_MASK                    (0xFU)
#define MC_RGM_FRET_FRET_SHIFT                   (0U)
#define MC_RGM_FRET_FRET_WIDTH                   (4U)
#define MC_RGM_FRET_FRET(x)                      (((uint32_t)(((uint32_t)(x)) << MC_RGM_FRET_FRET_SHIFT)) & MC_RGM_FRET_FRET_MASK)
/*! @} */

/*! @name DRET - Destructive Reset Escalation Threshold Register */
/*! @{ */

#define MC_RGM_DRET_DRET_MASK                    (0xFU)
#define MC_RGM_DRET_DRET_SHIFT                   (0U)
#define MC_RGM_DRET_DRET_WIDTH                   (4U)
#define MC_RGM_DRET_DRET(x)                      (((uint32_t)(((uint32_t)(x)) << MC_RGM_DRET_DRET_SHIFT)) & MC_RGM_DRET_DRET_MASK)
/*! @} */

/*! @name ERCTRL - External Reset Control Register */
/*! @{ */

#define MC_RGM_ERCTRL_ERASSERT_MASK              (0x1U)
#define MC_RGM_ERCTRL_ERASSERT_SHIFT             (0U)
#define MC_RGM_ERCTRL_ERASSERT_WIDTH             (1U)
#define MC_RGM_ERCTRL_ERASSERT(x)                (((uint32_t)(((uint32_t)(x)) << MC_RGM_ERCTRL_ERASSERT_SHIFT)) & MC_RGM_ERCTRL_ERASSERT_MASK)
/*! @} */

/*! @name RDSS - Reset During Standby Status Register */
/*! @{ */

#define MC_RGM_RDSS_DES_RES_MASK                 (0x1U)
#define MC_RGM_RDSS_DES_RES_SHIFT                (0U)
#define MC_RGM_RDSS_DES_RES_WIDTH                (1U)
#define MC_RGM_RDSS_DES_RES(x)                   (((uint32_t)(((uint32_t)(x)) << MC_RGM_RDSS_DES_RES_SHIFT)) & MC_RGM_RDSS_DES_RES_MASK)

#define MC_RGM_RDSS_FES_RES_MASK                 (0x2U)
#define MC_RGM_RDSS_FES_RES_SHIFT                (1U)
#define MC_RGM_RDSS_FES_RES_WIDTH                (1U)
#define MC_RGM_RDSS_FES_RES(x)                   (((uint32_t)(((uint32_t)(x)) << MC_RGM_RDSS_FES_RES_SHIFT)) & MC_RGM_RDSS_FES_RES_MASK)
/*! @} */

/*! @name FRENTC - Functional Reset Entry Timeout Control Register */
/*! @{ */

#define MC_RGM_FRENTC_FRET_EN_MASK               (0x1U)
#define MC_RGM_FRENTC_FRET_EN_SHIFT              (0U)
#define MC_RGM_FRENTC_FRET_EN_WIDTH              (1U)
#define MC_RGM_FRENTC_FRET_EN(x)                 (((uint32_t)(((uint32_t)(x)) << MC_RGM_FRENTC_FRET_EN_SHIFT)) & MC_RGM_FRENTC_FRET_EN_MASK)

#define MC_RGM_FRENTC_FRET_TIMEOUT_MASK          (0xFFFFFFFEU)
#define MC_RGM_FRENTC_FRET_TIMEOUT_SHIFT         (1U)
#define MC_RGM_FRENTC_FRET_TIMEOUT_WIDTH         (31U)
#define MC_RGM_FRENTC_FRET_TIMEOUT(x)            (((uint32_t)(((uint32_t)(x)) << MC_RGM_FRENTC_FRET_TIMEOUT_SHIFT)) & MC_RGM_FRENTC_FRET_TIMEOUT_MASK)
/*! @} */

/*! @name LPDEBUG - Low Power Debug Control Register */
/*! @{ */

#define MC_RGM_LPDEBUG_LP_DBG_EN_MASK            (0x1U)
#define MC_RGM_LPDEBUG_LP_DBG_EN_SHIFT           (0U)
#define MC_RGM_LPDEBUG_LP_DBG_EN_WIDTH           (1U)
#define MC_RGM_LPDEBUG_LP_DBG_EN(x)              (((uint32_t)(((uint32_t)(x)) << MC_RGM_LPDEBUG_LP_DBG_EN_SHIFT)) & MC_RGM_LPDEBUG_LP_DBG_EN_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group MC_RGM_Register_Masks */

/*!
 * @}
 */ /* end of group MC_RGM_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_MC_RGM_H_) */
