/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2017-2020 NXP
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_spdif_edma.h"
#if defined FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
#include "fsl_memory.h"
#endif

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.spdif_edma"
#endif

/*******************************************************************************
 * Definitations
 ******************************************************************************/
/* Used for edma_tcd_t size aligned */
#define STCD_ADDR(address) (edma_tcd_t *)(((uint32_t)(address) + sizeof(edma_tcd_t)) & ~(sizeof(edma_tcd_t) - 1U))

/*<! Structure definition for uart_edma_private_handle_t. The structure is private. */
typedef struct _spdif_edma_private_handle
{
    SPDIF_Type *base;
    spdif_edma_handle_t *handle;
} spdif_edma_private_handle_t;

/*!
 * @brief Used for conversion between `void*` and `uint32_t`.
 */
typedef union pvoid_to_u32
{
    void *pvoid;
    uint32_t u32;
} pvoid_to_u32_t;

/*! @brief spdif edma transfer state. */
enum
{
    kSPDIF_Busy = 0x0U, /*!< SPDIF is busy */
    kSPDIF_Idle,        /*!< Transfer is done. */
};

/*<! Private handle only used for internally. */
static spdif_edma_private_handle_t s_edmaPrivateHandle[FSL_FEATURE_SOC_SPDIF_COUNT][2];
static uint8_t s_spdif_tx_watermark[4] = {16, 12, 8, 4};
static uint8_t s_spdif_rx_watermark[4] = {1, 4, 8, 16};

/*******************************************************************************
 * Prototypes
 ******************************************************************************/
/*!
 * @brief Submit SPDIF tcds to EDMA.
 *
 * @param base SPDIF base pointer.
 */
static status_t SPDIF_SubmitTransfer(edma_handle_t *handle,
                                     const edma_transfer_config_t *config,
                                     uint32_t rightChannel);

/*!
 * @brief SPDIF EDMA callback for send.
 *
 * @param handle pointer to spdif_edma_handle_t structure which stores the transfer state.
 * @param userData Parameter for user callback.
 * @param done If the DMA transfer finished.
 * @param tcds The TCD index.
 */
static void SPDIF_TxEDMACallback(edma_handle_t *handle, void *userData, bool done, uint32_t tcds);

/*!
 * @brief SPDIF EDMA callback for receive.
 *
 * @param handle pointer to spdif_edma_handle_t structure which stores the transfer state.
 * @param userData Parameter for user callback.
 * @param done If the DMA transfer finished.
 * @param tcds The TCD index.
 */
static void SPDIF_RxEDMACallback(edma_handle_t *handle, void *userData, bool done, uint32_t tcds);

/*******************************************************************************
 * Code
 ******************************************************************************/
static void SPDIF_TxEDMACallback(edma_handle_t *handle, void *userData, bool done, uint32_t tcds)
{
    spdif_edma_private_handle_t *privHandle = (spdif_edma_private_handle_t *)userData;
    spdif_edma_handle_t *spdifHandle        = privHandle->handle;

    /* If finished a block, call the callback function */
    (void)memset(&spdifHandle->spdifQueue[spdifHandle->queueDriver], 0, sizeof(spdif_edma_transfer_t));
    spdifHandle->queueDriver = (spdifHandle->queueDriver + 0x01U) % SPDIF_XFER_QUEUE_SIZE;
    if (spdifHandle->callback != NULL)
    {
        (spdifHandle->callback)(privHandle->base, spdifHandle, kStatus_SPDIF_TxIdle, spdifHandle->userData);
    }

    /* If all data finished, just stop the transfer */
    if (spdifHandle->spdifQueue[spdifHandle->queueDriver].rightData == NULL)
    {
        SPDIF_TransferAbortSendEDMA(privHandle->base, spdifHandle);
    }
}

static void SPDIF_RxEDMACallback(edma_handle_t *handle, void *userData, bool done, uint32_t tcds)
{
    spdif_edma_private_handle_t *privHandle = (spdif_edma_private_handle_t *)userData;
    spdif_edma_handle_t *spdifHandle        = privHandle->handle;

    /* If finished a block, call the callback function */
    (void)memset(&spdifHandle->spdifQueue[spdifHandle->queueDriver], 0, sizeof(spdif_edma_transfer_t));
    spdifHandle->queueDriver = (spdifHandle->queueDriver + 0x01U) % SPDIF_XFER_QUEUE_SIZE;
    if (spdifHandle->callback != NULL)
    {
        (spdifHandle->callback)(privHandle->base, spdifHandle, kStatus_SPDIF_RxIdle, spdifHandle->userData);
    }

    /* If all data finished, just stop the transfer */
    if (spdifHandle->spdifQueue[spdifHandle->queueDriver].rightData == NULL)
    {
        SPDIF_TransferAbortReceiveEDMA(privHandle->base, spdifHandle);
    }
}

static status_t SPDIF_SubmitTransfer(edma_handle_t *handle, const edma_transfer_config_t *config, uint32_t rightChannel)
{
#if defined(FSL_EDMA_DRIVER_EDMA4) && FSL_EDMA_DRIVER_EDMA4
    edma_tcd_t *tcdRegs = handle->tcdBase;
#else
    edma_tcd_t *tcdRegs = (edma_tcd_t *)(uint32_t)&handle->base->TCD[handle->channel];
#endif
    uint32_t primask;
    uint16_t csr;
    int8_t currentTcd;
    int8_t previousTcd;
    int8_t nextTcd;
    int8_t tcdUsed = handle->tcdUsed;
    int8_t tcdSize = handle->tcdSize;

    /* Check if tcd pool is full. */
    primask = DisableGlobalIRQ();
    if (tcdUsed >= tcdSize)
    {
        EnableGlobalIRQ(primask);

        return kStatus_EDMA_QueueFull;
    }
    currentTcd = handle->tail;
    handle->tcdUsed++;
    /* Calculate index of next TCD */
    nextTcd = currentTcd + 0x01;
    if (nextTcd == handle->tcdSize)
    {
        nextTcd = 0x00;
    }
    /* Advance queue tail index */
    handle->tail = nextTcd;
    EnableGlobalIRQ(primask);
    /* Calculate index of previous TCD */
    previousTcd = (currentTcd != 0x00) ? (currentTcd - 0x01) : (handle->tcdSize - 0x01);
    /* Configure current TCD block. */
#if defined FSL_EDMA_DRIVER_EDMA4 && FSL_EDMA_DRIVER_EDMA4
    EDMA_TcdResetExt(handle->base, &handle->tcdPool[currentTcd]);
    EDMA_TcdSetTransferConfigExt(handle->base, &handle->tcdPool[currentTcd], config, NULL);
    /* Set channel link */
    EDMA_TcdSetChannelLinkExt(handle->base, &handle->tcdPool[currentTcd], kEDMA_MinorLink, rightChannel);
    EDMA_TcdSetChannelLinkExt(handle->base, &handle->tcdPool[currentTcd], kEDMA_MajorLink, rightChannel);
#else
    EDMA_TcdReset(&handle->tcdPool[currentTcd]);
    EDMA_TcdSetTransferConfig(&handle->tcdPool[currentTcd], config, NULL);
    /* Set channel link */
    EDMA_TcdSetChannelLink(&handle->tcdPool[currentTcd], kEDMA_MinorLink, rightChannel);
    EDMA_TcdSetChannelLink(&handle->tcdPool[currentTcd], kEDMA_MajorLink, rightChannel);
#endif
#if defined FSL_EDMA_DRIVER_EDMA4 && FSL_EDMA_DRIVER_EDMA4
    /* Enable major interrupt */
    EDMA_TCD_CSR((&handle->tcdPool[currentTcd]), EDMA_TCD_TYPE(handle->base)) |= DMA_CSR_INTMAJOR_MASK;
    /* Link current TCD with next TCD for identification of current TCD */
#if defined FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
    EDMA_TCD_DLAST_SGA((&handle->tcdPool[currentTcd]), EDMA_TCD_TYPE(handle->base)) =
        MEMORY_ConvertMemoryMapAddress((uint32_t)&handle->tcdPool[nextTcd], kMEMORY_Local2DMA);
#else
    EDMA_TCD_DLAST_SGA((&handle->tcdPool[currentTcd]), EDMA_TCD_TYPE(handle->base)) = (uint32_t)&handle->tcdPool[nextTcd];
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */
    /* Chain from previous descriptor unless tcd pool size is 1(this descriptor is its own predecessor). */
    if (currentTcd != previousTcd)
    {
        /* Enable scatter/gather feature in the previous TCD block. */
        csr = (EDMA_TCD_CSR((&handle->tcdPool[previousTcd]), EDMA_TCD_TYPE(handle->base)) | (uint16_t)DMA_CSR_ESG_MASK) & ~(uint16_t)DMA_CSR_DREQ_MASK;
        EDMA_TCD_CSR((&handle->tcdPool[previousTcd]), EDMA_TCD_TYPE(handle->base)) = csr;
        /*
            Check if the TCD block in the registers is the previous one (points to current TCD block). It
            is used to check if the previous TCD linked has been loaded in TCD register. If so, it need to
            link the TCD register in case link the current TCD with the dead chain when TCD loading occurs
            before link the previous TCD block.
        */
#if defined FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
        if (EDMA_TCD_DLAST_SGA(tcdRegs, EDMA_TCD_TYPE(handle->base)) ==
            MEMORY_ConvertMemoryMapAddress((uint32_t)&handle->tcdPool[currentTcd], kMEMORY_Local2DMA))
#else
        if (EDMA_TCD_DLAST_SGA(tcdRegs, EDMA_TCD_TYPE(handle->base)) == (uint32_t)&handle->tcdPool[currentTcd])
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */
        {
            /* Enable scatter/gather also in the TCD registers. */
            csr = (EDMA_TCD_CSR(tcdRegs, EDMA_TCD_TYPE(handle->base)) | (uint16_t)DMA_CSR_ESG_MASK) & ~(uint16_t)DMA_CSR_DREQ_MASK;
            /* Must write the CSR register one-time, because the transfer maybe finished anytime. */
            EDMA_TCD_CSR(tcdRegs, EDMA_TCD_TYPE(handle->base)) = csr;
            /*
                It is very important to check the ESG bit!
                Because this hardware design: if DONE bit is set, the ESG bit can not be set. So it can
                be used to check if the dynamic TCD link operation is successful. If ESG bit is not set
                and the DLAST_SGA is not the next TCD address(it means the dynamic TCD link succeed and
                the current TCD block has been loaded into TCD registers), it means transfer finished
                and TCD link operation fail, so must install TCD content into TCD registers and enable
                transfer again. And if ESG is set, it means transfer has notfinished, so TCD dynamic
                link succeed.
            */
            if ((EDMA_TCD_CSR(tcdRegs, EDMA_TCD_TYPE(handle->base)) & DMA_CSR_ESG_MASK) != 0x00U)
            {
                return kStatus_Success;
            }
            /*
                Check whether the current TCD block is already loaded in the TCD registers. It is another
                condition when ESG bit is not set: it means the dynamic TCD link succeed and the current
                TCD block has been loaded into TCD registers.
            */
#if defined FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
            if (EDMA_TCD_DLAST_SGA(tcdRegs, EDMA_TCD_TYPE(handle->base)) ==
                MEMORY_ConvertMemoryMapAddress((uint32_t)&handle->tcdPool[nextTcd], kMEMORY_Local2DMA))
#else
            if (EDMA_TCD_DLAST_SGA(tcdRegs, EDMA_TCD_TYPE(handle->base)) == (uint32_t)&handle->tcdPool[nextTcd])
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */
            {
                return kStatus_Success;
            }
            /*
                If go to this, means the previous transfer finished, and the DONE bit is set.
                So shall configure TCD registers.
            */
        }
        else if (EDMA_TCD_DLAST_SGA(tcdRegs, EDMA_TCD_TYPE(handle->base)) != 0x00U)
        {
            /* The current TCD block has been linked successfully. */
            return kStatus_Success;
        }
        else
        {
            /*
                DLAST_SGA is 0 and it means the first submit transfer, so shall configure
                TCD registers.
            */
        }
    }
#else
    /* Enable major interrupt */
    handle->tcdPool[currentTcd].CSR |= DMA_CSR_INTMAJOR_MASK;
    /* Link current TCD with next TCD for identification of current TCD */
#if defined FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
    handle->tcdPool[currentTcd].DLAST_SGA =
        MEMORY_ConvertMemoryMapAddress((uint32_t)&handle->tcdPool[nextTcd], kMEMORY_Local2DMA);
#else
    handle->tcdPool[currentTcd].DLAST_SGA = (uint32_t)&handle->tcdPool[nextTcd];
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */
    /* Chain from previous descriptor unless tcd pool size is 1(this descriptor is its own predecessor). */
    if (currentTcd != previousTcd)
    {
        /* Enable scatter/gather feature in the previous TCD block. */
        csr = (handle->tcdPool[previousTcd].CSR | (uint16_t)DMA_CSR_ESG_MASK) & ~(uint16_t)DMA_CSR_DREQ_MASK;
        handle->tcdPool[previousTcd].CSR = csr;
        /*
            Check if the TCD block in the registers is the previous one (points to current TCD block). It
            is used to check if the previous TCD linked has been loaded in TCD register. If so, it need to
            link the TCD register in case link the current TCD with the dead chain when TCD loading occurs
            before link the previous TCD block.
        */
#if defined FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
        if (tcdRegs->DLAST_SGA ==
            MEMORY_ConvertMemoryMapAddress((uint32_t)&handle->tcdPool[currentTcd], kMEMORY_Local2DMA))
#else
        if (tcdRegs->DLAST_SGA == (uint32_t)&handle->tcdPool[currentTcd])
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */
        {
            /* Enable scatter/gather also in the TCD registers. */
            csr = (tcdRegs->CSR | (uint16_t)DMA_CSR_ESG_MASK) & ~(uint16_t)DMA_CSR_DREQ_MASK;
            /* Must write the CSR register one-time, because the transfer maybe finished anytime. */
            tcdRegs->CSR = csr;
            /*
                It is very important to check the ESG bit!
                Because this hardware design: if DONE bit is set, the ESG bit can not be set. So it can
                be used to check if the dynamic TCD link operation is successful. If ESG bit is not set
                and the DLAST_SGA is not the next TCD address(it means the dynamic TCD link succeed and
                the current TCD block has been loaded into TCD registers), it means transfer finished
                and TCD link operation fail, so must install TCD content into TCD registers and enable
                transfer again. And if ESG is set, it means transfer has notfinished, so TCD dynamic
                link succeed.
            */
            if ((tcdRegs->CSR & DMA_CSR_ESG_MASK) != 0x00U)
            {
                return kStatus_Success;
            }
            /*
                Check whether the current TCD block is already loaded in the TCD registers. It is another
                condition when ESG bit is not set: it means the dynamic TCD link succeed and the current
                TCD block has been loaded into TCD registers.
            */
#if defined FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET && FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET
            if (tcdRegs->DLAST_SGA ==
                MEMORY_ConvertMemoryMapAddress((uint32_t)&handle->tcdPool[nextTcd], kMEMORY_Local2DMA))
#else
            if (tcdRegs->DLAST_SGA == (uint32_t)&handle->tcdPool[nextTcd])
#endif /* FSL_FEATURE_MEMORY_HAS_ADDRESS_OFFSET */
            {
                return kStatus_Success;
            }
            /*
                If go to this, means the previous transfer finished, and the DONE bit is set.
                So shall configure TCD registers.
            */
        }
        else if (tcdRegs->DLAST_SGA != 0x00U)
        {
            /* The current TCD block has been linked successfully. */
            return kStatus_Success;
        }
        else
        {
            /*
                DLAST_SGA is 0 and it means the first submit transfer, so shall configure
                TCD registers.
            */
        }
    }
#endif /* FSL_EDMA_DRIVER_EDMA4 */
    /* There is no live chain, TCD block need to be installed in TCD registers. */
    EDMA_InstallTCD(handle->base, handle->channel, &handle->tcdPool[currentTcd]);
    /* Enable channel request again. */
#if defined EDMA_TRANSFER_ENABLED_MASK && EDMA_TRANSFER_ENABLED_MASK
    if ((handle->flags & EDMA_TRANSFER_ENABLED_MASK) != 0x00U)

    {
        EDMA_EnableChannelRequest(handle->base, handle->channel);
    }
    else
    {
        ; /* Intentional empty */
    }
#endif

    return kStatus_Success;
}

/*!
 * brief Initializes the SPDIF eDMA handle.
 *
 * This function initializes the SPDIF master DMA handle, which can be used for other SPDIF master transactional APIs.
 * Usually, for a specified SPDIF instance, call this API once to get the initialized handle.
 *
 * param base SPDIF base pointer.
 * param handle SPDIF eDMA handle pointer.
 * param base SPDIF peripheral base address.
 * param callback Pointer to user callback function.
 * param userData User parameter passed to the callback function.
 * param dmaLeftHandle eDMA handle pointer for left channel, this handle shall be static allocated by users.
 * param dmaRightHandle eDMA handle pointer for right channel, this handle shall be static allocated by users.
 */
void SPDIF_TransferTxCreateHandleEDMA(SPDIF_Type *base,
                                      spdif_edma_handle_t *handle,
                                      spdif_edma_callback_t callback,
                                      void *userData,
                                      edma_handle_t *dmaLeftHandle,
                                      edma_handle_t *dmaRightHandle)
{
    assert(handle != NULL);
    assert(dmaLeftHandle != NULL);
    assert(dmaRightHandle != NULL);

    uint32_t instance = SPDIF_GetInstance(base);

    /* Zero the handle */
    (void)memset(handle, 0, sizeof(*handle));

    /* Set spdif base to handle */
    handle->dmaLeftHandle  = dmaLeftHandle;
    handle->dmaRightHandle = dmaRightHandle;
    handle->callback       = callback;
    handle->userData       = userData;
    handle->count =
        s_spdif_tx_watermark[(base->SCR & SPDIF_SCR_TXFIFOEMPTY_SEL_MASK) >> SPDIF_SCR_TXFIFOEMPTY_SEL_SHIFT];

    /* Set SPDIF state to idle */
    handle->state = kSPDIF_Idle;

    s_edmaPrivateHandle[instance][0].base   = base;
    s_edmaPrivateHandle[instance][0].handle = handle;

    /* Need to use scatter gather */
    EDMA_InstallTCDMemory(dmaLeftHandle, STCD_ADDR(handle->leftTcd), SPDIF_XFER_QUEUE_SIZE);
    EDMA_InstallTCDMemory(dmaRightHandle, STCD_ADDR(handle->rightTcd), SPDIF_XFER_QUEUE_SIZE);

    /* Install callback for Tx dma channel, only right channel finished, a transfer finished */
    EDMA_SetCallback(dmaRightHandle, SPDIF_TxEDMACallback, &s_edmaPrivateHandle[instance][0]);
}

/*!
 * brief Initializes the SPDIF Rx eDMA handle.
 *
 * This function initializes the SPDIF slave DMA handle, which can be used for other SPDIF master transactional APIs.
 * Usually, for a specified SPDIF instance, call this API once to get the initialized handle.
 *
 * param base SPDIF base pointer.
 * param handle SPDIF eDMA handle pointer.
 * param base SPDIF peripheral base address.
 * param callback Pointer to user callback function.
 * param userData User parameter passed to the callback function.
 * param dmaLeftHandle eDMA handle pointer for left channel, this handle shall be static allocated by users.
 * param dmaRightHandle eDMA handle pointer for right channel, this handle shall be static allocated by users.
 */
void SPDIF_TransferRxCreateHandleEDMA(SPDIF_Type *base,
                                      spdif_edma_handle_t *handle,
                                      spdif_edma_callback_t callback,
                                      void *userData,
                                      edma_handle_t *dmaLeftHandle,
                                      edma_handle_t *dmaRightHandle)
{
    assert(handle != NULL);
    assert(dmaLeftHandle != NULL);
    assert(dmaRightHandle != NULL);

    uint32_t instance = SPDIF_GetInstance(base);

    /* Zero the handle */
    (void)memset(handle, 0, sizeof(*handle));

    /* Set spdif base to handle */
    handle->dmaLeftHandle  = dmaLeftHandle;
    handle->dmaRightHandle = dmaRightHandle;
    handle->callback       = callback;
    handle->userData       = userData;
    handle->count = s_spdif_rx_watermark[(base->SCR & SPDIF_SCR_RXFIFOFULL_SEL_MASK) >> SPDIF_SCR_RXFIFOFULL_SEL_SHIFT];

    /* Set SPDIF state to idle */
    handle->state = kSPDIF_Idle;

    s_edmaPrivateHandle[instance][1].base   = base;
    s_edmaPrivateHandle[instance][1].handle = handle;

    /* Need to use scatter gather */
    EDMA_InstallTCDMemory(dmaLeftHandle, STCD_ADDR(handle->leftTcd), SPDIF_XFER_QUEUE_SIZE);
    EDMA_InstallTCDMemory(dmaRightHandle, STCD_ADDR(handle->rightTcd), SPDIF_XFER_QUEUE_SIZE);

    /* Install callback for Tx dma channel */
    EDMA_SetCallback(dmaRightHandle, SPDIF_RxEDMACallback, &s_edmaPrivateHandle[instance][1]);
}

/*!
 * brief Performs a non-blocking SPDIF transfer using DMA.
 *
 * note This interface returns immediately after the transfer initiates. Call
 * SPDIF_GetTransferStatus to poll the transfer status and check whether the SPDIF transfer is finished.
 *
 * param base SPDIF base pointer.
 * param handle SPDIF eDMA handle pointer.
 * param xfer Pointer to the DMA transfer structure.
 * retval kStatus_Success Start a SPDIF eDMA send successfully.
 * retval kStatus_InvalidArgument The input argument is invalid.
 * retval kStatus_TxBusy SPDIF is busy sending data.
 */
status_t SPDIF_TransferSendEDMA(SPDIF_Type *base, spdif_edma_handle_t *handle, spdif_edma_transfer_t *xfer)
{
    assert(handle != NULL);
    assert(xfer != NULL);

    pvoid_to_u32_t destAddr;
    edma_transfer_config_t config = {0};
    destAddr.u32                  = SPDIF_TxGetLeftDataRegisterAddress(base);

    /* Check if input parameter invalid */
    if ((xfer->leftData == NULL) || (xfer->dataSize == 0U) || (xfer->rightData == NULL))
    {
        return kStatus_InvalidArgument;
    }

    if ((handle->spdifQueue[handle->queueUser].leftData != NULL) ||
        (handle->spdifQueue[handle->queueUser].rightData != NULL))
    {
        return kStatus_SPDIF_QueueFull;
    }

    /* Change the state of handle */
    handle->state = kSPDIF_Busy;

    /* Update the queue state */
    handle->transferSize[handle->queueUser]         = xfer->dataSize;
    handle->spdifQueue[handle->queueUser].leftData  = xfer->leftData;
    handle->spdifQueue[handle->queueUser].dataSize  = xfer->dataSize;
    handle->spdifQueue[handle->queueUser].rightData = xfer->rightData;
    handle->queueUser                               = (handle->queueUser + 0x01U) % SPDIF_XFER_QUEUE_SIZE;

    /* Store the initially configured eDMA minor byte transfer count into the SPDIF handle */
    handle->nbytes = handle->count * 8U;

    /* Prepare edma configure */
    EDMA_PrepareTransfer(&config, xfer->leftData, 4U, destAddr.pvoid, 4U, (uint32_t)handle->count * 4U, xfer->dataSize,
                         kEDMA_MemoryToPeripheral);
    (void)SPDIF_SubmitTransfer(handle->dmaLeftHandle, &config, handle->dmaRightHandle->channel);

    /* Prepare right channel */
    destAddr.u32 = SPDIF_TxGetRightDataRegisterAddress(base);
    EDMA_PrepareTransfer(&config, xfer->rightData, 4U, destAddr.pvoid, 4U, (uint32_t)handle->count * 4U, xfer->dataSize,
                         kEDMA_MemoryToPeripheral);
    (void)EDMA_SubmitTransfer(handle->dmaRightHandle, &config);

    /* Start DMA transfer */
    EDMA_StartTransfer(handle->dmaLeftHandle);

    /* Enable DMA enable bit */
    SPDIF_EnableDMA(base, kSPDIF_TxDMAEnable, true);

    /* Enable SPDIF Tx clock */
    SPDIF_TxEnable(base, true);

    return kStatus_Success;
}

/*!
 * brief Performs a non-blocking SPDIF receive using eDMA.
 *
 * note This interface returns immediately after the transfer initiates. Call
 * the SPDIF_GetReceiveRemainingBytes to poll the transfer status and check whether the SPDIF transfer is finished.
 *
 * param base SPDIF base pointer
 * param handle SPDIF eDMA handle pointer.
 * param xfer Pointer to DMA transfer structure.
 * retval kStatus_Success Start a SPDIF eDMA receive successfully.
 * retval kStatus_InvalidArgument The input argument is invalid.
 * retval kStatus_RxBusy SPDIF is busy receiving data.
 */
status_t SPDIF_TransferReceiveEDMA(SPDIF_Type *base, spdif_edma_handle_t *handle, spdif_edma_transfer_t *xfer)
{
    assert(handle != NULL);
    assert(xfer != NULL);

    pvoid_to_u32_t srcAddr;
    edma_transfer_config_t config = {0};
    srcAddr.u32                   = SPDIF_RxGetLeftDataRegisterAddress(base);

    /* Check if input parameter invalid */
    if ((xfer->leftData == NULL) || (xfer->dataSize == 0U) || (xfer->rightData == NULL))
    {
        return kStatus_InvalidArgument;
    }

    if ((handle->spdifQueue[handle->queueUser].leftData != NULL) ||
        (handle->spdifQueue[handle->queueUser].rightData != NULL))
    {
        return kStatus_SPDIF_QueueFull;
    }

    /* Change the state of handle */
    handle->state = kSPDIF_Busy;

    /* Update the queue state */
    handle->transferSize[handle->queueUser]         = xfer->dataSize;
    handle->spdifQueue[handle->queueUser].leftData  = xfer->leftData;
    handle->spdifQueue[handle->queueUser].dataSize  = xfer->dataSize;
    handle->spdifQueue[handle->queueUser].rightData = xfer->rightData;
    handle->queueUser                               = (handle->queueUser + 0x01U) % SPDIF_XFER_QUEUE_SIZE;

    /* Store the initially configured eDMA minor byte transfer count into the SPDIF handle */
    handle->nbytes = handle->count * 8U;

    /* Prepare edma configure */
    EDMA_PrepareTransfer(&config, srcAddr.pvoid, 4U, xfer->leftData, 4U, (uint32_t)handle->count * 4U, xfer->dataSize,
                         kEDMA_PeripheralToMemory);
    /* Use specific submit function to enable channel link */
    (void)SPDIF_SubmitTransfer(handle->dmaLeftHandle, &config, handle->dmaRightHandle->channel);

    /* Prepare right channel */
    srcAddr.u32 = SPDIF_RxGetRightDataRegisterAddress(base);
    EDMA_PrepareTransfer(&config, srcAddr.pvoid, 4U, xfer->rightData, 4U, (uint32_t)handle->count * 4U, xfer->dataSize,
                         kEDMA_PeripheralToMemory);
    (void)EDMA_SubmitTransfer(handle->dmaRightHandle, &config);

    /* Start DMA transfer */
    EDMA_StartTransfer(handle->dmaLeftHandle);

    /* Enable DMA enable bit */
    SPDIF_EnableDMA(base, kSPDIF_RxDMAEnable, true);

    /* Enable SPDIF Rx clock */
    SPDIF_RxEnable(base, true);

    return kStatus_Success;
}

/*!
 * brief Aborts a SPDIF transfer using eDMA.
 *
 * param base SPDIF base pointer.
 * param handle SPDIF eDMA handle pointer.
 */
void SPDIF_TransferAbortSendEDMA(SPDIF_Type *base, spdif_edma_handle_t *handle)
{
    assert(handle != NULL);

    /* Disable dma */
    EDMA_AbortTransfer(handle->dmaLeftHandle);
    EDMA_AbortTransfer(handle->dmaRightHandle);

    /* Disable DMA enable bit */
    SPDIF_EnableDMA(base, kSPDIF_TxDMAEnable, false);

    /* Set internal state */
    (void)memset(handle->spdifQueue, 0, sizeof(handle->spdifQueue));
    (void)memset(handle->transferSize, 0, sizeof(handle->transferSize));
    handle->queueUser   = 0U;
    handle->queueDriver = 0U;

    /* Set the handle state */
    handle->state = kSPDIF_Idle;
}

/*!
 * brief Aborts a SPDIF receive using eDMA.
 *
 * param base SPDIF base pointer
 * param handle SPDIF eDMA handle pointer.
 */
void SPDIF_TransferAbortReceiveEDMA(SPDIF_Type *base, spdif_edma_handle_t *handle)
{
    assert(handle != NULL);

    /* Disable dma */
    EDMA_AbortTransfer(handle->dmaLeftHandle);
    EDMA_AbortTransfer(handle->dmaRightHandle);

    /* Disable DMA enable bit */
    SPDIF_EnableDMA(base, kSPDIF_RxDMAEnable, false);

    /* Set internal state */
    (void)memset(handle->spdifQueue, 0, sizeof(handle->spdifQueue));
    (void)memset(handle->transferSize, 0, sizeof(handle->transferSize));
    handle->queueUser   = 0U;
    handle->queueDriver = 0U;

    /* Set the handle state */
    handle->state = kSPDIF_Idle;
}

/*!
 * brief Gets byte count sent by SPDIF.
 *
 * param base SPDIF base pointer.
 * param handle SPDIF eDMA handle pointer.
 * param count Bytes count sent by SPDIF.
 * retval kStatus_Success Succeed get the transfer count.
 * retval kStatus_NoTransferInProgress There is no non-blocking transaction in progress.
 */
status_t SPDIF_TransferGetSendCountEDMA(SPDIF_Type *base, spdif_edma_handle_t *handle, size_t *count)
{
    assert(handle != NULL);

    status_t status = kStatus_Success;

    if (handle->state != (uint32_t)kSPDIF_Busy)
    {
        status = kStatus_NoTransferInProgress;
    }
    else
    {
        *count = (handle->transferSize[handle->queueDriver] -
                  (uint32_t)handle->nbytes *
                      EDMA_GetRemainingMajorLoopCount(handle->dmaRightHandle->base, handle->dmaRightHandle->channel));
    }

    return status;
}

/*!
 * brief Gets byte count received by SPDIF.
 *
 * param base SPDIF base pointer
 * param handle SPDIF eDMA handle pointer.
 * param count Bytes count received by SPDIF.
 * retval kStatus_Success Succeed get the transfer count.
 * retval kStatus_NoTransferInProgress There is no non-blocking transaction in progress.
 */
status_t SPDIF_TransferGetReceiveCountEDMA(SPDIF_Type *base, spdif_edma_handle_t *handle, size_t *count)
{
    assert(handle != NULL);

    status_t status = kStatus_Success;

    if (handle->state != (uint32_t)kSPDIF_Busy)
    {
        status = kStatus_NoTransferInProgress;
    }
    else
    {
        *count = (handle->transferSize[handle->queueDriver] -
                  (uint32_t)handle->nbytes *
                      EDMA_GetRemainingMajorLoopCount(handle->dmaRightHandle->base, handle->dmaRightHandle->channel));
    }

    return status;
}
