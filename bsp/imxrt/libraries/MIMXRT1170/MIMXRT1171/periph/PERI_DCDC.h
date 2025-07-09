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
**         CMSIS Peripheral Access Layer for DCDC
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
 * @file PERI_DCDC.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for DCDC
 *
 * CMSIS Peripheral Access Layer for DCDC
 */

#if !defined(PERI_DCDC_H_)
#define PERI_DCDC_H_                             /**< Symbol preventing repeated inclusion */

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
   -- DCDC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DCDC_Peripheral_Access_Layer DCDC Peripheral Access Layer
 * @{
 */

/** DCDC - Register Layout Typedef */
typedef struct {
  __IO uint32_t CTRL0;                             /**< DCDC Control Register 0, offset: 0x0 */
  __IO uint32_t CTRL1;                             /**< DCDC Control Register 1, offset: 0x4 */
  __IO uint32_t REG0;                              /**< DCDC Register 0, offset: 0x8 */
  __IO uint32_t REG1;                              /**< DCDC Register 1, offset: 0xC */
  __IO uint32_t REG2;                              /**< DCDC Register 2, offset: 0x10 */
  __IO uint32_t REG3;                              /**< DCDC Register 3, offset: 0x14 */
  __IO uint32_t REG4;                              /**< DCDC Register 4, offset: 0x18 */
  __IO uint32_t REG5;                              /**< DCDC Register 5, offset: 0x1C */
  __IO uint32_t REG6;                              /**< DCDC Register 6, offset: 0x20 */
  __IO uint32_t REG7;                              /**< DCDC Register 7, offset: 0x24 */
  __IO uint32_t REG7P;                             /**< DCDC Register 7 plus, offset: 0x28 */
  __IO uint32_t REG8;                              /**< DCDC Register 8, offset: 0x2C */
  __IO uint32_t REG9;                              /**< DCDC Register 9, offset: 0x30 */
  __IO uint32_t REG10;                             /**< DCDC Register 10, offset: 0x34 */
  __IO uint32_t REG11;                             /**< DCDC Register 11, offset: 0x38 */
  __IO uint32_t REG12;                             /**< DCDC Register 12, offset: 0x3C */
  __IO uint32_t REG13;                             /**< DCDC Register 13, offset: 0x40 */
  __IO uint32_t REG14;                             /**< DCDC Register 14, offset: 0x44 */
  __IO uint32_t REG15;                             /**< DCDC Register 15, offset: 0x48 */
  __IO uint32_t REG16;                             /**< DCDC Register 16, offset: 0x4C */
  __IO uint32_t REG17;                             /**< DCDC Register 17, offset: 0x50 */
  __IO uint32_t REG18;                             /**< DCDC Register 18, offset: 0x54 */
  __IO uint32_t REG19;                             /**< DCDC Register 19, offset: 0x58 */
  __IO uint32_t REG20;                             /**< DCDC Register 20, offset: 0x5C */
  __IO uint32_t REG21;                             /**< DCDC Register 21, offset: 0x60 */
  __IO uint32_t REG22;                             /**< DCDC Register 22, offset: 0x64 */
  __IO uint32_t REG23;                             /**< DCDC Register 23, offset: 0x68 */
  __IO uint32_t REG24;                             /**< DCDC Register 24, offset: 0x6C */
} DCDC_Type;

/* ----------------------------------------------------------------------------
   -- DCDC Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup DCDC_Register_Masks DCDC Register Masks
 * @{
 */

/*! @name CTRL0 - DCDC Control Register 0 */
/*! @{ */

#define DCDC_CTRL0_ENABLE_MASK                   (0x1U)
#define DCDC_CTRL0_ENABLE_SHIFT                  (0U)
/*! ENABLE
 *  0b0..Disable (Bypass)
 *  0b1..Enable
 */
#define DCDC_CTRL0_ENABLE(x)                     (((uint32_t)(((uint32_t)(x)) << DCDC_CTRL0_ENABLE_SHIFT)) & DCDC_CTRL0_ENABLE_MASK)

#define DCDC_CTRL0_DIG_EN_MASK                   (0x2U)
#define DCDC_CTRL0_DIG_EN_SHIFT                  (1U)
/*! DIG_EN
 *  0b0..Reserved
 *  0b1..Enable
 */
#define DCDC_CTRL0_DIG_EN(x)                     (((uint32_t)(((uint32_t)(x)) << DCDC_CTRL0_DIG_EN_SHIFT)) & DCDC_CTRL0_DIG_EN_MASK)

#define DCDC_CTRL0_STBY_EN_MASK                  (0x4U)
#define DCDC_CTRL0_STBY_EN_SHIFT                 (2U)
/*! STBY_EN
 *  0b1..Enter into standby mode
 */
#define DCDC_CTRL0_STBY_EN(x)                    (((uint32_t)(((uint32_t)(x)) << DCDC_CTRL0_STBY_EN_SHIFT)) & DCDC_CTRL0_STBY_EN_MASK)

#define DCDC_CTRL0_LP_MODE_EN_MASK               (0x8U)
#define DCDC_CTRL0_LP_MODE_EN_SHIFT              (3U)
/*! LP_MODE_EN
 *  0b1..Enter into low-power mode
 */
#define DCDC_CTRL0_LP_MODE_EN(x)                 (((uint32_t)(((uint32_t)(x)) << DCDC_CTRL0_LP_MODE_EN_SHIFT)) & DCDC_CTRL0_LP_MODE_EN_MASK)

#define DCDC_CTRL0_STBY_LP_MODE_EN_MASK          (0x10U)
#define DCDC_CTRL0_STBY_LP_MODE_EN_SHIFT         (4U)
/*! STBY_LP_MODE_EN
 *  0b0..Disable DCDC entry into low-power mode from a GPC standby request
 *  0b1..Enable DCDC to enter into low-power mode from a GPC standby request
 */
#define DCDC_CTRL0_STBY_LP_MODE_EN(x)            (((uint32_t)(((uint32_t)(x)) << DCDC_CTRL0_STBY_LP_MODE_EN_SHIFT)) & DCDC_CTRL0_STBY_LP_MODE_EN_MASK)

#define DCDC_CTRL0_ENABLE_DCDC_CNT_MASK          (0x20U)
#define DCDC_CTRL0_ENABLE_DCDC_CNT_SHIFT         (5U)
/*! ENABLE_DCDC_CNT - Enable internal count for DCDC_OK timeout
 *  0b0..Wait DCDC_OK for ACK
 *  0b1..Enable internal count for DCDC_OK timeout
 */
#define DCDC_CTRL0_ENABLE_DCDC_CNT(x)            (((uint32_t)(((uint32_t)(x)) << DCDC_CTRL0_ENABLE_DCDC_CNT_SHIFT)) & DCDC_CTRL0_ENABLE_DCDC_CNT_MASK)

#define DCDC_CTRL0_TRIM_HOLD_MASK                (0x40U)
#define DCDC_CTRL0_TRIM_HOLD_SHIFT               (6U)
/*! TRIM_HOLD - Hold trim input
 *  0b0..Sample trim input
 *  0b1..Hold trim input
 */
#define DCDC_CTRL0_TRIM_HOLD(x)                  (((uint32_t)(((uint32_t)(x)) << DCDC_CTRL0_TRIM_HOLD_SHIFT)) & DCDC_CTRL0_TRIM_HOLD_MASK)

#define DCDC_CTRL0_DEBUG_BITS_MASK               (0x7FF80000U)
#define DCDC_CTRL0_DEBUG_BITS_SHIFT              (19U)
/*! DEBUG_BITS - DEBUG_BITS[11:0] */
#define DCDC_CTRL0_DEBUG_BITS(x)                 (((uint32_t)(((uint32_t)(x)) << DCDC_CTRL0_DEBUG_BITS_SHIFT)) & DCDC_CTRL0_DEBUG_BITS_MASK)

#define DCDC_CTRL0_CONTROL_MODE_MASK             (0x80000000U)
#define DCDC_CTRL0_CONTROL_MODE_SHIFT            (31U)
/*! CONTROL_MODE - Control mode
 *  0b0..Software control mode
 *  0b1..Hardware control mode (controlled by GPC Setpoints)
 */
#define DCDC_CTRL0_CONTROL_MODE(x)               (((uint32_t)(((uint32_t)(x)) << DCDC_CTRL0_CONTROL_MODE_SHIFT)) & DCDC_CTRL0_CONTROL_MODE_MASK)
/*! @} */

/*! @name CTRL1 - DCDC Control Register 1 */
/*! @{ */

#define DCDC_CTRL1_VDD1P8CTRL_TRG_MASK           (0x1FU)
#define DCDC_CTRL1_VDD1P8CTRL_TRG_SHIFT          (0U)
/*! VDD1P8CTRL_TRG
 *  0b00000..1.5V
 *  0b01100..1.8V
 *  0b11111..2.275V
 */
#define DCDC_CTRL1_VDD1P8CTRL_TRG(x)             (((uint32_t)(((uint32_t)(x)) << DCDC_CTRL1_VDD1P8CTRL_TRG_SHIFT)) & DCDC_CTRL1_VDD1P8CTRL_TRG_MASK)

#define DCDC_CTRL1_VDD1P0CTRL_TRG_MASK           (0x1F00U)
#define DCDC_CTRL1_VDD1P0CTRL_TRG_SHIFT          (8U)
/*! VDD1P0CTRL_TRG
 *  0b00000..0.6V
 *  0b10000..1.0V
 *  0b11111..1.375V
 */
#define DCDC_CTRL1_VDD1P0CTRL_TRG(x)             (((uint32_t)(((uint32_t)(x)) << DCDC_CTRL1_VDD1P0CTRL_TRG_SHIFT)) & DCDC_CTRL1_VDD1P0CTRL_TRG_MASK)

#define DCDC_CTRL1_VDD1P8CTRL_STBY_TRG_MASK      (0x1F0000U)
#define DCDC_CTRL1_VDD1P8CTRL_STBY_TRG_SHIFT     (16U)
/*! VDD1P8CTRL_STBY_TRG
 *  0b00000..1.525V
 *  0b01011..1.8V
 *  0b11111..2.3V
 */
#define DCDC_CTRL1_VDD1P8CTRL_STBY_TRG(x)        (((uint32_t)(((uint32_t)(x)) << DCDC_CTRL1_VDD1P8CTRL_STBY_TRG_SHIFT)) & DCDC_CTRL1_VDD1P8CTRL_STBY_TRG_MASK)

#define DCDC_CTRL1_VDD1P0CTRL_STBY_TRG_MASK      (0x1F000000U)
#define DCDC_CTRL1_VDD1P0CTRL_STBY_TRG_SHIFT     (24U)
/*! VDD1P0CTRL_STBY_TRG
 *  0b00000..0.625V
 *  0b01111..1.0V
 *  0b11111..1.4V
 */
#define DCDC_CTRL1_VDD1P0CTRL_STBY_TRG(x)        (((uint32_t)(((uint32_t)(x)) << DCDC_CTRL1_VDD1P0CTRL_STBY_TRG_SHIFT)) & DCDC_CTRL1_VDD1P0CTRL_STBY_TRG_MASK)
/*! @} */

/*! @name REG0 - DCDC Register 0 */
/*! @{ */

#define DCDC_REG0_PWD_ZCD_MASK                   (0x1U)
#define DCDC_REG0_PWD_ZCD_SHIFT                  (0U)
/*! PWD_ZCD - Power Down Zero Cross Detection
 *  0b0..Zero cross detetion function powered up
 *  0b1..Zero cross detetion function powered down
 */
#define DCDC_REG0_PWD_ZCD(x)                     (((uint32_t)(((uint32_t)(x)) << DCDC_REG0_PWD_ZCD_SHIFT)) & DCDC_REG0_PWD_ZCD_MASK)

#define DCDC_REG0_DISABLE_AUTO_CLK_SWITCH_MASK   (0x2U)
#define DCDC_REG0_DISABLE_AUTO_CLK_SWITCH_SHIFT  (1U)
/*! DISABLE_AUTO_CLK_SWITCH - Disable Auto Clock Switch
 *  0b0..If DISABLE_AUTO_CLK_SWITCH is set to 0 and 24M xtal is OK, the clock source will switch from internal
 *       ring oscillator to 24M xtal automatically
 *  0b1..If DISABLE_AUTO_CLK_SWITCH is set to 1, SEL_CLK will determine which clock source the DCDC uses
 */
#define DCDC_REG0_DISABLE_AUTO_CLK_SWITCH(x)     (((uint32_t)(((uint32_t)(x)) << DCDC_REG0_DISABLE_AUTO_CLK_SWITCH_SHIFT)) & DCDC_REG0_DISABLE_AUTO_CLK_SWITCH_MASK)

#define DCDC_REG0_SEL_CLK_MASK                   (0x4U)
#define DCDC_REG0_SEL_CLK_SHIFT                  (2U)
/*! SEL_CLK - Select Clock
 *  0b0..DCDC uses internal ring oscillator
 *  0b1..DCDC uses 24M xtal
 */
#define DCDC_REG0_SEL_CLK(x)                     (((uint32_t)(((uint32_t)(x)) << DCDC_REG0_SEL_CLK_SHIFT)) & DCDC_REG0_SEL_CLK_MASK)

#define DCDC_REG0_PWD_OSC_INT_MASK               (0x8U)
#define DCDC_REG0_PWD_OSC_INT_SHIFT              (3U)
/*! PWD_OSC_INT - Power down internal ring oscillator
 *  0b0..Internal ring oscillator powered up
 *  0b1..Internal ring oscillator powered down
 */
#define DCDC_REG0_PWD_OSC_INT(x)                 (((uint32_t)(((uint32_t)(x)) << DCDC_REG0_PWD_OSC_INT_SHIFT)) & DCDC_REG0_PWD_OSC_INT_MASK)

#define DCDC_REG0_PWD_CUR_SNS_CMP_MASK           (0x10U)
#define DCDC_REG0_PWD_CUR_SNS_CMP_SHIFT          (4U)
/*! PWD_CUR_SNS_CMP - Power down signal of the current detector
 *  0b0..Current Detector powered up
 *  0b1..Current Detector powered down
 */
#define DCDC_REG0_PWD_CUR_SNS_CMP(x)             (((uint32_t)(((uint32_t)(x)) << DCDC_REG0_PWD_CUR_SNS_CMP_SHIFT)) & DCDC_REG0_PWD_CUR_SNS_CMP_MASK)

#define DCDC_REG0_CUR_SNS_THRSH_MASK             (0xE0U)
#define DCDC_REG0_CUR_SNS_THRSH_SHIFT            (5U)
/*! CUR_SNS_THRSH - Current Sense (detector) Threshold */
#define DCDC_REG0_CUR_SNS_THRSH(x)               (((uint32_t)(((uint32_t)(x)) << DCDC_REG0_CUR_SNS_THRSH_SHIFT)) & DCDC_REG0_CUR_SNS_THRSH_MASK)

#define DCDC_REG0_PWD_OVERCUR_DET_MASK           (0x100U)
#define DCDC_REG0_PWD_OVERCUR_DET_SHIFT          (8U)
/*! PWD_OVERCUR_DET - Power down overcurrent detection comparator
 *  0b0..Overcurrent detection comparator is enabled
 *  0b1..Overcurrent detection comparator is disabled
 */
#define DCDC_REG0_PWD_OVERCUR_DET(x)             (((uint32_t)(((uint32_t)(x)) << DCDC_REG0_PWD_OVERCUR_DET_SHIFT)) & DCDC_REG0_PWD_OVERCUR_DET_MASK)

#define DCDC_REG0_PWD_CMP_DCDC_IN_DET_MASK       (0x800U)
#define DCDC_REG0_PWD_CMP_DCDC_IN_DET_SHIFT      (11U)
/*! PWD_CMP_DCDC_IN_DET
 *  0b0..Low voltage detection comparator is enabled
 *  0b1..Low voltage detection comparator is disabled
 */
#define DCDC_REG0_PWD_CMP_DCDC_IN_DET(x)         (((uint32_t)(((uint32_t)(x)) << DCDC_REG0_PWD_CMP_DCDC_IN_DET_SHIFT)) & DCDC_REG0_PWD_CMP_DCDC_IN_DET_MASK)

#define DCDC_REG0_PWD_HIGH_VDD1P8_DET_MASK       (0x10000U)
#define DCDC_REG0_PWD_HIGH_VDD1P8_DET_SHIFT      (16U)
/*! PWD_HIGH_VDD1P8_DET - Power Down High Voltage Detection for VDD1P8
 *  0b0..Overvoltage detection comparator for the VDD1P8 output is enabled
 *  0b1..Overvoltage detection comparator for the VDD1P8 output is disabled
 */
#define DCDC_REG0_PWD_HIGH_VDD1P8_DET(x)         (((uint32_t)(((uint32_t)(x)) << DCDC_REG0_PWD_HIGH_VDD1P8_DET_SHIFT)) & DCDC_REG0_PWD_HIGH_VDD1P8_DET_MASK)

#define DCDC_REG0_PWD_HIGH_VDD1P0_DET_MASK       (0x20000U)
#define DCDC_REG0_PWD_HIGH_VDD1P0_DET_SHIFT      (17U)
/*! PWD_HIGH_VDD1P0_DET - Power Down High Voltage Detection for VDD1P0
 *  0b0..Overvoltage detection comparator for the VDD1P0 output is enabled
 *  0b1..Overvoltage detection comparator for the VDD1P0 output is disabled
 */
#define DCDC_REG0_PWD_HIGH_VDD1P0_DET(x)         (((uint32_t)(((uint32_t)(x)) << DCDC_REG0_PWD_HIGH_VDD1P0_DET_SHIFT)) & DCDC_REG0_PWD_HIGH_VDD1P0_DET_MASK)

#define DCDC_REG0_LP_HIGH_HYS_MASK               (0x200000U)
#define DCDC_REG0_LP_HIGH_HYS_SHIFT              (21U)
/*! LP_HIGH_HYS - Low Power High Hysteric Value
 *  0b0..Adjust hysteretic value in low power to 12.5mV
 *  0b1..Adjust hysteretic value in low power to 25mV
 */
#define DCDC_REG0_LP_HIGH_HYS(x)                 (((uint32_t)(((uint32_t)(x)) << DCDC_REG0_LP_HIGH_HYS_SHIFT)) & DCDC_REG0_LP_HIGH_HYS_MASK)

#define DCDC_REG0_PWD_CMP_OFFSET_MASK            (0x4000000U)
#define DCDC_REG0_PWD_CMP_OFFSET_SHIFT           (26U)
/*! PWD_CMP_OFFSET - power down the out-of-range detection comparator
 *  0b0..Out-of-range comparator powered up
 *  0b1..Out-of-range comparator powered down
 */
#define DCDC_REG0_PWD_CMP_OFFSET(x)              (((uint32_t)(((uint32_t)(x)) << DCDC_REG0_PWD_CMP_OFFSET_SHIFT)) & DCDC_REG0_PWD_CMP_OFFSET_MASK)

#define DCDC_REG0_XTALOK_DISABLE_MASK            (0x8000000U)
#define DCDC_REG0_XTALOK_DISABLE_SHIFT           (27U)
/*! XTALOK_DISABLE - Disable xtalok detection circuit
 *  0b0..Enable xtalok detection circuit
 *  0b1..Disable xtalok detection circuit and always outputs OK signal "1"
 */
#define DCDC_REG0_XTALOK_DISABLE(x)              (((uint32_t)(((uint32_t)(x)) << DCDC_REG0_XTALOK_DISABLE_SHIFT)) & DCDC_REG0_XTALOK_DISABLE_MASK)

#define DCDC_REG0_XTAL_24M_OK_MASK               (0x20000000U)
#define DCDC_REG0_XTAL_24M_OK_SHIFT              (29U)
/*! XTAL_24M_OK - 24M XTAL OK
 *  0b0..DCDC uses internal ring oscillator
 *  0b1..DCDC uses xtal 24M
 */
#define DCDC_REG0_XTAL_24M_OK(x)                 (((uint32_t)(((uint32_t)(x)) << DCDC_REG0_XTAL_24M_OK_SHIFT)) & DCDC_REG0_XTAL_24M_OK_MASK)

#define DCDC_REG0_STS_DC_OK_MASK                 (0x80000000U)
#define DCDC_REG0_STS_DC_OK_SHIFT                (31U)
/*! STS_DC_OK - DCDC Output OK
 *  0b0..DCDC is settling
 *  0b1..DCDC already settled
 */
#define DCDC_REG0_STS_DC_OK(x)                   (((uint32_t)(((uint32_t)(x)) << DCDC_REG0_STS_DC_OK_SHIFT)) & DCDC_REG0_STS_DC_OK_MASK)
/*! @} */

/*! @name REG1 - DCDC Register 1 */
/*! @{ */

#define DCDC_REG1_DM_CTRL_MASK                   (0x8U)
#define DCDC_REG1_DM_CTRL_SHIFT                  (3U)
/*! DM_CTRL - DM Control
 *  0b0..No change to ripple when the discontinuous current is present in DCM.
 *  0b1..Improves ripple when the inductor current goes to zero in DCM.
 */
#define DCDC_REG1_DM_CTRL(x)                     (((uint32_t)(((uint32_t)(x)) << DCDC_REG1_DM_CTRL_SHIFT)) & DCDC_REG1_DM_CTRL_MASK)

#define DCDC_REG1_RLOAD_REG_EN_LPSR_MASK         (0x10U)
#define DCDC_REG1_RLOAD_REG_EN_LPSR_SHIFT        (4U)
/*! RLOAD_REG_EN_LPSR - Load Resistor Enable
 *  0b0..Disconnect load resistor
 *  0b1..Connect load resistor
 */
#define DCDC_REG1_RLOAD_REG_EN_LPSR(x)           (((uint32_t)(((uint32_t)(x)) << DCDC_REG1_RLOAD_REG_EN_LPSR_SHIFT)) & DCDC_REG1_RLOAD_REG_EN_LPSR_MASK)

#define DCDC_REG1_VBG_TRIM_MASK                  (0x7C0U)
#define DCDC_REG1_VBG_TRIM_SHIFT                 (6U)
/*! VBG_TRIM - Trim Bandgap Voltage
 *  0b00000..0.452V
 *  0b10000..0.5V
 *  0b11111..0.545V
 */
#define DCDC_REG1_VBG_TRIM(x)                    (((uint32_t)(((uint32_t)(x)) << DCDC_REG1_VBG_TRIM_SHIFT)) & DCDC_REG1_VBG_TRIM_MASK)

#define DCDC_REG1_LP_CMP_ISRC_SEL_MASK           (0x1800U)
#define DCDC_REG1_LP_CMP_ISRC_SEL_SHIFT          (11U)
/*! LP_CMP_ISRC_SEL - Low Power Comparator Current Bias
 *  0b00..50nA
 *  0b01..100nA
 *  0b10..200nA
 *  0b11..400nA
 */
#define DCDC_REG1_LP_CMP_ISRC_SEL(x)             (((uint32_t)(((uint32_t)(x)) << DCDC_REG1_LP_CMP_ISRC_SEL_SHIFT)) & DCDC_REG1_LP_CMP_ISRC_SEL_MASK)

#define DCDC_REG1_LOOPCTRL_CM_HST_THRESH_MASK    (0x8000000U)
#define DCDC_REG1_LOOPCTRL_CM_HST_THRESH_SHIFT   (27U)
/*! LOOPCTRL_CM_HST_THRESH - Increase Threshold Detection */
#define DCDC_REG1_LOOPCTRL_CM_HST_THRESH(x)      (((uint32_t)(((uint32_t)(x)) << DCDC_REG1_LOOPCTRL_CM_HST_THRESH_SHIFT)) & DCDC_REG1_LOOPCTRL_CM_HST_THRESH_MASK)

#define DCDC_REG1_LOOPCTRL_DF_HST_THRESH_MASK    (0x10000000U)
#define DCDC_REG1_LOOPCTRL_DF_HST_THRESH_SHIFT   (28U)
/*! LOOPCTRL_DF_HST_THRESH - Increase Threshold Detection */
#define DCDC_REG1_LOOPCTRL_DF_HST_THRESH(x)      (((uint32_t)(((uint32_t)(x)) << DCDC_REG1_LOOPCTRL_DF_HST_THRESH_SHIFT)) & DCDC_REG1_LOOPCTRL_DF_HST_THRESH_MASK)

#define DCDC_REG1_LOOPCTRL_EN_CM_HYST_MASK       (0x20000000U)
#define DCDC_REG1_LOOPCTRL_EN_CM_HYST_SHIFT      (29U)
/*! LOOPCTRL_EN_CM_HYST
 *  0b0..Disable hysteresis in switching converter common mode analog comparators
 *  0b1..Enable hysteresis in switching converter common mode analog comparators
 */
#define DCDC_REG1_LOOPCTRL_EN_CM_HYST(x)         (((uint32_t)(((uint32_t)(x)) << DCDC_REG1_LOOPCTRL_EN_CM_HYST_SHIFT)) & DCDC_REG1_LOOPCTRL_EN_CM_HYST_MASK)

#define DCDC_REG1_LOOPCTRL_EN_DF_HYST_MASK       (0x40000000U)
#define DCDC_REG1_LOOPCTRL_EN_DF_HYST_SHIFT      (30U)
/*! LOOPCTRL_EN_DF_HYST
 *  0b0..Disable hysteresis in switching converter differential mode analog comparators
 *  0b1..Enable hysteresis in switching converter differential mode analog comparators
 */
#define DCDC_REG1_LOOPCTRL_EN_DF_HYST(x)         (((uint32_t)(((uint32_t)(x)) << DCDC_REG1_LOOPCTRL_EN_DF_HYST_SHIFT)) & DCDC_REG1_LOOPCTRL_EN_DF_HYST_MASK)
/*! @} */

/*! @name REG2 - DCDC Register 2 */
/*! @{ */

#define DCDC_REG2_LOOPCTRL_DC_C_MASK             (0x3U)
#define DCDC_REG2_LOOPCTRL_DC_C_SHIFT            (0U)
#define DCDC_REG2_LOOPCTRL_DC_C(x)               (((uint32_t)(((uint32_t)(x)) << DCDC_REG2_LOOPCTRL_DC_C_SHIFT)) & DCDC_REG2_LOOPCTRL_DC_C_MASK)

#define DCDC_REG2_LOOPCTRL_DC_R_MASK             (0x3CU)
#define DCDC_REG2_LOOPCTRL_DC_R_SHIFT            (2U)
#define DCDC_REG2_LOOPCTRL_DC_R(x)               (((uint32_t)(((uint32_t)(x)) << DCDC_REG2_LOOPCTRL_DC_R_SHIFT)) & DCDC_REG2_LOOPCTRL_DC_R_MASK)

#define DCDC_REG2_LOOPCTRL_DC_FF_MASK            (0x1C0U)
#define DCDC_REG2_LOOPCTRL_DC_FF_SHIFT           (6U)
#define DCDC_REG2_LOOPCTRL_DC_FF(x)              (((uint32_t)(((uint32_t)(x)) << DCDC_REG2_LOOPCTRL_DC_FF_SHIFT)) & DCDC_REG2_LOOPCTRL_DC_FF_MASK)

#define DCDC_REG2_LOOPCTRL_EN_RCSCALE_MASK       (0xE00U)
#define DCDC_REG2_LOOPCTRL_EN_RCSCALE_SHIFT      (9U)
/*! LOOPCTRL_EN_RCSCALE - Enable RC Scale */
#define DCDC_REG2_LOOPCTRL_EN_RCSCALE(x)         (((uint32_t)(((uint32_t)(x)) << DCDC_REG2_LOOPCTRL_EN_RCSCALE_SHIFT)) & DCDC_REG2_LOOPCTRL_EN_RCSCALE_MASK)

#define DCDC_REG2_LOOPCTRL_RCSCALE_THRSH_MASK    (0x1000U)
#define DCDC_REG2_LOOPCTRL_RCSCALE_THRSH_SHIFT   (12U)
#define DCDC_REG2_LOOPCTRL_RCSCALE_THRSH(x)      (((uint32_t)(((uint32_t)(x)) << DCDC_REG2_LOOPCTRL_RCSCALE_THRSH_SHIFT)) & DCDC_REG2_LOOPCTRL_RCSCALE_THRSH_MASK)

#define DCDC_REG2_LOOPCTRL_HYST_SIGN_MASK        (0x2000U)
#define DCDC_REG2_LOOPCTRL_HYST_SIGN_SHIFT       (13U)
#define DCDC_REG2_LOOPCTRL_HYST_SIGN(x)          (((uint32_t)(((uint32_t)(x)) << DCDC_REG2_LOOPCTRL_HYST_SIGN_SHIFT)) & DCDC_REG2_LOOPCTRL_HYST_SIGN_MASK)

#define DCDC_REG2_BATTMONITOR_EN_BATADJ_MASK     (0x8000U)
#define DCDC_REG2_BATTMONITOR_EN_BATADJ_SHIFT    (15U)
#define DCDC_REG2_BATTMONITOR_EN_BATADJ(x)       (((uint32_t)(((uint32_t)(x)) << DCDC_REG2_BATTMONITOR_EN_BATADJ_SHIFT)) & DCDC_REG2_BATTMONITOR_EN_BATADJ_MASK)

#define DCDC_REG2_BATTMONITOR_BATT_VAL_MASK      (0x3FF0000U)
#define DCDC_REG2_BATTMONITOR_BATT_VAL_SHIFT     (16U)
#define DCDC_REG2_BATTMONITOR_BATT_VAL(x)        (((uint32_t)(((uint32_t)(x)) << DCDC_REG2_BATTMONITOR_BATT_VAL_SHIFT)) & DCDC_REG2_BATTMONITOR_BATT_VAL_MASK)

#define DCDC_REG2_DCM_SET_CTRL_MASK              (0x10000000U)
#define DCDC_REG2_DCM_SET_CTRL_SHIFT             (28U)
/*! DCM_SET_CTRL - DCM Set Control */
#define DCDC_REG2_DCM_SET_CTRL(x)                (((uint32_t)(((uint32_t)(x)) << DCDC_REG2_DCM_SET_CTRL_SHIFT)) & DCDC_REG2_DCM_SET_CTRL_MASK)

#define DCDC_REG2_LOOPCTRL_TOGGLE_DIF_MASK       (0x40000000U)
#define DCDC_REG2_LOOPCTRL_TOGGLE_DIF_SHIFT      (30U)
#define DCDC_REG2_LOOPCTRL_TOGGLE_DIF(x)         (((uint32_t)(((uint32_t)(x)) << DCDC_REG2_LOOPCTRL_TOGGLE_DIF_SHIFT)) & DCDC_REG2_LOOPCTRL_TOGGLE_DIF_MASK)
/*! @} */

/*! @name REG3 - DCDC Register 3 */
/*! @{ */

#define DCDC_REG3_IN_BROWNOUT_MASK               (0x4000U)
#define DCDC_REG3_IN_BROWNOUT_SHIFT              (14U)
/*! IN_BROWNOUT
 *  0b1..DCDC_IN is lower than 2.6V
 */
#define DCDC_REG3_IN_BROWNOUT(x)                 (((uint32_t)(((uint32_t)(x)) << DCDC_REG3_IN_BROWNOUT_SHIFT)) & DCDC_REG3_IN_BROWNOUT_MASK)

#define DCDC_REG3_OVERVOLT_VDD1P8_DET_OUT_MASK   (0x8000U)
#define DCDC_REG3_OVERVOLT_VDD1P8_DET_OUT_SHIFT  (15U)
/*! OVERVOLT_VDD1P8_DET_OUT
 *  0b1..VDD1P8 Overvoltage
 */
#define DCDC_REG3_OVERVOLT_VDD1P8_DET_OUT(x)     (((uint32_t)(((uint32_t)(x)) << DCDC_REG3_OVERVOLT_VDD1P8_DET_OUT_SHIFT)) & DCDC_REG3_OVERVOLT_VDD1P8_DET_OUT_MASK)

#define DCDC_REG3_OVERVOLT_VDD1P0_DET_OUT_MASK   (0x10000U)
#define DCDC_REG3_OVERVOLT_VDD1P0_DET_OUT_SHIFT  (16U)
/*! OVERVOLT_VDD1P0_DET_OUT
 *  0b1..VDD1P0 Overvoltage
 */
#define DCDC_REG3_OVERVOLT_VDD1P0_DET_OUT(x)     (((uint32_t)(((uint32_t)(x)) << DCDC_REG3_OVERVOLT_VDD1P0_DET_OUT_SHIFT)) & DCDC_REG3_OVERVOLT_VDD1P0_DET_OUT_MASK)

#define DCDC_REG3_OVERCUR_DETECT_OUT_MASK        (0x20000U)
#define DCDC_REG3_OVERCUR_DETECT_OUT_SHIFT       (17U)
/*! OVERCUR_DETECT_OUT
 *  0b1..Overcurrent
 */
#define DCDC_REG3_OVERCUR_DETECT_OUT(x)          (((uint32_t)(((uint32_t)(x)) << DCDC_REG3_OVERCUR_DETECT_OUT_SHIFT)) & DCDC_REG3_OVERCUR_DETECT_OUT_MASK)

#define DCDC_REG3_ENABLE_FF_MASK                 (0x40000U)
#define DCDC_REG3_ENABLE_FF_SHIFT                (18U)
/*! ENABLE_FF
 *  0b1..Enable feed-forward (FF) function that can speed up transient settling.
 */
#define DCDC_REG3_ENABLE_FF(x)                   (((uint32_t)(((uint32_t)(x)) << DCDC_REG3_ENABLE_FF_SHIFT)) & DCDC_REG3_ENABLE_FF_MASK)

#define DCDC_REG3_DISABLE_PULSE_SKIP_MASK        (0x80000U)
#define DCDC_REG3_DISABLE_PULSE_SKIP_SHIFT       (19U)
/*! DISABLE_PULSE_SKIP - Disable Pulse Skip
 *  0b0..Stop charging if the duty cycle is lower than what is set by NEGLIMIT_IN
 */
#define DCDC_REG3_DISABLE_PULSE_SKIP(x)          (((uint32_t)(((uint32_t)(x)) << DCDC_REG3_DISABLE_PULSE_SKIP_SHIFT)) & DCDC_REG3_DISABLE_PULSE_SKIP_MASK)

#define DCDC_REG3_DISABLE_IDLE_SKIP_MASK         (0x100000U)
#define DCDC_REG3_DISABLE_IDLE_SKIP_SHIFT        (20U)
/*! DISABLE_IDLE_SKIP
 *  0b0..Enable the idle skip function. The DCDC will be idle when out-of-range comparator detects the output
 *       voltage is higher than the target by 25mV. This function requires the out-of-range comparator to be enabled
 *       (PWD_CMP_OFFSET=0).
 */
#define DCDC_REG3_DISABLE_IDLE_SKIP(x)           (((uint32_t)(((uint32_t)(x)) << DCDC_REG3_DISABLE_IDLE_SKIP_SHIFT)) & DCDC_REG3_DISABLE_IDLE_SKIP_MASK)

#define DCDC_REG3_DOUBLE_IBIAS_CMP_LP_LPSR_MASK  (0x200000U)
#define DCDC_REG3_DOUBLE_IBIAS_CMP_LP_LPSR_SHIFT (21U)
/*! DOUBLE_IBIAS_CMP_LP_LPSR
 *  0b1..Double the bias current of the comparator for low-voltage detector in LP (low-power) mode
 */
#define DCDC_REG3_DOUBLE_IBIAS_CMP_LP_LPSR(x)    (((uint32_t)(((uint32_t)(x)) << DCDC_REG3_DOUBLE_IBIAS_CMP_LP_LPSR_SHIFT)) & DCDC_REG3_DOUBLE_IBIAS_CMP_LP_LPSR_MASK)

#define DCDC_REG3_REG_FBK_SEL_MASK               (0xC00000U)
#define DCDC_REG3_REG_FBK_SEL_SHIFT              (22U)
#define DCDC_REG3_REG_FBK_SEL(x)                 (((uint32_t)(((uint32_t)(x)) << DCDC_REG3_REG_FBK_SEL_SHIFT)) & DCDC_REG3_REG_FBK_SEL_MASK)

#define DCDC_REG3_MINPWR_DC_HALFCLK_MASK         (0x1000000U)
#define DCDC_REG3_MINPWR_DC_HALFCLK_SHIFT        (24U)
/*! MINPWR_DC_HALFCLK
 *  0b0..DCDC clock remains at full frequency for continuous mode
 *  0b1..DCDC clock set to half frequency for continuous mode
 */
#define DCDC_REG3_MINPWR_DC_HALFCLK(x)           (((uint32_t)(((uint32_t)(x)) << DCDC_REG3_MINPWR_DC_HALFCLK_SHIFT)) & DCDC_REG3_MINPWR_DC_HALFCLK_MASK)

#define DCDC_REG3_MINPWR_HALF_FETS_MASK          (0x4000000U)
#define DCDC_REG3_MINPWR_HALF_FETS_SHIFT         (26U)
#define DCDC_REG3_MINPWR_HALF_FETS(x)            (((uint32_t)(((uint32_t)(x)) << DCDC_REG3_MINPWR_HALF_FETS_SHIFT)) & DCDC_REG3_MINPWR_HALF_FETS_MASK)

#define DCDC_REG3_MISC_DELAY_TIMING_MASK         (0x8000000U)
#define DCDC_REG3_MISC_DELAY_TIMING_SHIFT        (27U)
/*! MISC_DELAY_TIMING - Miscellaneous Delay Timing */
#define DCDC_REG3_MISC_DELAY_TIMING(x)           (((uint32_t)(((uint32_t)(x)) << DCDC_REG3_MISC_DELAY_TIMING_SHIFT)) & DCDC_REG3_MISC_DELAY_TIMING_MASK)

#define DCDC_REG3_VDD1P0CTRL_DISABLE_STEP_MASK   (0x20000000U)
#define DCDC_REG3_VDD1P0CTRL_DISABLE_STEP_SHIFT  (29U)
/*! VDD1P0CTRL_DISABLE_STEP - Disable Step for VDD1P0
 *  0b0..Enable stepping for VDD1P0
 *  0b1..Disable stepping for VDD1P0
 */
#define DCDC_REG3_VDD1P0CTRL_DISABLE_STEP(x)     (((uint32_t)(((uint32_t)(x)) << DCDC_REG3_VDD1P0CTRL_DISABLE_STEP_SHIFT)) & DCDC_REG3_VDD1P0CTRL_DISABLE_STEP_MASK)

#define DCDC_REG3_VDD1P8CTRL_DISABLE_STEP_MASK   (0x40000000U)
#define DCDC_REG3_VDD1P8CTRL_DISABLE_STEP_SHIFT  (30U)
/*! VDD1P8CTRL_DISABLE_STEP - Disable Step for VDD1P8
 *  0b0..Enable stepping for VDD1P8
 *  0b1..Disable stepping for VDD1P8
 */
#define DCDC_REG3_VDD1P8CTRL_DISABLE_STEP(x)     (((uint32_t)(((uint32_t)(x)) << DCDC_REG3_VDD1P8CTRL_DISABLE_STEP_SHIFT)) & DCDC_REG3_VDD1P8CTRL_DISABLE_STEP_MASK)
/*! @} */

/*! @name REG4 - DCDC Register 4 */
/*! @{ */

#define DCDC_REG4_ENABLE_SP_MASK                 (0xFFFFU)
#define DCDC_REG4_ENABLE_SP_SHIFT                (0U)
#define DCDC_REG4_ENABLE_SP(x)                   (((uint32_t)(((uint32_t)(x)) << DCDC_REG4_ENABLE_SP_SHIFT)) & DCDC_REG4_ENABLE_SP_MASK)
/*! @} */

/*! @name REG5 - DCDC Register 5 */
/*! @{ */

#define DCDC_REG5_DIG_EN_SP_MASK                 (0xFFFFU)
#define DCDC_REG5_DIG_EN_SP_SHIFT                (0U)
#define DCDC_REG5_DIG_EN_SP(x)                   (((uint32_t)(((uint32_t)(x)) << DCDC_REG5_DIG_EN_SP_SHIFT)) & DCDC_REG5_DIG_EN_SP_MASK)
/*! @} */

/*! @name REG6 - DCDC Register 6 */
/*! @{ */

#define DCDC_REG6_LP_MODE_SP_MASK                (0xFFFFU)
#define DCDC_REG6_LP_MODE_SP_SHIFT               (0U)
#define DCDC_REG6_LP_MODE_SP(x)                  (((uint32_t)(((uint32_t)(x)) << DCDC_REG6_LP_MODE_SP_SHIFT)) & DCDC_REG6_LP_MODE_SP_MASK)
/*! @} */

/*! @name REG7 - DCDC Register 7 */
/*! @{ */

#define DCDC_REG7_STBY_EN_SP_MASK                (0xFFFFU)
#define DCDC_REG7_STBY_EN_SP_SHIFT               (0U)
#define DCDC_REG7_STBY_EN_SP(x)                  (((uint32_t)(((uint32_t)(x)) << DCDC_REG7_STBY_EN_SP_SHIFT)) & DCDC_REG7_STBY_EN_SP_MASK)
/*! @} */

/*! @name REG7P - DCDC Register 7 plus */
/*! @{ */

#define DCDC_REG7P_STBY_LP_MODE_SP_MASK          (0xFFFFU)
#define DCDC_REG7P_STBY_LP_MODE_SP_SHIFT         (0U)
#define DCDC_REG7P_STBY_LP_MODE_SP(x)            (((uint32_t)(((uint32_t)(x)) << DCDC_REG7P_STBY_LP_MODE_SP_SHIFT)) & DCDC_REG7P_STBY_LP_MODE_SP_MASK)
/*! @} */

/*! @name REG8 - DCDC Register 8 */
/*! @{ */

#define DCDC_REG8_ANA_TRG_SP0_MASK               (0xFFFFFFFFU)
#define DCDC_REG8_ANA_TRG_SP0_SHIFT              (0U)
#define DCDC_REG8_ANA_TRG_SP0(x)                 (((uint32_t)(((uint32_t)(x)) << DCDC_REG8_ANA_TRG_SP0_SHIFT)) & DCDC_REG8_ANA_TRG_SP0_MASK)
/*! @} */

/*! @name REG9 - DCDC Register 9 */
/*! @{ */

#define DCDC_REG9_ANA_TRG_SP1_MASK               (0xFFFFFFFFU)
#define DCDC_REG9_ANA_TRG_SP1_SHIFT              (0U)
#define DCDC_REG9_ANA_TRG_SP1(x)                 (((uint32_t)(((uint32_t)(x)) << DCDC_REG9_ANA_TRG_SP1_SHIFT)) & DCDC_REG9_ANA_TRG_SP1_MASK)
/*! @} */

/*! @name REG10 - DCDC Register 10 */
/*! @{ */

#define DCDC_REG10_ANA_TRG_SP2_MASK              (0xFFFFFFFFU)
#define DCDC_REG10_ANA_TRG_SP2_SHIFT             (0U)
#define DCDC_REG10_ANA_TRG_SP2(x)                (((uint32_t)(((uint32_t)(x)) << DCDC_REG10_ANA_TRG_SP2_SHIFT)) & DCDC_REG10_ANA_TRG_SP2_MASK)
/*! @} */

/*! @name REG11 - DCDC Register 11 */
/*! @{ */

#define DCDC_REG11_ANA_TRG_SP3_MASK              (0xFFFFFFFFU)
#define DCDC_REG11_ANA_TRG_SP3_SHIFT             (0U)
#define DCDC_REG11_ANA_TRG_SP3(x)                (((uint32_t)(((uint32_t)(x)) << DCDC_REG11_ANA_TRG_SP3_SHIFT)) & DCDC_REG11_ANA_TRG_SP3_MASK)
/*! @} */

/*! @name REG12 - DCDC Register 12 */
/*! @{ */

#define DCDC_REG12_DIG_TRG_SP0_MASK              (0xFFFFFFFFU)
#define DCDC_REG12_DIG_TRG_SP0_SHIFT             (0U)
#define DCDC_REG12_DIG_TRG_SP0(x)                (((uint32_t)(((uint32_t)(x)) << DCDC_REG12_DIG_TRG_SP0_SHIFT)) & DCDC_REG12_DIG_TRG_SP0_MASK)
/*! @} */

/*! @name REG13 - DCDC Register 13 */
/*! @{ */

#define DCDC_REG13_DIG_TRG_SP1_MASK              (0xFFFFFFFFU)
#define DCDC_REG13_DIG_TRG_SP1_SHIFT             (0U)
#define DCDC_REG13_DIG_TRG_SP1(x)                (((uint32_t)(((uint32_t)(x)) << DCDC_REG13_DIG_TRG_SP1_SHIFT)) & DCDC_REG13_DIG_TRG_SP1_MASK)
/*! @} */

/*! @name REG14 - DCDC Register 14 */
/*! @{ */

#define DCDC_REG14_DIG_TRG_SP2_MASK              (0xFFFFFFFFU)
#define DCDC_REG14_DIG_TRG_SP2_SHIFT             (0U)
#define DCDC_REG14_DIG_TRG_SP2(x)                (((uint32_t)(((uint32_t)(x)) << DCDC_REG14_DIG_TRG_SP2_SHIFT)) & DCDC_REG14_DIG_TRG_SP2_MASK)
/*! @} */

/*! @name REG15 - DCDC Register 15 */
/*! @{ */

#define DCDC_REG15_DIG_TRG_SP3_MASK              (0xFFFFFFFFU)
#define DCDC_REG15_DIG_TRG_SP3_SHIFT             (0U)
#define DCDC_REG15_DIG_TRG_SP3(x)                (((uint32_t)(((uint32_t)(x)) << DCDC_REG15_DIG_TRG_SP3_SHIFT)) & DCDC_REG15_DIG_TRG_SP3_MASK)
/*! @} */

/*! @name REG16 - DCDC Register 16 */
/*! @{ */

#define DCDC_REG16_ANA_STBY_TRG_SP0_MASK         (0xFFFFFFFFU)
#define DCDC_REG16_ANA_STBY_TRG_SP0_SHIFT        (0U)
#define DCDC_REG16_ANA_STBY_TRG_SP0(x)           (((uint32_t)(((uint32_t)(x)) << DCDC_REG16_ANA_STBY_TRG_SP0_SHIFT)) & DCDC_REG16_ANA_STBY_TRG_SP0_MASK)
/*! @} */

/*! @name REG17 - DCDC Register 17 */
/*! @{ */

#define DCDC_REG17_ANA_STBY_TRG_SP1_MASK         (0xFFFFFFFFU)
#define DCDC_REG17_ANA_STBY_TRG_SP1_SHIFT        (0U)
#define DCDC_REG17_ANA_STBY_TRG_SP1(x)           (((uint32_t)(((uint32_t)(x)) << DCDC_REG17_ANA_STBY_TRG_SP1_SHIFT)) & DCDC_REG17_ANA_STBY_TRG_SP1_MASK)
/*! @} */

/*! @name REG18 - DCDC Register 18 */
/*! @{ */

#define DCDC_REG18_ANA_STBY_TRG_SP2_MASK         (0xFFFFFFFFU)
#define DCDC_REG18_ANA_STBY_TRG_SP2_SHIFT        (0U)
#define DCDC_REG18_ANA_STBY_TRG_SP2(x)           (((uint32_t)(((uint32_t)(x)) << DCDC_REG18_ANA_STBY_TRG_SP2_SHIFT)) & DCDC_REG18_ANA_STBY_TRG_SP2_MASK)
/*! @} */

/*! @name REG19 - DCDC Register 19 */
/*! @{ */

#define DCDC_REG19_ANA_STBY_TRG_SP3_MASK         (0xFFFFFFFFU)
#define DCDC_REG19_ANA_STBY_TRG_SP3_SHIFT        (0U)
#define DCDC_REG19_ANA_STBY_TRG_SP3(x)           (((uint32_t)(((uint32_t)(x)) << DCDC_REG19_ANA_STBY_TRG_SP3_SHIFT)) & DCDC_REG19_ANA_STBY_TRG_SP3_MASK)
/*! @} */

/*! @name REG20 - DCDC Register 20 */
/*! @{ */

#define DCDC_REG20_DIG_STBY_TRG_SP0_MASK         (0xFFFFFFFFU)
#define DCDC_REG20_DIG_STBY_TRG_SP0_SHIFT        (0U)
#define DCDC_REG20_DIG_STBY_TRG_SP0(x)           (((uint32_t)(((uint32_t)(x)) << DCDC_REG20_DIG_STBY_TRG_SP0_SHIFT)) & DCDC_REG20_DIG_STBY_TRG_SP0_MASK)
/*! @} */

/*! @name REG21 - DCDC Register 21 */
/*! @{ */

#define DCDC_REG21_DIG_STBY_TRG_SP1_MASK         (0xFFFFFFFFU)
#define DCDC_REG21_DIG_STBY_TRG_SP1_SHIFT        (0U)
#define DCDC_REG21_DIG_STBY_TRG_SP1(x)           (((uint32_t)(((uint32_t)(x)) << DCDC_REG21_DIG_STBY_TRG_SP1_SHIFT)) & DCDC_REG21_DIG_STBY_TRG_SP1_MASK)
/*! @} */

/*! @name REG22 - DCDC Register 22 */
/*! @{ */

#define DCDC_REG22_DIG_STBY_TRG_SP2_MASK         (0xFFFFFFFFU)
#define DCDC_REG22_DIG_STBY_TRG_SP2_SHIFT        (0U)
#define DCDC_REG22_DIG_STBY_TRG_SP2(x)           (((uint32_t)(((uint32_t)(x)) << DCDC_REG22_DIG_STBY_TRG_SP2_SHIFT)) & DCDC_REG22_DIG_STBY_TRG_SP2_MASK)
/*! @} */

/*! @name REG23 - DCDC Register 23 */
/*! @{ */

#define DCDC_REG23_DIG_STBY_TRG_SP3_MASK         (0xFFFFFFFFU)
#define DCDC_REG23_DIG_STBY_TRG_SP3_SHIFT        (0U)
#define DCDC_REG23_DIG_STBY_TRG_SP3(x)           (((uint32_t)(((uint32_t)(x)) << DCDC_REG23_DIG_STBY_TRG_SP3_SHIFT)) & DCDC_REG23_DIG_STBY_TRG_SP3_MASK)
/*! @} */

/*! @name REG24 - DCDC Register 24 */
/*! @{ */

#define DCDC_REG24_OK_COUNT_MASK                 (0xFFFFFFFFU)
#define DCDC_REG24_OK_COUNT_SHIFT                (0U)
#define DCDC_REG24_OK_COUNT(x)                   (((uint32_t)(((uint32_t)(x)) << DCDC_REG24_OK_COUNT_SHIFT)) & DCDC_REG24_OK_COUNT_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group DCDC_Register_Masks */


/*!
 * @}
 */ /* end of group DCDC_Peripheral_Access_Layer */


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


#endif  /* PERI_DCDC_H_ */

