/*
 * Copyright (c) 2013 - 2015, Freescale Semiconductor, Inc.
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

#include "fsl_sai_driver.h"
#include "fsl_interrupt_manager.h"
#include "fsl_clock_manager.h"
#if FSL_FEATURE_SOC_I2S_COUNT

/*******************************************************************************
 *Definition
 ******************************************************************************/
sai_state_t * volatile sai_state_ids[I2S_INSTANCE_COUNT][2];

#if defined FSL_FEATURE_EDMA_MODULE_CHANNEL
/* EDMA callback function */
void SAI_DRV_EdmaCallback(void *param, edma_chn_status_t status);
#else
void SAI_DRV_DmaCallback(void *param, dma_channel_status_t status);
#endif


/*******************************************************************************
 * Code
 ******************************************************************************/
 
/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_DRV_TxInit
 * Description   : Initialize sai tx module, and initialize sai state.
 *
 *END**************************************************************************/
sai_status_t SAI_DRV_TxInit(uint32_t instance, sai_user_config_t * config, sai_state_t *state)
{
    I2S_Type * reg_base = g_saiBase[instance];
    /* Open clock gate for sai instance */
    CLOCK_SYS_EnableSaiClock(instance);
    /*Check if the device is busy */
    if(sai_state_ids[instance][0] != NULL)
    {
        return kStatus_SAI_DeviceBusy;
    }
    sai_state_ids[instance][0] = state;
    SAI_HAL_TxInit(reg_base);
    /* Mclk source select */
    if (config->slave_master == kSaiMaster)
    {
        SAI_HAL_SetMclkSrc(reg_base, config->mclk_source);
        SAI_HAL_TxSetBclkSrc(reg_base, config->bclk_source);
    }
    SAI_HAL_TxSetSyncMode(reg_base, config->sync_mode);
    SAI_HAL_TxSetMasterSlave(reg_base, config->slave_master);
    SAI_HAL_TxSetProtocol(reg_base, config->protocol);
    SAI_HAL_TxSetDataChn(reg_base, config->channel);
#if (FSL_FEATURE_SAI_FIFO_COUNT > 1)
    SAI_HAL_TxSetWatermark(reg_base, config->watermark);
#endif

    /* Fill the state structure */
    sai_state_ids[instance][0]->sync_mode = config->sync_mode;
    sai_state_ids[instance][0]->fifo_channel = config->channel;
    sai_state_ids[instance][0]->dma_source = config->dma_source;
#if (FSL_FEATURE_SAI_FIFO_COUNT > 1)
    sai_state_ids[instance][0]->watermark = config->watermark;
#endif
    sai_state_ids[instance][0]->master_slave = config->slave_master;
    OSA_SemaCreate(&state->sem, 0);
    INT_SYS_EnableIRQ(g_saiTxIrqId[instance]);
 
    return kStatus_SAI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_DRV_RxInit
 * Description   : Initialize sai rx module, and initialize sai state.
 *
 *END**************************************************************************/
sai_status_t SAI_DRV_RxInit(uint32_t instance, sai_user_config_t * config, sai_state_t *state)
{
    I2S_Type * reg_base = g_saiBase[instance];
    /* Open clock gate for sai instance */
    CLOCK_SYS_EnableSaiClock(instance);
    /*Check if the device is busy */
    if(sai_state_ids[instance][1] != NULL)
    {
        return kStatus_SAI_DeviceBusy;
    }
    sai_state_ids[instance][1] = state;
    SAI_HAL_RxInit(reg_base);
    /* Mclk source select */
    if (config->slave_master == kSaiMaster)
    {
        SAI_HAL_SetMclkSrc(reg_base, config->mclk_source);
        SAI_HAL_RxSetBclkSrc(reg_base, config->bclk_source);
    }
    SAI_HAL_RxSetSyncMode(reg_base, config->sync_mode);
    SAI_HAL_RxSetMasterSlave(reg_base, config->slave_master);
    SAI_HAL_RxSetProtocol(reg_base, config->protocol);
    SAI_HAL_RxSetDataChn(reg_base, config->channel);
#if (FSL_FEATURE_SAI_FIFO_COUNT > 1)
    SAI_HAL_RxSetWatermark(reg_base, config->watermark);
#endif
    /* Fill the state structure */
    sai_state_ids[instance][1]->sync_mode = config->sync_mode;
    sai_state_ids[instance][1]->fifo_channel = config->channel;
    sai_state_ids[instance][1]->dma_source = config->dma_source;
#if (FSL_FEATURE_SAI_FIFO_COUNT > 1)
    sai_state_ids[instance][1]->watermark = config->watermark;
#endif
    sai_state_ids[instance][1]->master_slave = config->slave_master;
    OSA_SemaCreate(&state->sem, 0);
    INT_SYS_EnableIRQ(g_saiRxIrqId[instance]);
 
    return kStatus_SAI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_DRV_TxGetDefaultSetting
 * Description   : Get default settings for sai tx module.
 *
 *END**************************************************************************/
void SAI_DRV_TxGetDefaultSetting(sai_user_config_t * config)
{
    config->bclk_source = kSaiBclkSourceMclkDiv;
    config->channel = 0;
    config->mclk_source = kSaiMclkSourceSysclk;
    config->protocol = kSaiBusI2SType;
    config->slave_master = kSaiMaster;
#if (FSL_FEATURE_SAI_FIFO_COUNT > 1)
    config->watermark = 4;
#endif
    config->sync_mode = kSaiModeAsync;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_DRV_RxGetDefaultSetting
 * Description   : Get default settings for sai rx module.
 *
 *END**************************************************************************/
void SAI_DRV_RxGetDefaultSetting(sai_user_config_t * config)
{
    config->bclk_source = kSaiBclkSourceMclkDiv;
    config->channel = 0;
    config->mclk_source = kSaiMclkSourceSysclk;
    config->protocol = kSaiBusI2SType;
    config->slave_master = kSaiMaster;
#if (FSL_FEATURE_SAI_FIFO_COUNT > 1)
    config->watermark = 4;
#endif
    config->sync_mode = kSaiModeSync;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_DRV_TxDeinit
 * Description   :Deinit the sai tx module, free the resources.
 * 
 *END**************************************************************************/
sai_status_t SAI_DRV_TxDeinit(uint32_t instance)
{
    I2S_Type * reg_base = g_saiBase[instance];
    SAI_DRV_TxSetDmaCmd(instance, false);
    SAI_DRV_TxSetIntCmd(instance, false);
    SAI_HAL_TxDisable(reg_base);
    SAI_HAL_TxSetReset(reg_base, kSaiResetTypeSoftware);
    SAI_HAL_TxClearStateFlag(reg_base, kSaiStateFlagSoftReset);
    /* Release dma channel */
    if (sai_state_ids[instance][0]->use_dma)
    {
#if defined FSL_FEATURE_EDMA_MODULE_CHANNEL
        EDMA_DRV_StopChannel(&sai_state_ids[instance][0]->edma_chn);
        EDMA_DRV_ReleaseChannel(&sai_state_ids[instance][0]->edma_chn);
#else
        DMA_DRV_FreeChannel(&sai_state_ids[instance][0]->chn);
#endif
    }
    /* Destory sem */
    OSA_SemaDestroy(&sai_state_ids[instance][0]->sem);
    sai_state_ids[instance][0] = NULL;
    /* Check if need to close the clock gate */
    if  ((sai_state_ids[instance][0] == NULL) && (sai_state_ids[instance][1] == NULL))
    {
        CLOCK_SYS_DisableSaiClock(instance);
    }
    return kStatus_SAI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_DRV_RxDeinit
 * Description   :Deinit the sai rx module, free the resources.
 * 
 *END**************************************************************************/
sai_status_t SAI_DRV_RxDeinit(uint32_t instance)
{
    I2S_Type * reg_base = g_saiBase[instance];
    SAI_DRV_RxSetDmaCmd(instance, false);
    SAI_DRV_RxSetIntCmd(instance, false);
    SAI_HAL_RxDisable(reg_base);
    SAI_HAL_RxSetReset(reg_base, kSaiResetTypeSoftware);
    SAI_HAL_RxClearStateFlag(reg_base, kSaiStateFlagSoftReset);
    /* Release dma channel */
    if (sai_state_ids[instance][1]->use_dma)
    {
#if defined FSL_FEATURE_EDMA_MODULE_CHANNEL
        EDMA_DRV_ReleaseChannel(&sai_state_ids[instance][1]->edma_chn);
#else
        DMA_DRV_FreeChannel(&sai_state_ids[instance][1]->chn);
#endif
    }
    /* Destory sem */
    OSA_SemaDestroy(&sai_state_ids[instance][1]->sem);

    sai_state_ids[instance][1] = NULL;
    /* Check if need to close the clock gate */
    if  ((sai_state_ids[instance][0] == NULL) && (sai_state_ids[instance][1] == NULL))
    {
        CLOCK_SYS_DisableSaiClock(instance);
    }
    return kStatus_SAI_Success;
}

#if (FSL_FEATURE_SAI_FIFO_COUNT > 1)
/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_DRV_TxSetWatermark
 * Description   :Set the watermark value of sai tx.
 * 
 *END**************************************************************************/
void SAI_DRV_TxSetWatermark(uint32_t instance,uint32_t watermark)
{
    I2S_Type * reg_base = g_saiBase[instance];
    SAI_HAL_TxSetWatermark(reg_base,watermark);
    sai_state_ids[instance][0]->watermark = watermark;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_DRV_RxSetWatermark
 * Description   :Set the watermark value of sai rx.
 * 
 *END**************************************************************************/
void SAI_DRV_RxSetWatermark(uint32_t instance,uint32_t watermark)
{
    I2S_Type * reg_base = g_saiBase[instance];
    SAI_HAL_RxSetWatermark(reg_base,watermark);
    sai_state_ids[instance][1]->watermark = watermark;
}
#endif

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_DRV_TxConfigDataFormat
 * Description   :Configure audio format information of tx.
 * The audio format information includes the sample rate, data length and so on.
 *END**************************************************************************/
sai_status_t SAI_DRV_TxConfigDataFormat(uint32_t instance, sai_data_format_t *format)
{
    I2S_Type * reg_base = g_saiBase[instance];
    memcpy(&sai_state_ids[instance][0]->format, format, sizeof(sai_data_format_t));
    if(sai_state_ids[instance][0]->master_slave == kSaiMaster)
    {
        uint32_t bclk = format->sample_rate * format->bits * 2;
        uint8_t divider;
        if(SAI_HAL_TxGetBclkSrc(reg_base) == 0)
        {
            divider = (CLOCK_SYS_GetBusClockFreq())/bclk;
        }
        else
        {
            divider = format->mclk/bclk;
        }
#if FSL_FEATURE_SAI_HAS_MCLKDIV_REGISTER
        uint32_t frequency = 0;
        /* Get the clock source frequency */
        uint32_t mclk_sel = SAI_HAL_GetMclkSrc(reg_base);
        frequency = CLOCK_SYS_GetSaiFreq(instance, (clock_sai_src_t)mclk_sel);
        /* Configure master clock */
        SAI_HAL_SetMclkDiv(reg_base, format->mclk, frequency);
#endif
        /* Master clock and bit clock setting */
        SAI_HAL_TxSetBclkDiv(reg_base, divider);
    }
    SAI_HAL_TxSetWordWidth(reg_base, sai_state_ids[instance][0]->protocol, format->bits);
    /* The channel number configuration */
    SAI_HAL_TxSetMonoStereo(reg_base, format->mono_stereo);

    return kStatus_SAI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_DRV_RxConfigDataFormat
 * Description   :Configure audio format information of rx.
 * The audio format information includes the sample rate, data length and so on.
 *END**************************************************************************/
sai_status_t SAI_DRV_RxConfigDataFormat(uint32_t instance, sai_data_format_t *format)
{
    I2S_Type * reg_base = g_saiBase[instance];

    memcpy(&sai_state_ids[instance][1]->format, format, sizeof(sai_data_format_t));
    if(sai_state_ids[instance][1]->master_slave == kSaiMaster)
    {
        uint32_t bclk = format->sample_rate * format->bits * 2;
        uint8_t divider;
        if(SAI_HAL_RxGetBclkSrc(reg_base) == 0)
        {
            divider = (CLOCK_SYS_GetBusClockFreq())/bclk;
        }
        else
        {
            divider = format->mclk/bclk;
        }
#if FSL_FEATURE_SAI_HAS_MCLKDIV_REGISTER
        uint32_t frequency = 0;
        /* Get the clock source frequency */
        uint32_t mclk_sel = SAI_HAL_GetMclkSrc(reg_base);
        frequency = CLOCK_SYS_GetSaiFreq(instance, (clock_sai_src_t)mclk_sel);
        /* Configure master clock */
        SAI_HAL_SetMclkDiv(reg_base, format->mclk, frequency);
#endif
        /* Master clock and bit clock setting */
        SAI_HAL_RxSetBclkDiv(reg_base, divider);
    }
    SAI_HAL_RxSetWordWidth(reg_base, sai_state_ids[instance][1]->protocol, format->bits);
    /* The channel number configuration */
    SAI_HAL_RxSetMonoStereo(reg_base, format->mono_stereo);
    return kStatus_SAI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_DRV_TxStartModule
 * Description   : Start the writing process.
 * 
 *END**************************************************************************/
void SAI_DRV_TxStartModule(uint32_t instance)
{
    I2S_Type * reg_base = g_saiBase[instance];
    /* If the sync mode is synchronous, it will need Rx enable bit clock */
    if(sai_state_ids[instance][0]->sync_mode == kSaiModeSync)
    {
        SAI_HAL_TxEnable(reg_base);
        SAI_HAL_RxEnable(reg_base);
    }
    else
    {
        SAI_HAL_TxEnable(reg_base);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_DRV_RxStartModule
 * Description   : Start the reading process.
 * 
 *END**************************************************************************/
void SAI_DRV_RxStartModule(uint32_t instance)
{
    I2S_Type * reg_base = g_saiBase[instance];
    /* If the sync mode is synchronous, it will need Tx enable bit clock */
    if(sai_state_ids[instance][1]->sync_mode == kSaiModeSync)
    {
        SAI_HAL_RxEnable(reg_base);
        SAI_HAL_TxEnable(reg_base);
    }
    else
    {
        SAI_HAL_RxEnable(reg_base);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_DRV_TxIRQHandler
 * Description   : The interrupt handle of tx FIFO request or FIFO warning.
 * The interrupt handle is used to transfer data from sai buffer to sai fifo. 
 *END**************************************************************************/
void SAI_DRV_TxIRQHandler(uint32_t instance)
{
    I2S_Type * reg_base = g_saiBase[instance];
    uint8_t data_size = 0;
    uint8_t i = 0;
    sai_data_format_t format = sai_state_ids[instance][0]->format;
    uint32_t data = 0, temp = 0;
    uint32_t len = sai_state_ids[instance][0]->len;
    uint32_t count = sai_state_ids[instance][0]->count;
    
    data_size = format.bits/8;
    if((data_size == 3) || (format.bits & 0x7))
    {
        data_size = 4;
    }

    /* Judge if FIFO error */
    if(SAI_HAL_TxGetStateFlag(reg_base, kSaiStateFlagFIFOError))
    {
        SAI_HAL_TxClearStateFlag(reg_base, kSaiStateFlagFIFOError);
    }
#if (FSL_FEATURE_SAI_FIFO_COUNT > 1)
    uint8_t j = 0;
    /* Interrupt used to transfer data. */
    if((SAI_HAL_TxGetStateFlag(reg_base, kSaiStateFlagFIFORequest)) &&
        (!sai_state_ids[instance][0]->use_dma))
    {
        uint32_t watermark = sai_state_ids[instance][0]->watermark;
        uint8_t space = FSL_FEATURE_SAI_FIFO_COUNT - watermark;
        /*Judge if the data need to transmit is less than space */
        if(space > (len -count)/data_size)
        {
            space = (len -count)/data_size;
        }
        /* If normal, copy the data from sai buffer to FIFO */
        for(i = 0; i < space; i++)
        {
            for(j = 0; j < data_size; j ++)
            {
                temp = (uint32_t)(*sai_state_ids[instance][0]->address);
                data |= (temp << (8U * j));
                sai_state_ids[instance][0]->address ++;
            }
            SAI_HAL_SendData(reg_base, sai_state_ids[instance][0]->fifo_channel, (uint32_t )data);
            sai_state_ids[instance][0]->count += data_size;
            data = 0;
        }
        /* If a block is finished, just callback */
        count = sai_state_ids[instance][0]->count;
        if(count == len)
        {
            void * callback_param = sai_state_ids[instance][0]->callback_param;
            sai_state_ids[instance][0]->count = 0;
            sai_state_ids[instance][0]->len = 0;
            if (sai_state_ids[instance][0]->callback)
            {
                (sai_state_ids[instance][0]->callback)(callback_param);
            }
            else
            {
                SAI_HAL_TxSetIntCmd(reg_base, kSaiIntrequestFIFORequest, false);
            }
        }
    }
#else
    if((SAI_HAL_TxGetStateFlag(reg_base, kSaiStateFlagFIFOWarning)) &&
        (!sai_state_ids[instance][0]->use_dma))
    {
        for(i = 0; i < data_size; i ++)
        {
            temp = (uint32_t)(*sai_state_ids[instance][0]->address);
            data |= (temp << (8U * i));
            sai_state_ids[instance][0]->address ++;
        }
        SAI_HAL_SendData(reg_base,sai_state_ids[instance][0]->fifo_channel, (uint32_t)data);
        sai_state_ids[instance][0]->count += data_size;
        count = sai_state_ids[instance][0]->count;
        if(count == len)
        {
            void * callback_param = sai_state_ids[instance][0]->callback_param;
            sai_state_ids[instance][0]->count = 0;
            sai_state_ids[instance][0]->len = 0;
            OSA_SemaPost(&sai_state_ids[instance][0]->sem);
            if (sai_state_ids[instance][0]->callback)
            {
                (sai_state_ids[instance][0]->callback)(callback_param);
            }
            else
            {
                SAI_HAL_TxSetIntCmd(reg_base, kSaiIntrequestFIFOWarning, false);
            }
        }
    }
#endif
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_DRV_RxIRQHandler
 * Description   : The interrupt handle of rx FIFO request or FIFO warning.
 * The interrupt handle is used to transfer data from sai fifo to sai buffer. 
 *END**************************************************************************/
void SAI_DRV_RxIRQHandler(uint32_t instance)
{
    I2S_Type * reg_base = g_saiBase[instance];
    uint8_t i = 0;
    uint8_t data_size = 0;
    uint32_t data = 0;
    sai_data_format_t format = sai_state_ids[instance][1]->format;
    uint32_t len = sai_state_ids[instance][1]->len;
    uint32_t count = sai_state_ids[instance][1]->count;

    data_size = format.bits/8;
    if((data_size == 3) || (format.bits & 0x7))
    {
        data_size = 4;
    }

    /* Judge if FIFO error */
    if(SAI_HAL_RxGetStateFlag(reg_base, kSaiStateFlagFIFOError))
    {
        SAI_HAL_RxClearStateFlag(reg_base, kSaiStateFlagFIFOError);    
    }
#if (FSL_FEATURE_SAI_FIFO_COUNT > 1)
    uint8_t j = 0;
    /* Interrupt used to transfer data. */
    if((SAI_HAL_RxGetStateFlag(reg_base, kSaiStateFlagFIFORequest)) &&
        (!sai_state_ids[instance][1]->use_dma))
    {
        uint8_t space = sai_state_ids[instance][1]->watermark;
        /*Judge if the data need to transmit is less than space */
        if(space > (len - count)/data_size)
        {
            space = (len -count)/data_size;
        }
        /* Read data from FIFO to the buffer */
        for (i = 0; i < space; i ++)
        {
            data = SAI_HAL_ReceiveData(reg_base, sai_state_ids[instance][1]->fifo_channel);
            for(j = 0; j < data_size; j ++)
            {
                *sai_state_ids[instance][1]->address = (data >> (8U * j)) & 0xFF;
                sai_state_ids[instance][1]->address ++;
            }
            sai_state_ids[instance][1]->count += data_size;
        }
        /* If need to callback the function */
        count = sai_state_ids[instance][1]->count;
        if (count == len)
        {
            void *callback_param = sai_state_ids[instance][1]->callback_param;
            sai_state_ids[instance][1]->count = 0;
            sai_state_ids[instance][1]->len = 0;
            if (sai_state_ids[instance][1]->callback)
            {
                (sai_state_ids[instance][1]->callback)(callback_param);
            }
            else
            {
                SAI_HAL_RxSetIntCmd(reg_base, kSaiIntrequestFIFORequest,false);
            }
        }
    }
#else
    if((SAI_HAL_RxGetStateFlag(reg_base, kSaiStateFlagFIFOWarning)) &&
        (!sai_state_ids[instance][1]->use_dma))
    {
        data = SAI_HAL_ReceiveData(reg_base, sai_state_ids[instance][1]->fifo_channel);
        for(i = 0; i < data_size; i ++)
        {
                *sai_state_ids[instance][1]->address = (data >> (8U * i)) & 0xFF;
                sai_state_ids[instance][1]->address ++;
        }
        sai_state_ids[instance][1]->count += data_size;
        count = sai_state_ids[instance][1]->count;
        if (count == len)
        {
            void *callback_param = sai_state_ids[instance][1]->callback_param;
            sai_state_ids[instance][1]->count = 0;
            sai_state_ids[instance][1]->len = 0;
            OSA_SemaPost(&sai_state_ids[instance][1]->sem);
            if (sai_state_ids[instance][1]->callback)
            {
                (sai_state_ids[instance][1]->callback)(callback_param);
            }
            else
            {
                SAI_HAL_RxSetIntCmd(reg_base, kSaiIntrequestFIFOWarning, false);
            }
        }
    }

#endif
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_DRV_TxRegisterCallback
 * Description   : The function would register the callback function to tell sai
 * driver what to do after the transfer. 
 *END**************************************************************************/
void SAI_DRV_TxRegisterCallback
(
uint32_t instance, 
sai_callback_t callback, 
void *callback_param
)
{
    sai_state_ids[instance][0]->callback = callback;
    sai_state_ids[instance][0]->callback_param = callback_param;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_DRV_RxRegisterCallback
 * Description   : The function would register the callback function to tell sai
 * driver what to do after the receive. 
 *END**************************************************************************/
void SAI_DRV_RxRegisterCallback
(
uint32_t instance, 
sai_callback_t callback, 
void *callback_param
)
{
    sai_state_ids[instance][1]->callback = callback;
    sai_state_ids[instance][1]->callback_param = callback_param;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_DRV_SendDataInt
 * Description   : The function would tell sai driver to start send a period of
 * data to sai tx fifo.
 *END**************************************************************************/
uint32_t SAI_DRV_SendDataInt(uint32_t instance, uint8_t *addr, uint32_t len)
{
    I2S_Type * base = g_saiBase[instance];
    sai_state_ids[instance][0]->len = len;
    sai_state_ids[instance][0]->address= addr;
#if FSL_FEATURE_SAI_FIFO_COUNT > 1
    SAI_HAL_TxSetIntCmd(base, kSaiIntrequestFIFOError | kSaiIntrequestFIFORequest, true);
#else
    SAI_HAL_TxSetIntCmd(base, kSaiIntrequestFIFOError | kSaiIntrequestFIFOWarning, true);
#endif
    SAI_DRV_TxStartModule(instance);
    return len;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_DRV_ReceiveData
 * Description   : The function would tell sai driver to start receive a period of
 * data from sai rx fifo.
 *END**************************************************************************/
uint32_t SAI_DRV_ReceiveDataInt(uint32_t instance, uint8_t *addr, uint32_t len)
{
    I2S_Type * base = g_saiBase[instance];
    sai_state_ids[instance][1]->len = len;
    sai_state_ids[instance][1]->address= addr;
#if FSL_FEATURE_SAI_FIFO_COUNT > 1
    SAI_HAL_RxSetIntCmd(base, kSaiIntrequestFIFOError | kSaiIntrequestFIFORequest, true);
#else
    SAI_HAL_RxSetIntCmd(base, kSaiIntrequestFIFOError | kSaiIntrequestFIFOWarning, true);
#endif
    SAI_DRV_RxStartModule(instance);
    return len;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_DRV_SendDatadma
 * Description   : The function would tell sai driver to start send a period of
 * data to sai tx fifo. This function will configure and start dma.
 *END**************************************************************************/
uint32_t SAI_DRV_SendDataDma(uint32_t instance, uint8_t *addr, uint32_t len)
{
    I2S_Type * base = g_saiBase[instance];
    uint32_t bytes = sai_state_ids[instance][0]->format.bits/8;
    uint32_t destAddr = SAI_HAL_TxGetFifoAddr(base,sai_state_ids[instance][0]->fifo_channel);
#if defined FSL_FEATURE_EDMA_MODULE_CHANNEL
    edma_chn_state_t *edma_chn = &sai_state_ids[instance][0]->edma_chn;
    edma_software_tcd_t *tcd = sai_state_ids[instance][0]->tcd;
    uint32_t bytesOnEachRequest = 0;
#if FSL_FEATURE_SAI_FIFO_COUNT > 1
        bytesOnEachRequest = bytes * sai_state_ids[instance][0]->watermark;
#else
        bytesOnEachRequest = bytes;
#endif /* FSL_FEATURE_SAI_FIFO_COUNT > 1 */
#else
    dma_channel_t *chn = &sai_state_ids[instance][0]->chn;
#endif /* FSL_FEATURE_EDMA_MODULE_CHANNEL  */
    if (!sai_state_ids[instance][0]->use_dma)
    {
        uint32_t ret;
#if defined FSL_FEATURE_EDMA_MODULE_CHANNEL
        ret = EDMA_DRV_RequestChannel(kEDMAAnyChannel,
            (dma_request_source_t)sai_state_ids[instance][0]->dma_source, edma_chn);
        if (ret == kEDMAInvalidChannel)
        {
            return kStatus_SAI_Fail;
        }
        EDMA_DRV_InstallCallback(edma_chn, SAI_DRV_EdmaCallback, 
            sai_state_ids[instance][0]);
#else
        ret = DMA_DRV_RequestChannel(kDmaAnyChannel, 
            (dma_request_source_t)sai_state_ids[instance][0]->dma_source, chn);
        if (ret == kDmaInvalidChannel)
        {
            return kStatus_SAI_Fail;
        }
        DMA_DRV_RegisterCallback(chn, SAI_DRV_DmaCallback,
            sai_state_ids[instance][0]);
#endif
        sai_state_ids[instance][0]->use_dma = true;
    }
    if (bytes == 3)
    {
        bytes = 4;
    }
    sai_state_ids[instance][0]->len = len;
    sai_state_ids[instance][0]->address = addr;
#if defined FSL_FEATURE_EDMA_MODULE_CHANNEL
     /* Configure Edma */
    EDMA_DRV_ConfigLoopTransfer(edma_chn, tcd,kEDMAMemoryToPeripheral, 
        (uint32_t)addr, destAddr, bytes, bytesOnEachRequest, len, 1);
    EDMA_DRV_StartChannel(&sai_state_ids[instance][0]->edma_chn);   
#else
    /* Configure Dma */
    DMA_DRV_ConfigTransfer(chn, kDmaMemoryToPeripheral,
        bytes, (uint32_t)addr, destAddr, len);
    DMA_DRV_StartChannel(&sai_state_ids[instance][0]->chn);
#endif
    /* Enable DMA request */
    SAI_HAL_TxSetIntCmd(base, kSaiIntrequestFIFOError, true);
#if FSL_FEATURE_SAI_FIFO_COUNT > 1
    SAI_HAL_TxSetDmaCmd(base, kSaiDmaReqFIFORequest, true);
#else
    SAI_HAL_TxSetDmaCmd(base, kSaiDmaReqFIFOWarning, true);
#endif
    SAI_DRV_TxStartModule(instance);
    return len;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_DRV_ReceiveDataDma
 * Description   : The function would tell sai driver to start receive a period of
 * data from sai rx fifo. This function would also start dma.
 *END**************************************************************************/
uint32_t SAI_DRV_ReceiveDataDma(uint32_t instance, uint8_t *addr, uint32_t len)
{
    I2S_Type * base = g_saiBase[instance];
    uint32_t bytes = sai_state_ids[instance][1]->format.bits/8;
    uint32_t srcAddr = SAI_HAL_RxGetFifoAddr(base,sai_state_ids[instance][1]->fifo_channel);
#if defined FSL_FEATURE_EDMA_MODULE_CHANNEL
    edma_chn_state_t *edma_chn = &sai_state_ids[instance][1]->edma_chn;
    edma_software_tcd_t *tcd = sai_state_ids[instance][1]->tcd;
    uint32_t bytesOnEachRequest = 0;
#if FSL_FEATURE_SAI_FIFO_COUNT > 1
            bytesOnEachRequest = bytes * sai_state_ids[instance][1]->watermark;
#else
            bytesOnEachRequest = bytes;
#endif /* FSL_FEATURE_SAI_FIFO_COUNT > 1 */
#else
    dma_channel_t *chn = &sai_state_ids[instance][1]->chn;
#endif /* FSL_FEATURE_EDMA_MODULE_CHANNEL */
    if (!sai_state_ids[instance][1]->use_dma)
    {
        uint32_t ret;
#if defined FSL_FEATURE_EDMA_MODULE_CHANNEL
        ret = EDMA_DRV_RequestChannel(kEDMAAnyChannel,
            (dma_request_source_t)sai_state_ids[instance][1]->dma_source, edma_chn);
        if (ret == kEDMAInvalidChannel)
        {
            return kStatus_SAI_Fail;
        }
        EDMA_DRV_InstallCallback(edma_chn, SAI_DRV_EdmaCallback, 
            sai_state_ids[instance][1]);
#else
        ret = DMA_DRV_RequestChannel(kDmaAnyChannel, 
            (dma_request_source_t)sai_state_ids[instance][1]->dma_source, chn);
        if (ret == kDmaInvalidChannel)
        {
            return kStatus_SAI_Fail;
        }
        DMA_DRV_RegisterCallback(chn, SAI_DRV_DmaCallback,
            sai_state_ids[instance][1]);
#endif
        sai_state_ids[instance][1]->use_dma = true;
    }
    if (bytes == 3)
    {
        bytes = 4;
    }
    sai_state_ids[instance][1]->len = len;
    sai_state_ids[instance][1]->address = addr;
#if defined FSL_FEATURE_EDMA_MODULE_CHANNEL
    /* Configure Edma */
    EDMA_DRV_ConfigLoopTransfer(edma_chn, tcd, kEDMAPeripheralToMemory,
        srcAddr, (uint32_t)addr, bytes, bytesOnEachRequest, len, 1);
    EDMA_DRV_StartChannel(&sai_state_ids[instance][1]->edma_chn);
#else
    /* Configure Dma */
    DMA_DRV_ConfigTransfer(chn, kDmaPeripheralToMemory,
        bytes, srcAddr, (uint32_t)addr, len);
    DMA_DRV_StartChannel(&sai_state_ids[instance][1]->chn);
#endif
    /* Enable DMA request */
    SAI_HAL_RxSetIntCmd(base, kSaiIntrequestFIFOError, true);
#if FSL_FEATURE_SAI_FIFO_COUNT > 1
    SAI_HAL_RxSetDmaCmd(base, kSaiDmaReqFIFORequest, true);
#else
    SAI_HAL_RxSetDmaCmd(base, kSaiDmaReqFIFOWarning, true);
#endif
    SAI_DRV_RxStartModule(instance);
    return len;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_DRV_TxStopModule
 * Description   : The function stops transfer of tx, including closing interrupt
 request or dma request.
 *END**************************************************************************/
void SAI_DRV_TxStopModule(uint32_t instance)
{
    I2S_Type * reg_base = g_saiBase[instance];
#if (FSL_FEATURE_SAI_FIFO_COUNT > 1)
    SAI_HAL_TxSetIntCmd(reg_base,kSaiIntrequestFIFORequest,false);
    SAI_HAL_TxSetDmaCmd(reg_base,kSaiDmaReqFIFORequest, false);
#else
    SAI_HAL_TxSetIntCmd(reg_base,kSaiIntrequestFIFOWarning,false);
    SAI_HAL_TxSetDmaCmd(reg_base,kSaiDmaReqFIFOWarning, false);
#endif
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_DRV_RxStopModule
 * Description   : The function stops receiving, including closing interrupt
 request or dma request.
 *END**************************************************************************/
void SAI_DRV_RxStopModule(uint32_t instance)
{
    I2S_Type * reg_base = g_saiBase[instance];
#if (FSL_FEATURE_SAI_FIFO_COUNT > 1)
    SAI_HAL_RxSetIntCmd(reg_base,kSaiIntrequestFIFORequest,false);
    SAI_HAL_RxSetDmaCmd(reg_base,kSaiDmaReqFIFORequest, false);
#else
    SAI_HAL_RxSetIntCmd(reg_base,kSaiIntrequestFIFOWarning,false);
    SAI_HAL_RxSetDmaCmd(reg_base,kSaiDmaReqFIFOWarning, false);
#endif
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_DRV_TxSetIntCmd
 * Description   : The function enables interrupt request source for tx.
 *END**************************************************************************/
void SAI_DRV_TxSetIntCmd(uint32_t instance, bool enable)
{
    I2S_Type * reg_base = g_saiBase[instance];
#if (FSL_FEATURE_SAI_FIFO_COUNT > 1)
    SAI_HAL_TxSetIntCmd(reg_base,kSaiIntrequestFIFORequest,enable);
#else
    SAI_HAL_TxSetIntCmd(reg_base,kSaiIntrequestFIFOWarning,enable);
#endif
    SAI_HAL_TxSetIntCmd(reg_base, kSaiIntrequestFIFOError, enable);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_DRV_RxSetIntCmd
 * Description   : The function enables interrupt request source for rx.
 *END**************************************************************************/
void SAI_DRV_RxSetIntCmd(uint32_t instance, bool enable)
{
    I2S_Type * reg_base = g_saiBase[instance];
#if (FSL_FEATURE_SAI_FIFO_COUNT > 1)
    SAI_HAL_RxSetIntCmd(reg_base,kSaiIntrequestFIFORequest,enable);
#else
    SAI_HAL_RxSetIntCmd(reg_base,kSaiIntrequestFIFOWarning,enable);
#endif
    SAI_HAL_RxSetIntCmd(reg_base, kSaiIntrequestFIFOError,enable);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_DRV_TxSetDmaCmd
 * Description   : The function enables dma request source for tx.
 *END**************************************************************************/
void SAI_DRV_TxSetDmaCmd(uint32_t instance,  bool enable)
{
    I2S_Type * reg_base = g_saiBase[instance];
#if (FSL_FEATURE_SAI_FIFO_COUNT > 1)
    SAI_HAL_TxSetDmaCmd(reg_base, kSaiDmaReqFIFORequest,enable);
#else
    SAI_HAL_TxSetDmaCmd(reg_base,kSaiIntrequestFIFOWarning,enable);
#endif
    SAI_HAL_TxSetIntCmd(reg_base, kSaiIntrequestFIFOError,enable);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_DRV_RxSetDmaCmd
 * Description   : The function enables dma request source for rx.
 *END**************************************************************************/
void SAI_DRV_RxSetDmaCmd(uint32_t instance, bool enable)
{
    I2S_Type * reg_base = g_saiBase[instance];
#if (FSL_FEATURE_SAI_FIFO_COUNT > 1)
    SAI_HAL_RxSetDmaCmd(reg_base, kSaiDmaReqFIFORequest,enable);
#else
    SAI_HAL_RxSetDmaCmd(reg_base,kSaiIntrequestFIFOWarning,enable);
#endif
    SAI_HAL_RxSetIntCmd(reg_base, kSaiIntrequestFIFOError,enable);    
}

#if defined FSL_FEATURE_EDMA_MODULE_CHANNEL
/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_DRV_EdmaCallback
 * Description   : Callback function registered to edma, it will be called at 
 * the end of an edma transfer, users can register callback in this function.
 *END**************************************************************************/
void SAI_DRV_EdmaCallback(void *param, edma_chn_status_t status)
{
    sai_state_t *state = (sai_state_t *)param;
    OSA_SemaPost(&state->sem);
    if (state->callback)
    {
        (state->callback)(state->callback_param);
    }
}
#else
/*FUNCTION**********************************************************************
 *
 * Function Name : SAI_DRV_DmaCallback
 * Description   : Callback function registered to edma, it will be called at 
 * the end of a dma transfer, users can register callback in this function.
 *END**************************************************************************/
void SAI_DRV_DmaCallback(void *param, dma_channel_status_t status)
{
    sai_state_t *state = (sai_state_t *)param;
    OSA_SemaPost(&state->sem);
    if (state->callback)
    {
        (state->callback)(state->callback_param);
    }
}
#endif

#endif

/*******************************************************************************
 * EOF

 ******************************************************************************/
