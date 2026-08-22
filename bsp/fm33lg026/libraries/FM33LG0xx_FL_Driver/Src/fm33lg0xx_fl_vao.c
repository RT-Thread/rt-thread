/**
  *******************************************************************************************************
  * @file    fm33lg0xx_fl_vao.c
  * @author  FMSH Application Team
  * @brief   Src file of DMA FL Module
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

/** @addtogroup VAO
  * @{
  */

#ifdef FL_VAO_DRIVER_ENABLED

/* Private macros ------------------------------------------------------------*/
/** @addtogroup VAO_FL_Private_Macros
  * @{
  */
#define         IS_FL_VAO_INSTANCE(INTANCE)                      ((INTANCE) == VAO)

#define         IS_FL_VAO_OUTPUT_DRIVE_ABILITY(__VALUE__)        (((__VALUE__) == FL_VAO_XTLF_DRIVE_LEVEL_NONE)||\
                                                                  ((__VALUE__) == FL_VAO_XTLF_DRIVE_LEVEL_1)||\
                                                                  ((__VALUE__) == FL_VAO_XTLF_DRIVE_LEVEL_2)||\
                                                                  ((__VALUE__) == FL_VAO_XTLF_DRIVE_LEVEL_3)||\
                                                                  ((__VALUE__) == FL_VAO_XTLF_DRIVE_LEVEL_4)||\
                                                                  ((__VALUE__) == FL_VAO_XTLF_DRIVE_LEVEL_5)||\
                                                                  ((__VALUE__) == FL_VAO_XTLF_DRIVE_LEVEL_6)||\
                                                                  ((__VALUE__) == FL_VAO_XTLF_DRIVE_LEVEL_7))

#define         IS_FL_VAO_WORKING_CURRENT(__VALUE__)             (((__VALUE__) == FL_VAO_XTLF_WORK_CURRENT_850NA)||\
                                                                  ((__VALUE__) == FL_VAO_XTLF_WORK_CURRENT_800NA)||\
                                                                  ((__VALUE__) == FL_VAO_XTLF_WORK_CURRENT_750NA)||\
                                                                  ((__VALUE__) == FL_VAO_XTLF_WORK_CURRENT_700NA)||\
                                                                  ((__VALUE__) == FL_VAO_XTLF_WORK_CURRENT_650NA)||\
                                                                  ((__VALUE__) == FL_VAO_XTLF_WORK_CURRENT_600NA)||\
                                                                  ((__VALUE__) == FL_VAO_XTLF_WORK_CURRENT_550NA)||\
                                                                  ((__VALUE__) == FL_VAO_XTLF_WORK_CURRENT_500NA)||\
                                                                  ((__VALUE__) == FL_VAO_XTLF_WORK_CURRENT_450NA)||\
                                                                  ((__VALUE__) == FL_VAO_XTLF_WORK_CURRENT_400NA)||\
                                                                  ((__VALUE__) == FL_VAO_XTLF_WORK_CURRENT_350NA)||\
                                                                  ((__VALUE__) == FL_VAO_XTLF_WORK_CURRENT_300NA)||\
                                                                  ((__VALUE__) == FL_VAO_XTLF_WORK_CURRENT_250NA)||\
                                                                  ((__VALUE__) == FL_VAO_XTLF_WORK_CURRENT_200NA)||\
                                                                  ((__VALUE__) == FL_VAO_XTLF_WORK_CURRENT_150NA)||\
                                                                  ((__VALUE__) == FL_VAO_XTLF_WORK_CURRENT_100NA))

#define         IS_FL_VAO_PH15_INPUT(__VALUE__)                  (((__VALUE__) == FL_DISABLE)||\
                                                                  ((__VALUE__) == FL_ENABLE))

#define         IS_FL_VAO_PH15_PULL_UP(__VALUE__)                (((__VALUE__) == FL_DISABLE)||\
                                                                  ((__VALUE__) == FL_ENABLE))


#define         IS_FL_VAO_PH15_OPENDRAIN_OUTPUT(__VALUE__)       (((__VALUE__) == FL_DISABLE)||\
                                                                  ((__VALUE__) == FL_ENABLE))

#define         IS_FL_VAO_PH15_MODE(__VALUE__)                  (((__VALUE__) == FL_VAO_PH15_MODE_INPUT)||\
                                                                 ((__VALUE__) == FL_VAO_PH15_MODE_OUTPUT)||\
                                                                 ((__VALUE__) == FL_VAO_PH15_MODE_RTCOUT))

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup VAO_FL_EF_Init
  * @{
  */

/**
  * @brief  复位对应VAO寄存器
  * @param  VAOx VAO Port
  * @retval ErrorStatus枚举值:
  *         -FL_PASS 外设寄存器值恢复复位值
  *         -FL_FAIL 未成功执行
  */
FL_ErrorStatus FL_VAO_DeInit(VAO_Type *VAOx)
{
    /* 入口参数检查 */
    assert_param(IS_FL_VAO_INSTANCE(VAOx));
    /* 使能vao复位 */
    FL_VAO_EnableReset(VAOx);
    /*失能CDIF*/
    FL_CDIF_DisableVAOToCPU(CDIF);
    FL_CDIF_DisableCPUToVAO(CDIF);
    return FL_PASS;
}

/**
  * @brief  根据 VAO_IO_StructInit 的配置信息初始化对应外设入口地址的寄存器值
  * @param  VAOx VAOx
  * @param  VAO_IO_StructInit 指向一个 @ref FL_VAO_IO_InitTypeDef 结构体
  *         其中包含了外设的相关配置信息.
  * @retval ErrorStatus枚举值
  *         -FL_FAIL 配置过程发生错误
  *         -FL_PASS 配置成功
  */
FL_ErrorStatus FL_VAO_IO_Init(VAO_Type *VAOx, FL_VAO_IO_InitTypeDef *VAO_IO_InitStruct)
{
    /* 参数检查 */
    assert_param(IS_FL_VAO_INSTANCE(VAOx));
    assert_param(IS_FL_VAO_PH15_INPUT(VAO_IO_InitStruct->input));
    assert_param(IS_FL_VAO_PH15_PULL_UP(VAO_IO_InitStruct->pullup));
    assert_param(IS_FL_VAO_PH15_OPENDRAIN_OUTPUT(VAO_IO_InitStruct->opendrainOutput));
    assert_param(IS_FL_VAO_PH15_MODE(VAO_IO_InitStruct->mode));
    /*使能CDIF*/
    FL_CDIF_EnableVAOToCPU(CDIF);
    FL_CDIF_EnableCPUToVAO(CDIF);
    /*! PH15功能选择 */
    FL_VAO_GPIO_SetPH15Mode(VAOx, VAO_IO_InitStruct->mode);
    /*! PH15输入使能 */
    if(VAO_IO_InitStruct->input == FL_ENABLE)
    {
        FL_VAO_GPIO_EnablePH15Input(VAOx);
    }
    else
    {
        FL_VAO_GPIO_DisablePH15Input(VAOx);
    }
    /*! PH15上拉使能 */
    if(VAO_IO_InitStruct->pullup == FL_ENABLE)
    {
        FL_VAO_GPIO_EnablePH15Pullup(VAOx);
    }
    else
    {
        FL_VAO_GPIO_DisablePH15Pullup(VAOx);
    }
    /*! PH15开漏输出使能 */
    if(VAO_IO_InitStruct->opendrainOutput == FL_ENABLE)
    {
        FL_VAO_GPIO_EnablePH15OpenDrain(VAOx);
    }
    else
    {
        FL_VAO_GPIO_DisablePH15OpenDrain(VAOx);
    }
    return FL_PASS;
}

/**
  * @brief  根据 VAO_XTLF_StructInit 的配置信息初始化对应外设入口地址的寄存器值
  * @param  VAOx VAOx
  * @param  VAO_XTLF_StructInit 指向一个 @ref FL_VAO_XTLF_InitTypeDef 结构体
  *         其中包含了外设的相关配置信息.
  * @retval ErrorStatus枚举值
  *         -FL_FAIL 配置过程发生错误
  *         -FL_PASS 配置成功
  */
FL_ErrorStatus FL_VAO_XTLF_Init(VAO_Type *VAOx, FL_VAO_XTLF_InitTypeDef *VAO_XTLF_InitStruct)
{
    /* 参数检查 */
    assert_param(IS_FL_VAO_INSTANCE(VAOx));
    assert_param(IS_FL_VAO_OUTPUT_DRIVE_ABILITY(VAO_XTLF_InitStruct->driveMode));
    assert_param(IS_FL_VAO_WORKING_CURRENT(VAO_XTLF_InitStruct->workingCurrentMode));
    /*使能CDIF*/
    FL_CDIF_EnableVAOToCPU(CDIF);
    FL_CDIF_EnableCPUToVAO(CDIF);
    /*! XTLF工作电流选择 */
    FL_VAO_XTLF_SetWorkCurrent(VAOx, VAO_XTLF_InitStruct->workingCurrentMode);
    /*! XTLF输出级驱动能力配置 */
    FL_VAO_XTLF_SetDriveLevel(VAOx, VAO_XTLF_InitStruct->driveMode);
    return FL_PASS;
}

/**
* @brief   设置 VAO_IO_StructInit 为默认配置
* @param   VAO_IO_StructInit 指向需要将值设置为默认配置的结构体 @ref FL_VAO_IO_InitTypeDef 结构体
*
* @retval  None
*/

void FL_VAO_IO_StructInit(FL_VAO_IO_InitTypeDef *VAO_IO_InitStruct)
{
    VAO_IO_InitStruct->mode                       = FL_VAO_PH15_MODE_INPUT;
    VAO_IO_InitStruct->input                      = FL_ENABLE;
    VAO_IO_InitStruct->pullup                     = FL_ENABLE;
    VAO_IO_InitStruct->opendrainOutput            = FL_DISABLE;
}
/**
* @brief   设置 VAO_XTLF_StructInit 为默认配置
* @param   VAO_XTLF_StructInit 指向需要将值设置为默认配置的结构体 @ref FL_VAO_XTLF_InitTypeDef 结构体
*
* @retval  None
*/

void FL_VAO_XTLF_StructInit(FL_VAO_XTLF_InitTypeDef *VAO_XTLF_InitStruct)
{
    VAO_XTLF_InitStruct->driveMode                   = FL_VAO_XTLF_DRIVE_LEVEL_1;
    VAO_XTLF_InitStruct->workingCurrentMode          = FL_VAO_XTLF_WORK_CURRENT_450NA;
}

/**
  * @}
  */

#endif /* FL_VAO_DRIVER_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/*************************(C) COPYRIGHT Fudan Microelectronics **** END OF FILE*************************/
