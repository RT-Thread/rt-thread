/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2019 NXP
 * Copyright (c) 2021 HPMicro
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *
 */

#ifndef _HPM_SGTL5000_H_
#define _HPM_SGTL5000_H_

#include "hpm_i2c_drv.h"

/*!
 * @addtogroup sgtl5000
 * @ingroup codec
 * @{
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Define the register address of sgtl5000. */
#define CHIP_ID                            0x0000U
#define CHIP_DIG_POWER                     0x0002U
#define CHIP_CLK_CTRL                      0x0004U
#define CHIP_I2S_CTRL                      0x0006U
#define CHIP_SSS_CTRL                      0x000AU
#define CHIP_ADCDAC_CTRL                   0x000EU
#define CHIP_DAC_VOL                       0x0010U
#define CHIP_PAD_STRENGTH                  0x0014U
#define CHIP_ANA_ADC_CTRL                  0x0020U
#define CHIP_ANA_HP_CTRL                   0x0022U
#define CHIP_ANA_CTRL                      0x0024U
#define CHIP_LINREG_CTRL                   0x0026U
#define CHIP_REF_CTRL                      0x0028U
#define CHIP_MIC_CTRL                      0x002AU
#define CHIP_LINE_OUT_CTRL                 0x002CU
#define CHIP_LINE_OUT_VOL                  0x002EU
#define CHIP_ANA_POWER                     0x0030U
#define CHIP_PLL_CTRL                      0x0032U
#define CHIP_CLK_TOP_CTRL                  0x0034U
#define CHIP_ANA_STATUS                    0x0036U
#define CHIP_ANA_TEST2                     0x003AU
#define CHIP_SHORT_CTRL                    0x003CU
#define SGTL5000_DAP_CONTROL               0x0100U
#define SGTL5000_DAP_PEQ                   0x0102U
#define SGTL5000_DAP_BASS_ENHANCE          0x0104U
#define SGTL5000_DAP_BASS_ENHANCE_CTRL     0x0106U
#define SGTL5000_DAP_AUDIO_EQ              0x0108U
#define SGTL5000_DAP_SGTL_SURROUND         0x010AU
#define SGTL5000_DAP_FILTER_COEF_ACCESS    0x010CU
#define SGTL5000_DAP_COEF_WR_B0_MSB        0x010EU
#define SGTL5000_DAP_COEF_WR_B0_LSB        0x0110U
#define SGTL5000_DAP_AUDIO_EQ_BASS_BAND0   0x0116U
#define SGTL5000_DAP_AUDIO_EQ_BAND1        0x0118U
#define SGTL5000_DAP_AUDIO_EQ_BAND2        0x011AU
#define SGTL5000_DAP_AUDIO_EQ_BAND3        0x011CU
#define SGTL5000_DAP_AUDIO_EQ_TREBLE_BAND4 0x011EU
#define SGTL5000_DAP_MAIN_CHAN             0x0120U
#define SGTL5000_DAP_MIX_CHAN              0x0122U
#define SGTL5000_DAP_AVC_CTRL              0x0124U
#define SGTL5000_DAP_AVC_THRESHOLD         0x0126U
#define SGTL5000_DAP_AVC_ATTACK            0x0128U
#define SGTL5000_DAP_AVC_DECAY             0x012AU
#define SGTL5000_DAP_COEF_WR_B1_MSB        0x012CU
#define SGTL5000_DAP_COEF_WR_B1_LSB        0x012EU
#define SGTL5000_DAP_COEF_WR_B2_MSB        0x0130U
#define SGTL5000_DAP_COEF_WR_B2_LSB        0x0132U
#define SGTL5000_DAP_COEF_WR_A1_MSB        0x0134U
#define SGTL5000_DAP_COEF_WR_A1_LSB        0x0136U
#define SGTL5000_DAP_COEF_WR_A2_MSB        0x0138U
#define SGTL5000_DAP_COEF_WR_A2_LSB        0x013AU

/*
 * Field Definitions.
 */

/*
 * SGTL5000_CHIP_DIG_POWER
 */
#define SGTL5000_ADC_ENABLE_CLR_MASK     0xFFBFU
#define SGTL5000_ADC_ENABLE_GET_MASK     0x0040U
#define SGTL5000_ADC_ENABLE_SHIFT        0x6U
#define SGTL5000_DAC_ENABLE_CLR_MASK     0xFFDFU
#define SGTL5000_DAC_ENABLE_GET_MASK     0x0020U
#define SGTL5000_DAC_ENABLE_SHIFT        0x5U
#define SGTL5000_DAP_ENABLE_CLR_MASK     0xFFEFU
#define SGTL5000_DAP_ENABLE_GET_MASK     0x0010U
#define SGTL5000_DAP_ENABLE_SHIFT        0x4U
#define SGTL5000_I2S_OUT_ENABLE_CLR_MASK 0xFFFDU
#define SGTL5000_I2S_OUT_ENABLE_GET_MASK 0x0002U
#define SGTL5000_I2S_OUT_ENABLE_SHIFT    0x1U
#define SGTL5000_I2S_IN_ENABLE_CLR_MASK  0xFFFEU
#define SGTL5000_I2S_IN_ENABLE_GET_MASK  0x0001U
#define SGTL5000_I2S_IN_ENABLE_SHIFT     0x0U

/*
 * SGTL5000_CHIP_CLK_CTRL
 */
#define SGTL5000_RATE_MODE_CLR_MASK 0xFFCFU
#define SGTL5000_RATE_MODE_GET_MASK 0x0030U
#define SGTL5000_RATE_MODE_SHIFT    0x4U
#define SGTL5000_RATE_MODE_DIV_1    0x0000U
#define SGTL5000_RATE_MODE_DIV_2    0x0010U
#define SGTL5000_RATE_MODE_DIV_4    0x0020U
#define SGTL5000_RATE_MODE_DIV_6    0x0030U
#define SGTL5000_SYS_FS_CLR_MASK    0xFFF3U
#define SGTL5000_SYS_FS_GET_MASK    0x000CU
#define SGTL5000_SYS_FS_SHIFT       0x2U
#define SGTL5000_SYS_FS_32k         0x0000U
#define SGTL5000_SYS_FS_44_1k       0x0004U
#define SGTL5000_SYS_FS_48k         0x0008U
#define SGTL5000_SYS_FS_96k         0x000CU
#define SGTL5000_MCLK_FREQ_CLR_MASK 0xFFFCU
#define SGTL5000_MCLK_FREQ_GET_MASK 0x0003U
#define SGTL5000_MCLK_FREQ_SHIFT    0x0U
#define SGTL5000_MCLK_FREQ_256FS    0x0000U
#define SGTL5000_MCLK_FREQ_384FS    0x0001U
#define SGTL5000_MCLK_FREQ_512FS    0x0002U
#define SGTL5000_MCLK_FREQ_PLL      0x0003U

/*
 * SGTL5000_CHIP_I2S_CTRL
 */
#define SGTL5000_I2S_SLCKFREQ_CLR_MASK  0xFEFFU
#define SGTL5000_I2S_SCLKFREQ_GET_MASK  0x0100U
#define SGTL5000_I2S_SCLKFREQ_SHIFT     0x8U
#define SGTL5000_I2S_SCLKFREQ_64FS      0x0000U
#define SGTL5000_I2S_SCLKFREQ_32FS      0x0100U /* Not for RJ mode */
#define SGTL5000_I2S_MS_CLR_MASK        0xFF7FU
#define SGTL5000_I2S_MS_GET_MASK        0x0080U
#define SGTL5000_I2S_MS_SHIFT           0x7U
#define SGTL5000_I2S_MASTER             0x0080U
#define SGTL5000_I2S_SLAVE              0x0000U
#define SGTL5000_I2S_SCLK_INV_CLR_MASK  0xFFBFU
#define SGTL5000_I2S_SCLK_INV_GET_MASK  0x0040U
#define SGTL5000_I2S_SCLK_INV_SHIFT     0x6U
#define SGTL5000_I2S_VAILD_FALLING_EDGE 0x0040U
#define SGTL5000_I2S_VAILD_RISING_EDGE  0x0000U
#define SGTL5000_I2S_DLEN_CLR_MASK      0xFFCFU
#define SGTL5000_I2S_DLEN_GET_MASK      0x0030U
#define SGTL5000_I2S_DLEN_SHIFT         0x4U
#define SGTL5000_I2S_DLEN_32            0x0000U
#define SGTL5000_I2S_DLEN_24            0x0010U
#define SGTL5000_I2S_DLEN_20            0x0020U
#define SGTL5000_I2S_DLEN_16            0x0030U
#define SGTL5000_I2S_MODE_CLR_MASK      0xFFF3U
#define SGTL5000_I2S_MODE_GET_MASK      0x000CU
#define SGTL5000_I2S_MODE_SHIFT         0x2U
#define SGTL5000_I2S_MODE_I2S_LJ        0x0000U
#define SGTL5000_I2S_MODE_RJ            0x0004U
#define SGTL5000_I2S_MODE_PCM           0x0008U
#define SGTL5000_I2S_LRALIGN_CLR_MASK   0xFFFDU
#define SGTL5000_I2S_LRALIGN_GET_MASK   0x0002U
#define SGTL5000_I2S_LRALIGN_SHIFT      0x1U
#define SGTL5000_I2S_ONE_BIT_DELAY      0x0000U
#define SGTL5000_I2S_NO_DELAY           0x0002U
#define SGTL5000_I2S_LRPOL_CLR_MASK     0xFFFEU
#define SGTL5000_I2S_LRPOL_GET_MASK     0x0001U
#define SGTL5000_I2S_LRPOL_SHIFT        0x0U
#define SGTL5000_I2S_LEFT_FIRST         0x0000U
#define SGTL5000_I2S_RIGHT_FIRST        0x0001U

/*
 * SGTL5000_CHIP_SSS_CTRL
 */
#define SGTL5000_DAP_MIX_LRSWAP_CLR_MASK 0xBFFFU
#define SGTL5000_DAP_MIX_LRSWAP_GET_MASK 0x4000U
#define SGTL5000_DAP_MIX_LRSWAP_SHIFT    0xEU
#define SGTL5000_DAP_LRSWAP_CLR_MASK     0xDFFFU
#define SGTL5000_DAP_LRSWAP_GET_MASK     0x2000U
#define SGTL5000_DAP_LRSWAP_SHIFT        0xDU
#define SGTL5000_DAC_LRSWAP_CLR_MASK     0xEFFFU
#define SGTL5000_DAC_LRSWAP_GET_MASK     0x1000U
#define SGTL5000_DAC_LRSWAP_SHIFT        0xCU
#define SGTL5000_I2S_LRSWAP_CLR_MASK     0xFBFFU
#define SGTL5000_I2S_LRSWAP_GET_MASK     0x0400U
#define SGTL5000_I2S_LRSWAP_SHIFT        0xAU
#define SGTL5000_DAP_MIX_SEL_CLR_MASK    0xFCFFU
#define SGTL5000_DAP_MIX_SEL_GET_MASK    0x0300U
#define SGTL5000_DAP_MIX_SEL_SHIFT       0x8U
#define SGTL5000_DAP_MIX_SEL_ADC         0x0000U
#define SGTL5000_DAP_MIX_SEL_I2S_IN      0x0100U
#define SGTL5000_DAP_SEL_CLR_MASK        0xFF3FU
#define SGTL5000_DAP_SEL_GET_MASK        0x00C0U
#define SGTL5000_DAP_SEL_SHIFT           0x6U
#define SGTL5000_DAP_SEL_ADC             0x0000U
#define SGTL5000_DAP_SEL_I2S_IN          0x0040U
#define SGTL5000_DAC_SEL_CLR_MASK        0xFFCFU
#define SGTL5000_DAC_SEL_GET_MASK        0x0030U
#define SGTL5000_DAC_SEL_SHIFT           0x4U
#define SGTL5000_DAC_SEL_ADC             0x0000U
#define SGTL5000_DAC_SEL_I2S_IN          0x0010U
#define SGTL5000_DAC_SEL_DAP             0x0030U
#define SGTL5000_I2S_OUT_SEL_CLR_MASK    0xFFFCU
#define SGTL5000_I2S_OUT_SEL_GET_MASK    0x0003U
#define SGTL5000_I2S_OUT_SEL_SHIFT       0x0U
#define SGTL5000_I2S_OUT_SEL_ADC         0x0000U
#define SGTL5000_I2S_OUT_SEL_I2S_IN      0x0001U
#define SGTL5000_I2S_OUT_SEL_DAP         0x0003U

/*
 * SGTL5000_CHIP_ADCDAC_CTRL
 */
#define SGTL5000_VOL_BUSY_DAC_RIGHT         0x2000U
#define SGTL5000_VOL_BUSY_DAC_LEFT          0x1000U
#define SGTL5000_DAC_VOL_RAMP_EN_CLR_MASK   0xFDFFU
#define SGTL5000_DAC_VOL_RAMP_EN_GET_MASK   0x0200U
#define SGTL5000_DAC_VOL_RAMP_EN_SHIFT      0x9U
#define SGTL5000_DAC_VOL_RAMP_EXPO_CLR_MASK 0xFEFFU
#define SGTL5000_DAC_VOL_RAMP_EXPO_GET_MASK 0x0100U
#define SGTL5000_DAC_VOL_RAMP_EXPO_SHIFT    0x8U
#define SGTL5000_DAC_MUTE_RIGHT_CLR_MASK    0xFFF7U
#define SGTL5000_DAC_MUTE_RIGHT_GET_MASK    0x0008U
#define SGTL5000_DAC_MUTE_RIGHT_SHIFT       0x3U
#define SGTL5000_DAC_MUTE_LEFT_CLR_MASK     0xFFFBU
#define SGTL5000_DAC_MUTE_LEFT_GET_MASK     0x0004U
#define SGTL5000_DAC_MUTE_LEFT_SHIFT        0x2U
#define SGTL5000_ADC_HPF_FREEZE_CLR_MASK    0xFFFDU
#define SGTL5000_ADC_HPF_FREEZE_GET_MASK    0x0002U
#define SGTL5000_ADC_HPF_FREEZE_SHIFT       0x1U
#define SGTL5000_ADC_HPF_BYPASS_CLR_MASK    0xFFFEU
#define SGTL5000_ADC_HPF_BYPASS_GET_MASK    0x0001U
#define SGTL5000_ADC_HPF_BYPASS_SHIFT       0x0U

/*
 * SGTL5000_CHIP_DAC_VOL
 */
#define SGTL5000_DAC_VOL_RIGHT_CLR_MASK 0x00FFU
#define SGTL5000_DAC_VOL_RIGHT_GET_MASK 0xFF00U
#define SGTL5000_DAC_VOL_RIGHT_SHIFT    0x8U
#define SGTL5000_DAC_VOL_LEFT_CLR_MASK  0xFF00U
#define SGTL5000_DAC_VOL_LEFT_GET_MASK  0x00FFU
#define SGTL5000_DAC_VOL_LEFT_SHIFT     0x0U

/*
 * SGTL5000_CHIP_PAD_STRENGTH
 */
#define SGTL5000_PAD_I2S_LRCLK_CLR_MASK 0xFCFFU
#define SGTL5000_PAD_I2S_LRCLK_GET_MASK 0x0300U
#define SGTL5000_PAD_I2S_LRCLK_SHIFT    0x8U
#define SGTL5000_PAD_I2S_SCLK_CLR_MASK  0xFF3FU
#define SGTL5000_PAD_I2S_SCLK_GET_MASK  0x00C0U
#define SGTL5000_PAD_I2S_SCLK_SHIFT     0x6U
#define SGTL5000_PAD_I2S_DOUT_CLR_MASK  0xFFCFU
#define SGTL5000_PAD_I2S_DOUT_GET_MASK  0x0030U
#define SGTL5000_PAD_I2S_DOUT_SHIFT     0x4U
#define SGTL5000_PAD_I2C_SDA_CLR_MASK   0xFFF3U
#define SGTL5000_PAD_I2C_SDA_GET_MASK   0x000CU
#define SGTL5000_PAD_I2C_SDA_SHIFT      0x2U
#define SGTL5000_PAD_I2C_SCL_CLR_MASK   0xFFFCU
#define SGTL5000_PAD_I2C_SCL_GET_MASK   0x0003U
#define SGTL5000_PAD_I2C_SCL_SHIFT      0x0U

/*
 * SGTL5000_CHIP_ANA_ADC_CTRL
 */
#define SGTL5000_ADC_VOL_M6DB_CLR_MASK  0xFEFFU
#define SGTL5000_ADC_VOL_M6DB_GET_MASK  0x0100U
#define SGTL5000_ADC_VOL_M6DB_SHIFT     0x8U
#define SGTL5000_ADC_VOL_RIGHT_CLR_MASK 0xFF0FU
#define SGTL5000_ADC_VOL_RIGHT_GET_MASK 0x00F0U
#define SGTL5000_ADC_VOL_RIGHT_SHIFT    0x4U
#define SGTL5000_ADC_VOL_LEFT_CLR_MASK  0xFFF0U
#define SGTL5000_ADC_VOL_LEFT_GET_MASK  0x000FU
#define SGTL5000_ADC_VOL_LEFT_SHIFT     0x0U

/*
 * SGTL5000_CHIP_ANA_HP_CTRL
 */
#define SGTL5000_HP_VOL_RIGHT_CLR_MASK 0x80FFU
#define SGTL5000_HP_VOL_RIGHT_GET_MASK 0x7F00U
#define SGTL5000_HP_VOL_RIGHT_SHIFT    0x8U
#define SGTL5000_HP_VOL_LEFT_CLR_MASK  0xFF80U
#define SGTL5000_HP_VOL_LEFT_GET_MASK  0x007FU
#define SGTL5000_HP_VOL_LEFT_SHIFT     0x0U

/*
 * SGTL5000_CHIP_ANA_CTRL
 */
#define SGTL5000_MUTE_LO_GET_MASK    0x0100U
#define SGTL5000_MUTE_LO_CLR_MASK    0xFEFFU
#define SGTL5000_MUTE_LO_SHIFT       0x8U
#define SGTL5000_SEL_HP_GET_MASK     0x0040U
#define SGTL5000_SEL_HP_CLR_MASK     0xFFBFU
#define SGTL5000_SEL_HP_SHIFT        0x6U
#define SGTL5000_SEL_HP_DAC          0x0000U
#define SGTL5000_SEL_HP_LINEIN       0x0040U
#define SGTL5000_EN_ZCD_HP_GET_MASK  0x0020U
#define SGTL5000_EN_ZCD_HP_CLR_MASK  0xFFDFU
#define SGTL5000_EN_ZCD_HP_SHIFT     0x5U
#define SGTL5000_MUTE_HP_GET_MASK    0x0010U
#define SGTL5000_MUTE_HP_CLR_MASK    0xFFEFU
#define SGTL5000_MUTE_HP_SHIFT       0x4U
#define SGTL5000_SEL_ADC_GET_MASK    0x0004U
#define SGTL5000_SEL_ADC_CLR_MASK    0xFFFBU
#define SGTL5000_SEL_ADC_SHIFT       0x2U
#define SGTL5000_SEL_ADC_MIC         0x0000U
#define SGTL5000_SEL_ADC_LINEIN      0x0004U
#define SGTL5000_EN_ZCD_ADC_GET_MASK 0x0002U
#define SGTL5000_EN_ZCD_ADC_CLR_MASK 0xFFFDU
#define SGTL5000_EN_ZCD_ADC_SHIFT    0x1U
#define SGTL5000_MUTE_ADC_GET_MASK   0x0001U
#define SGTL5000_MUTE_ADC_CLR_MASK   0xFFFEU
#define SGTL5000_MUTE_ADC_SHIFT      0x0U

/*
 * SGTL5000_CHIP_LINREG_CTRL
 */
#define SGTL5000_VDDC_MAN_ASSN_CLR_MASK 0xFFBFU
#define SGTL5000_VDDC_MAN_ASSN_GET_MASK 0x0040U
#define SGTL5000_VDDC_MAN_ASSN_SHIFT    0x6U
#define SGTL5000_VDDC_MAN_ASSN_VDDA     0x0000U
#define SGTL5000_VDDC_MAN_ASSN_VDDIO    0x0040U
#define SGTL5000_VDDC_ASSN_OVRD         0x0020U
#define SGTL5000_LINREG_VDDD_CLR_MASK   0xFFF0U
#define SGTL5000_LINREG_VDDD_GET_MASK   0x000FU
#define SGTL5000_LINREG_VDDD_SHIFT      0x0U

/*
 * SGTL5000_CHIP_REF_CTRL
 */
#define SGTL5000_ANA_GND_MASK    0x01f0U
#define SGTL5000_ANA_GND_SHIFT   0x4U
#define SGTL5000_ANA_GND_WIDTH   0x5U
#define SGTL5000_ANA_GND_BASE    0x320U /* mv */
#define SGTL5000_ANA_GND_STP     0x19U  /*mv */
#define SGTL5000_BIAS_CTRL_MASK  0x000eU
#define SGTL5000_BIAS_CTRL_SHIFT 0x1U
#define SGTL5000_BIAS_CTRL_WIDTH 0x3U
#define SGTL5000_SMALL_POP       0x0001U

/*
 * SGTL5000_CHIP_MIC_CTRL
 */
#define SGTL5000_BIAS_R__CLR_MASK   0xFCFFU
#define SGTL5000_BIAS_R_GET_MASK    0x0300U
#define SGTL5000_BIAS_R_SHIFT       0x8U
#define SGTL5000_BIAS_R_off         0x0000U
#define SGTL5000_BIAS_R_2K          0x0100U
#define SGTL5000_BIAS_R_4k          0x0200U
#define SGTL5000_BIAS_R_8k          0x0300U
#define SGTL5000_BIAS_VOLT_CLR_MASK 0xFF8FU
#define SGTL5000_BIAS_VOLT_GET_MASK 0x0070U
#define SGTL5000_BIAS_VOLT_SHIFT    0x4U
#define SGTL5000_MIC_GAIN_CLR_MASK  0xFFFCU
#define SGTL5000_MIC_GAIN_GET_MASK  0x0003U
#define SGTL5000_MIC_GAIN_SHIFT     0x0U

/*
 * SGTL5000_CHIP_LINE_OUT_CTRL
 */
#define SGTL5000_LINE_OUT_CURRENT_CLR_MASK 0xF0FFU
#define SGTL5000_LINE_OUT_CURRENT_GET_MASK 0x0F00U
#define SGTL5000_LINE_OUT_CURRENT_SHIFT    0x8U
#define SGTL5000_LINE_OUT_CURRENT_180u     0x0000U
#define SGTL5000_LINE_OUT_CURRENT_270u     0x0100U
#define SGTL5000_LINE_OUT_CURRENT_360u     0x0300U
#define SGTL5000_LINE_OUT_CURRENT_450u     0x0700U
#define SGTL5000_LINE_OUT_CURRENT_540u     0x0F00U
#define SGTL5000_LINE_OUT_GND_CLR_MASK     0xFFC0U
#define SGTL5000_LINE_OUT_GND_GET_MASK     0x003FU
#define SGTL5000_LINE_OUT_GND_SHIFT        0x0U
#define SGTL5000_LINE_OUT_GND_BASE         0x320U /* mv */
#define SGTL5000_LINE_OUT_GND_STP          0x19U
#define SGTL5000_LINE_OUT_GND_MAX          0x23U

/*
 * SGTL5000_CHIP_LINE_OUT_VOL
 */
#define SGTL5000_LINE_OUT_VOL_RIGHT_CLR_MASK 0xE0FFU
#define SGTL5000_LINE_OUT_VOL_RIGHT_GET_MASK 0x1F00U
#define SGTL5000_LINE_OUT_VOL_RIGHT_SHIFT    0x8U
#define SGTL5000_LINE_OUT_VOL_LEFT_CLR_MASK  0xFFE0U
#define SGTL5000_LINE_OUT_VOL_LEFT_GET_MASK  0x001FU
#define SGTL5000_LINE_OUT_VOL_LEFT_SHIFT     0x0U

/*
 * SGTL5000_CHIP_ANA_POWER
 */
#define SGTL5000_RIGHT_DAC_POWERUP_GET_MASK         0x4000U
#define SGTL5000_RIGHT_DAC_POWERUP_CLR_MASK         0xBFFFU
#define SGTL5000_RIGHT_DAC_POWERUP_SHIFT            0xEU
#define SGTL5000_LINREG_SIMPLE_POWERUP_GET_MASK     0x2000U
#define SGTL5000_LINREG_SIMPLE_POWERUP_CLR_MASK     0xDFFFU
#define SGTL5000_LINREG_SIMPLE_POWERUP_SHIFT        0xDU
#define SGTL5000_STARTUP_POWERUP_GET_MASK           0x1000U
#define SGTL5000_STARTUP_POWERUP_CLR_MASK           0xEFFFU
#define SGTL5000_STARTUP_POWERUP_SHIFT              0xCU
#define SGTL5000_VDDC_CHRGPMP_POWERUP_GET_MASK      0x0800U
#define SGTL5000_VDDC_CHRGPMP_POWERUP_CLR_MASK      0xF7FFU
#define SGTL5000_VDDC_CHRGPMP_POWERUP_SHIFT         0xBU
#define SGTL5000_PLL_POWERUP_GET_MASK               0x0400U
#define SGTL5000_PLL_POWERUP_CLR_MASK               0xFBFFU
#define SGTL5000_PLL_POWERUP_SHIFT                  0xAU
#define SGTL5000_LINREG_D_POWERUP_GET_MASK          0x0200U
#define SGTL5000_LINREG_D_POWERUP_CLR_MASK          0xFDFFU
#define SGTL5000_LINREG_D_POWERUP_SHIFT             0x9U
#define SGTL5000_VCOAMP_POWERUP_GET_MASK            0x0100U
#define SGTL5000_VCOAMP_POWERUP_CLR_MASK            0xFEFFU
#define SGTL5000_VCOAMP_POWERUP_SHIFT               0x8U
#define SGTL5000_VAG_POWERUP_GET_MASK               0x0080U
#define SGTL5000_VAG_POWERUP_CLR_MASK               0xFF7FU
#define SGTL5000_VAG_POWERUP_SHIFT                  0x7U
#define SGTL5000_RIGHT_ADC_POWERUP_GET_MASK         0x0040U
#define SGTL5000_RIGHT_ADC_POWERUP_CLR_MASK         0xFFBFU
#define SGTL5000_RIGHT_ADC_POWERUP_SHIFT            0x6U
#define SGTL5000_REFTOP_POWERUP_GET_MASK            0x0020U
#define SGTL5000_REFTOP_POWERUP_CLR_MASK            0xFFDFU
#define SGTL5000_REFTOP_POWERUP_SHIFT               0x5U
#define SGTL5000_HEADPHONE_POWERUP_GET_MASK         0x0010U
#define SGTL5000_HEADPHONE_POWERUP_CLR_MASK         0xFFEFU
#define SGTL5000_HEADPHONE_POWERUP_SHIFT            0x4U
#define SGTL5000_DAC_POWERUP_GET_MASK               0x0008U
#define SGTL5000_DAC_POWERUP_CLR_MASK               0xFFF7U
#define SGTL5000_DAC_POWERUP_SHIFT                  0x3U
#define SGTL5000_CAPLESS_HEADPHONE_POWERUP_GET_MASK 0x0004U
#define SGTL5000_CAPLESS_HEADPHONE_POWERUP_CLR_MASK 0xFFFBU
#define SGTL5000_CAPLESS_HEADPHONE_POWERUP_SHIFT    0x2U
#define SGTL5000_ADC_POWERUP_GET_MASK               0x0002U
#define SGTL5000_ADC_POWERUP_CLR_MASK               0xFFFDU
#define SGTL5000_ADC_POWERUP_SHIFT                  0x1U
#define SGTL5000_LINEOUT_POWERUP_GET_MASK           0x0001U
#define SGTL5000_LINEOUT_POWERUP_CLR_MASK           0xFFFEU
#define SGTL5000_LINEOUT_POWERUP_SHIFT              0x0U

/*
 * SGTL5000_CHIP_PLL_CTRL
 */
#define SGTL5000_PLL_INT_DIV_CLR_MASK  0x07FFU
#define SGTL5000_PLL_INT_DIV_GET_MASK  0xF800U
#define SGTL5000_PLL_INT_DIV_SHIFT     0xBU
#define SGTL5000_PLL_FRAC_DIV_CLR_MASK 0xF8FFU
#define SGTL5000_PLL_FRAC_DIV_GET_MASK 0x0700U
#define SGTL5000_PLL_FRAC_DIV_SHIFT    0x0U

/*
 * SGTL5000_CHIP_CLK_TOP_CTRL
 */
#define SGTL5000_ENABLE_INT_OSC_GET_MASK  0x0800U
#define SGTL5000_ENABLE_INT_OSC_CLR_MASK  0xF7FFU
#define SGTL5000_ENABLE_INT_OSC_SHIFT     0xBU
#define SGTL5000_INPUT_FREQ_DIV2_GET_MASK 0x0008U
#define SGTL5000_INPUT_FREQ_DIV2_CLR_MASK 0xFFF7U
#define SGTL5000_INPUT_FREQ_DIV2_SHIFT    0x3U

/*
 * SGTL5000_CHIP_ANA_STATUS
 */
#define SGTL5000_HP_LRSHORT    0x0200U
#define SGTL5000_CAPLESS_SHORT 0x0100U
#define SGTL5000_PLL_LOCKED    0x0010U

/*
 * SGTL5000_CHIP_SHORT_CTRL
 */
#define SGTL5000_LVLADJR_CLR_MASK      0x8FFFU
#define SGTL5000_LVLADJR_GET_MASK      0x7000U
#define SGTL5000_LVLADJR_SHIFT         0xCU
#define SGTL5000_LVLADJL_CLR_MASK      0xF8FFU
#define SGTL5000_LVLADJL_GET_MASK      0x0700U
#define SGTL5000_LVLADJL_SHIFT         0x8U
#define SGTL5000_LVLADJC_CLR_MASK      0xFF8FU
#define SGTL5000_LVLADJC_GET_MASK      0x0070U
#define SGTL5000_LVLADJC_SHIFT         0x4U
#define SGTL5000_LR_SHORT_MOD_CLR_MASK 0xFFF3U
#define SGTL5000_LR_SHORT_MOD_GET_MASK 0x000CU
#define SGTL5000_LR_SHORT_MOD_SHIFT    0x2U
#define SGTL5000_CM_SHORT_MOD_CLR_MASK 0xFFFCU
#define SGTL5000_CM_SHORT_MOD_GET_MASK 0x0003U
#define SGTL5000_CM_SHORT_MOD_SHIFT    0x0U

/* DAP control register */
#define SGTL5000_DAP_CONTROL_MIX_EN_GET_MASK 0x0010U
#define SGTL5000_DAP_CONTROL_MIX_EN_CLR_MASK 0xFFEFU
#define SGTL5000_DAP_CONTROL_MIX_EN_SHIFT    0x4U
#define SGTL5000_DAP_CONTROL_DAP_EN_GET_MASK 0x0001U
#define SGTL5000_DAP_CONTROL_DAP_EN_CLR_MASK 0xFFFEU
#define SGTL5000_DAP_CONTROL_DAP_EN_SHIFT    0x0U

/*
 * DAP_PEQ_REG
 */
#define SGTL5000_DAP_PEQ_EN_GET_MASK 0x0007U
#define SGTL5000_DAP_PEQ_EN_CLR_MASK 0xFFF8U
#define SGTL5000_DAP_PEQ_EN_SHIFT    0x0U

/*
 * DAP_BASS_ENHANCE_REG
 */
#define SGTL5000_DAP_BASS_ENHANCE_MULT_GET_MASK       0xC000U
#define SGTL5000_DAP_BASS_ENHANCE_MULT_CLR_MASK       0x3FFFU
#define SGTL5000_DAP_BASS_ENHANCE_MULT_SHIFT          0xEU
#define SGTL5000_DAP_BASS_ENHANCE_CUTOFF_HPF_GET_MASK 0x0E00U
#define SGTL5000_DAP_BASS_ENHANCE_CUTOFF_HPF_CLR_MASK 0xF1FFU
#define SGTL5000_DAP_BASS_ENHANCE_CUTOFF_HPF_SHIFT    0x9U
#define SGTL5000_DAP_BASS_ENHANCE_BYPASS_HPF_GET_MASK 0x0100U
#define SGTL5000_DAP_BASS_ENHANCE_BYPASS_HPF_CLR_MASK 0xFEFFU
#define SGTL5000_DAP_BASS_ENHANCE_BYPASS_HPF_SHIFT    0x8U
#define SGTL5000_DAP_BASS_ENHANCE_CUTOFF_GET_MASK     0x0070U
#define SGTL5000_DAP_BASS_ENHANCE_CUTOFF_CLR_MASK     0xFF8FU
#define SGTL5000_DAP_BASS_ENHANCE_CUTOFF_SHIFT        0x4U
#define SGTL5000_DAP_BASS_ENHANCE_EN_GET_MASK         0x0001U
#define SGTL5000_DAP_BASS_ENHANCE_EN_CLR_MASK         0xFFFEU
#define SGTL5000_DAP_BASS_ENHANCE_EN_SHIFT            0x0U

/*
 * DAP_BASS_ENHANCE_CTRL_REG
 */
#define SGTL5000_DAP_BASS_ENHANCE_CTRL_LR_LEVEL_GET_MASK   0x3F00U
#define SGTL5000_DAP_BASS_ENHANCE_CTRL_LR_LEVEL_CLR_MASK   0xC0FFU
#define SGTL5000_DAP_BASS_ENHANCE_CTRL_LR_LEVEL_SHIFT      0x8U
#define SGTL5000_DAP_BASS_ENHANCE_CTRL_BASS_LEVEL_GET_MASK 0x007FU
#define SGTL5000_DAP_BASS_ENHANCE_CTRL_BASS_LEVEL_CLR_MASK 0xFF80U
#define SGTL5000_DAP_BASS_ENHANCE_CTRL_BASS_LEVEL_SHIFT    0x0U

/*
 * DAP_AUDIO_EQ_REG
 */
#define SGTL5000_DAP_AUDIO_EQ_EN_GET_MASK 0x0003U
#define SGTL5000_DAP_AUDIO_EQ_EN_CLR_MASK 0xFFFCU
#define SGTL5000_DAP_AUDIO_EQ_EN_SHIFT    0x0U

/*
 * DAP_SGTL_SURROUND_REG
 */
#define SGTL5000_DAP_SGTL_SURROUND_WIDTH_CONTROL_GET_MASK 0x0070U
#define SGTL5000_DAP_SGTL_SURROUND_WIDTH_CONTROL_CLR_MASK 0xFF8FU
#define SGTL5000_DAP_SGTL_SURROUND_WIDTH_CONTROL_SHIFT    0x4U
#define SGTL5000_DAP_SGTL_SURROUND_SEL_GET_MASK           0x0003U
#define SGTL5000_DAP_SGTL_SURROUND_SEL_CLR_MASK           0xFFFCU
#define SGTL5000_DAP_SGTL_SURROUND_SEL_SHIFT              0x0U

/*
 * DAP_FILTER_COEF_ACCESS_REG
 */
#define SGTL5000_DAP_FILTER_COEF_ACCESS_DEBUG_GET_MASK 0x1000U
#define SGTL5000_DAP_FILTER_COEF_ACCESS_DEBUG_CLR_MASK 0xEFFFU
#define SGTL5000_DAP_FILTER_COEF_ACCESS_DEBUG_SHIFT    0xCU
#define SGTL5000_DAP_FILTER_COEF_ACCESS_RD_GET_MASK    0x0200U
#define SGTL5000_DAP_FILTER_COEF_ACCESS_RD_CLR_MASK    0xFDFFU
#define SGTL5000_DAP_FILTER_COEF_ACCESS_RD_SHIFT       0x9U
#define SGTL5000_DAP_FILTER_COEF_ACCESS_WR_GET_MASK    0x0100U
#define SGTL5000_DAP_FILTER_COEF_ACCESS_WR_CLR_MASK    0xFEFFU
#define SGTL5000_DAP_FILTER_COEF_ACCESS_WR_SHIFT       0x8U
#define SGTL5000_DAP_FILTER_COEF_ACCESS_INDEX_GET_MASK 0x00FFU
#define SGTL5000_DAP_FILTER_COEF_ACCESS_INDEX_CLR_MASK 0xFF00U
#define SGTL5000_DAP_FILTER_COEF_ACCESS_INDEX_SHIFT    0x0U

/*
 *  DAP_COEF_WR_B0_MSB_REG
 */
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_19_GET_MASK 0x8000U
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_19_CLR_MASK 0x7FFFU
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_19_SHIFT    0xFU
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_18_GET_MASK 0x4000U
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_18_CLR_MASK 0xBFFFU
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_18_SHIFT    0xEU
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_17_GET_MASK 0x2000U
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_17_CLR_MASK 0xDFFFU
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_17_SHIFT    0xDU
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_16_GET_MASK 0x1000U
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_16_CLR_MASK 0xEFFFU
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_16_SHIFT    0xCU
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_15_GET_MASK 0x0800U
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_15_CLR_MASK 0xF7FFU
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_15_SHIFT    0xBU
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_14_GET_MASK 0x0400U
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_14_CLR_MASK 0xFBFFU
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_14_SHIFT    0xAU
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_13_GET_MASK 0x0200U
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_13_CLR_MASK 0xFDFFU
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_13_SHIFT    0x9U
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_12_GET_MASK 0x0100U
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_12_CLR_MASK 0xFEFFU
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_12_SHIFT    0x8U
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_11_GET_MASK 0x0080U
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_11_CLR_MASK 0xFF7FU
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_11_SHIFT    0x7U
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_10_GET_MASK 0x0040U
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_10_CLR_MASK 0xFFBFU
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_10_SHIFT    0x6U
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_9_GET_MASK  0x0020U
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_9_CLR_MASK  0xFFDFU
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_9_SHIFT     0x5U
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_8_GET_MASK  0x0010U
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_8_CLR_MASK  0xFFEFU
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_8_SHIFT     0x4U
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_7_GET_MASK  0x0008U
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_7_CLR_MASK  0xFFF7U
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_7_SHIFT     0x3U
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_6_GET_MASK  0x0004U
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_6_CLR_MASK  0xFFFBU
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_6_SHIFT     0x2U
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_5_GET_MASK  0x0002U
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_5_CLR_MASK  0xFFFDU
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_5_SHIFT     0x1U
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_4_GET_MASK  0x0001U
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_4_CLR_MASK  0xFFFEU
#define SGTL5000_DAP_COEF_WR_B0_MSB_BIT_4_SHIFT     0x0U

/*
 * DAP_COEF_WR_B0_LSB_REG
 */
#define SGTL5000_DAP_COEF_WR_B0_LSB_BIT_3_GET_MASK 0x0008U
#define SGTL5000_DAP_COEF_WR_B0_LSB_BIT_3_CLR_MASK 0xFFF7U
#define SGTL5000_DAP_COEF_WR_B0_LSB_BIT_3_SHIFT    0x3U
#define SGTL5000_DAP_COEF_WR_B0_LSB_BIT_2_GET_MASK 0x0004U
#define SGTL5000_DAP_COEF_WR_B0_LSB_BIT_2_CLR_MASK 0xFFFBU
#define SGTL5000_DAP_COEF_WR_B0_LSB_BIT_2_SHIFT    0x2U
#define SGTL5000_DAP_COEF_WR_B0_LSB_BIT_1_GET_MASK 0x0002U
#define SGTL5000_DAP_COEF_WR_B0_LSB_BIT_1_CLR_MASK 0xFFFDU
#define SGTL5000_DAP_COEF_WR_B0_LSB_BIT_1_SHIFT    0x1U
#define SGTL5000_DAP_COEF_WR_B0_LSB_BIT_0_GET_MASK 0x0001U
#define SGTL5000_DAP_COEF_WR_B0_LSB_BIT_0_CLR_MASK 0xFFFEU
#define SGTL5000_DAP_COEF_WR_B0_LSB_BIT_0_SHIFT    0x0U

/*
 * DAP_AUDIO_EQ_BASS_BAND0_REG
 */
#define SGTL5000_DAP_AUDIO_EQ_BASS_BAND0_VOLUME_GET_MASK 0x007FU
#define SGTL5000_DAP_AUDIO_EQ_BASS_BAND0_VOLUME_CLR_MASK 0xFF80U
#define SGTL5000_DAP_AUDIO_EQ_BASS_BAND0_VOLUME_SHIFT    0x0U

/*
 * DAP_AUDIO_EQ_BAND1_REG
 */
#define SGTL5000_DAP_AUDIO_EQ_BAND1_VOLUME_GET_MASK 0x007FU
#define SGTL5000_DAP_AUDIO_EQ_BAND1_VOLUME_CLR_MASK 0xFF80U
#define SGTL5000_DAP_AUDIO_EQ_BAND1_VOLUME_SHIFT    0x0U

/*
 * DAP_AUDIO_EQ_BAND2_REG
 */
#define SGTL5000_DAP_AUDIO_EQ_BAND2_VOLUME_GET_MASK 0x007FU
#define SGTL5000_DAP_AUDIO_EQ_BAND2_VOLUME_CLR_MASK 0xFF80U
#define SGTL5000_DAP_AUDIO_EQ_BAND2_VOLUME_SHIFT    0x0U

/*
 * DAP_AUDIO_EQ_BAND3_REG
 */
#define SGTL5000_DAP_AUDIO_EQ_BAND3_VOLUME_GET_MASK 0x007FU
#define SGTL5000_DAP_AUDIO_EQ_BAND3_VOLUME_CLR_MASK 0xFF80U
#define SGTL5000_DAP_AUDIO_EQ_BAND3_VOLUME_SHIFT    0x0U

/*
 * DAP_AUDIO_EQ_TREBLE_BAND4_REG
 */
#define SGTL5000_DAP_AUDIO_EQ_TREBLE_BAND4_VOLUME_GET_MASK 0x007FU
#define SGTL5000_DAP_AUDIO_EQ_TREBLE_BAND4_VOLUME_CLR_MASK 0xFF80U
#define SGTL5000_DAP_AUDIO_EQ_TREBLE_BAND4_VOLUME_SHIFT    0x0U

/*
 * DAP_MAIN_CHAN_REG
 */
#define SGTL5000_DAP_MAIN_CHAN_VOL_GET_MASK 0xFFFFU
#define SGTL5000_DAP_MAIN_CHAN_VOL_CLR_MASK 0x0000U
#define SGTL5000_DAP_MAIN_CHAN_VOL_SHIFT    0x0U

/*
 * DAP_MIX_CHAN_REG
 */
#define SGTL5000_DAP_MIX_CHAN_VOL_GET_MASK 0xFFFFU
#define SGTL5000_DAP_MIX_CHAN_VOL_CLR_MASK 0x0000U
#define SGTL5000_DAP_MIX_CHAN_VOL_SHIFT    0x0U

/*
 * DAP_AVC_CTRL_REG
 */
#define SGTL5000_DAP_AVC_CTRL_APOP_ENABLE_GET_MASK   0x4000U
#define SGTL5000_DAP_AVC_CTRL_APOP_ENABLE_CLR_MASK   0xBFFFU
#define SGTL5000_DAP_AVC_CTRL_APOP_ENABLE_SHIFT      0xEU
#define SGTL5000_DAP_AVC_CTRL_MAX_GAIN_GET_MASK      0x3000U
#define SGTL5000_DAP_AVC_CTRL_MAX_GAIN_CLR_MASK      0xCFFFU
#define SGTL5000_DAP_AVC_CTRL_MAX_GAIN_SHIFT         0xCU
#define SGTL5000_DAP_AVC_CTRL_LBI_RESPONSE_GET_MASK  0x0300U
#define SGTL5000_DAP_AVC_CTRL_LBI_RESPONSE_CLR_MASK  0xFCFFU
#define SGTL5000_DAP_AVC_CTRL_LBI_RESPONSE_SHIFT     0x8U
#define SGTL5000_DAP_AVC_CTRL_HARD_LIMIT_EN_GET_MASK 0x0020U
#define SGTL5000_DAP_AVC_CTRL_HARD_LIMIT_EN_CLR_MASK 0xFFDFU
#define SGTL5000_DAP_AVC_CTRL_HARD_LIMIT_EN_SHIFT    0x5U
#define SGTL5000_DAP_AVC_CTRL_STOP_GET_MASK          0x0004U
#define SGTL5000_DAP_AVC_CTRL_STOP_SHIFT             0x2U
#define SGTL5000_DAP_AVC_CTRL_RUNNING_GET_MASK       0x0002U
#define SGTL5000_DAP_AVC_CTRL_RUNNING_SHIFT          0x1U
#define SGTL5000_DAP_AVC_CTRL_EN_GET_MASK            0x0001U
#define SGTL5000_DAP_AVC_CTRL_EN_CLR_MASK            0xFFFEU
#define SGTL5000_DAP_AVC_CTRL_EN_SHIFT               0x0U

/*
 * DAP_AVC_ATTACK_REG
 */
#define SGTL5000_DAP_AVC_ATTACK_RATE_GET_MASK 0x0FFFU
#define SGTL5000_DAP_AVC_ATTACK_RATE_CLR_MASK 0xF000U
#define SGTL5000_DAP_AVC_ATTACK_RATE_SHIFT    0x0U

/*
 * DAP_AVC_DECAY_REG
 */
#define SGTL5000_DAP_AVC_DECAY_RATE_GET_MASK 0x0FFFU
#define SGTL5000_DAP_AVC_DECAY_RATE_CLR_MASK 0xF000U
#define SGTL5000_DAP_AVC_DECAY_RATE_SHIFT    0x0U

/*
 * DAP_COEF_WR_B1_LSB_REG
 */
#define SGTL5000_DAP_COEF_WR_B1_LSB_LSB_GET_MASK 0x000FU
#define SGTL5000_DAP_COEF_WR_B1_LSB_LSB_CLR_MASK 0xFFF0U
#define SGTL5000_DAP_COEF_WR_B1_LSB_LSB_SHIFT    0x0U

/*
 * DAP_COEF_WR_B2_LSB_REG
 */
#define SGTL5000_DAP_COEF_WR_B2_LSB_LSB_GET_MASK 0x000FU
#define SGTL5000_DAP_COEF_WR_B2_LSB_LSB_CLR_MASK 0xFFF0U
#define SGTL5000_DAP_COEF_WR_B2_LSB_LSB_SHIFT    0x0U

/*
 * DAP_COEF_WR_A1_LSB_REG
 */
#define SGTL5000_DAP_COEF_WR_A1_LSB_LSB_GET_MASK 0x000FU
#define SGTL5000_DAP_COEF_WR_A1_LSB_LSB_CLR_MASK 0xFFF0U
#define SGTL5000_DAP_COEF_WR_A1_LSB_LSB_SHIFT    0x0U

/*
 * DAP_COEF_WR_A2_LSB_REG
 */
#define SGTL5000_DAP_COEF_WR_A2_LSB_LSB_GET_MASK 0x000FU
#define SGTL5000_DAP_COEF_WR_A2_LSB_LSB_CLR_MASK 0xFFF0U
#define SGTL5000_DAP_COEF_WR_A2_LSB_LSB_SHIFT    0x0U

/*! @brief SGTL5000 volume setting range */
#define SGTL5000_HEADPHONE_MAX_VOLUME_VALUE 0x7FU
#define SGTL5000_HEADPHONE_MIN_VOLUME_VALUE 0U
#define SGTL5000_LINE_OUT_MAX_VOLUME_VALUE  0x1FU
#define SGTL5000_LINE_OUT_MIN_VOLUME_VALUE  0U
#define SGTL5000_ADC_MAX_VOLUME_VALUE       0xFU
#define SGTL5000_ADC_MIN_VOLUME_VALUE       0U
#define SGTL5000_DAC_MAX_VOLUME_VALUE       0xF0U
#define SGTL5000_DAC_MIN_VOLUME_VALUE       0x3CU

/*! @brief SGTL5000 I2C address. */
#define SGTL5000_I2C_ADDR 0x0A

/*! @brief sgtl i2c baudrate */
#define SGTL_I2C_BITRATE 100000U

/*! @brief Modules in Sgtl5000 board. */
typedef enum _sgtl5000_module {
    sgtl_module_adc = 0x0, /*!< ADC module in SGTL5000 */
    sgtl_module_dac,       /*!< DAC module in SGTL5000 */
    sgtl_module_dap,       /*!< DAP module in SGTL5000 */
    sgtl_module_hp,        /*!< Headphone module in SGTL5000 */
    sgtl_module_i2sin,     /*!< I2S-IN module in SGTL5000 */
    sgtl_module_i2sout,    /*!< I2S-OUT module in SGTL5000 */
    sgtl_module_linein,    /*!< Line-in moudle in SGTL5000 */
    sgtl_module_lineout,   /*!< Line-out module in SGTL5000 */
    sgtl_module_micin      /*!< Micphone module in SGTL5000 */
} sgtl_module_t;

/*!
 * @brief Sgtl5000 data route.
 * @note Only provide some typical data route, not all route listed.
 * Users cannot combine any routes, once a new route is set, the precios one would be replaced.
 */
typedef enum _sgtl_route {
    sgtl_route_bypass = 0x0,             /*!< LINEIN->Headphone. */
    sgtl_route_playback,                 /*!< I2SIN->DAC->Headphone. */
    sgtl_route_playback_record,        /*!< I2SIN->DAC->Headphone, LINEIN->ADC->I2SOUT. */
    sgtl_route_playback_with_dap,          /*!< I2SIN->DAP->DAC->Headphone. */
    sgtl_route_playback_with_dap_record, /*!< I2SIN->DAP->DAC->HP, LINEIN->ADC->I2SOUT. */
    sgtl_route_record                    /*!< LINEIN->ADC->I2SOUT. */
} sgtl_route_t;

/*!
 * @brief The audio data transfer protocol choice.
 * Sgtl5000 only supports I2S format and PCM format.
 */
typedef enum _sgtl_protocol {
    sgtl_bus_i2s = 0x0,      /*!< I2S Type */
    sgtl_bus_left_justified,  /*!< Left justified */
    sgtl_bus_right_justified, /*!< Right Justified */
    sgtl_bus_pcma,           /*!< PCMA */
    sgtl_bus_pcmb            /*!< PCMB */
} sgtl_protocol_t;

/*! @brief sgtl play channel
 * @anchor _sgtl_play_channel
 */
enum {
    sgtl_headphone_left  = 0, /*!< headphone left channel */
    sgtl_headphone_right = 1, /*!< headphone right channel */
    sgtl_lineout_left    = 2, /*!< lineout left channel */
    sgtl_lineout_right   = 3, /*!< lineout right channel */
};

/*! @brief sgtl record source
 * _sgtl_record_source
 */
enum {
    sgtl_record_source_linein = 0U, /*!< record source line in */
    sgtl_record_source_mic    = 1U, /*!< record source single end */
};

/*! @brief sgtl play source
 * _stgl_play_source
 */
enum {
    sgtl_play_source_linein = 0U, /*!< play source line in */
    sgtl_play_source_dac    = 1U, /*!< play source line in */
};

/*! @brief SGTL SCLK valid edge */
typedef enum _sgtl_sclk_edge {
    sgtl_sclk_valid_edge_rising   = 0U, /*!< SCLK valid edge */
    sgtl_sclk_valid_edge_failing = 1U, /*!< SCLK failling edge */
} sgtl_sclk_edge_t;

/*! @brief Audio format configuration. */
typedef struct _sgtl_audio_format {
    uint32_t mclk_hz;          /*!< master clock */
    uint32_t sample_rate;       /*!< Sample rate */
    uint32_t bit_width;         /*!< Bit width */
    sgtl_sclk_edge_t sclk_edge; /*!< sclk valid edge */
} sgtl_audio_format_t;

/*! @brief Initailize structure of sgtl5000 */
typedef struct _sgtl_config {
    sgtl_route_t route;         /*!< Audio data route.*/
    sgtl_protocol_t bus;        /*!< Audio transfer protocol */
    bool master;          /*!< Master or slave. True means master, false means slave. */
    sgtl_audio_format_t format; /*!< audio format */
} sgtl_config_t;

typedef struct {
    I2C_Type *ptr;                     /*!< sgtl I2C pointer */
    uint8_t slave_address;             /*!< code device slave address */
} sgtl_context_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief sgtl5000 initialize function.
 *
 * In this function, some configurations are fixed.
 * The second parameter can be NULL. If users want to change the SGTL5000 settings,
 * a configure structure should be prepared.
 * @note If the codec_config is NULL, it would initialize sgtl5000 using default settings.
 * The default setting:
 * @code
 * sgtl_init_t codec_config
 * codec_config.route = sgtl_route_playback_record
 * codec_config.bus = sgtl_bus_i2s
 * codec_config.master = slave
 * @endcode
 *
 * @param context Sgtl5000 context structure.
 * @param config sgtl5000 configuration structure. If this pointer equals to NULL,
 * it means using the default configuration.
 * @return Initialization status
 */
hpm_stat_t sgtl_init(sgtl_context_t *context, sgtl_config_t *config);

/*!
 * @brief Set audio data route in sgtl5000.
 *
 * This function would set the data route according to route. The route cannot be combined,
 * as all route would enable different modules.
 *
 * @note If a new route is set, the previous route would not work.
 * @param context Sgtl5000 context structure.
 * @param route Audio data route in sgtl5000.
 */
hpm_stat_t sgtl_set_data_route(sgtl_context_t *context, sgtl_route_t route);

/*!
 * @brief Set the audio transfer protocol.
 *
 * Sgtl5000 only supports I2S, I2S left, I2S right, PCM A, PCM B format.
 * @param context Sgtl5000 context structure.
 * @param protocol Audio data transfer protocol.
 */
hpm_stat_t sgtl_set_protocol(sgtl_context_t *context, sgtl_protocol_t protocol);

/*!
 * @brief Set sgtl5000 as master or slave.
 *
 * @param context Sgtl5000 context structure.
 * @param master 1 represent master, 0 represent slave.
 */
void sgtl_set_master_mode(sgtl_context_t *context, bool master);

/*!
 * @brief Set the volume of different modules in sgtl5000.
 *
 * This function would set the volume of sgtl5000 modules. This interface set module volume.
 * The function assume that left channel and right channel has the same volume.
 *
 * sgtl_module_adc volume range:      0 - 0xF,     0dB - 22.5dB
 * sgtl_module_dac volume range:      0x3C - 0xF0, 0dB - -90dB
 * sgtl_module_hp volume range:       0 - 0x7F,    12dB - -51.5dB
 * sgtl_module_lineout volume range:  0 - 0x1F,    0.5dB steps
 *
 * @param context Sgtl5000 context structure.
 * @param module Sgtl5000 module, such as DAC, ADC and etc.
 * @param volume Volume value need to be set. The value is the exact value in register.
 */
hpm_stat_t sgtl_set_volume(sgtl_context_t *context, sgtl_module_t module, uint32_t volume);

/*!
 * @brief Get the volume of different modules in sgtl5000.
 *
 * This function gets the volume of sgtl5000 modules. This interface get DAC module volume.
 * The function assume that left channel and right channel has the same volume.
 * @param context Sgtl5000 context structure.
 * @param module Sgtl5000 module, such as DAC, ADC and etc.
 * @return Module value, the value is exact value in register.
 */
uint32_t sgtl_get_volume(sgtl_context_t *context, sgtl_module_t module);

/*!
 * @brief Mute/unmute modules in sgtl5000.
 *
 * @param context Sgtl5000 context structure.
 * @param module Sgtl5000 module, such as DAC, ADC and etc.
 * @param mute True means mute, and false means unmute.
 */
hpm_stat_t sgtl_set_mute(sgtl_context_t *context, sgtl_module_t module, bool mute);

/*!
 * @brief Enable expected devices.
 * @param context Sgtl5000 context structure.
 * @param module Module expected to enable.
 */
hpm_stat_t sgtl_enable_module(sgtl_context_t *context, sgtl_module_t module);

/*!
 * @brief Disable expected devices.
 * @param context Sgtl5000 context structure.
 * @param module Module expected to enable.
 */
hpm_stat_t sgtl_disable_module(sgtl_context_t *context, sgtl_module_t module);

/*!
 * @brief Deinit the sgtl5000 codec. Shut down Sgtl5000 modules.
 * @param context Sgtl5000 context structure pointer.
 */
hpm_stat_t sgtl_deint(sgtl_context_t *context);

/*!
 * @brief Configure the data format of audio data.
 *
 * This function would configure the registers about the sample rate, bit depths.
 * @param context Sgtl5000 context structure pointer.
 * @param mclk Master clock frequency of I2S.
 * @param sample_rate Sample rate of audio file running in sgtl5000. Sgtl5000 now
 * supports 8k, 11.025k, 12k, 16k, 22.05k, 24k, 32k, 44.1k, 48k and 96k sample rate.
 * @param bits Bit depth of audio file (Sgtl5000 only supports 16bit, 20bit, 24bit
 * and 32 bit in HW).
 */
hpm_stat_t sgtl_config_data_format(sgtl_context_t *context, uint32_t mclk, uint32_t sample_rate, uint32_t bits);

/*!
 * @brief select SGTL codec play source.
 *
 * @param context Sgtl5000 context structure pointer.
 * @param playSource play source value, reference _sgtl_play_source.
 *
 * @return kStatus_Success, else failed.
 */
hpm_stat_t sgtl_set_play(sgtl_context_t *context, uint32_t playSource);

/*!
 * @brief select SGTL codec record source.
 *
 * @param context Sgtl5000 context structure pointer.
 * @param recordSource record source value, reference _sgtl_record_source.
 *
 * @return kStatus_Success, else failed.
 */
hpm_stat_t sgtl_set_record(sgtl_context_t *context, uint32_t recordSource);

/*!
 * @brief Write register to sgtl using I2C.
 * @param context Sgtl5000 context structure.
 * @param reg The register address in sgtl.
 * @param val Value needs to write into the register.
 */
hpm_stat_t sgtl_write_reg(sgtl_context_t *context, uint16_t reg, uint16_t val);

/*!
 * @brief Read register from sgtl using I2C.
 * @param context Sgtl5000 context structure.
 * @param reg The register address in sgtl.
 * @param val Value written to.
 */
hpm_stat_t sgtl_read_reg(sgtl_context_t *context, uint16_t reg, uint16_t *val);

/*!
 * @brief Modify some bits in the register using I2C.
 * @param context Sgtl5000 context structure.
 * @param reg The register address in sgtl.
 * @param clr_mask The mask code for the bits want to write. The bit you want to write should be 0.
 * @param val Value needs to write into the register.
 */
hpm_stat_t sgtl_modify_reg(sgtl_context_t *context, uint16_t reg, uint16_t clr_mask, uint16_t val);

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif /* _HPM_SGTL5000_H_ */
