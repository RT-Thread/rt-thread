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
 * @file S32K344_STCU.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_STCU
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
#if !defined(S32K344_STCU_H_)  /* Check if memory map has not been already included */
#define S32K344_STCU_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- STCU Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup STCU_Peripheral_Access_Layer STCU Peripheral Access Layer
 * @{
 */

/** STCU - Size of Registers Arrays */
#define STCU_LB_COUNT                             1u
#define STCU_MB_CTRL_COUNT                        12u

/** STCU - Register Layout Typedef */
typedef struct {
  uint8_t RESERVED_0[4];
  __IO uint32_t RUNSW;                             /**< STCU2 Run Software, offset: 0x4 */
  __O  uint32_t SKC;                               /**< STCU2 SK Code, offset: 0x8 */
  __IO uint32_t CFG;                               /**< STCU2 Configuration, offset: 0xC */
  uint8_t RESERVED_1[4];
  __IO uint32_t WDG;                               /**< STCU2 Watchdog Granularity, offset: 0x14 */
  uint8_t RESERVED_2[12];
  __IO uint32_t ERR_STAT;                          /**< STCU2 Error, offset: 0x24 */
  __IO uint32_t ERR_FM;                            /**< STCU2 Error FM, offset: 0x28 */
  uint8_t RESERVED_3[32];
  __I  uint32_t LBSSW0;                            /**< STCU2 Online LBIST Status, offset: 0x4C */
  uint8_t RESERVED_4[12];
  __I  uint32_t LBESW0;                            /**< STCU2 Online LBIST End Flag, offset: 0x5C */
  uint8_t RESERVED_5[28];
  __IO uint32_t LBUFM0;                            /**< STCU2 Online LBIST Unrecoverable FM, offset: 0x7C */
  uint8_t RESERVED_6[140];
  __I  uint32_t MBSSW0;                            /**< STCU2 Online MBIST Status, offset: 0x10C */
  uint8_t RESERVED_7[60];
  __I  uint32_t MBESW0;                            /**< STCU2 Online MBIST End Flag, offset: 0x14C */
  uint8_t RESERVED_8[60];
  __IO uint32_t MBUFM0;                            /**< STCU2 MBIST Unrecoverable FM, offset: 0x18C */
  uint8_t RESERVED_9[112];
  struct {                                         /* offset: 0x200, array step: 0x30 */
    __IO uint32_t CTRL;                              /**< STCU2 LBIST Control, array offset: 0x200, array step: 0x30 */
    __IO uint32_t PCS;                               /**< STCU2 LBIST PC Stop, array offset: 0x204, array step: 0x30 */
    uint8_t RESERVED_0[24];
    __IO uint32_t MISRELSW;                          /**< STCU2 Online LBIST MISR Expected Low, array offset: 0x220, array step: 0x30 */
    __IO uint32_t MISREHSW;                          /**< STCU2 Online LBIST MISR Expected High, array offset: 0x224, array step: 0x30 */
    __I  uint32_t MISRRLSW;                          /**< STCU2 Online LBIST MISR Read Low, array offset: 0x228, array step: 0x30 */
    __I  uint32_t MISRRHSW;                          /**< STCU2 Online LBIST MISR Read High, array offset: 0x22C, array step: 0x30 */
  } LB[STCU_LB_COUNT];
  uint8_t RESERVED_10[8144];
  __IO uint32_t ALGOSEL;                           /**< STCU2 Algorithm Select, offset: 0x2200 */
  uint8_t RESERVED_11[8];
  __IO uint32_t STGGR;                             /**< STCU2 MBIST Stagger, offset: 0x220C */
  __IO uint32_t BSTART;                            /**< STCU2 BIST Start, offset: 0x2210 */
  __IO uint32_t MB_CTRL[STCU_MB_CTRL_COUNT];       /**< STCU2 MBIST Control, array offset: 0x2214, array step: 0x4 */
} STCU_Type, *STCU_MemMapPtr;

/** Number of instances of the STCU module. */
#define STCU_INSTANCE_COUNT                      (1u)

/* STCU - Peripheral instance base addresses */
/** Peripheral STCU base address */
#define IP_STCU_BASE                             (0x403A0000u)
/** Peripheral STCU base pointer */
#define IP_STCU                                  ((STCU_Type *)IP_STCU_BASE)
/** Array initializer of STCU peripheral base addresses */
#define IP_STCU_BASE_ADDRS                       { IP_STCU_BASE }
/** Array initializer of STCU peripheral base pointers */
#define IP_STCU_BASE_PTRS                        { IP_STCU }

/* ----------------------------------------------------------------------------
   -- STCU Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup STCU_Register_Masks STCU Register Masks
 * @{
 */

/*! @name RUNSW - STCU2 Run Software */
/*! @{ */

#define STCU_RUNSW_RUNSW_MASK                    (0x1U)
#define STCU_RUNSW_RUNSW_SHIFT                   (0U)
#define STCU_RUNSW_RUNSW_WIDTH                   (1U)
#define STCU_RUNSW_RUNSW(x)                      (((uint32_t)(((uint32_t)(x)) << STCU_RUNSW_RUNSW_SHIFT)) & STCU_RUNSW_RUNSW_MASK)

#define STCU_RUNSW_LBSWPLLEN_MASK                (0x100U)
#define STCU_RUNSW_LBSWPLLEN_SHIFT               (8U)
#define STCU_RUNSW_LBSWPLLEN_WIDTH               (1U)
#define STCU_RUNSW_LBSWPLLEN(x)                  (((uint32_t)(((uint32_t)(x)) << STCU_RUNSW_LBSWPLLEN_SHIFT)) & STCU_RUNSW_LBSWPLLEN_MASK)

#define STCU_RUNSW_MBSWPLLEN_MASK                (0x200U)
#define STCU_RUNSW_MBSWPLLEN_SHIFT               (9U)
#define STCU_RUNSW_MBSWPLLEN_WIDTH               (1U)
#define STCU_RUNSW_MBSWPLLEN(x)                  (((uint32_t)(((uint32_t)(x)) << STCU_RUNSW_MBSWPLLEN_SHIFT)) & STCU_RUNSW_MBSWPLLEN_MASK)
/*! @} */

/*! @name SKC - STCU2 SK Code */
/*! @{ */

#define STCU_SKC_SKC_MASK                        (0xFFFFFFFFU)
#define STCU_SKC_SKC_SHIFT                       (0U)
#define STCU_SKC_SKC_WIDTH                       (32U)
#define STCU_SKC_SKC(x)                          (((uint32_t)(((uint32_t)(x)) << STCU_SKC_SKC_SHIFT)) & STCU_SKC_SKC_MASK)
/*! @} */

/*! @name CFG - STCU2 Configuration */
/*! @{ */

#define STCU_CFG_CLK_CFG_MASK                    (0x7U)
#define STCU_CFG_CLK_CFG_SHIFT                   (0U)
#define STCU_CFG_CLK_CFG_WIDTH                   (3U)
#define STCU_CFG_CLK_CFG(x)                      (((uint32_t)(((uint32_t)(x)) << STCU_CFG_CLK_CFG_SHIFT)) & STCU_CFG_CLK_CFG_MASK)

#define STCU_CFG_WRP_MASK                        (0x100U)
#define STCU_CFG_WRP_SHIFT                       (8U)
#define STCU_CFG_WRP_WIDTH                       (1U)
#define STCU_CFG_WRP(x)                          (((uint32_t)(((uint32_t)(x)) << STCU_CFG_WRP_SHIFT)) & STCU_CFG_WRP_MASK)

#define STCU_CFG_LB_DELAY_MASK                   (0x1FE000U)
#define STCU_CFG_LB_DELAY_SHIFT                  (13U)
#define STCU_CFG_LB_DELAY_WIDTH                  (8U)
#define STCU_CFG_LB_DELAY(x)                     (((uint32_t)(((uint32_t)(x)) << STCU_CFG_LB_DELAY_SHIFT)) & STCU_CFG_LB_DELAY_MASK)

#define STCU_CFG_PTR_MASK                        (0x7FE00000U)
#define STCU_CFG_PTR_SHIFT                       (21U)
#define STCU_CFG_PTR_WIDTH                       (10U)
#define STCU_CFG_PTR(x)                          (((uint32_t)(((uint32_t)(x)) << STCU_CFG_PTR_SHIFT)) & STCU_CFG_PTR_MASK)
/*! @} */

/*! @name WDG - STCU2 Watchdog Granularity */
/*! @{ */

#define STCU_WDG_WDGEOC_MASK                     (0xFFFFFFFFU)
#define STCU_WDG_WDGEOC_SHIFT                    (0U)
#define STCU_WDG_WDGEOC_WIDTH                    (32U)
#define STCU_WDG_WDGEOC(x)                       (((uint32_t)(((uint32_t)(x)) << STCU_WDG_WDGEOC_SHIFT)) & STCU_WDG_WDGEOC_MASK)
/*! @} */

/*! @name ERR_STAT - STCU2 Error */
/*! @{ */

#define STCU_ERR_STAT_RFSF_MASK                  (0x100U)
#define STCU_ERR_STAT_RFSF_SHIFT                 (8U)
#define STCU_ERR_STAT_RFSF_WIDTH                 (1U)
#define STCU_ERR_STAT_RFSF(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_ERR_STAT_RFSF_SHIFT)) & STCU_ERR_STAT_RFSF_MASK)

#define STCU_ERR_STAT_UFSF_MASK                  (0x200U)
#define STCU_ERR_STAT_UFSF_SHIFT                 (9U)
#define STCU_ERR_STAT_UFSF_WIDTH                 (1U)
#define STCU_ERR_STAT_UFSF(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_ERR_STAT_UFSF_SHIFT)) & STCU_ERR_STAT_UFSF_MASK)

#define STCU_ERR_STAT_INVPSW_MASK                (0x10000U)
#define STCU_ERR_STAT_INVPSW_SHIFT               (16U)
#define STCU_ERR_STAT_INVPSW_WIDTH               (1U)
#define STCU_ERR_STAT_INVPSW(x)                  (((uint32_t)(((uint32_t)(x)) << STCU_ERR_STAT_INVPSW_SHIFT)) & STCU_ERR_STAT_INVPSW_MASK)

#define STCU_ERR_STAT_ENGESW_MASK                (0x20000U)
#define STCU_ERR_STAT_ENGESW_SHIFT               (17U)
#define STCU_ERR_STAT_ENGESW_WIDTH               (1U)
#define STCU_ERR_STAT_ENGESW(x)                  (((uint32_t)(((uint32_t)(x)) << STCU_ERR_STAT_ENGESW_SHIFT)) & STCU_ERR_STAT_ENGESW_MASK)

#define STCU_ERR_STAT_WDTOSW_MASK                (0x80000U)
#define STCU_ERR_STAT_WDTOSW_SHIFT               (19U)
#define STCU_ERR_STAT_WDTOSW_WIDTH               (1U)
#define STCU_ERR_STAT_WDTOSW(x)                  (((uint32_t)(((uint32_t)(x)) << STCU_ERR_STAT_WDTOSW_SHIFT)) & STCU_ERR_STAT_WDTOSW_MASK)

#define STCU_ERR_STAT_LOCKESW_MASK               (0x100000U)
#define STCU_ERR_STAT_LOCKESW_SHIFT              (20U)
#define STCU_ERR_STAT_LOCKESW_WIDTH              (1U)
#define STCU_ERR_STAT_LOCKESW(x)                 (((uint32_t)(((uint32_t)(x)) << STCU_ERR_STAT_LOCKESW_SHIFT)) & STCU_ERR_STAT_LOCKESW_MASK)
/*! @} */

/*! @name ERR_FM - STCU2 Error FM */
/*! @{ */

#define STCU_ERR_FM_INVPUFM_MASK                 (0x1U)
#define STCU_ERR_FM_INVPUFM_SHIFT                (0U)
#define STCU_ERR_FM_INVPUFM_WIDTH                (1U)
#define STCU_ERR_FM_INVPUFM(x)                   (((uint32_t)(((uint32_t)(x)) << STCU_ERR_FM_INVPUFM_SHIFT)) & STCU_ERR_FM_INVPUFM_MASK)

#define STCU_ERR_FM_ENGEUFM_MASK                 (0x2U)
#define STCU_ERR_FM_ENGEUFM_SHIFT                (1U)
#define STCU_ERR_FM_ENGEUFM_WIDTH                (1U)
#define STCU_ERR_FM_ENGEUFM(x)                   (((uint32_t)(((uint32_t)(x)) << STCU_ERR_FM_ENGEUFM_SHIFT)) & STCU_ERR_FM_ENGEUFM_MASK)

#define STCU_ERR_FM_WDTOUFM_MASK                 (0x8U)
#define STCU_ERR_FM_WDTOUFM_SHIFT                (3U)
#define STCU_ERR_FM_WDTOUFM_WIDTH                (1U)
#define STCU_ERR_FM_WDTOUFM(x)                   (((uint32_t)(((uint32_t)(x)) << STCU_ERR_FM_WDTOUFM_SHIFT)) & STCU_ERR_FM_WDTOUFM_MASK)

#define STCU_ERR_FM_LOCKEUFM_MASK                (0x10U)
#define STCU_ERR_FM_LOCKEUFM_SHIFT               (4U)
#define STCU_ERR_FM_LOCKEUFM_WIDTH               (1U)
#define STCU_ERR_FM_LOCKEUFM(x)                  (((uint32_t)(((uint32_t)(x)) << STCU_ERR_FM_LOCKEUFM_SHIFT)) & STCU_ERR_FM_LOCKEUFM_MASK)
/*! @} */

/*! @name LBSSW0 - STCU2 Online LBIST Status */
/*! @{ */

#define STCU_LBSSW0_LBSSW0_MASK                  (0x1U)
#define STCU_LBSSW0_LBSSW0_SHIFT                 (0U)
#define STCU_LBSSW0_LBSSW0_WIDTH                 (1U)
#define STCU_LBSSW0_LBSSW0(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_LBSSW0_LBSSW0_SHIFT)) & STCU_LBSSW0_LBSSW0_MASK)
/*! @} */

/*! @name LBESW0 - STCU2 Online LBIST End Flag */
/*! @{ */

#define STCU_LBESW0_LBESW0_MASK                  (0x1U)
#define STCU_LBESW0_LBESW0_SHIFT                 (0U)
#define STCU_LBESW0_LBESW0_WIDTH                 (1U)
#define STCU_LBESW0_LBESW0(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_LBESW0_LBESW0_SHIFT)) & STCU_LBESW0_LBESW0_MASK)
/*! @} */

/*! @name LBUFM0 - STCU2 Online LBIST Unrecoverable FM */
/*! @{ */

#define STCU_LBUFM0_LBUFM0_MASK                  (0x1U)
#define STCU_LBUFM0_LBUFM0_SHIFT                 (0U)
#define STCU_LBUFM0_LBUFM0_WIDTH                 (1U)
#define STCU_LBUFM0_LBUFM0(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_LBUFM0_LBUFM0_SHIFT)) & STCU_LBUFM0_LBUFM0_MASK)
/*! @} */

/*! @name MBSSW0 - STCU2 Online MBIST Status */
/*! @{ */

#define STCU_MBSSW0_MBSSW0_MASK                  (0x1U)
#define STCU_MBSSW0_MBSSW0_SHIFT                 (0U)
#define STCU_MBSSW0_MBSSW0_WIDTH                 (1U)
#define STCU_MBSSW0_MBSSW0(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_MBSSW0_MBSSW0_SHIFT)) & STCU_MBSSW0_MBSSW0_MASK)

#define STCU_MBSSW0_MBSSW1_MASK                  (0x2U)
#define STCU_MBSSW0_MBSSW1_SHIFT                 (1U)
#define STCU_MBSSW0_MBSSW1_WIDTH                 (1U)
#define STCU_MBSSW0_MBSSW1(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_MBSSW0_MBSSW1_SHIFT)) & STCU_MBSSW0_MBSSW1_MASK)

#define STCU_MBSSW0_MBSSW2_MASK                  (0x4U)
#define STCU_MBSSW0_MBSSW2_SHIFT                 (2U)
#define STCU_MBSSW0_MBSSW2_WIDTH                 (1U)
#define STCU_MBSSW0_MBSSW2(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_MBSSW0_MBSSW2_SHIFT)) & STCU_MBSSW0_MBSSW2_MASK)

#define STCU_MBSSW0_MBSSW3_MASK                  (0x8U)
#define STCU_MBSSW0_MBSSW3_SHIFT                 (3U)
#define STCU_MBSSW0_MBSSW3_WIDTH                 (1U)
#define STCU_MBSSW0_MBSSW3(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_MBSSW0_MBSSW3_SHIFT)) & STCU_MBSSW0_MBSSW3_MASK)

#define STCU_MBSSW0_MBSSW4_MASK                  (0x10U)
#define STCU_MBSSW0_MBSSW4_SHIFT                 (4U)
#define STCU_MBSSW0_MBSSW4_WIDTH                 (1U)
#define STCU_MBSSW0_MBSSW4(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_MBSSW0_MBSSW4_SHIFT)) & STCU_MBSSW0_MBSSW4_MASK)

#define STCU_MBSSW0_MBSSW5_MASK                  (0x20U)
#define STCU_MBSSW0_MBSSW5_SHIFT                 (5U)
#define STCU_MBSSW0_MBSSW5_WIDTH                 (1U)
#define STCU_MBSSW0_MBSSW5(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_MBSSW0_MBSSW5_SHIFT)) & STCU_MBSSW0_MBSSW5_MASK)

#define STCU_MBSSW0_MBSSW6_MASK                  (0x40U)
#define STCU_MBSSW0_MBSSW6_SHIFT                 (6U)
#define STCU_MBSSW0_MBSSW6_WIDTH                 (1U)
#define STCU_MBSSW0_MBSSW6(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_MBSSW0_MBSSW6_SHIFT)) & STCU_MBSSW0_MBSSW6_MASK)

#define STCU_MBSSW0_MBSSW7_MASK                  (0x80U)
#define STCU_MBSSW0_MBSSW7_SHIFT                 (7U)
#define STCU_MBSSW0_MBSSW7_WIDTH                 (1U)
#define STCU_MBSSW0_MBSSW7(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_MBSSW0_MBSSW7_SHIFT)) & STCU_MBSSW0_MBSSW7_MASK)

#define STCU_MBSSW0_MBSSW8_MASK                  (0x100U)
#define STCU_MBSSW0_MBSSW8_SHIFT                 (8U)
#define STCU_MBSSW0_MBSSW8_WIDTH                 (1U)
#define STCU_MBSSW0_MBSSW8(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_MBSSW0_MBSSW8_SHIFT)) & STCU_MBSSW0_MBSSW8_MASK)

#define STCU_MBSSW0_MBSSW9_MASK                  (0x200U)
#define STCU_MBSSW0_MBSSW9_SHIFT                 (9U)
#define STCU_MBSSW0_MBSSW9_WIDTH                 (1U)
#define STCU_MBSSW0_MBSSW9(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_MBSSW0_MBSSW9_SHIFT)) & STCU_MBSSW0_MBSSW9_MASK)

#define STCU_MBSSW0_MBSSW10_MASK                 (0x400U)
#define STCU_MBSSW0_MBSSW10_SHIFT                (10U)
#define STCU_MBSSW0_MBSSW10_WIDTH                (1U)
#define STCU_MBSSW0_MBSSW10(x)                   (((uint32_t)(((uint32_t)(x)) << STCU_MBSSW0_MBSSW10_SHIFT)) & STCU_MBSSW0_MBSSW10_MASK)

#define STCU_MBSSW0_MBSSW11_MASK                 (0x800U)
#define STCU_MBSSW0_MBSSW11_SHIFT                (11U)
#define STCU_MBSSW0_MBSSW11_WIDTH                (1U)
#define STCU_MBSSW0_MBSSW11(x)                   (((uint32_t)(((uint32_t)(x)) << STCU_MBSSW0_MBSSW11_SHIFT)) & STCU_MBSSW0_MBSSW11_MASK)
/*! @} */

/*! @name MBESW0 - STCU2 Online MBIST End Flag */
/*! @{ */

#define STCU_MBESW0_MBESW0_MASK                  (0x1U)
#define STCU_MBESW0_MBESW0_SHIFT                 (0U)
#define STCU_MBESW0_MBESW0_WIDTH                 (1U)
#define STCU_MBESW0_MBESW0(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_MBESW0_MBESW0_SHIFT)) & STCU_MBESW0_MBESW0_MASK)

#define STCU_MBESW0_MBESW1_MASK                  (0x2U)
#define STCU_MBESW0_MBESW1_SHIFT                 (1U)
#define STCU_MBESW0_MBESW1_WIDTH                 (1U)
#define STCU_MBESW0_MBESW1(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_MBESW0_MBESW1_SHIFT)) & STCU_MBESW0_MBESW1_MASK)

#define STCU_MBESW0_MBESW2_MASK                  (0x4U)
#define STCU_MBESW0_MBESW2_SHIFT                 (2U)
#define STCU_MBESW0_MBESW2_WIDTH                 (1U)
#define STCU_MBESW0_MBESW2(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_MBESW0_MBESW2_SHIFT)) & STCU_MBESW0_MBESW2_MASK)

#define STCU_MBESW0_MBESW3_MASK                  (0x8U)
#define STCU_MBESW0_MBESW3_SHIFT                 (3U)
#define STCU_MBESW0_MBESW3_WIDTH                 (1U)
#define STCU_MBESW0_MBESW3(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_MBESW0_MBESW3_SHIFT)) & STCU_MBESW0_MBESW3_MASK)

#define STCU_MBESW0_MBESW4_MASK                  (0x10U)
#define STCU_MBESW0_MBESW4_SHIFT                 (4U)
#define STCU_MBESW0_MBESW4_WIDTH                 (1U)
#define STCU_MBESW0_MBESW4(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_MBESW0_MBESW4_SHIFT)) & STCU_MBESW0_MBESW4_MASK)

#define STCU_MBESW0_MBESW5_MASK                  (0x20U)
#define STCU_MBESW0_MBESW5_SHIFT                 (5U)
#define STCU_MBESW0_MBESW5_WIDTH                 (1U)
#define STCU_MBESW0_MBESW5(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_MBESW0_MBESW5_SHIFT)) & STCU_MBESW0_MBESW5_MASK)

#define STCU_MBESW0_MBESW6_MASK                  (0x40U)
#define STCU_MBESW0_MBESW6_SHIFT                 (6U)
#define STCU_MBESW0_MBESW6_WIDTH                 (1U)
#define STCU_MBESW0_MBESW6(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_MBESW0_MBESW6_SHIFT)) & STCU_MBESW0_MBESW6_MASK)

#define STCU_MBESW0_MBESW7_MASK                  (0x80U)
#define STCU_MBESW0_MBESW7_SHIFT                 (7U)
#define STCU_MBESW0_MBESW7_WIDTH                 (1U)
#define STCU_MBESW0_MBESW7(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_MBESW0_MBESW7_SHIFT)) & STCU_MBESW0_MBESW7_MASK)

#define STCU_MBESW0_MBESW8_MASK                  (0x100U)
#define STCU_MBESW0_MBESW8_SHIFT                 (8U)
#define STCU_MBESW0_MBESW8_WIDTH                 (1U)
#define STCU_MBESW0_MBESW8(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_MBESW0_MBESW8_SHIFT)) & STCU_MBESW0_MBESW8_MASK)

#define STCU_MBESW0_MBESW9_MASK                  (0x200U)
#define STCU_MBESW0_MBESW9_SHIFT                 (9U)
#define STCU_MBESW0_MBESW9_WIDTH                 (1U)
#define STCU_MBESW0_MBESW9(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_MBESW0_MBESW9_SHIFT)) & STCU_MBESW0_MBESW9_MASK)

#define STCU_MBESW0_MBESW10_MASK                 (0x400U)
#define STCU_MBESW0_MBESW10_SHIFT                (10U)
#define STCU_MBESW0_MBESW10_WIDTH                (1U)
#define STCU_MBESW0_MBESW10(x)                   (((uint32_t)(((uint32_t)(x)) << STCU_MBESW0_MBESW10_SHIFT)) & STCU_MBESW0_MBESW10_MASK)

#define STCU_MBESW0_MBESW11_MASK                 (0x800U)
#define STCU_MBESW0_MBESW11_SHIFT                (11U)
#define STCU_MBESW0_MBESW11_WIDTH                (1U)
#define STCU_MBESW0_MBESW11(x)                   (((uint32_t)(((uint32_t)(x)) << STCU_MBESW0_MBESW11_SHIFT)) & STCU_MBESW0_MBESW11_MASK)
/*! @} */

/*! @name MBUFM0 - STCU2 MBIST Unrecoverable FM */
/*! @{ */

#define STCU_MBUFM0_MBUFM0_MASK                  (0x1U)
#define STCU_MBUFM0_MBUFM0_SHIFT                 (0U)
#define STCU_MBUFM0_MBUFM0_WIDTH                 (1U)
#define STCU_MBUFM0_MBUFM0(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_MBUFM0_MBUFM0_SHIFT)) & STCU_MBUFM0_MBUFM0_MASK)

#define STCU_MBUFM0_MBUFM1_MASK                  (0x2U)
#define STCU_MBUFM0_MBUFM1_SHIFT                 (1U)
#define STCU_MBUFM0_MBUFM1_WIDTH                 (1U)
#define STCU_MBUFM0_MBUFM1(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_MBUFM0_MBUFM1_SHIFT)) & STCU_MBUFM0_MBUFM1_MASK)

#define STCU_MBUFM0_MBUFM2_MASK                  (0x4U)
#define STCU_MBUFM0_MBUFM2_SHIFT                 (2U)
#define STCU_MBUFM0_MBUFM2_WIDTH                 (1U)
#define STCU_MBUFM0_MBUFM2(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_MBUFM0_MBUFM2_SHIFT)) & STCU_MBUFM0_MBUFM2_MASK)

#define STCU_MBUFM0_MBUFM3_MASK                  (0x8U)
#define STCU_MBUFM0_MBUFM3_SHIFT                 (3U)
#define STCU_MBUFM0_MBUFM3_WIDTH                 (1U)
#define STCU_MBUFM0_MBUFM3(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_MBUFM0_MBUFM3_SHIFT)) & STCU_MBUFM0_MBUFM3_MASK)

#define STCU_MBUFM0_MBUFM4_MASK                  (0x10U)
#define STCU_MBUFM0_MBUFM4_SHIFT                 (4U)
#define STCU_MBUFM0_MBUFM4_WIDTH                 (1U)
#define STCU_MBUFM0_MBUFM4(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_MBUFM0_MBUFM4_SHIFT)) & STCU_MBUFM0_MBUFM4_MASK)

#define STCU_MBUFM0_MBUFM5_MASK                  (0x20U)
#define STCU_MBUFM0_MBUFM5_SHIFT                 (5U)
#define STCU_MBUFM0_MBUFM5_WIDTH                 (1U)
#define STCU_MBUFM0_MBUFM5(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_MBUFM0_MBUFM5_SHIFT)) & STCU_MBUFM0_MBUFM5_MASK)

#define STCU_MBUFM0_MBUFM6_MASK                  (0x40U)
#define STCU_MBUFM0_MBUFM6_SHIFT                 (6U)
#define STCU_MBUFM0_MBUFM6_WIDTH                 (1U)
#define STCU_MBUFM0_MBUFM6(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_MBUFM0_MBUFM6_SHIFT)) & STCU_MBUFM0_MBUFM6_MASK)

#define STCU_MBUFM0_MBUFM7_MASK                  (0x80U)
#define STCU_MBUFM0_MBUFM7_SHIFT                 (7U)
#define STCU_MBUFM0_MBUFM7_WIDTH                 (1U)
#define STCU_MBUFM0_MBUFM7(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_MBUFM0_MBUFM7_SHIFT)) & STCU_MBUFM0_MBUFM7_MASK)

#define STCU_MBUFM0_MBUFM8_MASK                  (0x100U)
#define STCU_MBUFM0_MBUFM8_SHIFT                 (8U)
#define STCU_MBUFM0_MBUFM8_WIDTH                 (1U)
#define STCU_MBUFM0_MBUFM8(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_MBUFM0_MBUFM8_SHIFT)) & STCU_MBUFM0_MBUFM8_MASK)

#define STCU_MBUFM0_MBUFM9_MASK                  (0x200U)
#define STCU_MBUFM0_MBUFM9_SHIFT                 (9U)
#define STCU_MBUFM0_MBUFM9_WIDTH                 (1U)
#define STCU_MBUFM0_MBUFM9(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_MBUFM0_MBUFM9_SHIFT)) & STCU_MBUFM0_MBUFM9_MASK)

#define STCU_MBUFM0_MBUFM10_MASK                 (0x400U)
#define STCU_MBUFM0_MBUFM10_SHIFT                (10U)
#define STCU_MBUFM0_MBUFM10_WIDTH                (1U)
#define STCU_MBUFM0_MBUFM10(x)                   (((uint32_t)(((uint32_t)(x)) << STCU_MBUFM0_MBUFM10_SHIFT)) & STCU_MBUFM0_MBUFM10_MASK)

#define STCU_MBUFM0_MBUFM11_MASK                 (0x800U)
#define STCU_MBUFM0_MBUFM11_SHIFT                (11U)
#define STCU_MBUFM0_MBUFM11_WIDTH                (1U)
#define STCU_MBUFM0_MBUFM11(x)                   (((uint32_t)(((uint32_t)(x)) << STCU_MBUFM0_MBUFM11_SHIFT)) & STCU_MBUFM0_MBUFM11_MASK)
/*! @} */

/*! @name CTRL - STCU2 LBIST Control */
/*! @{ */

#define STCU_CTRL_CWS_MASK                       (0x3FU)
#define STCU_CTRL_CWS_SHIFT                      (0U)
#define STCU_CTRL_CWS_WIDTH                      (6U)
#define STCU_CTRL_CWS(x)                         (((uint32_t)(((uint32_t)(x)) << STCU_CTRL_CWS_SHIFT)) & STCU_CTRL_CWS_MASK)

#define STCU_CTRL_SCEN_ON_MASK                   (0xF00U)
#define STCU_CTRL_SCEN_ON_SHIFT                  (8U)
#define STCU_CTRL_SCEN_ON_WIDTH                  (4U)
#define STCU_CTRL_SCEN_ON(x)                     (((uint32_t)(((uint32_t)(x)) << STCU_CTRL_SCEN_ON_SHIFT)) & STCU_CTRL_SCEN_ON_MASK)

#define STCU_CTRL_SCEN_OFF_MASK                  (0xF000U)
#define STCU_CTRL_SCEN_OFF_SHIFT                 (12U)
#define STCU_CTRL_SCEN_OFF_WIDTH                 (4U)
#define STCU_CTRL_SCEN_OFF(x)                    (((uint32_t)(((uint32_t)(x)) << STCU_CTRL_SCEN_OFF_SHIFT)) & STCU_CTRL_SCEN_OFF_MASK)

#define STCU_CTRL_SHS_MASK                       (0x70000U)
#define STCU_CTRL_SHS_SHIFT                      (16U)
#define STCU_CTRL_SHS_WIDTH                      (3U)
#define STCU_CTRL_SHS(x)                         (((uint32_t)(((uint32_t)(x)) << STCU_CTRL_SHS_SHIFT)) & STCU_CTRL_SHS_MASK)

#define STCU_CTRL_PTR_MASK                       (0x7FE00000U)
#define STCU_CTRL_PTR_SHIFT                      (21U)
#define STCU_CTRL_PTR_WIDTH                      (10U)
#define STCU_CTRL_PTR(x)                         (((uint32_t)(((uint32_t)(x)) << STCU_CTRL_PTR_SHIFT)) & STCU_CTRL_PTR_MASK)

#define STCU_CTRL_CSM_MASK                       (0x80000000U)
#define STCU_CTRL_CSM_SHIFT                      (31U)
#define STCU_CTRL_CSM_WIDTH                      (1U)
#define STCU_CTRL_CSM(x)                         (((uint32_t)(((uint32_t)(x)) << STCU_CTRL_CSM_SHIFT)) & STCU_CTRL_CSM_MASK)
/*! @} */

/*! @name PCS - STCU2 LBIST PC Stop */
/*! @{ */

#define STCU_PCS_PCS_MASK                        (0x3FFFFFFU)
#define STCU_PCS_PCS_SHIFT                       (0U)
#define STCU_PCS_PCS_WIDTH                       (26U)
#define STCU_PCS_PCS(x)                          (((uint32_t)(((uint32_t)(x)) << STCU_PCS_PCS_SHIFT)) & STCU_PCS_PCS_MASK)
/*! @} */

/*! @name MISRELSW - STCU2 Online LBIST MISR Expected Low */
/*! @{ */

#define STCU_MISRELSW_MISRESWx_MASK              (0xFFFFFFFFU)
#define STCU_MISRELSW_MISRESWx_SHIFT             (0U)
#define STCU_MISRELSW_MISRESWx_WIDTH             (32U)
#define STCU_MISRELSW_MISRESWx(x)                (((uint32_t)(((uint32_t)(x)) << STCU_MISRELSW_MISRESWx_SHIFT)) & STCU_MISRELSW_MISRESWx_MASK)
/*! @} */

/*! @name MISREHSW - STCU2 Online LBIST MISR Expected High */
/*! @{ */

#define STCU_MISREHSW_MISRESWx_MASK              (0xFFFFFFFFU)
#define STCU_MISREHSW_MISRESWx_SHIFT             (0U)
#define STCU_MISREHSW_MISRESWx_WIDTH             (32U)
#define STCU_MISREHSW_MISRESWx(x)                (((uint32_t)(((uint32_t)(x)) << STCU_MISREHSW_MISRESWx_SHIFT)) & STCU_MISREHSW_MISRESWx_MASK)
/*! @} */

/*! @name MISRRLSW - STCU2 Online LBIST MISR Read Low */
/*! @{ */

#define STCU_MISRRLSW_MISRRSWx_MASK              (0xFFFFFFFFU)
#define STCU_MISRRLSW_MISRRSWx_SHIFT             (0U)
#define STCU_MISRRLSW_MISRRSWx_WIDTH             (32U)
#define STCU_MISRRLSW_MISRRSWx(x)                (((uint32_t)(((uint32_t)(x)) << STCU_MISRRLSW_MISRRSWx_SHIFT)) & STCU_MISRRLSW_MISRRSWx_MASK)
/*! @} */

/*! @name MISRRHSW - STCU2 Online LBIST MISR Read High */
/*! @{ */

#define STCU_MISRRHSW_MISRRSWx_MASK              (0xFFFFFFFFU)
#define STCU_MISRRHSW_MISRRSWx_SHIFT             (0U)
#define STCU_MISRRHSW_MISRRSWx_WIDTH             (32U)
#define STCU_MISRRHSW_MISRRSWx(x)                (((uint32_t)(((uint32_t)(x)) << STCU_MISRRHSW_MISRRSWx_SHIFT)) & STCU_MISRRHSW_MISRRSWx_MASK)
/*! @} */

/*! @name ALGOSEL - STCU2 Algorithm Select */
/*! @{ */

#define STCU_ALGOSEL_ALGOSEL0_MASK               (0x1U)
#define STCU_ALGOSEL_ALGOSEL0_SHIFT              (0U)
#define STCU_ALGOSEL_ALGOSEL0_WIDTH              (1U)
#define STCU_ALGOSEL_ALGOSEL0(x)                 (((uint32_t)(((uint32_t)(x)) << STCU_ALGOSEL_ALGOSEL0_SHIFT)) & STCU_ALGOSEL_ALGOSEL0_MASK)

#define STCU_ALGOSEL_ALGOSEL1_MASK               (0x2U)
#define STCU_ALGOSEL_ALGOSEL1_SHIFT              (1U)
#define STCU_ALGOSEL_ALGOSEL1_WIDTH              (1U)
#define STCU_ALGOSEL_ALGOSEL1(x)                 (((uint32_t)(((uint32_t)(x)) << STCU_ALGOSEL_ALGOSEL1_SHIFT)) & STCU_ALGOSEL_ALGOSEL1_MASK)

#define STCU_ALGOSEL_ALGOSEL2_MASK               (0x4U)
#define STCU_ALGOSEL_ALGOSEL2_SHIFT              (2U)
#define STCU_ALGOSEL_ALGOSEL2_WIDTH              (1U)
#define STCU_ALGOSEL_ALGOSEL2(x)                 (((uint32_t)(((uint32_t)(x)) << STCU_ALGOSEL_ALGOSEL2_SHIFT)) & STCU_ALGOSEL_ALGOSEL2_MASK)

#define STCU_ALGOSEL_ALGOSEL3_MASK               (0x8U)
#define STCU_ALGOSEL_ALGOSEL3_SHIFT              (3U)
#define STCU_ALGOSEL_ALGOSEL3_WIDTH              (1U)
#define STCU_ALGOSEL_ALGOSEL3(x)                 (((uint32_t)(((uint32_t)(x)) << STCU_ALGOSEL_ALGOSEL3_SHIFT)) & STCU_ALGOSEL_ALGOSEL3_MASK)

#define STCU_ALGOSEL_ALGOSEL4_MASK               (0x10U)
#define STCU_ALGOSEL_ALGOSEL4_SHIFT              (4U)
#define STCU_ALGOSEL_ALGOSEL4_WIDTH              (1U)
#define STCU_ALGOSEL_ALGOSEL4(x)                 (((uint32_t)(((uint32_t)(x)) << STCU_ALGOSEL_ALGOSEL4_SHIFT)) & STCU_ALGOSEL_ALGOSEL4_MASK)

#define STCU_ALGOSEL_ALGOSEL5_MASK               (0x20U)
#define STCU_ALGOSEL_ALGOSEL5_SHIFT              (5U)
#define STCU_ALGOSEL_ALGOSEL5_WIDTH              (1U)
#define STCU_ALGOSEL_ALGOSEL5(x)                 (((uint32_t)(((uint32_t)(x)) << STCU_ALGOSEL_ALGOSEL5_SHIFT)) & STCU_ALGOSEL_ALGOSEL5_MASK)

#define STCU_ALGOSEL_ALGOSEL6_MASK               (0x40U)
#define STCU_ALGOSEL_ALGOSEL6_SHIFT              (6U)
#define STCU_ALGOSEL_ALGOSEL6_WIDTH              (1U)
#define STCU_ALGOSEL_ALGOSEL6(x)                 (((uint32_t)(((uint32_t)(x)) << STCU_ALGOSEL_ALGOSEL6_SHIFT)) & STCU_ALGOSEL_ALGOSEL6_MASK)

#define STCU_ALGOSEL_ALGOSEL7_MASK               (0x80U)
#define STCU_ALGOSEL_ALGOSEL7_SHIFT              (7U)
#define STCU_ALGOSEL_ALGOSEL7_WIDTH              (1U)
#define STCU_ALGOSEL_ALGOSEL7(x)                 (((uint32_t)(((uint32_t)(x)) << STCU_ALGOSEL_ALGOSEL7_SHIFT)) & STCU_ALGOSEL_ALGOSEL7_MASK)

#define STCU_ALGOSEL_ALGOSEL8_MASK               (0x100U)
#define STCU_ALGOSEL_ALGOSEL8_SHIFT              (8U)
#define STCU_ALGOSEL_ALGOSEL8_WIDTH              (1U)
#define STCU_ALGOSEL_ALGOSEL8(x)                 (((uint32_t)(((uint32_t)(x)) << STCU_ALGOSEL_ALGOSEL8_SHIFT)) & STCU_ALGOSEL_ALGOSEL8_MASK)

#define STCU_ALGOSEL_ALGOSEL9_MASK               (0x200U)
#define STCU_ALGOSEL_ALGOSEL9_SHIFT              (9U)
#define STCU_ALGOSEL_ALGOSEL9_WIDTH              (1U)
#define STCU_ALGOSEL_ALGOSEL9(x)                 (((uint32_t)(((uint32_t)(x)) << STCU_ALGOSEL_ALGOSEL9_SHIFT)) & STCU_ALGOSEL_ALGOSEL9_MASK)

#define STCU_ALGOSEL_ALGOSEL10_MASK              (0x400U)
#define STCU_ALGOSEL_ALGOSEL10_SHIFT             (10U)
#define STCU_ALGOSEL_ALGOSEL10_WIDTH             (1U)
#define STCU_ALGOSEL_ALGOSEL10(x)                (((uint32_t)(((uint32_t)(x)) << STCU_ALGOSEL_ALGOSEL10_SHIFT)) & STCU_ALGOSEL_ALGOSEL10_MASK)

#define STCU_ALGOSEL_ALGOSEL11_MASK              (0x800U)
#define STCU_ALGOSEL_ALGOSEL11_SHIFT             (11U)
#define STCU_ALGOSEL_ALGOSEL11_WIDTH             (1U)
#define STCU_ALGOSEL_ALGOSEL11(x)                (((uint32_t)(((uint32_t)(x)) << STCU_ALGOSEL_ALGOSEL11_SHIFT)) & STCU_ALGOSEL_ALGOSEL11_MASK)

#define STCU_ALGOSEL_ALGOSEL12_MASK              (0x1000U)
#define STCU_ALGOSEL_ALGOSEL12_SHIFT             (12U)
#define STCU_ALGOSEL_ALGOSEL12_WIDTH             (1U)
#define STCU_ALGOSEL_ALGOSEL12(x)                (((uint32_t)(((uint32_t)(x)) << STCU_ALGOSEL_ALGOSEL12_SHIFT)) & STCU_ALGOSEL_ALGOSEL12_MASK)

#define STCU_ALGOSEL_ALGOSEL13_MASK              (0x2000U)
#define STCU_ALGOSEL_ALGOSEL13_SHIFT             (13U)
#define STCU_ALGOSEL_ALGOSEL13_WIDTH             (1U)
#define STCU_ALGOSEL_ALGOSEL13(x)                (((uint32_t)(((uint32_t)(x)) << STCU_ALGOSEL_ALGOSEL13_SHIFT)) & STCU_ALGOSEL_ALGOSEL13_MASK)

#define STCU_ALGOSEL_ALGOSEL14_MASK              (0x4000U)
#define STCU_ALGOSEL_ALGOSEL14_SHIFT             (14U)
#define STCU_ALGOSEL_ALGOSEL14_WIDTH             (1U)
#define STCU_ALGOSEL_ALGOSEL14(x)                (((uint32_t)(((uint32_t)(x)) << STCU_ALGOSEL_ALGOSEL14_SHIFT)) & STCU_ALGOSEL_ALGOSEL14_MASK)

#define STCU_ALGOSEL_ALGOSEL15_MASK              (0x8000U)
#define STCU_ALGOSEL_ALGOSEL15_SHIFT             (15U)
#define STCU_ALGOSEL_ALGOSEL15_WIDTH             (1U)
#define STCU_ALGOSEL_ALGOSEL15(x)                (((uint32_t)(((uint32_t)(x)) << STCU_ALGOSEL_ALGOSEL15_SHIFT)) & STCU_ALGOSEL_ALGOSEL15_MASK)

#define STCU_ALGOSEL_ALGOSEL16_MASK              (0x10000U)
#define STCU_ALGOSEL_ALGOSEL16_SHIFT             (16U)
#define STCU_ALGOSEL_ALGOSEL16_WIDTH             (1U)
#define STCU_ALGOSEL_ALGOSEL16(x)                (((uint32_t)(((uint32_t)(x)) << STCU_ALGOSEL_ALGOSEL16_SHIFT)) & STCU_ALGOSEL_ALGOSEL16_MASK)

#define STCU_ALGOSEL_ALGOSEL17_MASK              (0x20000U)
#define STCU_ALGOSEL_ALGOSEL17_SHIFT             (17U)
#define STCU_ALGOSEL_ALGOSEL17_WIDTH             (1U)
#define STCU_ALGOSEL_ALGOSEL17(x)                (((uint32_t)(((uint32_t)(x)) << STCU_ALGOSEL_ALGOSEL17_SHIFT)) & STCU_ALGOSEL_ALGOSEL17_MASK)

#define STCU_ALGOSEL_ALGOSEL18_MASK              (0x40000U)
#define STCU_ALGOSEL_ALGOSEL18_SHIFT             (18U)
#define STCU_ALGOSEL_ALGOSEL18_WIDTH             (1U)
#define STCU_ALGOSEL_ALGOSEL18(x)                (((uint32_t)(((uint32_t)(x)) << STCU_ALGOSEL_ALGOSEL18_SHIFT)) & STCU_ALGOSEL_ALGOSEL18_MASK)

#define STCU_ALGOSEL_ALGOSEL19_MASK              (0x80000U)
#define STCU_ALGOSEL_ALGOSEL19_SHIFT             (19U)
#define STCU_ALGOSEL_ALGOSEL19_WIDTH             (1U)
#define STCU_ALGOSEL_ALGOSEL19(x)                (((uint32_t)(((uint32_t)(x)) << STCU_ALGOSEL_ALGOSEL19_SHIFT)) & STCU_ALGOSEL_ALGOSEL19_MASK)

#define STCU_ALGOSEL_ALGOSEL20_MASK              (0x100000U)
#define STCU_ALGOSEL_ALGOSEL20_SHIFT             (20U)
#define STCU_ALGOSEL_ALGOSEL20_WIDTH             (1U)
#define STCU_ALGOSEL_ALGOSEL20(x)                (((uint32_t)(((uint32_t)(x)) << STCU_ALGOSEL_ALGOSEL20_SHIFT)) & STCU_ALGOSEL_ALGOSEL20_MASK)

#define STCU_ALGOSEL_ALGOSEL21_MASK              (0x200000U)
#define STCU_ALGOSEL_ALGOSEL21_SHIFT             (21U)
#define STCU_ALGOSEL_ALGOSEL21_WIDTH             (1U)
#define STCU_ALGOSEL_ALGOSEL21(x)                (((uint32_t)(((uint32_t)(x)) << STCU_ALGOSEL_ALGOSEL21_SHIFT)) & STCU_ALGOSEL_ALGOSEL21_MASK)

#define STCU_ALGOSEL_ALGOSEL22_MASK              (0x400000U)
#define STCU_ALGOSEL_ALGOSEL22_SHIFT             (22U)
#define STCU_ALGOSEL_ALGOSEL22_WIDTH             (1U)
#define STCU_ALGOSEL_ALGOSEL22(x)                (((uint32_t)(((uint32_t)(x)) << STCU_ALGOSEL_ALGOSEL22_SHIFT)) & STCU_ALGOSEL_ALGOSEL22_MASK)

#define STCU_ALGOSEL_ALGOSEL23_MASK              (0x800000U)
#define STCU_ALGOSEL_ALGOSEL23_SHIFT             (23U)
#define STCU_ALGOSEL_ALGOSEL23_WIDTH             (1U)
#define STCU_ALGOSEL_ALGOSEL23(x)                (((uint32_t)(((uint32_t)(x)) << STCU_ALGOSEL_ALGOSEL23_SHIFT)) & STCU_ALGOSEL_ALGOSEL23_MASK)

#define STCU_ALGOSEL_ALGOSEL24_MASK              (0x1000000U)
#define STCU_ALGOSEL_ALGOSEL24_SHIFT             (24U)
#define STCU_ALGOSEL_ALGOSEL24_WIDTH             (1U)
#define STCU_ALGOSEL_ALGOSEL24(x)                (((uint32_t)(((uint32_t)(x)) << STCU_ALGOSEL_ALGOSEL24_SHIFT)) & STCU_ALGOSEL_ALGOSEL24_MASK)

#define STCU_ALGOSEL_ALGOSEL25_MASK              (0x2000000U)
#define STCU_ALGOSEL_ALGOSEL25_SHIFT             (25U)
#define STCU_ALGOSEL_ALGOSEL25_WIDTH             (1U)
#define STCU_ALGOSEL_ALGOSEL25(x)                (((uint32_t)(((uint32_t)(x)) << STCU_ALGOSEL_ALGOSEL25_SHIFT)) & STCU_ALGOSEL_ALGOSEL25_MASK)

#define STCU_ALGOSEL_ALGOSEL26_MASK              (0x4000000U)
#define STCU_ALGOSEL_ALGOSEL26_SHIFT             (26U)
#define STCU_ALGOSEL_ALGOSEL26_WIDTH             (1U)
#define STCU_ALGOSEL_ALGOSEL26(x)                (((uint32_t)(((uint32_t)(x)) << STCU_ALGOSEL_ALGOSEL26_SHIFT)) & STCU_ALGOSEL_ALGOSEL26_MASK)

#define STCU_ALGOSEL_ALGOSEL27_MASK              (0x8000000U)
#define STCU_ALGOSEL_ALGOSEL27_SHIFT             (27U)
#define STCU_ALGOSEL_ALGOSEL27_WIDTH             (1U)
#define STCU_ALGOSEL_ALGOSEL27(x)                (((uint32_t)(((uint32_t)(x)) << STCU_ALGOSEL_ALGOSEL27_SHIFT)) & STCU_ALGOSEL_ALGOSEL27_MASK)

#define STCU_ALGOSEL_ALGOSEL28_MASK              (0x10000000U)
#define STCU_ALGOSEL_ALGOSEL28_SHIFT             (28U)
#define STCU_ALGOSEL_ALGOSEL28_WIDTH             (1U)
#define STCU_ALGOSEL_ALGOSEL28(x)                (((uint32_t)(((uint32_t)(x)) << STCU_ALGOSEL_ALGOSEL28_SHIFT)) & STCU_ALGOSEL_ALGOSEL28_MASK)

#define STCU_ALGOSEL_ALGOSEL29_MASK              (0x20000000U)
#define STCU_ALGOSEL_ALGOSEL29_SHIFT             (29U)
#define STCU_ALGOSEL_ALGOSEL29_WIDTH             (1U)
#define STCU_ALGOSEL_ALGOSEL29(x)                (((uint32_t)(((uint32_t)(x)) << STCU_ALGOSEL_ALGOSEL29_SHIFT)) & STCU_ALGOSEL_ALGOSEL29_MASK)

#define STCU_ALGOSEL_ALGOSEL30_MASK              (0x40000000U)
#define STCU_ALGOSEL_ALGOSEL30_SHIFT             (30U)
#define STCU_ALGOSEL_ALGOSEL30_WIDTH             (1U)
#define STCU_ALGOSEL_ALGOSEL30(x)                (((uint32_t)(((uint32_t)(x)) << STCU_ALGOSEL_ALGOSEL30_SHIFT)) & STCU_ALGOSEL_ALGOSEL30_MASK)

#define STCU_ALGOSEL_ALGOSEL31_MASK              (0x80000000U)
#define STCU_ALGOSEL_ALGOSEL31_SHIFT             (31U)
#define STCU_ALGOSEL_ALGOSEL31_WIDTH             (1U)
#define STCU_ALGOSEL_ALGOSEL31(x)                (((uint32_t)(((uint32_t)(x)) << STCU_ALGOSEL_ALGOSEL31_SHIFT)) & STCU_ALGOSEL_ALGOSEL31_MASK)
/*! @} */

/*! @name STGGR - STCU2 MBIST Stagger */
/*! @{ */

#define STCU_STGGR_STAG_MASK                     (0xFFFFFFFFU)
#define STCU_STGGR_STAG_SHIFT                    (0U)
#define STCU_STGGR_STAG_WIDTH                    (32U)
#define STCU_STGGR_STAG(x)                       (((uint32_t)(((uint32_t)(x)) << STCU_STGGR_STAG_SHIFT)) & STCU_STGGR_STAG_MASK)
/*! @} */

/*! @name BSTART - STCU2 BIST Start */
/*! @{ */

#define STCU_BSTART_BSTART0_MASK                 (0x1U)
#define STCU_BSTART_BSTART0_SHIFT                (0U)
#define STCU_BSTART_BSTART0_WIDTH                (1U)
#define STCU_BSTART_BSTART0(x)                   (((uint32_t)(((uint32_t)(x)) << STCU_BSTART_BSTART0_SHIFT)) & STCU_BSTART_BSTART0_MASK)

#define STCU_BSTART_BSTART1_MASK                 (0x2U)
#define STCU_BSTART_BSTART1_SHIFT                (1U)
#define STCU_BSTART_BSTART1_WIDTH                (1U)
#define STCU_BSTART_BSTART1(x)                   (((uint32_t)(((uint32_t)(x)) << STCU_BSTART_BSTART1_SHIFT)) & STCU_BSTART_BSTART1_MASK)

#define STCU_BSTART_BSTART2_MASK                 (0x4U)
#define STCU_BSTART_BSTART2_SHIFT                (2U)
#define STCU_BSTART_BSTART2_WIDTH                (1U)
#define STCU_BSTART_BSTART2(x)                   (((uint32_t)(((uint32_t)(x)) << STCU_BSTART_BSTART2_SHIFT)) & STCU_BSTART_BSTART2_MASK)

#define STCU_BSTART_BSTART3_MASK                 (0x8U)
#define STCU_BSTART_BSTART3_SHIFT                (3U)
#define STCU_BSTART_BSTART3_WIDTH                (1U)
#define STCU_BSTART_BSTART3(x)                   (((uint32_t)(((uint32_t)(x)) << STCU_BSTART_BSTART3_SHIFT)) & STCU_BSTART_BSTART3_MASK)

#define STCU_BSTART_BSTART4_MASK                 (0x10U)
#define STCU_BSTART_BSTART4_SHIFT                (4U)
#define STCU_BSTART_BSTART4_WIDTH                (1U)
#define STCU_BSTART_BSTART4(x)                   (((uint32_t)(((uint32_t)(x)) << STCU_BSTART_BSTART4_SHIFT)) & STCU_BSTART_BSTART4_MASK)

#define STCU_BSTART_BSTART5_MASK                 (0x20U)
#define STCU_BSTART_BSTART5_SHIFT                (5U)
#define STCU_BSTART_BSTART5_WIDTH                (1U)
#define STCU_BSTART_BSTART5(x)                   (((uint32_t)(((uint32_t)(x)) << STCU_BSTART_BSTART5_SHIFT)) & STCU_BSTART_BSTART5_MASK)

#define STCU_BSTART_BSTART6_MASK                 (0x40U)
#define STCU_BSTART_BSTART6_SHIFT                (6U)
#define STCU_BSTART_BSTART6_WIDTH                (1U)
#define STCU_BSTART_BSTART6(x)                   (((uint32_t)(((uint32_t)(x)) << STCU_BSTART_BSTART6_SHIFT)) & STCU_BSTART_BSTART6_MASK)

#define STCU_BSTART_BSTART7_MASK                 (0x80U)
#define STCU_BSTART_BSTART7_SHIFT                (7U)
#define STCU_BSTART_BSTART7_WIDTH                (1U)
#define STCU_BSTART_BSTART7(x)                   (((uint32_t)(((uint32_t)(x)) << STCU_BSTART_BSTART7_SHIFT)) & STCU_BSTART_BSTART7_MASK)

#define STCU_BSTART_BSTART8_MASK                 (0x100U)
#define STCU_BSTART_BSTART8_SHIFT                (8U)
#define STCU_BSTART_BSTART8_WIDTH                (1U)
#define STCU_BSTART_BSTART8(x)                   (((uint32_t)(((uint32_t)(x)) << STCU_BSTART_BSTART8_SHIFT)) & STCU_BSTART_BSTART8_MASK)

#define STCU_BSTART_BSTART9_MASK                 (0x200U)
#define STCU_BSTART_BSTART9_SHIFT                (9U)
#define STCU_BSTART_BSTART9_WIDTH                (1U)
#define STCU_BSTART_BSTART9(x)                   (((uint32_t)(((uint32_t)(x)) << STCU_BSTART_BSTART9_SHIFT)) & STCU_BSTART_BSTART9_MASK)

#define STCU_BSTART_BSTART10_MASK                (0x400U)
#define STCU_BSTART_BSTART10_SHIFT               (10U)
#define STCU_BSTART_BSTART10_WIDTH               (1U)
#define STCU_BSTART_BSTART10(x)                  (((uint32_t)(((uint32_t)(x)) << STCU_BSTART_BSTART10_SHIFT)) & STCU_BSTART_BSTART10_MASK)

#define STCU_BSTART_BSTART11_MASK                (0x800U)
#define STCU_BSTART_BSTART11_SHIFT               (11U)
#define STCU_BSTART_BSTART11_WIDTH               (1U)
#define STCU_BSTART_BSTART11(x)                  (((uint32_t)(((uint32_t)(x)) << STCU_BSTART_BSTART11_SHIFT)) & STCU_BSTART_BSTART11_MASK)

#define STCU_BSTART_BSTART12_MASK                (0x1000U)
#define STCU_BSTART_BSTART12_SHIFT               (12U)
#define STCU_BSTART_BSTART12_WIDTH               (1U)
#define STCU_BSTART_BSTART12(x)                  (((uint32_t)(((uint32_t)(x)) << STCU_BSTART_BSTART12_SHIFT)) & STCU_BSTART_BSTART12_MASK)

#define STCU_BSTART_BSTART13_MASK                (0x2000U)
#define STCU_BSTART_BSTART13_SHIFT               (13U)
#define STCU_BSTART_BSTART13_WIDTH               (1U)
#define STCU_BSTART_BSTART13(x)                  (((uint32_t)(((uint32_t)(x)) << STCU_BSTART_BSTART13_SHIFT)) & STCU_BSTART_BSTART13_MASK)

#define STCU_BSTART_BSTART14_MASK                (0x4000U)
#define STCU_BSTART_BSTART14_SHIFT               (14U)
#define STCU_BSTART_BSTART14_WIDTH               (1U)
#define STCU_BSTART_BSTART14(x)                  (((uint32_t)(((uint32_t)(x)) << STCU_BSTART_BSTART14_SHIFT)) & STCU_BSTART_BSTART14_MASK)

#define STCU_BSTART_BSTART15_MASK                (0x8000U)
#define STCU_BSTART_BSTART15_SHIFT               (15U)
#define STCU_BSTART_BSTART15_WIDTH               (1U)
#define STCU_BSTART_BSTART15(x)                  (((uint32_t)(((uint32_t)(x)) << STCU_BSTART_BSTART15_SHIFT)) & STCU_BSTART_BSTART15_MASK)

#define STCU_BSTART_BSTART16_MASK                (0x10000U)
#define STCU_BSTART_BSTART16_SHIFT               (16U)
#define STCU_BSTART_BSTART16_WIDTH               (1U)
#define STCU_BSTART_BSTART16(x)                  (((uint32_t)(((uint32_t)(x)) << STCU_BSTART_BSTART16_SHIFT)) & STCU_BSTART_BSTART16_MASK)

#define STCU_BSTART_BSTART17_MASK                (0x20000U)
#define STCU_BSTART_BSTART17_SHIFT               (17U)
#define STCU_BSTART_BSTART17_WIDTH               (1U)
#define STCU_BSTART_BSTART17(x)                  (((uint32_t)(((uint32_t)(x)) << STCU_BSTART_BSTART17_SHIFT)) & STCU_BSTART_BSTART17_MASK)

#define STCU_BSTART_BSTART18_MASK                (0x40000U)
#define STCU_BSTART_BSTART18_SHIFT               (18U)
#define STCU_BSTART_BSTART18_WIDTH               (1U)
#define STCU_BSTART_BSTART18(x)                  (((uint32_t)(((uint32_t)(x)) << STCU_BSTART_BSTART18_SHIFT)) & STCU_BSTART_BSTART18_MASK)

#define STCU_BSTART_BSTART19_MASK                (0x80000U)
#define STCU_BSTART_BSTART19_SHIFT               (19U)
#define STCU_BSTART_BSTART19_WIDTH               (1U)
#define STCU_BSTART_BSTART19(x)                  (((uint32_t)(((uint32_t)(x)) << STCU_BSTART_BSTART19_SHIFT)) & STCU_BSTART_BSTART19_MASK)

#define STCU_BSTART_BSTART20_MASK                (0x100000U)
#define STCU_BSTART_BSTART20_SHIFT               (20U)
#define STCU_BSTART_BSTART20_WIDTH               (1U)
#define STCU_BSTART_BSTART20(x)                  (((uint32_t)(((uint32_t)(x)) << STCU_BSTART_BSTART20_SHIFT)) & STCU_BSTART_BSTART20_MASK)

#define STCU_BSTART_BSTART21_MASK                (0x200000U)
#define STCU_BSTART_BSTART21_SHIFT               (21U)
#define STCU_BSTART_BSTART21_WIDTH               (1U)
#define STCU_BSTART_BSTART21(x)                  (((uint32_t)(((uint32_t)(x)) << STCU_BSTART_BSTART21_SHIFT)) & STCU_BSTART_BSTART21_MASK)

#define STCU_BSTART_BSTART22_MASK                (0x400000U)
#define STCU_BSTART_BSTART22_SHIFT               (22U)
#define STCU_BSTART_BSTART22_WIDTH               (1U)
#define STCU_BSTART_BSTART22(x)                  (((uint32_t)(((uint32_t)(x)) << STCU_BSTART_BSTART22_SHIFT)) & STCU_BSTART_BSTART22_MASK)

#define STCU_BSTART_BSTART23_MASK                (0x800000U)
#define STCU_BSTART_BSTART23_SHIFT               (23U)
#define STCU_BSTART_BSTART23_WIDTH               (1U)
#define STCU_BSTART_BSTART23(x)                  (((uint32_t)(((uint32_t)(x)) << STCU_BSTART_BSTART23_SHIFT)) & STCU_BSTART_BSTART23_MASK)

#define STCU_BSTART_BSTART24_MASK                (0x1000000U)
#define STCU_BSTART_BSTART24_SHIFT               (24U)
#define STCU_BSTART_BSTART24_WIDTH               (1U)
#define STCU_BSTART_BSTART24(x)                  (((uint32_t)(((uint32_t)(x)) << STCU_BSTART_BSTART24_SHIFT)) & STCU_BSTART_BSTART24_MASK)

#define STCU_BSTART_BSTART25_MASK                (0x2000000U)
#define STCU_BSTART_BSTART25_SHIFT               (25U)
#define STCU_BSTART_BSTART25_WIDTH               (1U)
#define STCU_BSTART_BSTART25(x)                  (((uint32_t)(((uint32_t)(x)) << STCU_BSTART_BSTART25_SHIFT)) & STCU_BSTART_BSTART25_MASK)

#define STCU_BSTART_BSTART26_MASK                (0x4000000U)
#define STCU_BSTART_BSTART26_SHIFT               (26U)
#define STCU_BSTART_BSTART26_WIDTH               (1U)
#define STCU_BSTART_BSTART26(x)                  (((uint32_t)(((uint32_t)(x)) << STCU_BSTART_BSTART26_SHIFT)) & STCU_BSTART_BSTART26_MASK)

#define STCU_BSTART_BSTART27_MASK                (0x8000000U)
#define STCU_BSTART_BSTART27_SHIFT               (27U)
#define STCU_BSTART_BSTART27_WIDTH               (1U)
#define STCU_BSTART_BSTART27(x)                  (((uint32_t)(((uint32_t)(x)) << STCU_BSTART_BSTART27_SHIFT)) & STCU_BSTART_BSTART27_MASK)

#define STCU_BSTART_BSTART28_MASK                (0x10000000U)
#define STCU_BSTART_BSTART28_SHIFT               (28U)
#define STCU_BSTART_BSTART28_WIDTH               (1U)
#define STCU_BSTART_BSTART28(x)                  (((uint32_t)(((uint32_t)(x)) << STCU_BSTART_BSTART28_SHIFT)) & STCU_BSTART_BSTART28_MASK)

#define STCU_BSTART_BSTART29_MASK                (0x20000000U)
#define STCU_BSTART_BSTART29_SHIFT               (29U)
#define STCU_BSTART_BSTART29_WIDTH               (1U)
#define STCU_BSTART_BSTART29(x)                  (((uint32_t)(((uint32_t)(x)) << STCU_BSTART_BSTART29_SHIFT)) & STCU_BSTART_BSTART29_MASK)

#define STCU_BSTART_BSTART30_MASK                (0x40000000U)
#define STCU_BSTART_BSTART30_SHIFT               (30U)
#define STCU_BSTART_BSTART30_WIDTH               (1U)
#define STCU_BSTART_BSTART30(x)                  (((uint32_t)(((uint32_t)(x)) << STCU_BSTART_BSTART30_SHIFT)) & STCU_BSTART_BSTART30_MASK)

#define STCU_BSTART_BSTART31_MASK                (0x80000000U)
#define STCU_BSTART_BSTART31_SHIFT               (31U)
#define STCU_BSTART_BSTART31_WIDTH               (1U)
#define STCU_BSTART_BSTART31(x)                  (((uint32_t)(((uint32_t)(x)) << STCU_BSTART_BSTART31_SHIFT)) & STCU_BSTART_BSTART31_MASK)
/*! @} */

/*! @name MB_CTRL - STCU2 MBIST Control */
/*! @{ */

#define STCU_MB_CTRL_BSEL_MASK                   (0x100000U)
#define STCU_MB_CTRL_BSEL_SHIFT                  (20U)
#define STCU_MB_CTRL_BSEL_WIDTH                  (1U)
#define STCU_MB_CTRL_BSEL(x)                     (((uint32_t)(((uint32_t)(x)) << STCU_MB_CTRL_BSEL_SHIFT)) & STCU_MB_CTRL_BSEL_MASK)

#define STCU_MB_CTRL_PTR_MASK                    (0x7FE00000U)
#define STCU_MB_CTRL_PTR_SHIFT                   (21U)
#define STCU_MB_CTRL_PTR_WIDTH                   (10U)
#define STCU_MB_CTRL_PTR(x)                      (((uint32_t)(((uint32_t)(x)) << STCU_MB_CTRL_PTR_SHIFT)) & STCU_MB_CTRL_PTR_MASK)

#define STCU_MB_CTRL_CSM_MASK                    (0x80000000U)
#define STCU_MB_CTRL_CSM_SHIFT                   (31U)
#define STCU_MB_CTRL_CSM_WIDTH                   (1U)
#define STCU_MB_CTRL_CSM(x)                      (((uint32_t)(((uint32_t)(x)) << STCU_MB_CTRL_CSM_SHIFT)) & STCU_MB_CTRL_CSM_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group STCU_Register_Masks */

/*!
 * @}
 */ /* end of group STCU_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_STCU_H_) */
