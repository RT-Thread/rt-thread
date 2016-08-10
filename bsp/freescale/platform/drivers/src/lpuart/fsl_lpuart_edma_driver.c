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
#include "fsl_lpuart_edma_driver.h"
#include "fsl_interrupt_manager.h"
#include "fsl_edma_request.h"

#if FSL_FEATURE_SOC_LPUART_COUNT

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Pointer to lpuart runtime state structure */
extern void * g_lpuartStatePtr[LPUART_INSTANCE_COUNT];

/*******************************************************************************
 * Private Functions
 ******************************************************************************/
static void LPUART_DRV_EdmaCompleteSendData(uint32_t instance);
static void LPUART_DRV_EdmaTxCallback(void *param, edma_chn_status_t status);
static lpuart_status_t LPUART_DRV_EdmaStartSendData(uint32_t instance,
                                                   const uint8_t * txBuff,
                                                   uint32_t txSize);
static void LPUART_DRV_EdmaCompleteReceiveData(uint32_t instance);
static void LPUART_DRV_EdmaRxCallback(void *param, edma_chn_status_t status);
static lpuart_status_t LPUART_DRV_EdmaStartReceiveData(uint32_t instance,
                                                      uint8_t * rxBuff,
                                                      uint32_t rxSize);
/*******************************************************************************
 * Code
 ******************************************************************************/

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_EdmaInit
 * Description   : This function initializes a LPUART instance for operation.
 * This function will initialize the run-time state structure to keep track of
 * the on-going transfers, ungate the clock to the LPUART module, initialize the
 * module to user defined settings and default settings, configure LPUART DMA
 * and enable the LPUART module transmitter and receiver.
 * The following is an example of how to set up the lpuart_edma_state_t and the
 * lpuart_user_config_t parameters and how to call the LPUART_DRV_EdmaInit function
 * by passing in these parameters:
 *    lpuart_user_config_t lpuartConfig;
 *    lpuartConfig.clockSource = kClockLpuartSrcPllFllSel;
 *    lpuartConfig.baudRate = 9600;
 *    lpuartConfig.bitCountPerChar = kLpuart8BitsPerChar;
 *    lpuartConfig.parityMode = kLpuartParityDisabled;
 *    lpuartConfig.stopBitCount = kLpuartOneStopBit;
 *    lpuart_edma_state_t lpuartEdmaState;
 *    LPUART_DRV_EdmaInit(instance, &lpuartEdmaState, &lpuartConfig);
 *
 *END**************************************************************************/
lpuart_status_t LPUART_DRV_EdmaInit(uint32_t instance,
                                    lpuart_edma_state_t * lpuartEdmaStatePtr,
                                    const lpuart_edma_user_config_t * lpuartUserConfig)
{
    assert(lpuartEdmaStatePtr && lpuartUserConfig);
    assert(instance < LPUART_INSTANCE_COUNT);
    /* This driver only support UART instances with separate DMA channels for
     * both Tx and Rx.*/
    assert(FSL_FEATURE_LPUART_HAS_SEPARATE_DMA_RX_TX_REQn(instance) == 1);

    LPUART_Type * base = g_lpuartBase[instance];
    uint32_t lpuartSourceClock = 0;
    dma_request_source_t lpuartTxEdmaRequest = kDmaRequestMux0Disable;
    dma_request_source_t lpuartRxEdmaRequest = kDmaRequestMux0Disable;

    /* Exit if current instance is already initialized. */
    if (g_lpuartStatePtr[instance])
    {
        return kStatus_LPUART_Initialized;
    }

    /* Clear the state structure for this instance. */
    memset(lpuartEdmaStatePtr, 0, sizeof(lpuart_edma_state_t));

    /* Save runtime structure pointer.*/
    g_lpuartStatePtr[instance] = lpuartEdmaStatePtr;

    /* Set LPUART clock source */
    CLOCK_SYS_SetLpuartSrc(instance, lpuartUserConfig->clockSource);

    /* Un-gate LPUART module clock */
    CLOCK_SYS_EnableLpuartClock(instance);

    /* Initialize LPUART to a known state. */
    LPUART_HAL_Init(base);

    /* Create Semaphore for txIrq and rxIrq. */
    OSA_SemaCreate(&lpuartEdmaStatePtr->txIrqSync, 0);
    OSA_SemaCreate(&lpuartEdmaStatePtr->rxIrqSync, 0);

    /* LPUART clock source is either system or bus clock depending on instance */
    lpuartSourceClock = CLOCK_SYS_GetLpuartFreq(instance);

    /* Initialize LPUART baud rate, bit count, parity and stop bit. */
    LPUART_HAL_SetBaudRate(base, lpuartSourceClock, lpuartUserConfig->baudRate);
    LPUART_HAL_SetBitCountPerChar(base, lpuartUserConfig->bitCountPerChar);
    LPUART_HAL_SetParityMode(base, lpuartUserConfig->parityMode);
    LPUART_HAL_SetStopBitCount(base, lpuartUserConfig->stopBitCount);

    switch (instance)
    {
#if (FSL_FEATURE_LPUART_HAS_SEPARATE_DMA_RX_TX_REQn(0) == 1)
        case 0:
            lpuartRxEdmaRequest = kDmaRequestMux0LPUART0Rx;
            lpuartTxEdmaRequest = kDmaRequestMux0LPUART0Tx;
            break;
#endif
#if (FSL_FEATURE_LPUART_HAS_SEPARATE_DMA_RX_TX_REQn(1) == 1)
        case 1:
            lpuartRxEdmaRequest = kDmaRequestMux0LPUART1Rx;
            lpuartTxEdmaRequest = kDmaRequestMux0LPUART1Tx;
            break;
#endif
#if (FSL_FEATURE_LPUART_HAS_SEPARATE_DMA_RX_TX_REQn(2) == 1)
        case 2:
            lpuartRxEdmaRequest = kDmaRequestMux0LPUART2Rx;
            lpuartTxEdmaRequest = kDmaRequestMux0LPUART2Tx;
            break;
#endif
#if (FSL_FEATURE_LPUART_HAS_SEPARATE_DMA_RX_TX_REQn(3) == 1)
        case 3:
            lpuartRxEdmaRequest = kDmaRequestMux0LPUART3Rx;
            lpuartTxEdmaRequest = kDmaRequestMux0LPUART3Tx;
            break;
#endif
#if (FSL_FEATURE_LPUART_HAS_SEPARATE_DMA_RX_TX_REQn(4) == 1)
        case 4:
            lpuartRxEdmaRequest = kDmaRequestMux0LPUART4Rx;
            lpuartTxEdmaRequest = kDmaRequestMux0LPUART4Tx;
            break;
#endif
        default :
            break;
    }

    /*--------------- Setup RX ------------------*/
    /* Request DMA channels for RX FIFO. */
    EDMA_DRV_RequestChannel(kEDMAAnyChannel, lpuartRxEdmaRequest,
                            &lpuartEdmaStatePtr->edmaLpuartRx);
    EDMA_DRV_InstallCallback(&lpuartEdmaStatePtr->edmaLpuartRx,
                    LPUART_DRV_EdmaRxCallback, (void *)instance);

    /*--------------- Setup TX ------------------*/
    /* Request DMA channels for TX FIFO. */
    EDMA_DRV_RequestChannel(kEDMAAnyChannel, lpuartTxEdmaRequest,
                            &lpuartEdmaStatePtr->edmaLpuartTx);
    EDMA_DRV_InstallCallback(&lpuartEdmaStatePtr->edmaLpuartTx,
                    LPUART_DRV_EdmaTxCallback, (void *)instance);

    /* Finally, enable the LPUART transmitter and receiver.
     * Enable DMA trigger when transmit data register empty,
     * and receive data register full. */
    LPUART_HAL_SetTxDmaCmd(base, true);
    LPUART_HAL_SetRxDmaCmd(base, true);
    LPUART_HAL_SetTransmitterCmd(base, true);
    LPUART_HAL_SetReceiverCmd(base, true);

    return kStatus_LPUART_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_EdmaDeinit
 * Description   : This function shuts down the LPUART by disabling LPUART DMA and
 *                 the transmitter/receiver.
 *
 *END**************************************************************************/
lpuart_status_t LPUART_DRV_EdmaDeinit(uint32_t instance)
{
    assert(instance < LPUART_INSTANCE_COUNT);

    /* Exit if current instance is already de-initialized or is gated.*/
    if ((!g_lpuartStatePtr[instance]) || (!CLOCK_SYS_GetLpuartGateCmd(instance)))
    {
        return kStatus_LPUART_Fail;
    }

    LPUART_Type * base = g_lpuartBase[instance];
    lpuart_edma_state_t * lpuartEdmaState = (lpuart_edma_state_t *)g_lpuartStatePtr[instance];

    /* Wait until the data is completely shifted out of shift register */
    while(!(LPUART_BRD_STAT_TC(base))) { }

    LPUART_HAL_SetTxDmaCmd(base, false);
    LPUART_HAL_SetRxDmaCmd(base, false);

    /* Release DMA channel. */
    EDMA_DRV_ReleaseChannel(&lpuartEdmaState->edmaLpuartRx);
    EDMA_DRV_ReleaseChannel(&lpuartEdmaState->edmaLpuartTx);

    /* Disable TX and RX */
    LPUART_HAL_SetTransmitterCmd(base, false);
    LPUART_HAL_SetReceiverCmd(base, false);

    /* Destroy TX and RX sema. */
    OSA_SemaDestroy(&lpuartEdmaState->txIrqSync);
    OSA_SemaDestroy(&lpuartEdmaState->rxIrqSync);

    /* Cleared state pointer. */
    g_lpuartStatePtr[instance] = NULL;

    /* Gate LPUART module clock */
    CLOCK_SYS_DisableLpuartClock(instance);

    return kStatus_LPUART_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_EdmaSendDataBlocking
 * Description   :  Sends (transmits) data out through the LPUART-DMA module
 * using a blocking method.
 *
 *END**************************************************************************/
lpuart_status_t LPUART_DRV_EdmaSendDataBlocking(uint32_t instance,
                                                const uint8_t * txBuff,
                                                uint32_t txSize,
                                                uint32_t timeout)
{
    assert(txBuff);
    assert(instance < LPUART_INSTANCE_COUNT);

    lpuart_edma_state_t * lpuartEdmaState = (lpuart_edma_state_t *)g_lpuartStatePtr[instance];
    lpuart_status_t retVal = kStatus_LPUART_Success;
    osa_status_t syncStatus;

    /* Indicates current transaction is blocking. */
    lpuartEdmaState->isTxBlocking = true;

    /* Start the transmission process */
    retVal = LPUART_DRV_EdmaStartSendData(instance, txBuff, txSize);

    if (retVal == kStatus_LPUART_Success)
    {
        /* Wait until the transmit is complete. */
        do
        {
            syncStatus = OSA_SemaWait(&lpuartEdmaState->txIrqSync, timeout);
        }while(syncStatus == kStatus_OSA_Idle);

        if (syncStatus != kStatus_OSA_Success)
        {

            /* Stop DMA channel. */
            EDMA_DRV_StopChannel(&lpuartEdmaState->edmaLpuartTx);

            /* Update the information of the module driver state */
            lpuartEdmaState->isTxBusy = false;

            retVal = kStatus_LPUART_Timeout;
        }
    }

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_EdmaSendData
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
lpuart_status_t LPUART_DRV_EdmaSendData(uint32_t instance,
                                        const uint8_t * txBuff,
                                        uint32_t txSize)
{
    assert(txBuff);
    assert(instance < LPUART_INSTANCE_COUNT);

    lpuart_status_t retVal = kStatus_LPUART_Success;
    lpuart_edma_state_t * lpuartEdmaState = (lpuart_edma_state_t *)g_lpuartStatePtr[instance];

    /* Indicates current transaction is non-blocking. */
    lpuartEdmaState->isTxBlocking = false;

    /* Start the transmission process*/
    retVal = LPUART_DRV_EdmaStartSendData(instance, txBuff, txSize);

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_EdmaGetTransmitStatus
 * Description   : This function returns whether the previous LPUART transmit
 * has finished. When performing an async transmit, the user can call this
 * function to ascertain the state of the current transmission: in progress
 * (or busy) or complete (success). In addition, if the transmission is still
 * in progress, the user can obtain the number of words that have been
 * currently transferred.
 *
 *END**************************************************************************/
lpuart_status_t LPUART_DRV_EdmaGetTransmitStatus(uint32_t instance,
                                                uint32_t * bytesRemaining)
{
    assert(instance < LPUART_INSTANCE_COUNT);

    lpuart_edma_state_t * lpuartEdmaState = (lpuart_edma_state_t *)g_lpuartStatePtr[instance];
    lpuart_status_t retVal = kStatus_LPUART_Success;
    uint32_t txSize = 0;

    /* EDMA will reload the major count after finish transfer, need to set
     * the count to 0 manually. */
    if (lpuartEdmaState->isTxBusy)
    {
        txSize = EDMA_DRV_GetUnfinishedBytes(&lpuartEdmaState->edmaLpuartTx);
        retVal = kStatus_LPUART_TxBusy;
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
 * Function Name : LPUART_DRV_EdmaAbortSendingData
 * Description   : This function terminates an asynchronous LPUART transmission
 * early. During an async LPUART transmission, the user has the option to
 * terminate the transmission early if the transmission is still in progress.
 *
 *END**************************************************************************/
lpuart_status_t LPUART_DRV_EdmaAbortSendingData(uint32_t instance)
{
    assert(instance < LPUART_INSTANCE_COUNT);

    lpuart_edma_state_t * lpuartEdmaState = (lpuart_edma_state_t *)g_lpuartStatePtr[instance];

    /* Check if a transfer is running. */
    if (!lpuartEdmaState->isTxBusy)
    {
        return kStatus_LPUART_NoTransmitInProgress;
    }

    /* Stop the running transfer. */
    LPUART_DRV_EdmaCompleteSendData(instance);

    return kStatus_LPUART_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_EdmaReceiveDataBlocking
 * Description   : This function gets (receives) data from the LPUART module using
 * a blocking method. A blocking (also known as synchronous) function means that
 * the function does not return until the receive is complete. This blocking
 * function is used to send data through the LPUART port.
 *
 *END**************************************************************************/
lpuart_status_t LPUART_DRV_EdmaReceiveDataBlocking(uint32_t instance,
                                                   uint8_t * rxBuff,
                                                   uint32_t rxSize,
                                                   uint32_t timeout)
{
    assert(rxBuff);
    assert(instance < LPUART_INSTANCE_COUNT);

    lpuart_edma_state_t * lpuartEdmaState = (lpuart_edma_state_t *)g_lpuartStatePtr[instance];
    lpuart_status_t retVal = kStatus_LPUART_Success;
    osa_status_t syncStatus;

    /* Indicates current transaction is blocking. */
    lpuartEdmaState->isRxBlocking = true;

    retVal = LPUART_DRV_EdmaStartReceiveData(instance, rxBuff, rxSize);

    if (retVal == kStatus_LPUART_Success)
    {
        /* Wait until all the data is received or for timeout.*/
        do
        {
            syncStatus = OSA_SemaWait(&lpuartEdmaState->rxIrqSync, timeout);
        }while(syncStatus == kStatus_OSA_Idle);

        if (syncStatus != kStatus_OSA_Success)
        {

            /* Stop DMA channel. */
            EDMA_DRV_StopChannel(&lpuartEdmaState->edmaLpuartRx);

            /* Update the information of the module driver state */
            lpuartEdmaState->isRxBusy = false;

            retVal = kStatus_LPUART_Timeout;
        }
    }

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_EdmaReceiveData
 * Description   : This function gets (receives) data from the LPUART module
 * using a non-blocking method.
 * A non-blocking (also known as synchronous) function means that the function
 * returns immediately after initiating the receive function. The application
 * has to get the receive status to see when the receive is complete. In other
 * words, after calling non-blocking (asynchronous) get function, the
 * application must get the receive status to check if receive is completed or
 * not. The asynchronous method of transmitting and receiving allows the LPUART
 * to perform a full duplex operation (simultaneously transmit and receive).
 *
 *END**************************************************************************/
lpuart_status_t LPUART_DRV_EdmaReceiveData(uint32_t instance,
                                          uint8_t * rxBuff,
                                          uint32_t rxSize)
{
    assert(rxBuff);
    assert(instance < LPUART_INSTANCE_COUNT);

    lpuart_status_t retVal = kStatus_LPUART_Success;
    lpuart_edma_state_t * lpuartEdmaState = (lpuart_edma_state_t *)g_lpuartStatePtr[instance];

    lpuartEdmaState->isRxBlocking = false;

    retVal = LPUART_DRV_EdmaStartReceiveData(instance, rxBuff, rxSize);

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_EdmaGetReceiveStatus
 * Description   : This function returns whether the previous LPUART receive is
 * complete. When performing an async receive, the user can call this function
 * to ascertain the state of the current receive progress: in progress (or busy)
 * or complete (success). In addition, if the receive is still in progress,
 * the user can obtain the number of words that have been currently received.
 *
 *END**************************************************************************/
lpuart_status_t LPUART_DRV_EdmaGetReceiveStatus(uint32_t instance,
                                                uint32_t * bytesRemaining)
{
    assert(instance < LPUART_INSTANCE_COUNT);
    lpuart_edma_state_t * lpuartEdmaState = (lpuart_edma_state_t *)g_lpuartStatePtr[instance];
    lpuart_status_t retVal = kStatus_LPUART_Success;
    uint32_t rxSize = 0;

    /* EDMA will reload the major count after finish transfer, need to set
     * the count to 0 manually. */
    if (lpuartEdmaState->isRxBusy)
    {
        rxSize = EDMA_DRV_GetUnfinishedBytes(&lpuartEdmaState->edmaLpuartRx);
        retVal = kStatus_LPUART_RxBusy;
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
 * Function Name : LPUART_DRV_EdmaAbortReceivingData
 * Description   : This function shuts down the LPUART by disabling interrupts and
 * the transmitter/receiver.
 *
 *END**************************************************************************/
lpuart_status_t LPUART_DRV_EdmaAbortReceivingData(uint32_t instance)
{
    assert(instance < LPUART_INSTANCE_COUNT);
    lpuart_edma_state_t * lpuartEdmaState = (lpuart_edma_state_t *)g_lpuartStatePtr[instance];

    /* Check if a transfer is running. */
    if (!lpuartEdmaState->isRxBusy)
    {
        return kStatus_LPUART_NoReceiveInProgress;
    }

    /* Stop the running transfer. */
    LPUART_DRV_EdmaCompleteReceiveData(instance);

    return kStatus_LPUART_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_EdmaCompleteSendData
 * Description   : Finish up a transmit by completing the process of sending
 * data and disabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void LPUART_DRV_EdmaCompleteSendData(uint32_t instance)
{
    assert(instance < LPUART_INSTANCE_COUNT);

    lpuart_edma_state_t * lpuartEdmaState = (lpuart_edma_state_t *)g_lpuartStatePtr[instance];

    /* Stop DMA channel. */
    EDMA_DRV_StopChannel(&lpuartEdmaState->edmaLpuartTx);

    /* Signal the synchronous completion object. */
    if (lpuartEdmaState->isTxBlocking)
    {
        OSA_SemaPost(&lpuartEdmaState->txIrqSync);
    }

    /* Update the information of the module driver state */
    lpuartEdmaState->isTxBusy = false;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_EdmaTxCallback
 * Description   : This is not a public interface.
 *
 *END**************************************************************************/
static void LPUART_DRV_EdmaTxCallback(void *param, edma_chn_status_t status)
{
    LPUART_DRV_EdmaCompleteSendData((uint32_t)param);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_EdmaStartSendData
 * Description   : This is not a public interface.
 *
 *END**************************************************************************/
static lpuart_status_t LPUART_DRV_EdmaStartSendData(uint32_t instance,
                                                    const uint8_t * txBuff,
                                                    uint32_t txSize)
{
    assert(instance < LPUART_INSTANCE_COUNT);

    LPUART_Type * base = g_lpuartBase[instance];

    edma_transfer_config_t edmaTxConfig;
    edmaTxConfig.srcAddr            = (uint32_t)txBuff;
    edmaTxConfig.destAddr           = LPUART_HAL_GetDataRegAddr(base);
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
    lpuart_edma_state_t * lpuartEdmaState = (lpuart_edma_state_t *)g_lpuartStatePtr[instance];

    /* Check that we're not busy already transmitting data from a previous function call. */
    if (lpuartEdmaState->isTxBusy)
    {
        return kStatus_LPUART_TxBusy;
    }

    /* Update LPUART DMA run-time structure. */
    lpuartEdmaState->isTxBusy = true;

    memset(&stcd, 0, sizeof(edma_software_tcd_t));

    /* Sets the descriptor basic transfer for the descriptor. */
    EDMA_DRV_PrepareDescriptorTransfer(&lpuartEdmaState->edmaLpuartTx, &stcd, &edmaTxConfig, true, true);

    /* Copies the software TCD configuration to the hardware TCD */
    EDMA_DRV_PushDescriptorToReg(&lpuartEdmaState->edmaLpuartTx, &stcd);

    /* Start DMA channel */
    EDMA_DRV_StartChannel(&lpuartEdmaState->edmaLpuartTx);

    return kStatus_LPUART_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_EdmaCompleteReceiveData
 * Description   : Finish up a receive by completing the process of receiving data
 * and disabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void LPUART_DRV_EdmaCompleteReceiveData(uint32_t instance)
{
    assert(instance < LPUART_INSTANCE_COUNT);

    lpuart_edma_state_t * lpuartEdmaState = (lpuart_edma_state_t *)g_lpuartStatePtr[instance];

    /* Stop DMA channel. */
    EDMA_DRV_StopChannel(&lpuartEdmaState->edmaLpuartRx);

    /* Signal the synchronous completion object. */
    if (lpuartEdmaState->isRxBlocking)
    {
        OSA_SemaPost(&lpuartEdmaState->rxIrqSync);
    }

    /* Update the information of the module driver state */
    lpuartEdmaState->isRxBusy = false;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_EdmaRxCallback
 * Description   : This is not a public interface.
 *
 *END**************************************************************************/
static void LPUART_DRV_EdmaRxCallback(void *param, edma_chn_status_t status)
{
    LPUART_DRV_EdmaCompleteReceiveData((uint32_t)param);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_EdmaStartReceiveData
 * Description   : Initiate (start) a receive by beginning the process of
 * receiving data and enabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static lpuart_status_t LPUART_DRV_EdmaStartReceiveData(uint32_t instance,
                                                       uint8_t * rxBuff,
                                                       uint32_t rxSize)
{
    assert(instance < LPUART_INSTANCE_COUNT);

    LPUART_Type * base = g_lpuartBase[instance];

    edma_transfer_config_t edmaRxConfig;
    edmaRxConfig.srcAddr            = LPUART_HAL_GetDataRegAddr(base);
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
    lpuart_edma_state_t * lpuartEdmaState = (lpuart_edma_state_t *)g_lpuartStatePtr[instance];

    /* Check that we're not busy already receiving data from a previous function call. */
    if (lpuartEdmaState->isRxBusy)
    {
        return kStatus_LPUART_RxBusy;
    }

    /* Update LPUART DMA run-time structure. */
    lpuartEdmaState->isRxBusy = true;

    memset(&stcd, 0, sizeof(edma_software_tcd_t));

    /* Sets the descriptor basic transfer for the descriptor. */
    EDMA_DRV_PrepareDescriptorTransfer(&lpuartEdmaState->edmaLpuartRx, &stcd, &edmaRxConfig, true, true);

    /* Copies the software TCD configuration to the hardware TCD */
    EDMA_DRV_PushDescriptorToReg(&lpuartEdmaState->edmaLpuartRx, &stcd);

    /* Start DMA channel */
    EDMA_DRV_StartChannel(&lpuartEdmaState->edmaLpuartRx);

    return kStatus_LPUART_Success;
}

#endif /* FSL_FEATURE_SOC_LPUART_COUNT */
/*******************************************************************************
 * EOF
 ******************************************************************************/

