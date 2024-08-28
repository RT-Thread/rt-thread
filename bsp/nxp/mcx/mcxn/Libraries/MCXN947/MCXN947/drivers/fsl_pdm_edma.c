/*
 * Copyright 2019 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_pdm_edma.h"

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.pdm_edma"
#endif

/*******************************************************************************
 * Definitations
 ******************************************************************************/
/* Used for edma_tcd_t size aligned */
#define STCD_ADDR(address) (edma_tcd_t *)(((uint32_t)(address) + sizeof(edma_tcd_t)) & ~(sizeof(edma_tcd_t) - 1U))

/*<! Structure definition for pdm_edma_private_handle_t. The structure is private. */
typedef struct _pdm_edma_private_handle
{
    PDM_Type *base;
    pdm_edma_handle_t *handle;
} pdm_edma_private_handle_t;

/*! @brief pdm transfer state */
enum _pdm_edma_transfer_state
{
    kPDM_Busy = 0x0U, /*!< PDM is busy */
    kPDM_Idle,        /*!< Transfer is done. */
};

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief PDM EDMA callback for receive.
 *
 * @param handle pointer to pdm_edma_handle_t structure which stores the transfer state.
 * @param userData Parameter for user callback.
 * @param done If the DMA transfer finished.
 * @param tcds The TCD index.
 */
static void PDM_EDMACallback(edma_handle_t *handle, void *userData, bool done, uint32_t tcds);

/*!
 * @brief Mapping the enabled channel to a number power of 2.
 *
 * @param channel PDM channel number.
 */
static edma_modulo_t PDM_TransferMappingChannel(uint32_t *channel);
/*******************************************************************************
 * Variables
 ******************************************************************************/

/*! @brief pdm base address pointer */
static PDM_Type *const s_pdmBases[] = PDM_BASE_PTRS;
/*<! Private handle only used for internally. */
static pdm_edma_private_handle_t s_edmaPrivateHandle[ARRAY_SIZE(s_pdmBases)];
/*******************************************************************************
 * Code
 ******************************************************************************/
static edma_modulo_t PDM_TransferMappingChannel(uint32_t *channel)
{
    edma_modulo_t modulo = kEDMA_ModuloDisable;
#if FSL_FEATURE_PDM_CHANNEL_NUM == 8U
    if (*channel == 2U)
    {
        modulo = kEDMA_Modulo8bytes;
    }
    else if ((*channel == 3U) || (*channel == 4U))
    {
        *channel = 4U;
        modulo   = kEDMA_Modulo16bytes;
    }
    else
    {
        modulo = kEDMA_ModuloDisable;
    }
#endif

    return modulo;
}

static void PDM_EDMACallback(edma_handle_t *handle, void *userData, bool done, uint32_t tcds)
{
    pdm_edma_private_handle_t *privHandle = (pdm_edma_private_handle_t *)userData;
    pdm_edma_handle_t *pdmHandle          = privHandle->handle;

    if (!(pdmHandle->isLoopTransfer))
    {
        (void)memset(&pdmHandle->tcd[pdmHandle->tcdDriver], 0, sizeof(edma_tcd_t));
        pdmHandle->tcdDriver = (pdmHandle->tcdDriver + 1U) % pdmHandle->tcdNum;
    }
#if defined FSL_EDMA_DRIVER_EDMA4 && FSL_EDMA_DRIVER_EDMA4
    pdmHandle->receivedBytes +=
        EDMA_TCD_BITER((&pdmHandle->tcd[pdmHandle->tcdDriver]), EDMA_TCD_TYPE(handle->base)) *
        (EDMA_TCD_NBYTES((&pdmHandle->tcd[pdmHandle->tcdDriver]), EDMA_TCD_TYPE(handle->base)) & 0x3FFU);
#else
    pdmHandle->receivedBytes +=
        pdmHandle->tcd[pdmHandle->tcdDriver].BITER * (pdmHandle->tcd[pdmHandle->tcdDriver].NBYTES & 0x3FFU);
#endif
    /* If finished a block, call the callback function */
    if (pdmHandle->callback != NULL)
    {
        (pdmHandle->callback)(privHandle->base, pdmHandle, kStatus_PDM_Idle, pdmHandle->userData);
    }

    pdmHandle->tcdUsedNum--;
    /* If all data finished, just stop the transfer */
    if ((pdmHandle->tcdUsedNum == 0U) && !(pdmHandle->isLoopTransfer))
    {
        /* Disable DMA enable bit */
        PDM_EnableDMA(privHandle->base, false);
        EDMA_AbortTransfer(handle);
    }
}

/*!
 * brief Initializes the PDM Rx eDMA handle.
 *
 * This function initializes the PDM slave DMA handle, which can be used for other PDM master transactional APIs.
 * Usually, for a specified PDM instance, call this API once to get the initialized handle.
 *
 * param base PDM base pointer.
 * param handle PDM eDMA handle pointer.
 * param base PDM peripheral base address.
 * param callback Pointer to user callback function.
 * param userData User parameter passed to the callback function.
 * param dmaHandle eDMA handle pointer, this handle shall be static allocated by users.
 */
void PDM_TransferCreateHandleEDMA(
    PDM_Type *base, pdm_edma_handle_t *handle, pdm_edma_callback_t callback, void *userData, edma_handle_t *dmaHandle)
{
    assert((handle != NULL) && (dmaHandle != NULL));

    uint32_t instance = PDM_GetInstance(base);

    /* Zero the handle */
    (void)memset(handle, 0, sizeof(*handle));

    /* Set pdm base to handle */
    handle->dmaHandle = dmaHandle;
    handle->callback  = callback;
    handle->userData  = userData;

    /* Set PDM state to idle */
    handle->state = (uint32_t)kPDM_Idle;

    s_edmaPrivateHandle[instance].base   = base;
    s_edmaPrivateHandle[instance].handle = handle;

    /* Install callback for Tx dma channel */
    EDMA_SetCallback(dmaHandle, PDM_EDMACallback, &s_edmaPrivateHandle[instance]);
}

/*!
 * brief Initializes the multi PDM channel interleave type.
 *
 * This function initializes the PDM DMA handle member interleaveType, it shall be called only when application would
 * like to use type kPDM_EDMAMultiChannelInterleavePerChannelBlock, since the default interleaveType is
 * kPDM_EDMAMultiChannelInterleavePerChannelSample always
 *
 * param handle PDM eDMA handle pointer.
 * param multiChannelInterleaveType Multi channel interleave type.
 */
void PDM_TransferSetMultiChannelInterleaveType(pdm_edma_handle_t *handle,
                                               pdm_edma_multi_channel_interleave_t multiChannelInterleaveType)
{
    handle->interleaveType = multiChannelInterleaveType;
}

/*!
 * brief Install EDMA descriptor memory.
 *
 * param handle Pointer to EDMA channel transfer handle.
 * param tcdAddr EDMA head descriptor address.
 * param tcdNum EDMA link descriptor address.
 */
void PDM_TransferInstallEDMATCDMemory(pdm_edma_handle_t *handle, void *tcdAddr, size_t tcdNum)
{
    assert(handle != NULL);

    handle->tcd    = (edma_tcd_t *)tcdAddr;
    handle->tcdNum = tcdNum;
}

/*!
 * brief Configures the PDM channel.
 *
 * param base PDM base pointer.
 * param handle PDM eDMA handle pointer.
 * param channel channel index.
 * param pdmConfig pdm channel configurations.
 */
void PDM_TransferSetChannelConfigEDMA(PDM_Type *base,
                                      pdm_edma_handle_t *handle,
                                      uint32_t channel,
                                      const pdm_channel_config_t *config)
{
    assert((handle != NULL) && (config != NULL));
    assert(channel < (uint32_t)FSL_FEATURE_PDM_CHANNEL_NUM);

    /* Configure the PDM channel */
    PDM_SetChannelConfig(base, channel, config);

    /* record end channel number */
    handle->endChannel = (uint8_t)channel;
    /* increase totoal enabled channel number */
    handle->channelNums++;
    /* increase count pre channel numbers */
    handle->count = (uint8_t)(base->FIFO_CTRL & PDM_FIFO_CTRL_FIFOWMK_MASK);
}

/*!
 * brief Performs a non-blocking PDM receive using eDMA.
 *
 * note This interface returns immediately after the transfer initiates. Call
 * the PDM_GetReceiveRemainingBytes to poll the transfer status and check whether the PDM transfer is finished.
 *
 * Mcaro MCUX_SDK_PDM_EDMA_PDM_ENABLE_INTERNAL can control whether PDM is enabled internally or externally.
 *
 * 1. Scatter gather case:
 * This functio support dynamic scatter gather and staic scatter gather,
 * a. for the dynamic scatter gather case:
 * Application should call PDM_TransferReceiveEDMA function continuously to make sure new receive request is submit
 *before the previous one finish. b. for the static scatter gather case: Application should use the link transfer
 *feature and make sure a loop link transfer is provided, such as: code pdm_edma_transfer_t pdmXfer[2] =
 *   {
 *       {
 *       .data  = s_buffer,
 *       .dataSize = BUFFER_SIZE,
 *       .linkTransfer = &pdmXfer[1],
 *       },
 *
 *       {
 *       .data  = &s_buffer[BUFFER_SIZE],
 *       .dataSize = BUFFER_SIZE,
 *       .linkTransfer = &pdmXfer[0]
 *       },
 *   };
 *endcode
 *
 * 2. Multi channel case:
 * This function support receive multi pdm channel data, for example, if two channel is requested,
 * code
 * PDM_TransferSetChannelConfigEDMA(DEMO_PDM, &s_pdmRxHandle_0, DEMO_PDM_ENABLE_CHANNEL_0, &channelConfig);
 * PDM_TransferSetChannelConfigEDMA(DEMO_PDM, &s_pdmRxHandle_0, DEMO_PDM_ENABLE_CHANNEL_1, &channelConfig);
 * PDM_TransferReceiveEDMA(DEMO_PDM, &s_pdmRxHandle_0, pdmXfer);
 * endcode
 * The output data will be formatted as below if handle->interleaveType =
 *kPDM_EDMAMultiChannelInterleavePerChannelSample :
 * -------------------------------------------------------------------------
 * |CHANNEL0 | CHANNEL1 | CHANNEL0 | CHANNEL1 | CHANNEL0 | CHANNEL 1 | ....|
 * -------------------------------------------------------------------------
 *
 * The output data will be formatted as below if handle->interleaveType = kPDM_EDMAMultiChannelInterleavePerChannelBlock
 *:
 * ----------------------------------------------------------------------------------------------------------------------
 * |CHANNEL3 | CHANNEL3 | CHANNEL3 | .... | CHANNEL4 | CHANNEL 4 | CHANNEL4 |....| CHANNEL5 | CHANNEL 5 | CHANNEL5
 *|....|
 * ----------------------------------------------------------------------------------------------------------------------
 * Note: the dataSize of xfer is the total data size, while application using
 * kPDM_EDMAMultiChannelInterleavePerChannelBlock, the buffer size for each PDM channel is channelSize = dataSize /
 * channelNums, there are limitation for this feature,
 * 1. For 3 DMIC array: the dataSize shall be 4 * (channelSize)
 * The addtional buffer is mandantory for edma modulo feature.
 * 2. The kPDM_EDMAMultiChannelInterleavePerChannelBlock feature support below dmic array only,
 *    2 DMIC array: CHANNEL3, CHANNEL4
 *    3 DMIC array: CHANNEL3, CHANNEL4, CHANNEL5
 *    4 DMIC array: CHANNEL3, CHANNEL4, CHANNEL5, CHANNEL6
 * Any other combinations is not support, that is to SAY, THE FEATURE SUPPORT RECEIVE START FROM CHANNEL3 ONLY AND 4
 * MAXIMUM DMIC CHANNELS.
 *
 * param base PDM base pointer
 * param handle PDM eDMA handle pointer.
 * param xfer Pointer to DMA transfer structure.
 * retval kStatus_Success Start a PDM eDMA receive successfully.
 * retval kStatus_InvalidArgument The input argument is invalid.
 * retval kStatus_RxBusy PDM is busy receiving data.
 */
status_t PDM_TransferReceiveEDMA(PDM_Type *base, pdm_edma_handle_t *handle, pdm_edma_transfer_t *xfer)
{
    assert((handle != NULL) && (xfer != NULL));

    edma_transfer_config_t config = {0};
    uint32_t startAddr            = PDM_GetDataRegisterAddress(base, handle->endChannel - (handle->channelNums - 1UL));
    pdm_edma_transfer_t *currentTransfer = xfer;
    uint32_t nextTcdIndex = 0U, tcdIndex = handle->tcdUser, destOffset = FSL_FEATURE_PDM_FIFO_WIDTH;
    uint32_t mappedChannel = handle->channelNums;
    edma_modulo_t modulo   = kEDMA_ModuloDisable;
    /* minor offset used for channel sample interleave transfer */
    edma_minor_offset_config_t minorOffset = {
        .enableSrcMinorOffset  = true,
        .enableDestMinorOffset = false,
        .minorOffset           = 0xFFFFFU - mappedChannel * (uint32_t)FSL_FEATURE_PDM_FIFO_OFFSET + 1U};

    /* Check if input parameter invalid */
    if ((xfer->data == NULL) || (xfer->dataSize == 0U))
    {
        return kStatus_InvalidArgument;
    }

    if ((handle->interleaveType == kPDM_EDMAMultiChannelInterleavePerChannelBlock) && (mappedChannel > 1U))
    {
        /* Limitation of the feature, reference the API comments */
        if (((startAddr & 0xFU) != 0U) || (mappedChannel > 4U))
        {
            return kStatus_InvalidArgument;
        }
        modulo = PDM_TransferMappingChannel(&mappedChannel);
        if ((xfer->dataSize % mappedChannel) != 0U)
        {
            return kStatus_InvalidArgument;
        }
        destOffset = xfer->dataSize / mappedChannel;
        /* reconfigure the minor loop offset for channel block interleave */
        minorOffset.enableSrcMinorOffset = false, minorOffset.enableDestMinorOffset = true,
        minorOffset.minorOffset =
            0xFFFFFU - mappedChannel * (uint32_t)destOffset + (uint32_t)FSL_FEATURE_PDM_FIFO_WIDTH + 1U;
    }

    while (currentTransfer != NULL)
    {
        if (handle->tcdUsedNum >= handle->tcdNum)
        {
            return kStatus_PDM_QueueFull;
        }
        else
        {
            uint32_t primask = DisableGlobalIRQ();
            handle->tcdUsedNum++;
            EnableGlobalIRQ(primask);
        }

        nextTcdIndex = (handle->tcdUser + 1U) % handle->tcdNum;

        if (mappedChannel == 1U)
        {
            EDMA_PrepareTransferConfig(&config, (void *)(uint32_t *)startAddr, FSL_FEATURE_PDM_FIFO_WIDTH, 0,
                                       (uint8_t *)(uint32_t)currentTransfer->data, FSL_FEATURE_PDM_FIFO_WIDTH,
                                       FSL_FEATURE_PDM_FIFO_WIDTH, handle->count * (uint32_t)FSL_FEATURE_PDM_FIFO_WIDTH,
                                       currentTransfer->dataSize);
        }
        else
        {
            EDMA_PrepareTransferConfig(&config, (void *)(uint32_t *)startAddr, FSL_FEATURE_PDM_FIFO_WIDTH,
                                       FSL_FEATURE_PDM_FIFO_OFFSET, (uint8_t *)(uint32_t)currentTransfer->data,
                                       FSL_FEATURE_PDM_FIFO_WIDTH, (int16_t)destOffset,
                                       mappedChannel * (uint32_t)FSL_FEATURE_PDM_FIFO_WIDTH, currentTransfer->dataSize);
        }
#if defined FSL_EDMA_DRIVER_EDMA4 && FSL_EDMA_DRIVER_EDMA4
        EDMA_TcdSetTransferConfigExt(handle->dmaHandle->base, (edma_tcd_t *)&handle->tcd[handle->tcdUser], &config,
                                     (edma_tcd_t *)&handle->tcd[nextTcdIndex]);

        if (mappedChannel > 1U)
        {
            EDMA_TcdSetMinorOffsetConfigExt(handle->dmaHandle->base, (edma_tcd_t *)&handle->tcd[handle->tcdUser],
                                            &minorOffset);

            if (handle->interleaveType == kPDM_EDMAMultiChannelInterleavePerChannelBlock)
            {
                EDMA_TcdSetModuloExt(handle->dmaHandle->base, (edma_tcd_t *)&handle->tcd[handle->tcdUser], modulo,
                                     kEDMA_ModuloDisable);
            }
        }

        EDMA_TcdEnableInterruptsExt(handle->dmaHandle->base, (edma_tcd_t *)&handle->tcd[handle->tcdUser],
                                    (uint32_t)kEDMA_MajorInterruptEnable);
#else
        EDMA_TcdSetTransferConfig((edma_tcd_t *)&handle->tcd[handle->tcdUser], &config,
                                  (edma_tcd_t *)&handle->tcd[nextTcdIndex]);

        if (mappedChannel > 1U)
        {
            EDMA_TcdSetMinorOffsetConfig((edma_tcd_t *)&handle->tcd[handle->tcdUser], &minorOffset);

            if (handle->interleaveType == kPDM_EDMAMultiChannelInterleavePerChannelBlock)
            {
                EDMA_TcdSetModulo((edma_tcd_t *)&handle->tcd[handle->tcdUser], modulo, kEDMA_ModuloDisable);
            }
        }

        EDMA_TcdEnableInterrupts((edma_tcd_t *)&handle->tcd[handle->tcdUser], (uint32_t)kEDMA_MajorInterruptEnable);
#endif

        handle->tcdUser = nextTcdIndex;

        currentTransfer = currentTransfer->linkTransfer;

        if (currentTransfer == xfer)
        {
            handle->isLoopTransfer = true;
            break;
        }
    }

    if (handle->state != (uint32_t)kPDM_Busy)
    {
        EDMA_InstallTCD(handle->dmaHandle->base, handle->dmaHandle->channel, (edma_tcd_t *)&handle->tcd[tcdIndex]);
        /* Start DMA transfer */
        EDMA_StartTransfer(handle->dmaHandle);

        /* Enable DMA enable bit */
        PDM_EnableDMA(base, true);
#if defined(MCUX_SDK_PDM_EDMA_PDM_ENABLE_INTERNAL) && MCUX_SDK_PDM_EDMA_PDM_ENABLE_INTERNAL
        /* enable PDM */
        PDM_Enable(base, true);
#endif

        handle->state = (uint32_t)kPDM_Busy;
    }

    return kStatus_Success;
}

/*!
 * brief Aborts a PDM receive using eDMA.
 *
 * This function only aborts the current transfer slots, the other transfer slots' information still kept
 * in the handler. If users want to terminate all transfer slots, just call PDM_TransferTerminateReceiveEDMA.
 *
 * param base PDM base pointer
 * param handle PDM eDMA handle pointer.
 */
void PDM_TransferAbortReceiveEDMA(PDM_Type *base, pdm_edma_handle_t *handle)
{
    assert(handle != NULL);

    /* Disable dma */
    EDMA_AbortTransfer(handle->dmaHandle);

    /* Disable DMA enable bit */
    PDM_EnableDMA(base, false);

    /* Disable PDM */
    PDM_Enable(base, false);

    /* Handle the queue index */
    handle->tcdUsedNum--;

    /* Set the handle state */
    handle->state = (uint32_t)kPDM_Idle;
}

/*!
 * brief Terminate all PDM receive.
 *
 * This function will clear all transfer slots buffered in the pdm queue. If users only want to abort the
 * current transfer slot, please call PDM_TransferAbortReceiveEDMA.
 *
 * param base PDM base pointer.
 * param handle PDM eDMA handle pointer.
 */
void PDM_TransferTerminateReceiveEDMA(PDM_Type *base, pdm_edma_handle_t *handle)
{
    assert(handle != NULL);

    /* Abort the current transfer */
    PDM_TransferAbortReceiveEDMA(base, handle);

    /* Clear all the internal information */
    (void)memset(handle->tcd, 0, sizeof(edma_tcd_t) * handle->tcdNum);
    handle->tcdUser    = 0U;
    handle->tcdUsedNum = 0U;
}

/*!
 * brief Gets byte count received by PDM.
 *
 * param base PDM base pointer
 * param handle PDM eDMA handle pointer.
 * param count Bytes count received by PDM.
 * retval kStatus_Success Succeed get the transfer count.
 * retval kStatus_NoTransferInProgress There is no non-blocking transaction in progress.
 */
status_t PDM_TransferGetReceiveCountEDMA(PDM_Type *base, pdm_edma_handle_t *handle, size_t *count)
{
    assert(handle != NULL);

    *count = handle->receivedBytes;

    return kStatus_Success;
}
