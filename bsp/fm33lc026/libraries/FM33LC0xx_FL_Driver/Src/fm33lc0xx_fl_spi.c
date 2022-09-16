/**
  *******************************************************************************************************
  * @file    fm33lc0xx_fl_spi.c
  * @author  FMSH Application Team
  * @brief   Src file of SPI FL Module
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

/** @addtogroup SPI
  * @{
  */

#ifdef FL_SPI_DRIVER_ENABLED

/* Private macros ------------------------------------------------------------*/
/** @addtogroup Private_Macros
  * @{
  */
#define         IS_FL_SPI_INSTANCE(INTANCE)                     (((INTANCE) == SPI1)||\
                                                                 ((INTANCE) == SPI2))

#define         IS_FL_SPI_MODE(__VALUE__)                       (((__VALUE__) == FL_SPI_WORK_MODE_SLAVE)||\
                                                                 ((__VALUE__) == FL_SPI_WORK_MODE_MASTER))

#define         IS_FL_SPI_BITORDER(__VALUE__)                   (((__VALUE__) == FL_SPI_BIT_ORDER_MSB_FIRST)||\
                                                                 ((__VALUE__) == FL_SPI_BIT_ORDER_LSB_FIRST))

#define         IS_FL_SPI_DATAWIDT(__VALUE__)                   (((__VALUE__) == FL_SPI_DATA_WIDTH_8B)||\
                                                                 ((__VALUE__) == FL_SPI_DATA_WIDTH_16B)||\
                                                                 ((__VALUE__) == FL_SPI_DATA_WIDTH_24B)||\
                                                                 ((__VALUE__) == FL_SPI_DATA_WIDTH_32B))

#define         IS_FL_SPI_CLOCK_PHASE(__VALUE__)                (((__VALUE__) == FL_SPI_PHASE_EDGE1)||\
                                                                 ((__VALUE__) == FL_SPI_PHASE_EDGE2))

#define         IS_FL_SPI_CLOCK_POLARITY(__VALUE__)             (((__VALUE__) == FL_SPI_POLARITY_NORMAL)||\
                                                                 ((__VALUE__) == FL_SPI_POLARITY_INVERT))

#define         IS_FL_SPI_BAUDRATE(__VALUE__)                   (((__VALUE__) == FL_SPI_BAUDRATE_DIV2)||\
                                                                 ((__VALUE__) == FL_SPI_BAUDRATE_DIV4)||\
                                                                 ((__VALUE__) == FL_SPI_BAUDRATE_DIV8)||\
                                                                 ((__VALUE__) == FL_SPI_BAUDRATE_DIV16)||\
                                                                 ((__VALUE__) == FL_SPI_BAUDRATE_DIV32)||\
                                                                 ((__VALUE__) == FL_SPI_BAUDRATE_DIV64)||\
                                                                 ((__VALUE__) == FL_SPI_BAUDRATE_DIV128)||\
                                                                 ((__VALUE__) == FL_SPI_BAUDRATE_DIV256))


#define         IS_FL_SPI_TANSFERMODE(__VALUE__)                (((__VALUE__) == FL_SPI_TRANSFER_MODE_FULL_DUPLEX)||\
                                                                 ((__VALUE__) == FL_SPI_TRANSFER_MODE_HALF_DUPLEX))


/**
  * @}
  */

/** @addtogroup SPI_FL_EF_Init
  * @{
  */

/**
  * @brief  复位SPI
  * @param  SPIx 外设入口地址
  * @retval 错误状态，可能值：
  *         -FL_PASS 外设寄存器值恢复复位值
  *         -FL_FAIL 未成功执行
  */
FL_ErrorStatus FL_SPI_DeInit(SPI_Type *SPIx)
{
    assert_param(IS_FL_SPI_INSTANCE(SPIx));
    /* 使能外设复位 */
    FL_RCC_EnablePeripheralReset();
    if(SPIx == SPI1)
    {
        /* 复位SPI外设寄存器 */
        FL_RCC_EnableResetAPB2Peripheral(FL_RCC_RSTAPB_SPI1);
        FL_RCC_DisableResetAPB2Peripheral(FL_RCC_RSTAPB_SPI1);
        /* 关闭外设总线时钟和工作时钟 */
        FL_RCC_DisableGroup3BusClock(FL_RCC_GROUP3_BUSCLK_SPI1);
    }
    else
        if(SPIx == SPI2)
        {
            /* 复位SPI外设寄存器 */
            FL_RCC_EnableResetAPB1Peripheral(FL_RCC_RSTAPB_SPI2);
            FL_RCC_DisableResetAPB1Peripheral(FL_RCC_RSTAPB_SPI2);
            /* 关闭外设总线时钟和工作时钟 */
            FL_RCC_DisableGroup3BusClock(FL_RCC_GROUP3_BUSCLK_SPI2);
        }
        else
        {
            FL_RCC_DisablePeripheralReset();
            return FL_FAIL;
        }
    /* 锁定外设复位 */
    FL_RCC_DisablePeripheralReset();
    return FL_PASS;
}

/**
  * @brief  配置SPI
  * @param  SPIx 外设入口地址
  * @param  initStruct 指向 @ref FL_SPI_InitTypeDef 结构体的指针
  * @retval 错误状态，可能值：
  *         -FL_PASS 配置成功
  *         -FL_FAIL 配置过程发生错误
  */
FL_ErrorStatus FL_SPI_Init(SPI_Type *SPIx, FL_SPI_InitTypeDef *initStruct)
{
    assert_param(IS_FL_SPI_INSTANCE(SPIx));
    assert_param(IS_FL_SPI_MODE(initStruct->mode));
    assert_param(IS_FL_SPI_BITORDER(initStruct->bitOrder));
    assert_param(IS_FL_SPI_DATAWIDT(initStruct->dataWidth));
    assert_param(IS_FL_SPI_BAUDRATE(initStruct->baudRate));
    assert_param(IS_FL_SPI_CLOCK_PHASE(initStruct->clockPhase));
    assert_param(IS_FL_SPI_CLOCK_POLARITY(initStruct->clockPolarity));
    if(SPIx == SPI1)
    {
        /* 外设总线时钟 */
        FL_RCC_EnableGroup3BusClock(FL_RCC_GROUP3_BUSCLK_SPI1);
    }
    else
        if(SPIx == SPI2)
        {
            /* 外设总线时钟 */
            FL_RCC_EnableGroup3BusClock(FL_RCC_GROUP3_BUSCLK_SPI2);
        }
        else
        {
            return FL_FAIL;
        }
    /* 选择NSS脚控制模式 */
    if(initStruct->softControl == FL_ENABLE)
    {
        FL_SPI_EnableSSNSoftControl(SPIx);
    }
    else
    {
        FL_SPI_DisableSSNSoftControl(SPIx);
    }
    /* 外设工作主从模式 */
    FL_SPI_SetWorkMode(SPIx, initStruct->mode);
    /* 总线通讯速率 */
    FL_SPI_SetClockDivision(SPIx, initStruct->baudRate);
    /* 数据bit方向 */
    FL_SPI_SetBitOrder(SPIx, initStruct->bitOrder);
    /* 总线数据位宽 */
    FL_SPI_SetDataWidth(SPIx, initStruct->dataWidth);
    /* 时钟相位 */
    FL_SPI_SetClockPhase(SPIx, initStruct->clockPhase);
    /* 传输模式 双工半双工  */
    FL_SPI_SetTransferMode(SPIx, initStruct->transferMode);
    /* 时钟极性 */
    FL_SPI_SetClockPolarity(SPIx, initStruct->clockPolarity);
    /* 使能 外设*/
    FL_SPI_Enable(SPIx);
    return FL_PASS;
}

/**
  * @brief  将 @ref FL_SPI_InitTypeDef 结构体初始化为默认配置
  * @param  initStruct 指向 @ref FL_SPI_InitTypeDef 结构体的指针
  *
  * @retval None
  */
void FL_SPI_StructInit(FL_SPI_InitTypeDef *initStruct)
{
    initStruct->softControl         =   FL_DISABLE;
    initStruct->mode                =   FL_SPI_WORK_MODE_MASTER;
    initStruct->baudRate            =   FL_SPI_CLK_DIV8;
    initStruct->bitOrder            =   FL_SPI_BIT_ORDER_MSB_FIRST;
    initStruct->dataWidth           =   FL_SPI_DATA_WIDTH_8B;
    initStruct->clockPolarity       =   FL_SPI_POLARITY_NORMAL;
    initStruct->clockPhase          =   FL_SPI_PHASE_EDGE1;
    initStruct->transferMode        =   FL_SPI_TRANSFER_MODE_FULL_DUPLEX;
}

/**
  * @}
  */

#endif /* FL_SPI_DRIVER_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
