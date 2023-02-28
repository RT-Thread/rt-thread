/**
  ******************************************************************************
  * @file    bl808_adc.c
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

#include "bl808_adc.h"
#include "bl808_ef_ctrl.h"

/** @addtogroup  BL808_Peripheral_Driver
 *  @{
 */

/** @addtogroup  ADC
 *  @{
 */

/** @defgroup  ADC_Private_Macros
 *  @{
 */
#undef MSG
#define MSG(...)
#define AON_CLK_SET_DUMMY_WAIT \
    {                          \
        __NOP();               \
        __NOP();               \
        __NOP();               \
        __NOP();               \
        __NOP();               \
        __NOP();               \
        __NOP();               \
        __NOP();               \
    }
#define ADC_RESTART_DUMMY_WAIT arch_delay_us(100)

/*@} end of group ADC_Private_Macros */

/** @defgroup  ADC_Private_Types
 *  @{
 */

/*@} end of group ADC_Private_Types */

/** @defgroup  ADC_Private_Variables
 *  @{
 */
static intCallback_Type *adcIntCbfArra[ADC_INT_ALL] = { NULL };
static ADC_Gain_Coeff_Type adcGainCoeffCal = {
    .adcGainCoeffEnable = DISABLE,
    .adcgainCoeffVal = 0,
    .coe = 1,
};

/*@} end of group ADC_Private_Variables */

/** @defgroup  ADC_Global_Variables
 *  @{
 */

/*@} end of group ADC_Global_Variables */

/** @defgroup  ADC_Private_Fun_Declaration
 *  @{
 */

/*@} end of group ADC_Private_Fun_Declaration */

/** @defgroup  ADC_Private_Functions
 *  @{
 */

/*@} end of group ADC_Private_Functions */

/** @defgroup  ADC_Public_Functions
 *  @{
 */

/****************************************************************************/ /**
 * @brief  Software reset the whole ADC
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void ADC_Reset(void)
{
    uint32_t regCmd;

    /* reset ADC */
    regCmd = BL_RD_REG(AON_BASE, AON_GPADC_REG_CMD);
    BL_WR_REG(AON_BASE, AON_GPADC_REG_CMD, BL_SET_REG_BIT(regCmd, AON_GPADC_SOFT_RST));
    AON_CLK_SET_DUMMY_WAIT;
    BL_WR_REG(AON_BASE, AON_GPADC_REG_CMD, BL_CLR_REG_BIT(regCmd, AON_GPADC_SOFT_RST));
}

/****************************************************************************/ /**
 * @brief  ADC glable enable
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void ADC_Enable(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(AON_BASE, AON_GPADC_REG_CMD);
    tmpVal = BL_SET_REG_BIT(tmpVal, AON_GPADC_GLOBAL_EN);
    BL_WR_REG(AON_BASE, AON_GPADC_REG_CMD, tmpVal);
}

/****************************************************************************/ /**
 * @brief  ADC glable disable
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void ADC_Disable(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(AON_BASE, AON_GPADC_REG_CMD);
    tmpVal = BL_CLR_REG_BIT(tmpVal, AON_GPADC_GLOBAL_EN);
    BL_WR_REG(AON_BASE, AON_GPADC_REG_CMD, tmpVal);
}

/****************************************************************************/ /**
 * @brief  ADC normal mode init
 *
 * @param  cfg: ADC normal mode configuration
 *
 * @return None
 *
*******************************************************************************/
void ADC_Init(ADC_CFG_Type *cfg)
{
    uint32_t regCfg1;
    uint32_t regCfg2;
    uint32_t regCalib;
    uint32_t regCmd;

    CHECK_PARAM(IS_ADC_V18_SEL_TYPE(cfg->v18Sel));
    CHECK_PARAM(IS_ADC_V11_SEL_TYPE(cfg->v11Sel));
    CHECK_PARAM(IS_ADC_CLK_TYPE(cfg->clkDiv));
    CHECK_PARAM(IS_ADC_PGA_GAIN_TYPE(cfg->gain1));
    CHECK_PARAM(IS_ADC_PGA_GAIN_TYPE(cfg->gain2));
    CHECK_PARAM(IS_ADC_CHOP_MOD_TYPE(cfg->chopMode));
    CHECK_PARAM(IS_ADC_BIAS_SEL_TYPE(cfg->biasSel));
    CHECK_PARAM(IS_ADC_PGA_VCM_TYPE(cfg->vcm));
    CHECK_PARAM(IS_ADC_VREF_TYPE(cfg->vref));
    CHECK_PARAM(IS_ADC_SIG_INPUT_TYPE(cfg->inputMode));
    CHECK_PARAM(IS_ADC_DATA_WIDTH_TYPE(cfg->resWidth));

    /* config 1 */
    regCfg1 = BL_RD_REG(AON_BASE, AON_GPADC_REG_CONFIG1);
    regCfg1 = BL_SET_REG_BITS_VAL(regCfg1, AON_GPADC_V18_SEL, cfg->v18Sel);
    regCfg1 = BL_SET_REG_BITS_VAL(regCfg1, AON_GPADC_V11_SEL, cfg->v11Sel);
    regCfg1 = BL_CLR_REG_BIT(regCfg1, AON_GPADC_DITHER_EN);
    regCfg1 = BL_CLR_REG_BIT(regCfg1, AON_GPADC_SCAN_EN);
    regCfg1 = BL_SET_REG_BITS_VAL(regCfg1, AON_GPADC_SCAN_LENGTH, 0);
    regCfg1 = BL_SET_REG_BITS_VAL(regCfg1, AON_GPADC_CLK_DIV_RATIO, cfg->clkDiv);
    regCfg1 = BL_CLR_REG_BIT(regCfg1, AON_GPADC_CLK_ANA_INV);
    regCfg1 = BL_SET_REG_BITS_VAL(regCfg1, AON_GPADC_CAL_OS_EN, cfg->offsetCalibEn);
    regCfg1 = BL_SET_REG_BITS_VAL(regCfg1, AON_GPADC_RES_SEL, cfg->resWidth);
    BL_WR_REG(AON_BASE, AON_GPADC_REG_CONFIG1, regCfg1);
    AON_CLK_SET_DUMMY_WAIT;

    /* config 2 */
    regCfg2 = BL_RD_REG(AON_BASE, AON_GPADC_REG_CONFIG2);
    regCfg2 = BL_SET_REG_BITS_VAL(regCfg2, AON_GPADC_DLY_SEL, 0x02);
    regCfg2 = BL_SET_REG_BITS_VAL(regCfg2, AON_GPADC_PGA1_GAIN, cfg->gain1);
    regCfg2 = BL_SET_REG_BITS_VAL(regCfg2, AON_GPADC_PGA2_GAIN, cfg->gain2);
    regCfg2 = BL_SET_REG_BITS_VAL(regCfg2, AON_GPADC_BIAS_SEL, cfg->biasSel);
    regCfg2 = BL_SET_REG_BITS_VAL(regCfg2, AON_GPADC_CHOP_MODE, cfg->chopMode);
    /* pga_vcmi_en is for mic */
    regCfg2 = BL_CLR_REG_BIT(regCfg2, AON_GPADC_PGA_VCMI_EN);

    if ((cfg->gain1 != ADC_PGA_GAIN_NONE) || (cfg->gain2 != ADC_PGA_GAIN_NONE)) {
        regCfg2 = BL_SET_REG_BIT(regCfg2, AON_GPADC_PGA_EN);
    } else {
        regCfg2 = BL_CLR_REG_BIT(regCfg2, AON_GPADC_PGA_EN);
    }

    /* pga_os_cal is for mic */
    regCfg2 = BL_SET_REG_BITS_VAL(regCfg2, AON_GPADC_PGA_OS_CAL, 8);
    regCfg2 = BL_SET_REG_BITS_VAL(regCfg2, AON_GPADC_PGA_VCM, cfg->vcm);
    regCfg2 = BL_SET_REG_BITS_VAL(regCfg2, AON_GPADC_VREF_SEL, cfg->vref);
    regCfg2 = BL_SET_REG_BITS_VAL(regCfg2, AON_GPADC_DIFF_MODE, cfg->inputMode);

    BL_WR_REG(AON_BASE, AON_GPADC_REG_CONFIG2, regCfg2);

    /* mic2 diff enable */
    regCmd = BL_RD_REG(AON_BASE, AON_GPADC_REG_CMD);
    regCmd = BL_SET_REG_BIT(regCmd, AON_GPADC_MIC2_DIFF);
    if (cfg->inputMode == ADC_INPUT_SINGLE_END) {
        regCmd = BL_SET_REG_BIT(regCmd, AON_GPADC_NEG_GND);
    } else {
        regCmd = BL_CLR_REG_BIT(regCmd, AON_GPADC_NEG_GND);
    }
    BL_WR_REG(AON_BASE, AON_GPADC_REG_CMD, regCmd);

    /* calibration offset */
    regCalib = BL_RD_REG(AON_BASE, AON_GPADC_REG_DEFINE);
    regCalib = BL_SET_REG_BITS_VAL(regCalib, AON_GPADC_OS_CAL_DATA, cfg->offsetCalibVal);
    BL_WR_REG(AON_BASE, AON_GPADC_REG_DEFINE, regCalib);

#ifndef BFLB_USE_HAL_DRIVER
    Interrupt_Handler_Register(GPADC_DMA_IRQn, GPADC_DMA_IRQHandler);
#endif

    ADC_Gain_Trim();
}

/****************************************************************************/ /**
 * @brief  ADC normal mode channel config
 *
 * @param  posCh: ADC pos channel type
 * @param  negCh: ADC neg channel type
 * @param  contEn: ENABLE or DISABLE continuous mode
 *
 * @return None
 *
*******************************************************************************/
void ADC_Channel_Config(ADC_Chan_Type posCh, ADC_Chan_Type negCh, BL_Fun_Type contEn)
{
    uint32_t regCmd;
    uint32_t regCfg1;

    CHECK_PARAM(IS_AON_ADC_CHAN_TYPE(posCh));
    CHECK_PARAM(IS_AON_ADC_CHAN_TYPE(negCh));

    /* set channel */
    regCmd = BL_RD_REG(AON_BASE, AON_GPADC_REG_CMD);
    regCmd = BL_SET_REG_BITS_VAL(regCmd, AON_GPADC_POS_SEL, posCh);
    regCmd = BL_SET_REG_BITS_VAL(regCmd, AON_GPADC_NEG_SEL, negCh);
    BL_WR_REG(AON_BASE, AON_GPADC_REG_CMD, regCmd);

    /* set continuous mode */
    regCfg1 = BL_RD_REG(AON_BASE, AON_GPADC_REG_CONFIG1);
    regCfg1 = BL_SET_REG_BITS_VAL(regCfg1, AON_GPADC_CONT_CONV_EN, contEn);
    regCfg1 = BL_CLR_REG_BIT(regCfg1, AON_GPADC_SCAN_EN);
    BL_WR_REG(AON_BASE, AON_GPADC_REG_CONFIG1, regCfg1);
}

/****************************************************************************/ /**
 * @brief  ADC scan mode channel config
 *
 * @param  posChList[]: ADC pos channel list type
 * @param  negChList[]: ADC neg channel list type
 * @param  scanLength: ADC scan length
 * @param  contEn: ENABLE or DISABLE continuous mode
 *
 * @return None
 *
*******************************************************************************/
void ADC_Scan_Channel_Config(ADC_Chan_Type posChList[], ADC_Chan_Type negChList[], uint8_t scanLength, BL_Fun_Type contEn)
{
    uint32_t tmpVal, i;
    uint32_t dealLen;

    CHECK_PARAM((scanLength < 13));

    /* Deal with the first 6 */
    dealLen = 6;

    if (scanLength < dealLen) {
        dealLen = scanLength;
    }

    /* Set first 6 scan channels */
    tmpVal = BL_RD_REG(AON_BASE, AON_GPADC_REG_SCN_POS1);

    for (i = 0; i < dealLen; i++) {
        tmpVal = tmpVal & (~(0x1F << (i * 5)));
        tmpVal |= (posChList[i] << (i * 5));
    }

    BL_WR_REG(AON_BASE, AON_GPADC_REG_SCN_POS1, tmpVal);

    tmpVal = BL_RD_REG(AON_BASE, AON_GPADC_REG_SCN_NEG1);

    for (i = 0; i < dealLen; i++) {
        tmpVal = tmpVal & (~(0x1F << (i * 5)));
        tmpVal |= (negChList[i] << (i * 5));
    }

    BL_WR_REG(AON_BASE, AON_GPADC_REG_SCN_NEG1, tmpVal);

    /* Set the left channels */
    if (scanLength > dealLen) {
        tmpVal = BL_RD_REG(AON_BASE, AON_GPADC_REG_SCN_POS2);

        for (i = 0; i < scanLength - dealLen; i++) {
            tmpVal = tmpVal & (~(0x1F << (i * 5)));
            tmpVal |= (posChList[i + dealLen] << (i * 5));
        }

        BL_WR_REG(AON_BASE, AON_GPADC_REG_SCN_POS2, tmpVal);

        tmpVal = BL_RD_REG(AON_BASE, AON_GPADC_REG_SCN_NEG2);

        for (i = 0; i < scanLength - dealLen; i++) {
            tmpVal = tmpVal & (~(0x1F << (i * 5)));
            tmpVal |= (negChList[i + dealLen] << (i * 5));
        }

        BL_WR_REG(AON_BASE, AON_GPADC_REG_SCN_NEG2, tmpVal);
    }

    /* Scan mode */
    tmpVal = BL_RD_REG(AON_BASE, AON_GPADC_REG_CONFIG1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_GPADC_SCAN_LENGTH, scanLength - 1);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_GPADC_CONT_CONV_EN, contEn);
    tmpVal = BL_SET_REG_BIT(tmpVal, AON_GPADC_CLK_ANA_INV);
    tmpVal = BL_SET_REG_BIT(tmpVal, AON_GPADC_SCAN_EN);
    BL_WR_REG(AON_BASE, AON_GPADC_REG_CONFIG1, tmpVal);
}

/****************************************************************************/ /**
 * @brief  ADC normal mode convert start
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void ADC_Start(void)
{
    uint32_t regCmd;

    /* disable convert start */
    regCmd = BL_RD_REG(AON_BASE, AON_GPADC_REG_CMD);
    regCmd = BL_CLR_REG_BIT(regCmd, AON_GPADC_CONV_START);
    BL_WR_REG(AON_BASE, AON_GPADC_REG_CMD, regCmd);

    ADC_RESTART_DUMMY_WAIT;

    /* enable convert start */
    regCmd = BL_RD_REG(AON_BASE, AON_GPADC_REG_CMD);
    regCmd = BL_SET_REG_BIT(regCmd, AON_GPADC_CONV_START);
    BL_WR_REG(AON_BASE, AON_GPADC_REG_CMD, regCmd);
}

/****************************************************************************/ /**
 * @brief  ADC normal mode convert stop
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void ADC_Stop(void)
{
    uint32_t regCmd;

    /* disable convert start */
    regCmd = BL_RD_REG(AON_BASE, AON_GPADC_REG_CMD);
    regCmd = BL_CLR_REG_BIT(regCmd, AON_GPADC_CONV_START);
    BL_WR_REG(AON_BASE, AON_GPADC_REG_CMD, regCmd);
}

/****************************************************************************/ /**
 * @brief  ADC FIFO configuration
 *
 * @param  fifoCfg: ADC FIFO confifuration pointer
 *
 * @return None
 *
*******************************************************************************/
void ADC_FIFO_Cfg(ADC_FIFO_Cfg_Type *fifoCfg)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_GPIP_ADC_FIFO_THRESHOLD_TYPE(fifoCfg->fifoThreshold));

    /*
     *  DMA enable : ,When the fifo data is exceeded to fifoThreshold DMA request will occur
     *  DMA disable : fifoThreshold determine how many data will raise FIFO ready interrupt
     */

    tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPADC_CONFIG);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GPIP_GPADC_FIFO_THL, fifoCfg->fifoThreshold);

    /* Enable DMA */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, GPIP_GPADC_DMA_EN, fifoCfg->dmaEn);

    BL_WR_REG(GPIP_BASE, GPIP_GPADC_CONFIG, tmpVal);

    /* clear fifo by SET GPIP_GPADC_FIFO_CLR bit*/
    tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPADC_CONFIG);
    tmpVal = BL_SET_REG_BIT(tmpVal, GPIP_GPADC_FIFO_CLR);
    BL_WR_REG(GPIP_BASE, GPIP_GPADC_CONFIG, tmpVal);
}

/****************************************************************************/ /**
 * @brief  ADC get DMA FIFO data count
 *
 * @param  None
 *
 * @return data count in FIFO
 *
*******************************************************************************/
uint8_t ADC_Get_FIFO_Count(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPADC_CONFIG);

    return BL_GET_REG_BITS_VAL(tmpVal, GPIP_GPADC_FIFO_DATA_COUNT);
}

/****************************************************************************/ /**
 * @brief  ADC get DMA FIFO full status
 *
 * @param  None
 *
 * @return SET or RESET
 *
*******************************************************************************/
BL_Sts_Type ADC_FIFO_Is_Full(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPADC_CONFIG);

    if (BL_IS_REG_BIT_SET(tmpVal, GPIP_GPADC_FIFO_FULL)) {
        return SET;
    } else {
        return RESET;
    }
}

/****************************************************************************/ /**
 * @brief  ADC get DMA FIFO empty status
 *
 * @param  None
 *
 * @return SET or RESET
 *
*******************************************************************************/
BL_Sts_Type ADC_FIFO_Is_Empty(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPADC_CONFIG);

    if (BL_IS_REG_BIT_SET(tmpVal, GPIP_GPADC_FIFO_NE)) {
        return RESET;
    } else {
        return SET;
    }
}

/****************************************************************************/ /**
 * @brief  ADC read DMA FIFO data
 *
 * @param  None
 *
 * @return ADC result if return 0 that means this is error data,user should ignore this data.
 *
*******************************************************************************/
uint32_t ADC_Read_FIFO(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPADC_DMA_RDATA);

    return (tmpVal);
}

/****************************************************************************/ /**
 * @brief  ADC parse result
 *
 * @param  orgVal: Original A to D value
 * @param  len: Original AD vaule count
 * @param  result: Final Result array pointer
 *
 * @return None
 *
*******************************************************************************/
void ADC_Parse_Result(uint32_t *orgVal, uint32_t len, ADC_Result_Type *result)
{
    uint8_t neg = 0;
    uint32_t tmpVal1 = 0, tmpVal2 = 0;
    ADC_Data_Width_Type dataType;
    ADC_SIG_INPUT_Type sigType;
    float ref = 2.0;
    uint32_t i = 0;

    float coe = 1.0;

    if (adcGainCoeffCal.adcGainCoeffEnable) {
        coe = adcGainCoeffCal.coe;
    }

    tmpVal1 = BL_RD_REG(AON_BASE, AON_GPADC_REG_CONFIG1);
    tmpVal2 = BL_RD_REG(AON_BASE, AON_GPADC_REG_CONFIG2);
    dataType = BL_GET_REG_BITS_VAL(tmpVal1, AON_GPADC_RES_SEL);
    sigType = BL_GET_REG_BITS_VAL(tmpVal2, AON_GPADC_DIFF_MODE);

    if (BL_GET_REG_BITS_VAL(tmpVal2, AON_GPADC_VREF_SEL) == ADC_VREF_3P2V) {
        ref = 3.2;
    }

    if (sigType == ADC_INPUT_SINGLE_END) {
        for (i = 0; i < len; i++) {
            result[i].posChan = orgVal[i] >> 21;
            result[i].negChan = -1;

            if (dataType == ADC_DATA_WIDTH_12) {
                result[i].value = (unsigned int)(((orgVal[i] & 0xffff) >> 4) / coe);
                result[i].volt = result[i].value / 4096.0 * ref;
            } else if ((dataType == ADC_DATA_WIDTH_14_WITH_16_AVERAGE) ||
                       (dataType == ADC_DATA_WIDTH_14_WITH_64_AVERAGE)) {
                result[i].value = (unsigned int)(((orgVal[i] & 0xffff) >> 2) / coe);
                result[i].volt = result[i].value / 16384.0 * ref;
            } else if ((dataType == ADC_DATA_WIDTH_16_WITH_128_AVERAGE) ||
                       (dataType == ADC_DATA_WIDTH_16_WITH_256_AVERAGE)) {
                result[i].value = (unsigned int)((orgVal[i] & 0xffff) / coe);
                result[i].volt = result[i].value / 65536.0 * ref;
            }
        }
    } else {
        for (i = 0; i < len; i++) {
            neg = 0;
            result[i].posChan = orgVal[i] >> 21;
            result[i].negChan = (orgVal[i] >> 16) & 0x1F;

            if (orgVal[i] & 0x8000) {
                orgVal[i] = ~orgVal[i];
                orgVal[i] += 1;
                neg = 1;
            }

            if (dataType == ADC_DATA_WIDTH_12) {
                result[i].value = (unsigned int)(((orgVal[i] & 0xffff) >> 4) / coe);
                result[i].volt = result[i].value / 2048.0 * ref;
            } else if ((dataType == ADC_DATA_WIDTH_14_WITH_16_AVERAGE) ||
                       (dataType == ADC_DATA_WIDTH_14_WITH_64_AVERAGE)) {
                result[i].value = (unsigned int)(((orgVal[i] & 0xffff) >> 2) / coe);
                result[i].volt = result[i].value / 8192.0 * ref;
            } else if ((dataType == ADC_DATA_WIDTH_16_WITH_128_AVERAGE) ||
                       (dataType == ADC_DATA_WIDTH_16_WITH_256_AVERAGE)) {
                result[i].value = (unsigned int)((orgVal[i] & 0xffff) / coe);
                result[i].volt = result[i].value / 32768.0 * ref;
            }

            if (neg) {
                result[i].volt = -result[i].volt;
            }
        }
    }
}

/****************************************************************************/ /**
 * @brief  ADC mask or unmask certain or all interrupt
 *
 * @param  intType: interrupt type
 * @param  intMask: mask or unmask
 *
 * @return None
 *
*******************************************************************************/
BL_Mask_Type ADC_IntGetMask(ADC_INT_Type intType)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_GPIP_ADC_INT_TYPE(intType));
    CHECK_PARAM(IS_BL_MASK_TYPE(intMask));

    switch (intType) {
        case ADC_INT_POS_SATURATION:
            tmpVal = BL_RD_REG(AON_BASE, AON_GPADC_REG_ISR);
            return BL_IS_REG_BIT_SET(tmpVal, AON_GPADC_POS_SATUR_MASK);
            break;

        case ADC_INT_NEG_SATURATION:
            tmpVal = BL_RD_REG(AON_BASE, AON_GPADC_REG_ISR);
            return BL_IS_REG_BIT_SET(tmpVal, AON_GPADC_NEG_SATUR_MASK);
            break;

        case ADC_INT_FIFO_UNDERRUN:
            tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPADC_CONFIG);
            return BL_IS_REG_BIT_SET(tmpVal, GPIP_GPADC_FIFO_UNDERRUN_MASK);
            break;

        case ADC_INT_FIFO_OVERRUN:
            tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPADC_CONFIG);
            return BL_IS_REG_BIT_SET(tmpVal, GPIP_GPADC_FIFO_OVERRUN_MASK);
            break;

        case ADC_INT_ADC_READY:
            tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPADC_CONFIG);
            return BL_IS_REG_BIT_SET(tmpVal, GPIP_GPADC_RDY_MASK);
            break;

        default:
            break;
    }
    return 0;
}

/****************************************************************************/ /**
 * @brief  ADC mask or unmask certain or all interrupt
 *
 * @param  intType: interrupt type
 * @param  intMask: mask or unmask
 *
 * @return None
 *
*******************************************************************************/
void ADC_IntMask(ADC_INT_Type intType, BL_Mask_Type intMask)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_GPIP_ADC_INT_TYPE(intType));
    CHECK_PARAM(IS_BL_MASK_TYPE(intMask));

    switch (intType) {
        case ADC_INT_POS_SATURATION:
            tmpVal = BL_RD_REG(AON_BASE, AON_GPADC_REG_ISR);

            if (intMask == UNMASK) {
                /* Enable this interrupt */
                tmpVal = BL_CLR_REG_BIT(tmpVal, AON_GPADC_POS_SATUR_MASK);
            } else {
                /* Disable this interrupt */
                tmpVal = BL_SET_REG_BIT(tmpVal, AON_GPADC_POS_SATUR_MASK);
            }

            BL_WR_REG(AON_BASE, AON_GPADC_REG_ISR, tmpVal);
            break;

        case ADC_INT_NEG_SATURATION:
            tmpVal = BL_RD_REG(AON_BASE, AON_GPADC_REG_ISR);

            if (intMask == UNMASK) {
                /* Enable this interrupt */
                tmpVal = BL_CLR_REG_BIT(tmpVal, AON_GPADC_NEG_SATUR_MASK);
            } else {
                /* Disable this interrupt */
                tmpVal = BL_SET_REG_BIT(tmpVal, AON_GPADC_NEG_SATUR_MASK);
            }

            BL_WR_REG(AON_BASE, AON_GPADC_REG_ISR, tmpVal);
            break;

        case ADC_INT_FIFO_UNDERRUN:
            tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPADC_CONFIG);

            if (intMask == UNMASK) {
                /* Enable this interrupt */
                tmpVal = BL_CLR_REG_BIT(tmpVal, GPIP_GPADC_FIFO_UNDERRUN_MASK);
            } else {
                /* Disable this interrupt */
                tmpVal = BL_SET_REG_BIT(tmpVal, GPIP_GPADC_FIFO_UNDERRUN_MASK);
            }

            BL_WR_REG(GPIP_BASE, GPIP_GPADC_CONFIG, tmpVal);
            break;

        case ADC_INT_FIFO_OVERRUN:
            tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPADC_CONFIG);

            if (intMask == UNMASK) {
                /* Enable this interrupt */
                tmpVal = BL_CLR_REG_BIT(tmpVal, GPIP_GPADC_FIFO_OVERRUN_MASK);
            } else {
                /* Disable this interrupt */
                tmpVal = BL_SET_REG_BIT(tmpVal, GPIP_GPADC_FIFO_OVERRUN_MASK);
            }

            BL_WR_REG(GPIP_BASE, GPIP_GPADC_CONFIG, tmpVal);
            break;

        case ADC_INT_ADC_READY:
            tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPADC_CONFIG);

            if (intMask == UNMASK) {
                /* Enable this interrupt */
                tmpVal = BL_CLR_REG_BIT(tmpVal, GPIP_GPADC_RDY_MASK);
            } else {
                /* Disable this interrupt */
                tmpVal = BL_SET_REG_BIT(tmpVal, GPIP_GPADC_RDY_MASK);
            }

            BL_WR_REG(GPIP_BASE, GPIP_GPADC_CONFIG, tmpVal);
            break;

        case ADC_INT_ALL:
            if (intMask == UNMASK) {
                /* Enable this interrupt */
                tmpVal = BL_RD_REG(AON_BASE, AON_GPADC_REG_ISR);
                tmpVal = BL_CLR_REG_BIT(tmpVal, AON_GPADC_POS_SATUR_MASK);
                tmpVal = BL_CLR_REG_BIT(tmpVal, AON_GPADC_NEG_SATUR_MASK);
                BL_WR_REG(AON_BASE, AON_GPADC_REG_ISR, tmpVal);

                tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPADC_CONFIG);
                tmpVal = BL_CLR_REG_BIT(tmpVal, GPIP_GPADC_FIFO_UNDERRUN_MASK);
                tmpVal = BL_CLR_REG_BIT(tmpVal, GPIP_GPADC_FIFO_OVERRUN_MASK);
                tmpVal = BL_CLR_REG_BIT(tmpVal, GPIP_GPADC_RDY_MASK);
                BL_WR_REG(GPIP_BASE, GPIP_GPADC_CONFIG, tmpVal);
            } else {
                /* Disable this interrupt */
                tmpVal = BL_RD_REG(AON_BASE, AON_GPADC_REG_ISR);
                tmpVal = BL_SET_REG_BIT(tmpVal, AON_GPADC_POS_SATUR_MASK);
                tmpVal = BL_SET_REG_BIT(tmpVal, AON_GPADC_NEG_SATUR_MASK);
                BL_WR_REG(AON_BASE, AON_GPADC_REG_ISR, tmpVal);

                tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPADC_CONFIG);
                tmpVal = BL_SET_REG_BIT(tmpVal, GPIP_GPADC_FIFO_OVERRUN_MASK);
                tmpVal = BL_SET_REG_BIT(tmpVal, GPIP_GPADC_FIFO_UNDERRUN_MASK);
                tmpVal = BL_SET_REG_BIT(tmpVal, GPIP_GPADC_RDY_MASK);
                BL_WR_REG(GPIP_BASE, GPIP_GPADC_CONFIG, tmpVal);
            }

            break;

        default:
            break;
    }
}

/****************************************************************************/ /**
 * @brief  ADC clear certain or all interrupt
 *
 * @param  intType: interrupt type
 *
 * @return None
 *
*******************************************************************************/
void ADC_IntClr(ADC_INT_Type intType)
{
    uint32_t tmpVal;

    /* Check the parameters */
    CHECK_PARAM(IS_GPIP_ADC_INT_TYPE(intType));

    switch (intType) {
        case ADC_INT_POS_SATURATION:
            tmpVal = BL_RD_REG(AON_BASE, AON_GPADC_REG_ISR);
            tmpVal = BL_CLR_REG_BIT(tmpVal, AON_GPADC_POS_SATUR_CLR);
            BL_WR_REG(AON_BASE, AON_GPADC_REG_ISR, tmpVal);

            tmpVal = BL_SET_REG_BIT(tmpVal, AON_GPADC_POS_SATUR_CLR);
            BL_WR_REG(AON_BASE, AON_GPADC_REG_ISR, tmpVal);

            /*Manual reset*/
            tmpVal = BL_RD_REG(AON_BASE, AON_GPADC_REG_ISR);
            tmpVal = BL_CLR_REG_BIT(tmpVal, AON_GPADC_POS_SATUR_CLR);
            BL_WR_REG(AON_BASE, AON_GPADC_REG_ISR, tmpVal);

            break;

        case ADC_INT_NEG_SATURATION:
            tmpVal = BL_RD_REG(AON_BASE, AON_GPADC_REG_ISR);
            tmpVal = BL_CLR_REG_BIT(tmpVal, AON_GPADC_NEG_SATUR_CLR);
            BL_WR_REG(AON_BASE, AON_GPADC_REG_ISR, tmpVal);

            tmpVal = BL_SET_REG_BIT(tmpVal, AON_GPADC_NEG_SATUR_CLR);
            BL_WR_REG(AON_BASE, AON_GPADC_REG_ISR, tmpVal);

            /*Manual reset*/
            tmpVal = BL_RD_REG(AON_BASE, AON_GPADC_REG_ISR);
            tmpVal = BL_CLR_REG_BIT(tmpVal, AON_GPADC_NEG_SATUR_CLR);
            BL_WR_REG(AON_BASE, AON_GPADC_REG_ISR, tmpVal);

            break;

        case ADC_INT_FIFO_UNDERRUN:
            tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPADC_CONFIG);
            tmpVal = BL_CLR_REG_BIT(tmpVal, GPIP_GPADC_FIFO_UNDERRUN_CLR);
            BL_WR_REG(GPIP_BASE, GPIP_GPADC_CONFIG, tmpVal);

            tmpVal = BL_SET_REG_BIT(tmpVal, GPIP_GPADC_FIFO_UNDERRUN_CLR);
            BL_WR_REG(GPIP_BASE, GPIP_GPADC_CONFIG, tmpVal);

            /*Manual reset*/
            tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPADC_CONFIG);
            tmpVal = BL_CLR_REG_BIT(tmpVal, GPIP_GPADC_FIFO_UNDERRUN_CLR);
            BL_WR_REG(GPIP_BASE, GPIP_GPADC_CONFIG, tmpVal);

            break;

        case ADC_INT_FIFO_OVERRUN:
            tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPADC_CONFIG);
            tmpVal = BL_CLR_REG_BIT(tmpVal, GPIP_GPADC_FIFO_OVERRUN_CLR);
            BL_WR_REG(GPIP_BASE, GPIP_GPADC_CONFIG, tmpVal);

            tmpVal = BL_SET_REG_BIT(tmpVal, GPIP_GPADC_FIFO_OVERRUN_CLR);
            BL_WR_REG(GPIP_BASE, GPIP_GPADC_CONFIG, tmpVal);

            /*Manual reset*/
            tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPADC_CONFIG);
            tmpVal = BL_CLR_REG_BIT(tmpVal, GPIP_GPADC_FIFO_OVERRUN_CLR);
            BL_WR_REG(GPIP_BASE, GPIP_GPADC_CONFIG, tmpVal);

            break;

        case ADC_INT_ADC_READY:
            tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPADC_CONFIG);
            tmpVal = BL_CLR_REG_BIT(tmpVal, GPIP_GPADC_RDY_CLR);
            BL_WR_REG(GPIP_BASE, GPIP_GPADC_CONFIG, tmpVal);

            tmpVal = BL_SET_REG_BIT(tmpVal, GPIP_GPADC_RDY_CLR);
            BL_WR_REG(GPIP_BASE, GPIP_GPADC_CONFIG, tmpVal);

            /*Manual reset*/
            tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPADC_CONFIG);
            tmpVal = BL_CLR_REG_BIT(tmpVal, GPIP_GPADC_RDY_CLR);
            BL_WR_REG(GPIP_BASE, GPIP_GPADC_CONFIG, tmpVal);

            break;

        case ADC_INT_ALL:
            tmpVal = BL_RD_REG(AON_BASE, AON_GPADC_REG_ISR);
            tmpVal = BL_CLR_REG_BIT(tmpVal, AON_GPADC_POS_SATUR_CLR);
            tmpVal = BL_CLR_REG_BIT(tmpVal, AON_GPADC_NEG_SATUR_CLR);
            BL_WR_REG(AON_BASE, AON_GPADC_REG_ISR, tmpVal);

            tmpVal = BL_SET_REG_BIT(tmpVal, AON_GPADC_POS_SATUR_CLR);
            tmpVal = BL_SET_REG_BIT(tmpVal, AON_GPADC_NEG_SATUR_CLR);
            BL_WR_REG(AON_BASE, AON_GPADC_REG_ISR, tmpVal);

            /*Manual reset*/
            tmpVal = BL_RD_REG(AON_BASE, AON_GPADC_REG_ISR);
            tmpVal = BL_CLR_REG_BIT(tmpVal, AON_GPADC_POS_SATUR_CLR);
            tmpVal = BL_CLR_REG_BIT(tmpVal, AON_GPADC_NEG_SATUR_CLR);
            BL_WR_REG(AON_BASE, AON_GPADC_REG_ISR, tmpVal);

            tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPADC_CONFIG);
            tmpVal = BL_CLR_REG_BIT(tmpVal, GPIP_GPADC_FIFO_UNDERRUN_CLR);
            tmpVal = BL_CLR_REG_BIT(tmpVal, GPIP_GPADC_FIFO_OVERRUN_CLR);
            tmpVal = BL_CLR_REG_BIT(tmpVal, GPIP_GPADC_RDY_CLR);
            BL_WR_REG(GPIP_BASE, GPIP_GPADC_CONFIG, tmpVal);

            tmpVal = BL_SET_REG_BIT(tmpVal, GPIP_GPADC_FIFO_UNDERRUN_CLR);
            tmpVal = BL_SET_REG_BIT(tmpVal, GPIP_GPADC_FIFO_OVERRUN_CLR);
            tmpVal = BL_SET_REG_BIT(tmpVal, GPIP_GPADC_RDY_CLR);
            BL_WR_REG(GPIP_BASE, GPIP_GPADC_CONFIG, tmpVal);

            /*Manual reset*/
            tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPADC_CONFIG);
            tmpVal = BL_CLR_REG_BIT(tmpVal, GPIP_GPADC_FIFO_UNDERRUN_CLR);
            tmpVal = BL_CLR_REG_BIT(tmpVal, GPIP_GPADC_FIFO_OVERRUN_CLR);
            tmpVal = BL_CLR_REG_BIT(tmpVal, GPIP_GPADC_RDY_CLR);
            BL_WR_REG(GPIP_BASE, GPIP_GPADC_CONFIG, tmpVal);

            break;

        default:
            break;
    }
}

/****************************************************************************/ /**
 * @brief  ADC get interrupt status
 *
 * @param  intType: interrupt type
 *
 * @return SET or RESET
 *
*******************************************************************************/
BL_Sts_Type ADC_GetIntStatus(ADC_INT_Type intType)
{
    uint32_t tmpVal;
    BL_Sts_Type bitStatus = RESET;

    /* Check the parameters */
    CHECK_PARAM(IS_GPIP_ADC_INT_TYPE(intType));

    switch (intType) {
        case ADC_INT_POS_SATURATION:
            tmpVal = BL_RD_REG(AON_BASE, AON_GPADC_REG_ISR);
            bitStatus = (BL_IS_REG_BIT_SET(tmpVal, AON_GPADC_POS_SATUR)) ? SET : RESET;
            break;

        case ADC_INT_NEG_SATURATION:
            tmpVal = BL_RD_REG(AON_BASE, AON_GPADC_REG_ISR);
            bitStatus = (BL_IS_REG_BIT_SET(tmpVal, AON_GPADC_NEG_SATUR)) ? SET : RESET;
            break;

        case ADC_INT_FIFO_UNDERRUN:
            tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPADC_CONFIG);
            bitStatus = (BL_IS_REG_BIT_SET(tmpVal, GPIP_GPADC_FIFO_UNDERRUN)) ? SET : RESET;
            break;

        case ADC_INT_FIFO_OVERRUN:
            tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPADC_CONFIG);
            bitStatus = (BL_IS_REG_BIT_SET(tmpVal, GPIP_GPADC_FIFO_OVERRUN)) ? SET : RESET;
            break;

        case ADC_INT_ADC_READY:
            tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPADC_CONFIG);
            bitStatus = (BL_IS_REG_BIT_SET(tmpVal, GPIP_GPADC_RDY)) ? SET : RESET;
            break;

        case ADC_INT_ALL:
            break;

        default:
            break;
    }

    return bitStatus;
}

/****************************************************************************/ /**
 * @brief  ADC install interrupt callback
 *
 * @param  intType: ADC interrupt type
 * @param  cbFun: ADC interrupt callback
 *
 * @return None
 *
*******************************************************************************/
void ADC_Int_Callback_Install(ADC_INT_Type intType, intCallback_Type *cbFun)
{
    /* Check the parameters */
    CHECK_PARAM(IS_GPIP_ADC_INT_TYPE(intType));

    adcIntCbfArra[intType] = cbFun;
}

/****************************************************************************/ /**
 * @brief  ADC DMA interrupt handler
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
#ifndef BFLB_USE_HAL_DRIVER
void GPADC_DMA_IRQHandler(void)
{
    if (ADC_IntGetMask(ADC_INT_POS_SATURATION) == UNMASK && ADC_GetIntStatus(ADC_INT_POS_SATURATION) == SET) {
        ADC_IntClr(ADC_INT_POS_SATURATION);

        if (adcIntCbfArra[ADC_INT_POS_SATURATION] != NULL) {
            adcIntCbfArra[ADC_INT_POS_SATURATION]();
        }
    }

    if (ADC_IntGetMask(ADC_INT_NEG_SATURATION) == UNMASK && ADC_GetIntStatus(ADC_INT_NEG_SATURATION) == SET) {
        ADC_IntClr(ADC_INT_NEG_SATURATION);

        if (adcIntCbfArra[ADC_INT_NEG_SATURATION] != NULL) {
            adcIntCbfArra[ADC_INT_NEG_SATURATION]();
        }
    }

    if (ADC_IntGetMask(ADC_INT_FIFO_UNDERRUN) == UNMASK && ADC_GetIntStatus(ADC_INT_FIFO_UNDERRUN) == SET) {
        ADC_IntClr(ADC_INT_FIFO_UNDERRUN);

        if (adcIntCbfArra[ADC_INT_FIFO_UNDERRUN] != NULL) {
            adcIntCbfArra[ADC_INT_FIFO_UNDERRUN]();
        }
    }

    if (ADC_IntGetMask(ADC_INT_FIFO_OVERRUN) == UNMASK && ADC_GetIntStatus(ADC_INT_FIFO_OVERRUN) == SET) {
        ADC_IntClr(ADC_INT_FIFO_OVERRUN);

        if (adcIntCbfArra[ADC_INT_FIFO_OVERRUN] != NULL) {
            adcIntCbfArra[ADC_INT_FIFO_OVERRUN]();
        }
    }

    if (ADC_IntGetMask(ADC_INT_ADC_READY) == UNMASK && ADC_GetIntStatus(ADC_INT_ADC_READY) == SET) {
        ADC_IntClr(ADC_INT_ADC_READY);

        if (adcIntCbfArra[ADC_INT_ADC_READY] != NULL) {
            adcIntCbfArra[ADC_INT_ADC_READY]();
        }
    }
}
#endif

/****************************************************************************/ /**
 * @brief  ADC VBAT enable
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void ADC_Vbat_Enable(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(AON_BASE, AON_GPADC_REG_CONFIG2);
    tmpVal = BL_SET_REG_BIT(tmpVal, AON_GPADC_VBAT_EN);
    BL_WR_REG(AON_BASE, AON_GPADC_REG_CONFIG2, tmpVal);
}

/****************************************************************************/ /**
 * @brief  ADC VBAT disable
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void ADC_Vbat_Disable(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(AON_BASE, AON_GPADC_REG_CONFIG2);
    tmpVal = BL_CLR_REG_BIT(tmpVal, AON_GPADC_VBAT_EN);
    BL_WR_REG(AON_BASE, AON_GPADC_REG_CONFIG2, tmpVal);
}

/****************************************************************************/ /**
 * @brief  ADC TSEN Config
 *
 * @param  tsenMod: None
 *
 * @return None
 *
*******************************************************************************/
void ADC_Tsen_Init(ADC_TSEN_MOD_Type tsenMod)
{
    uint32_t tmpVal;

    CHECK_PARAM(IS_AON_ADC_TSEN_MOD_TYPE(type));

    /* config gpadc_reg_cmd */
    tmpVal = BL_RD_REG(AON_BASE, AON_GPADC_REG_CMD);
    /* enable sensor dc test mux*/
    tmpVal = BL_CLR_REG_BIT(tmpVal, AON_GPADC_SEN_TEST_EN);
    /*selected sen output current channel*/
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_GPADC_SEN_SEL, 0);
    /* enable chip sensor*/
    tmpVal = BL_CLR_REG_BIT(tmpVal, AON_GPADC_CHIP_SEN_PU);
    /*dwa_en */
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_GPADC_DWA_EN, 1);
    BL_WR_REG(AON_BASE, AON_GPADC_REG_CMD, tmpVal);

    /* config 2 */
    tmpVal = BL_RD_REG(AON_BASE, AON_GPADC_REG_CONFIG2);
    /*tsvbe low=0*/
    tmpVal = BL_CLR_REG_BIT(tmpVal, AON_GPADC_TSVBE_LOW);
    /*dly_sel=2*/
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_GPADC_DLY_SEL, 2);
    /*test_sel=0*/
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_GPADC_TEST_SEL, 0);
    /*test_en=0*/
    tmpVal = BL_CLR_REG_BIT(tmpVal, AON_GPADC_TEST_EN);
    /*ts_en*/
    tmpVal = BL_SET_REG_BIT(tmpVal, AON_GPADC_TS_EN);
    /*select tsen ext or inner*/
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_GPADC_TSEXT_SEL, tsenMod);

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_GPADC_PGA_VCM, 2);
    /*pga vcmi enable*/
    tmpVal = BL_CLR_REG_BIT(tmpVal, AON_GPADC_PGA_VCMI_EN);
    /*0:512uS;1:16mS;2:32mS;3:64mS*/
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_GPADC_PGA_OS_CAL, 0);

    BL_WR_REG(AON_BASE, AON_GPADC_REG_CONFIG2, tmpVal);

    /* config 3 */
    tmpVal = BL_RD_REG(AON_BASE, AON_GPADC_REG_CONFIG1);
    /* set gpadc_dither_en */
    tmpVal = BL_SET_REG_BIT(tmpVal, AON_GPADC_DITHER_EN);
    BL_WR_REG(AON_BASE, AON_GPADC_REG_CONFIG1, tmpVal);

    /* set 4000F90C[19](gpadc_mic2_diff) = 1
     * debug advise form Ran
     * 2020.08.26
     */
    tmpVal = BL_RD_REG(AON_BASE, AON_GPADC_REG_CMD);
    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_GPADC_MIC2_DIFF, 1);
    BL_WR_REG(AON_BASE, AON_GPADC_REG_CMD, tmpVal);
}

/****************************************************************************/ /**
 * @brief  ADC TSEN Enable
 *
 * @return None
 *
*******************************************************************************/
void ADC_Tsen_Enable(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(AON_BASE, AON_GPADC_REG_CONFIG2);
    tmpVal = BL_SET_REG_BIT(tmpVal, AON_GPADC_TS_EN);
    BL_WR_REG(AON_BASE, AON_GPADC_REG_CONFIG2, tmpVal);
}

/****************************************************************************/ /**
 * @brief  ADC TSEN Disable
 *
 * @return None
 *
*******************************************************************************/
void ADC_Tsen_Disable(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(AON_BASE, AON_GPADC_REG_CONFIG2);
    tmpVal = BL_CLR_REG_BIT(tmpVal, AON_GPADC_TS_EN);
    BL_WR_REG(AON_BASE, AON_GPADC_REG_CONFIG2, tmpVal);
}

/****************************************************************************/ /**
 * @brief  ADC Clear fifo
 *
 * @return None
 *
*******************************************************************************/
void ADC_FIFO_Clear(void)
{
    uint32_t tmpVal;

    /* clear fifo by SET GPIP_GPADC_FIFO_CLR bit*/
    tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPADC_CONFIG);
    tmpVal = BL_SET_REG_BIT(tmpVal, GPIP_GPADC_FIFO_CLR);
    BL_WR_REG(GPIP_BASE, GPIP_GPADC_CONFIG, tmpVal);
}

/****************************************************************************/ /**
 * @brief  config pga
 *
 * @param  pga_vcmi_enable: enable or not vcmi
 * @param  pga_os_cal: pga os cal value
 * @return None
 *
*******************************************************************************/
void ADC_PGA_Config(uint8_t pga_vcmi_enable, uint8_t pga_os_cal)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(AON_BASE, AON_GPADC_REG_CONFIG2);

    if (pga_vcmi_enable) {
        tmpVal = BL_SET_REG_BIT(tmpVal, AON_GPADC_PGA_VCMI_EN);
    } else {
        tmpVal = BL_CLR_REG_BIT(tmpVal, AON_GPADC_PGA_VCMI_EN);
    }

    tmpVal = BL_SET_REG_BITS_VAL(tmpVal, AON_GPADC_PGA_OS_CAL, pga_os_cal);

    BL_WR_REG(AON_BASE, AON_GPADC_REG_CONFIG2, tmpVal);
}
/****************************************************************************/ /**
 * @brief  TSEN_Get_V_Error
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
uint32_t TSEN_Get_V_Error(void)
{
    uint32_t v0 = 0, v1 = 0;
    uint32_t v_error = 0;
    uint32_t regVal = 0;
    ADC_Result_Type result;
    uint32_t tmpVal;
    uint8_t gainCalEnabled = 0;

    /* clear fifo by SET GPIP_GPADC_FIFO_CLR bit*/
    tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPADC_CONFIG);
    tmpVal = BL_SET_REG_BIT(tmpVal, GPIP_GPADC_FIFO_CLR);
    BL_WR_REG(GPIP_BASE, GPIP_GPADC_CONFIG, tmpVal);

    ADC_SET_TSVBE_LOW();

    ADC_Start();

    while (ADC_Get_FIFO_Count() == 0)
        ;

    regVal = ADC_Read_FIFO();
    gainCalEnabled = adcGainCoeffCal.adcGainCoeffEnable;
    adcGainCoeffCal.adcGainCoeffEnable = 0;
    ADC_Parse_Result(&regVal, 1, &result);
    adcGainCoeffCal.adcGainCoeffEnable = gainCalEnabled;
    v0 = result.value;

    /* clear fifo by SET GPIP_GPADC_FIFO_CLR bit*/
    tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPADC_CONFIG);
    tmpVal = BL_SET_REG_BIT(tmpVal, GPIP_GPADC_FIFO_CLR);
    BL_WR_REG(GPIP_BASE, GPIP_GPADC_CONFIG, tmpVal);

    ADC_SET_TSVBE_HIGH();

    ADC_Start();

    while (ADC_Get_FIFO_Count() == 0)
        ;

    regVal = ADC_Read_FIFO();
    gainCalEnabled = adcGainCoeffCal.adcGainCoeffEnable;
    adcGainCoeffCal.adcGainCoeffEnable = 0;
    ADC_Parse_Result(&regVal, 1, &result);
    adcGainCoeffCal.adcGainCoeffEnable = gainCalEnabled;
    v1 = result.value;

    v_error = v0 - v1;

    return v_error;
}

/****************************************************************************/ /**
 * @brief  Trim TSEN
 *
 * @param  tsen_offset: None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION ADC_Trim_TSEN(uint16_t *tsen_offset)
{
    Efuse_TSEN_Refcode_Corner_Type trim;

    EF_Ctrl_Read_TSEN_Trim(&trim);
    if (trim.tsenRefcodeCornerEn) {
        if (trim.tsenRefcodeCornerParity == EF_Ctrl_Get_Trim_Parity(trim.tsenRefcodeCorner, 12)) {
            *tsen_offset = trim.tsenRefcodeCorner;

            return SUCCESS;
        }
    }

    return ERROR;
}

/****************************************************************************/ /**
 * @brief  SET ADC TSEN TSVBE LOW/HIGH
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void ADC_SET_TSVBE_LOW(void)
{
    uint32_t tmpVal;
    tmpVal = BL_RD_REG(AON_BASE, AON_GPADC_REG_CONFIG2);
    tmpVal = BL_CLR_REG_BIT(tmpVal, AON_GPADC_TSVBE_LOW);
    BL_WR_REG(AON_BASE, AON_GPADC_REG_CONFIG2, tmpVal);
}

/****************************************************************************/ /**
 * @brief  SET ADC TSEN TSVBE LOW/HIGH
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void ADC_SET_TSVBE_HIGH(void)
{
    uint32_t tmpVal;
    tmpVal = BL_RD_REG(AON_BASE, AON_GPADC_REG_CONFIG2);
    tmpVal = BL_SET_REG_BIT(tmpVal, AON_GPADC_TSVBE_LOW);
    BL_WR_REG(AON_BASE, AON_GPADC_REG_CONFIG2, tmpVal);
}

/****************************************************************************/ /**
 * @brief  SET ADC TSEN TSVBE LOW/HIGH
 *
 * @param  tsen_offset: tsen_offset form efuse trim data
 *
 * @return tempture
 *
*******************************************************************************/
float TSEN_Get_Temp(uint32_t tsen_offset)
{
    uint32_t v0 = 0, v1 = 0;
    float temp = 0;
    uint32_t regVal = 0;
    ADC_Result_Type result;
    uint32_t tmpVal;
    uint8_t gainCalEnabled = 0;

    /* clear fifo by SET GPIP_GPADC_FIFO_CLR bit*/
    tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPADC_CONFIG);
    tmpVal = BL_SET_REG_BIT(tmpVal, GPIP_GPADC_FIFO_CLR);
    BL_WR_REG(GPIP_BASE, GPIP_GPADC_CONFIG, tmpVal);

    ADC_SET_TSVBE_LOW();

    ADC_Start();

    while (ADC_Get_FIFO_Count() == 0)
        ;

    regVal = ADC_Read_FIFO();

    gainCalEnabled = adcGainCoeffCal.adcGainCoeffEnable;
    adcGainCoeffCal.adcGainCoeffEnable = 0;
    ADC_Parse_Result(&regVal, 1, &result);
    adcGainCoeffCal.adcGainCoeffEnable = gainCalEnabled;
    v0 = result.value;

    /* clear fifo by SET GPIP_GPADC_FIFO_CLR bit*/
    tmpVal = BL_RD_REG(GPIP_BASE, GPIP_GPADC_CONFIG);
    tmpVal = BL_SET_REG_BIT(tmpVal, GPIP_GPADC_FIFO_CLR);
    BL_WR_REG(GPIP_BASE, GPIP_GPADC_CONFIG, tmpVal);

    ADC_SET_TSVBE_HIGH();

    ADC_Start();

    while (ADC_Get_FIFO_Count() == 0)
        ;

    regVal = ADC_Read_FIFO();
    gainCalEnabled = adcGainCoeffCal.adcGainCoeffEnable;
    adcGainCoeffCal.adcGainCoeffEnable = 0;
    ADC_Parse_Result(&regVal, 1, &result);
    adcGainCoeffCal.adcGainCoeffEnable = gainCalEnabled;
    v1 = result.value;

    if (v0 > v1) {
        temp = (((float)v0 - (float)v1) - (float)tsen_offset) / 7.753;
    } else {
        temp = (((float)v1 - (float)v0) - (float)tsen_offset) / 7.753;
    }

    return temp;
}

/****************************************************************************/ /**
 * @brief  ADC MIC Config
 *
 * @param  adc_mic_config: adc_mic_config
 *
 * @return success or not
 *
*******************************************************************************/
BL_Err_Type ADC_Mic_Init(ADC_MIC_Type *adc_mic_config)
{
    uint32_t tmpVal1 = 0, tmpVal2 = 0;

    CHECK_PARAM(IS_ADC_MICBOOST_DB_Type(adc_mic_config->micboostDb));
    CHECK_PARAM(IS_PGA2_GAIN_Type(adc_mic_config->micPga2Gain));
    CHECK_PARAM(IS_ADC_MIC_MODE_Type(adc_mic_config->mic1Mode));
    CHECK_PARAM(IS_ADC_MIC_MODE_Type(adc_mic_config->mic2Mode));
    CHECK_PARAM(IS_BL_Fun_Type(adc_mic_config->dwaEn));
    CHECK_PARAM(IS_BL_Fun_Type(adc_mic_config->micboostBypassEn));
    CHECK_PARAM(IS_BL_Fun_Type(adc_mic_config->micPgaEn));
    CHECK_PARAM(IS_BL_Fun_Type(adc_mic_config->micBiasEn));

    tmpVal2 = BL_RD_REG(AON_BASE, AON_GPADC_REG_CONFIG2);

    tmpVal1 = BL_RD_REG(AON_BASE, AON_GPADC_REG_CMD);
    tmpVal1 = BL_SET_REG_BITS_VAL(tmpVal1, AON_GPADC_MICBOOST_32DB_EN, adc_mic_config->micboostDb);
    tmpVal1 = BL_SET_REG_BITS_VAL(tmpVal1, AON_GPADC_MIC_PGA2_GAIN, adc_mic_config->micPga2Gain);
    tmpVal1 = BL_SET_REG_BITS_VAL(tmpVal1, AON_GPADC_MIC1_DIFF, adc_mic_config->mic1Mode);
    tmpVal1 = BL_SET_REG_BITS_VAL(tmpVal1, AON_GPADC_MIC2_DIFF, adc_mic_config->mic2Mode);
    tmpVal1 = BL_SET_REG_BITS_VAL(tmpVal1, AON_GPADC_DWA_EN, adc_mic_config->dwaEn);
    tmpVal1 = BL_SET_REG_BITS_VAL(tmpVal1, AON_GPADC_BYP_MICBOOST, adc_mic_config->micboostBypassEn);

    if (BL_IS_REG_BIT_SET(tmpVal2, AON_GPADC_PGA_EN) && adc_mic_config->micPgaEn == ENABLE) {
        /* 0x4000F914[13] and 0x4000F90c[15] Cannot be both Enable*/
        return ERROR;
    } else {
        tmpVal1 = BL_SET_REG_BITS_VAL(tmpVal1, AON_GPADC_MICPGA_EN, adc_mic_config->micPgaEn);
    }

    tmpVal1 = BL_SET_REG_BITS_VAL(tmpVal1, AON_GPADC_MICBIAS_EN, adc_mic_config->micBiasEn);

    BL_WR_REG(AON_BASE, AON_GPADC_REG_CMD, tmpVal1);

    return SUCCESS;
}

/****************************************************************************/ /**
 * @brief  ADC MIC bias control
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void ADC_MIC_Bias_Enable(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(AON_BASE, AON_GPADC_REG_CMD);
    tmpVal = BL_SET_REG_BIT(tmpVal, AON_GPADC_MICBIAS_EN);
    BL_WR_REG(AON_BASE, AON_GPADC_REG_CMD, tmpVal);
}

/****************************************************************************/ /**
 * @brief  ADC MIC bias control
 *
 * @param  None
 *
 * @return None
 *
*******************************************************************************/
void ADC_MIC_Bias_Disable(void)
{
    uint32_t tmpVal;

    tmpVal = BL_RD_REG(AON_BASE, AON_GPADC_REG_CMD);
    tmpVal = BL_CLR_REG_BIT(tmpVal, AON_GPADC_MICBIAS_EN);
    BL_WR_REG(AON_BASE, AON_GPADC_REG_CMD, tmpVal);
}

/****************************************************************************/ /**
 * @brief  Trim ADC Gain
 *
 * @param  None
 *
 * @return SUCCESS or ERROR
 *
*******************************************************************************/
BL_Err_Type ATTR_CLOCK_SECTION ADC_Gain_Trim(void)
{
    Efuse_ADC_Gain_Coeff_Type trim;
    uint32_t tmp;

    EF_Ctrl_Read_ADC_Gain_Trim(&trim);

    if (trim.adcGainCoeffEn) {
        if (trim.adcGainCoeffParity == EF_Ctrl_Get_Trim_Parity(trim.adcGainCoeff, 12)) {
            adcGainCoeffCal.adcGainCoeffEnable = ENABLE;
            adcGainCoeffCal.adcgainCoeffVal = trim.adcGainCoeff;
            tmp = adcGainCoeffCal.adcgainCoeffVal;

            if (tmp & 0x800) {
                tmp = ~tmp;
                tmp += 1;
                tmp = tmp & 0xfff;
                //printf("val==%08x\r\n",(unsigned int)tmp);
                adcGainCoeffCal.coe = (1.0 + ((float)tmp / 2048.0));
                //printf("coe==%0f\r\n",adcGainCoeffCal.coe);
            } else {
                adcGainCoeffCal.coe = (1.0 - ((float)tmp / 2048.0));
                //printf("coe==%0f\r\n",adcGainCoeffCal.coe);
            }

            return SUCCESS;
        }
    }

    return ERROR;
}

/*@} end of group ADC_Public_Functions */

/*@} end of group ADC */

/*@} end of group BL808_Peripheral_Driver */
