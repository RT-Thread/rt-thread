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
#include "fsl_flexio_uart_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"
#if FSL_FEATURE_SOC_FLEXIO_COUNT

/*******************************************************************************
 * Private Functions
 ******************************************************************************/
static flexio_uart_status_t FLEXIO_UART_DRV_StartSendData(flexio_uart_state_t *uartState,
                                            const uint8_t * txBuff,
                                            uint32_t txSize);
static flexio_uart_status_t FLEXIO_UART_DRV_StartReceiveData(flexio_uart_state_t *uartState,
                                               uint8_t * rxBuff,
                                               uint32_t rxSize);
static void FLEXIO_UART_DRV_CompleteSendData(flexio_uart_state_t *uartState);
static void FLEXIO_UART_DRV_CompleteReceiveData(flexio_uart_state_t *uartState);
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_Init
 * Description   : This function initializes a UART instance for operation.
 * This function will initialize the run-time state structure to keep track of
 * the on-going transfers, ungate the clock to the UART module, initialize the
 * module to user defined settings and default settings, configure the IRQ state
 * structure and enable the module-level interrupt to the core, and enable the
 * UART module transmitter and receiver.
 * The following is an example of how to set up the uart_state_t and the
 * uart_user_config_t parameters and how to call the UART_DRV_Init function by
 * passing in these parameters:
 *    flexio_uart_user_config_t uartConfig;
 *    uartConfig.baudRate = 9600;
 *    uartConfig.bitCountPerChar = kFlexIOUart8BitsPerChar;
 *    uart_state_t uartState;
 *    UART_DRV_Init(instance, &uartState, &uartConfig);
 *
 *END**************************************************************************/
flexio_uart_status_t FLEXIO_UART_DRV_Init(uint32_t instance, flexio_uart_state_t * uartState,
                                          const flexio_uart_userconfig_t * uartConfig)
{
    if((uartState == NULL)||(uartConfig == NULL))
    {
        return kStatus_FlexIO_UART_InvalidParam;
    }
    FLEXIO_Type* base = g_flexioBase[instance];
    uint32_t flexioSourceClock;
    flexio_uart_config_t devConfig;
    /*Reset the uartState structure*/
    memset(uartState,0,sizeof(*uartState));
    /* Create Semaphore for txIrq and rxIrq. */
    OSA_SemaCreate(&uartState->txIrqSync, 0);
    OSA_SemaCreate(&uartState->rxIrqSync, 0);  
    /* Get FlexIO clock frequency for baudrate caculation*/  
    flexioSourceClock = CLOCK_SYS_GetFlexioFreq(instance);
    uartState->mode = uartConfig->uartMode;
    devConfig.flexioBusClk = flexioSourceClock;
    devConfig.baudrate = uartConfig->baudRate;
    devConfig.bitCount = uartConfig->bitCounter;
    /*Configure buadrate, bit count and hardware resource including pin, shifter and timer for Tx module*/
    if((uartConfig->uartMode == flexioUART_TxOnly)||(uartConfig->uartMode == flexioUART_TxRx))
    {
        uartState->txDev.flexioBase = base;
        uartState->txDev.txPinIdx = uartConfig->txConfig.pinIdx;
        uartState->txDev.shifterIdx = uartConfig->txConfig.shifterIdx;
        uartState->txDev.timerIdx = uartConfig->txConfig.timerIdx;
        FLEXIO_UART_Tx_HAL_Configure(&(uartState->txDev), &devConfig);
        FLEXIO_DRV_RegisterCallback(instance,uartState->txDev.shifterIdx,
                                FLEXIO_UART_DRV_TX_IRQHandler,(void *)(uartState));
    }
    /*Configure buadrate, bit count and hardware resource including pin, shifter and timer for Rx module*/
    if((uartConfig->uartMode == flexioUART_RxOnly)||(uartConfig->uartMode == flexioUART_TxRx))
    {
        uartState->rxDev.flexioBase = base;
        uartState->rxDev.rxPinIdx = uartConfig->rxConfig.pinIdx;
        uartState->rxDev.shifterIdx = uartConfig->rxConfig.shifterIdx;
        uartState->rxDev.timerIdx = uartConfig->rxConfig.timerIdx;
        FLEXIO_UART_Rx_HAL_Configure(&(uartState->rxDev), &devConfig);
        FLEXIO_DRV_RegisterCallback(instance,uartState->rxDev.shifterIdx,
                                FLEXIO_UART_DRV_RX_IRQHandler,(void *)(uartState));
    }
    return kStatus_FlexIO_UART_Success;
}
void FLEXIO_UART_DRV_Deinit(flexio_uart_state_t *uartState)
{
	  /* Destroy TX and RX sema. */
    OSA_SemaDestroy(&uartState->txIrqSync);
    OSA_SemaDestroy(&uartState->rxIrqSync);
}
flexio_uart_rx_callback_t FLEXIO_UART_DRV_InstallRxCallback(flexio_uart_state_t *uartState,flexio_uart_rx_callback_t function, 
                                              uint8_t * rxBuff,void * callbackParam,bool alwaysEnableRxIrq)
{
    flexio_uart_rx_callback_t currentCallback = uartState->rxCallback;
    uartState->rxCallback = function;
    uartState->rxCallbackParam = callbackParam;
    uartState->rxBuff = rxBuff;

    /* Enable/Disable the receive data full interrupt */
    uartState->isRxBusy = true;
    return currentCallback;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : UART_DRV_SendDataBlocking
 * Description   : This function sends (transmits) data out through the UART
 * module using a blocking method.
 * A blocking (also known as synchronous) function means that the function does
 * not return until the transmit is complete. This blocking function is used to
 * send data through the UART port.
 *
 *END**************************************************************************/
flexio_uart_status_t FLEXIO_UART_DRV_SendDataBlocking(flexio_uart_state_t *uartState, 
                                        const uint8_t * txBuff,
                                        uint32_t txSize, 
                                        uint32_t timeout)
{
    if((uartState == NULL)||(txBuff == NULL))
    {
        return kStatus_FlexIO_UART_InvalidParam;
    }

    flexio_uart_status_t retVal = kStatus_FlexIO_UART_Success;
    osa_status_t syncStatus;

    /* Indicates current transaction is blocking.*/
    uartState->isTxBlocking = true;
    
    /* Start the transmission process */
    retVal = FLEXIO_UART_DRV_StartSendData(uartState, txBuff, txSize);

    if (retVal == kStatus_FlexIO_UART_Success)
    {
        /* Wait until the transmit is complete. */
        do
        {
            syncStatus = OSA_SemaWait(&uartState->txIrqSync, timeout);
        }while(syncStatus == kStatus_OSA_Idle);

        if (syncStatus != kStatus_OSA_Success)
        {
            /* Disable the transmitter data register empty interrupt */
            FLEXIO_UART_Tx_HAL_SetTxBufferEmptyIntCmd(&(uartState->txDev), false);
            /* Update the information of the module driver state */
            uartState->isTxBusy = false;

            retVal = kStatus_FlexIO_UART_Timeout;
        }
    }
    return retVal;	
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_SendData
 * Description   : This function sends (transmits) data through the UART module
 * using a non-blocking method.
 * A non-blocking (also known as asynchronous) function means that the function
 * returns immediately after initiating the transmit function. The application
 * has to get the transmit status to see when the transmit is complete. In
 * other words, after calling non-blocking (asynchronous) send function, the
 * application must get the transmit status to check if transmit is completed
 * or not. The asynchronous method of transmitting and receiving allows the UART
 * to perform a full duplex operation (simultaneously transmit and receive).
 *
 *END**************************************************************************/
flexio_uart_status_t FLEXIO_UART_DRV_SendData(flexio_uart_state_t *uartState,
                                const uint8_t * txBuff,
                                uint32_t txSize)
{
    if((uartState == NULL)||(txBuff == NULL))
    {
        return kStatus_FlexIO_UART_InvalidParam;
    }

    flexio_uart_status_t retVal = kStatus_FlexIO_UART_Success;

    /* Indicates current transaction is non-blocking */
    uartState->isTxBlocking = false;

    /* Start the transmission process */
    retVal = FLEXIO_UART_DRV_StartSendData(uartState, txBuff, txSize);

    return retVal;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : UART_DRV_GetTransmitStatus
 * Description   : This function returns whether the previous UART transmit has
 * finished.
 * When performing an async transmit, the user can call this function to
 * ascertain the state of the current transmission: in progress (or busy) or
 * complete (success). In addition, if the transmission is still in progress,
 * the user can obtain the number of words that have been currently transferred.
 *
 *END**************************************************************************/
flexio_uart_status_t FLEXIO_UART_DRV_GetTransmitStatus(flexio_uart_state_t *uartState, uint32_t * bytesRemaining)
{
    if(uartState == NULL)
    {
        return kStatus_FlexIO_UART_InvalidParam;
    }

    flexio_uart_status_t retVal = kStatus_FlexIO_UART_Success;
    uint32_t txSize = uartState->txSize;

    /* Fill in the bytes transferred. This may return that all bytes were
     * transmitted, however, for IPs with FIFO support, there still may be data
     * in the TX FIFO still in the process of being transmitted. */
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
 * Function Name : FLEXIO_UART_DRV_AbortSendingData
 * Description   : This function ends a non-blocking UART transmission early.
 * During a non-blocking UART transmission, the user has the option to terminate
 * the transmission early if the transmission is still in progress.
 *
 *END**************************************************************************/
flexio_uart_status_t FLEXIO_UART_DRV_AbortSendingData(flexio_uart_state_t *uartState)
{
    if(uartState == NULL)
    {
        return kStatus_FlexIO_UART_InvalidParam;
    }

    /* Check if a transfer is running. */
    if (!uartState->isTxBusy)
    {
        return kStatus_FlexIO_UART_NoTransmitInProgress;
    }

    /* Stop the running transfer. */
    FLEXIO_UART_DRV_CompleteSendData(uartState);

    return kStatus_FlexIO_UART_Success;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_ReceiveDataBlocking
 * Description   : This function gets (receives) data from the UART module using
 * a blocking method. A blocking (also known as synchronous) function means that
 * the function does not return until the receive is complete. This blocking
 * function is used to send data through the UART port.
 *
 *END**************************************************************************/
flexio_uart_status_t FLEXIO_UART_DRV_ReceiveDataBlocking(flexio_uart_state_t *uartState, uint8_t * rxBuff,
                                           uint32_t rxSize, uint32_t timeout)
{
    if((uartState == NULL)||(rxBuff == NULL))
    {
        return kStatus_FlexIO_UART_InvalidParam;
    }

    flexio_uart_status_t retVal = kStatus_FlexIO_UART_Success;
    osa_status_t syncStatus;

    /* Indicates current transaction is blocking.*/
    uartState->isRxBlocking = true;

    retVal = FLEXIO_UART_DRV_StartReceiveData(uartState, rxBuff, rxSize);

    if (retVal == kStatus_FlexIO_UART_Success)
    {
        /* Wait until all the data is received or for timeout.*/
        do
        {
            syncStatus = OSA_SemaWait(&uartState->rxIrqSync, timeout);
        }while(syncStatus == kStatus_OSA_Idle);

        if (syncStatus != kStatus_OSA_Success)
        {
            /* Disable receive data full and rx overrun interrupt */
            FLEXIO_UART_Rx_HAL_SetRxBufferFullIntCmd(&(uartState->rxDev), false);
            /* Update the information of the module driver state */
            uartState->isRxBusy = false;

            retVal = kStatus_FlexIO_UART_Timeout;
        }
    }

    return retVal;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_ReceiveData
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
flexio_uart_status_t FLEXIO_UART_DRV_ReceiveData(flexio_uart_state_t *uartState,
                                   uint8_t * rxBuff,
                                   uint32_t rxSize)
{
    if((uartState == NULL)||(rxBuff == NULL))
    {
        return kStatus_FlexIO_UART_InvalidParam;
    }

    flexio_uart_status_t retVal = kStatus_FlexIO_UART_Success;

    /* Indicates current transaction is non-blocking.*/
    uartState->isRxBlocking = false;

    retVal = FLEXIO_UART_DRV_StartReceiveData(uartState, rxBuff, rxSize);

    return retVal;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_GetReceiveStatus
 * Description   : This function returns whether the previous UART receive is
 *                 completed.
 * When performing a non-blocking receive, the user can call this function to
 * ascertain the state of the current receive progress: in progress (or busy)
 * or complete (success). In addition, if the receive is still in progress, the
 * user can obtain the number of words that have been currently received.
 *
 *END**************************************************************************/
flexio_uart_status_t FLEXIO_UART_DRV_GetReceiveStatus(flexio_uart_state_t *uartState,
                                        uint32_t * bytesRemaining)
{
    if(uartState == NULL)
    {
        return kStatus_FlexIO_UART_InvalidParam;
    }
    flexio_uart_status_t retVal = kStatus_FlexIO_UART_Success;
    uint32_t rxSize = uartState->rxSize;

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
 * Function Name : FLEXIO_UART_DRV_AbortReceivingData
 * Description   : This function shuts down the UART by disabling interrupts and
 *                 the transmitter/receiver.
 * This function disables the UART interrupts, disables the transmitter and
 * receiver, and flushes the FIFOs (for modules that support FIFOs).
 *
 *END**************************************************************************/
flexio_uart_status_t FLEXIO_UART_DRV_AbortReceivingData(flexio_uart_state_t *uartState)
{
    if(uartState == NULL)
    {
        return kStatus_FlexIO_UART_InvalidParam;
    }    assert(uartState);

    /* Check if a transfer is running. */
    if (!uartState->isRxBusy)
    {
        return kStatus_FlexIO_UART_NoReceiveInProgress;
    }

    /* Stop the running transfer. */
    FLEXIO_UART_DRV_CompleteReceiveData(uartState);

    return kStatus_FlexIO_UART_Success;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_TX_IRQHandler
 * Description   : Interrupt handler for TX of FLEXIO UART.
 * This handler uses the buffers stored in the flexio_uart_state_t struct to transfer
 * data. This is not a public API as it is called whenever an interrupt occurs.
 *
 *END**************************************************************************/
void FLEXIO_UART_DRV_TX_IRQHandler(void *param)
{
    flexio_uart_state_t *uartState = (flexio_uart_state_t *)param;
    if(uartState == NULL)
    {
        return;
    }

    /* Exit the ISR if no transfer is happening for this instance. */
    if ((!uartState->isTxBusy))
    {
        return;
    }
    /* Handle transmit data register empty interrupt */
    if((FLEXIO_UART_Tx_HAL_GetTxBufferEmptyIntCmd(&(uartState->txDev)))
      && (FLEXIO_UART_Tx_HAL_GetTxBufferEmptyFlag(&(uartState->txDev))))
    {
        --uartState->txSize;
        /* Check to see if there are any more bytes to send */
        if (uartState->txSize)
        {
            ++uartState->txBuff;
            /* Transmit data and update tx size/buff */
            FLEXIO_UART_Tx_HAL_PutData(&(uartState->txDev), *(uartState->txBuff));
        }
        else
        {
            FLEXIO_UART_DRV_CompleteSendData(uartState);
        }
    }
    
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_RX_IRQHandler
 * Description   : Interrupt handler for RX of FLEXIO UART.
 * This handler uses the buffers stored in the flexio_uart_state_t struct to transfer
 * data. This is not a public API as it is called whenever an interrupt occurs.
 *
 *END**************************************************************************/
void FLEXIO_UART_DRV_RX_IRQHandler(void *param)
{
    flexio_uart_state_t *uartState = (flexio_uart_state_t *)param;
    if(uartState == NULL)
    {
        return;
    }

    /* Exit the ISR if no transfer is happening for this instance. */
    if ((!uartState->isRxBusy))
    {
        return;
    }
        /* Handle receive data register full interrupt */
        /* Get data and put into receive buffer */
        *(uartState->rxBuff) = FLEXIO_UART_Rx_HAL_GetData(&(uartState->rxDev));

        /* Invoke callback if there is one */
        if (uartState->rxCallback != NULL)
        {
            uartState->rxCallback(uartState);
        }
        else
        {
            ++uartState->rxBuff;
            --uartState->rxSize;
            /* Check and see if this was the last byte received */
            if (uartState->rxSize == 0)
            {
                FLEXIO_UART_DRV_CompleteReceiveData(uartState);
            }
        }
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_StartSendData
 * Description   : Initiate (start) a transmit by beginning the process of
 * sending data and enabling the interrupt.
 *
 *END**************************************************************************/
static flexio_uart_status_t FLEXIO_UART_DRV_StartSendData(flexio_uart_state_t *uartState,
                                            const uint8_t * txBuff,
                                            uint32_t txSize)
{
    if(uartState == NULL)
    {
        return kStatus_FlexIO_UART_InvalidParam;
    }
    /* Check that we're not busy already transmitting data from a previous
     * function call. */
    if (uartState->isTxBusy)
    {
        return kStatus_FlexIO_UART_TxBusy;
    }

    if (txSize == 0U)
    {
        return kStatus_FlexIO_UART_NoDataToDeal;
    }
    /* Initialize the module driver state structure. */
    uartState->txBuff = txBuff;
    uartState->txSize = txSize;
    uartState->isTxBusy = true;
    /* Make sure the transmit data register is empty and ready for data */
    while(!FLEXIO_UART_Tx_HAL_GetTxBufferEmptyFlag(&(uartState->txDev))) { }

    /* Put the first data in shifter to start the transmission */
     FLEXIO_UART_Tx_HAL_PutData(&(uartState->txDev), *(uartState->txBuff));
    /* Enable interrupt generation for tx shifter.  */
    FLEXIO_UART_Tx_HAL_SetTxBufferEmptyIntCmd(&(uartState->txDev), true);

    return kStatus_FlexIO_UART_Success;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_StartReceiveData
 * Description   : Initiate (start) a receive by beginning the process of
 * receiving data and enabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static flexio_uart_status_t FLEXIO_UART_DRV_StartReceiveData(flexio_uart_state_t *uartState,
                                               uint8_t * rxBuff,
                                               uint32_t rxSize)
{
    if(uartState == NULL)
    {
        return kStatus_FlexIO_UART_InvalidParam;
    }

    /* Check that we're not busy receiving data from a previous function call. */
    if ((uartState->isRxBusy) && (!uartState->rxCallback))
    {
        return kStatus_FlexIO_UART_RxBusy;
    }

    if (rxSize == 0U)
    {
        return kStatus_FlexIO_UART_NoDataToDeal;
    }

    /* Initialize the module driver state struct to indicate transfer in progress
     * and with the buffer and byte count data */
    uartState->rxBuff = rxBuff;
    uartState->rxSize = rxSize;
    uartState->isRxBusy = true;

    /* Enable the receive data full interrupt */
    FLEXIO_UART_Rx_HAL_SetRxBufferFullIntCmd(&(uartState->rxDev), true);

    return kStatus_FlexIO_UART_Success;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_CompleteSendData
 * Description   : Finish up a transmit by completing the process of sending
 * data and disabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void FLEXIO_UART_DRV_CompleteSendData(flexio_uart_state_t *uartState)
{
    if(uartState == NULL)
    {
        return;
    }

    /* Disable the transmitter data register empty interrupt */
    FLEXIO_UART_Tx_HAL_SetTxBufferEmptyIntCmd(&(uartState->txDev), false);

    /* Signal the synchronous completion object. */
    if (uartState->isTxBlocking)
    {
        OSA_SemaPost(&uartState->txIrqSync);
    }

    /* Update the information of the module driver state */
    uartState->isTxBusy = false;
}
/*FUNCTION**********************************************************************
 *
 * Function Name : FLEXIO_UART_DRV_CompleteReceiveData
 * Description   : Finish up a receive by completing the process of receiving
 * data and disabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void FLEXIO_UART_DRV_CompleteReceiveData(flexio_uart_state_t *uartState)
{
    if(uartState == NULL)
    {
        return;
    }

    /* Disable receive data full interrupt */
    FLEXIO_UART_Rx_HAL_SetRxBufferFullIntCmd(&(uartState->rxDev), false);

    /* Signal the synchronous completion object. */
    if (uartState->isRxBlocking)
    {
        OSA_SemaPost(&uartState->rxIrqSync);
    }

    /* Update the information of the module driver state */
    uartState->isRxBusy = false;
}
#endif
