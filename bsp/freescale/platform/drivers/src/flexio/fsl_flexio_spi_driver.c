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
 
#include <string.h>
#include "fsl_flexio_spi_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"
/*******************************************************************************
 * Private Functions
 ******************************************************************************/
static flexio_spi_status_t FLEXIO_SPI_DRV_TxConfigDMA(flexio_spi_state_t *spiState);
static flexio_spi_status_t FLEXIO_SPI_DRV_RxConfigDMA(flexio_spi_state_t *spiState);
static flexio_spi_status_t FLEXIO_SPI_DRV_StartSendData(flexio_spi_state_t *spiState,
                                            const uint8_t * txBuff,
                                            uint32_t txSize);
static flexio_spi_status_t FLEXIO_SPI_DRV_StartReceiveData(flexio_spi_state_t *spiState,
                                               uint8_t * rxBuff,
                                               uint32_t rxSize);
static flexio_spi_status_t FLEXIO_SPI_DRV_StartTransferData(flexio_spi_state_t *spiState,
                                               const uint8_t * txBuff, uint8_t * rxBuff,
                                               uint32_t xSize);
static void FLEXIO_SPI_DRV_CompleteSendData(flexio_spi_state_t *spiState);
static void FLEXIO_SPI_DRV_CompleteReceiveData(flexio_spi_state_t *spiState);
static void FLEXIO_SPI_DRV_CompleteTransferData(flexio_spi_state_t *spiState);
#if defined FSL_FEATURE_EDMA_MODULE_CHANNEL
static void FLEXIO_SPI_DRV_EdmaTxCallback(void *param, edma_chn_status_t status);
static void FLEXIO_SPI_DRV_EdmaRxCallback(void *param, edma_chn_status_t status);
#else
static void FLEXIO_SPI_DRV_DmaTxCallback(void *param, dma_channel_status_t status);
static void FLEXIO_SPI_DRV_DmaRxCallback(void *param, dma_channel_status_t status);
#endif
/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_Init
 * Description   : Initialize a SPI device for operation.
 * This function will initialize the run-time state structure to keep track of
 * the on-going transfers,initialize the module to user defined settings and 
 * default settings, configures underlying flexio Pin,shifter and timer.
 * The following is an example of how to set up the flexio_spi_state_t and the
 * flexio_spi_userconfig_t parameters and how to call the FLEXIO_SPI_DRV_Init function
 * by passing in these parameters:
 *    flexio_spi_state_t spiState;
      flexio_spi_userconif_t spiConfig;
      spiConfig.spiMode = kFlexIOSpiMaster;
      spiConfig.baudRate = 100000;
      spiConfig.clkPhase = kFlexIOSpiClockPhase_FirstEdge;
      spiConfig.dataSize = kFlexIOSpi8BitMode;
      spiConfig.spiHwConfig.sdoPinIdx = 0;
      spiConfig.spiHwConfig.sdiPinIdx = 1;
      spiConfig.spiHwConfig.sclkPinIdx = 2;
      spiConfig.spiHwConfig.csnPinIdx = 3;
      spiConfig.spiHwConfig.shifterIdx = {0,1};
      spiConfig.spiHwConfig.timerIdx = {0,1};
 *    FLEXIO_SPI_DRV_Init(instance, &spiState, &spiConfig);
 *
 *END**************************************************************************/
flexio_spi_status_t FLEXIO_SPI_DRV_Init(uint32_t instance, flexio_spi_state_t *spiState, 
                                        const flexio_spi_userconfig_t *spiConfig)
{
    if((spiState == NULL)||(spiConfig == NULL))
    {
        return kStatus_FlexIO_SPI_InvalidParam;
    }
    FLEXIO_Type* base = g_flexioBase[instance];
    /*Reset the spiState structure*/
    memset(spiState,0,sizeof(*spiState));
    /*Create semaphore for txIrq, rxIrq and xIrq*/
    OSA_SemaCreate(&spiState->txIrqSync,0);
    OSA_SemaCreate(&spiState->rxIrqSync,0);
    OSA_SemaCreate(&spiState->xIrqSync,0);
    /*Init FlexIO SPI resource*/
    spiState->spiDev.flexioBase = base;
    spiState->spiDev.txPinIdx = spiConfig->spiHwConfig.sdoPinIdx;
    spiState->spiDev.rxPinIdx = spiConfig->spiHwConfig.sdiPinIdx;
    spiState->spiDev.sclkPinIdx = spiConfig->spiHwConfig.sclkPinIdx;
    spiState->spiDev.csnPinIdx =  spiConfig->spiHwConfig.csnPinIdx;
    spiState->spiDev.shifterIdx[0] = spiConfig->spiHwConfig.shifterIdx[0];
    spiState->spiDev.shifterIdx[1] = spiConfig->spiHwConfig.shifterIdx[1];
    spiState->spiDev.timerIdx[0] = spiConfig->spiHwConfig.timerIdx[0];
    spiState->spiDev.timerIdx[1] = spiConfig->spiHwConfig.timerIdx[1];
    spiState->mode = spiConfig->spiMode;
    spiState->dataSize = spiConfig->dataSize;
    spiState->bitDirection = spiConfig->bitDirection;
    if(spiConfig->spiMode == kFlexIOSpiMaster)
    {
        flexio_spi_master_config_t masterConfig;
        /*Get FlexIO clock frequency for baudrate calculation*/
        masterConfig.flexioBusClk = CLOCK_SYS_GetFlexioFreq(instance);
        masterConfig.baudrate = spiConfig->baudRate;
        masterConfig.bitCount = spiConfig->dataSize;
        if(spiConfig->clkPhase == 0)
        {
            masterConfig.cphaOneEnable = false;
        }
        else
        {
            masterConfig.cphaOneEnable = true;
        }
        FLEXIO_SPI_HAL_ConfigMaster(&(spiState->spiDev),&masterConfig);
    }
    else if(spiConfig->spiMode == kFlexIOSpiSlave)
    {
        flexio_spi_slave_config_t slaveConfig;
        slaveConfig.bitCount = spiConfig->dataSize;
        if(spiConfig->clkPhase == 0)
        {
            slaveConfig.cphaOneEnable = false;
        }
        else
        {
            slaveConfig.cphaOneEnable = true;
        }
        FLEXIO_SPI_HAL_ConfigSlave(&(spiState->spiDev),&slaveConfig);
    }
    FLEXIO_DRV_RegisterCallback(instance,spiState->spiDev.shifterIdx[0],
                        FLEXIO_SPI_DRV_TX_IRQHandler,(void *)(spiState));
    FLEXIO_DRV_RegisterCallback(instance,spiState->spiDev.shifterIdx[1],
                        FLEXIO_SPI_DRV_RX_IRQHandler,(void *)(spiState));
    return kStatus_FlexIO_SPI_Success;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_Deinit
 * Description   : Shutdown a FlexIO simulated SPI device.
 * This function destroy the semaphores
 *
 *END**************************************************************************/
void FLEXIO_SPI_DRV_Deinit(flexio_spi_state_t *spiState)
{
     /* Release dma channel */
    if (spiState->isTxUseDma)
    {
#if defined FSL_FEATURE_EDMA_MODULE_CHANNEL
        EDMA_DRV_ReleaseChannel(&spiState->edmaSpiTx);
#else
        DMA_DRV_FreeChannel(&spiState->dmaSpiTx);
#endif
    }
    if (spiState->isRxUseDma)
    {
#if defined FSL_FEATURE_EDMA_MODULE_CHANNEL
        EDMA_DRV_ReleaseChannel(&spiState->edmaSpiRx);
#else
        DMA_DRV_FreeChannel(&spiState->dmaSpiRx);
#endif
    }
    /* Destroy TX, RX, Tx&Rx sema. */
    OSA_SemaDestroy(&spiState->txIrqSync);
    OSA_SemaDestroy(&spiState->rxIrqSync);
    OSA_SemaDestroy(&spiState->xIrqSync);
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_InstallRxCallback
 * Description   : Install receive data callback function, pass in NULL pointer
 * as callback will unistall.
 *
 *END**************************************************************************/
flexio_spi_rx_callback_t FLEXIO_SPI_DRV_InstallRxCallback(flexio_spi_state_t *spiState,flexio_spi_rx_callback_t function, 
                                              uint8_t * rxBuff,void * callbackParam)
{
    flexio_spi_rx_callback_t currentCallback = spiState->rxCallback;
    spiState->rxCallback = function;
    spiState->rxCallbackParam = callbackParam;
    spiState->rxBuff = rxBuff;

    spiState->isRxBusy = true;
    return currentCallback;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_SendDataBlocking
 * Description   : This function sends (transmits) data out through the FlexIO
 * simulated SPI module using a blocking method.
 * A blocking (also known as synchronous) function means that the function does
 * not return until the transmit is complete. This blocking function is used to
 * send data through the FlexIO simulated SPI port.
 *
 *END**************************************************************************/
flexio_spi_status_t FLEXIO_SPI_DRV_SendDataBlocking(flexio_spi_state_t *spiState,
                                        const uint8_t * txBuff,
                                        uint32_t txSize,
                                        uint32_t timeout)
{
    if((spiState == NULL)||(txBuff == NULL))
    {
        return kStatus_FlexIO_SPI_InvalidParam;
    }
    flexio_spi_status_t retVal = kStatus_FlexIO_SPI_Success;
    osa_status_t syncStatus;

    /* Indicates current transaction is blocking.*/
    spiState->isTxBlocking = true;
    
    /* Start the transmission process */
    retVal = FLEXIO_SPI_DRV_StartSendData(spiState, txBuff, txSize);

    if (retVal == kStatus_FlexIO_SPI_Success)
    {
        /* Wait until the transmit is complete. */
        do
        {
            syncStatus = OSA_SemaWait(&spiState->txIrqSync, timeout);
        }while(syncStatus == kStatus_OSA_Idle);

        if (syncStatus != kStatus_OSA_Success)
        {
            /* Disable the transmitter data register empty interrupt */
            FLEXIO_SPI_HAL_SetTxBufferEmptyIntCmd(&(spiState->spiDev), false);
            /* Update the information of the module driver state */
            spiState->isTxBusy = false;

            retVal = kStatus_FlexIO_SPI_Timeout;
        }
    }
    return retVal;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_SendData
 * Description   : This function sends (transmits) data through the FlexIO simulated
 * SPI module using a non-blocking method.
 * A non-blocking (also known as asynchronous) function means that the function
 * returns immediately after initiating the transmit function. The application
 * has to get the transmit status to see when the transmit is complete. In
 * other words, after calling non-blocking (asynchronous) send function, the
 * application must get the transmit status to check if transmit is completed
 * or not.
 *
 *END**************************************************************************/
flexio_spi_status_t FLEXIO_SPI_DRV_SendData(flexio_spi_state_t *spiState,
                                            const uint8_t * txBuff,
                                            uint32_t txSize)
{
    if((spiState == NULL)||(txBuff == NULL))
    {
        return kStatus_FlexIO_SPI_InvalidParam;
    }

    flexio_spi_status_t retVal = kStatus_FlexIO_SPI_Success;

    /* Indicates current transaction is non-blocking */
    spiState->isTxBlocking = false;

    /* Start the transmission process */
    retVal = FLEXIO_SPI_DRV_StartSendData(spiState, txBuff, txSize);

    return retVal;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_GetTransmitStatus
 * Description   : This function returns whether the previous transmit has 
 * finished.
 * When performing an non-blocking transmit, the user can call this function to
 * ascertain the state of the current transmission: in progress (or busy) or
 * complete (success). In addition, if the transmission is still in progress,
 * the user can obtain the number of words that have been currently transferred.
 *
 *END**************************************************************************/
flexio_spi_status_t FLEXIO_SPI_DRV_GetTransmitStatus(flexio_spi_state_t *spiState, uint32_t * bytesRemaining)
{
    if(spiState == NULL)
    {
        return kStatus_FlexIO_SPI_InvalidParam;
    }

    flexio_spi_status_t retVal = kStatus_FlexIO_SPI_Success;
    uint32_t txSize = spiState->txSize;

    /* Fill in the bytes transferred. This may return that all bytes were
     * transmitted.*/
    if (bytesRemaining)
    {
        *bytesRemaining = txSize;
    }

    if (txSize)
    {
        retVal = kStatus_FlexIO_SPI_TxBusy;
    }
    
    return retVal;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_AbortSendingData
 * Description   : This function ends a non-blocking SPI transmission early.
 * During a non-blocking SPI transmission, the user has the option to terminate
 * the transmission early if the transmission is still in progress.
 *
 *END**************************************************************************/
flexio_spi_status_t FLEXIO_SPI_DRV_AbortSendingData(flexio_spi_state_t *spiState)
{
    if(spiState == NULL)
    {
        return kStatus_FlexIO_SPI_InvalidParam;
    }

    /* Check if a transfer is running. */
    if (!spiState->isTxBusy)
    {
        return kStatus_FlexIO_SPI_NoTransmitInProgress;
    }

    /* Stop the running transfer. */
    FLEXIO_SPI_DRV_CompleteSendData(spiState);

    return kStatus_FlexIO_SPI_Success;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_ReceiveDataBlocking
 * Description   : This function gets (receives) data from the SPI module using
 * a blocking method. A blocking (also known as synchronous) function means that
 * the function does not return until the receive is complete. This blocking
 * function is used to send data through the SPI port.
 *
 *END**************************************************************************/
flexio_spi_status_t FLEXIO_SPI_DRV_ReceiveDataBlocking(flexio_spi_state_t *spiState, uint8_t * rxBuff,
                                           uint32_t rxSize, uint32_t timeout)
{
    if((spiState == NULL)||(rxBuff == NULL))
    {
        return kStatus_FlexIO_SPI_InvalidParam;
    }

    flexio_spi_status_t retVal = kStatus_FlexIO_SPI_Success;
    osa_status_t syncStatus;

    /* Indicates current transaction is blocking.*/
    spiState->isRxBlocking = true;

    retVal = FLEXIO_SPI_DRV_StartReceiveData(spiState, rxBuff, rxSize);

    if (retVal == kStatus_FlexIO_SPI_Success)
    {
        /* Wait until all the data is received or for timeout.*/
        do
        {
            syncStatus = OSA_SemaWait(&spiState->rxIrqSync, timeout);
        }while(syncStatus == kStatus_OSA_Idle);

        if (syncStatus != kStatus_OSA_Success)
        {
            /* Disable receive data full and rx overrun interrupt */
            FLEXIO_SPI_HAL_SetRxBufferFullIntCmd(&(spiState->spiDev), false);
            /* Update the information of the module driver state */
            spiState->isRxBusy = false;

            retVal = kStatus_FlexIO_SPI_Timeout;
        }
    }

    return retVal;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_ReceiveData
 * Description   : This function gets (receives) data from the simluated SPI
 * module using a non-blocking method.
 * A non-blocking (also known as synchronous) function means that the function
 * returns immediately after initiating the receive function. The application
 * has to get the receive status to see when the receive is complete. In other
 * words, after calling non-blocking (asynchronous) get function, the
 * application must get the receive status to check if receive is completed or
 * not.
 *
 *END**************************************************************************/
flexio_spi_status_t FLEXIO_SPI_DRV_ReceiveData(flexio_spi_state_t *spiState,
                                   uint8_t * rxBuff,
                                   uint32_t rxSize)
{
    if((spiState == NULL)||(rxBuff == NULL))
    {
        return kStatus_FlexIO_SPI_InvalidParam;
    }

    flexio_spi_status_t retVal = kStatus_FlexIO_SPI_Success;

    /* Indicates current transaction is non-blocking.*/
    spiState->isRxBlocking = false;

    retVal = FLEXIO_SPI_DRV_StartReceiveData(spiState, rxBuff, rxSize);

    return retVal;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_GetReceiveStatus
 * Description   : This function returns whether the previous UART receive is
 *                 completed.
 * When performing a non-blocking receive, the user can call this function to
 * ascertain the state of the current receive progress: in progress (or busy)
 * or complete (success). In addition, if the receive is still in progress, the
 * user can obtain the number of words that have been currently received.
 *
 *END**************************************************************************/
flexio_spi_status_t FLEXIO_SPI_DRV_GetReceiveStatus(flexio_spi_state_t *spiState,
                                        uint32_t * bytesRemaining)
{
    if(spiState == NULL)
    {
        return kStatus_FlexIO_SPI_InvalidParam;
    }
    flexio_spi_status_t retVal = kStatus_FlexIO_SPI_Success;
    uint32_t rxSize = spiState->rxSize;

    /* Fill in the bytes transferred. */
    if (bytesRemaining)
    {
        *bytesRemaining = rxSize;
    }

    if (rxSize)
    {
        retVal = kStatus_FlexIO_SPI_RxBusy;
    }

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_AbortReceivingData
 * Description   : This function aborts data receive.
 *
 *END**************************************************************************/
flexio_spi_status_t FLEXIO_SPI_DRV_AbortReceivingData(flexio_spi_state_t *spiState)
{
    if(spiState == NULL)
    {
        return kStatus_FlexIO_SPI_InvalidParam;
    }

    /* Check if a transfer is running. */
    if (!spiState->isRxBusy)
    {
        return kStatus_FlexIO_SPI_NoReceiveInProgress;
    }

    /* Stop the running transfer. */
    FLEXIO_SPI_DRV_CompleteReceiveData(spiState);

    return kStatus_FlexIO_SPI_Success;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_TransferDataBlocking
 * Description   : This function sends&gets data from the SPI module using
 * a blocking method. A blocking (also known as synchronous) function means that
 * the function does not return until the transfer is complete. This blocking
 * function is used to transfer data through the SPI port.
 *
 *END**************************************************************************/
flexio_spi_status_t FLEXIO_SPI_DRV_TransferDataBlocking(flexio_spi_state_t *spiState, const uint8_t * txBuff,
                                           uint8_t *rxBuff, uint32_t xSize, uint32_t timeout)
{
    if((spiState == NULL)||(txBuff == NULL)||(rxBuff == NULL))
    {
        return kStatus_FlexIO_SPI_InvalidParam;
    }

    flexio_spi_status_t retVal = kStatus_FlexIO_SPI_Success;
    osa_status_t syncStatus;

    /* Indicates current transaction is blocking.*/
    spiState->isXBlocking = true;

    retVal = FLEXIO_SPI_DRV_StartTransferData(spiState, txBuff, rxBuff, xSize);

    if (retVal == kStatus_FlexIO_SPI_Success)
    {
        /* Wait until all the data is transferred or for timeout.*/
        do
        {
            syncStatus = OSA_SemaWait(&spiState->xIrqSync, timeout);
        }while(syncStatus == kStatus_OSA_Idle);

        if (syncStatus != kStatus_OSA_Success)
        {
            /* Disable receive data full and tx data empty interrupt */
            FLEXIO_SPI_HAL_SetTxBufferEmptyIntCmd(&(spiState->spiDev), false);
            FLEXIO_SPI_HAL_SetRxBufferFullIntCmd(&(spiState->spiDev), false);
            /* Update the information of the module driver state */
            spiState->isXBusy = false;

            retVal = kStatus_FlexIO_SPI_Timeout;
        }
    }

    return retVal;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_TransferData
 * Description   : This function sends&gets data from the simulated SPI
 * module using a non-blocking method.
 * A non-blocking (also known as synchronous) function means that the function
 * returns immediately after initiating the transfer function. The application
 * has to get the transfer status to see when the transfer is complete. In other
 * words, after calling non-blocking (asynchronous) get function, the
 * application must get the transfer status to check if transfer is completed or
 * not.
 *
 *END**************************************************************************/
flexio_spi_status_t FLEXIO_SPI_DRV_TransferData(flexio_spi_state_t *spiState,
                                   const uint8_t *txBuff, uint8_t * rxBuff,
                                   uint32_t xSize)
{
    if((spiState == NULL)||(txBuff == NULL)||(rxBuff == NULL))
    {
        return kStatus_FlexIO_SPI_InvalidParam;
    }

    flexio_spi_status_t retVal = kStatus_FlexIO_SPI_Success;

    /* Indicates current transaction is non-blocking.*/
    spiState->isXBlocking = false;

    retVal = FLEXIO_SPI_DRV_StartTransferData(spiState, txBuff, rxBuff, xSize);

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_AbortTransferData
 * Description   : This function aborts data transfer.
 *
 *END**************************************************************************/
flexio_spi_status_t FLEXIO_SPI_DRV_AbortTransferData(flexio_spi_state_t *spiState)
{
    if(spiState == NULL)
    {
        return kStatus_FlexIO_SPI_InvalidParam;
    }

    /* Check if a transfer is running. */
    if (!spiState->isXBusy)
    {
        return kStatus_FlexIO_SPI_NoTransferInProgress;
    }

    /* Stop the running transfer. */
    FLEXIO_SPI_DRV_CompleteTransferData(spiState);

    return kStatus_FlexIO_SPI_Success;
}
#if defined FSL_FEATURE_EDMA_MODULE_CHANNEL
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_EdmaTxCallback
 * Description   : This is not a public interface, called when dma tx ends.
 *
 *END**************************************************************************/
static void FLEXIO_SPI_DRV_EdmaTxCallback(void *param, edma_chn_status_t status)
{
    flexio_spi_state_t *spiState = (flexio_spi_state_t *)param;
    /* Stop DMA channel. */
    EDMA_DRV_StopChannel(&spiState->edmaSpiTx);
    FLEXIO_SPI_HAL_SetTxDmaCmd(&(spiState->spiDev), false);
    if(spiState->isTxBusy)
    {
        FLEXIO_SPI_DRV_CompleteSendData(spiState);
    }
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_EdmaRxCallback
 * Description   : This is not a public interface, called when dma rx ends.
 *
 *END**************************************************************************/
static void FLEXIO_SPI_DRV_EdmaRxCallback(void *param, edma_chn_status_t status)
{
    flexio_spi_state_t *spiState = (flexio_spi_state_t *)param;
    /* Stop DMA channel. */
    EDMA_DRV_StopChannel(&spiState->edmaSpiRx);
    FLEXIO_SPI_HAL_SetRxDmaCmd(&(spiState->spiDev), false);
    if(spiState->isRxBusy)
    {
        FLEXIO_SPI_DRV_CompleteReceiveData(spiState);
    }
    else if(spiState->isXBusy)
    {
        FLEXIO_SPI_DRV_CompleteTransferData(spiState);
    }
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_EdmaSendDataBlocking
 * Description   : Send a period of data using DMA way.
 * This function is an async function.
 *END**************************************************************************/
flexio_spi_status_t FLEXIO_SPI_DRV_EdmaSendDataBlocking(flexio_spi_state_t *spiState,
                                                        const uint8_t * txBuff, 
                                                        uint32_t txSize,
                                                        uint32_t timeout)
{
    FLEXIO_SPI_DRV_EdmaSendData(spiState, txBuff, txSize);
    spiState->isTxBlocking = true;
	FLEXIO_DRV_Start(0);
    /* Wait until the transmit is complete. */
    osa_status_t syncStatus;
    do
    {
        syncStatus = OSA_SemaWait(&spiState->txIrqSync, timeout);
    }while(syncStatus == kStatus_OSA_Idle);
    spiState->isTxBlocking = false;
    if (syncStatus != kStatus_OSA_Success)
    {
        /* Stop DMA channel. */
        EDMA_DRV_StopChannel(&spiState->edmaSpiTx);

        /* Update the information of the module driver state */
        spiState->isTxBusy = false;

        return  kStatus_FlexIO_SPI_Timeout;
    }
    return kStatus_FlexIO_SPI_Success;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_SendDataDma
 * Description   : Send a period of data using DMA way.
 * This function is an async function.
 *END**************************************************************************/
flexio_spi_status_t FLEXIO_SPI_DRV_EdmaSendData(flexio_spi_state_t *spiState,
                                               const uint8_t * txBuff, uint32_t txSize)
{
    if((spiState == NULL)||(txBuff == NULL))
    {
        return kStatus_FlexIO_SPI_InvalidParam;
    }
    if ((spiState->isTxBusy)||(spiState->isXBusy))
    {
        return kStatus_FlexIO_SPI_TxBusy;
    }

    if (txSize == 0U)
    {
        return kStatus_FlexIO_SPI_NoDataToDeal;
    }
    /* Have not configure DMA. */
    if (!spiState->isTxUseDma)
    {
        FLEXIO_SPI_DRV_TxConfigDMA(spiState);
    }
    /* Configure DMA module */
    uint32_t  destAddr;
    if(spiState->bitDirection == kFlexIOSpiMsbFirst)
    {
        destAddr = FLEXIO_SPI_HAL_GetTxBufferMSBAddr(&spiState->spiDev) + 
           (4 - spiState->dataSize/8);
    }
    else
    {
        destAddr = FLEXIO_SPI_HAL_GetTxBufferLSBAddr(&spiState->spiDev);
    }
    /* Configure DMA module */
    edma_transfer_size_t transfersize;
    switch(spiState->dataSize/8)
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
            break;
    }
    edma_software_tcd_t edmaTxTcd;
    edma_transfer_config_t txConfig;
    txConfig.srcLastAddrAdjust = 0;
    txConfig.destLastAddrAdjust = 0;
    txConfig.srcModulo = kEDMAModuloDisable;
    txConfig.destModulo = kEDMAModuloDisable;
    txConfig.srcTransferSize = transfersize;
    txConfig.destTransferSize = transfersize;
    txConfig.minorLoopCount = spiState->dataSize/8;
    txConfig.majorLoopCount = (txSize - spiState->dataSize/8) / (spiState->dataSize/8);
    txConfig.srcAddr = (uint32_t)(txBuff + spiState->dataSize/8);
    txConfig.srcOffset = spiState->dataSize/8;
    txConfig.destAddr = destAddr;
    txConfig.destOffset = 0;
    EDMA_DRV_PrepareDescriptorTransfer(&spiState->edmaSpiTx, &edmaTxTcd, &txConfig, true, true);
    EDMA_DRV_PushDescriptorToReg(&spiState->edmaSpiTx, &edmaTxTcd);
    EDMA_DRV_StartChannel(&spiState->edmaSpiTx);
    /* Put the first data in shifter to start the transmission */
    uint32_t tmp;
    if(spiState->bitDirection == kFlexIOSpiMsbFirst)
    {
      if(spiState->dataSize == kFlexIOSpi8BitMode)
      {
          tmp = *txBuff;
          FLEXIO_SPI_HAL_PutDataMSB(&(spiState->spiDev), tmp<<24);
      }else
      {
          tmp = *((const uint16_t *)txBuff);
          FLEXIO_SPI_HAL_PutDataMSB(&(spiState->spiDev), tmp<<16);   
      }
    }
    else
    {
      if(spiState->dataSize == kFlexIOSpi8BitMode)
      {
          FLEXIO_SPI_HAL_PutDataLSB(&(spiState->spiDev), *(spiState->txBuff));
      }else
      {
          FLEXIO_SPI_HAL_PutDataLSB(&(spiState->spiDev), *((const uint16_t *)(spiState->txBuff)));   
      }
    }
    /* Indicates current transaction is non-blocking */
    spiState->isTxBlocking = false;
    spiState->isTxBusy =  true;
    /*enable dma request interrupt*/
    FLEXIO_SPI_HAL_SetTxDmaCmd(&(spiState->spiDev), true);
    return kStatus_FlexIO_SPI_Success;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_EdmaGetTransmitStatus
 * Description   : This function returns whether the previous SPI transmit
 * has finished. When performing an sync transmit, the user can call this
 * function to ascertain the state of the current transmission: in progress
 * (or busy) or complete (success). In addition, if the transmission is still
 * in progress, the user can obtain the number of words that have been
 * currently transferred.
 *
 *END**************************************************************************/
flexio_spi_status_t FLEXIO_SPI_DRV_EdmaGetTransmitStatus(flexio_spi_state_t * spiState,
                                            uint32_t * bytesRemaining)
{
    if(spiState == NULL)
    {
        return kStatus_FlexIO_SPI_InvalidParam;
    }

    /* Fill in the bytes transferred. */
    if (bytesRemaining)
    {
        *bytesRemaining = EDMA_DRV_GetUnfinishedBytes(&spiState->edmaSpiTx);
    }

    return (spiState->isTxBusy ? kStatus_FlexIO_SPI_TxBusy : kStatus_FlexIO_SPI_Success);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_EdmaAbortSendingData
 * Description   : This function Terminates a non-blocking FLEXIO simulated SPI-DMA 
 * transmission early.During an sync SPI transmission, the user has the option to
 * terminate the transmission early if the transmission is still in progress.
 *
 *END**************************************************************************/
flexio_spi_status_t FLEXIO_SPI_DRV_EdmaAbortSendingData(flexio_spi_state_t * spiState)
{
    if(spiState == NULL)
    {
        return kStatus_FlexIO_SPI_InvalidParam;
    }

    /* Check if a transfer is running. */
    if (!spiState->isTxBusy)
    {
        return kStatus_FlexIO_SPI_NoTransmitInProgress;
    }
    /* Stop DMA channel. */
    EDMA_DRV_StopChannel(&spiState->edmaSpiTx);
    /* Disable SPI Tx DMA interrupt*/
    FLEXIO_SPI_HAL_SetTxDmaCmd(&(spiState->spiDev), false);
    /* Stop the running transfer. */
    FLEXIO_SPI_DRV_CompleteSendData(spiState);

    return kStatus_FlexIO_SPI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_EdmaReceiveDataBlocking
 * Description   : Receive a period of data using interrupt way.
 * This function is an async function.
 *END**************************************************************************/
flexio_spi_status_t FLEXIO_SPI_DRV_EdmaReceiveDataBlocking(flexio_spi_state_t *spiState, 
                                                           uint8_t *rxBuff,
                                                           uint32_t rxSize,
                                                           uint32_t timeout)
{
    FLEXIO_SPI_DRV_EdmaReceiveData(spiState, rxBuff, rxSize);
    spiState->isRxBlocking = true;
    FLEXIO_DRV_Start(0);
    /* Wait until the transmit is complete. */
    osa_status_t syncStatus;
    do
    {
        syncStatus = OSA_SemaWait(&spiState->rxIrqSync, timeout);
    }while(syncStatus == kStatus_OSA_Idle);
    spiState->isRxBlocking = false;
    if (syncStatus != kStatus_OSA_Success)
    {
        /* Stop DMA channel. */
        EDMA_DRV_StopChannel(&spiState->edmaSpiRx);

        /* Update the information of the module driver state */
        spiState->isRxBusy = false;

        return  kStatus_FlexIO_SPI_Timeout;
    }
    return kStatus_FlexIO_SPI_Success;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_EdmaReceiveData
 * Description   : Receive a period of data using interrupt way.
 * This function is an async function.
 *END**************************************************************************/
flexio_spi_status_t FLEXIO_SPI_DRV_EdmaReceiveData(flexio_spi_state_t *spiState, 
                                                   uint8_t *rxBuff,uint32_t rxSize)
{
    if ((spiState == NULL) || (rxBuff == NULL))
    {
        return kStatus_FlexIO_SPI_InvalidParam;
    }
    if ((spiState->isRxBusy)||(spiState->isXBusy))
    {
        return kStatus_FlexIO_SPI_RxBusy;
    }

    if (rxSize == 0U)
    {
        return kStatus_FlexIO_SPI_NoDataToDeal;
    }
    /* Have not configure DMA. */
    if (!spiState->isRxUseDma)
    {
        FLEXIO_SPI_DRV_RxConfigDMA(spiState);
    }
    /* Configure DMA module */
    edma_transfer_size_t transfersize;
    switch(spiState->dataSize/8)
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
            break;
    }
    edma_software_tcd_t edmaRxTcd;
    edma_transfer_config_t rxConfig;
    rxConfig.srcLastAddrAdjust = 0;
    rxConfig.destLastAddrAdjust = 0;
    rxConfig.srcModulo = kEDMAModuloDisable;
    rxConfig.destModulo = kEDMAModuloDisable;
    rxConfig.srcTransferSize = transfersize;
    rxConfig.destTransferSize = transfersize;
    rxConfig.minorLoopCount = spiState->dataSize/8;
    rxConfig.majorLoopCount = rxSize / (spiState->dataSize/8);
    rxConfig.srcAddr = FLEXIO_SPI_HAL_GetRxBufferMSBAddr(&spiState->spiDev);
    rxConfig.srcOffset = 0;
    rxConfig.destAddr = (uint32_t)(rxBuff);
    rxConfig.destOffset = spiState->dataSize/8;
    EDMA_DRV_PrepareDescriptorTransfer(&spiState->edmaSpiRx, &edmaRxTcd, &rxConfig, true, true);
    EDMA_DRV_PushDescriptorToReg(&spiState->edmaSpiRx, &edmaRxTcd);
    EDMA_DRV_StartChannel(&spiState->edmaSpiRx);
    /* Indicates current transaction is non-blocking */
    spiState->isRxBlocking = false;
    spiState->isRxBusy =  true;
    /*enable dma request interrupt*/
    FLEXIO_SPI_HAL_SetRxDmaCmd(&(spiState->spiDev), true);
    return kStatus_FlexIO_SPI_Success;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_EdmaGetReceiveStatus
 * Description   : This function returns whether the previous SPI receive is
 * complete. When performing an sync receive, the user can call this function
 * to ascertain the state of the current receive progress: in progress (or busy)
 * or complete (success). In addition, if the receive is still in progress,
 * the user can obtain the number of words that have been currently received.
 *
 *END**************************************************************************/
flexio_spi_status_t FLEXIO_SPI_DRV_EdmaGetReceiveStatus(flexio_spi_state_t * spiState,
                                           uint32_t * bytesRemaining)
{
    if(spiState == NULL)
    {
        return kStatus_FlexIO_SPI_InvalidParam;
    }

    /* Fill in the bytes transferred. */
    if (bytesRemaining)
    {
        *bytesRemaining = EDMA_DRV_GetUnfinishedBytes(&spiState->edmaSpiRx);
    }

    return (spiState->isRxBusy ? kStatus_FlexIO_SPI_RxBusy : kStatus_FlexIO_SPI_Success);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_EdmaAbortReceivingData
 * Description   : This function shuts down the SPI by disabling interrupts and
 * the transmitter/receiver.
 *
 *END**************************************************************************/
flexio_spi_status_t FLEXIO_SPI_DRV_EdmaAbortReceivingData(flexio_spi_state_t * spiState)
{
    if(spiState == NULL)
    {
        return kStatus_FlexIO_SPI_InvalidParam;
    }

    /* Check if a transfer is running. */
    if (!spiState->isRxBusy)
    {
        return kStatus_FlexIO_SPI_NoReceiveInProgress;
    }

    /* Stop DMA channel. */
    EDMA_DRV_StopChannel(&spiState->edmaSpiRx);
    /* Disable SPI Rx DMA interrupt*/
    FLEXIO_SPI_HAL_SetRxDmaCmd(&(spiState->spiDev), false);
    /* Stop the running transfer. */
    FLEXIO_SPI_DRV_CompleteReceiveData(spiState);

    return kStatus_FlexIO_SPI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_EdmaTransferDataBlocking
 * Description   : Receive a period of data using interrupt way.
 * This function is an async function.
 *END**************************************************************************/
flexio_spi_status_t FLEXIO_SPI_DRV_EdmaTransferDataBlocking(flexio_spi_state_t *spiState,
                                                           const uint8_t *txBuff,
                                                           uint8_t *rxBuff,
                                                           uint32_t xSize,
                                                           uint32_t timeout)
{
    spiState->isXBlocking = true;
    FLEXIO_SPI_DRV_EdmaTransferData(spiState, txBuff, rxBuff, xSize);
    FLEXIO_DRV_Start(0);
    /* Wait until the transmit is complete. */
    osa_status_t syncStatus;
    do
    {
        syncStatus = OSA_SemaWait(&spiState->rxIrqSync, timeout);
    }while(syncStatus == kStatus_OSA_Idle);
    spiState->isXBlocking = false;
    if (syncStatus != kStatus_OSA_Success)
    {
        /* Stop DMA channel. */
        EDMA_DRV_StopChannel(&spiState->edmaSpiRx);

        /* Update the information of the module driver state */
        spiState->isRxBusy = false;

        return  kStatus_FlexIO_SPI_Timeout;
    }
    return kStatus_FlexIO_SPI_Success;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_EdmaTransferData
 * Description   : Receive a period of data using interrupt way.
 * This function is an async function.
 *END**************************************************************************/
flexio_spi_status_t FLEXIO_SPI_DRV_EdmaTransferData(flexio_spi_state_t *spiState,
                                                   const uint8_t *txBuff,
                                                   uint8_t *rxBuff,
                                                   uint32_t xSize)
{
    if ((spiState == NULL) || (txBuff == NULL) || (rxBuff == NULL))
    {
        return kStatus_FlexIO_SPI_InvalidParam;
    }
    if ((spiState->isTxBusy)||(spiState->isRxBusy)||(spiState->isXBusy))
    {
        return kStatus_FlexIO_SPI_XBusy;
    }

    if (xSize == 0U)
    {
        return kStatus_FlexIO_SPI_NoDataToDeal;
    }
    /* Have not configure DMA. */
    if (!spiState->isTxUseDma)
    {
        FLEXIO_SPI_DRV_TxConfigDMA(spiState);
    }

    if (!spiState->isRxUseDma)
    {
        FLEXIO_SPI_DRV_RxConfigDMA(spiState);
    }
    /* Configure DMA module */
    uint32_t  destAddr;
    if(spiState->bitDirection == kFlexIOSpiMsbFirst)
    {
        destAddr = FLEXIO_SPI_HAL_GetTxBufferMSBAddr(&spiState->spiDev) + 
           (4 - spiState->dataSize/8);
    }
    else
    {
        destAddr = FLEXIO_SPI_HAL_GetTxBufferLSBAddr(&spiState->spiDev);
    }
    /* Configure DMA module */
    edma_transfer_size_t transfersize;
    switch(spiState->dataSize/8)
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
            break;
    }
    edma_software_tcd_t edmaTxTcd;
    memset(&edmaTxTcd, 0, sizeof(edmaTxTcd));
    edma_transfer_config_t txConfig;
    txConfig.srcLastAddrAdjust = 0;
    txConfig.destLastAddrAdjust = 0;
    txConfig.srcModulo = kEDMAModuloDisable;
    txConfig.destModulo = kEDMAModuloDisable;
    txConfig.srcTransferSize = transfersize;
    txConfig.destTransferSize = transfersize;
    txConfig.minorLoopCount = spiState->dataSize/8;
    txConfig.majorLoopCount = (xSize - spiState->dataSize/8) / (spiState->dataSize/8);
    txConfig.srcAddr = (uint32_t)(txBuff + spiState->dataSize/8);
    txConfig.srcOffset = spiState->dataSize/8;
    txConfig.destAddr = destAddr;
    txConfig.destOffset = 0;
    EDMA_DRV_PrepareDescriptorTransfer(&spiState->edmaSpiTx, &edmaTxTcd, &txConfig, true, true);
    EDMA_DRV_PushDescriptorToReg(&spiState->edmaSpiTx, &edmaTxTcd);
    EDMA_DRV_StartChannel(&spiState->edmaSpiTx);
    /* Put the first data in shifter to start the transmission */
    uint32_t tmp;
    if(spiState->bitDirection == kFlexIOSpiMsbFirst)
    {
      if(spiState->dataSize == kFlexIOSpi8BitMode)
      {
          tmp = *txBuff;
          FLEXIO_SPI_HAL_PutDataMSB(&(spiState->spiDev), tmp<<24);
      }else
      {
          tmp = *((const uint16_t *)txBuff);
          FLEXIO_SPI_HAL_PutDataMSB(&(spiState->spiDev), tmp<<16);   
      }
    }
    else
    {
      if(spiState->dataSize == kFlexIOSpi8BitMode)
      {
          FLEXIO_SPI_HAL_PutDataLSB(&(spiState->spiDev), *(spiState->txBuff));
      }else
      {
          FLEXIO_SPI_HAL_PutDataLSB(&(spiState->spiDev), *((const uint16_t *)(spiState->txBuff)));   
      }
    }
    /* Configure DMA module */
    edma_software_tcd_t edmaRxTcd;
    memset(&edmaRxTcd, 0, sizeof(edmaRxTcd));
    edma_transfer_config_t rxConfig;
    rxConfig.srcLastAddrAdjust = 0;
    rxConfig.destLastAddrAdjust = 0;
    rxConfig.srcModulo = kEDMAModuloDisable;
    rxConfig.destModulo = kEDMAModuloDisable;
    rxConfig.srcTransferSize = transfersize;
    rxConfig.destTransferSize = transfersize;
    rxConfig.minorLoopCount = spiState->dataSize/8;
    rxConfig.majorLoopCount = xSize / (spiState->dataSize/8);
    rxConfig.srcAddr = FLEXIO_SPI_HAL_GetRxBufferMSBAddr(&spiState->spiDev);
    rxConfig.srcOffset = 0;
    rxConfig.destAddr = (uint32_t)(rxBuff);
    rxConfig.destOffset = spiState->dataSize/8;
    EDMA_DRV_PrepareDescriptorTransfer(&spiState->edmaSpiRx, &edmaRxTcd, &rxConfig, true, true);
    EDMA_DRV_PushDescriptorToReg(&spiState->edmaSpiRx, &edmaRxTcd);
    EDMA_DRV_StartChannel(&spiState->edmaSpiRx);
    /* Indicates current transaction is non-blocking */
    spiState->isXBlocking = false;
    spiState->isXBusy =  true;
    /*enable dma request interrupt*/
    FLEXIO_SPI_HAL_SetTxDmaCmd(&(spiState->spiDev), true);
    FLEXIO_SPI_HAL_SetRxDmaCmd(&(spiState->spiDev), true);
    return kStatus_FlexIO_SPI_Success;
}
#else
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_DmaGetTransmitStatus
 * Description   : This function returns whether the previous SPI transmit
 * has finished. When performing an async transmit, the user can call this
 * function to ascertain the state of the current transmission: in progress
 * (or busy) or complete (success). In addition, if the transmission is still
 * in progress, the user can obtain the number of words that have been
 * currently transferred.
 *
 *END**************************************************************************/
flexio_spi_status_t FLEXIO_SPI_DRV_DmaGetTransmitStatus(flexio_spi_state_t * spiState,
                                            uint32_t * bytesRemaining)
{
    if(spiState == NULL)
    {
        return kStatus_FlexIO_SPI_InvalidParam;
    }

    /* Fill in the bytes transferred. */
    if (bytesRemaining)
    {
        *bytesRemaining = DMA_DRV_GetUnfinishedBytes(&spiState->dmaSpiTx);
    }

    return (spiState->isTxBusy ? kStatus_FlexIO_SPI_TxBusy : kStatus_FlexIO_SPI_Success);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_DmaAbortSendingData
 * Description   : This function Terminates a non-blocking FLEXIO simulated SPI-DMA 
 * transmission early.During an sync SPI transmission, the user has the option to
 * terminate the transmission early if the transmission is still in progress.
 *
 *END**************************************************************************/
flexio_spi_status_t FLEXIO_SPI_DRV_DmaAbortSendingData(flexio_spi_state_t * spiState)
{
    if(spiState == NULL)
    {
        return kStatus_FlexIO_SPI_InvalidParam;
    }

    /* Check if a transfer is running. */
    if (!spiState->isTxBusy)
    {
        return kStatus_FlexIO_SPI_NoTransmitInProgress;
    }
    /* Stop DMA channel. */
    DMA_DRV_StopChannel(&spiState->dmaSpiTx);
    /* Disable SPI Tx DMA interrupt*/
    FLEXIO_SPI_HAL_SetTxDmaCmd(&(spiState->spiDev), false);
    /* Stop the running transfer. */
    FLEXIO_SPI_DRV_CompleteSendData(spiState);

    return kStatus_FlexIO_SPI_Success;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_DmaTxCallback
 * Description   : This is not a public interface, called when dma tx ends.
 *
 *END**************************************************************************/
static void FLEXIO_SPI_DRV_DmaTxCallback(void *param, dma_channel_status_t status)
{
    flexio_spi_state_t *spiState = (flexio_spi_state_t *)param;
    /* Stop DMA channel. */
    DMA_DRV_StopChannel(&spiState->dmaSpiTx);
    FLEXIO_SPI_HAL_SetTxDmaCmd(&(spiState->spiDev), false);
    if(spiState->isTxBusy)
    {
        FLEXIO_SPI_DRV_CompleteSendData(spiState);
    }
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_DmaRxCallback
 * Description   : This is not a public interface, called when dma rx ends.
 *
 *END**************************************************************************/
static void FLEXIO_SPI_DRV_DmaRxCallback(void *param, dma_channel_status_t status)
{
    flexio_spi_state_t *spiState = (flexio_spi_state_t *)param;
    /* Stop DMA channel. */
    DMA_DRV_StopChannel(&spiState->dmaSpiRx);
    FLEXIO_SPI_HAL_SetRxDmaCmd(&(spiState->spiDev), false);
    if(spiState->isRxBusy)
    {
        FLEXIO_SPI_DRV_CompleteReceiveData(spiState);
    }
    else if(spiState->isXBusy)
    {
        FLEXIO_SPI_DRV_CompleteTransferData(spiState);
    }
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_DmaSendDataBlocking
 * Description   : Send a period of data using DMA way.
 * This function is an async function.
 *END**************************************************************************/
flexio_spi_status_t FLEXIO_SPI_DRV_DmaSendDataBlocking(flexio_spi_state_t *spiState,
                                                       const uint8_t * txBuff, 
                                                       uint32_t txSize,
                                                       uint32_t timeout)
{
    if((spiState == NULL)||(txBuff == NULL))
    {
        return kStatus_FlexIO_SPI_InvalidParam;
    }
    /* Check that we're not busy already transmitting data from a previous
     * function call. */
    if ((spiState->isTxBusy)||(spiState->isXBusy))
    {
        return kStatus_FlexIO_SPI_TxBusy;
    }

    if (txSize == 0U)
    {
        return kStatus_FlexIO_SPI_NoDataToDeal;
    }
    /* Have not configure DMA. */
    if (!spiState->isTxUseDma)
    {
        FLEXIO_SPI_DRV_TxConfigDMA(spiState);
    }
    /* Configure DMA module */
    uint32_t destAddr;
    if(spiState->bitDirection == kFlexIOSpiMsbFirst)
    {
        destAddr = FLEXIO_SPI_HAL_GetTxBufferMSBAddr(&spiState->spiDev) + 
           (4 - spiState->dataSize/8);
    }
    else
    {
        destAddr = FLEXIO_SPI_HAL_GetTxBufferLSBAddr(&spiState->spiDev);
    }
    DMA_DRV_ConfigTransfer(&spiState->dmaSpiTx,kDmaMemoryToPeripheral, 
           spiState->dataSize/8, (uint32_t)(txBuff + spiState->dataSize/8), 
           destAddr, (txSize - spiState->dataSize/8));
    DMA_DRV_StartChannel(&spiState->dmaSpiTx);
    /* Put the first data in shifter to start the transmission */
    uint32_t tmp;
    if(spiState->bitDirection == kFlexIOSpiMsbFirst)
    {
      if(spiState->dataSize == kFlexIOSpi8BitMode)
      {
          tmp = *txBuff;
          FLEXIO_SPI_HAL_PutDataMSB(&(spiState->spiDev), tmp<<24);
      }else
      {
          tmp = *((const uint16_t *)txBuff);
          FLEXIO_SPI_HAL_PutDataMSB(&(spiState->spiDev), tmp<<16);   
      }
    }
    else
    {
      if(spiState->dataSize == kFlexIOSpi8BitMode)
      {
          FLEXIO_SPI_HAL_PutDataLSB(&(spiState->spiDev), *(spiState->txBuff));
      }else
      {
          FLEXIO_SPI_HAL_PutDataLSB(&(spiState->spiDev), *((const uint16_t *)(spiState->txBuff)));   
      }
    }
    /* Indicates current transaction is non-blocking */
    spiState->isTxBlocking = true;
    spiState->isTxBusy =  true;
    /*enable dma request interrupt*/
    FLEXIO_SPI_HAL_SetTxDmaCmd(&(spiState->spiDev), true);
    FLEXIO_DRV_Start(0);
    /* Wait until the transmit is complete. */
    osa_status_t syncStatus;
    do
    {
        syncStatus = OSA_SemaWait(&spiState->txIrqSync, timeout);
    }while(syncStatus == kStatus_OSA_Idle);

    if (syncStatus != kStatus_OSA_Success)
    {
        /* Stop DMA channel. */
        DMA_DRV_StopChannel(&spiState->dmaSpiTx);

        /* Update the information of the module driver state */
        spiState->isTxBusy = false;

        return  kStatus_FlexIO_SPI_Timeout;
    }
    return kStatus_FlexIO_SPI_Success;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_DmaSendData
 * Description   : Send a period of data using DMA way.
 * This function is an async function.
 *END**************************************************************************/
flexio_spi_status_t FLEXIO_SPI_DRV_DmaSendData(flexio_spi_state_t *spiState,
                                               const uint8_t * txBuff, uint32_t txSize)
{
    if ((spiState == NULL) || (txBuff == NULL) )
    {
        return kStatus_FlexIO_SPI_InvalidParam;
    }
    /* Check that we're not busy already transmitting data from a previous
     * function call. */
    if ((spiState->isTxBusy)||(spiState->isXBusy))
    {
        return kStatus_FlexIO_SPI_TxBusy;
    }

    if (txSize == 0U)
    {
        return kStatus_FlexIO_SPI_NoDataToDeal;
    }
    /* Have not configure DMA. */
    if (!spiState->isTxUseDma)
    {
        FLEXIO_SPI_DRV_TxConfigDMA(spiState);
    }
    /* Configure DMA module */
    uint32_t destAddr;
    if(spiState->bitDirection == kFlexIOSpiMsbFirst)
    {
        destAddr = FLEXIO_SPI_HAL_GetTxBufferMSBAddr(&spiState->spiDev) + 
           (4 - spiState->dataSize/8);
    }
    else
    {
        destAddr = FLEXIO_SPI_HAL_GetTxBufferLSBAddr(&spiState->spiDev);
    }
    DMA_DRV_ConfigTransfer(&spiState->dmaSpiTx,kDmaMemoryToPeripheral, 
           spiState->dataSize/8, (uint32_t)(txBuff + spiState->dataSize/8), 
           destAddr, (txSize - spiState->dataSize/8));
    DMA_DRV_StartChannel(&spiState->dmaSpiTx);
    /* Put the first data in shifter to start the transmission */
    uint32_t tmp;
    if(spiState->bitDirection == kFlexIOSpiMsbFirst)
    {
      if(spiState->dataSize == kFlexIOSpi8BitMode)
      {
          tmp = *txBuff;
          FLEXIO_SPI_HAL_PutDataMSB(&(spiState->spiDev), tmp<<24);
      }else
      {
          tmp = *((const uint16_t *)txBuff);
          FLEXIO_SPI_HAL_PutDataMSB(&(spiState->spiDev), tmp<<16);   
      }
    }
    else
    {
      if(spiState->dataSize == kFlexIOSpi8BitMode)
      {
          FLEXIO_SPI_HAL_PutDataLSB(&(spiState->spiDev), *(spiState->txBuff));
      }else
      {
          FLEXIO_SPI_HAL_PutDataLSB(&(spiState->spiDev), *((const uint16_t *)(spiState->txBuff)));   
      }
    }
    /* Indicates current transaction is non-blocking */
    spiState->isTxBlocking = false;
    spiState->isTxBusy =  true;
    /*enable dma request interrupt*/
    FLEXIO_SPI_HAL_SetTxDmaCmd(&(spiState->spiDev), true);
    return kStatus_FlexIO_SPI_Success;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_DmaReceiveDataBlocking
 * Description   : Receive a period of data using interrupt way.
 * This function is an async function.
 *END**************************************************************************/
flexio_spi_status_t FLEXIO_SPI_DRV_DmaReceiveDataBlocking(flexio_spi_state_t *spiState,
                                                          uint8_t * rxBuff, 
                                                          uint32_t rxSize,
                                                          uint32_t timeout)
{
    if ((spiState == NULL) || (rxBuff == NULL))
    {
        return kStatus_FlexIO_SPI_InvalidParam;
    }
    if ((spiState->isRxBusy)||(spiState->isXBusy))
    {
        return kStatus_FlexIO_SPI_RxBusy;
    }

    if (rxSize == 0U)
    {
        return kStatus_FlexIO_SPI_NoDataToDeal;
    }
    if (!spiState->isRxUseDma)
    {
        FLEXIO_SPI_DRV_RxConfigDMA(spiState);
    }
    /* Configure DMA module */
    uint32_t srcAddr = FLEXIO_SPI_HAL_GetRxBufferMSBAddr(&spiState->spiDev);
    DMA_DRV_ConfigTransfer(&spiState->dmaSpiRx,kDmaPeripheralToMemory, 
           spiState->dataSize/8, srcAddr, (uint32_t)rxBuff, rxSize);
    DMA_DRV_StartChannel(&spiState->dmaSpiRx);
    /* Indicates current transaction is non-blocking */
    spiState->isRxBlocking = true;
    spiState->isRxBusy =  true;
    /*enable dma request interrupt*/
    FLEXIO_SPI_HAL_SetRxDmaCmd(&(spiState->spiDev), true);
    FLEXIO_DRV_Start(0);
    /* Wait until the transmit is complete. */
    osa_status_t syncStatus;
    do
    {
        syncStatus = OSA_SemaWait(&spiState->rxIrqSync, timeout);
    }while(syncStatus == kStatus_OSA_Idle);

    if (syncStatus != kStatus_OSA_Success)
    {
        /* Stop DMA channel. */
        DMA_DRV_StopChannel(&spiState->dmaSpiRx);

        /* Update the information of the module driver state */
        spiState->isRxBusy = false;

        return  kStatus_FlexIO_SPI_Timeout;
    }
    return kStatus_FlexIO_SPI_Success;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_DmaReceiveData
 * Description   : Receive a period of data using interrupt way.
 * This function is an async function.
 *END**************************************************************************/
flexio_spi_status_t FLEXIO_SPI_DRV_DmaReceiveData(flexio_spi_state_t *spiState, uint8_t *rxBuff, uint32_t rxSize)
{
    if ((spiState == NULL) || (rxBuff == NULL))
    {
        return kStatus_FlexIO_SPI_InvalidParam;
    }
    if ((spiState->isRxBusy)||(spiState->isXBusy))
    {
        return kStatus_FlexIO_SPI_RxBusy;
    }

    if (rxSize == 0U)
    {
        return kStatus_FlexIO_SPI_NoDataToDeal;
    }
    if (!spiState->isRxUseDma)
    {
        FLEXIO_SPI_DRV_RxConfigDMA(spiState);
    }
    /* Configure DMA module */
    uint32_t srcAddr = FLEXIO_SPI_HAL_GetRxBufferMSBAddr(&spiState->spiDev);
    DMA_DRV_ConfigTransfer(&spiState->dmaSpiRx,kDmaPeripheralToMemory, 
           spiState->dataSize/8, srcAddr, (uint32_t)rxBuff, rxSize);
    DMA_DRV_StartChannel(&spiState->dmaSpiRx);
    /* Indicates current transaction is non-blocking */
    spiState->isRxBlocking = false;
    spiState->isRxBusy =  true;
    /*enable dma request interrupt*/
    FLEXIO_SPI_HAL_SetRxDmaCmd(&(spiState->spiDev), true);

    return kStatus_FlexIO_SPI_Success;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_DmaTransferDataBlocking
 * Description   : Send&Receive a period of data using interrupt way.
 * This function is an async function.
 *END**************************************************************************/
flexio_spi_status_t FLEXIO_SPI_DRV_DmaTransferDataBlocking(flexio_spi_state_t *spiState, 
                                                           const uint8_t *txBuff, 
                                                           uint8_t *rxBuff,
                                                           uint32_t xSize,
                                                           uint32_t timeout)
{
    if ((spiState == NULL) || (txBuff == NULL) ||(rxBuff == NULL))
    {
        return kStatus_FlexIO_SPI_InvalidParam;
    }
    if ((spiState->isTxBusy)||(spiState->isRxBusy)||(spiState->isXBusy))
    {
        return kStatus_FlexIO_SPI_XBusy;
    }

    if (xSize == 0U)
    {
        return kStatus_FlexIO_SPI_NoDataToDeal;
    }
    if (!spiState->isTxUseDma)
    {
        FLEXIO_SPI_DRV_TxConfigDMA(spiState);
    }
    if (!spiState->isRxUseDma)
    {
        FLEXIO_SPI_DRV_RxConfigDMA(spiState);
    }
    /* Configure DMA module */
    uint32_t destAddr;
    if(spiState->bitDirection == kFlexIOSpiMsbFirst)
    {
        destAddr = FLEXIO_SPI_HAL_GetTxBufferMSBAddr(&spiState->spiDev) + 
           (4 - spiState->dataSize/8);
    }
    else
    {
        destAddr = FLEXIO_SPI_HAL_GetTxBufferLSBAddr(&spiState->spiDev);
    }
    DMA_DRV_ConfigTransfer(&spiState->dmaSpiTx,kDmaMemoryToPeripheral, 
           spiState->dataSize/8, (uint32_t)(txBuff + spiState->dataSize/8), 
           destAddr, (xSize - spiState->dataSize/8));
    DMA_DRV_StartChannel(&spiState->dmaSpiTx);
    /* Put the first data in shifter to start the transmission */
    uint32_t tmp;
    if(spiState->bitDirection == kFlexIOSpiMsbFirst)
    {
      if(spiState->dataSize == kFlexIOSpi8BitMode)
      {
          tmp = *txBuff;
          FLEXIO_SPI_HAL_PutDataMSB(&(spiState->spiDev), tmp<<24);
      }else
      {
          tmp = *((const uint16_t *)txBuff);
          FLEXIO_SPI_HAL_PutDataMSB(&(spiState->spiDev), tmp<<16);   
      }
    }
    else
    {
      if(spiState->dataSize == kFlexIOSpi8BitMode)
      {
          FLEXIO_SPI_HAL_PutDataLSB(&(spiState->spiDev), *(spiState->txBuff));
      }else
      {
          FLEXIO_SPI_HAL_PutDataLSB(&(spiState->spiDev), *((const uint16_t *)(spiState->txBuff)));   
      }
    }
    uint32_t srcAddr = FLEXIO_SPI_HAL_GetRxBufferMSBAddr(&spiState->spiDev);
    DMA_DRV_ConfigTransfer(&spiState->dmaSpiRx,kDmaPeripheralToMemory, 
           spiState->dataSize/8, srcAddr, (uint32_t)rxBuff, xSize);
    DMA_DRV_StartChannel(&spiState->dmaSpiRx);
    /* Indicates current transaction is non-blocking */
    spiState->isXBlocking = true;
    spiState->isXBusy =  true;
    /*enable dma request interrupt*/
    FLEXIO_SPI_HAL_SetTxDmaCmd(&(spiState->spiDev), true);
    FLEXIO_SPI_HAL_SetRxDmaCmd(&(spiState->spiDev), true);
    FLEXIO_DRV_Start(0);
    /* Wait until the transfer is complete. */
    osa_status_t syncStatus;
    do
    {
        syncStatus = OSA_SemaWait(&spiState->xIrqSync, timeout);
    }while(syncStatus == kStatus_OSA_Idle);

    if (syncStatus != kStatus_OSA_Success)
    {
        /* Stop DMA channel. */
        DMA_DRV_StopChannel(&spiState->dmaSpiTx);
        DMA_DRV_StopChannel(&spiState->dmaSpiRx);

        /* Update the information of the module driver state */
        spiState->isXBusy = false;

        return  kStatus_FlexIO_SPI_Timeout;
    }
    return kStatus_FlexIO_SPI_Success;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_DmaTransferData
 * Description   : Send&Receive a period of data using interrupt way.
 * This function is an async function.
 *END**************************************************************************/
flexio_spi_status_t FLEXIO_SPI_DRV_DmaTransferData(flexio_spi_state_t *spiState, 
                                                   const uint8_t *txBuff, 
                                                   uint8_t *rxBuff,
                                                   uint32_t xSize)
{
    if ((spiState == NULL) || (txBuff == NULL) ||(rxBuff == NULL))
    {
        return kStatus_FlexIO_SPI_InvalidParam;
    }
    if ((spiState->isTxBusy)||(spiState->isRxBusy)||(spiState->isXBusy))
    {
        return kStatus_FlexIO_SPI_XBusy;
    }

    if (xSize == 0U)
    {
        return kStatus_FlexIO_SPI_NoDataToDeal;
    }
    if (!spiState->isTxUseDma)
    {
        FLEXIO_SPI_DRV_TxConfigDMA(spiState);
    }
    if (!spiState->isRxUseDma)
    {
        FLEXIO_SPI_DRV_RxConfigDMA(spiState);
    }
    /* Configure DMA module */
    uint32_t destAddr;
    if(spiState->bitDirection == kFlexIOSpiMsbFirst)
    {
        destAddr = FLEXIO_SPI_HAL_GetTxBufferMSBAddr(&spiState->spiDev) + 
           (4 - spiState->dataSize/8);
    }
    else
    {
        destAddr = FLEXIO_SPI_HAL_GetTxBufferLSBAddr(&spiState->spiDev);
    }
    DMA_DRV_ConfigTransfer(&spiState->dmaSpiTx,kDmaMemoryToPeripheral, 
           spiState->dataSize/8, (uint32_t)(txBuff + spiState->dataSize/8), 
           destAddr, (xSize - spiState->dataSize/8));
    DMA_DRV_StartChannel(&spiState->dmaSpiTx);
    /* Put the first data in shifter to start the transmission */
    uint32_t tmp;
    if(spiState->bitDirection == kFlexIOSpiMsbFirst)
    {
      if(spiState->dataSize == kFlexIOSpi8BitMode)
      {
          tmp = *txBuff;
          FLEXIO_SPI_HAL_PutDataMSB(&(spiState->spiDev), tmp<<24);
      }else
      {
          tmp = *((const uint16_t *)txBuff);
          FLEXIO_SPI_HAL_PutDataMSB(&(spiState->spiDev), tmp<<16);   
      }
    }
    else
    {
      if(spiState->dataSize == kFlexIOSpi8BitMode)
      {
          FLEXIO_SPI_HAL_PutDataLSB(&(spiState->spiDev), *(spiState->txBuff));
      }else
      {
          FLEXIO_SPI_HAL_PutDataLSB(&(spiState->spiDev), *((const uint16_t *)(spiState->txBuff)));   
      }
    }
    uint32_t srcAddr = FLEXIO_SPI_HAL_GetRxBufferMSBAddr(&spiState->spiDev);
    DMA_DRV_ConfigTransfer(&spiState->dmaSpiRx,kDmaPeripheralToMemory, 
           spiState->dataSize/8, srcAddr, (uint32_t)rxBuff, xSize);
    DMA_DRV_StartChannel(&spiState->dmaSpiRx);
    /* Indicates current transaction is non-blocking */
    spiState->isXBlocking = false;
    spiState->isXBusy =  true;
    /*enable dma request interrupt*/
    FLEXIO_SPI_HAL_SetTxDmaCmd(&(spiState->spiDev), true);
    FLEXIO_SPI_HAL_SetRxDmaCmd(&(spiState->spiDev), true);
    return kStatus_FlexIO_SPI_Success;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_DmaGetReceiveStatus
 * Description   : This function returns whether the previous SPI receive is
 * complete. When performing an sync receive, the user can call this function
 * to ascertain the state of the current receive progress: in progress (or busy)
 * or complete (success). In addition, if the receive is still in progress,
 * the user can obtain the number of words that have been currently received.
 *
 *END**************************************************************************/
flexio_spi_status_t FLEXIO_SPI_DRV_DmaGetReceiveStatus(flexio_spi_state_t * spiState,
                                           uint32_t * bytesRemaining)
{
    if(spiState == NULL)
    {
        return kStatus_FlexIO_SPI_InvalidParam;
    }

    /* Fill in the bytes transferred. */
    if (bytesRemaining)
    {
        *bytesRemaining = DMA_DRV_GetUnfinishedBytes(&spiState->dmaSpiRx);
    }

    return (spiState->isRxBusy ? kStatus_FlexIO_SPI_RxBusy : kStatus_FlexIO_SPI_Success);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_DmaAbortReceivingData
 * Description   : This function shuts down the SPI by disabling interrupts and
 * the transmitter/receiver.
 *
 *END**************************************************************************/
flexio_spi_status_t FLEXIO_SPI_DRV_DmaAbortReceivingData(flexio_spi_state_t * spiState)
{
    if(spiState == NULL)
    {
        return kStatus_FlexIO_SPI_InvalidParam;
    }

    /* Check if a transfer is running. */
    if (!spiState->isRxBusy)
    {
        return kStatus_FlexIO_SPI_NoReceiveInProgress;
    }

    /* Stop DMA channel. */
    DMA_DRV_StopChannel(&spiState->dmaSpiRx);
    /* Disable SPI Rx DMA interrupt*/
    FLEXIO_SPI_HAL_SetTxDmaCmd(&(spiState->spiDev), false);
    /* Stop the running transfer. */
    FLEXIO_SPI_DRV_CompleteReceiveData(spiState);

    return kStatus_FlexIO_SPI_Success;
}
#endif
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_TX_IRQHandler
 * Description   : Interrupt spiState for SDO for FlexIO SPI device.
 * This spiState uses the buffers stored in the flexio_spi_state_t struct to send
 * data. This is not a public API as it is called whenever an interrupt occurs.
 *
 *END**************************************************************************/
void FLEXIO_SPI_DRV_TX_IRQHandler(void *param)
{
    flexio_spi_state_t *spiState = (flexio_spi_state_t *)param;
    uint32_t tmp;
    if(spiState == NULL)
    {
        return;
    }

    /* Exit the ISR if no transfer is happening for this instance. */
    if ((!spiState->isTxBusy)&& (!spiState->isXBusy))
    {
        return;
    }
    /* Handle transmit data register empty interrupt */
    if(spiState->dataSize == kFlexIOSpi8BitMode)
    {
          --spiState->txSize;
        /* Check to see if there are any more bytes to send */
        if (spiState->txSize)
        {
            /* Transmit data and update tx size/buff */
            ++spiState->txBuff;
            if(spiState->bitDirection == kFlexIOSpiMsbFirst)
            {
                tmp = *(spiState->txBuff);
                FLEXIO_SPI_HAL_PutDataMSB(&(spiState->spiDev), tmp<<24);
            }
            else
            {
                FLEXIO_SPI_HAL_PutDataLSB(&(spiState->spiDev), *(spiState->txBuff));
            }
        }
        else
        {
            if(spiState->isTxBusy)
            {
                FLEXIO_SPI_DRV_CompleteSendData(spiState);
            }
            if(spiState->isXBusy)
            {
                FLEXIO_SPI_HAL_SetTxBufferEmptyIntCmd(&(spiState->spiDev), false);
            }
        }
    }
    else
    {
        spiState->txSize = spiState->txSize - 2;
        if(spiState->txSize)
        {
            spiState->txBuff += 2;
            if(spiState->bitDirection == kFlexIOSpiMsbFirst)
            {
                tmp = *((const uint16_t *)(spiState->txBuff));
                FLEXIO_SPI_HAL_PutDataMSB(&(spiState->spiDev), tmp<<16);
            }
            else
            {
                FLEXIO_SPI_HAL_PutDataLSB(&(spiState->spiDev), *((const uint16_t *)(spiState->txBuff)));
            }
        }
        else
        {
            if(spiState->isTxBusy)
            {
                FLEXIO_SPI_DRV_CompleteSendData(spiState);
            }
            if(spiState->isXBusy)
            {
                FLEXIO_SPI_HAL_SetTxBufferEmptyIntCmd(&(spiState->spiDev), false);
            }
        }
    }
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_RX_IRQHandler
 * Description   : Interrupt spiState for SDI for FlexIO SPI device.
 * This spiState uses the buffers stored in the flexio_uart_state_t struct to transfer
 * data. This is not a public API as it is called whenever an interrupt occurs.
 *
 *END**************************************************************************/
void FLEXIO_SPI_DRV_RX_IRQHandler(void *param)
{
    flexio_spi_state_t *spiState = (flexio_spi_state_t *)param;
    if(spiState == NULL)
    {
        return;
    }

    /* Exit the ISR if no transfer is happening for this instance. */
    if ((!(spiState->isRxBusy))&&(!(spiState->isXBusy)))
    {
        return;
    }
    /* Handle transmit data register empty interrupt */
    if(spiState->dataSize == kFlexIOSpi8BitMode)
    {
        *(spiState->rxBuff) = FLEXIO_SPI_HAL_GetDataMSB(&(spiState->spiDev));
        ++spiState->rxBuff;
        --spiState->rxSize;
        if(spiState->rxSize == 0)
        {
            if(spiState->isRxBusy)
            {
                FLEXIO_SPI_DRV_CompleteReceiveData(spiState);
            }
            if(spiState->isXBusy)
            {
                FLEXIO_SPI_DRV_CompleteTransferData(spiState);
            }
            if (spiState->rxCallback != NULL)
            {
                spiState->rxCallback(spiState);
            }
        }
    }
    else
    {
       *((uint16_t *)(spiState->rxBuff)) = FLEXIO_SPI_HAL_GetDataMSB(&(spiState->spiDev));
       spiState->rxBuff += 2;
       spiState->rxSize -= 2;
       if(spiState->rxSize == 0)
       {
           if(spiState->isRxBusy)
           {
               FLEXIO_SPI_DRV_CompleteReceiveData(spiState);
           }
           if(spiState->isXBusy)
           {
               FLEXIO_SPI_DRV_CompleteTransferData(spiState);
           }
           if (spiState->rxCallback != NULL)
           {
               spiState->rxCallback(spiState);
           }
       }
    }
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_TxConfigDMA
 * Description   : Configure DMA for flexio SPI Tx port.
 * This function allocates DMA channel and register dma callback.
 *END**************************************************************************/
static flexio_spi_status_t FLEXIO_SPI_DRV_TxConfigDMA(flexio_spi_state_t *spiState)
{
    uint32_t ret;
    /* Request channel for Tx DMA */
    dma_request_source_t baseSource;
#if defined FSL_FEATURE_EDMA_MODULE_CHANNEL
    baseSource = kDmaRequestMux0Group1FlexIO0Channel0;
#else
    baseSource =kDmaRequestMux0FlexIOChannel0;
#endif
    dma_request_source_t source = (dma_request_source_t)((uint32_t)baseSource + spiState->spiDev.shifterIdx[0]);
#if defined FSL_FEATURE_EDMA_MODULE_CHANNEL
    ret = EDMA_DRV_RequestChannel(kEDMAAnyChannel, source, &spiState->edmaSpiTx);
    if (ret == kEDMAInvalidChannel)
    {
        return kStatus_FlexIO_SPI_DmaRequestFail ;
    }
    EDMA_DRV_InstallCallback(&spiState->edmaSpiTx, FLEXIO_SPI_DRV_EdmaTxCallback, spiState);
#else
    ret = DMA_DRV_RequestChannel(kDmaAnyChannel, source, &spiState->dmaSpiTx);
    if (ret == kDmaInvalidChannel)
    {
        return kStatus_FlexIO_SPI_DmaRequestFail ;
    }
    DMA_DRV_RegisterCallback(&spiState->dmaSpiTx, FLEXIO_SPI_DRV_DmaTxCallback, spiState);
#endif
    spiState->isTxUseDma = true;
    return kStatus_FlexIO_SPI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_RxConfigDMA
 * Description   : Configure DMA for flexio SPI Rx port.
 * This function allocates DMA channel and register dma callback.
 *END**************************************************************************/
static flexio_spi_status_t FLEXIO_SPI_DRV_RxConfigDMA(flexio_spi_state_t *spiState)
{
    uint32_t ret;
    /* Request channel for Tx DMA */
    dma_request_source_t baseSource;
#if defined FSL_FEATURE_EDMA_MODULE_CHANNEL
    baseSource = kDmaRequestMux0Group1FlexIO0Channel0;
#else
    baseSource =kDmaRequestMux0FlexIOChannel0;
#endif
    dma_request_source_t source = (dma_request_source_t)((uint32_t)baseSource + spiState->spiDev.shifterIdx[1]);
#if defined FSL_FEATURE_EDMA_MODULE_CHANNEL
    ret = EDMA_DRV_RequestChannel(kEDMAAnyChannel, source, &spiState->edmaSpiRx);
    if (ret == kEDMAInvalidChannel)
    {
        return kStatus_FlexIO_SPI_DmaRequestFail;
    }
    EDMA_DRV_InstallCallback(&spiState->edmaSpiRx, FLEXIO_SPI_DRV_EdmaRxCallback, spiState);
#else
    ret = DMA_DRV_RequestChannel(kDmaAnyChannel, source, &spiState->dmaSpiRx);
    if (ret == kDmaInvalidChannel)
    {
        return kStatus_FlexIO_SPI_DmaRequestFail;
    }
    DMA_DRV_RegisterCallback(&spiState->dmaSpiRx, FLEXIO_SPI_DRV_DmaRxCallback, spiState);
#endif
    spiState->isRxUseDma = true;
    return kStatus_FlexIO_SPI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_StartSendData
 * Description   : Initiate (start) a transmit by beginning the process of
 * sending data and enabling the interrupt.
 *
 *END**************************************************************************/
static flexio_spi_status_t FLEXIO_SPI_DRV_StartSendData(flexio_spi_state_t *spiState,
                                            const uint8_t * txBuff,
                                            uint32_t txSize)
{
    uint32_t tmp;
    /* Check that we're not busy already transmitting data from a previous
     * function call. */
    if (spiState->isTxBusy)
    {
        return kStatus_FlexIO_SPI_TxBusy;
    }

    if (txSize == 0U)
    {
        return kStatus_FlexIO_SPI_NoDataToDeal;
    }
    /* Initialize the module driver state structure. */
    spiState->txBuff = txBuff;
    spiState->txSize = txSize;
    spiState->isTxBusy = true;
    /* Make sure the transmit data register is empty and ready for data */
//    while(!FLEXIO_SPI_HAL_GetTxBufferEmptyFlag(&(spiState->spiDev))) { }

    /* Put the first data in shifter to start the transmission */
    if(spiState->bitDirection == kFlexIOSpiMsbFirst)
    {
      if(spiState->dataSize == kFlexIOSpi8BitMode)
      {
          tmp = *(spiState->txBuff);
          FLEXIO_SPI_HAL_PutDataMSB(&(spiState->spiDev), tmp<<24);
      }else
      {
          tmp = *((const uint16_t *)(spiState->txBuff));
          FLEXIO_SPI_HAL_PutDataMSB(&(spiState->spiDev), tmp<<16);   
      }
    }
    else
    {
      if(spiState->dataSize == kFlexIOSpi8BitMode)
      {
          FLEXIO_SPI_HAL_PutDataLSB(&(spiState->spiDev), *(spiState->txBuff));
      }else
      {
          FLEXIO_SPI_HAL_PutDataLSB(&(spiState->spiDev), *((const uint16_t *)(spiState->txBuff)));   
      }
    }
    /* Enable interrupt generation for tx shifter.  */
    FLEXIO_SPI_HAL_SetTxBufferEmptyIntCmd(&(spiState->spiDev), true);
    FLEXIO_DRV_Start(0);
    return kStatus_FlexIO_SPI_Success;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_StartReceiveData
 * Description   : Initiate (start) a receive by beginning the process of
 * receiving data and enabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static flexio_spi_status_t FLEXIO_SPI_DRV_StartReceiveData(flexio_spi_state_t *spiState,
                                               uint8_t * rxBuff,
                                               uint32_t rxSize)
{
    if(spiState == NULL)
    {
        return kStatus_FlexIO_SPI_InvalidParam;
    }

    /* Check that we're not busy receiving data from a previous function call. */
    if ((spiState->isRxBusy) && (!spiState->rxCallback))
    {
        return kStatus_FlexIO_SPI_RxBusy;
    }

    if (rxSize == 0U)
    {
        return kStatus_FlexIO_SPI_NoDataToDeal;
    }

    /* Initialize the module driver state struct to indicate transfer in progress
     * and with the buffer and byte count data */
    spiState->rxBuff = rxBuff;
    spiState->rxSize = rxSize;
    spiState->isRxBusy = true;

    /* Enable the receive data full interrupt */
    FLEXIO_SPI_HAL_SetRxBufferFullIntCmd(&(spiState->spiDev), true);
   // FLEXIO_DRV_Start(0);

    return kStatus_FlexIO_SPI_Success;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_StartTransferData
 * Description   : Initiate (start) a receive by beginning the process of
 * receiving data and enabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static flexio_spi_status_t FLEXIO_SPI_DRV_StartTransferData(flexio_spi_state_t *spiState,
                                               const uint8_t *txBuff,uint8_t * rxBuff,
                                               uint32_t xSize)
{
    uint32_t tmp;
    if(spiState == NULL)
    {
        return kStatus_FlexIO_SPI_InvalidParam;
    }

    /* Check that we're not busy transferring data from a previous function call. */
    if ((spiState->isXBusy) && (!spiState->rxCallback))
    {
        return kStatus_FlexIO_SPI_XBusy;
    }

    if (xSize == 0U)
    {
        return kStatus_FlexIO_SPI_NoDataToDeal;
    }

    /* Initialize the module driver state struct to indicate transfer in progress
     * and with the buffer and byte count data */
    spiState->txBuff = txBuff;
    spiState->txSize = xSize;
    spiState->rxBuff = rxBuff;
    spiState->rxSize = xSize;
    spiState->isXBusy = true;

    /* Make sure the transmit data register is empty and ready for data */
//    while(!FLEXIO_SPI_HAL_GetTxBufferEmptyFlag(&(spiState->spiDev))) { }

    /* Put the first data in shifter to start the transmission */
    if(spiState->bitDirection == kFlexIOSpiMsbFirst)
    {
      if(spiState->dataSize == kFlexIOSpi8BitMode)
      {
          tmp = *(spiState->txBuff);
          FLEXIO_SPI_HAL_PutDataMSB(&(spiState->spiDev), tmp<<24);
      }else
      {
          tmp = *((const uint16_t *)(spiState->txBuff));
          FLEXIO_SPI_HAL_PutDataMSB(&(spiState->spiDev), tmp<<16);   
      }
    }
    else
    {
      if(spiState->dataSize == kFlexIOSpi8BitMode)
      {
          FLEXIO_SPI_HAL_PutDataLSB(&(spiState->spiDev), *(spiState->txBuff));
      }else
      {
          FLEXIO_SPI_HAL_PutDataLSB(&(spiState->spiDev), *((const uint16_t *)(spiState->txBuff)));   
      }
    }
    /* Enable the send data empty and receive data full interrupt */
    FLEXIO_SPI_HAL_SetTxBufferEmptyIntCmd(&(spiState->spiDev), true);
    FLEXIO_SPI_HAL_SetRxBufferFullIntCmd(&(spiState->spiDev), true);
    if(spiState->mode == kFlexIOSpiMaster)
   {
    FLEXIO_DRV_Start(0);
    }
    return kStatus_FlexIO_SPI_Success;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_CompleteSendData
 * Description   : Finish up a transmit by completing the process of sending
 * data and disabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void FLEXIO_SPI_DRV_CompleteSendData(flexio_spi_state_t *spiState)
{
    if(spiState == NULL)
    {
        return;
    }

    /* Disable the transmitter data register empty interrupt */
    FLEXIO_SPI_HAL_SetTxBufferEmptyIntCmd(&(spiState->spiDev), false);

    /* Signal the synchronous completion object. */
    if (spiState->isTxBlocking)
    {
        OSA_SemaPost(&spiState->txIrqSync);
    }

    /* Update the information of the module driver state */
    spiState->isTxBusy = false;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_CompleteReceiveData
 * Description   : Finish up a receive by completing the process of receiving
 * data and disabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void FLEXIO_SPI_DRV_CompleteReceiveData(flexio_spi_state_t *spiState)
{
    if(spiState == NULL)
    {
        return;
    }

    /* Disable receive data full interrupt */
    FLEXIO_SPI_HAL_SetRxBufferFullIntCmd(&(spiState->spiDev), false);

    /* Signal the synchronous completion object. */
    if (spiState->isRxBlocking)
    {
        OSA_SemaPost(&spiState->rxIrqSync);
    }

    /* Update the information of the module driver state */
    spiState->isRxBusy = false;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_SPI_DRV_CompleteTransferData
 * Description   : Finish up a transfer by completing the process of transferring
 * data and disabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void FLEXIO_SPI_DRV_CompleteTransferData(flexio_spi_state_t *spiState)
{
    if(spiState == NULL)
    {
        return;
    }

    /* Disable receive data&send data full interrupt */
    FLEXIO_SPI_HAL_SetRxBufferFullIntCmd(&(spiState->spiDev), false);
    FLEXIO_SPI_HAL_SetTxBufferEmptyIntCmd(&(spiState->spiDev), false);
    /* Signal the synchronous completion object. */
    if (spiState->isXBlocking)
    {
        OSA_SemaPost(&spiState->xIrqSync);
    }

    /* Update the information of the module driver state */
    spiState->isXBusy = false;
}
