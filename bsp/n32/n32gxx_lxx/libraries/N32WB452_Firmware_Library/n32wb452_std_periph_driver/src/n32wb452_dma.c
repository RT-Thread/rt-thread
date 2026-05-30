/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file n32wb452_dma.c
 * @author Nations
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "n32wb452_dma.h"
#include "n32wb452_rcc.h"

/** @addtogroup N32WB452_StdPeriph_Driver
 * @{
 */

/** @addtogroup DMA
 * @brief DMA driver modules
 * @{
 */

/** @addtogroup DMA_Private_TypesDefinitions
 * @{
 */
/**
 * @}
 */

/** @addtogroup DMA_Private_Defines
 * @{
 */

/* DMA1 Channelx interrupt pending bit masks */
#define DMA1_CH1_INT_MASK ((uint32_t)(DMA_INTSTS_GLBF1 | DMA_INTSTS_TXCF1 | DMA_INTSTS_HTXF1 | DMA_INTSTS_ERRF1))
#define DMA1_CH2_INT_MASK ((uint32_t)(DMA_INTSTS_GLBF2 | DMA_INTSTS_TXCF2 | DMA_INTSTS_HTXF2 | DMA_INTSTS_ERRF2))
#define DMA1_CH3_INT_MASK ((uint32_t)(DMA_INTSTS_GLBF3 | DMA_INTSTS_TXCF3 | DMA_INTSTS_HTXF3 | DMA_INTSTS_ERRF3))
#define DMA1_CH4_INT_MASK ((uint32_t)(DMA_INTSTS_GLBF4 | DMA_INTSTS_TXCF4 | DMA_INTSTS_HTXF4 | DMA_INTSTS_ERRF4))
#define DMA1_CH5_INT_MASK ((uint32_t)(DMA_INTSTS_GLBF5 | DMA_INTSTS_TXCF5 | DMA_INTSTS_HTXF5 | DMA_INTSTS_ERRF5))
#define DMA1_CH6_INT_MASK ((uint32_t)(DMA_INTSTS_GLBF6 | DMA_INTSTS_TXCF6 | DMA_INTSTS_HTXF6 | DMA_INTSTS_ERRF6))
#define DMA1_CH7_INT_MASK ((uint32_t)(DMA_INTSTS_GLBF7 | DMA_INTSTS_TXCF7 | DMA_INTSTS_HTXF7 | DMA_INTSTS_ERRF7))
#define DMA1_CH8_INT_MASK ((uint32_t)(DMA_INTSTS_GLBF8 | DMA_INTSTS_TXCF8 | DMA_INTSTS_HTXF8 | DMA_INTSTS_ERRF8))

/* DMA2 Channelx interrupt pending bit masks */
#define DMA2_CH1_INT_MASK ((uint32_t)(DMA_INTSTS_GLBF1 | DMA_INTSTS_TXCF1 | DMA_INTSTS_HTXF1 | DMA_INTSTS_ERRF1))
#define DMA2_CH2_INT_MASK ((uint32_t)(DMA_INTSTS_GLBF2 | DMA_INTSTS_TXCF2 | DMA_INTSTS_HTXF2 | DMA_INTSTS_ERRF2))
#define DMA2_CH3_INT_MASK ((uint32_t)(DMA_INTSTS_GLBF3 | DMA_INTSTS_TXCF3 | DMA_INTSTS_HTXF3 | DMA_INTSTS_ERRF3))
#define DMA2_CH4_INT_MASK ((uint32_t)(DMA_INTSTS_GLBF4 | DMA_INTSTS_TXCF4 | DMA_INTSTS_HTXF4 | DMA_INTSTS_ERRF4))
#define DMA2_CH5_INT_MASK ((uint32_t)(DMA_INTSTS_GLBF5 | DMA_INTSTS_TXCF5 | DMA_INTSTS_HTXF5 | DMA_INTSTS_ERRF5))
#define DMA2_CH6_INT_MASK ((uint32_t)(DMA_INTSTS_GLBF6 | DMA_INTSTS_TXCF6 | DMA_INTSTS_HTXF6 | DMA_INTSTS_ERRF6))
#define DMA2_CH7_INT_MASK ((uint32_t)(DMA_INTSTS_GLBF7 | DMA_INTSTS_TXCF7 | DMA_INTSTS_HTXF7 | DMA_INTSTS_ERRF7))
#define DMA2_CH8_INT_MASK ((uint32_t)(DMA_INTSTS_GLBF8 | DMA_INTSTS_TXCF8 | DMA_INTSTS_HTXF8 | DMA_INTSTS_ERRF8))

/* DMA registers Masks */
#define CCR_CLEAR_Mask ((uint32_t)0xFFFF800F)

/**
 * @}
 */

/** @addtogroup DMA_Private_Macros
 * @{
 */

/**
 * @}
 */

/** @addtogroup DMA_Private_Variables
 * @{
 */

/**
 * @}
 */

/** @addtogroup DMA_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @addtogroup DMA_Private_Functions
 * @{
 */

/**
 * @brief  Deinitializes the DMAy Channelx registers to their default reset
 *         values.
 * @param DMAyChx where y can be 1 or 2 to select the DMA and
 *   x can be 1 to 8 for DMA1 and 1 to 8 for DMA2 to select the DMA Channel.
 */
void DMA_DeInit(DMA_ChannelType* DMAyChx)
{
    /* Check the parameters */
    assert_param(IS_DMA_ALL_PERIPH(DMAyChx));

    /* Disable the selected DMAy Channelx */
    DMAyChx->CHCFG &= (uint16_t)(~DMA_CHCFG1_CHEN);

    /* Reset DMAy Channelx control register */
    DMAyChx->CHCFG = 0;

    /* Reset DMAy Channelx remaining bytes register */
    DMAyChx->TXNUM = 0;

    /* Reset DMAy Channelx peripheral address register */
    DMAyChx->PADDR = 0;

    /* Reset DMAy Channelx memory address register */
    DMAyChx->MADDR = 0;

    if (DMAyChx == DMA1_CH1)
    {
        /* Reset interrupt pending bits for DMA1 Channel1 */
        DMA1->INTCLR |= DMA1_CH1_INT_MASK;
    }
    else if (DMAyChx == DMA1_CH2)
    {
        /* Reset interrupt pending bits for DMA1 Channel2 */
        DMA1->INTCLR |= DMA1_CH2_INT_MASK;
    }
    else if (DMAyChx == DMA1_CH3)
    {
        /* Reset interrupt pending bits for DMA1 Channel3 */
        DMA1->INTCLR |= DMA1_CH3_INT_MASK;
    }
    else if (DMAyChx == DMA1_CH4)
    {
        /* Reset interrupt pending bits for DMA1 Channel4 */
        DMA1->INTCLR |= DMA1_CH4_INT_MASK;
    }
    else if (DMAyChx == DMA1_CH5)
    {
        /* Reset interrupt pending bits for DMA1 Channel5 */
        DMA1->INTCLR |= DMA1_CH5_INT_MASK;
    }
    else if (DMAyChx == DMA1_CH6)
    {
        /* Reset interrupt pending bits for DMA1 Channel6 */
        DMA1->INTCLR |= DMA1_CH6_INT_MASK;
    }
    else if (DMAyChx == DMA1_CH7)
    {
        /* Reset interrupt pending bits for DMA1 Channel7 */
        DMA1->INTCLR |= DMA1_CH7_INT_MASK;
    }
    else if (DMAyChx == DMA1_CH8)
    {
        /* Reset interrupt pending bits for DMA1 Channel8 */
        DMA1->INTCLR |= DMA1_CH8_INT_MASK;
    }
    else if (DMAyChx == DMA2_CH1)
    {
        /* Reset interrupt pending bits for DMA2 Channel1 */
        DMA2->INTCLR |= DMA2_CH1_INT_MASK;
    }
    else if (DMAyChx == DMA2_CH2)
    {
        /* Reset interrupt pending bits for DMA2 Channel2 */
        DMA2->INTCLR |= DMA2_CH2_INT_MASK;
    }
    else if (DMAyChx == DMA2_CH3)
    {
        /* Reset interrupt pending bits for DMA2 Channel3 */
        DMA2->INTCLR |= DMA2_CH3_INT_MASK;
    }
    else if (DMAyChx == DMA2_CH4)
    {
        /* Reset interrupt pending bits for DMA2 Channel4 */
        DMA2->INTCLR |= DMA2_CH4_INT_MASK;
    }
    else if (DMAyChx == DMA2_CH5)
    {
        /* Reset interrupt pending bits for DMA2 Channel5 */
        DMA2->INTCLR |= DMA2_CH5_INT_MASK;
    }
    else if (DMAyChx == DMA2_CH6)
    {
        /* Reset interrupt pending bits for DMA2 Channel6 */
        DMA2->INTCLR |= DMA2_CH6_INT_MASK;
    }
    else if (DMAyChx == DMA2_CH7)
    {
        /* Reset interrupt pending bits for DMA2 Channel7 */
        DMA2->INTCLR |= DMA2_CH7_INT_MASK;
    }
    else
    {
        if (DMAyChx == DMA2_CH8)
        {
            /* Reset interrupt pending bits for DMA2 Channel8 */
            DMA2->INTCLR |= DMA2_CH8_INT_MASK;
        }
    }
}

/**
 * @brief  Initializes the DMAy Channelx according to the specified
 *         parameters in the DMA_InitParam.
 * @param DMAyChx where y can be 1 or 2 to select the DMA and
 *   x can be 1 to 8 for DMA1 and 1 to 8 for DMA2 to select the DMA Channel.
 * @param DMA_InitParam pointer to a DMA_InitType structure that
 *         contains the configuration information for the specified DMA Channel.
 */
void DMA_Init(DMA_ChannelType* DMAyChx, DMA_InitType* DMA_InitParam)
{
    uint32_t tmpregister = 0;

    /* Check the parameters */
    assert_param(IS_DMA_ALL_PERIPH(DMAyChx));
    assert_param(IS_DMA_DIR(DMA_InitParam->Direction));
    assert_param(IS_DMA_BUF_SIZE(DMA_InitParam->BufSize));
    assert_param(IS_DMA_PERIPH_INC_STATE(DMA_InitParam->PeriphInc));
    assert_param(IS_DMA_MEM_INC_STATE(DMA_InitParam->DMA_MemoryInc));
    assert_param(IS_DMA_PERIPH_DATA_SIZE(DMA_InitParam->PeriphDataSize));
    assert_param(IS_DMA_MEMORY_DATA_SIZE(DMA_InitParam->MemDataSize));
    assert_param(IS_DMA_MODE(DMA_InitParam->CircularMode));
    assert_param(IS_DMA_PRIORITY(DMA_InitParam->Priority));
    assert_param(IS_DMA_M2M_STATE(DMA_InitParam->Mem2Mem));

    /*--------------------------- DMAy Channelx CHCFG Configuration -----------------*/
    /* Get the DMAyChx CHCFG value */
    tmpregister = DMAyChx->CHCFG;
    /* Clear MEM2MEM, PL, MSIZE, PSIZE, MINC, PINC, CIRC and DIR bits */
    tmpregister &= CCR_CLEAR_Mask;
    /* Configure DMAy Channelx: data transfer, data size, priority level and mode */
    /* Set DIR bit according to Direction value */
    /* Set CIRC bit according to CircularMode value */
    /* Set PINC bit according to PeriphInc value */
    /* Set MINC bit according to DMA_MemoryInc value */
    /* Set PSIZE bits according to PeriphDataSize value */
    /* Set MSIZE bits according to MemDataSize value */
    /* Set PL bits according to Priority value */
    /* Set the MEM2MEM bit according to Mem2Mem value */
    tmpregister |= DMA_InitParam->Direction | DMA_InitParam->CircularMode | DMA_InitParam->PeriphInc
                   | DMA_InitParam->DMA_MemoryInc | DMA_InitParam->PeriphDataSize | DMA_InitParam->MemDataSize
                   | DMA_InitParam->Priority | DMA_InitParam->Mem2Mem;

    /* Write to DMAy Channelx CHCFG */
    DMAyChx->CHCFG = tmpregister;

    /*--------------------------- DMAy Channelx TXNUM Configuration ---------------*/
    /* Write to DMAy Channelx TXNUM */
    DMAyChx->TXNUM = DMA_InitParam->BufSize;

    /*--------------------------- DMAy Channelx PADDR Configuration ----------------*/
    /* Write to DMAy Channelx PADDR */
    DMAyChx->PADDR = DMA_InitParam->PeriphAddr;

    /*--------------------------- DMAy Channelx MADDR Configuration ----------------*/
    /* Write to DMAy Channelx MADDR */
    DMAyChx->MADDR = DMA_InitParam->MemAddr;
}

/**
 * @brief  Fills each DMA_InitParam member with its default value.
 * @param DMA_InitParam pointer to a DMA_InitType structure which will
 *         be initialized.
 */
void DMA_StructInit(DMA_InitType* DMA_InitParam)
{
    /*-------------- Reset DMA init structure parameters values ------------------*/
    /* Initialize the PeriphAddr member */
    DMA_InitParam->PeriphAddr = 0;
    /* Initialize the MemAddr member */
    DMA_InitParam->MemAddr = 0;
    /* Initialize the Direction member */
    DMA_InitParam->Direction = DMA_DIR_PERIPH_SRC;
    /* Initialize the BufSize member */
    DMA_InitParam->BufSize = 0;
    /* Initialize the PeriphInc member */
    DMA_InitParam->PeriphInc = DMA_PERIPH_INC_DISABLE;
    /* Initialize the DMA_MemoryInc member */
    DMA_InitParam->DMA_MemoryInc = DMA_MEM_INC_DISABLE;
    /* Initialize the PeriphDataSize member */
    DMA_InitParam->PeriphDataSize = DMA_PERIPH_DATA_SIZE_BYTE;
    /* Initialize the MemDataSize member */
    DMA_InitParam->MemDataSize = DMA_MemoryDataSize_Byte;
    /* Initialize the CircularMode member */
    DMA_InitParam->CircularMode = DMA_MODE_NORMAL;
    /* Initialize the Priority member */
    DMA_InitParam->Priority = DMA_PRIORITY_LOW;
    /* Initialize the Mem2Mem member */
    DMA_InitParam->Mem2Mem = DMA_M2M_DISABLE;
}

/**
 * @brief  Enables or disables the specified DMAy Channelx.
 * @param DMAyChx where y can be 1 or 2 to select the DMA and
 *   x can be 1 to 8 for DMA1 and 1 to 8 for DMA2 to select the DMA Channel.
 * @param Cmd new state of the DMAy Channelx.
 *   This parameter can be: ENABLE or DISABLE.
 */
void DMA_EnableChannel(DMA_ChannelType* DMAyChx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_DMA_ALL_PERIPH(DMAyChx));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));

    if (Cmd != DISABLE)
    {
        /* Enable the selected DMAy Channelx */
        DMAyChx->CHCFG |= DMA_CHCFG1_CHEN;
    }
    else
    {
        /* Disable the selected DMAy Channelx */
        DMAyChx->CHCFG &= (uint16_t)(~DMA_CHCFG1_CHEN);
    }
}

/**
 * @brief  Enables or disables the specified DMAy Channelx interrupts.
 * @param DMAyChx where y can be 1 or 2 to select the DMA and
 *   x can be 1 to 8 for DMA1 and 1 to 8 for DMA2 to select the DMA Channel.
 * @param DMAInt specifies the DMA interrupts sources to be enabled
 *   or disabled.
 *   This parameter can be any combination of the following values:
 *     @arg DMA_INT_TXC Transfer complete interrupt mask
 *     @arg DMA_INT_HTX Half transfer interrupt mask
 *     @arg DMA_INT_ERR Transfer error interrupt mask
 * @param Cmd new state of the specified DMA interrupts.
 *   This parameter can be: ENABLE or DISABLE.
 */
void DMA_ConfigInt(DMA_ChannelType* DMAyChx, uint32_t DMAInt, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_DMA_ALL_PERIPH(DMAyChx));
    assert_param(IS_DMA_CONFIG_INT(DMAInt));
    assert_param(IS_FUNCTIONAL_STATE(Cmd));
    if (Cmd != DISABLE)
    {
        /* Enable the selected DMA interrupts */
        DMAyChx->CHCFG |= DMAInt;
    }
    else
    {
        /* Disable the selected DMA interrupts */
        DMAyChx->CHCFG &= ~DMAInt;
    }
}

/**
 * @brief  Sets the number of data units in the current DMAy Channelx transfer.
 * @param DMAyChx where y can be 1 or 2 to select the DMA and
 *         x can be 1 to 8 for DMA1 and 1 to 8 for DMA2 to select the DMA Channel.
 * @param DataNumber The number of data units in the current DMAy Channelx
 *         transfer.
 * @note   This function can only be used when the DMAyChx is disabled.
 */
void DMA_SetCurrDataCounter(DMA_ChannelType* DMAyChx, uint16_t DataNumber)
{
    /* Check the parameters */
    assert_param(IS_DMA_ALL_PERIPH(DMAyChx));

    /*--------------------------- DMAy Channelx TXNUM Configuration ---------------*/
    /* Write to DMAy Channelx TXNUM */
    DMAyChx->TXNUM = DataNumber;
}

/**
 * @brief  Returns the number of remaining data units in the current
 *         DMAy Channelx transfer.
 * @param DMAyChx where y can be 1 or 2 to select the DMA and
 *   x can be 1 to 8 for DMA1 and 1 to 8 for DMA2 to select the DMA Channel.
 * @return The number of remaining data units in the current DMAy Channelx
 *         transfer.
 */
uint16_t DMA_GetCurrDataCounter(DMA_ChannelType* DMAyChx)
{
    /* Check the parameters */
    assert_param(IS_DMA_ALL_PERIPH(DMAyChx));
    /* Return the number of remaining data units for DMAy Channelx */
    return ((uint16_t)(DMAyChx->TXNUM));
}

/**
 * @brief  Checks whether the specified DMAy Channelx flag is set or not.
 * @param DMAyFlag specifies the flag to check.
 *   This parameter can be one of the following values:
 *     @arg DMA1_FLAG_GL1 DMA1 Channel1 global flag.
 *     @arg DMA1_FLAG_TC1 DMA1 Channel1 transfer complete flag.
 *     @arg DMA1_FLAG_HT1 DMA1 Channel1 half transfer flag.
 *     @arg DMA1_FLAG_TE1 DMA1 Channel1 transfer error flag.
 *     @arg DMA1_FLAG_GL2 DMA1 Channel2 global flag.
 *     @arg DMA1_FLAG_TC2 DMA1 Channel2 transfer complete flag.
 *     @arg DMA1_FLAG_HT2 DMA1 Channel2 half transfer flag.
 *     @arg DMA1_FLAG_TE2 DMA1 Channel2 transfer error flag.
 *     @arg DMA1_FLAG_GL3 DMA1 Channel3 global flag.
 *     @arg DMA1_FLAG_TC3 DMA1 Channel3 transfer complete flag.
 *     @arg DMA1_FLAG_HT3 DMA1 Channel3 half transfer flag.
 *     @arg DMA1_FLAG_TE3 DMA1 Channel3 transfer error flag.
 *     @arg DMA1_FLAG_GL4 DMA1 Channel4 global flag.
 *     @arg DMA1_FLAG_TC4 DMA1 Channel4 transfer complete flag.
 *     @arg DMA1_FLAG_HT4 DMA1 Channel4 half transfer flag.
 *     @arg DMA1_FLAG_TE4 DMA1 Channel4 transfer error flag.
 *     @arg DMA1_FLAG_GL5 DMA1 Channel5 global flag.
 *     @arg DMA1_FLAG_TC5 DMA1 Channel5 transfer complete flag.
 *     @arg DMA1_FLAG_HT5 DMA1 Channel5 half transfer flag.
 *     @arg DMA1_FLAG_TE5 DMA1 Channel5 transfer error flag.
 *     @arg DMA1_FLAG_GL6 DMA1 Channel6 global flag.
 *     @arg DMA1_FLAG_TC6 DMA1 Channel6 transfer complete flag.
 *     @arg DMA1_FLAG_HT6 DMA1 Channel6 half transfer flag.
 *     @arg DMA1_FLAG_TE6 DMA1 Channel6 transfer error flag.
 *     @arg DMA1_FLAG_GL7 DMA1 Channel7 global flag.
 *     @arg DMA1_FLAG_TC7 DMA1 Channel7 transfer complete flag.
 *     @arg DMA1_FLAG_HT7 DMA1 Channel7 half transfer flag.
 *     @arg DMA1_FLAG_TE7 DMA1 Channel7 transfer error flag.
 *     @arg DMA1_FLAG_GL8 DMA1 Channel7 global flag.
 *     @arg DMA1_FLAG_TC8 DMA1 Channel7 transfer complete flag.
 *     @arg DMA1_FLAG_HT8 DMA1 Channel7 half transfer flag.
 *     @arg DMA1_FLAG_TE8 DMA1 Channel7 transfer error flag.
 *     @arg DMA2_FLAG_GL1 DMA2 Channel1 global flag.
 *     @arg DMA2_FLAG_TC1 DMA2 Channel1 transfer complete flag.
 *     @arg DMA2_FLAG_HT1 DMA2 Channel1 half transfer flag.
 *     @arg DMA2_FLAG_TE1 DMA2 Channel1 transfer error flag.
 *     @arg DMA2_FLAG_GL2 DMA2 Channel2 global flag.
 *     @arg DMA2_FLAG_TC2 DMA2 Channel2 transfer complete flag.
 *     @arg DMA2_FLAG_HT2 DMA2 Channel2 half transfer flag.
 *     @arg DMA2_FLAG_TE2 DMA2 Channel2 transfer error flag.
 *     @arg DMA2_FLAG_GL3 DMA2 Channel3 global flag.
 *     @arg DMA2_FLAG_TC3 DMA2 Channel3 transfer complete flag.
 *     @arg DMA2_FLAG_HT3 DMA2 Channel3 half transfer flag.
 *     @arg DMA2_FLAG_TE3 DMA2 Channel3 transfer error flag.
 *     @arg DMA2_FLAG_GL4 DMA2 Channel4 global flag.
 *     @arg DMA2_FLAG_TC4 DMA2 Channel4 transfer complete flag.
 *     @arg DMA2_FLAG_HT4 DMA2 Channel4 half transfer flag.
 *     @arg DMA2_FLAG_TE4 DMA2 Channel4 transfer error flag.
 *     @arg DMA2_FLAG_GL5 DMA2 Channel5 global flag.
 *     @arg DMA2_FLAG_TC5 DMA2 Channel5 transfer complete flag.
 *     @arg DMA2_FLAG_HT5 DMA2 Channel5 half transfer flag.
 *     @arg DMA2_FLAG_TE5 DMA2 Channel5 transfer error flag.
 *     @arg DMA2_FLAG_GL6 DMA1 Channel6 global flag.
 *     @arg DMA2_FLAG_TC6 DMA1 Channel6 transfer complete flag.
 *     @arg DMA2_FLAG_HT6 DMA1 Channel6 half transfer flag.
 *     @arg DMA2_FLAG_TE6 DMA1 Channel6 transfer error flag.
 *     @arg DMA2_FLAG_GL7 DMA1 Channel7 global flag.
 *     @arg DMA2_FLAG_TC7 DMA1 Channel7 transfer complete flag.
 *     @arg DMA2_FLAG_HT7 DMA1 Channel7 half transfer flag.
 *     @arg DMA2_FLAG_TE7 DMA1 Channel7 transfer error flag.
 *     @arg DMA2_FLAG_GL8 DMA1 Channel7 global flag.
 *     @arg DMA2_FLAG_TC8 DMA1 Channel7 transfer complete flag.
 *     @arg DMA2_FLAG_HT8 DMA1 Channel7 half transfer flag.
 *     @arg DMA2_FLAG_TE8 DMA1 Channel7 transfer error flag.
 * @param DMAy DMA1 or DMA2.
 *   This parameter can be one of the following values:
 *     @arg DMA1 .
 *     @arg DMA2 .
 * @return The new state of DMAyFlag (SET or RESET).
 */
FlagStatus DMA_GetFlagStatus(uint32_t DMAyFlag, DMA_Module* DMAy)
{
    FlagStatus bitstatus = RESET;
    uint32_t tmpregister = 0;

    /* Check the parameters */
    assert_param(IS_DMA_GET_FLAG(DMAyFlag));

    /* Calculate the used DMAy */
    /* Get DMAy INTSTS register value */
    tmpregister = DMAy->INTSTS;

    /* Check the status of the specified DMAy flag */
    if ((tmpregister & DMAyFlag) != (uint32_t)RESET)
    {
        /* DMAyFlag is set */
        bitstatus = SET;
    }
    else
    {
        /* DMAyFlag is reset */
        bitstatus = RESET;
    }

    /* Return the DMAyFlag status */
    return bitstatus;
}

/**
 * @brief  Clears the DMAy Channelx's pending flags.
 * @param DMAyFlag specifies the flag to clear.
 *   This parameter can be any combination (for the same DMA) of the following values:
 *     @arg DMA1_FLAG_GL1 DMA1 Channel1 global flag.
 *     @arg DMA1_FLAG_TC1 DMA1 Channel1 transfer complete flag.
 *     @arg DMA1_FLAG_HT1 DMA1 Channel1 half transfer flag.
 *     @arg DMA1_FLAG_TE1 DMA1 Channel1 transfer error flag.
 *     @arg DMA1_FLAG_GL2 DMA1 Channel2 global flag.
 *     @arg DMA1_FLAG_TC2 DMA1 Channel2 transfer complete flag.
 *     @arg DMA1_FLAG_HT2 DMA1 Channel2 half transfer flag.
 *     @arg DMA1_FLAG_TE2 DMA1 Channel2 transfer error flag.
 *     @arg DMA1_FLAG_GL3 DMA1 Channel3 global flag.
 *     @arg DMA1_FLAG_TC3 DMA1 Channel3 transfer complete flag.
 *     @arg DMA1_FLAG_HT3 DMA1 Channel3 half transfer flag.
 *     @arg DMA1_FLAG_TE3 DMA1 Channel3 transfer error flag.
 *     @arg DMA1_FLAG_GL4 DMA1 Channel4 global flag.
 *     @arg DMA1_FLAG_TC4 DMA1 Channel4 transfer complete flag.
 *     @arg DMA1_FLAG_HT4 DMA1 Channel4 half transfer flag.
 *     @arg DMA1_FLAG_TE4 DMA1 Channel4 transfer error flag.
 *     @arg DMA1_FLAG_GL5 DMA1 Channel5 global flag.
 *     @arg DMA1_FLAG_TC5 DMA1 Channel5 transfer complete flag.
 *     @arg DMA1_FLAG_HT5 DMA1 Channel5 half transfer flag.
 *     @arg DMA1_FLAG_TE5 DMA1 Channel5 transfer error flag.
 *     @arg DMA1_FLAG_GL6 DMA1 Channel6 global flag.
 *     @arg DMA1_FLAG_TC6 DMA1 Channel6 transfer complete flag.
 *     @arg DMA1_FLAG_HT6 DMA1 Channel6 half transfer flag.
 *     @arg DMA1_FLAG_TE6 DMA1 Channel6 transfer error flag.
 *     @arg DMA1_FLAG_GL7 DMA1 Channel7 global flag.
 *     @arg DMA1_FLAG_TC7 DMA1 Channel7 transfer complete flag.
 *     @arg DMA1_FLAG_HT7 DMA1 Channel7 half transfer flag.
 *     @arg DMA1_FLAG_TE7 DMA1 Channel7 transfer error flag.
 *     @arg DMA1_FLAG_GL8 DMA1 Channel8 global flag.
 *     @arg DMA1_FLAG_TC8 DMA1 Channel8 transfer complete flag.
 *     @arg DMA1_FLAG_HT8 DMA1 Channel8 half transfer flag.
 *     @arg DMA1_FLAG_TE8 DMA1 Channel8 transfer error flag.
 *     @arg DMA2_FLAG_GL1 DMA2 Channel1 global flag.
 *     @arg DMA2_FLAG_TC1 DMA2 Channel1 transfer complete flag.
 *     @arg DMA2_FLAG_HT1 DMA2 Channel1 half transfer flag.
 *     @arg DMA2_FLAG_TE1 DMA2 Channel1 transfer error flag.
 *     @arg DMA2_FLAG_GL2 DMA2 Channel2 global flag.
 *     @arg DMA2_FLAG_TC2 DMA2 Channel2 transfer complete flag.
 *     @arg DMA2_FLAG_HT2 DMA2 Channel2 half transfer flag.
 *     @arg DMA2_FLAG_TE2 DMA2 Channel2 transfer error flag.
 *     @arg DMA2_FLAG_GL3 DMA2 Channel3 global flag.
 *     @arg DMA2_FLAG_TC3 DMA2 Channel3 transfer complete flag.
 *     @arg DMA2_FLAG_HT3 DMA2 Channel3 half transfer flag.
 *     @arg DMA2_FLAG_TE3 DMA2 Channel3 transfer error flag.
 *     @arg DMA2_FLAG_GL4 DMA2 Channel4 global flag.
 *     @arg DMA2_FLAG_TC4 DMA2 Channel4 transfer complete flag.
 *     @arg DMA2_FLAG_HT4 DMA2 Channel4 half transfer flag.
 *     @arg DMA2_FLAG_TE4 DMA2 Channel4 transfer error flag.
 *     @arg DMA2_FLAG_GL5 DMA2 Channel5 global flag.
 *     @arg DMA2_FLAG_TC5 DMA2 Channel5 transfer complete flag.
 *     @arg DMA2_FLAG_HT5 DMA2 Channel5 half transfer flag.
 *     @arg DMA2_FLAG_TE5 DMA2 Channel5 transfer error flag.
 *     @arg DMA2_FLAG_GL6 DMA2 Channel6 global flag.
 *     @arg DMA2_FLAG_TC6 DMA2 Channel6 transfer complete flag.
 *     @arg DMA2_FLAG_HT6 DMA2 Channel6 half transfer flag.
 *     @arg DMA2_FLAG_TE6 DMA2 Channel6 transfer error flag.
 *     @arg DMA2_FLAG_GL7 DMA2 Channel7 global flag.
 *     @arg DMA2_FLAG_TC7 DMA2 Channel7 transfer complete flag.
 *     @arg DMA2_FLAG_HT7 DMA2 Channel7 half transfer flag.
 *     @arg DMA2_FLAG_TE7 DMA2 Channel7 transfer error flag.
 *     @arg DMA2_FLAG_GL8 DMA2 Channel8 global flag.
 *     @arg DMA2_FLAG_TC8 DMA2 Channel8 transfer complete flag.
 *     @arg DMA2_FLAG_HT8 DMA2 Channel8 half transfer flag.
 *     @arg DMA2_FLAG_TE8 DMA2 Channel8 transfer error flag.
 * @param DMAy DMA1 or DMA2.
 *   This parameter can be one of the following values:
 *     @arg DMA1 .
 *     @arg DMA2 .
 */
void DMA_ClearFlag(uint32_t DMAyFlag, DMA_Module* DMAy)
{
    /* Check the parameters */
    assert_param(IS_DMA_CLEAR_FLAG(DMAyFlag));

    /* Calculate the used DMAy */
    /* Clear the selected DMAy flags */
    DMAy->INTCLR = DMAyFlag;
}

/**
 * @brief  Checks whether the specified DMAy Channelx interrupt has occurred or not.
 * @param DMAy_IT specifies the DMAy interrupt source to check.
 *   This parameter can be one of the following values:
 *     @arg DMA1_INT_GLB1 DMA1 Channel1 global interrupt.
 *     @arg DMA1_INT_TXC1 DMA1 Channel1 transfer complete interrupt.
 *     @arg DMA1_INT_HTX1 DMA1 Channel1 half transfer interrupt.
 *     @arg DMA1_INT_ERR1 DMA1 Channel1 transfer error interrupt.
 *     @arg DMA1_INT_GLB2 DMA1 Channel2 global interrupt.
 *     @arg DMA1_INT_TXC2 DMA1 Channel2 transfer complete interrupt.
 *     @arg DMA1_INT_HTX2 DMA1 Channel2 half transfer interrupt.
 *     @arg DMA1_INT_ERR2 DMA1 Channel2 transfer error interrupt.
 *     @arg DMA1_INT_GLB3 DMA1 Channel3 global interrupt.
 *     @arg DMA1_INT_TXC3 DMA1 Channel3 transfer complete interrupt.
 *     @arg DMA1_INT_HTX3 DMA1 Channel3 half transfer interrupt.
 *     @arg DMA1_INT_ERR3 DMA1 Channel3 transfer error interrupt.
 *     @arg DMA1_INT_GLB4 DMA1 Channel4 global interrupt.
 *     @arg DMA1_INT_TXC4 DMA1 Channel4 transfer complete interrupt.
 *     @arg DMA1_INT_HTX4 DMA1 Channel4 half transfer interrupt.
 *     @arg DMA1_INT_ERR4 DMA1 Channel4 transfer error interrupt.
 *     @arg DMA1_INT_GLB5 DMA1 Channel5 global interrupt.
 *     @arg DMA1_INT_TXC5 DMA1 Channel5 transfer complete interrupt.
 *     @arg DMA1_INT_HTX5 DMA1 Channel5 half transfer interrupt.
 *     @arg DMA1_INT_ERR5 DMA1 Channel5 transfer error interrupt.
 *     @arg DMA1_INT_GLB6 DMA1 Channel6 global interrupt.
 *     @arg DMA1_INT_TXC6 DMA1 Channel6 transfer complete interrupt.
 *     @arg DMA1_INT_HTX6 DMA1 Channel6 half transfer interrupt.
 *     @arg DMA1_INT_ERR6 DMA1 Channel6 transfer error interrupt.
 *     @arg DMA1_INT_GLB7 DMA1 Channel7 global interrupt.
 *     @arg DMA1_INT_TXC7 DMA1 Channel7 transfer complete interrupt.
 *     @arg DMA1_INT_HTX7 DMA1 Channel7 half transfer interrupt.
 *     @arg DMA1_INT_ERR7 DMA1 Channel7 transfer error interrupt.
 *     @arg DMA1_INT_GLB8 DMA1 Channel8 global interrupt.
 *     @arg DMA1_INT_TXC8 DMA1 Channel8 transfer complete interrupt.
 *     @arg DMA1_INT_HTX8 DMA1 Channel8 half transfer interrupt.
 *     @arg DMA1_INT_ERR8 DMA1 Channel8 transfer error interrupt.
 *     @arg DMA2_INT_GLB1 DMA2 Channel1 global interrupt.
 *     @arg DMA2_INT_TXC1 DMA2 Channel1 transfer complete interrupt.
 *     @arg DMA2_INT_HTX1 DMA2 Channel1 half transfer interrupt.
 *     @arg DMA2_INT_ERR1 DMA2 Channel1 transfer error interrupt.
 *     @arg DMA2_INT_GLB2 DMA2 Channel2 global interrupt.
 *     @arg DMA2_INT_TXC2 DMA2 Channel2 transfer complete interrupt.
 *     @arg DMA2_INT_HTX2 DMA2 Channel2 half transfer interrupt.
 *     @arg DMA2_INT_ERR2 DMA2 Channel2 transfer error interrupt.
 *     @arg DMA2_INT_GLB3 DMA2 Channel3 global interrupt.
 *     @arg DMA2_INT_TXC3 DMA2 Channel3 transfer complete interrupt.
 *     @arg DMA2_INT_HTX3 DMA2 Channel3 half transfer interrupt.
 *     @arg DMA2_INT_ERR3 DMA2 Channel3 transfer error interrupt.
 *     @arg DMA2_INT_GLB4 DMA2 Channel4 global interrupt.
 *     @arg DMA2_INT_TXC4 DMA2 Channel4 transfer complete interrupt.
 *     @arg DMA2_INT_HTX4 DMA2 Channel4 half transfer interrupt.
 *     @arg DMA2_INT_ERR4 DMA2 Channel4 transfer error interrupt.
 *     @arg DMA2_INT_GLB5 DMA2 Channel5 global interrupt.
 *     @arg DMA2_INT_TXC5 DMA2 Channel5 transfer complete interrupt.
 *     @arg DMA2_INT_HTX5 DMA2 Channel5 half transfer interrupt.
 *     @arg DMA2_INT_ERR5 DMA2 Channel5 transfer error interrupt.
 *     @arg DMA2_INT_GLB6 DMA2 Channel6 global interrupt.
 *     @arg DMA2_INT_TXC6 DMA2 Channel6 transfer complete interrupt.
 *     @arg DMA2_INT_HTX6 DMA2 Channel6 half transfer interrupt.
 *     @arg DMA2_INT_ERR6 DMA2 Channel6 transfer error interrupt.
 *     @arg DMA2_INT_GLB7 DMA2 Channel7 global interrupt.
 *     @arg DMA2_INT_TXC7 DMA2 Channel7 transfer complete interrupt.
 *     @arg DMA2_INT_HTX7 DMA2 Channel7 half transfer interrupt.
 *     @arg DMA2_INT_ERR7 DMA2 Channel7 transfer error interrupt.
 *     @arg DMA2_INT_GLB8 DMA2 Channel8 global interrupt.
 *     @arg DMA2_INT_TXC8 DMA2 Channel8 transfer complete interrupt.
 *     @arg DMA2_INT_HTX8 DMA2 Channel8 half transfer interrupt.
 *     @arg DMA2_INT_ERR8 DMA2 Channel8 transfer error interrupt.
 * @param DMAy DMA1 or DMA2.
 *   This parameter can be one of the following values:
 *     @arg DMA1 .
 *     @arg DMA2 .
 * @return The new state of DMAy_IT (SET or RESET).
 */
INTStatus DMA_GetIntStatus(uint32_t DMAy_IT, DMA_Module* DMAy)
{
    INTStatus bitstatus  = RESET;
    uint32_t tmpregister = 0;

    /* Check the parameters */
    assert_param(IS_DMA_GET_IT(DMAy_IT));

    /* Calculate the used DMA */
    /* Get DMAy INTSTS register value */
    tmpregister = DMAy->INTSTS;

    /* Check the status of the specified DMAy interrupt */
    if ((tmpregister & DMAy_IT) != (uint32_t)RESET)
    {
        /* DMAy_IT is set */
        bitstatus = SET;
    }
    else
    {
        /* DMAy_IT is reset */
        bitstatus = RESET;
    }
    /* Return the DMAInt status */
    return bitstatus;
}

/**
 * @brief  Clears the DMAy Channelx's interrupt pending bits.
 * @param DMAy_IT specifies the DMAy interrupt pending bit to clear.
 *   This parameter can be any combination (for the same DMA) of the following values:
 *     @arg DMA1_INT_GLB1 DMA1 Channel1 global interrupt.
 *     @arg DMA1_INT_TXC1 DMA1 Channel1 transfer complete interrupt.
 *     @arg DMA1_INT_HTX1 DMA1 Channel1 half transfer interrupt.
 *     @arg DMA1_INT_ERR1 DMA1 Channel1 transfer error interrupt.
 *     @arg DMA1_INT_GLB2 DMA1 Channel2 global interrupt.
 *     @arg DMA1_INT_TXC2 DMA1 Channel2 transfer complete interrupt.
 *     @arg DMA1_INT_HTX2 DMA1 Channel2 half transfer interrupt.
 *     @arg DMA1_INT_ERR2 DMA1 Channel2 transfer error interrupt.
 *     @arg DMA1_INT_GLB3 DMA1 Channel3 global interrupt.
 *     @arg DMA1_INT_TXC3 DMA1 Channel3 transfer complete interrupt.
 *     @arg DMA1_INT_HTX3 DMA1 Channel3 half transfer interrupt.
 *     @arg DMA1_INT_ERR3 DMA1 Channel3 transfer error interrupt.
 *     @arg DMA1_INT_GLB4 DMA1 Channel4 global interrupt.
 *     @arg DMA1_INT_TXC4 DMA1 Channel4 transfer complete interrupt.
 *     @arg DMA1_INT_HTX4 DMA1 Channel4 half transfer interrupt.
 *     @arg DMA1_INT_ERR4 DMA1 Channel4 transfer error interrupt.
 *     @arg DMA1_INT_GLB5 DMA1 Channel5 global interrupt.
 *     @arg DMA1_INT_TXC5 DMA1 Channel5 transfer complete interrupt.
 *     @arg DMA1_INT_HTX5 DMA1 Channel5 half transfer interrupt.
 *     @arg DMA1_INT_ERR5 DMA1 Channel5 transfer error interrupt.
 *     @arg DMA1_INT_GLB6 DMA1 Channel6 global interrupt.
 *     @arg DMA1_INT_TXC6 DMA1 Channel6 transfer complete interrupt.
 *     @arg DMA1_INT_HTX6 DMA1 Channel6 half transfer interrupt.
 *     @arg DMA1_INT_ERR6 DMA1 Channel6 transfer error interrupt.
 *     @arg DMA1_INT_GLB7 DMA1 Channel7 global interrupt.
 *     @arg DMA1_INT_TXC7 DMA1 Channel7 transfer complete interrupt.
 *     @arg DMA1_INT_HTX7 DMA1 Channel7 half transfer interrupt.
 *     @arg DMA1_INT_ERR7 DMA1 Channel7 transfer error interrupt.
 *     @arg DMA1_INT_GLB8 DMA1 Channel8 global interrupt.
 *     @arg DMA1_INT_TXC8 DMA1 Channel8 transfer complete interrupt.
 *     @arg DMA1_INT_HTX8 DMA1 Channel8 half transfer interrupt.
 *     @arg DMA1_INT_ERR8 DMA1 Channel8 transfer error interrupt.
 *     @arg DMA2_INT_GLB1 DMA2 Channel1 global interrupt.
 *     @arg DMA2_INT_TXC1 DMA2 Channel1 transfer complete interrupt.
 *     @arg DMA2_INT_HTX1 DMA2 Channel1 half transfer interrupt.
 *     @arg DMA2_INT_ERR1 DMA2 Channel1 transfer error interrupt.
 *     @arg DMA2_INT_GLB2 DMA2 Channel2 global interrupt.
 *     @arg DMA2_INT_TXC2 DMA2 Channel2 transfer complete interrupt.
 *     @arg DMA2_INT_HTX2 DMA2 Channel2 half transfer interrupt.
 *     @arg DMA2_INT_ERR2 DMA2 Channel2 transfer error interrupt.
 *     @arg DMA2_INT_GLB3 DMA2 Channel3 global interrupt.
 *     @arg DMA2_INT_TXC3 DMA2 Channel3 transfer complete interrupt.
 *     @arg DMA2_INT_HTX3 DMA2 Channel3 half transfer interrupt.
 *     @arg DMA2_INT_ERR3 DMA2 Channel3 transfer error interrupt.
 *     @arg DMA2_INT_GLB4 DMA2 Channel4 global interrupt.
 *     @arg DMA2_INT_TXC4 DMA2 Channel4 transfer complete interrupt.
 *     @arg DMA2_INT_HTX4 DMA2 Channel4 half transfer interrupt.
 *     @arg DMA2_INT_ERR4 DMA2 Channel4 transfer error interrupt.
 *     @arg DMA2_INT_GLB5 DMA2 Channel5 global interrupt.
 *     @arg DMA2_INT_TXC5 DMA2 Channel5 transfer complete interrupt.
 *     @arg DMA2_INT_HTX5 DMA2 Channel5 half transfer interrupt.
 *     @arg DMA2_INT_ERR5 DMA2 Channel5 transfer error interrupt.
 *     @arg DMA2_INT_GLB6 DMA2 Channel6 global interrupt.
 *     @arg DMA2_INT_TXC6 DMA2 Channel6 transfer complete interrupt.
 *     @arg DMA2_INT_HTX6 DMA2 Channel6 half transfer interrupt.
 *     @arg DMA2_INT_ERR6 DMA2 Channel6 transfer error interrupt.
 *     @arg DMA2_INT_GLB7 DMA2 Channel7 global interrupt.
 *     @arg DMA2_INT_TXC7 DMA2 Channel7 transfer complete interrupt.
 *     @arg DMA2_INT_HTX7 DMA2 Channel7 half transfer interrupt.
 *     @arg DMA2_INT_ERR7 DMA2 Channel7 transfer error interrupt.
 *     @arg DMA2_INT_GLB8 DMA2 Channel8 global interrupt.
 *     @arg DMA2_INT_TXC8 DMA2 Channel8 transfer complete interrupt.
 *     @arg DMA2_INT_HTX8 DMA2 Channel8 half transfer interrupt.
 *     @arg DMA2_INT_ERR8 DMA2 Channel8 transfer error interrupt.
 * @param DMAy DMA1 or DMA2.
 *   This parameter can be one of the following values:
 *     @arg DMA1 .
 *     @arg DMA2 .
 */
void DMA_ClrIntPendingBit(uint32_t DMAy_IT, DMA_Module* DMAy)
{
    /* Check the parameters */
    assert_param(IS_DMA_CLR_INT(DMAy_IT));

    /* Calculate the used DMAy */
    /* Clear the selected DMAy interrupt pending bits */
    DMAy->INTCLR = DMAy_IT;
}

/**
 * @brief  Set the DMAy Channelx's remap request.
 * @param DMAy_REMAP specifies the DMAy request.
 *   This parameter can be set by the following values:
 *     @arg DMA1_REMAP_ADC1 DMA1 Request For ADC1.
 *     @arg DMA1_REMAP_UART5_TX DMA1 Request For UART5_TX.
 *     @arg DMA1_REMAP_I2C3_TX DMA1 Request For I2C3_TX.
 *     @arg DMA1_REMAP_TIM2_CH3 DMA1 Request For TIM2_CH3.
 *     @arg DMA1_REMAP_TIM4_CH1 DMA1 Request For TIM4_CH1.
 *     @arg DMA1_REMAP_USART3_TX DMA1 Request For USART3_TX.
 *     @arg DMA1_REMAP_I2C3_RX DMA1 Request For I2C3_RX.
 *     @arg DMA1_REMAP_TIM1_CH1 DMA1 Request For TIM1_CH1.
 *     @arg DMA1_REMAP_TIM2_UP DMA1 Request For TIM2_UP.
 *     @arg DMA1_REMAP_TIM3_CH3 DMA1 Request For TIM3_CH3.
 *     @arg DMA1_REMAP_SPI1_RX DMA1 Request For SPI1_RX.
 *     @arg DMA1_REMAP_USART3_RX DMA1 Request For USART3_RX.
 *     @arg DMA1_REMAP_TIM1_CH2 DMA1 Request For TIM1_CH2.
 *     @arg DMA1_REMAP_TIM3_CH4 DMA1 Request For TIM3_CH4.
 *     @arg DMA1_REMAP_TIM3_UP DMA1 Request For TIM3_UP.
 *     @arg DMA1_REMAP_SPI1_TX DMA1 Request For SPI1_TX.
 *     @arg DMA1_REMAP_USART1_TX DMA1 Request For USART1_TX.
 *     @arg DMA1_REMAP_TIM1_CH4 DMA1 Request For TIM1_CH4.
 *     @arg DMA1_REMAP_TIM1_TRIG DMA1 Request For TIM1_TRIG.
 *     @arg DMA1_REMAP_TIM1_COM DMA1 Request For TIM1_COM.
 *     @arg DMA1_REMAP_TIM4_CH2 DMA1 Request For TIM4_CH2.
 *     @arg DMA1_REMAP_SPI_I2S2_RX DMA1 Request For SPI_I2S2_RX.
 *     @arg DMA1_REMAP_I2C2_TX DMA1 Request For I2C2_TX.
 *     @arg DMA1_REMAP_USART1_RX DMA1 Request For USART1_RX.
 *     @arg DMA1_REMAP_TIM1_UP DMA1 Request For TIM1_UP.
 *     @arg DMA1_REMAP_SPI_I2S2_TX DMA1 Request For SPI_I2S2_TX.
 *     @arg DMA1_REMAP_TIM4_CH3 DMA1 Request For TIM4_CH3.
 *     @arg DMA1_REMAP_I2C2_RX DMA1 Request For I2C2_RX.
 *     @arg DMA1_REMAP_TIM2_CH1 DMA1 Request For TIM2_CH1.
 *     @arg DMA1_REMAP_USART2_RX DMA1 Request For USART2_RX.
 *     @arg DMA1_REMAP_TIM1_CH3 DMA1 Request For TIM1_CH3.
 *     @arg DMA1_REMAP_TIM3_CH1 DMA1 Request For TIM3_CH1.
 *     @arg DMA1_REMAP_TIM3_TRIG DMA1 Request For TIM3_TRIG.
 *     @arg DMA1_REMAP_I2C1_TX DMA1 Request For I2C1_TX.
 *     @arg DMA1_REMAP_USART2_TX DMA1 Request For USART2_TX.
 *     @arg DMA1_REMAP_TIM2_CH2 DMA1 Request For TIM2_CH2.
 *     @arg DMA1_REMAP_TIM2_CH4 DMA1 Request For TIM2_CH4.
 *     @arg DMA1_REMAP_TIM4_UP DMA1 Request For TIM4_UP.
 *     @arg DMA1_REMAP_I2C1_RX DMA1 Request For I2C1_RX.
 *     @arg DMA1_REMAP_ADC2 DMA1 Request For ADC2.
 *     @arg DMA1_REMAP_UART5_RX DMA1 Request For UART5_RX.
 *     @arg DMA2_REMAP_TIM5_CH4 DMA2 Request For TIM5_CH4.
 *     @arg DMA2_REMAP_TIM5_TRIG DMA2 Request For TIM5_TRIG.
 *     @arg DMA2_REMAP_TIM8_CH3 DMA2 Request For TIM8_CH3.
 *     @arg DMA2_REMAP_TIM8_UP DMA2 Request For TIM8_UP.
 *     @arg DMA2_REMAP_SPI_I2S3_RX DMA2 Request For SPI_I2S3_RX.
 *     @arg DMA2_REMAP_UART6_RX DMA2 Request For UART6_RX.
 *     @arg DMA2_REMAP_TIM8_CH4 DMA2 Request For TIM8_CH4.
 *     @arg DMA2_REMAP_TIM8_TRIG DMA2 Request For TIM8_TRIG.
 *     @arg DMA2_REMAP_TIM8_COM DMA2 Request For TIM8_COM.
 *     @arg DMA2_REMAP_TIM5_CH3 DMA2 Request For TIM5_CH3.
 *     @arg DMA2_REMAP_TIM5_UP DMA2 Request For TIM5_UP.
 *     @arg DMA2_REMAP_SPI_I2S3_TX DMA2 Request For SPI_I2S3_TX.
 *     @arg DMA2_REMAP_UART6_TX DMA2 Request For UART6_TX.
 *     @arg DMA2_REMAP_TIM8_CH1 DMA2 Request For TIM8_CH1.
 *     @arg DMA2_REMAP_UART4_RX DMA2 Request For UART4_RX.
 *     @arg DMA2_REMAP_TIM6_UP DMA2 Request For TIM6_UP.
 *     @arg DMA2_REMAP_DAC1 DMA2 Request For DAC1.
 *     @arg DMA2_REMAP_TIM5_CH2 DMA2 Request For TIM5_CH2.
 *     @arg DMA2_REMAP_SDIO DMA2 Request For SDIO.
 *     @arg DMA2_REMAP_TIM7_UP DMA2 Request For TIM7_UP.
 *     @arg DMA2_REMAP_DAC2 DMA2 Request For DAC2.
 *     @arg DMA2_REMAP_TIM8_CH2 DMA2 Request For TIM8_CH2.
 *     @arg DMA2_REMAP_TIM5_CH1 DMA2 Request For TIM5_CH1.
 *     @arg DMA2_REMAP_UART4_TX DMA2 Request For UART4_TX.
 *     @arg DMA2_REMAP_I2C4_TX DMA2 Request For I2C4_TX.
 *     @arg DMA2_REMAP_UART7_RX DMA2 Request For UART7_RX.
 *     @arg DMA2_REMAP_I2C4_RX DMA2 Request For I2C4_RX.
 *     @arg DMA2_REMAP_UART7_TX DMA2 Request For UART7_TX.
 *     @arg DMA2_REMAP_DVP DMA2 Request For DVP.
 * @param DMAy DMA1 or DMA2.
 *   This parameter can be one of the following values:
 *     @arg DMA1 .
 *     @arg DMA2 .
 * @param DMAyChx where y can be 1 or 2 to select the DMA and
 *   x can be 1 to 8 for DMA1 and 1 to 8 for DMA2 to select the DMA Channel.
 * @param Cmd new state of the DMAy Channelx.
 *   This parameter can be: ENABLE or DISABLE.
 */
void DMA_RequestRemap(uint32_t DMAy_REMAP, DMA_Module* DMAy, DMA_ChannelType* DMAyChx, FunctionalState Cmd)
{
    /* Check the parameters */
    assert_param(IS_DMA_REMAP(DMAy_REMAP));

    if (Cmd != DISABLE)
    {
        /* Calculate the used DMAy */
        /* Set the selected DMAy remap request */
        DMAyChx->CHSEL = DMAy_REMAP;
        DMAy->CHMAPEN  = 1;
    }
    else
    {
        DMAy->CHMAPEN = 0;
    }
}

/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
