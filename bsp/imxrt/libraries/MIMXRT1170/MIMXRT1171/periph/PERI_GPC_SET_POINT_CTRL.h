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
**         CMSIS Peripheral Access Layer for GPC_SET_POINT_CTRL
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
 * @file PERI_GPC_SET_POINT_CTRL.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for GPC_SET_POINT_CTRL
 *
 * CMSIS Peripheral Access Layer for GPC_SET_POINT_CTRL
 */

#if !defined(PERI_GPC_SET_POINT_CTRL_H_)
#define PERI_GPC_SET_POINT_CTRL_H_               /**< Symbol preventing repeated inclusion */

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
   -- GPC_SET_POINT_CTRL Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPC_SET_POINT_CTRL_Peripheral_Access_Layer GPC_SET_POINT_CTRL Peripheral Access Layer
 * @{
 */

/** GPC_SET_POINT_CTRL - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[4];
  __IO uint32_t SP_AUTHEN_CTRL;                    /**< SP Authentication Control, offset: 0x4 */
  __IO uint32_t SP_INT_CTRL;                       /**< SP Interrupt Control, offset: 0x8 */
       uint8_t RESERVED_1[4];
  __I  uint32_t SP_CPU_REQ;                        /**< CPU SP Request, offset: 0x10 */
  __I  uint32_t SP_SYS_STAT;                       /**< SP System Status, offset: 0x14 */
       uint8_t RESERVED_2[4];
  __IO uint32_t SP_ROSC_CTRL;                      /**< SP ROSC Control, offset: 0x1C */
       uint8_t RESERVED_3[32];
  __IO uint32_t SP_PRIORITY_0_7;                   /**< SP0~7 Priority, offset: 0x40 */
  __IO uint32_t SP_PRIORITY_8_15;                  /**< SP8~15 Priority, offset: 0x44 */
       uint8_t RESERVED_4[184];
  __IO uint32_t SP_SSAR_SAVE_CTRL;                 /**< SP SSAR save control, offset: 0x100 */
       uint8_t RESERVED_5[12];
  __IO uint32_t SP_LPCG_OFF_CTRL;                  /**< SP LPCG off control, offset: 0x110 */
       uint8_t RESERVED_6[12];
  __IO uint32_t SP_GROUP_DOWN_CTRL;                /**< SP group down control, offset: 0x120 */
       uint8_t RESERVED_7[12];
  __IO uint32_t SP_ROOT_DOWN_CTRL;                 /**< SP root down control, offset: 0x130 */
       uint8_t RESERVED_8[12];
  __IO uint32_t SP_PLL_OFF_CTRL;                   /**< SP PLL off control, offset: 0x140 */
       uint8_t RESERVED_9[12];
  __IO uint32_t SP_ISO_ON_CTRL;                    /**< SP ISO on control, offset: 0x150 */
       uint8_t RESERVED_10[12];
  __IO uint32_t SP_RESET_EARLY_CTRL;               /**< SP reset early control, offset: 0x160 */
       uint8_t RESERVED_11[12];
  __IO uint32_t SP_POWER_OFF_CTRL;                 /**< SP power off control, offset: 0x170 */
       uint8_t RESERVED_12[12];
  __IO uint32_t SP_BIAS_OFF_CTRL;                  /**< SP bias off control, offset: 0x180 */
       uint8_t RESERVED_13[12];
  __IO uint32_t SP_BG_PLDO_OFF_CTRL;               /**< SP bandgap and PLL_LDO off control, offset: 0x190 */
       uint8_t RESERVED_14[12];
  __IO uint32_t SP_LDO_PRE_CTRL;                   /**< SP LDO pre control, offset: 0x1A0 */
       uint8_t RESERVED_15[12];
  __IO uint32_t SP_DCDC_DOWN_CTRL;                 /**< SP DCDC down control, offset: 0x1B0 */
       uint8_t RESERVED_16[76];
  __IO uint32_t SP_DCDC_UP_CTRL;                   /**< SP DCDC up control, offset: 0x200 */
       uint8_t RESERVED_17[12];
  __IO uint32_t SP_LDO_POST_CTRL;                  /**< SP LDO post control, offset: 0x210 */
       uint8_t RESERVED_18[12];
  __IO uint32_t SP_BG_PLDO_ON_CTRL;                /**< SP bandgap and PLL_LDO on control, offset: 0x220 */
       uint8_t RESERVED_19[12];
  __IO uint32_t SP_BIAS_ON_CTRL;                   /**< SP bias on control, offset: 0x230 */
       uint8_t RESERVED_20[12];
  __IO uint32_t SP_POWER_ON_CTRL;                  /**< SP power on control, offset: 0x240 */
       uint8_t RESERVED_21[12];
  __IO uint32_t SP_RESET_LATE_CTRL;                /**< SP reset late control, offset: 0x250 */
       uint8_t RESERVED_22[12];
  __IO uint32_t SP_ISO_OFF_CTRL;                   /**< SP ISO off control, offset: 0x260 */
       uint8_t RESERVED_23[12];
  __IO uint32_t SP_PLL_ON_CTRL;                    /**< SP PLL on control, offset: 0x270 */
       uint8_t RESERVED_24[12];
  __IO uint32_t SP_ROOT_UP_CTRL;                   /**< SP root up control, offset: 0x280 */
       uint8_t RESERVED_25[12];
  __IO uint32_t SP_GROUP_UP_CTRL;                  /**< SP group up control, offset: 0x290 */
       uint8_t RESERVED_26[12];
  __IO uint32_t SP_LPCG_ON_CTRL;                   /**< SP LPCG on control, offset: 0x2A0 */
       uint8_t RESERVED_27[12];
  __IO uint32_t SP_SSAR_RESTORE_CTRL;              /**< SP SSAR restore control, offset: 0x2B0 */
} GPC_SET_POINT_CTRL_Type;

/* ----------------------------------------------------------------------------
   -- GPC_SET_POINT_CTRL Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPC_SET_POINT_CTRL_Register_Masks GPC_SET_POINT_CTRL Register Masks
 * @{
 */

/*! @name SP_AUTHEN_CTRL - SP Authentication Control */
/*! @{ */

#define GPC_SET_POINT_CTRL_SP_AUTHEN_CTRL_USER_MASK (0x1U)
#define GPC_SET_POINT_CTRL_SP_AUTHEN_CTRL_USER_SHIFT (0U)
/*! USER - Allow user mode access
 *  0b0..Allow only privilege mode to access setpoint control registers
 *  0b1..Allow both privilege and user mode to access setpoint control registers
 */
#define GPC_SET_POINT_CTRL_SP_AUTHEN_CTRL_USER(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_AUTHEN_CTRL_USER_SHIFT)) & GPC_SET_POINT_CTRL_SP_AUTHEN_CTRL_USER_MASK)

#define GPC_SET_POINT_CTRL_SP_AUTHEN_CTRL_NONSECURE_MASK (0x2U)
#define GPC_SET_POINT_CTRL_SP_AUTHEN_CTRL_NONSECURE_SHIFT (1U)
/*! NONSECURE - Allow non-secure mode access
 *  0b0..Allow only secure mode to access setpoint control registers
 *  0b1..Allow both secure and non-secure mode to access setpoint control registers
 */
#define GPC_SET_POINT_CTRL_SP_AUTHEN_CTRL_NONSECURE(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_AUTHEN_CTRL_NONSECURE_SHIFT)) & GPC_SET_POINT_CTRL_SP_AUTHEN_CTRL_NONSECURE_MASK)

#define GPC_SET_POINT_CTRL_SP_AUTHEN_CTRL_LOCK_SETTING_MASK (0x10U)
#define GPC_SET_POINT_CTRL_SP_AUTHEN_CTRL_LOCK_SETTING_SHIFT (4U)
/*! LOCK_SETTING - Lock NONSECURE and USER */
#define GPC_SET_POINT_CTRL_SP_AUTHEN_CTRL_LOCK_SETTING(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_AUTHEN_CTRL_LOCK_SETTING_SHIFT)) & GPC_SET_POINT_CTRL_SP_AUTHEN_CTRL_LOCK_SETTING_MASK)

#define GPC_SET_POINT_CTRL_SP_AUTHEN_CTRL_WHITE_LIST_MASK (0xF00U)
#define GPC_SET_POINT_CTRL_SP_AUTHEN_CTRL_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Domain ID white list */
#define GPC_SET_POINT_CTRL_SP_AUTHEN_CTRL_WHITE_LIST(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_AUTHEN_CTRL_WHITE_LIST_SHIFT)) & GPC_SET_POINT_CTRL_SP_AUTHEN_CTRL_WHITE_LIST_MASK)

#define GPC_SET_POINT_CTRL_SP_AUTHEN_CTRL_LOCK_LIST_MASK (0x1000U)
#define GPC_SET_POINT_CTRL_SP_AUTHEN_CTRL_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - White list lock */
#define GPC_SET_POINT_CTRL_SP_AUTHEN_CTRL_LOCK_LIST(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_AUTHEN_CTRL_LOCK_LIST_SHIFT)) & GPC_SET_POINT_CTRL_SP_AUTHEN_CTRL_LOCK_LIST_MASK)

#define GPC_SET_POINT_CTRL_SP_AUTHEN_CTRL_LOCK_CFG_MASK (0x100000U)
#define GPC_SET_POINT_CTRL_SP_AUTHEN_CTRL_LOCK_CFG_SHIFT (20U)
/*! LOCK_CFG - Configuration lock */
#define GPC_SET_POINT_CTRL_SP_AUTHEN_CTRL_LOCK_CFG(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_AUTHEN_CTRL_LOCK_CFG_SHIFT)) & GPC_SET_POINT_CTRL_SP_AUTHEN_CTRL_LOCK_CFG_MASK)
/*! @} */

/*! @name SP_INT_CTRL - SP Interrupt Control */
/*! @{ */

#define GPC_SET_POINT_CTRL_SP_INT_CTRL_NO_ALLOWED_SP_INT_EN_MASK (0x1U)
#define GPC_SET_POINT_CTRL_SP_INT_CTRL_NO_ALLOWED_SP_INT_EN_SHIFT (0U)
/*! NO_ALLOWED_SP_INT_EN - no_allowed_set_point interrupt enable */
#define GPC_SET_POINT_CTRL_SP_INT_CTRL_NO_ALLOWED_SP_INT_EN(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_INT_CTRL_NO_ALLOWED_SP_INT_EN_SHIFT)) & GPC_SET_POINT_CTRL_SP_INT_CTRL_NO_ALLOWED_SP_INT_EN_MASK)

#define GPC_SET_POINT_CTRL_SP_INT_CTRL_NO_ALLOWED_SP_INT_MASK (0x2U)
#define GPC_SET_POINT_CTRL_SP_INT_CTRL_NO_ALLOWED_SP_INT_SHIFT (1U)
/*! NO_ALLOWED_SP_INT - no_allowed_set_point interrupt */
#define GPC_SET_POINT_CTRL_SP_INT_CTRL_NO_ALLOWED_SP_INT(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_INT_CTRL_NO_ALLOWED_SP_INT_SHIFT)) & GPC_SET_POINT_CTRL_SP_INT_CTRL_NO_ALLOWED_SP_INT_MASK)
/*! @} */

/*! @name SP_CPU_REQ - CPU SP Request */
/*! @{ */

#define GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_REQ_CPU0_MASK (0xFU)
#define GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_REQ_CPU0_SHIFT (0U)
/*! SP_REQ_CPU0 - Setpoint requested by CPU0 */
#define GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_REQ_CPU0(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_REQ_CPU0_SHIFT)) & GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_REQ_CPU0_MASK)

#define GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_REQ_CPU1_MASK (0xF0U)
#define GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_REQ_CPU1_SHIFT (4U)
/*! SP_REQ_CPU1 - Setpoint requested by CPU1 */
#define GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_REQ_CPU1(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_REQ_CPU1_SHIFT)) & GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_REQ_CPU1_MASK)

#define GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_REQ_CPU2_MASK (0xF00U)
#define GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_REQ_CPU2_SHIFT (8U)
/*! SP_REQ_CPU2 - Setpoint requested by CPU2 */
#define GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_REQ_CPU2(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_REQ_CPU2_SHIFT)) & GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_REQ_CPU2_MASK)

#define GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_REQ_CPU3_MASK (0xF000U)
#define GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_REQ_CPU3_SHIFT (12U)
/*! SP_REQ_CPU3 - Setpoint requested by CPU3 */
#define GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_REQ_CPU3(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_REQ_CPU3_SHIFT)) & GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_REQ_CPU3_MASK)

#define GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_ACCEPTED_CPU0_MASK (0xF0000U)
#define GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_ACCEPTED_CPU0_SHIFT (16U)
/*! SP_ACCEPTED_CPU0 - CPU0 Setpoint accepted by SP controller */
#define GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_ACCEPTED_CPU0(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_ACCEPTED_CPU0_SHIFT)) & GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_ACCEPTED_CPU0_MASK)

#define GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_ACCEPTED_CPU1_MASK (0xF00000U)
#define GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_ACCEPTED_CPU1_SHIFT (20U)
/*! SP_ACCEPTED_CPU1 - CPU1 Setpoint accepted by SP controller */
#define GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_ACCEPTED_CPU1(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_ACCEPTED_CPU1_SHIFT)) & GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_ACCEPTED_CPU1_MASK)

#define GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_ACCEPTED_CPU2_MASK (0xF000000U)
#define GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_ACCEPTED_CPU2_SHIFT (24U)
/*! SP_ACCEPTED_CPU2 - CPU2 Setpoint accepted by SP controller */
#define GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_ACCEPTED_CPU2(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_ACCEPTED_CPU2_SHIFT)) & GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_ACCEPTED_CPU2_MASK)

#define GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_ACCEPTED_CPU3_MASK (0xF0000000U)
#define GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_ACCEPTED_CPU3_SHIFT (28U)
/*! SP_ACCEPTED_CPU3 - CPU3 Setpoint accepted by SP controller */
#define GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_ACCEPTED_CPU3(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_ACCEPTED_CPU3_SHIFT)) & GPC_SET_POINT_CTRL_SP_CPU_REQ_SP_ACCEPTED_CPU3_MASK)
/*! @} */

/*! @name SP_SYS_STAT - SP System Status */
/*! @{ */

#define GPC_SET_POINT_CTRL_SP_SYS_STAT_SYS_SP_ALLOWED_MASK (0xFFFFU)
#define GPC_SET_POINT_CTRL_SP_SYS_STAT_SYS_SP_ALLOWED_SHIFT (0U)
/*! SYS_SP_ALLOWED - Allowed Setpoints by all current CPU Setpoint requests */
#define GPC_SET_POINT_CTRL_SP_SYS_STAT_SYS_SP_ALLOWED(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_SYS_STAT_SYS_SP_ALLOWED_SHIFT)) & GPC_SET_POINT_CTRL_SP_SYS_STAT_SYS_SP_ALLOWED_MASK)

#define GPC_SET_POINT_CTRL_SP_SYS_STAT_SYS_SP_TARGET_MASK (0xF0000U)
#define GPC_SET_POINT_CTRL_SP_SYS_STAT_SYS_SP_TARGET_SHIFT (16U)
/*! SYS_SP_TARGET - The Setpoint chosen as the target setpoint */
#define GPC_SET_POINT_CTRL_SP_SYS_STAT_SYS_SP_TARGET(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_SYS_STAT_SYS_SP_TARGET_SHIFT)) & GPC_SET_POINT_CTRL_SP_SYS_STAT_SYS_SP_TARGET_MASK)

#define GPC_SET_POINT_CTRL_SP_SYS_STAT_SYS_SP_CURRENT_MASK (0xF00000U)
#define GPC_SET_POINT_CTRL_SP_SYS_STAT_SYS_SP_CURRENT_SHIFT (20U)
/*! SYS_SP_CURRENT - Current Setpoint, only valid when not SP trans busy */
#define GPC_SET_POINT_CTRL_SP_SYS_STAT_SYS_SP_CURRENT(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_SYS_STAT_SYS_SP_CURRENT_SHIFT)) & GPC_SET_POINT_CTRL_SP_SYS_STAT_SYS_SP_CURRENT_MASK)

#define GPC_SET_POINT_CTRL_SP_SYS_STAT_SYS_SP_PREVIOUS_MASK (0xF000000U)
#define GPC_SET_POINT_CTRL_SP_SYS_STAT_SYS_SP_PREVIOUS_SHIFT (24U)
/*! SYS_SP_PREVIOUS - Previous Setpoint, only valid when not SP trans busy */
#define GPC_SET_POINT_CTRL_SP_SYS_STAT_SYS_SP_PREVIOUS(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_SYS_STAT_SYS_SP_PREVIOUS_SHIFT)) & GPC_SET_POINT_CTRL_SP_SYS_STAT_SYS_SP_PREVIOUS_MASK)
/*! @} */

/*! @name SP_ROSC_CTRL - SP ROSC Control */
/*! @{ */

#define GPC_SET_POINT_CTRL_SP_ROSC_CTRL_SP_ALLOW_ROSC_OFF_MASK (0xFFFFU)
#define GPC_SET_POINT_CTRL_SP_ROSC_CTRL_SP_ALLOW_ROSC_OFF_SHIFT (0U)
/*! SP_ALLOW_ROSC_OFF - Allow shutting off the ROSC */
#define GPC_SET_POINT_CTRL_SP_ROSC_CTRL_SP_ALLOW_ROSC_OFF(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_ROSC_CTRL_SP_ALLOW_ROSC_OFF_SHIFT)) & GPC_SET_POINT_CTRL_SP_ROSC_CTRL_SP_ALLOW_ROSC_OFF_MASK)
/*! @} */

/*! @name SP_PRIORITY_0_7 - SP0~7 Priority */
/*! @{ */

#define GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP0_PRIORITY_MASK (0xFU)
#define GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP0_PRIORITY_SHIFT (0U)
/*! SYS_SP0_PRIORITY - priority of Setpoint 0 */
#define GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP0_PRIORITY(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP0_PRIORITY_SHIFT)) & GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP0_PRIORITY_MASK)

#define GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP1_PRIORITY_MASK (0xF0U)
#define GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP1_PRIORITY_SHIFT (4U)
/*! SYS_SP1_PRIORITY - priority of Setpoint 1 */
#define GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP1_PRIORITY(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP1_PRIORITY_SHIFT)) & GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP1_PRIORITY_MASK)

#define GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP2_PRIORITY_MASK (0xF00U)
#define GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP2_PRIORITY_SHIFT (8U)
/*! SYS_SP2_PRIORITY - priority of Setpoint 2 */
#define GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP2_PRIORITY(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP2_PRIORITY_SHIFT)) & GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP2_PRIORITY_MASK)

#define GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP3_PRIORITY_MASK (0xF000U)
#define GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP3_PRIORITY_SHIFT (12U)
/*! SYS_SP3_PRIORITY - priority of Setpoint 3 */
#define GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP3_PRIORITY(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP3_PRIORITY_SHIFT)) & GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP3_PRIORITY_MASK)

#define GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP4_PRIORITY_MASK (0xF0000U)
#define GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP4_PRIORITY_SHIFT (16U)
/*! SYS_SP4_PRIORITY - priority of Setpoint 4 */
#define GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP4_PRIORITY(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP4_PRIORITY_SHIFT)) & GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP4_PRIORITY_MASK)

#define GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP5_PRIORITY_MASK (0xF00000U)
#define GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP5_PRIORITY_SHIFT (20U)
/*! SYS_SP5_PRIORITY - priority of Setpoint 5 */
#define GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP5_PRIORITY(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP5_PRIORITY_SHIFT)) & GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP5_PRIORITY_MASK)

#define GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP6_PRIORITY_MASK (0xF000000U)
#define GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP6_PRIORITY_SHIFT (24U)
/*! SYS_SP6_PRIORITY - priority of Setpoint 6 */
#define GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP6_PRIORITY(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP6_PRIORITY_SHIFT)) & GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP6_PRIORITY_MASK)

#define GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP7_PRIORITY_MASK (0xF0000000U)
#define GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP7_PRIORITY_SHIFT (28U)
/*! SYS_SP7_PRIORITY - priority of Setpoint 7 */
#define GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP7_PRIORITY(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP7_PRIORITY_SHIFT)) & GPC_SET_POINT_CTRL_SP_PRIORITY_0_7_SYS_SP7_PRIORITY_MASK)
/*! @} */

/*! @name SP_PRIORITY_8_15 - SP8~15 Priority */
/*! @{ */

#define GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP8_PRIORITY_MASK (0xFU)
#define GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP8_PRIORITY_SHIFT (0U)
/*! SYS_SP8_PRIORITY - priority of Setpoint 8 */
#define GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP8_PRIORITY(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP8_PRIORITY_SHIFT)) & GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP8_PRIORITY_MASK)

#define GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP9_PRIORITY_MASK (0xF0U)
#define GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP9_PRIORITY_SHIFT (4U)
/*! SYS_SP9_PRIORITY - priority of Setpoint 9 */
#define GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP9_PRIORITY(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP9_PRIORITY_SHIFT)) & GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP9_PRIORITY_MASK)

#define GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP10_PRIORITY_MASK (0xF00U)
#define GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP10_PRIORITY_SHIFT (8U)
/*! SYS_SP10_PRIORITY - priority of Setpoint 10 */
#define GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP10_PRIORITY(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP10_PRIORITY_SHIFT)) & GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP10_PRIORITY_MASK)

#define GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP11_PRIORITY_MASK (0xF000U)
#define GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP11_PRIORITY_SHIFT (12U)
/*! SYS_SP11_PRIORITY - priority of Setpoint 11 */
#define GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP11_PRIORITY(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP11_PRIORITY_SHIFT)) & GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP11_PRIORITY_MASK)

#define GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP12_PRIORITY_MASK (0xF0000U)
#define GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP12_PRIORITY_SHIFT (16U)
/*! SYS_SP12_PRIORITY - priority of Setpoint 12 */
#define GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP12_PRIORITY(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP12_PRIORITY_SHIFT)) & GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP12_PRIORITY_MASK)

#define GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP13_PRIORITY_MASK (0xF00000U)
#define GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP13_PRIORITY_SHIFT (20U)
/*! SYS_SP13_PRIORITY - priority of Setpoint 13 */
#define GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP13_PRIORITY(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP13_PRIORITY_SHIFT)) & GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP13_PRIORITY_MASK)

#define GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP14_PRIORITY_MASK (0xF000000U)
#define GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP14_PRIORITY_SHIFT (24U)
/*! SYS_SP14_PRIORITY - priority of Setpoint 14 */
#define GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP14_PRIORITY(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP14_PRIORITY_SHIFT)) & GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP14_PRIORITY_MASK)

#define GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP15_PRIORITY_MASK (0xF0000000U)
#define GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP15_PRIORITY_SHIFT (28U)
/*! SYS_SP15_PRIORITY - priority of Setpoint 15 */
#define GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP15_PRIORITY(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP15_PRIORITY_SHIFT)) & GPC_SET_POINT_CTRL_SP_PRIORITY_8_15_SYS_SP15_PRIORITY_MASK)
/*! @} */

/*! @name SP_SSAR_SAVE_CTRL - SP SSAR save control */
/*! @{ */

#define GPC_SET_POINT_CTRL_SP_SSAR_SAVE_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_SET_POINT_CTRL_SP_SSAR_SAVE_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_SET_POINT_CTRL_SP_SSAR_SAVE_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_SSAR_SAVE_CTRL_DISABLE_SHIFT)) & GPC_SET_POINT_CTRL_SP_SSAR_SAVE_CTRL_DISABLE_MASK)
/*! @} */

/*! @name SP_LPCG_OFF_CTRL - SP LPCG off control */
/*! @{ */

#define GPC_SET_POINT_CTRL_SP_LPCG_OFF_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_SET_POINT_CTRL_SP_LPCG_OFF_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_SET_POINT_CTRL_SP_LPCG_OFF_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_LPCG_OFF_CTRL_DISABLE_SHIFT)) & GPC_SET_POINT_CTRL_SP_LPCG_OFF_CTRL_DISABLE_MASK)
/*! @} */

/*! @name SP_GROUP_DOWN_CTRL - SP group down control */
/*! @{ */

#define GPC_SET_POINT_CTRL_SP_GROUP_DOWN_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_SET_POINT_CTRL_SP_GROUP_DOWN_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_SET_POINT_CTRL_SP_GROUP_DOWN_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_GROUP_DOWN_CTRL_DISABLE_SHIFT)) & GPC_SET_POINT_CTRL_SP_GROUP_DOWN_CTRL_DISABLE_MASK)
/*! @} */

/*! @name SP_ROOT_DOWN_CTRL - SP root down control */
/*! @{ */

#define GPC_SET_POINT_CTRL_SP_ROOT_DOWN_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_SET_POINT_CTRL_SP_ROOT_DOWN_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_SET_POINT_CTRL_SP_ROOT_DOWN_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_ROOT_DOWN_CTRL_DISABLE_SHIFT)) & GPC_SET_POINT_CTRL_SP_ROOT_DOWN_CTRL_DISABLE_MASK)
/*! @} */

/*! @name SP_PLL_OFF_CTRL - SP PLL off control */
/*! @{ */

#define GPC_SET_POINT_CTRL_SP_PLL_OFF_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_SET_POINT_CTRL_SP_PLL_OFF_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_SET_POINT_CTRL_SP_PLL_OFF_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_PLL_OFF_CTRL_DISABLE_SHIFT)) & GPC_SET_POINT_CTRL_SP_PLL_OFF_CTRL_DISABLE_MASK)
/*! @} */

/*! @name SP_ISO_ON_CTRL - SP ISO on control */
/*! @{ */

#define GPC_SET_POINT_CTRL_SP_ISO_ON_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_SET_POINT_CTRL_SP_ISO_ON_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_SET_POINT_CTRL_SP_ISO_ON_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_ISO_ON_CTRL_DISABLE_SHIFT)) & GPC_SET_POINT_CTRL_SP_ISO_ON_CTRL_DISABLE_MASK)
/*! @} */

/*! @name SP_RESET_EARLY_CTRL - SP reset early control */
/*! @{ */

#define GPC_SET_POINT_CTRL_SP_RESET_EARLY_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_SET_POINT_CTRL_SP_RESET_EARLY_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_SET_POINT_CTRL_SP_RESET_EARLY_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_RESET_EARLY_CTRL_DISABLE_SHIFT)) & GPC_SET_POINT_CTRL_SP_RESET_EARLY_CTRL_DISABLE_MASK)
/*! @} */

/*! @name SP_POWER_OFF_CTRL - SP power off control */
/*! @{ */

#define GPC_SET_POINT_CTRL_SP_POWER_OFF_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_SET_POINT_CTRL_SP_POWER_OFF_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_SET_POINT_CTRL_SP_POWER_OFF_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_POWER_OFF_CTRL_DISABLE_SHIFT)) & GPC_SET_POINT_CTRL_SP_POWER_OFF_CTRL_DISABLE_MASK)
/*! @} */

/*! @name SP_BIAS_OFF_CTRL - SP bias off control */
/*! @{ */

#define GPC_SET_POINT_CTRL_SP_BIAS_OFF_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_SET_POINT_CTRL_SP_BIAS_OFF_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_SET_POINT_CTRL_SP_BIAS_OFF_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_BIAS_OFF_CTRL_DISABLE_SHIFT)) & GPC_SET_POINT_CTRL_SP_BIAS_OFF_CTRL_DISABLE_MASK)
/*! @} */

/*! @name SP_BG_PLDO_OFF_CTRL - SP bandgap and PLL_LDO off control */
/*! @{ */

#define GPC_SET_POINT_CTRL_SP_BG_PLDO_OFF_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_SET_POINT_CTRL_SP_BG_PLDO_OFF_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_SET_POINT_CTRL_SP_BG_PLDO_OFF_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_BG_PLDO_OFF_CTRL_DISABLE_SHIFT)) & GPC_SET_POINT_CTRL_SP_BG_PLDO_OFF_CTRL_DISABLE_MASK)
/*! @} */

/*! @name SP_LDO_PRE_CTRL - SP LDO pre control */
/*! @{ */

#define GPC_SET_POINT_CTRL_SP_LDO_PRE_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_SET_POINT_CTRL_SP_LDO_PRE_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_SET_POINT_CTRL_SP_LDO_PRE_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_LDO_PRE_CTRL_DISABLE_SHIFT)) & GPC_SET_POINT_CTRL_SP_LDO_PRE_CTRL_DISABLE_MASK)
/*! @} */

/*! @name SP_DCDC_DOWN_CTRL - SP DCDC down control */
/*! @{ */

#define GPC_SET_POINT_CTRL_SP_DCDC_DOWN_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_SET_POINT_CTRL_SP_DCDC_DOWN_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_SET_POINT_CTRL_SP_DCDC_DOWN_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_DCDC_DOWN_CTRL_DISABLE_SHIFT)) & GPC_SET_POINT_CTRL_SP_DCDC_DOWN_CTRL_DISABLE_MASK)
/*! @} */

/*! @name SP_DCDC_UP_CTRL - SP DCDC up control */
/*! @{ */

#define GPC_SET_POINT_CTRL_SP_DCDC_UP_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_SET_POINT_CTRL_SP_DCDC_UP_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_SET_POINT_CTRL_SP_DCDC_UP_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_DCDC_UP_CTRL_DISABLE_SHIFT)) & GPC_SET_POINT_CTRL_SP_DCDC_UP_CTRL_DISABLE_MASK)
/*! @} */

/*! @name SP_LDO_POST_CTRL - SP LDO post control */
/*! @{ */

#define GPC_SET_POINT_CTRL_SP_LDO_POST_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_SET_POINT_CTRL_SP_LDO_POST_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_SET_POINT_CTRL_SP_LDO_POST_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_LDO_POST_CTRL_DISABLE_SHIFT)) & GPC_SET_POINT_CTRL_SP_LDO_POST_CTRL_DISABLE_MASK)
/*! @} */

/*! @name SP_BG_PLDO_ON_CTRL - SP bandgap and PLL_LDO on control */
/*! @{ */

#define GPC_SET_POINT_CTRL_SP_BG_PLDO_ON_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_SET_POINT_CTRL_SP_BG_PLDO_ON_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_SET_POINT_CTRL_SP_BG_PLDO_ON_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_BG_PLDO_ON_CTRL_DISABLE_SHIFT)) & GPC_SET_POINT_CTRL_SP_BG_PLDO_ON_CTRL_DISABLE_MASK)
/*! @} */

/*! @name SP_BIAS_ON_CTRL - SP bias on control */
/*! @{ */

#define GPC_SET_POINT_CTRL_SP_BIAS_ON_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_SET_POINT_CTRL_SP_BIAS_ON_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_SET_POINT_CTRL_SP_BIAS_ON_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_BIAS_ON_CTRL_DISABLE_SHIFT)) & GPC_SET_POINT_CTRL_SP_BIAS_ON_CTRL_DISABLE_MASK)
/*! @} */

/*! @name SP_POWER_ON_CTRL - SP power on control */
/*! @{ */

#define GPC_SET_POINT_CTRL_SP_POWER_ON_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_SET_POINT_CTRL_SP_POWER_ON_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_SET_POINT_CTRL_SP_POWER_ON_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_POWER_ON_CTRL_DISABLE_SHIFT)) & GPC_SET_POINT_CTRL_SP_POWER_ON_CTRL_DISABLE_MASK)
/*! @} */

/*! @name SP_RESET_LATE_CTRL - SP reset late control */
/*! @{ */

#define GPC_SET_POINT_CTRL_SP_RESET_LATE_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_SET_POINT_CTRL_SP_RESET_LATE_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_SET_POINT_CTRL_SP_RESET_LATE_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_RESET_LATE_CTRL_DISABLE_SHIFT)) & GPC_SET_POINT_CTRL_SP_RESET_LATE_CTRL_DISABLE_MASK)
/*! @} */

/*! @name SP_ISO_OFF_CTRL - SP ISO off control */
/*! @{ */

#define GPC_SET_POINT_CTRL_SP_ISO_OFF_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_SET_POINT_CTRL_SP_ISO_OFF_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_SET_POINT_CTRL_SP_ISO_OFF_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_ISO_OFF_CTRL_DISABLE_SHIFT)) & GPC_SET_POINT_CTRL_SP_ISO_OFF_CTRL_DISABLE_MASK)
/*! @} */

/*! @name SP_PLL_ON_CTRL - SP PLL on control */
/*! @{ */

#define GPC_SET_POINT_CTRL_SP_PLL_ON_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_SET_POINT_CTRL_SP_PLL_ON_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_SET_POINT_CTRL_SP_PLL_ON_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_PLL_ON_CTRL_DISABLE_SHIFT)) & GPC_SET_POINT_CTRL_SP_PLL_ON_CTRL_DISABLE_MASK)
/*! @} */

/*! @name SP_ROOT_UP_CTRL - SP root up control */
/*! @{ */

#define GPC_SET_POINT_CTRL_SP_ROOT_UP_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_SET_POINT_CTRL_SP_ROOT_UP_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_SET_POINT_CTRL_SP_ROOT_UP_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_ROOT_UP_CTRL_DISABLE_SHIFT)) & GPC_SET_POINT_CTRL_SP_ROOT_UP_CTRL_DISABLE_MASK)
/*! @} */

/*! @name SP_GROUP_UP_CTRL - SP group up control */
/*! @{ */

#define GPC_SET_POINT_CTRL_SP_GROUP_UP_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_SET_POINT_CTRL_SP_GROUP_UP_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_SET_POINT_CTRL_SP_GROUP_UP_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_GROUP_UP_CTRL_DISABLE_SHIFT)) & GPC_SET_POINT_CTRL_SP_GROUP_UP_CTRL_DISABLE_MASK)
/*! @} */

/*! @name SP_LPCG_ON_CTRL - SP LPCG on control */
/*! @{ */

#define GPC_SET_POINT_CTRL_SP_LPCG_ON_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_SET_POINT_CTRL_SP_LPCG_ON_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_SET_POINT_CTRL_SP_LPCG_ON_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_LPCG_ON_CTRL_DISABLE_SHIFT)) & GPC_SET_POINT_CTRL_SP_LPCG_ON_CTRL_DISABLE_MASK)
/*! @} */

/*! @name SP_SSAR_RESTORE_CTRL - SP SSAR restore control */
/*! @{ */

#define GPC_SET_POINT_CTRL_SP_SSAR_RESTORE_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_SET_POINT_CTRL_SP_SSAR_RESTORE_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_SET_POINT_CTRL_SP_SSAR_RESTORE_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_SET_POINT_CTRL_SP_SSAR_RESTORE_CTRL_DISABLE_SHIFT)) & GPC_SET_POINT_CTRL_SP_SSAR_RESTORE_CTRL_DISABLE_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group GPC_SET_POINT_CTRL_Register_Masks */


/*!
 * @}
 */ /* end of group GPC_SET_POINT_CTRL_Peripheral_Access_Layer */


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


#endif  /* PERI_GPC_SET_POINT_CTRL_H_ */

