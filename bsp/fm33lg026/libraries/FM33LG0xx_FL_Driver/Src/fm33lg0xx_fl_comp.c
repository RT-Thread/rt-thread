/**
  ****************************************************************************************************
  * @file    fm33lg0xx_fl_comp.c
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
#include "fm33lg0xx_fl.h"


/** @addtogroup FM33LG0XX_FL_Driver
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
                                                            ((INTENCE) == COMP2)||\
                                                            ((INTENCE) == COMP3))

#define         IS_FL_COMP_POSITIVEINPUT(__VALUE__)        (((__VALUE__) == FL_COMP_INP_SOURCE_INP1)||\
                                                            ((__VALUE__) == FL_COMP_INP_SOURCE_INP2)||\
                                                            ((__VALUE__) == FL_COMP_INP_SOURCE_AVREF)||\
                                                            ((__VALUE__) == FL_COMP_INP_SOURCE_ULPBG_REF)||\
                                                            ((__VALUE__) == FL_COMP_INP_SOURCE_VDD15)||\
                                                            ((__VALUE__) == FL_COMP_INP_SOURCE_VREFP))

#define         IS_FL_COMP_NEGATIVEINPUT(__VALUE__)        (((__VALUE__) == FL_COMP_INN_SOURCE_INN1)||\
                                                             ((__VALUE__) == FL_COMP_INN_SOURCE_INN2)||\
                                                             ((__VALUE__) == FL_COMP_INN_SOURCE_VREF)||\
                                                             ((__VALUE__) == FL_COMP_INN_SOURCE_VREF_DIV_2)||\
                                                             ((__VALUE__) == FL_COMP_INN_SOURCE_VREFP)||\
                                                             ((__VALUE__) == FL_COMP_INN_SOURCE_DAC))

#define         IS_FL_COMP_POLARITY(__VALUE__)             (((__VALUE__) == FL_COMP_OUTPUT_POLARITY_NORMAL)||\
                                                             ((__VALUE__) == FL_COMP_OUTPUT_POLARITY_INVERT))

#define         IS_FL_COMP_EDGE(__VALUE__)                 (((__VALUE__) == FL_COMP_INTERRUPT_EDGE_BOTH)||\
                                                            ((__VALUE__) == FL_COMP_INTERRUPT_EDGE_RISING )||\
                                                            ((__VALUE__) == FL_COMP_INTERRUPT_EDGE_FALLING))

#define         IS_FL_COMP_DIGITAL_FILTER(__VALUE__)       (((__VALUE__) == FL_DISABLE)||\
                                                            ((__VALUE__) == FL_ENABLE))

#define         IS_FL_COMP_DIGITAL_FILTER_LEN(__VALUE__)    (((__VALUE__) == FL_COMP_OUTPUT_FILTER_WINDOW_3APBCLK)||\
                                                            ((__VALUE__) == FL_COMP_OUTPUT_FILTER_WINDOW_4APBCLK )||\
                                                            ((__VALUE__) == FL_COMP_OUTPUT_FILTER_WINDOW_5APBCLK )||\
                                                            ((__VALUE__) == FL_COMP_OUTPUT_FILTER_WINDOW_6APBCLK )||\
                                                            ((__VALUE__) == FL_COMP_OUTPUT_FILTER_WINDOW_7APBCLK )||\
                                                            ((__VALUE__) == FL_COMP_OUTPUT_FILTER_WINDOW_8APBCLK )||\
                                                            ((__VALUE__) == FL_COMP_OUTPUT_FILTER_WINDOW_9APBCLK )||\
                                                            ((__VALUE__) == FL_COMP_OUTPUT_FILTER_WINDOW_10APBCLK )||\
                                                            ((__VALUE__) == FL_COMP_OUTPUT_FILTER_WINDOW_11APBCLK )||\
                                                            ((__VALUE__) == FL_COMP_OUTPUT_FILTER_WINDOW_12APBCLK )||\
                                                            ((__VALUE__) == FL_COMP_OUTPUT_FILTER_WINDOW_13APBCLK )||\
                                                            ((__VALUE__) == FL_COMP_OUTPUT_FILTER_WINDOW_14APBCLK )||\
                                                            ((__VALUE__) == FL_COMP_OUTPUT_FILTER_WINDOW_15APBCLK )||\
                                                            ((__VALUE__) == FL_COMP_OUTPUT_FILTER_WINDOW_16APBCLK )||\
                                                            ((__VALUE__) == FL_COMP_OUTPUT_FILTER_WINDOW_17APBCLK )||\
                                                            ((__VALUE__) == FL_COMP_OUTPUT_FILTER_WINDOW_18APBCLK )||\
                                                            ((__VALUE__) == FL_COMP_OUTPUT_FILTER_WINDOW_19APBCLK )||\
                                                            ((__VALUE__) == FL_COMP_OUTPUT_FILTER_WINDOW_20APBCLK )||\
                                                            ((__VALUE__) == FL_COMP_OUTPUT_FILTER_WINDOW_21APBCLK )||\
                                                            ((__VALUE__) == FL_COMP_OUTPUT_FILTER_WINDOW_22APBCLK )||\
                                                            ((__VALUE__) == FL_COMP_OUTPUT_FILTER_WINDOW_23APBCLK )||\
                                                            ((__VALUE__) == FL_COMP_OUTPUT_FILTER_WINDOW_24APBCLK )||\
                                                            ((__VALUE__) == FL_COMP_OUTPUT_FILTER_WINDOW_25APBCLK )||\
                                                            ((__VALUE__) == FL_COMP_OUTPUT_FILTER_WINDOW_26APBCLK )||\
                                                            ((__VALUE__) == FL_COMP_OUTPUT_FILTER_WINDOW_27APBCLK )||\
                                                            ((__VALUE__) == FL_COMP_OUTPUT_FILTER_WINDOW_28APBCLK )||\
                                                            ((__VALUE__) == FL_COMP_OUTPUT_FILTER_WINDOW_29APBCLK )||\
                                                            ((__VALUE__) == FL_COMP_OUTPUT_FILTER_WINDOW_30APBCLK )||\
                                                            ((__VALUE__) == FL_COMP_OUTPUT_FILTER_WINDOW_31APBCLK )||\
                                                            ((__VALUE__) == FL_COMP_OUTPUT_FILTER_WINDOW_32APBCLK))
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup COMP_FL_EF_Init
  * @{
  */

/**
  * @brief  复位对应COMP控制寄存器.
  * @param  COMPx COMP Port
  * @retval ErrorStatus枚举值:
  *           -FL_PASS 外设寄存器值恢复复位值
  *           -FL_FAIL 未成功执行
  */
FL_ErrorStatus FL_COMP_DeInit(COMP_Type *COMPx)
{
    /* 入口参数检查 */
    assert_param(IS_COMP_ALL_INSTANCE(COMPx));
    /* 恢复寄存器值为默认值 */
    COMPx->CR = 0x00000000U;
    return FL_PASS;
}

/**
  * @brief  根据 COMP_InitStruct的配置信息初始化对应外设.
  * @param  COMPx COMP Port
  * @param  initStruct 指向一个 @ref FL_COMP_InitTypeDef 结构体
  *         其中包含了外设的相关配置信息.
  * @param  Serial 比较器序号可取值：
  *         1 配置比较器1
  *         2 配置比较器2
  * @retval ErrorStatus枚举值
  *            -FL_FAIL 配置过程发生错误
  *            -FL_PASS COMP配置成功
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
    assert_param(IS_FL_COMP_DIGITAL_FILTER_LEN(initStruct->digitalFilterLen));
    /* 使能时钟总线 */
    FL_CMU_EnableGroup1BusClock(FL_CMU_GROUP1_BUSCLK_COMP);
    /* 比较器输出极性选择 */
    FL_COMP_SetOutputPolarity(COMPx, initStruct->polarity);
    /* 比较器正向输入选择 */
    FL_COMP_SetINPSource(COMPx, initStruct->positiveInput);
    /* 比较器反向输入选择 */
    FL_COMP_SetINNSource(COMPx, initStruct->negativeInput);
    /* 比较器使用1/2(internal reference) 打开buffer */
    if(initStruct->negativeInput == FL_COMP_INN_SOURCE_VREF_DIV_2)
    {
        FL_COMP_EnableBuffer(COMP);  /* buffer使能 */
        FL_COMP_DisableBufferBypass(COMP);   /* 不bypass buffer */
    }
    /* 比较器数字滤波 */
    if(COMPx == COMP1)
    {
        /* 比较器中断边沿选择 */
        FL_COMP_SetComparator1InterruptEdge(COMP, ((initStruct->edge) << COMP_ICR_CMP1SEL_Pos));
    }
    else
        if(COMPx == COMP2)
        {
            /* 比较器中断边沿选择 */
            FL_COMP_SetComparator2InterruptEdge(COMP, ((initStruct->edge) << COMP_ICR_CMP2SEL_Pos));
        }
        else
        {
            /* 比较器中断边沿选择 */
            FL_COMP_SetComparator3InterruptEdge(COMP, ((initStruct->edge) << COMP_ICR_CMP3SEL_Pos));
        }
    /* 滤波 */
    if(initStruct->digitalFilter)
    {
        FL_COMP_EnableOutputFilter(COMPx);
    }
    else
    {
        FL_COMP_DisableOutputFilter(COMPx);
    }
    /* 滤波长度 */
    FL_COMP_SetOutputFilterWindow(COMPx, initStruct->digitalFilterLen);
    return FL_PASS;
}
/**
  * @brief    设置 initStruct 为默认配置
  * @param     initStruct 指向需要将值设置为默认配置的结构体 @ref FL_COMP_InitTypeDef 结构体
  *
  * @retval    None
  */
void FL_COMP_StructInit(FL_COMP_InitTypeDef *initStruct)
{
    /* 复位配置信息 */
    initStruct->edge             = FL_COMP_INTERRUPT_EDGE_BOTH;
    initStruct->polarity         = FL_COMP_OUTPUT_POLARITY_NORMAL;
    initStruct->negativeInput    = FL_COMP_INN_SOURCE_INN1;
    initStruct->positiveInput    = FL_COMP_INP_SOURCE_INP1;
    initStruct->digitalFilter    = FL_ENABLE;
    initStruct->digitalFilterLen = FL_COMP_OUTPUT_FILTER_WINDOW_3APBCLK;
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
