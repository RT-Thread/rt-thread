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

#include <stdlib.h>
#include <string.h>
#include "fsl_edma_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"
#if FSL_FEATURE_SOC_EDMA_COUNT

/*******************************************************************************
 * Variabled
 ******************************************************************************/
/*! @brief EDMA global structure to maintain EDMA resource */
edma_state_t *g_edma = NULL;

/*******************************************************************************
 * PROTOTYPES
 ******************************************************************************/
static edma_status_t EDMA_DRV_ClaimChannel(
                uint8_t channel, dma_request_source_t source, edma_chn_state_t *chn);
static void EDMA_DRV_ClearIntStatus(uint8_t channel);

/*! @brief Macro for EDMA driver lock mechanism. */
#if (USE_RTOS)
    #define EDMA_DRV_LOCK()         OSA_MutexLock(&g_edma->lock, OSA_WAIT_FOREVER)
    #define EDMA_DRV_UNLOCK()       OSA_MutexUnlock(&g_edma->lock)
#else
    #define EDMA_DRV_LOCK()         do {}while(0)
    #define EDMA_DRV_UNLOCK()       do {}while(0)
#endif

/*******************************************************************************
 * Code
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_DRV_Init
 * Description   : Initializes all eDMA modules in SOC.
 *
 *END**************************************************************************/
edma_status_t EDMA_DRV_Init(edma_state_t *edmaState, const edma_user_config_t *userConfig)
{
    uint32_t i, j;
    DMA_Type * edmaRegBase;
    DMAMUX_Type * dmamuxRegBase;
    IRQn_Type irqNumber;

    if (g_edma)
    {
        return kStatus_EDMA_Success;
    }

    g_edma = edmaState;
    memset(g_edma, 0, sizeof(edma_state_t));
#if (USE_RTOS)
    /* Init mutex object for the access control of edma data structure. */
    OSA_MutexCreate(&g_edma->lock);
#endif

    for (i = 0; i < DMA_INSTANCE_COUNT; i++)
    {
        edmaRegBase = g_edmaBase[i];
        /* Enable clock gate of eDMA module. */
        CLOCK_SYS_EnableDmaClock(i);

        /* Init eDMA module in hardware level. */
        EDMA_HAL_Init(edmaRegBase);

        EDMA_HAL_SetChannelArbitrationMode(edmaRegBase, userConfig->chnArbitration);
#if (FSL_FEATURE_EDMA_CHANNEL_GROUP_COUNT > 0x1U)
        EDMA_HAL_SetGroupArbitrationMode(edmaRegBase, userConfig->groupArbitration);
        EDMA_HAL_SetGroupPriority(edmaRegBase, userConfig->groupPriority);
#endif
        EDMA_HAL_SetHaltOnErrorCmd(edmaRegBase, !userConfig->notHaltOnError);

#if !defined FSL_FEATURE_EDMA_HAS_ERROR_IRQ 
        /* Enable the error interrupt for eDMA module. */
        irqNumber = g_edmaErrIrqId[i];
        INT_SYS_EnableIRQ(irqNumber);
#endif

        /* Register all edma channl interrupt handler into vector table. */
        for (j = 0; j < FSL_FEATURE_EDMA_MODULE_CHANNEL; j++)
        {
            /* Enable channel interrupt ID. */
            irqNumber = g_edmaIrqId[i][j];
            INT_SYS_EnableIRQ(irqNumber);
        }
    }

    for (i = 0; i < DMAMUX_INSTANCE_COUNT; i++)
    {
        dmamuxRegBase = g_dmamuxBase[i];
        /* Enable dmamux clock gate */
        CLOCK_SYS_EnableDmamuxClock(i);
         
        /* Init dmamux module in hardware level */
        DMAMUX_HAL_Init(dmamuxRegBase);
    }

    return kStatus_EDMA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_DRV_Deinit
 * Description   : Deinitilize EDMA.
 *
 *END**************************************************************************/
edma_status_t EDMA_DRV_Deinit(void)
{
    uint32_t i, j;
    IRQn_Type irqNumber;
    edma_chn_state_t *chn;

    /* Release all edma channel. */
    for (i = 0; i < DMA_INSTANCE_COUNT; i++)
    {
#if !defined FSL_FEATURE_EDMA_HAS_ERROR_IRQ
        /* Disable the error interrupt for eDMA module. */
        irqNumber = g_edmaErrIrqId[i];
        INT_SYS_DisableIRQ(irqNumber);
#endif

        for (j = i * FSL_FEATURE_EDMA_MODULE_CHANNEL; j < (i + 1) * FSL_FEATURE_EDMA_MODULE_CHANNEL; j++)
        {
            /* Release all channel. */
            chn = g_edma->chn[j];
            if (chn)
            {
                EDMA_DRV_ReleaseChannel(chn);
            }

            /* Enable channel interrupt ID. */
            irqNumber = g_edmaIrqId[i][j];
            INT_SYS_DisableIRQ(irqNumber);
        }

        /* Disable edma clock gate. */
        CLOCK_SYS_DisableDmaClock(i);
    }

    /* Disable dmamux clock gate. */
    for (i = 0; i < DMAMUX_INSTANCE_COUNT; i++)
    {
        CLOCK_SYS_DisableDmamuxClock(i);
    }

#if (USE_RTOS)
    OSA_MutexDestroy(&g_edma->lock);
#endif

    g_edma = NULL;

    return kStatus_EDMA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_DRV_InstallCallback
 * Description   : Register callback function and parameter.
 *
 *END**************************************************************************/
edma_status_t EDMA_DRV_InstallCallback(
        edma_chn_state_t *chn, edma_callback_t callback, void *parameter)
{
    chn->callback = callback;
    chn->parameter = parameter;

    return kStatus_EDMA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_DRV_RequestChannel
 * Description   : Request an eDMA channel.
 *
 *END**************************************************************************/
uint8_t EDMA_DRV_RequestChannel(
                uint8_t channel, dma_request_source_t source, edma_chn_state_t *chn)
{

    /*Check if dynamically allocation is requested */
    if (channel == kEDMAAnyChannel)
    {
        uint32_t i = 0, j;
        uint32_t map;
        map = ((uint32_t)source >> 8);

        while (map != 0)
        {
            if (map & (1U << i))
            {
                for (j = i * FSL_FEATURE_DMAMUX_MODULE_CHANNEL/FSL_FEATURE_EDMA_CHANNEL_GROUP_COUNT;
                        j < (i + 1) * FSL_FEATURE_DMAMUX_MODULE_CHANNEL/FSL_FEATURE_EDMA_CHANNEL_GROUP_COUNT; j++)
                {
                    EDMA_DRV_LOCK();
                    if (!g_edma->chn[j])
                    {
                        g_edma->chn[j] = chn;
                        EDMA_DRV_UNLOCK();
                        EDMA_DRV_ClaimChannel(j, source, chn);
                        return j;
                    }
                    EDMA_DRV_UNLOCK();
                }

            }
            map &= ~(0x1U << i);
            i++;
        }

        /* No available channel. */
        return kEDMAInvalidChannel;
    }

    /* static allocation */
    EDMA_DRV_LOCK();
    if (!g_edma->chn[channel])
    {
        g_edma->chn[channel] = chn;
        EDMA_DRV_UNLOCK();
        EDMA_DRV_ClaimChannel(channel, source, chn);
        return channel;
    }
    EDMA_DRV_UNLOCK();

    return kEDMAInvalidChannel;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_DRV_ClaimChannel
 * Description   : Claim an edma channel.
 *
 *END**************************************************************************/
static edma_status_t EDMA_DRV_ClaimChannel(
                uint8_t channel, dma_request_source_t source, edma_chn_state_t *chn)
{
    uint8_t src = (uint32_t)source & 0xFF;
    DMA_Type * edmaRegBase = VIRTUAL_CHN_TO_EDMA_MODULE_REGBASE(channel);
    uint32_t edmaChannel = VIRTUAL_CHN_TO_EDMA_CHN(channel);
    DMAMUX_Type * dmamuxRegBase = VIRTUAL_CHN_TO_DMAMUX_MODULE_REGBASE(channel);
    uint32_t dmamuxChannel = VIRTUAL_CHN_TO_DMAMUX_CHN(channel);

    /* Reset the channel state structure to default value. */
    memset(chn, 0, sizeof(edma_chn_state_t));

    /* Init the channel state structure to the allocated channel number. */
    chn->channel = channel;

    /* Enable error interrupt for this channel */
    EDMA_HAL_SetErrorIntCmd(edmaRegBase, true, (edma_channel_indicator_t)edmaChannel);

    /* Configure the DMAMUX for edma channel */
    DMAMUX_HAL_SetChannelCmd(dmamuxRegBase, dmamuxChannel, false);
    DMAMUX_HAL_SetTriggerSource(dmamuxRegBase, dmamuxChannel, src%(uint8_t)kDmamuxDmaRequestSource);
    DMAMUX_HAL_SetChannelCmd(dmamuxRegBase, dmamuxChannel, true);

    /* Clear the TCD registers for this channel */
    EDMA_HAL_HTCDClearReg(edmaRegBase, edmaChannel);

    return kStatus_EDMA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_DRV_ReleaseChannel
 * Description   : Free eDMA channel's hardware and software resource.
 *
 *END**************************************************************************/
edma_status_t EDMA_DRV_ReleaseChannel(edma_chn_state_t *chn)
{
    uint32_t channel = chn->channel;
    DMA_Type * edmaRegBase = VIRTUAL_CHN_TO_EDMA_MODULE_REGBASE(channel);
    uint32_t edmaChannel = VIRTUAL_CHN_TO_EDMA_CHN(channel);

    if (!g_edma->chn[channel])
    {
        return kStatus_EDMA_InvalidArgument;
    }

    /* Stop edma channel. */
    EDMA_HAL_SetDmaRequestCmd(edmaRegBase,(edma_channel_indicator_t)edmaChannel, false);

    memset(chn, 0x0, sizeof(edma_chn_state_t));

    EDMA_DRV_LOCK();
    g_edma->chn[channel] = NULL;
    EDMA_DRV_UNLOCK();
    return kStatus_EDMA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_DRV_ClearIntStatus
 * Description   : Clear done and interrupt status.
 *
 *END**************************************************************************/
static void EDMA_DRV_ClearIntStatus(uint8_t channel)
{
    DMA_Type * edmaRegBase = VIRTUAL_CHN_TO_EDMA_MODULE_REGBASE(channel);
    uint32_t edmaChannel = VIRTUAL_CHN_TO_EDMA_CHN(channel);

    EDMA_HAL_ClearDoneStatusFlag(edmaRegBase, (edma_channel_indicator_t)edmaChannel);
    EDMA_HAL_ClearIntStatusFlag(edmaRegBase, (edma_channel_indicator_t)edmaChannel);
}

#if (FSL_FEATURE_EDMA_MODULE_CHANNEL == 32U)
/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_IRQ_HANDLER
 * Description   : EDMA IRQ handler.This handler is for EDMA module in which
 * 				   channel n share the irq number with channel (n + 16)
 *
 *END**************************************************************************/
void EDMA_DRV_IRQHandler(uint8_t channel)
{
    edma_chn_state_t *chn = g_edma->chn[channel];
    DMA_Type * edmaRegBase = VIRTUAL_CHN_TO_EDMA_MODULE_REGBASE(channel);
    uint32_t edmaChannel = VIRTUAL_CHN_TO_EDMA_CHN(channel);

    while (channel < 32)
    {
        chn = g_edma->chn[channel];

        if ((chn != NULL) && (EDMA_HAL_GetIntStatusFlag(edmaRegBase, edmaChannel) != 0))
        {
            EDMA_DRV_ClearIntStatus(channel);
            if (chn->callback)
            {
                chn->callback(chn->parameter, chn->status);
            }
        }
        channel += 16;
        edmaRegBase = VIRTUAL_CHN_TO_EDMA_MODULE_REGBASE(channel);
        edmaChannel = VIRTUAL_CHN_TO_EDMA_CHN(channel);
    }
}
#elif (FSL_FEATURE_EDMA_MODULE_CHANNEL == 8U)
/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_IRQ_HANDLER
 * Description   : EDMA IRQ handler.This handler is for EDMA module in which
 * 				   channel n share the irq number with channel (n + 4)
 *
 *END**************************************************************************/
void EDMA_DRV_IRQHandler(uint8_t channel)
{
    edma_chn_state_t *chn = g_edma->chn[channel];
    DMA_Type * edmaRegBase = VIRTUAL_CHN_TO_EDMA_MODULE_REGBASE(channel);
    uint32_t edmaChannel = VIRTUAL_CHN_TO_EDMA_CHN(channel);

    while (channel < 8)
    {
        chn = g_edma->chn[channel];

        if ((chn != NULL) && (EDMA_HAL_GetIntStatusFlag(edmaRegBase, edmaChannel) != 0))
        {
            EDMA_DRV_ClearIntStatus(channel);
            if (chn->callback)
            {
                chn->callback(chn->parameter, chn->status);
            }
        }
        channel += 4;
        edmaRegBase = VIRTUAL_CHN_TO_EDMA_MODULE_REGBASE(channel);
        edmaChannel = VIRTUAL_CHN_TO_EDMA_CHN(channel);
    }
}
#else
/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_IRQ_HANDLER
 * Description   : EDMA IRQ handler.
 *
 *END**************************************************************************/
void EDMA_DRV_IRQHandler(uint8_t channel)
{
    edma_chn_state_t *chn = g_edma->chn[channel];

    if (!chn)
    {
        EDMA_DRV_StopChannel(chn);
        return;
    }

    EDMA_DRV_ClearIntStatus(channel);

    if (chn->callback)
    {
        chn->callback(chn->parameter, chn->status);
    }
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_ERR_IRQHandler
 * Description   : EDMA error handler
 *
 *END**************************************************************************/
void EDMA_DRV_ErrorIRQHandler(uint8_t instance)
{
    uint32_t channel, error, j = 0;
    DMA_Type * edmaRegBase = g_edmaBase[instance];
    edma_chn_state_t *chn;

    error = EDMA_HAL_GetErrorIntStatusFlag(edmaRegBase);

    while (error && (j < FSL_FEATURE_EDMA_MODULE_CHANNEL))
    {
        if (error & 1U)
        {
            channel = instance * FSL_FEATURE_EDMA_MODULE_CHANNEL + j;
            EDMA_HAL_SetDmaRequestCmd(edmaRegBase, (edma_channel_indicator_t)j, false);
            chn = g_edma->chn[channel];
            if (chn)
            {
                EDMA_DRV_ClearIntStatus(channel);
                chn->status = kEDMAChnError;
                if (chn->callback)
                {
                    chn->callback(chn->parameter, chn->status);
                }
            }
        }
        error = error >> 1U;
        j++;
    }
    EDMA_HAL_SetHaltCmd(edmaRegBase, false);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_DRV_ConfigLoopTransfer
 * Description   : Configures the DMA transfer in a loop.
 *
 *END**************************************************************************/
edma_status_t EDMA_DRV_ConfigLoopTransfer(
                            edma_chn_state_t *chn, edma_software_tcd_t *stcd,
                            edma_transfer_type_t type,
                            uint32_t srcAddr, uint32_t destAddr, uint32_t size,
                            uint32_t bytesOnEachRequest, uint32_t totalLength, uint8_t number)
{
    assert(stcd);

    uint8_t i;
    edma_software_tcd_t *stcdAddr = (edma_software_tcd_t *)STCD_ADDR(stcd);
    edma_transfer_size_t transfersize;
    edma_transfer_config_t config;

    /* Set the software TCD memory to default value. */
    memset(stcdAddr, 0, number * sizeof(edma_software_tcd_t));

    /* translate the transfer size to eDMA allowed transfer size enum type. */
    switch(size)
    {
        case 1:
            transfersize = kEDMATransferSize_1Bytes;
            break;
        case 2:
            transfersize = kEDMATransferSize_2Bytes;
            break;
        case 4:
            transfersize = kEDMATransferSize_4Bytes;
            break;
        case 16:
            transfersize = kEDMATransferSize_16Bytes;
            break;
        case 32:
            transfersize = kEDMATransferSize_32Bytes;
            break;
        default:
            return kStatus_EDMA_InvalidArgument;
    }

    /* Configure the software TCD one by one.*/
    config.srcLastAddrAdjust = 0;
    config.destLastAddrAdjust = 0;
    config.srcModulo = kEDMAModuloDisable;
    config.destModulo = kEDMAModuloDisable;
    config.srcTransferSize = transfersize;
    config.destTransferSize = transfersize;
    config.minorLoopCount = bytesOnEachRequest;
    config.majorLoopCount = totalLength / (bytesOnEachRequest * number);
    for(i = 0; i < number; i++)
    {
        switch (type)
        {
            case kEDMAPeripheralToMemory:
                /* Configure Source Read. */
                config.srcAddr = srcAddr;
                config.srcOffset = 0;

                /* Configure Dest Write. */
                config.destAddr = destAddr + i * (totalLength/number);
                config.destOffset = size;
                break;
            case kEDMAMemoryToPeripheral:
                /* Configure Source Read. */
                config.srcAddr = srcAddr + i * (totalLength/number);
                config.srcOffset = size;

                /* Configure Dest Write. */
                config.destAddr = destAddr;
                config.destOffset = 0;
                break;
            case kEDMAMemoryToMemory:
                /* Configure Source Read. */
                config.srcAddr = srcAddr + i * (totalLength/number);
                config.srcOffset = size;

                /* Configure Dest Write. */
                config.destAddr = destAddr + i * (totalLength/number);
                config.destOffset = size;
                break;
            default:
                return kStatus_EDMA_InvalidArgument;
        }

        EDMA_DRV_PrepareDescriptorTransfer(chn, &stcdAddr[i], &config, true, false);
        EDMA_DRV_PrepareDescriptorScatterGather(&stcdAddr[i], &stcdAddr[(i+1)%number]);
    }

    EDMA_DRV_PushDescriptorToReg(chn, &stcdAddr[0]);

    return kStatus_EDMA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_DRV_ConfigScatterGatherTransfer
 * Description   : User friendly interface to configure single end descritptor chain.
 *
 *END**************************************************************************/
edma_status_t EDMA_DRV_ConfigScatterGatherTransfer(
                        edma_chn_state_t *chn, edma_software_tcd_t *stcd,
                        edma_transfer_type_t type,
                        uint32_t size, uint32_t bytesOnEachRequest,
                        edma_scatter_gather_list_t *srcList, edma_scatter_gather_list_t *destList,
                        uint8_t number)
{
    assert(stcd);
    uint8_t i;
    edma_transfer_size_t transfersize;
    edma_software_tcd_t *stcdAddr = (edma_software_tcd_t *)STCD_ADDR(stcd);
    edma_transfer_config_t config;

    if (number > 1)
    {
        memset(stcdAddr, 0, number * sizeof(edma_software_tcd_t));
    }

    switch(size)
    {
        case 1:
            transfersize = kEDMATransferSize_1Bytes;
            break;
        case 2:
            transfersize = kEDMATransferSize_2Bytes;
            break;
        case 4:
            transfersize = kEDMATransferSize_4Bytes;
            break;
        case 16:
            transfersize = kEDMATransferSize_16Bytes;
            break;
        case 32:
            transfersize = kEDMATransferSize_32Bytes;
            break;
        default:
            return kStatus_EDMA_InvalidArgument;
    }


    /* Configure the software TCD one by one.*/
    config.srcLastAddrAdjust = 0;
    config.destLastAddrAdjust = 0;
    config.srcModulo = kEDMAModuloDisable;
    config.destModulo = kEDMAModuloDisable;
    config.srcTransferSize = transfersize;
    config.destTransferSize = transfersize;
    config.minorLoopCount = bytesOnEachRequest;

    for (i = 0; i < number; i++)
    {
        config.srcAddr = srcList[i].address;
        config.destAddr = destList[i].address;
        if (srcList[i].length != destList[i].length)
        {
            return kStatus_EDMA_InvalidArgument;
        }
        config.majorLoopCount = srcList[i].length/bytesOnEachRequest;

        switch (type)
        {
            case kEDMAPeripheralToMemory:
                /* Configure Source Read. */
                config.srcOffset = 0;

                /* Configure Dest Write. */
                config.destOffset = size;
                break;
            case kEDMAMemoryToPeripheral:
                /* Configure Source Read. */
                config.srcOffset = size;

                /* Configure Dest Write. */
                config.destOffset = 0;
                break;
            case kEDMAMemoryToMemory:
                /* Configure Source Read. */
                config.srcOffset = size;

                /* Configure Dest Write. */
                config.destOffset = size;
                break;
            default:
                return kStatus_EDMA_InvalidArgument;
        }

        if (number == 1)
        {
            /* If only one TCD is required, only hardware TCD is required and user
             * is not required to prepare the software TCD memory. */
            edma_software_tcd_t temp[2];
            edma_software_tcd_t *tempTCD = STCD_ADDR(temp);
            memset((void*) tempTCD,0, sizeof(edma_software_tcd_t));
            EDMA_DRV_PrepareDescriptorTransfer(chn, tempTCD, &config, true, true);
            EDMA_DRV_PushDescriptorToReg(chn, tempTCD);
        }
        else if (i == (number - 1))
        {
            EDMA_DRV_PrepareDescriptorTransfer(chn, &stcdAddr[i], &config, true, true);
            EDMA_DRV_PushDescriptorToReg(chn, &stcdAddr[0]);
        }
        else
        {
            EDMA_DRV_PrepareDescriptorTransfer(chn, &stcdAddr[i], &config, false, false);
            EDMA_DRV_PrepareDescriptorScatterGather(&stcdAddr[i], &stcdAddr[i+1]);
        }
    }

    return kStatus_EDMA_Success;

}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_DRV_StartChannel
 * Description   : Starts an eDMA channel.
 *
 *END**************************************************************************/
edma_status_t EDMA_DRV_StartChannel(edma_chn_state_t *chn)
{
    uint32_t channel = chn->channel;
    DMA_Type * edmaRegBase = VIRTUAL_CHN_TO_EDMA_MODULE_REGBASE(channel);
    uint32_t edmaChannel = VIRTUAL_CHN_TO_EDMA_CHN(channel);

    EDMA_HAL_SetDmaRequestCmd(edmaRegBase,(edma_channel_indicator_t)edmaChannel,true);

    return kStatus_EDMA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_DRV_StopChannel
 * Description   : Stops an eDMA channel.
 *
 *END**************************************************************************/
edma_status_t EDMA_DRV_StopChannel(edma_chn_state_t *chn)
{
    uint32_t channel = chn->channel;
    DMA_Type * edmaRegBase = VIRTUAL_CHN_TO_EDMA_MODULE_REGBASE(channel);
    uint32_t edmaChannel = VIRTUAL_CHN_TO_EDMA_CHN(channel);

    EDMA_HAL_SetDmaRequestCmd(edmaRegBase,(edma_channel_indicator_t)edmaChannel, false);

    return kStatus_EDMA_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : EDMA_DRV_PushDescriptorToReg
 * Description   : Copy the software TCD configuration to the hardware TCD.
 *
 *END**************************************************************************/
edma_status_t EDMA_DRV_PushDescriptorToReg(edma_chn_state_t *chn, edma_software_tcd_t *stcd)
{
    uint32_t channel = chn->channel;
    DMA_Type * edmaRegBase = VIRTUAL_CHN_TO_EDMA_MODULE_REGBASE(channel);
    uint32_t edmaChannel = VIRTUAL_CHN_TO_EDMA_CHN(channel);

    EDMA_HAL_HTCDClearReg(edmaRegBase, edmaChannel);
    EDMA_HAL_PushSTCDToHTCD(edmaRegBase, edmaChannel, stcd);

    return kStatus_EDMA_Success;
}
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/

