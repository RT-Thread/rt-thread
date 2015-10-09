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
#include "fsl_flexio_uart_dma_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"
#include "fsl_dma_request.h"
#if FSL_FEATURE_SOC_DMA_COUNT

/*******************************************************************************
 * Private Functions
 ******************************************************************************/
static void FLEXIO_UART_DRV_DmaCompleteSendData(flexio_uart_dmastate_t * uartDmaState);
static void FLEXIO_UART_DRV_DmaTxCallback(void *param, dma_channel_status_t status);
static flexio_uart_status_t FLEXIO_UART_DRV_DmaStartSendData(flexio_uart_dmastate_t * uartDmaState,
                                               const uint8_t * txBuff,
                                               uint32_t txSize);
static void FLEXIO_UART_DRV_DmaCompleteReceiveData(flexio_uart_dmastate_t * uartDmaState);
static void FLEXIO_UART_DRV_DmaRxCallback(void *param, dma_channel_status_t status);
static flexio_uart_status_t FLEXIO_UART_DRV_DmaStartReceiveData(flexio_uart_dmastate_t * uartDmaState,
                                                  uint8_t * rxBuff,
                                                  uint32_t rxSize);
/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_DmaInit
 * Description   : Initializes a FLEXIO simulated UART device to work with DMA.
 * This function initializes the run-time state structure to keep track of the on-going
 * transfers, initializes the module to user-defined settings and default settings, 
 * configures underlying flexio Pin,shifter and timer resource and enables the FLEXIO
 * simulated UART module DMA interrupt.
 * The following is an example of how to set up the uart_dma_state_t and the
 * uart_user_config_t parameters and how to call the UART_DRV_DmaInit function
 * by passing in these parameters:
 *    uart_user_config_t uartConfig;
      flexio_uartdma_userconfig_t uartDmaConfig;
      uartDmaConfig.baudRate = 9600;
      uartDmaConfig.bitCountPerChar = kUart8BitsPerChar;
      uartDmaConfig.uartMode = flexioUART_TxRx;
 *    FLEXIO_UART_DRV_DmaInit(instance, &uartDmaState, &uartDmaConfig);
 *
 *END**************************************************************************/
flexio_uart_status_t FLEXIO_UART_DRV_DmaInit(uint32_t instance,
                               flexio_uart_dmastate_t * uartDmaState,
                               const flexio_uartdma_userconfig_t * uartDmaConfig)
{
    if(!(instance < FLEXIO_INSTANCE_COUNT))
    {
        return kStatus_FlexIO_UART_InvalidParam;
    }
    if((uartDmaState == NULL)||(uartDmaConfig == NULL))
    {
        return kStatus_FlexIO_UART_InvalidParam;
    }
    FLEXIO_Type* base = g_flexioBase[instance];
    uint32_t flexioSourceClock;
    flexio_uart_config_t devConfig;
    dma_request_source_t uartTxDmaRequest = kDmaRequestMux0Disable;
    dma_request_source_t uartRxDmaRequest = kDmaRequestMux0Disable;
    uint32_t dmaRequestBase = kDmaRequestMux0FlexIOChannel0;

    /* Clear the state structure for this instance. */
    memset(uartDmaState, 0, sizeof(flexio_uart_dmastate_t));

    /* Create Semaphore for txIrq and rxIrq. */
    OSA_SemaCreate(&uartDmaState->txIrqSync, 0);
    OSA_SemaCreate(&uartDmaState->rxIrqSync, 0);

     /* Get FlexIO clock frequency for baudrate caculation*/  
    flexioSourceClock = CLOCK_SYS_GetFlexioFreq(instance);
    uartDmaState->mode = uartDmaConfig->uartMode;
    devConfig.flexioBusClk = flexioSourceClock;
    devConfig.baudrate = uartDmaConfig->baudRate;
    devConfig.bitCount = uartDmaConfig->bitCountPerChar;

     /*Configure buadrate, bit count and hardware resource including pin, shifter and timer for Tx module*/
    if((uartDmaConfig->uartMode == flexioUART_TxOnly)||(uartDmaConfig->uartMode == flexioUART_TxRx))
    {
        uartDmaState->txDev.flexioBase = base;
        uartDmaState->txDev.txPinIdx = uartDmaConfig->txConfig.pinIdx;
        uartDmaState->txDev.shifterIdx = uartDmaConfig->txConfig.shifterIdx;
        uartDmaState->txDev.timerIdx = uartDmaConfig->txConfig.timerIdx;
        FLEXIO_UART_Tx_HAL_Configure(&(uartDmaState->txDev), &devConfig);
    }
    /*Configure buadrate, bit count and hardware resource including pin, shifter and timer for Rx module*/
    if((uartDmaConfig->uartMode == flexioUART_RxOnly)||(uartDmaConfig->uartMode == flexioUART_TxRx))
    {
        uartDmaState->rxDev.flexioBase = base;
        uartDmaState->rxDev.rxPinIdx = uartDmaConfig->rxConfig.pinIdx;
        uartDmaState->rxDev.shifterIdx = uartDmaConfig->rxConfig.shifterIdx;
        uartDmaState->rxDev.timerIdx = uartDmaConfig->rxConfig.timerIdx;
        FLEXIO_UART_Rx_HAL_Configure(&(uartDmaState->rxDev), &devConfig);
    }

    FLEXIO_UART_Tx_HAL_SetTxDmaCmd(&(uartDmaState->txDev), true);
    FLEXIO_UART_Rx_HAL_SetRxDmaCmd(&(uartDmaState->rxDev), true);

    switch (instance)
    {
        case 0:
            uartRxDmaRequest = (dma_request_source_t)(dmaRequestBase + uartDmaState->rxDev.shifterIdx);
            uartTxDmaRequest = (dma_request_source_t)(dmaRequestBase + uartDmaState->txDev.shifterIdx);
            break;
        default :
            break;
    }

    /* Request DMA channels for RX FIFO. */
    DMA_DRV_RequestChannel(kDmaAnyChannel, uartRxDmaRequest,
                            &uartDmaState->dmaUartRx);
    DMA_DRV_RegisterCallback(&uartDmaState->dmaUartRx,
                    FLEXIO_UART_DRV_DmaRxCallback, (void *)uartDmaState);

    /* Request DMA channels for TX FIFO. */
    DMA_DRV_RequestChannel(kDmaAnyChannel, uartTxDmaRequest,
                            &uartDmaState->dmaUartTx);
    DMA_DRV_RegisterCallback(&uartDmaState->dmaUartTx,
                    FLEXIO_UART_DRV_DmaTxCallback, (void *)uartDmaState);

    return kStatus_FlexIO_UART_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_DmaDeinit
 * Description   : This function disables the FLEXIO simulated UART-DMA trigger.
 *
 *END**************************************************************************/
void FLEXIO_UART_DRV_DmaDeinit(flexio_uart_dmastate_t * uartDmaState)
{
    if(uartDmaState == NULL)
    {
        return;
    }

    FLEXIO_UART_Tx_HAL_SetTxDmaCmd(&(uartDmaState->txDev), false);
    FLEXIO_UART_Rx_HAL_SetRxDmaCmd(&(uartDmaState->rxDev), false);
    /* Release DMA channel. */
    DMA_DRV_FreeChannel(&uartDmaState->dmaUartRx);
    DMA_DRV_FreeChannel(&uartDmaState->dmaUartTx);

    /* Destroy TX and RX sema. */
    OSA_SemaDestroy(&uartDmaState->txIrqSync);
    OSA_SemaDestroy(&uartDmaState->rxIrqSync);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_DmaSendDataBlocking
 * Description   :  Sends (transmits) data out through the FLEXIO simulated UART-DMA module 
 * using a blocking method.
 *
 *END**************************************************************************/
flexio_uart_status_t FLEXIO_UART_DRV_DmaSendDataBlocking(flexio_uart_dmastate_t * uartDmaState,
                                           const uint8_t * txBuff,
                                           uint32_t txSize,
                                           uint32_t timeout)
{
    if((uartDmaState == NULL)||(txBuff == NULL))
    {
        return kStatus_FlexIO_UART_InvalidParam;
    }

    flexio_uart_status_t retVal = kStatus_FlexIO_UART_Success;
    osa_status_t syncStatus;

    /* Indicates current transaction is blocking. */
    uartDmaState->isTxBlocking = true;

    /* Start the transmission process */
    retVal = FLEXIO_UART_DRV_DmaStartSendData(uartDmaState, txBuff, txSize);

    if (retVal == kStatus_FlexIO_UART_Success)
    {
        /* Wait until the transmit is complete. */
        do
        {
            syncStatus = OSA_SemaWait(&uartDmaState->txIrqSync, timeout);
        }while(syncStatus == kStatus_OSA_Idle);

        if (syncStatus != kStatus_OSA_Success)
        {
            /* Stop DMA channel. */
            DMA_DRV_StopChannel(&uartDmaState->dmaUartTx);

            /* Update the information of the module driver state */
            uartDmaState->isTxBusy = false;

            retVal = kStatus_FlexIO_UART_Timeout;
        }
    }

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_DmaSendData
 * Description   : Sends (transmits) data through the FLEXIO simulated UART-DMA module using a 
 *                 non-blocking method.
 * A non-blocking (also known as synchronous) function means that the function
 * returns immediately after initiating the transmit function. The application
 * has to get the transmit status to see when the transmit is complete. In
 * other words, after calling non-blocking (asynchronous) send function, the
 * application must get the transmit status to check if transmit is completed
 * or not. The asynchronous method of transmitting and receiving allows the UART
 * to perform a full duplex operation (simultaneously transmit and receive).
 *
 *END**************************************************************************/
flexio_uart_status_t FLEXIO_UART_DRV_DmaSendData(flexio_uart_dmastate_t * uartDmaState,
                                   const uint8_t * txBuff,
                                   uint32_t txSize)
{
    if((uartDmaState == NULL)||(txBuff == NULL))
    {
        return kStatus_FlexIO_UART_InvalidParam;
    }
    flexio_uart_status_t retVal = kStatus_FlexIO_UART_Success;

    /* Indicates current transaction is non-blocking. */
    uartDmaState->isTxBlocking = false;

    /* Start the transmission process*/
    retVal = FLEXIO_UART_DRV_DmaStartSendData(uartDmaState, txBuff, txSize);

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_DmaGetTransmitStatus
 * Description   : This function returns whether the previous UART transmit
 * has finished. When performing an async transmit, the user can call this
 * function to ascertain the state of the current transmission: in progress
 * (or busy) or complete (success). In addition, if the transmission is still
 * in progress, the user can obtain the number of words that have been
 * currently transferred.
 *
 *END**************************************************************************/
flexio_uart_status_t FLEXIO_UART_DRV_DmaGetTransmitStatus(flexio_uart_dmastate_t * uartDmaState,
                                            uint32_t * bytesRemaining)
{
    if(uartDmaState == NULL)
    {
        return kStatus_FlexIO_UART_InvalidParam;
    }

    /* Fill in the bytes transferred. */
    if (bytesRemaining)
    {
        *bytesRemaining = DMA_DRV_GetUnfinishedBytes(&uartDmaState->dmaUartTx);
    }

    return (uartDmaState->isTxBusy ? kStatus_FlexIO_UART_TxBusy : kStatus_FlexIO_UART_Success);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_DmaAbortSendingData
 * Description   : This function Terminates a non-blocking FLEXIO simulated UART-DMA 
 * transmission early.During an async UART transmission, the user has the option to
 * terminate the transmission early if the transmission is still in progress.
 *
 *END**************************************************************************/
flexio_uart_status_t FLEXIO_UART_DRV_DmaAbortSendingData(flexio_uart_dmastate_t * uartDmaState)
{
    if(uartDmaState == NULL)
    {
        return kStatus_FlexIO_UART_InvalidParam;
    }

    /* Check if a transfer is running. */
    if (!uartDmaState->isTxBusy)
    {
        return kStatus_FlexIO_UART_NoTransmitInProgress;
    }

    /* Stop the running transfer. */
    FLEXIO_UART_DRV_DmaCompleteSendData(uartDmaState);

    return kStatus_FlexIO_UART_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_DmaReceiveDataBlocking
 * Description   : This function gets (receives) data from the FLEXIO simulated UART-DMA 
 * module using a blocking method.A blocking (also known as synchronous) function means 
 * that the function does not return until the receive is complete. This blocking
 * function is used to send data through the UART port.
 *
 *END**************************************************************************/
flexio_uart_status_t FLEXIO_UART_DRV_DmaReceiveDataBlocking(flexio_uart_dmastate_t * uartDmaState,
                                              uint8_t * rxBuff,
                                              uint32_t rxSize,
                                              uint32_t timeout)
{
    if((uartDmaState == NULL)||(rxBuff == NULL))
    {
        return kStatus_FlexIO_UART_InvalidParam;
    }

    flexio_uart_status_t retVal = kStatus_FlexIO_UART_Success;
    osa_status_t syncStatus;

    /* Indicates current transaction is blocking. */
    uartDmaState->isRxBlocking = true;

    retVal = FLEXIO_UART_DRV_DmaStartReceiveData(uartDmaState, rxBuff, rxSize);

    if (retVal == kStatus_FlexIO_UART_Success)
    {
        /* Wait until all the data is received or for timeout.*/
        do
        {
            syncStatus = OSA_SemaWait(&uartDmaState->rxIrqSync, timeout);
        }while(syncStatus == kStatus_OSA_Idle);

        if (syncStatus != kStatus_OSA_Success)
        {
            /* Stop DMA channel. */
            DMA_DRV_StopChannel(&uartDmaState->dmaUartRx);

            /* Update the information of the module driver state */
            uartDmaState->isRxBusy = false;

            retVal = kStatus_FlexIO_UART_Timeout;
        }
    }

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_DmaReceiveData
 * Description   : This function gets (receives) data from the FLEXIO simulated 
 * UART-DMA module using a non-blocking method.
 * A non-blocking (also known as synchronous) function means that the function
 * returns immediately after initiating the receive function. The application
 * has to get the receive status to see when the receive is complete. In other
 * words, after calling non-blocking (asynchronous) get function, the
 * application must get the receive status to check if receive is completed or
 * not. The asynchronous method of transmitting and receiving allows the UART
 * to perform a full duplex operation (simultaneously transmit and receive).
 *
 *END**************************************************************************/
flexio_uart_status_t FLEXIO_UART_DRV_DmaReceiveData(flexio_uart_dmastate_t * uartDmaState,
                                      uint8_t * rxBuff,
                                      uint32_t rxSize)
{
    if((uartDmaState == NULL)||(rxBuff == NULL))
    {
        return kStatus_FlexIO_UART_InvalidParam;
    }

    flexio_uart_status_t retVal = kStatus_FlexIO_UART_Success;

    /* Indicates current transaction is non-blocking. */
    uartDmaState->isRxBlocking = false;

    retVal = FLEXIO_UART_DRV_DmaStartReceiveData(uartDmaState, rxBuff, rxSize);

    return retVal ;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_DmaGetReceiveStatus
 * Description   : This function returns whether the previous UART receive is
 * complete. When performing an async receive, the user can call this function
 * to ascertain the state of the current receive progress: in progress (or busy)
 * or complete (success). In addition, if the receive is still in progress,
 * the user can obtain the number of words that have been currently received.
 *
 *END**************************************************************************/
flexio_uart_status_t FLEXIO_UART_DRV_DmaGetReceiveStatus(flexio_uart_dmastate_t * uartDmaState,
                                           uint32_t * bytesRemaining)
{
    if(uartDmaState == NULL)
    {
        return kStatus_FlexIO_UART_InvalidParam;
    }

    /* Fill in the bytes transferred. */
    if (bytesRemaining)
    {
        *bytesRemaining = DMA_DRV_GetUnfinishedBytes(&uartDmaState->dmaUartRx);
    }

    return (uartDmaState->isRxBusy ? kStatus_FlexIO_UART_RxBusy : kStatus_FlexIO_UART_Success);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_DmaAbortReceivingData
 * Description   : This function shuts down the UART by disabling interrupts and
 * the transmitter/receiver.
 *
 *END**************************************************************************/
flexio_uart_status_t FLEXIO_UART_DRV_DmaAbortReceivingData(flexio_uart_dmastate_t * uartDmaState)
{
    if(uartDmaState == NULL)
    {
        return kStatus_FlexIO_UART_InvalidParam;
    }

    /* Check if a transfer is running. */
    if (!uartDmaState->isRxBusy)
    {
        return kStatus_FlexIO_UART_NoReceiveInProgress;
    }

    /* Stop the running transfer. */
    FLEXIO_UART_DRV_DmaCompleteReceiveData(uartDmaState);

    return kStatus_FlexIO_UART_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_DmaCompleteSendData
 * Description   : Finish up a transmit by completing the process of sending
 * data and disabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void FLEXIO_UART_DRV_DmaCompleteSendData(flexio_uart_dmastate_t * uartDmaState)
{
    if(uartDmaState == NULL)
    {
        return;
    }

    /* Stop DMA channel. */
    DMA_DRV_StopChannel(&uartDmaState->dmaUartTx);

    /* Signal the synchronous completion object. */
    if (uartDmaState->isTxBlocking)
    {
        OSA_SemaPost(&uartDmaState->txIrqSync);
    }

    /* Update the information of the module driver state */
    uartDmaState->isTxBusy = false;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_DRV_DmaTxCallback
 * Description   : This is not a public interface.
 *
 *END**************************************************************************/
static void FLEXIO_UART_DRV_DmaTxCallback(void *param, dma_channel_status_t status)
{
    FLEXIO_UART_DRV_DmaCompleteSendData((flexio_uart_dmastate_t *)param);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_DmaStartSendData
 * Description   : This is not a public interface.
 *
 *END**************************************************************************/
static flexio_uart_status_t FLEXIO_UART_DRV_DmaStartSendData(flexio_uart_dmastate_t * uartDmaState,
                                               const uint8_t * txBuff,
                                               uint32_t txSize)
{
    if(uartDmaState == NULL)
    {
        return kStatus_FlexIO_UART_InvalidParam;
    }

    dma_channel_t *chn = &uartDmaState->dmaUartTx;

    /* Check that we're not busy already transmitting data from a previous function call. */
    if (uartDmaState->isTxBusy)
    {
        return kStatus_FlexIO_UART_TxBusy;
    }

    /* Update UART DMA run-time structure. */
    uartDmaState->isTxBusy = true;
    /*Config UART TX DMA transfer*/
    uint32_t destAddr = FLEXIO_UART_Tx_HAL_GetTxBufferAddr((&(uartDmaState->txDev)));
    DMA_DRV_ConfigTransfer(chn,kDmaMemoryToPeripheral, 
       1, (uint32_t)(txBuff), destAddr, txSize);

    DMA_DRV_StartChannel(chn);

    return kStatus_FlexIO_UART_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_DmaCompleteReceiveData
 * Description   : Finish up a receive by completing the process of receiving data
 * and disabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void FLEXIO_UART_DRV_DmaCompleteReceiveData(flexio_uart_dmastate_t * uartDmaState)
{
    if(uartDmaState == NULL)
    {
        return;
    }

    /* Stop DMA channel. */
    DMA_DRV_StopChannel(&uartDmaState->dmaUartRx);

    /* Signal the synchronous completion object. */
    if (uartDmaState->isRxBlocking)
    {
        OSA_SemaPost(&uartDmaState->rxIrqSync);
    }

    /* Update the information of the module driver state */
    uartDmaState->isRxBusy = false;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_DmaRxCallback
 * Description   : This is not a public interface.
 *
 *END**************************************************************************/
static void FLEXIO_UART_DRV_DmaRxCallback(void *param, dma_channel_status_t status)
{
    FLEXIO_UART_DRV_DmaCompleteReceiveData((flexio_uart_dmastate_t *)param);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_DmaStartReceiveData
 * Description   : Initiate (start) a receive by beginning the process of
 * receiving data and enabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static flexio_uart_status_t FLEXIO_UART_DRV_DmaStartReceiveData(flexio_uart_dmastate_t * uartDmaState,
                                                  uint8_t * rxBuff,
                                                  uint32_t rxSize)
{
    if(uartDmaState == NULL)
    {
        return kStatus_FlexIO_UART_InvalidParam;
    }

    dma_channel_t *chn = &uartDmaState->dmaUartRx;

    /* Check that we're not busy already receiving data from a previous function call. */
    if (uartDmaState->isRxBusy)
    {
        return kStatus_FlexIO_UART_RxBusy;
    }

    /* Update UART DMA run-time structure. */
    uartDmaState->isRxBusy = true;
    /*Config UART RX DMA transfer*/
    uint32_t srcAddr = FLEXIO_UART_Rx_HAL_GetRxBufferAddr(&(uartDmaState->rxDev));
    DMA_DRV_ConfigTransfer(chn,kDmaPeripheralToMemory,
          1, srcAddr, (uint32_t)rxBuff, rxSize);

    DMA_DRV_StartChannel(chn);

    return kStatus_FlexIO_UART_Success;
}
#endif

/*******************************************************************************
 * EOF
 ******************************************************************************/

