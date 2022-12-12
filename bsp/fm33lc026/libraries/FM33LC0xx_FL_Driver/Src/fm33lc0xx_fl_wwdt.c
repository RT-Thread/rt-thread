/**
  ****************************************************************************************************
  * @file    fm33lc0xx_fl_wwdt.c
  * @author  FMSH Application Team
  * @brief   Src file of WWDT FL Module
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

/** @addtogroup WWDT
  * @{
  */

#ifdef FL_WWDT_DRIVER_ENABLED

/* Private macros ------------------------------------------------------------*/
/** @addtogroup WWDT_FL_Private_Macros
  * @{
  */

#define         IS_WWDT_INSTANCE(INTANCE)                ((INTANCE) == WWDT)

#define         IS_FL_WWDT_OVERFLOWPERIOD(__VALUE__)            (((__VALUE__) == FL_WWDT_PERIOD_1CNT)||\
                                                                 ((__VALUE__) == FL_WWDT_PERIOD_4CNT)||\
                                                                 ((__VALUE__) == FL_WWDT_PERIOD_16CNT)||\
                                                                 ((__VALUE__) == FL_WWDT_PERIOD_64CNT)||\
                                                                 ((__VALUE__) == FL_WWDT_PERIOD_128CNT)||\
                                                                 ((__VALUE__) == FL_WWDT_PERIOD_256CNT)||\
                                                                 ((__VALUE__) == FL_WWDT_PERIOD_512CNT)||\
                                                                 ((__VALUE__) == FL_WWDT_PERIOD_1024CNT))
/**
  * @}
  */

/** @addtogroup WWDT_FL_EF_Init
  * @{
  */

/**
  * @brief  关闭WWDT外设总线时钟
  *
  * @param  WWDTx 外设入口地址
  *
  * @retval 错误状态，可能值：
  *         -FL_PASS 外设寄存器值恢复复位值
  *         -FL_FAIL 未成功执行
  */
FL_ErrorStatus FL_WWDT_DeInit(WWDT_Type *WWDTx)
{
    assert_param(IS_WWDT_INSTANCE(WWDTx));
    return FL_PASS;
}

/**
  * @brief  根据 WWDT_InitStruct初始化对应外设入口地址的寄存器值.
  *
  * @note   WWTD使能后将无法关闭，直到下一次芯片复位
  *
  * @param  WWDTx 外设入口地址
  *
  * @param  WWDT_InitStruct 指向 @ref FL_WWDT_InitTypeDef 结构体的指针
  *
  * @retval 错误状态，可能值：
  *         -FL_PASS 配置成功
  *         -FL_FAIL 配置过程发生错误
  */
FL_ErrorStatus FL_WWDT_Init(WWDT_Type *WWDTx, FL_WWDT_InitTypeDef *WWDT_InitStruct)
{
    FL_ErrorStatus status = FL_PASS;
    /* 入口参数检查 */
    assert_param(IS_WWDT_INSTANCE(WWDTx));
    assert_param(IS_FL_WWDT_OVERFLOWPERIOD(WWDT_InitStruct->overflowPeriod));
    /* 开启总线时钟 */
    FL_RCC_EnableGroup2BusClock(FL_RCC_GROUP2_BUSCLK_WWDT);
    /* 配置独立看门狗溢出周期 */
    FL_WWDT_SetPeriod(WWDTx, WWDT_InitStruct->overflowPeriod);
    /* 启动看门狗 */
    FL_WWDT_Enable(WWDTx);
    return status;
}

/**
  * @brief  设置 WWDT_InitStruct 为默认配置
  *
  * @param  WWDT_InitStruct 指向 @ref FL_WWDT_InitTypeDef 结构体的指针
  *
  * @retval None
  */
void FL_WWDT_StructInit(FL_WWDT_InitTypeDef *WWDT_InitStruct)
{
    /* 默认最长溢出周期 */
    WWDT_InitStruct->overflowPeriod = FL_WWDT_PERIOD_1024CNT;
}

/**
  * @}
  */

#endif /* FL_WWDT_DRIVER_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
