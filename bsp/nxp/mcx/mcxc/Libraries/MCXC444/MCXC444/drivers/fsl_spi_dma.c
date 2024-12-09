/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2017, 2020 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_spi_dma.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.spi_dma"
#endif

/*<! Structure definition for spi_dma_private_handle_t. The structure is private. */
typedef struct _spi_dma_private_handle
{
    SPI_Type *base;
    spi_dma_handle_t *handle;
} spi_dma_private_handle_t;

/*! @brief SPI transfer state, which is used for SPI transactiaonl APIs' internal state. */
enum _spi_dma_states_t
{
    kSPI_Idle = 0x0, /*!< SPI is idle state */
    kSPI_Busy        /*!< SPI is busy tranferring data. */
};

/*<! Private handle only used for internally. */
static spi_dma_private_handle_t s_dmaPrivateHandle[FSL_FEATURE_SOC_SPI_COUNT];

/* If the RX data is not required, save it to this variable. */
static uint16_t s_spiDmaRxDrop;
/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief DMA callback function for SPI send transfer.
 *
 * @param handle DMA handle pointer.
 * @param userData User data for DMA callback function.
 */
static void SPI_TxDMACallback(dma_handle_t *handle, void *userData);

/*!
 * @brief DMA callback function for SPI receive transfer.
 *
 * @param handle DMA handle pointer.
 * @param userData User data for DMA callback function.
 */
static void SPI_RxDMACallback(dma_handle_t *handle, void *userData);

/*******************************************************************************
 * Code
 ******************************************************************************/
static void SPI_TxDMACallback(dma_handle_t *handle, void *userData)
{
    spi_dma_private_handle_t *privHandle = (spi_dma_private_handle_t *)userData;
    spi_dma_handle_t *spiHandle          = privHandle->handle;
    SPI_Type *base                       = privHandle->base;

    /* Disable Tx dma */
    SPI_EnableDMA(base, (uint8_t)kSPI_TxDmaEnable, false);

    /* Stop DMA transfer */
    DMA_StopTransfer(spiHandle->txHandle);

    /* change the state */
    spiHandle->txInProgress = false;

    /* All finished, call the callback */
    if ((spiHandle->txInProgress == false) && (spiHandle->rxInProgress == false))
    {
        spiHandle->state = (uint32_t)kSPI_Idle;
        if (spiHandle->callback != NULL)
        {
            (spiHandle->callback)(base, spiHandle, kStatus_Success, spiHandle->userData);
        }
    }
}

static void SPI_RxDMACallback(dma_handle_t *handle, void *userData)
{
    spi_dma_private_handle_t *privHandle = (spi_dma_private_handle_t *)userData;
    spi_dma_handle_t *spiHandle          = privHandle->handle;
    SPI_Type *base                       = privHandle->base;

    /* Disable Tx dma */
    SPI_EnableDMA(base, (uint8_t)kSPI_RxDmaEnable, false);

    /* Stop DMA transfer */
    DMA_StopTransfer(spiHandle->rxHandle);

    /* change the state */
    spiHandle->rxInProgress = false;

    /* All finished, call the callback */
    if ((spiHandle->txInProgress == false) && (spiHandle->rxInProgress == false))
    {
        spiHandle->state = (uint32_t)kSPI_Idle;
        if (spiHandle->callback != NULL)
        {
            (spiHandle->callback)(base, spiHandle, kStatus_Success, spiHandle->userData);
        }
    }
}

/*!
 * brief Initialize the SPI master DMA handle.
 *
 * This function initializes the SPI master DMA handle which can be used for other SPI master transactional APIs.
 * Usually, for a specified SPI instance, user need only call this API once to get the initialized handle.
 *
 * param base SPI peripheral base address.
 * param handle SPI handle pointer.
 * param callback User callback function called at the end of a transfer.
 * param userData User data for callback.
 * param txHandle DMA handle pointer for SPI Tx, the handle shall be static allocated by users.
 * param rxHandle DMA handle pointer for SPI Rx, the handle shall be static allocated by users.
 */
void SPI_MasterTransferCreateHandleDMA(SPI_Type *base,
                                       spi_dma_handle_t *handle,
                                       spi_dma_callback_t callback,
                                       void *userData,
                                       dma_handle_t *txHandle,
                                       dma_handle_t *rxHandle)
{
    assert(handle != NULL);
    uint32_t instance = SPI_GetInstance(base);

    /* Zero the handle */
    (void)memset(handle, 0, sizeof(*handle));

    /* Set spi base to handle */
    handle->txHandle = txHandle;
    handle->rxHandle = rxHandle;
    handle->callback = callback;
    handle->userData = userData;

    /* Set SPI state to idle */
    handle->state = (uint32_t)kSPI_Idle;

    /* Set handle to global state */
    s_dmaPrivateHandle[instance].base   = base;
    s_dmaPrivateHandle[instance].handle = handle;

/* Compute internal state */
#if defined(FSL_FEATURE_SPI_16BIT_TRANSFERS) && (FSL_FEATURE_SPI_16BIT_TRANSFERS)
    handle->bytesPerFrame = ((base->C2 & SPI_C2_SPIMODE_MASK) >> SPI_C2_SPIMODE_SHIFT) + 1U;
#else
    handle->bytesPerFrame = 1U;
#endif /* FSL_FEATURE_SPI_16BIT_TRANSFERS */

#if defined(FSL_FEATURE_SPI_HAS_FIFO) && (FSL_FEATURE_SPI_HAS_FIFO)
    /* If using DMA, disable FIFO, as the FIFO may cause data loss if the data size is not integer
       times of 2bytes. As SPI cannot set watermark to 0, only can set to 1/2 FIFO size or 3/4 FIFO
       size. */
    if (FSL_FEATURE_SPI_FIFO_SIZEn(base) != 0)
    {
        base->C3 &= (uint8_t)(~SPI_C3_FIFOMODE_MASK);
    }

#endif /* FSL_FEATURE_SPI_HAS_FIFO */

    /* Install callback for Tx dma channel */
    DMA_SetCallback(handle->txHandle, SPI_TxDMACallback, &s_dmaPrivateHandle[instance]);
    DMA_SetCallback(handle->rxHandle, SPI_RxDMACallback, &s_dmaPrivateHandle[instance]);
}

/*!
 * brief Perform a non-blocking SPI transfer using DMA.
 *
 * note This interface returned immediately after transfer initiates, users should call
 * SPI_GetTransferStatus to poll the transfer status to check whether SPI transfer finished.
 *
 * param base SPI peripheral base address.
 * param handle SPI DMA handle pointer.
 * param xfer Pointer to dma transfer structure.
 * retval kStatus_Success Successfully start a transfer.
 * retval kStatus_InvalidArgument Input argument is invalid.
 * retval kStatus_SPI_Busy SPI is not idle, is running another transfer.
 */
status_t SPI_MasterTransferDMA(SPI_Type *base, spi_dma_handle_t *handle, spi_transfer_t *xfer)
{
    assert((handle != NULL) && (xfer != NULL));

    dma_transfer_config_t config = {0};

    /* Check if the device is busy */
    if (handle->state == (uint32_t)kSPI_Busy)
    {
        return (status_t)kStatus_SPI_Busy;
    }

    /* Check if input parameter invalid */
    if (((xfer->txData == NULL) && (xfer->rxData == NULL)) || (xfer->dataSize == 0U))
    {
        return (status_t)kStatus_InvalidArgument;
    }

    /* Disable SPI and then enable it, this is used to clear S register*/
    SPI_Enable(base, false);
    SPI_Enable(base, true);

    /* Configure DMA transfer. */
    if (handle->bytesPerFrame == 1U)
    {
        config.srcSize  = kDMA_Transfersize8bits;
        config.destSize = kDMA_Transfersize8bits;
    }
    else
    {
        config.srcSize  = kDMA_Transfersize16bits;
        config.destSize = kDMA_Transfersize16bits;
    }
    config.transferSize = xfer->dataSize;

    /* Configure tx transfer DMA */
    config.destAddr            = SPI_GetDataRegisterAddress(base);
    config.enableDestIncrement = false;
    /* Configure DMA channel */
    if (xfer->txData != NULL)
    {
        config.enableSrcIncrement = true;
        config.srcAddr            = (uint32_t)(xfer->txData);
    }
    else
    {
        /* Disable the source increasement and source set to dummyData */
        config.enableSrcIncrement = false;
        config.srcAddr            = (uint32_t)(&g_spiDummyData[SPI_GetInstance(base)]);
    }
    (void)DMA_SubmitTransfer(handle->txHandle, &config, 1U);

    /*
     * Configure rx transfer DMA.
     * To make sure TX data has been sent out to bus, SPI DMA driver
     * checks the RX data count. When the RX data reaches the
     * desired count, it means TX data has been sent out to bus.
     * So DMA RX is enabled even when RX data is not desired,
     * and the data is saved to variable and dropped.
     */
    config.srcAddr            = SPI_GetDataRegisterAddress(base);
    config.enableSrcIncrement = false;

    if (xfer->rxData != NULL)
    {
        config.destAddr            = (uint32_t)(xfer->rxData);
        config.enableDestIncrement = true;
    }
    else
    {
        config.destAddr            = (uint32_t)(&s_spiDmaRxDrop);
        config.enableDestIncrement = false;
    }
    (void)DMA_SubmitTransfer(handle->rxHandle, &config, (uint32_t)kDMA_EnableInterrupt);

    /* Change the state of handle */
    handle->transferSize = xfer->dataSize;
    handle->state        = (uint32_t)kSPI_Busy;

    /* Start Rx transfer */
    handle->rxInProgress = true;
    SPI_EnableDMA(base, (uint8_t)kSPI_RxDmaEnable, true);
    DMA_StartTransfer(handle->rxHandle);

    /* Always start Tx transfer */
    handle->txInProgress = true;
    SPI_EnableDMA(base, (uint8_t)kSPI_TxDmaEnable, true);
    DMA_StartTransfer(handle->txHandle);

    return kStatus_Success;
}

/*!
 * brief Get the transferred bytes for SPI slave DMA.
 *
 * param base SPI peripheral base address.
 * param handle SPI DMA handle pointer.
 * param count Transferred bytes.
 * retval kStatus_SPI_Success Succeed get the transfer count.
 * retval kStatus_NoTransferInProgress There is not a non-blocking transaction currently in progress.
 */
status_t SPI_MasterTransferGetCountDMA(SPI_Type *base, spi_dma_handle_t *handle, size_t *count)
{
    assert(handle != NULL);

    status_t status = kStatus_Success;

    if (handle->state != (uint32_t)kSPI_Busy)
    {
        status = kStatus_NoTransferInProgress;
    }
    else
    {
        if (handle->rxInProgress)
        {
            *count = handle->transferSize - DMA_GetRemainingBytes(handle->rxHandle->base, handle->rxHandle->channel);
        }
        else
        {
            *count = handle->transferSize - DMA_GetRemainingBytes(handle->txHandle->base, handle->txHandle->channel);
        }
    }

    return status;
}

/*!
 * brief Abort a SPI transfer using DMA.
 *
 * param base SPI peripheral base address.
 * param handle SPI DMA handle pointer.
 */
void SPI_MasterTransferAbortDMA(SPI_Type *base, spi_dma_handle_t *handle)
{
    assert(handle != NULL);

    /* Disable dma */
    DMA_StopTransfer(handle->txHandle);
    DMA_StopTransfer(handle->rxHandle);

    /* Disable DMA enable bit */
    SPI_EnableDMA(base, (uint8_t)kSPI_DmaAllEnable, false);

    /* Set the handle state */
    handle->txInProgress = false;
    handle->rxInProgress = false;
    handle->state        = (uint32_t)kSPI_Idle;
}
