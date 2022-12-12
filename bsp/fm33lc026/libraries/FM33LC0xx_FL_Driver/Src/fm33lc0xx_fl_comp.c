/**
  ****************************************************************************************************
  * @file    fm33lc0xx_fl_comp.c
  * @author  FMSH Application Team
  * @brief   Src file of COMP FL Module
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

/** @addtogroup COMP
  * @{
  */

#ifdef FL_COMP_DRIVER_ENABLED

/* Private macros ------------------------------------------------------------*/
/** @addtogroup COMP_FL_Private_Macros
  * @{
  */

#define         IS_COMP_ALL_INSTANCE(INTENCE)              (((INTENCE) == COMP1)||\
                                                            ((INTENCE) == COMP2))

#define         IS_FL_COMP_POSITIVEINPUT(__VALUE__)        (((__VALUE__) == FL_COMP_INP_SOURCE_INP1)||\
                                                            ((__VALUE__) == FL_COMP_INP_SOURCE_INP2)||\
                                                            ((__VALUE__) == FL_COMP_INP_SOURCE_INP3))

#define         IS_FL_COMP_NEGATIVEINPUT(__VALUE__)        (((__VALUE__) == FL_COMP_INN_SOURCE_INN1)||\
                                                             ((__VALUE__) == FL_COMP_INN_SOURCE_INN2)||\
                                                             ((__VALUE__) == FL_COMP_INN_SOURCE_VREF)||\
                                                             ((__VALUE__) == FL_COMP_INN_SOURCE_VREF_DIV_2))

#define         IS_FL_COMP_POLARITY(__VALUE__)             (((__VALUE__) == FL_COMP_OUTPUT_POLARITY_NORMAL)||\
                                                             ((__VALUE__) == FL_COMP_OUTPUT_POLARITY_INVERT))

#define         IS_FL_COMP_EDGE(__VALUE__)                 (((__VALUE__) == FL_COMP_INTERRUPT_EDGE_BOTH)||\
                                                            ((__VALUE__) == FL_COMP_INTERRUPT_EDGE_RISING )||\
                                                            ((__VALUE__) == FL_COMP_INTERRUPT_EDGE_FALLING))

#define         IS_FL_COMP_DIGITAL_FILTER(__VALUE__)       (((__VALUE__) == FL_DISABLE)||\
                                                            ((__VALUE__) == FL_ENABLE))

/**
  * @}
  */

/** @addtogroup COMP_FL_EF_Init
  * @{
  */

/**
  * @brief  复位COMP外设
  * @param  COMPx 外设入口地址
  * @retval 错误状态，可能值：
  *         -FL_PASS 外设寄存器值恢复复位值
  *         -FL_FAIL 未成功执行
  */
FL_ErrorStatus FL_COMP_DeInit(COMP_Type *COMPx)
{
    /* 入口参数检查 */
    assert_param(IS_COMP_ALL_INSTANCE(COMPx));
    /* 恢复寄存器值为默认值 */
    COMPx->CR = 0x00000000U;
    /* 关闭外设总线时钟和工作时钟 */
    FL_RCC_DisableGroup1BusClock(FL_RCC_GROUP1_BUSCLK_ANAC);
    /* 锁定外设复位 */
    FL_RCC_DisablePeripheralReset();
    return FL_PASS;
}

/**
  * @brief  根据 COMP_InitStruct 的配置信息初始化对应外设.
  * @param  COMPx 外设入口地址
  * @param  initStruct 指向 @ref FL_COMP_InitTypeDef 结构体的指针
  * @retval 错误状态，可能值：
  *         -FL_PASS 配置成功
  *         -FL_FAIL 配置过程发生错误
  */
FL_ErrorStatus FL_COMP_Init(COMP_Type *COMPx, FL_COMP_InitTypeDef *initStruct)
{
    /* 入口参数检查 */
    assert_param(IS_COMP_ALL_INSTANCE(COMPx));
    assert_param(IS_FL_COMP_EDGE(initStruct->edge));
    assert_param(IS_FL_COMP_POLARITY(initStruct->polarity));
    assert_param(IS_FL_COMP_POSITIVEINPUT(initStruct->positiveInput));
    assert_param(IS_FL_COMP_NEGATIVEINPUT(initStruct->negativeInput));
    assert_param(IS_FL_COMP_DIGITAL_FILTER(initStruct->digitalFilter));
    /* 使能时钟总线 */
    FL_RCC_EnableGroup1BusClock(FL_RCC_GROUP1_BUSCLK_ANAC);
    /* 比较器输出极性选择 */
    FL_COMP_SetOutputPolarity(COMPx, initStruct->polarity);
    /* 比较器正向输入选择 */
    FL_COMP_SetINPSource(COMPx, initStruct->positiveInput);
    /* 比较器反向输入选择 */
    FL_COMP_SetINNSource(COMPx, initStruct->negativeInput);
    /* 比较器使用vref 打开vref_buf */
    if((initStruct->negativeInput == FL_COMP_INN_SOURCE_VREF) || (initStruct->negativeInput == FL_COMP_INN_SOURCE_VREF_DIV_2))
    {
        FL_OPA_EnableVrefBuffer(OPA1);  /* 使能 */
        FL_OPA_DisableBypassVrefBuffer(OPA1);   /* 不bypass */
    }
    if(COMPx == COMP1)
    {
        /* 比较器中断边沿选择 */
        FL_COMP_SetComparator1InterruptEdge(COMP, initStruct->edge);
    }
    else
    {
        /* 比较器中断边沿选择 */
        FL_COMP_SetComparator2InterruptEdge(COMP, initStruct->edge);
    }
    /* 滤波 */
    if(initStruct->digitalFilter)
    {
        if(COMPx == COMP1)
        { FL_COMP_EnableComparator1OutputFilter(COMP); }
        else
        { FL_COMP_EnableComparator2OutputFilter(COMP); }
    }
    else
    {
        if(COMPx == COMP1)
        { FL_COMP_DisableComparator1OutputFilter(COMP); }
        else
        { FL_COMP_DisableComparator2OutputFilter(COMP); }
    }
    return FL_PASS;
}
/**
  * @brief  将 @ref FL_COMP_InitTypeDef 结构体初始化为默认配置
  * @param  initStruct 指向 @ref FL_COMP_InitTypeDef 结构体的指针
  *
  * @retval None
  */
void FL_COMP_StructInit(FL_COMP_InitTypeDef *initStruct)
{
    /* 复位配置信息 */
    initStruct->edge             = FL_COMP_INTERRUPT_EDGE_BOTH;
    initStruct->polarity         = FL_COMP_OUTPUT_POLARITY_NORMAL;
    initStruct->negativeInput    = FL_COMP_INN_SOURCE_INN1;
    initStruct->positiveInput    = FL_COMP_INP_SOURCE_INP1;
    initStruct->digitalFilter    = FL_ENABLE;
}


/**
  * @}
  */

#endif /* FL_COMP_DRIVER_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
