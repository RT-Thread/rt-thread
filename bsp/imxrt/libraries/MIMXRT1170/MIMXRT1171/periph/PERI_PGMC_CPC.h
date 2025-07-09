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
**         CMSIS Peripheral Access Layer for PGMC_CPC
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
 * @file PERI_PGMC_CPC.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for PGMC_CPC
 *
 * CMSIS Peripheral Access Layer for PGMC_CPC
 */

#if !defined(PERI_PGMC_CPC_H_)
#define PERI_PGMC_CPC_H_                         /**< Symbol preventing repeated inclusion */

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
   -- PGMC_CPC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PGMC_CPC_Peripheral_Access_Layer PGMC_CPC Peripheral Access Layer
 * @{
 */

/** PGMC_CPC - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[4];
  __IO uint32_t CPC_AUTHEN_CTRL;                   /**< CPC Authentication Control, offset: 0x4 */
       uint8_t RESERVED_1[8];
  __IO uint32_t CPC_CORE_MODE;                     /**< CPC Core Mode, offset: 0x10 */
  __IO uint32_t CPC_CORE_POWER_CTRL;               /**< CPC core power control, offset: 0x14 */
       uint8_t RESERVED_2[20];
  __IO uint32_t CPC_FLAG;                          /**< CPC flag, offset: 0x2C */
       uint8_t RESERVED_3[16];
  __IO uint32_t CPC_CACHE_MODE;                    /**< CPC Cache Mode, offset: 0x40 */
  __IO uint32_t CPC_CACHE_CM_CTRL;                 /**< CPC cache CPU mode control, offset: 0x44 */
  __IO uint32_t CPC_CACHE_SP_CTRL_0;               /**< CPC cache Setpoint control 0, offset: 0x48 */
  __IO uint32_t CPC_CACHE_SP_CTRL_1;               /**< CPC cache Setpoint control 1, offset: 0x4C */
       uint8_t RESERVED_4[112];
  __IO uint32_t CPC_LMEM_MODE;                     /**< CPC local memory Mode, offset: 0xC0 */
  __IO uint32_t CPC_LMEM_CM_CTRL;                  /**< CPC local memory CPU mode control, offset: 0xC4 */
  __IO uint32_t CPC_LMEM_SP_CTRL_0;                /**< CPC local memory Setpoint control 0, offset: 0xC8 */
  __IO uint32_t CPC_LMEM_SP_CTRL_1;                /**< CPC local memory Setpoint control 1, offset: 0xCC */
} PGMC_CPC_Type;

/* ----------------------------------------------------------------------------
   -- PGMC_CPC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PGMC_CPC_Register_Masks PGMC_CPC Register Masks
 * @{
 */

/*! @name CPC_AUTHEN_CTRL - CPC Authentication Control */
/*! @{ */

#define PGMC_CPC_CPC_AUTHEN_CTRL_USER_MASK       (0x1U)
#define PGMC_CPC_CPC_AUTHEN_CTRL_USER_SHIFT      (0U)
/*! USER - Allow user mode access */
#define PGMC_CPC_CPC_AUTHEN_CTRL_USER(x)         (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_AUTHEN_CTRL_USER_SHIFT)) & PGMC_CPC_CPC_AUTHEN_CTRL_USER_MASK)

#define PGMC_CPC_CPC_AUTHEN_CTRL_NONSECURE_MASK  (0x2U)
#define PGMC_CPC_CPC_AUTHEN_CTRL_NONSECURE_SHIFT (1U)
/*! NONSECURE - Allow non-secure mode access */
#define PGMC_CPC_CPC_AUTHEN_CTRL_NONSECURE(x)    (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_AUTHEN_CTRL_NONSECURE_SHIFT)) & PGMC_CPC_CPC_AUTHEN_CTRL_NONSECURE_MASK)

#define PGMC_CPC_CPC_AUTHEN_CTRL_LOCK_SETTING_MASK (0x10U)
#define PGMC_CPC_CPC_AUTHEN_CTRL_LOCK_SETTING_SHIFT (4U)
/*! LOCK_SETTING - Lock NONSECURE and USER */
#define PGMC_CPC_CPC_AUTHEN_CTRL_LOCK_SETTING(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_AUTHEN_CTRL_LOCK_SETTING_SHIFT)) & PGMC_CPC_CPC_AUTHEN_CTRL_LOCK_SETTING_MASK)

#define PGMC_CPC_CPC_AUTHEN_CTRL_WHITE_LIST_MASK (0xF00U)
#define PGMC_CPC_CPC_AUTHEN_CTRL_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - Domain ID white list */
#define PGMC_CPC_CPC_AUTHEN_CTRL_WHITE_LIST(x)   (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_AUTHEN_CTRL_WHITE_LIST_SHIFT)) & PGMC_CPC_CPC_AUTHEN_CTRL_WHITE_LIST_MASK)

#define PGMC_CPC_CPC_AUTHEN_CTRL_LOCK_LIST_MASK  (0x1000U)
#define PGMC_CPC_CPC_AUTHEN_CTRL_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - White list lock */
#define PGMC_CPC_CPC_AUTHEN_CTRL_LOCK_LIST(x)    (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_AUTHEN_CTRL_LOCK_LIST_SHIFT)) & PGMC_CPC_CPC_AUTHEN_CTRL_LOCK_LIST_MASK)

#define PGMC_CPC_CPC_AUTHEN_CTRL_LOCK_CFG_MASK   (0x100000U)
#define PGMC_CPC_CPC_AUTHEN_CTRL_LOCK_CFG_SHIFT  (20U)
/*! LOCK_CFG - Configuration lock */
#define PGMC_CPC_CPC_AUTHEN_CTRL_LOCK_CFG(x)     (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_AUTHEN_CTRL_LOCK_CFG_SHIFT)) & PGMC_CPC_CPC_AUTHEN_CTRL_LOCK_CFG_MASK)
/*! @} */

/*! @name CPC_CORE_MODE - CPC Core Mode */
/*! @{ */

#define PGMC_CPC_CPC_CORE_MODE_CTRL_MODE_MASK    (0x3U)
#define PGMC_CPC_CPC_CORE_MODE_CTRL_MODE_SHIFT   (0U)
/*! CTRL_MODE - Control mode. This field is locked by AUTHEN_CTRL[LOCK_CFG] field.
 *  0b00..Not affected by any low power mode
 *  0b01..Controlled by CPU power mode of the domain
 *  0b10..Reserved
 *  0b11..Reserved
 */
#define PGMC_CPC_CPC_CORE_MODE_CTRL_MODE(x)      (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_CORE_MODE_CTRL_MODE_SHIFT)) & PGMC_CPC_CPC_CORE_MODE_CTRL_MODE_MASK)
/*! @} */

/*! @name CPC_CORE_POWER_CTRL - CPC core power control */
/*! @{ */

#define PGMC_CPC_CPC_CORE_POWER_CTRL_PWR_OFF_AT_WAIT_MASK (0x2U)
#define PGMC_CPC_CPC_CORE_POWER_CTRL_PWR_OFF_AT_WAIT_SHIFT (1U)
/*! PWR_OFF_AT_WAIT - Power off when domain enters WAIT mode */
#define PGMC_CPC_CPC_CORE_POWER_CTRL_PWR_OFF_AT_WAIT(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_CORE_POWER_CTRL_PWR_OFF_AT_WAIT_SHIFT)) & PGMC_CPC_CPC_CORE_POWER_CTRL_PWR_OFF_AT_WAIT_MASK)

#define PGMC_CPC_CPC_CORE_POWER_CTRL_PWR_OFF_AT_STOP_MASK (0x4U)
#define PGMC_CPC_CPC_CORE_POWER_CTRL_PWR_OFF_AT_STOP_SHIFT (2U)
/*! PWR_OFF_AT_STOP - Power off when domain enters STOP mode */
#define PGMC_CPC_CPC_CORE_POWER_CTRL_PWR_OFF_AT_STOP(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_CORE_POWER_CTRL_PWR_OFF_AT_STOP_SHIFT)) & PGMC_CPC_CPC_CORE_POWER_CTRL_PWR_OFF_AT_STOP_MASK)

#define PGMC_CPC_CPC_CORE_POWER_CTRL_PWR_OFF_AT_SUSPEND_MASK (0x8U)
#define PGMC_CPC_CPC_CORE_POWER_CTRL_PWR_OFF_AT_SUSPEND_SHIFT (3U)
/*! PWR_OFF_AT_SUSPEND - Power off when domain enters SUSPEND mode */
#define PGMC_CPC_CPC_CORE_POWER_CTRL_PWR_OFF_AT_SUSPEND(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_CORE_POWER_CTRL_PWR_OFF_AT_SUSPEND_SHIFT)) & PGMC_CPC_CPC_CORE_POWER_CTRL_PWR_OFF_AT_SUSPEND_MASK)

#define PGMC_CPC_CPC_CORE_POWER_CTRL_ISO_ON_SOFT_MASK (0x100U)
#define PGMC_CPC_CPC_CORE_POWER_CTRL_ISO_ON_SOFT_SHIFT (8U)
/*! ISO_ON_SOFT - Software isolation on trigger */
#define PGMC_CPC_CPC_CORE_POWER_CTRL_ISO_ON_SOFT(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_CORE_POWER_CTRL_ISO_ON_SOFT_SHIFT)) & PGMC_CPC_CPC_CORE_POWER_CTRL_ISO_ON_SOFT_MASK)

#define PGMC_CPC_CPC_CORE_POWER_CTRL_PSW_OFF_SOFT_MASK (0x200U)
#define PGMC_CPC_CPC_CORE_POWER_CTRL_PSW_OFF_SOFT_SHIFT (9U)
/*! PSW_OFF_SOFT - Software power off trigger */
#define PGMC_CPC_CPC_CORE_POWER_CTRL_PSW_OFF_SOFT(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_CORE_POWER_CTRL_PSW_OFF_SOFT_SHIFT)) & PGMC_CPC_CPC_CORE_POWER_CTRL_PSW_OFF_SOFT_MASK)

#define PGMC_CPC_CPC_CORE_POWER_CTRL_PSW_ON_SOFT_MASK (0x400U)
#define PGMC_CPC_CPC_CORE_POWER_CTRL_PSW_ON_SOFT_SHIFT (10U)
/*! PSW_ON_SOFT - Software power on trigger */
#define PGMC_CPC_CPC_CORE_POWER_CTRL_PSW_ON_SOFT(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_CORE_POWER_CTRL_PSW_ON_SOFT_SHIFT)) & PGMC_CPC_CPC_CORE_POWER_CTRL_PSW_ON_SOFT_MASK)

#define PGMC_CPC_CPC_CORE_POWER_CTRL_ISO_OFF_SOFT_MASK (0x800U)
#define PGMC_CPC_CPC_CORE_POWER_CTRL_ISO_OFF_SOFT_SHIFT (11U)
/*! ISO_OFF_SOFT - Software isolation off trigger */
#define PGMC_CPC_CPC_CORE_POWER_CTRL_ISO_OFF_SOFT(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_CORE_POWER_CTRL_ISO_OFF_SOFT_SHIFT)) & PGMC_CPC_CPC_CORE_POWER_CTRL_ISO_OFF_SOFT_MASK)
/*! @} */

/*! @name CPC_FLAG - CPC flag */
/*! @{ */

#define PGMC_CPC_CPC_FLAG_CORE_PDN_FLAG_MASK     (0x1U)
#define PGMC_CPC_CPC_FLAG_CORE_PDN_FLAG_SHIFT    (0U)
/*! CORE_PDN_FLAG - set to 1 after core power switch off, cleared by writing 1 */
#define PGMC_CPC_CPC_FLAG_CORE_PDN_FLAG(x)       (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_FLAG_CORE_PDN_FLAG_SHIFT)) & PGMC_CPC_CPC_FLAG_CORE_PDN_FLAG_MASK)
/*! @} */

/*! @name CPC_CACHE_MODE - CPC Cache Mode */
/*! @{ */

#define PGMC_CPC_CPC_CACHE_MODE_CTRL_MODE_MASK   (0x3U)
#define PGMC_CPC_CPC_CACHE_MODE_CTRL_MODE_SHIFT  (0U)
/*! CTRL_MODE - Control mode. This field is locked by AUTHEN_CTRL[LOCK_CFG] field.
 *  0b00..Not affected by any low power mode
 *  0b01..Controlled by CPU power mode of the domain
 *  0b10..Controlled by Setpoint
 *  0b11..Reserved
 */
#define PGMC_CPC_CPC_CACHE_MODE_CTRL_MODE(x)     (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_CACHE_MODE_CTRL_MODE_SHIFT)) & PGMC_CPC_CPC_CACHE_MODE_CTRL_MODE_MASK)
/*! @} */

/*! @name CPC_CACHE_CM_CTRL - CPC cache CPU mode control */
/*! @{ */

#define PGMC_CPC_CPC_CACHE_CM_CTRL_MLPL_AT_RUN_MASK (0xFU)
#define PGMC_CPC_CPC_CACHE_CM_CTRL_MLPL_AT_RUN_SHIFT (0U)
/*! MLPL_AT_RUN - Memory Low Power Level (MLPL) at RUN mode */
#define PGMC_CPC_CPC_CACHE_CM_CTRL_MLPL_AT_RUN(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_CACHE_CM_CTRL_MLPL_AT_RUN_SHIFT)) & PGMC_CPC_CPC_CACHE_CM_CTRL_MLPL_AT_RUN_MASK)

#define PGMC_CPC_CPC_CACHE_CM_CTRL_MLPL_AT_WAIT_MASK (0xF0U)
#define PGMC_CPC_CPC_CACHE_CM_CTRL_MLPL_AT_WAIT_SHIFT (4U)
/*! MLPL_AT_WAIT - Memory Low Power Level (MLPL) at WAIT mode. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_CACHE_CM_CTRL_MLPL_AT_WAIT(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_CACHE_CM_CTRL_MLPL_AT_WAIT_SHIFT)) & PGMC_CPC_CPC_CACHE_CM_CTRL_MLPL_AT_WAIT_MASK)

#define PGMC_CPC_CPC_CACHE_CM_CTRL_MLPL_AT_STOP_MASK (0xF00U)
#define PGMC_CPC_CPC_CACHE_CM_CTRL_MLPL_AT_STOP_SHIFT (8U)
/*! MLPL_AT_STOP - Memory Low Power Level (MLPL) at STOP mode. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_CACHE_CM_CTRL_MLPL_AT_STOP(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_CACHE_CM_CTRL_MLPL_AT_STOP_SHIFT)) & PGMC_CPC_CPC_CACHE_CM_CTRL_MLPL_AT_STOP_MASK)

#define PGMC_CPC_CPC_CACHE_CM_CTRL_MLPL_AT_SUSPEND_MASK (0xF000U)
#define PGMC_CPC_CPC_CACHE_CM_CTRL_MLPL_AT_SUSPEND_SHIFT (12U)
/*! MLPL_AT_SUSPEND - Memory Low Power Level (MLPL) at SUSPEND mode. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_CACHE_CM_CTRL_MLPL_AT_SUSPEND(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_CACHE_CM_CTRL_MLPL_AT_SUSPEND_SHIFT)) & PGMC_CPC_CPC_CACHE_CM_CTRL_MLPL_AT_SUSPEND_MASK)

#define PGMC_CPC_CPC_CACHE_CM_CTRL_MLPL_SOFT_MASK (0x10000U)
#define PGMC_CPC_CPC_CACHE_CM_CTRL_MLPL_SOFT_SHIFT (16U)
/*! MLPL_SOFT - Memory Low Power Level (MLPL) software change request, keep 1 until MLPL transition complete */
#define PGMC_CPC_CPC_CACHE_CM_CTRL_MLPL_SOFT(x)  (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_CACHE_CM_CTRL_MLPL_SOFT_SHIFT)) & PGMC_CPC_CPC_CACHE_CM_CTRL_MLPL_SOFT_MASK)
/*! @} */

/*! @name CPC_CACHE_SP_CTRL_0 - CPC cache Setpoint control 0 */
/*! @{ */

#define PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP0_MASK (0xFU)
#define PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP0_SHIFT (0U)
/*! MLPL_AT_SP0 - Memory Low Power Level (MLPL) at Setpoint 0. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP0(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP0_SHIFT)) & PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP0_MASK)

#define PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP1_MASK (0xF0U)
#define PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP1_SHIFT (4U)
/*! MLPL_AT_SP1 - Memory Low Power Level (MLPL) at Setpoint 1. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP1(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP1_SHIFT)) & PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP1_MASK)

#define PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP2_MASK (0xF00U)
#define PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP2_SHIFT (8U)
/*! MLPL_AT_SP2 - Memory Low Power Level (MLPL) at Setpoint 2. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP2(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP2_SHIFT)) & PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP2_MASK)

#define PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP3_MASK (0xF000U)
#define PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP3_SHIFT (12U)
/*! MLPL_AT_SP3 - Memory Low Power Level (MLPL) at Setpoint 3. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP3(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP3_SHIFT)) & PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP3_MASK)

#define PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP4_MASK (0xF0000U)
#define PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP4_SHIFT (16U)
/*! MLPL_AT_SP4 - Memory Low Power Level (MLPL) at Setpoint 4. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP4(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP4_SHIFT)) & PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP4_MASK)

#define PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP5_MASK (0xF00000U)
#define PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP5_SHIFT (20U)
/*! MLPL_AT_SP5 - Memory Low Power Level (MLPL) at Setpoint 5. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP5(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP5_SHIFT)) & PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP5_MASK)

#define PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP6_MASK (0xF000000U)
#define PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP6_SHIFT (24U)
/*! MLPL_AT_SP6 - Memory Low Power Level (MLPL) at Setpoint 6. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP6(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP6_SHIFT)) & PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP6_MASK)

#define PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP7_MASK (0xF0000000U)
#define PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP7_SHIFT (28U)
/*! MLPL_AT_SP7 - Memory Low Power Level (MLPL) at Setpoint 7. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP7(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP7_SHIFT)) & PGMC_CPC_CPC_CACHE_SP_CTRL_0_MLPL_AT_SP7_MASK)
/*! @} */

/*! @name CPC_CACHE_SP_CTRL_1 - CPC cache Setpoint control 1 */
/*! @{ */

#define PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP8_MASK (0xFU)
#define PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP8_SHIFT (0U)
/*! MLPL_AT_SP8 - Memory Low Power Level (MLPL) at Setpoint 8. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP8(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP8_SHIFT)) & PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP8_MASK)

#define PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP9_MASK (0xF0U)
#define PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP9_SHIFT (4U)
/*! MLPL_AT_SP9 - Memory Low Power Level (MLPL) at Setpoint 9. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP9(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP9_SHIFT)) & PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP9_MASK)

#define PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP10_MASK (0xF00U)
#define PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP10_SHIFT (8U)
/*! MLPL_AT_SP10 - Memory Low Power Level (MLPL) at Setpoint 10. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP10(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP10_SHIFT)) & PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP10_MASK)

#define PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP11_MASK (0xF000U)
#define PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP11_SHIFT (12U)
/*! MLPL_AT_SP11 - Memory Low Power Level (MLPL) at Setpoint 11. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP11(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP11_SHIFT)) & PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP11_MASK)

#define PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP12_MASK (0xF0000U)
#define PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP12_SHIFT (16U)
/*! MLPL_AT_SP12 - Memory Low Power Level (MLPL) at Setpoint 12. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP12(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP12_SHIFT)) & PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP12_MASK)

#define PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP13_MASK (0xF00000U)
#define PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP13_SHIFT (20U)
/*! MLPL_AT_SP13 - Memory Low Power Level (MLPL) at Setpoint 13. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP13(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP13_SHIFT)) & PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP13_MASK)

#define PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP14_MASK (0xF000000U)
#define PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP14_SHIFT (24U)
/*! MLPL_AT_SP14 - Memory Low Power Level (MLPL) at Setpoint 14. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP14(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP14_SHIFT)) & PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP14_MASK)

#define PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP15_MASK (0xF0000000U)
#define PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP15_SHIFT (28U)
/*! MLPL_AT_SP15 - Memory Low Power Level (MLPL) at Setpoint 15. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP15(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP15_SHIFT)) & PGMC_CPC_CPC_CACHE_SP_CTRL_1_MLPL_AT_SP15_MASK)
/*! @} */

/*! @name CPC_LMEM_MODE - CPC local memory Mode */
/*! @{ */

#define PGMC_CPC_CPC_LMEM_MODE_CTRL_MODE_MASK    (0x3U)
#define PGMC_CPC_CPC_LMEM_MODE_CTRL_MODE_SHIFT   (0U)
/*! CTRL_MODE - Control mode. This field is locked by AUTHEN_CTRL[LOCK_CFG] field.
 *  0b00..Not affected by any low power mode
 *  0b01..Controlled by CPU power mode of the domain
 *  0b10..Controlled by Setpoint
 *  0b11..Reserved
 */
#define PGMC_CPC_CPC_LMEM_MODE_CTRL_MODE(x)      (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_LMEM_MODE_CTRL_MODE_SHIFT)) & PGMC_CPC_CPC_LMEM_MODE_CTRL_MODE_MASK)
/*! @} */

/*! @name CPC_LMEM_CM_CTRL - CPC local memory CPU mode control */
/*! @{ */

#define PGMC_CPC_CPC_LMEM_CM_CTRL_MLPL_AT_RUN_MASK (0xFU)
#define PGMC_CPC_CPC_LMEM_CM_CTRL_MLPL_AT_RUN_SHIFT (0U)
/*! MLPL_AT_RUN - Memory Low Power Level (MLPL) at RUN mode */
#define PGMC_CPC_CPC_LMEM_CM_CTRL_MLPL_AT_RUN(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_LMEM_CM_CTRL_MLPL_AT_RUN_SHIFT)) & PGMC_CPC_CPC_LMEM_CM_CTRL_MLPL_AT_RUN_MASK)

#define PGMC_CPC_CPC_LMEM_CM_CTRL_MLPL_AT_WAIT_MASK (0xF0U)
#define PGMC_CPC_CPC_LMEM_CM_CTRL_MLPL_AT_WAIT_SHIFT (4U)
/*! MLPL_AT_WAIT - Memory Low Power Level (MLPL) at WAIT mode. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_LMEM_CM_CTRL_MLPL_AT_WAIT(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_LMEM_CM_CTRL_MLPL_AT_WAIT_SHIFT)) & PGMC_CPC_CPC_LMEM_CM_CTRL_MLPL_AT_WAIT_MASK)

#define PGMC_CPC_CPC_LMEM_CM_CTRL_MLPL_AT_STOP_MASK (0xF00U)
#define PGMC_CPC_CPC_LMEM_CM_CTRL_MLPL_AT_STOP_SHIFT (8U)
/*! MLPL_AT_STOP - Memory Low Power Level (MLPL) at STOP mode. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_LMEM_CM_CTRL_MLPL_AT_STOP(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_LMEM_CM_CTRL_MLPL_AT_STOP_SHIFT)) & PGMC_CPC_CPC_LMEM_CM_CTRL_MLPL_AT_STOP_MASK)

#define PGMC_CPC_CPC_LMEM_CM_CTRL_MLPL_AT_SUSPEND_MASK (0xF000U)
#define PGMC_CPC_CPC_LMEM_CM_CTRL_MLPL_AT_SUSPEND_SHIFT (12U)
/*! MLPL_AT_SUSPEND - Memory Low Power Level (MLPL) at SUSPEND mode. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_LMEM_CM_CTRL_MLPL_AT_SUSPEND(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_LMEM_CM_CTRL_MLPL_AT_SUSPEND_SHIFT)) & PGMC_CPC_CPC_LMEM_CM_CTRL_MLPL_AT_SUSPEND_MASK)

#define PGMC_CPC_CPC_LMEM_CM_CTRL_MLPL_SOFT_MASK (0x10000U)
#define PGMC_CPC_CPC_LMEM_CM_CTRL_MLPL_SOFT_SHIFT (16U)
/*! MLPL_SOFT - Memory Low Power Level (MLPL) software change request, keep 1 until MLPL transition complete */
#define PGMC_CPC_CPC_LMEM_CM_CTRL_MLPL_SOFT(x)   (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_LMEM_CM_CTRL_MLPL_SOFT_SHIFT)) & PGMC_CPC_CPC_LMEM_CM_CTRL_MLPL_SOFT_MASK)
/*! @} */

/*! @name CPC_LMEM_SP_CTRL_0 - CPC local memory Setpoint control 0 */
/*! @{ */

#define PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP0_MASK (0xFU)
#define PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP0_SHIFT (0U)
/*! MLPL_AT_SP0 - Memory Low Power Level (MLPL) at Setpoint 0. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP0(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP0_SHIFT)) & PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP0_MASK)

#define PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP1_MASK (0xF0U)
#define PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP1_SHIFT (4U)
/*! MLPL_AT_SP1 - Memory Low Power Level (MLPL) at Setpoint 1. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP1(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP1_SHIFT)) & PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP1_MASK)

#define PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP2_MASK (0xF00U)
#define PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP2_SHIFT (8U)
/*! MLPL_AT_SP2 - Memory Low Power Level (MLPL) at Setpoint 2. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP2(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP2_SHIFT)) & PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP2_MASK)

#define PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP3_MASK (0xF000U)
#define PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP3_SHIFT (12U)
/*! MLPL_AT_SP3 - Memory Low Power Level (MLPL) at Setpoint 3. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP3(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP3_SHIFT)) & PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP3_MASK)

#define PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP4_MASK (0xF0000U)
#define PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP4_SHIFT (16U)
/*! MLPL_AT_SP4 - Memory Low Power Level (MLPL) at Setpoint 4. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP4(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP4_SHIFT)) & PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP4_MASK)

#define PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP5_MASK (0xF00000U)
#define PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP5_SHIFT (20U)
/*! MLPL_AT_SP5 - Memory Low Power Level (MLPL) at Setpoint 5. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP5(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP5_SHIFT)) & PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP5_MASK)

#define PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP6_MASK (0xF000000U)
#define PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP6_SHIFT (24U)
/*! MLPL_AT_SP6 - Memory Low Power Level (MLPL) at Setpoint 6. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP6(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP6_SHIFT)) & PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP6_MASK)

#define PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP7_MASK (0xF0000000U)
#define PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP7_SHIFT (28U)
/*! MLPL_AT_SP7 - Memory Low Power Level (MLPL) at Setpoint 7. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP7(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP7_SHIFT)) & PGMC_CPC_CPC_LMEM_SP_CTRL_0_MLPL_AT_SP7_MASK)
/*! @} */

/*! @name CPC_LMEM_SP_CTRL_1 - CPC local memory Setpoint control 1 */
/*! @{ */

#define PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP8_MASK (0xFU)
#define PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP8_SHIFT (0U)
/*! MLPL_AT_SP8 - Memory Low Power Level (MLPL) at Setpoint 8. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP8(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP8_SHIFT)) & PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP8_MASK)

#define PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP9_MASK (0xF0U)
#define PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP9_SHIFT (4U)
/*! MLPL_AT_SP9 - Memory Low Power Level (MLPL) at Setpoint 9. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP9(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP9_SHIFT)) & PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP9_MASK)

#define PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP10_MASK (0xF00U)
#define PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP10_SHIFT (8U)
/*! MLPL_AT_SP10 - Memory Low Power Level (MLPL) at Setpoint 10. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP10(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP10_SHIFT)) & PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP10_MASK)

#define PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP11_MASK (0xF000U)
#define PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP11_SHIFT (12U)
/*! MLPL_AT_SP11 - Memory Low Power Level (MLPL) at Setpoint 11. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP11(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP11_SHIFT)) & PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP11_MASK)

#define PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP12_MASK (0xF0000U)
#define PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP12_SHIFT (16U)
/*! MLPL_AT_SP12 - Memory Low Power Level (MLPL) at Setpoint 12. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP12(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP12_SHIFT)) & PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP12_MASK)

#define PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP13_MASK (0xF00000U)
#define PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP13_SHIFT (20U)
/*! MLPL_AT_SP13 - Memory Low Power Level (MLPL) at Setpoint 13. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP13(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP13_SHIFT)) & PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP13_MASK)

#define PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP14_MASK (0xF000000U)
#define PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP14_SHIFT (24U)
/*! MLPL_AT_SP14 - Memory Low Power Level (MLPL) at Setpoint 14. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP14(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP14_SHIFT)) & PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP14_MASK)

#define PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP15_MASK (0xF0000000U)
#define PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP15_SHIFT (28U)
/*! MLPL_AT_SP15 - Memory Low Power Level (MLPL) at Setpoint 15. This field is locked by AUTHEN_CTRL[LOCK_CFG] field. */
#define PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP15(x) (((uint32_t)(((uint32_t)(x)) << PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP15_SHIFT)) & PGMC_CPC_CPC_LMEM_SP_CTRL_1_MLPL_AT_SP15_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group PGMC_CPC_Register_Masks */


/*!
 * @}
 */ /* end of group PGMC_CPC_Peripheral_Access_Layer */


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


#endif  /* PERI_PGMC_CPC_H_ */

