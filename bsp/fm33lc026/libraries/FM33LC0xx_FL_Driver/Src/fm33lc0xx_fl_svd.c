/**
  ****************************************************************************************************
  * @file    fm33lc0xx_fl_svd.c
  * @author  FMSH Application Team
  * @brief   Src file of SVD FL Module
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

/** @addtogroup SVD
  * @{
  */

#ifdef FL_SVD_DRIVER_ENABLED

/* Private macros ------------------------------------------------------------*/
/** @addtogroup SVD_FL_Private_Macros
  * @{
  */
#define         IS_SVD_INSTANCE(INSTANCE)                  (((INSTANCE) == SVD))

#define         IS_FL_SVD_WARNING_THRESHOLD_LEVEL(__VALUE__)        (((__VALUE__) == FL_SVD_WARNING_THRESHOLD_GROUP0)||\
                                                                     ((__VALUE__) == FL_SVD_WARNING_THRESHOLD_GROUP1)||\
                                                                     ((__VALUE__) == FL_SVD_WARNING_THRESHOLD_GROUP2)||\
                                                                     ((__VALUE__) == FL_SVD_WARNING_THRESHOLD_GROUP3)||\
                                                                     ((__VALUE__) == FL_SVD_WARNING_THRESHOLD_GROUP4)||\
                                                                     ((__VALUE__) == FL_SVD_WARNING_THRESHOLD_GROUP5)||\
                                                                     ((__VALUE__) == FL_SVD_WARNING_THRESHOLD_GROUP6)||\
                                                                     ((__VALUE__) == FL_SVD_WARNING_THRESHOLD_GROUP7)||\
                                                                     ((__VALUE__) == FL_SVD_WARNING_THRESHOLD_GROUP8)||\
                                                                     ((__VALUE__) == FL_SVD_WARNING_THRESHOLD_GROUP9)||\
                                                                     ((__VALUE__) == FL_SVD_WARNING_THRESHOLD_GROUP10)||\
                                                                     ((__VALUE__) == FL_SVD_WARNING_THRESHOLD_GROUP11)||\
                                                                     ((__VALUE__) == FL_SVD_WARNING_THRESHOLD_GROUP12)||\
                                                                     ((__VALUE__) == FL_SVD_WARNING_THRESHOLD_GROUP13)||\
                                                                     ((__VALUE__) == FL_SVD_WARNING_THRESHOLD_GROUP14)||\
                                                                     ((__VALUE__) == FL_SVD_WARNING_THRESHOLD_GROUP15))

#define         IS_FL_SVD_SVSCONFIG(__VALUE__)             (((__VALUE__) == FL_DISABLE)||\
                                                            ((__VALUE__) == FL_ENABLE))

#define         IS_FL_SVD_REFERENCE_VOLTAGE(__VALUE__)     (((__VALUE__) == FL_SVD_REFERENCE_1P2V)||\
                                                            ((__VALUE__) == FL_SVD_REFERENCE_1P1V)||\
                                                            ((__VALUE__) == FL_SVD_REFERENCE_1P0V))

#define         IS_FL_SVD_DIGITAL_FILTER(__VALUE__)        (((__VALUE__) == FL_DISABLE)||\
                                                            ((__VALUE__) == FL_ENABLE))
/**
  *@}
  */

/** @addtogroup SVD_FL_EF_Init
  * @{
  */

/**
  * @brief  复位SVD外设
  * @param  SVDx 外设入口地址
  * @retval 错误状态，可能值：
  *         -FL_PASS 外设寄存器值恢复复位值
  *         -FL_FAIL 未成功执行
  */
FL_ErrorStatus FL_SVD_DeInit(SVD_Type *SVDx)
{
    FL_ErrorStatus status = FL_PASS;
    /* 入口参数合法性断言 */
    assert_param(IS_SVD_INSTANCE(SVDx));
    SVDx->CFGR  = 0x00000C08U;
    SVDx->CR    = 0x00000000U;
    SVDx->IER   = 0x00000000U;
    SVDx->VSR   = 0x00000004U;
    return (status);
}

/**
  * @brief  配置SVD
  * @param  SVDx  外设入口地址
  * @param  initStruct 指向 @ref FL_SVD_InitTypeDef 结构体的指针
  *
  * @retval 错误状态，可能值：
  *         -FL_PASS 配置成功
  *         -FL_FAIL 配置过程发生错误
  */
FL_ErrorStatus FL_SVD_Init(SVD_Type *SVDx, FL_SVD_InitTypeDef *initStruct)
{
    FL_ErrorStatus status = FL_FAIL;
    /* 参数合法性检查 */
    assert_param(IS_SVD_INSTANCE(SVDx));
    assert_param(IS_FL_SVD_WARNING_THRESHOLD_LEVEL(initStruct->warningThreshold));
    assert_param(IS_FL_SVD_SVSCONFIG(initStruct->SVSChannel));
    assert_param(IS_FL_SVD_REFERENCE_VOLTAGE(initStruct->referenceVoltage));
    assert_param(IS_FL_SVD_DIGITAL_FILTER(initStruct->digitalFilter));
    /* 使能工作时钟 */
    FL_RCC_EnableGroup1BusClock(FL_RCC_GROUP1_BUSCLK_ANAC);
    /* 检测阈值 */
    FL_SVD_SetWarningThreshold(SVDx, initStruct->warningThreshold);
    /* 参考电压通道选择 */
    FL_SVD_EnableReference(SVD, initStruct->referenceVoltage);
    /* 外部通道配置 */
    if(initStruct->SVSChannel == FL_ENABLE)
    {
        FL_SVD_EnableSVSChannel(SVDx);
    }
    else
    {
        FL_SVD_DisableSVSChannel(SVDx);
    }
    /* 数字滤波配置 */
    if(initStruct->digitalFilter == FL_ENABLE)
    {
        FL_SVD_EnableDigitalFilter(SVDx);
    }
    else
    {
        FL_SVD_DisableDigitalFilter(SVDx);
    }
    status = FL_PASS;
    return status;
}

/**
  * @brief  将 @ref FL_SVD_InitTypeDef 结构体初始化为默认配置
  * @param  initStruct 指向 @ref FL_SVD_InitTypeDef 结构体的指针
  *
  * @retval None
  */
void FL_SVD_StructInit(FL_SVD_InitTypeDef *initStruct)
{
    initStruct->SVSChannel          = FL_DISABLE;
    initStruct->digitalFilter       = FL_ENABLE;
    initStruct->referenceVoltage    = FL_SVD_REFERENCE_1P0V;
    initStruct->warningThreshold    = FL_SVD_WARNING_THRESHOLD_GROUP0;
}

/**
  * @}
  */

#endif /* FL_SVD_DRIVER_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
