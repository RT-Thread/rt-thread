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
**         CMSIS Peripheral Access Layer for ANADIG_OSC
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
 * @file PERI_ANADIG_OSC.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for ANADIG_OSC
 *
 * CMSIS Peripheral Access Layer for ANADIG_OSC
 */

#if !defined(PERI_ANADIG_OSC_H_)
#define PERI_ANADIG_OSC_H_                       /**< Symbol preventing repeated inclusion */

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
   -- ANADIG_OSC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ANADIG_OSC_Peripheral_Access_Layer ANADIG_OSC Peripheral Access Layer
 * @{
 */

/** ANADIG_OSC - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[16];
  __IO uint32_t OSC_48M_CTRL;                      /**< 48MHz RCOSC Control Register, offset: 0x10 */
       uint8_t RESERVED_1[12];
  __IO uint32_t OSC_24M_CTRL;                      /**< 24MHz OSC Control Register, offset: 0x20 */
       uint8_t RESERVED_2[28];
  __I  uint32_t OSC_400M_CTRL0;                    /**< 400MHz RCOSC Control0 Register, offset: 0x40 */
       uint8_t RESERVED_3[12];
  __IO uint32_t OSC_400M_CTRL1;                    /**< 400MHz RCOSC Control1 Register, offset: 0x50 */
       uint8_t RESERVED_4[12];
  __IO uint32_t OSC_400M_CTRL2;                    /**< 400MHz RCOSC Control2 Register, offset: 0x60 */
       uint8_t RESERVED_5[92];
  __IO uint32_t OSC_16M_CTRL;                      /**< 16MHz RCOSC Control Register, offset: 0xC0 */
} ANADIG_OSC_Type;

/* ----------------------------------------------------------------------------
   -- ANADIG_OSC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup ANADIG_OSC_Register_Masks ANADIG_OSC Register Masks
 * @{
 */

/*! @name OSC_48M_CTRL - 48MHz RCOSC Control Register */
/*! @{ */

#define ANADIG_OSC_OSC_48M_CTRL_TEN_MASK         (0x2U)
#define ANADIG_OSC_OSC_48M_CTRL_TEN_SHIFT        (1U)
/*! TEN - 48MHz RCOSC Enable
 *  0b0..Power down
 *  0b1..Power up
 */
#define ANADIG_OSC_OSC_48M_CTRL_TEN(x)           (((uint32_t)(((uint32_t)(x)) << ANADIG_OSC_OSC_48M_CTRL_TEN_SHIFT)) & ANADIG_OSC_OSC_48M_CTRL_TEN_MASK)

#define ANADIG_OSC_OSC_48M_CTRL_RC_48M_DIV2_EN_MASK (0x1000000U)
#define ANADIG_OSC_OSC_48M_CTRL_RC_48M_DIV2_EN_SHIFT (24U)
/*! RC_48M_DIV2_EN - RCOSC_48M_DIV2 Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define ANADIG_OSC_OSC_48M_CTRL_RC_48M_DIV2_EN(x) (((uint32_t)(((uint32_t)(x)) << ANADIG_OSC_OSC_48M_CTRL_RC_48M_DIV2_EN_SHIFT)) & ANADIG_OSC_OSC_48M_CTRL_RC_48M_DIV2_EN_MASK)

#define ANADIG_OSC_OSC_48M_CTRL_RC_48M_DIV2_CONTROL_MODE_MASK (0x40000000U)
#define ANADIG_OSC_OSC_48M_CTRL_RC_48M_DIV2_CONTROL_MODE_SHIFT (30U)
/*! RC_48M_DIV2_CONTROL_MODE - RCOSC_48M_DIV2 Control Mode
 *  0b0..Software mode (default)
 *  0b1..GPC mode (Setpoint)
 */
#define ANADIG_OSC_OSC_48M_CTRL_RC_48M_DIV2_CONTROL_MODE(x) (((uint32_t)(((uint32_t)(x)) << ANADIG_OSC_OSC_48M_CTRL_RC_48M_DIV2_CONTROL_MODE_SHIFT)) & ANADIG_OSC_OSC_48M_CTRL_RC_48M_DIV2_CONTROL_MODE_MASK)

#define ANADIG_OSC_OSC_48M_CTRL_RC_48M_CONTROL_MODE_MASK (0x80000000U)
#define ANADIG_OSC_OSC_48M_CTRL_RC_48M_CONTROL_MODE_SHIFT (31U)
/*! RC_48M_CONTROL_MODE - 48MHz RCOSC Control Mode
 *  0b0..Software mode (default)
 *  0b1..GPC mode (Setpoint)
 */
#define ANADIG_OSC_OSC_48M_CTRL_RC_48M_CONTROL_MODE(x) (((uint32_t)(((uint32_t)(x)) << ANADIG_OSC_OSC_48M_CTRL_RC_48M_CONTROL_MODE_SHIFT)) & ANADIG_OSC_OSC_48M_CTRL_RC_48M_CONTROL_MODE_MASK)
/*! @} */

/*! @name OSC_24M_CTRL - 24MHz OSC Control Register */
/*! @{ */

#define ANADIG_OSC_OSC_24M_CTRL_BYPASS_CLK_MASK  (0x1U)
#define ANADIG_OSC_OSC_24M_CTRL_BYPASS_CLK_SHIFT (0U)
/*! BYPASS_CLK - 24MHz OSC Bypass Clock */
#define ANADIG_OSC_OSC_24M_CTRL_BYPASS_CLK(x)    (((uint32_t)(((uint32_t)(x)) << ANADIG_OSC_OSC_24M_CTRL_BYPASS_CLK_SHIFT)) & ANADIG_OSC_OSC_24M_CTRL_BYPASS_CLK_MASK)

#define ANADIG_OSC_OSC_24M_CTRL_BYPASS_EN_MASK   (0x2U)
#define ANADIG_OSC_OSC_24M_CTRL_BYPASS_EN_SHIFT  (1U)
/*! BYPASS_EN - 24MHz OSC Bypass Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define ANADIG_OSC_OSC_24M_CTRL_BYPASS_EN(x)     (((uint32_t)(((uint32_t)(x)) << ANADIG_OSC_OSC_24M_CTRL_BYPASS_EN_SHIFT)) & ANADIG_OSC_OSC_24M_CTRL_BYPASS_EN_MASK)

#define ANADIG_OSC_OSC_24M_CTRL_LP_EN_MASK       (0x4U)
#define ANADIG_OSC_OSC_24M_CTRL_LP_EN_SHIFT      (2U)
/*! LP_EN - 24MHz OSC Low-Power Mode Enable
 *  0b0..High Gain mode (HP)
 *  0b1..Low-power mode (LP)
 */
#define ANADIG_OSC_OSC_24M_CTRL_LP_EN(x)         (((uint32_t)(((uint32_t)(x)) << ANADIG_OSC_OSC_24M_CTRL_LP_EN_SHIFT)) & ANADIG_OSC_OSC_24M_CTRL_LP_EN_MASK)

#define ANADIG_OSC_OSC_24M_CTRL_OSC_COMP_MODE_MASK (0x8U)
#define ANADIG_OSC_OSC_24M_CTRL_OSC_COMP_MODE_SHIFT (3U)
/*! OSC_COMP_MODE - 24MHz OSC Comparator Mode
 *  0b0..Single-ended mode (default)
 *  0b1..Differential mode (test mode)
 */
#define ANADIG_OSC_OSC_24M_CTRL_OSC_COMP_MODE(x) (((uint32_t)(((uint32_t)(x)) << ANADIG_OSC_OSC_24M_CTRL_OSC_COMP_MODE_SHIFT)) & ANADIG_OSC_OSC_24M_CTRL_OSC_COMP_MODE_MASK)

#define ANADIG_OSC_OSC_24M_CTRL_OSC_EN_MASK      (0x10U)
#define ANADIG_OSC_OSC_24M_CTRL_OSC_EN_SHIFT     (4U)
/*! OSC_EN - 24MHz OSC Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define ANADIG_OSC_OSC_24M_CTRL_OSC_EN(x)        (((uint32_t)(((uint32_t)(x)) << ANADIG_OSC_OSC_24M_CTRL_OSC_EN_SHIFT)) & ANADIG_OSC_OSC_24M_CTRL_OSC_EN_MASK)

#define ANADIG_OSC_OSC_24M_CTRL_OSC_24M_GATE_MASK (0x80U)
#define ANADIG_OSC_OSC_24M_CTRL_OSC_24M_GATE_SHIFT (7U)
/*! OSC_24M_GATE - 24MHz OSC Gate Control
 *  0b0..Not Gated
 *  0b1..Gated
 */
#define ANADIG_OSC_OSC_24M_CTRL_OSC_24M_GATE(x)  (((uint32_t)(((uint32_t)(x)) << ANADIG_OSC_OSC_24M_CTRL_OSC_24M_GATE_SHIFT)) & ANADIG_OSC_OSC_24M_CTRL_OSC_24M_GATE_MASK)

#define ANADIG_OSC_OSC_24M_CTRL_OSC_24M_STABLE_MASK (0x40000000U)
#define ANADIG_OSC_OSC_24M_CTRL_OSC_24M_STABLE_SHIFT (30U)
/*! OSC_24M_STABLE - 24MHz OSC Stable
 *  0b0..Not Stable
 *  0b1..Stable
 */
#define ANADIG_OSC_OSC_24M_CTRL_OSC_24M_STABLE(x) (((uint32_t)(((uint32_t)(x)) << ANADIG_OSC_OSC_24M_CTRL_OSC_24M_STABLE_SHIFT)) & ANADIG_OSC_OSC_24M_CTRL_OSC_24M_STABLE_MASK)

#define ANADIG_OSC_OSC_24M_CTRL_OSC_24M_CONTROL_MODE_MASK (0x80000000U)
#define ANADIG_OSC_OSC_24M_CTRL_OSC_24M_CONTROL_MODE_SHIFT (31U)
/*! OSC_24M_CONTROL_MODE - 24MHz OSC Control Mode
 *  0b0..Software mode (default)
 *  0b1..GPC mode (Setpoint)
 */
#define ANADIG_OSC_OSC_24M_CTRL_OSC_24M_CONTROL_MODE(x) (((uint32_t)(((uint32_t)(x)) << ANADIG_OSC_OSC_24M_CTRL_OSC_24M_CONTROL_MODE_SHIFT)) & ANADIG_OSC_OSC_24M_CTRL_OSC_24M_CONTROL_MODE_MASK)
/*! @} */

/*! @name OSC_400M_CTRL0 - 400MHz RCOSC Control0 Register */
/*! @{ */

#define ANADIG_OSC_OSC_400M_CTRL0_OSC400M_AI_BUSY_MASK (0x80000000U)
#define ANADIG_OSC_OSC_400M_CTRL0_OSC400M_AI_BUSY_SHIFT (31U)
/*! OSC400M_AI_BUSY - 400MHz OSC AI BUSY */
#define ANADIG_OSC_OSC_400M_CTRL0_OSC400M_AI_BUSY(x) (((uint32_t)(((uint32_t)(x)) << ANADIG_OSC_OSC_400M_CTRL0_OSC400M_AI_BUSY_SHIFT)) & ANADIG_OSC_OSC_400M_CTRL0_OSC400M_AI_BUSY_MASK)
/*! @} */

/*! @name OSC_400M_CTRL1 - 400MHz RCOSC Control1 Register */
/*! @{ */

#define ANADIG_OSC_OSC_400M_CTRL1_PWD_MASK       (0x1U)
#define ANADIG_OSC_OSC_400M_CTRL1_PWD_SHIFT      (0U)
/*! PWD - Power down control for 400MHz RCOSC
 *  0b0..No Power down
 *  0b1..Power down
 */
#define ANADIG_OSC_OSC_400M_CTRL1_PWD(x)         (((uint32_t)(((uint32_t)(x)) << ANADIG_OSC_OSC_400M_CTRL1_PWD_SHIFT)) & ANADIG_OSC_OSC_400M_CTRL1_PWD_MASK)

#define ANADIG_OSC_OSC_400M_CTRL1_CLKGATE_400MEG_MASK (0x2U)
#define ANADIG_OSC_OSC_400M_CTRL1_CLKGATE_400MEG_SHIFT (1U)
/*! CLKGATE_400MEG - Clock gate control for 400MHz RCOSC
 *  0b0..Not Gated
 *  0b1..Gated
 */
#define ANADIG_OSC_OSC_400M_CTRL1_CLKGATE_400MEG(x) (((uint32_t)(((uint32_t)(x)) << ANADIG_OSC_OSC_400M_CTRL1_CLKGATE_400MEG_SHIFT)) & ANADIG_OSC_OSC_400M_CTRL1_CLKGATE_400MEG_MASK)

#define ANADIG_OSC_OSC_400M_CTRL1_RC_400M_CONTROL_MODE_MASK (0x80000000U)
#define ANADIG_OSC_OSC_400M_CTRL1_RC_400M_CONTROL_MODE_SHIFT (31U)
/*! RC_400M_CONTROL_MODE - 400MHz RCOSC Control mode
 *  0b0..Software mode (default)
 *  0b1..GPC mode (Setpoint)
 */
#define ANADIG_OSC_OSC_400M_CTRL1_RC_400M_CONTROL_MODE(x) (((uint32_t)(((uint32_t)(x)) << ANADIG_OSC_OSC_400M_CTRL1_RC_400M_CONTROL_MODE_SHIFT)) & ANADIG_OSC_OSC_400M_CTRL1_RC_400M_CONTROL_MODE_MASK)
/*! @} */

/*! @name OSC_400M_CTRL2 - 400MHz RCOSC Control2 Register */
/*! @{ */

#define ANADIG_OSC_OSC_400M_CTRL2_ENABLE_CLK_MASK (0x1U)
#define ANADIG_OSC_OSC_400M_CTRL2_ENABLE_CLK_SHIFT (0U)
/*! ENABLE_CLK - Clock enable
 *  0b0..Clock is disabled before entering GPC mode
 *  0b1..Clock is enabled before entering GPC mode
 */
#define ANADIG_OSC_OSC_400M_CTRL2_ENABLE_CLK(x)  (((uint32_t)(((uint32_t)(x)) << ANADIG_OSC_OSC_400M_CTRL2_ENABLE_CLK_SHIFT)) & ANADIG_OSC_OSC_400M_CTRL2_ENABLE_CLK_MASK)

#define ANADIG_OSC_OSC_400M_CTRL2_TUNE_BYP_MASK  (0x400U)
#define ANADIG_OSC_OSC_400M_CTRL2_TUNE_BYP_SHIFT (10U)
/*! TUNE_BYP - Bypass tuning logic
 *  0b0..Use the output of tuning logic to run the oscillator
 *  0b1..Bypass the tuning logic and use the programmed OSC_TUNE_VAL to run the oscillator
 */
#define ANADIG_OSC_OSC_400M_CTRL2_TUNE_BYP(x)    (((uint32_t)(((uint32_t)(x)) << ANADIG_OSC_OSC_400M_CTRL2_TUNE_BYP_SHIFT)) & ANADIG_OSC_OSC_400M_CTRL2_TUNE_BYP_MASK)

#define ANADIG_OSC_OSC_400M_CTRL2_OSC_TUNE_VAL_MASK (0xFF000000U)
#define ANADIG_OSC_OSC_400M_CTRL2_OSC_TUNE_VAL_SHIFT (24U)
/*! OSC_TUNE_VAL - Oscillator Tune Value */
#define ANADIG_OSC_OSC_400M_CTRL2_OSC_TUNE_VAL(x) (((uint32_t)(((uint32_t)(x)) << ANADIG_OSC_OSC_400M_CTRL2_OSC_TUNE_VAL_SHIFT)) & ANADIG_OSC_OSC_400M_CTRL2_OSC_TUNE_VAL_MASK)
/*! @} */

/*! @name OSC_16M_CTRL - 16MHz RCOSC Control Register */
/*! @{ */

#define ANADIG_OSC_OSC_16M_CTRL_EN_IRC4M16M_MASK (0x2U)
#define ANADIG_OSC_OSC_16M_CTRL_EN_IRC4M16M_SHIFT (1U)
/*! EN_IRC4M16M - Enable Clock Output
 *  0b0..Disable
 *  0b1..Enable
 */
#define ANADIG_OSC_OSC_16M_CTRL_EN_IRC4M16M(x)   (((uint32_t)(((uint32_t)(x)) << ANADIG_OSC_OSC_16M_CTRL_EN_IRC4M16M_SHIFT)) & ANADIG_OSC_OSC_16M_CTRL_EN_IRC4M16M_MASK)

#define ANADIG_OSC_OSC_16M_CTRL_EN_POWER_SAVE_MASK (0x8U)
#define ANADIG_OSC_OSC_16M_CTRL_EN_POWER_SAVE_SHIFT (3U)
/*! EN_POWER_SAVE - Power Save Enable
 *  0b0..Disable
 *  0b1..Enable
 */
#define ANADIG_OSC_OSC_16M_CTRL_EN_POWER_SAVE(x) (((uint32_t)(((uint32_t)(x)) << ANADIG_OSC_OSC_16M_CTRL_EN_POWER_SAVE_SHIFT)) & ANADIG_OSC_OSC_16M_CTRL_EN_POWER_SAVE_MASK)

#define ANADIG_OSC_OSC_16M_CTRL_SOURCE_SEL_16M_MASK (0x100U)
#define ANADIG_OSC_OSC_16M_CTRL_SOURCE_SEL_16M_SHIFT (8U)
/*! SOURCE_SEL_16M - Source select
 *  0b0..16MHz Oscillator
 *  0b1..24MHz Oscillator
 */
#define ANADIG_OSC_OSC_16M_CTRL_SOURCE_SEL_16M(x) (((uint32_t)(((uint32_t)(x)) << ANADIG_OSC_OSC_16M_CTRL_SOURCE_SEL_16M_SHIFT)) & ANADIG_OSC_OSC_16M_CTRL_SOURCE_SEL_16M_MASK)

#define ANADIG_OSC_OSC_16M_CTRL_RC_16M_CONTROL_MODE_MASK (0x80000000U)
#define ANADIG_OSC_OSC_16M_CTRL_RC_16M_CONTROL_MODE_SHIFT (31U)
/*! RC_16M_CONTROL_MODE - Control Mode for 16MHz Oscillator
 *  0b0..Software mode (default)
 *  0b1..GPC mode (Setpoint)
 */
#define ANADIG_OSC_OSC_16M_CTRL_RC_16M_CONTROL_MODE(x) (((uint32_t)(((uint32_t)(x)) << ANADIG_OSC_OSC_16M_CTRL_RC_16M_CONTROL_MODE_SHIFT)) & ANADIG_OSC_OSC_16M_CTRL_RC_16M_CONTROL_MODE_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group ANADIG_OSC_Register_Masks */


/*!
 * @}
 */ /* end of group ANADIG_OSC_Peripheral_Access_Layer */


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


#endif  /* PERI_ANADIG_OSC_H_ */

