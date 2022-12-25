/**
  ******************************************************************************
  * @file    bl808_audio.c
  * @version V1.0
  * @date
  * @brief   This file is the standard driver c file
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2020 Bouffalo Lab</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of Bouffalo Lab nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

#include "bl808_audio.h"
#include "audio_reg.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  AUDIO
 *  @{
 */

/** @defgroup  AUDIO_Private_Macros
 *  @{
 */

/*@} end of group AUDIO_Private_Macros */

/** @defgroup  AUDIO_Private_Types
 *  @{
 */

/*@} end of group AUDIO_Private_Types */

/** @defgroup  AUDIO_Private_Variables
 *  @{
 */
#ifndef BFLB_USE_HAL_DRIVER
static intCallback_Type *audioIntCbfArra[AUDIO_INT_NUM_ALL] = { NULL };
#endif
/*@} end of group AUDIO_Private_Variables */

/** @defgroup  AUDIO_Global_Variables
 *  @{
 */

/*@} end of group AUDIO_Global_Variables */

/** @defgroup  AUDIO_Private_Fun_Declaration
 *  @{
 */

/*@} end of group AUDIO_Private_Fun_Declaration */

/** @defgroup  AUDIO_Private_Functions
 *  @{
 */

/*@} end of group AUDIO_Private_Functions */

/** @defgroup  AUDIO_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  Select Tx channel source Defaule is tx0-dac_0,tx1-dac_1
 *
 * @param  tx_channel: tx_channel index . Note tx_channel <=2
 * @param  dac_id: tx[rx_channel] conect to dac_id
 *
 * @return Success or not
 *
*******************************************************************************/
BL_Err_Type Audio_Tx_Source_DAC_Sel(uint8_t tx_channel, Audio_DAC_ID_Type dac_id)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_DAC_ID_TYPE(dac_id));

    if (tx_channel > 2) {
        return ERROR;
        /*tx channel sel can not larger than 2*/
    }

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_AUD_ITF);

    if (tx_channel == 0) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AUD_TX0_SEL, dac_id);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AUD_TX1_SEL, dac_id);
    }

    BL_WR_REG(AUDIO_BASE, AUDIO_AUD_ITF, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Select Rx channel form ADC Channel . source Default selction is
 *         rx0-adc_0,rx1-adc_1,rx2-adc_2,rx3-aec_0,rx4-aec_1
 *
 * @param  rx_channel: rx_channel index . Note tx_channel <=4
 * @param  adc_id: rx[rx_channel] conect to adc_id
 *
 * @return Success or not
 *
*******************************************************************************/
BL_Err_Type Audio_Rx_Source_ADC_Sel(uint8_t rx_channel, Audio_ADC_ID_Type adc_id)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_ADC_ID_TYPE(adc_id));

    if (rx_channel > 4) {
        return ERROR;
        /*rx channel sel can not larger than 4*/
    }

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_AUD_ITF);

    switch (rx_channel) {
        case 0:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AUD_RX0_SEL, adc_id);
            break;
        case 1:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AUD_RX1_SEL, adc_id);
            break;
        case 2:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AUD_RX2_SEL, adc_id);
            break;
        case 3:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AUD_RX3_SEL, adc_id);
            break;
        case 4:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AUD_RX4_SEL, adc_id);
            break;
        default:
            break;
    }

    BL_WR_REG(AUDIO_BASE, AUDIO_AUD_ITF, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Select Rx channel form AEC Channel . source Default selction is
 *         rx0-adc_0,rx1-adc_1,rx2-adc_2,rx3-aec_0,rx4-aec_1
 *
 * @param  rx_channel: tx_channel index . Note tx_channel <=4
 * @param  aec_id: rx[rx_channel] conect to aec_id
 *
 * @return Success or not
 *
*******************************************************************************/
BL_Err_Type Audio_Rx_Source_AEC_Sel(uint8_t rx_channel, Audio_AEC_ID_Type aec_id)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_AEC_ID_TYPE(aec_id));

    if (rx_channel > 4) {
        return ERROR;
        /*rx channel sel can not larger than 4*/
    }

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_AUD_ITF);

    switch (rx_channel) {
        case 0:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AUD_RX0_SEL, aec_id + 3);
            break;
        case 1:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AUD_RX1_SEL, aec_id + 3);
            break;
        case 2:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AUD_RX2_SEL, aec_id + 3);
            break;
        case 3:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AUD_RX3_SEL, aec_id + 3);
            break;
        case 4:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AUD_RX4_SEL, aec_id + 3);
            break;
        default:
            break;
    }

    BL_WR_REG(AUDIO_BASE, AUDIO_AUD_ITF, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Audio Set HPF Parameter
 *
 * @param  id: ADC ID
 * @param  k1_enable: k1 parameter enable
 * @param  k1: k1 parameter in range 4 bit
 * @param  k2_enable: k2 parameter enable
 * @param  k2: k1 parameter in range 4 bit
 *
 * @return None
 *
*******************************************************************************/
void Audio_Set_HPF_Parameter(Audio_ADC_ID_Type id, uint8_t k1_enable, uint8_t k1, uint8_t k2_enable, uint8_t k2)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_ADC_ID_TYPE(id));

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_ADC_1);

    switch (id) {
        case AUDIO_ADC_0:
            if (k1_enable) {
                tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_ADC_0_K1_EN);
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_0_K1, k1);
            } else {
                tmpVal = BL_CLR_REG_BIT(tmpVal, AUDIO_ADC_0_K1_EN);
            }
            if (k2_enable) {
                tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_ADC_0_K2_EN);
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_0_K2, k2);
            } else {
                tmpVal = BL_CLR_REG_BIT(tmpVal, AUDIO_ADC_0_K2_EN);
            }
            break;
        case AUDIO_ADC_1:
            if (k1_enable) {
                tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_ADC_1_K1_EN);
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_1_K1, k1);
            } else {
                tmpVal = BL_CLR_REG_BIT(tmpVal, AUDIO_ADC_1_K1_EN);
            }
            if (k2_enable) {
                tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_ADC_1_K2_EN);
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_1_K2, k2);
            } else {
                tmpVal = BL_CLR_REG_BIT(tmpVal, AUDIO_ADC_1_K2_EN);
            }
            break;
        case AUDIO_ADC_2:
            if (k1_enable) {
                tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_ADC_2_K1_EN);
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_2_K1, k1);
            } else {
                tmpVal = BL_CLR_REG_BIT(tmpVal, AUDIO_ADC_2_K1_EN);
            }

            if (k2_enable) {
                tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_ADC_2_K2_EN);
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_2_K2, k2);
            } else {
                tmpVal = BL_CLR_REG_BIT(tmpVal, AUDIO_ADC_2_K2_EN);
            }
            break;
        default:
            break;
    }

    BL_WR_REG(AUDIO_BASE, AUDIO_ADC_1, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Audio Set ADC Source PDM or Analog
 *
 * @param  id: k1 parameter in range 4 bit ,when k0=0 k0 parameter will disabled
 * @param  adc_source: k2 parameter in range 4 bit ,when k1=0 k1 parameter will disabled
 *
 * @return None
 *
*******************************************************************************/
void Audio_Set_ADC_Source(Audio_ADC_ID_Type id, Audio_ADC_Source_Type adc_source)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_ADC_ID_TYPE(id));

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_DAC_0);

    if (id == AUDIO_ADC_0) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_0_SRC, adc_source);
    } else if (id == AUDIO_ADC_1) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_1_SRC, adc_source);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_2_SRC, adc_source);
    }

    BL_WR_REG(AUDIO_BASE, AUDIO_DAC_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Audio AEC enable
 *
 * @param  id: Auido AEC ID
 *
 * @return None
 *
*******************************************************************************/
void Audio_AEC_Enable(Audio_AEC_ID_Type id)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_AEC_ID_TYPE(id));

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_AUD_ITF);
    if (id == AUDIO_AEC_0) {
        tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_AEC_0_EN);
    } else {
        tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_AEC_1_EN);
    }
    BL_WR_REG(AUDIO_BASE, AUDIO_AUD_ITF, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Audio AEC disable
 *
 * @param  id: Auido AEC ID
 *
 * @return None
 *
*******************************************************************************/
void Audio_AEC_Disable(Audio_AEC_ID_Type id)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_AEC_ID_TYPE(id));

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_AUD_ITF);
    if (id == AUDIO_AEC_0) {
        tmpVal = BL_CLR_REG_BIT(tmpVal, AUDIO_AEC_0_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, AUDIO_AEC_1_EN);
    }
    BL_WR_REG(AUDIO_BASE, AUDIO_AUD_ITF, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Audio ADC enable
 *
 * @param  id: Auido ADC ID
 *
 * @return None
 *
*******************************************************************************/
void Audio_ADC_Enable(Audio_ADC_ID_Type id)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_ADC_ID_TYPE(id));

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_AUD_ITF);
    if (id == AUDIO_ADC_0) {
        tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_ADC_0_EN);
    } else if (id == AUDIO_ADC_1) {
        tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_ADC_1_EN);
    } else {
        tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_ADC_2_EN);
    }
    BL_WR_REG(AUDIO_BASE, AUDIO_AUD_ITF, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Audio ADC disable
 *
 * @param  id: Auido ADC ID
 *
 * @return None
 *
*******************************************************************************/
void Audio_ADC_Disable(Audio_ADC_ID_Type id)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_ADC_ID_TYPE(id));

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_AUD_ITF);
    if (id == AUDIO_ADC_0) {
        tmpVal = BL_CLR_REG_BIT(tmpVal, AUDIO_ADC_0_EN);
    } else if (id == AUDIO_ADC_1) {
        tmpVal = BL_CLR_REG_BIT(tmpVal, AUDIO_ADC_1_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, AUDIO_ADC_2_EN);
    }
    BL_WR_REG(AUDIO_BASE, AUDIO_AUD_ITF, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Audio DAC disable
 *
 * @param  id: Auido DAC ID
 *
 * @return None
 *
*******************************************************************************/
void Audio_DAC_Enable(Audio_DAC_ID_Type id)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_DAC_ID_TYPE(id));

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_AUD_ITF);
    if (id == AUDIO_DAC_0) {
        tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_DAC_0_EN);
    } else {
        tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_DAC_1_EN);
    }
    BL_WR_REG(AUDIO_BASE, AUDIO_AUD_ITF, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Audio DAC disable
 *
 * @param  id: Auido DAC ID
 *
 * @return None
 *
*******************************************************************************/
void Audio_DAC_Disable(Audio_DAC_ID_Type id)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_DAC_ID_TYPE(id));

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_AUD_ITF);
    if (id == AUDIO_DAC_0) {
        tmpVal = BL_CLR_REG_BIT(tmpVal, AUDIO_DAC_0_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, AUDIO_DAC_1_EN);
    }
    BL_WR_REG(AUDIO_BASE, AUDIO_AUD_ITF, tmpVal);
}

/****************************************************************************/ /**
 * @brief  set dac amp
 *
 * @param  enable: enable or noy
 * @param  amp: amp
 *
 * @return None
 *
*******************************************************************************/
void Audio_Set_DAC_Dither(uint8_t enable, uint8_t amp)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_DAC_1);

    if (enable) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_DSM_DITHER_EN, 1);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_DSM_DITHER_AMP, amp);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_DSM_DITHER_EN, 0);
    }

    BL_WR_REG(AUDIO_BASE, AUDIO_DAC_1, tmpVal);
}

/****************************************************************************/ /**
 * @brief  set dac scaling
 *
 * @param  enable: enable or noy
 * @param  scaling: scaling
 *
 * @return None
 *
*******************************************************************************/
void Audio_Set_DAC_Scaling(uint8_t enable, uint8_t scaling)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_DAC_1);
    if (enable) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_DSM_SCALING_EN, 1);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_DSM_SCALING_FACTOR, scaling);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_DSM_SCALING_EN, 0);
    }
    BL_WR_REG(AUDIO_BASE, AUDIO_DAC_1, tmpVal);
}

/****************************************************************************/ /**
 * @brief  set order
 *
 * @param  order: order
 *
 * @return None
 *
*******************************************************************************/
void Audio_Set_DAC_Order(Audio_DAC_Order_Type order)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_DAC_ORDER_TYPE(order));

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_DAC_1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_DSM_ORDER, order);
    BL_WR_REG(AUDIO_BASE, AUDIO_DAC_1, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Audio_Set_DAC_Dwa_Swap
 *
 * @param  swap: None
 *
 * @return None
 *
*******************************************************************************/
void Audio_Set_DAC_Dwa_Swap(uint8_t swap)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_DAC_1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_DEM_OUT_SWAP, swap);
    BL_WR_REG(AUDIO_BASE, AUDIO_DAC_1, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Audio_Set_DAC_Dsm_Bypass
 *
 * @param  bypass: None
 *
 * @return None
 *
*******************************************************************************/
void Audio_Set_DAC_Dwa_Bypass(uint8_t bypass)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_DAC_1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_DEM_BYPASS, bypass);
    BL_WR_REG(AUDIO_BASE, AUDIO_DAC_1, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Audio set adc lfsr
 *
 * @param  lfsrType: Auido ADC LFSR TYPE
 *
 * @return None
 *
*******************************************************************************/
void Audio_Set_DAC_LFSR(Audio_LFSR_Type lfsrType)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_ADC_LFSR_TYPE(lfsrType));

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_ADC_0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_LFSR_MODE, lfsrType);
    BL_WR_REG(AUDIO_BASE, AUDIO_ADC_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  read LSFR
 *
 * @param  None
 *
 * @return read LSFR out
 *
*******************************************************************************/
BL_Sts_Type Audio_Get_ADC_LFSR(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_ADC_0);
    return BL_IS_REG_BIT_SET(tmpVal, AUDIO_ADC_DITHER_DATA);
}

/****************************************************************************/ /**
 * @brief  set adc scaling value
 *
 * @param  id: Auido ADC ID
 * @param  scalingVal: scaling value
 *
 * @return None
 *
*******************************************************************************/
void Audio_Set_ADC_Scaling_Value(Audio_ADC_ID_Type id, uint8_t scalingVal)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_ADC_ID_TYPE(id));

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_ADC_0);

    if (id == AUDIO_ADC_0) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_0_SCAL, scalingVal);
    } else if (id == AUDIO_ADC_1) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_1_SCAL, scalingVal);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_2_SCAL, scalingVal);
    }
    BL_WR_REG(AUDIO_BASE, AUDIO_ADC_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  set fir mode
 *
 * @param  id: Auido ADC ID
 * @param  enable: enable or disable
 *
 * @return None
 *
*******************************************************************************/
void Audio_Set_Fir_Mode(Audio_ADC_ID_Type id, uint8_t enable)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_ADC_ID_TYPE(id));

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_ADC_0);

    if (id == AUDIO_ADC_0) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_0_FIR_MODE, enable);
    } else if (id == AUDIO_ADC_1) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_1_FIR_MODE, enable);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_2_FIR_MODE, enable);
    }
    BL_WR_REG(AUDIO_BASE, AUDIO_ADC_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  mixer setting function
 *
 * @param  enable: enbale mixer or not,if disable mixer then other parameter is invalid
 * @param  mixerId: mixer Id,audio have two mixer to selected
 * @param  mode: mixer mode selection , debug mode or sidetone mode(other source is come form
 *               adc0-adc2)
 * @param  sidetoneChannel: mixer adc channel selection , if debug mode is selected this paramter is
 *                          used , or user must select which adc source will be mixed with dac output.
 * @param  Volume: mixer Volume select
 *
 * @return None
 *
*******************************************************************************/
void Audio_Set_Mixer_Mode(uint8_t enable, Audio_Mixer_ID_Type mixerId, Audio_Mixer_Mode mode, Audio_ADC_ID_Type sidetoneChannel, Audio_Mixer_Volume_Type Volume)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_MIXER_ID_TYPE(sidetoneChannel));
    CHECK_PARAM(IS_AUDIO_ADC_ID_TYPE(sidetoneChannel));
    CHECK_PARAM(IS_AUDIO_MIXER_VOLUME_TYPE(Volume));
    CHECK_PARAM(IS_AUDIO_MIXER_MODE(mode));

    if (mixerId == AUDIO_MIXER_ID_0) {
        tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_DAC_0);
    } else {
        tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_DAC_1);
    }

    if (enable) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_MIX_0_MODE, mode);
        if (mode == AUDIO_SECOND_DEBUG_MODE) {
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_MIX_0_ATT_MODE1, Volume);
        } else {
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_MIX_0_SEL, sidetoneChannel + 1);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_MIX_0_ATT_MODE2, Volume);
        }
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_MIX_0_MODE, 0);
    }

    if (mixerId == AUDIO_MIXER_ID_0) {
        BL_WR_REG(AUDIO_BASE, AUDIO_DAC_0, tmpVal);
    } else {
        BL_WR_REG(AUDIO_BASE, AUDIO_DAC_1, tmpVal);
    }
}

/****************************************************************************/ /**
 * @brief  set adc swap
 *
 * @param  id: Auido ADC ID
 * @param  swap: swap
 *
 * @return None
 *
*******************************************************************************/
void Audio_ADC_Mash_Bit_Swap(Audio_ADC_ID_Type id, uint8_t swap)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_ADC_ID_TYPE(id));

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_DAC_0);
    if (id == AUDIO_ADC_0) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_0_MASH_BIT_SWAP, swap);
    } else if (id == AUDIO_ADC_1) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_1_MASH_BIT_SWAP, swap);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_2_MASH_BIT_SWAP, swap);
    }
    BL_WR_REG(AUDIO_BASE, AUDIO_DAC_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  set pdm inv
 *
 * @param  id: Auido ADC ID
 * @param  swap: inv
 *
 * @return None
 *
*******************************************************************************/
void Audio_ADC_PDM_Inv_Swap(Audio_ADC_ID_Type id, uint8_t swap)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_ADC_ID_TYPE(id));

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_DAC_0);
    if (id == AUDIO_ADC_0) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_1_PDM_LVL_SWAP, swap);
    } else if (id == AUDIO_ADC_1) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_1_PDM_LVL_SWAP, swap);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_1_PDM_LVL_SWAP, swap);
    }
    BL_WR_REG(AUDIO_BASE, AUDIO_DAC_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  set pdm value
 *
 * @param  pdm_l: pdm l
 * @param  pdm_h: pdm h
 *
 * @return None
 *
*******************************************************************************/
void Audio_ADC_Set_PDM_Value(uint8_t pdm_l, uint8_t pdm_h)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_PDM_0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_PDM_L, pdm_l);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_PDM_H, pdm_l);
    BL_WR_REG(AUDIO_BASE, AUDIO_PDM_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Audio_Set_AEC_Record_Vid
 *
 * @param  enable: enable or not
 * @param  div: div
 *
 * @return None
 *
*******************************************************************************/
void Audio_Set_AEC_Record_Vid(uint8_t enable, uint8_t div)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_AEC_0);

    if (enable) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AEC_RECORD_VLD_4S_EN, 1);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AEC_RECORD_VLD_4S_DIV, div);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AEC_RECORD_VLD_4S_EN, 0);
    }

    BL_WR_REG(AUDIO_BASE, AUDIO_AEC_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Audio_Set_AEC_Atten_mode
 *
 * @param  aec_id: AEC ID
 * @param  mode: Atten Mode
 *
 * @return None
 *
*******************************************************************************/
void Audio_Set_AEC_Atten_mode(Audio_AEC_ID_Type aec_id, Audio_AEC_Atten_Mode mode)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_AEC_ID_TYPE(aec_id));

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_AEC_0);

    if (aec_id == AUDIO_AEC_0) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AEC_0_ATTEN_MODE, mode);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AEC_1_ATTEN_MODE, mode);
    }

    BL_WR_REG(AUDIO_BASE, AUDIO_AEC_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Audio support three channel for pdm .Meanwhile Audio support two DMIC Interface which
 *         supporting four pdm data source input.This function is used to select channel with pdm
 *         source.
 *
 * @param  id: pdm channel,cannot be larger than 3
 * @param  pdmSel: pdm source select
 *
 * @return Success or not
 *
*******************************************************************************/
void Audio_ADC_PDM_Channel_Sel(Audio_PDM_ID_Type id, Audio_PDM_Source_Type pdmSel)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_PDM_SOURCE_TYPE(pdmSel));
    CHECK_PARAM(IS_AUDIO_PDM_ID_TYPE(id));

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_PDM_0);

    if (id == AUDIO_PDM_0) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_0_PDM_SEL, pdmSel);
    } else if (id == AUDIO_PDM_1) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_1_PDM_SEL, pdmSel);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_2_PDM_SEL, pdmSel);
    }
    BL_WR_REG(AUDIO_BASE, AUDIO_PDM_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Audio Enable PDM
 *
 * @param  id: PDM ID
 *
 * @return Success or not
 *
*******************************************************************************/
void Audio_ADC_PDM_Enable(Audio_PDM_ID_Type id)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_PDM_ID_TYPE(id));

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_PDM_0);

    if (id == AUDIO_PDM_0) {
        tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_PDM_0_EN);
    } else if (id == AUDIO_PDM_1) {
        tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_PDM_1_EN);
    } else {
        tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_PDM_2_EN);
    }
    BL_WR_REG(AUDIO_BASE, AUDIO_PDM_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Audio Disable PDM
 *
 * @param  id: None
 *
 * @return Success or not
 *
*******************************************************************************/
void Audio_ADC_PDM_Disable(Audio_PDM_ID_Type id)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_PDM_ID_TYPE(id));

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_PDM_0);

    if (id == AUDIO_PDM_0) {
        tmpVal = BL_CLR_REG_BIT(tmpVal, AUDIO_PDM_0_EN);
    } else if (id == AUDIO_PDM_1) {
        tmpVal = BL_CLR_REG_BIT(tmpVal, AUDIO_PDM_0_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, AUDIO_PDM_0_EN);
    }
    BL_WR_REG(AUDIO_BASE, AUDIO_PDM_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  debug 0x24 reigister
 *
 * @param  wCmd: None
 *
 * @return None
 *
*******************************************************************************/
void Debug0_Write(uint32_t wCmd)
{
    BL_WR_REG(AUDIO_BASE, AUDIO_DBG_0, wCmd);
}

/****************************************************************************/ /**
 * @brief  debug 0x28 reigister
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
uint32_t Debug1_Read(void)
{
    return BL_RD_REG(AUDIO_BASE, AUDIO_DBG_1);
}

/****************************************************************************/ /**
 * @brief  debug 0x2c reigister
 *
 * @param  wCmd: None
 *
 * @return None
 *
*******************************************************************************/
void Debug2_Write(uint32_t wCmd)
{
    BL_WR_REG(AUDIO_BASE, AUDIO_DBG_2, wCmd);
}

/****************************************************************************/ /**
 * @brief  debug 0x30 reigister
 *
 * @param  wCmd: None
 *
 * @return None
 *
*******************************************************************************/
void Debug3_Write(uint32_t wCmd)
{
    BL_WR_REG(AUDIO_BASE, AUDIO_DBG_3, wCmd);
}

/****************************************************************************/ /**
 * @brief  AUDIO Interrupt mask
 *
 * @param  intType: intType
 * @param  intMask: intMask
 *
 * @return None
 *
*******************************************************************************/
void Auido_IntMask(Audio_INT_Type intType, BL_Mask_Type intMask)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_INT_TYPE(intType));
    CHECK_PARAM(IS_BL_MASK_TYPE(intMask));

    switch (intType) {
        case AUDIO_INT_RX_FIFO_THR:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_RX_FIFO_CTRL);
            if (intMask) {
                tmpVal = BL_CLR_REG_BIT(tmpVal, AUDIO_RXA_INT_EN);
            } else {
                tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_RXA_INT_EN);
            }
            BL_WR_REG(AUDIO_BASE, AUDIO_RX_FIFO_CTRL, tmpVal);
            break;
        case AUDIO_INT_RX_FIFO_OVERRUN:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_RX_FIFO_CTRL);
            if (intMask) {
                tmpVal = BL_CLR_REG_BIT(tmpVal, AUDIO_RXO_INT_EN);
            } else {
                tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_RXO_INT_EN);
            }
            BL_WR_REG(AUDIO_BASE, AUDIO_RX_FIFO_CTRL, tmpVal);
            break;
        case AUDIO_INT_RX_FIFO_UNDERRUN:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_RX_FIFO_CTRL);
            if (intMask) {
                tmpVal = BL_CLR_REG_BIT(tmpVal, AUDIO_RXU_INT_EN);
            } else {
                tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_RXU_INT_EN);
            }
            BL_WR_REG(AUDIO_BASE, AUDIO_RX_FIFO_CTRL, tmpVal);
            break;

        case AUDIO_INT_TX_FIFO_THR:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_TX_FIFO_CTRL);
            if (intMask) {
                tmpVal = BL_CLR_REG_BIT(tmpVal, AUDIO_TXA_INT_EN);
            } else {
                tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_TXA_INT_EN);
            }
            BL_WR_REG(AUDIO_BASE, AUDIO_TX_FIFO_CTRL, tmpVal);
            break;
        case AUDIO_INT_TX_FIFO_OVERRUN:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_TX_FIFO_CTRL);
            if (intMask) {
                tmpVal = BL_CLR_REG_BIT(tmpVal, AUDIO_TXO_INT_EN);
            } else {
                tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_TXO_INT_EN);
            }
            BL_WR_REG(AUDIO_BASE, AUDIO_TX_FIFO_CTRL, tmpVal);
            break;
        case AUDIO_INT_TX_FIFO_UNDERRUN:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_TX_FIFO_CTRL);
            if (intMask) {
                tmpVal = BL_CLR_REG_BIT(tmpVal, AUDIO_TXU_INT_EN);
            } else {
                tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_TXU_INT_EN);
            }
            BL_WR_REG(AUDIO_BASE, AUDIO_TX_FIFO_CTRL, tmpVal);
            break;

        case AUDIO_INT_ADC0_SET_VOLUME_DONE:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_STATUS);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_S0_INT_CLR, intMask);
            BL_WR_REG(AUDIO_BASE, AUDIO_STATUS, tmpVal);
            break;
        case AUDIO_INT_ADC1_SET_VOLUME_DONE:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_STATUS);
            tmpVal = BL_SET_REG_BITS_VAL(AUDIO_BASE, AUDIO_ADC_S1_INT_CLR, intMask);
            BL_WR_REG(AUDIO_BASE, AUDIO_STATUS, tmpVal);
            break;

        case AUDIO_INT_ADC2_SET_VOLUME_DONE:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_STATUS);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_S2_INT_CLR, intMask);
            BL_WR_REG(AUDIO_BASE, AUDIO_STATUS, tmpVal);
            break;
        case AUDIO_INT_DAC0_SET_VOLUME_DONE:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_STATUS);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_S0_INT_CLR, intMask);
            BL_WR_REG(AUDIO_BASE, AUDIO_STATUS, tmpVal);
            break;
        case AUDIO_INT_DAC1_SET_VOLUME_DONE:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_STATUS);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_S1_INT_CLR, intMask);
            BL_WR_REG(AUDIO_BASE, AUDIO_STATUS, tmpVal);
            break;
        case AUDIO_INT_VAD:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_STATUS);
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_VAD_INT_CLR, intMask);
            BL_WR_REG(AUDIO_BASE, AUDIO_STATUS, tmpVal);
            break;
        case AUDIO_INT_NUM_ALL:
            if (intMask) {
                tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_RX_FIFO_CTRL);
                tmpVal = BL_CLR_REG_BIT(tmpVal, AUDIO_RXA_INT_EN);
                tmpVal = BL_CLR_REG_BIT(tmpVal, AUDIO_RXU_INT_EN);
                tmpVal = BL_CLR_REG_BIT(tmpVal, AUDIO_RXO_INT_EN);
                BL_WR_REG(AUDIO_BASE, AUDIO_RX_FIFO_CTRL, tmpVal);

                tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_TX_FIFO_CTRL);
                tmpVal = BL_CLR_REG_BIT(tmpVal, AUDIO_TXA_INT_EN);
                tmpVal = BL_CLR_REG_BIT(tmpVal, AUDIO_TXU_INT_EN);
                tmpVal = BL_CLR_REG_BIT(tmpVal, AUDIO_TXO_INT_EN);

                BL_WR_REG(AUDIO_BASE, AUDIO_TX_FIFO_CTRL, tmpVal);

                BL_WR_REG(AUDIO_BASE, AUDIO_STATUS, 0x40A0A80);
            } else {
                tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_RX_FIFO_CTRL);
                tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_RXA_INT_EN);
                tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_RXU_INT_EN);
                tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_RXO_INT_EN);
                BL_WR_REG(AUDIO_BASE, AUDIO_RX_FIFO_CTRL, tmpVal);

                tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_TX_FIFO_CTRL);
                tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_TXA_INT_EN);
                tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_TXU_INT_EN);
                tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_TXO_INT_EN);

                BL_WR_REG(AUDIO_BASE, AUDIO_TX_FIFO_CTRL, tmpVal);

                BL_WR_REG(AUDIO_BASE, AUDIO_STATUS, 0);
            }

        default:
            break;
    }
}

/****************************************************************************/ /**
 * @brief  clear audio Interrupt flag
 *
 * @param  intType: intType
 *
 * @return None
 *
*******************************************************************************/
void Auido_IntClear(Audio_INT_Type intType)
{
    uint32_t tmpVal = 0;
    uint32_t tmpVal2 = 0;

    CHECK_PARAM(IS_AUDIO_INT_TYPE(intType));

    switch (intType) {
        case AUDIO_INT_RX_FIFO_THR:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_RX_FIFO_STATUS);
            tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_RXA_INT);
            BL_WR_REG(AUDIO_BASE, AUDIO_RX_FIFO_STATUS, tmpVal);
            break;
        case AUDIO_INT_RX_FIFO_OVERRUN:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_RX_FIFO_STATUS);
            tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_RXO_INT);
            BL_WR_REG(AUDIO_BASE, AUDIO_RX_FIFO_STATUS, tmpVal);
            break;
        case AUDIO_INT_RX_FIFO_UNDERRUN:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_RX_FIFO_STATUS);
            tmpVal = BL_SET_REG_BIT(AUDIO_BASE, AUDIO_RXU_INT);
            BL_WR_REG(AUDIO_BASE, AUDIO_RX_FIFO_STATUS, tmpVal);
            break;

        case AUDIO_INT_TX_FIFO_THR:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_TX_FIFO_STATUS);
            tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_TXA_INT);
            BL_WR_REG(AUDIO_BASE, AUDIO_TX_FIFO_STATUS, tmpVal);
            break;
        case AUDIO_INT_TX_FIFO_OVERRUN:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_TX_FIFO_STATUS);
            tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_TXO_INT);
            BL_WR_REG(AUDIO_BASE, AUDIO_TX_FIFO_STATUS, tmpVal);
            break;
        case AUDIO_INT_TX_FIFO_UNDERRUN:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_TX_FIFO_STATUS);
            tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_TXU_INT);
            BL_WR_REG(AUDIO_BASE, AUDIO_TX_FIFO_STATUS, tmpVal);
            break;

        case AUDIO_INT_ADC0_SET_VOLUME_DONE:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_STATUS);
            tmpVal2 = tmpVal;
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_S0_INT_CLR, 1);
            BL_WR_REG(AUDIO_BASE, AUDIO_STATUS, tmpVal);

            BL_WR_REG(AUDIO_BASE, AUDIO_STATUS, tmpVal2);
            break;
        case AUDIO_INT_ADC1_SET_VOLUME_DONE:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_STATUS);
            tmpVal2 = tmpVal;
            tmpVal = BL_SET_REG_BITS_VAL(AUDIO_BASE, AUDIO_ADC_S1_INT_CLR, 1);
            BL_WR_REG(AUDIO_BASE, AUDIO_STATUS, tmpVal);

            BL_WR_REG(AUDIO_BASE, AUDIO_STATUS, tmpVal2);
            break;

        case AUDIO_INT_ADC2_SET_VOLUME_DONE:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_STATUS);
            tmpVal2 = tmpVal;
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_S2_INT_CLR, 1);
            BL_WR_REG(AUDIO_BASE, AUDIO_STATUS, tmpVal);

            BL_WR_REG(AUDIO_BASE, AUDIO_STATUS, tmpVal2);
            break;
        case AUDIO_INT_DAC0_SET_VOLUME_DONE:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_STATUS);
            tmpVal2 = tmpVal;
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_S0_INT_CLR, 1);
            BL_WR_REG(AUDIO_BASE, AUDIO_STATUS, tmpVal);

            BL_WR_REG(AUDIO_BASE, AUDIO_STATUS, tmpVal2);
            break;
        case AUDIO_INT_DAC1_SET_VOLUME_DONE:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_STATUS);
            tmpVal2 = tmpVal;
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_S1_INT_CLR, 1);
            BL_WR_REG(AUDIO_BASE, AUDIO_STATUS, tmpVal);

            BL_WR_REG(AUDIO_BASE, AUDIO_STATUS, tmpVal2);
            break;
        case AUDIO_INT_VAD:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_STATUS);
            tmpVal2 = tmpVal;
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_VAD_INT_CLR, 1);
            BL_WR_REG(AUDIO_BASE, AUDIO_STATUS, tmpVal);

            BL_WR_REG(AUDIO_BASE, AUDIO_STATUS, tmpVal2);
            break;
        case AUDIO_INT_NUM_ALL:

            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_RX_FIFO_STATUS);

            tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_RXA_INT);
            tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_RXU_INT);
            tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_RXO_INT);

            BL_WR_REG(AUDIO_BASE, AUDIO_RX_FIFO_STATUS, tmpVal);

            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_TX_FIFO_STATUS);

            tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_TXA_INT);
            tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_TXU_INT);
            tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_TXO_INT);

            BL_WR_REG(AUDIO_BASE, AUDIO_TX_FIFO_STATUS, tmpVal);

            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_STATUS);

            BL_WR_REG(AUDIO_BASE, AUDIO_STATUS, tmpVal | 0x40A0A80);
            BL_WR_REG(AUDIO_BASE, AUDIO_STATUS, tmpVal);

        default:
            break;
    }
}

/****************************************************************************/ /**
 * @brief  register interrupt callback function pointer
 *
 * @param  intType: intType
 * @param  cbFun: cbFun
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
BL_Err_Type Audio_Int_Callback_Install(Audio_INT_Type intType, intCallback_Type *cbFun)
{
    CHECK_PARAM(IS_AUDIO_INT_TYPE(intType));

    audioIntCbfArra[intType] = cbFun;

    return SUCCESS;
}
#endif

/****************************************************************************/ /**
 * @brief  read int flag
 *
 * @param  intType: intType
 *
 * @return flag status
 *
*******************************************************************************/
BL_Sts_Type Audio_GetIntStatus(Audio_INT_Type intType)
{
    uint32_t tmpVal = 0;
    BL_Sts_Type rlt = RESET;

    CHECK_PARAM(IS_AUDIO_INT_TYPE(intType));

    switch (intType) {
        case AUDIO_INT_RX_FIFO_THR:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_RX_FIFO_STATUS);
            rlt = BL_IS_REG_BIT_SET(tmpVal, AUDIO_RXA_INT);
            break;
        case AUDIO_INT_RX_FIFO_OVERRUN:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_RX_FIFO_STATUS);
            rlt = BL_IS_REG_BIT_SET(tmpVal, AUDIO_RXO_INT);
            break;
        case AUDIO_INT_RX_FIFO_UNDERRUN:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_RX_FIFO_STATUS);
            rlt = BL_IS_REG_BIT_SET(tmpVal, AUDIO_RXU_INT);
            break;

        case AUDIO_INT_TX_FIFO_THR:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_TX_FIFO_STATUS);
            rlt = BL_IS_REG_BIT_SET(tmpVal, AUDIO_TXA_INT);
            break;
        case AUDIO_INT_TX_FIFO_OVERRUN:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_TX_FIFO_STATUS);
            rlt = BL_IS_REG_BIT_SET(tmpVal, AUDIO_TXO_INT);
            break;
        case AUDIO_INT_TX_FIFO_UNDERRUN:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_TX_FIFO_STATUS);
            rlt = BL_IS_REG_BIT_SET(tmpVal, AUDIO_TXU_INT);
            break;

        case AUDIO_INT_ADC0_SET_VOLUME_DONE:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_STATUS);
            rlt = BL_IS_REG_BIT_SET(tmpVal, AUDIO_ADC_S0_INT);
            break;
        case AUDIO_INT_ADC1_SET_VOLUME_DONE:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_STATUS);
            rlt = BL_IS_REG_BIT_SET(tmpVal, AUDIO_ADC_S1_INT);
            break;

        case AUDIO_INT_ADC2_SET_VOLUME_DONE:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_STATUS);
            rlt = BL_IS_REG_BIT_SET(tmpVal, AUDIO_ADC_S2_INT);
            break;
        case AUDIO_INT_DAC0_SET_VOLUME_DONE:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_STATUS);
            rlt = BL_IS_REG_BIT_SET(tmpVal, AUDIO_DAC_S0_INT);
            break;
        case AUDIO_INT_DAC1_SET_VOLUME_DONE:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_STATUS);
            rlt = BL_IS_REG_BIT_SET(tmpVal, AUDIO_DAC_S1_INT);
            break;
        case AUDIO_INT_VAD:
            tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_STATUS);
            rlt = BL_IS_REG_BIT_SET(tmpVal, AUDIO_VAD_INT);
            break;
        default:
            break;
    }

    return rlt;
}

/****************************************************************************/ /**
 * @brief  rx fifo flush
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void Audio_RxFifoClear(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_RX_FIFO_CTRL);
    tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_RX_FIFO_FLUSH);
    BL_WR_REG(AUDIO_BASE, AUDIO_RX_FIFO_CTRL, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Get Rx FIFO Count
 *
 * @param  None
 *
 * @return fifi count
 *
*******************************************************************************/
uint32_t Audio_GetRxFifoCount(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_RX_FIFO_STATUS);
    tmpVal = BL_GET_REG_BITS_VAL(tmpVal, AUDIO_RXA_CNT);

    return tmpVal;
}

/****************************************************************************/ /**
 * @brief  Read RX FIFO
 *
 * @param  None
 *
 * @return fifo data
 *
*******************************************************************************/
uint32_t Audio_ReadRxFifo(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_RX_FIFO_DATA);

    return tmpVal;
}

/****************************************************************************/ /**
 * @brief  tx fifo flush
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void Audio_TxFifoClear(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_TX_FIFO_CTRL);
    tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_TX_FIFO_FLUSH);
    BL_WR_REG(AUDIO_BASE, AUDIO_TX_FIFO_CTRL, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Get Tx FIFO Count
 *
 * @param  None
 *
 * @return fifi count
 *
*******************************************************************************/
uint32_t Audio_GetTxFifoCount(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_TX_FIFO_STATUS);
    tmpVal = BL_GET_REG_BITS_VAL(tmpVal, AUDIO_TXA_CNT);

    return tmpVal;
}

/****************************************************************************/ /**
 * @brief  Wirte TX FIFO
 *
 * @param  da: None
 *
 * @return fifo data
 *
*******************************************************************************/
void Audio_WriteTxFifo(uint32_t da)
{
    BL_WR_REG(AUDIO_BASE, AUDIO_TX_FIFO_DATA, da);
}

/****************************************************************************/ /**
 * @brief  Configure rx fifo
 *
 * @param  cfg: fifo cfg
 *
 * @return None
 *
*******************************************************************************/
void Audio_RxFifoConfig(Audio_FifoCfg_Type *cfg)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_RESOLUTION_TYPE(cfg->resolution));
    CHECK_PARAM(IS_AUDIO_FIFO_AILGN_MODE(cfg->ailgnMode));
    CHECK_PARAM(IS_AUDIO_FIFO_DQR_THRESHOLD_MODE(cfg->dmaThresholdMode));

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_RX_FIFO_CTRL);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_RX_DATA_RES, cfg->resolution);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_RX_DATA_MODE, cfg->ailgnMode);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_RX_DRQ_CNT, cfg->dmaThresholdMode);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_RX_TRG_LEVEL, cfg->FifoIntThreshold);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_RX_DRQ_EN, cfg->dmaEn);

    BL_WR_REG(AUDIO_BASE, AUDIO_RX_FIFO_CTRL, tmpVal);

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_AUD_ITF);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_ITF_EN, cfg->dmaEn);
    BL_WR_REG(AUDIO_BASE, AUDIO_AUD_ITF, tmpVal);
}

/****************************************************************************/ /**
 * @brief  enable rx fifo
 *
 * @param  ch: ch
 *
 * @return None
 *
*******************************************************************************/
void Audio_RxFifoEnable(uint8_t ch)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_RX_FIFO_CTRL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_RX_CH_EN, ch);
    BL_WR_REG(AUDIO_BASE, AUDIO_RX_FIFO_CTRL, tmpVal);
}

/****************************************************************************/ /**
 * @brief  disable rx fifo
 *
 * @param  ch: fifo cfg
 *
 * @return None
 *
*******************************************************************************/
void Audio_RxFifoDisable(uint8_t ch)
{
    uint32_t tmpVal = 0;
    uint32_t tmpVal2 = 0;

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_RX_FIFO_CTRL);
    tmpVal2 = BL_GET_REG_BITS_VAL(tmpVal, AUDIO_RX_CH_EN);

    tmpVal2 &= ~ch;

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_RX_CH_EN, tmpVal2);

    BL_WR_REG(AUDIO_BASE, AUDIO_RX_FIFO_CTRL, tmpVal);
}

/****************************************************************************/ /**
 * @brief  enable rx fifo
 *
 * @param  ch: ch
 *
 * @return None
 *
*******************************************************************************/
void Audio_TxFifoEnable(uint8_t ch)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_TX_FIFO_CTRL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_TX_CH_EN, ch);
    BL_WR_REG(AUDIO_BASE, AUDIO_TX_FIFO_CTRL, tmpVal);
}

/****************************************************************************/ /**
 * @brief  disable rx fifo
 *
 * @param  ch: fifo cfg
 *
 * @return None
 *
*******************************************************************************/
void Audio_TxFifoDisable(uint8_t ch)
{
    uint32_t tmpVal = 0;
    uint32_t tmpVal2 = 0;

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_TX_FIFO_CTRL);
    tmpVal2 = BL_GET_REG_BITS_VAL(tmpVal, AUDIO_TX_CH_EN);

    tmpVal2 &= ~ch;

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_TX_CH_EN, tmpVal2);

    BL_WR_REG(AUDIO_BASE, AUDIO_TX_FIFO_CTRL, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Get Tx FIFO Count
 *
 * @param  cfg: None
 *
 * @return None
 *
*******************************************************************************/
void Audio_TxFifoConfig(Audio_FifoCfg_Type *cfg)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_RESOLUTION_TYPE(cfg->resolution));
    CHECK_PARAM(IS_AUDIO_FIFO_AILGN_MODE(cfg->ailgnMode));
    CHECK_PARAM(IS_AUDIO_FIFO_DQR_THRESHOLD_MODE(cfg->dmaThresholdMode));

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_TX_FIFO_CTRL);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_TX_DATA_RES, cfg->resolution);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_TX_DATA_MODE, cfg->ailgnMode);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_TX_DRQ_CNT, cfg->dmaThresholdMode);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_TX_TRG_LEVEL, cfg->FifoIntThreshold);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_TX_DRQ_EN, cfg->dmaEn);

    BL_WR_REG(AUDIO_BASE, AUDIO_TX_FIFO_CTRL, tmpVal);

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_AUD_ITF);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_ITF_EN, cfg->dmaEn);
    BL_WR_REG(AUDIO_BASE, AUDIO_AUD_ITF, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Audio_PEQ_Config
 *
 * @param  peq_index: PEQ index should be in range[0,19]
 * @param  peqBypass: PEQ is bypass,if bypass b_pra and a_pra is vaild
 * @param  qtfm: PEQ qtfm
 * @param  b_pra: PEQ b_pra ,should be set as [19:0] arrary pointer which length is 3
 * @param  a_pra: PEQ a_bra ,should be set as [19:0] arrary pointer which length is 2
 *
 * @return PEQ Setting is success or not
 *
*******************************************************************************/
BL_Err_Type Audio_DAC_PEQ_Config(uint8_t peq_index, uint8_t peqBypass, Audio_PEQ_QTFM_Type qtfm, uint32_t *b_pra, uint32_t *a_pra)
{
    uint32_t tmpVal = 0;
    uint32_t peqAddr = 0;
    if (peq_index > 19) {
        return ERROR;
        /* PEQ only support [0,19] index */
    }
    peqAddr = AUDIO_BASE + 0x200 + (peq_index * 0x14);

    if (peqBypass == 0) {
        tmpVal = BL_RD_WORD(peqAddr);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_PEQ_00_B0, b_pra[0]);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_PEQ_00_QFMT, qtfm);

        BL_WR_WORD(peqAddr, tmpVal);

        BL_WR_WORD(peqAddr + 0x04, b_pra[1]);
        BL_WR_WORD(peqAddr + 0x08, b_pra[2]);
        BL_WR_WORD(peqAddr + 0x0c, a_pra[0]);
        BL_WR_WORD(peqAddr + 0x10, a_pra[1]);

        tmpVal = BL_RD_WORD(peqAddr);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_PEQ_00_BYP, peqBypass);
        BL_WR_WORD(peqAddr, tmpVal);

    } else {
        tmpVal = BL_RD_WORD(peqAddr);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_PEQ_00_BYP, peqBypass);
        BL_WR_WORD(peqAddr, tmpVal);
    }
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Audio_ADC_PEQ_Config
 *
 * @param  peq_index: PEQ index should be in range[0,19]
 * @param  peqBypass: PEQ is bypass,if bypass b_pra and a_pra is vaild
 * @param  qtfm: PEQ qtfm
 * @param  b_pra: PEQ b_pra ,should be set as [19:0] arrary pointer which length is 3
 * @param  a_pra: PEQ a_bra ,should be set as [19:0] arrary pointer which length is 2
 *
 * @return PEQ Setting is success or not
 *
*******************************************************************************/
BL_Err_Type Audio_ADC_PEQ_Config(uint8_t peq_index, Audio_ADC_ID_Type adcChannel, uint8_t peqBypass, Audio_PEQ_QTFM_Type qtfm, uint32_t *b_pra, uint32_t *a_pra)
{
    uint32_t tmpVal = 0;
    uint32_t peqAddr = 0;
    if (peq_index > 19) {
        return ERROR;
        /* PEQ only support [0,19] index */
    }
    peqAddr = AUDIO_BASE + 0x390 + (peq_index * 0x14);

    tmpVal = BL_RD_WORD(AUDIO_BASE + 0x390);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_PEQ_IN_SEL, adcChannel);
    BL_WR_WORD(peqAddr, tmpVal);

    if (peqBypass == 0) {
        tmpVal = BL_RD_WORD(peqAddr);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_PEQ_20_B0, b_pra[0]);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_PEQ_20_QFMT, qtfm);

        BL_WR_WORD(peqAddr, tmpVal);

        BL_WR_WORD(peqAddr + 0x04, b_pra[1]);
        BL_WR_WORD(peqAddr + 0x08, b_pra[2]);
        BL_WR_WORD(peqAddr + 0x0c, a_pra[0]);
        BL_WR_WORD(peqAddr + 0x10, a_pra[1]);

        tmpVal = BL_RD_WORD(peqAddr);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_PEQ_20_BYP, peqBypass);
        BL_WR_WORD(peqAddr, tmpVal);

    } else {
        tmpVal = BL_RD_WORD(peqAddr);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_PEQ_20_BYP, peqBypass);
        BL_WR_WORD(peqAddr, tmpVal);
    }
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Audio adc Mute
 *
 * @param  muteSyncAllAdc: mute Sync All ADC Channle
 * @param  adc_id: adc id
 * @param  mute: Mute Or Not
 *
 * @return success or not
 *
*******************************************************************************/
BL_Err_Type Audio_ADC_Set_Mute(BL_Fun_Type muteSyncAllAdc, Audio_ADC_ID_Type adc_id, Audio_Mute_Type mute)
{
    uint32_t tmpVal = 0;
    uint32_t adcVolumeConfigAddrOffset = AUDIO_BASE + 0x408 + adc_id * 0x08;

    CHECK_PARAM(IS_AUDIO_ADC_ID_TYPE(adc_id));
    CHECK_PARAM(IS_AUDIO_MUTE_TYPE(mute));

    if (muteSyncAllAdc) {
        tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_ADC_S0_MISC);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_S012_MUTE, mute);
        BL_WR_REG(AUDIO_BASE, AUDIO_ADC_S0_MISC, tmpVal);
    } else {
        if (adc_id > 2) {
            return ERROR;
            /*only support 3 adc*/
        }

        tmpVal = BL_RD_WORD(adcVolumeConfigAddrOffset);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_S0_MUTE, mute);
        BL_WR_WORD(adcVolumeConfigAddrOffset, tmpVal);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Audio adc Mute
 *
 * @param  muteSyncAllDac: mute Sync All DAC Channle
 * @param  dac_id: dac id
 * @param  mute: Mute Or Not
 *
 * @return None
 *
*******************************************************************************/
BL_Err_Type Audio_DAC_Set_Mute(BL_Fun_Type muteSyncAllDac, Audio_DAC_ID_Type dac_id, Audio_Mute_Type mute)
{
    uint32_t tmpVal = 0;
    uint32_t dacVolumeConfigAddrOffset = AUDIO_BASE + 0x434 + dac_id * 0x08;

    CHECK_PARAM(IS_AUDIO_ADC_ID_TYPE(dac_id));
    CHECK_PARAM(IS_AUDIO_MUTE_TYPE(Mute));

    if (muteSyncAllDac) {
        tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_DAC_S0_MISC);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_S01_MUTE, mute);
        BL_WR_REG(AUDIO_BASE, AUDIO_DAC_S0_MISC, tmpVal);
    } else {
        if (dac_id > 1) {
            return ERROR;
            /*only support 2 dac*/
        }

        tmpVal = BL_RD_WORD(dacVolumeConfigAddrOffset);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_S0_MUTE, mute);
        BL_WR_WORD(dacVolumeConfigAddrOffset, tmpVal);
    }

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Audio adc Volume Config
 *
 * @param  adc_id: adc id
 * @param  cfg: volume config cfg pointer
 *
 * @return None
 *
*******************************************************************************/
BL_Err_Type Audio_ADC_Software_Volume_Config(Audio_ADC_ID_Type adc_id, Audio_Volume_Cfg_Type *cfg)
{
    uint32_t adcVolumeConfigAddrOffset = AUDIO_BASE + 0x408 + adc_id * 0x08;
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_ADC_ID_TYPE(adc_id));
    CHECK_PARAM(IS_AUDIO_MUTE_MODE(cfg->muteMode));
    CHECK_PARAM(IS_AUDIO_RAMP_RATE_TYPE(cfg->muteRmpdnRate));
    CHECK_PARAM(IS_AUDIO_RAMP_RATE_TYPE(cfg->muteRmpupRate));
    CHECK_PARAM(IS_AUDIO_VOLUME_CTR_MODE(cfg->volumeCtrMode));
    CHECK_PARAM(IS_AUDIO_ZERO_CROSS_RATE_TYPE(cfg->resovolumeZeroCrossRatelution));
    CHECK_PARAM(IS_AUDIO_RAMP_RATE_TYPE(cfg->volumeRmpRate));

    if (adc_id > 2) {
        return ERROR;
        /*only support 3 adc*/
    }

    tmpVal = BL_RD_WORD(adcVolumeConfigAddrOffset);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_S0_MUTE_SOFTMODE, cfg->muteMode);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_S0_MUTE_RMPDN_RATE, cfg->muteRmpdnRate);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_S0_MUTE_RMPUP_RATE, cfg->muteRmpupRate);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_S0_CTRL_MODE, cfg->volumeCtrMode);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_S0_CTRL_ZCD_RATE, cfg->volumeZeroCrossRate);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_S0_CTRL_RMP_RATE, cfg->volumeRmpRate);
    BL_WR_WORD(adcVolumeConfigAddrOffset, tmpVal);

    tmpVal = BL_RD_WORD(adcVolumeConfigAddrOffset + 0x04);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_S0_CTRL_ZCD_TIMEOUT, cfg->volumeZeroCrossTimeout);
    BL_WR_WORD(adcVolumeConfigAddrOffset + 0x04, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Audio DAC Volume Config
 *
 * @param  dac_id: dac id
 * @param  cfg: volume config cfg pointer
 *
 * @return None
 *
*******************************************************************************/
BL_Err_Type Audio_DAC_Software_Volume_Config(Audio_DAC_ID_Type dac_id, Audio_Volume_Cfg_Type *cfg)
{
    uint32_t dacVolumeConfigAddrOffset = AUDIO_BASE + 0x434 + dac_id * 0x08;
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_DAC_ID_TYPE(dac_id));
    CHECK_PARAM(IS_AUDIO_MUTE_MODE(cfg->muteMode));
    CHECK_PARAM(IS_AUDIO_RAMP_RATE_TYPE(cfg->muteRmpdnRate));
    CHECK_PARAM(IS_AUDIO_RAMP_RATE_TYPE(cfg->muteRmpupRate));
    CHECK_PARAM(IS_AUDIO_VOLUME_CTR_MODE(cfg->volumeCtrMode));
    CHECK_PARAM(IS_AUDIO_ZERO_CROSS_RATE_TYPE(cfg->resovolumeZeroCrossRatelution));
    CHECK_PARAM(IS_AUDIO_RAMP_RATE_TYPE(cfg->volumeRmpRate));

    if (dac_id > 1) {
        return ERROR;
        /*only support 2 dac*/
    }

    tmpVal = BL_RD_WORD(dacVolumeConfigAddrOffset);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_S0_MUTE_SOFTMODE, cfg->muteMode);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_S0_MUTE_RMPDN_RATE, cfg->muteRmpdnRate);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_S0_MUTE_RMPUP_RATE, cfg->muteRmpupRate);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_S0_CTRL_MODE, cfg->volumeCtrMode);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_S0_CTRL_ZCD_RATE, cfg->volumeZeroCrossRate);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_S0_CTRL_RMP_RATE, cfg->volumeRmpRate);
    BL_WR_WORD(dacVolumeConfigAddrOffset, tmpVal);

    tmpVal = BL_RD_WORD(dacVolumeConfigAddrOffset + 0x04);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_S0_CTRL_ZCD_TIMEOUT, cfg->volumeZeroCrossTimeout);
    BL_WR_WORD(dacVolumeConfigAddrOffset + 0x04, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Audio set adc volume
 *
 * @param  volumeSyncAllAdc: sync volume configuration for three adc channel
 * @param  adc_id: adc id
 * @param  volume: volume
 *
 * @return None
 *
*******************************************************************************/
BL_Err_Type Audio_ADC_Set_Volume(BL_Fun_Type volumeSyncAllAdc, Audio_ADC_ID_Type adc_id, uint16_t volume)
{
    uint32_t adcVolumeAddrOffset = AUDIO_BASE + 0x408 + adc_id * 0x08;
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_ADC_ID_TYPE(adc_id));

    if (adc_id > 2) {
        return ERROR;
        /*only support 3 adc*/
    }

    if (volumeSyncAllAdc) {
        tmpVal = BL_RD_WORD(AUDIO_BASE + 0x408);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_S0_VOLUME, volume);
        BL_WR_WORD(AUDIO_BASE + 0x408, tmpVal);

        tmpVal = BL_RD_WORD(AUDIO_BASE + 0x410);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_S1_VOLUME, volume);
        BL_WR_WORD(AUDIO_BASE + 0x410, tmpVal);

        tmpVal = BL_RD_WORD(AUDIO_BASE + 0x418);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_S2_VOLUME, volume);
        BL_WR_WORD(AUDIO_BASE + 0x418, tmpVal);

        tmpVal = BL_RD_WORD(AUDIO_BASE + 0x408 + 0x04);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_S012_VOLUME_UPDATE, 1);
        BL_WR_WORD(AUDIO_BASE + 0x408 + 0x04, tmpVal);

        //TODO AUDIO_ADC_SX_VOLUME_UPDATE/AUDIO_ADC_S012_VOLUME_UPDATE should be reset in isr

    } else {
        tmpVal = BL_RD_WORD(adcVolumeAddrOffset);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_S0_VOLUME, volume);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_S0_VOLUME_UPDATE, 1);
        BL_WR_WORD(adcVolumeAddrOffset, tmpVal);

        //TODO AUDIO_ADC_SX_VOLUME_UPDATE/AUDIO_ADC_S012_VOLUME_UPDATE should be reset in isr
    }
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Audio set dac volume
 *
 * @param  volumeSyncAllDac: sync volume configuration for two dac channel
 * @param  dac_id: dac id
 * @param  volume: volume
 *
 * @return None
 *
*******************************************************************************/
BL_Err_Type Audio_DAC_Set_Volume(BL_Fun_Type volumeSyncAllDac, Audio_DAC_ID_Type dac_id, uint16_t volume)
{
    uint32_t dacVolumeConfigAddrOffset = AUDIO_BASE + 0x434 + dac_id * 0x08;
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_DAC_ID_TYPE(dac_id));

    if (dac_id > 1) {
        return ERROR;
        /*only support 2 dac*/
    }

    if (volumeSyncAllDac) {
        tmpVal = BL_RD_WORD(AUDIO_BASE + 0x434);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_S0_VOLUME, volume);
        BL_WR_WORD(AUDIO_BASE + 0x434, tmpVal);

        tmpVal = BL_RD_WORD(AUDIO_BASE + 0x43c);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_S1_VOLUME, volume);
        BL_WR_WORD(AUDIO_BASE + 0x43c, tmpVal);

        tmpVal = BL_RD_WORD(AUDIO_BASE + 0x434 + 0x04);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_S01_VOLUME_UPDATE, 1);
        BL_WR_WORD(AUDIO_BASE + 0x434 + 0x04, tmpVal);

        //TODO AUDIO_DAC_SX_VOLUME_UPDATE/AUDIO_DAC_S01_VOLUME_UPDATE should be reset in isr

    } else {
        tmpVal = BL_RD_WORD(dacVolumeConfigAddrOffset);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_S0_VOLUME, volume);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_S0_VOLUME_UPDATE, 1);
        BL_WR_WORD(dacVolumeConfigAddrOffset, tmpVal);

        //TODO AUDIO_DAC_SX_VOLUME_UPDATE/AUDIO_DAC_S01_VOLUME_UPDATE should be reset in isr
    }
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  clear adc update bit
 *
 * @param  adc_id: adc id
 *
 * @return None
 *
*******************************************************************************/
void Audio_ADC_Reset_Volume_Update(Audio_ADC_ID_Type adc_id)
{
    uint32_t adcVolumeAddrOffset = AUDIO_BASE + 0x408 + adc_id * 0x08;
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_ADC_ID_TYPE(adc_id));

    if (adc_id > 2) {
        return;
        /*only support 3 adc*/
    }

    tmpVal = BL_RD_WORD(adcVolumeAddrOffset);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_S0_VOLUME, 0);
    BL_WR_WORD(adcVolumeAddrOffset, tmpVal);
}

/****************************************************************************/ /**
 * @brief  clear dac update bit
 *
 * @param  dac_id: dac id
 *
 * @return None
 *
*******************************************************************************/
void Audio_DAC_Reset_Volume_Update(Audio_DAC_ID_Type dac_id)
{
    uint32_t dacVolumeConfigAddrOffset = AUDIO_BASE + 0x434 + dac_id * 0x08;
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_DAC_ID_TYPE(dac_id));

    if (dac_id > 1) {
        return;
        /*only support 2 dac*/
    }

    tmpVal = BL_RD_WORD(dacVolumeConfigAddrOffset);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_S0_VOLUME, 0);
    BL_WR_WORD(dacVolumeConfigAddrOffset, tmpVal);
}

/****************************************************************************/ /**
 * @brief  clear adc or dac all update bit, when enable sync bit to set all channel dac/adc volume
 *         ,user should use this function to clear all update flag.
 *
 * @param  isAdcOrDac: IS ADC or DAC,ADC=1 DAC=0
 *
 * @return None
 *
*******************************************************************************/
void Audio_Reset_Volume_All_Update(uint8_t isAdcOrDac)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_ADC_ID_TYPE(adc_id));
    if (isAdcOrDac) {
        BL_RD_REG(AUDIO_BASE, AUDIO_ADC_S0_MISC);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_S012_VOLUME_UPDATE, 0);
        BL_WR_REG(AUDIO_BASE, AUDIO_ADC_S0_MISC, tmpVal);
    } else {
        BL_RD_REG(AUDIO_BASE, AUDIO_DAC_S0_MISC);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_S01_VOLUME_UPDATE, 0);
        BL_WR_REG(AUDIO_BASE, AUDIO_DAC_S0_MISC, tmpVal);
    }
}

/****************************************************************************/ /**
 * @brief  Audio set all adc volume Reg Without seting update bit
 *
 * @param  volumeSyncAllAdc: is set all adc
 * @param  adc_id: adc id
 * @param  volume: volume
 *
 * @return Success or Not
 *
*******************************************************************************/
BL_Err_Type Audio_ADC_Set_Volume_Reg(BL_Fun_Type volumeSyncAllAdc, Audio_ADC_ID_Type adc_id, uint16_t volume)
{
    uint32_t adcVolumeAddrOffset = AUDIO_BASE + 0x408 + adc_id * 0x08;
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_ADC_ID_TYPE(adc_id));

    if (adc_id > 2) {
        return ERROR;
        /*only support 3 adc*/
    }

    if (volumeSyncAllAdc) {
        tmpVal = BL_RD_WORD(AUDIO_BASE + 0x408);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_S0_VOLUME, volume);
        BL_WR_WORD(AUDIO_BASE + 0x408, tmpVal);

        tmpVal = BL_RD_WORD(AUDIO_BASE + 0x410);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_S1_VOLUME, volume);
        BL_WR_WORD(AUDIO_BASE + 0x410, tmpVal);

        tmpVal = BL_RD_WORD(AUDIO_BASE + 0x418);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_S2_VOLUME, volume);
        BL_WR_WORD(AUDIO_BASE + 0x418, tmpVal);

    } else {
        tmpVal = BL_RD_WORD(adcVolumeAddrOffset);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_S0_VOLUME, volume);
        BL_WR_WORD(adcVolumeAddrOffset, tmpVal);
    }
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Audio set all DAC volume Reg Without seting update bit
 *
 * @param  volumeSyncAllDac: is set all dac
 * @param  dac_id: dac id
 * @param  volume: volume
 *
 * @return Success or Not
 *
*******************************************************************************/
BL_Err_Type Audio_DAC_Set_Volume_Reg(BL_Fun_Type volumeSyncAllDac, Audio_DAC_ID_Type dac_id, uint16_t volume)
{
    uint32_t dacVolumeConfigAddrOffset = AUDIO_BASE + 0x434 + dac_id * 0x08;
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_DAC_ID_TYPE(dac_id));

    if (dac_id > 1) {
        return ERROR;
        /*only support 2 dac*/
    }

    if (volumeSyncAllDac) {
        tmpVal = BL_RD_WORD(AUDIO_BASE + 0x434);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_S0_VOLUME, volume);
        BL_WR_WORD(AUDIO_BASE + 0x434, tmpVal);

        tmpVal = BL_RD_WORD(AUDIO_BASE + 0x43c);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_S1_VOLUME, volume);
        BL_WR_WORD(AUDIO_BASE + 0x43c, tmpVal);

    } else {
        tmpVal = BL_RD_WORD(dacVolumeConfigAddrOffset);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_S0_VOLUME, volume);
        BL_WR_WORD(dacVolumeConfigAddrOffset, tmpVal);
    }
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Audio set adc volume
 *
 * @param  volumeSyncAllAdc: sync volume configuration for three adc channel,This function will
 *                           blocking CPU until volume adjust task done
 * @param  adc_id: adc id
 * @param  volume: volume
 * @param  blockTimeout: volume block timeout
 *
 * @return Configuration is success
 *
*******************************************************************************/
BL_Err_Type Audio_ADC_Set_Volume_Block(BL_Fun_Type volumeSyncAllAdc, Audio_ADC_ID_Type adc_id, uint16_t volume, uint32_t blockTimeout)
{
    uint32_t adcVolumeAddrOffset = AUDIO_BASE + 0x408 + adc_id * 0x08;
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_ADC_ID_TYPE(adc_id));

    if (adc_id > 2) {
        return ERROR;
        /*only support 3 adc*/
    }

    if (volumeSyncAllAdc) {
        tmpVal = BL_RD_WORD(AUDIO_BASE + 0x408);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_S0_VOLUME, volume);
        BL_WR_WORD(AUDIO_BASE + 0x408, tmpVal);

        tmpVal = BL_RD_WORD(AUDIO_BASE + 0x410);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_S1_VOLUME, volume);
        BL_WR_WORD(AUDIO_BASE + 0x410, tmpVal);

        tmpVal = BL_RD_WORD(AUDIO_BASE + 0x418);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_S2_VOLUME, volume);
        BL_WR_WORD(AUDIO_BASE + 0x418, tmpVal);

        tmpVal = BL_RD_WORD(AUDIO_BASE + 0x408 + 0x04);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_S012_VOLUME_UPDATE, 1);
        BL_WR_WORD(AUDIO_BASE + 0x408 + 0x04, tmpVal);

        while (Audio_IS_ADC_Volume_Set_Busy(AUDIO_ADC_0) && Audio_IS_ADC_Volume_Set_Busy(AUDIO_ADC_1) && Audio_IS_ADC_Volume_Set_Busy(AUDIO_ADC_2)) {
            blockTimeout--;
            if (blockTimeout) {
                return TIMEOUT;
            }
        }
        //clear update
        tmpVal = BL_RD_WORD(adcVolumeAddrOffset);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_S012_VOLUME_UPDATE, 0);
        BL_WR_WORD(adcVolumeAddrOffset, tmpVal);

    } else {
        tmpVal = BL_RD_WORD(adcVolumeAddrOffset);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_S0_VOLUME, volume);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_S0_VOLUME_UPDATE, 1);
        BL_WR_WORD(adcVolumeAddrOffset, tmpVal);

        while (Audio_IS_ADC_Volume_Set_Busy(adc_id)) {
            blockTimeout--;
            if (blockTimeout) {
                return TIMEOUT;
            }
        }
        //clear update
        tmpVal = BL_RD_WORD(adcVolumeAddrOffset);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_S0_VOLUME_UPDATE, 0);
        BL_WR_WORD(adcVolumeAddrOffset, tmpVal);
    }
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Audio set dac volume
 *
 * @param  volumeSyncAllDac: sync volume configuration for two dac channel ,This function will
 *                           blocking CPU until volume adjust task done
 * @param  dac_id: adc id
 * @param  volume: volume
 * @param  blockTimeout: volume block timeout
 *
 * @return is success or not
 *
*******************************************************************************/
BL_Err_Type Audio_DAC_Set_Volume_Block(BL_Fun_Type volumeSyncAllDac, Audio_DAC_ID_Type dac_id, uint16_t volume, uint32_t blockTimeout)
{
    uint32_t dacVolumeConfigAddrOffset = AUDIO_BASE + 0x434 + dac_id * 0x08;
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_DAC_ID_TYPE(dac_id));

    if (dac_id > 1) {
        return ERROR;
        /*only support 2 dac*/
    }

    if (volumeSyncAllDac) {
        tmpVal = BL_RD_WORD(AUDIO_BASE + 0x434);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_S0_VOLUME, volume);
        BL_WR_WORD(AUDIO_BASE + 0x434, tmpVal);

        tmpVal = BL_RD_WORD(AUDIO_BASE + 0x43c);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_S1_VOLUME, volume);
        BL_WR_WORD(AUDIO_BASE + 0x43c, tmpVal);

        tmpVal = BL_RD_WORD(AUDIO_BASE + 0x434 + 0x04);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_S01_VOLUME_UPDATE, 1);
        BL_WR_WORD(AUDIO_BASE + 0x434 + 0x04, tmpVal);

        while (Audio_IS_DAC_Volume_Set_Busy(AUDIO_DAC_0) && Audio_IS_DAC_Volume_Set_Busy(AUDIO_DAC_1)) {
            blockTimeout--;
            if (blockTimeout) {
                return TIMEOUT;
            }
        }
        //clear update
        tmpVal = BL_RD_WORD(dacVolumeConfigAddrOffset);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_S01_VOLUME_UPDATE, 0);
        BL_WR_WORD(dacVolumeConfigAddrOffset, tmpVal);

    } else {
        tmpVal = BL_RD_WORD(dacVolumeConfigAddrOffset);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_S0_VOLUME, volume);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_S0_VOLUME_UPDATE, 1);
        BL_WR_WORD(dacVolumeConfigAddrOffset, tmpVal);

        //TODO AUDIO_DAC_SX_VOLUME_UPDATE/AUDIO_DAC_S01_VOLUME_UPDATE should be reset in isr
    }
    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  Audio set adc agc hardware volume config
 *
 * @param  cfg: cfg pointer
 *
 * @return None
 *
*******************************************************************************/
BL_Err_Type Audio_ADC_Hardware_Volume_Config(Audio_Volume_Cfg_Type *cfg)
{
    uint32_t adcVolumeConfigAddrOffset = AUDIO_BASE + AUDIO_ADC_H_OFFSET;
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_MUTE_MODE(cfg->muteMode));
    CHECK_PARAM(IS_AUDIO_RAMP_RATE_TYPE(cfg->muteRmpdnRate));
    CHECK_PARAM(IS_AUDIO_RAMP_RATE_TYPE(cfg->muteRmpupRate));
    CHECK_PARAM(IS_AUDIO_VOLUME_CTR_MODE(cfg->volumeCtrMode));
    CHECK_PARAM(IS_AUDIO_ZERO_CROSS_RATE_TYPE(cfg->resovolumeZeroCrossRatelution));
    CHECK_PARAM(IS_AUDIO_RAMP_RATE_TYPE(cfg->volumeRmpRate));

    tmpVal = BL_RD_WORD(adcVolumeConfigAddrOffset);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_H_MUTE, cfg->muteMode);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_H_MUTE_RMPDN_RATE, cfg->muteRmpdnRate);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_H_MUTE_RMPUP_RATE, cfg->muteRmpupRate);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_H_CTRL_MODE, cfg->volumeCtrMode);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_H_CTRL_ZCD_RATE, cfg->volumeZeroCrossRate);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_H_CTRL_RMP_RATE, cfg->volumeRmpRate);
    BL_WR_WORD(adcVolumeConfigAddrOffset, tmpVal);

    tmpVal = BL_RD_WORD(adcVolumeConfigAddrOffset + 0x04);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_H_CTRL_ZCD_TIMEOUT, cfg->volumeZeroCrossTimeout);
    BL_WR_WORD(adcVolumeConfigAddrOffset + 0x04, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  when AGC is enable , software cannot change volume,but can read AGC ctrl result by this
 *         function
 *
 * @param  None
 *
 * @return AGC ctr result
 *
*******************************************************************************/
uint16_t Audio_ADC_Get_Hardware_Volume(void)
{
    uint32_t tmpVal = 0;
    uint16_t volume = 0;

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_ADC_H);
    volume = BL_GET_REG_BITS_VAL(tmpVal, AUDIO_ADC_H_VOLUME);

    return volume;
}

/****************************************************************************/ /**
 * @brief  when AGC is enable , software cannot change volume,but can read AGC ctrl result by this
 *         function
 *
 * @param  adc_id: adc id
 *
 * @return adc volume
 *
*******************************************************************************/
uint16_t Audio_ADC_Get_Volume(Audio_ADC_ID_Type adc_id)
{
    uint32_t tmpVal = 0;
    uint16_t volume = 0;

    if (adc_id == AUDIO_ADC_0) {
        tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_ADC_S0);
    } else if (adc_id == AUDIO_ADC_1) {
        tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_ADC_S1);
    } else {
        tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_ADC_S2);
    }

    volume = BL_GET_REG_BITS_VAL(tmpVal, AUDIO_ADC_S0_VOLUME);

    return volume;
}

/****************************************************************************/ /**
 * @brief  when AGC is enable , software cannot change volume,but can read AGC ctrl result by this
 *         function
 *
 * @param  dac_id: dac id
 *
 * @return dac volume
 *
*******************************************************************************/
uint16_t Audio_DAC_Get_Volume(Audio_DAC_ID_Type dac_id)
{
    uint32_t tmpVal = 0;

    if (dac_id == AUDIO_DAC_0) {
        tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_DAC_S0);
    } else {
        tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_DAC_S1);
    }

    tmpVal = BL_GET_REG_BITS_VAL(tmpVal, AUDIO_DAC_S0_VOLUME);

    return tmpVal;
}

/****************************************************************************/ /**
 * @brief  is audio mute done or not .
 *
 * @param  adc_id: adc id
 *
 * @return is adc mute done
 *
*******************************************************************************/
BL_Sts_Type Audio_IS_ADC_Mute_Done(Audio_ADC_ID_Type adc_id)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_ADC_ID_TYPE(adc_id));

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_STATUS);

    if (adc_id == AUDIO_ADC_0) {
        return BL_IS_REG_BIT_SET(tmpVal, AUDIO_ADC_H0_MUTE_DONE);
    } else if (adc_id == AUDIO_ADC_1) {
        return BL_IS_REG_BIT_SET(tmpVal, AUDIO_ADC_H1_MUTE_DONE);
    } else {
        return BL_IS_REG_BIT_SET(tmpVal, AUDIO_ADC_H2_MUTE_DONE);
    }
}

/****************************************************************************/ /**
 * @brief  is audio mute & volume set are busy or not .
 *
 * @param  adc_id: adc id
 *
 * @return is adc volume set done
 *
*******************************************************************************/
BL_Sts_Type Audio_IS_ADC_Volume_Set_Busy(Audio_ADC_ID_Type adc_id)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_ADC_ID_TYPE(adc_id));

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_STATUS);

    if (adc_id == AUDIO_ADC_0) {
        return BL_IS_REG_BIT_SET(tmpVal, AUDIO_ADC_H0_BUSY);
    } else if (adc_id == AUDIO_ADC_1) {
        return BL_IS_REG_BIT_SET(tmpVal, AUDIO_ADC_H1_BUSY);
    } else {
        return BL_IS_REG_BIT_SET(tmpVal, AUDIO_ADC_H2_BUSY);
    }
}

/****************************************************************************/ /**
 * @brief  is audio mute done or not .
 *
 * @param  dac_id: dac id
 *
 * @return is dac mute done
 *
*******************************************************************************/
BL_Sts_Type Audio_IS_DAC_Mute_Set_Done(Audio_DAC_ID_Type dac_id)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_ADC_ID_TYPE(dac_id));

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_STATUS);

    if (dac_id == AUDIO_DAC_0) {
        return BL_IS_REG_BIT_SET(tmpVal, AUDIO_DAC_H0_MUTE_DONE);
    } else {
        return BL_IS_REG_BIT_SET(tmpVal, AUDIO_DAC_H1_MUTE_DONE);
    }
}

/****************************************************************************/ /**
 * @brief  is audio mute & volume set are busy or not .
 *
 * @param  dac_id: dac id
 *
 * @return is dac_id done
 *
*******************************************************************************/
BL_Sts_Type Audio_IS_DAC_Volume_Set_Busy(Audio_DAC_ID_Type dac_id)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_ADC_ID_TYPE(dac_id));

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_STATUS);

    if (dac_id == AUDIO_DAC_0) {
        return BL_IS_REG_BIT_SET(tmpVal, AUDIO_DAC_H0_BUSY);
    } else {
        return BL_IS_REG_BIT_SET(tmpVal, AUDIO_DAC_H1_BUSY);
    }
}

/****************************************************************************/ /**
 * @brief  is audio mute & volume set are busy or not .
 *
 * @param  enable: enable agc
 * @param  cfg: agc cfg
 *
 * @return None
 *
*******************************************************************************/
void Audio_AGC_Init(uint8_t enable, Audio_AGC_Config_Type *cfg)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_AGC_SRC_TYPE(cfg->agc_src_select));
    CHECK_PARAM(IS_AUDIO_AGC_DETECT_MODE(cfg->agc_detect_mode));

    if (enable) {
        tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_ADC_AGC_0);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_AGC_EN, 0);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AGC_FORCE_GAIN_EN, cfg->agc_force_gain_en);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AGC_FORCE_GAIN_IND, cfg->agc_force_gain_ind);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AGC_MAX_GAIN_QDB, cfg->agc_max_gain_qdb);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AGC_MIN_GAIN_QDB, cfg->agc_min_gain_qdb);
        BL_WR_REG(AUDIO_BASE, AUDIO_ADC_AGC_0, tmpVal);

        tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_ADC_AGC_1);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AGC_LEVEL_TARGET, cfg->agc_level_target);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AGC_LEVEL_HYST_ATTACK, cfg->agc_level_hyst_attack);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AGC_LEVEL_HYST_DECAY, cfg->agc_level_hyst_decay);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AGC_HOLD_TIME_MS, cfg->agc_hold_time_ms);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AGC_DECAY_TIME_MS, cfg->agc_decay_time_ms);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AGC_ATTACK_TIME_MS, cfg->agc_attack_time_ms);
        //tmpVal = BL_SET_REG_BITS_VAL(tmpVal,AUDIO_ADC3_PGA_HW_CTRL,cfg->adc3_pga_hw_ctrl); //TODO
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC2_PGA_HW_CTRL, cfg->adc2_pga_hw_ctrl);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC1_PGA_HW_CTRL, cfg->adc1_pga_hw_ctrl);
        BL_WR_REG(AUDIO_BASE, AUDIO_ADC_AGC_1, tmpVal);

        tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_ADC_AGC_2);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AGC_NOISE_GATE_TH, cfg->agc_noise_gate_th);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AGC_NOISE_GATE_HYST, cfg->agc_noise_gate_hyst);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AGC_SILENCE_GAIN_QDB, cfg->agc_silence_gain_qdb);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AGC_SILENCE_GAIN_WAIT_MS, cfg->agc_silence_gain_wait_ms);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AGC_NOISE_ENTER_TIME_MS, cfg->agc_noise_enter_time_ms);
        BL_WR_REG(AUDIO_BASE, AUDIO_ADC_AGC_2, tmpVal);

        tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_ADC_AGC_3);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AGC_NOISE_EXIT_TIME_MS, cfg->agc_noise_exit_time_ms);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AGC_DBV_SETTLE_TIME, cfg->agc_dbv_settle_time);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AGC_SRC_SELECT, cfg->agc_src_select);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AGC_DETECT_MODE, cfg->agc_detect_mode);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AGC_ATTACK_TIME, cfg->agc_attack_time);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AGC_RELEASE_TIME, cfg->agc_release_time);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AGC_AVERAGE_TIME, cfg->agc_average_time);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_AGC_PGA_CTRL_EN, cfg->agc_pga_ctrl_en);
        BL_WR_REG(AUDIO_BASE, AUDIO_ADC_AGC_3, tmpVal);

        tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_ADC_AGC_0);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_AGC_EN, 1);
        BL_WR_REG(AUDIO_BASE, AUDIO_ADC_AGC_0, tmpVal);

    } else {
        tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_ADC_AGC_0);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_AGC_EN, 0);
        BL_WR_REG(AUDIO_BASE, AUDIO_ADC_AGC_0, tmpVal);
    }
}

/****************************************************************************/ /**
 * @brief  is audio mute & volume set are busy or not .
 *
 * @param  enable: enable drc
 * @param  cfg: drc cfg
 *
 * @return None
 *
*******************************************************************************/
void Audio_DRC_Init(uint8_t enable, Audio_DRC_Config_Type *cfg)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_DRC_DATA_TYPE(cfg->drc_raw_sel));
    CHECK_PARAM(IS_AUDIO_DRC_DATA_TYPE(cfg->drc_peak_sel));
    CHECK_PARAM(IS_AUDIO_DRC_DATA_TYPE(cfg->drc_avg_sel));
    CHECK_PARAM(IS_AUDIO_DRC_DATA_TYPE(cfg->ngt_src_sel));

    if (enable) {
        tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_DAC_DRC_0);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DRC_EN, 0);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DRC_RAW_SEL, cfg->drc_raw_sel);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DRC_PEAK_SEL, cfg->drc_peak_sel);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DRC_AVG_SEL, cfg->drc_avg_sel);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DRC_AVG_EN, cfg->drc_avg_en);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DRC_AVG_TIME, cfg->drc_avg_time);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DRC_ATT_TIME, cfg->drc_att_time);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DRC_RLS_TIME, cfg->drc_rls_time);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DRC_NGT_DOWNSAMPLE_EN, cfg->drc_ngt_downsample_en);
        BL_WR_REG(AUDIO_BASE, AUDIO_DAC_DRC_0, tmpVal);

        tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_DAC_DRC_1);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DRC_THRESHOLD_L, cfg->drc_threshold_l);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DRC_THRESHOLD_C, cfg->drc_threshold_c);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DRC_THRESHOLD_E, cfg->drc_threshold_e);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DRC_SLOPE_MODE_C, cfg->drc_slope_mode_c);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DRC_SLOPE_MODE_E, cfg->drc_slope_mode_e);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DRC_MAKEUP_GAIN, cfg->drc_makeup_gain);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DRC_ATTACK_TIME, cfg->drc_attack_time);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DRC_RELEASE_TIME, cfg->drc_release_time);
        BL_WR_REG(AUDIO_BASE, AUDIO_DAC_DRC_1, tmpVal);

        tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_DAC_NGT_0);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_NGT_EN, cfg->ngt_en);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_NGT_SRC_SEL, cfg->ngt_src_sel);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_NGT_AVG_TIME, cfg->ngt_avg_time);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_NGT_THRESHOLD, cfg->ngt_threshold);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_NGT_HYSTERESIS, cfg->ngt_hysteresis);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_NGT_NOISE_HOLD_EN, cfg->ngt_noise_hold_en);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_NGT_NOISE_HOLD_TIME_K, cfg->ngt_noise_hold_time_k);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_NGT_SIGNAL_HOLD_EN, cfg->ngt_signal_hold_en);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_NGT_SIGNAL_HOLD_TIME_K, cfg->ngt_signal_hold_time_k);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_NGT_DMUTE_ON, cfg->ngt_dmute_on);
        BL_WR_REG(AUDIO_BASE, AUDIO_DAC_NGT_0, tmpVal);

        tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_DAC_ZD_0);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ZD_EN, cfg->zd_en);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ZD_TIME, cfg->zd_time);
        BL_WR_REG(AUDIO_BASE, AUDIO_DAC_ZD_0, tmpVal);

        tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_DAC_DRC_0);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DRC_EN, 1);
        BL_WR_REG(AUDIO_BASE, AUDIO_DAC_DRC_0, tmpVal);

    } else {
        tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_DAC_DRC_0);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DRC_EN, 0);
        BL_WR_REG(AUDIO_BASE, AUDIO_DAC_DRC_0, tmpVal);
    }
}

/****************************************************************************/ /**
 * @brief  Audio interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void AUDIO_IRQHandler(void)
{
    uint8_t intIndex = 0;

    for (intIndex = 0; intIndex < AUDIO_INT_NUM_ALL; intIndex++) {
        if (Audio_GetIntStatus(intIndex) == SET) {
            if (audioIntCbfArra[intIndex] != NULL) {
                audioIntCbfArra[intIndex]();
            }
            Auido_IntClear(intIndex);
        }
    }
}
#endif

/****************************************************************************/ /**
 * @brief  Audio Clock Initialization Function
 *
 * @param  cfg: clock configuration pra
 *
 * @return None
 *
*******************************************************************************/
void Audio_Clock_Init(Audio_Clock_CFG_Type *cfg)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_ADC_CLOCK_TYPE(cfg->adc_clock));
    CHECK_PARAM(IS_AUDIO_DAC_CLOCK_TYPE(cfg->dac_clock));

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_AUD_TOP);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_RATE, cfg->adc_clock);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_RATE, cfg->dac_clock);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_PDM_ITF_INV_SEL, cfg->pdm_clk_inv);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC_ITF_INV_SEL, cfg->adc_clk_inv);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_ITF_INV_SEL, cfg->dac_clk_inv);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_CKG_EN, 1);

    BL_WR_REG(AUDIO_BASE, AUDIO_AUD_TOP, tmpVal);

    //TODO to select postion of register interrupt
#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(AUDIO_IRQn, AUDIO_IRQHandler);
#endif
}

/****************************************************************************/ /**
 * @brief  VAD Configuration function
 *
 * @param  cfg: VAD configuration pra
 *
 * @return None
 *
*******************************************************************************/
void Audio_VAD_Init(Audio_VAD_Cfg_Type *cfg)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUDIO_VAD_SOURCE_TYPE(cfg->vadSource));
    CHECK_PARAM(IS_AUDIO_VAD_FRAMINGSHIFT_TYPE(cfg->vadFramingShift));
    CHECK_PARAM(IS_AUDIO_VAD_FRAMINGTIME_TYPE(cfg->vadFramingTime));
    CHECK_PARAM(IS_AUDIO_VAD_IRQ_SOURCE_TYPE(cfg->vadIRQSource));
    CHECK_PARAM(IS_AUDIO_VAD_NOISYBUFFERLEN_TYPE(cfg->vadNoisyBufferLen));
    CHECK_PARAM(IS_AUDIO_VAD_NOISYBUFFERMONITOR_TYPE(cfg->vadNoisyBufferMonitor));

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_VAD_CTRL_0);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_VAD_NBUF_MONIT_EN, cfg->vadNoisyBufferMonitorEnable);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_VAD_NBUF_MONIT_CTRL, cfg->vadNoisyBufferMonitor);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_VAD_NBUF_LEN_CTRL, cfg->vadNoisyBufferLen);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_VAD_OUT_SEL, cfg->vadIRQSource);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_VAD_FRAMETIME_CTRL, cfg->vadFramingTime);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_VAD_FRAMESHIFT_CTRL, cfg->vadFramingShift);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_VAD_IN_SEL, cfg->vadSource);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_VAD_NTH_MAXLMT_EN, cfg->vadNoisyMaxLimitEnable);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_VAD_NTH_MINLMT_EN, cfg->vadNoisyMinLimitEnable);

    BL_WR_REG(AUDIO_BASE, AUDIO_VAD_CTRL_0, tmpVal);

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_VAD_CTRL_2);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_VAD_NTH_MINLMT, cfg->vadNoisyMinLimit);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_VAD_NTH_MAXLMT, cfg->vadNoisyMaxLimit);

    BL_WR_REG(AUDIO_BASE, AUDIO_VAD_CTRL_2, tmpVal);

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_VAD_CTRL_3);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_VAD_SMOOTH_FALL, cfg->vadSmoothFall);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_VAD_SMOOTH_RISE, cfg->vadSmoothRise);

    BL_WR_REG(AUDIO_BASE, AUDIO_VAD_CTRL_3, tmpVal);

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_VAD_CTRL_1);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_VAD_NTH_SCALE, cfg->noisyBufferThrScale);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_VAD_NTH_BIAS, cfg->noisyBufferThrBais);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_VAD_NBUF_DISCARD, cfg->noisyBufferDiscardNumber);

    BL_WR_REG(AUDIO_BASE, AUDIO_VAD_CTRL_1, tmpVal);

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_VAD_CTRL_5);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_VAD_NOISE_TH, cfg->noisyBufferThr);

    BL_WR_REG(AUDIO_BASE, AUDIO_VAD_CTRL_5, tmpVal);
}

/****************************************************************************/ /**
 * @brief  enable VAD
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void Audio_VAD_Enable(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_VAD_CTRL_0);
    tmpVal = BL_SET_REG_BIT(tmpVal, AUDIO_VAD_EN);
    BL_WR_REG(AUDIO_BASE, AUDIO_VAD_CTRL_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  disable VAD
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void Audio_VAD_Disable(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_VAD_CTRL_0);
    tmpVal = BL_CLR_REG_BIT(tmpVal, AUDIO_VAD_EN);
    BL_WR_REG(AUDIO_BASE, AUDIO_VAD_CTRL_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  VAD set EK function
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
uint32_t Audio_VAD_Get_EK(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_VAD_CTRL_4);

    return tmpVal;
}

/****************************************************************************/ /**
 * @brief  audio power on
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void Audio_Poweron(void)
{
    uint32_t tmpVal = 0;

    /* common */
    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_CODEC_POWER1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_MICBIAS_PU, 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_CODEC_VRDA_EN, 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_CODEC_IBIAS_CTRL, 5);
    BL_WR_REG(AUDIO_BASE, AUDIO_CODEC_POWER1, tmpVal);

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_CODEC_POWER2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_LDO25_PU, 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_HPBG_PU, 1);
    BL_WR_REG(AUDIO_BASE, AUDIO_CODEC_POWER2, tmpVal);

    /*DAC power on*/
    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_CODEC_DAC);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DACL_SDAC_LINEOUT, 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DACL_LINEOUT_MODE, 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DACL_EN_DAC, 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DACL_EN_LINEOUT, 1);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DACR_SDAC_LINEOUT, 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DACR_LINEOUT_MODE, 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DACR_EN_DAC, 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DACR_EN_LINEOUT, 1);
    BL_WR_REG(AUDIO_BASE, AUDIO_CODEC_DAC, tmpVal);

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_CODEC_DAC_RAMP);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_RG_LO_VREF_RAMP_DCL_EN, 0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DAC_RG_PU_VREF_RAMP, 1);
    BL_WR_REG(AUDIO_BASE, AUDIO_CODEC_DAC_RAMP, tmpVal);

    /*ADC Power on */

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_CODEC_ADC0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC0_EN_SDM, 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC0_EN_PGA, 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC0_PGA_GAIN, 8);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC0_ICTRL_ADC2, 3);
    BL_WR_REG(AUDIO_BASE, AUDIO_CODEC_ADC0, tmpVal);

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_CODEC_ADC1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC1_EN_SDM, 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC1_EN_PGA, 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC1_PGA_GAIN, 8);
    BL_WR_REG(AUDIO_BASE, AUDIO_CODEC_ADC1, tmpVal);

    tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_CODEC_ADC2);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC2_EN_SDM, 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC2_EN_PGA, 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC2_PGA_GAIN, 8);
    BL_WR_REG(AUDIO_BASE, AUDIO_CODEC_ADC2, tmpVal);

    /* best digital filter configuration*/
    Audio_Set_DAC_Scaling(1, 14);
}

void Audio_SetADCAnalogGain(Audio_ADC_ID_Type adc, uint8_t analogGain)
{
    uint32_t tmpVal = 0;

    if (adc == AUDIO_ADC_0) {
        tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_CODEC_ADC0);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC0_PGA_GAIN, analogGain);
        BL_WR_REG(AUDIO_BASE, AUDIO_CODEC_ADC0, tmpVal);
    } else if (adc == AUDIO_ADC_1) {
        tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_CODEC_ADC1);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC1_PGA_GAIN, analogGain);
        BL_WR_REG(AUDIO_BASE, AUDIO_CODEC_ADC1, tmpVal);
    } else {
        tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_CODEC_ADC2);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_ADC2_PGA_GAIN, analogGain);
        BL_WR_REG(AUDIO_BASE, AUDIO_CODEC_ADC2, tmpVal);
    }
}

void Audio_SetDACAnalogGain(Audio_DAC_ID_Type dac, uint8_t analogGain)
{
    uint32_t tmpVal = 0;

    if (dac == AUDIO_DAC_0) {
        tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_CODEC_DAC);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DACL_LINEOUT_GAIN, analogGain);
        BL_WR_REG(AUDIO_BASE, AUDIO_CODEC_DAC, tmpVal);
    } else {
        tmpVal = BL_RD_REG(AUDIO_BASE, AUDIO_CODEC_DAC);
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AUDIO_DACR_LINEOUT_GAIN, analogGain);
        BL_WR_REG(AUDIO_BASE, AUDIO_CODEC_DAC, tmpVal);
    }
}

/*@} end of group AUDIO_Public_Functions */

/*@} end of group AUDIO */

/*@} end of group BL808_Peripheral_Driver */
