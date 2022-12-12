/*!
 * @file        apm32f4xx_dma.c
 *
 * @brief       This file provides all the DMA firmware functions
 *
 * @version     V1.0.2
 *
 * @date        2022-06-23
 *
 * @attention
 *
 *  Copyright (C) 2021-2022 Geehy Semiconductor
 *
 *  You may not use this file except in compliance with the
 *  GEEHY COPYRIGHT NOTICE (GEEHY SOFTWARE PACKAGE LICENSE).
 *
 *  The program is only for reference, which is distributed in the hope
 *  that it will be usefull and instructional for customers to develop
 *  their software. Unless required by applicable law or agreed to in
 *  writing, the program is distributed on an "AS IS" BASIS, WITHOUT
 *  ANY WARRANTY OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the GEEHY SOFTWARE PACKAGE LICENSE for the governing permissions
 *  and limitations under the License.
 */

#include "apm32f4xx_dma.h"
#include "apm32f4xx_rcm.h"

/** @addtogroup APM32F4xx_StdPeriphDriver
  @{
*/

/** @defgroup DMA_Driver
  * @brief DMA driver modules
  @{
*/

/** @defgroup DMA_Functions
  @{
*/

/*!
 * @brief     Reset specified DMA Stream registers to their default reset
 *
 * @param     stream :DMAy_streamx(y can be 1 or 2 and x can be from 0 to 7)
 *
 * @retval    None
 *
 * @note      DMA2 channel only for APM32 High density devices.
 */
void DMA_Reset(DMA_Stream_T *stream)
{
    stream->SCFG_B.EN  =  BIT_RESET;
    stream->SCFG       =  0;
    stream->NDATA      =  0;
    stream->PADDR      =  0;
    stream->M0ADDR     =  0;
    stream->M1ADDR     =  0;
    stream->FCTRL      = (uint32_t)0x00000021;

    if (stream == DMA1_Stream0)
    {
        DMA1->LIFCLR |=  0x0000003D;
    }
    else if (stream == DMA1_Stream1)
    {
        DMA1->LIFCLR |=  0X00000F40;
    }
    else if (stream == DMA1_Stream2)
    {
        DMA1->LIFCLR |=  0x003D0000;
    }
    else if (stream == DMA1_Stream3)
    {
        DMA1->LIFCLR |=  0X0F400000;
    }
    else if (stream == DMA1_Stream4)
    {
        DMA1->HIFCLR |=  0x0000003D;
    }
    else if (stream == DMA1_Stream5)
    {
        DMA1->HIFCLR |=  0X00000F40;
    }
    else if (stream == DMA1_Stream6)
    {
        DMA1->HIFCLR |=  0x003D0000;
    }
    else if (stream == DMA1_Stream7)
    {
        DMA1->HIFCLR |=  0X0F400000;
    }
    else if (stream == DMA2_Stream0)
    {
        DMA2->LIFCLR |=  0x0000003D;
    }
    else if (stream == DMA2_Stream1)
    {
        DMA2->LIFCLR |=  0X00000F40;
    }
    else if (stream == DMA2_Stream2)
    {
        DMA2->LIFCLR |=  0x003D0000;
    }
    else if (stream == DMA2_Stream3)
    {
        DMA2->LIFCLR |=  0X0F400000;
    }
    else if (stream == DMA2_Stream4)
    {
        DMA2->HIFCLR |=  0x0000003D;
    }
    else if (stream == DMA2_Stream5)
    {
        DMA2->HIFCLR |=  0X00000F40;
    }
    else if (stream == DMA2_Stream6)
    {
        DMA2->HIFCLR |=  0x003D0000;
    }
    else if (stream == DMA2_Stream7)
    {
        DMA2->HIFCLR |=  0X0F400000;
    }
}

/*!
 * @brief     Configs specified DMA channel through a structure.
 *
 * @param     stream:DMA1_channelx(y can be 1 or 2 and x can be from 0 to 7).
 *
 * @param     dmaConfig: Point to a DMA_Config_T structure
 *
 * @retval    None
 *
 * @note      DMA2 channel only for APM32 High density devices.
 */
void DMA_Config(DMA_Stream_T *stream, DMA_Config_T *dmaConfig)
{
    stream->SCFG_B.DIRCFG = dmaConfig->dir;
    stream->SCFG_B.CIRCMEN = dmaConfig->loopMode;
    stream->SCFG_B.PERIM = dmaConfig->peripheralInc;
    stream->SCFG_B.MEMIM = dmaConfig->memoryInc;
    stream->SCFG_B.PERSIZECFG = dmaConfig->peripheralDataSize;
    stream->SCFG_B.MEMSIZECFG = dmaConfig->memoryDataSize;
    stream->SCFG_B.PRILCFG = dmaConfig->priority;
    stream->SCFG_B.PBCFG = dmaConfig->peripheralBurst;
    stream->SCFG_B.MBCFG = dmaConfig->memoryBurst;
    stream->SCFG_B.CHSEL = dmaConfig->channel;

    stream->NDATA  = dmaConfig->bufferSize;
    stream->PADDR  = dmaConfig->peripheralBaseAddr;
    stream->M0ADDR = dmaConfig->memoryBaseAddr;

    stream->FCTRL_B.DMDEN  = dmaConfig->fifoMode;
    stream->FCTRL_B.FTHSEL = dmaConfig->fifoThreshold;
}

/*!
 * @brief     Populate the structure with default values.
 *
 * @param     dmaConfig: Point to a DMA_Config_T structure.
 *
 * @retval    None
 */
void DMA_ConfigStructInit(DMA_Config_T *dmaConfig)
{
    dmaConfig->channel = DMA_CHANNEL_0;
    dmaConfig->peripheralBaseAddr = 0;
    dmaConfig->memoryBaseAddr = 0;
    dmaConfig->dir = DMA_DIR_PERIPHERALTOMEMORY;
    dmaConfig->bufferSize = 0;
    dmaConfig->peripheralInc = DMA_PERIPHERAL_INC_DISABLE;
    dmaConfig->memoryInc = DMA_MEMORY_INC_DISABLE;
    dmaConfig->peripheralDataSize = DMA_PERIPHERAL_DATA_SIZE_BYTE;
    dmaConfig->memoryDataSize = DMA_MEMORY_DATA_SIZE_BYTE;
    dmaConfig->loopMode = DMA_MODE_NORMAL;
    dmaConfig->priority = DMA_PRIORITY_LOW;
    dmaConfig->fifoMode = DMA_FIFOMODE_DISABLE;
    dmaConfig->fifoThreshold = DMA_FIFOTHRESHOLD_QUARTER;
    dmaConfig->peripheralBurst = DMA_PERIPHERALBURST_SINGLE;
    dmaConfig->memoryBurst = DMA_MEMORYBURST_SINGLE;
}

/*!
 * @brief     Enable the specified DMA channel
 *
 * @param     stream:DMAy_streamx(y can be 1 or 2 and x can be from 1 to 7)
 *
 * @retval    None
 *
 * @note      DMA2 channel only for APM32 High density devices.
 */
void DMA_Enable(DMA_Stream_T *stream)
{
    stream->SCFG_B.EN = ENABLE;
}

/*!
 * @brief     Disable the specified DMA channel
 *
 * @param     stream:DMAy_streamx(y can be 1 or 2 and x can be from 1 to 7)
 *
 * @retval    None
 *
 * @note      DMA2 channel only for APM32 High density devices.
 */
void DMA_Disable(DMA_Stream_T *stream)
{
    stream->SCFG_B.EN = DISABLE;
}

/*!
 * @brief     Configures the specified DMA Peripheral increment offset size.
 *
 * @param     perioSize: specifies the Peripheral increment offset size.
 *                       This parameter can be one of the following values:
 *                        @arg DMA_PERIOSIZE_PSIZE: Peripheral address increment is done
 *                                                  accordingly to PSIZE parameter.
 *                        @arg DMA_PERIOSIZE_WORDALIGNED: Peripheral address increment offset is
 *                                                  fixed to 4 (32-bit aligned addresses).
 *
 * @retval    None
 *
 * @note      DMA2 Stream only for APM32 High density devices.
 */
void DMA_ConfigPeriphIncOffsetSize(DMA_Stream_T *stream, DMA_PERIOSIZE_T perioSize)
{
    stream->SCFG_B.PERIOSIZE = perioSize;
}

/*!
 * @brief     Configures the specified DMA flow controller.
 *
 * @param     stream:DMAy_streamx(y can be 1 or 2 and x can be from 1 to 7)
 *
 * @param     flowController: specifies the DMA flow controller.
 *                             This parameter can be one of the following values:
 *                             @arg DMA_FLOWCTRL_MEMORY: DMAy_Channelx transactions flow controller is
 *                                                       the DMA controller.
 *                             @arg DMA_FLOWCTRL_PERIPHERAL: DMAy_Channelx transactions flow controller
 *                                                       is the peripheral.
 *
 * @retval    None
 *
 * @note      DMA2 Stream only for APM32 High density devices.
 */
void DMA_ConfigFlowController(DMA_Stream_T *stream, DMA_FLOWCTRL_T flowController)
{
    stream->SCFG_B.PERFC = flowController;
}

/*!
 * @brief     Configs the number of data units in the channel.
 *
 * @param     stream:DMAy_streamx(y can be 1 or 2 and x can be from 1 to 7)
 *
 * @param     dataNumber:The number of data units in the current DMA Stream transfer.
 *
 * @retval    The number of NDATA value
 *
 * @note      DMA2 Stream only for APM32 High density devices.
 */
void DMA_ConfigDataNumber(DMA_Stream_T *stream, uint16_t dataNumber)
{
    stream->NDATA = dataNumber;
}

/*!
 * @brief     Read the number of data units in the channel
 *
 * @param     stream:DMAy_streamx(y can be 1 or 2 and x can be from 1 to 7)
 *
 * @retval    The number of NDATA value
 *
 * @note      DMA2 Stream only for APM32 High density devices.
 */
uint16_t DMA_ReadDataNumber(DMA_Stream_T *stream)
{
    return (uint16_t)(stream->NDATA);
}

/*!
 * @brief     Configures the double buffer mode and the current memory target.
 *
 * @param     stream:DMAy_streamx(y can be 1 or 2 and x can be from 1 to 7)
 *
 * @param     memory1BaseAddr: the base address of the second buffer (Memory 1)
 *
 * @param     currentMemory: specifies which memory will be first buffer for
 *               the transactions when the Stream will be enabled.
 *                  This parameter can be one of the following values:
 *                    @arg DMA_MEMORY_0: Memory 0 is the current buffer.
 *                    @arg DMA_MEMORY_1: Memory 1 is the current buffer.
 *
 * @retval    None
 */
void DMA_ConfigBufferMode(DMA_Stream_T *stream, uint32_t memory1BaseAddr, DMA_MEMORY_T currentMemory)
{
    stream->SCFG_B.CTARG = currentMemory;
    stream->M1ADDR = memory1BaseAddr;
}

/*!
 * @brief     Enable the double buffer mode for the selected DMA channel.
 *
 * @param     stream: DMAy_streamx(y can be 1 or 2 and x can be from 1 to 7)
 *
 * @retval    None
 */
void DMA_EnableDoubleBufferMode(DMA_Stream_T *stream)
{
    stream->SCFG_B.DBM = BIT_SET;
}

/*!
 * @brief     Disable the double buffer mode for the selected DMA channel.
 *
 * @param     stream: DMAy_streamx(y can be 1 or 2 and x can be from 1 to 7)
 *
 * @retval    None
 */
void DMA_DisableDoubleBufferMode(DMA_Stream_T *stream)
{
    stream->SCFG_B.DBM = BIT_RESET;
}

/*!
 * @brief     Configures the Memory address for the next buffer transfer in double
 *               buffer mode (for dynamic use).
 *
 * @param     stream:DMAy_streamx(y can be 1 or 2 and x can be from 1 to 7)
 *
 * @param     memoryBaseAddr: The base address of the target memory buffer
 *
 * @param     memoryTarget: Next memory target to be used.
 *               This parameter can be one of the following values:
 *                  @arg DMA_MEMORY_0: To use the memory address 0
 *                  @arg DMA_MEMORY_1: To use the memory address 1
 *
 * @retval       None
 */
void DMA_ConfigMemoryTarget(DMA_Stream_T *stream, uint32_t memoryBaseAddr, DMA_MEMORY_T memoryTarget)
{
    if (memoryTarget != DMA_MEMORY_0)
    {
        stream->M1ADDR = memoryBaseAddr;
    }
    else
    {
        stream->M0ADDR = memoryBaseAddr;
    }
}

/*!
 * @brief     Returns the current memory target used by double buffer transfer.
 *
 * @param     stream:DMAy_streamx(y can be 1 or 2 and x can be from 1 to 7)
 *
 * @retval    The memory target number: 0 for Memory0 or 1 for Memory1.
 */
uint32_t DMA_ReadCurrentMemoryTarget(DMA_Stream_T *stream)
{
    return (uint32_t)(stream->SCFG_B.CTARG);
}

/*!
 * @brief      Returns the status of EN bit for the specified DMAy channelx.
 *
 * @param      stream:DMAy_streamx(y can be 1 or 2 and x can be from 1 to 7)
 *
 * @retval     Return state of the DMAy channelx (ENABLE or DISABLE).
 */
uint8_t DMA_ReadCmdStatus(DMA_Stream_T *stream)
{
    return (uint8_t)(stream->SCFG_B.EN);
}

/*!
 * @brief      Returns the current DMAy channelx FIFO filled level.
 *
 * @param      stream:DMAy_streamx(y can be 1 or 2 and x can be from 1 to 7)
 *
 * @retval     The FIFO filling state.
 *                  - DMA_FIFOSTATUS_LESS1QUARTER: when FIFO is less than 1 quarter-full and not empty.
 *                  - DMA_FIFOSTATUS_1QUARTER: if more than 1 quarter-full.
 *                  - DMA_FIFOSTATUS_HalfFull: if more than 1 half-full.
 *                  - DMA_FIFOSTATUS_3QUARTERS: if more than 3 quarters-full.
 *                  - DMA_FIFOSTATUS_EMPTY: when FIFO is empty
 *                  - DMA_FIFOSTATUS_FULL: when FIFO is full
 */
uint32_t DMA_ReadFIFOFlag(DMA_Stream_T *stream)
{
    return (uint32_t)(stream->FCTRL_B.FSTS);
}

/*!
 * @brief     Read the specified DMAy channelx flag.
 *
 * @param     stream:DMAy_streamx(y can be 1 or 2 and x can be from 1 to 7)
 *
 * @param     flag: specifies the flag to check.
 *                This parameter can be one of the following values:
 *                  @arg DMA_FLAG_TCIFLGx:  channelx transfer complete flag
 *                  @arg DMA_FLAG_HTIFLGx:  channelx half transfer complete flag
 *                  @arg DMA_FLAG_TEIFLGx:  channelx transfer error flag
 *                  @arg DMA_FLAG_DMEIFLGx: channelx direct mode error flag
 *                  @arg DMA_FLAG_FEIFLGx:  channelx FIFO error flag
 *               Where x can be 0 to 7 to select the DMA channel.
 *
 * @retval    None
 */
uint8_t DMA_ReadStatusFlag(DMA_Stream_T *stream, DMA_FLAG_T flag)
{
    DMA_T *dma;

    if (stream < DMA2_Stream0)
    {
        dma = DMA1;
    }
    else
    {
        dma = DMA2;
    }

    if ((flag & 0x10000000) != RESET)
    {
        if ((dma->LINTSTS & flag) != RESET)
        {
            return  SET;
        }
        else
        {
            return RESET;
        }
    }
    else
    {
        if ((dma->HINTSTS & flag) != RESET)
        {
            return  SET;
        }
        else
        {
            return RESET;
        }
    }
}

/*!
 * @brief     Clears the DMAy channelx's pending flags.
 *
 * @param     stream:DMAy_streamx(y can be 1 or 2 and x can be from 1 to 7)
 *
 * @param     flag: specifies the flag to clear.
 *                This parameter can be any combination of the following values:
 *                  @arg DMA_FLAG_TCIFLGx:  channelx transfer complete flag
 *                  @arg DMA_FLAG_HTIFLGx:  channelx half transfer complete flag
 *                  @arg DMA_FLAG_TEIFLGx:  channelx transfer error flag
 *                  @arg DMA_FLAG_DMEIFLGx: channelx direct mode error flag
 *                  @arg DMA_FLAG_FEIFLGx:  channelx FIFO error flag
 *               Where x can be 0 to 7 to select the DMA channel.
 *
 * @retval    None
 */
void DMA_ClearStatusFlag(DMA_Stream_T *stream, uint32_t flag)
{
    DMA_T *dma;

    if (stream < DMA2_Stream0)
    {
        dma = DMA1;
    }
    else
    {
        dma = DMA2;
    }

    if ((flag & 0x10000000) == RESET)
    {
        dma->LIFCLR = (flag & 0x0F7D0F7D);
    }
    else
    {
        dma->HIFCLR = (flag & 0x0F7D0F7D);
    }
}

/*!
 * @brief     Enable the specified DMAy channelx interrupts.
 *
 * @param     stream:DMAy_streamx(y can be 1 or 2 and x can be from 1 to 7)
 *
 * @param     flag: specifies the DMA interrupt sources to be enabled or disabled.
 *                This parameter can be any combination of the following values:
 *                  @arg DMA_INT_TCIFLG:  Transfer complete interrupt mask
 *                  @arg DMA_INT_HTIFLG:  Half transfer complete interrupt mask
 *                  @arg DMA_INT_TEIFLG:  Transfer error interrupt mask
 *                  @arg DMA_INT_FEIFLG:  FIFO error interrupt mask
 *
 * @retval    None
 */
void DMA_EnableInterrupt(DMA_Stream_T *stream, uint32_t interrupt)
{
    if ((interrupt & DMA_INT_FEIFLG) == DMA_INT_FEIFLG)
    {
        stream->FCTRL_B.FEIEN = BIT_SET;;
    }

    if (interrupt != DMA_INT_FEIFLG)
    {
        stream->SCFG |= (uint32_t)(interrupt & 0x0000001E);
    }
}

/*!
 * @brief     Disable the specified DMAy channelx interrupts.
 *
 * @param     stream:DMAy_streamx(y can be 1 or 2 and x can be from 1 to 7)
 *
 * @param     flag: specifies the DMA interrupt sources to be enabled or disabled.
 *                This parameter can be any combination of the following values:
 *                  @arg DMA_INT_TCIFLG:  Transfer complete interrupt mask
 *                  @arg DMA_INT_DMEIFLG:  Direct mode error interrupt mask
 *                  @arg DMA_INT_HTIFLG:  Half transfer complete interrupt mask
 *                  @arg DMA_INT_TEIFLG:  Transfer error interrupt mask
 *                  @arg DMA_INT_FEIFLG:  FIFO error interrupt mask
 *
 * @retval    None
 */
void DMA_DisableInterrupt(DMA_Stream_T *stream, uint32_t interrupt)
{
    if ((interrupt & DMA_INT_FEIFLG) == DMA_INT_FEIFLG)
    {
        stream->FCTRL_B.FEIEN = BIT_RESET;;
    }

    if (interrupt != DMA_INT_FEIFLG)
    {
        stream->SCFG &= ~(uint32_t)(interrupt & 0x0000001E);
    }
}

/*!
 * @brief     Read the specified DMAy channelx interrupt.
 *
 * @param     stream:DMAy_streamx(y can be 1 or 2 and x can be from 1 to 7)
 *
 * @param     flag: specifies the DMA interrupt source to check.
 *                This parameter can be one of the following values:
 *                  @arg DMA_INT_TCIFLGx:  streamx transfer complete flag
 *                  @arg DMA_INT_HTIFLGx:  streamx half transfer complete flag
 *                  @arg DMA_INT_TEIFLGx:  streamx transfer error flag
 *                  @arg DMA_INT_DMEIFLGx: streamx direct mode error flag
 *                  @arg DMA_INT_FEIFLGx:  streamx FIFO error flag
 *                 Where x can be 0 to 7 to select the DMA channel.
 *
 * @retval    None.
 */
uint8_t DMA_ReadIntFlag(DMA_Stream_T *stream, DMA_INT_FLAG_T flag)
{
    uint32_t tmpreg = 0, enablestatus = 0;
    DMA_T *dma;

    if (stream < DMA2_Stream0)
    {
        dma = DMA1;
    }
    else
    {
        dma = DMA2;
    }

    /** Check if the interrupt enable bit is in the FCTRL or SCFG register */
    if ((flag & 0x60000000) != RESET)
    {
        /** Check the enable bit in FEIEN register */
        enablestatus = stream->FCTRL_B.FEIEN;
    }
    else
    {
        /** Get the interrupt enable position mask in SCFG register */
        tmpreg = ((flag & 0xE000) >> 11) ;

        /** Check the enable bit in SCFG register */
        enablestatus = (stream->SCFG & tmpreg);
    }

    /* Check if the interrupt pending flag is in LINTSTS or HINTSTS */
    if ((flag & 0x10000000) == RESET)
    {
        tmpreg = dma->LINTSTS;
    }
    else
    {
        tmpreg = dma->HINTSTS;
    }

    tmpreg &= 0x0F7D0F7D;

    if (((tmpreg & flag) != RESET) && (enablestatus != RESET))
    {
        return SET ;
    }
    else
    {
        return RESET ;
    }
}

/*!
 * @brief     Read the DMAy channelx's interrupt pending bits.
 *
 * @param     stream:DMAy_streamx(y can be 1 or 2 and x can be from 1 to 7)
 *
 * @param     flag: specifies the DMA interrupt pending bit to clear.
 *                This parameter can be any combination of the following values:
 *                  @arg DMA_INT_TCIFLGx:  streamx transfer complete flag
 *                  @arg DMA_INT_HTIFLGx:  streamx half transfer complete flag
 *                  @arg DMA_INT_TEIFLGx:  streamx transfer error flag
 *                  @arg DMA_INT_DMEIFLGx: streamx direct mode error flag
 *                  @arg DMA_INT_FEIFLGx:  streamx FIFO error flag
 *               Where x can be 0 to 7 to select the DMA channel.
 *
 * @retval    None
 */
void DMA_ClearIntFlag(DMA_Stream_T *stream, uint32_t flag)
{
    DMA_T *dma;

    if (stream < DMA2_Stream0)
    {
        dma = DMA1;
    }
    else
    {
        dma = DMA2;
    }

    if ((flag & 0x10000000) == RESET)
    {
        dma->LIFCLR = (flag & 0x0F7D0F7D);
    }
    else
    {
        dma->HIFCLR = (flag & 0x0F7D0F7D);
    }
}

/**@} end of group DMA_Functions */
/**@} end of group DMA_Driver */
/**@} end of group APM32F4xx_StdPeriphDriver */
