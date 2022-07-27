/**
  *******************************************************************************************************
  * @file    fm33lc0xx_fl_dma.c
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
#include "fm33lc0xx_fl.h"

/** @addtogroup FM33LC0XX_FL_Driver
  * @{
  */

/** @addtogroup DMA
  * @{
  */

#ifdef FL_DMA_DRIVER_ENABLED

/* Private macros ------------------------------------------------------------*/
/** @addtogroup DMA_FL_Private_Macros
  * @{
  */

#define         IS_FL_DMA_INSTANCE(INTANCE)                         ((INTANCE) == DMA)

#define         IS_FL_DMA_PRIORITY(__VALUE__)                       (((__VALUE__) == FL_DMA_PRIORITY_LOW)||\
                                                                     ((__VALUE__) == FL_DMA_PRIORITY_MEDIUM)||\
                                                                     ((__VALUE__) == FL_DMA_PRIORITY_HIGH)||\
                                                                     ((__VALUE__) == FL_DMA_PRIORITY_VERYHIGH))

#define         IS_FL_DMA_CIRC_MODE(__VALUE__)                      (((__VALUE__) == FL_DISABLE)||\
                                                                     ((__VALUE__) == FL_ENABLE))


#define         IS_FL_DMA_DIRECTION(__VALUE__)                      (((__VALUE__) == FL_DMA_DIR_PERIPHERAL_TO_RAM)||\
                                                                     ((__VALUE__) == FL_DMA_DIR_RAM_TO_PERIPHERAL)||\
                                                                     ((__VALUE__) == FL_DMA_DIR_FLASH_TO_RAM)||\
                                                                     ((__VALUE__) == FL_DMA_DIR_RAM_TO_FLASH))


#define         IS_FL_DMA_DATA_SIZE(__VALUE__)                      (((__VALUE__) == FL_DMA_BANDWIDTH_8B)||\
                                                                     ((__VALUE__) == FL_DMA_BANDWIDTH_32B)||\
                                                                     ((__VALUE__) == FL_DMA_BANDWIDTH_16B))

#define         IS_FL_DMA_INCMODE(__VALUE__)                       (((__VALUE__) == FL_DMA_MEMORY_INC_MODE_INCREASE)||\
                                                                    ((__VALUE__) == FL_DMA_MEMORY_INC_MODE_DECREASE) ||\
                                                                    ((__VALUE__) == FL_DMA_CH7_MEMORY_INC_MODE_INCREASE)||\
                                                                    ((__VALUE__) == FL_DMA_CH7_MEMORY_INC_MODE_DECREASE)||\
                                                                    ((__VALUE__) == FL_DMA_CH7_FLASH_INC_MODE_INCREASE)||\
                                                                    ((__VALUE__) == FL_DMA_CH7_FLASH_INC_MODE_DECREASE))

#define         IS_FL_DMA_PERIPH(__VALUE__)                        (((__VALUE__) == FL_DMA_PERIPHERAL_FUNCTION1)||\
                                                                    ((__VALUE__) == FL_DMA_PERIPHERAL_FUNCTION2)||\
                                                                    ((__VALUE__) == FL_DMA_PERIPHERAL_FUNCTION3)||\
                                                                    ((__VALUE__) == FL_DMA_PERIPHERAL_FUNCTION4)||\
                                                                    ((__VALUE__) == FL_DMA_PERIPHERAL_FUNCTION5)||\
                                                                    ((__VALUE__) == FL_DMA_PERIPHERAL_FUNCTION6)||\
                                                                    ((__VALUE__) == FL_DMA_PERIPHERAL_FUNCTION7)||\
                                                                    ((__VALUE__) == FL_DMA_PERIPHERAL_FUNCTION8))
/**
  * @}
  */

/** @addtogroup DMA_FL_EF_Init
  * @{
  */

/**
  * @brief  复位DMA相关寄存器
  * @param  DMAx 外设入口地址
  * @retval 错误状态，可能值
  *         -FL_PASS 外设寄存器值恢复复位值
  *         -FL_FAIL 未成功执行
  */
FL_ErrorStatus FL_DMA_DeInit(DMA_Type *DMAx)
{
    assert_param(IS_FL_DMA_INSTANCE(DMAx));
    /* 使能外设复位 */
    FL_RCC_EnablePeripheralReset();
    /* 复位外设寄存器 */
    FL_RCC_EnableResetAHBPeripheral(FL_RCC_RSTAHB_DMA);
    FL_RCC_DisableResetAHBPeripheral(FL_RCC_RSTAHB_DMA);
    /* 关闭外设总线始时钟和工作时钟 */
    FL_RCC_DisableGroup2BusClock(FL_RCC_GROUP2_BUSCLK_DMA);
    /* 锁定外设复位 */
    FL_RCC_DisablePeripheralReset();
    return FL_PASS;
}

/**
  * @brief  根据 initStruct 的配置信息初始化对应外设入口地址的寄存器值.
  * @param  DMAx 外设入口地址
  * @param  initStruct 指向一个 @ref FL_DMA_InitTypeDef 结构体
  *         其中包含了外设的相关配置信息.
  * @param  Channel 此参数可取以下值：
  *           @arg @ref FL_DMA_CHANNEL_0
  *           @arg @ref FL_DMA_CHANNEL_1
  *           @arg @ref FL_DMA_CHANNEL_2
  *           @arg @ref FL_DMA_CHANNEL_3
  *           @arg @ref FL_DMA_CHANNEL_4
  *           @arg @ref FL_DMA_CHANNEL_5
  *           @arg @ref FL_DMA_CHANNEL_6
  *           @arg @ref FL_DMA_CHANNEL_7
  * @retval 错误状态，可能值：
  *         -FL_FAIL 配置过程发生错误
  *         -FL_PASS 配置成功
  */
FL_ErrorStatus FL_DMA_Init(DMA_Type *DMAx, FL_DMA_InitTypeDef *initStruct, uint32_t channel)
{
    /* 参数检查 */
    assert_param(IS_FL_DMA_INSTANCE(DMAx));
    assert_param(IS_FL_DMA_PRIORITY(initStruct->priority));
    assert_param(IS_FL_DMA_CIRC_MODE(initStruct->circMode));
    assert_param(IS_FL_DMA_DIRECTION(initStruct->direction));
    assert_param(IS_FL_DMA_DATA_SIZE(initStruct->dataSize));
    assert_param(IS_FL_DMA_INCMODE(initStruct->memoryAddressIncMode));
    /* 开启时钟 */
    FL_RCC_EnableGroup2BusClock(FL_RCC_GROUP2_BUSCLK_DMA);
    /* 配置通道优先级 */
    FL_DMA_SetPriority(DMAx, initStruct->priority, channel);
    /* RAM地址方向 */
    FL_DMA_SetMemoryIncrementMode(DMAx, initStruct->memoryAddressIncMode, channel);
    /* 传输方向 */
    FL_DMA_SetTransmissionDirection(DMAx, initStruct->direction, channel);
    /* 数据宽度 */
    FL_DMA_SetBandwidth(DMAx, initStruct->dataSize, channel);
    /* 循环模式 */
    if(initStruct->circMode == FL_ENABLE)
    {
        FL_DMA_EnableCircularMode(DMAx, channel);
        if(channel == FL_DMA_CHANNEL_7)
        {
            return FL_FAIL;
        }
    }
    else
    {
        FL_DMA_DisableCircularMode(DMAx, channel);
    }
    /* 如果是通道7 外设地址实际就是FLASH地址，因此这里针对通道7做了单独处理 */
    if(channel != FL_DMA_CHANNEL_7)
    {
        assert_param(IS_FL_DMA_PERIPH(initStruct->periphAddress));
        FL_DMA_SetPeripheralMap(DMAx, initStruct->periphAddress, channel);
    }
    else
    {
        /* Flash地址方向 */
        FL_DMA_SetFlashIncrementMode(DMAx, initStruct->flashAddressIncMode);
    }
    return FL_PASS;
}

/**
  * @brief  将 @ref FL_DMA_InitTypeDef 结构体初始化为默认配置
  * @param  initStruct 指向需要将值设置为默认配置的结构体 @ref FL_DMA_InitTypeDef 结构体
  *
  * @retval None
  */
void FL_DMA_StructInit(FL_DMA_InitTypeDef *initStruct)
{
    initStruct->circMode                = FL_DISABLE;
    initStruct->dataSize                = FL_DMA_BANDWIDTH_8B;
    initStruct->direction               = FL_DMA_DIR_PERIPHERAL_TO_RAM;
    initStruct->periphAddress           = FL_DMA_PERIPHERAL_FUNCTION1;
    initStruct->priority                = FL_DMA_PRIORITY_LOW;
    initStruct->memoryAddressIncMode    = FL_DMA_MEMORY_INC_MODE_INCREASE;
}

/**
  *@}
  */

/** @addtogroup DMA_FL_EF_Operation
  * @{
  */

/**
  * @brief  启动一次DMA传输.
  * @param  DMAx 外设入口地址
  * @param  configStruct 指向一个 @ref FL_DMA_ConfigTypeDef 结构体
  *         其中包含了外设的相关配置信息.
  * @param  channel 此参数可取以下值:
  *           @arg @ref FL_DMA_CHANNEL_0
  *           @arg @ref FL_DMA_CHANNEL_1
  *           @arg @ref FL_DMA_CHANNEL_2
  *           @arg @ref FL_DMA_CHANNEL_3
  *           @arg @ref FL_DMA_CHANNEL_4
  *           @arg @ref FL_DMA_CHANNEL_5
  *           @arg @ref FL_DMA_CHANNEL_6
  *           @arg @ref FL_DMA_CHANNEL_7
  * @retval 错误状态，可能值：
  *         -FL_FAIL 配置过程发生错误可能是超时也可能是地址非法
  *         -FL_PASS 配置成功
  */
FL_ErrorStatus FL_DMA_StartTransmission(DMA_Type *DMAx, FL_DMA_ConfigTypeDef *configStruct, uint32_t channel)
{
    /* 配置传输个数 */
    FL_DMA_WriteTransmissionSize(DMAx, configStruct->transmissionCount, channel);
    /* 配置Memory地址 */
    FL_DMA_WriteMemoryAddress(DMAx, configStruct->memoryAddress, channel);
    /* 清除DMA通道中断标志位 */
    FL_DMA_ClearFlag_TransferHalfComplete(DMAx, channel);
    FL_DMA_ClearFlag_TransferComplete(DMAx, channel);
    /* 使能DMA通道使能开关 */
    FL_DMA_EnableChannel(DMAx, channel);
    return FL_PASS;
}

/**
  * @}
  */

#endif /* FL_DMA_DRIVER_ENABLED */

/**
  * @}
  */

/**
  * @}
  */


/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
