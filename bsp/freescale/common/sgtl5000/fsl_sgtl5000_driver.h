/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __FSL_SGTL_5000_DRIVER_H__
#define __FSL_SGTL_5000_DRIVER_H__

#include "fsl_i2c_master_driver.h"

/*!
 * @addtogroup sgtl5000
 * @{
 */

/*! @file */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*! @brief Define the register address of sgtl5000. */
#define CHIP_ID 0x0000
#define CHIP_DIG_POWER 0x0002
#define CHIP_CLK_CTRL 0x0004
#define CHIP_I2S_CTRL 0x0006
#define CHIP_SSS_CTRL 0x000A
#define CHIP_ADCDAC_CTRL 0x000E
#define CHIP_DAC_VOL 0x0010
#define CHIP_PAD_STRENGTH 0x0014
#define CHIP_ANA_ADC_CTRL 0x0020
#define CHIP_ANA_HP_CTRL 0x0022
#define CHIP_ANA_CTRL 0x0024
#define CHIP_LINREG_CTRL 0x0026
#define CHIP_REF_CTRL 0x0028
#define CHIP_MIC_CTRL 0x002A
#define CHIP_LINE_OUT_CTRL 0x002C
#define CHIP_LINE_OUT_VOL 0x002E
#define CHIP_ANA_POWER 0x0030
#define CHIP_PLL_CTRL 0x0032
#define CHIP_CLK_TOP_CTRL 0x0034
#define CHIP_ANA_STATUS 0x0036
#define CHIP_ANA_TEST2 0x003A
#define CHIP_SHORT_CTRL 0x003C
#define DAP_CONTROL 0x0100
#define DAP_PEQ 0x0102
#define DAP_BASS_ENHANCE 0x0104
#define DAP_BASS_ENHANCE_CTRL 0x0106
#define DAP_AUDIO_EQ 0x0108
#define DAP_SGTL_SURROUND 0x010A
#define DAP_FILTER_COEF_ACCESS 0x010C
#define DAP_COEF_WR_B0_MSB 0x010E
#define DAP_COEF_WR_B0_LSB 0x0110
#define DAP_AUDIO_EQ_BASS_BAND0 0x0116
#define DAP_AUDIO_EQ_BAND1 0x0118
#define DAP_AUDIO_EQ_BAND2 0x011A
#define DAP_AUDIO_EQ_BAND3 0x011C
#define DAP_AUDIO_EQ_TREBLE_BAND4 0x011E
#define DAP_MAIN_CHAN 0x0120
#define DAP_MIX_CHAN 0x0122
#define DAP_AVC_CTRL 0x0124
#define DAP_AVC_THRESHOLD 0x0126
#define DAP_AVC_ATTACK 0x0128
#define DAP_AVC_DECAY 0x012A
#define DAP_COEF_WR_B1_MSB 0x012C
#define DAP_COEF_WR_B1_LSB 0x012E
#define DAP_COEF_WR_B2_MSB 0x0130
#define DAP_COEF_WR_B2_LSB 0x0132
#define DAP_COEF_WR_A1_MSB 0x0134
#define DAP_COEF_WR_A1_LSB 0x0136
#define DAP_COEF_WR_A2_MSB 0x0138
#define DAP_COEF_WR_A2_LSB 0x013A

/*
 * Field Definitions.
 */

/*
 * SGTL5000_CHIP_DIG_POWER
 */
#define SGTL5000_ADC_ENABLE_CLR_MASK    0xFFBF
#define SGTL5000_ADC_ENABLE_GET_MASK    0x0040
#define SGTL5000_ADC_ENABLE_SHIFT    0x6
#define SGTL5000_DAC_ENABLE_CLR_MASK    0xFFDF
#define SGTL5000_DAC_ENABLE_GET_MASK    0x0020
#define SGTL5000_DAC_ENABLE_SHIFT    0x5
#define SGTL5000_DAP_ENABLE_CLR_MASK    0xFFEF
#define SGTL5000_DAP_ENABLE_GET_MASK    0x0010
#define SGTL5000_DAP_ENABLE_SHIFT    0x4
#define SGTL5000_I2S_OUT_ENABLE_CLR_MASK    0xFFFD
#define SGTL5000_I2S_OUT_ENABLE_GET_MASK    0x0002
#define SGTL5000_I2S_OUT_ENABLE_SHIFT    0x1
#define SGTL5000_I2S_IN_ENABLE_CLR_MASK    0xFFFE
#define SGTL5000_I2S_IN_ENABLE_GET_MASK    0x0001
#define SGTL5000_I2S_IN_ENABLE_SHIFT    0x0

/*
 * SGTL5000_CHIP_CLK_CTRL
 */
#define SGTL5000_RATE_MODE_CLR_MASK    0xFFCF
#define SGTL5000_RATE_MODE_GET_MASK    0x0030
#define SGTL5000_RATE_MODE_SHIFT    0x4
#define SGTL5000_RATE_MODE_DIV_1    0x0000
#define SGTL5000_RATE_MODE_DIV_2    0x0010
#define SGTL5000_RATE_MODE_DIV_4    0x0020
#define SGTL5000_RATE_MODE_DIV_6    0x0030
#define SGTL5000_SYS_FS_CLR_MASK    0xFFF3
#define SGTL5000_SYS_FS_GET_MASK    0x000C
#define SGTL5000_SYS_FS_SHIFT    0x2
#define SGTL5000_SYS_FS_32k    0x0000
#define SGTL5000_SYS_FS_44_1k    0x0004
#define SGTL5000_SYS_FS_48k    0x0008
#define SGTL5000_SYS_FS_96k    0x000C
#define SGTL5000_MCLK_FREQ_CLR_MASK    0xFFFC
#define SGTL5000_MCLK_FREQ_GET_MASK    0x0003
#define SGTL5000_MCLK_FREQ_SHIFT    0x0
#define SGTL5000_MCLK_FREQ_256FS    0x0000
#define SGTL5000_MCLK_FREQ_384FS    0x0001
#define SGTL5000_MCLK_FREQ_512FS    0x0002
#define SGTL5000_MCLK_FREQ_PLL    0x0003

/*
 * SGTL5000_CHIP_I2S_CTRL
 */
#define SGTL5000_I2S_SLCKFREQ_CLR_MASK    0xFEFF 
#define SGTL5000_I2S_SCLKFREQ_GET_MASK    0x0100
#define SGTL5000_I2S_SCLKFREQ_SHIFT    0x8
#define SGTL5000_I2S_SCLKFREQ_64FS    0x0000
#define SGTL5000_I2S_SCLKFREQ_32FS    0x0100    /* Not for RJ mode */
#define SGTL5000_I2S_MS_CLR_MASK    0xFF7F
#define SGTL5000_I2S_MS_GET_MASK    0x0080
#define SGTL5000_I2S_MS_SHIFT    0x7
#define SGTL5000_I2S_MASTER    0x0080
#define SGTL5000_I2S_SLAVE    0x0000
#define SGTL5000_I2S_SCLK_INV_CLR_MASK    0xFFBF
#define SGTL5000_I2S_SCLK_INV_GET_MASK    0x0040
#define SGTL5000_I2S_SCLK_INV_SHIFT    0x6
#define SGTL5000_I2S_VAILD_FALLING_EDGE    0x0040
#define SGTL5000_I2S_VAILD_RISING_EDGE    0x0000
#define SGTL5000_I2S_DLEN_CLR_MASK    0xFFCF
#define SGTL5000_I2S_DLEN_GET_MASK    0x0030
#define SGTL5000_I2S_DLEN_SHIFT    0x4
#define SGTL5000_I2S_DLEN_32            0x0000
#define SGTL5000_I2S_DLEN_24            0x0010
#define SGTL5000_I2S_DLEN_20            0x0020
#define SGTL5000_I2S_DLEN_16            0x0030
#define SGTL5000_I2S_MODE_CLR_MASK    0xFFF3
#define SGTL5000_I2S_MODE_GET_MASK    0x000C
#define SGTL5000_I2S_MODE_SHIFT    0x2
#define SGTL5000_I2S_MODE_I2S_LJ    0x0000
#define SGTL5000_I2S_MODE_RJ    0x0004
#define SGTL5000_I2S_MODE_PCM    0x0008
#define SGTL5000_I2S_LRALIGN_CLR_MASK    0xFFFD
#define SGTL5000_I2S_LRALIGN_GET_MASK    0x0002
#define SGTL5000_I2S_LRALIGN_SHIFT    0x1
#define SGTL5000_I2S_ONE_BIT_DELAY    0x0000
#define SGTL5000_I2S_NO_DELAY    0x0002
#define SGTL5000_I2S_LRPOL_CLR_MASK    0xFFFE
#define SGTL5000_I2S_LRPOL_GET_MASK    0x0001
#define SGTL5000_I2S_LRPOL_SHIFT    0x0
#define SGTL5000_I2S_LEFT_FIRST    0x0000
#define SGTL5000_I2S_RIGHT_FIRST    0x0001

/*
 * SGTL5000_CHIP_SSS_CTRL
 */
#define SGTL5000_DAP_MIX_LRSWAP_CLR_MASK    0xBFFF
#define SGTL5000_DAP_MIX_LRSWAP_GET_MASK    0x4000
#define SGTL5000_DAP_MIX_LRSWAP_SHIFT    0xE
#define SGTL5000_DAP_LRSWAP_CLR_MASK    0xDFFF
#define SGTL5000_DAP_LRSWAP_GET_MASK    0x2000
#define SGTL5000_DAP_LRSWAP_SHIFT    0xD
#define SGTL5000_DAC_LRSWAP_CLR_MASK    0xEFFF
#define SGTL5000_DAC_LRSWAP_GET_MASK    0x1000
#define SGTL5000_DAC_LRSWAP_SHIFT    0xC
#define SGTL5000_I2S_LRSWAP_CLR_MASK    0xFBFF
#define SGTL5000_I2S_LRSWAP_GET_MASK    0x0400
#define SGTL5000_I2S_LRSWAP_SHIFT    0xA
#define SGTL5000_DAP_MIX_SEL_CLR_MASK    0xFCFF
#define SGTL5000_DAP_MIX_SEL_GET_MASK    0x0300
#define SGTL5000_DAP_MIX_SEL_SHIFT    0x8
#define SGTL5000_DAP_MIX_SEL_ADC    0x0000
#define SGTL5000_DAP_MIX_SEL_I2S_IN    0x0100
#define SGTL5000_DAP_SEL_CLR_MASK    0xFF3F
#define SGTL5000_DAP_SEL_GET_MASK    0x00C0
#define SGTL5000_DAP_SEL_SHIFT    0x6
#define SGTL5000_DAP_SEL_ADC    0x0000
#define SGTL5000_DAP_SEL_I2S_IN    0x0040
#define SGTL5000_DAC_SEL_CLR_MASK    0xFFCF
#define SGTL5000_DAC_SEL_GET_MASK    0x0030
#define SGTL5000_DAC_SEL_SHIFT    0x4
#define SGTL5000_DAC_SEL_ADC    0x0000
#define SGTL5000_DAC_SEL_I2S_IN    0x0010
#define SGTL5000_DAC_SEL_DAP    0x0030
#define SGTL5000_I2S_OUT_SEL_CLR_MASK    0xFFFC
#define SGTL5000_I2S_OUT_SEL_GET_MASK    0x0003
#define SGTL5000_I2S_OUT_SEL_SHIFT    0x0
#define SGTL5000_I2S_OUT_SEL_ADC    0x0000
#define SGTL5000_I2S_OUT_SEL_I2S_IN    0x0001
#define SGTL5000_I2S_OUT_SEL_DAP    0x0003

/*
 * SGTL5000_CHIP_ADCDAC_CTRL
 */
#define SGTL5000_VOL_BUSY_DAC_RIGHT    0x2000
#define SGTL5000_VOL_BUSY_DAC_LEFT    0x1000
#define SGTL5000_DAC_VOL_RAMP_EN_CLR_MASK    0xFDFF
#define SGTL5000_DAC_VOL_RAMP_EN_GET_MASK    0x0200
#define SGTL5000_DAC_VOL_RAMP_EN_SHIFT    0x9
#define SGTL5000_DAC_VOL_RAMP_EXPO_CLR_MASK    0xFEFF
#define SGTL5000_DAC_VOL_RAMP_EXPO_GET_MASK    0x0100
#define SGTL5000_DAC_VOL_RAMP_EXPO_SHIFT    0x8
#define SGTL5000_DAC_MUTE_RIGHT_CLR_MASK    0xFFF7
#define SGTL5000_DAC_MUTE_RIGHT_GET_MASK    0x0008
#define SGTL5000_DAC_MUTE_RIGHT_SHIFT    0x3
#define SGTL5000_DAC_MUTE_LEFT_CLR_MASK    0xFFFB
#define SGTL5000_DAC_MUTE_LEFT_GET_MASK    0x0004
#define SGTL5000_DAC_MUTE_LEFT_SHIFT    0x2
#define SGTL5000_ADC_HPF_FREEZE_CLR_MASK    0xFFFD
#define SGTL5000_ADC_HPF_FREEZE_GET_MASK    0x0002
#define SGTL5000_ADC_HPF_FREEZE_SHIFT    0x1
#define SGTL5000_ADC_HPF_BYPASS_CLR_MASK    0xFFFE
#define SGTL5000_ADC_HPF_BYPASS_GET_MASK    0x0001
#define SGTL5000_ADC_HPF_BYPASS_SHIFT    0x0

/*
 * SGTL5000_CHIP_DAC_VOL
 */
#define SGTL5000_DAC_VOL_RIGHT_CLR_MASK    0x00FF
#define SGTL5000_DAC_VOL_RIGHT_GET_MASK    0xFF00
#define SGTL5000_DAC_VOL_RIGHT_SHIFT    0x8
#define SGTL5000_DAC_VOL_LEFT_CLR_MASK    0xFF00
#define SGTL5000_DAC_VOL_LEFT_GET_MASK    0x00FF
#define SGTL5000_DAC_VOL_LEFT_SHIFT    0x0

/*
 * SGTL5000_CHIP_PAD_STRENGTH
 */
#define SGTL5000_PAD_I2S_LRCLK_CLR_MASK    0xFCFF 
#define SGTL5000_PAD_I2S_LRCLK_GET_MASK    0x0300
#define SGTL5000_PAD_I2S_LRCLK_SHIFT    0x8
#define SGTL5000_PAD_I2S_SCLK_CLR_MASK    0xFF3F
#define SGTL5000_PAD_I2S_SCLK_GET_MASK    0x00C0
#define SGTL5000_PAD_I2S_SCLK_SHIFT    0x6
#define SGTL5000_PAD_I2S_DOUT_CLR_MASK    0xFFCF
#define SGTL5000_PAD_I2S_DOUT_GET_MASK    0x0030
#define SGTL5000_PAD_I2S_DOUT_SHIFT    0x4
#define SGTL5000_PAD_I2C_SDA_CLR_MASK    0xFFF3
#define SGTL5000_PAD_I2C_SDA_GET_MASK    0x000C
#define SGTL5000_PAD_I2C_SDA_SHIFT    0x2
#define SGTL5000_PAD_I2C_SCL_CLR_MASK    0xFFFC
#define SGTL5000_PAD_I2C_SCL_GET_MASK    0x0003
#define SGTL5000_PAD_I2C_SCL_SHIFT    0x0

/*
 * SGTL5000_CHIP_ANA_ADC_CTRL
 */
#define SGTL5000_ADC_VOL_M6DB_CLR_MASK    0xFEFF 
#define SGTL5000_ADC_VOL_M6DB_GET_MASK    0x0100
#define SGTL5000_ADC_VOL_M6DB_SHIFT    0x8
#define SGTL5000_ADC_VOL_RIGHT_CLR_MASK    0xFF0F
#define SGTL5000_ADC_VOL_RIGHT_GET_MASK    0x00F0
#define SGTL5000_ADC_VOL_RIGHT_SHIFT    0x4
#define SGTL5000_ADC_VOL_LEFT_CLR_MASK    0xFFF0
#define SGTL5000_ADC_VOL_LEFT_GET_MASK    0x000F
#define SGTL5000_ADC_VOL_LEFT_SHIFT    0x0

/*
 * SGTL5000_CHIP_ANA_HP_CTRL
 */
#define SGTL5000_HP_VOL_RIGHT_CLR_MASK    0x80FF 
#define SGTL5000_HP_VOL_RIGHT_GET_MASK    0x7F00
#define SGTL5000_HP_VOL_RIGHT_SHIFT    0x8
#define SGTL5000_HP_VOL_LEFT_CLR_MASK    0xFF80
#define SGTL5000_HP_VOL_LEFT_GET_MASK    0x007F
#define SGTL5000_HP_VOL_LEFT_SHIFT    0x0

/*
 * SGTL5000_CHIP_ANA_CTRL
 */
#define    SGTL5000_MUTE_LO_GET_MASK    0x0100
#define    SGTL5000_MUTE_LO_CLR_MASK    0xFEFF
#define    SGTL5000_MUTE_LO_SHIFT    0x8
#define    SGTL5000_SEL_HP_GET_MASK    0x0040
#define    SGTL5000_SEL_HP_CLR_MASK    0xFFBF
#define    SGTL5000_SEL_HP_SHIFT    0x6
#define    SGTL5000_SEL_HP_DAC    0x0000
#define    SGTL5000_SEL_HP_LINEIN    0x0040
#define    SGTL5000_EN_ZCD_HP_GET_MASK    0x0020
#define    SGTL5000_EN_ZCD_HP_CLR_MASK    0xFFDF
#define    SGTL5000_EN_ZCD_HP_SHIFT    0x5
#define    SGTL5000_MUTE_HP_GET_MASK    0x0010
#define    SGTL5000_MUTE_HP_CLR_MASK    0xFFEF
#define    SGTL5000_MUTE_HP_SHIFT    0x4
#define    SGTL5000_SEL_ADC_GET_MASK    0x0004
#define    SGTL5000_SEL_ADC_CLR_MASK    0xFFFB
#define    SGTL5000_SEL_ADC_SHIFT    0x2
#define    SGTL5000_SEL_ADC_MIC    0x0000
#define    SGTL5000_SEL_ADC_LINEIN    0x0004
#define    SGTL5000_EN_ZCD_ADC_GET_MASK    0x0002
#define    SGTL5000_EN_ZCD_ADC_CLR_MASK    0xFFFD
#define    SGTL5000_EN_ZCD_ADC_SHIFT    0x1
#define    SGTL5000_MUTE_ADC_GET_MASK    0x0001
#define    SGTL5000_MUTE_ADC_CLR_MASK    0xFFFE
#define    SGTL5000_MUTE_ADC_SHIFT    0x0

/*
 * SGTL5000_CHIP_LINREG_CTRL
 */
#define SGTL5000_VDDC_MAN_ASSN_CLR_MASK    0xFFBF
#define SGTL5000_VDDC_MAN_ASSN_GET_MASK    0x0040
#define SGTL5000_VDDC_MAN_ASSN_SHIFT    0x6
#define SGTL5000_VDDC_MAN_ASSN_VDDA    0x0000
#define SGTL5000_VDDC_MAN_ASSN_VDDIO    0x0040
#define SGTL5000_VDDC_ASSN_OVRD            0x0020
#define SGTL5000_LINREG_VDDD_CLR_MASK    0xFFF0
#define SGTL5000_LINREG_VDDD_GET_MASK    0x000F
#define SGTL5000_LINREG_VDDD_SHIFT    0x0

/*
 * SGTL5000_CHIP_REF_CTRL
 */
#define SGTL5000_ANA_GND_MASK            0x01f0
#define SGTL5000_ANA_GND_SHIFT            0x4
#define SGTL5000_ANA_GND_WIDTH            0x5
#define SGTL5000_ANA_GND_BASE            0x320    /* mv */
#define SGTL5000_ANA_GND_STP            0x19    /*mv */
#define SGTL5000_BIAS_CTRL_MASK            0x000e
#define SGTL5000_BIAS_CTRL_SHIFT        0x1
#define SGTL5000_BIAS_CTRL_WIDTH        0x3
#define SGTL5000_SMALL_POP            0x0001

/*
 * SGTL5000_CHIP_MIC_CTRL
 */
#define SGTL5000_BIAS_R__CLR_MASK    0xFCFF
#define SGTL5000_BIAS_R_GET_MASK    0x0300
#define SGTL5000_BIAS_R_SHIFT    0x8
#define SGTL5000_BIAS_R_off    0x0000
#define SGTL5000_BIAS_R_2K    0x0100
#define SGTL5000_BIAS_R_4k    0x0200
#define SGTL5000_BIAS_R_8k    0x0300
#define SGTL5000_BIAS_VOLT_CLR_MASK    0xFF8F
#define SGTL5000_BIAS_VOLT_GET_MASK    0x0070
#define SGTL5000_BIAS_VOLT_SHIFT    0x4
#define SGTL5000_MIC_GAIN_CLR_MASK    0xFFFC
#define SGTL5000_MIC_GAIN_GET_MASK    0x0003
#define SGTL5000_MIC_GAIN_SHIFT    0x0

/*
 * SGTL5000_CHIP_LINE_OUT_CTRL
 */
#define SGTL5000_LINE_OUT_CURRENT_CLR_MASK    0xF0FF 
#define SGTL5000_LINE_OUT_CURRENT_GET_MASK    0x0F00
#define SGTL5000_LINE_OUT_CURRENT_SHIFT    0x8
#define SGTL5000_LINE_OUT_CURRENT_180u    0x0000
#define SGTL5000_LINE_OUT_CURRENT_270u    0x0100
#define SGTL5000_LINE_OUT_CURRENT_360u    0x0300
#define SGTL5000_LINE_OUT_CURRENT_450u    0x0700
#define SGTL5000_LINE_OUT_CURRENT_540u    0x0F00
#define SGTL5000_LINE_OUT_GND_CLR_MASK    0xFFC0
#define SGTL5000_LINE_OUT_GND_GET_MASK    0x003F
#define SGTL5000_LINE_OUT_GND_SHIFT    0x0
#define SGTL5000_LINE_OUT_GND_BASE    0x320    /* mv */
#define SGTL5000_LINE_OUT_GND_STP    0x19
#define SGTL5000_LINE_OUT_GND_MAX    0x23

/*
 * SGTL5000_CHIP_LINE_OUT_VOL
 */
#define SGTL5000_LINE_OUT_VOL_RIGHT_CLR_MASK    0xE0FF
#define SGTL5000_LINE_OUT_VOL_RIGHT_GET_MASK    0x1F00
#define SGTL5000_LINE_OUT_VOL_RIGHT_SHIFT    0x8
#define SGTL5000_LINE_OUT_VOL_LEFT_CLR_MASK    0xFFE0
#define SGTL5000_LINE_OUT_VOL_LEFT_GET_MASK    0x001F
#define SGTL5000_LINE_OUT_VOL_LEFT_SHIFT    0x0

/*
 * SGTL5000_CHIP_ANA_POWER
 */
#define    SGTL5000_RIGHT_DAC_POWERUP_GET_MASK    0x4000
#define    SGTL5000_RIGHT_DAC_POWERUP_CLR_MASK    0xBFFF
#define    SGTL5000_RIGHT_DAC_POWERUP_SHIFT    0xE
#define    SGTL5000_LINREG_SIMPLE_POWERUP_GET_MASK    0x2000
#define    SGTL5000_LINREG_SIMPLE_POWERUP_CLR_MASK    0xDFFF
#define    SGTL5000_LINREG_SIMPLE_POWERUP_SHIFT    0xD
#define    SGTL5000_STARTUP_POWERUP_GET_MASK      0x1000
#define    SGTL5000_STARTUP_POWERUP_CLR_MASK    0xEFFF
#define    SGTL5000_STARTUP_POWERUP_SHIFT     0xC
#define    SGTL5000_VDDC_CHRGPMP_POWERUP_GET_MASK    0x0800
#define    SGTL5000_VDDC_CHRGPMP_POWERUP_CLR_MASK    0xF7FF
#define    SGTL5000_VDDC_CHRGPMP_POWERUP_SHIFT    0xB
#define    SGTL5000_PLL_POWERUP_GET_MASK          0x0400
#define    SGTL5000_PLL_POWERUP_CLR_MASK        0xFBFF
#define    SGTL5000_PLL_POWERUP_SHIFT    0xA
#define    SGTL5000_LINREG_D_POWERUP_GET_MASK     0x0200
#define    SGTL5000_LINREG_D_POWERUP_CLR_MASK    0xFDFF
#define    SGTL5000_LINREG_D_POWERUP_SHIFT    0x9
#define    SGTL5000_VCOAMP_POWERUP_GET_MASK       0x0100
#define    SGTL5000_VCOAMP_POWERUP_CLR_MASK     0xFEFF
#define    SGTL5000_VCOAMP_POWERUP_SHIFT      0x8
#define    SGTL5000_VAG_POWERUP_GET_MASK          0x0080
#define    SGTL5000_VAG_POWERUP_CLR_MASK        0xFF7F
#define    SGTL5000_VAG_POWERUP_SHIFT    0x7
#define    SGTL5000_RIGHT_ADC_POWERUP_GET_MASK    0x0040
#define    SGTL5000_RIGHT_ADC_POWERUP_CLR_MASK    0xFFBF
#define    SGTL5000_RIGHT_ADC_POWERUP_SHIFT    0x6
#define    SGTL5000_REFTOP_POWERUP_GET_MASK       0x0020
#define    SGTL5000_REFTOP_POWERUP_CLR_MASK     0xFFDF
#define    SGTL5000_REFTOP_POWERUP_SHIFT      0x5
#define    SGTL5000_HEADPHONE_POWERUP_GET_MASK    0x0010
#define    SGTL5000_HEADPHONE_POWERUP_CLR_MASK    0xFFEF
#define    SGTL5000_HEADPHONE_POWERUP_SHIFT    0x4
#define    SGTL5000_DAC_POWERUP_GET_MASK          0x0008
#define    SGTL5000_DAC_POWERUP_CLR_MASK        0xFFF7
#define    SGTL5000_DAC_POWERUP_SHIFT         0x3
#define    SGTL5000_CAPLESS_HEADPHONE_POWERUP_GET_MASK    0x0004
#define    SGTL5000_CAPLESS_HEADPHONE_POWERUP_CLR_MASK    0xFFFB
#define    SGTL5000_CAPLESS_HEADPHONE_POWERUP_SHIFT    0x2
#define    SGTL5000_ADC_POWERUP_GET_MASK          0x0002
#define    SGTL5000_ADC_POWERUP_CLR_MASK        0xFFFD
#define    SGTL5000_ADC_POWERUP_SHIFT         0x1
#define    SGTL5000_LINEOUT_POWERUP_GET_MASK      0x0001
#define    SGTL5000_LINEOUT_POWERUP_CLR_MASK    0xFFFE
#define    SGTL5000_LINEOUT_POWERUP_SHIFT     0x0

/*
 * SGTL5000_CHIP_PLL_CTRL
 */
#define SGTL5000_PLL_INT_DIV_CLR_MASK    0x07FF
#define SGTL5000_PLL_INT_DIV_GET_MASK    0xF800
#define SGTL5000_PLL_INT_DIV_SHIFT    0xB
#define SGTL5000_PLL_FRAC_DIV_CLR_MASK    0xF8FF
#define SGTL5000_PLL_FRAC_DIV_GET_MASK    0x0700
#define SGTL5000_PLL_FRAC_DIV_SHIFT    0x0

/*
 * SGTL5000_CHIP_CLK_TOP_CTRL
 */
#define SGTL5000_ENABLE_INT_OSC_GET_MASK    0x0800
#define SGTL5000_ENABLE_INT_OSC_CLR_MASK    0xF7FF
#define SGTL5000_ENABLE_INT_OSC_SHIFT    0xB
#define SGTL5000_INPUT_FREQ_DIV2_GET_MASK    0x0008
#define SGTL5000_INPUT_FREQ_DIV2_CLR_MASK    0xFFF7
#define SGTL5000_INPUT_FREQ_DIV2_SHIFT    0x3

/*
 * SGTL5000_CHIP_ANA_STATUS
 */
#define SGTL5000_HP_LRSHORT    0x0200
#define SGTL5000_CAPLESS_SHORT    0x0100
#define SGTL5000_PLL_LOCKED     0x0010

/*
 * SGTL5000_CHIP_SHORT_CTRL
 */
#define SGTL5000_LVLADJR_CLR_MASK    0x8FFF
#define SGTL5000_LVLADJR_GET_MASK    0x7000
#define SGTL5000_LVLADJR_SHIFT    0xC
#define SGTL5000_LVLADJL_CLR_MASK    0xF8FF
#define SGTL5000_LVLADJL_GET_MASK    0x0700
#define SGTL5000_LVLADJL_SHIFT    0x8
#define SGTL5000_LVLADJC_CLR_MASK    0xFF8F
#define SGTL5000_LVLADJC_GET_MASK    0x0070
#define SGTL5000_LVLADJC_SHIFT    0x4
#define SGTL5000_LR_SHORT_MOD_CLR_MASK    0xFFF3
#define SGTL5000_LR_SHORT_MOD_GET_MASK    0x000C
#define SGTL5000_LR_SHORT_MOD_SHIFT    0x2
#define SGTL5000_CM_SHORT_MOD_CLR_MASK    0xFFFC
#define SGTL5000_CM_SHORT_MOD_GET_MASK    0x0003
#define SGTL5000_CM_SHORT_MOD_SHIFT    0x0

/* DAP control register */
#define    DAP_CONTROL_MIX_EN_GET_MASK    0x0010
#define    DAP_CONTROL_MIX_EN_CLR_MASK    0xFFEF
#define    DAP_CONTROL_MIX_EN_SHIFT    0x4
#define    DAP_CONTROL_DAP_EN_GET_MASK    0x0001
#define    DAP_CONTROL_DAP_EN_CLR_MASK    0xFFFE
#define    DAP_CONTROL_DAP_EN_SHIFT    0x0

/*
* DAP_PEQ_REG
*/
#define    DAP_PEQ_EN_GET_MASK    0x0007
#define    DAP_PEQ_EN_CLR_MASK    0xFFF8
#define    DAP_PEQ_EN_SHIFT    0x0

/*
* DAP_BASS_ENHANCE_REG
*/
#define    DAP_BASS_ENHANCE_MULT_GET_MASK    0xC000
#define    DAP_BASS_ENHANCE_MULT_CLR_MASK    0x3FFF
#define    DAP_BASS_ENHANCE_MULT_SHIFT    0xE
#define    DAP_BASS_ENHANCE_CUTOFF_HPF_GET_MASK    0x0E00
#define    DAP_BASS_ENHANCE_CUTOFF_HPF_CLR_MASK    0xF1FF
#define    DAP_BASS_ENHANCE_CUTOFF_HPF_SHIFT    0x9
#define    DAP_BASS_ENHANCE_BYPASS_HPF_GET_MASK    0x0100
#define    DAP_BASS_ENHANCE_BYPASS_HPF_CLR_MASK    0xFEFF
#define    DAP_BASS_ENHANCE_BYPASS_HPF_SHIFT    0x8
#define    DAP_BASS_ENHANCE_CUTOFF_GET_MASK    0x0070
#define    DAP_BASS_ENHANCE_CUTOFF_CLR_MASK    0xFF8F
#define    DAP_BASS_ENHANCE_CUTOFF_SHIFT    0x4
#define    DAP_BASS_ENHANCE_EN_GET_MASK     0x0001
#define    DAP_BASS_ENHANCE_EN_CLR_MASK    0xFFFE
#define    DAP_BASS_ENHANCE_EN_SHIFT     0x0

/*
* DAP_BASS_ENHANCE_CTRL_REG
*/
#define    DAP_BASS_ENHANCE_CTRL_LR_LEVEL_GET_MASK    0x3F00
#define    DAP_BASS_ENHANCE_CTRL_LR_LEVEL_CLR_MASK    0xC0FF
#define    DAP_BASS_ENHANCE_CTRL_LR_LEVEL_SHIFT    0x8
#define    DAP_BASS_ENHANCE_CTRL_BASS_LEVEL_GET_MASK    0x007F
#define    DAP_BASS_ENHANCE_CTRL_BASS_LEVEL_CLR_MASK    0xFF80
#define    DAP_BASS_ENHANCE_CTRL_BASS_LEVEL_SHIFT    0x0

/*
* DAP_AUDIO_EQ_REG
*/
#define    DAP_AUDIO_EQ_EN_GET_MASK     0x0003
#define    DAP_AUDIO_EQ_EN_CLR_MASK    0xFFFC
#define    DAP_AUDIO_EQ_EN_SHIFT    0x0

/*
* DAP_SGTL_SURROUND_REG
*/
#define    DAP_SGTL_SURROUND_WIDTH_CONTROL_GET_MASK     0x0070
#define    DAP_SGTL_SURROUND_WIDTH_CONTROL_CLR_MASK    0xFF8F
#define    DAP_SGTL_SURROUND_WIDTH_CONTROL_SHIFT    0x4
#define    DAP_SGTL_SURROUND_SEL_GET_MASK    0x0003
#define    DAP_SGTL_SURROUND_SEL_CLR_MASK     0xFFFC
#define    DAP_SGTL_SURROUND_SEL_SHIFT    0x0

/*
* DAP_FILTER_COEF_ACCESS_REG
*/
#define    DAP_FILTER_COEF_ACCESS_DEBUG_GET_MASK    0x1000
#define    DAP_FILTER_COEF_ACCESS_DEBUG_CLR_MASK    0xEFFF
#define    DAP_FILTER_COEF_ACCESS_DEBUG_SHIFT    0xC
#define    DAP_FILTER_COEF_ACCESS_RD_GET_MASK    0x0200
#define    DAP_FILTER_COEF_ACCESS_RD_CLR_MASK    0xFDFF
#define    DAP_FILTER_COEF_ACCESS_RD_SHIFT    0x9
#define    DAP_FILTER_COEF_ACCESS_WR_GET_MASK    0x0100
#define    DAP_FILTER_COEF_ACCESS_WR_CLR_MASK    0xFEFF
#define    DAP_FILTER_COEF_ACCESS_WR_SHIFT    0x8
#define    DAP_FILTER_COEF_ACCESS_INDEX_GET_MASK    0x00FF
#define    DAP_FILTER_COEF_ACCESS_INDEX_CLR_MASK    0xFF00
#define    DAP_FILTER_COEF_ACCESS_INDEX_SHIFT    0x0

/*
*  DAP_COEF_WR_B0_MSB_REG
*/
#define    DAP_COEF_WR_B0_MSB_BIT_19_GET_MASK    0x8000
#define    DAP_COEF_WR_B0_MSB_BIT_19_CLR_MASK    0x7FFF
#define    DAP_COEF_WR_B0_MSB_BIT_19_SHIFT    0xF
#define    DAP_COEF_WR_B0_MSB_BIT_18_GET_MASK    0x4000
#define    DAP_COEF_WR_B0_MSB_BIT_18_CLR_MASK     0xBFFF
#define    DAP_COEF_WR_B0_MSB_BIT_18_SHIFT    0xE
#define    DAP_COEF_WR_B0_MSB_BIT_17_GET_MASK    0x2000
#define    DAP_COEF_WR_B0_MSB_BIT_17_CLR_MASK     0xDFFF
#define    DAP_COEF_WR_B0_MSB_BIT_17_SHIFT    0xD
#define    DAP_COEF_WR_B0_MSB_BIT_16_GET_MASK    0x1000
#define    DAP_COEF_WR_B0_MSB_BIT_16_CLR_MASK     0xEFFF
#define    DAP_COEF_WR_B0_MSB_BIT_16_SHIFT    0xC
#define    DAP_COEF_WR_B0_MSB_BIT_15_GET_MASK    0x0800
#define    DAP_COEF_WR_B0_MSB_BIT_15_CLR_MASK    0xF7FF
#define    DAP_COEF_WR_B0_MSB_BIT_15_SHIFT    0xB
#define    DAP_COEF_WR_B0_MSB_BIT_14_GET_MASK     0x0400
#define    DAP_COEF_WR_B0_MSB_BIT_14_CLR_MASK    0xFBFF
#define    DAP_COEF_WR_B0_MSB_BIT_14_SHIFT    0xA
#define    DAP_COEF_WR_B0_MSB_BIT_13_GET_MASK    0x0200
#define    DAP_COEF_WR_B0_MSB_BIT_13_CLR_MASK    0xFDFF
#define    DAP_COEF_WR_B0_MSB_BIT_13_SHIFT    0x9
#define    DAP_COEF_WR_B0_MSB_BIT_12_GET_MASK    0x0100
#define    DAP_COEF_WR_B0_MSB_BIT_12_CLR_MASK    0xFEFF
#define    DAP_COEF_WR_B0_MSB_BIT_12_SHIFT    0x8
#define    DAP_COEF_WR_B0_MSB_BIT_11_GET_MASK    0x0080
#define    DAP_COEF_WR_B0_MSB_BIT_11_CLR_MASK    0xFF7F
#define    DAP_COEF_WR_B0_MSB_BIT_11_SHIFT    0x7
#define    DAP_COEF_WR_B0_MSB_BIT_10_GET_MASK    0x0040
#define    DAP_COEF_WR_B0_MSB_BIT_10_CLR_MASK    0xFFBF
#define    DAP_COEF_WR_B0_MSB_BIT_10_SHIFT    0x6
#define    DAP_COEF_WR_B0_MSB_BIT_9_GET_MASK    0x0020
#define    DAP_COEF_WR_B0_MSB_BIT_9_CLR_MASK    0xFFDF
#define    DAP_COEF_WR_B0_MSB_BIT_9_SHIFT    0x5
#define    DAP_COEF_WR_B0_MSB_BIT_8_GET_MASK    0x0010
#define    DAP_COEF_WR_B0_MSB_BIT_8_CLR_MASK    0xFFEF
#define    DAP_COEF_WR_B0_MSB_BIT_8_SHIFT    0x4
#define    DAP_COEF_WR_B0_MSB_BIT_7_GET_MASK    0x0008
#define    DAP_COEF_WR_B0_MSB_BIT_7_CLR_MASK    0xFFF7
#define    DAP_COEF_WR_B0_MSB_BIT_7_SHIFT    0x3
#define    DAP_COEF_WR_B0_MSB_BIT_6_GET_MASK    0x0004
#define    DAP_COEF_WR_B0_MSB_BIT_6_CLR_MASK    0xFFFB
#define    DAP_COEF_WR_B0_MSB_BIT_6_SHIFT    0x2
#define    DAP_COEF_WR_B0_MSB_BIT_5_GET_MASK    0x0002
#define    DAP_COEF_WR_B0_MSB_BIT_5_CLR_MASK    0xFFFD
#define    DAP_COEF_WR_B0_MSB_BIT_5_SHIFT    0x1
#define    DAP_COEF_WR_B0_MSB_BIT_4_GET_MASK    0x0001
#define    DAP_COEF_WR_B0_MSB_BIT_4_CLR_MASK    0xFFFE
#define    DAP_COEF_WR_B0_MSB_BIT_4_SHIFT    0x0

/*
* DAP_COEF_WR_B0_LSB_REG
*/
#define    DAP_COEF_WR_B0_LSB_BIT_3_GET_MASK    0x0008
#define    DAP_COEF_WR_B0_LSB_BIT_3_CLR_MASK    0xFFF7
#define    DAP_COEF_WR_B0_LSB_BIT_3_SHIFT    0x3
#define    DAP_COEF_WR_B0_LSB_BIT_2_GET_MASK    0x0004
#define    DAP_COEF_WR_B0_LSB_BIT_2_CLR_MASK    0xFFFB
#define    DAP_COEF_WR_B0_LSB_BIT_2_SHIFT    0x2
#define    DAP_COEF_WR_B0_LSB_BIT_1_GET_MASK    0x0002
#define    DAP_COEF_WR_B0_LSB_BIT_1_CLR_MASK    0xFFFD
#define    DAP_COEF_WR_B0_LSB_BIT_1_SHIFT    0x1
#define    DAP_COEF_WR_B0_LSB_BIT_0_GET_MASK    0x0001
#define    DAP_COEF_WR_B0_LSB_BIT_0_CLR_MASK    0xFFFE
#define    DAP_COEF_WR_B0_LSB_BIT_0_SHIFT    0x0

/*
* DAP_AUDIO_EQ_BASS_BAND0_REG
*/
#define    DAP_AUDIO_EQ_BASS_BAND0_VOLUME_GET_MASK      0x007F
#define    DAP_AUDIO_EQ_BASS_BAND0_VOLUME_CLR_MASK    0xFF80
#define    DAP_AUDIO_EQ_BASS_BAND0_VOLUME_SHIFT     0x0

/*
* DAP_AUDIO_EQ_BAND1_REG
*/
#define    DAP_AUDIO_EQ_BAND1_VOLUME_GET_MASK    0x007F
#define    DAP_AUDIO_EQ_BAND1_VOLUME_CLR_MASK    0xFF80
#define    DAP_AUDIO_EQ_BAND1_VOLUME_SHIFT    0x0

/*
* DAP_AUDIO_EQ_BAND2_REG
*/
#define    DAP_AUDIO_EQ_BAND2_VOLUME_GET_MASK    0x007F
#define    DAP_AUDIO_EQ_BAND2_VOLUME_CLR_MASK    0xFF80
#define    DAP_AUDIO_EQ_BAND2_VOLUME_SHIFT    0x0

/*
* DAP_AUDIO_EQ_BAND3_REG
*/
#define    DAP_AUDIO_EQ_BAND3_VOLUME_GET_MASK    0x007F
#define    DAP_AUDIO_EQ_BAND3_VOLUME_CLR_MASK    0xFF80
#define    DAP_AUDIO_EQ_BAND3_VOLUME_SHIFT    0x0

/*
* DAP_AUDIO_EQ_TREBLE_BAND4_REG
*/
#define    DAP_AUDIO_EQ_TREBLE_BAND4_VOLUME_GET_MASK    0x007F
#define    DAP_AUDIO_EQ_TREBLE_BAND4_VOLUME_CLR_MASK    0xFF80
#define    DAP_AUDIO_EQ_TREBLE_BAND4_VOLUME_SHIFT    0x0

/*
* DAP_MAIN_CHAN_REG
*/
#define    DAP_MAIN_CHAN_VOL_GET_MASK    0xFFFF
#define    DAP_MAIN_CHAN_VOL_CLR_MASK    0x0000
#define    DAP_MAIN_CHAN_VOL_SHIFT    0x0

/*
* DAP_MIX_CHAN_REG
*/
#define    DAP_MIX_CHAN_VOL_GET_MASK    0xFFFF
#define    DAP_MIX_CHAN_VOL_CLR_MASK    0x0000
#define    DAP_MIX_CHAN_VOL_SHIFT    0x0

/*
* DAP_AVC_CTRL_REG
*/
#define    DAP_AVC_CTRL_APOP_ENABLE_GET_MASK    0x4000
#define    DAP_AVC_CTRL_APOP_ENABLE_CLR_MASK    0xBFFF
#define    DAP_AVC_CTRL_APOP_ENABLE_SHIFT    0xE
#define    DAP_AVC_CTRL_MAX_GAIN_GET_MASK    0x3000
#define    DAP_AVC_CTRL_MAX_GAIN_CLR_MASK    0xCFFF
#define    DAP_AVC_CTRL_MAX_GAIN_SHIFT    0xC
#define    DAP_AVC_CTRL_LBI_RESPONSE_GET_MASK    0x0300
#define    DAP_AVC_CTRL_LBI_RESPONSE_CLR_MASK    0xFCFF
#define    DAP_AVC_CTRL_LBI_RESPONSE_SHIFT    0x8
#define    DAP_AVC_CTRL_HARD_LIMIT_EN_GET_MASK    0x0020
#define    DAP_AVC_CTRL_HARD_LIMIT_EN_CLR_MASK    0xFFDF
#define    DAP_AVC_CTRL_HARD_LIMIT_EN_SHIFT    0x5
#define    DAP_AVC_CTRL_STOP_GET_MASK    0x0004
#define    DAP_AVC_CTRL_STOP_SHIFT    0x2
#define    DAP_AVC_CTRL_RUNNING_GET_MASK    0x0002
#define    DAP_AVC_CTRL_RUNNING_SHIFT    0x1
#define    DAP_AVC_CTRL_EN_GET_MASK    0x0001
#define    DAP_AVC_CTRL_EN_CLR_MASK    0xFFFE
#define    DAP_AVC_CTRL_EN_SHIFT    0x0

/*
* DAP_AVC_ATTACK_REG
*/
#define    DAP_AVC_ATTACK_RATE_GET_MASK    0x0FFF
#define    DAP_AVC_ATTACK_RATE_CLR_MASK    0xF000
#define    DAP_AVC_ATTACK_RATE_SHIFT    0x0

/*
* DAP_AVC_DECAY_REG
*/
#define    DAP_AVC_DECAY_RATE_GET_MASK    0x0FFF
#define    DAP_AVC_DECAY_RATE_CLR_MASK    0xF000
#define    DAP_AVC_DECAY_RATE_SHIFT    0x0

/*
* DAP_COEF_WR_B1_LSB_REG
*/
#define    DAP_COEF_WR_B1_LSB_LSB_GET_MASK    0x000F
#define    DAP_COEF_WR_B1_LSB_LSB_CLR_MASK    0xFFF0
#define    DAP_COEF_WR_B1_LSB_LSB_SHIFT    0x0

/*
* DAP_COEF_WR_B2_LSB_REG
*/
#define    DAP_COEF_WR_B2_LSB_LSB_GET_MASK    0x000F
#define    DAP_COEF_WR_B2_LSB_LSB_CLR_MASK    0xFFF0
#define    DAP_COEF_WR_B2_LSB_LSB_SHIFT    0x0

/*
* DAP_COEF_WR_A1_LSB_REG
*/
#define    DAP_COEF_WR_A1_LSB_LSB_GET_MASK    0x000F
#define    DAP_COEF_WR_A1_LSB_LSB_CLR_MASK    0xFFF0
#define    DAP_COEF_WR_A1_LSB_LSB_SHIFT    0x0

/*
* DAP_COEF_WR_A2_LSB_REG
*/
#define    DAP_COEF_WR_A2_LSB_LSB_GET_MASK              0x000F
#define    DAP_COEF_WR_A2_LSB_LSB_CLR_MASK            0xFFF0
#define    DAP_COEF_WR_A2_LSB_LSB_SHIFT             0x0


/*! @brief SGTL5000 I2C address. */
#define SGTL5000_I2C_ADDR 0x0A

/*! @brief Sgtl5000 return status. */
typedef enum _sgtl5000_status
{
    kStatus_SGTL_Success = 0x0,
    kStatus_SGTL_I2CFail = 0x1,
    kStatus_SGTL_Fail = 0x2
} sgtl_status_t;

/*! @brief Modules in Sgtl5000 board. */
typedef enum _sgtl5000_module
{
    kSgtlModuleADC = 0x0,
    kSgtlModuleDAC = 0x1,
    kSgtlModuleDAP = 0x2,
    kSgtlModuleHP = 0x3,
    kSgtlModuleI2SIN = 0x4,
    kSgtlModuleI2SOUT = 0x5,
    kSgtlModuleLineIn = 0x6,
    kSgtlModuleLineOut = 0x7,
    kSgtlModuleMicin = 0x8
} sgtl_module_t;

/*! 
* @brief Sgtl5000 data route.
* Only provide some typical data route, not all route listed.
* Note: Users cannot combine any routes, once a new route is set, the precios one would be replaced.
*/
typedef enum _sgtl_route
{
    kSgtlRouteBypass = 0x0, /*!< LINEIN->Headphone. */
    kSgtlRoutePlayback = 0x1, /*!<  I2SIN->DAC->Headphone. */
    kSgtlRoutePlaybackandRecord = 0x2, /*!< I2SIN->DAC->Headphone, LINEIN->ADC->I2SOUT. */
    kSgtlRoutePlaybackwithDAP = 0x3, /*!< I2SIN->DAP->DAC->Headphone. */
    kSgtlRoutePlaybackwithDAPandRecord = 0x4, /*!< I2SIN->DAP->DAC->HP, LINEIN->ADC->I2SOUT. */
    kSgtlRouteRecord = 0x5/*!< LINEIN->ADC->I2SOUT. */
} sgtl_route_t;

/*! 
* @brief The audio data transfer protocol choice.
* Sgtl5000 only supports I2S format and PCM format.
*/
typedef enum _sgtl_protocol
{
    kSgtlBusI2S = 0x0,
    kSgtlBusI2SLeft = 0x1,
    kSgtlBusI2SRight = 0x2,
    kSgtlBusPCMA = 0x3,
    kSgtlBusPCMB = 0x4
} sgtl_protocol_t;

/*! @brief EQ type in DAP, only one EQ can be used at the same time. */
typedef enum _sgtl_EQ_type
{
    kSgtlEQType7band,
    kSgtlEQtype5band,
    kSgtlEQtypeVolumeControl
} sgtl_EQtype_t;

/*! @brief sgtl configure definition. */
typedef struct sgtl_handler
{
    /* I2C revelant definition. */
    uint32_t i2c_instance; /*!< I2C instance. */
    i2c_device_t device; /*!< I2C device setting */
    i2c_master_state_t state; /*!< I2C intenal state space. */
} sgtl_handler_t;

/*! @brief Initailize structure of sgtl5000 */
typedef struct sgtl_init
{
    sgtl_route_t route; /*!< Audio data route.*/
    sgtl_protocol_t bus; /*!< Audio transfer protocol */
    bool master_slave; /*!< Master or slave. */
} sgtl_init_t;

/*******************************************************************************
 * API
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif

/*!
 * @brief sgtl5000 initialize function.
 *
 * This function would call sgtl_i2c_init(), and in this function, some configurations
 * are fixed. The second parameter is NULL to sgtl5000 in this version. If users want
 * to change the settings, they have to use sgtl_write_reg() or sgtl_modify_reg()
 * to set the register value of sgtl5000.
 * Note: If the codec_config is NULL, it would initialize sgtl5000 using default settings.
 * The default setting:
 * codec_config->route = kSgtlRoutePlaybackandRecord
 * codec_config->bus = kSgtlBusI2S
 * codec_config->master = slave
 * @param handler Sgtl5000 handler structure.
 * @param codec_config sgtl5000 configuration structure.
 */
sgtl_status_t SGTL_Init(sgtl_handler_t *handler, sgtl_init_t *codec_config);

/*!
 * @brief Set audio data route in sgtl5000.
 *
 * This function would set the data route according to route. The route cannot be combined,
 * as all route would enable different modules.
 * Note: If a new route is set, the previous route would not work.
 * @param handler Sgtl5000 handler structure.
 * @param route Audio data route in sgtl5000.
 */
sgtl_status_t SGTL_SetDataRoute(sgtl_handler_t *handler, sgtl_route_t route);

/*! 
 * @brief Set the audio transfer protocol.
 *
 * Sgtl5000 only supports I2S, I2S left, I2S right, PCM A, PCM B format.
 * @param handler Sgtl5000 handler structure.
 * @param bus Audio data transfer protocol.
 */
sgtl_status_t SGTL_SetProtocol(sgtl_handler_t *handler, sgtl_protocol_t protocol);

/*!
 * @brief Set sgtl5000 as master or slave.
 *
 * @param handler Sgtl5000 handler structure.
 * @param master 1 represent master, 0 represent slave.
 */
sgtl_status_t SGTL_SetMasterSlave(sgtl_handler_t *handler, bool master);
/*!
 * @brief Configure PLL to get the expected MCLK and frame sync.
 *
 * While sglt5000 as master, PLL should be used.
 * @param handler Sgtl5000 handler structure.
 * @param mclk MCLK frequency expected to get.
 * @param fs Frame sync value expected to get, equals to sample rate.
 */
sgtl_status_t SGTL_SetPLL(sgtl_handler_t *handler, uint32_t mclk, uint32_t fs);

/*!
 * @brief Set the volume of different modules in sgtl5000.
 *
 * This function would set the volume of sgtl5000 modules. Uses need to appoint the module.
 * The function assume that left channel and right channel has the same volume.
 * @param handler Sgtl5000 handler structure.
 * @param module Module to set volume, it can be ADC, DAC, Headphone and so on.
 * @param volume Volume value need to be set.
 */
sgtl_status_t SGTL_SetVolume(sgtl_handler_t *handler, sgtl_module_t module, uint32_t volume);

/*!
 * @brief Get the volume of different modules in sgtl5000.
 *
 * This function gets the volume of sgtl5000 modules. Uses need to appoint the module.
 * The function assume that left channel and right channel has the same volume.
 * @param handler Sgtl5000 handler structure.
 * @param module Module to set volume, it can be ADC, DAC, Headphone and so on.
 * @return Volume value of the module.
 */
uint32_t SGTL_GetVolume(sgtl_handler_t *handler, sgtl_module_t module);

/*!
 * @brief Mute modules in sgtl5000.
 *
 * @param handler Sgtl5000 handler structure.
 * @param module Modules need to be mute.
 * @param isEnabled Mute or unmute, 1 represent mute.
 */
sgtl_status_t SGTL_SetMuteCmd(sgtl_handler_t *handler, sgtl_module_t module, bool isEnabled);

/*!
 * @brief Enable/disable expected devices.
 * @param handler Sgtl5000 handler structure.
 * @param module Module expected to enable.
 * @param isEnabled Enable or disable moudles.
 */
sgtl_status_t SGTL_SetModuleCmd(sgtl_handler_t *handler, sgtl_module_t module, bool isEnabled);

/*!
 * @brief Initialize the I2C module in sgtl.
 *
 * Sgtl now uses i2c to write/read the registers in it.
 * @param handler Sgtl5000 handler structure.
 */
sgtl_status_t SGTL_I2CInit(sgtl_handler_t *handler);

/*!
 * @brief Deinit the sgtl5000 codec. Mainly used to close the I2C controller.
 * @param handler Sgtl5000 handler structure pointer.
 */
sgtl_status_t SGTL_Deinit(sgtl_handler_t *handler);

/*!
 * @brief Configure the data format of audio data.
 *
 * This function would configure the registers about the sample rate, bit depths.
 * @param handler Sgtl5000 handler structure pointer.
 * @param mclk Master clock frequency of I2S.
 * @param sample_rate Sample rate of audio file running in sgtl5000. Sgtl5000 now
 * supports 8k, 11.025k, 12k, 16k, 22.05k, 24k, 32k, 44.1k, 48k and 96k sample rate.
 * @param bits Bit depth of audio file (Sgtl5000 only supports 16bit, 20bit, 24bit
 * and 32 bit in HW).
 */
sgtl_status_t SGTL_ConfigDataFormat(sgtl_handler_t *handler, uint32_t mclk, uint32_t sample_rate, uint8_t bits);
 
/*!
 * @brief Write register to sgtl using I2C.
 * @param handler Sgtl5000 handler structure.
 * @param reg The register address in sgtl.
 * @param val Value needs to write into the register.
 */
sgtl_status_t SGTL_WriteReg(sgtl_handler_t *handler, uint16_t reg, uint16_t val);

/*!
 * @brief Read register from sgtl using I2C.
 * @param handler Sgtl5000 handler structure.
 * @param reg The register address in sgtl.
 * @param val Value written to.
 */
sgtl_status_t SGTL_ReadReg(sgtl_handler_t * handler, uint16_t reg, uint16_t *val);

/*!
 * @brief Modify some bits in the register using I2C.
 * @param handler Sgtl5000 handler structure.
 * @param reg The register address in sgtl.
 * @param mask The mask code for the bits want to write. The bit you want to write should be 0.
 * @param val Value needs to write into the register.
 */
sgtl_status_t SGTL_ModifyReg(sgtl_handler_t * handler, uint16_t reg,  uint16_t clr_mask, uint16_t val);

/*!
 * @brief Set the volume of DAC modules in sgtl5000.
 *
 * This function would set the volume of sgtl5000 DAC.
 * The function assume that left channel and right channel has the same volume.
 * @param handler Sgtl5000 handler structure.
 * @param volume Volume value need to be set.
 */
static inline sgtl_status_t SGTL_SetDACVoulme(sgtl_handler_t * handler, uint32_t volume) 
{
    return SGTL_SetVolume(handler, kSgtlModuleDAC, volume);
}

/*!
 * @brief Get the volume of DAC modules in sgtl5000.
 *
 * This function gets the volume of sgtl5000 modules.
 * The function assume that left channel and right channel has the same volume.
 * @param handler Sgtl5000 handler structure.
 * @return Volume value of the module.
 */
static inline uint32_t SGTL_GetDACVolume(sgtl_handler_t * handler) 
{
    return SGTL_GetVolume(handler,kSgtlModuleDAC);
}

/*!
 * @brief Mute DAC in sgtl5000.
 *
 * @param handler Sgtl5000 handler structure.
 * @param isEnabled Mute or unmute, true represent mute.
 */
static inline sgtl_status_t SGTL_SetDACMute(sgtl_handler_t * handler, bool enable)   
{
    return SGTL_SetMuteCmd(handler,kSgtlModuleDAC, enable);
}

#if defined(__cplusplus)
}
#endif

/*! @} */

#endif/* __FSL_SGTL_5000_DRIVER_H__ */

/*******************************************************************************
 * API
 ******************************************************************************/

