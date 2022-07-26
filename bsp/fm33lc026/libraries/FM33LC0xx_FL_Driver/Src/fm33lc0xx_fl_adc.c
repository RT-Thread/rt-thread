/**
  ****************************************************************************************************
  * @file    fm33lc0xx_fl_adc.c
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
#include "fm33lc0xx_fl.h"

/** @addtogroup FM33LC0XX_FL_Driver
  * @{
  */

/** @addtogroup ADC
  * @{
  */

#ifdef FL_ADC_DRIVER_ENABLED

/* Private macros ------------------------------------------------------------*/
/** @addtogroup ADC_FL_PM ADC Private Macros
  * @{
  */

#define         IS_FL_ADC_INSTANCE(INSTANCE)                ((INSTANCE) == ADC)

#define         IS_FL_ADC_ADCCLK_SOURCE(__VALUE__)          (((__VALUE__) == FL_RCC_ADC_CLK_SOURCE_RCMF_PSC)||\
                                                            ((__VALUE__) == FL_RCC_ADC_CLK_SOURCE_RCHF)||\
                                                            ((__VALUE__) == FL_RCC_ADC_CLK_SOURCE_XTHF)||\
                                                            ((__VALUE__) == FL_RCC_ADC_CLK_SOURCE_PLL))


#define         IS_FL_ADC_ADCCLK_PRESCALER(__VALUE__)       (((__VALUE__) == FL_RCC_ADC_PSC_DIV1)||\
                                                            ((__VALUE__) == FL_RCC_ADC_PSC_DIV2)||\
                                                            ((__VALUE__) == FL_RCC_ADC_PSC_DIV4)||\
                                                            ((__VALUE__) == FL_RCC_ADC_PSC_DIV8)||\
                                                            ((__VALUE__) == FL_RCC_ADC_PSC_DIV16)||\
                                                            ((__VALUE__) == FL_RCC_ADC_PSC_DIV32))


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

#define         IS_FL_ADC_EXTERNALTRIGSOURCE(__VALUE__)     (((__VALUE__) == FL_ADC_TRGI_PA8)||\
                                                            ((__VALUE__) == FL_ADC_TRGI_PB9)||\
                                                            ((__VALUE__) == FL_ADC_TRGI_ATIM)||\
                                                            ((__VALUE__) == FL_ADC_TRGI_GPTIM0)||\
                                                            ((__VALUE__) == FL_ADC_TRGI_GPTIM1)||\
                                                            ((__VALUE__) == FL_ADC_TRGI_RTC)||\
                                                            ((__VALUE__) == FL_ADC_TRGI_BSTIM1)||\
                                                            ((__VALUE__) == FL_ADC_TRGI_COMP1)||\
                                                            ((__VALUE__) == FL_ADC_TRGI_COMP2))

#define         IS_FL_ADC_CHANNEL_FAST_TIME(__VALUE__)      (((__VALUE__) == FL_ADC_FAST_CH_SAMPLING_TIME_4_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_FAST_CH_SAMPLING_TIME_6_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_FAST_CH_SAMPLING_TIME_9_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_FAST_CH_SAMPLING_TIME_10_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_FAST_CH_SAMPLING_TIME_16_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_FAST_CH_SAMPLING_TIME_24_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_FAST_CH_SAMPLING_TIME_32_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_FAST_CH_SAMPLING_TIME_48_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_FAST_CH_SAMPLING_TIME_96_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_FAST_CH_SAMPLING_TIME_128_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_FAST_CH_SAMPLING_TIME_192_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_FAST_CH_SAMPLING_TIME_256_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_FAST_CH_SAMPLING_TIME_384_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_FAST_CH_SAMPLING_TIME_SOFTWARE_CONTROL))

#define         IS_FL_ADC_CHANNEL_SLOW_TIME(__VALUE__)      (((__VALUE__) == FL_ADC_SLOW_CH_SAMPLING_TIME_4_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_SLOW_CH_SAMPLING_TIME_6_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_SLOW_CH_SAMPLING_TIME_9_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_SLOW_CH_SAMPLING_TIME_10_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_SLOW_CH_SAMPLING_TIME_16_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_SLOW_CH_SAMPLING_TIME_24_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_SLOW_CH_SAMPLING_TIME_32_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_SLOW_CH_SAMPLING_TIME_48_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_SLOW_CH_SAMPLING_TIME_96_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_SLOW_CH_SAMPLING_TIME_128_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_SLOW_CH_SAMPLING_TIME_192_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_SLOW_CH_SAMPLING_TIME_256_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_SLOW_CH_SAMPLING_TIME_384_ADCCLK)||\
                                                            ((__VALUE__) == FL_ADC_SLOW_CH_SAMPLING_TIME_SOFTWARE_CONTROL))

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

/** @addtogroup ADC_FL_EF_Init
  * @{
  */

/**
  * @brief  恢复ADC公用寄存器到复位值
  * @param  None
  * @retval 执行结果
  *         -FL_PASS ADC公用寄存器值恢复复位值
  *         -FL_FAIL 未成功执行
  */
FL_ErrorStatus FL_ADC_CommonDeInit(void)
{
    /* 关闭总线时钟 */
    FL_RCC_DisableGroup2BusClock(FL_RCC_GROUP2_BUSCLK_ADC);
    /* 关闭操作时钟 */
    FL_RCC_DisableGroup2OperationClock(FL_RCC_GROUP2_OPCLK_ADC);
    return FL_PASS;
}
/**
  * @brief  配置ADC公用寄存器
  * @param  ADC_CommonInitStruct 指向 @ref FL_ADC_CommonInitTypeDef 的结构体，它包含ADC公用寄存器的配置信息
  * @retval 执行结果
  *         -FL_FAIL 配置过程发生错误
  *         -FL_PASS ADC公用寄存器配置成功
  */
FL_ErrorStatus FL_ADC_CommonInit(FL_ADC_CommonInitTypeDef *ADC_CommonInitStruct)
{
    FL_ErrorStatus status = FL_PASS;
    /* 入口参数检查 */
    assert_param(IS_FL_ADC_ADCCLK_PRESCALER(ADC_CommonInitStruct->clockPrescaler));
    assert_param(IS_FL_ADC_ADCCLK_SOURCE(ADC_CommonInitStruct->clockSource));
    /* 开启总线时钟 */
    FL_RCC_EnableGroup2BusClock(FL_RCC_GROUP2_BUSCLK_ADC);
    /* 开启操作时钟 */
    FL_RCC_EnableGroup2OperationClock(FL_RCC_GROUP2_OPCLK_ADC);
    /* 配置ADCCLOCK时钟预分频 */
    FL_RCC_SetADCPrescaler(ADC_CommonInitStruct->clockPrescaler);
    /* 配置ADCCLOCK时钟模块时钟源 */
    FL_RCC_SetADCClockSource(ADC_CommonInitStruct->clockSource);
    return status;
}
/**
  * @brief  初始化 @ref FL_ADC_CommonInitTypeDef 配置结构体
  * @param  ADC_CommonInitStruct 指向需要初始化的 @ref FL_ADC_CommonInitTypeDef 结构体
  * @retval None
  */
void FL_ADC_CommonStructInit(FL_ADC_CommonInitTypeDef *ADC_CommonInitStruct)
{
    /*默认使用RCHF作为ADC时钟模块时钟源，预分频系数16*/
    ADC_CommonInitStruct->clockSource     = FL_RCC_ADC_CLK_SOURCE_RCHF;
    ADC_CommonInitStruct->clockPrescaler  = FL_RCC_ADC_PSC_DIV16;
}
/**
  * @brief  恢复ADC外设寄存器到复位值
  * @param  ADCx  外设入口地址
  * @retval 执行结果
  *         -FL_PASS ADC外设寄存器值恢复复位值
  *         -FL_FAIL 未成功执行
  */
FL_ErrorStatus FL_ADC_DeInit(ADC_Type *ADCx)
{
    FL_ErrorStatus status = FL_PASS;
    /* 入口合法性检查 */
    assert_param(IS_FL_ADC_INSTANCE(ADCx));
    /* 外设复位使能 */
    FL_RCC_EnablePeripheralReset();
    FL_RCC_EnableResetAPB2Peripheral(FL_RCC_RSTAPB_ADC);
    FL_RCC_DisableResetAPB2Peripheral(FL_RCC_RSTAPB_ADC);
    FL_RCC_EnableResetAPB2Peripheral(FL_RCC_RSTAPB_ADCCR);
    FL_RCC_DisableResetAPB2Peripheral(FL_RCC_RSTAPB_ADCCR);
    FL_RCC_DisablePeripheralReset();
    return status;
}
/**
  * @brief  配置指定的ADC外设
  * @note   用户必须检查此函数的返回值，以确保自校准完成，否则转换结果精度无法保证，除此之外ADC使能过采样实际不会增加ADC的
  *         转换精度只会提高转换结果的稳定性（同时配置移位寄存器的情况下），同时过采样会降低转换速度。
  * @param  ADCx  外设入口地址
  * @param  ADC_InitStruct 指向 @ref FL_ADC_InitTypeDef 的结构体，它包含ADC外设寄存器的配置信息
  * @retval 执行结果
  *         -FL_FAIL 配置过程发生错误
  *         -FL_PASS ADC外设寄存器配置成功
  */
FL_ErrorStatus FL_ADC_Init(ADC_Type *ADCx, FL_ADC_InitTypeDef  *ADC_InitStruct)
{
    FL_ErrorStatus status = FL_PASS;
    uint32_t i = 0;
    /* 入口合法性检查 */
    assert_param(IS_FL_ADC_INSTANCE(ADCx));
    assert_param(IS_FL_ADC_CONTINUOUSCONVMODE(ADC_InitStruct->conversionMode));
    assert_param(IS_FL_ADC_AUTO_MODE(ADC_InitStruct->autoMode));
    assert_param(IS_FL_ADC_SCANDIRECTION(ADC_InitStruct->scanDirection));
    assert_param(IS_FL_ADC_EXTERNALTRIGCONV(ADC_InitStruct->externalTrigConv));
    assert_param(IS_FL_ADC_OVERSAMPCOFIG(ADC_InitStruct->oversamplingMode));
    assert_param(IS_FL_ADC_OVERSAMPINGRATIO(ADC_InitStruct->overSampingMultiplier));
    assert_param(IS_FL_ADC_OVERSAMPINGSHIFT(ADC_InitStruct->oversamplingShift));
    /* 使能ADC工作时钟 */
    FL_RCC_EnableGroup1BusClock(FL_RCC_GROUP1_BUSCLK_ANAC);
    FL_SVD_EnableADCMonitor(SVD);
    if(!FL_VREF_IsEnabled(VREF))
    {
        FL_VREF_ClearFlag_Ready(VREF);
        FL_VREF_Enable(VREF);   /* 置位VREF_EN寄存器，使能VREF1p2模块 */
    }
    FL_VREF_EnableTemperatureSensor(VREF);  /* 置位PTAT_EN寄存器 */
    while(FL_VREF_IsActiveFlag_Ready(VREF) == 0)
    {
        if(i >= 128000)
        {
            break;
        }
        i++;
    }
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
        /* 采样控制模式*/
        FL_ADC_SetSamplingTimeControlMode(ADCx, FL_ADC_SAMPLING_TIME_CONTROL_BY_REG);
        FL_ADC_SetSamplingStartControlMode(ADCx, FL_ADC_SAMPLING_START_CONTROL_BY_REG);
        /* 触发模式 */
        FL_ADC_SetTriggerEdge(ADCx, ADC_InitStruct->externalTrigConv);
        /* 触发源 */
        FL_ADC_SetTriggerSource(ADCx, ADC_InitStruct->triggerSource);
        /*通道采样时间设置*/
        FL_ADC_SetSamplingInterval(ADCx, FL_ADC_SAMPLING_INTERVAL_11_CYCLE);
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
    return status;
}
/**
  * @brief  初始化 @ref FL_ADC_InitTypeDef 配置结构体
  * @param  ADC_InitStruct 指向需要初始化的 @ref FL_ADC_InitTypeDef 结构体
  * @retval None
  */
void FL_ADC_StructInit(FL_ADC_InitTypeDef *ADC_InitStruct)
{
    ADC_InitStruct->conversionMode        = FL_ADC_CONV_MODE_SINGLE;
    ADC_InitStruct->autoMode              = FL_ADC_SINGLE_CONV_MODE_AUTO;
    ADC_InitStruct->scanDirection         = FL_ADC_SEQ_SCAN_DIR_FORWARD;
    ADC_InitStruct->externalTrigConv      = FL_ADC_TRIGGER_EDGE_NONE;
    ADC_InitStruct->overrunMode           = FL_ENABLE;
    ADC_InitStruct->waitMode              = FL_ENABLE;
    ADC_InitStruct->fastChannelTime       = FL_ADC_FAST_CH_SAMPLING_TIME_4_ADCCLK;
    ADC_InitStruct->lowChannelTime        = FL_ADC_SLOW_CH_SAMPLING_TIME_192_ADCCLK;
    ADC_InitStruct->oversamplingMode      = FL_ENABLE;
    ADC_InitStruct->overSampingMultiplier = FL_ADC_OVERSAMPLING_MUL_16X;
    ADC_InitStruct->oversamplingShift     = FL_ADC_OVERSAMPLING_SHIFT_4B;
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
