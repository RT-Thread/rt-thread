/**
  *******************************************************************************************************
  * @file    fm33lg0xx_fl_can.c
  * @author  FMSH Application Team
  * @brief   Src file of VAN fL Module
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

/** @addtogroup CAN
  * @{
  */

#ifdef FL_CAN_DRIVER_ENABLED

/* Private macros ------------------------------------------------------------*/
/** @addtogroup CAN_FL_Private_Macros
  * @{
  */
#define IS_CAN_SJW(__VALUE__)  (((__VALUE__) == FL_CAN_SJW_1Tq) \
                                                             || ((__VALUE__) == FL_CAN_SJW_2Tq) \
                                                             || ((__VALUE__) == FL_CAN_SJW_3Tq) \
                                                             || ((__VALUE__) == FL_CAN_SJW_4Tq))


#define IS_CAN_TS1(__VALUE__)    (((__VALUE__) == FL_CAN_TS1_1Tq) \
                                                                 || ((__VALUE__) == FL_CAN_TS1_2Tq) \
                                                                 || ((__VALUE__) == FL_CAN_TS1_3Tq) \
                                                                 || ((__VALUE__) == FL_CAN_TS1_4Tq) \
                                                                 || ((__VALUE__) == FL_CAN_TS1_5Tq) \
                                                                 || ((__VALUE__) == FL_CAN_TS1_6Tq) \
                                                                 || ((__VALUE__) == FL_CAN_TS1_7Tq) \
                                                                 || ((__VALUE__) == FL_CAN_TS1_8Tq) \
                                                                 || ((__VALUE__) == FL_CAN_TS1_9Tq) \
                                                                 || ((__VALUE__) == FL_CAN_TS1_10Tq) \
                                                                 || ((__VALUE__) == FL_CAN_TS1_11Tq) \
                                                                 || ((__VALUE__) == FL_CAN_TS1_12Tq) \
                                                                 || ((__VALUE__) == FL_CAN_TS1_13Tq) \
                                                                 || ((__VALUE__) == FL_CAN_TS1_14Tq) \
                                                                 || ((__VALUE__) == FL_CAN_TS1_15Tq) \
                                                                 || ((__VALUE__) == FL_CAN_TS1_16Tq))



#define IS_CAN_TS2(__VALUE__)    (((__VALUE__) == FL_CAN_TS2_1Tq) \
                                                                 || ((__VALUE__) == FL_CAN_TS2_2Tq) \
                                                                 || ((__VALUE__) == FL_CAN_TS2_3Tq) \
                                                                 || ((__VALUE__) == FL_CAN_TS2_4Tq) \
                                                                 || ((__VALUE__) == FL_CAN_TS2_5Tq) \
                                                                 || ((__VALUE__) == FL_CAN_TS2_6Tq) \
                                                                 || ((__VALUE__) == FL_CAN_TS2_7Tq) \
                                                                 || ((__VALUE__) == FL_CAN_TS2_8Tq))


#define IS_CAN_FILTER_EN(__VALUE__)    (((__VALUE__) == FL_ENABLE) \
                                                                 || ((__VALUE__) == FL_DISABLE))


#define IS_CAN_AFx(__VALUE__)    (((__VALUE__) == FL_CAN_FILTER1) \
                                                                 || ((__VALUE__) == FL_CAN_FILTER2) \
                                                                 || ((__VALUE__) == FL_CAN_FILTER3) \
                                                                 || ((__VALUE__) == FL_CAN_FILTER4))


#define IS_CAN_MODE(__VALUE__)    (((__VALUE__) == FL_CAN_MODE_NORMAL) \
                                                                 || ((__VALUE__) == FL_CAN_MODE_LOOPBACK) \
                                                                 || ((__VALUE__) == FL_CAN_MODE_CONFIG))


#define IS_CAN_CLK(__VALUE__)    (((__VALUE__) == FL_CMU_CAN_CLK_SOURCE_RCHF) \
                                                                 || ((__VALUE__) == FL_CMU_CAN_CLK_SOURCE_XTHF) \
                                                                 || ((__VALUE__) == FL_CMU_CAN_CLK_SOURCE_PLL) \
                                                                 || ((__VALUE__) == FL_CMU_CAN_CLK_SOURCE_APBCLK))






#define IS_CAN_SRR(__VALUE__)     (((__VALUE__)==FL_CAN_SRR_BIT_LOW) ||((__VALUE__)==FL_CAN_SRR_BIT_HIGH))
#define IS_CAN_IDE(__VALUE__)     (((__VALUE__)==FL_CAN_IDE_BIT_LOW) ||((__VALUE__)==FL_CAN_IDE_BIT_HIGH))
#define IS_CAN_RTR(__VALUE__)     (((__VALUE__)==FL_CAN_RTR_BIT_LOW) ||((__VALUE__)==FL_CAN_RTR_BIT_HIGH))

#define IS_CAN_ID18_MASK(__VALUE__)         (__VALUE__<=262143U)
#define IS_CAN_ID11_MASK(__VALUE__)         (__VALUE__<=2047U)

#define IS_CAN_SRR_MASK(__VALUE__)          (((__VALUE__) == FL_ENABLE) \
                                                                 || ((__VALUE__) == FL_DISABLE))

#define IS_CAN_IDE_MASK(__VALUE__)          (((__VALUE__) == FL_ENABLE) \
                                                                 || ((__VALUE__) == FL_DISABLE))

#define IS_CAN_RTR_MASK(__VALUE__)          (((__VALUE__) == FL_ENABLE) \
                                                                 || ((__VALUE__) == FL_DISABLE))
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup CAN_FL_EF_Init
  * @{
  */

/**
  * @brief  CAN初始化
  * @param  CANx外设入口地址
  * @param  CAN_InitStruct 指向一个@ref FL_CAN_InitTypeDef  结构体的指针
  * @retval 错误状态可能值
  *         -FL_FAIL 配置过程发生错误
  *         -FL_PASS 配置成功
  */
FL_ErrorStatus FL_CAN_Init(CAN_Type *CANx, FL_CAN_InitTypeDef *CAN_InitStruct)
{
    /*参数检查*/
    assert_param(IS_CAN_SJW(CAN_InitStruct->SJW));
    assert_param(IS_CAN_TS1(CAN_InitStruct->TS1));
    assert_param(IS_CAN_TS2(CAN_InitStruct->TS2));
    assert_param(IS_CAN_CLK(CAN_InitStruct->clockSource));
    /*时钟总线配置*/
    FL_CMU_EnableGroup3BusClock(FL_CMU_GROUP3_BUSCLK_CAN);
    FL_CMU_EnableGroup3OperationClock(FL_CMU_GROUP3_OPCLK_CAN);
    /*CAN时钟源选择*/
    FL_CMU_SetCANClockSource(CAN_InitStruct->clockSource);
    /*复位CAN模块*/
    FL_CAN_SetSoftwareReset(CANx, FL_CAN_SOFTWARE_RESET);
    /*设置同步段*/
    FL_CAN_WriteSyncJumpWidth(CANx, CAN_InitStruct->SJW);
    /*设置时间段1*/
    FL_CAN_WriteTimeSegment1Length(CANx, CAN_InitStruct->TS1);
    /*设置时间段2*/
    FL_CAN_WriteTimeSegment2Length(CANx, CAN_InitStruct->TS2);
    /*设置波特率*/
    FL_CAN_WriteBaudRatePrescaler(CANx, CAN_InitStruct->BRP);
    if(CAN_InitStruct->mode == FL_CAN_MODE_NORMAL)
    {
        FL_CAN_DisableLoopBackMode(CANx);    /* Normal模式 */
        FL_CAN_Enable(CANx);
    }
    else
        if(CAN_InitStruct->mode == FL_CAN_MODE_LOOPBACK)
        {
            FL_CAN_EnableLoopBackMode(CANx);    /* Loop Back模式 */
            FL_CAN_Enable(CANx);
        }
        else
        {
            FL_CAN_Disable(CANx);    /* Configuration模式 */
        }
    return FL_PASS;
}

/**
  * @brief  设置 CAN_InitStruct 为默认配置
  * @param  CAN_InitStruct 指向需要将值设置为默认配置的结构体 @ref FL_CAN_InitTypeDef 结构体
  *
  * @retval None
  */
void FL_CAN_StructInit(FL_CAN_InitTypeDef *CAN_InitStruct)
{
    CAN_InitStruct->mode = FL_CAN_MODE_NORMAL;
    CAN_InitStruct->BRP = 0;
    CAN_InitStruct->clockSource = FL_CMU_CAN_CLK_SOURCE_RCHF;
    CAN_InitStruct->SJW = FL_CAN_SJW_1Tq;
    CAN_InitStruct->TS1 = FL_CAN_TS1_5Tq;
    CAN_InitStruct->TS2 = FL_CAN_TS2_4Tq;
}

/**
  * @brief  CAN滤波器初始化
  * @param  CANx外设入口地址
  * @param  filterX This parameter can be one of the following values:
  *         @arg @ref  FL_CAN_FILTER1
  *         @arg @ref  FL_CAN_FILTER2
  *         @arg @ref  FL_CAN_FILTER3
  *         @arg @ref  FL_CAN_FILTER4
  * @param  CAN_InitFilterStruct 指向一个@ref FL_CAN_FilterInitTypeDef  结构体的指针
  * @retval 错误状态可能值
  *         -FL_FAIL 配置过程发生错误
  *         -FL_PASS 配置成功
  */
FL_ErrorStatus FL_CAN_FilterInit(CAN_Type *CANx, FL_CAN_FilterInitTypeDef *CAN_FilterInitStruct, uint32_t filterX)
{
    uint32_t counter = 0;
    uint32_t filterstatus;
    assert_param(IS_CAN_SRR(CAN_FilterInitStruct->filterIdSRR));
    assert_param(IS_CAN_IDE(CAN_FilterInitStruct->filterIdIDE));
    assert_param(IS_CAN_RTR(CAN_FilterInitStruct->filterIdRTR));
    assert_param(IS_CAN_FILTER_EN(CAN_FilterInitStruct->filterEn));
    assert_param(IS_CAN_ID18_MASK(CAN_FilterInitStruct->filterMaskIdLow));
    assert_param(IS_CAN_ID11_MASK(CAN_FilterInitStruct->filterMaskIdHigh));
    assert_param(IS_CAN_SRR_MASK(CAN_FilterInitStruct->filterMaskIdSRR));
    assert_param(IS_CAN_IDE_MASK(CAN_FilterInitStruct->filterMaskIdIDE));
    assert_param(IS_CAN_RTR_MASK(CAN_FilterInitStruct->filterMaskIdRTR));
    assert_param(IS_CAN_AFx(filterX));
    do
    {
        filterstatus = FL_CAN_IsActiveFlag_FilterBusy(CANx);
        counter++;
    } while((filterstatus != 0U) && (counter != CAN_TIMEOUT));
    if(CAN_FilterInitStruct->filterIdIDE == FL_CAN_IDE_BIT_HIGH)
    {
        FL_CAN_Filter_WriteIDCompare(CANx, filterX, ((CAN_FilterInitStruct->filterIdExtend) >> 18) & 0X7FF);
        FL_CAN_Filter_WriteEXTIDCompare(CANx, filterX, (CAN_FilterInitStruct->filterIdExtend) & 0X3FFFF);
    }
    else
    {
        FL_CAN_Filter_WriteIDCompare(CANx, filterX, (CAN_FilterInitStruct->filterIdStandard) & 0X7FF);
    }
    if((CAN_FilterInitStruct->filterMaskIdSRR) == FL_ENABLE)    /* SRR参与滤波器比较 */
    {
        FL_CAN_Filter_EnableSRRCompare(CANx, filterX);
    }
    else
    {
        FL_CAN_Filter_DisableSRRCompare(CANx, filterX);
    }
    if((CAN_FilterInitStruct->filterMaskIdIDE) == FL_ENABLE)    /* IDE位参与滤波器比较 */
    {
        FL_CAN_Filter_EnableIDECompare(CANx, filterX);
    }
    else
    {
        FL_CAN_Filter_DisableIDECompare(CANx, filterX);
    }
    if((CAN_FilterInitStruct->filterMaskIdRTR) == FL_ENABLE)    /* RTR位参与滤波器比较 */
    {
        FL_CAN_Filter_EnableRTRCompare(CANx, filterX);
    }
    else
    {
        FL_CAN_Filter_DisableRTRCompare(CANx, filterX);
    }
    FL_CAN_Filter_WriteIDCompareMask(CANx, filterX, CAN_FilterInitStruct->filterMaskIdHigh);    /* 滤波器掩码配置 */
    FL_CAN_Filter_WriteEXTIDCompareMask(CANx, filterX, CAN_FilterInitStruct->filterMaskIdLow);
    FL_CAN_Filter_SetSRRCompare(CANx, filterX, CAN_FilterInitStruct->filterIdSRR);
    FL_CAN_Filter_SetIDECompare(CANx, filterX, CAN_FilterInitStruct->filterIdIDE);    /* 滤波器ID配置 */
    FL_CAN_Filter_SetRTRCompare(CANx, filterX, CAN_FilterInitStruct->filterIdRTR);
    if((CAN_FilterInitStruct->filterEn) == FL_ENABLE)    /* 滤波器使能 */
    {
        FL_CAN_Filter_Enable(CANx, filterX);
    }
    else
    {
        FL_CAN_Filter_Disable(CANx, filterX);
    }
    return FL_PASS;
}
/**
  * @brief  设置 CAN_FilterInitStruct 为默认配置
  * @param  CAN_FilterInitStruct 指向需要将值设置为默认配置的结构体 @ref FL_CAN_FilterInitTypeDef 结构体
  *
  * @retval None
  */
void FL_CAN_StructFilterInit(FL_CAN_FilterInitTypeDef *CAN_FilterInitStruct)
{
    CAN_FilterInitStruct->filterEn = FL_DISABLE;
    CAN_FilterInitStruct->filterIdExtend = 0;
    CAN_FilterInitStruct->filterMaskIdHigh = 0x7FF;
    CAN_FilterInitStruct->filterIdIDE = FL_CAN_IDE_BIT_LOW;
    CAN_FilterInitStruct->filterMaskIdIDE = FL_DISABLE;
    CAN_FilterInitStruct->filterMaskIdLow = 0X3FFFF;
    CAN_FilterInitStruct->filterIdRTR = FL_CAN_RTR_BIT_LOW;
    CAN_FilterInitStruct->filterMaskIdRTR = FL_DISABLE;
    CAN_FilterInitStruct->filterIdSRR = FL_CAN_SRR_BIT_LOW;
    CAN_FilterInitStruct->filterMaskIdSRR = FL_DISABLE;
    CAN_FilterInitStruct->filterIdStandard = 0;
}

/**
  * @}
  */

#endif /* FL_CAN_DRIVER_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
