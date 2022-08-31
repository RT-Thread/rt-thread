/*
 * Copyright 2021 MindMotion Microelectronics Co., Ltd.
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "hal_dma.h"

/* clear all the interrupt enables and disable the dma channel. */
uint32_t DMA_InitChannel(DMA_Type * DMAx, uint32_t channel, DMA_Channel_Init_Type * init)
{
    uint32_t ccr = 0u;

    if (   (init->XferMode == DMA_XferMode_MemoryToPeriph)
        || (init->XferMode == DMA_XferMode_MemoryToPeriphBurst) )
    {
        ccr |= DMA_CCR_DIR_MASK;
    }

    if (   (init->XferMode == DMA_XferMode_PeriphToMemoryBurst)
        || (init->XferMode == DMA_XferMode_MemoryToPeriphBurst) )
    {
        ccr |= DMA_CCR_MEM2MEM_MASK;
    }

    if (init->ReloadMode == DMA_ReloadMode_AutoReload)
    {
        ccr |= DMA_CCR_ARE_MASK;
    }
    else if (init->ReloadMode == DMA_ReloadMode_AutoReloadContinuous)
    {
        ccr |= (DMA_CCR_ARE_MASK | DMA_CCR_CIRC_MASK);
    }

    ccr |= DMA_CCR_PINC(init->PeriphAddrIncMode)
         | DMA_CCR_MINC(init->MemAddrIncMode)
         | DMA_CCR_PSIZE(init->XferWidth)
         | DMA_CCR_MSIZE(init->XferWidth)
         | DMA_CCR_PL(init->Priority)
         ;

    DMAx->CH[channel].CCR = ccr;
    DMAx->CH[channel].CNDTR = init->XferCount;
    DMAx->CH[channel].CPAR = init->PeriphAddr;
    DMAx->CH[channel].CMAR = init->MemAddr;

    return 0u;
}

void DMA_EnableChannelInterrupts(DMA_Type * DMAx, uint32_t channel, uint32_t interrupts, bool enable)
{
    if (enable)
    {
        DMAx->CH[channel].CCR |= (interrupts & 0xEu);
    }
    else
    {
        DMAx->CH[channel].CCR &= ~(interrupts & 0xEu);
    }
}

uint32_t DMA_GetChannelInterruptStatus(DMA_Type * DMAx, uint32_t channel)
{
    return (DMAx->ISR >> (channel * 4u)) & 0xFu;
}

void DMA_ClearChannelInterruptStatus(DMA_Type * DMAx, uint32_t channel, uint32_t interrupts)
{
    DMAx->IFCR = ( (interrupts & 0xFu) << (channel * 4u) );
}

void DMA_EnableChannel(DMA_Type * DMAx, uint32_t channel, bool enable)
{
    if (enable)
    {
        DMAx->CH[channel].CCR |= DMA_CCR_EN_MASK;
    }
    else
    {
        DMAx->CH[channel].CCR &= ~DMA_CCR_EN_MASK;
    }
}

/* EOF. */

