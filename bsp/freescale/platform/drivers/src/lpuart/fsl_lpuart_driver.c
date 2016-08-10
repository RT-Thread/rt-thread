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
#include "fsl_lpuart_driver.h"
#include "fsl_interrupt_manager.h"

#if FSL_FEATURE_SOC_LPUART_COUNT

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Pointer to lpuart runtime state structure */
extern void * g_lpuartStatePtr[LPUART_INSTANCE_COUNT];

/*******************************************************************************
 * Private Functions
 ******************************************************************************/
static lpuart_status_t LPUART_DRV_StartSendData(uint32_t instance,
                                                const uint8_t * txBuff,
                                                uint32_t txSize);
static void LPUART_DRV_CompleteSendData(uint32_t instance);
static lpuart_status_t LPUART_DRV_StartReceiveData(uint32_t instance,
                                                   uint8_t * rxBuff,
                                                   uint32_t rxSize);
static void LPUART_DRV_CompleteReceiveData(uint32_t instance);
/*******************************************************************************
 * Code
 ******************************************************************************/
/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_Init
 * Description   : This function initializes a LPUART instance for operation.
 * This function will initialize the run-time state structure to keep track of
 * the on-going transfers, ungate the clock to the LPUART module, initialize the
 * module to user defined settings and default settings, configure the IRQ state
 * structure and enable the module-level interrupt to the core, and enable the
 * LPUART module transmitter and receiver.
 * The following is an example of how to set up the lpuart_state_t and the
 * lpuart_user_config_t parameters and how to call the LPUART_DRV_Init function
 * by passing in these parameters:
 *    lpuart_user_config_t lpuartConfig;
 *    lpuartConfig.clockSource = kClockLpuartSrcPllFllSel;
 *    lpuartConfig.baudRate = 9600;
 *    lpuartConfig.bitCountPerChar = klpuart8BitsPerChar;
 *    lpuartConfig.parityMode = klpuartParityDisabled;
 *    lpuartConfig.stopBitCount = klpuartOneStopBit;
 *    lpuart_state_t lpuartState;
 *    LPUART_DRV_Init(instance, &lpuartState, &lpuartConfig);
 *
 *END**************************************************************************/
lpuart_status_t LPUART_DRV_Init(uint32_t instance, lpuart_state_t * lpuartStatePtr,
                                const lpuart_user_config_t * lpuartUserConfig)
{
    assert(lpuartStatePtr && lpuartUserConfig);
    assert(instance < LPUART_INSTANCE_COUNT);

    uint32_t lpuartSourceClock;
    LPUART_Type * base = g_lpuartBase[instance];

    /* Exit if current instance is already initialized. */
    if (g_lpuartStatePtr[instance])
    {
        return kStatus_LPUART_Initialized;
    }

    /* Clear the state struct for this instance. */
    memset(lpuartStatePtr, 0, sizeof(lpuart_state_t));

    /* Save runtime structure pointer.*/
    g_lpuartStatePtr[instance] = lpuartStatePtr;

    /* Set LPUART clock source */
    CLOCK_SYS_SetLpuartSrc(instance, lpuartUserConfig->clockSource);

    /* ungate lpuart module clock */
    CLOCK_SYS_EnableLpuartClock(instance);

    /* initialize the LPUART instance */
    LPUART_HAL_Init(base);

    /* Init the interrupt sync object. */
    OSA_SemaCreate(&lpuartStatePtr->txIrqSync, 0);
    OSA_SemaCreate(&lpuartStatePtr->rxIrqSync, 0);

    /* LPUART clock source is either system clock or bus clock depending on the instance */
    lpuartSourceClock = CLOCK_SYS_GetLpuartFreq(instance);

    /* initialize the parameters of the LPUART config structure with desired data */
    LPUART_HAL_SetBaudRate(base, lpuartSourceClock, lpuartUserConfig->baudRate);
    LPUART_HAL_SetBitCountPerChar(base, lpuartUserConfig->bitCountPerChar);
    LPUART_HAL_SetParityMode(base, lpuartUserConfig->parityMode);
    LPUART_HAL_SetStopBitCount(base, lpuartUserConfig->stopBitCount);

#if FSL_FEATURE_LPUART_HAS_FIFO
    uint8_t fifoSize;
    /* Obtain raw TX FIFO size bit setting */
    fifoSize = LPUART_HAL_GetTxFifoSize(base);
    /* Now calculate the number of data words per given FIFO size */
    lpuartStatePtr->txFifoEntryCount = (fifoSize == 0 ? 1 : 0x1 << (fifoSize + 1));

    /* Configure the TX FIFO watermark to be 1/2 of the total entry or 0 if
     * entry count = 1 A watermark setting of 0 for TX FIFO entry count of 1
     * means that TDRE will only interrupt when the TX buffer (the one entry in
     * the TX FIFO) is empty. Otherwise, if we set the watermark to 1, the TDRE
     * will always be set regardless if the TX buffer was empty or not as the
     * spec says TDRE will set when the FIFO is at or below the configured
     * watermark. */
    if (lpuartStatePtr->txFifoEntryCount > 1)
    {
        LPUART_HAL_SetTxFifoWatermark(base, (lpuartStatePtr->txFifoEntryCount >> 1U));
    }
    else
    {
        LPUART_HAL_SetTxFifoWatermark(base, 0);
    }

    /* Configure the RX FIFO watermark to be 0.
     * Note about RX FIFO support: There is only one RX data full interrupt that
     * is associated with the RX FIFO Watermark. The watermark cannot be
     * dynamically changed. This means if the rxSize is less or equal to the programmed
     * watermark the interrupt will never occur. If we try to change the
     * watermark, this will involve shutting down the receiver first - which is
     * not a desirable operation when the LPUART is actively receiving data.
     * Hence, the best solution is to set the RX FIFO watermark to 0. */
    LPUART_HAL_SetRxFifoWatermark(base, 0);

    /* Enable and flush the FIFO prior to enabling the TX/RX */
    LPUART_HAL_SetTxFifoCmd(base, true);
    LPUART_HAL_SetRxFifoCmd(base, true);
    LPUART_HAL_FlushTxFifo(base);
    LPUART_HAL_FlushRxFifo(base);
#else
    /* For modules that do not support a FIFO, they have a data buffer that
     * essentially acts likes a one-entry FIFO, thus to make the code cleaner,
     * we'll equate txFifoEntryCount to 1. Also note that TDRE flag will set
     * only when the tx buffer is empty. */
    lpuartStatePtr->txFifoEntryCount = 1;
#endif

    /* finally, enable the LPUART transmitter and receiver */
    LPUART_HAL_SetTransmitterCmd(base, true);
    LPUART_HAL_SetReceiverCmd(base, true);

    /* Enable LPUART interrupt. */
    INT_SYS_EnableIRQ(g_lpuartRxTxIrqId[instance]);

    return kStatus_LPUART_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_Deinit
 * Description   : This function shuts down the UART by disabling interrupts, 
 *                 transmitter/receiver and flushing FIFOs (if module supports FIFO).
 *
 *END**************************************************************************/
lpuart_status_t LPUART_DRV_Deinit(uint32_t instance)
{
    assert(instance < LPUART_INSTANCE_COUNT);

    /* Exit if current instance is already de-initialized or is gated.*/
    if ((!g_lpuartStatePtr[instance]) || (!CLOCK_SYS_GetLpuartGateCmd(instance)))
    {
        return kStatus_LPUART_Fail;
    }

    LPUART_Type * base = g_lpuartBase[instance];
    lpuart_state_t * lpuartState = (lpuart_state_t *)g_lpuartStatePtr[instance];

    /* In case there is still data in the TX FIFO or shift register that is
     * being transmitted wait till transmit is complete. */
#if FSL_FEATURE_LPUART_HAS_FIFO
    /* Wait until there all of the data has been drained from the TX FIFO */
    while(LPUART_HAL_GetTxDatawordCountInFifo(base) != 0) { }
#endif
    /* Wait until the data is completely shifted out of shift register */
    while (!LPUART_BRD_STAT_TC(base)) {}

    /* Disable LPUART interrupt. */
    INT_SYS_DisableIRQ(g_lpuartRxTxIrqId[instance]);

    /* disable tx and rx */
    LPUART_HAL_SetTransmitterCmd(base, false);
    LPUART_HAL_SetReceiverCmd(base, false);

    /* Destroy TX and RX sema. */
    OSA_SemaDestroy(&lpuartState->txIrqSync);
    OSA_SemaDestroy(&lpuartState->rxIrqSync);

#if FSL_FEATURE_LPUART_HAS_FIFO
    /* Disable the FIFOs; should be done after disabling the TX/RX */
    LPUART_HAL_SetTxFifoCmd(base, false);
    LPUART_HAL_SetRxFifoCmd(base, false);
    LPUART_HAL_FlushTxFifo(base);
    LPUART_HAL_FlushRxFifo(base);
#endif

    /* Clear our saved pointer to the state structure */
    g_lpuartStatePtr[instance] = NULL;

    /* gate lpuart module clock */
    CLOCK_SYS_DisableLpuartClock(instance);

    return kStatus_LPUART_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_InstallRxCallback
 * Description   : Install receive data callback function.
 *
 *END**************************************************************************/
lpuart_rx_callback_t LPUART_DRV_InstallRxCallback(uint32_t instance,
                                                lpuart_rx_callback_t function,
                                                uint8_t * rxBuff,
                                                void * callbackParam,
                                                bool alwaysEnableRxIrq)
{
    assert(instance < LPUART_INSTANCE_COUNT);
    LPUART_Type * base = g_lpuartBase[instance];
    lpuart_state_t * lpuartState = (lpuart_state_t *)g_lpuartStatePtr[instance];

    lpuart_rx_callback_t currentCallback = lpuartState->rxCallback;
    lpuartState->rxCallback = function;
    lpuartState->rxCallbackParam = callbackParam;
    lpuartState->rxBuff = rxBuff;

    /* Enable/Disable the receive data full interrupt */
    lpuartState->isRxBusy = true;
    LPUART_BWR_CTRL_RIE(base, alwaysEnableRxIrq);

    return currentCallback;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_InstallTxCallback
 * Description   : Install transmit data callback function, pass in NULL pointer
 * as callback will uninstall.
 *
 *END**************************************************************************/
lpuart_tx_callback_t LPUART_DRV_InstallTxCallback(uint32_t instance,
                                                  lpuart_tx_callback_t function,
                                                  uint8_t * txBuff,
                                                  void * callbackParam)
{
    assert(instance < LPUART_INSTANCE_COUNT);
    lpuart_state_t * lpuartState = (lpuart_state_t *)g_lpuartStatePtr[instance];

    lpuart_tx_callback_t currentCallback = lpuartState->txCallback;
    lpuartState->txCallback = function;
    lpuartState->txCallbackParam = callbackParam;
    lpuartState->txBuff = txBuff;

    return currentCallback;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_SendDataBlocking
 * Description   : This function sends data out through the LPUART module using
 * blocking method. The function does not return until the transmit is complete.
 *
 *END**************************************************************************/
lpuart_status_t LPUART_DRV_SendDataBlocking(uint32_t instance,
                                            const uint8_t * txBuff,
                                            uint32_t txSize,
                                            uint32_t timeout)
{
    assert(txBuff);
    assert(instance < LPUART_INSTANCE_COUNT);

    lpuart_state_t * lpuartState = (lpuart_state_t *)g_lpuartStatePtr[instance];
    LPUART_Type * base = g_lpuartBase[instance];
    lpuart_status_t retVal = kStatus_LPUART_Success;
    osa_status_t syncStatus;

    /* Indicates this is a blocking transaction. */
    lpuartState->isTxBlocking = true;

    /* Start the transmission process */
    retVal = LPUART_DRV_StartSendData(instance, txBuff, txSize);

    if (retVal == kStatus_LPUART_Success)
    {
        /* Wait until the transmit is complete. */
        do
        {
            syncStatus = OSA_SemaWait(&lpuartState->txIrqSync, timeout);
        } while(syncStatus == kStatus_OSA_Idle);

        if (syncStatus != kStatus_OSA_Success)
        {
            /* Disable transmission complete interrupt */
            LPUART_BWR_CTRL_TIE(base, 0U);

            /* Update the information of the module driver state */
            lpuartState->isTxBusy = false;

            retVal = kStatus_LPUART_Timeout;
        }

#if FSL_FEATURE_LPUART_HAS_FIFO
        /* Wait till the TX FIFO is empty before returning. */
        while(LPUART_HAL_GetTxDatawordCountInFifo(base) != 0) { }
#endif        

    }

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_StartSendData
 * Description   : This function sends data out through the LPUART module using
 * non-blocking method. The function will return immediately after calling this
 * function.
 *
 *END**************************************************************************/
lpuart_status_t LPUART_DRV_SendData(uint32_t instance,
                                    const uint8_t * txBuff,
                                    uint32_t txSize)
{
    assert(txBuff);
    assert(instance < LPUART_INSTANCE_COUNT);

    lpuart_status_t retVal = kStatus_LPUART_Success;
    lpuart_state_t * lpuartState = (lpuart_state_t *)g_lpuartStatePtr[instance];

    /* Indicates this is a non-blocking transaction. */
    lpuartState->isTxBlocking = false;

    /* Start the transmission process */
    retVal = LPUART_DRV_StartSendData(instance, txBuff, txSize);

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_GetTransmitStatus
 * Description   : This function returns whether the previous LPUART transmit has
 * finished. When performing non-blocking transmit, the user can call this
 * function to ascertain the state of the current transmission:
 * in progress (or busy) or complete (success). In addition, if the transmission
 * is still in progress, the user can obtain the number of words that have been
 * currently transferred.
 *
 *END**************************************************************************/
lpuart_status_t LPUART_DRV_GetTransmitStatus(uint32_t instance, uint32_t * bytesRemaining)
{
    assert(instance < LPUART_INSTANCE_COUNT);

    lpuart_state_t * lpuartState = (lpuart_state_t *)g_lpuartStatePtr[instance];
    lpuart_status_t retVal = kStatus_LPUART_Success;
    uint32_t txSize = lpuartState->txSize;

    /* Fill in the bytes transferred. This may return that all bytes were
     * transmitted, however, for IPs with FIFO support, there still may be data
     * in the TX FIFO in the process of being transmitted. */
    if (bytesRemaining)
    {
        *bytesRemaining = txSize;
    }

    if (txSize)
    {
        retVal = kStatus_LPUART_TxBusy;
    }
#if FSL_FEATURE_LPUART_HAS_FIFO    
    else
    {
        LPUART_Type * base = g_lpuartBase[instance];

        if (LPUART_HAL_GetTxDatawordCountInFifo(base))
        {
            retVal = kStatus_LPUART_TxBusy;
        }
    }    
#endif
    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_AbortSendingData
 * Description   : This function terminates an non-blocking LPUART transmission
 * early. During a non-blocking LPUART transmission, the user has the option to
 * terminate the transmission early if the transmission is still in progress.
 *
 *END**************************************************************************/
lpuart_status_t LPUART_DRV_AbortSendingData(uint32_t instance)
{
    assert(instance < LPUART_INSTANCE_COUNT);

    lpuart_state_t * lpuartState = (lpuart_state_t *)g_lpuartStatePtr[instance];

    /* Check if a transfer is running. */
    if (!lpuartState->isTxBusy)
    {
        return kStatus_LPUART_NoTransmitInProgress;
    }

    /* Stop the running transfer. */
    LPUART_DRV_CompleteSendData(instance);

    return kStatus_LPUART_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_ReceiveDataBlocking
 * Description   : This function receives data from LPUART module using blocking
 * method, the function does not return until the receive is complete.
 *
 *END**************************************************************************/
lpuart_status_t LPUART_DRV_ReceiveDataBlocking(uint32_t instance,
                                               uint8_t * rxBuff,
                                               uint32_t rxSize,
                                               uint32_t timeout)
{
    assert(rxBuff);
    assert(instance < LPUART_INSTANCE_COUNT);

    lpuart_state_t * lpuartState = (lpuart_state_t *)g_lpuartStatePtr[instance];
    LPUART_Type * base = g_lpuartBase[instance];
    lpuart_status_t retVal = kStatus_LPUART_Success;
    osa_status_t syncStatus;

    /* Indicates this is a blocking transaction. */
    lpuartState->isRxBlocking = true;

    retVal = LPUART_DRV_StartReceiveData(instance, rxBuff, rxSize);

    if (retVal == kStatus_LPUART_Success)
    {
        /* Wait until the receive is complete. */
        do
        {
            syncStatus = OSA_SemaWait(&lpuartState->rxIrqSync, timeout);
        } while(syncStatus == kStatus_OSA_Idle);

        if (syncStatus != kStatus_OSA_Success)
        {
            /* Disable receive data full and rx overrun interrupt. */
            LPUART_BWR_CTRL_RIE(base, 0U);
            LPUART_HAL_SetIntMode(base, kLpuartIntRxOverrun, false);

            /* Update the information of the module driver state */
            lpuartState->isRxBusy = false;

            retVal = kStatus_LPUART_Timeout;
        }
    }

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_ReceiveData
 * Description   : This function receives data from LPUART module using
 * non-blocking method.  This function returns immediately after initiating the
 * receive function. The application has to get the receive status to see when
 * the receive is complete. In other words, after calling non-blocking get
 * function, the application must get the receive status to check if receive
 * is completed or not.
 *
 *END**************************************************************************/
lpuart_status_t LPUART_DRV_ReceiveData(uint32_t instance,
                                       uint8_t * rxBuff,
                                       uint32_t rxSize)
{
    assert(rxBuff);
    assert(instance < LPUART_INSTANCE_COUNT);

    lpuart_status_t retVal = kStatus_LPUART_Success;
    lpuart_state_t * lpuartState = (lpuart_state_t *)g_lpuartStatePtr[instance];

    /* Indicates this is a non-blocking transaction. */
    lpuartState->isRxBlocking = false;

    retVal = LPUART_DRV_StartReceiveData(instance, rxBuff, rxSize);

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_GetReceiveStatus
 * Description   : This function returns whether the previous LPUART receive is
 * complete. When performing a non-blocking receive, the user can call this
 * function to ascertain the state of the current receive progress: in progress
 * or complete. In addition, if the receive is still in progress, the user can
 * obtain the number of words that have been currently received.
 *
 *END**************************************************************************/
lpuart_status_t LPUART_DRV_GetReceiveStatus(uint32_t instance,
                                            uint32_t * bytesRemaining)
{
    assert(instance < LPUART_INSTANCE_COUNT);

    lpuart_state_t * lpuartState = (lpuart_state_t *)g_lpuartStatePtr[instance];
    lpuart_status_t retVal = kStatus_LPUART_Success;
    uint32_t rxSize = lpuartState->rxSize;

    /* Fill in the bytes transferred. */
    if (bytesRemaining)
    {
        *bytesRemaining = rxSize;
    }

    if (rxSize)
    {
        retVal = kStatus_LPUART_RxBusy;
    }

    return retVal;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_AbortReceivingData
 * Description   : Terminates a non-blocking receive early.
 *
 *END**************************************************************************/
lpuart_status_t LPUART_DRV_AbortReceivingData(uint32_t instance)
{
    assert(instance < LPUART_INSTANCE_COUNT);

    lpuart_state_t * lpuartState = (lpuart_state_t *)g_lpuartStatePtr[instance];

    /* Check if a transfer is running. */
    if (!lpuartState->isRxBusy)
    {
        return kStatus_LPUART_NoReceiveInProgress;
    }

    /* Stop the running transfer. */
    LPUART_DRV_CompleteReceiveData(instance);

    return kStatus_LPUART_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_IRQHandler
 * Description   : Interrupt handler for LPUART.
 * This handler uses the buffers stored in the lpuart_state_t structs to transfer
 * data. This is not a public API as it is called by IRQ whenever an interrupt
 * occurs.
 *
 *END**************************************************************************/
void LPUART_DRV_IRQHandler(uint32_t instance)
{
    lpuart_state_t * lpuartState = (lpuart_state_t *)g_lpuartStatePtr[instance];
    LPUART_Type * base = g_lpuartBase[instance];

    /* Exit the ISR if no transfer is happening for this instance. */
    if ((!lpuartState->isTxBusy) && (!lpuartState->isRxBusy))
    {
        return;
    }

    /* Handle receive data full interrupt */
    if((LPUART_BRD_CTRL_RIE(base)) && (LPUART_BRD_STAT_RDRF(base)))
    {
#if FSL_FEATURE_LPUART_HAS_FIFO
        /* Read out all data from RX FIFO */
        while(LPUART_HAL_GetRxDatawordCountInFifo(base))
        {
#endif    
            /* Get data and put in receive buffer  */
            LPUART_HAL_Getchar(base, lpuartState->rxBuff);

            /* Invoke callback if there is one */
            if (lpuartState->rxCallback != NULL)
            {
                lpuartState->rxCallback(instance, lpuartState);
            }
            else
            {
                ++lpuartState->rxBuff;
                --lpuartState->rxSize;

                /* Check and see if this was the last byte received */
                if (lpuartState->rxSize == 0)
                {
                    LPUART_DRV_CompleteReceiveData(instance);
                    #if FSL_FEATURE_LPUART_HAS_FIFO
                    break;
                    #endif
                }
            }
#if FSL_FEATURE_LPUART_HAS_FIFO
        }
#endif        
    }

    /* Handle transmitter data register empty interrupt */
    if((LPUART_BRD_CTRL_TIE(base)) && (LPUART_BRD_STAT_TDRE(base)))
    {
        /* Check to see if there are any more bytes to send */
        if (lpuartState->txSize)
        {
            uint8_t emptyEntryCountInFifo;
#if FSL_FEATURE_LPUART_HAS_FIFO
            emptyEntryCountInFifo = lpuartState->txFifoEntryCount -
                                    LPUART_HAL_GetTxDatawordCountInFifo(base);
#else
            emptyEntryCountInFifo = lpuartState->txFifoEntryCount;
#endif
            while(emptyEntryCountInFifo--)
            {
                /* Transmit data and update tx size/buff */
                LPUART_HAL_Putchar(base, *(lpuartState->txBuff));

                /* Invoke callback if there is one */
                if (lpuartState->txCallback != NULL)
                {
                   /* The callback MUST set the txSize to 0 if the
                    * transmit is ended.*/
                   lpuartState->txCallback(instance, lpuartState);
                }
                else
                {
                    ++lpuartState->txBuff;
                    --lpuartState->txSize;
                }

                /* Check and see if this was the last byte */
                if (lpuartState->txSize == 0U)
                {
                    LPUART_DRV_CompleteSendData(instance);
                    break;
                }
            }
        }
    }

    /* Handle receive overrun interrupt */
    if (LPUART_HAL_GetStatusFlag(base, kLpuartRxOverrun))
    {
        /* Clear the flag, OR the rxDataRegFull will not be set any more */
        LPUART_HAL_ClearStatusFlag(base, kLpuartRxOverrun);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_StartSendData
 * Description   : Initiate (start) a transmit by beginning the process of
 * sending data and enabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static lpuart_status_t LPUART_DRV_StartSendData(uint32_t instance,
                                                const uint8_t * txBuff,
                                                uint32_t txSize)
{
    assert(instance < LPUART_INSTANCE_COUNT);

    LPUART_Type * base = g_lpuartBase[instance];
    lpuart_state_t * lpuartState = (lpuart_state_t *)g_lpuartStatePtr[instance];

    /* Check it's not busy transmitting data from a previous function call */
    if (lpuartState->isTxBusy)
    {
        return kStatus_LPUART_TxBusy;
    }

    if (txSize == 0U)
    {
        return kStatus_LPUART_NoDataToDeal;
    }

    /* initialize the module driver state structure */
    lpuartState->txBuff = txBuff;
    lpuartState->txSize = txSize;
    lpuartState->isTxBusy = true;

    /* Enable the transmitter data register empty interrupt. The TDRE flag will
     * set whenever the TX buffer is emptied into the TX shift register (for
     * non-FIFO IPs) or when the data in the TX FIFO is at or below the
     * programmed watermark (for FIFO-supported IPs). */
    LPUART_BWR_CTRL_TIE(base, 1U);

    return kStatus_LPUART_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_CompleteSendData
 * Description   : Finish up a transmit by completing the process of sending
 * data and disabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void LPUART_DRV_CompleteSendData(uint32_t instance)
{
    assert(instance < LPUART_INSTANCE_COUNT);

    LPUART_Type * base = g_lpuartBase[instance];
    lpuart_state_t * lpuartState = (lpuart_state_t *)g_lpuartStatePtr[instance];

    /* Disable transmission complete interrupt */
    LPUART_BWR_CTRL_TIE(base, 0U);

    /* Signal the synchronous completion object. */
    if (lpuartState->isTxBlocking)
    {
        OSA_SemaPost(&lpuartState->txIrqSync);
    }

    /* Update the information of the module driver state */
    lpuartState->isTxBusy = false;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_StartReceiveData
 * Description   : Initiate (start) a receive by beginning the process of
 * receiving data and enabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static lpuart_status_t LPUART_DRV_StartReceiveData(uint32_t instance,
                                                   uint8_t * rxBuff,
                                                   uint32_t rxSize)
{
    assert(instance < LPUART_INSTANCE_COUNT);

    lpuart_state_t * lpuartState = (lpuart_state_t *)g_lpuartStatePtr[instance];
    LPUART_Type * base = g_lpuartBase[instance];

    /* Check it's not busy receiving data from a previous function call */
    if ((lpuartState->isRxBusy) && (!lpuartState->rxCallback))
    {
        return kStatus_LPUART_RxBusy;
    }

    if (rxSize == 0U)
    {
        return kStatus_LPUART_NoDataToDeal;
    }

    /* Initialize the module driver state struct to indicate transfer in progress
     * and with the buffer and byte count data. */
    lpuartState->isRxBusy = true;
    lpuartState->rxBuff = rxBuff;
    lpuartState->rxSize = rxSize;

    /* Enable the receive data overrun interrupt */
    LPUART_HAL_SetIntMode(base, kLpuartIntRxOverrun, true);

    /* Enable receive data full interrupt */
    LPUART_BWR_CTRL_RIE(base, 1U);

    return kStatus_LPUART_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : LPUART_DRV_CompleteReceiveData
 * Description   : Finish up a receive by completing the process of receiving data
 * and disabling the interrupt.
 * This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void LPUART_DRV_CompleteReceiveData(uint32_t instance)
{
    assert(instance < LPUART_INSTANCE_COUNT);

    lpuart_state_t * lpuartState = (lpuart_state_t *)g_lpuartStatePtr[instance];
    LPUART_Type * base = g_lpuartBase[instance];

    /* disable receive data full and rx overrun interrupt. */
    LPUART_BWR_CTRL_RIE(base, 0U);
    LPUART_HAL_SetIntMode(base, kLpuartIntRxOverrun, false);

    /* Signal the synchronous completion object. */
    if (lpuartState->isRxBlocking)
    {
        OSA_SemaPost(&lpuartState->rxIrqSync);
    }

    /* Update the information of the module driver state */
    lpuartState->isRxBusy = false;
}

#endif /* FSL_FEATURE_SOC_LPUART_COUNT */
/*******************************************************************************
 * EOF
 ******************************************************************************/

