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
#include "fsl_lpuart_dma_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"
#include "fsl_dma_request.h"

#if FSL_FEATURE_SOC_LPUART_COUNT

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Pointer to lpuart runtime state structure */
extern void * g_lpuartStatePtr[LPUART_INSTANCE_COUNT];

/*******************************************************************************
 * Private Functions
 ******************************************************************************/
static void LPUART_DRV_DmaCompleteSendData(uint32_t instance);
static void LPUART_DRV_DmaTxCallback(void *param, dma_channel_status_t status);
static lpuart_status_t LPUART_DRV_DmaStartSendData(uint32_t instance,
                                               const uint8_t * txBuff,
                                               uint32_t txSize);
static void LPUART_DRV_DmaCompleteReceiveData(uint32_t instance);
static void LPUART_DRV_DmaRxCallback(void *param, dma_channel_status_t status);
static lpuart_status_t LPUART_DRV_DmaStartReceiveData(uint32_t instance,
                                                  uint8_t * rxBuff,
                                                  uint32_t rxSize);
/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_DmaInit
 * Description   : This function initializes a LPUART instance for operation.
 * This function will initialize the run-time state structure to keep track of
 * the on-going transfers, ungate the clock to the LPUART module, initialize the
 * module to user defined settings and default settings, configure LPUART DMA
 * and enable the LPUART module transmitter and receiver.
 * The following is an example of how to set up the lpuart_dma_state_t and the
 * lpuart_user_config_t parameters and how to call the LPUART_DRV_DmaInit function
 * by passing in these parameters:
 *    lpuart_user_config_t lpuartConfig;
 *    lpuartConfig.baudRate = 9600;
 *    lpuartConfig.bitCountPerChar = kLpuart8BitsPerChar;
 *    lpuartConfig.parityMode = kLpuartParityDisabled;
 *    lpuartConfig.stopBitCount = kLpuartOneStopBit;
 *    lpuart_dma_state_t lpuartDmaState;
 *    LPUART_DRV_DmaInit(instance, &lpuartDmaState, &lpuartConfig);
 *
 *END**************************************************************************/
lpuart_status_t LPUART_DRV_DmaInit(uint32_t instance,
                               lpuart_dma_state_t * lpuartDmaStatePtr,
                               const lpuart_dma_user_config_t * lpuartUserConfig)
{
    assert(lpuartDmaStatePtr && lpuartUserConfig);
    assert(instance < LPUART_INSTANCE_COUNT);

    LPUART_Type * base = g_lpuartBase[instance];
    uint32_t lpuartSourceClock = 0;
    dma_request_source_t lpuartTxDmaRequest = kDmaRequestMux0Disable;
    dma_request_source_t lpuartRxDmaRequest = kDmaRequestMux0Disable;

    /* Exit if current instance is already initialized. */
    if (g_lpuartStatePtr[instance])
    {
        return kStatus_LPUART_Initialized;
    }

    /* Clear the state structure for this instance. */
    memset(lpuartDmaStatePtr, 0, sizeof(lpuart_dma_state_t));

    /* Save runtime structure pointer.*/
    g_lpuartStatePtr[instance] = lpuartDmaStatePtr;

    /* Un-gate LPUART module clock */
    CLOCK_SYS_EnableLpuartClock(instance);

    /* Set LPUART clock source */
    CLOCK_SYS_SetLpuartSrc(instance, lpuartUserConfig->clockSource);

    /* Initialize LPUART to a known state. */
    LPUART_HAL_Init(base);

    /* Create Semaphore for txIrq and rxIrq. */
    OSA_SemaCreate(&lpuartDmaStatePtr->txIrqSync, 0);
    OSA_SemaCreate(&lpuartDmaStatePtr->rxIrqSync, 0);

    /* LPUART clock source is either system or bus clock depending on instance */
    lpuartSourceClock = CLOCK_SYS_GetLpuartFreq(instance);

    /* Initialize LPUART baud rate, bit count, parity and stop bit. */
    LPUART_HAL_SetBaudRate(base, lpuartSourceClock, lpuartUserConfig->baudRate);
    LPUART_HAL_SetBitCountPerChar(base, lpuartUserConfig->bitCountPerChar);
    LPUART_HAL_SetParityMode(base, lpuartUserConfig->parityMode);
#if FSL_FEATURE_LPUART_HAS_STOP_BIT_CONFIG_SUPPORT
    LPUART_HAL_SetStopBitCount(base, lpuartUserConfig->stopBitCount);
#endif

    /* Enable DMA trigger when transmit data register empty,
     * and receive data register full. */
    LPUART_HAL_SetTxDmaCmd(base, true);
    LPUART_HAL_SetRxDmaCmd(base, true);

    switch (instance)
    {
        case 0:
            lpuartRxDmaRequest = kDmaRequestMux0LPUART0Rx;
            lpuartTxDmaRequest = kDmaRequestMux0LPUART0Tx;
            break;
        default :
            break;
    }

    /* Request DMA channels for RX FIFO. */
    DMA_DRV_RequestChannel(kDmaAnyChannel, lpuartRxDmaRequest,
                            &lpuartDmaStatePtr->dmaLpuartRx);
    DMA_DRV_RegisterCallback(&lpuartDmaStatePtr->dmaLpuartRx,
                    LPUART_DRV_DmaRxCallback, (void *)instance);

    /* Request DMA channels for TX FIFO. */
    DMA_DRV_RequestChannel(kDmaAnyChannel, lpuartTxDmaRequest,
                            &lpuartDmaStatePtr->dmaLpuartTx);
    DMA_DRV_RegisterCallback(&lpuartDmaStatePtr->dmaLpuartTx,
                    LPUART_DRV_DmaTxCallback, (void *)instance);

    /* Finally, enable the LPUART transmitter and receiver*/
    LPUART_HAL_SetTransmitterCmd(base, true);
    LPUART_HAL_SetReceiverCmd(base, true);

    return kStatus_LPUART_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_DmaDeinit
 * Description   : This function shuts down the LPUART by disabling LPUART DMA and
 *                 the transmitter/receiver.
 *
 *END**************************************************************************/
lpuart_status_t LPUART_DRV_DmaDeinit(uint32_t instance)
{
    assert(instance < LPUART_INSTANCE_COUNT);

    /* Exit if current instance is already de-initialized or is gated.*/
    if ((!g_lpuartStatePtr[instance]) || (!CLOCK_SYS_GetLpuartGateCmd(instance)))
    {
        return kStatus_LPUART_Fail;
    }

    LPUART_Type * base = g_lpuartBase[instance];
    lpuart_dma_state_t * lpuartDmaState = (lpuart_dma_state_t *)g_lpuartStatePtr[instance];

    /* Wait until the data is completely shifted out of shift register */
    while(!(LPUART_BRD_STAT_TC(base))) { }

    LPUART_HAL_SetTxDmaCmd(base, false);
    LPUART_HAL_SetRxDmaCmd(base, false);

    /* Release DMA channel. */
    DMA_DRV_FreeChannel(&lpuartDmaState->dmaLpuartRx);
    DMA_DRV_FreeChannel(&lpuartDmaState->dmaLpuartTx);

    /* Disable TX and RX */
    LPUART_HAL_SetTransmitterCmd(base, false);
    LPUART_HAL_SetReceiverCmd(base, false);

    /* Destroy TX and RX sema. */
    OSA_SemaDestroy(&lpuartDmaState->txIrqSync);
    OSA_SemaDestroy(&lpuartDmaState->rxIrqSync);

    /* Cleared state pointer. */
    g_lpuartStatePtr[instance] = NULL;

    /* Gate LPUART module clock */
    CLOCK_SYS_DisableLpuartClock(instance);

    return kStatus_LPUART_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_DmaSendDataBlocking
 * Description   :  Sends (transmits) data out through the LPUART-DMA module
 * using a blocking method.
 *
 *END**************************************************************************/
lpuart_status_t LPUART_DRV_DmaSendDataBlocking(uint32_t instance,
                                           const uint8_t * txBuff,
                                           uint32_t txSize,
                                           uint32_t timeout)
{
    assert(txBuff);
    assert(instance < LPUART_INSTANCE_COUNT);

    lpuart_dma_state_t * lpuartDmaState = (lpuart_dma_state_t *)g_lpuartStatePtr[instance];
    lpuart_status_t retVal = kStatus_LPUART_Success;
    osa_status_t syncStatus;

    /* Indicates current transaction is blocking. */
    lpuartDmaState->isTxBlocking = true;

    /* Start the transmission process */
    retVal = LPUART_DRV_DmaStartSendData(instance, txBuff, txSize);

    if (retVal == kStatus_LPUART_Success)
    {
        /* Wait until the transmit is complete. */
        do
        {
            syncStatus = OSA_SemaWait(&lpuartDmaState->txIrqSync, timeout);
        }while(syncStatus == kStatus_OSA_Idle);

        if (syncStatus != kStatus_OSA_Success)
        {
            /* Stop DMA channel. */
            DMA_DRV_StopChannel(&lpuartDmaState->dmaLpuartTx);

            /* Update the information of the module driver state */
            lpuartDmaState->isTxBusy = false;

            retVal = kStatus_LPUART_Timeout;
        }
    }

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_DmaSendData
 * Description   : This function sends (transmits) data through the LPUART module
 *                 using a non-blocking method.
 * A non-blocking (also known as synchronous) function means that the function
 * returns immediately after initiating the transmit function. The application
 * has to get the transmit status to see when the transmit is complete. In
 * other words, after calling non-blocking (asynchronous) send function, the
 * application must get the transmit status to check if transmit is completed
 * or not. The asynchronous method of transmitting and receiving allows the LPUART
 * to perform a full duplex operation (simultaneously transmit and receive).
 *
 *END**************************************************************************/
lpuart_status_t LPUART_DRV_DmaSendData(uint32_t instance,
                                   const uint8_t * txBuff,
                                   uint32_t txSize)
{
    assert(txBuff);
    assert(instance < LPUART_INSTANCE_COUNT);

    lpuart_status_t retVal = kStatus_LPUART_Success;
    lpuart_dma_state_t * lpuartDmaState = (lpuart_dma_state_t *)g_lpuartStatePtr[instance];

    /* Indicates current transaction is non-blocking. */
    lpuartDmaState->isTxBlocking = false;

    /* Start the transmission process*/
    retVal = LPUART_DRV_DmaStartSendData(instance, txBuff, txSize);

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_DmaGetTransmitStatus
 * Description   : This function returns whether the previous LPUART transmit
 * has finished. When performing an async transmit, the user can call this
 * function to ascertain the state of the current transmission: in progress
 * (or busy) or complete (success). In addition, if the transmission is still
 * in progress, the user can obtain the number of words that have been
 * currently transferred.
 *
 *END**************************************************************************/
lpuart_status_t LPUART_DRV_DmaGetTransmitStatus(uint32_t instance,
                                            uint32_t * bytesRemaining)
{
    assert(instance < LPUART_INSTANCE_COUNT);

    lpuart_dma_state_t * lpuartDmaState = (lpuart_dma_state_t *)g_lpuartStatePtr[instance];

    /* Fill in the bytes transferred. */
    if (bytesRemaining)
    {
        *bytesRemaining = DMA_DRV_GetUnfinishedBytes(&lpuartDmaState->dmaLpuartTx);
    }

    return (lpuartDmaState->isTxBusy ? kStatus_LPUART_TxBusy : kStatus_LPUART_Success);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_DmaAbortSendingData
 * Description   : This function terminates an asynchronous LPUART transmission
 * early. During an async LPUART transmission, the user has the option to
 * terminate the transmission early if the transmission is still in progress.
 *
 *END**************************************************************************/
lpuart_status_t LPUART_DRV_DmaAbortSendingData(uint32_t instance)
{
    assert(instance < LPUART_INSTANCE_COUNT);

    lpuart_dma_state_t * lpuartDmaState = (lpuart_dma_state_t *)g_lpuartStatePtr[instance];

    /* Check if a transfer is running. */
    if (!lpuartDmaState->isTxBusy)
    {
        return kStatus_LPUART_NoTransmitInProgress;
    }

    /* Stop the running transfer. */
    LPUART_DRV_DmaCompleteSendData(instance);

    return kStatus_LPUART_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_DmaReceiveDataBlocking
 * Description   : This function gets (receives) data from the LPUART module using
 * a blocking method. A blocking (also known as synchronous) function means that
 * the function does not return until the receive is complete. This blocking
 * function is used to send data through the LPUART port.
 *
 *END**************************************************************************/
lpuart_status_t LPUART_DRV_DmaReceiveDataBlocking(uint32_t instance,
                                              uint8_t * rxBuff,
                                              uint32_t rxSize,
                                              uint32_t timeout)
{
    assert(rxBuff);
    assert(instance < LPUART_INSTANCE_COUNT);

    lpuart_dma_state_t * lpuartDmaState = (lpuart_dma_state_t *)g_lpuartStatePtr[instance];
    lpuart_status_t retVal = kStatus_LPUART_Success;
    osa_status_t syncStatus;

    /* Indicates current transaction is blocking. */
    lpuartDmaState->isRxBlocking = true;

    retVal = LPUART_DRV_DmaStartReceiveData(instance, rxBuff, rxSize);

    if (retVal == kStatus_LPUART_Success)
    {
        /* Wait until all the data is received or for timeout.*/
        do
        {
            syncStatus = OSA_SemaWait(&lpuartDmaState->rxIrqSync, timeout);
        }while(syncStatus == kStatus_OSA_Idle);

        if (syncStatus != kStatus_OSA_Success)
        {
            /* Stop DMA channel. */
            DMA_DRV_StopChannel(&lpuartDmaState->dmaLpuartRx);

            /* Update the information of the module driver state */
            lpuartDmaState->isRxBusy = false;

            retVal = kStatus_LPUART_Timeout;
        }
    }

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_DmaReceiveData
 * Description   : This function gets (receives) data from the LPUART module using
 * a non-blocking method.
 * A non-blocking (also known as synchronous) function means that the function
 * returns immediately after initiating the receive function. The application
 * has to get the receive status to see when the receive is complete. In other
 * words, after calling non-blocking (asynchronous) get function, the
 * application must get the receive status to check if receive is completed or
 * not. The asynchronous method of transmitting and receiving allows the LPUART
 * to perform a full duplex operation (simultaneously transmit and receive).
 *
 *END**************************************************************************/
lpuart_status_t LPUART_DRV_DmaReceiveData(uint32_t instance,
                                      uint8_t * rxBuff,
                                      uint32_t rxSize)
{
    assert(rxBuff);
    assert(instance < LPUART_INSTANCE_COUNT);

    lpuart_status_t retVal = kStatus_LPUART_Success;
    lpuart_dma_state_t * lpuartDmaState = (lpuart_dma_state_t *)g_lpuartStatePtr[instance];

    /* Indicates current transaction is non-blocking. */
    lpuartDmaState->isRxBlocking = false;

    retVal = LPUART_DRV_DmaStartReceiveData(instance, rxBuff, rxSize);

    return retVal ;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_DmaGetReceiveStatus
 * Description   : This function returns whether the previous LPUART receive is
 * complete. When performing an async receive, the user can call this function
 * to ascertain the state of the current receive progress: in progress (or busy)
 * or complete (success). In addition, if the receive is still in progress,
 * the user can obtain the number of words that have been currently received.
 *
 *END**************************************************************************/
lpuart_status_t LPUART_DRV_DmaGetReceiveStatus(uint32_t instance,
                                           uint32_t * bytesRemaining)
{
    assert(instance < LPUART_INSTANCE_COUNT);
    lpuart_dma_state_t * lpuartDmaState = (lpuart_dma_state_t *)g_lpuartStatePtr[instance];

    /* Fill in the bytes transferred. */
    if (bytesRemaining)
    {
        *bytesRemaining = DMA_DRV_GetUnfinishedBytes(&lpuartDmaState->dmaLpuartRx);
    }

    return (lpuartDmaState->isRxBusy ? kStatus_LPUART_RxBusy : kStatus_LPUART_Success);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_DmaAbortReceivingData
 * Description   : This function shuts down the LPUART by disabling interrupts and
 * the transmitter/receiver.
 *
 *END**************************************************************************/
lpuart_status_t LPUART_DRV_DmaAbortReceivingData(uint32_t instance)
{
    assert(instance < LPUART_INSTANCE_COUNT);
    lpuart_dma_state_t * lpuartDmaState = (lpuart_dma_state_t *)g_lpuartStatePtr[instance];

    /* Check if a transfer is running. */
    if (!lpuartDmaState->isRxBusy)
    {
        return kStatus_LPUART_NoReceiveInProgress;
    }

    /* Stop the running transfer. */
    LPUART_DRV_DmaCompleteReceiveData(instance);

    return kStatus_LPUART_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_DmaCompleteSendData
 * Description   : Finish up a transmit by completing the process of sending
 * data and disabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void LPUART_DRV_DmaCompleteSendData(uint32_t instance)
{
    assert(instance < LPUART_INSTANCE_COUNT);

    lpuart_dma_state_t * lpuartDmaState = (lpuart_dma_state_t *)g_lpuartStatePtr[instance];

    /* Stop DMA channel. */
    DMA_DRV_StopChannel(&lpuartDmaState->dmaLpuartTx);

    /* Signal the synchronous completion object. */
    if (lpuartDmaState->isTxBlocking)
    {
        OSA_SemaPost(&lpuartDmaState->txIrqSync);
    }

    /* Update the information of the module driver state */
    lpuartDmaState->isTxBusy = false;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_DmaTxCallback
 * Description   : This is not a public interface.
 *
 *END**************************************************************************/
static void LPUART_DRV_DmaTxCallback(void *param, dma_channel_status_t status)
{
    LPUART_DRV_DmaCompleteSendData((uint32_t)param);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_DmaStartSendData
 * Description   : This is not a public interface.
 *
 *END**************************************************************************/
static lpuart_status_t LPUART_DRV_DmaStartSendData(uint32_t instance,
                                               const uint8_t * txBuff,
                                               uint32_t txSize)
{
    assert(instance < LPUART_INSTANCE_COUNT);

    LPUART_Type * base = g_lpuartBase[instance];
    /* Get current runtime structure. */
    lpuart_dma_state_t * lpuartDmaState = (lpuart_dma_state_t *)g_lpuartStatePtr[instance];
    dma_channel_t *chn = &lpuartDmaState->dmaLpuartTx;

    /* Check that we're not busy already transmitting data from a previous function call. */
    if (lpuartDmaState->isTxBusy)
    {
        return kStatus_LPUART_TxBusy;
    }

    /* Update LPUART DMA run-time structure. */
    lpuartDmaState->isTxBusy = true;

    DMA_DRV_ConfigTransfer(&lpuartDmaState->dmaLpuartTx, kDmaMemoryToPeripheral,
        1u, (uint32_t)txBuff, LPUART_HAL_GetDataRegAddr(base), txSize);

    DMA_DRV_StartChannel(chn);

    return kStatus_LPUART_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_DmaCompleteReceiveData
 * Description   : Finish up a receive by completing the process of receiving data
 * and disabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void LPUART_DRV_DmaCompleteReceiveData(uint32_t instance)
{
    assert(instance < LPUART_INSTANCE_COUNT);

    lpuart_dma_state_t * lpuartDmaState = (lpuart_dma_state_t *)g_lpuartStatePtr[instance];

    /* Stop DMA channel. */
    DMA_DRV_StopChannel(&lpuartDmaState->dmaLpuartRx);

    /* Signal the synchronous completion object. */
    if (lpuartDmaState->isRxBlocking)
    {
        OSA_SemaPost(&lpuartDmaState->rxIrqSync);
    }

    /* Update the information of the module driver state */
    lpuartDmaState->isRxBusy = false;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_DmaRxCallback
 * Description   : This is not a public interface.
 *
 *END**************************************************************************/
static void LPUART_DRV_DmaRxCallback(void *param, dma_channel_status_t status)
{
    LPUART_DRV_DmaCompleteReceiveData((uint32_t)param);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_DmaStartReceiveData
 * Description   : Initiate (start) a receive by beginning the process of
 * receiving data and enabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static lpuart_status_t LPUART_DRV_DmaStartReceiveData(uint32_t instance,
                                                  uint8_t * rxBuff,
                                                  uint32_t rxSize)
{
    assert(instance < LPUART_INSTANCE_COUNT);

    LPUART_Type * base = g_lpuartBase[instance];
    /* Get current runtime structure. */
    lpuart_dma_state_t * lpuartDmaState = (lpuart_dma_state_t *)g_lpuartStatePtr[instance];
    dma_channel_t *chn = &lpuartDmaState->dmaLpuartRx;

    /* Check that we're not busy already receiving data from a previous function call. */
    if (lpuartDmaState->isRxBusy)
    {
        return kStatus_LPUART_RxBusy;
    }

    /* Update LPUART DMA run-time structure. */
    lpuartDmaState->isRxBusy = true;

    DMA_DRV_ConfigTransfer(&lpuartDmaState->dmaLpuartRx, kDmaPeripheralToMemory,
        1u, LPUART_HAL_GetDataRegAddr(base), (uint32_t)rxBuff, rxSize);

    DMA_DRV_StartChannel(chn);

    return kStatus_LPUART_Success;
}

#endif /* FSL_FEATURE_SOC_LPUART_COUNT */
/*******************************************************************************
 * EOF
 ******************************************************************************/

