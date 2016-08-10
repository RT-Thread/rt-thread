/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <string.h>
#include "fsl_dma_driver.h"
#include "fsl_interrupt_manager.h"
#include "fsl_clock_manager.h"
#if FSL_FEATURE_SOC_DMA_COUNT

/*******************************************************************************
 * Variables
 ******************************************************************************/
/*! @brief Global DMA  management data structure. */
dma_state_t *g_dma;

/*! @brief Macro for EDMA driver lock mechanism. */
#if (USE_RTOS)
    #define DMA_DRV_LOCK()         OSA_MutexLock(&g_dma->lock, OSA_WAIT_FOREVER)
    #define DMA_DRV_UNLOCK()       OSA_MutexUnlock(&g_dma->lock)
#else
    #define DMA_DRV_LOCK()         do {}while(0)
    #define DMA_DRV_UNLOCK()       do {}while(0)
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_Init
 * Description   : Initialize DMA.
 *
 *END**************************************************************************/
dma_status_t DMA_DRV_Init(dma_state_t *state)
{
    uint8_t i;
    g_dma = state;
    memset(g_dma, 0, sizeof(dma_state_t));
#if (USE_RTOS)
    OSA_MutexCreate(&state->lock);
#endif
    /* Enable DMA clock. */
    for (i = 0; i < DMA_INSTANCE_COUNT; i ++)
    {
        CLOCK_SYS_EnableDmaClock(i);
    }

    /* Enable DMAMUX clock and init. */
    for (i = 0; i < DMAMUX_INSTANCE_COUNT; i++)
    {
        CLOCK_SYS_EnableDmamuxClock(i);
        DMAMUX_HAL_Init(g_dmamuxBase[i]);
    }

    return kStatus_DMA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_Deinit
 * Description   : Deinitilize DMA
 *
 *END**************************************************************************/
dma_status_t DMA_DRV_Deinit(void)
{
    uint8_t i;

    /* Disable DMA clock and free channel. */
    for (i = 0; i < FSL_FEATURE_DMA_DMAMUX_CHANNELS; i++)
    {
        /* Free all requested channels. */
        if (g_dma->dmaChan[i])
        {
            DMA_DRV_FreeChannel(g_dma->dmaChan[i]);
        }
    }

    /* Disable DMA clcok. */
    for (i = 0; i < DMA_INSTANCE_COUNT; i++)
    {
        CLOCK_SYS_DisableDmaClock(i);
    }

    /* Disable DMAMUX clock. */
    for (i = 0; i < DMAMUX_INSTANCE_COUNT; i++)
    {
        CLOCK_SYS_DisableDmaClock(i);
    }
#if USE_RTOS
    OSA_MutexDestroy(&g_dma->lock);
#endif

    return kStatus_DMA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_RegisterCallback
 * Description   : Register callback function and parameter.
 *
 *END**************************************************************************/
dma_status_t DMA_DRV_RegisterCallback(
        dma_channel_t *chn, dma_callback_t callback, void *para)
{
    chn->callback = callback;
    chn->parameter = para;

    return kStatus_DMA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_RequestChannel
 * Description   : Request a DMA  channel.
 *
 *END**************************************************************************/
uint32_t DMA_DRV_RequestChannel(
        uint32_t channel, dma_request_source_t source, dma_channel_t *chn)
{
    uint8_t i = 0, j;

    /*Check if dynamically allocation is requested */
    if (channel == kDmaAnyChannel)
    {
        uint32_t map = ((uint32_t)source >> 8U);
        while (map != 0)
        {
            if (map & (1U << i))
            {
                for (j = i * FSL_FEATURE_DMAMUX_MODULE_CHANNEL; j < (i + 1) * FSL_FEATURE_DMAMUX_MODULE_CHANNEL; j++)
                {
                    DMA_DRV_LOCK();
                    if (!g_dma->dmaChan[j])
                    {
                        g_dma->dmaChan[j] = chn;
                        DMA_DRV_UNLOCK();
                        DMA_DRV_ClaimChannel(j, source, chn);
                        return j;
                    }
                    DMA_DRV_UNLOCK();
                }

            }
            map &= ~(0x1U << i);
            i++;
        }

        return kDmaInvalidChannel;
    }

    /*static allocation */
    DMA_DRV_LOCK();
    if (!g_dma->dmaChan[channel])
    {
        DMA_DRV_UNLOCK();
        DMA_DRV_ClaimChannel(channel, source, chn);
        return channel;
    }
    DMA_DRV_UNLOCK();

    return kDmaInvalidChannel;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_ClaimChannel
 * Description   : claim DMA  channel.
 *
 *END**************************************************************************/
dma_status_t DMA_DRV_ClaimChannel(
        uint32_t channel, dma_request_source_t source, dma_channel_t *chn)
{
    IRQn_Type irqNumber;
    uint32_t dmaInstance = channel/FSL_FEATURE_DMA_DMAMUX_CHANNELS;
    DMAMUX_Type * dmamuxBaseAddr = g_dmamuxBase[channel/FSL_FEATURE_DMAMUX_MODULE_CHANNEL];
    memset(chn, 0, sizeof(dma_channel_t));

    DMA_DRV_LOCK();
    g_dma->dmaChan[channel] = chn;
    DMA_DRV_UNLOCK();

    chn->channel = channel % FSL_FEATURE_DMA_DMAMUX_CHANNELS;
    chn->dmamuxChannel = channel % FSL_FEATURE_DMAMUX_MODULE_CHANNEL;
    chn->dmamuxModule = channel / FSL_FEATURE_DMAMUX_MODULE_CHANNEL;

    chn->parameter = 0;
    chn->callback = NULL;

    chn->status = kDmaNormal;

    /*Enable the interrupt */
    irqNumber = g_dmaIrqId[dmaInstance][chn->channel];
    INT_SYS_EnableIRQ(irqNumber);

    /*Configure the DMAMUX for EDMA channel */
    DMAMUX_HAL_SetChannelCmd(dmamuxBaseAddr, chn->dmamuxChannel, false);
    DMAMUX_HAL_SetTriggerSource(
       dmamuxBaseAddr, chn->dmamuxChannel, (uint32_t)source % (uint32_t)kDmamuxDmaRequestSource);
    DMAMUX_HAL_SetChannelCmd(dmamuxBaseAddr, chn->dmamuxChannel,true);

    return kStatus_DMA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_FreeChannel
 * Description   : Free DMA  channel's hardware and software resource.
 *
 *END**************************************************************************/
dma_status_t DMA_DRV_FreeChannel(dma_channel_t *chn)
{
    /* Stop channel firstly. */
    DMA_DRV_StopChannel(chn);

    DMA_DRV_LOCK();
    /* Unregister channel from global structure. */
    g_dma->dmaChan[chn->channel] = NULL;
    DMA_DRV_UNLOCK();
    memset(chn, 0x1, sizeof(dma_channel_t));

    return kStatus_DMA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_StartChannel
 * Description   : Start a DMA  channel.
 *
 *END**************************************************************************/
dma_status_t DMA_DRV_StartChannel(dma_channel_t *chn)
{
    DMA_Type * dmaBaseAddr = g_dmaBase[chn->channel/FSL_FEATURE_DMA_DMAMUX_CHANNELS];
    DMA_HAL_SetDmaRequestCmd(dmaBaseAddr, chn->channel, true);
    return kStatus_DMA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_StopChannel
 * Description   : Stop a DMA   channel.
 *
 *END**************************************************************************/
dma_status_t DMA_DRV_StopChannel(dma_channel_t *chn)
{
    DMA_Type * dmaBaseAddr = g_dmaBase[chn->channel/FSL_FEATURE_DMA_DMAMUX_CHANNELS];
    DMA_HAL_SetDmaRequestCmd(dmaBaseAddr, chn->channel, false);
    return kStatus_DMA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_GetDescriptorStatus
 * Description   : Get the left bytes to be transferred.
 *
 *END**************************************************************************/
uint32_t DMA_DRV_GetUnfinishedBytes(dma_channel_t *chn)
{
    DMA_Type * dmaBaseAddr = g_dmaBase[chn->channel/FSL_FEATURE_DMA_DMAMUX_CHANNELS];
    return DMA_HAL_GetUnfinishedByte(dmaBaseAddr, chn->channel);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_IRQhandler
 * Description   : IRQ handler for DMA  channel.
 *
 *END**************************************************************************/
void DMA_DRV_IRQhandler(uint32_t channel)
{
    dma_channel_t *chn = g_dma->dmaChan[channel];
    DMA_Type * dmaBaseAddr = g_dmaBase[channel/FSL_FEATURE_DMA_DMAMUX_CHANNELS];
    dma_error_status_t status;

    if (!chn)
    {
        return;
    }

    status = DMA_HAL_GetStatus(dmaBaseAddr, channel);

    if ((status.dmaConfigError) || (status.dmaDestBusError) || (status.dmaSourceBusError))
    {
        chn->status = kDmaError;
        status = DMA_HAL_GetStatus(dmaBaseAddr, channel);
    }

    DMA_HAL_ClearStatus(dmaBaseAddr, channel);


    if (chn->callback)
    {
        chn->callback(chn->parameter, chn->status);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_ConfigTransfer
 * Description   : Configure transfer for DMA.
 *
 *END**************************************************************************/
dma_status_t DMA_DRV_ConfigTransfer(
        dma_channel_t *chn, dma_transfer_type_t type, uint32_t size, uint32_t
        sourceAddr, uint32_t destAddr, uint32_t length)
{
    DMA_Type * dmaBaseAddr = g_dmaBase[chn->channel/FSL_FEATURE_DMA_DMAMUX_CHANNELS];
    dma_transfer_size_t transfersize;
    switch (size)
    {
        case 1:
            transfersize = kDmaTransfersize8bits;
            break;
        case 2:
            transfersize = kDmaTransfersize16bits;
            break;
        case 4:
            transfersize = kDmaTransfersize32bits;
            break;
        default:
            return kStatus_DMA_InvalidArgument;
    }

    /* Clear the DMA status. */
    DMA_HAL_ClearStatus(dmaBaseAddr, chn->channel);

    DMA_HAL_ConfigTransfer(dmaBaseAddr, chn->channel, transfersize,
        type, sourceAddr, destAddr, length);

    return kStatus_DMA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_ConfigChanLink
 * Description   : Configure channel link for dma.
 *
 *END**************************************************************************/
dma_status_t DMA_DRV_ConfigChanLink(
    dma_channel_t * chn,dma_channel_link_config_t * link_config)
{
    uint32_t channel = chn->channel;
    DMA_Type * base = g_dmaBase[channel/FSL_FEATURE_DMA_DMAMUX_CHANNELS];
    DMA_HAL_SetChanLink(base, channel,link_config);
    return kStatus_DMA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_SetDestTransferSize
 * Description   : Update DMA destination transfer size
 *
 *END**************************************************************************/
dma_status_t DMA_DRV_SetDestTransferSize(dma_channel_t *chn, uint32_t transferSize)
{
    dma_transfer_size_t size;
    uint32_t channel = chn->channel;
    DMA_Type * base = g_dmaBase[channel/FSL_FEATURE_DMA_DMAMUX_CHANNELS];

    switch (transferSize)
    {
        case 1:
            size = kDmaTransfersize8bits;
            break;
        case 2:
            size = kDmaTransfersize16bits;
            break;
        case 4:
            size = kDmaTransfersize32bits;
            break;
        default:
            return kStatus_DMA_InvalidArgument;
    }

    DMA_HAL_SetDestTransferSize(base, channel, size);
    return kStatus_DMA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_DRV_SetSourceTransferSize
 * Description   : Update DMA source transfer size
 *
 *END**************************************************************************/
dma_status_t DMA_DRV_SetSourceTransferSize(dma_channel_t *chn, uint32_t transferSize)
{
    dma_transfer_size_t size;
    uint32_t channel = chn->channel;
    DMA_Type * base = g_dmaBase[channel/FSL_FEATURE_DMA_DMAMUX_CHANNELS];

    switch (transferSize)
    {
        case 1:
            size = kDmaTransfersize8bits;
            break;
        case 2:
            size = kDmaTransfersize16bits;
            break;
        case 4:
            size = kDmaTransfersize32bits;
            break;
        default:
            return kStatus_DMA_InvalidArgument;
    }

    DMA_HAL_SetSourceTransferSize(base, channel, size);
    return kStatus_DMA_Success;
}

#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/
