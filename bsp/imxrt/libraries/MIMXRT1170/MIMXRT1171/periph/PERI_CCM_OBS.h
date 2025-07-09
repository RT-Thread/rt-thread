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
**         CMSIS Peripheral Access Layer for CCM_OBS
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
 * @file PERI_CCM_OBS.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for CCM_OBS
 *
 * CMSIS Peripheral Access Layer for CCM_OBS
 */

#if !defined(PERI_CCM_OBS_H_)
#define PERI_CCM_OBS_H_                          /**< Symbol preventing repeated inclusion */

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
   -- CCM_OBS Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CCM_OBS_Peripheral_Access_Layer CCM_OBS Peripheral Access Layer
 * @{
 */

/** CCM_OBS - Size of Registers Arrays */
#define CCM_OBS_OBSERVE_COUNT                     6u

/** CCM_OBS - Register Layout Typedef */
typedef struct {
  struct {                                         /* offset: 0x0, array step: 0x80 */
    __IO uint32_t CONTROL;                           /**< Observe control, array offset: 0x0, array step: 0x80 */
    __IO uint32_t CONTROL_SET;                       /**< Observe control, array offset: 0x4, array step: 0x80 */
    __IO uint32_t CONTROL_CLR;                       /**< Observe control, array offset: 0x8, array step: 0x80 */
    __IO uint32_t CONTROL_TOG;                       /**< Observe control, array offset: 0xC, array step: 0x80 */
         uint8_t RESERVED_0[16];
    __I  uint32_t STATUS0;                           /**< Observe status, array offset: 0x20, array step: 0x80 */
         uint8_t RESERVED_1[12];
    __IO uint32_t AUTHEN;                            /**< Observe access control, array offset: 0x30, array step: 0x80 */
    __IO uint32_t AUTHEN_SET;                        /**< Observe access control, array offset: 0x34, array step: 0x80 */
    __IO uint32_t AUTHEN_CLR;                        /**< Observe access control, array offset: 0x38, array step: 0x80 */
    __IO uint32_t AUTHEN_TOG;                        /**< Observe access control, array offset: 0x3C, array step: 0x80 */
    __I  uint32_t FREQUENCY_CURRENT;                 /**< Current frequency detected, array offset: 0x40, array step: 0x80 */
    __I  uint32_t FREQUENCY_MIN;                     /**< Minimum frequency detected, array offset: 0x44, array step: 0x80 */
    __I  uint32_t FREQUENCY_MAX;                     /**< Maximum frequency detected, array offset: 0x48, array step: 0x80 */
         uint8_t RESERVED_2[52];
  } OBSERVE[CCM_OBS_OBSERVE_COUNT];
} CCM_OBS_Type;

/* ----------------------------------------------------------------------------
   -- CCM_OBS Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup CCM_OBS_Register_Masks CCM_OBS Register Masks
 * @{
 */

/*! @name OBSERVE_CONTROL - Observe control */
/*! @{ */

#define CCM_OBS_OBSERVE_CONTROL_SELECT_MASK      (0x1FFU)
#define CCM_OBS_OBSERVE_CONTROL_SELECT_SHIFT     (0U)
/*! SELECT - Observe signal selector */
#define CCM_OBS_OBSERVE_CONTROL_SELECT(x)        (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_CONTROL_SELECT_SHIFT)) & CCM_OBS_OBSERVE_CONTROL_SELECT_MASK)

#define CCM_OBS_OBSERVE_CONTROL_RAW_MASK         (0x1000U)
#define CCM_OBS_OBSERVE_CONTROL_RAW_SHIFT        (12U)
/*! RAW - Observe raw signal
 *  0b0..Select divided signal.
 *  0b1..Select raw signal.
 */
#define CCM_OBS_OBSERVE_CONTROL_RAW(x)           (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_CONTROL_RAW_SHIFT)) & CCM_OBS_OBSERVE_CONTROL_RAW_MASK)

#define CCM_OBS_OBSERVE_CONTROL_INV_MASK         (0x2000U)
#define CCM_OBS_OBSERVE_CONTROL_INV_SHIFT        (13U)
/*! INV - Invert
 *  0b0..Clock phase remain same.
 *  0b1..Invert clock phase before measurement or send to IO.
 */
#define CCM_OBS_OBSERVE_CONTROL_INV(x)           (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_CONTROL_INV_SHIFT)) & CCM_OBS_OBSERVE_CONTROL_INV_MASK)

#define CCM_OBS_OBSERVE_CONTROL_RESET_MASK       (0x8000U)
#define CCM_OBS_OBSERVE_CONTROL_RESET_SHIFT      (15U)
/*! RESET - Reset observe divider
 *  0b0..No reset
 *  0b1..Reset observe divider
 */
#define CCM_OBS_OBSERVE_CONTROL_RESET(x)         (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_CONTROL_RESET_SHIFT)) & CCM_OBS_OBSERVE_CONTROL_RESET_MASK)

#define CCM_OBS_OBSERVE_CONTROL_DIVIDE_MASK      (0xFF0000U)
#define CCM_OBS_OBSERVE_CONTROL_DIVIDE_SHIFT     (16U)
/*! DIVIDE - Divider for observe signal */
#define CCM_OBS_OBSERVE_CONTROL_DIVIDE(x)        (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_CONTROL_DIVIDE_SHIFT)) & CCM_OBS_OBSERVE_CONTROL_DIVIDE_MASK)

#define CCM_OBS_OBSERVE_CONTROL_OFF_MASK         (0x1000000U)
#define CCM_OBS_OBSERVE_CONTROL_OFF_SHIFT        (24U)
/*! OFF - Turn off
 *  0b0..observe slice is on
 *  0b1..observe slice is off
 */
#define CCM_OBS_OBSERVE_CONTROL_OFF(x)           (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_CONTROL_OFF_SHIFT)) & CCM_OBS_OBSERVE_CONTROL_OFF_MASK)
/*! @} */

/* The count of CCM_OBS_OBSERVE_CONTROL */
#define CCM_OBS_OBSERVE_CONTROL_COUNT            (6U)

/*! @name OBSERVE_CONTROL_SET - Observe control */
/*! @{ */

#define CCM_OBS_OBSERVE_CONTROL_SET_SELECT_MASK  (0x1FFU)
#define CCM_OBS_OBSERVE_CONTROL_SET_SELECT_SHIFT (0U)
/*! SELECT - Observe signal selector */
#define CCM_OBS_OBSERVE_CONTROL_SET_SELECT(x)    (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_CONTROL_SET_SELECT_SHIFT)) & CCM_OBS_OBSERVE_CONTROL_SET_SELECT_MASK)

#define CCM_OBS_OBSERVE_CONTROL_SET_RAW_MASK     (0x1000U)
#define CCM_OBS_OBSERVE_CONTROL_SET_RAW_SHIFT    (12U)
/*! RAW - Observe raw signal */
#define CCM_OBS_OBSERVE_CONTROL_SET_RAW(x)       (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_CONTROL_SET_RAW_SHIFT)) & CCM_OBS_OBSERVE_CONTROL_SET_RAW_MASK)

#define CCM_OBS_OBSERVE_CONTROL_SET_INV_MASK     (0x2000U)
#define CCM_OBS_OBSERVE_CONTROL_SET_INV_SHIFT    (13U)
/*! INV - Invert */
#define CCM_OBS_OBSERVE_CONTROL_SET_INV(x)       (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_CONTROL_SET_INV_SHIFT)) & CCM_OBS_OBSERVE_CONTROL_SET_INV_MASK)

#define CCM_OBS_OBSERVE_CONTROL_SET_RESET_MASK   (0x8000U)
#define CCM_OBS_OBSERVE_CONTROL_SET_RESET_SHIFT  (15U)
/*! RESET - Reset observe divider */
#define CCM_OBS_OBSERVE_CONTROL_SET_RESET(x)     (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_CONTROL_SET_RESET_SHIFT)) & CCM_OBS_OBSERVE_CONTROL_SET_RESET_MASK)

#define CCM_OBS_OBSERVE_CONTROL_SET_DIVIDE_MASK  (0xFF0000U)
#define CCM_OBS_OBSERVE_CONTROL_SET_DIVIDE_SHIFT (16U)
/*! DIVIDE - Divider for observe signal */
#define CCM_OBS_OBSERVE_CONTROL_SET_DIVIDE(x)    (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_CONTROL_SET_DIVIDE_SHIFT)) & CCM_OBS_OBSERVE_CONTROL_SET_DIVIDE_MASK)

#define CCM_OBS_OBSERVE_CONTROL_SET_OFF_MASK     (0x1000000U)
#define CCM_OBS_OBSERVE_CONTROL_SET_OFF_SHIFT    (24U)
/*! OFF - Turn off */
#define CCM_OBS_OBSERVE_CONTROL_SET_OFF(x)       (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_CONTROL_SET_OFF_SHIFT)) & CCM_OBS_OBSERVE_CONTROL_SET_OFF_MASK)
/*! @} */

/* The count of CCM_OBS_OBSERVE_CONTROL_SET */
#define CCM_OBS_OBSERVE_CONTROL_SET_COUNT        (6U)

/*! @name OBSERVE_CONTROL_CLR - Observe control */
/*! @{ */

#define CCM_OBS_OBSERVE_CONTROL_CLR_SELECT_MASK  (0x1FFU)
#define CCM_OBS_OBSERVE_CONTROL_CLR_SELECT_SHIFT (0U)
/*! SELECT - Observe signal selector */
#define CCM_OBS_OBSERVE_CONTROL_CLR_SELECT(x)    (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_CONTROL_CLR_SELECT_SHIFT)) & CCM_OBS_OBSERVE_CONTROL_CLR_SELECT_MASK)

#define CCM_OBS_OBSERVE_CONTROL_CLR_RAW_MASK     (0x1000U)
#define CCM_OBS_OBSERVE_CONTROL_CLR_RAW_SHIFT    (12U)
/*! RAW - Observe raw signal */
#define CCM_OBS_OBSERVE_CONTROL_CLR_RAW(x)       (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_CONTROL_CLR_RAW_SHIFT)) & CCM_OBS_OBSERVE_CONTROL_CLR_RAW_MASK)

#define CCM_OBS_OBSERVE_CONTROL_CLR_INV_MASK     (0x2000U)
#define CCM_OBS_OBSERVE_CONTROL_CLR_INV_SHIFT    (13U)
/*! INV - Invert */
#define CCM_OBS_OBSERVE_CONTROL_CLR_INV(x)       (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_CONTROL_CLR_INV_SHIFT)) & CCM_OBS_OBSERVE_CONTROL_CLR_INV_MASK)

#define CCM_OBS_OBSERVE_CONTROL_CLR_RESET_MASK   (0x8000U)
#define CCM_OBS_OBSERVE_CONTROL_CLR_RESET_SHIFT  (15U)
/*! RESET - Reset observe divider */
#define CCM_OBS_OBSERVE_CONTROL_CLR_RESET(x)     (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_CONTROL_CLR_RESET_SHIFT)) & CCM_OBS_OBSERVE_CONTROL_CLR_RESET_MASK)

#define CCM_OBS_OBSERVE_CONTROL_CLR_DIVIDE_MASK  (0xFF0000U)
#define CCM_OBS_OBSERVE_CONTROL_CLR_DIVIDE_SHIFT (16U)
/*! DIVIDE - Divider for observe signal */
#define CCM_OBS_OBSERVE_CONTROL_CLR_DIVIDE(x)    (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_CONTROL_CLR_DIVIDE_SHIFT)) & CCM_OBS_OBSERVE_CONTROL_CLR_DIVIDE_MASK)

#define CCM_OBS_OBSERVE_CONTROL_CLR_OFF_MASK     (0x1000000U)
#define CCM_OBS_OBSERVE_CONTROL_CLR_OFF_SHIFT    (24U)
/*! OFF - Turn off */
#define CCM_OBS_OBSERVE_CONTROL_CLR_OFF(x)       (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_CONTROL_CLR_OFF_SHIFT)) & CCM_OBS_OBSERVE_CONTROL_CLR_OFF_MASK)
/*! @} */

/* The count of CCM_OBS_OBSERVE_CONTROL_CLR */
#define CCM_OBS_OBSERVE_CONTROL_CLR_COUNT        (6U)

/*! @name OBSERVE_CONTROL_TOG - Observe control */
/*! @{ */

#define CCM_OBS_OBSERVE_CONTROL_TOG_SELECT_MASK  (0x1FFU)
#define CCM_OBS_OBSERVE_CONTROL_TOG_SELECT_SHIFT (0U)
/*! SELECT - Observe signal selector */
#define CCM_OBS_OBSERVE_CONTROL_TOG_SELECT(x)    (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_CONTROL_TOG_SELECT_SHIFT)) & CCM_OBS_OBSERVE_CONTROL_TOG_SELECT_MASK)

#define CCM_OBS_OBSERVE_CONTROL_TOG_RAW_MASK     (0x1000U)
#define CCM_OBS_OBSERVE_CONTROL_TOG_RAW_SHIFT    (12U)
/*! RAW - Observe raw signal */
#define CCM_OBS_OBSERVE_CONTROL_TOG_RAW(x)       (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_CONTROL_TOG_RAW_SHIFT)) & CCM_OBS_OBSERVE_CONTROL_TOG_RAW_MASK)

#define CCM_OBS_OBSERVE_CONTROL_TOG_INV_MASK     (0x2000U)
#define CCM_OBS_OBSERVE_CONTROL_TOG_INV_SHIFT    (13U)
/*! INV - Invert */
#define CCM_OBS_OBSERVE_CONTROL_TOG_INV(x)       (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_CONTROL_TOG_INV_SHIFT)) & CCM_OBS_OBSERVE_CONTROL_TOG_INV_MASK)

#define CCM_OBS_OBSERVE_CONTROL_TOG_RESET_MASK   (0x8000U)
#define CCM_OBS_OBSERVE_CONTROL_TOG_RESET_SHIFT  (15U)
/*! RESET - Reset observe divider */
#define CCM_OBS_OBSERVE_CONTROL_TOG_RESET(x)     (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_CONTROL_TOG_RESET_SHIFT)) & CCM_OBS_OBSERVE_CONTROL_TOG_RESET_MASK)

#define CCM_OBS_OBSERVE_CONTROL_TOG_DIVIDE_MASK  (0xFF0000U)
#define CCM_OBS_OBSERVE_CONTROL_TOG_DIVIDE_SHIFT (16U)
/*! DIVIDE - Divider for observe signal */
#define CCM_OBS_OBSERVE_CONTROL_TOG_DIVIDE(x)    (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_CONTROL_TOG_DIVIDE_SHIFT)) & CCM_OBS_OBSERVE_CONTROL_TOG_DIVIDE_MASK)

#define CCM_OBS_OBSERVE_CONTROL_TOG_OFF_MASK     (0x1000000U)
#define CCM_OBS_OBSERVE_CONTROL_TOG_OFF_SHIFT    (24U)
/*! OFF - Turn off */
#define CCM_OBS_OBSERVE_CONTROL_TOG_OFF(x)       (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_CONTROL_TOG_OFF_SHIFT)) & CCM_OBS_OBSERVE_CONTROL_TOG_OFF_MASK)
/*! @} */

/* The count of CCM_OBS_OBSERVE_CONTROL_TOG */
#define CCM_OBS_OBSERVE_CONTROL_TOG_COUNT        (6U)

/*! @name OBSERVE_STATUS0 - Observe status */
/*! @{ */

#define CCM_OBS_OBSERVE_STATUS0_SELECT_MASK      (0x1FFU)
#define CCM_OBS_OBSERVE_STATUS0_SELECT_SHIFT     (0U)
/*! SELECT - Select value */
#define CCM_OBS_OBSERVE_STATUS0_SELECT(x)        (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_STATUS0_SELECT_SHIFT)) & CCM_OBS_OBSERVE_STATUS0_SELECT_MASK)

#define CCM_OBS_OBSERVE_STATUS0_RAW_MASK         (0x1000U)
#define CCM_OBS_OBSERVE_STATUS0_RAW_SHIFT        (12U)
/*! RAW - Observe raw signal
 *  0b0..Divided signal is selected
 *  0b1..Raw signal is selected
 */
#define CCM_OBS_OBSERVE_STATUS0_RAW(x)           (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_STATUS0_RAW_SHIFT)) & CCM_OBS_OBSERVE_STATUS0_RAW_MASK)

#define CCM_OBS_OBSERVE_STATUS0_INV_MASK         (0x2000U)
#define CCM_OBS_OBSERVE_STATUS0_INV_SHIFT        (13U)
/*! INV - Polarity of the observe target
 *  0b0..Polarity is not inverted
 *  0b1..Polarity of the observe target is inverted
 */
#define CCM_OBS_OBSERVE_STATUS0_INV(x)           (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_STATUS0_INV_SHIFT)) & CCM_OBS_OBSERVE_STATUS0_INV_MASK)

#define CCM_OBS_OBSERVE_STATUS0_RESET_MASK       (0x8000U)
#define CCM_OBS_OBSERVE_STATUS0_RESET_SHIFT      (15U)
/*! RESET - Reset state
 *  0b0..Observe divider is not in reset state
 *  0b1..Observe divider is in reset state
 */
#define CCM_OBS_OBSERVE_STATUS0_RESET(x)         (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_STATUS0_RESET_SHIFT)) & CCM_OBS_OBSERVE_STATUS0_RESET_MASK)

#define CCM_OBS_OBSERVE_STATUS0_DIVIDE_MASK      (0xFF0000U)
#define CCM_OBS_OBSERVE_STATUS0_DIVIDE_SHIFT     (16U)
/*! DIVIDE - Divide value status. The clock will be divided by DIVIDE + 1. */
#define CCM_OBS_OBSERVE_STATUS0_DIVIDE(x)        (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_STATUS0_DIVIDE_SHIFT)) & CCM_OBS_OBSERVE_STATUS0_DIVIDE_MASK)

#define CCM_OBS_OBSERVE_STATUS0_OFF_MASK         (0x1000000U)
#define CCM_OBS_OBSERVE_STATUS0_OFF_SHIFT        (24U)
/*! OFF - Turn off slice
 *  0b0..observe slice is on
 *  0b1..observe slice is off
 */
#define CCM_OBS_OBSERVE_STATUS0_OFF(x)           (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_STATUS0_OFF_SHIFT)) & CCM_OBS_OBSERVE_STATUS0_OFF_MASK)
/*! @} */

/* The count of CCM_OBS_OBSERVE_STATUS0 */
#define CCM_OBS_OBSERVE_STATUS0_COUNT            (6U)

/*! @name OBSERVE_AUTHEN - Observe access control */
/*! @{ */

#define CCM_OBS_OBSERVE_AUTHEN_TZ_USER_MASK      (0x1U)
#define CCM_OBS_OBSERVE_AUTHEN_TZ_USER_SHIFT     (0U)
/*! TZ_USER - User access
 *  0b0..Clock cannot be changed in user mode.
 *  0b1..Clock can be changed in user mode.
 */
#define CCM_OBS_OBSERVE_AUTHEN_TZ_USER(x)        (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_AUTHEN_TZ_USER_SHIFT)) & CCM_OBS_OBSERVE_AUTHEN_TZ_USER_MASK)

#define CCM_OBS_OBSERVE_AUTHEN_TZ_NS_MASK        (0x2U)
#define CCM_OBS_OBSERVE_AUTHEN_TZ_NS_SHIFT       (1U)
/*! TZ_NS - Non-secure access
 *  0b0..Cannot be changed in Non-secure mode.
 *  0b1..Can be changed in Non-secure mode.
 */
#define CCM_OBS_OBSERVE_AUTHEN_TZ_NS(x)          (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_AUTHEN_TZ_NS_SHIFT)) & CCM_OBS_OBSERVE_AUTHEN_TZ_NS_MASK)

#define CCM_OBS_OBSERVE_AUTHEN_LOCK_TZ_MASK      (0x10U)
#define CCM_OBS_OBSERVE_AUTHEN_LOCK_TZ_SHIFT     (4U)
/*! LOCK_TZ - Lock truszone setting
 *  0b0..Trustzone setting is not locked.
 *  0b1..Trustzone setting is locked.
 */
#define CCM_OBS_OBSERVE_AUTHEN_LOCK_TZ(x)        (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_AUTHEN_LOCK_TZ_SHIFT)) & CCM_OBS_OBSERVE_AUTHEN_LOCK_TZ_MASK)

#define CCM_OBS_OBSERVE_AUTHEN_WHITE_LIST_MASK   (0xF00U)
#define CCM_OBS_OBSERVE_AUTHEN_WHITE_LIST_SHIFT  (8U)
/*! WHITE_LIST - White list
 *  0b0000..No domain can change.
 *  0b0001..Domain 0 can change.
 *  0b0010..Domain 1 can change.
 *  0b0011..Domain 0 and domain 1 can change.
 *  0b0100..Domain 2 can change.
 *  0b1111..All domain can change.
 */
#define CCM_OBS_OBSERVE_AUTHEN_WHITE_LIST(x)     (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_AUTHEN_WHITE_LIST_SHIFT)) & CCM_OBS_OBSERVE_AUTHEN_WHITE_LIST_MASK)

#define CCM_OBS_OBSERVE_AUTHEN_LOCK_LIST_MASK    (0x1000U)
#define CCM_OBS_OBSERVE_AUTHEN_LOCK_LIST_SHIFT   (12U)
/*! LOCK_LIST - Lock white list
 *  0b0..White list is not locked.
 *  0b1..White list is locked.
 */
#define CCM_OBS_OBSERVE_AUTHEN_LOCK_LIST(x)      (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_AUTHEN_LOCK_LIST_SHIFT)) & CCM_OBS_OBSERVE_AUTHEN_LOCK_LIST_MASK)

#define CCM_OBS_OBSERVE_AUTHEN_DOMAIN_MODE_MASK  (0x10000U)
#define CCM_OBS_OBSERVE_AUTHEN_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by domain
 *  0b0..Clock does not work in domain mode.
 *  0b1..Clock works in domain mode.
 */
#define CCM_OBS_OBSERVE_AUTHEN_DOMAIN_MODE(x)    (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_AUTHEN_DOMAIN_MODE_SHIFT)) & CCM_OBS_OBSERVE_AUTHEN_DOMAIN_MODE_MASK)

#define CCM_OBS_OBSERVE_AUTHEN_LOCK_MODE_MASK    (0x100000U)
#define CCM_OBS_OBSERVE_AUTHEN_LOCK_MODE_SHIFT   (20U)
/*! LOCK_MODE - Lock low power and access mode
 *  0b0..MODE is not locked.
 *  0b1..MODE is locked.
 */
#define CCM_OBS_OBSERVE_AUTHEN_LOCK_MODE(x)      (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_AUTHEN_LOCK_MODE_SHIFT)) & CCM_OBS_OBSERVE_AUTHEN_LOCK_MODE_MASK)
/*! @} */

/* The count of CCM_OBS_OBSERVE_AUTHEN */
#define CCM_OBS_OBSERVE_AUTHEN_COUNT             (6U)

/*! @name OBSERVE_AUTHEN_SET - Observe access control */
/*! @{ */

#define CCM_OBS_OBSERVE_AUTHEN_SET_TZ_USER_MASK  (0x1U)
#define CCM_OBS_OBSERVE_AUTHEN_SET_TZ_USER_SHIFT (0U)
/*! TZ_USER - User access */
#define CCM_OBS_OBSERVE_AUTHEN_SET_TZ_USER(x)    (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_AUTHEN_SET_TZ_USER_SHIFT)) & CCM_OBS_OBSERVE_AUTHEN_SET_TZ_USER_MASK)

#define CCM_OBS_OBSERVE_AUTHEN_SET_TZ_NS_MASK    (0x2U)
#define CCM_OBS_OBSERVE_AUTHEN_SET_TZ_NS_SHIFT   (1U)
/*! TZ_NS - Non-secure access */
#define CCM_OBS_OBSERVE_AUTHEN_SET_TZ_NS(x)      (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_AUTHEN_SET_TZ_NS_SHIFT)) & CCM_OBS_OBSERVE_AUTHEN_SET_TZ_NS_MASK)

#define CCM_OBS_OBSERVE_AUTHEN_SET_LOCK_TZ_MASK  (0x10U)
#define CCM_OBS_OBSERVE_AUTHEN_SET_LOCK_TZ_SHIFT (4U)
/*! LOCK_TZ - Lock truszone setting */
#define CCM_OBS_OBSERVE_AUTHEN_SET_LOCK_TZ(x)    (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_AUTHEN_SET_LOCK_TZ_SHIFT)) & CCM_OBS_OBSERVE_AUTHEN_SET_LOCK_TZ_MASK)

#define CCM_OBS_OBSERVE_AUTHEN_SET_WHITE_LIST_MASK (0xF00U)
#define CCM_OBS_OBSERVE_AUTHEN_SET_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - White list */
#define CCM_OBS_OBSERVE_AUTHEN_SET_WHITE_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_AUTHEN_SET_WHITE_LIST_SHIFT)) & CCM_OBS_OBSERVE_AUTHEN_SET_WHITE_LIST_MASK)

#define CCM_OBS_OBSERVE_AUTHEN_SET_LOCK_LIST_MASK (0x1000U)
#define CCM_OBS_OBSERVE_AUTHEN_SET_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - Lock white list */
#define CCM_OBS_OBSERVE_AUTHEN_SET_LOCK_LIST(x)  (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_AUTHEN_SET_LOCK_LIST_SHIFT)) & CCM_OBS_OBSERVE_AUTHEN_SET_LOCK_LIST_MASK)

#define CCM_OBS_OBSERVE_AUTHEN_SET_DOMAIN_MODE_MASK (0x10000U)
#define CCM_OBS_OBSERVE_AUTHEN_SET_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by domain */
#define CCM_OBS_OBSERVE_AUTHEN_SET_DOMAIN_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_AUTHEN_SET_DOMAIN_MODE_SHIFT)) & CCM_OBS_OBSERVE_AUTHEN_SET_DOMAIN_MODE_MASK)

#define CCM_OBS_OBSERVE_AUTHEN_SET_LOCK_MODE_MASK (0x100000U)
#define CCM_OBS_OBSERVE_AUTHEN_SET_LOCK_MODE_SHIFT (20U)
/*! LOCK_MODE - Lock low power and access mode */
#define CCM_OBS_OBSERVE_AUTHEN_SET_LOCK_MODE(x)  (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_AUTHEN_SET_LOCK_MODE_SHIFT)) & CCM_OBS_OBSERVE_AUTHEN_SET_LOCK_MODE_MASK)
/*! @} */

/* The count of CCM_OBS_OBSERVE_AUTHEN_SET */
#define CCM_OBS_OBSERVE_AUTHEN_SET_COUNT         (6U)

/*! @name OBSERVE_AUTHEN_CLR - Observe access control */
/*! @{ */

#define CCM_OBS_OBSERVE_AUTHEN_CLR_TZ_USER_MASK  (0x1U)
#define CCM_OBS_OBSERVE_AUTHEN_CLR_TZ_USER_SHIFT (0U)
/*! TZ_USER - User access */
#define CCM_OBS_OBSERVE_AUTHEN_CLR_TZ_USER(x)    (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_AUTHEN_CLR_TZ_USER_SHIFT)) & CCM_OBS_OBSERVE_AUTHEN_CLR_TZ_USER_MASK)

#define CCM_OBS_OBSERVE_AUTHEN_CLR_TZ_NS_MASK    (0x2U)
#define CCM_OBS_OBSERVE_AUTHEN_CLR_TZ_NS_SHIFT   (1U)
/*! TZ_NS - Non-secure access */
#define CCM_OBS_OBSERVE_AUTHEN_CLR_TZ_NS(x)      (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_AUTHEN_CLR_TZ_NS_SHIFT)) & CCM_OBS_OBSERVE_AUTHEN_CLR_TZ_NS_MASK)

#define CCM_OBS_OBSERVE_AUTHEN_CLR_LOCK_TZ_MASK  (0x10U)
#define CCM_OBS_OBSERVE_AUTHEN_CLR_LOCK_TZ_SHIFT (4U)
/*! LOCK_TZ - Lock truszone setting */
#define CCM_OBS_OBSERVE_AUTHEN_CLR_LOCK_TZ(x)    (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_AUTHEN_CLR_LOCK_TZ_SHIFT)) & CCM_OBS_OBSERVE_AUTHEN_CLR_LOCK_TZ_MASK)

#define CCM_OBS_OBSERVE_AUTHEN_CLR_WHITE_LIST_MASK (0xF00U)
#define CCM_OBS_OBSERVE_AUTHEN_CLR_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - White list */
#define CCM_OBS_OBSERVE_AUTHEN_CLR_WHITE_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_AUTHEN_CLR_WHITE_LIST_SHIFT)) & CCM_OBS_OBSERVE_AUTHEN_CLR_WHITE_LIST_MASK)

#define CCM_OBS_OBSERVE_AUTHEN_CLR_LOCK_LIST_MASK (0x1000U)
#define CCM_OBS_OBSERVE_AUTHEN_CLR_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - Lock white list */
#define CCM_OBS_OBSERVE_AUTHEN_CLR_LOCK_LIST(x)  (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_AUTHEN_CLR_LOCK_LIST_SHIFT)) & CCM_OBS_OBSERVE_AUTHEN_CLR_LOCK_LIST_MASK)

#define CCM_OBS_OBSERVE_AUTHEN_CLR_DOMAIN_MODE_MASK (0x10000U)
#define CCM_OBS_OBSERVE_AUTHEN_CLR_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by domain */
#define CCM_OBS_OBSERVE_AUTHEN_CLR_DOMAIN_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_AUTHEN_CLR_DOMAIN_MODE_SHIFT)) & CCM_OBS_OBSERVE_AUTHEN_CLR_DOMAIN_MODE_MASK)

#define CCM_OBS_OBSERVE_AUTHEN_CLR_LOCK_MODE_MASK (0x100000U)
#define CCM_OBS_OBSERVE_AUTHEN_CLR_LOCK_MODE_SHIFT (20U)
/*! LOCK_MODE - Lock low power and access mode */
#define CCM_OBS_OBSERVE_AUTHEN_CLR_LOCK_MODE(x)  (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_AUTHEN_CLR_LOCK_MODE_SHIFT)) & CCM_OBS_OBSERVE_AUTHEN_CLR_LOCK_MODE_MASK)
/*! @} */

/* The count of CCM_OBS_OBSERVE_AUTHEN_CLR */
#define CCM_OBS_OBSERVE_AUTHEN_CLR_COUNT         (6U)

/*! @name OBSERVE_AUTHEN_TOG - Observe access control */
/*! @{ */

#define CCM_OBS_OBSERVE_AUTHEN_TOG_TZ_USER_MASK  (0x1U)
#define CCM_OBS_OBSERVE_AUTHEN_TOG_TZ_USER_SHIFT (0U)
/*! TZ_USER - User access */
#define CCM_OBS_OBSERVE_AUTHEN_TOG_TZ_USER(x)    (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_AUTHEN_TOG_TZ_USER_SHIFT)) & CCM_OBS_OBSERVE_AUTHEN_TOG_TZ_USER_MASK)

#define CCM_OBS_OBSERVE_AUTHEN_TOG_TZ_NS_MASK    (0x2U)
#define CCM_OBS_OBSERVE_AUTHEN_TOG_TZ_NS_SHIFT   (1U)
/*! TZ_NS - Non-secure access */
#define CCM_OBS_OBSERVE_AUTHEN_TOG_TZ_NS(x)      (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_AUTHEN_TOG_TZ_NS_SHIFT)) & CCM_OBS_OBSERVE_AUTHEN_TOG_TZ_NS_MASK)

#define CCM_OBS_OBSERVE_AUTHEN_TOG_LOCK_TZ_MASK  (0x10U)
#define CCM_OBS_OBSERVE_AUTHEN_TOG_LOCK_TZ_SHIFT (4U)
/*! LOCK_TZ - Lock truszone setting */
#define CCM_OBS_OBSERVE_AUTHEN_TOG_LOCK_TZ(x)    (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_AUTHEN_TOG_LOCK_TZ_SHIFT)) & CCM_OBS_OBSERVE_AUTHEN_TOG_LOCK_TZ_MASK)

#define CCM_OBS_OBSERVE_AUTHEN_TOG_WHITE_LIST_MASK (0xF00U)
#define CCM_OBS_OBSERVE_AUTHEN_TOG_WHITE_LIST_SHIFT (8U)
/*! WHITE_LIST - White list */
#define CCM_OBS_OBSERVE_AUTHEN_TOG_WHITE_LIST(x) (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_AUTHEN_TOG_WHITE_LIST_SHIFT)) & CCM_OBS_OBSERVE_AUTHEN_TOG_WHITE_LIST_MASK)

#define CCM_OBS_OBSERVE_AUTHEN_TOG_LOCK_LIST_MASK (0x1000U)
#define CCM_OBS_OBSERVE_AUTHEN_TOG_LOCK_LIST_SHIFT (12U)
/*! LOCK_LIST - Lock white list */
#define CCM_OBS_OBSERVE_AUTHEN_TOG_LOCK_LIST(x)  (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_AUTHEN_TOG_LOCK_LIST_SHIFT)) & CCM_OBS_OBSERVE_AUTHEN_TOG_LOCK_LIST_MASK)

#define CCM_OBS_OBSERVE_AUTHEN_TOG_DOMAIN_MODE_MASK (0x10000U)
#define CCM_OBS_OBSERVE_AUTHEN_TOG_DOMAIN_MODE_SHIFT (16U)
/*! DOMAIN_MODE - Low power and access control by domain */
#define CCM_OBS_OBSERVE_AUTHEN_TOG_DOMAIN_MODE(x) (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_AUTHEN_TOG_DOMAIN_MODE_SHIFT)) & CCM_OBS_OBSERVE_AUTHEN_TOG_DOMAIN_MODE_MASK)

#define CCM_OBS_OBSERVE_AUTHEN_TOG_LOCK_MODE_MASK (0x100000U)
#define CCM_OBS_OBSERVE_AUTHEN_TOG_LOCK_MODE_SHIFT (20U)
/*! LOCK_MODE - Lock low power and access mode */
#define CCM_OBS_OBSERVE_AUTHEN_TOG_LOCK_MODE(x)  (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_AUTHEN_TOG_LOCK_MODE_SHIFT)) & CCM_OBS_OBSERVE_AUTHEN_TOG_LOCK_MODE_MASK)
/*! @} */

/* The count of CCM_OBS_OBSERVE_AUTHEN_TOG */
#define CCM_OBS_OBSERVE_AUTHEN_TOG_COUNT         (6U)

/*! @name OBSERVE_FREQUENCY_CURRENT - Current frequency detected */
/*! @{ */

#define CCM_OBS_OBSERVE_FREQUENCY_CURRENT_FREQUENCY_MASK (0xFFFFFFFFU)
#define CCM_OBS_OBSERVE_FREQUENCY_CURRENT_FREQUENCY_SHIFT (0U)
/*! FREQUENCY - Frequency */
#define CCM_OBS_OBSERVE_FREQUENCY_CURRENT_FREQUENCY(x) (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_FREQUENCY_CURRENT_FREQUENCY_SHIFT)) & CCM_OBS_OBSERVE_FREQUENCY_CURRENT_FREQUENCY_MASK)
/*! @} */

/* The count of CCM_OBS_OBSERVE_FREQUENCY_CURRENT */
#define CCM_OBS_OBSERVE_FREQUENCY_CURRENT_COUNT  (6U)

/*! @name OBSERVE_FREQUENCY_MIN - Minimum frequency detected */
/*! @{ */

#define CCM_OBS_OBSERVE_FREQUENCY_MIN_FREQUENCY_MASK (0xFFFFFFFFU)
#define CCM_OBS_OBSERVE_FREQUENCY_MIN_FREQUENCY_SHIFT (0U)
/*! FREQUENCY - Frequency */
#define CCM_OBS_OBSERVE_FREQUENCY_MIN_FREQUENCY(x) (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_FREQUENCY_MIN_FREQUENCY_SHIFT)) & CCM_OBS_OBSERVE_FREQUENCY_MIN_FREQUENCY_MASK)
/*! @} */

/* The count of CCM_OBS_OBSERVE_FREQUENCY_MIN */
#define CCM_OBS_OBSERVE_FREQUENCY_MIN_COUNT      (6U)

/*! @name OBSERVE_FREQUENCY_MAX - Maximum frequency detected */
/*! @{ */

#define CCM_OBS_OBSERVE_FREQUENCY_MAX_FREQUENCY_MASK (0xFFFFFFFFU)
#define CCM_OBS_OBSERVE_FREQUENCY_MAX_FREQUENCY_SHIFT (0U)
/*! FREQUENCY - Frequency */
#define CCM_OBS_OBSERVE_FREQUENCY_MAX_FREQUENCY(x) (((uint32_t)(((uint32_t)(x)) << CCM_OBS_OBSERVE_FREQUENCY_MAX_FREQUENCY_SHIFT)) & CCM_OBS_OBSERVE_FREQUENCY_MAX_FREQUENCY_MASK)
/*! @} */

/* The count of CCM_OBS_OBSERVE_FREQUENCY_MAX */
#define CCM_OBS_OBSERVE_FREQUENCY_MAX_COUNT      (6U)


/*!
 * @}
 */ /* end of group CCM_OBS_Register_Masks */


/*!
 * @}
 */ /* end of group CCM_OBS_Peripheral_Access_Layer */


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


#endif  /* PERI_CCM_OBS_H_ */

