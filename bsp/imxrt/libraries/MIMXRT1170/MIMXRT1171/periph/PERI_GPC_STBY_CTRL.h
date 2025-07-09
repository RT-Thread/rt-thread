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
**         CMSIS Peripheral Access Layer for GPC_STBY_CTRL
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
 * @file PERI_GPC_STBY_CTRL.h
 * @version 2.0
 * @date 2024-10-29
 * @brief CMSIS Peripheral Access Layer for GPC_STBY_CTRL
 *
 * CMSIS Peripheral Access Layer for GPC_STBY_CTRL
 */

#if !defined(PERI_GPC_STBY_CTRL_H_)
#define PERI_GPC_STBY_CTRL_H_                    /**< Symbol preventing repeated inclusion */

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
   -- GPC_STBY_CTRL Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPC_STBY_CTRL_Peripheral_Access_Layer GPC_STBY_CTRL Peripheral Access Layer
 * @{
 */

/** GPC_STBY_CTRL - Register Layout Typedef */
typedef struct {
       uint8_t RESERVED_0[4];
  __IO uint32_t STBY_AUTHEN_CTRL;                  /**< Standby Authentication Control, offset: 0x4 */
       uint8_t RESERVED_1[4];
  __IO uint32_t STBY_MISC;                         /**< STBY Misc, offset: 0xC */
       uint8_t RESERVED_2[224];
  __IO uint32_t STBY_LPCG_IN_CTRL;                 /**< STBY lpcg_in control, offset: 0xF0 */
       uint8_t RESERVED_3[12];
  __IO uint32_t STBY_PLL_IN_CTRL;                  /**< STBY pll_in control, offset: 0x100 */
       uint8_t RESERVED_4[12];
  __IO uint32_t STBY_BIAS_IN_CTRL;                 /**< STBY bias_in control, offset: 0x110 */
       uint8_t RESERVED_5[12];
  __IO uint32_t STBY_PLDO_IN_CTRL;                 /**< STBY pldo_in control, offset: 0x120 */
       uint8_t RESERVED_6[4];
  __IO uint32_t STBY_BANDGAP_IN_CTRL;              /**< STBY bandgap_in control, offset: 0x128 */
       uint8_t RESERVED_7[4];
  __IO uint32_t STBY_LDO_IN_CTRL;                  /**< STBY ldo_in control, offset: 0x130 */
       uint8_t RESERVED_8[12];
  __IO uint32_t STBY_DCDC_IN_CTRL;                 /**< STBY dcdc_in control, offset: 0x140 */
       uint8_t RESERVED_9[12];
  __IO uint32_t STBY_PMIC_IN_CTRL;                 /**< STBY PMIC in control, offset: 0x150 */
       uint8_t RESERVED_10[172];
  __IO uint32_t STBY_PMIC_OUT_CTRL;                /**< STBY PMIC out control, offset: 0x200 */
       uint8_t RESERVED_11[12];
  __IO uint32_t STBY_DCDC_OUT_CTRL;                /**< STBY DCDC out control, offset: 0x210 */
       uint8_t RESERVED_12[12];
  __IO uint32_t STBY_LDO_OUT_CTRL;                 /**< STBY LDO out control, offset: 0x220 */
       uint8_t RESERVED_13[12];
  __IO uint32_t STBY_BANDGAP_OUT_CTRL;             /**< STBY bandgap out control, offset: 0x230 */
       uint8_t RESERVED_14[4];
  __IO uint32_t STBY_PLDO_OUT_CTRL;                /**< STBY pldo out control, offset: 0x238 */
       uint8_t RESERVED_15[4];
  __IO uint32_t STBY_BIAS_OUT_CTRL;                /**< STBY bias out control, offset: 0x240 */
       uint8_t RESERVED_16[12];
  __IO uint32_t STBY_PLL_OUT_CTRL;                 /**< STBY PLL out control, offset: 0x250 */
       uint8_t RESERVED_17[12];
  __IO uint32_t STBY_LPCG_OUT_CTRL;                /**< STBY LPCG out control, offset: 0x260 */
} GPC_STBY_CTRL_Type;

/* ----------------------------------------------------------------------------
   -- GPC_STBY_CTRL Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup GPC_STBY_CTRL_Register_Masks GPC_STBY_CTRL Register Masks
 * @{
 */

/*! @name STBY_AUTHEN_CTRL - Standby Authentication Control */
/*! @{ */

#define GPC_STBY_CTRL_STBY_AUTHEN_CTRL_LOCK_CFG_MASK (0x100000U)
#define GPC_STBY_CTRL_STBY_AUTHEN_CTRL_LOCK_CFG_SHIFT (20U)
/*! LOCK_CFG - Configuration lock */
#define GPC_STBY_CTRL_STBY_AUTHEN_CTRL_LOCK_CFG(x) (((uint32_t)(((uint32_t)(x)) << GPC_STBY_CTRL_STBY_AUTHEN_CTRL_LOCK_CFG_SHIFT)) & GPC_STBY_CTRL_STBY_AUTHEN_CTRL_LOCK_CFG_MASK)
/*! @} */

/*! @name STBY_MISC - STBY Misc */
/*! @{ */

#define GPC_STBY_CTRL_STBY_MISC_FORCE_CPU0_STBY_MASK (0x1U)
#define GPC_STBY_CTRL_STBY_MISC_FORCE_CPU0_STBY_SHIFT (0U)
/*! FORCE_CPU0_STBY - Force CPU0 requesting standby mode */
#define GPC_STBY_CTRL_STBY_MISC_FORCE_CPU0_STBY(x) (((uint32_t)(((uint32_t)(x)) << GPC_STBY_CTRL_STBY_MISC_FORCE_CPU0_STBY_SHIFT)) & GPC_STBY_CTRL_STBY_MISC_FORCE_CPU0_STBY_MASK)

#define GPC_STBY_CTRL_STBY_MISC_FORCE_CPU1_STBY_MASK (0x2U)
#define GPC_STBY_CTRL_STBY_MISC_FORCE_CPU1_STBY_SHIFT (1U)
/*! FORCE_CPU1_STBY - Force CPU0 requesting standby mode */
#define GPC_STBY_CTRL_STBY_MISC_FORCE_CPU1_STBY(x) (((uint32_t)(((uint32_t)(x)) << GPC_STBY_CTRL_STBY_MISC_FORCE_CPU1_STBY_SHIFT)) & GPC_STBY_CTRL_STBY_MISC_FORCE_CPU1_STBY_MASK)

#define GPC_STBY_CTRL_STBY_MISC_FORCE_CPU2_STBY_MASK (0x4U)
#define GPC_STBY_CTRL_STBY_MISC_FORCE_CPU2_STBY_SHIFT (2U)
/*! FORCE_CPU2_STBY - Force CPU2 requesting standby mode */
#define GPC_STBY_CTRL_STBY_MISC_FORCE_CPU2_STBY(x) (((uint32_t)(((uint32_t)(x)) << GPC_STBY_CTRL_STBY_MISC_FORCE_CPU2_STBY_SHIFT)) & GPC_STBY_CTRL_STBY_MISC_FORCE_CPU2_STBY_MASK)

#define GPC_STBY_CTRL_STBY_MISC_FORCE_CPU3_STBY_MASK (0x8U)
#define GPC_STBY_CTRL_STBY_MISC_FORCE_CPU3_STBY_SHIFT (3U)
/*! FORCE_CPU3_STBY - Force CPU3 requesting standby mode */
#define GPC_STBY_CTRL_STBY_MISC_FORCE_CPU3_STBY(x) (((uint32_t)(((uint32_t)(x)) << GPC_STBY_CTRL_STBY_MISC_FORCE_CPU3_STBY_SHIFT)) & GPC_STBY_CTRL_STBY_MISC_FORCE_CPU3_STBY_MASK)
/*! @} */

/*! @name STBY_LPCG_IN_CTRL - STBY lpcg_in control */
/*! @{ */

#define GPC_STBY_CTRL_STBY_LPCG_IN_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_STBY_CTRL_STBY_LPCG_IN_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_STBY_CTRL_STBY_LPCG_IN_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_STBY_CTRL_STBY_LPCG_IN_CTRL_DISABLE_SHIFT)) & GPC_STBY_CTRL_STBY_LPCG_IN_CTRL_DISABLE_MASK)
/*! @} */

/*! @name STBY_PLL_IN_CTRL - STBY pll_in control */
/*! @{ */

#define GPC_STBY_CTRL_STBY_PLL_IN_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_STBY_CTRL_STBY_PLL_IN_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_STBY_CTRL_STBY_PLL_IN_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_STBY_CTRL_STBY_PLL_IN_CTRL_DISABLE_SHIFT)) & GPC_STBY_CTRL_STBY_PLL_IN_CTRL_DISABLE_MASK)
/*! @} */

/*! @name STBY_BIAS_IN_CTRL - STBY bias_in control */
/*! @{ */

#define GPC_STBY_CTRL_STBY_BIAS_IN_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_STBY_CTRL_STBY_BIAS_IN_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_STBY_CTRL_STBY_BIAS_IN_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_STBY_CTRL_STBY_BIAS_IN_CTRL_DISABLE_SHIFT)) & GPC_STBY_CTRL_STBY_BIAS_IN_CTRL_DISABLE_MASK)
/*! @} */

/*! @name STBY_PLDO_IN_CTRL - STBY pldo_in control */
/*! @{ */

#define GPC_STBY_CTRL_STBY_PLDO_IN_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_STBY_CTRL_STBY_PLDO_IN_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_STBY_CTRL_STBY_PLDO_IN_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_STBY_CTRL_STBY_PLDO_IN_CTRL_DISABLE_SHIFT)) & GPC_STBY_CTRL_STBY_PLDO_IN_CTRL_DISABLE_MASK)
/*! @} */

/*! @name STBY_BANDGAP_IN_CTRL - STBY bandgap_in control */
/*! @{ */

#define GPC_STBY_CTRL_STBY_BANDGAP_IN_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_STBY_CTRL_STBY_BANDGAP_IN_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_STBY_CTRL_STBY_BANDGAP_IN_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_STBY_CTRL_STBY_BANDGAP_IN_CTRL_DISABLE_SHIFT)) & GPC_STBY_CTRL_STBY_BANDGAP_IN_CTRL_DISABLE_MASK)
/*! @} */

/*! @name STBY_LDO_IN_CTRL - STBY ldo_in control */
/*! @{ */

#define GPC_STBY_CTRL_STBY_LDO_IN_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_STBY_CTRL_STBY_LDO_IN_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_STBY_CTRL_STBY_LDO_IN_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_STBY_CTRL_STBY_LDO_IN_CTRL_DISABLE_SHIFT)) & GPC_STBY_CTRL_STBY_LDO_IN_CTRL_DISABLE_MASK)
/*! @} */

/*! @name STBY_DCDC_IN_CTRL - STBY dcdc_in control */
/*! @{ */

#define GPC_STBY_CTRL_STBY_DCDC_IN_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_STBY_CTRL_STBY_DCDC_IN_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_STBY_CTRL_STBY_DCDC_IN_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_STBY_CTRL_STBY_DCDC_IN_CTRL_DISABLE_SHIFT)) & GPC_STBY_CTRL_STBY_DCDC_IN_CTRL_DISABLE_MASK)
/*! @} */

/*! @name STBY_PMIC_IN_CTRL - STBY PMIC in control */
/*! @{ */

#define GPC_STBY_CTRL_STBY_PMIC_IN_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_STBY_CTRL_STBY_PMIC_IN_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_STBY_CTRL_STBY_PMIC_IN_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_STBY_CTRL_STBY_PMIC_IN_CTRL_DISABLE_SHIFT)) & GPC_STBY_CTRL_STBY_PMIC_IN_CTRL_DISABLE_MASK)
/*! @} */

/*! @name STBY_PMIC_OUT_CTRL - STBY PMIC out control */
/*! @{ */

#define GPC_STBY_CTRL_STBY_PMIC_OUT_CTRL_STEP_CNT_MASK (0xFFFFU)
#define GPC_STBY_CTRL_STBY_PMIC_OUT_CTRL_STEP_CNT_SHIFT (0U)
/*! STEP_CNT - Step count, useage is depending on CNT_MODE */
#define GPC_STBY_CTRL_STBY_PMIC_OUT_CTRL_STEP_CNT(x) (((uint32_t)(((uint32_t)(x)) << GPC_STBY_CTRL_STBY_PMIC_OUT_CTRL_STEP_CNT_SHIFT)) & GPC_STBY_CTRL_STBY_PMIC_OUT_CTRL_STEP_CNT_MASK)

#define GPC_STBY_CTRL_STBY_PMIC_OUT_CTRL_CNT_MODE_MASK (0x30000000U)
#define GPC_STBY_CTRL_STBY_PMIC_OUT_CTRL_CNT_MODE_SHIFT (28U)
/*! CNT_MODE - Count mode
 *  0b00..Counter disable mode: not use step counter, step completes once receiving step_done
 *  0b01..Counter delay mode: delay after receiving step_done, delay cycle number is STEP_CNT
 *  0b10..Ignore step_done response, the counter starts to count once step begins, when counter reaches STEP_CNT value, the step completes
 *  0b11..Time out mode, the counter starts to count once step begins, the step completes when either step_done received or counting to STEP_CNT value
 */
#define GPC_STBY_CTRL_STBY_PMIC_OUT_CTRL_CNT_MODE(x) (((uint32_t)(((uint32_t)(x)) << GPC_STBY_CTRL_STBY_PMIC_OUT_CTRL_CNT_MODE_SHIFT)) & GPC_STBY_CTRL_STBY_PMIC_OUT_CTRL_CNT_MODE_MASK)

#define GPC_STBY_CTRL_STBY_PMIC_OUT_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_STBY_CTRL_STBY_PMIC_OUT_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_STBY_CTRL_STBY_PMIC_OUT_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_STBY_CTRL_STBY_PMIC_OUT_CTRL_DISABLE_SHIFT)) & GPC_STBY_CTRL_STBY_PMIC_OUT_CTRL_DISABLE_MASK)
/*! @} */

/*! @name STBY_DCDC_OUT_CTRL - STBY DCDC out control */
/*! @{ */

#define GPC_STBY_CTRL_STBY_DCDC_OUT_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_STBY_CTRL_STBY_DCDC_OUT_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_STBY_CTRL_STBY_DCDC_OUT_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_STBY_CTRL_STBY_DCDC_OUT_CTRL_DISABLE_SHIFT)) & GPC_STBY_CTRL_STBY_DCDC_OUT_CTRL_DISABLE_MASK)
/*! @} */

/*! @name STBY_LDO_OUT_CTRL - STBY LDO out control */
/*! @{ */

#define GPC_STBY_CTRL_STBY_LDO_OUT_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_STBY_CTRL_STBY_LDO_OUT_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_STBY_CTRL_STBY_LDO_OUT_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_STBY_CTRL_STBY_LDO_OUT_CTRL_DISABLE_SHIFT)) & GPC_STBY_CTRL_STBY_LDO_OUT_CTRL_DISABLE_MASK)
/*! @} */

/*! @name STBY_BANDGAP_OUT_CTRL - STBY bandgap out control */
/*! @{ */

#define GPC_STBY_CTRL_STBY_BANDGAP_OUT_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_STBY_CTRL_STBY_BANDGAP_OUT_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_STBY_CTRL_STBY_BANDGAP_OUT_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_STBY_CTRL_STBY_BANDGAP_OUT_CTRL_DISABLE_SHIFT)) & GPC_STBY_CTRL_STBY_BANDGAP_OUT_CTRL_DISABLE_MASK)
/*! @} */

/*! @name STBY_PLDO_OUT_CTRL - STBY pldo out control */
/*! @{ */

#define GPC_STBY_CTRL_STBY_PLDO_OUT_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_STBY_CTRL_STBY_PLDO_OUT_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_STBY_CTRL_STBY_PLDO_OUT_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_STBY_CTRL_STBY_PLDO_OUT_CTRL_DISABLE_SHIFT)) & GPC_STBY_CTRL_STBY_PLDO_OUT_CTRL_DISABLE_MASK)
/*! @} */

/*! @name STBY_BIAS_OUT_CTRL - STBY bias out control */
/*! @{ */

#define GPC_STBY_CTRL_STBY_BIAS_OUT_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_STBY_CTRL_STBY_BIAS_OUT_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_STBY_CTRL_STBY_BIAS_OUT_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_STBY_CTRL_STBY_BIAS_OUT_CTRL_DISABLE_SHIFT)) & GPC_STBY_CTRL_STBY_BIAS_OUT_CTRL_DISABLE_MASK)
/*! @} */

/*! @name STBY_PLL_OUT_CTRL - STBY PLL out control */
/*! @{ */

#define GPC_STBY_CTRL_STBY_PLL_OUT_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_STBY_CTRL_STBY_PLL_OUT_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_STBY_CTRL_STBY_PLL_OUT_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_STBY_CTRL_STBY_PLL_OUT_CTRL_DISABLE_SHIFT)) & GPC_STBY_CTRL_STBY_PLL_OUT_CTRL_DISABLE_MASK)
/*! @} */

/*! @name STBY_LPCG_OUT_CTRL - STBY LPCG out control */
/*! @{ */

#define GPC_STBY_CTRL_STBY_LPCG_OUT_CTRL_DISABLE_MASK (0x80000000U)
#define GPC_STBY_CTRL_STBY_LPCG_OUT_CTRL_DISABLE_SHIFT (31U)
/*! DISABLE - Disable this step */
#define GPC_STBY_CTRL_STBY_LPCG_OUT_CTRL_DISABLE(x) (((uint32_t)(((uint32_t)(x)) << GPC_STBY_CTRL_STBY_LPCG_OUT_CTRL_DISABLE_SHIFT)) & GPC_STBY_CTRL_STBY_LPCG_OUT_CTRL_DISABLE_MASK)
/*! @} */


/*!
 * @}
 */ /* end of group GPC_STBY_CTRL_Register_Masks */


/*!
 * @}
 */ /* end of group GPC_STBY_CTRL_Peripheral_Access_Layer */


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


#endif  /* PERI_GPC_STBY_CTRL_H_ */

