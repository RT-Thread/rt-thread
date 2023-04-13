/*!
 * @file        apm32f0xx_dma.c
 *
 * @brief       This file contains all the functions for the DMA peripheral
 *
 * @version     V1.0.3
 *
 * @date        2022-09-20
 *
 * @attention
 *
 *  Copyright (C) 2020-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be useful and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

/* Includes */
#include "apm32f0xx_dma.h"

/** @addtogroup APM32F0xx_StdPeriphDriver
  @{
*/

/** @addtogroup DMA_Driver
  @{
*/

/** @defgroup DMA_Macros Macros
  @{
  */

/**@} end of group DMA_Macros */

/** @defgroup DMA_Enumerates Enumerates
  @{
  */

/**@} end of group DMA_Enumerates */

/** @defgroup DMA_Structures Structures
  @{
  */

/**@} end of group DMA_Structures */

/** @defgroup DMA_Variables Variables
  @{
  */

/**@} end of group DMA_Variables */

/** @defgroup DMA_Functions Functions
  @{
  */

/*!
 * @brief     Set the DMA peripheral registers to their default reset values
 *
 * @param     DMA_CHANNEL_T:  Pointer to a DMA_CHANNEL_T structure that
 *                          set DMA channel for the DMA peripheral
 *                          This parameter can be one of the following values:
 *                           @arg DMA1_CHANNEL_1
 *                           @arg DMA1_CHANNEL_2
 *                           @arg DMA1_CHANNEL_3
 *                           @arg DMA1_CHANNEL_4
 *                           @arg DMA1_CHANNEL_5
 *                           @arg DMA1_CHANNEL_6(only for APM32F072 and APM32F091)
 *                           @arg DMA1_CHANNEL_7(only for APM32F072 and APM32F091)
 *                           @arg DMA2_CHANNEL_1(only for APM32F091)
 *                           @arg DMA2_CHANNEL_2(only for APM32F091)
 *                           @arg DMA2_CHANNEL_3(only for APM32F091)
 *                           @arg DMA2_CHANNEL_4(only for APM32F091)
 *                           @arg DMA2_CHANNEL_5(only for APM32F091)
 * @retval    None
 */
void DMA_Reset(DMA_CHANNEL_T* channel)
{
    channel->CHCFG_B.CHEN = 0;
    channel->CHCFG = 0;
    channel->CHNDATA = 0;
    channel->CHPADDR = 0;
    channel->CHMADDR = 0;

    if (channel == DMA1_CHANNEL_1)
    {
        DMA1->INTFCLR = (uint32_t)0x0000000F;
    }
    else if (channel == DMA1_CHANNEL_2)
    {
        DMA1->INTFCLR = (uint32_t)0x000000F0;
    }
    else if (channel == DMA1_CHANNEL_3)
    {
        DMA1->INTFCLR = (uint32_t)0x00000F00;
    }
    else if (channel == DMA1_CHANNEL_4)
    {
        DMA1->INTFCLR = (uint32_t)0x0000F000;
    }
    else if (channel == DMA1_CHANNEL_5)
    {
        DMA1->INTFCLR = (uint32_t)0x000F0000;
    }
    else if (channel == DMA1_CHANNEL_6)
    {
        DMA1->INTFCLR = (uint32_t)0x00F00000;
    }
    else if (channel == DMA1_CHANNEL_7)
    {
        DMA1->INTFCLR = (uint32_t)0x0F000000;
    }
    else if (channel == DMA2_CHANNEL_1)
    {
        DMA2->INTFCLR = (uint32_t)0x0000000F;
    }
    else if (channel == DMA2_CHANNEL_2)
    {
        DMA2->INTFCLR = (uint32_t)0x000000F0;
    }
    else if (channel == DMA2_CHANNEL_3)
    {
        DMA2->INTFCLR = (uint32_t)0x00000F00;
    }
    else if (channel == DMA2_CHANNEL_4)
    {
        DMA2->INTFCLR = (uint32_t)0x0000F000;
    }
    else if (channel == DMA2_CHANNEL_5)
    {
        DMA2->INTFCLR = (uint32_t)0x000F0000;
    }
}

/*!
 * @brief       Config the DMA peripheral according to the specified parameters in the dmaConfig
 *
 * @param     DMA_CHANNEL_T:  Pointer to a DMA_CHANNEL_T structure that
 *                          set DMA channel for the DMA peripheral
 *                          This parameter can be one of the following values:
 *                           @arg DMA1_CHANNEL_1
 *                           @arg DMA1_CHANNEL_2
 *                           @arg DMA1_CHANNEL_3
 *                           @arg DMA1_CHANNEL_4
 *                           @arg DMA1_CHANNEL_5
 *                           @arg DMA1_CHANNEL_6(only for APM32F072 and APM32F091)
 *                           @arg DMA1_CHANNEL_7(only for APM32F072 and APM32F091)
 *                           @arg DMA2_CHANNEL_1(only for APM32F091)
 *                           @arg DMA2_CHANNEL_2(only for APM32F091)
 *                           @arg DMA2_CHANNEL_3(only for APM32F091)
 *                           @arg DMA2_CHANNEL_4(only for APM32F091)
 *                           @arg DMA2_CHANNEL_5(only for APM32F091)
 *
 * @param       dmaConfig:  Pointer to a DMA_Config_T structure that
 *                          contains the configuration information for the DMA peripheral
 *
 * @retval      None
 */
void DMA_Config(DMA_CHANNEL_T* channel, DMA_Config_T* dmaConfig)
{
    channel->CHCFG_B.DIRCFG   = dmaConfig->direction;
    channel->CHCFG_B.CIRMODE  = dmaConfig->circular;
    channel->CHCFG_B.M2MMODE  = dmaConfig->memoryTomemory;
    channel->CHCFG_B.CHPL     = dmaConfig->priority;
    channel->CHCFG_B.MIMODE   = dmaConfig->memoryInc;
    channel->CHCFG_B.PERIMODE = dmaConfig->peripheralInc;
    channel->CHCFG_B.MSIZE    = dmaConfig->memoryDataSize;
    channel->CHCFG_B.PERSIZE  = dmaConfig->peripheralDataSize;

    channel->CHNDATA = dmaConfig->bufferSize;
    channel->CHMADDR = dmaConfig->memoryAddress;
    channel->CHPADDR = dmaConfig->peripheralAddress;

}

/*!
 * @brief       Fills each dmaConfig member with its default value
 *
 * @param       dmaConfig:  Pointer to a DMA_Config_T structure which will be initialized
 *
 * @retval      None
 */
void DMA_ConfigStructInit(DMA_Config_T* dmaConfig)
{
    dmaConfig->direction = DMA_DIR_PERIPHERAL;
    dmaConfig->circular = DMA_CIRCULAR_DISABLE;
    dmaConfig->memoryTomemory = DMA_M2M_DISABLE;
    dmaConfig->priority = DMA_PRIORITY_LEVEL_LOW;
    dmaConfig->memoryInc = DMA_MEMORY_INC_DISABLE;
    dmaConfig->peripheralInc = DMA_PERIPHERAL_INC_DISABLE;
    dmaConfig->memoryDataSize = DMA_MEMORY_DATASIZE_BYTE;
    dmaConfig->peripheralDataSize = DMA_PERIPHERAL_DATASIZE_BYTE;

    dmaConfig->bufferSize = 0;
    dmaConfig->memoryAddress = 0;
    dmaConfig->peripheralAddress = 0;
}

/*!
 * @brief       Enable the DMA peripheral
 *
 * @param       DMA_CHANNEL_T:  Pointer to a DMA_CHANNEL_T structure that
 *                          set DMA channel for the DMA peripheral
 *                          This parameter can be one of the following values:
 *                           @arg DMA1_CHANNEL_1
 *                           @arg DMA1_CHANNEL_2
 *                           @arg DMA1_CHANNEL_3
 *                           @arg DMA1_CHANNEL_4
 *                           @arg DMA1_CHANNEL_5
 *                           @arg DMA1_CHANNEL_6(only for APM32F072 and APM32F091)
 *                           @arg DMA1_CHANNEL_7(only for APM32F072 and APM32F091)
 *                           @arg DMA2_CHANNEL_1(only for APM32F091)
 *                           @arg DMA2_CHANNEL_2(only for APM32F091)
 *                           @arg DMA2_CHANNEL_3(only for APM32F091)
 *                           @arg DMA2_CHANNEL_4(only for APM32F091)
 *                           @arg DMA2_CHANNEL_5(only for APM32F091)
 *
 * @retval      None
 */
void DMA_Enable(DMA_CHANNEL_T* channel)
{
    channel->CHCFG_B.CHEN = BIT_SET;
}

/*!
 * @brief       Disable the DMA peripheral
 *
 * @param       DMA_CHANNEL_T:  Pointer to a DMA_CHANNEL_T structure that
 *                          set DMA channel for the DMA peripheral
 *                          This parameter can be one of the following values:
 *                           @arg DMA1_CHANNEL_1
 *                           @arg DMA1_CHANNEL_2
 *                           @arg DMA1_CHANNEL_3
 *                           @arg DMA1_CHANNEL_4
 *                           @arg DMA1_CHANNEL_5
 *                           @arg DMA1_CHANNEL_6(only for APM32F072 and APM32F091)
 *                           @arg DMA1_CHANNEL_7(only for APM32F072 and APM32F091)
 *                           @arg DMA2_CHANNEL_1(only for APM32F091)
 *                           @arg DMA2_CHANNEL_2(only for APM32F091)
 *                           @arg DMA2_CHANNEL_3(only for APM32F091)
 *                           @arg DMA2_CHANNEL_4(only for APM32F091)
 *                           @arg DMA2_CHANNEL_5(only for APM32F091)
 *
 * @retval      None
 */
void DMA_Disable(DMA_CHANNEL_T* channel)
{
    channel->CHCFG_B.CHEN = BIT_RESET;
}

/*!
 * @brief       Set the DMA Channelx transfer data of number
 *
 * @param       DMA_CHANNEL_T:  Pointer to a DMA_CHANNEL_T structure that
 *                          set DMA channel for the DMA peripheral
 *                          This parameter can be one of the following values:
 *                           @arg DMA1_CHANNEL_1
 *                           @arg DMA1_CHANNEL_2
 *                           @arg DMA1_CHANNEL_3
 *                           @arg DMA1_CHANNEL_4
 *                           @arg DMA1_CHANNEL_5
 *                           @arg DMA1_CHANNEL_6(only for APM32F072 and APM32F091)
 *                           @arg DMA1_CHANNEL_7(only for APM32F072 and APM32F091)
 *                           @arg DMA2_CHANNEL_1(only for APM32F091)
 *                           @arg DMA2_CHANNEL_2(only for APM32F091)
 *                           @arg DMA2_CHANNEL_3(only for APM32F091)
 *                           @arg DMA2_CHANNEL_4(only for APM32F091)
 *                           @arg DMA2_CHANNEL_5(only for APM32F091)
 *
 * @param       dataNumber:  The number of data units in the current DMA Channel transfer
 *
 * @retval      None
 */
void DMA_SetDataNumber(DMA_CHANNEL_T* channel, uint32_t dataNumber)
{
    channel->CHNDATA = (uint32_t)dataNumber;
}

/*!
 * @brief       Read the DMA Channelx transfer data of number
 *
 * @param       DMA_CHANNEL_T:  Pointer to a DMA_CHANNEL_T structure that
 *                          set DMA channel for the DMA peripheral
 *                          This parameter can be one of the following values:
 *                           @arg DMA1_CHANNEL_1
 *                           @arg DMA1_CHANNEL_2
 *                           @arg DMA1_CHANNEL_3
 *                           @arg DMA1_CHANNEL_4
 *                           @arg DMA1_CHANNEL_5
 *                           @arg DMA1_CHANNEL_6(only for APM32F072 and APM32F091)
 *                           @arg DMA1_CHANNEL_7(only for APM32F072 and APM32F091)
 *                           @arg DMA2_CHANNEL_1(only for APM32F091)
 *                           @arg DMA2_CHANNEL_2(only for APM32F091)
 *                           @arg DMA2_CHANNEL_3(only for APM32F091)
 *                           @arg DMA2_CHANNEL_4(only for APM32F091)
 *                           @arg DMA2_CHANNEL_5(only for APM32F091)
 *
 * @retval      The number of data units in the current DMA Channel transfer
 */
uint32_t DMA_ReadDataNumber(DMA_CHANNEL_T* channel)
{
    return ((uint32_t)channel->CHNDATA);
}

/*!
 * @brief       Configure the DMA channels remapping.
 *
 * @param       dma:   Select the the DMA peripheral.
                       It can be DMA1/DMA2.
 *
 * @param       remap: Select the the DMA_CHANNEL_REMAP_T.
                       When select DMA1, the DMA channel can be 1 to 7.
 *                     When select DMA2, the DMA channel can be 1 to 5.
 *
 * @retval      It's only for APM32F091 devices.
 */
void DMA_ConfigRemap(DMA_T* dma, DMA_CHANNEL_REMAP_T remap)
{
    dma->CHSEL &= ~((uint32_t)0x0F << (uint32_t)(remap >> 28) * 4);
    dma->CHSEL |= (uint32_t)(remap & 0x0FFFFFFF);
}

/*!
 * @brief       Enables the specified interrupts
 * @param       DMA_CHANNEL_T:  Pointer to a DMA_CHANNEL_T structure that
 *                          set DMA channel for the DMA peripheral
 *                          This parameter can be one of the following values:
 *                           @arg DMA1_CHANNEL_1
 *                           @arg DMA1_CHANNEL_2
 *                           @arg DMA1_CHANNEL_3
 *                           @arg DMA1_CHANNEL_4
 *                           @arg DMA1_CHANNEL_5
 *                           @arg DMA1_CHANNEL_6(only for APM32F072 and APM32F091)
 *                           @arg DMA1_CHANNEL_7(only for APM32F072 and APM32F091)
 *                           @arg DMA2_CHANNEL_1(only for APM32F091)
 *                           @arg DMA2_CHANNEL_2(only for APM32F091)
 *                           @arg DMA2_CHANNEL_3(only for APM32F091)
 *                           @arg DMA2_CHANNEL_4(only for APM32F091)
 *                           @arg DMA2_CHANNEL_5(only for APM32F091)
 *
 * @param       interrupt:  Specifies the DMA interrupts sources
 *                          The parameter can be combination of following values:
 *                          @arg DMA_INT_TFIE:    Transfer complete interrupt
 *                          @arg DMA_INT_HTIE:    Half Transfer interrupt
 *                          @arg DMA_INT_TEIE:    Transfer error interrupt
 *
 * @retval      None
 */
void DMA_EnableInterrupt(DMA_CHANNEL_T* channel, uint32_t interrupt)
{
    channel->CHCFG |= (uint32_t)interrupt;
}

/*!
 * @brief       Disables the specified interrupts
 * @param       DMA_CHANNEL_T:  Pointer to a DMA_CHANNEL_T structure that
 *                          set DMA channel for the DMA peripheral
 *                          This parameter can be one of the following values:
 *                           @arg DMA1_CHANNEL_1
 *                           @arg DMA1_CHANNEL_2
 *                           @arg DMA1_CHANNEL_3
 *                           @arg DMA1_CHANNEL_4
 *                           @arg DMA1_CHANNEL_5
 *                           @arg DMA1_CHANNEL_6(only for APM32F072 and APM32F091)
 *                           @arg DMA1_CHANNEL_7(only for APM32F072 and APM32F091)
 *                           @arg DMA2_CHANNEL_1(only for APM32F091)
 *                           @arg DMA2_CHANNEL_2(only for APM32F091)
 *                           @arg DMA2_CHANNEL_3(only for APM32F091)
 *                           @arg DMA2_CHANNEL_4(only for APM32F091)
 *                           @arg DMA2_CHANNEL_5(only for APM32F091)
 *
 * @param       interrupt:  Specifies the DMA interrupts sources
 *                          The parameter can be combination of following values:
 *                           @arg DMA_INT_TFIE:    Transfer complete interrupt
 *                           @arg DMA_INT_HTIE:    Half Transfer interrupt
 *                           @arg DMA_INT_TEIE:    Transfer error interrupt
 *
 * @retval      None
 */
void DMA_DisableInterrupt(DMA_CHANNEL_T* channel, uint32_t interrupt)
{
    channel->CHCFG &= (uint32_t)~interrupt;
}

/*!
 * @brief       Checks whether the specified DMA flag is set or not
 *
 * @param       flag:   Specifies the flag to check
 *                      This parameter can be one of the following values:
 *                      @arg DMA1_FLAG_AL1:   DMA1 Channel 1 All flag
 *                      @arg DMA1_FLAG_TF1:   DMA1 Channel 1 Transfer Complete flag
 *                      @arg DMA1_FLAG_HT1:   DMA1 Channel 1 Half Transfer Complete flag
 *                      @arg DMA1_FLAG_TE1:   DMA1 Channel 1 Transfer Error flag
 *                      @arg DMA1_FLAG_AL2:   DMA1 Channel 2 All flag
 *                      @arg DMA1_FLAG_TF2:   DMA1 Channel 2 Transfer Complete flag
 *                      @arg DMA1_FLAG_HT2:   DMA1 Channel 2 Half Transfer Complete flag
 *                      @arg DMA1_FLAG_TE2:   DMA1 Channel 2 Transfer Error flag
 *                      @arg DMA1_FLAG_AL3:   DMA1 Channel 3 All flag
 *                      @arg DMA1_FLAG_TF3:   DMA1 Channel 3 Transfer Complete flag
 *                      @arg DMA1_FLAG_HT3:   DMA1 Channel 3 Half Transfer Complete flag
 *                      @arg DMA1_FLAG_TE3:   DMA1 Channel 3 Transfer Error flag
 *                      @arg DMA1_FLAG_AL4:   DMA1 Channel 4 All flag
 *                      @arg DMA1_FLAG_TF4:   DMA1 Channel 4 Transfer Complete flag
 *                      @arg DMA1_FLAG_HT4:   DMA1 Channel 4 Half Transfer Complete flag
 *                      @arg DMA1_FLAG_TE4:   DMA1 Channel 4 Transfer Error flag
 *                      @arg DMA1_FLAG_AL5:   DMA1 Channel 5 All flag
 *                      @arg DMA1_FLAG_TF5:   DMA1 Channel 5 Transfer Complete flag
 *                      @arg DMA1_FLAG_HT5:   DMA1 Channel 5 Half Transfer Complete flag
 *                      @arg DMA1_FLAG_TE5:   DMA1 Channel 5 Transfer Error flag
 *                      Below is only for APM32F072 and APM32F091 devices:
 *                      @arg DMA1_FLAG_AL6:   DMA1 Channel 6 All flag
 *                      @arg DMA1_FLAG_TF6:   DMA1 Channel 6 Transfer Complete flag
 *                      @arg DMA1_FLAG_HT6:   DMA1 Channel 6 Half Transfer Complete flag
 *                      @arg DMA1_FLAG_TE6:   DMA1 Channel 6 Transfer Error flag
 *                      @arg DMA1_FLAG_AL7:   DMA1 Channel 7 All flag
 *                      @arg DMA1_FLAG_TF7:   DMA1 Channel 7 Transfer Complete flag
 *                      @arg DMA1_FLAG_HT7:   DMA1 Channel 7 Half Transfer Complete flag
 *                      @arg DMA1_FLAG_TE7:   DMA1 Channel 7 Transfer Error flag
 *                      Below is only for APM32F091 devices:
 *                      @arg DMA2_FLAG_AL1:   DMA2 Channel 1 All flag
 *                      @arg DMA2_FLAG_TF1:   DMA2 Channel 1 Transfer Complete flag
 *                      @arg DMA2_FLAG_HT1:   DMA2 Channel 1 Half Transfer Complete flag
 *                      @arg DMA2_FLAG_TE1:   DMA2 Channel 1 Transfer Error flag
 *                      @arg DMA2_FLAG_AL2:   DMA2 Channel 2 All flag
 *                      @arg DMA2_FLAG_TF2:   DMA2 Channel 2 Transfer Complete flag
 *                      @arg DMA2_FLAG_HT2:   DMA2 Channel 2 Half Transfer Complete flag
 *                      @arg DMA2_FLAG_TE2:   DMA2 Channel 2 Transfer Error flag
 *                      @arg DMA2_FLAG_AL3:   DMA2 Channel 3 All flag
 *                      @arg DMA2_FLAG_TF3:   DMA2 Channel 3 Transfer Complete flag
 *                      @arg DMA2_FLAG_HT3:   DMA2 Channel 3 Half Transfer Complete flag
 *                      @arg DMA2_FLAG_TE3:   DMA2 Channel 3 Transfer Error flag
 *                      @arg DMA2_FLAG_AL4:   DMA2 Channel 4 All flag
 *                      @arg DMA2_FLAG_TF4:   DMA2 Channel 4 Transfer Complete flag
 *                      @arg DMA2_FLAG_HT4:   DMA2 Channel 4 Half Transfer Complete flag
 *                      @arg DMA2_FLAG_TE4:   DMA2 Channel 4 Transfer Error flag
 *                      @arg DMA2_FLAG_AL5:   DMA2 Channel 5 All flag
 *                      @arg DMA2_FLAG_TF5:   DMA2 Channel 5 Transfer Complete flag
 *                      @arg DMA2_FLAG_HT5:   DMA2 Channel 5 Half Transfer Complete flag
 *                      @arg DMA2_FLAG_TE5:   DMA2 Channel 5 Transfer Error flag
 *
 * @retval      The new state of flag (SET or RESET)
 */
uint8_t DMA_ReadStatusFlag(DMA_FLAG_T flag)
{
    uint32_t status;

    if ((flag & 0x10000000) == SET)
    {
        status = DMA2->INTSTS & ((uint32_t)flag & 0x000FFFFF);
    }
    else
    {
        status = DMA1->INTSTS & ((uint32_t)flag & 0x0FFFFFFF);
    }

    if (status == flag)
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief       Clear whether the specified DMA flag is set or not
 *
 * @param       flag:   Specifies the flag to Clear
 *                      This parameter can be any combination of the following values:
 *                      @arg DMA1_FLAG_AL1:   DMA1 Channel 1 All flag
 *                      @arg DMA1_FLAG_TF1:   DMA1 Channel 1 Transfer Complete flag
 *                      @arg DMA1_FLAG_HT1:   DMA1 Channel 1 Half Transfer Complete flag
 *                      @arg DMA1_FLAG_TE1:   DMA1 Channel 1 Transfer Error flag
 *                      @arg DMA1_FLAG_AL2:   DMA1 Channel 2 All flag
 *                      @arg DMA1_FLAG_TF2:   DMA1 Channel 2 Transfer Complete flag
 *                      @arg DMA1_FLAG_HT2:   DMA1 Channel 2 Half Transfer Complete flag
 *                      @arg DMA1_FLAG_TE2:   DMA1 Channel 2 Transfer Error flag
 *                      @arg DMA1_FLAG_AL3:   DMA1 Channel 3 All flag
 *                      @arg DMA1_FLAG_TF3:   DMA1 Channel 3 Transfer Complete flag
 *                      @arg DMA1_FLAG_HT3:   DMA1 Channel 3 Half Transfer Complete flag
 *                      @arg DMA1_FLAG_TE3:   DMA1 Channel 3 Transfer Error flag
 *                      @arg DMA1_FLAG_AL4:   DMA1 Channel 4 All flag
 *                      @arg DMA1_FLAG_TF4:   DMA1 Channel 4 Transfer Complete flag
 *                      @arg DMA1_FLAG_HT4:   DMA1 Channel 4 Half Transfer Complete flag
 *                      @arg DMA1_FLAG_TE4:   DMA1 Channel 4 Transfer Error flag
 *                      @arg DMA1_FLAG_AL5:   DMA1 Channel 5 All flag
 *                      @arg DMA1_FLAG_TF5:   DMA1 Channel 5 Transfer Complete flag
 *                      @arg DMA1_FLAG_HT5:   DMA1 Channel 5 Half Transfer Complete flag
 *                      @arg DMA1_FLAG_TE5:   DMA1 Channel 5 Transfer Error flag
 *                      Below is only for APM32F072 and APM32F091 devices:
 *                      @arg DMA1_FLAG_AL6:   DMA1 Channel 6 All flag
 *                      @arg DMA1_FLAG_TF6:   DMA1 Channel 6 Transfer Complete flag
 *                      @arg DMA1_FLAG_HT6:   DMA1 Channel 6 Half Transfer Complete flag
 *                      @arg DMA1_FLAG_TE6:   DMA1 Channel 6 Transfer Error flag
 *                      @arg DMA1_FLAG_AL7:   DMA1 Channel 7 All flag
 *                      @arg DMA1_FLAG_TF7:   DMA1 Channel 7 Transfer Complete flag
 *                      @arg DMA1_FLAG_HT7:   DMA1 Channel 7 Half Transfer Complete flag
 *                      @arg DMA1_FLAG_TE7:   DMA1 Channel 7 Transfer Error flag
 *                      Below is only for APM32F091 devices:
 *                      @arg DMA2_FLAG_AL1:   DMA2 Channel 1 All flag
 *                      @arg DMA2_FLAG_TF1:   DMA2 Channel 1 Transfer Complete flag
 *                      @arg DMA2_FLAG_HT1:   DMA2 Channel 1 Half Transfer Complete flag
 *                      @arg DMA2_FLAG_TE1:   DMA2 Channel 1 Transfer Error flag
 *                      @arg DMA2_FLAG_AL2:   DMA2 Channel 2 All flag
 *                      @arg DMA2_FLAG_TF2:   DMA2 Channel 2 Transfer Complete flag
 *                      @arg DMA2_FLAG_HT2:   DMA2 Channel 2 Half Transfer Complete flag
 *                      @arg DMA2_FLAG_TE2:   DMA2 Channel 2 Transfer Error flag
 *                      @arg DMA2_FLAG_AL3:   DMA2 Channel 3 All flag
 *                      @arg DMA2_FLAG_TF3:   DMA2 Channel 3 Transfer Complete flag
 *                      @arg DMA2_FLAG_HT3:   DMA2 Channel 3 Half Transfer Complete flag
 *                      @arg DMA2_FLAG_TE3:   DMA2 Channel 3 Transfer Error flag
 *                      @arg DMA2_FLAG_AL4:   DMA2 Channel 4 All flag
 *                      @arg DMA2_FLAG_TF4:   DMA2 Channel 4 Transfer Complete flag
 *                      @arg DMA2_FLAG_HT4:   DMA2 Channel 4 Half Transfer Complete flag
 *                      @arg DMA2_FLAG_TE4:   DMA2 Channel 4 Transfer Error flag
 *                      @arg DMA2_FLAG_AL5:   DMA2 Channel 5 All flag
 *                      @arg DMA2_FLAG_TF5:   DMA2 Channel 5 Transfer Complete flag
 *                      @arg DMA2_FLAG_HT5:   DMA2 Channel 5 Half Transfer Complete flag
 *                      @arg DMA2_FLAG_TE5:   DMA2 Channel 5 Transfer Error flag
 *
 * @retval      None
 */

void DMA_ClearStatusFlag(uint32_t flag)
{
    if ((flag & 0x10000000) == SET)
    {
        DMA2->INTFCLR |= (uint32_t)(flag & 0x000FFFFF);
    }
    else
    {
        DMA1->INTFCLR |= (uint32_t)(flag & 0x0FFFFFFF);
    }
}

/*!
 * @brief       Checks whether the specified interrupt has occurred or not
 *
 * @param       flag:   Specifies the DMA interrupt pending bit to check
 *                      The parameter can be one following values:
 *                      @arg DMA1_INT_FLAG_AL1:   DMA1_Channel 1 All interrupt flag
 *                      @arg DMA1_INT_FLAG_TF1:   DMA1_Channel 1 Transfer Complete interrupt flag
 *                      @arg DMA1_INT_FLAG_HT1:   DMA1_Channel 1 Half Transfer Complete interrupt flag
 *                      @arg DMA1_INT_FLAG_TE1:   DMA1_Channel 1 Transfer Error interrupt flag
 *                      @arg DMA1_INT_FLAG_AL2:   DMA1_Channel 2 All interrupt flag
 *                      @arg DMA1_INT_FLAG_TF2:   DMA1_Channel 2 Transfer Complete interrupt flag
 *                      @arg DMA1_INT_FLAG_HT2:   DMA1_Channel 2 Half Transfer Complete interrupt flag
 *                      @arg DMA1_INT_FLAG_TE2:   DMA1_Channel 2 Transfer Error interrupt flag
 *                      @arg DMA1_INT_FLAG_AL3:   DMA1_Channel 3 All interrupt flag
 *                      @arg DMA1_INT_FLAG_TF3:   DMA1_Channel 3 Transfer Complete interrupt flag
 *                      @arg DMA1_INT_FLAG_HT3:   DMA1_Channel 3 Half Transfer Complete interrupt flag
 *                      @arg DMA1_INT_FLAG_TE3:   DMA1_Channel 3 Transfer Error interrupt flag
 *                      @arg DMA1_INT_FLAG_AL4:   DMA1_Channel 4 All interrupt flag
 *                      @arg DMA1_INT_FLAG_TF4:   DMA1_Channel 4 Transfer Complete interrupt flag
 *                      @arg DMA1_INT_FLAG_HT4:   DMA1_Channel 4 Half Transfer Complete interrupt flag
 *                      @arg DMA1_INT_FLAG_TE4:   DMA1_Channel 4 Transfer Error interrupt flag
 *                      @arg DMA1_INT_FLAG_AL5:   DMA1_Channel 5 All interrupt flag
 *                      @arg DMA1_INT_FLAG_TF5:   DMA1_Channel 5 Transfer Complete interrupt flag
 *                      @arg DMA1_INT_FLAG_HT5:   DMA1_Channel 5 Half Transfer Complete interrupt flag
 *                      @arg DMA1_INT_FLAG_TE5:   DMA1_Channel 5 Transfer Error interrupt flag
 *                      Below is only for APM32F072 and APM32F091 devices:
 *                      @arg DMA1_INT_FLAG_AL6:   DMA1_Channel 6 All interrupt flag
 *                      @arg DMA1_INT_FLAG_TF6:   DMA1_Channel 6 Transfer Complete interrupt flag
 *                      @arg DMA1_INT_FLAG_HT6:   DMA1_Channel 6 Half Transfer Complete interrupt flag
 *                      @arg DMA1_INT_FLAG_TE6:   DMA1_Channel 6 Transfer Error interrupt flag
 *                      @arg DMA1_INT_FLAG_AL7:   DMA1_Channel 7 All interrupt flag
 *                      @arg DMA1_INT_FLAG_TF7:   DMA1_Channel 7 Transfer Complete interrupt flag
 *                      @arg DMA1_INT_FLAG_HT7:   DMA1_Channel 7 Half Transfer Complete interrupt flag
 *                      @arg DMA1_INT_FLAG_TE7:   DMA1_Channel 7 Transfer Error interrupt flag
 *                      Below is only for APM32F091 devices:
 *                      @arg DMA2_INT_FLAG_AL1:   DMA2_Channel 1 All interrupt flag
 *                      @arg DMA2_INT_FLAG_TF1:   DMA2_Channel 1 Transfer Complete interrupt flag
 *                      @arg DMA2_INT_FLAG_HT1:   DMA2_Channel 1 Half Transfer Complete interrupt flag
 *                      @arg DMA2_INT_FLAG_TE1:   DMA2_Channel 1 Transfer Error interrupt flag
 *                      @arg DMA2_INT_FLAG_AL2:   DMA2_Channel 2 All interrupt flag
 *                      @arg DMA2_INT_FLAG_TF2:   DMA2_Channel 2 Transfer Complete interrupt flag
 *                      @arg DMA2_INT_FLAG_HT2:   DMA2_Channel 2 Half Transfer Complete interrupt flag
 *                      @arg DMA2_INT_FLAG_TE2:   DMA2_Channel 2 Transfer Error interrupt flag
 *                      @arg DMA2_INT_FLAG_AL3:   DMA2_Channel 3 All interrupt flag
 *                      @arg DMA2_INT_FLAG_TF3:   DMA2_Channel 3 Transfer Complete interrupt flag
 *                      @arg DMA2_INT_FLAG_HT3:   DMA2_Channel 3 Half Transfer Complete interrupt flag
 *                      @arg DMA2_INT_FLAG_TE3:   DMA2_Channel 3 Transfer Error interrupt flag
 *                      @arg DMA2_INT_FLAG_AL4:   DMA2_Channel 4 All interrupt flag
 *                      @arg DMA2_INT_FLAG_TF4:   DMA2_Channel 4 Transfer Complete interrupt flag
 *                      @arg DMA2_INT_FLAG_HT4:   DMA2_Channel 4 Half Transfer Complete interrupt flag
 *                      @arg DMA2_INT_FLAG_TE4:   DMA2_Channel 4 Transfer Error interrupt flag
 *                      @arg DMA2_INT_FLAG_AL5:   DMA2_Channel 5 All interrupt flag
 *                      @arg DMA2_INT_FLAG_TF5:   DMA2_Channel 5 Transfer Complete interrupt flag
 *                      @arg DMA2_INT_FLAG_HT5:   DMA2_Channel 5 Half Transfer Complete interrupt flag
 *                      @arg DMA2_INT_FLAG_TE5:   DMA2_Channel 5 Transfer Error interrupt flag
 *
 * @retval      The new state of flag (SET or RESET)
 */
uint8_t DMA_ReadIntFlag(DMA_INT_FLAG_T flag)
{
    uint32_t status;

    if ((flag & 0x10000000) == SET)
    {
        status = DMA2->INTSTS & ((uint32_t)flag & 0x000FFFFF);
    }
    else
    {
        status = DMA1->INTSTS & ((uint32_t)flag & 0x0FFFFFFF);
    }

    if (status == flag)
    {
        return SET;
    }

    return RESET;
}

/*!
 * @brief       Clears the specified interrupt pending bits
 *
 * @param       flag:   Specifies the DMA interrupt pending bit to clear
 *                      The parameter can be combination of following values:
 *                      @arg DMA1_INT_FLAG_AL1:   DMA1_Channel 1 All interrupt flag
 *                      @arg DMA1_INT_FLAG_TF1:   DMA1_Channel 1 Transfer Complete interrupt flag
 *                      @arg DMA1_INT_FLAG_HT1:   DMA1_Channel 1 Half Transfer Complete interrupt flag
 *                      @arg DMA1_INT_FLAG_TE1:   DMA1_Channel 1 Transfer Error interrupt flag
 *                      @arg DMA1_INT_FLAG_AL2:   DMA1_Channel 2 All interrupt flag
 *                      @arg DMA1_INT_FLAG_TF2:   DMA1_Channel 2 Transfer Complete interrupt flag
 *                      @arg DMA1_INT_FLAG_HT2:   DMA1_Channel 2 Half Transfer Complete interrupt flag
 *                      @arg DMA1_INT_FLAG_TE2:   DMA1_Channel 2 Transfer Error interrupt flag
 *                      @arg DMA1_INT_FLAG_AL3:   DMA1_Channel 3 All interrupt flag
 *                      @arg DMA1_INT_FLAG_TF3:   DMA1_Channel 3 Transfer Complete interrupt flag
 *                      @arg DMA1_INT_FLAG_HT3:   DMA1_Channel 3 Half Transfer Complete interrupt flag
 *                      @arg DMA1_INT_FLAG_TE3:   DMA1_Channel 3 Transfer Error interrupt flag
 *                      @arg DMA1_INT_FLAG_AL4:   DMA1_Channel 4 All interrupt flag
 *                      @arg DMA1_INT_FLAG_TF4:   DMA1_Channel 4 Transfer Complete interrupt flag
 *                      @arg DMA1_INT_FLAG_HT4:   DMA1_Channel 4 Half Transfer Complete interrupt flag
 *                      @arg DMA1_INT_FLAG_TE4:   DMA1_Channel 4 Transfer Error interrupt flag
 *                      @arg DMA1_INT_FLAG_AL5:   DMA1_Channel 5 All interrupt flag
 *                      @arg DMA1_INT_FLAG_TF5:   DMA1_Channel 5 Transfer Complete interrupt flag
 *                      @arg DMA1_INT_FLAG_HT5:   DMA1_Channel 5 Half Transfer Complete interrupt flag
 *                      @arg DMA1_INT_FLAG_TE5:   DMA1_Channel 5 Transfer Error interrupt flag
 *                      Below is only for APM32F072 and APM32F091 devices:
 *                      @arg DMA1_INT_FLAG_AL6:   DMA1_Channel 6 All interrupt flag
 *                      @arg DMA1_INT_FLAG_TF6:   DMA1_Channel 6 Transfer Complete interrupt flag
 *                      @arg DMA1_INT_FLAG_HT6:   DMA1_Channel 6 Half Transfer Complete interrupt flag
 *                      @arg DMA1_INT_FLAG_TE6:   DMA1_Channel 6 Transfer Error interrupt flag
 *                      @arg DMA1_INT_FLAG_AL7:   DMA1_Channel 7 All interrupt flag
 *                      @arg DMA1_INT_FLAG_TF7:   DMA1_Channel 7 Transfer Complete interrupt flag
 *                      @arg DMA1_INT_FLAG_HT7:   DMA1_Channel 7 Half Transfer Complete interrupt flag
 *                      @arg DMA1_INT_FLAG_TE7:   DMA1_Channel 7 Transfer Error interrupt flag
 *                      Below is only for APM32F091 devices:
 *                      @arg DMA2_INT_FLAG_AL1:   DMA2_Channel 1 All interrupt flag
 *                      @arg DMA2_INT_FLAG_TF1:   DMA2_Channel 1 Transfer Complete interrupt flag
 *                      @arg DMA2_INT_FLAG_HT1:   DMA2_Channel 1 Half Transfer Complete interrupt flag
 *                      @arg DMA2_INT_FLAG_TE1:   DMA2_Channel 1 Transfer Error interrupt flag
 *                      @arg DMA2_INT_FLAG_AL2:   DMA2_Channel 2 All interrupt flag
 *                      @arg DMA2_INT_FLAG_TF2:   DMA2_Channel 2 Transfer Complete interrupt flag
 *                      @arg DMA2_INT_FLAG_HT2:   DMA2_Channel 2 Half Transfer Complete interrupt flag
 *                      @arg DMA2_INT_FLAG_TE2:   DMA2_Channel 2 Transfer Error interrupt flag
 *                      @arg DMA2_INT_FLAG_AL3:   DMA2_Channel 3 All interrupt flag
 *                      @arg DMA2_INT_FLAG_TF3:   DMA2_Channel 3 Transfer Complete interrupt flag
 *                      @arg DMA2_INT_FLAG_HT3:   DMA2_Channel 3 Half Transfer Complete interrupt flag
 *                      @arg DMA2_INT_FLAG_TE3:   DMA2_Channel 3 Transfer Error interrupt flag
 *                      @arg DMA2_INT_FLAG_AL4:   DMA2_Channel 4 All interrupt flag
 *                      @arg DMA2_INT_FLAG_TF4:   DMA2_Channel 4 Transfer Complete interrupt flag
 *                      @arg DMA2_INT_FLAG_HT4:   DMA2_Channel 4 Half Transfer Complete interrupt flag
 *                      @arg DMA2_INT_FLAG_TE4:   DMA2_Channel 4 Transfer Error interrupt flag
 *                      @arg DMA2_INT_FLAG_AL5:   DMA2_Channel 5 All interrupt flag
 *                      @arg DMA2_INT_FLAG_TF5:   DMA2_Channel 5 Transfer Complete interrupt flag
 *                      @arg DMA2_INT_FLAG_HT5:   DMA2_Channel 5 Half Transfer Complete interrupt flag
 *                      @arg DMA2_INT_FLAG_TE5:   DMA2_Channel 5 Transfer Error interrupt flag
 *
 * @retval      None
 */
void DMA_ClearIntFlag(uint32_t flag)
{
    if ((flag & 0x10000000) == SET)
    {
        DMA2->INTFCLR |= (uint32_t)(flag & 0x000FFFFF);
    }
    else
    {
        DMA1->INTFCLR |= (uint32_t)(flag & 0x0FFFFFFF);
    }
}

/**@} end of group DMA_Functions */
/**@} end of group DMA_Driver */
/**@} end of group APM32F0xx_StdPeriphDriver */

