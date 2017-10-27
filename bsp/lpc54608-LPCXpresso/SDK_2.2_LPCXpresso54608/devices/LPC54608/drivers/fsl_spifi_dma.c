/*
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright 2016-2017 NXP
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
 * o Neither the name of the copyright holder nor the names of its
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

#include "fsl_spifi_dma.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*<! Structure definition for spifi_dma_private_handle_t. The structure is private. */
typedef struct _spifi_dma_private_handle
{
    SPIFI_Type *base;
    spifi_dma_handle_t *handle;
} spifi_dma_private_handle_t;

/* SPIFI DMA transfer handle. */
enum _spifi_dma_tansfer_states
{
    kSPIFI_Idle,   /* TX idle. */
    kSPIFI_BusBusy /* RX busy. */
};

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*<! Private handle only used for internally. */
static spifi_dma_private_handle_t s_dmaPrivateHandle[FSL_FEATURE_SOC_SPIFI_COUNT][2];

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief SPIFI DMA send finished callback function.
 *
 * This function is called when SPIFI DMA send finished. It disables the SPIFI
 * TX DMA request and sends @ref kStatus_SPIFI_TxIdle to SPIFI callback.
 *
 * @param handle The DMA handle.
 * @param param Callback function parameter.
 */
static void SPIFI_SendDMACallback(dma_handle_t *handle, void *param, bool transferDone, uint32_t intmode);

/*!
 * @brief SPIFI DMA receive finished callback function.
 *
 * This function is called when SPIFI DMA receive finished. It disables the SPIFI
 * RX DMA request and sends @ref kStatus_SPIFI_RxIdle to SPIFI callback.
 *
 * @param handle The DMA handle.
 * @param param Callback function parameter.
 */
static void SPIFI_ReceiveDMACallback(dma_handle_t *handle, void *param, bool transferDone, uint32_t intmode);

/*!
 * @brief Get the SPIFI instance from peripheral base address.
 *
 * @param base SPIFI peripheral base address.
 * @return SPIFI instance.
 */
extern uint32_t SPIFI_GetInstance(SPIFI_Type *base);

/*******************************************************************************
 * Code
 ******************************************************************************/

static void SPIFI_SendDMACallback(dma_handle_t *handle, void *param, bool transferDone, uint32_t intmode)
{
    spifi_dma_private_handle_t *spifiPrivateHandle = (spifi_dma_private_handle_t *)param;

    /* Avoid the warning for unused variables. */
    handle = handle;
    intmode = intmode;

    if (transferDone)
    {
        SPIFI_TransferAbortSendDMA(spifiPrivateHandle->base, spifiPrivateHandle->handle);

        if (spifiPrivateHandle->handle->callback)
        {
            spifiPrivateHandle->handle->callback(spifiPrivateHandle->base, spifiPrivateHandle->handle,
                                                 kStatus_SPIFI_Idle, spifiPrivateHandle->handle->userData);
        }
    }
}

static void SPIFI_ReceiveDMACallback(dma_handle_t *handle, void *param, bool transferDone, uint32_t intmode)
{
    spifi_dma_private_handle_t *spifiPrivateHandle = (spifi_dma_private_handle_t *)param;

    /* Avoid warning for unused parameters. */
    handle = handle;
    intmode = intmode;

    if (transferDone)
    {
        /* Disable transfer. */
        SPIFI_TransferAbortReceiveDMA(spifiPrivateHandle->base, spifiPrivateHandle->handle);

        if (spifiPrivateHandle->handle->callback)
        {
            spifiPrivateHandle->handle->callback(spifiPrivateHandle->base, spifiPrivateHandle->handle,
                                                 kStatus_SPIFI_Idle, spifiPrivateHandle->handle->userData);
        }
    }
}

void SPIFI_TransferTxCreateHandleDMA(SPIFI_Type *base,
                                     spifi_dma_handle_t *handle,
                                     spifi_dma_callback_t callback,
                                     void *userData,
                                     dma_handle_t *dmaHandle)
{
    assert(handle);

    uint32_t instance = SPIFI_GetInstance(base);

    s_dmaPrivateHandle[instance][0].base = base;
    s_dmaPrivateHandle[instance][0].handle = handle;

    memset(handle, 0, sizeof(*handle));

    handle->state = kSPIFI_Idle;
    handle->dmaHandle = dmaHandle;

    handle->callback = callback;
    handle->userData = userData;

    /* Configure TX dma callback */
    DMA_SetCallback(handle->dmaHandle, SPIFI_SendDMACallback, &s_dmaPrivateHandle[instance][0]);
}

void SPIFI_TransferRxCreateHandleDMA(SPIFI_Type *base,
                                     spifi_dma_handle_t *handle,
                                     spifi_dma_callback_t callback,
                                     void *userData,
                                     dma_handle_t *dmaHandle)
{
    assert(handle);

    uint32_t instance = SPIFI_GetInstance(base);

    s_dmaPrivateHandle[instance][1].base = base;
    s_dmaPrivateHandle[instance][1].handle = handle;

    memset(handle, 0, sizeof(*handle));

    handle->state = kSPIFI_Idle;
    handle->dmaHandle = dmaHandle;

    handle->callback = callback;
    handle->userData = userData;

    /* Configure RX dma callback */
    DMA_SetCallback(handle->dmaHandle, SPIFI_ReceiveDMACallback, &s_dmaPrivateHandle[instance][1]);
}

status_t SPIFI_TransferSendDMA(SPIFI_Type *base, spifi_dma_handle_t *handle, spifi_transfer_t *xfer)
{
    assert(handle && (handle->dmaHandle));

    dma_transfer_config_t xferConfig;
    status_t status;

    /* If previous TX not finished. */
    if (kSPIFI_BusBusy == handle->state)
    {
        status = kStatus_SPIFI_Busy;
    }
    else
    {
        handle->state = kSPIFI_BusBusy;

        /* Prepare transfer. */
        DMA_PrepareTransfer(&xferConfig, xfer->data, (void *)SPIFI_GetDataRegisterAddress(base), sizeof(uint32_t),
                            xfer->dataSize, kDMA_MemoryToPeripheral, NULL);

        /* Submit transfer. */
        DMA_SubmitTransfer(handle->dmaHandle, &xferConfig);
        DMA_StartTransfer(handle->dmaHandle);

        /* Enable SPIFI TX DMA. */
        SPIFI_EnableDMA(base, true);

        status = kStatus_Success;
    }

    return status;
}

status_t SPIFI_TransferReceiveDMA(SPIFI_Type *base, spifi_dma_handle_t *handle, spifi_transfer_t *xfer)
{
    assert(handle && (handle->dmaHandle));

    dma_transfer_config_t xferConfig;
    status_t status;

    /* If previous TX not finished. */
    if (kSPIFI_BusBusy == handle->state)
    {
        status = kStatus_SPIFI_Busy;
    }
    else
    {
        handle->state = kSPIFI_BusBusy;

        /* Prepare transfer. */
        DMA_PrepareTransfer(&xferConfig, (void *)SPIFI_GetDataRegisterAddress(base), xfer->data, sizeof(uint32_t),
                            xfer->dataSize, kDMA_PeripheralToMemory, NULL);

        /* Submit transfer. */
        DMA_SubmitTransfer(handle->dmaHandle, &xferConfig);
        DMA_StartTransfer(handle->dmaHandle);

        /* Enable SPIFI TX DMA. */
        SPIFI_EnableDMA(base, true);

        status = kStatus_Success;
    }

    return status;
}

void SPIFI_TransferAbortSendDMA(SPIFI_Type *base, spifi_dma_handle_t *handle)
{
    assert(handle && (handle->dmaHandle));

    /* Disable SPIFI TX DMA. */
    SPIFI_EnableDMA(base, false);

    /* Stop transfer. */
    DMA_AbortTransfer(handle->dmaHandle);

    handle->state = kSPIFI_Idle;
}

void SPIFI_TransferAbortReceiveDMA(SPIFI_Type *base, spifi_dma_handle_t *handle)
{
    assert(handle && (handle->dmaHandle));

    /* Disable SPIFI RX DMA. */
    SPIFI_EnableDMA(base, false);

    /* Stop transfer. */
    DMA_AbortTransfer(handle->dmaHandle);

    handle->state = kSPIFI_Idle;
}

status_t SPIFI_TransferGetSendCountDMA(SPIFI_Type *base, spifi_dma_handle_t *handle, size_t *count)
{
    assert(handle);

    status_t status = kStatus_Success;

    if (handle->state != kSPIFI_BusBusy)
    {
        status = kStatus_NoTransferInProgress;
    }
    else
    {
        *count = handle->transferSize - DMA_GetRemainingBytes(handle->dmaHandle->base, handle->dmaHandle->channel);
    }

    return status;
}

status_t SPIFI_TransferGetReceiveCountDMA(SPIFI_Type *base, spifi_dma_handle_t *handle, size_t *count)
{
    assert(handle);

    status_t status = kStatus_Success;

    if (handle->state != kSPIFI_BusBusy)
    {
        status = kStatus_NoTransferInProgress;
    }
    else
    {
        *count = handle->transferSize - DMA_GetRemainingBytes(handle->dmaHandle->base, handle->dmaHandle->channel);
    }

    return status;
}
