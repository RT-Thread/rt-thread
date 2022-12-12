/**
  ****************************************************************************************************
  * @file    fm33lc0xx_fl_uart.c
  * @author  FMSH Application Team
  * @brief   Src file of UART FL Module
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

/** @addtogroup UART
  * @{
  */

#ifdef FL_UART_DRIVER_ENABLED

/* Private macros ------------------------------------------------------------*/
/** @addtogroup UART_FL_Private_Macros
  * @{
  */


#define         IS_UART_INSTANCE(INSTANCE)              (((INSTANCE) == UART0)||\
                                                         ((INSTANCE) == UART1)||\
                                                         ((INSTANCE) == UART4)||\
                                                         ((INSTANCE) == UART5))

#define         IS_FL_UART_CLKSRC(__VALUE__)            (((__VALUE__) == FL_RCC_UART1_CLK_SOURCE_APB1CLK)||\
                                                         ((__VALUE__) == FL_RCC_UART1_CLK_SOURCE_RCHF)||\
                                                         ((__VALUE__) == FL_RCC_UART1_CLK_SOURCE_SYSCLK)||\
                                                         ((__VALUE__) == FL_RCC_UART1_CLK_SOURCE_RCMF_PSC)||\
                                                         ((__VALUE__) == FL_RCC_UART0_CLK_SOURCE_APB1CLK)||\
                                                         ((__VALUE__) == FL_RCC_UART0_CLK_SOURCE_RCHF)||\
                                                         ((__VALUE__) == FL_RCC_UART0_CLK_SOURCE_SYSCLK)||\
                                                         ((__VALUE__) == FL_RCC_UART0_CLK_SOURCE_RCMF_PSC))


#define         IS_FL_UART_DATAWIDTH(__VALUE__)           (((__VALUE__) == FL_UART_DATA_WIDTH_7B)||\
                                                           ((__VALUE__) == FL_UART_DATA_WIDTH_8B)||\
                                                           ((__VALUE__) == FL_UART_DATA_WIDTH_9B)||\
                                                           ((__VALUE__) == FL_UART_DATA_WIDTH_6B))

#define         IS_FL_UART_STOPBITS(__VALUE__)            (((__VALUE__) == FL_UART_STOP_BIT_WIDTH_1B)||\
                                                           ((__VALUE__) == FL_UART_STOP_BIT_WIDTH_2B))

#define         IS_FL_UART_PARITY(__VALUE__)              (((__VALUE__) == FL_UART_PARITY_NONE)||\
                                                           ((__VALUE__) == FL_UART_PARITY_EVEN)||\
                                                           ((__VALUE__) == FL_UART_PARITY_ODD))

#define         IS_FL_UART_DIRECTION(__VALUE__)           (((__VALUE__) == FL_UART_DIRECTION_NONE)||\
                                                           ((__VALUE__) == FL_UART_DIRECTION_RX)||\
                                                           ((__VALUE__) == FL_UART_DIRECTION_TX)||\
                                                           ((__VALUE__) == FL_UART_DIRECTION_TX_RX))

#define         IS_FL_UART_INFRA_MODULATION(__VALUE__)    (((__VALUE__) == FL_DISABLE)||\
                                                           ((__VALUE__) == FL_ENABLE))


#define         IS_FL_UART_INFRARED_POLARITY(__VALUE__)        (((__VALUE__) == FL_UART_INFRARED_POLARITY_NORMAL)||\
                                                                ((__VALUE__) == FL_UART_INFRARED_POLARITY_INVERT))

#define         IS_FL_UART_INFRARED_MODULATION_DUTY(__VALUE__) (((__VALUE__) <= 100))


/**
  * @}
  */

/** @addtogroup UART_FL_EF_Init
  * @{
  */

/**
  * @brief  复位UART外设
  * @param  UARTx 外设入口地址
  * @retval 错误状态，可能值:
  *         -FL_PASS 外设寄存器值恢复复位值
  *         -FL_FAIL 复位未成功
  */
FL_ErrorStatus FL_UART_DeInit(UART_Type *UARTx)
{
    FL_ErrorStatus status = FL_PASS;
    /* 参数入口合法性 */
    assert_param(IS_UART_INSTANCE(UARTx));
    /* 外设复位使能 */
    FL_RCC_EnablePeripheralReset();
    if(UARTx == UART0)
    {
        /*复位UART*/
        FL_RCC_EnableResetAPB2Peripheral(FL_RCC_RSTAPB_UART0);
        FL_RCC_DisableResetAPB2Peripheral(FL_RCC_RSTAPB_UART0);
        /* 外设总线时钟关闭 */
        FL_RCC_DisableGroup3BusClock(FL_RCC_GROUP3_BUSCLK_UART0);
        /* 外设操作时钟关闭 */
        FL_RCC_DisableGroup1OperationClock(FL_RCC_GROUP1_OPCLK_UART0);
    }
    else
        if(UARTx == UART1)
        {
            /*复位UART*/
            FL_RCC_EnableResetAPB2Peripheral(FL_RCC_RSTAPB_UART1);
            FL_RCC_DisableResetAPB2Peripheral(FL_RCC_RSTAPB_UART1);
            /* 外设总线时钟关闭 */
            FL_RCC_DisableGroup3BusClock(FL_RCC_GROUP3_BUSCLK_UART1);
            /* 外设操作时钟关闭 */
            FL_RCC_DisableGroup1OperationClock(FL_RCC_GROUP1_OPCLK_UART1);
        }
        else
            if(UARTx == UART4)
            {
                /*复位UART*/
                FL_RCC_EnableResetAPB1Peripheral(FL_RCC_RSTAPB_UART4);
                FL_RCC_DisableResetAPB1Peripheral(FL_RCC_RSTAPB_UART4);
                /* 外设总线时钟关闭 */
                FL_RCC_DisableGroup3BusClock(FL_RCC_GROUP3_BUSCLK_UART4);
            }
            else
                if(UARTx == UART5)
                {
                    /*复位UART*/
                    FL_RCC_EnableResetAPB1Peripheral(FL_RCC_RSTAPB_UART5);
                    FL_RCC_DisableResetAPB1Peripheral(FL_RCC_RSTAPB_UART5);
                    /* 外设总线时钟关闭 */
                    FL_RCC_DisableGroup3BusClock(FL_RCC_GROUP3_BUSCLK_UART5);
                }
                else
                {
                    status = FL_FAIL;
                }
    /* 锁定外设复位功能 */
    FL_RCC_DisablePeripheralReset();
    return (status);
}

/**
  * @brief  配置UART
  *
  * @param  UARTx  外设入口地址
  * @param  initStruct 指向 @ref FL_UART_InitTypeDef 结构体的指针
  *
  * @retval 错误状态，可能值：
  *         -FL_PASS 配置成功
  *         -FL_FAIL 配置过程发生错误
  */
FL_ErrorStatus FL_UART_Init(UART_Type *UARTx, FL_UART_InitTypeDef *initStruct)
{
    FL_ErrorStatus status = FL_FAIL;
    uint32_t Fclk = 0, baudRate = 0;
    /* 参数合法性检查 */
    assert_param(IS_UART_INSTANCE(UARTx));
    assert_param(IS_FL_UART_CLKSRC(initStruct->clockSrc));
    assert_param(IS_FL_UART_DATAWIDTH(initStruct->dataWidth));
    assert_param(IS_FL_UART_PARITY(initStruct->parity));
    assert_param(IS_FL_UART_STOPBITS(initStruct->stopBits));
    assert_param(IS_FL_UART_DIRECTION(initStruct->transferDirection));
    if(UARTx == UART0)
    {
        /*时钟源选择*/
        FL_RCC_SetUART0ClockSource(initStruct->clockSrc);
        /* 根据不同的时钟源计算baudrate 寄存器值,并配置 */
        switch(initStruct->clockSrc)
        {
            case FL_RCC_UART0_CLK_SOURCE_APB1CLK:
                Fclk = FL_RCC_GetAPB1ClockFreq();
                break;
            case FL_RCC_UART0_CLK_SOURCE_RCHF:
                Fclk = FL_RCC_GetRCHFClockFreq();
                break;
            case FL_RCC_UART0_CLK_SOURCE_SYSCLK:
                Fclk = FL_RCC_GetSystemClockFreq();
                break;
            case FL_RCC_UART0_CLK_SOURCE_RCMF_PSC:
                Fclk = FL_RCC_GetRCMFClockFreq();
                break;
        }
        baudRate = Fclk / initStruct->baudRate - 1;
    }
    if(UARTx == UART1)
    {
        /*时钟源选择*/
        FL_RCC_SetUART1ClockSource(initStruct->clockSrc);
        /* 根据不同的时钟源计算baudrate 寄存器值,并配置 */
        switch(initStruct->clockSrc)
        {
            case FL_RCC_UART1_CLK_SOURCE_APB1CLK:
                Fclk = FL_RCC_GetAPB1ClockFreq();
                break;
            case FL_RCC_UART1_CLK_SOURCE_RCHF:
                Fclk = FL_RCC_GetRCHFClockFreq();
                break;
            case FL_RCC_UART1_CLK_SOURCE_SYSCLK:
                Fclk = FL_RCC_GetSystemClockFreq();
                break;
            case FL_RCC_UART1_CLK_SOURCE_RCMF_PSC:
                Fclk = FL_RCC_GetRCMFClockFreq();
                break;
        }
        baudRate = Fclk / initStruct->baudRate - 1;
    }
    if(UARTx == UART0)
    {
        /*总线时钟使能*/
        FL_RCC_EnableGroup3BusClock(FL_RCC_GROUP3_BUSCLK_UART0);
        /*操作时钟使能*/
        FL_RCC_EnableGroup1OperationClock(FL_RCC_GROUP1_OPCLK_UART0);
    }
    else
        if(UARTx == UART1)
        {
            /*总线时钟使能*/
            FL_RCC_EnableGroup3BusClock(FL_RCC_GROUP3_BUSCLK_UART1);
            /*操作时钟使能*/
            FL_RCC_EnableGroup1OperationClock(FL_RCC_GROUP1_OPCLK_UART1);
        }
        else
            if(UARTx == UART4)
            {
                /*总线时钟使能*/
                FL_RCC_EnableGroup3BusClock(FL_RCC_GROUP3_BUSCLK_UART4);
                Fclk = FL_RCC_GetAPB2ClockFreq();
                baudRate = Fclk / initStruct->baudRate - 1;
            }
            else
                if(UARTx == UART5)
                {
                    FL_RCC_EnableGroup3BusClock(FL_RCC_GROUP3_BUSCLK_UART5);
                    Fclk = FL_RCC_GetAPB2ClockFreq();
                    baudRate = Fclk / initStruct->baudRate - 1;
                }
    /*发送接收控制*/
    if(initStruct->transferDirection & FL_UART_DIRECTION_TX)
    {
        FL_UART_EnableTX(UARTx);
    }
    if(initStruct->transferDirection & FL_UART_DIRECTION_RX)
    {
        FL_UART_EnableRX(UARTx);
    }
    /*配置波特率*/
    FL_UART_WriteBaudRate(UARTx, baudRate);
    /*配置停止位长度*/
    FL_UART_SetStopBitsWidth(UARTx, initStruct->stopBits);
    /*数据长度*/
    FL_UART_SetDataWidth(UARTx, initStruct->dataWidth);
    /*配置奇偶校验*/
    FL_UART_SetParity(UARTx, initStruct->parity);
    status = FL_PASS;
    return status;
}

/**
  * @brief  配置UART红外调制
  *
  * @param  UARTx 外设入口地址
  *
  * @param  initStruct 指向 @ref FL_UART_InfraRed_InitTypeDef 结构体的指针
  *
  * @retval 错误状态，可能值：
  *         -FL_PASS 配置成功
  *         -FL_FAIL 配置过程发生错误
  */
FL_ErrorStatus FL_UART_InfraRed_Init(UART_Type *UARTx, FL_UART_InfraRed_InitTypeDef *initStruct)
{
    FL_ErrorStatus status = FL_FAIL;
    uint32_t  tempTZBRG = 0, tempTH = 0;
    /* 参数合法性检查 */
    assert_param(IS_UART_INSTANCE(UARTx));
    assert_param(IS_FL_UART_INFRARED_POLARITY(initStruct->polarity));
    assert_param(IS_FL_UART_INFRARED_MODULATION_DUTY(initStruct->modulationDuty));
    FL_RCC_EnableGroup3BusClock(FL_RCC_GROUP3_BUSCLK_UARTIR);
    /*红外发送使能*/
    FL_UART_EnableIRModulation(UARTx);
    /*红外调制极性*/
    FL_UART_SetIRPolarity(UART, initStruct->polarity);
    /*红外调制频率*/
    tempTZBRG = (uint32_t)((FL_RCC_GetAPB1ClockFreq() * 1.0) / initStruct->modulationFrequency - 1);
    /* 调制占空比 */
    if((tempTZBRG >> 4) != 0)
    {
        tempTH = (uint32_t)(((float)initStruct->modulationDuty / 100.0) * ((float)(tempTZBRG + 1) / (float)(tempTZBRG >> 4)) + 0.5);
    }
    else
    {
        tempTH = (uint32_t)(((float)initStruct->modulationDuty / 100.0) * (float)(tempTZBRG + 1) + 0.5);
    }
    /* 占空比限位到小于95%，否则结果会有问题 */
    tempTH = ((float)((tempTZBRG >> 4) * tempTH) / (float)(tempTZBRG + 1)) < 0.95f ? tempTH : tempTH - 1;
    /* 占空比和调制频率配置 */
    FL_UART_WriteIRModulationDuty(UART, tempTH);
    FL_UART_WriteIRModulationFrequency(UART, tempTZBRG);
    status = FL_PASS;
    return status;
}

/**
  * @brief  将 @ref FL_UART_InfraRed_InitTypeDef 结构体初始化为默认配置
  * @param  initStruct 指向 @ref FL_UART_InfraRed_InitTypeDef 结构体的指针
  *
  * @retval None
  */
void FL_UART_InfraRed_StructInit(FL_UART_InfraRed_InitTypeDef *initStruct)
{
    initStruct->polarity                  = FL_UART_INFRARED_POLARITY_NORMAL;
    initStruct->modulationDuty            = 50;
    initStruct->modulationFrequency       = 38000;
}

/**
  * @brief  将 @ref FL_UART_InitTypeDef 结构体初始化为默认配置
  * @param  initStruct 指向 @ref FL_UART_InitTypeDef 结构体的指针
  *
  * @retval None
  */
void FL_UART_StructInit(FL_UART_InitTypeDef *initStruct)
{
    initStruct->baudRate            = 115200;
    initStruct->dataWidth           = FL_UART_DATA_WIDTH_8B;
    initStruct->stopBits            = FL_UART_STOP_BIT_WIDTH_1B;
    initStruct->parity              = FL_UART_PARITY_EVEN ;
    initStruct->transferDirection   = FL_UART_DIRECTION_TX_RX;
    initStruct->clockSrc            = 0;
}

/**
  * @}
  */

#endif /* FL_UART_DRIVER_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
