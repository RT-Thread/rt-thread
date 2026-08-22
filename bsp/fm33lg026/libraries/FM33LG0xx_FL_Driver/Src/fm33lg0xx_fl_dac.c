/**
  ****************************************************************************************************
  * @file    fm33lg0xx_fl_dac.c
  * @author  FMSH Application Team
  * @brief   Src file of DAC FL Module
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

/** @addtogroup DAC
  * @{
  */

#ifdef FL_DAC_DRIVER_ENABLED

/* Private macros ------------------------------------------------------------*/
/** @addtogroup DAC_FL_Private_Macros
  * @{
  */

#define         IS_FL_DAC_INSTANCE(INSTANCE)                            ((INSTANCE) == DAC)

#define         IS_FL_DAC_TRIGGERMODE(__VALUE__)                        (((__VALUE__) == FL_DISABLE)||\
        ((__VALUE__) == FL_ENABLE))

#define         IS_FL_DAC_TRIGGE_SOURCE(__VALUE__)                      (((__VALUE__) == FL_DAC_TRGI_SOFTWARE)||\
        ((__VALUE__) == FL_DAC_TRGI_ATIM)||\
        ((__VALUE__) == FL_DAC_TRGI_GPTIM1)||\
        ((__VALUE__) == FL_DAC_TRGI_GPTIM2)||\
        ((__VALUE__) == FL_DAC_TRGI_BSTIM16)||\
                ((__VALUE__) == FL_DAC_TRGI_LPTIM16)||\
        ((__VALUE__) == FL_DAC_TRGI_EXTI0)||\
        ((__VALUE__) == FL_DAC_TRGI_EXTI4)||\
        ((__VALUE__) == FL_DAC_TRGI_EXTI8)||\
        ((__VALUE__) == FL_DAC_TRGI_EXTI12))

#define         IS_FL_DAC_SAMPLEHOLDMODE(__VALUE__)                     (((__VALUE__) == FL_DISABLE)||\
        ((__VALUE__) == FL_ENABLE))

#define         IS_FL_DAC_HOLD_TIME(__VALUE__)                          (((__VALUE__) <= 0XFFFF))

#define         IS_FL_DAC_SAMPLE_TIME(__VALUE__)                        (((__VALUE__) <= 0XFF))

#define         IS_FL_DAC_BUFFERMODE(__VALUE__)                         (((__VALUE__) == FL_DISABLE)||\
        ((__VALUE__) == FL_ENABLE))

#define         IS_FL_DAC_SWITCHMODE(__VALUE__)                         (((__VALUE__) == FL_DISABLE)||\
        ((__VALUE__) == FL_ENABLE))

#define         IS_FL_DAC_DMAMODE(__VALUE__)                            (((__VALUE__) == FL_DISABLE)||\
        ((__VALUE__) == FL_ENABLE))

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup CRC_FL_EF_Init
  * @{
  */

/**
  * @brief  恢复对应的DAC入口地址寄存器为默认值
  *
  * @param  DACx  外设入口地址
  *
  * @retval ErrorStatus枚举值
  *         -FL_FAIL 配置过程发生错误
  *         -FL_PASS DAC配置成功
  */
FL_ErrorStatus  FL_DAC_DeInit(DAC_Type *DACx)
{
    FL_ErrorStatus status = FL_PASS;
    /* 入口合法性检查 */
    assert_param(IS_FL_DAC_INSTANCE(DACx));
    /* 外设复位使能 */
    FL_RMU_EnablePeripheralReset(RMU);
    FL_RMU_EnableResetAPBPeripheral(RMU, FL_RMU_RSTAPB_DAC);
    FL_RMU_DisableResetAPBPeripheral(RMU, FL_RMU_RSTAPB_DAC);
    FL_RMU_DisablePeripheralReset(RMU);
    return status;
}
/**
  * @brief  初始化DACx指定的入口地址的外设寄存器
  * @param  DACx  外设入口地址
  * @param  DAC_InitStruct 向一FL_DAC_InitTypeDef结构体，它包含指定DAC外设的配置信息
  *
  * @retval ErrorStatus枚举值
  *         -FL_FAIL 配置过程发生错误
  *         -FL_PASS DAC配置成功
  */
FL_ErrorStatus FL_DAC_Init(DAC_Type *DACx, FL_DAC_InitTypeDef  *DAC_InitStruct)
{
    FL_ErrorStatus status = FL_PASS;
    /* 入口合法性检查 */
    assert_param(IS_FL_DAC_INSTANCE(DACx));
    assert_param(IS_FL_DAC_TRIGGERMODE(DAC_InitStruct->triggerMode));
    assert_param(IS_FL_DAC_TRIGGE_SOURCE(DAC_InitStruct->triggerSource));
    assert_param(IS_FL_DAC_SAMPLEHOLDMODE(DAC_InitStruct->sampleHoldMode));
    assert_param(IS_FL_DAC_HOLD_TIME(DAC_InitStruct->holdTime));
    assert_param(IS_FL_DAC_SAMPLE_TIME(DAC_InitStruct->sampleTime));
    assert_param(IS_FL_DAC_BUFFERMODE(DAC_InitStruct->bufferMode));
    assert_param(IS_FL_DAC_SWITCHMODE(DAC_InitStruct->switchMode));
    FL_RMU_EnablePeripheralReset(RMU);
    FL_RMU_EnableResetAPBPeripheral(RMU, FL_RMU_RSTAPB_DAC);
    FL_RMU_DisableResetAPBPeripheral(RMU, FL_RMU_RSTAPB_DAC);
    FL_RMU_DisablePeripheralReset(RMU);
    FL_CMU_EnableGroup2BusClock(FL_CMU_GROUP2_BUSCLK_DAC);
    FL_DAC_Disable(DACx);
    if(FL_DAC_IsEnabled(DACx) == 0U)
    {
        /* 采样保持使能配置 */
        if(DAC_InitStruct->sampleHoldMode)
        {
            FL_DAC_WriteSamplingTime(DACx, DAC_InitStruct->sampleTime);
            FL_DAC_WriteHoldingTime(DACx, DAC_InitStruct->holdTime);
            FL_DAC_EnableSampleHoldMode(DACx);
        }
        else
        { FL_DAC_DisableSampleHoldMode(DACx); }
        /* 触发模式使能配置 */
        if(DAC_InitStruct->triggerMode)
        {
            FL_DAC_SetTriggerSource(DACx, DAC_InitStruct->triggerSource);
            FL_DAC_EnableTriggerMode(DACx);
        }
        else
        { FL_DAC_DisableTriggerMode(DACx); }
        /* buffer使能配置 */
        if(DAC_InitStruct->bufferMode)
        { FL_DAC_EnableOutputBuffer(DACx); }
        else
        { FL_DAC_DisableOutputBuffer(DACx); }
        /* SWITCH使能配置 */
        if(DAC_InitStruct->switchMode)
        { FL_DAC_EnableFeedbackSwitch(DACx); }
        else
        { FL_DAC_DisableFeedbackSwitch(DACx); }
    }
    else
    {
        status = FL_FAIL;
    }
    return status;
}


/**
  * @brief  设置 DAC_InitStruct 为默认配置
  * @param  DAC_InitStruct 指向需要将值设置为默认配置的结构体 @ref FL_DAC_InitTypeDef 结构体
  *
  * @retval None
  */
void FL_DAC_StructInit(FL_DAC_InitTypeDef *DAC_InitStruct)
{
    DAC_InitStruct->bufferMode = FL_ENABLE;
    DAC_InitStruct->switchMode = FL_ENABLE;
    DAC_InitStruct->triggerMode = FL_DISABLE;
    DAC_InitStruct->triggerSource = FL_DAC_TRGI_SOFTWARE;
    DAC_InitStruct->sampleHoldMode = FL_DISABLE;
    DAC_InitStruct->sampleTime = 0xFF;
    DAC_InitStruct->holdTime = 0X0;
}

/**
  * @}
  */

#endif /* FL_DAC_DRIVER_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/


