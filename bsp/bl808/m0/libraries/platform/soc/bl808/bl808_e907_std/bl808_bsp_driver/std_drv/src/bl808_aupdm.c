/**
  ******************************************************************************
  * @file    bl808_pdm.c
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

#include "bl808_aupdm.h"
#include "pdm_reg.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  AUDIOPDM
 *  @{
 */

/** @defgroup  AUDIOPDM_Private_Macros
 *  @{
 */

/*@} end of group AUDIOPDM_Private_Macros */

/** @defgroup  AUDIOPDM_Private_Types
 *  @{
 */

/*@} end of group AUDIOPDM_Private_Types */

/** @defgroup  AUDIOPDM_Private_Variables
 *  @{
 */
static intCallback_Type *aupdmIntCbfArra[AUPDM_INT_NUM_ALL] = { NULL };

/*@} end of group AUDIOPDM_Private_Variables */

/** @defgroup  AUDIOPDM_Global_Variables
 *  @{
 */

/*@} end of group AUDIOPDM_Global_Variables */

/** @defgroup  AUDIOPDM_Private_Fun_Declaration
 *  @{
 */

/*@} end of group AUDIOPDM_Private_Fun_Declaration */

/** @defgroup  AUDIOPDM_Private_Functions
 *  @{
 */

/*@} end of group AUDIOPDM_Private_Functions */

/** @defgroup  AUDIOPDM_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  AUDIO Interrupt mask
 *
 * @param  intType: intType
 * @param  intMask: intMask
 *
 * @return None
 *
*******************************************************************************/
void Aupdm_IntMask(Aupdm_INT_Type intType, BL_Mask_Type intMask)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUPDM_INT_TYPE(intType));
    CHECK_PARAM(IS_BL_MASK_TYPE(intMask));

    switch (intType) {
        case AUPDM_INT_RX_FIFO_THR:
            tmpVal = BL_RD_REG(PDM0_BASE, PDM_RX_FIFO_CTRL);
            if (intMask) {
                tmpVal = BL_CLR_REG_BIT(tmpVal, PDM_RXA_INT_EN);
            } else {
                tmpVal = BL_SET_REG_BIT(tmpVal, PDM_RXA_INT_EN);
            }
            BL_WR_REG(PDM0_BASE, PDM_RX_FIFO_CTRL, tmpVal);
            break;
        case AUPDM_INT_RX_FIFO_OVERRUN:
            tmpVal = BL_RD_REG(PDM0_BASE, PDM_RX_FIFO_CTRL);
            if (intMask) {
                tmpVal = BL_CLR_REG_BIT(tmpVal, PDM_RXO_INT_EN);
            } else {
                tmpVal = BL_SET_REG_BIT(tmpVal, PDM_RXO_INT_EN);
            }
            BL_WR_REG(PDM0_BASE, PDM_RX_FIFO_CTRL, tmpVal);
            break;
        case AUPDM_INT_RX_FIFO_UNDERRUN:
            tmpVal = BL_RD_REG(PDM0_BASE, PDM_RX_FIFO_CTRL);
            if (intMask) {
                tmpVal = BL_CLR_REG_BIT(tmpVal, PDM_RXU_INT_EN);
            } else {
                tmpVal = BL_SET_REG_BIT(tmpVal, PDM_RXU_INT_EN);
            }
            BL_WR_REG(PDM0_BASE, PDM_RX_FIFO_CTRL, tmpVal);
            break;

        case AUPDM_INT_NUM_ALL:
            if (intMask) {
                tmpVal = BL_RD_REG(PDM0_BASE, PDM_RX_FIFO_CTRL);
                tmpVal = BL_CLR_REG_BIT(tmpVal, PDM_RXA_INT_EN);
                tmpVal = BL_CLR_REG_BIT(tmpVal, PDM_RXU_INT_EN);
                tmpVal = BL_CLR_REG_BIT(tmpVal, PDM_RXO_INT_EN);
                BL_WR_REG(PDM0_BASE, PDM_RX_FIFO_CTRL, tmpVal);

            } else {
                tmpVal = BL_RD_REG(PDM0_BASE, PDM_RX_FIFO_CTRL);
                tmpVal = BL_SET_REG_BIT(tmpVal, PDM_RXA_INT_EN);
                tmpVal = BL_SET_REG_BIT(tmpVal, PDM_RXU_INT_EN);
                tmpVal = BL_SET_REG_BIT(tmpVal, PDM_RXO_INT_EN);
                BL_WR_REG(PDM0_BASE, PDM_RX_FIFO_CTRL, tmpVal);
            }
            break;

        default:
            break;
    }
}

/****************************************************************************/ /**
 * @brief  read int flag
 *
 * @param  intType: intType
 *
 * @return flag status
 *
*******************************************************************************/
BL_Sts_Type Aupdm_GetIntStatus(Aupdm_INT_Type intType)
{
    uint32_t tmpVal = 0;
    BL_Sts_Type rlt = RESET;

    CHECK_PARAM(IS_AUPDM_INT_TYPE(intType));

    switch (intType) {
        case AUPDM_INT_RX_FIFO_THR:
            tmpVal = BL_RD_REG(PDM0_BASE, PDM_RX_FIFO_STATUS);
            rlt = BL_IS_REG_BIT_SET(tmpVal, PDM_RXA_INT);
            break;
        case AUPDM_INT_RX_FIFO_OVERRUN:
            tmpVal = BL_RD_REG(PDM0_BASE, PDM_RX_FIFO_STATUS);
            rlt = BL_IS_REG_BIT_SET(tmpVal, PDM_RXO_INT);
            break;
        case AUPDM_INT_RX_FIFO_UNDERRUN:
            tmpVal = BL_RD_REG(PDM0_BASE, PDM_RX_FIFO_STATUS);
            rlt = BL_IS_REG_BIT_SET(tmpVal, PDM_RXU_INT);
            break;
        default:
            break;
    }

    return rlt;
}

/****************************************************************************/ /**
 * @brief  clear audio Interrupt flag
 *
 * @param  intType: intType
 *
 * @return None
 *
*******************************************************************************/
void Aupdm_IntClear(Aupdm_INT_Type intType)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUPDM_INT_TYPE(intType));

    switch (intType) {
        case AUPDM_INT_RX_FIFO_THR:
            tmpVal = BL_RD_REG(PDM0_BASE, PDM_RX_FIFO_STATUS);
            tmpVal = BL_SET_REG_BIT(tmpVal, PDM_RXA_INT);
            BL_WR_REG(PDM0_BASE, PDM_RX_FIFO_STATUS, tmpVal);
            break;
        case AUPDM_INT_RX_FIFO_OVERRUN:
            tmpVal = BL_RD_REG(PDM0_BASE, PDM_RX_FIFO_STATUS);
            tmpVal = BL_SET_REG_BIT(tmpVal, PDM_RXO_INT);
            BL_WR_REG(PDM0_BASE, PDM_RX_FIFO_STATUS, tmpVal);
            break;
        case AUPDM_INT_RX_FIFO_UNDERRUN:
            tmpVal = BL_RD_REG(PDM0_BASE, PDM_RX_FIFO_STATUS);
            tmpVal = BL_SET_REG_BIT(PDM0_BASE, PDM_RXU_INT);
            BL_WR_REG(PDM0_BASE, PDM_RX_FIFO_STATUS, tmpVal);
            break;

        case AUPDM_INT_NUM_ALL:

            tmpVal = BL_RD_REG(PDM0_BASE, PDM_RX_FIFO_STATUS);

            tmpVal = BL_SET_REG_BIT(tmpVal, PDM_RXA_INT);
            tmpVal = BL_SET_REG_BIT(tmpVal, PDM_RXU_INT);
            tmpVal = BL_SET_REG_BIT(tmpVal, PDM_RXO_INT);

            BL_WR_REG(PDM0_BASE, PDM_RX_FIFO_STATUS, tmpVal);

        default:
            break;
    }
}

/****************************************************************************/ /**
 * @brief  AUPDM PDM interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
static void AUPDM_PDM_IRQHandler(void)
{
    uint8_t intIndex = 0;

    for (intIndex = 0; intIndex < AUPDM_INT_NUM_ALL; intIndex++) {
        if (Aupdm_GetIntStatus(intIndex) == SET) {
            aupdmIntCbfArra[intIndex]();
            Aupdm_IntClear(intIndex);
        }
    }
}
#endif

/****************************************************************************/ /**
 * @brief  AUPDM PDM Clock Initialization Function
 *
 * @param  cfg: clock configuration pra
 *
 * @return None
 *
*******************************************************************************/
void Aupdm_Clock_Init(Aupdm_Clock_CFG_Type *cfg)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUPDM_ADC_CLOCK_TYPE(cfg->adc_clock));
    CHECK_PARAM(IS_AUPDM_DAC_CLOCK_TYPE(cfg->dac_clock));

    tmpVal = BL_RD_REG(PDM0_BASE, PDM_AUDPDM_TOP);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_ADC_RATE, cfg->adc_clock);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_ITF_INV_SEL, cfg->pdm_clk_inv);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_ADC_ITF_INV_SEL, cfg->adc_clk_inv);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_AUDIO_CKG_EN, 1);

    BL_WR_REG(PDM0_BASE, PDM_AUDPDM_TOP, tmpVal);

//TODO to select postion of register interrupt
#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(AUPDM_TOUCH_IRQn, AUPDM_PDM_IRQHandler);
#endif
}

/****************************************************************************/ /**
 * @brief  AUPDM support three channel for pdm .Meanwhile AUPDM support two DMIC Interface which
 *         supporting four pdm data source input.This function is used to select channel with pdm
 *         source.
 *
 * @param  id: pdm channel,cannot be larger than 3
 * @param  pdmSel: pdm source select
 *
 * @return Success or not
 *
*******************************************************************************/
void Aupdm_PDM_Channel_Sel(Aupdm_PDM_ID_Type id, Aupdm_PDM_Source_Type pdmSel)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUPDM_PDM_SOURCE_TYPE(pdmSel));
    CHECK_PARAM(IS_AUPDM_PDM_ID_TYPE(id));

    tmpVal = BL_RD_REG(PDM0_BASE, PDM_PDM_0);

    if (id == AUPDM_PDM_0) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_ADC_0_PDM_SEL, pdmSel);
    } else if (id == AUPDM_PDM_1) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_ADC_1_PDM_SEL, pdmSel);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_ADC_2_PDM_SEL, pdmSel);
    }
    BL_WR_REG(PDM0_BASE, PDM_PDM_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  AUPDM Enable PDM
 *
 * @param  id: PDM ID
 *
 * @return Success or not
 *
*******************************************************************************/
void Aupdm_PDM_Enable(Aupdm_PDM_ID_Type id)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUPDM_PDM_ID_TYPE(id));

    tmpVal = BL_RD_REG(PDM0_BASE, PDM_PDM_0);

    if (id == AUPDM_PDM_0) {
        tmpVal = BL_SET_REG_BIT(tmpVal, PDM_0_EN);
    } else if (id == AUPDM_PDM_1) {
        tmpVal = BL_SET_REG_BIT(tmpVal, PDM_1_EN);
    } else {
        tmpVal = BL_SET_REG_BIT(tmpVal, PDM_2_EN);
    }
    BL_WR_REG(PDM0_BASE, PDM_PDM_0, tmpVal);
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
BL_Err_Type Aupdm_Int_Callback_Install(Aupdm_INT_Type intType, intCallback_Type *cbFun)
{
    CHECK_PARAM(IS_AUPDM_INT_TYPE(intType));

    aupdmIntCbfArra[intType] = cbFun;

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  rx fifo flush
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void Aupdm_RxFifoClear(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(PDM0_BASE, PDM_RX_FIFO_CTRL);
    tmpVal = BL_SET_REG_BIT(tmpVal, PDM_RX_FIFO_FLUSH);
    BL_WR_REG(PDM0_BASE, PDM_RX_FIFO_CTRL, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Get Rx FIFO Count
 *
 * @param  None
 *
 * @return fifi count
 *
*******************************************************************************/
uint32_t Aupdm_GetRxFifoCount(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(PDM0_BASE, PDM_RX_FIFO_STATUS);
    tmpVal = BL_GET_REG_BITS_VAL(tmpVal, PDM_RXA_CNT);

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
uint32_t Aupdm_ReadRxFifo(void)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(PDM0_BASE, PDM_RX_FIFO_DATA);

    return tmpVal;
}

/****************************************************************************/ /**
 * @brief  Configure rx fifo
 *
 * @param  cfg: fifo cfg
 *
 * @return None
 *
*******************************************************************************/
void Aupdm_RxFifoConfig(Aupdm_FifoCfg_Type *cfg)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUPDM_RESOLUTION_TYPE(cfg->resolution));
    CHECK_PARAM(IS_AUPDM_FIFO_AILGN_MODE(cfg->ailgnMode));
    CHECK_PARAM(IS_AUPDM_FIFO_DQR_THRESHOLD_MODE(cfg->dmaThresholdMode));

    tmpVal = BL_RD_REG(PDM0_BASE, PDM_RX_FIFO_CTRL);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_RX_DATA_RES, cfg->resolution);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_RX_DATA_MODE, cfg->ailgnMode);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_RX_DRQ_CNT, cfg->dmaThresholdMode);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_RX_TRG_LEVEL, cfg->FifoIntThreshold);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_RX_DRQ_EN, cfg->dmaEn);

    BL_WR_REG(PDM0_BASE, PDM_RX_FIFO_CTRL, tmpVal);

    tmpVal = BL_RD_REG(PDM0_BASE, PDM_AUDPDM_ITF);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_ADC_ITF_EN, cfg->dmaEn);
    BL_WR_REG(PDM0_BASE, PDM_AUDPDM_ITF, tmpVal);
}

/****************************************************************************/ /**
 * @brief  enable rx fifo
 *
 * @param  ch: ch
 *
 * @return None
 *
*******************************************************************************/
void Aupdm_RxFifoEnable(uint8_t ch)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(PDM0_BASE, PDM_RX_FIFO_CTRL);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_RX_CH_EN, ch);
    BL_WR_REG(PDM0_BASE, PDM_RX_FIFO_CTRL, tmpVal);
}

/****************************************************************************/ /**
 * @brief  disable rx fifo
 *
 * @param  ch: fifo cfg
 *
 * @return None
 *
*******************************************************************************/
void Aupdm_RxFifoDisable(uint8_t ch)
{
    uint32_t tmpVal = 0;
    uint32_t tmpVal2 = 0;

    tmpVal = BL_RD_REG(PDM0_BASE, PDM_RX_FIFO_CTRL);
    tmpVal2 = BL_GET_REG_BITS_VAL(tmpVal, PDM_RX_CH_EN);

    tmpVal2 &= ~ch;

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_RX_CH_EN, tmpVal2);

    BL_WR_REG(PDM0_BASE, PDM_RX_FIFO_CTRL, tmpVal);
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
BL_Err_Type Aupdm_Rx_Source_ADC_Sel(uint8_t rx_channel, Aupdm_ADC_ID_Type adc_id)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUPDM_ADC_ID_TYPE(adc_id));

    if (rx_channel > 4) {
        return ERROR;
        /*rx channel sel can not larger than 4*/
    }

    tmpVal = BL_RD_REG(PDM0_BASE, PDM_AUDPDM_ITF);

    switch (rx_channel) {
        case 0:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_AUD_RX0_SEL, adc_id);
            break;
        case 1:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_AUD_RX1_SEL, adc_id);
            break;
        case 2:
            tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_AUD_RX2_SEL, adc_id);
            break;
        default:
            break;
    }

    BL_WR_REG(PDM0_BASE, PDM_AUDPDM_ITF, tmpVal);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  AUPDM ADC enable
 *
 * @param  id: Auido ADC ID
 *
 * @return None
 *
*******************************************************************************/
void Aupdm_ADC_Enable(Aupdm_ADC_ID_Type id)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUPDM_ADC_ID_TYPE(id));

    tmpVal = BL_RD_REG(PDM0_BASE, PDM_AUDPDM_ITF);
    if (id == AUPDM_ADC_0) {
        tmpVal = BL_SET_REG_BIT(tmpVal, PDM_ADC_0_EN);
    } else if (id == AUPDM_ADC_1) {
        tmpVal = BL_SET_REG_BIT(tmpVal, PDM_ADC_1_EN);
    } else {
        tmpVal = BL_SET_REG_BIT(tmpVal, PDM_ADC_2_EN);
    }
    BL_WR_REG(PDM0_BASE, PDM_AUDPDM_ITF, tmpVal);
}

/****************************************************************************/ /**
 * @brief  AUPDM ADC disable
 *
 * @param  id: Auido ADC ID
 *
 * @return None
 *
*******************************************************************************/
void Aupdm_ADC_Disable(Aupdm_ADC_ID_Type id)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(PDM0_BASE, PDM_AUDPDM_ITF);
    if (id == AUPDM_ADC_0) {
        tmpVal = BL_CLR_REG_BIT(tmpVal, PDM_ADC_0_EN);
    } else if (id == AUPDM_ADC_1) {
        tmpVal = BL_CLR_REG_BIT(tmpVal, PDM_ADC_1_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, PDM_ADC_2_EN);
    }
    BL_WR_REG(PDM0_BASE, PDM_AUDPDM_ITF, tmpVal);
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
void Aupdm_Set_ADC_Scaling_Value(Aupdm_ADC_ID_Type id, uint8_t scalingVal)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUPDM_ADC_ID_TYPE(id));

    tmpVal = BL_RD_REG(PDM0_BASE, PDM_ADC_0);

    if (id == AUPDM_ADC_0) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_ADC_0_SCAL, scalingVal);
    } else if (id == AUPDM_ADC_1) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_ADC_1_SCAL, scalingVal);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_ADC_2_SCAL, scalingVal);
    }
    BL_WR_REG(PDM0_BASE, PDM_ADC_0, tmpVal);
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
void Aupdm_Set_Fir_Mode(Aupdm_ADC_ID_Type id, uint8_t enable)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUPDM_ADC_ID_TYPE(id));

    tmpVal = BL_RD_REG(PDM0_BASE, PDM_ADC_0);

    if (id == AUPDM_ADC_0) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_ADC_0_FIR_MODE, enable);
    } else if (id == AUPDM_ADC_1) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_ADC_1_FIR_MODE, enable);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_ADC_2_FIR_MODE, enable);
    }
    BL_WR_REG(PDM0_BASE, PDM_ADC_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  AUPDM Set HPF Parameter
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
void Aupdm_Set_HPF_Parameter(Aupdm_ADC_ID_Type id, uint8_t k1_enable, uint8_t k1, uint8_t k2_enable, uint8_t k2)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUPDM_ADC_ID_TYPE(id));

    tmpVal = BL_RD_REG(PDM0_BASE, PDM_ADC_1);

    switch (id) {
        case AUPDM_ADC_0:
            if (k1_enable) {
                tmpVal = BL_SET_REG_BIT(tmpVal, PDM_ADC_0_K1_EN);
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_ADC_0_K1, k1);
            } else {
                tmpVal = BL_CLR_REG_BIT(tmpVal, PDM_ADC_0_K1_EN);
            }
            if (k2_enable) {
                tmpVal = BL_SET_REG_BIT(tmpVal, PDM_ADC_0_K2_EN);
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_ADC_0_K2, k2);
            } else {
                tmpVal = BL_CLR_REG_BIT(tmpVal, PDM_ADC_0_K2_EN);
            }
            break;
        case AUPDM_ADC_1:
            if (k1_enable) {
                tmpVal = BL_SET_REG_BIT(tmpVal, PDM_ADC_1_K1_EN);
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_ADC_1_K1, k1);
            } else {
                tmpVal = BL_CLR_REG_BIT(tmpVal, PDM_ADC_1_K1_EN);
            }
            if (k2_enable) {
                tmpVal = BL_SET_REG_BIT(tmpVal, PDM_ADC_1_K2_EN);
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_ADC_1_K2, k2);
            } else {
                tmpVal = BL_CLR_REG_BIT(tmpVal, PDM_ADC_1_K2_EN);
            }
            break;
        case AUPDM_ADC_2:
            if (k1_enable) {
                tmpVal = BL_SET_REG_BIT(tmpVal, PDM_ADC_2_K1_EN);
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_ADC_2_K1, k1);
            } else {
                tmpVal = BL_CLR_REG_BIT(tmpVal, PDM_ADC_2_K1_EN);
            }

            if (k2_enable) {
                tmpVal = BL_SET_REG_BIT(tmpVal, PDM_ADC_2_K2_EN);
                tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_ADC_2_K2, k2);
            } else {
                tmpVal = BL_CLR_REG_BIT(tmpVal, PDM_ADC_2_K2_EN);
            }
            break;
        default:
            break;
    }

    BL_WR_REG(PDM0_BASE, PDM_ADC_1, tmpVal);
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
void Aupdm_ADC_PDM_Inv_Swap(Aupdm_ADC_ID_Type id, uint8_t swap)
{
    uint32_t tmpVal = 0;

    CHECK_PARAM(IS_AUPDM_ADC_ID_TYPE(id));

    tmpVal = BL_RD_REG(PDM0_BASE, PDM_DAC_0);
    if (id == AUPDM_ADC_0) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_ADC_0_PDM_LVL_SWAP, swap);
    } else if (id == AUPDM_ADC_1) {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_ADC_1_PDM_LVL_SWAP, swap);
    } else {
        tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_ADC_2_PDM_LVL_SWAP, swap);
    }
    BL_WR_REG(PDM0_BASE, PDM_DAC_0, tmpVal);
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
void Aupdm_ADC_Set_PDM_Value(uint8_t pdm_l, uint8_t pdm_h)
{
    uint32_t tmpVal = 0;

    tmpVal = BL_RD_REG(PDM0_BASE, PDM_DAC_0);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_ADC_PDM_L, pdm_l);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, PDM_ADC_PDM_H, pdm_l);
    BL_WR_REG(PDM0_BASE, PDM_DAC_0, tmpVal);
}

/****************************************************************************/ /**
 * @brief  AUPDM adc Volume Config
 *
 * @param  adc_id: adc id
 * @param  volume: volume config cfg pointer
 *
 * @return None
 *
*******************************************************************************/
BL_Err_Type Aupdm_ADC_Volume_Config(Aupdm_ADC_ID_Type adc_id, uint8_t volume)
{
    if (adc_id > 2) {
        return ERROR;
        /*only support 3 adc*/
    }

    if (adc_id == AUPDM_ADC_0) {
        BL_WR_REG(PDM0_BASE, PDM_ADC_S0, volume);
    } else if (adc_id == AUPDM_ADC_1) {
        BL_WR_REG(PDM0_BASE, PDM_ADC_S1, volume);
    } else {
        BL_WR_REG(PDM0_BASE, PDM_ADC_S2, volume);
    }

    return SUCCESS;
}

/*@} end of group AUPDMPDM_Public_Functions */

/*@} end of group AUPDMPDM */

/*@} end of group BL808_Peripheral_Driver */
