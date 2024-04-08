/*
 * Copyright 2019-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_flexspi_dma.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.flexspi_dma"
#endif

/*<! Structure definition for flexspi_dma_private_handle_t. The structure is private. */
typedef struct _flexspi_dma_private_handle
{
    FLEXSPI_Type *base;
    flexspi_dma_handle_t *handle;
} flexspi_dma_private_handle_t;

/* FLEXSPI DMA transfer handle, _flexspi_dma_tansfer_states. */
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
static flexspi_dma_private_handle_t s_dmaPrivateHandle[ARRAY_SIZE(s_flexspiBases)];

#if defined(FSL_FEATURE_FLEXSPI_DMA_MULTIPLE_DES) && FSL_FEATURE_FLEXSPI_DMA_MULTIPLE_DES
/*<! Private DMA descriptor array used for internally to fix FLEXSPI+DMA ERRATA.
FLEXSPI.1: Using FLEXSPI register interface, TX buffer fill / RX buffer drain by DMA
with a single DMA descriptor cannot be performed. The link array consumes about
2K RAM consumption support FLEXSPI TX watermark starting from 8 bytes.*/
#define FLEXSPI_DMA_DES_COUNT 128U
#else
/*<! Private DMA descriptor array to support transfer size not multiple of watermark level byts.
The link array consumes 16 bytes consumption.*/
#define FLEXSPI_DMA_DES_COUNT 1U
#endif

#if defined(FSL_FEATURE_DMA_DESCRIPTOR_ALIGN_SIZEn)
#define FSL_FEATURE_DMA_DESCRIPTOR_ALIGN_SIZE                                            \
    ((FSL_FEATURE_DMA0_DESCRIPTOR_ALIGN_SIZE > FSL_FEATURE_DMA1_DESCRIPTOR_ALIGN_SIZE) ? \
         FSL_FEATURE_DMA0_DESCRIPTOR_ALIGN_SIZE :                                        \
         FSL_FEATURE_DMA1_DESCRIPTOR_ALIGN_SIZE)
#endif
#if defined(__ICCARM__)
#pragma data_alignment = FSL_FEATURE_DMA_DESCRIPTOR_ALIGN_SIZE
static dma_descriptor_t s_flexspiDes[FLEXSPI_DMA_DES_COUNT];
#elif defined(__CC_ARM) || defined(__ARMCC_VERSION)
__attribute__((
    aligned(FSL_FEATURE_DMA_DESCRIPTOR_ALIGN_SIZE))) static dma_descriptor_t s_flexspiDes[FLEXSPI_DMA_DES_COUNT];
#elif defined(__GNUC__)
__attribute__((
    aligned(FSL_FEATURE_DMA_DESCRIPTOR_ALIGN_SIZE))) static dma_descriptor_t s_flexspiDes[FLEXSPI_DMA_DES_COUNT];
#endif
/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief FLEXSPI DMA transfer finished callback function.
 *
 * This function is called when FLEXSPI DMA transfer finished. It disables the FLEXSPI
 * TX/RX DMA request and sends status to FLEXSPI callback.
 *
 * @param handle The DMA handle.
 * @param param Callback function parameter.
 */
static void FLEXSPI_TransferDMACallback(dma_handle_t *handle, void *param, bool transferDone, uint32_t tcds);

/*!
 * @brief FLEXSPI Write DMA data.
 *
 * This function is called in FLEXSPI DMA transfer. It configures Write DMA and prepare DMA data transfer.
 *
 * @param base FLEXSPI peripheral base address.
 * @param handle The DMA handle.
 * @param data pointer to data buffer which stores the transmit data
 * @param dataSize size for transmit data buffer .
 */
static status_t FLEXSPI_WriteDataDMA(FLEXSPI_Type *base, flexspi_dma_handle_t *handle, uint32_t *data, size_t dataSize);

/*!
 * @brief FLEXSPI Read DMA data.
 *
 * This function is called in FLEXSPI DMA transfer. It configures Read DMA and prepare DMA data transfer.
 *
 * @param base FLEXSPI peripheral base address.
 * @param handle The DMA handle.
 * @param data pointer to data buffer which stores the receive data
 * @param dataSize size for receive data buffer .
 */
static status_t FLEXSPI_ReadDataDMA(FLEXSPI_Type *base, flexspi_dma_handle_t *handle, uint32_t *data, size_t dataSize);
/*******************************************************************************
 * Code
 ******************************************************************************/
#if !(defined(FSL_FEATURE_FLEXSPI_DMA_MULTIPLE_DES) && FSL_FEATURE_FLEXSPI_DMA_MULTIPLE_DES)
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
#endif

static void FLEXSPI_TransferDMACallback(dma_handle_t *handle, void *param, bool transferDone, uint32_t tcds)
{
    flexspi_dma_private_handle_t *flexspiPrivateHandle = (flexspi_dma_private_handle_t *)param;

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
        FLEXSPI_TransferAbortDMA(flexspiPrivateHandle->base, flexspiPrivateHandle->handle);

        if (flexspiPrivateHandle->handle->completionCallback != NULL)
        {
            flexspiPrivateHandle->handle->completionCallback(flexspiPrivateHandle->base, flexspiPrivateHandle->handle,
                                                             kStatus_Success, flexspiPrivateHandle->handle->userData);
        }
    }
}

static status_t FLEXSPI_WriteDataDMA(FLEXSPI_Type *base, flexspi_dma_handle_t *handle, uint32_t *data, size_t dataSize)
{
    void *txFifoBase = (void *)(uint32_t *)FLEXSPI_GetTxFifoAddress(base);
    void *nextDesc   = NULL;
    dma_channel_trigger_t dmaTxTriggerConfig;
    dma_channel_config_t txChannelConfig;
    uint32_t bytesPerDes;
    uint8_t desCount;
    uint8_t remains;
    uint32_t srcInc;
    uint32_t dstInc;

    /* Source address interleave size */
    srcInc = kDMA_AddressInterleave1xWidth;
    /* Destination address interleave size */
    dstInc = kDMA_AddressInterleave1xWidth;

    /* Check the xfer->data start address follows the alignment */
    if (((uint32_t)data & ((uint32_t)handle->nsize - 1U)) != 0U)
    {
        return kStatus_InvalidArgument;
    }

    handle->count =
        8U * ((uint8_t)(((base->IPTXFCR & FLEXSPI_IPTXFCR_TXWMRK_MASK) >> FLEXSPI_IPTXFCR_TXWMRK_SHIFT) + 1U));

    /* Check the handle->count is power of 2 */
    if (((handle->count) & (handle->count - 1U)) != 0U)
    {
        return kStatus_InvalidArgument;
    }

#if defined(FSL_FEATURE_FLEXSPI_DMA_MULTIPLE_DES) && FSL_FEATURE_FLEXSPI_DMA_MULTIPLE_DES
    if (dataSize < handle->count)
    {
        handle->nsize  = kFLEXPSI_DMAnSize1Bytes;
        handle->nbytes = (uint8_t)dataSize;
    }
    else
    {
        /* Store the initially configured dma minor byte transfer count into the FLEXSPI handle */
        handle->nbytes = handle->count;
    }

    handle->transferSize     = dataSize;
    dmaTxTriggerConfig.burst = kDMA_SingleTransfer;
    dmaTxTriggerConfig.type  = kDMA_HighLevelTrigger;
    dmaTxTriggerConfig.wrap  = kDMA_NoWrap;

    /* Configure linked descriptors to start FLEXSPI Tx DMA transfer to provide software workaround for
    ERRATA FLEXSPI.1: Using FLEXSPI register interface, TX buffer fill / RX buffer drain by DMA with a
    single DMA descriptor cannot be performed. */
    desCount    = (uint8_t)(dataSize / (uint32_t)handle->nbytes);
    bytesPerDes = handle->nbytes;
    remains     = (uint8_t)(dataSize - (uint32_t)desCount * (uint32_t)handle->nbytes);
    if (remains > 0U)
    {
        uint32_t width = (uint32_t)kFLEXPSI_DMAnSize1Bytes;
        DMA_SetupDescriptor(&s_flexspiDes[desCount - 1U],
                            DMA_CHANNEL_XFER(false, true, true, false, width, srcInc, dstInc, remains),
                            (void *)(uint64_t *)((uint32_t)data + desCount * bytesPerDes), txFifoBase, NULL);
        nextDesc = &s_flexspiDes[desCount - 1U];
    }

    remains = (uint8_t)bytesPerDes;
#else
    uint32_t dmaTriggerBurst;
    dmaTxTriggerConfig.type = kDMA_RisingEdgeTrigger;
    bytesPerDes             = dataSize;

    if (dataSize < handle->count)
    {
        handle->nsize           = kFLEXPSI_DMAnSize1Bytes;
        handle->nbytes          = (uint8_t)(dataSize / (uint32_t)handle->nsize);
        dmaTxTriggerConfig.wrap = kDMA_NoWrap;

        /* Check the handle->nbytes is power of 2 */
        if (((handle->nbytes) & (handle->nbytes - 1U)) != 0U)
        {
            handle->nbytes = 2U * ((handle->nbytes) & (handle->nbytes - 1U));
        }

        desCount = 1U;
    }
    else
    {
        dmaTxTriggerConfig.wrap = kDMA_DstWrap;
        remains                 = (uint8_t)(dataSize % (uint32_t)handle->count);
        if (remains == 0U)
        {
            desCount = 1U;
        }
        else
        {
            desCount    = 2U;
            bytesPerDes = dataSize - remains;
            if ((remains & 3U) == 0U)
            {
                handle->nsize = kFLEXPSI_DMAnSize4Bytes;
            }
            else if ((remains & 1U) == 0U)
            {
                handle->nsize = kFLEXPSI_DMAnSize2Bytes;
            }
            else
            {
                handle->nsize = kFLEXPSI_DMAnSize1Bytes;
            }
        }
        /* Store the initially configured dma minor byte transfer count into the FLEXSPI handle */
        handle->nbytes = handle->count / (uint8_t)handle->nsize;

        /* Check if dataSize exceeds the maximum transfer count supported by the driver. */
        if ((dataSize - handle->count + 1U) / ((uint32_t)handle->nsize) > 1024U)
        {
            return kStatus_InvalidArgument;
        }
    }

    /* xfer->dataSize needs to be larger than 1 due to hardware limitation */
    if (dataSize / (uint8_t)handle->nsize == 1U)
    {
        return kStatus_InvalidArgument;
    }

    dmaTriggerBurst = DMA_CHANNEL_CFG_TRIGBURST(1) | DMA_CHANNEL_CFG_BURSTPOWER(FLEXSPI_CalculatePower(handle->nbytes));
    dmaTxTriggerConfig.burst = (dma_trigger_burst_t)dmaTriggerBurst;
    handle->transferSize     = dataSize;
#endif

    for (uint8_t i = desCount - 1U; i > 0U; i--)
    {
        DMA_SetupDescriptor(&s_flexspiDes[i - 1U],
                            DMA_CHANNEL_XFER((nextDesc == NULL) ? false : true, true, (nextDesc == NULL) ? true : false,
                                             false, (uint32_t)handle->nsize, srcInc, dstInc, remains),
                            (void *)(uint64_t *)((uint32_t)data + i * bytesPerDes), txFifoBase, nextDesc);
        nextDesc = &s_flexspiDes[i - 1U];
    }

    DMA_PrepareChannelTransfer(
        &txChannelConfig, (void *)data, txFifoBase,
        DMA_CHANNEL_XFER((nextDesc == NULL) ? false : true, true, (nextDesc == NULL) ? true : false, false,
                         (uint32_t)handle->nsize, srcInc, dstInc, bytesPerDes),
        kDMA_MemoryToMemory, &dmaTxTriggerConfig, nextDesc);

    (void)DMA_SubmitChannelTransfer(handle->txDmaHandle, &txChannelConfig);

    DMA_SetCallback(handle->txDmaHandle, FLEXSPI_TransferDMACallback, &s_dmaPrivateHandle[FLEXSPI_GetInstance(base)]);
    DMA_StartTransfer(handle->txDmaHandle);

    /* Enable FLEXSPI TX DMA. */
    FLEXSPI_EnableTxDMA(base, true);

    /* Start Transfer. */
    base->IPCMD |= FLEXSPI_IPCMD_TRG_MASK;

    return kStatus_Success;
}

static status_t FLEXSPI_ReadDataDMA(FLEXSPI_Type *base, flexspi_dma_handle_t *handle, uint32_t *data, size_t dataSize)
{
    dma_channel_trigger_t dmaRxTriggerConfig;
    void *rxFifoBase = (void *)(uint32_t *)FLEXSPI_GetRxFifoAddress(base);
    void *nextDesc   = NULL;
    dma_channel_config_t rxChannelConfig;
    uint32_t bytesPerDes;
    uint8_t remains;
    uint8_t desCount;
    uint32_t srcInc;
    uint32_t dstInc;

    /* Source address interleave size */
    srcInc = kDMA_AddressInterleave1xWidth;
    /* Destination address interleave size */
    dstInc = kDMA_AddressInterleave1xWidth;

    handle->count =
        8U * (uint8_t)(((base->IPRXFCR & FLEXSPI_IPRXFCR_RXWMRK_MASK) >> FLEXSPI_IPRXFCR_RXWMRK_SHIFT) + 1U);

    /* Check the watermark is power of 2U */
    if ((handle->count & (handle->count - 1U)) != 0U)
    {
        return kStatus_InvalidArgument;
    }

#if defined(FSL_FEATURE_FLEXSPI_DMA_MULTIPLE_DES) && FSL_FEATURE_FLEXSPI_DMA_MULTIPLE_DES
    if (dataSize < handle->count)
    {
        handle->nsize  = kFLEXPSI_DMAnSize1Bytes;
        handle->nbytes = (uint8_t)dataSize;
    }
    else
    {
        /* Store the initially configured dma minor byte transfer count into the FLEXSPI handle */
        handle->nbytes = handle->count;
    }

    dmaRxTriggerConfig.burst = kDMA_SingleTransfer;
    dmaRxTriggerConfig.type  = kDMA_HighLevelTrigger;
    dmaRxTriggerConfig.wrap  = kDMA_NoWrap;

    /* Configure linked descriptors to start FLEXSPI Tx DMA transfer to provide software workaround for
    ERRATA FLEXSPI.1: Using FLEXSPI register interface, TX buffer fill / RX buffer drain by DMA with a
    single DMA descriptor cannot be performed. */
    desCount    = (uint8_t)(dataSize / (uint32_t)handle->nbytes);
    bytesPerDes = handle->nbytes;
    remains     = (uint8_t)(dataSize - (uint32_t)desCount * (uint32_t)handle->nbytes);

    if (remains > 0U)
    {
        uint32_t width = (uint32_t)kFLEXPSI_DMAnSize1Bytes;
        DMA_SetupDescriptor(&s_flexspiDes[desCount - 1U],
                            DMA_CHANNEL_XFER(false, true, true, false, width, srcInc, dstInc, remains), rxFifoBase,
                            (void *)(uint64_t *)((uint32_t)data + desCount * bytesPerDes), NULL);
        nextDesc = &s_flexspiDes[desCount - 1U];
    }
    remains = (uint8_t)bytesPerDes;

#else
    uint32_t dmaTriggerBurst;
    dmaRxTriggerConfig.type = kDMA_RisingEdgeTrigger;
    bytesPerDes             = dataSize;

    if (dataSize < handle->count)
    {
        handle->nsize           = kFLEXPSI_DMAnSize1Bytes;
        handle->nbytes          = (uint8_t)(dataSize / (uint32_t)handle->nsize);
        dmaRxTriggerConfig.wrap = kDMA_NoWrap;
        /* Check the handle->nbytes is power of 2 */
        if (((handle->nbytes) & (handle->nbytes - 1U)) != 0U)
        {
            handle->nbytes = 2U * ((handle->nbytes) & (handle->nbytes - 1U));
        }
        desCount = 1U;
    }
    else
    {
        dmaRxTriggerConfig.wrap = kDMA_SrcWrap;
        remains                 = (uint8_t)(dataSize % (uint32_t)handle->count);
        if (remains == 0U)
        {
            desCount = 1U;
        }
        else
        {
            desCount    = 2U;
            bytesPerDes = dataSize - remains;
            if ((remains & 3U) == 0U)
            {
                handle->nsize = kFLEXPSI_DMAnSize4Bytes;
            }
            else if ((remains & 1U) == 0U)
            {
                handle->nsize = kFLEXPSI_DMAnSize2Bytes;
            }
            else
            {
                handle->nsize = kFLEXPSI_DMAnSize1Bytes;
            }
        }
        /* Store the initially configured dma minor byte transfer count into the FLEXSPI handle */
        handle->nbytes = handle->count / (uint8_t)handle->nsize;

        /* Check dataSize exceeds the maximum transfer count supported by the driver. */
        if ((dataSize - handle->count + 1U) / ((uint32_t)handle->nsize) > 1024U)
        {
            return kStatus_InvalidArgument;
        }
    }

    dmaTriggerBurst =
        DMA_CHANNEL_CFG_TRIGBURST(1U) | DMA_CHANNEL_CFG_BURSTPOWER(FLEXSPI_CalculatePower(handle->nbytes));
    dmaRxTriggerConfig.burst = (dma_trigger_burst_t)(dmaTriggerBurst);
#endif

    for (uint8_t i = desCount - 1U; i > 0U; i--)
    {
        DMA_SetupDescriptor(&s_flexspiDes[i - 1U],
                            DMA_CHANNEL_XFER((nextDesc == NULL) ? false : true, true, (nextDesc == NULL) ? true : false,
                                             false, (uint32_t)handle->nsize, srcInc, dstInc, remains),
                            rxFifoBase, (void *)(uint64_t *)((uint32_t)data + i * bytesPerDes), nextDesc);
        nextDesc = &s_flexspiDes[i - 1U];
    }

    DMA_PrepareChannelTransfer(
        &rxChannelConfig, rxFifoBase, (void *)data,
        DMA_CHANNEL_XFER((nextDesc == NULL) ? false : true, true, (nextDesc == NULL) ? true : false, false,
                         (uint32_t)handle->nsize, srcInc, dstInc, bytesPerDes),
        kDMA_MemoryToMemory, &dmaRxTriggerConfig, nextDesc);

    (void)DMA_SubmitChannelTransfer(handle->rxDmaHandle, &rxChannelConfig);

    DMA_SetCallback(handle->rxDmaHandle, FLEXSPI_TransferDMACallback, &s_dmaPrivateHandle[FLEXSPI_GetInstance(base)]);
    DMA_StartTransfer(handle->rxDmaHandle);

    /* Enable FLEXSPI RX DMA. */
    FLEXSPI_EnableRxDMA(base, true);

    /* Start Transfer. */
    base->IPCMD |= FLEXSPI_IPCMD_TRG_MASK;

    return kStatus_Success;
}

/*!
 * brief Initializes the FLEXSPI handle for transfer which is used in transactional functions and set the callback.
 *
 * param base FLEXSPI peripheral base address
 * param handle Pointer to flexspi_dma_handle_t structure
 * param callback FLEXSPI callback, NULL means no callback.
 * param userData User callback function data.
 * param txDmaHandle User requested DMA handle for TX DMA transfer.
 * param rxDmaHandle User requested DMA handle for RX DMA transfer.
 */
void FLEXSPI_TransferCreateHandleDMA(FLEXSPI_Type *base,
                                     flexspi_dma_handle_t *handle,
                                     flexspi_dma_callback_t callback,
                                     void *userData,
                                     dma_handle_t *txDmaHandle,
                                     dma_handle_t *rxDmaHandle)
{
    assert(handle);

    uint32_t instance = FLEXSPI_GetInstance(base);

    s_dmaPrivateHandle[instance].base   = base;
    s_dmaPrivateHandle[instance].handle = handle;

    (void)memset(handle, 0, sizeof(*handle));

    handle->state       = kFLEXSPI_Idle;
    handle->txDmaHandle = txDmaHandle;
    handle->rxDmaHandle = rxDmaHandle;
    handle->nsize       = kFLEXPSI_DMAnSize4Bytes;

    handle->completionCallback = callback;
    handle->userData           = userData;
}

/*!
 * brief Update FLEXSPI DMA transfer source data transfer size(SSIZE) and destination data transfer size(DSIZE).
 *
 * param base FLEXSPI peripheral base address
 * param handle Pointer to flexspi_dma_handle_t structure
 * param nsize FLEXSPI DMA transfer data transfer size(SSIZE/DSIZE), by default the size is
 * kFLEXPSI_DMAnSize1Bytes(one byte).
 * see flexspi_dma_transfer_nsize_t               .
 */
void FLEXSPI_TransferUpdateSizeDMA(FLEXSPI_Type *base, flexspi_dma_handle_t *handle, flexspi_dma_transfer_nsize_t nsize)
{
    handle->nsize = nsize;
}

/*!
 * brief Transfers FLEXSPI data using an dma non-blocking method.
 *
 * This function writes/receives data to/from the FLEXSPI transmit/receive FIFO. This function is non-blocking.
 * param base FLEXSPI peripheral base address.
 * param handle Pointer to flexspi_dma_handle_t structure
 * param xfer FLEXSPI transfer structure.
 * retval kStatus_FLEXSPI_Busy     FLEXSPI is busy transfer.
 * retval kStatus_InvalidArgument  The watermark configuration is invalid, the watermark should be power of
                                    2 to do successfully DMA transfer.
 * retval kStatus_Success          FLEXSPI successfully start dma transfer.
 */
status_t FLEXSPI_TransferDMA(FLEXSPI_Type *base, flexspi_dma_handle_t *handle, flexspi_transfer_t *xfer)
{
    uint32_t configValue = 0;
    status_t result      = kStatus_Success;

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

        if ((xfer->cmdType == kFLEXSPI_Write) || (xfer->cmdType == kFLEXSPI_Config))
        {
            handle->state = kFLEXSPI_Busy;
            result        = FLEXSPI_WriteDataDMA(base, handle, xfer->data, xfer->dataSize);
        }
        else if (xfer->cmdType == kFLEXSPI_Read)
        {
            handle->state = kFLEXSPI_Busy;
            result        = FLEXSPI_ReadDataDMA(base, handle, xfer->data, xfer->dataSize);
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
    }

    return result;
}

/*!
 * brief Aborts the transfer data using dma.
 *
 * This function aborts the transfer data using dma.
 *
 * param base FLEXSPI peripheral base address.
 * param handle Pointer to flexspi_dma_handle_t structure
 */
void FLEXSPI_TransferAbortDMA(FLEXSPI_Type *base, flexspi_dma_handle_t *handle)
{
    assert(handle != NULL);

    if ((base->IPTXFCR & FLEXSPI_IPTXFCR_TXDMAEN_MASK) != 0x00U)
    {
        FLEXSPI_EnableTxDMA(base, false);
        DMA_AbortTransfer(handle->txDmaHandle);
    }

    if ((base->IPRXFCR & FLEXSPI_IPRXFCR_RXDMAEN_MASK) != 0x00U)
    {
        FLEXSPI_EnableRxDMA(base, false);
        DMA_AbortTransfer(handle->rxDmaHandle);
    }

    handle->state = kFLEXSPI_Idle;
}

status_t FLEXSPI_TransferGetTransferCountDMA(FLEXSPI_Type *base, flexspi_dma_handle_t *handle, size_t *count)
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
            *count =
                (handle->transferSize - DMA_GetRemainingBytes(handle->rxDmaHandle->base, handle->rxDmaHandle->channel));
        }
        else if ((base->IPTXFCR & FLEXSPI_IPTXFCR_TXDMAEN_MASK) != 0x00U)
        {
            *count =
                (handle->transferSize - DMA_GetRemainingBytes(handle->txDmaHandle->base, handle->txDmaHandle->channel));
        }
        else
        {
            ; /* Intentional empty for MISRA C-2012 rule 15.7. */
        }
    }

    return result;
}
