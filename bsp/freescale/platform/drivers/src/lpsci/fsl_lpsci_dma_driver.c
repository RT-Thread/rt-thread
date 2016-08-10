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

#include <assert.h>
#include <string.h>
#include "fsl_lpsci_dma_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"
#include "fsl_dma_request.h"

#if FSL_FEATURE_SOC_LPSCI_COUNT
/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Pointer to lpsci runtime state structure */
extern void * g_lpsciStatePtr[UART0_INSTANCE_COUNT];

/*******************************************************************************
 * Private Functions
 ******************************************************************************/
static void LPSCI_DRV_DmaCompleteSendData(uint32_t instance);
static void LPSCI_DRV_DmaTxCallback(void *param, dma_channel_status_t status);
static lpsci_status_t LPSCI_DRV_DmaStartSendData(uint32_t instance,
                                               const uint8_t * txBuff,
                                               uint32_t txSize);
static void LPSCI_DRV_DmaCompleteReceiveData(uint32_t instance);
static void LPSCI_DRV_DmaRxCallback(void *param, dma_channel_status_t status);
static lpsci_status_t LPSCI_DRV_DmaStartReceiveData(uint32_t instance,
                                                  uint8_t * rxBuff,
                                                  uint32_t rxSize);
/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_DRV_DmaInit
 * Description   : This function initializes a LPSCI instance for operation.
 * This function will initialize the run-time state structure to keep track of
 * the on-going transfers, ungate the clock to the LPSCI module, initialize the
 * module to user defined settings and default settings, configure LPSCI DMA
 * and enable the LPSCI module transmitter and receiver.
 * The following is an example of how to set up the lpsci_dma_state_t and the
 * lpsci_user_config_t parameters and how to call the LPSCI_DRV_DmaInit function
 * by passing in these parameters:
 *    lpsci_user_config_t lpsciConfig;
 *    lpsciConfig.baudRate = 9600;
 *    lpsciConfig.bitCountPerChar = kLpsci8BitsPerChar;
 *    lpsciConfig.parityMode = kLpsciParityDisabled;
 *    lpsciConfig.stopBitCount = kLpsciOneStopBit;
 *    lpsci_dma_state_t lpsciDmaState;
 *    LPSCI_DRV_DmaInit(instance, &lpsciDmaState, &lpsciConfig);
 *
 *END**************************************************************************/
lpsci_status_t LPSCI_DRV_DmaInit(uint32_t instance,
                               lpsci_dma_state_t * lpsciDmaStatePtr,
                               const lpsci_dma_user_config_t * lpsciUserConfig)
{
    assert(lpsciDmaStatePtr && lpsciUserConfig);
    assert(instance < UART0_INSTANCE_COUNT);

    UART0_Type * base = g_lpsciBase[instance];
    uint32_t lpsciSourceClock = 0;
    dma_request_source_t lpsciTxDmaRequest = kDmaRequestMux0Disable;
    dma_request_source_t lpsciRxDmaRequest = kDmaRequestMux0Disable;

    /* Exit if current instance is already initialized. */
    if (g_lpsciStatePtr[instance])
    {
        return kStatus_LPSCI_Initialized;
    }

    /* Clear the state structure for this instance. */
    memset(lpsciDmaStatePtr, 0, sizeof(lpsci_dma_state_t));

    /* Save runtime structure pointer.*/
    g_lpsciStatePtr[instance] = lpsciDmaStatePtr;

    /* Un-gate LPSCI module clock */
    CLOCK_SYS_EnableLpsciClock(instance);

    /* Set LPSCI clock source */
    CLOCK_SYS_SetLpsciSrc(instance, lpsciUserConfig->clockSource);

    /* Initialize LPSCI to a known state. */
    LPSCI_HAL_Init(base);

    /* Create Semaphore for txIrq and rxIrq. */
    OSA_SemaCreate(&lpsciDmaStatePtr->txIrqSync, 0);
    OSA_SemaCreate(&lpsciDmaStatePtr->rxIrqSync, 0);

    /* LPSCI clock source is either system or bus clock depending on instance */
    lpsciSourceClock = CLOCK_SYS_GetLpsciFreq(instance);

    /* Initialize LPSCI baud rate, bit count, parity and stop bit. */
    LPSCI_HAL_SetBaudRate(base, lpsciSourceClock, lpsciUserConfig->baudRate);
    LPSCI_HAL_SetBitCountPerChar(base, lpsciUserConfig->bitCountPerChar);
    LPSCI_HAL_SetParityMode(base, lpsciUserConfig->parityMode);
#if FSL_FEATURE_LPSCI_HAS_STOP_BIT_CONFIG_SUPPORT
    LPSCI_HAL_SetStopBitCount(base, lpsciUserConfig->stopBitCount);
#endif

    /* Enable DMA trigger when transmit data register empty,
     * and receive data register full. */
    LPSCI_HAL_SetTxDmaCmd(base, true);
    LPSCI_HAL_SetRxDmaCmd(base, true);

    switch (instance)
    {
        case 0:
            lpsciRxDmaRequest = kDmaRequestMux0LPSCI0Rx;
            lpsciTxDmaRequest = kDmaRequestMux0LPSCI0Tx;
            break;
        default :
            break;
    }

    /* Request DMA channels for RX FIFO. */
    DMA_DRV_RequestChannel(kDmaAnyChannel, lpsciRxDmaRequest,
                            &lpsciDmaStatePtr->dmaLpsciRx);
    DMA_DRV_RegisterCallback(&lpsciDmaStatePtr->dmaLpsciRx,
                    LPSCI_DRV_DmaRxCallback, (void *)instance);

    /* Request DMA channels for TX FIFO. */
    DMA_DRV_RequestChannel(kDmaAnyChannel, lpsciTxDmaRequest,
                            &lpsciDmaStatePtr->dmaLpsciTx);
    DMA_DRV_RegisterCallback(&lpsciDmaStatePtr->dmaLpsciTx,
                    LPSCI_DRV_DmaTxCallback, (void *)instance);

    /* Finally, enable the LPSCI transmitter and receiver*/
    LPSCI_HAL_EnableTransmitter(base);
    LPSCI_HAL_EnableReceiver(base);

    return kStatus_LPSCI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_DRV_DmaDeinit
 * Description   : This function shuts down the LPSCI by disabling LPSCI DMA and
 *                 the transmitter/receiver.
 *
 *END**************************************************************************/
lpsci_status_t LPSCI_DRV_DmaDeinit(uint32_t instance)
{
    assert(instance < UART0_INSTANCE_COUNT);

    /* Exit if current instance is already de-initialized or is gated.*/
    if ((!g_lpsciStatePtr[instance]) || (!CLOCK_SYS_GetLpsciGateCmd(instance)))
    {
        return kStatus_LPSCI_Fail;
    }

    UART0_Type * base = g_lpsciBase[instance];
    lpsci_dma_state_t * lpsciDmaState = (lpsci_dma_state_t *)g_lpsciStatePtr[instance];

    /* Wait until the data is completely shifted out of shift register */
    while(!(UART0_BRD_S1_TC(base))) { }

    LPSCI_HAL_SetTxDmaCmd(base, false);
    LPSCI_HAL_SetRxDmaCmd(base, false);

    /* Release DMA channel. */
    DMA_DRV_FreeChannel(&lpsciDmaState->dmaLpsciRx);
    DMA_DRV_FreeChannel(&lpsciDmaState->dmaLpsciTx);

    /* Disable TX and RX */
    LPSCI_HAL_DisableTransmitter(base);
    LPSCI_HAL_DisableReceiver(base);

    /* Destroy TX and RX sema. */
    OSA_SemaDestroy(&lpsciDmaState->txIrqSync);
    OSA_SemaDestroy(&lpsciDmaState->rxIrqSync);

    /* Cleared state pointer. */
    g_lpsciStatePtr[instance] = NULL;

    /* Gate LPSCI module clock */
    CLOCK_SYS_DisableLpsciClock(instance);

    return kStatus_LPSCI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_DRV_DmaSendDataBlocking
 * Description   :  Sends (transmits) data out through the LPSCI-DMA module
 * using a blocking method.
 *
 *END**************************************************************************/
lpsci_status_t LPSCI_DRV_DmaSendDataBlocking(uint32_t instance,
                                           const uint8_t * txBuff,
                                           uint32_t txSize,
                                           uint32_t timeout)
{
    assert(txBuff);
    assert(instance < UART0_INSTANCE_COUNT);

    lpsci_dma_state_t * lpsciDmaState = (lpsci_dma_state_t *)g_lpsciStatePtr[instance];
    lpsci_status_t retVal = kStatus_LPSCI_Success;
    osa_status_t syncStatus;

    /* Indicates current transaction is blocking. */
    lpsciDmaState->isTxBlocking = true;

    /* Start the transmission process */
    retVal = LPSCI_DRV_DmaStartSendData(instance, txBuff, txSize);

    if (retVal == kStatus_LPSCI_Success)
    {
        /* Wait until the transmit is complete. */
        do
        {
            syncStatus = OSA_SemaWait(&lpsciDmaState->txIrqSync, timeout);
        }while(syncStatus == kStatus_OSA_Idle);

        if (syncStatus != kStatus_OSA_Success)
        {
            /* Stop DMA channel. */
            DMA_DRV_StopChannel(&lpsciDmaState->dmaLpsciTx);

            /* Update the information of the module driver state */
            lpsciDmaState->isTxBusy = false;

            retVal = kStatus_LPSCI_Timeout;
        }
    }

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_DRV_DmaSendData
 * Description   : This function sends (transmits) data through the LPSCI module
 *                 using a non-blocking method.
 * A non-blocking (also known as synchronous) function means that the function
 * returns immediately after initiating the transmit function. The application
 * has to get the transmit status to see when the transmit is complete. In
 * other words, after calling non-blocking (asynchronous) send function, the
 * application must get the transmit status to check if transmit is completed
 * or not. The asynchronous method of transmitting and receiving allows the LPSCI
 * to perform a full duplex operation (simultaneously transmit and receive).
 *
 *END**************************************************************************/
lpsci_status_t LPSCI_DRV_DmaSendData(uint32_t instance,
                                   const uint8_t * txBuff,
                                   uint32_t txSize)
{
    assert(txBuff);
    assert(instance < UART0_INSTANCE_COUNT);

    lpsci_status_t retVal = kStatus_LPSCI_Success;
    lpsci_dma_state_t * lpsciDmaState = (lpsci_dma_state_t *)g_lpsciStatePtr[instance];

    /* Indicates current transaction is non-blocking. */
    lpsciDmaState->isTxBlocking = false;

    /* Start the transmission process*/
    retVal = LPSCI_DRV_DmaStartSendData(instance, txBuff, txSize);

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_DRV_DmaGetTransmitStatus
 * Description   : This function returns whether the previous LPSCI transmit
 * has finished. When performing an async transmit, the user can call this
 * function to ascertain the state of the current transmission: in progress
 * (or busy) or complete (success). In addition, if the transmission is still
 * in progress, the user can obtain the number of words that have been
 * currently transferred.
 *
 *END**************************************************************************/
lpsci_status_t LPSCI_DRV_DmaGetTransmitStatus(uint32_t instance,
                                            uint32_t * bytesRemaining)
{
    assert(instance < UART0_INSTANCE_COUNT);

    lpsci_dma_state_t * lpsciDmaState = (lpsci_dma_state_t *)g_lpsciStatePtr[instance];

    /* Fill in the bytes transferred. */
    if (bytesRemaining)
    {
        *bytesRemaining = DMA_DRV_GetUnfinishedBytes(&lpsciDmaState->dmaLpsciTx);
    }

    return (lpsciDmaState->isTxBusy ? kStatus_LPSCI_TxBusy : kStatus_LPSCI_Success);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_DRV_DmaAbortSendingData
 * Description   : This function terminates an asynchronous LPSCI transmission
 * early. During an async LPSCI transmission, the user has the option to
 * terminate the transmission early if the transmission is still in progress.
 *
 *END**************************************************************************/
lpsci_status_t LPSCI_DRV_DmaAbortSendingData(uint32_t instance)
{
    assert(instance < UART0_INSTANCE_COUNT);

    lpsci_dma_state_t * lpsciDmaState = (lpsci_dma_state_t *)g_lpsciStatePtr[instance];

    /* Check if a transfer is running. */
    if (!lpsciDmaState->isTxBusy)
    {
        return kStatus_LPSCI_NoTransmitInProgress;
    }

    /* Stop the running transfer. */
    LPSCI_DRV_DmaCompleteSendData(instance);

    return kStatus_LPSCI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_DRV_DmaReceiveDataBlocking
 * Description   : This function gets (receives) data from the LPSCI module using
 * a blocking method. A blocking (also known as synchronous) function means that
 * the function does not return until the receive is complete. This blocking
 * function is used to send data through the LPSCI port.
 *
 *END**************************************************************************/
lpsci_status_t LPSCI_DRV_DmaReceiveDataBlocking(uint32_t instance,
                                              uint8_t * rxBuff,
                                              uint32_t rxSize,
                                              uint32_t timeout)
{
    assert(rxBuff);
    assert(instance < UART0_INSTANCE_COUNT);

    lpsci_dma_state_t * lpsciDmaState = (lpsci_dma_state_t *)g_lpsciStatePtr[instance];
    lpsci_status_t retVal = kStatus_LPSCI_Success;
    osa_status_t syncStatus;

    /* Indicates current transaction is blocking. */
    lpsciDmaState->isRxBlocking = true;

    retVal = LPSCI_DRV_DmaStartReceiveData(instance, rxBuff, rxSize);

    if (retVal == kStatus_LPSCI_Success)
    {
        /* Wait until all the data is received or for timeout.*/
        do
        {
            syncStatus = OSA_SemaWait(&lpsciDmaState->rxIrqSync, timeout);
        }while(syncStatus == kStatus_OSA_Idle);

        if (syncStatus != kStatus_OSA_Success)
        {
            /* Stop DMA channel. */
            DMA_DRV_StopChannel(&lpsciDmaState->dmaLpsciRx);

            /* Update the information of the module driver state */
            lpsciDmaState->isRxBusy = false;

            retVal = kStatus_LPSCI_Timeout;
        }
    }

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_DRV_DmaReceiveData
 * Description   : This function gets (receives) data from the LPSCI module using
 * a non-blocking method.
 * A non-blocking (also known as synchronous) function means that the function
 * returns immediately after initiating the receive function. The application
 * has to get the receive status to see when the receive is complete. In other
 * words, after calling non-blocking (asynchronous) get function, the
 * application must get the receive status to check if receive is completed or
 * not. The asynchronous method of transmitting and receiving allows the LPSCI
 * to perform a full duplex operation (simultaneously transmit and receive).
 *
 *END**************************************************************************/
lpsci_status_t LPSCI_DRV_DmaReceiveData(uint32_t instance,
                                      uint8_t * rxBuff,
                                      uint32_t rxSize)
{
    assert(rxBuff);
    assert(instance < UART0_INSTANCE_COUNT);

    lpsci_status_t retVal = kStatus_LPSCI_Success;
    lpsci_dma_state_t * lpsciDmaState = (lpsci_dma_state_t *)g_lpsciStatePtr[instance];

    /* Indicates current transaction is non-blocking. */
    lpsciDmaState->isRxBlocking = false;

    retVal = LPSCI_DRV_DmaStartReceiveData(instance, rxBuff, rxSize);

    return retVal ;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_DRV_DmaGetReceiveStatus
 * Description   : This function returns whether the previous LPSCI receive is
 * complete. When performing an async receive, the user can call this function
 * to ascertain the state of the current receive progress: in progress (or busy)
 * or complete (success). In addition, if the receive is still in progress,
 * the user can obtain the number of words that have been currently received.
 *
 *END**************************************************************************/
lpsci_status_t LPSCI_DRV_DmaGetReceiveStatus(uint32_t instance,
                                           uint32_t * bytesRemaining)
{
    assert(instance < UART0_INSTANCE_COUNT);
    lpsci_dma_state_t * lpsciDmaState = (lpsci_dma_state_t *)g_lpsciStatePtr[instance];

    /* Fill in the bytes transferred. */
    if (bytesRemaining)
    {
        *bytesRemaining = DMA_DRV_GetUnfinishedBytes(&lpsciDmaState->dmaLpsciRx);
    }

    return (lpsciDmaState->isRxBusy ? kStatus_LPSCI_RxBusy : kStatus_LPSCI_Success);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_DRV_DmaAbortReceivingData
 * Description   : This function shuts down the LPSCI by disabling interrupts and
 * the transmitter/receiver.
 *
 *END**************************************************************************/
lpsci_status_t LPSCI_DRV_DmaAbortReceivingData(uint32_t instance)
{
    assert(instance < UART0_INSTANCE_COUNT);
    lpsci_dma_state_t * lpsciDmaState = (lpsci_dma_state_t *)g_lpsciStatePtr[instance];

    /* Check if a transfer is running. */
    if (!lpsciDmaState->isRxBusy)
    {
        return kStatus_LPSCI_NoReceiveInProgress;
    }

    /* Stop the running transfer. */
    LPSCI_DRV_DmaCompleteReceiveData(instance);

    return kStatus_LPSCI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_DRV_DmaCompleteSendData
 * Description   : Finish up a transmit by completing the process of sending
 * data and disabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void LPSCI_DRV_DmaCompleteSendData(uint32_t instance)
{
    assert(instance < UART0_INSTANCE_COUNT);

    lpsci_dma_state_t * lpsciDmaState = (lpsci_dma_state_t *)g_lpsciStatePtr[instance];

    /* Stop DMA channel. */
    DMA_DRV_StopChannel(&lpsciDmaState->dmaLpsciTx);

    /* Signal the synchronous completion object. */
    if (lpsciDmaState->isTxBlocking)
    {
        OSA_SemaPost(&lpsciDmaState->txIrqSync);
    }

    /* Update the information of the module driver state */
    lpsciDmaState->isTxBusy = false;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_DRV_DmaTxCallback
 * Description   : This is not a public interface.
 *
 *END**************************************************************************/
static void LPSCI_DRV_DmaTxCallback(void *param, dma_channel_status_t status)
{
    LPSCI_DRV_DmaCompleteSendData((uint32_t)param);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_DRV_DmaStartSendData
 * Description   : This is not a public interface.
 *
 *END**************************************************************************/
static lpsci_status_t LPSCI_DRV_DmaStartSendData(uint32_t instance,
                                               const uint8_t * txBuff,
                                               uint32_t txSize)
{
    assert(instance < UART0_INSTANCE_COUNT);

    UART0_Type * base = g_lpsciBase[instance];
    /* Get current runtime structure. */
    lpsci_dma_state_t * lpsciDmaState = (lpsci_dma_state_t *)g_lpsciStatePtr[instance];
    dma_channel_t *chn = &lpsciDmaState->dmaLpsciTx;

    /* Check that we're not busy already transmitting data from a previous function call. */
    if (lpsciDmaState->isTxBusy)
    {
        return kStatus_LPSCI_TxBusy;
    }

    /* Update LPSCI DMA run-time structure. */
    lpsciDmaState->isTxBusy = true;

    DMA_DRV_ConfigTransfer(&lpsciDmaState->dmaLpsciTx, kDmaMemoryToPeripheral,
        1u, (uint32_t)txBuff, LPSCI_HAL_GetDataRegAddr(base), txSize);

    DMA_DRV_StartChannel(chn);

    return kStatus_LPSCI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_DRV_DmaCompleteReceiveData
 * Description   : Finish up a receive by completing the process of receiving data
 * and disabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void LPSCI_DRV_DmaCompleteReceiveData(uint32_t instance)
{
    assert(instance < UART0_INSTANCE_COUNT);

    lpsci_dma_state_t * lpsciDmaState = (lpsci_dma_state_t *)g_lpsciStatePtr[instance];

    /* Stop DMA channel. */
    DMA_DRV_StopChannel(&lpsciDmaState->dmaLpsciRx);

    /* Signal the synchronous completion object. */
    if (lpsciDmaState->isRxBlocking)
    {
        OSA_SemaPost(&lpsciDmaState->rxIrqSync);
    }

    /* Update the information of the module driver state */
    lpsciDmaState->isRxBusy = false;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_DRV_DmaRxCallback
 * Description   : This is not a public interface.
 *
 *END**************************************************************************/
static void LPSCI_DRV_DmaRxCallback(void *param, dma_channel_status_t status)
{
    LPSCI_DRV_DmaCompleteReceiveData((uint32_t)param);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPSCI_DRV_DmaStartReceiveData
 * Description   : Initiate (start) a receive by beginning the process of
 * receiving data and enabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static lpsci_status_t LPSCI_DRV_DmaStartReceiveData(uint32_t instance,
                                                  uint8_t * rxBuff,
                                                  uint32_t rxSize)
{
    assert(instance < UART0_INSTANCE_COUNT);

    UART0_Type * base = g_lpsciBase[instance];
    /* Get current runtime structure. */
    lpsci_dma_state_t * lpsciDmaState = (lpsci_dma_state_t *)g_lpsciStatePtr[instance];
    dma_channel_t *chn = &lpsciDmaState->dmaLpsciRx;

    /* Check that we're not busy already receiving data from a previous function call. */
    if (lpsciDmaState->isRxBusy)
    {
        return kStatus_LPSCI_RxBusy;
    }

    /* Update LPSCI DMA run-time structure. */
    lpsciDmaState->isRxBusy = true;

    DMA_DRV_ConfigTransfer(&lpsciDmaState->dmaLpsciRx, kDmaPeripheralToMemory,
        1u, LPSCI_HAL_GetDataRegAddr(base), (uint32_t)rxBuff, rxSize);

    DMA_DRV_StartChannel(chn);

    return kStatus_LPSCI_Success;
}

#endif /* FSL_FEATURE_SOC_LPSCI_COUNT */
/*******************************************************************************
 * EOF
 ******************************************************************************/

