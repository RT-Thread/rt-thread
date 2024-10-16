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
 * @file S32K344_CONFIGURATION_GPR.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_CONFIGURATION_GPR
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
#if !defined(S32K344_CONFIGURATION_GPR_H_)  /* Check if memory map has not been already included */
#define S32K344_CONFIGURATION_GPR_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- CONFIGURATION_GPR Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CONFIGURATION_GPR_Peripheral_Access_Layer CONFIGURATION_GPR Peripheral Access Layer
 * @{
 */

/** CONFIGURATION_GPR - Register Layout Typedef */
typedef struct {
  uint8_t RESERVED_0[28];
  __I  uint32_t CONFIG_REG0;                       /**< General Purpose Configuration 0, offset: 0x1C */
  uint8_t RESERVED_1[20];
  __I  uint32_t CONFIG_REG6;                       /**< General Purpose Configuration 6, offset: 0x34 */
  __I  uint32_t CONFIG_RAMPR;                      /**< Configuration RAM Protected Region, offset: 0x38 */
  __I  uint32_t CONFIG_CFPRL;                      /**< Configuration Code Flash Memory Active Block, offset: 0x3C */
  __I  uint32_t CONFIG_CFPRH;                      /**< Configuration Code Flash Memory Passive Block, offset: 0x40 */
  __I  uint32_t CONFIG_DFPR;                       /**< Configuration Data Flash Memory Protected Region, offset: 0x44 */
  uint8_t RESERVED_2[8];
  __I  uint32_t CONFIG_PE_LOCK;                    /**< Configuration Program and Erase Lock, offset: 0x50 */
  __I  uint32_t CONFIG_RAMPR_ALT;                  /**< Configuration RAM Protected Region Alternate, offset: 0x54 */
  __I  uint32_t CONFIG_CFPRL_ALT;                  /**< Configuration Code Flash Memory Active Block Alternate, offset: 0x58 */
  __I  uint32_t CONFIG_CFPRH_ALT;                  /**< Configuration Code Flash Memory Passive Block Alternate, offset: 0x5C */
  __I  uint32_t CONFIG_DFPR_ALT;                   /**< Configuration Data Flash Memory Protected Region Alternate, offset: 0x60 */
  __IO uint32_t CONFIG_REG_GPR;                    /**< Configuration REG_GPR, offset: 0x64 */
} CONFIGURATION_GPR_Type, *CONFIGURATION_GPR_MemMapPtr;

/** Number of instances of the CONFIGURATION_GPR module. */
#define CONFIGURATION_GPR_INSTANCE_COUNT         (1u)

/* CONFIGURATION_GPR - Peripheral instance base addresses */
/** Peripheral CONFIGURATION_GPR base address */
#define IP_CONFIGURATION_GPR_BASE                (0x4039C000u)
/** Peripheral CONFIGURATION_GPR base pointer */
#define IP_CONFIGURATION_GPR                     ((CONFIGURATION_GPR_Type *)IP_CONFIGURATION_GPR_BASE)
/** Array initializer of CONFIGURATION_GPR peripheral base addresses */
#define IP_CONFIGURATION_GPR_BASE_ADDRS          { IP_CONFIGURATION_GPR_BASE }
/** Array initializer of CONFIGURATION_GPR peripheral base pointers */
#define IP_CONFIGURATION_GPR_BASE_PTRS           { IP_CONFIGURATION_GPR }

/* ----------------------------------------------------------------------------
   -- CONFIGURATION_GPR Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CONFIGURATION_GPR_Register_Masks CONFIGURATION_GPR Register Masks
 * @{
 */

/*! @name CONFIG_REG0 - General Purpose Configuration 0 */
/*! @{ */

#define CONFIGURATION_GPR_CONFIG_REG0_EDB_MASK   (0x40U)
#define CONFIGURATION_GPR_CONFIG_REG0_EDB_SHIFT  (6U)
#define CONFIGURATION_GPR_CONFIG_REG0_EDB_WIDTH  (1U)
#define CONFIGURATION_GPR_CONFIG_REG0_EDB(x)     (((uint32_t)(((uint32_t)(x)) << CONFIGURATION_GPR_CONFIG_REG0_EDB_SHIFT)) & CONFIGURATION_GPR_CONFIG_REG0_EDB_MASK)
/*! @} */

/*! @name CONFIG_REG6 - General Purpose Configuration 6 */
/*! @{ */

#define CONFIGURATION_GPR_CONFIG_REG6_QUADSPI_SDID_PCTL_MASK (0x1U)
#define CONFIGURATION_GPR_CONFIG_REG6_QUADSPI_SDID_PCTL_SHIFT (0U)
#define CONFIGURATION_GPR_CONFIG_REG6_QUADSPI_SDID_PCTL_WIDTH (1U)
#define CONFIGURATION_GPR_CONFIG_REG6_QUADSPI_SDID_PCTL(x) (((uint32_t)(((uint32_t)(x)) << CONFIGURATION_GPR_CONFIG_REG6_QUADSPI_SDID_PCTL_SHIFT)) & CONFIGURATION_GPR_CONFIG_REG6_QUADSPI_SDID_PCTL_MASK)

#define CONFIGURATION_GPR_CONFIG_REG6_EMAC_CLOCK_GATE_MASK (0x4U)
#define CONFIGURATION_GPR_CONFIG_REG6_EMAC_CLOCK_GATE_SHIFT (2U)
#define CONFIGURATION_GPR_CONFIG_REG6_EMAC_CLOCK_GATE_WIDTH (1U)
#define CONFIGURATION_GPR_CONFIG_REG6_EMAC_CLOCK_GATE(x) (((uint32_t)(((uint32_t)(x)) << CONFIGURATION_GPR_CONFIG_REG6_EMAC_CLOCK_GATE_SHIFT)) & CONFIGURATION_GPR_CONFIG_REG6_EMAC_CLOCK_GATE_MASK)

#define CONFIGURATION_GPR_CONFIG_REG6_FLEXIO_CLOCK_GATE_MASK (0x10U)
#define CONFIGURATION_GPR_CONFIG_REG6_FLEXIO_CLOCK_GATE_SHIFT (4U)
#define CONFIGURATION_GPR_CONFIG_REG6_FLEXIO_CLOCK_GATE_WIDTH (1U)
#define CONFIGURATION_GPR_CONFIG_REG6_FLEXIO_CLOCK_GATE(x) (((uint32_t)(((uint32_t)(x)) << CONFIGURATION_GPR_CONFIG_REG6_FLEXIO_CLOCK_GATE_SHIFT)) & CONFIGURATION_GPR_CONFIG_REG6_FLEXIO_CLOCK_GATE_MASK)

#define CONFIGURATION_GPR_CONFIG_REG6_SAI_SDID_PCTL_MASK (0x20U)
#define CONFIGURATION_GPR_CONFIG_REG6_SAI_SDID_PCTL_SHIFT (5U)
#define CONFIGURATION_GPR_CONFIG_REG6_SAI_SDID_PCTL_WIDTH (1U)
#define CONFIGURATION_GPR_CONFIG_REG6_SAI_SDID_PCTL(x) (((uint32_t)(((uint32_t)(x)) << CONFIGURATION_GPR_CONFIG_REG6_SAI_SDID_PCTL_SHIFT)) & CONFIGURATION_GPR_CONFIG_REG6_SAI_SDID_PCTL_MASK)

#define CONFIGURATION_GPR_CONFIG_REG6_HL_MASK    (0x80000000U)
#define CONFIGURATION_GPR_CONFIG_REG6_HL_SHIFT   (31U)
#define CONFIGURATION_GPR_CONFIG_REG6_HL_WIDTH   (1U)
#define CONFIGURATION_GPR_CONFIG_REG6_HL(x)      (((uint32_t)(((uint32_t)(x)) << CONFIGURATION_GPR_CONFIG_REG6_HL_SHIFT)) & CONFIGURATION_GPR_CONFIG_REG6_HL_MASK)
/*! @} */

/*! @name CONFIG_RAMPR - Configuration RAM Protected Region */
/*! @{ */

#define CONFIGURATION_GPR_CONFIG_RAMPR_SECURE_SIZE_MASK (0x1FFFE0U)
#define CONFIGURATION_GPR_CONFIG_RAMPR_SECURE_SIZE_SHIFT (5U)
#define CONFIGURATION_GPR_CONFIG_RAMPR_SECURE_SIZE_WIDTH (16U)
#define CONFIGURATION_GPR_CONFIG_RAMPR_SECURE_SIZE(x) (((uint32_t)(((uint32_t)(x)) << CONFIGURATION_GPR_CONFIG_RAMPR_SECURE_SIZE_SHIFT)) & CONFIGURATION_GPR_CONFIG_RAMPR_SECURE_SIZE_MASK)

#define CONFIGURATION_GPR_CONFIG_RAMPR_SOFT_LOCK_MASK (0x40000000U)
#define CONFIGURATION_GPR_CONFIG_RAMPR_SOFT_LOCK_SHIFT (30U)
#define CONFIGURATION_GPR_CONFIG_RAMPR_SOFT_LOCK_WIDTH (1U)
#define CONFIGURATION_GPR_CONFIG_RAMPR_SOFT_LOCK(x) (((uint32_t)(((uint32_t)(x)) << CONFIGURATION_GPR_CONFIG_RAMPR_SOFT_LOCK_SHIFT)) & CONFIGURATION_GPR_CONFIG_RAMPR_SOFT_LOCK_MASK)

#define CONFIGURATION_GPR_CONFIG_RAMPR_HARD_LOCK_MASK (0x80000000U)
#define CONFIGURATION_GPR_CONFIG_RAMPR_HARD_LOCK_SHIFT (31U)
#define CONFIGURATION_GPR_CONFIG_RAMPR_HARD_LOCK_WIDTH (1U)
#define CONFIGURATION_GPR_CONFIG_RAMPR_HARD_LOCK(x) (((uint32_t)(((uint32_t)(x)) << CONFIGURATION_GPR_CONFIG_RAMPR_HARD_LOCK_SHIFT)) & CONFIGURATION_GPR_CONFIG_RAMPR_HARD_LOCK_MASK)
/*! @} */

/*! @name CONFIG_CFPRL - Configuration Code Flash Memory Active Block */
/*! @{ */

#define CONFIGURATION_GPR_CONFIG_CFPRL_SECURE_SIZE_MASK (0x1FE000U)
#define CONFIGURATION_GPR_CONFIG_CFPRL_SECURE_SIZE_SHIFT (13U)
#define CONFIGURATION_GPR_CONFIG_CFPRL_SECURE_SIZE_WIDTH (8U)
#define CONFIGURATION_GPR_CONFIG_CFPRL_SECURE_SIZE(x) (((uint32_t)(((uint32_t)(x)) << CONFIGURATION_GPR_CONFIG_CFPRL_SECURE_SIZE_SHIFT)) & CONFIGURATION_GPR_CONFIG_CFPRL_SECURE_SIZE_MASK)

#define CONFIGURATION_GPR_CONFIG_CFPRL_SOFT_LOCK_MASK (0x40000000U)
#define CONFIGURATION_GPR_CONFIG_CFPRL_SOFT_LOCK_SHIFT (30U)
#define CONFIGURATION_GPR_CONFIG_CFPRL_SOFT_LOCK_WIDTH (1U)
#define CONFIGURATION_GPR_CONFIG_CFPRL_SOFT_LOCK(x) (((uint32_t)(((uint32_t)(x)) << CONFIGURATION_GPR_CONFIG_CFPRL_SOFT_LOCK_SHIFT)) & CONFIGURATION_GPR_CONFIG_CFPRL_SOFT_LOCK_MASK)

#define CONFIGURATION_GPR_CONFIG_CFPRL_HARD_LOCK_MASK (0x80000000U)
#define CONFIGURATION_GPR_CONFIG_CFPRL_HARD_LOCK_SHIFT (31U)
#define CONFIGURATION_GPR_CONFIG_CFPRL_HARD_LOCK_WIDTH (1U)
#define CONFIGURATION_GPR_CONFIG_CFPRL_HARD_LOCK(x) (((uint32_t)(((uint32_t)(x)) << CONFIGURATION_GPR_CONFIG_CFPRL_HARD_LOCK_SHIFT)) & CONFIGURATION_GPR_CONFIG_CFPRL_HARD_LOCK_MASK)
/*! @} */

/*! @name CONFIG_CFPRH - Configuration Code Flash Memory Passive Block */
/*! @{ */

#define CONFIGURATION_GPR_CONFIG_CFPRH_SECURE_SIZE_MASK (0x1FE000U)
#define CONFIGURATION_GPR_CONFIG_CFPRH_SECURE_SIZE_SHIFT (13U)
#define CONFIGURATION_GPR_CONFIG_CFPRH_SECURE_SIZE_WIDTH (8U)
#define CONFIGURATION_GPR_CONFIG_CFPRH_SECURE_SIZE(x) (((uint32_t)(((uint32_t)(x)) << CONFIGURATION_GPR_CONFIG_CFPRH_SECURE_SIZE_SHIFT)) & CONFIGURATION_GPR_CONFIG_CFPRH_SECURE_SIZE_MASK)

#define CONFIGURATION_GPR_CONFIG_CFPRH_SOFT_LOCK_MASK (0x40000000U)
#define CONFIGURATION_GPR_CONFIG_CFPRH_SOFT_LOCK_SHIFT (30U)
#define CONFIGURATION_GPR_CONFIG_CFPRH_SOFT_LOCK_WIDTH (1U)
#define CONFIGURATION_GPR_CONFIG_CFPRH_SOFT_LOCK(x) (((uint32_t)(((uint32_t)(x)) << CONFIGURATION_GPR_CONFIG_CFPRH_SOFT_LOCK_SHIFT)) & CONFIGURATION_GPR_CONFIG_CFPRH_SOFT_LOCK_MASK)

#define CONFIGURATION_GPR_CONFIG_CFPRH_HARD_LOCK_MASK (0x80000000U)
#define CONFIGURATION_GPR_CONFIG_CFPRH_HARD_LOCK_SHIFT (31U)
#define CONFIGURATION_GPR_CONFIG_CFPRH_HARD_LOCK_WIDTH (1U)
#define CONFIGURATION_GPR_CONFIG_CFPRH_HARD_LOCK(x) (((uint32_t)(((uint32_t)(x)) << CONFIGURATION_GPR_CONFIG_CFPRH_HARD_LOCK_SHIFT)) & CONFIGURATION_GPR_CONFIG_CFPRH_HARD_LOCK_MASK)
/*! @} */

/*! @name CONFIG_DFPR - Configuration Data Flash Memory Protected Region */
/*! @{ */

#define CONFIGURATION_GPR_CONFIG_DFPR_SECURE_SIZE_MASK (0x1FE000U)
#define CONFIGURATION_GPR_CONFIG_DFPR_SECURE_SIZE_SHIFT (13U)
#define CONFIGURATION_GPR_CONFIG_DFPR_SECURE_SIZE_WIDTH (8U)
#define CONFIGURATION_GPR_CONFIG_DFPR_SECURE_SIZE(x) (((uint32_t)(((uint32_t)(x)) << CONFIGURATION_GPR_CONFIG_DFPR_SECURE_SIZE_SHIFT)) & CONFIGURATION_GPR_CONFIG_DFPR_SECURE_SIZE_MASK)

#define CONFIGURATION_GPR_CONFIG_DFPR_SOFT_LOCK_MASK (0x40000000U)
#define CONFIGURATION_GPR_CONFIG_DFPR_SOFT_LOCK_SHIFT (30U)
#define CONFIGURATION_GPR_CONFIG_DFPR_SOFT_LOCK_WIDTH (1U)
#define CONFIGURATION_GPR_CONFIG_DFPR_SOFT_LOCK(x) (((uint32_t)(((uint32_t)(x)) << CONFIGURATION_GPR_CONFIG_DFPR_SOFT_LOCK_SHIFT)) & CONFIGURATION_GPR_CONFIG_DFPR_SOFT_LOCK_MASK)

#define CONFIGURATION_GPR_CONFIG_DFPR_HARD_LOCK_MASK (0x80000000U)
#define CONFIGURATION_GPR_CONFIG_DFPR_HARD_LOCK_SHIFT (31U)
#define CONFIGURATION_GPR_CONFIG_DFPR_HARD_LOCK_WIDTH (1U)
#define CONFIGURATION_GPR_CONFIG_DFPR_HARD_LOCK(x) (((uint32_t)(((uint32_t)(x)) << CONFIGURATION_GPR_CONFIG_DFPR_HARD_LOCK_SHIFT)) & CONFIGURATION_GPR_CONFIG_DFPR_HARD_LOCK_MASK)
/*! @} */

/*! @name CONFIG_PE_LOCK - Configuration Program and Erase Lock */
/*! @{ */

#define CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_BLOCK_0_MASK (0x1000U)
#define CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_BLOCK_0_SHIFT (12U)
#define CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_BLOCK_0_WIDTH (1U)
#define CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_BLOCK_0(x) (((uint32_t)(((uint32_t)(x)) << CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_BLOCK_0_SHIFT)) & CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_BLOCK_0_MASK)

#define CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_BLOCK_1_MASK (0x2000U)
#define CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_BLOCK_1_SHIFT (13U)
#define CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_BLOCK_1_WIDTH (1U)
#define CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_BLOCK_1(x) (((uint32_t)(((uint32_t)(x)) << CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_BLOCK_1_SHIFT)) & CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_BLOCK_1_MASK)

#define CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_BLOCK_2_MASK (0x4000U)
#define CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_BLOCK_2_SHIFT (14U)
#define CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_BLOCK_2_WIDTH (1U)
#define CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_BLOCK_2(x) (((uint32_t)(((uint32_t)(x)) << CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_BLOCK_2_SHIFT)) & CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_BLOCK_2_MASK)

#define CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_BLOCK_3_MASK (0x8000U)
#define CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_BLOCK_3_SHIFT (15U)
#define CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_BLOCK_3_WIDTH (1U)
#define CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_BLOCK_3(x) (((uint32_t)(((uint32_t)(x)) << CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_BLOCK_3_SHIFT)) & CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_BLOCK_3_MASK)

#define CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_BLOCK_4_MASK (0x10000U)
#define CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_BLOCK_4_SHIFT (16U)
#define CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_BLOCK_4_WIDTH (1U)
#define CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_BLOCK_4(x) (((uint32_t)(((uint32_t)(x)) << CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_BLOCK_4_SHIFT)) & CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_BLOCK_4_MASK)

#define CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_UTEST_MASK (0x40000U)
#define CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_UTEST_SHIFT (18U)
#define CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_UTEST_WIDTH (1U)
#define CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_UTEST(x) (((uint32_t)(((uint32_t)(x)) << CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_UTEST_SHIFT)) & CONFIGURATION_GPR_CONFIG_PE_LOCK_PE_LOCK_UTEST_MASK)
/*! @} */

/*! @name CONFIG_RAMPR_ALT - Configuration RAM Protected Region Alternate */
/*! @{ */

#define CONFIGURATION_GPR_CONFIG_RAMPR_ALT_INVERT_VALUE_RAMPR_MASK (0xFFFFFFFFU)
#define CONFIGURATION_GPR_CONFIG_RAMPR_ALT_INVERT_VALUE_RAMPR_SHIFT (0U)
#define CONFIGURATION_GPR_CONFIG_RAMPR_ALT_INVERT_VALUE_RAMPR_WIDTH (32U)
#define CONFIGURATION_GPR_CONFIG_RAMPR_ALT_INVERT_VALUE_RAMPR(x) (((uint32_t)(((uint32_t)(x)) << CONFIGURATION_GPR_CONFIG_RAMPR_ALT_INVERT_VALUE_RAMPR_SHIFT)) & CONFIGURATION_GPR_CONFIG_RAMPR_ALT_INVERT_VALUE_RAMPR_MASK)
/*! @} */

/*! @name CONFIG_CFPRL_ALT - Configuration Code Flash Memory Active Block Alternate */
/*! @{ */

#define CONFIGURATION_GPR_CONFIG_CFPRL_ALT_INVERT_VALUE_CFPRAB_MASK (0xFFFFFFFFU)
#define CONFIGURATION_GPR_CONFIG_CFPRL_ALT_INVERT_VALUE_CFPRAB_SHIFT (0U)
#define CONFIGURATION_GPR_CONFIG_CFPRL_ALT_INVERT_VALUE_CFPRAB_WIDTH (32U)
#define CONFIGURATION_GPR_CONFIG_CFPRL_ALT_INVERT_VALUE_CFPRAB(x) (((uint32_t)(((uint32_t)(x)) << CONFIGURATION_GPR_CONFIG_CFPRL_ALT_INVERT_VALUE_CFPRAB_SHIFT)) & CONFIGURATION_GPR_CONFIG_CFPRL_ALT_INVERT_VALUE_CFPRAB_MASK)
/*! @} */

/*! @name CONFIG_CFPRH_ALT - Configuration Code Flash Memory Passive Block Alternate */
/*! @{ */

#define CONFIGURATION_GPR_CONFIG_CFPRH_ALT_INVERT_VALUE_CFPRP_MASK (0xFFFFFFFFU)
#define CONFIGURATION_GPR_CONFIG_CFPRH_ALT_INVERT_VALUE_CFPRP_SHIFT (0U)
#define CONFIGURATION_GPR_CONFIG_CFPRH_ALT_INVERT_VALUE_CFPRP_WIDTH (32U)
#define CONFIGURATION_GPR_CONFIG_CFPRH_ALT_INVERT_VALUE_CFPRP(x) (((uint32_t)(((uint32_t)(x)) << CONFIGURATION_GPR_CONFIG_CFPRH_ALT_INVERT_VALUE_CFPRP_SHIFT)) & CONFIGURATION_GPR_CONFIG_CFPRH_ALT_INVERT_VALUE_CFPRP_MASK)
/*! @} */

/*! @name CONFIG_DFPR_ALT - Configuration Data Flash Memory Protected Region Alternate */
/*! @{ */

#define CONFIGURATION_GPR_CONFIG_DFPR_ALT_INVERT_VALUE_DFPR_MASK (0xFFFFFFFFU)
#define CONFIGURATION_GPR_CONFIG_DFPR_ALT_INVERT_VALUE_DFPR_SHIFT (0U)
#define CONFIGURATION_GPR_CONFIG_DFPR_ALT_INVERT_VALUE_DFPR_WIDTH (32U)
#define CONFIGURATION_GPR_CONFIG_DFPR_ALT_INVERT_VALUE_DFPR(x) (((uint32_t)(((uint32_t)(x)) << CONFIGURATION_GPR_CONFIG_DFPR_ALT_INVERT_VALUE_DFPR_SHIFT)) & CONFIGURATION_GPR_CONFIG_DFPR_ALT_INVERT_VALUE_DFPR_MASK)
/*! @} */

/*! @name CONFIG_REG_GPR - Configuration REG_GPR */
/*! @{ */

#define CONFIGURATION_GPR_CONFIG_REG_GPR_FIRC_DIV_SEL_MASK (0x3U)
#define CONFIGURATION_GPR_CONFIG_REG_GPR_FIRC_DIV_SEL_SHIFT (0U)
#define CONFIGURATION_GPR_CONFIG_REG_GPR_FIRC_DIV_SEL_WIDTH (2U)
#define CONFIGURATION_GPR_CONFIG_REG_GPR_FIRC_DIV_SEL(x) (((uint32_t)(((uint32_t)(x)) << CONFIGURATION_GPR_CONFIG_REG_GPR_FIRC_DIV_SEL_SHIFT)) & CONFIGURATION_GPR_CONFIG_REG_GPR_FIRC_DIV_SEL_MASK)

#define CONFIGURATION_GPR_CONFIG_REG_GPR_APP_CORE_ACC_MASK (0xE0000000U)
#define CONFIGURATION_GPR_CONFIG_REG_GPR_APP_CORE_ACC_SHIFT (29U)
#define CONFIGURATION_GPR_CONFIG_REG_GPR_APP_CORE_ACC_WIDTH (3U)
#define CONFIGURATION_GPR_CONFIG_REG_GPR_APP_CORE_ACC(x) (((uint32_t)(((uint32_t)(x)) << CONFIGURATION_GPR_CONFIG_REG_GPR_APP_CORE_ACC_SHIFT)) & CONFIGURATION_GPR_CONFIG_REG_GPR_APP_CORE_ACC_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group CONFIGURATION_GPR_Register_Masks */

/*!
 * @}
 */ /* end of group CONFIGURATION_GPR_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_CONFIGURATION_GPR_H_) */
