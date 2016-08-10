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

#include <string.h>
#include <assert.h>
#include "fsl_dspi_edma_slave_driver.h"
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
typedef enum _dspi_edma_event_flags {
    kDspiEdmaTransferDone = 0x01,         /*!< Transferring done flag */
} dspi_edma_event_flag_t;

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
 * @param status current status of eDMA channel
 */
static void DSPI_DRV_EdmaRxCallback(void *param, edma_chn_status_t status);

/*!
 * @brief DSPI transmit done callback function
 * @details This function is called when transmitting is done.
 *
 * @param param pointer to parameter
 * @param status current status of eDMA channel
 */
static void DSPI_DRV_EdmaTxCallback(void *param, edma_chn_status_t status);

/*!
 * @brief Finish the current DSPI transfer
 * @details This function stop the DSPI transfer
 *
 * @param instance The instance of DSPI hardware
 */
static void DSPI_DRV_EdmaCompleteTransfer(uint32_t instance);

/*!
 * @brief Start slave transferring.
 * @details This function make starting the transfer.
 *
 * @param instance The instance number of DSPI peripheral
 * @param sendBuffer The pointer to transmit buffer
 * @param receiveBuffer The pointer to receive buffer
 * @param transferByteCount The transfer size
 */
static void DSPI_DRV_EdmaSlaveStartTransfer(uint32_t instance,
                                            const uint8_t *sendBuffer,
                                            uint8_t *receiveBuffer,
                                            uint32_t transferByteCount);

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_EdmaSlaveInit
 * Description   : Initialize a DSPI slave instance.
 * Un-gate DSPI's clock, setup the default value and initializes the required
 * resources.
 *
 *END**************************************************************************/
dspi_status_t DSPI_DRV_EdmaSlaveInit(uint32_t instance,
                                     dspi_edma_slave_state_t * dspiState,
                                     const dspi_edma_slave_user_config_t * slaveConfig)
{
    dspi_status_t result = kStatus_DSPI_Success;
    dma_request_source_t dspiTxEdmaRequest = kDmaRequestMux0Disable;
    dma_request_source_t dspiRxEdmaRequest = kDmaRequestMux0Disable;
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

    /* Check if bits/frame size is valid, if not return error. */
    if (slaveConfig->dataConfig.bitsPerFrame > 16)
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
            dspiRxEdmaRequest = kDmaRequestMux0SPI0Rx;
            dspiTxEdmaRequest = kDmaRequestMux0SPI0Tx;
#else
            dspiRxEdmaRequest = kDmaRequestMux0SPI0;
            dspiTxEdmaRequest = kDmaRequestMux0Disable;
#endif
            break;
#if (FSL_FEATURE_SOC_DSPI_COUNT > 1)
        case 1:
            /* SPI1 */
#if FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(1)
            dspiRxEdmaRequest = kDmaRequestMux0SPI1Rx;
            dspiTxEdmaRequest = kDmaRequestMux0SPI1Tx;
#else
            dspiRxEdmaRequest = kDmaRequestMux0SPI1;
            dspiTxEdmaRequest = kDmaRequestMux0Disable;
#endif
            break;
#endif
#if (FSL_FEATURE_SOC_DSPI_COUNT > 2)
        case 2:
            /* SPI2 */
#if FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(2)
            dspiRxEdmaRequest = kDmaRequestMux0SPI2Rx;
            dspiTxEdmaRequest = kDmaRequestMux0SPI2Tx;
#else
            dspiRxEdmaRequest = kDmaRequestMux0SPI2;
            dspiTxEdmaRequest = kDmaRequestMux0Disable;
#endif
            break;
#endif
        default :
            return kStatus_DSPI_InvalidInstanceNumber;
    }

    /* This channel transfers data from RX FIFO to receiveBuffer */
    if (kEDMAInvalidChannel == EDMA_DRV_RequestChannel(kEDMAAnyChannel,
                                                       dspiRxEdmaRequest,
                                                       &dspiState->edmaRxChannel))
    {
        dspiState->status = kStatus_DSPI_Error;
        return kStatus_DSPI_DMAChannelInvalid;
    }

    /* This channel transfers data from transmitBuffer to TX FIFO */
    if (kEDMAInvalidChannel == EDMA_DRV_RequestChannel(kEDMAAnyChannel,
                                                       dspiTxEdmaRequest,
                                                       &dspiState->edmaTxChannel))
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
 * Function Name : DSPI_DRV_EdmaSlaveDeinit
 * Description   : Shutdown a DSPI instance.
 * Resets the DSPI peripheral, disables the interrupt to the core, and gates its clock.
 *
 *END**************************************************************************/
dspi_status_t DSPI_DRV_EdmaSlaveDeinit(uint32_t instance)
{
    SPI_Type *base = g_dspiBase[instance];
    dspi_edma_slave_state_t * dspiState = (dspi_edma_slave_state_t *)g_dspiStatePtr[instance];

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

    EDMA_DRV_ReleaseChannel(&dspiState->edmaTxChannel);
    EDMA_DRV_ReleaseChannel(&dspiState->edmaRxChannel);

    dspiState->status = kStatus_DSPI_NonInit;

    /* Clear state pointer. */
    g_dspiStatePtr[instance] = NULL;

    return kStatus_DSPI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_EdmaSlaveStartTransfer
 * Description   : Starts transfer data on SPI bus using eDMA and non-blocking call
 * Start DSPI transfering, update transmit/receive information into slave state structure
 *
 *END**************************************************************************/
static void DSPI_DRV_EdmaSlaveStartTransfer(uint32_t instance,
                                            const uint8_t *sendBuffer,
                                            uint8_t *receiveBuffer,
                                            uint32_t transferByteCount)
{
    SPI_Type *base = g_dspiBase[instance];
    dspi_edma_slave_state_t * dspiState = (dspi_edma_slave_state_t *)g_dspiStatePtr[instance];
    uint8_t nBytes = dspiState->bitsPerFrame / 8;
    uint32_t txTransferByteCnt = 0;
    uint32_t rxTransferByteCnt = 0;
    uint32_t sendData = 0;
    edma_software_tcd_t stcd;
    edma_transfer_config_t config;

    /* Calculate number of bytes in frame */
    if (dspiState->bitsPerFrame % 8 != 0)
    {
        nBytes ++;
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
    /* Firstly, fill one TX FIFO register to ensure the data will be transmitted to master. */
    if (sendBuffer)
    {
        if (nBytes == 1)
        {
            sendData = *sendBuffer;
            sendBuffer ++;
        }
        else
        {
            sendData = *sendBuffer;
            sendBuffer ++;
            sendData |= (uint32_t)(*sendBuffer) << 8;
            sendBuffer++;
        }
    }
    else
    {
        sendData = s_dataToSend;
    }
    DSPI_HAL_WriteDataSlavemode(base, sendData);
    /* try to clear TFFF by writing a one to it; it will not clear if TX FIFO not full */
    DSPI_HAL_ClearStatusFlag(base, kDspiTxFifoFillRequest);

    /* Calculate number of byte to transmit & receive */
    if ((nBytes > 1) && ((transferByteCount % nBytes) != 0))
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
    /* Tx transfer byte count is FIFO size more than Rx count */
    txTransferByteCnt = rxTransferByteCnt;

    /* Update remaining receive byte count */
    dspiState->remainingReceiveByteCount = rxTransferByteCnt;

    /* Store send buffer */
    dspiState->sendBuffer = sendBuffer;
    if (txTransferByteCnt)
    {
        memset(&config, 0, sizeof(edma_transfer_config_t));
        memset(&stcd, 0, sizeof(edma_software_tcd_t));

        if (sendBuffer)
        {
            config.srcAddr = (uint32_t)(sendBuffer); /* Source addr, TX Send buffer */
        }
        else
        {
            config.srcAddr = (uint32_t)(&s_dataToSend); /* Source address is static dummy data */
        }

        config.destAddr = DSPI_HAL_GetSlavePushrRegAddr(base); /* Destination is the TX FIFO */

        /* * The source and destination attributes (bit size) depends on bits/frame setting */
        if (dspiState->bitsPerFrame <= 8)
        {
            if (sendBuffer)
            {
                /* Source addr offset is 1 as send buffer pointer is incremented 1 bytes
                 * for each write
                 */
                config.srcOffset = 1U;
            }
            /* Destination size is always one byte, source size varies depending on bits/frame */
            config.srcTransferSize = kEDMATransferSize_1Bytes;
            config.destTransferSize = kEDMATransferSize_1Bytes;

            config.minorLoopCount = 1U; /* Transfer 1 byte from RX FIFO to receive buffer */

            config.majorLoopCount = txTransferByteCnt; /* Adjust majorIteration to 1 byte per transfer */
        }
        /* Source size is two bytes */
        else
        {
            if (sendBuffer)
            {
                /* Source addr offset is 2 as send buffer pointer is incremented 2 bytes
                 * for each write
                 */
                config.srcOffset = 2U;
            }

            /* Destination size is always one byte, source size varies depending on bits/frame */
            config.srcTransferSize = kEDMATransferSize_2Bytes;
            config.destTransferSize = kEDMATransferSize_2Bytes;

            /* Transfer 2 bytes from transmit buffer to TX FIFO */
            config.minorLoopCount = 2U;

            /* Adjust majorIteration to 2 bytes per transfer */
            config.majorLoopCount = txTransferByteCnt/2;
        }
        EDMA_DRV_PrepareDescriptorTransfer(&dspiState->edmaTxChannel,
                &stcd, &config, true, true);
        EDMA_DRV_PushDescriptorToReg(&dspiState->edmaTxChannel, &stcd);

        /* Start the DMA channel */
        EDMA_DRV_StartChannel(&dspiState->edmaTxChannel);
    }
    else
    {
        /* Transmission FIFO fill request interrupt disable */
        DSPI_HAL_SetTxFifoFillDmaIntMode(base, kDspiGenerateIntReq, false);
    }

    /* Store receive buffer */
    dspiState->receiveBuffer = receiveBuffer;
    if (rxTransferByteCnt)
    {
        memset(&config, 0, sizeof(edma_transfer_config_t));
        memset(&stcd, 0, sizeof(edma_software_tcd_t));

        /* Source addr, RX FIFO */
        config.srcAddr = DSPI_HAL_GetPoprRegAddr(base);

        if (receiveBuffer)
        {
            config.destAddr = (uint32_t)(receiveBuffer);    /* Destination is the receive buffer */
        }
        else
        {
            config.destAddr = (uint32_t)(&s_rxBuffIfNull);  /* Destination is the static buffer */
        }

        /* The source and destination attributes (bit size) depends on bits/frame setting */
        if (dspiState->bitsPerFrame <= 8)
        {
            if (receiveBuffer)
            {
                /* Dest addr offset, always increment to the next byte */
                config.destOffset = 1U;
            }

            /* Destination size is always one byte, source size varies depending on bits/frame */
            config.srcTransferSize = kEDMATransferSize_1Bytes;
            config.destTransferSize = kEDMATransferSize_1Bytes;

            /* Transfer 1 byte from RX FIFO to receive buffer */
            config.minorLoopCount = 1U;

            /* Adjust majorIteration to 1 byte per transfer */
            config.majorLoopCount = rxTransferByteCnt;
        }
        else
        /* Source size is two bytes */
        {
            if (receiveBuffer)
            {
                /* Dest addr offset, always increment to the next byte */
                config.destOffset = 2U;
            }

            /* Destination size is always one byte, source size varies depending on bits/frame */
            config.srcTransferSize = kEDMATransferSize_2Bytes;
            config.destTransferSize = kEDMATransferSize_2Bytes;

            /* Transfer 2 bytes from RX FIFO to receive buffer */
            config.minorLoopCount = 2U;

            /* Adjust majorIteration to 2 bytes per transfer */
            config.majorLoopCount = rxTransferByteCnt/2;
        }

        EDMA_DRV_PrepareDescriptorTransfer(&dspiState->edmaRxChannel,
                &stcd, &config, true, true);
        EDMA_DRV_PushDescriptorToReg(&dspiState->edmaRxChannel, &stcd);

        /* For DSPI instances with shared RX/TX DMA requests, we'll use the RX DMA request to
         * trigger ongoing transfers and will link to the TX DMA channel from the RX DMA channel.
         */
        if (!FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(instance))
        {
            /* Enable channel linking to TX channel (at the end of each minor loop) */
            EDMA_DRV_PrepareDescriptorMinorLink(&stcd,
                    VIRTUAL_CHN_TO_EDMA_CHN(dspiState->edmaTxChannel.channel));

            /* Enable MAJOR link and link to TX DMA channel. This is needed to perform one more
             * channel link when the major loop is exhausted.
             */
            EDMA_DRV_PrepareDescriptorChannelLink(&stcd,
                    VIRTUAL_CHN_TO_EDMA_CHN(dspiState->edmaTxChannel.channel));
        }

        /* Now that the TCD was set up, enable the DSPI Peripheral Hardware request for the
         * RX FIFO
         */
        EDMA_DRV_StartChannel(&dspiState->edmaRxChannel);

        /* Due to MISRA 11.1 rule:
         * Conversions shall not be performed between a pointer to a function
         * and any type other than an integral type.
         * We first have to typecast the callback function pointer as a uint32_t before typecasting
         * as a void pointer.
         */
        EDMA_DRV_InstallCallback(&dspiState->edmaRxChannel,
                                 DSPI_DRV_EdmaRxCallback,(void *)instance);
    }
    else if (dspiState->extraReceiveByte)
    {
        /* Slave receive length is less than bits/frame number of bytes */
        DSPI_HAL_ClearStatusFlag(base, kDspiTxComplete);
        DSPI_HAL_SetIntMode(base, kDspiTxComplete, true);
    }
    else
    {
        /* Reception FIFO fill request interrupt disable */
        DSPI_HAL_SetRxFifoDrainDmaIntMode(base, kDspiGenerateIntReq, false);
    }

    if(txTransferByteCnt)
    {
        /* Check if number of send bytes is smaller than FIFO deepth, enable transmit completed
         * interrupt to know when transferring is done
         */
        if (dspiState->remainingSendByteCount <= (g_dspiFifoSize[instance] * nBytes))
        {
            DSPI_HAL_ClearStatusFlag(base, kDspiTxComplete);
            DSPI_HAL_SetIntMode(base, kDspiTxComplete, true);
        }
        else
        {
            DSPI_HAL_SetIntMode(base, kDspiTxComplete, false);
        }

        /* For DSPI instances with separate RX/TX DMA requests, we'll use the TX DMA request to
         * trigger the TX DMA channel hence we'll enable the TX channel DMA request.
         */
        if (FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(instance))
        {
            /* Set up eDMA callback */
            /* Due to MISRA 11.1 rule:
             * Conversions shall not be performed between a pointer to a function
             * and any type other than an integral type.
             * We first have to typecast the callback function pointer as a uint32_t before typecasting
             * as a void pointer.
             */
            EDMA_DRV_InstallCallback(&dspiState->edmaTxChannel,
                                     DSPI_DRV_EdmaTxCallback,(void *)instance);
            /* Now that the TCD was set up for each channel, enable the DSPI peripheral hardware
             * request for the first TX DMA channel.
             */
            EDMA_DRV_StartChannel(&dspiState->edmaTxChannel);

            /* Enable TFFF request in the DSPI module */
            DSPI_HAL_SetTxFifoFillDmaIntMode(base, kDspiGenerateDmaReq, true);
        }
        /* For DSPI instances with shared RX/TX DMA requests, we'll use the RX DMA request to
         * trigger ongoing transfers that will link to the TX DMA channel from the RX DMA channel.
         * So, we'll disable the TX channel DMA request and then we'll have to manually start the
         * TX DMA channel to get the tranfer process started, where the RX DMA channel will take care
         * of the ongoing transfers from there.
         */
        else /* For shared RX/TX DMA requests */
        {
            /* Disable the DSPI TX peripheral hardware request */
            EDMA_DRV_StopChannel(&dspiState->edmaTxChannel);

            /* Disable TFFF request in the DSPI module */
            DSPI_HAL_SetTxFifoFillDmaIntMode(base, kDspiGenerateDmaReq, false);

            /* Manually start the TX DMA channel to get the process going */
            EDMA_DRV_TriggerChannelStart(&dspiState->edmaTxChannel);
        }
    }
    if(dspiState->remainingReceiveByteCount > 0)
    {
        /* Enable the Receive FIFO Drain Request as a DMA request */
        DSPI_HAL_SetRxFifoDrainDmaIntMode(base, kDspiGenerateDmaReq, true);
    }

    /* Update state */
    dspiState->isTransferInProgress = true;
    dspiState->status = kStatus_DSPI_Busy;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_EdmaSlaveAbortTransfer
 * Description   : Abort tranfer
 * Abort data transfer, using after function DSPI_DRV_EdmaSlaveTransfer() to abort
 * transfering data.
 *
 *END**************************************************************************/
dspi_status_t DSPI_DRV_EdmaSlaveAbortTransfer(uint32_t instance)
{
    dspi_edma_slave_state_t * dspiState = (dspi_edma_slave_state_t *)g_dspiStatePtr[instance];

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
    DSPI_DRV_EdmaCompleteTransfer(instance);

    return kStatus_DSPI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_EdmaCompleteTransfer
 * Description   : Finish the transfer
 * Called when transfer is finished
 *
 *END**************************************************************************/
static void DSPI_DRV_EdmaCompleteTransfer(uint32_t instance)
{
    dspi_edma_slave_state_t * dspiState = (dspi_edma_slave_state_t *)g_dspiStatePtr[instance];
    SPI_Type *base = g_dspiBase[instance];
    uint32_t readData;

    /* Stop Rx DMA channel. */
    EDMA_DRV_StopChannel(&dspiState->edmaRxChannel);

    /* Stop Tx DMA channel. */
    EDMA_DRV_StopChannel(&dspiState->edmaTxChannel);

    /* Stop transfer */
    DSPI_HAL_StopTransfer(base);

    /* Disable the transmit FIFO fill request */
    DSPI_HAL_SetTxFifoFillDmaIntMode(base, kDspiGenerateDmaReq, false);
    /* Disable the Receive FIFO Drain Request */
    DSPI_HAL_SetRxFifoDrainDmaIntMode(base, kDspiGenerateDmaReq, false);
    /* Disable transmit complete interrupt request */
    DSPI_HAL_SetIntMode(base, kDspiTxComplete, false);

    /* Update extra receive bytes */
    if((dspiState->extraReceiveByte > 0) && (dspiState->receiveBuffer))
    {
        /* Read data from FIFO and clear flag */
        readData = DSPI_HAL_ReadData(base);

        /* First byte */
        dspiState->receiveBuffer[dspiState->remainingReceiveByteCount] = (uint8_t)readData;
        if ((dspiState->extraReceiveByte > 0) &&(--dspiState->extraReceiveByte > 0))
        {
            /* Second byte if available */
            dspiState->receiveBuffer[dspiState->remainingReceiveByteCount + 1] = (uint8_t)(readData >> 8);
        }
    }

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
 * Function Name : DSPI_DRV_EdmaSlaveGetTransferStatus
 * Description   : Returns whether the previous transfer has finished yet.
 * When performing an async transfer, the user can call this function to ascertain the state of the
 * current transfer: in progress (or busy) or complete (success). In addition, if the transfer
 * is still in progress, the user can obtain the number of words that have been currently
 * transferred.
 *
 *END**************************************************************************/
dspi_status_t DSPI_DRV_EdmaSlaveGetTransferStatus(uint32_t instance, uint32_t * framesTransferred)
{
    /* instantiate local variable of type dspi_edma_slave_state_t and point to global state */
    dspi_edma_slave_state_t * dspiState = (dspi_edma_slave_state_t *)g_dspiStatePtr[instance];
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
 * Function Name : DSPI_DRV_EdmaSlaveTransfer
 * Description   : Transfer data to master
 * Start transfer data to master
 *
 *END**************************************************************************/
dspi_status_t DSPI_DRV_EdmaSlaveTransfer(uint32_t instance,
                                         const uint8_t *sendBuffer,
                                         uint8_t *receiveBuffer,
                                         uint32_t transferByteCount)
{
    dspi_edma_slave_state_t * dspiState = (dspi_edma_slave_state_t *)g_dspiStatePtr[instance];

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

    DSPI_DRV_EdmaSlaveStartTransfer(instance, sendBuffer, receiveBuffer, transferByteCount);

    return kStatus_DSPI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_EdmaSlaveTransferBlocking
 * Description   : Transfer data - blocking
 * Transfer data - blocking
 *
 *END**************************************************************************/
dspi_status_t DSPI_DRV_EdmaSlaveTransferBlocking(uint32_t instance,
                                                 const uint8_t *sendBuffer,
                                                 uint8_t *receiveBuffer,
                                                 uint32_t transferByteCount,
                                                 uint32_t timeOut)
{
    dspi_edma_slave_state_t * dspiState = (dspi_edma_slave_state_t *)g_dspiStatePtr[instance];
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
    OSA_EventClear(&dspiState->event, kDspiEdmaTransferDone);

    DSPI_DRV_EdmaSlaveStartTransfer(instance, sendBuffer, receiveBuffer, transferByteCount);

    /* wait transfer finished */
    do
    {
        osaStatus = OSA_EventWait(&dspiState->event, kDspiEdmaTransferDone, true, timeOut, &setFlags);
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
        DSPI_DRV_EdmaSlaveAbortTransfer(instance);
    }

    return result;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_EdmaRxCallback
 * Description   : Callback function, this called when eDMA receiving data
 * completed
 *
 *END**************************************************************************/
static void DSPI_DRV_EdmaRxCallback(void *param, edma_chn_status_t status)
{
    uint32_t instance = (uint32_t)param;
    SPI_Type *base = g_dspiBase[instance];
    dspi_edma_slave_state_t * dspiState = (dspi_edma_slave_state_t *)g_dspiStatePtr[instance];

    if (dspiState->extraReceiveByte != 0)
    {
        /* Enable transmit complete interrupt */
        DSPI_HAL_ClearStatusFlag(base, kDspiTxComplete);
        DSPI_HAL_SetIntMode(base, kDspiTxComplete, true);
    }

    /* Stop DMA channel. */
    EDMA_DRV_StopChannel(&dspiState->edmaRxChannel);

    /* Disable Rx Fifo drain interrupt */
    DSPI_HAL_SetRxFifoDrainDmaIntMode(base, kDspiGenerateDmaReq, false);

    /* If transmission completed, stop the transferring */
    if ((dspiState->isTransferInProgress) &&
        (!FSL_FEATURE_DSPI_HAS_SEPARATE_DMA_RX_TX_REQn(instance)) &&
        (dspiState->extraReceiveByte == 0))
    {
        DSPI_DRV_EdmaCompleteTransfer(instance);

        /* Notify event */
        if(dspiState->isSync)
        {
            OSA_EventSet(&dspiState->event, kDspiEdmaTransferDone);
        }
    }
    else if ((dspiState->isTransferInProgress) &&
             (dspiState->remainingSendByteCount <= 0) &&
             (dspiState->extraReceiveByte == 0))
    {
        DSPI_DRV_EdmaCompleteTransfer(instance);

        /* Notify event */
        if(dspiState->isSync)
        {
            OSA_EventSet(&dspiState->event, kDspiEdmaTransferDone);
        }
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_EdmaTxCallback
 * Description   : Callback function, this called when eDMA transmitting data
 * completed
 *
 *END**************************************************************************/
static void DSPI_DRV_EdmaTxCallback(void *param, edma_chn_status_t status)
{
    uint32_t instance = (uint32_t)param;
    SPI_Type *base = g_dspiBase[instance];
    dspi_edma_slave_state_t * dspiState = (dspi_edma_slave_state_t *)g_dspiStatePtr[instance];
    uint8_t nBytes;

    nBytes = dspiState->bitsPerFrame / 8;
    if (dspiState->bitsPerFrame % 8 != 0)
    {
        nBytes += 1;
    }

    /* Check if send bytes count is greater than FIFO size, update this count and enable
     * transmit completed interrupt.
     */
    if (dspiState->remainingSendByteCount > (g_dspiFifoSize[instance] * nBytes))
    {
        /* Enable transmit complete interrupt */
        DSPI_HAL_ClearStatusFlag(base, kDspiTxComplete);
        DSPI_HAL_SetIntMode(base, kDspiTxComplete, true);
    }

    /* Stop DMA channel. */
    EDMA_DRV_StopChannel(&dspiState->edmaTxChannel);

    /* Disable Tx Fifo fill interrupt */
    DSPI_HAL_SetTxFifoFillDmaIntMode(base, kDspiGenerateDmaReq, false);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : DSPI_DRV_EdmaSlaveIRQHandler
 * Description   : DSPI slave interrupt handler
 *          This function is DSPI slave interrupt handler using eDMA mechanism. The
 *          pupose of this interrupt handler is indicates when the transfer is really
 *          finished. The eDMA only used to copy data from/to RX FIFO/TX FIFO, but it
 *          not sure the data was transmitted to the master. So must have to enable
 *          this interrupt to do it. This interrupt only be enabled when the last
 *          four FIFO will be transmitted.
 *
 *END**************************************************************************/
void DSPI_DRV_EdmaSlaveIRQHandler(uint32_t instance)
{
    SPI_Type *base = g_dspiBase[instance];
    dspi_edma_slave_state_t * dspiState = (dspi_edma_slave_state_t *)g_dspiStatePtr[instance];
    uint8_t nBytes;

    nBytes = dspiState->bitsPerFrame / 8;
    if (dspiState->bitsPerFrame % 8 != 0)
    {
        nBytes += 1;
    }

    /* Catch Tx complete interrupt */
    if ((DSPI_HAL_GetIntMode(base, kDspiTxComplete)) &&
        (DSPI_HAL_GetStatusFlag(base, kDspiTxComplete)))
    {
        /* Clear this flag first */
        DSPI_HAL_ClearStatusFlag(base, kDspiTxComplete);

        /* Check if number of transfered bytes is greater or equals user request */
        if(dspiState->remainingSendByteCount <= (DSPI_HAL_GetTransferCount(base) * nBytes))
        {
            /* Complete the transfer */
            DSPI_DRV_EdmaCompleteTransfer(instance);
            /* Notify to wait task */
            if(dspiState->isSync)
            {
                OSA_EventSet(&dspiState->event, kDspiEdmaTransferDone);
            }
        }
    }
}

#endif /* FSL_FEATURE_SOC_DSPI_COUNT */
/*******************************************************************************
 * EOF
 ******************************************************************************/

