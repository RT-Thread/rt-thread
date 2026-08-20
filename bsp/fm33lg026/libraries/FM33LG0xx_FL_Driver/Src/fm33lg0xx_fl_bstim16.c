/**
  *******************************************************************************************************
  * @file    fm33lg0xx_fl_bstim16.c
  * @author  FMSH Application Team
  * @brief   Src file of BSTIM FL Module
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
#include "fm33lg0xx_fl.h"

/** @addtogroup FM33LG0XX_FL_Driver
  * @{
  */

/** @addtogroup BSTIM16
  * @{
  */

#ifdef FL_BSTIM16_DRIVER_ENABLED

/* Private macros ------------------------------------------------------------*/
/** @addtogroup BSTIM16_FL_Private_Macros
  * @{
  */
#define         IS_FL_BSTIM16_INSTANCE(INTANCE)                     ((INTANCE) == BSTIM16)

#define         IS_FL_BSTIM16_PSC(__VALUE__)                        ((__VALUE__) <= 0x0000FFFF)

#define         IS_FL_BSTIM16_AUTORELOAD(__VALUE__)                 ((__VALUE__) <= 0x0000FFFF)


#define         IS_FL_BSTIM16_AUTORELOAD_MODE(__VALUE__)           (((__VALUE__) == FL_ENABLE)||\
                                                                    ((__VALUE__) == FL_DISABLE))

#define         IS_FL_BSTIM16_CLOCK_SRC(__VALUE__)                 (((__VALUE__) == FL_CMU_BSTIM16_CLK_SOURCE_APBCLK)||\
                                                                    ((__VALUE__) == FL_CMU_BSTIM16_CLK_SOURCE_RCLP)||\
                                                                    ((__VALUE__) == FL_CMU_BSTIM16_CLK_SOURCE_RCLF)||\
                                                                    ((__VALUE__) == FL_CMU_BSTIM16_CLK_SOURCE_LSCLK))

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup BSTIM16_FL_EF_Init
  * @{
  */

/**
  * @brief  复位对应BSTIM16寄存器.
  * @param  BSTIMx
  * @retval ErrorStatus枚举值:
  *         -FL_PASS 外设寄存器值恢复复位值
  *         -FL_FAIL 未成功执行
  */
FL_ErrorStatus FL_BSTIM16_DeInit(BSTIM16_Type *BSTIM16x)
{
    assert_param(IS_FL_BSTIM16_INSTANCE(BSTIM16x));
    /* 使能外设复位 */
    FL_RMU_EnablePeripheralReset(RMU);
    /* 复位IIC外设寄存器 */
    FL_RMU_EnableResetAPBPeripheral(RMU, FL_RMU_RSTAPB_BSTIM16);
    FL_RMU_DisableResetAPBPeripheral(RMU, FL_RMU_RSTAPB_BSTIM16);
    /* 关闭外设总线始时钟和工作时钟 */
    FL_CMU_DisableGroup4BusClock(FL_CMU_GROUP4_BUSCLK_BSTIM16);
    FL_CMU_DisableGroup3OperationClock(FL_CMU_GROUP3_OPCLK_BSTIM16);
    /* 锁定外设复位 */
    FL_RMU_DisablePeripheralReset(RMU);
    return FL_PASS;
}
/**
  * @brief  根据 BSTIM16_InitStruct 的配置信息初始化对应外设入口地址的寄存器值.
  * @param  BSTIMx BSTIMx
  * @param  BSTIM16_InitStruct 指向一个 @ref FL_BSTIM16_InitTypeDef 结构体
  *         其中包含了外设的相关配置信息.
  * @retval ErrorStatus枚举值
  *         -FL_FAIL 配置过程发生错误
  *         -FL_PASS 配置成功
  */
FL_ErrorStatus FL_BSTIM16_Init(BSTIM16_Type *BSTIM16x, FL_BSTIM16_InitTypeDef *init)
{
    uint32_t i = 5;
    /* 参数检查 */
    assert_param(IS_FL_BSTIM16_INSTANCE(BSTIM16x));
    assert_param(IS_FL_BSTIM16_CLOCK_SRC(init->clockSource));
    assert_param(IS_FL_BSTIM16_PSC(init->prescaler));
    assert_param(IS_FL_BSTIM16_AUTORELOAD(init->autoReload));
    assert_param(IS_FL_BSTIM16_AUTORELOAD_MODE(init->autoReloadState));
    /* 时钟使能 */
    FL_CMU_EnableGroup4BusClock(FL_CMU_GROUP4_BUSCLK_BSTIM16);
    /* 选择时钟源 */
    FL_CMU_SetBSTIM16ClockSource(init->clockSource);
    FL_CMU_EnableGroup3OperationClock(FL_CMU_GROUP3_OPCLK_BSTIM16);
    /* 分频系数 */
    FL_BSTIM16_WritePrescaler(BSTIM16x, init->prescaler);
    /* 自动重装载值 */
    FL_BSTIM16_EnableUpdateEvent(BSTIM16x);
    FL_BSTIM16_WriteAutoReload(BSTIM16x, init->autoReload);
    if(init->autoReloadState == FL_ENABLE)
    {
        FL_BSTIM16_EnableARRPreload(BSTIM16x);
    }
    else
    {
        FL_BSTIM16_DisableARRPreload(BSTIM16x);
    }
    FL_BSTIM16_GenerateUpdateEvent(BSTIM16x);
    while((!FL_BSTIM16_IsActiveFlag_Update(BSTIM16x)) && i)
    {
        i--;
    }
    return FL_PASS;
}
/**
  * @brief  设置 BSTIM16_InitStruct 为默认配置
  * @param  BSTIM16_InitStruct 指向需要将值设置为默认配置的结构体 @ref FL_BSTIM16_InitTypeDef 结构体
  *
  * @retval None
  */

void FL_BSTIM16_StructInit(FL_BSTIM16_InitTypeDef *init)
{
    init->prescaler         = 0;
    init->autoReload        = 0xFFFFFFFF;
    init->autoReloadState   = FL_ENABLE;
    init->clockSource       = FL_CMU_BSTIM16_CLK_SOURCE_APBCLK;
}

/**
  * @}
  */

#endif /* FL_BSTIM16_DRIVER_ENABLED */

/**
  * @}
  */

/**
  * @}
  */


/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
