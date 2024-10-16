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
 * @file S32K344_FCCU.h
 * @version 1.9
 * @date 2021-10-27
 * @brief Peripheral Access Layer for S32K344_FCCU
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
#if !defined(S32K344_FCCU_H_)  /* Check if memory map has not been already included */
#define S32K344_FCCU_H_

#include "S32K344_COMMON.h"

/* ----------------------------------------------------------------------------
   -- FCCU Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FCCU_Peripheral_Access_Layer FCCU Peripheral Access Layer
 * @{
 */

/** FCCU - Size of Registers Arrays */
#define FCCU_NCF_CFG_COUNT                        1u
#define FCCU_NCFS_CFG_COUNT                       1u
#define FCCU_NCF_S_COUNT                          1u
#define FCCU_NCF_E_COUNT                          1u
#define FCCU_NCF_TOE_COUNT                        1u
#define FCCU_IRQ_ALARM_EN_COUNT                   1u
#define FCCU_NMI_EN_COUNT                         1u
#define FCCU_EOUT_SIG_EN_COUNT                    1u

/** FCCU - Register Layout Typedef */
typedef struct {
  __IO uint32_t CTRL;                              /**< Control, offset: 0x0 */
  __O  uint32_t CTRLK;                             /**< Control Key, offset: 0x4 */
  __IO uint32_t CFG;                               /**< Configuration, offset: 0x8 */
  uint8_t RESERVED_0[16];
  __IO uint32_t NCF_CFG[FCCU_NCF_CFG_COUNT];       /**< Non-critical Fault Configuration, array offset: 0x1C, array step: 0x4 */
  uint8_t RESERVED_1[44];
  __IO uint32_t NCFS_CFG[FCCU_NCFS_CFG_COUNT];     /**< Non-critical Fault-State Configuration, array offset: 0x4C, array step: 0x4 */
  uint8_t RESERVED_2[48];
  __IO uint32_t NCF_S[FCCU_NCF_S_COUNT];           /**< Non-critical Fault Status, array offset: 0x80, array step: 0x4 */
  uint8_t RESERVED_3[12];
  __O  uint32_t NCFK;                              /**< Non-critical Fault Key, offset: 0x90 */
  __IO uint32_t NCF_E[FCCU_NCF_E_COUNT];           /**< Non-critical Fault Enable, array offset: 0x94, array step: 0x4 */
  uint8_t RESERVED_4[12];
  __IO uint32_t NCF_TOE[FCCU_NCF_TOE_COUNT];       /**< Non-critical-Fault Alarm-State Timeout Enable, array offset: 0xA4, array step: 0x4 */
  uint8_t RESERVED_5[12];
  __IO uint32_t NCF_TO;                            /**< Non-critical-Fault Alarm-State Timeout Interval, offset: 0xB4 */
  __IO uint32_t CFG_TO;                            /**< Configuration-State Timeout Interval, offset: 0xB8 */
  __IO uint32_t EINOUT;                            /**< IO Control, offset: 0xBC */
  __I  uint32_t STAT;                              /**< Status, offset: 0xC0 */
  __I  uint32_t N2AF_STATUS;                       /**< Normal-to-Alarm Freeze Status, offset: 0xC4 */
  __I  uint32_t A2FF_STATUS;                       /**< Alarm-to-Fault Freeze Status, offset: 0xC8 */
  __I  uint32_t N2FF_STATUS;                       /**< Normal-to-Fault Freeze Status, offset: 0xCC */
  __I  uint32_t F2AF_STATUS;                       /**< Fault-to-Alarm Freeze Status, offset: 0xD0 */
  uint8_t RESERVED_6[8];
  __O  uint32_t NCFF;                              /**< Non-critical Fault Fake, offset: 0xDC */
  __IO uint32_t IRQ_STAT;                          /**< IRQ Status, offset: 0xE0 */
  __IO uint32_t IRQ_EN;                            /**< IRQ Enable, offset: 0xE4 */
  uint8_t RESERVED_7[8];
  __O  uint32_t TRANS_LOCK;                        /**< Transient Configuration Lock, offset: 0xF0 */
  __O  uint32_t PERMNT_LOCK;                       /**< Permanent Configuration Lock, offset: 0xF4 */
  __IO uint32_t DELTA_T;                           /**< Delta T, offset: 0xF8 */
  __IO uint32_t IRQ_ALARM_EN[FCCU_IRQ_ALARM_EN_COUNT]; /**< Non-critical Alarm-State Interrupt-Request Enable, array offset: 0xFC, array step: 0x4 */
  uint8_t RESERVED_8[12];
  __IO uint32_t NMI_EN[FCCU_NMI_EN_COUNT];         /**< Non-critical Fault-State Non-maskable-Interrupt-Request Enable, array offset: 0x10C, array step: 0x4 */
  uint8_t RESERVED_9[12];
  __IO uint32_t EOUT_SIG_EN[FCCU_EOUT_SIG_EN_COUNT]; /**< Non-critical Fault-State EOUT Signaling Enable, array offset: 0x11C, array step: 0x4 */
  uint8_t RESERVED_10[12];
  __I  uint32_t TMR_ALARM;                         /**< Alarm-State Timer, offset: 0x12C */
  uint8_t RESERVED_11[4];
  __I  uint32_t TMR_CFG;                           /**< Configuration-State Timer, offset: 0x134 */
  __I  uint32_t TMR_ETMR;                          /**< Fault-Output Timer, offset: 0x138 */
} FCCU_Type, *FCCU_MemMapPtr;

/** Number of instances of the FCCU module. */
#define FCCU_INSTANCE_COUNT                      (1u)

/* FCCU - Peripheral instance base addresses */
/** Peripheral FCCU base address */
#define IP_FCCU_BASE                             (0x40384000u)
/** Peripheral FCCU base pointer */
#define IP_FCCU                                  ((FCCU_Type *)IP_FCCU_BASE)
/** Array initializer of FCCU peripheral base addresses */
#define IP_FCCU_BASE_ADDRS                       { IP_FCCU_BASE }
/** Array initializer of FCCU peripheral base pointers */
#define IP_FCCU_BASE_PTRS                        { IP_FCCU }

/* ----------------------------------------------------------------------------
   -- FCCU Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FCCU_Register_Masks FCCU Register Masks
 * @{
 */

/*! @name CTRL - Control */
/*! @{ */

#define FCCU_CTRL_OPR_MASK                       (0x1FU)
#define FCCU_CTRL_OPR_SHIFT                      (0U)
#define FCCU_CTRL_OPR_WIDTH                      (5U)
#define FCCU_CTRL_OPR(x)                         (((uint32_t)(((uint32_t)(x)) << FCCU_CTRL_OPR_SHIFT)) & FCCU_CTRL_OPR_MASK)

#define FCCU_CTRL_OPS_MASK                       (0xC0U)
#define FCCU_CTRL_OPS_SHIFT                      (6U)
#define FCCU_CTRL_OPS_WIDTH                      (2U)
#define FCCU_CTRL_OPS(x)                         (((uint32_t)(((uint32_t)(x)) << FCCU_CTRL_OPS_SHIFT)) & FCCU_CTRL_OPS_MASK)

#define FCCU_CTRL_DEBUG_MASK                     (0x200U)
#define FCCU_CTRL_DEBUG_SHIFT                    (9U)
#define FCCU_CTRL_DEBUG_WIDTH                    (1U)
#define FCCU_CTRL_DEBUG(x)                       (((uint32_t)(((uint32_t)(x)) << FCCU_CTRL_DEBUG_SHIFT)) & FCCU_CTRL_DEBUG_MASK)
/*! @} */

/*! @name CTRLK - Control Key */
/*! @{ */

#define FCCU_CTRLK_CTRLK_MASK                    (0xFFFFFFFFU)
#define FCCU_CTRLK_CTRLK_SHIFT                   (0U)
#define FCCU_CTRLK_CTRLK_WIDTH                   (32U)
#define FCCU_CTRLK_CTRLK(x)                      (((uint32_t)(((uint32_t)(x)) << FCCU_CTRLK_CTRLK_SHIFT)) & FCCU_CTRLK_CTRLK_MASK)
/*! @} */

/*! @name CFG - Configuration */
/*! @{ */

#define FCCU_CFG_FOM_MASK                        (0x1C0U)
#define FCCU_CFG_FOM_SHIFT                       (6U)
#define FCCU_CFG_FOM_WIDTH                       (3U)
#define FCCU_CFG_FOM(x)                          (((uint32_t)(((uint32_t)(x)) << FCCU_CFG_FOM_SHIFT)) & FCCU_CFG_FOM_MASK)

#define FCCU_CFG_PS_MASK                         (0x200U)
#define FCCU_CFG_PS_SHIFT                        (9U)
#define FCCU_CFG_PS_WIDTH                        (1U)
#define FCCU_CFG_PS(x)                           (((uint32_t)(((uint32_t)(x)) << FCCU_CFG_PS_SHIFT)) & FCCU_CFG_PS_MASK)

#define FCCU_CFG_CM_MASK                         (0x800U)
#define FCCU_CFG_CM_SHIFT                        (11U)
#define FCCU_CFG_CM_WIDTH                        (1U)
#define FCCU_CFG_CM(x)                           (((uint32_t)(((uint32_t)(x)) << FCCU_CFG_CM_SHIFT)) & FCCU_CFG_CM_MASK)

#define FCCU_CFG_FCCU_SET_CLEAR_MASK             (0xC00000U)
#define FCCU_CFG_FCCU_SET_CLEAR_SHIFT            (22U)
#define FCCU_CFG_FCCU_SET_CLEAR_WIDTH            (2U)
#define FCCU_CFG_FCCU_SET_CLEAR(x)               (((uint32_t)(((uint32_t)(x)) << FCCU_CFG_FCCU_SET_CLEAR_SHIFT)) & FCCU_CFG_FCCU_SET_CLEAR_MASK)

#define FCCU_CFG_FCCU_SET_AFTER_RESET_MASK       (0x1000000U)
#define FCCU_CFG_FCCU_SET_AFTER_RESET_SHIFT      (24U)
#define FCCU_CFG_FCCU_SET_AFTER_RESET_WIDTH      (1U)
#define FCCU_CFG_FCCU_SET_AFTER_RESET(x)         (((uint32_t)(((uint32_t)(x)) << FCCU_CFG_FCCU_SET_AFTER_RESET_SHIFT)) & FCCU_CFG_FCCU_SET_AFTER_RESET_MASK)
/*! @} */

/*! @name NCF_CFG - Non-critical Fault Configuration */
/*! @{ */

#define FCCU_NCF_CFG_NCFC0_MASK                  (0x1U)
#define FCCU_NCF_CFG_NCFC0_SHIFT                 (0U)
#define FCCU_NCF_CFG_NCFC0_WIDTH                 (1U)
#define FCCU_NCF_CFG_NCFC0(x)                    (((uint32_t)(((uint32_t)(x)) << FCCU_NCF_CFG_NCFC0_SHIFT)) & FCCU_NCF_CFG_NCFC0_MASK)

#define FCCU_NCF_CFG_NCFC1_MASK                  (0x2U)
#define FCCU_NCF_CFG_NCFC1_SHIFT                 (1U)
#define FCCU_NCF_CFG_NCFC1_WIDTH                 (1U)
#define FCCU_NCF_CFG_NCFC1(x)                    (((uint32_t)(((uint32_t)(x)) << FCCU_NCF_CFG_NCFC1_SHIFT)) & FCCU_NCF_CFG_NCFC1_MASK)

#define FCCU_NCF_CFG_NCFC2_MASK                  (0x4U)
#define FCCU_NCF_CFG_NCFC2_SHIFT                 (2U)
#define FCCU_NCF_CFG_NCFC2_WIDTH                 (1U)
#define FCCU_NCF_CFG_NCFC2(x)                    (((uint32_t)(((uint32_t)(x)) << FCCU_NCF_CFG_NCFC2_SHIFT)) & FCCU_NCF_CFG_NCFC2_MASK)

#define FCCU_NCF_CFG_NCFC3_MASK                  (0x8U)
#define FCCU_NCF_CFG_NCFC3_SHIFT                 (3U)
#define FCCU_NCF_CFG_NCFC3_WIDTH                 (1U)
#define FCCU_NCF_CFG_NCFC3(x)                    (((uint32_t)(((uint32_t)(x)) << FCCU_NCF_CFG_NCFC3_SHIFT)) & FCCU_NCF_CFG_NCFC3_MASK)

#define FCCU_NCF_CFG_NCFC4_MASK                  (0x10U)
#define FCCU_NCF_CFG_NCFC4_SHIFT                 (4U)
#define FCCU_NCF_CFG_NCFC4_WIDTH                 (1U)
#define FCCU_NCF_CFG_NCFC4(x)                    (((uint32_t)(((uint32_t)(x)) << FCCU_NCF_CFG_NCFC4_SHIFT)) & FCCU_NCF_CFG_NCFC4_MASK)

#define FCCU_NCF_CFG_NCFC5_MASK                  (0x20U)
#define FCCU_NCF_CFG_NCFC5_SHIFT                 (5U)
#define FCCU_NCF_CFG_NCFC5_WIDTH                 (1U)
#define FCCU_NCF_CFG_NCFC5(x)                    (((uint32_t)(((uint32_t)(x)) << FCCU_NCF_CFG_NCFC5_SHIFT)) & FCCU_NCF_CFG_NCFC5_MASK)

#define FCCU_NCF_CFG_NCFC6_MASK                  (0x40U)
#define FCCU_NCF_CFG_NCFC6_SHIFT                 (6U)
#define FCCU_NCF_CFG_NCFC6_WIDTH                 (1U)
#define FCCU_NCF_CFG_NCFC6(x)                    (((uint32_t)(((uint32_t)(x)) << FCCU_NCF_CFG_NCFC6_SHIFT)) & FCCU_NCF_CFG_NCFC6_MASK)

#define FCCU_NCF_CFG_NCFC7_MASK                  (0x80U)
#define FCCU_NCF_CFG_NCFC7_SHIFT                 (7U)
#define FCCU_NCF_CFG_NCFC7_WIDTH                 (1U)
#define FCCU_NCF_CFG_NCFC7(x)                    (((uint32_t)(((uint32_t)(x)) << FCCU_NCF_CFG_NCFC7_SHIFT)) & FCCU_NCF_CFG_NCFC7_MASK)
/*! @} */

/*! @name NCFS_CFG - Non-critical Fault-State Configuration */
/*! @{ */

#define FCCU_NCFS_CFG_NCFSC0_MASK                (0x3U)
#define FCCU_NCFS_CFG_NCFSC0_SHIFT               (0U)
#define FCCU_NCFS_CFG_NCFSC0_WIDTH               (2U)
#define FCCU_NCFS_CFG_NCFSC0(x)                  (((uint32_t)(((uint32_t)(x)) << FCCU_NCFS_CFG_NCFSC0_SHIFT)) & FCCU_NCFS_CFG_NCFSC0_MASK)

#define FCCU_NCFS_CFG_NCFSC1_MASK                (0xCU)
#define FCCU_NCFS_CFG_NCFSC1_SHIFT               (2U)
#define FCCU_NCFS_CFG_NCFSC1_WIDTH               (2U)
#define FCCU_NCFS_CFG_NCFSC1(x)                  (((uint32_t)(((uint32_t)(x)) << FCCU_NCFS_CFG_NCFSC1_SHIFT)) & FCCU_NCFS_CFG_NCFSC1_MASK)

#define FCCU_NCFS_CFG_NCFSC2_MASK                (0x30U)
#define FCCU_NCFS_CFG_NCFSC2_SHIFT               (4U)
#define FCCU_NCFS_CFG_NCFSC2_WIDTH               (2U)
#define FCCU_NCFS_CFG_NCFSC2(x)                  (((uint32_t)(((uint32_t)(x)) << FCCU_NCFS_CFG_NCFSC2_SHIFT)) & FCCU_NCFS_CFG_NCFSC2_MASK)

#define FCCU_NCFS_CFG_NCFSC3_MASK                (0xC0U)
#define FCCU_NCFS_CFG_NCFSC3_SHIFT               (6U)
#define FCCU_NCFS_CFG_NCFSC3_WIDTH               (2U)
#define FCCU_NCFS_CFG_NCFSC3(x)                  (((uint32_t)(((uint32_t)(x)) << FCCU_NCFS_CFG_NCFSC3_SHIFT)) & FCCU_NCFS_CFG_NCFSC3_MASK)

#define FCCU_NCFS_CFG_NCFSC4_MASK                (0x300U)
#define FCCU_NCFS_CFG_NCFSC4_SHIFT               (8U)
#define FCCU_NCFS_CFG_NCFSC4_WIDTH               (2U)
#define FCCU_NCFS_CFG_NCFSC4(x)                  (((uint32_t)(((uint32_t)(x)) << FCCU_NCFS_CFG_NCFSC4_SHIFT)) & FCCU_NCFS_CFG_NCFSC4_MASK)

#define FCCU_NCFS_CFG_NCFSC5_MASK                (0xC00U)
#define FCCU_NCFS_CFG_NCFSC5_SHIFT               (10U)
#define FCCU_NCFS_CFG_NCFSC5_WIDTH               (2U)
#define FCCU_NCFS_CFG_NCFSC5(x)                  (((uint32_t)(((uint32_t)(x)) << FCCU_NCFS_CFG_NCFSC5_SHIFT)) & FCCU_NCFS_CFG_NCFSC5_MASK)

#define FCCU_NCFS_CFG_NCFSC6_MASK                (0x3000U)
#define FCCU_NCFS_CFG_NCFSC6_SHIFT               (12U)
#define FCCU_NCFS_CFG_NCFSC6_WIDTH               (2U)
#define FCCU_NCFS_CFG_NCFSC6(x)                  (((uint32_t)(((uint32_t)(x)) << FCCU_NCFS_CFG_NCFSC6_SHIFT)) & FCCU_NCFS_CFG_NCFSC6_MASK)

#define FCCU_NCFS_CFG_NCFSC7_MASK                (0xC000U)
#define FCCU_NCFS_CFG_NCFSC7_SHIFT               (14U)
#define FCCU_NCFS_CFG_NCFSC7_WIDTH               (2U)
#define FCCU_NCFS_CFG_NCFSC7(x)                  (((uint32_t)(((uint32_t)(x)) << FCCU_NCFS_CFG_NCFSC7_SHIFT)) & FCCU_NCFS_CFG_NCFSC7_MASK)
/*! @} */

/*! @name NCF_S - Non-critical Fault Status */
/*! @{ */

#define FCCU_NCF_S_NCFS0_MASK                    (0x1U)
#define FCCU_NCF_S_NCFS0_SHIFT                   (0U)
#define FCCU_NCF_S_NCFS0_WIDTH                   (1U)
#define FCCU_NCF_S_NCFS0(x)                      (((uint32_t)(((uint32_t)(x)) << FCCU_NCF_S_NCFS0_SHIFT)) & FCCU_NCF_S_NCFS0_MASK)

#define FCCU_NCF_S_NCFS1_MASK                    (0x2U)
#define FCCU_NCF_S_NCFS1_SHIFT                   (1U)
#define FCCU_NCF_S_NCFS1_WIDTH                   (1U)
#define FCCU_NCF_S_NCFS1(x)                      (((uint32_t)(((uint32_t)(x)) << FCCU_NCF_S_NCFS1_SHIFT)) & FCCU_NCF_S_NCFS1_MASK)

#define FCCU_NCF_S_NCFS2_MASK                    (0x4U)
#define FCCU_NCF_S_NCFS2_SHIFT                   (2U)
#define FCCU_NCF_S_NCFS2_WIDTH                   (1U)
#define FCCU_NCF_S_NCFS2(x)                      (((uint32_t)(((uint32_t)(x)) << FCCU_NCF_S_NCFS2_SHIFT)) & FCCU_NCF_S_NCFS2_MASK)

#define FCCU_NCF_S_NCFS3_MASK                    (0x8U)
#define FCCU_NCF_S_NCFS3_SHIFT                   (3U)
#define FCCU_NCF_S_NCFS3_WIDTH                   (1U)
#define FCCU_NCF_S_NCFS3(x)                      (((uint32_t)(((uint32_t)(x)) << FCCU_NCF_S_NCFS3_SHIFT)) & FCCU_NCF_S_NCFS3_MASK)

#define FCCU_NCF_S_NCFS4_MASK                    (0x10U)
#define FCCU_NCF_S_NCFS4_SHIFT                   (4U)
#define FCCU_NCF_S_NCFS4_WIDTH                   (1U)
#define FCCU_NCF_S_NCFS4(x)                      (((uint32_t)(((uint32_t)(x)) << FCCU_NCF_S_NCFS4_SHIFT)) & FCCU_NCF_S_NCFS4_MASK)

#define FCCU_NCF_S_NCFS5_MASK                    (0x20U)
#define FCCU_NCF_S_NCFS5_SHIFT                   (5U)
#define FCCU_NCF_S_NCFS5_WIDTH                   (1U)
#define FCCU_NCF_S_NCFS5(x)                      (((uint32_t)(((uint32_t)(x)) << FCCU_NCF_S_NCFS5_SHIFT)) & FCCU_NCF_S_NCFS5_MASK)

#define FCCU_NCF_S_NCFS6_MASK                    (0x40U)
#define FCCU_NCF_S_NCFS6_SHIFT                   (6U)
#define FCCU_NCF_S_NCFS6_WIDTH                   (1U)
#define FCCU_NCF_S_NCFS6(x)                      (((uint32_t)(((uint32_t)(x)) << FCCU_NCF_S_NCFS6_SHIFT)) & FCCU_NCF_S_NCFS6_MASK)

#define FCCU_NCF_S_NCFS7_MASK                    (0x80U)
#define FCCU_NCF_S_NCFS7_SHIFT                   (7U)
#define FCCU_NCF_S_NCFS7_WIDTH                   (1U)
#define FCCU_NCF_S_NCFS7(x)                      (((uint32_t)(((uint32_t)(x)) << FCCU_NCF_S_NCFS7_SHIFT)) & FCCU_NCF_S_NCFS7_MASK)
/*! @} */

/*! @name NCFK - Non-critical Fault Key */
/*! @{ */

#define FCCU_NCFK_NCFK_MASK                      (0xFFFFFFFFU)
#define FCCU_NCFK_NCFK_SHIFT                     (0U)
#define FCCU_NCFK_NCFK_WIDTH                     (32U)
#define FCCU_NCFK_NCFK(x)                        (((uint32_t)(((uint32_t)(x)) << FCCU_NCFK_NCFK_SHIFT)) & FCCU_NCFK_NCFK_MASK)
/*! @} */

/*! @name NCF_E - Non-critical Fault Enable */
/*! @{ */

#define FCCU_NCF_E_NCFE0_MASK                    (0x1U)
#define FCCU_NCF_E_NCFE0_SHIFT                   (0U)
#define FCCU_NCF_E_NCFE0_WIDTH                   (1U)
#define FCCU_NCF_E_NCFE0(x)                      (((uint32_t)(((uint32_t)(x)) << FCCU_NCF_E_NCFE0_SHIFT)) & FCCU_NCF_E_NCFE0_MASK)

#define FCCU_NCF_E_NCFE1_MASK                    (0x2U)
#define FCCU_NCF_E_NCFE1_SHIFT                   (1U)
#define FCCU_NCF_E_NCFE1_WIDTH                   (1U)
#define FCCU_NCF_E_NCFE1(x)                      (((uint32_t)(((uint32_t)(x)) << FCCU_NCF_E_NCFE1_SHIFT)) & FCCU_NCF_E_NCFE1_MASK)

#define FCCU_NCF_E_NCFE2_MASK                    (0x4U)
#define FCCU_NCF_E_NCFE2_SHIFT                   (2U)
#define FCCU_NCF_E_NCFE2_WIDTH                   (1U)
#define FCCU_NCF_E_NCFE2(x)                      (((uint32_t)(((uint32_t)(x)) << FCCU_NCF_E_NCFE2_SHIFT)) & FCCU_NCF_E_NCFE2_MASK)

#define FCCU_NCF_E_NCFE3_MASK                    (0x8U)
#define FCCU_NCF_E_NCFE3_SHIFT                   (3U)
#define FCCU_NCF_E_NCFE3_WIDTH                   (1U)
#define FCCU_NCF_E_NCFE3(x)                      (((uint32_t)(((uint32_t)(x)) << FCCU_NCF_E_NCFE3_SHIFT)) & FCCU_NCF_E_NCFE3_MASK)

#define FCCU_NCF_E_NCFE4_MASK                    (0x10U)
#define FCCU_NCF_E_NCFE4_SHIFT                   (4U)
#define FCCU_NCF_E_NCFE4_WIDTH                   (1U)
#define FCCU_NCF_E_NCFE4(x)                      (((uint32_t)(((uint32_t)(x)) << FCCU_NCF_E_NCFE4_SHIFT)) & FCCU_NCF_E_NCFE4_MASK)

#define FCCU_NCF_E_NCFE5_MASK                    (0x20U)
#define FCCU_NCF_E_NCFE5_SHIFT                   (5U)
#define FCCU_NCF_E_NCFE5_WIDTH                   (1U)
#define FCCU_NCF_E_NCFE5(x)                      (((uint32_t)(((uint32_t)(x)) << FCCU_NCF_E_NCFE5_SHIFT)) & FCCU_NCF_E_NCFE5_MASK)

#define FCCU_NCF_E_NCFE6_MASK                    (0x40U)
#define FCCU_NCF_E_NCFE6_SHIFT                   (6U)
#define FCCU_NCF_E_NCFE6_WIDTH                   (1U)
#define FCCU_NCF_E_NCFE6(x)                      (((uint32_t)(((uint32_t)(x)) << FCCU_NCF_E_NCFE6_SHIFT)) & FCCU_NCF_E_NCFE6_MASK)

#define FCCU_NCF_E_NCFE7_MASK                    (0x80U)
#define FCCU_NCF_E_NCFE7_SHIFT                   (7U)
#define FCCU_NCF_E_NCFE7_WIDTH                   (1U)
#define FCCU_NCF_E_NCFE7(x)                      (((uint32_t)(((uint32_t)(x)) << FCCU_NCF_E_NCFE7_SHIFT)) & FCCU_NCF_E_NCFE7_MASK)
/*! @} */

/*! @name NCF_TOE - Non-critical-Fault Alarm-State Timeout Enable */
/*! @{ */

#define FCCU_NCF_TOE_NCFTOE0_MASK                (0x1U)
#define FCCU_NCF_TOE_NCFTOE0_SHIFT               (0U)
#define FCCU_NCF_TOE_NCFTOE0_WIDTH               (1U)
#define FCCU_NCF_TOE_NCFTOE0(x)                  (((uint32_t)(((uint32_t)(x)) << FCCU_NCF_TOE_NCFTOE0_SHIFT)) & FCCU_NCF_TOE_NCFTOE0_MASK)

#define FCCU_NCF_TOE_NCFTOE1_MASK                (0x2U)
#define FCCU_NCF_TOE_NCFTOE1_SHIFT               (1U)
#define FCCU_NCF_TOE_NCFTOE1_WIDTH               (1U)
#define FCCU_NCF_TOE_NCFTOE1(x)                  (((uint32_t)(((uint32_t)(x)) << FCCU_NCF_TOE_NCFTOE1_SHIFT)) & FCCU_NCF_TOE_NCFTOE1_MASK)

#define FCCU_NCF_TOE_NCFTOE2_MASK                (0x4U)
#define FCCU_NCF_TOE_NCFTOE2_SHIFT               (2U)
#define FCCU_NCF_TOE_NCFTOE2_WIDTH               (1U)
#define FCCU_NCF_TOE_NCFTOE2(x)                  (((uint32_t)(((uint32_t)(x)) << FCCU_NCF_TOE_NCFTOE2_SHIFT)) & FCCU_NCF_TOE_NCFTOE2_MASK)

#define FCCU_NCF_TOE_NCFTOE3_MASK                (0x8U)
#define FCCU_NCF_TOE_NCFTOE3_SHIFT               (3U)
#define FCCU_NCF_TOE_NCFTOE3_WIDTH               (1U)
#define FCCU_NCF_TOE_NCFTOE3(x)                  (((uint32_t)(((uint32_t)(x)) << FCCU_NCF_TOE_NCFTOE3_SHIFT)) & FCCU_NCF_TOE_NCFTOE3_MASK)

#define FCCU_NCF_TOE_NCFTOE4_MASK                (0x10U)
#define FCCU_NCF_TOE_NCFTOE4_SHIFT               (4U)
#define FCCU_NCF_TOE_NCFTOE4_WIDTH               (1U)
#define FCCU_NCF_TOE_NCFTOE4(x)                  (((uint32_t)(((uint32_t)(x)) << FCCU_NCF_TOE_NCFTOE4_SHIFT)) & FCCU_NCF_TOE_NCFTOE4_MASK)

#define FCCU_NCF_TOE_NCFTOE5_MASK                (0x20U)
#define FCCU_NCF_TOE_NCFTOE5_SHIFT               (5U)
#define FCCU_NCF_TOE_NCFTOE5_WIDTH               (1U)
#define FCCU_NCF_TOE_NCFTOE5(x)                  (((uint32_t)(((uint32_t)(x)) << FCCU_NCF_TOE_NCFTOE5_SHIFT)) & FCCU_NCF_TOE_NCFTOE5_MASK)

#define FCCU_NCF_TOE_NCFTOE6_MASK                (0x40U)
#define FCCU_NCF_TOE_NCFTOE6_SHIFT               (6U)
#define FCCU_NCF_TOE_NCFTOE6_WIDTH               (1U)
#define FCCU_NCF_TOE_NCFTOE6(x)                  (((uint32_t)(((uint32_t)(x)) << FCCU_NCF_TOE_NCFTOE6_SHIFT)) & FCCU_NCF_TOE_NCFTOE6_MASK)

#define FCCU_NCF_TOE_NCFTOE7_MASK                (0x80U)
#define FCCU_NCF_TOE_NCFTOE7_SHIFT               (7U)
#define FCCU_NCF_TOE_NCFTOE7_WIDTH               (1U)
#define FCCU_NCF_TOE_NCFTOE7(x)                  (((uint32_t)(((uint32_t)(x)) << FCCU_NCF_TOE_NCFTOE7_SHIFT)) & FCCU_NCF_TOE_NCFTOE7_MASK)
/*! @} */

/*! @name NCF_TO - Non-critical-Fault Alarm-State Timeout Interval */
/*! @{ */

#define FCCU_NCF_TO_TO_MASK                      (0xFFFFFFFFU)
#define FCCU_NCF_TO_TO_SHIFT                     (0U)
#define FCCU_NCF_TO_TO_WIDTH                     (32U)
#define FCCU_NCF_TO_TO(x)                        (((uint32_t)(((uint32_t)(x)) << FCCU_NCF_TO_TO_SHIFT)) & FCCU_NCF_TO_TO_MASK)
/*! @} */

/*! @name CFG_TO - Configuration-State Timeout Interval */
/*! @{ */

#define FCCU_CFG_TO_TO_MASK                      (0x7U)
#define FCCU_CFG_TO_TO_SHIFT                     (0U)
#define FCCU_CFG_TO_TO_WIDTH                     (3U)
#define FCCU_CFG_TO_TO(x)                        (((uint32_t)(((uint32_t)(x)) << FCCU_CFG_TO_TO_SHIFT)) & FCCU_CFG_TO_TO_MASK)
/*! @} */

/*! @name EINOUT - IO Control */
/*! @{ */

#define FCCU_EINOUT_EOUT0_MASK                   (0x1U)
#define FCCU_EINOUT_EOUT0_SHIFT                  (0U)
#define FCCU_EINOUT_EOUT0_WIDTH                  (1U)
#define FCCU_EINOUT_EOUT0(x)                     (((uint32_t)(((uint32_t)(x)) << FCCU_EINOUT_EOUT0_SHIFT)) & FCCU_EINOUT_EOUT0_MASK)

#define FCCU_EINOUT_EOUT1_MASK                   (0x2U)
#define FCCU_EINOUT_EOUT1_SHIFT                  (1U)
#define FCCU_EINOUT_EOUT1_WIDTH                  (1U)
#define FCCU_EINOUT_EOUT1(x)                     (((uint32_t)(((uint32_t)(x)) << FCCU_EINOUT_EOUT1_SHIFT)) & FCCU_EINOUT_EOUT1_MASK)

#define FCCU_EINOUT_EIN0_MASK                    (0x10U)
#define FCCU_EINOUT_EIN0_SHIFT                   (4U)
#define FCCU_EINOUT_EIN0_WIDTH                   (1U)
#define FCCU_EINOUT_EIN0(x)                      (((uint32_t)(((uint32_t)(x)) << FCCU_EINOUT_EIN0_SHIFT)) & FCCU_EINOUT_EIN0_MASK)

#define FCCU_EINOUT_EIN1_MASK                    (0x20U)
#define FCCU_EINOUT_EIN1_SHIFT                   (5U)
#define FCCU_EINOUT_EIN1_WIDTH                   (1U)
#define FCCU_EINOUT_EIN1(x)                      (((uint32_t)(((uint32_t)(x)) << FCCU_EINOUT_EIN1_SHIFT)) & FCCU_EINOUT_EIN1_MASK)
/*! @} */

/*! @name STAT - Status */
/*! @{ */

#define FCCU_STAT_STATUS_MASK                    (0x7U)
#define FCCU_STAT_STATUS_SHIFT                   (0U)
#define FCCU_STAT_STATUS_WIDTH                   (3U)
#define FCCU_STAT_STATUS(x)                      (((uint32_t)(((uint32_t)(x)) << FCCU_STAT_STATUS_SHIFT)) & FCCU_STAT_STATUS_MASK)

#define FCCU_STAT_ESTAT_MASK                     (0x8U)
#define FCCU_STAT_ESTAT_SHIFT                    (3U)
#define FCCU_STAT_ESTAT_WIDTH                    (1U)
#define FCCU_STAT_ESTAT(x)                       (((uint32_t)(((uint32_t)(x)) << FCCU_STAT_ESTAT_SHIFT)) & FCCU_STAT_ESTAT_MASK)

#define FCCU_STAT_PhysicErrorPin_MASK            (0x30U)
#define FCCU_STAT_PhysicErrorPin_SHIFT           (4U)
#define FCCU_STAT_PhysicErrorPin_WIDTH           (2U)
#define FCCU_STAT_PhysicErrorPin(x)              (((uint32_t)(((uint32_t)(x)) << FCCU_STAT_PhysicErrorPin_SHIFT)) & FCCU_STAT_PhysicErrorPin_MASK)
/*! @} */

/*! @name N2AF_STATUS - Normal-to-Alarm Freeze Status */
/*! @{ */

#define FCCU_N2AF_STATUS_NAFS_MASK               (0xFFU)
#define FCCU_N2AF_STATUS_NAFS_SHIFT              (0U)
#define FCCU_N2AF_STATUS_NAFS_WIDTH              (8U)
#define FCCU_N2AF_STATUS_NAFS(x)                 (((uint32_t)(((uint32_t)(x)) << FCCU_N2AF_STATUS_NAFS_SHIFT)) & FCCU_N2AF_STATUS_NAFS_MASK)
/*! @} */

/*! @name A2FF_STATUS - Alarm-to-Fault Freeze Status */
/*! @{ */

#define FCCU_A2FF_STATUS_AFFS_MASK               (0xFFU)
#define FCCU_A2FF_STATUS_AFFS_SHIFT              (0U)
#define FCCU_A2FF_STATUS_AFFS_WIDTH              (8U)
#define FCCU_A2FF_STATUS_AFFS(x)                 (((uint32_t)(((uint32_t)(x)) << FCCU_A2FF_STATUS_AFFS_SHIFT)) & FCCU_A2FF_STATUS_AFFS_MASK)

#define FCCU_A2FF_STATUS_AF_SRC_MASK             (0x300U)
#define FCCU_A2FF_STATUS_AF_SRC_SHIFT            (8U)
#define FCCU_A2FF_STATUS_AF_SRC_WIDTH            (2U)
#define FCCU_A2FF_STATUS_AF_SRC(x)               (((uint32_t)(((uint32_t)(x)) << FCCU_A2FF_STATUS_AF_SRC_SHIFT)) & FCCU_A2FF_STATUS_AF_SRC_MASK)
/*! @} */

/*! @name N2FF_STATUS - Normal-to-Fault Freeze Status */
/*! @{ */

#define FCCU_N2FF_STATUS_NFFS_MASK               (0xFFU)
#define FCCU_N2FF_STATUS_NFFS_SHIFT              (0U)
#define FCCU_N2FF_STATUS_NFFS_WIDTH              (8U)
#define FCCU_N2FF_STATUS_NFFS(x)                 (((uint32_t)(((uint32_t)(x)) << FCCU_N2FF_STATUS_NFFS_SHIFT)) & FCCU_N2FF_STATUS_NFFS_MASK)

#define FCCU_N2FF_STATUS_NF_SRC_MASK             (0x300U)
#define FCCU_N2FF_STATUS_NF_SRC_SHIFT            (8U)
#define FCCU_N2FF_STATUS_NF_SRC_WIDTH            (2U)
#define FCCU_N2FF_STATUS_NF_SRC(x)               (((uint32_t)(((uint32_t)(x)) << FCCU_N2FF_STATUS_NF_SRC_SHIFT)) & FCCU_N2FF_STATUS_NF_SRC_MASK)
/*! @} */

/*! @name F2AF_STATUS - Fault-to-Alarm Freeze Status */
/*! @{ */

#define FCCU_F2AF_STATUS_FAFS_MASK               (0x1FFU)
#define FCCU_F2AF_STATUS_FAFS_SHIFT              (0U)
#define FCCU_F2AF_STATUS_FAFS_WIDTH              (9U)
#define FCCU_F2AF_STATUS_FAFS(x)                 (((uint32_t)(((uint32_t)(x)) << FCCU_F2AF_STATUS_FAFS_SHIFT)) & FCCU_F2AF_STATUS_FAFS_MASK)
/*! @} */

/*! @name NCFF - Non-critical Fault Fake */
/*! @{ */

#define FCCU_NCFF_FNCFC_MASK                     (0x7FU)
#define FCCU_NCFF_FNCFC_SHIFT                    (0U)
#define FCCU_NCFF_FNCFC_WIDTH                    (7U)
#define FCCU_NCFF_FNCFC(x)                       (((uint32_t)(((uint32_t)(x)) << FCCU_NCFF_FNCFC_SHIFT)) & FCCU_NCFF_FNCFC_MASK)
/*! @} */

/*! @name IRQ_STAT - IRQ Status */
/*! @{ */

#define FCCU_IRQ_STAT_CFG_TO_STAT_MASK           (0x1U)
#define FCCU_IRQ_STAT_CFG_TO_STAT_SHIFT          (0U)
#define FCCU_IRQ_STAT_CFG_TO_STAT_WIDTH          (1U)
#define FCCU_IRQ_STAT_CFG_TO_STAT(x)             (((uint32_t)(((uint32_t)(x)) << FCCU_IRQ_STAT_CFG_TO_STAT_SHIFT)) & FCCU_IRQ_STAT_CFG_TO_STAT_MASK)

#define FCCU_IRQ_STAT_ALRM_STAT_MASK             (0x2U)
#define FCCU_IRQ_STAT_ALRM_STAT_SHIFT            (1U)
#define FCCU_IRQ_STAT_ALRM_STAT_WIDTH            (1U)
#define FCCU_IRQ_STAT_ALRM_STAT(x)               (((uint32_t)(((uint32_t)(x)) << FCCU_IRQ_STAT_ALRM_STAT_SHIFT)) & FCCU_IRQ_STAT_ALRM_STAT_MASK)

#define FCCU_IRQ_STAT_NMI_STAT_MASK              (0x4U)
#define FCCU_IRQ_STAT_NMI_STAT_SHIFT             (2U)
#define FCCU_IRQ_STAT_NMI_STAT_WIDTH             (1U)
#define FCCU_IRQ_STAT_NMI_STAT(x)                (((uint32_t)(((uint32_t)(x)) << FCCU_IRQ_STAT_NMI_STAT_SHIFT)) & FCCU_IRQ_STAT_NMI_STAT_MASK)
/*! @} */

/*! @name IRQ_EN - IRQ Enable */
/*! @{ */

#define FCCU_IRQ_EN_CFG_TO_IEN_MASK              (0x1U)
#define FCCU_IRQ_EN_CFG_TO_IEN_SHIFT             (0U)
#define FCCU_IRQ_EN_CFG_TO_IEN_WIDTH             (1U)
#define FCCU_IRQ_EN_CFG_TO_IEN(x)                (((uint32_t)(((uint32_t)(x)) << FCCU_IRQ_EN_CFG_TO_IEN_SHIFT)) & FCCU_IRQ_EN_CFG_TO_IEN_MASK)
/*! @} */

/*! @name TRANS_LOCK - Transient Configuration Lock */
/*! @{ */

#define FCCU_TRANS_LOCK_TRANSKEY_MASK            (0x1FFU)
#define FCCU_TRANS_LOCK_TRANSKEY_SHIFT           (0U)
#define FCCU_TRANS_LOCK_TRANSKEY_WIDTH           (9U)
#define FCCU_TRANS_LOCK_TRANSKEY(x)              (((uint32_t)(((uint32_t)(x)) << FCCU_TRANS_LOCK_TRANSKEY_SHIFT)) & FCCU_TRANS_LOCK_TRANSKEY_MASK)
/*! @} */

/*! @name PERMNT_LOCK - Permanent Configuration Lock */
/*! @{ */

#define FCCU_PERMNT_LOCK_PERMNTKEY_MASK          (0x1FFU)
#define FCCU_PERMNT_LOCK_PERMNTKEY_SHIFT         (0U)
#define FCCU_PERMNT_LOCK_PERMNTKEY_WIDTH         (9U)
#define FCCU_PERMNT_LOCK_PERMNTKEY(x)            (((uint32_t)(((uint32_t)(x)) << FCCU_PERMNT_LOCK_PERMNTKEY_SHIFT)) & FCCU_PERMNT_LOCK_PERMNTKEY_MASK)
/*! @} */

/*! @name DELTA_T - Delta T */
/*! @{ */

#define FCCU_DELTA_T_DELTA_T_MASK                (0x3FFFU)
#define FCCU_DELTA_T_DELTA_T_SHIFT               (0U)
#define FCCU_DELTA_T_DELTA_T_WIDTH               (14U)
#define FCCU_DELTA_T_DELTA_T(x)                  (((uint32_t)(((uint32_t)(x)) << FCCU_DELTA_T_DELTA_T_SHIFT)) & FCCU_DELTA_T_DELTA_T_MASK)
/*! @} */

/*! @name IRQ_ALARM_EN - Non-critical Alarm-State Interrupt-Request Enable */
/*! @{ */

#define FCCU_IRQ_ALARM_EN_IRQEN0_MASK            (0x1U)
#define FCCU_IRQ_ALARM_EN_IRQEN0_SHIFT           (0U)
#define FCCU_IRQ_ALARM_EN_IRQEN0_WIDTH           (1U)
#define FCCU_IRQ_ALARM_EN_IRQEN0(x)              (((uint32_t)(((uint32_t)(x)) << FCCU_IRQ_ALARM_EN_IRQEN0_SHIFT)) & FCCU_IRQ_ALARM_EN_IRQEN0_MASK)

#define FCCU_IRQ_ALARM_EN_IRQEN1_MASK            (0x2U)
#define FCCU_IRQ_ALARM_EN_IRQEN1_SHIFT           (1U)
#define FCCU_IRQ_ALARM_EN_IRQEN1_WIDTH           (1U)
#define FCCU_IRQ_ALARM_EN_IRQEN1(x)              (((uint32_t)(((uint32_t)(x)) << FCCU_IRQ_ALARM_EN_IRQEN1_SHIFT)) & FCCU_IRQ_ALARM_EN_IRQEN1_MASK)

#define FCCU_IRQ_ALARM_EN_IRQEN2_MASK            (0x4U)
#define FCCU_IRQ_ALARM_EN_IRQEN2_SHIFT           (2U)
#define FCCU_IRQ_ALARM_EN_IRQEN2_WIDTH           (1U)
#define FCCU_IRQ_ALARM_EN_IRQEN2(x)              (((uint32_t)(((uint32_t)(x)) << FCCU_IRQ_ALARM_EN_IRQEN2_SHIFT)) & FCCU_IRQ_ALARM_EN_IRQEN2_MASK)

#define FCCU_IRQ_ALARM_EN_IRQEN3_MASK            (0x8U)
#define FCCU_IRQ_ALARM_EN_IRQEN3_SHIFT           (3U)
#define FCCU_IRQ_ALARM_EN_IRQEN3_WIDTH           (1U)
#define FCCU_IRQ_ALARM_EN_IRQEN3(x)              (((uint32_t)(((uint32_t)(x)) << FCCU_IRQ_ALARM_EN_IRQEN3_SHIFT)) & FCCU_IRQ_ALARM_EN_IRQEN3_MASK)

#define FCCU_IRQ_ALARM_EN_IRQEN4_MASK            (0x10U)
#define FCCU_IRQ_ALARM_EN_IRQEN4_SHIFT           (4U)
#define FCCU_IRQ_ALARM_EN_IRQEN4_WIDTH           (1U)
#define FCCU_IRQ_ALARM_EN_IRQEN4(x)              (((uint32_t)(((uint32_t)(x)) << FCCU_IRQ_ALARM_EN_IRQEN4_SHIFT)) & FCCU_IRQ_ALARM_EN_IRQEN4_MASK)

#define FCCU_IRQ_ALARM_EN_IRQEN5_MASK            (0x20U)
#define FCCU_IRQ_ALARM_EN_IRQEN5_SHIFT           (5U)
#define FCCU_IRQ_ALARM_EN_IRQEN5_WIDTH           (1U)
#define FCCU_IRQ_ALARM_EN_IRQEN5(x)              (((uint32_t)(((uint32_t)(x)) << FCCU_IRQ_ALARM_EN_IRQEN5_SHIFT)) & FCCU_IRQ_ALARM_EN_IRQEN5_MASK)

#define FCCU_IRQ_ALARM_EN_IRQEN6_MASK            (0x40U)
#define FCCU_IRQ_ALARM_EN_IRQEN6_SHIFT           (6U)
#define FCCU_IRQ_ALARM_EN_IRQEN6_WIDTH           (1U)
#define FCCU_IRQ_ALARM_EN_IRQEN6(x)              (((uint32_t)(((uint32_t)(x)) << FCCU_IRQ_ALARM_EN_IRQEN6_SHIFT)) & FCCU_IRQ_ALARM_EN_IRQEN6_MASK)

#define FCCU_IRQ_ALARM_EN_IRQEN7_MASK            (0x80U)
#define FCCU_IRQ_ALARM_EN_IRQEN7_SHIFT           (7U)
#define FCCU_IRQ_ALARM_EN_IRQEN7_WIDTH           (1U)
#define FCCU_IRQ_ALARM_EN_IRQEN7(x)              (((uint32_t)(((uint32_t)(x)) << FCCU_IRQ_ALARM_EN_IRQEN7_SHIFT)) & FCCU_IRQ_ALARM_EN_IRQEN7_MASK)
/*! @} */

/*! @name NMI_EN - Non-critical Fault-State Non-maskable-Interrupt-Request Enable */
/*! @{ */

#define FCCU_NMI_EN_NMIEN0_MASK                  (0x1U)
#define FCCU_NMI_EN_NMIEN0_SHIFT                 (0U)
#define FCCU_NMI_EN_NMIEN0_WIDTH                 (1U)
#define FCCU_NMI_EN_NMIEN0(x)                    (((uint32_t)(((uint32_t)(x)) << FCCU_NMI_EN_NMIEN0_SHIFT)) & FCCU_NMI_EN_NMIEN0_MASK)

#define FCCU_NMI_EN_NMIEN1_MASK                  (0x2U)
#define FCCU_NMI_EN_NMIEN1_SHIFT                 (1U)
#define FCCU_NMI_EN_NMIEN1_WIDTH                 (1U)
#define FCCU_NMI_EN_NMIEN1(x)                    (((uint32_t)(((uint32_t)(x)) << FCCU_NMI_EN_NMIEN1_SHIFT)) & FCCU_NMI_EN_NMIEN1_MASK)

#define FCCU_NMI_EN_NMIEN2_MASK                  (0x4U)
#define FCCU_NMI_EN_NMIEN2_SHIFT                 (2U)
#define FCCU_NMI_EN_NMIEN2_WIDTH                 (1U)
#define FCCU_NMI_EN_NMIEN2(x)                    (((uint32_t)(((uint32_t)(x)) << FCCU_NMI_EN_NMIEN2_SHIFT)) & FCCU_NMI_EN_NMIEN2_MASK)

#define FCCU_NMI_EN_NMIEN3_MASK                  (0x8U)
#define FCCU_NMI_EN_NMIEN3_SHIFT                 (3U)
#define FCCU_NMI_EN_NMIEN3_WIDTH                 (1U)
#define FCCU_NMI_EN_NMIEN3(x)                    (((uint32_t)(((uint32_t)(x)) << FCCU_NMI_EN_NMIEN3_SHIFT)) & FCCU_NMI_EN_NMIEN3_MASK)

#define FCCU_NMI_EN_NMIEN4_MASK                  (0x10U)
#define FCCU_NMI_EN_NMIEN4_SHIFT                 (4U)
#define FCCU_NMI_EN_NMIEN4_WIDTH                 (1U)
#define FCCU_NMI_EN_NMIEN4(x)                    (((uint32_t)(((uint32_t)(x)) << FCCU_NMI_EN_NMIEN4_SHIFT)) & FCCU_NMI_EN_NMIEN4_MASK)

#define FCCU_NMI_EN_NMIEN5_MASK                  (0x20U)
#define FCCU_NMI_EN_NMIEN5_SHIFT                 (5U)
#define FCCU_NMI_EN_NMIEN5_WIDTH                 (1U)
#define FCCU_NMI_EN_NMIEN5(x)                    (((uint32_t)(((uint32_t)(x)) << FCCU_NMI_EN_NMIEN5_SHIFT)) & FCCU_NMI_EN_NMIEN5_MASK)

#define FCCU_NMI_EN_NMIEN6_MASK                  (0x40U)
#define FCCU_NMI_EN_NMIEN6_SHIFT                 (6U)
#define FCCU_NMI_EN_NMIEN6_WIDTH                 (1U)
#define FCCU_NMI_EN_NMIEN6(x)                    (((uint32_t)(((uint32_t)(x)) << FCCU_NMI_EN_NMIEN6_SHIFT)) & FCCU_NMI_EN_NMIEN6_MASK)

#define FCCU_NMI_EN_NMIEN7_MASK                  (0x80U)
#define FCCU_NMI_EN_NMIEN7_SHIFT                 (7U)
#define FCCU_NMI_EN_NMIEN7_WIDTH                 (1U)
#define FCCU_NMI_EN_NMIEN7(x)                    (((uint32_t)(((uint32_t)(x)) << FCCU_NMI_EN_NMIEN7_SHIFT)) & FCCU_NMI_EN_NMIEN7_MASK)
/*! @} */

/*! @name EOUT_SIG_EN - Non-critical Fault-State EOUT Signaling Enable */
/*! @{ */

#define FCCU_EOUT_SIG_EN_EOUTEN0_MASK            (0x1U)
#define FCCU_EOUT_SIG_EN_EOUTEN0_SHIFT           (0U)
#define FCCU_EOUT_SIG_EN_EOUTEN0_WIDTH           (1U)
#define FCCU_EOUT_SIG_EN_EOUTEN0(x)              (((uint32_t)(((uint32_t)(x)) << FCCU_EOUT_SIG_EN_EOUTEN0_SHIFT)) & FCCU_EOUT_SIG_EN_EOUTEN0_MASK)

#define FCCU_EOUT_SIG_EN_EOUTEN1_MASK            (0x2U)
#define FCCU_EOUT_SIG_EN_EOUTEN1_SHIFT           (1U)
#define FCCU_EOUT_SIG_EN_EOUTEN1_WIDTH           (1U)
#define FCCU_EOUT_SIG_EN_EOUTEN1(x)              (((uint32_t)(((uint32_t)(x)) << FCCU_EOUT_SIG_EN_EOUTEN1_SHIFT)) & FCCU_EOUT_SIG_EN_EOUTEN1_MASK)

#define FCCU_EOUT_SIG_EN_EOUTEN2_MASK            (0x4U)
#define FCCU_EOUT_SIG_EN_EOUTEN2_SHIFT           (2U)
#define FCCU_EOUT_SIG_EN_EOUTEN2_WIDTH           (1U)
#define FCCU_EOUT_SIG_EN_EOUTEN2(x)              (((uint32_t)(((uint32_t)(x)) << FCCU_EOUT_SIG_EN_EOUTEN2_SHIFT)) & FCCU_EOUT_SIG_EN_EOUTEN2_MASK)

#define FCCU_EOUT_SIG_EN_EOUTEN3_MASK            (0x8U)
#define FCCU_EOUT_SIG_EN_EOUTEN3_SHIFT           (3U)
#define FCCU_EOUT_SIG_EN_EOUTEN3_WIDTH           (1U)
#define FCCU_EOUT_SIG_EN_EOUTEN3(x)              (((uint32_t)(((uint32_t)(x)) << FCCU_EOUT_SIG_EN_EOUTEN3_SHIFT)) & FCCU_EOUT_SIG_EN_EOUTEN3_MASK)

#define FCCU_EOUT_SIG_EN_EOUTEN4_MASK            (0x10U)
#define FCCU_EOUT_SIG_EN_EOUTEN4_SHIFT           (4U)
#define FCCU_EOUT_SIG_EN_EOUTEN4_WIDTH           (1U)
#define FCCU_EOUT_SIG_EN_EOUTEN4(x)              (((uint32_t)(((uint32_t)(x)) << FCCU_EOUT_SIG_EN_EOUTEN4_SHIFT)) & FCCU_EOUT_SIG_EN_EOUTEN4_MASK)

#define FCCU_EOUT_SIG_EN_EOUTEN5_MASK            (0x20U)
#define FCCU_EOUT_SIG_EN_EOUTEN5_SHIFT           (5U)
#define FCCU_EOUT_SIG_EN_EOUTEN5_WIDTH           (1U)
#define FCCU_EOUT_SIG_EN_EOUTEN5(x)              (((uint32_t)(((uint32_t)(x)) << FCCU_EOUT_SIG_EN_EOUTEN5_SHIFT)) & FCCU_EOUT_SIG_EN_EOUTEN5_MASK)

#define FCCU_EOUT_SIG_EN_EOUTEN6_MASK            (0x40U)
#define FCCU_EOUT_SIG_EN_EOUTEN6_SHIFT           (6U)
#define FCCU_EOUT_SIG_EN_EOUTEN6_WIDTH           (1U)
#define FCCU_EOUT_SIG_EN_EOUTEN6(x)              (((uint32_t)(((uint32_t)(x)) << FCCU_EOUT_SIG_EN_EOUTEN6_SHIFT)) & FCCU_EOUT_SIG_EN_EOUTEN6_MASK)

#define FCCU_EOUT_SIG_EN_EOUTEN7_MASK            (0x80U)
#define FCCU_EOUT_SIG_EN_EOUTEN7_SHIFT           (7U)
#define FCCU_EOUT_SIG_EN_EOUTEN7_WIDTH           (1U)
#define FCCU_EOUT_SIG_EN_EOUTEN7(x)              (((uint32_t)(((uint32_t)(x)) << FCCU_EOUT_SIG_EN_EOUTEN7_SHIFT)) & FCCU_EOUT_SIG_EN_EOUTEN7_MASK)
/*! @} */

/*! @name TMR_ALARM - Alarm-State Timer */
/*! @{ */

#define FCCU_TMR_ALARM_COUNT_MASK                (0xFFFFFFFFU)
#define FCCU_TMR_ALARM_COUNT_SHIFT               (0U)
#define FCCU_TMR_ALARM_COUNT_WIDTH               (32U)
#define FCCU_TMR_ALARM_COUNT(x)                  (((uint32_t)(((uint32_t)(x)) << FCCU_TMR_ALARM_COUNT_SHIFT)) & FCCU_TMR_ALARM_COUNT_MASK)
/*! @} */

/*! @name TMR_CFG - Configuration-State Timer */
/*! @{ */

#define FCCU_TMR_CFG_COUNT_MASK                  (0xFFFFFFFFU)
#define FCCU_TMR_CFG_COUNT_SHIFT                 (0U)
#define FCCU_TMR_CFG_COUNT_WIDTH                 (32U)
#define FCCU_TMR_CFG_COUNT(x)                    (((uint32_t)(((uint32_t)(x)) << FCCU_TMR_CFG_COUNT_SHIFT)) & FCCU_TMR_CFG_COUNT_MASK)
/*! @} */

/*! @name TMR_ETMR - Fault-Output Timer */
/*! @{ */

#define FCCU_TMR_ETMR_COUNT_MASK                 (0xFFFFFFFFU)
#define FCCU_TMR_ETMR_COUNT_SHIFT                (0U)
#define FCCU_TMR_ETMR_COUNT_WIDTH                (32U)
#define FCCU_TMR_ETMR_COUNT(x)                   (((uint32_t)(((uint32_t)(x)) << FCCU_TMR_ETMR_COUNT_SHIFT)) & FCCU_TMR_ETMR_COUNT_MASK)
/*! @} */

/*!
 * @}
 */ /* end of group FCCU_Register_Masks */

/*!
 * @}
 */ /* end of group FCCU_Peripheral_Access_Layer */

#endif  /* #if !defined(S32K344_FCCU_H_) */
