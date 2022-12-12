/**
  *******************************************************************************************************
  * @file    fm33lc0xx_fl_opa.c
  * @author  FMSH Application Team
  * @brief   Src file of OPA FL Module
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

/** @addtogroup OPA
  * @{
  */

#ifdef FL_OPA_DRIVER_ENABLED

/* Private macros ------------------------------------------------------------*/
/** @addtogroup OPA_FL_Private_Macros
  * @{
  */

#define         IS_OPA_ALL_INSTANCE(INTENCE)               (((INTENCE) == OPA1)||\
                                                            ((INTENCE) == OPA2))

#define         IS_FL_OPA_INP_CHANNAL(__VALUE__)           (((__VALUE__) == FL_OPA_INP_SOURCE_INP1)||\
                                                            ((__VALUE__) == FL_OPA_INP_SOURCE_INP2))


#define         IS_FL_OPA_INN_CHANNAL(__VALUE__)           (((__VALUE__) == FL_OPA_INN_SOURCE_INN1)||\
                                                            ((__VALUE__) == FL_OPA_INN_SOURCE_INN2)||\
                                                            ((__VALUE__) == FL_OPA_INN_SOURCE_VREF)||\
                                                            ((__VALUE__) == FL_OPA_INN_SOURCE_THREE_QUARTERS_VREF)||\
                                                            ((__VALUE__) == FL_OPA_INN_SOURCE_HALF_VREF)||\
                                                            ((__VALUE__) == FL_OPA_INN_SOURCE_ONE_QUARTER_VREF)||\
                                                            ((__VALUE__) == FL_OPA_INN_SOURCE_ONE_EIGHTH_VREF))

#define         IS_FL_OPA_MODE(__VALUE__)                  (((__VALUE__) == FL_OPA_MODE_STANDALONE)||\
                                                            ((__VALUE__) == FL_OPA_MODE_COMPARATOR)||\
                                                            ((__VALUE__) == FL_OPA_MODE_PGA)||\
                                                            ((__VALUE__) == FL_OPA_MODE_BUFFER))

#define         IS_FL_OPA_DIGITALFILTER(__VALUE__)         (((__VALUE__) == FL_DISABLE)||\
                                                            ((__VALUE__) == FL_ENABLE))

#define         IS_FL_OPA_NEGTIVE_TO_PIN(__VALUE__)        (((__VALUE__) == FL_DISABLE)||\
                                                            ((__VALUE__) == FL_ENABLE))

#define         IS_FL_OPA_LOW_POWER_MODE(__VALUE__)        (((__VALUE__) == FL_DISABLE)||\
                                                            ((__VALUE__) == FL_ENABLE))

#define         IS_FL_OPA_GAIN(__VALUE__)                  (((__VALUE__) == FL_OPA_GAIN_X2)||\
                                                            ((__VALUE__) == FL_OPA_GAIN_X4)||\
                                                            ((__VALUE__) == FL_OPA_GAIN_X8)||\
                                                            ((__VALUE__) == FL_OPA_GAIN_X16))

/**
  * @}
  */

/** @addtogroup OPA_FL_EF_Init
  * @{
  */

/**
  * @brief  复位OPA
  * @param  OPAx 外设入口地址
  * @retval 错误状态，可能值：
  *         -FL_PASS 外设寄存器值恢复复位值
  *         -FL_FAIL 未成功执行
  */
FL_ErrorStatus FL_OPA_DeInit(OPA_Type *OPAx)
{
    /* 入口参数合法性断言 */
    assert_param(IS_OPA_ALL_INSTANCE(OPAx));
    /* 使能外设复位 */
    FL_RCC_EnablePeripheralReset();
    /* 复位外设寄存器 */
    FL_RCC_EnableResetAPB2Peripheral(FL_RCC_RSTAPB_OPA);
    FL_RCC_DisableResetAPB2Peripheral(FL_RCC_RSTAPB_OPA);
    /* 关闭外设总线时钟和工作时钟 */
    FL_RCC_DisableGroup1BusClock(FL_RCC_GROUP1_BUSCLK_ANAC);
    /* 锁定外设复位 */
    FL_RCC_DisablePeripheralReset();
    return FL_PASS;
}

/**
  * @brief  配置OPA
  *
  * @param  OPAx  外设入口地址
  * @param  initStruct 指向 @ref FL_OPA_InitTypeDef 结构体的指针
  *
  * @retval 错误状态，可能值：
  *         -FL_PASS 配置成功
  *         -FL_FAIL 配置过程发生错误
  */
FL_ErrorStatus FL_OPA_Init(OPA_Type *OPAx, FL_OPA_InitTypeDef *initStruct)
{
    FL_ErrorStatus status = FL_PASS;
    /* 入口参数检查 */
    assert_param(IS_OPA_ALL_INSTANCE(OPAx));
    assert_param(IS_FL_OPA_INP_CHANNAL(initStruct->INP));
    assert_param(IS_FL_OPA_INN_CHANNAL(initStruct->INN));
    assert_param(IS_FL_OPA_MODE(initStruct->mode));
    assert_param(IS_FL_OPA_DIGITALFILTER(initStruct->digitalFilter));
    assert_param(IS_FL_OPA_NEGTIVE_TO_PIN(initStruct->negtiveToPin));
    assert_param(IS_FL_OPA_LOW_POWER_MODE(initStruct->lowPowermode));
    assert_param(IS_FL_OPA_GAIN(initStruct->gain));
    /*总线时钟使能*/
    FL_RCC_EnableGroup1BusClock(FL_RCC_GROUP1_BUSCLK_ANAC);
    /*配置模式*/
    FL_OPA_SetMode(OPAx, initStruct->mode);
    /*配置反向输入*/
    FL_OPA_SetINNSource(OPAx, initStruct->INN);
    /*配置正向输入*/
    FL_OPA_SetINPSource(OPAx, initStruct->INP);
    /*配置低功耗模式*/
    if(initStruct->lowPowermode == FL_ENABLE)
    {
        FL_OPA_EnableLowPowerMode(OPAx);
    }
    if(initStruct->mode == FL_OPA_MODE_PGA)
    {
        /*配置PGA增益*/
        FL_OPA_PGA_SetGain(OPAx, initStruct->gain);
        if(initStruct->negtiveToPin == FL_ENABLE)
        {
            /*配置PGA模式下反向输入端接到PIN*/
            FL_OPA_PGA_EnableINNConnectToPin(OPAx);
        }
    }
    return status;
}

/**
  * @brief  将 @ref FL_OPA_InitTypeDef 结构体初始化为默认配置
  * @param  initStruct 指向 @ref FL_OPA_InitTypeDef 结构体的指针
  *
  * @retval None
  */

void FL_OPA_StructInit(FL_OPA_InitTypeDef *initStruct)
{
    initStruct->INP              = FL_OPA_INP_SOURCE_INP1;
    initStruct->INN              = FL_OPA_INN_SOURCE_INN1;
    initStruct->mode             = FL_OPA_MODE_STANDALONE;
    initStruct->digitalFilter    = FL_DISABLE;
    initStruct->negtiveToPin     = FL_DISABLE;
    initStruct->gain             = FL_OPA_GAIN_X2;
    initStruct->lowPowermode     = FL_DISABLE;
}

/**
  * @}
  */

#endif /* FL_OPA_DRIVER_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
