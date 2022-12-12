/**
  *******************************************************************************************************
  * @file    fm33lc0xx_fl_divas.c
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
#include "fm33lc0xx_fl.h"

/** @addtogroup FM33LC0XX_FL_Driver
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
#define         IS_DIVAS_ALL_INSTANCE(INTENCE)              ((INTENCE) == DIV)

#define         IS_FL_DIVAS_DIVISOR(__VALUE__)              (((__VALUE__) != 0))

/**
  * @}
  */

/** @addtogroup DIVAS_FL_EF_Init
  * @{
  */

/**
  * @brief  复位DIVAS外设
  *
  * @param  DIVx 外设入口地址
  *
  * @retval 错误状态，可能值：
  *         -FL_PASS 外设寄存器值恢复复位值
  *         -FL_FAIL 未成功执行
  */
FL_ErrorStatus FL_DIVAS_DeInit(DIV_Type *DIVx)
{
    /* 入口参数检查 */
    assert_param(IS_DIVAS_ALL_INSTANCE(DIVx));
    /* 外设复位使能 */
    FL_RCC_EnablePeripheralReset();
    /* 恢复寄存器值为默认值 */
    FL_RCC_EnableResetAPB2Peripheral(FL_RCC_RSTAPB_DIVAS);
    FL_RCC_DisableResetAPB2Peripheral(FL_RCC_RSTAPB_DIVAS);
    /* 关闭总线时钟 */
    FL_RCC_DisableGroup2BusClock(FL_RCC_GROUP2_BUSCLK_HDIV);
    /* 锁定外设复位功能 */
    FL_RCC_DisablePeripheralReset();
    return FL_PASS;
}

/**
  * @brief  配置DIVAS外设的DIV模块
  *
  * @param  DIVx 外设入口地址
  *
  * @retval 错误状态，可能值：
  *         -FL_PASS 配置成功
  *         -FL_FAIL 配置过程发生错误
  */
FL_ErrorStatus FL_DIVAS_Init(DIV_Type *DIVx)
{
    /* 入口参数检查 */
    assert_param(IS_DIVAS_ALL_INSTANCE(DIVx));
    /* 使能时钟总线 */
    FL_RCC_EnableGroup2BusClock(FL_RCC_GROUP2_BUSCLK_HDIV);
    return FL_PASS;
}

/**
  * @}
  */

/** @addtogroup DIVAS_FL_EF_Operation
  * @{
  */

/**
  * @brief 硬件除法器计算
  *
  * @param  DIVx        外设入口地址
  * @param  DivisorEnd  32位有符号被除数
  * @param  Divisor     16位有符号除数，注意不能为0
  * @param  Quotient    指向 @ref int32_t 指针 保存商的地址
  * @param  Residue     指向 @ref int16_t 指针 保存余数的地址
  *
  * @retval 计算正确性与否
  *         -0   计算结果正确
  *         -非0 计算过程发生错误
  */
uint32_t FL_DIVAS_Hdiv_Calculation(DIV_Type *DIVx, int32_t DivisorEnd, int16_t Divisor, int32_t *Quotient, int16_t *Residue)
{
    uint32_t  TimeOut ;
    FL_DIV_WriteDividend_S32(DIVx, DivisorEnd);
    FL_DIV_WriteDivisor_S16(DIVx, Divisor);
    if(FL_DIV_IsActiveFlag_DividedZero(DIVx))
    {
        /*除数为0 */
        *Quotient = 0;
        *Residue  = 0;
        return 1;
    }
    TimeOut = FL_DIVAS_SR_BUSY_TIMEOUT;
    while(FL_DIV_IsActiveFlag_Busy(DIVx))
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
    *Quotient = FL_DIV_ReadQuotient_S32(DIVx);
    *Residue  = FL_DIV_ReadResidue_S16(DIVx);
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
