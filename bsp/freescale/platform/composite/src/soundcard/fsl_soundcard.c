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


#include "fsl_soundcard.h"
#include <assert.h>
#include <string.h>
#include "fsl_os_abstraction.h"

/*******************************************************************************
 *Definitation
 ******************************************************************************/
#if SOUNDCARD_USE_STATIC_MEM
#if defined( __ICCCF__ ) || defined( __ICCARM__ )
#pragma segment="SAI_BDT_Z"
#pragma data_alignment=4
__no_init static uint8_t s_tx_buffer[AUDIO_CONTROLLER_NUM][AUDIO_BUFFER_SIZE] @ "SAI_BDT_Z";
__no_init static uint8_t s_rx_buffer[AUDIO_CONTROLLER_NUM][AUDIO_BUFFER_SIZE] @ "SAI_BDT_Z";
#elif defined(__GNUC__)
__attribute__((aligned(4))) static uint8_t s_tx_buffer[AUDIO_CONTROLLER_NUM][AUDIO_BUFFER_SIZE];
__attribute__((aligned(4))) static uint8_t s_rx_buffer[AUDIO_CONTROLLER_NUM][AUDIO_BUFFER_SIZE];
#elif defined (__CC_ARM)
__align(4) static uint8_t s_tx_buffer[AUDIO_CONTROLLER_NUM][AUDIO_BUFFER_SIZE];
__align(4) static uint8_t s_rx_buffer[AUDIO_CONTROLLER_NUM][AUDIO_BUFFER_SIZE];
#endif
#endif

#if USEDMA
void SND_TxDmaCallback(void *param, edma_chn_status_t status);
void SND_RxDmaCallback(void *param, edma_chn_status_t status);
#else
void SND_TxCallback(void *param);
void SND_RxCallback(void *param);
#endif

/* The instance for sai operation structure. */
audio_ctrl_operation_t g_sai_ops =
{
    SAI_DRV_TxInit,
    SAI_DRV_RxInit,
    SAI_DRV_TxDeinit,
    SAI_DRV_RxDeinit,
    SAI_DRV_TxConfigDataFormat,
    SAI_DRV_RxConfigDataFormat,
    SAI_DRV_TxStartModule,
    SAI_DRV_RxStartModule,
    SAI_DRV_TxStopModule,
    SAI_DRV_RxStopModule,
    SAI_DRV_TxRegisterCallback,
    SAI_DRV_RxRegisterCallback,
    SAI_DRV_TxSetIntCmd,
    SAI_DRV_RxSetIntCmd,
    SAI_DRV_TxSetDmaCmd,
    SAI_DRV_RxSetDmaCmd,
    SAI_DRV_TxGetWatermark,
    SAI_DRV_RxGetWatermark,
    SAI_DRV_TxGetFifoAddr,
    SAI_DRV_RxGetFifoAddr,
    SAI_DRV_SendDataInt,
    SAI_DRV_ReceiveDataInt
};

/* Instance of codec operation for sgtl5000. */
audio_codec_operation_t g_sgtl_ops =
{
    SGTL_Init,
    SGTL_Deinit,
    SGTL_ConfigDataFormat,
    SGTL_SetDACMute,
    SGTL_SetDACVoulme,
    SGTL_GetDACVolume
};

/*******************************************************************************
 *Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
*
* Function Name : SND_TxInit
* Description	: Initialize the soundcard.
*  The soundcard includes a controller and a codec.
*END**************************************************************************/
snd_status_t SND_TxInit(
    sound_card_t * card, void * ctrl_config, void * codec_config, ctrl_state_t *state)
{
    audio_controller_t *ctrl = &card->controller;
    audio_codec_t *codec = &card->codec;
    /* Allocate space for buffer */
    audio_buffer_t *buffer = &card->buffer;
    /* Buffer size and block settings */
    if ((buffer->blocks == 0) || (buffer->size == 0))
    {
        buffer->blocks = AUDIO_BUFFER_BLOCK;
        buffer->size = AUDIO_BUFFER_BLOCK_SIZE;
    }
#if SOUNDCARD_USE_STATIC_MEM
    buffer->buff = &s_tx_buffer[ctrl->instance][0];
#else
    buffer->buff = (uint8_t *)OSA_MemAllocZero(buffer->size * buffer->blocks);
    if(!buffer->buff)
    {
        return kStatus_SND_BufferAllocateFail;
    }
#endif
    buffer->input_curbuff = buffer->buff;
    buffer->output_curbuff = buffer->buff;
    /* Initialize the status structure */
    buffer->empty_block = buffer->blocks;
    buffer->full_block = 0;
    OSA_SemaCreate(&buffer->sem, buffer->blocks); 
    /* Initialize audio controller and codec */
    ctrl->ops->Ctrl_TxInit(ctrl->instance, ctrl_config, state);
    codec->ops->Codec_Init((void *)codec->handler, codec_config);
#if USEDMA
    EDMA_DRV_RequestChannel(kEDMAAnyChannel, ctrl->dma_source, &ctrl->dma_channel);
    EDMA_DRV_InstallCallback(&ctrl->dma_channel, SND_TxDmaCallback, (void *)card);
#else
    ctrl->ops->Ctrl_TxRegisterCallback(ctrl->instance,  SND_TxCallback, card);
#endif   
    return kStatus_SND_Success;
}

/*FUNCTION**********************************************************************
*
* Function Name : SND_RxInit
* Description	: Initialize the Rx soundcard.
*  The soundcard includes a controller and a codec.
*END**************************************************************************/
snd_status_t SND_RxInit(
sound_card_t * card, void * ctrl_config, void * codec_config, ctrl_state_t *state)
{
    audio_controller_t *ctrl = &card->controller;
    audio_codec_t *codec = &card->codec;
    /* Allocate space for buffer */
    audio_buffer_t *buffer = &card->buffer;
    /* Buffer size and block settings */
    if ((buffer->blocks == 0) || (buffer->size == 0))
    {
        buffer->blocks = AUDIO_BUFFER_BLOCK;
        buffer->size = AUDIO_BUFFER_BLOCK_SIZE;
    }
#if SOUNDCARD_USE_STATIC_MEM
    buffer->buff = &s_rx_buffer[ctrl->instance][0];
#else
    buffer->buff = (uint8_t *)OSA_MemAllocZero(buffer->size * buffer->blocks);
    if(!buffer->buff)
    {
        return kStatus_SND_BufferAllocateFail;
    }
#endif
    buffer->input_curbuff = buffer->buff;
    buffer->output_curbuff = buffer->buff;
    /* Initialize the status structure */
    buffer->empty_block = buffer->blocks;
    buffer->full_block = 0;
    OSA_SemaCreate(&buffer->sem, 0);
    /* Initialize audio controller and codec */
    ctrl->ops->Ctrl_RxInit(ctrl->instance, ctrl_config,state);
    codec->ops->Codec_Init((void *)codec->handler, codec_config);
#if USEDMA
    EDMA_DRV_RequestChannel(kEDMAAnyChannel, ctrl->dma_source, &ctrl->dma_channel);
    EDMA_DRV_InstallCallback(&ctrl->dma_channel, SND_RxDmaCallback, (void *)card);
#else
    ctrl->ops->Ctrl_RxRegisterCallback(ctrl->instance,  SND_RxCallback, card);
#endif   
    return kStatus_SND_Success;
}

/*FUNCTION*********************************************************************
*
* Function Name : SND_TxDeinit
* Description	: Deinit the tx soundcard.
*  The soundcard includes a controller and a codec.
*END**************************************************************************/
snd_status_t SND_TxDeinit(sound_card_t *card)
{
    audio_controller_t *ctrl = &card->controller;
    audio_codec_t *codec = &card->codec;
    audio_buffer_t *buffer = &card->buffer;
    /* Call the deinit function of the ctrl and codec. */
    ctrl->ops->Ctrl_TxDeinit(ctrl->instance);
    codec->ops->Codec_Deinit((void *)codec->handler);
#if USEDMA
    /* Deinit the dma resource */
    EDMA_DRV_StopChannel(&ctrl->dma_channel);
    EDMA_DRV_ReleaseChannel(&ctrl->dma_channel);
#endif
    OSA_SemaDestroy(&buffer->sem);
#if !SOUNDCARD_USE_STATIC_MEM
    /* Free the tx and rx buffer. */
    OSA_MemFree(buffer->buff);
#endif
    return kStatus_SND_Success;
}

/*FUNCTION*********************************************************************
*
* Function Name : SND_RxDeinit
* Description	: Deinit the rx soundcard.
*  The soundcard includes a controller and a codec.
*END**************************************************************************/
snd_status_t SND_RxDeinit(sound_card_t *card)
{
    audio_controller_t *ctrl = &card->controller;
    audio_codec_t *codec = &card->codec;
    audio_buffer_t *buffer = &card->buffer;
    /* Call the deinit function of the ctrl and codec. */
    ctrl->ops->Ctrl_RxDeinit(ctrl->instance);
    codec->ops->Codec_Deinit((void *)codec->handler);
#if USEDMA
    /* Deinit the dma resource */
    EDMA_DRV_StopChannel(&ctrl->dma_channel);
    EDMA_DRV_ReleaseChannel(&ctrl->dma_channel);
#endif
    OSA_SemaDestroy(&buffer->sem);
#if !SOUNDCARD_USE_STATIC_MEM
    /* Free the tx and rx buffer. */
    OSA_MemFree(buffer->buff);
#endif
    return kStatus_SND_Success;
}

/*FUNCTION**********************************************************************
*
* Function Name : SND_TxConfigDataFormat
* Description	: Configure the audio file format in tx soundcard.
*  The soundcard includes a controller and a codec. The audio format includes 
*  sample rate, bit length and so on.
*END**************************************************************************/
snd_status_t SND_TxConfigDataFormat(sound_card_t *card, ctrl_data_format_t *format)
{
    audio_controller_t *ctrl = &card->controller;
    audio_codec_t *codec = &card->codec;

    ctrl->ops->Ctrl_TxConfigDataFormat(ctrl->instance, format);
    codec->ops->Codec_ConfigDataFormat(codec->handler, format->mclk, format->sample_rate, 
                                                                    format->bits);
    /* Configure dma */
#if USEDMA
    audio_buffer_t *buffer = &card->buffer;
    uint32_t watermark = ctrl->ops->Ctrl_TxGetWatermark(ctrl->instance);
    uint8_t sample_size = format->bits/8;
    if((sample_size == 3) || (format->bits & 0x7))
    {
        sample_size = 4;
    }
    uint32_t desAddr = ctrl->ops->Ctrl_TxGetFifoAddr(ctrl->instance, ctrl->fifo_channel);
    EDMA_DRV_ConfigLoopTransfer(
            &ctrl->dma_channel, ctrl->stcd, kEDMAMemoryToPeripheral,
            (uint32_t)buffer->buff, (uint32_t)desAddr, sample_size,
            sample_size * (AUDIO_FIFO_LEN -watermark) , AUDIO_BUFFER_SIZE, AUDIO_BUFFER_BLOCK);
    EDMA_DRV_StartChannel(&ctrl->dma_channel); 
#endif
    return kStatus_SND_Success;
}

/*FUNCTION**********************************************************************
*
* Function Name : SND_RxConfigDataFormat
* Description	: Configure the audio file format in rx soundcard.
*  The soundcard includes a controller and a codec. The audio format includes 
*  sample rate, bit length and so on.
*END**************************************************************************/
snd_status_t SND_RxConfigDataFormat(sound_card_t *card, ctrl_data_format_t *format)
{
    audio_controller_t *ctrl = &card->controller;
    audio_codec_t *codec = &card->codec;

    ctrl->ops->Ctrl_RxConfigDataFormat(ctrl->instance, format);
    codec->ops->Codec_ConfigDataFormat(codec->handler, format->mclk, format->sample_rate, 
                                                                    format->bits);
    /* Configure dma */
#if USEDMA
    audio_buffer_t *buffer = &card->buffer;
    uint8_t sample_size = format->bits/8;
    uint32_t watermark = ctrl->ops->Ctrl_RxGetWatermark(ctrl->instance);
    if((sample_size == 3) || (format->bits & 0x7))
    {
        sample_size = 4;
    }
    uint32_t desAddr = ctrl->ops->Ctrl_RxGetFifoAddr(ctrl->instance,ctrl->fifo_channel);
    EDMA_DRV_ConfigLoopTransfer(
            &ctrl->dma_channel, ctrl->stcd, kEDMAPeripheralToMemory,
             (uint32_t)desAddr, (uint32_t)buffer->buff, sample_size,
            sample_size * watermark, AUDIO_BUFFER_SIZE, AUDIO_BUFFER_BLOCK);
    EDMA_DRV_StartChannel(&ctrl->dma_channel);
#endif
    return kStatus_SND_Success;
}

/*FUNCTION**********************************************************************
*
* Function Name : SND_TxUpdateStatus
* Description	: Update the status of tx soundcard internal logic
* The function would tell tx soundcard how many data applications have written
* to the ring buffer.
*END**************************************************************************/
uint32_t SND_TxUpdateStatus(sound_card_t * card, uint32_t len)
{
    audio_buffer_t * buffer = &card->buffer;
    uint32_t blocks = len/buffer->size;
    /* Update the buffer information */
    buffer->requested += len;
    buffer->queued += len;

    if(buffer->input_index + blocks < buffer->blocks)
    {
        buffer->input_index += blocks;
    }
    else
    {
        buffer->input_index = blocks - (buffer->blocks - 1 - buffer->input_index) - 1;
    }
    buffer->input_curbuff = buffer->buff + buffer->input_index * buffer->size;
    buffer->empty_block -= blocks;
    buffer->full_block += blocks;
    /* If sai is not enable, enable the sai */
    if (buffer->first_io)
    {
        buffer->first_io = false;
        SND_TxStart(card);
    }
    return len;
}

/*FUNCTION**********************************************************************
*
* Function Name : SND_RxUpdateStatus
* Description	: Update the status of rx soundcard internal logic
* The function would tell rx soundcard how many data applications have received
* from the ring buffer.
*END**************************************************************************/
uint32_t SND_RxUpdateStatus(sound_card_t * card, uint32_t len)
{
    audio_buffer_t * buffer = &card->buffer;
    uint32_t blocks = len/buffer->size;
    /* Update inner information */
    buffer->requested += len;
    buffer->processed += len;
    buffer->queued -= len;
    /* Switch the buffer */
    if(buffer->output_index + blocks < buffer->blocks)
    {
        buffer->output_index += blocks;
    }
    else
    {
        buffer->output_index = blocks - (buffer->blocks - 1 - buffer->output_index) - 1;
    }
    buffer->output_curbuff = buffer->buff + buffer->output_index * buffer->size;
    buffer->full_block -= blocks;
    buffer->empty_block += blocks;  
    /* If sai is not enable, enable the sai */
    if (buffer->first_io)
    {
        buffer->first_io = false;
        SND_RxStart(card);
    }
    return len;
}

/*FUNCTION**********************************************************************
*
* Function Name : SND_TxCallback
* Description	: Callback function to tell that audio controller have finished 
* a period data.
* The function would update the buffer status information.
*END**************************************************************************/
void SND_TxCallback(void *param)
{
    sound_card_t *card = (sound_card_t *)param;
    audio_buffer_t *buffer = &card->buffer;
    if(buffer->queued == 0)
    {
        return;
    }
    buffer->processed += buffer->size;
    buffer->queued -= buffer->size;

    /* Change the current buffer */
    if (buffer->output_index == buffer->blocks - 1)
    {
        buffer->output_curbuff = buffer->buff;
        buffer->output_index = 0;
    }
    else
    {
        buffer->output_index ++;
        buffer->output_curbuff += buffer->size;
    }
    /* Update the status */
    buffer->empty_block += 1;
    buffer->full_block -= 1;
    /* Judge if need to close the SAI transfer. */
    if (buffer->input_index == buffer->output_index)
    {
        SND_TxStop(card);
        buffer->buffer_error ++;
        buffer->first_io = true;
    }
    else
    {
#if !USEDMA
    audio_controller_t * ctrl = &card->controller;
    ctrl->ops->Ctrl_SendData(ctrl->instance, buffer->output_curbuff, buffer->size);
#endif
    }
    /* post the sync */
    OSA_SemaPost(&buffer->sem);
}

/*FUNCTION**********************************************************************
*
* Function Name : SND_RxCallback
* Description	: Callback function to tell that audio controller have finished
*  a period data.
* The function would update the buffer status information.
*END**************************************************************************/
void SND_RxCallback(void *param)
{
    sound_card_t *card = (sound_card_t *)param;
    audio_buffer_t *buffer = &card->buffer;
    buffer->queued += buffer->size;
    /* Change the current buffer. */
    if (buffer->input_index == buffer->blocks - 1)
    {  
        buffer->input_curbuff = buffer->buff;
        buffer->input_index = 0;
    }
    else
    {
        buffer->input_index ++;
        buffer->input_curbuff += buffer->size;
    }
    buffer->empty_block -= 1;
    buffer->full_block += 1;
    /* Judge if need to close the SAI transfer, while the buffer is full, 
     * we need to close the SAI */
    if (buffer->input_index == buffer->output_index)
    {
        SND_RxStop(card);
        buffer->buffer_error ++;
        buffer->first_io = true;
    }
    else
     {
#if !USEDMA
    audio_controller_t *ctrl = &card->controller;
    ctrl->ops->Ctrl_ReceiveData(ctrl->instance, buffer->input_curbuff, buffer->size);
#endif
    }
    OSA_SemaPost(&buffer->sem);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SND_GetStatus
 * Description   : Get the status of audio buffer, the status includes the empty
 *  blocks, full blocks and the starting address.
 *END**************************************************************************/
 void SND_GetStatus(sound_card_t *card, snd_state_t *status)
{
    audio_buffer_t *buffer = &card->buffer;
    status->size = buffer->size;
    status->empty_block = buffer->empty_block;
    status->full_block = buffer->full_block;
    status->input_address = buffer->input_curbuff;
    status->output_address = buffer->output_curbuff;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SND_WaitEvent
 * Description   : This function is used for appliaction to wait for the semaphore
 * to copy data in/out the sai buffer.
 *END**************************************************************************/
void SND_WaitEvent(sound_card_t *card)
{
    osa_status_t syncStatus;
    audio_buffer_t *buffer = &card->buffer;
    do
    {
        syncStatus = OSA_SemaWait(&buffer->sem, OSA_WAIT_FOREVER);
    }while(syncStatus == kStatus_OSA_Idle);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SND_TxStart
 * Description   : This function is used to start tx transfer.
 *END**************************************************************************/
void SND_TxStart(sound_card_t *card)
{
    audio_controller_t *ctrl = &card->controller;
#if !USEDMA
    audio_buffer_t *buffer = &card->buffer;
    ctrl->ops->Ctrl_SendData(ctrl->instance, buffer->output_curbuff, buffer->size);
    ctrl->ops->Ctrl_TxSetIntCmd(ctrl->instance, true);
#else
    ctrl->ops->Ctrl_TxSetDmaCmd(ctrl->instance,true);
    EDMA_DRV_StartChannel(&card->controller.dma_channel);
#endif
    ctrl->ops->Ctrl_TxStart(ctrl->instance);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SND_RxStart
 * Description   : This function is used to start rx receive.
 *END**************************************************************************/
void SND_RxStart(sound_card_t *card)
{
    audio_controller_t *ctrl = &card->controller;
#if !USEDMA
    audio_buffer_t *buffer = &card->buffer;
    ctrl->ops->Ctrl_ReceiveData(ctrl->instance, buffer->input_curbuff, buffer->size);
    ctrl->ops->Ctrl_RxSetIntCmd(ctrl->instance, true);
#else
    ctrl->ops->Ctrl_RxSetDmaCmd(ctrl->instance,true);
    EDMA_DRV_StartChannel(&card->controller.dma_channel);
#endif
    ctrl->ops->Ctrl_RxStart(ctrl->instance);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SND_SetMuteCmd
 * Description   : This function is used to mute or unmute the soundcard.
 *END**************************************************************************/
snd_status_t SND_SetMuteCmd(sound_card_t * card,bool enable)
{
    audio_codec_t *codec = &card->codec;
    codec->ops->Codec_SetMuteCmd(codec->handler, enable);
    return kStatus_SND_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SND_SetVolume
 * Description   : This function is used to set the volume of soundcard.
 *END**************************************************************************/
snd_status_t SND_SetVolume(sound_card_t * card,uint32_t volume)
{
    audio_codec_t *codec = &card->codec;
    codec->ops->Codec_SetMuteCmd(codec->handler, false);
    codec->ops->Codec_SetVolume(codec->handler,volume);
    return kStatus_SND_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SND_GetVolume
 * Description   : This function is used to get the volume of soundcard.
 *END**************************************************************************/
uint32_t SND_GetVolume(sound_card_t * card)
{
    audio_codec_t *codec = &card->codec;
    return codec->ops->Codec_GetVolume(codec->handler);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SND_TxDmaCallback
 * Description   : This function is as the tx callback function registered to dma module.
 *END**************************************************************************/
void SND_TxDmaCallback(void *param, edma_chn_status_t status)
{
    SND_TxCallback(param);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SND_RxDmaCallback
 * Description   : This function is as the rx callback function registered to dma module.
 *END**************************************************************************/
void SND_RxDmaCallback(void *param, edma_chn_status_t status)
{
    SND_RxCallback(param);    
}

/*******************************************************************************
 *EOF
 ******************************************************************************/
 
