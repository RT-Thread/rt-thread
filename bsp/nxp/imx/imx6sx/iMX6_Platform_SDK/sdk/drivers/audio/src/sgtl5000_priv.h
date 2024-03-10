/*
 * Copyright (c) 2011-2012, Freescale Semiconductor, Inc.
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

/*!
 * @file sgtl5000_priv.h
 * @brief Header file for the SGTL5000.
 *
 * @ingroup diag_audio
 */

#ifndef ___SGTL5000_REGMAP_H___
#define ___SGTL5000_REGMAP_H___

//###############################################################
// REGISTER INTERFACE
//###############################################################
#define CHIP_DIG_ID_REG							0x0000
//-------------------------------------------------------------
// CHIP_DIG_POWER_REG
//-------------------------------------------------------------
#define	CHIP_DIG_POWER_REG                      			0x0002

// Bit-Field Access
#define	CHIP_DIG_POWER_DISABLE_LOGIC_CLK_GATING_GETMASK	0x0100
#define	CHIP_DIG_POWER_DISABLE_LOGIC_CLK_GATING_CLEARMASK	0xFEFF
#define	CHIP_DIG_POWER_DISABLE_LOGIC_CLK_GATING_STARTBIT	0x8

#define	CHIP_DIG_POWER_PWM_POWERUP_GETMASK      	0x0080
#define	CHIP_DIG_POWER_PWM_POWERUP_CLEARMASK    	0xFF7F
#define	CHIP_DIG_POWER_PWM_POWERUP_STARTBIT     	0x7

#define	CHIP_DIG_POWER_ADC_POWERUP_GETMASK      	0x0040
#define	CHIP_DIG_POWER_ADC_POWERUP_CLEARMASK    	0xFFBF
#define	CHIP_DIG_POWER_ADC_POWERUP_STARTBIT     	0x6

#define	CHIP_DIG_POWER_DAC_POWERUP_GETMASK      	0x0020
#define	CHIP_DIG_POWER_DAC_POWERUP_CLEARMASK    	0xFFDF
#define	CHIP_DIG_POWER_DAC_POWERUP_STARTBIT     	0x5

#define	CHIP_DIG_POWER_DAP_POWERUP_GETMASK      	0x0010
#define	CHIP_DIG_POWER_DAP_POWERUP_CLEARMASK    	0xFFEF
#define	CHIP_DIG_POWER_DAP_POWERUP_STARTBIT     	0x4

#define	CHIP_DIG_POWER_I2S0_OUT_POWERUP_GETMASK 	0x0002
#define	CHIP_DIG_POWER_I2S0_OUT_POWERUP_CLEARMASK	0xFFFD
#define	CHIP_DIG_POWER_I2S0_OUT_POWERUP_STARTBIT	0x1

#define	CHIP_DIG_POWER_I2S0_IN_POWERUP_GETMASK  	0x0001
#define	CHIP_DIG_POWER_I2S0_IN_POWERUP_CLEARMASK	0xFFFE
#define	CHIP_DIG_POWER_I2S0_IN_POWERUP_STARTBIT 	0x0

//-------------------------------------------------------------
// CHIP_CLK_CTRL_REG
//-------------------------------------------------------------
#define	CHIP_CLK_CTRL_REG                       			0x0004

// Bit-Field Access
#define	CHIP_CLK_CTRL_SYS_FS_GETMASK            	0x000C
#define	CHIP_CLK_CTRL_SYS_FS_CLEARMASK          	0xFFF3
#define	CHIP_CLK_CTRL_SYS_FS_STARTBIT           	0x2

#define	CHIP_CLK_CTRL_MCLK_FREQ_GETMASK         	0x0003
#define	CHIP_CLK_CTRL_MCLK_FREQ_CLEARMASK       	0xFFFC
#define	CHIP_CLK_CTRL_MCLK_FREQ_STARTBIT        	0x0

//-------------------------------------------------------------
// CHIP_I2S0_CTRL_REG
//-------------------------------------------------------------
#define	CHIP_I2S0_CTRL_REG                      			0x0006

//-------------------------------------------------------------
// CHIP_SSS_CTRL_REG
//-------------------------------------------------------------
#define	CHIP_SSS_CTRL_REG                       			0x000A

//-------------------------------------------------------------
// CHIP_ADCDAC_CTRL_REG
//-------------------------------------------------------------
#define	CHIP_ADCDAC_CTRL_REG                    			0x000E

// Bit-Field Access
#define	CHIP_ADCDAC_CTRL_DAC_MUTE_RIGHT_GETMASK 	0x0008
#define	CHIP_ADCDAC_CTRL_DAC_MUTE_RIGHT_CLEARMASK	0xFFF7
#define	CHIP_ADCDAC_CTRL_DAC_MUTE_RIGHT_STARTBIT	0x3

#define	CHIP_ADCDAC_CTRL_DAC_MUTE_LEFT_GETMASK  	0x0004
#define	CHIP_ADCDAC_CTRL_DAC_MUTE_LEFT_CLEARMASK	0xFFFB
#define	CHIP_ADCDAC_CTRL_DAC_MUTE_LEFT_STARTBIT 	0x2

//-------------------------------------------------------------
// CHIP_DAC_VOL_REG
//-------------------------------------------------------------
#define	CHIP_DAC_VOL_REG                        			0x0010

// Bit-Field Access
#define	CHIP_DAC_VOL_DAC_VOL_RIGHT_GETMASK      	0xFF00
#define	CHIP_DAC_VOL_DAC_VOL_RIGHT_CLEARMASK    	0x00FF
#define	CHIP_DAC_VOL_DAC_VOL_RIGHT_STARTBIT     	0x8

#define	CHIP_DAC_VOL_DAC_VOL_LEFT_GETMASK       	0x00FF
#define	CHIP_DAC_VOL_DAC_VOL_LEFT_CLEARMASK     	0xFF00
#define	CHIP_DAC_VOL_DAC_VOL_LEFT_STARTBIT      	0x0

//-------------------------------------------------------------
// CHIP_ANA_ADC_CTRL_REG
//-------------------------------------------------------------
#define	CHIP_ANA_ADC_CTRL_REG                   			0x0020

// Bit-Field Access
#define	CHIP_ANA_ADC_CTRL_ADC_VOL_M6DB_GETMASK  	0x0100
#define	CHIP_ANA_ADC_CTRL_ADC_VOL_M6DB_CLEARMASK	0xFEFF
#define	CHIP_ANA_ADC_CTRL_ADC_VOL_M6DB_STARTBIT 	0x8

#define	CHIP_ANA_ADC_CTRL_ADC_VOL_RIGHT_GETMASK 	0x00F0
#define	CHIP_ANA_ADC_CTRL_ADC_VOL_RIGHT_CLEARMASK	0xFF0F
#define	CHIP_ANA_ADC_CTRL_ADC_VOL_RIGHT_STARTBIT	0x4

#define	CHIP_ANA_ADC_CTRL_ADC_VOL_LEFT_GETMASK  	0x000F
#define	CHIP_ANA_ADC_CTRL_ADC_VOL_LEFT_CLEARMASK	0xFFF0
#define	CHIP_ANA_ADC_CTRL_ADC_VOL_LEFT_STARTBIT 	0x0

//-------------------------------------------------------------
// CHIP_ANA_HP_CTRL_REG
//-------------------------------------------------------------
#define	CHIP_ANA_HP_CTRL_REG                    			0x0022

// Bit-Field Access
#define	CHIP_ANA_HP_CTRL_HP_VOL_RIGHT_GETMASK   	0x7F00
#define	CHIP_ANA_HP_CTRL_HP_VOL_RIGHT_CLEARMASK 	0x80FF
#define	CHIP_ANA_HP_CTRL_HP_VOL_RIGHT_STARTBIT  	0x8

#define	CHIP_ANA_HP_CTRL_HP_VOL_LEFT_GETMASK    	0x007F
#define	CHIP_ANA_HP_CTRL_HP_VOL_LEFT_CLEARMASK  	0xFF80
#define	CHIP_ANA_HP_CTRL_HP_VOL_LEFT_STARTBIT   	0x0

//-------------------------------------------------------------
// CHIP_ANA_CTRL_REG
//-------------------------------------------------------------
#define	CHIP_ANA_CTRL_REG                       			0x0024

// Bit-Field Access
#define	CHIP_ANA_CTRL_MUTE_LO_GETMASK           	0x0100
#define	CHIP_ANA_CTRL_MUTE_LO_CLEARMASK         	0xFEFF
#define	CHIP_ANA_CTRL_MUTE_LO_STARTBIT          	0x8

#define	CHIP_ANA_CTRL_SELECT_HP_GETMASK         	0x0040
#define	CHIP_ANA_CTRL_SELECT_HP_CLEARMASK       	0xFFBF
#define	CHIP_ANA_CTRL_SELECT_HP_STARTBIT        	0x6

#define	CHIP_ANA_CTRL_EN_ZCD_HP_GETMASK         	0x0020
#define	CHIP_ANA_CTRL_EN_ZCD_HP_CLEARMASK       	0xFFDF
#define	CHIP_ANA_CTRL_EN_ZCD_HP_STARTBIT        	0x5

#define	CHIP_ANA_CTRL_MUTE_HP_GETMASK           	0x0010
#define	CHIP_ANA_CTRL_MUTE_HP_CLEARMASK         	0xFFEF
#define	CHIP_ANA_CTRL_MUTE_HP_STARTBIT          	0x4

#define	CHIP_ANA_CTRL_SELECT_ADC_GETMASK        	0x0004
#define	CHIP_ANA_CTRL_SELECT_ADC_CLEARMASK      	0xFFFB
#define	CHIP_ANA_CTRL_SELECT_ADC_STARTBIT       	0x2

#define	CHIP_ANA_CTRL_EN_ZCD_ADC_GETMASK        	0x0002
#define	CHIP_ANA_CTRL_EN_ZCD_ADC_CLEARMASK      	0xFFFD
#define	CHIP_ANA_CTRL_EN_ZCD_ADC_STARTBIT       	0x1

#define	CHIP_ANA_CTRL_MUTE_ADC_GETMASK          	0x0001
#define	CHIP_ANA_CTRL_MUTE_ADC_CLEARMASK        	0xFFFE
#define	CHIP_ANA_CTRL_MUTE_ADC_STARTBIT         	0x0

//-------------------------------------------------------------
// CHIP_LINREG_CTRL_REG
//-------------------------------------------------------------
#define	CHIP_LINREG_CTRL_REG                    			0x0026

//-------------------------------------------------------------
// CHIP_REF_CTRL_REG
//-------------------------------------------------------------
#define	CHIP_REF_CTRL_REG                       			0x0028

//-------------------------------------------------------------
// CHIP_MIC_CTRL_REG
//-------------------------------------------------------------
#define	CHIP_MIC_CTRL_REG                       			0x002A

//-------------------------------------------------------------
// CHIP_LINE_OUT_CTRL_REG
//-------------------------------------------------------------
#define	CHIP_LINE_OUT_CTRL_REG                  			0x002C

//-------------------------------------------------------------
// CHIP_LINE_OUT_VOL_REG
//-------------------------------------------------------------
#define	CHIP_LINE_OUT_VOL_REG                   			0x002E

//-------------------------------------------------------------
// CHIP_ANA_POWER_REG
//-------------------------------------------------------------
#define	CHIP_ANA_POWER_REG                      			0x0030

// Bit-Field Access
#define	CHIP_ANA_POWER_RIGHT_DAC_POWERUP_GETMASK	0x4000
#define	CHIP_ANA_POWER_RIGHT_DAC_POWERUP_CLEARMASK	0xBFFF
#define	CHIP_ANA_POWER_RIGHT_DAC_POWERUP_STARTBIT	0xE

#define	CHIP_ANA_POWER_LINREG_SIMPLE_POWERUP_GETMASK	0x2000
#define	CHIP_ANA_POWER_LINREG_SIMPLE_POWERUP_CLEARMASK	0xDFFF
#define	CHIP_ANA_POWER_LINREG_SIMPLE_POWERUP_STARTBIT	0xD

#define	CHIP_ANA_POWER_STARTUP_POWERUP_GETMASK  	0x1000
#define	CHIP_ANA_POWER_STARTUP_POWERUP_CLEARMASK	0xEFFF
#define	CHIP_ANA_POWER_STARTUP_POWERUP_STARTBIT 	0xC

#define	CHIP_ANA_POWER_VDDC_CHRGPMP_POWERUP_GETMASK	0x0800
#define	CHIP_ANA_POWER_VDDC_CHRGPMP_POWERUP_CLEARMASK	0xF7FF
#define	CHIP_ANA_POWER_VDDC_CHRGPMP_POWERUP_STARTBIT	0xB

#define	CHIP_ANA_POWER_PLL_POWERUP_GETMASK      	0x0400
#define	CHIP_ANA_POWER_PLL_POWERUP_CLEARMASK    	0xFBFF
#define	CHIP_ANA_POWER_PLL_POWERUP_STARTBIT     	0xA

#define	CHIP_ANA_POWER_LINREG_D_POWERUP_GETMASK 	0x0200
#define	CHIP_ANA_POWER_LINREG_D_POWERUP_CLEARMASK	0xFDFF
#define	CHIP_ANA_POWER_LINREG_D_POWERUP_STARTBIT	0x9

#define	CHIP_ANA_POWER_VCOAMP_POWERUP_GETMASK   	0x0100
#define	CHIP_ANA_POWER_VCOAMP_POWERUP_CLEARMASK 	0xFEFF
#define	CHIP_ANA_POWER_VCOAMP_POWERUP_STARTBIT  	0x8

#define	CHIP_ANA_POWER_VAG_POWERUP_GETMASK      	0x0080
#define	CHIP_ANA_POWER_VAG_POWERUP_CLEARMASK    	0xFF7F
#define	CHIP_ANA_POWER_VAG_POWERUP_STARTBIT     	0x7

#define	CHIP_ANA_POWER_RIGHT_ADC_POWERUP_GETMASK	0x0040
#define	CHIP_ANA_POWER_RIGHT_ADC_POWERUP_CLEARMASK	0xFFBF
#define	CHIP_ANA_POWER_RIGHT_ADC_POWERUP_STARTBIT	0x6

#define	CHIP_ANA_POWER_REFTOP_POWERUP_GETMASK   	0x0020
#define	CHIP_ANA_POWER_REFTOP_POWERUP_CLEARMASK 	0xFFDF
#define	CHIP_ANA_POWER_REFTOP_POWERUP_STARTBIT  	0x5

#define	CHIP_ANA_POWER_HEADPHONE_POWERUP_GETMASK	0x0010
#define	CHIP_ANA_POWER_HEADPHONE_POWERUP_CLEARMASK	0xFFEF
#define	CHIP_ANA_POWER_HEADPHONE_POWERUP_STARTBIT	0x4

#define	CHIP_ANA_POWER_DAC_POWERUP_GETMASK      	0x0008
#define	CHIP_ANA_POWER_DAC_POWERUP_CLEARMASK    	0xFFF7
#define	CHIP_ANA_POWER_DAC_POWERUP_STARTBIT     	0x3

#define	CHIP_ANA_POWER_CAPLESS_HEADPHONE_POWERUP_GETMASK	0x0004
#define	CHIP_ANA_POWER_CAPLESS_HEADPHONE_POWERUP_CLEARMASK	0xFFFB
#define	CHIP_ANA_POWER_CAPLESS_HEADPHONE_POWERUP_STARTBIT	0x2

#define	CHIP_ANA_POWER_ADC_POWERUP_GETMASK      	0x0002
#define	CHIP_ANA_POWER_ADC_POWERUP_CLEARMASK    	0xFFFD
#define	CHIP_ANA_POWER_ADC_POWERUP_STARTBIT     	0x1

#define	CHIP_ANA_POWER_LINEOUT_POWERUP_GETMASK  	0x0001
#define	CHIP_ANA_POWER_LINEOUT_POWERUP_CLEARMASK	0xFFFE
#define	CHIP_ANA_POWER_LINEOUT_POWERUP_STARTBIT 	0x0

//-------------------------------------------------------------
// CHIP_PLL_CTRL_REG
//-------------------------------------------------------------
#define	CHIP_PLL_CTRL_REG                       			0x0032

//-------------------------------------------------------------
// CHIP_CLK_TOP_CTRL_REG
//-------------------------------------------------------------
#define	CHIP_CLK_TOP_CTRL_REG                   			0x0034

// Bit-field access
#define	CHIP_CLK_TOP_CTRL_INPUT_FREQ_DIV2_GETMASK	0x0008
#define	CHIP_CLK_TOP_CTRL_INPUT_FREQ_DIV2_CLEARMASK	0xFFF7
#define	CHIP_CLK_TOP_CTRL_INPUT_FREQ_DIV2_STARTBIT	0x3

//-------------------------------------------------------------
// CHIP_ANA_STATUS_REG
//-------------------------------------------------------------
#define	CHIP_ANA_STATUS_REG                     			0x0036

//-------------------------------------------------------------
// CHIP_SHORT_CTRL_REG
//-------------------------------------------------------------
#define	CHIP_SHORT_CTRL_REG                     			0x003C

#endif /*___SGTL5000_REGMAP_H___*/

//###############################################################
// DIGITAL AUDIO PROCESSING (DAP)
//###############################################################

//-------------------------------------------------------------
// DAP_CONTROL_REG
//-------------------------------------------------------------
#define	DAP_CONTROL_REG                         			0x0100

// Bit-Field Access
#define	DAP_CONTROL_RSVD0_GETMASK               	0xFFE0
#define	DAP_CONTROL_RSVD0_STARTBIT              	0x5

#define	DAP_CONTROL_MIX_EN_GETMASK              	0x0010
#define	DAP_CONTROL_MIX_EN_CLEARMASK            	0xFFEF
#define	DAP_CONTROL_MIX_EN_STARTBIT             	0x4

#define	DAP_CONTROL_RSVD2_GETMASK               	0x000E
#define	DAP_CONTROL_RSVD2_STARTBIT              	0x1

#define	DAP_CONTROL_DAP_EN_GETMASK              	0x0001
#define	DAP_CONTROL_DAP_EN_CLEARMASK            	0xFFFE
#define	DAP_CONTROL_DAP_EN_STARTBIT             	0x0

//-------------------------------------------------------------
// DAP_PEQ_REG
//-------------------------------------------------------------
#define	DAP_PEQ_REG                             			0x0102

// Bit-Field Access
#define	DAP_PEQ_RSVD0_GETMASK                   	0xFFF8
#define	DAP_PEQ_RSVD0_STARTBIT                  	0x3

#define	DAP_PEQ_EN_GETMASK                      	0x0007
#define	DAP_PEQ_EN_CLEARMASK                    	0xFFF8
#define	DAP_PEQ_EN_STARTBIT                     	0x0

//-------------------------------------------------------------
// DAP_BASS_ENHANCE_REG
//-------------------------------------------------------------
#define	DAP_BASS_ENHANCE_REG                    			0x0104

// Bit-Field Access
#define	DAP_BASS_ENHANCE_MULT_GETMASK           	0xC000
#define	DAP_BASS_ENHANCE_MULT_CLEARMASK         	0x3FFF
#define	DAP_BASS_ENHANCE_MULT_STARTBIT          	0xE

#define	DAP_BASS_ENHANCE_RSVD1_GETMASK          	0x3000
#define	DAP_BASS_ENHANCE_RSVD1_STARTBIT         	0xC

#define	DAP_BASS_ENHANCE_CUTOFF_HPF_GETMASK     	0x0E00
#define	DAP_BASS_ENHANCE_CUTOFF_HPF_CLEARMASK   	0xF1FF
#define	DAP_BASS_ENHANCE_CUTOFF_HPF_STARTBIT    	0x9

#define	DAP_BASS_ENHANCE_BYPASS_HPF_GETMASK     	0x0100
#define	DAP_BASS_ENHANCE_BYPASS_HPF_CLEARMASK   	0xFEFF
#define	DAP_BASS_ENHANCE_BYPASS_HPF_STARTBIT    	0x8

#define	DAP_BASS_ENHANCE_RSVD4_GETMASK          	0x0080
#define	DAP_BASS_ENHANCE_RSVD4_STARTBIT         	0x7

#define	DAP_BASS_ENHANCE_CUTOFF_GETMASK         	0x0070
#define	DAP_BASS_ENHANCE_CUTOFF_CLEARMASK       	0xFF8F
#define	DAP_BASS_ENHANCE_CUTOFF_STARTBIT        	0x4

#define	DAP_BASS_ENHANCE_RSVD6_GETMASK          	0x000E
#define	DAP_BASS_ENHANCE_RSVD6_STARTBIT         	0x1

#define	DAP_BASS_ENHANCE_EN_GETMASK             	0x0001
#define	DAP_BASS_ENHANCE_EN_CLEARMASK           	0xFFFE
#define	DAP_BASS_ENHANCE_EN_STARTBIT            	0x0

//-------------------------------------------------------------
// DAP_BASS_ENHANCE_CTRL_REG
//-------------------------------------------------------------
#define	DAP_BASS_ENHANCE_CTRL_REG               			0x0106

// Bit-Field Access
#define	DAP_BASS_ENHANCE_CTRL_RSVD0_GETMASK     	0xC000
#define	DAP_BASS_ENHANCE_CTRL_RSVD0_STARTBIT    	0xE

#define	DAP_BASS_ENHANCE_CTRL_LR_LEVEL_GETMASK  	0x3F00
#define	DAP_BASS_ENHANCE_CTRL_LR_LEVEL_CLEARMASK	0xC0FF
#define	DAP_BASS_ENHANCE_CTRL_LR_LEVEL_STARTBIT 	0x8

#define	DAP_BASS_ENHANCE_CTRL_RSVD2_GETMASK     	0x0080
#define	DAP_BASS_ENHANCE_CTRL_RSVD2_STARTBIT    	0x7

#define	DAP_BASS_ENHANCE_CTRL_BASS_LEVEL_GETMASK	0x007F
#define	DAP_BASS_ENHANCE_CTRL_BASS_LEVEL_CLEARMASK	0xFF80
#define	DAP_BASS_ENHANCE_CTRL_BASS_LEVEL_STARTBIT	0x0

//-------------------------------------------------------------
// DAP_AUDIO_EQ_REG
//-------------------------------------------------------------
#define	DAP_AUDIO_EQ_REG                        			0x0108

// Bit-Field Access
#define	DAP_AUDIO_EQ_RSVD0_GETMASK              	0xFFFC
#define	DAP_AUDIO_EQ_RSVD0_STARTBIT             	0x2

#define	DAP_AUDIO_EQ_EN_GETMASK                 	0x0003
#define	DAP_AUDIO_EQ_EN_CLEARMASK               	0xFFFC
#define	DAP_AUDIO_EQ_EN_STARTBIT                	0x0

//-------------------------------------------------------------
// DAP_SGTL_SURROUND_REG
//-------------------------------------------------------------
#define	DAP_SGTL_SURROUND_REG                   			0x010A

// Bit-Field Access
#define	DAP_SGTL_SURROUND_RSVD0_GETMASK         	0xFF80
#define	DAP_SGTL_SURROUND_RSVD0_STARTBIT        	0x7

#define	DAP_SGTL_SURROUND_WIDTH_CONTROL_GETMASK 	0x0070
#define	DAP_SGTL_SURROUND_WIDTH_CONTROL_CLEARMASK	0xFF8F
#define	DAP_SGTL_SURROUND_WIDTH_CONTROL_STARTBIT	0x4

#define	DAP_SGTL_SURROUND_RSVD2_GETMASK         	0x000C
#define	DAP_SGTL_SURROUND_RSVD2_STARTBIT        	0x2

#define	DAP_SGTL_SURROUND_SELECT_GETMASK        	0x0003
#define	DAP_SGTL_SURROUND_SELECT_CLEARMASK      	0xFFFC
#define	DAP_SGTL_SURROUND_SELECT_STARTBIT       	0x0

//-------------------------------------------------------------
// DAP_FILTER_COEF_ACCESS_REG
//-------------------------------------------------------------
#define	DAP_FILTER_COEF_ACCESS_REG              			0x010C

// Bit-Field Access
#define	DAP_FILTER_COEF_ACCESS_RSVD0_GETMASK    	0xE000
#define	DAP_FILTER_COEF_ACCESS_RSVD0_STARTBIT   	0xD

#define	DAP_FILTER_COEF_ACCESS_DEBUG_GETMASK    	0x1000
#define	DAP_FILTER_COEF_ACCESS_DEBUG_CLEARMASK  	0xEFFF
#define	DAP_FILTER_COEF_ACCESS_DEBUG_STARTBIT   	0xC

#define	DAP_FILTER_COEF_ACCESS_RSVD2_GETMASK    	0x0C00
#define	DAP_FILTER_COEF_ACCESS_RSVD2_STARTBIT   	0xA

#define	DAP_FILTER_COEF_ACCESS_RD_GETMASK       	0x0200
#define	DAP_FILTER_COEF_ACCESS_RD_CLEARMASK     	0xFDFF
#define	DAP_FILTER_COEF_ACCESS_RD_STARTBIT      	0x9

#define	DAP_FILTER_COEF_ACCESS_WR_GETMASK       	0x0100
#define	DAP_FILTER_COEF_ACCESS_WR_CLEARMASK     	0xFEFF
#define	DAP_FILTER_COEF_ACCESS_WR_STARTBIT      	0x8

#define	DAP_FILTER_COEF_ACCESS_INDEX_GETMASK    	0x00FF
#define	DAP_FILTER_COEF_ACCESS_INDEX_CLEARMASK  	0xFF00
#define	DAP_FILTER_COEF_ACCESS_INDEX_STARTBIT   	0x0

//-------------------------------------------------------------
// DAP_COEF_WR_B0_MSB_REG
//-------------------------------------------------------------
#define	DAP_COEF_WR_B0_MSB_REG                  			0x010E

// Bit-Field Access
#define	DAP_COEF_WR_B0_MSB_BIT_19_GETMASK       	0x8000
#define	DAP_COEF_WR_B0_MSB_BIT_19_CLEARMASK     	0x7FFF
#define	DAP_COEF_WR_B0_MSB_BIT_19_STARTBIT      	0xF

#define	DAP_COEF_WR_B0_MSB_BIT_18_GETMASK       	0x4000
#define	DAP_COEF_WR_B0_MSB_BIT_18_CLEARMASK     	0xBFFF
#define	DAP_COEF_WR_B0_MSB_BIT_18_STARTBIT      	0xE

#define	DAP_COEF_WR_B0_MSB_BIT_17_GETMASK       	0x2000
#define	DAP_COEF_WR_B0_MSB_BIT_17_CLEARMASK     	0xDFFF
#define	DAP_COEF_WR_B0_MSB_BIT_17_STARTBIT      	0xD

#define	DAP_COEF_WR_B0_MSB_BIT_16_GETMASK       	0x1000
#define	DAP_COEF_WR_B0_MSB_BIT_16_CLEARMASK     	0xEFFF
#define	DAP_COEF_WR_B0_MSB_BIT_16_STARTBIT      	0xC

#define	DAP_COEF_WR_B0_MSB_BIT_15_GETMASK       	0x0800
#define	DAP_COEF_WR_B0_MSB_BIT_15_CLEARMASK     	0xF7FF
#define	DAP_COEF_WR_B0_MSB_BIT_15_STARTBIT      	0xB

#define	DAP_COEF_WR_B0_MSB_BIT_14_GETMASK       	0x0400
#define	DAP_COEF_WR_B0_MSB_BIT_14_CLEARMASK     	0xFBFF
#define	DAP_COEF_WR_B0_MSB_BIT_14_STARTBIT      	0xA

#define	DAP_COEF_WR_B0_MSB_BIT_13_GETMASK       	0x0200
#define	DAP_COEF_WR_B0_MSB_BIT_13_CLEARMASK     	0xFDFF
#define	DAP_COEF_WR_B0_MSB_BIT_13_STARTBIT      	0x9

#define	DAP_COEF_WR_B0_MSB_BIT_12_GETMASK       	0x0100
#define	DAP_COEF_WR_B0_MSB_BIT_12_CLEARMASK     	0xFEFF
#define	DAP_COEF_WR_B0_MSB_BIT_12_STARTBIT      	0x8

#define	DAP_COEF_WR_B0_MSB_BIT_11_GETMASK       	0x0080
#define	DAP_COEF_WR_B0_MSB_BIT_11_CLEARMASK     	0xFF7F
#define	DAP_COEF_WR_B0_MSB_BIT_11_STARTBIT      	0x7

#define	DAP_COEF_WR_B0_MSB_BIT_10_GETMASK       	0x0040
#define	DAP_COEF_WR_B0_MSB_BIT_10_CLEARMASK     	0xFFBF
#define	DAP_COEF_WR_B0_MSB_BIT_10_STARTBIT      	0x6

#define	DAP_COEF_WR_B0_MSB_BIT_9_GETMASK        	0x0020
#define	DAP_COEF_WR_B0_MSB_BIT_9_CLEARMASK      	0xFFDF
#define	DAP_COEF_WR_B0_MSB_BIT_9_STARTBIT       	0x5

#define	DAP_COEF_WR_B0_MSB_BIT_8_GETMASK        	0x0010
#define	DAP_COEF_WR_B0_MSB_BIT_8_CLEARMASK      	0xFFEF
#define	DAP_COEF_WR_B0_MSB_BIT_8_STARTBIT       	0x4

#define	DAP_COEF_WR_B0_MSB_BIT_7_GETMASK        	0x0008
#define	DAP_COEF_WR_B0_MSB_BIT_7_CLEARMASK      	0xFFF7
#define	DAP_COEF_WR_B0_MSB_BIT_7_STARTBIT       	0x3

#define	DAP_COEF_WR_B0_MSB_BIT_6_GETMASK        	0x0004
#define	DAP_COEF_WR_B0_MSB_BIT_6_CLEARMASK      	0xFFFB
#define	DAP_COEF_WR_B0_MSB_BIT_6_STARTBIT       	0x2

#define	DAP_COEF_WR_B0_MSB_BIT_5_GETMASK        	0x0002
#define	DAP_COEF_WR_B0_MSB_BIT_5_CLEARMASK      	0xFFFD
#define	DAP_COEF_WR_B0_MSB_BIT_5_STARTBIT       	0x1

#define	DAP_COEF_WR_B0_MSB_BIT_4_GETMASK        	0x0001
#define	DAP_COEF_WR_B0_MSB_BIT_4_CLEARMASK      	0xFFFE
#define	DAP_COEF_WR_B0_MSB_BIT_4_STARTBIT       	0x0

//-------------------------------------------------------------
// DAP_COEF_WR_B0_LSB_REG
//-------------------------------------------------------------
#define	DAP_COEF_WR_B0_LSB_REG                  			0x0110

// Bit-Field Access
#define	DAP_COEF_WR_B0_LSB_RSVD0_GETMASK        	0xFFF0
#define	DAP_COEF_WR_B0_LSB_RSVD0_STARTBIT       	0x4

#define	DAP_COEF_WR_B0_LSB_BIT_3_GETMASK        	0x0008
#define	DAP_COEF_WR_B0_LSB_BIT_3_CLEARMASK      	0xFFF7
#define	DAP_COEF_WR_B0_LSB_BIT_3_STARTBIT       	0x3

#define	DAP_COEF_WR_B0_LSB_BIT_2_GETMASK        	0x0004
#define	DAP_COEF_WR_B0_LSB_BIT_2_CLEARMASK      	0xFFFB
#define	DAP_COEF_WR_B0_LSB_BIT_2_STARTBIT       	0x2

#define	DAP_COEF_WR_B0_LSB_BIT_1_GETMASK        	0x0002
#define	DAP_COEF_WR_B0_LSB_BIT_1_CLEARMASK      	0xFFFD
#define	DAP_COEF_WR_B0_LSB_BIT_1_STARTBIT       	0x1

#define	DAP_COEF_WR_B0_LSB_BIT_0_GETMASK        	0x0001
#define	DAP_COEF_WR_B0_LSB_BIT_0_CLEARMASK      	0xFFFE
#define	DAP_COEF_WR_B0_LSB_BIT_0_STARTBIT       	0x0

//-------------------------------------------------------------
// DAP_AUDIO_EQ_BASS_BAND0_REG
//-------------------------------------------------------------
#define	DAP_AUDIO_EQ_BASS_BAND0_REG             			0x0116

// Bit-Field Access
#define	DAP_AUDIO_EQ_BASS_BAND0_RSVD0_GETMASK   	0xFF80
#define	DAP_AUDIO_EQ_BASS_BAND0_RSVD0_STARTBIT  	0x7

#define	DAP_AUDIO_EQ_BASS_BAND0_VOLUME_GETMASK  	0x007F
#define	DAP_AUDIO_EQ_BASS_BAND0_VOLUME_CLEARMASK	0xFF80
#define	DAP_AUDIO_EQ_BASS_BAND0_VOLUME_STARTBIT 	0x0

//-------------------------------------------------------------
// DAP_AUDIO_EQ_BAND1_REG
//-------------------------------------------------------------
#define	DAP_AUDIO_EQ_BAND1_REG                  			0x0118

// Bit-Field Access
#define	DAP_AUDIO_EQ_BAND1_RSVD0_GETMASK        	0xFF80
#define	DAP_AUDIO_EQ_BAND1_RSVD0_STARTBIT       	0x7

#define	DAP_AUDIO_EQ_BAND1_VOLUME_GETMASK       	0x007F
#define	DAP_AUDIO_EQ_BAND1_VOLUME_CLEARMASK     	0xFF80
#define	DAP_AUDIO_EQ_BAND1_VOLUME_STARTBIT      	0x0

//-------------------------------------------------------------
// DAP_AUDIO_EQ_BAND2_REG
//-------------------------------------------------------------
#define	DAP_AUDIO_EQ_BAND2_REG                  			0x011A

// Bit-Field Access
#define	DAP_AUDIO_EQ_BAND2_RSVD0_GETMASK        	0xFF80
#define	DAP_AUDIO_EQ_BAND2_RSVD0_STARTBIT       	0x7

#define	DAP_AUDIO_EQ_BAND2_VOLUME_GETMASK       	0x007F
#define	DAP_AUDIO_EQ_BAND2_VOLUME_CLEARMASK     	0xFF80
#define	DAP_AUDIO_EQ_BAND2_VOLUME_STARTBIT      	0x0

//-------------------------------------------------------------
// DAP_AUDIO_EQ_BAND3_REG
//-------------------------------------------------------------
#define	DAP_AUDIO_EQ_BAND3_REG                  			0x011C

// Bit-Field Access
#define	DAP_AUDIO_EQ_BAND3_RSVD0_GETMASK        	0xFF80
#define	DAP_AUDIO_EQ_BAND3_RSVD0_STARTBIT       	0x7

#define	DAP_AUDIO_EQ_BAND3_VOLUME_GETMASK       	0x007F
#define	DAP_AUDIO_EQ_BAND3_VOLUME_CLEARMASK     	0xFF80
#define	DAP_AUDIO_EQ_BAND3_VOLUME_STARTBIT      	0x0

//-------------------------------------------------------------
// DAP_AUDIO_EQ_TREBLE_BAND4_REG
//-------------------------------------------------------------
#define	DAP_AUDIO_EQ_TREBLE_BAND4_REG           			0x011E

// Bit-Field Access
#define	DAP_AUDIO_EQ_TREBLE_BAND4_RSVD0_GETMASK 	0xFF80
#define	DAP_AUDIO_EQ_TREBLE_BAND4_RSVD0_STARTBIT	0x7

#define	DAP_AUDIO_EQ_TREBLE_BAND4_VOLUME_GETMASK	0x007F
#define	DAP_AUDIO_EQ_TREBLE_BAND4_VOLUME_CLEARMASK	0xFF80
#define	DAP_AUDIO_EQ_TREBLE_BAND4_VOLUME_STARTBIT	0x0

//-------------------------------------------------------------
// DAP_MAIN_CHAN_REG
//-------------------------------------------------------------
#define	DAP_MAIN_CHAN_REG                       			0x0120

// Bit-Field Access
#define	DAP_MAIN_CHAN_VOL_GETMASK               	0xFFFF
#define	DAP_MAIN_CHAN_VOL_CLEARMASK             	0x0000
#define	DAP_MAIN_CHAN_VOL_STARTBIT              	0x0

//-------------------------------------------------------------
// DAP_MIX_CHAN_REG
//-------------------------------------------------------------
#define	DAP_MIX_CHAN_REG                        			0x0122

// Bit-Field Access
#define	DAP_MIX_CHAN_VOL_GETMASK                	0xFFFF
#define	DAP_MIX_CHAN_VOL_CLEARMASK              	0x0000
#define	DAP_MIX_CHAN_VOL_STARTBIT               	0x0

//-------------------------------------------------------------
// DAP_AVC_CTRL_REG
//-------------------------------------------------------------
#define	DAP_AVC_CTRL_REG                        			0x0124

// Bit-Field Access
#define	DAP_AVC_CTRL_RSVD0_GETMASK              	0x8000
#define	DAP_AVC_CTRL_RSVD0_STARTBIT             	0xF

#define	DAP_AVC_CTRL_APOP_ENABLE_GETMASK        	0x4000
#define	DAP_AVC_CTRL_APOP_ENABLE_CLEARMASK      	0xBFFF
#define	DAP_AVC_CTRL_APOP_ENABLE_STARTBIT       	0xE

#define	DAP_AVC_CTRL_MAX_GAIN_GETMASK           	0x3000
#define	DAP_AVC_CTRL_MAX_GAIN_CLEARMASK         	0xCFFF
#define	DAP_AVC_CTRL_MAX_GAIN_STARTBIT          	0xC

#define	DAP_AVC_CTRL_RSVD3_GETMASK              	0x0C00
#define	DAP_AVC_CTRL_RSVD3_STARTBIT             	0xA

#define	DAP_AVC_CTRL_LBI_RESPONSE_GETMASK       	0x0300
#define	DAP_AVC_CTRL_LBI_RESPONSE_CLEARMASK     	0xFCFF
#define	DAP_AVC_CTRL_LBI_RESPONSE_STARTBIT      	0x8

#define	DAP_AVC_CTRL_RSVD5_GETMASK              	0x00C0
#define	DAP_AVC_CTRL_RSVD5_STARTBIT             	0x6

#define	DAP_AVC_CTRL_HARD_LIMIT_EN_GETMASK      	0x0020
#define	DAP_AVC_CTRL_HARD_LIMIT_EN_CLEARMASK    	0xFFDF
#define	DAP_AVC_CTRL_HARD_LIMIT_EN_STARTBIT     	0x5

#define	DAP_AVC_CTRL_RSVD7_GETMASK              	0x0018
#define	DAP_AVC_CTRL_RSVD7_STARTBIT             	0x3

#define	DAP_AVC_CTRL_STOP_GETMASK               	0x0004
#define	DAP_AVC_CTRL_STOP_STARTBIT              	0x2

#define	DAP_AVC_CTRL_RUNNING_GETMASK            	0x0002
#define	DAP_AVC_CTRL_RUNNING_STARTBIT           	0x1

#define	DAP_AVC_CTRL_EN_GETMASK                 	0x0001
#define	DAP_AVC_CTRL_EN_CLEARMASK               	0xFFFE
#define	DAP_AVC_CTRL_EN_STARTBIT                	0x0

//-------------------------------------------------------------
// DAP_AVC_THRESHOLD_REG
//-------------------------------------------------------------
#define	DAP_AVC_THRESHOLD_REG                   			0x0126

// Bit-Field Access
#define	DAP_AVC_THRESHOLD_THRESH_GETMASK        	0xFFFF
#define	DAP_AVC_THRESHOLD_THRESH_CLEARMASK      	0x0000
#define	DAP_AVC_THRESHOLD_THRESH_STARTBIT       	0x0

//-------------------------------------------------------------
// DAP_AVC_ATTACK_REG
//-------------------------------------------------------------
#define	DAP_AVC_ATTACK_REG                      			0x0128

// Bit-Field Access
#define	DAP_AVC_ATTACK_RSVD0_GETMASK            	0xF000
#define	DAP_AVC_ATTACK_RSVD0_STARTBIT           	0xC

#define	DAP_AVC_ATTACK_RATE_GETMASK             	0x0FFF
#define	DAP_AVC_ATTACK_RATE_CLEARMASK           	0xF000
#define	DAP_AVC_ATTACK_RATE_STARTBIT            	0x0

//-------------------------------------------------------------
// DAP_AVC_DECAY_REG
//-------------------------------------------------------------
#define	DAP_AVC_DECAY_REG                       			0x012A

// Bit-Field Access
#define	DAP_AVC_DECAY_RSVD0_GETMASK             	0xF000
#define	DAP_AVC_DECAY_RSVD0_STARTBIT            	0xC

#define	DAP_AVC_DECAY_RATE_GETMASK              	0x0FFF
#define	DAP_AVC_DECAY_RATE_CLEARMASK            	0xF000
#define	DAP_AVC_DECAY_RATE_STARTBIT             	0x0

//-------------------------------------------------------------
// DAP_COEF_WR_B1_MSB_REG
//-------------------------------------------------------------
#define	DAP_COEF_WR_B1_MSB_REG                  			0x012C

// Bit-Field Access
#define	DAP_COEF_WR_B1_MSB_MSB_GETMASK          	0xFFFF
#define	DAP_COEF_WR_B1_MSB_MSB_CLEARMASK        	0x0000
#define	DAP_COEF_WR_B1_MSB_MSB_STARTBIT         	0x0

//-------------------------------------------------------------
// DAP_COEF_WR_B1_LSB_REG
//-------------------------------------------------------------
#define	DAP_COEF_WR_B1_LSB_REG                  			0x012E

// Bit-Field Access
#define	DAP_COEF_WR_B1_LSB_RSVD0_GETMASK        	0xFFF0
#define	DAP_COEF_WR_B1_LSB_RSVD0_STARTBIT       	0x4

#define	DAP_COEF_WR_B1_LSB_LSB_GETMASK          	0x000F
#define	DAP_COEF_WR_B1_LSB_LSB_CLEARMASK        	0xFFF0
#define	DAP_COEF_WR_B1_LSB_LSB_STARTBIT         	0x0

//-------------------------------------------------------------
// DAP_COEF_WR_B2_MSB_REG
//-------------------------------------------------------------
#define	DAP_COEF_WR_B2_MSB_REG                  			0x0130

// Bit-Field Access
#define	DAP_COEF_WR_B2_MSB_MSB_GETMASK          	0xFFFF
#define	DAP_COEF_WR_B2_MSB_MSB_CLEARMASK        	0x0000
#define	DAP_COEF_WR_B2_MSB_MSB_STARTBIT         	0x0

//-------------------------------------------------------------
// DAP_COEF_WR_B2_LSB_REG
//-------------------------------------------------------------
#define	DAP_COEF_WR_B2_LSB_REG                  			0x0132

// Bit-Field Access
#define	DAP_COEF_WR_B2_LSB_RSVD0_GETMASK        	0xFFF0
#define	DAP_COEF_WR_B2_LSB_RSVD0_STARTBIT       	0x4

#define	DAP_COEF_WR_B2_LSB_LSB_GETMASK          	0x000F
#define	DAP_COEF_WR_B2_LSB_LSB_CLEARMASK        	0xFFF0
#define	DAP_COEF_WR_B2_LSB_LSB_STARTBIT         	0x0

//-------------------------------------------------------------
// DAP_COEF_WR_A1_MSB_REG
//-------------------------------------------------------------
#define	DAP_COEF_WR_A1_MSB_REG                  			0x0134

// Bit-Field Access
#define	DAP_COEF_WR_A1_MSB_MSB_GETMASK          	0xFFFF
#define	DAP_COEF_WR_A1_MSB_MSB_CLEARMASK        	0x0000
#define	DAP_COEF_WR_A1_MSB_MSB_STARTBIT         	0x0

//-------------------------------------------------------------
// DAP_COEF_WR_A1_LSB_REG
//-------------------------------------------------------------
#define	DAP_COEF_WR_A1_LSB_REG                  			0x0136

// Bit-Field Access
#define	DAP_COEF_WR_A1_LSB_RSVD0_GETMASK        	0xFFF0
#define	DAP_COEF_WR_A1_LSB_RSVD0_STARTBIT       	0x4

#define	DAP_COEF_WR_A1_LSB_LSB_GETMASK          	0x000F
#define	DAP_COEF_WR_A1_LSB_LSB_CLEARMASK        	0xFFF0
#define	DAP_COEF_WR_A1_LSB_LSB_STARTBIT         	0x0

//-------------------------------------------------------------
// DAP_COEF_WR_A2_MSB_REG
//-------------------------------------------------------------
#define	DAP_COEF_WR_A2_MSB_REG                  			0x0138

// Bit-Field Access
#define	DAP_COEF_WR_A2_MSB_MSB_GETMASK          	0xFFFF
#define	DAP_COEF_WR_A2_MSB_MSB_CLEARMASK        	0x0000
#define	DAP_COEF_WR_A2_MSB_MSB_STARTBIT         	0x0

//-------------------------------------------------------------
// DAP_COEF_WR_A2_LSB_REG
//-------------------------------------------------------------
#define	DAP_COEF_WR_A2_LSB_REG                  			0x013A

// Bit-Field Access
#define	DAP_COEF_WR_A2_LSB_RSVD0_GETMASK        	0xFFF0
#define	DAP_COEF_WR_A2_LSB_RSVD0_STARTBIT       	0x4

#define	DAP_COEF_WR_A2_LSB_LSB_GETMASK          	0x000F
#define	DAP_COEF_WR_A2_LSB_LSB_CLEARMASK        	0xFFF0
#define	DAP_COEF_WR_A2_LSB_LSB_STARTBIT         	0x0

/*End DAP register commented out section*/
