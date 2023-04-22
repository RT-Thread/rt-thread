/**
  ****************************************************************************************************
  * @file    fm33lc0xx_fl_exti.c
  * @author  FMSH Application Team
  * @brief   Src file of EXTI FL Module
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

/** @addtogroup EXTI
  * @{
  */

#ifdef FL_EXTI_DRIVER_ENABLED

/* Private macros ------------------------------------------------------------*/
/** @addtogroup EXTI_FL_Private_Macros
  * @{
  */

#define IS_EXTI_ALL_INSTANCE(INSTANCE)             (((INSTANCE) == FL_GPIO_EXTI_LINE_0)||\
                                                    ((INSTANCE) == FL_GPIO_EXTI_LINE_1)||\
                                                    ((INSTANCE) == FL_GPIO_EXTI_LINE_2)||\
                                                    ((INSTANCE) == FL_GPIO_EXTI_LINE_3)||\
                                                    ((INSTANCE) == FL_GPIO_EXTI_LINE_4)||\
                                                    ((INSTANCE) == FL_GPIO_EXTI_LINE_5)||\
                                                    ((INSTANCE) == FL_GPIO_EXTI_LINE_6)||\
                                                    ((INSTANCE) == FL_GPIO_EXTI_LINE_7)||\
                                                    ((INSTANCE) == FL_GPIO_EXTI_LINE_8)||\
                                                    ((INSTANCE) == FL_GPIO_EXTI_LINE_9)||\
                                                    ((INSTANCE) == FL_GPIO_EXTI_LINE_10)||\
                                                    ((INSTANCE) == FL_GPIO_EXTI_LINE_11)||\
                                                    ((INSTANCE) == FL_GPIO_EXTI_LINE_12)||\
                                                    ((INSTANCE) == FL_GPIO_EXTI_LINE_13)||\
                                                    ((INSTANCE) == FL_GPIO_EXTI_LINE_14))

#define IS_EXTI_CLK_SOURCE(__VALUE__)              (((__VALUE__) == FL_RCC_EXTI_CLK_SOURCE_HCLK)||\
                                                    ((__VALUE__) == FL_RCC_EXTI_CLK_SOURCE_LSCLK))

#define IS_EXTI_INPUT_GROUP(__VALUE__)             (((__VALUE__) == FL_GPIO_EXTI_INPUT_GROUP0)||\
                                                    ((__VALUE__) == FL_GPIO_EXTI_INPUT_GROUP1)||\
                                                    ((__VALUE__) == FL_GPIO_EXTI_INPUT_GROUP2)||\
                                                    ((__VALUE__) == FL_GPIO_EXTI_INPUT_GROUP3))

#define IS_EXTI_TRIG_EDGE(__VALUE__)               (((__VALUE__) == FL_GPIO_EXTI_TRIGGER_EDGE_RISING)||\
                                                    ((__VALUE__) == FL_GPIO_EXTI_TRIGGER_EDGE_FALLING)||\
                                                    ((__VALUE__) == FL_GPIO_EXTI_TRIGGER_EDGE_BOTH))

#define IS_EXTI_FILTER(__VALUE__)                  (((__VALUE__) == FL_ENABLE)||\
                                                    ((__VALUE__) == FL_DISABLE))

/**
  * @}
  */

/* Private consts ------------------------------------------------------------*/
/** @addtogroup EXTI_FL_Private_Consts
  * @{
  */

typedef void (*pSetExtiLineFunc)(GPIO_COMMON_Type *, uint32_t);
static const pSetExtiLineFunc setExtiLineFuncs[] =
{
    FL_GPIO_SetExtiLine0,
    FL_GPIO_SetExtiLine1,
    FL_GPIO_SetExtiLine2,
    FL_GPIO_SetExtiLine3,
    FL_GPIO_SetExtiLine4,
    FL_GPIO_SetExtiLine5,
    FL_GPIO_SetExtiLine6,
    FL_GPIO_SetExtiLine7,
    FL_GPIO_SetExtiLine8,
    FL_GPIO_SetExtiLine9,
    FL_GPIO_SetExtiLine10,
    NULL,
    FL_GPIO_SetExtiLine12,
    FL_GPIO_SetExtiLine13,
    FL_GPIO_SetExtiLine14,
};

typedef void (*pSetTrigEdgeFunc)(GPIO_COMMON_Type *, uint32_t, uint32_t);
static const pSetTrigEdgeFunc setTrigEdgeFuncs[] =
{
    FL_GPIO_SetTriggerEdge,
};

/**
  * @}
  */

/** @addtogroup EXTI_FL_EF_Init
  * @{
  */

/**
  * @brief  EXTI通用配置设置
  *
  * @param  EXTI_CommonInitStruct 指向 @ref FL_EXTI_CommonInitTypeDef 类型的结构体，它包含EXTI外设通用配置信息
  *
  * @retval ErrorStatus枚举值
  *         -FL_FAIL 配置过程发生错误
  *         -FL_PASS EXTI配置成功
  */
FL_ErrorStatus FL_EXTI_CommonInit(FL_EXTI_CommonInitTypeDef *EXTI_CommonInitStruct)
{
    assert_param(IS_EXTI_CLK_SOURCE(EXTI_CommonInitStruct->clockSource));
    /* 使能IO时钟寄存器总线时钟 */
    FL_RCC_EnableGroup1BusClock(FL_RCC_GROUP1_BUSCLK_PAD);
    /* 使能并配置外部中断时钟源 */
    FL_RCC_EnableGroup1OperationClock(FL_RCC_GROUP1_OPCLK_EXTI);
    FL_RCC_SetEXTIClockSource(EXTI_CommonInitStruct->clockSource);
    return FL_PASS;
}

/**
  * @brief  复位EXTI通用配置设置
  *
  * @retval 执行结果
  *         -FL_PASS 外设寄存器值恢复复位值
  *         -FL_FAIL 未成功执行
  */
FL_ErrorStatus FL_EXTI_CommonDeinit(void)
{
    /* 关闭外部中断时钟源 */
    FL_RCC_DisableGroup1OperationClock(FL_RCC_GROUP1_OPCLK_EXTI);
    return FL_PASS;
}

/**
  * @brief  设置 EXTI_CommonInitStruct 为默认配置
  * @param  EXTI_CommonInitStruct 指向需要将值设置为默认配置的结构体 @ref FL_EXTI_CommonInitTypeDef 结构体
  *
  * @retval None
  */
void FL_EXTI_CommonStructInit(FL_EXTI_CommonInitTypeDef *EXTI_CommonInitStruct)
{
    EXTI_CommonInitStruct->clockSource = FL_RCC_EXTI_CLK_SOURCE_LSCLK;
}

/**
  * @brief  EXTI配置设置
  *
  * @param  extiLineX 外设入口地址
  * @param  EXTI_InitStruct 指向 @ref FL_EXTI_InitTypeDef 类型的结构体，它包含EXTI外设配置信息
  *
  * @retval ErrorStatus枚举值
  *         -FL_FAIL 配置过程发生错误
  *         -FL_PASS EXTI配置成功
  */
FL_ErrorStatus FL_EXTI_Init(uint32_t extiLineX, FL_EXTI_InitTypeDef *EXTI_InitStruct)
{
    uint8_t extiLineId;
    uint32_t tmpExtiLineX;
    /* 检查参数合法性 */
    assert_param(IS_EXTI_ALL_INSTANCE(extiLineX));
    assert_param(IS_EXTI_INPUT_GROUP(EXTI_InitStruct->input));
    assert_param(IS_EXTI_TRIG_EDGE(EXTI_InitStruct->triggerEdge));
    assert_param(IS_EXTI_FILTER(EXTI_InitStruct->filter));
    /* 获取EXTI中断线对应id号 */
    tmpExtiLineX = extiLineX;
    for(extiLineId = 0; tmpExtiLineX != FL_GPIO_EXTI_LINE_0; tmpExtiLineX >>= 1, extiLineId++);
    /* 设置中断线连接的IO */
    setExtiLineFuncs[extiLineId](GPIO, EXTI_InitStruct->input << (2 * extiLineId));
    /* 设置数字滤波 */
    EXTI_InitStruct->filter == FL_ENABLE ? FL_GPIO_EnableDigitalFilter(GPIO, extiLineX) : FL_GPIO_DisableDigitalFilter(GPIO, extiLineX);
    /* 设置中断线触发边沿 */
    setTrigEdgeFuncs[extiLineId / 16](GPIO, extiLineX, EXTI_InitStruct->triggerEdge);
    /* 延时需要大于3个32K的周期 */
        for(uint16_t i=0; i<1000; ++i)
        {
            __NOP();
        }
    /* 清除外部中断标志 */
    FL_GPIO_ClearFlag_EXTI(GPIO, extiLineX);
    /* 清除中断挂起 */
    NVIC_ClearPendingIRQ(GPIO_IRQn);
    return FL_PASS;
}

/**
  * @brief  复位EXTI配置设置
  *
  * @retval ErrorStatus枚举值
  *         -FL_FAIL 发生错误
  *         -FL_PASS EXTI设置复位成功
  */
FL_ErrorStatus FL_EXTI_DeInit(uint32_t extiLineX)
{
    uint8_t extiLineId;
    uint32_t tmpExtiLineX;
    /* 检查参数合法性 */
    assert_param(IS_EXTI_ALL_INSTANCE(extiLineX));
    /* 获取EXTI中断线对应id号 */
    tmpExtiLineX = extiLineX;
    for(extiLineId = 0; tmpExtiLineX != FL_GPIO_EXTI_LINE_0; tmpExtiLineX >>= 1, extiLineId++);
    /* 清除外部中断标志 */
    FL_GPIO_ClearFlag_EXTI(GPIO, extiLineX);
    /* 中断线触发边沿禁止 */
    setTrigEdgeFuncs[extiLineId / 16](GPIO, extiLineX, FL_GPIO_EXTI_TRIGGER_EDGE_DISABLE);
    /* 禁止数字滤波 */
    FL_GPIO_DisableDigitalFilter(GPIO, extiLineX);
    return FL_PASS;
}

/**
  * @brief  设置 EXTI_InitStruct 为默认配置
  * @param  EXTI_InitStruct 指向需要将值设置为默认配置的结构体 @ref FL_EXTI_InitTypeDef 结构体
  *
  * @retval None
  */
void FL_EXTI_StructInit(FL_EXTI_InitTypeDef *EXTI_InitStruct)
{
    EXTI_InitStruct->filter = FL_DISABLE;
    EXTI_InitStruct->input = FL_GPIO_EXTI_INPUT_GROUP0;
    EXTI_InitStruct->triggerEdge = FL_GPIO_EXTI_TRIGGER_EDGE_RISING;
}

/**
  * @}
  */

#endif /* FL_EXTI_DRIVER_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
