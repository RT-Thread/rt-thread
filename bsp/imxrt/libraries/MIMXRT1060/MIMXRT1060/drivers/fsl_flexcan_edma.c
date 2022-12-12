/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2021 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_flexcan_edma.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.flexcan_edma"
#endif

/*<! Structure definition for flexcan_edma_private_handle_t. The structure is private. */
typedef struct _flexcan_edma_private_handle
{
    CAN_Type *base;
    flexcan_edma_handle_t *handle;
} flexcan_edma_private_handle_t;

/* FlexCAN EDMA transfer handle. */
enum _flexcan_edma_tansfer_state
{
    KFLEXCAN_RxFifoIdle = 0U, /* Rx Fifo idle. */
    KFLEXCAN_RxFifoBusy = 1U, /* Rx Fifo busy. */
};

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*<! Private handle only used for internally. */
static flexcan_edma_private_handle_t s_flexcanEdmaPrivateHandle[FSL_FEATURE_SOC_FLEXCAN_COUNT];

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief FlexCAN EDMA receive finished callback function.
 *
 * This function is called when FlexCAN Rx FIFO EDMA receive finished.
 * It disables the FlexCAN Rx FIFO EDMA request and sends
 * @ref kStatus_FLEXCAN_RxFifoIdle to FlexCAN EDMA callback.
 *
 * @param handle The EDMA handle.
 * @param param Callback function parameter.
 */
static void FLEXCAN_ReceiveFifoEDMACallback(edma_handle_t *handle, void *param, bool transferDone, uint32_t tcds);

/*******************************************************************************
 * Code
 ******************************************************************************/
static void FLEXCAN_ReceiveFifoEDMACallback(edma_handle_t *handle, void *param, bool transferDone, uint32_t tcds)
{
    handle = handle;
    tcds   = tcds;
#if (defined(FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO) && FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO)
    flexcan_fd_frame_t *framefd;
    uint32_t idHitIndex;
#endif
    flexcan_edma_private_handle_t *flexcanPrivateHandle = (flexcan_edma_private_handle_t *)param;

    if (transferDone)
    {
#if (defined(FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO) && FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO)
        framefd = flexcanPrivateHandle->handle->framefd;
        for (uint32_t i = 0; i < flexcanPrivateHandle->handle->frameNum; i++)
        {
            /* Enhanced Rx FIFO ID HIT offset is changed dynamically according to data length code (DLC) . */
            idHitIndex     = (DLC_LENGTH_DECODE(framefd->length) + 3U) / 4U;
            framefd->idhit = framefd->dataWord[idHitIndex];
            /* Clear the unused frame data. */
            for (uint32_t i = idHitIndex; i < 16U; i++)
            {
                framefd->dataWord[i] = 0x0U;
            }
            framefd++;
        }
#endif
        /* Disable transfer. */
        FLEXCAN_TransferAbortReceiveFifoEDMA(flexcanPrivateHandle->base, flexcanPrivateHandle->handle);

        if (NULL != flexcanPrivateHandle->handle->callback)
        {
            flexcanPrivateHandle->handle->callback(flexcanPrivateHandle->base, flexcanPrivateHandle->handle,
                                                   kStatus_FLEXCAN_RxFifoIdle, flexcanPrivateHandle->handle->userData);
        }
    }
}

/*!
 * brief Initializes the FlexCAN handle, which is used in transactional functions.
 *
 * param base FlexCAN peripheral base address.
 * param handle Pointer to flexcan_edma_handle_t structure.
 * param callback The callback function.
 * param userData The parameter of the callback function.
 * param rxFifoEdmaHandle User-requested DMA handle for Rx FIFO DMA transfer.
 */
void FLEXCAN_TransferCreateHandleEDMA(CAN_Type *base,
                                      flexcan_edma_handle_t *handle,
                                      flexcan_edma_transfer_callback_t callback,
                                      void *userData,
                                      edma_handle_t *rxFifoEdmaHandle)
{
    assert(NULL != handle);

    uint32_t instance                           = FLEXCAN_GetInstance(base);
    s_flexcanEdmaPrivateHandle[instance].base   = base;
    s_flexcanEdmaPrivateHandle[instance].handle = handle;

    (void)memset(handle, 0, sizeof(flexcan_edma_handle_t));

    handle->rxFifoState      = (uint8_t)KFLEXCAN_RxFifoIdle;
    handle->rxFifoEdmaHandle = rxFifoEdmaHandle;

    /* Register Callback. */
    handle->callback = callback;
    handle->userData = userData;

    /* Configure Legacy/Enhanced Rx FIFO DMA callback. */
    EDMA_SetCallback(handle->rxFifoEdmaHandle, FLEXCAN_ReceiveFifoEDMACallback, &s_flexcanEdmaPrivateHandle[instance]);
}

/*!
 * brief Prepares the eDMA transfer configuration for FLEXCAN Legacy RX FIFO.
 *
 * This function prepares the eDMA transfer configuration structure according to FLEXCAN Legacy RX FIFO.
 *
 * param base FlexCAN peripheral base address.
 * param pFifoXfer FlexCAN Rx FIFO EDMA transfer structure, see #flexcan_fifo_transfer_t.
 * param pEdmaConfig The user configuration structure of type edma_transfer_t.
 *
 */
void FLEXCAN_PrepareTransfConfiguration(CAN_Type *base,
                                        flexcan_fifo_transfer_t *pFifoXfer,
                                        edma_transfer_config_t *pEdmaConfig)
{
    assert(NULL != pFifoXfer);
    assert(NULL != pFifoXfer->frame);
    assert(NULL != pEdmaConfig);

    flexcan_frame_t *fifoAddr = (flexcan_frame_t *)FLEXCAN_GetRxFifoHeadAddr(base);

#if (defined(FSL_FEATURE_EDMA_SUPPORT_16_BYTES_TRANSFER) && FSL_FEATURE_EDMA_SUPPORT_16_BYTES_TRANSFER)
    EDMA_PrepareTransfer(pEdmaConfig, (void *)fifoAddr, sizeof(flexcan_frame_t), (void *)pFifoXfer->frame,
                         sizeof(uint32_t), sizeof(flexcan_frame_t), sizeof(flexcan_frame_t), kEDMA_PeripheralToMemory);
#else
    /* The Data Size of FLEXCAN Legacy RX FIFO output port is 16 Bytes, but lots of chips not support 16Bytes width DMA
     * transfer. These chips always support 4Byte width memory transfer, so we need prepare Memory to Memory mode by 4
     * Bytes width mode.
     */
    EDMA_PrepareTransfer(pEdmaConfig, (void *)fifoAddr, 4U, (void *)pFifoXfer->frame, sizeof(uint32_t),
                         sizeof(flexcan_frame_t), sizeof(flexcan_frame_t), kEDMA_MemoryToMemory);
#endif
}

/*!
 * brief Start Transfer Data from the FLEXCAN Legacy Rx FIFO using eDMA.
 *
 * This function to Update edma transfer confiugration and Start eDMA transfer
 *
 * param base FlexCAN peripheral base address.
 * param handle Pointer to flexcan_edma_handle_t structure.
 * param pEdmaConfig The user configuration structure of type edma_transfer_t.
 * retval kStatus_Success if succeed, others failed.
 * retval kStatus_FLEXCAN_RxFifoBusy Previous transfer ongoing.
 */
status_t FLEXCAN_StartTransferDatafromRxFIFO(CAN_Type *base,
                                             flexcan_edma_handle_t *handle,
                                             edma_transfer_config_t *pEdmaConfig)
{
    assert(NULL != handle->rxFifoEdmaHandle);
    assert(NULL != pEdmaConfig);
    status_t status;

    /* If previous Rx FIFO receive not finished. */
    if ((uint8_t)KFLEXCAN_RxFifoBusy == handle->rxFifoState)
    {
        status = kStatus_FLEXCAN_RxFifoBusy;
    }
    else
    {
        handle->rxFifoState = (uint8_t)KFLEXCAN_RxFifoBusy;

        /* Enable FlexCAN Rx FIFO EDMA. */
        FLEXCAN_EnableRxFifoDMA(base, true);

        /* Submit configuration. */
        (void)EDMA_SubmitTransfer(handle->rxFifoEdmaHandle, (const edma_transfer_config_t *)pEdmaConfig);
        /* Start transfer. */
        EDMA_StartTransfer(handle->rxFifoEdmaHandle);

        status = kStatus_Success;
    }

    return status;
}

/*!
 * brief Receives the CAN Message from the Legacy Rx FIFO using eDMA.
 *
 * This function receives the CAN Message using eDMA. This is a non-blocking function, which returns
 * right away. After the CAN Message is received, the receive callback function is called.
 *
 * param base FlexCAN peripheral base address.
 * param handle Pointer to flexcan_edma_handle_t structure.
 * param pFifoXfer FlexCAN Rx FIFO EDMA transfer structure, see #flexcan_fifo_transfer_t.
 * retval kStatus_Success if succeed, others failed.
 * retval kStatus_FLEXCAN_RxFifoBusy Previous transfer ongoing.
 */
status_t FLEXCAN_TransferReceiveFifoEDMA(CAN_Type *base,
                                         flexcan_edma_handle_t *handle,
                                         flexcan_fifo_transfer_t *pFifoXfer)
{
    assert(NULL != handle->rxFifoEdmaHandle);

    edma_transfer_config_t dmaXferConfig;
    status_t status;

    /* Prepare transfer. */
    FLEXCAN_PrepareTransfConfiguration(base, pFifoXfer, &dmaXferConfig);

    /* Submit configuration and start edma transfer. */
    status = FLEXCAN_StartTransferDatafromRxFIFO(base, handle, &dmaXferConfig);

    return status;
}

/*!
 * brief Aborts the receive Legacy/Enhanced Rx FIFO process which used eDMA.
 *
 * This function aborts the receive Legacy/Enhanced Rx FIFO process which used eDMA.
 *
 * param base FlexCAN peripheral base address.
 * param handle Pointer to flexcan_edma_handle_t structure.
 */
void FLEXCAN_TransferAbortReceiveFifoEDMA(CAN_Type *base, flexcan_edma_handle_t *handle)
{
    assert(NULL != handle->rxFifoEdmaHandle);

    /* Stop transfer. */
    EDMA_AbortTransfer(handle->rxFifoEdmaHandle);

    handle->rxFifoState = (uint8_t)KFLEXCAN_RxFifoIdle;
#if (defined(FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO) && FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO)
    handle->framefd  = NULL;
    handle->frameNum = 0U;
#endif
    /* Disable FlexCAN Legacy/Enhanced Rx FIFO EDMA. */
    FLEXCAN_EnableRxFifoDMA(base, false);
}

#if (defined(FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO) && FSL_FEATURE_FLEXCAN_HAS_ENHANCED_RX_FIFO)
/*!
 * brief Receives the CAN FD Message from the Enhanced Rx FIFO using eDMA.
 *
 * This function receives the CAN FD Message using eDMA. This is a non-blocking function, which returns
 * right away. After the CAN Message is received, the receive callback function is called.
 *
 * param base FlexCAN peripheral base address.
 * param handle Pointer to flexcan_edma_handle_t structure.
 * param pFifoXfer FlexCAN Rx FIFO EDMA transfer structure, see #flexcan_fifo_transfer_t.
 * retval kStatus_Success if succeed, others failed.
 * retval kStatus_FLEXCAN_RxFifoBusy Previous transfer ongoing.
 * retval kStatus_InvalidArgument  The watermark configuration is invalid, the watermark need be set to
                                    1 to do successfully EDMA transfer with this API.
 */
status_t FLEXCAN_TransferReceiveEnhancedFifoEDMA(CAN_Type *base,
                                                 flexcan_edma_handle_t *handle,
                                                 flexcan_fifo_transfer_t *pFifoXfer)
{
    assert(NULL != handle->rxFifoEdmaHandle);
    assert(NULL != pFifoXfer->framefd);

    edma_transfer_config_t dmaXferConfig;
    status_t status;
    flexcan_fd_frame_t *fifoAddr = (flexcan_fd_frame_t *)E_RX_FIFO(base);
    uint32_t perReadWords        = ((base->ERFCR & CAN_ERFCR_DMALW_MASK) >> CAN_ERFCR_DMALW_SHIFT) + 1U;
    uint32_t watermark           = ((base->ERFCR & CAN_ERFCR_ERFWM_MASK) >> CAN_ERFCR_ERFWM_SHIFT) + 1U;

    handle->frameNum = pFifoXfer->frameNum;
    handle->framefd  = pFifoXfer->framefd;
    /*!< To reduce the complexity of DMA software configuration, need to set watermark to 1 to make that each DMA
       request read once Rx FIFO. Because a DMA transfer cannot be dynamically changed, Number of words read per
       transfer (ERFCR[DMALW] + 1) should be programmed so that the Enhanced Rx FIFO element can store the largest CAN
       message present on the CAN bus. */
    if ((watermark != 1U) || ((sizeof(uint32_t) * perReadWords) != sizeof(flexcan_fd_frame_t)))
    {
        return kStatus_InvalidArgument;
    }

    /* Prepare transfer. */
    EDMA_PrepareTransfer(&dmaXferConfig, (void *)fifoAddr, sizeof(uint32_t), (void *)pFifoXfer->framefd,
                         sizeof(uint32_t), sizeof(uint32_t) * perReadWords,  /* minor loop bytes : 4* perReadWords */
                         sizeof(uint32_t) * perReadWords * handle->frameNum, /* major loop counts : handle->frameNum */
                         kEDMA_MemoryToMemory);
    /* Submit configuration. */
    (void)EDMA_SubmitTransfer(handle->rxFifoEdmaHandle, &dmaXferConfig);
    handle->rxFifoEdmaHandle->base->CH[handle->rxFifoEdmaHandle->channel].TCD_NBYTES_MLOFFYES &=
        ~DMA_TCD_NBYTES_MLOFFYES_MLOFF_MASK;
    handle->rxFifoEdmaHandle->base->CH[handle->rxFifoEdmaHandle->channel].TCD_NBYTES_MLOFFYES |=
        DMA_TCD_NBYTES_MLOFFYES_MLOFF(128U - sizeof(uint32_t) * perReadWords) | DMA_TCD_NBYTES_MLOFFYES_SMLOE_MASK;
    handle->rxFifoEdmaHandle->base->CH[handle->rxFifoEdmaHandle->channel].TCD_ATTR &= ~(uint16_t)DMA_TCD_ATTR_SMOD_MASK;
    handle->rxFifoEdmaHandle->base->CH[handle->rxFifoEdmaHandle->channel].TCD_ATTR |= DMA_TCD_ATTR_SMOD(7U);

    /* If previous Rx FIFO receive not finished. */
    if ((uint8_t)KFLEXCAN_RxFifoBusy == handle->rxFifoState)
    {
        status = kStatus_FLEXCAN_RxFifoBusy;
    }
    else
    {
        handle->rxFifoState = (uint8_t)KFLEXCAN_RxFifoBusy;

        /* Enable FlexCAN Rx FIFO EDMA. */
        FLEXCAN_EnableRxFifoDMA(base, true);
        /* Start transfer. */
        EDMA_StartTransfer(handle->rxFifoEdmaHandle);

        status = kStatus_Success;
    }

    return status;
}

/*!
 * brief Gets the Enhanced Rx Fifo transfer status during a interrupt non-blocking receive.
 *
 * param base FlexCAN peripheral base address.
 * param handle FlexCAN handle pointer.
 * param count Number of CAN messages receive so far by the non-blocking transaction.
 * retval kStatus_InvalidArgument count is Invalid.
 * retval kStatus_Success Successfully return the count.
 */

status_t FLEXCAN_TransferGetReceiveEnhancedFifoCountEMDA(CAN_Type *base, flexcan_edma_handle_t *handle, size_t *count)
{
    assert(NULL != handle);

    status_t result = kStatus_Success;

    if (handle->rxFifoState == (uint32_t)KFLEXCAN_RxFifoIdle)
    {
        result = kStatus_NoTransferInProgress;
    }
    else
    {
        *count = handle->frameNum -
                 EDMA_GetRemainingMajorLoopCount(handle->rxFifoEdmaHandle->base, handle->rxFifoEdmaHandle->channel);
    }

    return result;
}
#endif
