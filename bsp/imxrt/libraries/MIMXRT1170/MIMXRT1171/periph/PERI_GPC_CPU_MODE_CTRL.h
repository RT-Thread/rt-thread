/*
** ###################################################################
**     Processors:          MIMXRT1171AVM8A
**                          MIMXRT1171AVM8B
**                          MIMXRT1171CVM8A
**                          MIMXRT1171CVM8B
**                          MIMXRT1171DVMAA
**                          MIMXRT1171DVMAB
**                          MIMXRT1172AVM8A
**                          MIMXRT1172AVM8B
**                          MIMXRT1172CVM8A
**                          MIMXRT1172CVM8B
**                          MIMXRT1172DVMAA
**                          MIMXRT1172DVMAB
**                          MIMXRT1173CVM8A_cm4
**                          MIMXRT1173CVM8A_cm7
**                          MIMXRT1173CVM8B_cm4
**                          MIMXRT1173CVM8B_cm7
**                          MIMXRT1175AVM8A_cm4
**                          MIMXRT1175AVM8A_cm7
**                          MIMXRT1175AVM8B_cm4
**                          MIMXRT1175AVM8B_cm7
**                          MIMXRT1175CVM8A_cm4
**                          MIMXRT1175CVM8A_cm7
**                          MIMXRT1175CVM8B_cm4
**                          MIMXRT1175CVM8B_cm7
**                          MIMXRT1175DVMAA_cm4
**                          MIMXRT1175DVMAA_cm7
**                          MIMXRT1175DVMAB_cm4
**                          MIMXRT1175DVMAB_cm7
**                          MIMXRT1176AVM8A_cm4
**                          MIMXRT1176AVM8A_cm7
**                          MIMXRT1176AVM8B_cm4
**                          MIMXRT1176AVM8B_cm7
**                          MIMXRT1176CVM8A_cm4
**                          MIMXRT1176CVM8A_cm7
**                          MIMXRT1176CVM8B_cm4
**                          MIMXRT1176CVM8B_cm7
**                          MIMXRT1176DVMAA_cm4
**                          MIMXRT1176DVMAA_cm7
**                          MIMXRT1176DVMAB_cm4
**                          MIMXRT1176DVMAB_cm7
**                          MIMXRT117HAVM8A_cm4
**                          MIMXRT117HAVM8A_cm7
**                          MIMXRT117HAVM8B_cm4
**                          MIMXRT117HAVM8B_cm7
**                          MIMXRT117HCVM8A_cm4
**                          MIMXRT117HCVM8A_cm7
**                          MIMXRT117HCVM8B_cm4
**                          MIMXRT117HCVM8B_cm7
**                          MIMXRT117HDVMAA_cm4
**                          MIMXRT117HDVMAA_cm7
**                          MIMXRT117HDVMAB_cm4
**                          MIMXRT117HDVMAB_cm7
**
**     Version:             rev. 2.0, 2024-10-29
**     Build:               b250520
**
**     Abstract:
**         CMSIS Peripheral Access Layer for GPC_CPU_MODE_CTRL
**
**     Copyright 1997-2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2025 NXP
**     SPDX-License-Identifier: BSD-3-Clause
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 0.1 (2018-03-05)
**         Initial version.
**     - rev. 1.0 (2020-12-29)
**         Update header files to align with IMXRT1170RM Rev.0.
**     - rev. 2.0 (2024-10-29)
**         Change the device header file from single flat file to multiple files based on peripherals,
**         each peripheral with dedicated header file located in periphN folder.
**
** ###################################################################
*/

/*!
 * @file PERI_GPC_CPU_MODE_CTRL.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for GPC_CPU_MODE_CTRL
 *
 * CMSIS Peripheral Access Layer for GPC_CPU_MODE_CTRL
 */

#if !defined(PERI_GPC_CPU_MODE_CTRL_H_)
#define PERI_GPC_CPU_MODE_CTRL_H_                /**< Symbol preventing repeated inclusion */

#if (defined(CPU_MIMXRT1171AVM8A) || defined(CPU_MIMXRT1171AVM8B) || defined(CPU_MIMXRT1171CVM8A) || defined(CPU_MIMXRT1171CVM8B) || defined(CPU_MIMXRT1171DVMAA) || defined(CPU_MIMXRT1171DVMAB))
#include "MIMXRT1171_COMMON.h"
#elif (defined(CPU_MIMXRT1172AVM8A) || defined(CPU_MIMXRT1172AVM8B) || defined(CPU_MIMXRT1172CVM8A) || defined(CPU_MIMXRT1172CVM8B) || defined(CPU_MIMXRT1172DVMAA) || defined(CPU_MIMXRT1172DVMAB))
#include "MIMXRT1172_COMMON.h"
#elif (defined(CPU_MIMXRT1173CVM8A_cm4) || defined(CPU_MIMXRT1173CVM8B_cm4))
#include "MIMXRT1173_cm4_COMMON.h"
#elif (defined(CPU_MIMXRT1173CVM8A_cm7) || defined(CPU_MIMXRT1173CVM8B_cm7))
#include "MIMXRT1173_cm7_COMMON.h"
#elif (defined(CPU_MIMXRT1175AVM8A_cm4) || defined(CPU_MIMXRT1175AVM8B_cm4) || defined(CPU_MIMXRT1175CVM8A_cm4) || defined(CPU_MIMXRT1175CVM8B_cm4) || defined(CPU_MIMXRT1175DVMAA_cm4) || defined(CPU_MIMXRT1175DVMAB_cm4))
#include "MIMXRT1175_cm4_COMMON.h"
#elif (defined(CPU_MIMXRT1175AVM8A_cm7) || defined(CPU_MIMXRT1175AVM8B_cm7) || defined(CPU_MIMXRT1175CVM8A_cm7) || defined(CPU_MIMXRT1175CVM8B_cm7) || defined(CPU_MIMXRT1175DVMAA_cm7) || defined(CPU_MIMXRT1175DVMAB_cm7))
#include "MIMXRT1175_cm7_COMMON.h"
#elif (defined(CPU_MIMXRT1176AVM8A_cm4) || defined(CPU_MIMXRT1176AVM8B_cm4) || defined(CPU_MIMXRT1176CVM8A_cm4) || defined(CPU_MIMXRT1176CVM8B_cm4) || defined(CPU_MIMXRT1176DVMAA_cm4) || defined(CPU_MIMXRT1176DVMAB_cm4))
#include "MIMXRT1176_cm4_COMMON.h"
#elif (defined(CPU_MIMXRT1176AVM8A_cm7) || defined(CPU_MIMXRT1176AVM8B_cm7) || defined(CPU_MIMXRT1176CVM8A_cm7) || defined(CPU_MIMXRT1176CVM8B_cm7) || defined(CPU_MIMXRT1176DVMAA_cm7) || defined(CPU_MIMXRT1176DVMAB_cm7))
#include "MIMXRT1176_cm7_COMMON.h"
#elif (defined(CPU_MIMXRT117HAVM8A_cm4) || defined(CPU_MIMXRT117HAVM8B_cm4) || defined(CPU_MIMXRT117HCVM8A_cm4) || defined(CPU_MIMXRT117HCVM8B_cm4) || defined(CPU_MIMXRT117HDVMAA_cm4) || defined(CPU_MIMXRT117HDVMAB_cm4))
#include "MIMXRT117H_cm4_COMMON.h"
#elif (defined(CPU_MIMXRT117HAVM8A_cm7) || defined(CPU_MIMXRT117HAVM8B_cm7) || defined(CPU_MIMXRT117HCVM8A_cm7) || defined(CPU_MIMXRT117HCVM8B_cm7) || defined(CPU_MIMXRT117HDVMAA_cm7) || defined(CPU_MIMXRT117HDVMAB_cm7))
#include "MIMXRT117H_cm7_COMMON.h"
#else
  #error "No valid CPU defined!"
#endif

/* ----------------------------------------------------------------------------
   -- Device Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup Peripheral_access_layer Device Peripheral Access Layer
 * @{
 */


/*
** Start of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic push
  #else
    #pragma push
    #pragma anon_unions
  #endif
#elif defined(__CWCC__)
  #pragma push
  #pragma cpp_extensions on
#elif defined(__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=extended
#else
  #error Not supported compiler type
#endif

/* ----------------------------------------------------------------------------
   -- GPC_CPU_MODE_CTRL Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPC_CPU_MODE_CTRL_Peripheral_Access_Layer GPC_CPU_MODE_CTRL Peripheral Access Layer
 * @{
 */

/** GPC_CPU_MODE_CTRL - Size of Registers Arrays */
#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_COUNT 8u
#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_COUNT 8u
#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_COUNT     16u

/** GPC_CPU_MODE_CTRL - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[4];
  __IO uint32_t CM_AUTHEN_CTRL;                    /**< CM Authentication Control, offset: 0x4 */
  __IO uint32_t CM_INT_CTRL;                       /**< CM Interrupt Control, offset: 0x8 */
  __IO uint32_t CM_MISC;                           /**< Miscellaneous, offset: 0xC */
  __IO uint32_t CM_MODE_CTRL;                      /**< CPU mode control, offset: 0x10 */
  __I  uint32_t CM_MODE_STAT;                      /**< CM CPU mode Status, offset: 0x14 */
       uint8_t RESERVED_1[232];
  __IO uint32_t CM_IRQ_WAKEUP_MASK[GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_COUNT]; /**< CM IRQ0~31 wakeup mask..CM IRQ224~255 wakeup mask, array offset: 0x100, array step: 0x4 */
       uint8_t RESERVED_2[32];
  __IO uint32_t CM_NON_IRQ_WAKEUP_MASK;            /**< CM non-irq wakeup mask, offset: 0x140 */
       uint8_t RESERVED_3[12];
  __I  uint32_t CM_IRQ_WAKEUP_STAT[GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_COUNT]; /**< CM IRQ0~31 wakeup status..CM IRQ224~255 wakeup status, array offset: 0x150, array step: 0x4 */
       uint8_t RESERVED_4[32];
  __I  uint32_t CM_NON_IRQ_WAKEUP_STAT;            /**< CM non-irq wakeup status, offset: 0x190 */
       uint8_t RESERVED_5[108];
  __IO uint32_t CM_SLEEP_SSAR_CTRL;                /**< CM sleep SSAR control, offset: 0x200 */
       uint8_t RESERVED_6[4];
  __IO uint32_t CM_SLEEP_LPCG_CTRL;                /**< CM sleep LPCG control, offset: 0x208 */
       uint8_t RESERVED_7[4];
  __IO uint32_t CM_SLEEP_PLL_CTRL;                 /**< CM sleep PLL control, offset: 0x210 */
       uint8_t RESERVED_8[4];
  __IO uint32_t CM_SLEEP_ISO_CTRL;                 /**< CM sleep isolation control, offset: 0x218 */
       uint8_t RESERVED_9[4];
  __IO uint32_t CM_SLEEP_RESET_CTRL;               /**< CM sleep reset control, offset: 0x220 */
       uint8_t RESERVED_10[4];
  __IO uint32_t CM_SLEEP_POWER_CTRL;               /**< CM sleep power control, offset: 0x228 */
       uint8_t RESERVED_11[100];
  __IO uint32_t CM_WAKEUP_POWER_CTRL;              /**< CM wakeup power control, offset: 0x290 */
       uint8_t RESERVED_12[4];
  __IO uint32_t CM_WAKEUP_RESET_CTRL;              /**< CM wakeup reset control, offset: 0x298 */
       uint8_t RESERVED_13[4];
  __IO uint32_t CM_WAKEUP_ISO_CTRL;                /**< CM wakeup isolation control, offset: 0x2A0 */
       uint8_t RESERVED_14[4];
  __IO uint32_t CM_WAKEUP_PLL_CTRL;                /**< CM wakeup PLL control, offset: 0x2A8 */
       uint8_t RESERVED_15[4];
  __IO uint32_t CM_WAKEUP_LPCG_CTRL;               /**< CM wakeup LPCG control, offset: 0x2B0 */
       uint8_t RESERVED_16[4];
  __IO uint32_t CM_WAKEUP_SSAR_CTRL;               /**< CM wakeup SSAR control, offset: 0x2B8 */
       uint8_t RESERVED_17[68];
  __IO uint32_t CM_SP_CTRL;                        /**< CM Setpoint Control, offset: 0x300 */
  __I  uint32_t CM_SP_STAT;                        /**< CM Setpoint Status, offset: 0x304 */
       uint8_t RESERVED_18[8];
  __IO uint32_t CM_RUN_MODE_MAPPING;               /**< CM Run Mode Setpoint Allowed, offset: 0x310 */
  __IO uint32_t CM_WAIT_MODE_MAPPING;              /**< CM Wait Mode Setpoint Allowed, offset: 0x314 */
  __IO uint32_t CM_STOP_MODE_MAPPING;              /**< CM Stop Mode Setpoint Allowed, offset: 0x318 */
  __IO uint32_t CM_SUSPEND_MODE_MAPPING;           /**< CM Suspend Mode Setpoint Allowed, offset: 0x31C */
  __IO uint32_t CM_SP_MAPPING[GPC_CPU_MODE_CTRL_CM_SP_MAPPING_COUNT]; /**< CM Setpoint 0 Mapping..CM Setpoint 15 Mapping, array offset: 0x320, array step: 0x4 */
       uint8_t RESERVED_19[32];
  __IO uint32_t CM_STBY_CTRL;                      /**< CM standby control, offset: 0x380 */
} GPC_CPU_MODE_CTRL_Type;

/* ----------------------------------------------------------------------------
   -- GPC_CPU_MODE_CTRL Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPC_CPU_MODE_CTRL_Register_Masks GPC_CPU_MODE_CTRL Register Masks
 * @{
 */

/*! @name CM_AUTHEN_CTRL - CM Authentication Control */
/*! @{ */

#define GPC_CPU_MODE_CTRL_CM_AUTHEN_CTRL_USER_MASK (0x1U)
#define GPC_CPU_MODE_CTRL_CM_AUTHEN_CTRL_USER_SHIFT (0U)
/*! USER - Allow user mode access
 *  0b0..Allow only privilege mode to access CPU mode control registers
 *  0b1..Allow both privilege and user mode to access CPU mode control registers
 */
#define GPC_CPU_MODE_CTRL_CM_AUTHEN_CTRL_USER(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_AUTHEN_CTRL_USER_SHIFT)) & GPC_CPU_MODE_CTRL_CM_AUTHEN_CTRL_USER_MASK)

#define GPC_CPU_MODE_CTRL_CM_AUTHEN_CTRL_NONSECURE_MASK (0x2U)
#define GPC_CPU_MODE_CTRL_CM_AUTHEN_CTRL_NONSECURE_SHIFT (1U)
/*! NONSECURE - Allow non-secure mode access
 *  0b0..Allow only secure mode to access CPU mode control registers
 *  0b1..Allow both secure and non-secure mode to access CPU mode control registers
 */
#define GPC_CPU_MODE_CTRL_CM_AUTHEN_CTRL_NONSECURE(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_AUTHEN_CTRL_NONSECURE_SHIFT)) & GPC_CPU_MODE_CTRL_CM_AUTHEN_CTRL_NONSECURE_MASK)

#define GPC_CPU_MODE_CTRL_CM_AUTHEN_CTRL_LOCK_SETTING_MASK (0x10U)
#define GPC_CPU_MODE_CTRL_CM_AUTHEN_CTRL_LOCK_SETTING_SHIFT (4U)
/*! LOCK_SETTING - Lock NONSECURE and USER */
#define GPC_CPU_MODE_CTRL_CM_AUTHEN_CTRL_LOCK_SETTING(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_AUTHEN_CTRL_LOCK_SETTING_SHIFT)) & GPC_CPU_MODE_CTRL_CM_AUTHEN_CTRL_LOCK_SETTING_MASK)

#define GPC_CPU_MODE_CTRL_CM_AUTHEN_CTRL_WHITE_LIST_MASK (0xF00U)
#define GPC_CPU_MODE_CTRL_CM_AUTHEN_CTRL_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Domain ID white list */
#define GPC_CPU_MODE_CTRL_CM_AUTHEN_CTRL_WHITE_LIST(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_AUTHEN_CTRL_WHITE_LIST_SHIFT)) & GPC_CPU_MODE_CTRL_CM_AUTHEN_CTRL_WHITE_LIST_MASK)

#define GPC_CPU_MODE_CTRL_CM_AUTHEN_CTRL_LOCK_LIST_MASK (0x1000U)
#define GPC_CPU_MODE_CTRL_CM_AUTHEN_CTRL_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - White list lock */
#define GPC_CPU_MODE_CTRL_CM_AUTHEN_CTRL_LOCK_LIST(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_AUTHEN_CTRL_LOCK_LIST_SHIFT)) & GPC_CPU_MODE_CTRL_CM_AUTHEN_CTRL_LOCK_LIST_MASK)

#define GPC_CPU_MODE_CTRL_CM_AUTHEN_CTRL_LOCK_CFG_MASK (0x100000U)
#define GPC_CPU_MODE_CTRL_CM_AUTHEN_CTRL_LOCK_CFG_SHIFT (20U)
/*! LOCK_CFG - Configuration lock */
#define GPC_CPU_MODE_CTRL_CM_AUTHEN_CTRL_LOCK_CFG(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_AUTHEN_CTRL_LOCK_CFG_SHIFT)) & GPC_CPU_MODE_CTRL_CM_AUTHEN_CTRL_LOCK_CFG_MASK)
/*! @} */

/*! @name CM_INT_CTRL - CM Interrupt Control */
/*! @{ */

#define GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_SLEEP_INT_EN_MASK (0x1U)
#define GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_SLEEP_INT_EN_SHIFT (0U)
/*! SP_REQ_NOT_ALLOWED_SLEEP_INT_EN - sp_req_not_allowed_for_sleep interrupt enable
 *  0b0..Interrupt disable
 *  0b1..Interrupt enable
 */
#define GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_SLEEP_INT_EN(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_SLEEP_INT_EN_SHIFT)) & GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_SLEEP_INT_EN_MASK)

#define GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_WAKEUP_INT_EN_MASK (0x2U)
#define GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_WAKEUP_INT_EN_SHIFT (1U)
/*! SP_REQ_NOT_ALLOWED_WAKEUP_INT_EN - sp_req_not_allowed_for_wakeup interrupt enable
 *  0b0..Interrupt disable
 *  0b1..Interrupt enable
 */
#define GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_WAKEUP_INT_EN(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_WAKEUP_INT_EN_SHIFT)) & GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_WAKEUP_INT_EN_MASK)

#define GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_SOFT_INT_EN_MASK (0x4U)
#define GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_SOFT_INT_EN_SHIFT (2U)
/*! SP_REQ_NOT_ALLOWED_SOFT_INT_EN - sp_req_not_allowed_for_soft interrupt enable
 *  0b0..Interrupt disable
 *  0b1..Interrupt enable
 */
#define GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_SOFT_INT_EN(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_SOFT_INT_EN_SHIFT)) & GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_SOFT_INT_EN_MASK)

#define GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_SLEEP_INT_MASK (0x10000U)
#define GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_SLEEP_INT_SHIFT (16U)
/*! SP_REQ_NOT_ALLOWED_SLEEP_INT - sp_req_not_allowed_for_sleep interrupt status and clear register */
#define GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_SLEEP_INT(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_SLEEP_INT_SHIFT)) & GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_SLEEP_INT_MASK)

#define GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_WAKEUP_INT_MASK (0x20000U)
#define GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_WAKEUP_INT_SHIFT (17U)
/*! SP_REQ_NOT_ALLOWED_WAKEUP_INT - sp_req_not_allowed_for_wakeup interrupt status and clear register */
#define GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_WAKEUP_INT(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_WAKEUP_INT_SHIFT)) & GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_WAKEUP_INT_MASK)

#define GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_SOFT_INT_MASK (0x40000U)
#define GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_SOFT_INT_SHIFT (18U)
/*! SP_REQ_NOT_ALLOWED_SOFT_INT - sp_req_not_allowed_for_soft interrupt status and clear register */
#define GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_SOFT_INT(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_SOFT_INT_SHIFT)) & GPC_CPU_MODE_CTRL_CM_INT_CTRL_SP_REQ_NOT_ALLOWED_SOFT_INT_MASK)
/*! @} */

/*! @name CM_MISC - Miscellaneous */
/*! @{ */

#define GPC_CPU_MODE_CTRL_CM_MISC_NMI_STAT_MASK  (0x1U)
#define GPC_CPU_MODE_CTRL_CM_MISC_NMI_STAT_SHIFT (0U)
/*! NMI_STAT - Non-masked interrupt status
 *  0b0..NMI is not asserting
 *  0b1..NMI is asserting
 */
#define GPC_CPU_MODE_CTRL_CM_MISC_NMI_STAT(x)    (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_MISC_NMI_STAT_SHIFT)) & GPC_CPU_MODE_CTRL_CM_MISC_NMI_STAT_MASK)

#define GPC_CPU_MODE_CTRL_CM_MISC_SLEEP_HOLD_EN_MASK (0x2U)
#define GPC_CPU_MODE_CTRL_CM_MISC_SLEEP_HOLD_EN_SHIFT (1U)
/*! SLEEP_HOLD_EN - Allow cpu_sleep_hold_req assert during CPU low power status
 *  0b0..Disable cpu_sleep_hold_req
 *  0b1..Allow cpu_sleep_hold_req assert during CPU low power status
 */
#define GPC_CPU_MODE_CTRL_CM_MISC_SLEEP_HOLD_EN(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_MISC_SLEEP_HOLD_EN_SHIFT)) & GPC_CPU_MODE_CTRL_CM_MISC_SLEEP_HOLD_EN_MASK)

#define GPC_CPU_MODE_CTRL_CM_MISC_SLEEP_HOLD_STAT_MASK (0x4U)
#define GPC_CPU_MODE_CTRL_CM_MISC_SLEEP_HOLD_STAT_SHIFT (2U)
/*! SLEEP_HOLD_STAT - Status of cpu_sleep_hold_ack_b */
#define GPC_CPU_MODE_CTRL_CM_MISC_SLEEP_HOLD_STAT(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_MISC_SLEEP_HOLD_STAT_SHIFT)) & GPC_CPU_MODE_CTRL_CM_MISC_SLEEP_HOLD_STAT_MASK)

#define GPC_CPU_MODE_CTRL_CM_MISC_MASTER_CPU_MASK (0x10U)
#define GPC_CPU_MODE_CTRL_CM_MISC_MASTER_CPU_SHIFT (4U)
/*! MASTER_CPU - Master CPU */
#define GPC_CPU_MODE_CTRL_CM_MISC_MASTER_CPU(x)  (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_MISC_MASTER_CPU_SHIFT)) & GPC_CPU_MODE_CTRL_CM_MISC_MASTER_CPU_MASK)
/*! @} */

/*! @name CM_MODE_CTRL - CPU mode control */
/*! @{ */

#define GPC_CPU_MODE_CTRL_CM_MODE_CTRL_CPU_MODE_TARGET_MASK (0x3U)
#define GPC_CPU_MODE_CTRL_CM_MODE_CTRL_CPU_MODE_TARGET_SHIFT (0U)
/*! CPU_MODE_TARGET - The CPU mode the CPU platform should transit to on next sleep event
 *  0b00..Stay in RUN mode
 *  0b01..Transit to WAIT mode
 *  0b10..Transit to STOP mode
 *  0b11..Transit to SUSPEND mode
 */
#define GPC_CPU_MODE_CTRL_CM_MODE_CTRL_CPU_MODE_TARGET(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_MODE_CTRL_CPU_MODE_TARGET_SHIFT)) & GPC_CPU_MODE_CTRL_CM_MODE_CTRL_CPU_MODE_TARGET_MASK)

#define GPC_CPU_MODE_CTRL_CM_MODE_CTRL_WFE_EN_MASK (0x10U)
#define GPC_CPU_MODE_CTRL_CM_MODE_CTRL_WFE_EN_SHIFT (4U)
/*! WFE_EN - WFE assertion can be sleep event
 *  0b0..WFE assertion can not trigger low power
 *  0b1..WFE assertion can trigger low power
 */
#define GPC_CPU_MODE_CTRL_CM_MODE_CTRL_WFE_EN(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_MODE_CTRL_WFE_EN_SHIFT)) & GPC_CPU_MODE_CTRL_CM_MODE_CTRL_WFE_EN_MASK)
/*! @} */

/*! @name CM_MODE_STAT - CM CPU mode Status */
/*! @{ */

#define GPC_CPU_MODE_CTRL_CM_MODE_STAT_CPU_MODE_CURRENT_MASK (0x3U)
#define GPC_CPU_MODE_CTRL_CM_MODE_STAT_CPU_MODE_CURRENT_SHIFT (0U)
/*! CPU_MODE_CURRENT - Current CPU mode
 *  0b00..CPU is currently in RUN mode
 *  0b01..CPU is currently in WAIT mode
 *  0b10..CPU is currently in STOP mode
 *  0b11..CPU is currently in SUSPEND mode
 */
#define GPC_CPU_MODE_CTRL_CM_MODE_STAT_CPU_MODE_CURRENT(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_MODE_STAT_CPU_MODE_CURRENT_SHIFT)) & GPC_CPU_MODE_CTRL_CM_MODE_STAT_CPU_MODE_CURRENT_MASK)

#define GPC_CPU_MODE_CTRL_CM_MODE_STAT_CPU_MODE_PREVIOUS_MASK (0xCU)
#define GPC_CPU_MODE_CTRL_CM_MODE_STAT_CPU_MODE_PREVIOUS_SHIFT (2U)
/*! CPU_MODE_PREVIOUS - Previous CPU mode
 *  0b00..CPU was previously in RUN mode
 *  0b01..CPU was previously in WAIT mode
 *  0b10..CPU was previously in STOP mode
 *  0b11..CPU was previously in SUSPEND mode
 */
#define GPC_CPU_MODE_CTRL_CM_MODE_STAT_CPU_MODE_PREVIOUS(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_MODE_STAT_CPU_MODE_PREVIOUS_SHIFT)) & GPC_CPU_MODE_CTRL_CM_MODE_STAT_CPU_MODE_PREVIOUS_MASK)
/*! @} */

/*! @name CM_IRQ_WAKEUP_MASK - CM IRQ0~31 wakeup mask..CM IRQ224~255 wakeup mask */
/*! @{ */

#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_0_31_MASK (0xFFFFFFFFU)
#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_0_31_SHIFT (0U)
/*! IRQ_WAKEUP_MASK_0_31 - "1" means the IRQ cannot wakeup CPU platform */
#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_0_31(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_0_31_SHIFT)) & GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_0_31_MASK)

#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_32_63_MASK (0xFFFFFFFFU)
#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_32_63_SHIFT (0U)
/*! IRQ_WAKEUP_MASK_32_63 - "1" means the IRQ cannot wakeup CPU platform */
#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_32_63(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_32_63_SHIFT)) & GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_32_63_MASK)

#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_64_95_MASK (0xFFFFFFFFU)
#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_64_95_SHIFT (0U)
/*! IRQ_WAKEUP_MASK_64_95 - "1" means the IRQ cannot wakeup CPU platform */
#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_64_95(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_64_95_SHIFT)) & GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_64_95_MASK)

#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_96_127_MASK (0xFFFFFFFFU)
#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_96_127_SHIFT (0U)
/*! IRQ_WAKEUP_MASK_96_127 - "1" means the IRQ cannot wakeup CPU platform */
#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_96_127(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_96_127_SHIFT)) & GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_96_127_MASK)

#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_128_159_MASK (0xFFFFFFFFU)
#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_128_159_SHIFT (0U)
/*! IRQ_WAKEUP_MASK_128_159 - "1" means the IRQ cannot wakeup CPU platform */
#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_128_159(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_128_159_SHIFT)) & GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_128_159_MASK)

#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_160_191_MASK (0xFFFFFFFFU)
#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_160_191_SHIFT (0U)
/*! IRQ_WAKEUP_MASK_160_191 - "1" means the IRQ cannot wakeup CPU platform */
#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_160_191(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_160_191_SHIFT)) & GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_160_191_MASK)

#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_192_223_MASK (0xFFFFFFFFU)
#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_192_223_SHIFT (0U)
/*! IRQ_WAKEUP_MASK_192_223 - "1" means the IRQ cannot wakeup CPU platform */
#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_192_223(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_192_223_SHIFT)) & GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_192_223_MASK)

#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_224_255_MASK (0xFFFFFFFFU)
#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_224_255_SHIFT (0U)
/*! IRQ_WAKEUP_MASK_224_255 - "1" means the IRQ cannot wakeup CPU platform */
#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_224_255(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_224_255_SHIFT)) & GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_MASK_IRQ_WAKEUP_MASK_224_255_MASK)
/*! @} */

/*! @name CM_NON_IRQ_WAKEUP_MASK - CM non-irq wakeup mask */
/*! @{ */

#define GPC_CPU_MODE_CTRL_CM_NON_IRQ_WAKEUP_MASK_EVENT_WAKEUP_MASK_MASK (0x1U)
#define GPC_CPU_MODE_CTRL_CM_NON_IRQ_WAKEUP_MASK_EVENT_WAKEUP_MASK_SHIFT (0U)
/*! EVENT_WAKEUP_MASK - There are 256 interrupts and 1 event as a wakeup source for GPC. This field masks the 1 event wakeup source.
 *  0b1..The event cannot wakeup CPU platform
 */
#define GPC_CPU_MODE_CTRL_CM_NON_IRQ_WAKEUP_MASK_EVENT_WAKEUP_MASK(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_NON_IRQ_WAKEUP_MASK_EVENT_WAKEUP_MASK_SHIFT)) & GPC_CPU_MODE_CTRL_CM_NON_IRQ_WAKEUP_MASK_EVENT_WAKEUP_MASK_MASK)

#define GPC_CPU_MODE_CTRL_CM_NON_IRQ_WAKEUP_MASK_DEBUG_WAKEUP_MASK_MASK (0x2U)
#define GPC_CPU_MODE_CTRL_CM_NON_IRQ_WAKEUP_MASK_DEBUG_WAKEUP_MASK_SHIFT (1U)
/*! DEBUG_WAKEUP_MASK - "1" means the debug_wakeup_request cannot wakeup CPU platform */
#define GPC_CPU_MODE_CTRL_CM_NON_IRQ_WAKEUP_MASK_DEBUG_WAKEUP_MASK(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_NON_IRQ_WAKEUP_MASK_DEBUG_WAKEUP_MASK_SHIFT)) & GPC_CPU_MODE_CTRL_CM_NON_IRQ_WAKEUP_MASK_DEBUG_WAKEUP_MASK_MASK)
/*! @} */

/*! @name CM_IRQ_WAKEUP_STAT - CM IRQ0~31 wakeup status..CM IRQ224~255 wakeup status */
/*! @{ */

#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_MASK_224_255_MASK (0xFFFFFFFFU)
#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_MASK_224_255_SHIFT (0U)
/*! IRQ_WAKEUP_MASK_224_255 - IRQ status
 *  0b00000000000000000000000000000000..None
 *  0b00000000000000000000000000000001..Valid
 */
#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_MASK_224_255(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_MASK_224_255_SHIFT)) & GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_MASK_224_255_MASK)

#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_STAT_0_31_MASK (0xFFFFFFFFU)
#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_STAT_0_31_SHIFT (0U)
/*! IRQ_WAKEUP_STAT_0_31 - IRQ status
 *  0b00000000000000000000000000000000..None
 *  0b00000000000000000000000000000001..Valid
 */
#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_STAT_0_31(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_STAT_0_31_SHIFT)) & GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_STAT_0_31_MASK)

#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_STAT_32_63_MASK (0xFFFFFFFFU)
#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_STAT_32_63_SHIFT (0U)
/*! IRQ_WAKEUP_STAT_32_63 - IRQ status
 *  0b00000000000000000000000000000000..None
 *  0b00000000000000000000000000000001..Valid
 */
#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_STAT_32_63(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_STAT_32_63_SHIFT)) & GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_STAT_32_63_MASK)

#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_STAT_64_95_MASK (0xFFFFFFFFU)
#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_STAT_64_95_SHIFT (0U)
/*! IRQ_WAKEUP_STAT_64_95 - IRQ status
 *  0b00000000000000000000000000000000..None
 *  0b00000000000000000000000000000001..Valid
 */
#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_STAT_64_95(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_STAT_64_95_SHIFT)) & GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_STAT_64_95_MASK)

#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_STAT_96_127_MASK (0xFFFFFFFFU)
#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_STAT_96_127_SHIFT (0U)
/*! IRQ_WAKEUP_STAT_96_127 - IRQ status
 *  0b00000000000000000000000000000000..None
 *  0b00000000000000000000000000000001..Valid
 */
#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_STAT_96_127(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_STAT_96_127_SHIFT)) & GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_STAT_96_127_MASK)

#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_STAT_128_159_MASK (0xFFFFFFFFU)
#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_STAT_128_159_SHIFT (0U)
/*! IRQ_WAKEUP_STAT_128_159 - IRQ status
 *  0b00000000000000000000000000000000..None
 *  0b00000000000000000000000000000001..Valid
 */
#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_STAT_128_159(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_STAT_128_159_SHIFT)) & GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_STAT_128_159_MASK)

#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_STAT_160_191_MASK (0xFFFFFFFFU)
#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_STAT_160_191_SHIFT (0U)
/*! IRQ_WAKEUP_STAT_160_191 - IRQ status
 *  0b00000000000000000000000000000000..None
 *  0b00000000000000000000000000000001..Valid
 */
#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_STAT_160_191(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_STAT_160_191_SHIFT)) & GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_STAT_160_191_MASK)

#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_STAT_192_223_MASK (0xFFFFFFFFU)
#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_STAT_192_223_SHIFT (0U)
/*! IRQ_WAKEUP_STAT_192_223 - IRQ status
 *  0b00000000000000000000000000000000..None
 *  0b00000000000000000000000000000001..Valid
 */
#define GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_STAT_192_223(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_STAT_192_223_SHIFT)) & GPC_CPU_MODE_CTRL_CM_IRQ_WAKEUP_STAT_IRQ_WAKEUP_STAT_192_223_MASK)
/*! @} */

/*! @name CM_NON_IRQ_WAKEUP_STAT - CM non-irq wakeup status */
/*! @{ */

#define GPC_CPU_MODE_CTRL_CM_NON_IRQ_WAKEUP_STAT_EVENT_WAKEUP_STAT_MASK (0x1U)
#define GPC_CPU_MODE_CTRL_CM_NON_IRQ_WAKEUP_STAT_EVENT_WAKEUP_STAT_SHIFT (0U)
/*! EVENT_WAKEUP_STAT - Event wakeup status
 *  0b1..Interrupt is asserting (pending)
 */
#define GPC_CPU_MODE_CTRL_CM_NON_IRQ_WAKEUP_STAT_EVENT_WAKEUP_STAT(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_NON_IRQ_WAKEUP_STAT_EVENT_WAKEUP_STAT_SHIFT)) & GPC_CPU_MODE_CTRL_CM_NON_IRQ_WAKEUP_STAT_EVENT_WAKEUP_STAT_MASK)

#define GPC_CPU_MODE_CTRL_CM_NON_IRQ_WAKEUP_STAT_DEBUG_WAKEUP_STAT_MASK (0x2U)
#define GPC_CPU_MODE_CTRL_CM_NON_IRQ_WAKEUP_STAT_DEBUG_WAKEUP_STAT_SHIFT (1U)
/*! DEBUG_WAKEUP_STAT - Debug wakeup status */
#define GPC_CPU_MODE_CTRL_CM_NON_IRQ_WAKEUP_STAT_DEBUG_WAKEUP_STAT(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_NON_IRQ_WAKEUP_STAT_DEBUG_WAKEUP_STAT_SHIFT)) & GPC_CPU_MODE_CTRL_CM_NON_IRQ_WAKEUP_STAT_DEBUG_WAKEUP_STAT_MASK)
/*! @} */

/*! @name CM_SLEEP_SSAR_CTRL - CM sleep SSAR control */
/*! @{ */

#define GPC_CPU_MODE_CTRL_CM_SLEEP_SSAR_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_CPU_MODE_CTRL_CM_SLEEP_SSAR_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_CPU_MODE_CTRL_CM_SLEEP_SSAR_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_SLEEP_SSAR_CTRL_DISABLE_SHIFT)) & GPC_CPU_MODE_CTRL_CM_SLEEP_SSAR_CTRL_DISABLE_MASK)
/*! @} */

/*! @name CM_SLEEP_LPCG_CTRL - CM sleep LPCG control */
/*! @{ */

#define GPC_CPU_MODE_CTRL_CM_SLEEP_LPCG_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_CPU_MODE_CTRL_CM_SLEEP_LPCG_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_CPU_MODE_CTRL_CM_SLEEP_LPCG_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_SLEEP_LPCG_CTRL_DISABLE_SHIFT)) & GPC_CPU_MODE_CTRL_CM_SLEEP_LPCG_CTRL_DISABLE_MASK)
/*! @} */

/*! @name CM_SLEEP_PLL_CTRL - CM sleep PLL control */
/*! @{ */

#define GPC_CPU_MODE_CTRL_CM_SLEEP_PLL_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_CPU_MODE_CTRL_CM_SLEEP_PLL_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_CPU_MODE_CTRL_CM_SLEEP_PLL_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_SLEEP_PLL_CTRL_DISABLE_SHIFT)) & GPC_CPU_MODE_CTRL_CM_SLEEP_PLL_CTRL_DISABLE_MASK)
/*! @} */

/*! @name CM_SLEEP_ISO_CTRL - CM sleep isolation control */
/*! @{ */

#define GPC_CPU_MODE_CTRL_CM_SLEEP_ISO_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_CPU_MODE_CTRL_CM_SLEEP_ISO_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_CPU_MODE_CTRL_CM_SLEEP_ISO_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_SLEEP_ISO_CTRL_DISABLE_SHIFT)) & GPC_CPU_MODE_CTRL_CM_SLEEP_ISO_CTRL_DISABLE_MASK)
/*! @} */

/*! @name CM_SLEEP_RESET_CTRL - CM sleep reset control */
/*! @{ */

#define GPC_CPU_MODE_CTRL_CM_SLEEP_RESET_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_CPU_MODE_CTRL_CM_SLEEP_RESET_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_CPU_MODE_CTRL_CM_SLEEP_RESET_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_SLEEP_RESET_CTRL_DISABLE_SHIFT)) & GPC_CPU_MODE_CTRL_CM_SLEEP_RESET_CTRL_DISABLE_MASK)
/*! @} */

/*! @name CM_SLEEP_POWER_CTRL - CM sleep power control */
/*! @{ */

#define GPC_CPU_MODE_CTRL_CM_SLEEP_POWER_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_CPU_MODE_CTRL_CM_SLEEP_POWER_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_CPU_MODE_CTRL_CM_SLEEP_POWER_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_SLEEP_POWER_CTRL_DISABLE_SHIFT)) & GPC_CPU_MODE_CTRL_CM_SLEEP_POWER_CTRL_DISABLE_MASK)
/*! @} */

/*! @name CM_WAKEUP_POWER_CTRL - CM wakeup power control */
/*! @{ */

#define GPC_CPU_MODE_CTRL_CM_WAKEUP_POWER_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_CPU_MODE_CTRL_CM_WAKEUP_POWER_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_CPU_MODE_CTRL_CM_WAKEUP_POWER_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_WAKEUP_POWER_CTRL_DISABLE_SHIFT)) & GPC_CPU_MODE_CTRL_CM_WAKEUP_POWER_CTRL_DISABLE_MASK)
/*! @} */

/*! @name CM_WAKEUP_RESET_CTRL - CM wakeup reset control */
/*! @{ */

#define GPC_CPU_MODE_CTRL_CM_WAKEUP_RESET_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_CPU_MODE_CTRL_CM_WAKEUP_RESET_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_CPU_MODE_CTRL_CM_WAKEUP_RESET_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_WAKEUP_RESET_CTRL_DISABLE_SHIFT)) & GPC_CPU_MODE_CTRL_CM_WAKEUP_RESET_CTRL_DISABLE_MASK)
/*! @} */

/*! @name CM_WAKEUP_ISO_CTRL - CM wakeup isolation control */
/*! @{ */

#define GPC_CPU_MODE_CTRL_CM_WAKEUP_ISO_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_CPU_MODE_CTRL_CM_WAKEUP_ISO_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_CPU_MODE_CTRL_CM_WAKEUP_ISO_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_WAKEUP_ISO_CTRL_DISABLE_SHIFT)) & GPC_CPU_MODE_CTRL_CM_WAKEUP_ISO_CTRL_DISABLE_MASK)
/*! @} */

/*! @name CM_WAKEUP_PLL_CTRL - CM wakeup PLL control */
/*! @{ */

#define GPC_CPU_MODE_CTRL_CM_WAKEUP_PLL_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_CPU_MODE_CTRL_CM_WAKEUP_PLL_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_CPU_MODE_CTRL_CM_WAKEUP_PLL_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_WAKEUP_PLL_CTRL_DISABLE_SHIFT)) & GPC_CPU_MODE_CTRL_CM_WAKEUP_PLL_CTRL_DISABLE_MASK)
/*! @} */

/*! @name CM_WAKEUP_LPCG_CTRL - CM wakeup LPCG control */
/*! @{ */

#define GPC_CPU_MODE_CTRL_CM_WAKEUP_LPCG_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_CPU_MODE_CTRL_CM_WAKEUP_LPCG_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_CPU_MODE_CTRL_CM_WAKEUP_LPCG_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_WAKEUP_LPCG_CTRL_DISABLE_SHIFT)) & GPC_CPU_MODE_CTRL_CM_WAKEUP_LPCG_CTRL_DISABLE_MASK)
/*! @} */

/*! @name CM_WAKEUP_SSAR_CTRL - CM wakeup SSAR control */
/*! @{ */

#define GPC_CPU_MODE_CTRL_CM_WAKEUP_SSAR_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_CPU_MODE_CTRL_CM_WAKEUP_SSAR_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_CPU_MODE_CTRL_CM_WAKEUP_SSAR_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_WAKEUP_SSAR_CTRL_DISABLE_SHIFT)) & GPC_CPU_MODE_CTRL_CM_WAKEUP_SSAR_CTRL_DISABLE_MASK)
/*! @} */

/*! @name CM_SP_CTRL - CM Setpoint Control */
/*! @{ */

#define GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_RUN_EN_MASK (0x1U)
#define GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_RUN_EN_SHIFT (0U)
/*! CPU_SP_RUN_EN - Request a Setpoint transition when this bit is set */
#define GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_RUN_EN(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_RUN_EN_SHIFT)) & GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_RUN_EN_MASK)

#define GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_RUN_MASK (0x1EU)
#define GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_RUN_SHIFT (1U)
/*! CPU_SP_RUN - The Setpoint that CPU want the system to transit to when CPU_SP_RUN_EN is set */
#define GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_RUN(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_RUN_SHIFT)) & GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_RUN_MASK)

#define GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_SLEEP_EN_MASK (0x20U)
#define GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_SLEEP_EN_SHIFT (5U)
/*! CPU_SP_SLEEP_EN - 1 means enable Setpoint transition on next CPU platform sleep sequence */
#define GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_SLEEP_EN(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_SLEEP_EN_SHIFT)) & GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_SLEEP_EN_MASK)

#define GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_SLEEP_MASK (0x3C0U)
#define GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_SLEEP_SHIFT (6U)
/*! CPU_SP_SLEEP - The Setpoint that CPU want the system to transit to on next CPU platform sleep sequence */
#define GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_SLEEP(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_SLEEP_SHIFT)) & GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_SLEEP_MASK)

#define GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_WAKEUP_EN_MASK (0x400U)
#define GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_WAKEUP_EN_SHIFT (10U)
/*! CPU_SP_WAKEUP_EN - 1 means enable Setpoint transition on next CPU platform wakeup sequence */
#define GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_WAKEUP_EN(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_WAKEUP_EN_SHIFT)) & GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_WAKEUP_EN_MASK)

#define GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_WAKEUP_MASK (0x7800U)
#define GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_WAKEUP_SHIFT (11U)
/*! CPU_SP_WAKEUP - The Setpoint that CPU want the system to transit to on next CPU platform wakeup sequence */
#define GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_WAKEUP(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_WAKEUP_SHIFT)) & GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_WAKEUP_MASK)

#define GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_WAKEUP_SEL_MASK (0x8000U)
#define GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_WAKEUP_SEL_SHIFT (15U)
/*! CPU_SP_WAKEUP_SEL - Select the Setpoint transiton on the next CPU platform wakeup sequence
 *  0b0..Request SP transition to CPU_SP_WAKEUP
 *  0b1..Request SP transition to the Setpoint when the sleep event happens, which is captured in CPU_SP_PREVIOUS
 */
#define GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_WAKEUP_SEL(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_WAKEUP_SEL_SHIFT)) & GPC_CPU_MODE_CTRL_CM_SP_CTRL_CPU_SP_WAKEUP_SEL_MASK)
/*! @} */

/*! @name CM_SP_STAT - CM Setpoint Status */
/*! @{ */

#define GPC_CPU_MODE_CTRL_CM_SP_STAT_CPU_SP_CURRENT_MASK (0xFU)
#define GPC_CPU_MODE_CTRL_CM_SP_STAT_CPU_SP_CURRENT_SHIFT (0U)
/*! CPU_SP_CURRENT - The current Setpoint of the system */
#define GPC_CPU_MODE_CTRL_CM_SP_STAT_CPU_SP_CURRENT(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_SP_STAT_CPU_SP_CURRENT_SHIFT)) & GPC_CPU_MODE_CTRL_CM_SP_STAT_CPU_SP_CURRENT_MASK)

#define GPC_CPU_MODE_CTRL_CM_SP_STAT_CPU_SP_PREVIOUS_MASK (0xF0U)
#define GPC_CPU_MODE_CTRL_CM_SP_STAT_CPU_SP_PREVIOUS_SHIFT (4U)
/*! CPU_SP_PREVIOUS - The previous Setpoint of the system */
#define GPC_CPU_MODE_CTRL_CM_SP_STAT_CPU_SP_PREVIOUS(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_SP_STAT_CPU_SP_PREVIOUS_SHIFT)) & GPC_CPU_MODE_CTRL_CM_SP_STAT_CPU_SP_PREVIOUS_MASK)

#define GPC_CPU_MODE_CTRL_CM_SP_STAT_CPU_SP_TARGET_MASK (0xF00U)
#define GPC_CPU_MODE_CTRL_CM_SP_STAT_CPU_SP_TARGET_SHIFT (8U)
/*! CPU_SP_TARGET - The requested Setpoint from the CPU platform */
#define GPC_CPU_MODE_CTRL_CM_SP_STAT_CPU_SP_TARGET(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_SP_STAT_CPU_SP_TARGET_SHIFT)) & GPC_CPU_MODE_CTRL_CM_SP_STAT_CPU_SP_TARGET_MASK)
/*! @} */

/*! @name CM_RUN_MODE_MAPPING - CM Run Mode Setpoint Allowed */
/*! @{ */

#define GPC_CPU_MODE_CTRL_CM_RUN_MODE_MAPPING_CPU_RUN_MODE_MAPPING_MASK (0xFFFFU)
#define GPC_CPU_MODE_CTRL_CM_RUN_MODE_MAPPING_CPU_RUN_MODE_MAPPING_SHIFT (0U)
/*! CPU_RUN_MODE_MAPPING - Defines which Setpoint is allowed when CPU enters RUN mode. Each bit stands for 1 Setpoint, locked by LOCK_CFG field */
#define GPC_CPU_MODE_CTRL_CM_RUN_MODE_MAPPING_CPU_RUN_MODE_MAPPING(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_RUN_MODE_MAPPING_CPU_RUN_MODE_MAPPING_SHIFT)) & GPC_CPU_MODE_CTRL_CM_RUN_MODE_MAPPING_CPU_RUN_MODE_MAPPING_MASK)
/*! @} */

/*! @name CM_WAIT_MODE_MAPPING - CM Wait Mode Setpoint Allowed */
/*! @{ */

#define GPC_CPU_MODE_CTRL_CM_WAIT_MODE_MAPPING_CPU_WAIT_MODE_MAPPING_MASK (0xFFFFU)
#define GPC_CPU_MODE_CTRL_CM_WAIT_MODE_MAPPING_CPU_WAIT_MODE_MAPPING_SHIFT (0U)
/*! CPU_WAIT_MODE_MAPPING - Defines which Setpoint is allowed when CPU enters WAIT mode. Each bit stands for 1 Setpoint, locked by LOCK_CFG */
#define GPC_CPU_MODE_CTRL_CM_WAIT_MODE_MAPPING_CPU_WAIT_MODE_MAPPING(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_WAIT_MODE_MAPPING_CPU_WAIT_MODE_MAPPING_SHIFT)) & GPC_CPU_MODE_CTRL_CM_WAIT_MODE_MAPPING_CPU_WAIT_MODE_MAPPING_MASK)
/*! @} */

/*! @name CM_STOP_MODE_MAPPING - CM Stop Mode Setpoint Allowed */
/*! @{ */

#define GPC_CPU_MODE_CTRL_CM_STOP_MODE_MAPPING_CPU_STOP_MODE_MAPPING_MASK (0xFFFFU)
#define GPC_CPU_MODE_CTRL_CM_STOP_MODE_MAPPING_CPU_STOP_MODE_MAPPING_SHIFT (0U)
/*! CPU_STOP_MODE_MAPPING - Defines which Setpoint is allowed when CPU enters STOP mode. Each bit stands for 1 Setpoint, locked by LOCK_CFG */
#define GPC_CPU_MODE_CTRL_CM_STOP_MODE_MAPPING_CPU_STOP_MODE_MAPPING(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_STOP_MODE_MAPPING_CPU_STOP_MODE_MAPPING_SHIFT)) & GPC_CPU_MODE_CTRL_CM_STOP_MODE_MAPPING_CPU_STOP_MODE_MAPPING_MASK)
/*! @} */

/*! @name CM_SUSPEND_MODE_MAPPING - CM Suspend Mode Setpoint Allowed */
/*! @{ */

#define GPC_CPU_MODE_CTRL_CM_SUSPEND_MODE_MAPPING_CPU_SUSPEND_MODE_MAPPING_MASK (0xFFFFU)
#define GPC_CPU_MODE_CTRL_CM_SUSPEND_MODE_MAPPING_CPU_SUSPEND_MODE_MAPPING_SHIFT (0U)
/*! CPU_SUSPEND_MODE_MAPPING - Defines which Setpoint is allowed when CPU enters SUSPEND mode. Each bit stands for 1 Setpoint, locked by LOCK_CFG */
#define GPC_CPU_MODE_CTRL_CM_SUSPEND_MODE_MAPPING_CPU_SUSPEND_MODE_MAPPING(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_SUSPEND_MODE_MAPPING_CPU_SUSPEND_MODE_MAPPING_SHIFT)) & GPC_CPU_MODE_CTRL_CM_SUSPEND_MODE_MAPPING_CPU_SUSPEND_MODE_MAPPING_MASK)
/*! @} */

/*! @name CM_SP_MAPPING - CM Setpoint 0 Mapping..CM Setpoint 15 Mapping */
/*! @{ */

#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP0_MAPPING_MASK (0xFFFFU)
#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP0_MAPPING_SHIFT (0U)
/*! CPU_SP0_MAPPING - Defines when SP0 is set as the CPU_SP_TARGET, which SP is allowed, locked by LOCK_CFG field */
#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP0_MAPPING(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP0_MAPPING_SHIFT)) & GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP0_MAPPING_MASK)

#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP1_MAPPING_MASK (0xFFFFU)
#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP1_MAPPING_SHIFT (0U)
/*! CPU_SP1_MAPPING - Defines when SP1 is set as the CPU_SP_TARGET, which SP is allowed, locked by LOCK_CFG field */
#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP1_MAPPING(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP1_MAPPING_SHIFT)) & GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP1_MAPPING_MASK)

#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP2_MAPPING_MASK (0xFFFFU)
#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP2_MAPPING_SHIFT (0U)
/*! CPU_SP2_MAPPING - Defines when SP2 is set as the CPU_SP_TARGET, which SP is allowed, locked by LOCK_CFG field */
#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP2_MAPPING(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP2_MAPPING_SHIFT)) & GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP2_MAPPING_MASK)

#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP3_MAPPING_MASK (0xFFFFU)
#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP3_MAPPING_SHIFT (0U)
/*! CPU_SP3_MAPPING - Defines when SP3 is set as the CPU_SP_TARGET, which SP is allowed, locked by LOCK_CFG field */
#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP3_MAPPING(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP3_MAPPING_SHIFT)) & GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP3_MAPPING_MASK)

#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP4_MAPPING_MASK (0xFFFFU)
#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP4_MAPPING_SHIFT (0U)
/*! CPU_SP4_MAPPING - Defines when SP4 is set as the CPU_SP_TARGET, which SP is allowed, locked by LOCK_CFG field */
#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP4_MAPPING(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP4_MAPPING_SHIFT)) & GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP4_MAPPING_MASK)

#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP5_MAPPING_MASK (0xFFFFU)
#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP5_MAPPING_SHIFT (0U)
/*! CPU_SP5_MAPPING - Defines when SP5 is set as the CPU_SP_TARGET, which SP is allowed, locked by LOCK_CFG field */
#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP5_MAPPING(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP5_MAPPING_SHIFT)) & GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP5_MAPPING_MASK)

#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP6_MAPPING_MASK (0xFFFFU)
#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP6_MAPPING_SHIFT (0U)
/*! CPU_SP6_MAPPING - Defines when SP6 is set as the CPU_SP_TARGET, which SP is allowed, locked by LOCK_CFG field */
#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP6_MAPPING(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP6_MAPPING_SHIFT)) & GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP6_MAPPING_MASK)

#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP7_MAPPING_MASK (0xFFFFU)
#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP7_MAPPING_SHIFT (0U)
/*! CPU_SP7_MAPPING - Defines when SP7 is set as the CPU_SP_TARGET, which SP is allowed, locked by LOCK_CFG field */
#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP7_MAPPING(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP7_MAPPING_SHIFT)) & GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP7_MAPPING_MASK)

#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP8_MAPPING_MASK (0xFFFFU)
#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP8_MAPPING_SHIFT (0U)
/*! CPU_SP8_MAPPING - Defines when SP8 is set as the CPU_SP_TARGET, which SP is allowed, locked by LOCK_CFG field */
#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP8_MAPPING(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP8_MAPPING_SHIFT)) & GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP8_MAPPING_MASK)

#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP9_MAPPING_MASK (0xFFFFU)
#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP9_MAPPING_SHIFT (0U)
/*! CPU_SP9_MAPPING - Defines when SP9 is set as the CPU_SP_TARGET, which SP is allowed, locked by LOCK_CFG field */
#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP9_MAPPING(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP9_MAPPING_SHIFT)) & GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP9_MAPPING_MASK)

#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP10_MAPPING_MASK (0xFFFFU)
#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP10_MAPPING_SHIFT (0U)
/*! CPU_SP10_MAPPING - Defines when SP10 is set as the CPU_SP_TARGET, which SP is allowed, locked by LOCK_CFG field */
#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP10_MAPPING(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP10_MAPPING_SHIFT)) & GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP10_MAPPING_MASK)

#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP11_MAPPING_MASK (0xFFFFU)
#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP11_MAPPING_SHIFT (0U)
/*! CPU_SP11_MAPPING - Defines when SP11 is set as the CPU_SP_TARGET, which SP is allowed, locked by LOCK_CFG field */
#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP11_MAPPING(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP11_MAPPING_SHIFT)) & GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP11_MAPPING_MASK)

#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP12_MAPPING_MASK (0xFFFFU)
#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP12_MAPPING_SHIFT (0U)
/*! CPU_SP12_MAPPING - Defines when SP12 is set as the CPU_SP_TARGET, which SP is allowed, locked by LOCK_CFG field */
#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP12_MAPPING(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP12_MAPPING_SHIFT)) & GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP12_MAPPING_MASK)

#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP13_MAPPING_MASK (0xFFFFU)
#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP13_MAPPING_SHIFT (0U)
/*! CPU_SP13_MAPPING - Defines when SP13 is set as the CPU_SP_TARGET, which SP is allowed, locked by LOCK_CFG field */
#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP13_MAPPING(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP13_MAPPING_SHIFT)) & GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP13_MAPPING_MASK)

#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP14_MAPPING_MASK (0xFFFFU)
#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP14_MAPPING_SHIFT (0U)
/*! CPU_SP14_MAPPING - Defines when SP14 is set as the CPU_SP_TARGET, which SP is allowed, locked by LOCK_CFG field */
#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP14_MAPPING(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP14_MAPPING_SHIFT)) & GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP14_MAPPING_MASK)

#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP15_MAPPING_MASK (0xFFFFU)
#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP15_MAPPING_SHIFT (0U)
/*! CPU_SP15_MAPPING - Defines when SP15 is set as the CPU_SP_TARGET, which SP is allowed, locked by LOCK_CFG field */
#define GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP15_MAPPING(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP15_MAPPING_SHIFT)) & GPC_CPU_MODE_CTRL_CM_SP_MAPPING_CPU_SP15_MAPPING_MASK)
/*! @} */

/*! @name CM_STBY_CTRL - CM standby control */
/*! @{ */

#define GPC_CPU_MODE_CTRL_CM_STBY_CTRL_STBY_WAIT_MASK (0x1U)
#define GPC_CPU_MODE_CTRL_CM_STBY_CTRL_STBY_WAIT_SHIFT (0U)
/*! STBY_WAIT - 0x1: Request the chip into standby mode when CPU entering WAIT mode, locked by LOCK_CFG field. */
#define GPC_CPU_MODE_CTRL_CM_STBY_CTRL_STBY_WAIT(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_STBY_CTRL_STBY_WAIT_SHIFT)) & GPC_CPU_MODE_CTRL_CM_STBY_CTRL_STBY_WAIT_MASK)

#define GPC_CPU_MODE_CTRL_CM_STBY_CTRL_STBY_STOP_MASK (0x2U)
#define GPC_CPU_MODE_CTRL_CM_STBY_CTRL_STBY_STOP_SHIFT (1U)
/*! STBY_STOP - 0x1: Request the chip into standby mode when CPU entering STOP mode, locked by LOCK_CFG field. */
#define GPC_CPU_MODE_CTRL_CM_STBY_CTRL_STBY_STOP(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_STBY_CTRL_STBY_STOP_SHIFT)) & GPC_CPU_MODE_CTRL_CM_STBY_CTRL_STBY_STOP_MASK)

#define GPC_CPU_MODE_CTRL_CM_STBY_CTRL_STBY_SUSPEND_MASK (0x4U)
#define GPC_CPU_MODE_CTRL_CM_STBY_CTRL_STBY_SUSPEND_SHIFT (2U)
/*! STBY_SUSPEND - 0x1: Request the chip into standby mode when CPU entering SUSPEND mode, locked by LOCK_CFG field. */
#define GPC_CPU_MODE_CTRL_CM_STBY_CTRL_STBY_SUSPEND(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_STBY_CTRL_STBY_SUSPEND_SHIFT)) & GPC_CPU_MODE_CTRL_CM_STBY_CTRL_STBY_SUSPEND_MASK)

#define GPC_CPU_MODE_CTRL_CM_STBY_CTRL_STBY_SLEEP_BUSY_MASK (0x10000U)
#define GPC_CPU_MODE_CTRL_CM_STBY_CTRL_STBY_SLEEP_BUSY_SHIFT (16U)
/*! STBY_SLEEP_BUSY - Indicate the CPU is busy entering standby mode. */
#define GPC_CPU_MODE_CTRL_CM_STBY_CTRL_STBY_SLEEP_BUSY(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_STBY_CTRL_STBY_SLEEP_BUSY_SHIFT)) & GPC_CPU_MODE_CTRL_CM_STBY_CTRL_STBY_SLEEP_BUSY_MASK)

#define GPC_CPU_MODE_CTRL_CM_STBY_CTRL_STBY_WAKEUP_BUSY_MASK (0x20000U)
#define GPC_CPU_MODE_CTRL_CM_STBY_CTRL_STBY_WAKEUP_BUSY_SHIFT (17U)
/*! STBY_WAKEUP_BUSY - Indicate the CPU is busy exiting standby mode. */
#define GPC_CPU_MODE_CTRL_CM_STBY_CTRL_STBY_WAKEUP_BUSY(x) (((uint32_t)(((uint32_t)(x)) << GPC_CPU_MODE_CTRL_CM_STBY_CTRL_STBY_WAKEUP_BUSY_SHIFT)) & GPC_CPU_MODE_CTRL_CM_STBY_CTRL_STBY_WAKEUP_BUSY_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group GPC_CPU_MODE_CTRL_Register_Masks */


/*!
 * @}
 */ /* end of group GPC_CPU_MODE_CTRL_Peripheral_Access_Layer */


/*
** End of section using anonymous unions
*/

#if defined(__ARMCC_VERSION)
  #if (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic pop
  #else
    #pragma pop
  #endif
#elif defined(__CWCC__)
  #pragma pop
#elif defined(__GNUC__)
  /* leave anonymous unions enabled */
#elif defined(__IAR_SYSTEMS_ICC__)
  #pragma language=default
#else
  #error Not supported compiler type
#endif

/*!
 * @}
 */ /* end of group Peripheral_access_layer */


#endif  /* PERI_GPC_CPU_MODE_CTRL_H_ */

