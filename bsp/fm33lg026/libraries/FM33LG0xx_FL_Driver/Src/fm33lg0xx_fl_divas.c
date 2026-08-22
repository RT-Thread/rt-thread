/**
  *******************************************************************************************************
  * @file    fm33lg0xx_fl_divas.c
  * @author  FMSH Application Team
  * @brief   Src file of DIVAS FL Module
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

/** @addtogroup DIVAS
  * @{
  */

#ifdef FL_DIVAS_DRIVER_ENABLED

/* Private macros ------------------------------------------------------------*/
/** @addtogroup DIVAS_FL_Private_Macros
  * @{
  */
#define         IS_DIVAS_ALL_INSTANCE(INTENCE)              ((INTENCE) == DIVAS)

#define         IS_FL_DIVAS_DIVISOR(__VALUE__)              (((__VALUE__) != 0))

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup DIVAS_FL_EF_Init
  * @{
  */

/**
  * @brief  复位对应HDIV控制寄存器.
  *
  * @param  DIVASx 外设入口地址
  *
  * @retval FL_ErrorStatus枚举值
  *         -FL_PASS 配置成功
  *         -FL_FAIL 配置过程发生错误
  */
FL_ErrorStatus FL_DIVAS_DeInit(DIVAS_Type *DIVASx)
{
    /* 入口参数检查 */
    assert_param(IS_DIVAS_ALL_INSTANCE(DIVASx));
    /* 外设复位使能 */
    FL_RMU_EnablePeripheralReset(RMU);
    /* 恢复寄存器值为默认值 */
    FL_RMU_EnableResetAPBPeripheral(RMU, FL_RMU_RSTAPB_DIVAS);
    FL_RMU_DisableResetAPBPeripheral(RMU, FL_RMU_RSTAPB_DIVAS);
    /* 关闭总线时钟 */
    FL_CMU_DisableGroup2BusClock(FL_CMU_GROUP2_BUSCLK_DIVAS);
    /* 锁定外设复位功能 */
    FL_RMU_DisablePeripheralReset(RMU);
    return FL_PASS;
}

/**
  * @brief  根据 初始化对应外设DIVAS.
  *
  * @param  DIVASx 外设入口地址
  *
  * @retval FL_ErrorStatus枚举值
  *         -FL_PASS 配置成功
  *         -FL_FAIL 配置过程发生错误
  */
FL_ErrorStatus FL_DIVAS_Init(DIVAS_Type *DIVASx)
{
    /* 入口参数检查 */
    assert_param(IS_DIVAS_ALL_INSTANCE(DIVASx));
    /* 使能时钟总线 */
    FL_CMU_EnableGroup2BusClock(FL_CMU_GROUP2_BUSCLK_DIVAS);
    return FL_PASS;
}
/**
  * @brief 硬件除法器计算函数
  *
  * @param  DIVASx 外设入口地址
  * @param  DivisorEnd 32位有符号被除数
  * @param  Divisor 16位有符号除数，注意不能为0
  * @param  Quotient 指向 @ref int32_t 指针 保存商的地址
  * @param  Residue 指向 @ref int16_t 指针 保存余数的地址
  *
  * @retval 计算正确性与否
  *         -0 计算结果正确
  *         -非0 计算过程发生错误
  */
uint32_t FL_DIVAS_Hdiv_Calculation(DIVAS_Type *DIVASx, int32_t DivisorEnd, int16_t Divisor, int32_t *Quotient, int16_t *Residue)
{
    uint32_t  TimeOut ;
    FL_DIVAS_SetMode(DIVASx, FL_DIVAS_MODE_DIV);
    FL_DIVAS_WriteOperand(DIVASx, (uint32_t)DivisorEnd);
    FL_DIVAS_WriteDivisor(DIVASx, (uint32_t)Divisor);
    if(FL_DIVAS_IsActiveFlag_DividedZero(DIVASx))
    {
        /*除数为0 */
        *Quotient = 0;
        *Residue  = 0;
        return 1;
    }
    TimeOut = FL_DIVAS_SR_BUSY_TIMEOUT;
    while(FL_DIVAS_IsActiveFlag_Busy(DIVASx))
    {
        TimeOut--;
        if(TimeOut == 0)
        {
            /* 计算超时*/
            *Quotient = 0;
            *Residue  = 0;
            return 3;
        }
    }
    *Quotient = FL_DIVAS_ReadQuotient(DIVASx);
    *Residue  = FL_DIVAS_ReadResidue(DIVASx);
    return 0;
}

/**
  * @brief 硬件开方计算函数
  *
  * @param  DIVASx 外设入口地址
  * @param  Root 32bit被开方数
  * @param  Result 指向 @ref int16_t 指针 保存结果开方根
  *
  * @retval 计算正确性与否
  *         -0 计算结果正确
  *         -非0 计算过程发生错误
  */
uint32_t FL_DIVAS_Root_Calculation(DIVAS_Type *DIVASx, uint32_t Root, uint16_t *Result)
{
    uint32_t  TimeOut ;
    FL_DIVAS_SetMode(DIVASx, FL_DIVAS_MODE_ROOT);
    FL_DIVAS_WriteOperand(DIVASx, Root);
    TimeOut = FL_DIVAS_SR_BUSY_TIMEOUT;
    while(FL_DIVAS_IsActiveFlag_Busy(DIVASx))
    {
        TimeOut --;
        if(TimeOut == 0)
        {
            /* 计算超时*/
            *Result = 0;
            return 1;
        }
    }
    *Result = FL_DIVAS_ReadRoot(DIVASx);
    return 0;
}

/**
  * @}
  */

#endif /* FL_DIVAS_DRIVER_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/

