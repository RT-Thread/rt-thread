/**
  ****************************************************************************************************
  * @file    fm33lg0xx_fl_vrefp.c
  * @author  FMSH Application Team
  * @brief   Src file of VREFP FL Module
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

/** @addtogroup VREFP
  * @{
  */


#ifdef FL_VREFP_DRIVER_ENABLED

/* Private macros ------------------------------------------------------------*/
/** @addtogroup VREFP_FL_Private_Macros
  * @{
  */
#define         IS_VREFP_INSTANCE(INTANCE)                       ((INTANCE) == VREFP)

#define         IS_FL_VREFP_VOLTAGETRIM(__VALUE__)               (((__VALUE__) == FL_VREFP_OUTPUT_VOLTAGE_2P0V_TRIM)||\
                                                                 ((__VALUE__) == FL_VREFP_OUTPUT_VOLTAGE_2P5V_TRIM)||\
                                                                 ((__VALUE__) == FL_VREFP_OUTPUT_VOLTAGE_3P0V_TRIM)||\
                                                                 ((__VALUE__) == FL_VREFP_OUTPUT_VOLTAGE_4P5V_TRIM)||\
                                                                 ((__VALUE__) == FL_VREFP_OUTPUT_VOLTAGE_1P5V_TRIM))

#define         IS_FL_VREFP_OUTPUTVOLTAGE(__VALUE__)             (((__VALUE__) == FL_VREFP_OUTPUT_VOLTAGE_2P0V)||\
                                                                 ((__VALUE__) == FL_VREFP_OUTPUT_VOLTAGE_2P5V)||\
                                                                 ((__VALUE__) == FL_VREFP_OUTPUT_VOLTAGE_3P0V)||\
                                                                 ((__VALUE__) == FL_VREFP_OUTPUT_VOLTAGE_4P5V)||\
                                                                 ((__VALUE__) == FL_VREFP_OUTPUT_VOLTAGE_1P5V))

#define         IS_FL_VREFP_ENABLEPERIOD(__VALUE__)              (((__VALUE__) == FL_VREFP_ENABLE_PERIOD_1MS)||\
                                                                 ((__VALUE__) == FL_VREFP_ENABLE_PERIOD_4MS)||\
                                                                 ((__VALUE__) == FL_VREFP_ENABLE_PERIOD_16MS)||\
                                                                 ((__VALUE__) == FL_VREFP_ENABLE_PERIOD_32MS)||\
                                                                 ((__VALUE__) == FL_VREFP_ENABLE_PERIOD_64MS)||\
                                                                 ((__VALUE__) == FL_VREFP_ENABLE_PERIOD_256MS)||\
                                                                 ((__VALUE__) == FL_VREFP_ENABLE_PERIOD_1000MS)||\
                                                                 ((__VALUE__) == FL_VREFP_ENABLE_PERIOD_4000MS))

#define         IS_FL_VREFP_DRIVINGTIME(__VALUE__)               (((__VALUE__) == FL_VREFP_DRIVING_TIME_4LSCLK)||\
                                                                 ((__VALUE__) == FL_VREFP_DRIVING_TIME_8LSCLK)||\
                                                                 ((__VALUE__) == FL_VREFP_DRIVING_TIME_16LSCLK)||\
                                                                 ((__VALUE__) == FL_VREFP_DRIVING_TIME_32LSCLK)||\
                                                                 ((__VALUE__) == FL_VREFP_DRIVING_TIME_64LSCLK)||\
                                                                 ((__VALUE__) == FL_VREFP_DRIVING_TIME_128LSCLK)||\
                                                                 ((__VALUE__) == FL_VREFP_DRIVING_TIME_256LSCLK)||\
                                                                 ((__VALUE__) == FL_VREFP_DRIVING_TIME_512LSCLK))

#define         IS_FL_VREFP_WORKMODE(__VALUE__)                  (((__VALUE__) == FL_VREFP_WORK_MODE_CONTINUOUS)||\
                                                                 ((__VALUE__) == FL_VREFP_WORK_MODE_PERIODIC))

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup VREFP_FL_EF_Init
  * @{
  */

/**
  * @brief  关闭VREFP外设总线时钟
  *
  * @param  VREFPx 外设入口地址
  *
  * @retval ErrorStatus枚举值
  *         -FL_PASS 配置成功
  *         -FL_FAIL 配置过程发生错误
  */
FL_ErrorStatus FL_VREFP_DeInit(VREFP_Type *VREFPx)
{
    assert_param(IS_VREFP_INSTANCE(VREFPx));
    return FL_PASS;
}
/**
  * @brief  根据 VREFP_InitStruct初始化对应外设入口地址的寄存器值.
  *
  * @note   WWTD使能后将无法关闭，直到下一次芯片复位
  *
  * @param  VREFPx 外设入口地址
  *
  * @param  VREFP_InitStruct 指向 @ref FL_VREFP_InitTypeDef 结构体的指针
  *
  * @retval ErrorStatus枚举值
  *         -FL_PASS 配置成功
  *         -FL_FAIL 配置过程发生错误
  */
FL_ErrorStatus FL_VREFP_Init(VREFP_Type *VREFPx, FL_VREFP_InitTypeDef *VREFP_InitStruct)
{
    FL_ErrorStatus status = FL_PASS;
    /* 入口参数检查 */
    assert_param(IS_VREFP_INSTANCE(VREFPx));
    assert_param(IS_FL_VREFP_VOLTAGETRIM(VREFP_InitStruct->voltageTrim));
    assert_param(IS_FL_VREFP_OUTPUTVOLTAGE(VREFP_InitStruct->outputVoltage));
    assert_param(IS_FL_VREFP_ENABLEPERIOD(VREFP_InitStruct->timeOfPeriod));
    assert_param(IS_FL_VREFP_DRIVINGTIME(VREFP_InitStruct->timeOfDriving));
    assert_param(IS_FL_VREFP_WORKMODE(VREFP_InitStruct->mode));
    /* 开启总线时钟 */
    FL_CMU_EnableGroup1BusClock(FL_CMU_GROUP1_BUSCLK_PMU);
    /* 配置VREFP输出电压TRIM值 */
    FL_VREFP_WriteOutputVoltageTrim(VREFPx, VREFP_InitStruct->voltageTrim);
    /* 配置VREFP输出电压 */
    FL_VREFP_SetOutputVoltage(VREFPx, VREFP_InitStruct->outputVoltage);
    /* 配置输出模式 */
    FL_VREFP_SetWorkMode(VREFPx, VREFP_InitStruct->mode);
    /* 间歇模式下使能周期 */
    FL_VREFP_SetEnablePeriod(VREFPx, VREFP_InitStruct->timeOfPeriod);
    /* 间歇模式下单次驱动时间 */
    FL_VREFP_SetDrivingTime(VREFPx, VREFP_InitStruct->timeOfDriving);
    /* 启动VREFP */
    FL_VREFP_Enable(VREFPx);
    return status;
}
/**
  * @brief  设置 VREFP_InitStruct 为默认配置
  *
  * @param  VREFP_InitStruct 指向需要将值设置为默认配置的结构体 @ref FL_VREFP_InitTypeDef 结构体
  *
  * @retval None
  */
void FL_VREFP_StructInit(FL_VREFP_InitTypeDef *VREFP_InitStruct)
{
    VREFP_InitStruct->voltageTrim = FL_VREFP_OUTPUT_VOLTAGE_3P0V_TRIM;
    VREFP_InitStruct->outputVoltage = FL_VREFP_OUTPUT_VOLTAGE_3P0V;
    VREFP_InitStruct->mode = FL_VREFP_WORK_MODE_CONTINUOUS;
    VREFP_InitStruct->timeOfPeriod = FL_VREFP_ENABLE_PERIOD_1MS;
    VREFP_InitStruct->timeOfDriving = FL_VREFP_DRIVING_TIME_4LSCLK;
}

/**
  * @}
  */

#endif /* FL_VREFP_DRIVER_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/*************************(C) COPYRIGHT Fudan Microelectronics **** END OF FILE*************************/

