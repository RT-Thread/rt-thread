/*
 * Copyright 2021-2023 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_flexspi_edma.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.flexspi_dma3"
#endif

/*<! Structure definition for flexspi_edma_private_handle_t. The structure is private. */
typedef struct _flexspi_edma_private_handle
{
    FLEXSPI_Type *base;
    flexspi_edma_handle_t *handle;
} flexspi_edma_private_handle_t;

/* FLEXSPI EDMA transfer handle, _flexspi_edma_tansfer_states. */
enum
{
    kFLEXSPI_Idle, /* FLEXSPI Bus idle. */
    kFLEXSPI_Busy  /* FLEXSPI Bus busy. */
};

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief Pointers to flexspi bases for each instance. */
static FLEXSPI_Type *const s_flexspiBases[] = FLEXSPI_BASE_PTRS;

/*<! Private handle only used for internally. */
static flexspi_edma_private_handle_t s_edmaPrivateHandle[ARRAY_SIZE(s_flexspiBases)];

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
static void FLEXSPI_EDMAMemset(void *src, uint8_t value, size_t length);

/*!
 * @brief FLEXSPI EDMA transfer finished callback function.
 *
 * This function is called when FLEXSPI EDMA transfer finished. It disables the FLEXSPI
 * TX/RX EDMA request and sends status to FLEXSPI callback.
 *
 * @param handle The EDMA handle.
 * @param param Callback function parameter.
 */
static void FLEXSPI_TransferEDMACallback(edma_handle_t *handle, void *param, bool transferDone, uint32_t tcds);

/*******************************************************************************
 * Code
 ******************************************************************************/
/* To avoid compiler opitimizing this API into memset() in library. */
#if defined(__ICCARM__)
#pragma optimize = none
#endif /* defined(__ICCARM__) */
static void FLEXSPI_EDMAMemset(void *src, uint8_t value, size_t length)
{
    assert(src != NULL);
    uint8_t *p = src;

    for (uint32_t i = 0U; i < length; i++)
    {
        *p = value;
        p++;
    }
}

static uint8_t FLEXSPI_CalculatePower(uint8_t value)
{
    uint8_t power = 0;
    while (value >> 1 != 0U)
    {
        power++;
        value = value >> 1;
    }

    return power;
}
static void FLEXSPI_TransferEDMACallback(edma_handle_t *handle, void *param, bool transferDone, uint32_t tcds)
{
    flexspi_edma_private_handle_t *flexspiPrivateHandle = (flexspi_edma_private_handle_t *)param;

    /* Avoid warning for unused parameters. */
    handle = handle;
    tcds   = tcds;

    if (transferDone)
    {
        /* Wait for bus idle. */
        while (!FLEXSPI_GetBusIdleStatus(flexspiPrivateHandle->base))
        {
        }
        /* Disable transfer. */
        FLEXSPI_TransferAbortEDMA(flexspiPrivateHandle->base, flexspiPrivateHandle->handle);

        if (flexspiPrivateHandle->handle->completionCallback != NULL)
        {
            flexspiPrivateHandle->handle->completionCallback(flexspiPrivateHandle->base, flexspiPrivateHandle->handle,
                                                             kStatus_Success, flexspiPrivateHandle->handle->userData);
        }
    }
}

/*!
 * brief Initializes the FLEXSPI handle for transfer which is used in transactional functions and set the callback.
 *
 * param base FLEXSPI peripheral base address
 * param handle Pointer to flexspi_edma_handle_t structure
 * param callback FLEXSPI callback, NULL means no callback.
 * param userData User callback function data.
 * param txDmaHandle User requested DMA handle for TX DMA transfer.
 * param rxDmaHandle User requested DMA handle for RX DMA transfer.
 */
void FLEXSPI_TransferCreateHandleEDMA(FLEXSPI_Type *base,
                                      flexspi_edma_handle_t *handle,
                                      flexspi_edma_callback_t callback,
                                      void *userData,
                                      edma_handle_t *txDmaHandle,
                                      edma_handle_t *rxDmaHandle)
{
    assert(handle);

    uint32_t instance = FLEXSPI_GetInstance(base);

    s_edmaPrivateHandle[instance].base   = base;
    s_edmaPrivateHandle[instance].handle = handle;

    (void)FLEXSPI_EDMAMemset(handle, 0, sizeof(*handle));

    handle->state       = kFLEXSPI_Idle;
    handle->txDmaHandle = txDmaHandle;
    handle->rxDmaHandle = rxDmaHandle;
    handle->nsize       = kFLEXPSI_EDMAnSize1Bytes;

    handle->completionCallback = callback;
    handle->userData           = userData;
}

/*!
 * brief Update FLEXSPI EDMA transfer source data transfer size(SSIZE) and destination data transfer size(DSIZE).
 *
 * param base FLEXSPI peripheral base address
 * param handle Pointer to flexspi_edma_handle_t structure
 * param nsize FLEXSPI DMA transfer data transfer size(SSIZE/DSIZE), by default the size is
 * kFLEXPSI_EDMAnSize1Bytes(one byte).
 * see flexspi_edma_transfer_nsize_t               .
 */
void FLEXSPI_TransferUpdateSizeEDMA(FLEXSPI_Type *base,
                                    flexspi_edma_handle_t *handle,
                                    flexspi_edma_transfer_nsize_t nsize)
{
    handle->nsize = nsize;
}

/*!
 * brief Transfers FLEXSPI data using an eDMA non-blocking method.
 *
 * This function writes/receives data to/from the FLEXSPI transmit/receive FIFO. This function is non-blocking.
 * param base FLEXSPI peripheral base address.
 * param handle Pointer to flexspi_edma_handle_t structure
 * param xfer FLEXSPI transfer structure.
 * retval kStatus_FLEXSPI_Busy     FLEXSPI is busy transfer.
 * retval kStatus_InvalidArgument  The watermark configuration is invalid, the watermark should be power of
                                    2 to do successfully EDMA transfer.
 * retval kStatus_Success          FLEXSPI successfully start edma transfer.
 */
status_t FLEXSPI_TransferEDMA(FLEXSPI_Type *base, flexspi_edma_handle_t *handle, flexspi_transfer_t *xfer)
{
    uint32_t configValue = 0;
    status_t result      = kStatus_Success;
    edma_transfer_config_t xferConfig;
    uint32_t instance = FLEXSPI_GetInstance(base);
    uint8_t power     = 0;

    assert(handle);
    assert(xfer);

    /* Check if the FLEXSPI bus is idle - if not return busy status. */
    if (handle->state != (uint32_t)kFLEXSPI_Idle)
    {
        result = kStatus_FLEXSPI_Busy;
    }
    else
    {
        handle->transferSize = xfer->dataSize;
        handle->state        = kFLEXSPI_Busy;

        /* Clear sequence pointer before sending data to external devices. */
        base->FLSHCR2[xfer->port] |= FLEXSPI_FLSHCR2_CLRINSTRPTR_MASK;

        /* Clear former pending status before start this transfer. */
        base->INTR |= FLEXSPI_INTR_AHBCMDERR_MASK | FLEXSPI_INTR_IPCMDERR_MASK | FLEXSPI_INTR_AHBCMDGE_MASK |
                      FLEXSPI_INTR_IPCMDGE_MASK;

        /* Configure base address. */
        base->IPCR0 = xfer->deviceAddress;

        /* Reset fifos. */
        base->IPTXFCR |= FLEXSPI_IPTXFCR_CLRIPTXF_MASK;
        base->IPRXFCR |= FLEXSPI_IPRXFCR_CLRIPRXF_MASK;

        /* Configure data size. */
        if ((xfer->cmdType == kFLEXSPI_Read) || (xfer->cmdType == kFLEXSPI_Write))
        {
            configValue = FLEXSPI_IPCR1_IDATSZ(xfer->dataSize);
        }

        /* Configure sequence ID. */
        configValue |= FLEXSPI_IPCR1_ISEQID(xfer->seqIndex) | FLEXSPI_IPCR1_ISEQNUM((uint32_t)xfer->SeqNumber - 1U);
        base->IPCR1 = configValue;
    }

    if ((xfer->cmdType == kFLEXSPI_Write) || (xfer->cmdType == kFLEXSPI_Config))
    {
        handle->count = (uint8_t)((base->IPTXFCR & FLEXSPI_IPTXFCR_TXWMRK_MASK) >> FLEXSPI_IPTXFCR_TXWMRK_SHIFT) + 1U;

        if (xfer->dataSize < 8U * (uint32_t)handle->count)
        {
            handle->nbytes = (uint8_t)xfer->dataSize;
        }
        else
        {
            /* Check the handle->count is power of 2 */
            if (((handle->count) & (handle->count - 1U)) != 0U)
            {
                return kStatus_InvalidArgument;
            }
            /* Store the initially configured eDMA minor byte transfer count into the FLEXSPI handle */
            handle->nbytes = (8U * handle->count);
        }

        power = FLEXSPI_CalculatePower(8U * handle->count);

        /* Prepare transfer. */
        EDMA_PrepareTransfer(&xferConfig, xfer->data, (uint32_t)handle->nsize,
                             (void *)(uint32_t *)FLEXSPI_GetTxFifoAddress(base), (uint32_t)handle->nsize,
                             (uint32_t)handle->nbytes, xfer->dataSize, kEDMA_MemoryToMemory);

        /* Submit transfer. */
        (void)EDMA_SubmitTransfer(handle->txDmaHandle, &xferConfig);
        EDMA_SetModulo(handle->txDmaHandle->base, handle->txDmaHandle->channel, kEDMA_ModuloDisable,
                       (edma_modulo_t)power);
        EDMA_SetCallback(handle->txDmaHandle, FLEXSPI_TransferEDMACallback,
                         &s_edmaPrivateHandle[FLEXSPI_GetInstance(base)]);
        EDMA_StartTransfer(handle->txDmaHandle);

        /* Enable FLEXSPI TX EDMA. */
        FLEXSPI_EnableTxDMA(base, true);

        /* Start Transfer. */
        base->IPCMD |= FLEXSPI_IPCMD_TRG_MASK;
    }
    else if (xfer->cmdType == kFLEXSPI_Read)
    {
        handle->count = (uint8_t)((base->IPRXFCR & FLEXSPI_IPRXFCR_RXWMRK_MASK) >> FLEXSPI_IPRXFCR_RXWMRK_SHIFT) + 1U;

        if (xfer->dataSize < 8U * (uint32_t)handle->count)
        {
            handle->nbytes = (uint8_t)xfer->dataSize;
        }
        else
        {
            /* Check the handle->count is power of 2 */
            if (((handle->count) & (handle->count - 1U)) != 0U)
            {
                return kStatus_InvalidArgument;
            }
            /* Store the initially configured eDMA minor byte transfer count into the FLEXSPI handle */
            handle->nbytes = (8U * handle->count);
        }

        power = FLEXSPI_CalculatePower(8U * handle->count);

        /* Prepare transfer. */
        EDMA_PrepareTransfer(&xferConfig, (void *)(uint32_t *)FLEXSPI_GetRxFifoAddress(base), (uint32_t)handle->nsize,
                             xfer->data, (uint32_t)handle->nsize, (uint32_t)handle->nbytes, xfer->dataSize,
                             kEDMA_MemoryToMemory);

        /* Submit transfer. */
        (void)EDMA_SubmitTransfer(handle->rxDmaHandle, &xferConfig);
        EDMA_SetModulo(handle->rxDmaHandle->base, handle->rxDmaHandle->channel, (edma_modulo_t)power,
                       kEDMA_ModuloDisable);
        EDMA_SetCallback(handle->rxDmaHandle, FLEXSPI_TransferEDMACallback, &s_edmaPrivateHandle[instance]);
        EDMA_StartTransfer(handle->rxDmaHandle);

        /* Enable FLEXSPI RX EDMA. */
        FLEXSPI_EnableRxDMA(base, true);

        /* Start Transfer. */
        base->IPCMD |= FLEXSPI_IPCMD_TRG_MASK;
    }
    else
    {
        /* Start Transfer. */
        base->IPCMD |= FLEXSPI_IPCMD_TRG_MASK;
        /* Wait for bus idle. */
        while (!FLEXSPI_GetBusIdleStatus(base))
        {
        }
        result = FLEXSPI_CheckAndClearError(base, base->INTR);

        handle->state = kFLEXSPI_Idle;

        if (handle->completionCallback != NULL)
        {
            handle->completionCallback(base, handle, result, handle->userData);
        }
    }

    return result;
}

/*!
 * brief Aborts the transfer data using eDMA.
 *
 * This function aborts the transfer data using eDMA.
 *
 * param base FLEXSPI peripheral base address.
 * param handle Pointer to flexspi_edma_handle_t structure
 */
void FLEXSPI_TransferAbortEDMA(FLEXSPI_Type *base, flexspi_edma_handle_t *handle)
{
    assert(handle);

    if ((base->IPTXFCR & FLEXSPI_IPTXFCR_TXDMAEN_MASK) != 0x00U)
    {
        FLEXSPI_EnableTxDMA(base, false);
        EDMA_AbortTransfer(handle->txDmaHandle);
    }

    if ((base->IPRXFCR & FLEXSPI_IPRXFCR_RXDMAEN_MASK) != 0x00U)
    {
        FLEXSPI_EnableRxDMA(base, false);
        EDMA_AbortTransfer(handle->rxDmaHandle);
    }

    handle->state = kFLEXSPI_Idle;
}

status_t FLEXSPI_TransferGetTransferCountEDMA(FLEXSPI_Type *base, flexspi_edma_handle_t *handle, size_t *count)
{
    assert(handle);
    assert(count);

    status_t result = kStatus_Success;

    if (handle->state != (uint32_t)kFLEXSPI_Busy)
    {
        result = kStatus_NoTransferInProgress;
    }
    else
    {
        if ((base->IPRXFCR & FLEXSPI_IPRXFCR_RXDMAEN_MASK) != 0x00U)
        {
            *count = (handle->transferSize -
                      (uint32_t)handle->nbytes *
                          EDMA_GetRemainingMajorLoopCount(handle->rxDmaHandle->base, handle->rxDmaHandle->channel));
        }
        else if ((base->IPTXFCR & FLEXSPI_IPTXFCR_TXDMAEN_MASK) != 0x00U)
        {
            *count = (handle->transferSize -
                      (uint32_t)handle->nbytes *
                          EDMA_GetRemainingMajorLoopCount(handle->txDmaHandle->base, handle->txDmaHandle->channel));
        }
        else
        {
            ; /* Intentional empty for MISRA C-2012 rule 15.7. */
        }
    }

    return result;
}
