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

 #include "fsl_flexio_i2s_driver.h"
 #include "fsl_clock_manager.h"
#if FSL_FEATURE_SOC_FLEXIO_COUNT


void FLEXIO_I2S_DRV_TxIrq(void *param);
void FLEXIO_I2S_DRV_RxIrq(void *param);

#if defined FSL_FEATURE_EDMA_MODULE_CHANNEL
void FLEXIO_I2S_DRV_EdmaTxCallback(void *param, edma_chn_status_t status);
void FLEXIO_I2S_DRV_EdmaRxCallback(void *param, edma_chn_status_t status);
#else
void FLEXIO_I2S_DRV_DmaTxCallback(void *param, dma_channel_status_t status);
void FLEXIO_I2S_DRV_DmaRxCallback(void *param, dma_channel_status_t status);
#endif
 

 /*FUNCTION**********************************************************************
  *
  * Function Name : FLEXIO_I2S_DRV_Init
  * Description   : Initialize flexio I2S state structure.
  * This functionconfigure flexio and initialize the state handler.
  *END**************************************************************************/
flexio_i2s_status_t FLEXIO_I2S_DRV_Init(uint32_t instance, flexio_i2s_handler_t *handler, 
        const flexio_i2s_config_t * userConfig)
{
    if ((handler == NULL) || (userConfig == NULL))
    {
        return kStatus_FlexioI2S_InvalidParameter;
    }
    FLEXIO_Type * base = g_flexioBase[instance];
    handler->device.flexioBase = base;
    handler->device.txPinIdx = userConfig->txPinIdx;
    handler->device.rxPinIdx = userConfig->rxPinIdx;
    handler->device.sckPinIdx = userConfig->sckPinIdx;
    handler->device.wsPinIdx = userConfig->wsPinIdx;
    handler->device.shifterIdx[0] = userConfig->shifterIdx[0];
    handler->device.shifterIdx[1] = userConfig->shifterIdx[1];
    handler->device.timerIdx[0] = userConfig->timerIdx[0];
    handler->device.timerIdx[1] = userConfig->timerIdx[1];
    handler->sample_rate = userConfig->sample_rate;
    handler->bit_depth = userConfig->data_depth;
    handler->baseSource = userConfig->baseSource;
    /* Initialize the statement of handler */
    handler->tx_buffer = NULL;
    handler->rx_buffer = NULL;
    handler->tx_length = 0;
    handler->rx_length = 0;
    handler->tx_finished_bytes = 0;
    handler->rx_finished_bytes = 0;
    handler->tx_active = false;
    handler->rx_active = false;
    OSA_SemaCreate(&handler->tx_sem, 0);
    OSA_SemaCreate(&handler->rx_sem, 0);
    handler->tx_use_dma = false;
    handler->rx_use_dma = false;
    /* Configure flexio */
    if (userConfig->master_slave == kFlexioI2SMaster)
    {
        flexio_i2s_master_config_t master;
        master.flexioBusClk = CLOCK_SYS_GetFlexioFreq(instance);
        master.bitClk = userConfig->sample_rate * 32 * 2;
        master.bitCount = userConfig->data_depth;
        FLEXIO_I2S_HAL_Configure_Master(&handler->device, &master);
    }
    else
    {
        flexio_i2s_slave_config_t slave;
        slave.bitCount = userConfig->data_depth;
        FLEXIO_I2S_HAL_Configure_Slave(&handler->device, &slave);
    }
    FLEXIO_DRV_RegisterCallback(instance,userConfig->shifterIdx[0],
        FLEXIO_I2S_DRV_TxIrq, handler);
    FLEXIO_DRV_RegisterCallback(instance,userConfig->shifterIdx[1],
        FLEXIO_I2S_DRV_RxIrq, handler);
    return kStatus_FlexioI2S_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_I2S_DRV_Deinit
 * Description   : Deinit flexio I2S.
 * This function clear i2s state.
 *END**************************************************************************/
flexio_i2s_status_t FLEXIO_I2S_DRV_Deinit(flexio_i2s_handler_t *handler)
{
    /* Release dma channel */
    if (handler->tx_use_dma)
    {
#if defined FSL_FEATURE_EDMA_MODULE_CHANNEL
        EDMA_DRV_ReleaseChannel(&handler->tx_edma_state);
#else
        DMA_DRV_FreeChannel(&handler->tx_dma_chn);
#endif
    }
    if (handler->rx_use_dma)
    {
#if defined FSL_FEATURE_EDMA_MODULE_CHANNEL
        EDMA_DRV_ReleaseChannel(&handler->rx_edma_state);
#else
        DMA_DRV_FreeChannel(&handler->rx_dma_chn);
#endif
    }
    memset(&handler, 0, sizeof(flexio_i2s_handler_t));
    return kStatus_FlexioI2S_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_I2S_DRV_TxStart
 * Description   : Start transfer data in tx port.
 * This function enables tx interrupt request or dma request.
 *END**************************************************************************/
flexio_i2s_status_t FLEXIO_I2S_DRV_TxStart(flexio_i2s_handler_t *handler)
{
    handler->tx_active = true;
    FLEXIO_I2S_HAL_SetTxErrIntCmd(&handler->device, true);
    if (handler->tx_use_dma)
    {
        FLEXIO_I2S_HAL_SetTxDmaCmd(&handler->device, true);
    }
    else
    {
        FLEXIO_I2S_HAL_SetTxBufferEmptyIntCmd(&handler->device, true);
    }
    return kStatus_FlexioI2S_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_I2S_DRV_RxStart
 * Description   : Start transfer data in rx port.
 * This function enables rx interrupt request or dma request.
 *END**************************************************************************/
flexio_i2s_status_t FLEXIO_I2S_DRV_RxStart(flexio_i2s_handler_t *handler)
{
    handler->rx_active = true;
    FLEXIO_I2S_HAL_SetRxErrIntCmd(&handler->device, true);
    if (handler->rx_use_dma)
    {
        FLEXIO_I2S_HAL_SetRxDmaCmd(&handler->device, true);
    }
    else
    {
        FLEXIO_I2S_HAL_SetRxBufferFullIntCmd(&handler->device, true);
    }
    return kStatus_FlexioI2S_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_I2S_DRV_TxStop
 * Description   : Stop transfer data in tx port.
 * This function disables tx interrupt request or dma request.
 *END**************************************************************************/
flexio_i2s_status_t FLEXIO_I2S_DRV_TxStop(flexio_i2s_handler_t *handler)
{
    handler->tx_active = false;
    FLEXIO_I2S_HAL_SetTxBufferEmptyIntCmd(&handler->device, false);
    FLEXIO_I2S_HAL_SetTxErrIntCmd(&handler->device, false);
    if (handler->tx_use_dma)
    {
        FLEXIO_I2S_HAL_SetTxDmaCmd(&handler->device, false);
    }
    return kStatus_FlexioI2S_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_I2S_DRV_RxStop
 * Description   : Stop transfer data in rx port.
 * This function disables rx interrupt request or dma request.
 *END**************************************************************************/
flexio_i2s_status_t FLEXIO_I2S_DRV_RxStop(flexio_i2s_handler_t *handler)
{
    handler->rx_active = false;
    FLEXIO_I2S_HAL_SetRxBufferFullIntCmd(&handler->device, false);
    FLEXIO_I2S_HAL_SetRxErrIntCmd(&handler->device, false);
    if (handler->rx_use_dma)
    {
        FLEXIO_I2S_HAL_SetRxDmaCmd(&handler->device, false);
    }
    return kStatus_FlexioI2S_Success; 
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_I2S_DRV_SendDataInt
 * Description   : Send a period of data using interrupt way.
 * This function is an async function.
 *END**************************************************************************/
flexio_i2s_status_t FLEXIO_I2S_DRV_SendDataInt(flexio_i2s_handler_t *handler, uint8_t *addr, uint32_t len)
{
    if ((handler == NULL) || (addr == NULL) || (len == 0))
    {
        return kStatus_FlexioI2S_InvalidParameter;
    }
    handler->tx_length = len;
    handler->tx_buffer = addr;
    handler->tx_finished_bytes = 0;
    FLEXIO_I2S_DRV_TxStart(handler);
    return kStatus_FlexioI2S_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_I2S_DRV_ReceiveDataInt
 * Description   : Receive a period of data using interrupt way.
 * This function is an async function.
 *END**************************************************************************/
flexio_i2s_status_t FLEXIO_I2S_DRV_ReceiveDataInt(flexio_i2s_handler_t *handler, uint8_t *addr, uint32_t len)
{
    if ((handler == NULL) || (addr == NULL) || (len == 0))
    {
        return kStatus_FlexioI2S_InvalidParameter;
    }
    handler->rx_length = len;
    handler->rx_buffer = addr;
    handler->rx_finished_bytes = 0;
    FLEXIO_I2S_DRV_RxStart(handler);
    return kStatus_FlexioI2S_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_I2S_DRV_SendDataDma
 * Description   : Send a period of data using DMA way.
 * This function is an async function.
 *END**************************************************************************/
flexio_i2s_status_t FLEXIO_I2S_DRV_SendDataDma(flexio_i2s_handler_t *handler, uint8_t *addr, uint32_t len)
{
    if ((handler == NULL) || (addr == NULL) || (len == 0))
    {
        return kStatus_FlexioI2S_InvalidParameter;
    }
    /* Have not configure DMA. */
    if (!handler->tx_use_dma)
    {
        uint32_t ret;
        /* Request channel for Tx DMA */
        dma_request_source_t baseSource=handler->baseSource;
        dma_request_source_t source = (dma_request_source_t)((uint32_t)baseSource + handler->device.shifterIdx[0]);
#if defined FSL_FEATURE_EDMA_MODULE_CHANNEL
        ret = EDMA_DRV_RequestChannel(kEDMAAnyChannel, source, &handler->tx_edma_state);
        if (ret == kEDMAInvalidChannel)
        {
            return kStatus_FlexioI2S_Fail;
        }
        EDMA_DRV_InstallCallback(&handler->tx_edma_state, FLEXIO_I2S_DRV_EdmaTxCallback, handler);
#else
        ret = DMA_DRV_RequestChannel(kDmaAnyChannel, source, &handler->tx_dma_chn);
        if (ret == kDmaInvalidChannel)
        {
            return kStatus_FlexioI2S_Fail;
        }
        DMA_DRV_RegisterCallback(&handler->tx_dma_chn, FLEXIO_I2S_DRV_DmaTxCallback, handler);
#endif
        handler->tx_use_dma = true;
    }
    handler->tx_buffer = addr;
    handler->tx_length = len;
    /* Configure DMA module */
    uint32_t  destAddr = FLEXIO_I2S_HAL_GetTxBufferAddr(&handler->device) + 
           (4 - handler->bit_depth/8);
#if defined FSL_FEATURE_EDMA_MODULE_CHANNEL
    EDMA_DRV_ConfigLoopTransfer(&handler->tx_edma_state, handler->tx_edma_tcd,
        kEDMAMemoryToPeripheral, (uint32_t)addr, destAddr, handler->bit_depth/8, handler->bit_depth/8,
        len, 1);
    EDMA_DRV_StartChannel(&handler->tx_edma_state);
#else
    DMA_DRV_ConfigTransfer(&handler->tx_dma_chn,kDmaMemoryToPeripheral, 
           handler->bit_depth/8, (uint32_t)addr, destAddr, len);
    DMA_DRV_StartChannel(&handler->tx_dma_chn);
#endif
    FLEXIO_I2S_DRV_TxStart(handler);
    return kStatus_FlexioI2S_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_I2S_DRV_ReceiveDataDma
 * Description   : Receive a period of data using interrupt way.
 * This function is an async function.
 *END**************************************************************************/
flexio_i2s_status_t FLEXIO_I2S_DRV_ReceiveDataDma(flexio_i2s_handler_t *handler, uint8_t *addr, uint32_t len)
{
    if ((handler == NULL) || (addr == NULL) || (len == 0))
    {
        return kStatus_FlexioI2S_InvalidParameter;
    }
    if (!handler->rx_use_dma)
    {
        uint32_t ret;
        /* Request channel for Rx DMA */
        dma_request_source_t baseSource= handler->baseSource;
        dma_request_source_t source = (dma_request_source_t)((uint32_t)baseSource + handler->device.shifterIdx[1]);
#if defined FSL_FEATURE_EDMA_MODULE_CHANNEL
        ret = EDMA_DRV_RequestChannel(kEDMAAnyChannel, source, &handler->rx_edma_state);
        if (ret == kEDMAInvalidChannel)
        {
            return kStatus_FlexioI2S_Fail;
        }
        EDMA_DRV_InstallCallback(&handler->rx_edma_state, FLEXIO_I2S_DRV_EdmaRxCallback, handler);
#else
        ret = DMA_DRV_RequestChannel(kDmaAnyChannel, source, &handler->rx_dma_chn);
        if (ret == kDmaInvalidChannel)
        {
            return kStatus_FlexioI2S_Fail;
        }
        DMA_DRV_RegisterCallback(&handler->rx_dma_chn, FLEXIO_I2S_DRV_DmaRxCallback, handler);
#endif
        handler->rx_use_dma = true;
    }
    handler->rx_buffer = addr;
    handler->rx_length = len;
    /* Configure DMA module */
    uint32_t srcAddr = FLEXIO_I2S_HAL_GetRxBufferAddr(&handler->device) + 
             (4 - handler->bit_depth/8);
#if defined FSL_FEATURE_EDMA_MODULE_CHANNEL
    EDMA_DRV_ConfigLoopTransfer(&handler->rx_edma_state, handler->rx_edma_tcd,
        kEDMAPeripheralToMemory, srcAddr, (uint32_t)addr, handler->bit_depth/8, handler->bit_depth/8,
        len, 1);
    EDMA_DRV_StartChannel(&handler->rx_edma_state);
#else
    DMA_DRV_ConfigTransfer(&handler->rx_dma_chn,kDmaPeripheralToMemory, 
           handler->bit_depth/8, srcAddr, (uint32_t)addr, len);
    DMA_DRV_StartChannel(&handler->rx_dma_chn);
#endif
    FLEXIO_I2S_DRV_RxStart(handler);
    return kStatus_FlexioI2S_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_I2S_DRV_TxIrq
 * Description   : IRQ handler for tx.
 * This function sends data and also handle error flag.
 *END**************************************************************************/
void FLEXIO_I2S_DRV_TxIrq(void * param)
{
    flexio_i2s_handler_t * handler = (flexio_i2s_handler_t *)param;
    uint32_t bytes = handler->bit_depth/8;
    uint8_t *addr = handler->tx_buffer + handler->tx_finished_bytes;
    uint32_t data = 0;
    uint32_t i = 0;
    /* Clear the error flag. */
    if (FLEXIO_I2S_HAL_GetTxErrFlag(&handler->device))
    {
        FLEXIO_I2S_HAL_ClearTxErrFlag(&handler->device);
    }
    /* If need to transfer data using ISR. */
    if ((FLEXIO_I2S_HAL_GetTxBufferEmptyIntCmd(&handler->device)) &&
        (FLEXIO_I2S_HAL_GetTxBufferEmptyFlag(&handler->device)))
    {
        for (i = 0; i < bytes; i ++)
        {
            data |= (uint32_t)(*addr) << (i * 8U);
            addr ++;
            handler->tx_finished_bytes ++;
        }
        data <<= (32 - handler->bit_depth); 
        FLEXIO_I2S_HAL_PutData(&handler->device, data);
        /* If need to callback */
        if (handler->tx_finished_bytes >= handler->tx_length)
        {
            /* If there is callback */
            if (handler->tx_callback)
            {
                (handler->tx_callback)(handler->tx_callback_param);
            }
            else
            {
                /* If no callback, just close */
                OSA_SemaPost(&handler->tx_sem);
                FLEXIO_I2S_DRV_TxStop(handler);
            }
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_I2S_DRV_RxIrq
 * Description   : IRQ handler for rx.
 * This function sends data and also handle error flag.
 *END**************************************************************************/
void FLEXIO_I2S_DRV_RxIrq(void * param)
{
    flexio_i2s_handler_t * handler = (flexio_i2s_handler_t *)param;
    uint32_t bytes = handler->bit_depth/8;
    uint8_t *addr = handler->rx_buffer + handler->rx_finished_bytes;
    uint32_t data;
    uint32_t i = 0;
    /* Clear error flag */
    if (FLEXIO_I2S_HAL_GetRxErrFlag(&handler->device))
    {
        FLEXIO_I2S_HAL_ClearRxErrFlag(&handler->device);
    }
    /* If using ISR to transfer data. */
    if ((FLEXIO_I2S_HAL_GetRxBufferFullIntCmd(&handler->device)) &&
        (FLEXIO_I2S_HAL_GetRxBufferFullFlag(&handler->device)))
    {
        data = FLEXIO_I2S_HAL_GetData(&handler->device);
        for (i = 0; i < bytes; i ++)
        {
            *addr = (data >> (8 * i)) & 0xFFU;
            addr ++;
            handler->rx_finished_bytes ++;
        }
        /* If finished */
        if (handler->rx_finished_bytes >= handler->rx_length)
        {
            if (handler->rx_callback)
            {
                (handler->rx_callback)(handler->rx_callback_param);
            }
            else
            {
                OSA_SemaPost(&handler->rx_sem);
                FLEXIO_I2S_DRV_RxStop(handler);
            }
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_I2S_DRV_TxInstallCallback
 * Description   : Install callback function for finished sending data.
 * This function would be called while finished sending data, both can be used
 * in interrupt way and also dma way.
 *END**************************************************************************/
void FLEXIO_I2S_DRV_TxInstallCallback(flexio_i2s_handler_t *handler, i2s_callback callback,
     void *param)
{
    handler->tx_callback = callback;
    handler->tx_callback_param = param;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_I2S_DRV_RxInstallCallback
 * Description   : Install callback function for finished receiving data.
 * This function would be called while finished receiving data, both can be used
 * in interrupt way and also dma way.
 *END**************************************************************************/
void FLEXIO_I2S_DRV_RxInstallCallback(flexio_i2s_handler_t *handler, i2s_callback callback,
    void *param)
{
    handler->rx_callback = callback;
    handler->rx_callback_param = param;
}

#if defined FSL_FEATURE_EDMA_MODULE_CHANNEL
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_I2S_DRV_EdmaTaRxCallback
 * Description   : Default callback function for edma finished sending data.
 * This function would only post semaphore and call callback function installed
 * by users if there is.
 *END**************************************************************************/
void FLEXIO_I2S_DRV_EdmaTxCallback(void *param, edma_chn_status_t status)
{
    flexio_i2s_handler_t *handler = (flexio_i2s_handler_t *)param;
    OSA_SemaPost(&handler->tx_sem);
    if (handler->tx_callback)
    {
        (handler->tx_callback)(handler->tx_callback_param);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_I2S_DRV_EdmaRxCallback
 * Description   : Default callback function for edma finished receiving data.
 * This function would only post semaphore and call callback function installed
 * by users if there is.
 *END**************************************************************************/
void FLEXIO_I2S_DRV_EdmaRxCallback(void *param, edma_chn_status_t status)
{
    flexio_i2s_handler_t *handler = (flexio_i2s_handler_t *)param;
    OSA_SemaPost(&handler->rx_sem);
    if (handler->rx_callback)
    {
        (handler->rx_callback)(handler->rx_callback_param);
    }
}
#else
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_I2S_DRV_DmaTaRxCallback
 * Description   : Default callback function for dma finished sending data.
 * This function would only post semaphore and call callback function installed
 * by users if there is.
 *END**************************************************************************/
void FLEXIO_I2S_DRV_DmaTxCallback(void *param, dma_channel_status_t status)
{
    flexio_i2s_handler_t *handler = (flexio_i2s_handler_t *)param;
    OSA_SemaPost(&handler->tx_sem);
    FLEXIO_I2S_DRV_TxStop(handler);
    if (handler->tx_callback)
    {
        (handler->tx_callback)(handler->tx_callback_param);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_I2S_DRV_DmaRxCallback
 * Description   : Default callback function for dma finished receiving data.
 * This function would only post semaphore and call callback function installed
 * by users if there is.
 *END**************************************************************************/
void FLEXIO_I2S_DRV_DmaRxCallback(void *param, dma_channel_status_t status)
{
    flexio_i2s_handler_t *handler = (flexio_i2s_handler_t *)param;
    OSA_SemaPost(&handler->rx_sem);
    FLEXIO_I2S_DRV_RxStop(handler);
    if (handler->tx_callback)
    {
        (handler->rx_callback)(handler->rx_callback_param);
    }
}
#endif
#endif

