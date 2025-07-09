/*
 * Copyright (c) 2015, Freescale Semiconductor, Inc.
 * Copyright 2016-2021, 2025 NXP
 * All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "fsl_lpi2c_edma.h"
#include <stdlib.h>
#include <string.h>

/*
 * $Coverage Justification Reference$
 *
 * $Justification fsl_lpi2c_edma_c_ref_1$
 * Need multiple master and slave modules on bus to simulate the true branch
 *
 * $Justification fsl_lpi2c_edma_c_ref_2$
 * FSL_FEATURE_LPI2C_HAS_SEPARATE_DMA_RX_TX_REQn(X) is a constant.
 *
 */

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/* Component ID definition, used by tools. */
#ifndef FSL_COMPONENT_ID
#define FSL_COMPONENT_ID "platform.drivers.lpi2c_edma"
#endif

/* @brief Mask to align an address to edma_tcd_t size. */
#define ALIGN_TCD_SIZE_MASK (sizeof(edma_tcd_t) - 1U)

/* ! @brief LPI2C master fifo commands. */
enum _lpi2c_master_fifo_cmd
{
    kTxDataCmd = LPI2C_MTDR_CMD(0x0U), /*!< Transmit DATA[7:0] */
    kRxDataCmd = LPI2C_MTDR_CMD(0X1U), /*!< Receive (DATA[7:0] + 1) bytes */
    kStopCmd   = LPI2C_MTDR_CMD(0x2U), /*!< Generate STOP condition */
    kStartCmd  = LPI2C_MTDR_CMD(0x4U), /*!< Generate(repeated) START and transmit address in DATA[[7:0] */
};

/*! @brief States for the state machine used by transactional APIs. */
enum _lpi2c_transfer_states
{
    kIdleState = 0,
    kSendCommandState,
    kIssueReadCommandState,
    kTransferDataState,
    kStopState,
    kWaitForCompletionState,
};

/*! @brief Typedef for interrupt handler. */
typedef void (*lpi2c_isr_t)(LPI2C_Type *base, void *handle);

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*!
 * @brief Prepares the command buffer with the sequence of commands needed to send the requested transaction.
 * @param handle Master DMA driver handle.
 * @return Number of command words.
 */
static uint32_t LPI2C_GenerateCommands(lpi2c_master_edma_handle_t *handle);

/*!
 * @brief DMA completion callback.
 * @param dmaHandle DMA channel handle for the channel that completed.
 * @param userData User data associated with the channel handle. For this callback, the user data is the
 *      LPI2C DMA driver handle.
 * @param isTransferDone Whether the DMA transfer has completed.
 * @param tcds Number of TCDs that completed.
 */
static void LPI2C_MasterEDMACallback(edma_handle_t *dmaHandle, void *userData, bool isTransferDone, uint32_t tcds);

/*!
 * @brief LPI2C master edma transfer IRQ handle routine.
 *
 * This API handles the LPI2C bus error status and invoke callback if needed.
 *
 * @param base The LPI2C peripheral base address.
 * @param lpi2cMasterEdmaHandle Pointer to the LPI2C master edma handle.
 */
static void LPI2C_MasterTransferEdmaHandleIRQ(LPI2C_Type *base, void *lpi2cMasterEdmaHandle);
/*******************************************************************************
 * Variables
 ******************************************************************************/

static uint32_t lpi2c_edma_RecSetting = 0x02;

/*******************************************************************************
 * Code
 ******************************************************************************/

/*!
 * brief Create a new handle for the LPI2C master DMA APIs.
 *
 * The creation of a handle is for use with the DMA APIs. Once a handle
 * is created, there is not a corresponding destroy handle. If the user wants to
 * terminate a transfer, the LPI2C_MasterTransferAbortEDMA() API shall be called.
 *
 * For devices where the LPI2C send and receive DMA requests are OR'd together, the a txDmaHandle
 * parameter is ignored and may be set to NULL.
 *
 * param base The LPI2C peripheral base address.
 * param[out] handle Pointer to the LPI2C master driver handle.
 * param rxDmaHandle Handle for the eDMA receive channel. Created by the user prior to calling this function.
 * param txDmaHandle Handle for the eDMA transmit channel. Created by the user prior to calling this function.
 * param callback User provided pointer to the asynchronous callback function.
 * param userData User provided pointer to the application callback data.
 */
void LPI2C_MasterCreateEDMAHandle(LPI2C_Type *base,
                                  lpi2c_master_edma_handle_t *handle,
                                  edma_handle_t *rxDmaHandle,
                                  edma_handle_t *txDmaHandle,
                                  lpi2c_master_edma_transfer_callback_t callback,
                                  void *userData)
{
    assert(handle != NULL);
    assert(rxDmaHandle != NULL);
    assert(txDmaHandle != NULL);

    /* Look up instance number */
    uint32_t instance = LPI2C_GetInstance(base);

    /* Clear out the handle. */
    (void)memset(handle, 0, sizeof(*handle));

    /* Set up the handle. For combined rx/tx DMA requests, the tx channel handle is set to the rx handle */
    /* in order to make the transfer API code simpler. */
    handle->base               = base;
    handle->completionCallback = callback;
    handle->userData           = userData;
    handle->rx                 = rxDmaHandle;
    handle->tx                 = (FSL_FEATURE_LPI2C_HAS_SEPARATE_DMA_RX_TX_REQn(base) > 0) ? txDmaHandle : rxDmaHandle;
    handle->remainingCommand   = 0;
    handle->commandIndex       = 0;
    handle->enableTxReadyFlag  = false;

    /* Save the handle in global variables to support the double weak mechanism. */
    s_lpi2cMasterHandle[instance] = handle;

    /* Set LPI2C_MasterTransferEdmaHandleIRQ as LPI2C DMA IRQ handler */
    s_lpi2cMasterIsr = LPI2C_MasterTransferEdmaHandleIRQ;

    /* Enable interrupt in NVIC. */
#ifdef LPI2C_IRQS
    (void)EnableIRQ(kLpi2cIrqs[instance]);
#endif
#ifdef LPI2C_MASTER_IRQS
    (void)EnableIRQ(kLpi2cMasterIrqs[instance]);
#endif

    /* Set DMA channel completion callbacks. */
    EDMA_SetCallback(handle->rx, LPI2C_MasterEDMACallback, handle);
    if (FSL_FEATURE_LPI2C_HAS_SEPARATE_DMA_RX_TX_REQn(base) != 0)
    {
        EDMA_SetCallback(handle->tx, LPI2C_MasterEDMACallback, handle);
    }
}

static uint32_t LPI2C_GenerateCommands(lpi2c_master_edma_handle_t *handle)
{
    lpi2c_master_transfer_t *xfer = &handle->transfer;
    uint16_t *cmd                 = (uint16_t *)&handle->commandBuffer;
    uint32_t cmdCount             = 0;

    /* Handle no start option. */
    if ((xfer->flags & (uint32_t)kLPI2C_TransferNoStartFlag) != 0U)
    {
        if (xfer->direction == kLPI2C_Read)
        {
            /* Need to issue read command first. */
            cmd[cmdCount++] = (uint16_t)kRxDataCmd | (uint16_t)LPI2C_MTDR_DATA(xfer->dataSize - 1U);
        }
    }
    else
    {
        /*
         * Initial direction depends on whether a subaddress was provided, and of course the actual
         * data transfer direction.
         */
        lpi2c_direction_t direction = (xfer->subaddressSize != 0U) ? kLPI2C_Write : xfer->direction;

        /* Start command. */
        cmd[cmdCount++] =
            (uint16_t)kStartCmd | (uint16_t)((uint16_t)((uint16_t)xfer->slaveAddress << 1U) | (uint16_t)direction);

        /* Subaddress, MSB first. */
        if (xfer->subaddressSize != 0U)
        {
            uint32_t subaddressRemaining = xfer->subaddressSize;
            while (0U != subaddressRemaining--)
            {
                uint8_t subaddressByte = (uint8_t)(xfer->subaddress >> (8U * subaddressRemaining)) & 0xffU;
                cmd[cmdCount++]        = subaddressByte;
            }
        }

        /* Reads need special handling because we have to issue a read command and maybe a repeated start. */
        if ((xfer->dataSize != 0U) && (xfer->direction == kLPI2C_Read))
        {
            /* Need to send repeated start if switching directions to read. */
            if (direction == kLPI2C_Write)
            {
                cmd[cmdCount++] = (uint16_t)kStartCmd |
                                  (uint16_t)((uint16_t)((uint16_t)xfer->slaveAddress << 1U) | (uint16_t)kLPI2C_Read);
            }

            /* Read command. A single write to MTDR can issue read operation of 0xFFU + 1 byte of data at most, so when
              the dataSize is larger than 0x100U, push multiple read commands to MTDR until dataSize is reached. */
            size_t tmpRxSize = xfer->dataSize;
            while (tmpRxSize != 0U)
            {
                if (tmpRxSize > 256U)
                {
                    cmd[cmdCount++] = (uint16_t)kRxDataCmd | (uint16_t)LPI2C_MTDR_DATA(0xFFU);
                    tmpRxSize -= 256U;
                }
                else
                {
                    cmd[cmdCount++] = (uint16_t)kRxDataCmd | (uint16_t)LPI2C_MTDR_DATA(tmpRxSize - 1U);
                    tmpRxSize       = 0U;
                }
            }
        }
    }

    return cmdCount;
}

/*!
 * brief Performs a non-blocking DMA-based transaction on the I2C bus.
 *
 * The callback specified when the a handle was created is invoked when the transaction has
 * completed.
 *
 * param base The LPI2C peripheral base address.
 * param handle Pointer to the LPI2C master driver handle.
 * param transfer The pointer to the transfer descriptor.
 * retval #kStatus_Success The transaction was started successfully.
 * retval #kStatus_LPI2C_Busy Either another master is currently utilizing the bus, or another DMA
 *      transaction is already in progress.
 */
status_t LPI2C_MasterTransferEDMA(LPI2C_Type *base,
                                  lpi2c_master_edma_handle_t *handle,
                                  lpi2c_master_transfer_t *transfer)
{
    status_t result;

    assert(handle != NULL);
    assert(transfer != NULL);
    assert(transfer->subaddressSize <= sizeof(transfer->subaddress));

    /* Check transfer data size in read operation. */
    /* A single write to MTDR can issue read operation of 0xFFU + 1 byte of data at most, so when the dataSize is larger
       than 0x100U, push multiple read commands to MTDR until dataSize is reached. LPI2C edma transfer uses linked
       descriptor to transfer command and data, the command buffer is stored in handle. Allocate 4 command words to
       carry read command which can cover nearly all use cases. */
    if ((transfer->direction == kLPI2C_Read) && (transfer->dataSize > (256U * 9U)))
    {
        return kStatus_InvalidArgument;
    }

    /* Return busy if another transaction is in progress. */
    if (handle->isBusy)
    {
        return kStatus_LPI2C_Busy;
    }

    /* Enable the master function and disable the slave function. */
    LPI2C_MasterEnable(base, true);
    LPI2C_SlaveEnable(base, false);

    /* Return an error if the bus is already in use not by us. */
    result = LPI2C_CheckForBusyBus(base);
    /*
     * $Branch Coverage Justification$
     * $ref fsl_lpi2c_edma_c_ref_1$
     */
    if (result != kStatus_Success)
    {
        return result;
    }

    /* We're now busy. */
    handle->isBusy = true;

    /* Disable LPI2C IRQ and DMA sources while we configure stuff. */
    LPI2C_MasterDisableInterrupts(base, (uint32_t)kLPI2C_MasterIrqFlags);
    LPI2C_MasterEnableDMA(base, false, false);

    /* Clear all flags. */
    LPI2C_MasterClearStatusFlags(base, (uint32_t)kLPI2C_MasterClearFlags);

    /* Save transfer into handle. */
    handle->transfer = *transfer;

    /* Generate commands to send. */
    uint32_t commandCount = LPI2C_GenerateCommands(handle);

    /* If the user is transmitting no data with no start or stop, then just go ahead and invoke the callback. */
    if ((0U == commandCount) && (transfer->dataSize == 0U))
    {
        if (handle->completionCallback != NULL)
        {
            handle->completionCallback(base, handle, kStatus_Success, handle->userData);
        }
        return kStatus_Success;
    }

    /* Reset DMA channels. */
    EDMA_ResetChannel(handle->rx->base, handle->rx->channel);
    if (FSL_FEATURE_LPI2C_HAS_SEPARATE_DMA_RX_TX_REQn(base) != 0)
    {
        EDMA_ResetChannel(handle->tx->base, handle->tx->channel);
    }

    /* Get a 32-byte aligned TCD pointer. */
    edma_tcd_t *tcd = (edma_tcd_t *)((uint32_t)(&handle->tcds[1]) & (~ALIGN_TCD_SIZE_MASK));

    bool hasSendData    = (transfer->direction == kLPI2C_Write) && (transfer->dataSize != 0U);
    bool hasReceiveData = (transfer->direction == kLPI2C_Read) && (transfer->dataSize != 0U);

    edma_transfer_config_t transferConfig = {0};
    edma_tcd_t *linkTcd                   = NULL;

    /* Set up data transmit. */
    if (hasSendData)
    {
        uint32_t *srcAddr               = (uint32_t *)transfer->data;
        transferConfig.srcAddr          = (uint32_t)srcAddr;
        transferConfig.destAddr         = (uint32_t)LPI2C_MasterGetTxFifoAddress(base);
        transferConfig.srcTransferSize  = kEDMA_TransferSize1Bytes;
        transferConfig.destTransferSize = kEDMA_TransferSize1Bytes;
        transferConfig.srcOffset        = (int16_t)sizeof(uint8_t);
        transferConfig.destOffset       = 0;
        transferConfig.minorLoopBytes   = sizeof(uint8_t); /* TODO optimize to fill fifo */
        transferConfig.majorLoopCounts  = transfer->dataSize;

        /* Store the initially configured eDMA minor byte transfer count into the LPI2C handle */
        handle->nbytes = (uint8_t)transferConfig.minorLoopBytes;

        if (commandCount != 0U)
        {
#if defined FSL_EDMA_DRIVER_EDMA4 && FSL_EDMA_DRIVER_EDMA4
            /* Create a software TCD, which will be chained after the commands. */
            EDMA_TcdResetExt(handle->tx->base, tcd);
            EDMA_TcdSetTransferConfigExt(handle->tx->base, tcd, &transferConfig, NULL);
            EDMA_TcdEnableInterruptsExt(handle->tx->base, tcd, (uint32_t)kEDMA_MajorInterruptEnable);
#else
            /* Create a software TCD, which will be chained after the commands. */
            EDMA_TcdReset(tcd);
            EDMA_TcdSetTransferConfig(tcd, &transferConfig, NULL);
            EDMA_TcdEnableInterrupts(tcd, (uint32_t)kEDMA_MajorInterruptEnable);
#endif
            linkTcd = tcd;
        }
        else
        {
            /* User is only transmitting data with no required commands, so this transfer can stand alone. */
            EDMA_SetTransferConfig(handle->tx->base, handle->tx->channel, &transferConfig, NULL);
            EDMA_EnableChannelInterrupts(handle->tx->base, handle->tx->channel, (uint32_t)kEDMA_MajorInterruptEnable);
        }
    }
    else if (hasReceiveData)
    {
        uint32_t *srcAddr = (uint32_t *)transfer->data;
        /* Set up data receive. */
        transferConfig.srcAddr          = (uint32_t)LPI2C_MasterGetRxFifoAddress(base);
        transferConfig.destAddr         = (uint32_t)srcAddr;
        transferConfig.srcTransferSize  = kEDMA_TransferSize1Bytes;
        transferConfig.destTransferSize = kEDMA_TransferSize1Bytes;
        transferConfig.srcOffset        = 0;
        transferConfig.destOffset       = (int16_t)sizeof(uint8_t);
        transferConfig.minorLoopBytes   = sizeof(uint8_t); /* TODO optimize to empty fifo */
        transferConfig.majorLoopCounts  = transfer->dataSize;

        /* Store the initially configured eDMA minor byte transfer count into the LPI2C handle */
        handle->nbytes = (uint8_t)transferConfig.minorLoopBytes;

        if ((FSL_FEATURE_LPI2C_HAS_SEPARATE_DMA_RX_TX_REQn(base) != 0) || (0U == commandCount))
        {
            /* We can put this receive transfer on its own DMA channel. */
            EDMA_SetTransferConfig(handle->rx->base, handle->rx->channel, &transferConfig, NULL);
            EDMA_EnableChannelInterrupts(handle->rx->base, handle->rx->channel, (uint32_t)kEDMA_MajorInterruptEnable);
        }
        else
        {
            /* For shared rx/tx DMA requests, when there are commands, create a software TCD of
               enabling rx dma and disabling tx dma, which will be chained onto the commands transfer,
               and create another software TCD of transfering data and chain it onto the last TCD.
               Notice that in this situation assume tx/rx uses same channel */
#if defined FSL_EDMA_DRIVER_EDMA4 && FSL_EDMA_DRIVER_EDMA4
            EDMA_TcdResetExt(handle->rx->base, tcd);
            EDMA_TcdSetTransferConfigExt(handle->rx->base, tcd, &transferConfig, NULL);
            EDMA_TcdEnableInterruptsExt(handle->rx->base, tcd, (uint32_t)kEDMA_MajorInterruptEnable);
#else
            EDMA_TcdReset(tcd);
            EDMA_TcdSetTransferConfig(tcd, &transferConfig, NULL);
            EDMA_TcdEnableInterrupts(tcd, (uint32_t)kEDMA_MajorInterruptEnable);
#endif

            transferConfig.srcAddr          = (uint32_t)&lpi2c_edma_RecSetting;
            transferConfig.destAddr         = (uint32_t) & (base->MDER);
            transferConfig.srcTransferSize  = kEDMA_TransferSize1Bytes;
            transferConfig.destTransferSize = kEDMA_TransferSize1Bytes;
            transferConfig.srcOffset        = 0;
            transferConfig.destOffset       = (int16_t)sizeof(uint8_t);
            transferConfig.minorLoopBytes   = sizeof(uint8_t);
            transferConfig.majorLoopCounts  = 1;

            edma_tcd_t *tcdSetRxClearTxDMA = (edma_tcd_t *)((uint32_t)(&handle->tcds[2]) & (~ALIGN_TCD_SIZE_MASK));
#if defined FSL_EDMA_DRIVER_EDMA4 && FSL_EDMA_DRIVER_EDMA4
            EDMA_TcdResetExt(handle->rx->base, tcdSetRxClearTxDMA);
            EDMA_TcdSetTransferConfigExt(handle->rx->base, tcdSetRxClearTxDMA, &transferConfig, tcd);
#else
            EDMA_TcdReset(tcdSetRxClearTxDMA);
            EDMA_TcdSetTransferConfig(tcdSetRxClearTxDMA, &transferConfig, tcd);
#endif
            linkTcd = tcdSetRxClearTxDMA;
        }
    }
    else
    {
        /* No data to send */
    }

    /* Set up commands transfer. */
    if (commandCount != 0U)
    {
        transferConfig.srcAddr          = (uint32_t)handle->commandBuffer;
        transferConfig.destAddr         = (uint32_t)LPI2C_MasterGetTxFifoAddress(base);
        transferConfig.srcTransferSize  = kEDMA_TransferSize2Bytes;
        transferConfig.destTransferSize = kEDMA_TransferSize2Bytes;
        transferConfig.srcOffset        = (int16_t)sizeof(uint16_t);
        transferConfig.destOffset       = 0;
        transferConfig.minorLoopBytes   = sizeof(uint16_t); /* TODO optimize to fill fifo */
        if((FSL_FEATURE_LPI2C_HAS_SEPARATE_DMA_RX_TX_REQn(base) != 0) || transfer->direction == kLPI2C_Write)
        {
            transferConfig.majorLoopCounts = commandCount;
            handle->remainingCommand = 0;
        }
        else
        {
            uint32_t maxTxFifo = (handle->base->PARAM & LPI2C_PARAM_MTXFIFO_MASK) >> LPI2C_PARAM_MTXFIFO_SHIFT;
            uint32_t minCommandCount = MIN(commandCount, maxTxFifo);
            transferConfig.majorLoopCounts = minCommandCount;
            handle->remainingCommand = commandCount - minCommandCount;
            handle->commandIndex = maxTxFifo;
        }
        if(handle->remainingCommand > 0)
        {
            handle->enableTxReadyFlag = true;
            EDMA_EnableChannelInterrupts(handle->rx->base, handle->rx->channel, (uint32_t)kEDMA_MajorInterruptEnable);
        }
        else
        {
            handle->enableTxReadyFlag = false;
        }

        EDMA_SetTransferConfig(handle->tx->base, handle->tx->channel, &transferConfig, linkTcd);
    }

    /* Start DMA transfer. */
    /*
     * $Branch Coverage Justification$
     * $ref fsl_lpi2c_edma_c_ref_2$
     */
    if (hasReceiveData || (0 == FSL_FEATURE_LPI2C_HAS_SEPARATE_DMA_RX_TX_REQn(base)))
    {
        EDMA_StartTransfer(handle->rx);
    }
    /*
     * $Branch Coverage Justification$
     * $ref fsl_lpi2c_edma_c_ref_2$
     */
    if ((hasSendData || (commandCount != 0U)) && (FSL_FEATURE_LPI2C_HAS_SEPARATE_DMA_RX_TX_REQn(base) != 0))
    {
        EDMA_StartTransfer(handle->tx);
    }

    /* Enable DMA in both directions. This actually kicks of the transfer. */
    LPI2C_MasterEnableDMA(base, true, true);

    /* Enable all LPI2C master interrupts */
    LPI2C_MasterEnableInterrupts(base,
                                 (uint32_t)kLPI2C_MasterArbitrationLostFlag | (uint32_t)kLPI2C_MasterNackDetectFlag |
                                     (uint32_t)kLPI2C_MasterPinLowTimeoutFlag | (uint32_t)kLPI2C_MasterFifoErrFlag);

    return result;
}

/*!
 * brief Returns number of bytes transferred so far.
 *
 * param base The LPI2C peripheral base address.
 * param handle Pointer to the LPI2C master driver handle.
 * param[out] count Number of bytes transferred so far by the non-blocking transaction.
 * retval #kStatus_Success
 * retval #kStatus_NoTransferInProgress There is not a DMA transaction currently in progress.
 */
status_t LPI2C_MasterTransferGetCountEDMA(LPI2C_Type *base, lpi2c_master_edma_handle_t *handle, size_t *count)
{
    assert(handle != NULL);

    if (NULL == count)
    {
        return kStatus_InvalidArgument;
    }

    /* Catch when there is not an active transfer. */
    if (!handle->isBusy)
    {
        *count = 0;
        return kStatus_NoTransferInProgress;
    }

    uint32_t remaining = handle->transfer.dataSize;

    /* If the DMA is still on a commands transfer that chains to the actual data transfer, */
    /* we do nothing and return the number of transferred bytes as zero. */
    if (EDMA_GetNextTCDAddress(handle->tx) == 0U)
    {
        if (handle->transfer.direction == kLPI2C_Write)
        {
            remaining =
                (uint32_t)handle->nbytes * EDMA_GetRemainingMajorLoopCount(handle->tx->base, handle->tx->channel);
        }
        else
        {
            remaining =
                (uint32_t)handle->nbytes * EDMA_GetRemainingMajorLoopCount(handle->rx->base, handle->rx->channel);
        }
    }

    *count = handle->transfer.dataSize - remaining;

    return kStatus_Success;
}

/*!
 * brief Terminates a non-blocking LPI2C master transmission early.
 *
 * note It is not safe to call this function from an IRQ handler that has a higher priority than the
 *      eDMA peripheral's IRQ priority.
 *
 * param base The LPI2C peripheral base address.
 * param handle Pointer to the LPI2C master driver handle.
 * retval #kStatus_Success A transaction was successfully aborted.
 * retval #kStatus_LPI2C_Idle There is not a DMA transaction currently in progress.
 */
status_t LPI2C_MasterTransferAbortEDMA(LPI2C_Type *base, lpi2c_master_edma_handle_t *handle)
{
    /* Catch when there is not an active transfer. */
    if (!handle->isBusy)
    {
        return kStatus_LPI2C_Idle;
    }

    /* Terminate DMA transfers. */
    EDMA_AbortTransfer(handle->rx);
    if (FSL_FEATURE_LPI2C_HAS_SEPARATE_DMA_RX_TX_REQn(base) != 0)
    {
        EDMA_AbortTransfer(handle->tx);
    }

    /* Reset fifos. */
    base->MCR |= LPI2C_MCR_RRF_MASK | LPI2C_MCR_RTF_MASK;

    /* Disable LPI2C interrupts. */
    LPI2C_MasterDisableInterrupts(base, (uint32_t)kLPI2C_MasterIrqFlags);

    /* If master is still busy and has not send out stop signal yet. */
    if ((LPI2C_MasterGetStatusFlags(base) &
         ((uint32_t)kLPI2C_MasterStopDetectFlag | (uint32_t)kLPI2C_MasterBusyFlag)) == (uint32_t)kLPI2C_MasterBusyFlag)
    {
        /* Send a stop command to finalize the transfer. */
        base->MTDR = (uint32_t)kStopCmd;
    }

    /* Reset handle. */
    handle->isBusy = false;

    return kStatus_Success;
}

static void LPI2C_MasterEDMACallback(edma_handle_t *dmaHandle, void *userData, bool isTransferDone, uint32_t tcds)
{
    lpi2c_master_edma_handle_t *handle = (lpi2c_master_edma_handle_t *)userData;

    if (NULL == handle)
    {
        return;
    }

    if((FSL_FEATURE_LPI2C_HAS_SEPARATE_DMA_RX_TX_REQn(base) == 0) && handle->enableTxReadyFlag == true)
    {
        LPI2C_MasterEnableInterrupts(handle->base, kLPI2C_MasterTxReadyFlag);
        handle->enableTxReadyFlag = false;
        return;
    }

    /* Check for errors. */
    status_t result = LPI2C_MasterCheckAndClearError(handle->base, LPI2C_MasterGetStatusFlags(handle->base));

    /* Done with this transaction. */
    handle->isBusy = false;

    if (0U == (handle->transfer.flags & (uint32_t)kLPI2C_TransferNoStopFlag))
    {
        /* Send a stop command to finalize the transfer. */
        handle->base->MTDR = (uint32_t)kStopCmd;
    }

    /* Invoke callback. */
    if (handle->completionCallback != NULL)
    {
        handle->completionCallback(handle->base, handle, result, handle->userData);
    }
}

static void LPI2C_MasterTransferEdmaHandleIRQ(LPI2C_Type *base, void *lpi2cMasterEdmaHandle)
{
    assert(lpi2cMasterEdmaHandle != NULL);

    lpi2c_master_edma_handle_t *handle = (lpi2c_master_edma_handle_t *)lpi2cMasterEdmaHandle;
    uint32_t status                    = LPI2C_MasterGetStatusFlags(base);
    status_t result                    = kStatus_Success;
    if(0U != (status & (uint32_t)kLPI2C_MasterTxReadyFlag))
    {
        if(handle->remainingCommand > 0)
        {
            uint32_t i;
            uint32_t maxTxFifo = (handle->base->PARAM & LPI2C_PARAM_MTXFIFO_MASK) >> LPI2C_PARAM_MTXFIFO_SHIFT;
            uint32_t txCount = maxTxFifo - ((base->MFSR & LPI2C_MFSR_TXCOUNT_MASK) >> LPI2C_MFSR_TXCOUNT_SHIFT);
            for(i = 0; i < MIN(txCount, handle->remainingCommand); i++)
            {
                base->MTDR = handle->commandBuffer[handle->commandIndex + i];
            }
            handle->remainingCommand -= i;
            handle->commandIndex += i;
        }
        if(handle->remainingCommand == 0)
        {
            LPI2C_MasterDisableInterrupts(handle->base, kLPI2C_MasterTxReadyFlag);
        }
    }
    else
    {
        /* Terminate DMA transfers. */
        EDMA_AbortTransfer(handle->rx);
        if (FSL_FEATURE_LPI2C_HAS_SEPARATE_DMA_RX_TX_REQn(base) != 0)
        {
            EDMA_AbortTransfer(handle->tx);
        }

        /* Done with this transaction. */
        handle->isBusy = false;

        /* Disable LPI2C interrupts. */
        LPI2C_MasterDisableInterrupts(base, (uint32_t)kLPI2C_MasterIrqFlags);

        /* Check error status */
        if (0U != (status & (uint32_t)kLPI2C_MasterPinLowTimeoutFlag))
        {
            result = kStatus_LPI2C_PinLowTimeout;
        }
        /*
        * $Branch Coverage Justification$
        * $ref fsl_lpi2c_edma_c_ref_1$
        */
        else if (0U != (status & (uint32_t)kLPI2C_MasterArbitrationLostFlag))
        {
            result = kStatus_LPI2C_ArbitrationLost;
        }
        else if (0U != (status & (uint32_t)kLPI2C_MasterNackDetectFlag))
        {
            result = kStatus_LPI2C_Nak;
        }
        else if (0U != (status & (uint32_t)kLPI2C_MasterFifoErrFlag))
        {
            result = kStatus_LPI2C_FifoError;
        }
        else
        {
            ; /* Intentional empty */
        }

        /* Clear error status. */
        (void)LPI2C_MasterCheckAndClearError(base, status);

        /* Send stop flag if needed */
        if (0U == (handle->transfer.flags & (uint32_t)kLPI2C_TransferNoStopFlag))
        {
            status = LPI2C_MasterGetStatusFlags(base);
            /* If bus is still busy and the master has not generate stop flag */
            if ((status & ((uint32_t)kLPI2C_MasterBusBusyFlag | (uint32_t)kLPI2C_MasterStopDetectFlag)) ==
                (uint32_t)kLPI2C_MasterBusBusyFlag)
            {
                /* Send a stop command to finalize the transfer. */
                handle->base->MTDR = (uint32_t)kStopCmd;
            }
        }

        /* Invoke callback. */
        if (handle->completionCallback != NULL)
        {
            handle->completionCallback(base, handle, result, handle->userData);
        }
    }
}
