/**
  *******************************************************************************************************
  * @file    fm33lg0xx_fl_rtcb.c
  * @author  FMSH Application Team
  * @brief   Src file of RTCB FL Module
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

/** @addtogroup RTCB
  * @{
  */

#ifdef FL_RTCB_DRIVER_ENABLED

/* Private macros ------------------------------------------------------------*/
/** @addtogroup TIM_FL_Private_Macros
  * @{
  */
#define IS_RTCB_INSTANCE(RTCBx)                     ((RTCBx) == RTCB)

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup RTCB_FL_EF_Init
  * @{
  */
/**
  * @brief  复位对应RTCBx寄存器.
  * @param  RTCBx
  * @retval ErrorStatus枚举值:
  *           -FL_PASS 外设寄存器值恢复复位值
  *           -FL_FAIL 未成功执行
  */
FL_ErrorStatus FL_RTCB_DeInit(RTCB_Type *RTCBx)
{
    FL_ErrorStatus result = FL_PASS;
    /* Check the parameters */
    assert_param(IS_RTCB_INSTANCE(RTCBx));
    /* 打开电源域接口 */
    CDIF->CR = 0X00000003;
    RTCBx->IER       = 0x00000000U;
    RTCBx->WER       = 0xACACACACU;
    RTCBx->STPCR     = 0x00000000U;
    RTCBx->STPCLKRR = 0x00000000U;
    RTCBx->STPCALRR = 0x00000000U;
    RTCBx->ALARM     = 0x00000000U;
    RTCBx->BCDDAY    = 0x00000000U;
    RTCBx->BCDHOUR   = 0x00000000U;
    RTCBx->BCDMIN    = 0x00000000U;
    RTCBx->BCDMONTH  = 0x00000000U;
    RTCBx->BCDSEC    = 0x00000000U;
    RTCBx->BCDWEEK   = 0x00000000U;
    RTCBx->BCDYEAR   = 0x00000000U;
    RTCBx->ADJR         = 0x00000000U;
    RTCBx->TMSEL     = 0x00000000U;
    RTCBx->CR        = 0x00000000U;
    RTCBx->WER       = 0x00000000U;
    return result;
}
/**
  * @brief  配置实时时钟相关.
  * @param  RTCBx Timer Instance
  * @param  initStruct 指向一个 @ref FL_RTCB_InitTypeDef(时基配置结构体)
  * @retval ErrorStatus枚举值
  *            -FL_FAIL 配置过程发生错误
  *            -FL_PASS 成功
  */
FL_ErrorStatus FL_RTCB_Init(RTCB_Type *RTCBx, FL_RTCB_InitTypeDef *initStruct)
{
    /* 参数检查 */
    assert_param(IS_RTCB_INSTANCE(RTCBx));
    /* 打开电源域接口 */
    CDIF->CR = 0X00000003;
    /* 配置时间 */
    FL_RTCB_ConfigTime(RTCBx, initStruct);

    return FL_PASS;
}

/**
  * @brief  设置实时时钟
  * @param  RTCBx Timer Instance
  * @param  initStruct 指向一个 @ref FL_RTCB_InitTypeDef(时基配置结构体)
  * @retval ErrorStatus枚举值
  *            -FL_FAIL 配置过程发生错误
  *            -FL_PASS 成功
  */
FL_ErrorStatus FL_RTCB_ConfigTime(RTCB_Type *RTCBx, FL_RTCB_InitTypeDef *initStruct)
{
    /* 使能时间配置 */
    FL_RTCB_WriteEnable(RTCBx);
    /* 配置秒 */
    FL_RTCB_WriteSecond(RTCBx, initStruct->second);
    /* 配置分钟 */
    FL_RTCB_WriteMinute(RTCBx, initStruct->minute);
    /* 配置小时 */
    FL_RTCB_WriteHour(RTCBx, initStruct->hour);
    /* 配置日期 */
    FL_RTCB_WriteDay(RTCBx, initStruct->day);
    /* 配置周 */
    FL_RTCB_WriteWeek(RTCBx, initStruct->week);
    /* 配置月 */
    FL_RTCB_WriteMonth(RTCBx, initStruct->month);
    /* 配置年 */
    FL_RTCB_WriteYear(RTCBx, initStruct->year);
    /* 锁定时间配置 */
    FL_RTCB_WriteDisable(RTCBx);
    return FL_PASS;
}
/**
  * @brief  获取实时时间并保存到指定结构体中
  * @param  RTCBx Timer Instance
  * @param  initStruct 指向一个 @ref FL_RTCB_InitTypeDef(时基配置结构体)
  * @retval ErrorStatus枚举值
  *            -FL_FAIL 配置过程发生错误
  *            -FL_PASS 成功
  */
FL_ErrorStatus FL_RTCB_GetTime(RTCB_Type *RTCBx, FL_RTCB_InitTypeDef *initStruct)
{
    /* 配置秒 */
    initStruct->second = FL_RTCB_ReadSecond(RTCBx);
    /* 配置分钟 */
    initStruct->minute  = FL_RTCB_ReadMinute(RTCBx);
    /* 配置小时 */
    initStruct->hour = FL_RTCB_ReadHour(RTCBx);
    /* 配置日期 */
    initStruct->day = FL_RTCB_ReadDay(RTCBx);
    /* 配置周 */
    initStruct->week = FL_RTCB_ReadWeek(RTCBx);
    /* 配置月 */
    initStruct->month = FL_RTCB_ReadMonth(RTCBx);
    /* 配置年 */
    initStruct->year = FL_RTCB_ReadYear(RTCBx);
    return FL_PASS;
}
/**
  * @brief    设置 initStruct 为默认配置
  * @param     initStruct 指向需要将值设置为默认配置的结构体 @ref FL_RTCB_InitTypeDef 结构体
  *
  * @retval    None
  */

void FL_RTCB_StructInit(FL_RTCB_InitTypeDef *initStruct)
{
    /*  */
    initStruct->year    = 0x00;
    initStruct->month   = 0x00;
    initStruct->day     = 0x00;
    initStruct->week    = 0x00;
    initStruct->hour    = 0x00;
    initStruct->minute  = 0x00;
    initStruct->second  = 0x00;
}

/**
  * @}
  */

#endif /* FL_RTCB_DRIVER_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/*************************(C) COPYRIGHT Fudan Microelectronics **** END OF FILE*************************/

