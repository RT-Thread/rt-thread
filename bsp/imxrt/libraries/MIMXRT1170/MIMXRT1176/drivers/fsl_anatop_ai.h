/*
 * Copyright 2019,2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _FSL_ANATOP_AI_H_
#define _FSL_ANATOP_AI_H_

#include "fsl_common.h"
/*! @addtogroup anatop_ai */
/*! @{ */

/*! @file */

/*! @name Driver version */
/*@{*/
/*! @brief Anatop AI driver version 1.0.0. */
#define FSL_ANATOP_AI_DRIVER_VERSION (MAKE_VERSION(1, 0, 0))
/*@}*/

/*!
 * @brief Anatop AI ITF enumeration.
 */
typedef enum _anatop_ai_itf
{
    kAI_Itf_Ldo     = 0, /*!< LDO ITF. */
    kAI_Itf_1g      = 1, /*!< 1G PLL ITF. */
    kAI_Itf_Audio   = 2, /*!< Audio PLL ITF. */
    kAI_Itf_Video   = 3, /*!< Video PLL ITF. */
    kAI_Itf_400m    = 4, /*!< 400M OSC ITF. */
    kAI_Itf_Temp    = 5, /*!< Temperature Sensor ITF. */
    kAI_Itf_Bandgap = 6, /*!< Bandgap ITF. */
} anatop_ai_itf_t;

/*!
 * @brief The enumeration of ANATOP AI Register.
 */
typedef enum _anatop_ai_reg
{
    kAI_PHY_LDO_CTRL0     = 0x0,  /*!< PHY LDO CTRL0 Register. */
    kAI_PHY_LDO_CTRL0_SET = 0x4,  /*!< PHY LDO CTRL0 Set Register. */
    kAI_PHY_LDO_CTRL0_CLR = 0x8,  /*!< PHY LDO CTRL0 Clr Register. */
    kAI_PHY_LDO_CTRL0_TOG = 0xC,  /*!< PHY LDO CTRL0 TOG Register. */
    kAI_PHY_LDO_STAT0     = 0x50, /*!< PHY LDO STAT0 Register. */
    kAI_PHY_LDO_STAT0_SET = 0x54, /*!< PHY LDO STAT0 Set Register. */
    kAI_PHY_LDO_STAT0_CLR = 0x58, /*!< PHY LDO STAT0 Clr Register. */
    kAI_PHY_LDO_STAT0_TOG = 0x5C, /*!< PHY LDO STAT0 Tog Register. */

    kAI_BANDGAP_CTRL0 = 0x0,  /*!< BANDGAP CTRL0 Register. */
    kAI_BANDGAP_STAT0 = 0x50, /*!< BANDGAP STAT0 Register. */

    kAI_RCOSC400M_CTRL0     = 0x0,  /*!< RC OSC 400M CTRL0 Register. */
    kAI_RCOSC400M_CTRL0_SET = 0x4,  /*!< RC OSC 400M CTRL0 SET Register. */
    kAI_RCOSC400M_CTRL0_CLR = 0x8,  /*!< RC OSC 400M CTRL0 CLR Register. */
    kAI_RCOSC400M_CTRL0_TOG = 0xC,  /*!< RC OSC 400M CTRL0 TOG Register. */
    kAI_RCOSC400M_CTRL1     = 0x10, /*!< RC OSC 400M CTRL1 Register. */
    kAI_RCOSC400M_CTRL1_SET = 0x14, /*!< RC OSC 400M CTRL1 SET Register. */
    kAI_RCOSC400M_CTRL1_CLR = 0x18, /*!< RC OSC 400M CTRL1 CLR Register. */
    kAI_RCOSC400M_CTRL1_TOG = 0x1C, /*!< RC OSC 400M CTRL1 TOG Register. */
    kAI_RCOSC400M_CTRL2     = 0x20, /*!< RC OSC 400M CTRL2 Register. */
    kAI_RCOSC400M_CTRL2_SET = 0x24, /*!< RC OSC 400M CTRL2 SET Register. */
    kAI_RCOSC400M_CTRL2_CLR = 0x28, /*!< RC OSC 400M CTRL2 CLR Register. */
    kAI_RCOSC400M_CTRL2_TOG = 0x2C, /*!< RC OSC 400M CTRL2 TOG Register. */
    kAI_RCOSC400M_CTRL3     = 0x30, /*!< RC OSC 400M CTRL3 Register. */
    kAI_RCOSC400M_CTRL3_SET = 0x34, /*!< RC OSC 400M CTRL3 SET Register. */
    kAI_RCOSC400M_CTRL3_CLR = 0x38, /*!< RC OSC 400M CTRL3 CLR Register. */
    kAI_RCOSC400M_CTRL3_TOG = 0x3C, /*!< RC OSC 400M CTRL3 TOG Register. */
    kAI_RCOSC400M_STAT0     = 0x50, /*!< RC OSC 400M STAT0 Register. */
    kAI_RCOSC400M_STAT0_SET = 0x54, /*!< RC OSC 400M STAT0 SET Register. */
    kAI_RCOSC400M_STAT0_CLR = 0x58, /*!< RC OSC 400M STAT0 CLR  Register. */
    kAI_RCOSC400M_STAT0_TOG = 0x5C, /*!< RC OSC 400M STAT0 TOG Register. */
    kAI_RCOSC400M_STAT1     = 0x60, /*!< RC OSC 400M STAT1 Register. */
    kAI_RCOSC400M_STAT1_SET = 0x64, /*!< RC OSC 400M STAT1 SET Register. */
    kAI_RCOSC400M_STAT1_CLR = 0x68, /*!< RC OSC 400M STAT1 CLR Register. */
    kAI_RCOSC400M_STAT1_TOG = 0x6C, /*!< RC OSC 400M STAT1 TOG Register. */
    kAI_RCOSC400M_STAT2     = 0x70, /*!< RC OSC 400M STAT2 Register. */
    kAI_RCOSC400M_STAT2_SET = 0x74, /*!< RC OSC 400M STAT2 SET Register. */
    kAI_RCOSC400M_STAT2_CLR = 0x78, /*!< RC OSC 400M STAT2 CLR Register. */
    kAI_RCOSC400M_STAT2_TOG = 0x7C, /*!< RC OSC 400M STAT2 TOG Register. */

    kAI_PLL1G_CTRL0     = 0x0,  /*!< 1G PLL CTRL0 Register. */
    kAI_PLL1G_CTRL0_SET = 0x4,  /*!< 1G PLL CTRL0 SET Register. */
    kAI_PLL1G_CTRL0_CLR = 0x8,  /*!< 1G PLL CTRL0 CLR Register. */
    kAI_PLL1G_CTRL1     = 0x10, /*!< 1G PLL CTRL1 Register. */
    kAI_PLL1G_CTRL1_SET = 0x14, /*!< 1G PLL CTRL1 SET Register. */
    kAI_PLL1G_CTRL1_CLR = 0x18, /*!< 1G PLL CTRL1 CLR Register. */
    kAI_PLL1G_CTRL2     = 0x20, /*!< 1G PLL CTRL2 Register. */
    kAI_PLL1G_CTRL2_SET = 0x24, /*!< 1G PLL CTRL2 SET Register. */
    kAI_PLL1G_CTRL2_CLR = 0x28, /*!< 1G PLL CTRL2 CLR Register. */
    kAI_PLL1G_CTRL3     = 0x30, /*!< 1G PLL CTRL3 Register. */
    kAI_PLL1G_CTRL3_SET = 0x34, /*!< 1G PLL CTRL3 SET Register. */
    kAI_PLL1G_CTRL3_CLR = 0x38, /*!< 1G PLL CTRL3 CLR Register. */

    kAI_PLLAUDIO_CTRL0     = 0x0,  /*!< AUDIO PLL CTRL0 Register. */
    kAI_PLLAUDIO_CTRL0_SET = 0x4,  /*!< AUDIO PLL CTRL0 SET Register. */
    kAI_PLLAUDIO_CTRL0_CLR = 0x8,  /*!< AUDIO PLL CTRL0 CLR Register. */
    kAI_PLLAUDIO_CTRL1     = 0x10, /*!< AUDIO PLL CTRL1 Register. */
    kAI_PLLAUDIO_CTRL1_SET = 0x14, /*!< AUDIO PLL CTRL1 SET Register. */
    kAI_PLLAUDIO_CTRL1_CLR = 0x18, /*!< AUDIO PLL CTRL1 CLR Register. */
    kAI_PLLAUDIO_CTRL2     = 0x20, /*!< AUDIO PLL CTRL2 Register. */
    kAI_PLLAUDIO_CTRL2_SET = 0x24, /*!< AUDIO PLL CTRL2 SET Register. */
    kAI_PLLAUDIO_CTRL2_CLR = 0x28, /*!< AUDIO PLL CTRL2 CLR Register. */
    kAI_PLLAUDIO_CTRL3     = 0x30, /*!< AUDIO PLL CTRL3 Register. */
    kAI_PLLAUDIO_CTRL3_SET = 0x34, /*!< AUDIO PLL CTRL3 SET Register. */
    kAI_PLLAUDIO_CTRL3_CLR = 0x38, /*!< AUDIO PLL CTRL3 CLR Register. */

    kAI_PLLVIDEO_CTRL0     = 0x0,  /*!< VIDEO PLL CTRL0 Register. */
    kAI_PLLVIDEO_CTRL0_SET = 0x4,  /*!< VIDEO PLL CTRL0 SET Register. */
    kAI_PLLVIDEO_CTRL0_CLR = 0x8,  /*!< VIDEO PLL CTRL0 CLR Register. */
    kAI_PLLVIDEO_CTRL1     = 0x10, /*!< VIDEO PLL CTRL1 Register. */
    kAI_PLLVIDEO_CTRL1_SET = 0x14, /*!< VIDEO PLL CTRL1 SET Register. */
    kAI_PLLVIDEO_CTRL1_CLR = 0x18, /*!< VIDEO PLL CTRL1 CLR Register. */
    kAI_PLLVIDEO_CTRL2     = 0x20, /*!< VIDEO PLL CTRL2 Register. */
    kAI_PLLVIDEO_CTRL2_SET = 0x24, /*!< VIDEO PLL CTRL2 SET Register. */
    kAI_PLLVIDEO_CTRL2_CLR = 0x28, /*!< VIDEO PLL CTRL2 CLR Register. */
    kAI_PLLVIDEO_CTRL3     = 0x30, /*!< VIDEO PLL CTRL3 Register. */
    kAI_PLLVIDEO_CTRL3_SET = 0x34, /*!< VIDEO PLL CTRL3 SET Register. */
    kAI_PLLVIDEO_CTRL3_CLR = 0x38, /*!< VIDEO PLL CTRL3 CLR Register. */
} anatop_ai_reg_t;

/* ----------------------------------------------------------------------------
   -- AI PHY_LDO CTRL0 Register Masks
   ---------------------------------------------------------------------------- */

/*! @name CTRL0 - CTRL0 Register */
/*! @{ */
#define AI_PHY_LDO_CTRL0_LINREG_EN(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_PHY_LDO_CTRL0_LINREG_EN_SHIFT)) & AI_PHY_LDO_CTRL0_LINREG_EN_MASK)
#define AI_PHY_LDO_CTRL0_LINREG_EN_MASK  (0x1U)
#define AI_PHY_LDO_CTRL0_LINREG_EN_SHIFT (0U)

/*! LINREG_EN - LinReg master enable
 *  LinReg master enable. Setting this bit will enable the regular
 */

#define AI_PHY_LDO_CTRL0_PWRUPLOAD_DIS(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_PHY_LDO_CTRL0_PWRUPLOAD_DIS_SHIFT)) & AI_PHY_LDO_CTRL0_PWRUPLOAD_DIS_MASK)
#define AI_PHY_LDO_CTRL0_PWRUPLOAD_DIS_MASK  (0x2U)
#define AI_PHY_LDO_CTRL0_PWRUPLOAD_DIS_SHIFT (1U)
/*! LINREG_PWRUPLOAD_DIS - LinReg power-up load disable
 *  0b0..Internal pull-down enabled
 *  0b1..Internal pull-down disabled
 */

#define AI_PHY_LDO_CTRL0_LIMIT_EN(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_PHY_LDO_CTRL0_LIMIT_EN_SHIFT)) & AI_PHY_LDO_CTRL0_LIMIT_EN_MASK)
#define AI_PHY_LDO_CTRL0_LIMIT_EN_MASK  (0x4U)
#define AI_PHY_LDO_CTRL0_LIMIT_EN_SHIFT (2U)
/*! LINREG_LIMIT_EN - LinReg current limit enable
 *  LinReg current-limit enable. Setting this bit will enable the
 *  current-limiter in the regulator
 */

#define AI_PHY_LDO_CTRL0_OUTPUT_TRG(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_PHY_LDO_CTRL0_OUTPUT_TRG_SHIFT)) & AI_PHY_LDO_CTRL0_OUTPUT_TRG_MASK)
#define AI_PHY_LDO_CTRL0_OUTPUT_TRG_MASK  (0x1F0U)
#define AI_PHY_LDO_CTRL0_OUTPUT_TRG_SHIFT (4U)
/*! LINREG_OUTPUT_TRG - LinReg output voltage target setting
 *  0b00000..Set output voltage to x.xV
 *  0b10000..Set output voltage to 1.0V
 *  0b11111..Set output voltage to x.xV
 */

#define AI_PHY_LDO_CTRL0_PHY_ISO_B(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_PHY_LDO_CTRL0_PHY_ISO_B_SHIFT)) & AI_PHY_LDO_CTRL0_PHY_ISO_B_MASK)
#define AI_PHY_LDO_CTRL0_PHY_ISO_B_MASK  (0x8000U)
#define AI_PHY_LDO_CTRL0_PHY_ISO_B_SHIFT (15U)
/*! LINREG_PHY_ISO_B - Isolation control for attached PHY load
 * This control bit is to be used by the system controller to isolate the
 * attached PHY load when the LinReg is powered down. During a power-up
 * event of the regulator it is expected that this control signal is set high
 * at least 100us after the main regulator is enabled. During a power-down
 * event of the regulator it is expected that this control signal is set low
 * before the main regulator is disabled/power-down.
 */
/*! @} */

/*! @name STAT0 - STAT0 Register */
/*! @{ */
#define AI_PHY_LDO_STAT0_LINREG_STAT(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_PHY_LDO_STAT0_LINREG_STAT_SHIFT)) & AI_PHY_LDO_STAT0_LINREG_STAT_MASK)
#define AI_PHY_LDO_STAT0_LINREG_STAT_MASK  (0xFU)
#define AI_PHY_LDO_STAT0_LINREG_STAT_SHIFT (0U)

/*! LINREG_STAT - LinReg status bits
 *  LinReg status bits.
 */

/*! @} */

/*! @name CTRL0 - CTRL0 Register */
/*! @{ */
#define AI_BANDGAP_CTRL0_REFTOP_PWD(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_BANDGAP_CTRL0_REFTOP_PWD_SHIFT)) & AI_BANDGAP_CTRL0_REFTOP_PWD_MASK)
#define AI_BANDGAP_CTRL0_REFTOP_PWD_MASK  (0x1U)
#define AI_BANDGAP_CTRL0_REFTOP_PWD_SHIFT (0U)
/*! REFTOP_PWD - This bit fully powers down the bandgap module.
 *  Setting this bit high will disable reference output currents and voltages from the
 *  bandgap and will affect functionality and validity of the voltage detectors.
 */

#define AI_BANDGAP_CTRL0_REFTOP_LINREGREF_PWD(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << AI_BANDGAP_CTRL0_REFTOP_LINREGREF_PWD_SHIFT)) & \
     AI_BANDGAP_CTRL0_REFTOP_LINREGREF_PWD_MASK)
#define AI_BANDGAP_CTRL0_REFTOP_LINREGREF_PWD_MASK  (0x2U)
#define AI_BANDGAP_CTRL0_REFTOP_LINREGREF_PWD_SHIFT (1U)
/*!
 * REFOP_LINREGREF_PWD - This bit powers down only the voltage reference output section of the bandgap.
 * Setting this bit high will affect functionality and validity
 * of the voltage detectors.
 */

#define AI_BANDGAP_CTRL0_REFTOP_PWDVBGUP(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_BANDGAP_CTRL0_REFTOP_PWDVBGUP_SHIFT)) & AI_BANDGAP_CTRL0_REFTOP_PWDVBGUP_MASK)
#define AI_BANDGAP_CTRL0_REFTOP_PWDVBGUP_MASK  (0x4U)
#define AI_BANDGAP_CTRL0_REFTOP_PWDVBGUP_SHIFT (2U)
/*!
 * REFTOP_PWDVBGUP - This bit powers down the VBGUP detector of the bandgap
 * without affecting any additional functionality.
 */

#define AI_BANDGAP_CTRL0_REFTOP_LOWPOWER(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_BANDGAP_CTRL0_REFTOP_LOWPOWER_SHIFT)) & AI_BANDGAP_CTRL0_REFTOP_LOWPOWER_MASK)
#define AI_BANDGAP_CTRL0_REFTOP_LOWPOWER_MASK  (0x8U)
#define AI_BANDGAP_CTRL0_REFTOP_LOWPOWER_SHIFT (3U)
/*!
 * REFTOP_LOWPOWER - This bit enables the low-power operation of the
 * bandgap by cutting the bias currents in half to the main amplifiers.
 * This will save power but could affect the accuracy of the output voltages and currents.
 */

#define AI_BANDGAP_CTRL0_REFTOP_SELFBIASOFF(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << AI_BANDGAP_CTRL0_REFTOP_SELFBIASOFF_SHIFT)) & \
     AI_BANDGAP_CTRL0_REFTOP_SELFBIASOFF_MASK)
#define AI_BANDGAP_CTRL0_REFTOP_SELFBIASOFF_MASK  (0x10U)
#define AI_BANDGAP_CTRL0_REFTOP_SELFBIASOFF_SHIFT (4U)
/*!
 * REFTOP_SELFBIASOFF - Control bit to disable the self-bias circuit in the bandgap.
 * The self-bias circuit is used by the bandgap during startup. This bit should be
 * set high after the bandgap has stabilized and is necessary for best noise performance
 * of modules using the outputs of the bandgap. It is expected that this control bit
 * be set low any time that either the bandgap is fully powered-down or the 1.8V supply is removed.
 */

#define AI_BANDGAP_CTRL0_REFTOP_VBGADJ(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_BANDGAP_CTRL0_REFTOP_VBGADJ_SHIFT)) & AI_BANDGAP_CTRL0_REFTOP_VBGADJ_MASK)
#define AI_BANDGAP_CTRL0_REFTOP_VBGADJ_MASK  (0xE0U)
#define AI_BANDGAP_CTRL0_REFTOP_VBGADJ_SHIFT (5U)
/*!
 * REFTOP_VBGADJ - These bits allow the output VBG voltage of the bandgap to be trimmed
 * 000 : nominal
 * 001 : +10mV
 * 010 : +20mV
 * 011 : +30mV
 * 100 : -10mV
 * 101 : -20mV
 * 110 : -30mV
 * 111 : -40mV
 */

#define AI_BANDGAP_CTRL0_REFTOP_IBZTCADJ(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_BANDGAP_CTRL0_REFTOP_IBZTCADJ_SHIFT)) & AI_BANDGAP_CTRL0_REFTOP_IBZTCADJ_MASK)
#define AI_BANDGAP_CTRL0_REFTOP_IBZTCADJ_MASK  (0x1C00U)
#define AI_BANDGAP_CTRL0_REFTOP_IBZTCADJ_SHIFT (10U)
/*!
 * REFTOP_IBZTCADJ - These bits allow trimming of the ZTC bias currents from the bandgap to
 * the temperature sensors. Assuming a typical process corner the expected values of output
 * currents are:
 * 000 : 11.5 uA
 * 001 : 11.8 uA
 * 010 : 12.1 uA
 * 100 : 12.4 uA (Nominal expected from MX8QM tempsensor)
 * 101 : 12.7 uA
 * 110 : 13.0 uA
 * 111 : 13.3 uA
 */

/*! @} */

/*! @name STAT0 - STAT0 Register */
/*! @{ */
#define AI_BANDGAP_STAT0_REFTOP_VBGUP(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_BANDGAP_STAT0_REFTOP_VBGUP_SHIFT)) & AI_BANDGAP_STAT0_REFTOP_VBGUP_MASK)
#define AI_BANDGAP_STAT0_REFTOP_VBGUP_MASK  (0x1U)
#define AI_BANDGAP_STAT0_REFTOP_VBGUP_SHIFT (0U)
/*! @} */

/*! @name CTRL0 - CTRL0 Register */
/*! @{ */
#define AI_RCOSC400M_CTRL0_REF_CLK_DIV(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_RCOSC400M_CTRL0_REF_CLK_DIV_SHIFT)) & AI_RCOSC400M_CTRL0_REF_CLK_DIV_MASK)
#define AI_RCOSC400M_CTRL0_REF_CLK_DIV_MASK  (0x3F000000U)
#define AI_RCOSC400M_CTRL0_REF_CLK_DIV_SHIFT (24U)
/*! @} */

/*! @name CTRL1 - CTRL1 Register */
/*! @{ */
#define AI_RCOSC400M_CTRL1_HYST_MINUS(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_RCOSC400M_CTRL1_HYST_MINUS_SHIFT)) & AI_RCOSC400M_CTRL1_HYST_MINUS_MASK)
#define AI_RCOSC400M_CTRL1_HYST_MINUS_MASK  (0xFU)
#define AI_RCOSC400M_CTRL1_HYST_MINUS_SHIFT (0U)

#define AI_RCOSC400M_CTRL1_HYST_PLUS(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_RCOSC400M_CTRL1_HYST_PLUS_SHIFT)) & AI_RCOSC400M_CTRL1_HYST_PLUS_MASK)
#define AI_RCOSC400M_CTRL1_HYST_PLUS_MASK  (0xF00U)
#define AI_RCOSC400M_CTRL1_HYST_PLUS_SHIFT (8U)

#define AI_RCOSC400M_CTRL1_TARGET_COUNT(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_RCOSC400M_CTRL1_TARGET_COUNT_SHIFT)) & AI_RCOSC400M_CTRL1_TARGET_COUNT_MASK)
#define AI_RCOSC400M_CTRL1_TARGET_COUNT_MASK  (0xFFFF0000U)
#define AI_RCOSC400M_CTRL1_TARGET_COUNT_SHIFT (16U)
/*! @} */

/*! @name CTRL2 - CTRL2 Register */
/*! @{ */
#define AI_RCOSC400M_CTRL2_TUNE_BYP(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_RCOSC400M_CTRL2_TUNE_BYP_SHIFT)) & AI_RCOSC400M_CTRL2_TUNE_BYP_MASK)
#define AI_RCOSC400M_CTRL2_TUNE_BYP_MASK  (0x400U)
#define AI_RCOSC400M_CTRL2_TUNE_BYP_SHIFT (10U)

#define AI_RCOSC400M_CTRL2_TUNE_EN(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_RCOSC400M_CTRL2_TUNE_EN_SHIFT)) & AI_RCOSC400M_CTRL2_TUNE_EN_MASK)
#define AI_RCOSC400M_CTRL2_TUNE_EN_MASK  (0x1000U)
#define AI_RCOSC400M_CTRL2_TUNE_EN_SHIFT (12U)

#define AI_RCOSC400M_CTRL2_TUNE_START(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_RCOSC400M_CTRL2_TUNE_START_SHIFT)) & AI_RCOSC400M_CTRL2_TUNE_START_MASK)
#define AI_RCOSC400M_CTRL2_TUNE_START_MASK  (0x4000U)
#define AI_RCOSC400M_CTRL2_TUNE_START_SHIFT (14U)

#define AI_RCOSC400M_CTRL2_OSC_TUNE_VAL(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_RCOSC400M_CTRL2_OSC_TUNE_VAL_SHIFT)) & AI_RCOSC400M_CTRL2_OSC_TUNE_VAL_MASK)
#define AI_RCOSC400M_CTRL2_OSC_TUNE_VAL_MASK  (0xFF000000U)
#define AI_RCOSC400M_CTRL2_OSC_TUNE_VAL_SHIFT (24U)
/*! @} */

/*! @name CTRL3 - CTRL3 Register */
/*! @{ */
#define AI_RCOSC400M_CTRL3_CLR_ERR(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_RCOSC400M_CTRL3_CLR_ERR_SHIFT)) & AI_RCOSC400M_CTRL3_CLR_ERR_MASK)
#define AI_RCOSC400M_CTRL3_CLR_ERR_MASK  (0x1U)
#define AI_RCOSC400M_CTRL3_CLR_ERR_SHIFT (0U)

#define AI_RCOSC400M_CTRL3_EN_1M_CLK(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_RCOSC400M_CTRL3_EN_1M_CLK_SHIFT)) & AI_RCOSC400M_CTRL3_EN_1M_CLK_MASK)
#define AI_RCOSC400M_CTRL3_EN_1M_CLK_MASK  (0x100U)
#define AI_RCOSC400M_CTRL3_EN_1M_CLK_SHIFT (8U)

#define AI_RCOSC400M_CTRL3_MUX_1M_CLK(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_RCOSC400M_CTRL3_MUX_1M_CLK_SHIFT)) & AI_RCOSC400M_CTRL3_MUX_1M_CLK_MASK)
#define AI_RCOSC400M_CTRL3_MUX_1M_CLK_MASK  (0x400U)
#define AI_RCOSC400M_CTRL3_MUX_1M_CLK_SHIFT (10U)

#define AI_RCOSC400M_CTRL3_COUNT_1M_CLK(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_RCOSC400M_CTRL3_COUNT_1M_CLK_SHIFT)) & AI_RCOSC400M_CTRL3_COUNT_1M_CLK_MASK)
#define AI_RCOSC400M_CTRL3_COUNT_1M_CLK_MASK  (0xFFFF0000U)
#define AI_RCOSC400M_CTRL3_COUNT_1M_CLK_SHIFT (16U)
/*! @} */

/*! @name STAT0 - STAT0 Register */
/*! @{ */
#define AI_RCOSC400M_STAT0_CLK1M_ERR(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_RCOSC400M_STAT0_CLK1M_ERR_SHIFT)) & AI_RCOSC400M_STAT0_CLK1M_ERR_MASK)
#define AI_RCOSC400M_STAT0_CLK1M_ERR_MASK  (0x1U)
#define AI_RCOSC400M_STAT0_CLK1M_ERR_SHIFT (0U)
/*! @} */

/*! @name STAT1 - STAT1 Register */
/*! @{ */
#define AI_RCOSC400M_STAT1_CURR_COUNT_VAL(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_RCOSC400M_STAT1_CURR_COUNT_VAL_SHIFT)) & AI_RCOSC400M_STAT1_CURR_COUNT_VAL_MASK)
#define AI_RCOSC400M_STAT1_CURR_COUNT_VAL_MASK  (0xFFFF0000U)
#define AI_RCOSC400M_STAT1_CURR_COUNT_VAL_SHIFT (16U)
/*! @} */

/*! @name STAT2 - STAT2 Register */
/*! @{ */
#define AI_RCOSC400M_STAT2_CURR_OSC_TUNE_VAL(x)                                    \
    (((uint32_t)(((uint32_t)(x)) << AI_RCOSC400M_STAT2_CURR_OSC_TUNE_VAL_SHIFT)) & \
     AI_RCOSC400M_STAT2_CURR_OSC_TUNE_VAL_MASK)
#define AI_RCOSC400M_STAT2_CURR_OSC_TUNE_VAL_MASK  (0xFF000000U)
#define AI_RCOSC400M_STAT2_CURR_OSC_TUNE_VAL_SHIFT (24U)
/*! @} */

/*! @name CTRL0 - CTRL0 Register */
/*! @{ */
#define AI_PLL1G_CTRL0_HOLD_RING_OFF(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_PLL1G_CTRL0_HOLD_RING_OFF_SHIFT)) & AI_PLL1G_CTRL0_HOLD_RING_OFF_MASK)
#define AI_PLL1G_CTRL0_HOLD_RING_OFF_MASK  (0x2000UL)
#define AI_PLL1G_CTRL0_HOLD_RING_OFF_SHIFT (13U)

#define AI_PLL1G_CTRL0_POWER_UP(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_PLL1G_CTRL0_POWER_UP_SHIFT)) & AI_PLL1G_CTRL0_POWER_UP_MASK)
#define AI_PLL1G_CTRL0_POWER_UP_MASK  (0x4000UL)
#define AI_PLL1G_CTRL0_POWER_UP_SHIFT (14U)

#define AI_PLL1G_CTRL0_ENABLE(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_PLL1G_CTRL0_ENABLE_SHIFT)) & AI_PLL1G_CTRL0_ENABLE_MASK)
#define AI_PLL1G_CTRL0_ENABLE_MASK  (0x8000UL)
#define AI_PLL1G_CTRL0_ENABLE_SHIFT (15U)

#define AI_PLL1G_CTRL0_BYPASS(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_PLL1G_CTRL0_BYPASS_SHIFT)) & AI_PLL1G_CTRL0_BYPASS_MASK)
#define AI_PLL1G_CTRL0_BYPASS_MASK  (0x10000UL)
#define AI_PLL1G_CTRL0_BYPASS_SHIFT (16U)

#define AI_PLL1G_CTRL0_PLL_REG_EN(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_PLL1G_CTRL0_PLL_REG_EN_SHIFT)) & AI_PLL1G_CTRL0_PLL_REG_EN_MASK)
#define AI_PLL1G_CTRL0_PLL_REG_EN_MASK  (0x400000UL)
#define AI_PLL1G_CTRL0_PLL_REG_EN_SHIFT (22U)
/*! @} */

/*! @name CTRL0 - CTRL0 Register */
/*! @{ */
#define AI_PLLAUDIO_CTRL0_HOLD_RING_OFF(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_PLLAUDIO_CTRL0_HOLD_RING_OFF_SHIFT)) & AI_PLLAUDIO_CTRL0_HOLD_RING_OFF_MASK)
#define AI_PLLAUDIO_CTRL0_HOLD_RING_OFF_MASK  (0x2000UL)
#define AI_PLLAUDIO_CTRL0_HOLD_RING_OFF_SHIFT (13U)

#define AI_PLLAUDIO_CTRL0_POWER_UP(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_PLLAUDIO_CTRL0_POWER_UP_SHIFT)) & AI_PLLAUDIO_CTRL0_POWER_UP_MASK)
#define AI_PLLAUDIO_CTRL0_POWER_UP_MASK  (0x4000UL)
#define AI_PLLAUDIO_CTRL0_POWER_UP_SHIFT (14U)

#define AI_PLLAUDIO_CTRL0_ENABLE(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_PLLAUDIO_CTRL0_ENABLE_SHIFT)) & AI_PLLAUDIO_CTRL0_ENABLE_MASK)
#define AI_PLLAUDIO_CTRL0_ENABLE_MASK  (0x8000UL)
#define AI_PLLAUDIO_CTRL0_ENABLE_SHIFT (15U)

#define AI_PLLAUDIO_CTRL0_BYPASS(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_PLLAUDIO_CTRL0_BYPASS_SHIFT)) & AI_PLLAUDIO_CTRL0_BYPASS_MASK)
#define AI_PLLAUDIO_CTRL0_BYPASS_MASK  (0x10000UL)
#define AI_PLLAUDIO_CTRL0_BYPASS_SHIFT (16U)

#define AI_PLLAUDIO_CTRL0_PLL_REG_EN(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_PLLAUDIO_CTRL0_PLL_REG_EN_SHIFT)) & AI_PLLAUDIO_CTRL0_PLL_REG_EN_MASK)
#define AI_PLLAUDIO_CTRL0_PLL_REG_EN_MASK  (0x400000UL)
#define AI_PLLAUDIO_CTRL0_PLL_REG_EN_SHIFT (22U)
/*! @} */

/*! @name CTRL0 - CTRL0 Register */
/*! @{ */
#define AI_PLLVIDEO_CTRL0_HOLD_RING_OFF(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_PLLVIDEO_CTRL0_HOLD_RING_OFF_SHIFT)) & AI_PLLVIDEO_CTRL0_HOLD_RING_OFF_MASK)
#define AI_PLLVIDEO_CTRL0_HOLD_RING_OFF_MASK  (0x2000UL)
#define AI_PLLVIDEO_CTRL0_HOLD_RING_OFF_SHIFT (13U)

#define AI_PLLVIDEO_CTRL0_POWER_UP(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_PLLVIDEO_CTRL0_POWER_UP_SHIFT)) & AI_PLLVIDEO_CTRL0_POWER_UP_MASK)
#define AI_PLLVIDEO_CTRL0_POWER_UP_MASK  (0x4000UL)
#define AI_PLLVIDEO_CTRL0_POWER_UP_SHIFT (14U)

#define AI_PLLVIDEO_CTRL0_ENABLE(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_PLLVIDEO_CTRL0_ENABLE_SHIFT)) & AI_PLLVIDEO_CTRL0_ENABLE_MASK)
#define AI_PLLVIDEO_CTRL0_ENABLE_MASK  (0x8000UL)
#define AI_PLLVIDEO_CTRL0_ENABLE_SHIFT (15U)

#define AI_PLLVIDEO_CTRL0_BYPASS(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_PLLVIDEO_CTRL0_BYPASS_SHIFT)) & AI_PLLVIDEO_CTRL0_BYPASS_MASK)
#define AI_PLLVIDEO_CTRL0_BYPASS_MASK  (0x10000UL)
#define AI_PLLVIDEO_CTRL0_BYPASS_SHIFT (16U)

#define AI_PLLVIDEO_CTRL0_PLL_REG_EN(x) \
    (((uint32_t)(((uint32_t)(x)) << AI_PLLVIDEO_CTRL0_PLL_REG_EN_SHIFT)) & AI_PLLVIDEO_CTRL0_PLL_REG_EN_MASK)
#define AI_PLLVIDEO_CTRL0_PLL_REG_EN_MASK  (0x400000UL)
#define AI_PLLVIDEO_CTRL0_PLL_REG_EN_SHIFT (22U)
/*! @} */

/*! @} */

/*******************************************************************************
 * API
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus */

/*!
 * @brief AI interface access
 *
 * @param itf AI interface name
 * @param isWrite write enable
 * @param addr address
 * @param wdata data to be set
 *
 */
uint32_t ANATOP_AI_Access(anatop_ai_itf_t itf, bool isWrite, anatop_ai_reg_t addr, uint32_t wdata);

/*!
 * @brief AI interface writing
 *
 * @param itf AI interface name
 * @param addr address
 * @param wdata data to be set
 *
 */
void ANATOP_AI_Write(anatop_ai_itf_t itf, anatop_ai_reg_t addr, uint32_t wdata);

/*!
 * @brief AI interface reading
 *
 * @param itf AI interface name
 * @param addr address
 * @return data read
 *
 */
uint32_t ANATOP_AI_Read(anatop_ai_itf_t itf, anatop_ai_reg_t addr);

/*!
 * @brief AI interface write with mask and shift
 *
 * @param itf AI interface name
 * @param addr address
 * @param wdata data to be written
 * @param mask bit field mask
 * @param shift bit field shift
 *
 */
void ANATOP_AI_WriteWithMaskShift(
    anatop_ai_itf_t itf, anatop_ai_reg_t addr, uint32_t wdata, uint32_t mask, uint32_t shift);

/* @} */

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/*! @} */

#endif /* _FSL_ANATOP_AI_H_ */
