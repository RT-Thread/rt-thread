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
**         CMSIS Peripheral Access Layer for KEY_MANAGER
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
 * @file PERI_KEY_MANAGER.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for KEY_MANAGER
 *
 * CMSIS Peripheral Access Layer for KEY_MANAGER
 */

#if !defined(PERI_KEY_MANAGER_H_)
#define PERI_KEY_MANAGER_H_                      /**< Symbol preventing repeated inclusion */

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
   -- KEY_MANAGER Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup KEY_MANAGER_Peripheral_Access_Layer KEY_MANAGER Peripheral Access Layer
 * @{
 */

/** KEY_MANAGER - Register Layout Typedef */
typedef struct {
  __IO uint32_t MASTER_KEY_CTRL;                   /**< CSR Master Key Control Register, offset: 0x0 */
       uint8_t RESERVED_0[12];
  __IO uint32_t OTFAD1_KEY_CTRL;                   /**< CSR OTFAD-1 Key Control, offset: 0x10 */
       uint8_t RESERVED_1[4];
  __IO uint32_t OTFAD2_KEY_CTRL;                   /**< CSR OTFAD-2 Key Control, offset: 0x18 */
       uint8_t RESERVED_2[4];
  __IO uint32_t IEE_KEY_CTRL;                      /**< CSR IEE Key Control, offset: 0x20 */
       uint8_t RESERVED_3[12];
  __IO uint32_t PUF_KEY_CTRL;                      /**< CSR PUF Key Control, offset: 0x30 */
       uint8_t RESERVED_4[972];
  __IO uint32_t SLOT0_CTRL;                        /**< Slot 0 Control, offset: 0x400 */
  __IO uint32_t SLOT1_CTRL;                        /**< Slot1 Control, offset: 0x404 */
  __IO uint32_t SLOT2_CTRL;                        /**< Slot2 Control, offset: 0x408 */
  __IO uint32_t SLOT3_CTRL;                        /**< Slot3 Control, offset: 0x40C */
  __IO uint32_t SLOT4_CTRL;                        /**< Slot 4 Control, offset: 0x410 */
} KEY_MANAGER_Type;

/* ----------------------------------------------------------------------------
   -- KEY_MANAGER Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup KEY_MANAGER_Register_Masks KEY_MANAGER Register Masks
 * @{
 */

/*! @name MASTER_KEY_CTRL - CSR Master Key Control Register */
/*! @{ */

#define KEY_MANAGER_MASTER_KEY_CTRL_SELECT_MASK  (0x1U)
#define KEY_MANAGER_MASTER_KEY_CTRL_SELECT_SHIFT (0U)
/*! SELECT - Key select for SNVS OTPMK. Default value comes from FUSE_MASTER_KEY_SEL.
 *  0b0..select key from UDF
 *  0b1..If LOCK = 1, select key from PUF, otherwise select key from fuse (bypass the fuse OTPMK to SNVS)
 */
#define KEY_MANAGER_MASTER_KEY_CTRL_SELECT(x)    (((uint32_t)(((uint32_t)(x)) << KEY_MANAGER_MASTER_KEY_CTRL_SELECT_SHIFT)) & KEY_MANAGER_MASTER_KEY_CTRL_SELECT_MASK)

#define KEY_MANAGER_MASTER_KEY_CTRL_LOCK_MASK    (0x10000U)
#define KEY_MANAGER_MASTER_KEY_CTRL_LOCK_SHIFT   (16U)
/*! LOCK - lock this register, prevent from writing. Default value comes from FUSE_MASTER_KEY_SEL_LOCK.
 *  0b0..not locked
 *  0b1..locked
 */
#define KEY_MANAGER_MASTER_KEY_CTRL_LOCK(x)      (((uint32_t)(((uint32_t)(x)) << KEY_MANAGER_MASTER_KEY_CTRL_LOCK_SHIFT)) & KEY_MANAGER_MASTER_KEY_CTRL_LOCK_MASK)
/*! @} */

/*! @name OTFAD1_KEY_CTRL - CSR OTFAD-1 Key Control */
/*! @{ */

#define KEY_MANAGER_OTFAD1_KEY_CTRL_SELECT_MASK  (0x1U)
#define KEY_MANAGER_OTFAD1_KEY_CTRL_SELECT_SHIFT (0U)
/*! SELECT - key select for OTFAD-1. Default value comes from FUSE_OTFAD1_KEY_SEL.
 *  0b0..Select key from OCOTP USER_KEY5
 *  0b1..If PUF_KEY_CTRL[LOCK] is 1, select key from PUF, otherwise select key from OCOTP USER_KEY5
 */
#define KEY_MANAGER_OTFAD1_KEY_CTRL_SELECT(x)    (((uint32_t)(((uint32_t)(x)) << KEY_MANAGER_OTFAD1_KEY_CTRL_SELECT_SHIFT)) & KEY_MANAGER_OTFAD1_KEY_CTRL_SELECT_MASK)

#define KEY_MANAGER_OTFAD1_KEY_CTRL_LOCK_MASK    (0x10000U)
#define KEY_MANAGER_OTFAD1_KEY_CTRL_LOCK_SHIFT   (16U)
/*! LOCK - lock this register, prevent from writing. Default value comes from FUSE_OTFAD1_KEY_SEL_LOCK.
 *  0b0..not locked
 *  0b1..locked
 */
#define KEY_MANAGER_OTFAD1_KEY_CTRL_LOCK(x)      (((uint32_t)(((uint32_t)(x)) << KEY_MANAGER_OTFAD1_KEY_CTRL_LOCK_SHIFT)) & KEY_MANAGER_OTFAD1_KEY_CTRL_LOCK_MASK)
/*! @} */

/*! @name OTFAD2_KEY_CTRL - CSR OTFAD-2 Key Control */
/*! @{ */

#define KEY_MANAGER_OTFAD2_KEY_CTRL_SELECT_MASK  (0x1U)
#define KEY_MANAGER_OTFAD2_KEY_CTRL_SELECT_SHIFT (0U)
/*! SELECT - key select for OTFAD-2. Default value comes from FUSE_OTFAD1_KEY_SEL.
 *  0b0..select key from OCOTP USER_KEY5
 *  0b1..If PUF_KEY_CTRL[LOCK] is 1, select key from PUF, otherwise select key from OCOTP USER_KEY5
 */
#define KEY_MANAGER_OTFAD2_KEY_CTRL_SELECT(x)    (((uint32_t)(((uint32_t)(x)) << KEY_MANAGER_OTFAD2_KEY_CTRL_SELECT_SHIFT)) & KEY_MANAGER_OTFAD2_KEY_CTRL_SELECT_MASK)

#define KEY_MANAGER_OTFAD2_KEY_CTRL_LOCK_MASK    (0x10000U)
#define KEY_MANAGER_OTFAD2_KEY_CTRL_LOCK_SHIFT   (16U)
/*! LOCK - lock this register, prevent from writing. Default value comes from FUSE_OTFAD2_KEY_SEL_LOCK.
 *  0b0..not locked
 *  0b1..locked
 */
#define KEY_MANAGER_OTFAD2_KEY_CTRL_LOCK(x)      (((uint32_t)(((uint32_t)(x)) << KEY_MANAGER_OTFAD2_KEY_CTRL_LOCK_SHIFT)) & KEY_MANAGER_OTFAD2_KEY_CTRL_LOCK_MASK)
/*! @} */

/*! @name IEE_KEY_CTRL - CSR IEE Key Control */
/*! @{ */

#define KEY_MANAGER_IEE_KEY_CTRL_RELOAD_MASK     (0x1U)
#define KEY_MANAGER_IEE_KEY_CTRL_RELOAD_SHIFT    (0U)
/*! RELOAD - Restart load key signal for IEE
 *  0b0..Do nothing
 *  0b1..Restart IEE key load flow
 */
#define KEY_MANAGER_IEE_KEY_CTRL_RELOAD(x)       (((uint32_t)(((uint32_t)(x)) << KEY_MANAGER_IEE_KEY_CTRL_RELOAD_SHIFT)) & KEY_MANAGER_IEE_KEY_CTRL_RELOAD_MASK)
/*! @} */

/*! @name PUF_KEY_CTRL - CSR PUF Key Control */
/*! @{ */

#define KEY_MANAGER_PUF_KEY_CTRL_LOCK_MASK       (0x1U)
#define KEY_MANAGER_PUF_KEY_CTRL_LOCK_SHIFT      (0U)
/*! LOCK - Lock signal for key select
 *  0b0..Do not lock the key select
 *  0b1..Lock the key select to select key from PUF, otherwise bypass key from OCOPT and do not lock. Once it has
 *       been set to 1, it cannot be reset manually. It will be set to 0 when the IEE key reload operation is done.
 */
#define KEY_MANAGER_PUF_KEY_CTRL_LOCK(x)         (((uint32_t)(((uint32_t)(x)) << KEY_MANAGER_PUF_KEY_CTRL_LOCK_SHIFT)) & KEY_MANAGER_PUF_KEY_CTRL_LOCK_MASK)
/*! @} */

/*! @name SLOT0_CTRL - Slot 0 Control */
/*! @{ */

#define KEY_MANAGER_SLOT0_CTRL_WHITE_LIST_MASK   (0xFU)
#define KEY_MANAGER_SLOT0_CTRL_WHITE_LIST_SHIFT  (0U)
/*! WHITE_LIST - Whitelist */
#define KEY_MANAGER_SLOT0_CTRL_WHITE_LIST(x)     (((uint32_t)(((uint32_t)(x)) << KEY_MANAGER_SLOT0_CTRL_WHITE_LIST_SHIFT)) & KEY_MANAGER_SLOT0_CTRL_WHITE_LIST_MASK)

#define KEY_MANAGER_SLOT0_CTRL_LOCK_LIST_MASK    (0x8000U)
#define KEY_MANAGER_SLOT0_CTRL_LOCK_LIST_SHIFT   (15U)
/*! LOCK_LIST - Lock whitelist
 *  0b0..Whitelist is not locked
 *  0b1..Whitelist is locked
 */
#define KEY_MANAGER_SLOT0_CTRL_LOCK_LIST(x)      (((uint32_t)(((uint32_t)(x)) << KEY_MANAGER_SLOT0_CTRL_LOCK_LIST_SHIFT)) & KEY_MANAGER_SLOT0_CTRL_LOCK_LIST_MASK)

#define KEY_MANAGER_SLOT0_CTRL_TZ_NS_MASK        (0x10000U)
#define KEY_MANAGER_SLOT0_CTRL_TZ_NS_SHIFT       (16U)
/*! TZ_NS - Allow non-secure write access to this register and the slot it controls
 *  0b0..Do not allow non-secure write access
 *  0b1..Allow non-secure write access
 */
#define KEY_MANAGER_SLOT0_CTRL_TZ_NS(x)          (((uint32_t)(((uint32_t)(x)) << KEY_MANAGER_SLOT0_CTRL_TZ_NS_SHIFT)) & KEY_MANAGER_SLOT0_CTRL_TZ_NS_MASK)

#define KEY_MANAGER_SLOT0_CTRL_TZ_USER_MASK      (0x20000U)
#define KEY_MANAGER_SLOT0_CTRL_TZ_USER_SHIFT     (17U)
/*! TZ_USER - Allow user write access to this register and the slot it controls
 *  0b0..Do not allow user write access
 *  0b1..Allow user write access
 */
#define KEY_MANAGER_SLOT0_CTRL_TZ_USER(x)        (((uint32_t)(((uint32_t)(x)) << KEY_MANAGER_SLOT0_CTRL_TZ_USER_SHIFT)) & KEY_MANAGER_SLOT0_CTRL_TZ_USER_MASK)

#define KEY_MANAGER_SLOT0_CTRL_LOCK_CONTROL_MASK (0x80000000U)
#define KEY_MANAGER_SLOT0_CTRL_LOCK_CONTROL_SHIFT (31U)
/*! LOCK_CONTROL - Lock control of this slot
 *  0b0..Do not lock the control register of this slot
 *  0b1..Lock the control register of this slot
 */
#define KEY_MANAGER_SLOT0_CTRL_LOCK_CONTROL(x)   (((uint32_t)(((uint32_t)(x)) << KEY_MANAGER_SLOT0_CTRL_LOCK_CONTROL_SHIFT)) & KEY_MANAGER_SLOT0_CTRL_LOCK_CONTROL_MASK)
/*! @} */

/*! @name SLOT1_CTRL - Slot1 Control */
/*! @{ */

#define KEY_MANAGER_SLOT1_CTRL_WHITE_LIST_MASK   (0xFU)
#define KEY_MANAGER_SLOT1_CTRL_WHITE_LIST_SHIFT  (0U)
/*! WHITE_LIST - Whitelist */
#define KEY_MANAGER_SLOT1_CTRL_WHITE_LIST(x)     (((uint32_t)(((uint32_t)(x)) << KEY_MANAGER_SLOT1_CTRL_WHITE_LIST_SHIFT)) & KEY_MANAGER_SLOT1_CTRL_WHITE_LIST_MASK)

#define KEY_MANAGER_SLOT1_CTRL_LOCK_LIST_MASK    (0x8000U)
#define KEY_MANAGER_SLOT1_CTRL_LOCK_LIST_SHIFT   (15U)
/*! LOCK_LIST - Lock whitelist
 *  0b0..Whitelist is not locked
 *  0b1..Whitelist is locked
 */
#define KEY_MANAGER_SLOT1_CTRL_LOCK_LIST(x)      (((uint32_t)(((uint32_t)(x)) << KEY_MANAGER_SLOT1_CTRL_LOCK_LIST_SHIFT)) & KEY_MANAGER_SLOT1_CTRL_LOCK_LIST_MASK)

#define KEY_MANAGER_SLOT1_CTRL_TZ_NS_MASK        (0x10000U)
#define KEY_MANAGER_SLOT1_CTRL_TZ_NS_SHIFT       (16U)
/*! TZ_NS - Allow non-secure write access to this register and the slot it controls
 *  0b0..Do not allow non-secure write access
 *  0b1..Allow non-secure write access
 */
#define KEY_MANAGER_SLOT1_CTRL_TZ_NS(x)          (((uint32_t)(((uint32_t)(x)) << KEY_MANAGER_SLOT1_CTRL_TZ_NS_SHIFT)) & KEY_MANAGER_SLOT1_CTRL_TZ_NS_MASK)

#define KEY_MANAGER_SLOT1_CTRL_TZ_USER_MASK      (0x20000U)
#define KEY_MANAGER_SLOT1_CTRL_TZ_USER_SHIFT     (17U)
/*! TZ_USER - Allow user write access to this register and the slot it controls
 *  0b0..Do not allow user write access
 *  0b1..Allow user write access
 */
#define KEY_MANAGER_SLOT1_CTRL_TZ_USER(x)        (((uint32_t)(((uint32_t)(x)) << KEY_MANAGER_SLOT1_CTRL_TZ_USER_SHIFT)) & KEY_MANAGER_SLOT1_CTRL_TZ_USER_MASK)

#define KEY_MANAGER_SLOT1_CTRL_LOCK_CONTROL_MASK (0x80000000U)
#define KEY_MANAGER_SLOT1_CTRL_LOCK_CONTROL_SHIFT (31U)
/*! LOCK_CONTROL - Lock control of this slot
 *  0b0..Do not lock the control register of this slot
 *  0b1..Lock the control register of this slot
 */
#define KEY_MANAGER_SLOT1_CTRL_LOCK_CONTROL(x)   (((uint32_t)(((uint32_t)(x)) << KEY_MANAGER_SLOT1_CTRL_LOCK_CONTROL_SHIFT)) & KEY_MANAGER_SLOT1_CTRL_LOCK_CONTROL_MASK)
/*! @} */

/*! @name SLOT2_CTRL - Slot2 Control */
/*! @{ */

#define KEY_MANAGER_SLOT2_CTRL_WHITE_LIST_MASK   (0xFU)
#define KEY_MANAGER_SLOT2_CTRL_WHITE_LIST_SHIFT  (0U)
/*! WHITE_LIST - Whitelist */
#define KEY_MANAGER_SLOT2_CTRL_WHITE_LIST(x)     (((uint32_t)(((uint32_t)(x)) << KEY_MANAGER_SLOT2_CTRL_WHITE_LIST_SHIFT)) & KEY_MANAGER_SLOT2_CTRL_WHITE_LIST_MASK)

#define KEY_MANAGER_SLOT2_CTRL_LOCK_LIST_MASK    (0x8000U)
#define KEY_MANAGER_SLOT2_CTRL_LOCK_LIST_SHIFT   (15U)
/*! LOCK_LIST - Lock whitelist
 *  0b0..Whitelist is not locked
 *  0b1..Whitelist is locked
 */
#define KEY_MANAGER_SLOT2_CTRL_LOCK_LIST(x)      (((uint32_t)(((uint32_t)(x)) << KEY_MANAGER_SLOT2_CTRL_LOCK_LIST_SHIFT)) & KEY_MANAGER_SLOT2_CTRL_LOCK_LIST_MASK)

#define KEY_MANAGER_SLOT2_CTRL_TZ_NS_MASK        (0x10000U)
#define KEY_MANAGER_SLOT2_CTRL_TZ_NS_SHIFT       (16U)
/*! TZ_NS - Allow non-secure write access to this register and the slot it controls
 *  0b0..Do not allow non-secure write access
 *  0b1..Allow non-secure write access
 */
#define KEY_MANAGER_SLOT2_CTRL_TZ_NS(x)          (((uint32_t)(((uint32_t)(x)) << KEY_MANAGER_SLOT2_CTRL_TZ_NS_SHIFT)) & KEY_MANAGER_SLOT2_CTRL_TZ_NS_MASK)

#define KEY_MANAGER_SLOT2_CTRL_TZ_USER_MASK      (0x20000U)
#define KEY_MANAGER_SLOT2_CTRL_TZ_USER_SHIFT     (17U)
/*! TZ_USER - Allow user write access to this register and the slot it controls
 *  0b0..Do not allow user write access
 *  0b1..Allow user write access
 */
#define KEY_MANAGER_SLOT2_CTRL_TZ_USER(x)        (((uint32_t)(((uint32_t)(x)) << KEY_MANAGER_SLOT2_CTRL_TZ_USER_SHIFT)) & KEY_MANAGER_SLOT2_CTRL_TZ_USER_MASK)

#define KEY_MANAGER_SLOT2_CTRL_LOCK_CONTROL_MASK (0x80000000U)
#define KEY_MANAGER_SLOT2_CTRL_LOCK_CONTROL_SHIFT (31U)
/*! LOCK_CONTROL - Lock control of this slot
 *  0b0..Do not lock the control register of this slot
 *  0b1..Lock the control register of this slot
 */
#define KEY_MANAGER_SLOT2_CTRL_LOCK_CONTROL(x)   (((uint32_t)(((uint32_t)(x)) << KEY_MANAGER_SLOT2_CTRL_LOCK_CONTROL_SHIFT)) & KEY_MANAGER_SLOT2_CTRL_LOCK_CONTROL_MASK)
/*! @} */

/*! @name SLOT3_CTRL - Slot3 Control */
/*! @{ */

#define KEY_MANAGER_SLOT3_CTRL_WHITE_LIST_MASK   (0xFU)
#define KEY_MANAGER_SLOT3_CTRL_WHITE_LIST_SHIFT  (0U)
/*! WHITE_LIST - Whitelist */
#define KEY_MANAGER_SLOT3_CTRL_WHITE_LIST(x)     (((uint32_t)(((uint32_t)(x)) << KEY_MANAGER_SLOT3_CTRL_WHITE_LIST_SHIFT)) & KEY_MANAGER_SLOT3_CTRL_WHITE_LIST_MASK)

#define KEY_MANAGER_SLOT3_CTRL_LOCK_LIST_MASK    (0x8000U)
#define KEY_MANAGER_SLOT3_CTRL_LOCK_LIST_SHIFT   (15U)
/*! LOCK_LIST - Lock whitelist
 *  0b0..Whitelist is not locked
 *  0b1..Whitelist is locked
 */
#define KEY_MANAGER_SLOT3_CTRL_LOCK_LIST(x)      (((uint32_t)(((uint32_t)(x)) << KEY_MANAGER_SLOT3_CTRL_LOCK_LIST_SHIFT)) & KEY_MANAGER_SLOT3_CTRL_LOCK_LIST_MASK)

#define KEY_MANAGER_SLOT3_CTRL_TZ_NS_MASK        (0x10000U)
#define KEY_MANAGER_SLOT3_CTRL_TZ_NS_SHIFT       (16U)
/*! TZ_NS - Allow non-secure write access to this register and the slot it controls
 *  0b0..Do not allow non-secure write access
 *  0b1..Allow non-secure write access
 */
#define KEY_MANAGER_SLOT3_CTRL_TZ_NS(x)          (((uint32_t)(((uint32_t)(x)) << KEY_MANAGER_SLOT3_CTRL_TZ_NS_SHIFT)) & KEY_MANAGER_SLOT3_CTRL_TZ_NS_MASK)

#define KEY_MANAGER_SLOT3_CTRL_TZ_USER_MASK      (0x20000U)
#define KEY_MANAGER_SLOT3_CTRL_TZ_USER_SHIFT     (17U)
/*! TZ_USER - Allow user write access to this register and the slot it controls
 *  0b0..Do not allow user write access
 *  0b1..Allow user write access
 */
#define KEY_MANAGER_SLOT3_CTRL_TZ_USER(x)        (((uint32_t)(((uint32_t)(x)) << KEY_MANAGER_SLOT3_CTRL_TZ_USER_SHIFT)) & KEY_MANAGER_SLOT3_CTRL_TZ_USER_MASK)

#define KEY_MANAGER_SLOT3_CTRL_LOCK_CONTROL_MASK (0x80000000U)
#define KEY_MANAGER_SLOT3_CTRL_LOCK_CONTROL_SHIFT (31U)
/*! LOCK_CONTROL - Lock control of this slot
 *  0b0..Do not lock the control register of this slot
 *  0b1..Lock the control register of this slot
 */
#define KEY_MANAGER_SLOT3_CTRL_LOCK_CONTROL(x)   (((uint32_t)(((uint32_t)(x)) << KEY_MANAGER_SLOT3_CTRL_LOCK_CONTROL_SHIFT)) & KEY_MANAGER_SLOT3_CTRL_LOCK_CONTROL_MASK)
/*! @} */

/*! @name SLOT4_CTRL - Slot 4 Control */
/*! @{ */

#define KEY_MANAGER_SLOT4_CTRL_WHITE_LIST_MASK   (0xFU)
#define KEY_MANAGER_SLOT4_CTRL_WHITE_LIST_SHIFT  (0U)
/*! WHITE_LIST - Whitelist */
#define KEY_MANAGER_SLOT4_CTRL_WHITE_LIST(x)     (((uint32_t)(((uint32_t)(x)) << KEY_MANAGER_SLOT4_CTRL_WHITE_LIST_SHIFT)) & KEY_MANAGER_SLOT4_CTRL_WHITE_LIST_MASK)

#define KEY_MANAGER_SLOT4_CTRL_LOCK_LIST_MASK    (0x8000U)
#define KEY_MANAGER_SLOT4_CTRL_LOCK_LIST_SHIFT   (15U)
/*! LOCK_LIST - Lock whitelist
 *  0b0..Whitelist is not locked
 *  0b1..Whitelist is locked
 */
#define KEY_MANAGER_SLOT4_CTRL_LOCK_LIST(x)      (((uint32_t)(((uint32_t)(x)) << KEY_MANAGER_SLOT4_CTRL_LOCK_LIST_SHIFT)) & KEY_MANAGER_SLOT4_CTRL_LOCK_LIST_MASK)

#define KEY_MANAGER_SLOT4_CTRL_TZ_NS_MASK        (0x10000U)
#define KEY_MANAGER_SLOT4_CTRL_TZ_NS_SHIFT       (16U)
/*! TZ_NS - Allow non-secure write access to this register and the slot it controls
 *  0b0..Do not allow non-secure write access
 *  0b1..Allow non-secure write access
 */
#define KEY_MANAGER_SLOT4_CTRL_TZ_NS(x)          (((uint32_t)(((uint32_t)(x)) << KEY_MANAGER_SLOT4_CTRL_TZ_NS_SHIFT)) & KEY_MANAGER_SLOT4_CTRL_TZ_NS_MASK)

#define KEY_MANAGER_SLOT4_CTRL_TZ_USER_MASK      (0x20000U)
#define KEY_MANAGER_SLOT4_CTRL_TZ_USER_SHIFT     (17U)
/*! TZ_USER - Allow user write access to this register and the slot it controls
 *  0b0..Do not allow user write access
 *  0b1..Allow user write access
 */
#define KEY_MANAGER_SLOT4_CTRL_TZ_USER(x)        (((uint32_t)(((uint32_t)(x)) << KEY_MANAGER_SLOT4_CTRL_TZ_USER_SHIFT)) & KEY_MANAGER_SLOT4_CTRL_TZ_USER_MASK)

#define KEY_MANAGER_SLOT4_CTRL_LOCK_CONTROL_MASK (0x80000000U)
#define KEY_MANAGER_SLOT4_CTRL_LOCK_CONTROL_SHIFT (31U)
/*! LOCK_CONTROL - Lock control of this slot
 *  0b0..Do not lock the control register of this slot
 *  0b1..Lock the control register of this slot
 */
#define KEY_MANAGER_SLOT4_CTRL_LOCK_CONTROL(x)   (((uint32_t)(((uint32_t)(x)) << KEY_MANAGER_SLOT4_CTRL_LOCK_CONTROL_SHIFT)) & KEY_MANAGER_SLOT4_CTRL_LOCK_CONTROL_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group KEY_MANAGER_Register_Masks */


/*!
 * @}
 */ /* end of group KEY_MANAGER_Peripheral_Access_Layer */


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


#endif  /* PERI_KEY_MANAGER_H_ */

