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
#include "fsl_spi_dma_slave_driver.h"
#include "fsl_clock_manager.h"
#include "fsl_interrupt_manager.h"

#if FSL_FEATURE_SOC_SPI_COUNT

/*******************************************************************************
 * Definitions
 ******************************************************************************/
/*!
 * @brief Flags of SPI slave event.
 *
 * SPI event used to notify user that it finishes the task.
 */
typedef enum _spi_dma_event_flags {
    kSpiDmaTransferDone = 0x01,        /*!< Transferring done flag */
} spi_dma_event_flag_t;
/*******************************************************************************
 * Variables
 ******************************************************************************/
/* Pointer to runtime state structure.*/
extern void * g_spiStatePtr[SPI_INSTANCE_COUNT];

static uint8_t s_byteToSend;  /* Word to send, if no send buffer, this variable is used
                                 as the word to send, which should be initialized to 0. Needs
                                 to be static and stored in data section as this variable
                                 address is the DMA source address if no source buffer. */

static uint8_t s_rxBuffIfNull; /* If no receive buffer provided, direct rx DMA channel to this
                                  destination */

/* Table of SPI FIFO sizes per instance. */
extern const uint32_t g_spiFifoSize[SPI_INSTANCE_COUNT];

/*******************************************************************************
 * Code
 ******************************************************************************/
/*!
 * @brief Configure SPI slave module and start the transfer using DMA
 *
 * This function updates SPI slave state structure, configures SPI slave module
 * using DMA driven and then start the transfer.
 *
 * @param instance The instance number of the SPI peripheral.
 */
static spi_status_t SPI_DRV_DmaSlaveStartTransfer(uint32_t instance);

/*!
 * @brief Stop the SPI slave transfer using DMA
 *
 * This function makes SPI slave transferring stop.
 *
 * @param instance The instance number of the SPI peripheral.
 */
static void SPI_DRV_DmaSlaveCompleteTransfer(uint32_t instance);

/*!
 * @brief The callback function for DMA complete interrupt.
 *
 * @param param Instance number of the SPI module.
 * @param chanStatus Current status of DMA channel.
 */
void SPI_DRV_DmaSlaveCallback(void *param, dma_channel_status_t chanStatus);

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_DRV_DmaSlaveCallback
 * Description   : This function is called when the DMA generates an interrupt.
 * The DMA generates an interrupt when the channel is "done", meaning that the
 * expected number of bytes have been transferred.  When the interrupt occurs,
 * the DMA will jump to this callback as it was registered in the DMA register
 * callback service function.  The user will defined their own callback function
 * to take whatever action they deem necessary for handling the end of a transfer.
 * For example, the user may simply want their callback function to set a global
 * flag to indicate that the transfer is complete.  The user defined callback
 * is passed in through the "param" parameter.
 * The parameter chanStatus is currently not used.
 *
 *END**************************************************************************/
void SPI_DRV_DmaSlaveCallback(void *param, dma_channel_status_t chanStatus)
{
    uint32_t instance = (uint32_t)(param);

    /* instantiate local variable of type spi_master_state_t and point to global state */
    spi_dma_slave_state_t * spiDmaState = (spi_dma_slave_state_t *)g_spiStatePtr[instance];

    SPI_Type *base = g_spiBase[instance];

    /* If hasExtraByte flag was set, need to enable the TX empty interrupt to get the last byte */
    if ((spiDmaState->hasExtraByte) && (spiDmaState->remainingReceiveByteCount))
    {
        SPI_HAL_SetTxDmaCmd(base, false);
        SPI_HAL_SetIntMode(base, kSpiTxEmptyInt, true);
    }
    else
    {
        /* Transfer completed, finish the transfer */
        SPI_DRV_DmaSlaveCompleteTransfer(instance);
    }

}

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_DRV_DmaSlaveInit
 * Description   : Initializes the SPI module for slave mode.
 * Saves the application callback info, turns on the clock to the module,
 * enables the device, and enables interrupts. Sets the SPI to a slave mode.
 *
 *END**************************************************************************/
spi_status_t SPI_DRV_DmaSlaveInit(uint32_t instance, spi_dma_slave_state_t * spiState,
                       const spi_dma_slave_user_config_t * slaveConfig)
{
    SPI_Type *base = g_spiBase[instance];
    assert(slaveConfig);
    assert(instance < SPI_INSTANCE_COUNT);
    assert(spiState);

#if FSL_FEATURE_SPI_16BIT_TRANSFERS
    if (slaveConfig->bitCount > kSpi16BitMode)
    {
        /* bits/frame larger than hardware support */
        return kStatus_SPI_InvalidParameter;
    }
#endif /* FSL_FEATURE_SPI_16BIT_TRANSFERS */

    /* Check if the slave already initialized */
    if (g_spiStatePtr[instance])
    {
        return kStatus_SPI_AlreadyInitialized;
    }

    /* Clear the state for this instance. */
    memset(spiState, 0, sizeof(* spiState));

    spiState->hasExtraByte = false;

    /* Update dummy pattern value */
    spiState->dummyPattern = slaveConfig->dummyPattern;

    /* Enable clock for SPI */
    CLOCK_SYS_EnableSpiClock(instance);

    /* Reset the SPI module to its default settings including disabling SPI */
    SPI_HAL_Init(base);

    /* Initialize the event structure */
    if (OSA_EventCreate(&spiState->event, kEventAutoClear) != kStatus_OSA_Success)
    {
        return kStatus_SPI_Error;
    }

    /* Set SPI to slave mode */
    SPI_HAL_SetMasterSlave(base, kSpiSlave);

    /* Configure the slave clock polarity, phase and data direction */
    SPI_HAL_SetDataFormat(base, slaveConfig->polarity, slaveConfig->phase,
            slaveConfig->direction);

    /* Set the SPI pin mode to normal mode */
    SPI_HAL_SetPinMode(base, kSpiPinMode_Normal);

#if FSL_FEATURE_SPI_16BIT_TRANSFERS
    SPI_HAL_Set8or16BitMode(base, slaveConfig->bitCount);
#endif /* FSL_FEATURE_SPI_16BIT_TRANSFERS */

#if FSL_FEATURE_SPI_FIFO_SIZE
    if (g_spiFifoSize[instance] != 0)
    {
        /* If SPI module contains a FIFO, enable it and set watermarks to half full/empty */
        SPI_HAL_SetFifoMode(base, true, kSpiTxFifoOneHalfEmpty, kSpiRxFifoOneHalfFull);

        /* Set the interrupt clearing mechansim select for later use in driver to clear
         * status flags
         */
        SPI_HAL_SetIntClearCmd(base, true);
    }
#endif /* FSL_FEATURE_SPI_FIFO_SIZE */

    /*****************************************
     * Request DMA channel for RX and TX FIFO
     *****************************************/
    /* This channel transfers data from RX FIFO to receiveBuffer */
    if (instance == 0)
    {
        /* Request DMA channel for RX FIFO */
        if (kDmaInvalidChannel == DMA_DRV_RequestChannel(kDmaAnyChannel,
                                                         kDmaRequestMux0SPI0Rx,
                                                         &spiState->dmaReceive))
        {
            return kStatus_SPI_DMAChannelInvalid;
        }
        /* Request DMA channel for TX FIFO */
        if (kDmaInvalidChannel == DMA_DRV_RequestChannel(kDmaAnyChannel,
                                                         kDmaRequestMux0SPI0Tx,
                                                         &spiState->dmaTransmit))
        {
            return kStatus_SPI_DMAChannelInvalid;
        }
    }
#if (SPI_INSTANCE_COUNT > 1)
    else if (instance == 1)
    {
        /* Request DMA channel for RX FIFO */
        if (kDmaInvalidChannel == DMA_DRV_RequestChannel(kDmaAnyChannel,
                                                         kDmaRequestMux0SPI1Rx,
                                                         &spiState->dmaReceive))
        {
            return kStatus_SPI_DMAChannelInvalid;
        }
        /* Request DMA channel for TX FIFO */
        if (kDmaInvalidChannel == DMA_DRV_RequestChannel(kDmaAnyChannel,
                                                         kDmaRequestMux0SPI1Tx,
                                                         &spiState->dmaTransmit))
        {
            return kStatus_SPI_DMAChannelInvalid;
        }
    }
    else
    {
        return kStatus_SPI_OutOfRange;
    }
#endif

    /* Save runtime structure pointers to irq handler can point to the correct state structure */
    g_spiStatePtr[instance] = spiState;

    /* Enable SPI interrupt. The transmit interrupt should immediately cause an interrupt
     * which will fill in the transmit buffer and will be ready to send once the slave initiates
     * transmission.
     */
    INT_SYS_EnableIRQ(g_spiIrqId[instance]);

    /* SPI module enable */
    SPI_HAL_Enable(base);

    return kStatus_SPI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_DRV_DmaSlaveDeinit
 * Description   : De-initializes the device.
 * Clears the control register and turns off the clock to the module.
 *
 *END**************************************************************************/
spi_status_t SPI_DRV_DmaSlaveDeinit(uint32_t instance)
{
    spi_dma_slave_state_t * spiState = (spi_dma_slave_state_t *)g_spiStatePtr[instance];
    SPI_Type *base = g_spiBase[instance];

    assert(instance < SPI_INSTANCE_COUNT);

    /* Disable SPI interrupt */
    INT_SYS_DisableIRQ(g_spiIrqId[instance]);

    /* Reset the SPI module to its default settings including disabling SPI and its interrupts */
    SPI_HAL_Init(base);

#if FSL_FEATURE_SPI_16BIT_TRANSFERS
    if (g_spiFifoSize[instance] != 0)
    {
        SPI_HAL_SetFifoIntCmd(base, kSpiRxFifoNearFullInt, false);
    }

    /* disable transmit interrupt */
    SPI_HAL_SetIntMode(base, kSpiTxEmptyInt, false);
#endif /* FSL_FEATURE_SPI_16BIT_TRANSFERS */

    /* Free DMA channels */
    DMA_DRV_FreeChannel(&spiState->dmaReceive);
    DMA_DRV_FreeChannel(&spiState->dmaTransmit);

    /* Disable clock for SPI */
    CLOCK_SYS_DisableSpiClock(instance);

    /* Destroy the event */
    OSA_EventDestroy(&spiState->event);

    /* Clear state pointer */
    g_spiStatePtr[instance] = NULL;

    return kStatus_SPI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_DRV_DmaSlaveTransfer
 * Description   : Transfer data with the master using DMA driven. Starts the
 * transfer with transmit buffer, receive buffer and transfer byte count passed.
 *
 *END**************************************************************************/
spi_status_t SPI_DRV_DmaSlaveTransfer(uint32_t instance,
                                   const uint8_t *sendBuffer,
                                   uint8_t *receiveBuffer,
                                   uint32_t transferByteCount)
{
    spi_dma_slave_state_t * spiState = (spi_dma_slave_state_t *)g_spiStatePtr[instance];
    spi_status_t errorStatus = kStatus_SPI_Success;

    /* Validate the parameter */
    assert(instance < SPI_INSTANCE_COUNT);

    if ((!sendBuffer) && (!receiveBuffer))
    {
        /* sendBuffer and receiveBuffer are not available, this is invalid */
        return kStatus_SPI_InvalidParameter;
    }

    if (!transferByteCount)
    {
        /* number of transfer bytes is 0 */
        return kStatus_SPI_InvalidParameter;
    }

    if (spiState->isTransferInProgress)
    {
        /* The another transfer is in progress */
        return kStatus_SPI_Busy;
    }

    /* fill in members of the run-time state struct */
    spiState->isSync = false;
    spiState->sendBuffer = sendBuffer;
    spiState->receiveBuffer = (uint8_t *)receiveBuffer;
    spiState->remainingSendByteCount = transferByteCount;
    spiState->remainingReceiveByteCount = transferByteCount;

    /* Setup hardware to start the transfer */
    errorStatus = SPI_DRV_DmaSlaveStartTransfer(instance);
    if (errorStatus != kStatus_SPI_Success)
    {
        return errorStatus;
    }

    return kStatus_SPI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_DRV_DmaSlaveTransferBlocking
 * Description   : Transfer data with the master, using blocking call and DMA
 * driven.
 *
 *END**************************************************************************/
spi_status_t SPI_DRV_DmaSlaveTransferBlocking(uint32_t instance,
                                           const uint8_t *sendBuffer,
                                           uint8_t *receiveBuffer,
                                           uint32_t transferByteCount,
                                           uint32_t timeout)
{
    spi_dma_slave_state_t * spiState = (spi_dma_slave_state_t *)g_spiStatePtr[instance];
    spi_status_t errorStatus = kStatus_SPI_Success;
    event_flags_t setFlags = 0;

    /* fill in members of the run-time state struct */
    spiState->isSync = true;
    spiState->sendBuffer = (const uint8_t *)sendBuffer;
    spiState->receiveBuffer = (uint8_t *)receiveBuffer;
    spiState->remainingSendByteCount = transferByteCount;
    spiState->remainingReceiveByteCount = transferByteCount;

    /* Clear the event flags */
    OSA_EventClear(&spiState->event, kSpiDmaTransferDone);

    errorStatus = SPI_DRV_DmaSlaveStartTransfer(instance);
    if (errorStatus != kStatus_SPI_Success)
    {
        return errorStatus;
    }

    /* As this is a synchronous transfer, wait until the transfer is complete. */
    osa_status_t syncStatus;

    do
    {
        syncStatus = OSA_EventWait(&spiState->event, kSpiDmaTransferDone, true, timeout, &setFlags);
    }while(syncStatus == kStatus_OSA_Idle);

    if (syncStatus != kStatus_OSA_Success)
    {
        /* Abort the transfer so it doesn't continue unexpectedly. */
        SPI_DRV_DmaSlaveAbortTransfer(instance);

        errorStatus = kStatus_SPI_Timeout;
    }

    return errorStatus;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_DRV_DmaSlaveStartTransfer
 * Description   : Starts the transfer with information passed.
 *
 *END**************************************************************************/
static spi_status_t SPI_DRV_DmaSlaveStartTransfer(uint32_t instance)
{
    spi_dma_slave_state_t * spiState = (spi_dma_slave_state_t *)g_spiStatePtr[instance];

    /* For temporarily storing DMA register channel */
    void * param;
    SPI_Type *base = g_spiBase[instance];
    uint32_t transferSizeInBytes;  /* DMA transfer size in bytes */

    /* Initialize s_byteToSend */
    s_byteToSend = spiState->dummyPattern;

    /* If the transfer count is zero, then return immediately. */
    if (spiState->remainingSendByteCount == 0)
    {
        /* Signal the synchronous completion object if the transfer wasn't async.
         * Otherwise, when we return the the sync function we'll get stuck in the sync wait loop.
         */
        if (spiState->isSync)
        {
            /* Signal the synchronous completion object */
            OSA_EventSet(&spiState->event, kSpiDmaTransferDone);
        }
        return kStatus_SPI_Success;
    }

    /* In order to flush any remaining data in the shift register, disable then enable the SPI */
    SPI_HAL_Disable(base);
    SPI_HAL_Enable(base);

    /* First, set the DMA transfer size in bytes */
#if FSL_FEATURE_SPI_16BIT_TRANSFERS
    if (SPI_HAL_Get8or16BitMode(base) == kSpi16BitMode)
    {
        transferSizeInBytes = 2;
        /* If bits/frame > 8, meaning 2 bytes, then the transfer byte count must not be an odd
         * count. If so, drop the last odd byte. This odd byte will be transferred in when dma
         * completed
         */
        if (spiState->remainingSendByteCount % 2 != 0)
        {
            spiState->remainingSendByteCount ++;
            spiState->remainingReceiveByteCount --;
            spiState->hasExtraByte = true;
        }
        else
        {
            spiState->hasExtraByte = false;
        }
    }
    else
    {
        transferSizeInBytes = 1;
    }
#else
    transferSizeInBytes = 1;
#endif /* FSL_FEATURE_SPI_16BIT_TRANSFERS */

    param = (void *)(instance);     /* For DMA callback, set "param" as the SPI instance number */

    /* Save information about the transfer for use by the ISR. */
    spiState->isTransferInProgress = true;

    /************************************************************************************
     * Set up the RX DMA channel Transfer Control Descriptor (TCD)
     * Note, if there is no receive buffer (if user passes in NULL), then bypass RX DMA
     * set up.
     ************************************************************************************/
    /* If no receive buffer then disable incrementing the destination and set the destination
     * to a temporary location
     */
    if ((spiState->remainingReceiveByteCount > 0) || (spiState->hasExtraByte))
    {
        uint32_t receiveSize = spiState->remainingReceiveByteCount;
        if ((!spiState->receiveBuffer) || (!spiState->remainingReceiveByteCount))
        {
            if (!spiState->remainingReceiveByteCount)
            {
                /* If receive count is 0, always receive 1 frame (2 bytes) */
                receiveSize = 2;
            }
            /* Set up this channel's control which includes enabling the DMA interrupt */
            DMA_DRV_ConfigTransfer(&spiState->dmaReceive,
                                   kDmaPeripheralToPeripheral,
                                   transferSizeInBytes,
                                   SPI_HAL_GetDataRegAddr(base), /* src is data register */
                                   (uint32_t)(&s_rxBuffIfNull), /* dest is temporary location */
                                   (uint32_t)(receiveSize));
        }
        else
        {
            /* Set up this channel's control which includes enabling the DMA interrupt */
            DMA_DRV_ConfigTransfer(&spiState->dmaReceive,
                                   kDmaPeripheralToMemory,
                                   transferSizeInBytes,
                                   SPI_HAL_GetDataRegAddr(base), /* src is data register */
                                   (uint32_t)(spiState->receiveBuffer), /* dest is rx buffer */
                                   (uint32_t)(receiveSize));
        }
        /* Destination size is only one byte */
        DMA_DRV_SetDestTransferSize(&spiState->dmaReceive, 1U);

        /* Enable the DMA peripheral request */
        DMA_DRV_StartChannel(&spiState->dmaReceive);

        /* Register callback for DMA interrupt */
        DMA_DRV_RegisterCallback(&spiState->dmaReceive, SPI_DRV_DmaSlaveCallback, param);
    }

    /************************************************************************************
     * Set up the TX DMA channel Transfer Control Descriptor (TCD)
     * Note, if there is no source buffer (if user passes in NULL), then send zeros
     ************************************************************************************/
    /* Per the reference manual, before enabling the SPI transmit DMA request, we first need
     * to read the status register and then write to the SPI data register.  Afterwards, we need
     * to decrement the sendByteCount and perform other driver maintenance functions.
     */
    /* Read the SPI Status register */
    SPI_HAL_IsTxBuffEmptyPending(base);

    /* Start the transfer by writing the first byte/word to the SPI data register.
     * If a send buffer was provided, the byte/word comes from there. Otherwise we just send zeros.
     */
#if FSL_FEATURE_SPI_16BIT_TRANSFERS
    if (transferSizeInBytes == 2) /* 16-bit transfers for SPI16 module */
    {
        if (spiState->sendBuffer)
        {
            s_byteToSend = *(spiState->sendBuffer);
            SPI_HAL_WriteDataLow(base, s_byteToSend);
            ++spiState->sendBuffer;

            s_byteToSend = *(spiState->sendBuffer);
            SPI_HAL_WriteDataHigh(base, s_byteToSend);
            ++spiState->sendBuffer;
        }
        else  /* Else, if no send buffer, write zeros */
        {
            SPI_HAL_WriteDataLow(base, s_byteToSend);
            SPI_HAL_WriteDataHigh(base, s_byteToSend);
        }
        spiState->remainingSendByteCount -= 2;  /* Decrement the send byte count by 2 */
    }
    else /* 8-bit transfers for SPI16 module */
    {
        if (spiState->sendBuffer)
        {
            s_byteToSend = *(spiState->sendBuffer);
            ++spiState->sendBuffer;
        }
        SPI_HAL_WriteDataLow(base, s_byteToSend);  /* If no send buffer, s_byteToSend=0 */
        --spiState->remainingSendByteCount; /* Decrement the send byte count for use in DMA setup */
    }
#else
    /* For SPI modules that do not support 16-bit transfers */
    if (spiState->sendBuffer)
    {
        s_byteToSend = *(spiState->sendBuffer);
        ++spiState->sendBuffer;
    }
    SPI_HAL_WriteData(base, s_byteToSend); /* If no send buffer, s_byteToSend=0 */
    --spiState->remainingSendByteCount; /* Decrement the send byte count for use in DMA setup */
#endif /* FSL_FEATURE_SPI_16BIT_TRANSFERS */

    /* If there are no more bytes to send then return without setting up the TX DMA channel.
     * Else, set up the TX DMA channel and enable the TX DMA request.
     */
    if (!spiState->remainingSendByteCount) /* No more bytes to send */
    {
        if ((spiState->remainingReceiveByteCount) || (spiState->hasExtraByte))
        {
            /* Enable the RX DMA channel request now */
            SPI_HAL_SetRxDmaCmd(base, true);
            return kStatus_SPI_Success;
        }
        else    /* If RX DMA chan not setup then enable the interrupt to get the received byte */
        {
            SPI_HAL_SetIntMode(base, kSpiTxEmptyInt, true);
            return kStatus_SPI_Success;
        }
    }
    else  /* Since there are more bytes to send, set up the TX DMA channel */
    {
        /* If there is a send buffer, data comes from there, else send 0 */
        if (spiState->sendBuffer)
        {
            /* Set up this channel's control which includes enabling the DMA interrupt */
            DMA_DRV_ConfigTransfer(&spiState->dmaTransmit, kDmaMemoryToPeripheral,
                                   transferSizeInBytes,
                                   (uint32_t)(spiState->sendBuffer),
                                   SPI_HAL_GetDataRegAddr(base),
                                   (uint32_t)(spiState->remainingSendByteCount));
        }
        else /* Configure TX DMA channel to send zeros */
        {
            /* Set up this channel's control which includes enabling the DMA interrupt */
            DMA_DRV_ConfigTransfer(&spiState->dmaTransmit, kDmaPeripheralToPeripheral,
                                   transferSizeInBytes,
                                   (uint32_t)(&s_byteToSend),
                                   SPI_HAL_GetDataRegAddr(base),
                                   (uint32_t)(spiState->remainingSendByteCount));
        }
        /* Source size is only one byte */
        DMA_DRV_SetSourceTransferSize(&spiState->dmaTransmit, 1U);

        /* Enable the SPI TX DMA Request */
        SPI_HAL_SetTxDmaCmd(base, true);

        /* Enable the SPI RX DMA request also. */
        SPI_HAL_SetRxDmaCmd(base, true);

        /* Enable the DMA peripheral request */
        DMA_DRV_StartChannel(&spiState->dmaTransmit);
    }

    return kStatus_SPI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_DRV_DmaSlaveCompleteTransfer
 * Description   : Finish up a transfer.
 * Cleans up after a transfer is complete. Interrupts are disabled, and the SPI module
 * is disabled. This is not a public API as it is called from other driver functions.
 *
 *END**************************************************************************/
static void SPI_DRV_DmaSlaveCompleteTransfer(uint32_t instance)
{
    spi_dma_slave_state_t * spiState = (spi_dma_slave_state_t *)g_spiStatePtr[instance];

    SPI_Type *base = g_spiBase[instance];

    /* Disable DMA requests and interrupts. */
    SPI_HAL_SetRxDmaCmd(base, false);
    SPI_HAL_SetTxDmaCmd(base, false);
    SPI_HAL_SetIntMode(base, kSpiTxEmptyInt, false);

    /* Stop DMA channels */
    DMA_DRV_StopChannel(&spiState->dmaTransmit);
    DMA_DRV_StopChannel(&spiState->dmaReceive);

    /* Disable interrupts */
    SPI_HAL_SetIntMode(base, kSpiRxFullAndModfInt, false);

#if FSL_FEATURE_SPI_16BIT_TRANSFERS
    if (g_spiFifoSize[instance] != 0)
    {
        /* Now disable the SPI FIFO interrupts */
        SPI_HAL_SetFifoIntCmd(base, kSpiTxFifoNearEmptyInt, false);
        SPI_HAL_SetFifoIntCmd(base, kSpiRxFifoNearFullInt, false);
    }

    /* Receive extra byte if remaining receive byte is 0 */
    if ((spiState->hasExtraByte) && (!spiState->remainingReceiveByteCount) &&
        (spiState->receiveBuffer))
    {
        spiState->receiveBuffer[spiState->remainingReceiveByteCount] =
                                                                 SPI_HAL_ReadDataLow(base);
    }
#endif /* FSL_FEATURE_SPI_16BIT_TRANSFERS */

    if (spiState->isSync)
    {
        /* Signal the synchronous completion object */
        OSA_EventSet(&spiState->event, kSpiDmaTransferDone);
    }

    /* The transfer is complete, update the state structure */
    spiState->isTransferInProgress = false;
    spiState->status = kStatus_SPI_Success;
    spiState->errorCount = 0;
    spiState->sendBuffer = NULL;
    spiState->receiveBuffer = NULL;
    spiState->remainingSendByteCount = 0;
    spiState->remainingReceiveByteCount = 0;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_DRV_DmaSlaveAbortTransfer
 * Description   : Stop the transfer if it is in progress
 *
 *END**************************************************************************/
spi_status_t SPI_DRV_DmaSlaveAbortTransfer(uint32_t instance)
{
    spi_dma_slave_state_t * spiState = (spi_dma_slave_state_t *)g_spiStatePtr[instance];

    /* Check instance is valid or not */
    assert(instance < SPI_INSTANCE_COUNT);

    /* Check driver is initialized */
    if (!spiState)
    {
        return kStatus_SPI_NonInit;
    }

    /* Check transfer is in progress */
    if (!spiState->isTransferInProgress)
    {
        return kStatus_SPI_NoTransferInProgress;
    }

    /* Stop transfer */
    SPI_DRV_DmaSlaveCompleteTransfer(instance);

    return kStatus_SPI_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_DRV_DmaSlaveGetTransferStatus
 * Description   : Returns whether the previous transfer finished.
 * When performing an a-sync transfer, the user can call this function to ascertain the state of the
 * current transfer: in progress (or busy) or complete (success). In addition, if the transfer
 * is still in progress, the user can get the number of words that have been
 * transferred up to now.
 *
 *END**************************************************************************/
spi_status_t SPI_DRV_DmaSlaveGetTransferStatus(uint32_t instance,
                                            uint32_t * framesTransferred)
{
    spi_dma_slave_state_t * spiState = (spi_dma_slave_state_t *)g_spiStatePtr[instance];

    /* Fill in the bytes transferred. */
    if (framesTransferred)
    {
        *framesTransferred = spiState->remainingSendByteCount -
                            DMA_DRV_GetUnfinishedBytes(&spiState->dmaTransmit);
    }

    return (spiState->isTransferInProgress ? kStatus_SPI_Busy : kStatus_SPI_Success);
}


/*FUNCTION**********************************************************************
 *
 * Function Name : SPI_DRV_DmaSlaveIRQHandler
 * Description   : Interrupt handler for SPI master mode.
 * This handler is used when the hasExtraByte flag is set to retrieve the received last byte.
 *
 *END**************************************************************************/
void SPI_DRV_DmaSlaveIRQHandler(uint32_t instance)
{
#if FSL_FEATURE_SPI_16BIT_TRANSFERS
    /* instantiate local variable of type spi_master_state_t and point to global state */
    spi_dma_slave_state_t * spiDmaState = (spi_dma_slave_state_t *)g_spiStatePtr[instance];

    SPI_Type *base = g_spiBase[instance];

    /* If the SPI module contains a FIFO (and if it is enabled), check the FIFO empty flag */
    if ((g_spiFifoSize[instance] != 0) && (SPI_HAL_GetFifoCmd(base)))
    {
        if (SPI_HAL_GetFifoStatusFlag(base, kSpiRxFifoEmpty) == 0)
        {
            /* If there is a receive buffer, copy the final byte from the SPI data register
             *  to the receive buffer
             */
            if (spiDmaState->receiveBuffer)
            {
                spiDmaState->receiveBuffer[spiDmaState->remainingReceiveByteCount] =
                                                              SPI_HAL_ReadDataLow(base);
            }
            /* Else, read out the data register and throw away the bytes read */
            else
            {
                /* Read and throw away the lower data buffer to clear it out */
                s_rxBuffIfNull = SPI_HAL_ReadDataLow(base);
            }
            /* Read and throw away the upper data buffer to clear it out */
            s_rxBuffIfNull = SPI_HAL_ReadDataHigh(base);

            SPI_DRV_DmaSlaveCompleteTransfer(instance);
        }
    }
    else /* Check the read pending flag */
    {
        if (SPI_HAL_IsReadBuffFullPending(base) == 1)
        {
            /* If there is a receive buffer, copy the final byte from the SPI data register
             *  to the receive buffer
             */
            if (spiDmaState->receiveBuffer)
            {
                spiDmaState->receiveBuffer[spiDmaState->remainingReceiveByteCount] =
                                                              SPI_HAL_ReadDataLow(base);
            }
            /* Else, read out the data register and throw away the bytes read */
            else
            {
                /* Read and throw away the lower data buffer to clear it out */
                s_rxBuffIfNull = SPI_HAL_ReadDataLow(base);
            }
            /* Read and throw away the upper data buffer to clear it out */
            s_rxBuffIfNull = SPI_HAL_ReadDataHigh(base);
            SPI_DRV_DmaSlaveCompleteTransfer(instance);
        }
    }
#endif /* FSL_FEATURE_SPI_16BIT_TRANSFERS */
}

#endif /* FSL_FEATURE_SOC_SPI_COUNT */
/*******************************************************************************
 * EOF
 ******************************************************************************/

