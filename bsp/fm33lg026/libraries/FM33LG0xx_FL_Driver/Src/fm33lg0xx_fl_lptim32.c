/**
  ****************************************************************************************************
  * @file    fm33lg0xx_fl_lptim32.c
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
#include "fm33lg0xx_fl.h"

/** @addtogroup FM33LG0XX_FL_Driver
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

#define         IS_LPTIM32_INSTANCE(INSTANCE)                            ((INSTANCE) == LPTIM32)

#define         IS_FL_LPTIM32_CHANNEL(__VALUE__)                        (((__VALUE__) == FL_LPTIM32_CHANNEL_1)||\
                                                                         ((__VALUE__) == FL_LPTIM32_CHANNEL_2)||\
                                                                         ((__VALUE__) == FL_LPTIM32_CHANNEL_3)||\
                                                                         ((__VALUE__) == FL_LPTIM32_CHANNEL_4))

#define         IS_FL_LPTIM32_CMU_CLK_SOURCE(__VALUE__)                 (((__VALUE__) == FL_CMU_LPTIM32_CLK_SOURCE_RCLF)||\
                                                                         ((__VALUE__) == FL_CMU_LPTIM32_CLK_SOURCE_RCLP)||\
                                                                         ((__VALUE__) == FL_CMU_LPTIM32_CLK_SOURCE_LSCLK)||\
                                                                         ((__VALUE__) == FL_CMU_LPTIM32_CLK_SOURCE_APBCLK))

#define         IS_FL_LPTIM32_CLK_SOURCE(__VALUE__)                     (((__VALUE__) == FL_LPTIM32_CLK_SOURCE_INTERNAL)||\
                                                                         ((__VALUE__) == FL_LPTIM32_CLK_SOURCE_EXTERNAL))

#define         IS_FL_LPTIM32_PSC(__VALUE__)                            (((__VALUE__) == FL_LPTIM32_PSC_DIV1)||\
                                                                         ((__VALUE__) == FL_LPTIM32_PSC_DIV2)||\
                                                                         ((__VALUE__) == FL_LPTIM32_PSC_DIV4)||\
                                                                         ((__VALUE__) == FL_LPTIM32_PSC_DIV8)||\
                                                                         ((__VALUE__) == FL_LPTIM32_PSC_DIV16)||\
                                                                         ((__VALUE__) == FL_LPTIM32_PSC_DIV32)||\
                                                                         ((__VALUE__) == FL_LPTIM32_PSC_DIV64)||\
                                                                         ((__VALUE__) == FL_LPTIM32_PSC_DIV128))

#define         IS_FL_LPTIM32_OPERATION_MODE(__VALUE__)                 (((__VALUE__) == FL_LPTIM32_OPERATION_MODE_NORMAL)||\
                                                                         ((__VALUE__) == FL_LPTIM32_OPERATION_MODE_EXTERNAL_TRIGGER_CNT)||\
                                                                         ((__VALUE__) == FL_LPTIM32_OPERATION_MODE_EXTERNAL_ASYNC_PULSE_CNT)||\
                                                                         ((__VALUE__) == FL_LPTIM32_OPERATION_MODE_TIMEOUT))

#define         IS_FL_LPTIM32_ETR_TRIGGER_EDGE(__VALUE__)               (((__VALUE__) == FL_LPTIM32_ETR_TRIGGER_EDGE_RISING)||\
                                                                         ((__VALUE__) == FL_LPTIM32_ETR_TRIGGER_EDGE_FALLING)||\
                                                                         ((__VALUE__) == FL_LPTIM32_ETR_TRIGGER_EDGE_BOTH))

#define         IS_FL_LPTIM32_ETR_COUNT_EDGE(__VALUE__)                 (((__VALUE__) == FL_LPTIM32_ETR_COUNT_EDGE_RISING)||\
                                                                         ((__VALUE__) == FL_LPTIM32_ETR_COUNT_EDGE_FALLING))

#define         IS_FL_LPTIM32_ONE_PULSE_MODE(__VALUE__)                 (((__VALUE__) == FL_LPTIM32_ONE_PULSE_MODE_CONTINUOUS)||\
                                                                         ((__VALUE__) == FL_LPTIM32_ONE_PULSE_MODE_SINGLE))

#define         IS_FL_LPTIM32_IC_EDGE(__VALUE__)                        (((__VALUE__) == FL_LPTIM32_IC_EDGE_RISING)||\
                                                                         ((__VALUE__) == FL_LPTIM32_IC_EDGE_FALLING)||\
                                                                         ((__VALUE__) == FL_LPTIM32_IC_EDGE_BOTH))

#define         IS_FL_LPTIM32_OC_POLARITY(__VALUE__)                    (((__VALUE__) == FL_LPTIM32_OC_POLARITY_NORMAL)||\
                                                                         ((__VALUE__) == FL_LPTIM32_OC_POLARITY_INVERT))

#define         IS_FL_LPTIM32_IC1_CAPTURE_SOURCE(__VALUE__)             (((__VALUE__) == FL_LPTIM32_IC1_CAPTURE_SOURCE_GROUP0)||\
                                                                         ((__VALUE__) == FL_LPTIM32_IC1_CAPTURE_SOURCE_GROUP1)||\
                                                                         ((__VALUE__) == FL_LPTIM32_IC1_CAPTURE_SOURCE_GROUP2)||\
                                                                         ((__VALUE__) == FL_LPTIM32_IC1_CAPTURE_SOURCE_GROUP3))

#define         IS_FL_LPTIM32_TRGO_SOURCE(__VALUE__)                    (((__VALUE__) == FL_LPTIM32_TRGO_ENABLE)||\
                                                                         ((__VALUE__) == FL_LPTIM32_TRGO_UPDATE)||\
                                                                         ((__VALUE__) == FL_LPTIM32_TRGO_OC1_CMP_PULSE)||\
                                                                         ((__VALUE__) == FL_LPTIM32_TRGO_IC1_EVENT)||\
                                                                         ((__VALUE__) == FL_LPTIM32_TRGO_IC2_EVENT))

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup LPTIM32_FL_EF_Init
  * @{
  */

/**
  * @brief  复位LPTIM32 外设
  * @param  外设入口地址
  * @retval 返回错误状态，可能值：
  *         -FL_PASS 外设寄存器值恢复复位值
  *         -FL_FAIL 未成功执行
  */
FL_ErrorStatus FL_LPTIM32_DeInit(LPTIM32_Type *LPTIM32x)
{
    /* 参数检查 */
    assert_param(IS_LPTIM32_INSTANCE(LPTIM32x));
    /* 使能外设复位 */
    FL_RMU_EnablePeripheralReset(RMU);
    /* 复位外设寄存器 */
    FL_RMU_EnableResetAPBPeripheral(RMU, FL_RMU_RSTAPB_LPTIM32);
    FL_RMU_DisableResetAPBPeripheral(RMU, FL_RMU_RSTAPB_LPTIM32);
    /* 关闭外设总线时钟和工作时钟 */
    FL_CMU_DisableGroup1BusClock(FL_CMU_GROUP1_BUSCLK_LPTIM32);
    FL_CMU_DisableGroup3OperationClock(FL_CMU_GROUP3_OPCLK_LPTIM32);
    /* 锁定外设复位 */
    FL_RMU_DisablePeripheralReset(RMU);
    return FL_PASS;
}

/**
  * @brief  根据需要功能配置LPTIM32寄存器使之工作在定时器功能模式下
  *
  * @note   需要使用ETR作为计数源时，建议根据需求配置为异步脉冲计数模式
  *         @ref FL_LPTIM32_OPERATION_MODE_EXTERNAL_ASYNC_PULSE_CNT 或外部触发计数模式
  *         @ref FL_LPTIM32_OPERATION_MODE_EXTERNAL_TRIGGER_CNT
  *
  * @param  LPTIM32x  外设入口地址
  * @param  init 为 @ref FL_LPTIM32_InitTypeDef类型的结构体
  *
  * @retval ErrorStatus枚举值
  *         -FL_FAIL 配置过程发生错误
  *         -FL_PASS LPTIM32配置成功
  */
FL_ErrorStatus FL_LPTIM32_Init(LPTIM32_Type *LPTIM32x, FL_LPTIM32_InitTypeDef *init)
{
    /* 参数检查 */
    assert_param(IS_LPTIM32_INSTANCE(LPTIM32x));
    assert_param(IS_FL_LPTIM32_CMU_CLK_SOURCE(init->clockSource));
    assert_param(IS_FL_LPTIM32_CLK_SOURCE(init->prescalerClockSource));
    assert_param(IS_FL_LPTIM32_PSC(init->prescaler));
    assert_param(IS_FL_LPTIM32_OPERATION_MODE(init->mode));
    assert_param(IS_FL_LPTIM32_ONE_PULSE_MODE(init->onePulseMode));
    assert_param(IS_FL_LPTIM32_ETR_TRIGGER_EDGE(init->triggerEdge));
    assert_param(IS_FL_LPTIM32_ETR_COUNT_EDGE(init->countEdge));
    /* 时钟配置 */
    if(LPTIM32x == LPTIM32)
    {
        /* 使能总线时钟 */
        FL_CMU_EnableGroup1BusClock(FL_CMU_GROUP1_BUSCLK_LPTIM32);
        /* 除了异步计数模式，其他模式都需要使能工作时钟 */
        if(init->mode != FL_LPTIM32_OPERATION_MODE_EXTERNAL_ASYNC_PULSE_CNT)
        {
            /* 使能工作时钟 */
            FL_CMU_EnableGroup3OperationClock(FL_CMU_GROUP3_OPCLK_LPTIM32);
            /* 设置工作时钟时钟源 */
            FL_CMU_SetLPTIM32ClockSource(init->clockSource);
        }
    }
    /* 配置分频器的时钟源 */
    FL_LPTIM32_SetClockSource(LPTIM32x, init->prescalerClockSource);
    /* 配置时钟分频 */
    FL_LPTIM32_SetPrescaler(LPTIM32x, init->prescaler);
    /* 配置定时器工作模式 */
    FL_LPTIM32_SetOperationMode(LPTIM32x, init->mode);
    /* 配置定时器不同模式下的特殊寄存器 */
    switch(init->mode)
    {
        case FL_LPTIM32_OPERATION_MODE_NORMAL:
        {
            if(init->prescalerClockSource == FL_LPTIM32_CLK_SOURCE_EXTERNAL)
            {
                /* 配置外部计数边沿 */
                FL_LPTIM32_SetETRCountEdge(LPTIM32x, init->countEdge);
                /* 开启外部输入滤波 */
                FL_LPTIM32_EnableETRFilter(LPTIM32x);
            }
        }
        break;
        case FL_LPTIM32_OPERATION_MODE_EXTERNAL_TRIGGER_CNT:
        {
            /* 配置外部输入有效边沿 */
            FL_LPTIM32_SetETRTriggerEdge(LPTIM32x, init->triggerEdge);
        }
        break;
        case FL_LPTIM32_OPERATION_MODE_EXTERNAL_ASYNC_PULSE_CNT:
        {
            /* 配置外部计数边沿 */
            FL_LPTIM32_SetETRCountEdge(LPTIM32x, init->countEdge);
            /* 开启外部输入滤波 */
            FL_LPTIM32_EnableETRFilter(LPTIM32x);
        }
        break;
        case FL_LPTIM32_OPERATION_MODE_TIMEOUT:
        {
            /* 配置外部输入有效边沿 */
            FL_LPTIM32_SetETRTriggerEdge(LPTIM32x, init->triggerEdge);
        }
        break;
    }
    /* 单次计数模式 */
    FL_LPTIM32_SetOnePulseMode(LPTIM32x, init->onePulseMode);
    /* 设置重装载值 */
    FL_LPTIM32_WriteAutoReload(LPTIM32x, init->autoReload);
    return FL_PASS;
}

/**
  * @brief  设置 LPTIM32_InitStruct 为默认配置
  * @param  init 为 @ref FL_LPTIM32_InitTypeDef类型的结构体
  *
  * @retval None
  */
void FL_LPTIM32_StructInit(FL_LPTIM32_InitTypeDef *init)
{
    init->clockSource           = FL_CMU_LPTIM32_CLK_SOURCE_APBCLK;
    init->prescalerClockSource  = FL_LPTIM32_CLK_SOURCE_INTERNAL;
    init->prescaler             = FL_LPTIM32_PSC_DIV1;
    init->autoReload            = 0;
    init->mode                  = FL_LPTIM32_OPERATION_MODE_NORMAL;
    init->countEdge             = FL_LPTIM32_ETR_COUNT_EDGE_RISING;
    init->triggerEdge           = FL_LPTIM32_ETR_TRIGGER_EDGE_RISING;
    init->onePulseMode          = FL_LPTIM32_ONE_PULSE_MODE_CONTINUOUS;
}

/**
  * @brief  配置LPTIM32工作在输入捕获模式
  *
  * @param  LPTIM32x  外设入口地址
  * @param  ic_init 为 @ref FL_LPTIM32_IC_InitTypeDef类型的结构体
  * @param  Channel LPTIM32输入通道
  *
  * @retval ErrorStatus枚举值
  *         -FL_FAIL 配置过程发生错误
  *         -FL_PASS LPTIM32配置成功
  */
//输入捕获配置
FL_ErrorStatus FL_LPTIM32_IC_Init(LPTIM32_Type *LPTIM32x, uint32_t Channel, FL_LPTIM32_IC_InitTypeDef *ic_init)
{
    FL_ErrorStatus result = FL_PASS;
    /* 参数检查 */
    assert_param(IS_LPTIM32_INSTANCE(LPTIM32x));
    assert_param(IS_FL_LPTIM32_CHANNEL(Channel));
    assert_param(IS_FL_LPTIM32_IC_EDGE(ic_init->ICEdge));
    assert_param(IS_FL_LPTIM32_IC1_CAPTURE_SOURCE(ic_init->ICSource));
    /* 通道1捕获源 */
    if(Channel == FL_LPTIM32_CHANNEL_1)
    {
        FL_LPTIM32_IC_SetChannel1CaptureSource(LPTIM32, ic_init->ICSource);
    }
    /* 捕获通道边沿 */
    FL_LPTIM32_IC_SetCaptureEdge(LPTIM32, ic_init->ICEdge, Channel);
    /* 通道输入捕获使能 */
    FL_LPTIM32_SetChannelMode(LPTIM32, FL_LPTIM32_CHANNEL_MODE_INPUT, Channel);
    return result;
}

/**
  * @brief  设置 LPTIM32_IC_InitStruct 为默认配置
  * @param  ic_init为 @ref FL_LPTIM32_IC_InitTypeDef类型的结构体
  *
  * @retval None
  */
void FL_LPTIM32_IC_StructInit(FL_LPTIM32_IC_InitTypeDef *ic_init)
{
    ic_init->ICEdge      = FL_LPTIM32_IC_EDGE_RISING;
    ic_init->ICSource    = FL_LPTIM32_IC1_CAPTURE_SOURCE_GROUP0;
}

/**
  * @brief  根据需要功能配置LPTIM32寄存器工作在输出比较模式
  *
  * @param  LPTIM32x  外设入口地址
  * @param  oc_init 为 @ref FL_LPTIM32_OC_InitTypeDef类型的结构体
  * @param  Channel LPTIM32输出通道
  *
  * @retval ErrorStatus枚举值
  *         -FL_FAIL 配置过程发生错误
  *         -FL_PASS LPTIM32配置成功
  */
FL_ErrorStatus FL_LPTIM32_OC_Init(LPTIM32_Type *LPTIM32x, uint32_t Channel, FL_LPTIM32_OC_InitTypeDef *oc_init)
{
    FL_ErrorStatus result = FL_PASS;
    /* 参数检查 */
    assert_param(IS_LPTIM32_INSTANCE(LPTIM32x));
    assert_param(IS_FL_LPTIM32_CHANNEL(Channel));
    assert_param(IS_FL_LPTIM32_OC_POLARITY(oc_init->OCPolarity));
    /* 比较通道极性 */
    FL_LPTIM32_OC_SetPolarity(LPTIM32x, oc_init->OCPolarity, Channel);
    /* 设置比较值 */
    switch(Channel)
    {
        case FL_LPTIM32_CHANNEL_1:
            FL_LPTIM32_WriteCompareCH1(LPTIM32x, oc_init->compareValue);
            break;
        case FL_LPTIM32_CHANNEL_2:
            FL_LPTIM32_WriteCompareCH2(LPTIM32x, oc_init->compareValue);
            break;
        case FL_LPTIM32_CHANNEL_3:
            FL_LPTIM32_WriteCompareCH3(LPTIM32x, oc_init->compareValue);
            break;
        case FL_LPTIM32_CHANNEL_4:
            FL_LPTIM32_WriteCompareCH4(LPTIM32x, oc_init->compareValue);
            break;
        default :
            result = FL_FAIL;
            break;
    }
    /* 通道输出比较使能 */
    FL_LPTIM32_SetChannelMode(LPTIM32x, FL_LPTIM32_CHANNEL_MODE_OUTPUT, Channel);
    return result;
}

/**
  * @brief  设置 LPTIM32_OC_InitStruct 为默认配置
  * @param  oc_init为 @ref FL_LPTIM32_OC_InitTypeDef类型的结构体
  *
  * @retval None
  */
void FL_LPTIM32_OC_StructInit(FL_LPTIM32_OC_InitTypeDef *oc_init)
{
    oc_init->compareValue = 0;
    oc_init->OCPolarity   = FL_LPTIM32_OC_POLARITY_NORMAL;
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

/*************************(C) COPYRIGHT Fudan Microelectronics **** END OF FILE*************************/
