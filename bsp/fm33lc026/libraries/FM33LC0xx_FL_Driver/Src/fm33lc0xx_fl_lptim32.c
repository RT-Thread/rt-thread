/**
  ****************************************************************************************************
  * @file    fm33lc0xx_fl_lptim32.c
  * @author  FMSH Application Team
  * @brief   Src file of LPTIM32 FL Module
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

/** @addtogroup LPTIM32
  * @{
  */

#ifdef FL_LPTIM32_DRIVER_ENABLED

/* Private macros ------------------------------------------------------------*/
/** @addtogroup LPTIM32_FL_Private_Macros
  * @{
  */

#define         IS_LPTIM32_INSTANCE(INSTANCE)                           (((INSTANCE) == LPTIM32))

#define         IS_FL_LPTIM32_OPCLK_SOURCE(__VALUE__)                   (((__VALUE__) == FL_RCC_LPTIM32_CLK_SOURCE_APB1CLK)||\
                                                                         ((__VALUE__) == FL_RCC_LPTIM32_CLK_SOURCE_LSCLK)||\
                                                                         ((__VALUE__) == FL_RCC_LPTIM32_CLK_SOURCE_LPOSC)||\
                                                                         ((__VALUE__) == FL_RCC_LPTIM32_CLK_SOURCE_RCMF_PSC))

#define         IS_FL_LPTIM32_CLK_SOURCE(__VALUE__)                     (((__VALUE__) == FL_LPTIM32_CLK_SOURCE_INTERNAL)||\
                                                                         ((__VALUE__) == FL_LPTIM32_CLK_SOURCE_EXTERNAL))

#define         IS_FL_LPTIM32_PRESCALER(__VALUE__)                      (((__VALUE__) == FL_LPTIM32_PSC_DIV1)||\
                                                                         ((__VALUE__) == FL_LPTIM32_PSC_DIV2)||\
                                                                         ((__VALUE__) == FL_LPTIM32_PSC_DIV4)||\
                                                                         ((__VALUE__) == FL_LPTIM32_PSC_DIV8)||\
                                                                         ((__VALUE__) == FL_LPTIM32_PSC_DIV16)||\
                                                                         ((__VALUE__) == FL_LPTIM32_PSC_DIV32)||\
                                                                         ((__VALUE__) == FL_LPTIM32_PSC_DIV64)||\
                                                                         ((__VALUE__) == FL_LPTIM32_PSC_DIV128))

#define         IS_FL_LPTIM32_MODE(__VALUE__)                           (((__VALUE__) == FL_LPTIM32_OPERATION_MODE_NORMAL)||\
                                                                         ((__VALUE__) == FL_LPTIM32_OPERATION_MODE_EXTERNAL_TRIGGER_CNT)||\
                                                                         ((__VALUE__) == FL_LPTIM32_OPERATION_MODE_EXTERNAL_ASYNC_PULSE_CNT)||\
                                                                         ((__VALUE__) == FL_LPTIM32_OPERATION_MODE_TIMEOUT))

#define         IS_FL_LPTIM32_ETR_TRIGEER_EDGE(__VALUE__)               (((__VALUE__) == FL_LPTIM32_ETR_TRIGGER_EDGE_RISING)||\
                                                                         ((__VALUE__) == FL_LPTIM32_ETR_TRIGGER_EDGE_FALLING)||\
                                                                         ((__VALUE__) == FL_LPTIM32_ETR_TRIGGER_EDGE_BOTH))

#define         IS_FL_LPTIM32_ONE_PULSE_MODE(__VALUE__)                 (((__VALUE__) == FL_LPTIM32_ONE_PULSE_MODE_CONTINUOUS)||\
                                                                         ((__VALUE__) == FL_LPTIM32_ONE_PULSE_MODE_SINGLE))

#define         IS_FL_LPTIM32_ETR_COUNT_EDGE(__VALUE__)                 (((__VALUE__) == FL_LPTIM32_ETR_COUNT_EDGE_RISING)||\
                                                                         ((__VALUE__) == FL_LPTIM32_ETR_COUNT_EDGE_FALLING))

#define         IS_FL_LPTIM32_IC_EDGE(__VALUE__)                        (((__VALUE__) == FL_LPTIM32_IC_EDGE_RISING)||\
                                                                         ((__VALUE__) == FL_LPTIM32_IC_EDGE_FALLING)||\
                                                                         ((__VALUE__) == FL_LPTIM32_IC_EDGE_BOTH))

#define         IS_FL_LPTIM32_OC_POLARITY(__VALUE__)                    (((__VALUE__) == FL_LPTIM32_OC_POLARITY_NORMAL)||\
                                                                         ((__VALUE__) == FL_LPTIM32_OC_POLARITY_INVERT))

#define         IS_FL_LPTIM32_CHANNEL(__VALUE__)                        (((__VALUE__) == FL_LPTIM32_CHANNEL_1)||\
                                                                         ((__VALUE__) == FL_LPTIM32_CHANNEL_2))

#define         IS_FL_LPTIM32_CAPTURE_SOURCE(__VALUE__)                 (((__VALUE__) == FL_LPTIM32_IC_CAPTURE_SOURCE_GROUP0)||\
                                                                         ((__VALUE__) == FL_LPTIM32_IC_CAPTURE_SOURCE_GROUP1)||\
                                                                         ((__VALUE__) == FL_LPTIM32_IC_CAPTURE_SOURCE_GROUP2)||\
                                                                         ((__VALUE__) == FL_LPTIM32_IC_CAPTURE_SOURCE_GROUP3))


/**
  * @}
  */

/** @addtogroup LPTIM32_FL_EF_Init
  * @{
  */

/**
  * @brief  复位LPTIM32外设
  * @param  LPTIM32x 外设入口地址
  * @retval 错误状态，可能值：
  *         -FL_PASS 外设寄存器值恢复复位值
  *         -FL_FAIL 未成功执行
  */
FL_ErrorStatus FL_LPTIM32_DeInit(LPTIM32_Type *LPTIM32x)
{
    FL_ErrorStatus status = FL_FAIL;
    assert_param(IS_LPTIM32_INSTANCE(LPTIM32x));
    /* 使能外设复位 */
    FL_RCC_EnablePeripheralReset();
    /*复位LPTIM*/
    FL_RCC_EnableResetAPB1Peripheral(FL_RCC_RSTAPB_LPTIM32);
    FL_RCC_DisableResetAPB1Peripheral(FL_RCC_RSTAPB_LPTIM32);
    /* 关闭外设总线时钟和工作时钟 */
    FL_RCC_DisableGroup1BusClock(FL_RCC_GROUP1_BUSCLK_LPTIM32);
    FL_RCC_DisableGroup2OperationClock(FL_RCC_GROUP2_OPCLK_LPTIM32);
    /* 锁定外设复位功能 */
    FL_RCC_DisablePeripheralReset();
    status = FL_PASS;
    return status;
}
/**
  * @brief  配置LPTIM32工作在定时器模式
  *
  * @note   其中 @ref FL_LPTIM32_OPERATION_MODE_EXTERNAL_ASYNC_PULSE_CNT 模式需要外部脉冲提供给LPTIM32模块作为工作时钟，此时
  *         LPTIM32完全工作在异步模式下。
  * @param  LPTIM32x  外设入口地址
  * @param  initStruct 指向 @ref FL_LPTIM32_InitTypeDef 结构体的指针
  *
  * @retval 错误状态，可能值：
  *         -FL_PASS 配置成功
  *         -FL_FAIL 配置过程发生错误
  */
FL_ErrorStatus FL_LPTIM32_Init(LPTIM32_Type *LPTIM32x, FL_LPTIM32_InitTypeDef *initStruct)
{
    FL_ErrorStatus status = FL_PASS;
    /* 检查入口参数 */
    assert_param(IS_LPTIM32_INSTANCE(LPTIM32x));
    assert_param(IS_FL_LPTIM32_OPCLK_SOURCE(initStruct->clockSource));
    assert_param(IS_FL_LPTIM32_CLK_SOURCE(initStruct->prescalerClockSource));
    assert_param(IS_FL_LPTIM32_PRESCALER(initStruct->prescaler));
    assert_param(IS_FL_LPTIM32_MODE(initStruct->mode));
    assert_param(IS_FL_LPTIM32_ETR_TRIGEER_EDGE(initStruct->triggerEdge));
    assert_param(IS_FL_LPTIM32_ONE_PULSE_MODE(initStruct->onePulseMode));
    assert_param(IS_FL_LPTIM32_ETR_COUNT_EDGE(initStruct->countEdge));
    /* 时钟配置 */
    if(LPTIM32x == LPTIM32)
    {
        /* 使能总线时钟 */
        FL_RCC_EnableGroup1BusClock(FL_RCC_GROUP1_BUSCLK_LPTIM32);
        /* 除了异步计数模式，其他模式都需要使能工作时钟 */
        if(initStruct->mode != FL_LPTIM32_OPERATION_MODE_EXTERNAL_ASYNC_PULSE_CNT)
        {
            /* 使能工作时钟 */
            FL_RCC_EnableGroup2OperationClock(FL_RCC_GROUP2_OPCLK_LPTIM32);
            /* 设置工作时钟时钟源 */
            FL_RCC_SetLPTIM32ClockSource(initStruct->clockSource);
        }
    }
    /* 配置分频器的时钟源 */
    FL_LPTIM32_SetClockSource(LPTIM32x, initStruct->prescalerClockSource);
    /* 配置时钟分频 */
    FL_LPTIM32_SetPrescaler(LPTIM32x, initStruct->prescaler);
    /* 配置定时器工作模式 */
    FL_LPTIM32_SetOperationMode(LPTIM32x, initStruct->mode);
    /* 配置定时器不同模式下的特殊寄存器 */
    switch(initStruct->mode)
    {
        case FL_LPTIM32_OPERATION_MODE_NORMAL:
        {
        }
        break;
        case FL_LPTIM32_OPERATION_MODE_EXTERNAL_TRIGGER_CNT:
        {
            /* 配置外部输入有效边沿 */
            FL_LPTIM32_SetETRTriggerEdge(LPTIM32x, initStruct->triggerEdge);
        }
        break;
        case FL_LPTIM32_OPERATION_MODE_EXTERNAL_ASYNC_PULSE_CNT:
        {
            /* 配置外部计数边沿 */
            FL_LPTIM32_SetETRCountEdge(LPTIM32x, initStruct->countEdge);
            /* 开启外部输入滤波 */
            FL_LPTIM32_EnableETRFilter(LPTIM32x);
        }
        break;
        case FL_LPTIM32_OPERATION_MODE_TIMEOUT:
        {
            /* 配置外部输入有效边沿 */
            FL_LPTIM32_SetETRTriggerEdge(LPTIM32x, initStruct->triggerEdge);
        }
        break;
    }
    /* 单次计数模式 */
    FL_LPTIM32_SetOnePulseMode(LPTIM32x, initStruct->onePulseMode);
    /* 设置重装载值 */
    FL_LPTIM32_WriteAutoReload(LPTIM32x, initStruct->autoReload);
    return status;
}
/**
  * @brief  将 @ref FL_LPTIM32_InitTypeDef 结构体初始化为默认配置
  * @param  initStruct 指向 @ref FL_LPTIM32_InitTypeDef 结构体的指针
  *
  * @retval None
  */
void FL_LPTIM32_StructInit(FL_LPTIM32_InitTypeDef *initStruct)
{
    initStruct->clockSource           = FL_RCC_LPTIM32_CLK_SOURCE_APB1CLK;
    initStruct->prescalerClockSource  = FL_LPTIM32_CLK_SOURCE_INTERNAL;
    initStruct->prescaler             = FL_LPTIM32_PSC_DIV1;
    initStruct->autoReload            = 0;
    initStruct->mode                  = FL_LPTIM32_OPERATION_MODE_NORMAL;
    initStruct->countEdge             = FL_LPTIM32_ETR_COUNT_EDGE_RISING;
    initStruct->triggerEdge           = FL_LPTIM32_ETR_TRIGGER_EDGE_RISING;
    initStruct->onePulseMode          = FL_LPTIM32_ONE_PULSE_MODE_CONTINUOUS;
}

/**
  * @brief  配置LPTIM32工作在输入捕获模式
  *
  * @param  LPTIM32x  外设入口地址
  * @param  initStruct_IC 指向 @ref FL_LPTIM32_IC_InitTypeDef 结构体的指针
  * @param  channel LPTIM32通道
  *         此参数可取以下值：
  *         @arg @ref FL_LPTIM32_CHANNEL_1
  *         @arg @ref FL_LPTIM32_CHANNEL_2
  *
  * @retval 错误状态，可能值：
  *         -FL_PASS 配置成功
  *         -FL_FAIL 配置过程发生错误
  */
FL_ErrorStatus FL_LPTIM32_IC_Init(LPTIM32_Type *LPTIM32x, uint32_t channel, FL_LPTIM32_IC_InitTypeDef *initStruct_IC)
{
    FL_ErrorStatus status = FL_PASS;
    /* 参数检查 */
    assert_param(IS_LPTIM32_INSTANCE(LPTIM32x));
    assert_param(IS_FL_LPTIM32_CHANNEL(channel));
    assert_param(IS_FL_LPTIM32_IC_EDGE(initStruct_IC->ICEdge));
    assert_param(IS_FL_LPTIM32_CAPTURE_SOURCE(initStruct_IC->ICSource));
    /* 通道捕获源 */
    FL_LPTIM32_IC_SetCaptureSource(LPTIM32, initStruct_IC->ICSource, channel);
    /* 捕获通道边沿 */
    FL_LPTIM32_IC_SetCaptureEdge(LPTIM32, initStruct_IC->ICEdge, channel);
    /* 通道输入捕获使能 */
    FL_LPTIM32_SetChannelMode(LPTIM32, FL_LPTIM32_CHANNEL_MODE_INPUT, channel);
    return status;
}
/**
  * @brief  将 @ref FL_LPTIM32_IC_InitTypeDef 结构体初始化为默认配置
  * @param  initStruct_IC 指向 @ref FL_LPTIM32_IC_InitTypeDef 结构体的指针
  *
  * @retval None
  */
void FL_LPTIM32_IC_StructInit(FL_LPTIM32_IC_InitTypeDef *initStruct_IC)
{
    initStruct_IC->ICEdge      = FL_LPTIM32_IC_EDGE_RISING;
    initStruct_IC->ICSource    = FL_LPTIM32_IC_CAPTURE_SOURCE_GROUP0;
}

/**
  * @brief  配置LPTIM32寄存器工作在输出比较模式
  *
  * @param  LPTIM32x  外设入口地址
  * @param  initStruct_OC 指向 @ref FL_LPTIM32_OC_InitTypeDef 结构体的指针
  * @param  channel LPTIM32通道
  *         此参数可取以下值：
  *         @arg @ref FL_LPTIM32_CHANNEL_1
  *         @arg @ref FL_LPTIM32_CHANNEL_2
  *
  * @retval ErrorStatus枚举值
  *         -FL_PASS 配置成功
  *         -FL_FAIL 配置过程发生错误
  */
FL_ErrorStatus FL_LPTIM32_OC_Init(LPTIM32_Type *LPTIM32x, uint32_t channel, FL_LPTIM32_OC_InitTypeDef *initStruct_OC)
{
    FL_ErrorStatus result = FL_PASS;
    /* 参数检查 */
    assert_param(IS_LPTIM32_INSTANCE(LPTIM32x));
    assert_param(IS_FL_LPTIM32_CHANNEL(channel));
    assert_param(IS_FL_LPTIM32_OC_POLARITY(initStruct_OC->OCPolarity));
    /* 比较通道极性 */
    FL_LPTIM32_OC_SetPolarity(LPTIM32x, initStruct_OC->OCPolarity, channel);
    /* 设置比较值 */
    switch(channel)
    {
        case FL_LPTIM32_CHANNEL_1:
            FL_LPTIM32_WriteCompareCH1(LPTIM32x, initStruct_OC->compareValue);
            break;
        case FL_LPTIM32_CHANNEL_2:
            FL_LPTIM32_WriteCompareCH2(LPTIM32x, initStruct_OC->compareValue);
            break;
        default :
            result = FL_FAIL;
            break;
    }
    /* 通道输出比较使能 */
    FL_LPTIM32_SetChannelMode(LPTIM32x, FL_LPTIM32_CHANNEL_MODE_OUTPUT, channel);
    return result;
}

/**
  * @brief  将 @ref FL_LPTIM32_OC_InitTypeDef 结构体初始化为默认配置
  * @param  initStruct_OC 指向 @ref FL_LPTIM32_OC_InitTypeDef 结构体的指针
  *
  * @retval None
  */
void FL_LPTIM32_OC_StructInit(FL_LPTIM32_OC_InitTypeDef *initStruct_OC)
{
    initStruct_OC->compareValue  = 0;
    initStruct_OC->OCPolarity    = FL_LPTIM32_OC_POLARITY_NORMAL;
}

/**
  * @}
  */

#endif /* FL_LPTIM32_DRIVER_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
