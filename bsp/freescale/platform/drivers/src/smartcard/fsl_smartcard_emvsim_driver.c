/*
* Copyright (c) 2015, Freescale Semiconductor, Inc.
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
#include "fsl_smartcard_emvsim_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"
#include "fsl_emvsim_hal.h"

/*******************************************************************************
* Variables
******************************************************************************/
/* Pointer to emvsim runtime state structure */
extern void * g_emvsimStatePtr[EMVSIM_INSTANCE_COUNT];

/* Table to save emvsim IRQ enum numbers defined in CMSIS header file */
extern const IRQn_Type g_emvsimRxTxIrqId[EMVSIM_INSTANCE_COUNT];

extern smartcard_driver_interface_t smartcardDrvInterface;
/*******************************************************************************
* Private Functions
******************************************************************************/
static void SMARTCARD_EMVSIM_DRV_CompleteSendData(uint32_t instance);
static smartcard_status_t SMARTCARD_EMVSIM_DRV_StartSendData(uint32_t instance,
                                                             const uint8_t * txBuff,
                                                             uint32_t txSize);
static void SMARTCARD_EMVSIM_DRV_CompleteReceiveData(uint32_t instance);
static smartcard_status_t SMARTCARD_EMVSIM_DRV_StartReceiveData(uint32_t instance,
                                                                uint8_t * rxBuff,
                                                                uint32_t rxSize);

#if defined(FSL_FEATURE_EDMA_MODULE_CHANNEL)
static void SMARTCARD_EVMSIM_DRV_EdmaTxCallback(void *param, edma_chn_status_t status);
static void SMARTCARD_EMVSIM_DRV_EdmaRxCallback(void *param, edma_chn_status_t status);
#elif defined(FSL_FEATURE_DMA_DMAMUX_CHANNELS)
static void SMARTCARD_EMVSIM_DRV_DmaTxCallback(void *param, dma_channel_status_t status);
static void SMARTCARD_EMVSIM_DRV_DmaRxCallback(void *param, dma_channel_status_t status);
#endif
static void SMARTCARD_EMVSIM_DRV_SetTransferType(uint32_t instance, smartcard_control_t control);
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

    smartcardDrvInterface.smartcardDrvInit = SMARTCARD_EMVSIM_DRV_Init;
    smartcardDrvInterface.smartcardDrvDeinit = SMARTCARD_EMVSIM_DRV_Deinit;
    smartcardDrvInterface.smartcardDrvSendDataBlocking = SMARTCARD_EMVSIM_DRV_SendDataBlocking;
    smartcardDrvInterface.smartcardDrvSendData = SMARTCARD_EMVSIM_DRV_SendData;
    smartcardDrvInterface.smartcardDrvGetTransmitStatus = SMARTCARD_EMVSIM_DRV_GetTransmitStatus;
    smartcardDrvInterface.smartcardDrvAbortSendingData = SMARTCARD_EMVSIM_DRV_AbortSendingData;
    smartcardDrvInterface.smartcardDrvReceiveDataBlocking = SMARTCARD_EMVSIM_DRV_ReceiveDataBlocking;
    smartcardDrvInterface.smartcardDrvReceiveData = SMARTCARD_EMVSIM_DRV_ReceiveData;
    smartcardDrvInterface.smartcardDrvGetReceiveStatus = SMARTCARD_EMVSIM_DRV_GetReceiveStatus;
    smartcardDrvInterface.smartcardDrvAbortReceivingData = SMARTCARD_EMVSIM_DRV_AbortReceivingData;
    smartcardDrvInterface.smartcardDrvControl = SMARTCARD_EMVSIM_DRV_Control;
}

/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_EMVSIM_DRV_Init
* Description   : This function initializes a EMVSIM instance for operation.
* This function will initialize the run-time state structure to keep track of
* the on-going transfers, ungate the clock to the EMVSIM module, initialize the
* module to user defined settings and default settings, configure the IRQ state
* structure and enable the module-level interrupt to the core, initialize DMA,
* and enable the EMVSIM module transmitter and receiver.
* This function is normally invoked by SMARTCARD composite peripheral driver.
*
*END**************************************************************************/
smartcard_status_t SMARTCARD_EMVSIM_DRV_Init(uint32_t instance, smartcard_state_t * smartcardStatePtr,
                                             const smartcard_user_config_t * smartcardUserConfig)
{
    assert(instance < EMVSIM_INSTANCE_COUNT);
    assert(smartcardStatePtr && smartcardUserConfig);

    EMVSIM_Type * base = g_emvsimBase[instance];

    dma_request_source_t emvsimTxDmaRequest = kDmaRequestMux0Disable;
    dma_request_source_t emvsimRxDmaRequest = kDmaRequestMux0Disable;

    /* Exit if current instance is already initialized. */
    if ((g_smartcardStatePtr[instance]))
    {
        return kStatus_SMARTCARD_Initialized;
    }

    /* Clear the state structure for this instance. */
    memset(smartcardStatePtr, 0, sizeof(smartcard_state_t));

    /* Copy required user configuration to card specific state */
    smartcardStatePtr->interfaceConfig = smartcardUserConfig->interfaceConfig;
    smartcardStatePtr->cardParams.vcc = smartcardUserConfig->vcc;
    smartcardStatePtr->useDMA = (smartcardUserConfig->xferMode == kSmartcardDMAXferMode)?true:false;

    /* Save runtime structure pointer.*/
    g_emvsimStatePtr[instance] = smartcardStatePtr;
    g_smartcardStatePtr[instance] = smartcardStatePtr;

    /* Enable EMVSIM module clock source */
    CLOCK_SYS_SetEmvsimSrc(instance, kClockEmvsimSrcPllFllSel);

    /* Un-gate EMVSIM module clock */
    CLOCK_SYS_EnableEmvsimClock(instance);

    /* Initialize EMVSIM to a known state. */
    EMVSIM_HAL_Init(base);

    /* Create Semaphore for txIrq and rxIrq. */
    if ((kStatus_OSA_Success != OSA_SemaCreate(&smartcardStatePtr->txIrqSync, 0)) ||
        (kStatus_OSA_Success != OSA_SemaCreate(&smartcardStatePtr->rxIrqSync, 0)))
    {
        return kStatus_SMARTCARD_OtherError;
    }

    /* Initialize EMVSIM module for smartcard mode of default operation */
    SMARTCARD_EMVSIM_DRV_SetTransferType(instance, kSmartcardSetupATRMode);

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
            emvsimRxDmaRequest = kDmaRequestMux0Group1EMVSIM0Rx;
            emvsimTxDmaRequest = kDmaRequestMux0Group1EMVSIM0Tx;
            break;
        case 1:
            emvsimRxDmaRequest = kDmaRequestMux0Group1EMVSIM1Rx;
            emvsimTxDmaRequest = kDmaRequestMux0Group1EMVSIM1Tx;
            break;
        default :
            break;
        }
#if defined(FSL_FEATURE_EDMA_MODULE_CHANNEL)
        /* Request DMA channels for RX FIFO. */
        EDMA_DRV_RequestChannel(kEDMAAnyChannel, emvsimRxDmaRequest,
                                &smartcardStatePtr->rxDmaState);
        EDMA_DRV_InstallCallback(&smartcardStatePtr->rxDmaState,
                                 SMARTCARD_EMVSIM_DRV_EdmaRxCallback, (void *)instance);

        /* Request DMA channels for TX FIFO. */
        EDMA_DRV_RequestChannel(kEDMAAnyChannel, emvsimTxDmaRequest,
                                &smartcardStatePtr->txDmaState);
        EDMA_DRV_InstallCallback(&smartcardStatePtr->txDmaState,
                                 SMARTCARD_EVMSIM_DRV_EdmaTxCallback, (void *)instance);
#elif defined(FSL_FEATURE_DMA_DMAMUX_CHANNELS)
        /* Request DMA channels for RX FIFO. */
        DMA_DRV_RequestChannel(kDmaAnyChannel, emvsimRxDmaRequest,
                               &smartcardStatePtr->rxDmaState);
        DMA_DRV_RegisterCallback(&smartcardStatePtr->rxDmaState,
                                 SMARTCARD_EMVSIM_DRV_DmaRxCallback, (void *)instance);

        /* Request DMA channels for TX FIFO. */
        DMA_DRV_RequestChannel(kDmaAnyChannel, emvsimTxDmaRequest,
                               &smartcardStatePtr->txDmaState);
        DMA_DRV_RegisterCallback(&smartcardStatePtr->txDmaState,
                                 SMARTCARD_EMVSIM_DRV_DmaTxCallback, (void *)instance);
#endif
    } /* End of if(smartcardStatePtr->useDMA) */

    /* Enable EMVSIM interrupt on NVIC level. */
    INT_SYS_EnableIRQ(g_emvsimRxTxIrqId[instance]);

    /* Finally, enable the EMVSIM transmitter and receiver*/
    EMVSIM_HAL_SetControl(base, kEmvsimCtrlTransmitterEnable, false);
    EMVSIM_HAL_SetControl(base, kEmvsimCtrlReceiverEnable, false);

    return kStatus_SMARTCARD_Success;
}

/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_EMVSIM_DRV_Deinit
* Description   : This function shuts down the EMVSIM by disabling interrupts and
*                 the transmitter/receiver.
* This function disables the EMVSIM interrupts, disables the transmitter and
* receiver, and flushes the FIFOs (for modules that support FIFOs).
*
*END**************************************************************************/
void SMARTCARD_EMVSIM_DRV_Deinit(uint32_t instance)
{
    assert(instance < EMVSIM_INSTANCE_COUNT);

    EMVSIM_Type * base = g_emvsimBase[instance];
    smartcard_state_t * smartcardState = (smartcard_state_t *)g_emvsimStatePtr[instance];
    
    /* Check if driver is already de-initialized */
    if (smartcardState == NULL)
    {
        return;
    }
    /* In case there is still data in the TX FIFO or shift register that is
    * being transmitted wait till transmit is complete. */

    /* Wait until the data is completely shifted out of shift register */
    while(!(EMVSIM_HAL_GetTransmitStatus(base, kEmvsimTxComplete))) { }

    EMVSIM_HAL_SetControl(base, kEmvsimCtrlTxDmaEnable, false);
    EMVSIM_HAL_SetControl(base, kEmvsimCtrlRxDmaEnable, false);
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
    INT_SYS_DisableIRQ(g_emvsimRxTxIrqId[instance]);

    /* Disable TX and RX */
    EMVSIM_HAL_SetControl(base, kEmvsimCtrlTransmitterEnable, false);
    EMVSIM_HAL_SetControl(base, kEmvsimCtrlReceiverEnable, false);

    /* Destroy TX and RX sema. */
    OSA_SemaDestroy(&smartcardState->txIrqSync);
    OSA_SemaDestroy(&smartcardState->rxIrqSync);

    /* Clear state pointer. */
    g_emvsimStatePtr[instance] = NULL;
    g_smartcardStatePtr[instance] = NULL;

    /* Gate EMVSIM module clock */
    CLOCK_SYS_DisableEmvsimClock(instance);
}

/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_EMVSIM_DRV_SendDataBlocking
* Description   : This function sends (transmits) data out through the EMVSIM
* module using a blocking method.
* A blocking (also known as synchronous) function means that the function does
* not return until the transmit is complete. This blocking function is used to
* send data through the EMVSIM port.
*
*END**************************************************************************/
smartcard_status_t SMARTCARD_EMVSIM_DRV_SendDataBlocking(uint32_t instance,
                                                         const uint8_t * txBuff,
                                                         uint32_t txSize,
                                                         uint32_t timeout)
{
    assert(instance < EMVSIM_INSTANCE_COUNT);
    assert(txBuff);

    EMVSIM_Type * base = g_emvsimBase[instance];
    smartcard_state_t * smartcardState = (smartcard_state_t *)g_emvsimStatePtr[instance];
    smartcard_status_t error = kStatus_SMARTCARD_Success;
    osa_status_t syncStatus;

    /* Indicates current transaction is blocking.*/
    smartcardState->isTxBlocking = true;

    /* Start the transmission process */
    if (SMARTCARD_EMVSIM_DRV_StartSendData(instance, txBuff, txSize) == kStatus_SMARTCARD_TxBusy)
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
        SMARTCARD_EMVSIM_DRV_AbortSendingData(instance);
        error = kStatus_SMARTCARD_Timeout;
    }

    if(smartcardState->tType == kSmartcardT1Transport)
    {
        /* For T=1 protocol data transmit, clear state */
        smartcardState->timersState.cwtExpired = false;
        smartcardState->timersState.bwtExpired = false;

        /* Disable CWT interrupt */
        EMVSIM_HAL_SetIntMode(base, kEmvsimIntCWTErr, false);
    }

    if(smartcardState->txtCrossed)
    {
        smartcardState->txtCrossed = false;
    }

    return error;
}

/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_EMVSIM_DRV_SendData
* Description   : This function sends (transmits) data through the EMVSIM module
* using a non-blocking method.
* A non-blocking (also known as asynchronous) function means that the function
* returns immediately after initiating the transmit function. The application
* has to get the transmit status to see when the transmit is complete. In
* other words, after calling non-blocking (asynchronous) send function, the
* application must get the transmit status to check if transmit is completed
* or not. The asynchronous method of transmitting and receiving allows the EMVSIM
* to perform a full duplex operation (simultaneously transmit and receive).
*
*END**************************************************************************/
smartcard_status_t SMARTCARD_EMVSIM_DRV_SendData(uint32_t instance,
                                                 const uint8_t * txBuff,
                                                 uint32_t txSize)
{
    assert(instance < EMVSIM_INSTANCE_COUNT);
    assert(txBuff);

    smartcard_state_t * smartcardState = (smartcard_state_t *)g_emvsimStatePtr[instance];

    /* Indicates current transaction is non-blocking */
    smartcardState->isTxBlocking = false;

    /* Start the transmission process */
    if (SMARTCARD_EMVSIM_DRV_StartSendData(instance, txBuff, txSize) == kStatus_SMARTCARD_TxBusy)
    {
        return kStatus_SMARTCARD_TxBusy;
    }

    return kStatus_SMARTCARD_Success;
}

/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_EMVSIM_DRV_GetTransmitStatus
* Description   : This function returns whether the previous EMVSIM transmit has
* finished.
* When performing an async transmit, the user can call this function to
* ascertain the state of the current transmission: in progress (or busy) or
* complete (success). In addition, if the transmission is still in progress,
* the user can obtain the number of words that have been currently transferred.
*
*END**************************************************************************/
smartcard_status_t SMARTCARD_EMVSIM_DRV_GetTransmitStatus(uint32_t instance, uint32_t * bytesRemaining)
{
    assert(instance < EMVSIM_INSTANCE_COUNT);

    smartcard_state_t * smartcardState = (smartcard_state_t *)g_emvsimStatePtr[instance];

    /* Fill in the bytes transferred. This may return that all bytes were
    * transmitted, however, for IPs with FIFO support, there still may be data
    * in the TX FIFO still in the process of being transmitted. */
    if (bytesRemaining)
    {
        *bytesRemaining = smartcardState->txSize;
    }

    /* Return kStatus_SMARTCARD_TxBusy or kStatus_SMARTCARD_Success depending on whether
    * or not the EMVSIM has a FIFO. If it does have a FIFO, we'll need to wait
    * until the FIFO is completely drained before indicating success in
    * addition to isTxBusy = 0. If there is no FIFO, then we need to only worry
    * about isTxBusy. */
    return (smartcardState->isTxBusy ? kStatus_SMARTCARD_TxBusy : kStatus_SMARTCARD_Success);
}

/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_EMVSIM_DRV_AbortSendingData
* Description   : This function ends a non-blocking EMVSIM transmission early.
* During a non-blocking EMVSIM transmission, the user has the option to terminate
* the transmission early if the transmission is still in progress.
*
*END**************************************************************************/
smartcard_status_t SMARTCARD_EMVSIM_DRV_AbortSendingData(uint32_t instance)
{
    assert(instance < EMVSIM_INSTANCE_COUNT);

    smartcard_state_t * smartcardState = (smartcard_state_t *)g_emvsimStatePtr[instance];

    /* Check if a transfer is running. */
    if (!smartcardState->isTxBusy)
    {
        return kStatus_SMARTCARD_NoTransmitInProgress;
    }

    /* Stop the running transfer. */
    SMARTCARD_EMVSIM_DRV_CompleteSendData(instance);

    return kStatus_SMARTCARD_Success;
}

/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_EMVSIM_DRV_ReceiveDataBlocking
* Description   : This function gets (receives) data from the EMVSIM module using
* a blocking method. A blocking (also known as synchronous) function means that
* the function does not return until the receive is complete. This blocking
* function is used to send data through the EMVSIM port.
*
*END**************************************************************************/
smartcard_status_t SMARTCARD_EMVSIM_DRV_ReceiveDataBlocking(uint32_t instance, uint8_t * rxBuff,
                                                            uint32_t rxSize, uint32_t * rcvdSize, uint32_t timeout)
{
    assert(instance < EMVSIM_INSTANCE_COUNT);
    assert(rxBuff);
    assert(rcvdSize);

    smartcard_state_t * smartcardState = (smartcard_state_t *)g_emvsimStatePtr[instance];
    smartcard_status_t error = kStatus_SMARTCARD_Success;
    osa_status_t syncStatus;

    smartcardState->transState = kSmartcardReceivingState;

    /* Indicates current transaction is blocking.*/
    smartcardState->isRxBlocking = true;

    /* Initialize error check flags */
    smartcardState->rxtCrossed = false;
    smartcardState->parityError = false;

    if (SMARTCARD_EMVSIM_DRV_StartReceiveData(instance, rxBuff, rxSize) == kStatus_SMARTCARD_RxBusy)
    {
        return kStatus_SMARTCARD_RxBusy;
    }

    /* Wait until all the data is received or for timeout.*/
    do
    {
       syncStatus = OSA_SemaWait(&smartcardState->rxIrqSync, timeout);
    }while((syncStatus == kStatus_OSA_Idle) || (syncStatus == kStatus_OSA_Timeout));

    if (syncStatus != kStatus_OSA_Success)
    {
        /* Abort the transfer so it doesn't continue unexpectedly.*/
        SMARTCARD_EMVSIM_DRV_AbortReceivingData(instance);
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

    /* Update received data size */
    *rcvdSize = rxSize - smartcardState->rxSize;

    return error;
}

/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_EMVSIM_DRV_ReceiveData
* Description   : This function gets (receives) data from the EMVSIM module using
* a non-blocking method.
* A non-blocking (also known as synchronous) function means that the function
* returns immediately after initiating the receive function. The application
* has to get the receive status to see when the receive is complete. In other
* words, after calling non-blocking (asynchronous) get function, the
* application must get the receive status to check if receive is completed or
* not. The asynchronous method of transmitting and receiving allows the EMVSIM
* to perform a full duplex operation (simultaneously transmit and receive).
*
*END**************************************************************************/
smartcard_status_t SMARTCARD_EMVSIM_DRV_ReceiveData(uint32_t instance,
                                                    uint8_t * rxBuff,
                                                    uint32_t rxSize)
{
    assert(instance < EMVSIM_INSTANCE_COUNT);
    assert(rxBuff);

    smartcard_state_t * smartcardState = (smartcard_state_t *)g_emvsimStatePtr[instance];

    /* Indicates current transaction is non-blocking.*/
    smartcardState->isRxBlocking = false;

    /* Initialize the error flags */
    smartcardState->rxtCrossed = false;
    smartcardState->parityError = false;

    if (SMARTCARD_EMVSIM_DRV_StartReceiveData(instance, rxBuff, rxSize) == kStatus_SMARTCARD_RxBusy)
    {
        return kStatus_SMARTCARD_RxBusy;
    }

    return kStatus_SMARTCARD_Success;
}

/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_EMVSIM_DRV_GetReceiveStatus
* Description   : This function returns whether the previous EMVSIM receive is
*                 completed.
* When performing a non-blocking receive, the user can call this function to
* ascertain the state of the current receive progress: in progress (or busy)
* or complete (success). In addition, if the receive is still in progress, the
* user can obtain the number of words that have been currently received.
*
*END**************************************************************************/
smartcard_status_t SMARTCARD_EMVSIM_DRV_GetReceiveStatus(uint32_t instance,
                                                         uint32_t * bytesRemaining)
{
    assert(instance < EMVSIM_INSTANCE_COUNT);

    smartcard_state_t * smartcardState = (smartcard_state_t *)g_emvsimStatePtr[instance];
#if defined(FSL_FEATURE_EDMA_MODULE_CHANNEL)
    DMA_Type * edmaBaseAddr = VIRTUAL_CHN_TO_EDMA_MODULE_REGBASE(smartcardState->txDmaState.channel);
    uint32_t edmaChannel = VIRTUAL_CHN_TO_EDMA_CHN(smartcardState->txDmaState.channel);
#endif
    smartcard_status_t retVal = kStatus_SMARTCARD_Success;
    uint32_t rxSize = 0;

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
* Function Name : SMARTCARD_EMVSIM_DRV_AbortReceivingData
* Description   : This function shuts down the EMVSIM by disabling interrupts and
*                 the transmitter/receiver.
* This function disables the EMVSIM interrupts, disables the transmitter and
* receiver, and flushes the FIFOs (for modules that support FIFOs).
*
*END**************************************************************************/
smartcard_status_t SMARTCARD_EMVSIM_DRV_AbortReceivingData(uint32_t instance)
{
    assert(instance < EMVSIM_INSTANCE_COUNT);
    smartcard_state_t * smartcardState = (smartcard_state_t *)g_emvsimStatePtr[instance];

    /* Check if a transfer is running. */
    if (!smartcardState->isRxBusy)
    {
        return kStatus_SMARTCARD_NoReceiveInProgress;
    }

    /* Stop the running transfer. */
    SMARTCARD_EMVSIM_DRV_CompleteReceiveData(instance);

    return kStatus_SMARTCARD_Success;
}

#if defined(FSL_FEATURE_EDMA_MODULE_CHANNEL)
/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_EMVSIM_DRV_EdmaRxCallback
* Description   : Callback function to be called from the EDMA ISR after receive.
* This is not a public interface.
*
*END**************************************************************************/
static void SMARTCARD_EMVSIM_DRV_EdmaRxCallback(void *param, edma_chn_status_t status)
{
    SMARTCARD_EMVSIM_DRV_CompleteReceiveData((uint32_t)param);
}
#elif defined(FSL_FEATURE_DMA_DMAMUX_CHANNELS)
/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_EMVSIM_DRV_DmaRxCallback
* Description   : Callback function to be called from the DMA ISR after receive.
* This is not a public interface.
*
*END**************************************************************************/
static void SMARTCARD_EMVSIM_DRV_DmaRxCallback(void *param, dma_channel_status_t status)
{
    SMARTCARD_EMVSIM_DRV_CompleteReceiveData((uint32_t)param);
}
#endif

/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_EMVSIM_DRV_IRQHandler
* Description   : Interrupt handler for EMVSIM.
* This handler uses the buffers stored in the smartcard_state_t structs to transfer
* data. This is not a public API as it is called whenever an interrupt occurs.
*
*END**************************************************************************/
void SMARTCARD_EMVSIM_DRV_IRQHandler(uint32_t instance)
{
    assert(instance < EMVSIM_INSTANCE_COUNT);

    smartcard_state_t * smartcardState = (smartcard_state_t *)g_emvsimStatePtr[instance];
    EMVSIM_Type * base = g_emvsimBase[instance];
    uint8_t temp8 = 0;

    /* Check card insertion/removal interrupt, only EMVSIM DIRECT interface driver using enables this interrupt to occur */
    if((EMVSIM_HAL_GetIntMode(base, kEmvsimIntPresenceDetect)) && (EMVSIM_HAL_GetCardPresenceDetectInterruptStatus(base)))
    {
        /* Clear interrupt */
        EMVSIM_HAL_ClearCardPresenceDetectInterruptStatus(base);

        if((EMVSIM_HAL_GetCardPresenceDetectEdge(base) == kEmvsimPDOnFallingEdge)
           && (EMVSIM_HAL_GetCardPresenceDetectPinStatus(base) == kEmvsimPDPinIsLow))
        {
            EMVSIM_HAL_SetCardPresenceDetectEdge(base, kEmvsimPDOnRisingEdge);
        }
        else if((EMVSIM_HAL_GetCardPresenceDetectEdge(base) == kEmvsimPDOnRisingEdge)
           && (EMVSIM_HAL_GetCardPresenceDetectPinStatus(base) == kEmvsimPDPinIsHigh))
        {
            EMVSIM_HAL_SetCardPresenceDetectEdge(base, kEmvsimPDOnFallingEdge);
        }

        /* Card presence(insertion)/removal detected */
        /* Invoke callback if there is one */
        if (smartcardState->interfaceCallback != NULL)
        {
            smartcardState->interfaceCallback(instance, smartcardState->interfaceCallbackParam);
        }
    }

    /* Check if timer for initial character (TS) detection has expired */
    if((EMVSIM_HAL_GetIntMode(base, kEmvsimIntGPCnt0)) && (EMVSIM_HAL_GetTransmitStatus(base, kEmvsimGPCNT0Timeout)))
    {
        smartcardState->timersState.initCharTimerExpired = true;

        /* Disable and clear GPCNT interrupt */
        EMVSIM_HAL_SetIntMode(base, kEmvsimIntGPCnt0, false);
        /* Down counter trigger, and clear any pending counter status flag */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlReceiverEnable, false);
        EMVSIM_HAL_ClearTransmitStatus(base, kEmvsimGPCNT0Timeout);
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlReceiverEnable, true);

        EMVSIM_HAL_SetGPCClockSelect(base, 0, kEmvsimGPCClockDisable);


        /* Un-block the caller */
        SMARTCARD_EMVSIM_DRV_CompleteReceiveData(instance);
    }

    /* Check if timer for ATR duration timer has expired */
    if((EMVSIM_HAL_GetIntMode(base, kEmvsimIntGPCnt1)) && (EMVSIM_HAL_GetTransmitStatus(base, kEmvsimGPCNT1Timeout)))
    {
        /* Disable and clear GPCNT interrupt */
        EMVSIM_HAL_SetIntMode(base, kEmvsimIntGPCnt1, false);
        EMVSIM_HAL_ClearTransmitStatus(base, kEmvsimGPCNT1Timeout);
        EMVSIM_HAL_SetGPCClockSelect(base, 1, kEmvsimGPCClockDisable);

        if (smartcardState->bwtActive)
        {
            /* Down counter trigger, and clear any pending counter status flag */
            EMVSIM_HAL_SetControl(base, kEmvsimCtrlReceiverEnable, false);
            smartcardState->bwtActive = false;
            /* Unblock waiting task */
            OSA_SemaPost(&smartcardState->txIrqSync);
            return;
        }
        else
        {
            smartcardState->timersState.adtExpired = true;
            /* Un-block the caller */
            SMARTCARD_EMVSIM_DRV_CompleteReceiveData(instance);
        }
    }

    /*
    * Check if a parity error was indicated.
    * A parity error will cause transmission of NACK if ANACK bit is set in
    * CTRL register and PEF bit will not be asserted. When ANACK is not set,
    * PEF will be asserted.
    */
    if(EMVSIM_HAL_GetReceiveStatus(base, kEmvsimParityErr))
    {
        smartcardState->parityError = true;

        /* Clear parity error indication */
        EMVSIM_HAL_ClearReceiveStatus(base, kEmvsimParityErr);
    }

    if(smartcardState->transState != kSmartcardWaitingForTSState)
    {
        /* Exit the ISR if no transfer is happening for this instance. */
        if ((!smartcardState->isTxBusy) && (!smartcardState->isRxBusy))
        {
            return;
        }
    }

    /* Check if transmit NACK generation threshold was reached */
    if(EMVSIM_HAL_GetTransmitStatus(base, kEmvsimTxNackThresholdErr))
    {
        smartcardState->txtCrossed = true;
    }

    /* Check if receive NACK generation threshold was reached */
    if(EMVSIM_HAL_GetReceiveStatus(base, kEmvsimRxNackThresholdErr))
    {
        smartcardState->rxtCrossed = true;

        /* Un-block the caller */
        SMARTCARD_EMVSIM_DRV_CompleteReceiveData(instance);

        /* Clear receiver NACK threshold interrupt status */
        EMVSIM_HAL_ClearReceiveStatus(base, kEmvsimRxNackThresholdErr);
    }

    /* Check if a Character Wait Timer expired */
    if(EMVSIM_HAL_GetReceiveStatus(base, kEmvsimCWTErr))
    {
        /* Disable Character Wait Timer interrupt */
        EMVSIM_HAL_SetIntMode(base, kEmvsimIntCWTErr, false);

        /* Clear interrupt status */
        EMVSIM_HAL_ClearReceiveStatus(base, kEmvsimCWTErr);

        /* Reset CWT timer */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlCWTEnable, false);
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlCWTEnable, true);

        smartcardState->transState = kSmartcardIdleState;

        if(smartcardState->tType == kSmartcardT0Transport)
        {
            /* Indicate WWT expired */
            smartcardState->timersState.wwtExpired = true;
        }
        else
        {
            /* Indicate CWT expired */
            smartcardState->timersState.cwtExpired = true;
        }

        if((smartcardState->isTxBusy) || (smartcardState->isRxBusy))
        {
            /* Terminate and un-block any caller */
            SMARTCARD_EMVSIM_DRV_CompleteReceiveData(instance);
        }
    }

    /* Check if a Block Wait Timer expired */
    if(EMVSIM_HAL_GetReceiveStatus(base, kEmvsimBWTErr))
    {
        /* Disable Block Wait Timer interrupt */
        EMVSIM_HAL_SetIntMode(base, kEmvsimIntBWTErr, false);

        /* Clear interrupt status flag */
        EMVSIM_HAL_ClearReceiveStatus(base, kEmvsimBWTErr);

        /* Reset BWT timer */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlBWTEnable, false);
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlBWTEnable, true);

        if(smartcardState->tType == kSmartcardT0Transport)
        {
            /* Indicate WWT expired */
            smartcardState->timersState.wwtExpired = true;
        }
        else
        {
            /* Indicate BWT expired */
            smartcardState->timersState.bwtExpired = true;
        }

        /* Check if Wait Time Extension(WTX) was requested */
        if(smartcardState->wtxRequested)
        {
            /* Reset WTX to default */
            temp8 = 1;
            SMARTCARD_EMVSIM_DRV_Control(instance, kSmartcardResetWaitTimeMultiplier, &temp8);
        }

        if((smartcardState->isTxBusy) || (smartcardState->isRxBusy))
        {
            /* Terminate and un-block any caller */
            SMARTCARD_EMVSIM_DRV_CompleteReceiveData(instance);
        }
    }

    /* Handle receive data register full interrupt, if rx data register full
    * interrupt is enabled AND there is data available. */
    if((EMVSIM_HAL_GetIntMode(base, kEmvsimIntRxData)) && (EMVSIM_HAL_GetReceiveStatus(base, kEmvsimRxData)))
    {
        if(smartcardState->transState == kSmartcardWaitingForTSState)
        {
            EMVSIM_HAL_GetChar(base, &temp8);

            if(EMVSIM_HAL_GetControl(base, kEmvsimCtrlinitialCharacterMode))
            {
                /* ICM mode still enabled, this is due to parity error */
                smartcardState->transState = kSmartcardInvalidTSDetecetedState;
            }
            else
            {
                /* Received valid TS */
                smartcardState->transState = kSmartcardReceivingState;
                /* Get Data Convention form by reading IC bit of EMVSIM_CTRL register */
                smartcardState->cardParams.convention = (smartcard_card_convention_t)EMVSIM_HAL_GetControl(base, kEmvsimCtrlInverseConvention);
            }

            if(smartcardState->transState == kSmartcardInvalidTSDetecetedState)
            {
                /* Stop initial character (TS) detection timer and it's interrupt to occur */
                EMVSIM_HAL_SetGPCClockSelect(base, 0, kEmvsimGPCClockDisable);
                EMVSIM_HAL_SetIntMode(base, kEmvsimIntGPCnt0, false);

                SMARTCARD_EMVSIM_DRV_CompleteReceiveData(instance);
            }

            if(smartcardState->transState == kSmartcardReceivingState)
            {
                /* Stop initial character (TS) detection timer and it's interrupt to occur */
                EMVSIM_HAL_SetGPCClockSelect(base, 0, kEmvsimGPCClockDisable);
                EMVSIM_HAL_SetIntMode(base, kEmvsimIntGPCnt0, false);

                /* Start ATR duration counter */
                /* Enable counter interrupt */
                EMVSIM_HAL_SetIntMode(base, kEmvsimIntGPCnt1, true);

                /* Start ATR duration counter (restart GPCNT) */
                EMVSIM_HAL_SetGPCClockSelect(base, 1, kEmvsimGPCClockDisable);
                EMVSIM_HAL_SetGPCClockSelect(base, 1, kEmvsimGPCTxClock);

                SMARTCARD_EMVSIM_DRV_CompleteReceiveData(instance);

                if(smartcardState->useDMA)
                {
                    EMVSIM_HAL_SetIntMode(base, kEmvsimIntRxData, false);
                }
            }

            /* Return anyway */
            return;
        }

        /* Get data and put into receive buffer */
        EMVSIM_HAL_GetChar(base, smartcardState->rxBuff);
        /* Clear received data interrupt status */
        EMVSIM_HAL_ClearReceiveStatus(base, kEmvsimRxData);

        ++smartcardState->rxBuff;
        --smartcardState->rxSize;

        if((smartcardState->tType == kSmartcardT1Transport)
           && (smartcardState->rxSize > 0)
               && (EMVSIM_HAL_GetIntMode(base, kEmvsimIntBWTErr)))
        {
            /* Only the 1st byte has been received, now time to disable BWT interrupt */
            EMVSIM_HAL_SetIntMode(base, kEmvsimIntBWTErr, false);
            /* And, enable CWT interrupt */
            smartcardState->timersState.cwtExpired = false;
            EMVSIM_HAL_SetIntMode(base, kEmvsimIntCWTErr, true);
        }

        /* Check and see if this was the last byte received */
        if (smartcardState->rxSize == 0)
        {
            SMARTCARD_EMVSIM_DRV_CompleteReceiveData(instance);
        }
    }

    /* Handle transmit data register empty interrupt and
    * last data was shifted out of IO line */
    if((EMVSIM_HAL_GetTransmitStatus(base, kEmvsimTxFIFOEmpty)) && (EMVSIM_HAL_GetTransmitStatus(base, kEmvsimTxComplete)))
    {
        if(smartcardState->txtCrossed)
        {
            /* Un-block the caller */
            SMARTCARD_EMVSIM_DRV_CompleteSendData(instance);

            /* Disable and Clear TNTE interrupt */
            EMVSIM_HAL_SetIntMode(base, kEmvsimIntTxNackThresold, false);
            EMVSIM_HAL_ClearTransmitStatus(base, kEmvsimTxNackThresholdErr);
        }
        else
        {
            /* Check to see if there are any more bytes to send */
            if (smartcardState->txSize)
            {
                uint8_t emptyEntryCountInFifo;
                emptyEntryCountInFifo = smartcardState->txFifoEntryCount;

                while(emptyEntryCountInFifo--)
                {
                    /* Transmit data and update tx size/buff */
                    EMVSIM_HAL_PutChar(base, *(smartcardState->txBuff));

                    /* Clear TCF interrupt */
                    EMVSIM_HAL_ClearTransmitStatus(base, kEmvsimTxComplete);

                    ++smartcardState->txBuff;
                    --smartcardState->txSize;

                    if (!smartcardState->txSize)
                    {
                        SMARTCARD_EMVSIM_DRV_CompleteSendData(instance);
                        break;
                    }
                }
            }
        }
    }
}

/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_EMVSIM_DRV_CompleteSendData
* Description   : Finish up a transmit by completing the process of sending
* data and disabling the interrupt.
* This is not a public API as it is called from other driver functions.
*
*END**************************************************************************/
static void SMARTCARD_EMVSIM_DRV_CompleteSendData(uint32_t instance)
{
    assert(instance < EMVSIM_INSTANCE_COUNT);

    EMVSIM_Type * base = g_emvsimBase[instance];
    smartcard_state_t * smartcardState = (smartcard_state_t *)g_emvsimStatePtr[instance];
#if defined(FSL_FEATURE_EDMA_MODULE_CHANNEL)
    DMA_Type * edmaBaseAddr = VIRTUAL_CHN_TO_EDMA_MODULE_REGBASE(smartcardState->txDmaState.channel);
    uint32_t edmaChannel = VIRTUAL_CHN_TO_EDMA_CHN(smartcardState->txDmaState.channel);
#endif

    EMVSIM_HAL_SetAdditionalTransmitterGuardTime(base, 0x00);

    if(!smartcardState->useDMA)
    {
        /* Disable the transmission complete interrupt */
        EMVSIM_HAL_SetIntMode(base, kEmvsimIntTxComplete, false);
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

        /* Disable DMA trigger when transmit data register empty,
        * and receive data register full. */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlTxDmaEnable, false);
    }

    /* Wait for TC bit to set - last byte transmission has finished */
    while ((!EMVSIM_HAL_GetTransmitStatus(base, kEmvsimTxComplete))) {}

    EMVSIM_HAL_SetAdditionalTransmitterGuardTime(base, smartcardState->cardParams.GTN);

    /* disable after transmit */
    EMVSIM_HAL_SetControl(base, kEmvsimCtrlTransmitterEnable, false);
    /* Disable DMA trigger */
    EMVSIM_HAL_SetControl(base, kEmvsimCtrlRxDmaEnable, false);
    /* Clear receive status flag */
    EMVSIM_HAL_ClearReceiveStatus(base, kEmvsimRxData);
    /* Enable Receiver */
    EMVSIM_HAL_SetControl(base, kEmvsimCtrlReceiverEnable, true);

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
* Function Name : SMARTCARD_EMVSIM_DRV_StartSendData
* Description   : Initiate (start) a transmit by beginning the process of
* sending data and enabling the interrupt.
* This is not a public API as it is called from other driver functions.
*
*END**************************************************************************/
static smartcard_status_t SMARTCARD_EMVSIM_DRV_StartSendData(uint32_t instance,
                                                             const uint8_t * txBuff,
                                                             uint32_t txSize)
{
    assert(instance < EMVSIM_INSTANCE_COUNT);
    assert(txBuff);

    EMVSIM_Type * base = g_emvsimBase[instance];
    smartcard_state_t * smartcardState = (smartcard_state_t *)g_emvsimStatePtr[instance];
    uint32_t delay = 0;
    osa_status_t syncStatus;
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
        0,                      /* channel2 */
    };
#endif

    /* Check that we're not busy already transmitting data from a previous
     * function call. */
    if (smartcardState->isTxBusy)
    {
        return kStatus_SMARTCARD_TxBusy;
    }

    /* Block guard time */
    if(smartcardState->tType == kSmartcardT0Transport)
    {   /* 16 etu - 11 etu from the start bit of the last received byte * (16 Receiver Clocks == 1 etu) */
        delay = 5*16;
    }
    else
    {   /* 22 etus - 11 etu from the start bit of the last received byte * (16 Receiver Clocks == 1 etu) */
        delay = 11*16;
    }
    /* Disable receiver to correctly configure trigger for Global counter */
    EMVSIM_HAL_SetControl(base, kEmvsimCtrlReceiverEnable, false);
    /* Clear Global counter time-out flag */
    EMVSIM_HAL_ClearTransmitStatus(base, kEmvsimGPCNT1Timeout);
    /* Disable counter interrupt */
    EMVSIM_HAL_SetIntMode(base, kEmvsimIntGPCnt1, false);
    /* Set counter value */
    EMVSIM_HAL_SetGPCNTValue(base, 1, delay);
    /* Select the clock for GPCNT */
    EMVSIM_HAL_SetGPCClockSelect(base, 1, kEmvsimGPCRxClock);
    /* Trigger the counter */
    EMVSIM_HAL_SetControl(base, kEmvsimCtrlReceiverEnable, true);
    /* Enable counter interrupt */
    EMVSIM_HAL_SetIntMode(base, kEmvsimIntGPCnt1, true);

    smartcardState->bwtActive = true;
    /* Wait until the Block guard time expires */
    do
    {   /* Wait at least one System Tick timer tick */
        syncStatus = OSA_SemaWait(&smartcardState->txIrqSync, 5);
    }while(syncStatus == kStatus_OSA_Idle);

    /* Check if timer expires successfully */
    if (syncStatus != kStatus_OSA_Success)
    {
        /* Set bwtActive to false in case that Global Timer 1 time-out interrupt didn't occur */
        smartcardState->bwtActive = false;
        /* Disable and clear GPCNT interrupt */
        EMVSIM_HAL_SetIntMode(base, kEmvsimIntGPCnt1, false);
        EMVSIM_HAL_ClearTransmitStatus(base, kEmvsimGPCNT1Timeout);
        EMVSIM_HAL_SetGPCClockSelect(base, 1, kEmvsimGPCClockDisable);
        /* Down counter trigger, and clear any pending counter status flag */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlReceiverEnable, false);
    }

    smartcardState->transState = kSmartcardTransmittingState;

    /* Disable transmitter and receiver */
    EMVSIM_HAL_SetControl(base, kEmvsimCtrlTransmitterEnable, false);
    EMVSIM_HAL_SetControl(base, kEmvsimCtrlReceiverEnable, false);

    smartcardState->isTxBusy = true;

    /* Set the TX pin as output and enable transmitter */
    EMVSIM_HAL_SetControl(base, kEmvsimCtrlTransmitterEnable, true);

    if(!smartcardState->useDMA)
    {
        /* Initialize the module driver state structure. */
        smartcardState->txBuff = txBuff;
        smartcardState->txSize = txSize;

        /* Enable the transmission complete interrupt. The TC bit will
        * set whenever the transmit data is shifted out */
        EMVSIM_HAL_SetIntMode(base, kEmvsimIntTxComplete, true);
    }
    else
    {
        /* Initialize the module driver state structure. */
        smartcardState->txBuff = txBuff;
        smartcardState->txSize = txSize;

        /* Clear the TCF bit to be able to poll this bit at the end of DMA transmission */
        EMVSIM_HAL_ClearTransmitStatus(base, kEmvsimTxComplete);

        /* Enable DMA trigger when transmit data register empty,
        * and receive data register full. */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlTxDmaEnable, true);

#if defined(FSL_FEATURE_EDMA_MODULE_CHANNEL)
        /* Setup source */
        EDMA_HAL_HTCDSetSrcAddr(edmaBaseAddr, edmaChannel, (uint32_t)txBuff);
        EDMA_HAL_HTCDSetSrcOffset(edmaBaseAddr, edmaChannel, 1);
        EDMA_HAL_HTCDSetSrcLastAdjust(edmaBaseAddr, edmaChannel, 0);

        /* Setup destination */
        EDMA_HAL_HTCDSetDestAddr(edmaBaseAddr, edmaChannel, EMVSIM_HAL_GetTxDataRegAddr(base));
        EDMA_HAL_HTCDSetDestOffset(edmaBaseAddr, edmaChannel, 0);
        EDMA_HAL_HTCDSetDestLastAdjust(edmaBaseAddr, edmaChannel, 0);

        /* Setup transfer properties */
        EDMA_HAL_HTCDSetNbytes(edmaBaseAddr, edmaChannel, 1);
        EDMA_HAL_HTCDSetChannelMinorLink(edmaBaseAddr, edmaChannel, 0, false);
        EDMA_HAL_HTCDSetMajorCount(edmaBaseAddr, edmaChannel, smartcardState->txSize);
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
        DMA_HAL_SetDestAddr(dmaBase, chn->channel, EMVSIM_HAL_GetDataRegAddr(base));
        DMA_HAL_SetDestModulo(dmaBase, chn->channel, kDmaModuloDisable);
        DMA_HAL_SetDestTransferSize(dmaBase, chn->channel, kDmaTransfersize8bits);
        DMA_HAL_SetDestIncrementCmd(dmaBase, chn->channel, false);

        DMA_HAL_SetIntCmd(dmaBase, chn->channel, true);

        /* Setup source */
        DMA_HAL_SetSourceAddr(dmaBase, chn->channel, (uint32_t)txBuff);
        DMA_HAL_SetTransferCount(dmaBase, chn->channel, (smartcardState->txSize > 1)?(smartcardState->txSize - 1):1);

        /* Start DMA channel */
        DMA_DRV_StartChannel(chn);
#endif
    }

    return kStatus_SMARTCARD_Success;
}

/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_EMVSIM_DRV_CompleteReceiveData
* Description   : Finish up a receive by completing the process of receiving
* data and disabling the interrupt.
* This is not a public API as it is called from other driver functions.
*
*END**************************************************************************/
static void SMARTCARD_EMVSIM_DRV_CompleteReceiveData(uint32_t instance)
{
    assert(instance < EMVSIM_INSTANCE_COUNT);

    smartcard_state_t * smartcardState = (smartcard_state_t *)g_emvsimStatePtr[instance];
    EMVSIM_Type * base = g_emvsimBase[instance];
#if defined(FSL_FEATURE_EDMA_MODULE_CHANNEL)
    DMA_Type * edmaBaseAddr = VIRTUAL_CHN_TO_EDMA_MODULE_REGBASE(smartcardState->rxDmaState.channel);
    uint32_t edmaChannel = VIRTUAL_CHN_TO_EDMA_CHN(smartcardState->rxDmaState.channel);
#endif
    /* Clear receive status flag */
    EMVSIM_HAL_ClearReceiveStatus(base, kEmvsimRxData);

    if(!smartcardState->useDMA)
    {
        /* Disable receive data full interrupt */
        EMVSIM_HAL_SetIntMode(base, kEmvsimIntRxData, false);
    }
    else
    {
        /* Disable DMA trigger. */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlRxDmaEnable, false);
#if defined(FSL_FEATURE_EDMA_MODULE_CHANNEL)
        /* Disable DMA major loop interrupt */
        EDMA_HAL_HTCDSetIntCmd(edmaBaseAddr, edmaChannel, false);

        /* Stop DMA channel. */
        EDMA_HAL_SetDmaRequestCmd(edmaBaseAddr, (edma_channel_indicator_t)edmaChannel, false);
#elif defined(FSL_FEATURE_DMA_DMAMUX_CHANNELS)
        /* Stop DMA channel. */
        DMA_DRV_StopChannel(&smartcardState->rxDmaState);
#endif

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
        {   /* transfer completed normally */
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
* Function Name : SMARTCARD_EVMSIM_DRV_EdmaTxCallback
* Description   : Callback function to be called from the EDMA ISR after transmit.
* This is not a public interface.
*
*END**************************************************************************/
static void SMARTCARD_EVMSIM_DRV_EdmaTxCallback(void *param, edma_chn_status_t status)
{
    SMARTCARD_EMVSIM_DRV_CompleteSendData((uint32_t)param);
}
#elif defined(FSL_FEATURE_DMA_DMAMUX_CHANNELS)
/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_EMVSIM_DRV_DmaTxCallback
* Description   : Callback function to be called from the DMA ISR after transmit.
* This is not a public interface.
*
*END**************************************************************************/
static void SMARTCARD_EMVSIM_DRV_DmaTxCallback(void *param, dma_channel_status_t status)
{
    SMARTCARD_EMVSIM_DRV_CompleteSendData((uint32_t)param);
}
#endif

/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_EMVSIM_DRV_StartReceiveData
* Description   : Initiate (start) a receive by beginning the process of
* receiving data and enabling the interrupt.
* This is not a public API as it is called from other driver functions.
*
*END**************************************************************************/
static smartcard_status_t SMARTCARD_EMVSIM_DRV_StartReceiveData(uint32_t instance,
                                                                uint8_t * rxBuff,
                                                                uint32_t rxSize)
{
    assert(instance < EMVSIM_INSTANCE_COUNT);
    assert(rxBuff);

    smartcard_state_t * smartcardState = (smartcard_state_t *)g_emvsimStatePtr[instance];
    EMVSIM_Type * base = g_emvsimBase[instance];
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

    /* Enable BWT Timer interrupt to occur */
    EMVSIM_HAL_SetIntMode(base, kEmvsimIntBWTErr, true);
    /* Clear receive status flag */
    EMVSIM_HAL_ClearReceiveStatus(base, kEmvsimRxData);
    /* Disable transmitter */
    EMVSIM_HAL_SetControl(base, kEmvsimCtrlTransmitterEnable, false);

    /* Initialize the module driver state struct with the buffer and byte count data */
    smartcardState->rxBuff = rxBuff;
    smartcardState->rxSize = rxSize;

    /* Enable receiver and switch to receive direction */
    EMVSIM_HAL_SetControl(base, kEmvsimCtrlReceiverEnable, true);

    if(!smartcardState->useDMA)
    {
        /* Enable the receive data full interrupt */
        EMVSIM_HAL_SetIntMode(base, kEmvsimIntRxData, true);
    }
    else
    {
        /* Enable receiver to trigger DMA */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlRxDmaEnable, true);

#if defined(FSL_FEATURE_EDMA_MODULE_CHANNEL)
        /* Setup destination */
        EDMA_HAL_HTCDSetDestAddr(edmaBaseAddr, edmaChannel, (uint32_t)rxBuff);
        EDMA_HAL_HTCDSetDestOffset(edmaBaseAddr, edmaChannel, 1);
        EDMA_HAL_HTCDSetDestLastAdjust(edmaBaseAddr, edmaChannel, 0);

        /* Setup source */
        EDMA_HAL_HTCDSetSrcAddr(edmaBaseAddr, edmaChannel, EMVSIM_HAL_GetRxDataRegAddr(base));
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
        DMA_HAL_SetSourceAddr(dmaBase, chn->channel, EMVSIM_HAL_GetRxDataRegAddr(base));
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
* Function Name : SMARTCARD_EMVSIM_DRV_SetTransferType
* Description   : Sets up the EMVSIM hardware for T=0 or T=1 protocol data exchange
* and initialize timer values.
* This is not a public API as it is called from other driver functions.
*
*END**************************************************************************/
static void SMARTCARD_EMVSIM_DRV_SetTransferType(uint32_t instance, smartcard_control_t control)
{
    assert(instance < EMVSIM_INSTANCE_COUNT);
    assert((control != kSmartcardSetupATRMode) || \
        (control != kSmartcardSetupT0Mode) || \
        (control != kSmartcardSetupT1Mode));

    uint16_t temp16 = 0;
    uint32_t bwiVal = 0;
    EMVSIM_Type * base = g_emvsimBase[instance];
    uint8_t tdt = 0;
    smartcard_state_t * smartcardStatePtr = (smartcard_state_t *)g_emvsimStatePtr[instance];
    if(control == kSmartcardSetupATRMode)
    {
        /* Disable receiver at first if it's not */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlReceiverEnable, false);
        /* Set default values as per EMV specification */
        smartcardStatePtr->cardParams.Fi = 372;
        smartcardStatePtr->cardParams.Di = 1;
        smartcardStatePtr->cardParams.currentD = 1;
        smartcardStatePtr->cardParams.WI = 0x0A;
        smartcardStatePtr->cardParams.GTN = 0x00;

        /* Set default baudrate/ETU time based on EMV parameters and card clock */
        EMVSIM_HAL_SetBaudrateDivisor(base, (smartcardStatePtr->cardParams.Fi/smartcardStatePtr->cardParams.currentD));

        /* EMV expectation: WWT = (960 x D x WI) + (D x 480)
        * EMVSIM formula: BWT_VAL[15:0] = CWT_VAL[15:0]
        */
        temp16 = (960 * smartcardStatePtr->cardParams.currentD * smartcardStatePtr->cardParams.WI) + \
            (smartcardStatePtr->cardParams.currentD * 480) + WWT_ADJUSTMENT;
        EMVSIM_HAL_SetCharacterWaitTime(base, temp16);
        EMVSIM_HAL_SetBlockWaitTime(base, temp16);

        /* Set Extended Guard Timer value
        * EMV expectation: GT = GTN not equal to 255 -> 12 + GTN
        * = GTN equal to 255 -> 12
        * EMVSIM formula: same as above
        */
        EMVSIM_HAL_SetAdditionalTransmitterGuardTime(base, smartcardStatePtr->cardParams.GTN);

        /* Setup for single wire ISO7816 mode */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlRcvr11ModeEnable, (bool)kEmvsimCharacter12EtuMode);

        /* Set transport protocol type to T=0 */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlXmtCrcOrLrcEnable, false);
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlLrcEnable, false);

        /* Disable initial character detection */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlinitialCharacterMode, true);

        /*
        * Disable Automatic Nack generation for parity errors
        * in received messages (default during ATR reception)
        */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlANACKEnable, false);

        /* Disable Nack on overflow interrupt */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlONACKEnable, false);

        /*Setting Rx threshld so that an interrupt is generated when a NACK is
        sent either due to parity error or wrong INIT char*/
        EMVSIM_HAL_SetReceiverNackThreshold(base, 0);
        EMVSIM_HAL_SetReceiverDataThreshold(base, 1);

        /* Setting up Tx NACK threshold */
        EMVSIM_HAL_SetTransmitterNackThreshold(base, EMV_TX_NACK_THRESHOLD);
        tdt = (EMVSIM_HAL_GetTxFifoSize(base) < 0x0FU)?EMVSIM_HAL_GetTxFifoSize(base):0x0FU;
        EMVSIM_HAL_SetTransmitterDataThreshold(base, tdt);

        /* Clear all pending interrupts */
        EMVSIM_HAL_ClearReceiveStatus(base, kEmvsimRxAllStatus);

        /* Enable Tx NACK threshold interrupt to occur */
        EMVSIM_HAL_SetIntMode(base, kEmvsimIntTxNackThresold, true);

        /* Set transport type to T=0 in smartcard state structure */
        smartcardStatePtr->tType = kSmartcardT0Transport;
    }
    else if(control == kSmartcardSetupT0Mode)
    {
        /* Disable receiver at first if it's not */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlReceiverEnable, false);
        /* Disable T=0 mode counters 1st */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlCWTEnable, false);
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlBWTEnable, false);

        /* EMV expectation: WWT = (960 x D x WI) + (D x 480)
        * EMVSIM formula: BWT_VAL[15:0] = CWT_VAL[15:0]
        */
        temp16 = (960 * smartcardStatePtr->cardParams.currentD * smartcardStatePtr->cardParams.WI) + \
            (smartcardStatePtr->cardParams.currentD * 480) + WWT_ADJUSTMENT;
        EMVSIM_HAL_SetCharacterWaitTime(base, temp16);
        EMVSIM_HAL_SetBlockWaitTime(base, temp16);

        /* Set Extended Guard Timer value
        * EMV expectation: GT = GTN not equal to 255 -> 12 + GTN
        * = GTN equal to 255 -> 12
        * EMVSIM formula: same as above for range [0:254]
        */
        EMVSIM_HAL_SetAdditionalTransmitterGuardTime(base, smartcardStatePtr->cardParams.GTN);

        /* Setup for single wire ISO7816 mode */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlRcvr11ModeEnable, (bool)kEmvsimCharacter12EtuMode);

        /* Set transport protocol type to T=0 */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlXmtCrcOrLrcEnable, false);
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlLrcEnable, false);

        /* Disable initial character detection */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlinitialCharacterMode, false);

        /* Enable Nack on error interrupt */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlANACKEnable, true);

        /* Enable Nack on overflow interrupt */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlONACKEnable, true);

        /*Setting Rx threshld so that an interrupt is generated when a NACK is
        sent either due to parity error or wrong INIT char*/
        EMVSIM_HAL_SetReceiverNackThreshold(base, EMV_RX_NACK_THRESHOLD);
        EMVSIM_HAL_SetReceiverDataThreshold(base, 1);

        /* Setting up Tx NACK threshold */
        EMVSIM_HAL_SetTransmitterNackThreshold(base, EMV_TX_NACK_THRESHOLD);
        tdt = (EMVSIM_HAL_GetTxFifoSize(base) < 0x0FU)?EMVSIM_HAL_GetTxFifoSize(base):0x0FU;
        EMVSIM_HAL_SetTransmitterDataThreshold(base, tdt);

        /* Enable Tx NACK threshold interrupt to occur */
        EMVSIM_HAL_SetIntMode(base, kEmvsimIntTxNackThresold, true);

        /* Enable T=0 mode counters */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlCWTEnable, true);
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlBWTEnable, true);

        /* Set transport type to T=0 in smartcard state structure */
        smartcardStatePtr->tType = kSmartcardT0Transport;
    }
    else
    {
        /* Disable T=1 mode counters 1st */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlCWTEnable, false);
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlBWTEnable, false);

        /* Calculate and set Block Wait Timer (BWT) value */
        /*
        * EMV expectation: BWT = 11 + (2^BWI x 960 x D) + (D x 960)
        = 11 + (2^BWI + 1) x 960 x D
        * EMVSIM formula: BWT = Same
        */
        bwiVal = 11 + (((1 << smartcardStatePtr->cardParams.BWI) + 1) * 960 * smartcardStatePtr->cardParams.currentD);
        EMVSIM_HAL_SetBlockWaitTime(base, bwiVal);

        /* Calculate and set Character Wait Timer (CWT) value */
        /*
        * EMV expectation: CWT = ((2^CWI + 11) + 4)
        * EMVSIM formula: CWT = Same
        */
        if(smartcardStatePtr->cardParams.currentD == 1)
        {
            temp16 = (1 << smartcardStatePtr->cardParams.CWI) + 15;
        }
        else
        {
            temp16 = (1 << smartcardStatePtr->cardParams.CWI) + 15 + CWT_ADJUSTMENT;
        }
        EMVSIM_HAL_SetCharacterWaitTime(base, temp16);    /* EMV = 15, ISO = 11*/

        /*
        * EMV expectation: BGT = 22
        * EMVSIM formula: BGT = Same
        */
        smartcardStatePtr->cardParams.BGI = 22;
        EMVSIM_HAL_SetBlockGuardTime(base, smartcardStatePtr->cardParams.BGI);

        /* Set Extended Guard Timer value
        * EMV expectation: GT = GTN not equal to 255 -> 12 + GTN
        = GTN equal to 255 -> 11
        * EMVSIM formula: same as above
        */
        EMVSIM_HAL_SetAdditionalTransmitterGuardTime(base, smartcardStatePtr->cardParams.GTN);

        /* Setup for single wire ISO7816 mode */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlRcvr11ModeEnable, (bool)kEmvsimCharacter11EtuMode);

        /* Disable Nack on error interrupt */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlANACKEnable, false);

        /* Disable Nack on overflow interrupt */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlONACKEnable, false);

        /* Setting Rx threshld */
        EMVSIM_HAL_SetReceiverDataThreshold(base, 1);

        /* Setting up Tx threshold */
        tdt = (EMVSIM_HAL_GetTxFifoSize(base) < 0x0FU)?EMVSIM_HAL_GetTxFifoSize(base):0x0FU;
        EMVSIM_HAL_SetTransmitterDataThreshold(base, tdt);

        /* Set transport protocol type to T=1 */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlXmtCrcOrLrcEnable, false);
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlLrcEnable, false);

        /* Enable T=0 mode counters */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlCWTEnable, true);
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlBWTEnable, true);

        /* Set transport type to T=1 in smartcard state structure */
        smartcardStatePtr->tType = kSmartcardT1Transport;
    }
}

/*FUNCTION**********************************************************************
*
* Function Name : SMARTCARD_EMVSIM_DRV_Control
* Description   : Cotrols different driver settings as per caller request.
*
*END**************************************************************************/
smartcard_status_t SMARTCARD_EMVSIM_DRV_Control(uint32_t instance, smartcard_control_t control, void *controlBuff)
{
    assert(instance < EMVSIM_INSTANCE_COUNT);

    EMVSIM_Type * base = g_emvsimBase[instance];
    smartcard_state_t * smartcardState = (smartcard_state_t *)g_emvsimStatePtr[instance];
    uint32_t temp32 = 0;

    switch(control)
    {
    case kSmartcardEnableADT:
        /*
         * Do nothing, ADT counter has been loaded and started after reset
         * and during starting TS delay counter only. This is because, once
         * TS counter has been trigerred with RCV_EN down-up, we should not
         * trigger again after TS is received(to avoid missing next character to
         * TS. Rather, after TS is received, the ATR duration counter should just
         * be restarted w/o re-trigerring the counter.
         */

        break;
    case kSmartcardDisableADT:
        /* Stop ADT specific counter and it's interrupt to occur */
        EMVSIM_HAL_SetGPCClockSelect(base, 1, kEmvsimGPCClockDisable);
        EMVSIM_HAL_ClearTransmitStatus(base, kEmvsimGPCNT1Timeout);
        EMVSIM_HAL_SetIntMode(base, kEmvsimIntGPCnt1, false);

        break;

    case kSmartcardEnableGTV:
        /* Enable GTV specific interrupt */
        EMVSIM_HAL_SetIntMode(base, kEmvsimIntBGTErr, true);
        break;

    case kSmartcardDisableGTV:
        /* Disable GTV specific interrupt */
        EMVSIM_HAL_SetIntMode(base, kEmvsimIntBGTErr, false);
        break;

    case kSmartcardResetWWT:
        /* Reset WWT Timer */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlCWTEnable, false);
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlBWTEnable, false);
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlCWTEnable, true);
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlBWTEnable, true);
        break;

    case kSmartcardEnableWWT:
        /* BGT must be masked */
        EMVSIM_HAL_SetIntMode(base, kEmvsimIntBGTErr, false);
        /* Enable WWT Timer interrupt to occur */
        EMVSIM_HAL_SetIntMode(base, kEmvsimIntCWTErr, true);
        EMVSIM_HAL_SetIntMode(base, kEmvsimIntBWTErr, true);
        break;

    case kSmartcardDisableWWT:
        /* Disable WWT Timer interrupt to occur */
        EMVSIM_HAL_SetIntMode(base, kEmvsimIntCWTErr, false);
        EMVSIM_HAL_SetIntMode(base, kEmvsimIntBWTErr, false);
        break;

    case kSmartcardResetCWT:
        /* Reset CWT Timer */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlCWTEnable, false);
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlCWTEnable, true);
        break;

    case kSmartcardEnableCWT:
        /* Enable CWT Timer interrupt to occur */
        EMVSIM_HAL_SetIntMode(base, kEmvsimIntCWTErr, true);
        break;

    case kSmartcardDisableCWT:
        /* CWT counter is for receive mode only */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlCWTEnable, false);

        /* Disable CWT Timer interrupt to occur */
        EMVSIM_HAL_SetIntMode(base, kEmvsimIntCWTErr, false);
        break;

    case kSmartcardResetBWT:
        /* Reset BWT Timer */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlBWTEnable, false);
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlBWTEnable, true);
        break;

    case kSmartcardEnableBWT:
        /* Enable BWT Timer interrupt to occur */
        EMVSIM_HAL_SetIntMode(base, kEmvsimIntBWTErr, true);
        break;

    case kSmartcardDisableBWT:
        /* Disable BWT Timer interrupt to occur */
        EMVSIM_HAL_SetIntMode(base, kEmvsimIntBWTErr, false);
        break;

    case kSmartcardEnableInitDetect:
        /*Clear all ISO7816 interrupt flags */
        EMVSIM_HAL_ClearReceiveStatus(base, kEmvsimRxAllStatus);

        /* Enable initial character detection : hardware method */
        smartcardState->transState = kSmartcardWaitingForTSState;
        EMVSIM_HAL_SetIntMode(base, kEmvsimIntRxData, true);
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlReceiverEnable, true);

        /* Enable initial character detection */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlinitialCharacterMode, true);

        break;

    case kSmartcardEnableAnack:
        /* Enable Nack-on-error interrupt to occur */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlANACKEnable, true);
        break;

    case kSmartcardDisableAnack:
        /* Disable Nack-on-error interrupt to occur */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlANACKEnable, false);
        break;

    case kSmartcardConfigureBaudrate:
        /* Set default baudrate/ETU time based on EMV parameters and card clock */
        EMVSIM_HAL_SetBaudrateDivisor(base, (smartcardState->cardParams.Fi/smartcardState->cardParams.currentD));

        break;

    case kSmartcardSetupATRMode:
        /* Set in default ATR mode */
        SMARTCARD_EMVSIM_DRV_SetTransferType(instance, kSmartcardSetupATRMode);
        break;

    case kSmartcardSetupT0Mode:
        /* Set transport protocol type to T=0 */
        SMARTCARD_EMVSIM_DRV_SetTransferType(instance, kSmartcardSetupT0Mode);
        break;

    case kSmartcardSetupT1Mode:
        /* Set transport protocol type to T=1 */
        SMARTCARD_EMVSIM_DRV_SetTransferType(instance, kSmartcardSetupT1Mode);
        break;

    case kSmartcardEnableReceiverMode:
        /* Enable receiver mode and switch to receive direction */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlReceiverEnable, true);
        break;

    case kSmartcardDisableReceiverMode:
        /* Disable receiver */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlReceiverEnable, false);
        break;

    case kSmartcardEnableTransmitterMode:
        /* Enable transmitter mode and switch to transmit direction */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlTransmitterEnable, true);
        break;

    case kSmartcardDisableTransmitterMode:
        /* Disable transmitter */
        EMVSIM_HAL_SetControl(base, kEmvsimCtrlTransmitterEnable, false);
        break;

    case kSmartcardResetWaitTimeMultiplier:
        /* Reset Wait Timer Multiplier */
        /*
        * EMV Formula : WTX x (11 + ((2^BWI + 1) x 960 x D))
        */
        temp32 = (*((uint8_t *)controlBuff)) *
            (11 + (((1 << smartcardState->cardParams.BWI) + 1) * 960 * smartcardState->cardParams.currentD));

        EMVSIM_HAL_SetBlockWaitTime(base, temp32);

        /* Set flag to smartcard state accordingly */
        if(*((uint8_t *)controlBuff) > 1)
        {
            smartcardState->wtxRequested = true;
        }
        else
        {
            smartcardState->wtxRequested = false;
        }
        break;

    default:
        break;
    }

    return kStatus_SMARTCARD_Success;
}
/*******************************************************************************
* EOF
******************************************************************************/

