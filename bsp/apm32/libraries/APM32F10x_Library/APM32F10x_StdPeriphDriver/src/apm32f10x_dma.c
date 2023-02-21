/*!
 * @file        apm32f10x_dma.c
 *
 * @brief       This file provides all the DMA firmware functions
 *
 * @version     V1.0.4
 *
 * @date        2022-12-01
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

#include "apm32f10x_dma.h"

/** @addtogroup APM32F10x_StdPeriphDriver
  @{
*/

/** @addtogroup DMA_Driver DMA Driver
  * @brief DMA driver modules
  @{
*/

/** @defgroup DMA_Functions Functions
  @{
*/

/*!
 * @brief     Reset specified DMA Channel registers to their default reset
 *
 * @param     channel:DMA1_channelx(x can be from 1 to 7) or DMA2_channely(y can be from 1 to 5).
 *
 * @retval    None
 *
 * @note      DMA2 Channel only for APM32 High density devices.
 */
void DMA_Reset(DMA_Channel_T* channel)
{
    channel->CHCFG_B.CHEN = BIT_RESET;
    channel->CHCFG = 0;
    channel->CHNDATA = 0;
    channel->CHMADDR = 0;
    channel->CHPADDR = 0;

    if (channel == DMA1_Channel1)
    {
        DMA1->INTFCLR |= 0xFFFFFFF0;
    }
    else if (channel == DMA1_Channel2)
    {
        DMA1->INTFCLR |= 0xFFFFFF0F;
    }
    else if (channel == DMA1_Channel3)
    {
        DMA1->INTFCLR |= 0xFFFFF0FF;
    }
    else if (channel == DMA1_Channel4)
    {
        DMA1->INTFCLR |= 0xFFFF0FFF;
    }
    else if (channel == DMA1_Channel5)
    {
        DMA1->INTFCLR |= 0xFFF0FFFF;
    }
    else if (channel == DMA1_Channel6)
    {
        DMA1->INTFCLR |= 0xFF0FFFFF;
    }
    else if (channel == DMA1_Channel7)
    {
        DMA1->INTFCLR |= 0xF0FFFFFF;
    }
    else if (channel == DMA2_Channel1)
    {
        DMA2->INTFCLR |= 0xFFFFFFF0;
    }
    else if (channel == DMA2_Channel2)
    {
        DMA2->INTFCLR |= 0xFFFFFF0F;
    }
    else if (channel == DMA2_Channel3)
    {
        DMA2->INTFCLR |= 0xFFFFF0FF;
    }
    else if (channel == DMA2_Channel4)
    {
        DMA2->INTFCLR |= 0xFFFF0FFF;
    }
    else if (channel == DMA2_Channel5)
    {
        DMA2->INTFCLR |= 0xFFF0FFFF;
    }
}

/*!
 * @brief     Configs specified DMA Channel through a structure.
 *
 * @param     channel:DMA1_channelx(x can be from 1 to 7) or DMA2_channely(y can be from 1 to 5)
 *
 * @param     dmaConfig: Point to a DMA_Config_T structure
 *
 * @retval    None
 *
 * @note      DMA2 Channel only for APM32 High density devices.
 */
void DMA_Config(DMA_Channel_T* channel, DMA_Config_T* dmaConfig)
{
    channel->CHCFG_B.DIRCFG = dmaConfig->dir;
    channel->CHCFG_B.CIRMODE = dmaConfig->loopMode;
    channel->CHCFG_B.PERIMODE = dmaConfig->peripheralInc;
    channel->CHCFG_B.MIMODE = dmaConfig->memoryInc;
    channel->CHCFG_B.PERSIZE = dmaConfig->peripheralDataSize;
    channel->CHCFG_B.MEMSIZE = dmaConfig->memoryDataSize;
    channel->CHCFG_B.CHPL = dmaConfig->priority;
    channel->CHCFG_B.M2MMODE = dmaConfig->M2M;

    channel->CHNDATA = dmaConfig->bufferSize;
    channel->CHPADDR = dmaConfig->peripheralBaseAddr;
    channel->CHMADDR = dmaConfig->memoryBaseAddr;
}

/*!
 * @brief     Populate the structure with default values.
 *
 * @param     dmaConfig: Point to a DMA_Config_T structure.
 *
 * @retval    None
 */
void DMA_ConfigStructInit(DMA_Config_T* dmaConfig)
{
    dmaConfig->peripheralBaseAddr = 0;
    dmaConfig->memoryBaseAddr = 0;
    dmaConfig->dir = DMA_DIR_PERIPHERAL_SRC;
    dmaConfig->bufferSize = 0;
    dmaConfig->peripheralInc = DMA_PERIPHERAL_INC_DISABLE;
    dmaConfig->memoryInc = DMA_MEMORY_INC_DISABLE;
    dmaConfig->peripheralDataSize = DMA_PERIPHERAL_DATA_SIZE_BYTE;
    dmaConfig->memoryDataSize = DMA_MEMORY_DATA_SIZE_BYTE;
    dmaConfig->loopMode = DMA_MODE_NORMAL;
    dmaConfig->priority = DMA_PRIORITY_LOW;
    dmaConfig->M2M = DMA_M2MEN_DISABLE;
}

/*!
 * @brief     Enable the specified DMA Channel
 *
 * @param     channel:DMA1_channelx(x can be from 1 to 7) or DMA2_channely(y can be from 1 to 5)
 *
 * @retval    None
 *
 * @note      DMA2 Channel only for APM32 High density devices.
 */
void DMA_Enable(DMA_Channel_T* channel)
{
    channel->CHCFG_B.CHEN = ENABLE;
}

/*!
 * @brief     Disable the specified DMA Channel
 *
 * @param     channel:DMA1_channelx(x can be from 1 to 7) or DMA2_channely(y can be from 1 to 5)
 *
 * @retval    None
 *
 * @note      DMA2 Channel only for APM32 High density devices.
 */
void DMA_Disable(DMA_Channel_T* channel)
{
    channel->CHCFG_B.CHEN = DISABLE;
}

/*!
 * @brief     Configs the number of data units in the channel.
 *
 * @param     channel:DMA1_channelx(x can be from 1 to 7) or DMA2_channely(y can be from 1 to 5)
 *
 * @param     dataNumber:The number of data units in the current DMA Channel transfer.
 *
 * @retval    None
 *
 * @note      DMA2 Channel only for APM32 High density devices.
 */
void DMA_ConfigDataNumber(DMA_Channel_T* channel, uint16_t dataNumber)
{
    channel->CHNDATA = dataNumber;
}

/*!
 * @brief     Read the number of data units in the channel
 *
 * @param     channel:DMA1_channelx(x can be from 1 to 7) or DMA2_channely(y can be from 1 to 5)
 *
 * @retval    The number of CHNDATA value
 *
 * @note      DMA2 Channel only for APM32 High density devices.
 */
uint16_t DMA_ReadDataNumber(DMA_Channel_T* channel)
{
    return channel->CHNDATA;
}

/*!
 * @brief     Enables the specified DMA Channel interrupts.
 *
 * @param     channel:DMA1_channelx(x can be from 1 to 7) or DMA2_channely(y can be from 1 to 5)
 *
 * @param     interrupt: DMA interrupts sources to selsct
 *                       This parameter can be any combination of the following values:
 *                       @arg DMA_INT_TC   : All Transfer Complete Interrupt
 *                       @arg DMA_INT_HT   : Half Transfer Complete Interrupt
 *                       @arg DMA_INT_TERR : Transfer Error Occur Interrupt
 *
 * @retval    None
 *
 * @note      DMA2 Channel only for APM32 High density devices.
 */
void DMA_EnableInterrupt(DMA_Channel_T* channel, uint32_t interrupt)
{
    channel->CHCFG |= interrupt;
}

/*!
 * @brief     Disable the specified DMA Channel interrupts.
 *
 * @param     channel:DMA1_channelx(x can be from 1 to 7) or DMA2_channely(y can be from 1 to 5)
 *
 * @param     interrupt: DMA interrupts sources to selsct
 *                       This parameter can be any combination of the following values:
 *                       @arg DMA_INT_TC   : All Transfer Complete Interrupt
 *                       @arg DMA_INT_HT   : Half Transfer Complete Interrupt
 *                       @arg DMA_INT_TERR : Transfer Error Occur Interrupt
 *
 * @retval    None
 *
 * @note      DMA2 Channel only for APM32 High density devices.
 */
void DMA_DisableInterrupt(DMA_Channel_T* channel, uint32_t interrupt)
{
    channel->CHCFG &= ~interrupt;
}

/*!
 * @brief     Read whether the specifie DMA Channel flag is set or not.
 *
 * @param     flag: the flag to check.
 *                  This parameter can be one of the following values:
 *                    @arg DMA1_FLAG_GINT1: DMA1 Channel 1 global flag.
 *                    @arg DMA1_FLAG_TC1:   DMA1 Channel 1 transfer complete flag.
 *                    @arg DMA1_FLAG_HT1:   DMA1 Channel 1 half transfer flag.
 *                    @arg DMA1_FLAG_TERR1: DMA1 Channel 1 transfer error flag.
 *                    @arg DMA1_FLAG_GINT2: DMA1 Channel2 global flag.
 *                    @arg DMA1_FLAG_TC2:   DMA1 Channel2 transfer complete flag.
 *                    @arg DMA1_FLAG_HT2:   DMA1 Channel2 half transfer flag.
 *                    @arg DMA1_FLAG_TERR2: DMA1 Channel2 transfer error flag.
 *                    @arg DMA1_FLAG_GINT3: DMA1 Channel3 global flag.
 *                    @arg DMA1_FLAG_TC3:   DMA1 Channel3 transfer complete flag.
 *                    @arg DMA1_FLAG_HT3:   DMA1 Channel3 half transfer flag.
 *                    @arg DMA1_FLAG_TERR3: DMA1 Channel3 transfer error flag.
 *                    @arg DMA1_FLAG_GINT4: DMA1 Channel4 global flag.
 *                    @arg DMA1_FLAG_TC4:   DMA1 Channel4 transfer complete flag.
 *                    @arg DMA1_FLAG_HT4:   DMA1 Channel4 half transfer flag.
 *                    @arg DMA1_FLAG_TERR4: DMA1 Channel4 transfer error flag.
 *                    @arg DMA1_FLAG_GINT5: DMA1 Channel5 global flag.
 *                    @arg DMA1_FLAG_TC5:   DMA1 Channel5 transfer complete flag.
 *                    @arg DMA1_FLAG_HT5:   DMA1 Channel5 half transfer flag.
 *                    @arg DMA1_FLAG_TERR5: DMA1 Channel5 transfer error flag.
 *                    @arg DMA1_FLAG_GINT6: DMA1 Channel6 global flag.
 *                    @arg DMA1_FLAG_TC6:   DMA1 Channel6 transfer complete flag.
 *                    @arg DMA1_FLAG_HT6:   DMA1 Channel6 half transfer flag.
 *                    @arg DMA1_FLAG_TERR6: DMA1 Channel6 transfer error flag.
 *                    @arg DMA1_FLAG_GINT7: DMA1 Channel7 global flag.
 *                    @arg DMA1_FLAG_TC7:   DMA1 Channel7 transfer complete flag.
 *                    @arg DMA1_FLAG_HT7:   DMA1 Channel7 half transfer flag.
 *                    @arg DMA1_FLAG_TERR7: DMA1 Channel7 transfer error flag.
 *
 *                    @arg DMA2_FLAG_GINT1: DMA2 Channel 1 global flag.
 *                    @arg DMA2_FLAG_TC1:   DMA2 Channel 1 transfer complete flag.
 *                    @arg DMA2_FLAG_HT1:   DMA2 Channel 1 half transfer flag.
 *                    @arg DMA2_FLAG_TERR1: DMA2 Channel 1 transfer error flag.
 *                    @arg DMA2_FLAG_GINT2: DMA2 Channel 2 global flag.
 *                    @arg DMA2_FLAG_TC2:   DMA2 Channel 2 transfer complete flag.
 *                    @arg DMA2_FLAG_HT2:   DMA2 Channel 2 half transfer flag.
 *                    @arg DMA2_FLAG_TERR2: DMA2 Channel 2 transfer error flag.
 *                    @arg DMA2_FLAG_GINT3: DMA2 Channel 3 global flag.
 *                    @arg DMA2_FLAG_TC3:   DMA2 Channel 3 transfer complete flag.
 *                    @arg DMA2_FLAG_HT3:   DMA2 Channel 3 half transfer flag.
 *                    @arg DMA2_FLAG_TERR3: DMA2 Channel 3 transfer error flag.
 *                    @arg DMA2_FLAG_GINT4: DMA2 Channel 4 global flag.
 *                    @arg DMA2_FLAG_TC4:   DMA2 Channel 4 transfer complete flag.
 *                    @arg DMA2_FLAG_HT4:   DMA2 Channel 4 half transfer flag.
 *                    @arg DMA2_FLAG_TERR4: DMA2 Channel 4 transfer error flag.
 *                    @arg DMA2_FLAG_GINT5: DMA2 Channel 5 global flag.
 *                    @arg DMA2_FLAG_TC5:   DMA2 Channel 5 transfer complete flag.
 *                    @arg DMA2_FLAG_HT5:   DMA2 Channel 5 half transfer flag.
 *                    @arg DMA2_FLAG_TERR5: DMA2 Channel 5 transfer error flag.
 *
 * @retval    Flag State
 *
 * @note      DMA2 Channel only for APM32 High density devices.
 */
uint8_t DMA_ReadStatusFlag(DMA_FLAG_T flag)
{
    if ((flag & 0x10000000) != RESET)
    {
        if ((DMA2->INTSTS & flag) != RESET)
        {
            return SET ;
        }
        else
        {
            return RESET ;
        }
    }
    else
    {
        if ((DMA1->INTSTS & flag) != RESET)
        {
            return SET ;
        }
        else
        {
            return RESET ;
        }
    }
}

/*!
 * @brief     Clears the specifie DMA Channel's flags.
 *
 * @param     flag:the flag to Clear.
 *                  This parameter can be any combination of the following values:
 *                    @arg DMA1_FLAG_GINT1: DMA1 Channel 1 global flag.
 *                    @arg DMA1_FLAG_TC1:   DMA1 Channel 1 transfer complete flag.
 *                    @arg DMA1_FLAG_HT1:   DMA1 Channel 1 half transfer flag.
 *                    @arg DMA1_FLAG_TERR1: DMA1 Channel 1 transfer error flag.
 *                    @arg DMA1_FLAG_GINT2: DMA1 Channel2 global flag.
 *                    @arg DMA1_FLAG_TC2:   DMA1 Channel2 transfer complete flag.
 *                    @arg DMA1_FLAG_HT2:   DMA1 Channel2 half transfer flag.
 *                    @arg DMA1_FLAG_TERR2: DMA1 Channel2 transfer error flag.
 *                    @arg DMA1_FLAG_GINT3: DMA1 Channel3 global flag.
 *                    @arg DMA1_FLAG_TC3:   DMA1 Channel3 transfer complete flag.
 *                    @arg DMA1_FLAG_HT3:   DMA1 Channel3 half transfer flag.
 *                    @arg DMA1_FLAG_TERR3: DMA1 Channel3 transfer error flag.
 *                    @arg DMA1_FLAG_GINT4: DMA1 Channel4 global flag.
 *                    @arg DMA1_FLAG_TC4:   DMA1 Channel4 transfer complete flag.
 *                    @arg DMA1_FLAG_HT4:   DMA1 Channel4 half transfer flag.
 *                    @arg DMA1_FLAG_TERR4: DMA1 Channel4 transfer error flag.
 *                    @arg DMA1_FLAG_GINT5: DMA1 Channel5 global flag.
 *                    @arg DMA1_FLAG_TC5:   DMA1 Channel5 transfer complete flag.
 *                    @arg DMA1_FLAG_HT5:   DMA1 Channel5 half transfer flag.
 *                    @arg DMA1_FLAG_TERR5: DMA1 Channel5 transfer error flag.
 *                    @arg DMA1_FLAG_GINT6: DMA1 Channel6 global flag.
 *                    @arg DMA1_FLAG_TC6:   DMA1 Channel6 transfer complete flag.
 *                    @arg DMA1_FLAG_HT6:   DMA1 Channel6 half transfer flag.
 *                    @arg DMA1_FLAG_TERR6: DMA1 Channel6 transfer error flag.
 *                    @arg DMA1_FLAG_GINT7: DMA1 Channel7 global flag.
 *                    @arg DMA1_FLAG_TC7:   DMA1 Channel7 transfer complete flag.
 *                    @arg DMA1_FLAG_HT7:   DMA1 Channel7 half transfer flag.
 *                    @arg DMA1_FLAG_TERR7: DMA1 Channel7 transfer error flag.

 *                    @arg DMA2_FLAG_GINT1: DMA2 Channel 1 global flag.
 *                    @arg DMA2_FLAG_TC1:   DMA2 Channel 1 transfer complete flag.
 *                    @arg DMA2_FLAG_HT1:   DMA2 Channel 1 half transfer flag.
 *                    @arg DMA2_FLAG_TERR1: DMA2 Channel 1 transfer error flag.
 *                    @arg DMA2_FLAG_GINT2: DMA2 Channel 2 global flag.
 *                    @arg DMA2_FLAG_TC2:   DMA2 Channel 2 transfer complete flag.
 *                    @arg DMA2_FLAG_HT2:   DMA2 Channel 2 half transfer flag.
 *                    @arg DMA2_FLAG_TERR2: DMA2 Channel 2 transfer error flag.
 *                    @arg DMA2_FLAG_GINT3: DMA2 Channel 3 global flag.
 *                    @arg DMA2_FLAG_TC3:   DMA2 Channel 3 transfer complete flag.
 *                    @arg DMA2_FLAG_HT3:   DMA2 Channel 3 half transfer flag.
 *                    @arg DMA2_FLAG_TERR3: DMA2 Channel 3 transfer error flag.
 *                    @arg DMA2_FLAG_GINT4: DMA2 Channel 4 global flag.
 *                    @arg DMA2_FLAG_TC4:   DMA2 Channel 4 transfer complete flag.
 *                    @arg DMA2_FLAG_HT4:   DMA2 Channel 4 half transfer flag.
 *                    @arg DMA2_FLAG_TERR4: DMA2 Channel 4 transfer error flag.
 *                    @arg DMA2_FLAG_GINT5: DMA2 Channel 5 global flag.
 *                    @arg DMA2_FLAG_TC5:   DMA2 Channel 5 transfer complete flag.
 *                    @arg DMA2_FLAG_HT5:   DMA2 Channel 5 half transfer flag.
 *                    @arg DMA2_FLAG_TERR5: DMA2 Channel 5 transfer error flag.
 *
 * @retval    None
 *
 * @note      DMA2 Channel only for APM32 High density devices.
 */
void DMA_ClearStatusFlag(uint32_t flag)
{
    if ((flag & 0x10000000) != RESET)
    {
        DMA2->INTFCLR = flag;
    }
    else
    {
        DMA1->INTFCLR = flag;
    }
}

/*!
 * @brief     Read whether the specified DMA Channel interrupts is set or not.
 *
 * @param     interrupt: interrupt source to check.
 *                  This parameter can be one of the following values:
 *                    @arg DMA1_INT_FLAG_GINT1 : DMA1 Channel 1 global interrupt.
 *                    @arg DMA1_INT_FLAG_TC1   : DMA1 Channel 1 transfer complete interrupt.
 *                    @arg DMA1_INT_FLAG_HT1   : DMA1 Channel 1 half transfer interrupt.
 *                    @arg DMA1_INT_FLAG_TERR1 : DMA1 Channel 1 transfer error interrupt.
 *                    @arg DMA1_INT_FLAG_GINT2 : DMA1 Channel2 global interrupt.
 *                    @arg DMA1_INT_FLAG_TC2   : DMA1 Channel2 transfer complete interrupt.
 *                    @arg DMA1_INT_FLAG_HT2   : DMA1 Channel2 half transfer interrupt.
 *                    @arg DMA1_INT_FLAG_TERR2 : DMA1 Channel2 transfer error interrupt.
 *                    @arg DMA1_INT_FLAG_GINT3 : DMA1 Channel3 global interrupt.
 *                    @arg DMA1_INT_FLAG_TC3   : DMA1 Channel3 transfer complete interrupt.
 *                    @arg DMA1_INT_FLAG_HT3   : DMA1 Channel3 half transfer interrupt.
 *                    @arg DMA1_INT_FLAG_TERR3 : DMA1 Channel3 transfer error interrupt.
 *                    @arg DMA1_INT_FLAG_GINT4 : DMA1 Channel4 global interrupt.
 *                    @arg DMA1_INT_FLAG_TC4   : DMA1 Channel4 transfer complete interrupt.
 *                    @arg DMA1_INT_FLAG_HT4   : DMA1 Channel4 half transfer interrupt.
 *                    @arg DMA1_INT_FLAG_TERR4 : DMA1 Channel4 transfer error interrupt.
 *                    @arg DMA1_INT_FLAG_GINT5 : DMA1 Channel5 global interrupt.
 *                    @arg DMA1_INT_FLAG_TC5     DMA1 Channel5 transfer complete interrupt.
 *                    @arg DMA1_INT_FLAG_HT5     DMA1 Channel5 half transfer interrupt.
 *                    @arg DMA1_INT_FLAG_TERR5 : DMA1 Channel5 transfer error interrupt.
 *                    @arg DMA1_INT_FLAG_GINT6 : DMA1 Channel6 global interrupt.
 *                    @arg DMA1_INT_FLAG_TC6   : DMA1 Channel6 transfer complete interrupt.
 *                    @arg DMA1_INT_FLAG_HT6   : DMA1 Channel6 half transfer interrupt.
 *                    @arg DMA1_INT_FLAG_TERR6 : DMA1 Channel6 transfer error interrupt.
 *                    @arg DMA1_INT_FLAG_GINT7 : DMA1 Channel7 global interrupt.
 *                    @arg DMA1_INT_FLAG_TC7   : DMA1 Channel7 transfer complete interrupt.
 *                    @arg DMA1_INT_FLAG_HT7   : DMA1 Channel7 half transfer interrupt.
 *                    @arg DMA1_INT_FLAG_TERR7 : DMA1 Channel7 transfer error interrupt.

 *                    @arg DMA2_INT_FLAG_GINT1 : DMA2 Channel 1 global interrupt.
 *                    @arg DMA2_INT_FLAG_TC1   : DMA2 Channel 1 transfer complete interrupt.
 *                    @arg DMA2_INT_FLAG_HT1   : DMA2 Channel 1 half transfer interrupt.
 *                    @arg DMA2_INT_FLAG_TERR1 : DMA2 Channel 1 transfer error interrupt.
 *                    @arg DMA2_INT_FLAG_GINT2 : DMA2 Channel 2 global interrupt.
 *                    @arg DMA2_INT_FLAG_TC2   : DMA2 Channel 2 transfer complete interrupt.
 *                    @arg DMA2_INT_FLAG_HT2   : DMA2 Channel 2 half transfer interrupt.
 *                    @arg DMA2_INT_FLAG_TERR2 : DMA2 Channel 2 transfer error interrupt.
 *                    @arg DMA2_INT_FLAG_GINT3 : DMA2 Channel 3 global interrupt.
 *                    @arg DMA2_INT_FLAG_TC3   : DMA2 Channel 3 transfer complete interrupt.
 *                    @arg DMA2_INT_FLAG_HT3   : DMA2 Channel 3 half transfer interrupt.
 *                    @arg DMA2_INT_FLAG_TERR3 : DMA2 Channel 3 transfer error interrupt.
 *                    @arg DMA2_INT_FLAG_GINT4 : DMA2 Channel 4 global interrupt.
 *                    @arg DMA2_INT_FLAG_TC4   : DMA2 Channel 4 transfer complete interrupt.
 *                    @arg DMA2_INT_FLAG_HT4   : DMA2 Channel 4 half transfer interrupt.
 *                    @arg DMA2_INT_FLAG_TERR4 : DMA2 Channel 4 transfer error interrupt.
 *                    @arg DMA2_INT_FLAG_GINT5 : DMA2 Channel 5 global interrupt.
 *                    @arg DMA2_INT_FLAG_TC5   : DMA2 Channel 5 transfer complete interrupt.
 *                    @arg DMA2_INT_FLAG_HT5   : DMA2 Channel 5 half transfer interrupt.
 *                    @arg DMA2_INT_FLAG_TERR5 : DMA2 Channel 5 transfer error interrupt.
 *
 * @retval    interrupt State
 *
 * @note      DMA2 Channel only for APM32 High density devices.
 */
uint8_t DMA_ReadIntFlag(DMA_INT_FLAG_T flag)
{
    if ((flag & 0x10000000) != RESET)
    {
        if ((DMA2->INTSTS & flag) != RESET)
        {
            return SET ;
        }
        else
        {
            return RESET ;
        }
    }
    else
    {
        if ((DMA1->INTSTS & flag) != RESET)
        {
            return SET ;
        }
        else
        {
            return RESET ;
        }
    }
}

/*!
 * @brief     Clears the specified DMA Channel's interrupts.
 *
 * @param     flag: the interrupt flag to Clear.
 *                  This parameter can be any combination of the following values:
 *                    @arg DMA1_INT_FLAG_GINT1 : DMA1 Channel 1 global interrupt.
 *                    @arg DMA1_INT_FLAG_TC1   : DMA1 Channel 1 transfer complete interrupt.
 *                    @arg DMA1_INT_FLAG_HT1   : DMA1 Channel 1 half transfer interrupt.
 *                    @arg DMA1_INT_FLAG_TERR1 : DMA1 Channel 1 transfer error interrupt.
 *                    @arg DMA1_INT_FLAG_GINT2 : DMA1 Channel2 global interrupt.
 *                    @arg DMA1_INT_FLAG_TC2   : DMA1 Channel2 transfer complete interrupt.
 *                    @arg DMA1_INT_FLAG_HT2   : DMA1 Channel2 half transfer interrupt.
 *                    @arg DMA1_INT_FLAG_TERR2 : DMA1 Channel2 transfer error interrupt.
 *                    @arg DMA1_INT_FLAG_GINT3 : DMA1 Channel3 global interrupt.
 *                    @arg DMA1_INT_FLAG_TC3   : DMA1 Channel3 transfer complete interrupt.
 *                    @arg DMA1_INT_FLAG_HT3   : DMA1 Channel3 half transfer interrupt.
 *                    @arg DMA1_INT_FLAG_TERR3 : DMA1 Channel3 transfer error interrupt.
 *                    @arg DMA1_INT_FLAG_GINT4 : DMA1 Channel4 global interrupt.
 *                    @arg DMA1_INT_FLAG_TC4   : DMA1 Channel4 transfer complete interrupt.
 *                    @arg DMA1_INT_FLAG_HT4   : DMA1 Channel4 half transfer interrupt.
 *                    @arg DMA1_INT_FLAG_TERR4 : DMA1 Channel4 transfer error interrupt.
 *                    @arg DMA1_INT_FLAG_GINT5 : DMA1 Channel5 global interrupt.
 *                    @arg DMA1_INT_FLAG_TC5     DMA1 Channel5 transfer complete interrupt.
 *                    @arg DMA1_INT_FLAG_HT5     DMA1 Channel5 half transfer interrupt.
 *                    @arg DMA1_INT_FLAG_TERR5 : DMA1 Channel5 transfer error interrupt.
 *                    @arg DMA1_INT_FLAG_GINT6 : DMA1 Channel6 global interrupt.
 *                    @arg DMA1_INT_FLAG_TC6   : DMA1 Channel6 transfer complete interrupt.
 *                    @arg DMA1_INT_FLAG_HT6   : DMA1 Channel6 half transfer interrupt.
 *                    @arg DMA1_INT_FLAG_TERR6 : DMA1 Channel6 transfer error interrupt.
 *                    @arg DMA1_INT_FLAG_GINT7 : DMA1 Channel7 global interrupt.
 *                    @arg DMA1_INT_FLAG_TC7   : DMA1 Channel7 transfer complete interrupt.
 *                    @arg DMA1_INT_FLAG_HT7   : DMA1 Channel7 half transfer interrupt.
 *                    @arg DMA1_INT_FLAG_TERR7 : DMA1 Channel7 transfer error interrupt.

 *                    @arg DMA2_INT_FLAG_GINT1 : DMA2 Channel 1 global interrupt.
 *                    @arg DMA2_INT_FLAG_TC1   : DMA2 Channel 1 transfer complete interrupt.
 *                    @arg DMA2_INT_FLAG_HT1   : DMA2 Channel 1 half transfer interrupt.
 *                    @arg DMA2_INT_FLAG_TERR1 : DMA2 Channel 1 transfer error interrupt.
 *                    @arg DMA2_INT_FLAG_GINT2 : DMA2 Channel 2 global interrupt.
 *                    @arg DMA2_INT_FLAG_TC2   : DMA2 Channel 2 transfer complete interrupt.
 *                    @arg DMA2_INT_FLAG_HT2   : DMA2 Channel 2 half transfer interrupt.
 *                    @arg DMA2_INT_FLAG_TERR2 : DMA2 Channel 2 transfer error interrupt.
 *                    @arg DMA2_INT_FLAG_GINT3 : DMA2 Channel 3 global interrupt.
 *                    @arg DMA2_INT_FLAG_TC3   : DMA2 Channel 3 transfer complete interrupt.
 *                    @arg DMA2_INT_FLAG_HT3   : DMA2 Channel 3 half transfer interrupt.
 *                    @arg DMA2_INT_FLAG_TERR3 : DMA2 Channel 3 transfer error interrupt.
 *                    @arg DMA2_INT_FLAG_GINT4 : DMA2 Channel 4 global interrupt.
 *                    @arg DMA2_INT_FLAG_TC4   : DMA2 Channel 4 transfer complete interrupt.
 *                    @arg DMA2_INT_FLAG_HT4   : DMA2 Channel 4 half transfer interrupt.
 *                    @arg DMA2_INT_FLAG_TERR4 : DMA2 Channel 4 transfer error interrupt.
 *                    @arg DMA2_INT_FLAG_GINT5 : DMA2 Channel 5 global interrupt.
 *                    @arg DMA2_INT_FLAG_TC5   : DMA2 Channel 5 transfer complete interrupt.
 *                    @arg DMA2_INT_FLAG_HT5   : DMA2 Channel 5 half transfer interrupt.
 *                    @arg DMA2_INT_FLAG_TERR5 : DMA2 Channel 5 transfer error interrupt.
 *
 * @retval    None
 *
 * @note      DMA2 Channel only for APM32 High density devices.
 */
void DMA_ClearIntFlag(uint32_t flag)
{
    if ((flag & 0x10000000) != RESET)
    {
        DMA2->INTFCLR = flag;
    }
    else
    {
        DMA1->INTFCLR = flag;
    }
}

/**@} end of group DMA_Functions*/
/**@} end of group DMA_Driver*/
/**@} end of group APM32F10x_StdPeriphDriver */
