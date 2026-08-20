/**
  ****************************************************************************************************
  * @file    fm33lg0xx_fl_lptim16.c
  * @author  FMSH Application Team
  * @brief   Src file of LPTIM16 FL Module
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

/** @addtogroup FM33LG0XX_FL_Driver
  * @{
  */

/** @addtogroup LPTIM16
  * @{
  */

#ifdef FL_LPTIM16_DRIVER_ENABLED

/* Private macros ------------------------------------------------------------*/
/** @addtogroup LPTIM16_FL_Private_Macros
  * @{
  */

#define         IS_LPTIM16_INSTANCE(INSTANCE)                           (((INSTANCE) == LPTIM16))

#define         IS_FL_LPTIM16_CHANNEL(__VALUE__)                        (((__VALUE__) == FL_LPTIM16_CHANNEL_1)||\
                                                                         ((__VALUE__) == FL_LPTIM16_CHANNEL_2))

#define         IS_FL_LPTIM16_CMU_CLK_SOURCE(__VALUE__)                 (((__VALUE__) == FL_CMU_LPTIM16_CLK_SOURCE_RCLF)||\
                                                                         ((__VALUE__) == FL_CMU_LPTIM16_CLK_SOURCE_RCLP)||\
                                                                         ((__VALUE__) == FL_CMU_LPTIM16_CLK_SOURCE_LSCLK)||\
                                                                         ((__VALUE__) == FL_CMU_LPTIM16_CLK_SOURCE_APBCLK))

#define         IS_FL_LPTIM16_CLK_SOURCE(__VALUE__)                     (((__VALUE__) == FL_LPTIM16_CLK_SOURCE_INTERNAL)||\
                                                                         ((__VALUE__) == FL_LPTIM16_CLK_SOURCE_EXTERNAL))

#define         IS_FL_LPTIM16_PSC(__VALUE__)                            (((__VALUE__) == FL_LPTIM16_PSC_DIV1)||\
                                                                         ((__VALUE__) == FL_LPTIM16_PSC_DIV2)||\
                                                                         ((__VALUE__) == FL_LPTIM16_PSC_DIV4)||\
                                                                         ((__VALUE__) == FL_LPTIM16_PSC_DIV8)||\
                                                                         ((__VALUE__) == FL_LPTIM16_PSC_DIV16)||\
                                                                         ((__VALUE__) == FL_LPTIM16_PSC_DIV32)||\
                                                                         ((__VALUE__) == FL_LPTIM16_PSC_DIV64)||\
                                                                         ((__VALUE__) == FL_LPTIM16_PSC_DIV128))

#define         IS_FL_LPTIM16_OPERATION_MODE(__VALUE__)                 (((__VALUE__) == FL_LPTIM16_OPERATION_MODE_NORMAL)||\
                                                                         ((__VALUE__) == FL_LPTIM16_OPERATION_MODE_EXTERNAL_TRIGGER_CNT)||\
                                                                         ((__VALUE__) == FL_LPTIM16_OPERATION_MODE_EXTERNAL_ASYNC_PULSE_CNT)||\
                                                                         ((__VALUE__) == FL_LPTIM16_OPERATION_MODE_TIMEOUT))

#define         IS_FL_LPTIM16_ENCODER_MODE(__VALUE__)                   (((__VALUE__) == FL_LPTIM16_ENCODER_MODE_DISABLE)||\
                                                                         ((__VALUE__) == FL_LPTIM16_ENCODER_MODE_TI1FP1_TI2FP2_CNT)||\
                                                                         ((__VALUE__) == FL_LPTIM16_ENCODER_MODE_TI2FP2_TI1FP1_CNT)||\
                                                                         ((__VALUE__) == FL_LPTIM16_ENCODER_MODE_TI2FP2_CNT_TI1FP1_CNT))

#define         IS_FL_LPTIM16_ETR_TRIGGER_EDGE(__VALUE__)               (((__VALUE__) == FL_LPTIM16_ETR_TRIGGER_EDGE_RISING)||\
                                                                         ((__VALUE__) == FL_LPTIM16_ETR_TRIGGER_EDGE_FALLING)||\
                                                                         ((__VALUE__) == FL_LPTIM16_ETR_TRIGGER_EDGE_BOTH))

#define         IS_FL_LPTIM16_ETR_COUNT_EDGE(__VALUE__)                 (((__VALUE__) == FL_LPTIM16_ETR_COUNT_EDGE_RISING)||\
                                                                         ((__VALUE__) == FL_LPTIM16_ETR_COUNT_EDGE_FALLING))

#define         IS_FL_LPTIM16_ONE_PULSE_MODE(__VALUE__)                 (((__VALUE__) == FL_LPTIM16_ONE_PULSE_MODE_CONTINUOUS)||\
                                                                         ((__VALUE__) == FL_LPTIM16_ONE_PULSE_MODE_SINGLE))

#define         IS_FL_LPTIM16_IC_EDGE(__VALUE__)                        (((__VALUE__) == FL_LPTIM16_IC_EDGE_RISING)||\
                                                                         ((__VALUE__) == FL_LPTIM16_IC_EDGE_FALLING)||\
                                                                         ((__VALUE__) == FL_LPTIM16_IC_EDGE_BOTH))

#define         IS_FL_LPTIM16_IC_POLARITY(__VALUE__)                    (((__VALUE__) == FL_LPTIM16_IC_POLARITY_NORMAL)||\
                                                                         ((__VALUE__) == FL_LPTIM16_IC_POLARITY_INVERT))

#define         IS_FL_LPTIM16_OC_POLARITY(__VALUE__)                    (((__VALUE__) == FL_LPTIM16_OC_POLARITY_NORMAL)||\
                                                                         ((__VALUE__) == FL_LPTIM16_OC_POLARITY_INVERT))

#define         IS_FL_LPTIM16_IC1_CAPTURE_SOURCE(__VALUE__)             (((__VALUE__) == FL_LPTIM16_IC1_CAPTURE_SOURCE_GROUP0)||\
                                                                         ((__VALUE__) == FL_LPTIM16_IC1_CAPTURE_SOURCE_GROUP1)||\
                                                                         ((__VALUE__) == FL_LPTIM16_IC1_CAPTURE_SOURCE_GROUP2)||\
                                                                         ((__VALUE__) == FL_LPTIM16_IC1_CAPTURE_SOURCE_GROUP3))

#define         IS_FL_LPTIM16_TRGO_SOURCE(__VALUE__)                    (((__VALUE__) == FL_LPTIM16_TRGO_ENABLE)||\
                                                                         ((__VALUE__) == FL_LPTIM16_TRGO_UPDATE)||\
                                                                         ((__VALUE__) == FL_LPTIM16_TRGO_OC1_CMP_PULSE)||\
                                                                         ((__VALUE__) == FL_LPTIM16_TRGO_IC1_EVENT)||\
                                                                         ((__VALUE__) == FL_LPTIM16_TRGO_IC2_EVENT))

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup LPTIM16_FL_EF_Init
  * @{
  */

/**
  * @brief  复位LPTIM16 外设
  * @param  外设入口地址
  * @retval 返回错误状态，可能值：
  *         -FL_PASS 外设寄存器值恢复复位值
  *         -FL_FAIL 未成功执行
  */
FL_ErrorStatus FL_LPTIM16_DeInit(LPTIM16_Type *LPTIM16x)
{
    /* 参数检查 */
    assert_param(IS_LPTIM16_INSTANCE(LPTIM16x));
    /* 使能外设复位 */
    FL_RMU_EnablePeripheralReset(RMU);
    /* 复位外设寄存器 */
    FL_RMU_EnableResetAPBPeripheral(RMU, FL_RMU_RSTAPB_LPTIM16);
    FL_RMU_DisableResetAPBPeripheral(RMU, FL_RMU_RSTAPB_LPTIM16);
    /* 关闭外设总线时钟和工作时钟 */
    FL_CMU_DisableGroup1BusClock(FL_CMU_GROUP1_BUSCLK_LPTIM16);
    FL_CMU_DisableGroup3OperationClock(FL_CMU_GROUP3_OPCLK_LPTIM16);
    /* 锁定外设复位 */
    FL_RMU_DisablePeripheralReset(RMU);
    return FL_PASS;
}

/**
  * @brief  根据需要功能配置LPTIM16寄存器使之工作在定时器功能模式下
  *
  * @note   需要使用ETR作为计数源时，建议根据需求配置为异步脉冲计数模式
  *         @ref FL_LPTIM16_OPERATION_MODE_EXTERNAL_ASYNC_PULSE_CNT 或外部触发计数模式
  *         @ref FL_LPTIM16_OPERATION_MODE_EXTERNAL_TRIGGER_CNT
  *
  * @param  LPTIM16x  外设入口地址
  * @param  init 为 @ref FL_LPTIM16_InitTypeDef类型的结构体
  *
  * @retval ErrorStatus枚举值
  *         -FL_FAIL 配置过程发生错误
  *         -FL_PASS LPTIM16配置成功
  */
FL_ErrorStatus FL_LPTIM16_Init(LPTIM16_Type *LPTIM16x, FL_LPTIM16_InitTypeDef *init)
{
    /* 参数检查 */
    assert_param(IS_LPTIM16_INSTANCE(LPTIM16x));
    assert_param(IS_FL_LPTIM16_CMU_CLK_SOURCE(init->clockSource));
    assert_param(IS_FL_LPTIM16_CLK_SOURCE(init->prescalerClockSource));
    assert_param(IS_FL_LPTIM16_PSC(init->prescaler));
    assert_param(IS_FL_LPTIM16_OPERATION_MODE(init->mode));
    assert_param(IS_FL_LPTIM16_ENCODER_MODE(init->encoderMode));
    assert_param(IS_FL_LPTIM16_ONE_PULSE_MODE(init->onePulseMode));
    assert_param(IS_FL_LPTIM16_ETR_TRIGGER_EDGE(init->triggerEdge));
    assert_param(IS_FL_LPTIM16_ETR_COUNT_EDGE(init->countEdge));
    /* 时钟配置 */
    if(LPTIM16x == LPTIM16)
    {
        /* 使能总线时钟 */
        FL_CMU_EnableGroup1BusClock(FL_CMU_GROUP1_BUSCLK_LPTIM16);
        /* 除了异步计数模式，其他模式都需要使能工作时钟 */
        if(init->mode != FL_LPTIM16_OPERATION_MODE_EXTERNAL_ASYNC_PULSE_CNT)
        {
            /* 使能工作时钟 */
            FL_CMU_EnableGroup3OperationClock(FL_CMU_GROUP3_OPCLK_LPTIM16);
            /* 设置工作时钟时钟源 */
            FL_CMU_SetLPTIM16ClockSource(init->clockSource);
        }
    }
    else
    {
        return FL_FAIL;
    }
    /* 配置分频器的时钟源 */
    FL_LPTIM16_SetClockSource(LPTIM16x, init->prescalerClockSource);
    /* 配置时钟分频 */
    FL_LPTIM16_SetPrescaler(LPTIM16x, init->prescaler);
    /* 配置重装载值 */
    FL_LPTIM16_WriteAutoReload(LPTIM16x, init->autoReload);
    /* 配置定时器工作模式 */
    FL_LPTIM16_SetOperationMode(LPTIM16x, init->mode);
    /* 配置编码器模式 */
    if(init->mode == FL_LPTIM16_OPERATION_MODE_NORMAL)
    {
        FL_LPTIM16_SetEncoderMode(LPTIM16x, init->encoderMode);
    }
    /* 单次计数模式 */
    FL_LPTIM16_SetOnePulseMode(LPTIM16x, init->onePulseMode);
    /* 配置定时器不同模式下的特殊寄存器 */
    switch(init->mode)
    {
        case FL_LPTIM16_OPERATION_MODE_NORMAL:
        {
            /* ETR作为时钟时和异步脉冲计数模式信号路径一样，需要使能模拟滤波，并配置边沿 */
            if(init->prescalerClockSource == FL_LPTIM16_CLK_SOURCE_EXTERNAL)
            {
                /* 配置异步计数边沿 */
                FL_LPTIM16_SetETRCountEdge(LPTIM16x, init->countEdge);
                /* 开启外部输入滤波 */
                FL_LPTIM16_EnableETRFilter(LPTIM16x);
            }
        }
        break;
        case FL_LPTIM16_OPERATION_MODE_EXTERNAL_TRIGGER_CNT:
        {
            /* 配置外部输入有效边沿 */
            FL_LPTIM16_SetETRTriggerEdge(LPTIM16x, init->triggerEdge);
        }
        break;
        case FL_LPTIM16_OPERATION_MODE_EXTERNAL_ASYNC_PULSE_CNT:
        {
            /* 配置异步计数边沿 */
            FL_LPTIM16_SetETRCountEdge(LPTIM16x, init->countEdge);
            /* 开启外部输入滤波 */
            FL_LPTIM16_EnableETRFilter(LPTIM16x);
        }
        break;
        case FL_LPTIM16_OPERATION_MODE_TIMEOUT:
        {
            /* 配置外部输入有效边沿 */
            FL_LPTIM16_SetETRTriggerEdge(LPTIM16x, init->triggerEdge);
        }
        break;
        default:
            return FL_FAIL;
    }
    return FL_PASS;
}

/**
  * @brief  设置 LPTIM16_InitStruct 为默认配置
  * @param  init 为 @ref FL_LPTIM16_InitTypeDef类型的结构体
  *
  * @retval None
  */
void FL_LPTIM16_StructInit(FL_LPTIM16_InitTypeDef *init)
{
    init->clockSource           = FL_CMU_LPTIM16_CLK_SOURCE_APBCLK;
    init->prescalerClockSource  = FL_LPTIM16_CLK_SOURCE_INTERNAL;
    init->prescaler             = FL_LPTIM16_PSC_DIV1;
    init->autoReload            = 0;
    init->mode                  = FL_LPTIM16_OPERATION_MODE_NORMAL;
    init->countEdge             = FL_LPTIM16_ETR_COUNT_EDGE_RISING;
    init->triggerEdge           = FL_LPTIM16_ETR_TRIGGER_EDGE_RISING;
    init->encoderMode           = FL_LPTIM16_ENCODER_MODE_DISABLE;
    init->onePulseMode          = FL_LPTIM16_ONE_PULSE_MODE_CONTINUOUS;
}

/**
  * @brief  配置LPTIM16工作在输入捕获模式
  *
  * @param  LPTIM16x  外设入口地址
  * @param  ic_init 为 @ref FL_LPTIM16_IC_InitTypeDef类型的结构体
  * @param  Channel LPTIM16输入通道
  *
  * @retval ErrorStatus枚举值
  *         -FL_FAIL 配置过程发生错误
  *         -FL_PASS LPTIM16配置成功
  */
FL_ErrorStatus FL_LPTIM16_IC_Init(LPTIM16_Type *LPTIM16x, uint32_t Channel, FL_LPTIM16_IC_InitTypeDef *ic_init)
{
    /* 参数检查 */
    assert_param(IS_LPTIM16_INSTANCE(LPTIM16x));
    assert_param(IS_FL_LPTIM16_CHANNEL(Channel));
    assert_param(IS_FL_LPTIM16_IC_EDGE(ic_init->ICEdge));
    assert_param(IS_FL_LPTIM16_IC_POLARITY(ic_init->ICInputPolarity));
    assert_param(IS_FL_LPTIM16_IC1_CAPTURE_SOURCE(ic_init->channel1CaptureSource));
    /* 通道1捕获源 & 预分频 */
    if(Channel == FL_LPTIM16_CHANNEL_1)
    {
        FL_LPTIM16_IC_WriteChannel1Prescaler(LPTIM16x, ic_init->channel1Prescaler);
        FL_LPTIM16_IC_SetChannel1CaptureSource(LPTIM16x, ic_init->channel1CaptureSource);
    }
    if(ic_init->ICInputDigitalFilter == FL_DISABLE)
    {
        FL_LPTIM16_DisableDigitalFilter(LPTIM16, Channel);
    }
    else
    {
        FL_LPTIM16_EnableDigitalFilter(LPTIM16, Channel);
    }
    /* 捕获通道极性 */
    FL_LPTIM16_IC_SetInputPolarity(LPTIM16x, ic_init->ICInputPolarity, Channel);
    /* 配置捕获边沿 */
    FL_LPTIM16_IC_SetCaptureEdge(LPTIM16x, ic_init->ICEdge, Channel);
    /* 通道输入捕获使能 */
    FL_LPTIM16_SetChannelMode(LPTIM16x, FL_LPTIM16_CHANNEL_MODE_INPUT, Channel);
    return FL_PASS;
}

/**
  * @brief  设置 LPTIM16_IC_InitStruct 为默认配置
  * @param  ic_init 为 @ref FL_LPTIM16_IC_InitTypeDef类型的结构体
  *
  * @retval None
  */
void FL_LPTIM16_IC_StructInit(FL_LPTIM16_IC_InitTypeDef *ic_init)
{
    ic_init->ICInputPolarity          = FL_LPTIM16_IC_POLARITY_NORMAL;
    ic_init->ICInputDigitalFilter     = FL_DISABLE;
    ic_init->ICEdge                   = FL_LPTIM16_IC_EDGE_RISING;
    ic_init->channel1Prescaler        = 1 - 1;
    ic_init->channel1CaptureSource    = FL_LPTIM16_IC1_CAPTURE_SOURCE_GROUP0;
}

/**
  * @brief  根据需要功能配置LPTIM16寄存器工作在输出比较模式
  *
  * @param  LPTIM16x  外设入口地址
  * @param  oc_init 为 @ref FL_LPTIM16_OC_InitTypeDef类型的结构体
  * @param  Channel LPTIM16输出通道
  *
  * @retval ErrorStatus枚举值
  *         -FL_FAIL 配置过程发生错误
  *         -FL_PASS LPTIM16配置成功
  */
FL_ErrorStatus FL_LPTIM16_OC_Init(LPTIM16_Type *LPTIM16x, uint32_t Channel, FL_LPTIM16_OC_InitTypeDef *oc_init)
{
    /* 参数检查 */
    assert_param(IS_LPTIM16_INSTANCE(LPTIM16x));
    assert_param(IS_FL_LPTIM16_CHANNEL(Channel));
    assert_param(IS_FL_LPTIM16_OC_POLARITY(oc_init->OCPolarity));
    /* 比较通道极性 */
    FL_LPTIM16_OC_SetPolarity(LPTIM16x, oc_init->OCPolarity, Channel);
    /* 设置比较值 */
    switch(Channel)
    {
        case FL_LPTIM16_CHANNEL_1:
            FL_LPTIM16_WriteCompareCH1(LPTIM16x, oc_init->compareValue);
            break;
        case FL_LPTIM16_CHANNEL_2:
            FL_LPTIM16_WriteCompareCH2(LPTIM16x, oc_init->compareValue);
            break;
        default :
            return FL_FAIL;
    }
    /* 通道输出比较使能 */
    FL_LPTIM16_SetChannelMode(LPTIM16x, FL_LPTIM16_CHANNEL_MODE_OUTPUT, Channel);
    return FL_PASS;
}

/**
  * @brief  设置 LPTIM16_OC_InitStruct 为默认配置
  * @param  oc_init 为 @ref FL_LPTIM16_OC_InitTypeDef类型的结构体
  *
  * @retval None
  */
void FL_LPTIM16_OC_StructInit(FL_LPTIM16_OC_InitTypeDef *oc_init)
{
    oc_init->compareValue = 0;
    oc_init->OCPolarity   = FL_LPTIM16_OC_POLARITY_NORMAL;
}

/**
  * @}
  */

#endif /* FL_LPTIM16_DRIVER_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/*************************(C) COPYRIGHT Fudan Microelectronics **** END OF FILE*************************/

