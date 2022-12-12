/**
  *******************************************************************************************************
  * @file    fm33lc0xx_fl_i2c.c
  * @author  FMSH Application Team
  * @brief   Src file of I2C FL Module
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

/** @addtogroup I2C
  * @{
  */

#ifdef FL_I2C_DRIVER_ENABLED

/* Private macros ------------------------------------------------------------*/
/** @addtogroup I2C_FL_Private_Macros
  * @{
  */

#define         IS_FL_I2C_INSTANCE(INSTANCE)                    ((INSTANCE) == I2C)

#define         IS_FL_I2C_BAUDRATE(__VALUE__)                   (((__VALUE__) > 0 )&&((__VALUE__) <= 1000000))

#define         IS_FL_I2C_CLOCKSRC(__VALUE__)                   (((__VALUE__) == FL_RCC_I2C_CLK_SOURCE_APB1CLK )||\
                                                                 ((__VALUE__) == FL_RCC_I2C_CLK_SOURCE_RCHF)||\
                                                                 ((__VALUE__) == FL_RCC_I2C_CLK_SOURCE_SYSCLK)||\
                                                                 ((__VALUE__) == FL_RCC_I2C_CLK_SOURCE_RCMF_PSC ))

#define         IS_FL_I2C_MSATER_TIMEOUT(__VALUE__)             (((__VALUE__) == FL_IWDT_PERIOD_125MS)||\
                                                                 ((__VALUE__) == FL_IWDT_PERIOD_16000MS))


#define         IS_FL_I2C_SLAVE_ACK(__VALUE__)                  (((__VALUE__) == FL_ENABLE)||\
                                                                 ((__VALUE__) == FL_DISABLE))



#define         IS_FL_I2C_ANGLOGFILTER(__VALUE__)               (((__VALUE__) == FL_ENABLE)||\
                                                                 ((__VALUE__) == FL_DISABLE))

#define         IS_FL_I2C_ADDRSIZE10BIT(__VALUE__)              (((__VALUE__) == FL_ENABLE)||\
                                                                 ((__VALUE__) == FL_DISABLE))

#define         IS_FL_I2C_SLAVE_SCLSEN(__VALUE__)               (((__VALUE__) == FL_ENABLE)||\
                                                                 ((__VALUE__) == FL_DISABLE))

/**
  * @}
  */

/** @addtogroup I2C_FL_EF_Init
  * @{
  */

/**
  * @brief  复位I2C外设.
  * @param  I2Cx 外设入口地址
  * @retval 错误状态，可能值：
  *         -FL_PASS 外设寄存器值恢复复位值
  *         -FL_FAIL 未成功执行
  */
FL_ErrorStatus FL_I2C_DeInit(I2C_Type *I2Cx)
{
    assert_param(IS_FL_I2C_INSTANCE(I2Cx));
    /* 使能外设复位 */
    FL_RCC_EnablePeripheralReset();
    /* 复位I2C外设寄存器 */
    FL_RCC_EnableResetAPB1Peripheral(FL_RCC_RSTAPB_I2C);
    FL_RCC_DisableResetAPB1Peripheral(FL_RCC_RSTAPB_I2C);
    /* 关闭外设总线始时钟和工作时钟 */
    FL_RCC_DisableGroup3BusClock(FL_RCC_GROUP3_BUSCLK_I2C);
    FL_RCC_DisableGroup1OperationClock(FL_RCC_GROUP1_OPCLK_I2C);
    /* 锁定外设复位 */
    FL_RCC_DisablePeripheralReset();
    return FL_PASS;
}

/**
  * @brief  配置I2C主机模式.
  * @param  I2Cx 外设入口地址
  * @param  I2C_InitStruct 指向 @ref FL_I2C_MasterMode_InitTypeDef 结构体的指针
  * @retval 错误状态，可能值：
  *         -FL_PASS 配置成功
  *         -FL_FAIL 配置过程发生错误
  */
FL_ErrorStatus FL_I2C_MasterMode_Init(I2C_Type *I2Cx, FL_I2C_MasterMode_InitTypeDef *I2C_InitStruct)
{
    uint32_t I2C_Clk_Freq = 0, BRG = 0;
    assert_param(IS_FL_I2C_INSTANCE(I2Cx));
    assert_param(IS_FL_I2C_CLOCKSRC(I2C_InitStruct->clockSource));
    assert_param(IS_FL_I2C_BAUDRATE(I2C_InitStruct->baudRate));
    /* 外设总线时钟和工作时钟开启 */
    FL_RCC_EnableGroup3BusClock(FL_RCC_GROUP3_BUSCLK_I2C);
    FL_RCC_EnableGroup1OperationClock(FL_RCC_GROUP1_OPCLK_I2C);
    /* 选择I2C工作时钟源 */
    FL_RCC_SetI2CClockSource(I2C_InitStruct->clockSource);
    /* 获取时钟源速度 */
    switch(I2C_InitStruct->clockSource)
    {
        case FL_RCC_I2C_CLK_SOURCE_APB1CLK:
            I2C_Clk_Freq = FL_RCC_GetAPB1ClockFreq();
            break;
        case FL_RCC_I2C_CLK_SOURCE_RCHF:
            I2C_Clk_Freq = FL_RCC_GetRCHFClockFreq();
            break;
        case FL_RCC_I2C_CLK_SOURCE_SYSCLK:
            I2C_Clk_Freq = FL_RCC_GetSystemClockFreq();
            break;
        case FL_RCC_I2C_CLK_SOURCE_RCMF_PSC:
            I2C_Clk_Freq = FL_RCC_GetRCMFClockFreq();
            break;
        default:
            break;
    }
    /* 根据不同的时钟源速度计算出配置速率需要的寄存器值并配置相关寄存器 */
    BRG = (uint32_t)(I2C_Clk_Freq / (2 * I2C_InitStruct->baudRate)) - 1;
    FL_I2C_Master_WriteSCLHighWidth(I2Cx, BRG);
    FL_I2C_Master_WriteSCLLowWidth(I2Cx, BRG);
    FL_I2C_Master_WriteSDAHoldTime(I2Cx, (uint32_t)(BRG / 2.0 + 0.5));
    /* 使能外设 */
    FL_I2C_Master_Enable(I2C);
    return FL_PASS;
}

/**
  * @brief  将 @ref FL_I2C_MasterMode_InitTypeDef 结构体初始化为默认配置
  * @param  I2C_InitStruct 指向 @ref FL_I2C_MasterMode_InitTypeDef 结构体的指针
  *
  * @retval None
  */
void FL_I2C_MasterMode_StructInit(FL_I2C_MasterMode_InitTypeDef *I2C_InitStruct)
{
    I2C_InitStruct->clockSource = FL_RCC_I2C_CLK_SOURCE_RCHF;
    I2C_InitStruct->baudRate = 40000;
}

/**
  * @brief  配置I2C从机模式.
  * @param  I2Cx 外设入口地址
  * @param  I2C_InitStruct 指向 @ref FL_I2C_SlaveMode_InitTypeDef 结构体的指针.
  * @note   作为从机时的从机地址应参考手册推荐具体设置
  * @retval 错误状态，可能值：
  *         -FL_PASS 配置成功
  *         -FL_FAIL 配置过程发生错误
  */
FL_ErrorStatus FL_I2C_SlaveMode_Init(I2C_Type *I2Cx, FL_I2C_SlaveMode_InitTypeDef *I2C_InitStruct)
{
    assert_param(IS_FL_I2C_INSTANCE(I2Cx));
    assert_param(IS_FL_I2C_SLAVE_ACK(I2C_InitStruct->ACK));
    assert_param(IS_FL_I2C_ADDRSIZE10BIT(I2C_InitStruct->ownAddrSize10bit));
    assert_param(IS_FL_I2C_SLAVE_SCLSEN(I2C_InitStruct->SCLSEN));
    /* 外设总线时钟开启 注：不需要工作时钟*/
    FL_RCC_EnableGroup3BusClock(FL_RCC_GROUP3_BUSCLK_I2C);
    /* 使能SDA输出延迟 注：推荐开启*/
    FL_I2C_Slave_EnableSDAStretching(I2Cx);
    /* 使能SCL模拟滤波使能 注：推荐开启*/
    FL_I2C_Slave_EnableSCLAnalogFilter(I2Cx);
    /* 从机ACK */
    if(I2C_InitStruct->ACK == FL_ENABLE)
    {
        FL_I2C_Slave_EnableACK(I2Cx);
    }
    else
    {
        FL_I2C_Slave_DisableACK(I2Cx);
    }
    /* 从机地址宽度  和地址配置 */
    if(I2C_InitStruct->ownAddrSize10bit == FL_ENABLE)
    {
        FL_I2C_Slave_Enable10BitAddress(I2Cx);
        FL_I2C_Slave_WriteSlaveAddress(I2Cx, I2C_InitStruct->ownAddr);
    }
    else
    {
        FL_I2C_Slave_Disable10BitAddress(I2Cx);
        FL_I2C_Slave_WriteSlaveAddress(I2Cx, I2C_InitStruct->ownAddr & 0x7F);
    }
    /* 从机时钟延展使能 */
    if(I2C_InitStruct->SCLSEN == FL_ENABLE)
    {
        FL_I2C_Slave_EnableSCLStretching(I2Cx);
    }
    else
    {
        FL_I2C_Slave_DisableSCLStretching(I2Cx);
    }
    /* 外设开启 */
    FL_I2C_Slave_Enable(I2Cx);
    return FL_PASS;
}

/**
  * @brief  将 @ref FL_I2C_SlaveMode_InitTypeDef 结构体初始化为默认配置
  * @param  I2C_InitStruct 指向 @ref FL_I2C_SlaveMode_InitTypeDef 结构体的指针
  *
  * @retval None
  */

void FL_I2C_SlaveMode_StructInit(FL_I2C_SlaveMode_InitTypeDef *I2C_InitStruct)
{
    I2C_InitStruct->ACK                 = FL_ENABLE;
    I2C_InitStruct->ownAddr             = 0x55;
    I2C_InitStruct->ownAddrSize10bit    = FL_DISABLE;
    I2C_InitStruct->SCLSEN              = FL_DISABLE;
}

/**
  * @}
  */

#endif /* FL_I2C_DRIVER_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
