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
#include "fsl_flexio_uart_edma_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"
#include "fsl_edma_request.h"
#if FSL_FEATURE_SOC_EDMA_COUNT

static void FLEXIO_UART_DRV_EdmaCompleteSendData(flexio_uart_edmastate_t *uartEdmaState);
static void FLEXIO_UART_DRV_EdmaTxCallback(void *param, edma_chn_status_t status);
static flexio_uart_status_t FLEXIO_UART_DRV_EdmaStartSendData(flexio_uart_edmastate_t *uartEdmaState, 
                                                const uint8_t * txBuff,
                                                uint32_t txSize);
static void FLEXIO_UART_DRV_EdmaCompleteReceiveData(flexio_uart_edmastate_t *uartEdmaState);
static void FLEXIO_UART_DRV_EdmaRxCallback(void *param, edma_chn_status_t status);
static flexio_uart_status_t FLEXIO_UART_DRV_EdmaStartReceiveData(flexio_uart_edmastate_t *uartEdmaState,
                                                   uint8_t * rxBuff,
                                                   uint32_t rxSize);
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_EdmaInit
 * Description   : This function initializes a UART device for operation.
 * This function will initialize the run-time state structure to keep track of
 * the on-going transfers, ungate the clock to the UART module, initialize the
 * module to user defined settings and default settings, configure the IRQ state
 * structure and enable the module-level interrupt to the core, and enable the
 * UART module transmitter and receiver.
 * The following is an example of how to set up the flexio_uart_edmastate_t and the
 * flexio_uartedma_userconfig_t parameters and how to call the flexio_uart_edmastate_t function by
 * passing in these parameters:
 *    flexio_uartedma_userconfig_t uartEdmaConfig;
 *    uartEdmaConfig.baudRate = 9600;
 *    uartEdmaConfig.bitCountPerChar = kUart8BitsPerChar;
 *    flexio_uart_edmastate_t uartEdmaState;
 *    FLEXIO_UART_DRV_EdmaInit(instance, &uartEdmaState, &uartEdmaConfig);
 *
 *END**************************************************************************/
flexio_uart_status_t FLEXIO_UART_DRV_EdmaInit(uint32_t instance,flexio_uart_edmastate_t *uartEdmaState, const flexio_uartedma_userconfig_t *uartEdmaConfig)
{
    if((uartEdmaState == NULL)||(uartEdmaConfig == NULL))
    {
        return kStatus_FlexIO_UART_InvalidParam;
    }

    FLEXIO_Type* base = g_flexioBase[instance];
    uint32_t flexioSourceClock;
    flexio_uart_config_t devConfig;
    /*Reset the uartEdmaState structure*/
    memset(uartEdmaState,0,sizeof(*uartEdmaState));
    /* Create Semaphore for txIrq and rxIrq. */
    OSA_SemaCreate(&uartEdmaState->txIrqSync, 0);
    OSA_SemaCreate(&uartEdmaState->rxIrqSync, 0);  
    /* Get FlexIO clock frequency for baudrate caculation*/  
    flexioSourceClock = CLOCK_SYS_GetFlexioFreq(instance);
    uartEdmaState->mode = uartEdmaConfig->uartMode;
    devConfig.flexioBusClk = flexioSourceClock;
    devConfig.baudrate = uartEdmaConfig->baudRate;
    devConfig.bitCount = uartEdmaConfig->bitCounter;
    /*Configure buadrate, bit count and hardware resource including pin, shifter and timer for Tx module*/
    if((uartEdmaConfig->uartMode == flexioUART_TxOnly)||(uartEdmaConfig->uartMode == flexioUART_TxRx))
    {
        uartEdmaState->txDev.flexioBase = base;
        uartEdmaState->txDev.txPinIdx = uartEdmaConfig->txConfig.pinIdx;
        uartEdmaState->txDev.shifterIdx = uartEdmaConfig->txConfig.shifterIdx;
        uartEdmaState->txDev.timerIdx = uartEdmaConfig->txConfig.timerIdx;
        FLEXIO_UART_Tx_HAL_Configure(&(uartEdmaState->txDev), &devConfig);
    }
    /*Configure buadrate, bit count and hardware resource including pin, shifter and timer for Rx module*/
    if((uartEdmaConfig->uartMode == flexioUART_RxOnly)||(uartEdmaConfig->uartMode == flexioUART_TxRx))
    {
        uartEdmaState->rxDev.flexioBase = base;
        uartEdmaState->rxDev.rxPinIdx = uartEdmaConfig->rxConfig.pinIdx;
        uartEdmaState->rxDev.shifterIdx = uartEdmaConfig->rxConfig.shifterIdx;
        uartEdmaState->rxDev.timerIdx = uartEdmaConfig->rxConfig.timerIdx;
        FLEXIO_UART_Rx_HAL_Configure(&(uartEdmaState->rxDev), &devConfig);
    }
    dma_request_source_t uartTxEdmaRequest;
    dma_request_source_t uartRxEdmaRequest;
    dma_request_source_t dmaRequestBase = kDmaRequestMux0Group1FlexIO0Channel0;
    switch (instance)
    {
        case 0:
            uartRxEdmaRequest = (dma_request_source_t)(dmaRequestBase + uartEdmaState->rxDev.shifterIdx);
            uartTxEdmaRequest = (dma_request_source_t)(dmaRequestBase + uartEdmaState->txDev.shifterIdx);
            break;
        default :
            break;
    }
 /*--------------- Setup RX ------------------*/
    /* Request DMA channels for RX FIFO. */
    EDMA_DRV_RequestChannel(kEDMAAnyChannel, uartRxEdmaRequest,
                            &uartEdmaState->edmaUartRx);
    EDMA_DRV_InstallCallback(&uartEdmaState->edmaUartRx,
                    FLEXIO_UART_DRV_EdmaRxCallback, (void *)uartEdmaState);

    /*--------------- Setup TX ------------------*/
    /* Request DMA channels for TX FIFO. */
    EDMA_DRV_RequestChannel(kEDMAAnyChannel, uartTxEdmaRequest,
                            &uartEdmaState->edmaUartTx);
    EDMA_DRV_InstallCallback(&uartEdmaState->edmaUartTx,
                    FLEXIO_UART_DRV_EdmaTxCallback, (void *)uartEdmaState); 
    /* Finally, enable the UART transmitter and receiver.
     * Enable DMA trigger when transmit data register empty, 
     * and receive data register full. */
    FLEXIO_UART_Tx_HAL_SetTxDmaCmd(&(uartEdmaState->txDev), true);
    FLEXIO_UART_Rx_HAL_SetRxDmaCmd(&(uartEdmaState->rxDev), true);
    return kStatus_FlexIO_UART_Success;
}
void FLEXIO_UART_DRV_Deinit(flexio_uart_edmastate_t *uartEdmaState)
{
    if(uartEdmaState == NULL)
    {
        return;
    }
    FLEXIO_UART_Tx_HAL_SetTxDmaCmd(&(uartEdmaState->txDev), false);
    FLEXIO_UART_Rx_HAL_SetRxDmaCmd(&(uartEdmaState->rxDev), false);
     /* Release DMA channel. */
    EDMA_DRV_ReleaseChannel(&uartEdmaState->edmaUartRx);
    EDMA_DRV_ReleaseChannel(&uartEdmaState->edmaUartTx);
	  /* Destroy TX and RX sema. */
    OSA_SemaDestroy(&uartEdmaState->txIrqSync);
    OSA_SemaDestroy(&uartEdmaState->rxIrqSync);
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_EdmaSendDataBlocking
 * Description   :  Sends (transmits) data out through the UART-DMA module
 * using a blocking method.  
 * 
 *END**************************************************************************/
flexio_uart_status_t FLEXIO_UART_DRV_EdmaSendDataBlocking(flexio_uart_edmastate_t *uartEdmaState,
                                            const uint8_t * txBuff,
                                            uint32_t txSize,
                                            uint32_t timeout)
{
    if((uartEdmaState == NULL)||(txBuff == NULL))
    {
        return kStatus_FlexIO_UART_InvalidParam;
    }

    flexio_uart_status_t retVal = kStatus_FlexIO_UART_Success;
    osa_status_t syncStatus;

    /* Indicates current transaction is blocking. */
    uartEdmaState->isTxBlocking = true;

    /* Start the transmission process */
    retVal = FLEXIO_UART_DRV_EdmaStartSendData(uartEdmaState, txBuff, txSize);

    if (retVal == kStatus_FlexIO_UART_Success)
    {
        /* Wait until the transmit is complete. */
        do
        {
            syncStatus = OSA_SemaWait(&uartEdmaState->txIrqSync, timeout);
        }while(syncStatus == kStatus_OSA_Idle);

        if (syncStatus != kStatus_OSA_Success)
        {

            /* Stop DMA channel. */
            EDMA_DRV_StopChannel(&uartEdmaState->edmaUartTx);
               
            /* Update the information of the module driver state */
            uartEdmaState->isTxBusy = false; 

            retVal = kStatus_FlexIO_UART_Timeout;
        }
    }

    return retVal;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_EdmaSendData
 * Description   : This function sends (transmits) data through the UART module
 *                 using a non-blocking method.
 * A non-blocking (also known as synchronous) function means that the function
 * returns immediately after initiating the transmit function. The application
 * has to get the transmit status to see when the transmit is complete. In
 * other words, after calling non-blocking (asynchronous) send function, the
 * application must get the transmit status to check if transmit is completed
 * or not. The asynchronous method of transmitting and receiving allows the UART
 * to perform a full duplex operation (simultaneously transmit and receive).
 *
 *END**************************************************************************/
flexio_uart_status_t FLEXIO_UART_DRV_EdmaSendData(flexio_uart_edmastate_t *uartEdmaState,
                                    const uint8_t * txBuff,
                                    uint32_t txSize)
{
    if((uartEdmaState == NULL)||(txBuff == NULL))
    {
        return kStatus_FlexIO_UART_InvalidParam;
    }
    flexio_uart_status_t retVal = kStatus_FlexIO_UART_Success;

    /* Indicates current transaction is non-blocking. */
    uartEdmaState->isTxBlocking = false;

    /* Start the transmission process*/
    retVal = FLEXIO_UART_DRV_EdmaStartSendData(uartEdmaState, txBuff, txSize);

    return retVal;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_EdmaGetTransmitStatus
 * Description   : This function returns whether the previous UART transmit
 * has finished. When performing an async transmit, the user can call this 
 * function to ascertain the state of the current transmission: in progress
 * (or busy) or complete (success). In addition, if the transmission is still
 * in progress, the user can obtain the number of words that have been
 * currently transferred.
 *
 *END**************************************************************************/
flexio_uart_status_t FLEXIO_UART_DRV_EdmaGetTransmitStatus(flexio_uart_edmastate_t *uartEdmaState,
                                             uint32_t * bytesRemaining)
{
    if(uartEdmaState == NULL)
    {
        return kStatus_FlexIO_UART_InvalidParam;
    }

    flexio_uart_status_t retVal = kStatus_FlexIO_UART_Success;
    uint32_t txSize = EDMA_DRV_GetUnfinishedBytes(&uartEdmaState->edmaUartTx);

    /* Fill in the bytes transferred. */
    if (bytesRemaining)
    {
        *bytesRemaining = txSize;
    }

    if (txSize)
    {
        retVal = kStatus_FlexIO_UART_TxBusy;
    }

    return retVal;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_EdmaAbortSendingData
 * Description   : This function terminates an asynchronous UART transmission
 * early. During an async UART transmission, the user has the option to
 * terminate the transmission early if the transmission is still in progress.
 *
 *END**************************************************************************/
flexio_uart_status_t FLEXIO_UART_DRV_EdmaAbortSendingData(flexio_uart_edmastate_t *uartEdmaState)
{
    if(uartEdmaState == NULL)
    {
        return kStatus_FlexIO_UART_InvalidParam;
    }

    /* Check if a transfer is running. */
    if (!uartEdmaState->isTxBusy)
    {
        return kStatus_FlexIO_UART_NoTransmitInProgress;
    }

    /* Stop the running transfer. */
    FLEXIO_UART_DRV_EdmaCompleteSendData(uartEdmaState);

    return kStatus_FlexIO_UART_Success;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_EdmaReceiveDataBlocking
 * Description   : This function gets (receives) data from the UART module using
 * a blocking method. A blocking (also known as synchronous) function means that
 * the function does not return until the receive is complete. This blocking
 * function is used to send data through the UART port.
 *
 *END**************************************************************************/
flexio_uart_status_t FLEXIO_UART_DRV_EdmaReceiveDataBlocking(flexio_uart_edmastate_t *uartEdmaState,
                                               uint8_t * rxBuff,
                                               uint32_t rxSize,
                                               uint32_t timeout)
{
    if((uartEdmaState == NULL)||(rxBuff == NULL))
    {
        return kStatus_FlexIO_UART_InvalidParam;
    }

    flexio_uart_status_t retVal = kStatus_FlexIO_UART_Success;
    osa_status_t syncStatus;

    /* Indicates current transaction is blocking. */
    uartEdmaState->isRxBlocking = true;

    retVal = FLEXIO_UART_DRV_EdmaStartReceiveData(uartEdmaState, rxBuff, rxSize);

    if (retVal == kStatus_FlexIO_UART_Success)
    {
        /* Wait until all the data is received or for timeout.*/
        do
        {
            syncStatus = OSA_SemaWait(&uartEdmaState->rxIrqSync, timeout);
        }while(syncStatus == kStatus_OSA_Idle);

        if (syncStatus != kStatus_OSA_Success)
        {
            /* Stop DMA channel. */
            EDMA_DRV_StopChannel(&uartEdmaState->edmaUartRx);

            /* Update the information of the module driver state */
            uartEdmaState->isRxBusy = false;

            retVal = kStatus_FlexIO_UART_Timeout;
        }
    }

    return retVal;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_EdmaReceiveData
 * Description   : This function gets (receives) data from the UART module using
 * a non-blocking method.
 * A non-blocking (also known as synchronous) function means that the function
 * returns immediately after initiating the receive function. The application 
 * has to get the receive status to see when the receive is complete. In other
 * words, after calling non-blocking (asynchronous) get function, the 
 * application must get the receive status to check if receive is completed or
 * not. The asynchronous method of transmitting and receiving allows the UART 
 * to perform a full duplex operation (simultaneously transmit and receive).
 *
 *END**************************************************************************/
flexio_uart_status_t FLEXIO_UART_DRV_EdmaReceiveData(flexio_uart_edmastate_t *uartEdmaState,
                                       uint8_t * rxBuff,
                                       uint32_t rxSize)
{
    if((uartEdmaState == NULL)||(rxBuff == NULL))
    {
        return kStatus_FlexIO_UART_InvalidParam;
    }

    flexio_uart_status_t retVal = kStatus_FlexIO_UART_Success;

    /* Indicates current transaction is non-blocking. */
    uartEdmaState->isRxBlocking = false;

    retVal = FLEXIO_UART_DRV_EdmaStartReceiveData(uartEdmaState, rxBuff, rxSize);
    
    return retVal;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_EdmaGetReceiveStatus
 * Description   : This function returns whether the previous UART receive is
 * complete. When performing an async receive, the user can call this function 
 * to ascertain the state of the current receive progress: in progress (or busy)
 * or complete (success). In addition, if the receive is still in progress,
 * the user can obtain the number of words that have been currently received.
 *
 *END**************************************************************************/
flexio_uart_status_t FLEXIO_UART_DRV_EdmaGetReceiveStatus(flexio_uart_edmastate_t *uartEdmaState,
                                            uint32_t * bytesRemaining)
{
    if(uartEdmaState == NULL)
    {
        return kStatus_FlexIO_UART_InvalidParam;
    }

    flexio_uart_status_t retVal = kStatus_FlexIO_UART_Success;
    uint32_t rxSize = EDMA_DRV_GetUnfinishedBytes(&uartEdmaState->edmaUartRx);

    /* Fill in the bytes transferred. */
    if (bytesRemaining)
    {
        *bytesRemaining = rxSize;
    }

    if (rxSize)
    {
        retVal = kStatus_FlexIO_UART_RxBusy;
    }

    return retVal;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_EdmaAbortReceivingData
 * Description   : This function shuts down the UART by disabling interrupts and
 * the transmitter/receiver.
 *
 *END**************************************************************************/
flexio_uart_status_t FLEXIO_UART_DRV_EdmaAbortReceivingData(flexio_uart_edmastate_t *uartEdmaState)
{
    if(uartEdmaState == NULL)
    {
        return kStatus_FlexIO_UART_InvalidParam;
    }

    /* Check if a transfer is running. */
    if (!uartEdmaState->isRxBusy)
    {
        return kStatus_FlexIO_UART_NoReceiveInProgress;
    }

    /* Stop the running transfer. */
    FLEXIO_UART_DRV_EdmaCompleteReceiveData(uartEdmaState);

    return kStatus_FlexIO_UART_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_EdmaCompleteSendData
 * Description   : Finish up a transmit by completing the process of sending 
 * data and disabling the interrupt. 
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void FLEXIO_UART_DRV_EdmaCompleteSendData(flexio_uart_edmastate_t *uartEdmaState)
{
    if(uartEdmaState == NULL)
    {
        return;
    }
    /* Stop DMA channel. */
    EDMA_DRV_StopChannel(&uartEdmaState->edmaUartTx);
    /* Signal the synchronous completion object. */
    if (uartEdmaState->isTxBlocking)
    {
        OSA_SemaPost(&uartEdmaState->txIrqSync);
    }

    /* Update the information of the module driver state */
    uartEdmaState->isTxBusy = false; 
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_EdmaTxCallback
 * Description   : This is not a public interface.
 *
 *END**************************************************************************/
static void FLEXIO_UART_DRV_EdmaTxCallback(void *param, edma_chn_status_t status)
{
    FLEXIO_UART_DRV_EdmaCompleteSendData((flexio_uart_edmastate_t *)param);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_EdmaStartSendData
 * Description   : This is not a public interface.
 *
 *END**************************************************************************/
static flexio_uart_status_t FLEXIO_UART_DRV_EdmaStartSendData(flexio_uart_edmastate_t *uartEdmaState, 
                                                const uint8_t * txBuff,
                                                uint32_t txSize)
{
    if(uartEdmaState == NULL)
    {
        return kStatus_FlexIO_UART_InvalidParam;
    }

    /* Check that we're not busy already transmitting data from a previous function call. */
    if (uartEdmaState->isTxBusy)
    {
        return kStatus_FlexIO_UART_TxBusy;
    }
  
    /* Update UART DMA run-time structure. */
    uartEdmaState->isTxBusy = true;
    /* Configure DMA module */
    edma_software_tcd_t edmaTxTcd;
    memset(&edmaTxTcd, 0, sizeof( edma_software_tcd_t));
    edma_transfer_config_t txConfig;
    txConfig.srcLastAddrAdjust = 0;
    txConfig.destLastAddrAdjust = 0;
    txConfig.srcModulo = kEDMAModuloDisable;
    txConfig.destModulo = kEDMAModuloDisable;
    txConfig.srcTransferSize = kEDMATransferSize_1Bytes;
    txConfig.destTransferSize = kEDMATransferSize_1Bytes;
    txConfig.minorLoopCount = 1;
    txConfig.majorLoopCount = txSize;
    txConfig.srcAddr = (uint32_t)(txBuff);
    txConfig.srcOffset = 1;
    txConfig.destAddr = FLEXIO_UART_Tx_HAL_GetTxBufferAddr(&(uartEdmaState->txDev));
    txConfig.destOffset = 0;
    EDMA_DRV_PrepareDescriptorTransfer(&uartEdmaState->edmaUartTx, &edmaTxTcd, &txConfig, true, true);
    EDMA_DRV_PushDescriptorToReg(&uartEdmaState->edmaUartTx, &edmaTxTcd);
    EDMA_DRV_StartChannel(&uartEdmaState->edmaUartTx);

    return kStatus_FlexIO_UART_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_EdmaCompleteReceiveData
 * Description   : Finish up a receive by completing the process of receiving data
 * and disabling the interrupt. 
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void FLEXIO_UART_DRV_EdmaCompleteReceiveData(flexio_uart_edmastate_t *uartEdmaState)
{
    if(uartEdmaState == NULL)
    {
        return;
    }

    /* Stop DMA channel. */
    EDMA_DRV_StopChannel(&uartEdmaState->edmaUartRx);

    /* Signal the synchronous completion object. */
    if (uartEdmaState->isRxBlocking)
    {
        OSA_SemaPost(&uartEdmaState->rxIrqSync);
    }

    /* Update the information of the module driver state */
    uartEdmaState->isRxBusy = false;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_EdmaRxCallback
 * Description   : This is not a public interface.
 *
 *END**************************************************************************/
static void FLEXIO_UART_DRV_EdmaRxCallback(void *param, edma_chn_status_t status)
{
    FLEXIO_UART_DRV_EdmaCompleteReceiveData((flexio_uart_edmastate_t *)param);
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_EdmaStartReceiveData
 * Description   : Initiate (start) a receive by beginning the process of
 * receiving data and enabling the interrupt. 
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static flexio_uart_status_t FLEXIO_UART_DRV_EdmaStartReceiveData(flexio_uart_edmastate_t *uartEdmaState,
                                                   uint8_t * rxBuff,
                                                   uint32_t rxSize)
{
    if(uartEdmaState == NULL)
    {
        return kStatus_FlexIO_UART_InvalidParam;
    }

    /* Check that we're not busy already receiving data from a previous function call. */
    if (uartEdmaState->isRxBusy)
    {
        return kStatus_FlexIO_UART_RxBusy;
    }

    /* Update UART DMA run-time structure. */
    uartEdmaState->isRxBusy = true;

    /* Configure DMA module */
    edma_software_tcd_t edmaRxTcd;
    memset(&edmaRxTcd, 0, sizeof( edma_software_tcd_t));
    edma_transfer_config_t rxConfig;
    rxConfig.srcLastAddrAdjust = 0;
    rxConfig.destLastAddrAdjust = 0;
    rxConfig.srcModulo = kEDMAModuloDisable;
    rxConfig.destModulo = kEDMAModuloDisable;
    rxConfig.srcTransferSize = kEDMATransferSize_1Bytes;
    rxConfig.destTransferSize = kEDMATransferSize_1Bytes;
    rxConfig.minorLoopCount = 1;
    rxConfig.majorLoopCount = rxSize;
    rxConfig.srcAddr = FLEXIO_UART_Rx_HAL_GetRxBufferAddr(&(uartEdmaState->rxDev));
    rxConfig.srcOffset = 0;
    rxConfig.destAddr = (uint32_t)(rxBuff);
    rxConfig.destOffset = 1;
    EDMA_DRV_PrepareDescriptorTransfer(&uartEdmaState->edmaUartRx, &edmaRxTcd, &rxConfig, true, true);
    EDMA_DRV_PushDescriptorToReg(&uartEdmaState->edmaUartRx, &edmaRxTcd);
    EDMA_DRV_StartChannel(&uartEdmaState->edmaUartRx);

    return kStatus_FlexIO_UART_Success;
}
#endif

