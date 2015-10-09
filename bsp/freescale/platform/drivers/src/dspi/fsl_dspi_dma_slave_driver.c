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

#include <string.h>
#include <assert.h>
#include "fsl_dspi_dma_slave_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"

#if FSL_FEATURE_SOC_DSPI_COUNT

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*!
 * @brief Flags of DSPI slave event.
 *
 * DSPI event used to notify user that it finishes the task.
 */
typedef enum _dspi_dma_event_flags {
    kDspiDmaTransferDone = 0x01,         /*!< Transferring done flag */
} dspi_dma_event_flag_t;

/*******************************************************************************
 * Variables
 ******************************************************************************/

/* Pointer to runtime state structure.*/
extern void * g_dspiStatePtr[SPI_INSTANCE_COUNT];

/* Table of SPI FIFO sizes per instance. */
extern const uint32_t g_dspiFifoSize[SPI_INSTANCE_COUNT];

/* For storing DMA intermediate buffers between the source buffer and TX FIFO */
static uint32_t s_dataToSend; /* Word to send, if no send buffer, this variable is used
                                 as the word to send, which should be initialized to 0. Needs
                                 to be static and stored in data section as this variable
                                 address is the source address if no source buffer.  */
static uint32_t s_rxBuffIfNull; /* If no receive buffer provided, direct rx DMA channel to this
                                  destination */

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * @brief DSPI receive done callback function
 * @details This function is called when receiving is done.
 *
 * @param param pointer to parameter
 * @param status current status of DMA channel
 */
static void DSPI_DRV_DmaRxCallback(void *param, dma_channel_status_t status);

/*!
 * @brief DSPI transmit done callback function
 * @details This function is called when transmitting is done.
 *
 * @param param pointer to parameter
 * @param status current status of DMA channel
 */
static void DSPI_DRV_DmaTxCallback(void *param, dma_channel_status_t status);

/*!
 * @brief Finish the current DSPI transfer
 * @details This function stop the DSPI transfer
 *
 * @param instance The instance of DSPI hardware
 */
static void DSPI_DRV_DmaCompleteTransfer(uint32_t instance);

/*!
 * @brief Start slave transferring.
 * @details This function make starting the transfer.
 *
 * @param instance The instance number of DSPI peripheral
 * @param sendBuffer The pointer to transmit buffer
 * @param receiveBuffer The pointer to receive buffer
 * @param transferByteCount The transfer size
 */
static void DSPI_DRV_DmaSlaveStartTransfer(uint32_t instance,
                                            const uint8_t *sendBuffer,
                                            uint8_t *receiveBuffer,
                                            uint32_t transferByteCount);

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_DmaSlaveInit
 * Description   : Initialize a DSPI slave instance.
 * Un-gate DSPI's clock, setup the default value and initializes the required
 * resources.
 *
 *END**************************************************************************/
dspi_status_t DSPI_DRV_DmaSlaveInit(uint32_t instance,
                                     dspi_dma_slave_state_t * dspiState,
                                     const dspi_dma_slave_user_config_t * slaveConfig)
{
    dspi_status_t result = kStatus_DSPI_Success;
    dma_request_source_t dspiTxDmaRequest = kDmaRequestMux0Disable;
    dma_request_source_t dspiRxDmaRequest = kDmaRequestMux0Disable;
    SPI_Type *base = g_dspiBase[instance];

    /* Check parameter pointer is not NULL */
    if ((dspiState == NULL) || (slaveConfig == NULL))
    {
        return kStatus_DSPI_InvalidParameter;
    }

    /* Check DSPI slave instance is already initialized */
    if (g_dspiStatePtr[instance])
    {
        return kStatus_DSPI_Initialized;
    }

    /* Check if bits/frame is 3 bytes, DMA driver does not support 3bytes copy at a time. */
    if ((16 < slaveConfig->dataConfig.bitsPerFrame) && (slaveConfig->dataConfig.bitsPerFrame <= 24))
    {
        return kStatus_DSPI_OutOfRange;
    }

    /* Check bits/frame number */
    if (slaveConfig->dataConfig.bitsPerFrame > 32)
    {
        return kStatus_DSPI_OutOfRange;
    }

    /* Clear the run-time state struct for this instance. */
    memset(dspiState, 0, sizeof(* dspiState));

    /* Initial default value slave state structure */
    dspiState->status = kStatus_DSPI_Success;
    dspiState->errorCount = 0;
    dspiState->dummyPattern = slaveConfig->dummyPattern;
    dspiState->remainingSendByteCount = 0;
    dspiState->remainingReceiveByteCount = 0;
    dspiState->isTransferInProgress = false;
    dspiState->extraReceiveByte = 0;

    if (kStatus_OSA_Success != OSA_EventCreate(&dspiState->event, kEventAutoClear))
    {
        /* Create event error */
        dspiState->status = kStatus_DSPI_Error;
        return kStatus_DSPI_Error;
    }

    /* configure the run-time state struct with the nubmer of bits/frame */
    dspiState->bitsPerFrame = slaveConfig->dataConfig.bitsPerFrame;

    /* Enable clock for DSPI */
    CLOCK_SYS_EnableSpiClock(instance);

    /* Reset the DSPI module, which also disables the DSPI module */
    DSPI_HAL_Init(base);

    /* Set to slave mode. */
    DSPI_HAL_SetMasterSlaveMode(base, kDspiSlave);

    /* Set slave data format */
    result = DSPI_HAL_SetDataFormat(base, kDspiCtar0, &slaveConfig->dataConfig);

    /* Enable fifo operation (regardless of FIFO depth) */
    DSPI_HAL_SetFifoCmd(base, true, true);

    /* flush the fifos */
    DSPI_HAL_SetFlushFifoCmd(base, true, true);

    switch (instance)
    {
        case 0:
            /* SPI0 */
#if FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(0)
            dspiRxDmaRequest = kDmaRequestMux0SPI0Rx;
            dspiTxDmaRequest = kDmaRequestMux0SPI0Tx;
#else
            dspiRxDmaRequest = kDmaRequestMux0SPI0;
            dspiTxDmaRequest = kDmaRequestMux0Disable;
#endif
            break;
#if (SPI_INSTANCE_COUNT > 1)
        case 1:
            /* SPI1 */
#if FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(1)
            dspiRxDmaRequest = kDmaRequestMux0SPI1Rx;
            dspiTxDmaRequest = kDmaRequestMux0SPI1Tx;
#else
            dspiRxDmaRequest = kDmaRequestMux0SPI1;
            dspiTxDmaRequest = kDmaRequestMux0Disable;
#endif
            break;
#endif
#if (SPI_INSTANCE_COUNT > 2)
        case 2:
            /* SPI2 */
#if FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(2)
            dspiRxDmaRequest = kDmaRequestMux0SPI2Rx;
            dspiTxDmaRequest = kDmaRequestMux0SPI2Tx;
#else
            dspiRxDmaRequest = kDmaRequestMux0SPI2;
            dspiTxDmaRequest = kDmaRequestMux0Disable;
#endif
            break;
#endif
        default :
            return kStatus_DSPI_InvalidInstanceNumber;
    }

    /* This channel transfers data from RX FIFO to receiveBuffer */
    if (kDmaInvalidChannel == DMA_DRV_RequestChannel(kDmaAnyChannel,
                                                      dspiRxDmaRequest,
                                                      &dspiState->dmaRxChannel))
    {
        dspiState->status = kStatus_DSPI_Error;
        return kStatus_DSPI_DMAChannelInvalid;
    }

    /* This channel transfers data from transmitBuffer to TX FIFO */
    if (kDmaInvalidChannel == DMA_DRV_RequestChannel(kDmaAnyChannel,
                                                      dspiTxDmaRequest,
                                                      &dspiState->dmaTxChannel))
    {
        dspiState->status = kStatus_DSPI_Error;
        return kStatus_DSPI_DMAChannelInvalid;
    }

    /* Configure IRQ state structure, so irq handler can point to the correct state structure */
    g_dspiStatePtr[instance] = dspiState;

    /* Enable the interrupt */
    INT_SYS_EnableIRQ(g_dspiIrqId[instance]);

    /* DSPI module enable */
    DSPI_HAL_Enable(base);

    return result;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_DmaSlaveDeinit
 * Description   : Shutdown a DSPI instance.
 * Resets the DSPI peripheral, disables the interrupt to the core, and gates its clock.
 *
 *END**************************************************************************/
dspi_status_t DSPI_DRV_DmaSlaveDeinit(uint32_t instance)
{
    SPI_Type *base = g_dspiBase[instance];
    dspi_dma_slave_state_t * dspiState = (dspi_dma_slave_state_t *)g_dspiStatePtr[instance];

    /* Validate function parameters */
    assert(instance < SPI_INSTANCE_COUNT);

    if (!dspiState)
    {
        return kStatus_DSPI_NonInit;
    }

    /* disable the interrupt */
    INT_SYS_DisableIRQ(g_dspiIrqId[instance]);

    /* Stop the transfer process in the slave */
    DSPI_HAL_StopTransfer(base);

    /* Wait until the DSPI run status signals that is has halted before shutting down the module
     * and before gating off the DSPI clock source.  Otherwise, if the DSPI is shut down before
     * it has halted it's internal processes, it may be left in an unknown state.
     */
    /* Note that if the master slave select is still asserted, the run status will never clear.
     * Hence, ensure before shutting down the slave that the master has de-asserted the slave
     * select signal (it should be high if slave select active low or it should be low if
     * slave select is active high).
     */
    while((DSPI_HAL_GetStatusFlag(base, kDspiTxAndRxStatus))) { }

    /* Restore the module to defaults then power it down. This also disables the DSPI module. */
    DSPI_HAL_Init(base);

    /* Gate the clock for DSPI. */
    CLOCK_SYS_DisableSpiClock(instance);

    /* Destroy event */
    OSA_EventDestroy(&dspiState->event);

    DMA_DRV_FreeChannel(&dspiState->dmaTxChannel);
    DMA_DRV_FreeChannel(&dspiState->dmaRxChannel);

    dspiState->status = kStatus_DSPI_NonInit;

    /* Clear state pointer. */
    g_dspiStatePtr[instance] = NULL;

    return kStatus_DSPI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_DmaSlaveStartTransfer
 * Description   : Starts transfer data on SPI bus using DMA and non-blocking call
 * Start DSPI transfering, update transmit/receive information into slave state structure
 *
 *END**************************************************************************/
static void DSPI_DRV_DmaSlaveStartTransfer(uint32_t instance,
                                           const uint8_t *sendBuffer,
                                           uint8_t *receiveBuffer,
                                           uint32_t transferByteCount)
{
    void * param;
    SPI_Type *base = g_dspiBase[instance];
    dspi_dma_slave_state_t * dspiState = (dspi_dma_slave_state_t *)g_dspiStatePtr[instance];
    uint8_t nBytes = 1;
    uint32_t txTransferByteCnt = 0;
    uint32_t rxTransferByteCnt = 0;
    uint32_t sendData = 0;

    /* Calculate the transfer size on bits/frame */
    if (dspiState->bitsPerFrame <= 8)
    {
        nBytes = 1U;
    }
    else if (dspiState->bitsPerFrame <= 16)
    {
        nBytes = 2U;
    }
    else
    {
        nBytes = 4U;
    }

    /* Set dataToSend variable to dummy pattern */
    s_dataToSend = dspiState->dummyPattern;

    /* Stop the transfer first */
    DSPI_HAL_StopTransfer(base);

    /* Reset the transfer counter to 0. */
    DSPI_HAL_PresetTransferCount(base, 0);

    /* flush the fifos */
    DSPI_HAL_SetFlushFifoCmd(base, true, true);

    /* Clear DSPI flags */
    DSPI_HAL_ClearStatusFlag(base, kDspiTxComplete);
    DSPI_HAL_ClearStatusFlag(base, kDspiTxAndRxStatus);
    DSPI_HAL_ClearStatusFlag(base, kDspiEndOfQueue);
    DSPI_HAL_ClearStatusFlag(base, kDspiTxFifoUnderflow);
    DSPI_HAL_ClearStatusFlag(base, kDspiTxFifoFillRequest);
    DSPI_HAL_ClearStatusFlag(base, kDspiRxFifoOverflow);
    DSPI_HAL_ClearStatusFlag(base, kDspiRxFifoDrainRequest);

    /* Start DSPI transfers, set to running state */
    DSPI_HAL_StartTransfer(base);
    /* Wait util TFFF set */
    while(!DSPI_HAL_GetStatusFlag(base,kDspiTxFifoFillRequest))
    {}
    param = (void *)(instance);     /* For DMA callback, set "param" as the SPI instance number */
    /* Firstly, fill one TX FIFO register to ensure the data will be transmitted to master. */
    if (sendBuffer)
    {
        if (nBytes == 1)
        {
            sendData = (uint32_t)*sendBuffer;
            sendBuffer ++;
        }
        else if (nBytes == 2)
        {
            sendData = (uint32_t)*sendBuffer;
            sendBuffer ++;
            sendData |= (uint32_t)(*sendBuffer) << 8;
            sendBuffer++;
        }
        else
        {
            sendData = (uint32_t)*sendBuffer;
            sendBuffer++;
            sendData |= (uint32_t)(*sendBuffer) << 8;
            sendBuffer++;
            sendData |= (uint32_t)(*sendBuffer) << 16;
            sendBuffer++;
            sendData |= (uint32_t)(*sendBuffer) << 24;
            sendBuffer++;
        }
    }
    else
    {
        sendData = s_dataToSend;
    }
    /* Write one transmit FIFO first, it ensure the slave responses ASAP */
    DSPI_HAL_WriteDataSlavemode(base, sendData);
    /* Clear TFFF flag */
    DSPI_HAL_ClearStatusFlag(base, kDspiTxFifoFillRequest);

    /* Calculate number of byte to transmit & receive */
    if ((nBytes > 1) && ((transferByteCount & (uint32_t)(nBytes - 1)) != 0))
    {
        rxTransferByteCnt = (transferByteCount/nBytes) * nBytes;
        dspiState->extraReceiveByte = transferByteCount - rxTransferByteCnt;
        /* Update remaining send byte count */
        dspiState->remainingSendByteCount = (transferByteCount/nBytes + 1) * nBytes;
    }
    else
    {
        dspiState->extraReceiveByte = 0;
        rxTransferByteCnt = transferByteCount;
        /* Update remaining send byte count */
        dspiState->remainingSendByteCount = transferByteCount;
    }
    txTransferByteCnt = rxTransferByteCnt;

    /* Update remaining receive byte count */
    dspiState->remainingReceiveByteCount = rxTransferByteCnt;

    /* Configure for transmit */
    /* Store send buffer */
    dspiState->sendBuffer = sendBuffer;

    if (txTransferByteCnt)
    {
        if (sendBuffer)
        {
            /* Set up this channel's control which includes enabling the DMA interrupt */
            DMA_DRV_ConfigTransfer(&dspiState->dmaTxChannel, kDmaMemoryToPeripheral,
                                   nBytes, (uint32_t)(sendBuffer),
                                   DSPI_HAL_GetSlavePushrRegAddr(base),
                                   (uint32_t)(txTransferByteCnt));
            /* Source is one byte size */
            DMA_DRV_SetSourceTransferSize(&dspiState->dmaTxChannel, 1U);
        }
        else
        {
            /* Source address is static dummy data */
            DMA_DRV_ConfigTransfer(&dspiState->dmaTxChannel, kDmaPeripheralToPeripheral,
                                   nBytes, (uint32_t)(&s_dataToSend),
                                   DSPI_HAL_GetSlavePushrRegAddr(base),
                                   (uint32_t)(txTransferByteCnt));
        }
    }

    /* Configure for receive */
    dspiState->receiveBuffer = receiveBuffer;
    if ((!receiveBuffer) && (rxTransferByteCnt))
    {
        /* Setup DMA for fill the received data into temp variable */
        DMA_DRV_ConfigTransfer(&dspiState->dmaRxChannel,
                               kDmaPeripheralToPeripheral,
                               nBytes, DSPI_HAL_GetPoprRegAddr(base), /* src is data register */
                               (uint32_t)(&s_rxBuffIfNull), /* dest is temporary location */
                               (uint32_t)(rxTransferByteCnt));
    }
    else if (!rxTransferByteCnt)
    {
        /* Setup DMA for fill received data into temp variable, this only run 1 time due to get extra byte */
        DMA_DRV_ConfigTransfer(&dspiState->dmaRxChannel,
                               kDmaPeripheralToPeripheral,
                               nBytes, DSPI_HAL_GetPoprRegAddr(base), /* src is data register */
                               (uint32_t)(&s_rxBuffIfNull), /* dest is temporary location */
                               (uint32_t)(nBytes));
    }
    else
    {
        /* Set up this channel's control which includes enabling the DMA interrupt */
        DMA_DRV_ConfigTransfer(&dspiState->dmaRxChannel,
                               kDmaPeripheralToMemory,
                               nBytes, DSPI_HAL_GetPoprRegAddr(base), /* src is data register */
                               (uint32_t)(receiveBuffer), /* dest is rx buffer */
                               (uint32_t)(rxTransferByteCnt));
        /* Destination is one byte */
        DMA_DRV_SetDestTransferSize(&dspiState->dmaRxChannel, 1U);
    }

    /* Register callback for DMA interrupt */
    DMA_DRV_RegisterCallback(&dspiState->dmaRxChannel, DSPI_DRV_DmaRxCallback, param);

    /* Enable the Receive FIFO Drain Request as a DMA request */
    DSPI_HAL_SetRxFifoDrainDmaIntMode(base, kDspiGenerateDmaReq, true);

    /* Enable the DMA peripheral request */
    DMA_DRV_StartChannel(&dspiState->dmaRxChannel);

    if (txTransferByteCnt)
    {
        /* For DSPI instances with separate RX/TX DMA requests, we'll use the TX DMA request to
         * trigger the TX DMA channel hence we'll enable the TX channel DMA request.
         */
        if (FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(instance))
        {
            /* Set up DMA callback */
            /* Due to MISRA 11.1 rule:
             * Conversions shall not be performed between a pointer to a function
             * and any type other than an integral type.
             * We first have to typecast the callback function pointer as a uint32_t before typecasting
             * as a void pointer.
             */
            DMA_DRV_RegisterCallback(&dspiState->dmaTxChannel, DSPI_DRV_DmaTxCallback, param);

            /* Enable TFFF request in the DSPI module */
            DSPI_HAL_SetTxFifoFillDmaIntMode(base, kDspiGenerateDmaReq, true);

            /* Start DMA tx channel */
            DMA_DRV_StartChannel(&dspiState->dmaTxChannel);
        }
        /* For DSPI instances with shared RX/TX DMA requests, we'll use the RX DMA request to
         * trigger ongoing transfers that will link to the TX DMA channel from the RX DMA channel.
         * So, we'll disable the TX channel DMA request and then we'll have to manually start the
         * TX DMA channel to get the tranfer process started, where the RX DMA channel will take care
         * of the ongoing transfers from there.
         */
        else /* For shared RX/TX DMA requests */
        {
            dma_channel_link_config_t linkConfig;
            linkConfig.linkType = kDmaChannelLinkChan1;
            linkConfig.channel1 = dspiState->dmaTxChannel.channel;
            linkConfig.channel2 = 0;

            /* Disable TFFF request in the DSPI module */
            DSPI_HAL_SetTxFifoFillDmaIntMode(base, kDspiGenerateDmaReq, false);

            /* Configure Tx DMA channel linked to Rx DMA channel, and will be trigger by Rx DMA channel */
            DMA_DRV_ConfigChanLink(&dspiState->dmaRxChannel, &linkConfig);
        }
    }

    /* Update state */
    dspiState->isTransferInProgress = true;
    dspiState->status = kStatus_DSPI_Busy;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_DmaSlaveAbortTransfer
 * Description   : Abort tranfer
 * Abort data transfer, using after function DSPI_DRV_DmaSlaveTransfer() to abort
 * transfering data.
 *
 *END**************************************************************************/
dspi_status_t DSPI_DRV_DmaSlaveAbortTransfer(uint32_t instance)
{
    dspi_dma_slave_state_t * dspiState = (dspi_dma_slave_state_t *)g_dspiStatePtr[instance];

    /* Check driver initialized */
    if (!dspiState)
    {
        return kStatus_DSPI_NonInit;
    }

    /* Check current status */
    if (!dspiState->isTransferInProgress)
    {
        return kStatus_DSPI_NoTransferInProgress;
    }

    /* Force complete the transfer */
    DSPI_DRV_DmaCompleteTransfer(instance);

    return kStatus_DSPI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_DmaCompleteTransfer
 * Description   : Finish the transfer
 * Called when transfer is finished
 *
 *END**************************************************************************/
static void DSPI_DRV_DmaCompleteTransfer(uint32_t instance)
{
    SPI_Type *base = g_dspiBase[instance];
    dspi_dma_slave_state_t * dspiState = (dspi_dma_slave_state_t *)g_dspiStatePtr[instance];

    /* Stop DMA channels */
    DMA_DRV_StopChannel(&dspiState->dmaTxChannel);
    DMA_DRV_StopChannel(&dspiState->dmaRxChannel);

    /* Stop transfer */
    DSPI_HAL_StopTransfer(base);

    /* Disable the transmit FIFO fill request */
    DSPI_HAL_SetTxFifoFillDmaIntMode(base, kDspiGenerateDmaReq, false);
    /* Disable the Receive FIFO Drain Request */
    DSPI_HAL_SetRxFifoDrainDmaIntMode(base, kDspiGenerateDmaReq, false);

    /* Update status */
    dspiState->status = kStatus_DSPI_Success;
    dspiState->isTransferInProgress = false;
    dspiState->sendBuffer = NULL;
    dspiState->receiveBuffer = NULL;
    dspiState->remainingSendByteCount = 0;
    dspiState->remainingReceiveByteCount = 0;
    dspiState->extraReceiveByte = 0;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_DmaSlaveGetTransferStatus
 * Description   : Returns whether the previous transfer has finished yet.
 * When performing an async transfer, the user can call this function to ascertain the state of the
 * current transfer: in progress (or busy) or complete (success). In addition, if the transfer
 * is still in progress, the user can obtain the number of words that have been currently
 * transferred.
 *
 *END**************************************************************************/
dspi_status_t DSPI_DRV_DmaSlaveGetTransferStatus(uint32_t instance, uint32_t * framesTransferred)
{
    /* instantiate local variable of type dspi_dma_slave_state_t and point to global state */
    dspi_dma_slave_state_t * dspiState = (dspi_dma_slave_state_t *)g_dspiStatePtr[instance];
    SPI_Type *base = g_dspiBase[instance];

    /* Fill in the bytes transferred. */
    if (framesTransferred)
    {
        *framesTransferred = DSPI_HAL_GetTransferCount(base);
    }

    return ((dspiState->isTransferInProgress) ? kStatus_DSPI_Busy : kStatus_DSPI_Success);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_DmaSlaveTransfer
 * Description   : Transfer data to master
 * Start transfer data to master
 *
 *END**************************************************************************/
dspi_status_t DSPI_DRV_DmaSlaveTransfer(uint32_t instance,
                                         const uint8_t *sendBuffer,
                                         uint8_t *receiveBuffer,
                                         uint32_t transferByteCount)
{
    dspi_dma_slave_state_t * dspiState = (dspi_dma_slave_state_t *)g_dspiStatePtr[instance];

    assert(instance < SPI_INSTANCE_COUNT);

    /* Check if DSPI is not initialized */
    if (!dspiState)
    {
        return kStatus_DSPI_NonInit;
    }

    /* Check if buffers and length is empty */
    if (((!sendBuffer) && (!receiveBuffer)) ||
        (!transferByteCount))
    {
        return kStatus_DSPI_InvalidParameter;
    }

    /* Check if driver does not idle */
    if (dspiState->status != kStatus_DSPI_Success)
    {
        return dspiState->status;
    }

    /* If using a shared RX/TX DMA request, then this limits the amount of data we can transfer
     * due to the linked channel. The max bytes is 511 if 8-bit/frame or 1022 if 16-bit/frame
     */
    if (!FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(instance))
    {
        if (dspiState->bitsPerFrame > 8)
        {
            if (transferByteCount > 1022)
            {
                return kStatus_DSPI_OutOfRange;
            }
        }
        else
        {
            if (transferByteCount > 511)
            {
                return kStatus_DSPI_OutOfRange;
            }
        }
    }

    dspiState->isSync = false;

    DSPI_DRV_DmaSlaveStartTransfer(instance, sendBuffer, receiveBuffer, transferByteCount);

    return kStatus_DSPI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_DmaSlaveTransferBlocking
 * Description   : Transfer data - blocking
 * Transfer data - blocking
 *
 *END**************************************************************************/
dspi_status_t DSPI_DRV_DmaSlaveTransferBlocking(uint32_t instance,
                                                 const uint8_t *sendBuffer,
                                                 uint8_t *receiveBuffer,
                                                 uint32_t transferByteCount,
                                                 uint32_t timeOut)
{
    dspi_dma_slave_state_t * dspiState = (dspi_dma_slave_state_t *)g_dspiStatePtr[instance];
    dspi_status_t result = kStatus_DSPI_Success;
    event_flags_t setFlags = 0;
    osa_status_t osaStatus = kStatus_OSA_Success;

    /* Check if DSPI is not initialized */
    if (!dspiState)
    {
        return kStatus_DSPI_NonInit;
    }

    /* Check if buffers and length is empty */
    if (((!sendBuffer) && (!receiveBuffer)) ||
        (!transferByteCount))
    {
        return kStatus_DSPI_InvalidParameter;
    }

    /* Check if driver does not idle */
    if (dspiState->status != kStatus_DSPI_Success)
    {
        return dspiState->status;
    }

    /* If using a shared RX/TX DMA request, then this limits the amount of data we can transfer
     * due to the linked channel. The max bytes is 511 if 8-bit/frame or 1022 if 16-bit/frame
     */
    if (!FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(instance))
    {
        if (dspiState->bitsPerFrame > 8)
        {
            if (transferByteCount > 1022)
            {
                return kStatus_DSPI_OutOfRange;
            }
        }
        else
        {
            if (transferByteCount > 511)
            {
                return kStatus_DSPI_OutOfRange;
            }
        }
    }

    dspiState->isSync = true;

    /* Clear the event flags */
    OSA_EventClear(&dspiState->event, kDspiDmaTransferDone);

    DSPI_DRV_DmaSlaveStartTransfer(instance, sendBuffer, receiveBuffer, transferByteCount);

    /* wait transfer finished */
    do
    {
        osaStatus = OSA_EventWait(&dspiState->event, kDspiDmaTransferDone, true, timeOut, &setFlags);
    } while(osaStatus == kStatus_OSA_Idle);

    /* Check status of OSA wait event */
    switch (osaStatus)
    {
        case kStatus_OSA_Success:
            result = kStatus_DSPI_Success;
            break;
        case kStatus_OSA_Timeout:
            result = kStatus_DSPI_Timeout;
            break;
        case kStatus_OSA_Error:
        default:
            result = kStatus_DSPI_Error;
            break;
    }

    if (result != kStatus_DSPI_Success)
    {
        /* Abort the transfer */
        DSPI_DRV_DmaSlaveAbortTransfer(instance);
    }

    return result;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_DmaRxCallback
 * Description   : Callback function, this called when DMA receiving data
 * completed
 *
 *END**************************************************************************/
static void DSPI_DRV_DmaRxCallback(void *param, dma_channel_status_t status)
{
    uint32_t instance = (uint32_t)param;
    uint8_t i = 0;
    DMAMUX_Type *dmamuxbase;
    uint32_t dmaChannel;
    SPI_Type *base = g_dspiBase[instance];
    dspi_dma_slave_state_t * dspiState = (dspi_dma_slave_state_t *)g_dspiStatePtr[instance];

    /* Stop DMA Rx channel */
    DMA_DRV_StopChannel(&dspiState->dmaRxChannel);

    /* If transmission is finish with extra bytes remainning */
    if ((dspiState->extraReceiveByte) && (dspiState->remainingReceiveByteCount))
    {
        /* Setup DMA channel to receive extra bytes - 1 frame only */
        if (dspiState->receiveBuffer)
        {
            dspiState->receiveBuffer += dspiState->remainingReceiveByteCount;
        }
        dspiState->remainingReceiveByteCount = 0;

        dmaChannel = dspiState->dmaRxChannel.channel;
        dmamuxbase = g_dmamuxBase[dmaChannel/FSL_FEATURE_DMAMUX_MODULE_CHANNEL];
        /* The DONE needs to be cleared before programming the channel's TCDs for the next transfer. */
        // DMA_DRV_ClearStatus(&dspiState->dmaRxChannel);

        /* Disable and enable the RX DMA channel at the DMA mux. Doing so will prevent an
         * inadvertent DMA transfer when the RX DMA channel ERQ bit is set after having been
         * cleared from a previous DMA transfer (clearing of the ERQ bit is automatically performed
         * at the end of a transfer when D_REQ is set).
         */
        DMAMUX_HAL_SetChannelCmd(dmamuxbase, dmaChannel, false);
        DMAMUX_HAL_SetChannelCmd(dmamuxbase, dmaChannel, true);

        /* Setup DMA for fill received data into temp variable, this only run 1 time due to get extra byte */
        DMA_DRV_ConfigTransfer(&dspiState->dmaRxChannel,
                               kDmaPeripheralToPeripheral,
                               4u, DSPI_HAL_GetPoprRegAddr(base), /* src is data register */
                               (uint32_t)(&s_rxBuffIfNull), /* dest is temporary location */
                               4u);

        /* Register callback for DMA interrupt */
        DMA_DRV_RegisterCallback(&dspiState->dmaRxChannel, DSPI_DRV_DmaRxCallback, param);

        /* Enable the DMA peripheral request */
        DMA_DRV_StartChannel(&dspiState->dmaRxChannel);

        return;
    }

    /* The DSPI transmission finished. If it has extra bytes, store these bytes */
    if ((dspiState->extraReceiveByte) && (dspiState->receiveBuffer))
    {
        for (i = 0; i < dspiState->extraReceiveByte; ++i)
        {
            dspiState->receiveBuffer[i] = (uint8_t)(s_rxBuffIfNull >> i);
        }
    }

    DSPI_DRV_DmaCompleteTransfer(instance);

    /* Notify event */
    if(dspiState->isSync)
    {
        OSA_EventSet(&dspiState->event, kDspiDmaTransferDone);
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_DmaTxCallback
 * Description   : Callback function, this called when DMA transmitting data
 * completed
 *
 *END**************************************************************************/
static void DSPI_DRV_DmaTxCallback(void *param, dma_channel_status_t status)
{
    uint32_t instance = (uint32_t)param;
    SPI_Type *base = g_dspiBase[instance];
    dspi_dma_slave_state_t * dspiState = (dspi_dma_slave_state_t *)g_dspiStatePtr[instance];
    uint8_t nBytes;

    nBytes = dspiState->bitsPerFrame / 8;
    if ((dspiState->bitsPerFrame & 0x07U) != 0)
    {
        nBytes += 1;
    }

    /* Stop DMA Tx channel */
    DMA_DRV_StopChannel(&dspiState->dmaTxChannel);

    /* Disable Tx Fifo fill interrupt */
    DSPI_HAL_SetTxFifoFillDmaIntMode(base, kDspiGenerateDmaReq, false);
}

#endif /* FSL_FEATURE_SOC_DSPI_COUNT */
/*******************************************************************************
 * EOF
 ******************************************************************************/

