/**
  *******************************************************************************************************
  * @file    fm33lc0xx_fl_gptim.c
  * @author  FMSH Application Team
  * @brief   Src file of GPTIM FL Module
  *******************************************************************************************************
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
  *******************************************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "fm33lc0xx_fl.h"

/** @addtogroup FM33LC0XX_FL_Driver
  * @{
  */

/** @addtogroup GPTIM
  * @{
  */

#ifdef FL_GPTIM_DRIVER_ENABLED

/* Private macros ------------------------------------------------------------------*/
/** @addtogroup GPTIM_FL_Private_Macros
  * @{
  */


#define IS_GPTIM_INSTANCE(TIMx)                     (((TIMx) == GPTIM0) || \
                                                     ((TIMx) == GPTIM1))


#define IS_FL_GPTIM_COUNTERMODE(__VALUE__)          (((__VALUE__) == FL_GPTIM_COUNTER_DIR_UP) || \
                                                     ((__VALUE__) == FL_GPTIM_COUNTER_DIR_DOWN) || \
                                                     ((__VALUE__) == FL_GPTIM_COUNTER_ALIGNED_EDGE) || \
                                                     ((__VALUE__) == FL_GPTIM_COUNTER_ALIGNED_CENTER_UP) || \
                                                     ((__VALUE__) == FL_GPTIM_COUNTER_ALIGNED_CENTER_DOWN) || \
                                                     ((__VALUE__) == FL_GPTIM_COUNTER_ALIGNED_CENTER_UP_DOWN))

#define IS_FL_GPTIM_CLOCKDIVISION(__VALUE__)        (((__VALUE__) == FL_GPTIM_CLK_DIVISION_DIV1) || \
                                                     ((__VALUE__) == FL_GPTIM_CLK_DIVISION_DIV2) || \
                                                     ((__VALUE__) == FL_GPTIM_CLK_DIVISION_DIV4))


#define IS_FL_GPTIM_CHANNEL_MODE(__VALUE__)         (((__VALUE__) == FL_GPTIM_CHANNEL_MODE_OUTPUT) || \
                                                     ((__VALUE__) == FL_GPTIM_CHANNEL_MODE_INPUT_NORMAL) || \
                                                     ((__VALUE__) == FL_GPTIM_CHANNEL_MODE_INPUT_CROSSOVER) || \
                                                     ((__VALUE__) == FL_GPTIM_CHANNEL_MODE_INPUT_TRC))

#define IS_FL_GPTIM_IC_FILTER(__VALUE__)            (((__VALUE__) == FL_GPTIM_IC_FILTER_DIV1) || \
                                                     ((__VALUE__) == FL_GPTIM_IC_FILTER_DIV1_N2) || \
                                                     ((__VALUE__) == FL_GPTIM_IC_FILTER_DIV1_N4) || \
                                                     ((__VALUE__) == FL_GPTIM_IC_FILTER_DIV1_N8) || \
                                                     ((__VALUE__) == FL_GPTIM_IC_FILTER_DIV2_N6) || \
                                                     ((__VALUE__) == FL_GPTIM_IC_FILTER_DIV2_N8) || \
                                                     ((__VALUE__) == FL_GPTIM_IC_FILTER_DIV4_N6) || \
                                                     ((__VALUE__) == FL_GPTIM_IC_FILTER_DIV4_N8) || \
                                                     ((__VALUE__) == FL_GPTIM_IC_FILTER_DIV8_N6) || \
                                                     ((__VALUE__) == FL_GPTIM_IC_FILTER_DIV8_N8) || \
                                                     ((__VALUE__) == FL_GPTIM_IC_FILTER_DIV16_N5) || \
                                                     ((__VALUE__) == FL_GPTIM_IC_FILTER_DIV16_N6) || \
                                                     ((__VALUE__) == FL_GPTIM_IC_FILTER_DIV16_N8) || \
                                                     ((__VALUE__) == FL_GPTIM_IC_FILTER_DIV32_N5) || \
                                                     ((__VALUE__) == FL_GPTIM_IC_FILTER_DIV32_N6) || \
                                                     ((__VALUE__) == FL_GPTIM_IC_FILTER_DIV32_N8))

#define IS_FL_GPTIM_CHANNEL(__VALUE__)              (((__VALUE__) == FL_GPTIM_CHANNEL_1)\
                                                    || ((__VALUE__) == FL_GPTIM_CHANNEL_2)\
                                                    || ((__VALUE__) == FL_GPTIM_CHANNEL_3)\
                                                    || ((__VALUE__) == FL_GPTIM_CHANNEL_4))



#define IS_FL_GPTIM_SLAVE_MODE(__VALUE__)           (((__VALUE__) == FL_GPTIM_SLAVE_MODE_PROHIBITED)\
                                                    || ((__VALUE__) == FL_GPTIM_SLAVE_MODE_ENCODER_X2_TI1)\
                                                    || ((__VALUE__) == FL_GPTIM_SLAVE_MODE_ENCODER_X2_TI2)\
                                                    || ((__VALUE__) == FL_GPTIM_SLAVE_MODE_ENCODER_X4_TI1TI2)\
                                                    || ((__VALUE__) == FL_GPTIM_SLAVE_MODE_TRGI_RISE_RST)\
                                                    || ((__VALUE__) == FL_GPTIM_SLAVE_MODE_TRGI_HIGH_RUN)\
                                                    || ((__VALUE__) == FL_GPTIM_SLAVE_MODE_TRGI_RISE_RUN)\
                                                    || ((__VALUE__) == FL_GPTIM_SLAVE_MODE_TRGI_CLK))


#define IS_FL_GPTIM_TRIGGER_SRC(__VALUE__)          (((__VALUE__) ==FL_GPTIM_TIM_TS_ITR0 )\
                                                        ||((__VALUE__) ==FL_GPTIM_TIM_TS_ITR1 )\
                                                        ||((__VALUE__) ==FL_GPTIM_TIM_TS_ITR2)\
                                                        ||((__VALUE__) ==FL_GPTIM_TIM_TS_ITR3)\
                                                        ||((__VALUE__) ==FL_GPTIM_TIM_TS_TI1F_ED)\
                                                        ||((__VALUE__) ==FL_GPTIM_TIM_TS_TI1FP1)\
                                                        ||((__VALUE__) ==FL_GPTIM_TIM_TS_TI2FP2)\
                                                        ||((__VALUE__) ==FL_GPTIM_TIM_TS_ETRF))



#define IS_FL_GPTIM_ETR_FILTER(__VALUE__)           (((__VALUE__) == FL_GPTIM_ETR_FILTER_DIV1) || \
                                                     ((__VALUE__) == FL_GPTIM_ETR_FILTER_DIV1_N2) || \
                                                     ((__VALUE__) == FL_GPTIM_ETR_FILTER_DIV1_N4) || \
                                                     ((__VALUE__) == FL_GPTIM_ETR_FILTER_DIV1_N8) || \
                                                     ((__VALUE__) == FL_GPTIM_ETR_FILTER_DIV2_N6) || \
                                                     ((__VALUE__) == FL_GPTIM_ETR_FILTER_DIV2_N8) || \
                                                     ((__VALUE__) == FL_GPTIM_ETR_FILTER_DIV4_N6) || \
                                                     ((__VALUE__) == FL_GPTIM_ETR_FILTER_DIV4_N8) || \
                                                     ((__VALUE__) == FL_GPTIM_ETR_FILTER_DIV8_N6) || \
                                                     ((__VALUE__) == FL_GPTIM_ETR_FILTER_DIV8_N8) || \
                                                     ((__VALUE__) == FL_GPTIM_ETR_FILTER_DIV16_N5) || \
                                                     ((__VALUE__) == FL_GPTIM_ETR_FILTER_DIV16_N6) || \
                                                     ((__VALUE__) == FL_GPTIM_ETR_FILTER_DIV16_N8) || \
                                                     ((__VALUE__) == FL_GPTIM_ETR_FILTER_DIV32_N5) || \
                                                     ((__VALUE__) == FL_GPTIM_ETR_FILTER_DIV32_N6) || \
                                                     ((__VALUE__) == FL_GPTIM_ETR_FILTER_DIV32_N8))


#define IS_FL_GPTIM_ETR_PSC(__VALUE__)              (((__VALUE__) == FL_GPTIM_ETR_PSC_DIV1) ||\
                                                     ((__VALUE__) == FL_GPTIM_ETR_PSC_DIV2) ||\
                                                     ((__VALUE__) == FL_GPTIM_ETR_PSC_DIV4) ||\
                                                     ((__VALUE__) == FL_GPTIM_ETR_PSC_DIV8))

#define IS_FL_GPTIM_ETR_POLARITY(__VALUE__)         (((__VALUE__) == FL_GPTIM_ETR_POLARITY_NORMAL) || \
                                                     ((__VALUE__) == FL_GPTIM_ETR_POLARITY_INVERT))



#define IS_FL_GPTIM_IC_POLARITY(__VALUE__)          (((__VALUE__) == FL_GPTIM_IC_POLARITY_NORMAL) \
                                                       || ((__VALUE__) == FL_GPTIM_IC_POLARITY_INVERT))



#define IS_FL_GPTIM_IC_PSC(__VALUE__)               (((__VALUE__) == FL_GPTIM_IC_PSC_DIV1) \
                                                     || ((__VALUE__) == FL_GPTIM_IC_PSC_DIV2) \
                                                     || ((__VALUE__) == FL_GPTIM_IC_PSC_DIV4) \
                                                     || ((__VALUE__) == FL_GPTIM_IC_PSC_DIV8))

#define IS_FL_GPTIM_OC_POLARITY(__VALUE__)          (((__VALUE__) == FL_GPTIM_OC_POLARITY_NORMAL) \
                                                    || ((__VALUE__) == FL_GPTIM_OC_POLARITY_INVERT))

#define IS_FL_GPTIM_OC_MODE(__VALUE__)               (((__VALUE__) ==   FL_GPTIM_OC_MODE_FROZEN) \
                                                      || ((__VALUE__) == FL_GPTIM_OC_MODE_ACTIVE) \
                                                      || ((__VALUE__) == FL_GPTIM_OC_MODE_INACTIVE) \
                                                      || ((__VALUE__) == FL_GPTIM_OC_MODE_TOGGLE) \
                                                      || ((__VALUE__) == FL_GPTIM_OC_MODE_FORCED_INACTIVE) \
                                                      || ((__VALUE__) == FL_GPTIM_OC_MODE_FORCED_ACTIVE) \
                                                      || ((__VALUE__) == FL_GPTIM_OC_MODE_PWM1) \
                                                      || ((__VALUE__) == FL_GPTIM_OC_MODE_PWM2))

#define IS_FL_GPTIM_OC_FASTMODE(__VALUE__)          (((__VALUE__) == FL_ENABLE) \
                                                    || ((__VALUE__) == FL_DISABLE))

#define IS_FL_GPTIM_OC_PRELOAD(__VALUE__)           (((__VALUE__) == FL_ENABLE) \
                                                    || ((__VALUE__) == FL_DISABLE))

#define IS_FL_GPTIM_OC_ETR_CLEARN(__VALUE__)        (((__VALUE__) == FL_ENABLE) \
                                                    || ((__VALUE__) == FL_DISABLE))


#define IS_FL_GPTIM_TRIGGER_DELAY(__VALUE__)       (((__VALUE__) == FL_DISABLE) \
                                                    || ((__VALUE__) == FL_ENABLE))


#define IS_FL_GPTIM_IC_CAPTURE_STATE(__VALUE__)    (((__VALUE__) == FL_DISABLE) \
                                                     || ((__VALUE__) == FL_ENABLE))
/**
  * @}
  */


/* Private function prototypes -----------------------------------------------*/
/** @defgroup GPTIM_FL_Private_Functions GPTIM Private Functions
  * @{
  */
static FL_ErrorStatus  OCConfig(GPTIM_Type *TIMx, uint32_t Channel, FL_GPTIM_OC_InitTypeDef *TIM_OC_InitStruct);

/**
  * @}
  */

/** @addtogroup GPTIM_FL_EF_Init
  * @{
  */

/**
  * @brief  复位GPTIM外设
  * @param  TIMx 外设入口地址
  * @retval 错误状态，可能值：
  *         -FL_PASS 外设寄存器值恢复复位值
  *         -FL_FAIL 未成功执行
  */
FL_ErrorStatus FL_GPTIM_DeInit(GPTIM_Type *TIMx)
{
    FL_ErrorStatus result = FL_PASS;
    /* Check the parameters */
    assert_param(IS_GPTIM_INSTANCE(TIMx));
    /* 使能外设复位 */
    FL_RCC_EnablePeripheralReset();
    if(TIMx == GPTIM0)
    {
        /* 使能外设复位 */
        FL_RCC_EnableResetAPB1Peripheral(FL_RCC_RSTAPB_GPTIM0);
        FL_RCC_DisableResetAPB1Peripheral(FL_RCC_RSTAPB_GPTIM0);
        /* 关闭外设时钟 */
        FL_RCC_DisableGroup4BusClock(FL_RCC_GROUP4_BUSCLK_GPTIM0);
    }
    else
        if(TIMx == GPTIM1)
        {
            /* 使能外设复位 */
            FL_RCC_EnableResetAPB1Peripheral(FL_RCC_RSTAPB_GPTIM1);
            FL_RCC_DisableResetAPB1Peripheral(FL_RCC_RSTAPB_GPTIM1);
            /* 关闭外设时钟 */
            FL_RCC_DisableGroup4BusClock(FL_RCC_GROUP4_BUSCLK_GPTIM1);
        }
        else
        {
            result = FL_FAIL;
        }
    /* 锁定外设复位 */
    FL_RCC_DisablePeripheralReset();
    return result;
}

/**
  * @brief  配置GPTIM基本定时器时基单元（内部时钟源）
  * @param  TIMx 外设入口地址
  * @param  init 指向 @ref FL_GPTIM_InitTypeDef 结构体的指针
  * @retval 错误状态，可能值：
  *         -FL_PASS 配置成功
  *         -FL_FAIL 配置过程发生错误
  */
FL_ErrorStatus FL_GPTIM_Init(GPTIM_Type *TIMx, FL_GPTIM_InitTypeDef *init)
{
    uint32_t i = 5;
    /* 参数检查 */
    assert_param(IS_GPTIM_INSTANCE(TIMx));
    assert_param(IS_FL_GPTIM_COUNTERMODE(init->counterMode));
    assert_param(IS_FL_GPTIM_CLOCKDIVISION(init->clockDivision));
    /* 时钟总线使能配置 */
    if(TIMx == GPTIM0)
    {
        FL_RCC_EnableGroup4BusClock(FL_RCC_GROUP4_BUSCLK_GPTIM0);
    }
    else
        if(TIMx == GPTIM1)
        {
            FL_RCC_EnableGroup4BusClock(FL_RCC_GROUP4_BUSCLK_GPTIM1);
        }
    /* 计数器计数模式配置 */
    switch(init->counterMode)
    {
        /* 中心对称模式 */
        case FL_GPTIM_COUNTER_ALIGNED_CENTER_DOWN   :
        case FL_GPTIM_COUNTER_ALIGNED_CENTER_UP     :
        case FL_GPTIM_COUNTER_ALIGNED_CENTER_UP_DOWN:
            FL_GPTIM_SetCounterAlignedMode(TIMx, init->counterMode);
            break;
        default:
            /* 边沿模式 */
            FL_GPTIM_SetCounterDirection(TIMx, init->counterMode);
            FL_GPTIM_SetCounterAlignedMode(TIMx, FL_GPTIM_COUNTER_ALIGNED_EDGE);
            break;
    }
    /* 自动重装载值 */
    FL_GPTIM_WriteAutoReload(TIMx, init->autoReload);
    /* 定时器分频系数与数字滤波器所使用的采样时钟分频比 */
    FL_GPTIM_SetClockDivision(TIMx, init->clockDivision);
    /* 时钟分频 */
    FL_GPTIM_WritePrescaler(TIMx, init->prescaler);
    /* 预装载配置 */
    if(init->autoReloadState == FL_ENABLE)
    {
        FL_GPTIM_EnableARRPreload(TIMx);
    }
    else
    {
        FL_GPTIM_DisableARRPreload(TIMx);
    }
    /* 手动触发更新事件，将配置值写入 */
    FL_GPTIM_GenerateUpdateEvent(TIMx);
    while((!FL_GPTIM_IsActiveFlag_Update(TIMx))&&i)
    {
        i--;
    }
    /*清除UIF标志，防止产生UG事件中断*/
    FL_GPTIM_ClearFlag_Update(TIMx);
    return FL_PASS;
}

/**
  * @brief  将 @ref FL_GPTIM_InitTypeDef 结构体初始化为默认配置
  * @param  TIM_InitStruct 指向 @ref FL_GPTIM_InitTypeDef 结构体的指针
  *
  * @retval None
  */
void FL_GPTIM_StructInit(FL_GPTIM_InitTypeDef *TIM_InitStruct)
{
    /* Set the default configuration */
    TIM_InitStruct->prescaler         = (uint16_t)0x0000;
    TIM_InitStruct->autoReloadState   = FL_DISABLE;
    TIM_InitStruct->counterMode       = FL_GPTIM_COUNTER_DIR_UP;
    TIM_InitStruct->autoReload        = 0xFFFFU;
    TIM_InitStruct->clockDivision     = FL_GPTIM_CLK_DIVISION_DIV1;
}

/**
  * @brief  配置GPTIM基本定时器外部时钟源模式，包括编码器模式.
  * @param  TIMx 外设入口地址
  * @param  slave_init 指向 @ref FL_GPTIM_SlaveInitTypeDef 结构体的指针
  * @retval 错误状态，可能值：
  *         -FL_PASS 配置成功
  *         -FL_FAIL 配置过程发生错误
  */
FL_ErrorStatus FL_GPTIM_SlaveMode_Init(GPTIM_Type *TIMx, FL_GPTIM_SlaveInitTypeDef *slave_init)
{
    /* 参数检查 */
    assert_param(IS_GPTIM_INSTANCE(TIMx));
    assert_param(IS_FL_GPTIM_SLAVE_MODE(slave_init->slaveMode));
    assert_param(IS_FL_GPTIM_TRIGGER_SRC(slave_init->triggerSrc));
    assert_param(IS_FL_GPTIM_TRIGGER_DELAY(slave_init->triggerDelay));
    /* 时钟总线使能配置 */
    if(TIMx == GPTIM0)
    {
        FL_RCC_EnableGroup4BusClock(FL_RCC_GROUP4_BUSCLK_GPTIM0);
    }
    else
        if(TIMx == GPTIM1)
        {
            FL_RCC_EnableGroup4BusClock(FL_RCC_GROUP4_BUSCLK_GPTIM1);
        }
    /* 触发延迟默认关闭 */
    FL_GPTIM_DisableMasterSlaveMode(TIMx);
    /* 关闭从模式以能写入TS */
    FL_GPTIM_SetSlaveMode(TIMx, 0);
    /* 从模式输入源选择 */
    FL_GPTIM_SetTriggerInput(TIMx, slave_init->triggerSrc);
    /* ITRx 输入源选择 */
    if(slave_init->triggerSrc <= FL_GPTIM_TIM_TS_ITR3)
    {
        /* 内部触发ITRx源选择 */
        FL_GPTIM_SetITRInput(TIMx, (1U << (slave_init->triggerSrc >> GPTIM_SMCR_TS_Pos)), slave_init->ITRSourceGroup);
    }
    /* 从模式选择 */
    FL_GPTIM_SetSlaveMode(TIMx, slave_init->slaveMode);
    /* 触发延迟默认关闭 */
    if(slave_init->triggerDelay == FL_ENABLE)
    {
        FL_GPTIM_EnableMasterSlaveMode(TIMx);
    }
    return FL_PASS;
}

/**
  * @brief  将 @ref FL_GPTIM_SlaveInitTypeDef 结构体初始化为默认配置
  * @param  slave_init 指向 @ref FL_GPTIM_SlaveInitTypeDef 结构体的指针
  *
  * @retval None
  */
void FL_GPTIM_SlaveMode_StructInit(FL_GPTIM_SlaveInitTypeDef *slave_init)
{
    slave_init->ITRSourceGroup  = 0;
    slave_init->slaveMode       = FL_GPTIM_SLAVE_MODE_PROHIBITED;
    slave_init->triggerSrc      = FL_GPTIM_TIM_TS_TI1FP1;
    slave_init->triggerDelay    = FL_DISABLE;
}

/**
  * @brief  配置GPTIM触发输入捕获通道ETR.
  * @param  TIMx 外设入口地址
  * @param  etr_init 指向 @ref FL_GPTIM_ETR_InitTypeDef 结构体的指针
  * @retval 错误状态，可能值：
  *         -FL_PASS 配置成功
  *         -FL_FAIL 配置过程发生错误
  */
FL_ErrorStatus  FL_GPTIM_ETR_Init(GPTIM_Type *TIMx, FL_GPTIM_ETR_InitTypeDef *etr_init)
{
    assert_param(IS_FL_GPTIM_ETR_FILTER(etr_init->ETRFilter));
    assert_param(IS_FL_GPTIM_ETR_PSC(etr_init->ETRClockDivision));
    assert_param(IS_FL_GPTIM_ETR_POLARITY(etr_init->ETRPolarity));
    /* 时钟总线使能配置 */
    if(TIMx == GPTIM0)
    {
        FL_RCC_EnableGroup4BusClock(FL_RCC_GROUP4_BUSCLK_GPTIM0);
    }
    else
        if(TIMx == GPTIM1)
        {
            FL_RCC_EnableGroup4BusClock(FL_RCC_GROUP4_BUSCLK_GPTIM1);
        }
    /* 外部时钟极性 */
    FL_GPTIM_SetETRPolarity(TIMx, etr_init->ETRPolarity);
    /* 外部时钟滤波 */
    FL_GPTIM_SetETRFilter(TIMx, etr_init->ETRFilter);
    /* 外部时钟分频 */
    FL_GPTIM_SetETRPrescaler(TIMx, etr_init->ETRClockDivision);
    if(etr_init->useExternalTrigger == FL_ENABLE)
    {
        FL_GPTIM_EnableExternalClock(TIMx);
    }
    else
    {
        FL_GPTIM_DisableExternalClock(TIMx);
    }
    return FL_PASS;
}

/**
  * @brief  将 @ref FL_GPTIM_ETR_InitTypeDef 结构体初始化为默认配置
  * @param  etr_init 指向 @ref FL_GPTIM_ETR_InitTypeDef 结构体的指针
  *
  * @retval None
  */
void FL_GPTIM_ETR_StructInit(FL_GPTIM_ETR_InitTypeDef *etr_init)
{
    etr_init->useExternalTrigger  = FL_DISABLE;
    etr_init->ETRFilter           = FL_GPTIM_ETR_FILTER_DIV1;
    etr_init->ETRPolarity         = FL_GPTIM_ETR_POLARITY_NORMAL;
    etr_init->ETRClockDivision    = FL_GPTIM_ETR_PSC_DIV1;
}

/**
  * @brief  配置GPTIM的比较输出通道.
  * @param  TIMx 外设入口地址
  * @param  channel GPTIM通道
  *         此参数可取以下值：
  *         @arg @ref FL_GPTIM_CHANNEL_1
  *         @arg @ref FL_GPTIM_CHANNEL_2
  *         @arg @ref FL_GPTIM_CHANNEL_3
  *         @arg @ref FL_GPTIM_CHANNEL_4
  * @param  oc_init 指向 @ref FL_GPTIM_OC_InitTypeDef 结构体的指针
  * @retval 错误状态，可能值：
  *         -FL_PASS 配置成功
  *         -FL_FAIL 配置过程发生错误
  */
FL_ErrorStatus FL_GPTIM_OC_Init(GPTIM_Type *TIMx, uint32_t channel, FL_GPTIM_OC_InitTypeDef *oc_init)
{
    FL_ErrorStatus result = FL_PASS;
    /* 参数检查 */
    assert_param(IS_GPTIM_INSTANCE(TIMx));
    assert_param(IS_FL_GPTIM_OC_MODE(oc_init->OCMode));
    assert_param(IS_FL_GPTIM_OC_PRELOAD(oc_init->OCPreload));
    assert_param(IS_FL_GPTIM_OC_POLARITY(oc_init->OCPolarity));
    assert_param(IS_FL_GPTIM_OC_FASTMODE(oc_init->OCFastMode));
    assert_param(IS_FL_GPTIM_OC_ETR_CLEARN(oc_init->OCETRFStatus));
    /* 通道关闭 */
    FL_GPTIM_OC_DisableChannel(TIMx, channel);
    /* 通道极性 */
    FL_GPTIM_OC_SetChannelPolarity(TIMx, oc_init->OCPolarity, channel);
    /* 捕获映射到输出通道 */
    FL_GPTIM_CC_SetChannelMode(TIMx, FL_GPTIM_CHANNEL_MODE_OUTPUT, channel);
    /* 输出比较模式寄存器配置 */
    OCConfig(TIMx, channel, oc_init);
    /* 通道使能 */
    FL_GPTIM_OC_EnableChannel(TIMx, channel);
    return result;
}

/**
  * @brief  配置输出通道
  * @param  TIMx 外设入口地址
  * @param  channel GPTIM通道
  *         此参数可取以下值：
  *         @arg @ref FL_GPTIM_CHANNEL_1
  *         @arg @ref FL_GPTIM_CHANNEL_2
  *         @arg @ref FL_GPTIM_CHANNEL_3
  *         @arg @ref FL_GPTIM_CHANNEL_4
  * @param  oc_init 指向 @ref FL_GPTIM_OC_InitTypeDef 结构体的指针.
  * @retval 错误状态，可能值：
  *         -FL_PASS 配置成功
  *         -FL_FAIL 配置过程发生错误
  */
static FL_ErrorStatus OCConfig(GPTIM_Type *TIMx, uint32_t channel, FL_GPTIM_OC_InitTypeDef *oc_init)
{
    FL_ErrorStatus result = FL_PASS;
    /* 配置比较输出通道模式 */
    FL_GPTIM_OC_SetMode(TIMx, oc_init->OCMode, channel);
    /* 配置ETRF清零使能 */
    if(oc_init->OCETRFStatus == FL_ENABLE)
    {
        FL_GPTIM_OC_EnableClear(TIMx, channel);
    }
    /* 比较输出通道快速模式 */
    if(oc_init->OCFastMode == FL_ENABLE)
    {
        FL_GPTIM_OC_EnableFastMode(TIMx, channel);
    }
    /* 比较输出通道缓冲模式 */
    if(oc_init->OCPreload == FL_ENABLE)
    {
        FL_GPTIM_OC_EnablePreload(TIMx, channel);
    }
    /* 设置比较值 */
    switch(channel)
    {
        case FL_GPTIM_CHANNEL_1:
            FL_GPTIM_WriteCompareCH1(TIMx, oc_init->compareValue);
            break;
        case FL_GPTIM_CHANNEL_2:
            FL_GPTIM_WriteCompareCH2(TIMx, oc_init->compareValue);
            break;
        case FL_GPTIM_CHANNEL_3:
            FL_GPTIM_WriteCompareCH3(TIMx, oc_init->compareValue);
            break;
        case FL_GPTIM_CHANNEL_4:
            FL_GPTIM_WriteCompareCH4(TIMx, oc_init->compareValue);
            break;
        default :
            result = FL_FAIL;
            break;
    }
    return result;
}

/**
  * @brief  将 @ref FL_GPTIM_OC_InitTypeDef 结构体初始化为默认配置
  * @param  oc_init 指向 @ref FL_GPTIM_OC_InitTypeDef 结构体的指针
  *
  * @retval None
  */
void FL_GPTIM_OC_StructInit(FL_GPTIM_OC_InitTypeDef *oc_init)
{
    /* Set the default configuration */
    oc_init->OCMode       = FL_GPTIM_OC_MODE_FROZEN;
    oc_init->OCETRFStatus = FL_DISABLE;
    oc_init->OCFastMode   = FL_DISABLE;
    oc_init->compareValue = 0x00000000U;
    oc_init->OCPolarity   = FL_GPTIM_OC_POLARITY_NORMAL;
    oc_init->OCPreload    = FL_DISABLE;
}

/**
  * @brief  配置GPTIM的输入捕获通道.
  * @param  TIMx 外设入口地址
  * @param  channel GPTIM通道
  *         此参数可取以下值：
  *         @arg @ref FL_GPTIM_CHANNEL_1
  *         @arg @ref FL_GPTIM_CHANNEL_2
  *         @arg @ref FL_GPTIM_CHANNEL_3
  *         @arg @ref FL_GPTIM_CHANNEL_4
  * @param  ic_init 指向 @ref FL_GPTIM_IC_InitTypeDef 结构体的指针
  * @retval ErrorStatus枚举值
  *         -FL_FAIL 配置过程发生错误
  *         -FL_PASS 成功
  */
FL_ErrorStatus FL_GPTIM_IC_Init(GPTIM_Type *TIMx, uint32_t channel, FL_GPTIM_IC_InitTypeDef *ic_init)
{
    FL_ErrorStatus result = FL_PASS;
    /* 参数检查 */
    assert_param(IS_FL_GPTIM_CHANNEL(channel));
    assert_param(IS_FL_GPTIM_IC_CAPTURE_STATE(ic_init->captureState));
    assert_param(IS_FL_GPTIM_IC_POLARITY(ic_init->ICPolarity));
    assert_param(IS_FL_GPTIM_CHANNEL_MODE(ic_init->ICActiveInput));
    assert_param(IS_FL_GPTIM_IC_PSC(ic_init->ICPrescaler));
    assert_param(IS_FL_GPTIM_IC_FILTER(ic_init->ICFilter));
    /* 时钟总线使能配置 */
    if(TIMx == GPTIM0)
    {
        FL_RCC_EnableGroup4BusClock(FL_RCC_GROUP4_BUSCLK_GPTIM0);
    }
    else
        if(TIMx == GPTIM1)
        {
            FL_RCC_EnableGroup4BusClock(FL_RCC_GROUP4_BUSCLK_GPTIM1);
        }
    /* 通道关闭 */
    FL_GPTIM_IC_DisableChannel(TIMx, channel);
    /*捕获极性 */
    FL_GPTIM_IC_SetChannelPolarity(TIMx, ic_init->ICPolarity, channel);
    /* 捕获映射通道 */
    FL_GPTIM_CC_SetChannelMode(TIMx, ic_init->ICActiveInput, channel);
    /* 捕获预分频 */
    FL_GPTIM_IC_SetPrescaler(TIMx, ic_init->ICPrescaler, channel);
    /* 捕获滤波器 */
    FL_GPTIM_IC_SetFilter(TIMx, ic_init->ICFilter, channel);
    if(ic_init->captureState == FL_ENABLE)
    {
        FL_GPTIM_IC_EnableChannel(TIMx, channel);
    }
    return result;
}

/**
  * @brief  将 @ref FL_GPTIM_IC_InitTypeDef 结构体初始化为默认配置
  * @param  ic_init 指向 @ref FL_GPTIM_IC_InitTypeDef 结构体的指针
  *
  * @retval None
  */
void FL_GPTIM_IC_StructInit(FL_GPTIM_IC_InitTypeDef *ic_init)
{
    /* Set the default configuration */
    ic_init->ICPolarity    = FL_GPTIM_IC_POLARITY_NORMAL;
    ic_init->ICActiveInput = FL_GPTIM_CHANNEL_MODE_INPUT_NORMAL;
    ic_init->ICPrescaler   = FL_GPTIM_IC_PSC_DIV1;
    ic_init->ICFilter      = FL_GPTIM_IC_FILTER_DIV1;
    ic_init->captureState  = FL_DISABLE;
}

/**
  * @}
  */

#endif /* FL_GPTIM_DRIVER_ENABLED */

/**
  * @}
  */

/**
  * @}
  */
/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
