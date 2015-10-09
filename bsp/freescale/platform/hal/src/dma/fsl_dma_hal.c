/*
* Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* o Redistributions of source code must retain the above copyright notice, this list
*	of conditions and the following disclaimer.
*
* o Redistributions in binary form must reproduce the above copyright notice, this
*	list of conditions and the following disclaimer in the documentation and/or
*	other materials provided with the distribution.
*
* o Neither the name of Freescale Semiconductor, Inc. nor the names of its
*	contributors may be used to endorse or promote products derived from this
*	software without specific prior written permission.
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
#include "fsl_dma_hal.h"
#if FSL_FEATURE_SOC_DMA_COUNT

/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_HAL_Init
 * Description   : Set all registers for the channel to 0.
 *
 *END**************************************************************************/
void DMA_HAL_Init(DMA_Type * base,uint32_t channel)
{
    assert(channel < FSL_FEATURE_DMA_DMAMUX_CHANNELS);
    DMA_WR_SAR(base,channel,0);
    DMA_WR_DAR(base,channel,0);
    DMA_WR_DCR(base,channel,0);
    DMA_WR_DSR(base,channel, 0);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_HAL_ConfigTransfer
 * Description   : Configure the basic paramenters for dma transfer.
 *
 *END**************************************************************************/
void DMA_HAL_ConfigTransfer(
    DMA_Type * base,uint32_t channel,dma_transfer_size_t size,dma_transfer_type_t type,
    uint32_t sourceAddr, uint32_t destAddr, uint32_t length)
{

    dma_channel_link_config_t config;

    config.channel1 = 0;
    config.channel2 = 0;
    config.linkType = kDmaChannelLinkDisable;

    /* Common configuration. */
    DMA_BWR_DCR_AA(base, channel, false);
    DMA_BWR_DCR_CS(base, channel, true);
    DMA_BWR_DCR_EADREQ(base, channel, false);
    DMA_BWR_DCR_D_REQ(base, channel, true);
    DMA_HAL_SetChanLink(base, channel, &config);

    DMA_BWR_DCR_EINT(base, channel, true);
    DMA_WR_SAR(base, channel, sourceAddr);
    DMA_WR_DAR(base, channel, destAddr);
    DMA_BWR_DCR_SMOD(base, channel, kDmaModuloDisable);
    DMA_BWR_DCR_DMOD(base, channel, kDmaModuloDisable);
    DMA_BWR_DCR_SSIZE(base, channel, size);
    DMA_BWR_DCR_DSIZE(base, channel, size);
    DMA_BWR_DSR_BCR_BCR(base, channel, length);

    switch (type)
    {
      case kDmaMemoryToPeripheral:
          DMA_BWR_DCR_SINC(base, channel, true);
          DMA_BWR_DCR_DINC(base, channel, false);
          break;
      case kDmaPeripheralToMemory:
          DMA_BWR_DCR_SINC(base, channel, false);
          DMA_BWR_DCR_DINC(base, channel, true);
          break;
      case kDmaMemoryToMemory:
          DMA_BWR_DCR_SINC(base, channel, true);
          DMA_BWR_DCR_DINC(base, channel, true);
          break;
      case kDmaPeripheralToPeripheral:
          DMA_BWR_DCR_SINC(base, channel, false);
          DMA_BWR_DCR_DINC(base, channel, false);
          break;
      default:
          break;
    }

}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_HAL_SetChanLink
 * Description   : Configure the channel link feature.
 *
 *END**************************************************************************/
void DMA_HAL_SetChanLink(
        DMA_Type * base, uint8_t channel, dma_channel_link_config_t *mode)
{
    assert(channel < FSL_FEATURE_DMA_DMAMUX_CHANNELS);

    DMA_BWR_DCR_LINKCC(base, channel, mode->linkType);

    switch(mode->linkType)
    {
        case kDmaChannelLinkDisable:
            break;
        case kDmaChannelLinkChan1AndChan2:
            DMA_BWR_DCR_LCH1(base, channel, mode->channel1);
            DMA_BWR_DCR_LCH2(base, channel, mode->channel2);
            DMA_HAL_SetCycleStealCmd(base,channel,true);
            break;
        case kDmaChannelLinkChan1:
            DMA_BWR_DCR_LCH1(base, channel, mode->channel1);
            DMA_HAL_SetCycleStealCmd(base,channel,true);
            break;
        case kDmaChannelLinkChan1AfterBCR0:
            DMA_BWR_DCR_LCH1(base, channel, mode->channel1);
            break;
        default:
            break;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DMA_HAL_GetStatus
 * Description   : Get dma transfer status.
 *
 *END**************************************************************************/
dma_error_status_t DMA_HAL_GetStatus(DMA_Type * base, uint8_t channel)
{
    assert(channel < FSL_FEATURE_DMA_DMAMUX_CHANNELS);
    
    dma_error_status_t status;
    uint32_t val = DMA_RD_DSR_BCR(base,channel);
    status.dmaBytesToBeTransffered = val & DMA_DSR_BCR_BCR_MASK;
    status.dmaBusy = (bool)((val & DMA_DSR_BCR_BSY_MASK) >> DMA_DSR_BCR_BSY_SHIFT);
    status.dmaTransDone = (bool)((val & DMA_DSR_BCR_DONE_MASK) >> DMA_DSR_BCR_DONE_SHIFT);
    status.dmaPendingRequest = (bool)((val & DMA_DSR_BCR_REQ_MASK) >> DMA_DSR_BCR_REQ_SHIFT);
    status.dmaDestBusError = (bool)((val & DMA_DSR_BCR_BED_MASK) >> DMA_DSR_BCR_BED_SHIFT);
    status.dmaSourceBusError = (bool)((val & DMA_DSR_BCR_BES_MASK) >> DMA_DSR_BCR_BES_SHIFT);
    status.dmaConfigError = (bool)((val & DMA_DSR_BCR_CE_MASK) >> DMA_DSR_BCR_CE_SHIFT);
    return status;
}

#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/

