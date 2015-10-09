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
#include "fsl_uart_edma_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"
#include "fsl_edma_request.h"
#if FSL_FEATURE_SOC_EDMA_COUNT && FSL_FEATURE_SOC_UART_COUNT

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Pointer to uart runtime state structure */
extern void * g_uartStatePtr[UART_INSTANCE_COUNT];

/*******************************************************************************
 * Private Functions
 ******************************************************************************/
static void UART_DRV_EdmaCompleteSendData(uint32_t instance);
static void UART_DRV_EdmaTxCallback(void *param, edma_chn_status_t status);
static uart_status_t UART_DRV_EdmaStartSendData(uint32_t instance,
                                               const uint8_t * txBuff,
                                               uint32_t txSize);
static void UART_DRV_EdmaCompleteReceiveData(uint32_t instance);
static void UART_DRV_EdmaRxCallback(void *param, edma_chn_status_t status);
static uart_status_t UART_DRV_EdmaStartReceiveData(uint32_t instance,
                                                  uint8_t * rxBuff,
                                                  uint32_t rxSize);
/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_DRV_EdmaInit
 * Description   : This function initializes a UART instance for operation.
 * This function will initialize the run-time state structure to keep track of
 * the on-going transfers, ungate the clock to the UART module, initialize the
 * module to user defined settings and default settings, configure UART DMA
 * and enable the UART module transmitter and receiver.
 * The following is an example of how to set up the uart_edma_state_t and the
 * uart_user_config_t parameters and how to call the UART_DRV_EdmaInit function
 * by passing in these parameters:
 *    uart_user_config_t uartConfig;
 *    uartConfig.baudRate = 9600;
 *    uartConfig.bitCountPerChar = kUart8BitsPerChar;
 *    uartConfig.parityMode = kUartParityDisabled;
 *    uartConfig.stopBitCount = kUartOneStopBit;
 *    uart_edma_state_t uartEdmaState;
 *    UART_DRV_EdmaInit(instance, &uartEdmaState, &uartConfig);
 *
 *END**************************************************************************/
uart_status_t UART_DRV_EdmaInit(uint32_t instance,
                                uart_edma_state_t * uartEdmaStatePtr,
                                const uart_edma_user_config_t * uartUserConfig)
{
    assert(uartEdmaStatePtr && uartUserConfig);
    assert(g_uartBase[instance]);
    assert(instance < UART_INSTANCE_COUNT);
    /* This driver only support UART instances with separate DMA channels for
     * both Tx and Rx.*/
    assert(FSL_FEATURE_UART_HAS_SEPARATE_DMA_RX_TX_REQn(instance) == 1);

    UART_Type * base = g_uartBase[instance];
    uint32_t uartSourceClock = 0;
    dma_request_source_t uartTxEdmaRequest = kDmaRequestMux0Disable;
    dma_request_source_t uartRxEdmaRequest = kDmaRequestMux0Disable;

    /* Exit if current instance is already initialized. */
    if (g_uartStatePtr[instance])
    {
        return kStatus_UART_Initialized;
    }

    /* Clear the state structure for this instance. */
    memset(uartEdmaStatePtr, 0, sizeof(uart_edma_state_t));

    /* Save runtime structure pointer.*/
    g_uartStatePtr[instance] = uartEdmaStatePtr;

    /* Un-gate UART module clock */
    CLOCK_SYS_EnableUartClock(instance);

    /* Initialize UART to a known state. */
    UART_HAL_Init(base);

    /* Create Semaphore for txIrq and rxIrq. */
    OSA_SemaCreate(&uartEdmaStatePtr->txIrqSync, 0);
    OSA_SemaCreate(&uartEdmaStatePtr->rxIrqSync, 0);

    /* UART clock source is either system or bus clock depending on instance */
    uartSourceClock = CLOCK_SYS_GetUartFreq(instance);

    /* Initialize UART baud rate, bit count, parity and stop bit. */
    UART_HAL_SetBaudRate(base, uartSourceClock, uartUserConfig->baudRate);
    UART_HAL_SetBitCountPerChar(base, uartUserConfig->bitCountPerChar);
    UART_HAL_SetParityMode(base, uartUserConfig->parityMode);
#if FSL_FEATURE_UART_HAS_STOP_BIT_CONFIG_SUPPORT
    UART_HAL_SetStopBitCount(base, uartUserConfig->stopBitCount);
#endif

    switch (instance)
    {
#if (FSL_FEATURE_UART_HAS_SEPARATE_DMA_RX_TX_REQn(0) == 1)
        case 0:
            uartRxEdmaRequest = kDmaRequestMux0UART0Rx;
            uartTxEdmaRequest = kDmaRequestMux0UART0Tx;
            break;
#endif
#if (FSL_FEATURE_UART_HAS_SEPARATE_DMA_RX_TX_REQn(1) == 1)
        case 1:
            uartRxEdmaRequest = kDmaRequestMux0UART1Rx;
            uartTxEdmaRequest = kDmaRequestMux0UART1Tx;
            break;
#endif
#if (FSL_FEATURE_UART_HAS_SEPARATE_DMA_RX_TX_REQn(2) == 1)
        case 2:
            uartRxEdmaRequest = kDmaRequestMux0UART2Rx;
            uartTxEdmaRequest = kDmaRequestMux0UART2Tx;
            break;
#endif
#if (FSL_FEATURE_UART_HAS_SEPARATE_DMA_RX_TX_REQn(3) == 1)
        case 3:
            uartRxEdmaRequest = kDmaRequestMux0UART3Rx;
            uartTxEdmaRequest = kDmaRequestMux0UART3Tx;
            break;
#endif
#if (FSL_FEATURE_UART_HAS_SEPARATE_DMA_RX_TX_REQn(4) == 1)
        case 4:
            uartRxEdmaRequest = kDmaRequestMux0UART4Rx;
            uartTxEdmaRequest = kDmaRequestMux0UART4Tx;
            break;
#endif
#if (FSL_FEATURE_UART_HAS_SEPARATE_DMA_RX_TX_REQn(5) == 1)
        case 5:
            uartRxEdmaRequest = kDmaRequestMux0UART5Rx;
            uartTxEdmaRequest = kDmaRequestMux0UART5Tx;
            break;
#endif
        default :
            break;
    }

    /*--------------- Setup RX ------------------*/
    /* Request DMA channels for RX FIFO. */
    EDMA_DRV_RequestChannel(kEDMAAnyChannel, uartRxEdmaRequest,
                            &uartEdmaStatePtr->edmaUartRx);
    EDMA_DRV_InstallCallback(&uartEdmaStatePtr->edmaUartRx,
                    UART_DRV_EdmaRxCallback, (void *)instance);

    /*--------------- Setup TX ------------------*/
    /* Request DMA channels for TX FIFO. */
    EDMA_DRV_RequestChannel(kEDMAAnyChannel, uartTxEdmaRequest,
                            &uartEdmaStatePtr->edmaUartTx);
    EDMA_DRV_InstallCallback(&uartEdmaStatePtr->edmaUartTx,
                    UART_DRV_EdmaTxCallback, (void *)instance);

    /* Finally, enable the UART transmitter and receiver.
     * Enable DMA trigger when transmit data register empty,
     * and receive data register full. */
    UART_HAL_SetTxDmaCmd(base, true);
    UART_HAL_SetRxDmaCmd(base, true);
    UART_HAL_EnableTransmitter(base);
    UART_HAL_EnableReceiver(base);

    return kStatus_UART_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_DRV_EdmaDeinit
 * Description   : This function shuts down the UART by disabling UART DMA and
 *                 the transmitter/receiver.
 *
 *END**************************************************************************/
uart_status_t UART_DRV_EdmaDeinit(uint32_t instance)
{
    assert(instance < UART_INSTANCE_COUNT);
    assert(g_uartBase[instance]);

    /* Exit if current instance is already de-initialized or is gated.*/
    if ((!g_uartStatePtr[instance]) || (!CLOCK_SYS_GetUartGateCmd(instance)))
    {
        return kStatus_UART_Fail;
    }

    UART_Type * base = g_uartBase[instance];
    uart_edma_state_t * uartEdmaState = (uart_edma_state_t *)g_uartStatePtr[instance];

    /* Wait until the data is completely shifted out of shift register */
    while(!(UART_BRD_S1_TC(base))) { }

    UART_HAL_SetTxDmaCmd(base, false);
    UART_HAL_SetRxDmaCmd(base, false);

    /* Release DMA channel. */
    EDMA_DRV_ReleaseChannel(&uartEdmaState->edmaUartRx);
    EDMA_DRV_ReleaseChannel(&uartEdmaState->edmaUartTx);

    /* Disable TX and RX */
    UART_HAL_DisableTransmitter(base);
    UART_HAL_DisableReceiver(base);

    /* Destroy TX and RX sema. */
    OSA_SemaDestroy(&uartEdmaState->txIrqSync);
    OSA_SemaDestroy(&uartEdmaState->rxIrqSync);

    /* Cleared state pointer. */
    g_uartStatePtr[instance] = NULL;

    /* Gate UART module clock */
    CLOCK_SYS_DisableUartClock(instance);

    return kStatus_UART_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_DRV_EdmaSendDataBlocking
 * Description   :  Sends (transmits) data out through the UART-DMA module
 * using a blocking method.
 *
 *END**************************************************************************/
uart_status_t UART_DRV_EdmaSendDataBlocking(uint32_t instance,
                                            const uint8_t * txBuff,
                                            uint32_t txSize,
                                            uint32_t timeout)
{
    assert(txBuff);
    assert(instance < UART_INSTANCE_COUNT);

    uart_edma_state_t * uartEdmaState = (uart_edma_state_t *)g_uartStatePtr[instance];
    uart_status_t retVal = kStatus_UART_Success;
    osa_status_t syncStatus;

    /* Indicates current transaction is blocking. */
    uartEdmaState->isTxBlocking = true;

    /* Start the transmission process */
    retVal = UART_DRV_EdmaStartSendData(instance, txBuff, txSize);

    if (retVal == kStatus_UART_Success)
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

            retVal = kStatus_UART_Timeout;
        }
    }

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_DRV_EdmaSendData
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
uart_status_t UART_DRV_EdmaSendData(uint32_t instance,
                                    const uint8_t * txBuff,
                                    uint32_t txSize)
{
    assert(txBuff);
    assert(instance < UART_INSTANCE_COUNT);

    uart_status_t retVal = kStatus_UART_Success;
    uart_edma_state_t * uartEdmaState = (uart_edma_state_t *)g_uartStatePtr[instance];

    /* Indicates current transaction is non-blocking. */
    uartEdmaState->isTxBlocking = false;

    /* Start the transmission process*/
    retVal = UART_DRV_EdmaStartSendData(instance, txBuff, txSize);

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_DRV_EdmaGetTransmitStatus
 * Description   : This function returns whether the previous UART transmit
 * has finished. When performing an async transmit, the user can call this
 * function to ascertain the state of the current transmission: in progress
 * (or busy) or complete (success). In addition, if the transmission is still
 * in progress, the user can obtain the number of words that have been
 * currently transferred.
 *
 *END**************************************************************************/
uart_status_t UART_DRV_EdmaGetTransmitStatus(uint32_t instance,
                                             uint32_t * bytesRemaining)
{
    assert(instance < UART_INSTANCE_COUNT);

    uart_edma_state_t * uartEdmaState = (uart_edma_state_t *)g_uartStatePtr[instance];
    uart_status_t retVal = kStatus_UART_Success;
    uint32_t txSize = 0;

    /* EDMA will reload the major count after finish transfer, need to set
    * the count to 0 manually. */
    if (uartEdmaState->isTxBusy)
    {
        txSize = EDMA_DRV_GetUnfinishedBytes(&uartEdmaState->edmaUartTx);
        retVal = kStatus_UART_TxBusy;
    }

    /* Fill in the bytes transferred. */
    if (bytesRemaining)
    {
        *bytesRemaining = txSize;
    }

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_DRV_EdmaAbortSendingData
 * Description   : This function terminates an asynchronous UART transmission
 * early. During an async UART transmission, the user has the option to
 * terminate the transmission early if the transmission is still in progress.
 *
 *END**************************************************************************/
uart_status_t UART_DRV_EdmaAbortSendingData(uint32_t instance)
{
    assert(instance < UART_INSTANCE_COUNT);

    uart_edma_state_t * uartEdmaState = (uart_edma_state_t *)g_uartStatePtr[instance];

    /* Check if a transfer is running. */
    if (!uartEdmaState->isTxBusy)
    {
        return kStatus_UART_NoTransmitInProgress;
    }

    /* Stop the running transfer. */
    UART_DRV_EdmaCompleteSendData(instance);

    return kStatus_UART_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_DRV_EdmaReceiveDataBlocking
 * Description   : This function gets (receives) data from the UART module using
 * a blocking method. A blocking (also known as synchronous) function means that
 * the function does not return until the receive is complete. This blocking
 * function is used to send data through the UART port.
 *
 *END**************************************************************************/
uart_status_t UART_DRV_EdmaReceiveDataBlocking(uint32_t instance,
                                               uint8_t * rxBuff,
                                               uint32_t rxSize,
                                               uint32_t timeout)
{
    assert(rxBuff);
    assert(instance < UART_INSTANCE_COUNT);

    uart_edma_state_t * uartEdmaState = (uart_edma_state_t *)g_uartStatePtr[instance];
    uart_status_t retVal = kStatus_UART_Success;
    osa_status_t syncStatus;

    /* Indicates current transaction is blocking. */
    uartEdmaState->isRxBlocking = true;

    retVal = UART_DRV_EdmaStartReceiveData(instance, rxBuff, rxSize);

    if (retVal == kStatus_UART_Success)
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

            retVal = kStatus_UART_Timeout;
        }
    }

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_DRV_EdmaReceiveData
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
uart_status_t UART_DRV_EdmaReceiveData(uint32_t instance,
                                       uint8_t * rxBuff,
                                       uint32_t rxSize)
{
    assert(rxBuff);
    assert(instance < UART_INSTANCE_COUNT);

    uart_status_t retVal = kStatus_UART_Success;
    uart_edma_state_t * uartEdmaState = (uart_edma_state_t *)g_uartStatePtr[instance];

    /* Indicates current transaction is non-blocking. */
    uartEdmaState->isRxBlocking = false;

    retVal = UART_DRV_EdmaStartReceiveData(instance, rxBuff, rxSize);

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_DRV_EdmaGetReceiveStatus
 * Description   : This function returns whether the previous UART receive is
 * complete. When performing an async receive, the user can call this function
 * to ascertain the state of the current receive progress: in progress (or busy)
 * or complete (success). In addition, if the receive is still in progress,
 * the user can obtain the number of words that have been currently received.
 *
 *END**************************************************************************/
uart_status_t UART_DRV_EdmaGetReceiveStatus(uint32_t instance,
                                            uint32_t * bytesRemaining)
{
    assert(instance < UART_INSTANCE_COUNT);
    uart_edma_state_t * uartEdmaState = (uart_edma_state_t *)g_uartStatePtr[instance];
    uart_status_t retVal = kStatus_UART_Success;
    uint32_t rxSize = 0;

    /* EDMA will reload the major count after finish transfer, need to set
     * the count to 0 manually. */
    if (uartEdmaState->isRxBusy)
    {
        rxSize = EDMA_DRV_GetUnfinishedBytes(&uartEdmaState->edmaUartRx);
        retVal = kStatus_UART_RxBusy;
    }

    /* Fill in the bytes transferred. */
    if (bytesRemaining)
    {
        *bytesRemaining = rxSize;
    }

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_DRV_EdmaAbortReceivingData
 * Description   : This function shuts down the UART by disabling interrupts and
 * the transmitter/receiver.
 *
 *END**************************************************************************/
uart_status_t UART_DRV_EdmaAbortReceivingData(uint32_t instance)
{
    assert(instance < UART_INSTANCE_COUNT);
    uart_edma_state_t * uartEdmaState = (uart_edma_state_t *)g_uartStatePtr[instance];

    /* Check if a transfer is running. */
    if (!uartEdmaState->isRxBusy)
    {
        return kStatus_UART_NoReceiveInProgress;
    }

    /* Stop the running transfer. */
    UART_DRV_EdmaCompleteReceiveData(instance);

    return kStatus_UART_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_DRV_EdmaCompleteSendData
 * Description   : Finish up a transmit by completing the process of sending
 * data and disabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void UART_DRV_EdmaCompleteSendData(uint32_t instance)
{
    assert(instance < UART_INSTANCE_COUNT);

    uart_edma_state_t * uartEdmaState = (uart_edma_state_t *)g_uartStatePtr[instance];

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
 * Function Name : UART_DRV_EdmaTxCallback
 * Description   : This is not a public interface.
 *
 *END**************************************************************************/
static void UART_DRV_EdmaTxCallback(void *param, edma_chn_status_t status)
{
    UART_DRV_EdmaCompleteSendData((uint32_t)param);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_DRV_EdmaStartSendData
 * Description   : This is not a public interface.
 *
 *END**************************************************************************/
static uart_status_t UART_DRV_EdmaStartSendData(uint32_t instance,
                                                const uint8_t * txBuff,
                                                uint32_t txSize)
{
    assert(instance < UART_INSTANCE_COUNT);

    UART_Type * base = g_uartBase[instance];

    edma_transfer_config_t edmaTxConfig;
    edmaTxConfig.srcAddr            = (uint32_t)txBuff;
    edmaTxConfig.destAddr           = UART_HAL_GetDataRegAddr(base);
    edmaTxConfig.srcTransferSize    = kEDMATransferSize_1Bytes;
    edmaTxConfig.destTransferSize   = kEDMATransferSize_1Bytes;
    edmaTxConfig.srcOffset          = 1U;
    edmaTxConfig.destOffset         = 0U;
    edmaTxConfig.srcLastAddrAdjust  = 0U;
    edmaTxConfig.destLastAddrAdjust = 0U;
    edmaTxConfig.srcModulo          = kEDMAModuloDisable;
    edmaTxConfig.destModulo         = kEDMAModuloDisable;
    edmaTxConfig.minorLoopCount     = 1U;
    edmaTxConfig.majorLoopCount     = txSize;

    edma_software_tcd_t   stcd;

    /* Get current runtime structure. */
    uart_edma_state_t * uartEdmaState = (uart_edma_state_t *)g_uartStatePtr[instance];

    /* Check that we're not busy already transmitting data from a previous function call. */
    if (uartEdmaState->isTxBusy)
    {
        return kStatus_UART_TxBusy;
    }

    /* Update UART DMA run-time structure. */
    uartEdmaState->isTxBusy = true;

    memset(&stcd, 0, sizeof(edma_software_tcd_t));

    /* Sets the descriptor basic transfer for the descriptor. */
    EDMA_DRV_PrepareDescriptorTransfer(&uartEdmaState->edmaUartTx, &stcd, &edmaTxConfig, true, true);

    /* Copies the software TCD configuration to the hardware TCD */
    EDMA_DRV_PushDescriptorToReg(&uartEdmaState->edmaUartTx, &stcd);

    /* Start DMA channel */
    EDMA_DRV_StartChannel(&uartEdmaState->edmaUartTx);

    return kStatus_UART_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_DRV_EdmaCompleteReceiveData
 * Description   : Finish up a receive by completing the process of receiving data
 * and disabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void UART_DRV_EdmaCompleteReceiveData(uint32_t instance)
{
    assert(instance < UART_INSTANCE_COUNT);

    uart_edma_state_t * uartEdmaState = (uart_edma_state_t *)g_uartStatePtr[instance];

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
 * Function Name : UART_DRV_EdmaRxCallback
 * Description   : This is not a public interface.
 *
 *END**************************************************************************/
static void UART_DRV_EdmaRxCallback(void *param, edma_chn_status_t status)
{
    UART_DRV_EdmaCompleteReceiveData((uint32_t)param);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : UART_DRV_EdmaStartReceiveData
 * Description   : Initiate (start) a receive by beginning the process of
 * receiving data and enabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static uart_status_t UART_DRV_EdmaStartReceiveData(uint32_t instance,
                                                   uint8_t * rxBuff,
                                                   uint32_t rxSize)
{
    assert(instance < UART_INSTANCE_COUNT);

    UART_Type * base = g_uartBase[instance];

    edma_transfer_config_t edmaRxConfig;
    edmaRxConfig.srcAddr            = UART_HAL_GetDataRegAddr(base);
    edmaRxConfig.destAddr           = (uint32_t)rxBuff;
    edmaRxConfig.srcTransferSize    = kEDMATransferSize_1Bytes;
    edmaRxConfig.destTransferSize   = kEDMATransferSize_1Bytes;
    edmaRxConfig.srcOffset          = 0U;
    edmaRxConfig.destOffset         = 1U;
    edmaRxConfig.srcLastAddrAdjust  = 0U;
    edmaRxConfig.destLastAddrAdjust = 0U;
    edmaRxConfig.srcModulo          = kEDMAModuloDisable;
    edmaRxConfig.destModulo         = kEDMAModuloDisable;
    edmaRxConfig.minorLoopCount     = 1U;
    edmaRxConfig.majorLoopCount     = rxSize;

    edma_software_tcd_t   stcd;

    /* Get current runtime structure. */
    uart_edma_state_t * uartEdmaState = (uart_edma_state_t *)g_uartStatePtr[instance];

    /* Check that we're not busy already receiving data from a previous function call. */
    if (uartEdmaState->isRxBusy)
    {
        return kStatus_UART_RxBusy;
    }

    /* Update UART DMA run-time structure. */
    uartEdmaState->isRxBusy = true;

    memset(&stcd, 0, sizeof(edma_software_tcd_t));

    /* Sets the descriptor basic transfer for the descriptor. */
    EDMA_DRV_PrepareDescriptorTransfer(&uartEdmaState->edmaUartRx, &stcd, &edmaRxConfig, true, true);

    /* Copies the software TCD configuration to the hardware TCD */
    EDMA_DRV_PushDescriptorToReg(&uartEdmaState->edmaUartRx, &stcd);

    /* Start DMA channel */
    EDMA_DRV_StartChannel(&uartEdmaState->edmaUartRx);

    return kStatus_UART_Success;
}

#endif /* FSL_FEATURE_SOC_DMA_COUNT && FSL_FEATURE_SOC_UART_COUNT */
/*******************************************************************************
 * EOF
 ******************************************************************************/

