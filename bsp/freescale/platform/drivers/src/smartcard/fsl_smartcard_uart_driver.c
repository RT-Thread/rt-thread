/*
* Copyright (c) 2014 - 2015, Freescale Semiconductor, Inc.
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
#include "fsl_smartcard_uart_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"
#if defined(FSL_FEATURE_PIT_TIMER_COUNT)
#include "fsl_hwtimer_pit.h"
#endif

/*******************************************************************************
* Variables
******************************************************************************/
/* Pointer to uart runtime state structure */
extern void * g_uartStatePtr[UART_INSTANCE_COUNT];

/* Table to save uart IRQ enum numbers defined in CMSIS header file */
extern const IRQn_Type g_uartRxTxIrqId[UART_INSTANCE_COUNT];

/* Table to save uart IRQ enum numbers defined in CMSIS header file */
const IRQn_Type g_uartErrIrqId[UART_INSTANCE_COUNT] = UART_ERR_IRQS;

extern smartcard_driver_interface_t smartcardDrvInterface;

hwtimer_t g_tsTimer[HW_SMARTCARD_INSTANCE_COUNT];
uint32_t g_tsCallbackParam[HW_SMARTCARD_INSTANCE_COUNT];
/*******************************************************************************
* Private Functions
******************************************************************************/
static void SMARTCARD_UART_DRV_CompleteSendData(uint32_t instance);
static smartcard_status_t SMARTCARD_UART_DRV_StartSendData(uint32_t instance,
                                                           const uint8_t * txBuff,
                                                           uint32_t txSize);
static void SMARTCARD_UART_DRV_CompleteReceiveData(uint32_t instance);
static smartcard_status_t SMARTCARD_UART_DRV_StartReceiveData(uint32_t instance,
                                                              uint8_t * rxBuff,
                                                              uint32_t rxSize);
static void SMARTCARD_UART_TSExpiryCallback(void *callbackParam);

#if defined(FSL_FEATURE_EDMA_MODULE_CHANNEL)
static void SMARTCARD_UART_DRV_EdmaTxCallback(void *param, edma_chn_status_t status);
static void SMARTCARD_UART_DRV_EdmaRxCallback(void *param, edma_chn_status_t status);
#elif defined(FSL_FEATURE_DMA_DMAMUX_CHANNELS)
static void SMARTCARD_UART_DRV_DmaTxCallback(void *param, dma_channel_status_t status);
static void SMARTCARD_UART_DRV_DmaRxCallback(void *param, dma_channel_status_t status);
#endif
static void SMARTCARD_UART_DRV_SetTransferType(uint32_t instance, smartcard_control_t control);
/*******************************************************************************
* Code
******************************************************************************/
/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_DRV_InstallDriverFunctions
* Description   : This function Installs SMARTCARD Peripheral Driver functions
*
*END**************************************************************************/
void SMARTCARD_DRV_InstallDriverFunctions(smartcard_driver_interface_t *smartcardDrvInterfacePtr)
{
    assert(smartcardDrvInterfacePtr);
    
    smartcardDrvInterface.smartcardDrvInit = SMARTCARD_UART_DRV_Init;
    smartcardDrvInterface.smartcardDrvDeinit = SMARTCARD_UART_DRV_Deinit;
    smartcardDrvInterface.smartcardDrvSendDataBlocking = SMARTCARD_UART_DRV_SendDataBlocking;    
    smartcardDrvInterface.smartcardDrvSendData = SMARTCARD_UART_DRV_SendData;
    smartcardDrvInterface.smartcardDrvGetTransmitStatus = SMARTCARD_UART_DRV_GetTransmitStatus;
    smartcardDrvInterface.smartcardDrvAbortSendingData = SMARTCARD_UART_DRV_AbortSendingData;
    smartcardDrvInterface.smartcardDrvReceiveDataBlocking = SMARTCARD_UART_DRV_ReceiveDataBlocking;
    smartcardDrvInterface.smartcardDrvReceiveData = SMARTCARD_UART_DRV_ReceiveData;
    smartcardDrvInterface.smartcardDrvGetReceiveStatus = SMARTCARD_UART_DRV_GetReceiveStatus;
    smartcardDrvInterface.smartcardDrvAbortReceivingData = SMARTCARD_UART_DRV_AbortReceivingData;
    smartcardDrvInterface.smartcardDrvControl = SMARTCARD_UART_DRV_Control;
}

/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_UART_DRV_Init
* Description   : This function initializes a UART instance for operation.
* This function will initialize the run-time state structure to keep track of
* the on-going transfers, ungate the clock to the UART module, initialize the
* module to user defined settings and default settings, configure the IRQ state
* structure and enable the module-level interrupt to the core, initialize DMA, 
* and enable the UART module transmitter and receiver.
* This function is normally invoked by SMARTCARD composite peripheral driver.
*
*END**************************************************************************/
smartcard_status_t SMARTCARD_UART_DRV_Init(uint32_t instance, smartcard_state_t * smartcardStatePtr,
                                           const smartcard_user_config_t * smartcardUserConfig)
{
    assert(instance < UART_INSTANCE_COUNT);
    assert(smartcardStatePtr && smartcardUserConfig);
    
    UART_Type * base = g_uartBase[instance];
    
    dma_request_source_t uartTxDmaRequest = kDmaRequestMux0Disable;
    dma_request_source_t uartRxDmaRequest = kDmaRequestMux0Disable;
    
    /* Exit if current instance is already initialized. */
    if (g_uartStatePtr[instance])
    {
        return kStatus_SMARTCARD_Initialized;
    }
    
    if (g_smartcardStatePtr[instance])
    {
        return kStatus_SMARTCARD_Initialized;
    }
    
    /* Clear the state structure for this instance. */
    memset(smartcardStatePtr, 0, sizeof(smartcard_state_t));
    
    /* Copy required user configuration to card specific state */    
    smartcardStatePtr->interfaceConfig = smartcardUserConfig->interfaceConfig;
    smartcardStatePtr->cardParams.vcc = smartcardUserConfig->vcc;
    smartcardStatePtr->useDMA = (smartcardUserConfig->xferMode == kSmartcardDMAXferMode)?true:false;
    smartcardStatePtr->extTimerConfig = smartcardUserConfig->extTimerConfig;
    
    /* Save runtime structure pointer.*/
    g_uartStatePtr[instance] = smartcardStatePtr;
    g_smartcardStatePtr[instance] = smartcardStatePtr;
    
    /* Un-gate UART module clock */
    CLOCK_SYS_EnableUartClock(instance);
    
    /* Initialize UART to a known state. */
    UART_HAL_Init(base);
    
    /* Create Semaphore for txIrq and rxIrq. */
    if ((kStatus_OSA_Success != OSA_SemaCreate(&smartcardStatePtr->txIrqSync, 0)) || 
        (kStatus_OSA_Success != OSA_SemaCreate(&smartcardStatePtr->rxIrqSync, 0)))
    {
        return kStatus_SMARTCARD_OtherError;
    }
    
    /* Initialize UART module for smartcard mode of default operation */
    SMARTCARD_UART_DRV_SetTransferType(instance, kSmartcardSetupATRMode);
    
    
#if FSL_FEATURE_UART_HAS_FIFO
    /* Flush FIFO contents */
    UART_HAL_FlushTxFifo(base);
    UART_HAL_FlushRxFifo(base);
#endif
    /* For modules that do not support a FIFO, they have a data buffer that
    * essentially acts likes a one-entry FIFO, thus to make the code cleaner,
    * we'll equate txFifoEntryCount to 1. Also note that TDRE flag will set
    * only when the tx buffer is empty. */
    smartcardStatePtr->txFifoEntryCount = 1;
    
    /* Initialize DMA channels if needed */
    if(smartcardStatePtr->useDMA)
    {
        /* Check if DMA module is initialized */
        if(!CLOCK_SYS_GetDmaGateCmd(0))
        {
            return kStatus_SMARTCARD_DmaNotInitialized;
        }

        switch (instance)
        {
        case 0:
#if defined(UART0_IDX)
            uartRxDmaRequest = kDmaRequestMux0UART0Rx;
            uartTxDmaRequest = kDmaRequestMux0UART0Tx;
#elif defined(UART1_IDX)
            uartRxDmaRequest = kDmaRequestMux0UART1Rx;
            uartTxDmaRequest = kDmaRequestMux0UART1Tx;
#elif defined(UART2_IDX)
            uartRxDmaRequest = kDmaRequestMux0UART2Rx;
            uartTxDmaRequest = kDmaRequestMux0UART2Tx;
#endif
            break;
        case 1:
#if defined(UART1_IDX)
            uartRxDmaRequest = kDmaRequestMux0UART1Rx;
            uartTxDmaRequest = kDmaRequestMux0UART1Tx;
#elif defined(UART2_IDX)
            uartRxDmaRequest = kDmaRequestMux0UART2Rx;
            uartTxDmaRequest = kDmaRequestMux0UART2Tx;
#endif
            break;
        default :
            break;
        }

#if defined(FSL_FEATURE_EDMA_MODULE_CHANNEL)
        /* Request DMA channels for RX FIFO. */
        EDMA_DRV_RequestChannel(kEDMAAnyChannel, uartRxDmaRequest,
                                &smartcardStatePtr->rxDmaState);
        EDMA_DRV_InstallCallback(&smartcardStatePtr->rxDmaState,
                                 SMARTCARD_UART_DRV_EdmaRxCallback, (void *)instance);
        
        /* Request DMA channels for TX FIFO. */
        EDMA_DRV_RequestChannel(kEDMAAnyChannel, uartTxDmaRequest,
                                &smartcardStatePtr->txDmaState);
        EDMA_DRV_InstallCallback(&smartcardStatePtr->txDmaState,
                                 SMARTCARD_UART_DRV_EdmaTxCallback, (void *)instance); 
#elif defined(FSL_FEATURE_DMA_DMAMUX_CHANNELS)    
        /* Request DMA channels for RX FIFO. */
        DMA_DRV_RequestChannel(kDmaAnyChannel, uartRxDmaRequest,
                                &smartcardStatePtr->rxDmaState);
        DMA_DRV_RegisterCallback(&smartcardStatePtr->rxDmaState,
                        SMARTCARD_UART_DRV_DmaRxCallback, (void *)instance);
        
        /* Request DMA channels for TX FIFO. */
        DMA_DRV_RequestChannel(kDmaAnyChannel, uartTxDmaRequest,
                                &smartcardStatePtr->txDmaState);
        DMA_DRV_RegisterCallback(&smartcardStatePtr->txDmaState,
                        SMARTCARD_UART_DRV_DmaTxCallback, (void *)instance);
#endif
    } /* End of if(smartcardStatePtr->useDMA) */
    
#if defined(FSL_FEATURE_PIT_TIMER_COUNT)
    /* Initialize HW timer for the initiail character (TS) delay measurement */
    if(HWTIMER_SYS_Init(&g_tsTimer[instance], &kPitDevif, smartcardStatePtr->extTimerConfig.tsTimerId, NULL) != kHwtimerSuccess)
    {
        return kStatus_SMARTCARD_OtherError;
    }
    
    /* Register callback for TS timer */
    g_tsCallbackParam[instance] = instance;
    HWTIMER_SYS_RegisterCallback(&g_tsTimer[instance], SMARTCARD_UART_TSExpiryCallback, &g_tsCallbackParam[instance]);
#endif
    
    /* Enable UART interrupt on NVIC level. */
    INT_SYS_EnableIRQ(g_uartRxTxIrqId[instance]);
    INT_SYS_EnableIRQ(g_uartErrIrqId[instance]);
    
    /* Finally, enable the UART transmitter and receiver*/
    UART_HAL_DisableTransmitter(base);
    UART_HAL_EnableReceiver(base);
    
    return kStatus_SMARTCARD_Success;
}

/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_UART_DRV_Deinit
* Description   : This function shuts down the UART by disabling interrupts and
*                 the transmitter/receiver.
* This function disables the UART interrupts, disables the transmitter and 
* receiver, and flushes the FIFOs (for modules that support FIFOs).
*
*END**************************************************************************/
void SMARTCARD_UART_DRV_Deinit(uint32_t instance)
{
    assert(instance < UART_INSTANCE_COUNT);

    UART_Type * base = g_uartBase[instance];
    smartcard_state_t * smartcardState = (smartcard_state_t *)g_uartStatePtr[instance];

    /* Check if driver is already de-initialized */
    if (smartcardState == NULL)
    {
        return;
    }
    /* In case there is still data in the TX FIFO or shift register that is
    * being transmitted wait till transmit is complete. */
    
    /* Wait until the data is completely shifted out of shift register */
    while(!(UART_BRD_S1_TC(base))) { }
    
    UART_HAL_SetTxDmaCmd(base, false);
    UART_HAL_SetRxDmaCmd(base, false);
    /* Check if DMA was used and release used channels */
    if((smartcardState->useDMA) && (CLOCK_SYS_GetDmaGateCmd(0)))
    {
#if defined(FSL_FEATURE_EDMA_MODULE_CHANNEL)
        /* Release DMA channel. */
        EDMA_DRV_ReleaseChannel(&smartcardState->rxDmaState);
        EDMA_DRV_ReleaseChannel(&smartcardState->txDmaState);
#elif defined(FSL_FEATURE_DMA_DMAMUX_CHANNELS)
        /* Release DMA channel. */
        DMA_DRV_FreeChannel(&smartcardState->rxDmaState);
        DMA_DRV_FreeChannel(&smartcardState->txDmaState);
#endif
    }
    /* Disable the interrupt */
    INT_SYS_DisableIRQ(g_uartRxTxIrqId[instance]);
    INT_SYS_DisableIRQ(g_uartErrIrqId[instance]);
    
    /* Disable TX and RX */
    UART_HAL_DisableTransmitter(base);
    UART_HAL_DisableReceiver(base);
    
    /* Destroy TX and RX sema. */
    OSA_SemaDestroy(&smartcardState->txIrqSync);
    OSA_SemaDestroy(&smartcardState->rxIrqSync);
    
#if FSL_FEATURE_UART_HAS_FIFO
    /* Flush FIFO contents */
    UART_HAL_FlushTxFifo(base);
    UART_HAL_FlushRxFifo(base);
#endif
    /* Clear state pointer. */
    g_uartStatePtr[instance] = NULL;
    g_smartcardStatePtr[instance] = NULL;
    
    /* Gate UART module clock */
    CLOCK_SYS_DisableUartClock(instance);
}

/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_DRV_SendDataBlocking
* Description   : This function sends (transmits) data out through the UART 
* module using a blocking method.
* A blocking (also known as synchronous) function means that the function does
* not return until the transmit is complete. This blocking function is used to
* send data through the UART port.
*
*END**************************************************************************/
smartcard_status_t SMARTCARD_UART_DRV_SendDataBlocking(uint32_t instance,
                                                       const uint8_t * txBuff,
                                                       uint32_t txSize,
                                                       uint32_t timeout)
{
    assert(instance < UART_INSTANCE_COUNT);
    assert(txBuff);
    
    UART_Type * base = g_uartBase[instance];
    smartcard_state_t * smartcardState = (smartcard_state_t *)g_uartStatePtr[instance];
    smartcard_status_t error = kStatus_SMARTCARD_Success;
    osa_status_t syncStatus;
    
    /* Indicates current transaction is blocking.*/
    smartcardState->isTxBlocking = true;
    
    /* Start the transmission process */
    if (SMARTCARD_UART_DRV_StartSendData(instance, txBuff, txSize) == kStatus_SMARTCARD_TxBusy)
    {
        return kStatus_SMARTCARD_TxBusy;
    }
    
    /* Wait until the transmit is complete. */
    do
    {
        syncStatus = OSA_SemaWait(&smartcardState->txIrqSync, timeout);
    }while(syncStatus == kStatus_OSA_Idle);
    
    if (syncStatus != kStatus_OSA_Success)
    {
        /* Abort the transfer so it doesn't continue unexpectedly.*/
        SMARTCARD_UART_DRV_AbortSendingData(instance);
        error = kStatus_SMARTCARD_Timeout;
    }
    
    if(smartcardState->tType == kSmartcardT1Transport)
    {
        /* For T=1 protocol data transmit, clear state */
        smartcardState->timersState.cwtExpired = false;
        smartcardState->timersState.bwtExpired = false;
        
        /* Disable CWT interrupt */
        UART_HAL_SetISO7816IntMode(base, kUartIntIso7816CharWaitTimer, false);
    }
    
    if(smartcardState->txtCrossed)
    {
        smartcardState->txtCrossed = false;
    }
	  
    /* Switch to receive mode after transmission is complete */
    UART_HAL_SetTransmitterDir(base, kUartSinglewireTxdirIn);    
    
    /* disable after transmit */
    UART_HAL_DisableTransmitter(base);
    
    return error;
}

/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_UART_DRV_SendData
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
smartcard_status_t SMARTCARD_UART_DRV_SendData(uint32_t instance,
                                               const uint8_t * txBuff,
                                               uint32_t txSize)
{
    assert(instance < UART_INSTANCE_COUNT);
    assert(txBuff);
    
    smartcard_state_t * smartcardState = (smartcard_state_t *)g_uartStatePtr[instance];
    
    /* Indicates current transaction is non-blocking */
    smartcardState->isTxBlocking = false;
    
    /* Start the transmission process */
    if (SMARTCARD_UART_DRV_StartSendData(instance, txBuff, txSize) == kStatus_SMARTCARD_TxBusy)
    {
        return kStatus_SMARTCARD_TxBusy;
    }
    
    return kStatus_SMARTCARD_Success;
}

/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_UART_DRV_GetTransmitStatus
* Description   : This function returns whether the previous UART transmit has
* finished.
* When performing an async transmit, the user can call this function to
* ascertain the state of the current transmission: in progress (or busy) or
* complete (success). In addition, if the transmission is still in progress,
* the user can obtain the number of words that have been currently transferred.
*
*END**************************************************************************/
smartcard_status_t SMARTCARD_UART_DRV_GetTransmitStatus(uint32_t instance, uint32_t * bytesRemaining)
{
    assert(instance < UART_INSTANCE_COUNT);
    
    smartcard_state_t * smartcardState = (smartcard_state_t *)g_uartStatePtr[instance];
    
    /* Fill in the bytes transferred. This may return that all bytes were
    * transmitted, however, for IPs with FIFO support, there still may be data
    * in the TX FIFO still in the process of being transmitted. */
    if (bytesRemaining)
    {
        *bytesRemaining = smartcardState->txSize;
    }
    
    /* Return kStatus_UART_TxBusy or kStatus_UART_Success depending on whether
    * or not the UART has a FIFO. If it does have a FIFO, we'll need to wait
    * until the FIFO is completely drained before indicating success in
    * addition to isTxBusy = 0. If there is no FIFO, then we need to only worry
    * about isTxBusy. */
    return (smartcardState->isTxBusy ? kStatus_SMARTCARD_TxBusy : kStatus_SMARTCARD_Success);
}

/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_UART_DRV_AbortSendingData
* Description   : This function ends a non-blocking UART transmission early.
* During a non-blocking UART transmission, the user has the option to terminate
* the transmission early if the transmission is still in progress.
*
*END**************************************************************************/
smartcard_status_t SMARTCARD_UART_DRV_AbortSendingData(uint32_t instance)
{
    assert(instance < UART_INSTANCE_COUNT);
    
    smartcard_state_t * smartcardState = (smartcard_state_t *)g_uartStatePtr[instance];
    
    /* Check if a transfer is running. */
    if (!smartcardState->isTxBusy)
    {
        return kStatus_SMARTCARD_NoTransmitInProgress;
    }
    
    /* Stop the running transfer. */
    SMARTCARD_UART_DRV_CompleteSendData(instance);
    
    return kStatus_SMARTCARD_Success;
}

/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_UART_DRV_ReceiveDataBlocking
* Description   : This function gets (receives) data from the UART module using
* a blocking method. A blocking (also known as synchronous) function means that
* the function does not return until the receive is complete. This blocking
* function is used to send data through the UART port.
*
*END**************************************************************************/
smartcard_status_t SMARTCARD_UART_DRV_ReceiveDataBlocking(uint32_t instance, uint8_t * rxBuff,
                                                          uint32_t rxSize, uint32_t * rcvdSize, uint32_t timeout)
{
    assert(instance < UART_INSTANCE_COUNT);
    assert(rxBuff);
    assert(rcvdSize);
    
    UART_Type * base = g_uartBase[instance];
    smartcard_state_t * smartcardState = (smartcard_state_t *)g_uartStatePtr[instance];
    smartcard_status_t error = kStatus_SMARTCARD_Success;
    osa_status_t syncStatus;
    
    smartcardState->transState = kSmartcardReceivingState; 
    
    /* Indicates current transaction is blocking.*/
    smartcardState->isRxBlocking = true;
    
    /* Initialize error check flags */
    smartcardState->rxtCrossed = false;
    smartcardState->parityError = false;
    
    if (SMARTCARD_UART_DRV_StartReceiveData(instance, rxBuff, rxSize) == kStatus_SMARTCARD_RxBusy)
    {
        return kStatus_SMARTCARD_RxBusy;
    }
    
    /* Wait until all the data is received or for timeout.*/
    do
    {
        syncStatus = OSA_SemaWait(&smartcardState->rxIrqSync, timeout);
    }while(syncStatus == kStatus_OSA_Idle);
    
    if (syncStatus != kStatus_OSA_Success)
    {
        /* Abort the transfer so it doesn't continue unexpectedly.*/
        SMARTCARD_UART_DRV_AbortReceivingData(instance);
        error = kStatus_SMARTCARD_Timeout;
    }
    
    /* Check for timeouts */
    if(smartcardState->tType == kSmartcardT0Transport)
    {
        if(smartcardState->timersState.wwtExpired)
        {
            error = kStatus_SMARTCARD_Timeout;
        }
    }
    else
    {
        if((smartcardState->timersState.bwtExpired) || (smartcardState->timersState.cwtExpired))
        {
            error = kStatus_SMARTCARD_Timeout;
        }
    }
    
    /* Disable transmitter */
    UART_HAL_DisableTransmitter(base);
    
    /* Update received data size */
    *rcvdSize = rxSize - smartcardState->rxSize;
    
    return error;
}

/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_UART_DRV_ReceiveData
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
smartcard_status_t SMARTCARD_UART_DRV_ReceiveData(uint32_t instance,
                                                  uint8_t * rxBuff,
                                                  uint32_t rxSize)
{
    assert(instance < UART_INSTANCE_COUNT);
    assert(rxBuff);
    
    smartcard_state_t * smartcardState = (smartcard_state_t *)g_uartStatePtr[instance];
    
    /* Indicates current transaction is non-blocking.*/
    smartcardState->isRxBlocking = false;
    
    /* Initialize the error flags */
    smartcardState->rxtCrossed = false;
    smartcardState->parityError = false;
    
    if (SMARTCARD_UART_DRV_StartReceiveData(instance, rxBuff, rxSize) == kStatus_SMARTCARD_RxBusy)
    {
        return kStatus_SMARTCARD_RxBusy;
    }
    
    return kStatus_SMARTCARD_Success;
}

/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_UART_DRV_GetReceiveStatus
* Description   : This function returns whether the previous UART receive is
*                 completed.
* When performing a non-blocking receive, the user can call this function to
* ascertain the state of the current receive progress: in progress (or busy)
* or complete (success). In addition, if the receive is still in progress, the
* user can obtain the number of words that have been currently received.
*
*END**************************************************************************/
smartcard_status_t SMARTCARD_UART_DRV_GetReceiveStatus(uint32_t instance,
                                                       uint32_t * bytesRemaining)
{
    assert(instance < UART_INSTANCE_COUNT);
    
    smartcard_state_t * smartcardState = (smartcard_state_t *)g_uartStatePtr[instance];
#if defined(FSL_FEATURE_EDMA_MODULE_CHANNEL)
    DMA_Type * edmaBaseAddr = VIRTUAL_CHN_TO_EDMA_MODULE_REGBASE(smartcardState->txDmaState.channel);
    uint32_t edmaChannel = VIRTUAL_CHN_TO_EDMA_CHN(smartcardState->txDmaState.channel);
    uint32_t rxSize = 0;
#endif
    smartcard_status_t retVal = kStatus_SMARTCARD_Success;
    
    /* Fill in the remaining bytes. */
    if (bytesRemaining)
    {
        if(!smartcardState->useDMA)
        {
            *bytesRemaining = smartcardState->rxSize;
        }
        else
        {
#if defined(FSL_FEATURE_DMA_DMAMUX_CHANNELS)
            *bytesRemaining = DMA_DRV_GetUnfinishedBytes(&smartcardState->rxDmaState);
#endif
        }
    }
    
    retVal = smartcardState->isRxBusy ? kStatus_SMARTCARD_RxBusy : kStatus_SMARTCARD_Success;
    
#if defined(FSL_FEATURE_EDMA_MODULE_CHANNEL)
    if(smartcardState->useDMA)
    {
        /* EDMA will reload the major count after finish transfer, need to set
        * the count to 0 manually. */
        if (smartcardState->isRxBusy)
        {
            rxSize = EDMA_HAL_HTCDGetUnfinishedBytes(edmaBaseAddr, edmaChannel);
            retVal = kStatus_SMARTCARD_RxBusy;
        }
        
        /* Fill in the bytes transferred. */
        if (bytesRemaining)
        {
            *bytesRemaining = rxSize;
        }
    }    
#endif

    return retVal;
}

/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_UART_DRV_AbortReceivingData
* Description   : This function shuts down the UART by disabling interrupts and
*                 the transmitter/receiver.
* This function disables the UART interrupts, disables the transmitter and
* receiver, and flushes the FIFOs (for modules that support FIFOs).
*
*END**************************************************************************/
smartcard_status_t SMARTCARD_UART_DRV_AbortReceivingData(uint32_t instance)
{
    assert(instance < UART_INSTANCE_COUNT);
    smartcard_state_t * smartcardState = (smartcard_state_t *)g_uartStatePtr[instance];
    
    /* Check if a transfer is running. */
    if (!smartcardState->isRxBusy)
    {
        return kStatus_SMARTCARD_NoReceiveInProgress;
    }
    
    /* Stop the running transfer. */
    SMARTCARD_UART_DRV_CompleteReceiveData(instance);
    
    return kStatus_SMARTCARD_Success;
}

#if defined(FSL_FEATURE_EDMA_MODULE_CHANNEL)
/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_UART_DRV_EdmaRxCallback
* Description   : Callback function to be called from the EDMA ISR after receive.
* This is not a public interface.
*
*END**************************************************************************/
static void SMARTCARD_UART_DRV_EdmaRxCallback(void *param, edma_chn_status_t status)
{
    SMARTCARD_UART_DRV_CompleteReceiveData((uint32_t)param);
}
#elif defined(FSL_FEATURE_DMA_DMAMUX_CHANNELS)
/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_UART_DRV_DmaRxCallback
* Description   : Callback function to be called from the DMA ISR after receive.
* This is not a public interface.
*
*END**************************************************************************/
static void SMARTCARD_UART_DRV_DmaRxCallback(void *param, dma_channel_status_t status)
{
    SMARTCARD_UART_DRV_CompleteReceiveData((uint32_t)param);
}
#endif

/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_UART_DRV_ErrIRQHandler
* Description   : Error Interrupt handler for UART.
* This handler uses the buffers stored in the smartcard_state_t structs to handle 
* types of erros/events. This is not a public API as it is called whenever an 
* interrupt occurs.
*
*END**************************************************************************/
void SMARTCARD_UART_DRV_ErrIRQHandler(uint32_t instance)
{
    assert(instance < UART_INSTANCE_COUNT);
    
    uint8_t temp8;
    smartcard_state_t * smartcardState = (smartcard_state_t *)g_uartStatePtr[instance];
    UART_Type * base = g_uartBase[instance];
    
    /* Check if a parity error occurred */
    if (UART_HAL_GetStatusFlag(base, kUartParityErr))
    {
   
        if(smartcardState->transState == kSmartcardWaitingForTSState)
        {
            /* A parity error detected during initial character (TS) detection phase */
            smartcardState->transState = kSmartcardInvalidTSDetecetedState;
            
            /* Un-block any caller waiting for initial character detection */
            if(smartcardState->isRxBusy)
            {
                SMARTCARD_UART_DRV_CompleteReceiveData(instance);
            }
        }
        else
        {
            /* Parity error detected after iniital character detection phase */
            smartcardState->parityError = true;
        }
    }
    
    /* Check if Transmission threshold value was exceeded */
    if(UART_HAL_GetISO7816InterruptStatus(base, kUartIntIso7816TxThresholdExceeded))
    {
        /* Disable transmitter */
        UART_HAL_DisableTransmitter(base);
        
        /* Clear Transmission threshold interrupt flag */
        UART_HAL_ClearISO7816InterruptStatus(base, kUartIntIso7816TxThresholdExceeded);
        
        /* Enable transmitter */
        UART_HAL_EnableTransmitter(base);
        
        smartcardState->txtCrossed = true;
    }
    
    /* Check if Receive threshold value was exceeded */
    if(UART_HAL_GetISO7816InterruptStatus(base, kUartIntIso7816RxThreasholdExceeded))
    {
        /* Clear Receive threshold interrupt flag */
        UART_HAL_ClearISO7816InterruptStatus(base, kUartIntIso7816RxThreasholdExceeded);
        
      
        /* Check if Receive threshold was exceeded during initial character detection */
        if(smartcardState->transState == kSmartcardWaitingForTSState)
        {
            smartcardState->transState = kSmartcardInvalidTSDetecetedState;
            if(smartcardState->isRxBusy)
            {
                SMARTCARD_UART_DRV_CompleteReceiveData(instance);
            }
        }
        else
        {
            /* Receive threshold exceeded during normal transfer, set flags */
            smartcardState->rxtCrossed = true;
            
            /* Signal the synchronous completion object. */
            if (smartcardState->isRxBlocking)
            {
                OSA_SemaPost(&smartcardState->rxIrqSync);
                smartcardState->isRxBlocking = false;
            }
        }
    }
    
    /* Check if a Guard Timer rule was violated */
    if(UART_HAL_GetISO7816InterruptStatus(base, kUartIntIso7816GuardTimerViolated))
    {
        /* Clear respective interrupt status flag */
        UART_HAL_ClearISO7816InterruptStatus(base, kUartIntIso7816GuardTimerViolated);
    }
    
    /* Check if a Work Wait Timer expired */
    if(UART_HAL_GetISO7816InterruptStatus(base, kUartIntIso7816WaitTimer))
    {  
        /* Clear Work Wait Timer interrupt flag */
        UART_HAL_ClearISO7816InterruptStatus(base, kUartIntIso7816WaitTimer);
        
        /* Disable Work Wait Timer interrupt */
        UART_HAL_SetISO7816IntMode(base, kUartIntIso7816WaitTimer, false);
        
        /* Reset WT timer */
        UART_HAL_ResetISO7816WaitTimer(base);
        
        /* Indicate WWT expired */
        smartcardState->timersState.wwtExpired = true;
        
        if(smartcardState->isTxBusy)
        {
            /* Terminate and un-block any caller */
            SMARTCARD_UART_DRV_CompleteSendData(instance);
        }
        
        if(smartcardState->isRxBusy)
        {
            /* Terminate and un-block any caller */
            SMARTCARD_UART_DRV_CompleteReceiveData(instance);
        }
    }
    
    /* Check if a Character Wait Timer expired */
    if(UART_HAL_GetISO7816InterruptStatus(base, kUartIntIso7816CharWaitTimer))
    {
        /* Disable Character Wait Timer interrupt */
        UART_HAL_SetISO7816IntMode(base, kUartIntIso7816CharWaitTimer, false);
        
        /* Reset CWT timer otherwise this interrupt keeps coming*/
        UART_HAL_ResetISO7816CharacterWaitTimer(base);     
        
        smartcardState->transState = kSmartcardIdleState;
        
        /* Indicate CWT expired */
        smartcardState->timersState.cwtExpired = true;
        
        if(smartcardState->isTxBusy)
        {
            /* Terminate and un-block any caller */
            SMARTCARD_UART_DRV_CompleteSendData(instance);
        }
        
        if(smartcardState->isRxBusy)
        {
            /* Terminate and un-block any caller */
            SMARTCARD_UART_DRV_CompleteReceiveData(instance);
        }
    }
    
    /* Check if a Bloick Wait Timer expired */
    if(UART_HAL_GetISO7816InterruptStatus(base, kUartIntIso7816BlockWaitTimer))
    {
        /* Disable Block Wait Timer interrupt */
        UART_HAL_SetISO7816IntMode(base, kUartIntIso7816BlockWaitTimer, false);
        
        /* Reset BWT timer */
        UART_HAL_ResetISO7816BlockWaitTimer(base);
        
        /* Indicate BWT expired */
        smartcardState->timersState.bwtExpired = true;
        
        /* Check if Wait Time Extension was requested */
        if(smartcardState->wtxRequested)
        {
            temp8 = 0;
            SMARTCARD_UART_DRV_Control(instance, kSmartcardResetWaitTimeMultiplier, &temp8);
        }
        
        if(smartcardState->isTxBusy)
        {
            /* Terminate and un-block any caller */
            SMARTCARD_UART_DRV_CompleteSendData(instance);
        }
        
        if(smartcardState->isRxBusy)
        {
            /* Terminate and un-block any caller */
            SMARTCARD_UART_DRV_CompleteReceiveData(instance);
        }
    }
    
#if FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT
    /* Check if a ATR duration timer Wait Timer expired */
    if((UART_HAL_GetISO7816IntMode(base, kUartIntIso7816AtrDurationTimer)) && 
        (UART_HAL_GetISO7816InterruptStatus(base, kUartIntIso7816AtrDurationTimer)))
    {
        /* Clear ATR Duration Timer interrupt flag */
        UART_HAL_ClearISO7816InterruptStatus(base, kUartIntIso7816AtrDurationTimer);
        
        /* Indicate ADT expired */
        smartcardState->timersState.adtExpired = true;
    }
#endif
    
    /* Clear pending interrupts */
    UART_HAL_ClearStatusFlag(base, kUartIdleLineDetect);
}

/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_UART_DRV_IRQHandler
* Description   : Interrupt handler for UART.
* This handler uses the buffers stored in the smartcard_state_t structs to transfer
* data. This is not a public API as it is called whenever an interrupt occurs.
*
*END**************************************************************************/
void SMARTCARD_UART_DRV_IRQHandler(uint32_t instance)
{
    assert(instance < UART_INSTANCE_COUNT);
    
    smartcard_state_t * smartcardState = (smartcard_state_t *)g_uartStatePtr[instance];
    UART_Type * base = g_uartBase[instance];
    
    /* Check if Initial Character (TS) was detected */
    if(UART_HAL_GetISO7816InterruptStatus(base, kUartIntIso7816InitialCharDetected))
    {
#if defined(FSL_FEATURE_PIT_TIMER_COUNT)
        /* Stop TS timer */
        HWTIMER_SYS_Stop(&g_tsTimer[instance]);
#endif
        /* Get Data Convention format from RXINV bit in UART_S2 register */
        smartcardState->cardParams.convention = (smartcard_card_convention_t)UART_BRD_S2_RXINV(base);
    
        /* Clear interrupt flag for initial character detected */
        UART_HAL_ClearISO7816InterruptStatus(base, kUartIntIso7816InitialCharDetected);
        
        /* Disable initial character detection */
        UART_HAL_SetISO7816IntMode(base, kUartIntIso7816InitialCharDetected, false);
        
        /* Set transfer mode to receiving(ATR bytes) mode */
        smartcardState->transState = kSmartcardReceivingState;
        
        if(smartcardState->isRxBlocking)
        {
            /* Complete receive process */
            SMARTCARD_UART_DRV_CompleteReceiveData(instance);
        }
    }
    
    /* Exit the ISR if no transfer is happening for this instance. */
    if ((!smartcardState->isTxBusy) && (!smartcardState->isRxBusy))
    {
        return;
    }
    
    /* Handle receive data register full interrupt, if rx data register full
     * interrupt is enabled AND there is data available. */
    if((UART_BRD_C2_RIE(base)) && (UART_BRD_S1_RDRF(base)))
    {
        /* Get data and put into receive buffer */
        UART_HAL_Getchar(base, smartcardState->rxBuff);
        
        ++smartcardState->rxBuff;
        --smartcardState->rxSize;

        if((smartcardState->tType == kSmartcardT1Transport)
           && (smartcardState->rxSize > 0)
           && (UART_HAL_GetISO7816IntMode(base, kUartIntIso7816BlockWaitTimer)))
        {
            /* Only the 1st byte has been received, now time to disable BWT interrupt */
            UART_HAL_SetISO7816IntMode(base, kUartIntIso7816BlockWaitTimer, false);
            /* And, enable CWT interrupt */
            smartcardState->timersState.cwtExpired = false;
            UART_HAL_SetISO7816IntMode(base, kUartIntIso7816CharWaitTimer, true);
        }

        /* Check and see if this was the last byte received */
        if (smartcardState->rxSize == 0)
        {
            SMARTCARD_UART_DRV_CompleteReceiveData(instance);
        }
    }
    
    /* Handle transmit data register empty interrupt and 
    * last data was shifted out of IO line */
    if((UART_BRD_S1_TDRE(base)) && (UART_HAL_GetStatusFlag(base, kUartTxComplete)))
    {
        if(smartcardState->txtCrossed)
        {
            /* Un-block the caller */
            SMARTCARD_UART_DRV_CompleteSendData(instance);
        }
        else
        /* Check to see if there are any more bytes to send */
        if (smartcardState->txSize)
        {
            uint8_t emptyEntryCountInFifo;
            emptyEntryCountInFifo = smartcardState->txFifoEntryCount;
            
            while(emptyEntryCountInFifo--)
            {
                /* Transmit data and update tx size/buff */
                UART_HAL_Putchar(base, *(smartcardState->txBuff));
                ++smartcardState->txBuff; 
                --smartcardState->txSize;
                
                if (!smartcardState->txSize)
                {
                    SMARTCARD_UART_DRV_CompleteSendData(instance);
                    break;
                }
            }
        }
    }
    
#if defined (KL43Z4_SERIES)
#if (UART_INSTANCE_COUNT > 0)
    SMARTCARD_UART_DRV_ErrIRQHandler(instance);
#endif
#endif
}

/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_UART_DRV_CompleteSendData
* Description   : Finish up a transmit by completing the process of sending 
* data and disabling the interrupt. 
* This is not a public API as it is called from other driver functions.
*
*END**************************************************************************/
static void SMARTCARD_UART_DRV_CompleteSendData(uint32_t instance)
{
    assert(instance < UART_INSTANCE_COUNT);
    
    UART_Type * base = g_uartBase[instance];
    smartcard_state_t * smartcardState = (smartcard_state_t *)g_uartStatePtr[instance];
#if defined(FSL_FEATURE_EDMA_MODULE_CHANNEL)
    DMA_Type * edmaBaseAddr = VIRTUAL_CHN_TO_EDMA_MODULE_REGBASE(smartcardState->txDmaState.channel);
    uint32_t edmaChannel = VIRTUAL_CHN_TO_EDMA_CHN(smartcardState->txDmaState.channel);
#endif
    
    if(!smartcardState->useDMA)
    {
        /* Disable the transmission complete interrupt */
        UART_HAL_SetIntMode(base, kUartIntTxComplete, false);
    }
    else
    {
#if defined(FSL_FEATURE_EDMA_MODULE_CHANNEL)
        /* Disable DMA major loop interrupt */
        EDMA_HAL_HTCDSetIntCmd(edmaBaseAddr, edmaChannel, false);
        
        /* Stop DMA channel. */
        EDMA_HAL_SetDmaRequestCmd(edmaBaseAddr, (edma_channel_indicator_t)edmaChannel, false);
#elif defined(FSL_FEATURE_DMA_DMAMUX_CHANNELS)
        /* Stop DMA channel. */
        DMA_DRV_StopChannel(&smartcardState->txDmaState);
#endif
        
        /* Wait for TC bit to set - last byte transmission has finished */
        while (!UART_HAL_GetStatusFlag(base, kUartTxComplete)){}
    
        /* Disable DMA trigger when transmit data register empty, 
        * and receive data register full. */
        UART_HAL_SetTxDmaCmd(base, false);
    }
    
    /* Wait for TC bit to clear - last byte to be completely shifted out off IO line */
    while(!UART_HAL_GetStatusFlag(base, kUartTxComplete)){}
    
    /* Switch to receive mode after transmission is complete */
    UART_HAL_SetTransmitterDir(base, kUartSinglewireTxdirIn);    
    
    /* disable after transmit */
    UART_HAL_DisableTransmitter(base);
    
    /* Enable Receiver */
    UART_HAL_EnableReceiver(base);
    
    /* Signal the synchronous completion object. */
    if (smartcardState->isTxBlocking)
    {
        OSA_SemaPost(&smartcardState->txIrqSync);
        smartcardState->isTxBlocking = false;
    }
    
    /* Update the information of the module driver state */
    smartcardState->isTxBusy = false;
    
    /* Clear txSize to avoid any spurious transmit from ISR */
    smartcardState->txSize = 0;
}

/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_UART_DRV_StartSendData
* Description   : Initiate (start) a transmit by beginning the process of
* sending data and enabling the interrupt.
* This is not a public API as it is called from other driver functions.
*
*END**************************************************************************/
static smartcard_status_t SMARTCARD_UART_DRV_StartSendData(uint32_t instance,
                                                           const uint8_t * txBuff,
                                                           uint32_t txSize)
{
    assert(instance < UART_INSTANCE_COUNT);
    assert(txBuff);
    
    UART_Type * base = g_uartBase[instance];
    smartcard_state_t * smartcardState = (smartcard_state_t *)g_uartStatePtr[instance];
#if defined(FSL_FEATURE_EDMA_MODULE_CHANNEL)
    DMA_Type * edmaBaseAddr = VIRTUAL_CHN_TO_EDMA_MODULE_REGBASE(smartcardState->txDmaState.channel);
    uint32_t edmaChannel = VIRTUAL_CHN_TO_EDMA_CHN(smartcardState->txDmaState.channel);
#elif defined(FSL_FEATURE_DMA_DMAMUX_CHANNELS)
    dma_channel_t *chn = &smartcardState->txDmaState;
    DMA_Type * dmaBase = g_dmaBase[chn->channel/FSL_FEATURE_DMA_DMAMUX_CHANNELS];
    dma_channel_link_config_t config =
    {
        kDmaChannelLinkDisable, /* linkType */
        0,                      /* channel1 */
        0                       /* channel2 */
    };
#endif
    
    /* Check that we're not busy already transmitting data from a previous
    * function call. */
    if (smartcardState->isTxBusy)
    {
        return kStatus_SMARTCARD_TxBusy;
    }
    
    smartcardState->transState = kSmartcardTransmittingState;
    
    /* Disable transmitter and receiver */
    UART_HAL_DisableTransmitter(base);
    UART_HAL_DisableReceiver(base);
    
    /* Check if current transport protocol is T=1 */
    if(smartcardState->tType == kSmartcardT1Transport)
    {
        /* Reset CWT timer at the beginning of transmission only */
        smartcardState->timersState.cwtExpired = false;
        UART_HAL_ResetISO7816CharacterWaitTimer(base);
        
        /* Enable CWT timer interrupt */
        UART_HAL_SetISO7816IntMode(base, kUartIntIso7816CharWaitTimer, true);
        
        /* Disable WWT timer as not in T=0 mode */
        UART_HAL_SetISO7816IntMode(base, kUartIntIso7816WaitTimer, false);
        
        /* The TLEN does not count the NAD, PCB, LEN, LRC */
        UART_HAL_SetTLen(base, (txSize - 4));
    }
    
    smartcardState->isTxBusy = true;
    
    /* Set the TX pin as output and enable transmitter */
    UART_HAL_SetTransmitterDir(base, kUartSinglewireTxdirOut);
    UART_HAL_EnableTransmitter(base);
        
    if(!smartcardState->useDMA)
    {       
        /* Initialize the module driver state structure. */
        smartcardState->txBuff = txBuff;
        smartcardState->txSize = txSize;        
        
        /* Enable the transmission complete interrupt. The TC bit will
        * set whenever the transmit data is shifted out */
        UART_HAL_SetIntMode(base, kUartIntTxComplete, true);
    }
    else
    {
        /* Initialize the module driver state structure. */
        smartcardState->txBuff = txBuff;
        smartcardState->txSize = txSize;
        
        /* Enable DMA trigger when transmit data register empty, 
        * and receive data register full. */
        UART_HAL_SetTxDmaCmd(base, true);
    
#if defined(FSL_FEATURE_EDMA_MODULE_CHANNEL)
        /* Setup source */
        EDMA_HAL_HTCDSetSrcAddr(edmaBaseAddr, edmaChannel, (uint32_t)txBuff);
        EDMA_HAL_HTCDSetSrcOffset(edmaBaseAddr, edmaChannel, 1);
        EDMA_HAL_HTCDSetSrcLastAdjust(edmaBaseAddr, edmaChannel, 0);
        
        /* Setup destination */
        EDMA_HAL_HTCDSetDestAddr(edmaBaseAddr, edmaChannel, UART_HAL_GetDataRegAddr(base));
        EDMA_HAL_HTCDSetDestOffset(edmaBaseAddr, edmaChannel, 0);
        EDMA_HAL_HTCDSetDestLastAdjust(edmaBaseAddr, edmaChannel, 0);
                
        /* Setup transfer properties */
        EDMA_HAL_HTCDSetNbytes(edmaBaseAddr, edmaChannel, 1);
        EDMA_HAL_HTCDSetChannelMinorLink(edmaBaseAddr, edmaChannel, 0, false);
        EDMA_HAL_HTCDSetMajorCount(edmaBaseAddr, edmaChannel, txSize);
        EDMA_HAL_HTCDSetAttribute(edmaBaseAddr, edmaChannel, kEDMAModuloDisable,
                                  kEDMAModuloDisable, kEDMATransferSize_1Bytes, kEDMATransferSize_1Bytes);
        EDMA_HAL_HTCDSetScatterGatherCmd(edmaBaseAddr, edmaChannel, false);
        EDMA_HAL_HTCDSetDisableDmaRequestAfterTCDDoneCmd(edmaBaseAddr, edmaChannel, true);
        
        /* Enable DMA major loop interrupt */
        EDMA_HAL_HTCDSetIntCmd(edmaBaseAddr, edmaChannel, true);
        
        /* Start DMA channel */
        EDMA_HAL_SetDmaRequestCmd(edmaBaseAddr, (edma_channel_indicator_t)edmaChannel, true);
#elif defined(FSL_FEATURE_DMA_DMAMUX_CHANNELS)
        /* Setup transfer properties */
        DMA_HAL_SetAutoAlignCmd(dmaBase, chn->channel, false);
        DMA_HAL_SetCycleStealCmd(dmaBase, chn->channel, true);
        DMA_HAL_SetAsyncDmaRequestCmd(dmaBase, chn->channel, false);
        DMA_HAL_SetDisableRequestAfterDoneCmd(dmaBase, chn->channel, true);
        DMA_HAL_SetChanLink(dmaBase, chn->channel, &config);
        
        DMA_HAL_SetSourceModulo(dmaBase, chn->channel, kDmaModuloDisable);
        DMA_HAL_SetSourceTransferSize(dmaBase, chn->channel, kDmaTransfersize8bits);
        DMA_HAL_SetSourceIncrementCmd(dmaBase, chn->channel, true);
        
        /* Setup destination */
        DMA_HAL_SetDestAddr(dmaBase, chn->channel, UART_HAL_GetDataRegAddr(base));
        DMA_HAL_SetDestModulo(dmaBase, chn->channel, kDmaModuloDisable);
        DMA_HAL_SetDestTransferSize(dmaBase, chn->channel, kDmaTransfersize8bits);
        DMA_HAL_SetDestIncrementCmd(dmaBase, chn->channel, false);
        
        DMA_HAL_SetIntCmd(dmaBase, chn->channel, true);
        
        /* Setup source */
        DMA_HAL_SetSourceAddr(dmaBase, chn->channel, (uint32_t)txBuff);
        DMA_HAL_SetTransferCount(dmaBase, chn->channel, txSize);
        
        /* Start DMA channel */
        DMA_DRV_StartChannel(chn);
#endif
    }
    
    return kStatus_SMARTCARD_Success;
}

/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_UART_DRV_CompleteReceiveData
* Description   : Finish up a receive by completing the process of receiving 
* data and disabling the interrupt. 
* This is not a public API as it is called from other driver functions.
*
*END**************************************************************************/
static void SMARTCARD_UART_DRV_CompleteReceiveData(uint32_t instance)
{
    assert(instance < UART_INSTANCE_COUNT);
    
    smartcard_state_t * smartcardState = (smartcard_state_t *)g_uartStatePtr[instance];
    UART_Type * base = g_uartBase[instance];
#if defined(FSL_FEATURE_EDMA_MODULE_CHANNEL)
    DMA_Type * edmaBaseAddr = VIRTUAL_CHN_TO_EDMA_MODULE_REGBASE(smartcardState->rxDmaState.channel);
    uint32_t edmaChannel = VIRTUAL_CHN_TO_EDMA_CHN(smartcardState->rxDmaState.channel);
#endif    
    
    if(!smartcardState->useDMA)
    {
        /* Disable receive data full interrupt */
        UART_BWR_C2_RIE(base, 0U);
    }
    else
    {
#if defined(FSL_FEATURE_EDMA_MODULE_CHANNEL)
        /* Disable DMA major loop interrupt */
        EDMA_HAL_HTCDSetIntCmd(edmaBaseAddr, edmaChannel, false);
        
        /* Stop DMA channel. */
        EDMA_HAL_SetDmaRequestCmd(edmaBaseAddr, (edma_channel_indicator_t)edmaChannel, false);
#elif defined(FSL_FEATURE_DMA_DMAMUX_CHANNELS)
        /* Stop DMA channel. */
        DMA_DRV_StopChannel(&smartcardState->rxDmaState);
#endif
        
        /* Disable DMA trigger. */
        UART_HAL_SetRxDmaCmd(base, false);
    
        /* Check if DMA transfer completed normally or not */
        if(((smartcardState->tType == kSmartcardT0Transport) && (smartcardState->timersState.wwtExpired))
           || ((smartcardState->tType == kSmartcardT1Transport) && ((smartcardState->timersState.cwtExpired) || (smartcardState->timersState.bwtExpired))))
        {
#if defined(FSL_FEATURE_EDMA_MODULE_CHANNEL)
            /* Read number of left of bytes left to read from DMA channel */
            smartcardState->rxSize = EDMA_HAL_HTCDGetUnfinishedBytes(edmaBaseAddr, edmaChannel);
#elif defined(FSL_FEATURE_DMA_DMAMUX_CHANNELS)
            /* Read number of left of bytes left to read from DMA channel */
            smartcardState->rxSize = DMA_DRV_GetUnfinishedBytes(&smartcardState->rxDmaState);
#endif
        }
        else
        {
            /* transfer completed normally */
            smartcardState->rxSize = 0;
        }
    }
    
    /* Signal the synchronous completion object. */
    if (smartcardState->isRxBlocking)
    {
        OSA_SemaPost(&smartcardState->rxIrqSync);
        smartcardState->isRxBlocking = false;
    }
    
    /* Update the information of the module driver state */
    smartcardState->isRxBusy = false;
}

#if defined(FSL_FEATURE_EDMA_MODULE_CHANNEL)
/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_UART_DRV_EdmaTxCallback
* Description   : Callback function to be called from the EDMA ISR after transmit.
* This is not a public interface.
*
*END**************************************************************************/
static void SMARTCARD_UART_DRV_EdmaTxCallback(void *param, edma_chn_status_t status)
{
    SMARTCARD_UART_DRV_CompleteSendData((uint32_t)param);
}
#elif defined(FSL_FEATURE_DMA_DMAMUX_CHANNELS)
/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_UART_DRV_DmaTxCallback
* Description   : Callback function to be called from the DMA ISR after transmit.
* This is not a public interface.
*
*END**************************************************************************/
static void SMARTCARD_UART_DRV_DmaTxCallback(void *param, dma_channel_status_t status)
{
    SMARTCARD_UART_DRV_CompleteSendData((uint32_t)param);
}
#endif

/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_UART_DRV_StartReceiveData
* Description   : Initiate (start) a receive by beginning the process of
* receiving data and enabling the interrupt. 
* This is not a public API as it is called from other driver functions.
*
*END**************************************************************************/
static smartcard_status_t SMARTCARD_UART_DRV_StartReceiveData(uint32_t instance,
                                                              uint8_t * rxBuff,
                                                              uint32_t rxSize)
{
    assert(instance < UART_INSTANCE_COUNT);
    assert(rxBuff);
    
    smartcard_state_t * smartcardState = (smartcard_state_t *)g_uartStatePtr[instance];
    UART_Type * base = g_uartBase[instance];
#if defined(FSL_FEATURE_EDMA_MODULE_CHANNEL)
    DMA_Type * edmaBaseAddr = VIRTUAL_CHN_TO_EDMA_MODULE_REGBASE(smartcardState->rxDmaState.channel);
    uint32_t edmaChannel = VIRTUAL_CHN_TO_EDMA_CHN(smartcardState->rxDmaState.channel);
#elif defined(FSL_FEATURE_DMA_DMAMUX_CHANNELS)
    dma_channel_t *chn = &smartcardState->rxDmaState;
    DMA_Type * dmaBase = g_dmaBase[chn->channel/FSL_FEATURE_DMA_DMAMUX_CHANNELS];

    dma_channel_link_config_t config =
    {
        kDmaChannelLinkDisable, /* linkType */
        0,                      /* channel1 */
        0,                      /* channel2 */
    };
#endif    
    
    /* Check that we're not busy receiving data from a previous function call. */
    if (smartcardState->isRxBusy)
    {
        return kStatus_SMARTCARD_RxBusy;
    }
    
    /* Initialize the module driver state struct to indicate transfer in progress */
    smartcardState->isRxBusy = true;
    
    if(!smartcardState->useDMA)
    {
        /* Disable transmitter */
        UART_HAL_DisableTransmitter(base);
        
        /* Enable receiver and switch to receive direction */
        UART_HAL_EnableReceiver(base);
        UART_HAL_SetTransmitterDir(base, kUartSinglewireTxdirIn);
        
        /*Disable GTV flag for data receiving*/
        UART_HAL_SetISO7816IntMode(base, kUartIntIso7816GuardTimerViolated, false);
        
        /* Initialize the module driver state struct with the buffer and byte count data */
        smartcardState->rxBuff = rxBuff;
        smartcardState->rxSize = rxSize;        
        
        /* Enable the receive data full interrupt */
        UART_BWR_C2_RIE(base, 1U);
    }
    else
    {
        /* Disable transmitter */
        UART_HAL_DisableTransmitter(base);
        
        /* Switch to receive direction */
        UART_HAL_SetTransmitterDir(base, kUartSinglewireTxdirIn);
        
        /* Initialize the module driver state struct with the buffer and byte count data */
        smartcardState->rxBuff = rxBuff;
        smartcardState->rxSize = rxSize;
        
        /* Enable DMA trigger when transmit data register empty, 
        * and receive data register full. */
        UART_HAL_SetRxDmaCmd(base, true);
        
#if defined(FSL_FEATURE_EDMA_MODULE_CHANNEL)
        /* Setup destination */
        EDMA_HAL_HTCDSetDestAddr(edmaBaseAddr, edmaChannel, (uint32_t)rxBuff);
        EDMA_HAL_HTCDSetDestOffset(edmaBaseAddr, edmaChannel, 1);
        EDMA_HAL_HTCDSetDestLastAdjust(edmaBaseAddr, edmaChannel, 0);
        
        /* Setup source */
        EDMA_HAL_HTCDSetSrcAddr(edmaBaseAddr, edmaChannel, UART_HAL_GetDataRegAddr(base));
        EDMA_HAL_HTCDSetSrcOffset(edmaBaseAddr, edmaChannel, 0);
        EDMA_HAL_HTCDSetSrcLastAdjust(edmaBaseAddr, edmaChannel, 0);
        
        /* Setup transfer properties */
        EDMA_HAL_HTCDSetNbytes(edmaBaseAddr, edmaChannel, 1);
        EDMA_HAL_HTCDSetChannelMinorLink(edmaBaseAddr, edmaChannel, 0, false);
        EDMA_HAL_HTCDSetMajorCount(edmaBaseAddr, edmaChannel, rxSize);
        EDMA_HAL_HTCDSetAttribute(edmaBaseAddr, edmaChannel, kEDMAModuloDisable, 
                                  kEDMAModuloDisable, kEDMATransferSize_1Bytes, kEDMATransferSize_1Bytes);
        EDMA_HAL_HTCDSetScatterGatherCmd(edmaBaseAddr, edmaChannel, false);
        EDMA_HAL_HTCDSetDisableDmaRequestAfterTCDDoneCmd(edmaBaseAddr, edmaChannel, true);
        
        /* Enable DMA major loop interrupt */
        EDMA_HAL_HTCDSetIntCmd(edmaBaseAddr, edmaChannel, true);
#elif defined(FSL_FEATURE_DMA_DMAMUX_CHANNELS)
        /* Setup transfer properties */
        DMA_HAL_SetAutoAlignCmd(dmaBase, chn->channel, false);
        DMA_HAL_SetCycleStealCmd(dmaBase, chn->channel, true);
        DMA_HAL_SetAsyncDmaRequestCmd(dmaBase, chn->channel, false);
        DMA_HAL_SetDisableRequestAfterDoneCmd(dmaBase, chn->channel, true);
        DMA_HAL_SetChanLink(dmaBase, chn->channel, &config);
        
        /* Setup source */
        DMA_HAL_SetSourceAddr(dmaBase, chn->channel, UART_HAL_GetDataRegAddr(base));
        DMA_HAL_SetSourceModulo(dmaBase, chn->channel, kDmaModuloDisable);
        DMA_HAL_SetSourceTransferSize(dmaBase, chn->channel, kDmaTransfersize8bits);
        DMA_HAL_SetSourceIncrementCmd(dmaBase, chn->channel, false);
        
        DMA_HAL_SetDestModulo(dmaBase, chn->channel, kDmaModuloDisable);
        DMA_HAL_SetDestTransferSize(dmaBase, chn->channel, kDmaTransfersize8bits);
        DMA_HAL_SetDestIncrementCmd(dmaBase, chn->channel, true);
        
        DMA_HAL_SetIntCmd(dmaBase, chn->channel, true);
        
        /* Setup destination */
        DMA_HAL_SetDestAddr(dmaBase, chn->channel, (uint32_t)rxBuff);
        DMA_HAL_SetTransferCount(dmaBase, chn->channel, rxSize);
#endif
        
        /* Enable rceiver for reception */
        UART_HAL_EnableReceiver(base);
        
#if defined(FSL_FEATURE_EDMA_MODULE_CHANNEL)
        /* Start DMA channel */
        EDMA_HAL_SetDmaRequestCmd(edmaBaseAddr, (edma_channel_indicator_t)edmaChannel, true);
#elif defined(FSL_FEATURE_DMA_DMAMUX_CHANNELS)
        /* Start DMA channel */
        DMA_DRV_StartChannel(chn);
#endif
    }
    
    return kStatus_SMARTCARD_Success;
}

/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_UART_DRV_SetTransferType
* Description   : Sets up the UART hardware for T=0 or T=1 protocol data exchange 
* and initialize timer values. 
* This is not a public API as it is called from other driver functions.
*
*END**************************************************************************/
static void SMARTCARD_UART_DRV_SetTransferType(uint32_t instance, smartcard_control_t control)
{
    assert(instance < UART_INSTANCE_COUNT);
    assert((control != kSmartcardSetupATRMode) || \
        (control != kSmartcardSetupT0Mode) || \
        (control != kSmartcardSetupT1Mode));
    
    uint16_t temp16;
    uint8_t temp8;
    uint16_t bwiVal = 0;
    UART_Type * base = g_uartBase[instance];
    smartcard_state_t * smartcardState = (smartcard_state_t *)g_uartStatePtr[instance];
    uint32_t uartModuleClock = 0;
        
    if(control == kSmartcardSetupATRMode)
    {
        /* Set default values as per EMV specification */
        smartcardState->cardParams.Fi = 372;
        smartcardState->cardParams.currentD = 1;
        smartcardState->cardParams.WI = 0x0A;
        
        /* Get UART module clock from system clock module */
        uartModuleClock = CLOCK_SYS_GetUartFreq(instance);
    
        /* Set baudrate/ETU time based on EMV parameters and card clock */
        UART_HAL_SetISO7816Etu(base, uartModuleClock, smartcardState->interfaceConfig.sCClock, \
            smartcardState->cardParams.Fi, smartcardState->cardParams.currentD);
    
        /* Disable ISO7816 mode 1st */
        UART_HAL_DisableISO7816(base);
        
        /* Set transport protocol type to T=0 */
        UART_HAL_SetTransferProtocolType(base, kUartIso7816TransfertType0);
        
        /* Calculate and set Work Wait Timer (WWT) */
#if FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT
        /* EMV expectation: WWT = (960 x D x WI) + (D x 480) = 480xD x (2xWI + 1)
        * UART formula: WI x 480
        */
        temp16 = smartcardState->cardParams.currentD * ((2 * smartcardState->cardParams.WI) + 1);
        UART_HAL_SetWorkWaitTimeInteger(base, temp16);
#else
        UART_HAL_SetWorkWaitTimeInteger(base, smartcardState->cardParams.WI);
#endif
        
        /* Set Extended Guard Timer value
        * EMV expectation: GT = GTN not equal to 255 -> 12 + GTN
        * = GTN equal to 255 -> 12
        * UART formula: same as above
        */
        if(smartcardState->cardParams.GTN < EMV_RX_TO_TX_GUARD_TIME_T0)
        {
            temp8 = EMV_RX_TO_TX_GUARD_TIME_T0;            
        }
        else
        {
            /* All other values include default 0xFF */
            temp8 = smartcardState->cardParams.GTN;            
        }
        UART_HAL_SetGuardBandInteger(base, temp8);
        
        /* Set FD multiplier */
        UART_HAL_SetFDMultiplier(base, smartcardState->cardParams.currentD);
        
        /* Setup for single wire ISO7816 mode */
        UART_HAL_SetLoopCmd(base, true);
        UART_HAL_SetReceiverSource(base, kUartSingleWire);
        UART_HAL_SetBitCountPerChar(base, kUart9BitsPerChar);
        
        /* Normally, parity mode should be set to kUartParityEven, 
        * but in case can be set to kUartParityOdd to help in initial character 
        * (TS) detection by SW(by switching off hardware feature) */
        if(smartcardState->parity == kSmartcardOddParity)
        {
            UART_HAL_SetParityMode(base, kUartParityOdd);
        }
        else
        {
            UART_HAL_SetParityMode(base, kUartParityEven);
        }
        
        /* 
         * Setting Rx threshld to 0 so that an interrupt is generated when a NACK is 
         * sent either due to parity error or wrong INIT char.
         */
        UART_HAL_SetRxNACKThreshold(base, 0);
        
        /* Setting up Tx NACK threshold */
        UART_HAL_SetTxNACKThreshold(base, EMV_TX_NACK_THRESHOLD);
        
        /* Enable Interrupt for RXT crossing */
        UART_HAL_SetISO7816IntMode(base, kUartIntIso7816RxThreasholdExceeded, true);
        
        /* Enable parity error indication */
        UART_HAL_SetIntMode(base, kUartIntParityErrFlag, true);
        
        /* Enable ISO7816 mode */
        UART_HAL_EnableISO7816(base);
        
        /* Set transport type to T=0 in smartcard state structure */
        smartcardState->tType = kSmartcardT0Transport;
    }
    else if(control == kSmartcardSetupT0Mode)
    {
        /* Disable ISO7816 mode 1st */
        UART_HAL_DisableISO7816(base);
        
        /* Set transport protocol type to T=0 */
        UART_HAL_SetTransferProtocolType(base, kUartIso7816TransfertType0);
        
        /* Calculate and set Work Wait Timer (WWT) */
#if FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT
        /* EMV expectation: WWT = (960 x D x WI) + (D x 480) = 480xD x (2xWI + 1)
        * UART formula: WI x 480
        */
        temp16 = smartcardState->cardParams.currentD * ((2 * smartcardState->cardParams.WI) + 1);
        UART_HAL_SetWorkWaitTimeInteger(base, temp16);
#else
        UART_HAL_SetWorkWaitTimeInteger(base, smartcardState->cardParams.WI);
#endif
        
        /* Set Extended Guard Timer value
        * EMV expectation: GT = GTN not equal to 255 -> 12 + GTN
        * = GTN equal to 255 -> 12
        * UART formula: same as above
        */
        if(smartcardState->cardParams.GTN < EMV_RX_TO_TX_GUARD_TIME_T0)
        {
            temp8 = EMV_RX_TO_TX_GUARD_TIME_T0;            
        }
        else
        {
            /* All other values include default 0xFF */
            temp8 = smartcardState->cardParams.GTN;            
        }
        UART_HAL_SetGuardBandInteger(base, temp8);
        
        /* Set FD multiplier */
        UART_HAL_SetFDMultiplier(base, smartcardState->cardParams.currentD);
        
        /* Setup for single wire ISO7816 mode */
        UART_HAL_SetLoopCmd(base, true);
        UART_HAL_SetReceiverSource(base, kUartSingleWire);
        UART_HAL_SetBitCountPerChar(base, kUart9BitsPerChar);
        
        /* Normally, parity mode should be set to kUartParityEven, 
        * but in case can be set to kUartParityOdd to help in initial character 
        * (TS) detection by SW(by switching off hardware feature) */
        if(smartcardState->parity == kSmartcardOddParity)
        {
            UART_HAL_SetParityMode(base, kUartParityOdd);
        }
        else
        {
            UART_HAL_SetParityMode(base, kUartParityEven);
        }
        
        /* Enable Nack on error interrupt */
        UART_HAL_ConfigureNackOnError(base, kUartIso7816AnackEnable);
        
        /*Setting Rx threshld so that an interrupt is generated when a NACK is 
        sent either due to parity error or wrong INIT char*/
        UART_HAL_SetRxNACKThreshold(base, EMV_RX_NACK_THRESHOLD);
        
        /* Setting up Tx NACK threshold */
        UART_HAL_SetTxNACKThreshold(base, EMV_TX_NACK_THRESHOLD);
        
        /* Enable Interrupt for RXT crossing */
        UART_HAL_SetISO7816IntMode(base, kUartIntIso7816RxThreasholdExceeded, true);
        
        /* Enable parity error indication */
        UART_HAL_SetIntMode(base, kUartIntParityErrFlag, true);
        
        /* Enable ISO7816 mode */
        UART_HAL_EnableISO7816(base);
        
        /* Set transport type to T=0 in smartcard state structure */
        smartcardState->tType = kSmartcardT0Transport;
    }
    else
    {
        /* Disable ISO7816 mode 1st */
        UART_HAL_DisableISO7816(base);
        
        /* Set transport protocol type to T=1 */
        UART_HAL_SetTransferProtocolType(base, kUartIso7816TransfertType1);
        
        /* Calculate and set Block Wait Timer (BWT) value */
#if FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT
        /* 
        * EMV expectation: BWT = 11 + (2^BWI x 960 x D) + (D x 960)
        = 11 + (2^BWI + 1) x 960 x D
        * UART formula: BWT = (11 + (BWI × 960 × GTFD)) * (WTX + 1)    
        */
        bwiVal = (1 << smartcardState->cardParams.BWI) + 1;
        UART_HAL_SetBlockWaitTimeInteger(base, bwiVal);
#else
        UART_HAL_SetBlockWaitTimeInteger(base, smartcardState->cardParams.BWI);
#endif
        
#if FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT
        /* Set Wait Timer Multiplier default value */
        UART_HAL_SetWaitTimeMultipllier(base, 0);
#endif
        
        /* Calculate and set Character Wait Timer (BWT) value */
#if FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT
        /* 
        * EMV expectation: CWT = ((2^CWI + 11) + 4)
        * UART formula: CWT = 2^CWI1 + CWI2
        * EMV expectation: BGT = 22
        * UART formula: BWT = 16 + BGI
        */        
        UART_HAL_SetCharacterWaitTimeInteger(base, smartcardState->cardParams.CWI, 15);        /* EMV = 15, ISO = 11*/
        UART_HAL_SetBlockGuardTimeInteger(base, (smartcardState->cardParams.BGI & 0x0F));
#else
        UART_HAL_SetCharacterWaitTimeInteger(base, smartcardState->cardParams.CWI, 0);
#endif
        
        /* Set Extended Guard Timer value
        * EMV expectation: GT = GTN not equal to 255 -> 12 + GTN
        = GTN equal to 255 -> 11
        * UART formula: same as above
        */
        UART_HAL_SetGuardBandInteger(base, smartcardState->cardParams.GTN);
        
        /* Set FD multiplier */
        UART_HAL_SetFDMultiplier(base, smartcardState->cardParams.currentD);
        
        /* Setup for single wire ISO7816 mode */
        UART_HAL_SetLoopCmd(base, true);
        UART_HAL_SetReceiverSource(base, kUartSingleWire);
        UART_HAL_SetBitCountPerChar(base, kUart9BitsPerChar);
        
        /* Set parity mode */
        if(smartcardState->parity == kSmartcardOddParity)
        {
            UART_HAL_SetParityMode(base, kUartParityOdd);
        }
        else
        {
            UART_HAL_SetParityMode(base, kUartParityEven);
        }
        
        /* Set transport protocol type to T=1 */
        UART_HAL_SetTransferProtocolType(base, kUartIso7816TransfertType1);
        
        /* Enable ISO7816 mode */
        UART_HAL_EnableISO7816(base);
        
        /* Clear all ISO interrupt modes, and enable only GTV interrupt by default */
        UART_HAL_SetISO7816IntMode(base, kUartIntIso7816All, false);
        UART_HAL_SetISO7816IntMode(base, kUartIntIso7816GuardTimerViolated, true);
        
        /* Enable ISO7816 mode */
        UART_HAL_EnableISO7816(base);
        
        /* Set transport type to T=1 in smartcard state structure */
        smartcardState->tType = kSmartcardT1Transport;
    }
}

/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_UART_DRV_Control
* Description   : Cotrols different driver settings as per caller request. 
*
*END**************************************************************************/
smartcard_status_t SMARTCARD_UART_DRV_Control(uint32_t instance, smartcard_control_t control, void *controlBuff)
{
    assert(instance < UART_INSTANCE_COUNT);
    
    UART_Type * base = g_uartBase[instance];
    smartcard_state_t * smartcardState = (smartcard_state_t *)g_uartStatePtr[instance];
    uint32_t uartModuleClock;
    
    switch(control)
    {
    case kSmartcardEnableADT: 
#if FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT
        /*Disable ISO-7816 mode first*/
        UART_HAL_DisableISO7816(base);
        
        /* Set ATR timer value */
        UART_HAL_SetAtrDurationTimer(base, EMV_ATR_DURATION_ETU);
        
        /* Enable ATR specific interrupt */
        UART_HAL_SetISO7816IntMode(base, kUartIntIso7816AtrDurationTimer, true);
        
        /*Enable ISO-7816 mode */
        UART_HAL_EnableISO7816(base);
#endif
        break;
    case kSmartcardDisableADT: 
#if FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT
        /* Disable ATR specific interrupt */
        UART_HAL_SetISO7816IntMode(base, kUartIntIso7816AtrDurationTimer, false);
        
        /* Clear ATR timer value */
        UART_HAL_SetAtrDurationTimer(base, 0);
#endif
        break;
        
    case kSmartcardEnableGTV:
        /* Enable GTV specific interrupt */
        UART_HAL_SetISO7816IntMode(base, kUartIntIso7816GuardTimerViolated, true);
        break;
        
    case kSmartcardDisableGTV:
        /* Disable GTV specific interrupt */
        UART_HAL_SetISO7816IntMode(base, kUartIntIso7816GuardTimerViolated, false);
        break;
        
    case kSmartcardResetWWT:
        /* Reset WWT Timer */
        UART_HAL_ResetISO7816WaitTimer(base);
        break;
        
    case kSmartcardEnableWWT:
        /* Enable WWT Timer interrupt to occur */
        UART_HAL_SetISO7816IntMode(base, kUartIntIso7816WaitTimer, true);
        break;
        
    case kSmartcardDisableWWT:
        /* Disable WWT Timer interrupt to occur */
        UART_HAL_SetISO7816IntMode(base, kUartIntIso7816WaitTimer, false);
        break;
        
    case kSmartcardResetCWT:
        /* Reset CWT Timer */
        UART_HAL_ResetISO7816CharacterWaitTimer(base);
        break;
        
    case kSmartcardEnableCWT:
        /* Enable CWT Timer interrupt to occur */
        UART_HAL_SetISO7816IntMode(base, kUartIntIso7816CharWaitTimer, true);
        break;
        
    case kSmartcardDisableCWT:
        /* Disable WWT Timer interrupt to occur */
        UART_HAL_SetISO7816IntMode(base, kUartIntIso7816CharWaitTimer, false);
        break;
        
    case kSmartcardResetBWT:
        /* Reset BWT Timer */
        UART_HAL_ResetISO7816BlockWaitTimer(base);
        break;
        
    case kSmartcardEnableBWT:
        /* Enable BWT Timer interrupt to occur */
        UART_HAL_SetISO7816IntMode(base, kUartIntIso7816BlockWaitTimer, true);
        break;
        
    case kSmartcardDisableBWT:
        /* Disable BWT Timer interrupt to occur */
        UART_HAL_SetISO7816IntMode(base, kUartIntIso7816BlockWaitTimer, false);
        break;
        
    case kSmartcardEnableInitDetect: 
        /*Clear all ISO7816 interrupt flags */ 
        UART_HAL_ClearISO7816InterruptStatus(base, kUartIntIso7816All);
        
        /* Enable initial character detection */
        UART_HAL_ConfigureInitialCharacterDetection(base, kUartIso7816InitdEnable);
        
        /* Check and clear any pending initial character deteted flag */
        if(UART_HAL_GetISO7816InterruptStatus(base, kUartIntIso7816InitialCharDetected))
        {        
            UART_HAL_ClearISO7816InterruptStatus(base, kUartIntIso7816InitialCharDetected);
        }
        
        /* Enable TS detect interrupt*/
        UART_HAL_SetISO7816IntMode(base, kUartIntIso7816InitialCharDetected, true);
        break;
        
    case kSmartcardEnableAnack:
        /* Enable Nack-on-error interrupt to occur */
        UART_HAL_ConfigureNackOnError(base, kUartIso7816AnackEnable);
        break;
        
    case kSmartcardDisableAnack:
        /* Disable Nack-on-error interrupt to occur */
        UART_HAL_ConfigureNackOnError(base, kUartIso7816AnackDisable);
        break;
        
    case kSmartcardConfigureBaudrate:
        /* Get UART module clock from system clock module */
        uartModuleClock = CLOCK_SYS_GetUartFreq(instance);
    
        /* Set baudrate/ETU time based on EMV parameters and card clock */
        UART_HAL_SetISO7816Etu(base, uartModuleClock, smartcardState->interfaceConfig.sCClock, \
            smartcardState->cardParams.Fi, smartcardState->cardParams.currentD);
        
        break;
        
    case kSmartcardSetupATRMode:
        /* Set in default ATR mode */
        SMARTCARD_UART_DRV_SetTransferType(instance, kSmartcardSetupATRMode);
        break;
        
    case kSmartcardSetupT0Mode:
        /* Set transport protocol type to T=0 */
        SMARTCARD_UART_DRV_SetTransferType(instance, kSmartcardSetupT0Mode);
        break;
        
    case kSmartcardSetupT1Mode:
        /* Set transport protocol type to T=1 */
        SMARTCARD_UART_DRV_SetTransferType(instance, kSmartcardSetupT1Mode);
        break;
        
    case kSmartcardEnableReceiverMode:
        /* Enable receiver mode and switch to receive direction */
        UART_HAL_EnableReceiver(base);
        UART_HAL_SetTransmitterDir(base, kUartSinglewireTxdirIn);
        break;
        
    case kSmartcardDisableReceiverMode:
        /* Disable receiver */
        UART_HAL_DisableReceiver(base);
        break;
        
    case kSmartcardEnableTransmitterMode:
        /* Enable transmitter mode and switch to transmit direction */
        UART_HAL_EnableTransmitter(base);
        UART_HAL_SetTransmitterDir(base, kUartSinglewireTxdirOut);
        break;
        
    case kSmartcardDisableTransmitterMode:
        /* Disable transmitter */
        UART_HAL_DisableTransmitter(base);
        break;
        
    case kSmartcardResetWaitTimeMultiplier:
#if FSL_FEATURE_UART_HAS_IMPROVED_SMART_CARD_SUPPORT
        /* Reset Wait Timer Multiplier */
        UART_HAL_ResetWaitTimeMultipllier(base, *((uint8_t *)controlBuff));
        
        /* Set flag to smartcard state accordingly */
        if(*((uint8_t *)controlBuff) == 0)
        {
            smartcardState->wtxRequested = false;
        }
        else
        {
            smartcardState->wtxRequested = true;
        }
#endif
        break;
        
    default: 
        break;
    }
    
    return kStatus_SMARTCARD_Success;
}

/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_UART_TSExpiryCallback
* Description   : This function is called at the expiry of the HW timer expiry,
*                 at a period which was set and started before by the driver.
*
*END**************************************************************************/
static void SMARTCARD_UART_TSExpiryCallback(void *callbackParam)
{
    uint32_t instance = *(uint32_t *)callbackParam;
    smartcard_state_t * smartcardState = (smartcard_state_t *)g_uartStatePtr[instance];
    
    smartcardState->timersState.initCharTimerExpired = true;

    /* Stop TS timer */
    HWTIMER_SYS_Stop(&g_tsTimer[instance]);

    /* Un-block the caller */
    SMARTCARD_UART_DRV_CompleteReceiveData(instance);    
    
    return;
}
/*******************************************************************************
* EOF
******************************************************************************/

