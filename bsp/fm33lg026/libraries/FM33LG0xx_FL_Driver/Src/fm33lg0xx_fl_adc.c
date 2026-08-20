/**
  ****************************************************************************************************
  * @file    fm33lg0xx_fl_adc.c
  * @author  FMSH Application Team
  * @brief   Src file of ADC FL Module
  ****************************************************************************************************
  * @attention
  *
  * Copyright (c) [2021] [Fudan Microelectronics]
  * THIS SOFTWARE is licensed under Mulan PSL v2.
  * You can use this software according to the terms and conditions of the Mulan PSL v2.
  * You may obtain a copy of Mulan PSL v2 at:
  *          http://license.coscl.org.cn/MulanPSL2
  * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
  * EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
  * MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
  * See the Mulan PSL v2 for more details.
  *
  ****************************************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "fm33lg0xx_fl.h"

/** @addtogroup FM33LG0xx_FL_Driver
  * @{
  */

/** @addtogroup ADC
  * @{
  */

#ifdef FL_ADC_DRIVER_ENABLED

/* Private macros ------------------------------------------------------------*/
/** @addtogroup ADC_FL_Private_Macros
  * @{
  */

#define         IS_FL_ADC_INSTANCE(INSTANCE)                ((INSTANCE) == ADC)

#define         IS_FL_ADC_CLK_SOURCE(__VALUE__)             (((__VALUE__) == FL_CMU_ADC_CLK_SOURCE_RCLF)||\
                                                            ((__VALUE__) == FL_CMU_ADC_CLK_SOURCE_RCHF)||\
                                                            ((__VALUE__) == FL_CMU_ADC_CLK_SOURCE_XTHF)||\
                                                            ((__VALUE__) == FL_CMU_ADC_CLK_SOURCE_PLL)||\
                                                            ((__VALUE__) == FL_ADC_CLK_SOURCE_APBCLK))

#define         IS_FL_ADC_CMUCLK_PRESCALER(__VALUE__)       (((__VALUE__) == FL_ADC_CLK_PSC_DIV1)||\
                                                            ((__VALUE__) == FL_ADC_CLK_PSC_DIV2)||\
                                                            ((__VALUE__) == FL_ADC_CLK_PSC_DIV4)||\
                                                            ((__VALUE__) == FL_ADC_CLK_PSC_DIV8)||\
                                                            ((__VALUE__) == FL_ADC_CLK_PSC_DIV16)||\
                                                            ((__VALUE__) == FL_ADC_CLK_PSC_DIV32))

#define         IS_FL_ADC_APBCLK_PRESCALER(__VALUE__)       (((__VALUE__) == FL_ADC_CLK_PSC_DIV1)||\
                                                            ((__VALUE__) == FL_ADC_CLK_PSC_DIV2)||\
                                                            ((__VALUE__) == FL_ADC_CLK_PSC_DIV4)||\
                                                            ((__VALUE__) == FL_ADC_CLK_PSC_DIV8))

#define         IS_FL_ADC_REFERENCE_SOURCE(__VALUE__)       (((__VALUE__) == FL_ADC_REF_SOURCE_VDDA)||\
                                                            ((__VALUE__) == FL_ADC_REF_SOURCE_VREFP))

#define         IS_FL_ADC_BITWIDTH(__VALUE__)               (((__VALUE__) == FL_ADC_BIT_WIDTH_12B)||\
                                                            ((__VALUE__) == FL_ADC_BIT_WIDTH_10B)||\
                                                            ((__VALUE__) == FL_ADC_BIT_WIDTH_8B)||\
                                                            ((__VALUE__) == FL_ADC_BIT_WIDTH_6B))

#define         IS_FL_ADC_CONTINUOUSCONVMODE(__VALUE__)     (((__VALUE__) == FL_ADC_CONV_MODE_SINGLE)||\
                                                            ((__VALUE__) == FL_ADC_CONV_MODE_CONTINUOUS))

#define         IS_FL_ADC_AUTO_MODE(__VALUE__)              (((__VALUE__) == FL_ADC_SINGLE_CONV_MODE_AUTO)||\
                                                            ((__VALUE__) == FL_ADC_SINGLE_CONV_MODE_SEMIAUTO))


#define         IS_FL_ADC_SCANDIRECTION(__VALUE__)          (((__VALUE__) == FL_ADC_SEQ_SCAN_DIR_FORWARD)||\
                                                            ((__VALUE__) == FL_ADC_SEQ_SCAN_DIR_BACKWARD))


#define         IS_FL_ADC_EXTERNALTRIGCONV(__VALUE__)       (((__VALUE__) == FL_ADC_TRIGGER_EDGE_NONE)||\
                                                            ((__VALUE__) == FL_ADC_TRIGGER_EDGE_RISING)||\
                                                            ((__VALUE__) == FL_ADC_TRIGGER_EDGE_FALLING)||\
                                                            ((__VALUE__) == FL_ADC_TRIGGER_EDGE_BOTH))

#define         IS_FL_ADC_EXTERNALTRIGSOURCE(__VALUE__)     (((__VALUE__) == FL_ADC_TRGI_LUT0)||\
                                                            ((__VALUE__) == FL_ADC_TRGI_LUT1)||\
                                                            ((__VALUE__) == FL_ADC_TRGI_LUT2)||\
                                                            ((__VALUE__) == FL_ADC_TRGI_ATIM)||\
                                                            ((__VALUE__) == FL_ADC_TRGI_GPTIM1)||\
                                                            ((__VALUE__) == FL_ADC_TRGI_GPTIM2)||\
                                                            ((__VALUE__) == FL_ADC_TRGI_BSTIM16)||\
                                                            ((__VALUE__) == FL_ADC_TRGI_LPTIM12)||\
                                                            ((__VALUE__) == FL_ADC_TRGI_COMP1)||\
                                                            ((__VALUE__) == FL_ADC_TRGI_COMP2)||\
                                                            ((__VALUE__) == FL_ADC_TRGI_RTCA)||\
                                                            ((__VALUE__) == FL_ADC_TRGI_LUT3)||\
                                                            ((__VALUE__) == FL_ADC_TRGI_GPTIM0)||\
                                                            ((__VALUE__) == FL_ADC_TRGI_COMP3))

#define         IS_FL_ADC_CHANNEL_FAST_TIME(__VALUE__)      (((__VALUE__) == FL_ADC_FAST_CH_SAMPLING_TIME_2_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_FAST_CH_SAMPLING_TIME_4_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_FAST_CH_SAMPLING_TIME_8_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_FAST_CH_SAMPLING_TIME_16_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_FAST_CH_SAMPLING_TIME_32_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_FAST_CH_SAMPLING_TIME_64_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_FAST_CH_SAMPLING_TIME_80_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_FAST_CH_SAMPLING_TIME_96_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_FAST_CH_SAMPLING_TIME_128_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_FAST_CH_SAMPLING_TIME_160_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_FAST_CH_SAMPLING_TIME_192_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_FAST_CH_SAMPLING_TIME_256_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_FAST_CH_SAMPLING_TIME_320_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_FAST_CH_SAMPLING_TIME_384_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_FAST_CH_SAMPLING_TIME_512_ADCCLK))

#define         IS_FL_ADC_CHANNEL_SLOW_TIME(__VALUE__)      (((__VALUE__) == FL_ADC_SLOW_CH_SAMPLING_TIME_2_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_SLOW_CH_SAMPLING_TIME_4_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_SLOW_CH_SAMPLING_TIME_8_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_SLOW_CH_SAMPLING_TIME_16_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_SLOW_CH_SAMPLING_TIME_32_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_SLOW_CH_SAMPLING_TIME_64_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_SLOW_CH_SAMPLING_TIME_80_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_SLOW_CH_SAMPLING_TIME_96_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_SLOW_CH_SAMPLING_TIME_128_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_SLOW_CH_SAMPLING_TIME_160_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_SLOW_CH_SAMPLING_TIME_192_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_SLOW_CH_SAMPLING_TIME_256_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_SLOW_CH_SAMPLING_TIME_320_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_SLOW_CH_SAMPLING_TIME_384_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_SLOW_CH_SAMPLING_TIME_512_ADCCLK))

#define         IS_FL_ADC_OVERSAMPCOFIG(__VALUE__)          (((__VALUE__) == FL_DISABLE)||\
                                                            ((__VALUE__) == FL_ENABLE))

#define         IS_FL_ADC_OVERSAMPINGRATIO(__VALUE__)       (((__VALUE__) == FL_ADC_OVERSAMPLING_MUL_2X)||\
                                                            ((__VALUE__) == FL_ADC_OVERSAMPLING_MUL_4X)||\
                                                            ((__VALUE__) == FL_ADC_OVERSAMPLING_MUL_8X)||\
                                                            ((__VALUE__) == FL_ADC_OVERSAMPLING_MUL_16X)||\
                                                            ((__VALUE__) == FL_ADC_OVERSAMPLING_MUL_32X)||\
                                                            ((__VALUE__) == FL_ADC_OVERSAMPLING_MUL_64X)||\
                                                            ((__VALUE__) == FL_ADC_OVERSAMPLING_MUL_128X)||\
                                                            ((__VALUE__) == FL_ADC_OVERSAMPLING_MUL_256X))

#define         IS_FL_ADC_OVERSAMPINGSHIFT(__VALUE__)       (((__VALUE__) == FL_ADC_OVERSAMPLING_SHIFT_0B)||\
                                                            ((__VALUE__) == FL_ADC_OVERSAMPLING_SHIFT_1B)||\
                                                            ((__VALUE__) == FL_ADC_OVERSAMPLING_SHIFT_2B)||\
                                                            ((__VALUE__) == FL_ADC_OVERSAMPLING_SHIFT_3B)||\
                                                            ((__VALUE__) == FL_ADC_OVERSAMPLING_SHIFT_4B)||\
                                                            ((__VALUE__) == FL_ADC_OVERSAMPLING_SHIFT_5B)||\
                                                            ((__VALUE__) == FL_ADC_OVERSAMPLING_SHIFT_6B)||\
                                                            ((__VALUE__) == FL_ADC_OVERSAMPLING_SHIFT_7B)||\
                                                            ((__VALUE__) == FL_ADC_OVERSAMPLING_SHIFT_8B))

#define         ADC_CALIBRATIN_TIME_OUT                     (500000)

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup ADC_FL_EF_Init
  * @{
  */

/**
  * @brief  ADC外设寄存器值为复位值
  * @param  外设入口地址
  * @retval 返回错误状态，可能值：
  *         -FL_PASS 外设寄存器值恢复复位值
  *         -FL_FAIL 未成功执行
  */
FL_ErrorStatus FL_ADC_CommonDeInit(void)
{
    /* 关闭总线时钟 */
    FL_CMU_DisableGroup2BusClock(FL_CMU_GROUP2_BUSCLK_ADC);
    /* 关闭操作时钟 */
    FL_CMU_DisableGroup3OperationClock(FL_CMU_GROUP3_OPCLK_ADC);
    return FL_PASS;
}
/**
  * @brief  ADC共用寄存器设置以配置外设工作时钟
  *
  * @note   其中FL_LPTIM_OPERATION_MODE_EXTERNAL_ASYN_PAUSE_CNT 模式需要外部脉冲提供给LPTIM模块作为工作时钟，此时
  *         LPTIM完全工作在异步模式下。
  * @param  LPTIM  外设入口地址
  * @param  LPTIM_InitStruct指向FL_LPTIM_TimeInitTypeDef类的结构体，它包含指定LPTIM外设的配置信息
  *
  * @retval ErrorStatus枚举值
  *         -FL_FAIL 配置过程发生错误
  *         -FL_PASS ADC配置成功
  */
FL_ErrorStatus FL_ADC_CommonInit(FL_ADC_CommonInitTypeDef *ADC_CommonInitStruct)
{
    FL_ErrorStatus status = FL_PASS;
    /* 入口参数检查 */
    assert_param(IS_FL_ADC_CLK_SOURCE(ADC_CommonInitStruct->clockSource));
    assert_param(IS_FL_ADC_REFERENCE_SOURCE(ADC_CommonInitStruct->referenceSource));
    assert_param(IS_FL_ADC_BITWIDTH(ADC_CommonInitStruct->bitWidth));
    if(ADC_CommonInitStruct->clockSource == FL_ADC_CLK_SOURCE_APBCLK)
    {
        assert_param(IS_FL_ADC_APBCLK_PRESCALER(ADC_CommonInitStruct->clockPrescaler));
    }
    else
    {
        assert_param(IS_FL_ADC_CMUCLK_PRESCALER(ADC_CommonInitStruct->clockPrescaler));
    }

    /* 开启总线时钟 */
    FL_CMU_EnableGroup2BusClock(FL_CMU_GROUP2_BUSCLK_ADC);
    /* 配置ADC时钟 */
    if(ADC_CommonInitStruct->clockSource == FL_ADC_CLK_SOURCE_APBCLK)
    {
        /* 设置ADC时钟来源于APBCLK */
        FL_ADC_SetClockSource(ADC, FL_ADC_CLK_SOURCE_APBCLK);

        /* 配置APBCLOCK时钟预分频 */
        FL_ADC_SetAPBPrescaler(ADC, ADC_CommonInitStruct->clockPrescaler << ADC_CFGR1_APBCLK_PSC_Pos);
    }
    else
    {
        /* 设置ADC时钟来源于ADCCLK */
        FL_ADC_SetClockSource(ADC, FL_ADC_CLK_SOURCE_ADCCLK);

        /* 设置ADCCLK时钟源 */
        FL_CMU_SetADCClockSource(ADC_CommonInitStruct->clockSource);

        /* 配置ADCCLK时钟预分频 */
        FL_CMU_SetADCPrescaler(ADC_CommonInitStruct->clockPrescaler << CMU_OPCCR2_ADCPRSC_Pos);

        /* 开启操作时钟 */
        FL_CMU_EnableGroup3OperationClock(FL_CMU_GROUP3_OPCLK_ADC);
    }
    /* 配置ADC基准电压*/
    FL_ADC_SetReferenceSource(ADC, ADC_CommonInitStruct->referenceSource);
    /* 配置ADC输出位数*/
    FL_ADC_SetBitWidth(ADC, ADC_CommonInitStruct->bitWidth);
    return status;
}
/**
  * @brief  设置 ADC_CommonInitStruct 为默认配置
  * @param  ADC_CommonInitStruct 指向需要将值设置为默认配置的结构体 @ref FL_ADC_CommonInitTypeDef 结构体
  *
  * @retval None
  */
void FL_ADC_CommonStructInit(FL_ADC_CommonInitTypeDef *ADC_CommonInitStruct)
{
    /* 默认使用RCHF作为ADC时钟模块时钟源，预分频系数16 */
    ADC_CommonInitStruct->clockSource           = FL_CMU_ADC_CLK_SOURCE_RCHF;
    ADC_CommonInitStruct->clockPrescaler        = FL_CMU_ADC_PSC_DIV16;
    ADC_CommonInitStruct->referenceSource       = FL_ADC_REF_SOURCE_VDDA;
    ADC_CommonInitStruct->bitWidth              = FL_ADC_BIT_WIDTH_12B;
}
/**
  * @brief  恢复对应的ADC入口地址寄存器为默认值
  *
  * @param  ADCx  外设入口地址
  *
  * @retval ErrorStatus枚举值
  *         -FL_FAIL 配置过程发生错误
  *         -FL_PASS ADC配置成功
  */
FL_ErrorStatus  FL_ADC_DeInit(ADC_Type *ADCx)
{
    FL_ErrorStatus status = FL_PASS;
    /* 入口合法性检查 */
    assert_param(IS_FL_ADC_INSTANCE(ADCx));
    /* 外设复位使能 */
    FL_RMU_EnablePeripheralReset(RMU);
    FL_RMU_EnableResetAPBPeripheral(RMU, FL_RMU_RSTAPB_ADC);
    FL_RMU_DisableResetAPBPeripheral(RMU, FL_RMU_RSTAPB_ADC);
    FL_RMU_EnableResetAPBPeripheral(RMU, FL_RMU_RSTAPB_ADCCR);
    FL_RMU_DisableResetAPBPeripheral(RMU, FL_RMU_RSTAPB_ADCCR);
    FL_RMU_DisablePeripheralReset(RMU);
    return status;
}
/**
  * @brief  初始化ADCx指定的入口地址的外设寄存器
  *
  * @note   用户必须检查此函数的返回值，以确保自校准完成，否则转换结果精度无法保证，除此之外ADC使能过采样实际不会增加ADC的
  *         转换精度只会提高转换结果的稳定性（同时配置移位寄存器的情况下），同时过采样会降低转换速度。
  * @param  ADCx  外设入口地址
  * @param  ADC_InitStruct 指向一 @ref FL_ADC_InitTypeDef 结构体，它包含指定ADC外设的配置信息
  *
  * @retval ErrorStatus枚举值
  *         -FL_FAIL 配置过程发生错误
  *         -FL_PASS ADC配置成功
  */
FL_ErrorStatus FL_ADC_Init(ADC_Type *ADCx, FL_ADC_InitTypeDef  *ADC_InitStruct)
{
    FL_ErrorStatus status = FL_PASS;
    uint32_t i = 0, Calibration_Flag;
    /* 入口合法性检查 */
    assert_param(IS_FL_ADC_INSTANCE(ADCx));
    assert_param(IS_FL_ADC_CONTINUOUSCONVMODE(ADC_InitStruct->conversionMode));
    assert_param(IS_FL_ADC_AUTO_MODE(ADC_InitStruct->autoMode));
    assert_param(IS_FL_ADC_SCANDIRECTION(ADC_InitStruct->scanDirection));
    assert_param(IS_FL_ADC_EXTERNALTRIGCONV(ADC_InitStruct->externalTrigConv));
    assert_param(IS_FL_ADC_OVERSAMPCOFIG(ADC_InitStruct->oversamplingMode));
    assert_param(IS_FL_ADC_OVERSAMPINGRATIO(ADC_InitStruct->overSampingMultiplier));
    assert_param(IS_FL_ADC_OVERSAMPINGSHIFT(ADC_InitStruct->oversamplingShift));
    FL_CMU_EnableGroup1BusClock(FL_CMU_GROUP1_BUSCLK_VREF1P2);
    if(!FL_VREF_IsEnabled(VREF))
    {
        FL_VREF_ClearFlag_Ready(VREF);
        FL_VREF_Enable(VREF);//置位VREF_EN寄存器，使能VREF1p2模块
    }
    FL_VREF_EnableTemperatureSensor(VREF);//置位PTAT_EN寄存器
    while(FL_VREF_IsActiveFlag_Ready(VREF) == 0)    /* 等待VREF建立 */
    {
        if(i >= 128000)
        {
            break;
        }
        i++;
    }
    FL_ADC_Disable(ADCx);
    FL_ADC_DisableOverSampling(ADCx);
    FL_ADC_Enable(ADCx);
    FL_ADC_EnableCalibration(ADC);

    i = 0;
    do
    {
        Calibration_Flag = FL_ADC_IsActiveFlag_EndOfCalibration(ADC);
        i++;
    } while((i != 0xFFFFFFFFU) && (Calibration_Flag == 0U));           //等待转换完成

    if(Calibration_Flag == 0x01)
    {
        FL_ADC_ClearFlag_EndOfCalibration(ADC);
        /* 关闭ADC，关闭后ADC自校准值依然保持 */
        FL_ADC_Disable(ADCx);
        if(FL_ADC_IsEnabled(ADCx) == 0U)
        {
            /* 连续转换模式 */
            FL_ADC_SetConversionMode(ADCx, ADC_InitStruct->conversionMode);
            /* 自动转换模式 */
            FL_ADC_SetSingleConversionAutoMode(ADCx, ADC_InitStruct->autoMode);
            /* 通道等待使能 */
            if(ADC_InitStruct->waitMode)
            {
                FL_ADC_EnableWaitMode(ADCx);
            }
            else
            {
                FL_ADC_DisableWaitMode(ADCx);
            }
            /*数据冲突模式设置*/
            if(ADC_InitStruct->overrunMode)
            {
                FL_ADC_EnableOverrunMode(ADCx);
            }
            else
            {
                FL_ADC_DisableOverrunMode(ADCx);
            }
            /* 多通道扫描方向 */
            FL_ADC_SetSequenceScanDirection(ADCx, ADC_InitStruct->scanDirection);
            /* 外部引脚触发 */
            FL_ADC_DisableExternalConversion(ADCx);
            /* 触发模式 */
            FL_ADC_SetTriggerEdge(ADCx, ADC_InitStruct->externalTrigConv);
            /* 触发源 */
            FL_ADC_SetTriggerSource(ADCx, ADC_InitStruct->triggerSource);
            /*通道采样时间设置*/
            FL_ADC_SetFastChannelSamplingTime(ADCx, ADC_InitStruct->fastChannelTime);
            FL_ADC_SetSlowChannelSamplingTime(ADCx, ADC_InitStruct->lowChannelTime);
            if(ADC_InitStruct->oversamplingMode)
            {
                /*使能过采样倍数后，需要配置移位寄存器进行移位，这一过程是硬件自动完成的最终最大
                可输出16位的结果值（即256被采样得到的结果是20bit的，右移4bit结果就是16bit的）*/
                FL_ADC_SetOverSamplingMultiplier(ADCx, ADC_InitStruct->overSampingMultiplier);
                FL_ADC_SetOverSamplingShift(ADCx, ADC_InitStruct->oversamplingShift);
                /* 过采样使能 */
                FL_ADC_EnableOverSampling(ADCx);
            }
            else
            {
                /* 关闭过采样 */
                FL_ADC_DisableOverSampling(ADCx);
            }
        }
        else
        {
            status = FL_FAIL;
        }
    }
    else
    {
        status = FL_FAIL;
    }
    return status;
}

/**
  * @brief  设置 ADC_InitStruct 为默认配置
  * @param  ADC_InitStruct 指向需要将值设置为默认配置的结构体 @ref FL_ADC_InitTypeDef 结构体
  *
  * @retval None
  */
void FL_ADC_StructInit(FL_ADC_InitTypeDef *ADC_InitStruct)
{
    ADC_InitStruct->conversionMode                  = FL_ADC_CONV_MODE_SINGLE;
    ADC_InitStruct->autoMode                    = FL_ADC_SINGLE_CONV_MODE_AUTO;
    ADC_InitStruct->scanDirection               = FL_ADC_SEQ_SCAN_DIR_FORWARD;
    ADC_InitStruct->externalTrigConv            = FL_ADC_TRIGGER_EDGE_NONE;
    ADC_InitStruct->overrunMode                 = FL_ENABLE;
    ADC_InitStruct->waitMode                    = FL_ENABLE;
    ADC_InitStruct->fastChannelTime             = FL_ADC_FAST_CH_SAMPLING_TIME_2_ADCCLK;
    ADC_InitStruct->lowChannelTime                  = FL_ADC_SLOW_CH_SAMPLING_TIME_512_ADCCLK;
    ADC_InitStruct->oversamplingMode            = FL_ENABLE;
    ADC_InitStruct->overSampingMultiplier   = FL_ADC_OVERSAMPLING_MUL_16X;
    ADC_InitStruct->oversamplingShift           = FL_ADC_OVERSAMPLING_SHIFT_4B;
}

/**
  * @}
  */

#endif /* FL_ADC_DRIVER_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/


